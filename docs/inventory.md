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

### M9: Synchronization Reference batch (winbase.h + winnt.h)

All function pages are official `(v=msdn.10)` CE 5.0 pages under
*Core OS Reference → Synchronization Reference*.  Page-derived
Requirement rows vary between Coredll.lib, "Coredll.lib, Nk.lib",
"Nk.lib" and "Coremain.lib"; rows are transcribed verbatim in the
table and their import-provider interpretation is discussed under
"Link-library row notes" below.

| Item | Official page | OS Versions | Header | Link Library (page row) | Notes |
|---|---|---|---|---|---|
| `CreateEvent(W)` | `ms885177` | CE 1.0+ | Winbase.h | Coredll.lib, Nk.lib | lpEventAttributes ignored/NULL; manual/auto reset; name ≤ MAX_PATH, no backslash, case-sensitive; existing name ⇒ ERROR_ALREADY_EXISTS; EVENT_ALL_ACCESS; Unicode-only export CreateEventW |
| `OpenEvent(W)` | `ms886764` | CE .NET 4.0+ | Winbase.h | Coredll.lib | dwDesiredAccess must be EVENT_ALL_ACCESS; bInheritHandle FALSE; export OpenEventW |
| `SetEvent` | `ms886810` | CE 1.0+ | Kfuncs.h (page) | Coredll.lib | sets signaled; kernel-scope header row, user-mode export |
| `ResetEvent` | `ms886800` | CE 1.0+ | Kfuncs.h (page) | Coredll.lib | sets nonsignaled; as SetEvent |
| `PulseEvent` | `ms886784` | CE 1.0+ | Winbase.h | Coredll.lib | signal/release/reset in one operation |
| `CreateMutex(W)` | `ms885181` | CE 1.01+ | Winbase.h | Coredll.lib, Nk.lib | attributes ignored; bInitialOwner; ERROR_ALREADY_EXISTS on existing name; export CreateMutexW |
| `ReleaseMutex` | `ms886797` | CE 1.01+ | Winbase.h | Nk.lib (page) | caller must own the mutex |
| `CreateSemaphore(W)` | `ms885184` | CE 3.0+ | Winbase.h | Nk.lib (page) | counts LONG; lInitialCount 0..lMaximumCount; attributes ignored; export CreateSemaphoreW |
| `ReleaseSemaphore` | `ms886798` | CE 3.0+ | Winbase.h | Coredll.lib | lReleaseCount>0; previous count via lpPreviousCount |
| `WaitForSingleObject` | `aa450988` | CE 1.0+ | Winbase.h | Coredll.lib | CE time-out cap 0x7FFFFFFF; WAIT_OBJECT_0/TIMEOUT/FAILED; waitable: event, mutex, semaphore (3.0+), process, thread |
| `WaitForMultipleObjects` | `aa450987` | CE 1.01+ | Winbase.h | Nk.lib (page) | nCount ≤ MAXIMUM_WAIT_OBJECTS; WAIT_OBJECT_0+n / WAIT_ABANDONED_0+n |
| `DuplicateHandle` | `ms885208` | CE .NET 4.0+ | Windows.h (page) | Coredll.lib | CE: dwDesiredAccess ignored, bInheritHandle FALSE; DUPLICATE_CLOSE_SOURCE / DUPLICATE_SAME_ACCESS |
| `InitializeCriticalSection` | `ms885665` | CE 1.0+ | Winbase.h | Coremain.lib (page) | VOID; object per RTL_CRITICAL_SECTION (winnt.h) |
| `EnterCriticalSection` | `ms885212` | CE 1.0+ | Winbase.h | Coremain.lib (page) | VOID |
| `LeaveCriticalSection` | `ms886733` | CE 1.0+ | Winbase.h | Coremain.lib (page) | VOID |
| `DeleteCriticalSection` | `ms885196` | CE 1.0+ | Winbase.h | Coremain.lib (page) | VOID |
| `TryEnterCriticalSection` | `aa450959` | CE 3.0+ | Winbase.h | Coredll.lib | nonzero on success |
| `InterlockedExchange` | `ms885670` | CE .NET 4.0+ | Windows.h (page) | Coredll.lib | |
| `InterlockedIncrement` | `ms885673` | CE .NET 4.0+ | Windows.h (page) | Coredll.lib | returns new value |
| `InterlockedDecrement` | `ms885669` | CE .NET 4.0+ | Windows.h (page) | Coredll.lib | returns new value |
| `InterlockedExchangeAdd` | `ms885671` | CE .NET 4.0+ | Windows.h (page) | Coredll.lib | returns original value |
| `InterlockedCompareExchange` | `ms885667` | CE .NET 4.0+ | Windows.h (page) | Coredll.lib | returns original value |
| `InterlockedTestExchange` | `ms885674` | CE .NET 4.0+ | Winbase.h | Coredll.lib | CE-only conditional set; returns old value |
| `InterlockedExchangePointer` | `ms885672` | CE .NET 4.0+ | Winbase.h | Coredll.lib | |
| `InterlockedCompareExchangePointer` | `ms885668` | CE .NET 4.0+ | Winbase.h | Coredll.lib | |
| `RTL_CRITICAL_SECTION`/`CRITICAL_SECTION`, `PRTL_CRITICAL_SECTION_DEBUG` | desktop-official debugger structure reference (offsets 0x0/0x4/0x8/0xc/0x10/0x14, 24 bytes on 32-bit) | — | Winnt.h | — | CE publishes no separate layout; desktop-official member order used, see link-library/ABI note below |
| `LONGLONG`/`ULONGLONG`/`LARGE_INTEGER`/`ULARGE_INTEGER` | official Windows Data Types / LARGE_INTEGER structure reference | — | Winnt.h | — | union with anonymous LowPart/HighPart + QuadPart |
| `WAIT_OBJECT_0`, `WAIT_ABANDONED_0`, `WAIT_TIMEOUT`, `WAIT_FAILED`, `MAXIMUM_WAIT_OBJECTS` | names per `aa450988`/`aa450987`; numeric values per the fixed Win32 wait-result ABI | — | Winbase.h | — | |
| `DUPLICATE_CLOSE_SOURCE`, `DUPLICATE_SAME_ACCESS` | names per `ms885208`; values per official DuplicateHandle reference | — | Winbase.h | — | |
| `EVENT_ALL_ACCESS` | `ms886764`; value per official synchronization access-rights reference | — | Winbase.h | — | |

