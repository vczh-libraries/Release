#include <GacUIReflection.h>
#include <Windows.h>

using namespace vl;
using namespace vl::filesystem;
using namespace vl::reflection::description;
using namespace vl::presentation;
using namespace vl::presentation::controls;
using namespace vl::presentation::compositions;

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