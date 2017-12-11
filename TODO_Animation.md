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
