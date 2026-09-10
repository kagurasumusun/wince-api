/*
 * Imjpskin.h -- Japanese Pocket IME skin (customizable UI) classes.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE pages
 * of the International book (Japanese Pocket IME skin reference,
 * tools/manifests/intl-book.manifest): 73 leaves.  The skin API is a
 * C++ class library (implementation inheritance, nested classes and
 * static members) -- it has no C-callable surface, so per the M80
 * record-only policy the classes are recorded below as verbatim
 * method-signature records; the MARGINS helper structure is printed
 * in full and compiled.  Requirements rows print Header Imjpskin.h
 * and no Link Library.  See docs/inventory.md M84.
 */

#ifndef AKARI_IMJPSKIN_H
#define AKARI_IMJPSKIN_H

#include "Windef.h"    /* int, COLORREF via Windef */

#ifdef __cplusplus
extern "C" {
#endif

/* ms906227 "MARGINS": print `typedef struct _MARGINS {intcxLeftWidth;
 * intcxRightWidth;intcyTopHeight;intcyBottomHeight;} MARGINS,*
 * PMARGINS;` (glued tokens split). */
typedef struct _MARGINS {
    int cxLeftWidth;
    int cxRightWidth;
    int cyTopHeight;
    int cyBottomHeight;
} MARGINS, *PMARGINS;

/* ------------------------------------------------------------------ */
/* C++ class records (no C surface; pages print prototypes such as
 * `static COLORREF GetTextColor(void);`).  Class overviews:
 * CImeCUICandWindow, CImeCUIDefCompWindow, CImeCUIToolBar.
 * ------------------------------------------------------------------ */

/* CImeCUICandWindow (candidate window skin class, 41 leaves):
 *  CImeCUICandWindow::GetHorizontalOffset, GetMargins, GetMaxHeight,
 *    GetMaxItems, GetWndStyle, GetWndStyleEx, IsHoverActionSupported,
 *    PaintBackground, UseNumButtons.
 *  CImeCUICandWindow::CBottomInfoArea::GetMargins, GetTextColor,
 *    IsAvailable, PaintBackground, UseCandMenuButton,
 *    UseCandNumText, UseSortButton.
 *  CImeCUICandWindow::CBottomInfoArea::CButton::AdjustRect,
 *    PaintBackground, PaintIcon.
 *  CImeCUICandWindow::CCandListArea::GetMargins, PaintBackground.
 *  CImeCUICandWindow::CCandListArea::Item::CreateRenderingMetrics,
 *    FreeRenderingMetrics, GetSize, PaintBackground,
 *    PaintCandidateString, PaintInlineComment, SetSize.
 *  CImeCUICandWindow::CCandListArea::ScrollBar::IsVisibleAlways.
 *  CImeCUICandWindow::CNumButton::AdjustRect, PaintBackground,
 *    PaintIcon.
 *  CImeCUICandWindow::CReadingsArea::GetMargins, GetTextColor,
 *    IsAvailable, PaintBackground.
 *  CImeCUICandWindow::CReadingsArea::CButton::AdjustRect,
 *    PaintBackground, PaintBitmap, PaintText. */

/* CImeCUIDefCompWindow (default composition window skin class,
 * 13 leaves):
 *  CImeCUIDefCompWindow::GetMargins, GetTextColor, GetWndStyle,
 *    GetWndStyleEx, IsHoverActionSupported, PaintBackground,
 *    PaintGripper.
 *  CImeCUIDefCompWindow::CloseButton::AdjustRect, GetSize,
 *    PaintBackground, PaintBitmap.
 *  CImeCUIDefCompWindow::CompArea::GetMargins. */

/* CImeCUIToolBar (tool-bar skin class, 18 leaves):
 *  CImeCUIToolBar::GetMargins, GetWndStyle, GetWndStyleEx,
 *    IsHoverActionSupported, PaintBackground, PaintGripper.
 *  CImeCUIToolBar::Button::AdjustRect, GetSize, PaintBackground,
 *    PaintBitmap, PaintIcon.
 *  CImeCUIToolBar::ButtonArea::GetMargins, GetSeparator.
 *  CImeCUIToolBar::OnOffButton::AdjustRect, GetSize, PaintBackground,
 *    PaintBitmap. */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_IMJPSKIN_H */
