﻿/***********************************************************************
!!!!!! DO NOT MODIFY !!!!!!

GacGen.exe Resource.xml

This file is generated by Workflow compiler
https://github.com/vczh-libraries
***********************************************************************/

#ifndef VCZH_WORKFLOW_COMPILER_GENERATED_DEMOREFLECTION
#define VCZH_WORKFLOW_COMPILER_GENERATED_DEMOREFLECTION

#include "Demo.h"
#ifndef VCZH_DEBUG_NO_REFLECTION
#include "GacUIReflection.h"
#endif

#if defined( _MSC_VER)
#pragma warning(push)
#pragma warning(disable:4250)
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wparentheses-equality"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#endif

/***********************************************************************
Reflection
***********************************************************************/

namespace vl
{
	namespace reflection
	{
		namespace description
		{
#ifndef VCZH_DEBUG_NO_REFLECTION
			DECL_TYPE_INFO(::demo::ICategory)
			DECL_TYPE_INFO(::demo::IContact)
			DECL_TYPE_INFO(::demo::IViewModel)
			DECL_TYPE_INFO(::demo::MainWindow)
			DECL_TYPE_INFO(::demo::MainWindowConstructor)
			DECL_TYPE_INFO(::demo::NewContactWindow)
			DECL_TYPE_INFO(::demo::NewContactWindowConstructor)
			DECL_TYPE_INFO(::demo::NewFolderWindow)
			DECL_TYPE_INFO(::demo::NewFolderWindowConstructor)

#ifdef VCZH_DESCRIPTABLEOBJECT_WITH_METADATA

			BEGIN_INTERFACE_PROXY_NOPARENT_SHAREDPTR(::demo::ICategory)
				::vl::Ptr<::vl::reflection::description::IValueObservableList> GetContacts() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(GetContacts);
				}
				::vl::Ptr<::vl::reflection::description::IValueObservableList> GetFolders() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(GetFolders);
				}
				::vl::Ptr<::vl::presentation::GuiImageData> GetImage() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(GetImage);
				}
				::vl::WString GetName() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(GetName);
				}
				::demo::ICategory* GetParent() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(GetParent);
				}
			END_INTERFACE_PROXY(::demo::ICategory)

			BEGIN_INTERFACE_PROXY_NOPARENT_SHAREDPTR(::demo::IContact)
				::vl::WString GetAddress() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(GetAddress);
				}
				::vl::Ptr<::vl::presentation::GuiImageData> GetBigImage() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(GetBigImage);
				}
				::vl::DateTime GetBirthday() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(GetBirthday);
				}
				::vl::WString GetBirthdayText() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(GetBirthdayText);
				}
				::vl::WString GetName() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(GetName);
				}
				::vl::WString GetPhone() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(GetPhone);
				}
				::vl::Ptr<::vl::presentation::GuiImageData> GetSmallImage() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(GetSmallImage);
				}
				void Update(const ::vl::WString& name, ::vl::DateTime birthday, const ::vl::WString& phone, const ::vl::WString& address) override
				{
					INVOKE_INTERFACE_PROXY(Update, name, birthday, phone, address);
				}
			END_INTERFACE_PROXY(::demo::IContact)

			BEGIN_INTERFACE_PROXY_NOPARENT_SHAREDPTR(::demo::IViewModel)
				void AddCategory(const ::vl::WString& name) override
				{
					INVOKE_INTERFACE_PROXY(AddCategory, name);
				}
				void AddContact(::vl::Ptr<::demo::IContact> contact) override
				{
					INVOKE_INTERFACE_PROXY(AddContact, contact);
				}
				::vl::Ptr<::demo::IContact> CreateContact() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(CreateContact);
				}
				::vl::Ptr<::demo::ICategory> GetRootCategory() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(GetRootCategory);
				}
				::vl::Ptr<::demo::ICategory> GetSelectedCategory() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(GetSelectedCategory);
				}
				::vl::Ptr<::demo::IContact> GetSelectedContact() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(GetSelectedContact);
				}
				void RemoveCategory() override
				{
					INVOKE_INTERFACE_PROXY_NOPARAMS(RemoveCategory);
				}
				void RemoveContact() override
				{
					INVOKE_INTERFACE_PROXY_NOPARAMS(RemoveContact);
				}
				void SetSelectedCategory(::vl::Ptr<::demo::ICategory> __vwsn_value_) override
				{
					INVOKE_INTERFACE_PROXY(SetSelectedCategory, __vwsn_value_);
				}
				void SetSelectedContact(::vl::Ptr<::demo::IContact> __vwsn_value_) override
				{
					INVOKE_INTERFACE_PROXY(SetSelectedContact, __vwsn_value_);
				}
			END_INTERFACE_PROXY(::demo::IViewModel)
#endif
#endif

			extern bool LoadDemoTypes();
		}
	}
}

#if defined( _MSC_VER)
#pragma warning(pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#endif
