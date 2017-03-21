# TODO

## Working On
* Workflow
    * State Machine
        * WfCoroutineStatement: Base class of all coroutine statements, which will be totally removed after the ValidateSemantic pass
* GacUI Resource
    * Don't need to specify item type when assigning to array properties (e.g. Table.(Rows|Columns))
    * Handle resource file encoding if there is no BOM
        * Windows: Test UTF-8 correctness and local encoding correctness, may need to modify `vl::filesystem::File`
        * Others: Use local encoding (usually UTF-8)
* GacUI
    * Report errors with XML row/column number, instead of having Workflow_ValidateStatement
        * in `<Workflow>`
            * Create a full map from AST to position. The coordinate in the position will be used when an AST contains no codeRange.
    * Strong-typed template checking (in XML, instead of delaying until compiling generated workflow script)
    * Icon

## Wait For A Few Releases
* Workflow
    * async, delay, yield (provider written in C++).
    * **Workflow to C++ code generation with hint**.
        * Don't create IValueList if apply `{1 2 3}` on `List<int>` argument.
        * Use ::vl::vint for int in both 32 and 64 configurations.
* GacUI Resource
    * Add `<ref.Ctor>`, `<ref.Dtor>`
    * InheritableCustomWindow
    * InheritableCustomControl
    * GuiCustomControl::SetContainerComposition // using a special syntax
    * Make ItemSource from constructor argument to property
    * Localizable text template resource, adding str://
* GacGen.exe
    * Enable linking to external symbols
* DocTools
    * Support `decltype(auto)` type

## Low Property
* Vlpp
    * Regex supports UTF-16 (instead of UCS-2) on MSVC
        * Always convert to UTF-32 internally (**`vl::regex::Utf32Reader`**)
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
        * Be able to assign to any properties (not just enum) in with statement
* Workflow
    * Macro
    * Context-Grammar Sensitive Macro
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
    * Don't force re-rendering at every frame.
        * GuiGraphicsComposition::Render will detect bounds change
        * IGuiElement will detect property change
* GacStudio.exe

## Proposal (Workflow State Machine)

### Goal
To implement
* Async operations
* Delayed operations
* State machine (visual state, animation)

### Agenda
* State Machine Interface
* Raw state machine
* Extension (Enumerable, $Yield)
* Extension (Task)
* Extension (State Machine)

### State Machine Interface
```
namespace system
{
    enum CoroutineStatus
    {
        Waiting = 0,
        Executing = 1,
        Stopped = 2,
    }

    interface Coroutine
    {
        /* Call (Waiting -> Executing | Stopped), raise exception if (Executing | Stopped) */
        /* If raiseException == true, the function will raise the exception after storing to the Failure property */
        func Resume(raiseException : bool) : void;

        /* Stored the $raise/$retry result */
        prop Failure : Exception^ {const, not observe}
        prop Status : CoroutineStatus {const, not observe}
    }
}
```

### Raw state machine

#### Syntax
* `$coroutine {...}` **expression**
    * Create a Coroutine^
* `$pause {}` **statement**
    * `$pause` are not allowed inside another `$pause`
    * If `return`, `break`, `continue` or any other statements are used to exit the scope
        * The state machine will not pause
* `return` **statement**
    * No expression
    * Stop the state machine
* If an exception is raised and there is no `try` to catch it
    * Stop the state machine with a failure

#### Sample
```
/* Status == Waiting */
$coroutine
{
    /* Resume(): Status == Executing */
    for (i in range [1, 10])
    {
        /* Status == Waiting */
        $pause
        {
            /* Execute some code after Status == Waiting and before yielding the state machine */
        }
        /* Resume(): Status == Executing */
    }
    /* Status == Stopped */
    return;
    /* Status == Stopped with exception */
    raise "Something is happened!";
}
```

### Extension (Enumerable, $Yield)

#### Syntax
* `return` is always mapped to `ReturnAndExit`
    * If `return` has an expression, than `ReturnAndExit` should also have an argument
    * `ReturnAndExit` is always required, and is called at the end of the coroutine
        * All arguments are filled with default values

