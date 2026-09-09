/*
 * Winnls.h -- National Language Support API for Windows CE (Akari API).
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

#include "Windef.h"
#include "Winbase.h"   /* SYSTEMTIME for the date/time formatters */

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
AKARI_CE_IMPORT int MultiByteToWideChar(UINT CodePage, DWORD dwFlags,
                        LPCSTR lpMultiByteStr, int cbMultiByte,
                        LPWSTR lpWideCharStr, int cchWideChar) AKARI_CE_NAME(MultiByteToWideChar);

/* aa450989 "WideCharToMultiByte (Windows CE 5.0)":
 * int WideCharToMultiByte(UINT, DWORD, LPCWSTR, int, LPSTR, int,
 * LPCSTR, LPBOOL).  CE 1.01+; Winnls.h; Coredll.lib.  Maps a wide
 * string to the given code page. */
AKARI_CE_IMPORT int WideCharToMultiByte(UINT CodePage, DWORD dwFlags,
                        LPCWSTR lpWideCharStr, int cchWideChar,
                        LPSTR lpMultiByteStr, int cbMultiByte,
                        LPCSTR lpDefaultChar,
                        LPBOOL lpUsedDefaultChar) AKARI_CE_NAME(WideCharToMultiByte);

/* ms886515 "IsDBCSLeadByte (Windows CE 5.0)":
 * BOOL IsDBCSLeadByte(BYTE).  CE 1.01+; Winnls.h; Coredll.lib. */
AKARI_CE_IMPORT BOOL IsDBCSLeadByte(BYTE TestChar) AKARI_CE_NAME(IsDBCSLeadByte);

/* ms886608 "IsDBCSLeadByteEx (Windows CE 5.0)":
 * BOOL IsDBCSLeadByteEx(UINT, BYTE).  CE 1.01+; Winnls.h;
 * Coredll.lib. */
AKARI_CE_IMPORT BOOL IsDBCSLeadByteEx(UINT CodePage, BYTE TestChar) AKARI_CE_NAME(IsDBCSLeadByteEx);

/* ------------------------------------------------------------------ */
/* M16: locale/code-page functions (official NLS Reference pages).    */
/* The NLS pages list Link Library Coreloc.lib except where noted.    */
/* ------------------------------------------------------------------ */

/* Character-type flag groups for GetStringTypeW/GetStringTypeEx
 * (ms905272/ms905283 name CT_CTYPE1/2/3; the values 1/2/4 are the
 * fixed Win32 ABI values). */
#define CT_CTYPE1 0x00000001u
#define CT_CTYPE2 0x00000002u
#define CT_CTYPE3 0x00000004u

/* Validity-test flags for IsValidLocale (ms906219). */
#define LCID_INSTALLED   0x00000001u
#define LCID_SUPPORTED   0x00000002u

/* String comparison results of CompareString (ms904713). */
#define CSTR_LESS_THAN    1
#define CSTR_EQUAL        2
#define CSTR_GREATER_THAN 3

/* CPINFO array sizes (names from the CPINFO page ms904717; values are
 * the fixed Win32 NLS-ABI sizes MAX_DEFAULTCHAR/MAX_LEADBYTES). */
#define MAX_DEFAULTCHAR 2
#define MAX_LEADBYTES   12

/* ms904717 "CPINFO (Windows CE 5.0)": code-page information filled by
 * GetCPInfo.  CE .NET 4.0+; Winnls.h. */
typedef struct _cpinfo {
    UINT MaxCharSize;              /* max length, in bytes, of a char */
    BYTE DefaultChar[MAX_DEFAULTCHAR]; /* default character */
    BYTE LeadByte[MAX_LEADBYTES];  /* lead-byte ranges, zero-terminated */
} CPINFO, *LPCPINFO;

/* ms905215 "GetACP (Windows CE 5.0)": UINT GetACP(VOID).  Returns the
 * current ANSI code-page identifier for the system.  CE .NET 4.0+;
 * Winnls.h; Coreloc.lib. */
AKARI_CE_IMPORT UINT GetACP(void) AKARI_CE_NAME(GetACP);

/* ms905256 "GetOEMCP (Windows CE 5.0)": UINT GetOEMCP(void).  Returns
 * the current OEM code-page identifier.  CE .NET 4.0+; Winnls.h;
 * Coreloc.lib. */
