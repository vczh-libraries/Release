#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/Demo.h"

using namespace vl::collections;
using namespace vl::stream;

class ViewModelImpl : public Object, public virtual demo::IViewModel
{
public:
	WString GetText()override
	{
		return L"This is a Window! (ViewModel)";
	}
};

void GuiMain()
{
	{
		FileStream fileStream(L"../UIRes/Member_Parameter.bin", FileStream::ReadOnly);
		GetResourceManager()->LoadResourceOrPending(fileStream);
	}
	demo::MainWindow window(Ptr(new ViewModelImpl));
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}