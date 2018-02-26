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
- [ ] Real visual state: different layouts / different images in different sizes
- [ ] Add and query services from controls
- [ ] Demo: DocumentEditor
  - [ ] Manually crafted Ribbon
- [ ] Demo: TextEditor
  - [ ] Use toolstrip group instead of splitter
  - [ ] Recently opened files in both menu and toolbar
- [ ] **Update Release**
- [ ] Normal text box supports surrogate pairs like document viewer
- [ ] RTF / HTML clipboard format for document viewer
- [ ] Locale awared text resource with `str://` protocol
- [ ] Demo: DocumentEditor
  - [ ] Load / Save
- [ ] **Update Release**
- [ ] New default control templates with animation, written in XML generated C++ code.
- [ ] A window can be called to update all its controls' and components' template
- [ ] Tutorials use the new default control templates
- [ ] **Update Release**
- [ ] Enable Workflow script template for IGuiInstanceLoader written in text
- [ ] **Update Release**
- [ ] (optional) `ViewModelContext` property for `GuiListControl` instead of `GuiVirtualDataGrid`
- [ ] (optional) `ViewModelContext` property for repeat compositions
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
