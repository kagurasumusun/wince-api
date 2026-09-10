#!/usr/bin/env python3
"""Emit include/Uxtheme.h, include/webvw.h, include/Mshtml.h,
include/Mshtmhst.h (M93 -- Internet Client book close-out)."""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from rtctext import page_text  # noqa: F401  (page-text re-verification)

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# ---------------------------------------------------------------- data

# Uxtheme.h: Ietheme.dll rows, CE 5.0+.  HTHEME appears by value in 7 of
# the 8 prints and has NO typedef on any page in the preserved corpus
# (grep across pages/pages4/pages6/pagesw/pageswm) -> hold policy: all
# HTHEME-bearing prototypes are records; only IsAppThemed (BOOL(void))
# declares.
UXTHEME_RECORDS = [
    ("aa452106", "CloseThemeData",
     "HRESULT CloseThemeData( HTHEME hTheme);"),
    ("aa452191", "DrawThemeBackground",
     "HRESULT DrawThemeBackground( HTHEME hTheme, HDC hdc, int iPartId,"
     " int iStateId, const RECT* pRect, const RECT* pClipRect);"),
    ("ms906298", "GetThemeBackgroundExtent",
     "HRESULT GetThemeBackgroundExtent( HTHEME hTheme, HDC hdc,"
     " int iPartId, int iStateId, const RECT* pContentRect,"
     " const RECT* pExtentRect);"),
    ("ms906304", "GetThemeColor",
     "HRESULT GetThemeColor( HTHEME hTheme, HDC hdc, int iPartId,"
     " int iStateId, int iPropID, COLORREF* pColor);"),
    ("ms906315", "GetThemeFont",
     "HRESULT GetThemeColor( HTHEME hTheme, HDC hdc, int iPartId,"
     " int iStateId, int iPropID, LOGFONT* pFont);"),
    ("ms906340", "HitTestThemeBackground",
     "HRESULT GetThemeColor( HTHEME hTheme, HDC hdc, int iPartId,"
     " int iStateId, DWORD dwOptions, const RECT* pRect, HRGN hrgn,"
     " POINT ptTest, WORD* pwHitTestCode);"),
    ("ms918830", "OpenThemeDataEx",
     "HTHEME OpenThemeDataEx( HWND hwnd, LPCWSTR pszClassList,"
     " DWORD dwFlags);"),
]

