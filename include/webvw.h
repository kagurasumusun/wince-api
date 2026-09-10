/*
 * webvw.h -- Windows CE Webview Browser Object interfaces (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE
 * documentation (learn.microsoft.com previous-versions archive;
 * page ids cited per record).  This is the complete webvw.h row
 * set of the Internet Client Services book harvest (M92/M93,
 * tools/manifests/internetclient-book.manifest): 68 method pages,
 * every Requirements row printing "Header: webvw.h  Link Library:
 * wvuuid.lib" and "OS Versions: Windows CE .NET 4.0 and later."
 * -- plus the three IHTMLCEPopupEvents popup-blocker pages whose
 * Requirements print the archive typo "Interned.h .h." (no twin
 * in any tree corrects it; their See-Also chain -- BeforeWindowOpen
 * -> "Using the Popup Blocker Interfaces" -> the IE6 support page
 * aa452009 -- ties them to this webview/IE feature set, so they are
 * recorded here).
 *
 * Layout policy (the Urlmon.h M58 pattern): every interface is an
 * opaque struct typedef exactly as the pages treat it, and every
 * documented method signature is recorded in the interface record
 * comments.  wvuuid.lib is the interface-UUID library -- the method
 * pages document vtable/dispinterface members, not exports, so
 * there is no import-library surface and no def file.
 *
 * Print artifacts recorded (M93): glued HRESULT/name and name/type
 * pairs split with repairs noted per record (FrameNavigate,
 * Refresh, Stop, get_LocationURL, get_title, navigate); the
 * OnStatusBar page aa452178 prints the callee "onStatusBar"
 * (lowercase o) -- kept verbatim.
 */

#ifndef AKARI_WEBVW_H
#define AKARI_WEBVW_H

#include "Windef.h"    /* BOOL, DWORD */
#include "Objbase.h"   /* HRESULT, BSTR, VARIANT, VARIANT_BOOL,
                          IDispatch, IUnknown, LPOLESTR */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Interfaces -- opaque typedefs, methods recorded below                */
/* ------------------------------------------------------------------ */

/* IBrowser (18 documented methods). */
typedef struct IBrowser IBrowser;

/* IBrowser2 (16 documented methods). */
typedef struct IBrowser2 IBrowser2;

/* IBrowser3 (16 documented methods). */
typedef struct IBrowser3 IBrowser3;

/* _DPIEWebBrowserEvents2 (18 documented methods). */
typedef struct _DPIEWebBrowserEvents2 _DPIEWebBrowserEvents2;

/* IHTMLCEPopupEvents (3 methods; popup blocker --
 * Requirements prints the archive typo "Interned.h .h."). */
typedef struct IHTMLCEPopupEvents IHTMLCEPopupEvents;

