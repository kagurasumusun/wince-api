/*
 * Uxtheme.h -- Windows CE Theme-Services draw API (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE 5.0
 * documentation (learn.microsoft.com previous-versions archive;
 * page ids cited per record).  This is the complete Uxtheme.h
 * surface of the Internet Client Services book harvest (M92/M93,
 * tools/manifests/internetclient-book.manifest): 8 function pages,
 * every Requirements row printing "Header: Uxtheme.h.  Link
 * Library: Ietheme.dll." and "OS Versions: Windows CE 5.0 and
 * later.".
 *
 * HELD (name documented, type not published anywhere official):
 * HTHEME -- it appears by value in 7 of the 8 signature prints and
 * as the OpenThemeDataEx return, but no page in the preserved
 * corpus (pages/pages4/pages6/pagesw/pageswm, full-corpus grep)
 * prints its typedef.  Hold policy (the HINTERNET M92 precedent):
 * every HTHEME-bearing prototype stays a record below; only
 * IsAppThemed -- BOOL (void), no HTHEME anywhere -- declares.
 *
 * Print artifacts recorded: the GetThemeFont (ms906315) and
 * HitTestThemeBackground (ms906340) pages both print the callee
 * name "GetThemeColor" (archive copy-paste misprint -- the
 * parameter lists match the page titles); the GetThemeColor print
 * itself breaks the line after "HDC hdc,"; OpenThemeDataEx glues
 * "DWORDdwFlags".  GetThemeBackgroundExtent prints both RECT
 * pointers const, including the out parameter pExtentRect, kept
 * verbatim.
 */

#ifndef AKARI_UXTHEME_H
#define AKARI_UXTHEME_H

#include "Windef.h"    /* BOOL, DWORD, HWND, RECT */
#include "Wingdi.h"    /* HDC, HRGN, COLORREF, LOGFONT, POINT */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Declared (all parameter types resolve) -- 1 of 8                     */
/* ------------------------------------------------------------------ */

/* ms918803 "IsAppThemed": print `BOOL IsAppThemed(void);` */
AKARI_CE_IMPORT BOOL IsAppThemed(void)
                    AKARI_CE_NAME(IsAppThemed);

/* ------------------------------------------------------------------ */
/* Recorded -- HTHEME by value / return (typedef unpublished)           */
/* ------------------------------------------------------------------ */

/* aa452106 "CloseThemeData": `HRESULT CloseThemeData( HTHEME hTheme);` */
/* aa452191 "DrawThemeBackground": `HRESULT DrawThemeBackground( HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT* pRect, const RECT* pClipRect);` */
/* ms906298 "GetThemeBackgroundExtent": `HRESULT GetThemeBackgroundExtent( HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT* pContentRect, const RECT* pExtentRect);` */
/* ms906304 "GetThemeColor": `HRESULT GetThemeColor( HTHEME hTheme, HDC hdc, int iPartId, int iStateId, int iPropID, COLORREF* pColor);` */
/* ms906315 "GetThemeFont": `HRESULT GetThemeColor( HTHEME hTheme, HDC hdc, int iPartId, int iStateId, int iPropID, LOGFONT* pFont);` */
/* ms906340 "HitTestThemeBackground": `HRESULT GetThemeColor( HTHEME hTheme, HDC hdc, int iPartId, int iStateId, DWORD dwOptions, const RECT* pRect, HRGN hrgn, POINT ptTest, WORD* pwHitTestCode);` */
/* ms918830 "OpenThemeDataEx": `HTHEME OpenThemeDataEx( HWND hwnd, LPCWSTR pszClassList, DWORD dwFlags);` */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_UXTHEME_H */
