#define GAC_HEADER_USE_NAMESPACE
#include <GacUICompiler.h>

using namespace vl::collections;
using namespace vl::workflow;
using namespace vl::workflow::emitter;
using namespace vl::workflow::runtime;

const wchar_t* WorkflowScript = LR"workflow(

module helloworld;

using presentation::*;
using presentation::controls::Gui*;
using presentation::theme::*;

func CreateMainWindow() : Window*
{
	var window = new Window*(ThemeName::Window);
	window.Text = "Hello, world!";
	window.ClientSize = {x:480 y:320};
	window.BoundsComposition.PreferredMinSize = {x:480 y:320};
	window.MoveToScreenCenter();

	var label = new Label*(ThemeName::Label);
	label.Text = "Welcom to GacUI Library!";
	label.Font = {fontFamily:"Segoe UI" size:32};
	window.AddChild(label);

	return window;
}

)workflow";

void GuiMain()
{
	Ptr<WfRuntimeGlobalContext> globalContext;
	{
		List<glr::ParsingError> errors;
		List<WString> codes;
		codes.Add(WorkflowScript);
		workflow::Parser workflowParser;
		auto assembly = Compile(workflowParser, workflow::analyzer::WfCpuArchitecture::AsExecutable, codes, errors);
		globalContext = Ptr(new WfRuntimeGlobalContext(assembly));
		LoadFunction<void()>(globalContext, L"<initialize>")();
	}

	auto CreateMainWindow = LoadFunction<GuiWindow*()>(globalContext, L"CreateMainWindow");

	auto window = CreateMainWindow();
	window->MoveToScreenCenter();
	GetApplication()->Run(window);
	delete window;
}