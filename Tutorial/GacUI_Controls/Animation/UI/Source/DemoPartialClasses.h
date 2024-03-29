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
	struct __vwsnf10_Demo_demo_MainWindow_BallAnimation_;
	struct __vwsnf11_Demo_demo_MainWindow_BallAnimationWithDelay_;
	struct __vwsnf12_Demo_demo_MainWindow_WaitingAnimation_;
	struct __vwsnf2_Demo_demo_ColorAnimation_CreateAnimation_;
	struct __vwsnf3_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_;
	struct __vwsnf4_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_;
	struct __vwsnf5_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_;
	struct __vwsnf6_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_;
	struct __vwsnf7_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_;
	struct __vwsnf8_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_;
	struct __vwsnf9_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_;
	struct __vwsno1_Demo_demo_ColorAnimation_;
	class __vwsnc1_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize__vl_reflection_description_IValueSubscription;
	class __vwsnc2_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize__vl_reflection_description_IValueSubscription;
	class __vwsnc3_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize__vl_reflection_description_IValueSubscription;
	class __vwsnc4_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize__vl_reflection_description_IValueSubscription;
	class __vwsnc5_Demo_demo_MainWindow_BallAnimationWithDelay___vl_reflection_description_ICoroutine;
	class __vwsnc6_Demo_demo_MainWindow_WaitingAnimation___vl_reflection_description_ICoroutine;
}

namespace demo
{
	class ColorAnimation;
	class ColorDef;
	class MainWindowConstructor;
	class MainWindow;

	class ColorAnimation : public ::vl::Object, public ::vl::reflection::Description<ColorAnimation>
	{
		friend struct ::vl_workflow_global::__vwsnf2_Demo_demo_ColorAnimation_CreateAnimation_;
		friend struct ::vl_workflow_global::__vwsno1_Demo_demo_ColorAnimation_;
#ifdef VCZH_DESCRIPTABLEOBJECT_WITH_METADATA
		friend struct ::vl::reflection::description::CustomTypeDescriptorSelector<ColorAnimation>;
#endif
	public:
		::vl::Ptr<::demo::ColorDef> __vwsn_prop_Begin;
		::vl::Ptr<::demo::ColorDef> GetBegin();
		void SetBegin(::vl::Ptr<::demo::ColorDef> __vwsn_value_);
		::vl::Event<void()> BeginChanged;
		::vl::Ptr<::demo::ColorDef> __vwsn_prop_End;
		::vl::Ptr<::demo::ColorDef> GetEnd();
		void SetEnd(::vl::Ptr<::demo::ColorDef> __vwsn_value_);
		::vl::Event<void()> EndChanged;
		::vl::Ptr<::demo::ColorDef> __vwsn_prop_Current;
		::vl::Ptr<::demo::ColorDef> GetCurrent();
		void SetCurrent(::vl::Ptr<::demo::ColorDef> __vwsn_value_);
		::vl::Event<void()> CurrentChanged;
	private:
		::vl::Func<double(double)> __vwsn_ani_int_;
		::vl::Func<double(double)> __vwsn_ani_int_Thickness;
	public:
		double GetTimeScale(::vl::Ptr<::demo::ColorDef> __vwsn_ani_begin, ::vl::Ptr<::demo::ColorDef> __vwsn_ani_end, ::vl::Ptr<::demo::ColorDef> __vwsn_ani_current);
		void Interpolate(::vl::Ptr<::demo::ColorDef> __vwsn_ani_begin, ::vl::Ptr<::demo::ColorDef> __vwsn_ani_end, ::vl::Ptr<::demo::ColorDef> __vwsn_ani_current, double __vwsn_ani_ratio);
		void Interpolate(double __vwsn_ani_ratio);
		::vl::Ptr<::vl::presentation::controls::IGuiAnimation> CreateAnimation(::vl::Ptr<::demo::ColorDef> __vwsn_ani_target, ::vl::vuint64_t __vwsn_ani_time);
		ColorAnimation(::vl::Ptr<::demo::ColorDef> __vwsn_ani_current);
	};

