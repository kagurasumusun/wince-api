# Akari API (wince-api)

Clean-room **Win32 API layer for Windows CE 4.x / 5.x / 6.x** whose
purpose is to provide everything a **WinCE-targeted build needs on a
plain host (Linux, macOS, ...)**: API headers and coredll import
libraries, so that a CE program can be compiled and linked anywhere
the `LLVM-WinCE` clang/lld toolchain runs — replacing the "w32api"
role of the CE toolchain sysroot without needing that third-party
tree.  Targets: `arm-pc-wince` (armel) and x86 CE, CE 4.2/5.0/6.0.
Written from scratch under the same conditions as
[kagurasumusun/wince-crt](https://github.com/kagurasumusun/wince-crt):

* **Official public information only.** Every declaration is annotated
  with the official Microsoft documentation page it is taken from —
  the CE-era MSDN pages now served as the *Windows Embedded / MSDN
  archive* on learn.microsoft.com (`previous-versions/windows/
  embedded/... (v=msdn.10)`), plus Microsoft's official Win32/PE/ABI
  reference where a CE page does not exist (recorded per item in
  `docs/inventory.md`).  No function, type, constant, macro or file
  is copied, ported or adapted from w32api, mingwrt, mingw32ce,
  MinGW-w64, CeGCC or any other third-party tree; no third-party code
  is combined in.  Third-party trees are inspected **only** for
  existence/comparison (never as implementation material), and only
  the verified toolchain behavior of
  `kagurasumusun/llvm-project` (branch `LLVM-WinCE`) anchors ABI
  facts the docs do not state.
* **Own license.** MIT — see LICENSE; every file carries the SPDX
  notice.

## Scope

| Concern | Provider |
|---|---|
| Win32 **API headers** for CE (this repo) | **Akari API** (`include/`, `windows.h` umbrella) |
| Coredll **import libraries** | **Akari API** — `def/coredll-doc.def` derived only from the official per-function documentation pages (see "Export defs" below); build the `.a` with the fork's `llvm-dlltool` |
| CRT startup glue (entries, argv, ctors) | [wince-crt](https://github.com/kagurasumusun/wince-crt) |
| C run-time library (libc) headers/objects | out of scope (libc provider) |

### Export defs and import libraries (public-information only)

The export defs are **derived exclusively from the official Microsoft
CE documentation** — never from shared source, VS/Platform Builder
sources, a device dump, or a third-party tree.  The pipeline is:

1. `tools/ce-manifest.py` reads the official Learn table of contents
   (`toc.json`, published by Microsoft for the previous-versions CE
   archive) and writes a page manifest for a reference book.
   Committed manifests: `tools/manifests/core-*.manifest`.
2. `tools/ce-fetch.py` downloads each official page
   (`.../previous-versions/windows/embedded/<id>(v=msdn.10)`) and
   parses its Requirements rows into `build/rows.json` (not
   committed).
3. `tools/gen-doc-def.py` produces `def/*-doc.def` from that record
   set: a function is listed under a DLL only when that DLL's name
   appears in the function page's documented "Link Library" row.
   Ordinals are not published by the documentation, so the defs are
   name-only; import libraries built from them resolve by name, which
   is how lld links PE imports.  The generated defs are committed so
   the tree is self-contained; regenerate after harvesting more
   categories with `make defdoc` (needs `build/rows.json`).

```sh
# after a fresh harvest:
python3 tools/ce-fetch.py tools/manifests/core-synchronization-reference.manifest
make defdoc                       # writes def/*-doc.def from build/rows.json

# build an import library with the LLVM-WinCE dlltool
llvm-dlltool -m armce -d def/coredll-doc.def -l coredll.lib       # ARM CE
llvm-dlltool -m i386 --no-leading-underscore -d def/coredll-doc.def \
    -l coredll-x86.lib                                            # x86 CE
```

Functions whose page rows name only Nk.lib or Coremain.lib (e.g. the
four base critical-section functions, ReleaseMutex,
WaitForMultipleObjects) are *not* claimed as coredll exports by the
doc-derived def; they are recorded in `docs/inventory.md` (M9 notes)
and kept separate from the coredll surface pending device-surface
verification — the same conflict model as ExitProcess.

Windows CE is **Unicode-only** and its API lives in `coredll.dll`
("Link Library: Coredll.lib" on every CE function page); the CE
versions differ only in *which* APIs exist (per-page "OS Versions"
lines) and in the `_WIN32_WCE` value the toolchain driver defines
(0x420 / 0x500 / 0x600).  CE 4/5/6 and ARM/x86 are therefore one
header set with per-declaration version annotations, exactly like the
official pages.

## Layout

```
include/windows.h   umbrella (declarations whose page says Header:
                    Windows.h, e.g. ExitProcess)
include/windef.h    base types/macros (CE: TCHAR = WCHAR, WINAPI
                    empty, WCHAR 16-bit), GDI handle types
                    (HGDIOBJ/HPEN/HPALETTE), POINTS/RECTL
include/winuser.h   user-interface API (window/class/message/paint &
                    DC/coordinate & rectangle helpers, Header-row
                    Winuser.h)
include/wingdi.h    GDI Reference: bitmap/pen/brush/palette/region/
                    font/DEVMODE structures + the 129 GDI functions
                    whose CE 5.0 pages print Header Windows.h (CE 6
                    component name; see header note)
include/tvout.h     VIDEOPARAMETERS (TV-out; Header Tvout.h)
include/winnt.h     base 64-bit types (LONGLONG/LARGE_INTEGER),
                    MEMORY_BASIC_INFORMATION, MAKELANGID/MAKELCID,
                    SecureZeroMemory
include/winnls.h    code-page / NLS API (MultiByteToWideChar,
                    WideCharToMultiByte, IsDBCSLeadByte*, locale/
                    code-page getters, CompareString, GetStringType*)
include/winreg.h    registry API (Reg* + CeFind*RegChange)
include/commctrl.h  Image List API (Header Commctrl.h rows of the CE
                    5.0 Image Lists book): HIMAGELIST / IMAGEINFO /
                    IMAGELISTDRAWPARAMS, the 32 ImageList_* functions,
                    the four documented macros and the ILC_*/ILD_*/
                    CLR_* value constants (include Windows.h first)
include/winbase.h   base OS API: process/thread/module/command line,
                    dynamic-link, local memory, file management +
                    synchronous file I/O + directory management,
                    time (M7), synchronization (M9: events/mutexes/
                    semaphores/wait/critical sections/interlocked),
                    heaps + memory status + tick/time helpers (M10)
include/winerror.h  error-code constants (rows 0-1078 of the official
                    CE numeric table, aa450919)
def/                coredll export def derived from the official
                    documentation pages (coredll-doc.def, name-only);
                    generated by tools/gen-doc-def.py from
                    build/rows.json and committed
tools/              manifest/fetch/parse/generate tools
                    (ce-manifest.py, ce-fetch.py, ce-text.py,
                    gen-doc-def.py, ce-corpus.py); manifests under
                    tools/manifests/; page-corpus round trip via
                    ce-corpus.py + kagurasumusun/wince-docs-corpus
                    (docs/corpus.md)
docs/inventory.md   per-declaration official-source matrix
                    (page ID, OS Versions, Header, Link Library)
tests/host/         host compile checks (types, syntax, mappings)
tests/e2e/          end-to-end link consumers (main / WinMain / DLL;
                    `make e2e`)
Makefile            make check  (host syntax/type checks for CE
                    0x420/0x500/0x600); make crosscheck WINCECLANG=...
```

## Build and check

```sh
make check          # host: headers + TU compile warning-free under
                    # _WIN32_WCE = 0x420 / 0x500 / 0x600
make crosscheck WINCECLANG=/path/to/LLVM-WinCE/clang
                    # real-toolchain compile checks for the six
                    # arm/i386-pc-wince{4.2,5.0,6.0} targets
make e2e WINCECLANG=/path/to/LLVM-WinCE/clang CRTDIR=/path/to/wince-crt
                    # doc-derived import libraries (llvm-dlltool) +
                    # Akari CRT: link the tests/e2e consumers into
                    # PE images on all six targets (main app /
                    # WinMain app / DLL) and assert machine, CE
                    # subsystem and import names
```

Cross checks with the real toolchain (32-bit pointer model, x86
decoration) run exactly like wince-crt's: build with the
`LLVM-WinCE` toolchain.  As of the M10 batch the freestanding
compile matrix (headers + TU, `-Werror`) passes for
`arm-pc-wince4.2/5.0/6.0` and `i386-pc-wince4.2/5.0/6.0`.  End-to-end
linking is shipped (M37): `make e2e WINCECLANG=... CRTDIR=...`
builds the doc-derived import libraries (`llvm-dlltool`), links the
`tests/e2e` consumers with the Akari CRT against them on all six
targets, and asserts the PE machine/subsystem/import surface — the
x86 headers are pinned to the undecorated CE export names
(`AKARI_CE_IMPORT`/`AKARI_CE_NAME` in windef.h).

## Status / roadmap

Landing history (each batch adds only official-page-grounded
declarations, recorded in `docs/inventory.md`):

* **M50 (landed):** AYGShell unit (new `include/aygshell.h`,
  `shellsdk.h`, `newmenu.h`, `shlobj.h`, `extfile.h`; Aygshell.lib) --
  the CE 5.0 AYGShell Reference book (62 leaves): 33 exported
  functions (SHChangeNotifyRegister .. SHSipInfo, plus SHInitDialog in
  its documented shellsdk.h home and SHGetAutoRunPath in windows.h),
  the SHNP enumeration, 9 documented structures (SHACTIVATEINFO,
  SHCHANGENOTIFYENTRY, SHINITDLGINFO, SHMENUBARINFO, SHNOTIFICATIONDATA,
  SHRGINFO, NMNEWMENU, FILECHANGENOTIFY, FILECHANGEINFO) with 10
  TU-asserted 32-bit sizes, the WC_SIPPREF control class, the
  application-implemented INewMenuItemServer / IShellNotificationCallback
  interfaces (opaque tags + method records), NMHDR + WM_NOTIFY +
  WM_SETTINGCHANGE added to winuser.h, and the three SendMessage macros
  + SHCMBM_*/NMN_*/WM_FILECHANGEINFO message shapes recorded verbatim.
  SHSipPreference is held (SIPSTATE has no published definition
  anywhere in the official CE trees); the extensive name-without-value
  flag sets (SHIDIF_/SHCMBF_/SHRG_/SHNF_/SHFS_/SHDB_/SHNUM_/SPI_*)
  are recorded as gaps per the held-set policy.  New
  `aygshell-doc.def` with 33 exports; e2e asserts aygshell.dll +
  SHCreateMenuBar + SHHandleWMActivate + SHInitDialog +
  SHGetAutoRunPath on all six targets.
* **M48 (landed):** Cryptography certificate / encode / OID / PFX
  unit (wincrypt.h; **Crypt32.lib**) -- the 54 documented Cert*
  store/context functions, the 25 encode/decode/OID/key-identifier
  functions and the 4 PFX functions (every page Header: Wincrypt.h /
  Link Library: Crypt32.lib), plus the full CERT_* / CMSG_* / CRYPT_*
  structure trees transcribed from the 71 structure pages (CERT_INFO
  closes the M47 hold; 8 pointer-only targets stay opaque by design),
  the 5 crypto handle carriers, the two documented callback shapes
  (PFN_CERT_ENUM_SYSTEM_STORE / _LOCATION) and 63 TU-asserted 32-bit
  sizes measured on the CE target.  New `crypt32-doc.def` with 83
  exports; e2e asserts crypt32.dll + CertOpenStore +
  CryptEncodeObjectEx + PFXImportCertStore on all six targets.
* **M49 (landed):** Smart Card subsystem unit (new `include/winscard.h`;
  Winscard.lib) -- the 28 documented SCard* functions (SCardBeginTransaction
  .. SCardTransmit) plus SCARD_IO_REQUEST / SCARD_READERSTATE /
  SCARD_ATRMASK, SCARDCONTEXT/SCARDHANDLE handle carriers and the
  LPCBYTE/LPCGUID documented spellings.  New `winscard-doc.def` with
  28 exports; e2e asserts winscard.dll + SCardEstablishContext +
  SCardTransmit on all six targets.  Also this batch:
  `docs/ce-not-nt.md` records the official-source readout that
  Windows CE 1.x-6.x is a separate OS family with its own kernel
  (not NT-derived), quoting the learn.microsoft.com archive pages.
* **M47 (landed):** Cryptography base CSP unit (new
  `include/wincrypt.h`; Coredll.lib) -- the 42 documented Crypt*
  functions of the CE 5.0 Cryptography book (CryptAcquireContext ..
  CryptVerifySignature incl. the CryptMsg* family and
  CryptProtectData/CryptUnprotectData; every page Header: Wincrypt.h
  / Link Library: Coredll.lib), the four fundamental types (ALG_ID,
  HCRYPTHASH, HCRYPTKEY, HCRYPTPROV -- all printed verbatim), the
  HCRYPTMSG handle carrier, _CRYPTOAPI_BLOB + its 13 documented alias
  names (DATA_BLOB et al.), CMSG_STREAM_INFO +
  PFN_CMSG_STREAM_OUTPUT, VTableProvStruc (Version 3 on CE), and
  CPAcquireContext (declared-not-exported: "Link Library: Developer
  defined").  PCERT_INFO stays an opaque forward declaration until
  the certificate unit; CRYPTPROTECT_PROMPTSTRUCT is documented
  unused (must be NULL) on CE.  The crypto constant sets
  (CRYPT_VERIFYCONTEXT/..., PROV_*, CALG_* x40, AT_*,
  CRYPTPROTECT_*) publish names without values in the CE archive ->
  recorded-not-defined (the M39-M41 held-set policy).  coredll
  560 -> 602 exports; e2e asserts CryptAcquireContext + CryptMsgClose
  + CryptProtectData imports on all six targets.
* **M46 (landed):** Input Method Manager unit (new `include/imm.h`;
  Coreimm.lib) -- the 55 documented IMM functions of the official CE
  5.0 Input Method Manager reference (56 function pages harvested;
  ImmGetConversionStatusForeground recorded-not-declared: Pwinuser.h
  / "Linked during platform build" platform-builder row), the nine
  complete structures (CANDIDATEFORM/CANDIDATEINFO/CANDIDATELIST/
  COMPOSITIONFORM/COMPOSITIONSTR/GUIDELINE/RECONVERTSTRING/
  REGISTERWORD/STYLEBUF, 32-bit sizes TU-asserted), the HIMC/HIMCC
  handle carriers, LPHKL/LPUINT, REGISTERWORDENUMPROC, and three
  opaque pointer sets (INPUTCONTEXT / IMEMENUITEMINFO /
  IMECHARPOSITION: each layout needs an unpublished piece -- the
  LOGFONTA layout, the IMEMENUITEM_STRING_SIZE value, the width of
  UNIT -- verified absent from the CE 5.0 / CE .NET / CE 6.0 trees).
  The 83 IMM constant pages (IME_CMODE_*/GCS_*/IME_CHOTKEY_*/
  IME_SMODE_*/IME_ESC_*/IMC_*/IMN_*/IMR_*/IPCTRL_*/WM_IME_*) publish
  names without values in both CE 5.0 and the fetched CE 6.0 twins ->
  recorded-not-defined (the M39-M41 held-set policy).  coreimm 1 ->
  56 exports; e2e asserts coreimm.dll + ImmGetContext +
  ImmSIPanelState imports on all six targets.
* **M45 (landed):** TAPI client runtime unit (tapi.h; closes the M43
  client hold) -- the 89 documented TAPI client functions (66 line* +
  23 phone*) of the official CE 5.0 Telephony API book
  (`tapi-client-functions.manifest`, 89 pages harvested this session;
  every page Header: Tapi.h / Link Library: Coredll.lib), the
  LINECALLBACK / PHONECALLBACK callback shapes (lineCallbackFunc
  ms893424 / phoneCallbackFunc ms895910), the client-side opaque
  handles HLINEAPP/HCALL/HPHONE/HPHONEAPP + LPH* aliases (documented
  parameter-wording basis), and the LPLINEFORWARDLIST opaque pointer
  (the LINEFORWARDLIST layout ms894148 names a LINEFORWARD element
  whose layout no official CE tree publishes).  The opaque pointer
  also closes the M43 TSPI_lineForward hold: the TSPI surface is now
  79 declared entry points.  coredll 470 -> 560 exports; e2e asserts
  lineInitializeEx / lineOpen / lineForward / phoneOpen /
  TSPI_lineForward in the coredll import table on all six targets.
* **M38 (landed):** CopyFileEx unit (winbase.h; closes the M31
  deferral) -- `CopyFileExW` (CE 5.0+, `aa517311` / CE 6.0 twin
  `ee490791`; Winbase.h, Coredll.lib), `LPPROGRESS_ROUTINE` (the
  official Win32 reference callback shape; the CE page names the type
  only), PROGRESS_CONTINUE/CANCEL/STOP and the three COPY_FILE_*
  flags (names per the CE page; fixed Win32 ABI values per the
  official CopyFileExW reference; desktop-only variants
  recorded-not-defined).  gen-doc-def.py's declaration matcher
  accepts the M37 import pin.  coredll 391 -> 392 (total 654); e2e
  console links CopyFileExW on all six targets.
* **M37 (landed):** x86 CE undecorated import surface + end-to-end
  link harness.  CE coredll/component-DLL export names are
  undecorated on x86 as well as ARM (verified import surface); the
  shipped headers, declared as plain C, produced
  leading-underscore references on i386 that the undecorated import
  libraries cannot satisfy.  `windef.h` gains `AKARI_CE_IMPORT`
  (`__declspec(dllimport)` on x86) and `AKARI_CE_NAME(n)`
  (`__asm(#n)` on x86); all 602 component-DLL declarations are
  pinned.  The dllimport indirection is required because
  uppercase-`L` names (LocalAlloc, LoadLibraryW, ...) cannot be
  referenced by a bare asm label (MC local-label rule; verified
  toolchain diagnostic).  New `tests/e2e` consumers + `make e2e`:
  all 33 doc-derived defs -> llvm-dlltool import libraries
  (armce / i386 `--no-leading-underscore`), Akari CRT per triple,
  `lld-link -wince` PE images (mainACRTStartup / WinMainCRTStartup /
  DllMainCRTStartup) with machine/subsystem-9/undecorated-import
  assertions — passing on all six arm/i386-pc-wince{4.2,5.0,6.0}
  targets.  Stray `a.out` removed.
* **M36 (landed):** GDI fonts-and-text + MultiMonitor in wingdi.h --
  22 font/text functions (AddFontResourceW … SetTextColor) and 5
  MultiMonitor functions from the official CE 5.0 Fonts-and-Text GDI
  pages and CE .NET 4.0+ MultiMonitor pages (CE 6.0 twins), with
  LOGFONT / ENUMLOGFONT / NEWTEXTMETRIC / ABC / MONITORINFO structures,
  FONTENUMPROC / MONITORENUMPROC callback typedefs, LF_FACESIZE,
  font-type, DT_* / ETO_* / TA_* and monitor flag constants (fixed
  Win32 ABI values); HFONT / HMONITOR / LPINT in windef.h.  coredll
  def 364 → 391 (total 626 → 653).
* **M35 (landed):** GWES style bits in winuser.h -- 126 constants
  (WS_*/WS_EX_*, MB_*, BS_*, ES_*, LBS_*, CBS_*, SBS_*, SS_*, DS_*)
  from the official CE 5.0 style pages with CE 6.0 twins; fixed Win32
  ABI values static-asserted.
* **M34 (landed):** Windows CE .NET tree read in full (6,361 leaves
  -> corpus pages4/; rows4.json 4,030 Requirement-row pages; cross-tree
  union vs CE 5.0/CE 6.0; docs/cenet-readout.md) + NLS string mapping
  & directory-service user-name batch (LCMapStringW, FoldStringW,
  EnumSystemCodePagesW, GetUserNameExW + CODEPAGE_ENUMPROC +
  EXTENDED_NAME_FORMAT; exports 622 -> 626).
* **M33 (landed):** CE 6.0 full-twin corpus + reconciliation
  (1133/1133 CE 6.0 twins of the harvested CE 5.0 corpus fetched and
  compared: 1039 identical Requirement rows; 51 categorized diffs --
  editorial wording, CE6 kernel-mode Nkstub.lib/OEMMain.lib rows
  (import defs unchanged), and 3 CE6 information fills; docs/
  ce6-reconciliation.md + docs/ce6-twins.tsv + tools/ce-twins.py;
  corpus pages6/ 38 -> 1133).  COPYDATASTRUCT added to winuser.h
  (fixed-ABI structure reference for WM_COPYDATA; 12 bytes on 32-bit).
* **M32 (landed):** NLS formatting / locale-info (Coreloc.lib):
  CURRENCYFMT/NUMBERFMT structures and GetCurrencyFormatW /
  GetNumberFormatW / GetDateFormatW / GetTimeFormatW / GetLocaleInfoW /
  SetLocaleInfoW + LCTYPE typedef (winnls.h).  coreloc 24 -> 30, 622
  name-only exports across 33 def files; DATE_/TIME_ flag names and the
  LCTYPE value table recorded-not-transcribed.
* **M31 (landed):** WM_COPYDATA (winuser.h) + cross-process
  read/thread-context (ReadProcessMemory/GetThreadContext + LPCONTEXT),
  VS_FIXEDFILEINFO + VS_FF_* version flags (winbase.h), and
  FONTSIGNATURE/CHARSETINFO/TranslateCharsetInfo + TCI_* charset
  translation (wingdi.h).  coredll 360 -> 363, 616 name-only exports
  across 33 def files; second full-corpus rows-vs-headers audit pass
  with all remaining gaps recorded in docs/inventory.md.
* **M30 (landed):** corpus-preservation pipeline + remaining
  Winbase.h/Windows.h gap fill.  `tools/ce-corpus.py` + `docs/corpus.md`
  implement save-all-pages / push / delete-per-session / refetch-from-
  GitHub (`kagurasumusun/wince-docs-corpus`: 1175 CE 5.0 + 38 CE 6.0
  pages + rows + catalogs; raw MS HTML stays out of this MIT tree).
  Audited rows.json vs headers and added the missing documented
  exports: FreeLibraryAndExitThread, CeZeroPointer, CeGetThreadQuantum,
  CeSetThreadQuantum, VerQueryValueW, IsProcessorFeaturePresent,
  QueryInstructionSet (winbase.h) and SetUserDefaultLCID (windows.h).
  coredll 353 -> 360, coreloc 23 -> 24, 613 name-only exports across 33
  def files; deferred items recorded with reasons in docs/inventory.md.
* **M29 (landed):** Image List Reference book + GWES message/
  notification constants (two units together).  New
  `include/commctrl.h` (CE 5.0 Image Lists book: HIMAGELIST /
  IMAGEINFO / IMAGELISTDRAWPARAMS, 32 ImageList_* functions, macros
  ImageList_AddIcon/ExtractIcon/LoadBitmap/INDEXTOOVERLAYMASK, ILC_*/
  ILD_*/CLR_* values; 38 leaves; signatures from the official CE 6.0
  twins).  winuser.h gains the BM/BN/STM/STN/menu/dialog/clipboard/
  GDI-message identifiers and notifications + the M26-announced WM_*
  numeric transcription + IMAGE_BITMAP/ICON/CURSOR; wingdi.h gains the
  ternary/binary ROP codes (SRC*/PAT*/R2_*).  Numeric message values
  are fixed Win32 ABI (CE pages document names/parameters, not
  numbers); every define carries its CE page id.  Rows 939 -> 1175;
  defs 31 -> 33 (commctrl-doc.def + imgctl-doc.def, 31 exports each,
  armce-verified), total name-only exports 543 -> 605.
* **M28 (landed):** window-control function layer -- Menus / Dialog
  Boxes / Buttons / Clipboards / Printing / Resources / System
  Information functions+structures, the Notify Reference books and the
  owner-draw/icon support structures (DRAWITEMSTRUCT / COMBOBOXINFO /
  MEASUREITEMSTRUCT / DELETEITEMSTRUCT / ICONINFO) (112 CE 5.0 leaves,
  rows 827 -> 939; CE 6.0 twins used for whitespace-preserved
  signatures).  New headers `include/notify.h` (Notify.h rows) and
  `include/shellapi.h` (Shellapi.h row); winbase.h gains the
  resource-module functions + power-status structs/functions, wingdi.h
  the printing book + DOCINFO/ABORTPROC + extended dialog templates,
  windows.h the Header-Windows.h items (MessageBox, CheckDlgButton,
  IsDlgButtonChecked, DRAWITEMSTRUCT); HRSRC added to windef.h.  New
  component defs clipbd/dlgmgr/drawmbar/icon/loadimg/menu/mgprint/
  msgbeep/msgbox/wmbase; coredll 335 -> 353, winmgr 17 -> 18, wmgr_c
  3 -> 4, kbdui 5 -> 6; 21 -> 31 def files, all armce-verified.
  GWES sub-book manifests now regenerate from the official TOC
  (`tools/ce-gwes-manifest.py`, 32 manifests; CE 5.0 archive located by
  title search, no fixed nesting assumption).
* **M27 (landed):** GDI Reference bulk -- GDI Functions + GDI
  Structures (161 CE 5.0 leaves, rows 666 -> 827): new
  `include/wingdi.h` (129 GDI functions + the bitmap/color/palette/
  pen/brush/region/DEVMODE/display/font structures; the three color
  accessors GetRValue/GetGValue/GetBValue are declared *as macros* per
  the official pages), `include/tvout.h` (VIDEOPARAMETERS).  Signatures
  recovered from the official CE 6.0 `(v=winembedded.60)` twins
  (whitespace-preserved prototypes; the CE 5.0 migration strips code
  spacing); per-declaration id pairs in the headers.  Windef.h gains
  HGDIOBJ/HPEN/HPALETTE + POINTS/RECTL; winuser.h gains the paint/DC/
  coordinate/rectangle helpers whose rows say Winuser.h; winbase.h
  gains InflateRect/SetRect (rows say Winbase.h).  coredll def 221 ->
  335; winmgr 1 -> 17; new component defs rectapi(11), loadbmp(1),
  nclient(1); 18 -> 21 def files, all armce-verified.
* **M26 (landed):** GWES window-manager core — new `include/winuser.h`
  (Windows / Window Class / Window Properties / Windows Timer /
  Carets / Atoms / Message Queue / Keyboard / Scroll Bars books, 156
  GWES pages harvested, rows.json 510 → 666); Header-home moves the
  Windows.h-row items (properties, atoms, SendMessageTimeout, ScrollDC,
  GetMessageQueueReadyTimeStamp) into windows.h and Winbase.h-row items
  (KillTimer, MsgWaitForMultipleObjects/Ex) into winbase.h; windef.h
  gains POINT/RECT/SIZE/HWND-family + MAKELONG.  coredll def 192 → 221;
  new component-module defs accel/caret/foregnd/hotkey/kbdui/coreimm/
  msgque/sbcmn/uibase/winmgr/wmgr_c (7 → 18 defs, all armce-verified).
* **M1 (landed):** foundation + windef/winbase/windows.h — process
  termination, module/command-line/proc-address, local memory.
* **M2 (landed):** process/thread/module/error batch (GetLastError,
  CreateThread, CreateProcessW, LoadLibraryW, FreeLibrary,
  PROCESS_INFORMATION, SECURITY_ATTRIBUTES/STARTUPINFOW opaque
  tags) + `docs/clean-room.md`, `docs/generations.md`,
  `docs/parity-target.md`.
* **M3 (landed):** winerror.h error-code set from the official CE
  numeric table `aa450919`; handle/process/error batch (CloseHandle,
  OpenProcess, GetExitCodeProcess, SetLastError).
* **M4 (landed):** TLS (TlsAlloc/Free/SetValue/GetValue), thread
  scheduling (Suspend/ResumeThread, GetExitCodeThread), LoadLibraryEx
  + the documented kfuncs/ExitProcess conflicts.
* **M5 (landed):** Sleep, thread priorities, GetThreadPriority/
  SetThreadPriority + thread/process structure grounding.
* **M6 (landed):** file management batch (CreateFile, DeleteFile,
  GetFileAttributes, FindFirstFile/FindNextFile/FindClose) +
  FILETIME/WIN32_FIND_DATAW.
* **M7 (landed):** time management (SYSTEMTIME + the four file-time
  conversions) + winerror.h completion against the official table.
* **M8 (landed):** synchronous file I/O and file/directory management
  batch — ReadFile `ms891445`, WriteFile `ms892380`, GetFileSize
  `ms890939`, SetFilePointer `ms891933`, SetEndOfFile `ms891916`,
  FlushFileBuffers `ms890238`, MoveFile `ms891388`, CopyFile
  `aa517309`, CreateDirectory `aa517316`, RemoveDirectory `ms891470`,
  SetFileAttributes `ms891925` — plus the OVERLAPPED opaque tag,
  FILE_BEGIN/CURRENT/END, INVALID_SET_FILE_POINTER, `PLONG` in
  windef.h, and the first real-toolchain verification harness
  (`make crosscheck WINCECLANG=...`).
* **Def policy change (M9):** the device-dump/audited-surface def
  approach (and the obsolete `gen-defs.sh` input path) is gone.
  Export defs are now derived only from the official documentation:
  TOC manifests (`tools/ce-manifest.py`), per-page Requirements
  harvesting (`tools/ce-fetch.py`), and `tools/gen-doc-def.py`
  producing committed `def/*-doc.def` files (name-only; ordinals are
  not published).
* **M9 (landed):** synchronization batch from *Core OS Reference →
  Synchronization Reference*: event objects (CreateEvent/OpenEvent/
  SetEvent/ResetEvent/PulseEvent), mutexes and semaphores, the wait
  functions, DuplicateHandle, critical sections, and the interlocked
  family (24 functions), plus `winnt.h` (LONGLONG/LARGE_INTEGER
  unions, RTL_CRITICAL_SECTION/CRITICAL_SECTION, SecureZeroMemory),
  WAIT_*/MAXIMUM_WAIT_OBJECTS/DUPLICATE_*/EVENT_ALL_ACCESS constants,
  `PVOID`/`LPLONG`/`LPHANDLE` pointer typedefs.  Page-derived
  Nk.lib/Coremain.lib link-library rows are recorded and kept out of
  the coredll doc def (documented conflict model, see inventory M9
  notes).
* **M10 (landed):** Time Reference + Memory Management Reference
  batch (no new page fetches; the 203 harvested rows already covered
  these two books): tick/counter and file-time helpers (GetTickCount,
  GetFileTime/SetFileTime, CompareFileTime, GetCurrentFT, GetIdleTime,
  Random, SetDaylightTime, QueryPerformanceCounter/Frequency) and the
  heap/local-memory/status/probe set (GetProcessHeap [Lmem.lib row],
  HeapCreate/Destroy/Alloc/Free/ReAlloc/Size/Validate/Compact,
  LocalReAlloc/LocalSize, GlobalMemoryStatus + MEMORYSTATUS,
  IsBadCodePtr/IsBadReadPtr/IsBadWritePtr).  `def/coredll-doc.def`
  regenerated 53 → 77 name-only exports.
* **M15 (landed):** Registry Reference — new `include/winreg.h`
  (RegOpenKeyExW/RegCreateKeyExW/RegEnum*/RegQuery*/RegSetValueEx,
  CeFind*RegChange, HKEY/REGSAM/REG_* constants).  def 100 → 114.
* **M16 (landed):** NLS part 1 (locale/code-page getters, CompareString,
  GetStringTypeW/Ex, CPINFO; LANGID/LCID; MAKELANGID/MAKELCID in
  winnt.h).  def 114 → 115.
* **M17 (landed):** File I/O continuation (change notifications,
  FindFirstFileEx + enum levels, GetFileAttributesEx/GetDiskFreeSpaceEx/
  GetFileInformationByHandle + CE dwOID record, GetTempPath/FileName,
  LockFileEx/UnlockFileEx, DeleteAndRenameFile, GetFileVersionInfo*).
  def 115 → 147.
* **M18 (landed):** ToolHelp Reference — new `include/tlhelp32.h`
  (snapshot enumeration + PROCESSENTRY32/THREADENTRY32/MODULEENTRY32/
  HEAPLIST32/HEAPENTRY32 with their CE-only members).
* **M19 (landed):** Strings Reference (Char*Lower/Upper*, CharNext/
  CharPrev, IsChar*, wsprintfW/wvsprintfW, LoadString) and def
  generation generalized to one def per documented Link Library
  (coreloc/toolhelp/lmem/loadstr + coredll).
* **M20/M20b (landed):** File Mapping Reference (CreateFileForMapping/
  CreateFileMapping/MapViewOfFile/UnmapViewOfFile/FlushViewOfFile),
  DisableThreadLibraryCalls + DLL_* reason constants, new
  `include/psapi.h` (MODULEINFO/GetModuleInformation).  def 148 → 154.
* **M25 (landed):** Error Values + NAT + CeLog (bulk) — winerror.h
  completed to the full official CE System-Errors page (769 defines,
  incl. NTE/CRYPT/CERTSRV/TRUST namespaces), FormatMessageW + new
  `fmtmsg-doc.def`; new `include/natedit.h` (NAT editor API) and
  `include/celog.h` (CeLog tracking functions).  coredll def 171 → 192
  (247 exports across all libs).
* **M24 (landed):** Exception + Debugging References (bulk) — new
  `excpt.h` (SEH intrinsics + EXCEPTION_POINTERS), `dbgapi.h`
  (DBGPARAM/NKDbgPrintfW/RegisterDbgZones/WriteDebugLED), `errorrep.h`
  (ReportFault); winnt.h EXCEPTION_RECORD/CONTEXT(opaque)/EXCEPTION_*
  codes; winbase.h RaiseException/DebugBreak/DEBUG_EVENT family/
  debug-event + DBG_* constants.  def 164 → 171.
* **M23 (landed):** Serial Communications Reference — 16 functions
  (ClearCommBreak…WaitCommEvent) + COMMTIMEOUTS/COMSTAT/DCB/COMMPROP
  in winbase.h; new def/serdev-doc.def (16 Serdev.lib exports).
* **M22 (landed):** Message Queue Point-to-Point Reference — new
  `include/msgqueue.h` (Close/CreateMsgQueue, GetMsgQueueInfo,
  OpenMsgQueue, ReadMsgQueue, WriteMsgQueue, MSGQUEUEOPTIONS,
  MSGQUEUEINFO).  All pages CE .NET 4.0+, Msgqueue.h, Coredll.lib.
  def 158 → 164.
* **M21 (landed):** GetStoreInformation + STORE_INFORMATION,
  CeGenRandom/CeGetCanonicalPathName/CeGetFileNotificationInfo,
  FILE_NOTIFY_INFORMATION/FILE_ACTION_* (winnt.h).  def 154 → 158.
* **M11 (landed):** System Management Reference (part 1) — SYSTEM_INFO
  + GetSystemInfo `ms885638`/`aa450921`, OSVERSIONINFO + GetVersionEx
  `ms885648`/`ms886768`, SignalStarted `aa450898` (PROCESSOR_
  ARCHITECTURE_* and VER_PLATFORM_* with fixed Win32 ABI values).
  def 77 → 80 exports.
* **M12 (landed):** virtual memory + time zone + version/timing —
  VirtualAlloc/Free/Protect/Query + MEMORY_BASIC_INFORMATION and
  MEM_*/PAGE_* constants (`aa450975`/`aa450979`/`aa450980`/`aa450981`/
  `ms886752`), FlushInstructionCache `ms885595`, GetProcessVersion
  `ms885636`, GetDllVersion `ms885617`, GetThreadTimes `ms885644`,
  TIME_ZONE_INFORMATION + Get/SetTimeZoneInformation
  (`aa450943`/`ms885646`/`aa450893`).  def 80 → 90 exports.
* **M13 (landed):** code-page / NLS — new `include/winnls.h`
  (MultiByteToWideChar `ms886760`, WideCharToMultiByte `aa450989`,
  IsDBCSLeadByte/Ex `ms886515`/`ms886608`, CP_*/MB_*/WC_* constants),
  `BYTE`/`LPBOOL` in windef.h.  def 90 → 94 exports.

Remaining roadmap (queued, page-grounded): the second-order DLL
books (other component modules), the CE books
not yet harvested in full (e.g. the CE 4.2 book pages), and the
held constant sets whose official pages publish names without values
(the M39-M41 Winsock SO_/LUP_/NS_ set, the TSPI callback-message
values, the M50 AYGShell flag sets) -- those need the documented
on-device readback procedure
before they can be defined.  Each batch adds only
official-page-grounded declarations; def harvesting continues in
lockstep (coredll at 602 name-only exports incl. the 42 M47 Crypt*
functions; coreimm 56, M46; crypt32 83 + winscard 28, M48/M49;
aygshell 33, M50);
end-to-end link
verification with wince-crt on the `LLVM-WinCE` toolchain (host +
cross) runs for every milestone.

## Verification rules (same as wince-crt)

1. Implement only from official pages + official ABI references;
   record the page ID next to every declaration.
2. Anything not covered by official text is marked *own design* in
   `docs/inventory.md` and decided from the verified toolchain's
   observable output — never from a third-party implementation's
   behavior alone.
3. Warning-free host checks; cross checks with the real toolchain
   import libraries; every commit pushed immediately.