# webvw.h: IBrowser/IBrowser2/IBrowser3/_DPIEWebBrowserEvents2 method
# records (wvuuid.lib on every page) + the IHTMLCEPopupEvents popup
# blocker methods (Requirements prints the archive typo "Interned.h .h.").
WEBVW_INTERFACES = [
    ("IBrowser", 18, [
        ("ms906418", "HRESULT navigate(BSTR bstrURL, long dwFlags,"
         " BSTR bstrTargetFrameName, BSTR bstrPostData);"),
        ("ms906408", "HRESULT FrameNavigate(BSTR bstrURL, BSTR bstrTarget,"
         " BSTR bstrSource, BSTR bstrPostData, BOOL* pbCancel);"),
        ("ms906424", "HRESULT Refresh(void);"),
        ("ms906425", "HRESULT Stop(void);"),
        ("ms906409", "HRESULT get_Busy(BOOL* pVal);"),
        ("ms906410", "HRESULT get_CBrowserPointer( long* pVal);"),
        ("ms906411", "HRESULT get_IsFrame( VARIANT_BOOL* pvbIsFrame);"),
        ("ms906412", "HRESULT get_LocationURL(BSTR* pVal);"),
        ("ms906413", "HRESULT get_MarginHeight( long* pVal);"),
        ("ms906414", "HRESULT get_MarginWidth( long* pVal);"),
        ("ms906415", "HRESULT get_ScrollStyle ( long* pVal);"),
        ("ms906416", "HRESULT get_SelectedCodepage( long* pVal);"),
        ("ms906417", "HRESULT get_title(BSTR* pVal);"),
        ("ms906419", "HRESULT put_IsFrame( VARIANT_BOOL vbIsFrame);"),
        ("ms906420", "HRESULT put_MarginHeight( long newVal);"),
        ("ms906421", "HRESULT put_MarginWidth( long newVal);"),
        ("ms906422", "HRESULT put_ScrollStyle ( long newVal);"),
        ("ms906423", "HRESULT put_SelectedCodepage( long newVal);"),
    ]),
    ("IBrowser2", 16, [
        ("ms906375", "HRESULT get_ClearTypeEnabled("
         " VARIANT_BOOL* pbClearTypeEnabled);"),
        ("ms906376", "HRESULT get_FitToWindow( VARIANT_BOOL* pbFitToWindow);"),
        ("ms906377", "HRESULT get_LayoutHeight( int* piLayoutHeight);"),
        ("ms906378", "HRESULT get_LayoutWidth( int* piLayoutWidth);"),
        ("ms906379", "HRESULT get_LocationBaseURL("
         " BSTR* bstrBaseLocationURL);"),
        ("ms906380", "HRESULT get_PlaySounds( VARIANT_BOOL* pbPlaySounds);"),
        ("ms906381", "HRESULT get_ScriptingEnabled("
         " VARIANT_BOOL* pbScriptingEnabled);"),
        ("ms906382", "HRESULT get_ShowImages( VARIANT_BOOL* pbShowImages);"),
        ("ms906383", "HRESULT get_ZoomLevel( DWORD* pdwZoomLevel);"),
        ("ms906384", "HRESULT put_ClearTypeEnabled("
         " VARIANT_BOOL bClearTypeEnabled);"),
        ("ms906385", "HRESULT put_FitToWindow( VARIANT_BOOL bFitToWindow);"),
        ("ms906386", "HRESULT put_LocationBaseURL("
         " BSTR bstrBaseLocationURL);"),
        ("ms906387", "HRESULT put_PlaySounds( VARIANT_BOOL bPlaySounds);"),
        ("ms906388", "HRESULT put_ScriptingEnabled("
         " VARIANT_BOOL bScriptingEnabled);"),
        ("ms906389", "HRESULT put_ShowImages( VARIANT_BOOL bShowImages);"),
        ("ms906390", "HRESULT put_ZoomLevel( DWORD dwZoomLevel);"),
    ]),
    ("IBrowser3", 16, [
        ("ms906392", "HRESULT addStyle( BSTR bstrStyle);"),
        ("ms906393", "HRESULT get_ActiveXEnabled("
         " VARIANT_BOOL* pvbActiveXEnabled);"),
        ("ms906394", "HRESULT get_CanCopy( VARIANT_BOOL* pvbCanCopy);"),
        ("ms906395", "HRESULT get_ContextMenuEnabled("
         " VARIANT_BOOL* pvbContextMenu);"),
        ("ms906397", "HRESULT get_FocusRectEnabled("
         " VARIANT_BOOL* pvbFocusRectEnabled);"),
        ("ms906398", "HRESULT get_IntegralPaging("
         " VARIANT_BOOL* pvbIntegralPaging);"),
        ("ms906400", "HRESULT get_SelectionEnabled("
         " VARIANT_BOOL* pvbSelectionEnabled);"),
        ("ms906401", "HRESULT get_SuperFitToWindow("
         " VARIANT_BOOL* pbSuperFitToWindow);"),
        ("ms906396", "HRESULT get_document( IDispatch** ppDisp);"),
        ("ms906399", "HRESULT get_script( IDispatch** ppDisp);"),
        ("ms906402", "HRESULT put_ActiveXEnabled("
         " VARIANT_BOOL vbActiveXEnabled);"),
        ("ms906403", "HRESULT put_ContextMenuEnabled("
         " VARIANT_BOOL vbContextMenu);"),
        ("ms906404", "HRESULT put_FocusRectEnabled("
         " VARIANT_BOOL bFocusRectEnabled);"),
        ("ms906405", "HRESULT put_IntegralPaging("
         " VARIANT_BOOL vbIntegralPaging);"),
        ("ms906406", "HRESULT put_SelectionEnabled("
         " VARIANT_BOOL vbSelectionEnabled);"),
        ("ms906407", "HRESULT put_SuperFitToWindow("
         " VARIANT_BOOL bSuperFitToWindow);"),
    ]),
    ("_DPIEWebBrowserEvents2", 18, [
        ("aa452156", "void BeforeNavigate2( IDispatch* pdisp,"
         " VARIANT* pvtURL, VARIANT* pvtFlags,"
         " VARIANT* pvtTargetFrameName, VARIANT* pvtPostData,"
         " VARIANT* pvtHeaders, VARIANT_BOOL* pvbCancel);"),
        ("aa452157", "void CommandStateChange( long lCommand,"
         " VARIANT_BOOL vbEnable);"),
        ("aa452159", "void DocumentComplete ( IDispatch* pdisp,"
         " VARIANT* pvtURL);"),
        ("aa452161", "void DownloadBegin(void);"),
        ("aa452163", "void DownloadComplete(void);"),
        ("aa452165", "void NavigateComplete2( IDispatch* pdisp,"
         " VARIANT vtURL);"),
        ("aa452167", "void NewWindow2( IDispatch** ppdisp,"
         " VARIANT_BOOL* pvbCancel);"),
        ("aa452170", "void OnFullScreen( VARIANT_BOOL vbFullScreen);"),
        ("aa452172", "void OnMenuBar( VARIANT_BOOL vbMenuBar);"),
        ("aa452174", "void OnProgressChange( long lProgress,"
         " long lProgressMax);"),
        ("aa452176", "void OnQuit(void);"),
        ("aa452178", "void onStatusBar( VARIANT_BOOL vbOnStatusBar);"),
        ("aa452179", "void OnTheaterMode( VARIANT_BOOL vbOnTheaterMode);"),
        ("aa452181", "void OnToolBar( VARIANT_BOOL vbOnToolBar);"),
        ("aa452183", "void OnVisible(void);"),
        ("aa452185", "void PropertyChange( BSTR bstrProperty);"),
        ("aa452187", "void StatusTextChange( BSTR bstrText);"),
        ("aa452189", "void TitleChange( BSTR bstrTitle);"),
    ]),
    ("IHTMLCEPopupEvents", 3, [
        ("aa451906", "HRESULT BeforeWindowOpen( BSTR url, BSTR urlContext,"
         " BSTR name, BSTR features, IUnknown* punkEvents);"),
        ("aa452134", "HRESULT Count(long *pCount);"),
        ("aa452193", "HRESULT Event( int index, DWORD *pdispidEvt);"),
    ]),
]