	class ColorDef : public ::vl::Object, public ::vl::reflection::Description<ColorDef>
	{
#ifdef VCZH_DESCRIPTABLEOBJECT_WITH_METADATA
		friend struct ::vl::reflection::description::CustomTypeDescriptorSelector<ColorDef>;
#endif
	private:
		::vl::presentation::Color __vwsn_prop_Top;
	public:
		::vl::presentation::Color GetTop();
		void SetTop(::vl::presentation::Color __vwsn_value_);
		::vl::Event<void()> TopChanged;
	private:
		::vl::presentation::Color __vwsn_prop_Bottom;
	public:
		::vl::presentation::Color GetBottom();
		void SetBottom(::vl::presentation::Color __vwsn_value_);
		::vl::Event<void()> BottomChanged;
	private:
		::vl::presentation::Color __vwsn_prop_Shadow;
	public:
		::vl::presentation::Color GetShadow();
		void SetShadow(::vl::presentation::Color __vwsn_value_);
		::vl::Event<void()> ShadowChanged;
	private:
		::vl::vint __vwsn_prop_Thickness;
	public:
		::vl::vint GetThickness();
		void SetThickness(::vl::vint __vwsn_value_);
		::vl::Event<void()> ThicknessChanged;
		static ::vl::Ptr<::demo::ColorDef> Dark();
		static ::vl::Ptr<::demo::ColorDef> Light();
		static ::vl::Ptr<::demo::ColorDef> Sink();
		ColorDef();
	};

	class MainWindowConstructor : public ::vl::Object, public ::vl::reflection::Description<MainWindowConstructor>
	{
		friend class ::vl_workflow_global::__vwsnc1_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize__vl_reflection_description_IValueSubscription;
		friend class ::vl_workflow_global::__vwsnc2_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize__vl_reflection_description_IValueSubscription;
		friend class ::vl_workflow_global::__vwsnc3_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize__vl_reflection_description_IValueSubscription;
		friend class ::vl_workflow_global::__vwsnc4_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize__vl_reflection_description_IValueSubscription;
		friend struct ::vl_workflow_global::__vwsnf3_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_;
		friend struct ::vl_workflow_global::__vwsnf4_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_;
		friend struct ::vl_workflow_global::__vwsnf5_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_;
		friend struct ::vl_workflow_global::__vwsnf6_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_;
		friend struct ::vl_workflow_global::__vwsnf7_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_;
		friend struct ::vl_workflow_global::__vwsnf8_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_;
		friend struct ::vl_workflow_global::__vwsnf9_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_;
#ifdef VCZH_DESCRIPTABLEOBJECT_WITH_METADATA
		friend struct ::vl::reflection::description::CustomTypeDescriptorSelector<MainWindowConstructor>;
#endif
	protected:
		::demo::MainWindow* self;
		::vl::presentation::compositions::GuiBoundsComposition* animationBackground;
		::vl::presentation::controls::GuiTab* __vwsn_precompile_0;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_1;
		::vl::presentation::controls::GuiTabPage* __vwsn_precompile_2;
		::vl::presentation::compositions::GuiTableComposition* __vwsn_precompile_3;
		::vl::presentation::compositions::GuiCellComposition* __vwsn_precompile_4;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_5;
		::vl::Ptr<::vl::presentation::elements::GuiGradientBackgroundElement> __vwsn_precompile_6;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_7;
		::vl::Ptr<::vl::presentation::elements::GuiInnerShadowElement> __vwsn_precompile_8;
		::vl::presentation::compositions::GuiCellComposition* __vwsn_precompile_9;
		::vl::presentation::controls::GuiButton* __vwsn_precompile_10;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_11;
		::vl::presentation::compositions::GuiCellComposition* __vwsn_precompile_12;
		::vl::presentation::controls::GuiButton* __vwsn_precompile_13;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_14;
		::vl::presentation::compositions::GuiCellComposition* __vwsn_precompile_15;
		::vl::presentation::controls::GuiButton* __vwsn_precompile_16;
		::vl::presentation::compositions::GuiBoundsComposition* __vwsn_precompile_17;
		::vl::presentation::controls::GuiTabPage* __vwsn_precompile_18;
		::vl::Ptr<::vl::presentation::elements::GuiSolidBackgroundElement> __vwsn_precompile_19;
		::vl::presentation::compositions::GuiGraphicsComposition* __vwsn_precompile_20;
		void __vwsn_demo_MainWindow_Initialize(::demo::MainWindow* __vwsn_this_);
	public:
		MainWindowConstructor();
	};

