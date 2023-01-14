#include "W05_Lib.h"

using namespace vl::console;

namespace myapi
{
	WString App::Get()
	{
		return Console::Read();
	}

	WString App::Get(const WString& message)
	{
		Console::Write(message);
		return Console::Read();
	}

	void App::Print(const WString& text)
	{
		Console::WriteLine(text);
	}
}

namespace vl
{
	namespace reflection
	{
		namespace description
		{
#ifndef VCZH_DEBUG_NO_REFLECTION
			MYAPI_TYPELIST(IMPL_CPP_TYPE_INFO)

			using namespace myapi;

#pragma warning(push)
#pragma warning(disable:4250)
			BEGIN_INTERFACE_PROXY_SHAREDPTR(IScripting)
				void Execute(const WString& name)override
				{
					INVOKE_INTERFACE_PROXY(Execute, name);
				}
			END_INTERFACE_PROXY(IScripting)
#pragma warning(pop)

#define _ ,

			BEGIN_CLASS_MEMBER(App)
				CLASS_MEMBER_STATIC_METHOD_OVERLOAD(Get, NO_PARAMETER, WString(*)())
				CLASS_MEMBER_STATIC_METHOD_OVERLOAD(Get, { L"message" }, WString(*)(const WString&))
				CLASS_MEMBER_STATIC_METHOD(Print, { L"text" })
			END_CLASS_MEMBER(App)

			BEGIN_INTERFACE_MEMBER(IScripting)
				CLASS_MEMBER_METHOD(Execute, { L"name" })
			END_INTERFACE_MEMBER(IScripting)

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
#endif

			void LoadMyApiTypes()
			{
#ifndef VCZH_DEBUG_NO_REFLECTION
				GetGlobalTypeManager()->AddTypeLoader(Ptr(new MyApiTypeLoader));
#endif
			}
		}
	}
}