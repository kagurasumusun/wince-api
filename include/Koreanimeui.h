/*
 * Koreanimeui.h -- Korean Pocket IME user-interface interface.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE pages
 * of the International book (Korean Pocket IME reference,
 * tools/manifests/intl-book.manifest): the IKoreanImeUI interface
 * overview and its 18 method pages (Requirements rows print Header
 * Koreanimeui.h; the interface/method pages print "Link Library:
 * Uuid.lib" -- GUID linkage, no def).  Following the M44/M69/M80
 * interface-record policy (no vtable layout is published), the
 * interface is carried as an opaque forward declaration plus
 * verbatim method-signature records.  See docs/inventory.md M84.
 */

#ifndef AKARI_KOREANIMEUI_H
#define AKARI_KOREANIMEUI_H

#include "Windef.h"    /* DWORD, LONG, VOID, WCHAR, BYTE, RECT */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct IKoreanImeUI IKoreanImeUI;

/* "IKoreanImeUI" (Vtable order: IUnknown then the methods below, as
 * listed on the interface page table):
 *  - InitializeUIWindows:  `STDMETHOD InitializeUIWindows(VOID);`
 *  - UninitializeUIWindows: `STDMETHOD UninitializeUIWindows(VOID);`
 *  - GetCandWndPos:        `STDMETHOD GetCandWndPos(LONG* px,
 *                          LONG* py);`
 *  - SetCandWndPos:        `STDMETHOD SetCandWndPos(DWORD dwFlag,
 *                          RECT* pRect, LONG x, LONG y);`
 *  - ShowHideCandWnd:      `STDMETHOD ShowHideCandWnd(int bShow);`
 *  - RedrawCandWnd:        `STDMETHOD RedrawCandWnd(VOID);`
 *  - SetCandData:          `STDMETHOD SetCandData(DWORD dwSize,
 *                          BYTE* lpCandList);`
 *  - GetCompWndPos:        `STDMETHOD GetCompWndPos(LONG* px,
 *                          LONG* py);`
 *  - SetCompWndPos:        `STDMETHOD SetCompWndPos(LONG x, LONG y);`
 *  - ShowHideCompWnd:      `STDMETHOD ShowHideCompWnd(int bShow);`
 *  - RedrawCompWnd:        `STDMETHOD RedrawCompWnd(VOID);`
 *  - SetCompData:          `STDMETHOD SetCompData(DWORD dwCompLen,
 *                          WCHAR* lpCompStr);`
 *  - GetCompositionFont:   `STDMETHOD GetCompoitionFont(DWORD dwSize,
 *                          BYTE* pLogFont);` (method name misprinted
 *                          "GetCompoitionFont" on its page)
 *  - GetStatusWndPos:      `STDMETHOD GetStatusWndPos(LONG* px,
 *                          LONG* py);`
 *  - SetStatusWndPos:      `STDMETHOD SetStatusWndPos(LONG x,
 *                          LONG y);`
 *  - ShowHideStatusWnd:    `STDMETHOD ShowHideStatusWnd(int bShow);`
 *  - RedrawStatusWnd:      `STDMETHOD RedrawStatusWnd(VOID);`
 *  - SetStatusData:        `STDMETHOD SetStatusData(DWORD dwState);` */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_KOREANIMEUI_H */
