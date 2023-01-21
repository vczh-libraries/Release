#include "WfMergeCpp.h"
#include <VlppRegex.h>

namespace vl
{
	namespace workflow
	{
		namespace cppcodegen
		{
			using namespace collections;
			using namespace stream;
			using namespace regex;

/***********************************************************************
MergeCpp
***********************************************************************/

			WString RemoveSpacePrefix(const WString& s)
			{
				for (vint i = 0; i < s.Length(); i++)
				{
					if (s[i] != L' '&&s[i] != L'\t')
					{
						return s.Sub(i, s.Length() - i);
					}
				}
				return WString::Empty;
			}

			const vint NORMAL = 0;
			const vint WAIT_HEADER = 1;
			const vint WAIT_OPEN = 2;
			const vint WAIT_CLOSE = 3;
			const vint USER_CONTENT = 4;
			const vint UNUSED_USER_CONTENT = 5;

			template<typename TCallback>
			void ProcessCppContent(const WString& code, const TCallback& callback)
			{
				Regex regexUserContentBegin(L"/.*?(?/{)?///* USER_CONTENT_BEGIN/((<name>[^)]*?)/) /*//");
				vint _name = regexUserContentBegin.CaptureNames().IndexOf(L"name");

				vint state = NORMAL;
				vint counter = 0;
				WString previousContent;

				StringReader reader(code);
				while (!reader.IsEnd())
				{
					auto line = reader.ReadLine();
					if (reader.IsEnd() && line == L"")
					{
						break;
					}

					if (line == L"// UNUSED_USER_CONTENT:")
					{
						state = UNUSED_USER_CONTENT;
					}

					if (state == UNUSED_USER_CONTENT)
					{
						callback(state, state, line, line);
					}
					else
					{
						auto content = RemoveSpacePrefix(line);
						auto previousState = state;
						switch (state)
						{
						case NORMAL:
							if (auto match = regexUserContentBegin.MatchHead(content))
							{
								content = L"USERIMPL(/* " + match->Groups()[_name][0].Value() + L" */)";
								if (match->Captures().Count() > 0)
								{
									content += previousContent;
								}
								state = USER_CONTENT;
							}
							else if (INVLOC.StartsWith(content, L"USERIMPL(",Locale::None))
							{
								state = WAIT_HEADER;
							}
							break;
						case WAIT_HEADER:
							state = WAIT_OPEN;
							break;
						case WAIT_OPEN:
							if (INVLOC.StartsWith(content, L"{", Locale::None))
							{
								state = WAIT_CLOSE;
							}
							break;
						case WAIT_CLOSE:
							if (INVLOC.StartsWith(content, L"{", Locale::None))
							{
								counter++;
							}
							else if (INVLOC.StartsWith(content, L"}", Locale::None))
							{
								if (counter == 0)
								{
									state = NORMAL;
								}
								else
								{
									counter--;
								}
							}
							break;
						case USER_CONTENT:
							if (INVLOC.EndsWith(content, L"/* USER_CONTENT_END() */", Locale::None))
							{
								state = NORMAL;
							}
							break;
						}
						callback(previousState, state, line, content);
					}
					previousContent = RemoveSpacePrefix(line);
				}
			}

			template<typename TCallback>
			void SplitCppContent(const WString& code, Dictionary<WString, WString>& userContents, Dictionary<WString, WString>& userContentsFull, const TCallback& callback)
			{
				WString name;
				WString userImpl;
				WString userImplFull;
				ProcessCppContent(code, [&](vint previousState, vint state, const WString& line, const WString& content)
				{
					if (state == UNUSED_USER_CONTENT)
					{
						callback(line);
					}
					else
					{
						switch (previousState)
						{
						case NORMAL:
							switch (state)
							{
							case WAIT_HEADER:
							case USER_CONTENT:
								name = content;
								userImpl = L"";
								userImplFull = L"";
								break;
							}
							break;
						case WAIT_HEADER:
							name += content;
							break;
						case WAIT_CLOSE:
						case USER_CONTENT:
							switch (state)
							{
							case WAIT_CLOSE:
							case USER_CONTENT:
								userImpl += line + L"\r\n";
								break;
							case NORMAL:
								userImplFull += L"//" + line + L"\r\n";
								userContents.Add(name, userImpl);
								userContentsFull.Add(name, userImplFull);
								name = L"";
								break;
							}
							break;
						}

						if (name != L"")
						{
							userImplFull += L"//" + line + L"\r\n";
						}
					}
				});
			}

