﻿/***********************************************************************
!!!!!! DO NOT MODIFY !!!!!!

GacGen.exe Resource.xml

This file is generated by Workflow compiler
https://github.com/vczh-libraries
***********************************************************************/

#ifndef VCZH_WORKFLOW_COMPILER_GENERATED_DEMOPARTIALCLASSES
#define VCZH_WORKFLOW_COMPILER_GENERATED_DEMOPARTIALCLASSES

#include "GacUI.h"

#if defined( _MSC_VER)
#pragma warning(push)
#pragma warning(disable:4250)
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wparentheses-equality"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#endif

namespace vl_workflow_global
{
	struct __vwsnf1_Demo_demo_DemoServiceControlConstructor___vwsn_demo_DemoServiceControl_Initialize_;
	struct __vwsnf2_Demo_demo_DemoServiceControlConstructor___vwsn_demo_DemoServiceControl_Initialize_;
	struct __vwsnf3_Demo_demo_DemoServiceControlConstructor___vwsn_demo_DemoServiceControl_Initialize_;
	struct __vwsnf4_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_;
	class __vwsnc1_Demo_demo_DemoServiceControlConstructor___vwsn_demo_DemoServiceControl_Initialize__vl_reflection_description_IValueSubscription;
	class __vwsnc2_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize__vl_reflection_description_IValueSubscription;
	class __vwsnc3_Demo_demo_MainWindow__IDemoService;
}

class IDemoService;
namespace demo
{
	class DemoServiceControlConstructor;
	class DemoServiceControl;
	class MainWindowConstructor;
	class MainWindow;

}
class IDemoService : public virtual ::vl::reflection::IDescriptable, public ::vl::reflection::Description<IDemoService>
{
#ifdef VCZH_DESCRIPTABLEOBJECT_WITH_METADATA
	friend struct ::vl::reflection::description::CustomTypeDescriptorSelector<IDemoService>;
#endif
public:
	static ::vl::WString GetIdentifier();
	virtual ::vl::WString GetName() = 0;
	virtual void SetName(const ::vl::WString& __vwsn_value_) = 0;
	::vl::Event<void()> NameChanged;
};

namespace demo
{
	class DemoServiceControlConstructor : public ::vl::Object, public ::vl::reflection::Description<DemoServiceControlConstructor>
	{
		friend class ::vl_workflow_global::__vwsnc1_Demo_demo_DemoServiceControlConstructor___vwsn_demo_DemoServiceControl_Initialize__vl_reflection_description_IValueSubscription;
		friend struct ::vl_workflow_global::__vwsnf1_Demo_demo_DemoServiceControlConstructor___vwsn_demo_DemoServiceControl_Initialize_;
		friend struct ::vl_workflow_global::__vwsnf2_Demo_demo_DemoServiceControlConstructor___vwsn_demo_DemoServiceControl_Initialize_;
		friend struct ::vl_workflow_global::__vwsnf3_Demo_demo_DemoServiceControlConstructor___vwsn_demo_DemoServiceControl_Initialize_;
#ifdef VCZH_DESCRIPTABLEOBJECT_WITH_METADATA
		friend struct ::vl::reflection::description::CustomTypeDescriptorSelector<DemoServiceControlConstructor>;
#endif
	protected:
		::demo::DemoServiceControl* self;
		::vl::presentation::controls::GuiSinglelineTextBox* textBox;
		::vl::presentation::compositions::GuiTableComposition* __vwsn_precompile_0;
		::vl::presentation::compositions::GuiCellComposition* __vwsn_precompile_1;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_2;
		::vl::presentation::compositions::GuiCellComposition* __vwsn_precompile_3;
		::vl::Ptr<::vl::presentation::elements::GuiSolidLabelElement> __vwsn_precompile_4;
		void __vwsn_demo_DemoServiceControl_Initialize(::demo::DemoServiceControl* __vwsn_this_);
	public:
		DemoServiceControlConstructor();
	};

