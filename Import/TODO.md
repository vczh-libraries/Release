# TODO

## Working On
* Workflow
    * **Workflow to C++ code generation with hint**.
        * Only `Enumerable<T>^` and `ObservableList^` in containers are allowed in script.
        * C++ code generator reports errors when any script does not satisfy these rules.
    
## Comming Soon
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
* GacGen.exe
    * Add G4, Remove G3 [(reference)](http://www.gaclib.net/#~/Tutorial)
    
## Wait For A Few Releases
* GacUI Resource
    * InheritableCustomWindow
    * InheritableCustomControl
    * `<ref.Event/>`
    * `<ref.Component/>` // readonly property with -eval

## Low Property
* Workflow
     * async, delay, yield (provider written in C++).
* GacUI Resource
    * GuiCustomControl::SetContainerComposition // using a special syntax
    * InstanceStyle:Replace
    * Visual State, State Machine, Animation
    * ev.Event-(eval|async|delayed)
* GacUI C++ Code Generation Supports
    * Make ItemSource from constructor argument to property
* Core
    * Embedded Languages: Colorizer, AutoComplete
    * Abstract Graphics API
    * Chart, Ribbon, Dock Container
* GacStudio.exe
