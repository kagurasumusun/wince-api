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
| `GetExitCodeThread` | `ms885623` | CE 1.01 and later | Winbase.h | Coredll.lib | STILL_ACTIVE while running; thread-fn return value is a documented exit status |
| `Sleep` | `aa450900` | CE 1.0 and later | Winbase.h | Coredll.lib | Sleep(INFINITE) == SuspendThread(GetCurrentThread()) on CE (resumable), unlike desktop |
| `GetThreadPriority` | `ms885643` | CE 1.0 and later | Winbase.h | Coredll.lib | legacy 8-level scale; THREAD_PRIORITY_ERROR_RETURN on failure; CE has no priority classes |
| `SetThreadPriority` | `aa450891` | CE 1.0 and later | Winbase.h | Coredll.lib | starts at THREAD_PRIORITY_NORMAL; legacy scale 0..7 |
| `PROCESS_INFORMATION` struct | `ms886775` | CE 1.0 and later | Winbase.h | — | fields hProcess/hThread/dwProcessId/dwThreadId; filled by CreateProcess |
| ThreadProc / `LPTHREAD_START_ROUTINE` | `aa450940` | CE 1.01 and later | developer-defined | — | return value readable via GetExitCodeThread |
| `THREAD_PRIORITY_*` constants | `aa450596` + `ms885643` + `aa450891` | — | Winbase.h | — | 0..7 legacy scale, NORMAL=3 maps to new-level 251; priority table ranges 0..255 with 0 highest |
| `INFINITE` | `aa450900` | — | Winbase.h | — | wait/delay constant |
| `SuspendThread` | `aa450913` | CE 1.0 and later | Winbase.h | Coredll.lib | suspend count (max MAXIMUM_SUSPEND_COUNT); fails while thread is in a kernel call — may need repeats (CE note) |
| `ResumeThread` | `ms886801` | CE 1.0 and later | Winbase.h | Coredll.lib | returns previous suspend count: 0 not suspended / 1 restarted / >1 still suspended |
| `TlsAlloc` | `aa450945` | CE 1.0 and later | **Winuser.h (per page)** | Coredll.lib | 0xFFFFFFFF = failure; TLS_MINIMUM_AVAILABLE ≥ 64; TLS indexes not valid across processes |
| `TlsFree` | `aa450947` | CE 1.0 and later | Winbase.h | Coredll.lib | does not free dynamic storage; call at process detach |
| `TlsSetValue` | `aa450951` | CE 1.0 and later | Winbase.h | Coredll.lib | minimal validation: index 0..TLS_MINIMUM_AVAILABLE-1 |
| `TlsGetValue` | `aa450949` | CE 1.0 and later | Winbase.h | Coredll.lib | clears last error on success; NULL-before-set guaranteed only CE 3.0+ |
| `LoadLibraryEx(W)` | `ms886737` | CE 3.0 and later | Winbase.h | Coredll.lib | hFile reserved NULL; flags per CE page: DONT_RESOLVE_DLL_REFERENCES, LOAD_LIBRARY_AS_DATAFILE (implies DONT_RESOLVE), LOAD_WITH_ALTERED_SEARCH_PATH = not supported; CE loads a module once so flags stick |
| `CreateFile(W)` | `aa517318` | CE 1.0 and later | Winbase.h | Coredll.lib | security attr + template ignored (NULL); no current dir; \Windows+root search; ROM modules not accessible; INVALID_HANDLE_VALUE on failure; export CreateFileW |
| `DeleteFile(W)` | `ms889001` | CE 1.0 and later | Winbase.h | Coredll.lib | fails if missing or open/mapped; dirs need RemoveDirectory; export DeleteFileW |
| `GetFileAttributes(W)` | `ms890895` | CE 1.0 and later | Winbase.h | Coredll.lib | 0xFFFFFFFF failure; attribute list incl. CE ROM attrs; export GetFileAttributesW |
| `FindFirstFile(W)` | `ms889678` | CE 1.0 and later | Winbase.h | Coredll.lib | wildcards `*`/`?`; INVALID_HANDLE_VALUE failure; name-only search; export FindFirstFileW |
| `FindNextFile(W)` | `ms889873` | CE 1.0 and later | Winbase.h | Coredll.lib | ERROR_NO_MORE_FILES at end; export FindNextFileW |
| `FindClose` | `ms889619` | CE 1.0 and later | Winbase.h | Coredll.lib | file search handles only (DB handles: CloseHandle) |
| `ReadFile` | `ms891445` | CE 1.0 and later | Winbase.h | Coredll.lib | synchronous only; lpOverlapped unsupported (NULL); lpNumberOfBytesRead zeroed before work; at EOF nonzero return with zero count; hFile needs GENERIC_READ, cannot be a socket |
| `WriteFile` | `ms892380` | CE 1.0 and later | Winbase.h | Coredll.lib | synchronous; lpOverlapped NULL; zero count is a null write (stamp changes, no truncate); hFile needs GENERIC_WRITE; truncation only via SetEndOfFile |
| `GetFileSize` | `ms890939` | CE 1.0 and later | Winbase.h | Coredll.lib | returns low 32 bits; lpFileSizeHigh optionally receives high 32; 0xFFFFFFFF failure — disambiguate with GetLastError |
| `SetFilePointer` | `ms891933` | CE 1.0 and later | Winbase.h | Coredll.lib | lpDistanceToMoveHigh not supported (NULL or points to zero); CE size limit 0xFFFFFFFF; 0xFFFFFFFF return is ambiguous — check GetLastError; not for non-seeking devices |
| `SetEndOfFile` | `ms891916` | CE 1.0 and later | Winbase.h | Coredll.lib | truncate/extend to current file pointer; GENERIC_WRITE; extended region contents undefined |
| `FlushFileBuffers` | `ms890238` | CE 1.0 and later | Winbase.h | Coredll.lib | writes buffered data to storage; comm-device handle flushes transmit buffer; GENERIC_WRITE |
| `MoveFile(W)` | `ms891388` | CE 1.0 and later | Winbase.h | Coredll.lib | renames/moves file or directory incl. children; new name must not exist; directory moves across volumes fail; Unicode-only → export MoveFileW |
| `CopyFile(W)` | `aa517309` | CE 1.0 and later | Winbase.h | Coredll.lib | copies an existing file incl. its attributes; bFailIfExists TRUE fails on existing destination, FALSE overwrites; not for directories; Unicode-only → export CopyFileW |
| `CreateDirectory(W)` | `aa517316` | CE 1.0 and later | Winbase.h | Coredll.lib | not recursive (missing parent ⇒ ERROR_PATH_NOT_FOUND); lpSecurityAttributes ignored (NULL); MAX_PATH default limit; CE 5.0+ canonicalization ignores trailing backslashes; Unicode-only → export CreateDirectoryW |
| `RemoveDirectory(W)` | `ms891470` | CE 1.0 and later | Winbase.h | Coredll.lib | empty directories only; caller needs delete access; Unicode-only → export RemoveDirectoryW |
| `SetFileAttributes(W)` | `ms891925` | CE 1.0 and later | Winbase.h | Coredll.lib | sets FILE_ATTRIBUTE_* combination; FILE_ATTRIBUTE_DIRECTORY cannot be set (use CreateDirectory); ROM FS unaffected; NORMAL is overridden by any other value; Unicode-only → export SetFileAttributesW |
| `OVERLAPPED` opaque tag, `FILE_BEGIN/CURRENT/END`, `INVALID_SET_FILE_POINTER`, `PLONG` | opaque tag: lpOverlapped "Unsupported; set to NULL" (`ms891445`, `ms892380`); move-method names per `ms891933`; numeric values per official Win32 File Management reference | — | Winbase.h / Windef.h | — | CE has no asynchronous file I/O; the opaque tag admits only the required NULL |
| `FILETIME` struct | `ms885586` | CE 1.0 and later | Winbase.h | — | 100ns since 1601; low/high DWORD halves |
| `WIN32_FIND_DATAW` struct | `ms892378` | CE 1.0 and later | Winbase.h | — | CE layout: dwOID, no cAlternateFileName; UTC times; long-name support |
| `FILE_ATTRIBUTE_*` / GENERIC / share / disposition / flag constants | names per CE pages (`aa517318`, `ms892378`, `ms890895`); values per official Win32 File Attribute Constants + Generic Access Rights references (INROM/ROMMODULE bit values parity-checked) | — | Winbase.h | — | ROMSTATICREF named by CE pages but value not yet defined (pending official numeric source) |
| `MAX_PATH` (windef.h) | cited by `aa517318`/`ms889678`/`ms890895` | — | Windef.h | — | Win32 ABI value 260 |
| `ERROR_NO_MORE_FILES` | `ms889873` | — | Winerror.h | — | value 18 |
| `INVALID_HANDLE_VALUE` | `aa517318`/`ms889678` | — | Winbase.h | — | ((HANDLE)-1) |
| `SYSTEMTIME` struct | `aa450923` | CE 1.0 and later | Winbase.h | — | 8 WORD fields in order year..ms; wDayOfWeek ignored by SetLocalTime/SystemTimeToFileTime |
| `GetLocalTime` | `ms885628` | CE 1.0 and later | Winbase.h | Coredll.lib | current local time (TZ/DST-adjusted); returns void |
| `GetSystemTime` | `ms885640` | CE 1.0 and later | Winbase.h | Coredll.lib | current system time in UTC; returns void |
| `SetLocalTime` | `ms886818` | CE 1.0 and later | Winbase.h | Coredll.lib | wDayOfWeek ignored; nonzero success, zero failure (GetLastError) |
| `SetSystemTime` | `aa450867` | CE 1.0 and later | Winbase.h | Coredll.lib | sets UTC time; nonzero success, zero failure (GetLastError) |
| `FileTimeToLocalFileTime` | `ms885589` | CE 1.0 and later | Winbase.h | Coredll.lib | out param must not alias in; uses TZ + DST current settings |
| `LocalFileTimeToFileTime` | `ms886740` | CE 1.0 and later | Winbase.h | Coredll.lib | out param must not alias in |
| `FileTimeToSystemTime` | `ms885593` | CE 1.0 and later | Winbase.h | Coredll.lib | fails for FILETIME ≥ 0x8000000000000000 |
| `SystemTimeToFileTime` | `aa450925` | CE 1.0 and later | Winbase.h | Coredll.lib | wDayOfWeek ignored; nonzero success, zero failure |
| System error-code block (winerror.h rows 0–1078) | `aa450919` (System Errors - Numerical Order, Windows CE 5.0) | — | Winerror.h | — | full numeric table transcribed (0–1078 incl. registry 1009–1022 and service 1051–1078 groups); rows the CE table omits stay undefined; names/values are ABI facts; index page `aa450740` |
| `ERROR_NO_UNICODE_TRANSLATION` | outside rows above; cited by `ms915519`/`ms961248` | — | Winerror.h | — | value 1113 |
| Export defs (`def/coredll{,4,6,-x86}.def`) | names/ordinals = OS facts from the device-dump-audited toolchain export surface | — | — | coredll.dll | generation mapping: coredll=CE5, coredll4=CE4, coredll6=CE6 ARM, coredll6-x86=CE6 x86; **regenerated by `./gen-defs.sh` from the audited surface and not committed** (see README) |

