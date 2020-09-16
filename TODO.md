# TODO

https://zhuanlan.zhihu.com/p/39369370

## GacUI 1.0

### Bug

- [ ] `GlobalStringKey` need to remember the `GlobalStringKeyManager` object, and if the global object is changed, it means this key becomes a wild pointer, it should crash.
- [ ] `let X = Y in (F(X.a.b.c))` reports `X does not exist in the current scope` in binding property value
  - while `F((let X = Y.a.b).c)` works

### Feature

- [ ] Move dependended plugin from GacUI to Vlpp (optional)
- [ ] Cannot change column size during datagrid's bounds changing, which is by designed and this could be solved by calling InvokeInMainThread. But new feature for solving this is under considering
  - [ ] Considering GuiBindableDataGrid updating columns' sizes according to configuration automatically, and call `GuiControl::InvokeOrDelayIfRendering` (indirectly) inside `DataColumn::NotifyAllColumnsUpdate` when necessary.
  - [ ] Like a table, a column can use `Absolute`, `Draggable` and `Percentage` to specify a column size. Only when a column is draggable, users can use their mouse to change the size of a column, and then trigger `IColumnItemView::SetColumnSize`
- [ ] Consider drag and drop support, with column drag and drop
- [ ] New item arranger that can accept a `GuiRepeatCompositionBase`
- [ ] **Update Release**
- [ ] New default control templates with animation, written in XML generated C++ code.
- [ ] A window can be called to update all its controls' and components' template
- [ ] Tutorials use the new default control templates
- [ ] **Update Release**
- [ ] Fix GacGen reports only "error dumping resource file" while the resource file contains some syntax errors preventing GacGen from reading it
  - Unable to repro

## GacUI 2.0

### Vlpp

- Add `char8_t` and `UString`, and make following library support `UString` natively:
  - `TextWriter/TextReader`, encoder, decoder
  - Regex
  - Parser
- Add `Utf32Encoder` and `Utf32Decoder` to `vl::stream`.
- Consider about heterougeneous tree string
- Regex supports UTF-16 (instead of UCS-2) on MSVC.
  - Always convert to UTF-32 internally (**`vl::regex::Utf32Reader`**).
- Redesign vl::parsing.
  - No need to specify ambiguity
  - Will print all ambiguous cases and marked AST node
  - ToString with hints and custom options
  - Print diff when updating AST (for IDE)
  - All existing features and backward compatible interface design
- Binary ITypeDescriptor provider format.
- API to import and export fake types (ITypeDescriptor that cannot be executed)
- Interfaces for collections types like `IReadableCollection<T>`
  - or `IReadOnlyCollection`, `IWriteOnlyCollection`, `ICollection`
  - `Slice`, `Contact` functions on interfaces
- Reflectable interfaces like `IReflectableReadableCollection<T>`, inherits from `IReadableCollection<T>` and `IReadableCollection<Value>`
- Remove `FOREACH` and `FOREACH_INDEXER`, replaced by range-based for loop
- Fix `Linq` so that lambda parameters can be `auto`, instead of specified `types`
- Redesign `VCZH_MSVC` series macros

### Workflow

- Don't create IValueList if apply `{1 2 3}` on `List<int>` argument.
- Support `<category>name` identifier, make generated code re-parsable.
- Recognize collection interfaces instead of collection entities.
  - Reconsider how to implement collection creating code in Workflow.
- Move to new ParserGen.
- WorkflowCompiler.exe (x32/x64)
  - Enable external symbols
  - Compile
  - Binary Output (full assembly or types only)
  - C++ Codegen (x32/x64)
- (probably not do)
  - Macro
  - Context-Grammar Sensitive Macro
  - Virtual function
  - Class implements interface

### Hero DB

### ParserGen 2

## GacUI

### Before 1.0 (Optional)

- `<eval Eval="expression"/>` tags
- INativeImage::SaveToStream handle correctly for git format. It is possible that LoadFromStream need to process diff between git raw frames.

### After 1.0

- Use collection interfaces on function signatures.
- Move to new ParserGen.

### Cross Platforms

- Ncurses on Ubuntu
- macOS
- Web Assembly

### Graphics

- Proposal 1
  - MetaImageElement and MetaImage data structure
  - Remove PolygonElement
  - Default non-text element renderer using MetaImageElement
  - Replacing GDI and D2D non-text element renderers
  - Meta3DElement and Meta3D data structure
  - Default Meta3DElement renderer using MetaImageElement with a surface sorting based algorithm
- Proposal 2
  - 2D drawing API
  - restriction-based meta image
  - basic 3D rendering based on the above item with a surface sorting based algorithm
- Others
  - GIF player
  - video player

### Controls

- Chart
- Dock Container
- Touch support

### Binders

- Other languages
  - XML still generate C++ files, and they need to be compiled to an appropriate form.
  - Other programming languages doesn't access GacUI objects, instead they implement view model interfaces that defined in XML.
  - Users need to compile C++ code by themselves.
  - Users are not required to write C++ code, but they can.
  - Users can add attributes in XML defined interfaces, so that GacGen can generate a list of them. After that, by reading generated workflow assembly files, glue code can be generated so that users can implement required view model interfaces directly. I will provide some tools for listed languages.
  - Resources need to be generated in C++ files, because other languages cannot access GacUI objects, which means they cannot load resources manually.
  - Languages:
    - [ ] JavaScript / TypeScript through Web assembly
    - [ ] .NET (core?) through dll
    - [ ] Python through dll

## GacGen.exe

- Enable linking to external symbols
  - Remove all loader implementation
  - `mynamespaces::VirtualClassesX` for adding classes (under this namespace) and specifying their base types
    - X for anything, for simulating partial classes
    - following a naming convention, like: `GuiSelectableButton* CheckBox()`
  - `mynamespaces::XXXLoader` for implementing different kinds of properties / constructors that are not actually exist in `mynamespaces::XXX`
    - following a naming convention, e.g. `GuiTableComposition`'s rows/columns properties
    - searching for correct default control templates
  - GacGen.exe uses external files for control types (but not for elements / compositions)
    - external files provide reflection-only type information, maybe created by Workflow
- Modulized GacUISrc sources and projects
  - NativeWindow
  - Windows
  - WindowsGDI
  - WindowsDirect2D
  - GacUI
  - Basic Controls / List Controls / Toolstrip Controls / TextBox Controls
    - Controls in future
    - UI in future (e.g. Wizard framework)
    - With reflections / virtual classes / loaders placed separately
    - CodePack-ed files don't change
  - Compiler
- In the final pass, only workflow scripts are printed
  - Use WorkflowCompiler.exe to do codegen externally

## GacStudio.exe
