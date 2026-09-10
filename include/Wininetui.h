/*
 * Wininetui.h -- WinInet UI callback.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE page
 * ms918809 "IsMessageBoxHandled Callback Function" (Internet Client
 * Services book, M92 harvest; Requirements rows print Header
 * Wininetui.h, Link Library Wininetui.lib).  The callback is called
 * when WinInet has attempted a secure connection and trust was
 * revoked for a certificate in the server certificate chain.
 * See docs/inventory.md M92.
 */

#ifndef AKARI_WININETUI_H
#define AKARI_WININETUI_H

#include "Windef.h"    /* DWORD, HWND, UINT */

#ifdef __cplusplus
extern "C" {
#endif

/* ms918809 "IsMessageBoxHandled": print `DWORD IsMessageBoxHandled(
 * HWND hWnd, UINT uText, UINT uCaption, UINT uType)` (uText/uCaption
 * are resource IDs of the message/caption strings). */
AKARI_CE_IMPORT DWORD IsMessageBoxHandled(HWND hWnd, UINT uText,
                    UINT uCaption, UINT uType)
                    AKARI_CE_NAME(IsMessageBoxHandled);

/* ------------------------------------------------------------------
 * Book surface: internetclient-book (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms918807 IsDialogBoxHandled Callback Function (WinInet) (Header: Wininetui.h.) */
/* ms918809 IsMessageBoxHandled Callback Function (Header: Wininetui.h.) */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WININETUI_H */
