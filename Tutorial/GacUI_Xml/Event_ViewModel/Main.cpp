#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/Demo.h"

using namespace vl::collections;
using namespace vl::stream;

class ViewModelImpl : public Object, public virtual demo::IViewModel
{
public:
	vint Add(vint a, vint b)override
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
		GetResourceManager()->LoadResourceOrPending(fileStream);
	}
	demo::MainWindow window(Ptr(new ViewModelImpl));
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}