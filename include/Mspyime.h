/*
 * Mspyime.h -- MSPY IME (Simplified Chinese Pinyin) helper API.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE pages
 * of the International book (IME reference): GetPinyinType ms905263,
 * SetPinyinType ms906278, ClearEudpContent (Requirements rows print
 * Header: Mspyime.h, Link Library: Chsime03.lib).
 * See docs/inventory.md M83.
 */

#ifndef AKARI_MSPYIME_H
#define AKARI_MSPYIME_H

#include "Windef.h"    /* BOOL, DWORD, void */

/* ms905263 "GetPinyinType": print `BOOL GetPinyinType( DWORD*
 * pdwType);`. */
AKARI_CE_IMPORT BOOL GetPinyinType(DWORD *pdwType)
                    AKARI_CE_NAME(GetPinyinType);

/* ms906278 "SetPinyinType": print `BOOL SetPinyinType( DWORD
 * dwType);`. */
AKARI_CE_IMPORT BOOL SetPinyinType(DWORD dwType)
                    AKARI_CE_NAME(SetPinyinType);

/* "ClearEudpContent": print `void ClearEudpContent(void);`. */
AKARI_CE_IMPORT void ClearEudpContent(void)
                    AKARI_CE_NAME(ClearEudpContent);

#endif /* AKARI_MSPYIME_H */