#### Build a coroutine using a provider
```
/* Use [Enumerable]Coroutine, the ^ sign should match the return type of EnumerableCoroutine */
$new Enumerable^
{
    for (i in range [1, 10])
    {
        /* Use [Enumerable]Coroutine.[Yield]And(Pause|Exit) */
        $Yield(i);
    }
    /* Use [Enumerable]Coroutine.ReturnAndExit */
    return;
}
```

#### Generated code
```
EnumerableCoroutine.Create
(
    func (impl : EnumerableCoroutine.IImpl*) : Coroutine^
    {
        return $coroutine
        {
            for (i in range [1, 10])
            {
                $pause
                {
                    EnumerableCoroutine.YieldAndPause(impl, i);
                }
            }
            {
                EnumerableCoroutine.ReturnAndExit(impl);
                return;
            }
        };
    }
);
```

#### Building a provider
```
class EnumerableCoroutine
{
    interface IImpl : Enumerator^
    {
        func OnNext(value : object) : void;
    }
    
    /* The first argument should match the declaration of the Create function */
    static func YieldAndPause(impl : IImpl*, value : object) : void
    {
        impl.OnNext(value);
    }

    /* The first argument should match the declaration of the Create function */
    static func ReturnAndExit(impl : IImpl*) : void
    {
    }
    
    /* The argument of the Create function should be a function, which has one argument and returns a Coroutine^ */
    static func Create(creator : func (impl : IImpl*) : Coroutine^) : Enumerable^
    {
        return new Enumerable^
        {
            override func CreateEnumerator() : Enumerator^
            {
                return new IImpl^
                {
                    var current = null;
                    var index = -1;
                    var coroutine : Coroutine^ = null;
                    
                    override func OnNext(value : object) : void
                    {
                        index = index + 1;
                        current = value;
                    }

                    override func GetCurrent() : object
                    {
                        return current;
                    }

                    override func GetIndex() : int
                    {
                        return index;
                    }

                    override func Next() : bool
                    {
                        if (coroutine is null)
                        {
                            coroutine = creator(this);
                        }
                        
                        if (coroutine.Status != Stopped)
                        {
                            coroutine.Resume(true);
                        }
                        return coroutine.Status != Stopped;
                    }
                }
            }
        }
    }
}
```

### Extension (Task)

#### Build a coroutine using a provider
```

interface ITask
{
    prop AsyncResult : IAsyncResult^ {const, not observe}
    func Execute(callback : func():void) : void;
}

interface IAsyncResult
{
    prop Task : ITask^ {not observe}
    
    static func StartExecute(asyncResult : IAsyncResult^, callback : func():void) : void
    {
        if (asyncResult.Task is null)
        {
            raise "Wrong!";
        }
        var task = asyncResult.Task;
        task.AsyncResult = asyncResult;
        asyncResult.Task = null;
        task.Execute(callback);
    }
}

interface IDownloadAsync : IAsyncResult
{
    prop CoroutineResult : int[] {const, not observe}
}

func DownloadAsync(string[] urls) : IDownloadAsync^
{
    return new IDownloadAsync^
    {
        override prop CoroutineResult : int[] = null {const, not observe}
        override prop Task : ITask^ = $new Async
        {
            var result : int[] = {};
            for(url in urls)
            {
                var text = $Await(DownloadSingleAsync(url));
                result.Add(text);
            }
            SetCoroutineResult(result);
        } {const, not observe}
    };
}
```

