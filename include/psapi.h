/*
 * psapi.h -- process/module status API for Windows CE (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (CE-era MSDN pages, learn.microsoft.com previous-versions archive,
 * (v=msdn.10) IDs).  The CE pages' Header row is Psapi.h; the Link
 * Library row of GetModuleInformation is Coredll.lib.
 */

#ifndef AKARI_PSAPI_H
#define AKARI_PSAPI_H

#include "windef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ms886757 "MODULEINFO (Windows CE 5.0)": module load address, size
 * and entry point, filled by GetModuleInformation.  CE .NET 4.1+;
 * Psapi.h.  The load address equals the HMODULE value (page note). */
typedef struct _MODULEINFO {
    LPVOID lpBaseOfDll;   /* module load address = HMODULE value */
    DWORD  SizeOfImage;   /* linear space the module occupies */
    LPVOID EntryPoint;    /* module entry point (near DllMain) */
} MODULEINFO, *LPMODULEINFO;

/* ms885631 "GetModuleInformation (Windows CE 5.0)":
 * BOOL GetModuleInformation(HANDLE, HMODULE, LPMODULEINFO, DWORD).
 * CE .NET 4.1+; Psapi.h; Coredll.lib.  Fills the MODULEINFO for a
 * module of the given process; cb = sizeof(MODULEINFO). */
AKARI_CE_IMPORT BOOL GetModuleInformation(HANDLE hProcess, HMODULE hModule,
                          LPMODULEINFO lpmodinfo, DWORD cb) AKARI_CE_NAME(GetModuleInformation);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_PSAPI_H */
