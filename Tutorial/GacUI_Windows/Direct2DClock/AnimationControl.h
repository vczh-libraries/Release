#pragma once

#include <GacUI.h>

namespace vl
{
	namespace presentation
	{
		namespace elements
		{
			struct GuiDirect2DElementEventArgs;
			class GuiDirect2DElement;
		}
	}
}

namespace demo
{
	struct AnimationControlMembers;

	class AnimationControl
		: public vl::presentation::controls::GuiControl
		, protected vl::presentation::INativeControllerListener
	{
		using D2DElement = vl::presentation::elements::GuiDirect2DElement;
		using D2DEventArgs = vl::presentation::elements::GuiDirect2DElementEventArgs;
		using GuiGraphicsComposition = vl::presentation::compositions::GuiGraphicsComposition;

	protected:
		vl::Ptr<AnimationControlMembers>	members;
		D2DElement*							element;

		void								GlobalTimer()override;
		void								OnBeforeRenderTargetChanged(GuiGraphicsComposition* sender, D2DEventArgs& arguments);
		void								OnAfterRenderTargetChanged(GuiGraphicsComposition* sender, D2DEventArgs& arguments);
		void								OnRendering(GuiGraphicsComposition* sender, D2DEventArgs& arguments);
	public:
		AnimationControl();
		~AnimationControl();
	};
}