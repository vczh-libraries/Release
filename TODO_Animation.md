## Animation (continuation)

### Goal
- Provide XML-defined interpolation function
- Provide new animation API

### Demo
- Download with round progress bar
- First X seconds the animation fill the progress bar
- After that if the downloading is not finished, show a rolling animation
- When the downloading is finished, show a ending animation
- Downloaded text fade in
- Progress bar fly out

### Feature

#### Interpolation function
A new xml tag will be added in <instance> to write a function:
- `func <NAME>(start: T, end: T, target: T): IGuiGraphicsAnimationInterpolation^;`
- `func <NAME>(start: T, end: T, target: U): IGuiGraphicsAnimationInterpolation^;`
  - if T is a value type so it has to be change a property of type T in U

```
interface IGuiGraphicsAnimationInterpolation
{
    func Interpolate(position: double):void;
}
```

#### API
- A group of new overloading functions are added in `GuiInstanceRootObject` which do
  - Add animation to `root->GetControlHostInternal()->GetGraphicsHost()->GetAnimationManager()`, where `GetControlHostInternal` is a new protected abstract function.
  - If the control host is not ready (e.g. the control has not been added to a window), then all animations will be kept and attach to the window later
  - When the root object is deleted, all animations are stopped (set the internal flag so that the animation manager will remove them later)
  - And has the following options:
    - **interpolation object**
    - **timed or infinite**
      - for timed animation
        - **a function** to convert passed total time to a double value
          - default: `passed total time / total time`
        - **a fomular** function to convert a double value from `[0..1]` to `[0..1]` to control the animation behavior
      - for infinite animation
        - **a function** to convert passed total time to a double value
          - default: `passed total time`
    - **end of animation notification**
      - Stop an `IAsync` object
      - Call a callback function

#### Workflow
- Author calls animation APIs themselves to start an animation
- State machine or async coroutine is supported by "end of animation notification"
- Add `$Await GetApplication().DoEvents();`

## Proposal (2)
```xml
<TimedAnimation Progress="progress"> <!-- Progress's default value is "progress" -->
  <Interpolation> <!-- Interpolation's default value is "{ return progress; }" -->
    <!CData[
      {
        var pi = 2 * Math::ASin(1);
        return (Math::Sin((progress - 0.5) * pi) + 1) / 2;
      }
    ]]>
  </Interpolation>
  
  <Data Name="Color" Type="Color"/>
  <Data Name="Distance" Type="int"/> <!-- Data has its own Interpolation child element -->
  
  <States Default="A">
    <State Name="A">
      <Data Name="Color" Value="#FF0000"/>
      <Data Name="Distance" Value="0"/>
    </State>
    <State Name="B">
      <Data Name="Color" Value="#FFFFFF"/>
      <Data Name="Distance" Value="100"/>
    </State>
  </States>
  
  <!--
    Generate component:
      class State{ /* all properties */ }
      property Current : State^ {const, not observe}
      property Source : State^ {const, not observe}
      property Target : State^ {const, not observe}
      property A : State^ {const, not observe}
      property B : State^ {const, not observe}
      func CreateAnimation(source:State^, target:State^, length:int):IGuiGraphicsAnimation^;
      func ContinueAnimation(source:State^, target:State^, length:int):IGuiGraphicsAnimation^;
      func GetAnimationLengthScale(source:State^, target:State^, current:State^):double;
      func Interpolate(source:State^, target:State^, current:State^, progress:double):void;
  -->
</TimedAnimation>

<InfiniteAnimation>
</InfiniteAnimation>
```

## Proposal (3)

- Remove `<InfiniteAnimation>`
- Add `Type="Once|Repeat"` to `<TimedAnimation>`
- All `<State>` should set exactly the same set of properties
- All properties that are not set in `<State>` should have a `Value` property, which is similar to `Interpolation`
  - `Property Value` = `Value`(`Interpolation`((`CurrentTime` - `StartTime`) % `Length` / cast double `Length`))
- (optional) Syntax for `$switch` to wait for callbacks caused from some actions in the `$init` block
- (optional) Syntax for `$switch` to raise a specified exception for wrong inputs

```
try
  {
    $switch(raise "Sad!")
    {
        $init
        {
            DownloadAsync().Execute([$1; this.Cancel(); ], null);
        }
        case A():{}
        case B():{}
    }
}
catch(ex)
{
    if (ex.Message == "Sad!") { return; }
    raise;
}
```
