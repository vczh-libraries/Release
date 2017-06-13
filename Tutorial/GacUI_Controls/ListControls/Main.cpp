#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/Demo.h"
#include <Windows.h>

using namespace vl::collections;
using namespace vl::stream;
using namespace vl::reflection::description;
using namespace demo;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int CmdShow)
{
	return SetupWindowsDirect2DRenderer();
}

class ViewModel : public Object, public IViewModel
{
public:
	list::ObservableList<Ptr<MyTextItem>> textItems;

	Ptr<IValueObservableList> GetTextItems()override
	{
		return textItems.GetWrapper();
	}

	void AddTextItem(Ptr<MyTextItem> item)override
	{
		textItems.Add(item);
	}

	void RemoveTextItem(vint32_t index)override
	{
		textItems.RemoveAt(index);
	}

	void ClearTextItems()override
	{
		textItems.Clear();
	}
};

void GuiMain()
{
	{
		FileStream fileStream(L"../UIRes/ListControls.bin", FileStream::ReadOnly);
		auto resource = GuiResource::LoadPrecompiledBinary(fileStream);
		GetResourceManager()->SetResource(L"Resource", resource);
	}
	demo::MainWindow window(new ViewModel);
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}