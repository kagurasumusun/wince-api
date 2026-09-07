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

### M21: store info + Ce* file helpers + FILE_NOTIFY (winbase.h/winnt.h)

| Item | Official page | OS Versions | Header | Link Library (page row) | Notes |
|---|---|---|---|---|---|
| `STORE_INFORMATION`/`LPSTORE_INFORMATION` | `ms891279` | CE 1.0+ | Winbase.h | — | dwStoreSize/dwFreeSize (object store) |
| `GetStoreInformation` | `ms891023` | CE 1.0+ | Winbase.h | Coredll.lib | page deprecates (use GetDiskFreeSpaceEx); reports 44 KB less than available |
| `CeGenRandom` | `aa517140` | CE .NET 4.1+ | Winbase.h | Coredll.lib | fills a buffer with random bytes; optional seed |
| `CeGetCanonicalPathName` | `aa517144` | CE 5.0+ | Winbase.h | Coredll.lib | canonical-path length / string; ERROR_INSUFFICIENT_BUFFER rule |
| `CeGetFileNotificationInfo` | `aa517158` | CE .NET 4.2+ | Winbase.h | Coredll.lib | returns FILE_NOTIFY_INFORMATION record(s); ERROR_MORE_DATA / ERROR_INSUFFICIENT_BUFFER semantics |
| `FILE_NOTIFY_INFORMATION`/`PFILE_NOTIFY_INFORMATION` | `ms889597` | CE 1.01+ | **Winnt.h** | — | variable-length FileName[1] record |
| `FILE_ACTION_ADDED/REMOVED/MODIFIED/RENAMED_OLD_NAME/RENAMED_NEW_NAME` | names per `ms889597`; values fixed Win32 ABI | — | Winnt.h | — | |

coredll def 154 -> 158 exports.

### M22: Message Queue Point-to-Point Reference (new header `msgqueue.h`)

All pages `ms885168/ms885180/ms885632/ms886765/ms886793/aa450991/ms886758/ms886759`
were fetched in full from the (v=msdn.10) CE 5.0 archive.  Every
function page states **Header: Msgqueue.h** and **Link Library:
Coredll.lib**; OS Versions is **Windows CE .NET 4.0 and later** for
every item (the APIs were introduced with CE .NET; they remain
documented in the CE 6.0 / later archives under twin page IDs, e.g.
CloseMsgQueue `ee488787(v=winembedded.60)`).

| Item | Official page | OS Versions | Header | Link Library | Notes |
|---|---|---|---|---|---|
| `CloseMsgQueue` | `ms885168` | CE .NET 4.0+ | Msgqueue.h | Coredll.lib | closes a queue handle |
| `CreateMsgQueue` | `ms885180` | CE .NET 4.0+ | Msgqueue.h | Coredll.lib | LPCWSTR name (NULL=unnamed, max MAX_PATH); read *or* write access; ERROR_ALREADY_EXISTS if present; handles signalable |
| `GetMsgQueueInfo` | `ms885632` | CE .NET 4.0+ | Msgqueue.h | Coredll.lib | fills MSGQUEUEINFO |
| `OpenMsgQueue` | `ms886765` | CE .NET 4.0+ | Msgqueue.h | Coredll.lib | source-process handle + queue handle; checks dwSize/bReadAccess only |
| `ReadMsgQueue` | `ms886793` | CE .NET 4.0+ | Msgqueue.h | Coredll.lib | ERROR_INSUFFICIENT_BUFFER / ERROR_PIPE_NOT_CONNECTED / ERROR_TIMEOUT |
| `WriteMsgQueue` | `aa450991` | CE .NET 4.0+ | Msgqueue.h | Coredll.lib | dwFlags = MSGQUEUE_MSGALERT; ERROR_OUTOFMEMORY with MSGQUEUE_NOPRECOMMIT |
| `MSGQUEUEOPTIONS` + `PMSGQUEUEOPTIONS`/`LPMSGQUEUEOPTIONS` | `ms886759` | CE .NET 4.0+ | Msgqueue.h | — | dwSize/dwFlags/dwMaxMessages/cbMaxMessage/bReadAccess (32-bit layout: size 20) |
| `MSGQUEUEINFO` + `PMSGQUEUEINFO`/`LPMSGQUEUEINFO` | `ms886758` | CE .NET 4.0+ | Msgqueue.h | — | adds dwCurrentMessages/dwMaxQueueMessages/wNumReaders/wNumWriters (size 28) |

