# Release
Release folder of all projects.

**Read the [LICENSE](https://github.com/vczh-libraries/Release/blob/master/LICENSE.md) first.**

**Read [GacUI website](http://vczh-libraries.github.io/) or [the mirror website](http://gaclib.net) for more information.**

The deepwiki website [indexed GacUI](https://deepwiki.com/vczh-libraries/GacUI), it provides high level ideas with acceptable accuracy, but it is problematic in details.

Executables in `Tools` are no longer committed to this repo. **Read [Tools/README.md](Tools/README.md) for building tools.**

Download code from [public releases](https://github.com/vczh-libraries/Release/releases) to get the latest stable release. Code from this repo is also usable but I don't make any promise. I will only make a new release when I think the code is ready to update.

## Synchronized latest releases:

- **GacUI**: [1.2.11.0](https://github.com/vczh-libraries/Release/releases/tag/1.2.11.0)
- **iGac**: Not specified yet
- **gGac**: [1.2.11.0](https://github.com/vczh-libraries/gGac/commit/5a6dc87d03d0616080d38dd344d13b1d423b0127)

When **iGac** and **gGac** targets on a certain **GacUI** version, **iGac** and **gGac** will use the same version number as a tag to the commits.
  - A **GacUI** release will always be `X.Y.Z.0`, the last digit increases when only small bug fixing is introduced.
  - If **iGac** and **gGac** have multiple releases based on the same **GacUI** release, only the last digit will change.

## Visual Studio Extension

Copy [Vlpp.natvis](https://github.com/vczh-libraries/Release/blob/master/Import/vlpp.natvis) to Visual Studio's visualizers folder.

For example, VS2022's default visualizers folder will be **C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Packages\Debugger\Visualizers**.

## Github Copilot with Visual Studio Code

The `prompts` folder copies all task in Visual Studio github copilot recognized format.
- [0-scrum.prompt.md](.github/prompts/win-0-scrum.prompt.md) creates `Copilot_Scrum.md`.
  - Use `# Problem` for the problem.
  - Convert your feature request to multiple tasks.
- [1-design.prompt.md](.github/prompts/win-1-design.prompt.md) creates `Copilot_Task.md`.
  - Use `# Problem` for the problem. It will find the first unfinished task in `Copilot_Scrum.md`.
  - Create a more detailed design for the task.
- [2-planning.prompt.md](.github/prompts/win-2-planning.prompt.md) creates `Copilot_Planning.md`.
  - Propose actual code change from the detailed design.
- [3-summarizing.prompt.md](.github/prompts/win-3-summarizing.prompt.md) creates `Copilot_Execution.md`.
  - Extract proposed code change.
- [4-execution.prompt.md](.github/prompts/win-3-execution.prompt.md) edit source files according to `Copilot_Execution.md`.
  - Apply proposed code change, ensure it compiles.
- [5-verifying.prompt.md](.github/prompts/win-5-verifying.prompt.md) compiles and runs unit test.
  - Ensure passing all test cases.
- You can always use `# Update` in any phrase for adjustment.

Example:
```markdown
#win-0-scrum.prompt.md <-- vscode will convert it to a #file tag, otherwise you are not typing it correctly
I would like to do this feature. Here are proposed task splitting:
- Complete the source code
- Complete unit test
```

You can copy the whole `.github` folder to your own repo.
`.vscode/tasks.json` needs to be ready, see [tasks-example.json](.vscode/tasks-example.json) for details.

## Content of This Project

- **Import** Gaclib source code
  - **Skins** Predefined control templates. You will need to call `vl::presentation::theme::RegisterTheme` to set a default skin before creating any controls. Read [WinMain.cpp](https://github.com/vczh-libraries/Release/blob/master/Tutorial/Lib/GacUILite/WinMain.cpp) for details.
- **Tools**
  - **GacGen.exe** GacUI resource compiler and C++ code generator for x86 and x64
  - **CppMerge.exe** Merge GacUI generated code for x86 and x64 to architecture-independent code
  - **GlrParserGen.exe** General LR parser to C++ code generator
  - **CodePack.exe** Merge a group of C++ source files into multiple pairs of .h/.cpp big files
  - **GacBuild.ps1** Do everything for you if you don't want to understand build steps. This one builds multiple resource xml files at the same time. Read the comment for more information.
  - **GacClear.ps1** Force `GacBuild.ps1` rebuilding all resource xml files for the next time.
- **Tutorial** Sample code
  - **Lib** Static library projects for all tutorials
  - **GacUI_HelloWorlds** Different ways to create a GacUI hello world project
  - **GacUI_Layout** Demo how to use GacUI layout
  - **GacUI_Controls** Demo how to use GacUI controls
  - **GacUI_ControlTemplate** Demo how to create control templates (skin) for GacUI controls
  - **GacUI_Xml** Demo how to author GacUI XML resource file
  - **GacUI_Windows** Demo how to interact with native Windows OS features.

Image files are not owned by this repo or organization except for GacUI logos.

## Creating a GacUI app using CMake

**WARNING: it is not maintained by members in **vczh-libraries** organization, please check the version number before using.**

Third party project for GacUI 1.0: https://github.com/mangosroom/GacUI-CMake-support

## Building using vcpkg

**WARNING: it is not maintained by members in **vczh-libraries** organization, please check the version number before using.**

You can build and install vlpp using [vcpkg](https://github.com/Microsoft/vcpkg/) dependency manager:

  - git clone https://github.com/Microsoft/vcpkg.git
  - cd vcpkg
  - ./bootstrap-vcpkg.sh  # ./bootstrap-vcpkg.bat for Windows
  - ./vcpkg integrate install
  - ./vcpkg install vlpp

Source files in the "Import" folder are grouped by different features defined in [CMakeLists.txt](./Import/CMakeLists.txt).

The vlpp port in vcpkg is kept up to date by Microsoft team members and community contributors. If the version is out of date, please [create an issue or pull request](https://github.com/Microsoft/vcpkg) on the vcpkg repository.
