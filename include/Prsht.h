/*
 * Prsht.h -- Property Sheets API for Windows CE (Prsht.h layer).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  Source book: CE 5.0 "Shell and User Interface :: Shell :: Common
 * Controls Reference :: Property Sheets Reference" (the 57 leaves of
 * tools/manifests/cc-propertysheets.manifest, fetched M54/M55).
 *
 * Requirement rows: the function and structure pages print "Header:
 * Prsht.h" with NO Link Library row (the functions carry no documented
 * import library on CE), so no def is generated and the declarations
 * carry no import pin -- the Shell_NotifyIcon / CreateToolbarEx
 * precedent.  OS Versions: "Windows CE 1.0 and later" unless noted.
 *
 * The PropSheet_* macro pages print signatures but no macro bodies, and
 * the PSM_ messages, PSN_ notifications, PSP_ / PSH_ / PSPCB_ /
 * PSCB_ / PSBTN_ / PSWIZB_ and ID_PS value families are names-only:
 * all held (see the ledger at the end and docs/inventory.md M55).
 */

#ifndef AKARI_PRSHT_H
#define AKARI_PRSHT_H

#include "Windef.h"
#include "Winuser.h"  /* NMHDR, DLGPROC, LPCDLGTEMPLATE */

#ifdef __cplusplus
extern "C" {
#endif

/* Opaque property-sheet page handle: typed by every page but never
 * laid out (the HIMAGELIST model, M29). */
typedef void *HPROPSHEETPAGE;

/* Forward tag: the LPFNPSPCALLBACK parameter below is spelled via the
 * struct tag because the callback and the structure are mutually
 * recursive (the page typedef pair follows the full definition). */
struct _PROPSHEETPAGE;

/* aa453563 "PropSheetPageProc": "UINT CALLBACK PropSheetPageProc(HWND
 * hwnd, UINT uMsg, LPPROPSHEETPAGE ppsp );" -- the LPFNPSPCALLBACK
 * pointer type is named by the PROPSHEETPAGE member (aa453562);
 * built from the documented signature (M51 IMENUMPROC model; the
 * parameter is spelled via the struct tag because the typedef pair
 * is mutually recursive). */
typedef UINT (CALLBACK *LPFNPSPCALLBACK)(HWND hwnd, UINT uMsg,
                                         struct _PROPSHEETPAGE *ppsp);

/* aa453565 "PropSheetProc": "int CALLBACK PropSheetProc(HWND hwndDlg,
 * UINT uMsg, LPARAM lParam );" -- the PFNPROPSHEETCALLBACK pointer
 * type is named by the PROPSHEETHEADER member (aa453560); built from
 * the documented signature. */
typedef int (CALLBACK *PFNPROPSHEETCALLBACK)(HWND hwndDlg, UINT uMsg,
                                             LPARAM lParam);

/* aa452848 "AddPropSheetPageProc": "BOOL CALLBACK
 * AddPropSheetPageProc(HPROPSHEETPAGE hpage, LPARAM lParam );" -- the
 * LPFNADDPROPSHEETPAGE pointer type is named by the
 * ExtensionPropSheetPageProc parameter (aa453062); built from the
 * documented signature.  (This closes the M53 dangling-type note in
 * shobjidl.h.) */
typedef BOOL (CALLBACK *LPFNADDPROPSHEETPAGE)(HPROPSHEETPAGE hpage,
                                              LPARAM lParam);

/* aa453562 "PROPSHEETPAGE" (CE 1.0+): "typedef struct _PROPSHEETPAGE
 * { DWORD dwSize; DWORD dwFlags; HINSTANCE hInstance; union {LPCSTR
 * pszTemplate; LPCDLGTEMPLATE pResource; }; union {HICON hIcon;
 * LPCSTR pszIcon; }; LPCSTR pszTitle; DLGPROC pfnDlgProc; LPARAM
 * lParam; LPFNPSPCALLBACK pfnCallback; UINT FAR* pcRefParent;
 * } PROPSHEETPAGE, FAR* LPPROPSHEETPAGE; typedef const
 * PROPSHEETPAGE FAR* LPCPROPSHEETPAGE;".  32-bit size 40,
 * TU-asserted. */
typedef struct _PROPSHEETPAGE {
    DWORD     dwSize;
    DWORD     dwFlags;
    HINSTANCE hInstance;
    union {
        LPCSTR          pszTemplate;
        LPCDLGTEMPLATE  pResource;
    };
    union {
        HICON   hIcon;
        LPCSTR  pszIcon;
    };
    LPCSTR         pszTitle;
    DLGPROC        pfnDlgProc;
    LPARAM         lParam;
    LPFNPSPCALLBACK pfnCallback;
    UINT  FAR     *pcRefParent;
} PROPSHEETPAGE, FAR *LPPROPSHEETPAGE;
typedef const PROPSHEETPAGE FAR *LPCPROPSHEETPAGE;

/* aa453560 "PROPSHEETHEADER" (CE 1.0+): "typedef struct
 * _PROPSHEETHEADER { DWORD dwSize; DWORD dwFlags; HWND hwndParent;
 * HINSTANCE hInstance; union {HICON hIcon; LPCWSTR pszIcon; };
 * LPCWSTR pszCaption; UINT nPages; union {UINT nStartPage; LPCWSTR
 * pStartPage; }; union {LPCPROPSHEETPAGE ppsp; HPROPSHEETPAGE FAR*
 * phpage; }; PFNPROPSHEETCALLBACK pfnCallback; } PROPSHEETHEADER,
 * FAR* LPPROPSHEETHEADER; typedef const PROPSHEETHEADER FAR*
 * LPCPROPSHEETHEADER;".  32-bit size 40, TU-asserted. */
typedef struct _PROPSHEETHEADER {
    DWORD     dwSize;
    DWORD     dwFlags;
    HWND      hwndParent;
    HINSTANCE hInstance;
    union {
        HICON   hIcon;
        LPCWSTR pszIcon;
    };
    LPCWSTR   pszCaption;
    UINT      nPages;
    union {
        UINT    nStartPage;
        LPCWSTR pStartPage;
    };
    union {
        LPCPROPSHEETPAGE   ppsp;
        HPROPSHEETPAGE FAR *phpage;
    };
    PFNPROPSHEETCALLBACK pfnCallback;
} PROPSHEETHEADER, FAR *LPPROPSHEETHEADER;
typedef const PROPSHEETHEADER FAR *LPCPROPSHEETHEADER;

/* aa453576 "PSHNOTIFY" (CE 1.0+): "typedef struct _PSHNOTIFY { NMHDR
 * hdr; LPARAM lParam; } PSHNOTIFY, FAR* LPPSHNOTIFY;".
 * 32-bit size 16, TU-asserted. */
typedef struct _PSHNOTIFY {
    NMHDR    hdr;
    LPARAM   lParam;
} PSHNOTIFY, FAR *LPPSHNOTIFY;

/* ------------------------------------------------------------------ */
/* Functions (no Link Library rows on the CE pages: declared without  */
/* import pins, like Shell_NotifyIcon).                                */
/* ------------------------------------------------------------------ */

/* ms908183 "CreatePropertySheetPage" (CE 1.0+):
 * "HPROPSHEETPAGE CreatePropertySheetPage(LPCPROPSHEETPAGE lppsp );". */
HPROPSHEETPAGE CreatePropertySheetPage(LPCPROPSHEETPAGE lppsp); /* ms908183 */

/* aa452941 "DestroyPropertySheetPage" (CE 1.0+):
 * "BOOL DestroyPropertySheetPage(HPROPSHEETPAGE hPSPage );". */
BOOL     DestroyPropertySheetPage(HPROPSHEETPAGE hPSPage);    /* aa452941 */

/* aa453552 "PropertySheet" (CE 1.0+): "int PropertySheet(
 * LPCPROPSHEETHEADER lppsph );" -- the return value is ID_PSREBOOTSYSTEM
 * or ID_PSRESTARTWINDOWS when a page asked for a restart (names
 * published, values held). */
int      PropertySheet(LPCPROPSHEETHEADER lppsph);            /* aa453552 */

/* aa453062 "ExtensionPropSheetPageProc" (CE 1.0+; Developer
 * implemented): "BOOL CALLBACK ExtensionPropSheetPageProc(LPVOID lpv,
 * LPFNADDPROPSHEETPAGE lpfnAddPropSheetPageProc, LPARAM lParam );". */
BOOL     CALLBACK ExtensionPropSheetPageProc(LPVOID lpv,
                                             LPFNADDPROPSHEETPAGE
                                             lpfnAddPropSheetPageProc,
                                             LPARAM lParam);    /* aa453062 */

/* aa453563 "PropSheetPageProc" (CE 1.0+; Developer implemented):
 * callback prototype, see the LPFNPSPCALLBACK note above. */
UINT     CALLBACK PropSheetPageProc(HWND hwnd, UINT uMsg,
                                    LPPROPSHEETPAGE ppsp);    /* aa453563 */

/* aa453565 "PropSheetProc" (CE 1.0+; Developer implemented):
 * callback prototype, see the PFNPROPSHEETCALLBACK note above. */
int      CALLBACK PropSheetProc(HWND hwndDlg, UINT uMsg,
                                LPARAM lParam);               /* aa453565 */

/* aa452848 "AddPropSheetPageProc" (CE 1.0+; Developer implemented):
 * callback prototype, see the LPFNADDPROPSHEETPAGE note above. */
BOOL     CALLBACK AddPropSheetPageProc(HPROPSHEETPAGE hpage,
                                       LPARAM lParam);        /* aa452848 */

/* ------------------------------------------------------------------ */
/* HELD ledger (names without numeric values and macro bodies without
 * printed definitions; page-id accounting in docs/inventory.md M55):
 * the 18 PropSheet_* macro signatures (aa453553-aa453575, recorded in
 * docs/inventory.md M55), the PSM_* messages (aa453577.., 18), the
 * PSN_* notifications, PSPCB_CREATE/PSPCB_RELEASE (aa453563),
 * PSCB_GETTITLE/PSCB_GETVERSION/PSCB_INITIALIZED/PSCB_PRECREATE
 * (aa453565), PSBTN_* (aa453564), PSWIZB_* (aa453574),
 * ID_PSREBOOTSYSTEM/ID_PSRESTARTWINDOWS (aa453552), the PSP_* page
 * flags and PSH_* header flags (aa453562/aa453560 tables).
 * ------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_PRSHT_H */
