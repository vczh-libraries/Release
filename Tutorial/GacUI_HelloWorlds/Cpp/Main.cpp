#define GAC_HEADER_USE_NAMESPACE
#include <GacUI.h>

void GuiMain()
{
	GuiWindow* window = g::NewWindow();
	window->SetText(L"Hello, world!");
	window->SetClientSize(Size(480, 320));
	window->GetBoundsComposition()->SetPreferredMinSize(Size(480, 320));
	window->MoveToScreenCenter();

	GuiControl* label = g::NewLabel();
	label->SetText(L"Welcome to GacUI Library!");
	{
		FontProperties font;
		font.fontFamily = L"Segoe UI";
		font.size = 32;
		font.antialias = true;
		label->SetFont(font);
	}
	window->AddChild(label);
	GetApplication()->Run(window);
	delete window;
}