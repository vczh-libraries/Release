#define GAC_HEADER_USE_NAMESPACE
#include <GacUIReflection.h>

using namespace vl::collections;
using namespace vl::stream;
using namespace vl::reflection::description;

void GuiMain()
{
	{
#ifdef VCZH_64
		FileStream fileStream(L"../UIRes/Xml.bin.x64", FileStream::ReadOnly);
#else
		FileStream fileStream(L"../UIRes/Xml.bin.x86", FileStream::ReadOnly);
#endif
		GetResourceManager()->LoadResourceOrPending(fileStream, GuiResourceUsage::InstanceClass);
	}

	auto window = UnboxValue<GuiWindow*>(Value::Create(L"helloworld::MainWindow"));
	window->MoveToScreenCenter();
	GetApplication()->Run(window);
	delete window;
}