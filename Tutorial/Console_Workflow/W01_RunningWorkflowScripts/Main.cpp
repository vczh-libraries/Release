#include <VlppWorkflowCompiler.h>

using namespace vl;
using namespace vl::console;
using namespace vl::collections;
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
		List<glr::ParsingError> errors;
		workflow::Parser parser;
		auto assembly = Compile(parser, workflow::analyzer::WfCpuArchitecture::AsExecutable, codes, errors);
		CHECK_ERROR(assembly && errors.Count() == 0, L"Please check the 'errors' variable.");

		// initialize the assembly
		auto globalContext = Ptr(new WfRuntimeGlobalContext(assembly));
		auto initializeFunction = LoadFunction<void()>(globalContext, L"<initialize>");
		initializeFunction();

		// call main
		auto mainFunction = LoadFunction<WString()>(globalContext, L"main");
		Console::WriteLine(mainFunction());
	}

	// stop reflection
	DestroyGlobalTypeManager();
}