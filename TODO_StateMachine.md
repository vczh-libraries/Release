## Proposal (Workflow State Machine)

### Goal
To implement
* Async operations
* Delayed operations
* State machine (visual state, animation)

### Agenda
- [x] State Machine Interface
- [x] Raw state machine
- [x] Extension Syntax
- [x] Extension (Enumerable, $Yield)
- [x] Extension (Task, $Await, return)
- [ ] Extension (State Machine)

### Extension (Syntax)

* `return` is always mapped to `ReturnAndExit`
    * If `return` has an expression, than `ReturnAndExit` should also have an argument
* `$<OPERATOR> ...;` is available if `<OPERATOR>AndRead` or `<OPERATOR>AndPause` exists
* `var NAME = $<OPERATOR> ...;` is available if `<OPERATOR>AndRead` exists
    * The return type is object, except that there is a `static func CastResult(value : object):T` in one of the argument types
    * Use the first available and correct CastResult that is discovered
* A function body begins with `${` or `$<PROVIDER>{` means this is a coroutine function
    * If the provider is not omitted, it will search for a type named `<PROVIDER>`, and than use `<PROVIDER>Coroutine` as the provider
    * If the provider is omitted, it will search the return type and its base types in order, and find the first existing `<TYPE>Coroutine` class as the provider
    * A provider is only choosen by name. If the class ending with `Coroutine` doesn't have appropriate functions, errors occur.
    * For example:
        * `func F() : int[] ${}` returns `int[]`, which is `system::Enumerable`, so `system::EnumerableCoroutine` is used.
        * `func F() : IDownloadAsync^ ${}` returns `IDownloadAsync`, which has a base interface `system::Async`, so `system::AsyncCoroutine` is used.
        * `func F() : void $Async{}` has a provider `Async`, so `system::AsyncCoroutine` is used.
* If the function return type does not match the provider's `Create` function
    * If the function returns void, then `CreateAndRun` is used
    * In other cases:
        * Cast from InterfaceA to InterfaceB
        * InterfaceB is required to inherit from InterfaceA
        * Fail if InterfaceB has extra methods

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
