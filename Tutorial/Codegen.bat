pushd GacUI_HelloWorlds
pushd Xml\UI
call Codegen.bat
popd
pushd CppXml\UI
call Codegen.bat
popd
pushd MVVM\UI
call Codegen.bat
popd
popd
pushd GacUI_Layout
pushd Alignment\UI
call Codegen.bat
popd
pushd Stack\UI
call Codegen.bat
popd
pushd Table\UI
call Codegen.bat
popd
pushd TableSplitter\UI
call Codegen.bat
popd
pushd Flow\UI
call Codegen.bat
popd
pushd RichTextEmbedding\UI
call Codegen.bat
popd
popd
pushd GacUI_Controls
pushd ContainersAndButtons\UI
call Codegen.bat
popd
pushd TextEditor\UI
call Codegen.bat
popd
pushd ColorPicker\UI
call Codegen.bat
popd
popd
pushd GacUI_ControlTemplate
pushd BlackSkin\UI
call Codegen.bat
popd
popd
pushd GacUI_Xml
pushd Instance_Window\UI
call Codegen.bat
popd
pushd Instance_MultipleWindows\UI
call Codegen.bat
popd
pushd Instance_Control\UI
call Codegen.bat
popd
pushd Binding_Uri\UI
call Codegen.bat
popd
pushd Binding_Eval\UI
call Codegen.bat
popd
pushd Binding_Bind\UI
call Codegen.bat
popd
pushd Binding_Format\UI
call Codegen.bat
popd
pushd Binding_ViewModel\UI
call Codegen.bat
popd
pushd Event_Cpp\UI
call Codegen.bat
popd
pushd Event_Script\UI
call Codegen.bat
popd
pushd Event_ViewModel\UI
call Codegen.bat
popd
pushd Member_Field\UI
call Codegen.bat
popd
pushd Member_Property\UI
call Codegen.bat
popd
pushd Member_Parameter\UI
call Codegen.bat
popd
popd