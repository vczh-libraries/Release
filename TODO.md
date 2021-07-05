# TODO

https://zhuanlan.zhihu.com/p/39369370

## GacUI 1.0

### Bug

- [ ] `GlobalStringKey` need to remember the `GlobalStringKeyManager` object, and if the global object is changed, it means this key becomes a wild pointer, it should crash.
- [ ] `let X = Y in (F(X.a.b.c))` reports `X does not exist in the current scope` in binding property value
  - while `F((let X = Y.a.b).c)` works
- [ ] GacGen reports only "error dumping resource file" while the resource file contains some syntax errors preventing GacGen from reading it
  - Unable to repro

### Feature (not necessary 1.0)

- [ ] Drag and Drop framework
- [ ] `IColumnItemView`
  - [ ] Change column size from `int` to `{minSize:int, columnOption:Absolute|Percentage, absolute:int, percentage:float}`
  - [ ] Column drag and drop
    - [ ] ListView: swap column object, texts in list view items are not touch
    - [ ] DataGrid: swap column object, cells are changed due to binding
- [ ] ListView
  - [ ] `GroupedListView` and `BindableGroupedListView` from `GuiVirtualListView`: Group headers on all views
  - [ ] `TreeListView` and `BindableTreeListView` from `GuiVirtualTreeView`
- [ ] New `GuiListControl::IItemArranger` that can accept a `GuiRepeatCompositionBase`
- [ ] - `<eval Eval="expression"/>` tags
- [ ] INativeImage::SaveToStream handle correctly for git format. It is possible that LoadFromStream need to process diff between git raw frames.
- [ ] New skin
  - [ ] New default control templates with animation, written in XML generated C++ code.
  - [ ] A window can be called to update all its controls' and components' template
  - [ ] Tutorials use the new default control templates

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
  - `Slice`, `Concat` functions on interfaces
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

- Use collection interfaces on function signatures.
- UI Automation
- Test Automation for `GacUISrc`

### Cross Platforms

- `INativeHostedController` + `INativeHostedWindow`
  - Implementing these interfaces enable GacUI to run in the `hosted single window` mode, all GacUI windows and menus are rendered in one native window
- SyncTree architecture that streams layout/element changes per `GuiControlHost`
- Port GacUI to other platforms:
  - Windows
    - Command/Powershell Line in Windows (hosted)
    - GDI (hosted mode)
    - Direct2d (hosted mode)
    - UWP (hosted mode + sync tree)
  - Linux
    - Ncurses on Ubuntu (hosted)
    - xGac repo
  - macOS
    - iGac repo
  - Web Assembly (hosted mode + sync tree)
    - Canvas?
    - DOM?

### Graphics

- 2D drawing API
- restriction-based MetaImageElement
  - Remove PolygonElement
  - Default non-text element renderer using 2D drawing API
- Meta3DElement and Meta3D data structure
  - Default Meta3DElement renderer using MetaImageElement with a surface sorting based algorithm
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

### Refactoring

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
- In the final pass, only workflow scripts are printed
  - Use WorkflowCompiler.exe to do codegen externally
- Incremental build inside single resource.
  -  Calculate dependencies by only parsing.
  -  Cache workflow assembly per resource in file.
  -  Codegen c++ from multiple workflow assembly.

## GacStudio.exe
