# TODO

## Working On
* Workflow
    * Attributes
    * **Workflow to C++ code generation with hint**.
        * Types and other symbols, which are reported not supported in C++, cannot be used.
        * Generate reflection code, protected by VCZH_DEBUG_NO_REFLECTION.

## Comming Soon
* GacUI
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
    * Add G4, Retire G2 [(reference)](http://www.gaclib.net/#~/Tutorial)
    
## Wait For A Few Releases
* GacUI Resource
    * InheritableCustomWindow
    * InheritableCustomControl
    * GuiCustomControl::SetContainerComposition // using a special syntax
    * `<ref.Event/>`
    * `<ref.Component/>` // readonly property with -eval
    * Strong-typed template checking (in XML, instead of delaying until compiling generated workflow script)
    * Report errors with XML row/column number
* GacUI
    * New predefined control templates, written in XML generated C++ code.
    * Retire Win7/Win8 control templates, rewrite them in tutorials.
* GacGen.exe
    * Enable linking to external symbols

## Low Property
* Workflow
     * async, delay, yield (provider written in C++).
* GacUI Resource
    * InstanceStyle:Replace
    * Visual State, State Machine, Animation
    * ev.Event-(eval|async|delayed)
* GacUI
    * Make ItemSource from constructor argument to property
    * Embedded Languages: Colorizer, AutoComplete
    * Abstract Graphics API
    * Chart, Ribbon, Dock Container
* GacStudio.exe
