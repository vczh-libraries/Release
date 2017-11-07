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

#### Sample
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
    calculator.Digit(1);
    calculator.Digit(2);
    calculator.Add();
    calculator.Digit(3);
    calculator.Digit(4);
    calculator.Equal();
    return calculator.Value; // "46"
}
```
