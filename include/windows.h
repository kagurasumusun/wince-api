/*
 * windows.h -- umbrella header for the Akari API (Windows CE 4/5/6).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch; spec basis is the official Microsoft Windows
 * CE documentation (see windef.h / winbase.h for per-declaration
 * page IDs).  On Windows CE every API is Unicode-only; no UNICODE
 * switch exists -- the wide names are the API.
 */

#ifndef AKARI_WINDOWS_H
#define AKARI_WINDOWS_H

#include "windef.h"
#include "winbase.h"
#include "winerror.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ms885217 "ExitProcess (Windows CE 5.0)" lists Header: Windows.h,
 * which is why this declaration lives here (see winbase.h for the
 * export-surface conflict note). */
VOID ExitProcess(UINT uExitCode);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WINDOWS_H */
