/*
 * shellsdk.h -- shell SDK dialog initialization for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  The AYGShell Reference book of the CE 5.0 Shell documentation is
 * the source book.
 *
 * Header home, per the official Requirements row: SHInitDialog
 * (aa453713) prints Header: shellsdk.h, Library: aygshell.lib,
 * OS Versions: Windows CE 3.0 and later (the CE 6.0 twin ee501722
 * repeats shellsdk.h).  The SHINITDLGINFO structure the function takes
 * is documented on page aa453714 with Header: aygshell.h, so this
 * header includes aygshell.h for the structure (documented design
 * decision; the two documented homes are preserved as printed).
 */

#ifndef AKARI_SHELLSDK_H
#define AKARI_SHELLSDK_H

#include "aygshell.h"    /* SHINITDLGINFO, PSHINITDLGINFO, SHIDIM_FLAGS */

#ifdef __cplusplus
extern "C" {
#endif

/* aa453713 "SHInitDialog" (Windows CE 3.0 and later; shellsdk.h;
 * aygshell.lib).  Resizes a dialog box to accommodate a software input
 * panel based on the parameters in the SHINITDLGINFO structure.
 * Returns TRUE if successful.  The SHIDIF_* dwFlags values the
 * structure takes are published as names without values (held set,
 * see aygshell.h). */
AKARI_CE_IMPORT BOOL SHInitDialog(PSHINITDLGINFO pshidi) AKARI_CE_NAME(SHInitDialog);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_SHELLSDK_H */
