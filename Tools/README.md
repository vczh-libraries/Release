# Using Tools

## Windows

- Open `Executables/Executables.sln` in Visual Studio and build `Release` with `x86`.
- Run `CopyExecutables.ps1`.
- New files will be available in this folder:
  - CodePack.exe
  - CppMerge.exe
  - GacGen.exe
  - GlrParserGen.exe

## Linux

- Run `BuildExecutables.sh`
- New files will be available in this folder:
  - CodePack
  - CppMerge
  - GacGen
  - GlrParserGen

**NOTE**: Optimization is not turned on at this moment, tool performance could be slow especially for GacGen. You could change the makefile if you need to.

## macOS

(editing...)
