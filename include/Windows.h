/*
 * Windows.h -- umbrella header for the Akari API (Windows CE 4/5/6).
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

#include "Windef.h"
#include "Winbase.h"
/* GDI: CE 5.0 Requirement rows for the GDI Reference items list
 * "Header: Windows.h" (the CE 5.0 headers were monolithic); the items
 * live in wingdi.h -- the component header of the CE 6.0 era -- and
 * are included here so Windows.h still provides them (see wingdi.h). */
#include "Wingdi.h"
#include "Tvout.h"    /* ms914096 VIDEOPARAMETERS (Header: Tvout.h) */
#include "Winnls.h"
#include "Winreg.h"
#include "Psapi.h"
#include "Msgqueue.h"
#include "Excpt.h"
#include "Winuser.h"
/* Component headers of the CE SDK that CE applications include either
 * directly or via Windows.h: Notify.h (Notify Reference) and Shellapi.h
 * (Resources Reference items with Header: Shellapi.h). */
#include "Notify.h"
#include "Shellapi.h"
#include "winerror.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ms885217 "ExitProcess (Windows CE 5.0)" lists Header: Windows.h,
 * which is why this declaration lives here (see winbase.h for the
 * export-surface conflict note). */
AKARI_CE_IMPORT VOID ExitProcess(UINT uExitCode) AKARI_CE_NAME(ExitProcess);

/* ------------------------------------------------------------------ */
/* GWES items whose official pages give Header: Windows.h.            */
/* ------------------------------------------------------------------ */

/* Window properties (Window Properties Reference; CE .NET 4.0+;
 * Header Windows.h; Link Library Coredll.lib).  Window properties are
 * per-window data keyed by a string or atom. */
AKARI_CE_IMPORT BOOL   SetPropW(HWND hWnd, LPCTSTR lpString, HANDLE hData) AKARI_CE_NAME(SetPropW);  /* aa453647 */
#define SetProp SetPropW
AKARI_CE_IMPORT HANDLE GetPropW(HWND hWnd, LPCTSTR lpString) AKARI_CE_NAME(GetPropW);               /* aa453155 */
#define GetProp GetPropW
AKARI_CE_IMPORT HANDLE RemovePropW(HWND hWnd, LPCTSTR lpString) AKARI_CE_NAME(RemovePropW);            /* ms939781 */
#define RemoveProp RemovePropW
AKARI_CE_IMPORT int    EnumPropsExW(HWND hWnd, PROPENUMPROCEX lpEnumFunc,   /* aa453050 */
                    LPARAM lParam) AKARI_CE_NAME(EnumPropsExW);
#define EnumPropsEx EnumPropsExW

/* aa453551 "PropEnumProcEx (Windows CE 5.0)": the enumeration callback
 * prototype (typedef PROPENUMPROCEX in winuser.h). */
BOOL CALLBACK PropEnumProcEx(HWND hwnd, LPTSTR lpszString,
                             HANDLE hData, ULONG_PTR dwData);

/* Atoms (Atoms Reference; CE .NET 4.0+; Header Windows.h; Link
 * Library Coredll.lib). */
AKARI_CE_IMPORT ATOM GlobalAddAtomW(LPCTSTR lpString) AKARI_CE_NAME(GlobalAddAtomW);      /* aa453188 */
#define GlobalAddAtom GlobalAddAtomW
AKARI_CE_IMPORT ATOM GlobalDeleteAtom(ATOM nAtom) AKARI_CE_NAME(GlobalDeleteAtom);          /* aa453189 */
AKARI_CE_IMPORT ATOM GlobalFindAtomW(LPCTSTR lpString) AKARI_CE_NAME(GlobalFindAtomW);     /* aa453190 */
#define GlobalFindAtom GlobalFindAtomW

/* aa453137 "GetMessageQueueReadyTimeStamp (CE .NET 4.0+)": returns the
 * time stamp of the first message in the queue.  Header Windows.h;
 * Link Library Coredll.lib. */
AKARI_CE_IMPORT DWORD GetMessageQueueReadyTimeStamp(HWND hWnd) AKARI_CE_NAME(GetMessageQueueReadyTimeStamp);

/* ms939981 "SendMessageTimeout (Windows CE 5.0)":
 * LRESULT SendMessageTimeout(HWND, UINT, WPARAM, LPARAM, UINT, UINT,
 * PDWORD_PTR).  CE .NET 4.0+; Windows.h; Coredll.lib. */
AKARI_CE_IMPORT LRESULT SendMessageTimeout(HWND hWnd, UINT Msg, WPARAM wParam,
                            LPARAM lParam, UINT fuFlags, UINT uTimeout,
                            PDWORD_PTR lpdwResult) AKARI_CE_NAME(SendMessageTimeout);

/* ms932696 "ScrollDC (Windows CE 5.0)":
 * BOOL ScrollDC(HDC, int, int, const RECT*, const RECT*, HRGN, LPRECT).
 * CE 1.0+; Windows.h; Coredll.lib. */