/* ------------------------------------------------------------------ */
/* Interface method records                                             */
/* ------------------------------------------------------------------ */
/*
IBrowser:
 *   ms906418  HRESULT navigate(BSTR bstrURL, long dwFlags, BSTR
 *             bstrTargetFrameName, BSTR bstrPostData);
 *   ms906408  HRESULT FrameNavigate(BSTR bstrURL, BSTR bstrTarget,
 *             BSTR bstrSource, BSTR bstrPostData, BOOL* pbCancel);
 *   ms906424  HRESULT Refresh(void);
 *   ms906425  HRESULT Stop(void);
 *   ms906409  HRESULT get_Busy(BOOL* pVal);
 *   ms906410  HRESULT get_CBrowserPointer( long* pVal);
 *   ms906411  HRESULT get_IsFrame( VARIANT_BOOL* pvbIsFrame);
 *   ms906412  HRESULT get_LocationURL(BSTR* pVal);
 *   ms906413  HRESULT get_MarginHeight( long* pVal);
 *   ms906414  HRESULT get_MarginWidth( long* pVal);
 *   ms906415  HRESULT get_ScrollStyle ( long* pVal);
 *   ms906416  HRESULT get_SelectedCodepage( long* pVal);
 *   ms906417  HRESULT get_title(BSTR* pVal);
 *   ms906419  HRESULT put_IsFrame( VARIANT_BOOL vbIsFrame);
 *   ms906420  HRESULT put_MarginHeight( long newVal);
 *   ms906421  HRESULT put_MarginWidth( long newVal);
 *   ms906422  HRESULT put_ScrollStyle ( long newVal);
 *   ms906423  HRESULT put_SelectedCodepage( long newVal);
 *
IBrowser2:
 *   ms906375  HRESULT get_ClearTypeEnabled( VARIANT_BOOL*
 *             pbClearTypeEnabled);
 *   ms906376  HRESULT get_FitToWindow( VARIANT_BOOL* pbFitToWindow);
 *   ms906377  HRESULT get_LayoutHeight( int* piLayoutHeight);
 *   ms906378  HRESULT get_LayoutWidth( int* piLayoutWidth);
 *   ms906379  HRESULT get_LocationBaseURL( BSTR*
 *             bstrBaseLocationURL);
 *   ms906380  HRESULT get_PlaySounds( VARIANT_BOOL* pbPlaySounds);
 *   ms906381  HRESULT get_ScriptingEnabled( VARIANT_BOOL*
 *             pbScriptingEnabled);
 *   ms906382  HRESULT get_ShowImages( VARIANT_BOOL* pbShowImages);
 *   ms906383  HRESULT get_ZoomLevel( DWORD* pdwZoomLevel);
 *   ms906384  HRESULT put_ClearTypeEnabled( VARIANT_BOOL
 *             bClearTypeEnabled);
 *   ms906385  HRESULT put_FitToWindow( VARIANT_BOOL bFitToWindow);
 *   ms906386  HRESULT put_LocationBaseURL( BSTR bstrBaseLocationURL);
 *   ms906387  HRESULT put_PlaySounds( VARIANT_BOOL bPlaySounds);
 *   ms906388  HRESULT put_ScriptingEnabled( VARIANT_BOOL
 *             bScriptingEnabled);
 *   ms906389  HRESULT put_ShowImages( VARIANT_BOOL bShowImages);
 *   ms906390  HRESULT put_ZoomLevel( DWORD dwZoomLevel);
 *
IBrowser3:
 *   ms906392  HRESULT addStyle( BSTR bstrStyle);
 *   ms906393  HRESULT get_ActiveXEnabled( VARIANT_BOOL*
 *             pvbActiveXEnabled);
 *   ms906394  HRESULT get_CanCopy( VARIANT_BOOL* pvbCanCopy);
 *   ms906395  HRESULT get_ContextMenuEnabled( VARIANT_BOOL*
 *             pvbContextMenu);
 *   ms906397  HRESULT get_FocusRectEnabled( VARIANT_BOOL*
 *             pvbFocusRectEnabled);
 *   ms906398  HRESULT get_IntegralPaging( VARIANT_BOOL*
 *             pvbIntegralPaging);
 *   ms906400  HRESULT get_SelectionEnabled( VARIANT_BOOL*
 *             pvbSelectionEnabled);
 *   ms906401  HRESULT get_SuperFitToWindow( VARIANT_BOOL*
 *             pbSuperFitToWindow);
 *   ms906396  HRESULT get_document( IDispatch** ppDisp);
 *   ms906399  HRESULT get_script( IDispatch** ppDisp);
 *   ms906402  HRESULT put_ActiveXEnabled( VARIANT_BOOL
 *             vbActiveXEnabled);
 *   ms906403  HRESULT put_ContextMenuEnabled( VARIANT_BOOL
 *             vbContextMenu);
 *   ms906404  HRESULT put_FocusRectEnabled( VARIANT_BOOL
 *             bFocusRectEnabled);
 *   ms906405  HRESULT put_IntegralPaging( VARIANT_BOOL
 *             vbIntegralPaging);
 *   ms906406  HRESULT put_SelectionEnabled( VARIANT_BOOL
 *             vbSelectionEnabled);
 *   ms906407  HRESULT put_SuperFitToWindow( VARIANT_BOOL
 *             bSuperFitToWindow);
 *
_DPIEWebBrowserEvents2:
 *   aa452156  void BeforeNavigate2( IDispatch* pdisp, VARIANT*
 *             pvtURL, VARIANT* pvtFlags, VARIANT* pvtTargetFrameName,
 *             VARIANT* pvtPostData, VARIANT* pvtHeaders,
 *             VARIANT_BOOL* pvbCancel);
 *   aa452157  void CommandStateChange( long lCommand, VARIANT_BOOL
 *             vbEnable);
 *   aa452159  void DocumentComplete ( IDispatch* pdisp, VARIANT*
 *             pvtURL);
 *   aa452161  void DownloadBegin(void);
 *   aa452163  void DownloadComplete(void);
 *   aa452165  void NavigateComplete2( IDispatch* pdisp, VARIANT
 *             vtURL);
 *   aa452167  void NewWindow2( IDispatch** ppdisp, VARIANT_BOOL*
 *             pvbCancel);
 *   aa452170  void OnFullScreen( VARIANT_BOOL vbFullScreen);
 *   aa452172  void OnMenuBar( VARIANT_BOOL vbMenuBar);
 *   aa452174  void OnProgressChange( long lProgress, long
 *             lProgressMax);
 *   aa452176  void OnQuit(void);
 *   aa452178  void onStatusBar( VARIANT_BOOL vbOnStatusBar);
 *   aa452179  void OnTheaterMode( VARIANT_BOOL vbOnTheaterMode);
 *   aa452181  void OnToolBar( VARIANT_BOOL vbOnToolBar);
 *   aa452183  void OnVisible(void);
 *   aa452185  void PropertyChange( BSTR bstrProperty);
 *   aa452187  void StatusTextChange( BSTR bstrText);
 *   aa452189  void TitleChange( BSTR bstrTitle);
 *
IHTMLCEPopupEvents:
 *   aa451906  HRESULT BeforeWindowOpen( BSTR url, BSTR urlContext,
 *             BSTR name, BSTR features, IUnknown* punkEvents);
 *   aa452134  HRESULT Count(long *pCount);
 *   aa452193  HRESULT Event( int index, DWORD *pdispidEvt);
 *
 */
