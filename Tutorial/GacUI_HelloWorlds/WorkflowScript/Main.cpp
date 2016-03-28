#include <GacUICompiler.h>
#include <Windows.h>

using namespace vl::parsing;
using namespace vl::collections;
using namespace vl::workflow;
using namespace vl::workflow::analyzer;
using namespace vl::workflow::runtime;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int CmdShow)
{
	return SetupWindowsDirect2DRenderer();
}

const wchar_t* WorkflowScript = LR"workflow(

module helloworld;

using presentation::*;
using presentation::controls::Gui*;
using presentation::theme::*;

func CreateMainWindow() : Window*
{
	var theme = ITheme::GetCurrentTheme();

	var window = new Window*(theme.CreateWindowStyle());
	window.Text = "Hello, world!";
	window.ClientSize = cast Size "x:480 y:320";
	window.BoundsComposition.PreferredMinSize = cast Size "x:480 y:320";
	window.MoveToScreenCenter();

	var label = new Label*(theme.CreateLabelStyle());
	label.Text = "Welcom to GacUI Library!";
	label.Font = cast FontProperties "fontFamily:{Segoe UI} size:32";
	window.AddChild(label);

	return window;
}

)workflow";

void GuiMain()
{
	Ptr<WfRuntimeGlobalContext> globalContext;
	{
		List<Ptr<ParsingError>> errors;
		List<WString> codes;
		codes.Add(WorkflowScript);
		auto table = WfLoadTable();
		auto assembly = Compile(table, codes, errors);
		globalContext = MakePtr<WfRuntimeGlobalContext>(assembly);
		LoadFunction<void()>(globalContext, L"<initialize>")();
	}

	auto CreateMainWindow = LoadFunction<GuiWindow*()>(globalContext, L"CreateMainWindow");

	auto window = CreateMainWindow();
	window->MoveToScreenCenter();
	GetApplication()->Run(window);
	delete window;
}