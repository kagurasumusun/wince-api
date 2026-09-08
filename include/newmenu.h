/*
 * newmenu.h -- New button menu notifications for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  The AYGShell Reference / AYGShell Messages + AYGShell Structures
 * books of the CE 5.0 Shell documentation are the source; every page
 * prints Header: newmenu.h and no Link Library row.
 *
 * The five NMN_* notification-message pages (NMN_GETAPPREGKEY,
 * NMN_GETPROPERTYBAG, NMN_INVOKECOMMAND, NMN_NEWBUTTONUPDATED,
 * NMN_NEWMENUDESTROY) publish the message shapes
 * (wParam = (WPARAM) 0, lParam = (PNMNEWMENU) pnmnm) but no numeric
 * values, and they are CE New-button notifications, not fixed Win32 ABI
 * identifiers -- so the names are recorded below and held as gaps in
 * docs/inventory.md rather than defined here (the M39-M41 held-set
 * policy).  The notifications arrive as WM_NOTIFY messages (winuser.h).
 */

#ifndef AKARI_NEWMENU_H
#define AKARI_NEWMENU_H

#include "windef.h"
#include "winuser.h"    /* NMHDR (hdr member), HMENU */
#include "objbase.h"    /* CLSID, IPropertyBag (pppropbag member) */

#ifdef __cplusplus
extern "C" {
#endif

/* ms931659 "NMNEWMENU" (Windows CE 3.0 and later; newmenu.h).  The
 * notification structure carried by the lParam of the NMN_* New button
 * messages (sent as WM_NOTIFY).  szReg receives the application's
 * New-button registry key on NMN_GETAPPREGKEY; clsid carries the CLSID
 * of the chosen menu item on NMN_INVOKECOMMAND; hMenu is a handle to
 * the New button menu; pppropbag receives the IPersistPropertyBag
 * pointer on NMN_GETPROPERTYBAG.  The page prints the member type
 * "IpropertyBag **" (lowercase p); the documented interface spelling
 * from the objbase.h pages is used below (transcription note). */
typedef struct tagNMNEWMENU {
    NMHDR        hdr;         /* hwndFrom / idFrom / code (winuser.h) */
    TCHAR        szReg[80];   /* application's New-menu registry key */
    HMENU        hMenu;       /* handle to the New button menu */
    CLSID        clsid;       /* CLSID of the chosen menu item */
    IPropertyBag **pppropbag; /* property bag for NMN_GETPROPERTYBAG */
} NMNEWMENU, *PNMNEWMENU;

/* NMN_* notification messages (newmenu.h; names held, no values
 * published on the CE 5.0 pages or the CE 6.0 twins ee503945 /
 * ee505265 / ee502621 / ee501920 / ee505277):
 *   NMN_GETAPPREGKEY      wParam = (WPARAM) 0; lParam = (PNMNEWMENU) pnmnm
 *   NMN_GETPROPERTYBAG    wParam = (WPARAM) 0; lParam = (PNMNEWMENU) pnmnm
 *   NMN_INVOKECOMMAND     wParam = (WPARAM) 0; lParam = (PNMNEWMENU) pnmnm
 *   NMN_NEWBUTTONUPDATED  wParam = (WPARAM) 0; lParam = (PNMNEWMENU) pnmnm
 *   NMN_NEWMENUDESTROY    wParam = (WPARAM) 0; lParam = (PNMNEWMENU) pnmnm
 */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_NEWMENU_H */
