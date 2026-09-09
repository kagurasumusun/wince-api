/*
 * dvdmedia.h -- DVD/media property-set enums for the Akari API.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  The single DirectShow Enumerations page
 * whose Requirements row prints Header: dvdmedia.h (all other pages
 * of the book print Dshow.h or leave the row blank):
 *
 *   aa452528 "KS_AM_KSPROPSETID_TSRateChange" -- OS Versions:
 *   "Windows CE 5.0 with Windows CE 5.0 Networked Media Device
 *   Feature Pack"; Header: dvdmedia.h; no Link Library row (the
 *   book's "Setting Up the Build Environment" preamble).  The page
 *   title names the KSPROPSETID but the body prints the
 *   KS_AM_PROPERTY_TS_RATE_CHANGE enumeration (verbatim):
 *     typedef enum {
 *       KS_AM_RATE_SimpleRateChange = 1,
 *       KS_AM_RATE_ExactRateChange  = 2,
 *       KS_AM_RATE_MaxFullDataRate  = 3,
 *       KS_AM_RATE_Step             = 4
 *     } KS_AM_PROPERTY_TS_RATE_CHANGE;
 */

#ifndef AKARI_DVDMEDIA_H
#define AKARI_DVDMEDIA_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    KS_AM_RATE_SimpleRateChange = 1,
    KS_AM_RATE_ExactRateChange  = 2,
    KS_AM_RATE_MaxFullDataRate  = 3,
    KS_AM_RATE_Step             = 4
} KS_AM_PROPERTY_TS_RATE_CHANGE;

#ifdef __cplusplus
}
#endif

#endif /* AKARI_DVDMEDIA_H */
