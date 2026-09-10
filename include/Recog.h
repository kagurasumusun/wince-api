/*
 * Recog.h -- Japanese handwriting recognition (HWX) driver-side API.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE pages
 * of the International book (Handwriting Recognition reference,
 * tools/manifests/intl-book.manifest): the Hwx* function pages print
 * "Header: Recog.h" with Link Library rows "Hwxjpn.lib, ..." (trailing
 * comma as printed).  HRC (recognition-context handle) and ALC (ambient
 * link constraint enumeration) are not printed by any CE page, so the
 * functions taking them by value are recorded; HwxConfig prints a
 * plain void prototype and is declared.  HWXGUIDE and HWXRESULTS are
 * printed in full and compiled.
 * See docs/inventory.md M83.
 */

#ifndef AKARI_RECOG_H
#define AKARI_RECOG_H

#include "Windef.h"    /* BOOL, UINT, INT, USHORT, WCHAR, DWORD, POINT */

/* ms905440 "HWXGUIDE": print `typedef struct tagHWXGUIDE {UINT
 * cHorzBox;UINT cVertBox;INT xOrigin;INT yOrigin;UINT cxBox;UINT
 * cyBox;UINT cxOffset;UINT cyOffset;UINT cxWriting;UINT cyWriting;UINT
 * cyMid;UINT cyBase;UINTnDir;} HWXGUIDE, *PHWXGUIDE;` (glued tokens
 * split). */
typedef struct tagHWXGUIDE {
    UINT cHorzBox;
    UINT cVertBox;
    INT  xOrigin;
    INT  yOrigin;
    UINT cxBox;
    UINT cyBox;
    UINT cxOffset;
    UINT cyOffset;
    UINT cxWriting;
    UINT cyWriting;
    UINT cyMid;
    UINT cyBase;
    UINT nDir;
} HWXGUIDE, *PHWXGUIDE;

/* "HWXRESULTS": print `typedef struct tagHWXRESULTS {USHORT indxBox;
 * WCHAR rgChar[1]} HWXRESULTS, *PHWXRESULTS;` (missing semicolon in
 * the print repaired -- doc typo). */
typedef struct tagHWXRESULTS {
    USHORT indxBox;
    WCHAR  rgChar[1];
} HWXRESULTS, *PHWXRESULTS;

/* --- Declared (grounded print). ---------------------------------- */
/* "HwxConfig": print `BOOL HwxConfig(void);` (Hwxjpn.lib row). */
AKARI_CE_IMPORT BOOL HwxConfig(void)
                    AKARI_CE_NAME(HwxConfig);

/* --- Recorded (HRC / ALC unpublished). ---------------------------- */
/* "HwxCreate": `HRC HwxCreate( HRC hrc);` */
/* "HwxDestroy": `BOOL HwxDestroy( HRChrc);` */
/* "HwxEndInput": `BOOL HwxEndInput( HRChrc);` */
/* "HwxInput": `BOOL HwxInput( HRChrc,POINT* lppnt,UINT upoints,
 * DWORDtimestamp );` */
/* "HwxProcess": `BOOL HwxProcess( HRChrc);` */
/* "HwxResultsAvailable": `INT HwxResultsAvailable( HRC hrc);` */
/* "HwxSetAbort" (Hwxjpn.lib row): page prints no signature. */
/* "HwxSetContext": `BOOL HwxSetContext( HRChrc,WCHAR wContext );` */
/* "HwxSetGuide": `BOOL HwxSetGuide( HRChrc,HWXGUIDE* lpGuide );` */
/* "HwxSetPartial": `BOOL HwxSetPartial( HRChrc,UINT urecog );` */
/* "HwxALCPriority": `BOOL HwxALCPriority( HRChrc,ALC alc );` */
/* "HwxALCValid": `BOOL HwxALCValid( HRChrc,ALC alc );` */
/* "HwxGetResults": `INT32 HwxGetResults( HRChrc,UINT cAlt,UINT
 * iFirst,UINT cBoxRes,HWXRESULTS* rgBoxResults );`. */

#endif /* AKARI_RECOG_H */
