/*
 * Msimeui.h -- Chinese Pocket IME UI-module entry point.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE pages
 * of the International book: ImeGetUIClassName is documented twice --
 * Simplified Chinese ms905977 and Traditional Chinese ms905978 -- with
 * identical prints (Requirements rows: Header Msimeui.h, Link Library
 * Msimeuic.lib).  An OEM UI module for the Chinese Pocket IME must
 * expose this function.  See docs/inventory.md M84.
 */

#ifndef AKARI_MSIMEUI_H
#define AKARI_MSIMEUI_H

#include "Windef.h"    /* void */
#include "Winnt.h"     /* LPTSTR */

#ifdef __cplusplus
extern "C" {
#endif

/* ms905977 / ms905978 "ImeGetUIClassName": print
 * `voidImeGetUIClassName( LPTSTRlpszImeUIClassName);` (glued tokens
 * split; called by the Chinese Pocket IME to load the UI module). */
AKARI_CE_IMPORT void ImeGetUIClassName(LPTSTR lpszImeUIClassName)
                    AKARI_CE_NAME(ImeGetUIClassName);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_MSIMEUI_H */
