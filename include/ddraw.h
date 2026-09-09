/*
 * ddraw.h -- DirectDraw for Windows CE (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE 5.0
 * "DirectDraw Reference" book (learn.microsoft.com previous-versions
 * archive, page ids cited per declaration).  Every declaration below
 * is grounded only in those official pages; the DirectDraw surface is
 * the CE 2.12-and-later SDK layer ("OS Versions: Windows CE 2.12 and
 * later. Version 2.12 requires DXPAK 1.0 or later.").
 *
 * Page-header mapping (Requirements rows of the 134-page book):
 *
 *   Ddraw.h  -- 90 pages (4 global functions Ddraw.lib, 7 callbacks
 *               "User-defined", 12 structures without a Link Library
 *               row, and the IDirectDraw4 / IDirectDrawSurface5 /
 *               IDirectDrawClipper / IDirectDrawPalette /
 *               IDirectDrawColorControl interface records)
 *   Dvp.h    -- 26 pages (see include/dvp.h: the video-port layer)
 *
 * Layout policy for this unit:
 *
 *   Structures -- the CE 5.0 pages print complete C definitions
 *   (member order, types, union grouping); they are transcribed
 *   verbatim (spacing of the archive print normalized).  The CE 6.0
 *   twins of DDBLTFX / DDCAPS / DDCOLORCONTROL / DDOVERLAYFX /
 *   DDPIXELFORMAT / DDSURFACEDESC print divergent, condensed member
 *   lists (ee491245 / ee490705 / ee490304 / ee491509 / ee491068 /
 *   ee490816); the CE 5.0 prints are implemented here and the twin
 *   divergences are recorded in docs/inventory.md (M59).
 *
 *   Interfaces -- the CE pages declare the DirectDraw interfaces the
 *   same way this header does: opaque structure pointers ("typedef
 *   struct IDirectDraw FAR *LPDIRECTDRAW", ms929639).  No page prints
 *   a vtable layout, so no interface is laid out; every documented
 *   method signature is recorded in the interface record comments
 *   below (the IDvdDrv* pattern used since M58).
 *
 *   Constants -- every DD* constant family of this book (DD_OK /
 *   DDERR_* return values and all flag families DDBLT_*, DDBLTFX_*,
 *   DDCAPS_*, DDCAPS2_*, DDCKEYCAPS_*, DDFXCAPS_*, DDFXALPHACAPS_*,
 *   DDPCAPS_*, DDSVCAPS_*, DDBD_*, DDCOLOR_*, DDOVER_*, DDOVERFX_*,
 *   DDOVERZ_*, DDPF_*, DDSCAPS_*, DDSCAPS2_*, DDSCAPS4_*, DDSD_*,
 *   DDSCL_*, DDLOCK_*, DDFLIP_*, DDSPD_*, DDGFS_*, DDGBS_*,
 *   DDCKEY_*, DDBLTFAST_*, DDABLT_*, DDENUM_*, DDENUMRET_*,
 *   DDEDM_*, DDENUMSURFACES_*, DDENUMOVERLAYZ_*, DDWAITVB_*,
 *   DDSDM_*, DDCREATE_*, DDPSETPAL_*, and the Dvp.h DDVP* families)
 *   is documented by NAME ONLY (flag tables and the DirectDraw Return
 *   Values page aa451337 list names and descriptions but no numeric
 *   values).  Per the zero-gap policy they are NOT defined here; the
 *   families are catalogued in docs/inventory.md (M59).
 */

#ifndef AKARI_DDRAW_H
#define AKARI_DDRAW_H

#include "windef.h"    /* DWORD, BOOL, LONG, WORD, FAR, LPSTR, LPVOID, HMONITOR, WINAPI */
#include "winnt.h"     /* GUID, ULONG_PTR (DDVIDEOPORTCONNECT &c. in dvp.h), HRESULT base LONG */
#include "objbase.h"   /* HRESULT, IUnknown, REFGUID (referenced by method records) */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The CE 5.0 structure prints carry the Microsoft SDK union-name
 * marker DUMMYUNIONNAMEN(n) (DDBLTFX ms907788, DDSURFACEDESC2
 * ms907800, DDOVERLAYFX ms907794).  Following the convention the
 * desktop ddraw.h documentation states for these structures -- "The
 * unions in this structure have been updated to work with compilers
 * that do not support nameless unions" (DDBLTFX, ddraw.h docs) -- the
 * marker is defined empty here, which reproduces the printed text and
 * yields anonymous (nameless) unions.
 */
#ifndef DUMMYUNIONNAMEN
#define DUMMYUNIONNAMEN(n)
#endif

