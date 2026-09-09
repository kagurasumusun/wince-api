/*
 * Shelwapi.h -- light-weight shell helper layer for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  This header holds the Standard Shell Reference items whose CE
 * 5.0 pages print Header: Shelwapi.h.
 */

#ifndef AKARI_SHELWAPI_H
#define AKARI_SHELWAPI_H

#include "Windef.h"   /* UINT, LPTSTR carriers */
#include "Shtypes.h"   /* STRRET (pstr parameter) */
#include "Shlobj.h"    /* LPCITEMIDLIST (pidl parameter) */

#ifdef __cplusplus
extern "C" {
#endif

/* ms940378 "StrRetToBuf" (Windows CE .NET 4.2 and later; Shelwapi.h;
 * Ceshell.lib).  Converts a STRRET returned by
 * IShellFolder::GetDisplayNameOf (shobjidl.h) into a string buffer;
 * when the STRRET is STRRET_WSTR the pOleStr memory is freed on
 * return.  pszBuf receives a null-terminated string truncated to
 * cchBuf characters.  Returns S_OK or an error code. */
AKARI_CE_IMPORT HRESULT StrRetToBuf(LPSTRRET pstr, LPCITEMIDLIST pidl,
                                    LPTSTR pszBuf,
                                    UINT cchBuf) AKARI_CE_NAME(StrRetToBuf);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_SHELWAPI_H */
