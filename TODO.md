# TODO

## Working On
* GacUI Resource
    * Don't need to specify item type when assigning to array properties (e.g. Table.(Rows|Columns))
    * Handle resource file encoding if there is no BOM
        * Windows: Test UTF-8 correctness and local encoding correctness, may need to modify `vl::filesystem::File`
        * Others: Use local encoding (usually UTF-8)
* GacUI
    * Strong-typed template checking (in XML, instead of delaying until compiling generated workflow script)
    * Icon
* Vlpp
    * Redesign vl::parsing
        * No need to specify allow ambiguity or not
        * Escaping and Unescaping pairs (instead of only unescaping)
        * Calculate ambiguous **Parse** cases, pointing out which AST need to support ambiguity
        * Calculate ambiguous **ToString** cases
        * Generate **ToString** algorithm
        * Low overhead AST with reflection
        * Error message generation
        * Error recovering
        * Full CFG power, no limitation
        * Be able to assign to any properties (not just enum) in with statement

## Wait For A Few Releases
* Workflow
    * **Workflow to C++ code generation with hint**.
        * Don't create IValueList if apply `{1 2 3}` on `List<int>` argument.
        * Use ::vl::vint for int in both 32 and 64 configurations.
* GacUI Resource
    * Add `<ref.Ctor>`, `<ref.Dtor>`
    * InheritableCustomWindow
    * InheritableCustomControl
    * GuiCustomControl::SetContainerComposition // using a special syntax
    * Make ItemSource from constructor argument to property
    * Localizable text template resource, adding str://
* GacGen.exe
    * Enable linking to external symbols
* DocTools
    * Support `decltype(auto)` type

## Low Property
* Vlpp
    * Regex supports UTF-16 (instead of UCS-2) on MSVC
        * Always convert to UTF-32 internally (**`vl::regex::Utf32Reader`**)
* Workflow
    * State Machine
    * Macro
    * Context-Grammar Sensitive Macro
    * Virtual function
    * Class implements interface
* GacUI Resource
    * InstanceStyle:Replace
    * Visual State, State Machine, Animation
* GacUI
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
* GacStudio.exe

