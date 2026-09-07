# CE 6.0 twin reconciliation (CE5 corpus × Windows Embedded CE 6.0)

Every CE 5.0 leaf harvested into `build/rows.json` (1175 pages across
69 manifests; the user-mode API reference surface of the Core OS
Reference and the GWES/GDI reference books) was resolved to its
Windows Embedded CE 6.0 twin by exact title match against the official
CE 6.0 TOC catalog, and all resolvable twins were **fetched in full**
and their Requirement rows compared to the CE 5.0 record.

Committed twin map: `docs/ce6-twins.tsv`
(`title<TAB>CE5-id<TAB>CE6-id`; CE6 id `-` = the CE5 title is a book
index page with no per-function leaf in the CE 6.0 tree).  The full
raw CE 6.0 pages are preserved in the corpus repository
(`kagurasumusun/wince-docs-corpus`, `pages6/`; see `docs/corpus.md`).

## Numbers

* CE 5.0 leaves harvested (manifest titles): 1175
* CE 6.0 twins resolved by title: **1133**
* CE 6.0 twins fetched (full page, Requirement rows read): **1133**
* Twins whose Requirement rows match the CE 5.0 record exactly
  (after case/punctuation normalization): **1039**
* Twins with a Requirement-row difference: **51** (table below)
* CE 5.0 leaves with no CE 6.0 twin: 42 — all are *book index pages*
  ("DLL Functions", "Exception Structures", "File I/O Enumerations",
  "Time Functions", …), i.e. TOC nodes, not API leaves.

## Category summary of the 51 differences

1. **Editorial wording of "not applicable" rows (28).**  The CE 5.0
   archive prints `OS Versions: Windows CE 2.10 and later` with a
   stray leading "OS" on the Dbgapi.h debug-zone/macro pages, prints
   `Link Library: none.` and prints `Header: Not applicable.` /
   "This structure … does not appear in any of the header files" /
   `Developer defined`; the CE 6.0 twins print the same facts as
   `2.10 and later`, empty/`None` library rows and `Developer
   Implemented`.  Same meaning; no header/def change.
2. **CE 6.0 kernel-mode library row `Nkstub.lib` (10, plus members).**
   CE 6.0 split user/kernel execution; pages whose function the CE 5.0
   archive links with `Coredll.lib, Nk.lib` (or that CE 6.0 implements
   in the kernel) now print the *kernel-module* link library
   `Nkstub.lib` (and `OEMMain.lib or OEMMain_StaticKITL.lib` for OEM
   main): GetLastError, SetLastError, Sleep, RegCloseKey,
   RegCreateKeyEx, RegFlushKey, RegOpenKeyEx, RegQueryValueEx,
   CompareFileTime, FileTimeToSystemTime, SystemTimeToFileTime,
   GetTickCount, IsProcessorFeaturePresent, WriteDebugLED.  User-mode
   applications on CE 6.0 still link Coredll; the import defs (built
   from the Coredll.lib rows) are unchanged.  Nkstub.lib / OEMMain.lib
   are kernel/OEM scope and are never import-def sources (same rule as
   Nk.lib / Coremain.lib).
3. **Header/library case, order and punctuation.**  `coredll.lib` vs
   `Coredll.lib`, `winuser.h` vs `Winuser.h`, `Drawmbar.lib. Menu.lib`
   vs `Drawmbar.lib, Menu.lib`, `tlhelp32.h` vs `Tlhelp32.h` (CE 6.0
   additionally lists `toolhelp.h`), `winnt.h, windows.h` order.  No
   semantic change.
4. **Information the CE 6.0 page supplies that the CE 5.0 page omits**
   (recorded, and used where a header needed the row):
   * `DISPLAY_DEVICE` (CE5 `aa452957` row blank) — CE 6.0
     `ee499040`: OS `.NET 4.2 and later`, Header `windows.h`.
   * `GRADIENT_RECT` (CE5 `aa453193` row blank) — CE 6.0 `ee504211`:
     OS `.NET 4.2 and later`, Header `windows.h`.
   * `FILECHANGEINFO` (CE5 `ms889030` Header `Extfile.h`) — CE 6.0
     `ee490403` adds Header `extfile.h, shlobj.h`, Link Library
     `ceshell.lib` (shell file-change notification structure on CE 6.0).

## Full difference table

```
name                                  CE5 page   OS(CE5->CE6)     Header / Library notes
```
Regenerate the audit with `tools/ce-twins.py` + `build/rows.json`.

