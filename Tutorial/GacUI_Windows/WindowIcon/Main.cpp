#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/Demo.h"
#include <GacUI.Windows.h>
#include "resource.h"

using namespace vl::collections;
using namespace vl::stream;
using namespace vl::reflection::description;
using namespace demo;

/*
The code has to run before calling SetupWindowsDirect2DRenderer
But I am lazy and I don't want to create another GacUILite without WinMain
So I just do this
*/
class Initialize
{
public:
	Initialize()
	{
		windows::SetWindowDefaultIcon(MAINICON);
	}
} initialize;

void GuiMain()
{
	{
		FileStream fileStream(L"../UIRes/WindowIcon.bin", FileStream::ReadOnly);
		GetResourceManager()->LoadResourceOrPending(fileStream);
	}
	MainWindow window;
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}