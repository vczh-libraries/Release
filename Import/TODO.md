# TODO

* Workflow
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
* GacUI C++ Code Generation Supports
    * Strong-typed template checking
    * Don't use string for XXXProperty:
        * **BindableTextList**.(Text|Checked)Property
        * **BindableListView**.(Large|Small)ImageProperty
        * **ListViewColumn**.TextProperty
        * **BindableTreeView**.(Text|Image|Children)Property
        * **BindableDataColumn**.ValueProperty
    * Don't use string for XXXTemplate:
        * **WindowTemplate**.(Tooltip|ShortcutKey)Template
        * **ToolstripButtonTemplate**.SubMenuTemplate
        * **DatePickerTemplate**.Date(Button|TextList|ComboBox)Template
        * **DateComboBoxTemplate**.DatePickerTemplate
        * **ScrollViewTemplate**.(H|V)ScrollTemplate
        * **TextListTemplate**.(Background|Bullet)Template
        * **ListViewTemplate**.(Background|ColumnHeader)Template
        * **TreeViewTemplate**.(Background\ExpandingDecorator)Template
        * **TabTemplate**.(Header|Dropdown|Menu|MenuItem)Template
    * Make ItemSource from constructor argument to property
* Core
    * Embedded Languages: Colorizer, AutoComplete
    * Abstract Graphics API
    * Chart, Ribbon, Dock Container
    * Add G4, Remove G3 [(reference)](http://www.gaclib.net/#~/Tutorial)
* GacGen.exe
    * Hint C++ code generator
* GacStudio
