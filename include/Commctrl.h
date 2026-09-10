/*
 * Commctrl.h -- Common Controls API for Windows CE (GWES; Image List
 *               book M29 + Common Controls Reference batch 1 M54).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  The M29 Image List Functions / Macros / Structures books and the
 * M54 Common Controls Reference batch (Animation, CapEdit, Command Bands,
 * Command Bars, Common Control, Custom Draw, Progress, SbEdit, Status
 * Bars, Toolbar, ToolTips, Trackbar, Up-Down sub-books) are the source
 * books; function signatures were recovered from the official CE 6.0
 * (v=winembedded.60) twins of the same books, which publish
 * whitespace-preserved prototypes (the CE 5.0 migration strips code
 * spacing; the twin id is noted per declaration).
 *
 * Requirement rows: Header: Commctrl.h for every page; Link Library rows
 * read "Commctrl.lib, Imgctl.lib." for the image-list functions,
 * "Commctrl.lib." for the command-bar/bands, status-bar and
 * InitCommonControls* functions, and are absent for the macro/struct/
 * message pages -- see def/commctrl-doc.def and def/imgctl-doc.def
 * for the export rows that follow those documented tokens.
 *
 * Windows CE functions are __cdecl; the WINAPI/CALLBACK decorations the
 * migrated pages sometimes print are empty on CE (see windef.h).
 */

#ifndef AKARI_COMMCTRL_H
#define AKARI_COMMCTRL_H

/* Like the CE SDK (where applications include Commctrl.h after
 * Windows.h), this header builds on the GWES umbrella: it needs the
 * Winuser.h image-type constants (IMAGE_BITMAP, used by the
 * ImageList_LoadBitmap macro), the notification header (NMHDR, the
 * M50 winuser.h declaration) and the windef/wingdi handle types.
 * The includes below make the header self-sufficient for the
 * standalone crosscheck. */
#include "Windef.h"
#include "Wingdi.h"   /* COLORREF, RECT via windef; HDC/HBITMAP/HICON */
#include "Winuser.h"  /* NMHDR (ms931479), HMENU, WM_NOTIFY, WINDOWPOS */
#include "Winbase.h"  /* SYSTEMTIME (aa450923; M56 DTPicker/MonthCal) */

