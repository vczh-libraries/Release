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
Ptr<GuiImageData> contactBigImage;
Ptr<GuiImageData> contactSmallImage;

class ViewModel;

class Category : public Object, public ICategory
{
	friend class ViewModel;
protected:
	ICategory*									parent;
	WString										name;
	list::ObservableList<Ptr<ICategory>>		folders;
	list::ObservableList<Ptr<IContact>>			contacts;

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
		return contacts.GetWrapper();
	}
};

class Contact : public Object, public IContact
{
protected:
	Category*									category;
	WString										name;
	DateTime									birthday;
	WString										phone;
	WString										address;

public:
	Contact(Category* _category)
		:category(_category)
	{
	}

	Category* GetCategory()
	{
		return category;
	}

	WString GetName()override
	{
		return name;
	}

	Ptr<GuiImageData> GetBigImage()override
	{
		return contactBigImage;
	}

	Ptr<GuiImageData> GetSmallImage()override
	{
		return contactSmallImage;
	}

	DateTime GetBirthday()override
	{
		return birthday;
	}

	WString GetPhone()override
	{
		return phone;
	}

	WString GetAddress()
	{
		return address;
	}

	void Update(WString _name, DateTime _birthday, WString _phone, WString _address)override
	{
		name = _name;
		birthday = _birthday;
		phone = _phone;
		address = _address;
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
	Ptr<IContact>								selectedContact;

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

	Ptr<IContact> GetSelectedContact()override
	{
		return selectedContact;
	}

	void SetSelectedContact(Ptr<IContact> value)override
	{
		if (selectedContact != value)
		{
			selectedContact = value;
			SelectedContactChanged();
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
	
	Ptr<IContact> CreateContact()override
	{
		if (auto parent = dynamic_cast<Category*>(selectedCategory.Obj()))
		{
			return new Contact(parent);
		}
		return nullptr;
	}

	void AddContact(vl::Ptr<demo::IContact> contact)override
	{
		dynamic_cast<Contact*>(contact.Obj())->GetCategory()->contacts.Add(contact);
	}

	void RemoveContact()override
	{
		if (auto contact = dynamic_cast<Contact*>(selectedContact.Obj()))
		{
			contact->GetCategory()->contacts.Remove(selectedContact.Obj());
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
		contactBigImage = resource->GetImageByPath(L"Images/ContactBig");
		contactSmallImage = resource->GetImageByPath(L"Images/ContactSmall");
	}
	MainWindow window(new ViewModel);
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);

	folderImage = nullptr;
	contactBigImage = nullptr;
	contactSmallImage = nullptr;
}