#### Building a provider
```
class AsyncCoroutine
{
    interface IImpl : ITask
    {
        func OnContinue() : void;
    }

    static func AwaitAndRead(impl : IImpl*, value : IAsyncResult^) : void
    {
        // The same to AwaitAndPause, but it supports
        // var NAME = $Await(ASYNC-RESULT);
        // expanding to:
        //      var <ASYNC-RESULT>NAME = ASYNC-RESULT;
        //      $pause { AwaitAndRead(impl, <ASYNC-RESULT>NAME); }
        //      var NAME = <ASYNC-RESULT>NAME.CoroutineResult;
        IAsyncResult::StartExecute(value, impl.OnContinue);
    }
    
    static func Create(creator : func (impl : IImpl*) : Coroutine^) : ITask^
    {
        var impl = new IImpl^
        {
            var coroutine : ICoroutine^ = null;
            var callback : func():void;
            override prop AsyncResult : IAsyncResult^ {not observe}
            
            func OnContinue() : void
            {
                ITask::ScheduleToACorrectThread(func():void
                {
                    coroutine.Resume(true);
                    if (coroutine.Status == Stopped and callback is not null)
                    {
                        callback();
                    }
                });
            }
            
            override func Execute(_callback : func():void) : void
            {
                if (coroutine is not null)
                {
                    raise "Wrong!";
                }
                coroutine = creator(this);
                callback = _callback;
                OnContinue();
            }
        };
    }
}
```

### Extension (State Machine Interface)

#### Declare input methods in interfaces
* `$input Name(a:Ta, b:Tb);` **declaration**
    * `func Name(a:Ta, b:Tb) : bool`
        * Returns false if a failed input causes a retry
        * No overloading
    * `prop NameEnabled : bool {const}`
        * `var <prop>NameEnabled : bool = false;`
        * `func GetNameEnabled() : bool { ... }`
        * `func SetNameEnabled(<value> : bool) : void { ... }`

#### Statements in `$state` declarations
* `$input[_else_exit] { case <INPUT-NAME>(arguments...): { ... } ... }` **statement**
    * If the input is failed to match
        * `$input_else_exit`: exit the current state scope
        * `$input`: retry
* `$input[_else_exit] <INPUT-NAME>(arguments...) (;|{ ... })` **statement**
    * Short for `$input[_else_exit] { case <INPUT-NAME>(arguments...): { ... } }`
* `$join <NAME>;` **statement**
    * Enter the specified state
* `$join { ... }` **statement**
    * Create a state scope, if any `$input_else_exit` failed inside, exit the `$join` statement

#### Declare states inside a new interface expression
* `$state <NAME> { ... }`
    * Define a sub state machine
* `$state { ... }`
    * Define a state machine as the entry
    * Cannot create dead loop for any failed input
        * Example: `$state { while (true) { $join { $input_else_exit DoSomething(); } } }`

#### Sample
```
interface ICalculator : Coroutine
{
    $input Digit(i : int);
    $input Dot();
    $input Add();
    $input Mul();
    $input Equal();
    $input Clear();
    
    prop Value : string {const}
}

var calculator = new ICalculator^
{
    var valueFirst : string = "";
    var op : string = "";
    override prop Value : string = "0";
    
    func Update(value : string) : void
    {
        SetValue(value);
        valueFirst = value;
    }
    
    func Calculate() : void
    {
        if (valueFirst == "")
        {
            valueFirst = value;
        }
        else if (op == "+")
        {
            Update((cast double valueFirst) + (cast double Value));
        }
        else if (op == "*")
        {
            Update((cast double valueFirst) * (cast double Value));
        }
        else
        {
            raise $"Unrecognized operator: $(op)";
        }
    }
    
    $state Digits()
    {
        while (true)
        {
            $input_else_exit Digit(i)
            {
                Value = Value & i;
            }
        }
    }
    
    $state Integer()
    {
        $input_else_exit Digit(i)
        {
            Value = i;
            $join Digits();
        }
    }
    
    $state Number()
    {
        $join Integer();
        $input_else_exit Dot()
        {
            Value = Value & ".";
        }
        $input Digit(i)
        {
            Value = Value & i;
        }
        $join Digits();
    }

    $state
    {
        while (true)
        {
            $join Number();
            $input
            {
                case Add():     {Calculate(); op = "+";}
                case Mul():     {Calculate(); op = "-";}
                case Equal():   {Calculate(); op = "=";}
                case Clear():
                {
                    valueFirst = "";
                    op = "";
                    Value = "0";
                }
            }
        }
    }
};
```
