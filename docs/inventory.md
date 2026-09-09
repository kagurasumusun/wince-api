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



### M31: message/version/charset/cross-process units (winuser + winbase + wingdi + winnt)

Multi-unit continuation of the rows.json-vs-headers audit.  The full
201-title gap list was re-derived with a word-boundary matcher and
triaged: 85 are index pages or style/error tables (recorded in
sections above / below), 61 are CEL_* kernel event-payload pages
already recorded as intentionally not transcribed (see the celog.h
header note and M21/M25 records), the Dbgapi debug macros, Kfuncs.h
and Pwinuser.h items and the NAT editor callbacks are recorded
intentional non-exports, and the remainder are implemented here.

| Item | Official page (CE 5.0) | OS | Header | Link Library | Notes |
|---|---|---|---|---|---|
| `WM_COPYDATA` = 0x004A | `aa453921` | CE 1.0+ | Winuser.h | — | fixed Win32 ABI message value (message page documents semantics; see also COPYDATASTRUCT note below) |
| `ReadProcessMemory` | `ms886794` | CE 2.0+ | Winbase.h | Coredll.lib, Nk.lib | Coredll.lib membership feeds the def; Nk.lib kernel scope excluded |
| `GetThreadContext` | `ms885642` | CE 2.0+ | Winbase.h | Coredll.lib, Nk.lib | parameter typed LPCONTEXT; CONTEXT is the M24-recorded incomplete type; LPCONTEXT alias added to winnt.h |
| `VS_FIXEDFILEINFO` | `aa450983` | CE 3.0+ | Winbase.h | — | dwSignature 0xFEEF04BD documented on the page; VS_FF_* flag names from the page table, numeric values fixed Win32 ABI (recorded) |
| `FONTSIGNATURE` | `ms885597` | CE 2.10+ | Wingdi.h | — | fsUsb[4]/fsCsb[2], members per page prototype |
| `CHARSETINFO` (+ LPCHARSETINFO) | `ms885163` | CE 2.11+ | Wingdi.h | — | ciCharset/ciACP/fs; CE layout exactly as the page prints (no union) |
| `TranslateCharsetInfo` | `aa450955` | CE 2.0+ | Wingdi.h | Coredll.lib | page's dwFlags table names TCI_SRCCHARSET/TCI_SRCCODEPAGE/TCI_SRCFONTSIG (fixed Win32 ABI values); page remark table names the supported *_CHARSET / FS_* values by name only -> recorded, not defined |

Recorded-not-defined (names documented, values/numerics unavailable on
the CE pages or in a clean table): the *_CHARSET and FS_* constants of
the aa450955 translation table, VS_FF_* beyond the fixed-ABI six above
are all the page lists, WM_SYSCOPYDATA (aa453912, Pwinuser.h -- OEM
window class range), COPYDATASTRUCT (referenced by aa453921; no CE
structure leaf, desktop fixed layout would need a Win32 structure
reference -- deferred).  Deferred function rows kept on file:
CopyFileEx (aa517311, CE 5.0+; needs the COPY_FILE_* flags + progress
routine typedef), GetUserNameEx (aa517595; needs EXTENDED_NAME_FORMAT
values, no CE numeric table), CeHeapCreate (aa450797; OEM Pkfuncs
callback prototypes), WriteProcessMemory / SetThreadContext (Nk.lib
only -> kernel scope).  The crypto/NTE/TRUST/CERTSRV/RAS/Net error-code
table pages are recorded as not yet transcribed: their Value columns
are not numeric tables on the CE pages (winerror.h stays at the System
0-1078 numeric table, aa450919).

Export surface: coredll 360 -> 363 (ReadProcessMemory, GetThreadContext,
TranslateCharsetInfo), total name-only exports 613 -> **616** (33 def
files).  Host + six CE targets pass warning-free; TU static-asserts
FONTSIGNATURE=24 / CHARSETINFO=32 / VS_FIXEDFILEINFO=52 on the 32-bit
ABI (also verified under the CE toolchain targets).



### M32: NLS formatting / locale-info unit (Coreloc.lib; winnls.h)

The NLS *formatting* layer of the Coreloc export surface: functions
whose pages print Header Winnls.h and Link Library Coreloc.lib, OS
Versions "Windows CE .NET 4.0 and later" (exceptions noted per page).

| Item | Official page (CE 5.0) | Header | Link Library | Notes |
|---|---|---|---|---|
| `CURRENCYFMT` struct | `ms904720` | Winnls.h | — | member list verbatim: NumDigits/LeadingZero/Grouping, lpDecimalSep/lpThousandSep, NegativeOrder/PositiveOrder, lpCurrencySymbol |
| `NUMBERFMT` struct | `ms906228` | Winnls.h | — | NumDigits/LeadingZero/Grouping, lpDecimalSep/lpThousandSep, NegativeOrder |
| `GetCurrencyFormatW` | `ms905229` | Winnls.h | Coreloc.lib | returns char count; cch 0 -> required size; dwFlags must be 0 when lpFormat non-NULL |
| `GetNumberFormatW` | `ms905250` | Winnls.h | Coreloc.lib | same contract |
| `GetDateFormatW` | `ms905235` | Winnls.h | Coreloc.lib | lpFormat picture string or locale default; Locale ignored on CE 1.0 |
| `GetTimeFormatW` | `ms905310` | Winnls.h | Coreloc.lib | same contract |
| `GetLocaleInfoW` | `ms905243` | Winnls.h | Coreloc.lib | LCType param takes the LCTYPE constants |
| `SetLocaleInfoW` | `ms906277` | Winnls.h | Coreloc.lib | LCType param takes the LCTYPE constants |
| `LCTYPE` typedef (DWORD) | `ms905243` + `ms906223` | Winnls.h | — | the LCTYPE constant *space*; the ms906223 table values are recorded-not-transcribed (follow-on) |

The `DATE_*` / `TIME_*` flag names the GetDateFormat/GetTimeFormat
pages document (dwFlags) are recorded but not defined -- the pages do
not republish numeric values; every function is callable with
dwFlags = 0 for the locale default, which the pages define.  The NLS
macro/identifier pages (MAKELCID `ms906226`, LCTYPE Constants
`ms906223`, Language Identifiers and Locales `ms903928`, NLS Locale
Identifiers `ms906224`) remain recorded follow-ons.  CE is
Unicode-only, so the exports are the W spellings with generic macros
(gen-doc-def Unicode map updated).

Export surface: coreloc 24 -> **30** (the six W functions above);
total name-only exports 616 -> **622** (33 def files).  winnls.h now
includes winbase.h for SYSTEMTIME (the date/time formatters type
against it).  Host + six CE targets pass warning-free; TU
static-asserts CURRENCYFMT=32 / NUMBERFMT=24 on the 32-bit ABI.



### M33: CE 6.0 full-twin corpus + reconciliation; COPYDATASTRUCT

All 1133 resolvable CE 6.0 twins of the harvested CE 5.0 corpus were
fetched in full and reconciled (see `docs/ce6-reconciliation.md` and
the committed map `docs/ce6-twins.tsv`; `tools/ce-twins.py` regenerates
the map from the committed official catalogs).  The corpus
preservation repo's `pages6/` grows 38 -> 1133 pages.  1039 of the
1133 twins have Requirement rows identical to the CE 5.0 record; the
51 differences are categorized in the doc: editorial wording of
Not-applicable/Developer-Implemented rows, the CE 6.0 kernel-mode
library row `Nkstub.lib` / OEM `OEMMain.lib` (user-mode apps still
link Coredll; import defs unchanged; Nkstub/OEMMain are never
import-def sources, same rule as Nk.lib/Coremain.lib), header/library
case-order-punctuation, and three *information fills* where the CE 5.0
page row was blank:
  DISPLAY_DEVICE  (CE6 ee499040: OS .NET 4.2+, Header windows.h),
  GRADIENT_RECT   (CE6 ee504211: OS .NET 4.2+, Header windows.h),
  FILECHANGEINFO  (CE6 ee490403 adds Header extfile.h, shlobj.h and
                   Link Library ceshell.lib).
42 CE 5.0 leaves have no CE 6.0 twin -- all book index pages.

Also added (WM_COPYDATA support): `COPYDATASTRUCT` in winuser.h.  The
CE page aa453921 types lParam with a pointer to the structure but the
CE books publish no structure leaf; the fixed layout is taken from
Microsoft's official Win32 *COPYDATASTRUCT* structure reference
(winuser.h, learn.microsoft.com) -- fixed-ABI record (same policy as
HARDWAREINPUT / CRITICAL_SECTION).  12 bytes on the 32-bit ABI
(static-asserted).  No new exports (struct-only).

### M34 header batch: NLS string mapping + directory-service user name

Added after the CE 6.0 full-twin reconciliation; every page below was
read from the CE 5.0 `(v=msdn.10)` page and its CE 6.0
`(v=winembedded.60)` twin (both saved in the corpus), plus the CE .NET
`(v=msdn.10)` twins of the NLS functions.

* `LCMapString` ms906221 (twin ee491201, CE .NET ms921462):
  `int LCMapString(LCID, DWORD, LPCTSTR, int, LPTSTR, int)`.  OS
  CE .NET 4.0+; Winnls.h; Coreloc.lib.  Declared `LCMapStringW` +
  `#define LCMapString LCMapStringW` (the page itself states
  "Windows CE supports only the Unicode version of this function").
  The LCMAP_* / NORM_* dwMapFlags *names* are listed on the page but
  the CE page does not publish their numeric values -> no flag
  constants shipped (recorded; value-table backlog).
* `FoldString` ms905209 (twin ee491930, CE .NET ms919269): `int
  FoldString(DWORD, LPCTSTR, int, LPTSTR, int)`.  OS CE 1.0+;
  Winnls.h; Coreloc.lib.  `FoldStringW` + macro.  The MAP_* flag
  names (MAP_FOLDCZONE / MAP_PRECOMPOSED / MAP_COMPOSITE /
  MAP_FOLDDIGITS / MAP_EXPAND_LIGATURES) are on the page with CE
  support notes but without values -> no MAP_* constants shipped.
* `EnumSystemCodePages` ms905062 (twin ee491962, CE .NET ms919231):
  `BOOL EnumSystemCodePages(CODEPAGE_ENUMPROC, DWORD)`.  OS CE .NET
  4.0+; Winnls.h; Coreloc.lib.  `EnumSystemCodePagesW` + macro.
* `CODEPAGE_ENUMPROC` typedef added to winnls.h: the callback's
  prototype comes from the EnumCodePagesProc page ms904723 (twin
  ee491122; "BOOL CALLBACK EnumCodePagesProc(LPTSTR lpCodePageString)";
  "The CODEPAGE_ENUMPROC type defines a pointer to this callback
  function"), and the EnumSystemCodePages parameter is typed
  CODEPAGE_ENUMPROC on both pages.
* `GetUserNameEx` aa517595 (twin ee489621, CE .NET ms902915):
  `BOOLEAN GetUserNameEx(EXTENDED_NAME_FORMAT, LPTSTR, PULONG)`.  OS
  CE .NET 4.0+; Winbase.h; Coredll.lib.  `GetUserNameExW` + macro
  (CE Unicode-only; buffer typed LPTSTR on the page).
* `EXTENDED_NAME_FORMAT` enum added to winbase.h from its CE type page
  aa450831 (twin ee483142): members NameUnknown 0, NameFullyQualifiedDN
  1, NameSamCompatible 2, NameDisplay 3, NameUniqueId 6, NameCanonical
  7, NameUserPrincipal 8, NameCanonicalEx 9, NameServicePrincipal 10
  and the **CE-specific** member `NameWindowsCeLocal = 0x80000001`
  (absent from the desktop form); `*PEXTENDED_NAME_FORMAT` pointer
  typedef per the page.  Values static-asserted in the host TU.

Export surface: coredll 363 -> 364 (GetUserNameExW), coreloc 30 -> 33
(EnumSystemCodePagesW, FoldStringW, LCMapStringW).  gen-doc-def.py
UNICODE_ONLY gained the four base-name -> W entries.  Host + all six
CE targets pass warning-free.



### M35: GWES window / control / dialog style bits (winuser.h)

126 style constants added to winuser.h.  Name lists and the
CE-supported set come verbatim from the official CE 5.0 GWES style
pages (CE 6.0 twins in parentheses):

* Basic Window Styles aa452869 (ee504355): WS_CHILD / WS_CLIPCHILDREN /
  WS_CLIPSIBLINGS / WS_DISABLED / WS_GROUP / WS_POPUP / WS_TABSTOP /
  WS_VISIBLE + extended styles WS_EX_TOPMOST and WS_EX_NOACTIVATE.
* Non-client Area Styles ms911872 (ee506097): WS_BORDER / WS_CAPTION /
  WS_DLGFRAME / WS_HSCROLL / WS_OVERLAPPED / WS_SIZEBOX / WS_SYSMENU /
  WS_VSCROLL + WS_EX_DLGMODALFRAME / WS_EX_CLIENTEDGE / WS_EX_CONTEXTHELP /
  WS_EX_STATICEDGE / WS_EX_WINDOWEDGE / WS_EX_OVERLAPPEDWINDOW
  (documented as WS_EX_CLIENTEDGE | WS_EX_WINDOWEDGE).
* Message Box Styles ms911829 (ee502245): MB_OK / MB_OKCANCEL /
  MB_ABORTRETRYIGNORE / MB_YESNOCANCEL / MB_YESNO / MB_RETRYCANCEL /
  MB_DEFBUTTON1-3 / MB_ICON* (incl. the alias pairs the page lists in
  one cell: ICONERROR=ICONHAND=ICONSTOP, ICONWARNING=ICONEXCLAMATION,
  ICONINFORMATION=ICONASTERISK) / MB_APPLMODAL / MB_SETFOREGROUND /
  MB_TOPMOST.
* Button styles: push aa453604 (ee501475), check ms928572 (ee504569),
  radio aa453607 (ee505912) -> BS_PUSHBUTTON / BS_DEFPUSHBUTTON /
  BS_CHECKBOX / BS_AUTOCHECKBOX / BS_RADIOBUTTON / BS_3STATE /
  BS_AUTO3STATE / BS_AUTORADIOBUTTON / BS_OWNERDRAW / BS_RIGHTBUTTON /
  BS_LEFT/RIGHT/CENTER/TOP/BOTTOM/VCENTER / BS_PUSHLIKE / BS_NOTIFY.
* Edit Control Styles aa452995 (ee504833) -> ES_* (14).
* List Box Styles aa453299 (ee501958) -> LBS_* (incl. LBS_STANDARD =
  LBS_NOTIFY | LBS_SORT as documented).
* Combo Box Styles ms908112 (ee501099) -> CBS_* (10 documented; CE
  does not list CBS_SIMPLE or the owner-draw combo styles).
* Scroll Bar Styles ms932612 (ee505682) -> SBS_HORZ / SBS_VERT.
* Static Control Styles ms940359 (ee505845) -> SS_* (9).
* Dialog styles (from the DLGTEMPLATE aa452960 / DLGTEMPLATEEX aa452961
  pages) -> DS_* (14).

The CE style pages document each style name and meaning but do not
republish its numeric value; Windows CE GWES implements the standard
Win32 style ABI, so the numeric values are the fixed Win32 ABI style
bits (same fixed-ABI policy as the message-identifier block).  Host TU
pins every family's key values and the documented composites
(WS_CAPTION = WS_BORDER|WS_DLGFRAME, LBS_STANDARD, WS_EX_OVERLAPPED-
WINDOW, MB_* aliases, BS_RIGHTBUTTON) with static asserts.

CE-only styles the pages name but whose numeric value is NOT published
anywhere on the CE pages are recorded and left undefined (not
invented): WS_NONAVDONEBUTTON, WS_EX_NOANIMATION, WS_EX_NODRAG,
WS_EX_CAPTIONOKBTN.

### M36: GDI fonts-and-text + MultiMonitor (wingdi.h / windef.h)

Pages harvested (36 leaves, CE 5.0 + CE 6.0 twins; fonts-and-text ids
below, MultiMonitor ids listed per item).  Every CE 5.0 Requirement row
names Coredll.lib; header rows are Windows.h except where noted.

* Fonts-and-text functions (22): `AddFontResource` ms901109 (ee489896,
  CE 2.0+), `CreateFontIndirect` ms901120 (ee489863), `DrawText`
  ms901121 (ee489886), `EnumFontFamilies` ms901123 (ee489908),
  `EnumFontFamiliesEx` ms901124 (ee489844, CE 5.0+; Header wingdi.h),
  `EnumFonts` ms901126 (ee489905), `ExtTextOut` ms901129 (ee489846),
  `GetCharABCWidths` ms901130 (ee489910, CE .NET 4.2+), `GetCharWidth32`
  ms901131 (ee489848, CE .NET 4.0+), `GetFontData` aa520325 (ee489901,
  CE 5.0+), `GetTextAlign` ms901132 (ee489856, CE .NET 4.0+),
  `GetTextCharacterExtra` ms901133 (ee489907, CE 5.0+; Wingdi.h),
  `GetTextColor` ms901134 (ee489912), `GetTextExtentExPoint` ms901135
  (ee489883), `GetTextExtentPoint` ms901136 (ee489897, CE 2.0+),
  `GetTextExtentPoint32` ms901137 (ee489838, CE 2.0+), `GetTextFace`
  ms901138 (ee489915), `GetTextMetrics` ms901139 (ee489911),
  `RemoveFontResource` ms901142 (ee489851), `SetTextAlign` ms901143
  (ee489853, CE .NET 4.0+), `SetTextCharacterExtra` ms901144 (ee489860,
  CE 5.0+; Wingdi.h), `SetTextColor` ms901145 (ee489887, CE .NET 4.0+).
  String-bearing exports are the wide spellings (CE Unicode-only; e.g.
  AddFontResourceW, CreateFontIndirectW, DrawTextW, EnumFontFamiliesW,
  EnumFontFamiliesExW, EnumFontsW, ExtTextOutW, GetCharABCWidthsW,
  GetCharWidth32W, GetTextExtentExPointW, GetTextExtentPointW,
  GetTextExtentPoint32W, GetTextFaceW, GetTextMetricsW,
  RemoveFontResourceW) with the generic-name `#define` mapping.
  TextOut is **not** declared: no CE .NET / CE 5.0 / CE 6.0 catalog
  leaf documents it, so there is no official signature to transcribe.
* DrawText's official page types the last parameter `UNIT uFormat`
  (sic) on both trees; the DT_TABSTOP description defines its tab-stop
  field as bits 8-15 of uFormat, so the parameter is declared `UINT`
  (recorded conflict -- page typo, ABI UINT).  EnumFontFamiliesEx
  dwFlags is "not used; must be 0".  EnumFonts/EnumFontFamilies/Ex
  return `int` (last callback return).
* Structures/types from their CE pages: `LOGFONT` ms901140 (ee489840;
  Header Wingdi.h) with `TCHAR lfFaceName[LF_FACESIZE]`, `ENUMLOGFONT`
  ms901128 (ee489900) with `TCHAR elfFullName[LF_FULLFACESIZE]` +
  `elfStyle[LF_FACESIZE]`, `NEWTEXTMETRIC` ms901141 (ee489904; its
  page types the four glyph members BCHAR), `ABC` ms901108 (ee489865;
  CE .NET 4.2+; `ABC, *PABC`; LPABC is the GetCharABCWidths parameter
  type).  TEXTMETRIC (ms901146, char glyph members) and
  OUTLINETEXTMETRICW already shipped; `LPTEXTMETRIC` alias added.
  `LF_FACESIZE` 32 / `LF_FULLFACESIZE` 64 (fixed Win32 ABI sizes; the
  pages name the constants without values).
* Callbacks: `EnumFontFamProc` ms901125 (ee489849) and `EnumFontsProc`
  ms901127 (ee489833) callback pages; the enumeration function pages
  type the callback parameters `FONTENUMPROC`.  The archive publishes
  no FONTENUMPROC typedef page, so the typedef follows the
  EnumFontFamProc shape the enumeration pages reference
  (`int (CALLBACK *)(const LOGFONT*, const TEXTMETRIC*, DWORD,
  LPARAM)`); EnumFonts' own EnumFontsProc page spells the two font
  pointers without const (recorded in wingdi.h).  Font-type constants
  RASTER_FONTTYPE / DEVICE_FONTTYPE / TRUETYPE_FONTTYPE = 1/2/4.
* Constant families from the value tables (names only on the CE pages;
  fixed Win32 ABI values, host-pinned): DrawText DT_* (18 flags: TOP/
  LEFT/CENTER/RIGHT/VCENTER/BOTTOM/WORDBREAK/SINGLELINE/EXPANDTABS/
  TABSTOP/NOCLIP/EXTERNALLEADING/CALCRECT/NOPREFIX/INTERNAL/END_ELLIPSIS/
  RTLREADING/WORD_ELLIPSIS), ExtTextOut ETO_OPAQUE/CLIPPED/RTLREADING,
  text alignment TA_NOUPDATECP/UPDATECP/LEFT/RIGHT/CENTER/TOP/BOTTOM/
  BASELINE/RTLREADING.  DT_EDITCONTROL / DT_MODIFYSTRING /
  DT_HIDEPREFIX / DT_PREFIXONLY / DT_PATH_ELLIPSIS and TA_VCENTER are
  absent from the CE tables and are left undefined.
* MultiMonitor functions and type (all CE .NET 4.0+, Header Windows.h,
  Coredll.lib): `EnumDisplayMonitors` aa451688 (ee490277, takes
  MONITORENUMPROC), `GetMonitorInfo` aa451738 (ee491682),
  `MonitorEnumProc` ms932091 (ee490724; "A value of type
  MONITORENUMPROC is a pointer to this function" -> MONITORENUMPROC
  typedef `BOOL (CALLBACK *)(HMONITOR, HDC, LPRECT, LPARAM)`),
  `MonitorFromPoint` ms932198 (ee491624), `MonitorFromRect` ms932208
  (ee491307), `MonitorFromWindow` ms932212 (ee490720), and the
  `MONITORINFO` structure ms932213 (ee491429: cbSize / rcMonitor /
  rcWork / dwFlags).  MonitorFrom* dwFlags values and the MONITORINFO
  dwFlags bit MONITORINFOF_PRIMARY (fixed Win32 ABI values 0/1/2 and 1).
  The pages call the display handles HMONITOR; added to windef.h with
  HFONT and LPINT (all fixed-ABI opaque/spelling types used by these
  pages).
* ABI pins in tests/host/tu_compile.c: TEXTMETRIC 56 / LOGFONT 92
  (lfFaceName@28, lfCharSet@23) / ENUMLOGFONT 284 (elfFullName@92) /
  NEWTEXTMETRIC 76 (ntmFlags@60) / ABC 12 / MONITORINFO 40
  (rcMonitor@4, dwFlags@36), plus the DT_*/ETO_*/TA_*/font-type/LF/
  monitor flag values.
* Export surface: coredll 364 → 391 (+27: the 22 font/text functions
  plus EnumDisplayMonitors, GetMonitorInfo, MonitorFromPoint,
  MonitorFromRect, MonitorFromWindow); total 626 → 653.  `TextOut` is
  not exported (no page, no signature).


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
* x86 decoration: **shipped (M37)** — the headers pin every
  component-DLL declaration to the undecorated CE export surface
  (`AKARI_CE_IMPORT`/`AKARI_CE_NAME`), link-verified against
  `llvm-dlltool -m i386 --no-leading-underscore` import libraries.
* End-to-end: **shipped (M37)** — `make e2e WINCECLANG=...
  CRTDIR=...` links wince-crt + Akari API consumer TUs against the
  doc-derived import libraries on all six `arm/i386-pc-wince`
  triples (EXE main/WinMain + DLL; machine/subsystem/imports
  asserted).

### M37: x86 CE undecorated import surface + end-to-end link harness

**Fact (verified import surface, wince-crt audit):** CE component-DLL
export names are undecorated on **x86 as well as ARM** — the CE
import libraries define `__imp_<name>` without a leading underscore.
The shipped headers declared plain C functions, so `i386-pc-wince`
objects referenced the leading-underscore spelling (`_GetTickCount`)
and could not resolve against the undecorated import libraries that
the Akari CRT itself requires.  The x86 CE link path was therefore
broken in the shipped header set (ARM was unaffected: no C symbol
decoration).

**Fix (own design from the verified surface):** `windef.h` defines

* `AKARI_CE_IMPORT` = `__declspec(dllimport)` on x86, empty elsewhere;
* `AKARI_CE_NAME(n)` = `__asm(#n)` on x86, empty elsewhere;

and every one of the 602 component-DLL function declarations across
the shipped headers is written
`AKARI_CE_IMPORT <ret> <name>(...) AKARI_CE_NAME(<name>);`.  On x86
the object then references the import variable `__imp_<name>`
(undecorated spelling, set by the asm pin), which resolves against
`llvm-dlltool -m i386 --no-leading-underscore` import libraries and
yields PE import-table entries with the documented undecorated export
names.  On ARM/Thumb both macros are empty (plain declarations; C
symbols already undecorated).

`__declspec(dllimport)` is required (not only the asm pin) because
export names beginning with an uppercase `L` (`LocalAlloc`,
`LocalFree`, `LocalReAlloc`, `LoadLibraryW`, ...) cannot be
referenced by a bare asm label: the LLVM MC assembler treats
uppercase-`L` labels as local labels and rejects the undefined
reference ("assembler label 'X' can not be undefined" — verified on
clang 22.1.8, `i386-pc-wince*` and `i686-unknown-windows-gnu`; ARM
and x86-64 unaffected).  Through the `__imp_` variable the reference
always carries the `_` prefix and the constraint is avoided; the
verified toolchain's own CRT pins its coredll imports the same way
(wince-crt audit).

**End-to-end harness (shipped):** `tests/e2e/e2e_console.c` (a
`main()` app: GetTickCount / GetSystemInfo / LocalAlloc+LocalFree /
GetModuleHandleW / SetLastError), `tests/e2e/e2e_winmain.c` (a
`WinMain()` app: MessageBoxW from msgbox.dll, the documented CE
WinMain shape, ms914104) and `tests/e2e/e2e_module.c` (a DLL:
DllMain per ms885202 + exported `E2EDemo`).  `make e2e
WINCECLANG=... CRTDIR=...` builds import libraries from all 33
doc-derived defs (armce / i386 `--no-leading-underscore`), builds the
Akari CRT per triple, compiles the consumers `-Werror`, and links
three PE images per triple with `lld-link -wince`
(`/subsystem:windowsce`, entries `mainACRTStartup` /
`WinMainCRTStartup` / `DllMainCRTStartup`, `/export:E2EDemo`), then
asserts with llvm-readobj: machine (ARM 0x1C0 / I386 0x14C), EXE
subsystem `IMAGE_SUBSYSTEM_WINDOWS_CE_GUI` (9), coredll.dll import
names (undecorated), MessageBoxW import, E2EDemo export.  Passes all
six `arm/i386-pc-wince{4.2,5.0,6.0}` targets against the
`LLVM-WinCE` toolchain (CI run 34078339236, head 29d8b882ab, clang
22.1.8) — the import libraries are wince-api's own
doc-derived products, i.e. the sysroot-import-library role the
parity target requires.

Housekeeping: the stray `a.out` (x86-64 host test residue) is
removed from the tree; `*.exe` / `*.dll` / `a.out` are gitignored.

### M38: CopyFileEx unit (winbase.h; closes the M31 deferral)

| Item | Official page (CE 5.0) | OS Versions | Header | Link Library | Notes |
|---|---|---|---|---|---|
| `CopyFileExW` (`#define CopyFileEx`) | `aa517311` (CE 6.0 twin `ee490791`) | Windows CE 5.0 and later | Winbase.h | Coredll.lib | prototype per the CE page (LPCTSTR forms; CE Unicode-only ⇒ export `CopyFileExW`); dwCopyFlags table names three flags; Remarks document ERROR_ACCESS_DENIED on a HIDDEN/READONLY destination and ERROR_REQUEST_ABORTED with delete-on-CANCEL / keep-on-STOP semantics; `#define` mapping + `CopyFileEx -> CopyFileExW` added to gen-doc-def's Unicode-only map |
| `LPPROGRESS_ROUTINE` typedef | shape: Microsoft's official Win32 reference LPPROGRESS_ROUTINE page | — | Winbase.h | — | the CE page names the parameter type only and does not publish the prototype; the official reference page "defines a pointer to this callback function" (nine arguments: four LARGE_INTEGERs, dwStreamNumber, dwCallbackReason, two HANDLEs, lpData; DWORD return).  Single function-pointer typedef (the desktop SDK's double-pointer form is not what the official page states) |
| `PROGRESS_CONTINUE` 0 / `PROGRESS_CANCEL` 1 / `PROGRESS_STOP` 2 | names: `aa517311` Remarks (CANCEL/STOP); values + CONTINUE: official Win32 reference | — | Winbase.h | — | fixed Win32 ABI; PROGRESS_QUIET (desktop-only) recorded-not-defined |
| `COPY_FILE_FAIL_IF_EXISTS` 0x00000001 / `COPY_FILE_RESTARTABLE` 0x00000002 / `COPY_FILE_ALLOW_DECRYPTED_DESTINATION` 0x00000008 | names: `aa517311` Value table; values: official CopyFileExW reference | — | Winbase.h | — | fixed Win32 ABI; the desktop-only COPY_FILE_OPEN_SOURCE_FOR_WRITE / COPY_FILE_COPY_SYMLINK / COPY_FILE_NO_BUFFERING / COPY_FILE_REQUEST_COMPRESSED_TRAFFIC are recorded-not-defined (not named on the CE pages) |

Tooling: `tools/gen-doc-def.py`'s declaration matcher now accepts the
M37 `AKARI_CE_IMPORT` declaration prefix (verified: regeneration
reproduces the committed defs byte-identically before this batch, and
adds exactly `CopyFileExW` after it).

Export surface: coredll 391 -> **392** (total 653 -> **654**).  The
TU static-asserts the three progress values and the three copy flags
and assigns a nine-argument callback to `LPPROGRESS_ROUTINE`
(signature-fit check); the e2e console app links `CopyFileExW` and
`make e2e` asserts it in the import table of all six target images.
### M39: Winsock core unit (winsock2.h + ws2tcpip.h; Ws2.lib)

The core Winsock surface of the official CE 5.0 "Windows Sockets
Reference" book (107 pages, (v=msdn.10); harvest manifests
`tools/manifests/wsock-socket-functions.manifest` (30),
`wsock-ext-functions.manifest` (34), `wsock-structures.manifest`
(35), `wsock-enumerations.manifest` (1), `wsock-socket-options.manifest`
(7)).  The official `ws2 Module` page (ms924522) documents the
module as "Windows Sockets (Winsock) 2.2" with `Ws2.lib` as the link
library; `def/ws2-doc.def` (`LIBRARY ws2.dll`) is generated from the
harvested Requirement rows and declares exactly the 58 names below.

Prototypes: transcribed from the CE 5.0 pages; the CE 5.0 archive
strips whitespace inside some code blocks, so the five pages whose
prototype could not be spaced unambiguously (WSAStartup, WSASocket,
WSASetEvent, WSASetLastError, WSASetService) use the official CE 6.0
twin pages (ee495252, ee493507, ee494648, ee493103, ee493906) — the
documented-twin procedure of M27.  The CE pages print `FAR*` pointer
qualifiers (a Winsock 1.1 / 16-bit relic); Windows CE has a single
32-bit flat address model, so the declarations use plain pointers
(documented design decision).

