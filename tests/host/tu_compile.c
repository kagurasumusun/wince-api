/* TU smoke test for the Akari API headers (host, compile-only).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Compiled with -c for each CE generation value of _WIN32_WCE
 * (0x420, 0x500, 0x600).  Exercises every shipped declaration and the
 * generic-text mappings; verifies the target-independent type widths.
 * Pointer sizes are verified when the host is 32-bit; the 32-bit
 * pointer model itself is checked on the real CE toolchain later
 * (see docs/verification.md).
 */

#include <windows.h>
#include <stddef.h>

/* Type-width invariants of the CE ABI (32-bit, 16-bit wchar). */
typedef char assert_wchar_size[(sizeof(WCHAR) == 2) ? 1 : -1];
typedef char assert_dword_size[(sizeof(DWORD) == 4) ? 1 : -1];
typedef char assert_long_size[(sizeof(LONG) == 4) ? 1 : -1];
typedef char assert_handle_pointer[(sizeof(HANDLE) == sizeof(void *)) ? 1 : -1];

#if __SIZEOF_POINTER__ == 4
typedef char assert_ce_pointer_size[(sizeof(HANDLE) == 4) ? 1 : -1];
typedef char assert_ce_ulongptr_size[(sizeof(ULONG_PTR) == 4) ? 1 : -1];
#endif

/* Reference every declared function (no calls, compile-only). */
static const void *const api_symbols[] = {
    (const void *) &TerminateProcess,
    (const void *) &TerminateThread,
    (const void *) &ExitThread,
    (const void *) &ExitProcess,
    (const void *) &GetModuleHandleW,
    (const void *) &GetModuleHandle,
    (const void *) &GetModuleFileNameW,
    (const void *) &GetModuleFileName,
    (const void *) &GetCommandLineW,
    (const void *) &GetCommandLine,
    (const void *) &GetProcAddressW,
    (const void *) &GetProcAddressA,
    (const void *) &GetProcAddress,
    (const void *) &LocalAlloc,
    (const void *) &LocalFree,
    (const void *) &GetLastError,
    (const void *) &CreateThread,
    (const void *) &CreateProcessW,
    (const void *) &CreateProcess,
    (const void *) &LoadLibraryW,
    (const void *) &LoadLibrary,
    (const void *) &FreeLibrary,
    (const void *) &CloseHandle,
    (const void *) &OpenProcess,
    (const void *) &GetExitCodeProcess,
    (const void *) &SetLastError,
    (const void *) &GetExitCodeThread,
    (const void *) &SuspendThread,
    (const void *) &ResumeThread,
    (const void *) &Sleep,
    (const void *) &GetThreadPriority,
    (const void *) &SetThreadPriority,
    (const void *) &TlsAlloc,
    (const void *) &TlsFree,
    (const void *) &TlsSetValue,
    (const void *) &TlsGetValue,
    (const void *) &LoadLibraryEx,
    (const void *) &LoadLibraryExW,
    (const void *) &CreateFile,
    (const void *) &CreateFileW,
    (const void *) &DeleteFile,
    (const void *) &DeleteFileW,
    (const void *) &FindFirstFile,
    (const void *) &FindFirstFileW,
    (const void *) &FindNextFile,
    (const void *) &FindNextFileW,
    (const void *) &FindClose,
    (const void *) &GetFileAttributes,
    (const void *) &GetFileAttributesW,
    (const void *) &ReadFile,
    (const void *) &WriteFile,
    (const void *) &GetFileSize,
    (const void *) &SetFilePointer,
    (const void *) &SetEndOfFile,
    (const void *) &FlushFileBuffers,
    (const void *) &MoveFileW,
    (const void *) &MoveFile,
    (const void *) &CopyFileW,
    (const void *) &CopyFile,
    (const void *) &CreateDirectoryW,
    (const void *) &CreateDirectory,
    (const void *) &RemoveDirectoryW,
    (const void *) &RemoveDirectory,
    (const void *) &SetFileAttributesW,
    (const void *) &SetFileAttributes,
    (const void *) &CreateEventW,
    (const void *) &CreateEvent,
    (const void *) &OpenEventW,
    (const void *) &OpenEvent,
    (const void *) &SetEvent,
    (const void *) &ResetEvent,
    (const void *) &PulseEvent,
    (const void *) &CreateMutexW,
    (const void *) &CreateMutex,
    (const void *) &ReleaseMutex,
    (const void *) &CreateSemaphoreW,
    (const void *) &CreateSemaphore,
    (const void *) &ReleaseSemaphore,
    (const void *) &WaitForSingleObject,
    (const void *) &WaitForMultipleObjects,
    (const void *) &DuplicateHandle,
    (const void *) &InitializeCriticalSection,
    (const void *) &EnterCriticalSection,
    (const void *) &LeaveCriticalSection,
    (const void *) &DeleteCriticalSection,
    (const void *) &TryEnterCriticalSection,
    (const void *) &InterlockedExchange,
    (const void *) &InterlockedIncrement,
    (const void *) &InterlockedDecrement,
    (const void *) &InterlockedExchangeAdd,
    (const void *) &InterlockedCompareExchange,
    (const void *) &InterlockedTestExchange,
    (const void *) &InterlockedExchangePointer,
    (const void *) &InterlockedCompareExchangePointer,
    (const void *) &GetLocalTime,
    (const void *) &GetSystemTime,
    (const void *) &SetLocalTime,
    (const void *) &SetSystemTime,
    (const void *) &FileTimeToLocalFileTime,
    (const void *) &LocalFileTimeToFileTime,
    (const void *) &FileTimeToSystemTime,
    (const void *) &SystemTimeToFileTime,
    /* M10: memory management (heaps/local/status/probes). */
    (const void *) &GetProcessHeap,
    (const void *) &HeapCreate,
    (const void *) &HeapDestroy,
    (const void *) &HeapAlloc,
    (const void *) &HeapFree,
    (const void *) &HeapReAlloc,
    (const void *) &HeapSize,
    (const void *) &HeapValidate,
    (const void *) &HeapCompact,
    (const void *) &LocalReAlloc,
    (const void *) &LocalSize,
    (const void *) &GlobalMemoryStatus,
    (const void *) &IsBadCodePtr,
    (const void *) &IsBadReadPtr,
    (const void *) &IsBadWritePtr,
    /* M10: ticks/file times/time helpers. */
    (const void *) &GetTickCount,
    (const void *) &GetFileTime,
    (const void *) &SetFileTime,
    (const void *) &CompareFileTime,
    (const void *) &GetCurrentFT,
    (const void *) &GetIdleTime,
    (const void *) &Random,
    (const void *) &SetDaylightTime,
    (const void *) &QueryPerformanceCounter,
    (const void *) &QueryPerformanceFrequency,
    /* M11: system information. */
    (const void *) &GetSystemInfo,
    (const void *) &GetVersionEx,
    (const void *) &SignalStarted,
    /* M12: virtual memory / time zone / times. */
    (const void *) &VirtualAlloc,
    (const void *) &VirtualFree,
    (const void *) &VirtualProtect,
    (const void *) &VirtualQuery,
    (const void *) &FlushInstructionCache,
    (const void *) &GetProcessVersion,
    (const void *) &GetDllVersion,
    (const void *) &GetThreadTimes,
    (const void *) &GetTimeZoneInformation,
    (const void *) &SetTimeZoneInformation,
    /* M13: code-page / NLS (winnls.h). */
    (const void *) &MultiByteToWideChar,
    (const void *) &WideCharToMultiByte,
    (const void *) &IsDBCSLeadByte,
    (const void *) &IsDBCSLeadByteEx,
    /* M14: fibers (CE .NET 4.0+). */
    (const void *) &CreateFiber,
    (const void *) &ConvertThreadToFiber,
    (const void *) &DeleteFiber,
    (const void *) &GetCurrentFiber,
    (const void *) &GetFiberData,
    (const void *) &SwitchToFiber,
    /* M15: registry (winreg.h). */
    (const void *) &RegOpenKeyExW, (const void *) &RegOpenKeyEx,
    (const void *) &RegCreateKeyExW, (const void *) &RegCreateKeyEx,
    (const void *) &RegDeleteKeyW, (const void *) &RegDeleteKey,
    (const void *) &RegDeleteValueW, (const void *) &RegDeleteValue,
    (const void *) &RegEnumKeyExW, (const void *) &RegEnumKeyEx,
    (const void *) &RegEnumValueW, (const void *) &RegEnumValue,
    (const void *) &RegQueryInfoKeyW, (const void *) &RegQueryInfoKey,
    (const void *) &RegQueryValueExW, (const void *) &RegQueryValueEx,
    (const void *) &RegSetValueExW, (const void *) &RegSetValueEx,
    (const void *) &RegFlushKeyW, (const void *) &RegFlushKey,
    (const void *) &CeFindFirstRegChange,
    (const void *) &CeFindNextRegChange,
    (const void *) &CeFindCloseRegChange,
};

