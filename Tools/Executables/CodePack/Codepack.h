#include <VlppGlrParser.h>

using namespace vl;
using namespace vl::collections;
using namespace vl::filesystem;
using namespace vl::glr;
using namespace vl::glr::xml;
using namespace vl::regex;
using namespace vl::console;
using namespace vl::stream;

extern Regex regexInclude;
extern Regex regexSystemInclude;
extern Regex regexInstruction;

extern const vint include_path;
extern const vint systemInclude_path;
extern const vint instruction_name;
extern const vint instruction_param;

inline WString ConvertPathDelimiters(const WString& path, wchar_t delimiter)
{
	if (path.Length() == 0) return path;

	Array<wchar_t> buffer(path.Length() + 1);
	for (vint i = 0; i < path.Length(); i++)
	{
		auto c = path[i];
		buffer[i] = (c == L'/' || c == L'\\') ? delimiter : c;
	}
	buffer[path.Length()] = 0;
	return &buffer[0];
}

inline FilePath NormalizePathForFileSystem(const WString& path)
{
	return FilePath(ConvertPathDelimiters(path, FilePath::GetPathDelimiter()));
}

inline FilePath NormalizePathForFileSystem(const FilePath& path)
{
	return NormalizePathForFileSystem(path.GetFullPath());
}

inline WString GetCodePackPath(const WString& path)
{
	return ConvertPathDelimiters(path, L'\\');
}

inline WString GetCodePackCommentPath(const WString& path)
{
	auto codePackPath = GetCodePackPath(path);
	if (codePackPath.Length() == 0 || codePackPath[0] == L'.')
	{
		return codePackPath;
	}
	return L".\\" + codePackPath;
}

inline WString ReadFile(const FilePath& path)
{
	WString text;
	BomEncoder::Encoding encoding;
	bool containsBom;
	File(NormalizePathForFileSystem(path)).ReadAllTextWithEncodingTesting(text, encoding, containsBom);
	return text;
}

extern LazyList<FilePath> GetCppFiles(
	const FilePath& folder,
	List<WString>& exceptions
	);

extern LazyList<FilePath> GetHeaderFiles(
	const FilePath& folder,
	List<WString>& exceptions
	);

extern void CategorizeCodeFiles(
	Ptr<XmlDocument> config,
	LazyList<FilePath> files,
	Group<WString, FilePath>& categorizedFiles,
	Dictionary<FilePath, WString>& inputFileToCategories
	);

extern LazyList<FilePath> GetIncludedFiles(
	const FilePath& codeFile,
	const Dictionary<WString, FilePath>& skippedImportFiles,
	Dictionary<FilePath, LazyList<FilePath>>& cachedFileToIncludes,
	Group<FilePath, Tuple<WString, FilePath>>& conditionOns,
	Group<FilePath, Tuple<WString, FilePath>>& conditionOffs
	);

extern void Combine(
	const Dictionary<FilePath, WString>& inputFileToOutputFiles,
	const Dictionary<WString, FilePath>& skippedImportFiles,
	Dictionary<FilePath, LazyList<FilePath>>& cachedFileToIncludes,
	Group<FilePath, Tuple<WString, FilePath>>& conditionOns,
	Group<FilePath, Tuple<WString, FilePath>>& conditionOffs,
	const List<FilePath>& files,
	FilePath outputFilePath,
	FilePath outputIncludeFilePath,
	SortedList<WString>& systemIncludes,
	LazyList<WString> externalIncludes
	);
