/*
 * shellapi.h -- Shell API declarations for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  This header currently holds the Resources Reference items whose
 * CE 5.0 pages print Header: Shellapi.h.
 */

#ifndef AKARI_SHELLAPI_H
#define AKARI_SHELLAPI_H

#include "windef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* aa453065 "ExtractIconEx": extracts icon handles from an executable,
 * DLL, or icon file.  CE 1.0+; Header: Shellapi.h.  Windows CE is
 * Unicode-only, so the wide form is the API (generic macro below). */
HICON ExtractIconExW(LPCTSTR lpszFile, int nIconIndex,
                     HICON* phiconLarge, HICON* phiconSmall, UINT nIcons);
#define ExtractIconEx ExtractIconExW

#ifdef __cplusplus
}
#endif

#endif /* AKARI_SHELLAPI_H */