/* File structures: layout checks (winbase.h).  CE 32-bit: each
 * FILETIME = 8 bytes; WIN32_FIND_DATAW has no alternate-name member
 * on CE (dwOID instead), so offsetof(cFileName) must be 4+3*8+4+4+4
 * = 40 and the total size 40+260*2 = 560. */
typedef char assert_filetime_size[sizeof(FILETIME) == 8 ? 1 : -1];
typedef char assert_finddata_offsets[
    (offsetof(WIN32_FIND_DATAW, ftCreationTime) == 4 &&
     offsetof(WIN32_FIND_DATAW, ftLastWriteTime) == 20 &&
     offsetof(WIN32_FIND_DATAW, nFileSizeHigh) == 28 &&
     offsetof(WIN32_FIND_DATAW, dwOID) == 36 &&
     offsetof(WIN32_FIND_DATAW, cFileName) == 40 &&
     sizeof(WIN32_FIND_DATAW) == 560) ? 1 : -1];

/* File constants exercised (winbase.h + winerror.h). */
typedef char assert_file_vals[
    (MAX_PATH == 260 &&
     FILE_ATTRIBUTE_READONLY == 1u &&
     FILE_ATTRIBUTE_DIRECTORY == 0x10u &&
     FILE_ATTRIBUTE_ENCRYPTED == 0x4000u &&
     GENERIC_READ == 0x80000000u &&
     GENERIC_WRITE == 0x40000000u &&
     FILE_SHARE_READ == 1u &&
     CREATE_NEW == 1u && CREATE_ALWAYS == 2u &&
     OPEN_EXISTING == 3u && OPEN_ALWAYS == 4u &&
     TRUNCATE_EXISTING == 5u &&
     FILE_FLAG_WRITE_THROUGH == 0x80000000u &&
     ERROR_NO_MORE_FILES == 18L) ? 1 : -1];