AKARI_CE_IMPORT UINT GetOEMCP(void) AKARI_CE_NAME(GetOEMCP);

/* ms905298 "GetSystemDefaultLCID (Windows CE 5.0)":
 * LCID GetSystemDefaultLCID(void).  CE .NET 4.0+; Winnls.h;
 * Coreloc.lib. */
AKARI_CE_IMPORT LCID GetSystemDefaultLCID(void) AKARI_CE_NAME(GetSystemDefaultLCID);

/* ms905323 "GetUserDefaultLCID (Windows CE 5.0)":
 * LCID GetUserDefaultLCID(void).  CE .NET 4.0+; Winnls.h; Coreloc.lib. */
AKARI_CE_IMPORT LCID GetUserDefaultLCID(void) AKARI_CE_NAME(GetUserDefaultLCID);

/* ms905289 "GetSystemDefaultLangID (Windows CE 5.0)":
 * LANGID GetSystemDefaultLangID(void).  CE .NET 4.0+; Winnls.h;
 * Coreloc.lib. */
AKARI_CE_IMPORT LANGID GetSystemDefaultLangID(void) AKARI_CE_NAME(GetSystemDefaultLangID);

/* ms905315 "GetUserDefaultLangID (Windows CE 5.0)":
 * LANGID GetUserDefaultLangID(void).  CE .NET 4.0+; Winnls.h;
 * Coreloc.lib. */
AKARI_CE_IMPORT LANGID GetUserDefaultLangID(void) AKARI_CE_NAME(GetUserDefaultLangID);

/* ms906218 "IsValidCodePage (Windows CE 5.0)":
 * BOOL IsValidCodePage(UINT).  CE .NET 4.0+; Winnls.h; Coreloc.lib. */
AKARI_CE_IMPORT BOOL IsValidCodePage(UINT CodePage) AKARI_CE_NAME(IsValidCodePage);

/* ms906219 "IsValidLocale (Windows CE 5.0)":
 * BOOL IsValidLocale(LCID, DWORD).  CE .NET 4.0+; Winnls.h;
 * Coreloc.lib.  dwFlags = LCID_INSTALLED and/or LCID_SUPPORTED; CE
 * cannot download code pages to a device (page note). */
AKARI_CE_IMPORT BOOL IsValidLocale(LCID Locale, DWORD dwFlags) AKARI_CE_NAME(IsValidLocale);

/* ms904713 "CompareString (Windows CE 5.0)":
 * int CompareString(LCID, DWORD, LPCTSTR, int, LPCTSTR, int).
 * CE 1.0+; Winnls.h; Coreloc.lib.  Compares two strings under the
 * locale; returns CSTR_LESS_THAN/EQUAL/GREATER_THAN (0 on failure).
 * cchCount -1 means null-terminated.  Fastest at dwCmpFlags 0 or
 * NORM_IGNORECASE with -1 counts (page note). */
AKARI_CE_IMPORT int CompareStringW(LCID Locale, DWORD dwCmpFlags,
                   LPCWSTR lpString1, int cchCount1,
                   LPCWSTR lpString2, int cchCount2) AKARI_CE_NAME(CompareStringW);
#define CompareString CompareStringW

/* ms904716 "ConvertDefaultLocale (Windows CE 5.0)":
 * LCID ConvertDefaultLocale(LCID).  CE .NET 4.0+; Winnls.h;
 * Coreloc.lib. */
AKARI_CE_IMPORT LCID ConvertDefaultLocale(LCID Locale) AKARI_CE_NAME(ConvertDefaultLocale);

/* ms905221 "GetCPInfo (Windows CE 5.0)":
 * BOOL GetCPInfo(UINT, LPCPINFO).  CE .NET 4.0+; Winnls.h;
 * Coreloc.lib.  Fills the code-page info structure. */
AKARI_CE_IMPORT BOOL GetCPInfo(UINT CodePage, LPCPINFO lpCPInfo) AKARI_CE_NAME(GetCPInfo);

/* ms905272 "GetStringTypeW (Windows CE 5.0)":
 * BOOL GetStringTypeW(DWORD, LPCWSTR, int, LPWORD).  CE 1.0+;
 * Winnls.h; **Coredll.lib** (page row).  Sets one or more CT_* bits
 * per source character in the output WORD array. */