#ifdef __cplusplus
extern "C" {
#endif

/* Image-list handle.  CE pages type every function with HIMAGELIST but
 * do not republish a typedef; it is an opaque handle like the other
 * GDI/GWES handles (fixed Win32 ABI). */
typedef void *HIMAGELIST;

/* ------------------------------------------------------------------ */
/* Image List Structures.                                             */
/* ------------------------------------------------------------------ */

/* ms909781 "IMAGEINFO": information about an image in an image list
 * (ImageList_GetImageInfo).  CE 1.0+; Commctrl.h. */
typedef struct _IMAGEINFO {
    HBITMAP hbmImage;   /* bitmap containing the images */
    HBITMAP hbmMask;    /* mask bitmap, or NULL if the list has no mask */
    int     Unused1;    /* not used; set to zero */
    int     Unused2;    /* not used; set to zero */
    RECT    rcImage;    /* bounding rectangle of the image in hbmImage */
} IMAGEINFO, *LPIMAGEINFO;

/* ms909819 "IMAGELISTDRAWPARAMS": parameters for ImageList_DrawIndirect.
 * CE 2.0+; Commctrl.h. */
typedef struct _IMAGELISTDRAWPARAMS {
    DWORD      cbSize;    /* sizeof(IMAGELISTDRAWPARAMS) */
    HIMAGELIST himl;
    int        i;         /* zero-based image index */
    HDC        hdcDst;
    int        x;         /* destination coordinates */
    int        y;
    int        cx;        /* pixels drawn (0 = entire valid section) */
    int        cy;
    int        xBitmap;   /* upper-left of the drawing within the image */
    int        yBitmap;
    COLORREF   rgbBk;     /* image-list background color */
    COLORREF   rgbFg;     /* foreground blend color (ILD_BLEND* styles) */
    UINT       fStyle;    /* ILD_* drawing styles + overlay index */
    DWORD      dwRop;     /* raster operation for ILD_ROP */
} IMAGELISTDRAWPARAMS, *LPIMAGELISTDRAWPARAMS;

/* ------------------------------------------------------------------ */
/* Image list creation flags (ImageList_Create "flags" parameter; the  */
/* ILC_* names are listed on ms909810).  Numeric values are the fixed  */
/* Win32 ABI values (CE GWES implements the same image-list protocol). */
/* ------------------------------------------------------------------ */
#define ILC_MASK      0x0001
#define ILC_COLOR     0x0000   /* default: ILC_COLOR4 or ILC_COLORDDB */
#define ILC_COLOR4    0x0004
#define ILC_COLOR8    0x0008
#define ILC_COLOR16   0x0010
#define ILC_COLOR24   0x0018
#define ILC_COLOR32   0x0020
#define ILC_COLORDDB  0x00FE
#define ILC_MIRROR    0x2000   /* CE mirrored display: do not mirror */

/* Drawing styles (ImageList_Draw/DrawEx fStyle; names on ms909816). */
#define ILD_NORMAL    0x0000
#define ILD_TRANSPARENT 0x0001
#define ILD_BLEND25   0x0002
#define ILD_FOCUS     ILD_BLEND25
#define ILD_BLEND50   0x0004
#define ILD_SELECTED  ILD_BLEND50
#define ILD_BLEND     ILD_BLEND50
#define ILD_MASK      0x0010
#define ILD_IMAGE     0x0020
#define ILD_ROP       0x0040
#define ILD_OVERLAYMASK 0x0F00

/* CLR_NONE selects transparent drawing via the mask (ms909836). */
#define CLR_NONE      0xFFFFFFFF
#define CLR_DEFAULT   0xFF000000

/* ------------------------------------------------------------------ */
/* Image List functions (Header Commctrl.h; Link Library rows          */
/* "Commctrl.lib, Imgctl.lib.").                                       */
/* ------------------------------------------------------------------ */

AKARI_CE_IMPORT int      ImageList_Add(HIMAGELIST himl, HBITMAP hbmImage,     /* ms909786 */
                       HBITMAP hbmMask) AKARI_CE_NAME(ImageList_Add);
AKARI_CE_IMPORT int      ImageList_AddMasked(HIMAGELIST himl, HBITMAP hbmImage,
                             COLORREF crMask) AKARI_CE_NAME(ImageList_AddMasked);                 /* ms909795 */
AKARI_CE_IMPORT BOOL     ImageList_BeginDrag(HIMAGELIST himlTrack, int iTrack,
                             int dxHotspot, int dyHotspot) AKARI_CE_NAME(ImageList_BeginDrag);    /* ms909799 */
AKARI_CE_IMPORT BOOL     ImageList_Copy(HIMAGELIST himlDst, int iDst,
                        HIMAGELIST himlSrc, int iSrc,
                        UINT uFlags) AKARI_CE_NAME(ImageList_Copy);                          /* ms909805 */
AKARI_CE_IMPORT HIMAGELIST ImageList_Create(int cx, int cy, UINT flags,
                            int cInitial, int cGrow) AKARI_CE_NAME(ImageList_Create);          /* ms909810 */
BOOL     ImageList_Destroy(HIMAGELIST himl);                   /* ms909811 */
AKARI_CE_IMPORT BOOL     ImageList_DragEnter(HWND hwndLock, int x, int y) AKARI_CE_NAME(ImageList_DragEnter);     /* ms909812 */
AKARI_CE_IMPORT BOOL     ImageList_DragLeave(HWND hwndLock) AKARI_CE_NAME(ImageList_DragLeave);                   /* ms909813 */
AKARI_CE_IMPORT BOOL     ImageList_DragMove(int x, int y) AKARI_CE_NAME(ImageList_DragMove);                     /* ms909814 */
AKARI_CE_IMPORT BOOL     ImageList_DragShowNolock(BOOL fShow) AKARI_CE_NAME(ImageList_DragShowNolock);                 /* ms909815 */
AKARI_CE_IMPORT BOOL     ImageList_Draw(HIMAGELIST himl, int i, HDC hdcDst,    /* ms909816 */
                        int x, int y, UINT fStyle) AKARI_CE_NAME(ImageList_Draw);
AKARI_CE_IMPORT BOOL     ImageList_DrawEx(HIMAGELIST himl, int i, HDC hdcDst,  /* ms909817 */
                          int x, int y, int dx, int dy,
                          COLORREF rgbBk, COLORREF rgbFg,
                          UINT fStyle) AKARI_CE_NAME(ImageList_DrawEx);
AKARI_CE_IMPORT BOOL     ImageList_DrawIndirect(IMAGELISTDRAWPARAMS *pimldp) AKARI_CE_NAME(ImageList_DrawIndirect);  /* ms909818 */
AKARI_CE_IMPORT HIMAGELIST ImageList_Duplicate(HIMAGELIST himl) AKARI_CE_NAME(ImageList_Duplicate);               /* ms909820 */
AKARI_CE_IMPORT BOOL     ImageList_EndDrag(void) AKARI_CE_NAME(ImageList_EndDrag);                              /* ms909821 */
AKARI_CE_IMPORT COLORREF ImageList_GetBkColor(HIMAGELIST himl) AKARI_CE_NAME(ImageList_GetBkColor);                /* ms909823 */
AKARI_CE_IMPORT HIMAGELIST ImageList_GetDragImage(POINT *ppt, POINT *pptHotspot) AKARI_CE_NAME(ImageList_GetDragImage); /* ms909824 */
AKARI_CE_IMPORT HICON    ImageList_GetIcon(HIMAGELIST himl, int i, UINT flags) AKARI_CE_NAME(ImageList_GetIcon); /* ms909825 */
AKARI_CE_IMPORT BOOL     ImageList_GetIconSize(HIMAGELIST himl, int *cx,
                               int *cy) AKARI_CE_NAME(ImageList_GetIconSize);                       /* ms909826 */
AKARI_CE_IMPORT int      ImageList_GetImageCount(HIMAGELIST himl) AKARI_CE_NAME(ImageList_GetImageCount);             /* ms909827 */
AKARI_CE_IMPORT BOOL     ImageList_GetImageInfo(HIMAGELIST himl, int i,
                                IMAGEINFO *pImageInfo) AKARI_CE_NAME(ImageList_GetImageInfo);        /* ms909828 */
AKARI_CE_IMPORT HIMAGELIST ImageList_LoadImage(HINSTANCE hi, LPCSTR lpbmp,     /* ms909830 */
                               int cx, int cGrow, COLORREF crMask,
                               UINT uType, UINT uFlags) AKARI_CE_NAME(ImageList_LoadImage);
AKARI_CE_IMPORT HIMAGELIST ImageList_Merge(HIMAGELIST himl1, int i1,           /* ms909831 */
                           HIMAGELIST himl2, int i2, int dx, int dy) AKARI_CE_NAME(ImageList_Merge);
AKARI_CE_IMPORT BOOL     ImageList_Remove(HIMAGELIST himl, int i) AKARI_CE_NAME(ImageList_Remove);             /* ms909832 */
AKARI_CE_IMPORT BOOL     ImageList_RemoveAll(HIMAGELIST himl) AKARI_CE_NAME(ImageList_RemoveAll);                 /* ms909833 */
AKARI_CE_IMPORT BOOL     ImageList_Replace(HIMAGELIST himl, int i,             /* ms909834 */
                           HBITMAP hbmImage, HBITMAP hbmMask) AKARI_CE_NAME(ImageList_Replace);
AKARI_CE_IMPORT int      ImageList_ReplaceIcon(HIMAGELIST himl, int i,         /* ms909835 */
                               HICON hicon) AKARI_CE_NAME(ImageList_ReplaceIcon);
AKARI_CE_IMPORT COLORREF ImageList_SetBkColor(HIMAGELIST himl, COLORREF clrBk) AKARI_CE_NAME(ImageList_SetBkColor); /* ms909836 */
AKARI_CE_IMPORT BOOL     ImageList_SetDragCursorImage(HIMAGELIST himlDrag,     /* ms909837 */
                                      int iDrag, int dxHotspot,
                                      int dyHotspot) AKARI_CE_NAME(ImageList_SetDragCursorImage);
AKARI_CE_IMPORT BOOL     ImageList_SetIconSize(HIMAGELIST himl, int cx, int cy) AKARI_CE_NAME(ImageList_SetIconSize); /* ms909838 */
AKARI_CE_IMPORT BOOL     ImageList_SetImageCount(HIMAGELIST himl,              /* ms909839 */
                                 UINT uNewCount) AKARI_CE_NAME(ImageList_SetImageCount);
AKARI_CE_IMPORT BOOL     ImageList_SetOverlayImage(HIMAGELIST himl, int iImage,
                                   int iOverlay) AKARI_CE_NAME(ImageList_SetOverlayImage);              /* ms909840 */

/* ------------------------------------------------------------------ */
/* Image List Macros (Header Commctrl.h; no Link Library row).         */
/* ------------------------------------------------------------------ */

/* ms909790 "ImageList_AddIcon": macro body per the CE 5.0 page.  (-1
 * appends the icon at the end of the list.) */
#define ImageList_AddIcon(himl, hicon) ImageList_ReplaceIcon((himl), -1, (hicon))

/* ms909843 "INDEXTOOVERLAYMASK": prepares an overlay-mask index for
 * ImageList_Draw/DrawEx (macro body per the CE 5.0 page). */
#define INDEXTOOVERLAYMASK(i) ((i) << 8)

/* ms909829 "ImageList_LoadBitmap": the CE 5.0 page documents this as a
 * macro that calls ImageList_LoadImage for a bitmap resource (uType =
 * IMAGE_BITMAP, uFlags = 0; fixed Win32-ABI macro shape). */
#define ImageList_LoadBitmap(hi, lpbmp, cx, cGrow, crMask) \
    ImageList_LoadImage((hi), (lpbmp), (cx), (cGrow), (crMask), \
                        IMAGE_BITMAP, 0)

/* ms909822 "ImageList_ExtractIcon": the CE 5.0 page states the macro
 * calls ImageList_GetIcon to create an icon from an image and mask
 * (fixed Win32-ABI macro shape; hi is unused on CE). */
#define ImageList_ExtractIcon(hi, himl, i) ImageList_GetIcon((himl), (i), 0)

/* ------------------------------------------------------------------ */
/* Shell API Notifications (M53 supplement).                           */
/* ------------------------------------------------------------------ */

/* NM_RECOGNIZEGESTURE (Windows Mobile 6.5 documentation, "Shell API
 * Notifications > NM_RECOGNIZEGESTURE" page, preserved in the corpus
 * pageswm/ tree; Requirements: Header commctrl.h, Windows CE .NET 4.2
 * and later -- no Link Library row, it is a notification, not a
 * function).  WM_NOTIFY-carried notification used to let an
 * application decide whether it wants automatic gesture recognition in
 * the common controls (list views, tree views):
 *
 *     nmrgi = (NMRGINFO*) lParam
 *
 * The parent must return TRUE if it does NOT want gesture recognition;
 * otherwise the gesture is recognized, the animation is shown and the
 * context menu messages (GN_CONTEXTMENU, WM_CONTEXTMENU) are sent to
 * the parent.  The notification value is not published on any official
 * page (no CE 5.0/6.0/Compact 7/Compact 2013 page exists for it --
 * verified against the embedded TOC and catalogs -- and the WM 6.5
 * page is names-only): name held (docs/inventory.md M53).  NMRGINFO
 * is declared in aygshell.h (its documented home). */

/* ================================================================== */
/* M54: Common Controls Reference, batch 1 (the Animation, CapEdit,    */
/* Command Bands, Command Bars, Common Control, Custom Draw,          */
/* Progress, SbEdit, Status Bars, Toolbar, ToolTips, Trackbar and      */
/* Up-Down sub-books + the Rebar REBARBANDINFO dependency;            */
/* tools/manifests/cc-*.manifest).  Prototypes were cross-read        */
/* against the CE 6.0 (v=winembedded.60) twins                        */
/* (tools/manifests/m54-ce60.manifest).  The control messages,        */
/* notifications, styles and flag families are published as names     */
/* without numeric values and stay held (grouped ledger at the end    */
/* of this section; full accounting in docs/inventory.md M54).        */
/* ================================================================== */

/* ------------------------------------------------------------------ */
/* Class names (published as string literals on the control pages).    */
/* ------------------------------------------------------------------ */

/* aa452920 "CAPEDIT Control": "#define WC_CAPEDIT L"CAPEDIT"". */
#define WC_CAPEDIT  L"CAPEDIT"

/* ms939903 "SBEDIT Control": "#define WC_SBEDIT L"sbedit"". */
#define WC_SBEDIT   L"sbedit"

/* ------------------------------------------------------------------ */
/* Common Control structures (shared sub-book + control books).        */
/* ------------------------------------------------------------------ */

/* ms909850 "INITCOMMONCONTROLSEX" (CE 2.0+): "typedef struct
 * tagINITCOMMONCONTROLSEX {DWORD dwSize; DWORD dwICC;}
 * INITCOMMONCONTROLSEX, *LPINITCOMMONCONTROLSEX;".  dwICC takes the
 * ICC_* class flags (names published on the page, values held).
 * 32-bit size 8, TU-asserted. */
typedef struct tagINITCOMMONCONTROLSEX {
    DWORD    dwSize;
    DWORD    dwICC;
} INITCOMMONCONTROLSEX, *LPINITCOMMONCONTROLSEX;

/* ms931482 "NMKEY" (CE .NET 4.0+): "typedef struct tagNMKEY {NMHDR
 * hdr; WORD wVKey; UINT flags;} NMKEY, FAR* LPNMKEY;".
 * 32-bit size 20, TU-asserted. */
typedef struct tagNMKEY {
    NMHDR    hdr;
    WORD     wVKey;
    UINT     flags;
} NMKEY, FAR *LPNMKEY;

/* ms931655 "NMMOUSE" (CE .NET 4.0+): "typedef struct tagNMMOUSE
 * {NMHDR hdr; DWORD dwItemSpec; DWORD dwItemData; POINT pt;} NMMOUSE,
 * FAR* LPNMMOUSE;".  32-bit size 28, TU-asserted. */
typedef struct tagNMMOUSE {
    NMHDR    hdr;
    DWORD    dwItemSpec;
    DWORD    dwItemData;
    POINT    pt;
} NMMOUSE, FAR *LPNMMOUSE;

/* ms931470 "NMCUSTOMDRAW" (Custom Draw Structures, CE .NET 4.0+):
 * "typedef struct tagNMCUSTOMDRAWINFO {NMHDR hdr; DWORD dwDrawStage;
 * HDC hdc; RECT rc; DWORD dwItemSpec; UINT uItemState; LPARAM
 * lItemlParam} NMCUSTOMDRAW, FAR* LPNMCUSTOMDRAW;" -- the last member
 * name is printed "lItemlParam" [sic] and the closing member has no
 * semicolon on the page; both kept as printed.  dwDrawStage takes the
 * CDDS_* stages, uItemState the CDIS_* states (names published on the
 * page, values held).  32-bit size 48, TU-asserted. */
typedef struct tagNMCUSTOMDRAWINFO {
    NMHDR    hdr;
    DWORD    dwDrawStage;
    HDC      hdc;
    RECT     rc;
    DWORD    dwItemSpec;
    UINT     uItemState;
    LPARAM   lItemlParam;
} NMCUSTOMDRAW, FAR *LPNMCUSTOMDRAW;

/* ms911865 "NMTTCUSTOMDRAW" (ToolTips Structures, CE .NET 4.0+):
 * "typedef struct tagNMTTCUSTOMDRAW {NMCUSTOMDRAW nmcd; UINT
 * uDrawFlags;} NMTTCUSTOMDRAW, FAR* LPNMTTCUSTOMDRAW;".  uDrawFlags
 * takes the DrawText DT_* values (wingdi.h).  32-bit size 52,
 * TU-asserted. */
typedef struct tagNMTTCUSTOMDRAW {
    NMCUSTOMDRAW nmcd;
    UINT         uDrawFlags;
} NMTTCUSTOMDRAW, FAR *LPNMTTCUSTOMDRAW;

/* ms940418 "TBBUTTON" (Toolbar Controls Structures, CE 1.0+):
 * "typedef struct _TBBUTTON { int iBitmap; int idCommand; BYTE
 * fsState; BYTE fsStyle; DWORD dwData; int iString; } TBBUTTON, NEAR*
 * PTBBUTTON, FAR* LPTBBUTTON; typedef const TBBUTTON FAR*
 * LPCTBBUTTON;".  32-bit size 20, TU-asserted. */
typedef struct _TBBUTTON {
    int      iBitmap;
    int      idCommand;
    BYTE     fsState;
    BYTE     fsStyle;
    DWORD    dwData;
    int      iString;
} TBBUTTON, NEAR *PTBBUTTON, FAR *LPTBBUTTON;
typedef const TBBUTTON FAR *LPCTBBUTTON;

/* ms940420 "TBBUTTONINFO" (CE .NET 4.0+): both the CE 5.0 page and
 * its CE 6.0 twin ee503445 print the typedef names TBBUTTONINFOA /
 * *LPTBBUTTONINFOA ("typedef struct {UINT cbSize; DWORD dwMask; int
 * idCommand; int iImage; BYTE fsState; BYTE fsStyle; WORD cx; DWORD
 * lParam; LPTSTR pszText; int cchText;} TBBUTTONINFOA,
 * *LPTBBUTTONINFOA;"); the TB_GETBUTTONINFO message page (ms940430)
 * types its lParam "LPTBBUTTONINFO", so the unsuffixed alias is
 * bridged below (same model as the M54 CHOOSEFONT/CHOOSEFONTW note in
 * commdlg.h).  32-bit size 32, TU-asserted. */
typedef struct {
    UINT     cbSize;
    DWORD    dwMask;
    int      idCommand;
    int      iImage;
    BYTE     fsState;
    BYTE     fsStyle;
    WORD     cx;
    DWORD    lParam;
    LPTSTR   pszText;
    int      cchText;
} TBBUTTONINFOA, *LPTBBUTTONINFOA;
typedef TBBUTTONINFOA   TBBUTTONINFO;
typedef LPTBBUTTONINFOA LPTBBUTTONINFO;

/* ms940414 "TBADDBITMAP" (CE 1.0+): "typedef struct { INSTANCE hInst;
 * INT nID; } TBADDBITMAP, *LPTBADDBITMAP;" -- the first member type
 * is printed "INSTANCE" [sic, missing H]; restored as HINSTANCE (the
 * member is the module handle of the bitmap, and CommandBar_AddBitmap
 * ms908128 types the same parameter HINSTANCE).  32-bit size 8,
 * TU-asserted. */
typedef struct {
    HINSTANCE hInst;
    INT       nID;
} TBADDBITMAP, *LPTBADDBITMAP;

/* ms913817 "TBREPLACEBITMAP" (CE .NET 4.0+): "typedef struct
 * {HINSTANCE hInstOld; UINT nIDOld; HINSTANCE hInstNew; UINT nIDNew;
 * int nButtons;} TBREPLACEBITMAP, *LPTBREPLACEBITMAP;".
 * 32-bit size 20, TU-asserted. */
typedef struct {
    HINSTANCE hInstOld;
    UINT      nIDOld;
    HINSTANCE hInstNew;
    UINT      nIDNew;
    int       nButtons;
} TBREPLACEBITMAP, *LPTBREPLACEBITMAP;

/* ms911863 "NMTOOLBAR" (Toolbar Controls Structures, CE .NET 4.0+):
 * "typedef struct tagNMTOOLBAR {NMHDR hdr; int iItem; TBBUTTON
 * tbButton; int cchText; LPTSTR pszText;} NMTOOLBAR, FAR*
 * LPNMTOOLBAR;".  32-bit size 44, TU-asserted. */
typedef struct tagNMTOOLBAR {
    NMHDR    hdr;
    int      iItem;
    TBBUTTON tbButton;
    int      cchText;
    LPTSTR   pszText;
} NMTOOLBAR, FAR *LPNMTOOLBAR;

/* aa453757 "TOOLINFO" (ToolTips Structures, CE .NET 4.0+): "typedef
 * struct tagTOOLINFO {UINT cbSize; UINT uFlags; HWND hwnd; UINT uId;
 * RECT rect; HINSTANCE hinst; LPTSTR lpszText; LPARAM lParam;}
 * TTTOOLINFO, NEAR* PTOOLINFO, FAR* LPTTTOOLINFO;" -- the CE typedef
 * names are TTTOOLINFO / PTOOLINFO / LPTTTOOLINFO.  uFlags takes the
 * TTF_* flags (names published, values held).  32-bit size 44,
 * TU-asserted. */
typedef struct tagTOOLINFO {
    UINT      cbSize;
    UINT      uFlags;
    HWND      hwnd;
    UINT      uId;
    RECT      rect;
    HINSTANCE hinst;
    LPTSTR    lpszText;
    LPARAM    lParam;
} TTTOOLINFO, NEAR *PTOOLINFO, FAR *LPTTTOOLINFO;

/* aa453819 "TTHITTESTINFO" (CE .NET 4.0+): "typedef struct
 * _TT_HITTESTINFO {HWND hwnd; POINT pt; TTTOOLINFO ti;} TTHITTESTINFO,
 * FAR* LPTTHITTESTINFO;".  32-bit size 56, TU-asserted. */
typedef struct _TT_HITTESTINFO {
    HWND       hwnd;
    POINT      pt;
    TTTOOLINFO ti;
} TTHITTESTINFO, FAR *LPTTHITTESTINFO;

/* ms911866 "NMTTDISPINFO" (CE .NET 4.0+): "typedef struct
 * tagNMTTDISPINFO {NMHDR hdr; LPTSTR lpszText; TCHAR szText[80];
 * HINSTANCE hinst; UINT uFlags; LPARAM lParam;} NMTTDISPINFO, FAR*
 * LPNMTTDISPINFO;".  32-bit size 188, TU-asserted. */
typedef struct tagNMTTDISPINFO {
    NMHDR      hdr;
    LPTSTR     lpszText;
    TCHAR      szText[80];
    HINSTANCE  hinst;
    UINT       uFlags;
    LPARAM     lParam;
} NMTTDISPINFO, FAR *LPNMTTDISPINFO;

/* ms911927 "PBRANGE" (Progress Bar Controls Structures, CE 2.0+):
 * "typedef struct {int iLow; int iHigh;} PBRANGE, *PPBRANGE;" (tag
 * printed anonymous, as on the page).  32-bit size 8, TU-asserted. */
typedef struct {
    int      iLow;
    int      iHigh;
} PBRANGE, *PPBRANGE;

/* ms911870 "NMUPDOWN" (Up-Down Controls Structures, CE .NET 4.0+):
 * "typedef struct _NM_UPDOWN {NMHDR hdr; int iPos; int iDelta;}
 * NMUPDOWN, FAR* LPNMUPDOWN;".  32-bit size 20, TU-asserted. */
typedef struct _NM_UPDOWN {
    NMHDR    hdr;
    int      iPos;
    int      iDelta;
} NMUPDOWN, FAR *LPNMUPDOWN;

/* ms914067 "UDACCEL" (CE .NET 4.0+): "typedef struct {int nSec; int
 * nInc; } UDACCEL;" (tag printed anonymous).  32-bit size 8,
 * TU-asserted. */
typedef struct {
    int      nSec;
    int      nInc;
} UDACCEL;

/* aa453639 "REBARBANDINFO" (Rebar Controls Structures, CE 2.0+;
 * fetched as the CommandBands dependency, see
 * tools/manifests/cc-cmdbands-dep.manifest): "typedef struct
 * tagREBARBANDINFO {UINT cbSize; UINT fMask; UINT fStyle; COLORREF
 * clrFore; COLORREF clrBack; LPTSTR lpText; UINT cch; int iImage;
 * HWND hwndChild; UINT cxMinChild; UINT cyMinChild; UINT cx; HBITMAP
 * hbmBack; UINT wID; UINT cyChild; UINT cyMaxChild; UINT cyIntegral;
 * UINT cxIdeal; LPARAM lParam;} REBARBANDINFO, FAR* LPREBARBANDINFO;".
 * fMask takes the RBBIM_* mask flags and fStyle the RBBS_* styles
 * (names published on the CE pages, values held).  32-bit size 80,
 * TU-asserted. */
typedef struct tagREBARBANDINFO {
    UINT      cbSize;
    UINT      fMask;
    UINT      fStyle;
    COLORREF  clrFore;
    COLORREF  clrBack;
    LPTSTR    lpText;
    UINT      cch;
    int       iImage;
    HWND      hwndChild;
    UINT      cxMinChild;
    UINT      cyMinChild;
    UINT      cx;
    HBITMAP   hbmBack;
    UINT      wID;
    UINT      cyChild;
    UINT      cyMaxChild;
    UINT      cyIntegral;
    UINT      cxIdeal;
    LPARAM    lParam;
} REBARBANDINFO, FAR *LPREBARBANDINFO;

/* ms908125 "COMMANDBANDSRESTOREINFO" (Command Bands Structures,
 * CE 2.0+): "typedef struct tagCOMMANDBANDSRESTOREINFO {UINT cbSize;
 * UINT wID; UINT fStyle; UINT cxRestored; BOOL fMaximized;}
 * COMMANDBANDSRESTOREINFO, *LPCOMMANDBANDSRESTOREINFO;".  fStyle takes
 * the RBBS_* band styles (names published, values held).  32-bit size
 * 20, TU-asserted. */
typedef struct tagCOMMANDBANDSRESTOREINFO {
    UINT     cbSize;
    UINT     wID;
    UINT     fStyle;
    UINT     cxRestored;
    BOOL     fMaximized;
} COMMANDBANDSRESTOREINFO, *LPCOMMANDBANDSRESTOREINFO;

/* ------------------------------------------------------------------ */
/* Common Control functions and macros (shared sub-book).              */
/* ------------------------------------------------------------------ */

/* ms909848 "InitCommonControls" (CE 2.0+; Commctrl.lib):
 * "void InitCommonControls(void);". */
AKARI_CE_IMPORT void     InitCommonControls(void) AKARI_CE_NAME(InitCommonControls);                            /* ms909848 */

/* ms909849 "InitCommonControlsEx" (CE 2.0+; Commctrl.lib):
 * "BOOL InitCommonControlsEx(LPINITCOMMONCONTROLSEX lpInitCtrls );". */
AKARI_CE_IMPORT BOOL     InitCommonControlsEx(LPINITCOMMONCONTROLSEX lpInitCtrls) AKARI_CE_NAME(InitCommonControlsEx); /* ms909849 */

/* ms909844 "INDEXTOSTATEIMAGEMASK" (Common Control Macros): the page
 * prints the macro body verbatim. */
#define INDEXTOSTATEIMAGEMASK(i) ((i) << 12)

/* aa453073 "FORWARD_WM_NOTIFY": the page (and its CE 6.0 twin
 * ee505696) print the body verbatim:
 *   #define FORWARD_WM_NOTIFY(hwnd, idFrom, pnmhdr, fn) \
 *       (void)(fn)((hwnd), WM_NOTIFY, (WPARAM)(int)(id), \
 *       (LPARAM)(NMHDR FAR*)(pnmhdr))
 * -- the printed body references (id) while the documented parameter
 * is named idFrom [sic, kept as printed on both generations]. */
#define FORWARD_WM_NOTIFY(hwnd, idFrom, pnmhdr, fn) \
    (void)(fn)((hwnd), WM_NOTIFY, (WPARAM)(int)(id), \
               (LPARAM)(NMHDR FAR*)(pnmhdr))

/* ms929879 "HANDLE_WM_NOTIFY": body printed verbatim. */
#define HANDLE_WM_NOTIFY(hwnd, wParam, lParam, fn) \
    (fn)((hwnd), (int)(wParam), (NMHDR FAR*)(lParam))

/* ------------------------------------------------------------------ */
/* Command Bars (CE-specific; all Commctrl.lib, CE 1.0+ unless        */
/* noted).                                                             */
/* ------------------------------------------------------------------ */
AKARI_CE_IMPORT HWND     CommandBar_Create(HINSTANCE hInst, HWND hwndParent,
                           int idCmdBar) AKARI_CE_NAME(CommandBar_Create);                     /* ms908131 */
AKARI_CE_IMPORT BOOL     CommandBar_AddAdornments(HWND hwndCB, DWORD dwFlags,
                                  DWORD dwReserved) AKARI_CE_NAME(CommandBar_AddAdornments);          /* ms908127 */
AKARI_CE_IMPORT int      CommandBar_AddBitmap(HWND hwndCB, HINSTANCE hInst,
                              int idBitmap, int iNumImages,
                              int iImageWidth,
                              int iImageHeight) AKARI_CE_NAME(CommandBar_AddBitmap);              /* ms908128 */
AKARI_CE_IMPORT void     CommandBar_AlignAdornments(HWND hwndCB) AKARI_CE_NAME(CommandBar_AlignAdornments);             /* aa453948 (CE 4.0+) */
AKARI_CE_IMPORT BOOL     CommandBar_DrawMenuBar(HWND hwndCB, WORD iButton) AKARI_CE_NAME(CommandBar_DrawMenuBar);   /* ms908133 */
AKARI_CE_IMPORT HMENU    CommandBar_GetMenu(HWND hwndCB, WORD iButton) AKARI_CE_NAME(CommandBar_GetMenu);       /* ms908134 */
AKARI_CE_IMPORT int      CommandBar_Height(HWND hwndCB) AKARI_CE_NAME(CommandBar_Height);                      /* ms908135 */
AKARI_CE_IMPORT HWND     CommandBar_InsertComboBox(HWND hwndCB, HINSTANCE hInst,
                                   int iWidth, UINT dwStyle,
                                   WORD idComboBox,
                                   WORD iButton) AKARI_CE_NAME(CommandBar_InsertComboBox);             /* ms908137 */
AKARI_CE_IMPORT BOOL     CommandBar_InsertMenubar(HWND hwndCB, HINSTANCE hInst,
                                  WORD idMenu, WORD iButton) AKARI_CE_NAME(CommandBar_InsertMenubar); /* ms908138 */
AKARI_CE_IMPORT BOOL     CommandBar_InsertMenubarEx(HWND hwndCB, HINSTANCE hInst,
                                    LPTSTR pszMenu,
                                    WORD iButton) AKARI_CE_NAME(CommandBar_InsertMenubarEx);            /* ms908139 */
AKARI_CE_IMPORT BOOL     CommandBar_Show(HWND hwndCB, BOOL fShow) AKARI_CE_NAME(CommandBar_Show);            /* ms908141 */

/* Command Bars Macros (ms907216 sub-book): the CE macro pages print
 * signatures but no macro bodies, so the definitions are held; the
 * documented signatures are recorded here:
 *   BOOL CommandBar_AddButtons(HWND hwndCB, UINT uNumButtons,
 *                              LPTBBUTTON lpButtons);      ms908129
 *   BOOL CommandBar_AddToolTips(HWND hwndCB, UINT uNumToolTips,
 *                              LPTSTR lpToolTips);         ms908130
 *   void CommandBar_Destroy(HWND hwndCB);                   ms908132
 *   BOOL CommandBar_InsertButton(HWND hwndCB, int iButton,
 *                              LPTBBUTTON lpButton);       ms908136
 *   BOOL CommandBar_IsVisible(HWND hwndCB);                 ms908140
 */

/* ------------------------------------------------------------------ */
/* Command Bands (CE-specific; all Commctrl.lib, CE 2.0+).            */
/* ------------------------------------------------------------------ */
AKARI_CE_IMPORT HWND     CommandBands_Create(HINSTANCE hinst, HWND hwndParent, UINT wID,
                             DWORD dwStyles,
                             HIMAGELIST himl) AKARI_CE_NAME(CommandBands_Create);                /* ms908121 */
AKARI_CE_IMPORT BOOL     CommandBands_AddAdornments(HWND hwndCmdBands, HINSTANCE hinst,
                                    DWORD dwFlags,
                                    LPREBARBANDINFO prbbi) AKARI_CE_NAME(CommandBands_AddAdornments);   /* ms908118 */
AKARI_CE_IMPORT BOOL     CommandBands_AddBands(HWND hwndCmdBands, HINSTANCE hinst,
                               UINT cBands,
                               LPREBARBANDINFO prbbi) AKARI_CE_NAME(CommandBands_AddBands);        /* ms908120 */
AKARI_CE_IMPORT HWND     CommandBands_GetCommandBar(HWND hwndCmdBands,
                                    UINT uBand) AKARI_CE_NAME(CommandBands_GetCommandBar);              /* ms908122 */
AKARI_CE_IMPORT BOOL     CommandBands_GetRestoreInformation(HWND hwndCmdBands, UINT uBand,
                                            LPCOMMANDBANDSRESTOREINFO
                                            pcbri) AKARI_CE_NAME(CommandBands_GetRestoreInformation);            /* ms908123 */
AKARI_CE_IMPORT BOOL     CommandBands_Show(HWND hwndCmdBands, BOOL fShow) AKARI_CE_NAME(CommandBands_Show);    /* ms908126 */

/* Command Bands Macros: CommandBands_Height(HWND hwndCmdBands)
 * (ms908124) -- signature documented, body not printed: held. */

/* ------------------------------------------------------------------ */
/* Status Bars (Commctrl.lib, CE 1.0+).                                */
/* ------------------------------------------------------------------ */

/* ms908188 "CreateStatusWindow": "HWND CreateStatusWindow(LONG style,
 * LPSTR lpszText, HWND hwndParent, WORD wID );" -- the text parameter
 * is printed LPSTR [as printed; the DrawStatusText twin prints
 * LPCWSTR]. */
AKARI_CE_IMPORT HWND     CreateStatusWindow(LONG style, LPSTR lpszText,
                            HWND hwndParent, WORD wID) AKARI_CE_NAME(CreateStatusWindow);       /* ms908188 */

/* aa452976 "DrawStatusText": "void DrawStatusText(HDC hdc, LPRECT
 * lprc, LPCWSTR pszText, UINT uFlags );" -- uFlags takes the SBT_*
 * drawing flags (names published on the page, values held). */
AKARI_CE_IMPORT void     DrawStatusText(HDC hdc, LPRECT lprc, LPCWSTR pszText,
                        UINT uFlags) AKARI_CE_NAME(DrawStatusText);                         /* aa452976 */

/* ------------------------------------------------------------------ */
/* Toolbar (no Link Library row on the CE page: host-declared only).   */
/* ------------------------------------------------------------------ */

/* ms908190 "CreateToolbarEx": "HWND CreateToolbarEx(HWND hwnd, DWORD
 * ws, UINT wID, int nBitmaps, HINSTANCE hBMInst, UINT wBMID,
 * LPCTBBUTTON lpButtons, int iNumButtons, int dxButton, int dyButton,
 * int dxBitmap, int dyBitmap, UINT uStructSize );". */
HWND     CreateToolbarEx(HWND hwnd, DWORD ws, UINT wID, int nBitmaps,
                         HINSTANCE hBMInst, UINT wBMID,
                         LPCTBBUTTON lpButtons, int iNumButtons,
                         int dxButton, int dyButton, int dxBitmap,
                         int dyBitmap, UINT uStructSize);     /* ms908190 */

/* ------------------------------------------------------------------ */
/* Up-Down (no Link Library row on the CE page: host-declared only).   */
/* ------------------------------------------------------------------ */

/* ms908191 "CreateUpDownControl": "HWND CreateUpDownControl(DWORD
 * dwStyle, int x, int y, int cx, int cy, HWND hParent, int nID,
 * HINSTANCE hInst, HWND hBuddy, int nUpper, int nLower, int nPos );". */
HWND     CreateUpDownControl(DWORD dwStyle, int x, int y, int cx, int cy,
                             HWND hParent, int nID, HINSTANCE hInst,
                             HWND hBuddy, int nUpper, int nLower,
                             int nPos);                       /* ms908191 */

/* ------------------------------------------------------------------ */
/* Animation controls: the Animate_* macro pages (aa452851..aa452857)
 * print signatures but no macro bodies, so the definitions are held;
 * the documented signatures are recorded here:
 *   BOOL Animate_Close(HWND hwnd);                          aa452851
 *   HWND Animate_Create(HWND hwndP, UINT id, DWORD dwStyle,
 *                       HINSTANCE hInstance);              aa452852
 *   BOOL Animate_Open(HWND hwndAnim, LPTSTR lpszName);     aa452853
 *   BOOL Animate_OpenEx(HWND hwndAnim, HINSTANCE hinst,
 *                       LPTSTR lpszName);                  aa452854
 *   BOOL Animate_Play(HWND hwndAnim, UINT wFrom, UINT wTo,
 *                     UINT cRepeat);                        aa452855
 *   BOOL Animate_Seek(HWND hwndAnim, UINT wFrame);         aa452856
 *   BOOL Animate_Stop(HWND hwndAnim);                       aa452857
 * ------------------------------------------------------------------ */

/* ------------------------------------------------------------------ */
/* HELD ledger (names published without numeric values; full page-id
 * accounting in docs/inventory.md M54):
 *   shared:   ICC_ANIMATE_CLASS, ICC_BAR_CLASSES, ICC_CAPEDIT_CLASS,
 *             ICC_COOL_CLASSES, ICC_DATE_CLASSES, ICC_FE_CLASSES,
 *             ICC_LISTVIEW_CLASSES, ICC_PROGRESS_CLASS,
 *             ICC_TAB_CLASSES, ICC_TOOLTIP_CLASSES,
 *             ICC_TREEVIEW_CLASSES, ICC_UPDOWN_CLASS (ms909850);
 *             NM_CLICK, NM_DBLCLK, NM_HOVER, NM_KEYDOWN, NM_KILLFOCUS,
 *             NM_OUTOFMEMORY, NM_RCLICK, NM_RDBLCLK, NM_RETURN,
 *             NM_SETFOCUS (Common Control Notifications);
 *             NM_CUSTOMDRAW (ms911871)
 *   custom draw: CDDS_PREPAINT..CDDS_ITEMPOSTPAINT, CDDS_ITEM,
 *             CDDS_PREERASE/POSTERASE (ms931470); CDIS_CHECKED..
 *             CDIS_SELECTED (ms931470); TBCD_CHANNEL/TBCD_THUMB/
 *             TBCD_TICS (ms931470)
 *   animation: ACS_AUTOPLAY, ACS_CENTER, ACS_TIMER, ACS_TRANSPARENT
 *             (aa452861); ACM_OPEN/ACM_PLAY/ACM_STOP (aa452840..842);
 *             ACN_START/ACN_STOP (aa452843/844); ANIMATE_CLASS (not
 *             published at all)
 *   capedit:   CEM_ENABLEUPCASE, CEM_UPCASEALLWORDS (ms908080/081)
 *   cmdbands:  CMDBAR_HELP, CMDBAR_OK (ms908118/127); RBBS_* band
 *             styles (ms908125, 8 names)
 *   status:    SB_GETBORDERS..SB_SIMPLE (13 messages, ms939915..
 *             ms932534); SBT_NOBORDERS/POPOUT/OWNERDRAW/RTLREADING
 *             (aa452976, ms913198, ms932525); SBN_SIMPLEMODECHANGE
 *             (ms913282); STATUSCLASSNAME (not published)
 *   toolbar:   TB_ADDBITMAP..TB_LOADIMAGES etc. (54 messages,
 *             ms913849..ms913724); TBN_* notifications; IDB_STD_* /
 *             IDB_VIEW_* bitmap ids and STD_* / VIEW_* image indices
 *             (ms940414, ms908128; names only); TBSTATE_* / TBSTYLE_*
 *             (not republished as tables on the CE pages)
 *   tooltips:  TTM_* messages (27); TTN_GETDISPINFO/TTN_POP/TTN_SHOW/
 *             TTN_NEEDTEXT (notifications); TTF_ABSOLUTE, TTF_CENTERTIP,
 *             TTF_IDISHWND, TTF_RTLREADING, TTF_SUBCLASS, TTF_DI_SETITEM
 *             (aa453757, ms911866)
 *   trackbar:  TBM_CLEARSEL..TBM_SETTICFREQ etc. (30 messages,
 *             ms913727..); TBS_* styles (referenced by name)
 *   up-down:   UDM_* messages (12) and UDN_DELTAPOS (ms914080);
 *             UDS_* styles (referenced by name)
 *   progress:  PBM_DELTAPOS..PBM_STEPIT (8 messages, ms911919..926)
 * ------------------------------------------------------------------ */


/* ================================================================== */
/* M56: Common Controls Reference, batch 2 (the Date and Time Picker,  */
/* Header, List View, Month Calendar, Rebar, Tab and Tree View         */
/* sub-books; tools/manifests/cc-{dateandtimepicker,header,listview,  */
/* monthcalendar,rebar,tab,treeview}.manifest).  Structures only --   */
/* every message / notification / style / flag family of these books  */
/* publishes names without numeric values (held ledger below) and no  */
/* page of this batch carries a Link Library row, so no defs and no   */
/* import pins are generated.  Prototypes were cross-read against     */
/* the CE 6.0 twins (tools/manifests/m55-ce60.manifest).              */
/* ================================================================== */

/* HTREEITEM: tree-view item handle, typed by every Tree View page but
 * never laid out (the HIMAGELIST model, M29). */
typedef void *HTREEITEM;

/* ------------------------------------------------------------------ */
/* Rebar Controls Structures (CE 2.0+).                                */
/* ------------------------------------------------------------------ */

/* aa453640 "REBARINFO": "typedef struct tagREBARINFO {UINT cbSize;
 * UINT fMask; HIMAGELIST himl;} REBARINFO, FAR* LPREBARINFO;".
 * fMask takes RBIM_IMAGELIST (name published, value held).
 * 32-bit size 12, TU-asserted. */
typedef struct tagREBARINFO {
    UINT        cbSize;
    UINT        fMask;
    HIMAGELIST  himl;
} REBARINFO, FAR *LPREBARINFO;

/* ms911836 "NMRBAUTOSIZE": "typedef struct tagNMRBAUTOSIZE {NMHDR
 * hdr; BOOL fChanged; RECT rcTarget; RECT rcActual;} NMRBAUTOSIZE,
 * *LPNMRBAUTOSIZE;".  32-bit size 48, TU-asserted. */
typedef struct tagNMRBAUTOSIZE {
    NMHDR    hdr;
    BOOL     fChanged;
    RECT     rcTarget;
    RECT     rcActual;
} NMRBAUTOSIZE, *LPNMRBAUTOSIZE;

/* ms911851 "NMREBAR": "typedef struct tagNMREBAR {NMHDR hdr; UINT
 * uBand; UINT wID; UINT cyChild; UINT cyBand;} NMREBAR, *LPNMREBAR;".
 * 32-bit size 28, TU-asserted. */
typedef struct tagNMREBAR {
    NMHDR    hdr;
    UINT     uBand;
    UINT     wID;
    UINT     cyChild;
    UINT     cyBand;
} NMREBAR, *LPNMREBAR;

/* aa453620 "RBHITTESTINFO" (page title spelling): "typedef struct
 * _RB_HITTESTINFO {POINT pt; UINT flags; int iBand;} RBHITTESTINFO,
 * FAR* LPRBHITTESTINFO;".  flags takes the RBHT_* values (names
 * published on the page, values held).  32-bit size 16, TU-asserted. */
typedef struct _RB_HITTESTINFO {
    POINT    pt;
    UINT     flags;
    int      iBand;
} RBHITTESTINFO, FAR *LPRBHITTESTINFO;

/* ------------------------------------------------------------------ */
/* Header Controls Structures.                                         */
/* ------------------------------------------------------------------ */

/* ms929881 "HDITEM": "typedef struct _HDITEM { UINT mask; int cxy;
 * LPTSTR pszText; HBITMAP hbm; int cchTextMax; int fmt; LPARAM
 * lParam; int iImage; int iOrder;} HDITEM;" (twin ee502857 identical;
 * the HDM_* message pages spell the type HD_ITEM -- alias bridged
 * below, the TBBUTTONINFO model).  mask takes the HDI_* values and
 * fmt the HDF_* values (names published, values held).
 * 32-bit size 36, TU-asserted. */
typedef struct _HDITEM {
    UINT     mask;
    int      cxy;
    LPTSTR   pszText;
    HBITMAP  hbm;
    int      cchTextMax;
    int      fmt;
    LPARAM   lParam;
    int      iImage;
    int      iOrder;
} HDITEM, FAR *LPHDITEM;
typedef HDITEM  HD_ITEM;      /* HDM_GETITEM/SETITEM/INSERTITEM spell */
typedef LPHDITEM LPHD_ITEM;

/* ms929882 "HDLAYOUT" (page title spelling): "typedef struct
 * _HD_LAYOUT { RECT FAR* prc; WINDOWPOS FAR* pwpos;} HD_LAYOUT;".
 * 32-bit size 8, TU-asserted. */
typedef struct _HD_LAYOUT {
    RECT  FAR *prc;
    WINDOWPOS FAR *pwpos;
} HD_LAYOUT, FAR *LPHD_LAYOUT;
typedef HD_LAYOUT  HDLAYOUT;      /* page title spelling */
typedef LPHD_LAYOUT LPHDLAYOUT;

/* ms929880 "HDHITTESTINFO" (page title spelling): "typedef struct
 * _HD_HITTESTINFO { POINT pt; UINT flags; int iItem;}
 * HD_HITTESTINFO;".  flags takes the HHT_* values (names published,
 * values held).  32-bit size 16, TU-asserted. */
typedef struct _HD_HITTESTINFO {
    POINT    pt;
    UINT     flags;
    int      iItem;
} HD_HITTESTINFO;
typedef HD_HITTESTINFO HDHITTESTINFO;   /* page title spelling */

/* ms931478 "NMHDDISPINFO": "typedef struct tagNMHDDISPINFO { NMHDR
 * hdr; int iItem; UINT mask; LPTSTR pszText; int cchTextMax; int
 * iImage; LPARAM lParam;} NMHDDISPINFO, FAR* LPNMHDDISPINFO;".
 * 32-bit size 36, TU-asserted. */
typedef struct tagNMHDDISPINFO {
    NMHDR    hdr;
    int      iItem;
    UINT     mask;
    LPTSTR   pszText;
    int      cchTextMax;
    int      iImage;
    LPARAM   lParam;
} NMHDDISPINFO, FAR *LPNMHDDISPINFO;

/* ms931480 "NMHEADER": "typedef struct tagNMHEADER { NMHDR hdr; int
 * iItem; int iButton; HDITEM FAR* pItem;} NMHEADER, FAR* LPNMHEADER;".
 * 32-bit size 24, TU-asserted. */
typedef struct tagNMHEADER {
    NMHDR        hdr;
    int          iItem;
    int          iButton;
    HDITEM FAR  *pItem;
} NMHEADER, FAR *LPNMHEADER;

/* ------------------------------------------------------------------ */
/* Tab Controls Structures.                                            */
/* ------------------------------------------------------------------ */

/* ms913857 "TCITEM": "typedef struct tagTCITEM {UINT mask; DWORD
 * dwState; DWORD dwStateMask; LPTSTR pszText; int cchTextMax; int
 * iImage; LPARAM lParam;} TCITEM;".  mask takes the TCIF_* values,
 * dwState the TCIS_* values (names published, values held).
 * 32-bit size 28, TU-asserted. */
typedef struct tagTCITEM {
    UINT     mask;
    DWORD    dwState;
    DWORD    dwStateMask;
    LPTSTR   pszText;
    int      cchTextMax;
    int      iImage;
    LPARAM   lParam;
} TCITEM, FAR *LPTCITEM;

/* ms913860 "TCITEMHEADER": "typedef struct tagTCITEMHEADER {UINT
 * mask; UINT lpReserved1; UINT lpReserved2; LPTSTR pszText; int
 * cchTextMax; int iImage;} TCITEMHEADER, FAR* LPTCITEMHEADER;".
 * 32-bit size 24, TU-asserted. */
typedef struct tagTCITEMHEADER {
    UINT     mask;
    UINT     lpReserved1;
    UINT     lpReserved2;
    LPTSTR   pszText;
    int      cchTextMax;
    int      iImage;
} TCITEMHEADER, FAR *LPTCITEMHEADER;

/* ms913854 "TCHITTESTINFO": "typedef struct _TCHITTESTINFO { POINT
 * pt; UINT flags; } TCHITTESTINFO;".  flags takes the TCHT_* values
 * (names published, values held).  32-bit size 12, TU-asserted. */
typedef struct _TCHITTESTINFO {
    POINT    pt;
    UINT     flags;
} TCHITTESTINFO, FAR *LPTCHITTESTINFO;

/* ms911862 "NMTCKEYDOWN": "typedef struct tagNMTCKEYDOWN {NMHDR hdr;
 * WORD wVKey; UINT flags;} NMTCKEYDOWN;".  32-bit size 20,
 * TU-asserted. */
typedef struct tagNMTCKEYDOWN {
    NMHDR    hdr;
    WORD     wVKey;
    UINT     flags;
} NMTCKEYDOWN, FAR *LPNMTCKEYDOWN;

/* ------------------------------------------------------------------ */
/* Date and Time Picker Controls Structures.                           */
/* ------------------------------------------------------------------ */

/* ms931471 "NMDATETIMECHANGE": "typedef struct tagNMDATETIMECHANGE
 * {NMHDR nmhdr; DWORD dwFlags; SYSTEMTIME st;} NMDATETIMECHANGE,
 * FAR* LPNMDATETIMECHANGE;".  dwFlags takes GDT_NONE/GDT_VALID
 * (names published, values held).  32-bit size 32, TU-asserted. */
typedef struct tagNMDATETIMECHANGE {
    NMHDR       nmhdr;
    DWORD       dwFlags;
    SYSTEMTIME  st;
} NMDATETIMECHANGE, FAR *LPNMDATETIMECHANGE;

/* ms931472 "NMDATETIMEFORMAT": "typedef struct tagNMDATETIMEFORMAT
 * {NMHDR nmhdr; LPCTSTR pszFormat; SYSTEMTIME st; LPCTSTR pszDisplay;
 * TCHAR szDisplay[64];} NMDATETIMEFORMAT, FAR* LPNMDATETIMEFORMAT;".
 * 32-bit size 164, TU-asserted. */
typedef struct tagNMDATETIMEFORMAT {
    NMHDR       nmhdr;
    LPCTSTR     pszFormat;
    SYSTEMTIME  st;
    LPCTSTR     pszDisplay;
    TCHAR       szDisplay[64];
} NMDATETIMEFORMAT, FAR *LPNMDATETIMEFORMAT;

/* ms931473 "NMDATETIMEFORMATQUERY": "typedef struct
 * tagNMDATETIMEFORMATQUERY {NMHDR nmhdr; LPCTSTR pszFormat; SIZE
 * szMax;} NMDATETIMEFORMATQUERY, FAR* LPNMDATETIMEFORMATQUERY;".
 * 32-bit size 24, TU-asserted. */
typedef struct tagNMDATETIMEFORMATQUERY {
    NMHDR       nmhdr;
    LPCTSTR     pszFormat;
    SIZE        szMax;
} NMDATETIMEFORMATQUERY, FAR *LPNMDATETIMEFORMATQUERY;

/* ms931474 "NMDATETIMESTRING": "typedef struct tagNMDATETIMESTRING
 * {NMHDR nmhdr; LPCTSTR pszUserString; SYSTEMTIME st; DWORD dwFlags;}
 * NMDATETIMESTRING, FAR* LPNMDATETIMESTRING;".  32-bit size 36,
 * TU-asserted. */
typedef struct tagNMDATETIMESTRING {
    NMHDR       nmhdr;
    LPCTSTR     pszUserString;
    SYSTEMTIME  st;
    DWORD       dwFlags;
} NMDATETIMESTRING, FAR *LPNMDATETIMESTRING;

/* ms931475 "NMDATETIMEWMKEYDOWN": "typedef struct
 * tagNMDATETIMEWMKEYDOWN {NMHDR nmhdr; int nVirtKey; LPCTSTR
 * pszFormat; SYSTEMTIME st;} NMDATETIMEWMKEYDOWN, FAR*
 * LPNMDATETIMEWMKEYDOWN;".  32-bit size 36, TU-asserted. */
typedef struct tagNMDATETIMEWMKEYDOWN {
    NMHDR       nmhdr;
    int         nVirtKey;
    LPCTSTR     pszFormat;
    SYSTEMTIME  st;
} NMDATETIMEWMKEYDOWN, FAR *LPNMDATETIMEWMKEYDOWN;

/* ------------------------------------------------------------------ */
/* Month Calendar Controls Structures.                                 */
/* ------------------------------------------------------------------ */

/* ms911793 "MCHITTESTINFO": "typedef struct {UINT cbSize; POINT pt;
 * UINT uHit; SYSTEMTIME st;} MCHITTESTINFO, *PMCHITTESTINFO;" (tag
 * printed anonymous).  uHit takes the MCHT_* values (names published,
 * values held).  32-bit size 32, TU-asserted. */
typedef struct {
    UINT        cbSize;
    POINT       pt;
    UINT        uHit;
    SYSTEMTIME  st;
} MCHITTESTINFO, *PMCHITTESTINFO;

/* ms911859 "NMSELCHANGE": "typedef struct tagNMSELCHANGE {NMHDR
 * nmhdr; SYSTEMTIME stSelStart; SYSTEMTIME stSelEnd;} NMSELCHANGE,
 * FAR* LPNMSELCHANGE;".  32-bit size 44, TU-asserted. */
typedef struct tagNMSELCHANGE {
    NMHDR       nmhdr;
    SYSTEMTIME  stSelStart;
    SYSTEMTIME  stSelEnd;
} NMSELCHANGE, FAR *LPNMSELCHANGE;

/* ms931476 "NMDAYSTATE": "typedef struct tagNMDAYSTATE {NMHDR
 * nmhdr; SYSTEMTIME stStart; int cDayState; LPMONTHDAYSTATE
 * prgDayState;} NMDAYSTATE, FAR* LPNMDAYSTATE;" -- LPMONTHDAYSTATE
 * has no CE page (dangling type, the SHCONTF precedent): the member
 * is typed layout-neutral void* with the print recorded.
 * 32-bit size 36, TU-asserted. */
typedef struct tagNMDAYSTATE {
    NMHDR       nmhdr;
    SYSTEMTIME  stStart;
    int         cDayState;
    void       *prgDayState;   /* printed LPMONTHDAYSTATE; no CE page */
} NMDAYSTATE, FAR *LPNMDAYSTATE;

/* ------------------------------------------------------------------ */
/* Tree View Controls Structures.                                      */
/* ------------------------------------------------------------------ */

/* PFNTVCOMPARE: the TV_SORTCB lpfnCompare member type; the ms914065
 * page prints the comparison callback as
 * "int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2,
 * LPARAM lParamSort);" -- pointer built from the documented signature
 * (M51 IMENUMPROC model). */
typedef int (CALLBACK *PFNTVCOMPARE)(LPARAM lParam1, LPARAM lParam2,
                                     LPARAM lParamSort);

/* ms913992 "TVITEM": "typedef struct _TVITEM { tvi UINT mask;
 * HTREEITEM hItem; UINT state; UINT stateMask; LPSTR pszText; int
 * cchTextMax; int iImage; int iSelectedImage; int cChildren; LPARAM
 * lParam; } TVITEM, FAR* LPTVITEM;" -- the leading "tvi" of the
 * first member is a print artifact present in BOTH the CE 5.0 page
 * and the CE 6.0 twin ee502863 [recorded]; the member type is UINT.
 * The legacy-spelling page ms914064 "TV_ITEM" prints the identical
 * layout -- alias bridged below.  mask takes the TVIF_* values,
 * state the TVIS_* values, and hInsertAfter the TVI_* values (names
 * published, values held).  32-bit size 40, TU-asserted. */
typedef struct _TVITEM {
    UINT        mask;
    HTREEITEM   hItem;
    UINT        state;
    UINT        stateMask;
    LPSTR       pszText;
    int         cchTextMax;
    int         iImage;
    int         iSelectedImage;
    int         cChildren;
    LPARAM      lParam;
} TVITEM, FAR *LPTVITEM;
typedef TVITEM   TV_ITEM;      /* ms914064, identical layout */
typedef LPTVITEM LPTV_ITEM;

/* ms914063 "TV_INSERTSTRUCT": "typedef struct _TV_INSERTSTRUCT {
 * HTREEITEM hParent; HTREEITEM hInsertAfter; TV_ITEM item; }
 * TV_INSERTSTRUCT, FAR* LPTV_INSERTSTRUCT;" (twin ee505024
 * identical).  32-bit size 48, TU-asserted. */
typedef struct _TV_INSERTSTRUCT {
    HTREEITEM   hParent;
    HTREEITEM   hInsertAfter;
    TV_ITEM     item;
} TV_INSERTSTRUCT, FAR *LPTV_INSERTSTRUCT;

/* ms914062 "TV_HITTESTINFO": "typedef struct _TVHITTESTINFO { POINT
 * pt; UINT flags; HTREEITEM hItem; } TV_HITTESTINFO, FAR*
 * LPTV_HITTESTINFO;".  The new-spelling page ms913985 "TVHITTESTINFO"
 * prints the identical layout -- alias bridged below.  flags takes
 * the TVHT_* values (names published, values held).  32-bit size 16,
 * TU-asserted. */
typedef struct _TVHITTESTINFO {
    POINT       pt;
    UINT        flags;
    HTREEITEM   hItem;
} TV_HITTESTINFO, FAR *LPTV_HITTESTINFO;
typedef TV_HITTESTINFO   TVHITTESTINFO;      /* ms913985 */
typedef LPTV_HITTESTINFO LPTVHITTESTINFO;

/* ms914061 "TVSORTCB": "typedef struct _TVSORTCB { HTREEITEM
 * hParent; PFNTVCOMPARE lpfnCompare; LPARAM lParam; } TVSORTCB,
 * FAR* LPTVSORTCB;" -- the legacy page ms914065 "TV_SORTCB" prints
 * the identical layout with a "tvscb" prefix artifact on the first
 * member [recorded].  32-bit size 12, TU-asserted. */
typedef struct _TVSORTCB {
    HTREEITEM     hParent;
    PFNTVCOMPARE  lpfnCompare;
    LPARAM        lParam;
} TVSORTCB, FAR *LPTVSORTCB;
typedef TVSORTCB   TV_SORTCB;      /* ms914065, identical layout */
typedef LPTVSORTCB LPTV_SORTCB;

/* ms911864 "NM_TREEVIEW": "typedef struct _NM_TREEVIEW { NMHDR hdr;
 * UINT action; TV_ITEM itemOld; TV_ITEM itemNew; POINT ptDrag; }
 * NM_TREEVIEW; typedef NM_TREEVIEW FAR* LPNM_TREEVIEW;".
 * 32-bit size 104, TU-asserted. */
typedef struct _NM_TREEVIEW {
    NMHDR     hdr;
    UINT      action;
    TV_ITEM   itemOld;
    TV_ITEM   itemNew;
    POINT     ptDrag;
} NM_TREEVIEW, FAR *LPNM_TREEVIEW;

/* ms913978 "TV_DISPINFO": "typedef struct _TV_DISPINFO { NMHDR hdr;
 * TV_ITEM item; } TV_DISPINFO;".  32-bit size 52, TU-asserted. */
typedef struct _TV_DISPINFO {
    NMHDR     hdr;
    TV_ITEM   item;
} TV_DISPINFO;

/* ms911867 "NMTVCUSTOMDRAW": "typedef struct tagNMTVCUSTOMDRAW
 * {NMCUSTOMDRAW nmcd; COLORREF clrText; COLORREF clrTextBk;}
 * NMTVCUSTOMDRAW, *LPNMTVCUSTOMDRAW;".  32-bit size 56,
 * TU-asserted. */
typedef struct tagNMTVCUSTOMDRAW {
    NMCUSTOMDRAW  nmcd;
    COLORREF      clrText;
    COLORREF      clrTextBk;
} NMTVCUSTOMDRAW, *LPNMTVCUSTOMDRAW;

/* ms911869 "NMTVKEYDOWN": "typedef struct tagTVKEYDOWN {NMHDR hdr;
 * WORD wVKey; UINT flags;} NMTVKEYDOWN, FAR* LPNMTVKEYDOWN;" -- the
 * legacy page ms913996 "TV_KEYDOWN" prints the identical layout
 * under the tag _TV_KEYDOWN; alias bridged below (single definition,
 * both page ids recorded).  32-bit size 20, TU-asserted. */
typedef struct tagTVKEYDOWN {
    NMHDR    hdr;
    WORD     wVKey;
    UINT     flags;
} NMTVKEYDOWN, FAR *LPNMTVKEYDOWN;
typedef NMTVKEYDOWN  TV_KEYDOWN;      /* ms913996, identical layout */
typedef LPNMTVKEYDOWN LPTV_KEYDOWN;

/* ------------------------------------------------------------------ */
/* List View Controls Structures.                                      */
/* ------------------------------------------------------------------ */

/* aa453430 "LVITEM": "typedef struct _LVITEM {UINT mask; int iItem;
 * int iSubItem; UINT state; UINT stateMask; LPTSTR pszText; int
 * cchTextMax; int iImage; LPARAM lParam; #if (_WIN32_IE >= 0x0300)
 * int iIndent; #endif int iGroupId;} LVITEM;" -- the _WIN32_IE
 * conditional member is printed verbatim by the page and reproduced
 * here (this repo never defines _WIN32_IE, so iIndent is absent and
 * the 32-bit size is 40, TU-asserted; with _WIN32_IE >= 0x0300 it
 * would be 44).  mask takes the LVIF_* values, state the LVIS_*
 * values (names published, values held). */
typedef struct _LVITEM {
    UINT     mask;
    int      iItem;
    int      iSubItem;
    UINT     state;
    UINT     stateMask;
    LPTSTR   pszText;
    int      cchTextMax;
    int      iImage;
    LPARAM   lParam;
#if (_WIN32_IE >= 0x0300)
    int      iIndent;
#endif
    int      iGroupId;
} LVITEM, FAR *LPLVITEM;

/* aa453423 "LVCOLUMN": "typedef struct _LVCOLUMN {UINT mask; int
 * fmt; int cx; LPTSTR pszText; int cchTextMax; int iSubItem; int
 * iOrder; int iImage;} LVCOLUMN;" (twin ee499089 identical).
 * 32-bit size 32, TU-asserted. */
typedef struct _LVCOLUMN {
    UINT     mask;
    int      fmt;
    int      cx;
    LPTSTR   pszText;
    int      cchTextMax;
    int      iSubItem;
    int      iOrder;
    int      iImage;
} LVCOLUMN, FAR *LPLVCOLUMN;

/* aa453422 "LVBKIMAGE": "typedef struct tagLVBKIMAGE { ULONG
 * ulFlags; HBITMAP hbm; LPTSTR pszImage; UINT cchImageMax; int
 * xOffsetPercent; int yOffsetPercent;} LVBKIMAGE, *LPLVBKIMAGE;".
 * ulFlags takes the LVBKIF_* values (names published, values held).
 * 32-bit size 24, TU-asserted. */
typedef struct tagLVBKIMAGE {
    ULONG    ulFlags;
    HBITMAP  hbm;
    LPTSTR   pszImage;
    UINT     cchImageMax;
    int      xOffsetPercent;
    int      yOffsetPercent;
} LVBKIMAGE, *LPLVBKIMAGE;

/* aa453425 "LVFINDINFO": "typedef struct tagLVFINDINFO {UINT flags;
 * LPCTSTR psz; LPARAM lParam; POINT pt; UINT vkDirection;} LVFINDINFO,
 * FAR* LPFINDINFO;" -- the page's pointer alias is printed LPFINDINFO
 * [sic, no LV prefix; kept as printed].  The legacy page aa453540
 * "LV_FINDINFO" prints the identical layout with psz typed LPCSTR --
 * alias bridged below.  flags takes the LVFI_* values (names
 * published, values held).  32-bit size 24, TU-asserted. */
typedef struct tagLVFINDINFO {
    UINT     flags;
    LPCTSTR  psz;
    LPARAM   lParam;
    POINT    pt;
    UINT     vkDirection;
} LVFINDINFO, FAR *LPFINDINFO;
typedef LVFINDINFO  LV_FINDINFO;      /* aa453540, identical layout */

/* aa453428 "LVHITTESTINFO": "typedef struct _LVHITTESTINFO {POINT
 * pt; UINT flags; int iItem; int iSubItem;} LVHITTESTINFO;".
 * flags takes the LVHT_* values (names published, values held).
 * 32-bit size 20, TU-asserted. */
typedef struct _LVHITTESTINFO {
    POINT    pt;
    UINT     flags;
    int      iItem;
    int      iSubItem;
} LVHITTESTINFO, FAR *LPLVHITTESTINFO;

/* ms931605 "NMLISTVIEW": "typedef struct tagNMLISTVIEW {NMHDR hdr;
 * int iItem; int iSubItem; UINT uNewState; UINT uOldState; UINT
 * uChanged; POINT ptAction; LPARAM lParam;} NMLISTVIEW, FAR*
 * LPNMLISTVIEW;".  32-bit size 44, TU-asserted. */
typedef struct tagNMLISTVIEW {
    NMHDR    hdr;
    int      iItem;
    int      iSubItem;
    UINT     uNewState;
    UINT     uOldState;
    UINT     uChanged;
    POINT    ptAction;
    LPARAM   lParam;
} NMLISTVIEW, FAR *LPNMLISTVIEW;

/* ms931617 "NMLVCACHEHINT": "typedef struct tagNMLVCACHEHINT {NMHDR
 * hdr; int iFrom; int iTo;} NMLVCACHEHINT, *PNMLVCACHEHINT;".
 * 32-bit size 20, TU-asserted. */
typedef struct tagNMLVCACHEHINT {
    NMHDR    hdr;
    int      iFrom;
    int      iTo;
} NMLVCACHEHINT, *PNMLVCACHEHINT;

/* ms931627 "NMLVCUSTOMDRAW": "typedef struct tagNMLVCUSTOMDRAW {
 * NMCUSTOMDRAW nmcd; COLORREF clrText; COLORREF clrTextBk;
 * #if (_WIN32_IE >= 0x0400) int iSubItem; #endif DWORD dwItemType;
 * RECT rcText; UINT uAlign;} NMLVCUSTOMDRAW, *LPNMLVCUSTOMDRAW;" --
 * the _WIN32_IE conditional member is printed verbatim by the page
 * and reproduced here (absent in this repo: 32-bit size 80,
 * TU-asserted).  dwItemType takes the LVCDI_* values and uAlign the
 * LVA_* values (names published, values held). */
typedef struct tagNMLVCUSTOMDRAW {
    NMCUSTOMDRAW  nmcd;
    COLORREF      clrText;
    COLORREF      clrTextBk;
#if (_WIN32_IE >= 0x0400)
    int           iSubItem;
#endif
    DWORD         dwItemType;
    RECT          rcText;
    UINT          uAlign;
} NMLVCUSTOMDRAW, *LPNMLVCUSTOMDRAW;

/* ms931633 "NMLVFINDITEM": "typedef struct _NMLVFINDITEM {NMHDR
 * hdr; int iStart; LVFINDINFO lvfi;} NMLVFINDITEM, *PNMLVFINDITEM;".
 * 32-bit size 40, TU-asserted. */
typedef struct _NMLVFINDITEM {
    NMHDR       hdr;
    int         iStart;
    LVFINDINFO  lvfi;
} NMLVFINDITEM, *PNMLVFINDITEM;

/* ms931639 "NMLVGETINFOTIP": "typedef struct tagNMLVGETINFOTIP {
 * NMHDR hdr; DWORD dwFlags; LPTSTR pszText; int cchTextMax; int
 * iItem; int iSubItem; LPARAM lParam;} NMLVGETINFOTIP,
 * *LPNMLVGETINFOTIP;".  32-bit size 36, TU-asserted. */
typedef struct tagNMLVGETINFOTIP {
    NMHDR    hdr;
    DWORD    dwFlags;
    LPTSTR   pszText;
    int      cchTextMax;
    int      iItem;
    int      iSubItem;
    LPARAM   lParam;
} NMLVGETINFOTIP, *LPNMLVGETINFOTIP;

/* ms931645 "NMLVKEYDOWN": "typedef struct tagLVKEYDOWN {NMHDR hdr;
 * WORD wVKey; UINT flags;} NMLVKEYDOWN, FAR* LPNMLVKEYDOWN;".
 * 32-bit size 20, TU-asserted. */
typedef struct tagLVKEYDOWN {
    NMHDR    hdr;
    WORD     wVKey;
    UINT     flags;
} NMLVKEYDOWN, FAR *LPNMLVKEYDOWN;

/* ms931653 "NMLVODSTATECHANGE": "typedef struct
 * tagNMLVODSTATECHANGE {NMHDR hdr; int iFrom; int iTo; UINT
 * uNewState; UINT uOldState;} NMLVODSTATECHANGE, FAR*
 * LPNMLVODSTATECHANGE;".  32-bit size 28, TU-asserted. */
typedef struct tagNMLVODSTATECHANGE {
    NMHDR    hdr;
    int      iFrom;
    int      iTo;
    UINT     uNewState;
    UINT     uOldState;
} NMLVODSTATECHANGE, FAR *LPNMLVODSTATECHANGE;

/* aa453424 "LV_DISPINFO": "typedef struct tag LV_DISPINFO {NMHDR
 * hdr; LVITEM item; } LV_DISPINFO;" -- the tag is printed with a
 * space ("tag LV_DISPINFO") [sic]; tag spelled tagLV_DISPINFO here.
 * 32-bit size 52, TU-asserted. */
typedef struct tagLV_DISPINFO {
    NMHDR    hdr;
    LVITEM   item;
} LV_DISPINFO;

/* ------------------------------------------------------------------ */
/* HELD ledger, batch 2 (names published without numeric values; full
 * page-id accounting in docs/inventory.md M56):
 *   rebar:    RB_ messages (aa453608..), RBN_ notifications
 *             (aa453625..), RBBIM_/RBBS_ (aa453639),
 *             RBIM_IMAGELIST (aa453640), RBHT_ (aa453620), RBS_
 *             styles
 *   header:   HDM_ messages (ms929883..), HDN_ notifications,
 *             HDI_/HDF_/HHT_ (ms929880/81), the 15 Header_ macros --
 *             their SNDMSG bodies ARE printed (ms929911..) but
 *             reference the unpublished HDM_ values, so the macro
 *             definitions are held
 *   tab:      TCM_/TCN_ (ms9138xx/aa45278x), TCIF_/TCIS_/TCHT_
 *             (ms913854/57/60), the TabCtrl_ macro bodies (not
 *             printed)
 *   dtpicker: DTM_ messages (aa452979..), DTN_ notifications, DTS_
 *             styles, MCSC_/GDTR_/GDT_ (names, values held)
 *   monthcal: MCM_/MCN_ (aa452xxx), MCHT_ (ms911793), the MonthCal_
 *             macro bodies (not printed)
 *   treeview: TVM_/TVN_ (ms913xxx/aa45280x), TVIF_/TVIS_/TVHT_/TVI_
 *             (ms913992 etc.), the TreeView_ macro bodies (not
 *             printed)
 *   listview: LVM_/LVN_ (aa4534xx/ms931xxx), LVIF_/LVIS_/LVFI_/
 *             LVHT_/LVBKIF_/LVCDI_/LVA_ (aa453422..), the ListView_
 *             macro bodies (not printed)
 * ------------------------------------------------------------------ */

/* ================================================================== */
/* M94 (Shell book completion) message/macro records.
 *
 * The Shell-book gap survey (M94a) showed these Requirements rows
 * homed in Commctrl.h were never shipped.  Their pages print no
 * numeric message values (full-corpus grep; the desktop Win32
 * reference does not print them either -- checked 2026-09-10),
 * so per the hold policy every row below is RECORDED with its
 * printed wParam/lParam packing or prototype; none can #define
 * without inventing values (the M82/M92 name-list precedent).
 * Bodies/prototypes that reference the constants symbolically
 * are kept verbatim.  Print oddities noted inline.
 * ================================================================== */

/* aa453482 "LVM_SETICONSPACING": the page prints the name
 * "LVS_SETICONSPACING" (archive misprint).  Recorded there. */
/* ms911819 "MCN_SELECTNONE": the page prints "MCN_SELECT;"
 * (archive oddity).  Recorded there. */
/* ms933410 "TCN_SELCHANGING": the page prints "TCN_SELCHANGE
 * lpnmhdr = (LPNMHDR) lParam;" (archive oddity). */

/* aa453426 "LVGROUP": `typedef struct LVGROUP { UINT cbSize; UINT mask; LPWSTR pszHeader; int cchHeader; LPWSTR pszFooter; int cchFooter; int iGroupId; UINT stateMask; UINT state; UINT uAlign;} LVGROUP, *PLVGROUP;` -- all member
 * types resolve, so the structure compiles (32-bit size
 * TU-asserted by the M94 block in tests/host/tu_compile.c). */
typedef struct LVGROUP {
    UINT    cbSize;
    UINT    mask;
    LPWSTR  pszHeader;
    int     cchHeader;
    LPWSTR  pszFooter;
    int     cchFooter;
    int     iGroupId;
    UINT    stateMask;
    UINT    state;
    UINT    uAlign;
} LVGROUP, *PLVGROUP;

/* aa453427 "LVGROUPMETRICS": `typedef struct LVGROUPMETRICS { UINT cbSize; UINT mask; UINT Left; UINT Top; UINT Right; UINT Bottom; COLORREF crLeft; COLORREF crTop; COLORREF crRight; COLORREF crBottom; COLORREF crRightHeader; COLORREF crFooter;} LVGROUPMETRICS, *PLVGROUPMETRICS;` -- all member
 * types resolve, so the structure compiles (32-bit size
 * TU-asserted by the M94 block in tests/host/tu_compile.c). */
typedef struct LVGROUPMETRICS {
    UINT      cbSize;
    UINT      mask;
    UINT      Left;
    UINT      Top;
    UINT      Right;
    UINT      Bottom;
    COLORREF  crLeft;
    COLORREF  crTop;
    COLORREF  crRight;
    COLORREF  crBottom;
    COLORREF  crRightHeader;
    COLORREF  crFooter;
} LVGROUPMETRICS, *PLVGROUPMETRICS;

/* aa453539 "LVSETINFOTIP": `typedef struct LVSETINFOTIP { UINT cbSize; DWORD dwFlags; LPWSTR pszText; int iItem; int iSubItem;} LVSETINFOTIP, *PLVSETINFOTIP;` -- all member
 * types resolve, so the structure compiles (32-bit size
 * TU-asserted by the M94 block in tests/host/tu_compile.c). */
typedef struct LVSETINFOTIP {
    UINT    cbSize;
    DWORD   dwFlags;
    LPWSTR  pszText;
    int     iItem;
    int     iSubItem;
} LVSETINFOTIP, *PLVSETINFOTIP;

/* ------------------------------------------------------------------ */
/* Date and Time Picker control (DTM_/DTN_/DateTime_) */
/* ------------------------------------------------------------------ */

/* aa452977 "DTM_GETMCCOLOR": `DTM_GETMCCOLOR wParam = (WPARAM)(INT)iColor;lParam = 0;` */

/* aa452978 "DTM_GETMCFONT": `DTM_GETMCFONT wParam = 0;lParam = 0;` */

/* aa452979 "DTM_GETMONTHCAL": `DTM_GETMONTHCAL wParam = 0;lParam = 0;` */

/* aa452980 "DTM_GETRANGE": `DTM_GETRANGE wParam = 0;lParam = (LPARAM) lpSysTimeArray;` */

/* aa452981 "DTM_GETSYSTEMTIME": `DTM_GETSYSTEMTIME wParam = 0;lParam = (LPARAM)lpSysTime;` */

/* aa452982 "DTM_SETFORMAT": `DTM_SETFORMAT wParam = 0;lParam = (LPARAM)lpszFormat;` */

/* aa452983 "DTM_SETMCCOLOR": `DTM_SETMCCOLOR wParam = (WPARAM)(INT)iColor;lParam = (LPARAM)(COLORREF)clr;` */

/* aa452984 "DTM_SETMCFONT": `DTM_SETMCFONT wParam = (WPARAM)(HFONT)hFont;lParam = (LPARAM) MAKELONG(fRedraw, 0);` */

/* aa452985 "DTM_SETRANGE": `DTM_SETRANGE wParam = (WPARAM)flags;lParam = (LPARAM)lpSysTimeArray;` */

/* aa452986 "DTM_SETSYSTEMTIME": `DTM_SETSYSTEMTIME wParam = (WPARAM)flag;lParam = (LPARAM)lpSysTime;` */

/* aa452987 "DTN_CLOSEUP": `DTN_CLOSEUP lpNmhdr = (LPNMHDR)lParam;` */

/* aa452988 "DTN_DATETIMECHANGE": `DTN_DATETIMECHANGE lpChange = (LPNMDATETIMECHANGE)lParam;` */

/* aa452989 "DTN_DROPDOWN": `DTN_DROPDOWN lpNmhdr = (LPNMHDR)lParam;` */

/* aa452990 "DTN_FORMAT": `DTN_FORMAT lpNMFormat = (LPNMDATETIMEFORMAT)lParam;` */

/* aa452991 "DTN_FORMATQUERY": `DTN_FORMATQUERY lpDTFormatQuery = (LPNMDATETIMEFORMATQUERY)lParam;` */

/* aa452992 "DTN_USERSTRING": `DTN_USERSTRING lpDTstring = (LPNMDATETIMESTRING)lParam;` */

/* aa452993 "DTN_WMKEYDOWN": `DTN_WMKEYDOWNlpDTKeystroke = (LPNMDATETIMEWMKEYDOWN)lParam;` */

/* ms908198 "DateTime_GetMonthCal": `HWND DateTime_GetMonthCal( HWNDhwndDP);` */

/* ms908199 "DateTime_GetMonthCalColor": `COLORREF DateTime_GetMonthCalColor(HWNDhwndDP, int iColor);` */

/* ms908200 "DateTime_GetMonthCalFont": `HFONT DateTime_GetMonthCalFont(HWNDhwndDP);` */

/* ms908202 "DateTime_GetRange": `DWORD DateTime_GetRange(HWNDhwndDT, LPSYSTEMTIMElpSysTimeArray);` */

/* ms908203 "DateTime_GetSystemtime": `DWORD DateTime_GetSystemtime(HWNDhwndDP, LPSYSTEMTIMElpSysTime);` */

/* ms908204 "DateTime_SetFormat": `BOOL DateTime_SetFormat(HWNDhwndDT, LPCTSTRlpszFormat);` */

/* ms908205 "DateTime_SetMonthCalColor": `COLORREF DateTime_SetMonthCalColor(HWNDhwndDP, intiColor, COLORREFclr);` */

/* ms908206 "DateTime_SetMonthCalFont": `void DateTime_SetMonthCalFont(HWND hwndDP,HFONThFont,LPARAM MAKELONG(fRedraw, 0));` */

/* ms908207 "DateTime_SetRange": `BOOL DateTime_SetRange(HWNDhwndDT,DWORDflags,LPSYSTEMTIMElpSysTimeArray);` */

/* ms908208 "DateTime_SetSystemtime": `BOOL DateTime_SetSystemtime(HWND hwndDT,DWORDflag,LPSYSTEMTIMElpSysTime);` */

/* ------------------------------------------------------------------ */
/* Header control (HDM_/HDN_/Header_) */
/* ------------------------------------------------------------------ */

/* ms929883 "HDM_CREATEDRAGIMAGE": `HDM_CREATEDRAGIMAGEwParam = (WPARAM)(int)iIndex;lParam= 0;` */

/* ms929884 "HDM_DELETEITEM": `HDM_DELETEITEMwParam = (WPARAM)(int)index;lParam= 0;` */

/* ms929885 "HDM_GETIMAGELIST": `HDM_GETIMAGELISTwParam= 0;lParam= 0;` */

/* ms929887 "HDM_GETITEMCOUNT": `HDM_GETITEMCOUNTwParam= 0;lParam= 0;` */

/* ms929889 "HDM_GETITEMRECT": `HDM_GETITEMRECTwParam = (WPARAM)(int)iIndex;lParam = (LPARAM)lpItemRect;` */

/* ms929890 "HDM_GETORDERARRAY": `HDM_GETORDERARRAYwParam = (WPARAM)(int)iSize;lParam = (LPARAM)lpiArray;` */

/* ms929891 "HDM_HITTEST": `HDM_HITTESTwParam= 0;lParam = (LPARAM)(HD_HITTESTINFOFAR*)phdhti;` */

/* ms929892 "HDM_INSERTITEM": `HDM_INSERTITEMwParam = (WPARAM)(int)index;lParam = (LPARAM)(constHD_ITEMFAR*)phdi;` */

/* ms929893 "HDM_LAYOUT": `HDM_LAYOUTwParam= 0;lParam = (LPARAM)(HD_LAYOUTFAR*)playout;` */

/* ms929894 "HDM_ORDERTOINDEX": `HDM_ORDERTOINDEXwParam = (WPARAM)iOrder;lParam= 0;` */

/* ms929895 "HDM_SETHOTDIVIDER": `HDM_SETHOTDIVIDERwParam = (WPARAM)flag;lParam = (LPARAM)dwInputValue;` */

/* ms929896 "HDM_SETIMAGELIST": `HDM_SETIMAGELISTwParam= 0;lParam = (LPARAM)himl;` */

/* ms929897 "HDM_SETITEM": `HDM_SETITEMwParam = (WPARAM)(int)iIndex;lParam = (LPARAM)(constHD_ITEMFAR*)phdItem;` */

/* ms929898 "HDM_SETORDERARRAY": `HDM_SETORDERARRAYwParam = (WPARAM)(int)iSize;lParam = (LPARAM)lpiArray;` */

/* ms929899 "HDN_BEGINDRAG": `HDN_BEGINDRAGpNMHeader = (LPNMHEADER)lParam;` */

/* ms929900 "HDN_BEGINTRACK": `HDN_BEGINTRACKphdn=(HD_NOTIFYFAR*)lParam;` */

/* ms929901 "HDN_DIVIDERDBLCLICK": `HDN_DIVIDERDBLCLICKphdn=(HD_NOTIFYFAR*)lParam;` */

/* ms929902 "HDN_ENDDRAG": `HDN_ENDDRAGpNMHeader = (LPNMHEADER)lParam;` */

/* ms929903 "HDN_ENDTRACK": `HDN_ENDTRACKphdn=(HD_NOTIFYFAR*)lParam;` */

/* ms929904 "HDN_GETDISPINFO": `HDN_GETDISPINFOpDispInfo = (LPNMHDDISPINFO)lParam;` */

/* ms929905 "HDN_ITEMCHANGED": `HDN_ITEMCHANGEDphdr=(HD_NOTIFYFAR*)lParam;` */

/* ms929906 "HDN_ITEMCHANGING": `HDN_ITEMCHANGINGphdr=(HD_NOTIFYFAR*)lParam;` */

/* ms929907 "HDN_ITEMCLICK": `HDN_ITEMCLICKphdr=(HD_NOTIFYFAR*)lParam;` */

/* ms929908 "HDN_ITEMDBLCLICK": `HDN_ITEMDBLCLICKpnmhdr=(NMHDRFAR*)lParam;` */

/* ms929909 "HDN_TRACK": `HDN_TRACKphdr=(HD_NOTIFYFAR*)lParam;` */

/* ms929911 "Header_CreateDragImage" (printed verbatim; references held value-less constants):
 *   #define Header_CreateDragImage(hwnd, i) \ (HIMAGELIST)SNDMSG((hwnd), HDM_CREATEDRAGIMAGE, (WPARAM)i )
 */

/* ms929912 "Header_DeleteItem" (printed verbatim; references held value-less constants):
 *   #define Header_DeleteItem(hwndHD, i) \ (BOOL)SNDMSG((hwndHD), HDM_DELETEITEM, (WPARAM)(int)(i), 0L)
 */

/* ms929913 "Header_GetImageList" (printed verbatim; references held value-less constants):
 *   #define Header_GetImageList(hwnd) \ (HIMAGELIST)SNDMSG((hwnd), HDM_GETIMAGELIST, 0, 0)
 */

/* ms929914 "Header_GetItem" (printed verbatim; references held value-less constants):
 *   #define Header_GetItem(hwndHD, i, phdi) \ (BOOL)SNDMSG((hwndHD), HDM_GETITEM, (WPARAM)(int)(i), \ (LPARAM)(HD_ITEM FAR*)(phdi))
 */

/* ms929915 "Header_GetItemCount" (printed verbatim; references held value-less constants):
 *   #define Header_GetItemCount(hwndHD) \ (int)SNDMSG((hwndHD), HDM_GETITEMCOUNT, 0, 0L)
 */

/* ms929916 "Header_GetItemRect" (printed verbatim; references held value-less constants):
 *   #define Header_GetItemRect(hwnd, iItem, lprc) \ (BOOL)SNDMSG((hwnd), HDM_GETITEMRECT, (WPARAM)iItem, (LPARAM)lprc)
 */

/* ms929917 "Header_GetOrderArray" (printed verbatim; references held value-less constants):
 *   #define Header_GetOrderArray(hwnd, iCount, lpi) \ (BOOL)SNDMSG((hwnd), HDM_GETORDERARRAY, (WPARAM)iCount, (LPARAM)lpi)
 */

/* ms929918 "Header_InsertItem" (printed verbatim; references held value-less constants):
 *   #define Header_InsertItem(hwndHD, i, phdi) \ (int)SNDMSG((hwndHD), HDM_INSERTITEM, (WPARAM)(int)(i), \ (LPARAM)(const HD_ITEM FAR*)(phdi))
 */

/* ms929919 "Header_Layout" (printed verbatim; references held value-less constants):
 *   #define Header_Layout(hwndHD, playout) \ (BOOL)SNDMSG((hwndHD), HDM_LAYOUT, 0, \ (LPARAM)(HD_LAYOUT FAR*)(playout))
 */

/* ms929920 "Header_OrderToIndex" (printed verbatim; references held value-less constants):
 *   #define Header_OrderToIndex(hwnd, i) \ (int)SNDMSG((hwnd), HDM_ORDERTOINDEX, (WPARAM)i, 0)
 */

/* ms929921 "Header_SetHotDivider" (printed verbatim; references held value-less constants):
 *   #define Header_SetHotDivider(hwnd, fPos, dw) \ (int)SNDMSG((hwnd), HDM_SETHOTDIVIDER, (WPARAM)fPos, (LPARAM)dw)
 */

/* ms929922 "Header_SetImageList" (printed verbatim; references held value-less constants):
 *   #define Header_SetImageList(hwnd, himl) \ (HIMAGELIST)SNDMSG((hwnd), HDM_SETIMAGELIST, 0, (LPARAM)himl)
 */

/* ms929923 "Header_SetItem" (printed verbatim; references held value-less constants):
 *   #define Header_SetItem(hwndHD, i, phdi) \ (BOOL)SNDMSG((hwndHD), HDM_SETITEM, (WPARAM)(int)(i), \ (LPARAM)(const HD_ITEM FAR*)(phdi))
 */

/* ms929924 "Header_SetOrderArray" (printed verbatim; references held value-less constants):
 *   #define Header_SetOrderArray(hwnd, iCount, lpi) \ (BOOL)SNDMSG((hwnd), HDM_SETORDERARRAY, \ (WPARAM)iCount, (LPARAM)lpi)
 */

/* ------------------------------------------------------------------ */
/* List-View control (LVM_/LVN_/ListView_) */
/* ------------------------------------------------------------------ */

/* aa453431 "LVM_APPROXIMATEVIEWRECT": `LVM_APPROXIMATEVIEWRECT wParam= (WPARAM)(INT)iCount;lParam=(LPARAM) MAKELPARAM(cx,cy);` */

/* aa453432 "LVM_ARRANGE": `LVM_ARRANGE wParam=(WPARAM)(int)code;lParam= 0;` */

/* aa453433 "LVM_CREATEDRAGIMAGE": `LVM_CREATEDRAGIMAGE wParam=(WPARAM)(int)iItem;lParam=(LPARAM)(LPPOINT)lpptUpLeft;` */

/* aa453434 "LVM_DELETEALLITEMS": `LVM_DELETEALLITEMS wParam= 0;lParam= 0;` */

/* aa453435 "LVM_DELETECOLUMN": `LVM_DELETECOLUMN wParam=(WPARAM)(int)iCol;lParam= 0;` */

/* aa453436 "LVM_DELETEITEM": `LVM_DELETEITEM wParam= (WPARAM)(int)iItem;lParam= 0;` */

/* aa453437 "LVM_EDITLABEL": `LVM_EDITLABEL wParam=(WPARAM)(int)iItem;lParam= 0;` */

/* aa453497 "LVM_ENABLEGROUPVIEW": `lResult = SendMessage( (HWND) hWndControl, (UINT) LVM_ENABLEGROUPVIEW, (WPARAM) wParam, // = (WPARAM) (BOOL) fEnable; (LPARAM) lParam // = (LPARAM) (LPARAM) lParam;)` */

/* aa453438 "LVM_ENSUREVISIBLE": `LVM_ENSUREVISIBLE wParam= (WPARAM)(int)i;lParam=(LPARAM)(BOOL)fPartialOK;` */

/* aa453439 "LVM_FINDITEM": `LVM_FINDITEM wParam= (WPARAM)(int)iStart;lParam=(LPARAM)(const LV_FINDINFO FAR *)plvfi;` */

/* aa453440 "LVM_GETBKCOLOR": `LVM_GETBKCOLOR wParam= 0;lParam= 0;` */

/* aa453498 "LVM_GETBKIMAGE": `lResult = SendMessage( (HWND) hWndControl, (UINT) LVM_GETBKIMAGE, (WPARAM) wParam, // = 0; not used, must be zero (LPARAM) lParam // = (LPARAM) (LPLVBKIMAGE) plvbki;)` */

/* aa453441 "LVM_GETCALLBACKMASK": `LVM_GETCALLBACKMASK wParam= 0;lParam= 0;` */

/* aa453442 "LVM_GETCOLUMN": `LVM_GETCOLUMN wParam=(WPARAM)(int)iCol;lParam= (LPARAM)(LV_COLUMN FAR *)pcol;` */

/* aa453443 "LVM_GETCOLUMNORDERARRAY": `LVM_GETCOLUMNORDERARRAY wParam=(WPARAM) (int)iCount;lParam=(LPARAM)lpiArray;` */

/* aa453445 "LVM_GETCOLUMNWIDTH": `LVM_GETCOLUMNWIDTH wParam= (WPARAM)(int)iCol;lParam= 0;` */

/* aa453446 "LVM_GETCOUNTPERPAGE": `LVM_GETCOUNTPERPAGE wParam= 0;lParam= 0;` */

/* aa453447 "LVM_GETEDITCONTROL": `LVM_GETEDITCONTROL wParam= 0;lParam= 0;` */

/* aa453448 "LVM_GETEXTENDEDLISTVIEWSTYLE": `LVM_GETEXTENDEDLISTVIEWSTYLE wParam= 0;lParam= 0;` */

/* aa453499 "LVM_GETGROUPCOUNT": `lResult = SendMessage( (hwnd) hwndControl, LVM_GETGROUPCOUNT, (WPARAM) wparam, (LPARAM) lparam)` */

/* aa453500 "LVM_GETGROUPINFO": `lResult = SendMessage( (HWND) hWndControl, (UINT) LVM_GETGROUPINFO, (WPARAM) wParam, // = (WPARAM) (int) iGroupId; (LPARAM) lParam // = (LPARAM) (PLVGROUP) pgrp;)` */

/* aa453501 "LVM_GETGROUPINFOBYINDEX": `lResult = SendMessage( (hwnd) hwndControl, LVM_GETGROUPINFOBYINDEX, (WPARAM) iIndex, (LPARAM) pgrp)` */

/* aa453502 "LVM_GETGROUPMETRICS": `lResult = SendMessage( (HWND) hWndControl, (UINT) LVM_GETGROUPMETRICS, (WPARAM) wParam, // = (WPARAM) (WPARAM) wParam; (LPARAM) lParam // = (LPARAM) (PLVGROUPMETRICS) pGroupMetrics;)` */

/* aa453449 "LVM_GETHEADER": `LVM_GETHEADER wParam= 0;lParam= 0;` */

/* aa453450 "LVM_GETIMAGELIST": `LVM_GETIMAGELIST wParam=(WPARAM)(int)iImageList;lParam= 0;` */

/* aa453451 "LVM_GETISEARCHSTRING": `LVM_GETISEARCHSTRING wParam= 0;lParam= (LPARAM)(LPSTR) lpsz;` */

/* aa453452 "LVM_GETITEM": `LVM_GETITEM wParam= 0;lParam=(LPARAM)(LVITEM FAR*)pitem;` */

/* aa453453 "LVM_GETITEMCOUNT": `LVM_GETITEMCOUNT wParam= 0;lParam= 0;` */

/* aa453454 "LVM_GETITEMPOSITION": `LVM_GETITEMPOSITION wParam=(WPARAM)(int)i;lParam=(LPARAM)(POINT FAR *)ppt;` */

/* aa453455 "LVM_GETITEMRECT": `LVM_GETITEMRECT wParam= (WPARAM)(int)i;lParam= (LPARAM)(LPRECT)prc;` */

/* aa453456 "LVM_GETITEMSPACING": `LVM_GETITEMSPACING wParam= (WPARAM)(BOOL)fSmall;lParam= 0;` */

/* aa453457 "LVM_GETITEMSTATE": `LVM_GETITEMSTATE wParam= (WPARAM)(int)i;lParam= (LPARAM)(UINT)mask;` */

/* aa453458 "LVM_GETITEMTEXT": `LVM_GETITEMTEXT wParam = (WPARAM)(int)iItem;lParam= (LPARAM)(LVITEM FAR *)pitem;` */

/* aa453459 "LVM_GETNEXTITEM": `LVM_GETNEXTITEM wParam = (WPARAM)(int)iStart;lParam = MAKELPARAM((UINT)flags,0);` */

/* aa453460 "LVM_GETNUMBEROFWORKAREAS": `LVM_GETNUMBEROFWORKAREAS wParam = 0; lParam = (LPARAM) (LPUINT) lpuWorkAreas;` */

/* aa453461 "LVM_GETORIGIN": `LVM_GETORIGIN wParam = 0; lParam= (LPARAM)(LPPOINT)lpptOrg;` */

/* aa453462 "LVM_GETSELECTEDCOUNT": `LVM_GETSELECTEDCOUNT wParam= 0;lParam= 0;` */

/* aa453463 "LVM_GETSELECTIONMARK": `LVM_GETSELECTIONMARK Param= 0;lParam= 0;` */

/* aa453464 "LVM_GETSTRINGWIDTH": `LVM_GETSTRINGWIDTH wParam= 0;lParam=(LPARAM)(LPCSTR)psz;` */

/* aa453465 "LVM_GETSUBITEMRECT": `LVM_GETSUBITEMRECT wParam= (WPARAM)(int)iItem;lParam=(LPARAM)(LPRECT)lpRect;` */

/* aa453466 "LVM_GETTEXTBKCOLOR": `LVM_GETTEXTBKCOLOR wParam = 0;lParam = 0;` */

/* aa453467 "LVM_GETTEXTCOLOR": `LVM_GETTEXTCOLOR wParam= 0;lParam= 0;` */

/* aa453503 "LVM_GETTOOLTIPS": `lResult = SendMessage( (HWND) hWndControl, (UINT) LVM_GETTOOLTIPS, (WPARAM) wParam, // = 0; not used, must be zero (LPARAM) lParam // = 0; not used, must be zero)` */

/* aa453468 "LVM_GETTOPINDEX": `LVM_GETTOPINDEX wParam= 0;lParam= 0;` */

/* aa453469 "LVM_GETVIEWRECT": `LVM_GETVIEWRECT wParam= 0;lParam= (LPARAM)(RECT FAR *)prc;` */

/* aa453470 "LVM_GETWORKAREAS": `LVM_GETWORKAREAS wParam = (WPARAM) (int) nWorkAreas; lParam = (LPARAM) (LPRECT) lprc;` */

/* aa453504 "LVM_HASGROUP": `lResult = SendMessage( (HWND) hWndControl, (UINT) LVM_HASGROUP, (WPARAM) wParam, // = (WPARAM) (int) dwGroupId; (LPARAM) lParam // = (LPARAM) (LPARAM) lParam;)` */

/* aa453471 "LVM_HITTEST": `LVM_HITTEST wParam = 0;` */

/* aa453472 "LVM_INSERTCOLUMN": `LVM_INSERTCOLUMN wParam = (WPARAM)(int)iCol;lParam = (LPARAM)(const LV_COLUMN FAR *)pcol;` */

/* aa453505 "LVM_INSERTGROUP": `lResult = SendMessage( (HWND) hWndControl, (UINT) LVM_INSERTGROUP, (WPARAM) wParam, // = (WPARAM) (int) index; (LPARAM) lParam // = (LPARAM) (PLVGROUP) pgrp;)` */

/* aa453506 "LVM_INSERTGROUPSORTED": `lResult = SendMessage( (HWND) hWndControl, (UINT) LVM_INSERTGROUPSORTED, (WPARAM) wParam, // = (WPARAM) (PLVINSERTGROUPSORTED) structInsert; (LPARAM) lParam // = (LPARAM) (LPARAM) lParam;)` */

/* aa453473 "LVM_INSERTITEM": `LVM_INSERTITEM wParam = 0;lParam = (LPARAM)(const LVITEM FAR *)pitem;` */

/* aa453507 "LVM_ISGROUPVIEWENABLED": `lResult = SendMessage( (HWND) hWndControl, (UINT) LVM_ISGROUPVIEWENABLED, (WPARAM) wParam, (LPARAM) lParam)` */

/* aa453508 "LVM_MAPIDTOINDEX": `lResult = SendMessage( (HWND) hWndControl, (UINT) LVM_MAPIDTOINDEX, (WPARAM) wParam, // = (WPARAM) (UINT) id; (LPARAM) lParam // = 0; not used, must be zero)` */

/* aa453509 "LVM_MAPINDEXTOID": `lResult = SendMessage( (HWND) hWndControl, (UINT) LVM_MAPINDEXTOID, (WPARAM) wParam, // = (WPARAM) (UINT) index; (LPARAM) lParam // = 0; not used, must be zero)` */

/* aa453510 "LVM_MOVEGROUP": `lResult = SendMessage( (HWND) hWndControl, (UINT) LVM_MOVEGROUP, (WPARAM) wParam, // = (WPARAM) (int) iGroupId; (LPARAM) lParam // = (LPARAM) (int) toIndex;)` */

/* aa453511 "LVM_MOVEITEMTOGROUP": `lResult = SendMessage( (HWND) hWndControl, (UINT) LVM_MOVEITEMTOGROUP, (WPARAM) wParam, // = (WPARAM) (int) idItemFrom; (LPARAM) lParam // = (LPARAM) (int) idGroupTo;)` */

/* aa453474 "LVM_REDRAWITEMS": `lResult = SendMessage( (HWND) hWndControl, (UINT) LVM_REDRAWITEMS, (WPARAM) wParam, // = (WPARAM) (int) iFirst; (LPARAM) lParam // = (LPARAM) (int) iLast; );)` */

/* aa453512 "LVM_REMOVEALLGROUPS": `lResult = SendMessage( (HWND) hWndControl, (UINT) LVM_REMOVEALLGROUPS, (WPARAM) wParam, // = (WPARAM) (WPARAM) wParam; (LPARAM) lParam // = (LPARAM) (LPARAM) lParam;)` */

/* aa453513 "LVM_REMOVEGROUP": `lResult = SendMessage( (HWND) hWndControl, (UINT) LVM_REMOVEGROUP, (WPARAM) wParam, // = (WPARAM) (int) iGroupId; (LPARAM) lParam // = (LPARAM) (LPARAM) lParam;)` */

/* aa453475 "LVM_SCROLL": `LVM_SCROLL wParam = (WPARAM)(int)dx;lParam = (LPARAM)(int) dy;` */

/* aa453476 "LVM_SETBKCOLOR": `LVM_SETBKCOLOR wParam = 0;lParam = (LPARAM)(COLORREF)clrBk;` */

/* aa453514 "LVM_SETBKIMAGE": `lResult = SendMessage( (HWND) hWndControl, (UINT) LVM_SETBKIMAGE, (WPARAM) wParam, // = 0; not used, must be zero (LPARAM) lParam // = (LPARAM) (LPLVBKIMAGE) plvbki;)` */

/* aa453477 "LVM_SETCALLBACKMASK": `LVM_SETCALLBACKMASK wParam = (WPARAM)(UINT) mask;lParam = 0;` */

/* aa453478 "LVM_SETCOLUMN": `LVM_SETCOLUMN wParam = (WPARAM)(int)iCol;lParam = (LPARAM)(const LV_COLUMN FAR *)pcol;` */

/* aa453479 "LVM_SETCOLUMNORDERARRAY": `LVM_SETCOLUMNORDERARRAY wParam = (WPARAM) (int)iCount;lParam = (LPARAM) (LPINT)lpiArray;` */

/* aa453480 "LVM_SETCOLUMNWIDTH": `LVM_SETCOLUMNWIDTH wParam = (WPARAM)(int)iCol;lParam = MAKELPARAM((int)cx, 0);` */

/* aa453481 "LVM_SETEXTENDEDLISTVIEWSTYLE": `LVM_SETEXTENDEDLISTVIEWSTYLE wParam = (WPARAM)dwExMask;lParam = (LPARAM)dwExStyle;` */

/* aa453515 "LVM_SETGROUPINFO": `lResult = SendMessage( (HWND) hWndControl, (UINT) LVM_SETGROUPINFO, (WPARAM) wParam, // = (WPARAM) (int) iGroupId; (LPARAM) lParam // = (LPARAM) (PLVGROUP) pgrp;)` */

/* aa453516 "LVM_SETGROUPMETRICS": `lResult = SendMessage( (HWND) hWndControl, (UINT) LVM_SETGROUPMETRICS, (WPARAM) wParam, // = (WPARAM) (WPARAM) wParam; (LPARAM) lParam // = (LPARAM) (PLVGROUPMETRICS) pGroupMetrics;)` */

/* aa453482 "LVM_SETICONSPACING": `LVS_SETICONSPACING wParam = 0;lParam = (LPARAM) MAKELONG(cx,cy);` */

/* aa453483 "LVM_SETIMAGELIST": `LVM_SETIMAGELIST wParam = (WPARAM)(int) iImageList;lParam = (LPARAM)(HIMAGELIST)himl;` */

/* aa453517 "LVM_SETINFOTIP": `lResult = SendMessage( (HWND) hWndControl, // handle to destination control (UINT) LVM_SETINFOTIP, // message ID (WPARAM) wParam, // = 0; not used, must be zero (LPARAM) lParam // = (LPARAM) (PLVSETINFOTIP) plvSetInfoTip;)` */

/* aa453484 "LVM_SETITEM": `LVM_SETITEM wParam = 0;lParam = (LPARAM)(const LVITEM FAR *)pitem;` */

/* aa453485 "LVM_SETITEMCOUNT": `LVM_SETITEMCOUNT wParam = (WPARAM) (int)cItems;lParam = (LPARAM)dwFlags;` */

/* aa453486 "LVM_SETITEMPOSITION": `LVM_SETITEMPOSITION wParam = (LPARAM)(int)i;lParam = MAKELPARAM((int)x,(int)y );` */

/* aa453487 "LVM_SETITEMPOSITION32": `LVM_SETITEMPOSITION32 wParam = (WPARAM)(int)iItem;lParam = (LPARAM)(LPPOINT)lpptNewPos;` */

/* aa453488 "LVM_SETITEMSTATE": `LVM_SETITEMSTATE wParam = (WPARAM)(int)i;lParam = (LPARAM)(LVITEM FAR *)pitem;` */

/* aa453489 "LVM_SETITEMTEXT": `LVM_SETITEMTEXT wParam = (WPARAM)(int)i;lParam = (LPARAM)(LVITEM FAR *)pitem;` */

/* aa453490 "LVM_SETSELECTIONMARK": `LVM_SETSELECTIONMARK wParam = 0;lParam = (LPARAM)(INT)iIndex;` */

/* aa453491 "LVM_SETTEXTBKCOLOR": `LVM_SETTEXTBKCOLOR wParam = 0;lParam = (LPARAM)(COLORREF)clrText;` */

/* aa453492 "LVM_SETTEXTCOLOR": `LVM_SETTEXTCOLOR wParam = 0;lParam = (LPARAM)(COLORREF)clrText;` */

/* aa453518 "LVM_SETTOOLTIPS": `lResult = SendMessage( (HWND) hWndControl, (UINT) LVM_SETTOOLTIPS, (WPARAM) wParam, // = 0; not used, must be zero (LPARAM) lParam // = (LPARAM) (HWND) hwndToolTip;)` */

/* aa453493 "LVM_SETWORKAREAS": `LVM_SETWORKAREAS wParam = (WPARAM) (INT) nWorkAreas; lParam = (LPARAM) (LPRECT) lprc;` */

/* aa453519 "LVM_SORTGROUPS": `lResult = SendMessage( (HWND) hWndControl, (UINT) LVM_SORTGROUPS, (WPARAM) wParam, // = (WPARAM) (PFNLVGROUPCOMPARE) pfnGroupCompare; (LPARAM) lParam // = (LPARAM) (LPVOID) plv;)` */

/* aa453494 "LVM_SORTITEMS": `LVM_SORTITEMS wParam = (WPARAM)(LPARAM)lParamSort;lParam = (LPARAM)(PFNLVCOMPARE)pfnCompare;` */

/* aa453495 "LVM_SUBITEMHITTEST": `LVM_SUBITEMHITTEST wParam = 0;lParam = (LPARAM)(LVHITTESTINFO FAR *)pInfo;` */

/* aa453496 "LVM_UPDATE": `LVM_UPDATE wParam = (WPARAM)iItem;lParam = 0;` */

/* aa453520 "LVN_BEGINDRAG": `LVN_BEGINDRAG pnmv= (NM_LISTVIEW FAR *)lParam;` */

/* aa453521 "LVN_BEGINLABELEDIT": `LVN_BEGINLABELEDIT pdi= (LV_DISPINFO FAR *)lParam;` */

/* aa453522 "LVN_COLUMNCLICK": `LVN_COLUMNCLICK pnmv = (NM_LISTVIEW FAR *)lParam;` */

/* aa453523 "LVN_DELETEALLITEMS": `LVN_DELETEALLITEMS pnmv= (NM_LISTVIEW FAR *)lParam;` */

/* aa453524 "LVN_DELETEITEM": `LVN_DELETEITEM pnmv= (NM_LISTVIEW FAR *)lParam;` */

/* aa453525 "LVN_ENDDRAG": `LVN_ENDDRAG pnmv = (NM_LISTVIEW FAR *)lParam;` */

/* aa453526 "LVN_ENDLABELEDIT": `LVN_ENDLABELEDIT pdi= (LV_DISPINFO FAR *)lParam;` */

/* aa453527 "LVN_GETDISPINFO": `LVN_GETDISPINFO pnmv= (LV_DISPINFO FAR *)lParam;` */

/* aa453538 "LVN_GETINFOTIP": `LVN_GETINFOTIP pGetInfoTip = (LPNMLVGETINFOTIP)lParam;` */

/* aa453528 "LVN_INSERTITEM": `LVN_INSERTITEM pnmv= (NM_LISTVIEW FAR *)lParam;` */

/* aa453529 "LVN_ITEMACTIVATE": `LVN_ITEMACTIVATE lpnmlv = (LPNMLISTVIEW)lParam;` */

/* aa453530 "LVN_ITEMCHANGED": `LVN_ITEMCHANGED pnmv= (NM_LISTVIEW FAR *)lParam;` */

/* aa453531 "LVN_ITEMCHANGING": `LVN_ITEMCHANGING pnmv= (NM_LISTVIEW FAR *)lParam;` */

/* aa453532 "LVN_KEYDOWN": `LVN_KEYDOWN pnkd = (LV_KEYDOWN FAR *)lParam;` */

/* aa453533 "LVN_MARQUEEBEGIN": `LVN_MARQUEEBEGIN pnmv = (NM_LISTVIEW FAR *)lParam;` */

/* aa453534 "LVN_ODCACHEHINT": `LVN_ODCACHEHINT pCachehint = (NMLVCACHEHINT *)lParam;` */

/* aa453535 "LVN_ODFINDITEM": `LVN_ODFINDITEM pFindInfo = (PNMLVFINDITEM)lParam;` */

/* aa453536 "LVN_ODSTATECHANGED": `LVN_ODSTATECHANGED lpStateChange = (LPNMLVODSTATECHANGE)lParam;` */

/* aa453537 "LVN_SETDISPINFO": `LVN_SETDISPINFO pnmv= (LV_DISPINFO FAR *)lParam;` */

/* aa453304 "ListView_ApproximateViewRect": `DWORD ListView_ApproximateViewRect(HWNDhwndLV,int cx,int cy,int iCount );` */

/* aa453305 "ListView_Arrange": `BOOLListView_Arrange( HWNDhwnd, UINTcode );` */

/* aa453306 "ListView_CreateDragImage": `HIMAGELISTListView_CreateDragImage( HWNDhwnd, intiItem,LPPOINTlpptUpLeft );` */

/* aa453307 "ListView_DeleteAllItems": `BOOLListView_DeleteAllItems( HWNDhwnd );` */

/* aa453308 "ListView_DeleteColumn": `BOOLListView_DeleteColumn( HWNDhwnd, intiCol );` */

/* aa453309 "ListView_DeleteItem": `BOOLListView_DeleteItem( HWNDhwnd, intiItem );` */

/* aa453310 "ListView_EditLabel": `HWNDListView_EditLabel( HWNDhwnd, intiItem );` */

/* aa453382 "ListView_EnableGroupView": `int ListView_EnableGroupView( HWND hwnd, BOOL fEnable);` */

/* aa453311 "ListView_EnsureVisible": `BOOLListView_EnsureVisible( HWNDhwnd, inti, BOOLfPartialOK );` */

/* aa453312 "ListView_FindItem": `intListView_FindItem( HWNDhwnd, intiStart, constLV_FINDINFOFAR* plvfi );` */

/* aa453313 "ListView_GetBkColor": `COLORREFListView_GetBkColor( HWNDhwnd );` */

/* aa453383 "ListView_GetBkImage": `BOOL ListView_GetBkImage( HWND hwndLV, LPLVBKIMAGE plvbki);` */

/* aa453314 "ListView_GetCallbackMask": `UINTListView_GetCallbackMask( HWNDhwnd );` */

/* aa453315 "ListView_GetCheckState": `BOOL ListView_GetCheckState(HWND hwndLV, UINT iIndex );` */

/* aa453316 "ListView_GetColumn": `BOOLListView_GetColumn( HWNDhwnd, intiCol, LV_COLUMNFAR*pcol );` */

/* aa453317 "ListView_GetColumnOrderArray": `BOOL ListView_GetColumnOrderArray(HWND hwndLV, int iCount, int* lpiArray );` */

/* aa453318 "ListView_GetColumnWidth": `intListView_GetColumnWidth( HWNDhwnd, intiCol );` */

/* aa453319 "ListView_GetCountPerPage": `intListView_GetCountPerPage( HWNDhwnd );` */

/* aa453320 "ListView_GetEditControl": `HWNDListView_GetEditControl( HWNDhwnd );` */

/* aa453321 "ListView_GetExtendedListViewStyle": `DWORD ListView_GetExtendedListViewStyle(HWND hwndLV );` */

/* aa453385 "ListView_GetGroupCount": `int ListView_GetGroupCount( HWND hwnd);` */

/* aa453386 "ListView_GetGroupInfo": `int ListView_GetGroupInfo( HWND hwnd, int iGroupId, PLVGROUP pgrp);` */

/* aa453387 "ListView_GetGroupInfoByIndex": `BOOL ListView_GetGroupInfoByIndex( HWND hwnd, int iIndex, PLVGROUP pgrp)` */

/* aa453388 "ListView_GetGroupMetrics": `ListView_GetGroupMetrics( HWND hwnd, PLVGROUPMETRICS pGroupMetrics);` */

/* aa453322 "ListView_GetHeader": `HWND ListView_GetHeader(hwndLV );` */

/* aa453324 "ListView_GetISearchString": `BOOLListView_GetISearchString( HWNDhwnd, LPSTRlpsz );` */

/* aa453323 "ListView_GetImageList": `HIMAGELISTListView_GetImageList( HWNDhwnd, intiImageList );` */

/* aa453325 "ListView_GetItem": `BOOLListView_GetItem( HWNDhwnd, LVITEMFAR* pitem );` */

/* aa453326 "ListView_GetItemCount": `intListView_GetItemCount( HWNDhwnd );` */

/* aa453327 "ListView_GetItemPosition": `BOOLListView_GetItemPosition( HWNDhwnd, inti, POINTFAR* ppt );` */

/* aa453328 "ListView_GetItemRect": `BOOLListView_GetItemRect( HWNDhwnd, inti, RECTFAR* prc, intcode );` */

/* aa453329 "ListView_GetItemSpacing": `DWORDListView_GetItemSpacing( HWNDhwnd, BOOLfSmall );` */

/* aa453340 "ListView_GetItemState": `UINTWINAPIListView_GetItemState( HWNDhwnd, inti, UINTmask );` */

/* aa453341 "ListView_GetItemText": `voidWINAPIListView_GetItemText( HWNDhwnd, intiItem, intiSubItem,LPSTRpszText, intcchTextMax );` */

/* aa453342 "ListView_GetNextItem": `intListView_GetNextItem( HWNDhwnd, intiStart, UINTflags );` */

/* aa453344 "ListView_GetOrigin": `BOOLListView_GetOrigin( HWNDhwnd, LPPOINTlpptOrg );` */

/* aa453345 "ListView_GetSelectedCount": `UINTListView_GetSelectedCount( HWNDhwnd );` */

/* aa453346 "ListView_GetSelectionMark": `INT ListView_GetSelectionMark(HWND hwndLV);` */

/* aa453347 "ListView_GetStringWidth": `intListView_GetStringWidth( HWNDhwnd, LPCSTRpsz );` */

/* aa453348 "ListView_GetSubItemRect": `BOOL ListView_GetSubItemRect( HWND hwndLV, int iItem, int iSubItem, int code, LPRECT lpRect );` */

/* aa453349 "ListView_GetTextBkColor": `COLORREFListView_GetTextBkColor( HWNDhwnd );` */

/* aa453350 "ListView_GetTextColor": `COLORREFListView_GetTextColor( HWNDhwnd );` */

/* aa453389 "ListView_GetToolTips": `HWND ListView_GetToolTips( HWND hwnd);` */

/* aa453351 "ListView_GetTopIndex": `intListView_GetTopIndex( HWNDhwnd );` */

/* aa453352 "ListView_GetViewRect": `BOOLListView_GetViewRect( HWNDhwnd, RECTFAR* prc );` */

/* aa453390 "ListView_HasGroup": `BOOL ListView_HasGroup( HWND hwnd, int dwGroupId);` */

/* aa453354 "ListView_HitTest": `intListView_HitTest( HWNDhwnd, LV_HITTESTINFOFAR* pinfo );` */

/* aa453355 "ListView_InsertColumn": `intListView_InsertColumn( HWNDhwnd, intiCol, constLV_COLUMNFAR* pcol );` */

/* aa453391 "ListView_InsertGroup": `int ListView_InsertGroup( HWND hwnd, int index, PLVGROUP pgrp);` */

/* aa453392 "ListView_InsertGroupSorted": `ListView_InsertGroupSorted( HWND hwnd, PLVINSERTGROUPSORTED structInsert, int index);` */

/* aa453356 "ListView_InsertItem": `intListView_InsertItem( HWNDhwnd, const LVITEMFAR* pitem );` */

/* aa453393 "ListView_IsGroupViewEnabled": `BOOL ListView_IsGroupViewEnabled( HWND hwnd);` */

/* aa453394 "ListView_MapIDToIndex": `UINT ListView_MapIDToIndex( HWND hwnd, UINT id);` */

/* aa453395 "ListView_MapIndexToID": `UINT ListView_MapIndexToID( HWND hwnd, UINT index);` */

/* aa453396 "ListView_MoveGroup": `ListView_MoveGroup( HWND hwnd, int iGroupId, int toIndex);` */

/* aa453397 "ListView_MoveItemToGroup": `ListView_MoveItemToGroup( HWND hwnd, int idItemFrom, int idGroupTo);` */

/* aa453357 "ListView_RedrawItems": `BOOLListView_RedrawItems( HWNDhwnd, intiFirst, intiLast );` */

/* aa453398 "ListView_RemoveAllGroups": `ListView_RemoveAllGroups( HWND hwnd);` */

/* aa453399 "ListView_RemoveGroup": `int ListView_RemoveGroup( HWND hwnd, int iGroupId);` */

/* aa453358 "ListView_Scroll": `BOOLListView_Scroll( HWNDhwnd, intdx, intdy );` */

/* aa453359 "ListView_SetBkColor": `BOOLListView_SetBkColor( HWNDhwnd, COLORREFclrBk );` */

/* aa453400 "ListView_SetBkImage": `BOOL ListView_SetBkImage( HWND hwndLV, LPLVBKIMAGE plvbki);` */

/* aa453360 "ListView_SetCallbackMask": `BOOLListView_SetCallbackMask( HWNDhwnd, UINTmask );` */

/* aa453361 "ListView_SetColumn": `BOOLListView_SetColumn( HWNDhwnd, intiCol, LV_COLUMNFAR* pcol );` */

/* aa453362 "ListView_SetColumnOrderArray": `BOOL ListView_SetColumnOrderArray(HWND hwndLV, int iCount, int* lpiArray);` */

/* aa453363 "ListView_SetColumnWidth": `BOOLListView_SetColumnWidth( HWNDhwnd, intiCol, intcx);` */

/* aa453364 "ListView_SetExtendedListViewStyle": `void ListView_SetExtendedListViewStyle(HWND hwndLV, DWORD dwExStyle);` */

/* aa453384 "ListView_SetExtendedListViewStyleEx": `void ListView_SetExtendedListViewStyleEx( HWND hwndLV, DWORD dwExMask, DWORD dwExStyle);` */

/* aa453401 "ListView_SetGroupInfo": `int ListView_SetGroupInfo( HWND hwnd, int iGroupId, PLVGROUP pgrp);` */

/* aa453402 "ListView_SetGroupMetrics": `ListView_SetGroupMetrics( HWND hwnd, PLVGROUPMETRICS pGroupMetrics);` */

/* aa453365 "ListView_SetIconSpacing": `DWORD ListView_SetIconSpacing(HWND hwndLV, int cx, int cy);` */

/* aa453366 "ListView_SetImageList": `HIMAGELISTListView_SetImageList( HWNDhwnd, HIMAGELISThiml,intiImageList);` */

/* aa453403 "ListView_SetInfoTip": `BOOL ListView_SetInfoTip( HWND hwnd, PLVSETINFOTIP plvSetInfoTip);` */

/* aa453367 "ListView_SetItem": `BOOLListView_SetItem( HWNDhwnd, const LVITEMFAR* pitem);` */

/* aa453368 "ListView_SetItemCount": `voidListView_SetItemCount( HWNDhwndLV, intcItems);` */

/* aa453369 "ListView_SetItemCountEx": `void ListView_SetItemCountEx(HWND hwndLV, int cItems, DWORD dwFlags );` */

/* aa453370 "ListView_SetItemPosition": `BOOLListView_SetItemPosition( HWNDhwnd, inti, intx, inty );` */

/* aa453371 "ListView_SetItemPosition32": `voidListView_SetItemPosition32( HWNDhwnd, intiItem, intx, inty );` */

/* aa453372 "ListView_SetItemState": `voidWINAPIListView_SetItemState( HWNDhwnd, inti, UINTstate, UINTmask );` */

/* aa453373 "ListView_SetItemText": `voidWINAPIListView_SetItemText( HWNDhwnd, inti, intiSubItem, LPCSTRpszText );` */

/* aa453374 "ListView_SetSelectionMark": `INT ListView_SetSelectionMark(HWND hwndLV, INT iIndex );` */

/* aa453375 "ListView_SetTextBkColor": `BOOLListView_SetTextBkColor( HWNDhwnd, COLORREFclrText );` */

/* aa453376 "ListView_SetTextColor": `BOOLListView_SetTextColor( HWNDhwnd, COLORREFclrText );` */

/* aa453404 "ListView_SetToolTips": `HWND ListView_SetToolTips( HWND hwnd, HWND hwndToolTip);` */

/* aa453405 "ListView_SortGroups": `int ListView_SortGroups( HWND hwnd, PFNLVGROUPCOMPARE pfnGroupCompare, LPVOID plv);` */

/* aa453378 "ListView_SortItems": `BOOLListView_SortItems( HWNDhwnd, PFNLVCOMPAREpfnCompare,LPARAMlParamSort );` */

/* aa453380 "ListView_SubItemHitTest": `INT ListView_SubItemHitTest(HWND hwndLV, LPLVHITTESTINFO pInfo );` */

/* aa453381 "ListView_Update": `BOOLListView_Update( HWNDhwnd, intiItem );` */

/* ------------------------------------------------------------------ */
/* Month Calendar control (MCM_/MCN_/MonthCal_) */
/* ------------------------------------------------------------------ */

/* ms911794 "MCM_GETCOLOR": `MCM_GETCOLOR wParam = (WPARAM)(INT)iColor;lParam= 0;` */

/* ms911795 "MCM_GETCURSEL": `MCM_GETCURSEL wParam= 0;lParam = (LPARAM) (LPSYSTEMTIME)lpSysTime;` */

/* ms911796 "MCM_GETFIRSTDAYOFWEEK": `MCM_GETFIRSTDAYOFWEEK wParam= 0;lParam= 0;` */

/* ms911797 "MCM_GETMAXNONEWIDTH": `MCM_GETMAXNONEWIDTH wParam= void;lParam= LPDWORD;` */

/* ms911798 "MCM_GETMAXSELCOUNT": `MCM_GETMAXSELCOUNT wParam= 0;lParam= 0;` */

/* ms911799 "MCM_GETMAXTODAYWIDTH": `MCM_GETMAXTODAYWIDTH wParam= 0;lParam= 0;` */

/* ms911800 "MCM_GETMINREQRECT": `MCM_GETMINREQRECT wParam= 0;lParam = (LPARAM) (LPRECT)lpRectInfo;` */

/* ms911801 "MCM_GETMONTHDELTA": `MCM_GETMONTHDELTA wParam= 0;lParam= 0;` */

/* ms911802 "MCM_GETMONTHRANGE": `MCM_GETMONTHRANGE wParam = (WPARAM)(DWORD) dwFlag;lParam = (LPARAM)(LPSYSTEMTIME)lprgSysTimeArray;` */

/* ms911803 "MCM_GETRANGE": `MCM_GETRANGE wParam= 0;lParam = (LPARAM)(LPSYSTEMTIME) lprgSysTimeArray;` */

/* ms911804 "MCM_GETSELRANGE": `MCM_GETSELRANGE wParam= 0;lParam = (LPARAM)(LPSYSTEMTIME)lprgSysTimeArray;` */

/* ms911805 "MCM_GETTODAY": `MCM_GETTODAY wParam= 0;lParam = (LPARAM)(LPSYSTEMTIME) lpToday;` */

/* ms911806 "MCM_HITTEST": `MCM_HITTEST wParam= 0;lParam = (LPARAM)(PMCHITTESTINFO)pMCHitTest;` */

/* ms911807 "MCM_SETCOLOR": `MCM_SETCOLOR wParam = (WPARAM)(INT)iColor;lParam = (LPARAM)(COLORREF)clr;` */

/* ms911808 "MCM_SETCURSEL": `MCM_SETCURSEL wParam= 0;lParam = (LPARAM)(LPSYSTEMTIME)lpSysTime;` */

/* ms911809 "MCM_SETDAYSTATE": `MCM_SETDAYSTATE wParam = (WPARAM)iMonths;lParam = (LPARAM)(LPMONTHDAYSTATE)lpDayStateArray;` */

/* ms911810 "MCM_SETFIRSTDAYOFWEEK": `MCM_SETFIRSTDAYOFWEEK wParam= 0;lParam = (LPARAM)(INT) iDay;` */

/* ms911811 "MCM_SETMAXSELCOUNT": `MCM_SETMAXSELCOUNT wParam = (WPARAM)(INT)iMax;lParam= 0;` */

/* ms911812 "MCM_SETMONTHDELTA": `MCM_SETMONTHDELTA wParam = (WPARAM)(INT)iDelta;lParam= 0;` */

/* ms911813 "MCM_SETRANGE": `MCM_SETRANGE wParam = (WPARAM)(SHORT) fWhichLimit;lParam = (LPARAM)(LPSYSTEMTIME)lprgSysTimeArray;` */

/* ms911814 "MCM_SETSELRANGE": `MCM_SETSELRANGE wParam= 0;lParam = (LPARAM)(LPSYSTEMTIME)lprgSysTimeArray;` */

/* ms911815 "MCM_SETTODAY": `MCM_SETTODAY wParam= 0;lParam = (LPARAM)(LPSYSTEMTIME) lpSysTime;` */

/* ms911816 "MCN_GETDAYSTATE": `MCN_GETDAYSTATE lpNMDayState = (LPNMDAYSTATE)lParam;` */

/* ms911817 "MCN_SELCHANGE": `MCN_SELCHANGE lpNMSelChange = (LPNMSELCHANGE)lParam;` */

/* ms911818 "MCN_SELECT": `MCN_SELECT lpNMSelChange = (LPNMSELCHANGE)lParam;` */

/* ms911819 "MCN_SELECTNONE": `MCN_SELECTNONE` */

/* ms931431 "MonthCal_GetColor": `COLORREF MonthCal_GetColor(HWND hwndMC, INT iColor );` */

/* ms931432 "MonthCal_GetCurSel": `BOOL MonthCal_GetCurSel(HWND hwndMC, LPSYSTEMTIME lpSysTime );` */

/* ms931433 "MonthCal_GetFirstDayOfWeek": `DWORD MonthCal_GetFirstDayOfWeek(HWND hwndMC );` */

/* ms931434 "MonthCal_GetMaxSelCount": `DWORD MonthCal_GetMaxSelCount(HWND hwndMC );` */

/* ms931435 "MonthCal_GetMaxTodayWidth": `DWORD MonthCal_GetMaxTodayWidth(HWND hwndMC );` */

/* ms931436 "MonthCal_GetMinReqRect": `BOOL MonthCal_GetMinReqRect(HWND hwndMC, LPRECT lpRectInfo );` */

/* ms931437 "MonthCal_GetMonthDelta": `INT MonthCal_GetMonthDelta(HWND hwndMC );` */

/* ms931438 "MonthCal_GetMonthRange": `DWORD MonthCal_GetMonthRange(HWND hwndMC, DWORD dwFlag, LPSYSTEMTIME lprgSysTimeArray );` */

/* ms931439 "MonthCal_GetRange": `DWORD MonthCal_GetRange(HWND hwndMC, LPSYSTEMTIME lprgSysTimeArray );` */

/* ms931440 "MonthCal_GetSelRange": `BOOL MonthCal_GetSelRange(HWND hwndMC, LPSYSTEMTIME lprgSysTimeArray );` */

/* ms931441 "MonthCal_GetToday": `BOOL MonthCal_GetToday(HWND hwndMC, LPSYSTEMTIME lpToday );` */

/* ms931442 "MonthCal_HitTest": `DWORD MonthCal_HitTest(HWND hwndMC, PMCHITTESTINFO pMCHitTest );` */

/* ms931443 "MonthCal_SetColor": `COLORREF MonthCal_SetColor(HWND hwndMC, INT iColor, COLORREF clr );` */

/* ms931445 "MonthCal_SetCurSel": `BOOL MonthCal_SetCurSel(HWND hwndMC, LPSYSTEMTIME lpSysTime );` */

/* ms931446 "MonthCal_SetDayState": `BOOL MonthCal_SetDayState(HWND hwndMC,INT iMonths, LPMONTHDAYSTATE lpDayStateArray );` */

/* ms931447 "MonthCal_SetFirstDayOfWeek": `DWORD MonthCal_SetFirstDayOfWeek(HWND hwndMC, INT iDay );` */

/* ms931448 "MonthCal_SetMaxSelCount": `BOOL MonthCal_SetMaxSelCount(HWND hwndMC, UINT iMax );` */

/* ms931449 "MonthCal_SetMonthDelta": `INT MonthCal_SetMonthDelta(HWND hwndMC, INT iDelta );` */

/* ms931450 "MonthCal_SetRange": `BOOL MonthCal_SetRange(HWND hwndMC, DWORD fWhichLimit, LPSYSTEMTIME lprgSysTimeArray );` */

/* ms931451 "MonthCal_SetSelRange": `BOOL MonthCal_SetSelRange(HWND hwndMC, LPSYSTEMTIME lprgSysTimeArray );` */

/* ms931452 "MonthCal_SetToday": `void MonthCal_SetToday(HWND hwndMC, LPSYSTEMTIME lpSysTime );` */

/* ------------------------------------------------------------------ */
/* Progress bar (PBM_) */
/* ------------------------------------------------------------------ */

/* ms911920 "PBM_GETPOS": `PBM_GETPOS wParam= 0;lParam= 0;` */

/* ms911921 "PBM_GETRANGE": `PBM_GETRANGE wParam = (WPARAM)(BOOL)fWhichLimit;lParam = (LPARAM)(PPBRANGE) ppBRange;` */

/* ms911922 "PBM_SETPOS": `PBM_SETPOSnNewPos= (WPARAM)wParam;` */

/* ms911923 "PBM_SETRANGE": `PBM_SETRANGE(nMinRange,nMaxRange)= (MAKELPARAM)lParam;` */

/* ms911924 "PBM_SETRANGE32": `PBM_SETRANGE32 wParam = (WPARAM)(int)iLowLim;lParam = (LPARAM)(int)iHighLim;` */

/* ms911925 "PBM_SETSTEP": `PBM_SETSTEPnStepInc= (WPARAM)wParam;` */

/* ------------------------------------------------------------------ */
/* Rebar control (RB_/RBN_) */
/* ------------------------------------------------------------------ */

/* aa453625 "RBN_AUTOSIZE": `RBN_AUTOSIZE lpnmas = (LPNMRBAUTOSIZE)lParam;` */

/* aa453626 "RBN_BEGINDRAG": `RBN_BEGINDRAG lpnmrb = (LPNMREBAR)lParam;` */

/* aa453627 "RBN_ENDDRAG": `RBN_ENDDRAG lpnmrb = (LPNMREBAR)lParam;` */

/* aa453628 "RBN_HEIGHTCHANGE": `RBN_HEIGHTCHANGE lpnmhdr = (LPNMHDR) lParam;` */

/* aa453629 "RBN_LAYOUTCHANGED": `RBN_LAYOUTCHANGED lpnmhdr = (LPNMHDR)lParam;` */

/* aa453608 "RB_DELETEBAND": `RB_DELETEBAND wParam = (WPARAM)(UINT)uBand;lParam= 0;` */

/* aa453609 "RB_GETBANDBORDERS": `RB_GETBANDBORDERS wParam = (WPARAM)(UINT)uBand;lParam = (LPARAM)(LPRECT)lprc;` */

/* aa453610 "RB_GETBANDCOUNT": `RB_GETBANDCOUNT wParam= 0;lParam= 0;` */

/* aa453611 "RB_GETBANDINFO": `RB_GETBANDINFO wParam = (WPARAM)(UINT)uBand;lParam = (LPARAM)(LPREBARBANDINFO)lprbbi;` */

/* aa453612 "RB_GETBARHEIGHT": `RB_GETBARHEIGHT wParam= 0;lParam= 0;` */

/* aa453613 "RB_GETBARINFO": `RB_GETBARINFO wParam= 0;lParam = (LPARAM)(LPREBARINFO)lprbi;` */

/* aa453614 "RB_GETBKCOLOR": `RB_GETBKCOLOR wParam= 0;lParam= 0;` */

/* aa453615 "RB_GETRECT": `RB_GETRECT wParam = (WPARAM)(INT)iBand;lParam = (LPARAM)(LPRECT)lprc;` */

/* aa453616 "RB_GETROWCOUNT": `RB_GETROWCOUNT wParam= 0;lParam= 0;` */

/* aa453617 "RB_GETROWHEIGHT": `RB_GETROWHEIGHT wParam = (WPARAM)(UINT)uRow;lParam= 0;` */

/* aa453618 "RB_GETTEXTCOLOR": `RB_GETTEXTCOLOR wParam= 0;lParam= 0;` */

/* aa453621 "RB_IDTOINDEX": `RB_IDTOINDEXwParam = (WPARAM)(UINT)uBandID;lParam= 0;` */

/* aa453622 "RB_INSERTBAND": `RB_INSERTBAND wParam = (WPARAM)(UINT)uIndex;lParam = (LPARAM)(LPREBARBANDINFO)lprbbi;` */

/* aa453623 "RB_MAXIMIZEBAND": `RB_MAXIMIZEBAND wParam = (WPARAM)(UINT)uBand;lParam = (LPARAM)(BOOL)fIdeal;` */

/* aa453624 "RB_MINIMIZEBAND": `RB_MINIMIZEBAND wParam = (WPARAM)(UINT)uBand;lParam= 0;` */

/* aa453630 "RB_SETBANDINFO": `RB_SETBANDINFO wParam = (WPARAM)(UINT)uBand;lParam = (LPARAM)(LPREBARBANDINFO)lprbbi;` */

/* aa453631 "RB_SETBARINFO": `RB_SETBARINFO wParam= 0;lParam = (LPARAM)(LPREBARINFO)lprbi;` */

/* aa453632 "RB_SETBKCOLOR": `RB_SETBKCOLOR wParam= 0;lParam = (LPARAM)(COLORREF)clrBk;` */

/* aa453633 "RB_SETPARENT": `RB_SETPARENT wParam = (WPARAM)(HWND)hwndParent;lParam= 0;` */

/* aa453634 "RB_SETTEXTCOLOR": `RB_SETTEXTCOLOR wParam= 0;lParam = (LPARAM)(COLORREF)clrText;` */

/* aa453635 "RB_SHOWBAND": `RB_SHOWBAND wParam = (WPARAM)(INT)iBand;lParam = (LPARAM)(BOOL)fShow;` */

/* aa453636 "RB_SIZETORECT": `RB_SIZETORECT wParam= 0;lParam = (LPARAM)(LPRECT)prc;` */

/* ------------------------------------------------------------------ */
/* Status bar (SB_/SBN_) */
/* ------------------------------------------------------------------ */

/* ms932550 "SB_GETICON": `lResult = SendMessage( (HWND) hWndControl, (UINT) SB_GETICON, (WPARAM) wParam, // = (WPARAM) (INT) iPart; (LPARAM) lParam // = 0; not used, must be zero )` */

/* ms939925 "SB_GETPARTS": `SB_GETPARTS wParam= (WPARAM)nParts;lParam = (LPARAM)(LPINT)aRightCoord;` */

/* ms913125 "SB_GETRECT": `SB_GETRECT wParam = (WPARAM)iPart;lParam= (LPARAM)(LPRECT)lprc;` */

/* ms913198 "SB_GETTEXT": `SB_GETTEXT wParam = (WPARAM)iPart;lParam= (LPARAM)(LPSTR)szText;` */

/* ms913203 "SB_GETTEXTLENGTH": `SB_GETTEXTLENGTH wParam= (WPARAM)iPart;lParam= 0;` */

/* ms913210 "SB_ISSIMPLE": `SB_ISSIMPLE wParam= 0;lParam= 0;` */

/* ms932561 "SB_SETBKCOLOR": `lResult = SendMessage( // returns LRESULT in lResult (HWND) hWndControl, // handle to destination control (UINT) SB_SETBKCOLOR, // message ID (WPARAM) wParam, // = 0; not used, must be zero (LPARAM) lParam // = (LPARAM) (COLORREF) clrBk;)` */

/* ms932570 "SB_SETICON": `lResult = SendMessage( (HWND) hWndControl, (UINT) SB_SETICON, (WPARAM) wParam, // = (WPARAM) (INT) iPart; (LPARAM) lParam // = (LPARAM) (HICON) hIcon; )` */

/* ms913344 "SB_SETMINHEIGHT": `SB_SETMINHEIGHT wParam= (WPARAM)minHeight;lParam= 0;` */

/* ms932515 "SB_SETPARTS": `SB_SETPARTS wParam= (WPARAM)nParts;lParam = (LPARAM)(LPINT)aWidths;` */

/* ms932525 "SB_SETTEXT": `SB_SETTEXT wParam= (WPARAM)iPart|uType;lParam = (LPARAM)(LPSTR)szText;` */

/* ------------------------------------------------------------------ */
/* Toolbar (TB_/TBN_) */
/* ------------------------------------------------------------------ */

/* ms913804 "TBN_BEGINDRAG": `TBN_BEGINDRAG lpnmtb=(TBNOTIFY FAR *)lParam;` */

/* ms913807 "TBN_DRAGOUT": `TBN_DRAGOUTlpnmtb = (LPNMTOOLBAR) lParam;` */

/* ms913809 "TBN_DROPDOWN": `TBN_DROPDOWNlpnmtb=(LPNMTOOLBAR)lParam;` */

/* ms913811 "TBN_ENDDRAG": `TBN_ENDDRAGlpnmtb=(TBNOTIFY FAR *)lParam;` */

/* ms913813 "TBN_GETBUTTONINFO": `TBN_GETBUTTONINFOlpnmtb= (TBNOTIFY FAR *)lParam;` */

/* ms940415 "TB_ADDBUTTONS": `TB_ADDBUTTONSwParam=(WPARAM)(UINT)uNumButtons;lParam=(LPARAM)(LPTBBUTTON)lpButtons;` */

/* ms940416 "TB_ADDSTRING": `TB_ADDSTRINGwParam= (WPARAM)(HINSTANCE)hinst;lParam=(LPARAM)MAKELONG(idString,0);` */

/* ms940417 "TB_AUTOSIZE": `TB_AUTOSIZE wParam= 0;lParam= 0;` */

/* ms940419 "TB_BUTTONCOUNT": `TB_BUTTONCOUNT wParam= 0;lParam= 0;` */

/* ms940421 "TB_BUTTONSTRUCTSIZE": `TB_BUTTONSTRUCTSIZEwParam=(WPARAM)cb;lParam= 0;` */

/* ms940422 "TB_CHANGEBITMAP": `TB_CHANGEBITMAP wParam=(WPARAM)idButton;lParam=(LPARAM)MAKELPARAM(iBitmap,0);` */

/* ms940423 "TB_CHECKBUTTON": `TB_CHECKBUTTON wParam=(WPARAM)idButton;lParam = (LPARAM)MAKELONG(fCheck,0);` */

/* ms940424 "TB_COMMANDTOINDEX": `TB_COMMANDTOINDEX wParam=(WPARAM)idButton;lParam= 0;` */

/* ms940425 "TB_DELETEBUTTON": `TB_DELETEBUTTON wParam=(WPARAM)iButton;lParam= 0;` */

/* ms940426 "TB_ENABLEBUTTON": `TB_ENABLEBUTTON wParam=(WPARAM) idButton;lParam= (LPARAM)MAKELONG(fEnable,0);` */

/* ms940427 "TB_GETBITMAP": `TB_GETBITMAP wParam= (WPARAM)idButton;lParam= 0;` */

/* ms940428 "TB_GETBITMAPFLAGS": `TB_GETBITMAPFLAGS wParam= 0;lParam= 0;` */

/* ms940431 "TB_GETBUTTONSIZE": `TB_GETBUTTONSIZE wParam= 0;lParam= 0;` */

/* ms940432 "TB_GETBUTTONTEXT": `TB_GETBUTTONTEXTwParam= (WPARAM)idButton;lParam= (LPARAM)(LPSTR)lpszText;` */

/* ms940433 "TB_GETDISABLEDIMAGELIST": `TB_GETDISABLEDIMAGELISTwParam= 0;lParam= 0;` */

/* ms940434 "TB_GETIMAGELIST": `TB_GETIMAGELIST wParam= 0;lParam= 0;` */

/* ms940435 "TB_GETITEMRECT": `TB_GETITEMRECTwParam = (WPARAM)iButton;lParam= (LPARAM)(LPRECT)lprc;` */

/* ms940436 "TB_GETRECT": `TB_GETRECTwParam= (WPARAM)(INT) iID;lParam= (LPARAM)(LPRECT)lprc;` */

/* ms940437 "TB_GETROWS": `TB_GETROWS wParam= 0;lParam= 0;` */

/* ms940438 "TB_GETSTATE": `TB_GETSTATE wParam= (WPARAM)idButton;lParam= 0;` */

/* ms913710 "TB_GETSTYLE": `TB_GETSTYLE wParam= 0;lParam= 0;` */

/* ms913711 "TB_GETTEXTROWS": `TB_GETTEXTROWS wParam= 0;lParam= 0;` */

/* ms913712 "TB_GETTOOLTIPS": `TB_GETTOOLTIPS` */

/* ms913713 "TB_HIDEBUTTON": `TB_HIDEBUTTON wParam=(WPARAM)idButton;lParam= (LPARAM)MAKELONG(fShow,0);` */

/* ms913714 "TB_HIGHLIGHTBUTTON": `TB_HIGHLIGHTBUTTONwParam = (WPARAM)idButton;lParam = (LPARAM) MAKELONG(fHighlight,0);` */

/* ms913715 "TB_INDETERMINATE": `TB_INDETERMINATE wParam= (WPARAM)idButton;lParam= (LPARAM)MAKELONG(fIndeterminate,0);` */

/* ms913716 "TB_INSERTBUTTON": `TB_INSERTBUTTON wParam = (WPARAM)iButton;lParam = (LPARAM)(LPTBBUTTON)lpButton;` */

/* ms913717 "TB_ISBUTTONCHECKED": `TB_ISBUTTONCHECKED wParam=(WPARAM)idButton;lParam= 0;` */

/* ms913718 "TB_ISBUTTONENABLED": `TB_ISBUTTONENABLED wParam= (WPARAM)idButton;lParam= 0;` */

/* ms913719 "TB_ISBUTTONHIDDEN": `TB_ISBUTTONHIDDEN wParam=(WPARAM)idButton;lParam= 0;` */

/* ms913720 "TB_ISBUTTONHIGHLIGHTED": `TB_ISBUTTONHIGHLIGHTEDwParam=(WPARAM)idButton;lParam= 0;` */

/* ms913721 "TB_ISBUTTONINDETERMINATE": `TB_ISBUTTONINDETERMINATEwParam=(WPARAM)idButton;lParam= 0;` */

/* ms913722 "TB_ISBUTTONPRESSED": `TB_ISBUTTONPRESSED wParam=(WPARAM)idButton;lParam= 0;` */

/* ms913815 "TB_PRESSBUTTON": `TB_PRESSBUTTON wParam= (WPARAM)idButton;lParam= (LPARAM)MAKELONG(fPress,0);` */

/* ms913851 "TB_REPLACEBITMAP": `TB_REPLACEBITMAPwParam= 0;lParam=(LPARAM) (LPTBREPLACEBITMAP)ptbrb;` */

/* ms913819 "TB_SETBITMAPSIZE": `TB_SETBITMAPSIZE wParam= 0;lParam=(LPARAM)MAKELONG(dxBitmap,dyBitmap);` */

/* ms913821 "TB_SETBUTTONINFO": `TB_SETBUTTONINFOwParam=(WPARAM)(INT)iID;lParam=(LPARAM)(LPTBBUTTONINFO)lptbbi;` */

/* ms913823 "TB_SETBUTTONSIZE": `TB_SETBUTTONSIZE wParam= 0;lParam= (LPARAM)MAKELONG(dxButton,dyButton);` */

/* ms913825 "TB_SETBUTTONWIDTH": `TB_SETBUTTONWIDTHwParam= 0;lParam=(LPARAM)(DWORD) MAKELONG(cxMin,cxMax);` */

/* ms913829 "TB_SETDISABLEDIMAGELIST": `TB_SETDISABLEDIMAGELISTwParam= 0;lParam=(LPARAM)(HIMAGELIST)himlNewDisabled;` */

/* ms913831 "TB_SETDRAWTEXTFLAGS": `TB_SETDRAWTEXTFLAGSwParam=(WPARAM)(DWORD)dwMask;lParam= (LPARAM)(DWORD)dwDTFlags;` */

/* ms913833 "TB_SETIMAGELIST": `TB_SETIMAGELIST wParam= 0;lParam=(LPARAM)(HIMAGELIST)himlNew;` */

/* ms913835 "TB_SETINDENT": `TB_SETINDENT wParam= (WPARAM)(INT) iIndent;lParam = 0;` */

/* ms913837 "TB_SETMAXTEXTROWS": `TB_SETMAXTEXTROWSwParam=(WPARAM)(INT)iMaxRows;lParam= 0;` */

/* ms913839 "TB_SETPARENT": `TB_SETPARENT wParam= (WPARAM)(HWND)hwndParent;lParam= 0;` */

/* ms913841 "TB_SETROWS": `TB_SETROWSwParam=(WPARAM)MAKEWPARAM(cRows,fLarger);lParam = (LPARAM)(LPRECT)lprc;` */

/* ms913843 "TB_SETSTATE": `TB_SETSTATE wParam= (WPARAM) idButton;lParam=(LPARAM)MAKELONG(fState,0);` */

/* ms913845 "TB_SETSTYLE": `TB_SETSTYLE wParam= 0;lParam=(LPARAM)(DWORD)dwStyle;` */

/* ms913847 "TB_SETTOOLTIPS": `TB_SETTOOLTIPSwParam = (WPARAM) (HWND) hwndToolTip;lParam = 0;` */

/* ------------------------------------------------------------------ */
/* Tooltip control (TTM_/TTN_) */
/* ------------------------------------------------------------------ */

/* aa453820 "TTM_ACTIVATE": `TTM_ACTIVATE wParam= (WPARAM) (BOOL)fActivate;lParam= 0;` */

/* aa453821 "TTM_ADDTOOL": `TTM_ADDTOOLwParam = 0;lParam = (LPARAM) (LPTOOLINFO) lpti;` */

/* aa453822 "TTM_DELTOOL": `TTM_DELTOOLwParam= 0;lParam= (LPARAM) (LPTOOLINFO)lpti;` */

/* aa453823 "TTM_ENUMTOOLS": `TTM_ENUMTOOLS wParam= (WPARAM) (UINT)iTool;lParam= (LPARAM) (LPTOOLINFO)lpti;` */

/* aa453824 "TTM_GETCURRENTTOOL": `TTM_GETCURRENTTOOLwParam= 0;lParam= (LPARAM)(LPTOOLINFO) lpti;` */

/* aa453825 "TTM_GETDELAYTIME": `TTM_GETDELAYTIMEwParam= (DWORD)dwDuration;` */

/* aa453826 "TTM_GETMARGIN": `TTM_GETMARGINwParam= 0;lParam= (LPARAM)(LPRECT)lprc;` */

/* aa453827 "TTM_GETMAXTIPWIDTH": `TTM_GETMAXTIPWIDTH wParam= 0;lParam= 0;` */

/* aa453828 "TTM_GETTEXT": `TTM_GETTEXT wParam= 0;lParam= (LPARAM) (LPTOOLINFO)lpti;` */

/* aa453829 "TTM_GETTIPBKCOLOR": `TTM_GETTIPBKCOLOR wParam= 0;lParam= 0;` */

/* aa453831 "TTM_GETTOOLCOUNT": `TTM_GETTOOLCOUNT wParam= 0;lParam= 0;` */

/* aa453832 "TTM_GETTOOLINFO": `TTM_GETTOOLINFO wParam= 0;lParam= (LPARAM) (LPTOOLINFO)lpti;` */

/* aa453833 "TTM_HITTEST": `TTM_HITTEST wParam= 0;lParam= (LPARAM) (LPHITTESTINFO)lphti;` */

/* aa453834 "TTM_NEWTOOLRECT": `TTM_NEWTOOLRECT wParam= 0;lParam= (LPARAM) (LPTOOLINFO)lpti;` */

/* aa453835 "TTM_POP": `TTM_POP wParam= 0;lParam= 0;` */

/* aa453836 "TTM_RELAYEVENT": `TTM_RELAYEVENT wParam= 0;lParam= (LPARAM) (LPMSG)lpmsg;` */

/* aa453837 "TTM_SETDELAYTIME": `TTM_SETDELAYTIMEwParam= (WPARAM)(DWORD)dwDuration;lParam= (LPARAM)(INT) MAKELONG(iTime,0);` */

/* aa453838 "TTM_SETMARGIN": `TTM_SETMARGINwParam= 0;lParam= (LPARAM)(LPRECT)lprc;` */

/* aa453839 "TTM_SETMAXTIPWIDTH": `TTM_SETMAXTIPWIDTH wParam= 0;lParam= (LPARAM)(INT)iWidth;` */

/* aa453840 "TTM_SETTIPBKCOLOR": `TTM_SETTIPBKCOLOR wParam= (WPARAM)(COLORREF) clr;lParam= 0;` */

/* aa453841 "TTM_SETTIPTEXTCOLOR": `TTM_SETTIPTEXTCOLOR wParam= (WPARAM)(COLORREF)clr;lParam= 0;` */

/* aa453842 "TTM_SETTOOLINFO": `TTM_SETTOOLINFO wParam= 0;lParam= (LPARAM) (LPTOOLINFO)lpti;` */

/* aa453843 "TTM_TRACKACTIVATE": `TTM_TRACKACTIVATE wParam= (WPARAM)(BOOL)bActivate;lParam= (LPARAM)(LPTOOLINFO)lpti;` */

/* aa453844 "TTM_TRACKPOSITION": `TTM_TRACKPOSITION wParam= 0;lParam= (LPARAM)(DWORD) MAKELONG(xPos, yPos);` */

/* aa453845 "TTM_UPDATETIPTEXT": `TTM_UPDATETIPTEXT wParam = 0;lParam = (LPARAM) (LPTOOLINFO)lpti;` */

/* aa453846 "TTM_WINDOWFROMPOINT": `TTM_WINDOWFROMPOINT wParam = 0;lParam = (POINT FAR *)lppt;` */

/* ------------------------------------------------------------------ */
/* Trackbar (TBM_) */
/* ------------------------------------------------------------------ */

/* ms913729 "TBM_CLEARTICS": `TBM_CLEARTICS wParam=(WPARAM)(BOOL)fRedraw;lParam = 0;` */

/* ms913731 "TBM_GETBUDDY": `TBM_GETBUDDY wParam= (WPARAM)(BOOL)fLocation;lParam = 0;` */

/* ms913733 "TBM_GETCHANNELRECT": `TBM_GETCHANNELRECTwParam = 0;lParam=(LPARAM)(LPRECT)lprc;` */

/* ms913735 "TBM_GETLINESIZE": `TBM_GETLINESIZE wParam = 0;lParam = 0;` */

/* ms913736 "TBM_GETNUMTICS": `TBM_GETNUMTICS wParam = 0;lParam = 0;` */

/* ms913739 "TBM_GETPAGESIZE": `TBM_GETPAGESIZE wParam = 0;lParam = 0;` */

/* ms913741 "TBM_GETPOS": `TBM_GETPOS wParam = 0;lParam = 0;` */

/* ms913743 "TBM_GETPTICS": `TBM_GETPTICS wParam = 0;lParam = 0;` */

/* ms913747 "TBM_GETRANGEMAX": `TBM_GETRANGEMAX wParam = 0;lParam = 0;` */

/* ms913749 "TBM_GETRANGEMIN": `TBM_GETRANGEMIN wParam = 0;lParam = 0;` */

/* ms913751 "TBM_GETSELEND": `TBM_GETSELEND wParam = 0;lParam = 0;` */

/* ms913754 "TBM_GETSELSTART": `TBM_GETSELSTART wParam = 0;lParam = 0;` */

/* ms913756 "TBM_GETTHUMBLENGTH": `TBM_GETTHUMBLENGTH wParam = 0;lParam = 0;` */

/* ms913758 "TBM_GETTHUMBRECT": `TBM_GETTHUMBRECTwParam = 0;lParam=(LPARAM)(LPRECT)lprc;` */

/* ms913761 "TBM_GETTIC": `TBM_GETTIC wParam=(WPARAM)(WORD)iTic;lParam = 0;` */

/* ms913765 "TBM_GETTICPOS": `TBM_GETTICPOSwParam=(WPARAM)(WORD)iTic;lParam = 0;` */

/* ms913769 "TBM_SETBUDDY": `TBM_SETBUDDY wParam= (WPARAM)(BOOL)fLocation;lParam= (LPARAM)(HWND)hwndBuddy;` */

/* ms913773 "TBM_SETLINESIZE": `TBM_SETLINESIZE wParam = 0;lParam= (LONG)lLineSize;` */

/* ms913779 "TBM_SETPAGESIZE": `TBM_SETPAGESIZE wParam = 0;lParam= (LONG)lPageSize;` */

/* ms913783 "TBM_SETPOS": `TBM_SETPOS wParam=(WPARAM)(BOOL) fPosition;lParam=(LPARAM)(LONG)lPosition;` */

/* ms913785 "TBM_SETRANGE": `TBM_SETRANGE wParam= (WPARAM)(BOOL) fRedraw;lParam= (LPARAM)MAKELONG(lMinimum,lMaximum);` */

/* ms913787 "TBM_SETRANGEMAX": `TBM_SETRANGEMAX wParam= (WPARAM)fRedraw;lParam=(LPARAM)lMaximum;` */

/* ms913789 "TBM_SETRANGEMIN": `TBM_SETRANGEMIN wParam = (WPARAM)fRedraw;lParam = (LPARAM)lMinimum;` */

/* ms913791 "TBM_SETSEL": `TBM_SETSEL wParam=(WPARAM)(BOOL)fRedraw;lParam=(LPARAM)MAKELONG(lMinimum,lMaximum);` */

/* ms913793 "TBM_SETSELEND": `TBM_SETSELENDwParam=(WPARAM)(BOOL)fRedraw;lParam= (LPARAM)(LONG)lEnd;` */

/* ms913795 "TBM_SETSELSTART": `TBM_SETSELSTARTwParam= (WPARAM)(BOOL)fRedraw;lParam=(LPARAM)(LONG)lStart;` */

/* ms913797 "TBM_SETTHUMBLENGTH": `TBM_SETTHUMBLENGTHwParam= (WPARAM)(UINT)iLength;lParam = 0;` */

/* ------------------------------------------------------------------ */
/* Tab control (TCM_/TCN_/TabCtrl_) */
/* ------------------------------------------------------------------ */

/* ms913864 "TCM_ADJUSTRECT": `TCM_ADJUSTRECTwParam=(WPARAM)(BOOL)fLarger;lParam=(LPARAM)(LPRECT)prc;` */

/* ms913867 "TCM_DELETEALLITEMS": `TCM_DELETEALLITEMS wParam= 0;lParam= 0;` */

/* ms913870 "TCM_DELETEITEM": `TCM_DELETEITEM wParam=(WPARAM)(int)iItem;lParam= 0;` */

/* ms913872 "TCM_DESELECTALL": `TCM_DESELECTALL wParam=(WPARAM) (DWORD)fExcludeFocus;lParam= 0;` */

/* ms913876 "TCM_GETCURFOCUS": `TCM_GETCURFOCUS wParam= 0;lParam= 0;` */

/* ms913879 "TCM_GETCURSEL": `TCM_GETCURSEL wParam= 0;lParam= 0;` */

/* ms913882 "TCM_GETEXTENDEDSTYLE": `TCM_GETEXTENDEDSTYLE wParam= 0;lParam= 0;` */

/* ms913885 "TCM_GETIMAGELIST": `TCM_GETIMAGELIST wParam= 0;lParam= 0;` */

/* ms913894 "TCM_GETITEM": `TCM_GETITEMwParam= (WPARAM)(int) iItem;lParam=(LPARAM)(TCITEM FAR *)pitem;` */

/* ms913898 "TCM_GETITEMCOUNT": `TCM_GETITEMCOUNT wParam= 0;lParam= 0;` */

/* ms933234 "TCM_GETITEMRECT": `TCM_GETITEMRECTwParam=(WPARAM)(int)iItem;lParam= (LPARAM)(RECT FAR *)prc;` */

/* ms933237 "TCM_GETROWCOUNT": `TCM_GETROWCOUNT wParam= 0;lParam= 0;` */

/* ms933240 "TCM_HIGHLIGHTITEM": `TCM_HIGHLIGHTITEMwParam= (WPARAM)idItem;lParam= (LPARAM) MAKELONG(fHighlight,0);` */

/* ms933245 "TCM_HITTEST": `TCM_HITTESTwParam= 0;lParam= (LPARAM)(TC_HITTESTINFO FAR *)pinfo;` */

/* ms933248 "TCM_INSERTITEM": `TCM_INSERTITEMwParam= (WPARAM)(int)iItem;lParam= (LPARAM)(const TCITEM FAR*)pitem;` */

/* ms933255 "TCM_REMOVEIMAGE": `TCM_REMOVEIMAGE | wParam= (WPARAM)(int)iImage;lParam= 0;` */

/* ms933258 "TCM_SETCURFOCUS": `TCM_SETCURFOCUSiItem= (int) (WPARAM)wParam;` */

/* ms933261 "TCM_SETCURSEL": `TCM_SETCURSEL wParam= (WPARAM)(int)iItem;lParam= 0;` */

/* ms933265 "TCM_SETEXTENDEDSTYLE": `TCM_SETEXTENDEDSTYLEwParam= (WPARAM)dwExMask;lParam=(LPARAM)dwExStyle;` */

/* ms933267 "TCM_SETIMAGELIST": `TCM_SETIMAGELISTwParam= 0; lParam= (LPARAM)(HIMAGELIST)himl;` */

/* ms933270 "TCM_SETITEM": `TCM_SETITEMwParam= (WPARAM)(int)iItem;lParam= (LPARAM)(TCITEM FAR *)pitem;` */

/* ms933276 "TCM_SETITEMEXTRA": `TCM_SETITEMEXTRAwParam= (WPARAM)(int)cb;lParam= 0;` */

/* ms933283 "TCM_SETITEMSIZE": `TCM_SETITEMSIZE wParam= 0; lParam=MAKELPARAM(cx,cy);` */

/* ms933286 "TCM_SETMINTABWIDTH": `TCM_SETMINTABWIDTHwParam= 0;lParam= (LPARAM) (INT)cx;` */

/* ms933294 "TCM_SETPADDING": `TCM_SETPADDING wParam = 0;lParam= MAKELPARAM(cx,cy);` */

/* ms933299 "TCN_KEYDOWN": `TCN_KEYDOWNpnm= (TC_KEYDOWN FAR *)lParam;` */

/* ms933405 "TCN_SELCHANGE": `TCN_SELCHANGE lpnmhdr = (LPNMHDR) lParam;` */

/* ms933410 "TCN_SELCHANGING": `TCN_SELCHANGE lpnmhdr = (LPNMHDR) lParam;` */

/* ms940387 "TabCtrl_AdjustRect": `void TabCtrl_AdjustRect(HWNDhwnd,BOOLfLarger,RECT FAR* prc );` */

/* ms940388 "TabCtrl_DeleteAllItems": `BOOL TabCtrl_DeleteAllItems( HWND hwnd );` */

/* ms940389 "TabCtrl_DeleteItem": `BOOL TabCtrl_DeleteItem( HWND hwnd, int iItem );` */

/* ms940390 "TabCtrl_DeselectAll": `void TabCtrl_DeselectAll( HWND hwndTab, UINT fExcludeFocus);` */

/* ms940391 "TabCtrl_GetCurFocus": `int TabCtrl_GetCurFocus( HWND hwnd );` */

/* ms940392 "TabCtrl_GetCurSel": `int TabCtrl_GetCurSel( HWND hwnd );` */

/* ms940393 "TabCtrl_GetExtendedStyle": `DWORD TabCtrl_GetExtendedStyle( HWND hwndTab);` */

/* ms940394 "TabCtrl_GetImageList": `HIMAGELIST TabCtrl_GetImageList( HWND hwnd );` */

/* ms940395 "TabCtrl_GetItem": `BOOL TabCtrl_GetItem( HWND hwnd, int iItem, TCITEM FAR* pitem );` */

/* ms940396 "TabCtrl_GetItemCount": `int TabCtrl_GetItemCount( HWND hwnd );` */

/* ms940397 "TabCtrl_GetItemRect": `BOOL TabCtrl_GetItemRect( HWND hwnd, int iItem, RECT FAR* prc );` */

/* ms940398 "TabCtrl_GetRowCount": `int TabCtrl_GetRowCount( HWND hwnd );` */

/* ms940399 "TabCtrl_HighlightItem": `BOOL TabCtrl_HighlightItem(HWND hwndTab, INT idItem, WORD fHighlight );` */

/* ms940400 "TabCtrl_HitTest": `intTabCtrl_HitTest( HWNDhwnd, TC_HITTESTINFOFAR* pinfo );` */

/* ms940401 "TabCtrl_InsertItem": `intTabCtrl_InsertItem( HWNDhwnd, intiItem, constTCITEMFAR* pitem );` */

/* ms940402 "TabCtrl_RemoveImage": `voidTabCtrl_RemoveImage( HWNDhwnd, intiImage );` */

/* ms940403 "TabCtrl_SetCurFocus" (printed verbatim; references held value-less constants):
 *   VOID TabCtrl_SetCurFocus( HWNDhwnd,
 *   intiItem);
 */

/* ms940404 "TabCtrl_SetCurSel": `intTabCtrl_SetCurSel(HWNDhwnd,intiItem );` */

/* ms940405 "TabCtrl_SetExtendedStyle": `DWORD TabCtrl_SetExtendedStyle(WND hwndTab, DWORD dwExStyle );` */

/* ms940406 "TabCtrl_SetImageList": `BOOLTabCtrl_SetImageList(HWNDhwnd,HIMAGELISThiml );` */

/* ms940407 "TabCtrl_SetItem": `BOOLTabCtrl_SetItem(HWNDhwnd,intiItem,TCITEMFAR* pitem );` */

/* ms940408 "TabCtrl_SetItemExtra": `BOOLTabCtrl_SetItemExtra(HWNDhwnd,intcb );` */

/* ms940409 "TabCtrl_SetItemSize": `DWORDTabCtrl_SetItemSize(HWNDhwnd,intcx,intcy );` */

/* ms940410 "TabCtrl_SetMinTabWidth": `int TabCtrl_SetMinTabWidth(HWND hwndTab, INT cx );` */

/* ms940411 "TabCtrl_SetPadding": `voidTabCtrl_SetPadding(HWNDhwnd,intcx,intcy );` */

/* ------------------------------------------------------------------ */
/* Tree-View control (TVM_/TVN_/TreeView_) */
/* ------------------------------------------------------------------ */

/* ms914008 "TVM_CREATEDRAGIMAGE": `TVM_CREATEDRAGIMAGEwParam = 0;lParam= (LPARAM)(HTREEITEM)hitem;` */

/* ms914019 "TVM_DELETEITEM": `TVM_DELETEITEMwParam = 0;lParam= (LPARAM)(HTREEITEM)hitem;` */

/* ms914024 "TVM_EDITLABEL": `TVM_EDITLABELwParam = 0;lParam= (LPARAM)(HTREEITEM)hitem;` */

/* ms914028 "TVM_ENDEDITLABELNOW": `TVM_ENDEDITLABELNOWwParam= (WPARAM)(BOOL)fCancel;lParam = 0;` */

/* ms914029 "TVM_ENSUREVISIBLE": `TVM_ENSUREVISIBLEwParam = 0;lParam= (LPARAM)(HTREEITEM)hitem;` */

/* ms914030 "TVM_EXPAND": `TVM_EXPANDwParam= (WPARAM)(UINT)flag;lParam = (LPARAM)(HTREEITEM)hitem;` */

/* ms914031 "TVM_GETCOUNT": `TVM_GETCOUNT wParam = 0;lParam = 0;` */

/* ms914032 "TVM_GETEDITCONTROL": `TVM_GETEDITCONTROL wParam = 0;lParam = 0;` */

/* ms914033 "TVM_GETIMAGELIST": `TVM_GETIMAGELIST wParam= (WPARAM)iImage;lParam = 0;` */

/* ms914034 "TVM_GETINDENT": `TVM_GETINDENT wParam = 0;lParam = 0;` */

/* ms914035 "TVM_GETISEARCHSTRING": `TVM_GETISEARCHSTRINGwParam = 0;lParam=(LPARAM)(LPSTR)lpsz;` */

/* ms914036 "TVM_GETITEM": `TVM_GETITEMwParam = 0;lParam= (LPARAM)(TV_ITEM FAR*)pitem;` */

/* ms914037 "TVM_GETITEMRECT": `TVM_GETITEMRECTwParam= (WPARAM)(BOOL)fItemRect;lParam= (LPARAM)(RECT FAR*)prc;` */

/* ms914038 "TVM_GETNEXTITEM": `TVM_GETNEXTITEMwParam=(WPARAM)(UINT)flag;lParam = (LPARAM)(HTREEITEM)hitem;` */

/* ms914039 "TVM_GETVISIBLECOUNT": `TVM_GETVISIBLECOUNT wParam = 0;lParam = 0;` */

/* ms914040 "TVM_HITTEST": `TVM_HITTEST wParam = 0;lParam=(LPARAM)(LPTV_HITTESTINFO)lpht;` */

/* ms914041 "TVM_INSERTITEM": `TVM_INSERTITEMwParam = 0;lParam= (LPARAM)(LPTV_INSERTSTRUCT)lpis;` */

/* ms914042 "TVM_SELECTITEM": `TVM_SELECTITEMwParam= (WPARAM)flag;lParam = (LPARAM)(HTREEITEM)hitem;` */

/* ms914043 "TVM_SETIMAGELIST": `TVM_SETIMAGELISTwParam= (WPARAM)iImage;lParam = (LPARAM)(HIMAGELIST)himl;` */

/* ms914044 "TVM_SETINDENT": `TVM_SETINDENT wParam=(WPARAM)indent;lParam = 0;` */

/* ms914045 "TVM_SETITEM": `TVM_SETITEMwParam = 0;lParam = (LPARAM)(const TV_ITEM FAR*)pitem;` */

/* ms914046 "TVM_SETITEMSPACING": `TVM_SETITEMSPACINGwParam = 0;lParam = (LPARAM)(int)iSpacing;` */

/* ms914047 "TVM_SORTCHILDREN": `TVM_SORTCHILDRENwParam=(WPARAM)fRecurse;lParam = (LPARAM)(HTREEITEM)hitem;` */

/* ms914048 "TVM_SORTCHILDRENCB": `TVM_SORTCHILDRENCBwParam = (WPARAM)fRecurse;lParam = (LPARAM)(LPTV_SORTCB)psort;` */

/* ms914050 "TVN_BEGINDRAG": `TVN_BEGINDRAGpnmtv= (NM_TREEVIEW FAR *)lParam;` */

/* ms914051 "TVN_BEGINLABELEDIT": `TVN_BEGINLABELEDITptvdi= (TV_DISPINFO FAR *)lParam;` */

/* ms914052 "TVN_DELETEITEM": `TVN_DELETEITEMpnmtv=(NM_TREEVIEW FAR *)lParam;` */

/* ms914053 "TVN_ENDLABELEDIT": `TVN_ENDLABELEDIT ptvdi=(TV_DISPINFO FAR *)lParam;` */

/* ms914054 "TVN_GETDISPINFO": `TVN_GETDISPINFOlptvdi=(TV_DISPINFO FAR *)lParam;` */

/* ms914055 "TVN_ITEMEXPANDED": `TVN_ITEMEXPANDEDpnmtv=(NM_TREEVIEW FAR *)lParam;` */

/* ms914056 "TVN_ITEMEXPANDING": `TVN_ITEMEXPANDINGpnmtv= (NM_TREEVIEW FAR *)lParam;` */

/* ms914057 "TVN_KEYDOWN": `TVN_KEYDOWNptvkd= (TV_KEYDOWN FAR *)lParam;` */

/* ms914058 "TVN_SELCHANGED": `TVN_SELCHANGEDpnmtv=(NM_TREEVIEW FAR *)lParam;` */

/* ms914059 "TVN_SELCHANGING": `TVN_SELCHANGINGpnmtv= (NM_TREEVIEW FAR *)lParam;` */

/* ms914060 "TVN_SETDISPINFO": `TVN_SETDISPINFOlptvdi= (TV_DISPINFO FAR *)lParam;` */

/* aa453780 "TreeView_CreateDragImage": `HIMAGELISTTreeView_CreateDragImage(hwnd,hitem );` */

/* aa453781 "TreeView_DeleteAllItems": `BOOLTreeView_DeleteAllItems( hwnd );` */

/* aa453782 "TreeView_DeleteItem": `BOOLTreeView_DeleteItem(hwnd,hitem );` */

/* aa453783 "TreeView_EditLabel": `HWNDTreeView_EditLabel(hwnd,hitem );` */

/* aa453784 "TreeView_EndEditLabelNow": `BOOLTreeView_EndEditLabelNow(hwnd,fCancel );` */

/* aa453785 "TreeView_EnsureVisible": `BOOLTreeView_EnsureVisible(hwnd,hitem );` */

/* aa453786 "TreeView_Expand": `BOOLTreeView_Expand(hwnd,hitem,flag );` */

/* aa453787 "TreeView_GetChild": `HTREEITEMTreeView_GetChild(hwnd,hitem );` */

/* aa453788 "TreeView_GetCount": `UINTTreeView_GetCount(hwnd );` */

/* aa453789 "TreeView_GetDropHilight": `HTREEITEMTreeView_GetDropHilight(hwnd);` */

/* aa453790 "TreeView_GetEditControl": `HWNDTreeView_GetEditControl(hwnd );` */

/* aa453791 "TreeView_GetFirstVisible": `HTREEITEMTreeView_GetFirstVisible(hwnd );` */

/* aa453794 "TreeView_GetISearchString": `BOOLTreeView_GetISearchString(hwnd,lpsz);` */

/* aa453792 "TreeView_GetImageList": `HIMAGELISTTreeView_GetImageList(hwnd,iImage );` */

/* aa453793 "TreeView_GetIndent": `UINTTreeView_GetIndent( hwnd );` */

/* aa453795 "TreeView_GetItem": `BOOLTreeView_GetItem(hwnd,pitem );` */

/* aa453796 "TreeView_GetItemRect": `BOOLTreeView_GetItemRect(hwnd,hitem,prc,fItemRect );` */

/* aa453797 "TreeView_GetNextItem": `HTREEITEMTreeView_GetNextItem(hwnd,hitem,flag );` */

/* aa453798 "TreeView_GetNextSibling": `HTREEITEMTreeView_GetNextSibling(hwnd,hitem );` */

/* aa453799 "TreeView_GetNextVisible": `HTREEITEMTreeView_GetNextVisible(hwnd,hitem );` */

/* aa453800 "TreeView_GetParent": `HTREEITEMTreeView_GetParent(hwnd,hitem );` */

/* aa453801 "TreeView_GetPrevSibling": `HTREEITEMTreeView_GetPrevSibling(hwnd,hitem );` */

/* aa453802 "TreeView_GetPrevVisible": `HTREEITEMTreeView_GetPrevVisible(hwnd,hitem );` */

/* aa453803 "TreeView_GetRoot": `HTREEITEMTreeView_GetRoot(hwnd );` */

/* aa453804 "TreeView_GetSelection": `HTREEITEMTreeView_GetSelection(hwnd );` */

/* aa453805 "TreeView_GetVisibleCount": `UINTTreeView_GetVisibleCount(hwnd );` */

/* aa453806 "TreeView_HitTest": `HTREEITEMTreeView_HitTest(hwnd,lpht );` */

/* aa453807 "TreeView_InsertItem": `HTREEITEMTreeView_InsertItem(hwnd,lpis );` */

/* aa453808 "TreeView_Select": `BOOLTreeView_Select(hwnd,hitem,flag );` */

/* aa453809 "TreeView_SelectDropTarget": `BOOLTreeView_SelectDropTarget(hwnd,hitem );` */

/* aa453810 "TreeView_SelectItem": `BOOLTreeView_SelectItem(hwnd,hitem );` */

/* aa453811 "TreeView_SelectSetFirstVisible": `BOOLTreeView_SelectSetFirstVisible(hwnd,hitem );` */

/* aa453812 "TreeView_SetImageList": `HIMAGELISTTreeView_SetImageList(hwnd,himl,iImage );` */

/* aa453813 "TreeView_SetIndent": `BOOLTreeView_SetIndent(hwnd,indent);` */

/* aa453814 "TreeView_SetItem": `BOOLTreeView_SetItem(hwnd,pitem );` */

/* aa453815 "TreeView_SortChildren": `BOOLTreeView_SortChildren(hwnd,hitem,fRecurse );` */

/* aa453816 "TreeView_SortChildrenCB": `BOOLTreeView_SortChildrenCB(hwnd,psort,fRecurse );` */

/* ------------------------------------------------------------------ */
/* Up-Down control (UDM_) */
/* ------------------------------------------------------------------ */

/* ms914068 "UDM_GETACCEL": `UDM_GETACCEL wParam = (WPARAM)cAccels;lParam = (LPARAM)(LPUDACCEL)paAccels;` */

/* ms914069 "UDM_GETBASE": `UDM_GETBASE wParam = 0;lParam = 0;` */

/* ms914070 "UDM_GETBUDDY": `UDM_GETBUDDY wParam = 0;lParam = 0;` */

/* ms914071 "UDM_GETPOS": `UDM_GETPOS wParam = 0;lParam = 0;` */

/* ms914072 "UDM_GETRANGE": `UDM_GETRANGE wParam = 0;lParam = 0;` */

/* ms914073 "UDM_GETRANGE32": `UDM_GETRANGE32 wParam = (WPARAM)(LPINT) pLow;lParam = (LPARAM)(LPINT)pHigh;` */

/* ms914074 "UDM_SETACCEL": `UDM_SETACCEL wParam = (WPARAM)nAccels;lParam = (LPARAM)(LPUDACCEL)aAccels;` */

/* ms914075 "UDM_SETBASE": `UDM_SETBASE wParam = (WPARAM)nBase;lParam = 0;` */

/* ms914076 "UDM_SETBUDDY": `UDM_SETBUDDY wParam = (WPARAM)(HWND)hwndBuddy;lParam = 0;` */

/* ms914077 "UDM_SETPOS": `UDM_SETPOS wParam = 0;lParam = (LPARAM)MAKELONG((short)nPos,0);` */

/* ms914078 "UDM_SETRANGE": `UDM_SETRANGE wParam = 0;lParam = (LPARAM)MAKELONG((short)nUpper,(short)nLower );` */

/* ms914079 "UDM_SETRANGE32": `UDM_SETRANGE32 wParam = (WPARAM)(int)iLow;lParam = (LPARAM)(int)iHigh;` */

/* ------------------------------------------------------------------ */
/* Shared notifications and misc (NM_/WM_/other) */
/* ------------------------------------------------------------------ */

/* aa453429 "LVINSERTGROUPSORTED" (printed verbatim; references held value-less constants):
 *   typedef struct LVINSERTGROUPSORTED { PFNLVGROUPCOMPARE pfnGroupCompare; LPVOID *pvData; LVGROUP lvGroup;} LVINSERTGROUPSORTED, *PLVINSERTGROUPSORTED
 */

/* aa453577 "PSM_ADDPAGE": `PSM_ADDPAGE wParam = 0;lParam = (LPARAM)(HPROPSHEETPAGE)hpage;` */

/* aa453578 "PSM_APPLY": `PSM_APPLY wParam = 0;lParam = 0;` */

/* aa453579 "PSM_CANCELTOCLOSE": `PSM_CANCELTOCLOSE` */

/* aa453580 "PSM_CHANGED": `PSM_CHANGED wParam = (WPARAM)(HWND)hwndPage;lParam= 0;` */

/* aa453581 "PSM_GETCURRENTPAGEHWND": `PSM_GETCURRENTPAGEHWND wParam= 0;lParam= 0;` */

/* aa453582 "PSM_GETTABCONTROL": `PSM_GETTABCONTROL wParam= 0;lParam= 0;` */

/* aa453583 "PSM_ISDIALOGMESSAGE": `PSM_ISDIALOGMESSAGE wParam= 0;lParam = (LPARAM)pMsg;` */

/* aa453584 "PSM_PRESSBUTTON": `PSM_PRESSBUTTON wParam= (WPARAM)(int)iButton; lParam= 0;` */

/* aa453585 "PSM_QUERYSIBLINGS": `PSM_QUERYSIBLINGS wParam= (WPARAM)param1;lParam= (LPARAM)param2;` */

/* aa453586 "PSM_REBOOTSYSTEM": `PSM_REBOOTSYSTEM wParam= 0;lParam= 0;` */

/* aa453587 "PSM_REMOVEPAGE": `PSM_REMOVEPAGE wParam = (WPARAM)(int)index;lParam= (LPARAM)(HPROPSHEETPAGE) hpage;` */

/* aa453588 "PSM_RESTARTWINDOWS": `PSM_RESTARTWINDOWS wParam= 0;lParam= 0;` */

/* aa453589 "PSM_SETCURSEL": `PSM_SETCURSEL wParam = (WPARAM)(int)index;lParam= (LPARAM)(HPROPSHEETPAGE)hpage;` */

/* aa453590 "PSM_SETCURSELID": `PSM_SETCURSELID wParam = 0;lParam = (LPARAM)(int)id;` */

/* aa453591 "PSM_SETFINISHTEXT": `PSM_SETFINISHTEXT wParam= 0;lParam = (LPARAM) (LPSTR)lpszText;` */

/* aa453592 "PSM_SETTITLE": `PSM_SETTITLE wParam= (WPARAM)(DWORD)dwStyle;lParam = (LPARAM)(LPCSTR)lpszText;` */

/* aa453593 "PSM_SETWIZBUTTONS": `PSM_SETWIZBUTTONSwParam= 0;` */

/* aa453594 "PSM_UNCHANGED": `PSM_UNCHANGED wParam = (WPARAM)(HWND)hwndPage;lParam= 0;` */

/* aa453429 "LVINSERTGROUPSORTED" is HELD as a structure: the
 * print `typedef struct LVINSERTGROUPSORTED { PFNLVGROUPCOMPARE
 * pfnGroupCompare; LPVOID *pvData; LVGROUP lvGroup;}` names
 * PFNLVGROUPCOMPARE, which has no typedef or signature on any
 * page in the corpus (used by aa453405/aa453429/aa453519 only). */

/* LVGROUP flag names printed on aa453426 (mask/state/uAlign):
 *   LVGF_ALIGN LVGF_FOOTER LVGF_GROUPID LVGF_HEADER LVGF_NONE
 *   LVGF_STATE
 *   LVGS_NORMAL
 *   LVGA_FOOTER_CENTER LVGA_FOOTER_LEFT LVGA_FOOTER_RIGHT
 *   LVGA_HEADER_CENTER LVGA_HEADER_LEFT LVGA_HEADER_RIGHT
 * LVGROUPMETRICS mask names printed on aa453427:
 *   LVGMF_BORDERCOLOR LVGMF_BORDERSIZE LVGMF_NONE
 *   LVGMF_TEXTCOLOR
 * (names only; no values printed anywhere). */


/* ------------------------------------------------------------------ */
/* M94 part 2 -- late-found rows.  ms913827 TB_SETCMDID's Requirements */
/* prints "Header: Commctrl.h" without the trailing period the other  */
/* rows carry (that spelling difference is why the M94 part-1 sweep   */
/* missed it); aa453830 TTM_GETTIPTEXTCOLOR's Requirements prints     */
/* "Header: Windows.h" (archive quirk -- the row belongs to the       */
/* tooltip family).  The three ListView_*WorkAreas macros are the     */
/* Pcommctrl.h-homed rows; their pages print full #define bodies,     */
/* recorded verbatim (they reference the held value-less LVM_*        */
/* constants).                                                         */
/* ------------------------------------------------------------------ */

/* ms913827 "TB_SETCMDID": `TB_SETCMDID wParam=(WPARAM)(UINT)index;lParam=(WPARAM)(UINT)cmdId;` */
/* aa453830 "TTM_GETTIPTEXTCOLOR": `TTM_GETTIPTEXTCOLOR wParam= 0;lParam= 0;` */
/* aa453343 "ListView_GetNumberOfWorkAreas" (printed body):
 *   #define ListView_GetNumberOfWorkAreas(hwnd, pnWorkAreas) \
 *       (BOOL)SNDMSG((hwnd), LVM_GETNUMBEROFWORKAREAS, 0, \
 *       (LPARAM)(UINT *)(pnWorkAreas))
 */
/* aa453353 "ListView_GetWorkAreas" (printed body):
 *   #define ListView_GetWorkAreas(hwnd, nWorkAreas, prc) \
 *       (BOOL)SNDMSG((hwnd), LVM_GETWORKAREAS, (WPARAM)(int)nWorkAreas, \
 *       (LPARAM)(RECT FAR*)(prc))
 */
/* aa453377 "ListView_SetWorkAreas" (printed body):
 *   #define ListView_SetWorkAreas(hwnd, nWorkAreas, prc) \
 *       (BOOL)SNDMSG((hwnd), LVM_SETWORKAREAS, (WPARAM)(int)nWorkAreas, \
 *       (LPARAM)(RECT FAR*)(prc))
 */

#ifdef __cplusplus
}
#endif