/* ------------------------------------------------------------------ */
/*  Interfaces (opaque; no page prints a vtable layout)                */
/* ------------------------------------------------------------------ */

/* ms929639 "IDirectDraw4": the page prints the full opaque typedef
 * chain for the interface generations reachable from DirectDrawCreate
 * (ms907787/ms929677 print the same records for the other objects). */
typedef struct IDirectDraw FAR *LPDIRECTDRAW;
typedef struct IDirectDraw2 FAR *LPDIRECTDRAW2;
typedef struct IDirectDraw4 FAR *LPDIRECTDRAW4;

/* ms929663 "IDirectDrawClipper" (Initialize not supported in Windows CE). */
typedef struct IDirectDrawClipper FAR *LPDIRECTDRAWCLIPPER;

/* ms929670 "IDirectDrawColorControl". */
typedef struct IDirectDrawColorControl FAR *LPDIRECTDRAWCOLORCONTROL;

/* ms929673 "IDirectDrawPalette" (Initialize not supported in Windows CE). */
typedef struct IDirectDrawPalette FAR *LPDIRECTDRAWPALETTE;

/* ms929677 "IDirectDrawSurface5": opaque typedef chain for the
 * surface interface generations. */
typedef struct IDirectDrawSurface FAR *LPDIRECTDRAWSURFACE;
typedef struct IDirectDrawSurface2 FAR *LPDIRECTDRAWSURFACE2;
typedef struct IDirectDrawSurface3 FAR *LPDIRECTDRAWSURFACE3;
typedef struct IDirectDrawSurface4 FAR *LPDIRECTDRAWSURFACE4;
typedef struct IDirectDrawSurface5 FAR *LPDIRECTDRAWSURFACE5;

/* ------------------------------------------------------------------ */
/*  Structures (verbatim CE 5.0 prints)                                */
/* ------------------------------------------------------------------ */

/* ms907791 "DDCOLORKEY" */
typedef struct _DDCOLORKEY{
    DWORD dwColorSpaceLowValue;
    DWORD dwColorSpaceHighValue;
} DDCOLORKEY, FAR* LPDDCOLORKEY;

/* ms907796 "DDSCAPS" */
typedef struct _DDSCAPS{
    DWORD dwCaps;
} DDSCAPS, FAR* LPDDSCAPS;

/* ms907797 "DDSCAPS2" */
typedef struct _DDSCAPS2 {
    DWORD dwCaps;
    DWORD dwCaps2;
    DWORD dwCaps3;
    DWORD dwCaps4;
} DDSCAPS2, FAR* LPDDSCAPS2;

/* ms907798 "DDSCAPSEX" */
typedef struct _DDSCAPSEX {
    DWORD dwCaps2;
    DWORD dwCaps3;
    DWORD dwCaps4;
} DDSCAPSEX, FAR* LPDDSCAPSEX;

/* ms907795 "DDPIXELFORMAT" (OS: Windows CE .NET 4.0 and later) */
typedef struct _DDPIXELFORMAT {
    DWORD dwSize;
    DWORD dwFlags;
    DWORD dwFourCC;
    union {
        DWORD dwRGBBitCount;
        DWORD dwYUVBitCount;
        DWORD dwZBufferBitDepth;
        DWORD dwAlphaBitDepth;
        DWORD dwLuminanceBitCount;
        DWORD dwBumpBitCount;
        DWORD dwPrivateFormatBitCount;
    };
    union {
        DWORD dwRBitMask;
        DWORD dwYBitMask;
        DWORD dwStencilBitDepth;
        DWORD dwLuminanceBitMask;
        DWORD dwBumpDuBitMask;
        DWORD dwOperations;
    };
    union {
        DWORD dwGBitMask;
        DWORD dwUBitMask;
        DWORD dwZBitMask;
        DWORD dwBumpDvBitMask;
        struct {
            WORD wFlipMSTypes;
            WORD wBltMSTypes;
        } MultiSampleCaps;
    };
    union {
        DWORD dwBBitMask;
        DWORD dwVBitMask;
        DWORD dwStencilBitMask;
        DWORD dwBumpLuminanceBitMask;
    };
    union {
        DWORD dwRGBAlphaBitMask;
        DWORD dwYUVAlphaBitMask;
        DWORD dwLuminanceAlphaBitMask;
        DWORD dwRGBZBitMask;
        DWORD dwYUVZBitMask;
    };
} DDPIXELFORMAT, FAR* LPDDPIXELFORMAT;

