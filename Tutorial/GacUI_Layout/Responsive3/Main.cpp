#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/Demo.h"

void GuiMain()
{
	{
		auto resourceFolder = filesystem::FilePath(GetApplication()->GetExecutableFolder()).GetFolder();
#if defined VCZH_64
		resourceFolder = resourceFolder.GetFolder();
#endif
		auto resourcePath = resourceFolder / L"UIRes/Responsive3.bin";
		stream::FileStream fileStream(resourcePath.GetFullPath(), stream::FileStream::ReadOnly);
		GetResourceManager()->LoadResourceOrPending(fileStream);
	}
	demo::EasyLayoutResponsiveWindow window;
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}