| Item | Official page (CE 5.0) | OS Versions | Header | Link Library | Notes |
|---|---|---|---|---|---|
| Winsock 1.1 functions: `accept` `bind` `closesocket` `connect` `gethostbyaddr` `gethostbyname` `gethostname` `getpeername` `getsockname` `getsockopt` `htonl` `htons` `inet_addr` `inet_ntoa` `ioctlsocket` `listen` `ntohl` `ntohs` `recv` `recvfrom` `select` `send` `sendto` `sethostname` `setsockopt` `shutdown` `socket` | 27 pages of the Socket Functions book (aa450277, aa450301, ms887908, ms887913, aa450403, aa450404, aa450405, aa450420, ms890293, ms890305, ms890324, ms890325, ms890981, ms890984, ms891129, ms894564, ms895778, ms895783, aa450869, aa450870, aa450882, aa450883, aa450885, aa450918, aa450935, aa450939, aa450958) | Windows CE 1.0 and later | Winsock2.h | Ws2.lib | prototypes verbatim (whitespace compressed by the archive, restored); `select` uses the CE counted-array `fd_set` |
| `getaddrinfo` / `freeaddrinfo` / `getnameinfo` | `aa450395` / `aa450383` / `aa450416` | Windows CE .NET 4.1 and later | **Ws2tcpip.h** (⇒ `include/ws2tcpip.h`) | Ws2.lib | the CE pages name Ws2tcpip.h as the header; the addrinfo structure (aa450282) and AI_* flags live in winsock2.h |
| WSA core functions: `WSAAccept` `WSAAddressToString` `WSACleanup` `WSACloseEvent` `WSAConnect` `WSACreateEvent` `WSAEnumNetworkEvents` `WSAEnumProtocols` `WSAEventSelect` `WSAGetLastError` `WSAGetOverlappedResult` `WSAHtonl` `WSAHtons` `WSAIoctl` `WSAJoinLeaf` `WSANtohl` `WSANtohs` `WSARecv` `WSARecvFrom` `WSAResetEvent` `WSASend` `WSASendTo` `WSASetEvent` `WSASetLastError` `WSASocket` `WSAStartup` `WSAStringToAddress` `WSAWaitForMultipleEvents` | 28 pages of the Windows-Specific Extension Functions book (ms898727..ms900456) | Windows CE .NET 4.0 and later (WSACleanup / WSAGetLastError / WSASetLastError CE 1.0+; WSAIoctl CE 2.0+) | Winsock2.h | Ws2.lib | CE 6.0 twins for the five no-space prototypes (see above); the CE WSAConnect/WSAJoinLeaf pages mark `lpSQOS`/`lpGQOS` "Reserved" ⇒ `QOS` is declared opaque, callers pass NULL; `LPCONDITIONPROC` and the overlapped-completion-routine typedefs are transcribed from the prototypes the CE WSAAccept (ms898727) and WSAIoctl (ms898745) pages print |
| Name-service WSA functions: `WSAEnumNameSpaceProviders` `WSALookupServiceBegin` `WSALookupServiceEnd` `WSALookupServiceNext` `WSANSPIoctl` `WSASetService` (+ the WSAQUERYSET / WSANAMESPACE_INFO / NS_SERVICE_INFO / SERVICE_ADDRESS / SERVICE_ADDRESSES / SERVICE_INFO / SERVICE_TYPE_INFO_ABS / SERVICE_TYPE_VALUE_ABS / CSADDR_INFO / BLOB / WSASERVICECLASSINFO / WSACOMPLETION structures and the WSAECOMPARATOR enumeration) | function pages ms898737 / ms898748 / ms898750 / ms898752 / ms898755 / ms898772; structure pages aa450302, ms887919, ms895775, aa450894, aa450895, aa450902, aa450910, aa450912, ms898732, ms898753, ms898762, ms898768; enumeration page ms898736 | .NET 4.0+ | Winsock2.h | Ws2.lib | **implemented in M41** (see the M41 section); `WSANSPIoctl` (ms898755) remains recorded-not-defined there (no documented link library) |
| Structures: `sockaddr` `sockaddr_in` `in_addr` `in6_addr` `sockaddr_in6` `linger` `hostent` `servent` `protoent` `timeval` `fd_set` `WSADATA` `WSABUF` `WSAOVERLAPPED` `AFPROTOCOLS` `PROTOCOL_INFO` `WSAPROTOCOL_INFO` `WSAPROTOCOLCHAIN` `SOCKET_ADDRESS` `WSANETWORKEVENTS` `TRANSMIT_FILE_BUFFERS` `addrinfo` | 22 structure pages (aa450282, aa450284, aa450370, ms890319, ms890973, ms890972, ms894561, ms896340, ms896341, aa450886, aa450942, aa450946, aa450948, aa450954, aa450970, aa450974, ms898729, ms898735, ms898754, ms898758, ms898760, ms898759) | per page (mostly .NET 4.0+; sockaddr / sockaddr_in CE 1.0+; in6_addr / sockaddr_in6 / addrinfo .NET 4.1+) | Winsock2.h | — | member names/order/types verbatim from the CE pages; the TU static-asserts the 32-bit sizes (sockaddr/sockaddr_in 16, in_addr 4, sockaddr_in6 28, linger 4, hostent 16, servent 16, protoent 12, timeval 8, fd_set 4+4×FD_SETSIZE, WSADATA 400, WSABUF 8, WSAOVERLAPPED 20, AFPROTOCOLS 8, PROTOCOL_INFO 32, WSAPROTOCOLCHAIN 4+4×MAX_PROTOCOL_CHAIN, WSAPROTOCOL_INFO 628, SOCKET_ADDRESS 8, WSANETWORKEVENTS 4+4×FD_MAX_EVENTS, TRANSMIT_FILE_BUFFERS 16, addrinfo 32) |
| `SOCKADDR_STORAGE` | aa450952 | .NET 4.1+ | Winsock2.h | — | **recorded-not-defined**: the page prints `_SS_PAD1SIZE`/`_SS_PAD2SIZE` without values; the 32-bit CE size is not derivable from official pages |
| `FD_ZERO` / `FD_SET` / `FD_CLR` / `FD_ISSET` macros | select page aa450882 (names) + official FD_ macro reference pages (semantics: FD_SET "adds a file descriptor ... If the file descriptor already exist within the set, a duplicate will not be added") | — | Winsock2.h | — | implemented as header macros over the CE counted-array fd_set (documented design decision from the documented semantics) |
| `AF_UNSPEC` 0 / `AF_INET` 2 / `AF_INET6` 23 | names: socket page aa450958 (AF_UNSPEC), sockaddr_in aa450946 ("must be AF_INET"), sockaddr_in6 aa450948 ("must be AF_INET6"); values: official Win32 socket() reference table | — | Winsock2.h | — | AF_IPX / AF_APPLETALK / AF_NETBIOS / AF_IRDA / AF_BTH are named by the official desktop table but not by the CE pages ⇒ recorded-not-defined (the CE socket page's "Af_irda" is a page typo for the IrDA family, documented for the separate IrDA sockets book) |
| `SOCK_STREAM` 1 / `SOCK_DGRAM` 2 / `SOCK_RAW` 3 | names: aa450958; values: official socket() table | — | Winsock2.h | — | SOCK_RDM / SOCK_SEQPACKET (desktop-only, not named on the CE pages) recorded-not-defined |
| `IPPROTO_IP` 0 / `IPPROTO_TCP` 6 / `IPPROTO_UDP` 17 / `IPPROTO_IPV6` 41 | names: aa450958 + the Socket Options book (aa450063/aa450064/aa450065/aa450066); values: IANA protocol numbers registry (TCP 6 / UDP 17 agree with the official socket() table) | — | Winsock2.h | — | |
| `SD_RECEIVE` 0 / `SD_SEND` 1 / `SD_BOTH` 2 | official shutdown() reference table (the CE shutdown page aa450939 documents the how parameter without printing the constant names) | — | Winsock2.h | — | |
| `AI_PASSIVE` 0x01 / `AI_CANONNAME` 0x02 / `AI_NUMERICHOST` 0x04 | names: addrinfo page aa450282; values: official ADDRINFOA reference table | — | Winsock2.h | — | |
| `WSA_FLAG_OVERLAPPED` 0x01 / `WSA_FLAG_MULTIPOINT_C_ROOT` 0x02 / `WSA_FLAG_MULTIPOINT_C_LEAF` 0x04 / `WSA_FLAG_MULTIPOINT_D_ROOT` 0x08 / `WSA_FLAG_MULTIPOINT_D_LEAF` 0x10 / `WSA_FLAG_ACCESS_SYSTEM_SECURITY` 0x40 / `WSA_FLAG_NO_HANDLE_INHERIT` 0x80; `SG_UNCONSTRAINED_GROUP` 0x01 / `SG_CONSTRAINED_GROUP` 0x02 | official WSASocket() reference table; the CE WSASocket page ms898773 documents dwFlags and g | — | Winsock2.h | — | |
| `SO_KEEPALIVE` 0x0008 / `SO_CONDITIONAL_ACCEPT` 0x3002 | names: CE SOL_SOCKET page ms884940; values: official SO_KEEPALIVE / SO_CONDITIONAL_ACCEPT pages ("The constant that represents this socket option is ...") | — | Winsock2.h | — | |
| `WSADESCRIPTION_LEN` 256 | WSADATA page ms898735 ("text (up to 256 characters in length)") | — | Winsock2.h | — | |
| `WSAPROTOCOL_LEN` 255 | WSAPROTOCOL_INFO page ms898760 ("defined to be 255") | — | Winsock2.h | — | |
| `FD_SETSIZE` 64 | fd_set page aa450370 ("defaults to 64") | — | Winsock2.h | — | |
| Winsock 2.2 error codes (all WSAE*/WSA*/WSA_QOS* values, 85 entries) | names referenced by the Return Values tables of the CE pages throughout the book; values: official "Windows Sockets Error Codes" table | — | Winsock2.h | — | the full official table is defined (fixed Winsock 2.2 ABI; the ws2 Module page documents the module as Winsock 2.2) |
| `INVALID_SOCKET` `(SOCKET)(~0u)` | official Socket Data Type page: "the SOCKET type is unsigned" + a handle "may take any value in the range 0 to INVALID_SOCKET–1" (⇒ INVALID_SOCKET is the largest representable unsigned value) | — | Winsock2.h | — | documented derivation |
| `WSAVersion(major, minor)` `MAKEWORD(minor, major)` | CE WSAStartup page ms898774: "The high-order byte specifies the minor version (revision) number; the low-order byte specifies the major version number", documented example `MAKEWORD( 2, 2 )` | — | Winsock2.h | — | |
| `WSASYS_STATUS_LEN` 128 / `FD_MAX_EVENTS` 16 / `MAX_PROTOCOL_CHAIN` 7 | referenced by the CE pages (ms898735 / ms898754 / ms898759) but **no official page prints the values** (verified: CE 5.0, CE .NET, desktop ws2def, MSDN-legacy aa923613) | — | Winsock2.h | — | **(c) flagged design decisions**: the embedding structures (WSADATA, WSANETWORKEVENTS, WSAPROTOCOLCHAIN) must be complete; an on-device Ws2.dll cross-check of these three members is required before relying on them |
| `SOL_SOCKET` / `SOL_IRLMP`; `SO_DEBUG` `SO_ACCEPTCONN` `SO_REUSEADDR` `SO_DONTROUTE` `SO_BROADCAST` `SO_LINGER` `SO_OOBINLINE` `SO_RCVBUF` `SO_SNDBUF` `SO_TYPE` `SO_ERROR` `SO_DONTLINGER` `SO_MAX_MSG_SIZE` `SO_PROTOCOL_INFO` `SO_PROTOCOL_INFOW` `SO_GROUP_ID` `SO_GROUP_PRIORITY` `PVD_CONFIG`; `FD_READ` `FD_WRITE` `FD_OOB` `FD_ACCEPT` `FD_CONNECT` `FD_CLOSE` `FD_ADDRESS_LIST_CHANGE` `FD_ROUTING_INTERFACE_CHANGE`; `MSG_OOB` `MSG_PEEK` `MSG_DONTROUTE` `MSG_PARTIAL`; `FIONBIO` `FIONREAD` (FIOASYNC: "no command that is equivalent to FIOASYNC" — CE WSAIoctl page); `SIO_FLUSH` `SIO_RFCOMM_COMM_PARAMETERS` `SIO_RFCOMM_WAIT_MODEM_STATUS` `SIO_ADDRESS_LIST_CHANGE` `SIO_ROUTING_INTERFACE_CHANGE`; `CF_ACCEPT` `CF_DEFER` `CF_REJECT`; `SOMAXCONN` | names documented by the CE pages (SOL_SOCKET ms884940; WSAEventSelect ms898740; recv/send/WSARecv/WSASend pages; WSAIoctl ms898745; WSAAccept ms898727; listen ms894564) | — | Winsock2.h | — | **recorded-not-defined**: the CE pages name the constants but print no numeric values, and no official page (CE 5.0 / CE .NET / desktop current / desktop legacy) publishes them; defining them from non-official sources is out of rule.  Follow-up: an on-device Ws2.dll readback (setsockopt(SO_TYPE) / WSAEnumNetworkEvents / ioctlsocket(FIONREAD) round-trips) is the compliant way to verify values before adding them |

Tooling: `tools/ce-fetch.py` — (1) the bare-id archive tag now keeps its `v=` prefix
(`v=msdn.10`): Learn serves the previous-versions archive only under the full
`(v=...)` tag, a regression introduced in M22 (`root + "(" + tag + ")"` with
`tag = "msdn.10"`) silently 404s every bare-id URL and the platform now enforces
the tag strictly; (2) transient 404s (Learn rate limiting returns 404, not 429)
are retried with long backoff; (3) error records from a previous run are dropped
at start so a re-fetch replaces them; (4) the signature search key strips the
archive's disambiguation suffixes ("socket (Windows Sockets)").
`tools/gen-doc-def.py` — the declaration matcher additionally parses
`AKARI_CE_IMPORT` lines whose return type is multi-word or a pointer
(`struct hostent *gethostbyaddr`, `unsigned long inet_addr`); regeneration
reproduces all 33 existing defs byte-identically and adds `def/ws2-doc.def`.

Export surface: 33 -> **34** def files; 654 -> **712** name-only lines;
unique names 603 -> **661**.  The TU static-asserts the 22 structure
sizes/offsets and the documented constant values and calls all 58
functions (including the two callback prototypes); the e2e console app
links `socket` / `WSAStartup` / `getaddrinfo` and `make e2e` asserts
`Name: ws2.dll` plus the three symbols in the import table of all six
target images.

### M41: Winsock name service (name spaces) unit (winsock2.h + winnt.h; Ws2.lib)

Closes the M39 name-service deferral: the WSA name-space provider and
service-registration surface of the official CE 5.0 documentation, from
pages already harvested in the M39 manifests (function pages
`tools/manifests/wsock-ext-functions.manifest`, structure pages
`wsock-structures.manifest`, enumeration page
`wsock-enumerations.manifest`).

Prototypes: the CE 5.0 pages ms898737 / ms898748 / ms898750 / ms898752
print their prototypes with the archive's whitespace intact; the
WSASetService prototype is taken from the documented CE 6.0 twin
**ee493906** (the CE 5.0 page ms898772 prints
`INTWSASetService(LPWSAQUERYSETlpqsRegInfo, WSAESETSERVICEOPessOperation,
DWORDdwControlFlags);` unspaced) — the M27 documented-twin procedure,
as recorded for the M39 batch.

| Item | Official page | OS Versions | Header | Notes |
|---|---|---|---|---|
| `WSAEnumNameSpaceProviders` | ms898737 | .NET 4.0+ | Winsock2.h | returns the number of `WSANAMESPACE_INFO` structures copied, or SOCKET_ERROR |
| `WSALookupServiceBegin` / `WSALookupServiceEnd` / `WSALookupServiceNext` | ms898748 / ms898750 / ms898752 | .NET 4.0+ | Winsock2.h | begin/next use `WSAQUERYSET` + a lookup HANDLE; the CE provider ignores `dwControlFlags` (silently); "continue to call this function until it returns WSA_E_NOMORE" — the page prints WSAENOMORE (10102) and WSA_E_NO_MORE (10110), both already defined in M39 |
| `WSASetService` | ms898772 (twin ee493906) | .NET 4.0+ | Winsock2.h | not supported by the default DNS/WINS provider (Nspm.dll) in CE; supported by the PNRP provider (documented notes) |
| `WSANAMESPACE_INFO` | ms898753 | .NET 4.0+ | Winsock2.h | 32-bit size 32 (TU-asserted) |
| `WSAQUERYSET` | ms898762 | .NET 4.0+ | Winsock2.h | 15 members verbatim; 32-bit size 60 (TU-asserted); the page's typedef alias is `PWSAQUERYSETW`, the prototypes name `LPWSAQUERYSET` (both declared, the latter as a documented prototype requirement) |
| `CSADDR_INFO` | ms887919 | .NET 4.0+ | Winsock2.h | 32-bit size 24 (TU-asserted); the CE form carries the two `SOCKET_ADDRESS` members directly (no desktop ADDRESSLIST); `LPCSAADDR_INFO` named by the WSAQUERYSET page |
| `BLOB` | aa450302 | .NET 4.0+ | Winsock2.h | 32-bit size 8 (TU-asserted); "For Bluetooth, this structure defines values in the SDP record" |
| `WSASERVICECLASSINFO` | ms898768 | .NET 4.0+ | Winsock2.h | 32-bit size 16 (TU-asserted); `WSANSCLASSINFOW` layout not published ⇒ opaque pointer type |
| `SERVICE_ADDRESS` / `SERVICE_ADDRESSES` / `SERVICE_INFO` / `SERVICE_TYPE_VALUE_ABS` / `SERVICE_TYPE_INFO_ABS` | aa450894 / aa450895 / aa450902 / aa450912 / aa450910 | .NET 4.0+ | Winsock2.h | 32-bit sizes 24 / 28 / 44 / 20 / 28 (TU-asserted); `LPSERVICE_ADDRESSES` named by the SERVICE_INFO page |
| `NS_SERVICE_INFO` | ms895775 | .NET 4.0+ | Winsock2.h | 32-bit size 48 (TU-asserted) |
| `WSAECOMPARATOR` | ms898736 | .NET 4.0+ | Winsock2.h | the page prints `typedef enum _WSAEcomparator {COMP_EQUAL = 0,COMP_NOTLESS} WSAECOMPARATOR, *PWSAECOMPARATOR;` — COMP_EQUAL 0 / COMP_NOTLESS 1 asserted |
| `WSAESETSERVICEOP` | ms898772 (operation table) | .NET 4.0+ | Winsock2.h | RNRSERVICE_REGISTER / RNRSERVICE_DEREGISTER / RNRSERVICE_DELETE; **(c) flagged**: the page publishes the operation names but no numeric values; the C-enum ordinals (0/1/2) follow the documented listing order |
| `WSAVERSION` | (referenced by ms898762) | — | Winsock2.h | the WSAQUERYSET page documents `LPWSAVERSION lpVersion` ("References desired version number and provides version comparison semantics") but no CE page publishes the layout ⇒ opaque pointer type |
| `LPGUID` | named by ms898762 (`LPGUID lpServiceClassId`) | — | **winnt.h** | pointer typedef next to the M39 GUID definition |
| `WSANSPIoctl` | ms898755 | — | — | **recorded-not-defined**: the CE page documents the function (signature in build/rows.json) but its Requirements section names no link library, so it cannot enter the doc-derived ws2.dll def; not declared |

Constants **recorded-not-defined** (the CE pages publish the names
without numeric values; same policy as the M39 held set):

* `LUP_DEEP` `LUP_NOCONTAINERS` `LUP_NEAREST` `LUP_RES_SERVICE`
  `LUP_RETURN_ALIASES` `LUP_RETURN_NAME` `LUP_RETURN_TYPE`
  `LUP_RETURN_VERSION` `LUP_RETURN_COMMENT` `LUP_RETURN_ADDR`
  `LUP_RETURN_BLOB` `LUP_RETURN_ALL` — the WSALookupServiceBegin
  dwControlFlags table (ms898748)
* `NS_DEFAULT` `NS_DNS` `NS_MS` `NS_NDS` `NS_NETBT` `NS_NIS` `NS_SAP`
  `NS_STDA` `NS_TCPIP_HOSTS` `NS_TCPIP_LOCAL` `NS_WINS` `NS_X500` and
  `NS_ALL` — the name-space tables on ms895775 / aa450912 and the
  WSAQUERYSET page's `dwNameSpace` member (ms898762)
* `SERVICE_ADDRESS_FLAG_RPC_CN` `SERVICE_ADDRESS_FLAG_RPC_DG`
  `SERVICE_ADDRESS_FLAG_RPC_NB` — the SERVICE_ADDRESS dwAddressFlags
  table (aa450894)
* `RESOURCEDISPLAYTYPE_DOMAIN` `RESOURCEDISPLAYTYPE_FILE`
  `RESOURCEDISPLAYTYPE_GENERIC` `RESOURCEDISPLAYTYPE_GROUP`
  `RESOURCEDISPLAYTYPE_SERVER` — the SERVICE_INFO dwDisplayHint table
  (aa450902)
* the WSAQUERYSET `dwOutputFlags` field names no table on any CE page
  (the desktop WSAFL_* set is not an official CE source)

Verification: `make check` GREEN (hostcheck all CE versions; defcheck
`ws2-doc.def` 63 exports); `make crosscheck` GREEN on all six arm/i386
× CE 4.2/5.0/6.0 targets (the 32-bit name-service sizes above);
`make e2e` GREEN — the e2e console app now references the five
name-service functions and the recipe asserts `WSAEnumNameSpaceProviders`
/ `WSALookupServiceBegin` / `WSASetService` in the ws2.dll import table
of all six target images.

Export surface: `def/ws2-doc.def` 58 -> **63** exports (name-only,
`LIBRARY ws2.dll`); the defdoc total is now 34 def files, 717 name-only
lines.

### M42: Winsock SPI (Service Provider Interface) unit (new header ws2spi.h; Ws2.lib)

The "Winsock SPI Reference" section of the official CE 5.0 Windows
Sockets Reference book: the 29 WSP* transport-SPI function pages
(ms898783..ms898915), the 8 NSP* name-space-SPI function pages
(ms895725..ms895766), and the WSPDATA (ms900586) / WSATHREADID
(ms898776) / NSP_Routine (ms895763) structure pages, plus the
"Upcalls Exposed by Ws2.dll" page (ms885421).  Harvest manifests:
`tools/manifests/wsock-spi-functions.manifest` (33) and
`wsock-spi-nsp.manifest` (8).

Every one of the 37 function pages carries the Requirements rows
**Header: Ws2spi.h, Link Library: Ws2.lib, Windows CE .NET 4.0 and
later** — i.e. the official documentation places the entire SPI
surface in the Ws2.lib link group, so all 37 names enter
`def/ws2-doc.def` (the def is documentation-driven; whether an
on-device ws2.dll re-exports each SPI name is the same on-device
verification owed to the whole ws2 set).

| Item | Official page | Notes |
|---|---|---|
| `WSPStartup` `WSPAccept` `WSPAddressToString` `WSPAsyncSelect` `WSPBind` `WSPCleanup` `WSPCloseSocket` `WSPConnect` `WSPDuplicateSocket` `WSPEnumNetworkEvents` `WSPEventSelect` `WSPGetOverlappedResult` `WSPGetPeerName` `WSPGetSockName` `WSPGetSockOpt` `WSPIoctl` `WSPJoinLeaf` `WSPListen` `WSPRecv` `WSPRecvDisconnect` `WSPRecvFrom` `WSPSelect` `WSPSend` `WSPSendDisconnect` `WSPSendTo` `WSPSetSockOpt` `WSPShutdown` `WSPSocket` `WSPStringToAddress` (29) | ms898783..ms898915 | prototypes verbatim (whitespace restored; `FAR` qualifiers dropped per the M39 documented decision); every WSP function takes the documented trailing `LPINT lpErrno` except WSPStartup |
| `NSPCleanup` `NSPGetServiceClassInfo` `NSPInstallServiceClass` `NSPLookupServiceBegin` `NSPLookupServiceEnd` `NSPLookupServiceNext` `NSPRemoveServiceClass` `NSPSetService` (8) | ms895725 / ms895733 / ms895740 / ms895748 / ms895751 / ms895756 / ms895758 / ms895766 | the NSP_Routine page: "Ws2spi.h contains complete prototypes for all the NSP functions this structure points to" |
| `WSPDATA` | ms900586 | 32-bit size 518 (TU-asserted); `WSPDESCRIPTION_LEN` 256 named by the page's own syntax (`szDescription[WSPDESCRIPTION_LEN+1]`, "up to 256 characters in length") |
| `WSATHREADID` | ms898776 | 32-bit size 8 (TU-asserted) |
| `NSP_ROUTINE` | ms895763 | 32-bit size 44 (TU-asserted); 3 DWORDs + 8 function pointers, each documented as returning WSAENOTIMPLEMENTED when unimplemented |
| `WSAPROTOCOL_INFOW` / `LPWSAPROTOCOL_INFOW` / `WSAQUERYSETW` / `LPWSAQUERYSETW` / `LPWSASERVICECLASSINFOW` | named by the SPI prototypes | documented-nominal aliases of the M39/M41 types (Unicode CE: A/W is nominal) |
| `NSPAPI` | ms895756 prototype | empty, exactly like `WSAAPI` (single CE calling convention) |
| `WSPUPCALLTABLE` / `WSPPROC_TABLE` | (referenced by ms898913) | no CE archive page (CE 5.0 / CE .NET / CE 6.0) publishes the layouts ⇒ opaque; documented design decision |
| `WSPStartup` UpcallTable parameter | ms898913 | the page prints a by-value `WSPUPCALLTABLE`; because the layout is unpublished the declaration uses a pointer form — the documented SPI client is Ws2.dll itself, so no user-mode ABI is exposed (flagged design deviation) |
| WPU upcalls: `WPUCloseEvent` `WPUCloseSocketHandle` `WPUCreateEvent` `WPUCreateSocketHandle` `WPUFDIsSet` `WPUQuerySocketHandleContext` `WPUResetEvent` `WPUSetEvent` | ms885421 | **recorded-not-defined**: names + required/optional status documented, but no CE page prints the prototypes |
| `NSPLookupServiceNext` prototype | ms895756 | the archive prints the prototype without a "Syntax" heading and with the WSA-prefixed name (an archive typo: `int NSPAPI WSALookupServiceNext(...)`); declared under the page's title name with the printed parameter list (documented in the header comment) |

Constants **recorded-not-defined** (names published without values):
`LUP_FLUSHPREVIOUS` (the NSPLookupServiceNext page: "Currently only
LUP_FLUSHPREVIOUS is defined as a means to cope with a result set that
is too large") — joins the M41 LUP_* held set.

Verification: `make check` GREEN (hostcheck all CE versions; defcheck
`ws2-doc.def` 100 exports); `make crosscheck` GREEN on all six
arm/i386 × CE 4.2/5.0/6.0 targets (WSPDATA 518 / WSATHREADID 8 /
NSP_ROUTINE 44); `make e2e` GREEN — the e2e console app references
`WSPStartup` / `WSPCleanup` / `NSPSetService` / `NSPLookupServiceNext`
and the recipe asserts `WSPStartup` / `NSPSetService` in the ws2.dll
import table of all six target images.

Export surface: `def/ws2-doc.def` 63 -> **100** exports (name-only,
`LIBRARY ws2.dll`); defdoc total 34 def files, 754 name-only lines,
703 unique names.

## M43 -- TAPI/TSPI (Telephony API, Service Provider Interface) unit

New: `include/tapi.h` (foundation: handle types, the three TSPI callback
prototypes, 26 TAPI structures, 643 constants) and `include/tapicomn.h`
(78 TSPI service-provider entry points).  The TAPI **client** surface
(`lineOpen`, `phoneOpen`, the client functions, ~232 pages) is
deliberately held for a later milestone: this milestone covers the
provider side (TSPI) plus the types/constants the TSPI prototypes
consume, because the TSPI pages are self-contained in the CE 5.0
archive.

Harvest: `tspi-all.manifest` (98 = 81 TSPI function pages + 17 TSPI
message pages) and `tapi-structures-constants.manifest` (98 = 26
structure pages + 66 constant pages incl. one reference page + 3
callback/type pages + LINE_NEWCALL).  All 196 pages fetched from the
official CE 5.0 archive; 1364 pre-existing rows + 196 new rows =
1560 rows in `build/rows.json`.

Every TSPI function page carries the Requirements rows **Header:
Tapicomn.h, Link Library: Coredll.lib, Windows CE 3.0 and later** — so
all 78 declared names enter `def/coredll-doc.def`.

### tapicomn.h -- the 78 declared TSPI entry points

| Item | Official pages | Notes |
|---|---|---|
| TSPI_line* (49 declared) | aa451008 aa451010 aa451012 aa451014 aa451016 aa451018 aa451020 aa451024 aa451025 aa451028 aa451030 aa451034 aa451036 aa451038 aa451040 aa451042 aa451044 aa451046 aa451048 aa451050 aa451052 aa451054 aa451057 aa451056 aa451059 aa451061 aa451063 aa451066 aa451068 aa451069 aa451071 aa451072 aa451073 aa451074 aa451075 aa451076 aa451077 aa451078 aa451080 aa451082 aa451086 aa451088 aa451089 aa451090 aa451091 aa451092 aa451093 aa451094 aa451095 | prototypes transcribed; whitespace restored mechanically; `FAR` dropped; the two glued `const` parameter forms on the archive (`LPLINECALLPARAMSconstlpCallParams` et al.) restored to `LPLINECALLPARAMS const lpCallParams` |
| TSPI_phone* (21) | aa451096 aa451097 aa451098 aa451099 aa451100 aa451101 aa451102 aa451104 aa451103 aa451105 aa451106 aa451107 aa451108 aa451109 aa451120 aa451121 aa451122 aa451123 aa451124 aa451125 aa451126 | same; `TSPI_phoneClose` prints a `long` return |
| TSPI_provider* (8) | aa451127 aa451128 aa451129 aa451130 aa451131 aa451132 aa451133 aa451134 | `TSPI_providerInit` takes the `ASYNC_COMPLETION` completion callback + `LPDWORD lpdwTSPIOptions`; `TSPI_providerEnumDevices` takes the `LINEEVENT`/`PHONEEVENT` create callbacks; install/remove take `HWND` + `DWORD dwPermanentProviderID` |
| `TSPI_lineForward` | aa451032 | **recorded-not-defined**: the prototype's element type `LINEFORWARD` (the array element of LINEFORWARDLIST) has no CE page publishing its layout |
| `TSPI_lineConditionalMediaDetection` | aa451022 | **recorded-not-defined**: the archive page prints a corrupted prototype (member names mangled); not transcribed |
| `TSPI_lineSetCurrentLocation` | aa451084 | **recorded-not-defined**: the page says "This function is obsolete" and prints no prototype |
| 17 TSPI message pages (LINE_ADDRESSSTATE ... PHONE_STATE, "(TSPI)") | ms893374, ms893651, ms894004, ms894120, ms894127, ms894133, ms894157, ms894381, ms894393, ms894399, ms894457, ms895909, ms895914, ms895917, ms895920, ms895947, ms896240 | the dwMsg callback-message **values** are published without numbers (only names + parameter meanings): recorded-not-defined; joins the held set |

### tapi.h -- foundation

| Item | Official pages | Notes |
|---|---|---|
| Handles: `HTAPILINE` `HTAPICALL` `HTAPIPHONE` `HDRVLINE` `HDRVCALL` `HDRVPHONE` `HLINE` `HPROVIDER` `DRV_REQUESTID` | named by the TSPI/callback pages | documented as HANDLE/DWORD carriers (note (d) in the header) |
| `LINEEVENT` | ms894144 | `void (CALLBACK*)(HTAPILINE, HTAPICALL, DWORD, DWORD, DWORD, DWORD)` — "supplied to the service provider as a parameter to the TSPI_lineOpen function" |
| `PHONEEVENT` | ms895922 | `void (CALLBACK*)(HTAPIPHONE, DWORD, DWORD, DWORD, DWORD)` — same for TSPI_phoneOpen |
| `ASYNC_COMPLETION` | aa450289 | `void (CALLBACK*)(DRV_REQUESTID, LONG)` — same for TSPI_providerInit |
| 26 structures | see below | sizes TU-asserted (32-bit) |
| 643 constants (63 pages) | see below | no cross-page conflicts; per-page comment in the header |
| `LPHICON` | the GetIcon pairs | `typedef HICON *LPHICON` (windef.h HICON) |
| `TAPIAPI` / `TSPIAPI` | all pages | empty, exactly like WINAPI |

Structures (page, 32-bit size, TU-asserted):

| Structure | Page | Size | Structure | Page | Size |
|---|---|---|---|---|---|
| LINEDIALPARAMS | ms894138 | 16 | LINECALLINFO | ms893611 | 296 |
| LINEEXTENSIONID | ms894145 | 16 | LINEADDRESSCAPS | ms893350 | 228 |
| PHONEEXTENSIONID | ms895923 | 16 | LINEDEVCAPS | ms894130 | 252 |
| LINEGENERATETONE | ms894155 | 16 | LINEDEVSTATUS | ms894135 | 76 |
| LINECALLTREATMENTENTRY | ms894117 | 12 | LINEINITIALIZEEXPARAMS | ms894378 | 24 |
| LINECALLLIST | ms893660 | 24 | PHONEINITIALIZEEXPARAMS | ms895939 | 24 |
| LINEPROVIDERENTRY | ms894431 | 12 | PHONECAPS | ms895911 | 180 |
| LINEPROVIDERLIST | ms894433 | 24 | PHONESTATUS | ms896250 | 104 |
| LINEMESSAGE | ms894390 | 24 | LINELOCATIONENTRY | ms894383 | 68 |
| PHONEMESSAGE | ms895941 | 24 | LINETRANSLATECAPS | ms894541 | 44 |
| VARSTRING | ms898569 | 24 | LINETRANSLATEOUTPUT | ms894550 | 40 |
| LINECALLPARAMS | ms893776 | 180 | LINECALLSTATUS | ms894104 | 56 |
| LINEADDRESSSTATUS | ms893382 | 64 | | | |

Documented restorations: the LINEDEVCAPS page prints
`dwDevSpecificOffset` and `dwLineFeatures` with no separator (semicolon
restored); the PHONECAPS page declares the structure without a pointer
alias (LPPHONECAPS added, named by TSPI_phoneGetDevCaps); the
LINEDEVCAPS / LINECALLPARAMS / LINECALLINFO pages embed
`LINEDIALPARAMS` by value; the two INITIALIZEEXPARAMS structs carry the
documented `union { HANDLE hEvent; HANDLE hCompletionPort; } Handles`
member + `dwCompletionKey`; LINEMESSAGE uses `DWORD_PTR` for the four
callback/parameter words while PHONEMESSAGE is all-DWORD (as printed).

Recorded-not-defined structure: `LINEFORWARDLIST` (ms894148) — its
element type `LINEFORWARD` is named but never laid out (drives the
TSPI_lineForward exclusion above).

Constants: 63 of the 65 constant pages publish values (643
name/value pairs, zero cross-page conflicts): LINEADDRCAPFLAGS (29),
LINECALLINFOSTATE (31), LINEDEVSTAT, LINEDISCONNECTMODE (20),
LINEFORWARDMODE (18), LINESTATE (24), LINETERMINALMODE, LINEERR
(85, e.g. `LINEERR_ADDRESSBLOCKED` 0x80000053), PHONEBUTTONFUNCTION
(47), PHONEERR (34, e.g. `PHONEERR_ALLOCATED` 0x90000001), PHONESTATE
and the rest.  No-value pages: `LINECONFIGDATA`, `LINELOCATIONOPTION`
(names + meanings only) and the `The LINECALLINFO Data Structure`
reference page (ms885284, prose description of the LINECALLINFO members
already declared from ms893611).

`lineCallbackFunc` (ms893424) / `phoneCallbackFunc` (ms895910) are the
**client**-side TAPI callbacks: recorded, not declared — they belong to
the held TAPI client milestone.

### Verification

* `make check` GREEN: hostcheck (headers + TU, warning-free under
  `_WIN32_WCE` 0x420/0x500/0x600), defcheck `coredll-doc.def` **470**
  exports.
* `make crosscheck` GREEN on all six arm/i386 × CE 4.2/5.0/6.0 targets;
  all 25 32-bit structure size asserts hold.
* `make e2e` GREEN: the e2e console app references `TSPI_lineOpen` /
  `TSPI_phoneGetDevCaps`; the recipe asserts `Symbol: TSPI_lineOpen`
  and `Symbol: TSPI_phoneGetDevCaps` in the coredll.dll import table of
  all six target images.

Export surface: `def/coredll-doc.def` 392 -> **470** exports
(+78 TSPI; name-only, `LIBRARY coredll.dll`).

## M44 -- COM/OLE/Storage/Automation unit (new umbrella header objbase.h; Ole32.lib + Oleaut32.lib)

The 635 corpus pages whose Requirements line names one of the
COM-family headers (Objbase.h 87, Objidl.h/Objidl.idl 131,
Oaidl.h/Oaidl.idl 141, Wtypes.h 6, Unknwn.h/Unknwn.idl 3,
Oleauto.h 227, Ocidl.h/Ocidl.idl 40) are implemented as a single
umbrella header `include/objbase.h`, mirroring how the CE SDK's
`<Objbase.h>` itself includes Objidl.h, Oaidl.h, Wtypes.h and
Unknwn.h (Oleauto.h/Ocidl.h pages resolve here too; every declaration
notes the header its page names).

### Functions (307 declared)

* **ole32.dll (84)**: the Co* activation/marshaling/API-set surface
  (CoInitialize[Ex], CoCreateInstance[Ex], CoCreateGuid,
  CoGetClassObject, CoRegisterClassObject, CoMarshal*/Unmarshal*,
  CoTaskMem*, CoGetMalloc, ...), the moniker factory/operation set
  (Create{Anti,Class,File,Item,Pointer}Moniker,
  CreateGenericComposite, MkParseDisplayName, BindMoniker,
  MonikerCommonPrefixWith, MonikerRelativePathTo,
  GetRunningObjectTable), the storage set (StgCreateDocfile[OnILockBytes],
  StgOpenStorage[OnILockBytes], GetClassFile), the GUID-string set
  (StringFromCLSID/IID/GUID2, CLSIDFromString/FromProgID,
  ProgIDFromCLSID, IIDFromString), DllGetClassObject,
  UpdateDCOMSettings, CoRegisterPSClsid.
* **oleaut32.dll (223)**: the full Automation runtime --
  SysAllocString[Llen]/SysReAllocString[Llen]/SysFreeString/
  SysString(Len|ByteLen), SafeArrayCreate[Vector][Data][Descriptor]/
  SafeArrayDestroy/SafeArrayAccessData/SafeArrayGet*/Put*/Lock/Unlock/
  Redim/Copy, the complete Var*From* conversion matrix (bool/cy/date/
  dec/i1/i2/i4/r4/r8/str/ui1/ui2/ui4 x the corresponding sources,
  ~180 pages), VariantInit/Copy/CopyInd/Clear/ChangeType[Ex],
  SystemTimeToVariantTime/VariantTimeToSystemTime, VectorFromBstr/
  BstrFromVector, VarParseNumFromStr/VarNumFromParseNum,
  CreateErrorInfo/Set-GetErrorInfo, DispGetIDsOfNames/DispGetParam/
  DispInvoke, the type-library API (LoadTypeLib/LoadRegTypeLib/
  RegisterTypeLib/UnRegisterTypeLib/CreateTypeLib2).

Recorded-not-declared: `CoBuildVersion` (ms886213; deprecated, the CE
page publishes no prototype, CE 5.0+ only). `UnRegisterTypeLib`
(ms891303) is declared (its prototype is published) but its page's
Link Library field prints "None" (archive artifact), so it is not in
`def/oleaut32-doc.def`.

### Types (64 struct/union/enum definitions + scalars)

* Automation: VARTYPE/VARENUM (VT_* through VT_UI1=17 + VT_ARRAY/
  VT_BYREF/VT_RESERVED), VARIANT/VARIANTARG (anonymous union, 26
  members), SAFEARRAY/SAFEARRAYBOUND (+ FADF_*), DISPPARAMS, EXCEPINFO,
  CURRENCY/CY, PARAMDATA/METHODDATA.
* Type library: TLIBATTR, TYPEDESC, ARRAYDESC, IDLDESC, PARAMDESC,
  ELEMDESC, FUNCDESC, VARDESC, INTERFACEINFO, BINDPTR, TYPEATTR,
  CUSTDATA/CUSTDATAITEM + enums TYPEKIND/VARKIND/CALLCONV/FUNCKIND/
  INVOKEKIND/FUNCFLAGS/ADVF/TYPEFLAGS/DATADIR/DESCKIND.
* OLE: COSERVERINFO, COAUTHINFO, COAUTHIDENTITY,
  SOLE_AUTHENTICATION_SERVICE, MULTI_QI, DVTARGETDEVICE, FORMATETC,
  STGMEDIUM, STATSTG, BIND_OPTS/BIND_OPTS2, BINDINFO, CLSCTX,
  DVASPECT, TYMED, STGC, STGM (18 values), MKSYS, MKRREDUCE,
  BIND_FLAGS, SYSKIND.
* Ocidl.h: LICINFO, CONNECTDATA, CONTROLINFO, DVASPECTINFO,
  DVEXTENTINFO, DVASPECT2, DVASPECTINFOFLAG, DVEXTENTMODE, HITRESULT,
  VIEWSTATUS, SIZEL.
* Scalars: OLECHAR/LPOLESTR/LPCOLESTR/BSTR (ms886145), HRESULT,
  CLSID/IID/LPIID/LPCLSID + REFGUID/REFCLSID/REFIID (GUID itself is in
  winnt.h), DISPID (ms886967)/MEMBERID (ms890763)/HREFTYPE (ms886994),
  VARIANT_BOOL/DATE/SCODE, LCID (windef.h; page ms890741 consistent).
* Opaque (named by documented prototypes, no corpus page): SNB,
  PARAMDESCEX, SOLE_AUTHENTICATION_LIST, RPC_AUTHZ_HANDLE,
  RPC_AUTH_IDENTITY_HANDLE, SECURITY_DESCRIPTOR (declared in its
  documented Win32 layout -- length/descriptor/inherit -- because
  BINDINFO embeds it by value and winbase.h only forward-declares),
  DECIMAL, UDATE, NUMPARSE, HENHMETAFILE, HMETAFILEPICT.

### Interfaces (50 opaque, 258 documented method pages)

IUnknown, IClassFactory(2), IBindCtx, IConnectionPoint(Container),
ICreateErrorInfo, ICreateTypeInfo(2), ICreateTypeLib(2), IDataObject,
IDispatch, IErrorInfo, IErrorlog, IExternalConnection,
IEnum{ConnectionPoints,Connections,FORMATETC,Moniker,STATDATA,STATSTG,
String,Unknown,VARIANT}, IGlobalInterfaceTable, IAdviseSink,
IFillLockBytes, ILockBytes, IMalloc, IMallocSpy, IMarshal,
IMessageFilter, IMoniker, IMultiQI, IOleItemContainer, IPersistFile,
IPersistPropertyBag, IPropertyBag, IRunningObjectTable, IStorage,
IStream, ISurrogate, ITypeComp, ITypeInfo(2), ITypeLib(2),
IViewObjectEx. Vtable layouts are not published by the CE corpus: each
interface is an opaque pointer type and its documented methods
(signatures + page ids) are listed in a header comment. Pointer
aliases: the generic LPX per interface plus the documented short
spellings (LPUNKNOWN, LPMONIKER, LPBC, LPSTREAM, LPMALLOC, LPMARSHAL,
LPMALLOCSPY, LPMESSAGEFILTER, LPRUNNINGOBJECTTABLE).

### Documented print artifacts fixed (noted at each site)

* IDLDESC missing closing brace; ELEMDESC alias printed "ELEMDES";
  VARDESC missing semicolon; TYPEDESC first union member printed twice
  with garbage prefixes ("ESC"/"tagTYPEDSC"); VARTYPE flag tail
  printed without separators.
* LoadRegTypeLib/UnRegisterTypeLib: comma missing between
  wVerMajor/wVerMinor; SafeArrayCreate "SAFEARRRAYBOUND";
  CoTaskMemFree "void pv" -> LPVOID pv; SystemTimeToVariantTime /
  DispInvoke parameters printed by value but documented as pointers.
* Page-title/prototype mismatches resolved to the documented title:
  ms891328 (prints VarCyFromUI1/BSTR 4-param form -> VarBstrFromUI1),
  ms891629 (prints VarDecFromUI1(ULONG) -> VarDecFromUI4), ms891663
  (prints VarI4FromUI1(short) -> VarI4FromI2), ms891846 (titled
  VarR8FromI4, prints ULONG -> VarR8FromUI4), CoRegisterPSCLsid ->
  CoRegisterPSClsid (the export name per the page title).
* Duplicate page ms891659 (VarI4FromUI1 with a wrong DATE parameter)
  dropped in favour of ms891668.
* SafeArrayGetDim/SafeArrayGetElemsize: printed return type HRESULT;
  each page's own "Return Values" text says the dimension count /
  element size is returned -> declared ULONG.
* StringFromGUID2: printed form lacks a return type; "Return Values"
  says the character count is returned -> int.
* CURRENTY->CURRENCY, DOUBLE->char/double, Ulong->ULONG,
  ItypeInfo->ITypeInfo, IerrorInfo->IErrorInfo, VarR8FromDips->
  VarR8FromDisp, IMoniker_com_Imoniker->IMoniker, HRESUTL->HRESULT,
  LPOlESTR->LPOLESTR.
* FAR/FARSTRUCT/HUGEP pointer qualifiers dropped (no effect on the
  32-bit flat CE address space); UNION_NAME(u) expands to the member
  u; MIDL attributes on the CE 5.0 STGMEDIUM page stripped; the
  STGMEDIUM alias "uSTGMEDIUM" (ms891275) is a typo, STGMEDIUM
  (ms928939 spelling) is used.

### Recorded-not-defined (no values published in the CE corpus)

S_OK/S_FALSE/E_* result constants, COINIT_MULTITHREADED/APARTMENTTHREADED,
REGCLS_* (referenced by CoRegisterClassObject), the special DISPID_*
names (DISPID_VALUE et al.), MSHLFLAGS; the REGCLS/COINIT/MSHL name
sets are referenced by the pages but their values are not published.

### 32-bit structure sizes (asserted in tests/host/tu_compile.c)

| Structure | Size | Structure | Size |
|---|---|---|---|
| GUID/CLSID/IID | 16 | SAFEARRAYBOUND | 8 |
| CY/CURRENCY | 8 | SAFEARRAY | 24 |
| VARIANT(VARIANTARG) | 16 | DISPPARAMS | 16 |
| EXCEPINFO | 32 | PARAMDATA | 8 |
| METHODDATA | 28 | TLIBATTR | 32 |
| TYPEDESC | 8 | ARRAYDESC | 20 |
| IDLDESC | 8 | PARAMDESC | 8 |
| ELEMDESC | 16 | FUNCDESC | 52 |
| VARDESC | 36 | INTERFACEINFO | 24 |
| BINDPTR | 4 | TYPEATTR | 76 |
| CUSTDATAITEM | 32 | CUSTDATA | 8 |
| COAUTHIDENTITY | 28 | COAUTHINFO | 28 |
| COSERVERINFO | 16 | SOLE_AUTH_SERVICE | 16 |
| MULTI_QI | 12 | DVTARGETDEVICE | 16 |
| FORMATETC | 20 | STGMEDIUM | 12 |
| STATSTG | 72 | BIND_OPTS | 16 |
| BIND_OPTS2 | 32 | BINDINFO | 84 |
| LICINFO | 12 | CONNECTDATA | 8 |
| CONTROLINFO | 16 | DVASPECTINFO | 8 |
| DVEXTENTINFO | 16 | SIZEL | 8 |
| SECURITY_ATTRIBUTES | 12 | | |

### Verification

* `make check` GREEN: hostcheck (headers + TU, warning-free under
  `_WIN32_WCE` 0x420/0x500/0x600), defcheck with
  `ole32-doc.def` **84** and `oleaut32-doc.def` **222** exports
  (coredll-doc.def still **470**).
* `make crosscheck` GREEN on all six arm/i386 × CE 4.2/5.0/6.0
  targets; all 48 32-bit COM structure size asserts hold.
* `make e2e` GREEN: the e2e console app calls CoCreateGuid /
  CoCreateInstanceEx / CLSIDFromString / CreateFileMoniker /
  StgCreateDocfile (ole32.dll) and SysAllocString / SysFreeString /
  VariantInit / VariantClear / SafeArrayDestroy / LoadTypeLib
  (oleaut32.dll); the recipe asserts `Name: ole32.dll`,
  `Symbol: CoCreateGuid`, `Symbol: CreateFileMoniker`,
  `Symbol: StgCreateDocfile`, `Name: oleaut32.dll`,
  `Symbol: SysAllocString`, `Symbol: VariantInit`, `Symbol: LoadTypeLib`
  in the import tables of all six target images.

Export surface: new `def/ole32-doc.def` 84 exports (name-only,
`LIBRARY ole32.dll`) and `def/oleaut32-doc.def` 222 exports
(`LIBRARY oleaut32.dll`). `tools/gen-doc-def.py` gained a no-sole-link
rule: co-listed library tokens with no sole-link exports (Uuid.lib,
co-listed on 238 COM pages) get no def file.

## M45 -- TAPI client runtime unit (tapi.h; closes the M43 client hold)

The TAPI **client** surface of the official CE 5.0 "Telephony API"
book: `tools/manifests/tapi-client-functions.manifest` (91 leaves).
89 pages were harvested in this session (the two callback-shape pages
ms893424 lineCallbackFunc / ms895910 phoneCallbackFunc were already
in rows.json via the M43 structures/constants manifest).  Every
function page carries the Requirements rows **Header: Tapi.h, Link
Library: Coredll.lib**; the per-page OS Versions are noted in the
header comments (most CE 1.0+; lineGetMessage / lineInitializeEx /
lineSendUserUserInfo and all phone* functions CE 3.0+; lineAddProvider
CE 2.0+; lineSetCurrentLocation CE 2.10+; lineSetTollList CE .NET
4.0+).

### Prototypes

70 of the 89 pages print their prototypes with whitespace intact in
the archive; 19 print them glued (the archive's code-block spacing
strip).  The glued prototypes were restored mechanically against the
documented tapi.h types (the same documented restoration as the M43
TSPI batch): ms893340 lineAddProvider, ms894118 lineClose, ms894123
lineConfigDialogEdit, ms894128 lineDeallocateCall, ms894142 lineDrop,
ms894156 lineGenerateTone, ms894165 lineGetDevCaps, ms894331
lineGetID, ms894361 lineGetTranslateCaps, ms894369 lineInitialize,
ms894387 lineMakeCall, ms894402 lineNegotiateAPIVersion, ms894420
lineOpen, ms894475 lineSetCallPrivilege, ms894481
lineSetCurrentLocation, ms894488 lineSetDevConfig, ms894500
lineSetStatusMessages, ms894517 lineShutdown, ms894539
lineTranslateAddress, ms894543 lineTranslateDialog, ms895932
phoneGetStatus.  Restorations verified against the raw archive prints
(`LPVOIDconstlpDeviceConfigIn` -> `LPVOID const lpDeviceConfigIn`,
`LPLINECALLPARAMSconstlpCallParams` -> `LPLINECALLPARAMS const
lpCallParams`, `DWORD_PTRdwCallbackInstance` -> `DWORD_PTR
dwCallbackInstance`, etc.).  The pages print `LONG WINAPI`; WINAPI is
empty for CE and the declarations follow the repository's
single-convention style.

### New types (tapi.h)

| Item | Basis | Notes |
|---|---|---|
| `HLINEAPP` / `HCALL` / `HPHONE` / `HPHONEAPP` | client function pages: "Handle to the application's registration with TAPI." (lineOpen ms894420 hLineApp, phoneOpen ms895944 hPhoneApp); "Pointer to an HCALL handle." (lineMakeCall ms894387 lphCall); "Pointer to an HPHONE handle that identifies the open phone device." (phoneOpen ms895944 lphPhone); "Pointer to a location that is filled with the application's usage handle for TAPI." (lineInitialize ms894369 lphLineApp) | opaque object handles documented without a carrier type -> `typedef HANDLE`, same documented design decision as note (d) |
| `LPHLINE` / `LPHLINEAPP` / `LPHCALL` / `LPHPHONE` / `LPHPHONEAPP` | named by the prototypes above | pointer aliases |
| `LINECALLBACK` | lineCallbackFunc page ms893424: printed shape `VOID FAR PASCAL lineCallbackFunc(DWORD hDevice, DWORD dwMsg, DWORD dwCallbackInstance, DWORD dwParam1, DWORD dwParam2, DWORD dwParam3)`; the page's hDevice note ("Applications must use the DWORD type for this parameter...") | `typedef void (CALLBACK *)(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD)` |
| `PHONECALLBACK` | phoneCallbackFunc page ms895910: same placeholder model, first parameter printed `HANDLE hDevice` | `typedef void (CALLBACK *)(HANDLE, DWORD, DWORD, DWORD, DWORD, DWORD)` |
| `LPLINEFORWARDLIST` | LINEFORWARDLIST page ms894148 prints the typedef (dwTotalSize / dwNumEntries / `LINEFORWARD ForwardList[1]`, CE 3.0+); the LINEFORWARD element has no layout page in any official CE tree (CE 5.0 / CE .NET / CE 6.0 catalogs verified) | pointer to an incomplete tag (documented design decision; the structure cannot be completed in C from official information) |

### M43 hold closed: TSPI_lineForward

`TSPI_lineForward` (aa451032) was recorded-not-declared in M43
because its `LPLINEFORWARDLIST` parameter needed the LINEFORWARD
element layout.  With the opaque pointer declaration above the
prototype needs nothing more, so it is declared in tapicomn.h in M45
(restored from the glued archive print against the documented types).
The client `lineForward` (ms894147) is declared the same way.  This
completes the TSPI surface to 79 declared entry points.

### Functions declared (89: 66 line* + 23 phone*)

lineAccept `ms893325`, lineAddProvider `ms893340`, lineAddToConference
`ms893390`, lineAnswer `ms893395`, lineBlindTransfer `ms893412`,
lineClose `ms894118`, lineCompleteTransfer `ms894122`,
lineConfigDialogEdit `ms894123`, lineDeallocateCall `ms894128`,
lineDevSpecific `ms894131`, lineDial `ms894137`, lineDrop `ms894142`,
lineForward `ms894147`, lineGenerateDigits `ms894152`, lineGenerateTone
`ms894156`, lineGetAddressCaps `ms894158`, lineGetAddressID `ms894159`,
lineGetAddressStatus `ms894160`, lineGetAppPriority `ms894161`,
lineGetCallInfo `ms894162`, lineGetCallStatus `ms894163`,
lineGetConfRelatedCalls `ms894164`, lineGetDevCaps `ms894165`,
lineGetDevConfig `ms894177`, lineGetIcon `ms894313`, lineGetID
`ms894331`, lineGetLineDevStatus `ms894336`, lineGetMessage `ms894338`,
lineGetNewCalls `ms894341`, lineGetNumRings `ms894350`,
lineGetProviderList `ms894352`, lineGetStatusMessages `ms894356`,
lineGetTranslateCaps `ms894361`, lineHandoff `ms894363`, lineHold
`ms894368`, lineInitialize `ms894369`, lineInitializeEx `ms894370`,
lineMakeCall `ms894387`, lineMonitorDigits `ms894391`, lineMonitorMedia
`ms894395`, lineNegotiateAPIVersion `ms894402`, lineNegotiateExtVersion
`ms894404`, lineOpen `ms894420`, linePickup `ms894423`,
linePrepareAddToConference `ms894429`, lineRedirect `ms894435`,
lineReleaseUserUserInfo `ms894438`, lineRemoveFromConference
`ms894452`, lineSendUserUserInfo `ms894466`, lineSetAppPriority
`ms894470`, lineSetCallParams `ms894473`, lineSetCallPrivilege
`ms894475`, lineSetCurrentLocation `ms894481`, lineSetDevConfig
`ms894488`, lineSetMediaMode `ms894491`, lineSetNumRings `ms894494`,
lineSetStatusMessages `ms894500`, lineSetTerminal `ms894505`,
lineSetTollList `ms894509`, lineSetupConference `ms894512`,
lineSetupTransfer `ms894514`, lineShutdown `ms894517`, lineSwapHold
`ms894522`, lineTranslateAddress `ms894539`, lineTranslateDialog
`ms894543`, lineUnhold `ms894557`; phoneClose `ms895912`,
phoneConfigDialog `ms895915`, phoneDevSpecific `ms895918`,
phoneGetDevCaps `ms895925`, phoneGetGain `ms895926`, phoneGetHookSwitch
`ms895927`, phoneGetIcon `ms895928`, phoneGetID `ms895929`,
phoneGetMessage `ms895930`, phoneGetRing `ms895931`, phoneGetStatus
`ms895932`, phoneGetStatusMessages `ms895933`, phoneGetVolume
`ms895934`, phoneInitializeEx `ms895937`, phoneNegotiateAPIVersion
`ms895942`, phoneNegotiateExtVersion `ms895943`, phoneOpen `ms895944`,
phoneSetGain `ms896179`, phoneSetHookSwitch `ms896185`, phoneSetRing
`ms896190`, phoneSetStatusMessages `ms896197`, phoneSetVolume
`ms896201`, phoneShutdown `ms896208`.

Documented parameter-form notes kept verbatim: lineDrop /
lineSetDevConfig print `LPCTSTR` (CE Unicode-only -> the wide string);
linePickup / lineRedirect / lineHandoff / lineSetAppPriority /
lineGetDevConfig / phoneConfigDialog print narrow-string parameters
(`LPCSTR`) exactly as on the pages; phoneOpen prints `DWORD_PTR
dwCallbackInstance`; lineGenerateTone / lineMakeCall / lineOpen /
lineForward / lineSetupConference / lineSetupTransfer /
linePrepareAddToConference / lineConfigDialogEdit / lineSetDevConfig
carry the page-printed `const` qualifiers.

### Recorded-not-declared

* lineCallbackFunc / phoneCallbackFunc (ms893424 / ms895910) are
  application-supplied callback *shapes*, not exports: implemented as
  the LINECALLBACK / PHONECALLBACK typedefs above.  Their pages'
  Coredll.lib rows therefore do not enter the def (the matcher keys on
  header-declared export names).
* All M43 recorded-not-defined items stand except TSPI_lineForward
  (closed above): TSPI_lineSetCurrentLocation ("obsolete", no
  prototype), TSPI_lineConditionalMediaDetection (corrupted archive
  print), the LINE_*/PHONE_* TSPI callback-message values (names
  without numbers).

### Verification

* `make check` GREEN: hostcheck (headers + TU, warning-free under
  `_WIN32_WCE` 0x420/0x500/0x600; the TU exercises all 89 client
  functions, both callback shapes and TSPI_lineForward), defcheck
  `coredll-doc.def` **560** exports.
* `make crosscheck` GREEN on all six arm/i386 × CE 4.2/5.0/6.0
  targets.
* `make e2e` GREEN: the e2e console app references lineInitializeEx /
  lineNegotiateAPIVersion / lineOpen / lineMakeCall / lineForward /
  lineDrop / lineClose / lineShutdown / phoneOpen / phoneGetStatus /
  phoneClose / TSPI_lineForward; the recipe asserts
  `Symbol: lineInitializeEx`, `Symbol: lineOpen`, `Symbol: lineForward`,
  `Symbol: phoneOpen`, `Symbol: TSPI_lineForward` in the coredll.dll
  import table of all six target images (x86 imports verified
  undecorated).

Export surface: `def/coredll-doc.def` 470 -> **560** exports (+89
client + TSPI_lineForward; name-only, `LIBRARY coredll.dll`).  rows
1560 -> 1649.  Corpus pages5 1479 -> 1568.

## M46 -- Input Method Manager (IMM) unit (new header imm.h; Coreimm.lib)

The official CE 5.0 "Input Method Manager" reference set harvested in
this session: `tools/manifests/imm-reference.manifest` (152 leaves:
56 function-shaped pages, 12 structure pages, the EnumRegisterWordProc
callback page, and 84 constant/message pages).  rows 1649 -> 1801;
corpus pages5 1568 -> 1720 (plus 10 CE 6.0 twins fetched for the
constant-value cross-check: ee490906 / ee491772 / ee491563 / ee492116
/ ee491945 / ee491174 / ee491913 / ee491163 / ee491938 / ee491940).

### Functions (55 declared; every page Header: Imm.h, Link Library: Coreimm.lib, OS: Windows CE .NET 4.0 and later)

ImmAssociateContext `ms905984`, ImmAssociateContextEx `ms905985`,
ImmConfigureIME `ms905986`, ImmCreateContext `ms905987`, ImmCreateIMCC
`ms905988`, ImmDestroyContext `ms905989`, ImmDestroyIMCC `ms905990`,
ImmDisableIME `ms905991`, ImmEnumRegisterWord `ms905992`, ImmEscape
`ms905993`, ImmGenerateMessage `ms905994`, ImmGetCandidateList
`ms905995`, ImmGetCandidateListCount `ms905996`, ImmGetCandidateWindow
`ms905997`, ImmGetCompositionFont `ms905998`, ImmGetCompositionString
`ms906001`, ImmGetCompositionWindow `ms906002`, ImmGetContext
`ms906003`, ImmGetConversionList `ms906004`, ImmGetConversionStatus
`ms906005`, ImmGetDefaultIMEWnd `ms906007`, ImmGetDescription
`ms906008`, ImmGetGuideLine `ms906009`, ImmGetHotKey `ms906010`,
ImmGetIMCCLockCount `ms906011`, ImmGetIMCCSize `ms906012`,
ImmGetIMCLockCount `ms906013`, ImmGetIMEFileName `ms906014`,
ImmGetImeMenuItems `ms906015`, ImmGetOpenStatus `ms906016`,
ImmGetProperty `ms906017`, ImmGetRegisterWordStyle `ms906018`,
ImmGetStatusWindowPos `ms906019`, ImmGetVirtualKey `ms906020`,
ImmIsIME `ms906021`, ImmIsUIMessage `ms906022`, ImmLockIMC `ms906023`,
ImmLockIMCC `ms906024`, ImmNotifyIME `ms906025`, ImmRegisterWord
`ms906026`, ImmReleaseContext `ms906027`, ImmReSizeIMCC `ms906028`,
ImmSetCandidateWindow `ms906029`, ImmSetCompositionFont `ms906030`,
ImmSetCompositionString `ms906031`, ImmSetCompositionWindow
`ms906032`, ImmSetConversionStatus `ms906033`, ImmSetHotKey
`ms906034`, ImmSetOpenStatus `ms906035`, ImmSetStatusWindowPos
`ms906036`, ImmSimulateHotKey `ms906037`, ImmSIPanelState `ms906038`
(the CE-specific software input panel helper), ImmUnlockIMC
`ms906039`, ImmUnlockIMCC `ms906040`, ImmUnregisterWord `ms906041`.

Glued archive prototypes restored mechanically against the documented
types (the M43/M45 model); the pages that print `WINAPI` do so for
the IMCC/lock/hotkey/menu set -- WINAPI is empty for CE and the
declarations follow the repository's single-convention style.

Print artifacts fixed (each noted at the declaration site):
ImmAssociateContextEx prints `HINC hIMC` (the page's own parameter
text says "Handle to the input method context" -> HIMC);
ImmRegisterWord prints `LPCTSR lpszReading` (-> LPCTSTR).

### Types

| Item | Basis | Notes |
|---|---|---|
| `HIMC` | parameter text "Handle to the input method context." (ms906003 / ms905985); ImmGetContext returns it | HANDLE carrier (no published carrier type), the documented opaque-handle design |
| `HIMCC` | ImmCreateIMCC / ImmReSizeIMCC return type (ms905988 / ms906028) | HANDLE carrier |
| `LPHKL` / `LPUINT` | ImmGetHotKey prototype (ms906010) | added to windef.h next to HKL |
| `REGISTERWORDENUMPROC` | EnumRegisterWordProc page ms904955 ("application-defined callback function used with the ImmEnumRegisterWord function"): `UINT CALLBACK EnumRegisterWordProc(LPCTSTR, DWORD, LPCTSTR, LPVOID)` | function-pointer typedef |
| CANDIDATEFORM | ms904636 | 32-bit size 32 (TU-asserted) |
| CANDIDATEINFO | ms904637 | 32-bit size 144 (dwOffset[32]) |
| CANDIDATELIST | ms904638 | printed open-ended `dwOffset[]` -> C flexible array member; 32-bit size 24 |
| COMPOSITIONFORM | ms904714 | 32-bit size 28; archive print "Typedef struct_tag" restored |
| COMPOSITIONSTR | ms904715 | 25 documented DWORD members; 32-bit size 100 |
| GUIDELINE | ms905340 | 32-bit size 28 |
| RECONVERTSTRING | ms906231 | 32-bit size 32; P/NP/LP aliases (NEAR/FAR dropped, M39 decision) |
| REGISTERWORD | ms906232 | 32-bit size 8; LPTSTR members (CE Unicode-only) |
| STYLEBUF | ms906434 | 32-bit size 36 (CHAR szDescription[32]) |
| `LPINPUTCONTEXT` / `PINPUTCONTEXT` / `NPINPUTCONTEXT` | INPUTCONTEXT page ms906185 | **opaque**: the documented lfFont union needs the LOGFONTA layout; the official CE trees document LOGFONT only (CE Unicode-only) -- the layout cannot be completed from official information (LINEFORWARDLIST precedent) |
| `LPIMEMENUITEMINFO` (+P/NP) | IMEMENUITEMINFO page ms905980 | **opaque**: `szString[IMEMENUITEM_STRING_SIZE]` -- no CE tree (5.0 / .NET / 6.0, verified incl. CE .NET twin ms920945) publishes the constant value |
| `PIMECHARPOSITION` | IMECHARPOSITION page ms905972 | **opaque**: the `UNIT cLineHeight` member -- no CE tree publishes the width of UNIT (CE .NET twin ms920940 prints UNIT as well) |

### Recorded-not-defined (names published without values, both CE 5.0 and CE 6.0 trees)

The 83 IMM constant pages publish names only (verified: no numeric
value on any of the CE 5.0 pages or their CE 6.0 twins):

* IME Conversion Mode Values `ms905974` (IME_CMODE_*), IME
  Composition String Values `ms905973` (GCS_*), IME Hot Key
  Identifiers `ms905979` (IME_CHOTKEY_*), IME Sentence Mode Values
  `ms905981` (IME_SMODE_*), IME Escapes `ms905976` (IME_ESC_*)
* IMC_* message sub-codes: ms905842, ms905949, ms905955, ms905958,
  ms905959, ms905960, ms905961, ms905962, ms905963, ms905964,
  ms905966, ms905967, ms905968, ms905969, ms905970, ms905971 (16)
* IMN_* notifications: ms906042..ms906054 (13)
* IMR_* request codes: ms906055, ms906056, ms906147, ms906166,
  ms906175, ms906183, ms906184 (7)
* IPCTRL_* input-panel control codes (Header: Msime.h):
  ms906187..ms906217 (30)
* WM_IME_* messages: ms906445..ms906456 (12)

Same policy as the held Winsock constant sets (M39-M41): an on-device
readback is the documented compliant way to verify values before they
can be defined.

### Recorded-not-declared

* ImmGetConversionStatusForeground `ms906006`: Requirements rows
  Header: Pwinuser.h, Link Library: "Linked during platform build"
  -- a Platform Builder row, not a user-mode link library (CE .NET
  4.2+ only).

### Verification

* `make check` GREEN: hostcheck (headers + TU, warning-free under
  `_WIN32_WCE` 0x420/0x500/0x600; TU exercises all 55 functions, the
  callback shape and the nine structure sizes), defcheck
  `coreimm-doc.def` **56** exports (GetKeyboardLayout + the 55 IMM
  functions).
* `make crosscheck` GREEN on all six arm/i386 × CE 4.2/5.0/6.0
  targets (32-bit structure sizes asserted there).
* `make e2e` GREEN: the e2e console app references ImmGetContext /
  ImmReleaseContext / ImmGetOpenStatus / ImmNotifyIME /
  ImmSIPanelState; the recipe asserts `Name: coreimm.dll`,
  `Symbol: ImmGetContext`, `Symbol: ImmSIPanelState` in the import
  table of all six target images.

Export surface: `def/coreimm-doc.def` 1 -> **56** exports (name-only,
`LIBRARY coreimm.dll`).

## M47 -- Cryptography base CSP unit (new header wincrypt.h; Coredll.lib)

Scope: the base cryptographic-service-provider (CSP) surface of the
CE 5.0 "Cryptography" book -- the four fundamental crypto data types,
the BLOB structure, the CSP-authoring types, CPAcquireContext and the
42 Crypt* functions (including the CryptMsg* family and
CryptProtectData/CryptUnprotectData), 51 documented leaves harvested
(`tools/manifests/crypt-csp-base.manifest`, 47 base + BLOB/CERT_INFO/
CMSG_STREAM_INFO/VTableProvStruc support pages).

### Functions (42 declared, all Coredll.lib imports)

CryptAcquireContext (ms937733, CE 2.10+, BOOLEAN return per page),
CryptContextAddRef (ms937737), CryptCreateHash (ms937738), CryptDecrypt
(ms937741), CryptDeriveKey (ms937742), CryptDestroyHash (ms937743),
CryptDestroyKey (ms937744), CryptDuplicateHash (ms937745),
CryptDuplicateKey (ms937746), CryptEncrypt (ms937989),
CryptEnumProviders (ms938012), CryptEnumProviderTypes (ms938017),
CryptExportKey (ms938025), CryptFindLocalizedName (aa452566, CE 2.10+,
LPCWSTR only), CryptGenKey (ms938062), CryptGenRandom (ms938069),
CryptGetDefaultProvider (ms938088), CryptGetHashParam (ms938096),
CryptGetKeyParam (ms938103), CryptGetProvParam (ms938119),
CryptGetUserKey (ms938123), CryptHashData (ms938141),
CryptHashSessionKey (ms938156), CryptImportKey (ms938178),
CryptMsgCalculateEncodedLength (ms938232, CE 5.0+),
CryptMsgClose (ms938239), CryptMsgControl (ms938247),
CryptMsgDuplicate (ms938251), CryptMsgGetParam (ms938257),
CryptMsgOpenToDecode (ms938264), CryptMsgOpenToEncode (ms938271),
CryptMsgUpdate (ms938279), CryptProtectData (ms938309, CE .NET 4.0+),
CryptReleaseContext (ms938317), CryptSetHashParam (ms938326),
CryptSetKeyParam (ms938335), CryptSetProvider (ms938347),
CryptSetProviderEx (ms938353), CryptSetProvParam (ms938358),
CryptSignHash (ms938369), CryptUnprotectData (ms938379, CE .NET 4.0+),
CryptVerifySignature (ms938383).

### Declared-not-exported

* CPAcquireContext (ms937726): CSP-authoring entry point; its page
  lists "Link Library: Developer defined." -- provider DLLs export it,
  so it is declared in wincrypt.h but not added to any doc-derived
  def.

### Types

* ALG_ID = `unsigned int` (ms937014 verbatim), HCRYPTHASH/HCRYPTKEY/
  HCRYPTPROV = `unsigned long` (ms906535/ms906545/ms925987 verbatim).
* HCRYPTMSG: no dedicated data-type page in the CE archive; the
  CryptMsg* prototypes pass/return it, so it is declared as the
  handle carrier (repository design, documented in wincrypt.h).
* _CRYPTOAPI_BLOB (ms937016): {DWORD cbData; BYTE *pbData;} with the
  13 documented alias typedef names CRYPT_INTEGER_BLOB, CRYPT_UINT_BLOB,
  CRYPT_OBJID_BLOB, CERT_NAME_BLOB, CERT_RDN_VALUE_BLOB, CERT_BLOB,
  CRL_BLOB, DATA_BLOB, CRYPT_DATA_BLOB, CRYPT_HASH_BLOB,
  CRYPT_DIGEST_BLOB, CRYPT_DER_BLOB, CRYPT_ATTR_BLOB (plus pointers).
  The page prints no self-named CRYPTOAPI_BLOB typedef.
* CMSG_STREAM_INFO (ms937724) + PFN_CMSG_STREAM_OUTPUT (callback shape
  documented on the same page).
* VTableProvStruc (ms926457; the page documents Version = 3 on CE).
* PCERT_INFO: forward-declared opaque pointer only -- the full
  CERT_INFO structure (ms937672) chains into CERT_PUBLIC_KEY_INFO,
  CRYPT_ALGORITHM_IDENTIFIER, CERT_EXTENSION et al. and belongs to the
  certificate unit.
* CRYPTPROTECT_PROMPTSTRUCT: opaque tag; the CryptProtectData page
  documents that the parameter must be NULL on CE ("structure is not
  used").

### Title/print fix-ups (as always, page title declares the name)

* ms937746 prints the CryptDuplicateHash name on the CryptDuplicateKey
  row (parameter list is the key-duplicate shape).
* ms938096 prints lowercase "CryptGethashParam" for CryptGetHashParam.
* CryptExportKey's last parameter is printed `pdwbDataLen` (kept).
* The four CryptMsg pages (ms938247/ms938251/ms938271/ms938279) print
  their Requirements fields with the colon outside the label tag
  (`<strong>OS Versions</strong>:`); tools/ce-fetch.py was fixed to
  parse both shapes and the whole cached corpus re-parsed.

### Recorded-not-defined (names documented, values absent from the CE
archive -- same policy as the M39-M41/M46 held constant sets)

* CryptAcquireContext dwFlags: CRYPT_VERIFYCONTEXT, CRYPT_NEWKEYSET,
  CRYPT_DELETEKEYSET, CRYPT_MACHINE_KEYSET, CRYPT_SILENT,
  CRYPT_USER_PROTECTED (ms937733 parameter table).
* CryptProtectData flags: CRYPTPROTECT_LOCAL_MACHINE,
  CRYPTPROTECT_UI_FORBIDDEN, CRYPTPROTECT_SYSTEM,
  CRYPTPROTECT_NO_RECOVERY (ms938309).
* Provider types (ms937733): PROV_RSA_FULL, PROV_RSA_SIG, PROV_DSS,
  PROV_DSS_DH, PROV_FORTEZZA, PROV_MS_EXCHANGE, PROV_SSL,
  PROV_RSA_SCHANNEL, PROV_SPYRUS_LYNKS, PROV_RNG, PROV_INTEL_SEC,
  PROV_EC_ECDSA_SIG, PROV_EC_ECDSA_FULL, PROV_EC_ECNRA_SIG,
  PROV_EC_ECNRA_FULL.
* Algorithm identifiers (ms937014 table): 40 CALG_* names
  (CALG_AES_128/192/256, CALG_3DES, CALG_DES, CALG_MD5, CALG_SHA1,
  CALG_RSA_SIGN, CALG_RSA_KEYX, ...).
* Key specifications AT_KEYEXCHANGE / AT_SIGNATURE (ms937014 body).
* CryptGenKey documents the key-length encoding in dwFlags (high 16
  bits: value << 16, e.g. 0x08000000 for 128-bit) inside parameter
  text; no named constants.

### Verification

* `make check` GREEN: hostcheck (headers + TU warning-free under
  `_WIN32_WCE` 0x420/0x500/0x600; TU exercises all 42 functions +
  CPAcquireContext, the PFN_CMSG_STREAM_OUTPUT shape, and the
  _CRYPTOAPI_BLOB/DATA_BLOB/CMSG_STREAM_INFO/VTableProvStruc sizes),
  defcheck `coredll-doc.def` **602** exports (+42).
* `make crosscheck` GREEN on all six arm/i386 x CE 4.2/5.0/6.0
  targets (32-bit structure sizes asserted there).
* `make e2e` GREEN: the e2e console app references CryptAcquireContext
  / CryptCreateHash / CryptGenRandom / CryptMsgOpenToEncode /
  CryptMsgClose / CryptProtectData; the recipe asserts
  `Symbol: CryptAcquireContext`, `Symbol: CryptMsgClose`,
  `Symbol: CryptProtectData` in the import table of all six target
  images (all from coredll.dll).

Export surface: `def/coredll-doc.def` 560 -> **602** exports.
rows.json 1801 -> **1852** records.

## M48 -- Cryptography certificate / encode / OID / PFX unit (wincrypt.h; Crypt32.lib) + structure trees

Scope: the certificate-store surface of the CE 5.0 Cryptography book,
154 documented leaves harvested across three manifests
(`crypt-cert.manifest` 54 Cert* functions, `crypt-encode-pfx.manifest`
29 encode/OID/PFX functions, `crypt-structs.manifest` 71 structure
pages -- BLOB/CMSG_STREAM_INFO/VTableProvStruc/CERT_INFO already
harvested in M47).  Every function page lists Header: Wincrypt.h and
Link Library: **Crypt32.lib** (new doc-derived def).

### Functions (83 declared, all Crypt32.lib imports)

* Cert* store/context functions (54, all CE 3.0+):
  CertAddCertificateContextToStore (ms937018), CertAddCertificateLinkToStore
  (ms937019), CertAddEncodedCertificateToStore (ms937020),
  CertAddEnhancedKeyUsageIdentifier (ms937021),
  CertAddSerializedElementToStore (ms937022), CertAlgIdToOID (ms937023),
  CertCloseStore (ms937035), CertCompareCertificate (ms937036),
  CertCompareCertificateName (ms937037), CertCompareIntegerBlob
  (ms937038), CertComparePublicKeyInfo (ms937039), CertControlStore
  (ms937042), CertCreateCertificateContext (ms937043),
  CertDeleteCertificateFromStore (ms937044), CertDuplicateCertificateChain
  (ms937235), CertDuplicateCertificateContext (ms937328),
  CertDuplicateStore (ms937422), CertEnumCertificateContextProperties
  (ms937534), CertEnumCertificatesInStore (ms937636),
  CertEnumPhysicalStore (aa452564), CertEnumSystemStore (ms937645),
  CertEnumSystemStoreLocation (ms937650), CertFindAttribute (ms937652),
  CertFindCertificateInStore (ms937653), CertFindExtension (ms937655),
  CertFindRDNAttr (ms937657), CertFreeCertificateChain (ms937658, void
  return as printed), CertFreeCertificateContext (ms937659),
  CertGetCertificateChain (ms937660), CertGetCertificateContextProperty
  (ms937661), CertGetEnhancedKeyUsage (ms937662), CertGetIntendedKeyUsage
  (ms937663), CertGetIssuerCertificateFromStore (ms937664),
  CertGetNameString (ms937665), CertGetPublicKeyLength (ms937667),
  CertGetStoreProperty (ms937668, no qualifier printed),
  CertGetSubjectCertificateFromStore (ms937670), CertGetValidUsages
  (aa452565), CertIsRDNAttrsInCertificateName (ms937674), CertNameToStr
  (ms937681), CertOIDToAlgId (ms937682), CertOpenStore (ms937683),
  CertOpenSystemStore (ms937684), CertRDNValueToStr (ms937693),
  CertRemoveEnhancedKeyUsageIdentifier (ms937694), CertSaveStore
  (ms937696), CertSerializeCertificateStoreElement (ms937697),
  CertSetCertificateContextProperty (ms937698), CertSetEnhancedKeyUsage
  (ms937699), CertSetStoreProperty (ms937700, no qualifier printed),
  CertStrToName (ms937703), CertVerifySubjectCertificateContext
  (ms937709), CertVerifyTimeValidity (ms937710), CertVerifyValidityNesting
  (ms937711).
* Encode/decode/OID/key-identifier functions (25, CE 3.0+):
  CryptAcquireCertificatePrivateKey (ms937732),
  CryptCreateKeyIdentifierFromCSP (ms937739), CryptDecodeObjectEx
  (ms937740), CryptEncodeObjectEx (ms937747),
  CryptEnumKeyIdentifierProperties (ms937995), CryptEnumOIDInfo
  (ms938004), CryptExportPublicKeyInfoEx (ms938031),
  CryptFindCertificateKeyProvInfo (ms938040), CryptFindOIDInfo
  (ms938050), CryptFreeOIDFunctionAddress (ms938057),
  CryptGetDefaultOIDFunctionAddress (ms938079),
  CryptGetKeyIdentifierProperty (ms938099), CryptGetOIDFunctionAddress
  (ms938109), CryptHashCertificate (ms938130), CryptHashPublicKeyInfo
  (ms938149), CryptHashToBeSigned (ms938167), CryptImportPublicKeyInfoEx
  (ms938185), CryptInitOIDFunctionSet (ms938191),
  CryptInstallDefaultContext (ms938197), CryptInstallOIDFunctionAddress
  (ms938204), CryptSetKeyIdentifierProperty (ms938330),
  CryptSignAndEncodeCertificate (ms938360), CryptSignCertificate
  (ms938364), CryptVerifyCertificateSignature (aa452567, CE 2.10+),
  CryptUninstallDefaultContext (ms938372).
* PFX (4, CE 5.0+): PFXExportCertStoreEx (ms926224), PFXImportCertStore
  (ms926229), PFXIsPFXBlob (ms926234), PFXVerifyPassword (ms926241).

### Types completed from the structure pages (transcribed verbatim)

Handle carriers (no type pages): HCERTSTORE, HCERTCHAINENGINE,
HCRYPTOIDFUNCSET, HCRYPTOIDFUNCADDR, HCRYPTDEFAULTCONTEXT.

CRYPT_BIT_BLOB, CRYPT_ALGORITHM_IDENTIFIER, CRYPT_ATTRIBUTE,
CRYPT_ATTRIBUTES (+CMSG_ATTR), CRYPT_KEY_PROV_PARAM, CRYPT_KEY_PROV_INFO,
CRYPT_OID_FUNC_ENTRY, CRYPT_OID_INFO (+CCRYPT_OID_INFO/PCCRYPT_OID_INFO),
HMAC_INFO (tag _HMAC_Info), PROV_ENUMALGS, PROV_ENUMALGS_EX,
PUBLICKEYSTRUC (+BLOBHEADER), RSAPUBKEY, CTL_USAGE (+CERT_ENHKEY_USAGE),
CERT_TRUST_STATUS, CERT_EXTENSION, CERT_ISSUER_SERIAL_NUMBER,
CERT_PRIVATE_KEY_VALIDITY, CERT_PUBLIC_KEY_INFO, **CERT_INFO** (closing
the M47 hold), CERT_CONTEXT (+PCCERT_CONTEXT), CERT_RDN_ATTR, CERT_RDN,
CERT_NAME_INFO, CERT_POLICY_QUALIFIER_INFO, CERT_POLICY_ID,
CERT_POLICY_INFO, CERT_POLICIES_INFO, CERT_KEY_ATTRIBUTES_INFO,
CERT_KEY_CONTEXT, CERT_KEY_USAGE_RESTRICTION_INFO,
CERT_KEYGEN_REQUEST_INFO, CERT_ID, CERT_ALT_NAME_ENTRY,
CERT_ALT_NAME_INFO, CERT_ACCESS_DESCRIPTION,
CERT_AUTHORITY_INFO_ACCESS, CERT_AUTHORITY_KEY_ID_INFO,
CERT_AUTHORITY_KEY_ID2_INFO, CERT_BASIC_CONSTRAINTS_INFO,
CERT_BASIC_CONSTRAINTS2_INFO, CERT_REQUEST_INFO,
CERT_SIGNED_CONTENT_INFO, CERT_USAGE_MATCH, CERT_CHAIN_ELEMENT,
CERT_SIMPLE_CHAIN, CERT_CHAIN_CONTEXT (+PCCERT_CHAIN_CONTEXT),
CERT_CHAIN_ENGINE_CONFIG, CERT_CHAIN_PARA, CERT_TRUST_LIST_INFO,
CERT_SYSTEM_STORE_INFO, CERT_SYSTEM_STORE_RELOCATE_PARA,
CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR_PARA, CMSG_CTRL_DECRYPT_PARA,
CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA, CMSG_CTRL_KEY_AGREE_DECRYPT_PARA,
CMSG_CTRL_VERIFY_SIGNATURE_EX_PARA, CMSG_KEY_TRANS_RECIPIENT_INFO,
CMSG_MAIL_LIST_RECIPIENT_INFO, CMSG_CMS_RECIPIENT_INFO,
CMSG_CMS_SIGNER_INFO, CMSG_SIGNER_INFO, CMSG_SIGNER_ENCODE_INFO,
CMSG_SIGNED_ENCODE_INFO, CMSG_ENVELOPED_ENCODE_INFO,
CMSG_HASHED_ENCODE_INFO, CRYPT_ENCODE_PARA.

Callback pointer types: PFN_CERT_ENUM_SYSTEM_STORE and
PFN_CERT_ENUM_SYSTEM_STORE_LOCATION have documented callback shapes
(ms937645 / ms937650, incl. the printed pvszStoreLoocations spelling);
PFN_CERT_ENUM_PHYSICAL_STORE / PFN_CRYPT_ENUM_KEYID_PROP /
PFN_CRYPT_ENUM_OID_INFO / PFN_CRYPT_ALLOC / PFN_CRYPT_FREE publish no
callback signatures on the CE pages -> generic function pointer
(documented design decision).

### Opaque (pointer-only, no layout page in the CE archive)

PCERT_OTHER_NAME, PCERT_REVOCATION_INFO, PCTL_ENTRY, PCCTL_CONTEXT,
PCMSG_KEY_AGREE_RECIPIENT_INFO, PCRYPT_ATTRIBUTE_TYPE_VALUE,
PCMSG_RECIPIENT_ENCODE_INFO, PCRYPT_DECODE_PARA -- each is referenced
only through a pointer member/parameter; forward-declared tags keep
every documented struct complete.

### Title/print fix-ups

* ms937719 CMSG_HASHED_ENCODE_INFO: the page print reuses the
  ENVELOPED struct name; the topic title declares the hashed one.
* ms937701 CERT_SIGNED_CONTENT_INFO: the print is truncated before the
  closing brace; completed from the same print.
* ms937721 CMSG_SIGNED_ENCODE_INFO: the pointer alias is missing from
  the print; completed (printed member spelling cAttrCertlEncoded
  kept).
* CertGetStoreProperty / CertSetStoreProperty print no calling
  convention; CertFreeCertificateChain prints a void return -- all as
  printed (WINAPI is empty on CE either way).

### 32-bit sizes (measured on the CE target, TU-asserted)

PROV_ENUMALGS 52, PROV_ENUMALGS_EX 148, PUBLICKEYSTRUC/BLOBHEADER 8,
RSAPUBKEY 12, CERT_SYSTEM_STORE_INFO 4, CERT_TRUST_STATUS 8;
pointer-bearing (32-bit model): CTL_USAGE 8, CRYPT_BIT_BLOB 12,
CRYPT_ALGORITHM_IDENTIFIER 12, CRYPT_ATTRIBUTE 12, CRYPT_ATTRIBUTES 8,
CRYPT_KEY_PROV_PARAM 16, CRYPT_KEY_PROV_INFO 28, CRYPT_OID_INFO 28,
CRYPT_ENCODE_PARA 12, HMAC_INFO 20, CERT_EXTENSION 16,
CERT_ISSUER_SERIAL_NUMBER 16, CERT_PRIVATE_KEY_VALIDITY 16,
CERT_PUBLIC_KEY_INFO 24, CERT_INFO 112, CERT_CONTEXT 20,
CERT_RDN_ATTR 16, CERT_RDN 8, CERT_NAME_INFO 8,
CERT_POLICY_QUALIFIER_INFO 12, CERT_POLICY_ID 8, CERT_POLICY_INFO 12,
CERT_POLICIES_INFO 8, CERT_KEY_ATTRIBUTES_INFO 24, CERT_KEY_CONTEXT 12,
CERT_KEY_USAGE_RESTRICTION_INFO 20, CERT_KEYGEN_REQUEST_INFO 32,
CERT_ID 20, CERT_ALT_NAME_ENTRY 12, CERT_ALT_NAME_INFO 8,
CERT_ACCESS_DESCRIPTION 16, CERT_AUTHORITY_INFO_ACCESS 8,
CERT_AUTHORITY_KEY_ID_INFO 24, CERT_AUTHORITY_KEY_ID2_INFO 24,
CERT_BASIC_CONSTRAINTS_INFO 28, CERT_BASIC_CONSTRAINTS2_INFO 12,
CERT_REQUEST_INFO 44, CERT_SIGNED_CONTENT_INFO 32, CERT_USAGE_MATCH 12,
CERT_CHAIN_ELEMENT 20, CERT_SIMPLE_CHAIN 24, CERT_CHAIN_CONTEXT 20,
CERT_CHAIN_ENGINE_CONFIG 40, CERT_CHAIN_PARA 16, CERT_TRUST_LIST_INFO 12,
CERT_SYSTEM_STORE_RELOCATE_PARA 8, CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR_PARA 16,
CMSG_CTRL_DECRYPT_PARA 16, CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA 12,
CMSG_CTRL_KEY_AGREE_DECRYPT_PARA 36, CMSG_CTRL_VERIFY_SIGNATURE_EX_PARA 20,
CMSG_KEY_TRANS_RECIPIENT_INFO 44, CMSG_MAIL_LIST_RECIPIENT_INFO 44,
CMSG_CMS_RECIPIENT_INFO 8, CMSG_CMS_SIGNER_INFO 72, CMSG_SIGNER_INFO 68,
CMSG_SIGNER_ENCODE_INFO 84, CMSG_SIGNED_ENCODE_INFO 36,
CMSG_ENVELOPED_ENCODE_INFO 68, CMSG_HASHED_ENCODE_INFO 24.

### Recorded-not-defined (values absent from the CE archive)

CERT_NAME_* / CERT_FIND_* / CERT_STORE_* / CERT_CHAIN_* / CMSG_* /
szOID_* identifier sets that the parameter tables name without numeric
values (same held-set policy as M39-M41/M46/M47).

### Verification

* `make check` GREEN (TU exercises all 83 functions + both documented
  callback shapes + every struct; defcheck `crypt32-doc.def` **83**).
* `make crosscheck` GREEN on all six targets (all sizes above asserted
  there).
* `make e2e` GREEN: asserts `Name: crypt32.dll` + CertOpenStore /
  CryptEncodeObjectEx / PFXImportCertStore imports on all six images.

Export surface: new `def/crypt32-doc.def` **83** exports.
rows.json 1852 -> **2033** records (incl. M49 below).

## M49 -- Smart Card subsystem unit (new header winscard.h; Winscard.lib)

Scope: the Smart Card book of the CE 5.0 Cryptography chapter -- 28
SCard* functions (every page Header: Winscard.h / Link Library:
Winscard.lib) + 3 structures, 31 leaves
(`tools/manifests/smartcard.manifest`).

### Functions (28)

SCardBeginTransaction (ms938481), SCardCancel (ms938495), SCardConnect
(ms938504), SCardControl (ms938510), SCardDisconnect (ms938517),
SCardEndTransaction (ms938526), SCardEstablishContext (ms938536),
SCardForgetCardType (ms938545), SCardForgetReader (ms938553),
SCardFreeMemory (ms938564, CE 5.0+, trailing-comma print fixed),
SCardGetAttrib (ms938574), SCardGetCardTypeProviderName (ms926375),
SCardGetProviderId (ms926397), SCardGetStatusChange (ms926406),
SCardIntroduceCardType (ms926415), SCardIntroduceReader (ms926416),
SCardIsValidContext (ms926418, CE .NET 4.1+), SCardListCards (ms926419),
SCardListInterfaces (ms926420), SCardListReaders (ms926422),
SCardLocateCards (ms926423), SCardLocateCardsByATR (ms926424, CE .NET
4.1+; page prints the SCardLocateCards name -- title wins),
SCardReconnect (ms926426), SCardReleaseContext (ms926427),
SCardSetAttrib (ms926428), SCardSetCardTypeProviderName (ms926429),
SCardStatus (ms926430), SCardTransmit (ms926431; printed
LPCSCARD_I0_REQUEST declared as the const pointer to SCARD_IO_REQUEST).

### Types

* SCARD_IO_REQUEST (ms926417, anonymous tag as printed; LPSCARD_IO_REQUEST
  / LPCSCARD_IO_REQUEST named by the SCardTransmit prototype).
* SCARD_READERSTATE (ms926425, 32-bit size 56 TU-asserted).
* SCARD_ATRMASK (ms938473, size 76 TU-asserted, CE .NET 4.1+).
* SCARDCONTEXT / SCARDHANDLE: no type pages -> handle carriers
  (documented design decision).
* New windef/winnt helpers added for documented spellings: PBYTE
  (M48), LPCBYTE, LPCGUID.

### Recorded-not-defined

SCARD_STATE_* / SCARD_PROTOCOL_* / SCARD_ATTR_* / SCARD_SCOPE_* /
SCARD_SHARE_* value sets: named without values on the CE pages
(held-set policy).

### Verification

* `make check` GREEN (TU m49 exercises all 28 functions + the three
  structures; defcheck `winscard-doc.def` **28**).
* `make crosscheck` GREEN on all six targets.
* `make e2e` GREEN: asserts `Name: winscard.dll` + SCardEstablishContext
  / SCardTransmit imports on all six images.

Export surface: new `def/winscard-doc.def` **28** exports.

## M50 -- AYGShell unit (new headers aygshell.h, shellsdk.h, newmenu.h, shlobj.h, extfile.h; Aygshell.lib)

Scope: the AYGShell Reference book of the CE 5.0 Shell documentation
(Shell and User Interface :: Shell :: Shell Reference :: AYGShell
Reference; book root ms907090) -- 62 API leaves
(`tools/manifests/aygshell.manifest`): 34 SH* function pages,
2 interface roots + 4 method pages, 3 macros, 9 messages, 8 structures,
1 enumeration (SHNP), 1 control class (WC_SIPPREF).  The CE 6.0 twins
(`build/aygshell-ce60.manifest`, 63 pages; INewMenuItemServer and
IShellNotificationCallback roots have no twin) were harvested for
cross-checking only -- they stay in pages6/ in the corpus.

### Functions (34 pages; aygshell.lib unless noted)

SHChangeNotifyDeregister (aa453670, CE .NET 4.2+), SHChangeNotifyFree
(aa453672, CE .NET 4.2+), SHChangeNotifyRegister (aa453673, CE .NET
4.2+), SHCloseApps (aa453674), SHCreateMenuBar (aa453678, CE .NET
4.2+), SHCreateNewItem (aa453679), SHDoneButton (aa453682),
SHEnumPropSheetHandlers (aa453688; stub on CE devices, returns FALSE),
SHFindMenuBar (aa453692), SHFreeContextMenuExtensions (aa453693),
SHFullScreen (aa453694; CE 6.0 twin ee499392 prints Header: shellsdk.h
-- CE 5.0 home aygshell.h kept, divergence recorded), SHGetAppKeyAssoc
(aa453695), SHGetAutoRunPath (aa453696, CE .NET 4.2+; Header: windows.h
-- declared in windows.h, library aygshell.lib), SHGetEmergencyCallList
(aa453699; stub, E_NOTIMPL), SHGetInputContext (aa453701, CE .NET 4.0+;
stub, E_NOTIMPL; token spacing restored from twin ee503391),
SHHandleWMActivate (aa453710), SHHandleWMSettingChange (aa453711),
SHInitDialog (aa453713; Header: shellsdk.h, library aygshell.lib --
declared in shellsdk.h; twin ee501722 repeats shellsdk.h),
SHInitExtraControls (aa453715), SHInputDialog (aa453716),
SHInvokeContextMenuCommand (aa453717), SHLoadContextMenuExtensions
(aa453719), SHNavigateBack (aa453722; stub), SHNotificationAdd
(aa453723), SHNotificationGetData (aa453725), SHNotificationRemove
(aa453726), SHNotificationUpdate (aa453727), SHRecognizeGesture
(aa453732), SHSetAppKeyWndAssoc (aa453734), SHSetBack (aa453735,
CE 5.0+; stub, ERROR_CALL_NOT_IMPLEMENTED), SHSetInputContext
(aa453736, CE .NET 4.0+; stub, E_NOTIMPL; spacing from twin ee502532),
SHSetNavBarText (aa453737), SHSipInfo (aa453740).  SHSipPreference
(aa453741) is HELD entirely (see below).  Windows CE 3.0+ unless noted.
Library-row spellings alternate between "Link Library:" and "Library:"
in this book (parser handles both).

### Interfaces (application-implemented; not DLL exports)

* INewMenuItemServer (ms909845, CE .NET 4.2+; Link Library:
  Application-defined) + CreateNewItem (ms909846).  Opaque interface
  tag + documented method record (M44 objbase.h model).
* IShellNotificationCallback (ms909877) + OnCommandSelected (ms909878),
  OnDismiss (ms909879), OnLinkSelected (ms909880); OnShow is Reserved,
  returns E_NOTIMPL, no signature page.  Vtable order as the page
  table prints (IUnknown, OnShow, OnCommandSelected, OnLinkSelected,
  OnDismiss).  Opaque tag + method records.

### Structures / enumeration / control class

* SHACTIVATEINFO (aa453665; 32-bit size 12 TU-asserted; page prints
  stray periods after member names -- "cbSize.", "fSipUp.:1" --
  removed; 1/1/1/29 bitfield split as printed).
* SHCHANGENOTIFYENTRY (aa453671, CE .NET 4.2+; size 12 TU-asserted;
  fRecursive "Not supported" per the page; SHCNE_* event names held).
* SHINITDLGINFO (aa453714; size 12 TU-asserted; tag tagSHINITDIALOG;
  carries the one published value SHIDIM_FLAGS 0x0001).
* SHMENUBARINFO (aa453721; size 36 TU-asserted; SHCMBF_* held).
* SHNOTIFICATIONDATA (aa453724; size 56 TU-asserted; tag
  _SHNOTIFICATIONDATA; SHNP priority, SHNF_* held; the page prints
  "SHNF_SHNF_SPINNERS" doubled -- verbatim record:
  SHNF_ SHNF_SPINNERS.  The CE 6.0 twin ee499049 extends the layout
  with union { SOFTKEYMENU skm; SOFTKEYNOTIFY rgskn
  [NOTIF_NUM_SOFTKEYS]; } + pszTodaySK / pszTodayExec; SOFTKEYMENU /
  SOFTKEYNOTIFY / NOTIF_NUM_SOFTKEYS have no pages in any official CE
  catalog, so the extension is HELD.  Internal inconsistency: the
  CE 5.0 page's own example uses rgskn / pszTodaySK / pszTodayExec).
* SHRGINFO (aa453733; size 20 TU-asserted; tag tagSHRGI; SHRG_* held).
* NMNEWMENU (ms931659; size 196 TU-asserted; newmenu.h; no library
  row; member type printed "IpropertyBag **" -- documented
  IPropertyBag spelling used).
* FILECHANGENOTIFY (aa453066, CE .NET 4.2+; size 40 TU-asserted).
  Main Requirements row prints the multi-header list "Commctrl.h,
  Prsht.h, Shlguid.h." with no library; the Windows Mobile row and the
  WM_FILECHANGEINFO carrier page name shlobj.h + ceshell.lib.  Design
  decision: co-located with its carrier message in shlobj.h (the
  Prsht.h/Shlguid.h homes belong to unharvested books).  CE 6.0 twin
  ee500811 repeats the multi-header list.
* FILECHANGEINFO (ms889030; size 36 TU-asserted; Extfile.h, CE 2.10+;
  dependency harvest from the File I/O Structures book; no library
  row; page prints the layout without the typedef keyword -- restored;
  SHCNE_* / SHCNF_* names held.  CE 6.0 twin ee490403 prints extfile.h,
  shlobj.h / ceshell.lib).
* SHNP (aa453728): complete enum body printed (SHNP_INFORM,
  SHNP_ICONIC), implicit enumerator values.
* WC_SIPPREF (ms914097, CE .NET 4.2+): L"SIPPREF" -- value published.

### Messages / macros / dependencies (winuser.h, windows.h)

* NMHDR (ms931479, CE 1.0+; Winuser.h; size 12 TU-asserted) added to
  winuser.h: hwndFrom / idFrom / code, the notification header of
  WM_NOTIFY (aa453890 types the lParam LPNMHDR; the NMN_* New-button
  notifications and common-control notifications ride on it).  The
  NMHDR page's remark names NM_RCLICK / NM_RDBCLICK (sic) as mouse
  support -- names only, no values, recorded.
* WM_NOTIFY (aa453890) = 0x004E and WM_SETTINGCHANGE (aa453906) =
  0x001A (== WM_WININICHANGE) added to winuser.h via the M29
  fixed-Win32-ABI-value policy (both are fixed Win32 ABI identifiers
  with published Win32 values; both CE pages print Winuser.h, CE 1.0+).
* SHGetAutoRunPath declared in windows.h per its documented Header row
  (library aygshell.lib feeds def/aygshell-doc.def).
* Macros SHGetMenu (aa453703) / SHGetSubMenu (aa453708) / SHSetSubMenu
  (aa453738): recorded verbatim in aygshell.h comments, not defined --
  they expand to SendMessage calls on the SHCMBM_* messages whose
  values are unpublished (held-set policy).  CE 6.0 twins confirm
  aygshell.lib for all three and CE 4.2+ availability.
* Messages SHCMBM_GETMENU (aa453675) / SHCMBM_GETSUBMENU (aa453676) /
  SHCMBM_SETSUBMENU (aa453677): shapes documented (lParam = menuid /
  (HMENU) hmenu), values held.  Page quirk: SHCMBM_SETSUBMENU's lParam
  is (HMENU) hmenu while the SHSetSubMenu macro passes ID_MENU.
* WM_FILECHANGEINFO (aa453860; shlobj.h + ceshell.lib; CE 3.0+):
  shape documented (wParam reserved 0, lParam = FILECHANGENOTIFY*), CE
  shell message, value held.  ceshell.lib has no other sole-link
  function pages, so no ceshell-doc.def is written (gen-doc-def
  reports 1 co-listed page skipped).

### Recorded-not-defined (held sets; names published, values not,
in any official CE tree -- M39-M41 policy)

SHIDIF_* (8), SHCMBF_* (5), SHRG_* (4), SHNF_* (10), SHNUM_*,
SPI_GETSIPINFO / SPI_SETSIPINFO / SPI_GETCURRENTIM / SPI_SETCURRENTIM
(SHSipInfo actions; *SIPINFO take SIPINFO*, *CURRENTIM take CLSID*;
uiParam 0 or the WM_SETTINGCHANGE lParam; fWinIni reserved 0), SHFS_*
(6), SHDB_* (3), SHCMBM_* (3), NMN_* (5), WM_FILECHANGEINFO,
GN_CONTEXTMENU, SHIC_FEATURE (enumeration named, no page), SHA_INPUTDIALOG,
SIP_INPUTDIALOG, SHCNE_* / SHCNF_* (ms889030 tables), VK_APP1..VK_APP6
(SHSetAppKeyWndAssoc remarks), NM_RCLICK / NM_RDBCLICK (sic).

### Held entire

* SHSipPreference (aa453741): parameter type SIPSTATE has no published
  definition in any official CE tree (no SIPSTATE page in the CE 5.0 /
  CE .NET / CE 6.0 catalogs; SIP_UP / SIP_DOWN / SIP_FORCEDOWN /
  SIP_UNCHANGED appear only as prose names), so the documented
  signature cannot be typed in C without inventing the enum.  Held
  with a verbatim record in aygshell.h; excluded from
  def/aygshell-doc.def.
* SHNOTIFICATIONDATA CE 6.0 layout extension (see above; types
  unpublished).

### Handle carriers / opaque tags (design decisions)

HPROPSHEETPAGE = HANDLE (aa453688 types a HPROPSHEETPAGE* array; no CE
page publishes the carrier -- its home is the unharvested Property
Sheets book).  IShellPropSheetExt opaque tag (aa453688; the Remarks
name its AddPages method; no interface page in any catalog).

### Verification

* `make check` GREEN (TU m50 exercises all 33 exported functions + the
  structures / enum / WC_SIPPREF / NMNEWMENU / FILECHANGENOTIFY /
  FILECHANGEINFO / NMHDR; 10 new 32-bit size asserts, pointer-guarded,
  fired by the CE targets in crosscheck).
* `make crosscheck` GREEN on all six targets (real LLVM-WinCE clang,
  `-Werror`; the five new headers standalone + full TU).
* `make e2e` GREEN: the M50 consumer unit links 17 SH* calls against
  def/aygshell-doc.def; asserts `Name: aygshell.dll` + SHCreateMenuBar
  + SHHandleWMActivate + SHInitDialog + SHGetAutoRunPath imports on
  all six images.  (The e2e block avoids aggregate zero-initializers:
  the freestanding ARM link has no __aeabi_memclr helpers -- M44
  style, explicit member stores.)

Export surface: new `def/aygshell-doc.def` **33** exports (31
aygshell.h functions + SHInitDialog + SHGetAutoRunPath; SHSipPreference
held).  Header count 30 -> 35; def count 38 -> 39.

## M51 -- Software-based Input Panel unit (new headers sipapi.h, sip.h; Coredll.lib)

Scope: the Software-based Input Panel Reference book of the CE 5.0
documentation (Shell and User Interface :: User Interface ::
Software-based Input Panel, book root aa453941; reference aa452750) --
49 leaves (`tools/manifests/sip.manifest`): 10 function pages (9 Sip*
imports + the application-defined SipEnumIMProc callback), 4 structure
pages and 35 interface/method pages (IIMCallback, IIMCallback2,
IInputMethod, IInputMethod2).  The 14 CE 6.0 twins of the function and
structure pages were harvested for cross-checking
(`tools/manifests/sip-ce60.manifest`); the four
interface roots have no CE 6.0 leaf under those titles.  Two CE 5.0
message dependency pages were harvested: WM_IM_INFO (aa453870) and
WM_SYSCOPYDATA (aa453912).

### Functions (9 exports; every page Header: Sipapi.h / Link Library:
Coredll.lib / Windows CE 2.10 and later; CE 6.0 twins repeat
sipapi.h + coredll.lib)

SipEnumIM (aa453742; NULL callback returns the IM count; -1 = error on
CE 3.0+; does not initialize the SIP environment), SipGetCurrentIM
(aa453744), SipGetInfo (aa453745), SipRegisterNotification (ms932947;
single registration, survives until boot; posts WM_IM_INFO),
SipSetCurrentIM (ms940337), SipSetDefaultRect (ms940340; page prints
"BOOLSipSetDefaultRect" -- spacing restored from twin ee504359),
SipSetInfo (ms940341), SipShowIM (ms940342; SIPF_ON / SIPF_OFF),
SipStatus (ms940343; SIP_STATUS_AVAILABLE / SIP_STATUS_UNAVAILABLE).

SipEnumIMProc (aa453743) is the application-defined callback (Header
and Link Library rows print "Developer defined"; the CE 6.0 twin
ee505466 prints "Developer Implemented"): declared in sipapi.h without
the import pin, same model as the M47 CPAcquireContext declaration.
IMENUMPROC is named by SipEnumIM's parameter but has no page; carried
as a function-pointer typedef built from the two documented
signatures (documented design decision, note (b) in sipapi.h).

### Structures

* SIPINFO (ms932860, Sipapi.h, CE 2.01+, no library row; 32-bit size
  48 TU-asserted; anonymous tag as printed; twin ee499105 prints the
  identical layout -- no CE 6.0 extension).  This closes the M50
  SHSipInfo forward note: the SPI_*SIPINFO actions' pvParam now has a
  declared target (the SHSipInfo comment was updated; the action-name
  values themselves remain held).
* IMENUMINFO (ms909841, Sipapi.h, CE 2.10+, no library row; 32-bit
  size 536 TU-asserted).  Page prints the declaration without the
  typedef keyword ("struct_IMENUMINFO{...}IMENUMINFO;"); typedef
  restored, tag _IMENUMINFO as printed (twin ee503605 repeats the
  print).
* IMINFO (ms909842, Sip.h, CE 2.01+, no library row; 32-bit size 40
  TU-asserted; anonymous tag as printed; twin ee503199 identical).
  Page quirk: the fdwFlags table prints "SIP_OFF" (no F) for the off
  state while the SIPINFO table prints SIPF_OFF for the same state --
  recorded verbatim; all four state bits are names-without-values
  (held).  HIMAGELIST comes from commctrl.h (M29).
* LMDATA (aa453406, Sip.h, CE 2.12+, no library row; size 24
  TU-asserted; tag _tagLMDATA as printed; twin ee499697 identical).
  dwVersion must be 0x00010000 (the one published value); the twelve
  LMDATA_SYMBOL_* / LMDATA_SKIP_* / LMDATA_SCORE_* flag names are held
  (no values); offsets are measured from the end of the structure.

### Interfaces (Sip.h / Uuid.lib rows; application/IM-implemented,
not DLL exports -- M44 opaque-tag + method-record model)

