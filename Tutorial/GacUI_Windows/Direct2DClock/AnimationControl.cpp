#define GAC_HEADER_USE_NAMESPACE
#include "AnimationControl.h"
#include <GacUI.Windows.h>

namespace demo
{
	struct AnimationControlMembers
	{
		DateTime						lastUpdateTime;

		ComPtr<ID2D1SolidColorBrush>	borderBrush;
		ComPtr<ID2D1SolidColorBrush>	hourBrush;
		ComPtr<ID2D1SolidColorBrush>	minuteBrush;
		ComPtr<ID2D1SolidColorBrush>	secondBrush;
	};

	void AnimationControl::GlobalTimer()
	{
		auto time = DateTime::LocalTime();
		if (time.osMilliseconds - members->lastUpdateTime.osMilliseconds >= 100)
		{
			members->lastUpdateTime = time;
			if (auto renderer = element->GetRenderer())
			{
				this->GetRelatedControlHost()->GetGraphicsHost()->RequestRender();
			}
		}
	}

	void AnimationControl::OnBeforeRenderTargetChanged(GuiGraphicsComposition* sender, D2DEventArgs& arguments)
	{
		members->borderBrush = nullptr;
		members->hourBrush = nullptr;
		members->minuteBrush = nullptr;
		members->secondBrush = nullptr;
	}

	void AnimationControl::OnAfterRenderTargetChanged(GuiGraphicsComposition* sender, D2DEventArgs& arguments)
	{
		if (!arguments.rt) return;
		{
			ID2D1SolidColorBrush* brush = nullptr;
			arguments.rt->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f), &brush);
			members->borderBrush = brush;
		}
		{
			ID2D1SolidColorBrush* brush = nullptr;
			arguments.rt->CreateSolidColorBrush(D2D1::ColorF(0.0f, 1.0f, 1.0f), &brush);
			members->hourBrush = brush;
		}
		{
			ID2D1SolidColorBrush* brush = nullptr;
			arguments.rt->CreateSolidColorBrush(D2D1::ColorF(0.0f, 1.0f, 0.0f), &brush);
			members->minuteBrush = brush;
		}
		{
			ID2D1SolidColorBrush* brush = nullptr;
			arguments.rt->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 0.0f), &brush);
			members->secondBrush = brush;
		}
	}

	void AnimationControl::OnRendering(GuiGraphicsComposition* sender, D2DEventArgs& arguments)
	{
		auto rt = arguments.rt;
		if (!rt) return;
		vint cx = arguments.bounds.Left() + arguments.bounds.Width() / 2;
		vint cy = arguments.bounds.Top() + arguments.bounds.Height() / 2;

		rt->DrawEllipse(D2D1::Ellipse(D2D1::Point2F((FLOAT)cx, (FLOAT)cy), 160, 160), members->borderBrush.Obj());
		for (vint i = 0; i < 12; i++)
		{
			auto s = sin(i * 3.14 / 6);
			auto c = cos(i * 3.14 / 6);
			rt->DrawLine(D2D1::Point2F((FLOAT)(cx + c * 150), (FLOAT)(cy + s * 150)), D2D1::Point2F((FLOAT)(cx + c * 160), (FLOAT)(cy + s * 160)), members->borderBrush.Obj());
		}

		auto time = DateTime::LocalTime();
		{
			auto d = ((time.hour + time.minute / 60.f + time.second / 3600.f) / 6.f - 0.5) * 3.14;
			auto s = sin(d);
			auto c = cos(d);
			rt->DrawLine(D2D1::Point2F((FLOAT)cx, (FLOAT)cy), D2D1::Point2F((FLOAT)(cx + c * 90), (FLOAT)(cy + s * 90)), members->hourBrush.Obj());
		}
		{
			auto d = ((time.minute + time.second / 60.f) / 30.f - 0.5) * 3.14;
			auto s = sin(d);
			auto c = cos(d);
			rt->DrawLine(D2D1::Point2F((FLOAT)cx, (FLOAT)cy), D2D1::Point2F((FLOAT)(cx + c * 110), (FLOAT)(cy + s * 110)), members->minuteBrush.Obj());
		}
		{
			auto d = (time.second / 30.f - 0.5) * 3.14;
			auto s = sin(d);
			auto c = cos(d);
			rt->DrawLine(D2D1::Point2F((FLOAT)cx, (FLOAT)cy), D2D1::Point2F((FLOAT)(cx + c * 130), (FLOAT)(cy + s * 130)), members->secondBrush.Obj());
		}
	}

	AnimationControl::AnimationControl()
		:GuiControl(theme::ThemeName::CustomControl)
		, members(Ptr(new AnimationControlMembers))
	{
		element = D2DElement::Create();
		element->BeforeRenderTargetChanged.AttachMethod(this, &AnimationControl::OnBeforeRenderTargetChanged);
		element->AfterRenderTargetChanged.AttachMethod(this, &AnimationControl::OnAfterRenderTargetChanged);
		element->Rendering.AttachMethod(this, &AnimationControl::OnRendering);
		{
			auto bounds = new GuiBoundsComposition();
			bounds->SetAlignmentToParent(Margin(0, 0, 0, 0));
			bounds->SetOwnedElement(Ptr(element));
			GetContainerComposition()->AddChild(bounds);
		}

		members->lastUpdateTime = DateTime::LocalTime();

		GetCurrentController()->CallbackService()->InstallListener(this);
	}

	AnimationControl::~AnimationControl()
	{
		GetCurrentController()->CallbackService()->UninstallListener(this);
	}
}