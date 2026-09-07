# Akari API (wince-api)

Clean-room **Win32 API headers for Windows CE 4.x / 5.x / 6.x** — the
replacement for the "w32api" role of the CE toolchain sysroot, written
from scratch for **Clang/lld** targets (`arm-pc-wince` armel, x86 CE,
CE 4.2/5.0/6.0), under the same conditions as
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
| Coredll **import libraries** per CE generation/arch | **Akari API** (`def/` sources, generated `.a` via `llvm-dlltool`) — in progress |
| CRT startup glue (entries, argv, ctors) | [wince-crt](https://github.com/kagurasumusun/wince-crt) |
| C run-time library (libc) headers/objects | out of scope (libc provider) |

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
                    empty, WCHAR 16-bit)
include/winbase.h   base OS API: process/thread, module, command
                    line, dynamic-link, local memory (M1)
def/                self-authored coredll export defs per CE
                    generation and architecture (planned)
docs/inventory.md   per-declaration official-source matrix
                    (page ID, OS Versions, Header, Link Library)
tests/host/         host compile checks (types, syntax, mappings)
Makefile            make check  (host syntax/type checks for CE
                    0x420/0x500/0x600)
```

## Build and check

```sh
make check          # host: headers + TU compile warning-free under
                    # _WIN32_WCE = 0x420 / 0x500 / 0x600
```

Cross checks with the real toolchain (32-bit pointer model, link
against the sysroot import libraries, x86 decoration) run in a later
phase exactly like wince-crt's: build with the `LLVM-WinCE` toolchain
and link end-to-end against the verified sysroot.  See
`docs/verification.md`.

## Status / roadmap

* **M1 (landed):** repository foundation + windef/winbase/windows.h
  declaring exactly the functions whose official CE pages were
  fetched and transcribed — TerminateProcess, TerminateThread,
  ExitThread, ExitProcess (with its documented export conflict),
  GetModuleHandle(W), GetModuleFileName(W), GetCommandLine(W),
  GetProcAddress(W/A), LocalAlloc, LocalFree.  Host checks pass.
* **M2 (landed):** process/thread/module/error batch from official
  pages fetched in full: GetLastError (`ms885627`), CreateThread
  (`ms885186`, incl. the CE-only STACK_SIZE_PARAM_IS_A_RESERVATION
  note), CreateProcessW (`ms885182`, CE-specific signature and
  unsupported-parameter rules), LoadLibraryW (`ms886736`),
  FreeLibrary (`ms885601`); `PROCESS_INFORMATION` defined,
  `SECURITY_ATTRIBUTES`/`STARTUPINFOW` opaque NULL-only tags;
  `docs/clean-room.md` (definition and scope of the clean-room
  conditions), `docs/generations.md` (official sources per CE
  generation) and `docs/parity-target.md` (CeGCC w32api replacement
  scope, measured) added.  Host checks pass.
* **M3:** next official-page batches — remaining winbase families
  (queued with official IDs: OpenProcess `ms886766`, GetExitCode*
  `ms885622`/`ms885623`, ResumeThread `ms886801`, CloseHandle
  `aa517300`, LoadLibraryEx `ms886737`, SetLastError `ms886817`,
  Error Values `aa450740`, category index Process and Thread
  Functions `aa450760`), then winuser/winreg and the rest; each
  function added only after its official page is fetched into
  `docs/inventory.md`.
* **M4:** import-library deliverables: self-authored `coredll*.def`
  per CE generation (4/5/6) and architecture (ARM/x86), generated
  with `llvm-dlltool`, validated against the verified export surface.
* **M5:** end-to-end link verification with wince-crt on the
  `LLVM-WinCE` toolchain (host + cross), and the documented
  discrepancies review (the ExitProcess page conflict is the model).
* **M3:** import-library deliverables: self-authored `coredll*.def`
  per CE generation (4/5/6) and architecture (ARM/x86), generated
  with `llvm-dlltool`, validated against the verified export surface;
  consumer-side headers (`winuser.h`, `winreg.h`, ...) as their
  functions land.
* **M4:** end-to-end link verification with wince-crt on the
  `LLVM-WinCE` toolchain (host + cross), and the documented
  discrepancies review (the ExitProcess page conflict is the model).

## Verification rules (same as wince-crt)

1. Implement only from official pages + official ABI references;
   record the page ID next to every declaration.
2. Anything not covered by official text is marked *own design* in
   `docs/inventory.md` and decided from the verified toolchain's
   observable output — never from a third-party implementation's
   behavior alone.
3. Warning-free host checks; cross checks with the real toolchain
   import libraries; every commit pushed immediately.