AKARI_CE_IMPORT BOOL ScrollDC(HDC hDC, int dx, int dy, const RECT *lprcScroll,
              const RECT *lprcClip, HRGN hrgnUpdate, LPRECT lprcUpdate) AKARI_CE_NAME(ScrollDC);

/* M28 dialog-book items whose official pages give Header: Windows.h. */

/* ms911827 "MessageBox (Windows CE 5.0)": modal message box.  CE 1.0+;
 * Header: Windows.h; Link Library Msgbox.lib.  Windows CE supports only
 * the wide form (the repo rule for text functions); uType combines the
 * MB_* styles documented in the "Message Box Styles" book. */
AKARI_CE_IMPORT int MessageBoxW(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType) AKARI_CE_NAME(MessageBoxW);
#define MessageBox MessageBoxW

/* ms928573 "CheckDlgButton": sets the check state of a button control
 * (its official page prints an __inline prototype with Header:
 * Windows.h; Link Library Coredll.lib). */
AKARI_CE_IMPORT BOOL CheckDlgButton(HWND hDlg, int nIDButton, UINT uCheck) AKARI_CE_NAME(CheckDlgButton);

/* ms909866 "IsDlgButtonChecked": returns the check state of a button
 * (official page prints __inline UINT WINAPI ...; Header: Windows.h;
 * Link Library Coredll.lib). */
AKARI_CE_IMPORT UINT IsDlgButtonChecked(HWND hDlg, int nIDButton) AKARI_CE_NAME(IsDlgButtonChecked);

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
AKARI_CE_IMPORT BOOL SetUserDefaultLCID(LCID Locale) AKARI_CE_NAME(SetUserDefaultLCID);

/* aa453696 "SHGetAutoRunPath" (CE .NET 4.2+; Header Windows.h per the
 * page -- the AYGShell book's one Windows.h-row function; Link Library
 * aygshell.lib -> def/aygshell-doc.def).  Constructs the
 * \Storage Card\<cpu-id>\autorun.exe path of the first storage card
 * into a caller buffer of at least MAX_PATH TCHARs (the OS names the
 * subdirectory with the microprocessor ID).  The full AYGShell unit
 * lives in aygshell.h; this declaration follows its documented Header
 * row. */
AKARI_CE_IMPORT BOOL SHGetAutoRunPath(LPTSTR pAutoRunPath) AKARI_CE_NAME(SHGetAutoRunPath);

#ifdef __cplusplus
}
#endif


/* ------------------------------------------------------------------ */
/* MUI (Multilingual User Interface) and EUDC/font items whose pages   */
/* list Header: Windows.h (International / Fonts books, M83).          */
/* ------------------------------------------------------------------ */

/* ms905116 "EnumUILanguagesProc" (Coreloc.lib row on the sibling
 * pages): print `BOOL CALLBACK EnumUILanguagesProc(LPTSTR
 * lpUILanguageString);` -- the application-defined callback.  The
 * UILANGUAGE_ENUMPROC pointer typedef named by the EnumUILanguages
 * print (ms905092) is closed on this callback prototype (recorded
 * path). */
typedef BOOL (CALLBACK *UILANGUAGE_ENUMPROC)(LPTSTR lpUILanguageString);

/* ms905092 "EnumUILanguages": print `BOOL EnumUILanguages(
 * UILANGUAGE_ENUMPROC lpUILanguageEnumProc,DWORDdwFlags);` (glued
 * tokens split; Coreloc.lib). */
AKARI_CE_IMPORT BOOL EnumUILanguages(UILANGUAGE_ENUMPROC lpUILanguageEnumProc,
                    DWORD dwFlags) AKARI_CE_NAME(EnumUILanguages);

/* ms905303 "GetSystemDefaultUILanguage": print
 * `LANGID GetSystemDefaultUILanguage();` (Coreloc.lib). */
AKARI_CE_IMPORT LANGID GetSystemDefaultUILanguage(void)
                    AKARI_CE_NAME(GetSystemDefaultUILanguage);

/* ms905328 "GetUserDefaultUILanguage": print
 * `LANGID GetUserDefaultUILanguage();` (Coreloc.lib). */
AKARI_CE_IMPORT LANGID GetUserDefaultUILanguage(void)
                    AKARI_CE_NAME(GetUserDefaultUILanguage);

/* ms906280 "SetUserDefaultUILanguage": print
 * `BOOL SetUserDefaultUILanguage(LANGID langid);` (Coreloc.lib). */
AKARI_CE_IMPORT BOOL SetUserDefaultUILanguage(LANGID langid)
                    AKARI_CE_NAME(SetUserDefaultUILanguage);

/* ms901122 "EnableEUDC" (Fonts book): print `BOOL EnableEUDC(BOOL
 * fEnableEUDC);` (Coredll.lib). */
AKARI_CE_IMPORT BOOL EnableEUDC(BOOL fEnableEUDC)
                    AKARI_CE_NAME(EnableEUDC);

/* aa520324 "GetCharABCWidthsI" (Fonts book): print
 * `BOOL GetCharABCWidthsI( HDC hdc, UINT giFirst, UINT cgi, LPWORD
 * pgi, LPABC lpabc);` (Coredll.lib). */
