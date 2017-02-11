# TODO

## Working On
* GacUI Resource
    * Don't need to specify item type when assigning to array properties (e.g. Table.(Rows|Columns))
    * Correctly handle spaces when saving `<Doc/>`
* GacUI
    * Report errors with XML row/column number, instead of having Workflow_ValidateStatement
    * Strong-typed template checking (in XML, instead of delaying until compiling generated workflow script)
    * Icon

## Wait For A Few Releases
* Workflow
    * Auto property
        * Put `WfClassMember` inside `WfDeclaration`
        * Add `WfVirtual(Expression|Statement|Declaration)`, to represent an "expandable" AST unit (e.g. bind)
            * `WfExpression`
            * `List<WfStatement>`
            * `List<WfDeclaration>`
        * CONFIG:
            * {}
            * {const}
            * {not observe}
            * {const, not observe}
        * For interface: `prop NAME : TYPE CONFIG;`
            * Expand to Getter / Setter / Event / Property
        * For class: `prop NAME : TYPE = EXPRESSION CONFIG;`
            * Expand to [@cpp:Private]Variable / Getter / Setter / Event / Property
        * For class (override): `override prop NAME : TYPE = EXPRESSION CONFIG;`
            * Expand to [@cpp:Private]Variable / Getter / Setter
    * Macro
    * State Machine
    * Context-Grammar Sensitive Macro
    * **Workflow to C++ code generation with hint**.
        * Don't create IValueList if apply `{1 2 3}` on `List<int>` argument.
        * Use ::vl::vint for int in both 32 and 64 configurations.
* GacUI Resource
    * Add `<ref.Ctor>`, `<ref.Dtor>`
    * InheritableCustomWindow
    * InheritableCustomControl  
    * GuiCustomControl::SetContainerComposition // using a special syntax
    * Make ItemSource from constructor argument to property
    * Localizable text template resource
* GacGen.exe
    * Enable linking to external symbols
* DocTools
    * Support `decltype(auto)` type

## Low Property
* Vlpp
    * Regex supports UTF-16 (instead of UCS-2) on MSVC
    * Redesign vl::parsing
        * No need to specify allow ambiguity or not
        * Escaping and Unescaping pairs (instead of only unescaping)
        * Calculate ambiguous **Parse** cases, pointing out which AST need to support ambiguity
        * Calculate ambiguous **ToString** cases
        * Generate **ToString** algorithm
        * Low overhead AST with reflection
        * Error message generation
        * Error recovering
        * Full CFG power, no limitation
* Workflow
    * async, delay, yield (provider written in C++).
    * Virtual function
    * Class implements interface
* GacUI Resource
    * InstanceStyle:Replace
    * Visual State, State Machine, Animation
    * ev.Event-(eval|async|delayed)
* GacUI
    * Embedded Languages: Colorizer, AutoComplete
    * Abstract Graphics API
    * Chart, Ribbon, Dock Container
    * **(after animation is done)**
        * New predefined control templates, written in XML generated C++ code.
        * Retire Win7/Win8 control templates, rewrite them in tutorials.
        * Remove control style interfaces, controls talk to templates directly
* GacStudio.exe

## Proposal (Workflow State Machine)

### Goal
To implement
* Async operations
* Delayed operations
* State machine (visual state, animation)

### Need to consider
* Scheduler
* How to build syntax suger for different kinds of state machines (e.g. Macro)

### State Machine Interface
```
namespace system
{
    enum StateMachineStatus
    {
        Stopped = 0,
        Executing = 1,
        Waiting = 2,
    }

    interface StateMachine
    {
        func Start() : void;            /* Call to restart, will raise exception during execution */
        func Stop(ex : string) : void;  /* Call to stop, will raise exception if it is not executing or waiting for stateinput. */
        prop Status : StateMachineStatus {const}
        event OnStop(Exception^ /* null if no statefatal */);
    }
}
```

### Keywords
* `stateinput`: declaration, statement
* `statefatal`: statement
* `stateerror`: statement
* `statemachine`: declaration

### Syntax
```
stateinput <Name>(<Argument>, ...);
statefatal "exception";     /* stop the state machine with a fatal error */
stateerror "exception";     /* redo the current stateinput statement with an error, only available in stateinput statement */
return;                     /* stop the state machine normally */

/* wait until received expected input */
stateinput(<StateMachine^ expression, optional, will loop until it done, or fatal if there is a statefatal>)
{
    case <Name>(<Argument-Name>, ...):
    {
        ...
    }
    case <Event>(<Argument-Name>, ...):
    {
        ...
    }
    default:
    {
        // if there is no default, stateerror is inserted
    }
}

/* join another stat machine */
var result : object = null;
stateinput(StateMachine::Any({m1 m2 m3}))
{
    case m1.Result(r):{ result = r; }
    case m2.Result(r):{ result = r; }
    case m3.Result(r):{ result = r; }
}
```

### Sample (Workflow Script)
```
module test;
using system::*;
using presentation::controls::Gui*;

interface ICountDown : StateMachine
{
    stateinput BeginCountDown();
    /* Equivalent to */
    func BeginCountDown() : void;
    prop BeginCountDownEnabled : bool {const}

    stateinput CountDown();
    stateinput DoNotCall();
    prop Remains : int {const}
}
```

### Sample (Xml)
```xml
<Instance ref.CodeBehind="false" ref.Class="demo::MainWindow">
  <ref.Members>
    var CountDOwn : ICountDown^ = new CountDown^();
  </ref.Members>
  <Window ref.Name="self" Text="State Machine" ClientSize="x:480 y:320">
    <att.BoundsComposition-set PreferredMinSize="x:480 y:320"/>
    <!-- ignore layout settings -->
    <Button Enabled-bind="self.CountDown.BeginCountDownEnabled">
      <ev.Clicked-eval>{self.CountDown.Start(); self.CountDown.BeginCountDown();}</ev.Clicked-eval>
    </Button>
    <Button Enabled-bind="self.CountDown.CountDownEnabled">
      <ev.Clicked-eval>self.CountDown.CountDown();</ev.Clicked-eval>
    </Button>
    <Button Enabled-bind="self.CountDown.IsExecuting">
      <ev.Clicked-eval>self.CountDown.Stop();</ev.Clicked-eval>
    </Button>
    <Label Text-format="Remains: $(self.CountDown.Remains)"/>
  </Window>
  <ref.Members>
    <![CDATA[
        class CountDown : ICountDown
        {
            override prop Remains : int = 0 {const}

            statemachine
            {
                stateinput()
                {
                    case BeginCountDown():{} /* If there are arguments, specify names only */
                    /*
                    Automatically updated before waiting:
                    BeginCountDownEnabled = true;
                    CountDownEnabled = false;
                    DoNotCallEnabled = false;
                    */
                }

                Remains = 10;
                while (true)
                {
                    if (Remains > 0)
                    {
                        stateinput()
                        {
                            case CountDown():
                            {
                                Remains = Remains - 1;
                            }
                            /*
                            Automatically updated before waiting:
                            BeginCountDownEnabled = false;
                            CountDownEnabled = true;
                            DoNotCallEnabled = false;
                            */
                        }
                    }
                }
            }
        }
    ]]>
  </ref.Members>
</Instance>
```
