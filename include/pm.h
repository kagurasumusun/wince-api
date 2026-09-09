/*
 * pm.h -- device power states for Windows CE (Pm.h layer).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  The declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * page in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * ID).  Source book: CE 5.0 "CEDDK Dynamic-Link Library" dependency
 * (tools/manifests/ceddk-dep.manifest, fetched M57; CE 6.0 twin
 * ee497766 in build/pages6 cross-read).  OS Versions: "Windows CE .NET
 * 4.0 and later".
 *
 * The page prints no Link Library row, so no def is generated.
 */

#ifndef AKARI_PM_H
#define AKARI_PM_H

#include "windef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* aa447663 "CEDEVICE_POWER_STATE": values printed (implicit
 * successors: D1..D4 follow D0 = 0; PwrDeviceMaximum follows D4). */
typedef enum _CEDEVICE_POWER_STATE {
    PwrDeviceUnspecified = -1,
    D0 = 0,
    D1,
    D2,
    D3,
    D4,
    PwrDeviceMaximum
} CEDEVICE_POWER_STATE, *PCEDEVICE_POWER_STATE;

#ifdef __cplusplus
}
#endif

#endif /* AKARI_PM_H */