	class MainWindow : public ::vl::presentation::controls::GuiWindow, public ::demo::MainWindowConstructor, public ::vl::reflection::Description<MainWindow>
	{
		friend class ::vl_workflow_global::__vwsnc5_Demo_demo_MainWindow_BallAnimationWithDelay___vl_reflection_description_ICoroutine;
		friend class ::vl_workflow_global::__vwsnc6_Demo_demo_MainWindow_WaitingAnimation___vl_reflection_description_ICoroutine;
		friend struct ::vl_workflow_global::__vwsnf10_Demo_demo_MainWindow_BallAnimation_;
		friend struct ::vl_workflow_global::__vwsnf11_Demo_demo_MainWindow_BallAnimationWithDelay_;
		friend struct ::vl_workflow_global::__vwsnf12_Demo_demo_MainWindow_WaitingAnimation_;
		friend class ::demo::MainWindowConstructor;
		friend class ::vl_workflow_global::__vwsnc1_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize__vl_reflection_description_IValueSubscription;
		friend class ::vl_workflow_global::__vwsnc2_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize__vl_reflection_description_IValueSubscription;
		friend class ::vl_workflow_global::__vwsnc3_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize__vl_reflection_description_IValueSubscription;
		friend class ::vl_workflow_global::__vwsnc4_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize__vl_reflection_description_IValueSubscription;
		friend struct ::vl_workflow_global::__vwsnf3_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_;
		friend struct ::vl_workflow_global::__vwsnf4_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_;
		friend struct ::vl_workflow_global::__vwsnf5_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_;
		friend struct ::vl_workflow_global::__vwsnf6_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_;
		friend struct ::vl_workflow_global::__vwsnf7_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_;
		friend struct ::vl_workflow_global::__vwsnf8_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_;
		friend struct ::vl_workflow_global::__vwsnf9_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_;
#ifdef VCZH_DESCRIPTABLEOBJECT_WITH_METADATA
		friend struct ::vl::reflection::description::CustomTypeDescriptorSelector<MainWindow>;
#endif
	private:
		static ::vl::Ptr<::vl::presentation::controls::IGuiAnimation> BallAnimation(::vl::presentation::compositions::GuiBoundsComposition* container, ::vl::presentation::compositions::GuiBoundsComposition* ball);
		static ::vl::Ptr<::vl::presentation::controls::IGuiAnimation> BallAnimationWithDelay(::vl::presentation::compositions::GuiBoundsComposition* container, ::vl::presentation::compositions::GuiBoundsComposition* ball, ::vl::vint delay);
		static ::vl::Ptr<::vl::presentation::controls::IGuiAnimation> WaitingAnimation(::vl::presentation::compositions::GuiBoundsComposition* container);
		::vl::Ptr<::demo::ColorAnimation> gradientColorDef;
		::vl::Ptr<::vl::presentation::controls::IGuiAnimation> lastGradientAnimation;
	public:
		void PerformGradientAnimation(::vl::Ptr<::demo::ColorDef> target);
		::vl::vint counter;
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

		double F(double x);
		double G(double x);

		static Demo& Instance();
	};

/***********************************************************************
Closures
***********************************************************************/

	struct __vwsnf10_Demo_demo_MainWindow_BallAnimation_
	{
		::vl::presentation::compositions::GuiBoundsComposition* ball;
		::vl::presentation::compositions::GuiBoundsComposition* container;

		__vwsnf10_Demo_demo_MainWindow_BallAnimation_(::vl::presentation::compositions::GuiBoundsComposition* __vwsnctor_ball, ::vl::presentation::compositions::GuiBoundsComposition* __vwsnctor_container);