/* File-pointer constants (winbase.h, ms891933 + Win32 ABI values). */
typedef char assert_fileptr_vals[
    (FILE_BEGIN == 0u && FILE_CURRENT == 1u && FILE_END == 2u &&
     INVALID_SET_FILE_POINTER == (DWORD)0xFFFFFFFFu) ? 1 : -1];

/* Synchronization constants (winbase.h; names per CE pages
 * ms885177/aa450988/aa450987/ms885208; numeric values are the fixed
 * Win32 ABI values). */
typedef char assert_sync_vals[
    (WAIT_OBJECT_0 == 0u && WAIT_ABANDONED_0 == 0x80u &&
     WAIT_TIMEOUT == 0x102u && WAIT_FAILED == (DWORD)0xFFFFFFFFu &&
     MAXIMUM_WAIT_OBJECTS == 64 &&
     DUPLICATE_CLOSE_SOURCE == 1u && DUPLICATE_SAME_ACCESS == 2u &&
     EVENT_ALL_ACCESS == 0x1F0003u) ? 1 : -1];

/* 64-bit integer forms and their unions (winnt.h). */
typedef char assert_large_int_size[sizeof(LARGE_INTEGER) == 8 ? 1 : -1];
typedef char assert_ll_size[sizeof(LONGLONG) == 8 ? 1 : -1];

#if __SIZEOF_POINTER__ == 4
/* CRITICAL_SECTION layout on 32-bit (desktop-official member order
 * recorded in winnt.h): the six fields occupy 24 bytes. */
typedef char assert_cs_layout[
    (offsetof(CRITICAL_SECTION, DebugInfo) == 0 &&
     offsetof(CRITICAL_SECTION, LockCount) == 4 &&
     offsetof(CRITICAL_SECTION, RecursionCount) == 8 &&
     offsetof(CRITICAL_SECTION, OwningThread) == 12 &&
     offsetof(CRITICAL_SECTION, LockSemaphore) == 16 &&
     offsetof(CRITICAL_SECTION, SpinCount) == 20 &&
     sizeof(CRITICAL_SECTION) == 24) ? 1 : -1];
typedef char assert_li_layout[
    (offsetof(LARGE_INTEGER, QuadPart) == 0) ? 1 : -1];
#endif
typedef char assert_tls_vals[
    (TLS_MINIMUM_AVAILABLE == 64 &&
     TLS_OUT_OF_INDEXES == (DWORD)0xFFFFFFFFu) ? 1 : -1];

/* LoadLibraryEx flags (winbase.h, values per official Win32 ABI). */
typedef char assert_loadlib_flags[
    (DONT_RESOLVE_DLL_REFERENCES == 1u &&
     LOAD_LIBRARY_AS_DATAFILE == 2u &&
     LOAD_WITH_ALTERED_SEARCH_PATH == 8u) ? 1 : -1];

/* CE thread-priority constants (winbase.h): legacy 8-level scale
 * with NORMAL = 3 (old level n maps to new level 248+n, so NORMAL's
 * new-scale value is 251 per ms885643/aa450891). */
typedef char assert_priority_vals[
    (THREAD_PRIORITY_TIME_CRITICAL == 0 &&
     THREAD_PRIORITY_NORMAL == 3 &&
     THREAD_PRIORITY_IDLE == 7 &&
     THREAD_PRIORITY_ERROR_RETURN == (int)0x7FFFFFFF &&
     INFINITE == 0xFFFFFFFFu) ? 1 : -1];

/* Error constants exercised (values from winerror.h, per the official
 * CE numeric table aa450919 rows 0-1078; spot checks cover each
 * numeric group edge plus the independently cited constants). */
typedef char assert_winerror_vals[
    (ERROR_SUCCESS == 0 && NO_ERROR == 0 &&
     ERROR_TOO_MANY_OPEN_FILES == 4 && ERROR_ACCESS_DENIED == 5 &&
     ERROR_OUTOFMEMORY == 14 && ERROR_NO_MORE_FILES == 18 &&
     ERROR_HANDLE_DISK_FULL == 39 && ERROR_NOT_SUPPORTED == 50 &&
     ERROR_NETNAME_DELETED == 64 && ERROR_FILE_EXISTS == 80 &&
     ERROR_INVALID_PARAMETER == 87 && ERROR_TOO_MANY_SEMAPHORES == 100 &&
     ERROR_BROKEN_PIPE == 109 && ERROR_BUFFER_OVERFLOW == 111 &&
     ERROR_DISK_FULL == 112 && ERROR_CALL_NOT_IMPLEMENTED == 120 &&
     ERROR_INSUFFICIENT_BUFFER == 122 && ERROR_INVALID_NAME == 123 &&
     ERROR_MOD_NOT_FOUND == 126 && ERROR_PROC_NOT_FOUND == 127 &&
     ERROR_DIR_NOT_EMPTY == 145 && ERROR_SIGNAL_PENDING == 162 &&
     ERROR_BUSY == 170 && ERROR_ALREADY_EXISTS == 183 &&
     ERROR_BAD_EXE_FORMAT == 193 && ERROR_EXE_MACHINE_TYPE_MISMATCH == 216 &&
     ERROR_BAD_PIPE == 230 && ERROR_PIPE_BUSY == 231 &&
     ERROR_NO_DATA == 232 && ERROR_MORE_DATA == 234 &&
     ERROR_NO_MORE_ITEMS == 259 && STILL_ACTIVE == 259 &&
     ERROR_DIRECTORY == 267 && ERROR_NOT_OWNER == 288 &&
     ERROR_PARTIAL_COPY == 299 && ERROR_PIPE_LISTENING == 536 &&
     ERROR_IO_PENDING == 997 && ERROR_NOACCESS == 998 &&
     ERROR_STACK_OVERFLOW == 1001 && ERROR_UNRECOGNIZED_VOLUME == 1005 &&
     ERROR_BADDB == 1009 && ERROR_KEY_DELETED == 1018 &&
     ERROR_DUPLICATE_SERVICE_NAME == 1078 &&
     ERROR_NO_UNICODE_TRANSLATION == 1113) ? 1 : -1];

