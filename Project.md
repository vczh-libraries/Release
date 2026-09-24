# Projects to Work on

Take a look at [the GacUI repo example](https://github.com/vczh-libraries/GacUI/blob/master/Project.md) for better understanding about how to prepare this file.

## Content of This Project

### Tools

`Tools/Executables/Executables.sln` builds the release executables. See [Tools/README.md](Tools/README.md) for building and copying them into `Tools`.

- [UiaListApp](.github/KnowledgeBase/KB_GacUI_Design_UiaList.md) is a Windows UI Automation inspector for discovering application windows, inspecting nodes and properties, and invoking supported actions.
- [GitTui](.github/KnowledgeBase/KB_GacUI_Design_GitTui.md) browses Git working-tree diffs and local branch history in a terminal on Windows, Linux and macOS. Launch it inside the repository to inspect. Its explicit pull commands can update that repository.

Their source files are maintained in `GacUI/Tools/UiaList` and `GacUI/Tools/GitView` and copied here by `Tools/Tools/Build.ps1 -Project UpdateRelease` in the sibling Tools repository. Edit the owning sources and run the release update instead of editing the copied files.
