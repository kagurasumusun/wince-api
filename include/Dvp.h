/*
 * Dvp.h -- DirectDraw video port extensions for Windows CE (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE 5.0
 * "DirectDraw Reference" book pages whose Requirements rows name
 * Dvp.h (26 pages: the IDDVideoPortContainer and IDirectDrawVideoPort
 * interface records with Ddraw.lib link rows, and the six
 * DDVIDEOPORT* structures without Link Library rows).  Page ids are
 * cited per declaration; OS baseline "Windows CE 2.12 and later,
 * Version 2.12 requires DXPAK 1.0 or later".
 *
 * Interfaces are opaque exactly as their pages print them; method
 * signatures are recorded in the comments (the M58 pattern).  All
 * DDVP* constant families (DDVPCAPS_*, DDVPD_*, DDVPFX_*,
 * DDVPCONNECT_*, DDVPTYPE_* GUID names, DDVP_* info flags,
 * DDVPCREATE_*, DDVPFLIP_*, DDVPB_*, DDVPFORMAT_*, DDVPTARGET_*,
 * DDVPWAIT_*, DDVPSQ_*, DDVPSTATUS_*, DDVPBCAPS_*) are documented by
 * name only (no numeric values published) and are catalogued in
 * docs/inventory.md (M59).
 */

#ifndef AKARI_DVP_H
#define AKARI_DVP_H

#include "Ddraw.h"    /* DDPIXELFORMAT, LPDIRECTDRAWSURFACE, base types */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/*  Interfaces (opaque; no page prints a vtable layout)                */
/* ------------------------------------------------------------------ */

/* ms909107 "IDDVideoPortContainer" (Ddraw.lib). */
typedef struct IDDVideoPortContainer FAR *LPDDVIDEOPORTCONTAINER;

/* aa451780 "IDirectDrawVideoPort" (Ddraw.lib). */
typedef struct IDirectDrawVideoPort FAR *LPDIRECTDRAWVIDEOPORT;

/* ------------------------------------------------------------------ */
/*  Structures (verbatim CE 5.0 prints)                                */
/* ------------------------------------------------------------------ */

/* ms907801 "DDVIDEOPORTBANDWIDTH" */
typedef struct _DDVIDEOPORTBANDWIDTH {
    DWORD dwSize;
    DWORD dwCaps;
    DWORD dwOverlay;
    DWORD dwColorkey;
    DWORD dwYInterpolate;
    DWORD dwYInterpAndColorkey;
    DWORD dwReserved1;
    DWORD dwReserved2;
} DDVIDEOPORTBANDWIDTH, *LPDDVIDEOPORTBANDWIDTH;

/* ms907802 "DDVIDEOPORTCAPS" */
typedef struct _DDVIDEOPORTCAPS {
    DWORD dwSize;
    DWORD dwFlags;
    DWORD dwMaxWidth;
    DWORD dwMaxVBIWidth;
    DWORD dwMaxHeight;
    DWORD dwVideoPortID;
    DWORD dwCaps;
    DWORD dwFX;
    DWORD dwNumAutoFlipSurfaces;
    DWORD dwAlignVideoPortBoundary;
    DWORD dwAlignVideoPortPrescaleWidth;
    DWORD dwAlignVideoPortCropBoundary;
    DWORD dwAlignVideoPortCropWidth;
    DWORD dwPreshrinkXStep;
    DWORD dwPreshrinkYStep;
    DWORD dwNumVBIAutoFlipSurfaces;
    DWORD dwNumPreferredAutoflip;
    WORD wNumFilterTapsX;
    WORD wNumFilterTapsY;
} DDVIDEOPORTCAPS, *LPDDVIDEOPORTCAPS;

/* ms907803 "DDVIDEOPORTCONNECT" (guidTypeID names the DDVPTYPE_*
 * connect types; those GUIDs are not published) */
typedef struct _DDVIDEOPORTCONNECT{
    DWORD dwSize;
    DWORD dwPortWidth;
    GUID guidTypeID;
    DWORD dwFlags;
    ULONG_PTR dwReserved1;
} DDVIDEOPORTCONNECT, *LPDDVIDEOPORTCONNECT;

/* ms907804 "DDVIDEOPORTDESC" */
typedef struct _DDVIDEOPORTDESC {
    DWORD dwSize;
    DWORD dwFieldWidth;
    DWORD dwVBIWidth;
    DWORD dwFieldHeight;
    DWORD dwMicrosecondsPerField;
    DWORD dwMaxPixelsPerSecond;
    DWORD dwVideoPortID;
    DWORD dwReserved1;
    DDVIDEOPORTCONNECT VideoPortType;
    ULONG_PTR dwReserved2;
    ULONG_PTR dwReserved3;
} DDVIDEOPORTDESC, *LPDDVIDEOPORTDESC;

/* ms907805 "DDVIDEOPORTINFO" */
typedef struct _DDVIDEOPORTINFO{
    DWORD dwSize;
    DWORD dwOriginX;
    DWORD dwOriginY;
    DWORD dwVPFlags;
    RECT rCrop;
    DWORD dwPrescaleWidth;
    DWORD dwPrescaleHeight;
    LPDDPIXELFORMAT lpddpfInputFormat;
    LPDDPIXELFORMAT lpddpfVBIInputFormat;
    LPDDPIXELFORMAT lpddpfVBIOutputFormat;
    DWORD dwVBIHeight;
    ULONG_PTR dwReserved1;
    ULONG_PTR dwReserved2;
} DDVIDEOPORTINFO, *LPDDVIDEOPORTINFO;

