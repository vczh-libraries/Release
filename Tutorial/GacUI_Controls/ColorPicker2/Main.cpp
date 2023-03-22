#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/Demo.h"

using namespace vl::collections;
using namespace vl::stream;

class ColorItem : public Object, public demo::IColorItem
{
protected:
	demo::IViewModel*			viewModel = nullptr;
	WString						name;
	Color						color;

public:
	ColorItem(demo::IViewModel* _viewModel, WString _name, WString _color)
		: viewModel(_viewModel)
		, name(_name)
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

	Ptr<demo::IViewModel> GetViewModel()override
	{
		return Ptr(viewModel);
	}
};

class ViewModel : public Object, public demo::IViewModel
{
protected:
	List<Ptr<demo::IColorItem>>		items;
	Color							selectedColor;

public:
	ViewModel()
	{
		items.Add(Ptr(new ColorItem(this, L"Black",   L"#000000")));
		items.Add(Ptr(new ColorItem(this, L"Maroon",  L"#800000")));
		items.Add(Ptr(new ColorItem(this, L"Green",   L"#008000")));
		items.Add(Ptr(new ColorItem(this, L"Olive",   L"#808000")));
		items.Add(Ptr(new ColorItem(this, L"Navy",    L"#000080")));
		items.Add(Ptr(new ColorItem(this, L"Purble",  L"#800080")));
		items.Add(Ptr(new ColorItem(this, L"Teal",    L"#008080")));
		items.Add(Ptr(new ColorItem(this, L"Silver",  L"#C0C0C0")));
		items.Add(Ptr(new ColorItem(this, L"Gray",    L"#808080")));
		items.Add(Ptr(new ColorItem(this, L"Red",     L"#FF0000")));
		items.Add(Ptr(new ColorItem(this, L"Lime",    L"#00FF00")));
		items.Add(Ptr(new ColorItem(this, L"Yellow",  L"#FFFF00")));
		items.Add(Ptr(new ColorItem(this, L"Blue",    L"#0000FF")));
		items.Add(Ptr(new ColorItem(this, L"Fuchsia", L"#FF00FF")));
		items.Add(Ptr(new ColorItem(this, L"Aqua",    L"#00FFFF")));
		items.Add(Ptr(new ColorItem(this, L"White",   L"#FFFFFF")));
	}

	Color GetSelectedColor()override
	{
		return selectedColor;
	}

	void SetSelectedColor(Color value)override
	{
		selectedColor = value;
		SelectedColorChanged();
	}

	LazyList<Ptr<demo::IColorItem>> GetColorItems()override
	{
		return items;
	}
};

void GuiMain()
{
	{
		FileStream fileStream(L"../UIRes/ColorPicker2.bin", FileStream::ReadOnly);
		GetResourceManager()->LoadResourceOrPending(fileStream);
	}
	demo::MainWindow window(Ptr(new ViewModel));
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}