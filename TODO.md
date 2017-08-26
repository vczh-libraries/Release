# TODO

## Vlpp

* Regex supports UTF-16 (instead of UCS-2) on MSVC.
    * Always convert to UTF-32 internally (**`vl::regex::Utf32Reader`**).
* Redesign vl::parsing.
    * No need to specify ambiguity
    * Will print all ambiguous cases and marked AST node
    * ToString with hints and custom options
    * Print diff when updating AST (for IDE)
    * All existing features and backward compatible interface design

### (optional)

* Binary ITypeDescriptor provider format.
* API to import and export fake types (ITypeDescriptor that cannot be executed)

## Workflow

* **Workflow to C++ code generation with hint**.
    * Don't create IValueList if apply `{1 2 3}` on `List<int>` argument.
    * Leave spaces for user defined `#include`s or `using namespace`s.

### (optional)

* Support `<category>name` identifier, make generated code re-parsable.
* Separate assembly binary to types, instructions and debug informations.
* State Machine.
* WorkflowCompiler.exe (x32/x64)
    * Enable external symbols
    * Compile
    * Binary Output (full assembly or types only)
    * C++ Codegen (x32/x64)
    * C++ Merge

### (probably not do)

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
- [x] Full control test UI in GacUISrc/Host project
- [x] Fix ControlTemplates/BlackSkin
- [x] **Update Release**, use Full control test to replace ControlTemplates tutorial
- [x] Generate ITheme implementation in XML Resource
- [x] Retire and archive Win7/Win8 control templates, using DarkSkin temporary
- [x] Separate DarkSkin from FullControlTest
- [x] Update GacGen with new codegen functions
- [x] Support 32-64 merging in GacGen
- [x] Generate DarkSkin to `Source\Skins\DarkSkin\`
- [x] Update CodePack to read `/* CodePack: */` comments
- [x] Generate DarkSkin code to Release\Skins\DarkSkin.(h|cpp)
- [x] **Update Release**, every tutorial uses DarkSkin in shared library, with a new common `WinMain.cpp`
- [ ] GuiListControl with non-virtual composition items
    * GuiScrollView supports hiding scrolls forever
    * New arranger for `Flow` and `Stack`
- [ ] Redesign TabControl's control template so that a container can bind to tab header list control
- [ ] Update DarkSkin to write a new tab template
- [ ] **Update Release**
- [ ] Remove control style interfaces, controls talk to templates directly
- [ ] **Update Release**
- [ ] New default control templates, written in XML generated C++ code.
- [ ] Default control templates replace GacUIDefaultSkin
- [ ] **Update Release**
- [ ] Reorganize GacUISrc so that it builds a template library containing multiple set of skins
- [ ] **Update Release**, so that ControlTemplate tutorial is updated
- [ ] Simple way to write animation using Workflow in Xml resource, add animation to default control templates
- [ ] Enable Workflow script template for IGuiInstanceLoader written in text
- [ ] Redesign ToolstripMenu so that items so that a container can bind to toolstrip items
- [ ] Normal text box supports surrogate pairs like document viewer

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

### (probably not do)

* GuiCustomControl::SetContainerComposition // using a special syntax
* InstanceStyle:Replace

## GacGen.exe

* Enable linking to external symbols
* Generate `ITheme` implementation

### (optional)

* In the final pass, only workflow scripts are printed
    * Use WorkflowCompiler.exe to do codegen externally

## GacStudio.exe

## DocTools

* Support `decltype(auto)` type
