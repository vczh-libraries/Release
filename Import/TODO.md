# TODO

* Workflow
    * **Declarations**:
        * Define struct
        * Define enum
    * **Workflow to C++ code generation with hint**.
        * Only `Enumerable<T>^` and `ObservableList^` in containers are allowed in script.
        * C++ code generator reports errors when any script does not satisfy these rules.
    * **Low Priority**:
        * async, delay, yield (provider written in C++).
* GacUI Resource
    * InheritableCustomWindow
    * InheritableCustomControl
    * `<ref.Event/>`
    * `<ref.Component/>` // readonly property with -eval
    * GuiCustomControl::SetContainerComposition // using a special syntax
    * InstanceStyle:Replace
    * Pure C++ Code Generation
    * Visual State, State Machine, Animation
    * **Low Priority**:
        * ev.Event-(eval|async|delayed)
* Core
    * Make ItemSource from constructor argument to property
    * Embedded Languages: Colorizer, AutoComplete
    * Abstract Graphics API
    * Controls: Chart, Ribbon, Dock Container
    * New template (generated pure C++ code), remove old ones
* GacGen.exe
    * Hint C++ code generator
* GacStudio
