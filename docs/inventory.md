# Inventory and verification matrix

Every item shipped in `include/` is transcribed from an official
Microsoft documentation page.  For CE APIs the source is the
CE-era MSDN archive now served on learn.microsoft.com as
`https://learn.microsoft.com/en-us/previous-versions/windows/embedded/<ID>(v=msdn.10)`.
The per-page **Requirements** block (OS Versions / Header / Link
Library) is recorded below verbatim in condensed form.  Where no CE
page exists (or the CE page is silent), the basis is named explicitly
and the item is marked accordingly — never inferred from a
third-party implementation.

## Type and macro basis (`windef.h`)

| Item | Basis |
|---|---|
| Windows CE Unicode-only ⇒ `TCHAR`/`LPTSTR`/`LPCTSTR` are the wide forms | official CE function pages: "Windows CE supports only the Unicode version of this function" (e.g. GetCommandLine `ms885605`, GetCommandLine `ms928607`) |
| `WCHAR` is 16-bit | CE wchar_t ABI of the verified toolchain target (clang `*-pc-wince`: 16-bit wchar_t); module handles equal base addresses per DllMain doc `ms885202` |
| `WINAPI`/`APIENTRY`/`CALLBACK` empty | Microsoft documents CE functions as `__cdecl` (/ENTRY `aa449732`, "Linking to the CRT" `ms859584`); ARM `__cdecl`= `__stdcall`; x86 CE export names carry no `@n` decoration (verified import surface) |
| Integer widths (DWORD 32, LONG 32, ...) | documented Win32 data-type semantics; `stdint.h` typedefs keep widths explicit |
| Flag values `LMEM_FIXED` 0x0000, `LMEM_ZEROINIT` 0x0040, `LPTR` | names and meanings: LocalAlloc `ms886739`; numeric values: official Win32 memory-management reference (ABI values) |

## M1 functions (`winbase.h`, `windows.h`)

All pages fetched in full unless marked (snip) = full content seen in
the official page body via the Learn archive.