		void operator()(::vl::vuint64_t time) const;
	};

	struct __vwsnf11_Demo_demo_MainWindow_BallAnimationWithDelay_
	{
		::vl::presentation::compositions::GuiBoundsComposition* ball;
		::vl::presentation::compositions::GuiBoundsComposition* container;
		::vl::vint delay;

		__vwsnf11_Demo_demo_MainWindow_BallAnimationWithDelay_(::vl::presentation::compositions::GuiBoundsComposition* __vwsnctor_ball, ::vl::presentation::compositions::GuiBoundsComposition* __vwsnctor_container, ::vl::vint __vwsnctor_delay);

		::vl::Ptr<::vl::reflection::description::ICoroutine> operator()(::vl::presentation::controls::IGuiAnimationCoroutine::IImpl* __vwsn_co_impl_) const;
	};

	struct __vwsnf12_Demo_demo_MainWindow_WaitingAnimation_
	{
		::vl::presentation::compositions::GuiBoundsComposition* container;

		__vwsnf12_Demo_demo_MainWindow_WaitingAnimation_(::vl::presentation::compositions::GuiBoundsComposition* __vwsnctor_container);

		::vl::Ptr<::vl::reflection::description::ICoroutine> operator()(::vl::presentation::controls::IGuiAnimationCoroutine::IImpl* __vwsn_co_impl_) const;
	};

	struct __vwsnf2_Demo_demo_ColorAnimation_CreateAnimation_
	{
		::vl::vuint64_t __vwsn_ani_time;
		::demo::ColorAnimation* __vwsnthis_0;

		__vwsnf2_Demo_demo_ColorAnimation_CreateAnimation_(::vl::vuint64_t __vwsnctor___vwsn_ani_time, ::demo::ColorAnimation* __vwsnctorthis_0);

		void operator()(::vl::vuint64_t __vwsn_ani_currentTime) const;
	};

	struct __vwsnf3_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_
	{
		::demo::MainWindowConstructor* __vwsnthis_0;

		__vwsnf3_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_(::demo::MainWindowConstructor* __vwsnctorthis_0);

		void operator()(const ::vl::reflection::description::Value& __vwsn_value_) const;
	};

	struct __vwsnf4_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_
	{
		::demo::MainWindowConstructor* __vwsnthis_0;

		__vwsnf4_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_(::demo::MainWindowConstructor* __vwsnctorthis_0);

		void operator()(const ::vl::reflection::description::Value& __vwsn_value_) const;
	};

	struct __vwsnf5_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_
	{
		::demo::MainWindowConstructor* __vwsnthis_0;

		__vwsnf5_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_(::demo::MainWindowConstructor* __vwsnctorthis_0);

		void operator()(const ::vl::reflection::description::Value& __vwsn_value_) const;
	};

	struct __vwsnf6_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_
	{
		::demo::MainWindowConstructor* __vwsnthis_0;

		__vwsnf6_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_(::demo::MainWindowConstructor* __vwsnctorthis_0);

		void operator()(const ::vl::reflection::description::Value& __vwsn_value_) const;
	};

	struct __vwsnf7_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_
	{
		::demo::MainWindowConstructor* __vwsnthis_0;

		__vwsnf7_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_(::demo::MainWindowConstructor* __vwsnctorthis_0);

		void operator()(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments) const;
	};

	struct __vwsnf8_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_
	{
		::demo::MainWindowConstructor* __vwsnthis_0;

		__vwsnf8_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_(::demo::MainWindowConstructor* __vwsnctorthis_0);

		void operator()(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments) const;
	};

	struct __vwsnf9_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_
	{
		::demo::MainWindowConstructor* __vwsnthis_0;

		__vwsnf9_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_(::demo::MainWindowConstructor* __vwsnctorthis_0);

		void operator()(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments) const;
	};

	struct __vwsno1_Demo_demo_ColorAnimation_
	{
		__vwsno1_Demo_demo_ColorAnimation_();

		double operator()(double __vwsno_1) const;
	};