/* ms907799 "DDSURFACEDESC" (anonymous unions exactly as printed) */
typedef struct _DDSURFACEDESC {
    DWORD dwSize;
    DWORD dwFlags;
    DWORD dwHeight;
    DWORD dwWidth;
    union {
        LONG lPitch;
        DWORD dwLinearSize;
    };
    DWORD dwBackBufferCount;
    union {
        DWORD dwMipMapCount;
        DWORD dwZBufferBitDepth;
        DWORD dwRefreshRate;
    };
    DWORD dwAlphaBitDepth;
    DWORD dwReserved;
    LPVOID lpSurface;
    DDCOLORKEY ddckCKDestOverlay;
    DDCOLORKEY ddckCKDestBlt;
    DDCOLORKEY ddckCKSrcOverlay;
    DDCOLORKEY ddckCKSrcBlt;
    DDPIXELFORMAT ddpfPixelFormat;
    DDSCAPS ddsCaps;
} DDSURFACEDESC, FAR *LPDDSURFACEDESC;

/* ms907800 "DDSURFACEDESC2" */
typedef struct _DDSURFACEDESC2 {
    DWORD dwSize;
    DWORD dwFlags;
    DWORD dwHeight;
    DWORD dwWidth;
    union {
        LONG lPitch;
        DWORD dwLinearSize;
    } DUMMYUNIONNAMEN(1);
    DWORD dwBackBufferCount;
    union {
        DWORD dwMipMapCount;
        DWORD dwRefreshRate;
    } DUMMYUNIONNAMEN(2);
    DWORD dwAlphaBitDepth;
    DWORD dwReserved;
    LPVOID lpSurface;
    DDCOLORKEY ddckCKDestOverlay;
    DDCOLORKEY ddckCKDestBlt;
    DDCOLORKEY ddckCKSrcOverlay;
    DDCOLORKEY ddckCKSrcBlt;
    DDPIXELFORMAT ddpfPixelFormat;
    DDSCAPS2 ddsCaps;
    DWORD dwTextureStage;
} DDSURFACEDESC2, FAR* LPDDSURFACEDESC2;

/* ms907788 "DDBLTFX" */
typedef struct _DDBLTFX{
    DWORD dwSize;
    DWORD dwDDFX;
    DWORD dwROP;
    DWORD dwDDROP;
    DWORD dwRotationAngle;
    DWORD dwZBufferOpCode;
    DWORD dwZBufferLow;
    DWORD dwZBufferHigh;
    DWORD dwZBufferBaseDest;
    DWORD dwZDestConstBitDepth;
    union {
        DWORD dwZDestConst;
        LPDIRECTDRAWSURFACE lpDDSZBufferDest;
    } DUMMYUNIONNAMEN(1);
    DWORD dwZSrcConstBitDepth;
    union {
        DWORD dwZSrcConst;
        LPDIRECTDRAWSURFACE lpDDSZBufferSrc;
    } DUMMYUNIONNAMEN(2);
    DWORD dwAlphaEdgeBlendBitDepth;
    DWORD dwAlphaEdgeBlend;
    DWORD dwReserved;
    DWORD dwAlphaDestConstBitDepth;
    union {
        DWORD dwAlphaDestConst;
        LPDIRECTDRAWSURFACE lpDDSAlphaDest;
    } DUMMYUNIONNAMEN(3);
    DWORD dwAlphaSrcConstBitDepth;
    union {
        DWORD dwAlphaSrcConst;
        LPDIRECTDRAWSURFACE lpDDSAlphaSrc;
    } DUMMYUNIONNAMEN(4);
    union {
        DWORD dwFillColor;
        DWORD dwFillDepth;
        DWORD dwFillPixel;
        LPDIRECTDRAWSURFACE lpDDSPattern;
    } DUMMYUNIONNAMEN(5);
    DDCOLORKEY ddckDestColorkey;
    DDCOLORKEY ddckSrcColorkey;
} DDBLTFX, FAR* LPDDBLTFX;

/* ms907794 "DDOVERLAYFX" (member names dck* as printed; the CE 6.0
 * twin ee491509 prints a divergent condensed layout) */
typedef struct _DDOVERLAYFX{
    DWORD dwSize;
    DWORD dwAlphaEdgeBlendBitDepth;
    DWORD dwAlphaEdgeBlend;
    DWORD dwReserved;
    DWORD dwAlphaDestConstBitDepth;
    union {
        DWORD dwAlphaDestConst;
        LPDIRECTDRAWSURFACE lpDDSAlphaDest;
    } DUMMYUNIONNAMEN(1);
    DWORD dwAlphaSrcConstBitDepth;
    union {
        DWORD dwAlphaSrcConst;
        LPDIRECTDRAWSURFACE lpDDSAlphaSrc;
    } DUMMYUNIONNAMEN(2);
    DDCOLORKEY dckDestColorkey;
    DDCOLORKEY dckSrcColorkey;
    DWORD dwDDFX;
    DWORD dwFlags;
} DDOVERLAYFX, FAR* LPDDOVERLAYFX;

