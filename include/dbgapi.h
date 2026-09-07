/*
 * dbgapi.h -- debug-support API for Windows CE (driver/debug builds).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (CE-era MSDN pages, learn.microsoft.com previous-versions archive,
 * (v=msdn.10) IDs).  The Debugging Reference pages state Header:
 * Dbgapi.h for these items; OS Versions is "Windows CE OS 2.10 and
 * later" for NKDbgPrintfW / RegisterDbgZones / DBGPARAM and
 * "Windows CE 2.12 and later" for WriteDebugLED.  NKDbgPrintfW and
 * RegisterDbgZones print "Link Library: none" on their pages (kernel/
 * driver support routines, not user-mode import-library exports);
 * WriteDebugLED prints Link Library: Coredll.lib.  The debug *macros*
 * of the Debugging Reference (ASSERT, DEBUGMSG, RETAILMSG, ERRORMSG,
 * ...) are documented to expand to these support routines; their
 * expansions are driver/zone machinery that the pages do not specify
 * in implementable form, so only the support functions are declared
 * here (see docs/inventory.md for the recorded macro names).
 */

#ifndef AKARI_DBGAPI_H
#define AKARI_DBGAPI_H

#include "windef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* aa451060 "DBGPARAM (Windows CE 5.0)": debug-zone registration
 * parameters.  CE OS 2.10+; Dbgapi.h.  The RegisterDbgZones page
 * documents the global variable "dpCurSettings" as a DBGPARAM. */
typedef struct _DBGPARAM {
    WCHAR lpszName[32];        /* zone name */
    WCHAR rglpszZones[16][32]; /* zone names */
    ULONG ulZoneMask;          /* zone enable mask */
} DBGPARAM, *LPDBGPARAM;

/* aa451081 "NKDbgPrintfW (Windows CE 5.0)":
 * void WINAPIV NKDbgPrintfW(LPCWSTR lpszFmt, ...).  CE OS 2.10+;
 * Dbgapi.h; Link Library: none.  Prints to the debug output stream;
 * the DEBUGMSG/RETAILMSG/ERRORMSG macros call it. */
void WINAPIV NKDbgPrintfW(LPCWSTR lpszFmt, ...);

/* aa451083 "RegisterDbgZones (Windows CE 5.0)":
 * BOOL RegisterDbgZones(HMODULE hMod, LPDBGPARAM lpdbgparam).
 * CE OS 2.10+; Dbgapi.h; Link Library: none.  Registers the debug
 * zones of a process or DLL; NULL hMod registers process zones. */
BOOL RegisterDbgZones(HMODULE hMod, LPDBGPARAM lpdbgparam);

/* aa450990 "WriteDebugLED (Windows CE 5.0)":
 * void WriteDebugLED(WORD wIndex, DWORD dwPattern).  CE 2.12+;
 * Dbgapi.h; Coredll.lib.  Sends a debug event to an OEM-supplied LED;
 * wIndex 0..MAX_OEM_LEDINDEX (the OS reserves its own index range). */
AKARI_CE_IMPORT void WriteDebugLED(WORD wIndex, DWORD dwPattern) AKARI_CE_NAME(WriteDebugLED);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_DBGAPI_H */