* IIMCallback (ms929942, CE 2.01+): SetImInfo (ms929952), SendVirtualKey
  (ms929951), SendCharEvents (ms929949), SendString (ms929950) -- page
  table order.
* IIMCallback2 (ms929943, CE 2.12+): the four IIMCallback shapes
  (ms929948 / ms929947 / ms929945 / ms929946) + SendAlternatives2
  (ms929944, LMDATA* -- delivered as WM_SYSCOPYDATA with wParam
  WMSCD_CHAR_RANKED_ALTS).
* IInputMethod (ms929953, CE 2.12+ per the root page -- the method
  pages print CE 2.01+ (recorded inconsistency)): Select (ms909669),
  Deselect (ms930093), Showing (ms909766), Hiding (ms930118), GetInfo
  (ms930107), ReceiveSipInfo (ms930126, SIPINFO*), RegisterCallback
  (ms930132, IIMCallback*), GetImData (ms930101), SetImData (ms909763),
  UserOptionsDlg (ms909775; printed "HRESULTUserOptionsDlg" --
  spacing restored).  Documented initialization call sequence:
  Select, GetInfo, ReceiveSipInfo, RegisterCallback.
* IInputMethod2 (ms929954, CE 2.12+): the IInputMethod shapes
  (ms929962 / ms929955 / ms929965 / ms929958 / ms929957 / ms929959 /
  ms929960 / ms929956 / ms929963 / ms930035) + SetIMMActiveContext
  (ms929964; HWND, BOOL, DWORD, DWORD, DWORD hkl -- hkl printed as
  DWORD although the prose calls it "a handle to the current active
  keyboard layout"; called when ImmSetActiveContext is called) +
  RegisterCallback2 (ms929961, IIMCallback2*).  Quirk:
  IInputMethod2::RegisterCallback (ms929960) prints the parameter
  IIMCallback* while its prose says IIMCallback2 -- printed signature
  wins, recorded.

### Messages / dependency records

* WM_IM_INFO (aa453870; Header Winuser.h, CE 2.10+, no library row):
  shape wParam = flag / lParam = pdata with the IM_POSITION /
  IM_WIDEIMAGE / IM_NARROWIMAGE change-type names -- recorded in
  winuser.h (its documented home), values held (message id and flag
  values unpublished; CE shell message, not a fixed Win32 ABI id).
* WM_SYSCOPYDATA (aa453912; Header Pwinuser.h, CE 2.12+): shape
  wParam = data type (WMSCD_CHAR_RANKED_ALTS, the only defined type) /
  lParam = PCOPYDATASTRUCT (winuser.h, M31); "no counterpart on
  Windows-based desktop platforms", reserved for system components.
  The home Pwinuser.h belongs to the deferred OEM layer, so the shape
  is recorded in sip.h (note (e)) and the name is held.
* KEY_STATE_FLAGS / KeyStateDownFlag (Keybd.h, page ms902150 exists):
  referenced by SendCharEvents prose; the printed signature types the
  parameters UINT / UINT*, so no dependency is needed; the Keybd.h
  batch stays deferred (winuser.h note unchanged).
* KEYEVENTF_KEYUP / KEYEVENTF_SILENT: SendVirtualKey dwFlags names,
  published without values (held set; cf. the keybd_event record in
  winuser.h, whose dwFlags names KEYEVENTF_EXTENDEDKEY /
  KEYEVENTF_KEYUP -- also values-held).

### Recorded-not-defined (held sets; names published, values not)

SIPF_ON / SIPF_OFF (SipShowIM), SIPF_DOCKED / SIPF_LOCKED / SIPF_OFF /
SIPF_ON (SIPINFO.fdwFlags and IMINFO.fdwFlags -- the IMINFO table's
"SIP_OFF" spelling recorded verbatim), SIP_STATUS_AVAILABLE /
SIP_STATUS_UNAVAILABLE (SipStatus), IM_POSITION / IM_WIDEIMAGE /
IM_NARROWIMAGE (WM_IM_INFO), WMSCD_CHAR_RANKED_ALTS (WM_SYSCOPYDATA),
LMDATA_SYMBOL_* / LMDATA_SKIP_* / LMDATA_SCORE_* (12, LMDATA.flags),
KEYEVENTF_KEYUP / KEYEVENTF_SILENT (SendVirtualKey).  The message
identifiers WM_IM_INFO and WM_SYSCOPYDATA are themselves held (no
published numeric values).

### Verification

* `make check` GREEN (TU m51 exercises all 9 Sip* functions + the
  SipEnumIMProc callback shape + the IMENUMPROC carrier; 4 size
  asserts: SIPINFO 48, IMENUMINFO 536, IMINFO 40, LMDATA 24 --
  pointer-guarded, fired by the CE targets in crosscheck).
* `make crosscheck` GREEN on all six targets (real LLVM-WinCE clang,
  `-Werror`; the two new headers standalone + full TU).
* `make e2e` GREEN: the M51 consumer unit links 9 Sip* calls against
  def/coredll-doc.def; asserts Symbol: SipGetInfo + SipShowIM imports
  on all six images (coredll.dll).

Export surface: `def/coredll-doc.def` 602 -> **611** exports (+9 Sip*
functions; no new def file -- the Uuid.lib interface rows produce no
def, gen-doc-def reports 35 co-listed pages skipped).  Header count
35 -> 37; def count 39 (unchanged).

## M52 -- OEM keyboard layer + derived-value policy (new headers keybd.h, pwinuser.h; Kbdui.lib / Coredll.lib / Aygshell.lib)

Scope: two parts.  (1) Application of the owner-granted derived-value
policy (implement an unpublished value ONLY when it is derivable from
official public information, with the derivation path recorded):
a systematic sweep of every held value set against the remaining
official sources.  (2) The deferred OEM keyboard unit the M26 note
promised (Pwinuser.h / Keybd.h leaves of the Keyboard Reference and
Keyboard Driver DDI books) plus the never-harvested CE 5.0 Virtual-Key
Codes tables.

### Derivation sweep -- sources checked (negative results recorded)

* CE 5.0 pages + CE 6.0 twins: names only (the doc generation prints
  flag tables without value columns) -- known from M50/M51.
* CE .NET (pages4 catalog): the archived CE .NET product documentation
  has NO AYGShell / SIP / Keyboard-Reference book (its Shell section is
  OS-design pages only) -- no older-generation value source exists
  there.
* Windows Mobile 6.5 official documentation: retired by Microsoft to
  the official Download Center CHM
  (download.microsoft.com/download/d/5/3/d532530a-507f-488e-9747-1f8757071d92/windowsmobile6.5.chm,
  linked from the learn.microsoft.com archive page dn887939).  All
  16,642 pages were extracted and every held-set token was grepped for
  a nearby published value.  Result: the WM 6.5 documentation is the
  same names-only generation for every flag/message set -- EXCEPT the
  "Shell Enumerations > (Declaration)" pages, which publish complete
  enum bodies with values (SIPSTATE, SHIC_FEATURE; the SHNP twin
  matches the CE page), and the "Keys and Key Codes for Windows
  Mobile" page, which publishes the VK_APP1..6 assignments and the
  VK_F22 <-> VK_KEYLOCK cell mapping.  The 31 inspected WM pages are
  preserved in the corpus pageswm/ tree.
* Desktop Win32 references (learn.microsoft.com/windows/win32/api):
  publish values for fixed-ABI identifiers shared with CE
  (KEYEVENTF_EXTENDEDKEY/KEYUP of keybd_event; the INPUT type values).
  The two pages read are preserved in the corpus pagesw/ tree.

### Derivation ledger (values implemented this milestone)

| item | CE grounding (name) | derivation source (value) | value(s) |
|---|---|---|---|
| SIPSTATE enum + SHSipPreference | aa453741 (signature, aygshell.h/aygshell.lib, CE 3.0+) | WM 6.5 "SIPSTATE" (Declaration) page: full enum body with values; Requirements "Windows Embedded CE 3.0 and later / Header shellapi.h (Aygshell.h on PPC 2000-2002) / Library aygshell.lib" | SIP_UP=0, SIP_DOWN=1, SIP_FORCEDOWN=2, SIP_UNCHANGED=3, SIP_INPUTDIALOG=4; releases the M50 hold |
| SHIC_FEATURE enum | aa453701/aa453736 ("a value of the SHIC_FEATURE enumeration") | WM 6.5 "SHIC_FEATURE" (Declaration) page: full enum body with values; Requirements "Header aygshell.h / Windows Embedded CE .NET 4.0 and later" | RESTOREDEFAULT=0, AUTOCORRECT=0x1, AUTOSUGGEST=0x2, HAVETRAILER=0x3, CLASS=0x4 |
| VK_APP1..VK_APP6 | aa453734 remarks (names) | WM 6.5 "Keys and Key Codes for Windows Mobile": "0xC1 VK_APP_FIRST / VK_APP1 .. 0xC6 VK_APP6 / VK_APP_LAST"; keys undefined for CE, overridden as application keys in WM | 0xC1..0xC6 (in aygshell.h; VK_APP_FIRST/LAST alias spellings recorded, not defined) |
| VK_KEYLOCK | ms927178 (value cell prints "F22" = the VK_F22 row) | WM 6.5 key table maps 0x85 to both VK_F22 (CE constant) and VK_KEYLOCK (WM constant) | 0x85 |
| KEYEVENTF_EXTENDEDKEY / KEYEVENTF_KEYUP | aa453245 (names) | desktop keybd_event reference (winuser/ns/nf pages, values 0x0001/0x0002); fixed Win32 keyboard-input ABI (same policy family as the M29 WM_* fixed-ABI values) | 0x0001 / 0x0002 |
| INPUT_MOUSE / INPUT_KEYBOARD / INPUT_HARDWARE | ms909851 / ms932719 (names; INPUT_HARDWARE unsupported on CE) | desktop INPUT structure reference (0/1/2); fixed SendInput ABI | 0 / 1 / 2 |

### Held after derivation analysis (no unique public derivation)

* KEY_STATE_FLAGS values (ms902150): the reserved-entry names carry
  hex suffixes (Reserved4/8/10/20, Reserved40000/400/200/100) that pin
  the first six entries contiguously (0x1..0x20) but are mutually
  inconsistent with any single contiguous assignment of the printed
  33-entry table order -- multiple assignments fit, so no unique
  derivation exists.  The TYPE ships (typedef UINT32
  KEY_STATE_FLAGS, verbatim); all 33 flag names recorded in keybd.h.
  (WM 6.5 prints the identical names-only table.)
* LMDATA_* flags (aa453406): the page's memory-dump example prints
  0x00000102 = LMDATA_SYMBOL_WORD | LMDATA_SCORE_DWORD -- one equation,
  two unknowns; every split of 0x102 between the two names (and the
  remaining ten flags) is underdetermined.  Held.
* No published value anywhere (CE 5.0 / CE 6.0 / WM 6.5 / CE .NET n/a
  / desktop n/a): SHIDIF_*, SHCMBF_*, SHRG_*, SHFS_*, SHDB_*, SHNF_*,
  SHNUM_*, SHCMBM_* (message values), NMN_*, SIPF_*, SIP_STATUS_*,
  IM_POSITION / IM_WIDEIMAGE / IM_NARROWIMAGE, WMSCD_CHAR_RANKED_ALTS,
  SHCNE_* / SHCNF_*, GN_CONTEXTMENU, SHA_INPUTDIALOG, KEYEVENTF_SILENT,
  SPI_GETSIPINFO / SPI_SETSIPINFO / SPI_GETCURRENTIM / SPI_SETCURRENTIM,
  the WM_FILECHANGEINFO / WM_IM_INFO / WM_SYSCOPYDATA message
  identifiers, KBDI_* identifiers.  (The whole-CHM grep for a hex value
  near any of these tokens returns only the LMDATA example.)

### OEM keyboard unit (direct CE pages, no derivation)

* ms927178 "Virtual-Key Codes" (CE 5.0): the full CE virtual-key table
  WITH hexadecimal values -- standard table (VK_LBUTTON 0x01 ..
  VK_OEM_CLEAR 0xFE), the Microsoft-assigned OEM table (VK_OEM_SCROLL
  0x91 -- same cell as VK_SCROLL, recorded -- VK_OEM_1 0xBA ..
  VK_OEM_102 0xE2) and the East-Asian IME DBE table (VK_DBE_* 0xF0..
  0xFB).  ~100 constants added to winuser.h; the table's range rows
  (unassigned/OEM-reserved cells) are recorded in the header comment.
  This is the first direct CE-page grounding for VK_* (the set was
  entirely absent from the tree).
* aa452679 "Manufacturer-specific Virtual-Key Codes" (CE 5.0): NEC
  PC-9800 (VK_OEM_NEC_*), Nokia/Ericsson (VK_OEM_F17..F24 = 0x80..0x87,
  VK_ERICSSON_BASE 0xE8 and the chorded VK_OEM_RESET..VK_OEM_BACKTAB
  set published as base-relative expressions -- defined verbatim as
  published), Fujitsu/OASYS (VK_OEM_FJ_*, VK_OEM_OAS_1..29) and ICO
  (VK_ICO_*) assignments.  All values as published; numeric collisions
  with the standard table are per-device range reuse, noted.
* ms902150 "KEY_STATE_FLAGS" (Keyboard Driver DDI Data Types; Keybd.h;
  CE 1.0+): typedef UINT32 KEY_STATE_FLAGS (new include/keybd.h; the
  UINT32 base type is added to windef.h, printed verbatim by the page);
  flag values held (above).
* aa453186 "GET_FOREGROUND_INFO" (Keyboard Structures; Pwinuser.h; CE
  .NET 4.2+; "only available to OEMs"): tagGetForegroundInfo, 9
  members, 32-bit size 36 TU-asserted; new include/pwinuser.h.
* ms929241 GetForegroundInfo (Pwinuser.h; "Linked during platform
  build"), ms929242 GetForegroundKeyboardLayoutHandle and ms929243
  GetForegroundKeyboardTarget (Pwinuser.h; "Linked during build"):
  OEM-only, no import-library row -> declared, excluded from defs
  (documented; the TU exercises them compile-only).
* aa453955 GetAsyncShiftFlags (Pwinuser.h; Kbdui.lib; CE .NET 4.2+)
  -> def/kbdui-doc.def.
* aa453246 KeybdGetDeviceInfo (Pwinuser.h; Coredll.lib; CE 1.0+):
  iIndex takes the KBDI_* identifiers (names held) -> coredll-doc.def.
* ms911936 PostKeybdMessage (Header: Winuser.h; Link Library:
  Kbdui.lib; CE 2.0+): declared in winuser.h.  CORRECTION of the M26
  inventory note, which had filed it under Pwinuser.h: the page's
  Requirements row is Winuser.h (the M26 note followed the Keybd.h
  parameter types instead); the winuser.h comment block is fixed and
  the correction is recorded here.
* SendInput (ms932719) / INPUT (ms909851): already shipped since M26;
  the type constants INPUT_MOUSE/INPUT_KEYBOARD/INPUT_HARDWARE are now
  defined (derived values, ledger above) and the CE remark "Windows CE
  does not support the INPUT_HARDWARE value" is recorded.

### WM 6.5 findings recorded, not shipped (this tree is CE)

* NMRGINFO (aygshell.h, CE 3.0+) and NM_RECOGNIZEGESTURE (commctrl.h,
  CE .NET 4.2+): documented in the WM 6.5 reference with CE
  availability rows but absent from the CE 5.0 AYGShell book -- queued
  as candidates for a WM-sourced follow-up batch (see docs/README
  roadmap note).
* The WM VK_T* navigation-constant mapping (VK_TBACK 0x08 ..
  VK_VOICEDIAL 0x87, sharing cells with the CE VK_* constants) and the
  VK_DONE / VK_MOJI chorded codes: Windows Mobile-only spellings of
  shared CE cells, recorded in the corpus pageswm/ tree; not defined in
  this CE tree.
* The WM SHNOTIFICATIONDATA layout extension confirms the M50 note:
  the SOFTKEYMENU / SOFTKEYNOTIFY / NOTIF_NUM_SOFTKEYS types stay
  unpublished.

### Verification

* `make check` GREEN (TU m52: 18 published-value spot asserts + the
  SIPSTATE / SHIC_FEATURE / VK_APP / KEYEVENTF / INPUT_ derived-value
  asserts + GET_FOREGROUND_INFO size 36 + PostKeybdMessage /
  GetAsyncShiftFlags / KeybdGetDeviceInfo / GetForegroundInfo /
  GetForegroundKeyboardLayoutHandle / GetForegroundKeyboardTarget /
  SHSipPreference / SHSetAppKeyWndAssoc(VK_APP1) shaped usage).
* `make crosscheck` GREEN on all six targets (37 headers standalone +
  full TU, `-Werror`).
* `make e2e` GREEN: the M52 consumer unit links PostKeybdMessage +
  GetAsyncShiftFlags (kbdui.dll), KeybdGetDeviceInfo (coredll.dll) and
  SHSipPreference (aygshell.dll); asserts Name: kbdui.dll + the three
  symbols + Symbol: SHSipPreference on all six images.

Export surface: `def/kbdui-doc.def` 6 -> **8** (+GetAsyncShiftFlags,
PostKeybdMessage), `def/coredll-doc.def` 611 -> **612** (+
KeybdGetDeviceInfo), `def/aygshell-doc.def` 33 -> **34** (+
SHSipPreference, M50 hold released by derivation).  Header count
37 -> 39; def count unchanged at 39 (kbdui-doc.def existed since
M26).

## M53 -- Standard Shell Reference book + WM gesture supplement (new headers shtypes.h, shobjidl.h, cpl.h, shelwapi.h, windowsx.h, commdlg.h; Ceshell.lib / Coredll.lib / Shmisc.lib)

Source book: CE 5.0 "Shell and User Interface > Shell > Shell
Reference > **Standard Shell Reference**" (82 pages harvested via
tools/manifests/stdshell.manifest: 21 functions + 2 callbacks, 10
structures, 6 interfaces / 33 method pages, 1 enumeration, 2 macros,
17 messages).  Supplement: the WM 6.5 documentation pages for NMRGINFO,
GN_CONTEXTMENU and NM_RECOGNIZEGESTURE (the gesture items absent from
every CE-side tree -- verified against the embedded toc.json and all
three catalog snapshots; preserved in the corpus pageswm/ tree).

### Pages and header homes (Requirements rows)

* **shtypes.h** (new): SHITEMID aa453718 (CE 1.0+), STRRET ms940377
  (CE .NET 4.2+).
* **shlobj.h** (extended): ITEMIDLIST aa453244 (CE 1.0+), BROWSEINFO
  aa452901 + BrowseCallbackProc aa452900 + SHBrowseForFolder aa453669
  (CE .NET 4.0+), SHBindToParent aa453668 + SHGetDesktopFolder
  aa453697 + SHGetSpecialFolderLocation aa453706 (CE .NET 4.2+),
  SHGetMalloc aa453702 (CE 2.12+), SHGetDocumentsFolder aa453698
  (CE 3.0+; the row prints the multi-header list "shlobj.h,
  commctrl.h" with ceshell.lib -- first-listed home used, co-listing
  recorded).
* **shobjidl.h** (new): SHGNO aa453709 (CE .NET 4.2+); IDropTarget
  ms929937..ms929940, IPersistFolder ms909861, IShellFolder
  ms909868..ms909876 (CE .NET 4.2+), IShellView ms909882..ms909893,
  ITaskbarList aa453239..aa453243, ITaskbarList2 aa453238 (CE 5.0+).
  All method pages print "Shobjidl.h, Shobjidl.idl" + "Link Library:
  Implementation dependent" -- interface records only (M44 objbase.h
  policy: opaque forward declarations + verbatim method-signature
  comments; no invented vtables, no def entries).
