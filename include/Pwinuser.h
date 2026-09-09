/*
 * Pwinuser.h -- OEM keyboard / foreground-target layer for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  The Keyboard Reference book of the CE 5.0 GWES documentation is
 * the source book; these leaves were deferred from the M26 window-manager
 * harvest because their Header rows name Pwinuser.h and they depend on
 * the OEM keybd types (KEY_STATE_FLAGS, keybd.h, M52).
 *
 * Requirement rows (per page):
 *   GetAsyncShiftFlags (aa453955): Pwinuser.h / Kbdui.lib, CE .NET 4.2+.
 *   GetForegroundInfo (ms929241): Pwinuser.h / "Linked during platform
 *     build", CE .NET 4.2+ -- only available to OEMs; no import library
 *     row, so no def entry (documented).
 *   GetForegroundKeyboardLayoutHandle (ms929242): Pwinuser.h / "Linked
 *     during build", CE .NET 4.2+ -- OEMs only, no def entry.
 *   GetForegroundKeyboardTarget (ms929243): Pwinuser.h / "Linked during
 *     build", CE .NET 4.2+ -- OEMs only, no def entry.
 *   KeybdGetDeviceInfo (aa453246): Pwinuser.h / Coredll.lib, CE 1.0+.
 *   GET_FOREGROUND_INFO (aa453186): Pwinuser.h, CE .NET 4.2+.
 *
 * The iIndex identifiers of KeybdGetDeviceInfo are published as names
 * only (KBDI_VKEY_TO_UNICODE_INFO_ID, KBDI_AUTOREPEAT_INFO_ID,
 * KBDI_AUTOREPEAT_SELECTIONS_INFO_ID, KBDI_KEYBOARD_STATUS_ID, and the
 * status bits KBDI_KEYBOARD_PRESENT / KBDI_KEYBOARD_ENABLED /
 * KBDI_KEYBOARD_ENTER_ESC / KBDI_KEYBOARD_ALPHA_NUM); no official source
 * publishes their values (checked CE 5.0 / WM 6.5), so they are held as
 * gaps in docs/inventory.md rather than defined here.
 */

#ifndef AKARI_PWINUSER_H
#define AKARI_PWINUSER_H

#include "Windows.h"   /* HWND, BOOL, DWORD, HKL */
#include "Keybd.h"     /* KEY_STATE_FLAGS (GetAsyncShiftFlags return) */

#ifdef __cplusplus
extern "C" {
#endif

/* aa453186 "GET_FOREGROUND_INFO" (Windows CE .NET 4.2 and later;
 * Pwinuser.h).  Information about the current foreground thread, filled
 * by GetForegroundInfo.  "This structure is only available to OEMs."
 * Tag as printed (tagGetForegroundInfo).  The IME members carry the
 * foreground thread's conversion / sentence / open state and composition
 * string length. */
typedef struct tagGetForegroundInfo {
    HWND  hwndActive;           /* current active window of the foreground thread */
    HWND  hwndFocus;            /* current focus window (can be NULL) */
    HWND  hwndMenu;             /* current menu window (can be NULL) */
    HWND  hwndKeyboardDest;     /* current destination window for keystrokes */
    DWORD fdwConversion;        /* IME conversion mode */
    DWORD fdwSentence;          /* IME sentence mode */
    BOOL  fOpen;                /* IME open state */
    DWORD dwCompStrLen;         /* IME composition string length */
    HKL   KeyboardLayoutHandle; /* current keyboard layout handle */
} GET_FOREGROUND_INFO;

/* ms929241 "GetForegroundInfo" (CE .NET 4.2+; Pwinuser.h; Linked during
 * platform build).  Retrieves the GET_FOREGROUND_INFO of the current
 * foreground thread; used by the more specialized functions below (and
 * ImmGetConversionStatusForeground).  OEMs only. */
AKARI_CE_IMPORT BOOL GetForegroundInfo(GET_FOREGROUND_INFO *pgfi) AKARI_CE_NAME(GetForegroundInfo);

/* ms929242 "GetForegroundKeyboardLayoutHandle" (CE .NET 4.2+;
 * Pwinuser.h; Linked during build).  Returns the keyboard layout handle
 * of the current foreground thread (low word = language identifier,
 * high word = device handle of the physical layout).  OEMs only. */
AKARI_CE_IMPORT HKL GetForegroundKeyboardLayoutHandle(void) AKARI_CE_NAME(GetForegroundKeyboardLayoutHandle);

/* ms929243 "GetForegroundKeyboardTarget" (CE .NET 4.2+; Pwinuser.h;
 * Linked during build).  Returns the window currently receiving keyboard
 * input (NULL on failure).  OEMs only. */
AKARI_CE_IMPORT HWND GetForegroundKeyboardTarget(void) AKARI_CE_NAME(GetForegroundKeyboardTarget);

/* aa453955 "GetAsyncShiftFlags" (CE .NET 4.2+; Pwinuser.h; Kbdui.lib ->
 * def/kbdui-doc.def).  Asynchronous state of a virtual key: low-order
 * bits carry the key state, high-order bits the SHIFT state (the
 * KEY_STATE_FLAGS layout, keybd.h).  An invalid virtual-key code returns
 * 0 and sets ERROR_INVALID_PARAMETER -- clear the last error before the
 * call to distinguish that from a genuine 0. */
AKARI_CE_IMPORT KEY_STATE_FLAGS GetAsyncShiftFlags(UINT VKey) AKARI_CE_NAME(GetAsyncShiftFlags);

/* aa453246 "KeybdGetDeviceInfo" (CE 1.0+; Pwinuser.h; Coredll.lib ->
 * def/coredll-doc.def).  Returns information about the keyboard and its
 * driver.  iIndex takes the KBDI_* identifiers (names held): for
 * KBDI_KEYBOARD_STATUS_ID the routine fills lpOutput with a DWORD
 * combining KBDI_KEYBOARD_PRESENT / KBDI_KEYBOARD_ENABLED /
 * KBDI_KEYBOARD_ENTER_ESC / KBDI_KEYBOARD_ALPHA_NUM; any other index is
 * passed to the driver's PFN_KEYBD_DRIVER_GET_INFO. */
AKARI_CE_IMPORT BOOL KeybdGetDeviceInfo(INT iIndex, LPVOID lpOutput) AKARI_CE_NAME(KeybdGetDeviceInfo);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_PWINUSER_H */
