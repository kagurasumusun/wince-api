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

## Coverage status

| Area | Status |
|---|---|
| `windows.h` umbrella | shipped (M1) |
| `windef.h` base types/macros | shipped (M1) |
| `winbase.h` — process/thread/module/memory/error core | M1–M8 shipped (ExitProcess = documented conflict, declared for source compat; kernel-scope kfuncs intentionally not declared) |
| Structures (PROCESS_INFORMATION, FILETIME, SYSTEMTIME, WIN32_FIND_DATAW defined; SECURITY_ATTRIBUTES/STARTUPINFOW/OVERLAPPED opaque NULL-only tags) | shipped (M1–M8) |
| Constants (`winerror.h` rows 0–1078 from official numeric table `aa450919`; file/directory + creation/flag + priority + TLS + load-library values) | shipped (M1–M8) |
| Remaining winbase families (heap, sync/wait, string, registry) | queued; official page per function |
| GUI: `winuser.h` (WinMain, windows, messages, controls) | queued (WinMain page `ms914104` already in wince-crt records) |
| Import-library defs (`def/coredll-doc.def` + more per harvested DLL) | M9: derived from the official documentation pages only — `tools/ce-manifest.py` + `tools/ce-fetch.py` harvest the per-page Link Library rows into `build/rows.json`; `tools/gen-doc-def.py` writes the committed def; `llvm-dlltool` builds the import lib. Grows as more reference books are harvested |
| Real-toolchain compile matrix (headers + TU, `-Werror`) | passing since M8 (now M9 sync + winnt.h): `make crosscheck WINCECLANG=...` for arm/i386 × CE 4.2/5.0/6.0 |
| End-to-end links (wince-crt + wince-api consumer, against doc-derived import libraries) | shipped (M37): `make e2e` links the tests/e2e consumers (main app / WinMain app / DLL) with the Akari CRT against the doc-derived `llvm-dlltool` import libraries on all six arm/i386-pc-wince{4.2,5.0,6.0} targets; PE machine/CE-subsystem/import names asserted |

## Ordering principle

1. coredll core (this package must make a console-less CE "hello"
   program with wince-crt compile and link);
2. then per-DLL batches, each function grounded on its official page;
3. def/import-library production once the header set covers a DLL's
   surface; cross-verified against the device-dump-audited export
   surface.

Every batch adds only page-grounded declarations; the third-party
tree is never consulted for content.
