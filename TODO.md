# TODO

https://zhuanlan.zhihu.com/p/39369370

# GacUI 1.0

- [ ] Move `CopyStream`(GacUI) and `GenerateToStream`(Workflow) to Vlpp and refactor in everywhere including using or copying.
- [x] Add partial ordering to Vlpp and refactor
  - [ ] CodePack `SortDependencies` function
  - [ ] Workflow `WfCppConfig::SortInternal` function
  - [ ] Workflow `PostCollect` function
  - [ ] Workflow `StructRecursivelyIncludeItself` `DuplicatedBaseInterface` errors
  - [ ] `GacBuild.ps1`
- [ ] Workflow Codegen
  - [x] When some classes inherit from a `@cpp:File` class, group them in a different pair of files.
    - [ ] Test internal structs and classes, which depends on other internal structs and classes inside a `@cpp:File` class.
  - [x] Change `USERIMPL` and finish compatibility for merging old code using `USERIMPL(NAME)` from
    ```c++
    USERIMPL(NAME)
    FUNCTION-HEADER
    {
      // USER CODE
    }
    ```
    to
    ```c++
    FUNCTION-HEADER
    {/* USER_CONTENT_BEGIN(NAME) */
    }/* USER_CONTENT_END() */
    ```
  - [x] Use `/* USER_CONTENT_BEGIN(NAME) */` and `/* USER_CONTENT_END() */` for class members(h).
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
