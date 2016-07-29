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

Ptr<GuiImageData> folderImage;
Ptr<GuiImageData> contactImage;

class Category : public Object, public ICategory
{
protected:
	ICategory*									parent;
	WString										name;
	list::ObservableList<Ptr<ICategory>>		folders;

public:
	Category(ICategory* _parent)
		:parent(_parent)
	{
	}

	ICategory* GetParent()override
	{
		return parent;
	}

	WString GetName()override
	{
		return name;
	}

	Ptr<GuiImageData> GetImage()override
	{
		return folderImage;
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
	StaticCategory()
		:Category(nullptr)
	{
	}

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

	ICategory* GetParent()override
	{
		return nullptr;
	}

	WString GetName()override
	{
		return L"";
	}

	Ptr<GuiImageData> GetImage()override
	{
		return nullptr;
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
	Ptr<ICategory>								selectedCategory;

public:
	ViewModel()
	{
		rootCategory = new RootCategory;
	}

	Ptr<ICategory> GetRootCategory()override
	{
		return rootCategory;
	}

	Ptr<ICategory> GetSelectedCategory()override
	{
		return selectedCategory;
	}

	void SetSelectedCategory(Ptr<ICategory> value)override
	{
		if (selectedCategory != value)
		{
			selectedCategory = value;
			SelectedCategoryChanged();
		}
	}

	void AddCategory(WString name)
	{
	}

	void RemoveCategory()
	{
	}
};

void GuiMain()
{
	{
		List<WString> errors;
		FileStream fileStream(L"../UIRes/AddressBook.bin", FileStream::ReadOnly);
		auto resource = GuiResource::LoadPrecompiledBinary(fileStream, errors);
		GetResourceManager()->SetResource(L"Resource", resource);

		folderImage = resource->GetImageByPath(L"Images/Folder");
		contactImage = resource->GetImageByPath(L"Images/Contact");
	}
	MainWindow window(new ViewModel);
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);

	folderImage = nullptr;
	contactImage = nullptr;
}