	class DemoServiceControl : public ::vl::presentation::controls::GuiCustomControl, public ::demo::DemoServiceControlConstructor, public ::vl::reflection::Description<DemoServiceControl>
	{
		friend class ::demo::DemoServiceControlConstructor;
		friend class ::vl_workflow_global::__vwsnc1_Demo_demo_DemoServiceControlConstructor___vwsn_demo_DemoServiceControl_Initialize__vl_reflection_description_IValueSubscription;
		friend struct ::vl_workflow_global::__vwsnf1_Demo_demo_DemoServiceControlConstructor___vwsn_demo_DemoServiceControl_Initialize_;
		friend struct ::vl_workflow_global::__vwsnf2_Demo_demo_DemoServiceControlConstructor___vwsn_demo_DemoServiceControl_Initialize_;
		friend struct ::vl_workflow_global::__vwsnf3_Demo_demo_DemoServiceControlConstructor___vwsn_demo_DemoServiceControl_Initialize_;
#ifdef VCZH_DESCRIPTABLEOBJECT_WITH_METADATA
		friend struct ::vl::reflection::description::CustomTypeDescriptorSelector<DemoServiceControl>;
#endif
	private:
		::IDemoService* demoService;
	public:
		DemoServiceControl();
		~DemoServiceControl();
	};

	class MainWindowConstructor : public ::vl::Object, public ::vl::reflection::Description<MainWindowConstructor>
	{
		friend class ::vl_workflow_global::__vwsnc2_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize__vl_reflection_description_IValueSubscription;
		friend struct ::vl_workflow_global::__vwsnf4_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_;
#ifdef VCZH_DESCRIPTABLEOBJECT_WITH_METADATA
		friend struct ::vl::reflection::description::CustomTypeDescriptorSelector<MainWindowConstructor>;
#endif
	protected:
		::demo::MainWindow* self;
		::vl::presentation::compositions::GuiTableComposition* __vwsn_precompile_0;
		::vl::presentation::compositions::GuiCellComposition* __vwsn_precompile_1;
		::demo::DemoServiceControl* __vwsn_precompile_2;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_3;
		void __vwsn_demo_MainWindow_Initialize(::demo::MainWindow* __vwsn_this_);
	public:
		MainWindowConstructor();
	};

	class MainWindow : public ::vl::presentation::controls::GuiWindow, public ::demo::MainWindowConstructor, public ::vl::reflection::Description<MainWindow>
	{
		friend class ::vl_workflow_global::__vwsnc3_Demo_demo_MainWindow__IDemoService;
		friend class ::demo::MainWindowConstructor;
		friend class ::vl_workflow_global::__vwsnc2_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize__vl_reflection_description_IValueSubscription;
		friend struct ::vl_workflow_global::__vwsnf4_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_;
#ifdef VCZH_DESCRIPTABLEOBJECT_WITH_METADATA
		friend struct ::vl::reflection::description::CustomTypeDescriptorSelector<MainWindow>;
#endif
	private:
		::vl::Ptr<::IDemoService> demoService;
	public:
		MainWindow();
		void __vwsn_instance_ctor_();
		~MainWindow();
	};

}
/***********************************************************************
Global Variables and Functions
***********************************************************************/

namespace vl_workflow_global
{
	class Demo
	{
	public:

		static Demo& Instance();
	};

/***********************************************************************
Closures
***********************************************************************/

	struct __vwsnf1_Demo_demo_DemoServiceControlConstructor___vwsn_demo_DemoServiceControl_Initialize_
	{
		::demo::DemoServiceControlConstructor* __vwsnthis_0;

		__vwsnf1_Demo_demo_DemoServiceControlConstructor___vwsn_demo_DemoServiceControl_Initialize_(::demo::DemoServiceControlConstructor* __vwsnctorthis_0);

