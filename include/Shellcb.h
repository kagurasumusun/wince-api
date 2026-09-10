/*
 * Shellcb.h -- Windows CE shell callback registration (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE 2.12+
 * documentation (learn.microsoft.com previous-versions archive; page
 * ids cited per declaration).  Sources: the two Shellcb.h pages of
 * the Shell book harvest (M94, tools/manifests/shell-book.manifest).
 * Neither page prints a Link Library row, so there is no doc-derived
 * def entry; ShellRegisterCallbacks is an OS-facing registration
 * function the shell calls (the SHELLCALLBACKS page: "You must
 * register these callback functions by passing the SHELLCALLBACKS
 * structure to the ShellRegisterCallbacks function").
 *
 * Print artifacts recorded: the SHELLCALLBACKS typedef and both
 * callback typedefs print with glued name/type tokens
 * (PFNSHELL_NOTIFYICONpfnShell_NotifyIcon et al.; DWORDdwSize) --
 * split with repairs, noted here.  The OS "always forwards
 * Shell_NotifyIcon to a custom shell" (page remark) -- the callbacks
 * are how a replacement shell receives those two APIs.
 */

#ifndef AKARI_SHELLCB_H
#define AKARI_SHELLCB_H

#include "Windef.h"     /* DWORD, UINT, BOOL, WINAPI, LPCVOID, HWND */
#include "Shellapi.h"   /* PNOTIFYICONDATA (Shell_NotifyIcon data) */

#ifdef __cplusplus
extern "C" {
#endif

/* aa453683 (member print): `typedef BOOL (WINAPI* PFNSHELL_NOTIFYICON)
 * (DWORD dwMessage, PNOTIFYICONDATA lpData);` */
typedef BOOL (WINAPI *PFNSHELL_NOTIFYICON)(DWORD dwMessage,
                                           PNOTIFYICONDATA lpData);

/* aa453683 (member print): `typedef void (WINAPI* PFNSHHADDTORECENTDOCS)
 * (UINT uFlags, LPCVOID pv);` */
typedef void (WINAPI *PFNSHHADDTORECENTDOCS)(UINT uFlags, LPCVOID pv);

/* aa453683 "SHELLCALLBACKS": `typedef struct {DWORD dwSize;
 * PFNSHELL_NOTIFYICON pfnShell_NotifyIcon; PFNSHHADDTORECENTDOCS
 * pfnSHAddToRecentDocs;} SHELLCALLBACKS;` -- dwSize must be filled
 * in by the caller. */
typedef struct {
    DWORD                   dwSize;
    PFNSHELL_NOTIFYICON     pfnShell_NotifyIcon;
    PFNSHHADDTORECENTDOCS   pfnSHAddToRecentDocs;
} SHELLCALLBACKS;

/* aa453687 "ShellRegisterCallbacks": `BOOL ShellRegisterCallbacks(
 * SHELLCALLBACKS* pShellCallbacks);` */
AKARI_CE_IMPORT BOOL ShellRegisterCallbacks(SHELLCALLBACKS *pShellCallbacks)
                    AKARI_CE_NAME(ShellRegisterCallbacks);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_SHELLCB_H */
