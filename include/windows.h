/*
 * windows.h -- umbrella header for the Akari API (Windows CE 4/5/6).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch; spec basis is the official Microsoft Windows
 * CE documentation (see windef.h / winbase.h / winuser.h for
 * per-declaration page IDs).  On Windows CE every API is
 * Unicode-only; no UNICODE switch exists -- the wide names are the
 * API.  This umbrella mirrors the CE SDK's Windows.h: it includes the
 * component headers, and the few items whose official pages list
 * "Header: Windows.h." live directly below (same rule as ExitProcess).
 */

#ifndef AKARI_WINDOWS_H
#define AKARI_WINDOWS_H

#include "windef.h"
#include "winbase.h"
/* GDI: CE 5.0 Requirement rows for the GDI Reference items list
 * "Header: Windows.h" (the CE 5.0 headers were monolithic); the items
 * live in wingdi.h -- the component header of the CE 6.0 era -- and
 * are included here so Windows.h still provides them (see wingdi.h). */
#include "wingdi.h"
#include "tvout.h"    /* ms914096 VIDEOPARAMETERS (Header: Tvout.h) */
#include "winnls.h"
#include "winreg.h"
#include "psapi.h"
#include "msgqueue.h"
#include "excpt.h"
#include "winuser.h"
/* Component headers of the CE SDK that CE applications include either
 * directly or via Windows.h: Notify.h (Notify Reference) and Shellapi.h
 * (Resources Reference items with Header: Shellapi.h). */
#include "notify.h"
#include "shellapi.h"
#include "winerror.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ms885217 "ExitProcess (Windows CE 5.0)" lists Header: Windows.h,
 * which is why this declaration lives here (see winbase.h for the
 * export-surface conflict note). */
VOID ExitProcess(UINT uExitCode);

/* ------------------------------------------------------------------ */
/* GWES items whose official pages give Header: Windows.h.            */
/* ------------------------------------------------------------------ */

/* Window properties (Window Properties Reference; CE .NET 4.0+;
 * Header Windows.h; Link Library Coredll.lib).  Window properties are
 * per-window data keyed by a string or atom. */
BOOL   SetPropW(HWND hWnd, LPCTSTR lpString, HANDLE hData);  /* aa453647 */
#define SetProp SetPropW
HANDLE GetPropW(HWND hWnd, LPCTSTR lpString);               /* aa453155 */
#define GetProp GetPropW
HANDLE RemovePropW(HWND hWnd, LPCTSTR lpString);            /* ms939781 */
#define RemoveProp RemovePropW
int    EnumPropsExW(HWND hWnd, PROPENUMPROCEX lpEnumFunc,   /* aa453050 */
                    LPARAM lParam);
#define EnumPropsEx EnumPropsExW

/* aa453551 "PropEnumProcEx (Windows CE 5.0)": the enumeration callback
 * prototype (typedef PROPENUMPROCEX in winuser.h). */
BOOL CALLBACK PropEnumProcEx(HWND hwnd, LPTSTR lpszString,
                             HANDLE hData, ULONG_PTR dwData);

/* Atoms (Atoms Reference; CE .NET 4.0+; Header Windows.h; Link
 * Library Coredll.lib). */
ATOM GlobalAddAtomW(LPCTSTR lpString);      /* aa453188 */
#define GlobalAddAtom GlobalAddAtomW
ATOM GlobalDeleteAtom(ATOM nAtom);          /* aa453189 */
ATOM GlobalFindAtomW(LPCTSTR lpString);     /* aa453190 */
#define GlobalFindAtom GlobalFindAtomW

/* aa453137 "GetMessageQueueReadyTimeStamp (CE .NET 4.0+)": returns the
 * time stamp of the first message in the queue.  Header Windows.h;
 * Link Library Coredll.lib. */
DWORD GetMessageQueueReadyTimeStamp(HWND hWnd);

/* ms939981 "SendMessageTimeout (Windows CE 5.0)":
 * LRESULT SendMessageTimeout(HWND, UINT, WPARAM, LPARAM, UINT, UINT,
 * PDWORD_PTR).  CE .NET 4.0+; Windows.h; Coredll.lib. */
LRESULT SendMessageTimeout(HWND hWnd, UINT Msg, WPARAM wParam,
                            LPARAM lParam, UINT fuFlags, UINT uTimeout,
                            PDWORD_PTR lpdwResult);

/* ms932696 "ScrollDC (Windows CE 5.0)":
 * BOOL ScrollDC(HDC, int, int, const RECT*, const RECT*, HRGN, LPRECT).
 * CE 1.0+; Windows.h; Coredll.lib. */
BOOL ScrollDC(HDC hDC, int dx, int dy, const RECT *lprcScroll,
              const RECT *lprcClip, HRGN hrgnUpdate, LPRECT lprcUpdate);

/* M28 dialog-book items whose official pages give Header: Windows.h. */

/* ms911827 "MessageBox (Windows CE 5.0)": modal message box.  CE 1.0+;
 * Header: Windows.h; Link Library Msgbox.lib.  Windows CE supports only
 * the wide form (the repo rule for text functions); uType combines the
 * MB_* styles documented in the "Message Box Styles" book. */
int MessageBoxW(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType);
#define MessageBox MessageBoxW

/* ms928573 "CheckDlgButton": sets the check state of a button control
 * (its official page prints an __inline prototype with Header:
 * Windows.h; Link Library Coredll.lib). */
BOOL CheckDlgButton(HWND hDlg, int nIDButton, UINT uCheck);

/* ms909866 "IsDlgButtonChecked": returns the check state of a button
 * (official page prints __inline UINT WINAPI ...; Header: Windows.h;
 * Link Library Coredll.lib). */
UINT IsDlgButtonChecked(HWND hDlg, int nIDButton);

/* aa452974 "DRAWITEMSTRUCT (Windows CE 5.0)": owner-draw item passed as
 * the lParam of WM_DRAWITEM; Header: Windows.h.  The typedef is shared
 * with the Combo Boxes / Menus owner-draw documentation. */
typedef struct tagDRAWITEMSTRUCT {
    UINT      CtlType;    /* ODT_* control type */
    UINT      CtlID;
    UINT      itemID;
    UINT      itemAction; /* ODA_* */
    UINT      itemState;  /* ODS_* */
    HWND      hwndItem;
    HDC       hDC;
    RECT      rcItem;
    ULONG_PTR itemData;
} DRAWITEMSTRUCT;


/* ms906279 "SetUserDefaultLCID" (CE .NET 4.0+; Header Windows.h per the
 * page; Link Library Coreloc.lib -> def/coreloc-doc.def).  Sets the
 * user default locale; the page requires broadcasting WM_WININICHANGE
 * with wParam INI_INTL afterwards. */
BOOL SetUserDefaultLCID(LCID Locale);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WINDOWS_H */
