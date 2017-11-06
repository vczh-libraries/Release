## Animation (continuation)

### Goal
- Implement Animation in GacUI XMl Resource
- Possible to provide state machine XML tags
- Animation can be aborted at any moment, and launch a new one if necessary
- Animation can change different part of the view model using different interpolation at the same time
- Using `IAsync`

### Demo
- Download with round progress bar
- First X seconds the animation fill the progress bar
- After that if the downloading is not finished, show a rolling animation
- When the downloading is finished, show a ending animation
- Downloaded text fade in
- Progress bar fly out

### Animation

- Feature
  - Can be canceled at any moment
  - Can set a new start state or start from the current state
- Exit Condition
  - Time based
  - Condition based
- Playing Rate
  - Realtime
  - Frame animation with a fixed interval
- Composed animation
- With infinite looping

### XML
