#define GAC_HEADER_USE_NAMESPACE
#include <GacUI.h>
#include <Skins\DarkSkin\DarkSkin.h>
#include <Windows.h>

class DefaultSkinPlugin : public Object, public IGuiPlugin
{
public:

	GUI_PLUGIN_NAME(Custom_DefaultSkinPlugin)
	{
		GUI_PLUGIN_DEPEND(GacGen_DarkSkinResourceLoader);
	}

	void Load()override
	{
		RegisterTheme(MakePtr<darkskin::Theme>());
	}

	void Unload()override
	{
	}
};
GUI_REGISTER_PLUGIN(DefaultSkinPlugin)

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int CmdShow)
{
	return SetupWindowsDirect2DRenderer();
}