| Function | Official page (CE 5.0 archive) | OS Versions | Header | Link Library | Notes |
|---|---|---|---|---|---|
| `TerminateProcess` | `aa450927` | CE 1.0 and later | Winbase.h | Coredll.lib | also CE 3.0-era page `ms913239` (CE 1.0+, same link lib) |
| `TerminateThread` | `aa450930` | CE 1.01 and later | Winbase.h | Coredll.lib | |
| `ExitThread` | `ms885219` | CE 1.0 and later | Winbase.h | Coredll.lib | |
| `ExitProcess` | `ms885217` | CE 2.0 and later | Windows.h | Coredll.lib | **documented conflict**: absent from every CE 4/5/6 coredll import library of the verified sysroot; CE toolchain headers declare it as inline `TerminateProcess(GetCurrentProcess(), code)`.  Declared for source compatibility; calls fail at link time.  See wince-crt audit |
| `GetModuleHandleW` | `ms885630` | CE 2.10 and later | Winbase.h | Coredll.lib, Nk.lib | NULL ⇒ pseudo-handle of current process; W-only export |
| `GetModuleFileNameW` | `ms885629` | CE 2.0 and later | Winbase.h | Coredll.lib | nSize in characters; W-only export |
| `GetCommandLineW` | `ms885605` | CE 3.0 and later | Winbase.h | Coredll.lib | remarks: Unicode-only; W-only export |
| `GetProcAddressW` / `GetProcAddressA` | `ms885634` | CE 1.0 and later (W); A: CE 3.0+ per Remarks | Winbase.h | Coredll.lib | lpProcName Unicode for the W form; both exports present in the CE 4/5/6 import libraries (verified) |
| `LocalAlloc` | `ms886739` | CE 1.0 and later | Winbase.h | Coredll.lib | CE: local heap = global heap; LPTR = fixed + zeroinit; NULL = failure |
| `LocalFree` | `ms886741` | CE 1.0 and later | Winbase.h | Coredll.lib | NULL on success; NULL argument ignored |
| `GetLastError` | `ms885627` | CE 1.0 and later | Winbase.h | Coredll.lib, Nk.lib | per-thread; page points to official Error Values `aa450740` (constants batch) and WINERROR.H |
| `CreateThread` | `ms885186` | CE 1.01 and later | Winbase.h | Coredll.lib | lpsa ignored/NULL; cbStack ignored unless CE-only STACK_SIZE_PARAM_IS_A_RESERVATION; 64 KB default reservation |
| `CreateProcessW` | `ms885182` | CE 1.0 and later | Winbase.h | Coredll.lib | CE-specific W signature; psaProcess/psaThread/fInheritHandles/pvEnvironment/pszCurDir/psiStartInfo not supported (NULL/FALSE); pszCmdLine NULL ⇒ image name as command line; .EXE appended when no extension; no priority classes; search order \windows, root, OEM dir, (CE 2.10+) \ceshell; not from DllMain |
| `LoadLibraryW` | `ms886736` | CE 1.0 and later | Winbase.h | Coredll.lib | loaded once, mapped per process; paths ignored for module identity; .cpl treated as .dll; .dll appended by default; search order + HKEY_LOCAL_MACHINE\Loader\SystemPath (≤260 chars); not from DllMain |
| `FreeLibrary` | `ms885601` | CE 1.0 and later | Winbase.h | Coredll.lib | per-process refcount; DllMain DLL_PROCESS_DETACH at zero; not from DllMain |
| `CloseHandle` | `aa517300` | CE 1.0 and later | Winbase.h | Coredll.lib | closes file/event/mutex/process/thread/socket handles; does not terminate threads |
| `OpenProcess` | `ms886766` | CE 2.0 and later | Winbase.h | Coredll.lib | fdwAccess not supported (0); fInherit not supported (FALSE) |
| `GetExitCodeProcess` | `ms885622` | CE 2.0 and later | Winbase.h | Coredll.lib | STILL_ACTIVE while running; main/WinMain return values are documented termination statuses |
| `SetLastError` | `ms886817` | CE 1.0 and later | Winbase.h | Coredll.lib | per-thread last error; bit 29 reserved for application codes |
| Error constants (`winerror.h`) | names cited per CE page (ms885186, ms885622, ms885182, ms914104, ms915519/ms961248); values per official Win32 System Error Codes reference | — | Winerror.h | — | full CE list = official Error Values `aa450740` (later batch) |
| Export defs (`def/coredll{,4,6,-x86}.def`) | names/ordinals = OS facts from the device-dump-audited toolchain export surface | — | — | coredll.dll | generation mapping: coredll=CE5, coredll4=CE4, coredll6=CE6 ARM, coredll6-x86=CE6 x86 |
| Structures | `PROCESS_INFORMATION` defined (hProcess, hThread, dwProcessId, dwThreadId; handles with ALL_ACCESS per `ms885182`; official structure page `ms886775` pending full transcription).  `SECURITY_ATTRIBUTES`/`STARTUPINFOW`: opaque NULL-only tags per "Not supported; set to NULL" (`ms885182`) | — | Winbase.h | — | full layouts in structure batches |

## Export-surface cross-check

The declarations' spellings were matched against the verified CE 4/5/6
coredll export surface (import libraries of the toolchain sysroot;
device-dump-audited defs, `audit-coredll.py`):

* W spellings exported on all generations: `GetModuleHandleW`,
  `GetModuleFileNameW`, `GetCommandLineW`, `GetProcAddressW`,
  `CreateProcessW`, `LoadLibraryW`; `A` spelling: `GetProcAddressA`.
* Undecorated single names: `TerminateProcess`, `TerminateThread`,
  `ExitThread`, `GetLastError`, `CreateThread`, `FreeLibrary`,
  `LocalAlloc`, `LocalFree`.
* `ExitProcess`: not exported on any generation (conflict above).

## Remaining verification (roadmap)

* M2/M3 declarations: fetch each function's official page, transcribe
  its Requirements row into this matrix, then declare.
* Pointer model: 32-bit pointer/`ULONG_PTR` assertions run under the
  CE toolchain (host checks assert them only on 32-bit hosts).
* x86 decoration: link checks with `llvm-dlltool -m i386
  --no-leading-underscore` import libraries, mirroring wince-crt.
* End-to-end: link wince-crt + Akari API consumer TUs against the
  sysroot import libraries on `arm-pc-wince` and `i386-pc-wince`.