/* ms907790 "DDCOLORCONTROL" */
typedef struct _DDCOLORCONTROL {
    DWORD dwSize;
    DWORD dwFlags;
    LONG lBrightness;
    LONG lContrast;
    LONG lHue;
    LONG lSaturation;
    LONG lSharpness;
    LONG lGamma;
    LONG lColorEnable;
    DWORD dwReserved1;
} DDCOLORCONTROL, FAR* LPDDCOLORCONTROL;

/*
 * DD_ROP_SPACE -- size of the dwRops arrays in DDCAPS.
 *
 * Derivation (absolutely public information only): the DDCAPS print
 * (ms907789, identical in the CE .NET 4.2 twin ms893881) uses
 * "DWORD dwRops[DD_ROP_SPACE]"; no CE page prints the constant's
 * value.  The DirectDraw driver documentation (DDCORECAPS, ddrawi.h)
 * states the array is "an array of DD_ROP_SPACE DWORDs that together
 * can hold flags to indicate the ROPs that the driver supports" and
 * defers to "the Microsoft Windows SDK documentation for information
 * about ROPs"; the Windows SDK Ternary Raster Operations reference
 * enumerates the ROP space by an 8-bit operation index (256 codes,
 * Boolean functions 00-FF).  One flag bit per ROP, 32 bits per DWORD:
 * DD_ROP_SPACE = 256 / 32 = 8.
 */
#define DD_ROP_SPACE 8

/* ms907789 "DDCAPS" (final DDSCAPS2 ddsCaps member as printed; the
 * CE 6.0 twin ee490705 prints a divergent condensed layout) */
typedef struct _DDCAPS {
    DWORD dwSize;
    DWORD dwCaps;
    DWORD dwCaps2;
    DWORD dwCKeyCaps;
    DWORD dwFXCaps;
    DWORD dwFXAlphaCaps;
    DWORD dwPalCaps;
    DWORD dwSVCaps;
    DWORD dwAlphaBltConstBitDepths;
    DWORD dwAlphaBltPixelBitDepths;
    DWORD dwAlphaBltSurfaceBitDepths;
    DWORD dwAlphaOverlayConstBitDepths;
    DWORD dwAlphaOverlayPixelBitDepths;
    DWORD dwAlphaOverlaySurfaceBitDepths;
    DWORD dwZBufferBitDepths;
    DWORD dwVidMemTotal;
    DWORD dwVidMemFree;
    DWORD dwMaxVisibleOverlays;
    DWORD dwCurrVisibleOverlays;
    DWORD dwNumFourCCCodes;
    DWORD dwAlignBoundarySrc;
    DWORD dwAlignSizeSrc;
    DWORD dwAlignBoundaryDest;
    DWORD dwAlignSizeDest;
    DWORD dwAlignStrideAlign;
    DWORD dwRops[DD_ROP_SPACE];
    DWORD dwReservedCaps;
    DWORD dwMinOverlayStretch;
    DWORD dwMaxOverlayStretch;
    DWORD dwMinLiveVideoStretch;
    DWORD dwMaxLiveVideoStretch;
    DWORD dwMinHwCodecStretch;
    DWORD dwMaxHwCodecStretch;
    DWORD dwReserved1;
    DWORD dwReserved2;
    DWORD dwReserved3;
    DWORD dwSVBCaps;
    DWORD dwSVBCKeyCaps;
    DWORD dwSVBFXCaps;
    DWORD dwSVBRops[DD_ROP_SPACE];
    DWORD dwVSBCaps;
    DWORD dwVSBCKeyCaps;
    DWORD dwVSBFXCaps;
    DWORD dwVSBRops[DD_ROP_SPACE];
    DWORD dwSSBCaps;
    DWORD dwSSBCKeyCaps;
    DWORD dwSSBCFXCaps;
    DWORD dwSSBRops[DD_ROP_SPACE];
    DWORD dwMaxVideoPorts;
    DWORD dwCurrVideoPorts;
    DWORD dwSVBCaps2;
    DWORD dwNLVBCaps;
    DWORD dwNLVBCaps2;
    DWORD dwNLVBCKeyCaps;
    DWORD dwNLVBFXCaps;
    DWORD dwNLVBRops[DD_ROP_SPACE];
    DDSCAPS2 ddsCaps;
} DDCAPS, FAR *LPDDCAPS;

