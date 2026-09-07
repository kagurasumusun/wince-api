/*
 * commctrl.h -- Image List API for Windows CE (GWES, Image Lists book).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  The Image List Functions / Macros / Structures books of the CE
 * 5.0 GWES documentation are the source books; function signatures were
 * recovered from the official CE 6.0 (v=winembedded.60) twins of the
 * same books, which publish whitespace-preserved prototypes (the CE 5.0
 * migration strips code spacing; the twin id is noted per declaration).
 *
 * Requirement rows: Header: Commctrl.h for every page; Link Library rows
 * read "Commctrl.lib, Imgctl.lib." for the functions, and are absent for
 * the macro/struct pages -- see def/commctrl-doc.def and def/imgctl-doc.def
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
 * ImageList_LoadBitmap macro) and the windef/wingdi handle types.
 * Include Windows.h (or winuser.h) first. */
#include "windef.h"
#include "wingdi.h"   /* COLORREF, RECT via windef; HDC/HBITMAP/HICON */

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

int      ImageList_Add(HIMAGELIST himl, HBITMAP hbmImage,     /* ms909786 */
                       HBITMAP hbmMask);
int      ImageList_AddMasked(HIMAGELIST himl, HBITMAP hbmImage,
                             COLORREF crMask);                 /* ms909795 */
BOOL     ImageList_BeginDrag(HIMAGELIST himlTrack, int iTrack,
                             int dxHotspot, int dyHotspot);    /* ms909799 */
BOOL     ImageList_Copy(HIMAGELIST himlDst, int iDst,
                        HIMAGELIST himlSrc, int iSrc,
                        UINT uFlags);                          /* ms909805 */
HIMAGELIST ImageList_Create(int cx, int cy, UINT flags,
                            int cInitial, int cGrow);          /* ms909810 */
BOOL     ImageList_Destroy(HIMAGELIST himl);                   /* ms909811 */
BOOL     ImageList_DragEnter(HWND hwndLock, int x, int y);     /* ms909812 */
BOOL     ImageList_DragLeave(HWND hwndLock);                   /* ms909813 */
BOOL     ImageList_DragMove(int x, int y);                     /* ms909814 */
BOOL     ImageList_DragShowNolock(BOOL fShow);                 /* ms909815 */
BOOL     ImageList_Draw(HIMAGELIST himl, int i, HDC hdcDst,    /* ms909816 */
                        int x, int y, UINT fStyle);
BOOL     ImageList_DrawEx(HIMAGELIST himl, int i, HDC hdcDst,  /* ms909817 */
                          int x, int y, int dx, int dy,
                          COLORREF rgbBk, COLORREF rgbFg,
                          UINT fStyle);
BOOL     ImageList_DrawIndirect(IMAGELISTDRAWPARAMS *pimldp);  /* ms909818 */
HIMAGELIST ImageList_Duplicate(HIMAGELIST himl);               /* ms909820 */
BOOL     ImageList_EndDrag(void);                              /* ms909821 */
COLORREF ImageList_GetBkColor(HIMAGELIST himl);                /* ms909823 */
HIMAGELIST ImageList_GetDragImage(POINT *ppt, POINT *pptHotspot); /* ms909824 */
HICON    ImageList_GetIcon(HIMAGELIST himl, int i, UINT flags); /* ms909825 */
BOOL     ImageList_GetIconSize(HIMAGELIST himl, int *cx,
                               int *cy);                       /* ms909826 */
int      ImageList_GetImageCount(HIMAGELIST himl);             /* ms909827 */
BOOL     ImageList_GetImageInfo(HIMAGELIST himl, int i,
                                IMAGEINFO *pImageInfo);        /* ms909828 */
HIMAGELIST ImageList_LoadImage(HINSTANCE hi, LPCSTR lpbmp,     /* ms909830 */
                               int cx, int cGrow, COLORREF crMask,
                               UINT uType, UINT uFlags);
HIMAGELIST ImageList_Merge(HIMAGELIST himl1, int i1,           /* ms909831 */
                           HIMAGELIST himl2, int i2, int dx, int dy);
BOOL     ImageList_Remove(HIMAGELIST himl, int i);             /* ms909832 */
BOOL     ImageList_RemoveAll(HIMAGELIST himl);                 /* ms909833 */
BOOL     ImageList_Replace(HIMAGELIST himl, int i,             /* ms909834 */
                           HBITMAP hbmImage, HBITMAP hbmMask);
int      ImageList_ReplaceIcon(HIMAGELIST himl, int i,         /* ms909835 */
                               HICON hicon);
COLORREF ImageList_SetBkColor(HIMAGELIST himl, COLORREF clrBk); /* ms909836 */
BOOL     ImageList_SetDragCursorImage(HIMAGELIST himlDrag,     /* ms909837 */
                                      int iDrag, int dxHotspot,
                                      int dyHotspot);
BOOL     ImageList_SetIconSize(HIMAGELIST himl, int cx, int cy); /* ms909838 */
BOOL     ImageList_SetImageCount(HIMAGELIST himl,              /* ms909839 */
                                 UINT uNewCount);
BOOL     ImageList_SetOverlayImage(HIMAGELIST himl, int iImage,
                                   int iOverlay);              /* ms909840 */

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

#ifdef __cplusplus
}
#endif

#endif /* AKARI_COMMCTRL_H */
