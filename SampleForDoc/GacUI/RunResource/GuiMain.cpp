#include <GacUIReflection.h>
#include <GacUIWindows.h>
#include "resource.h"

using namespace vl;
using namespace vl::filesystem;
using namespace vl::reflection::description;
using namespace vl::presentation;
using namespace vl::presentation::controls;
using namespace vl::presentation::compositions;

/*
The code has to run before calling SetupWindowsDirect2DRenderer
But I am lazy and I don't want to create another GacUILite without WinMain
So I just do this
*/
class Initialize
{
public:
	Initialize()
	{
		windows::SetWindowDefaultIcon(MAINICON);
	}
} initialize;

void GuiMain()
{
	{
		// expected to executed like "RunResource.exe kb-elements"
		WString resourceName;
		{
			int argc = 0;
			LPWSTR* argv = CommandLineToArgvW(GetCommandLine(), &argc);
			CHECK_ERROR(argc == 2, L"Command line arguments are missing."); \
			resourceName = argv[1];
			LocalFree(argv);
		}
#ifdef VCZH_64
		FilePath resourcePath = FilePath(L"../UIRes/64bits") / (resourceName + L".bin");
#else
		FilePath resourcePath = FilePath(L"../UIRes/32bits") / (resourceName + L".bin");
#endif

		stream::FileStream resourceStream(resourcePath.GetFullPath(), stream::FileStream::ReadOnly);
		GetResourceManager()->LoadResourceOrPending(resourceStream, GuiResourceUsage::InstanceClass);
	}

	auto window = UnboxValue<GuiWindow*>(Value::Create(L"sample::MainWindow"));
	window->MoveToScreenCenter();
	GetApplication()->Run(window);
	SafeDeleteControl(window);
}