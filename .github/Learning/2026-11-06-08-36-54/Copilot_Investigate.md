# !!!INVESTIGATE!!!

# PROBLEM DESCRIPTION

- Add `Release/Tutorials/GacUI_Layout/Responsive3` with the main window in `EasyLayoutResponsiveWindow.xml` and other necessary files from `FullControlTest`.
  - That file is in `GacUI` repo, the window is pretty isolated, you can mainly copy them with a little twist. Unlike `FullControlTest` to `GacUI_ControlTemplate/BlackSkin`, this new `Responsive3` will be permanently detach from `FullControlTest`, so `Build.ps1 -Project UpdateRelease` do not need to handle the copying. Create the vcxproj and copy/fixed source files by yourself. `Build.ps1 -Project UpdateRelease` will generated C++ files out of copied XML resources.
  - Run `Build.ps1 -Project GacUI` and `Build.ps1 -Project Release` to make sure everything works.
  - commit and push all local changes.
  - Update the website and existing documents in `Release` repo (if any, I suspect no) to reflect the change, publish the website.

# TEST [CONFIRMED]

- Run `<Tools repo>/Tools/Build.ps1 -Project GacUI` and `-Project Release`; require successful resource generation, unit tests and tutorial builds.
- Build `<Release repo>/Tutorial/GacUI_Layout/GacUI_Layout.sln` in Debug and Release for x64 in addition to the Win32 builds included above.
- Check resource links and generated project inventory. Verify the tutorial's responsive transitions using available native UI automation.
- Build and test `<WebsiteSource repo>`, export both website packages and markdown, and verify the published tutorial links.

## Results

- Source inventory checks passed: all linked XML and image resources exist, the project has Debug/Release configurations for Win32/x64, and the copied templates match FullControlTest. The window differs only in its standalone title.
- Website build, all 57 tests, both website exports and the markdown export passed. Five updated pages passed local and live browser checks, including visible Responsive3 links and no JavaScript page errors.
- Website publication completed successfully. Existing WebAssembly files were preserved, and exported manual updates were synchronized to the canonical documentation and downstream repositories.
- `<Tools repo>/Tools/Build.ps1 -Project GacUI` passed completely, including the full Win32/x64 rebuilds, metadata generation, metadata validation, unit tests, release-tool builds, skin generation and CodePack. Its regenerated release sources were committed and pushed separately from the snapshots.
- `<Tools repo>/Tools/Build.ps1 -Project Release` passed completely: release executables, Workflow tutorial builds, all XML resource generation and all Win32 Debug/Release tutorial builds. Responsive3 has its five generated C++ files and resource binary, with both `ViewSizes` assignments emitted correctly. This resolves the preliminary rejection by the old release tools.
- The first Release attempt stopped in the existing BlackSkin Debug build: the newly copied FullControlTest templates reference `darkskin::TabHeaderTemplate` and `darkskin::Theme`, but the copied manifest only included `GacUI.h`. Updated the BlackSkin packaging step to add the packaged DarkSkin header before regenerating, then reran the full Release command.
- The rerun generated the missing DarkSkin include and passed the ControlTemplate Debug and Release builds, confirming the packaging fix.
- The layout solution, including Responsive3, passed focused Debug builds for Win32 and x64 and the additional Release x64 build with zero warnings and zero errors. Together with the full Release pipeline, all four configurations passed.
- The Windows Computer Use helper rejected both launch attempts with `GetCursorPos failed: Access is denied. (0x80070005)`. The repository execution wrapper subsequently launched Responsive3 successfully, and the windowless UiaList CLI connected through native UIA. At window widths 240, 460 and 700, UIA confirmed the account menu, 64-pixel account list and 230-pixel account list, respectively; movie rows switched from 26 to 106 pixels. Selecting an account and scrolling to the last of 24 movies succeeded without a runtime-error dialog.
- Reviewed and separately committed the Windows unit-test snapshots: generated file-dialog paths, the current calendar month and UTF-16 caret positions explain the retained differences. The temporary Win32 scroll-navigation ID differences disappeared after the x64 run.
- Native UIA also confirmed that selecting Oxford University Press from the narrow menu changes the shared account-list selection when widened. Movie rows returned to a consistent compact height after scrolling to the end and shrinking. The x64 executable independently loaded its resource and exposed the expected 24 movie items. The Win32 and x64 processes both exited with code zero through UIA Window.Close and Cancel invocation, respectively; no runtime-error dialog appeared. The menu exposes Invoke but does not expose its selection image as a UIA selection property, so shared selection was verified in the list after widening.

# PROPOSALS

- No.1 Independently maintained Responsive3 tutorial [CONFIRMED]

## No.1 Independently maintained Responsive3 tutorial

Use the existing `<Release repo>/Tutorial/GacUI_Layout` directory. Copy the two responsive Easy Layout XML files and their image resources from FullControlTest, add a standalone resource manifest and launcher, and register a new project in the layout solution. Resource discovery already includes the new manifest; do not add a copying rule to UpdateRelease.

### CODE CHANGE

- Add Responsive3 source XML, images, project files and launcher; generate its C++ and resource binary with the existing release pipeline.
- Update the existing tutorial README, website demo listing and responsive-layout documentation.
- Publish the website and synchronize exported manuals through the documented workflow.
- Fix BlackSkin's existing UpdateRelease packaging step to set its copied manifest's `Cpp/NormalInclude` value to `GacUI.h;Skins/DarkSkin/DarkSkin.h`, matching the existing TuiSkin include override. This does not add a Responsive3 copying rule.

### CONFIRMED

Responsive3 contains its own window, templates, images, resource manifest and launcher. The existing resource discovery generates its C++ and binary resources without copying from FullControlTest. Both requested full build pipelines passed, and the layout solution passed Debug/Release for Win32/x64. Native UIA verified layout transitions, scrolling, account selection across the menu/list transition, resource loading from both executable output layouts and clean shutdown.

The website and tutorial documentation describe the new sample and its independent maintenance. All 57 website tests passed, the five changed pages passed local and live browser checks, and GitHub Pages publication succeeded. The release regeneration also exposed and verified the small BlackSkin packaging correction described above. Generated GacUI sources, Windows snapshots, release resources and documentation were committed and pushed in their owning repositories.
