#ifdef GACUILITE_TUI_APPLICATION

#define GAC_HEADER_USE_NAMESPACE
#include <GacUI.h>
#include <Skins/TuiSkin/TuiSkin.h>

class DefaultTuiSkinPlugin : public Object, public IGuiPlugin
{
public:

	GUI_PLUGIN_NAME(Custom_DefaultTuiSkinPlugin)
	{
		GUI_PLUGIN_DEPEND(GacGen_TuiSkinResourceLoader);
	}

	void Load(bool controllerUnrelatedPlugins, bool controllerRelatedPlugins)override
	{
		RegisterTheme(Ptr(new tuiskin::TuiTheme));
	}

	void Unload(bool controllerUnrelatedPlugins, bool controllerRelatedPlugins)override
	{
	}
};
GUI_REGISTER_PLUGIN(DefaultTuiSkinPlugin)

int wmain()
{
	auto result = SetupTuiWindowsRenderer();
#if VCZH_CHECK_MEMORY_LEAKS
	_CrtDumpMemoryLeaks();
#endif
	return result;
}

#endif
