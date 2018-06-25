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
- [x] Delay all composition tree updating during rendering
- [x] Cancel the delayed layout task in combo box if it is deleted right after the size is changed
- [x] Private clipboard format for `GuiDocument`
- [x] Generate `CF_RTF`(Rich Text Format) but not parse
- [x] Generate `CF_HTML`(HTML Format) but not parse
- [x] Copy image to clipboard if only an image is selected
- [x] Add image file format for all three supported clipboard formats
  - [x] Private clipboard format
  - [x] `CF_RTF`
  - [x] `CF_HTML`
- [ ] Demo: DocumentEditor
  - [ ] Load / Save
- [ ] Known issue: Word doesn't recognize embedded GIF represented by data URL in HTML clipboard format.
  - Find someday to fix it
- [ ] **Update Release**
- [ ] Normal text box supports surrogate pairs like document viewer
- [ ] Demo: TriplePhaseImageButton using `Context` property
- [ ] Demo: `<SharedSize>` and `<SharedSizeRoot>`, sync all buttons in item templates in a list control
- [ ] **Update Release**
- [ ] Inheritable custom window / control with `<ref.Parameter>`
- [ ] Resource should have name and version
- [ ] Document clipboard data should have version
- [ ] Depend on another resource, to decide loading order
- [ ] Demo: DocumentEditor: Split 1 Resource.xml to 3.
- [ ] **Update Release**
- [ ] CppMerge.exe reports error instead of crashes
- [ ] Add and query services from controls
- [ ] **Update Release**
- [ ] New default control templates with animation, written in XML generated C++ code.
- [ ] A window can be called to update all its controls' and components' template
- [ ] Tutorials use the new default control templates
- [ ] **Update Release**
- [ ] Render focus
- [ ] BlackSkin window template handle window properties (border, buttons, ...)
- [ ] SM_CXPADDEDBORDER + SM_CXFRAME == 8, don't hardcode this in DarkSkin.xml. This is for the necessary border when the window is maximized.
- [ ] High DPI for Direct2D (GDI will blur)
- [ ] Window Icon
- [ ] **Update Release**

#### Before 1.0 (Optional)
- [ ] `<eval Ref="Name"/>` and `<eval Eval="expression"/>` tags
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
- [ ] Dock Container

#### Binders
- [ ] Web assembly
- [ ] XML Metadata output for codegen written by users

## GacGen.exe

* Enable linking to external symbols

### (optional)

* In the final pass, only workflow scripts are printed
  * Use WorkflowCompiler.exe to do codegen externally

## GacStudio.exe

## DocTools

* Rewrite in C++
