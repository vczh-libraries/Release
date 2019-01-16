#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/Demo.h"
#include <GacUIWindows.h>
#include "resource.h"

using namespace vl::collections;
using namespace vl::stream;
using namespace vl::reflection::description;
using namespace demo;

void GuiMain()
{
	windows::SetWindowDefaultIcon(MAINICON);
	{
		FileStream fileStream(L"../UIRes/WindowIcon.bin", FileStream::ReadOnly);
		GetResourceManager()->LoadResourceOrPending(fileStream);
	}
	MainWindow window;
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}