### M9 link-library and ABI notes (documented, not inferred)

* Several M9 pages list **Nk.lib** or **Coremain.lib** as the only
  Link Library (ReleaseMutex, CreateSemaphore, WaitForMultipleObjects,
  the four base critical-section functions).  Those rows are
  transcribed verbatim.  The doc-derived coredll export def includes
  only functions whose page row names **Coredll.lib** (see the def
  section below); the Nk/Coremain-named functions are tracked
  separately and flagged for device-surface verification, exactly like
  the ExitProcess conflict model.
* Windows CE publishes no critical-section object layout, so
  `CRITICAL_SECTION` is declared with the desktop-official
  `RTL_CRITICAL_SECTION` member order (Microsoft Learn debugger
  reference; 24 bytes on 32-bit).  This is an *own design* ABI
  decision recorded here, not claimed as CE documentation.
* Pages listing Header **Windows.h** (DuplicateHandle, most
  Interlocked pages) or **Kfuncs.h** (SetEvent/ResetEvent) are
  declared in winbase.h/winnt.h with the page row recorded; the base
  names map to the Unicode exports where the page documents Unicode
  only.
| `ERROR_NO_UNICODE_TRANSLATION` | outside rows above; cited by `ms915519`/`ms961248` | — | Winerror.h | — | value 1113 |
| Export defs (public-info derived) | names = documented exports, taken ONLY from the official per-function "Link Library" rows harvested from the `(v=msdn.10)` pages (see `tools/ce-manifest.py`, `tools/ce-fetch.py`, `tools/gen-doc-def.py`); no shared-source/device-dump/VS/PB-derived names | — | — | coredll.dll | `def/coredll-doc.def` lists pages whose row names Coredll.lib; name-only (ordinals are not published); generated and committed from `build/rows.json` (see README) |

### M10: Time Reference + Memory Management Reference batch (winbase.h)

Harvested from the same manifest pipeline (books *Core OS Reference →
Time Reference* and *Memory Management Reference*; official
`(v=msdn.10)` CE 5.0 pages, already in `build/rows.json`).  All rows
below are transcribed verbatim from the page Requirements; link
libraries are Coredll.lib except where noted.

| Item | Official page | OS Versions | Header | Link Library (page row) | Notes |
|---|---|---|---|---|---|
| `GetTickCount` | `ms885645` | CE 1.0+ | Winbase.h | Coredll.lib | milliseconds since system start |
| `GetFileTime` | `ms885625` | CE 1.0+ | Winbase.h | Coredll.lib | creation/access/write times; hFile needs GENERIC_READ; NULL out-pointers allowed |
| `SetFileTime` | `ms886812` | CE 1.0+ | Winbase.h | Coredll.lib | hFile needs GENERIC_WRITE; NULL in-pointers leave the time unchanged |
| `CompareFileTime` | `ms885172` | CE 1.0+ | Windows.h (page) | Coredll.lib | −1/0/+1 ordering of two 64-bit file times |
| `GetCurrentFT` | `aa451027` | CE 3.0+ | Winbase.h | Coredll.lib | fills a FILETIME with the current system date/time; void |
| `GetIdleTime` | `ms885626` | CE 3.0+ | Winbase.h | Coredll.lib | idle milliseconds; MAXDWORD ⇒ feature unsupported (source of MAXDWORD) |
| `Random` | `ms886791` | CE 1.0+ | Winbase.h | Coredll.lib | CE-only pseudo-random DWORD |
| `SetDaylightTime` | `ms886808` | CE 2.0+ | Winbase.h | Coredll.lib | dst = 1 DST in effect, 0 standard time; void |
| `QueryPerformanceCounter` | `ms886788` | CE 2.0+ | Winbase.h | Coredll.lib | 64-bit count via LARGE_INTEGER |
| `QueryPerformanceFrequency` | `ms886789` | CE 2.0+ | Winbase.h | Coredll.lib | counts per second via LARGE_INTEGER |
| `GetProcessHeap` | `ms885635` | CE 1.0+ | Winbase.h | **Lmem.lib** (page) | handle usable by the Heap* functions; not destroyable; excluded from the coredll def |
| `HeapCreate` | `ms885656` | CE 1.0+ | Winbase.h | Coredll.lib | CE: reserves shared-memory-area memory; dwMaximumSize 0 = growable; HEAP_SHARED_READONLY (kernel mode only) named, numeric value not published |
| `HeapDestroy` | `ms885657` | CE 1.0+ | Winbase.h | Coredll.lib | destroys a HeapCreate heap (not the process heap) without prior HeapFree |
| `HeapAlloc` | `ms885654` | CE 1.0+ | Winbase.h | Coredll.lib | non-movable; HEAP_NO_SERIALIZE ignored (always serialized); HEAP_ZERO_MEMORY; NULL failure, no extended error |
| `HeapFree` | `ms885659` | CE 1.0+ | Winbase.h | Coredll.lib | | 
| `HeapReAlloc` | `ms885661` | CE 1.0+ | Winbase.h | Coredll.lib | HEAP_NO_SERIALIZE ignored |
| `HeapSize` | `ms885662` | CE 1.0+ | Winbase.h | Coredll.lib | actual (≥ requested) size of an allocated block |
| `HeapValidate` | `ms885663` | CE 1.0+ | Winbase.h | Coredll.lib | whole heap when lpMem NULL, else the one block |
| `HeapCompact` | `ms885655` | CE 5.0+ | Winbase.h | Coredll.lib | coalesces free blocks, decommits large ones |
| `LocalReAlloc` | `ms886742` | CE 1.0+ | Winbase.h | Coredll.lib | LMEM_MODIFY changes attributes (uBytes ignored); else LMEM_MOVEABLE/LMEM_ZEROINIT reallocation flags |
| `LocalSize` | `ms886743` | CE 1.0+ | Winbase.h | Coredll.lib | size in bytes of a local memory object |
| `GlobalMemoryStatus` | `ms885649` | CE 1.0+ | Winbase.h | Coredll.lib | fills MEMORYSTATUS; caller sets dwLength first |
| `IsBadCodePtr` | `ms885687` | CE 1.0+ | Winbase.h | Coredll.lib | page itself warns the function is unsafe for input validation |
| `IsBadReadPtr` | `ms885688` | CE 1.0+ | Winbase.h | Coredll.lib | ucb 0 ⇒ valid (returns zero) |
| `IsBadWritePtr` | `ms885689` | CE 1.0+ | Winbase.h | Coredll.lib | as IsBadReadPtr |
| `MEMORYSTATUS`/`LPMEMORYSTATUS` struct | `ms886753` | CE 1.0+ | Winbase.h | — | 8 DWORD members ending at dwAvailVirtual (32 bytes; no desktop-only dwAvailExtendedVirtual on CE) |
| `HEAP_NO_SERIALIZE`, `HEAP_ZERO_MEMORY` | names per `ms885654`/`ms885656` | — | Winbase.h | — | numeric values fixed Win32 ABI (1, 8) |
| `LMEM_MOVEABLE`, `LMEM_MODIFY` | names per `ms886742` (LocalAlloc page `ms886739` defines LMEM_FIXED/ZEROINIT/LPTR) | — | Winbase.h | — | numeric values fixed Win32 ABI (2, 0x80) |
| `MAXDWORD` | cited by `ms885626` | — | Winbase.h | — | `(DWORD)0xFFFFFFFF` |

