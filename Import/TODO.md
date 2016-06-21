# TODO

* Workflow
    * Enum
    * Struct
    * Expression: new T{x}, Enum.Item
    * async, delay, yield (provider written in C++)
    * Workflow to C++ code generation with hint
        * Only Enumerable<T>^ and ObservableList^ are allowed in script
        * All native classes report real C++ collection type when using collection objects
        * Only TypedValueSerializerProvider<T> instances support serialization (e.g. Color)
        * C++ code generator reports errors when any script does not satisfy these rules
* GacUI Resource
    * InheritableCustomWindow
    * InheritableCustomControl
    * <ref.Event/>
    * <ref.Component/> // readonly property with -eval
    * GuiCustomControl::SetContainerComposition // using a special syntax
    * InstanceStyle:Replace
    * Pure C++ Code Generation
    * Visual State, State Machine, Animation
    * ev.Event-(eval|async|delayed)
* Core
    * Limit combo box dropdown size
    * Bindable combo box that can customize the selected value representation
    * Embedded Languages: Colorizer, AutoComplete
    * Abstract Graphics API
    * Controls: Chart, Ribbon, Dock Container
    * New template (generated pure C++ code), remove old ones
* GacGen.exe
    * Hint C++ code generator
* GacStudio