Flag names documented but **values unpublished on the CE pages** (recorded unknown, not defined): `MSGQUEUE_NOPRECOMMIT`, `MSGQUEUE_ALLOW_BROKEN`
(MSGQUEUEOPTIONS/MSGQUEUEINFO dwFlags) and `MSGQUEUE_MSGALERT`
(ReadMsgQueue pdwFlags / WriteMsgQueue dwFlags).  The page syntax lines
print the two struct typedefs without an internal tag ("typedef
MSGQUEUEINFO{…} MSGQUEUEINFO, …" / "typedef MSGQUEUEOPTIONS_OS{…} …"),
so the internal tags are treated as unpublished and none is invented.

coredll def 158 -> 164 exports; `windows.h` now includes `msgqueue.h`.

### M23: Serial Communications Reference (winbase.h)

All 16 function pages and 4 structure pages of the CE 5.0 archive
(`ms885166`–`ms885173`, `ms885192`, `ms885213`, `ms885606`–`ms885610`,
`ms886785`, `ms886804`–`ms886807`, `aa450896`, `aa450957`, `aa450985`)
were fetched in full.  Every function page states **Header: Winbase.h**
and **Link Library: Serdev.lib** (the serial device-driver module — NOT
Coredll.dll, so these exports live in a separate `def/serdev-doc.def`);
OS Versions is **Windows CE 1.0 and later** except EscapeCommFunction =
**CE 2.10 and later**.  Structures carry no Link Library row.

| Item | Official page | OS Versions | Header | Link Library |
|---|---|---|---|---|
| `ClearCommBreak` | `ms885166` | CE 1.0+ | Winbase.h | Serdev.lib |
| `ClearCommError` | `ms885167` | CE 1.0+ | Winbase.h | Serdev.lib |
| `EscapeCommFunction` | `ms885213` | CE 2.10+ | Winbase.h | Serdev.lib |
| `GetCommMask` | `ms885606` | CE 1.0+ | Winbase.h | Serdev.lib |
| `GetCommModemStatus` | `ms885607` | CE 1.0+ | Winbase.h | Serdev.lib |
| `GetCommProperties` | `ms885608` | CE 1.0+ | Winbase.h | Serdev.lib |
| `GetCommState` | `ms885609` | CE 1.0+ | Winbase.h | Serdev.lib |
| `GetCommTimeouts` | `ms885610` | CE 1.0+ | Winbase.h | Serdev.lib |
| `PurgeComm` | `ms886785` | CE 1.0+ | Winbase.h | Serdev.lib |
| `SetCommBreak` | `ms886804` | CE 1.0+ | Winbase.h | Serdev.lib |
| `SetCommMask` | `ms886805` | CE 1.0+ | Winbase.h | Serdev.lib |
| `SetCommState` | `ms886806` | CE 1.0+ | Winbase.h | Serdev.lib |
| `SetCommTimeouts` | `ms886807` | CE 1.0+ | Winbase.h | Serdev.lib |
| `SetupComm` | `aa450896` | CE 1.0+ | Winbase.h | Serdev.lib |
| `TransmitCommChar` | `aa450957` | CE 1.0+ | Winbase.h | Serdev.lib |
| `WaitCommEvent` | `aa450985` | CE 1.0+ | Winbase.h | Serdev.lib |
| `COMMTIMEOUTS`/`LPCOMMTIMEOUTS` | `ms885171` | CE 1.0+ | Winbase.h | — |
| `COMSTAT`/`LPCOMSTAT` | `ms885173` | CE 1.0+ | Winbase.h | — |
| `DCB`/`LPDCB` | `ms885192` | CE 1.0+ | Winbase.h | — |
| `COMMPROP` + `LPCOMMPROP` | `ms885170` | CE 1.0+ | Winbase.h | — |

Notes recorded verbatim from the pages: WaitCommEvent's `lpOverlapped`
is "Ignored; set to NULL" on CE; COMMTIMEOUTS semantics (MAXDWORD
interval + multiplier with a small constant) follow the page; DCB's
`fBinary` must be TRUE (the CE page: nonbinary mode is not supported);
COMMPROP's typedef is transcribed with its page-listed members
(including `WORD dwCurrentTxQueue` followed by `DWORD dwCurrentRxQueue`
as the page prints them) and the pointer alias `LPCOMMPROP` is supplied
because the function pages type the parameter `LPCOMMPROP`.  Named
serial constants (CBR_* / BAUD_* indexes, DTR/RTS control values,
PURGE_* actions, CLR/SET escape codes, EV_* masks, CE_* errors,
SP_SERIALCOMM) are described on the pages **without numeric values** →
recorded unknown, not defined.

New doc-derived def: `def/serdev-doc.def` (16 exports).  Host checks
(CE 0x420/0x500/0x600 + standalone headers) pass; the six-target WinCE
clang crosscheck for this batch is *pending* toolchain re-acquisition
(the LLVM-WinCE clang cache is deleted each session end by policy).

### M24: Exception Reference + Debugging Reference (excpt.h / dbgapi.h / errorrep.h / winnt.h / winbase.h)

All Exception pages (`aa450784`, `ms885620/621`, `ms886790`, `ms886799`,
`ms885215/216`) and the Debugging pages (`ms885175/183/187/193/194/195/
214/218/220`, `ms886734/769/770`, `aa450986/990`, `aa451060/081/083`,
plus the recorded macro pages `ms887725`, `aa451037`..`aa451087`) were
fetched in full from the CE 5.0 archive.

| Item | Official page | OS Versions | Header | Link Library | Placement |
|---|---|---|---|---|---|
| `EXCEPTION_RECORD`/`PEXCEPTION_RECORD` | `ms885216` | CE 1.0+ | Winnt.h | — | winnt.h |
| `EXCEPTION_POINTERS` (+P/LP) | `ms885215` | CE 1.0+ | Excpt.h | — | excpt.h |
| `AbnormalTermination` | `aa450784` | CE 1.0+ | Excpt.h | Coredll.lib(row; intrinsic) | excpt.h |
| `GetExceptionCode` | `ms885620` | CE 1.0+ | Excpt.h | Coredll.lib(row; intrinsic) | excpt.h |
| `GetExceptionInformation` | `ms885621` | CE 1.0+ | Excpt.h | Coredll.lib(row; intrinsic) | excpt.h |
| `RaiseException` | `ms886790` | CE 1.0+ | Winbase.h | Coredll.lib | winbase.h |
| `ReportFault`/`EFaultRepRetVal` | `ms886799` | CE 5.0+ | ErrorRep.h | Coredll.lib | errorrep.h |
| `CONTEXT` (opaque) | `ms885174` | CE 2.0+ | Winbase.h | — | winnt.h |
| `DebugBreak` | `ms885194` | CE 1.0+ | Kfuncs.h | Coredll.lib | winbase.h |
| `ContinueDebugEvent` | `ms885175` | CE 2.0+ | Winbase.h | Coredll.lib,Nk.lib | winbase.h |
| `DebugActiveProcess` | `ms885193` | CE 2.0+ | Winbase.h | Coredll.lib,Nk.lib | winbase.h |
| `WaitForDebugEvent` | `aa450986` | CE 2.0+ | Winbase.h | Coredll.lib,Nk.lib | winbase.h |
| `OutputDebugString(W)` | `ms886769` | CE 1.0+ | Winbase.h | Nk.lib (not Coredll) | winbase.h |
| `DEBUG_EVENT` | `ms885195` | CE 2.0+ | Winbase.h | — | winbase.h |
| `CREATE_PROCESS/THREAD_DEBUG_INFO`, `EXCEPTION/EXIT_*/LOAD_DLL/UNLOAD_DLL_DEBUG_INFO`, `OUTPUT_DEBUG_STRING_INFO` | `ms885183/187/214/218/220`, `ms886734/770`, `aa450963` | CE 2.0+ | Winbase.h | — | winbase.h |
| `DBGPARAM`/`LPDBGPARAM` | `aa451060` | CE OS 2.10+ | Dbgapi.h | — | dbgapi.h |
| `NKDbgPrintfW` | `aa451081` | CE OS 2.10+ | Dbgapi.h | none | dbgapi.h |
| `RegisterDbgZones` | `aa451083` | CE OS 2.10+ | Dbgapi.h | none | dbgapi.h |
| `WriteDebugLED` | `aa450990` | CE 2.12+ | Dbgapi.h | Coredll.lib | dbgapi.h |

Value/type provenance recorded in the headers and here:
* `EXCEPTION_MAXIMUM_PARAMETERS` = 15 (Win32 ABI bound used by
  EXCEPTION_RECORD layout and RaiseException).
* The 16 `EXCEPTION_*` *codes* are the names listed by `ms885620`;
  their hex values are the fixed Win32 ABI codes of the desktop
  exception reference.
* `EXCEPTION_CONTINUABLE` 0 / `EXCEPTION_NONCONTINUABLE` 1 flags
  (RaiseException `ms886790`).
* Debug-event codes 1..8 (`EXCEPTION_DEBUG_EVENT`..`OUTPUT_DEBUG_STRING_EVENT`,
  names per `ms885195`, values fixed Win32 ABI); the CE 5.0 page names
  no RIP_EVENT code row.
* `DBG_CONTINUE` 0x00010002 / `DBG_EXCEPTION_NOT_HANDLED` 0x80010001
  (names per `ms885175`, values fixed Win32 ABI).
* `RIP_INFO` (dwError/dwType) is referenced as a DEBUG_EVENT union
  member by `ms885195` but has no CE structure page; layout taken from
  Microsoft's official desktop debugging-structures reference.
* `CONTEXT` is only an incomplete type: `ms885174` says the per-CPU
  definitions live in the Winnt.h header file and publishes no layout.
* The Debugging Reference macro pages (ASSERT, ASSERTMSG, DEBUGCHK,
  DEBUGLED, DEBUGMSG, DEBUGREGISTER/RETAILREGISTERZONES, DEBUGZONE,
  ERRORMSG, RETAILLED, RETAILMSG — `aa451037`..`aa451087`, `ms887725`)
  are recorded; their expansions are driver/zone machinery the pages
  do not specify implementably, and they are not declared here.
* `ms886799` names two ReportFault returns (`frrvOk`, `frrvErrNoDW`)
  without numeric values → `EFaultRepRetVal` is a type alias and the
  `frrv*` constants are recorded unknown (not defined).  dwOpt is
  reserved, set to zero.
* `GetExceptionCode`/`GetExceptionInformation`/`AbnormalTermination`
  are callable only inside SEH constructs and are compiler intrinsics
  on CE; their pages' "Coredll.lib" rows are recorded but they are
  kept out of the export def (NOT_EXPORTS in gen-doc-def.py).

New headers: `excpt.h`, `dbgapi.h`, `errorrep.h` (windows.h now
includes excpt.h).  coredll def 164 -> 171 exports.  Host + six CE
targets pass (toolchain re-acquired and re-verified this session).

### M25: Error Values book + NAT Reference + CeLog functions (bulk)

**Error Values.**  winerror.h now carries the *complete* official
"System Errors - Numerical Order (Windows CE 5.0)" page (`aa450919`,
alphabetical twin `aa450917`): the earlier capture covered codes 0..1078
and M25 appends the remaining **427 rows** through code 6118 (zero
value conflicts with the prior 250 defines; NO_ERROR / STILL_ACTIVE
kept from other page provenance).  Also appended from the official CE
5.0 pages: **NTE error codes** `aa451033` (+30), **CRYPT error codes**
`aa451026` (+46), **CERTSRV error codes** `aa451023`, **TRUST error
codes** `aa451035` (hex values printed verbatim).  Recorded *unknown,
not defined*: **RAS error values** `ms886792` (page defines values only
as "RASBASE+n") and **NERR_** net errors `ms886761`/`ms886762` (the CE
page's NERR_ values conflict with the desktop Net Error Codes
reference, e.g. NERR_LastAdmin 242 vs 2219 — documented conflict; no
NERR constant emitted).  winerror.h: 251 -> 769 #defines.

`FormatMessageW` (`ms885599`, Header Winbase.h, **Link Library
Fmtmsg.lib** -> new `def/fmtmsg-doc.def`, 1 export; CE Unicode-only;
dwLanguageId unsupported; system message tables are a selectable OS
component) plus the FORMAT_MESSAGE_* flag names (fixed Win32-ABI
values) added to winbase.h.  GetLastError/SetLastError were already
implemented from these same book pages (ms885627/ms886817).

**Network Address Translation Reference** (new header `natedit.h`; all
pages Header **Natedit.h**, Link Library **Coredll.dll**, OS CE 3.0+
except the logging pages ms886745..748 = CE .NET 4.1+):
IP_NAT_DIRECTION enum (`ms885682`), IP_NAT_SESSION_MAPPING_STATISTICS
(`ms885684`, ULONG64 counters), IPRcvBuf (`ms885685`; page prints the
member types as lowercase tokens "uint"/"uchar" read as the fixed
UINT/UCHAR types used on the NAT pages), the driver entry points
EditorInitialize/RegisterEditor (`ms885210`/`ms886796`), the ticket/
session APIs CreateTicket, DeleteTicket, EditSession, QueryInfoSession,
TimeoutSession, DisassociateSession, EditorDeregister, and the
editor-implemented callback prototypes CreateHandler/DataHandler/
DeleteHandler.  The NAT logging typedefs PNAT_LOG_* (`ms886745..748`)
are declared.  Clean-room boundary: IP_NAT_REGISTER_EDITOR
(`ms885683`) is an *anonymous* typedef whose members consume
PNAT_EDITOR_* callback types that no CE page defines separately, so
the structure is provided as an **incomplete type** with the two
pointer spellings the pages use (PIP_NAT_REGISTER_EDITOR,
PNAT_REGISTER_EDITOR).  windef.h gained the fixed ABI typedefs UCHAR/
USHORT/ULONG64/BOOLEAN/PULONG/PUSHORT/PUCHAR/NTSTATUS used by these
pages.

**CeLog Event Tracking functions** (new header `celog.h`; all seven
function pages Header Celog.h, Link Library Coredll.lib):
CeLogData `aa450823` (CE 3.0+), CeLogGetZones `aa450824`,
CeLogInterrupt `aa451043`, CeLogMsg `aa450825`, CeLogQueryZones
`aa450826`, CeLogReSync `aa450827`, CeLogSetZones `aa450828`.  The
~60 CEL_* event-record pages (`CEL_EVENT_CREATE`, CEL_HEADER,
MAPHEADER, ...) plus the CeLog event-identifier / zone pages document
the payload format of the kernel event-log stream and carry no Header/
Link rows; they are **recorded, not transcribed** (no user-mode API).
NAT exports join coredll: coredll def 171 -> **192**.  Host + six CE
targets pass; all defs llvm-dlltool-armce verified.

### M26: GWES window-manager core (Windows / Class / Property / Timer / Caret / Atom / Message-Queue / Keyboard / Scroll books)

First user-interface batch.  Implemented from the CE 5.0 GWES
documentation in the learn.microsoft.com previous-versions archive
(`(v=msdn.10)`): **14 manifests** (`tools/manifests/gwes-*.manifest`,
156 unique leaf pages) were generated from the official CE 5.0 TOC and
fetched this session; `build/rows.json` grows 510 -> **666** rows.
New `include/winuser.h` (the CE user-interface header) plus additions
to `include/windef.h` (fixed Win32-ABI window/message types and
MAKELONG), `include/windows.h` (every M26 page whose Header row is
Windows.h: window properties, atoms, GetMessageQueueReadyTimeStamp,
SendMessageTimeout, ScrollDC) and `include/winbase.h` (KillTimer,
MsgWaitForMultipleObjects/Ex).  Export surface: coredll 192 -> **221**
exports, and the documented component-module Link rows become new def
files (accel, caret, foregnd, hotkey, kbdui, coreimm, msgque, sbcmn,
uibase, winmgr, wmgr_c): 7 -> **18** def files, every one
llvm-dlltool-`-m armce` verified.  gen-doc-def.py fixes this session:
the `.lib`-token regex keeps underscores (`wmgr_c.lib` had split into a
bogus `c.lib`) and the declared-name filter accepts underscore names
(`keybd_event`).

Leaf record per book (id / title / Header / Link Library as
published).  Declarations live in winuser.h unless a book note says
otherwise; header-home follows each page's Header row.


#### Windows Functions (35 leaves)

The Windows Functions book (35 leaves; every Header row is Winuser.h).
These pages carry OS-Versions rows but *no Link Library row at all*:
on CE the window manager is a GWES module service and the CE 5.0
documentation publishes no import-library token for it, so none of
these names enter any export def (recorded as documented "no link
library"; apps link these through the OS image, not through a
documented .lib).  EnumWindowsProc (aa453052), WindowProc (ms914102)
and WinMain (ms914104) are callback/entry prototypes.  Declared in
winuser.h (W exports + generic macros for the text/class-taking
forms, per the CE Unicode-only rule).

```
  aa452849  AdjustWindowRectEx   Header: Winuser.h.  no Link Library row
  aa452870  BeginDeferWindowPos   Header: Winuser.h.  no Link Library row
  aa452899  BringWindowToTop   Header: Winuser.h.  no Link Library row
  aa452919  CallWindowProc   Header: Winuser.h.  no Link Library row
  ms928578  ChildWindowFromPoint   Header: Winuser.h.  no Link Library row
  ms908192  CreateWindow   Header: Winuser.h.  no Link Library row
  ms908193  CreateWindowEx   Header: Winuser.h.  no Link Library row
  ms908210  DeferWindowPos   Header: Winuser.h.  no Link Library row
  aa452929  DefWindowProc   Header: Winuser.h.  no Link Library row
  aa452942  DestroyWindow   Header: Winuser.h.  no Link Library row
  aa453037  EndDeferWindowPos   Header: Winuser.h.  no Link Library row
  aa453051  EnumWindows   Header: Winuser.h.  no Link Library row
  aa453052  EnumWindowsProc   Header: Winuser.h.  no Link Library row
  aa453070  FindWindow   Header: Winuser.h.  no Link Library row
  ms929214  GetClientRect   Header: Winuser.h.  no Link Library row
  ms929229  GetDesktopWindow   Header: Winuser.h.  no Link Library row
  ms929244  GetForegroundWindow   Header: Winuser.h.  no Link Library row
  aa453152  GetParent   Header: Winuser.h.  no Link Library row
  aa453178  GetWindow   Header: Winuser.h.  no Link Library row
  aa453181  GetWindowRect   Header: Winuser.h.  no Link Library row
  aa453183  GetWindowText   Header: Winuser.h.  no Link Library row
  aa453184  GetWindowTextLength   Header: Winuser.h.  no Link Library row
  aa453185  GetWindowThreadProcessId   Header: Winuser.h.  no Link Library row
  ms909862  IsChild   Header: Winuser.h.  no Link Library row
  aa453233  IsWindow   Header: Winuser.h.  no Link Library row
  aa453235  IsWindowVisible   Header: Winuser.h.  no Link Library row
  ms931458  MoveWindow   Header: Winuser.h.  no Link Library row
  ms940024  SetForegroundWindow   Header: Winuser.h.  no Link Library row
  aa453645  SetParent   Header: Winuser.h.  no Link Library row
  aa453662  SetWindowPos   Header: Winuser.h.  no Link Library row
  aa453664  SetWindowText   Header: Winuser.h.  no Link Library row
  aa453731  ShowWindow   Header: Winuser.h.  no Link Library row
  ms914099  WindowFromPoint   Header: Winuser.h.  no Link Library row
  ms914102  WindowProc   Header: Winuser.h.  no Link Library row
  ms914104  WinMain   Header: Winuser.h.  no Link Library row
```

#### Window Class Functions (8)

Window Class Functions (8; Header Winuser.h, no Link Library rows --
same GWES-module model).  Declared in winuser.h.

```
  ms929211  GetClassInfo   Header: Winuser.h.  no Link Library row
  ms929212  GetClassLong   Header: Winuser.h.  no Link Library row
  ms929213  GetClassName   Header: Winuser.h.  no Link Library row
  aa453180  GetWindowLong   Header: Winuser.h.  no Link Library row
  ms913089  RegisterClass   Header: Winuser.h.  no Link Library row
  ms940014  SetClassLong   Header: Winuser.h.  no Link Library row
  aa453661  SetWindowLong   Header: Winuser.h.  no Link Library row
  ms914082  UnregisterClass   Header: Winuser.h.  no Link Library row
```

#### Window Properties Functions (5)

Window Properties Functions (5; OS rows "Windows CE .NET 4.0 and
later").  The pages' Header row is **Windows.h** (Link Library
Coredll.lib on the four API pages; PropEnumProcEx aa453551 is a
callback prototype with no link row), so the properties live in
windows.h and the enumeration-callback typedef PROPENUMPROCEX lives
in winuser.h.  Text-taking -> W exports (SetPropW/GetPropW/
RemovePropW/EnumPropsExW) in def/coredll-doc.def.

```
  aa453050  EnumPropsEx   Header: Windows.h.  Coredll.lib.
  aa453155  GetProp   Header: Windows.h.  Coredll.lib.
  aa453551  PropEnumProcEx   Header: Windows.h.  no Link Library row
  ms939781  RemoveProp   Header: Windows.h.  Coredll.lib.
  aa453647  SetProp   Header: Windows.h.  Coredll.lib.
```

#### Windows Timer Functions (4)

Windows Timer Functions (4).  SetTimer aa453657 (CE 2.0+) and
SystemIdleTimerReset ms940382 (CE 2.0+) print Header Winuser.h and no
link row -> winuser.h.  KillTimer aa453248 and TimerProc aa453746
print Header **Winbase.h** -> winbase.h (the timer-callback prototype
TimerProc is typedef'd TIMERPROC in winuser.h).

```
  aa453248  KillTimer   Header: Winbase.h.  no Link Library row
  aa453657  SetTimer   Header: Winuser.h.  no Link Library row
  ms940382  SystemIdleTimerReset   Header: Winuser.h.  no Link Library row
  aa453746  TimerProc   Header: Winbase.h.  no Link Library row
```

#### Carets Functions (8)

Carets Functions (8; CE 1.0+; Header Winuser.h; Link Library
**Caret.lib** -> def/caret-doc.def).  GetActiveWindow/SetActiveWindow/
GetFocus/SetFocus also carry Caret.lib (and Foregnd.lib) rows from the
Keyboard book, so caret-doc.def ends up with 12 exports and
foregnd-doc.def with 3.

```
  ms908164  CreateCaret   Header: Winuser.h.  Caret.lib.
  aa452936  DestroyCaret   Header: Winuser.h.  Caret.lib.
  ms929209  GetCaretBlinkTime   Header: Winuser.h.  Caret.lib.
  ms929210  GetCaretPos   Header: Winuser.h.  Caret.lib.
  ms929930  HideCaret   Header: Winuser.h.  Caret.lib.
  ms940012  SetCaretBlinkTime   Header: Winuser.h.  Caret.lib.
  ms940013  SetCaretPos   Header: Winuser.h.  Caret.lib.
  aa453729  ShowCaret   Header: Winuser.h.  Caret.lib.
```

#### Atoms Functions (3)

Atoms Functions (3; OS rows "Windows CE .NET 4.0 and later"; Header
**Windows.h**; Link Library Coredll.lib).  Declared in windows.h;
GlobalAddAtomW/GlobalFindAtomW (W) and GlobalDeleteAtom enter
def/coredll-doc.def.

```
  aa453188  GlobalAddAtom   Header: Windows.h.  Coredll.lib.
  aa453189  GlobalDeleteAtom   Header: Windows.h.  Coredll.lib.
  aa453190  GlobalFindAtom   Header: Windows.h.  Coredll.lib.
```

#### GWES Message Queue Functions (16)

GWES Message Queue Functions (16).  Header Winuser.h except
GetMessageQueueReadyTimeStamp aa453137 and SendMessageTimeout ms939981
(Header Windows.h -> windows.h).  Every page has a **Coredll.lib**
Link Library row: these sixteen are the M26 coredll export additions.
Text-free functions keep their documented base names (GetMessage,
PostMessage, SendMessage, DispatchMessage, TranslateMessage, ...);
RegisterWindowMessage is text-taking -> RegisterWindowMessageW.

```
  aa452956  DispatchMessage   Header: Winuser.h.  Coredll.lib.
  aa453135  GetMessage   Header: Winuser.h.  Coredll.lib.
  aa453136  GetMessagePos   Header: Winuser.h.  Coredll.lib.
  aa453137  GetMessageQueueReadyTimeStamp   Header: Windows.h.  Coredll.lib.
  aa453138  GetMessageSource   Header: Winuser.h.  Coredll.lib.
  aa453156  GetQueueStatus   Header: Winuser.h.  Coredll.lib.
  ms909852  InSendMessage   Header: Winuser.h.  Coredll.lib.
  ms911928  PeekMessage   Header: Winuser.h.  Coredll.lib.
  ms911937  PostMessage   Header: Winuser.h.  Coredll.lib.
  ms911938  PostQuitMessage   Header: Winuser.h.  Coredll.lib.
  ms911939  PostThreadMessage   Header: Winuser.h.  Coredll.lib.
  ms939737  RegisterWindowMessage   Header: Winuser.h.  Coredll.lib.
  ms939980  SendMessage   Header: Winuser.h.  Coredll.lib.
  ms939981  SendMessageTimeout   Header: Windows.h.  Coredll.lib.
  ms939983  SendNotifyMessage   Header: Winuser.h.  Coredll.lib.
  aa453776  TranslateMessage   Header: Winuser.h.  Coredll.lib.
```

#### Message Synchronization Functions (2)

Message Synchronization Functions (2): MsgWaitForMultipleObjects
ms931460 (CE 1.0+) / MsgWaitForMultipleObjectsEx ms931461 (CE 2.0+).
Header **Winbase.h** -> winbase.h; Link Library **Msgque.lib** ->
def/msgque-doc.def.

```
  ms931460  MsgWaitForMultipleObjects   Header: Winbase.h.  Msgque.lib.
  ms931461  MsgWaitForMultipleObjectsEx   Header: Winbase.h.  Msgque.lib.
```

#### Keyboard Functions (30)

Keyboard Functions (30).  Header Winuser.h except six OEM pages whose
Header row is Pwinuser.h.  Link Library rows are the CE 5.0 component
modules (Kbdui.lib, Caret.lib+Foregnd.lib, Wmgr_c.lib, Uibase.lib,
Accel.lib, Hotkey.lib, Coreimm.lib) plus Coredll.lib on the
keyboard-layout/type rows, producing the accel/caret/foregnd/kbdui/
wmgr_c/uibase/hotkey/coreimm def files (a documented export may appear
in several module defs, mirroring rows that print e.g. "Caret.lib,
Foregnd.lib").  Six leaves are **deferred to the OEM/input-method
batch** (recorded here so they are not lost): GetAsyncShiftFlags
aa453955, GetForegroundInfo ms929241, GetForegroundKeyboardLayoutHandle
ms929242, GetForegroundKeyboardTarget ms929243, KeybdGetDeviceInfo
aa453246 and PostKeybdMessage ms911936 -- their Header rows name
Pwinuser.h and their signatures need the OEM keybd types
GET_FOREGROUND_INFO (aa453186) and KEY_STATE_FLAGS (ms902150, Header
Keybd.h), whose flag values the CE documentation does not publish
numerically.

```
  aa452845  ActivateKeyboardLayout   Header: Winuser.h.  Coredll.lib.
  ms908162  CreateAcceleratorTable   Header: Winuser.h.  Accel.lib.
  aa452935  DestroyAcceleratorTable   Header: Winuser.h.  Accel.lib.
  aa453035  EnableWindow   Header: Winuser.h.  Wmgr_c.lib.
  ms929203  GetActiveWindow   Header: Winuser.h.  Caret.lib, Foregnd.lib.
  ms929204  GetAsyncKeyState   Header: Winuser.h.  Kbdui.lib.
  aa453955  GetAsyncShiftFlags   Header: Pwinuser.h.  Kbdui.lib.
  ms929240  GetFocus   Header: Winuser.h.  Caret.lib, Foregnd.lib.
  ms929241  GetForegroundInfo   Header: Pwinuser.h.  Linked during platform build
  ms929242  GetForegroundKeyboardLayoutHandle   Header: Pwinuser.h.  Linked during build.
  ms929243  GetForegroundKeyboardTarget   Header: Pwinuser.h.  Linked during build.
  ms929249  GetKeyboardLayout   Header: Winuser.h.  Coreimm.lib.
  ms929250  GetKeyboardLayoutList   Header: Winuser.h.  Coredll.lib.
  ms929252  GetKeyboardLayoutName   Header: Winuser.h.  Kbdui.lib.
  ms929253  GetKeyboardStatus   Header: Winuser.h.  Kbdui.lib.
  ms929254  GetKeyboardType   Header: Winuser.h.  Coredll.lib.
  aa453132  GetKeyState   Header: Winuser.h.  Kbdui.lib.
  aa453234  IsWindowEnabled   Header: Winuser.h.  Wmgr_c.lib.
  aa453245  keybd_event   Header: Winuser.h.  Uibase.lib.
  aa453246  KeybdGetDeviceInfo   Header: Pwinuser.h.  Coredll.lib.
  aa453407  LoadAccelerators   Header: Winuser.h.  Accel.lib.
  aa453414  LoadKeyboardLayout   Header: Winuser.h.  Coredll.lib.
  ms911789  MapVirtualKey   Header: Winuser.h.  Kbdui.lib.
  ms911936  PostKeybdMessage   Header: Winuser.h.  Kbdui.lib.
  ms913104  RegisterHotKey   Header: Winuser.h.  Hotkey.lib.
  ms932719  SendInput   Header: Winuser.h.  Wmgr_c.lib, Uibase.lib.
  ms939986  SetActiveWindow   Header: Winuser.h.  Caret.lib.
  ms940023  SetFocus   Header: Winuser.h.  Caret.lib, Foregnd.lib.
  aa453775  TranslateAccelerator   Header: Winuser.h.  Accel.lib.
  ms914083  UnregisterHotKey   Header: Winuser.h.  no Link Library row
```

#### Scroll Bars Functions (6)

Scroll Bars Functions (6).  GetScrollInfo aa453163 (CE 1.0+) /
SetScrollInfo aa453652 (CE 1.0+) / SetScrollPos aa453653 (CE 2.0+) /
SetScrollRange aa453654 (CE 2.0+): Header Winuser.h, Link Library
**Sbcmn.lib** -> def/sbcmn-doc.def.  ScrollWindowEx ms932713: Winuser.h,
"Coredll.lib, Winmgr.lib" -> coredll + def/winmgr-doc.def.  ScrollDC
ms932696: Header **Windows.h**, Coredll.lib -> declared in windows.h,
in def/coredll-doc.def.

```
  aa453163  GetScrollInfo   Header: Winuser.h.  Sbcmn.lib.
  ms932696  ScrollDC   Header: Windows.h.  Coredll.lib.
  ms932713  ScrollWindowEx   Header: Winuser.h.  Coredll.lib, Winmgr.lib.
  aa453652  SetScrollInfo   Header: Winuser.h.  Sbcmn.lib.
  aa453653  SetScrollPos   Header: Winuser.h.  Sbcmn.lib.
  aa453654  SetScrollRange   Header: Winuser.h.  Sbcmn.lib.
```

#### Windows Structures (6)

Windows Structures (6): CREATESTRUCT ms908189, STYLESTRUCT ms940380,
WINDOWPOS ms914101 (member blocks transcribed verbatim from the CE
pages) and the message-parameter packing macros MAKEWPARAM ms911780 /
MAKELPARAM aa453543 / MAKELRESULT ms911640.  The macro pages print
their bodies in terms of MAKELONG (windef.h now provides it);
MAKEWPARAM's page prints "(LPARAM)" where the cast belongs to WPARAM --
documented typo, conflict recorded in the notes below.

```
  ms908189  CREATESTRUCT   Header: Winuser.h.  no Link Library row
  aa453543  MAKELPARAM   Header: Winuser.h.  no Link Library row
  ms911640  MAKELRESULT   Header: Winuser.h.  no Link Library row
  ms911780  MAKEWPARAM   Header: Winuser.h.  no Link Library row
  ms940380  STYLESTRUCT   Header: Winuser.h.  no Link Library row
  ms914101  WINDOWPOS   Header: Winuser.h.  no Link Library row
```

#### Keyboard Structures (5)

Keyboard Structures (5): ACCEL aa452837 (CE 1.0+), INPUT ms909851 /
KEYBDINPUT aa453247 / MOUSEINPUT ms931454 (CE 2.0+), member layouts
transcribed verbatim from the CE pages; GET_FOREGROUND_INFO aa453186
(Header Pwinuser.h) is fetched and recorded, deferred with the OEM
keyboard batch.  HARDWAREINPUT, referenced by the INPUT union, has no
CE leaf -- fixed layout from Microsoft's official Win32 HARDWAREINPUT
structure reference (notes below).

```
  aa452837  ACCEL   Header: Winuser.h.  no Link Library row
  aa453186  GET_FOREGROUND_INFO   Header: Pwinuser.h.  no Link Library row
  ms909851  INPUT   Header: Winuser.h.  no Link Library row
  aa453247  KEYBDINPUT   Header: Winuser.h.  no Link Library row
  ms931454  MOUSEINPUT   Header: Winuser.h.  no Link Library row
```

#### Windows Messages (14)

Windows Messages (14, Header Winuser.h): fetched and recorded.  The
CE 5.0 WM_* pages document behavior and parameters but do **not**
publish the numeric message values, so no WM_* constant is defined
yet; the follow-on messages batch will transcribe values from fixed
Win32-ABI references with provenance.

```
  ms914108  WM_CANCELMODE   Header: Winuser.h.  no Link Library row
  ms914114  WM_CLOSE   Header: Winuser.h.  no Link Library row
  ms914118  WM_CREATE   Header: Winuser.h.  no Link Library row
  aa453854  WM_DESTROY   Header: Winuser.h.  no Link Library row
  aa453856  WM_ENABLE   Header: Winuser.h.  no Link Library row
  aa453858  WM_ERASEBKGND   Header: Winuser.h.  no Link Library row
  aa453864  WM_GETTEXT   Header: Winuser.h.  no Link Library row
  aa453865  WM_GETTEXTLENGTH   Header: Winuser.h.  no Link Library row
  aa453887  WM_MOVE   Header: Winuser.h.  no Link Library row
  aa453895  WM_QUIT   Header: Winuser.h.  no Link Library row
  aa453905  WM_SETTEXT   Header: Winuser.h.  no Link Library row
  aa453907  WM_SIZE   Header: Winuser.h.  no Link Library row
  aa453908  WM_STYLECHANGED   Header: Winuser.h.  no Link Library row
  aa453920  WM_WINDOWPOSCHANGED   Header: Winuser.h.  no Link Library row
```

#### Keyboard Messages (14)

Keyboard Messages (14, Header Winuser.h): same status as the Windows
Messages leaves above (WM_KEYDOWN/WM_KEYUP/WM_CHAR/... recorded; no
numeric values published by the CE pages).

```
  ms914105  WM_ACTIVATE   Header: Winuser.h.  no Link Library row
  ms914110  WM_CHAR   Header: Winuser.h.  no Link Library row
  aa453868  WM_HOTKEY   Header: Winuser.h.  no Link Library row
  aa453872  WM_INITMENUPOPUP   Header: Winuser.h.  no Link Library row
  aa453873  WM_KEYDOWN   Header: Winuser.h.  no Link Library row
  aa453876  WM_KEYUP   Header: Winuser.h.  no Link Library row
  aa453877  WM_KILLFOCUS   Header: Winuser.h.  no Link Library row
  aa453884  WM_MENUCHAR   Header: Winuser.h.  no Link Library row
  aa453901  WM_SETFOCUS   Header: Winuser.h.  no Link Library row
  aa453909  WM_SYSCHAR   Header: Winuser.h.  no Link Library row
  aa453911  WM_SYSCOMMAND   Header: Winuser.h.  no Link Library row
  aa453913  WM_SYSDEADCHAR   Header: Winuser.h.  no Link Library row
  aa453914  WM_SYSKEYDOWN   Header: Winuser.h.  no Link Library row
  aa453915  WM_SYSKEYUP   Header: Winuser.h.  no Link Library row
```

Window entry/class records: RegisterClass ms913089 returns an ATOM;
the class-registration pages (WNDCLASS/RegisterClass/GetClassInfo)
are Winuser.h / no-link-row like the rest of the window-manager book.
windef.h gained the fixed Win32-ABI window/message types the GWES
pages type against: HWND/HMENU/HACCEL/HBITMAP/HICON/HCURSOR/HBRUSH/
HDC/HRGN/HDWP/HKL handles, ATOM, WPARAM/LPARAM/LRESULT/
DWORD_PTR/PDWORD_PTR, SHORT, POINT/RECT/SIZE, and MAKELONG.

Documented conflicts and unknown facts recorded for M26:

* `MAKEWPARAM` (`ms911780`): the page prints the cast as "(LPARAM)";
  the macro's role is to build a WPARAM, so the definition casts to
  WPARAM (documentation typo; recorded, not silently copied).
* `HARDWAREINPUT` (referenced by `INPUT` ms909851): no CE GWES leaf
  defines the type.  The fixed layout `DWORD uMsg; WORD wParamL;
  WORD wParamH;` is taken from Microsoft's official Win32
  *HARDWAREINPUT* structure reference (winuser.h, learn.microsoft.com)
  -- a fixed-ABI reference, recorded as such.
* `SCROLLINFO`: the CE 5.0 Scroll Bars Structures book has no
  `(v=msdn.10)` leaf; its catalog entry points at the WinCE 6.0 twin
  `ee504371(v=winembedded.60)`.  The fixed Win32-ABI layout is used.
  SIF_*/SB_*/SW_* values are the fixed Win32-ABI values of the official
  scroll-bar reference the CE function pages type against.
* `KEY_STATE_FLAGS` (`ms902150`, Header Keybd.h): the page defines the
  type (`typedef UINT32 KEY_STATE_FLAGS`) and names the flag constants
  but publishes **no numeric values**; the six Pwinuser.h keyboard
  leaves that need it are deferred (values would have to be invented).
* WM_* message pages (28 leaves fetched) do not publish numeric values
  -> no WM_* constants yet (fixed-Win32-ABI transcription with
  provenance is the follow-on messages batch).
* OS rows cited in inline comments come from each page's "OS Versions"
  requirement: CE 1.0 (most window/caret/scroll/keyboard functions),
  CE 2.0/2.10 (SetTimer, RegisterWindowMessage, deferred window
  positioning, keyboard-layout-name), CE .NET 4.0 (properties, atoms,
  SendMessageTimeout, GetMessageQueueReadyTimeStamp) and CE .NET 4.2
  (ActivateKeyboardLayout/GetKeyboardLayoutList/GetKeyboardType/
  LoadKeyboardLayout, GetQueueStatus, foreground-input pages).


### M27: GDI Reference -- GDI Functions + GDI Structures (bulk)

Second graphics/user-interface batch, landed together as one large unit
with the full **GDI Reference** book of the CE 5.0 archive: two
manifests (`tools/manifests/gdi-functions.manifest`, 132 leaves;
`tools/manifests/gdi-structures.manifest`, 29 leaves) -> 161 unique
leaf pages; `build/rows.json` grows 666 -> **827** rows.

**Prototype recovery note.**  The migrated CE 5.0 pages (`(v=msdn.10)`)
serve their `<pre>` prototypes with inter-token whitespace removed
(`ce-fetch.py` reports "no-sig" for 99 of the GDI pages), while the CE
6.0 twins (`(v=winembedded.60)`, the same GDI book re-published with
`ee…`/`ms…` ids) still carry whitespace-preserved prototypes.  Every
M27 signature was therefore recovered from its **official CE 6.0 twin
page** (both archives were fetched; id pairs are listed
per-declaration in the headers), cross-checked against the CE 5.0
page bodies and the desktop-official fixed Win32 ABI where a CE page
omits a value.  No signature was invented: pages that print a bare
prototype without a return type are annotated inline with the page's
own "Return Values" text that fixes the type (the seven viewport/window
origin-and-extent getters/setters return BOOL -- nonzero success / zero
failure).  Two page typos are preserved with notes rather than silently
"fixed": TransparentBlt prints its 8th parameter as `int hHeightDest`
(sic; parameter is nHeightDest) and SetLayout prints a stray trailing
comma.  Three color accessor pages (GetRValue/GetGValue/GetBValue) are
documented by the official pages as **macros** with verbatim bodies and
no Link Library row, so they are defined as macros, not declared as
functions (129 declared functions + 3 macros from the 132 leaves).

**Header-home / new files.**  The CE 5.0 GDI Requirement rows name
Header Windows.h for the GDI bulk (CE 5 headers were monolithic).  This
substitute groups those items in a new **`include/wingdi.h`** (the CE
6.0-era component header, and the header the CE 5.0 TEXTMETRIC page
`ms901146` itself names), included by `windows.h`, so both CE 5-style
(`#include <windows.h>`) and CE 6-style (`#include <wingdi.h>`)
programs compile the same surface.  Items whose rows name Winuser.h
(27 functions incl. PAINTSTRUCT) live in winuser.h; the two rows naming
Winbase.h (InflateRect, SetRect) live in winbase.h; POINTS/RECTL
(Windef.h rows) and the three fixed-ABI GDI handle typedefs
HGDIOBJ/HPEN/HPALETTE were added to windef.h; VIDEOPARAMETERS (Header
Tvout.h) has a new `include/tvout.h`.  Fixed Win32-ABI support types
with **no CE structure page** are provided and recorded as such:
XFORM (ExtCreateRegion `aa453061` requires it, "[in] not supported; set
to NULL"), PANOSE (member type of OUTLINETEXTMETRICW `ms934025`),
GUID (leading member of VIDEOPARAMETERS `ms914096`), FLOAT, COLOR16 and
the DEVMODE string constants CCHDEVICENAME/CCHFORMNAME plus BCHAR.

Export-surface effect: coredll 221 -> **335** exports; the
Winuser.h-row window-manager items add winmgr 1 -> **17**; the
Rectapi.lib rows open `def/rectapi-doc.def` (11), the Loadbmp.lib row
`def/loadbmp-doc.def` (1) and the Nclient.lib row
`def/nclient-doc.def` (1): 18 -> **21** def files, **457** name-only
exports, every def llvm-dlltool-`-m armce` verified.  gen-doc-def.py
`short_title` now strips trailing "(GDI)"-style disambiguation
annotations so the page "CreatePalette (GDI)" contributes the export
`CreatePalette`.

#### GDI Functions (132 leaves; 129 declared + 3 color macros)

Requirement rows as published (declared location follows the Header
column per the note above; the three macro pages are marked *macro* in
wingdi.h).

%s

#### GDI Structures (29 leaves)

Requirement rows as published.  POINT (ms911930) and RECT (ms912843)
and SIZE (ms940344, page row Windows.h) are the tagPOINT/tagRECT/
tagSIZE forms already declared in windef.h for the GWES batch (same
fixed Win32-ABI layout); POINTS (ms911931) and RECTL (ms913063) are
new Windef.h-row additions.  PAINTSTRUCT (ms911912, Header Winuser.h)
is declared in winuser.h next to BeginPaint/EndPaint.  VIDEOPARAMETERS
(ms914096, Header Tvout.h) is in tvout.h.

%s

### M28: Window-control function layer (Menus / Dialog Boxes / Buttons / Clipboards / Printing / Resources / System Information / Notify + their Structures)

Landing as one large unit: the Dialog Boxes, Menus, Clipboards, Buttons, Printing, Resources and System-Information **Functions** and **Structures** books plus the Notify Reference books and the owner-draw/icon support structures (DRAWITEMSTRUCT / COMBOBOXINFO / MEASUREITEMSTRUCT / DELETEITEMSTRUCT / ICONINFO).  Regenerated GWES sub-book manifests (tools/ce-gwes-manifest.py + tools/gwes-targets.txt) all cross-check against tools/catalogs/books-windows-ce-50.tsv; build/rows.json grows 827 -> **939** rows (112 new leaf pages fetched: CE 5.0 + CE 6.0 twin, (v=msdn.10) + (v=winembedded.60)).

**Prototype recovery.**  As in M27 the migrated CE 5.0 pages serve `<pre>` prototypes with inter-token whitespace removed, so function signatures were recovered from the official CE 6.0 twin pages (identical API; ids recorded in the per-book manifests and headers) and cross-checked against the CE 5.0 body text.  Structure bodies (MENUITEMINFO, TPMPARAMS, DLG*, DOCINFO, SYSTEM_POWER_STATUS_EX(_2), the three CE_USER_NOTIFICATION/CE_NOTIFICATION_* and the owner-draw structs) are transcribed from the CE 5.0 structure pages, which print full `typedef struct` bodies.  No signature or member was invented; page-only facts are annotated inline.

**Header homes.**  Rows naming Winuser.h -> winuser.h; Winbase.h rows (FindResource/LoadResource/LockResource/SizeofResource, MessageBeep, GetSystemPowerStatusEx/Ex2 + both SYSTEM_POWER_STATUS_EX structs) -> winbase.h; Wingdi.h rows (printing book + DOCINFO + ABORTPROC, and DLGTEMPLATEEX/DLGITEMTEMPLATEEX whose pages print Header Wingdi.h) -> wingdi.h; the Header-Windows.h items (MessageBox, CheckDlgButton, IsDlgButtonChecked, DRAWITEMSTRUCT) stay in windows.h; SetSysColors is declared in wingdi.h because its prototype takes CONST COLORREF* and COLORREF is a GDI type (page row prints Header Winuser.h; deviation recorded here); Notify.h rows open a new **include/notify.h**; the Shellapi.h row (ExtractIconEx) opens **include/shellapi.h**; both are included by windows.h.  HRSRC (resource handle) was added to windef.h.

Export-surface effect: new def files clipbd (14), dlgmgr (18), drawmbar (1), icon (5), loadimg (1), menu (17), mgprint (6), msgbeep (1), msgbox (1 MessageBoxW), wmbase (1); coredll 335 -> **353** (notify x9, power x2, resource-module x4, SystemParametersInfoW, CheckDlgButton/IsDlgButtonChecked); winmgr -> 18 (SetSysColors), wmgr_c -> 4 (GetSysColor), kbdui -> 6 (EnableHardwareKeyboard): 21 -> **31** def files, all llvm-dlltool `-m armce` verified.  Text/Unicode-only functions are declared as W exports + generic macros per the repo rule and map in gen-doc-def.py.


#### Menus Functions (18 leaves; Header Winuser.h; Link Library rows Menu.lib for all but the text/creator pages, which publish no .lib row)

```
  aa452862  AppendMenu  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: 
  ms928575  CheckMenuItem  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Menu.lib.
  ms928576  CheckMenuRadioItem  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Menu.lib.
  ms908177  CreateMenu  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Menu.lib.
  ms908182  CreatePopupMenu  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Menu.lib.
  aa452932  DeleteMenu  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Menu.lib.
  aa452940  DestroyMenu  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Menu.lib.
  aa452975  DrawMenuBar  OS: Windows CE 2.0 and later.  Header: Winuser.h.  Lib: Drawmbar.lib. Menu.lib.
  aa453034  EnableMenuItem  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Menu.lib.
  aa453134  GetMenuItemInfo  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Menu.lib.
  aa453166  GetSubMenu  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Menu.lib.
  aa453169  GetSystemMenu  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Menu.lib.
  ms909853  InsertMenu  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Menu.lib.
  aa453415  LoadMenu  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Menu.lib.
  ms939775  RemoveMenu  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Menu.lib.
  ms940027  SetMenuItemInfo  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Menu.lib.
  aa453773  TrackPopupMenu  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Menu.lib.
  aa453774  TrackPopupMenuEx  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Menu.lib.
```

#### Menus Structures (2)

```
  ms911822  MENUITEMINFO  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: 
  aa453766  TPMPARAMS  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: 
```

#### Dialog Boxes Functions (27; Header Winuser.h except MessageBox/CheckDlgButton/IsDlgButtonChecked = Windows.h and MessageBeep = Winbase.h; Link Library rows Dlgmgr.lib / Msgbox.lib / Msgbeep.lib / Coredll.lib)

```
  ms928573  CheckDlgButton  OS: Windows CE .NET 4.0 and later.  Header: Windows.h.  Lib: Coredll.lib.
  ms908169  CreateDialog  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: 
  ms908170  CreateDialogIndirect  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Dlgmgr.lib.
  ms908171  CreateDialogIndirectParam  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Dlgmgr.lib.
  ms908172  CreateDialogParam  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: 
  ms908209  DefDlgProc  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Dlgmgr.lib.
  aa452947  DialogBox  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: 
  aa452948  DialogBoxIndirect  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: 
  aa452949  DialogBoxIndirectParam  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Dlgmgr.lib.
  aa452950  DialogBoxParam  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: 
  aa452951  DialogProc  OS: Windows CE 1.0 and later.  Header: Developer implemented.  Lib: Developer implemented.
  aa453038  EndDialog  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Dlgmgr.lib.
  ms929231  GetDialogBaseUnits  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Dlgmgr.lib.
  ms929233  GetDlgCtrlID  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Dlgmgr.lib.
  ms929234  GetDlgItem  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Dlgmgr.lib.
  ms929235  GetDlgItemInt  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Dlgmgr.lib.
  ms929236  GetDlgItemText  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Dlgmgr.lib.
  aa453145  GetNextDlgGroupItem  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Dlgmgr.lib.
  aa453146  GetNextDlgTabItem  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Dlgmgr.lib.
  ms909864  IsDialogMessage  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Dlgmgr.lib.
  ms909866  IsDlgButtonChecked  OS: Windows CE .NET 4.0 and later.  Header: Windows.h.  Lib: Coredll.lib.
  ms911788  MapDialogRect  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Dlgmgr.lib.
  ms911826  MessageBeep  OS: Windows CE 1.0 and later.  Header: Winbase.h.  Lib: Msgbeep.lib.
  ms911827  MessageBox  OS: Windows CE 1.0 and later.  Header: Windows.h.  Lib: Msgbox.lib.
  ms932717  SendDlgItemMessage  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Dlgmgr.lib.
  ms940020  SetDlgItemInt  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Dlgmgr.lib.
  ms940021  SetDlgItemText  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Dlgmgr.lib.
```

#### Dialog Boxes Structures (4)

```
  aa452958  DLGITEMTEMPLATE  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: 
  aa452959  DLGITEMTEMPLATEEX  OS: Windows CE 2.0 and later.  Header: Wingdi.h.  Lib: 
  aa452960  DLGTEMPLATE  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: 
  aa452961  DLGTEMPLATEEX  OS: Windows CE 2.12 and later.  Header: Winuser.h.  Lib: 
```

#### Buttons Functions (1)

```
  ms928577  CheckRadioButton  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Dlgmgr.lib.
```

#### Clipboards Functions (14; Header Winuser.h; Clipbd.lib)

```
  ms928586  CloseClipboard  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Clipbd.lib.
  ms908153  CountClipboardFormats  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Clipbd.lib.
  aa453019  EmptyClipboard  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Clipbd.lib.
  aa453047  EnumClipboardFormats  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Clipbd.lib.
  ms929215  GetClipboardData  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Clipbd.lib.
  ms929216  GetClipboardDataAlloc  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Clipbd.lib.
  ms929217  GetClipboardFormatName  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Clipbd.lib.
  ms929218  GetClipboardOwner  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Clipbd.lib.
  aa453149  GetOpenClipboardWindow  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Clipbd.lib.
  aa453154  GetPriorityClipboardFormat  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Clipbd.lib.
  ms909863  IsClipboardFormatAvailable  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Clipbd.lib.
  ms911905  OpenClipboard  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Clipbd.lib.
  ms913094  RegisterClipboardFormat  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Clipbd.lib.
  ms940015  SetClipboardData  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Clipbd.lib.
```

#### Printing Functions (7; Header Wingdi.h; Mgprint.lib)

```
  aa452835  AbortDoc  OS: Windows CE 2.0 and later.  Header: Wingdi.h.  Lib: Mgprint.lib.
  aa452836  AbortProc  OS: Windows CE 2.0 and later.  Header: Wingdi.h.  Lib: Mgprint.lib.
  aa453039  EndDoc  OS: Windows CE 2.0 and later.  Header: Wingdi.h.  Lib: Mgprint.lib.
  aa453040  EndPage  OS: Windows CE 2.0 and later.  Header: Wingdi.h.  Lib: Mgprint.lib.
  ms939985  SetAbortProc  OS: Windows CE 2.0 and later.  Header: Wingdi.h.  Lib: Mgprint.lib.
  ms940349  StartDoc  OS: Windows CE 2.0 and later.  Header: Wingdi.h.  Lib: Mgprint.lib.
  ms940350  StartPage  OS: Windows CE 2.0 and later.  Header: Wingdi.h.  Lib: Mgprint.lib.
```

#### Printing Structures (1)

```
  aa452964  DOCINFO  OS: Windows CE 2.0 and later.  Header: Wingdi.h.  Lib: 
```

#### Resources Functions (11; Headers Winuser.h / Winbase.h / Shellapi.h per row; libs Icon.lib, Loadimg.lib, Coredll.lib/Nk.lib)

```
  ms908175  CreateIconIndirect  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Icon.lib.
  aa452938  DestroyIcon  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Icon.lib.
  aa452972  DrawIconEx  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Icon.lib.
  aa453065  ExtractIconEx  OS: Windows CE 1.0 and later.  Header: Shellapi.h.  Lib: 
  aa453069  FindResource  OS: Windows CE 1.0 and later.  Header: Winbase.h.  Lib: Coredll.lib, Nk.lib.
  ms929247  GetIconInfo  OS: Windows CE 5.0 and later.  Header: Winuser.h.  Lib: Icon.lib.
  aa453411  LoadIcon  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Icon.lib.
  aa453413  LoadImage  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Loadimg.lib.
  aa453416  LoadResource  OS: Windows CE 1.0 and later.  Header: Winbase.h.  Lib: Coredll.lib, Nk.lib
  aa453417  LockResource  OS: Windows CE 1.0 and later.  Header: Winbase.h.  Lib: Coredll.lib, Nk.lib
  ms940346  SizeofResource  OS: Windows CE 1.0 and later.  Header: Winbase.h.  Lib: Coredll.lib.
```

#### Resources Macros (1: MAKEINTRESOURCE)

```
  aa453542  MAKEINTRESOURCE  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: 
```

#### System Information Functions (7; Headers Winuser.h / Winbase.h)

```
  aa453033  EnableHardwareKeyboard  OS: Windows CE 2.0 and later.  Header: Winuser.h.  Lib: Kbdui.lib.
  aa453167  GetSysColor  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Wmgr_c.lib.
  aa453170  GetSystemMetrics  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: Wmbase.lib.
  aa453172  GetSystemPowerStatusEx  OS: Windows CE 1.0 and later.  Header: Winbase.h.  Lib: Coredll.lib.
  aa453173  GetSystemPowerStatusEx2  OS: Windows CE 2.12 and later.  Header: Winbase.h.  Lib: Coredll.lib.
  aa453656  SetSysColors  OS: Windows CE 2.0 and later.  Header: Winuser.h.  Lib: Winmgr.lib.
  ms940383  SystemParametersInfo  OS: Windows CE 2.0 and later.  Header: Winuser.h.  Lib: Coredll.lib.
```

#### System Information Structures (2)

```
  ms940384  SYSTEM_POWER_STATUS_EX  OS: Windows CE 1.0 and later.  Header: Winbase.h.  Lib: 
  ms940385  SYSTEM_POWER_STATUS_EX2  OS: Windows CE 2.12 and later.  Header: Winbase.h.  Lib: 
```

#### Notify Functions (9; Header Notify.h; Coredll.lib)

```
  ms908074  CeClearUserNotification  OS: Windows CE 1.01 and later.  Header: Notify.h.  Lib: Coredll.lib.
  ms908076  CeGetUserNotification  OS: Windows CE 2.12 and later.  Header: Notify.h.  Lib: Coredll.lib.
  ms908077  CeGetUserNotificationHandles  OS: Windows CE 2.12 and later.  Header: Notify.h.  Lib: Coredll.lib.
  ms908078  CeGetUserNotificationPreferences  OS: Windows CE 1.01 and later.  Header: Notify.h.  Lib: Coredll.lib.
  ms908079  CeHandleAppNotifications  OS: Windows CE 1.01 and later.  Header: Notify.h.  Lib: Coredll.lib.
  ms908102  CeRunAppAtEvent  OS: Windows CE 1.01 and later.  Header: Notify.h.  Lib: Coredll.lib.
  ms908103  CeRunAppAtTime  OS: Windows CE 1.0 and later.  Header: Notify.h.  Lib: Coredll.lib.
  ms908104  CeSetUserNotification  OS: Windows CE 1.01 and later.  Header: Notify.h.  Lib: Coredll.lib.
  ms908105  CeSetUserNotificationEx  OS: Windows CE 2.12 and later.  Header: Notify.h.  Lib: Coredll.lib.
```

#### Notify Structures (3)

```
  ms908082  CE_NOTIFICATION_INFO_HEADER  OS: Windows CE 2.12 and later.  Header: Notify.h.  Lib: 
  ms908083  CE_NOTIFICATION_TRIGGER  OS: Windows CE 2.12 and later.  Header: Notify.h.  Lib: 
  ms908106  CE_USER_NOTIFICATION  OS: Windows CE 1.01 and later.  Header: Notify.h.  Lib: 
```

#### Combo Boxes Structures (3)

```
  ms928818  COMBOBOXINFO  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: 
  aa452974  DRAWITEMSTRUCT  OS: Windows CE 1.0 and later.  Header: Windows.h.  Lib: 
  ms911820  MEASUREITEMSTRUCT  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: 
```

#### List Boxes Structures (1)

```
  aa452931  DELETEITEMSTRUCT  OS: Windows CE 1.0 and later.  Header: Winuser.h.  Lib: 
```

#### ICONINFO (support structure for the Resources icon functions; catalog leaf ms929934)
```
  ms929934  ICONINFO  OS: Windows CE 1.0 and later.  Header: Commctrl.h.  Lib: 
```

Notes: MENUITEMINFO/TPMPARAMS/COMBOBOXINFO/MEASUREITEMSTRUCT/DELETEITEMSTRUCT/DRAWITEMSTRUCT/ICONINFO/DOCINFO/CE_NOTIFICATION_TRIGGER/CE_USER_NOTIFICATION/CE_NOTIFICATION_INFO_HEADER layouts come from the structure pages above (see the inline member comments for the CE-specific member sets, e.g. CE MENUITEMINFO has UINT wID and no hbmpItem).  DLGTEMPLATE/DLGITEMTEMPLATE are in winuser.h and the DLGTEMPLATEEX/DLGITEMTEMPLATEEX fixed prefixes (variable-length arrays follow in memory) in wingdi.h per their pages.  The power-status structs declare only the members the official pages list.  DialogProc (aa452951) and AbortProc (aa452836) are documented callbacks, not imports, so they are typedefs (DLGPROC / ABORTPROC), not exports.


### M29: Image List Reference books + GWES message/notification constants

Two units landed together: the full **Image Lists** book of the CE 5.0
GWES documentation (Functions 32 / Macros 4 / Structures 2 = 38
leaves) and the **message / notification** leaves of the Buttons /
Static Controls / Menus / Dialog Boxes / Clipboards / GDI / ROP
books (39 leaves), plus the numeric transcription of the already
harvested Windows-Messages and Keyboard-Messages leaves (M26) into
message identifiers.  New header `include/commctrl.h`; the message
identifiers and notification codes join the GWES message constants in
`include/winuser.h` and the binary/ternary raster-operation codes go
into `include/wingdi.h`.  The message block also carries the Combo
Boxes / List Boxes / Edit Boxes message and notification identifiers
(CB_*/CBN_*, LB_*/LBN_*, EM_*/EN_*, with their CE page ids) -- those
leaves were already-harvested manifests and the same
fixed-Win32-ABI numeric policy applies to them.  Rows grow 939 ->
**1175** (69 manifests; this session fetched the full committed
manifest set -- every CE 5.0 leaf -- and regenerated `build/rows.json`
from scratch, so the 236-row delta includes leaves of the Combo/List/
Edit message and style books that were harvested for the first time,
not only the two M29 units).

#### Image List Functions / Macros / Structures (Commctrl.h; Link Library row Commctrl.lib, Imgctl.lib.)

Every function page prints Header **Commctrl.h** and Link Library
**Commctrl.lib, Imgctl.lib.** except `ImageList_Destroy` (ms909811),
whose page omits the Link Library row in both the CE 5.0 and the CE
6.0 twin (ee501989) -- so the documented import defs (below) carry
the other 31 functions but not ImageList_Destroy.  Signatures were
recovered from the official CE 6.0 `(v=winembedded.60)` twins of the
same books (the CE 5.0 migration strips whitespace inside `<pre>`
prototypes) and cross-checked to the CE 5.0 bodies; each declaration
in commctrl.h annotates both page ids.  HIMAGELIST is typed
`typedef void *HIMAGELIST;` -- the CE pages use the type everywhere
without republishing its typedef, so it is supplied as an opaque
handle like the other GWES handles (own-design record of the fixed
ABI).  The ILC_* / ILD_* / CLR_* / CLR_DEFAULT flag values are named
by the CE pages; the numeric values are the fixed Win32 ABI values
(the CE pages do not republish them), recorded per the repo fixed-ABI
policy.

```
  ms909786  ImageList_Add          CE 1.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909795  ImageList_AddMasked    CE 1.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909799  ImageList_BeginDrag    CE 1.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909805  ImageList_Copy         CE 2.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909810  ImageList_Create       CE 1.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909811  ImageList_Destroy      CE 1.0+   Commctrl.h   (no Link Library row)
  ms909812  ImageList_DragEnter    CE 1.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909813  ImageList_DragLeave    CE 1.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909814  ImageList_DragMove     CE 1.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909815  ImageList_DragShowNolock CE 1.0+ Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909816  ImageList_Draw         CE 1.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909817  ImageList_DrawEx       CE 1.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909818  ImageList_DrawIndirect CE 2.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909820  ImageList_Duplicate    CE 2.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909821  ImageList_EndDrag      CE 1.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909823  ImageList_GetBkColor   CE 1.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909824  ImageList_GetDragImage CE 1.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909825  ImageList_GetIcon      CE 1.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909826  ImageList_GetIconSize  CE 1.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909827  ImageList_GetImageCount CE 1.0+  Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909828  ImageList_GetImageInfo CE 1.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909830  ImageList_LoadImage    CE 1.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909831  ImageList_Merge        CE 1.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909832  ImageList_Remove       CE 1.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909833  ImageList_RemoveAll    CE 1.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909834  ImageList_Replace      CE 1.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909835  ImageList_ReplaceIcon  CE 1.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909836  ImageList_SetBkColor   CE 1.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909837  ImageList_SetDragCursorImage CE 1.0+ Commctrl.h Commctrl.lib, Imgctl.lib.
  ms909838  ImageList_SetIconSize  CE 1.0+   Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909839  ImageList_SetImageCount CE 2.0+  Commctrl.h   Commctrl.lib, Imgctl.lib.
  ms909840  ImageList_SetOverlayImage CE 1.0+ Commctrl.h  Commctrl.lib, Imgctl.lib.
```

Image List Macros (4): `ImageList_AddIcon` ms909790 (macro = ImageList_ReplaceIcon(himl, -1, hicon)), `ImageList_ExtractIcon` ms909822, `ImageList_LoadBitmap` ms909829 and `INDEXTOOVERLAYMASK` ms909843; bodies are verbatim from the CE 5.0 page text; no Link Library row (macros, not imports).  The CE `ImageList_LoadImage` page (ms909830) documents uType values **IMAGE_BITMAP** and **IMAGE_ICON** only, and the CE LoadImage page (aa453413) documents IMAGE_BITMAP / IMAGE_CURSOR / IMAGE_ICON; IMAGE_ENHMETAFILE is not documented for CE and is not shipped (the three documented image-type values live in winuser.h: IMAGE_BITMAP 0 / IMAGE_ICON 1 / IMAGE_CURSOR 2, fixed Win32 ABI).

Image List Structures (2): `IMAGEINFO` ms909781 (hbmImage, hbmMask, Unused1, Unused2, rcImage) and `IMAGELISTDRAWPARAMS` ms909819 (14 members, first cbSize).  IMAGEINFO is 32 bytes and IMAGELISTDRAWPARAMS 56 bytes on the 32-bit CE ABI (checked with static asserts under the CE toolchain).

#### Buttons / Static / Menus / Dialog / Clipboards / GDI message and ROP books (39 leaves)

These leaves name the constants the GWES messages protocol is built
on; the CE pages document each name and its wParam/lParam but do not
republish the numeric identifiers.  The numeric values shipped in
winuser.h/wingdi.h are the fixed Win32 ABI values of the message
protocol GWES implements (same fixed-ABI policy as the SIF / SB / SW
and message-id transcription recorded since M26; every define carries
its CE page id).  Notification codes with CE pages (BN_*/STN_*/CBN_*/
LBN_*/EN_*) use the fixed Win32 ABI notification-code values.
STN_DBLCLK has no CE leaf (desktop-only) and is not shipped.

```
  aa452890..aa452898  BM_CLICK / BM_GETCHECK / BM_GETSTATE / BM_SETCHECK /
                      BM_SETSTATE / BM_SETSTYLE / BN_CLICKED / BN_KILLFOCUS / BN_SETFOCUS
                      (Buttons Messages; CE 1.0+; Header Winuser.h/Windows.h rows as published)
  ms940366..ms940370  STM_GETIMAGE / STM_SETIMAGE / STN_CLICKED / STN_ENABLE / STN_DISABLE
  aa452962..aa452963  DM_GETDEFID / DM_SETDEFID  (Dialog Boxes Messages)
  aa453847..aa453851  WM_CTLCOLORDLG / WM_CTLCOLOREDIT / WM_CTLCOLORLISTBOX / WM_CTLCOLORSTATIC
  ms914115..ms914119  WM_COMMAND / WM_CONTEXTMENU / WM_COPY / WM_CTLCOLORBTN  (as pages print)
  aa453852,aa453893,aa453898,aa453899  WM_CUT/WM_PASTE/WM_RENDERALLFORMATS/WM_RENDERFORMAT (Clipboards Messages)
  aa453891..aa453911  GDI window messages (WM_PAINT, WM_SETREDRAW, WM_SYSCOLORCHANGE,
                      WM_QUERYNEWPALETTE, WM_PALETTECHANGED) per the GDI Messages book
  aa452783/aa452878   Ternary / Binary Raster Operation code tables -> SRC*/PAT*/R2_* macros in wingdi.h
```

winuser.h message block totals ~250 defines: the M26 Windows Messages
(14) and Keyboard Messages (14) leaves (the M26-announced numeric
follow-on), the Buttons/Static/Menus/Dialog/Clipboard/GDI message
books, and the Combo/List/Edit message and notification leaves (pages
harvested with the M26-era manifests); each name keeps its CE page id.  WM_USER
is 0x0400; DM_GETDEFID/DM_SETDEFID are (WM_USER+0)/(WM_USER+1) as the
pages describe.  The EN_* edit notification codes are the fixed Win32
ABI 0x0100-range values (EN_SETFOCUS 0x0100 ... EN_VSCROLL 0x0602)
with their CE page ids (aa453036/aa453042..aa453054).

Export surface: 31 -> **33** def files; new `def/commctrl-doc.def`
and `def/imgctl-doc.def` (31 name-only exports each, the documented
Link Library rows of the Image List functions), both
llvm-dlltool-`-m armce` verified; total name-only exports 543 -> 605.
ImageList_Destroy is declared (its page documents it) but appears in
no import def (no documented Link Library row; recorded).  Host +
six CE targets (arm/i386 x 4.2/5.0/6.0) pass warning-free; the TU
type-checks every Image List function call and static-asserts the two
structure sizes on the 32-bit ABI.



### M30: remaining documented Winbase.h/Windows.h functions (coredll/coreloc gap fill)

Machine audit of `build/rows.json` (1175 harvested CE 5.0 leaves)
against the shipped headers found 63 signature-bearing rows whose page
name was not declared anywhere; most are intentionally non-exports
(debug *macros* documented but not specified in implementable form --
recorded in M24; Kfuncs.h kernel scope; Pwinuser.h OEM; callback
typedefs ThreadProc/FiberProc/DllMain/AbortProc/PropEnumProcEx; the
keyword false positives "for/if/switch"; macro pages
MAKEINT*/*MAKEL*/MAKEINTRESOURCE/*MAKELANGID).  The genuine missing
user-mode exports are added here.  Header homes follow each page's
Header row (Windows.h page -> include/windows.h).

| Function | Official page (CE 5.0) | OS Versions | Header | Link Library | Notes |
|---|---|---|---|---|---|
| `FreeLibraryAndExitThread` | `ms885602` | CE 3.0+ | Winbase.h | Coredll.dll | page: implemented as FreeLibrary(hModule); ExitThread(dwExitCode) |
| `CeZeroPointer` | `ms885158` | CE .NET 4.2+ | Winbase.h | Coredll.lib | maps a process-slot pointer to slot-zero; page points to OEM Pkfuncs.h ZeroPtr macro |
| `CeGetThreadQuantum` | `aa450796` | CE 3.0+ | Winbase.h | Coredll.lib | quantum in ms; MAXDWORD on failure |
| `CeSetThreadQuantum` | `ms885156` | CE 3.0+ | Winbase.h | Coredll.lib | dwTime 0 runs to completion; OEM default 100 ms |
| `VerQueryValueW` | `aa450973` | CE 3.0+ | Winbase.h | Coredll.lib | Unicode-only export spelling of VerQueryValue (LPTSTR sub-block); resolves \\VarFileInfo\\Translation etc. |
| `IsProcessorFeaturePresent` | `ms886726` | CE .NET 4.1+ | Winbase.h | Coredll.dll | flag *names* PF_ARM_*/PF_MIPS_* documented, values unpublished -> no PF_* constants shipped (recorded, cf. KEY_STATE_FLAGS) |
| `QueryInstructionSet` | `ms886787` | CE .NET 4.0+ | Winbase.h | Coredll.lib | PROCESSOR_*_INSTRUCTION names documented, values unpublished -> not defined |
| `SetUserDefaultLCID` | `ms906279` | CE .NET 4.0+ | Windows.h | Coreloc.lib | page requires broadcasting WM_WININICHANGE (wParam INI_INTL) after |

Deferred with reasons (recorded here so they are not re-derived):
CeHeapCreate (aa450797) needs the PFN_AllocHeapMem/PFN_FreeHeapMem
callback prototypes that the page defers to the OEM Pkfuncs.h
(unpublished); GetThreadContext (ms885642) / ReadProcessMemory
(ms886794) / WriteProcessMemory (aa450992) / SetThreadContext
(ms885155-family) operate on the per-CPU CONTEXT whose layout the
Winnt.h header pages do not publish (incomplete CONTEXT type already
recorded, M24); TranslateCharsetInfo (aa450955, Coredll.lib) needs the
CHARSETINFO structure + TCI_* values (no CE structure leaf in the
harvested set).  CeSetThreadPriority (ms885155) and SetThreadContext
rows name Nk.lib only -> kernel scope, not declared.  Dbgapi.h debug
macros (ASSERT/DEBUGMSG/RETAILMSG/ERRORMSG/DEBUGZONE/DEBUGCHK/
ASSERTMSG/DEBUGLED/RETAILLED/ERRORMSG) remain intentionally undeclared
(macro machinery not specified in implementable form; M24 record).

Export surface: coredll 353 -> 360, coreloc 23 -> 24 (SetUserDefaultLCID),
total name-only exports 605 -> **613**.  gen-doc-def.py's Unicode-only
map gains VerQueryValue -> VerQueryValueW.  Host + six CE targets pass
warning-free.


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
