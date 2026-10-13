# !!!INVESTIGATE!!!

# PROBLEM DESCRIPTION

- Add `Release/Tutorials/GacUI_Layout/Responsive3` with the main window in `EasyLayoutResponsiveWindow.xml` and other necessary files from `FullControlTest`.
  - That file is in `GacUI` repo, the window is pretty isolated, you can mainly copy them with a little twist. Unlike `FullControlTest` to `GacUI_ControlTemplate/BlackSkin`, this new `Responsive3` will be permanently detach from `FullControlTest`, so `Build.ps1 -Project UpdateRelease` do not need to handle the copying. Create the vcxproj and copy/fixed source files by yourself. `Build.ps1 -Project UpdateRelease` will generated C++ files out of copied XML resources.
  - Run `Build.ps1 -Project GacUI` and `Build.ps1 -Project Release` to make sure everything works.
  - commit and push all local changes.
  - Update the website and existing documents in `Release` repo (if any, I suspect no) to reflect the change, publish the website.

# TEST

- Run `<Tools repo>/Tools/Build.ps1 -Project GacUI` and `-Project Release`; require successful resource generation, unit tests and tutorial builds.
- Build `<Release repo>/Tutorial/GacUI_Layout/GacUI_Layout.sln` in Debug and Release for x64 in addition to the Win32 builds included above.
- Check resource links and generated project inventory. Verify the tutorial's responsive transitions using available native UI automation.
- Build and test `<WebsiteSource repo>`, export both website packages and markdown, and verify the published tutorial links.

# PROPOSALS

- No.1 Independently maintained Responsive3 tutorial

## No.1 Independently maintained Responsive3 tutorial

Use the existing `<Release repo>/Tutorial/GacUI_Layout` directory. Copy the two responsive Easy Layout XML files and their image resources from FullControlTest, add a standalone resource manifest and launcher, and register a new project in the layout solution. Resource discovery already includes the new manifest; do not add a copying rule to UpdateRelease.

### CODE CHANGE

- Add Responsive3 source XML, images, project files and launcher; generate its C++ and resource binary with the existing release pipeline.
- Update the existing tutorial README, website demo listing and responsive-layout documentation.
- Publish the website and synchronize exported manuals through the documented workflow.
