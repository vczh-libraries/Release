#ifndef GACUILITE_TUI_APPLICATION

#define GAC_HEADER_USE_NAMESPACE
#include <GacUI.h>
#include <Skins\DarkSkin\DarkSkin.h>
#define _WINSOCKAPI_
#include <Windows.h>

#ifdef _DEBUG
#include <GacUI.Windows.h>
#endif
#include <Shellapi.h>
#pragma comment(lib, "Shell32.lib")

namespace gacuilite
{
	bool useGdi = false;
#ifdef _DEBUG
	vint automationPort = 8888;
#endif

	bool ParseArguments()
	{
		int count = 0;
		auto arguments = CommandLineToArgvW(GetCommandLineW(), &count);
		if (!arguments) return false;
#ifdef _DEBUG
		bool specified = false;
#endif
		bool valid = true;
		for (int i = 1; i < count; i++)
		{
			WString argument(arguments[i]);
			if (argument == L"/Gdi")
			{
				useGdi = true;
				continue;
			}
#ifdef _DEBUG
			if (argument.Length() < 7 || argument.Left(7) != L"/AsPort") continue;
			if (specified || argument.Length() <= 8 || argument[7] != L':')
			{
				valid = false;
				break;
			}
			specified = true;
			vint port = 0;
			for (vint j = 8; j < argument.Length(); j++)
			{
				if (argument[j] < L'0' || argument[j] > L'9')
				{
					valid = false;
					break;
				}
				port = port * 10 + argument[j] - L'0';
				if (port > 65535)
				{
					valid = false;
					break;
				}
			}
			if (!port) valid = false;
			if (!valid) break;
			automationPort = port;
#endif
		}
		LocalFree(arguments);
		return valid;
	}
}

class DefaultSkinPlugin : public Object, public IGuiPlugin
{
#ifdef _DEBUG
	windows::WindowsAutomationService automationService;
#endif
public:

	GUI_PLUGIN_NAME(Custom_DefaultSkinPlugin)
	{
		GUI_PLUGIN_DEPEND(GacGen_DarkSkinResourceLoader);
	}

	void Load(bool controllerUnrelatedPlugins, bool controllerRelatedPlugins)override
	{
		RegisterTheme(Ptr(new darkskin::Theme));
#ifdef _DEBUG
		if (controllerRelatedPlugins)
		{
			GetNativeServiceSubstitution()->Substitute(&automationService, false);
			// Let utility service registration finish before HTTP requests can use automation.
			GetCurrentController()->AsyncService()->InvokeInMainThread(nullptr, []()
			{
				auto name = filesystem::FilePath(GetCurrentController()->GetExecutablePath()).GetName();
				windows::StartWindowsHttpAutomationService(L"Automation/" + name, gacuilite::automationPort);
			});
		}
#endif
	}

	void Unload(bool controllerUnrelatedPlugins, bool controllerRelatedPlugins)override
	{
#ifdef _DEBUG
		if (controllerRelatedPlugins)
		{
			windows::StopWindowsHttpAutomationService();
			automationService.Stop();
			GetNativeServiceSubstitution()->Unsubstitute(&automationService);
		}
#endif
	}
};
GUI_REGISTER_PLUGIN(DefaultSkinPlugin)

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int CmdShow)
{
	if (!gacuilite::ParseArguments()) return 1;
	return gacuilite::useGdi ? SetupWindowsGDIRenderer() : SetupWindowsDirect2DRenderer();
}

#endif
