# TODO

* Workflow
    * enum:
        * Support comparison, `|` and `&` operators for Enum.
        * When there is an determined expression expected enum type, enum item names are legal expressions.
        * So that `(Item1 | Item2 | Item3)::Enum` is a legal expression.
    * struct:
        * `{fontFamily:'Segoe UI' size:10}::FontProperties`, giving a type is not always necessary.
    * Workflow to C++ code generation with hint.
        * Only `Enumerable<T>^` and `ObservableList^` in containers are allowed in script.
        * All native classes report real C++ collection type when using collection objects.
        * C++ code generator reports errors when any script does not satisfy these rules.
    * Low Priority:
        * async, delay, yield (provider written in C++). **low priority**
* GacUI Resource
    * InheritableCustomWindow
    * InheritableCustomControl
    * `<ref.Event/>`
    * `<ref.Component/>` // readonly property with -eval
    * GuiCustomControl::SetContainerComposition // using a special syntax
    * InstanceStyle:Replace
    * Pure C++ Code Generation
    * Visual State, State Machine, Animation
    * Special grammar kicks in when assigning a text literal to non-serializable struct or enum types
        * serializable types: always use ISerializableType.
        * enum: `Item1 | Item2 | Item3`, the same as previous. (<text>)::<type>
        * struct: `fontFamily:'Segoe UI' size:10`, the same as previous, but no more {} escaping. {<text>}::<type>
        * Remove -format binding, use -bind/-eval instead:
            * **Before**: `Font-format="fontFamily: $(textBox1.Text) size:$(textBox2.Text)"`
            * **After**: `Font-bind="{fontFamily: textBox1.Text size: (cast int textBox2.Text)}"`
    * Low Priority:
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
