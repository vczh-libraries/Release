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

namespace demo
{
	class MainWindowConstructor;
	class MainWindow;

	class MainWindowConstructor : public ::vl::Object, public ::vl::reflection::Description<MainWindowConstructor>
	{
#ifdef VCZH_DESCRIPTABLEOBJECT_WITH_METADATA
		friend struct ::vl::reflection::description::CustomTypeDescriptorSelector<MainWindowConstructor>;
#endif
	protected:
		::vl::presentation::controls::GuiSelectableButton::MutexGroupController* radioGroup;
		::demo::MainWindow* __vwsn_precompile_0;
		::vl::presentation::controls::GuiTab* __vwsn_precompile_1;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_2;
		::vl::presentation::controls::GuiTabPage* __vwsn_precompile_3;
		::vl::presentation::compositions::GuiTableComposition* __vwsn_precompile_4;
		::vl::presentation::compositions::GuiCellComposition* __vwsn_precompile_5;
		::vl::presentation::controls::GuiControl* __vwsn_precompile_6;
		::vl::presentation::compositions::GuiStackComposition* __vwsn_precompile_7;
		::vl::presentation::compositions::GuiStackItemComposition* __vwsn_precompile_8;
		::vl::presentation::controls::GuiButton* __vwsn_precompile_9;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_10;
		::vl::presentation::compositions::GuiStackItemComposition* __vwsn_precompile_11;
		::vl::presentation::controls::GuiButton* __vwsn_precompile_12;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_13;
		::vl::presentation::compositions::GuiStackItemComposition* __vwsn_precompile_14;
		::vl::presentation::controls::GuiButton* __vwsn_precompile_15;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_16;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_17;
		::vl::presentation::compositions::GuiCellComposition* __vwsn_precompile_18;
		::vl::presentation::controls::GuiControl* __vwsn_precompile_19;
		::vl::presentation::compositions::GuiStackComposition* __vwsn_precompile_20;
		::vl::presentation::compositions::GuiStackItemComposition* __vwsn_precompile_21;
		::vl::presentation::controls::GuiSelectableButton* __vwsn_precompile_22;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_23;
		::vl::presentation::compositions::GuiStackItemComposition* __vwsn_precompile_24;
		::vl::presentation::controls::GuiSelectableButton* __vwsn_precompile_25;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_26;
		::vl::presentation::compositions::GuiStackItemComposition* __vwsn_precompile_27;
		::vl::presentation::controls::GuiSelectableButton* __vwsn_precompile_28;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_29;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_30;
		::vl::presentation::compositions::GuiCellComposition* __vwsn_precompile_31;
		::vl::presentation::controls::GuiControl* __vwsn_precompile_32;
		::vl::presentation::compositions::GuiStackComposition* __vwsn_precompile_33;
		::vl::presentation::compositions::GuiStackItemComposition* __vwsn_precompile_34;
		::vl::presentation::controls::GuiSelectableButton* __vwsn_precompile_35;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_36;
		::vl::presentation::compositions::GuiStackItemComposition* __vwsn_precompile_37;
		::vl::presentation::controls::GuiSelectableButton* __vwsn_precompile_38;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_39;
		::vl::presentation::compositions::GuiStackItemComposition* __vwsn_precompile_40;
		::vl::presentation::controls::GuiSelectableButton* __vwsn_precompile_41;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_42;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_43;
		::vl::presentation::controls::GuiTabPage* __vwsn_precompile_44;
		::vl::presentation::controls::GuiScrollContainer* __vwsn_precompile_45;
		::vl::presentation::compositions::GuiTableComposition* __vwsn_precompile_46;
		::vl::presentation::compositions::GuiCellComposition* __vwsn_precompile_47;
		::vl::presentation::controls::GuiButton* __vwsn_precompile_48;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_49;
		::vl::presentation::compositions::GuiCellComposition* __vwsn_precompile_50;
		::vl::presentation::controls::GuiButton* __vwsn_precompile_51;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_52;
		::vl::presentation::compositions::GuiCellComposition* __vwsn_precompile_53;
		::vl::presentation::controls::GuiButton* __vwsn_precompile_54;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_55;
		::vl::presentation::compositions::GuiCellComposition* __vwsn_precompile_56;
		::vl::presentation::controls::GuiButton* __vwsn_precompile_57;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_58;
		::vl::presentation::compositions::GuiCellComposition* __vwsn_precompile_59;
		::vl::presentation::controls::GuiButton* __vwsn_precompile_60;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_61;
		::vl::presentation::compositions::GuiCellComposition* __vwsn_precompile_62;
		::vl::presentation::controls::GuiButton* __vwsn_precompile_63;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_64;
		::vl::presentation::compositions::GuiCellComposition* __vwsn_precompile_65;
		::vl::presentation::controls::GuiButton* __vwsn_precompile_66;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_67;
		::vl::presentation::compositions::GuiCellComposition* __vwsn_precompile_68;
		::vl::presentation::controls::GuiButton* __vwsn_precompile_69;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_70;
		::vl::presentation::compositions::GuiCellComposition* __vwsn_precompile_71;
		::vl::presentation::controls::GuiButton* __vwsn_precompile_72;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_73;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_74;
		::vl::presentation::compositions::GuiGraphicsComposition* __vwsn_precompile_75;
		void __vwsn_demo_MainWindow_Initialize(::demo::MainWindow* __vwsn_this_);
	public:
		MainWindowConstructor();
	};

	class MainWindow : public ::vl::presentation::controls::GuiWindow, public ::demo::MainWindowConstructor, public ::vl::reflection::Description<MainWindow>
	{
		friend class ::demo::MainWindowConstructor;
#ifdef VCZH_DESCRIPTABLEOBJECT_WITH_METADATA
		friend struct ::vl::reflection::description::CustomTypeDescriptorSelector<MainWindow>;
#endif
	public:
		MainWindow();
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
}

#if defined( _MSC_VER)
#pragma warning(pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#endif