Note the M10 def effect: after this batch `def/coredll-doc.def` grows
53 → 77 name-only exports (regenerated by `make defdoc`); the coredll
def still excludes GetProcessHeap (Lmem.lib row).

### M11: System Management Reference batch, part 1 (winbase.h)

From *Core OS Reference → System Management Reference*; every page is
official `(v=msdn.10)` and already in `build/rows.json`.

| Item | Official page | OS Versions | Header | Link Library (page row) | Notes |
|---|---|---|---|---|---|
| `SYSTEM_INFO`/`LPSYSTEM_INFO` struct | `aa450921` | CE 1.0+ | Winbase.h | — | anonymous `dwOemId` union first, then page size / min-max addresses / masks / granularity DWORDs and the trailing `wProcessorLevel`/`wProcessorRevision` WORDs (36 bytes, 32-bit CE); `dwProcessorType` obsolete |
| `PROCESSOR_ARCHITECTURE_INTEL/MIPS/SHX/ARM/UNKNOWN` | names per `aa450921`; numeric values fixed Win32 ABI | — | Winbase.h | — | dwProcessorType constants (PROCESSOR_INTEL_386, PROCESSOR_MIPS_R4000, PROCESSOR_HITACHI_SH3 …) named by the page but left undefined: no official numeric source |
| `GetSystemInfo` | `ms885638` | CE 1.0+ | Winbase.h | Coredll.lib | VOID; fills SYSTEM_INFO; CeGetSystemInfo = RAPI form |
| `OSVERSIONINFO`/`LPOSVERSIONINFO` struct | `ms886768` | CE 1.0+ | Winbase.h | — | 5 DWORDs + `TCHAR szCSDVersion[128]` (TCHAR = WCHAR on CE) = 276 bytes; page typedefs OSVERSIONINFO, LP form implied by GetVersionEx signature |
| `VER_PLATFORM_WIN32s` / `VER_PLATFORM_WIN32_WINDOWS` / `VER_PLATFORM_WIN32_NT` / `VER_PLATFORM_WIN32_CE` | names per `ms886768`; numeric values fixed Win32 ABI (0/1/2/3) | — | Winbase.h | — | CE fills VER_PLATFORM_WIN32_CE (ms885648 remarks) |
| `GetVersionEx` | `ms885648` | CE 1.0+ | Winbase.h | Coredll.lib | caller sets dwOSVersionInfoSize; failure ⇒ GetLastError; feature-detect rather than version-test (page remarks) |
| `SignalStarted` | `aa450898` | CE 2.10+ | Winbase.h | Coredll.lib | boot (HKCU/Init) applications must call it after init; dw from the command line |

*Deferred from this book:* `QueryInstructionSet` `ms886787`
(CE .NET 4.0+, Coredll.lib — PROCESSOR_*_INSTRUCTION flags have no
published numeric values), `IsProcessorFeaturePresent` `ms886726`
(page row says Link Library **Coredll.dll**; PF_ARM_* values not
published), `VerQueryValue` `aa450973` + version structures
(VS_FIXEDFILEINFO etc. — version-resource batch).  These are recorded
here, not invented.

