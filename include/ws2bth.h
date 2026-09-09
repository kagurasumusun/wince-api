/*
 * ws2bth.h -- Bluetooth Winsock structures for Windows CE (Ws2bth.h layer).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  Source book: CE 5.0 "Bluetooth Application Development ::
 * Structures" (the Ws2bth.h leaves of tools/manifests/bt-appdev.manifest,
 * fetched M57).  OS Versions: "Windows CE .NET 4.0 and later".
 *
 * These are structure pages with no Link Library row, so no def is
 * generated for this header.
 *
 * The address types (bt_addr / BT_ADDR) are printed by the Bt_api.h
 * page ms896282, so this header includes bt_api.h for them.
 *
 * Held (see docs/inventory.md M57): the GET_NAP / GET_SAP / SET_NAP_SAP
 * macros named by the SOCKADDR_BTH page (aa450944) are printed
 * comment-only on that page, with no macro bodies -- not defined.
 */

#ifndef AKARI_WS2BTH_H
#define AKARI_WS2BTH_H

#include "windef.h"
#include "bt_api.h"    /* bt_addr / BT_ADDR (ms896282) */

#ifdef __cplusplus
extern "C" {
#endif

/* aa450944 "SOCKADDR_BTH". */
typedef struct _SOCKADDR_BTH {
    USHORT   addressFamily;
    bt_addr  btAddr;
    GUID     serviceClassId;
    ULONG    port;
} SOCKADDR_BTH, *PSOCKADDR_BTH;

/* ms887862 "BthInquiryResult": tag __bth_inquiry_result as printed;
 * the forward declaration in bt_api.h (BthPerformInquiry ms887872)
 * is completed here. */
struct __bth_inquiry_result {
    BT_ADDR        ba;
    unsigned int   cod;
    unsigned short clock_offset;
    unsigned char  page_scan_mode;
    unsigned char  page_scan_period_mode;
    unsigned char  page_scan_repetition_mode;
};

/* ms887863 "BTH_LOCAL_VERSION": lmp_features[8] as printed. */
typedef struct _BTH_LOCAL_VERSION {
    unsigned char  hci_version;
    unsigned short hci_revision;
    unsigned char  lmp_version;
    unsigned short lmp_subversion;
    unsigned short manufacturer;
    unsigned char  lmp_features[8];
} BTH_LOCAL_VERSION, *PBTH_LOCAL_VERSION;

/* ms887884 "BTH_REMOTE_VERSION". */
typedef struct _BTH_REMOTE_VERSION {
    unsigned char  lmp_version;
    unsigned short lmp_subversion;
    unsigned short manufacturer;
    unsigned char  lmp_features[8];
} BTH_REMOTE_VERSION, *PBTH_REMOTE_VERSION;

/* ms887882 "BTH_REMOTE_NAME": szNameBuffer[248] as printed. */
typedef struct _BTH_REMOTE_NAME {
    BT_ADDR bt;
    WCHAR   szNameBuffer[248];
} BTH_REMOTE_NAME, *PBTH_REMOTE_NAME;

/* ms887893 "BTH_SOCKOPT_SECURITY": caData[16] as printed. */
typedef struct _BTH_SOCKOPT_SECURITY {
    int           iLength;
    bt_addr       btAddr;
    unsigned char caData[16];
} BTH_SOCKOPT_SECURITY, *PBTH_SOCKOPT_SECURITY;

/* ms887904 "BTH_HOLD_MODE". */
typedef struct _BTH_HOLD_MODE {
    unsigned short hold_mode_max;
    unsigned short hold_mode_min;
    unsigned short interval;
} BTH_HOLD_MODE, *PBTH_HOLD_MODE;

/* ms887905 "BTH_PARK_MODE". */
typedef struct _BTH_PARK_MODE {
    unsigned short beacon_max;
    unsigned short beacon_min;
    unsigned short interval;
} BTH_PARK_MODE, *PBTH_PARK_MODE;

/* ms887906 "BTH_SNIFF_MODE". */
typedef struct _BTH_SNIFF_MODE {
    unsigned short sniff_mode_max;
    unsigned short sniff_mode_min;
    unsigned short sniff_attempt;
    unsigned short sniff_timeout;
    unsigned short interval;
} BTH_SNIFF_MODE, *PBTH_SNIFF_MODE;

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WS2BTH_H */
