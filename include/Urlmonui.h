/*
 * Urlmonui.h -- Urlmon UI callback.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE page
 * ms918806 "IsDialogBoxHandled Callback Function (Urlmon)" (Internet
 * Client Services book, M92 harvest; Requirements rows print Header
 * Urlmonui.h, Link Library Urlmonui.lib).  The callback is called by
 * Urlmon before it opens a Zones Alert/Prompt dialog box.
 * See docs/inventory.md M92.
 */

#ifndef AKARI_URLMONUI_H
#define AKARI_URLMONUI_H

#include "Windef.h"    /* DWORD, HWND, LPCTSTR */

#ifdef __cplusplus
extern "C" {
#endif

/* ms918806 "IsDialogBoxHandled (Urlmon)": print `DWORD
 * IsDialogBoxHandled( HWND hWnd, DWORD dwAction, DWORD dwPermissions,
 * LPCTSTR lpszText)`. */
AKARI_CE_IMPORT DWORD IsDialogBoxHandled(HWND hWnd, DWORD dwAction,
                    DWORD dwPermissions, LPCTSTR lpszText)
                    AKARI_CE_NAME(IsDialogBoxHandled);

/* ------------------------------------------------------------------
 * Book surface: internetclient-book (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms918806 IsDialogBoxHandled Callback Function (Urlmon) (Header: Urlmonui.h.) */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_URLMONUI_H */