/*
 * ms907787 "DDALPHABLTFX" -- HELD (cannot be confirmed in official
 * docs).  The page prints
 *
 *   typedef union _DDALPHABLTFX {
 *       DDARGB ddargbScaleFactors;
 *       DWORD dwFillValue;
 *   } DDALPHABLTFX, FAR * LPDDALPHABLTFX;
 *
 * but the member type DDARGB is not laid out on any official page:
 * not in the CE 4.2 / CE 5.0 / CE 6.0 trees (ms893879 / ms907787 /
 * ee490481 all print the union without a DDARGB definition), and the
 * desktop ddraw.h documentation set on Microsoft Learn has no DDARGB
 * page (ddraw.h header index checked; Learn search API returns no
 * DDARGB result).  Only third-party SDK header copies publish a
 * layout, which is not an implementation basis.  IDirectDrawSurface5
 * ::AlphaBlt (ms929680) takes LPDDALPHABLTFX; its signature is
 * recorded in the method list below.
 */

/* ------------------------------------------------------------------ */
/*  Enumeration callbacks (pointer typedefs)                           */
/* ------------------------------------------------------------------ */

/* Each callback page prints the callback prototype and states "You
 * can use the LP... data type to declare a variable that can contain
 * a pointer to this callback function."  The pointer typedef below is
 * the composition of those two published facts (derivation recorded
 * per item).  All callbacks: Header Ddraw.h, Link Library
 * "User-defined", OS Windows CE 2.12 and later. */

/* ms907792 "DDEnumCallback": BOOL WINAPI DDEnumCallback(GUID FAR*
 * lpGUID, LPSTR lpDriverDescription, LPSTR lpDriverName, LPVOID
 * lpContext); "If UNICODE is defined, the string values will be
 * returned as type LPWSTR rather than LPSTR." */
typedef BOOL (WINAPI *LPDDENUMCALLBACK)(GUID FAR* lpGUID,
    LPSTR lpDriverDescription, LPSTR lpDriverName, LPVOID lpContext);

/* ms907793 "DDEnumCallbackEx": BOOL WINAPI DDEnumCallbackEx(GUID FAR*
 * lpGUID, LPSTR lpDriverDescription, LPSTR lpDriverName, LPVOID
 * lpContext, HMONITOR hm); hm is NULL for the primary device. */
typedef BOOL (WINAPI *LPDDENUMCALLBACKEX)(GUID FAR* lpGUID,
    LPSTR lpDriverDescription, LPSTR lpDriverName, LPVOID lpContext,
    HMONITOR hm);

/* aa451690 "EnumModesCallback": HRESULT WINAPI EnumModesCallback(
 * LPDDSURFACEDESC lpDDSurfaceDesc, LPVOID lpContext); returns
 * DDENUMRET_OK to continue / DDENUMRET_CANCEL to stop (values not
 * published). */
typedef HRESULT (WINAPI *LPDDENUMMODESCALLBACK)(
    LPDDSURFACEDESC lpDDSurfaceDesc, LPVOID lpContext);

/* aa451691 "EnumModesCallback2" (page prints the prototype name
 * "EnumModesCallback"; the title and IDirectDraw4::EnumDisplayModes
 * fix the callback name): HRESULT WINAPI EnumModesCallback2(
 * LPDDSURFACEDESC2 lpDDSurfaceDesc, LPVOID lpContext); */
typedef HRESULT (WINAPI *LPDDENUMMODESCALLBACK2)(
    LPDDSURFACEDESC2 lpDDSurfaceDesc, LPVOID lpContext);

/* aa451692 "EnumSurfacesCallback": HRESULT WINAPI
 * EnumSurfacesCallback(LPDIRECTDRAWSURFACE lpDDSurface,
 * LPDDSURFACEDESC lpDDSurfaceDesc, LPVOID lpContext); */
typedef HRESULT (WINAPI *LPDDENUMSURFACESCALLBACK)(
    LPDIRECTDRAWSURFACE lpDDSurface, LPDDSURFACEDESC lpDDSurfaceDesc,
    LPVOID lpContext);

/* aa451693 "EnumSurfacesCallback2": HRESULT WINAPI
 * EnumSurfacesCallback2(LPDIRECTDRAWSURFACE4 lpDDSurface,
 * LPDDSURFACEDESC2 lpDDSurfaceDesc, LPVOID lpContext); */
typedef HRESULT (WINAPI *LPDDENUMSURFACESCALLBACK2)(
    LPDIRECTDRAWSURFACE4 lpDDSurface, LPDDSURFACEDESC2 lpDDSurfaceDesc,
    LPVOID lpContext);

