/*
 * btagnetwork.h -- Bluetooth Audio Gateway network-event entry point for
 * Windows CE (Btagnetwork.h layer).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  Source book: CE 5.0 "Audio Gateway" (aa450323, ms895682 of
 * tools/manifests/bt-os.manifest, fetched M57).  OS Versions: "Windows
 * CE 5.0 and later".
 *
 * aa450323 prints "Link Library: Btagsvc.lib" (the sole page of that
 * library in the harvest -- def/btagsvc-doc.def is exactly this one
 * export).
 *
 * Held family (names documented, values not published -- see
 * docs/inventory.md M57): the NETWORK_EVENT_* event ids of aa450323 are
 * names-only on the page.
 */

#ifndef AKARI_BTAGNETWORK_H
#define AKARI_BTAGNETWORK_H

#include "windef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* aa450323 "BthAGOnNetworkEvent": called by the Network Component of
 * the Audio Gateway service when an event occurs; the event ids
 * NETWORK_EVENT_CALL_IN / CALL_OUT / CALL_CONNECT / CALL_DISCONNECT /
 * CALL_REJECT / CALL_INFO / CALL_BUSY / RING / FAILED are names-only
 * (held). */
AKARI_CE_IMPORT void BthAGOnNetworkEvent(DWORD dwEvent,
                                         LPSTR pszParam) AKARI_CE_NAME(BthAGOnNetworkEvent);

/* ms895682 "NetworkCallFailedInfo". */
typedef struct _NetworkCallFailedInfo {
    USHORT usCallType;
    DWORD  dwStatus;
} NetworkCallFailedInfo;

#ifdef __cplusplus
}
#endif

#endif /* AKARI_BTAGNETWORK_H */
