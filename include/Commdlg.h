/*
 * Commdlg.h -- Common Dialog Boxes API for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  Sources: CE 5.0 "Shell and User Interface :: Shell :: Common
 * Controls Reference :: Common Dialog Boxes Reference" (the 24 leaves of
 * tools/manifests/cc-commdlg.manifest, fetched M54) plus the M53
 * WM_CHOOSEFONT_GETLOGFONT page; prototypes were cross-read against the
 * CE 6.0 (v=winembedded.60) twins (tools/manifests/m54-ce60.manifest).
 *
 * Requirement rows: ChooseColor / CommDlgExtendedError / PageSetupDlg /
 * PrintDlg print "Link Library: Commdlg.lib" and GetOpenFileName /
 * GetSaveFileName print "Fileopen.lib" (see def/commdlg-doc.def and
 * def/fileopen-doc.def); the hook-procedure pages carry no library row
 * (application-implemented callbacks).  ChooseFont (ms928581) carries
 * no Link Library row on its CE page, so it generates no def entry.
 *
 * The flag families (CC_*, CF_* and the *_FONTTYPE codes, OFN_*,
 * PD_*, PSD_*, the CDERR and PDERR error codes, WM_PSD_* and the
 * CDM/CDN items) are published
 * as names without numeric values and stay held (ledger in
 * docs/inventory.md M54).
 */

#ifndef AKARI_COMMDLG_H
#define AKARI_COMMDLG_H

#include "Windef.h"
#include "Wingdi.h"   /* COLORREF, LOGFONT (M54) */
#include "Winuser.h"  /* WM_USER, NMHDR */