/* ================================================================== */
/* ================================================================== */
/* M96 value adoption -- values adopted from the CeGCC-lineage w32api
 * reference (R1, public domain; docs/clean-room.md par.4
 * revision 2026-09-10).  Every name below is documented by
 * the official CE pages WITHOUT a value (see the record
 * comments and the held ledger in this header); the value
 * is a CE-era ABI fact carried by the CE lineage itself.
 * Desktop mingw-w64 was considered and EXCLUDED as a source
 * (desktop-era values; policy note in clean-room.md).  R1's
 * license-exception files (winsock*, gl*) are unused.
 * ================================================================== */

/* ---- ACM_ family (3 names; R1) ---- */
#define ACM_PLAY                                     0x0465
#define ACM_STOP                                     0x0466
#define ACM_OPEN                                     0x0467

/* ---- ACN_ family (2 names; R1) ---- */
#define ACN_START                                    0x0001
#define ACN_STOP                                     0x0002

/* ---- ACS_ family (4 names; R1) ---- */
#define ACS_CENTER                                   0x0001
#define ACS_TRANSPARENT                              0x0002
#define ACS_AUTOPLAY                                 0x0004
#define ACS_TIMER                                    0x0008

/* ---- CCS_ family (1 names; R1) ---- */
#define CCS_VERT                                     0x0080

