## Animation (continuation)

### Goal
- Implement Animation in GacUI XMl Resource
- Possible to provide state machine XML tags
- Animation can be aborted at any moment, and launch a new one if necessary
- Animation can change different part of the view model using different interpolation at the same time

### Script

```

class MyProperties
{
    prop A : int {}
    prop B : int {}
}

func CreatePropA() : MyProperties^ { ... }
...

func MyCalculation(dest: MyProperties^, a: MyProperties^, b: MyProperties^, ...): void { ... }

$interface IMyAnimation : IGuiAnimation<MyProperties>; // prop CurrentState : MyProperties^ {}

func MyAnimation() : IMyAnimation
${
    $Set CreatePropA(); // or use CurrentState
    $Play CreatePropB(), 10 // gradually change to the specified state during 10 seconds
    $Play CreatePropC(), 10, [$1*$1] // change the default linear interpolation 
    for(i in range [1, 10])
    {
        $Play CreatePropB(), 10, MyCalculation // call a function to decide the interpolation
    }
}
```
