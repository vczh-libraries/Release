# Sample Applications for Document

http://vczh-libraries.github.io/doc/current/gacui/home.html

## Steps to Try

### Modify a Resource File

- All resource files are in `XmlRes\*\Resource.xml`
- All compiled binaries are in `UIRes\*\*.bin`
  - C++ files are not generated in these samples
  - Compiled Workflow script are contained in binaries
  - They are platform dependent, x86 and x64 application doesn't load the same binary

### Build

- Go to folder `XmlRes`
- Run `..\..\..\Tools\GacClear.ps1 -FileName GacUI.xml`
  - Only run this command if you want to rebuild everything, or you will get a incremental build
- Run `..\..\..\Tools\GacBuild.ps1 -FileName GacUI.xml`

### Execute

- Open GacUI.sln
- Build the solution
- Run project `RunResource`
  - If you want to load `XmlRes\kb_elements\Resource.xml`, set the command line arguments to `kb_elements`.
  - Multiple resource names are separated by `;`, not by multiple arguments. Resources will be loaded in the specified order.
    - For example: `control_datagrid_base;control_datagrid_plaintext`.
