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

class ViewModel;

class Category : public Object, public ICategory
{
	friend class ViewModel;
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
		name = L"My Address Book";
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
		if (auto current = dynamic_cast<Category*>(selectedCategory.Obj()))
		{
			auto category = new Category(current);
			category->name = name;
			current->folders.Add(category);
		}
	}

	void RemoveCategory()
	{
		if (auto parent = dynamic_cast<Category*>(selectedCategory->GetParent()))
		{
			parent->folders.Remove(selectedCategory.Obj());
			SetSelectedCategory(nullptr);
		}
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