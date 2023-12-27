#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/Demo.h"

using namespace vl::collections;
using namespace vl::stream;
using namespace vl::reflection::description;
using namespace demo;

Ptr<GuiImageData> folderImage;
Ptr<GuiImageData> contactBigImage;
Ptr<GuiImageData> contactSmallImage;

class Contact;
class ViewModel;

class Category : public Object, public ICategory
{
	friend class ViewModel;
	friend class Contact;
protected:
	ICategory*							parent;
	WString								name;
	ObservableList<Ptr<ICategory>>		folders;
	ObservableList<Ptr<IContact>>		contacts;

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

	vl::Ptr<GuiImageData> GetImage()override
	{
		return folderImage;
	}

	vl::Ptr<IValueObservableList> GetFolders()override
	{
		return UnboxValue<Ptr<IValueObservableList>>(BoxParameter(folders));
	}

	vl::Ptr<IValueObservableList> GetContacts()override
	{
		return UnboxValue<Ptr<IValueObservableList>>(BoxParameter(contacts));
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

	vl::Ptr<GuiImageData> GetBigImage()override
	{
		return contactBigImage;
	}

	vl::Ptr<GuiImageData> GetSmallImage()override
	{
		return contactSmallImage;
	}

	DateTime GetBirthday()override
	{
		return birthday;
	}

	WString GetBirthdayText()override
	{
		List<WString> formats;
		Locale::UserDefault().GetShortDateFormats(formats);
		if (formats.Count() > 0)
		{
			return Locale::UserDefault().FormatDate(formats[0], birthday);
		}
		return L"";
	}

	WString GetPhone()override
	{
		return phone;
	}

	WString GetAddress()
	{
		return address;
	}

	void Update(const WString& _name, DateTime _birthday, const WString& _phone, const WString& _address)override
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
	ObservableList<Ptr<ICategory>>		folders;

public:
	RootCategory()
	{
		folders.Add(Ptr(new StaticCategory));
	}

	ICategory* GetParent()override
	{
		return nullptr;
	}

	WString GetName()override
	{
		return L"";
	}

	vl::Ptr<GuiImageData> GetImage()override
	{
		return nullptr;
	}

	vl::Ptr<IValueObservableList> GetFolders()override
	{
		return UnboxValue<Ptr<IValueObservableList>>(BoxParameter(folders));
	}

	vl::Ptr<IValueObservableList> GetContacts()override
	{
		return nullptr;
	}
};

class ViewModel : public Object, public IViewModel
{
protected:
	vl::Ptr<RootCategory>							rootCategory;
	vl::Ptr<ICategory>								selectedCategory;
	vl::Ptr<IContact>								selectedContact;

public:
	ViewModel()
	{
		rootCategory = Ptr(new RootCategory);
	}

	vl::Ptr<ICategory> GetRootCategory()override
	{
		return rootCategory;
	}

	vl::Ptr<ICategory> GetSelectedCategory()override
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

	vl::Ptr<IContact> GetSelectedContact()override
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

	void AddCategory(const WString& name)
	{
		if (auto current = dynamic_cast<Category*>(selectedCategory.Obj()))
		{
			auto category = Ptr(new Category(current));
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
	
	vl::Ptr<IContact> CreateContact()override
	{
		if (auto category = dynamic_cast<Category*>(selectedCategory.Obj()))
		{
			auto contact = Ptr(new Contact(category));
			contact->Update(L"Mr. New Contact", DateTime::LocalTime(), L"(123)-456-7890", L"110 st, New York, NY 10118");
			return contact;
		}
		return nullptr;
	}

	void AddContact(Ptr<demo::IContact> contact)override
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
		FileStream fileStream(L"../UIRes/AddressBook.bin", FileStream::ReadOnly);
		auto resource = GuiResource::LoadPrecompiledBinary(fileStream);
		GuiResourceError::List errors;
		GetResourceManager()->SetResource(resource, errors);

		folderImage = resource->GetImageByPath(L"Images/Folder");
		contactBigImage = resource->GetImageByPath(L"Images/ContactBig");
		contactSmallImage = resource->GetImageByPath(L"Images/ContactSmall");
	}
	MainWindow window(Ptr(new ViewModel));
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);

	folderImage = nullptr;
	contactBigImage = nullptr;
	contactSmallImage = nullptr;
}