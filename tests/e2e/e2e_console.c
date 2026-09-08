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
 * GetLastError, and the CE 5.0+ CopyFileExW export, M38).  It must
 * compile warning-free for every *-pc-wince target and link to a PE
 * whose import directory names only the real CE DLLs (coredll.dll
 * and friends).
 */

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ws2spi.h>
#include <tapi.h>
#include <tapicomn.h>
#include <objbase.h>

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
    /* M38: CopyFileExW (CE 5.0+, aa517311) -- linked, not run: the
     * image must export it per the doc-derived def. */
    (void) CopyFileExW(L"a", L"b", NULL, NULL, NULL,
                       COPY_FILE_FAIL_IF_EXISTS);
    /* M39: Winsock (Ws2.lib) import surface -- linked, not run: the
     * image must import the Ws2.lib-documented names from ws2.dll
     * per the doc-derived def. */
    (void) socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    (void) WSAStartup(WSAVersion(2, 2), (LPWSADATA)0);
    (void) getaddrinfo((const char *)0, (const char *)0,
                       (const struct addrinfo *)0, (struct addrinfo **)0);
    /* M41: Winsock name service (name spaces) -- linked, not run. */
    (void) WSAEnumNameSpaceProviders(NULL, NULL);
    (void) WSALookupServiceBegin(NULL, 0, NULL);
    (void) WSALookupServiceEnd(NULL);
    (void) WSALookupServiceNext(NULL, 0, NULL, NULL);
    (void) WSASetService(NULL, RNRSERVICE_REGISTER, 0);
    /* M42: Winsock SPI (Ws2spi.h) import surface -- linked, not run. */
    (void) WSPStartup(WSAVersion(2, 2), NULL, NULL, NULL, NULL);
    (void) WSPCleanup(NULL);
    (void) NSPSetService(NULL, NULL, NULL, RNRSERVICE_REGISTER, 0);
    (void) NSPLookupServiceNext(NULL, 0, NULL, NULL);
    /* M43: TAPI/TSPI (Tapicomn.h) import surface -- linked, not run. */
    (void) TSPI_lineOpen(0, NULL, NULL, 0, NULL);
    (void) TSPI_phoneGetDevCaps(0, 0, 0, NULL);
    /* M44: COM (Ole32.lib / Oleaut32.lib) import surface -- linked,
     * not run: the image must import the Ole32.lib/Oleaut32.lib-
     * documented names from ole32.dll/oleaut32.dll per the doc-derived
     * defs. */
    {
        GUID g;
        BSTR b;
        VARIANTARG va;
        (void) CoCreateGuid(&g);
        (void) CoInitialize(NULL);
        (void) CoCreateInstanceEx((REFCLSID)&g, (IUnknown *)0,
                                  CLSCTX_INPROC_SERVER, (COSERVERINFO *)0,
                                  0, (MULTI_QI *)0);
        (void) CLSIDFromString((LPOLESTR)0, (LPCLSID)0);
        (void) CreateFileMoniker((LPCOLESTR)0, (LPMONIKER *)0);
        (void) StgCreateDocfile((const WCHAR *)0, STGM_READ, 0, (IStorage **)0);
        b = SysAllocString((OLECHAR *)0);
        (void) SysFreeString(b);
        (void) VariantInit(&va);
        (void) VariantClear(&va);
        (void) SafeArrayDestroy((SAFEARRAY *)0);
        (void) LoadTypeLib((OLECHAR *)0, (ITypeLib **)0);
    }
    (void)tick;
    (void)si;
    (void)mod;
    if (!ok)
        SetLastError(ERROR_INTERNAL_ERROR);
    return ok ? 0 : 1;
}
