#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/Demo.h"
#if defined VCZH_MSVC
#include <VlppOS.Windows.h>
#elif defined VCZH_GCC
#include <unistd.h>
#endif

using namespace vl::collections;
using namespace vl::stream;
#if defined VCZH_MSVC
using namespace vl::inter_process;
#endif

class ViewModel : public Object, public demo::IViewModel
{
public:
	void BeginDownload(const ::vl::Func<void(::vl::vint)>& progress, const ::vl::Func<void(const ::vl::WString&)>& callback)override
	{
		GetApplication()->InvokeAsync([=]()
		{
			// This is a fake progress, it is just for demo
#if defined VCZH_MSVC
			HttpRequest request;
			request.query = L"/";

			WString responseText;
			EventObject completed;
			completed.CreateManualUnsignal(false);
			HttpClientApi client(L"www.microsoft.com", 80);
			client.HttpQuery(request, [&](Variant<HttpResponse, HttpError> result)
			{
				if (auto error = result.TryGet<HttpError>())
				{
					responseText = error->message;
				}
				else
				{
					responseText = result.Get<HttpResponse>().GetBodyUtf8();
				}
				completed.Signal();
			});
			completed.Wait();
			client.Stop();

			progress(1);
			for (vint i = 2; i <= 10; i++)
			{
				Sleep(500);
				progress(i);
			}

			callback(responseText);
#elif defined VCZH_GCC
			progress(1);
			for (vint i = 2; i <= 10; i+=2)
			{
				sleep(1000);
				progress(i);
			}

			callback(L"HttpQuery function only works on Windows.");
#endif
		});
	}
};

void GuiMain()
{
	{
		FileStream fileStream(L"../UIRes/ProgressAndAsync.bin", FileStream::ReadOnly);
		GetResourceManager()->LoadResourceOrPending(fileStream);
	}
	demo::MainWindow window(Ptr(new ViewModel));
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}
