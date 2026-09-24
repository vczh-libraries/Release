# Using Tools

`UiaListApp` is a Windows UI Automation inspector. It lists processes and windows, captures a window's UI tree, and lets you inspect nodes, properties and supported actions. See the [UiaListApp usage guide](../.github/KnowledgeBase/KB_GacUI_Design_UiaList.md).

`GitTui` shows a Git repository's working-tree changes and local branch history in a terminal. Git must be on `PATH`; launch the tool from the repository or one of its subdirectories. Use **CHANGES** for staged, unstaged and new files and **HISTORY** for commits. Its explicit pull commands modify the repository. See the [GitTui usage guide](../.github/KnowledgeBase/KB_GacUI_Design_GitTui.md) for navigation and command behavior.

## Windows

- Open `Executables/Executables.sln` in Visual Studio and build `Release` with `x86`.
- Run `CopyExecutables.ps1`.
- New files will be available in this folder:
  - CodePack.exe
  - CppMerge.exe
  - GacGen.exe
  - GlrParserGen.exe
  - UiaListApp.exe
  - GitTui.exe

The solution also supports `Debug` and `x64`. `CopyExecutables.ps1` deploys the six `Release|x86` executables and reports an error if any is missing.

Run `UiaListApp.exe` to choose a process and window to inspect. Run `GitTui.exe` in an interactive terminal with a valid console input and output; redirected streams cannot host its interface.

## Linux/macOS

- Build the native TUI provider libraries in the sibling `wGac` (Linux) or `iGac` (macOS) checkout first. GitTui's `vmake` uses `wGac/build/WGacTuiControlTest/libWGacTui.a` and `wGac/build/WGacShared/libWGac.a`, or `iGac/build/MacTuiControlTest/libGacOSXTui.a` and `iGac/build/MacShared/libGacOSX.a`. Linux also needs the provider's `pkg-config` dependencies.
- Run `BuildExecutables.sh`. It generates GitTui's makefile from `Executables/GitTui/vmake` using this repository's `.github/Ubuntu/build.sh` and builds the tool. `WGAC_ROOT`/`WGAC_BUILD` or `IGAC_ROOT`/`IGAC_BUILD` can override the provider locations when invoking make.
- New files will be available in this folder:
  - CodePack
  - CppMerge
  - GacGen
  - GlrParserGen
  - GitTui

`UiaListApp` is Windows-only. Launch `GitTui` inside the repository to inspect, in an interactive terminal.

**NOTE**: Optimization is not turned on at this moment, tool performance could be slow especially for GacGen. You could change the makefile if you need to.

## Updating packaged sources

The two applications are maintained in the sibling GacUI repository under `Tools/UiaList` and `Tools/GitView`. From the monorepo, run `Tools/Tools/Build.ps1 -Project UpdateRelease` to copy their sources, build the executables, and deploy them here. Do not edit the copied C++ files in this repository.

`Executables/UiaListApp/UiaList` and `Executables/GitTui/GitView` preserve the library source layout; each application's entry point is in its `Source` directory. The UiaListApp copy step also supplies `SharedArguments.h` and adjusts its one external test-tree include.
