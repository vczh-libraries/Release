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

## Github Copilot with Visual Studio Code

Both `AGENTS.md` and `CLAUDE.md` are prepared so that copilot/codex/claude coding agent follow the same instruction.

The follow keywords maintain design documents in `.github/TaskLogs`, anything except `Copilot_Scrum.md` is not tracked by git, you can change the `.gitignore` in that folder if you like.
- Use `scrum problem ...` to start a new scrum, `scrum update ...` to update the scrum.
- Use `design problem next` to fetch one task from the scrum.
- Use `design update ...` to update the design.
- Use `plan problem` to make detailed plan from the design.
- Use `plan update ...` to update the plan.
- Use `summary problem` to summary all code changes from the plan and ready to execute.
- Use `summary update ...` if the summarization has tiny mistakes, you could revert the summariziation completely and do `plan update ...` again.
- Use `execute` to execute the summarization and build your project.
- Use `verify` to build and test your project.
- Use `ask ...` to answer your question.
- Use `code ...` to code, build and test your project, without walking through all design documents.
- More use case in `AGENTS.md`.

You can copy the whole `.github` folder to your own repo.
- These prompts tells the coding agent how to work with msbuild. 
  - You need to prepare `VLPP_VSDEVCMD_PATH` and `CDBPATH` environment variable
  - Search in `.github/Scripts` and read comments about them.
- `.vscode/tasks.json` needs to be ready, see [tasks.example.json](.vscode/tasks.example.json) for details.
- Update `.github/Project.md` to describe where the source code is.
- `.github/copilot-instructions.md` and detailed guidelines follow the pattern in all repos in this github organization, feel free to change.

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
