#ifndef VCZH_TUTORIAL_TOUCHING
#define VCZH_TUTORIAL_TOUCHING

#include <GacUI.h>

namespace demo
{
	// Keep the attachment alive while drawing is needed. Destruction detaches all handlers.
	// Data: centerX,centerY,axisX,axisY,count followed by count triples of pointId,x,y.
	// The axis is a complex rotation/uniform-scale transform of a 160 by 100 rectangle.
	extern vl::Ptr<vl::Object> AttachTouchingElement(vl::Ptr<vl::presentation::elements::GuiRawElementBase> element);
}

#endif
