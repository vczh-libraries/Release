# TODO

* Workflow
    * Enum, `(Item1 | Item2 | Item3)::Enum`, giving a type is not always necessary.
    * Struct, `{fontFamily:'Segoe UI' size:10}::FontProperties`, giving a type is not always necessary.
    * async, delay, yield (provider written in C++). **low priority**
    * Limited serialization
        * Disable serialization for struct and enum.
        * Only `TypedValueSerializerProvider<T>` instances support serialization (e.g. `Color`), or provide a global type conversion interface and registration for type. Only the type author of T can provide all convensions from T to U.
    * Workflow to C++ code generation with hint.
        * Only `Enumerable<T>^` and `ObservableList^` are allowed in script.
        * All native classes report real C++ collection type when using collection objects.
        * C++ code generator reports errors when any script does not satisfy these rules
* GacUI Resource
    * InheritableCustomWindow
    * InheritableCustomControl
    * `<ref.Event/>`
    * `<ref.Component/>` // readonly property with -eval
    * GuiCustomControl::SetContainerComposition // using a special syntax
    * InstanceStyle:Replace
    * Pure C++ Code Generation
    * Visual State, State Machine, Animation
    * ev.Event-(eval|async|delayed)
    * Special grammar kicks in when assigning a text literal to non-serializable struct or enum types
        * enum: `Item1 | Item2 | Item2`, the same as previous.
        * struct: `fontFamily:'Segoe UI' size:10`, the same as previous, but no more {} escaping.
        * Remove -format binding, use -bind/-eval instead:
            * **Before**: `Font-format="fontFamily: $(textBox1.Text) size:$(textBox2.Text)"`
            * **After**: `Font-bind="{fontFamily: textBox1.Text size: (cast int textBox2.Text)}"`
* Core
    * Make ItemSource from constructor argument to property
    * Embedded Languages: Colorizer, AutoComplete
    * Abstract Graphics API
    * Controls: Chart, Ribbon, Dock Container
    * New template (generated pure C++ code), remove old ones
* GacGen.exe
    * Hint C++ code generator
* GacStudio