* **shellapi.h** (extended): NOTIFYICONDATA ms911889, SHELLEXECUTEINFO
  aa453685, SHFILEINFO aa453689, SHFILEOPSTRUCT aa453691 (structures);
  Shell_NotifyIcon aa453686, SHGetFileInfo aa453700 (no Link Library
  row on either CE 5.0 page -- def-less by the row-driven def policy;
  the WM 6.5 SHGetFileInfo page prints an aygshell.lib row, a
  different platform layer, recorded not used), SHGetPathFromIDList
  aa453704 (Ceshell.lib; the page types the path buffer LPSTR --
  recorded verbatim), SHGetShortcutTarget aa453705 / SHAddToRecentDocs
  aa453667 / SHCreateShortcut aa453680 / SHCreateShortcutEx aa453681 /
  ShellExecuteEx aa453684 / SHGetSpecialFolderPath aa453707 /
  SHLoadDIBitmap aa453720 (Coredll.lib), SHFileOperation aa453690
  (Ceshell.lib), SHShowOutOfMemory aa453739 (Shmisc.lib).
* **cpl.h** (new): CPlApplet ms908154 (Link Library "Developer
  implemented" -- no def), CPLINFO ms908158, NEWCPLINFO ms931468
  (CE 1.0+).
* **shelwapi.h** (new): StrRetToBuf ms940378 (CE .NET 4.2+;
  Ceshell.lib).
* **windowsx.h** (new): MapWindowRect ms911791, SetDlgMsgResult
  ms940022 (CE 1.0+; macros).
* **commdlg.h** (new): WM_CHOOSEFONT_GETLOGFONT ms914112 (CE .NET
  4.0+).
* **winuser.h** (extended): WM_HELP aa453866, WM_HIBERNATE aa453867,
  WM_KEYFIRST aa453874, WM_KEYLAST aa453875 (CE 1.0+; the four
  Standard Shell Messages whose Requirements rows print Winuser.h).
* **aygshell.h** (extended): NMRGINFO + GN_CONTEXTMENU record (WM 6.5
  pages, aygshell.h / aygshell.lib / CE 3.0+ -- no CE-side page
  exists).
* **commctrl.h** (extended): NM_RECOGNIZEGESTURE record (WM 6.5 page,
  commctrl.h / CE .NET 4.2+ -- no CE-side page exists).

### Derived-value ledger (M52 policy; paths recorded)

CE-page-published (no derivation needed):

* **CSIDL (15)** -- published with values in the aa453707
  SHGetSpecialFolderPath Windows Mobile Remarks table: CSIDL_DESKTOP
  0x0000, CSIDL_PROGRAMS 0x0002, CSIDL_PERSONAL 0x0005,
  CSIDL_FAVORITES 0x0006, CSIDL_STARTUP 0x0007, CSIDL_RECENT 0x0008,
  CSIDL_DESKTOPDIRECTORY 0x0010, CSIDL_FONTS 0x0014, CSIDL_MYMUSIC
  0x000D, CSIDL_MYVIDEO 0x000E, CSIDL_APPDATA 0x001A, CSIDL_WINDOWS
  0x0024, CSIDL_PROGRAM_FILES 0x0026, CSIDL_MYPICTURES 0x0027,
  CSIDL_PROFILE 0x0028.
* **SFGAO (25)** -- published with values in the ms909872
  IShellFolder::GetAttributesOf "Flag (value)" tables: CANCOPY
  0x00000001, CANMOVE 0x00000002, CANLINK 0x00000004, CANRENAME
  0x00000010, CANDELETE 0x00000020, HASPROPSHEET 0x00000040,
  DROPTARGET 0x00000100, CAPABILITYMASK 0x00000177, CANMONIKER
  0x00400000, LINK 0x00010000, SHARE 0x00020000, READONLY 0x00040000,
  GHOSTED 0x00080000, DISPLAYATTRMASK 0x000F0000, HASSUBFOLDER
  0x80000000, CONTENTSMASK 0x80000000, NEWCONTENT 0x00200000,
  NONENUMERATED 0x00100000, VALIDATE 0x01000000, REMOVABLE 0x02000000,
  BROWSABLE 0x08000000, COMPRESSED 0x04000000, FILESYSANCESTOR
  0x10000000, FOLDER 0x20000000, FILESYSTEM 0x40000000.
* **SHGDN_NORMAL = 0** -- published text on aa453709 (and the CE 6.0
  twin ee504556): "The numeric value of SHGDN_NORMAL is zero".

Desktop-fixed-ABI derivations (CE publishes the name + semantics, no
CE value, no conflict; desktop reference page preserved in the corpus
pagesw/ tree, listed in tools/manifests/stdshell-desktop.manifest):

* **NIF_MESSAGE/NIF_ICON/NIF_TIP = 0x1/0x2/0x4** -- desktop
  NOTIFYICONDATAA page (ms911889 CE names).
* **NIM_ADD/NIM_MODIFY/NIM_DELETE = 0x0/0x1/0x2** -- desktop
  Shell_NotifyIconW page (aa453686 CE names).
* **SEE_MASK_NOCLOSEPROCESS = 0x40, SEE_MASK_FLAG_NO_UI = 0x400** --
  desktop SHELLEXECUTEINFOA page (aa453685 CE names; CE 1.0/1.01 do
  not support fMask flags at all per the CE page).
* **SE_ERR_FNF 2 / PNF 3 / ACCESSDENIED 5 / OOM 8 / SHARE 26 /
  ASSOCINCOMPLETE 27 / DDETIMEOUT 28 / DDEFAIL 29 / DDEBUSY 30 /
  NOASSOC 31 / DLLNOTFOUND 32** -- desktop SHELLEXECUTEINFOA hInstApp
  table (aa453685 CE names, "less than or equal to 32" per the CE
  page).
* **SHGFI_LARGEICON 0 / SMALLICON 0x1 / OPENICON 0x2 /
  SHELLICONSIZE 0x4 / PIDL 0x8 / USEFILEATTRIBUTES 0x10 / ICON 0x100 /
  DISPLAYNAME 0x200 / TYPENAME 0x400 / ATTRIBUTES 0x800 /
  ICONLOCATION 0x1000 / EXETYPE 0x2000 / SYSICONINDEX 0x4000 /
  LINKOVERLAY 0x8000 / SELECTED 0x10000** -- desktop SHGetFileInfoW
  page (aa453700 CE names).
* **BIF_STATUSTEXT 0x4 / BIF_EDITBOX 0x10 / BIF_VALIDATE 0x20** --
  desktop BROWSEINFOA page (aa452901 CE names).
* **SVSI_DESELECT 0 / SELECT 0x1 / EDIT 0x3 / DESELECTOTHERS 0x4 /
  ENSUREVISIBLE 0x8 / FOCUSED 0x10 / TRANSLATEPT 0x20 /
  SELECTIONMARK 0x40 / POSITIONITEM 0x80 / CHECK 0x100** -- desktop
  _SVSIF page (ms909891 CE names).
* **SVGIO_BACKGROUND 0 / SELECTION 0x1 / ALLVIEW 0x2 / CHECKED 0x3 /
  TYPE_MASK 0xF / FLAG_VIEWORDER 0x80000000** -- desktop _SVGIO page
  (ms909887 CE names).

CE-internal derivation:

* **WM_KEYFIRST = 0x0100** -- the keyboard-message filter low bound is
  the first keyboard message; WM_KEYDOWN = 0x0100 is CE-published
  (aa453873, winuser.h).  WM_KEYLAST stays held (see below).

Formula derivation:

* **WM_CHOOSEFONT_GETLOGFONT = (WM_USER + 1) = 0x0401** -- the desktop
  dlgbox reference page prints the #define formula; WM_USER = 0x0400
  is CE-published (winuser.h).  Note both the desktop page and the
  CE-published DM_SETDEFID (aa452963) land on the same 0x0401 value
  (both print (WM_USER + 1)); the shared value is the documented ABI
  and is kept verbatim.

### Held after analysis (no unique public derivation)

* **SHGDN_INFOLDER / SHGDN_FOREDITING / SHGDN_FORADDRESSBAR /
  SHGDN_FORPARSING** -- the CE pages (aa453709, twin ee504556) publish
  a five-element enum body WITHOUT initializers (only SHGDN_NORMAL=0
  is stated); the desktop _SHGDNF page publishes 0x1 / 0x1000 /
  0x4000 / 0x8000.  The bare sequential enum body and the desktop bit
  values are both admissible readings (the two-group modifier
  semantics of the page's remarks argue for the bit values, the
  syntax block for sequential) -- not uniquely derivable.  Desktop
  values recorded here for the future on-device readback.
* **STRRET_CSTR / STRRET_OFFSET / STRRET_WSTR** -- names-only on the
  CE page ms940377 AND on the desktop STRRET page (checked; preserved
  in pagesw/).  No official value publication exists.
* **FO_COPY / FO_DELETE / FO_MOVE / FO_RENAME** and the 14 **FOF_***
  names (ALLOWUNDO, FILESONLY (ns), MULTIDESTFILES (ns),
  NO_CONNECTED_ELEMENTS (ns), NOCONFIRMATION, NOCONFIRMMKDIR,
  NOCOPYSECURITYATTRIBS (ns), NOERRORUI, NORECURSION (ns),
  RENAMEONCOLLISION, SILENT, SIMPLEPROGRESS, WANTMAPPINGHANDLE (ns),
  WANTNUKEWARNING (ns)) -- names-only on aa453691 and on the desktop
  SHFILEOPSTRUCTA page (checked; preserved in pagesw/).
* **SHARD_PATH / SHARD_PIDL** -- names-only on aa453667 and on the
  desktop SHAddToRecentDocs page (checked).
* **BFFM_INITIALIZED / SELCHANGED / SETSTATUSTEXT / ENABLEOK /
  SETSELECTION / VALIDATEFAILED** -- names-only on aa452872..aa452877
  and aa452900; the desktop SHBrowseForFolderA page is valueless
  (checked).
* **CPL_INIT / GETCOUNT / DBLCLK / NEWINQUIRE / STOP / EXIT** and
  **CPL_DYNAMIC_RES** -- names-only on ms908154..ms908161, ms908158;
  no desktop reference page publishes values.
* **WM_HELP, WM_HIBERNATE** -- names-only on aa453866 / aa453867 (and
  WM_HIBERNATE has no desktop counterpart).
* **WM_KEYLAST** -- aa453875 publishes no value; the CE-published
  keyboard block ends at WM_SYSDEADCHAR 0x0107 (aa453913) but a
  one-past bound of 0x0108 also fits the "filter for keyboard
  messages" contract; no official doc resolves the ambiguity.
* **CSIDL_BITBUCKET / CONTROLS (ns) / DRIVES / NETHOOD (ns) / NETWORK
  / PRINTERS (ns) / SENDTO (ns) / STARTMENU / TEMPLATES (ns)** -- the
  nine aa453706 names absent from the aa453707 value table; the
  desktop CSIDL reference page publishes no values (checked,
  preserved in pagesw/).
* **SHGFI_SELECTICON** -- aa453700 Windows Mobile-only selector; no
  desktop counterpart.
* **SVSI_NOSTATECHANGE** -- ms909891 CE-only selector; absent from the
  desktop _SVSIF list.
* **SVUIA_ACTIVATE_FOCUS / ACTIVATE_NOFOCUS / DEACTIVATE /
  IN_PLACEACTIVATE** -- ms909893 names-only; no API reference page
  (CE or desktop) publishes values (a debugger-walkthrough page's
  inline comment showing SVUIA_DEACTIVATE = 0 is not an API reference
  and grounds nothing else).
* **MK_ALT / MK_CONTROL / MK_LBUTTON / MK_MBUTTON / MK_RBUTTON /
  MK_SHIFT** and **DROPEFFECT_COPY / MOVE / LINK** -- names referenced
  by the IDropTarget method pages (ms929937..ms929940) without value
  tables; the DROPEFFECT enumeration belongs to the unharvested OLE
  drag-drop book (future milestone candidate).
* **FILEOP_FLAGS type width** -- the type name is printed by the CE
  5.0 / CE 6.0 (ee505480) / desktop syntax blocks but no doc
  publishes its width; WORD is adopted because it is layout-neutral
  at the fFlags offset (16-bit + alignment padding places
  fAnyOperationsAborted at the same offset and yields the same
  sizeof as a 32-bit member on ARM and x86 -- TU-asserted
  sizeof(SHFILEOPSTRUCT) == 32).  Width-held type, recorded.
* **SetDlgMsgResult macro expansion** -- ms940022 documents the name,
  the three parameters and "maps to the SetWindowLong function" but
  publishes no expansion (its parameter text is copied from
  SetWindowLong and no DWLP_MSGRESULT mechanism is documented for
  CE); recorded as a held macro, not defined.  MapWindowRect
  (ms911791, "calls MapWindowPoints") IS implemented: the forced
  geometry (a RECT is a 2-point array) plus the published parameter
  list determine the expansion.
* Dangling type/interface references from the interface method pages
  (no CE 5.0 pages of their own, recorded in shobjidl.h comments):
  **SHCONTF** (ms909871 references "the SHCONTF enumerated type";
  no CE page, no names listed), **IEnumIDList** (printed "IENUMIDLIST**"),
  **IShellBrowser**, **FOLDERSETTINGS**, **LPFNADDPROPSHEETPAGE**.

### CE-specific findings recorded in the headers

* NOTIFYICONDATA (ms911889): CE-specific short layout -- no szInfo /
  uTimeout / uVersion members; szTip is an explicit WCHAR[64].
* SHELLEXECUTEINFO (aa453685): lpDirectory "Not supported. Set to
  zero."; lpIDList / lpClass / hkeyClass / dwHotKey / hIcon
  "Ignored"; fMask flags unsupported on CE 1.0/1.01.
* SHFILEOPSTRUCT (aa453691): fAnyOperationsAborted and hNameMappings
  "Not supported"; FOF_* "(ns)" rows marked Not supported.
* NEWCPLINFO (ms931468): dwFlags / dwHelpContext / szHelpFile
  "Ignored".
* SHCreateShortcut / SHCreateShortcutEx (aa453680/aa453681): the
  pages state the functions "are not prototyped correctly in
  Shellapi.h: they return a BOOL instead of a DWORD" -- prototypes
  kept verbatim (DWORD) with the note.
* SHGetSpecialFolderPath (aa453707): with the AYGShell extensions the
  function returns FALSE even on success (Pocket PC 2002 era) --
  documented in the header comment.
* SHGetFileInfo (aa453700): the CE file-attribute additions
  FILE_ATTRIBUTE_INROM and FILE_ATTRIBUTE_ROMMODULE are documented
  (names recorded; values not published on this page -- the
  FILE_ATTRIBUTE_* value set belongs to the file-API book).
* SHAddToRecentDocs (aa453667): CE caps the recent-documents list at
  ten entries.

### Verification

* `make check` GREEN (TU m53: 32 published/derived-value spot asserts
  -- CSIDL/SFGAO/SHGDN_NORMAL tables, NIF/NIM/SEE_MASK/SE_ERR/SHGFI/
  BIF/SVSI/SVGIO derived sets, WM_KEYFIRST, WM_CHOOSEFONT_GETLOGFONT
  -- + 11 32-bit struct sizes (CPLINFO 16, NEWCPLINFO 468,
  SHFILEOPSTRUCT 32, BROWSEINFO 32, SHFILEINFO 692, NOTIFYICONDATA
  152, SHELLEXECUTEINFO 60, SHITEMID 4, ITEMIDLIST 4, NMRGINFO 24)
  + shaped usage of the full Ceshell/Coredll/Shmisc import surface +
  the def-less pair (Shell_NotifyIcon, SHGetFileInfo) host-compiled).
* `make crosscheck` GREEN on all six targets (47 headers standalone +
  full TU, `-Werror`).
* `make e2e` GREEN: the M53 consumer unit links the Ceshell.lib
  (SHBrowseForFolder, SHGetSpecialFolderLocation, StrRetToBuf,
  SHGetPathFromIDList, SHGetDocumentsFolder, SHGetMalloc,
  SHFileOperation, SHBindToParent, SHGetDesktopFolder), Coredll.lib
  (ShellExecuteEx, SHGetSpecialFolderPath, SHAddToRecentDocs,
  SHCreateShortcut, SHGetShortcutTarget, SHLoadDIBitmap) and
  Shmisc.lib (SHShowOutOfMemory) names; asserts Name: ceshell.dll +
  Name: shmisc.dll + Symbol: SHBrowseForFolder /
  SHGetSpecialFolderLocation / StrRetToBuf / SHShowOutOfMemory /
  ShellExecuteEx / SHGetSpecialFolderPath on all six images.

Export surface: `def/ceshell-doc.def` **new, 9 exports**,
`def/shmisc-doc.def` **new, 1 export**, `def/coredll-doc.def`
612 -> **619** (+SHAddToRecentDocs, SHCreateShortcut,
SHCreateShortcutEx, ShellExecuteEx, SHGetShortcutTarget,
SHGetSpecialFolderPath, SHLoadDIBitmap).  Header count 39 -> **47**;
def count 39 -> **41**.  aygshell (34) and kbdui (8) unchanged;
Shell_NotifyIcon / SHGetFileInfo / CPlApplet / BrowseCallbackProc are
deliberately def-less (no Link Library row / developer-implemented /
callback).

## M54 -- Common Controls batch 1 + LDAP Client + RDP virtual channels (new headers winldap.h, winber.h, cchannel.h, discodlg.h; Wldap32.lib / Commctrl.lib / Commdlg.lib / Fileopen.lib)

Three queues landed together per the multi-queue directive.  Source
books: CE 5.0 "Shell and User Interface :: Shell :: Common Controls
Reference" batch 1 (the Animation, CapEdit, Command Bands, Command
Bars, Common Dialog Boxes, Common Control, Custom Draw, Progress,
SbEdit, Status Bars, Toolbar, ToolTips, Trackbar and Up-Down
sub-books, 293 leaves, tools/manifests/cc-*.manifest) plus the Rebar
REBARBANDINFO dependency (cc-cmdbands-dep.manifest); CE 5.0
"Communications and Services :: Network Protocols :: Lightweight
Directory Access Protocol (LDAP) Client :: LDAP Reference" (124
leaves, ldap.manifest); CE 5.0 "Remote Desktop Protocol :: RDP
Reference" (105 leaves, rdp.manifest).  Every page was fetched with
tools/ce-fetch.py (0 errors) and 442 CE 6.0 (v=winembedded.60) twins
with whitespace-preserved prototypes were fetched as signature
cross-reads (m54-ce60.manifest; the twin ids are noted per
declaration where the CE 5.0 print is ambiguous).  rows.json
2233 -> 2753 CE 5.0 records + 453 twin records.

