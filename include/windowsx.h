/*
 * windowsx.h -- window helper macros for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  This header holds the Standard Shell Macros whose CE 5.0 pages
 * print Header: Windowsx.h.
 */

#ifndef AKARI_WINDOWSX_H
#define AKARI_WINDOWSX_H

#include "windef.h"
#include "windows.h"   /* HWND, LPRECT, MapWindowPoints, SetWindowLong */

#ifdef __cplusplus
extern "C" {
#endif

/* ms911791 "MapWindowRect" (Windows CE 1.0 and later; Windowsx.h).
 * "This macro calls the function MapWindowPoints": converts a rectangle
 * between window coordinate spaces.  The published facts -- the
 * MapWindowPoints carrier, the hwndFrom / hwndTo / lprc parameters and
 * the rect (two POINTs) geometry -- force the expansion below (a RECT
 * is a 2-point array to MapWindowPoints); the derivation is recorded
 * in docs/inventory.md M53. */
#define MapWindowRect(hwndFrom, hwndTo, lprc) \
    ((void) MapWindowPoints((hwndFrom), (hwndTo), (LPPOINT)(lprc), 2))

/* ms940022 "SetDlgMsgResult" (Windows CE 1.0 and later; Windowsx.h).
 * "This macro maps to the SetWindowLong function", with parameters
 * hwnd (dialog box), msg and result.  The CE page publishes no
 * expansion (its parameter text is copied from SetWindowLong and the
 * DWLP_MSGRESULT mechanism the desktop macro uses is not documented
 * for CE), so the macro name is recorded here and held as a gap in
 * docs/inventory.md M53 rather than defined speculatively:
 *
 *     SetDlgMsgResult(hwnd, msg, result)
 */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WINDOWSX_H */
