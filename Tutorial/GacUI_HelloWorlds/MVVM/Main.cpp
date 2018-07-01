#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/HelloWorld.h"

using namespace vl::collections;
using namespace vl::stream;
using namespace vl::regex;

class ViewModel : public Object, public virtual vm::IViewModel
{
private:
	WString userName;
	WString password;
	Regex regexLcLetters;
	Regex regexUcLetters;
	Regex regexNumbers;

public:
	ViewModel()
		:regexLcLetters(L"[a-z]")
		, regexUcLetters(L"[A-Z]")
		, regexNumbers(L"[0-9]")
	{
	}

	WString GetUserName()override
	{
		return userName;
	}

	void SetUserName(const WString& value)override
	{
		userName = value;
		UserNameErrorChanged();
	}

	WString GetUserNameError()override
	{
		if (userName == L"")
		{
			return L"User name should not be empty.";
		}
		return L"";
	}

	WString GetPassword()override
	{
		return password;
	}

	void SetPassword(const WString& value)override
	{
		password = value;
		PasswordErrorChanged();
	}

	WString GetPasswordError()override
	{
		if (password == L"")
		{
			return L"Password should not be empty.";
		}
		bool containsLowerCases = regexLcLetters.Match(password);
		bool containsUpperCases = regexUcLetters.Match(password);
		bool containsNumbers = regexNumbers.Match(password);
		if (!containsLowerCases || !containsUpperCases || !containsNumbers)
		{
			return L"Password should contains at least one lower case letter, one upper case letter and one digit.";
		}
		return L"";
	}

	bool SignUp()override
	{
		return true;
	}
};

void GuiMain()
{
	{
		FileStream fileStream(L"../UIRes/MVVM.bin", FileStream::ReadOnly);
		auto resource = GuiResource::LoadPrecompiledBinary(fileStream);
		GetResourceManager()->SetResource(resource);
	}
	auto viewModel = MakePtr<ViewModel>();
	auto window = new helloworld::MainWindow(viewModel);
	window->MoveToScreenCenter();
	GetApplication()->Run(window);
	delete window;
}