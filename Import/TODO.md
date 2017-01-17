# TODO

## Working On
* Workflow
    * Attributes
    * **Workflow to C++ code generation with hint**.
    	* Don't create IValueList if apply `{1 2 3}` on `List<int>` argument.
        * Generate reflection code, protected by VCZH_DEBUG_NO_REFLECTION.
	* Multiple file support
	* Merge user code
	* Use ::vl::vint for int in both 32 and 64 configurations

## Comming Soon
* GacUI
    * Don't use string for XXXProperty:
        * **BindableTextList**.(Text|Checked)Property
        * **BindableListView**.(Large|Small)ImageProperty
        * **ListViewColumn**.TextProperty
        * **BindableTreeView**.(Text|Image|Children)Property
        * **BindableDataColumn**.ValueProperty
    * Don't use string for XXXTemplate:
        * **WindowTemplate**.(Tooltip|ShortcutKey)Template
        * **ToolstripButtonTemplate**.SubMenuTemplate
        * **DatePickerTemplate**.Date(Button|TextList|ComboBox)Template
        * **DateComboBoxTemplate**.DatePickerTemplate
        * **ScrollViewTemplate**.(H|V)ScrollTemplate
        * **TextListTemplate**.(Background|Bullet)Template
        * **ListViewTemplate**.(Background|ColumnHeader)Template
        * **TreeViewTemplate**.(Background\ExpandingDecorator)Template
        * **TabTemplate**.(Header|Dropdown|Menu|MenuItem)Template
	* IEventInfo::ICpp for composition events
* GacGen.exe
    * Add G4, Retire G2 [(reference)](http://www.gaclib.net/#~/Tutorial)
    * Regenerate G2 tutorials using G4
        * **HelloWorlds**: CppXml, MVVM
        * **Layout**: Alignment, Flow, Stack, Table, TableSplitter, RichTextEmbedding
        * **Controls**: ContainersAndButtons, TextEditor, ColorPicker, AddressBook
        * **ControlTemplates**: BlackSkin
        * **Xml**:
            * Binding_(Bind|Eval|Format|Uri|ViewModel)
            * Event_(Cpp|Script|ViewModel)
            * Instance_(Control|WIndow|MultipleWindows)
            * Member_(Field|Parameter|Property)
    
## Wait For A Few Releases
* GacUI Resource
    * InheritableCustomWindow
    * InheritableCustomControl
    * GuiCustomControl::SetContainerComposition // using a special syntax
    * `<ref.Event/>`
    * `<ref.Component/>` // readonly property with -eval
    * Strong-typed template checking (in XML, instead of delaying until compiling generated workflow script)
    * Report errors with XML row/column number
* GacUI
    * New predefined control templates, written in XML generated C++ code.
    * Retire Win7/Win8 control templates, rewrite them in tutorials.
* GacGen.exe
    * Enable linking to external symbols

## Low Property
* Workflow
     * async, delay, yield (provider written in C++).
     * Auto property
* GacUI Resource
    * InstanceStyle:Replace
    * Visual State, State Machine, Animation
    * ev.Event-(eval|async|delayed)
    * `<ref.Members>`, `<ref.CtorBefore>`, `<ref.CtorAfter>`, `<ref.Dtor>`
    * Non-standard event handler name: `arg1`, `arg2`, ...
        * Instead of `<argument>1`, `<argument>2`, ...
* GacUI
    * Make ItemSource from constructor argument to property
    * Embedded Languages: Colorizer, AutoComplete
    * Abstract Graphics API
    * Chart, Ribbon, Dock Container
* GacStudio.exe

## Proposal (Workflow State Machine)

### Goal
To implement
* Async operations
* Delayed operations
* State machine (visual state, animation)

### State Machine Interface
```
namespace system
{
    interface IStateMachine
    {
        func Start() : void;            /* Call to restart, will raise exception during execution */
        func Stop(ex : string) : void;  /* Call to stop, will raise exception if not started. */
        
        func GetIsExecuting() : bool;
        event IsExecutingChanged();
        prop IsExecuting : bool {GetIsExecuting : IsExecutingChanged}
        
        event OnError(Exception^);      /* The current step goes wrong and continue to wait for more inputs */
        event OnFatal(Exception^);      /* The whole state machine goes wrong and has to stop */
        event OnStart();
        event OnExit();
    }
}
```

### Keywords
* `stateinput`
* `statefatal`
* `stateerror`

### Syntax
```
stateinput <Name>(<Argument>, ...);
statefatal "exception";     /* stop the state machine with a fatal error */
stateerror "exception";     /* redo the current stateinput statement with an error, only available in stateinput statement */
return;                     /* stop the state machine normally */

/* wait until received expected input */
switch(stateinput <IStateMachine^ expression, optional, will loop until it done, or fatal if there is a statefatal>)
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
        ...
    }
}

/* join another stat machine */
var result : object = null;
switch(stateinput IStateMachine::Any({m1 m2 m3}))
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

interface ICountDown : IStateMachine
{
    stateinput BeginCountDown();
    /* Equivalent to */
    func BeginCountDown() : void;
    func GetBeginCountDownEnabled() : bool;
    event BeginCountDownEnabledChanged() : bool;
    prop BeginCountDownEnabled : bool {GetBeginCountDownEnabled : BeginCountDownEnabledChanged}

    stateinput CountDown();
    stateinput DoNotCall();
    
    /* auto declare getter, setter and event */
    /* implementations are not generated in interface, but this one is implemented in state machine */
    prop Remains : int;
}
```

### Sample (Xml)
```xml
<Instance ref.CodeBehind="false" ref.Class="demo::MainWindow">
  <ref.Component Name="CountDown" Type="ICountDown^" Value="new CountDown^()"/>
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
	        statemachine
            {
                stateinput
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
                        stateinput
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
