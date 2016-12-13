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
	WString GetMessageFromName(WString name)override
	{
		return L"Hi, " + name + L"! How are you?";
	}
};

void GuiMain()
{
	{
		List<WString> errors;
		FileStream fileStream(L"../UIRes/Binding_ViewModel.bin", FileStream::ReadOnly);
		auto resource = GuiResource::LoadPrecompiledBinary(fileStream, errors);
		GetResourceManager()->SetResource(L"Resource", resource);
	}
	demo::MainWindow window(new ViewModelImpl);
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}