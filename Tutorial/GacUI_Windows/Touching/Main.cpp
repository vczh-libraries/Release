#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/Demo.h"
#include "Touching.h"

void GuiMain()
{
	{
		auto resourceFolder = filesystem::FilePath(GetApplication()->GetExecutableFolder()).GetFolder();
#if defined VCZH_64
		resourceFolder = resourceFolder.GetFolder();
#endif
		auto resourcePath = resourceFolder / L"UIRes/Touching.bin";
		stream::FileStream fileStream(resourcePath.GetFullPath(), stream::FileStream::ReadOnly);
		GetResourceManager()->LoadResourceOrPending(fileStream);
	}
	demo::TouchingWindow window;
	auto touchingAttachment = demo::AttachTouchingElement(window.GetTouchingElement());
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}
