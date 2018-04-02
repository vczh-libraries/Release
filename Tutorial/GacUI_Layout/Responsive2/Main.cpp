#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/Demo.h"
#include <Windows.h>

using namespace vl::collections;
using namespace vl::stream;

void GuiMain()
{
	{
		FileStream fileStream(L"../UIRes/Responsive2.bin", FileStream::ReadOnly);
		auto resource = GuiResource::LoadPrecompiledBinary(fileStream);
		GetResourceManager()->SetResource(L"Resource", resource);
	}
	demo::MainWindow window;
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}