/* TU smoke test for the Akari API headers (host, compile-only).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Compiled with -c for each CE generation value of _WIN32_WCE
 * (0x420, 0x500, 0x600).  Exercises every M1 declaration and the
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

/* Reference every M1 declaration (no calls, compile-only). */
static const void *const m1_symbols[] = {
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
};

static const unsigned m1_flags[] = {
    LMEM_FIXED, LMEM_ZEROINIT, LPTR,
};

/* Generic-text forms are the wide ones on CE. */
typedef char assert_tchar_wide[(sizeof(TCHAR) == sizeof(WCHAR)) ? 1 : -1];
typedef char assert_lpctstr_wide[(sizeof(LPCTSTR) == sizeof(LPCWSTR)) ? 1 : -1];

/* Handle/model sanity for the classic WinMain-shaped program. */
static int uses_handles(HMODULE h, HLOCAL l, HINSTANCE i)
{
    return h != 0 || l != 0 || i != 0;
}

int host_tu_entry(void)
{
    (void) m1_symbols;
    (void) m1_flags;
    (void) uses_handles;
    (void) LocalAlloc(LPTR, 16u);
    return 0;
}