AKARI_CE_IMPORT BOOL GetCharABCWidthsI(HDC hdc, UINT giFirst, UINT cgi,
                    LPWORD pgi, LPABC lpabc)
                    AKARI_CE_NAME(GetCharABCWidthsI);

/* ------------------------------------------------------------------
 * Book surface: fonts-book (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms901095 Changing the Font Size for the Help System */
/* ms901154 Configuring the ClearType Sample Application */
/* ms900852 Creating End User Defined Characters */
/* ms900854 Drawing and Formatting Text */
/* ms900901 Drawing Text */
/* ms901096 Enabling Antialiased Fonts */
/* ms901013 Enabling Asian Line Breaking */
/* ms901097 Enabling ClearType */
/* ms901067 Enabling EUDC */
/* ms901076 Enabling Font Linking */
/* ms901098 Enabling Linked Fonts */
/* aa520322 End User Defined Character Codepoint Ranges */
/* ms901077 Enumerating Fonts */
/* ms901078 Font Linking Registry Settings */
/* ms901079 Font Registry Settings */
/* ms901080 Font Registry Settings for Japan */
/* ms901081 Font Registry Settings for Korea */
/* ms901082 Font Registry Settings for Simplified Chinese */
/* ms901083 Font Registry Settings for Traditional Chinese */
/* ms901149 Fonts Application Development */
/* ms901084 Fonts Catalog Items */
/* ms901099 Fonts Functions */
/* ms901150 Fonts How-to Topics */
/* ms901100 Fonts Messages */
/* ms901151 Fonts Migration */
/* ms901152 Fonts OS Design Development */
/* ms901085 Fonts Overview */
/* ms901101 Fonts Reference */
/* ms901153 Fonts Samples */
/* ms901086 Fonts Security */
/* ms901102 Fonts Structures */
/* ms901088 Formatting Text */
/* ms901089 General Font Registry Settings */
/* ms901107 How to Implement ClearType */
/* ms901090 Installing and Using Fonts */
/* ms901103 Replacing Fonts */
/* ms901104 Replacing OS Design Fonts */
/* ms901105 Replacing Windows CE Default Fonts */
/* ms901155 Setting the Registry Key to Adjust Gamma Settings */
/* ms901156 Setting the Registry Key to Support ClearType */
/* ms901106 Specifying the Directory for Font Loading */
/* ms901091 System Font Registry Settings */
/* ms901092 Using Fonts */
/* ms901093 Working with ClearType Fonts */
/* ms901094 Working with TrueType and Raster Fonts */
/* ------------------------------------------------------------------
 * Book surface: graphics-book (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms932214 Multiple Screens Structures/MONITORINFOEX (Header: Windows.h.) */
/* ------------------------------------------------------------------
 * Book surface: fonts-book (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms901095 Changing the Font Size for the Help System */
/* ms901154 Configuring the ClearType Sample Application */
/* ms900852 Creating End User Defined Characters */
/* ms900854 Drawing and Formatting Text */
/* ms900901 Drawing Text */
/* ms901096 Enabling Antialiased Fonts */
/* ms901013 Enabling Asian Line Breaking */
/* ms901097 Enabling ClearType */
/* ms901067 Enabling EUDC */
/* ms901076 Enabling Font Linking */
/* ms901098 Enabling Linked Fonts */
/* aa520322 End User Defined Character Codepoint Ranges */
/* ms901077 Enumerating Fonts */
/* ms901078 Font Linking Registry Settings */
/* ms901079 Font Registry Settings */
/* ms901080 Font Registry Settings for Japan */
/* ms901081 Font Registry Settings for Korea */
/* ms901082 Font Registry Settings for Simplified Chinese */
/* ms901083 Font Registry Settings for Traditional Chinese */
/* ms901149 Fonts Application Development */
/* ms901084 Fonts Catalog Items */
/* ms901099 Fonts Functions */
/* ms901150 Fonts How-to Topics */
/* ms901100 Fonts Messages */
/* ms901151 Fonts Migration */
/* ms901152 Fonts OS Design Development */
/* ms901085 Fonts Overview */
/* ms901101 Fonts Reference */
/* ms901153 Fonts Samples */
/* ms901086 Fonts Security */
/* ms901102 Fonts Structures */
/* ms901088 Formatting Text */
/* ms901089 General Font Registry Settings */
/* ms901107 How to Implement ClearType */
/* ms901090 Installing and Using Fonts */
/* ms901103 Replacing Fonts */
/* ms901104 Replacing OS Design Fonts */
/* ms901105 Replacing Windows CE Default Fonts */
/* ms901155 Setting the Registry Key to Adjust Gamma Settings */
/* ms901156 Setting the Registry Key to Support ClearType */
/* ms901106 Specifying the Directory for Font Loading */
/* ms901091 System Font Registry Settings */
/* ms901092 Using Fonts */
/* ms901093 Working with ClearType Fonts */
/* ms901094 Working with TrueType and Raster Fonts */
/* ------------------------------------------------------------------
 * Book surface: graphics-book (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms932214 Multiple Screens Structures/MONITORINFOEX (Header: Windows.h.) */
#endif /* AKARI_WINDOWS_H */