# Mshtml.h: IOleControlNavigation2 (+AdviseSink) host-navigation
# interface method records (Mshtml.dll module rows, CE .NET 4.1+).
MSHTML_INTERFACES = [
    ("IOleControlNavigation2", [
        ("ms918392", "HRESULT STDMETHODCALLTYPE ActivateRect("
         " DWORD rectToActivate);"),
        ("ms918597", "HRESULT STDMETHODCALLTYPE DectivateRect(VOID);"),
        ("ms918608", "HRESULT GetControlNavigationCapabilities("
         " DWORD* navigationFlags);"),
        ("ms918620", "HRESULT STDMETHODCALLTYPE GetCurrentRectIndex("
         " DWORD __RPC_FAR* current);"),
        ("ms918717", "HRESULT GetNavigationRectCount("
         " DWORD __RPC_FAR* rectCount);"),
        ("ms918731", "virtual HRESULT STDMETHODCALLTYPE"
         " GetNavigationRects( DWORD rectCount,"
         " RECT __RPC_FAR rects[ ]);"),
        ("ms918755", "HRESULT STDMETHODCALLTYPE"
         " NavigateInControl( RECT lastRect,"
         " NVFOCUS_DIRECTION direction);"),
    ]),
    ("IOleControlNavigation2AdviseSink", [
        ("ms918399", "HRESULT STDMETHODCALLTYPE"
         " NavigateOutControl(RECT currentRect,"
         " NVFOCUS_DIRECTION direction);"),
        ("ms918561", "HRESULT STDMETHODCALLTYPE OnFocusRectChange("
         " RECT* newRect);"),
        ("ms918569", "virtual HRESULT STDMETHODCALLTYPE"
         " OnNavigationStatusChange( DWORD navigationStatus);"),
        ("ms918586", "HRESULT STDMETHODCALLTYPE OnRectsChange();"),
    ]),
]

