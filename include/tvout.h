/*
 * tvout.h -- TV-out video parameters for Windows CE (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE
 * documentation page ms914096 "VIDEOPARAMETERS" (CE .NET 4.0+), whose
 * Requirement row lists "Header: Tvout.h" -- hence this component
 * header, included by include/windows.h.
 */

#ifndef AKARI_TVOUT_H
#define AKARI_TVOUT_H

#include "windef.h"
#include "winnt.h"   /* GUID */

#ifdef __cplusplus
extern "C" {
#endif

/* ms914096 "VIDEOPARAMETERS": TV-out/video parameter block used with
 * the ChangeDisplaySettingsEx TV-mode commands (the dwCommand field
 * selects the command; see the VIDEOPARAMETERS page).  The page types
 * the mode/TV-standard bit fields as ULONG and the OEM copy-protection
 * scratch buffer as UCHAR[256]. */
typedef struct _VIDEOPARAMETERS {
    GUID   Guid;
    ULONG  dwOffset;
    ULONG  dwCommand;
    ULONG  dwFlags;
    ULONG  dwMode;
    ULONG  dwTVStandard;
    ULONG  dwAvailableModes;
    ULONG  dwAvailableTVStandard;
    ULONG  dwFlickerFilter;
    ULONG  dwOverScanX;
    ULONG  dwOverScanY;
    ULONG  dwMaxUnscaledX;
    ULONG  dwMaxUnscaledY;
    ULONG  dwPositionX;
    ULONG  dwPositionY;
    ULONG  dwBrightness;
    ULONG  dwContrast;
    ULONG  dwCPType;
    ULONG  dwCPCommand;
    ULONG  dwCPStandard;
    ULONG  dwCPKey;
    ULONG  bCP_APSTriggerBits;
    UCHAR  bOEMCopyProtection[256];
} VIDEOPARAMETERS, *PVIDEOPARAMETERS, *LPVIDEOPARAMETERS;

#ifdef __cplusplus
}
#endif

#endif /* AKARI_TVOUT_H */