			MergeCppMultiPlatformException::MergeCppMultiPlatformException(vint _row32, vint _column32, vint _row64, vint _column64)
				:Exception(L"The difference at "
					L"x86 file(row:" + itow(_row32 + 1) + L", column:" + itow(_column32 + 1) + L") and "
					L"x64 file(row:" + itow(_row64 + 1) + L", column:" + itow(_column64 + 1) + L") are not "
					L"\"vint32_t\" and \"vint64_t\", "
					L"\"vuint32_t\" and \"vuint64_t\", "
					L"\"<number>\" and \"<number>L\", "
					L"\"<number>\" and \"<number>UL\".")
				, row32(_row32)
				, column32(_column32)
				, row64(_row64)
				, column64(_column64)
			{
			}

			void CountRowAndColumn(const wchar_t* start, const wchar_t* reading, vint& row, vint& column)
			{
				row = 0;
				column = 0;
				while (start < reading)
				{
					if (*start++ == L'\n')
					{
						row++;
						column = 0;
					}
					else
					{
						column++;
					}
				}
			}


			WString MergeCppMultiPlatform(const WString& code32, const WString& code64)
			{
				static wchar_t stringCast32[] = L"static_cast<::vl::vint32_t>(";
				const vint lengthCast32 = sizeof(stringCast32) / sizeof(*stringCast32) - 1;

				static wchar_t stringCast64[] = L"static_cast<::vl::vint64_t>(";
				const vint lengthCast64 = sizeof(stringCast64) / sizeof(*stringCast64) - 1;

				return GenerateToStream([&](StreamWriter& writer)
				{
					const wchar_t* reading32 = code32.Buffer();
					const wchar_t* reading64 = code64.Buffer();
					const wchar_t* start32 = reading32;
					const wchar_t* start64 = reading64;
					while (true)
					{
						vint length = 0;
						while (reading32[length] && reading64[length])
						{
							if (reading32[length] == reading64[length])
							{
								length++;
							}
							else
							{
								break;
							}
						}

						writer.WriteString(reading32, length);
						reading32 += length;
						reading64 += length;

						if (*reading32 == 0 && *reading64 == 0)
						{
							break;
						}

#define IS_DIGIT(C) (L'0' <= C && C <= L'9')

						if (reading32[0] == L'3' && reading32[1] == L'2' && reading64[0] == L'6' && reading64[1] == L'4')
						{
							if (length >= 4)
							{
								if (wcsncmp(reading32 - 4, L"vint32_t", 8) == 0 && wcsncmp(reading64 - 4, L"vint64_t", 8) == 0)
								{
									reading32 += 4;
									reading64 += 4;
									goto NEXT_ROUND;
								}
							}
							if (length >= 5)
							{
								if (wcsncmp(reading32 - 5, L"vuint32_t", 9) == 0 && wcsncmp(reading64 - 5, L"vuint64_t", 9) == 0)
								{
									reading32 += 4;
									reading64 += 4;
									goto NEXT_ROUND;
								}
							}
						}
						else if (reading64[0] == L'L')
						{
							if (reading32[0] == reading64[1] && length >= 1)
							{
								if (IS_DIGIT(reading32[-1]) && !IS_DIGIT(reading32[0]))
								{
									if (IS_DIGIT(reading64[-1]) && !IS_DIGIT(reading64[1]))
									{
										reading64 += 1;
										goto NEXT_ROUND;
									}
								}
							}
						}
						else if (reading64[0] == L'U' && reading64[1] == L'L')
						{
							if (reading32[0] == reading64[2] && length >= 1)
							{
								if (IS_DIGIT(reading32[-1]) && !IS_DIGIT(reading32[0]))
								{
									if (IS_DIGIT(reading64[-1]) && !IS_DIGIT(reading64[2]))
									{
										reading64 += 2;
										goto NEXT_ROUND;
									}
								}
							}
						}
						else if (wcsncmp(reading32, stringCast32, lengthCast32) == 0 && IS_DIGIT(reading32[lengthCast32]) && IS_DIGIT(reading64[0]))
						{
							reading32 += lengthCast32;
							vint digitCount = 0;
							while (IS_DIGIT(reading32[digitCount])) digitCount++;
							if (wcsncmp(reading32, reading64, digitCount) == 0 && reading64[digitCount] == L'L' && reading32[digitCount] == L')')
							{
								writer.WriteString(L"static_cast<::vl::vint>(");
								writer.WriteString(WString::CopyFrom(reading32, digitCount));
								writer.WriteChar(L')');
								reading64 += digitCount + 1;
								reading32 += digitCount + 1;
								goto NEXT_ROUND;
							}
						}
						else if (wcsncmp(reading64, stringCast64, lengthCast64) == 0 && IS_DIGIT(reading64[lengthCast64]) && IS_DIGIT(reading32[0]))
						{
							reading64 += lengthCast64;
							vint digitCount = 0;
							while (IS_DIGIT(reading64[digitCount])) digitCount++;
							if (wcsncmp(reading64, reading32, digitCount) == 0 && reading64[digitCount] == L'L' && reading64[digitCount + 1] == L')')
							{
								writer.WriteString(L"static_cast<::vl::vint>(");
								writer.WriteString(WString::CopyFrom(reading64, digitCount));
								writer.WriteChar(L')');
								reading64 += digitCount + 2;
								reading32 += digitCount;
								goto NEXT_ROUND;
							}
						}

						{
							vint row32 = 0;
							vint column32 = 0;
							vint row64 = 0;
							vint column64 = 0;
							CountRowAndColumn(start32, reading32, row32, column32);
							CountRowAndColumn(start64, reading64, row64, column64);
							throw MergeCppMultiPlatformException(row32, column32, row64, column64);
						}
					NEXT_ROUND:;
#undef IS_DIGIT
					}
				});
			}

