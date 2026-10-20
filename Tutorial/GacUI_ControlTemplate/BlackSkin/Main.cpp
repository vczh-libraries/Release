#include "UI/FullControlTest/Source/Demo.h"
#if defined VCZH_MSVC
#include "FullControlTestRawElement.h"
#endif

using namespace vl;
using namespace vl::stream;
using namespace vl::presentation;
using namespace vl::presentation::controls;

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

void GuiMain()
{
	{
		FileStream fileStream(L"../UIRes/BlackSkin.bin", FileStream::ReadOnly);
		GetResourceManager()->LoadResourceOrPending(fileStream);
	}
	{
		demo::MainWindow window;
#if defined VCZH_MSVC
		auto rawClockAttachment = demo::AttachFullControlTestRawElement(window.GetClockElement());
		auto touchingAttachment = demo::AttachFullControlTestTouchingElement(window.GetTouchingElement());
#endif
		window.ForceCalculateSizeImmediately();
		window.MoveToScreenCenter();
		GetApplication()->Run(&window);
	}
}