# Mshtmhst.h: host method records (MSHTML calls them on the host
# container; the pages' own code example prints `MyContainer::GetFilename`).
MSHTMHST_RECORDS = [
    ("aa451975", "GetFilename",
     "HRESULT GetFilename( BOOL fSave, HWND hwnd, DWORD idFilterRes,"
     " LPOLESTR lpstrFileName, DWORD cchFile, long lCustData);"),
    ("ms905429", "ShowInternalMessage",
     "HRESULT ShowInternalMessage( HWND hwnd, LPOLESTR lpstrText,"
     " LPOLESTR lpstrCaption, DWORD dwType, DWORD dwMessageId,"
     " LPOLESTR lpstrHelpFile, DWORD dwHelpContext,"
     " LRESULT * plResult);"),
    ("ms905508", "ShowPrompt",
     "HRESULT ShowPrompt( HWND hwnd, LPOLESTR lpstrMessage,"
     " LPOLESTR lpstrDefault, VARIANT *pvarText, LRESULT *plResult);"),
]

NVFOCUS = [
    ("FOCUS_NONE", "0"), ("FOCUS_UP", "1"), ("FOCUS_DOWN", "2"),
    ("FOCUS_LEFT", "3"), ("FOCUS_RIGHT", "4"),
]



def rec(pid, sig, indent=10):
    """format one record comment, wrapped at 78 cols"""
    words = sig.split(" ")
    lines = []
    cur = ""
    for w in words:
        if len(cur) + len(w) + 1 > 78 - indent - len(pid) - 5 and cur:
            lines.append(cur)
            cur = w
        else:
            cur = (cur + " " + w).strip()
    lines.append(cur)
    out = [f" *   {pid}  {lines[0]}"]
    for cont in lines[1:]:
        out.append(" *   " + " " * indent + cont)
    return out

def W(path, lines):
    with open(os.path.join(ROOT, path), "w", encoding="utf-8") as fh:
        fh.write("\n".join(lines) + "\n")
    print(f"{path}: {len(lines)} lines")


def banner(c):
    return ["/* ------------------------------------------------------------------ */",
            f"/* {c:<68} */",
            "/* ------------------------------------------------------------------ */"]


# ---------------------------------------------------------------- Uxtheme
L = []
L += ["/*",
      " * Uxtheme.h -- Windows CE Theme-Services draw API (Akari API).",
      " *",
      " * Copyright (c) 2026 Akari API contributors",
      " * SPDX-License-Identifier: MIT",
      " *",
      " * Written from scratch from the official Microsoft Windows CE 5.0",
      " * documentation (learn.microsoft.com previous-versions archive;",
      " * page ids cited per record).  This is the complete Uxtheme.h",
      " * surface of the Internet Client Services book harvest (M92/M93,",
      " * tools/manifests/internetclient-book.manifest): 8 function pages,",
      " * every Requirements row printing \"Header: Uxtheme.h.  Link",
      " * Library: Ietheme.dll.\" and \"OS Versions: Windows CE 5.0 and",
      " * later.\".",
      " *",
      " * HELD (name documented, type not published anywhere official):",
      " * HTHEME -- it appears by value in 7 of the 8 signature prints and",
      " * as the OpenThemeDataEx return, but no page in the preserved",
      " * corpus (pages/pages4/pages6/pagesw/pageswm, full-corpus grep)",
      " * prints its typedef.  Hold policy (the HINTERNET M92 precedent):",
      " * every HTHEME-bearing prototype stays a record below; only",
      " * IsAppThemed -- BOOL (void), no HTHEME anywhere -- declares.",
      " *",
      " * Print artifacts recorded: the GetThemeFont (ms906315) and",
      " * HitTestThemeBackground (ms906340) pages both print the callee",
      " * name \"GetThemeColor\" (archive copy-paste misprint -- the",
      " * parameter lists match the page titles); the GetThemeColor print",
      " * itself breaks the line after \"HDC hdc,\"; OpenThemeDataEx glues",
      " * \"DWORDdwFlags\".  GetThemeBackgroundExtent prints both RECT",
      " * pointers const, including the out parameter pExtentRect, kept",
      " * verbatim.",
      " */",
      "",
      "#ifndef AKARI_UXTHEME_H",
      "#define AKARI_UXTHEME_H",
      "",
      '#include "Windef.h"    /* BOOL, DWORD, HWND, RECT */',
      '#include "Wingdi.h"    /* HDC, HRGN, COLORREF, LOGFONT, POINT */',
      "",
      "#ifdef __cplusplus",
      'extern "C" {',
      "#endif"]
