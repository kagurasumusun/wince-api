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
    (const void *) &TlsAlloc,
    (const void *) &TlsFree,
    (const void *) &TlsSetValue,
    (const void *) &TlsGetValue,
    (const void *) &LoadLibraryEx,
    (const void *) &LoadLibraryExW,
};

/* TLS constants exercised (winbase.h). */
typedef char assert_tls_vals[
    (TLS_MINIMUM_AVAILABLE == 64 &&
     TLS_OUT_OF_INDEXES == (DWORD)0xFFFFFFFFu) ? 1 : -1];

/* LoadLibraryEx flags (winbase.h, values per official Win32 ABI). */
typedef char assert_loadlib_flags[
    (DONT_RESOLVE_DLL_REFERENCES == 1u &&
     LOAD_LIBRARY_AS_DATAFILE == 2u &&
     LOAD_WITH_ALTERED_SEARCH_PATH == 8u) ? 1 : -1];

/* Error constants exercised (values from winerror.h). */
typedef char assert_winerror_vals[
    (ERROR_SUCCESS == 0 && ERROR_INVALID_PARAMETER == 87 &&
     ERROR_ALREADY_EXISTS == 183 && STILL_ACTIVE == 259 &&
     ERROR_INSUFFICIENT_BUFFER == 122) ? 1 : -1];

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

static int ce_shaped_usage(void)
{
    PROCESS_INFORMATION pi;
    HANDLE h;
    DWORD tid;

    if (!CreateProcessW(w_app, w_cmd, NULL, NULL,
                        FALSE, 0, NULL, NULL, NULL, &pi))
        return (int) GetLastError();
    h = CreateThread(NULL, 0, worker, NULL, 0, &tid);
    if (h == NULL)
        return (int) GetLastError();
    return (int) (pi.dwProcessId + tid);
}

int host_tu_entry(void)
{
    (void) api_symbols;
    (void) api_flags;
    (void) LocalAlloc(LPTR, 16u);
    return ce_shaped_usage() == 0 ? 0 : 1;
}
