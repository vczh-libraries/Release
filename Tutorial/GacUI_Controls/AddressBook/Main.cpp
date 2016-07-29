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

class Category : public Object, public ICategory
{
protected:
	WString										name;
	list::ObservableList<Ptr<ICategory>>		folders;

public:
	WString GetName()override
	{
		return name;
	}

	Ptr<IValueObservableList> GetFolders()override
	{
		return folders.GetWrapper();
	}

	Ptr<IValueObservableList> GetContacts()override
	{
		return nullptr;
	}
};

class StaticCategory : public Category
{
public:
	WString GetName()override
	{
		return L"My Address Book";
	}
};

class RootCategory : public Object, public ICategory
{
protected:
	list::ObservableList<Ptr<ICategory>>		folders;

public:
	RootCategory()
	{
		folders.Add(new StaticCategory);
	}

	WString GetName()override
	{
		return L"";
	}

	Ptr<IValueObservableList> GetFolders()override
	{
		return folders.GetWrapper();
	}

	Ptr<IValueObservableList> GetContacts()override
	{
		return nullptr;
	}
};

class ViewModel : public Object, public IViewModel
{
protected:
	Ptr<RootCategory>							rootCategory;

public:
	ViewModel()
	{
		rootCategory = new RootCategory;
	}

	Ptr<ICategory> GetRootCategory()override
	{
		return rootCategory;
	}
};

void GuiMain()
{
	{
		List<WString> errors;
		FileStream fileStream(L"../UIRes/AddressBook.bin", FileStream::ReadOnly);
		auto resource = GuiResource::LoadPrecompiledBinary(fileStream, errors);
		GetResourceManager()->SetResource(L"Resource", resource);
	}
	MainWindow window(new ViewModel);
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}