L += [""]
L += banner("Declared (all parameter types resolve) -- 1 of 8")
L += [""]
L += ['/* ms918803 "IsAppThemed": print `BOOL IsAppThemed(void);` */']
L += ["AKARI_CE_IMPORT BOOL IsAppThemed(void)",
      "                    AKARI_CE_NAME(IsAppThemed);"]
L += [""]
L += banner("Recorded -- HTHEME by value / return (typedef unpublished)")
L += [""]
for pid, name, sig in UXTHEME_RECORDS:
    L += [f'/* {pid} "{name}": `{sig}` */']
L += [""]
L += ["#ifdef __cplusplus",
      "}",
      "#endif",
      "",
      "#endif /* AKARI_UXTHEME_H */"]
W("include/Uxtheme.h", L)

# ---------------------------------------------------------------- webvw
L = []
L += ["/*",
      " * webvw.h -- Windows CE Webview Browser Object interfaces (Akari API).",
      " *",
      " * Copyright (c) 2026 Akari API contributors",
      " * SPDX-License-Identifier: MIT",
      " *",
      " * Written from scratch from the official Microsoft Windows CE",
      " * documentation (learn.microsoft.com previous-versions archive;",
      " * page ids cited per record).  This is the complete webvw.h row",
      " * set of the Internet Client Services book harvest (M92/M93,",
      " * tools/manifests/internetclient-book.manifest): 68 method pages,",
      " * every Requirements row printing \"Header: webvw.h  Link Library:",
      " * wvuuid.lib\" and \"OS Versions: Windows CE .NET 4.0 and later.\"",
      " * -- plus the three IHTMLCEPopupEvents popup-blocker pages whose",
      " * Requirements print the archive typo \"Interned.h .h.\" (no twin",
      " * in any tree corrects it; their See-Also chain -- BeforeWindowOpen",
      " * -> \"Using the Popup Blocker Interfaces\" -> the IE6 support page",
      " * aa452009 -- ties them to this webview/IE feature set, so they are",
      " * recorded here).",
      " *",
      " * Layout policy (the Urlmon.h M58 pattern): every interface is an",
      " * opaque struct typedef exactly as the pages treat it, and every",
      " * documented method signature is recorded in the interface record",
      " * comments.  wvuuid.lib is the interface-UUID library -- the method",
      " * pages document vtable/dispinterface members, not exports, so",
      " * there is no import-library surface and no def file.",
      " *",
      " * Print artifacts recorded (M93): glued HRESULT/name and name/type",
      " * pairs split with repairs noted per record (FrameNavigate,",
      " * Refresh, Stop, get_LocationURL, get_title, navigate); the",
      " * OnStatusBar page aa452178 prints the callee \"onStatusBar\"",
      " * (lowercase o) -- kept verbatim.",
      " */",
      "",
      "#ifndef AKARI_WEBVW_H",
      "#define AKARI_WEBVW_H",
      "",
      '#include "Windef.h"    /* BOOL, DWORD */',
      '#include "Objbase.h"   /* HRESULT, BSTR, VARIANT, VARIANT_BOOL,',
      "                          IDispatch, IUnknown, LPOLESTR */",
      "",
      "#ifdef __cplusplus",
      'extern "C" {',
      "#endif"]
