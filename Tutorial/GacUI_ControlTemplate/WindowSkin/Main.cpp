#include "UI/Source/Demo.h"

using namespace vl;
using namespace vl::stream;
using namespace vl::presentation;
using namespace vl::presentation::controls;

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

void GuiMain()
{
	{
		FileStream fileStream(L"../UIRes/WindowSkin.bin", FileStream::ReadOnly);
		GetResourceManager()->LoadResourceOrPending(fileStream);
	}
	{
		demo::MainWindow window;
		window.ForceCalculateSizeImmediately();
		window.MoveToScreenCenter();
		GetApplication()->Run(&window);
	}
}