### M12: virtual memory, time zone, version/timing helpers (winbase.h + winnt.h)

All pages official `(v=msdn.10)` CE 5.0 (Time Reference /
Memory Management Reference / Process and Thread Reference /
System Management Reference books; already in `build/rows.json`).

| Item | Official page | OS Versions | Header | Link Library (page row) | Notes |
|---|---|---|---|---|---|
| `VirtualAlloc` | `aa450975` | CE 1.0+ | Winbase.h | Coredll.lib | MEM_RESET "not supported", MEM_TOP_DOWN ignored on CE (page); dwSize 0 invalid |
| `VirtualFree` | `aa450979` | CE 1.0+ | Winbase.h | Coredll.lib | MEM_RELEASE requires dwSize 0 and the VirtualAlloc base address |
| `VirtualProtect` | `aa450980` | CE 1.0+ | Winbase.h | Coredll.lib | pages must belong to one VirtualAlloc region; `PDWORD` out for old protection |
| `VirtualQuery` | `aa450981` | CE 1.0+ | Winbase.h | Coredll.lib | fills MEMORY_BASIC_INFORMATION; returns bytes written |
| `MEMORY_BASIC_INFORMATION`/`PMEMORY_BASIC_INFORMATION` | `ms886752` | CE 1.0+ | **Winnt.h** (page) | — | 2 pointers + 6 DWORDs (28 bytes on 32-bit CE); State = MEM_COMMIT/FREE/RESERVE, Type = MEM_IMAGE/MAPPED/PRIVATE |
| `MEM_COMMIT/RESERVE/DECOMMIT/RELEASE/FREE/PRIVATE/MAPPED/IMAGE/RESET/TOP_DOWN`, `PAGE_NOACCESS/READONLY/READWRITE/WRITECOPY/EXECUTE/EXECUTE_READ/EXECUTE_READWRITE/EXECUTE_WRITECOPY/GUARD/NOCACHE` | names per `aa450975`/`aa450980`/`ms886752`; numeric values fixed Win32 ABI | — | Winbase.h | — | MEM_RESET/MEM_TOP_DOWN retained for source compatibility with CE notes (see header) |
| `FlushInstructionCache` | `ms885595` | CE 2.0+ | Winbase.h | Coredll.lib | |
| `GetProcessVersion` | `ms885636` | CE 3.0+ | Winbase.h | Coredll.lib | high word major / low word minor; 0 + GetLastError on failure |
| `GetDllVersion` | `ms885617` | CE 5.0+ | Winbase.h | Coredll.lib | version of the system the DLL expects to run on |
| `GetThreadTimes` | `ms885644` | CE 2.10+ | Winbase.h | Coredll.lib | creation/exit/kernel/user FILETIMEs |
| `TIME_ZONE_INFORMATION`/`PTIME_ZONE_INFORMATION`/`LPTIME_ZONE_INFORMATION` | `aa450943` | CE 1.0+ | Winbase.h | — | Bias + WCHAR name[32] + SYSTEMTIME transition + Bias triplets; 172 bytes on CE |
| `GetTimeZoneInformation` | `ms885646` | CE 1.0+ | Winbase.h | Coredll.lib | returns TIME_ZONE_ID_*; failure also reports TIME_ZONE_ID_UNKNOWN (page) — no TIME_ZONE_ID_INVALID on CE |
| `SetTimeZoneInformation` | `aa450893` | CE 1.0+ | Winbase.h | Coredll.lib | not persisted to registry; RegFlushKey(HKEY_LOCAL_MACHINE) persists |
| `TIME_ZONE_ID_UNKNOWN/STANDARD/DAYLIGHT` | names per `ms885646`; values fixed Win32 ABI (0/1/2) | — | Winbase.h | — | |
| `PDWORD` (windef.h) | used by VirtualProtect page signature `aa450980` | — | Windef.h | — | DWORD pointer typedef |

### M13: code-page / NLS batch (new header `winnls.h`)

*Unicode Reference* book pages; official `(v=msdn.10)` CE 5.0 pages.
`winnls.h` is the Header row those pages name (Winnls.h).

| Item | Official page | OS Versions | Header | Link Library (page row) | Notes |
|---|---|---|---|---|---|
| `CP_ACP`/`CP_OEMCP`/`CP_MACCP`/`CP_THREAD_ACP`/`CP_SYMBOL`/`CP_UTF7`/`CP_UTF8` | names per `ms886760`/`aa450989`; values fixed Win32 ABI | — | Winnls.h | — | CP_MACCP/CP_SYMBOL/CP_THREAD_ACP marked "Not supported" by the CE pages; kept as constants with the note |
| `MB_PRECOMPOSED`/`MB_COMPOSITE`/`MB_USEGLYPHCHARS`/`MB_ERR_INVALID_CHARS` | names per `ms886760`; values fixed Win32 ABI | — | Winnls.h | — | |
| `WC_COMPOSITECHECK`/`WC_DISCARDNS`/`WC_SEPCHARS`/`WC_DEFAULTCHAR` | names per `aa450989`; values fixed Win32 ABI | — | Winnls.h | — | WC_NO_BEST_FIT_CHARS not published by the CE page → undefined |
| `MultiByteToWideChar` | `ms886760` | CE 1.01+ | Winnls.h | Coredll.lib | maps (not necessarily multibyte) string to wide |
| `WideCharToMultiByte` | `aa450989` | CE 1.01+ | Winnls.h | Coredll.lib | |
| `IsDBCSLeadByte` | `ms886515` | CE 1.01+ | Winnls.h | Coredll.lib | BYTE arg |
| `IsDBCSLeadByteEx` | `ms886608` | CE 1.01+ | Winnls.h | Coredll.lib | |
| `BYTE`, `LPBOOL` (windef.h) | used by NLS signatures (`ms886515`, `aa450989`) | — | Windef.h | — | windef base types |

