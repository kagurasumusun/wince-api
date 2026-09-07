/*
 * e2e_console.c -- end-to-end link consumer: main() program.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Linked by `make e2e` with the Akari CRT (wince-crt) startup objects
 * and the doc-derived import libraries (the def directory, doc def
 * files, via llvm-dlltool -m armce) into a Windows CE PE executable; it
 * exercises the coredll import surface the headers declare
 * (GetTickCount, GetSystemInfo, the local heap, GetModuleHandleW,
 * GetLastError).  It must compile warning-free for every
 * *-pc-wince target and link to a PE whose import directory names
 * only the real CE DLLs (coredll.dll and friends).
 */

#include <windows.h>

int main(void)
{
    SYSTEM_INFO si;
    LPVOID p;
    DWORD tick;
    HMODULE mod;
    BOOL ok;

    tick = GetTickCount();
    GetSystemInfo(&si);
    p = LocalAlloc(LPTR, 64);
    ok = (p != NULL);
    if (p != NULL)
        LocalFree(p);
    mod = GetModuleHandleW(L"coredll.dll");
    if (mod == NULL)
        ok = FALSE;
    (void)tick;
    (void)si;
    (void)mod;
    if (!ok)
        SetLastError(ERROR_INTERNAL_ERROR);
    return ok ? 0 : 1;
}
