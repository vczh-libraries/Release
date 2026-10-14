# Tutorial

[http://vczh-libraries.github.io/demo.html](http://vczh-libraries.github.io/demo.html)

`<Release repo>/Tutorial/GacUI_Layout/Responsive3` demonstrates Easy Layout with responsive account and movie lists. Resize the window to switch account rows between icons with names, icons only, and a menu, and movie rows between detailed and compact views.

Open `<Release repo>/Tutorial/GacUI_Layout/GacUI_Layout.sln` and build `Responsive3` in Debug or Release for Win32 or x64. Its main window is defined in `<Release repo>/Tutorial/GacUI_Layout/Responsive3/UI/EasyLayoutResponsiveWindow.xml`; `<Release repo>/Tutorial/GacUI_Layout/Responsive3/UI/EasyLayoutResponsiveTemplates.xml` defines the item templates. The launcher locates `<Release repo>/Tutorial/GacUI_Layout/UIRes/Responsive3.bin` from the solution's standard executable output directories.

Responsive3 is maintained independently after its initial copy from FullControlTest. The release resource build generates its C++ and binary resources from the tutorial's XML files; UpdateRelease does not copy its sources from FullControlTest.
