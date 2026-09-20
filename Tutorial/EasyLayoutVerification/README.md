# Easy-layout tutorial verification

The migration rewrites 41 static arrangements: 32 tables (10 as docking layouts and 22 as grids) and nine stacks. It updates **19 existing XML files and adds three tutorial-owned editor XML files**. Seventeen existing files contain layout changes; the other two update resource links.

All 27 original XML files under GacUI_Controls were reviewed, together with the linked document-editor definitions. The resulting 30 XML files preserve control attributes, bindings, names and script tokens. Generated UI/Source files were regenerated through Tools/GacBuild.ps1 and Tutorial/GacUI.xml.

## Converted arrangements

| Tutorial/resource | Arrangements | Coverage |
| --- | ---: | --- |
| AddressBook | 4 | Both group-box contents and the new-folder/new-contact forms; preserve the 3-pixel content inset. |
| Animation | 1 | Static gradient page; retain the animated bounds on the complex-animation page. |
| ColorPicker | 2 | Main form and swatch/text template; preserve padding 10 and the 16/3-pixel swatch tracks. |
| ColorPicker2 | 2 | Main form and item template; preserve the repeated flow, shared-size groups, 2-pixel flow spacing and 1-pixel inset. |
| ContainersAndButtons | 5 | Group-box columns, three button stacks and the scroll-container grid. |
| DataGrid | 3 | Main layout, category template and date-filter form. |
| Dialogs | 7 | All four configuration pages and the file-dialog checkbox/button stacks. |
| DocumentEditor | 3 | Shared editor arrangement and both hyperlink-form tables. |
| DocumentEditorRibbon | 2 | Style-item template and search stack. |
| GlobalHotKey | 1 | Menu/content docking. |
| ListControls | 4 | TextList, ListView and TreeView pages, including the action-button stack. |
| Localization | 1 | Locale selector and localized list. |
| MenuVisibility | 1 | Menu/content docking. |
| ProgressAndAsync | 1 | Progress/action row and output area. |
| QueryService | 2 | Centered service control and its editor/label arrangement. |
| TriplePhaseImageButton | 2 | Button template and demo stack. |

DocumentComponents.xml, DocumentEditorBase.xml and DocumentEditorRibbon.xml are now owned by these tutorials. Their resource manifests link the local copies, and their Visual Studio project inventories include them. Toolbar images and the unchanged DocumentEditorToolstrip definition remain shared with the showcase.

Bounds wrappers preserve the old external alignment, cell/internal margins, minimum-size boundaries and control alignment. Explicit padding and track options retain each tutorial's spacing. Empty grid descriptors preserve unused tracks.

The native AddressBook table remains because its ColumnSplitter operates on that table. The calculator retains its table with spans on both axes and its Cell/Button style selector. Specialized repeated/shared-size compositions and animated bounds also remain. Win11ToolstripMenu, the document-toolstrip wrapper, the ListControls manifest and its four image/script XML resources have no static table/stack arrangement to replace.

## Results

- Resource generation discovers all 52 tutorial resources. All 19 GacUI_Controls resource projects regenerate successfully for x86 and x64, with no Errors.txt.
- GacUI_Controls builds with zero warnings/errors in Debug Win32, Debug x64 and Release x64.
- All 18 applications match at initial, smaller, larger and restored sizes: **72 comparisons** of element descriptions, label text, document content, control types, bounds and ancestor-bound intersections. The archived original executables also reproduce all 72 earlier baseline states. Localization's current time is normalized.
- **66 additional state comparisons** cover address-book forms, text entry and splitter movement; gradient animation; both color palettes and selections; checkbox/scroll-container behavior; DataGrid views; dialog configuration pages; both editor variants, ribbon tabs/search and menus; populated/filtered lists and list views; localization; progress/download; title binding; image-button states; and context menus. All geometry matches. The intermediate gradient color varies with elapsed animation time; the settled color matches. Downloaded document content differs only in Microsoft's per-request CV token, which is normalized.
- Windows UI Automation from an MTA client passes ColorPicker expansion/Maroon selection/collapse, QueryService ValuePattern editing and title binding, ListControls InvokePattern adding items, and ribbon Insert/Edit SelectionItemPattern switching.
- All 18 final Release x64 applications open native windows, have no requested-port or process-owned listener, and exit 0 on normal close. Successful Debug checks also close with exit 0.

An early HTTP probe exposed a race in the previous Debug launcher: the request could resolve the automation service before optional utility-service registration completed. CDB located the exception in GuiInitializeUtilities, before GuiMain. WinMain.cpp now schedules endpoint startup on the native main-thread queue after service substitution. The rebuilt applications pass the subsequent launch and interaction checks. This does not change layout or enable automation in Release builds.

## Evidence and limits

The earlier JSON baselines and automation records are available in Release commit e179f7e7. The requested separate cleanup commit removes the 206 JSON files introduced there. New before/after captures were kept outside the repository in a temporary verification directory.

Capture.ps1 supports -OutputDirectory to keep future captures outside the checkout. It records the renderer, skin, DPI, actual window size and commands, and checks for native runtime-error dialogs. To compare versions, use the same Windows Direct2D renderer, dark skin, Debug x64, 96 DPI and interaction sequence; compare rendered content and geometry while ignoring composition topology and transient IDs.

Pixel-image comparison remains unavailable: PrintWindow returns black images in this session, and earlier screen-capture alternatives failed. Geometry, unchanged element properties/assets and live interaction checks provide the comparison described above; no pixel-identical screenshot claim is made.

Automatic approval review rejected an additional DataGrid-filter/editor-hyperlink/calculator interaction command and a repeated-startup stress command, returning only "blocked by policy". They did not run and were not retried. The previously blocked default-port and Win32 live checks likewise remain unclaimed. These limitations do not change the successful build, geometry and interaction results above.
