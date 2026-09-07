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
    (const void *) &GetLocalTime,
    (const void *) &GetSystemTime,
    (const void *) &SetLocalTime,
    (const void *) &SetSystemTime,
    (const void *) &FileTimeToLocalFileTime,
    (const void *) &LocalFileTimeToFileTime,
    (const void *) &FileTimeToSystemTime,
    (const void *) &SystemTimeToFileTime,
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

static const unsigned api_flags[] = {
    LMEM_FIXED, LMEM_ZEROINIT, LPTR,
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

int host_tu_entry(void)
{
    (void) api_symbols;
    (void) api_flags;
    (void) LocalAlloc(LPTR, 16u);
    return ce_shaped_usage() == 0 ? 0 : 1;
}
