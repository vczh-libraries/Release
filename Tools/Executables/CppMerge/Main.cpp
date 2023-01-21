#include "WfMergeCpp.h"

using namespace vl;
using namespace vl::console;
using namespace vl::filesystem;
using namespace vl::stream;
using namespace vl::workflow::cppcodegen;

#if defined VCZH_MSVC
int wmain(int argc, wchar_t* argv[])
#elif defined VCZH_GCC
int main(int argc, char* argv[])
#endif
{
	Console::SetTitle(L"Vczh CodeMerge for C++");
	if (argc != 4)
	{
		Console::SetColor(true, false, false, true);
		Console::WriteLine(L"Usage: CppMerge <x32-file> <x64-file> <output-file>");
		Console::SetColor(true, true, true, false);
		return 0;
	}
#if defined VCZH_MSVC
	FilePath file32 = argv[1];
	FilePath file64 = argv[2];
	FilePath fileOutput = argv[3];
#elif defined VCZH_GCC
	FilePath file32 = atow(argv[1]);
	FilePath file64 = atow(argv[2]);
	FilePath fileOutput = atow(argv[3]);
#endif

	try
	{
		auto code = MergeCppMultiPlatform(File(file32).ReadAllTextByBom(), File(file64).ReadAllTextByBom());

		File file(fileOutput);
		if (file.Exists())
		{
			code = MergeCppFileContent(file.ReadAllTextByBom(), code);
		}

		if (file.Exists())
		{
			auto originalCode = file.ReadAllTextByBom();
			if (originalCode == code)
			{
				return 0;
			}
		}

		file.WriteAllText(code, true, BomEncoder::Utf8);
		return 0;
	}
	catch (const MergeCppMultiPlatformException& ex)
	{
		Console::SetColor(true, false, false, true);
		Console::WriteLine(ex.Message());
		Console::SetColor(true, true, true, false);
		throw;
	}
}