### Queue A: Common Controls batch 1 (commctrl.h extension + commdlg.h full book)

* INITCOMMONCONTROLSEX (ms909850, 8 bytes), InitCommonControls
  (ms909848, Commctrl.lib, CE 2.0+), InitCommonControlsEx (ms909849);
  the twelve ICC_* class flags are names-only (held).
* Notification records: NMKEY (ms931482, 20), NMMOUSE (ms931655, 28),
  NMCUSTOMDRAW (ms931470, 48; member lItemlParam [sic] and the
  missing member semicolon kept as printed), NMTTCUSTOMDRAW
  (ms911865, 52), NMTOOLBAR (ms911863, 44), NMUPDOWN (ms911870, 20);
  NMHDR itself stays in winuser.h (M50).  The CDDS_*/CDIS_*/TBCD_*,
  NM_* notification values and NM_CUSTOMDRAW are names-only (held).
* Toolbar structures: TBBUTTON (ms940418, 20) + LPCTBBUTTON,
  TBBUTTONINFO (ms940420, 32; both CE 5.0 and twin ee503445 print the
  typedef names TBBUTTONINFOA/LPTBBUTTONINFOA -- the unsuffixed alias
  is bridged from the TB_GETBUTTONINFO page ms940430, the CHOOSEFONT
  model), TBADDBITMAP (ms940414, 8; member type printed "INSTANCE"
  [sic] restored as HINSTANCE), TBREPLACEBITMAP (ms913817, 20);
  CreateToolbarEx (ms908190, no Link Library row -> no def, no
  import pin).
