/*
 * cpl.h -- Control Panel application layer for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  This header holds the Standard Shell Reference items whose CE
 * 5.0 pages print Header: Cpl.h.
 *
 * The CE 5.0 pages publish the six CPL_* message names and the
 * CPL_DYNAMIC_RES selector name without values, and no other official
 * doc (WM 6.5 documentation, desktop reference) publishes values for
 * them either -- so all of them are recorded here and held as gaps in
 * docs/inventory.md M53 rather than defined.
 */

#ifndef AKARI_CPL_H
#define AKARI_CPL_H

#include "windef.h"
#include "windows.h"   /* HWND, HICON, TCHAR carriers */

#ifdef __cplusplus
extern "C" {
#endif

/* ms908154 "CPlApplet" (Windows CE 1.0 and later; Cpl.h; Link Library:
 * Developer implemented).  The Control Panel application entry point
 * exported by every .cpl module: the Control Panel loads each DLL with
 * a .cpl extension from the Windows folder and calls this function
 * with the CPL_* messages below.  A single CPlApplet serves all of the
 * dialog boxes implemented in one .cpl file.  The return value depends
 * on the message.  (The page's Windows Mobile remarks name the
 * APPLET_PROC pointer type; no CE page publishes that typedef, so only
 * the prototype is carried here.) */
LONG CPlApplet(HWND hwndCPl, UINT msg, LPARAM lParam1, LPARAM lParam2);

/* ms908158 "CPLINFO" (Windows CE 1.0 and later; Cpl.h).  Resource
 * identifiers for a Control Panel dialog box, returned in response to
 * the CPL_INQUIRE-class messages.  idIcon / idName / idInfo may carry
 * the CPL_DYNAMIC_RES selector (value held) to request CPL_NEWINQUIRE
 * for each use instead. */
typedef struct tagCPLINFO {
    int  idIcon;   /* icon resource identifier */
    int  idName;   /* short-name string resource identifier */
    int  idInfo;   /* description string resource identifier */
    LONG lData;    /* application-defined data (returned with the message) */
} CPLINFO;

/* ms931468 "NEWCPLINFO" (Windows CE 1.0 and later; Cpl.h).  The
 * CPL_NEWINQUIRE response structure.  CE specifics: dwFlags,
 * dwHelpContext and szHelpFile are "Ignored"; the Handheld PC shell
 * does not use them.  dwSize must be sizeof(NEWCPLINFO).  For lData
 * the page documents returning the icon resource ID (the resource-ID
 * counterpart of hIcon). */
typedef struct tagNEWCPLINFO {
    DWORD dwSize;               /* sizeof(NEWCPLINFO) */
    DWORD dwFlags;              /* ignored */
    DWORD dwHelpContext;        /* ignored */
    LONG  lData;                /* application data / icon resource id */
    HICON hIcon;                /* dialog box icon */
    TCHAR szName[32];           /* dialog box name */
    TCHAR szInfo[64];           /* dialog box description */
    TCHAR szHelpFile[128];      /* ignored */
} NEWCPLINFO;

/* CPL_* messages (ms908155..ms908161; Cpl.h; names held, values not
 * published on the CE 5.0, WM 6.5 or desktop pages):
 *   CPL_INIT        wParam/lParam unused; nonzero = initialization ok
 *                   (a zero return ends communication and unloads the DLL)
 *   CPL_GETCOUNT    return: number of dialog boxes in the .cpl file
 *   CPL_DBLCLK      lParam1 = uAppNum, lParam2 = lData; display the box
 *   CPL_NEWINQUIRE  lParam1 = uAppNum, lParam2 = (LPNEWCPLINFO) lpncpli
 *   CPL_STOP        lParam1 = uAppNum, lParam2 = lData; per-box cleanup
 *   CPL_EXIT        final release before the DLL is freed
 * CPL_DYNAMIC_RES (ms908158 remarks): CPLINFO member selector that
 * requests CPL_NEWINQUIRE each time; value held.
 */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_CPL_H */
