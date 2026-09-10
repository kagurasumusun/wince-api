/*
 * Bthid.h -- Bluetooth HID class-driver IOCTLs.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows Embedded
 * CE 6.0 pages (v=winembedded.60 archive) harvested into
 * build/rows.json: BTHHID_IOCTL_HIDConnect ee496033 and
 * BTHHID_IOCTL_HIDDisconnect ee496034 (Requirements rows print
 * "Header Bthid.h"; Windows CE 5.0 and later).  The connect IOCTL
 * takes the peer device address as a BT_ADDR (Bt_api.h) in the input
 * buffer.  The pages print no CTL_CODE values, so the names are
 * recorded only (WM_SIDESHOW_* M82 precedent).  See
 * docs/inventory.md M85.
 */

#ifndef AKARI_BTHID_H
#define AKARI_BTHID_H

#ifdef __cplusplus
extern "C" {
#endif

/* ee496033 "BTHHID_IOCTL_HIDConnect": connect the HID class driver
 * on the host to the peer Bluetooth HID device (input buffer =
 * BT_ADDR of the device).  Name recorded only. */

/* ee495827 "BTHHID_IOCTL_HIDDisconnect": disconnect the HID class
 * driver from the peer device.  Name recorded only. */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_BTHID_H */