* ToolTips structures: TOOLINFO (aa453757, 44; CE typedef names
  TTTOOLINFO/PTOOLINFO/LPTTTOOLINFO), TTHITTESTINFO (aa453819, 56),
  NMTTDISPINFO (ms911866, 188).  TTF_* flags names-only (held).
* Progress/Up-Down: PBRANGE (ms911927, 8), NMUPDONE above, UDACCEL
  (ms914067, 8), CreateUpDownControl (ms908191, no lib row -> no
  def).  PBM_*/UDM_*/UDN_* names-only (held).
* Rebar dependency: REBARBANDINFO (aa453639, 76, CE 2.0+; fetched as
  the CommandBands dependency; RBBIM_*/RBBS_* names-only, held).
* Command Bars (CE-specific, Commctrl.lib, CE 1.0+): 11 functions
  (Create/AddAdornments/AddBitmap/AlignAdornments [CE 4.0+]/
  DrawMenuBar/GetMenu/Height/InsertComboBox/InsertMenubar/
  InsertMenubarEx/Show).  The five macro pages (AddButtons,
  AddToolTips, Destroy, InsertButton, IsVisible) print signatures but
  no macro bodies -- held, signatures recorded in commctrl.h.
  CMDBAR_HELP/CMDBAR_OK, IDB_STD_*/IDB_VIEW_*, STD_*/VIEW_* image
  indices names-only (held).
* Command Bands (CE-specific, Commctrl.lib, CE 2.0+): 6 functions
  (Create/AddAdornments/AddBands/GetCommandBar/
  GetRestoreInformation/Show) + COMMANDBANDSRESTOREINFO (ms908125,
  20).  CommandBands_Height macro (ms908124) body not printed: held.
* Status Bars: CreateStatusWindow (ms908188 -- text parameter
  printed LPSTR, kept verbatim) and DrawStatusText (aa452976 -- text
  parameter LPCWSTR), both Commctrl.lib CE 1.0+.  SB_*/SBT_*/SBN_*
  names-only (held).
* Class names: WC_CAPEDIT L"CAPEDIT" (aa452920), WC_SBEDIT
  L"sbedit" (ms939903).  ANIMATE_CLASS not published anywhere (held).
* Macros with printed bodies: INDEXTOSTATEIMAGEMASK(i) ((i)<<12)
  (ms909844); FORWARD_WM_NOTIFY (aa453073 -- the printed body
  references (id) while the parameter is named idFrom [sic, printed
  identically by twin ee505696]; kept verbatim, the TU exercises it
  with a local id) and HANDLE_WM_NOTIFY (ms929879).
* WM_SETFONT (aa453902) / WM_GETFONT (aa452862) added to winuser.h
  at the fixed Win32 ABI values 0x0030/0x0031 (the M29 fixed-ABI
  message policy; the CE Controls Messages pages publish names +
  wParam/lParam only).  windef.h gained PTCHAR/PWCHAR/PCHAR (printed
  verbatim by the LDAP book) and FAR/NEAR (empty segmentation
  decorations printed by the common-control structure pages).
* Common Dialog Boxes book (commdlg.h): structures CHOOSECOLOR
  (ms928580, 36), CHOOSEFONT (ms928582, 60; CHOOSEFONTW/
  LPCHOOSEFONTW as printed + the unsuffixed alias bridged from the
  function page ms928581 which prints LPCHOOSEFONT; the
  ___MISSING_ALIGNMENT__ placeholder member kept verbatim [sic];
  lpLogFont typed LPLOGFONTW bridged to the wingdi.h LOGFONT --
  ms901140 already shipped with LF_FACESIZE 32), OPENFILENAME
  (ms911906, 76; ANSI-spelled string members kept as printed;
  lpfnHook printed LPOFNHOOKPROC but no CE page defines it and
  OFN_ENABLEHOOK is "Not supported" -> typed as layout-neutral
  void*), OFNOTIFY (ms911893, 20), PAGESETUPDLG (ms911910, 84),
  PRINTDLG (aa453544, 68; CE-specific layout, OS row "Windows CE 2.0
  and 2.01" -- dropped after 2.01), DEVNAMES (aa452944, 8).
  Functions: ChooseColor/CommDlgExtendedError/PageSetupDlg/PrintDlg
  (Commdlg.lib), GetOpenFileName/GetSaveFileName (Fileopen.lib,
  CE 1.0+), ChooseFont (ms928581, no Link Library row -> no def, no
  pin).  Hook pointer typedefs built from the documented hook
  signatures (M51 IMENUMPROC model); LPCFHOOKPROC printed directly by
  ms908107.  All flag families (CC_*, CF_*/FONTTYPE, OFN_*, PD_*,
  PSD_*, CDERR/PDERR, WM_PSD_*, CDM_*/CDN_*) names-only (held).
* **CC message-value hold (recorded decision):** none of the ~200
  control messages (ACM_/PBM_/SB_/TB_/TBM_/TTM_/UDM_/CEM_/
  CDN_...) publishes a numeric identifier or a WM_USER formula on any
  CE page, and the desktop Win32 controls reference publishes none
  either (verified on the PBM_SETPOS desktop page,
  pagesw/controls-pbm-setpos.html) -- every message name is recorded
  in the commctrl.h held ledger with its book, no #define (the M53
  BFFM_* precedent).

### Queue B: LDAP Client (winldap.h + winber.h, Wldap32.lib)

* Opaque handles: LDAP/PLDAP (ms891742), LDAPMessage/PLDAPMessage
  (ms892278), LDAPSearch/PLDAPSearch (ms892309), BerElement
  (ms863747, one documented member), berval -> LDAP_BERVAL/BERVAL
  (ms863826: LDAP_BERVAL/PLDAP_BERVAL/BERVAL/PBERVAL).
* Value structures: LDAPControl (ms891757, 16), LDAPMod (ms892279,
  12), LDAP_TIMEVAL (ms892315, 8), LDAPSortKey (ms892313, 12),
  LDAP_REFERRAL_CALLBACK (ms892294, 16).
* LDAP_RETCODE (ms892299): full enum with published values 0x00-0x61
  (including the double-published 0x09 LDAP_REFERRAL_V2 /
  LDAP_PARTIAL_RESULTS).
* Published values: LDAP_MOD_ADD/DELETE/REPLACE (0x00-0x02, ms892279);
  the ms893453 Session Options tables (LDAP_OPT_* 0x01-0x98 including
  the page's "LPDA_OPT_SERVER_EXT_ERROR (0x34)" [sic] spelling, the
  PING_* trio 0x36-0x38); LDAP_DEREF_* 0x00-0x03; LDAP_NO_LIMIT 0.
  LBER_USE_DER 0x01 (ms863718 page text).
* 94 functions declared and pinned (Wldap32.lib, CE .NET 4.0+): the
  full session/directory-entry/search/parse/memory/error/UTF-8
  function set of the LDAP Reference book.  Documented readings
  recorded per declaration: ldap_connect (ms891756 + ee485147)
  prints PLDAP_TIMEVAL* (pointer to PLDAP_TIMEVAL) -- kept verbatim;
  ldap_parse_extended_result (ms892289 + ee486808) prints a bare
  "LDAP Connection" (no indirection, cannot compile) -- declared as
  the connection pointer; ldap_add_ext (ms891745 + ee483743) and
  ldap_sasl_bind_s (ms892301 + ee486753) print LDAPControlA** where
  no CE page defines an LDAPControlA (ms891757 defines LDAPControl
  only) -- declared with the documented LDAPControl spelling
  (layout-identical).
* Referral callbacks: DEREFERENCECONNECTION (ms864415),
  NOTIFYOFNEWCONNECTION (ms892585), QUERYFORCONNECTION (ms892640),
  VERIFYSERVERCERT (ms897184; PCCERT_CONTEXT from wincrypt.h) --
  declared as CALLBACK function types (pages print "_cdecl" [sic],
  one underscore); QUERYCLIENTCERT (ms892639) HELD: its parameter
  type PSecPkgContext_IssuerListInfoEx (SSPI) has no CE page in the
  harvested corpus.
* HELD: ldap_sasl_bind (ms892300) -- both the CE 5.0 page and twin
  ee484725 mis-print the ldap_sasl_bind_s prototype on the
  asynchronous page; the asynchronous prototype cannot be confirmed.
  Names-only holds: LDAP_AUTH_SIMPLE/NTLM/NEGOTIATE, LDAP_SCOPE_*,
  LDAP_RES_*, LDAP_OPT_ON/OFF, LDAP_ON/OFF, LDAP_VERSION2/3,
  LDAP_CHASE_*_REFERRALS, LDAP_OPT_SIGN.
* winber.h: the 13 ber_* functions (Winber.h, Wldap32.lib) with
  LBER_USE_DER.

### Queue C: RDP (cchannel.h + discodlg.h)

* CHANNEL_DEF (aa513856, 12) with CHANNEL_NAME_LEN **derived = 7**:
  the CE pages print name[CHANNEL_NAME_LEN + 1] without a value; the
  official Microsoft open specification [MS-RDPBCGR] 2.2.1.3.4.1
  publishes name as an 8-byte array of seven ANSI characters (page
  preserved in pagesw/openspecs-msrdpbcgr-channel-def.html; path
  recorded in cchannel.h and tools/manifests/rdp-openspecs.manifest).
* CHANNEL_PDU_HEADER (aa513859, 8).  CHANNEL_OPTION_* (11) and
  CHANNEL_FLAG_FIRST/LAST/MIDDLE/ONLY **derived from [MS-RDPBCGR]**
  2.2.1.3.4.1 / 2.2.6.1.1 (pages preserved in pagesw/; MIDDLE = 0
  from the "neither FIRST nor LAST" wording, ONLY = FIRST|LAST from
  the CE ms879661 wording; the CE page's
  CHANNEL_OPTION_REMOTE_CONTROL_PERSISTENT is the spec's
  REMOTE_CONTROL_PERSISTENT 0x00100000).
* The 7 base virtual-channel entry points + 7 Ex typedefs + the two
  entry-points tables (aa513858/aa513861, 24 bytes each) + the event
  callbacks; all "Developer implemented" (no def).  The Ex function
  set and the interface container pages have no CE 6.0 twins (the
  17 no-twin titles of m54-ce60.manifest analysis).  CHANNEL_EVENT_*,
  CHANNEL_RC_*, CHANNEL_MAX_COUNT names-only (held).  VCAPITYPE
  mapped to the empty-on-CE convention (windef.h).
* discodlg.h: nine Remote Desktop ActiveX interfaces as opaque
  records with verbatim method-signature comments (66 method pages,
  M44 model; no vtables, no defs), ExtendedDisconnectReasonCode
  published in full (aa513913, 0x0000-0x010A + the 0x1000-0x7FFF
  protocol-error range recorded), ControlCloseStatus names-only
  (held).  IMsRdpClientAdvancedSettings / IMsRdpClientSecuredSettings
  property sets documented as property-description pages (ms861195/
  ms861243/ms861737/aa514412/aa514423/aa513933) -- names recorded in
  the inventory ledger, no method records.

### Verification

* `make check` GREEN (TU m54: 42 published/derived-value asserts +
  32 struct sizes split pointer-free/32-bit-guarded + shaped usage of
  the full Commctrl/Wldap32/Commdlg/Fileopen import surface, the
  def-less trio (CreateToolbarEx/CreateUpDownControl/ChooseFont)
  host-compiled, and the cchannel/discodlg record surface).
* `make crosscheck` GREEN on all six targets (51 headers standalone +
  full TU, -Werror).
* `make e2e` GREEN on all six targets; new import assertions:
  CommandBar_Create, CommandBands_Create, GetOpenFileName, ldap_init,
  ber_alloc_t (commctrl.dll/commdlg.dll/fileopen.dll/wldap32.dll
  verified in the PE import tables on x86 and ARM).
* gen-doc-def.py: the export scanner now strips comments and accepts
  pointer-returning / multi-word-return declarations (M54; this also
  fixed a latent mis-capture -- the ws2 def had carried names matched
  only inside comments) and lstrip("*") handles the attached-star
  AKARI_CE_IMPORT forms.

Export surface: `def/wldap32-doc.def` **new, 96 exports** (6 skipped:
the four declared referral callbacks are function types, QUERYCLIENTCERT
held, ldap_sasl_bind held), `def/commdlg-doc.def` **new, 4**,
`def/fileopen-doc.def` **new, 2**, `def/commctrl-doc.def` 31 ->
**52** (+21).  Header count 47 -> **51**; def count 41 -> **44**.
Corpus: pages5 2152 -> 2672, pages6 1259 -> 1702 (442 M54 twins),
pagesw 16 -> 20 (2 MS-RDPBCGR + LOGFONTW + PBM_SETPOS), rows.json
2233 -> 2753 (+ twin records), rows4.json unchanged (6361).

## M55 -- Property Sheets (new header prsht.h; def-less Prsht.h layer) + CC batch 2 harvest

* prsht.h: the CE 5.0 Property Sheets Reference book (57 leaves,
  tools/manifests/cc-propertysheets.manifest).  Structures:
  PROPSHEETPAGE (aa453562, 40, verbatim unions; ANSI-spelled string
  members kept as printed), PROPSHEETHEADER (aa453560, 40, verbatim
  unions), PSHNOTIFY (aa453576, 16).  Functions:
  CreatePropertySheetPage (ms908183), DestroyPropertySheetPage
  (aa452941), PropertySheet (aa453552) -- all Prsht.h with NO Link
  Library row on CE, so no def and no import pin (the
  Shell_NotifyIcon precedent).  Callbacks: PropSheetPageProc
  (aa453563; LPFNPSPCALLBACK built from it -- mutually recursive
  with the struct, parameter spelled via the struct tag), PropSheetProc
  (aa453565; PFNPROPSHEETCALLBACK), AddPropSheetPageProc (aa452848;
  LPFNADDPROPSHEETPAGE -- closes the M53 shobjidl.h dangling-type
  note), ExtensionPropSheetPageProc (aa453062).  HELD: the 18
  PropSheet_* macro bodies (signatures only), PSM_/PSN_ messages,
  PSP_/PSH_/PSPCB_/PSCB_/PSBTN_/PSWIZB_/ID_PS* values (names-only).
* Batch 2 harvest (for the next milestones): the remaining seven
  Common Controls sub-books fetched and preserved -- Date and Time
  Picker (36), Header (49), List-View (220), Month Calendar (54),
  Rebar (36), Tab (61), Tree View (88) = 601 CE 5.0 pages
  (cc-dateandtimepicker/cc-header/cc-listview/cc-monthcalendar/
  cc-rebar/cc-tab/cc-treeview.manifest) + 569 CE 6.0 twins
  (m55-ce60.manifest; 32 titles have no CE 6.0 twin).
* Verification: make check / crosscheck / e2e GREEN on all six
  targets (TU m55: 3 struct sizes + shaped usage of the def-less
  Prsht.h surface).

Export surface: unchanged (Prsht.h carries no Link Library rows).
Header count 51 -> **52**; def count 44.  Corpus: pages5
2673 -> 3273 (+601), pages6 1702 -> 2270 (+568 twins; one
m55-ce60.manifest title 404s -- no CE 6.0 twin page),
rows.json 2753 -> 4365 (cumulative parsed records incl. the corpus
baseline twins).

## M56 -- Common Controls batch 2 structures (commctrl.h extension; no defs)

The seven remaining Common Controls sub-books' structure layers landed
in commctrl.h (batch-2 pages fetched and preserved in M55; prototypes
cross-read against the m55-ce60.manifest twins).  No page of this
batch carries a Link Library row, so no defs and no import pins.

* Rebar: REBARINFO (aa453640, 12), NMRBAUTOSIZE (ms911836, 48),
  NMREBAR (ms911851, 28), RBHITTESTINFO (aa453620, 16).