### M14: Fiber Reference batch (winbase.h)

*Fiber Reference* book; official `(v=msdn.10)` CE 5.0 pages.  All
functions are CE .NET 4.0 and later with Link Library Coredll.lib.

| Item | Official page | OS Versions | Header | Link Library (page row) | Notes |
|---|---|---|---|---|---|
| `CreateFiber` | `ms885178` | CE .NET 4.0+ | Winbase.h | Coredll.lib | dwStackSize 0 = default stack; does not schedule the fiber |
| `ConvertThreadToFiber` | `ms885176` | CE .NET 4.0+ | Winbase.h | Coredll.lib | converts calling thread into a fiber |
| `DeleteFiber` | `ms885197` | CE .NET 4.0+ | Winbase.h | Coredll.lib | |
| `GetCurrentFiber` | `ms885611` | CE .NET 4.0+ | Winbase.h | Coredll.lib | address of current fiber |
| `GetFiberData` | `ms885624` | CE .NET 4.0+ | Winbase.h | Coredll.lib | data pointer of current fiber |
| `SwitchToFiber` | `aa450915` | CE .NET 4.0+ | Winbase.h | Coredll.lib | schedules the fiber |
| `PFIBER_START_ROUTINE`/`LPFIBER_START_ROUTINE` | `ms885221` (FiberProc) | CE .NET 4.0+ | Windows.h (page) | — | callback type; FiberProc is the developer's own function name (placeholder), so no export and no macro |

### M15: Registry Reference batch (new header `winreg.h`)

Official `(v=msdn.10)` CE 5.0 pages of *File Systems and Data Store →
Registry Reference*; Header row Winreg.h and Link Library Coredll.lib
on every page.  The registry is Unicode-only on CE: exports are the W
spellings (base names provided as macros); CeFind* change-notification
functions are plain names.

| Item | Official page | OS Versions | Header | Link Library (page row) | Notes |
|---|---|---|---|---|---|
| `HKEY`/`PHKEY`/`REGSAM` | registry pages (HKEY used by every signature) | — | Winreg.h | — | HKEY opaque key handle; REGSAM requested-access type (ignored on CE; pass 0) |
| `HKEY_CLASSES_ROOT`/`HKEY_CURRENT_USER`/`HKEY_LOCAL_MACHINE`/`HKEY_USERS` | names per `ms891450`+; values fixed Win32 predefined-handle ABI | — | Winreg.h | — | CE does not support HKEY_CURRENT_CONFIG/PERFORMANCE_DATA/DYN_DATA (not defined) |
| `REG_*` value types | `ms891462`/`ms891469` (REG_NONE/SZ/EXPAND_SZ/BINARY/DWORD/LITTLE/BIG_ENDIAN/LINK/MULTI_SZ/RESOURCE_LIST) | — | Winreg.h | — | values fixed Win32 ABI |
| `REG_OPTION_NON_VOLATILE`/`REG_OPTION_VOLATILE`, `REG_CREATED_NEW_KEY`/`REG_OPENED_EXISTING_KEY` | `ms891450` | — | Winreg.h | — | values fixed Win32 ABI |
| `REG_NOTIFY_CHANGE_NAME`/`REG_NOTIFY_CHANGE_LAST_SET` | `aa517116` | — | Winreg.h | — | only these two documented for CE |
| `RegCloseKey` | `ms891448` | CE 1.0+ | Winreg.h | Coredll.lib | |
| `RegCreateKeyEx(W)` | `ms891450` | CE 1.0+ | Winreg.h | Coredll.lib | key names ≤ 255 chars, 16 subkey levels; samDesired ignored (0); lpSecurityAttributes NULL; disposition reported |
| `RegDeleteKey(W)` | `ms891451` | CE 1.0+ | Winreg.h | Coredll.lib | deletes a subkey recursively |
| `RegDeleteValue(W)` | `ms891452` | CE 1.0+ | Winreg.h | Coredll.lib | |
| `RegEnumKeyEx(W)` | `ms891453` | CE 1.0+ | Winreg.h | Coredll.lib | index from 0 to ERROR_NO_MORE_ITEMS; ERROR_MORE_DATA on short buffer |
| `RegEnumValue(W)` | `ms891454` | CE 1.0+ | Winreg.h | Coredll.lib | index enumeration as RegEnumKeyEx |
| `RegFlushKey(W)` | `ms891455` | CE 2.10+ | Winreg.h | Coredll.lib | CE: no lazy flush by default; flush groups of changes |
| `RegOpenKeyEx(W)` | `ms891460` | CE 1.0+ | Winreg.h | Coredll.lib | ulOptions reserved; samDesired ignored |
| `RegQueryInfoKey(W)` | `ms891461` | CE 1.0+ | Winreg.h | Coredll.lib | counts + longest-name sizes |
| `RegQueryValueEx(W)` | `ms891462` | CE 1.0+ | Winreg.h | Coredll.lib | NULL lpData + size ⇒ required size; ERROR_MORE_DATA |
| `RegSetValueEx(W)` | `ms891469` | CE 1.0+ | Winreg.h | Coredll.lib | cbData includes terminator for string types; CE data cap 4 KB; value names ≤ 255 |
| `CeFindFirstRegChange` | `aa517116` | CE 5.0+ | Winreg.h | Coredll.lib | HANDLE; INVALID_HANDLE_VALUE failure; NAME/LAST_SET filters |
| `CeFindNextRegChange` | `aa517123` | CE 5.0+ | Winreg.h | Coredll.lib | re-arms the notification |
| `CeFindCloseRegChange` | `aa517103` | CE 5.0+ | Winreg.h | Coredll.lib | stops monitoring |
| `LPBYTE` (windef.h) | registry value-data pointer (`ms891454`/`ms891462`/`ms891469`) | — | Windef.h | — | windef base type |