/* Time structures (winbase.h): SYSTEMTIME is eight WORDs in the
 * documented order (aa450923), so sizeof must be 16. */
typedef char assert_systemtime_size[sizeof(SYSTEMTIME) == 16 ? 1 : -1];
typedef char assert_systemtime_offsets[
    (offsetof(SYSTEMTIME, wYear) == 0 &&
     offsetof(SYSTEMTIME, wMonth) == 2 &&
     offsetof(SYSTEMTIME, wDayOfWeek) == 4 &&
     offsetof(SYSTEMTIME, wDay) == 6 &&
     offsetof(SYSTEMTIME, wHour) == 8 &&
     offsetof(SYSTEMTIME, wMinute) == 10 &&
     offsetof(SYSTEMTIME, wSecond) == 12 &&
     offsetof(SYSTEMTIME, wMilliseconds) == 14) ? 1 : -1];

/* M10 memory constants (winbase.h): heap flags (numeric values are
 * the fixed Win32 ABI values) and the local-allocation flags. */
typedef char assert_heap_vals[
    (HEAP_NO_SERIALIZE == 0x1u && HEAP_ZERO_MEMORY == 0x8u &&
     MAXDWORD == (DWORD)0xFFFFFFFFu) ? 1 : -1];

/* M10 MEMORYSTATUS layout (winbase.h, ms886753): eight DWORDs,
 * dwAvailVirtual last (no desktop-only dwAvailExtendedVirtual). */
typedef char assert_memstatus_layout[
    (offsetof(MEMORYSTATUS, dwLength) == 0 &&
     offsetof(MEMORYSTATUS, dwMemoryLoad) == 4 &&
     offsetof(MEMORYSTATUS, dwAvailVirtual) == 28 &&
     sizeof(MEMORYSTATUS) == 32) ? 1 : -1];

/* M11 system-information layout (winbase.h, from the CE pages):
 * SYSTEM_INFO is 36 bytes on 32-bit CE (union + 7 DWORDs + 2 WORDs)
 * with the anonymous dwOemId union first; OSVERSIONINFO is
 * 5 DWORDs + 128 TCHARs = 276 bytes. */
#if __SIZEOF_POINTER__ == 4
/* SYSTEM_INFO layout is pointer-dependent; checked only on 32-bit
 * hosts and, precisely, by the CE toolchain matrix (32-bit model). */
typedef char assert_sysinfo_layout[
    (offsetof(SYSTEM_INFO, dwPageSize) == 4 &&
     offsetof(SYSTEM_INFO, lpMinimumApplicationAddress) == 8 &&
     offsetof(SYSTEM_INFO, dwAllocationGranularity) == 28 &&
     offsetof(SYSTEM_INFO, wProcessorLevel) == 32 &&
     offsetof(SYSTEM_INFO, wProcessorRevision) == 34 &&
     sizeof(SYSTEM_INFO) == 36) ? 1 : -1];
#endif
typedef char assert_osversioninfo_layout[
    (offsetof(OSVERSIONINFO, dwPlatformId) == 16 &&
     offsetof(OSVERSIONINFO, szCSDVersion) == 20 &&
     sizeof(OSVERSIONINFO) == 276) ? 1 : -1];
typedef char assert_sysinfo_vals[
    (PROCESSOR_ARCHITECTURE_INTEL == 0 &&
     PROCESSOR_ARCHITECTURE_ARM == 5 &&
     PROCESSOR_ARCHITECTURE_UNKNOWN == 0xFFFF &&
     VER_PLATFORM_WIN32s == 0 &&
     VER_PLATFORM_WIN32_WINDOWS == 1 &&
     VER_PLATFORM_WIN32_NT == 2 &&
     VER_PLATFORM_WIN32_CE == 3) ? 1 : -1];

/* M12 memory/time-zone constants (winbase.h/winnt.h; values per the
 * fixed Win32 ABI). */
typedef char assert_m12_vals[
    (MEM_COMMIT == 0x1000u && MEM_RESERVE == 0x2000u &&
     MEM_DECOMMIT == 0x4000u && MEM_RELEASE == 0x8000u &&
     MEM_FREE == 0x10000u && MEM_PRIVATE == 0x20000u &&
     MEM_MAPPED == 0x40000u && MEM_IMAGE == 0x1000000u &&
     PAGE_NOACCESS == 0x1u && PAGE_READONLY == 0x2u &&
     PAGE_READWRITE == 0x4u && PAGE_EXECUTE_READWRITE == 0x40u &&
     PAGE_GUARD == 0x100u && PAGE_NOCACHE == 0x200u &&
     TIME_ZONE_ID_UNKNOWN == 0 && TIME_ZONE_ID_STANDARD == 1 &&
     TIME_ZONE_ID_DAYLIGHT == 2) ? 1 : -1];
