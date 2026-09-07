/*
 * e2e_module.c -- end-to-end link consumer: DLL module.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Linked by `make e2e` with /dll /entry:DllMainCRTStartup against the
 * doc-derived import libraries; the image must carry a DllMain entry
 * and an export table containing E2EDemo.  Exercises the DllMain
 * surface documented by the official DllMain page (ms885202: HANDLE
 * first parameter, process/thread reasons).
 */

#include <windows.h>

BOOL WINAPI DllMain(HANDLE hinstDLL, DWORD dwReason, LPVOID lpvReserved)
{
    (void)hinstDLL;
    (void)lpvReserved;
    return dwReason != DLL_PROCESS_DETACH;
}

DWORD E2EDemo(void)
{
    return GetTickCount() & 0x3F;
}
