/*
 * bt_ddi.h -- Bluetooth driver/device-interface definitions.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows Embedded
 * CE 6.0 pages (v=winembedded.60 archive) harvested into build/rows.json:
 * BASEBAND_CONNECTION_DATA aa450297, WODM_BT_SCO_AUDIO_CONTROL
 * ee495648, OID_PAN_AUTHENTICATE ee495- / OID_PAN_CONNECT ee495374 /
 * OID_PAN_DISCONNECT ee495819 / OID_PAN_ENCRYPT ee495824 (Requirements
 * rows print "Header bt_ddi.h"; Windows CE 5.0 and later).  The
 * lowercase file name is the dominant documented spelling (aygshell.h
 * precedent).  See docs/inventory.md M85.
 */

#ifndef AKARI_BT_DDI_H
#define AKARI_BT_DDI_H

#include "Windef.h"    /* USHORT, UINT, int */

#ifdef __cplusplus
extern "C" {
#endif

/* aa450297 "BASEBAND_CONNECTION_DATA" -- HELD (verbatim print
 * recorded; the `BD_ADDR baAddress` member names BD_ADDR, for which
 * no CE page exists -- the Bt_api.h print carries the BT_ADDR
 * spelling only):
 * `typedef struct _BASEBAND_CONNECTION_DATA{ USHORT hConnection;
 *  BD_ADDR baAddress; int cDataPacketsPending; UINT fLinkType : 1;
 *  UINT fEncrypted : 1; UINT fAuthenticated : 1; UINT fMode : 3;}
 *  BASEBAND_CONNECTION_DATA, *PBASEBAND_CONNECTION_DATA;` */

/* ee495648 "WODM_BT_SCO_AUDIO_CONTROL": message routed to the
 * Bluetooth audio chip through an MMDRV_MESSAGE_PARAMS structure
 * passed to WAV_IOControl.  The page prints no numeric value, so the
 * name is recorded only (WM_SIDESHOW_* M82 precedent). */

/* OID_PAN_* Bluetooth Personal Area Network object identifiers
 * (queryable/settable via the NDIS interface; the connect form takes
 * a service GUID plus the device BD_ADDR; the authenticate/encrypt
 * forms take BOOLEANs).  Pages print no numeric OID values, so the
 * names are recorded only:
 *   OID_PAN_AUTHENTICATE  OID_PAN_CONNECT
 *   OID_PAN_DISCONNECT    OID_PAN_ENCRYPT */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_BT_DDI_H */
