# Release
Release folder of all projects.

**Read the [LICENSE](https://github.com/vczh-libraries/Release/blob/master/LICENSE.md) first.**

**Read [GacUI website](http://vczh-libraries.github.io/) or [the mirror website](http://gaclib.net) for more information.**

The [![Ask DeepWiki](https://deepwiki.com/badge.svg)](https://deepwiki.com/vczh-libraries/GacUI) website [indexed GacUI](https://deepwiki.com/vczh-libraries/GacUI), it provides high level ideas with acceptable accuracy, but it is problematic in details.

Executables in `Tools` are no longer committed to this repo. **Read [Tools/README.md](Tools/README.md) for building tools.**

Download code from [public releases](https://github.com/vczh-libraries/Release/releases) to get the latest stable release. Code from this repo is also usable but I don't make any promise. I will only make a new release when I think the code is ready to update.

## Synchronized latest releases:

### 1.3.0.0

- [Windows](https://github.com/vczh-libraries/Release/releases/tag/1.3.0.0)
- [Linux Wayland](https://github.com/roodkcab/wGac/commit/c1d32b7bf447460a273a426fccce914d0a652107)
- [macOS](https://github.com/vczh-libraries/iGac/commit/5076a33a731523bd74d6ac922a370b3a515931a4)

### 1.2.11.0

- [Windows](https://github.com/vczh-libraries/Release/releases/tag/1.2.11.0)
- [Linux XWindow](https://github.com/vczh-libraries/gGac/commit/5a6dc87d03d0616080d38dd344d13b1d423b0127)
  - XWindow version is likely not being maintained in the near future. Please use Wayland version if possible.

## Visual Studio Extension

Copy [Vlpp.natvis](https://github.com/vczh-libraries/Release/blob/master/Import/vlpp.natvis) to Visual Studio's visualizers folder.

For example, VS2022's default visualizers folder will be **C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Packages\Debugger\Visualizers**.

## Using Coding Agents

Both `AGENTS.md` and `CLAUDE.md` are prepared so that copilot/codex/claude coding agent follow the same instruction.

The follow keywords maintain design documents in `.github/TaskLogs`, anything except `Copilot_Scrum.md` is not tracked by git, you can change the `.gitignore` in that folder if you like.
- Use `scrum problem ...` to start a new scrum backlog `Copilot_Scrum.md` with multiple tasks, `scrum update ...` to update.
- Use `design problem next` to fetch one task from the scrum and finish `Copilot_Task.md`, `design update ...` to update.
- Use `plan problem` to make detailed plan from the design and finish `Copilot_Planning.md`, `plan update ...` to update.
- Use `summary problem` to summary all code changes from the plan in `Copilot_Execution.md`.
- Use `summary update ...` if `Copilot_Execution.md` has tiny mistakes. To make a complex update, it is recommended to revert `Copilot_Execution.md` completely and do `plan update ...` again.
- Use `execute` to execute `Copilot_Execution.md` and build your project.
- Use `verify` to build and test your project.
- Use `ask ...` to answer your question.
- Use anything else to raise a feature request, it will code, build and test your project automatically, without walking through all design documents.
- More use cases in `AGENTS.md`.

You can copy the whole `.github` folder to your own repo.
- `.github/KnowledgeBase` contains detailed documentation for the library, they will be read without having to being explicitly mentioned.
- Prompt files tell the coding agent how to work with `msbuild` and `cdb` (the CLI version of WinDBG). 
  - You need to prepare `VLPP_VSDEVCMD_PATH` and `CDBPATH` environment variable
  - Search in `.github/Scripts` and read comments about them.
  - Building/testing/debugging is doable.
- Find `settings.example.json` and `tasks.example.json` for references, but prompts do not use `tasks.json`.
- Update `.github/Project.md` to describe where the source code is.
- `.github/copilot-instructions.md` and `.github/Guidelines` follow the pattern in all repos in this github organization, feel free to change.

**NOTICE**: The guideline about running your vcxproj is customized for the unit test framework in GacUI, a more general version is comming. Feel free to change.

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
