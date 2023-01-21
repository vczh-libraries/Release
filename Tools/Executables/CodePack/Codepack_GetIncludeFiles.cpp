#include "Codepack.h"

Regex regexInclude(LR"/(^\s*#include\s*"(<path>[^"]+)"\s*$)/");
Regex regexSystemInclude(LR"/(^\s*#include\s*<(<path>[^"]+)>\s*$)/");
Regex regexInstruction(LR"/(^\s*\/\*\s*CodePack:(<name>\w+)\(((<param>[^,)]+)(,\s*(<param>[^,)]+))*)?\)\s*\*\/\s*$)/");

const vint include_path = regexInclude.CaptureNames().IndexOf(L"path");
const vint systemInclude_path = regexSystemInclude.CaptureNames().IndexOf(L"path");
const vint instruction_name = regexInstruction.CaptureNames().IndexOf(L"name");
const vint instruction_param = regexInstruction.CaptureNames().IndexOf(L"param");

LazyList<FilePath> GetIncludedFiles(
	const FilePath& codeFile,											// (in)
	const Dictionary<WString, FilePath>& skippedImportFiles,			// (in)
	Dictionary<FilePath, LazyList<FilePath>>& cachedFileToIncludes,		// (cache)
	Group<FilePath, Tuple<WString, FilePath>>& conditionOns,			// (out)
	Group<FilePath, Tuple<WString, FilePath>>& conditionOffs			// (out)
)
{
	{
		vint index = cachedFileToIncludes.Keys().IndexOf(codeFile);
		if (index != -1)
		{
			return cachedFileToIncludes.Values()[index];
		}
	}
	Console::SetColor(true, true, false, true);
	Console::WriteLine(L"Scanning file: " + codeFile.GetFullPath());
	Console::SetColor(true, true, true, false);

	List<FilePath> includes;
	StringReader reader(ReadFile(codeFile));
	bool skip = false;
	vint lineIndex = 0;
	while (!reader.IsEnd())
	{
		lineIndex++;
		auto line = reader.ReadLine();
		Ptr<RegexMatch> match;
		if ((match = regexInstruction.MatchHead(line)))
		{
			auto name = match->Groups()[instruction_name][0].Value();
			const List<RegexString>* params = nullptr;
			{
				vint index = match->Groups().Keys().IndexOf(instruction_param);
				if (index != -1)
				{
					params = &match->Groups().GetByIndex(index);
				}
			}

			if (name == L"BeginIgnore")
			{
				if (params == nullptr)
				{
					skip = true;
					continue;
				}
			}
			else if (name == L"EndIgnore")
			{
				if (params == nullptr)
				{
					skip = false;
					continue;
				}
			}
			else if (name == L"ConditionOn")
			{
				if (params && params->Count() == 2)
				{
					conditionOns.Add(codeFile, { params->Get(0).Value(),codeFile.GetFolder() / params->Get(1).Value() });
					continue;
				}
			}
			else if (name == L"ConditionOff")
			{
				if (params && params->Count() == 2)
				{
					conditionOffs.Add(codeFile, { params->Get(0).Value(),codeFile.GetFolder() / params->Get(1).Value() });
					continue;
				}
			}
			Console::SetColor(true, false, false, true);
			Console::WriteLine(L"Error: Unrecognizable CodePack instruction: \"" + line + L"\" in file: " + codeFile.GetFullPath() + L" (" + itow(lineIndex) + L")");
			Console::SetColor(true, true, true, false);
		}
		else if ((match = regexInclude.MatchHead(line)))
		{
			if (!skip)
			{
				auto path = codeFile.GetFolder() / match->Groups()[include_path][0].Value();
				if (!includes.Contains(path))
				{
					includes.Add(path);
				}
			}
		}
		else if ((match = regexSystemInclude.MatchHead(line)))
		{
			if (!skip)
			{
				auto systemFile = match->Groups()[systemInclude_path][0].Value();
				vint index = skippedImportFiles.Keys().IndexOf(systemFile);
				if (index != -1)
				{
					auto path = skippedImportFiles.Values()[index];
					if (!includes.Contains(path))
					{
						includes.Add(path);
					}
				}
			}
		}
	}

	auto result = Ptr(new List<FilePath>);
	CopyFrom(
		*result.Obj(),
		From(includes)
			.Concat(From(includes).SelectMany([&](const FilePath& includedFile)
			{
				return GetIncludedFiles(includedFile, skippedImportFiles, cachedFileToIncludes, conditionOns, conditionOffs);
			}))
			.Distinct()
		);

	cachedFileToIncludes.Add(codeFile, result);
	return result;
}