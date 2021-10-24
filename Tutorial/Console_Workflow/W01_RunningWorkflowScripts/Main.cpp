#include <VlppWorkflowCompiler.h>

using namespace vl;
using namespace vl::console;
using namespace vl::collections;
using namespace vl::parsing;
using namespace vl::reflection::description;
using namespace vl::workflow;
using namespace vl::workflow::emitter;
using namespace vl::workflow::runtime;

const wchar_t ScriptCode[] = LR"Workflow(

module sampleModule;

func main(): string
{
	return "Hello, world!";
}

)Workflow";

int main()
{
	// start reflection
	LoadPredefinedTypes();
	WfLoadLibraryTypes();
	GetGlobalTypeManager()->Load();

	{
		// prepare Workflow script code
		List<WString> codes;
		codes.Add(WString::Unmanaged(ScriptCode));

		// compile code and get assemblies
		List<Ptr<ParsingError>> errors;
		auto table = WfLoadTable();
		auto assembly = Compile(table, codes, errors);
		CHECK_ERROR(assembly && errors.Count() == 0, L"Please check the 'errors' variable.");

		// initialize the assembly
		auto globalContext = MakePtr<WfRuntimeGlobalContext>(assembly);
		auto initializeFunction = LoadFunction<void()>(globalContext, L"<initialize>");
		initializeFunction();

		// call main
		auto mainFunction = LoadFunction<WString()>(globalContext, L"main");
		Console::WriteLine(mainFunction());
	}

	// stop reflection
	DestroyGlobalTypeManager();
}