AKARI_CE_IMPORT BOOL GetStringTypeW(DWORD dwInfoType, LPCWSTR lpSrcStr, int cchSrc,
                    LPWORD lpCharType) AKARI_CE_NAME(GetStringTypeW);

/* ms905283 "GetStringTypeEx (Windows CE 5.0)":
 * BOOL GetStringTypeEx(LCID, DWORD, LPCTSTR, int, LPWORD).  CE 1.0+;
 * Winnls.h; Coreloc.lib. */
AKARI_CE_IMPORT BOOL GetStringTypeExW(LCID Locale, DWORD dwInfoType,
                      LPCWSTR lpSrcStr, int cchSrc,
                      LPWORD lpCharType) AKARI_CE_NAME(GetStringTypeExW);
#define GetStringTypeEx GetStringTypeExW

/* ------------------------------------------------------------------ */
/* M32: NLS formatting / locale-info functions (Coreloc.lib; Winnls.h).*/
/*                                                                     */
/* All pages below print Header Winnls.h and Link Library Coreloc.lib, */
/* OS Versions Windows CE .NET 4.0 and later, except where noted.      */
/* The CURRENCYFMT / NUMBERFMT member lists are transcribed verbatim   */
/* from their structure pages (ms904720 / ms906228); the LPTSTR format */
/* fields are per the pages.  LCType takes the LCTYPE constants (the   */
/* ms906223 table); their values are not yet transcribed (recorded),   */
/* so GetLocaleInfoW/SetLocaleInfoW are declared and the LCTYPE table  */
/* is a recorded follow-on.  The DATE_ and TIME_ flag names are        */
/* documented by the GetDateFormat/GetTimeFormat pages; numeric values */
/* are not republished there (fixed-ABI follow-on, recorded).          */
/* republished there (fixed-ABI follow-on, recorded).  dwFlags=0 gives */
/* the default locale format for every function here.  CE is           */
/* Unicode-only: exports are the W spellings.                          */
/* ------------------------------------------------------------------ */

typedef DWORD LCTYPE;   /* LCTYPE constant space (UINT-sized) */

typedef struct _currencyfmt {
    UINT   NumDigits;
    UINT   LeadingZero;
    UINT   Grouping;
    LPTSTR lpDecimalSep;
    LPTSTR lpThousandSep;
    UINT   NegativeOrder;
    UINT   PositiveOrder;
    LPTSTR lpCurrencySymbol;
} CURRENCYFMT;

typedef struct _numberfmt {
    UINT   NumDigits;
    UINT   LeadingZero;
    UINT   Grouping;
    LPTSTR lpDecimalSep;
    LPTSTR lpThousandSep;
    UINT   NegativeOrder;
} NUMBERFMT;

AKARI_CE_IMPORT int GetCurrencyFormatW(LCID Locale, DWORD dwFlags, LPCWSTR lpValue,
                       const CURRENCYFMT *lpFormat,
                       LPWSTR lpCurrencyStr, int cchCurrency) AKARI_CE_NAME(GetCurrencyFormatW);
#define GetCurrencyFormat GetCurrencyFormatW
AKARI_CE_IMPORT int GetNumberFormatW(LCID Locale, DWORD dwFlags, LPCWSTR lpValue,
                     const NUMBERFMT *lpFormat,
                     LPWSTR lpNumberStr, int cchNumber) AKARI_CE_NAME(GetNumberFormatW);
#define GetNumberFormat GetNumberFormatW
AKARI_CE_IMPORT int GetDateFormatW(LCID Locale, DWORD dwFlags,
                   const SYSTEMTIME *lpDate, LPCWSTR lpFormat,
                   LPWSTR lpDateStr, int cchDate) AKARI_CE_NAME(GetDateFormatW);
#define GetDateFormat GetDateFormatW
AKARI_CE_IMPORT int GetTimeFormatW(LCID Locale, DWORD dwFlags,
                   const SYSTEMTIME *lpTime, LPCWSTR lpFormat,
                   LPWSTR lpTimeStr, int cchTime) AKARI_CE_NAME(GetTimeFormatW);
