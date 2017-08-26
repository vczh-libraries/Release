#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/Demo.h"
#include <Windows.h>

using namespace vl::collections;
using namespace vl::stream;

class ViewModel : public Object, public virtual demo::IViewModel
{
public:
	void OpenUrl(const WString& url)override
	{
		ShellExecute(NULL, L"OPEN", url.Buffer(), NULL, NULL, SW_MAXIMIZE);
	}
};

void GuiMain()
{
	{
		FileStream fileStream(L"../UIRes/RichTextEmbedding.bin", FileStream::ReadOnly);
		auto resource = GuiResource::LoadPrecompiledBinary(fileStream);
		GetResourceManager()->SetResource(L"Resource", resource);
	}
	demo::MainWindow window(new ViewModel);
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}