#if __SIZEOF_POINTER__ == 4
typedef char assert_mbi_layout[
    (offsetof(MEMORY_BASIC_INFORMATION, AllocationBase) == 4 &&
     offsetof(MEMORY_BASIC_INFORMATION, RegionSize) == 12 &&
     offsetof(MEMORY_BASIC_INFORMATION, State) == 16 &&
     offsetof(MEMORY_BASIC_INFORMATION, Type) == 24 &&
     sizeof(MEMORY_BASIC_INFORMATION) == 28) ? 1 : -1];
#endif
typedef char assert_tzi_layout[
    (offsetof(TIME_ZONE_INFORMATION, StandardName) == 4 &&
     offsetof(TIME_ZONE_INFORMATION, StandardBias) == 84 &&
     offsetof(TIME_ZONE_INFORMATION, DaylightName) == 88 &&
     offsetof(TIME_ZONE_INFORMATION, DaylightBias) == 168 &&
     sizeof(TIME_ZONE_INFORMATION) == 172) ? 1 : -1];

static const unsigned api_flags[] = {
    LMEM_FIXED, LMEM_ZEROINIT, LPTR,
    HEAP_NO_SERIALIZE, HEAP_ZERO_MEMORY,
};

/* Generic-text forms are the wide ones on CE. */
typedef char assert_tchar_wide[(sizeof(TCHAR) == sizeof(WCHAR)) ? 1 : -1];
typedef char assert_lpctstr_wide[(sizeof(LPCTSTR) == sizeof(LPCWSTR)) ? 1 : -1];

/* PROCESS_INFORMATION field order (official structure page ms886775
 * is pending full transcription; layout below is the standard
 * hProcess/hThread/dwProcessId/dwThreadId order). */
typedef char assert_pi_first[(offsetof(PROCESS_INFORMATION, hProcess) == 0) ? 1 : -1];

/* CE-shaped usage snippets (compile-only): process creation passes
 * NULL/FALSE for every unsupported parameter, per ms885182; the
 * thread entry type is exercised through CreateThread's signature. */
static DWORD worker(LPVOID p)
{
    return p != 0;
}

/* Wide-string literals are 32-bit wchar_t on the host but 16-bit on
 * the CE target; build explicit WCHAR strings so the TU is
 * host-independent. */
static const WCHAR w_app[] = { 'a', 'p', 'p', '.', 'e', 'x', 'e', 0 };
static const WCHAR w_cmd[] = {
    'a', 'p', 'p', '.', 'e', 'x', 'e', ' ', 'a', 'r', 'g', 0
};
static const WCHAR w_file[] = {
    't', 'm', 'p', '\\', 'f', '.', 't', 'x', 't', 0
};
static const WCHAR w_copy[] = {
    't', 'm', 'p', '\\', 'f', '2', '.', 't', 'x', 't', 0
};
static const WCHAR w_moved[] = {
    't', 'm', 'p', '\\', 'f', '3', '.', 't', 'x', 't', 0
};
static const WCHAR w_dir[] = {
    't', 'm', 'p', '\\', 'd', 'i', 'r', 0
};

static int ce_shaped_usage(void)
{
    PROCESS_INFORMATION pi;
    SYSTEMTIME st;
    FILETIME ft1, ft2;
    HANDLE h, hf;
    DWORD tid, cb, nread, nwrote, sizehi;
    BOOL ok;
    char io_buf[8] = "abcdefg";

    if (!CreateProcessW(w_app, w_cmd, NULL, NULL,
                        FALSE, 0, NULL, NULL, NULL, &pi))
        return (int) GetLastError();
    h = CreateThread(NULL, 0, worker, NULL, 0, &tid);
    if (h == NULL)
        return (int) GetLastError();

    /* Time round trip (compile + exercise): the conversions must
     * succeed for the current clock value on any host. */
    GetLocalTime(&st);
    if (!SystemTimeToFileTime(&st, &ft1))
        return (int) GetLastError();
    if (!FileTimeToLocalFileTime(&ft1, &ft2))
        return (int) GetLastError();
    if (!LocalFileTimeToFileTime(&ft2, &ft1))
        return (int) GetLastError();
    if (!FileTimeToSystemTime(&ft1, &st))
        return (int) GetLastError();
    GetSystemTime(&st);

    /* Synchronous file I/O and file/directory management: exercises
     * the argument types of every declaration of the file batch
     * (ReadFile ms891445, WriteFile ms892380, GetFileSize ms890939,
     * SetFilePointer ms891933, SetEndOfFile ms891916,
     * FlushFileBuffers ms890238, MoveFileW ms891388, CopyFileW
     * aa517309, CreateDirectoryW aa517316, RemoveDirectoryW
     * ms891470, SetFileAttributesW ms891925).  Compile-only: the
     * checks never link or run these calls. */
    hf = CreateFileW(w_file, GENERIC_READ | GENERIC_WRITE,
                     FILE_SHARE_READ, NULL, CREATE_ALWAYS,
                     FILE_ATTRIBUTE_NORMAL, NULL);
    if (hf == INVALID_HANDLE_VALUE)
        return (int) GetLastError();
    ok = WriteFile(hf, io_buf, (DWORD) sizeof(io_buf), &nwrote,
                   NULL) != 0;
    ok = FlushFileBuffers(hf) && ok;
    ok = (SetFilePointer(hf, 0, NULL, FILE_BEGIN)
          != INVALID_SET_FILE_POINTER) && ok;
    cb = GetFileSize(hf, &sizehi);
    ok = (cb != INVALID_SET_FILE_POINTER) && ok;
    ok = SetEndOfFile(hf) && ok;
    ok = ReadFile(hf, io_buf, (DWORD) sizeof(io_buf), &nread,
                  NULL) && ok;
    ok = CloseHandle(hf) && ok;
    ok = CreateDirectoryW(w_dir, NULL) && ok;
    ok = SetFileAttributesW(w_file, FILE_ATTRIBUTE_NORMAL) && ok;
    ok = CopyFileW(w_file, w_copy, FALSE) && ok;
    ok = MoveFileW(w_copy, w_moved) && ok;
    ok = DeleteFileW(w_moved) && ok;
    ok = RemoveDirectoryW(w_dir) && ok;
    if (!ok)
        return (int) GetLastError();
    return (int) (pi.dwProcessId + tid + st.wSecond + cb + nread
                  + nwrote + sizehi);
}

