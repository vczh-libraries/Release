#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/EditorRibbon.h"

using namespace vl::collections;
using namespace vl::stream;
using namespace vl::reflection::description;
using namespace demo;

void GuiMain()
{
	{
		FileStream fileStream(L"../UIRes/DocumentEditor.bin", FileStream::ReadOnly);
		GetResourceManager()->LoadResourceOrPending(fileStream);
	}
	{
		FileStream fileStream(L"../UIRes/DocumentEditorRibbon.bin", FileStream::ReadOnly);
		GetResourceManager()->LoadResourceOrPending(fileStream);
	}
	demo::MainWindow window;
	window.ForceCalculateSizeImmediately();
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}