# TODO

https://zhuanlan.zhihu.com/p/39369370

# GacUI 1.0

- [x] When there are combo boxes in item templates, inserting items will cause recursively calling list::ItemProviderBase::InvokeOnItemModified
- [x] Use another way to create focus rectangle bitmap mask for Direct2D
- [x] Fix combo dropdown hidden in topmost window
- [x] New `GuiListControl::IItemArranger` with different item height
  - [x] Correctly implement `FreeHeightItemArranger::EnsureItemVisible`
- [x] Change `GuiControl::Font` from `FontProperties` to `Nullable<FontProperties>`. It will changes following parent controls if it is set to null. If `GuiControlHost`'s font is null, it will become the default font.
- [ ] Window Icon
- [x] Fix GacGen crash when defining an instance whose name conflicts with something from imported resources
- [ ] Fix GacGen reports only "error dumping resource file" while the resource file contains some syntax errors preventing GacGen from reading it
- [x] Fix hook mouse events in ButtonTemplate make GuiButton::Click not working
- [x] Fix list control being able to scroll by mouse while there is no scroll bar
- [x] Fix list control cannot set data source from non-null to null
- [x] Initialize localized strings object to `en-US` at the beginning to prevent from getting a null object in script
- [x] `GuiControl::GetDisposeFlag`
- [x] Fix tutorials in release
  - [x] Localization doesn't need to test null Strings
  - [x] DataGrid combo box editor doesn't work
  - [x] AddressBook new folder doesn't work
  - [x] BlackSkin document changing font size doesn't work
- [ ] **Update Release**
- [ ] Fix `<childControl Font-bind="parentControl.Font"/>` script crash.
- [ ] High DPI for Direct2D (GDI will blur)
- [ ] Cannot change column size during datagrid's bounds changing, which is by designed and this could be solved by calling InvokeInMainThread. But new feature for solving this is under considering
- [ ] **Update Release**
- [ ] New default control templates with animation, written in XML generated C++ code.
- [ ] A window can be called to update all its controls' and components' template
- [ ] Tutorials use the new default control templates
- [ ] **Update Release**

**ON GOING**: Document repo

# GacUI 2.0

## Vlpp

* Regex supports UTF-16 (instead of UCS-2) on MSVC.
  * Always convert to UTF-32 internally (**`vl::regex::Utf32Reader`**).
* Redesign vl::parsing.
  * No need to specify ambiguity
  * Will print all ambiguous cases and marked AST node
  * ToString with hints and custom options
  * Print diff when updating AST (for IDE)
  * All existing features and backward compatible interface design
* Binary ITypeDescriptor provider format.
* API to import and export fake types (ITypeDescriptor that cannot be executed)

## Workflow

* Don't create IValueList if apply `{1 2 3}` on `List<int>` argument.
* Support `<category>name` identifier, make generated code re-parsable.
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

#### Before 1.0 (Optional)
- [ ] `<eval Ref="Name"/>` and `<eval Eval="expression"/>` tags
- [ ] Enable Workflow script template for IGuiInstanceLoader written in text
- [ ] INativeImage::SaveToStream handle correctly for git format. It is possible that LoadFromStream need to process diff between git raw frames.

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
* In the final pass, only workflow scripts are printed
  * Use WorkflowCompiler.exe to do codegen externally

## GacStudio.exe

## DocTools

* Rewrite in C++
