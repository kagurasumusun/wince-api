/*
 * Advbacklight.h -- Windows CE Advanced Backlight applet entry (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE .NET 4.0+
 * documentation (learn.microsoft.com previous-versions archive).  Source:
 * the one Advbacklight.h page of the Shell book harvest (M94,
 * tools/manifests/shell-book.manifest).
 *
 * The page prints no Link Library row: BacklightAdvApplet is the entry
 * the Backlight Control Panel application invokes (directly, when the
 * OEM registry adds the Advanced button) -- not a coredll export, so
 * there is no doc-derived def entry.
 */

#ifndef AKARI_ADVBACKLIGHT_H
#define AKARI_ADVBACKLIGHT_H

#include "Windef.h"    /* BOOL, HWND */

#ifdef __cplusplus
extern "C" {
#endif

/* aa452867 "BacklightAdvApplet": `BOOL BacklightAdvApplet(HWND hDlg);`
 * -- "displays the Advanced Backlight dialog box when the user
 * chooses Advanced in the Display Control Panel". */
AKARI_CE_IMPORT BOOL BacklightAdvApplet(HWND hDlg)
                    AKARI_CE_NAME(BacklightAdvApplet);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_ADVBACKLIGHT_H */
