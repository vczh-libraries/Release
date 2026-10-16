#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/Demo.h"
#include "RawClock.h"

using namespace demo;

void GuiMain()
{
	{
		auto resourceFolder = filesystem::FilePath(GetApplication()->GetExecutableFolder()).GetFolder();
#if defined VCZH_64
		resourceFolder = resourceFolder.GetFolder();
#endif
		auto resourcePath = resourceFolder / L"UIRes/RawClock.bin";
		stream::FileStream fileStream(resourcePath.GetFullPath(), stream::FileStream::ReadOnly);
		GetResourceManager()->LoadResourceOrPending(fileStream);
	}
	MainWindow window;
	auto clockAttachment = AttachRawClock(window.GetClockElement());
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}
