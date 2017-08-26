#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/Demo.h"

using namespace vl::collections;
using namespace vl::stream;

class ViewModelImpl : public Object, public virtual demo::IViewModel
{
public:
	WString GetMessageFromName(const WString& name)override
	{
		return L"Hi, " + name + L"! How are you?";
	}
};

void GuiMain()
{
	{
		FileStream fileStream(L"../UIRes/Binding_ViewModel.bin", FileStream::ReadOnly);
		auto resource = GuiResource::LoadPrecompiledBinary(fileStream);
		GetResourceManager()->SetResource(L"Resource", resource);
	}
	demo::MainWindow window(new ViewModelImpl);
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}