#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/Demo.h"
#include <Windows.h>

using namespace vl::collections;
using namespace vl::stream;

class ViewModel : public Object, public demo::IViewModel
{
public:
	void BeginDownload(const ::vl::Func<void(::vl::vint32_t)>& progress, const ::vl::Func<void(const ::vl::WString&)>& callback)override
	{
		GetApplication()->InvokeAsync([=]()
		{
			HttpRequest request;
			request.SetHost(L"http://www.microsoft.com/");

			HttpResponse response;
			HttpQuery(request, response);

			// This is a fake progress, it is just for demo
			progress(1);
			for (vint i = 2; i <= 10; i++)
			{
				Sleep(500);
				progress(i);
			}
			callback(response.GetBodyUtf8());
		});
	}
};

void GuiMain()
{
	{
		FileStream fileStream(L"../UIRes/ProgressAndAsync.bin", FileStream::ReadOnly);
		auto resource = GuiResource::LoadPrecompiledBinary(fileStream);
		GetResourceManager()->SetResource(L"Resource", resource);
	}
	demo::MainWindow window(new ViewModel);
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}