### M16: NLS Reference batch, part 1 (winnls.h + winnt.h + windef.h)

Official `(v=msdn.10)` CE 5.0 pages of *International → National
Language Support (NLS) Reference*.  Winnls.h is the pages' Header row;
Link Library is Coreloc.lib except where a page row says Coredll.lib.

| Item | Official page | OS Versions | Header | Link Library (page row) | Notes |
|---|---|---|---|---|---|
| `LANGID`/`LCID` (windef.h) | NLS pages use both (`ms905289`/`ms905298`) | — | Windef.h | — | WORD/DWORD aliases |
| `PRIMARYLANGID`/`SUBLANGID` macros | `ms906230`/`ms906441` (formulas printed verbatim on the pages) | — | Winnt.h | — | primary = lgid & 0x3ff; sub = lgid >> 10 |
| `MAKELANGID`/`MAKELCID` macros | `ms906225`/`ms906226` | — | Winnt.h | — | documented inverses; sort id in high 16 bits of LCID |
| `GetACP` | `ms905215` | CE .NET 4.0+ | Winnls.h | Coreloc.lib | UINT; current ANSI code page |
| `GetOEMCP` | `ms905256` | CE .NET 4.0+ | Winnls.h | Coreloc.lib | |
| `GetSystemDefaultLCID` | `ms905298` | CE .NET 4.0+ | Winnls.h | Coreloc.lib | |
| `GetUserDefaultLCID` | `ms905323` | CE .NET 4.0+ | Winnls.h | Coreloc.lib | |
| `GetSystemDefaultLangID` | `ms905289` | CE .NET 4.0+ | Winnls.h | Coreloc.lib | |
| `GetUserDefaultLangID` | `ms905315` | CE .NET 4.0+ | Winnls.h | Coreloc.lib | |
| `IsValidCodePage` | `ms906218` | CE .NET 4.0+ | Winnls.h | Coreloc.lib | |
| `IsValidLocale` | `ms906219` | CE .NET 4.0+ | Winnls.h | Coreloc.lib | LCID_INSTALLED/SUPPORTED; no code-page download on CE |
| `CompareString(W)` | `ms904713` | CE 1.0+ | Winnls.h | Coreloc.lib | CSTR_LESS_THAN/EQUAL/GREATER_THAN; −1 counts = null-terminated |
| `ConvertDefaultLocale` | `ms904716` | CE .NET 4.0+ | Winnls.h | Coreloc.lib | |
| `GetCPInfo` + `CPINFO` | `ms905221`/`ms904717` | CE .NET 4.0+ | Winnls.h | Coreloc.lib | MAX_DEFAULTCHAR 2 / MAX_LEADBYTES 12 (fixed Win32 NLS sizes) |
| `GetStringTypeW` | `ms905272` | CE 1.0+ | Winnls.h | **Coredll.lib** | CT_CTYPE1/2/3 (1/2/4) |
| `GetStringTypeEx(W)` | `ms905283` | CE 1.0+ | Winnls.h | Coreloc.lib | |
| `LPWORD` (windef.h) | GetStringType* arrays | — | Windef.h | — | WORD pointer |

*Deferred from this book:* GetLocaleInfo/SetLocaleInfo (needs the
LOCALE_* LCTYPE constant set), Enum*/format functions (GetDateFormat,
GetTimeFormat, GetCurrencyFormat, GetNumberFormat + ENUMPROC types),
LCMapString/FoldString (LCMAP_*/MAPFOLD_* flag set).  Recorded here,
implemented only once their official pages are processed.

### M17: File I/O Reference continuation (winbase.h)

Official `(v=msdn.10)` CE 5.0 pages of *File Systems and Data Store →
File I/O Reference*; Winbase.h / Coredll.lib rows throughout.
Wide-string functions use the W spellings (CE Unicode-only), macro
base names provided; handle-only functions are plain.

