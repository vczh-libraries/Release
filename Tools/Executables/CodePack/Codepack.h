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

inline WString ReadFile(const FilePath& path)
{
	WString text;
	BomEncoder::Encoding encoding;
	bool containsBom;
	File(path).ReadAllTextWithEncodingTesting(text, encoding, containsBom);
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