L += [""]
L += banner("Interfaces -- opaque typedefs, methods recorded below")
L += [""]
for name, count, methods in WEBVW_INTERFACES:
    if name == "IHTMLCEPopupEvents":
        L += [f'/* IHTMLCEPopupEvents ({count} methods; popup blocker --',
              ' * Requirements prints the archive typo "Interned.h .h."). */']
    else:
        L += [f"/* {name} ({count} documented methods). */"]
    L += [f"typedef struct {name} {name};", ""]
L += banner("Interface method records")
L += ["/*"]
for name, count, methods in WEBVW_INTERFACES:
    L += [f"{name}:"]
    for pid, sig in methods:
        L += rec(pid, sig)
    L += [" *"]
L += [" */",
      "#ifdef __cplusplus",
      "}",
      "#endif",
      "",
      "#endif /* AKARI_WEBVW_H */"]
W("include/webvw.h", L)

# ---------------------------------------------------------------- Mshtml
L = []
L += ["/*",
      " * Mshtml.h -- Windows CE MSHTML host-navigation interfaces (Akari API).",
      " *",
      " * Copyright (c) 2026 Akari API contributors",
      " * SPDX-License-Identifier: MIT",
      " *",
      " * Written from scratch from the official Microsoft Windows CE",
      " * documentation (learn.microsoft.com previous-versions archive;",
      " * page ids cited per record).  This is the complete \"Mshtml.h,",
      " * Mshtmhst.idl.\" row set of the Internet Client Services book",
      " * harvest (M92/M93, tools/manifests/internetclient-book.manifest):",
      " * 11 method pages, every Requirements row printing \"OS Versions:",
      " * Windows CE .NET 4.1 and later.  Link Library: Mshtml.dll.\"",
      " * (module form; no import-library surface, no def file).",
      " *",
      " * Layout policy (the Urlmon.h M58 pattern): every interface is an",
      " * opaque struct typedef exactly as the pages treat it, and every",
      " * documented method signature is recorded in the interface record",
      " * comments.",
      " *",
      " * Print artifacts recorded (M93): the MIDL print style -- \"virtual",
      " * HRESULT STDMETHODCALLTYPE\" prefixes, __RPC_FAR pointer",
      " * qualifiers, glued name/type pairs (DWORDrectToActivate,",
      " * RECTlastRect, NVFOCUS_DIRECTIONdirection) -- is kept verbatim",
      " * in the records; the DeactivateRect page ms918597 misspells the",
      " * callee \"DectivateRect\"; OnRectsChange prints empty parentheses.",
      " * NVFOCUS_DIRECTION (two records pass it by value) is declared in",
      " * Mshtmhst.h per its own page ms918828.  HELD: the",
      " * OnNavigationStatusChange prose names NAV_STATUS_CANNAVIGATENOW",
      " * -- no page, no value, nowhere published.",
      " */",
      "",
      "#ifndef AKARI_MSHTML_H",
      "#define AKARI_MSHTML_H",
      "",
      '#include "Windef.h"      /* DWORD, RECT, VOID */',
      '#include "Mshtmhst.h"    /* NVFOCUS_DIRECTION (by-value records) */',
      "",
      "#ifdef __cplusplus",
      'extern "C" {',
      "#endif"]
L += [""]
L += banner("Interfaces -- opaque typedefs, methods recorded below")
L += [""]
for name, methods in MSHTML_INTERFACES:
    L += [f"/* {name} ({len(methods)} documented methods). */",
          f"typedef struct {name} {name};", ""]
L += banner("Interface method records")
L += ["/*"]
for name, methods in MSHTML_INTERFACES:
    L += [f"{name}:"]
    for pid, sig in methods:
        L += rec(pid, sig)
    L += [" *"]
L += [" */",
      "#ifdef __cplusplus",
      "}",
      "#endif",
      "",
      "#endif /* AKARI_MSHTML_H */"]
