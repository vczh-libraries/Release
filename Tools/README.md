# Using Tools

`UiaListApp` is the graphical Windows UI Automation inspector; `UiaListCli` exposes the same shared services through a sequential UTF-8 JSON-line protocol. It lists processes and windows, captures a window's UI tree, and lets you inspect nodes, properties and supported actions. See the [UiaListApp usage guide](../.github/KnowledgeBase/KB_GacUI_Design_UiaList.md).

`GitTui` shows a Git repository's working-tree changes and local branch history in a terminal. Git must be on `PATH`; launch the tool from the repository or one of its subdirectories. Use **CHANGES** for staged, unstaged and new files and **HISTORY** for commits. Its explicit pull commands modify the repository. See the [GitTui usage guide](../.github/KnowledgeBase/KB_GacUI_Design_GitTui.md) for navigation and command behavior.

## Windows

- Open `Executables/Executables.sln` in Visual Studio and build `Release` with `x86`.
- Run `CopyExecutables.ps1`.
- New files will be available in this folder:
  - CodePack.exe
  - CppMerge.exe
  - GacGen.exe
  - GacBuild.exe
  - GlrParserGen.exe
  - UiaListApp.exe
  - UiaListCli.exe
  - GitTui.exe

The solution also supports `Debug` and `x64`. `<Release repo>/Tools/CopyExecutables.ps1` deploys the eight `Release|x86` executables and reports an error if any is missing.

Run `UiaListApp.exe` to choose a process and window to inspect. Run `GitTui.exe` in an interactive terminal with a valid console input and output; redirected streams cannot host its interface.

## Linux/macOS

- Build the native TUI provider libraries in the sibling `wGac` (Linux) or `iGac` (macOS) checkout first. GitTui's `vmake` uses `wGac/build/WGacTuiControlTest/libWGacTui.a` and `wGac/build/WGacShared/libWGac.a`, or `iGac/build/MacTuiControlTest/libGacOSXTui.a` and `iGac/build/MacShared/libGacOSX.a`. Linux also needs the provider's `pkg-config` dependencies.
- Run `<Release repo>/Tools/BuildExecutables.sh`. It clean-builds all six tools using their prepared makefiles in `<Release repo>/Tools/Executables` and copies the binaries to this folder. `WGAC_ROOT`/`WGAC_BUILD` or `IGAC_ROOT`/`IGAC_BUILD` can override the provider locations when invoking make.
- New files will be available in this folder:
  - CodePack
  - CppMerge
  - GacGen
  - GacBuild
  - GlrParserGen
  - GitTui

`UiaListApp` and `UiaListCli` are Windows-only. Launch `GitTui` inside the repository to inspect, in an interactive terminal.

`BuildExecutables.sh` always builds the tools with `-O2` optimization.

## Resource generation

Use `<Release repo>/Tools/GacBuild.ps1 -FileName <driver-xml> [-Dump]` for dependency-ordered incremental builds, or `<Release repo>/Tools/GacGen.ps1 -FileName <resource-xml> [-MappingFileName <mapping>]` for one resource. On Linux/macOS, use the corresponding `<Release repo>/Tools/GacBuild.sh` and `<Release repo>/Tools/GacGen.sh` with the same arguments.

Both wrapper pairs call native GacBuild with explicit absolute paths to the adjacent GacGen and CppMerge. Relative resource and mapping paths resolve from the caller's working directory; quote paths containing spaces. Released GacGen requires adjacent `Reflection32.bin` and `Reflection64.bin` and uses those full metadata sets.

Generation stages both architectures under `<application repo>/<resource-xml>.log/x32` and `x64`, merges the C++ pairs while preserving user content, then copies the UTF-8 `Deploy.xml` inventories. Failures propagate as nonzero status and invalidate resource freshness for a retry. Standard binary caches drive incremental selection; clear them when only tools or production outputs change. See the [GacBuild/GacGen contract](../.github/KnowledgeBase/KB_GacUI_Design_GacGenAndGacBuild.md).

## Updating packaged sources

These applications are maintained in the sibling GacUI repository under `Tools/UiaList` and `Tools/GitView`. From the monorepo, run `Tools/Tools/Build.ps1 -Project UpdateRelease` to copy their sources, build the executables, and deploy them here. Do not edit the copied C++ files in this repository.

GacBuild and GacGen implementations are maintained in `<GacUI repo>/Tools/GacBuild` and `<GacUI repo>/Tools/GacGen`. The same release update copies both native GacBuild implementations. Their packaging project/filter files, Unix makefiles and Bash wrappers are maintained in Release and survive subsequent updates.

`Executables/UiaList`, `Executables/UiaListApp` and `Executables/UiaListCli` are sibling projects. Both UiaList frontends reference the common static library, which owns generated views, view models and dependency objects. Frontend entry points/manifests are directly in their project directories. The copier copies authored/generated sources byte-for-byte from GacUI and removes the obsolete `UiaListApp/UiaList` and `UiaListApp/Source` directories. Project/filter files remain owned here. `Executables/GitTui/GitView` and its `Source` entry point retain their existing layout.

Run `UiaListCli.exe` interactively or with redirected UTF-8 streams. Start with `Help-Command`, then `List-Process`. Each command completes before one JSON response is flushed. Read the [protocol and examples](../.github/KnowledgeBase/KB_GacUI_Design_UiaList.md#uialistcli-json-protocol) for typed arguments, generation-scoped IDs, returned elements, ranges and preview bytes.