/* ---- CDDS_ family (9 names; R1) ---- */
#define CDDS_PREPAINT                                0x0001
#define CDDS_POSTPAINT                               0x0002
#define CDDS_PREERASE                                0x0003
#define CDDS_POSTERASE                               0x0004
#define CDDS_ITEM                                    0x10000
#define CDDS_ITEMPREPAINT                            0x10001
#define CDDS_ITEMPOSTPAINT                           0x10002
#define CDDS_ITEMPREERASE                            0x10003
#define CDDS_ITEMPOSTERASE                           0x10004

/* ---- CDIS_ family (7 names; R1) ---- */
#define CDIS_SELECTED                                0x0001
#define CDIS_GRAYED                                  0x0002
#define CDIS_DISABLED                                0x0004
#define CDIS_CHECKED                                 0x0008
#define CDIS_FOCUS                                   0x0010
#define CDIS_DEFAULT                                 0x0020
#define CDIS_HOT                                     0x0040

/* ---- CDRF_ family (7 names; R1) ---- */
#define CDRF_DODEFAULT                               0x0000
#define CDRF_NEWFONT                                 0x0002
#define CDRF_SKIPDEFAULT                             0x0004
#define CDRF_NOTIFYPOSTPAINT                         0x0010
#define CDRF_NOTIFYITEMDRAW                          0x0020
#define CDRF_NOTIFYPOSTERASE                         0x0040
#define CDRF_NOTIFYITEMERASE                         0x0080

