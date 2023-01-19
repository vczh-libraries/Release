#include <VlppWorkflowCompiler.h>

using namespace vl;
using namespace vl::console;
using namespace vl::collections;
using namespace vl::reflection;
using namespace vl::reflection::description;
using namespace vl::workflow;
using namespace vl::workflow::emitter;
using namespace vl::workflow::runtime;

namespace myapi
{
	class App : public Object, public Description<App>
	{
	public:
		static WString Get()
		{
			return Console::Read();
		}

		static WString Get(const WString& message)
		{
			Console::Write(message);
			return Console::Read();
		}

		static void Print(const WString& text)
		{
			Console::WriteLine(text);
		}
	};
}

#define MYAPI_TYPELIST(F)\
	F(myapi::App)\

namespace vl
{
	namespace reflection
	{
		namespace description
		{
			MYAPI_TYPELIST(DECL_TYPE_INFO)
			MYAPI_TYPELIST(IMPL_CPP_TYPE_INFO)

			using namespace myapi;

#define _ ,

			BEGIN_CLASS_MEMBER(App)
				CLASS_MEMBER_STATIC_METHOD_OVERLOAD(Get, NO_PARAMETER, WString(*)())
				CLASS_MEMBER_STATIC_METHOD_OVERLOAD(Get, { L"message" }, WString(*)(const WString&))
				CLASS_MEMBER_STATIC_METHOD(Print, { L"text" })
			END_CLASS_MEMBER(App)

#undef _
			class MyApiTypeLoader : public Object, public ITypeLoader
			{
			public:
				void Load(ITypeManager* manager)
				{
					MYAPI_TYPELIST(ADD_TYPE_INFO)
				}

				void Unload(ITypeManager* manager)
				{
				}
			};
		}
	}
}

const wchar_t ScriptCode[] = LR"Workflow(

module sampleModule;

using myapi::*;

func main(): void
{
	var name = App::Get("Please enter your name:");
	App::Print($"Hello, $(name)!");
}

)Workflow";

class MyDebugger : public WfDebugger
{
protected:
	void OnBlockExecution()override
	{
		// get the context for the current thread
		auto context = GetCurrentThreadContext();

		// whatever the input is, change the "name" variable to be "MyDebugger"
		// it will print "Hello, MyDebugger!" after continuing
		auto assembly = context->globalContext->assembly;
		vint functionIndex = context->GetCurrentStackFrame().functionIndex;
		auto functionMetadata = assembly->functions[functionIndex];
		vint indexName = functionMetadata->localVariableNames.IndexOf(L"name");
		context->StoreLocalVariable(indexName, BoxValue(WString(L"MyDebugger")));

		// continue
		Run();
	}
};

int main()
{
	// start reflection
	LoadPredefinedTypes();
	WfLoadLibraryTypes();
	GetGlobalTypeManager()->AddTypeLoader(Ptr(new MyApiTypeLoader));
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

		// start debugging
		auto debugger = Ptr(new MyDebugger);
		SetDebuggerForCurrentThread(debugger);

		// break at App::Print(...);, which is at line 9 in file 0
		// line  0: 
		// line  1: 
		// line  2: module sampleModule;
		// line  3: 
		// line  4: using myapi::*;
		// line  5: 
		// line  6: func main() : void
		// line  7: {
		// line  8: 	var name = App::Get("Please enter your name:");
		// line  9: 	App::Print($"Hello, $(name)!");
		// line 10: }
		// line 11: 
		// line 12: 
		debugger->AddCodeLineBreakPoint(assembly.Obj(), 0, 9, true);

		// call main, will trap into MyDebugger::OnBlockExecution when hitting the break point
		auto mainFunction = LoadFunction<void()>(globalContext, L"main");
		mainFunction();

		// stop debugging
		SetDebuggerForCurrentThread(nullptr);
	}

	// stop reflection
	DestroyGlobalTypeManager();
}