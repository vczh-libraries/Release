#include "UI/Source/Demo.h"
#include <Windows.h>

using namespace vl::collections;
using namespace vl::stream;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int CmdShow)
{
	return SetupWindowsDirect2DRenderer();
}

class ColorItem : public Object, public demo::IColorItem
{
protected:
	WString						name;
	Color						color;

public:
	ColorItem(WString _name, WString _color)
		:name(_name)
		, color(Color::Parse(_color))
	{
	}

	WString GetItemName()override
	{
		return name;
	}

	Color GetItemColor()override
	{
		return color;
	}
};

class ViewModel : public Object, public demo::IViewModel
{
protected:
	List<Ptr<demo::IColorItem>>		items;

public:
	ViewModel()
	{
		items.Add(new ColorItem(L"Black",   L"#000000"));
		items.Add(new ColorItem(L"Maroon",  L"#800000"));
		items.Add(new ColorItem(L"Green",   L"#008000"));
		items.Add(new ColorItem(L"Olive",   L"#808000"));
		items.Add(new ColorItem(L"Navy",    L"#000080"));
		items.Add(new ColorItem(L"Purble",  L"#800080"));
		items.Add(new ColorItem(L"Teal",    L"#008080"));
		items.Add(new ColorItem(L"Silver",  L"#C0C0C0"));
		items.Add(new ColorItem(L"Gray",    L"#808080"));
		items.Add(new ColorItem(L"Red",     L"#FF0000"));
		items.Add(new ColorItem(L"Lime",    L"#00FF00"));
		items.Add(new ColorItem(L"Yellow",  L"#FFFF00"));
		items.Add(new ColorItem(L"Blue",    L"#0000FF"));
		items.Add(new ColorItem(L"Fuchsia", L"#FF00FF"));
		items.Add(new ColorItem(L"Aqua",    L"#00FFFF"));
		items.Add(new ColorItem(L"White",   L"#FFFFFF"));
	}

	LazyList<Ptr<demo::IColorItem>> GetColorItems()override
	{
		return items;
	}
};

void GuiMain()
{
	{
		List<WString> errors;
		FileStream fileStream(L"../UIRes/ColorPicker.bin", FileStream::ReadOnly);
		auto resource = GuiResource::LoadPrecompiledBinary(fileStream, errors);
		GetResourceManager()->SetResource(L"Resource", resource);
	}
	demo::MainWindow window(new ViewModel);
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}