/* Synchronization usage shapes (compile-only; never run): events,
 * mutexes, semaphores, wait functions, critical sections and the
 * interlocked calls, with the CE parameter rules applied (attributes
 * NULL, OpenEvent's EVENT_ALL_ACCESS and bInheritHandle FALSE,
 * DuplicateHandle with bInheritHandle FALSE).  The process handle
 * that DuplicateHandle needs is supplied by a helper that is never
 * executed (the CE kernel-scope GetCurrentProcess is not part of
 * this user-mode header set). */
static HANDLE shape_current_process(void)
{
    return (HANDLE) 0;
}

static DWORD sync_worker(LPVOID p)
{
    LONG x = 0;
    (void) p;
    InterlockedIncrement(&x);
    InterlockedExchangeAdd(&x, 1);
    InterlockedCompareExchange(&x, 0, 1);
    InterlockedTestExchange(&x, 1, 0);
    return (DWORD) x;
}

static int sync_shaped_usage(void)
{
    HANDLE hev, hmut, hsem, hdup;
    CRITICAL_SECTION cs;
    LONG prev;
    DWORD rc;
    LPVOID p = 0;

    InitializeCriticalSection(&cs);
    EnterCriticalSection(&cs);
    if (!TryEnterCriticalSection(&cs))
        return (int) GetLastError();
    LeaveCriticalSection(&cs);
    DeleteCriticalSection(&cs);

    hev = CreateEventW(NULL, FALSE, FALSE, NULL);
    hmut = CreateMutexW(NULL, FALSE, NULL);
    hsem = CreateSemaphoreW(NULL, 0, 1, NULL);
    if (hev == NULL || hmut == NULL || hsem == NULL)
        return (int) GetLastError();
    SetEvent(hev);
    ResetEvent(hev);
    PulseEvent(hev);
    ReleaseMutex(hmut);
    ReleaseSemaphore(hsem, 1, &prev);
    rc = WaitForSingleObject(hev, INFINITE);
    if (rc != WAIT_OBJECT_0)
        return (int) rc;
    rc = WaitForMultipleObjects(1, (const HANDLE[]) { hev }, FALSE,
                                INFINITE);
    hdup = 0;
    if (!DuplicateHandle(shape_current_process(), hev,
                         shape_current_process(), &hdup, 0,
                         FALSE, DUPLICATE_SAME_ACCESS))
        return (int) GetLastError();
    CloseHandle(hdup);
    CloseHandle(hev);
    CloseHandle(hmut);
    CloseHandle(hsem);
    (void) sync_worker(p);
    return 0;
}

/* M10 usage shapes (winbase.h memory + time batch; compile-only for
 * the resource-hungry calls): process heap, private heaps, the local
 * memory completion pair, the memory status/probe functions, ticks,
 * file times, and the performance counter.  Runtime side effects are
 * avoided (no file created: GetFileTime/SetFileTime are only called
 * with INVALID_HANDLE_VALUE and their failure accepted). */
