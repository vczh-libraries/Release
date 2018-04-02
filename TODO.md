# TODO

https://zhuanlan.zhihu.com/p/33778843

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
* WorkflowCompiler.exe (x32/x64)
  * Enable external symbols
  * Compile
  * Binary Output (full assembly or types only)
  * C++ Codegen (x32/x64)

### (probably not do)

* Macro
* Context-Grammar Sensitive Macro
* Virtual function
* Class implements interface

## GacUI

#### Before 1.0
- [x] Redesign ToolstripMenu so that toolstrip items can be managed by an item source
  - [x] `GuiToolstripCollection` remove the space of an item if its `Visible` property is false
  - [x] `GuiToolstripGroupContainer` insert splitters between items
    - [x] `SplitterTemplate` property
    - [x] `ToolstripItems` (default) property
  - [x] `GuiToolstripGroup` insert multiple items in one control
    - [x] `ToolstripItems` (default) property
- [ ] `<eval Ref="Name"/>` and `<eval Eval="expression"/>` tags
- [x] Real visual state: different layouts / different images in different sizes
  - [x] `GuiResponsiveContainerComposition` to trigger level switching
  - [x] GuiResponsiveLayoutCompositionBase
    - [x] GuiResponsiveLayoutViewComposition
      Explicitly define views for different size level, with shared item, views should be `GuiResponsiveLayoutCompositionBase`
    - [x] GuiResponsiveLayoutGroupComposition
      All child `GuiResponsiveLayoutCompositionBase` transform at the same time
    - [x] GuiResponsiveLayoutStackComposition
      All child `GuiResponsiveLayoutCompositionBase` transform one by one
    - [x] GuiFixedLayoutComposition
      No transformation
- [x] Add simple demo for responsive layout to FullControlTest
- [x] Demo: Direct2DClock
- [x] Demo: Responsive1
- [ ] Demo: Responsive2
- [ ] Demo: TextEditor
  - [ ] Use toolstrip group instead of splitter
  - [ ] Recently opened files in both menu and toolbar
- [x] Prevent from crashing while binding to a.b.c if a.b is null with a.b.cChanged exists
- [ ] **Update Release**
- [ ] Demo: TriplePhaseImageButton
  - [x] Add TemplateContext(Changed) property to both Control and Template
  - [x] Remove ViewModelContext in BindableDataGrid
- [ ] Locale awared text resource with `str://` protocol
- [ ] **Update Release**
- [ ] Add and query services from controls
- [ ] Demo: DocumentEditor
  - [ ] Manually crafted Ribbon
    - [ ] Big version of toolstrip buttons / Button groups
    - [ ] Label with icon and another editor control
    - [ ] Multiple toolstrip panel
    - [ ] Preview list box
    - [ ] Ribbon Group with expand button
    - [ ] Ribbon tab with home button
- [ ] **Update Release**
- [ ] Normal text box supports surrogate pairs like document viewer
- [ ] RTF / HTML clipboard format for document viewer
- [ ] Demo: DocumentEditor
  - [ ] Load / Save
- [ ] **Update Release**
- [ ] New default control templates with animation, written in XML generated C++ code.
- [ ] A window can be called to update all its controls' and components' template
- [ ] Tutorials use the new default control templates
- [ ] **Update Release**
- [ ] Enable Workflow script template for IGuiInstanceLoader written in text
- [ ] **Update Release**
- [ ] Inheritable custom window / control
- [ ] Resource should have name and version
- [ ] Depend on another resource, to decide loading order
- [ ] **Update Release**
- [ ] (optional) Update all control template properties to have `in` or `out` prefix
  - `in`: Template implementation should read
  - `out`: Template implementation should write
- [ ] Render focus
- [ ] BlackSkin window template handle window properties (border, buttons, ...)
- [ ] SM_CXPADDEDBORDER + SM_CXFRAME == 8, don't hardcode this in DarkSkin.xml. This is for the necessary border when the window is maximized.
- [ ] High DPI for Direct2D (GDI will blur)
- [ ] **Update Release**

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

### (probably not do)

* GuiCustomControl::SetContainerComposition // using a special syntax
* InstanceStyle:Replace

## GacGen.exe

* Enable linking to external symbols

### (optional)

* In the final pass, only workflow scripts are printed
  * Use WorkflowCompiler.exe to do codegen externally

## GacStudio.exe

## DocTools

* Rewrite in C++
