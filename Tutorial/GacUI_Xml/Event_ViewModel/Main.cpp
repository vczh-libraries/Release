#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/Demo.h"
#include <Windows.h>

using namespace vl::collections;
using namespace vl::stream;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int CmdShow)
{
	return SetupWindowsDirect2DRenderer();
}

class ViewModelImpl : public Object, public virtual demo::IViewModel
{
public:
	vint32_t Add(vint32_t a, vint32_t b)override
	{
		return a + b;
	}

	WString Error()override
	{
		return L"<Error>";
	}
};

void GuiMain()
{
	{
		FileStream fileStream(L"../UIRes/Event_ViewModel.bin", FileStream::ReadOnly);
		auto resource = GuiResource::LoadPrecompiledBinary(fileStream);
		GetResourceManager()->SetResource(L"Resource", resource);
	}
	demo::MainWindow window(new ViewModelImpl);
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}