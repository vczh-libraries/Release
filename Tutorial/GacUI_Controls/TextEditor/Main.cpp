#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/Demo.h"
#ifdef VCZH_MSVC
#include <Windows.h>
#endif

using namespace vl::collections;
using namespace vl::stream;

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

void GuiMain()
{
	{
		FileStream fileStream(L"../UIRes/TextEditor.bin", FileStream::ReadOnly);
		GetResourceManager()->LoadResourceOrPending(fileStream);
	}
	demo::MainWindow window;
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}

/***********************************************************************
OpenUrl
***********************************************************************/

void OpenUrl(const WString& url)
{
#ifdef VCZH_MSVC
	ShellExecute(NULL, L"OPEN", url.Buffer(), NULL, NULL, SW_MAXIMIZE);
#endif
}

/***********************************************************************
SetTokenizer
***********************************************************************/

class XmlColorizer : public GuiTextBoxRegexColorizer
{
public:
	XmlColorizer()
	{
		text::ColorEntry entry;
		entry.normal.text = Color(255, 255, 255);
		entry.normal.background = Color(0, 0, 0, 0);
		entry.selectedFocused.text = Color(255, 255, 255);
		entry.selectedFocused.background = Color(0, 122, 204);
		entry.selectedUnfocused.text = Color(255, 255, 255);
		entry.selectedUnfocused.background = Color(0, 122, 204);
		SetDefaultColor(entry);

		entry.normal.text = Color(0, 128, 0);
		AddToken(L"/<!--([^/-]|-[^/-]|--[^>])*--/>", entry);

		entry.normal.text = Color(128, 0, 255);
		AddToken(L"/<!/[CDATA/[([^/]]|/][^/]]|/]/][^>])*/]/]/>", entry);

		entry.normal.text = Color(255, 255, 255);
		AddToken(L"\"[^\"]*\"", entry);

		entry.normal.text = Color(0, 0, 255);
		AddToken(L"[<>=]", entry);

		entry.normal.text = Color(255, 0, 0);
		AddToken(L"[a-zA-Z0-9_/-:]+", entry);

		entry.normal.text = Color(163, 21, 21);
		AddExtraToken(entry);

		Setup();
	}

	void ColorizeTokenContextSensitive(vint lineIndex, const wchar_t* text, vint start, vint length, vint& token, vint& contextState)override
	{
		// 0 < 1 name 2 att > 0
		switch (token)
		{
		case 3:
			if (length == 1)
			{
				switch (text[start])
				{
				case '<':
					contextState = 1;
					break;
				case '>':
					contextState = 0;
					break;
				}
			}
			break;
		case 4:
			switch (contextState)
			{
			case 0:
				token = -1;
				break;
			case 1:
				token = 5;
				contextState = 2;
				break;
			}
			break;
		}
	}

	vint GetContextStartState()override
	{
		return 0;
	}
};

void SetColorizer(GuiMultilineTextBox* textBox, bool forXml)
{
	textBox->SetColorizer(forXml ? Ptr(new XmlColorizer) : nullptr);
}