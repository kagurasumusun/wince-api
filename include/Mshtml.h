/*
 * Mshtml.h -- Windows CE MSHTML host-navigation interfaces (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE
 * documentation (learn.microsoft.com previous-versions archive;
 * page ids cited per record).  This is the complete "Mshtml.h,
 * Mshtmhst.idl." row set of the Internet Client Services book
 * harvest (M92/M93, tools/manifests/internetclient-book.manifest):
 * 11 method pages, every Requirements row printing "OS Versions:
 * Windows CE .NET 4.1 and later.  Link Library: Mshtml.dll."
 * (module form; no import-library surface, no def file).
 *
 * Layout policy (the Urlmon.h M58 pattern): every interface is an
 * opaque struct typedef exactly as the pages treat it, and every
 * documented method signature is recorded in the interface record
 * comments.
 *
 * Print artifacts recorded (M93): the MIDL print style -- "virtual
 * HRESULT STDMETHODCALLTYPE" prefixes, __RPC_FAR pointer
 * qualifiers, glued name/type pairs (DWORDrectToActivate,
 * RECTlastRect, NVFOCUS_DIRECTIONdirection) -- is kept verbatim
 * in the records; the DeactivateRect page ms918597 misspells the
 * callee "DectivateRect"; OnRectsChange prints empty parentheses.
 * NVFOCUS_DIRECTION (two records pass it by value) is declared in
 * Mshtmhst.h per its own page ms918828.  HELD: the
 * OnNavigationStatusChange prose names NAV_STATUS_CANNAVIGATENOW
 * -- no page, no value, nowhere published.
 */

#ifndef AKARI_MSHTML_H
#define AKARI_MSHTML_H

#include "Windef.h"      /* DWORD, RECT, VOID */
#include "Mshtmhst.h"    /* NVFOCUS_DIRECTION (by-value records) */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Interfaces -- opaque typedefs, methods recorded below                */
/* ------------------------------------------------------------------ */

/* IOleControlNavigation2 (7 documented methods). */
typedef struct IOleControlNavigation2 IOleControlNavigation2;

/* IOleControlNavigation2AdviseSink (4 documented methods). */
typedef struct IOleControlNavigation2AdviseSink IOleControlNavigation2AdviseSink;

/* ------------------------------------------------------------------ */
/* Interface method records                                             */
/* ------------------------------------------------------------------ */
/*
IOleControlNavigation2:
 *   ms918392  HRESULT STDMETHODCALLTYPE ActivateRect( DWORD
 *             rectToActivate);
 *   ms918597  HRESULT STDMETHODCALLTYPE DectivateRect(VOID);
 *   ms918608  HRESULT GetControlNavigationCapabilities( DWORD*
 *             navigationFlags);
 *   ms918620  HRESULT STDMETHODCALLTYPE GetCurrentRectIndex( DWORD
 *             __RPC_FAR* current);
 *   ms918717  HRESULT GetNavigationRectCount( DWORD __RPC_FAR*
 *             rectCount);
 *   ms918731  virtual HRESULT STDMETHODCALLTYPE GetNavigationRects(
 *             DWORD rectCount, RECT __RPC_FAR rects[ ]);
 *   ms918755  HRESULT STDMETHODCALLTYPE NavigateInControl( RECT
 *             lastRect, NVFOCUS_DIRECTION direction);
 *
IOleControlNavigation2AdviseSink:
 *   ms918399  HRESULT STDMETHODCALLTYPE NavigateOutControl(RECT
 *             currentRect, NVFOCUS_DIRECTION direction);
 *   ms918561  HRESULT STDMETHODCALLTYPE OnFocusRectChange( RECT*
 *             newRect);
 *   ms918569  virtual HRESULT STDMETHODCALLTYPE
 *             OnNavigationStatusChange( DWORD navigationStatus);
 *   ms918586  HRESULT STDMETHODCALLTYPE OnRectsChange();
 *
 */
/* ------------------------------------------------------------------
 * Book surface: internetclient-book (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms918392 IOleControlNavigation2::ActivateRect (Header: Mshtml.h, Mshtmhst.idl.) */
/* ms918597 IOleControlNavigation2::DeactivateRect (Header: Mshtml.h, Mshtmhst.idl.) */
/* ms918608 IOleControlNavigation2::GetControlNavigationCapabilities (Header: Mshtml.h, Mshtmhst.idl.) */
/* ms918620 IOleControlNavigation2::GetCurrentRectIndex (Header: Mshtml.h, Mshtmhst.idl.) */
/* ms918717 IOleControlNavigation2::GetNavigationRectCount (Header: Mshtml.h, Mshtmhst.idl.) */
/* ms918731 IOleControlNavigation2::GetNavigationRects (Header: Mshtml.h, Mshtmhst.idl.) */
/* ms918755 IOleControlNavigation2::NavigateInControl (Header: Mshtml.h, Mshtmhst.idl.) */
/* ms918399 IOleControlNavigation2AdviseSink::NavigateOutControl (Header: Mshtml.h, Mshtmhst.idl.) */
/* ms918561 IOleControlNavigation2AdviseSink::OnFocusRectChange (Header: Mshtml.h, Mshtmhst.idl.) */
/* ms918569 IOleControlNavigation2AdviseSink::OnNavigationStatusChange (Header: Mshtml.h, Mshtmhst.idl.) */
/* ms918586 IOleControlNavigation2AdviseSink::OnRectsChange (Header: Mshtml.h, Mshtmhst.idl.) */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_MSHTML_H */