static int m10_shaped_usage(void)
{
    HANDLE hheap, hproc, hf;
    LPVOID blk;
    MEMORYSTATUS ms;
    FILETIME ft, ftc, fta, ftw;
    LARGE_INTEGER qpc, qpf;
    DWORD ticks, idle, rnd, sz;
    BOOL ok = FALSE;
    HLOCAL hloc;

    hproc = GetProcessHeap();
    if (hproc == NULL)
        return (int) GetLastError();
    blk = HeapAlloc(hproc, HEAP_ZERO_MEMORY, 64u);
    if (blk == NULL)
        return (int) GetLastError();
    sz = HeapSize(hproc, 0, blk);
    blk = HeapReAlloc(hproc, HEAP_ZERO_MEMORY, blk, 128u);
    if (blk == NULL)
        return (int) GetLastError();
    ok = (sz >= 64u && HeapSize(hproc, 0, blk) >= sz) && ok;
    ok = HeapFree(hproc, 0, blk) != 0;
    ok = HeapValidate(hproc, 0, NULL) && ok;

    hheap = HeapCreate(0, 0, 0);
    if (hheap == NULL)
        return (int) GetLastError();
    blk = HeapAlloc(hheap, 0, 32u);
    if (blk == NULL)
        return (int) GetLastError();
    ok = HeapSize(hheap, 0, blk) >= 32u && ok;
    ok = HeapFree(hheap, 0, blk) && ok;
    (void) HeapCompact(hheap, 0);
    ok = HeapDestroy(hheap) && ok;

    hloc = LocalReAlloc((HLOCAL) 0, 16u, LMEM_MOVEABLE);
    if (hloc != NULL)
        ok = LocalSize(hloc) != 0 && ok;
    GlobalMemoryStatus(&ms);
    ok = ms.dwLength == sizeof(MEMORYSTATUS) && ok;

    /* Memory-integrity probes (compile shape only). */
    ok = (IsBadCodePtr((FARPROC) 0) != 0) && ok;
    ok = (IsBadReadPtr((const void *) 0, 0u) == 0) && ok;
    ok = (IsBadWritePtr((LPVOID) 0, 0u) == 0) && ok;

    /* Time/tick surface. */
    ticks = GetTickCount();
    idle = GetIdleTime();
    rnd = Random();
    (void) idle; (void) rnd;
    SetDaylightTime(0);
    GetCurrentFT(&ft);
    if (GetFileTime(INVALID_HANDLE_VALUE, &ftc, &fta, &ftw))
        return (int) GetLastError();
    (void) CompareFileTime(&ftc, &ftw);
    hf = CreateFileW(w_file, GENERIC_WRITE, FILE_SHARE_READ, NULL,
                     CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hf != INVALID_HANDLE_VALUE) {
        (void) SetFileTime(hf, NULL, NULL, &ft);
        ok = CloseHandle(hf) && ok;
    }
    ok = (QueryPerformanceCounter(&qpc) != 0) && ok;
    ok = (QueryPerformanceFrequency(&qpf) != 0 && qpf.QuadPart != 0)
         && ok;
    (void) qpc.QuadPart;
    return (ticks == (DWORD) -1) ? (int) ERROR_INVALID_PARAMETER : ok;
}

/* M11 usage shape: system-information report (compile-only; never
 * linked/run). */
static int m11_shaped_usage(void)
{
    SYSTEM_INFO si;
    OSVERSIONINFO ovi;

    GetSystemInfo(&si);
    if (si.dwPageSize == 0)
        return (int) GetLastError();
    ovi.dwOSVersionInfoSize = (DWORD) sizeof(OSVERSIONINFO);
    if (!GetVersionEx(&ovi))
        return (int) GetLastError();
    SignalStarted(0);
    return ovi.dwPlatformId == VER_PLATFORM_WIN32_CE ? 0 : 1;
}

/* M12 usage shape: virtual memory + time zone + process/DLL/thread
 * version & timing helpers (compile-only; never linked/run). */
static int m12_shaped_usage(void)
{
    LPVOID p;
    MEMORY_BASIC_INFORMATION mbi;
    TIME_ZONE_INFORMATION tzi;
    FILETIME ft1, ft2, ft3, ft4;
    DWORD oldp, tzid, cb;

    p = VirtualAlloc(NULL, 4096u, MEM_RESERVE | MEM_COMMIT,
                     PAGE_READWRITE);
    if (p == NULL)
        return (int) GetLastError();
    if (!VirtualProtect(p, 4096u, PAGE_READONLY, &oldp))
        return (int) GetLastError();
    cb = VirtualQuery(p, &mbi, sizeof(mbi));
    if (cb != sizeof(mbi) || mbi.State != MEM_COMMIT)
        return (int) ERROR_INVALID_PARAMETER;
    if (!VirtualFree(p, 0, MEM_RELEASE))
        return (int) GetLastError();
    if (GetProcessVersion(0) == 0)
        return (int) GetLastError();
    if (GetDllVersion((HMODULE) 0) == 0)
        return (int) GetLastError();
    if (!FlushInstructionCache(INVALID_HANDLE_VALUE, p, 0))
        return (int) GetLastError();
    if (!GetThreadTimes(INVALID_HANDLE_VALUE, &ft1, &ft2, &ft3, &ft4))
        return (int) GetLastError();
    tzid = GetTimeZoneInformation(&tzi);
    if (tzid == TIME_ZONE_ID_UNKNOWN && GetLastError() != 0)
        return (int) GetLastError();
    (void) SetTimeZoneInformation(&tzi);
    return 0;
}

/* M15 registry constants (winreg.h; values per fixed Win32 ABI). */
typedef char assert_reg_vals[
    (REG_NONE == 0 && REG_SZ == 1 && REG_EXPAND_SZ == 2 &&
     REG_BINARY == 3 && REG_DWORD == 4 &&
     REG_DWORD_LITTLE_ENDIAN == 4 && REG_DWORD_BIG_ENDIAN == 5 &&
     REG_LINK == 6 && REG_MULTI_SZ == 7 && REG_RESOURCE_LIST == 8 &&
     REG_OPTION_NON_VOLATILE == 0u && REG_OPTION_VOLATILE == 1u &&
     REG_CREATED_NEW_KEY == 1u && REG_OPENED_EXISTING_KEY == 2u &&
     REG_NOTIFY_CHANGE_NAME == 1u &&
     REG_NOTIFY_CHANGE_LAST_SET == 4u) ? 1 : -1];

