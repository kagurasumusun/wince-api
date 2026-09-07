/*
 * winnls.h -- National Language Support API for Windows CE (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (CE-era MSDN pages, learn.microsoft.com previous-versions archive,
 * (v=msdn.10) IDs); per-page Requirements rows (OS Versions / Header /
 * Link Library) are transcribed in docs/inventory.md.  Header Winnls.h
 * is the Header row the CE pages themselves name for these functions.
 */

#ifndef AKARI_WINNLS_H
#define AKARI_WINNLS_H

#include "windef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Code pages accepted by the conversion functions.  Names per the CE
 * MultiByteToWideChar / WideCharToMultiByte pages (ms886760,
 * aa450989), which mark CP_MACCP, CP_SYMBOL and CP_THREAD_ACP as "Not
 * supported" on Windows CE; values are the fixed Win32 ABI values. */
#define CP_ACP        0     /* ANSI code page */
#define CP_OEMCP      1     /* OEM code page */
#define CP_MACCP      2     /* not supported on Windows CE */
#define CP_THREAD_ACP 3     /* not supported on Windows CE */
#define CP_SYMBOL     42    /* not supported on Windows CE */
#define CP_UTF7       65000 /* UTF-7 code page */
#define CP_UTF8       65001 /* UTF-8 code page */

/* MultiByteToWideChar dwFlags (names per ms886760; values are the
 * fixed Win32 ABI values). */
#define MB_PRECOMPOSED        0x0001u
#define MB_COMPOSITE          0x0002u
#define MB_USEGLYPHCHARS      0x0004u
#define MB_ERR_INVALID_CHARS  0x0008u

/* WideCharToMultiByte dwFlags (names per aa450989; values are the
 * fixed Win32 ABI values; WC_NO_BEST_FIT_CHARS is not published by
 * the CE page so it is not defined here). */
#define WC_COMPOSITECHECK  0x0200u
#define WC_DISCARDNS       0x0010u
#define WC_SEPCHARS        0x0020u
#define WC_DEFAULTCHAR     0x0040u

/* ms886760 "MultiByteToWideChar (Windows CE 5.0)":
 * int MultiByteToWideChar(UINT, DWORD, LPCSTR, int, LPWSTR, int).
 * CE 1.01+; Winnls.h; Coredll.lib.  Maps a (not necessarily
 * multibyte) character string to a wide-character string. */
int MultiByteToWideChar(UINT CodePage, DWORD dwFlags,
                        LPCSTR lpMultiByteStr, int cbMultiByte,
                        LPWSTR lpWideCharStr, int cchWideChar);

/* aa450989 "WideCharToMultiByte (Windows CE 5.0)":
 * int WideCharToMultiByte(UINT, DWORD, LPCWSTR, int, LPSTR, int,
 * LPCSTR, LPBOOL).  CE 1.01+; Winnls.h; Coredll.lib.  Maps a wide
 * string to the given code page. */
int WideCharToMultiByte(UINT CodePage, DWORD dwFlags,
                        LPCWSTR lpWideCharStr, int cchWideChar,
                        LPSTR lpMultiByteStr, int cbMultiByte,
                        LPCSTR lpDefaultChar,
                        LPBOOL lpUsedDefaultChar);

/* ms886515 "IsDBCSLeadByte (Windows CE 5.0)":
 * BOOL IsDBCSLeadByte(BYTE).  CE 1.01+; Winnls.h; Coredll.lib. */
BOOL IsDBCSLeadByte(BYTE TestChar);

/* ms886608 "IsDBCSLeadByteEx (Windows CE 5.0)":
 * BOOL IsDBCSLeadByteEx(UINT, BYTE).  CE 1.01+; Winnls.h;
 * Coredll.lib. */
BOOL IsDBCSLeadByteEx(UINT CodePage, BYTE TestChar);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WINNLS_H */