	class __vwsnc1_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize__vl_reflection_description_IValueSubscription : public ::vl::Object, public virtual ::vl::reflection::description::IValueSubscription
	{
	public:
		::demo::MainWindowConstructor* __vwsnthis_0;

		__vwsnc1_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize__vl_reflection_description_IValueSubscription(::demo::MainWindowConstructor* __vwsnctorthis_0);

		::vl::Ptr<::demo::ColorAnimation> __vwsn_bind_cache_0;
		::vl::Ptr<::demo::ColorDef> __vwsn_bind_cache_1;
		::vl::Ptr<::vl::reflection::description::IEventHandler> __vwsn_bind_handler_0_0;
		::vl::Ptr<::vl::reflection::description::IEventHandler> __vwsn_bind_handler_1_0;
		bool __vwsn_bind_opened_ = false;
		bool __vwsn_bind_closed_ = false;
		void __vwsn_bind_activator_();
		void __vwsn_bind_callback_0_0();
		void __vwsn_bind_callback_1_0();
		bool Open() override;
		bool Update() override;
		bool Close() override;
	};

	class __vwsnc2_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize__vl_reflection_description_IValueSubscription : public ::vl::Object, public virtual ::vl::reflection::description::IValueSubscription
	{
	public:
		::demo::MainWindowConstructor* __vwsnthis_0;

		__vwsnc2_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize__vl_reflection_description_IValueSubscription(::demo::MainWindowConstructor* __vwsnctorthis_0);

		::vl::Ptr<::demo::ColorAnimation> __vwsn_bind_cache_0;
		::vl::Ptr<::demo::ColorDef> __vwsn_bind_cache_1;
		::vl::Ptr<::vl::reflection::description::IEventHandler> __vwsn_bind_handler_0_0;
		::vl::Ptr<::vl::reflection::description::IEventHandler> __vwsn_bind_handler_1_0;
		bool __vwsn_bind_opened_ = false;
		bool __vwsn_bind_closed_ = false;
		void __vwsn_bind_activator_();
		void __vwsn_bind_callback_0_0();
		void __vwsn_bind_callback_1_0();
		bool Open() override;
		bool Update() override;
		bool Close() override;
	};

	class __vwsnc3_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize__vl_reflection_description_IValueSubscription : public ::vl::Object, public virtual ::vl::reflection::description::IValueSubscription
	{
	public:
		::demo::MainWindowConstructor* __vwsnthis_0;

		__vwsnc3_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize__vl_reflection_description_IValueSubscription(::demo::MainWindowConstructor* __vwsnctorthis_0);

		::vl::Ptr<::demo::ColorAnimation> __vwsn_bind_cache_0;
		::vl::Ptr<::demo::ColorDef> __vwsn_bind_cache_1;
		::vl::Ptr<::vl::reflection::description::IEventHandler> __vwsn_bind_handler_0_0;
		::vl::Ptr<::vl::reflection::description::IEventHandler> __vwsn_bind_handler_1_0;
		bool __vwsn_bind_opened_ = false;
		bool __vwsn_bind_closed_ = false;
		void __vwsn_bind_activator_();
		void __vwsn_bind_callback_0_0();
		void __vwsn_bind_callback_1_0();
		bool Open() override;
		bool Update() override;
		bool Close() override;
	};

	class __vwsnc4_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize__vl_reflection_description_IValueSubscription : public ::vl::Object, public virtual ::vl::reflection::description::IValueSubscription
	{
	public:
		::demo::MainWindowConstructor* __vwsnthis_0;

		__vwsnc4_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize__vl_reflection_description_IValueSubscription(::demo::MainWindowConstructor* __vwsnctorthis_0);

		::vl::Ptr<::demo::ColorAnimation> __vwsn_bind_cache_0;
		::vl::Ptr<::demo::ColorDef> __vwsn_bind_cache_1;
		::vl::Ptr<::vl::reflection::description::IEventHandler> __vwsn_bind_handler_0_0;
		::vl::Ptr<::vl::reflection::description::IEventHandler> __vwsn_bind_handler_1_0;
		bool __vwsn_bind_opened_ = false;
		bool __vwsn_bind_closed_ = false;
		void __vwsn_bind_activator_();
		void __vwsn_bind_callback_0_0();
		void __vwsn_bind_callback_1_0();
		bool Open() override;
		bool Update() override;
		bool Close() override;
	};

