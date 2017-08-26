#include "UI/FullControlTest/Source/Demo.h"

using namespace vl;
using namespace vl::collections;
using namespace vl::stream;
using namespace vl::reflection::description;
using namespace vl::presentation;
using namespace vl::presentation::templates;
using namespace vl::presentation::elements;
using namespace vl::presentation::controls;

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

void GuiMain()
{
	{
		FileStream fileStream(L"../UIRes/BlackSkin.bin", FileStream::ReadOnly);
		auto resource = GuiResource::LoadPrecompiledBinary(fileStream);
		GetResourceManager()->SetResource(L"Resource", resource);
	}
	{
		demo::MainWindow window;
		window.ForceCalculateSizeImmediately();
		window.MoveToScreenCenter();
		GetApplication()->Run(&window);
	}
}