/* ------------------------------------------------------------------ */
/*  DirectDraw functions (Ddraw.lib)                                   */
/* ------------------------------------------------------------------ */

/* aa451583 "DirectDrawCreate": lpGUID selects the device (NULL for
 * the active display; DDCREATE_HARDWAREONLY / DDCREATE_SOFTWAREONLY
 * pseudo-GUID flags are named on the page, values not published);
 * pUnkOuter must be NULL. */
AKARI_CE_IMPORT HRESULT WINAPI DirectDrawCreate(GUID FAR* lpGUID,
    LPDIRECTDRAW FAR* lplpDD, IUnknown FAR* pUnkOuter)
    AKARI_CE_NAME(DirectDrawCreate);

/* aa451584 "DirectDrawCreateClipper": dwFlags must be 0; pUnkOuter
 * must be NULL. */
AKARI_CE_IMPORT HRESULT WINAPI DirectDrawCreateClipper(DWORD dwFlags,
    LPDIRECTDRAWCLIPPER FAR* lplpDDClipper, IUnknown FAR* pUnkOuter)
    AKARI_CE_NAME(DirectDrawCreateClipper);

/* aa451585 "DirectDrawEnumerate" */
AKARI_CE_IMPORT HRESULT WINAPI DirectDrawEnumerate(
    LPDDENUMCALLBACK lpCallback, LPVOID lpContext)
    AKARI_CE_NAME(DirectDrawEnumerate);

/* aa451586 "DirectDrawEnumerateEx": dwFlags is a combination of
 * DDENUM_ATTACHEDSECONDARYDEVICES / DDENUM_DETACHEDSECONDARYDEVICES /
 * DDENUM_NONDISPLAYDEVICES (names documented, values not published). */
AKARI_CE_IMPORT HRESULT WINAPI DirectDrawEnumerateEx(
    LPDDENUMCALLBACKEX lpCallback, LPVOID lpContext, DWORD dwFlags)
    AKARI_CE_NAME(DirectDrawEnumerateEx);

/* ------------------------------------------------------------------ */
/*  Interface records (opaque; documented method signatures)           */
/* ------------------------------------------------------------------ */