/* ---- CMDBAR_ family (2 names; R1) ---- */
#define CMDBAR_HELP                                  0x000B
#define CMDBAR_OK                                    0xF000

/* ---- DTM_ family (10 names; R1) ---- */
#define DTM_GETSYSTEMTIME                            0x1001
#define DTM_SETSYSTEMTIME                            0x1002
#define DTM_GETRANGE                                 0x1003
#define DTM_SETRANGE                                 0x1004
#define DTM_SETMCCOLOR                               0x1006
#define DTM_GETMCCOLOR                               0x1007
#define DTM_GETMONTHCAL                              0x1008
#define DTM_SETMCFONT                                0x1009
#define DTM_GETMCFONT                                0x100A
#define DTM_SETFORMAT                                0x1050

/* ---- DTN_ family (7 names; R1) ---- */
#define DTN_DATETIMECHANGE                           (-759)
#define DTN_DROPDOWN                                 (-754)
#define DTN_CLOSEUP                                  (-753)
#define DTN_USERSTRING                               (-745)
#define DTN_WMKEYDOWN                                (-744)
#define DTN_FORMAT                                   (-743)
#define DTN_FORMATQUERY                              (-742)

/* ---- DTS_ family (1 names; R1) ---- */
#define DTS_SHOWNONE                                 0x0002

