/*
 * commctrl.h -- Common Controls API for Windows CE (GWES; Image List
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
#include "windef.h"
#include "wingdi.h"   /* COLORREF, RECT via windef; HDC/HBITMAP/HICON */
#include "winuser.h"  /* NMHDR (ms931479), HMENU, WM_NOTIFY */

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

#ifdef __cplusplus
}
#endif

#endif /* AKARI_COMMCTRL_H */