W("include/Mshtml.h", L)

# ---------------------------------------------------------------- Mshtmhst
L = []
L += ["/*",
      " * Mshtmhst.h -- Windows CE MSHTML host callbacks (Akari API).",
      " *",
      " * Copyright (c) 2026 Akari API contributors",
      " * SPDX-License-Identifier: MIT",
      " *",
      " * Written from scratch from the official Microsoft Windows CE",
      " * documentation (learn.microsoft.com previous-versions archive;",
      " * page ids cited per record).  This is the complete \"Mshtmhst.h,",
      " * Mshtmhst.idl.\" row set of the Internet Client Services book",
      " * harvest (M92/M93, tools/manifests/internetclient-book.manifest):",
      " * the NVFOCUS_DIRECTION enumeration and three host method pages.",
      " *",
      " * The three functions are host-container METHODS MSHTML calls on",
      " * the host (each page opens \"This method is called by MSHTML\",",
      " * and the GetFilename code example prints a C++ method`",
      " * MyContainer::Getfilename`) -- they are recorded, not declared,",
      " * and no Link Library row is printed on any of the three pages.",
      " */",
      "",
      "#ifndef AKARI_MSHTMHST_H",
      "#define AKARI_MSHTMHST_H",
      "",
      '#include "Windef.h"    /* BOOL, DWORD, HWND, LRESULT, RECT */',
      '#include "Objbase.h"   /* HRESULT, LPOLESTR, VARIANT */',
      "",
      "#ifdef __cplusplus",
      'extern "C" {',
      "#endif"]
L += [""]
L += banner("NVFOCUS_DIRECTION (ms918828) -- enum print with values")
L += [""]
L += ['/* ms918828 "NVFOCUS_DIRECTION": print `typedef enum',
      ' * _NvFocusDirection {FOCUS_NONE = 0,FOCUS_UP = 1,FOCUS_DOWN = 2,',
      ' * FOCUS_LEFT = 3,FOCUS_RIGHT = 4,} NVFOCUS_DIRECTION;` (trailing',
      ' * comma normalized; OS row: Windows CE .NET 4.1 and later). */']
L += ["typedef enum _NvFocusDirection {"]
for name, val in NVFOCUS:
    L += [f"    {name} = {val},"]
L += ["} NVFOCUS_DIRECTION;"]
L += [""]
L += banner("Recorded -- host methods MSHTML calls on the container")
L += [""]
for pid, name, sig in MSHTMHST_RECORDS:
    L.append(f'/* {pid} "{name}": `{sig}` */')
L += [""]
L += ["#ifdef __cplusplus",
      "}",
      "#endif",
      "",
      "#endif /* AKARI_MSHTMHST_H */"]
W("include/Mshtmhst.h", L)

# ---------------------------------------------------------------- verify
# every record id must still carry the recorded tokens in its page text
BAD = 0
for group in (UXTHEME_RECORDS, MSHTMHST_RECORDS):
    for pid, name, sig in group:
        t = page_text(pid).replace("\n", " ")
        for tok in (name, sig.split("(")[0].split()[-1]):
            if tok.replace(" ", "") not in t.replace(" ", ""):
                print(f"VERIFY FAIL {pid}: {tok!r} not in page")
                BAD += 1
for name, count, methods in WEBVW_INTERFACES:
    for pid, sig in methods:
        t = page_text(pid).replace("\n", " ").replace(" ", "")
        head = sig.split("(")[0].replace(" ", "")
        if head not in t:
            print(f"VERIFY FAIL {pid}: {head!r} not in page")
            BAD += 1
for name, methods in MSHTML_INTERFACES:
    for pid, sig in methods:
        t = page_text(pid).replace("\n", " ").replace(" ", "")
        head = sig.split("(")[0].replace(" ", "")
        if head not in t:
            print(f"VERIFY FAIL {pid}: {head!r} not in page")
            BAD += 1
print("page-text verification:", "OK" if BAD == 0 else f"{BAD} FAILURES")
