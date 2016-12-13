#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/Demo.h"
#include <Windows.h>

using namespace vl::collections;
using namespace vl::stream;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int CmdShow)
{
	return SetupWindowsDirect2DRenderer();
}

class ViewModel : public Object, public virtual demo::IViewModel
{
public:
	void OpenUrl(WString url)override
	{
		ShellExecute(NULL, L"OPEN", url.Buffer(), NULL, NULL, SW_MAXIMIZE);
	}
};

void GuiMain()
{
	{
		List<WString> errors;
		FileStream fileStream(L"../UIRes/RichTextEmbedding.bin", FileStream::ReadOnly);
		auto resource = GuiResource::LoadPrecompiledBinary(fileStream, errors);
		GetResourceManager()->SetResource(L"Resource", resource);
	}
	demo::MainWindow window(new ViewModel);
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}