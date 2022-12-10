#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/Demo.h"
#ifdef VCZH_MSVC
#include <Windows.h>
#endif

using namespace vl::collections;
using namespace vl::stream;

class ViewModel : public Object, public virtual demo::IViewModel
{
public:
	void OpenUrl(const WString& url)override
	{
#ifdef VCZH_MSVC
		ShellExecute(NULL, L"OPEN", url.Buffer(), NULL, NULL, SW_MAXIMIZE);
#endif
	}
};

void GuiMain()
{
	{
		FileStream fileStream(L"../UIRes/RichTextEmbedding.bin", FileStream::ReadOnly);
		GetResourceManager()->LoadResourceOrPending(fileStream);
	}
	demo::MainWindow window(Ptr(new ViewModel));
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}