#ifdef __cplusplus
extern "C" {
#endif

/* ms914112 "WM_CHOOSEFONT_GETLOGFONT" (Windows CE .NET 4.0 and later;
 * Commdlg.h).  Sent to the open Font dialog box (SendMessage) to
 * retrieve the current font selections into the lParam LOGFONT
 * structure while the dialog is open; wParam is unused and must be
 * zero.  The CE page publishes the name without a value; the desktop
 * Win32 reference page prints the formula
 * "#define WM_CHOOSEFONT_GETLOGFONT (WM_USER + 1)", and WM_USER
 * (0x0400) is CE-published (winuser.h), so the derived value below
 * follows the M52 derived-value policy (path recorded in
 * docs/inventory.md M53).  Note the published formula lands on the
 * same 0x0401 value as DM_SETDEFID (aa452963, winuser.h) -- both
 * desktop pages print (WM_USER + 1); the shared value is the
 * documented ABI, kept verbatim. */
#define WM_CHOOSEFONT_GETLOGFONT  (WM_USER + 1)

/* ------------------------------------------------------------------ */
/* Hook procedures (application-implemented; no Link Library rows).    */
/* The pointer typedefs the structures type their lpfn* members with   */
/* are built from the documented hook signatures -- the M51            */
/* IMENUMPROC model -- except LPCFHOOKPROC, which the CFHookProc page  */
/* prints directly.                                                    */
/* ------------------------------------------------------------------ */

/* ms908071 "CCHookProc": "UINT APIENTRY CCHookProc(HWND hdlg, UINT
 * uiMsg, WPARAM wParam, LPARAM lParam);". */
typedef UINT (CALLBACK *LPCCHOOKPROC)(HWND hdlg, UINT uiMsg,
                                      WPARAM wParam, LPARAM lParam);

/* ms908107 "CFHookProc": page prints
 * "UINT (APIENTRY* LPCFHOOKPROC)(HWND hdlg, UINT uiMsg, WPARAM wParam,
 * LPARAM lParam);" verbatim. */
typedef UINT (CALLBACK *LPCFHOOKPROC)(HWND hdlg, UINT uiMsg,
                                      WPARAM wParam, LPARAM lParam);

/* ms911908 "PagePaintHook": "UINT CALLBACK PagePaintHook(HWND hdlg,
 * UINT uiMsg, WPARAM wParam, LPARAM lParam);". */
typedef UINT (CALLBACK *LPPAGEPAINTHOOK)(HWND hdlg, UINT uiMsg,
                                         WPARAM wParam, LPARAM lParam);

/* ms911911 "PageSetupHook": "UINT CALLBACK PageSetupHook(HWND hdlg,
 * UINT uiMsg, WPARAM wParam, LPARAM lParam);". */
typedef UINT (CALLBACK *LPPAGESETUPHOOK)(HWND hdlg, UINT uiMsg,
                                         WPARAM wParam, LPARAM lParam);

/* aa453545 "PrintHookProc": "UINT APIENTRY PrintHookProc(HWND hdlg,
 * UINT uiMsg, WPARAM wParam, LPARAM lParam );". */
typedef UINT (CALLBACK *LPPRINTHOOKPROC)(HWND hdlg, UINT uiMsg,
                                         WPARAM wParam, LPARAM lParam);

/* ------------------------------------------------------------------ */
/* Structures.                                                         */
/* ------------------------------------------------------------------ */

/* ms928580 "CHOOSECOLOR" (CE 2.0+): printed layout
 * "typedef struct tagCHOOSECOLOR {DWORD lStructSize; HWND hwndOwner;
 * HINSTANCE hInstance; COLORREF rgbResult; COLORREF* lpCustColors;
 * DWORD Flags; LPARAM lCustData; LPCCHOOKPROC lpfnHook; LPCTSTR
 * lpTemplateName;} CHOOSECOLOR, *LPCHOOSECOLOR;".  32-bit size 36,
 * TU-asserted. */
typedef struct tagCHOOSECOLOR {
    DWORD         lStructSize;
    HWND          hwndOwner;
    HINSTANCE     hInstance;
    COLORREF      rgbResult;
    COLORREF     *lpCustColors;
    DWORD         Flags;
    LPARAM        lCustData;
    LPCCHOOKPROC  lpfnHook;
    LPCTSTR       lpTemplateName;
} CHOOSECOLOR, *LPCHOOSECOLOR;

/* wingdi.h bridge: the CHOOSEFONT page types the member LPLOGFONTW;
 * the CE LOGFONT page (ms901140, wingdi.h) defines the TCHAR form. */
typedef LOGFONT  LOGFONTW;
typedef LOGFONT *LPLOGFONTW;

/* ms928582 "CHOOSEFONT" (CE 2.0+): printed layout
 * "typedef struct tagCHOOSEFONT {DWORD lStructSize; HWND hwndOwner;
 * HDC hDC; LPLOGFONTW lpLogFont; INT iPointSize; DWORD Flags;
 * COLORREF rgbColors; LPARAM lCustData; LPCFHOOKPROC lpfnHook;
 * LPCWSTR lpTemplateName; HINSTANCE hInstance; LPWSTR lpszStyle;
 * WORD nFontType; WORD ___MISSING_ALIGNMENT__; INT nSizeMin;
 * INT nSizeMax;} CHOOSEFONTW, *LPCHOOSEFONTW;" -- the placeholder
 * member name ___MISSING_ALIGNMENT__ is printed verbatim [sic].  The
 * ChooseFont function page (ms928581) types its parameter
 * "LPCHOOSEFONT", so the unsuffixed alias is added below (both
 * spellings appear in the book); the member is printed LPLOGFONTW
 * while the CE LOGFONT page (ms901140, wingdi.h) defines the TCHAR
 * (=WCHAR on CE) form named LOGFONT, so the W alias is bridged here.
 * 32-bit size 60, TU-asserted. */
typedef struct tagCHOOSEFONT {
    DWORD         lStructSize;
    HWND          hwndOwner;
    HDC           hDC;
    LPLOGFONTW    lpLogFont;
    INT           iPointSize;
    DWORD         Flags;
    COLORREF      rgbColors;
    LPARAM        lCustData;
    LPCFHOOKPROC  lpfnHook;
    LPCWSTR       lpTemplateName;
    HINSTANCE     hInstance;
    LPWSTR        lpszStyle;
    WORD          nFontType;
    WORD          ___MISSING_ALIGNMENT__;
    INT           nSizeMin;
    INT           nSizeMax;
} CHOOSEFONTW, *LPCHOOSEFONTW;
typedef CHOOSEFONTW  CHOOSEFONT;
typedef LPCHOOSEFONTW LPCHOOSEFONT;

/* aa452944 "DEVNAMES" (CE 2.0+): "typedef struct tagDEVNAMES {
 * WORD wDriverOffset; WORD wDeviceOffset; WORD wOutputOffset;
 * WORD wDefault; } DEVNAMES;".  32-bit size 8, TU-asserted. */
typedef struct tagDEVNAMES {
    WORD   wDriverOffset;
    WORD   wDeviceOffset;
    WORD   wOutputOffset;
    WORD   wDefault;
} DEVNAMES;

/* ms911906 "OPENFILENAME" (CE 1.0+): the CE page prints the ANSI-
 * spelled string members verbatim (LPCSTR/LPSTR -- kept as printed);
 * "typedef struct tagOFN {DWORD lStructSize; HWND hwndOwner;
 * HINSTANCE hInstance; LPCSTR lpstrFilter; LPSTR lpstrCustomFilter;
 * DWORD nMaxCustFilter; DWORD nFilterIndex; LPSTR lpstrFile;
 * DWORD nMaxFile; LPSTR lpstrFileTitle; DWORD nMaxFileTitle;
 * LPSTR lpstrInitialDir; LPCSTR lpstrTitle; DWORD Flags;
 * WORD nFileOffset; WORD nFileExtension; LPCSTR lpstrDefExt;
 * DWORD lCustData; LPOFNHOOKPROC lpfnHook; LPCSTR lpTemplateName;}
 * OPENFILENAME;".  lpfnHook is printed LPOFNHOOKPROC but no CE page
 * defines that type and the OFN_ENABLEHOOK flag row is "Not
 * supported" -- typed as a layout-neutral void* with the print
 * recorded.  32-bit size 76, TU-asserted. */
typedef struct tagOFN {
    DWORD    lStructSize;
    HWND     hwndOwner;
    HINSTANCE hInstance;
    LPCSTR   lpstrFilter;
    LPSTR    lpstrCustomFilter;
    DWORD    nMaxCustFilter;
    DWORD    nFilterIndex;
    LPSTR    lpstrFile;
    DWORD    nMaxFile;
    LPSTR    lpstrFileTitle;
    DWORD    nMaxFileTitle;
    LPSTR    lpstrInitialDir;
    LPCSTR   lpstrTitle;
    DWORD    Flags;
    WORD     nFileOffset;
    WORD     nFileExtension;
    LPCSTR   lpstrDefExt;
    DWORD    lCustData;
    void    *lpfnHook;      /* printed LPOFNHOOKPROC; no CE page */
    LPCSTR   lpTemplateName;
} OPENFILENAME, *LPOPENFILENAME;

/* ms911893 "OFNOTIFY" (CE .NET 4.0+): "typedef struct _OFNOTIFY {
 * NMHDR hdr; LPOPENFILENAME lpOFN; LPTSTR pszFile;} OFNOTIFY, FAR*
 * LPOFNOTIFY;".  32-bit size 20, TU-asserted. */
typedef struct _OFNOTIFY {
    NMHDR          hdr;
    LPOPENFILENAME lpOFN;
    LPTSTR         pszFile;
} OFNOTIFY, *LPOFNOTIFY;

/* ms911910 "PAGESETUPDLG" (CE 2.10+): "typedef struct tagPSD {
 * DWORD lStructSize; HWND hwndOwner; HGLOBAL hDevMode; HGLOBAL
 * hDevNames; DWORD Flags; POINT ptPaperSize; RECT rtMinMargin;
 * RECT rtMargin; HINSTANCE hInstance; LPARAM lCustData;
 * LPPAGESETUPHOOK lpfnPageSetupHook; LPPAGEPAINTHOOK
 * lpfnPagePaintHook; LPCTSTR lpPageSetupTemplateName; HGLOBAL
 * hPageSetupTemplate; } PAGESETUPDLG, *LPPAGESETUPDLG;".
 * 32-bit size 84, TU-asserted. */
typedef struct tagPSD {
    DWORD            lStructSize;
    HWND             hwndOwner;
    HGLOBAL          hDevMode;
    HGLOBAL          hDevNames;
    DWORD            Flags;
    POINT            ptPaperSize;
    RECT             rtMinMargin;
    RECT             rtMargin;
    HINSTANCE        hInstance;
    LPARAM           lCustData;
    LPPAGESETUPHOOK  lpfnPageSetupHook;
    LPPAGEPAINTHOOK  lpfnPagePaintHook;
    LPCTSTR          lpPageSetupTemplateName;
    HGLOBAL          hPageSetupTemplate;
} PAGESETUPDLG, *LPPAGESETUPDLG;

/* aa453544 "PRINTDLG" (CE 2.0 and 2.01 only -- the page's OS Versions
 * row reads "Windows CE 2.0 and 2.01", i.e. dropped after 2.01): the
 * CE layout differs from the desktop one and is printed verbatim:
 * "typedef struct tagPD {DWORD cbStruct; HWND hwndOwner; HDC hdc;
 * DWORD dwFlags; RECT rcMinMargin; RECT rcMargin; HINSTANCE hinst;
 * LPARAM lCustData; LPPRINTHOOKPROC pfnPrintHook; LPCTSTR
 * pszPrintTemplateName; HGLOBAL hglbPrintTemplateResource;}
 * PRINTDLG , *LPPRINTDLG;".  32-bit size 68, TU-asserted. */
typedef struct tagPD {
    DWORD            cbStruct;
    HWND             hwndOwner;
    HDC              hdc;
    DWORD            dwFlags;
    RECT             rcMinMargin;
    RECT             rcMargin;
    HINSTANCE        hinst;
    LPARAM           lCustData;
    LPPRINTHOOKPROC  pfnPrintHook;
    LPCTSTR          pszPrintTemplateName;
    HGLOBAL          hglbPrintTemplateResource;
} PRINTDLG, *LPPRINTDLG;

/* ------------------------------------------------------------------ */
/* Functions.                                                          */
/* ------------------------------------------------------------------ */

/* ms928579 "ChooseColor" (CE 2.0+; Commdlg.lib): the page prints no
 * prototype block; the documented signature is
 * "BOOL ChooseColor(LPCHOOSECOLOR lpcc);". */
AKARI_CE_IMPORT BOOL     ChooseColor(LPCHOOSECOLOR lpcc) AKARI_CE_NAME(ChooseColor);                    /* ms928579 */

/* ms928581 "ChooseFont" (CE 2.0+; no Link Library row on the CE page):
 * "BOOL APIENTRY ChooseFont(LPCHOOSEFONT lpcf);" (APIENTRY is empty
 * on CE, see windef.h). */
BOOL     ChooseFont(LPCHOOSEFONT lpcf);                      /* ms928581 */

/* ms908144 "CommDlgExtendedError" (CE 2.0+; Commdlg.lib):
 * "DWORD CommDlgExtendedError()". */
AKARI_CE_IMPORT DWORD    CommDlgExtendedError(void) AKARI_CE_NAME(CommDlgExtendedError);                         /* ms908144 */

/* aa453150 "GetOpenFileName" (CE 1.0+; Fileopen.lib): the page prints
 * no prototype block; the documented signature is
 * "BOOL GetOpenFileName(LPOPENFILENAME lpofn);". */
AKARI_CE_IMPORT BOOL     GetOpenFileName(LPOPENFILENAME lpofn) AKARI_CE_NAME(GetOpenFileName);              /* aa453150 */

/* aa453162 "GetSaveFileName" (CE 1.0+; Fileopen.lib):
 * "BOOL GetSaveFileName(LPOPENFILENAME lpofn);". */
AKARI_CE_IMPORT BOOL     GetSaveFileName(LPOPENFILENAME lpofn) AKARI_CE_NAME(GetSaveFileName);              /* aa453162 */

/* ms911909 "PageSetupDlg" (CE 2.10+; Commdlg.lib):
 * "BOOL PageSetupDlg(LPPAGESETUPDLG lppsd);". */
AKARI_CE_IMPORT BOOL     PageSetupDlg(LPPAGESETUPDLG lppsd) AKARI_CE_NAME(PageSetupDlg);                 /* ms911909 */

/* ms911940 "PrintDlg" (CE 2.0 and 2.01; Commdlg.lib):
 * "BOOL PrintDlg(LPPRINTDLG lppd);". */
AKARI_CE_IMPORT BOOL     PrintDlg(LPPRINTDLG lppd) AKARI_CE_NAME(PrintDlg);                          /* ms911940 */

/* Hook procedure types (declared as the documented callback forms;
 * APIENTRY/CALLBACK are empty on CE, see windef.h). */
UINT     APIENTRY CCHookProc(HWND hdlg, UINT uiMsg,
                             WPARAM wParam, LPARAM lParam);  /* ms908071 */
UINT     CALLBACK PagePaintHook(HWND hdlg, UINT uiMsg,
                                WPARAM wParam, LPARAM lParam); /* ms911908 */
UINT     CALLBACK PageSetupHook(HWND hdlg, UINT uiMsg,
                                WPARAM wParam, LPARAM lParam); /* ms911911 */
UINT     APIENTRY PrintHookProc(HWND hdlg, UINT uiMsg,
                                WPARAM wParam, LPARAM lParam); /* aa453545 */

/* HELD (names without values, see docs/inventory.md M54): the CC_*,
 * CF_* / *_FONTTYPE, OFN_*, PD_*, PSD_* flag families, the CDERR_* /
 * PDERR_* CommDlgExtendedError codes, WM_PSD_* hook messages
 * (ms911908), CDM_SETDEFEXT (ms908072) and CDN_TYPECHANGE
 * (ms908073; its LPOFNOTIFY lParam form is recorded above). */

/* aa452636 "DrvAdvPageSetupDlg" (CE .NET 4.0+): `BOOL
 * DrvAdvPageSetupDlg(LPPAGESETUPDLG lppsd,HWND hwndDlg);` -- RECORDED,
 * not declared: the page's Remarks say "You should implement this
 * function in the printer driver" (the Page Setup dialog invokes it
 * when the user chooses Advanced); the page prints no Link Library
 * row, so there is no doc-derived def entry either. */

/* ------------------------------------------------------------------
 * Book surface: cc-commdlg (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms907541 Common Dialog Boxes Functions */
/* ms907548 Common Dialog Boxes Messages */
/* ms907558 Common Dialog Boxes Structures */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_COMMDLG_H */