| Item | Official page | OS Versions | Header | Link Library (page row) | Notes |
|---|---|---|---|---|---|
| `FindFirstChangeNotification(W)` | `ms889670` | CE .NET 4.0+ | Winbase.h | Coredll.lib | directory change notification handle |
| `FindNextChangeNotification` | `ms889784` | CE .NET 4.0+ | Winbase.h | Coredll.lib | |
| `FindCloseChangeNotification` | `ms889625` | CE .NET 4.0+ | Winbase.h | Coredll.lib | |
| `FILE_NOTIFY_CHANGE_FILE_NAME/_DIR_NAME/_SIZE/_LAST_WRITE` | `ms889670` | — | Winbase.h | — | only these 4 documented for CE; values fixed Win32 ABI |
| `FINDEX_INFO_LEVELS` enum | `ms889654` | CE 3.0+ | Winbase.h | — | {FindExInfoStandard, FindExInfoMaxInfoLevel} (C enum printed on page) |
| `FINDEX_SEARCH_OPS` enum | `ms889664` | CE 3.0+ | Winbase.h | — | {NameMatch, LimitToDirectories, LimitToDevices}; CE notes on filters |
| `GET_FILEEX_INFO_LEVELS` enum | `ms890917` | CE 3.0+ | Winbase.h | — | {GetFileExInfoStandard} |
| `FindFirstFileEx(W)` | `ms889683` | CE 3.0+ | Winbase.h | Coredll.lib | INVALID_HANDLE_VALUE on failure |
| `GetFileAttributesEx(W)` | `ms890909` | CE 3.0+ | Winbase.h | Coredll.lib | level GetFileExInfoStandard ⇒ WIN32_FILE_ATTRIBUTE_DATA |
| `WIN32_FILE_ATTRIBUTE_DATA` | `ms892377` | CE 3.0+ | Winbase.h | — | attr + 3 FILETIME + size (36 bytes) |
| `GetDiskFreeSpaceEx(W)` | `ms890887` | CE 2.0+ | Winbase.h | Coredll.lib | three ULARGE_INTEGER outs; each may be NULL |
| `GetFileInformationByHandle` | `ms890926` | CE 1.0+ | Winbase.h | Coredll.lib | |
| `BY_HANDLE_FILE_INFORMATION` | `aa516973` | CE 1.0+ | Winbase.h | — | 10 shared members + CE-only trailing `dwOID` (56 bytes) |
| `GetTempPath(W)` | `ms891189` | CE 2.11+ | Winbase.h | Coredll.lib | temp directory path |
| `GetTempFileName(W)` | `ms891186` | CE 3.0+ | Winbase.h | Coredll.lib | temp files not auto-deleted on power-down (CE note) |
| `LockFileEx` | `ms891385` | CE 5.0+ | Winbase.h | Coredll.lib | offset via LPOVERLAPPED; LOCKFILE_EXCLUSIVE_LOCK/FAIL_IMMEDIATELY named |
| `UnlockFileEx` | `ms892364` | CE 5.0+ | Winbase.h | Coredll.lib | |
| `DeleteAndRenameFile(W)` | `ms887981` | CE 1.01+ | Winbase.h | Coredll.lib | CE-only copy-over + delete (rename helper) |
| `GetFileVersionInfoSize(W)`/`GetFileVersionInfo(W)` | `ms890963`/`ms890951` | CE 3.0+ | Winbase.h | Coredll.lib | buffer-size query + version-info copy (truncation note) |
| `PLARGE_INTEGER`/`PULARGE_INTEGER` (winnt.h) | `ms890887` | — | Winnt.h | — | ULARGE_INTEGER pointer forms |

*Deferred:* CopyFileEx `aa517311` (CE 5.0+, needs the progress-callback
type + LPPROGRESS_ROUTINE processing), GetStoreInformation `ms891023`
(needs the STORE_INFORMATION record), the Ce* RAPI forms
(CeGenRandom/CeGetCanonicalPathName/CeGetFileNotificationInfo),
FindFirstFileEx's FILE_NOTIFY_INFORMATION-related pairs.

### M18: ToolHelp Reference batch (new header `tlhelp32.h`)

Official `(v=msdn.10)` CE 5.0 pages of *Core OS Reference → ToolHelp
Reference*; every function page's Header row is Tlhelp32.h (the two
Heap32 pages print "Tlhelp.h") and Link Library row is Toolhelp.lib
(not Coredll.lib -- these names correctly stay out of the coredll
def).

| Item | Official page | OS Versions | Header | Link Library (page row) | Notes |
|---|---|---|---|---|---|
| `TH32CS_SNAPHEAPLIST/PROCESS/THREAD/MODULE/ALL/SNAPNOHEAPS/GETALLMODS` | names per `ms885189`; values fixed Win32 ABI | — | Tlhelp32.h | — | |
| `PROCESSENTRY32` | `ms886774` | CE 1.0+ | Tlhelp32.h | — | CE-only trailing th32MemoryBase/th32AccessKey; szExeFile[MAX_PATH]; 564 B on 32-bit CE |
| `THREADENTRY32` | `aa450938` | CE 1.0+ | Tlhelp32.h | — | CE-only trailing th32AccessKey/th32CurrentProcessID; 36 B |
| `MODULEENTRY32` | `ms886756` | CE 1.0+ | Tlhelp32.h | — | modBaseAddr is BYTE*; two MAX_PATH names; 1076 B on 32-bit CE |
| `HEAPLIST32` | `ms885660` | CE 1.0+ | Tlhelp32.h | — | 16 B |
| `HEAPENTRY32` | `ms885658` | CE 1.0+ | Tlhelp32.h | — | hHandle member; 36 B on 32-bit CE |
| `CreateToolhelp32Snapshot` | `ms885189` | CE 2.0+ | Tlhelp32.h | Toolhelp.lib | snapshot of processes/threads/modules/heaps |
| `CloseToolhelp32Snapshot` | `ms885169` | CE 2.0+ | Tlhelp32.h | Toolhelp.lib | |
| `Process32First`/`Process32Next` | `ms886772`/`ms886773` | CE 2.0+ | Tlhelp32.h | Toolhelp.lib | dwSize=sizeof first |
| `Thread32First`/`Thread32Next` | `aa450934`/`aa450936` | CE 2.0+ | Tlhelp32.h | Toolhelp.lib | |
| `Module32First`/`Module32Next` | `ms886754`/`ms886755` | CE 2.0+ | Tlhelp32.h | Toolhelp.lib | |
| `Heap32ListFirst`/`Heap32ListNext` | `ms885651`/`ms885652` | CE 2.0+ | Tlhelp32.h | Toolhelp.lib | |
| `Heap32First`/`Heap32Next` | `ms885650`/`ms885653` | CE 2.0+ | Tlhelp32.h | Toolhelp.lib | |
| `Toolhelp32ReadProcessMemory` | `aa450953` | CE 2.0+ | Tlhelp32.h | Toolhelp.lib | ids castable to handles; SetProcPermissions for other processes |

### M19: Strings Reference batch (winbase.h) + multi-lib defs

