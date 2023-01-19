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
	class App : public Object, public AggregatableDescription<App>
	{
	private:
		WString name;
		List<Ptr<IValueSubscription>> subscriptions;

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

		App() = default;

		~App()
		{
			for (auto sub : subscriptions)
			{
				sub->Close();
			}
			FinalizeAggregation();
		}

		Event<void()> NameChanged;

		WString GetName()
		{
			return name;
		}

		void SetName(const WString& value)
		{
			if (name != value)
			{
				name = value;
				NameChanged();
			}
		}

		List<Ptr<IValueSubscription>>& GetSubscriptions()
		{
			return subscriptions;
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

				CLASS_MEMBER_CONSTRUCTOR(Ptr<App>(), NO_PARAMETER)

				CLASS_MEMBER_EVENT(NameChanged)
				CLASS_MEMBER_PROPERTY_EVENT_FAST(Name, NameChanged)
				CLASS_MEMBER_PROPERTY_READONLY_FAST(Subscriptions)
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

namespace myscript
{
	class MyApp : App
	{
		new(name: string)
		{
			Name = name;

			/* "this" is not allowed in binding, copy it to a variable */
			var self = this;
			var subscription = bind($"Hello, $(self.Name)");

			attach(subscription.ValueChanged,
				func (value: object): void
				{
					Print(cast string value);
				});

			subscription.Open();
			Subscriptions.Add(subscription);
		}

		delete
		{
			Print("Destructing myscript::MyApp");
		}
	}
}

)Workflow";

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

		// call MyApp
		auto myapp = UnboxValue<Ptr<App>>(Value::Create(
			L"myscript::MyApp",
			(Value_xs(), BoxValue(WString(L"vczh")))
			));
		myapp->SetName(L"Vczh Libraries++");
		myapp->SetName(L"Workflow");
		myapp->SetName(L"Gaclib");
	}

	// stop reflection
	DestroyGlobalTypeManager();
}