/* M13 NLS constants (winnls.h; values per fixed Win32 ABI). */
typedef char assert_nls_vals[
    (CP_ACP == 0 && CP_OEMCP == 1 && CP_UTF7 == 65000 &&
     CP_UTF8 == 65001 &&
     MB_PRECOMPOSED == 1u && MB_ERR_INVALID_CHARS == 8u &&
     WC_SEPCHARS == 0x20u && WC_DEFAULTCHAR == 0x40u &&
     WC_COMPOSITECHECK == 0x200u) ? 1 : -1];

/* M13 usage shape (compile-only). */
static int m13_shaped_usage(void)
{
    WCHAR wbuf[16];
    char abuf[16];
    int n;

    n = MultiByteToWideChar(CP_UTF8, 0, "abc", 3, wbuf, 16);
    if (n <= 0)
        return (int) GetLastError();
    n = WideCharToMultiByte(CP_UTF8, WC_SEPCHARS, wbuf, n,
                            abuf, 16, NULL, NULL);
    if (n <= 0)
        return (int) GetLastError();
    if (!IsDBCSLeadByte((BYTE) 0))
        return (int) GetLastError();
    if (!IsDBCSLeadByteEx(CP_ACP, (BYTE) 0))
        return (int) GetLastError();
    return 0;
}

/* M14 usage shape (compile-only): fiber callbacks and handles. */
static VOID CALLBACK fiber_proc_shaper(PVOID lpParam)
{
    (void) lpParam;
}

static int m14_shaped_usage(void)
{
    LPVOID fiber, mainfiber;

    mainfiber = ConvertThreadToFiber(NULL);
    if (mainfiber == NULL)
        return (int) GetLastError();
    fiber = CreateFiber(0, fiber_proc_shaper, NULL);
    if (fiber == NULL)
        return (int) GetLastError();
    (void) GetCurrentFiber();
    (void) GetFiberData();
    SwitchToFiber(fiber);
    DeleteFiber(fiber);
    SwitchToFiber(mainfiber);
    DeleteFiber(mainfiber);
    return 0;
}

/* M15 usage shape (compile-only): registry round trip on a
 * volatile test key under HKEY_CURRENT_USER.  Never run/linked. */
static int m15_shaped_usage(void)
{
    static const WCHAR w_key[] = { 't', 0 };
    static const WCHAR w_val[] = { 'v', 0 };
    static const WCHAR w_sub[] = { 's', 0 };
    HKEY hk = NULL, hsub = NULL;
    LONG lr;
    DWORD disp, type = 0, cb = sizeof(DWORD), cch;
    DWORD dw = 7;

    if ((HKEY) (LONG_PTR) 0x80000001 != HKEY_CURRENT_USER)
        return (int) ERROR_INVALID_PARAMETER;
    if (HKEY_LOCAL_MACHINE == HKEY_CLASSES_ROOT)
        return (int) ERROR_INVALID_PARAMETER;
    lr = RegCreateKeyExW(HKEY_CURRENT_USER, w_key, 0, NULL,
                         REG_OPTION_VOLATILE, 0, NULL, &hk, &disp);
    if (lr != ERROR_SUCCESS)
        return (int) lr;
    lr = RegSetValueExW(hk, w_val, 0, REG_DWORD,
                        (const BYTE *) &dw, sizeof(dw));
    if (lr == ERROR_SUCCESS) {
        dw = 0;
        lr = RegQueryValueExW(hk, w_val, NULL, &type,
                              (LPBYTE) &dw, &cb);
    }
    if (lr == ERROR_SUCCESS && (type != REG_DWORD || dw != 7))
        lr = ERROR_INVALID_PARAMETER;
    if (lr == ERROR_SUCCESS)
        lr = RegCreateKeyExW(hk, w_sub, 0, NULL, REG_OPTION_VOLATILE,
                             0, NULL, &hsub, NULL);
    if (lr == ERROR_SUCCESS && hsub != NULL) {
        cch = 0;
        (void) RegEnumKeyExW(hk, 0, NULL, &cch, NULL, NULL, NULL,
                             NULL);
        (void) RegQueryInfoKeyW(hk, NULL, NULL, NULL, NULL, NULL,
                                NULL, NULL, NULL, NULL, NULL, NULL);
        RegDeleteKeyW(hk, w_sub);
    }
    if (lr == ERROR_SUCCESS)
        RegDeleteValueW(hk, w_val);
    RegFlushKeyW(hk);
    RegCloseKeyW(hk);
    return 0;
}

int host_tu_entry(void)
{
    (void) api_symbols;
    (void) api_flags;
    (void) LocalAlloc(LPTR, 16u);
    if (ce_shaped_usage() != 0)
        return 1;
    if (sync_shaped_usage() != 0)
        return 1;
    if (m10_shaped_usage() != 0)
        return 1;
    if (m11_shaped_usage() != 0)
        return 1;
    if (m12_shaped_usage() != 0)
        return 1;
    if (m13_shaped_usage() != 0)
        return 1;
    if (m14_shaped_usage() != 0)
        return 1;
    return m15_shaped_usage() == 0 ? 0 : 1;
}
