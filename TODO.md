# TODO

See `TODO.md` in each repos.

## Known Issue

- Check if envvar "UseMultiToolTask" is "True" in Build.ps1

## Roadmap

- Reimplement C++ parser in vczh-libraries/Document using this project.
  - Move all test cases to `BuiltIn_CppDoc`.
- Refactor vczh-libraries/Document to generate document using the new parser but skip the code index temporary.
- Revisit Hero DB (prolog is a bad idea, use a simple FPL with additional `query` syntax for querying)

## Ubuntu Development Environment

- `vmake` recognizes referenced projects automatically.
- `vmake` generates multiple targets to share libs.
