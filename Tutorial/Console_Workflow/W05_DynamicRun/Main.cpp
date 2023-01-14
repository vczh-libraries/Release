#include <VlppWorkflowCompiler.h>
#include "../W05_Lib/W05_Lib.h"

using namespace vl::stream;
using namespace vl::filesystem;
using namespace vl::reflection::description;
using namespace vl::workflow::runtime;

int wmain(int argc, const wchar_t* argv[])
{
	// start reflection
	LoadPredefinedTypes();
	WfLoadLibraryTypes();
	LoadMyApiTypes();
	GetGlobalTypeManager()->Load();

	{
		// load the assembly
		FilePath assemblyPath = FilePath(argv[0]).GetFolder() / L"WorkflowAssembly.bin";
		FileStream fileStream(assemblyPath.GetFullPath(), FileStream::ReadOnly);
		CHECK_ERROR(fileStream.IsAvailable(), L"You need to run W05_Compile before W05_DynamicRun.");

		WfAssemblyLoadErrors errors;
		auto assembly = WfAssembly::Deserialize(fileStream, errors);

		// initialize the assembly
		auto globalContext = Ptr(new WfRuntimeGlobalContext(assembly));
		auto initializeFunction = LoadFunction<void()>(globalContext, L"<initialize>");
		initializeFunction();

		// call MyApp
		auto myapp = Value::Create(L"myscript::MyApp");
		auto scripting = UnboxValue<Ptr<myapi::IScripting>>(myapp.Invoke(L"CreateScripting"));
		scripting->Execute(L"Gaclib");
	}

	// stop reflection
	DestroyGlobalTypeManager();
}