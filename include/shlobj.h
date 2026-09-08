/*
 * shlobj.h -- shell object / file-change notification layer for
 * Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  The AYGShell Reference book of the CE 5.0 Shell documentation is
 * the source book.
 *
 * Header homes, per the official Requirements rows:
 *   - WM_FILECHANGEINFO (aa453860): Header shlobj.h, Library ceshell.lib,
 *     Windows CE 3.0 and later.  The page prints the message shape
 *     (wParam reserved 0, lParam = FILECHANGENOTIFY*) but no numeric
 *     value, so the message identifier is held as a gap in
 *     docs/inventory.md rather than defined here.
 *   - FILECHANGENOTIFY (aa453066): the CE 5.0 main Requirements row
 *     prints the multi-header list "Commctrl.h, Prsht.h, Shlguid.h."
 *     (recorded verbatim; the Prsht.h/Shlguid.h homes belong to the
 *     unharvested Property Sheets / GUID books and the row carries no
 *     Link Library), while the page's Windows Mobile Requirements row
 *     and the WM_FILECHANGEINFO carrier message both name shlobj.h +
 *     ceshell.lib.  The structure is therefore co-located with its
 *     carrier message here (documented design decision); the CE 6.0
 *     twin ee500811 repeats the same multi-header list.
 *
 * Windows CE is Unicode-only; the notification strings referenced by the
 * event semantics are wide strings on CE.
 */

#ifndef AKARI_SHLOBJ_H
#define AKARI_SHLOBJ_H

#include "windef.h"
#include "extfile.h"    /* FILECHANGEINFO (fci member) */

#ifdef __cplusplus
extern "C" {
#endif

/* aa453066 "FILECHANGENOTIFY" (Windows CE .NET 4.2 and later).  The
 * structure pointed to by the lParam of the WM_FILECHANGEINFO message
 * the shell sends (SendNotifyMessage) to a window registered with
 * SHChangeNotifyRegister.  dwRefCount is internal ("should not be used
 * by applications"); fci details the file system change.  The window's
 * message processor must pass the pointer to SHChangeNotifyFree
 * (aygshell.h) -- failure leaks shell memory. */
typedef struct tagFILECHANGENOTIFY {
    DWORD          dwRefCount;   /* internal; not for application use */
    FILECHANGEINFO fci;
} FILECHANGENOTIFY;

/* aa453860 "WM_FILECHANGEINFO" (Windows CE 3.0 and later; shlobj.h,
 * ceshell.lib).  Sent by SendNotifyMessage from the shell to the window
 * registered with SHChangeNotifyRegister:
 *
 *     wParam : reserved for future use; must be 0
 *     lParam : pointer to a FILECHANGENOTIFY structure
 *
 * The page publishes no numeric message value (and WM_FILECHANGEINFO is
 * a CE shell message, not a fixed Win32 ABI identifier), so the name is
 * recorded here and held in docs/inventory.md. */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_SHLOBJ_H */
