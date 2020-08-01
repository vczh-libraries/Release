#pragma once

#include <VlppReflection.h>

using namespace vl;
using namespace vl::reflection;

namespace myapi
{
	class App : public Object, public Description<App>
	{
	public:
		static WString		Get();
		static WString		Get(const WString& message);
		static void			Print(const WString& text);
	};

	class IScripting : public virtual IDescriptable, public Description<IScripting>
	{
	public:
		virtual void Execute(const WString& name) = 0;
	};
}


namespace vl
{
	namespace reflection
	{
		namespace description
		{
#ifndef VCZH_DEBUG_NO_REFLECTION

			#define MYAPI_TYPELIST(F)\
				F(myapi::App)\
				F(myapi::IScripting)\


			MYAPI_TYPELIST(DECL_TYPE_INFO)
#endif

			extern void LoadMyApiTypes();
		}
	}
}