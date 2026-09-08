/*
 * keybd.h -- OEM keyboard event / shift-state flags for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).
 *
 * ms902150 "KEY_STATE_FLAGS" (Keyboard Driver DDI Data Types; Windows CE
 * 1.0 and later; Header Keybd.h): the keyboard event / SHIFT state word
 * used by PostKeybdMessage (winuser.h), GetAsyncShiftFlags
 * (pwinuser.h), the IIMCallback::SendCharEvents / IIMCallback2::
 * SendCharEvents methods (sip.h) and the keyboard driver DDI.  The page
 * publishes the complete type:
 *
 *     typedef UINT32 KEY_STATE_FLAGS;
 *
 * "The low-order bits keep track of a key state.  This enables you to
 * use 256 UINT8s for the key state array.  The upper bits keep track of
 * SHIFT state on a key-by-key basis."
 *
 * DERIVATION NOTE (held values).  The page's flag table prints the flag
 * NAMES only -- no numeric column.  The reserved-entry names carry
 * numeric suffixes (KeyStateReserved4 / 8 / 10 / 20 and KeyShiftReserved
 * 40000 / 400 / 200 / 100, KeyShiftLanguageFlag1), which read as
 * hexadecimal bit masks.  They pin the first six entries contiguously
 * (0x1, 0x2, 0x4, 0x8, 0x10, 0x20), but the tail anchors are mutually
 * inconsistent with any single contiguous assignment of the printed
 * table order (0x40000 / 0x400 / 0x200 / 0x100 collide with the
 * KeyShiftAnyCtrl/AnyShift/AnyAlt slots a contiguous reading assigns),
 * so no unique value assignment can be derived from the published
 * information.  Per the strict derivation policy (public information
 * only, derivation path recorded), the flag values are therefore HELD as
 * gaps in docs/inventory.md and the names are recorded below verbatim.
 * Cross-checks performed: the Windows Mobile 6.5 official documentation
 * (Microsoft Download Center CHM, "KEY_STATE_FLAGS" page -- preserved in
 * the corpus pageswm/ tree) prints the identical names-only table; the
 * desktop Win32 reference has no KEY_STATE_FLAGS (a different,
 * GetKeyState-based model).  The 33 documented flag names, in the page
 * table order:
 *
 *   Key state:  KeyStateToggledFlag, KeyStateGetAsyncDownFlag,
 *     KeyStateReserved4, KeyStateReserved8, KeyStateReserved10,
 *     KeyStateReserved20, KeyStatePrevDownFlag, KeyStateDownFlag,
 *     KeyStateKeyEventFlag
 *   Shift state:  KeyShiftAnyCtrlFlag, KeyShiftAnyShiftFlag,
 *     KeyShiftAnyAltFlag, KeyShiftCapitalFlag, KeyShiftLeftCtrlFlag,
 *     KeyShiftLeftShiftFlag, KeyShiftLeftAltFlag, KeyShiftLeftWinFlag,
 *     KeyShiftRightCtrlFlag, KeyShiftRightShiftFlag,
 *     KeyShiftRightAltFlag, KeyShiftRightWinFlag, KeyShiftReserved40000,
 *     KeyShiftDeadFlag, KeyShiftNoCharacterFlag, KeyShiftLanguageFlag1,
 *     KeyShiftKeybdEventFlag, KeyShiftUseVKNullFlag, KeyShiftNumLockFlag,
 *     KeyShiftScrollLockFlag, KeyShiftReserved400, KeyShiftReserved200,
 *     KeyShiftReserved100, KeyShiftKanaFlag
 */

#ifndef AKARI_KEYBD_H
#define AKARI_KEYBD_H

#include "windef.h"   /* UINT32 (KEY_STATE_FLAGS type) */

#ifdef __cplusplus
extern "C" {
#endif

/* ms902150 (Windows CE 1.0 and later; Keybd.h).  The PostKeybdMessage
 * KeyStateFlags parameter, the GetAsyncShiftFlags return value and the
 * SendCharEvents uKeyFlags / puShift parameters carry this type. */
typedef UINT32 KEY_STATE_FLAGS;

#ifdef __cplusplus
}
#endif

#endif /* AKARI_KEYBD_H */
