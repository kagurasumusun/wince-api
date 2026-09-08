/*
 * commdlg.h -- common dialog box messages for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  This header holds the Standard Shell Messages item whose CE
 * 5.0 page prints Header: Commdlg.h (the Font dialog box retrieval
 * message); the Common Dialog Boxes book of the Common Controls
 * Reference is a future milestone.
 */

#ifndef AKARI_COMMDLG_H
#define AKARI_COMMDLG_H

#include "windef.h"
#include "winuser.h"  /* WM_USER */

#ifdef __cplusplus
extern "C" {
#endif

/* ms914112 "WM_CHOOSEFONT_GETLOGFONT" (Windows CE .NET 4.0 and later;
 * Commdlg.h).  Sent to the open Font dialog box (SendMessage) to
 * retrieve the current font selections into the lParam LOGFONT
 * structure while the dialog is open; wParam is unused and must be
 * zero.  The CE page publishes the name without a value; the desktop
 * Win32 reference page prints the formula
 * "#define WM_CHOOSEFONT_GETLOGFONT (WM_USER + 1)", and WM_USER
 * (0x0400) is CE-published (winuser.h), so the derived value below
 * follows the M52 derived-value policy (path recorded in
 * docs/inventory.md M53).  Note the published formula lands on the
 * same 0x0401 value as DM_SETDEFID (aa452963, winuser.h) -- both
 * desktop pages print (WM_USER + 1); the shared value is the
 * documented ABI, kept verbatim. */
#define WM_CHOOSEFONT_GETLOGFONT  (WM_USER + 1)

#ifdef __cplusplus
}
#endif

#endif /* AKARI_COMMDLG_H */
