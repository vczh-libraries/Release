# TODO

## Vlpp

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

* Strong-typed template checking (in XML, instead of delaying until compiling generated workflow script)
* Icon
* Abstract Graphics API
    * MetaImageElement
        * Remove PolygonElement
        * Default non-text element renderer implementation by delegating things to MetaImageElement
        * Remove non-text GDI and D2D element renderer implementation
    * Meta3DImageElement
        * Default implementation by delegating things to MetaImageElement
            * Surface-sorting based renderer
* Chart, Ribbon, Dock Container
* **(after animation is done)**
    * New predefined control templates, written in XML generated C++ code.
    * Retire Win7/Win8 control templates, rewrite them in tutorials.
    * Remove control style interfaces, controls talk to templates directly

## GacUI Resource

* Handle resource file encoding if there is no BOM
    * Windows: Test UTF-8 correctness and local encoding correctness, may need to modify `vl::filesystem::File`
    * Others: Use local encoding (usually UTF-8)
* InheritableCustomWindow
* InheritableCustomControl
* GuiCustomControl::SetContainerComposition // using a special syntax
* Localizable text template resource, adding str://
* Visual State, State Machine, Animation

#### (probably not do)

* InstanceStyle:Replace

## ParserGen.exe

* Handle resource file encoding if there is no BOM
    * Windows: Test UTF-8 correctness and local encoding correctness, may need to modify `vl::filesystem::File`
    * Others: Use local encoding (usually UTF-8)

## GacGen.exe

* Enable linking to external symbols

## GacStudio.exe

## DocTools

* Support `decltype(auto)` type
