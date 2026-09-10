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

/* ------------------------------------------------------------------
 * Book surface: dshow-enum (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms925344 AM_SAMPLE_PROPERTY_FLAGS */
/* ms925346 AM_STREAM_INFO_FLAGS */
/* ms925348 AMVP_MODE */
/* ms925439 AnalogVideoStandard */
/* aa451714 FILTER_STATE */
/* ms932034 Merit */
/* ms932233 MPEG2Level */
/* ms932234 MPEG2Profile */
/* ms932255 PIN_DIRECTION */
/* ms932273 QualityMessageType */
/* aa452499 STREAMBUFFER_EC */
/* aa452378 StreamControlState */
/* aa452561 STRMBUF_CAPTURE_MODE */
/* aa452562 STRMBUF_PLAYBACK_TUNE_POLICY */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_DVDMEDIA_H */
