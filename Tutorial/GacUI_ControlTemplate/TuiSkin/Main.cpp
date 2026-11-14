#include "UI/TuiControlTest/Source/TuiControlTest.h"
#include "TuiControlTestEventHandlers.h"

using namespace vl;
using namespace vl::stream;
using namespace vl::presentation;
using namespace vl::presentation::controls;

void GuiMain()
{
	{
		FileStream fileStream(L"../UIRes/TuiSkin.bin", FileStream::ReadOnly);
		GetResourceManager()->LoadResourceOrPending(fileStream);
	}
	tuidemo::TuiMainWindow window;
	tuidemo::AttachTuiEvents<tuidemo::TuiDocumentEditorBase, tuidemo::TuiSkinItem>(&window);
	window.ForceCalculateSizeImmediately();
	GetApplication()->Run(&window);
}
