#define GAC_HEADER_USE_NAMESPACE
#include "ResDerived/Source/ResDerived.h"

using namespace vl::collections;
using namespace vl::stream;

void GuiMain()
{
	{
		FileStream fileStream(L"../UIRes/Misc_ImportFolder_ResBase.bin", FileStream::ReadOnly);
		GetResourceManager()->LoadResourceOrPending(fileStream);
	}
	{
		FileStream fileStream(L"../UIRes/Misc_ImportFolder_Derived.bin", FileStream::ReadOnly);
		GetResourceManager()->LoadResourceOrPending(fileStream);
	}
	demo::MainWindow window;
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}