### Documented conflicts (official page vs verified export surface)

| Item | Official page says | Verified coredll surface (CE 4/5/6 × ARM/x86) | Resolution |
|---|---|---|---|
| `GetCurrentProcess` | `ms885613` (CE 1.0+): Header **Kfuncs.h**, Link Library Coredll.lib | absent from all four audited defs | Kfuncs.h = kernel-function header; function is kernel-scope on CE (Cf. CeGCC w32api kfuncs.h static inlines — existence/parity only, not a source). Not declared in user-mode headers. |
| `GetCurrentProcessId` | `ms885614` (CE 1.0+): Header **Kfuncs.h**, Link Library Coredll.lib | absent from all four audited defs | same as above |
| `GetCurrentThread` | `ms885615` (CE 1.0+): Header **Kfuncs.h**, Link Library Coredll.lib | absent from all four audited defs | same family; note aa450900 (Sleep) itself cites GetCurrentThread() as the CE equivalent of Sleep(INFINITE) |
| `GetCurrentThreadId` | `ms885616` (CE 1.0+): Header **Kfuncs.h**, Link Library Coredll.lib | absent from all four audited defs | same as above |
| `ExitProcess` | `ms885217`: Header Windows.h | absent (recorded in windows.h note) | declared in windows.h for source compatibility, link fails on genuine import libs (see windows.h) |

