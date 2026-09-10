/*
 * Pkfuncs.h -- Windows CE public kernel functions.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE page
 * ms939622 "CaptureDumpFileOnDevice" (Error Report Generator
 * Functions, CE-era MSDN archive): Requirements row prints
 * "Header: Pkfuncs.h / Link Library: Coredll.lib / OS Versions:
 * Windows Embedded CE 6.0".  (The ZeroPtr macro named by the
 * CeZeroPointer page ms885158 is OEM-side and stays recorded in
 * Winbase.h -- see docs/inventory.md.)
 *
 * See docs/inventory.md M82.
 */

#ifndef AKARI_PKFUNCS_H
#define AKARI_PKFUNCS_H

#include "Windef.h"    /* BOOL, DWORD, LPCWSTR */

/* ms939622 "CaptureDumpFileOnDevice": print
 * `BOOL CaptureDumpFileOnDevice(DWORDdwProcessId,DWORDdwThreadId,
 * LPCWSTRpwzExtraFilesPath);` (glued tokens split).  Generates an
 * error-report dump file for the given process and thread. */
AKARI_CE_IMPORT BOOL CaptureDumpFileOnDevice(DWORD dwProcessId,
                    DWORD dwThreadId, LPCWSTR pwzExtraFilesPath)
                    AKARI_CE_NAME(CaptureDumpFileOnDevice);

#endif /* AKARI_PKFUNCS_H */