/*
 * Every record below lists the methods exactly as the CE 5.0 pages
 * document them.  The interfaces inherit the IUnknown methods
 * AddRef / QueryInterface / Release (stated on every interface page).
 * Missing-space artifacts of the archive print are normalized and
 * noted; page ids are per method.
 *
 * IDirectDraw4 (ms929639; 23 methods; GetDeviceIdentifier and
 * Initialize are not supported in Windows CE):
 *   ms929640  HRESULT Compact();                          [not currently implemented]
 *   ms929641  HRESULT CreateClipper(DWORD dwFlags,
 *              LPDIRECTDRAWCLIPPER FAR* lplpDDClipper,
 *              IUnknown FAR* pUnkOuter);
 *   ms929642  HRESULT CreatePalette(DWORD dwFlags,
 *              LPPALETTEENTRY lpDDColorArray,
 *              LPDIRECTDRAWPALETTE FAR* lplpDDPalette,
 *              IUnknown FAR* pUnkOuter);
 *   ms929643  HRESULT CreateSurface(LPDDSURFACEDESC2 lpDDSurfaceDesc2,
 *              LPDIRECTDRAWSURFACE4 FAR* lplpDDSurface,
 *              IUnknown FAR* pUnkOuter);
 *   ms929644  HRESULT DuplicateSurface(
 *              LPDIRECTDRAWSURFACE4 lpDDSurface,
 *              LPLPDIRECTDRAWSURFACE4 FAR* lplpDupDDSurface);
 *   ms929645  HRESULT EnumDisplayModes(DWORD dwFlags,
 *              LPDDSURFACEDESC2 lpDDSurfaceDesc2, LPVOID lpContext,
 *              LPDDENUMMODESCALLBACK2 lpEnumModesCallback);
 *   ms929646  HRESULT EnumSurfaces(DWORD dwFlags,
 *              LPDDSURFACEDESC2 lpDDSD2, LPVOID lpContext,
 *              LPDDENUMSURFACESCALLBACK2 pEnumSurfacesCallback);
 *   ms929647  HRESULT FlipToGDISurface();
 *   ms929648  HRESULT GetAvailableVidMem(LPDDSCAPS2 lpDDSCaps2,
 *              LPDWORD lpdwTotal, LPDWORD lpdwFree);
 *   ms929649  HRESULT GetCaps(LPDDCAPS lpDDDriverCaps,
 *              LPDDCAPS lpDDHELCaps);   [only one of the two may be NULL]
 *   ms929650  HRESULT GetDisplayMode(LPDDSURFACEDESC2 lpDDSurfaceDesc2);
 *   ms929651  HRESULT GetFourCCCodes(LPDWORD lpNumCodes,
 *              LPDWORD lpCodes);
 *   ms929652  HRESULT GetGDISurface(
 *              LPDIRECTDRAWSURFACE4 FAR* lplpGDIDDSSurface4);
 *   ms929653  HRESULT GetMonitorFrequency(LPDWORD lpdwFrequency);
 *   ms929654  HRESULT GetScanLine(LPDWORD lpdwScanLine);
 *   ms929655  HRESULT GetSurfaceFromDC(HDC hdc,
 *              LPDIRECTDRAWSURFACE4* lpDDS4);
 *   ms929656  HRESULT GetVerticalBlankStatus(LPBOOL lpbIsInVB);
 *   ms929657  HRESULT RestoreAllSurfaces();
 *   ms929658  HRESULT RestoreDisplayMode();
 *   ms929659  HRESULT SetCooperativeLevel(HWND hWnd, DWORD dwFlags);
 *   ms929660  HRESULT SetDisplayMode(DWORD dwWidth, DWORD dwHeight,
 *              DWORD dwBPP, DWORD dwRefreshRate, DWORD dwFlags);
 *   ms929661  HRESULT TestCooperativeLevel(void);
 *   ms929662  HRESULT WaitForVerticalBlank(DWORD dwFlags,
 *              HANDLE hEvent);
 *
 * IDirectDrawClipper (ms929663; 5 methods; Initialize not supported
 * in Windows CE):
 *   ms929664  HRESULT GetClipList(LPRECT lpRect,
 *              LPRGNDATA lpClipList, LPDWORD lpdwSize);   [RGNDATA as in wingdi.h]
 *   ms929665  HRESULT GetHWnd(HWND FAR* lphWnd);
 *   ms929667  HRESULT IsClipListChanged(BOOL FAR* lpbChanged);
 *   ms929668  HRESULT SetClipList(LPRGNDATA lpClipList,
 *              DWORD dwFlags);
 *   ms929669  HRESULT SetHWnd(DWORD dwFlags, HWND hWnd);
 *
 * IDirectDrawColorControl (ms929670; 2 methods):
 *   ms929671  HRESULT GetColorControls(
 *              LPDDCOLORCONTROL lpColorControl);
 *   ms929672  HRESULT SetColorControls(
 *              LPDDCOLORCONTROL lpColorControl);
 *
 * IDirectDrawPalette (ms929673; 3 methods; Initialize not supported
 * in Windows CE; PALETTEENTRY as in wingdi.h):
 *   ms929674  HRESULT GetCaps(LPDWORD lpdwCaps);
 *   ms929675  HRESULT GetEntries(DWORD dwFlags, DWORD dwBase,
 *              DWORD dwNumEntries, LPPALETTEENTRY lpEntries);
 *   ms929676  HRESULT SetEntries(DWORD dwFlags,
 *              DWORD dwStartingEntry, DWORD dwCount,
 *              LPPALETTEENTRY lpEntries);
 *
 * IDirectDrawSurface5 (ms929677; 42 methods):
 *   ms929678  HRESULT AddAttachedSurface(
 *              LPDIRECTDRAWSURFACE4 lpDDSAttachedSurface);
 *   ms929679  HRESULT AddOverlayDirtyRect(LPRECT lpRect);
 *                                                          [not currently implemented]
 *   ms929680  HRESULT AlphaBlt(LPRECT lpDestRect,
 *              LPDIRECTDRAWSURFACE4 lpDDSrcSurface, LPRECT lpSrcRect,
 *              DWORD dwFlags, LPDDALPHABLTFX lpDDAlphaBltFX);
 *   ms929681  HRESULT Blt(LPRECT lpDestRect,
 *              LPDIRECTDRAWSURFACE4 lpDDSrcSurface, LPRECT lpSrcRect,
 *              DWORD dwFlags, LPDDBLTFX lpDDBltFx);
 *   ms929682  HRESULT BltFast(DWORD dwX, DWORD dwY,
 *              LPDIRECTDRAWSURFACE4 lpDDSrcSurface, LPRECT lpSrcRect,
 *              DWORD dwTrans);
 *   ms929683  HRESULT ChangeUniquenessValue();
 *   ms929684  HRESULT DeleteAttachedSurface(DWORD dwFlags,
 *              LPDIRECTDRAWSURFACE4 lpDDSAttachedSurface);
 *   ms929685  HRESULT EnumAttachedSurfaces(LPVOID lpContext,
 *              LPDDENUMSURFACESCALLBACK2 lpEnumSurfacesCallback);
 *   ms929686  HRESULT EnumOverlayZOrders(DWORD dwFlags,
 *              LPVOID lpContext, LPDDENUMSURFACESCALLBACK2 lpfnCallback);
 *   ms929687  HRESULT Flip(LPDIRECTDRAWSURFACE5 lpDDSurfaceTargetOverride,
 *              DWORD dwFlags);
 *   ms929688  HRESULT FreePrivateData(REFGUID guidTag);
 *   ms929689  HRESULT GetAttachedSurface(LPDDSCAPS2 lpDDSCaps,
 *              LPDIRECTDRAWSURFACE4 FAR* lplpDDAttachedSurface);
 *   ms929690  HRESULT GetBltStatus(DWORD dwFlags);
 *   ms929691  HRESULT GetCaps(LPDDSCAPS2 lpDDSCaps);
 *   ms929692  HRESULT GetClipper(
 *              LPDIRECTDRAWCLIPPER FAR* lplpDDClipper);
 *   ms929693  HRESULT GetColorKey(DWORD dwFlags,
 *              LPDDCOLORKEY lpDDColorKey);
 *   ms929694  HRESULT GetDC(HDC FAR* lphDC);
 *   ms929695  HRESULT GetDDInterface(LPVOID FAR* lplpDD);
 *   ms929696  HRESULT GetFlipStatus(DWORD dwFlags);
 *   ms929697  HRESULT GetOverlayPosition(LPLONG lplX, LPLONG lplY);
 *   ms929698  HRESULT GetPalette(
 *              LPDIRECTDRAWPALETTE FAR* lplpDDPalette);
 *   ms929699  HRESULT GetPixelFormat(
 *              LPDDPIXELFORMAT lpDDPixelFormat);
 *   ms929700  HRESULT GetPrivateData(REFGUID guidTag,
 *              LPVOID lpBuffer, LPDWORD lpcbBufferSize);
 *   ms929701  HRESULT GetSurfaceDesc(
 *              LPDDSURFACEDESC2 lpDDSurfaceDesc);
 *   ms929702  HRESULT GetUniquenessValue(LPDWORD lpValue);
 *   ms929703  HRESULT Initialize(LPDIRECTDRAW lpDD,
 *              LPDDSURFACEDESC2 lpDDSurfaceDesc);   [returns DDERR_ALREADYINITIALIZED]
 *   ms929704  HRESULT IsLost();
 *   ms929705  HRESULT Lock(LPRECT lpDestRect,
 *              LPDDSURFACEDESC2 lpDDSurfaceDesc, DWORD dwFlags,
 *              HANDLE hEvent);   [hEvent not used, must be NULL;
 *                                  DDLOCK_NOSYSLOCK not supported in CE]
 *   ms929706  HRESULT PageLock(DWORD dwFlags);
 *   ms929707  HRESULT PageUnlock(DWORD dwFlags);
 *   ms929708  HRESULT ReleaseDC(HDC hDC);
 *   ms929709  HRESULT Restore();
 *   ms929710  HRESULT SetClipper(LPDIRECTDRAWCLIPPER lpDDClipper);
 *   ms929711  HRESULT SetColorKey(DWORD dwFlags,
 *              LPDDCOLORKEY lpDDColorKey);
 *   ms929712  HRESULT SetOverlayPosition(LONG lX, LONG lY);
 *   ms929713  HRESULT SetPalette(LPDIRECTDRAWPALETTE lpDDPalette);
 *   ms929714  HRESULT SetPrivateData(REFGUID guidTag,
 *              LPVOID lpData, DWORD cbSize, DWORD dwFlags);
 *   ms929715  HRESULT SetSurfaceDesc(LPDDSURFACEDESC2 lpddsd2,
 *              DWORD dwFlags);
 *   ms929716  HRESULT Unlock(LPRECT lpRect);
 *   ms929717  HRESULT UpdateOverlay(LPRECT lpSrcRect,
 *              LPDIRECTDRAWSURFACE4 lpDDDestSurface, LPRECT lpDestRect,
 *              DWORD dwFlags, LPDDOVERLAYFX lpDDOverlayFx);
 *   ms929718  UpdateOverlayDisplay -- "This method is not implemented
 *              in Windows CE"; no signature printed.
 *   aa451768  HRESULT UpdateOverlayZOrder(DWORD dwFlags,
 *              LPDIRECTDRAWSURFACE4 lpDDSReference);
 */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_DDRAW_H */