	class __vwsnc5_Demo_demo_MainWindow_BallAnimationWithDelay___vl_reflection_description_ICoroutine : public ::vl::Object, public virtual ::vl::reflection::description::ICoroutine
	{
	public:
		::vl::presentation::controls::IGuiAnimationCoroutine::IImpl* __vwsn_co_impl_;
		::vl::presentation::compositions::GuiBoundsComposition* ball;
		::vl::presentation::compositions::GuiBoundsComposition* container;
		::vl::vint delay;

		__vwsnc5_Demo_demo_MainWindow_BallAnimationWithDelay___vl_reflection_description_ICoroutine(::vl::presentation::controls::IGuiAnimationCoroutine::IImpl* __vwsnctor___vwsn_co_impl_, ::vl::presentation::compositions::GuiBoundsComposition* __vwsnctor_ball, ::vl::presentation::compositions::GuiBoundsComposition* __vwsnctor_container, ::vl::vint __vwsnctor_delay);

		::vl::vint __vwsn_co_state_ = 0;
		::vl::vint __vwsn_co_state_before_pause_ = 0;
		::vl::Ptr<::vl::reflection::description::IValueException> __vwsn_prop_Failure;
		::vl::Ptr<::vl::reflection::description::IValueException> GetFailure() override;
		void SetFailure(::vl::Ptr<::vl::reflection::description::IValueException> __vwsn_value_);
		::vl::reflection::description::CoroutineStatus __vwsn_prop_Status = static_cast<::vl::reflection::description::CoroutineStatus>(0);
		::vl::reflection::description::CoroutineStatus GetStatus() override;
		void SetStatus(::vl::reflection::description::CoroutineStatus __vwsn_value_);
		void Resume(bool __vwsn_raise_exception_, ::vl::Ptr<::vl::reflection::description::CoroutineResult> __vwsn_co_result_) override;
	};

	class __vwsnc6_Demo_demo_MainWindow_WaitingAnimation___vl_reflection_description_ICoroutine : public ::vl::Object, public virtual ::vl::reflection::description::ICoroutine
	{
	public:
		::vl::presentation::controls::IGuiAnimationCoroutine::IImpl* __vwsn_co_impl_;
		::vl::presentation::compositions::GuiBoundsComposition* container;

		__vwsnc6_Demo_demo_MainWindow_WaitingAnimation___vl_reflection_description_ICoroutine(::vl::presentation::controls::IGuiAnimationCoroutine::IImpl* __vwsnctor___vwsn_co_impl_, ::vl::presentation::compositions::GuiBoundsComposition* __vwsnctor_container);

		::vl::vint __vwsn_co0_for_begin_i = 0;
		::vl::vint __vwsn_co1_for_end_i = 0;
		::vl::vint __vwsn_co2_i = 0;
		::vl::Ptr<::vl::reflection::description::IValueList> __vwsn_co3_balls;
		::vl::vint __vwsn_co_state_ = 0;
		::vl::vint __vwsn_co_state_before_pause_ = 0;
		::vl::Ptr<::vl::reflection::description::IValueException> __vwsn_prop_Failure;
		::vl::Ptr<::vl::reflection::description::IValueException> GetFailure() override;
		void SetFailure(::vl::Ptr<::vl::reflection::description::IValueException> __vwsn_value_);
		::vl::reflection::description::CoroutineStatus __vwsn_prop_Status = static_cast<::vl::reflection::description::CoroutineStatus>(0);
		::vl::reflection::description::CoroutineStatus GetStatus() override;
		void SetStatus(::vl::reflection::description::CoroutineStatus __vwsn_value_);
		void Resume(bool __vwsn_raise_exception_, ::vl::Ptr<::vl::reflection::description::CoroutineResult> __vwsn_co_result_) override;
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