| name | CE5 | CE6 | OS CE5 | OS CE6 | Header CE5 | Header CE6 | Library CE5 | Library CE6 |
|---|---|---|---|---|---|---|---|---|
| ASSERT | aa451037 | ee488166 | OS 2.10 and later | 2.10 and later | Dbgapi.h | dbgapi.h | none |  |
| ASSERTMSG | aa451039 | ee488600 | OS 2.10 and later | 2.10 and later | Dbgapi.h | dbgapi.h | none |  |
| AlphaBlend | aa452850 | ee501410 | Microsoft® CE® 5.0 and later | 5.0 and later | Windows.h | windows.h | Coredll.lib | coredll.lib |
| BLENDFUNCTION | aa452889 | ee506302 | Microsoft® CE® 5.0 and later | 5.0 and later | Windows.h | windows.h |  |  |
| CeLogInterrupt | aa451043 | ee488562 | NET 3.0 and later | 3.0 and later | Celog.h | celog.h | Coredll.lib | coredll.lib |
| CeLogQueryZones | aa450826 | ee488630 | NET 4.0 and later | NET 4.0 and later | Not applicable | Developer Implemented | Coredll.lib | coredll.lib |
| CeLogReSync | aa450827 | ee488638 | 3.0 and later | 3.0 and later | Celog.h | celog.h | Coredll.lib | coredll.dll |
| CompareFileTime | ms885172 | ee488173 | 1.0 and later | 1.0 and later | Windows.h | windows.h | Coredll.lib | Nkstub.lib |
| CreateToolhelp32Snapshot | ms885189 | ee487995 | 2.0 and later | 2.0 and later | Tlhelp32.h | tlhelp32.h, toolhelp.h | Toolhelp.lib | toolhelp.lib |
| DBGPARAM | aa451060 | ee487951 | OS 2.10 and later | 2.10 and later | Dbgapi.h | dbgapi.h | none |  |
| DEBUGCHK | aa451062 | ee488167 | OS 2.10 and later | 2.10 and later | Dbgapi.h | dbgapi.h | none |  |
| DEBUGLED | aa451064 | ee488408 | OS 2.10 and later | 2.10 and later | Dbgapi.h | dbgapi.h | none |  |
| DEBUGMSG | aa451065 | ee488430 | OS 2.10 and later | 2.10 and later | Dbgapi.h | dbgapi.h | none |  |
| DEBUGREGISTER, RETAILREGISTERZONES | aa451067 | ee488796 | OS 2.10 and later | 2.10 and later | Dbgapi.h | dbgapi.h | none |  |
| DEBUGZONE | aa451070 | ee488354 | OS 2.10 and later | 2.10 and later | Dbgapi.h | dbgapi.h | none |  |
| DISPLAY_DEVICE | aa452957 | ee499040 |  | NET 4.2 and later |  | windows.h |  |  |
| DrawMenuBar | aa452975 | ee504537 | 2.0 and later | 2.0 and later | Winuser.h | winuser.h | Drawmbar.lib. Menu.lib | Drawmbar.lib, Menu.lib |
| ERRORMSG | aa451079 | ee488563 | OS 2.10 and later | 2.10 and later | Dbgapi.h | dbgapi.h | none |  |
| FILECHANGEINFO | ms889030 | ee490403 | 2.10 and later | 2.10 and later | Extfile.h | extfile.h, shlobj.h |  | ceshell.lib |
| FileTimeToSystemTime | ms885593 | ee488551 | 1.0 and later | 1.0 and later | Winbase.h | winbase.h | Coredll.lib | Nkstub.lib |
| GRADIENT_RECT | aa453193 | ee504211 |  | NET 4.2 and later |  | windows.h |  |  |
| GetForegroundInfo | ms929241 | ee504647 | NET 4.2 and later | NET 4.2 and later Note Linked during platform build | Pwinuser.h | pwinuser.h | Linked during platform build |  |
| GetForegroundKeyboardLayoutHandle | ms929242 | ee500141 | NET 4.2 and later | NET 4.2 and later Note Linked during platform build | Pwinuser.h | pwinuser.h | Linked during build |  |
| GetForegroundKeyboardTarget | ms929243 | ee502570 | NET 4.2 and later | NET 4.2 and later Note Linked during platform build | Pwinuser.h | pwinuser.h | Linked during build |  |
| GetLastError | ms885627 | ee488182 | 1.0 and later | 1.0 and later | Winbase.h | winbase.h | Coredll.lib, Nk.lib | coredll.lib, Nkstub.lib |
| GetStretchBltMode | aa453165 | ee504329 | Microsoft® CE® 5.0 and later | 5.0 and later | Windows.h | windows.h | Coredll.lib | coredll.lib |
| GetTickCount | ms885645 | ee487985 | 1.0 and later | 1.0 and later | Winbase.h | winbase.h | Coredll.lib | OEMMain.lib or OEMMain_StaticKITL.lib |
| IsProcessorFeaturePresent | ms886726 | ee488016 | NET 4.1 and later | NET 4.1 and later | Winbase.h | winbase.h | Coredll.dll | OEMMain.lib or OEMMain_StaticKITL.lib |
| NKDbgPrintfW | aa451081 | ee488771 | OS 2.10 and later | 2.10 and later | Dbgapi.h | dbgapi.h | none | None |
| RETAILLED | aa451085 | ee488432 | OS 2.10 and later | 2.10 and later | Dbgapi.h | dbgapi.h | none |  |
| RETAILMSG | aa451087 | ee488919 | OS 2.10 and later | 2.10 and later | Dbgapi.h | dbgapi.h | none |  |
| RegCloseKey | ms891448 | ee489566 | 1.0 and later | 1.0 and later | Winreg.h | winreg.h | Coredll.lib | Nkstub.lib |
| RegCreateKeyEx | ms891450 | ee490393 | 1.0 and later | 1.0 and later | Winreg.h | winreg.h | Coredll.lib | Nkstub.lib |
| RegFlushKey | ms891455 | ee490431 | 2.10 and later | 2.10 and later | Winreg.h | winreg.h | Coredll.lib | Nkstub.lib |
| RegOpenKeyEx | ms891460 | ee489985 | 1.0 and later | 1.0 and later | Winreg.h | winreg.h | Coredll.lib | Nkstub.lib |
| RegQueryValueEx | ms891462 | ee490180 | 1.0 and later | 1.0 and later | Winreg.h | winreg.h | Coredll.lib | Nkstub.lib |
| RegisterDbgZones | aa451083 | ee488024 | OS 2.10 and later | 2.10 and later | Dbgapi.h | dbgapi.h | none | None |
| ReportFault | ms886799 | ee488765 | 5.0 or later | 5.0 and later | ErrorRep.h | errorRep.h | Coredll.lib | coredll.lib |
| SecureZeroMemory | ms886803 | ee488421 | NET 4.1 and later | NET 4.1 and later | Winnt.h, Windows.h | windows.h, winnt.h | Coredll.lib | coredll.lib |
| SendInput | ms932719 | ee505708 | 2.0 and later | 2.0 and later | Winuser.h | winuser.h | Wmgr_c.lib, Uibase.lib | Uibase.lib, Wmgr_c.lib |
| SetLastError | ms886817 | ee487957 | 1.0 and later | 1.0 and later | Winbase.h | winbase.h | Coredll.lib | coredll.lib, Nkstub.lib |
| Sleep | aa450900 | ee488158 | 1.0 and later | 1.0 and later | Winbase.h | winbase.h | Coredll.lib | Nkstub.lib |
| String | aa450907 | ee488753 | 3.0 and later | 3.0 and later | Not applicable | Developer Implemented |  |  |
| StringFileInfo | aa450909 | ee488169 | 3.0 and later | 3.0 and later | Not applicable | Developer Implemented |  |  |
| StringTable | aa450911 | ee488384 | 3.0 and later | 3.0 and later | Not applicable | Developer Implemented |  |  |
| SystemTimeToFileTime | aa450925 | ee488792 | 1.0 and later | 1.0 and later | Winbase.h | winbase.h | Coredll.lib | Nkstub.lib |
| ThreadProc | aa450940 | ee488554 | 1.01 and later | 1.01 and later | Developer defined | Developer Implemented | Developer defined | Developer Implemented |
| VS_VERSIONINFO | aa450984 | ee488187 | 3.0 and later | 3.0 and later | Not applicable | Developer Implemented |  |  |
| Var | aa450969 | ee488649 | 3.0 and later | 3.0 and later Note This structure was created solely to depict the organization of data in a version resource and does not appear in any of the header files shipped with an SDK for a CE OS | This structure was created solely to depict the organization of data in a version resource and does not appear in any of the header files shipped with an SDK for a Windows CE OS |  |  |  |
| VarFileInfo | aa450972 | ee488583 | 3.0 and later | 3.0 and later | Not applicable | Developer Implemented |  |  |
| WriteDebugLED | aa450990 | ee487992 | 2.12 and later | 2.12 and later | Dbgapi.h | dbgapi.h | Coredll.lib | OEMMain.lib or OEMMain_StaticKITL.lib |