		void operator()(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments) const;
	};

	struct __vwsnf2_Demo_demo_DemoServiceControlConstructor___vwsn_demo_DemoServiceControl_Initialize_
	{
		::demo::DemoServiceControlConstructor* __vwsnthis_0;

		__vwsnf2_Demo_demo_DemoServiceControlConstructor___vwsn_demo_DemoServiceControl_Initialize_(::demo::DemoServiceControlConstructor* __vwsnctorthis_0);

		void operator()(const ::vl::reflection::description::Value& __vwsn_value_) const;
	};

	struct __vwsnf3_Demo_demo_DemoServiceControlConstructor___vwsn_demo_DemoServiceControl_Initialize_
	{
		::demo::DemoServiceControlConstructor* __vwsnthis_0;

		__vwsnf3_Demo_demo_DemoServiceControlConstructor___vwsn_demo_DemoServiceControl_Initialize_(::demo::DemoServiceControlConstructor* __vwsnctorthis_0);

		void operator()(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiControlSignalEventArgs* arguments) const;
	};

	struct __vwsnf4_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_
	{
		::demo::MainWindowConstructor* __vwsnthis_0;

		__vwsnf4_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_(::demo::MainWindowConstructor* __vwsnctorthis_0);

		void operator()(const ::vl::reflection::description::Value& __vwsn_value_) const;
	};

	class __vwsnc1_Demo_demo_DemoServiceControlConstructor___vwsn_demo_DemoServiceControl_Initialize__vl_reflection_description_IValueSubscription : public ::vl::Object, public virtual ::vl::reflection::description::IValueSubscription
	{
	public:
		::demo::DemoServiceControlConstructor* __vwsnthis_0;

		__vwsnc1_Demo_demo_DemoServiceControlConstructor___vwsn_demo_DemoServiceControl_Initialize__vl_reflection_description_IValueSubscription(::demo::DemoServiceControlConstructor* __vwsnctorthis_0);

		::demo::DemoServiceControl* __vwsn_bind_cache_0 = nullptr;
		::vl::Ptr<::vl::reflection::description::IEventHandler> __vwsn_bind_handler_0_0;
		bool __vwsn_bind_opened_ = false;
		bool __vwsn_bind_closed_ = false;
		void __vwsn_bind_activator_();
		void __vwsn_bind_callback_0_0(::vl::presentation::compositions::GuiGraphicsComposition* __vwsn_bind_callback_argument_0, ::vl::presentation::compositions::GuiEventArgs* __vwsn_bind_callback_argument_1);
		bool Open() override;
		bool Update() override;
		bool Close() override;
	};

	class __vwsnc2_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize__vl_reflection_description_IValueSubscription : public ::vl::Object, public virtual ::vl::reflection::description::IValueSubscription
	{
	public:
		::demo::MainWindowConstructor* __vwsnthis_0;

		__vwsnc2_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize__vl_reflection_description_IValueSubscription(::demo::MainWindowConstructor* __vwsnctorthis_0);

		::vl::Ptr<::IDemoService> __vwsn_bind_cache_0;
		::vl::Ptr<::vl::reflection::description::IEventHandler> __vwsn_bind_handler_0_0;
		bool __vwsn_bind_opened_ = false;
		bool __vwsn_bind_closed_ = false;
		void __vwsn_bind_activator_();
		void __vwsn_bind_callback_0_0();
		bool Open() override;
		bool Update() override;
		bool Close() override;
	};

	class __vwsnc3_Demo_demo_MainWindow__IDemoService : public ::vl::Object, public virtual ::IDemoService
	{
	public:
		__vwsnc3_Demo_demo_MainWindow__IDemoService();

		::vl::WString __vwsn_prop_Name;
		::vl::WString GetName() override;
		void SetName(const ::vl::WString& __vwsn_value_) override;
	};
}

#if defined( _MSC_VER)
#pragma warning(pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#endif