/* ms907806 "DDVIDEOPORTSTATUS" */
typedef struct _DDVIDEOPORTSTATUS {
    DWORD dwSize;
    BOOL bInUse;
    DWORD dwFlags;
    DWORD dwReserved1;
    DDVIDEOPORTCONNECT VideoPortType;
    ULONG_PTR dwReserved2;
    ULONG_PTR dwReserved3;
} DDVIDEOPORTSTATUS, *LPDDVIDEOPORTSTATUS;

/* ------------------------------------------------------------------ */
/*  Video-port callback (pointer typedef)                              */
/* ------------------------------------------------------------------ */

/* aa451694 "EnumVideoCallback" (the page's Requirements name
 * Ddraw.h, but its parameter type DDVIDEOPORTCAPS is a Dvp.h
 * structure per ms907802, so the pointer typedef lives here next to
 * its only consumer, IDDVideoPortContainer::EnumVideoPorts):
 * HRESULT WINAPI EnumVideoCallback(LPDDVIDEOPORTCAPS
 * lpDDVideoPortCaps, LPVOID lpContext); "Video-port related functions
 * cannot be called from inside the EnumVideoCallback function."
 * Composed from the printed prototype and the page's "You can use the
 * LPDDENUMVIDEOCALLBACK data type" remark. */
typedef HRESULT (WINAPI *LPDDENUMVIDEOCALLBACK)(
    LPDDVIDEOPORTCAPS lpDDVideoPortCaps, LPVOID lpContext);

/* ------------------------------------------------------------------ */
/*  Interface records (opaque; documented method signatures)           */
/* ------------------------------------------------------------------ */

/*
 * Both interfaces inherit the IUnknown methods AddRef / QueryInterface
 * / Release (stated on both interface pages).
 *
 * IDDVideoPortContainer (ms909107; 4 methods):
 *   ms909118  HRESULT CreateVideoPort(DWORD dwFlags,
 *              LPDDVIDEOPORTDESC lpDDVideoPortDesc,
 *              LPDIRECTDRAWVIDEOPORT FAR* lplpDDVideoPort,
 *              IUnknown FAR* pUnkOuter);
 *   ms909119  HRESULT EnumVideoPorts(DWORD dwFlags,
 *              LPDDVIDEOPORTCAPS lpDDVideoPortCaps, LPVOID lpContext,
 *              LPDDENUMVIDEOCALLBACK lpEnumVideoCallback);
 *   ms909120  HRESULT GetVideoPortConnectInfo(DWORD dwPortId,
 *              LPDWORD lpNumEntries,
 *              LPDDVIDEOPORTCONNECT lpConnectInfo);
 *   ms909121  HRESULT QueryVideoPortStatus(DWORD dwPortId,
 *              LPDDVIDEOPORTSTATUS lpVPStatus);
 *
 * IDirectDrawVideoPort (aa451780; 14 methods):
 *   aa451781  HRESULT Flip(LPDIRECTDRAWSURFACE lpDDSurface,
 *              DWORD dwFlags);
 *   aa451782  HRESULT GetBandwidthInfo(
 *              LPDDPIXELFORMAT lpddpfFormat, DWORD dwWidth,
 *              DWORD dwHeight, DWORD dwFlags,
 *              LPDDVIDEOPORTBANDWIDTH lpBandwidth);
 *   aa451783  HRESULT GetColorControls(
 *              LPDDCOLORCONTROL lpColorControl);
 *   aa451784  HRESULT GetFieldPolarity(LPBOOL lpbFieldPolarity);
 *   aa451785  HRESULT GetInputFormats(LPDWORD lpNumFormats,
 *              LPDDPIXELFORMAT lpFormats, DWORD dwFlags);
 *   aa451786  HRESULT GetOutputFormats(
 *              LPDDPIXELFORMAT lpInputFormat, LPDWORD lpNumFormats,
 *              LPDDPIXELFORMAT lpFormats, DWORD dwFlags);
 *   aa451787  HRESULT GetVideoLine(LPDWORD lpdwLine);
 *   aa451788  HRESULT GetVideoSignalStatus(LPDWORD lpdwStatus);
 *   aa451789  HRESULT SetColorControls(
 *              LPDDCOLORCONTROL lpColorControl);
 *   aa451790  HRESULT SetTargetSurface(
 *              LPDIRECTDRAWSURFACE lpDDSurface, DWORD dwFlags);
 *   aa451791  HRESULT StartVideo(LPDDVIDEOPORTINFO lpVideoInfo);
 *   aa451792  HRESULT StopVideo();
 *   aa451793  HRESULT UpdateVideo(LPDDVIDEOPORTINFO lpVideoInfo);
 *   aa451794  HRESULT WaitForSync(DWORD dwFlags, DWORD dwLine,
 *              DWORD dwTimeout);
 */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_DVP_H */
