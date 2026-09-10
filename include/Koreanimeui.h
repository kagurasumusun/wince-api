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

/* ------------------------------------------------------------------
 * Book surface: intl-book (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms905489 IKoreanImeUI::GetCandWndPos (Header: KoreanImeUI.h.) */
/* ms905490 IKoreanImeUI::GetCompositionFont (Header: KoreanImeUI.h.) */
/* ms905491 IKoreanImeUI::GetCompWndPos (Header: KoreanImeUI.h.) */
/* ms905492 IKoreanImeUI::GetStatusWndPos (Header: KoreanImeUI.h.) */
/* ms905493 IKoreanImeUI::InitializeUIWindows (Header: KoreanImeUI.h.) */
/* ms905494 IKoreanImeUI::RedrawCandWnd (Header: KoreanImeUI.h.) */
/* ms905495 IKoreanImeUI::RedrawCompWnd (Header: KoreanImeUI.h.) */
/* ms905496 IKoreanImeUI::RedrawStatusWnd (Header: KoreanImeUI.h.) */
/* ms905497 IKoreanImeUI::SetCandData (Header: KoreanImeUI.h.) */
/* ms905498 IKoreanImeUI::SetCandWndPos (Header: KoreanImeUI.h.) */
/* ms905499 IKoreanImeUI::SetCompData (Header: KoreanImeUI.h.) */
/* ms905500 IKoreanImeUI::SetCompWndPos (Header: KoreanImeUI.h.) */
/* ms905501 IKoreanImeUI::SetStatusData (Header: KoreanImeUI.h.) */
/* ms905502 IKoreanImeUI::SetStatusWndPos (Header: KoreanImeUI.h.) */
/* ms905503 IKoreanImeUI::ShowHideCandWnd (Header: KoreanImeUI.h.) */
/* ms905504 IKoreanImeUI::ShowHideCompWnd (Header: KoreanImeUI.h.) */
/* ms905715 IKoreanImeUI::ShowHideStatusWnd (Header: KoreanImeUI.h.) */
/* ms905791 IKoreanImeUI::UninitializeUIWindows (Header: KoreanImeUI.h.) */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_KOREANIMEUI_H */