/* ---- GDT_ family (2 names; R1) ---- */
#define GDT_VALID                                    0x0000
#define GDT_NONE                                     0x0001

/* ---- GDTR_ family (2 names; R1) ---- */
#define GDTR_MIN                                     0x0001
#define GDTR_MAX                                     0x0002

/* ---- GMR_ family (2 names; R1) ---- */
#define GMR_VISIBLE                                  0x0000
#define GMR_DAYSTATE                                 0x0001

/* ---- HDF_ family (10 names; R1) ---- */
#define HDF_LEFT                                     0x0000
#define HDF_RIGHT                                    0x0001
#define HDF_CENTER                                   0x0002
#define HDF_JUSTIFYMASK                              0x0003
#define HDF_RTLREADING                               0x0004
#define HDF_IMAGE                                    0x0800
#define HDF_BITMAP_ON_RIGHT                          0x1000
#define HDF_BITMAP                                   0x2000
#define HDF_STRING                                   0x4000
#define HDF_OWNERDRAW                                0x8000

/* ---- HDI_ family (9 names; R1) ---- */
#define HDI_HEIGHT                                   0x0001
#define HDI_WIDTH                                    0x0001
#define HDI_TEXT                                     0x0002
#define HDI_FORMAT                                   0x0004
#define HDI_LPARAM                                   0x0008
#define HDI_BITMAP                                   0x0010
#define HDI_IMAGE                                    0x0020
#define HDI_DI_SETITEM                               0x0040
#define HDI_ORDER                                    0x0080

