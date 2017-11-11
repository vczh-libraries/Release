## State Machine

### Goal
- Author methods, maybe override, using state machine

### Syntax
- `$state_machine` declaration (add methods to a class or an anonymous interface)
  - `$state_input` definition
    - Declare a function, which will be implemented in the state machine
    - Add `override` if necessary
    - If an input is not used, an error occurs
  - `$state` definition
    - Optional parameters
  - `$goto_state` statement
    - Jump to the state, providing arguments
  - `$push_state` statement
    - Await for a new state machine
  - `$switch` statement
    - Await for inputs
    - Configuration for default:
      - `$switch`: `default { raise "not supported input ... "; }`
      - `$switch(ignore[_and_return])`: `default {[return;]}`
      - `$switch(pass[_and_return])`: `default {$pass_input; [return;]}`
  - `$pass_input` statement
    - The next `$switch` will use the current input 

### Sample
```
class Calculator
{
    var valueFirst : string = "";
    var op : string = "";
    prop Value : string = "0";
    
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
    
    $state_machine
    {
        $state_input Digit(i : int);
        $state_input Dot();
        $state_input Add();
        $state_input Mul();
        $state_input Equal();
        $state_input Clear();
    
        $state Digits()
        {
            $switch(pass)
            {
                case Digit(i)
                {
                    Value = Value & i;
                    $goto_state Digits();
                }
            }
        }

        $state Integer(newNumber: bool)
        {
            $switch(pass)
            {
                case Digit(i)
                {
                    if (newNumber)
                    {
                        Value = i;
                    }
                    else
                    {
                        Value = Value & i;
                    }
                    $goto_state Digits();
                }
            }
        }

        $state Number()
        {
            $push_state Integer(true);
            $switch(pass_and_return)
            {
                case Dot()
                {
                    Value = Value & ".";
                }
            }
            $push_state Integer(false);
        }

        $state Calculate()
        {
            $push_state Number();
            $switch
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
        
        $state
        {
            $goto_state Calculate();
        }
    }
}

func Main(): string
{
    var calculator = new Calculator^();
    calculator.RunStateMachine();
    calculator.Digit(1);
    calculator.Digit(2);
    calculator.Add();
    calculator.Digit(3);
    calculator.Digit(4);
    calculator.Equal();
    return calculator.Value; // "46"
}
```

### Generated
```
class Calculator
{
    ... // ignored everything before $state_machine
    
    enum <state>Input
    {
        <state>Invalid = 0,
        Digit = 1,
        Dot = 2,
        Add = 3,
        Mul = 4,
        Equal = 5,
        Clear = 6,
    }
    
    enum <state>State
    {
        <state>Start = 0,
        Digit = 1,
        Integer = 2,
        Number = 3,
        Calculate = 4,
    }
    
    [cpp:Private]
    var <state>input: <State>Input = ::Calculator::<state>Input::<state>Invalid;
    
    [cpp:Private]
    var <state>coroutine: ::system::Coroutine^ = null;
    
    [cpp:Private]
    var <statep-Digit>i: int = 0;
    
    [cpp:Private]
    func <state>Resume(): void
    {
        var <state>currentResult: ::system::CoroutineResult^ = null;
        while (true)
        {            
            if (<state>coroutine: is null)
            {
                if (<state>Result is not null)
                {
                    if (<state>Result.Failure is not null)
                    {
                        raise <state>Result.Failure;
                    }
                }
                break;
            }
            if (<state>coroutine.Status == ::system::CoroutineStatus::Waiting)
            {
                var <state>currentCoroutine = <state>coroutine;
                <state>currentCoroutine.Status.Resume(true, <state>result);
                if (<state>currentCoroutine.Status == ::system::CoroutineStatus::Waiting)
                {
                    currentResult = new ::system::CoroutineResult^();
                    if (<state>currentCoroutine.Failure is not null)
                    {
                        currentResult.Failure = <state>currentCoroutine.Failure;
                    }
                }
            }
        }
    }
    
    func Digit(i: int): void  { <state>input = ::Calculator::<state>Input::Digit; <statep-Digit>i = i;  <state>Resume(); }
    func Dot(): void          { <state>input = ::Calculator::<state>Input::Dot;                         <state>Resume(); }
    func Add(): void          { <state>input = ::Calculator::<state>Input::Add;                         <state>Resume(); }
    func Mul(): void          { <state>input = ::Calculator::<state>Input::Mul;                         <state>Resume(); }
    func Equal(): void        { <state>input = ::Calculator::<state>Input::Equal;                       <state>Resume(); }
    func Clear(): void        { <state>input = ::Calculator::<state>Input::Clear;                       <state>Resume(); }
    
    [cpp:Private]
    func <state>CreateCoroutine(<state>startState: <state>State): void
    {
        <state>previousCoroutine = <state>coroutine;
        <state>coroutine = $coroutine
        {
            var <state>state : <state>State = <state>startState;
            
            while (true)
            {
                switch (<state>state)
                {
                case ::Calculator::<state>State::<state>Start :
                    {
                    }
                case ::Calculator::<state>State::Digit :
                    {
                    }
                case ::Calculator::<state>State::Integer :
                    {
                    }
                case ::Calculator::<state>State::Number :
                    {
                    }
                case ::Calculator::<state>State::Calculate :
                    {
                    }
                }
            }
        };
    }
    
    func RunStateMachine(): void
    {
        if (<state>coroutine is not null)
        {
            raise "RunStateMachine() cannot be called while the state machine is running.";
        }
        <state>CreateCoroutine(:Calculator::<state>State::<state>Start);
        <state>Resume();
    }
}
```
