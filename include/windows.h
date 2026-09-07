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
#include "winnls.h"
#include "winreg.h"
#include "psapi.h"
#include "msgqueue.h"
#include "excpt.h"
#include "winuser.h"
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

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WINDOWS_H */