/* ---- HDM_ family (15 names; R1) ---- */
#define HDM_GETITEMCOUNT                             0x1200
#define HDM_DELETEITEM                               0x1202
#define HDM_LAYOUT                                   0x1205
#define HDM_HITTEST                                  0x1206
#define HDM_GETITEMRECT                              0x1207
#define HDM_SETIMAGELIST                             0x1208
#define HDM_GETIMAGELIST                             0x1209
#define HDM_INSERTITEM                               0x120A
#define HDM_GETITEM                                  0x120B
#define HDM_SETITEM                                  0x120C
#define HDM_ORDERTOINDEX                             0x120F
#define HDM_CREATEDRAGIMAGE                          0x1210
#define HDM_GETORDERARRAY                            0x1211
#define HDM_SETORDERARRAY                            0x1212
#define HDM_SETHOTDIVIDER                            0x1213

/* ---- HDN_ family (11 names; R1) ---- */
#define HDN_GETDISPINFO                              (-329)
#define HDN_TRACK                                    (-328)
#define HDN_ENDTRACK                                 (-327)
#define HDN_BEGINTRACK                               (-326)
#define HDN_DIVIDERDBLCLICK                          (-325)
#define HDN_ITEMDBLCLICK                             (-323)
#define HDN_ITEMCLICK                                (-322)
#define HDN_ITEMCHANGED                              (-321)
#define HDN_ITEMCHANGING                             (-320)
#define HDN_ENDDRAG                                  (-311)
#define HDN_BEGINDRAG                                (-310)

/* ---- HDS_ family (2 names; R1) ---- */
#define HDS_BUTTONS                                  0x0002
#define HDS_DRAGDROP                                 0x0040

/* ---- HHT_ family (6 names; R1) ---- */
#define HHT_NOWHERE                                  0x0001
#define HHT_ONHEADER                                 0x0002
#define HHT_ONDIVIDER                                0x0004
#define HHT_ONDIVOPEN                                0x0008
#define HHT_TORIGHT                                  0x0400
#define HHT_TOLEFT                                   0x0800

/* ---- ICC_ family (12 names; R1) ---- */
#define ICC_LISTVIEW_CLASSES                         0x0001
#define ICC_TREEVIEW_CLASSES                         0x0002
#define ICC_BAR_CLASSES                              0x0004
#define ICC_TAB_CLASSES                              0x0008
#define ICC_UPDOWN_CLASS                             0x0010
#define ICC_PROGRESS_CLASS                           0x0020
#define ICC_HOTKEY_CLASS                             0x0040
#define ICC_ANIMATE_CLASS                            0x0080
#define ICC_DATE_CLASSES                             0x0100
#define ICC_USEREX_CLASSES                           0x0200
#define ICC_COOL_CLASSES                             0x0400
#define ICC_INTERNET_CLASSES                         0x0800

/* ---- IDB_ family (6 names; R1) ---- */
#define IDB_STD_SMALL_COLOR                          0x0000
#define IDB_STD_LARGE_COLOR                          0x0001
#define IDB_VIEW_SMALL_COLOR                         0x0004
#define IDB_VIEW_LARGE_COLOR                         0x0005
#define IDB_HIST_SMALL_COLOR                         0x0008
#define IDB_HIST_LARGE_COLOR                         0x0009

/* ---- ILCF_ family (2 names; R1) ---- */
#define ILCF_MOVE                                    0x0000
#define ILCF_SWAP                                    0x0001

/* ---- LVGIT_ family (1 names; R1) ---- */
#define LVGIT_UNFOLDED                               0x0001

/* ---- LVIF_ family (1 names; R1) ---- */
#define LVIF_TEXT                                    0x0001

/* ---- LVIS_ family (4 names; R1) ---- */
#define LVIS_FOCUSED                                 0x0001
#define LVIS_SELECTED                                0x0002
#define LVIS_CUT                                     0x0004
#define LVIS_DROPHILITED                             0x0008

/* ---- LVM_ family (84 names; R1) ---- */
#define LVM_GETBKCOLOR                               0x1000
#define LVM_SETBKCOLOR                               0x1001
#define LVM_GETIMAGELIST                             0x1002
#define LVM_SETIMAGELIST                             0x1003
#define LVM_GETITEMCOUNT                             0x1004
#define LVM_DELETEITEM                               0x1008
#define LVM_DELETEALLITEMS                           0x1009
#define LVM_GETCALLBACKMASK                          0x100A
#define LVM_SETCALLBACKMASK                          0x100B
#define LVM_GETNEXTITEM                              0x100C
#define LVM_GETITEMRECT                              0x100E
#define LVM_SETITEMPOSITION                          0x100F
#define LVM_GETITEMPOSITION                          0x1010
#define LVM_HITTEST                                  0x1012
#define LVM_ENSUREVISIBLE                            0x1013
#define LVM_SCROLL                                   0x1014
#define LVM_REDRAWITEMS                              0x1015
#define LVM_ARRANGE                                  0x1016
#define LVM_GETEDITCONTROL                           0x1018
#define LVM_DELETECOLUMN                             0x101C
#define LVM_GETCOLUMNWIDTH                           0x101D
#define LVM_SETCOLUMNWIDTH                           0x101E
#define LVM_GETHEADER                                0x101F
#define LVM_CREATEDRAGIMAGE                          0x1021
#define LVM_GETVIEWRECT                              0x1022
#define LVM_GETTEXTCOLOR                             0x1023
#define LVM_SETTEXTCOLOR                             0x1024
#define LVM_GETTEXTBKCOLOR                           0x1025
#define LVM_SETTEXTBKCOLOR                           0x1026
#define LVM_GETTOPINDEX                              0x1027
#define LVM_GETCOUNTPERPAGE                          0x1028
#define LVM_GETORIGIN                                0x1029
#define LVM_UPDATE                                   0x102A
#define LVM_SETITEMSTATE                             0x102B
#define LVM_GETITEMSTATE                             0x102C
#define LVM_SETITEMCOUNT                             0x102F
#define LVM_SORTITEMS                                0x1030
#define LVM_SETITEMPOSITION32                        0x1031
#define LVM_GETSELECTEDCOUNT                         0x1032
#define LVM_GETITEMSPACING                           0x1033
#define LVM_SETICONSPACING                           0x1035
#define LVM_SETEXTENDEDLISTVIEWSTYLE                 0x1036
#define LVM_GETEXTENDEDLISTVIEWSTYLE                 0x1037
#define LVM_GETSUBITEMRECT                           0x1038
#define LVM_SUBITEMHITTEST                           0x1039
#define LVM_SETCOLUMNORDERARRAY                      0x103A
#define LVM_GETCOLUMNORDERARRAY                      0x103B
#define LVM_APPROXIMATEVIEWRECT                      0x1040
#define LVM_SETWORKAREAS                             0x1041
#define LVM_GETSELECTIONMARK                         0x1042
#define LVM_SETSELECTIONMARK                         0x1043
#define LVM_GETWORKAREAS                             0x1046
#define LVM_GETNUMBEROFWORKAREAS                     0x1049
#define LVM_SETTOOLTIPS                              0x104A
#define LVM_GETITEM                                  0x104B
#define LVM_SETITEM                                  0x104C
#define LVM_INSERTITEM                               0x104D
#define LVM_GETTOOLTIPS                              0x104E
#define LVM_FINDITEM                                 0x1053
#define LVM_GETSTRINGWIDTH                           0x1057
#define LVM_GETCOLUMN                                0x105F
#define LVM_SETCOLUMN                                0x1060
#define LVM_INSERTCOLUMN                             0x1061
#define LVM_GETITEMTEXT                              0x1073
#define LVM_SETITEMTEXT                              0x1074
#define LVM_GETISEARCHSTRING                         0x1075
#define LVM_EDITLABEL                                0x1076
#define LVM_SETBKIMAGE                               0x108A
#define LVM_GETBKIMAGE                               0x108B
#define LVM_INSERTGROUP                              0x1091
#define LVM_SETGROUPINFO                             0x1093
#define LVM_GETGROUPINFO                             0x1095
#define LVM_REMOVEGROUP                              0x1096
#define LVM_MOVEGROUP                                0x1097
#define LVM_SETGROUPMETRICS                          0x109B
#define LVM_GETGROUPMETRICS                          0x109C
#define LVM_ENABLEGROUPVIEW                          0x109D
#define LVM_SORTGROUPS                               0x109E
#define LVM_INSERTGROUPSORTED                        0x109F
#define LVM_REMOVEALLGROUPS                          0x10A0
#define LVM_HASGROUP                                 0x10A1
#define LVM_SETINFOTIP                               0x10AD
#define LVM_ISGROUPVIEWENABLED                       0x10AF
#define LVM_MAPIDTOINDEX                             0x10B5

/* ---- LVN_ family (18 names; R1) ---- */
#define LVN_ODFINDITEM                               (-179)
#define LVN_SETDISPINFO                              (-178)
#define LVN_GETDISPINFO                              (-177)
#define LVN_ENDLABELEDIT                             (-176)
#define LVN_BEGINLABELEDIT                           (-175)
#define LVN_GETINFOTIP                               (-158)
#define LVN_MARQUEEBEGIN                             (-156)
#define LVN_KEYDOWN                                  (-155)
#define LVN_ODSTATECHANGED                           (-115)
#define LVN_ITEMACTIVATE                             (-114)
#define LVN_ODCACHEHINT                              (-113)
#define LVN_BEGINDRAG                                (-109)
#define LVN_COLUMNCLICK                              (-108)
#define LVN_DELETEALLITEMS                           (-104)
#define LVN_DELETEITEM                               (-103)
#define LVN_INSERTITEM                               (-102)
#define LVN_ITEMCHANGED                              (-101)
#define LVN_ITEMCHANGING                             (-100)

/* ---- MCHT_ family (15 names; R1) ---- */
#define MCHT_NOWHERE                                 0x0000
#define MCHT_TITLE                                   0x10000
#define MCHT_TITLEMONTH                              0x10001
#define MCHT_TITLEYEAR                               0x10002
#define MCHT_CALENDAR                                0x20000
#define MCHT_CALENDARDATE                            0x20001
#define MCHT_CALENDARDAY                             0x20002
#define MCHT_CALENDARWEEKNUM                         0x20003
#define MCHT_TODAYLINK                               0x30000
#define MCHT_NEXT                                    0x1000000
#define MCHT_TITLEBTNNEXT                            0x1010003
#define MCHT_CALENDARDATENEXT                        0x1020001
#define MCHT_PREV                                    0x2000000
#define MCHT_TITLEBTNPREV                            0x2010003
#define MCHT_CALENDARDATEPREV                        0x2020001

/* ---- MCM_ family (21 names; R1) ---- */
#define MCM_GETCURSEL                                0x1001
#define MCM_SETCURSEL                                0x1002
#define MCM_GETMAXSELCOUNT                           0x1003
#define MCM_SETMAXSELCOUNT                           0x1004
#define MCM_GETSELRANGE                              0x1005
#define MCM_SETSELRANGE                              0x1006
#define MCM_GETMONTHRANGE                            0x1007
#define MCM_SETDAYSTATE                              0x1008
#define MCM_GETMINREQRECT                            0x1009
#define MCM_SETCOLOR                                 0x100A
#define MCM_GETCOLOR                                 0x100B
#define MCM_SETTODAY                                 0x100C
#define MCM_GETTODAY                                 0x100D
#define MCM_HITTEST                                  0x100E
#define MCM_SETFIRSTDAYOFWEEK                        0x100F
#define MCM_GETFIRSTDAYOFWEEK                        0x1010
#define MCM_GETRANGE                                 0x1011
#define MCM_SETRANGE                                 0x1012
#define MCM_GETMONTHDELTA                            0x1013
#define MCM_SETMONTHDELTA                            0x1014
#define MCM_GETMAXTODAYWIDTH                         0x1015

/* ---- MCN_ family (3 names; R1) ---- */
#define MCN_SELCHANGE                                (-749)
#define MCN_GETDAYSTATE                              (-747)
#define MCN_SELECT                                   (-746)

/* ---- MCS_ family (3 names; R1) ---- */
#define MCS_DAYSTATE                                 0x0001
#define MCS_MULTISELECT                              0x0002
#define MCS_WEEKNUMBERS                              0x0004

/* ---- MCSC_ family (6 names; R1) ---- */
#define MCSC_BACKGROUND                              0x0000
#define MCSC_TEXT                                    0x0001
#define MCSC_TITLEBK                                 0x0002
#define MCSC_TITLETEXT                               0x0003
#define MCSC_MONTHBK                                 0x0004
#define MCSC_TRAILINGTEXT                            0x0005

/* ---- NM_ family (11 names; R1) ---- */
#define NM_KEYDOWN                                   (-15)
#define NM_HOVER                                     (-13)
#define NM_CUSTOMDRAW                                (-12)
#define NM_KILLFOCUS                                 (-8)
#define NM_SETFOCUS                                  (-7)
#define NM_RDBLCLK                                   (-6)
#define NM_RCLICK                                    (-5)
#define NM_RETURN                                    (-4)
#define NM_DBLCLK                                    (-3)
#define NM_CLICK                                     (-2)
#define NM_OUTOFMEMORY                               (-1)

/* ---- PBM_ family (8 names; R1) ---- */
#define PBM_SETRANGE                                 0x0401
#define PBM_SETPOS                                   0x0402
#define PBM_DELTAPOS                                 0x0403
#define PBM_SETSTEP                                  0x0404
#define PBM_STEPIT                                   0x0405
#define PBM_SETRANGE32                               0x0406
#define PBM_GETRANGE                                 0x0407
#define PBM_GETPOS                                   0x0408

/* ---- PSM_ family (18 names; R1) ---- */
#define PSM_SETCURSEL                                0x0465
#define PSM_REMOVEPAGE                               0x0466
#define PSM_ADDPAGE                                  0x0467
#define PSM_CHANGED                                  0x0468
#define PSM_RESTARTWINDOWS                           0x0469
#define PSM_REBOOTSYSTEM                             0x046A
#define PSM_CANCELTOCLOSE                            0x046B
#define PSM_QUERYSIBLINGS                            0x046C
#define PSM_UNCHANGED                                0x046D
#define PSM_APPLY                                    0x046E
#define PSM_SETWIZBUTTONS                            0x0470
#define PSM_PRESSBUTTON                              0x0471
#define PSM_SETCURSELID                              0x0472
#define PSM_GETTABCONTROL                            0x0474
#define PSM_ISDIALOGMESSAGE                          0x0475
#define PSM_GETCURRENTPAGEHWND                       0x0476
#define PSM_SETTITLE                                 0x0478
#define PSM_SETFINISHTEXT                            0x0479

/* ---- RB_ family (22 names; R1) ---- */
#define RB_DELETEBAND                                0x0402
#define RB_GETBARINFO                                0x0403
#define RB_SETBARINFO                                0x0404
#define RB_SETPARENT                                 0x0407
#define RB_GETRECT                                   0x0409
#define RB_INSERTBAND                                0x040A
#define RB_SETBANDINFO                               0x040B
#define RB_GETBANDCOUNT                              0x040C
#define RB_GETROWCOUNT                               0x040D
#define RB_GETROWHEIGHT                              0x040E
#define RB_IDTOINDEX                                 0x0410
#define RB_SETBKCOLOR                                0x0413
#define RB_GETBKCOLOR                                0x0414
#define RB_SETTEXTCOLOR                              0x0415
#define RB_GETTEXTCOLOR                              0x0416
#define RB_SIZETORECT                                0x0417
#define RB_GETBARHEIGHT                              0x041B
#define RB_GETBANDINFO                               0x041C
#define RB_MINIMIZEBAND                              0x041E
#define RB_MAXIMIZEBAND                              0x041F
#define RB_GETBANDBORDERS                            0x0422
#define RB_SHOWBAND                                  0x0423

/* ---- RBBIM_ family (1 names; R1) ---- */
#define RBBIM_CHILD                                  0x0010

/* ---- RBBS_ family (8 names; R1) ---- */
#define RBBS_BREAK                                   0x0001
#define RBBS_FIXEDSIZE                               0x0002
#define RBBS_CHILDEDGE                               0x0004
#define RBBS_HIDDEN                                  0x0008
#define RBBS_NOVERT                                  0x0010
#define RBBS_FIXEDBMP                                0x0020
#define RBBS_VARIABLEHEIGHT                          0x0040
#define RBBS_GRIPPERALWAYS                           0x0080

/* ---- RBIM_ family (1 names; R1) ---- */
#define RBIM_IMAGELIST                               0x0001

/* ---- RBN_ family (5 names; R1) ---- */
#define RBN_ENDDRAG                                  (-836)
#define RBN_BEGINDRAG                                (-835)
#define RBN_AUTOSIZE                                 (-834)
#define RBN_LAYOUTCHANGED                            (-833)
#define RBN_HEIGHTCHANGE                             (-831)

/* ---- SB_ family (13 names; R1) ---- */
#define SB_SETPARTS                                  0x0404
#define SB_GETPARTS                                  0x0406
#define SB_GETBORDERS                                0x0407
#define SB_SETMINHEIGHT                              0x0408
#define SB_SIMPLE                                    0x0409
#define SB_GETRECT                                   0x040A
#define SB_SETTEXT                                   0x040B
#define SB_GETTEXTLENGTH                             0x040C
#define SB_GETTEXT                                   0x040D
#define SB_ISSIMPLE                                  0x040E
#define SB_SETICON                                   0x040F
#define SB_GETICON                                   0x0414
#define SB_SETBKCOLOR                                0x2001

/* ---- SBT_ family (4 names; R1) ---- */
#define SBT_NOBORDERS                                0x0100
#define SBT_POPOUT                                   0x0200
#define SBT_RTLREADING                               0x0400
#define SBT_OWNERDRAW                                0x1000

/* ---- STD_ family (15 names; R1) ---- */
#define STD_CUT                                      0x0000
#define STD_COPY                                     0x0001
#define STD_PASTE                                    0x0002
#define STD_UNDO                                     0x0003
#define STD_REDOW                                    0x0004
#define STD_DELETE                                   0x0005
#define STD_FILENEW                                  0x0006
#define STD_FILEOPEN                                 0x0007
#define STD_FILESAVE                                 0x0008
#define STD_PRINTPRE                                 0x0009
#define STD_PROPERTIES                               0x000A
#define STD_HELP                                     0x000B
#define STD_FIND                                     0x000C
#define STD_REPLACE                                  0x000D
#define STD_PRINT                                    0x000E

/* ---- TB_ family (56 names; R1) ---- */
#define TB_LINEUP                                    0x0000
#define TB_LINEDOWN                                  0x0001
#define TB_PAGEUP                                    0x0002
#define TB_PAGEDOWN                                  0x0003
#define TB_ENABLEBUTTON                              0x0401
#define TB_CHECKBUTTON                               0x0402
#define TB_PRESSBUTTON                               0x0403
#define TB_HIDEBUTTON                                0x0404
#define TB_INDETERMINATE                             0x0405
#define TB_ISBUTTONENABLED                           0x0409
#define TB_ISBUTTONCHECKED                           0x040A
#define TB_ISBUTTONPRESSED                           0x040B
#define TB_ISBUTTONHIDDEN                            0x040C
#define TB_ISBUTTONINDETERMINATE                     0x040D
#define TB_ISBUTTONHIGHLIGHTED                       0x040E
#define TB_SETSTATE                                  0x0411
#define TB_GETSTATE                                  0x0412
#define TB_ADDBITMAP                                 0x0413
#define TB_ADDBUTTONS                                0x0414
#define TB_INSERTBUTTON                              0x0415
#define TB_DELETEBUTTON                              0x0416
#define TB_BUTTONCOUNT                               0x0418
#define TB_COMMANDTOINDEX                            0x0419
#define TB_GETITEMRECT                               0x041D
#define TB_BUTTONSTRUCTSIZE                          0x041E
#define TB_SETBUTTONSIZE                             0x041F
#define TB_SETBITMAPSIZE                             0x0420
#define TB_AUTOSIZE                                  0x0421
#define TB_GETTOOLTIPS                               0x0423
#define TB_SETTOOLTIPS                               0x0424
#define TB_SETPARENT                                 0x0425
#define TB_SETROWS                                   0x0427
#define TB_GETROWS                                   0x0428
#define TB_GETBITMAPFLAGS                            0x0429
#define TB_SETCMDID                                  0x042A
#define TB_CHANGEBITMAP                              0x042B
#define TB_GETBITMAP                                 0x042C
#define TB_REPLACEBITMAP                             0x042E
#define TB_SETINDENT                                 0x042F
#define TB_SETIMAGELIST                              0x0430
#define TB_GETIMAGELIST                              0x0431
#define TB_LOADIMAGES                                0x0432
#define TB_GETRECT                                   0x0433
#define TB_SETDISABLEDIMAGELIST                      0x0436
#define TB_GETDISABLEDIMAGELIST                      0x0437
#define TB_SETSTYLE                                  0x0438
#define TB_GETSTYLE                                  0x0439
#define TB_GETBUTTONSIZE                             0x043A
#define TB_SETBUTTONWIDTH                            0x043B
#define TB_SETMAXTEXTROWS                            0x043C
#define TB_GETTEXTROWS                               0x043D
#define TB_GETBUTTONINFO                             0x043F
#define TB_SETBUTTONINFO                             0x0440
#define TB_SETDRAWTEXTFLAGS                          0x0446
#define TB_GETBUTTONTEXT                             0x044B
#define TB_ADDSTRING                                 0x044D

/* ---- TBBF_ family (1 names; R1) ---- */
#define TBBF_LARGE                                   0x0001

/* ---- TBCD_ family (3 names; R1) ---- */
#define TBCD_TICS                                    0x0001
#define TBCD_THUMB                                   0x0002
#define TBCD_CHANNEL                                 0x0003

/* ---- TBIF_ family (8 names; R1) ---- */
#define TBIF_IMAGE                                   0x0001
#define TBIF_TEXT                                    0x0002
#define TBIF_STATE                                   0x0004
#define TBIF_STYLE                                   0x0008
#define TBIF_LPARAM                                  0x0010
#define TBIF_COMMAND                                 0x0020
#define TBIF_SIZE                                    0x0040
#define TBIF_BYINDEX                                 0x80000000