(Conflict model: official docs are the authority for the *documented API*; the audited
toolchain import surface is the authority for *what links*; when they disagree the item
is listed here instead of silently declaring or silently dropping.)
| Structures | `PROCESS_INFORMATION`, `FILETIME`, `SYSTEMTIME`, `WIN32_FIND_DATAW` defined from their official structure pages; `SECURITY_ATTRIBUTES`/`STARTUPINFOW`/`OVERLAPPED` are opaque NULL-only tags per the CE pages' "Not supported; set to NULL" (process `ms885182`, file I/O `ms891445`/`ms892380`) | — | Winbase.h | — | struct layouts per official pages; opaque tags deliberately un-instantiable |

## Export-surface cross-check

The earlier (M1–M7) declarations' spellings were matched against the
verified CE 4/5/6 coredll export surface (import libraries of the
toolchain sysroot; device-dump-audited defs, `audit-coredll.py`):

* W spellings exported on all generations: `GetModuleHandleW`,
  `GetModuleFileNameW`, `GetCommandLineW`, `GetProcAddressW`,
  `CreateProcessW`, `LoadLibraryW`; `A` spelling: `GetProcAddressA`.
* Undecorated single names: `TerminateProcess`, `TerminateThread`,
  `ExitThread`, `GetLastError`, `CreateThread`, `FreeLibrary`,
  `LocalAlloc`, `LocalFree`.
* `ExitProcess`: not exported on any generation (conflict above).

The M8 file/directory spellings follow the same documented rule
(Windows CE is Unicode-only ⇒ the base names map to the W exports,
plain names for the handle-based I/O functions).  The audited defs
are regenerated out-of-tree (`./gen-defs.sh`) and re-checked against
the export surface on the next audit run.

## Remaining verification (roadmap)

* Each new function's official page is fetched and its Requirements
  row transcribed into this matrix before it ships.
* Pointer model: 32-bit pointer/`ULONG_PTR` assertions run under the
  CE toolchain; the freestanding `-Werror` compile matrix for
  `arm/i386-pc-wince{4.2,5.0,6.0}` (headers + TU) passes since M8
  (`make crosscheck WINCECLANG=...`).
* x86 decoration: link checks with `llvm-dlltool -m i386
  --no-leading-underscore` import libraries, mirroring wince-crt.
* End-to-end: link wince-crt + Akari API consumer TUs against the
  sysroot import libraries on `arm-pc-wince` and `i386-pc-wince`
  (needs the regenerated audited import surface).