/* ------------------------------------------------------------------
 * Book surface: internetclient-book (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa452156 _DPIEWebBrowserEvents2::BeforeNavigate2 (Header: webvw.h) */
/* aa452157 _DPIEWebBrowserEvents2::CommandStateChange (Header: webvw.h) */
/* aa452159 _DPIEWebBrowserEvents2::DocumentComplete (Header: webvw.h) */
/* aa452161 _DPIEWebBrowserEvents2::DownloadBegin (Header: webvw.h) */
/* aa452163 _DPIEWebBrowserEvents2::DownloadComplete (Header: webvw.h) */
/* aa452165 _DPIEWebBrowserEvents2::NavigateComplete2 (Header: webvw.h) */
/* aa452167 _DPIEWebBrowserEvents2::NewWindow2 (Header: webvw.h) */
/* aa452170 _DPIEWebBrowserEvents2::OnFullScreen (Header: webvw.h) */
/* aa452172 _DPIEWebBrowserEvents2::OnMenuBar (Header: webvw.h) */
/* aa452174 _DPIEWebBrowserEvents2::OnProgressChange (Header: webvw.h) */
/* aa452176 _DPIEWebBrowserEvents2::OnQuit (Header: webvw.h) */
/* aa452178 _DPIEWebBrowserEvents2::OnStatusBar (Header: webvw.h) */
/* aa452179 _DPIEWebBrowserEvents2::OnTheaterMode (Header: webvw.h) */
/* aa452181 _DPIEWebBrowserEvents2::OnToolBar (Header: webvw.h) */
/* aa452183 _DPIEWebBrowserEvents2::OnVisible (Header: webvw.h) */
/* aa452185 _DPIEWebBrowserEvents2::PropertyChange (Header: webvw.h) */
/* aa452187 _DPIEWebBrowserEvents2::StatusTextChange (Header: webvw.h) */
/* aa452189 _DPIEWebBrowserEvents2::TitleChange (Header: webvw.h) */
/* ms906375 IBrowser2::get_ClearTypeEnabled (Header: webvw.h) */
/* ms906376 IBrowser2::get_FitToWindow (Header: webvw.h) */
/* ms906377 IBrowser2::get_LayoutHeight (Header: webvw.h) */
/* ms906378 IBrowser2::get_LayoutWidth (Header: webvw.h) */
/* ms906379 IBrowser2::get_LocationBaseURL (Header: webvw.h) */
/* ms906380 IBrowser2::get_PlaySounds (Header: webvw.h) */
/* ms906381 IBrowser2::get_ScriptingEnabled (Header: webvw.h) */
/* ms906382 IBrowser2::get_ShowImages (Header: webvw.h) */
/* ms906383 IBrowser2::get_ZoomLevel (Header: webvw.h) */
/* ms906384 IBrowser2::put_ClearTypeEnabled (Header: webvw.h) */
/* ms906385 IBrowser2::put_FitToWindow (Header: webvw.h) */
/* ms906386 IBrowser2::put_LocationBaseURL (Header: webvw.h) */
/* ms906387 IBrowser2::put_PlaySounds (Header: webvw.h) */
/* ms906388 IBrowser2::put_ScriptingEnabled (Header: webvw.h) */
/* ms906389 IBrowser2::put_ShowImages (Header: webvw.h) */
/* ms906390 IBrowser2::put_ZoomLevel (Header: webvw.h) */
/* ms906392 IBrowser3::addStyle (Header: webvw.h) */
/* ms906393 IBrowser3::get_ActiveXEnabled (Header: webvw.h) */
/* ms906394 IBrowser3::get_CanCopy (Header: webvw.h) */
/* ms906395 IBrowser3::get_ContextMenuEnabled (Header: webvw.h) */
/* ms906396 IBrowser3::get_document (Header: webvw.h) */
/* ms906397 IBrowser3::get_FocusRectEnabled (Header: webvw.h) */
/* ms906398 IBrowser3::get_IntegralPaging (Header: webvw.h) */
/* ms906399 IBrowser3::get_script (Header: webvw.h) */
/* ms906400 IBrowser3::get_SelectionEnabled (Header: webvw.h) */
/* ms906401 IBrowser3::get_SuperFitToWindow (Header: webvw.h) */
/* ms906402 IBrowser3::put_ActiveXEnabled (Header: webvw.h) */
/* ms906403 IBrowser3::put_ContextMenuEnabled (Header: webvw.h) */
/* ms906404 IBrowser3::put_FocusRectEnabled (Header: webvw.h) */
/* ms906405 IBrowser3::put_IntegralPaging (Header: webvw.h) */
/* ms906406 IBrowser3::put_SelectionEnabled (Header: webvw.h) */
/* ms906407 IBrowser3::put_SuperFitToWindow (Header: webvw.h) */
/* ms906408 IBrowser::FrameNavigate (Header: webvw.h) */
/* ms906409 IBrowser::get_Busy (Header: webvw.h) */
/* ms906410 IBrowser::get_CBrowserPointer (Header: webvw.h) */
/* ms906411 IBrowser::get_IsFrame (Header: webvw.h) */
/* ms906412 IBrowser::get_LocationURL (Header: webvw.h) */
/* ms906413 IBrowser::get_MarginHeight (Header: webvw.h) */
/* ms906414 IBrowser::get_MarginWidth (Header: webvw.h) */
/* ms906415 IBrowser::get_ScrollStyle (Header: webvw.h) */
/* ms906416 IBrowser::get_SelectedCodepage (Header: webvw.h) */
/* ms906417 IBrowser::get_title (Header: webvw.h) */
/* ms906418 IBrowser::navigate (Header: webvw.h) */
/* ms906419 IBrowser::put_IsFrame (Header: webvw.h) */
/* ms906420 IBrowser::put_MarginHeight (Header: webvw.h) */
/* ms906421 IBrowser::put_MarginWidth (Header: webvw.h) */
/* ms906422 IBrowser::put_ScrollStyle (Header: webvw.h) */
/* ms906423 IBrowser::put_SelectedCodepage (Header: webvw.h) */
/* ms906424 IBrowser::Refresh (Header: webvw.h) */
/* ms906425 IBrowser::Stop (Header: webvw.h) */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WEBVW_H */