/* ---- TBM_ family (29 names; R1) ---- */
#define TBM_GETRANGEMIN                              0x0401
#define TBM_GETRANGEMAX                              0x0402
#define TBM_GETTIC                                   0x0403
#define TBM_SETTIC                                   0x0404
#define TBM_SETPOS                                   0x0405
#define TBM_SETRANGE                                 0x0406
#define TBM_SETRANGEMIN                              0x0407
#define TBM_SETRANGEMAX                              0x0408
#define TBM_CLEARTICS                                0x0409
#define TBM_SETSEL                                   0x040A
#define TBM_SETSELSTART                              0x040B
#define TBM_SETSELEND                                0x040C
#define TBM_GETPTICS                                 0x040E
#define TBM_GETTICPOS                                0x040F
#define TBM_GETNUMTICS                               0x0410
#define TBM_GETSELSTART                              0x0411
#define TBM_GETSELEND                                0x0412
#define TBM_CLEARSEL                                 0x0413
#define TBM_SETTICFREQ                               0x0414
#define TBM_SETPAGESIZE                              0x0415
#define TBM_GETPAGESIZE                              0x0416
#define TBM_SETLINESIZE                              0x0417
#define TBM_GETLINESIZE                              0x0418
#define TBM_GETTHUMBRECT                             0x0419
#define TBM_GETCHANNELRECT                           0x041A
#define TBM_SETTHUMBLENGTH                           0x041B
#define TBM_GETTHUMBLENGTH                           0x041C
#define TBM_SETBUDDY                                 0x0420
#define TBM_GETBUDDY                                 0x0421

/* ---- TBN_ family (7 names; R1) ---- */
#define TBN_GETBUTTONINFO                            (-720)
#define TBN_DRAGOUT                                  (-714)
#define TBN_DROPDOWN                                 (-710)
#define TBN_QUERYDELETE                              (-707)
#define TBN_QUERYINSERT                              (-706)
#define TBN_ENDDRAG                                  (-702)
#define TBN_BEGINDRAG                                (-701)

/* ---- TBS_ family (4 names; R1) ---- */
#define TBS_HORZ                                     0x0000
#define TBS_VERT                                     0x0002
#define TBS_ENABLESELRANGE                           0x0020
#define TBS_FIXEDLENGTH                              0x0040

/* ---- TBSTYLE_ family (2 names; R1) ---- */
#define TBSTYLE_DROPDOWN                             0x0008
#define TBSTYLE_WRAPABLE                             0x0200

/* ---- TCHT_ family (4 names; R1) ---- */
#define TCHT_NOWHERE                                 0x0001
#define TCHT_ONITEMICON                              0x0002
#define TCHT_ONITEMLABEL                             0x0004
#define TCHT_ONITEM                                  0x0006

/* ---- TCIF_ family (5 names; R1) ---- */
#define TCIF_TEXT                                    0x0001
#define TCIF_IMAGE                                   0x0002
#define TCIF_RTLREADING                              0x0004
#define TCIF_PARAM                                   0x0008
#define TCIF_STATE                                   0x0010

/* ---- TCIS_ family (1 names; R1) ---- */
#define TCIS_BUTTONPRESSED                           0x0001

/* ---- TCM_ family (25 names; R1) ---- */
#define TCM_GETIMAGELIST                             0x1302
#define TCM_SETIMAGELIST                             0x1303
#define TCM_GETITEMCOUNT                             0x1304
#define TCM_DELETEITEM                               0x1308
#define TCM_DELETEALLITEMS                           0x1309
#define TCM_GETITEMRECT                              0x130A
#define TCM_GETCURSEL                                0x130B
#define TCM_SETCURSEL                                0x130C
#define TCM_HITTEST                                  0x130D
#define TCM_SETITEMEXTRA                             0x130E
#define TCM_ADJUSTRECT                               0x1328
#define TCM_SETITEMSIZE                              0x1329
#define TCM_REMOVEIMAGE                              0x132A
#define TCM_SETPADDING                               0x132B
#define TCM_GETROWCOUNT                              0x132C
#define TCM_GETCURFOCUS                              0x132F
#define TCM_SETCURFOCUS                              0x1330
#define TCM_SETMINTABWIDTH                           0x1331
#define TCM_DESELECTALL                              0x1332
#define TCM_HIGHLIGHTITEM                            0x1333
#define TCM_SETEXTENDEDSTYLE                         0x1334
#define TCM_GETEXTENDEDSTYLE                         0x1335
#define TCM_GETITEM                                  0x133C
#define TCM_SETITEM                                  0x133D
#define TCM_INSERTITEM                               0x133E

/* ---- TCN_ family (3 names; R1) ---- */
#define TCN_SELCHANGING                              (-552)
#define TCN_SELCHANGE                                (-551)
#define TCN_KEYDOWN                                  (-550)

/* ---- TCS_ family (2 names; R1) ---- */
#define TCS_EX_FLATSEPARATORS                        0x0001
#define TCS_BUTTONS                                  0x0100

/* ---- TTF_ family (6 names; R1) ---- */
#define TTF_IDISHWND                                 0x0001
#define TTF_CENTERTIP                                0x0002
#define TTF_RTLREADING                               0x0004
#define TTF_SUBCLASS                                 0x0010
#define TTF_ABSOLUTE                                 0x0080
#define TTF_DI_SETITEM                               0x8000

/* ---- TTM_ family (27 names; R1) ---- */
#define TTM_ACTIVATE                                 0x0401
#define TTM_SETDELAYTIME                             0x0403
#define TTM_RELAYEVENT                               0x0407
#define TTM_GETTOOLCOUNT                             0x040D
#define TTM_WINDOWFROMPOINT                          0x0410
#define TTM_TRACKACTIVATE                            0x0411
#define TTM_TRACKPOSITION                            0x0412
#define TTM_SETTIPBKCOLOR                            0x0413
#define TTM_SETTIPTEXTCOLOR                          0x0414
#define TTM_GETDELAYTIME                             0x0415
#define TTM_GETTIPBKCOLOR                            0x0416
#define TTM_GETTIPTEXTCOLOR                          0x0417
#define TTM_SETMAXTIPWIDTH                           0x0418
#define TTM_GETMAXTIPWIDTH                           0x0419
#define TTM_SETMARGIN                                0x041A
#define TTM_GETMARGIN                                0x041B
#define TTM_POP                                      0x041C
#define TTM_ADDTOOL                                  0x0432
#define TTM_DELTOOL                                  0x0433
#define TTM_NEWTOOLRECT                              0x0434
#define TTM_GETTOOLINFO                              0x0435
#define TTM_SETTOOLINFO                              0x0436
#define TTM_HITTEST                                  0x0437
#define TTM_GETTEXT                                  0x0438
#define TTM_UPDATETIPTEXT                            0x0439
#define TTM_ENUMTOOLS                                0x043A
#define TTM_GETCURRENTTOOL                           0x043B

/* ---- TTN_ family (4 names; R1) ---- */
#define TTN_GETDISPINFO                              (-530)
#define TTN_NEEDTEXT                                 (-530)
#define TTN_POP                                      (-522)
#define TTN_SHOW                                     (-521)

/* ---- TTS_ family (1 names; R1) ---- */
#define TTS_NOPREFIX                                 0x0002

/* ---- TVC_ family (3 names; R1) ---- */
#define TVC_UNKNOWN                                  0x0000
#define TVC_BYMOUSE                                  0x0001
#define TVC_BYKEYBOARD                               0x0002

/* ---- TVE_ family (5 names; R1) ---- */
#define TVE_COLLAPSE                                 0x0001
#define TVE_EXPAND                                   0x0002
#define TVE_TOGGLE                                   0x0003
#define TVE_EXPANDPARTIAL                            0x4000
#define TVE_COLLAPSERESET                            0x8000

/* ---- TVGN_ family (11 names; R1) ---- */
#define TVGN_ROOT                                    0x0000
#define TVGN_NEXT                                    0x0001
#define TVGN_PREVIOUS                                0x0002
#define TVGN_PARENT                                  0x0003
#define TVGN_CHILD                                   0x0004
#define TVGN_FIRSTVISIBLE                            0x0005
#define TVGN_NEXTVISIBLE                             0x0006
#define TVGN_PREVIOUSVISIBLE                         0x0007
#define TVGN_DROPHILITE                              0x0008
#define TVGN_CARET                                   0x0009
#define TVGN_LASTVISIBLE                             0x000A

/* ---- TVHT_ family (12 names; R1) ---- */
#define TVHT_NOWHERE                                 0x0001
#define TVHT_ONITEMICON                              0x0002
#define TVHT_ONITEMLABEL                             0x0004
#define TVHT_ONITEMINDENT                            0x0008
#define TVHT_ONITEMBUTTON                            0x0010
#define TVHT_ONITEMRIGHT                             0x0020
#define TVHT_ONITEMSTATEICON                         0x0040
#define TVHT_ONITEM                                  0x0046
#define TVHT_ABOVE                                   0x0100
#define TVHT_BELOW                                   0x0200
#define TVHT_TORIGHT                                 0x0400
#define TVHT_TOLEFT                                  0x0800

/* ---- TVIF_ family (7 names; R1) ---- */
#define TVIF_TEXT                                    0x0001
#define TVIF_IMAGE                                   0x0002
#define TVIF_PARAM                                   0x0004
#define TVIF_STATE                                   0x0008
#define TVIF_HANDLE                                  0x0010
#define TVIF_SELECTEDIMAGE                           0x0020
#define TVIF_CHILDREN                                0x0040

/* ---- TVIS_ family (8 names; R1) ---- */
#define TVIS_SELECTED                                0x0002
#define TVIS_CUT                                     0x0004
#define TVIS_DROPHILITED                             0x0008
#define TVIS_BOLD                                    0x0010
#define TVIS_EXPANDED                                0x0020
#define TVIS_EXPANDEDONCE                            0x0040
#define TVIS_OVERLAYMASK                             0x0F00
#define TVIS_STATEIMAGEMASK                          0xF000

/* ---- TVM_ family (23 names; R1) ---- */
#define TVM_DELETEITEM                               0x1101
#define TVM_EXPAND                                   0x1102
#define TVM_GETITEMRECT                              0x1104
#define TVM_GETCOUNT                                 0x1105
#define TVM_GETINDENT                                0x1106
#define TVM_SETINDENT                                0x1107
#define TVM_GETIMAGELIST                             0x1108
#define TVM_SETIMAGELIST                             0x1109
#define TVM_GETNEXTITEM                              0x110A
#define TVM_SELECTITEM                               0x110B
#define TVM_GETEDITCONTROL                           0x110F
#define TVM_GETVISIBLECOUNT                          0x1110
#define TVM_HITTEST                                  0x1111
#define TVM_CREATEDRAGIMAGE                          0x1112
#define TVM_SORTCHILDREN                             0x1113
#define TVM_ENSUREVISIBLE                            0x1114
#define TVM_SORTCHILDRENCB                           0x1115
#define TVM_ENDEDITLABELNOW                          0x1116
#define TVM_INSERTITEM                               0x1132
#define TVM_GETITEM                                  0x113E
#define TVM_SETITEM                                  0x113F
#define TVM_GETISEARCHSTRING                         0x1140
#define TVM_EDITLABEL                                0x1141

/* ---- TVN_ family (11 names; R1) ---- */
#define TVN_ENDLABELEDIT                             (-460)
#define TVN_BEGINLABELEDIT                           (-459)
#define TVN_DELETEITEM                               (-458)
#define TVN_BEGINDRAG                                (-456)
#define TVN_ITEMEXPANDED                             (-455)
#define TVN_ITEMEXPANDING                            (-454)
#define TVN_SETDISPINFO                              (-453)
#define TVN_GETDISPINFO                              (-452)
#define TVN_SELCHANGED                               (-451)
#define TVN_SELCHANGING                              (-450)
#define TVN_KEYDOWN                                  (-412)

/* ---- TVS_ family (1 names; R1) ---- */
#define TVS_HASBUTTONS                               0x0001

/* ---- TVSIL_ family (2 names; R1) ---- */
#define TVSIL_NORMAL                                 0x0000
#define TVSIL_STATE                                  0x0002

/* ---- UD_ family (2 names; R1) ---- */
#define UD_MINVAL                                    (-32767)
#define UD_MAXVAL                                    0x7FFF

/* ---- UDM_ family (12 names; R1) ---- */
#define UDM_SETRANGE                                 0x0465
#define UDM_GETRANGE                                 0x0466
#define UDM_SETPOS                                   0x0467
#define UDM_GETPOS                                   0x0468
#define UDM_SETBUDDY                                 0x0469
#define UDM_GETBUDDY                                 0x046A
#define UDM_SETACCEL                                 0x046B
#define UDM_GETACCEL                                 0x046C
#define UDM_SETBASE                                  0x046D
#define UDM_GETBASE                                  0x046E
#define UDM_SETRANGE32                               0x046F
#define UDM_GETRANGE32                               0x0470

/* ---- UDN_ family (1 names; R1) ---- */
#define UDN_DELTAPOS                                 (-722)

/* ---- VIEW_ family (8 names; R1) ---- */
#define VIEW_LARGEICONS                              0x0000
#define VIEW_SMALLICONS                              0x0001
#define VIEW_LIST                                    0x0002
#define VIEW_DETAILS                                 0x0003
#define VIEW_SORTNAME                                0x0004
#define VIEW_SORTSIZE                                0x0005
#define VIEW_SORTDATE                                0x0006
#define VIEW_SORTTYPE                                0x0007

/* ------------------------------------------------------------------
 * Book surface: cc-anim (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa452858 Animation Controls Macros */
/* aa452859 Animation Controls Messages */
/* aa452860 Animation Controls Notifications */
/* aa452861 Animation Controls Styles */
/* ------------------------------------------------------------------
 * Book surface: cc-capedit (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa452920 CAPEDIT Control (Header: Commctrl.h.) */
/* ------------------------------------------------------------------
 * Book surface: cc-capedit (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa452921 CapEdit Controls Messages */
/* ------------------------------------------------------------------
 * Book surface: cc-cdraw (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms907573 Custom Draw Messages */
/* ms907580 Custom Draw Structures */
/* ------------------------------------------------------------------
 * Book surface: cc-cmdbands-dep (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ee503418 REBARBANDINFO */
/* ------------------------------------------------------------------
 * Book surface: cc-cmdbands (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms907179 Command Bands Functions */
/* ms907189 Command Bands Macros */
/* ms907205 Command Bands Structures */
/* ------------------------------------------------------------------
 * Book surface: cc-cmdbars (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms907210 Command Bars Functions */
/* ms907216 Command Bars Macros */
/* ------------------------------------------------------------------
 * Book surface: cc-common (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms907234 Common Control Functions */
/* ms907242 Common Control Macros */
/* ms907247 Common Control Messages */
/* ms907254 Common Control Notifications */
/* ms907537 Common Control Structures */
/* ------------------------------------------------------------------
 * Book surface: cc-dateandtimepicker (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms907588 Date and Time Picker Controls Macros */
/* ms927538 Date and Time Picker Controls Messages */
/* ms927544 Date and Time Picker Controls Notifications */
/* ms927557 Date and Time Picker Controls Structures */
/* ------------------------------------------------------------------
 * Book surface: cc-header (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms927659 Header Controls Macros */
/* ms927663 Header Controls Messages */
/* ms927670 Header Controls Notifications */
/* ms927682 Header Controls Structures */
/* ------------------------------------------------------------------
 * Book surface: cc-listview (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms927751 List-View Controls Macros */
/* ms927755 List-View Controls Messages */
/* ms927760 List-View Controls Notifications */
/* ms927769 List-View Controls Structures */
/* ------------------------------------------------------------------
 * Book surface: cc-monthcalendar (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms927836 Month Calendar Controls Macros */
/* ms927842 Month Calendar Controls Messages */
/* ms927846 Month Calendar Controls Notifications */
/* ms927853 Month Calendar Controls Structures */
/* ------------------------------------------------------------------
 * Book surface: cc-progress (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms938700 Progress Bar Controls Messages */
/* ms938703 Progress Bar Controls Structures */
/* ------------------------------------------------------------------
 * Book surface: cc-rebar (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ------------------------------------------------------------------
 * Book surface: cc-rebar (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms938711 Rebar Controls Messages */
/* aa452727 Rebar Controls Notifications */
/* aa452729 Rebar Controls Structures */
/* ------------------------------------------------------------------
 * Book surface: cc-sbedit (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms939903 SBEDIT Control (Header: Commctrl.h.) */
/* ------------------------------------------------------------------
 * Book surface: cc-status (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa452763 Status Bars Functions */
/* aa452764 Status Bars Messages */
/* aa452765 Status Bars Notifications */
/* ------------------------------------------------------------------
 * Book surface: cc-tab (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa452778 Tab Controls Macros */
/* aa452779 Tab Controls Messages */
/* aa452780 Tab Controls Notifications */
/* aa452782 Tab Controls Structures */
/* ------------------------------------------------------------------
 * Book surface: cc-toolbar (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ------------------------------------------------------------------
 * Book surface: cc-toolbar (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa452784 Toolbar Controls Functions */
/* aa452785 Toolbar Controls Messages */
/* aa452786 Toolbar Controls Notifications */
/* aa452788 Toolbar Controls Structures */
/* ------------------------------------------------------------------
 * Book surface: cc-tooltips (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa452789 ToolTips Messages */
/* aa453758 ToolTips Notifications */
/* aa452791 ToolTips Structures */
/* ------------------------------------------------------------------
 * Book surface: cc-trackbar (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa452796 Trackbar Controls Messages */
/* ------------------------------------------------------------------
 * Book surface: cc-treeview (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa452798 Tree View Controls Macros */
/* aa452799 Tree View Controls Messages */
/* aa452800 Tree View Controls Notifications */
/* aa452802 Tree View Controls Structures */
/* ------------------------------------------------------------------
 * Book surface: cc-updown (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa452803 Up-Down Controls Functions */
/* aa452804 Up-Down Controls Messages */
/* aa452806 Up-Down Controls Structures */
/* ------------------------------------------------------------------
 * Book surface: shell-book (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa452920 CAPEDIT Control (Header: Commctrl.h.) */
/* ms939903 SBEDIT Control (Header: Commctrl.h.) */
/* ------------------------------------------------------------------
 * Book surface: shell-book (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms938413 About Animation Controls */
/* ms906513 Adding a Global New Button Menu Item */
/* ms906538 Adding a Temporary New Button Menu Item */
/* ms906521 Adding an Advanced Backlight Dialog Box */
/* ms906525 Adding an Advanced Print Dialog Box */
/* ms906532 Adding an Image List to a Tab Control */
/* ms906530 Adding and Editing Item Labels */
/* ms906546 Adding Callback Items and Callback Masks */
/* ms906548 Adding Columns */
/* ms925985 Adding Header Control Items */
/* ms925989 Adding Items and Subitems */
/* aa453945 Adding Resources to a Control Panel Application */
/* ms926077 Adding Text to the Status Bar */
/* ms926078 Adding Tool Text */
/* ms926084 Adding Tool Types */
/* ms926086 Animation Controls */
/* aa452858 Animation Controls Macros */
/* aa452859 Animation Controls Messages */
/* aa452860 Animation Controls Notifications */
/* ms927251 Animation Controls Reference */
/* aa452861 Animation Controls Styles */
/* ms926093 Arranging, Sorting, and Finding List Views */
/* ms926099 Atom Tables */
/* aa452863 ATTRIB */
/* ms926103 AYGShell API Extensions */
/* ms927269 AYGShell Controls */
/* ms927272 AYGShell Enumerations */
/* ms927275 AYGShell Functions */
/* ms907077 AYGShell Interfaces */
/* ms907080 AYGShell Macros */
/* ms907085 AYGShell Messages */
/* ms907090 AYGShell Reference */
/* ms907095 AYGShell Structures */
/* aa453946 Building a Control Panel Application */
/* aa452918 CALL */
/* aa452921 CapEdit Controls Messages */
/* aa452922 CapEdit Controls Reference */
/* ms926120 Changing Fonts and Colors */
/* aa453947 Changing the Skin Code for the Progress Bar */
/* ms908110 CHDIR, CD */
/* aa452828 Cloning the Commctrl Module */
/* ms928588 CLS */
/* ms907179 Command Bands Functions */
/* ms907189 Command Bands Macros */
/* ms907195 Command Bands Reference */
/* ms907205 Command Bands Structures */
/* ms907210 Command Bars Functions */
/* ms907216 Command Bars Macros */
/* ms907221 Command Bars Reference */
/* aa453924 Command Processor */
/* ms907227 Command Processor Commands */
/* ms926133 Command Processor OS Design Development */
/* ms926137 Command Processor Registry Settings */
/* aa453925 Command Processor Shell */
/* ms907234 Common Control Functions */
/* ms907242 Common Control Macros */
/* ms907247 Common Control Messages */
/* ms907254 Common Control Notifications */
/* ms907532 Common Control Reference */
/* ms926140 Common Control Registry Settings */
/* ms907537 Common Control Structures */
/* ms926144 Common Controls */
/* ms908145 Common Controls Reference */
/* ms926146 Common Dialog Boxes (Shell) */
/* ms907541 Common Dialog Boxes Functions */
/* ms907548 Common Dialog Boxes Messages */
/* ms907551 Common Dialog Boxes Reference */
/* ms907558 Common Dialog Boxes Structures */
/* ms908148 Console Registry Settings */
/* ms926152 Control Panel */
/* ms926154 Control Panel Applications */
/* ms907564 Controls Messages */
/* ms907569 Controls Reference */
/* ms908150 COPY (Command Processor) */
/* ms926168 Creating a Command Bands Control */
/* ms926170 Creating a Command Bar */
/* ms914264 Creating a Control Panel Application */
/* ms926176 Creating a Date and Time Picker Control */
/* ms926179 Creating a Header Control */
/* ms914378 Creating a Hello World Application */
/* ms926185 Creating a List View Control */
/* ms926188 Creating a Month Calendar Control */
/* ms926191 Creating a Multiple-Part Status Bar */
/* ms926208 Creating a Progress Bar */
/* ms926211 Creating a Property Sheet */
/* ms926213 Creating a Rebar Control */
/* ms926227 Creating a Status Bar */
/* ms926233 Creating a Tab Control */
/* ms926235 Creating a Toolbar */
/* ms926239 Creating a ToolTip Control */
/* ms906553 Creating a Trackbar */
/* ms906558 Creating a Tree View */
/* ms906562 Creating a Tree-View Image List */
/* ms906564 Creating a Welcome Application */
/* ms914382 Creating an Application that Demonstrates the Progress Bar */
/* ms914387 Creating an Empty Display-Based OS */
/* ms926202 Creating an Image List */
/* ms926205 Creating an Up-Down Control */
/* ms906575 Creating Controls */
/* ms914399 Creating Excluded Projects to Host Shell Source Code in the IDE */
/* ms906585 Creating Image Lists */
/* ms906591 Creating Multiline ToolTips */
/* ms906597 Creating Tracking ToolTips */
/* ms906578 Creating, Finding, and Deleting Atoms */
/* ms907573 Custom Draw Messages */
/* ms907578 Custom Draw Reference */
/* ms907580 Custom Draw Structures */
/* ms906608 Customizing Folders with Desktop.ini */
/* ms906612 Customizing Output with Callback Fields */
/* ms908196 DATE */
/* ms907588 Date and Time Picker Controls Macros */
/* ms927538 Date and Time Picker Controls Messages */
/* ms927544 Date and Time Picker Controls Notifications */
/* ms927550 Date and Time Picker Controls Reference */
/* ms927557 Date and Time Picker Controls Structures */
/* aa452934 Desktop Registry Settings */
/* aa452945 Dialing Characters Registry Settings */
/* aa452946 Dialing Locations Registry Settings */
/* aa452954 DIR */
/* aa452628 Displaying and Handling Items in the New Button Menu */
/* aa452635 Displaying Information */
/* aa452994 ECHO (Command Processor) */
/* aa452638 Editing Labels */
/* aa452639 Enabling a Backlight */
/* aa452642 Enabling Shell Callback Functions */
/* aa452644 Enabling Slide Animation for the Taskbar */
/* aa453057 ERASE, DEL */
/* aa453059 EXIT */
/* aa452650 Extending Shortcut Menus for a File Class */
/* ms929202 General Shell Registry Settings */
/* aa453191 GOTO (Command Processor) */
/* aa452658 Handling Drag-and-Drop Messages */
/* aa452659 Handling Messages for Tab Controls */
/* aa452660 Handling Miscellaneous Messages */
/* aa452662 Handling Paint Cycles, Drawing Stages, and Messages */
/* aa452664 Handling Tree-View Messages */
/* ms927659 Header Controls Macros */
/* ms927663 Header Controls Messages */
/* ms927670 Header Controls Notifications */
/* ms927676 Header Controls Reference */
/* ms927682 Header Controls Structures */
/* ms929929 HELP */
/* aa452665 Hiding System Sound Events */
/* aa452830 How to Customize the Appearance of Common Controls */
/* aa452831 How to Customize the Shell */
/* aa452832 How to Implement a Control Panel Application */
/* ms929941 IF (Command Processor) */
/* aa452670 Including a Command Processor */
/* aa452671 Including the Standard Shell */
/* aa452672 Including the Taskman Shell */
/* aa452675 Installing a Custom Shell */
/* ms927751 List-View Controls Macros */
/* ms927755 List-View Controls Messages */
/* ms927760 List-View Controls Notifications */
/* ms927764 List-View Controls Reference */
/* ms927769 List-View Controls Structures */
/* ms931429 MKDIR, MD */
/* aa452681 Modifying Control Position and Acceleration */
/* aa452683 Modifying Tree-View Item Appearance */
/* ms927836 Month Calendar Controls Macros */
/* ms927842 Month Calendar Controls Messages */
/* ms927846 Month Calendar Controls Notifications */
/* ms927850 Month Calendar Controls Reference */
/* ms927853 Month Calendar Controls Structures */
/* ms931456 MOVE */
/* ms931463 net */
/* ms911917 PATH */
/* ms911918 PAUSE (Command Processor) */
/* aa452692 Pocket PC-style Menu Bars */
/* aa452693 Pocket PC-style New Button */
/* ms938700 Progress Bar Controls Messages */
/* ms938702 Progress Bar Controls Reference */
/* ms938703 Progress Bar Controls Structures */
/* aa453550 PROMPT */
/* ms938704 Property Sheets Functions */
/* ms938705 Property Sheets Macros */
/* ms938706 Property Sheets Messages */
/* ms938707 Property Sheets Notifications */
/* ms938708 Property Sheets Reference */
/* ms938709 Property Sheets Structures */
/* aa453605 PWD */
/* ms938711 Rebar Controls Messages */
/* aa452727 Rebar Controls Notifications */
/* aa452728 Rebar Controls Reference */
/* aa452729 Rebar Controls Structures */
/* aa452708 Relaying Mouse Messages to a ToolTip */
/* ms939769 REM (Command Processor) */
/* ms939790 RENAME, REN */
/* aa452710 Responding to the Prepaint Notification */
/* ms939859 RMDIR, RD */
/* aa452714 Sample Custom Draw Function */
/* aa452733 SbEdit Controls Reference */
/* aa452716 Selecting Shell Components */
/* ms939984 SET (Command Processor) */
/* aa452720 Setting Regional Preferences */
/* aa452721 Setting Tab Size and Position */
/* aa452722 Setting the Position and Scroll Position of a List View Item */
/* aa452723 Setting the Range and Current Position */
/* aa452724 Setting the Size and Position of the Header Control */
/* aa452725 Setting the Time */
/* ms914408 Setting up Platform Builder to Build Modified Code in a Public Directory */
/* ms914412 Setting Up the Source Files for a Custom Shell */
/* aa453937 Shell Application Development */
/* ms926615 Shell Components */
/* aa452739 Shell Migration */
/* aa453938 Shell OS Design Development */
/* aa452738 Shell OS Functions */
/* aa452740 Shell OS Reference */
/* aa452744 Shell OS Structures */
/* aa453939 Shell Overview */
/* aa452741 Shell Reference */
/* aa452742 Shell Registry Settings */
/* aa452743 Shell Samples */
/* ms926685 Shell Security */
/* aa453712 SHIFT */
/* ms933849 Simple Shell Modifications */
/* ms926840 Specifying Toolbar Size, Position, and Appearance */
/* aa452752 Standard Shell Enumerations */
/* aa452753 Standard Shell Functions */
/* aa452754 Standard Shell Interfaces */
/* aa452755 Standard Shell Macros */
/* aa452756 Standard Shell Messages */
/* aa452757 Standard Shell Reference */
/* aa452758 Standard Shell Structures */
/* ms940348 START */
/* aa452763 Status Bars Functions */
/* aa452764 Status Bars Messages */
/* aa452765 Status Bars Notifications */
/* aa452766 Status Bars Reference */
/* ms926882 Supporting Full-Screen Dialog Boxes */
/* ms926909 Supporting the Input Panel */
/* aa452778 Tab Controls Macros */
/* aa452779 Tab Controls Messages */
/* aa452780 Tab Controls Notifications */
/* aa452781 Tab Controls Reference */
/* aa452782 Tab Controls Structures */
/* ms933416 TIME */
/* aa453747 TITLE (Command Processor) */
/* aa452784 Toolbar Controls Functions */
/* aa452785 Toolbar Controls Messages */
/* aa452786 Toolbar Controls Notifications */
/* aa452787 Toolbar Controls Reference */
/* aa452788 Toolbar Controls Structures */
/* aa452789 ToolTips Messages */
/* aa453758 ToolTips Notifications */
/* aa452790 ToolTips Reference */
/* aa452791 ToolTips Structures */
/* aa452796 Trackbar Controls Messages */
/* aa452797 Trackbar Controls Reference */
/* aa452798 Tree View Controls Macros */
/* aa452799 Tree View Controls Messages */
/* aa452800 Tree View Controls Notifications */
/* aa452801 Tree View Controls Reference */
/* aa452802 Tree View Controls Structures */
/* ms914066 TYPE */
/* ms926983 Types of Atoms */
/* aa452803 Up-Down Controls Functions */
/* aa452804 Up-Down Controls Messages */
/* aa452805 Up-Down Controls Reference */
/* aa452806 Up-Down Controls Structures */
/* ms927020 Using Advanced List View Functionality */
/* ms906829 Using Animation Controls */
/* ms906849 Using Atoms */
/* ms906859 Using Images in Image Lists */
/* ms906897 Using Overlays in Image Lists */
/* ms927169 Using the Custom Draw Service */
/* ms927173 Using ToolTips */
/* ms914103 Windows CE Explorer Registry Settings */
/* ms927193 Working with Active and Inactive Pages in a Property Sheet */
/* ms927196 Working with Advanced Header Control Functionality */
/* ms927205 Working with Common Controls */
#endif /* AKARI_COMMCTRL_H */
