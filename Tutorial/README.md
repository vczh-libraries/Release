# Tutorial

[http://vczh-libraries.github.io/demo.html](http://vczh-libraries.github.io/demo.html)

`<Release repo>/Tutorial/GacUI_Windows/RawClock` demonstrates owner drawing with `<Raw/>` and native Windows rendering APIs. Open `<Release repo>/Tutorial/GacUI_Windows/GacUI_Windows.sln` and build `RawClock`. Run `RawClock.exe` for Direct2D, or `RawClock.exe /Gdi` for GDI. The shared Windows tutorial launcher also accepts `/Gdi` in other GacUILite tutorials.

The clock's XML resource owns the raw element and updates its `Data` as `HH:mm:ss` once per second. The C++ attachment selects `GuiDirect2DElement` or `GuiGDIElement` and draws the same clock with that backend. Direct2D brushes follow render-target lifetime, and GDI drawing restores the device context state. RawClock is maintained independently of FullControlTest after its initial copy.

The BlackSkin showcase's FullControlTest XML and Windows native raw-clock attachment stay synchronized from `<GacUI repo>` by `<Tools repo>/Tools/BuildRelease.ps1`; its launcher enables that attachment only on Windows.

`<Release repo>/Tutorial/GacUI_Layout/Responsive3` demonstrates Easy Layout with responsive account and movie lists. Resize the window to switch account rows between icons with names, icons only, and a menu, and movie rows between detailed and compact views.

Open `<Release repo>/Tutorial/GacUI_Layout/GacUI_Layout.sln` and build `Responsive3` in Debug or Release for Win32 or x64. Its main window is defined in `<Release repo>/Tutorial/GacUI_Layout/Responsive3/UI/EasyLayoutResponsiveWindow.xml`; `<Release repo>/Tutorial/GacUI_Layout/Responsive3/UI/EasyLayoutResponsiveTemplates.xml` defines the item templates. The launcher locates `<Release repo>/Tutorial/GacUI_Layout/UIRes/Responsive3.bin` from the solution's standard executable output directories.

Responsive3 is maintained independently after its initial copy from FullControlTest. The release resource build generates its C++ and binary resources from the tutorial's XML files; UpdateRelease does not copy its sources from FullControlTest.