* Header: HDITEM (ms929881, 36; HD_ITEM alias per the HDM_* message
  pages' spelling, twin ee502857 identical), HD_LAYOUT/HDLAYOUT
  (ms929882, 8), HD_HITTESTINFO/HDHITTESTINFO (ms929880, 16),
  NMHDDISPINFO (ms931478, 36), NMHEADER (ms931480, 24).
* Tab: TCITEM (ms913857, 28), TCITEMHEADER (ms913860, 24),
  TCHITTESTINFO (ms913854, 12), NMTCKEYDOWN (ms911862, 20).
* Date and Time Picker: NMDATETIMECHANGE (ms931471, 32),
  NMDATETIMEFORMAT (ms931472, 164), NMDATETIMEFORMATQUERY (ms931473,
  24), NMDATETIMESTRING (ms931474, 36), NMDATETIMEWMKEYDOWN
  (ms931475, 36).
* Month Calendar: MCHITTESTINFO (ms911793, 32), NMSELCHANGE
  (ms911859, 44), NMDAYSTATE (ms931476, 36 -- the LPMONTHDAYSTATE
  member type has no CE page: typed layout-neutral void* with the
  print recorded, the SHCONTF precedent).
* Tree View: HTREEITEM (opaque handle, HIMAGELIST model), TVITEM
  (ms913992, 40 -- the "tvi UINT mask" print artifact is present in
  BOTH the CE 5.0 page and twin ee502863 [recorded]; TV_ITEM alias
  ms914064 identical), TV_INSERTSTRUCT (ms914063, 48),
  TV_HITTESTINFO/TVHITTESTINFO (ms914062/ms913985, 16),
  TVSORTCB/TV_SORTCB (ms914061/ms914065, 12; the legacy page prints
  the "tvscb" prefix artifact [recorded]), NM_TREEVIEW (ms911864,
  104), TV_DISPINFO (ms913978, 52), NMTVCUSTOMDRAW (ms911867, 56),
  NMTVKEYDOWN/TV_KEYDOWN (ms911869/ms913996, 20), PFNTVCOMPARE (the
  ms914065 page prints the CompareFunc example; M51 model).
* List View: LVITEM (aa453430, 40 -- the page's
  "#if (_WIN32_IE >= 0x0300) int iIndent; #endif" conditional member
  reproduced verbatim; this repo never defines _WIN32_IE), LVCOLUMN
  (aa453423, 32), LVBKIMAGE (aa453422, 24), LVFINDINFO (aa453425, 24
  -- pointer alias printed LPFINDINFO [sic, kept]; LV_FINDINFO alias
  aa453540 identical), LVHITTESTINFO (aa453428, 20), NMLISTVIEW
  (ms931605, 44), NMLVCACHEHINT (ms931617, 20), NMLVCUSTOMDRAW
  (ms931627, 80 -- the "#if (_WIN32_IE >= 0x0400) int iSubItem;
  #endif" conditional reproduced verbatim), NMLVFINDITEM (ms931633,
  40), NMLVGETINFOTIP (ms931639, 36), NMLVKEYDOWN (ms931645, 20),
  NMLVODSTATECHANGE (ms931653, 28), LV_DISPINFO (aa453424, 52 -- tag
  printed "tag LV_DISPINFO" with a space [sic]).
* commctrl.h now includes winbase.h (SYSTEMTIME for the DTPicker /
  Month Cal structures).
* HELD: every message / notification / style / flag family of the
  seven sub-books (names-only; full ledger in the commctrl.h batch-2
  held block).  Notably the 15 Header_* macros DO print SNDMSG bodies
  (ms929911..) but reference the unpublished HDM_ message values, so
  their definitions are held; all other sub-books' macro bodies are
  not printed at all.

Verification: make check / crosscheck / e2e GREEN on all six targets
(TU m56: 43 struct-size asserts + shaped usage + alias-bridge
checks).  Export surface unchanged; headers 52; defs 44.

## M57 -- Bluetooth + SNMP + CEDDK wave (new headers bt_api.h, bthsdpdef.h, ws2bth.h, bthapi.h, btagpub.h, btagnetwork.h, snmp.h, snmpapi.h, snmpexts.h, pm.h, ceddk.h; Btdrt.lib / CEDDK.lib / Snmpapi.lib / Snmp.lib / Btagsvc*.lib)

Source books (CE 5.0 Product Documentation, tools/manifests/): bt-os
(96 leaves), bt-appdev (78), snmp (36), snmp-structs (6), snmp-tfx (8),
ceddk-bus (26), ceddk-io (25), ceddk-addr (5), ceddk-dma (6), ceddk-dep
(2: ms898294/aa447663).  338 CE 5.0 pages fetched + 311 CE 6.0 twins
(m57-ce60.manifest, build/pages6) + 8 SnmpTfx CE 6.0 twins
(snmp-tfx-ce60.manifest).  Desktop snmp.h pages preserved as
build/pagesw/snmp-nf-*.html (20 pages, print-corruption cross-reads);
bthioctl/wudfddi derivation pages preserved as
build/pagesw/bthioctl-*.html / wudfddi-*.html.

* bt_api.h (Bt_api.h; Btdrt.lib): 50 Bth* C functions, each with its
  page id in the header; bt_addr/BT_ADDR typedef (ms896282),
  BASEBAND_CONNECTION (aa450296, 24), PORTEMUPortParams (ms896282,
  56, tag _portemu_port_params).  BthNsSetService (ms887870) prints
  no signature -- the CE 6.0 twin ee495417 supplies it.  HELD:
  IOCTL_BLUETOOTH_GET_PEER_DEVICE (ms891157) / GET_RFCOMM_CHANNEL
  (ms891159) names-only; GET_NAP/GET_SAP/SET_NAP_SAP (aa450944)
  comment-only.
* bthsdpdef.h (Bthsdpdef.h; no lib rows): SDP_TYPE (aa450880),
  SDP_SPECIFICTYPE (aa450879, the SDP_ST_UUID32 = 0x0220 duplicate
  reproduced [sic]), NODECONTAINERTYPE (ms895690, the
  "NodeContainerTypeSequence + 1" case typo recorded),
  SdpQueryUuidUnion (aa450878, 16), SdpQueryUuid (aa450877, 20),
  struct _SdpAttributeRange (aa450876, 4 -- printed without the
  typedef keyword), BTHNS_RESTRICTIONBLOB (ms887868, 256),
  BTHNS_INQUIRYBLOB (ms887864, 8, "ULONGLAP"/"unsigned charlength"
  artifacts), BTHNS_SETBLOB (ms887869, 20).
  DERIVED: MAX_UUIDS_IN_QUERY = 12 -- the CE pages use the macro
  without a value; the official bthioctl.h DDI page
  BTH_SDP_SERVICE_ATTRIBUTE_SEARCH_REQUEST documents the same
  SdpQueryUuid uuids[MAX_UUIDS_IN_QUERY] array as "a maximum of 12
  entries" (preserved page pagesw/bthioctl-ns-...html).
* ws2bth.h (Ws2bth.h; no lib rows): SOCKADDR_BTH (aa450944, 40),
  BthInquiryResult (ms887862, 24, tag __bth_inquiry_result --
  forward-declared in bt_api.h, completed here),
  BTH_LOCAL_VERSION (ms887863, 18), BTH_REMOTE_VERSION (ms887884,
  14), BTH_REMOTE_NAME (ms887882, 504), BTH_SOCKOPT_SECURITY
  (ms887893, 32), BTH_HOLD_MODE (ms887904, 6), BTH_PARK_MODE
  (ms887905, 6), BTH_SNIFF_MODE (ms887906, 10).
* bthapi.h (Bthapi.h/.idl; Btdrt.lib rows but interface methods, not
  exports -- def-less opaque records, M44/M53/M54 model): ISdpWalk
  (aa450617 + WalkNode aa450619 / WalkStream aa450622), ISdpRecord
  (aa450590 + 9 methods aa450579..aa450597), ISdpNodeContainer
  (aa450551 + 13 methods aa450534..aa450562), ISdpStream (aa450601 +
  the ByteSwap family aa450599 (10 instances) / Retrieve family
  aa450605 (9 instances) / NormalizeUuid aa450603 /
  RetrieveElementInfo aa450607 / RetrieveRecords aa450609 / Validate
  aa450611 / VerifySequenceOf aa450613 / Walk aa450615).  HELD:
  NodeData (ms895699) / NodeDataUnion (ms895706) layouts -- the
  int128/uint128/str/url members are typed DP_LARGE_INTEGER_16 /
  SDP_ULARGE_INTEGER_16 / SdpString and no official page of any CE
  generation or desktop/driver tree publishes those layouts (toc
  search + page grep recorded); forward-declared, pointer-only use.
* btagpub.h (Btagpub.h): PFN_SendATCommand / PFN_PhoneExtServiceCallback
  (verbatim header excerpts, aa450305/aa450310);
  NETWORK_FLAGS_DROP_* / NETWORK_FLAGS_STATE_* values (aa450316 /
  aa450315 pages).  Btagsvc_phoneext.lib (9): BthAGPhoneExtInit
  (aa450311 -- the "BthAGInitPhoneExt" print artifact recorded;
  parameters/rv from the page + twin ee495665), BthAGPhoneExtDeinit
  (aa450306, twin ee495979), BthAGPhoneExtEvent (ms880975),
  BthAGGetLastDialed (aa450307), BthAGGetNameByPhoneNumber (aa450308),
  BthAGGetSpeedDial (aa450309), BthAGSetServiceCallback (aa450310),
  BthAGOverrideCallIn (aa450324), BthAGOverrideCallOut (ms887483).
  Btagsvc_network.lib (11): BthAGNetworkInit (aa450318), Deinit
  (aa450313, twin ee495426), AnswerCall (aa450312), DropCall
  (aa450316, "HangupCall" artifact), DialNumber (aa450314),
  GetCallState (aa450315), HoldCall (aa450317, case artifact),
  RejectCall (aa450319), SwapCall (aa450320), TransmitDTMF (aa450321),
  UnholdCall (aa450322).  Developer-defined (no def): BthAGATHandler
  (aa450304), BthAGATSetCallback (aa450305, twin ee495634 supplies
  the prototype).  HELD: AG_PHONE_EVENT_* (ms880975), IOCTL_AG_*
  (ms891134..ms891153) names-only.
* btagnetwork.h (Btagnetwork.h; Btagsvc.lib): BthAGOnNetworkEvent
  (aa450323), NetworkCallFailedInfo (ms895682, 8).  HELD:
  NETWORK_EVENT_* names-only (aa450323).
* snmp.h (Snmp.h; Snmp.lib + Snmpapi.lib): AsnObjectIdentifier
  (ms894991, 8), AsnOctetString (ms894993, 12), AsnCounter64
  (ms894989, 8, LowPart-first), AsnAny (ms894988, 16, the CE spelling
  AsnIPAdress [sic] kept), SnmpVarBind (ms896055, 24), SnmpVarBindList
  (ms896056, 8).  Snmp.lib (7): SnmpExtensionClose (ms896018), Init
  (ms896019 -- the mangled second parameter resolved via the twin
  ee489093 parameter text + the desktop page: HANDLE*
  phSubagentTrapEvent), InitEx (ms896020), Query (ms896021), QueryEx
  (ms896022), Trap (ms896023 -- "AsnTimeticks" case artifact), and
  SnmpUtilMemAlloc (ms896036, declared in snmpapi.h: "Header:
  Snmpapi.h. Link Library: Snmp.lib.").  Snmpapi.lib (29): SnmpSvc*
  (ms896024/25/26 -- the DWORD return prints of SetLogLevel/SetLogType
  are artifacts, the pages' own "no return values" + desktop VOID
  win), SnmpUtil* (ms896031..ms896054) with every corrupted print
  (OctetsComp name, dropped pointer stars, VOID-vs-nonzero returns,
  the SnmpUtilOidFree/ OctetsFree body swaps) resolved via the
  parameter text + twins + the preserved desktop pages.
  DERIVED typedefs (paths in the header): SNMPAPI=LONG (signed
  comparison semantics documented on ms896039/ms896044);
  AsnInteger32/AsnUnsigned32/AsnCounter32/AsnGauge32/AsnTimeTicks =
  the documented 32-bit signed/unsigned scalars;
  AsnBits/AsnSequence/AsnIPAdress/AsnOpaque = AsnOctetString (RFC
  1155/2578 octet-string natures; the API's documented octet-string
  container); AsnObjectName=AsnObjectIdentifier and
  AsnObjectSyntax=AsnAny (desktop member text + RFC 1155);
  AsnInteger=LONG; RFC1157VarBindList=SnmpVarBindList (RFC 1157).
  HELD: ASN_*, SNMP_EXCEPTION_* (ms894988), SNMP_PDU_* /
  SNMP_EXTENSION_* / SNMP_ERRORSTATUS_* (ms896021/22/30),
  SNMP_GENERICTRAP_* (ms896023), SNMP_LOG_* / SNMP_OUTPUT_*
  (ms896025/26/33) -- all names-only.
* snmpapi.h (Snmpapi.h): SnmpUtilMemAlloc (ms896036; Snmp.lib def
  entry).
* snmpexts.h (Snmpexts.h; Snmpapi.lib): SnmpTfxOpen (ms896029),
  SnmpTfxQuery (ms896030), SnmpTfxClose (ms896028; twin ee489435).
  DERIVED: SnmpTfxHandle=HANDLE ("returns a HANDLE value",
  ms896029).  HELD: SnmpMibView / SnmpMibEntry / SnmpMibTable layouts
  (ms894645 documents that Snmpexts.h defines them but no page prints
  the members; the framework pages ms894613/ms894614/ms894616/
  ms894647 + CE 6.0 twins ee489447/ee489262/ee489056/ee489432 record
  the MIB_* macro conventions only) -- SnmpMibView is
  forward-declared for the documented SnmpTfxOpen prototype.
* pm.h (Pm.h; no lib row): CEDEVICE_POWER_STATE (aa447663, values
  printed; twin ee497766).
* ceddk.h (CEDDK.h): BUS_DATA_TYPE (ms896151), INTERFACE_TYPE
  (ms901367), DMA_ADAPTER_OBJECT (ms898303, 12, tag
  _DMA_ADAPTER_OBJECT_ [trailing underscore as printed]), PPVOID
  (printed by the Trans*/BusTrans* prototypes).  CEDDK.lib (36):
  HalGetBusData/ByOffset (ms899356/57), HalSetBusData/ByOffset
  (ms899359/60), HalTranslateBusAddress (ms899361),
  HalTranslateSystemAddress (ms899362), the 24 READ/WRITE_PORT /
  READ/WRITE_REGISTER / *_BUFFER functions (ms919746..ms923683 --
  WRITE_PORT_BUFFER_USHORT ms923673 prints the ULONG body in both CE
  generations [artifact]; the PUSHORT shape derived from the page's
  own description + the family), MmMapIoSpace (aa447863),
  MmUnmapIoSpace (aa447865), TransBusAddrToVirtual (aa448212),
  TransBusAddrToStatic (aa448211), HalAllocateCommonBuffer (ms899352),
  HalFreeCommonBuffer (ms899355).  Bus-access functions (no Link
  Library row, no pins/def): BusIoControl (ms896152),
  BusTransBusAddrToStatic/Virtual (ms896153/154), CreateBusAccessHandle
  (aa447690), CloseBusAccessHandle (aa447670), GetBusNamePrefix
  (aa447824), GetChildDeviceRemoveState (aa447825),
  GetDeviceConfigurationData (aa447827), SetDeviceConfigurationData
  (ms920576), GetDevicePowerState (aa447832), SetDevicePowerState
  (ms920590), GetParentDeviceInfo (ms899309), TranslateBusAddr
  (aa448213), TranslateSystemAddr (aa448215), StallExecution
  (aa448325), CalibrateStallCounter (aa448302 -- the CE 5.0 page
  prints the StallExecution body; twin ee481529 prints the real one).
  DERIVED: PHYSICAL_ADDRESS/PPHYSICAL_ADDRESS = LARGE_INTEGER (no CE
  page defines the type anywhere in the CE 5.0 catalog or the CE 6.0
  tree; the official wudfddi.h IWDFDevice3::MapIoSpace page prints
  "typedef LARGE_INTEGER PHYSICAL_ADDRESS;" -- preserved page
  pagesw/wudfddi-...html).
* winbase.h: DEVMGR_DEVICE_INFORMATION (ms898294, 1584, Winbase.h
  per the page; CE 5.0+; twin ee481699 identical; consumed by
  ceddk.h GetParentDeviceInfo).
* DVD (Dvddrvr.idl 43 + Dvdcss.idl 13 + macros ms892143) harvested
  for M58 (dvd.manifest, 60 pages).
* Not grounded in CE 5.0 books: Nk (no "Network Kernel" book);
  BASEBAND_CONNECTION_DATA (bt_ddi.h) held (BD_ADDR type layout not
  published); OID_PAN_* (bt_ddi.h), BTHHID_IOCTL_* (Bthid.h),
  WODM_BT_SCO_AUDIO_CONTROL (Bt_ddi.h) names-only.

Verification: make check / crosscheck / e2e GREEN on all six targets
(TU m57: 34 size asserts incl. the crosscheck-corrected
SdpQueryUuid 20 / BTHNS_RESTRICTIONBLOB 256 / BTHNS_INQUIRYBLOB 8,
enum-value asserts, and shaped usage covering every family; e2e adds
btdrt.dll / snmpapi.dll / snmp.dll / ceddk.dll / btagsvc_phoneext.dll
/ btagsvc_network.dll / btagsvc.dll import asserts).  Headers 52 ->
63; defs 44 -> 51 (btdrt 50, ceddk 36, snmpapi 29, snmp 7,
btagsvc_phoneext 9, btagsvc_network 11, btagsvc 1).

## M58 -- DVD-Video renderer (new headers dvddrvr.h, dvdcss.h; def-less Dvddrvr.idl / Dvdcss.idl layers)

Source book: CE 5.0 "DVD-Video Renderer Reference"
(tools/manifests/dvd.manifest, 60 pages, fetched M57; pages preserved in
the corpus with the M57 export).  Every page prints "Header:
Dvddrvr.idl" or "Header: Dvdcss.idl" with no Link Library row, so the
milestone is def-less (the M44/M53/M54/M57 interface-record model).

* dvddrvr.h enumerations (values printed; implicit successors where not
  explicit): EDVDAspectRatioMode (aa447766), EDVDAudioFreq (aa447767),
  EDVDAudioStreamType (aa447768, AC3 = 2), EDVDDisplayAspectRatio
  (aa447769, 4x3 = 0, 16x9 = 0x3 -- the SetContentAspectRatio
  ms901312 / SetDisplayAspectRatio ms901323 pages list the same values
  under the alternate spellings DISPLAY_ASPECT_4_3 /
  DISPLAY_ASPECT_16_9_DOWNSAMPLE_4_3, recorded in the header),
  EDVDLpcmQuantization (aa447780), EDVDSyncEventType (aa447781),
  EHighlightAction (aa447783, HIGHLIGHT_SELECT = 1).
* dvddrvr.h capability macros (ms892143 prints every value):
  DVD_AUDIOCAP_* (0x4000/0x1000/0x0800/0x0400/0x0080/0x0040/0x0010/
  0x0008/0x0004) and DVD_SCANCAP_* (0x1..0x20).
* dvddrvr.h opaque interface records: IDMAChannel (ms900175; methods
  ms900171-ms900179 -- GetPendingTransferCount ms900174 prints
  "GetPendingTransfersCount" in the signature block [artifact
  recorded]; RequestTransfer ms900177 takes the CEDDK.h
  PHYSICAL_ADDRESS; SetThresholdCallback ms900179 names
  PNOTIFICATION_CALLBACK, whose type is unpublished [held]),
  IBitstreamProcessor (ms900169; methods ms900165-ms900170),
  IDVDRenderer (ms900198; 21 methods ms900193-ms901363 -- the Step page
  ms901358 prints the Slow prototype [artifact recorded]).
* dvdcss.h opaque interface record: IDVDDecoderCSS (ms900185; 12
  methods ms900180-ms900192).  HELD: CSS_CHALLENGE / CSS_KEY / CSS_SDKS
  layouts (parameter types only; the 2048-byte disk-key size is
  documented but not the layouts), E_DVD_FAKE_ENCRYPTION (name-only).
* HELD across both headers: IID_IDMAChannel / IID_IBitstreamProcessor /
  IID_IDVDRenderer / IID_IDVDDecoderCSS (ms892115 names them with no
  GUID values).

Verification: make check / crosscheck / e2e GREEN on all six targets
(TU m58: 9 value-assert groups + shaped usage).  Headers 63 -> 65;
defs 51 (unchanged).

## M59 -- DirectDraw (new headers ddraw.h, dvp.h; def ddraw-doc.def)

Sources: CE 5.0 "DirectDraw Reference" book -- 134 pages harvested
(tools/manifests/ddraw.manifest; includes 3 TOC nodes, 4 global
functions, 7 callbacks, 18 structure pages, 7 interface records with
93 method pages, 1 return-values page) + 23 CE 6.0 twins
(tools/manifests/ddraw-ce60.manifest).  All pages: OS "Windows CE 2.12
and later. Version 2.12 requires DXPAK 1.0 or later" (DDPIXELFORMAT
ms907795: "Windows CE .NET 4.0 and later"); headers Ddraw.h (90 pages)
and Dvp.h (26 pages); link library Ddraw.lib for the 4 global
functions and the interface records, "User-defined" for callbacks, no
lib row for structures.

* ddraw.h structures transcribed verbatim from the CE 5.0 prints:
  DDCOLORKEY (ms907791, 8 bytes), DDSCAPS (ms907796, 4),
  DDSCAPS2 (ms907797, 16), DDSCAPSEX (ms907798, 12), DDPIXELFORMAT
  (ms907795, 32; five anonymous unions incl. the MultiSampleCaps
  WORD/WORD struct), DDSURFACEDESC (ms907799, 108; anonymous unions
  exactly as printed), DDSURFACEDESC2 (ms907800, 124;
  DUMMYUNIONNAMEN(1..2) markers kept with the macro defined empty --
  the nameless-union convention stated by the desktop DDBLTFX docs),
  DDBLTFX (ms907788, 100; DUMMYUNIONNAMEN(1..5)), DDOVERLAYFX
  (ms907794, 56; member spellings dckDestColorkey/dckSrcColorkey as
  printed), DDCOLORCONTROL (ms907790, 40), DDCAPS (ms907789, 380 =
  91 DWORDs + DDSCAPS2; six dw*Rops[DD_ROP_SPACE] arrays).
* dvp.h structures: DDVIDEOPORTBANDWIDTH (ms907801, 32),
  DDVIDEOPORTCAPS (ms907802, 72; WORD wNumFilterTapsX/Y tail),
  DDVIDEOPORTCONNECT (ms907803, 32; GUID guidTypeID + ULONG_PTR),
  DDVIDEOPORTDESC (ms907804, 72), DDVIDEOPORTINFO (ms907805, 64;
  RECT rCrop + three LPDDPIXELFORMAT), DDVIDEOPORTSTATUS (ms907806,
  56).  TU m59 asserts all sizes + key offsets (dwRops@100,
  ddsCaps@364, dwTextureStage@120, ddckDestColorkey@84, dwRGBBitCount
  @12 / dwRBitMask@16, rCrop@16, guidTypeID@8); crosscheck-corrected:
  DDCAPS 428->380 / ddsCaps 412->364 (initial miscount of the Rops
  arrays) and DDPIXELFORMAT dwRBitMask 12->16 (second union).
* DD_ROP_SPACE = 8: derived-value permission applied.  Path: DDCAPS
  prints "DWORD dwRops[DD_ROP_SPACE]" (ms907789, same in CE 4.2 twin
  ms893881); the DirectDraw driver docs (DDCORECAPS, ddrawi.h, Learn
  win32/ddrawi/ns-ddrawi-ddcorecaps) state the array is "an array of
  DD_ROP_SPACE DWORDs that together can hold flags to indicate the
  ROPs that the driver supports" and defer ROP information to "the
  Microsoft Windows SDK documentation"; the Win32 SDK Ternary Raster
  Operations reference enumerates the ROP space by an 8-bit operation
  index (Boolean functions 00-FF = 256 codes); 32 bits per DWORD
  -> 256/32 = 8.  Pages preserved in corpus pagesw/.
* Interfaces are opaque exactly as their pages print them (ms929639
  "typedef struct IDirectDraw FAR *LPDIRECTDRAW" + generations
  IDirectDraw2/4, Surface/2/3/4/5, Clipper, Palette, ColorControl;
  ms909107 / aa451780 for the Dvp.h pair).  No page prints a vtable
  layout, so no interface is laid out (M58 pattern); all 93 method
  signatures are recorded in the header comment blocks with per-page
  ids.  CE specifics recorded: IDirectDraw4::GetDeviceIdentifier and
  ::Initialize not supported in Windows CE (ms929639),
  IDirectDrawClipper::Initialize (ms929663) and
  IDirectDrawPalette::Initialize (ms929673) not supported,
  IDirectDrawSurface5::UpdateOverlayDisplay not implemented and
  prints no signature (ms929718), ::Compact (ms929640) and
  ::AddOverlayDirtyRect (ms929679) "not currently implemented",
  ::Lock hEvent "not used and must be set to NULL" + DDLOCK_NOSYSLOCK
  not supported in CE (ms929705).
* Callback pointer typedefs (composition of each page's printed
  prototype + its "You can use the LP... data type to declare a
  variable that can contain a pointer to this callback function"
  remark, path recorded per item in the header): LPDDENUMCALLBACK
  (ms907792), LPDDENUMCALLBACKEX (ms907793, HMONITOR tail),
  LPDDENUMMODESCALLBACK (aa451690), LPDDENUMMODESCALLBACK2 (aa451691;
  page prints the prototype name "EnumModesCallback" -- title wins,
  artifact recorded), LPDDENUMSURFACESCALLBACK (aa451692),
  LPDDENUMSURFACESCALLBACK2 (aa451693), LPDDENUMVIDEOCALLBACK
  (aa451694; page names Ddraw.h but its parameter type DDVIDEOPORTCAPS
  is a Dvp.h structure per ms907802, so the typedef is placed in
  dvp.h next to its only consumer IDDVideoPortContainer::
  EnumVideoPorts ms909119 -- placement decision recorded here).
* def/ddraw-doc.def: 4 exports (DirectDrawCreate aa451583,
  DirectDrawCreateClipper aa451584, DirectDrawEnumerate aa451585,
  DirectDrawEnumerateEx aa451586) -- exactly the Ddraw.lib function
  surface; interface-method pages carry Ddraw.lib rows but are
  def-less records (no dlltool-able symbols).  e2e asserts ddraw.dll +
  all 4 symbols.
* HELD (names documented, values/layouts not published):
  - DDARGB layout and therefore DDALPHABLTFX (ms907787; checked CE
    4.2 ms893879, CE 5.0 ms907787, CE 6.0 ee490481, desktop Learn
    ddraw.h header index + Learn search API -- no DDARGB definition
    anywhere official; only third-party SDK copies publish a layout).
  - All DD* constant families (values name-only everywhere): DD_OK /
    DDERR_* (aa451337, 130+ codes), DDBLT_*/DDBLTFX_* (ms907788,
    ms929681), DDCAPS_*/DDCAPS2_*/DDCKEYCAPS_*/DDFXCAPS_*/
    DDFXALPHACAPS_*/DDPCAPS_*/DDSVCAPS_*/DDBD_* (ms907789),
    DDCOLOR_* (ms907790), DDOVERFX_* (ms907794), DDPF_* (ms907795),
    DDSCAPS_*/DDSCAPS2_*/DDSCAPS4_* (ms907796/797/798),
    DDSD_* (ms907799/800), DDENUM_* (aa451586), DDENUMRET_*
    (aa451690..694), DDSCL_* (ms929659), DDEDM_* (ms929645),
    DDENUMSURFACES_* (ms929646), DDENUMOVERLAYZ_* (ms929686),
    DDWAITVB_* (ms929662), DDSDM_* (ms929660), DDCREATE_* (aa451583
    note text), DDGFS_*/DDGBS_* (ms929696/690), DDCKEY_* (ms929711),
    DDBLTFAST_* (ms929682), DDFLIP_* (ms929687), DDLOCK_* (ms929705),
    DDSPD_* (ms929714), DDOVER_*/DDOVERZ_* (ms929717/aa451768),
    DDABLT_* (ms929680), DDPSETPAL_* (ms929642), and the Dvp.h
    families DDVPCAPS_*/DDVPD_*/DDVPFX_* (ms907802),
    DDVPCONNECT_*/DDVPTYPE_* GUID names (ms907803), DDVP_* (ms907805),
    DDVPCREATE_* (ms909118), DDVPFLIP_* (aa451781), DDVPB_*
    (aa451782), DDVPFORMAT_* (aa451785/786), DDVPTARGET_* (aa451790),
    DDVPWAIT_* (aa451794), DDVPSQ_* (aa451788), DDVPSTATUS_*
    (ms907806), DDVPBCAPS_* (ms907801).
* CE 6.0 twin divergences recorded (condensed/variant member lists;
  CE 5.0 prints implemented): DDBLTFX ee491245, DDCAPS ee490705,
  DDCOLORCONTROL ee490304, DDOVERLAYFX ee491509, DDPIXELFORMAT
  ee491068, DDSURFACEDESC ee490816, DDALPHABLTFX ee490481 (adds a
  dwSize member).  Identical twins: DDCOLORKEY ee490463, DDSCAPS
  ee490733, RGNDATAHEADER/RGNDATA ee490821/ee490736 (already in
  wingdi.h from the GDI milestones).  The CE 5.0 prints are
  additionally corroborated member-by-member by the desktop ddraw.h
  documentation set on Learn (DDBLTFX, DDCAPS_DX7, DDSURFACEDESC(2),
  DDOVERLAYFX, DDPIXELFORMAT, DDCOLORCONTROL, DDCOLORKEY, DDSCAPS(2)
  pages), which also states the DUMMYUNIONNAMEN nameless-union
  convention (pages preserved in corpus pagesw/).

Verification: make check / crosscheck / e2e GREEN on all six targets
(TU m59: DD_ROP_SPACE value assert + 24 size/offset asserts + shaped
usage incl. the four Ddraw.lib calls).  Headers 63 -> 65; defs 51 ->
52 (ddraw 4).

## M60 -- URL Moniker Services (new header urlmon.h; def urlmon-doc.def)

Sources: the four URL Moniker Services books, 191 leaves harvested
(tools/manifests/urlmon.manifest 88, urlmon-app.manifest 48,
urlmon-zones.manifest 50, urlmon-hitlog.manifest 5).  All pages:
"Header: Urlmon.h, Urlmon.idl." + "Link Library: Urlmon.lib."
(functions/interfaces) or no lib row (enums/structures); OS "Windows
CE .NET 4.0 and later".

* Enumerations: 19 defined.  Ten print explicit hex/decimal values
  (transcribed verbatim): BINDF 24 values (aa452098), PI_FLAGS 14 incl.
  the printed name PD_FORCE_SWITCH (ms918833), BINDINFO_OPTIONS 5
  (aa452101), MONIKERPROPERTY 1 (ms918826), URL_ENCODING 3 (ms918867),
  PUAF 9 (ms918841), SZM_FLAGS 2 (ms918860), URLTEMPLATE 7 incl.
  URLTEMPLATE_LOW sharing PREDEFINED_MIN's 0x10000 (ms918875), ZAFLAGS
  8 (ms918890), URLZONE's mixed explicit set (ms918876: LOCAL_MACHINE=0,
  PREDEFINED_MAX=999, USER_MIN=1000, USER_MAX=10000).  Nine print
  starter values with C implicit successors (transcribed as printed):
  PSUACTION PSU_DEFAULT=1 (ms918840), BINDSTRING BINDSTRING_HEADERS=1
  (aa452103), PARSEACTION PARSE_CANONICALIZE=1 (ms918832), QUERYOPTION
  QUERY_EXPIRATION_DATE=1 (ms918843), URLZONEREG DEFAULT=0 (ms918877),
  and the value-less prints BINDINFOF / BINDVERB / BSCF (implicit 0..n,
  aa452100/aa452104/aa452105) and BINDSTATUS (aa452102).
* BINDSTATUS print artifacts recorded: the enumerator
  BINDSTATUS_COOKIE_STATE_PROMPT is printed TWICE (after COOKIE_STATE_REJECT
  and after COOKIE_STATE_LEASH); a C enum cannot repeat a name so the
  second occurrence is dropped -- 49 enumerators, BINDSTATUS_SIZEAVAILABLE
  = 48, and entries after the dropped slot number one less than a
  "count the duplicate" reading (both readings noted; no values are
  printed anywhere).  "VERFIEDMIMETYPEAVAILABLE" spelling kept as
  printed; the missing comma between BINDSTATUS_ACCEPTRANGES and
  BINDSTATUS_COOKIE_SENT is a spacing artifact.
