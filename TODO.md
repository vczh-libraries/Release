# TODO

## Vlpp

* `IValueSubscription` uses event instead of `IValueListener` + `Subscribe(object)`
* Regex supports UTF-16 (instead of UCS-2) on MSVC
    * Always convert to UTF-32 internally (**`vl::regex::Utf32Reader`**)
* Redesign vl::parsing

## Workflow

* **Workflow to C++ code generation with hint**.
    * Don't create IValueList if apply `{1 2 3}` on `List<int>` argument.
    * Use ::vl::vint for int in both 32 and 64 configurations.
* State Machine

#### (probably not do)

* Macro
* Context-Grammar Sensitive Macro
* Virtual function
* Class implements interface

## GacUI

#### Templates
- [x] Simplify item arranger
- [x] Add deserializer to IGuiInstanceLoader series API
- [x] `ItemTemplate<T>` for control template properties
- [x] `ItemTemplate<T>` for item template properties
- [x] Strong-typed template checking (in XML, instead of delaying until compiling generated workflow script)
- [x] Remove `IItemStyle(Provider|Controller)`
- [ ] Full control test UI in GacUISrc/Host project
- [ ] New predefined control templates, written in XML generated C++ code.
- [ ] GuiBindableRepeatContainer
    * Using `Flow` and `Stack` directly
    * Not a list control
    * Or let list control be able to hide scrolls and extend the parent container
- [ ] Redesign TabControl's control template so that a container can bind to tab header list control
- [ ] Remove control style interfaces, controls talk to templates directly, archive Win7/Win8 control templates
- [ ] Redesign ToolstripMenu so that items so that a container can bind to toolstrip items
- [ ] Retire Win7/Win8 control templates, rewrite them in tutorials.
- [ ] Simple way to write animation using Workflow in Xml resource, add animation to default control templates
- [ ] Enable Workflow script template for IGuiInstanceLoader written in text

#### Graphics
- [ ] MetaImageElement and MetaImage data structure
- [ ] Remove PolygonElement
- [ ] Default non-text element renderer using MetaImageElement
- [ ] Replacing GDI and D2D non-text element renderers
- [ ] Meta3DElement and Meta3D data structure
- [ ] Default Meta3DElement renderer using MetaImageElement with a surface sorting based algorithm

#### Controls
- [ ] Chart
- [ ] Ribbon
- [ ] Dock Container
- [ ] Icon

## GacUI Resource

* InheritableCustomWindow
* InheritableCustomControl
* Localizable text template resource, adding str://
* Visual State, State Machine, Animation

#### (probably not do)

* GuiCustomControl::SetContainerComposition // using a special syntax
* InstanceStyle:Replace

## GacGen.exe

* Enable linking to external symbols

## GacStudio.exe

## DocTools

* Support `decltype(auto)` type
