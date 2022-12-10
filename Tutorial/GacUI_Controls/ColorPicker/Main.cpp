#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/Demo.h"

using namespace vl::collections;
using namespace vl::stream;

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
		items.Add(Ptr(new ColorItem(L"Black",   L"#000000")));
		items.Add(Ptr(new ColorItem(L"Maroon",  L"#800000")));
		items.Add(Ptr(new ColorItem(L"Green",   L"#008000")));
		items.Add(Ptr(new ColorItem(L"Olive",   L"#808000")));
		items.Add(Ptr(new ColorItem(L"Navy",    L"#000080")));
		items.Add(Ptr(new ColorItem(L"Purble",  L"#800080")));
		items.Add(Ptr(new ColorItem(L"Teal",    L"#008080")));
		items.Add(Ptr(new ColorItem(L"Silver",  L"#C0C0C0")));
		items.Add(Ptr(new ColorItem(L"Gray",    L"#808080")));
		items.Add(Ptr(new ColorItem(L"Red",     L"#FF0000")));
		items.Add(Ptr(new ColorItem(L"Lime",    L"#00FF00")));
		items.Add(Ptr(new ColorItem(L"Yellow",  L"#FFFF00")));
		items.Add(Ptr(new ColorItem(L"Blue",    L"#0000FF")));
		items.Add(Ptr(new ColorItem(L"Fuchsia", L"#FF00FF")));
		items.Add(Ptr(new ColorItem(L"Aqua",    L"#00FFFF")));
		items.Add(Ptr(new ColorItem(L"White",   L"#FFFFFF")));
	}

	LazyList<Ptr<demo::IColorItem>> GetColorItems()override
	{
		return items;
	}
};

void GuiMain()
{
	{
		FileStream fileStream(L"../UIRes/ColorPicker.bin", FileStream::ReadOnly);
		GetResourceManager()->LoadResourceOrPending(fileStream);
	}
	demo::MainWindow window(Ptr(new ViewModel));
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}