* Structures: PROTOCOLDATA (ms918838, 16 bytes), PROTOCOLFILTERDATA
  (ms918839, 20), HIT_LOGGING_INFO (ms906339, 44, with LPHIT_LOGGING_INFO)
  transcribed verbatim.  BINDINFO NOT redefined: objbase.h already
  defines it (ms928761, Objidl.h book of the COM docs) and the URL
  Moniker Services BINDINFO page (aa452099) prints the identical
  member list (corroboration recorded).  ZONEATTRIBUTES (ms918891)
  HELD: the szDescription array length MAX_ZONE_DESCRIPTION is not
  published in the CE docs, the desktop docs set (no urlmon.h
  ZONEATTRIBUTES page on Learn, 404), or the Learn search index
  (0 results) -- only third-party header copies publish it.
* CLIPFORMAT derived (unsigned long): CE FORMATETC page ms886985
  prints cfFormat as unsigned long (the basis objbase.h used); the
  desktop FORMATETC documentation (objidl.h, saved to corpus pagesw/)
  prints the same member as CLIPFORMAT cfFormat; RegisterMediaTypes
  (ms918847) describes rgcfTypes as "an array of the 32-bit values".
* Registered media-type name constants (ms918847) defined with their
  printed string values: CF_NULL 0, SZ_URLCONTEXT L"URL Context", 21
  CFSTR_MIME_* TEXT() macros.  Print artifact recorded: the page lists
  CFSTR_MIME_X_MSVIDEO twice ("video/x-msvideo" and "video/x-sgi-movie");
  the first is defined, the second row is recorded as an artifact (the
  corrected spelling is not invented).
* Interfaces: 25 opaque typedefs exactly as the pages/function
  signatures name them (IInternet aa452292 no methods, IAsyncMoniker
  ms906353 IUnknown-only, IAuthenticate, IBindHost, IBinding,
  IBindStatusCallback, IHttpNegotiate, IHttpSecurity, IMonikerProp,
  IPersistMoniker, IWindowForBindingUI, IWinInetHttpInfo, IWinInetInfo,
  IInternetSession, IInternetProtocol, IInternetProtocolInfo,
  IInternetProtocolRoot, IInternetProtocolSink,
  IInternetProtocolSinkStackable, IInternetBindInfo, IInternetPriority,
  IInternetHostSecurityManager, IInternetSecurityManager,
  IInternetSecurityMgrSite, IInternetZoneManager).  77 method
  signatures recorded in the interface comments (page ids per method);
  archive print artifacts normalized and recorded: "ockRequest" for
  LockRequest (aa452309), "HRESULTGetBindResult"-style missing spaces
  (14 pages), "OueryOption" parameter name (aa452308),
  CoInternetGetSecurityURL capitalization (aa452113, title spelling
  implemented).  Interface-table rows without method pages (signatures
  unpublished, held): IBinding::SetPriority + Suspend (ms906360),
  IBindStatusCallback::OnLowResource "Not currently implemented"
  (ms906365), IInternetProtocolRoot::Resume + Suspend "Not implemented"
  (aa452311), IInternetZoneManager::LogAction + PromptAction "Not
  currently implemented" (aa452345).
* LPBINDSTATUSCALLBACK / LPBINDCTX pointer typedefs: composed from the
  names printed by the function signatures themselves (ms918866/871/
  872/873 print LPBINDSTATUSCALLBACK; aa452108 prints LPBINDCTX) with
  the opaque interface typedefs (derivation recorded in the header).
* def/urlmon-doc.def: 38 exports = the complete documented Urlmon.lib
  function surface.  Three TCHAR-generic prints are mapped to the W
  symbols (UNICODE_ONLY entries, the CreateFileW precedent):
  IsLoggingEnabled -> IsLoggingEnabledW (ms918808),
  URLDownloadToCacheFile -> URLDownloadToCacheFileW (ms918865),
  URLDownloadToFile -> URLDownloadToFileW (ms918866); the header
  declares the W names (winbase.h CreateDirectoryW pattern) so the
  ARM (plain C name) and x86 (__asm label) symbol spellings agree.
  e2e asserts urlmon.dll + CoInternetGetSession,
  CoInternetGetSecurityUrl, CreateURLMoniker, RegisterMediaTypes,
  IsLoggingEnabledW, URLDownloadToFileW, WriteHitLogging.
* HELD (names documented, values not published): INET_E_* (ms918870,
  26 codes), URLACTION_* (ms918863), URLPOLICY_* (ms918874),
  CLSID_InternetSecurityManager / CLSID_InternetZoneManager (aa452025 /
  aa452026; created via CoCreateInstance, no GUID values),
  ZONEATTRIBUTES / MAX_ZONE_DESCRIPTION (ms918891).  The four "Zone
  Settings" concept pages (ms919149 etc.) are registry-settings docs
  with no API surface.

Verification: make check / crosscheck / e2e GREEN on all six targets
(TU m60: 3 size + 2 offset asserts + 21 enum-value assert groups +
shaped usage of all 38 functions).  Headers 65 -> 66; defs 52 -> 53
(urlmon 38).

## M61 -- Internet Explorer Multiple-Language API (new header mlang.h; def mlang-doc.def)

Sources: the "Internet Explorer Multiple-Language API Reference"
book, 112 leaves (tools/manifests/mlang.manifest): 11 interfaces with
75 method pages, 6 functions, 6 structures, 6 enumerations, 5
object/concept pages.  All pages: "Header: Mlang.h, Mlang.idl." +
"Link Library: Mlang.dll." (module form; mapped to the Mlang.lib
export group with LIBRARY mlang.dll, the coredll.dll precedent) or no
lib row; OS "Windows CE .NET 4.0 and later".

* Enumerations, all with printed values: MIMECONTF 13 hex values
  (ms918819), MLCONVCHAR (tag tagMLCONVCHARF) 6 decimal values
  (ms918823), MLCP (tag tagMLCPF, MLDETECTF_* names) 7 values
  (ms918824), MLDETECTCP 5 values (ms918825), SCRIPTCONTF implicit
  from 0 with the printed Far-East aliases sidFEFirst=sidHangul /
  sidFELast=sidHan (ms918854; 41 enumerators + 2 aliases, TU asserts
  sidHangul==23, sidHan==26, sidLim==40), SCRIPTFONTCONTF 5 values
  (ms918856).
* SCRIPT_ID derived (recorded path): the type name is printed by
  SCRIPTINFO (ms918857) and the IMLangFontLink2 signatures
  (aa452370/aa452373); GetScriptFontInfo states a SCRIPT_ID value
  "can be one of the SCRIPTCONTF values" and SCRIPTCONTF is the
  published script-identifier list -> typedef SCRIPTCONTF SCRIPT_ID.
* Structures: UNICODERANGE (ms918861, 4 bytes) and DetectEncodingInfo
  (aa452152, 16 bytes; pointer typedef "pDetectEncodingInfo" exactly
  as printed) transcribed verbatim.  HELD: MIMECPINFO (ms918820),
  MIMECSETINFO (ms918821), RFC1766INFO (ms918852), SCRIPTINFO
  (ms918857, tag printed "tagSCRIPINFO" -- artifact recorded) -- all
  four carry MAX_MIMECP_NAME / MAX_MIMECSET_NAME / MAX_MIMEFACE_NAME /
  MAX_RFC1766_NAME / MAX_LOCALE_NAME / MAX_SCRIPT_NAME array lengths
  that are not published by the CE pages, the desktop Mlang docs set
  (removed from Learn) or the Learn search index (0 results).
  SCRIPTFONTINFO referenced by aa452373 with no page (held; the
  parameter text there even calls it "SCRIPTINFO str..." -- print
  artifact recorded).
* def/mlang-doc.def: 6 exports = the complete documented Mlang.dll
  function surface (ConvertINetMultiByteToUnicode aa452124,
  ConvertINetString aa452127, ConvertINetUnicodeToMultiByte aa452129,
  IsConvertINetStringAvailable ms918805, LcidToRfc1766 ms918817,
  Rfc1766ToLcid ms918853).  LcidToRfc1766 / Rfc1766ToLcid take LPTSTR
  but the pages publish only the plain names (no A/W pair anywhere in
  the docs), so the plain names are the exports.  e2e asserts
  mlang.dll + ConvertINetString / LcidToRfc1766 / Rfc1766ToLcid.
* Interfaces: 11 opaque typedefs (IEnumCodePage ms906426, IEnumRfc1766
  ms906430, IEnumScript aa452258, IMLangCodePages aa452355,
  IMLangConvertCharset aa452360, IMLangFontLink aa452368,
  IMLangFontLink2 aa452369, IMLangLineBreakConsole aa452389,
  IMultiLanguage ms918295, IMultiLanguage2 ms918297, IMultiLanguage3
  ms918323) with all 75 method signatures recorded per interface;
  inheritance as printed: IMLangFontLink/2 inherit IMLangCodePages,
  IMLangFontLink2 subsumes IMLangFontLink, IMultiLanguage3 inherits
  IMultiLanguage2.  IEnumCodePage / IEnumRfc1766 have no Clone method
  pages on CE (recorded).  IsConvertible "not currently implemented"
  on both IMultiLanguage (ms918338) and IMultiLanguage2 (ms918319).
  CE caveat recorded per interface: "not supported on all Windows
  CE-based operating systems" (all except IMultiLanguage, which is
  "supported on all Windows CE-based operating systems that include
  Mlang functionality").
* Objects: MultiLanguage object (ms918827) + Code Page Enumeration /
  Locale Enumeration / Script Enumeration / Conversion concept pages
  -- no CLSID values published (held); no API surface beyond the
  interfaces above.

Verification: make check / crosscheck / e2e GREEN on all six targets
(TU m61: 2 size asserts + 6 enum-value assert groups incl. the
SCRIPTCONTF alias identities + shaped usage of all 6 functions).
Headers 66 -> 67; defs 53 -> 54 (mlang 6).

### M61b -- Nk-scope closure (winbase.h additions; coredll def +1)

The "Nk" queue is resolved: rows.json carries 18 Winbase.h pages with
Nk.lib link rows (7 Nk.lib-only, 11 co-listed with Coredll.lib).  All
were already declared except four, now added:

* aa450795 "CeGetThreadPriority" (CE 2.11+; Coredll.lib):
  AKARI_CE_IMPORT int CeGetThreadPriority(HANDLE) -- coredll-doc.def
  619 -> 620 exports.
* ms885155 "CeSetThreadPriority" (CE 2.11+; Nk.lib-only): plain
  declaration, no user-mode doc def (the OutputDebugStringW pattern;
  kernel-side export).
* aa450889 "SetThreadContext" (CE 2.0+; Nk.lib-only): plain
  declaration; BOOL SetThreadContext(HANDLE, CONST CONTEXT*).
* aa450992 "WriteProcessMemory" (CE 2.0+; Nk.lib-only): plain
  declaration; BOOL WriteProcessMemory(HANDLE, LPVOID, LPVOID, DWORD,
  LPDWORD).  (GetThreadContext ms885642 / ReadProcessMemory ms886794
  were already declared via their Coredll.lib co-listing.)

Verification: make check / crosscheck / e2e GREEN on all six targets
(TU m61 shaped usage extended).  Headers 67 (unchanged count);
coredll def 619 -> 620; total defs 54 (unchanged count).

### M63 -- Waveform Audio + Timer Driver (mmsystem.h; coredll +51, mmtimer +9)

Waveform Audio book (124 leaves, sub-book of Graphics and Multimedia
Technologies > Audio) and Timer Driver Reference (13 leaves), harvested
under the M63 manifest (tools/manifests/waveaudio.manifest +
timerdriver.manifest).  New header include/mmsystem.h (68th; self-
contained, no windows.h dependency).

* Header-name compat: Win32 software expects mmsystem.h -- the file name
  itself is the compat surface (the msgqueue.h pattern).
* Transcribed CE 5.0 prints: WAVEFORMATEX, WAVEHDR (self-referential
  LPWAVEHDR wavehdr_tag), WAVEINCAPS/WAVEOUTCAPS (MMVERSION), MMTIME
  (union ms/sample/cb/ticks/smpte/midi), TIMECAPS, STREAMPROPS,
  AUDIOGAINCLASS, MIXERCAPS (TCHAR szPname[MAXPNAMELEN]), MIXERCONTROL
  (anonymous Bounds/Metrics unions), MIXERCONTROLDETAILS (+ union
  hwndOwner/cMultipleItems; LISTTEXT/BOOLEAN/SIGNED/UNSIGNED detail
  structs), MIXERLINE (+ Target sub-struct), MIXERLINECONTROLS.
* Handles: HWAVEIN/HWAVEOUT/HMIXER/HMIXEROBJ (void*), LPHWAVEIN/
  LPHWAVEOUT/LPHMIXER.  LPTIMECALLBACK with DWORD_PTR params
  (aa448195).
* Functions (53 Coredll.lib rows): PlaySound, sndPlaySound, waveIn x17
  (incl. CE-specific waveInGetProperty/waveInSetProperty GUID propsets),
  waveOut x24, mixer x10.  waveInProc/waveOutProc are user callbacks
  (their lib rows are callback registration, not imports) -- excluded
  from the def, declared as types only.
* New def mmtimer-doc.def (9 Mmtimer.lib rows): timeBeginPeriod,
  timeEndPeriod, timeGetDevCaps, timeGetHardwareFrequency (CE-specific),
  timeGetSystemTime, timeGetTime, timeGetTimeSinceInterrupt
  (CE-specific), timeKillEvent, timeSetEvent.  LIBRARY mmtimer.dll per
  the documented Link Library row (mmtimer.lib).
* Derived values (derivation path recorded in the header): MMRESULT =
  UINT (aa452425 prints MMRESULT mmrError, aa452446 prints UINT
  mmrError for the twin GetErrorText -- the pages interchange them);
  MMVERSION = UINT (WAVEINCAPS/WAVEOUTCAPS print, no width given);
  MAXPNAMELEN = 32 (printed value, aa452442).  Own-design closures
  (name-only in docs, no value pages anywhere incl. desktop mmeapi):
  MIXER_SHORT_NAME_CHARS = 16, MIXER_LONG_NAME_CHARS = 64,
  MAXERRORLENGTH = 256.
* Held (name-only, zero-gap policy): the full flag families -- SND_*,
  CALLBACK_*, WAVE_FORMAT_*, WAVECAPS_*, WHDR_*, WIM_/WOM_/MM_W*_
  (incl. CE-specific MM_WOM_ATTENUATED), MMSYSERR_ / WAVERR_ /
  MIXERR_ codes, TIME_* incl. TIME_CALLBACK_*, WAGC_CLASS_ /
  WAGC_PRIORITY_, MIXER_OBJECTF_ / GETLINEINFOF_ / GETLINECONTROLSF_ /
  GETCONTROLDETAILSF_ / SETCONTROLDETAILSF_, LINE_COMPONENTTYPE_ /
  LINE_LINEF_ / LINE_TARGETTYPE_, CONTROL_CT_CLASS_ / CONTROLTYPE_ /
  CONTROLF_, MXDM_USER, WAVE_MAPPER.  (Desktop WAVE_FORMAT_96* and
  WAVECAPS_SYNC are desktop-only -- confirmed absent from CE prints.)

Verification: make check / crosscheck / e2e GREEN on all six targets
(TU m63: 23 size/offset asserts + shaped usage of all 53+9 entry
points).  windef.h +PUINT (waveInGetID print).  Headers 67 -> 68;
coredll def 620 -> 671; defs 54 -> 55 (mmtimer 9).

### M64 -- Imaging API (imaging.h; no import def)

Imaging book (120 leaves, Graphics and Multimedia Technologies >
Graphics > Imaging), harvested under tools/manifests/imaging.manifest.
New header include/imaging.h (69th; self-contained).  The CE 5.0
Imaging API is a C++ COM API (CLSID_ImagingFactory /
CoCreateInstance, Imaging.h, Imaging.lib).

* Header-name compat: Win32 software expects imaging.h.
* Transcribed CE 5.0 class/struct prints (CE 6.0 twins compared
  token-for-token, identical: ee491598/ee490848/ee490096/ee490079/
  ee491100/ee491044/ee490672): BitmapData, ImageCodecInfo, ImageInfo,
  ColorPalette, PropertyItem, EncoderParameter, EncoderParameters.
* Types: ARGB = DWORD, PixelFormat = INT, PixelFormatID = PixelFormat
  (verbatim prints).  PROPID = ULONG is a recorded own-design closure
  (used by ms932269 PropertyItem and four IImageDecoder pages; no CE
  or Learn page prints its typedef; printed tag values reach 0x509B).
  UNALIGNED carried as a no-op spelling carrier (ms932269 print).
* Enums with printed values: DecoderInitFlag, EncoderParameterValueType
  (1..8), ImageCodecFlags, ImageFlags, ImageLockMode, SinkFlags (first
  three alias ImageFlags).
* Bare enum bodies, unique sequential C reading recorded in the header
  (CE 6.0 twins print the same bare bodies): BufferDisposalFlag (0..3),
  InterpolationHint (0..4), EncoderValue (0..23; the desktop GDI+
  "Using the EncoderValue Enumeration" concept page prints the same
  members in the same order with explicit 0..23 -- recorded
  corroboration; desktop-only ColorTypeGray/ColorTypeRGB excluded).
* MAKEARGB + ALPHA/RED/GREEN/BLUE_SHIFT + ALPHA_MASK: fully printed
  (ms932026), transcribed verbatim.
* PropertyTag Values (ms932271): all 217 property tags defined from the
  printed Tag column (archive line-join traps re-parsed entry-by-entry:
  ExifPixXDim 0xA002 vs ExifPixYDim 0xA003, ThumbnailResolutionX/Y
  0x502D/0x502E, Gamma 0x0301, DotRange 0x0150).
* Interfaces (7): opaque forward declarations + 72 verbatim
  method-signature records (M44 objbase.h policy; no vtable layouts
  are published anywhere).  Dangling names recorded: IPropertySetStorage
  (BeginDecode), IID_IBasicBitmapOps (ms939536), CodecIImageBytes.
* No import def: the 58 "Link Library: Imaging.lib" rows sit on METHOD
  pages (virtual calls, not import-library symbols) -- gen-doc-def.py
  confirms no sole-link export surface (shobjidl.h precedent).
* Held (name-only, zero-gap): PropertyTagType* (8; desktop page also
  values-less), IMGERR_* (11) + standard E_INVALIDARG/E_OUTOFMEMORY/
  E_NOTIMPL/E_ACCESSDENIED/E_PENDING (names only), every Imaging GUID
  (ImageFormat* x11 incl. "Not supported" EMF/WMF, FrameDimension* x3,
  FormatID* x2, DECODER_* x5, Encoder* x10 + CodecIImageBytes,
  CLSID_ImagingFactory), PixelFormat flag names (9) + composites (16,
  printed as expressions of the held flags) + PixelFormatMax.

Verification: make check / crosscheck / e2e GREEN on all six targets
(TU m64: 10 size/offset asserts + 8 enum-value asserts + 6 PropertyTag
spot checks + shaped usage).  Headers 68 -> 69; defs 55 (unchanged
count; no Imaging import surface is documentable).

### M65 -- Pocket Outlook Object Model (pimstore.h; no import def)

POOM book (90 leaves, Applications and Services Development > Pocket
Outlook Object Model (POOM)), harvested under
tools/manifests/poom.manifest.  New header include/pimstore.h (70th;
self-contained).  The CE POOM is a C++ COM API (CLSID_Application /
CoCreateInstance, Pimstore.h, Pimstore.lib, CE 2.0+).

* CePimCommand (ms863874): the one free function -- a menu add-in
  entry point the add-in DLL must define and expose; prototype +
  PFNCEPIMCOMMAND typedef declared, and the name added to gen-doc-def.py
  NOT_EXPORTS (user-side export, not an import; the M63 waveInProc /
  waveOutProc callback decision).  PIMTYPE printed verbatim with values
  (PT_CALENDAR=0, PT_TASKS, PT_CONTACT; the page also notes the
  Palm-sized PC 1.2 alternative ordering PT_CONTACT=0, recorded).
* Constants (aa513746): all 36 ol* values printed -- Task Priorities
  (olImportanceLow/Normal/High), Folder types (olFolderCalendar 9,
  olFolderContacts 10, olFolderTasks 13, olFolderInfrared 102), Item
  types (olAppointmentItem/olContactItem/olTaskItem 1/2/3), Recurrence
  Types (olRecursDaily..olRecursYearNth 0,1,2,3,5,6), Days of Week
  (olSunday..olSaturday 1,2,4,8,16,32,64), Reminder Options (olLED,
  olVibrate, olDialog, olSound, olRepeat 1,2,4,8,16), Busy Status
  (olFree/olTentative/olBusy/olOutOfOffice), Sensitivity (olNormal 0,
  olPrivate 2), Meeting Status (olNonMeeting/olMeeting).
* Interfaces (13, aa513748): opaque forward declarations + verbatim
  records: 41 method signatures (method pages) and 233 property
  accessors (the "Properties in Vtable Order" tables; accessor order
  preserved, but the properties/methods interleaving in the vtable is
  not published -- no vtable invented, M44 policy).
* Archive-print traps recorded verbatim: eaten type spaces
  (BSTRpwszName, DATEdate, intiIndex, VARIANT_BOOLfDisplayUI,
  VARIANT_BOOLfDescending), the eaten asterisk in "void pReserved"
  (CePimCommand), the doc's own misspellings (ITask
  ClearReccurencePattern; GetRecurrence printed under the
  GetRecurrencePattern title; Irecipients / Iexceptions / Iappointment
  in accessor prints), and the SAL annotations /*[out]*//*[in]*/
  stripped from the recorded accessor lines.
* Dangling names recorded (no CE 5.0 page): IDispatch, CEOID
  (GetItemFromOid -- to be landed with the CEDB remainder milestone),
  CEBLOB (BodyInk), IAppointmentItem (GetOccurrence print),
  CLSID_Application / IID_IPOutlookApp (Logon example; GUID values not
  published).  IPOlRecipient documented as derived from IRecipient.
* No import def: the 67 Pimstore.lib rows sit on method/property/
  interface pages (virtual calls) plus the user-side CePimCommand --
  gen-doc-def.py confirms no sole-link export surface.

Verification: make check / crosscheck / e2e GREEN on all six targets
(TU m65: 5 value asserts + shaped usage incl. the CePimCommand call
and all 13 opaque interface pointers).  Headers 69 -> 70; defs 55
(unchanged count; no POOM import surface is documentable).

### M66 -- MSXML / XML Core Services (msxml2.h; no import def)

XML book (501 leaves, Applications and Services Development > XML),
harvested under tools/manifests/msxml.manifest.  New header
include/msxml2.h (71st; self-contained; the Requirements rows print
"Header: Msxml2.h, Msxml2.idl" -- the file name is the compat surface).

* DOMNodeType (ms897200): verbatim enum print + printed element values
  NODE_ELEMENT (1) .. NODE_NOTATION (12); NODE_INVALID = 0 by position
  (zeroth element, no description printed -- recorded sequential
  reading).  The nodeType property page (ms892577) re-prints the same
  values.
* Interfaces (35 overview pages): opaque forward declarations --
  21 XML DOM interfaces + IXMLDOMSelection +
  XMLSchemaCache/IXMLDOMSchemaCollection + IXMLHTTPRequest +
  IXTLRuntime + 10 ISAX_/IMX_ interfaces.  The XML Minimal Parser
  (ms897202) is a subset view of the SAX set (ISAXAttributes,
  ISAXContentHandler, ISAXXMLReader + "two co-classes that implement
  the XML Reader interface", unnamed).
* Verbatim method/accessor records for all 243 pages carrying C/C++
  Syntax prints: 153 shared XML DOM method/property pages, 8 XSLT
  (IXTLRuntime) methods, 14 XML HTTP pages, 68 SAX pages (per
  interface).  IMXWriter/IMXReaderControl properties print the
  attribute style "[propget]HRESULTxxx(...)" / "[propput]" forms --
  recorded as printed.
* Archive-print traps preserved: eaten type spaces (BSTRbstrNodeName,
  VARIANTvarDate, intnIndex, Idispatch*), SAL-less parameter lists,
  "abort( )" vs "abort( void )" variants.
* Events: ondataavailable (ms892606) / onreadystatechange (ms892608)
  print "HRESULT onXxx( void );" C/C++ event signatures;
  ontransformnode (ms892611) is script-only (no C/C++ section).
* No import def: all 174 "Link Library: Uuid.lib" rows sit on
  interface/method/property pages (GUID linkage, not import-library
  export symbols) -- gen-doc-def.py uuid-doc.def co-listed skip count
  35 -> 201; no sole-link export surface exists.
* Held/catalogued (not C API): every IID_/CLSID_ GUID value (Uuid.lib
  implies linkage; values not published), DOMDocument coclass progID
  "Msxml2.DOMDocument" (CLSID value held), the four error-message
  pages (IXMLParseError ms891734 / XML DOM ms897201 / XQL ms897210 /
  XSLT ms897361 -- message text tables, no error constants), the
  XPath/XQL function pages and XSLT element pages (scripting-level),
  msxsl:script.  IXMLDOMDocument (base interface) and IXMLDSOControl
  appear nowhere in the CE 5.0 book (recorded absent).

Verification: make check / crosscheck / e2e GREEN on all six targets
(TU m66: 12 DOMNodeType value asserts + shaped usage of all 35 opaque
interface pointers).  Headers 70 -> 71; defs 55 (unchanged count; the
Uuid.lib rows yield no import surface).

### M67 -- Direct3D Mobile (d3dm.h; d3dm def +1)

Direct3D Mobile book (416 leaves, Graphics and Multimedia Technologies
> Graphics > Direct3D Mobile), harvested under
tools/manifests/d3dm.manifest.  New header include/d3dm.h (72nd;
self-contained).  Requirements rows: D3dm.h (API/functions/D3DMERR),
D3dmtypes.h (types/enums/structs/macros), D3dmcaps.h (D3DMCAPS).

* Entry point: Direct3DMobileCreate (aa451581, verbatim print
  "IDirect3DMobile* WINAPI Direct3DMobileCreate( UINT SDKVersion)";
  D3dm.lib row) -- def/d3dm-doc.def, 1 export (the only free-function
  import surface; d3dmguid.lib co-listed rows are GUID linkage, no
  def).
* Types: D3DMVALUE = signed int (ms907756), D3DMCOLOR = ULONG
  (ms939142) -- verbatim prints.
* 27 enums with fully printed values (D3DMFORMAT 32 values, D3DMPOOL,
  D3DMBLEND, ... D3DMZBUFFERTYPE; every enum body carries its values
  plus the trailing FORCE_ULONG/FORCE_DWORD member).
* 15 structures transcribed verbatim: D3DMMATRIX (anonymous union
  with the m[4][4]/_11.._44 print), D3DMDISPLAYMODE, D3DMCAPS
  (D3dmcaps.h), D3DMLIGHT, D3DMMATERIAL, D3DMVIEWPORT, D3DMCLIPSTATUS,
  D3DMLOCKED_RECT, D3DMSURFACE_DESC, D3DMPRESENT_PARAMETERS,
  D3DMDEVICE_CREATION_PARAMETERS, D3DMINDEXBUFFER_DESC,
  D3DMVERTEXBUFFER_DESC, D3DMCOLORVALUE, D3DMVECTOR.
* Macros (verbatim): D3DMCOLOR_ARGB/RGBA/XRGB, D3DMFVF_TEXCOORDSIZE1/2/3
  (recorded exactly as printed -- SIZE2/SIZE3 prints drop the shift
  factor), D3DMFVF_TEXCOORDFIXED/FLOAT, D3DM_MAKE_RSVALUE,
  D3DMRENDERSTATE_WRAPBIAS = 32, D3DMPV_DONOTCOPYDATA/D3DMPV_VALID.
* D3DMERR: _FACD3DM = 0x877, MAKE_D3DMHRESULT (ms932027 verbatim) and
  23 D3DMERR_* codes (aa451582 printed code numbers 2078..2158).
  MAKE_HRESULT is referenced by the CE print but defined on no CE
  page; its expansion is published by the official desktop winerror.h
  page (nf-winerror-make_hresult) -- added to include/winerror.h under
  that grounding with the derivation recorded (M52 precedent).
* D3DM_MAKE_D3DMVALUE (ms907763): C++ inline overloads; recorded
  verbatim, not compiled (not expressible in C).
* Interfaces (8 overview pages + dangling IDirect3DMobileBaseTexture,
  method pages only): opaque forward declarations + 101 verbatim
  method-signature records (M44 policy).
* Held (name-only Values pages / absent values): D3DMCLEAR, D3DMLOCK,
  D3DMUSAGE, D3DMFVF (incl. TEXCOORDCOUNTn / TEXCOORDFORMAT_*), the 16
  capability-bit families (D3DMDEVCAPS .. D3DMVTXPCAPS), D3DMPRESENT,
  D3DMCREATE, D3DMTA, D3DMTSS_TCI, D3DMWRAPCOORD, D3DMCS,
  D3DMCURRENT_DISPLAY_MODE, D3DMADAPTER, remaining D3DMERR beyond the
  23 printed, driver-side DDI value pages (D3DM_DRIVER, D3DM_GETINFO,
  D3DMRTYPEFLAG, D3DMTSS_TEXTUREOP); IID_ GUID names (ms912040),
  D3D_SDK_VERSION (value not published),
  MAX_DEVICE_IDENTIFIER_STRING (holds D3DMADAPTER_IDENTIFIER -- its
  verbatim print is recorded in the header, not compiled);
  CustomVertexFormat example (aa451366, not API).

Verification: make check / crosscheck / e2e GREEN on all six targets
(TU m67: 7 size asserts + 8 value asserts incl. the MAKE_D3DMHRESULT
identity + shaped usage with the Direct3DMobileCreate call).  Headers
71 -> 72; defs 55 -> 56 (d3dm 1).

### M68 -- Speech API (SAPI 5.0) (sapi.h; no import def)

Speech API (SAPI) 5.0 book (491 leaves, Applications and Services
Development > Speech API (SAPI) 5.0), harvested under
tools/manifests/sapi.manifest.  New header include/sapi.h (73rd;
self-contained; includes mmsystem.h for WAVEFORMATEX -- the SAPI
Structures book re-prints it identically).  Requirements rows:
Sapi.h/Sapi.idl (app interfaces), Sapiddk.h/Sapiddk.idl (engine DDI
interfaces), Sphelper.h (helpers).

* 79 enums/structures transcribed verbatim (printed values where
  printed; sequential bodies recorded where bare): SPEVENT
  ([restricted] print), SPEVENTENUM, SPEAKFLAGS, SPSTREAMFORMAT,
  SPPARTOFSPEECH, SPVSTATE, SPPHRASE (+RULE/PROPERTY/ELEMENT/
  REPLACEMENT/ALT/ALTREQUEST linked-list family -- self-references
  carried in the C struct-keyword form), SPVOICESTATUS, SPWORD /
  SPWORDPRONUNCIATION / lists, SPRECO* family, SPAUDIO* family, and
  the rest of the 40-structure + 41-enumeration books.
* Eaten-space archive prints repaired mechanically with a recorded
  type dictionary (ULONGulSize -> ULONG ulSize etc.); the doc's own
  missing comma in SPRECOEVENTFLAGS and the SPRECOECOEVENTFLAGS /
  SPSTREAMFORMATTYPE closing-name typos are recorded in the header.
* Handle/id carrier closures (recorded own-design closures, no CE
  page prints their typedefs): SPSTATEHANDLE / SPGRAMMARHANDLE /
  SPRULEHANDLE / SPTRANSITIONID = void*, SPPHONEID = WCHAR.
* Interfaces: 49 overview pages + dangling ISpPhraseBuilder (print-
  referenced) -- opaque forward declarations + 298 verbatim
  method-signature records (M44 policy).
* Sphelper.h helpers (25 pages: SPBindToFile, SpCreateObjectFromToken,
  ... -- printed as C++ inline functions/templates): recorded verbatim,
  not compiled, no import entries (header-side code; the MSXML
  Uuid.lib precedent).  SPFEI macro recorded.
* Held: SPRECOGNIZERSTATUS (ms895729 -- sizes aLangID with
  SP_MAX_LANGIDS whose value is not published anywhere; verbatim
  record only, the M67 D3DMADAPTER_IDENTIFIER decision), SAPI Class
  IDs (ms893442) / Token Category IDs (aa513788) / Global Variables
  (aa513761) name lists (GUID values held), SPNOTIFYCALLBACK
  (callback name only).
* No import def: all 373 Sapilib.lib rows sit on interface/method/
  helper pages (virtual calls / header-side code) -- gen-doc-def.py
  confirms no sole-link export surface.

Verification: make check / crosscheck / e2e GREEN on all six targets
(TU m68: 3 size asserts + 10 enum-value asserts + shaped usage of 23
opaque interface pointers).  Headers 72 -> 73; defs 56 (unchanged
count).