			WString MergeCppFileContent(const WString& dst, const WString& src)
			{
				Dictionary<WString, WString> userContents, userContentsFull;
				WString unusedUserContent = GenerateToStream([&](StreamWriter& writer)
				{
					SplitCppContent(dst, userContents, userContentsFull, [&](const WString& line)
					{
						writer.WriteLine(line);
					});
				});

				WString processedUnusedUserContent = GenerateToStream([&](StreamWriter& writer)
				{
					StringReader reader(unusedUserContent);
					while (!reader.IsEnd())
					{
						auto line = reader.ReadLine();
						if (line != L"// UNUSED_USER_CONTENT:")
						{
							if (INVLOC.StartsWith(line, L"//", Locale::None))
							{
								line = line.Right(line.Length() - 2);
							}
							writer.WriteLine(line);
						}
					}
				});

				SplitCppContent(processedUnusedUserContent, userContents, userContentsFull, [&](const WString& line) {});
				
				return GenerateToStream([&](StreamWriter& writer)
				{
					WString name;
					WString userImpl;
					ProcessCppContent(src, [&](vint previousState, vint state, const WString& line, const WString& content)
					{
						switch (previousState)
						{
						case NORMAL:
							switch (state)
							{
							case WAIT_HEADER:
							case USER_CONTENT:
								name = content;
								userImpl = L"";
								break;
							}
							break;
						case WAIT_HEADER:
							name += content;
							break;
						case WAIT_CLOSE:
						case USER_CONTENT:
							switch (state)
							{
							case WAIT_CLOSE:
							case USER_CONTENT:
								userImpl += line + L"\r\n";
								return;
							case NORMAL:
								{
									vint index = userContents.Keys().IndexOf(name);
									if (index == -1)
									{
										writer.WriteString(userImpl);
									}
									else
									{
										writer.WriteString(userContents.Values()[index]);
										userContentsFull.Remove(name);
									}
								}
								break;
							}
							break;
						}
						writer.WriteLine(line);
					});

					if (userContentsFull.Count() > 0)
					{
						writer.WriteLine(L"// UNUSED_USER_CONTENT:");
						for (auto content : userContentsFull.Values())
						{
							writer.WriteString(content);
						}
					}
				});
			}
		}
	}
}
