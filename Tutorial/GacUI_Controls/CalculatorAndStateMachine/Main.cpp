#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/Demo.h"

using namespace vl::collections;
using namespace vl::stream;

void GuiMain()
{
	{
		FileStream fileStream(L"../UIRes/CalculatorAndStateMachine.bin", FileStream::ReadOnly);
		GetResourceManager()->LoadResourceOrPending(fileStream);
	}
	demo::MainWindow window(Ptr(new demo::Calculator));
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}