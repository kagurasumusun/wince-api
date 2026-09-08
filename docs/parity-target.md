# CeGCC w32api parity target

wince-api must be able to *replace the role* of the CeGCC-lineage
w32api in the WinCE sysroot (kagurasumusun/w32api).  This page
records the measured target scope and the status of each part.

Method note: the numbers and file/DLL names below were obtained by
listing the third-party tree (existence inspection only, per
`clean-room.md` §4).  No content of those files is used anywhere in
this repository; our headers are written from the official pages
(`inventory.md`).

## Measured target (existence only, 2026-09)

* Headers in the sysroot w32api `include/`: **255 files** (the
  CE-relevant subset is smaller; the official per-function "Header:"
  requirement rows define the file set a CE program can legitimately
  need).
* Import-library sources in `libce/`: **59 entries** (DLL def files
  such as aygshell.def, commctrl.def, crypt32.def, CellCore.def,
  htmlview.def, winsock-family defs, plus GUID source files); the
  coredll defs (CE 4/5/6, ARM/x86) live in the mingwrt tree.
* These DLLs are the *second-order* target: after the coredll core,
  each DLL's official function pages are processed the same way.

## Coverage status (through M45, 2026-09-08)

| Area | Status |
|---|---|
| `windows.h` umbrella | shipped (M1) |
| `windef.h` base types/macros | shipped (M1) |
| `winbase.h` — full shipped surface: process/thread/module/memory/error, heap, sync/wait, strings, registry, files, messages, serial (M23 in winbase.h), services, power, system info, CE-specific (LocalAlloc/MsgQueue family) | shipped (M1–M35) |
| `winuser.h` GUI: windows, messages, controls, menus, dialogs, clipboards, accelerators, shell | shipped (M19–M29, M39 window properties) |
| `wingdi.h` / `wingdi` GDI | shipped (M10–M16, M27 fonts) |
| `winreg.h`, `winnls.h`, `psapi.h`, `tlhelp32.h`, `msgqueue.h`, `excpt.h`, `dbgapi.h`, `errorrep.h`, `celog.h`, `natedit.h`, `commctrl.h`, `notify.h`, `shellapi.h`, `tvout.h`, `winerror.h`, `winnt.h` | shipped |
| Winsock: `winsock2.h` + `ws2tcpip.h` + `ws2spi.h` (WS2_32/Ws2.lib) | shipped (M37–M42) |
| TAPI/TSPI: `tapi.h` + `tapicomn.h` -- TSPI provider surface (79 entry points incl. the M45 TSPI_lineForward closure) + TAPI foundation (26 structures, 643 constants) | shipped (M43) |
| TAPI client runtime: `tapi.h` -- the 89 documented client functions (66 line* + 23 phone*), LINECALLBACK/PHONECALLBACK, client handles HLINEAPP/HCALL/HPHONE/HPHONEAPP | shipped (M45; closes the M43 hold) |
| Input Method Manager: `imm.h` -- the 55 documented Coreimm.lib functions, nine structures, HIMC/HIMCC, REGISTERWORDENUMPROC | shipped (M46) |
| Cryptography base CSP: `wincrypt.h` -- the 42 documented Coredll.lib Crypt* functions (incl. CryptMsg* + CryptProtectData/Unprotect), ALG_ID/HCRYPTHASH/HCRYPTKEY/HCRYPTPROV/HCRYPTMSG, _CRYPTOAPI_BLOB + 13 alias names, CMSG_STREAM_INFO, VTableProvStruc, CPAcquireContext (developer-defined) | shipped (M47) |
| Cryptography certificate/encode/OID/PFX: `wincrypt.h` -- the 83 documented Crypt32.lib functions (54 Cert* + 25 encode/OID/key-id + 4 PFX) and the CERT_*/CMSG_*/CRYPT_* structure trees (CERT_INFO closes the M47 hold), 63 TU-asserted 32-bit sizes | shipped (M48) |
| Smart Card: `winscard.h` -- the 28 documented Winscard.lib SCard* functions, SCARD_IO_REQUEST/SCARD_READERSTATE/SCARD_ATRMASK, SCARDCONTEXT/SCARDHANDLE | shipped (M49) |
| AYGShell: `aygshell.h`/`shellsdk.h`/`newmenu.h`/`shlobj.h`/`extfile.h` -- the 33 documented Aygshell.lib functions (incl. SHInitDialog and SHGetAutoRunPath in their documented homes), SHNP, 9 structures (10 TU-asserted sizes), WC_SIPPREF, NMHDR/WM_NOTIFY/WM_SETTINGCHANGE, INewMenuItemServer/IShellNotificationCallback records; SHSipPreference held (SIPSTATE unpublished) | shipped (M50) |
| Software-based Input Panel: `sipapi.h`/`sip.h` -- the 9 documented Coredll.lib Sip* functions, the SipEnumIMProc callback shape + IMENUMPROC carrier, SIPINFO/IMENUMINFO/IMINFO/LMDATA (4 TU-asserted sizes), WM_IM_INFO record, the IIMCallback/IIMCallback2/IInputMethod/IInputMethod2 interface records; SIPF_*/SIP_STATUS_*/LMDATA_* value sets held | shipped (M51) |
| COM/OLE/Storage/Automation: `objbase.h` umbrella (635 pages: Objbase/Objidl/Oaidl/Wtypes/Unknwn/Oleauto/Ocidl) | shipped (M44): 307 functions (ole32.dll 84, oleaut32.dll 223), 64 documented structures/enums, 50 opaque interfaces with documented method lists, full STGM/CLSCTX/VT_/FADF_/type-lib constant sets |
| Import-library defs (`def/*-doc.def`) | doc-derived only — `tools/ce-fetch.py` harvests per-page Link Library rows into `build/rows.json`; `tools/gen-doc-def.py` writes the committed defs; `llvm-dlltool` builds the import libs. Current: coredll **611** (incl. the 89 M45 TAPI client functions + TSPI_lineForward, the 42 M47 Crypt* and the 9 M51 Sip* functions), coredll-adjacent (coreloc, commctrl, msgque, ...), ws2 **100**, **ole32 84**, **oleaut32 222**, coreimm **56**, crypt32 **83**, winscard **28**, aygshell **33** |
| Real-toolchain compile matrix (headers + TU, `-Werror`) | passing: `make crosscheck WINCECLANG=...` for arm/i386 × CE 4.2/5.0/6.0 (all 37 headers standalone + full TU) |
| End-to-end links (wince-crt + wince-api consumer, against doc-derived import libraries) | shipped (M37+, extended M39–M44, M49–M51): `make e2e` links the tests/e2e consumers (main app / WinMain app / DLL) on all six arm/i386-pc-wince{4.2,5.0,6.0} targets; PE machine/CE-subsystem/import names asserted for coredll.dll (incl. the M51 Sip* names), ws2.dll, ole32.dll/oleaut32.dll, crypt32.dll, winscard.dll and aygshell.dll |
| Queued (page-grounded, official pages in corpus) | remaining CE books not yet harvested in full (CE 4.2 book pages, Standard Shell / Common Controls books), other second-order DLLs, the held Winsock/TSPI/IMM/crypto/smart-card/AYGShell/SIP constant sets (names published without values; documented on-device readback owed) |

## Ordering principle

1. coredll core (this package must make a console-less CE "hello"
   program with wince-crt compile and link);
2. then per-DLL batches, each function grounded on its official page;
3. def/import-library production once the header set covers a DLL's
   surface; the def is exactly the pages' documented Link Library
   rows (no dump or binary inspection).

Every batch adds only page-grounded declarations; the third-party
tree is never consulted for content.
