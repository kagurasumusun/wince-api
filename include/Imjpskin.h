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

/* ------------------------------------------------------------------
 * Book surface: intl-book (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms904640 CImeCUICandWindow::CBottomInfoArea::CButton::AdjustRect (Header: Imjpskin.h.) */
/* ms904641 CImeCUICandWindow::CBottomInfoArea::CButton::PaintBackground (Header: Imjpskin.h.) */
/* ms904642 CImeCUICandWindow::CBottomInfoArea::CButton::PaintIcon (Header: Imjpskin.h.) */
/* ms904643 CImeCUICandWindow::CBottomInfoArea::GetMargins (Header: Imjpskin.h.) */
/* ms904644 CImeCUICandWindow::CBottomInfoArea::GetTextColor (Header: Imjpskin.h.) */
/* ms904645 CImeCUICandWindow::CBottomInfoArea::IsAvailable (Header: Imjpskin.h.) */
/* ms904646 CImeCUICandWindow::CBottomInfoArea::PaintBackground (Header: Imjpskin.h.) */
/* ms904647 CImeCUICandWindow::CBottomInfoArea::UseCandMenuButton (Header: Imjpskin.h.) */
/* ms904648 CImeCUICandWindow::CBottomInfoArea::UseCandNumText (Header: Imjpskin.h.) */
/* ms904649 CImeCUICandWindow::CBottomInfoArea::UseSortButton (Header: Imjpskin.h.) */
/* ms904650 CImeCUICandWindow::CCandListArea::GetMargins (Header: Imjpskin.h.) */
/* ms904651 CImeCUICandWindow::CCandListArea::Item::CreateRenderingMetrics (Header: Imjpskin.h.) */
/* ms904652 CImeCUICandWindow::CCandListArea::Item::FreeRenderingMetrics (Header: Imjpskin.h.) */
/* ms904653 CImeCUICandWindow::CCandListArea::Item::GetSize (Header: Imjpskin.h.) */
/* ms904654 CImeCUICandWindow::CCandListArea::Item::PaintBackground (Header: Imjpskin.h.) */
/* ms904655 CImeCUICandWindow::CCandListArea::Item::PaintCandidateString (Header: Imjpskin.h.) */
/* ms904656 CImeCUICandWindow::CCandListArea::Item::PaintInlineComment (Header: Imjpskin.h.) */
/* ms904657 CImeCUICandWindow::CCandListArea::Item::SetSize (Header: Imjpskin.h.) */
/* ms904658 CImeCUICandWindow::CCandListArea::PaintBackground (Header: Imjpskin.h.) */
/* ms904659 CImeCUICandWindow::CCandListArea::ScrollBar::IsVisibleAlways (Header: Imjpskin.h.) */
/* ms904660 CImeCUICandWindow::CNumButton::AdjustRect (Header: Imjpskin.h.) */
/* ms904661 CImeCUICandWindow::CNumButton::PaintBackground (Header: Imjpskin.h.) */
/* ms904662 CImeCUICandWindow::CNumButton::PaintIcon (Header: Imjpskin.h.) */
/* ms904663 CImeCUICandWindow::CReadingsArea::CButton::AdjustRect (Header: Imjpskin.h.) */
/* ms904664 CImeCUICandWindow::CReadingsArea::CButton::PaintBackground (Header: Imjpskin.h.) */
/* ms904665 CImeCUICandWindow::CReadingsArea::CButton::PaintBitmap (Header: Imjpskin.h.) */
/* ms904667 CImeCUICandWindow::CReadingsArea::CButton::PaintText (Header: Imjpskin.h.) */
/* ms904668 CImeCUICandWindow::CReadingsArea::GetMargins (Header: Imjpskin.h.) */
/* ms904669 CImeCUICandWindow::CReadingsArea::GetTextColor (Header: Imjpskin.h.) */
/* ms904670 CImeCUICandWindow::CReadingsArea::IsAvailable (Header: Imjpskin.h.) */
/* ms904671 CImeCUICandWindow::CReadingsArea::PaintBackground (Header: Imjpskin.h.) */
/* ms904672 CImeCUICandWindow::GetHorizontalOffset (Header: Imjpskin.h.) */
/* ms904673 CImeCUICandWindow::GetMargins (Header: Imjpskin.h.) */
/* ms904674 CImeCUICandWindow::GetMaxHeight (Header: Imjpskin.h.) */
/* ms904675 CImeCUICandWindow::GetMaxItems (Header: Imjpskin.h.) */
/* ms904676 CImeCUICandWindow::GetWndStyle (Header: Imjpskin.h.) */
/* ms904677 CImeCUICandWindow::GetWndStyleEx (Header: Imjpskin.h.) */
/* ms904678 CImeCUICandWindow::IsHoverActionSupported (Header: Imjpskin.h.) */
/* ms904679 CImeCUICandWindow::PaintBackground (Header: Imjpskin.h.) */
/* ms904680 CImeCUICandWindow::UseNumButtons (Header: Imjpskin.h.) */
/* ms904682 CImeCUIDefCompWindow::CloseButton::AdjustRect (Header: Imjpskin.h.) */
/* ms904683 CImeCUIDefCompWindow::CloseButton::GetSize (Header: Imjpskin.h.) */
/* ms904684 CImeCUIDefCompWindow::CloseButton::PaintBackground (Header: Imjpskin.h.) */
/* ms904685 CImeCUIDefCompWindow::CloseButton::PaintBitmap (Header: Imjpskin.h.) */
/* ms904686 CImeCUIDefCompWindow::CompArea::GetMargins (Header: Imjpskin.h.) */
/* ms904687 CImeCUIDefCompWindow::GetMargins (Header: Imjpskin.h.) */
/* ms904688 CImeCUIDefCompWindow::GetTextColor (Header: Imjpskin.h.) */
/* ms904689 CImeCUIDefCompWindow::GetWndStyle (Header: Imjpskin.h.) */
/* ms904690 CImeCUIDefCompWindow::GetWndStyleEx (Header: Imjpskin.h.) */
/* ms904691 CImeCUIDefCompWindow::IsHoverActionSupported (Header: Imjpskin.h.) */
/* ms904692 CImeCUIDefCompWindow::PaintBackground (Header: Imjpskin.h.) */
/* ms904693 CImeCUIDefCompWindow::PaintGripper (Header: Imjpskin.h.) */
/* ms904695 CImeCUIToolBar::Button::AdjustRect (Header: Imjpskin.h.) */
/* ms904698 CImeCUIToolBar::Button::GetSize (Header: Imjpskin.h.) */
/* ms904699 CImeCUIToolBar::Button::PaintBackground (Header: Imjpskin.h.) */
/* ms904700 CImeCUIToolBar::Button::PaintBitmap (Header: Imjpskin.h.) */
/* ms904701 CImeCUIToolBar::Button::PaintIcon (Header: Imjpskin.h.) */
/* ms904696 CImeCUIToolBar::ButtonArea::GetMargins (Header: Imjpskin.h.) */
/* ms904697 CImeCUIToolBar::ButtonArea::GetSeparator (Header: Imjpskin.h.) */
/* ms904702 CImeCUIToolBar::GetMargins (Header: Imjpskin.h.) */
/* ms904703 CImeCUIToolBar::GetWndStyle (Header: Imjpskin.h.) */
/* ms904704 CImeCUIToolBar::GetWndStyleEx (Header: Imjpskin.h.) */
/* ms904705 CImeCUIToolBar::IsHoverActionSupported (Header: Imjpskin.h.) */
/* ms904706 CImeCUIToolBar::OnOffButton::AdjustRect (Header: Imjpskin.h.) */
/* ms904707 CImeCUIToolBar::OnOffButton::GetSize (Header: Imjpskin.h.) */
/* ms904708 CImeCUIToolBar::OnOffButton::PaintBackground (Header: Imjpskin.h.) */
/* ms904709 CImeCUIToolBar::OnOffButton::PaintBitmap (Header: Imjpskin.h.) */
/* ms904710 CImeCUIToolBar::PaintBackground (Header: Imjpskin.h.) */
/* ms904711 CImeCUIToolBar::PaintGripper (Header: Imjpskin.h.) */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_IMJPSKIN_H */