#define GetTimeFormat GetTimeFormatW
AKARI_CE_IMPORT int GetLocaleInfoW(LCID Locale, LCTYPE LCType,
                   LPWSTR lpLCData, int cchData) AKARI_CE_NAME(GetLocaleInfoW);
#define GetLocaleInfo GetLocaleInfoW
AKARI_CE_IMPORT BOOL SetLocaleInfoW(LCID Locale, LCTYPE LCType, LPCWSTR lpLCData) AKARI_CE_NAME(SetLocaleInfoW);
#define SetLocaleInfo SetLocaleInfoW

/* ------------------------------------------------------------------ */
/* String mapping (FoldString / LCMapString) and code-page enumeration */
/* (EnumSystemCodePages).  Page family: FoldString ms905209 (CE 1.0+), */
/* LCMapString ms906221 (CE .NET 4.0+), EnumSystemCodePages ms905062   */
/* (CE .NET 4.0+); Header rows all Winnls.h; Link Library rows all     */
/* Coreloc.lib.  CE 6.0 twins ee491930 / ee491201 / ee491962 confirm   */
/* the prototypes and the (v=winembedded.60) requirement rows.         */
/*                                                                     */
/* Windows CE is Unicode-only: the CE .NET/CE 5.0 LCMapString page     */
/* states "Even though Windows CE supports only the Unicode version    */
/* of this function...", so the exports are the wide spellings         */
/* (gen-doc-def.py UNICODE_ONLY).                                     */

/* CODEPAGE_ENUMPROC -- pointer to the application-defined callback
 * that EnumSystemCodePages calls for each code page.  The official
 * EnumCodePagesProc page (ms904723, CE .NET 4.0+; Winnls.h;
 * Coreloc.lib) documents "BOOL CALLBACK EnumCodePagesProc(LPTSTR
 * lpCodePageString)" and states "The CODEPAGE_ENUMPROC type defines a
 * pointer to this callback function."; the EnumSystemCodePages
 * parameter is typed CODEPAGE_ENUMPROC.  CE 6.0 twins ee491122 /
 * ee491962 restate both. */
typedef BOOL (CALLBACK *CODEPAGE_ENUMPROC)(LPWSTR lpCodePageString);

/* ms905209 "FoldString (Windows CE 5.0)": int FoldString(DWORD, LPCTSTR,
 * int, LPTSTR, int).  OS CE 1.0+; Winnls.h; Coreloc.lib.  dwMapFlags
 * combines the MAP_* mapping flags (names and CE support notes are on
 * the page; the CE page does not publish the flag values, so no
 * MAP_* constants are shipped -- recorded). */
AKARI_CE_IMPORT int FoldStringW(DWORD dwMapFlags, LPCWSTR lpSrcStr, int cchSrc,
                LPWSTR lpDestStr, int cchDest) AKARI_CE_NAME(FoldStringW);
#define FoldString FoldStringW

/* ms906221 "LCMapString (Windows CE 5.0)": int LCMapString(LCID, DWORD,
 * LPCTSTR, int, LPTSTR, int).  OS CE .NET 4.0+; Winnls.h; Coreloc.lib.
 * dwMapFlags combines the LCMAP_* and NORM_* flags (the page names
 * them per supported-flag groups; numeric values are not published by
 * the CE page -> no LCMAP_* or NORM_* constants shipped -- recorded). */
AKARI_CE_IMPORT int LCMapStringW(LCID Locale, DWORD dwMapFlags, LPCWSTR lpSrcStr,
                 int cchSrc, LPWSTR lpDestStr, int cchDest) AKARI_CE_NAME(LCMapStringW);
#define LCMapString LCMapStringW

/* ms905062 "EnumSystemCodePages (Windows CE 5.0)":
 * BOOL EnumSystemCodePages(CODEPAGE_ENUMPROC, DWORD).  OS CE .NET 4.0+;
 * Winnls.h; Coreloc.lib.  Enumerates the code pages installed on (or,
 * with CP_INSTALLED unset, supported by) the system; enumeration stops
 * when the callback returns FALSE. */
AKARI_CE_IMPORT BOOL EnumSystemCodePagesW(CODEPAGE_ENUMPROC lpCodePageEnumProc,
                          DWORD dwFlags) AKARI_CE_NAME(EnumSystemCodePagesW);
#define EnumSystemCodePages EnumSystemCodePagesW

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WINNLS_H */
