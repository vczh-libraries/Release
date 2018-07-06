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
- [x] Resource import item/folder from depended resources
  - [x] `<Folder content="Import" name="Images">import-res://Base/Images</Folder>`
  - [x] `import-res://ResourceName/Path`
  - [x] `<ref.LocalizedStrings>` refer to class name not uri
  - [x] Add Demo: GacUI_Xml/Misc_ImportFolder
- [x] Known issue
  - [x] Ribbon groups doesn't layout well at the beginning, user should resize the window to fix it.
  - [x] AddressBook demo's new contact window default height too large.
  - [x] `Text-bind="Strings.f()"` should not be allowed for `<ref.LocalizedStrings Name="Strings"/>`, it should be `self.Strings.f()`.
  - Find someday to fix it
- [x] **Update Release**
- [ ] Normal text box supports surrogate pairs like document viewer
- [x] Demo: TriplePhaseImageButton using `Context` property
- [ ] Demo: `<SharedSize>` and `<SharedSizeRoot>`
  - [ ] sync all buttons in item templates in a list control
  - [ ] Two columns in repeat flow
- [ ] **Update Release**
- [ ] Workflow Codegen
  - [ ] When some `ref.CodeBehind="false"` classes inherit from a `ref.CodeBehind="true"` one, group them in a different pair of files.
  - [ ] `USERIMPL_BEGIN` and `USERIMPL_END` for header includes, cpp includes and class members.
  - [ ] Put `USERIMPL` series macros in `VlppWorkflowLibrary.h`
- [ ] Document clipboard data should have version
- [ ] Word doesn't recognize embedded GIF represented by data URL in HTML clipboard format.
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