Official `(v=msdn.10)` CE 5.0 pages of *Core OS Reference → Strings
Reference*.  Every page's Header row is Winbase.h.  All pages except
CharNext state "Windows CE supports only the Unicode version of this
function"; the W spellings below are therefore the documented exports
(base names provided as macros).  CharNext/CharPrev print no A/W
suffix; the W spelling follows the CE Unicode-only convention
(recorded as an inference in the header comment).

| Item | Official page | OS Versions | Header | Link Library (page row) | Notes |
|---|---|---|---|---|---|
| `CharLower(W)` | `ms885159` | CE 1.0+ | Winbase.h | Coreloc.lib | Unicode-only per page |
| `CharLowerBuff(W)` | `ms885160` | CE 1.0+ | Winbase.h | Coreloc.lib | |
| `CharUpper(W)` | `ms885164` | CE 1.0+ | Winbase.h | Coreloc.lib | |
| `CharUpperBuff(W)` | `ms885165` | CE 1.0+ | Winbase.h | Coreloc.lib | |
| `CharNext(W)` | `ms885161` | CE 1.0+ | Winbase.h | Coredll.lib | page prints base name only; W inferred |
| `CharPrev(W)` | `ms885162` | CE 1.01+ | Winbase.h | Coreloc.lib | |
| `IsCharAlpha(W)` | `ms885690` | CE 1.0+ | Winbase.h | Coreloc.lib | |
| `IsCharAlphaNumeric(W)` | `ms885691` | CE 1.0+ | Winbase.h | Coreloc.lib | |
| `IsCharLower(W)` | `ms885692` | CE 1.0+ | Winbase.h | Coreloc.lib | |
| `IsCharUpper(W)` | `ms885693` | CE 1.0+ | Winbase.h | Coreloc.lib | |
| `LoadString(W)` | `ms886738` | CE 1.0+ | Winbase.h | Loadstr.lib | NULL buffer ⇒ read-only resource pointer; not null-terminated by default; W inferred from CE Unicode resources |
| `wsprintf(W)` | `aa450993` | CE 1.0+ | Winbase.h | Coreloc.lib | Unicode-only per page; ≤1024 chars (page note); no length parameter |
| `wvsprintf(W)` | `aa450994` | CE 1.0+ | Winbase.h | Coreloc.lib | Unicode-only per page; va_list argument |

**Def generation is now multi-library.**  `tools/gen-doc-def.py` emits
one `def/*-doc.def` per documented user-mode Link Library token:
`coredll-doc.def` (148), `coreloc-doc.def` (23), `toolhelp-doc.def`
(13), `lmem-doc.def` (1), `loadstr-doc.def` (1).  Nk.lib/Coremain.lib
rows stay excluded (kernel-scope conflict model).  Auxiliary defs note
that only the import-library token is documented (module names are not
published); all are name-only and build with `llvm-dlltool -m armce`.

### M20/M20b: File Mapping Reference + DLL entry batch

Official `(v=msdn.10)` CE 5.0 pages.  All Header rows Winbase.h (or
Psapi.h where noted), all Link Library rows Coredll.lib.

| Item | Official page | OS Versions | Header | Link Library (page row) | Notes |
|---|---|---|---|---|---|
| `CreateFileForMapping(W)` | `aa517321` | CE 1.01+ | Winbase.h | Coredll.lib | CE-specific CreateFile-for-mapping; empty string is a named object (CE note); W per Unicode convention (base printed) |
| `CreateFileMapping(W)` | `aa517331` | CE 1.01+ | Winbase.h | Coredll.lib | INVALID_HANDLE_VALUE ⇒ physical-memory-backed object outside the 32 MB process space; attrs NULL; PAGE_READONLY/READWRITE/WRITECOPY; SEC_COMMIT/IMAGE/NOCACHE/RESERVE named, values unpublished → undefined |
| `MapViewOfFile` | `ms891386` | CE 1.01+ | Winbase.h | Coredll.lib | FILE_MAP_WRITE/READ/ALL_ACCESS (ALL_ACCESS = WRITE per page) |
| `UnmapViewOfFile` | `ms892373` | CE 1.01+ | Winbase.h | Coredll.lib | file stays open while views are mapped |
| `FlushViewOfFile` | `ms890303` | CE 1.01+ | Winbase.h | Coredll.lib | byte count cannot be 0; FILE_FLAG_WRITE_THROUGH for physical-write wait |
| `DisableThreadLibraryCalls` | `ms885200` | CE 3.0+ | Winbase.h | Coredll.lib | disables DLL_THREAD_* notifications; CE has no static TLS |
| `DLL_PROCESS_ATTACH/DETACH`/`DLL_THREAD_ATTACH/DETACH` | names per `ms885202` (DllMain); values fixed Win32 ABI | — | Winbase.h | — | DllMain itself is developer-defined (BOOL WINAPI DllMain(HANDLE,DWORD,LPVOID)); hinstDLL = HMODULE = base address |
| `MODULEINFO`/`LPMODULEINFO` struct | `ms886757` | CE .NET 4.1+ | Psapi.h | — | load address = HMODULE; SizeOfImage/EntryPoint from the PE header |
| `GetModuleInformation` | `ms885631` | CE .NET 4.1+ | Psapi.h | Coredll.lib | new header `include/psapi.h` |

New manifest `tools/manifests/file-mapping-reference.manifest` (6
pages); coredll def 148 -> 154 exports.

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

The M8/M9 spellings follow the same documented rule (Windows CE is
Unicode-only ⇒ the base names map to the W exports, plain names for
the handle-based I/O functions).  Export defs are no longer produced
from a device/audit surface: `def/coredll-doc.def` is generated from
the harvested official pages (`tools/gen-doc-def.py` over
`build/rows.json`); see the def section above and README.

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
