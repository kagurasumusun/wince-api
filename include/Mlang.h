/*
 * Mlang.h -- Internet Explorer Multiple-Language API for Windows CE
 * (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE .NET 4.0+
 * documentation (learn.microsoft.com previous-versions archive; page
 * ids cited per declaration).  Source: the "Internet Explorer
 * Multiple-Language API Reference" book, 112 leaves
 * (tools/manifests/mlang.manifest): 11 interface records with 75
 * method pages, 6 functions, 6 structures, 6 enumerations, 5 object /
 * concept pages.  Every Requirements row prints "Header: Mlang.h,
 * Mlang.idl." and, for function/interface/method pages, "Link
 * Library: Mlang.dll." (module form -- the coredll.dll precedent:
 * the documented module token maps to the Mlang.lib import group,
 * def/mlang-doc.def, LIBRARY mlang.dll).  Several interfaces carry
 * the CE caveat "This interface is not supported on all Windows
 * CE-based operating systems.  See the SDK documentation specific to
 * your target device" (recorded per interface below).
 *
 * HELD (names documented, values/layouts not published anywhere
 * official): the MAX_MIMECP_NAME / MAX_MIMECSET_NAME / MAX_MIMEFACE_NAME
 * / MAX_RFC1766_NAME / MAX_LOCALE_NAME / MAX_SCRIPT_NAME array-length
 * constants (not printed by the CE pages; the desktop Mlang
 * documentation set has been removed from Microsoft Learn; Learn
 * search returns no result) and therefore the four array-carrying
 * structures MIMECPINFO (ms918820), MIMECSETINFO (ms918821),
 * RFC1766INFO (ms918852) and SCRIPTINFO (ms918857); SCRIPTFONTINFO
 * (referenced by aa452373, no page); the MultiLanguage object's
 * CLSID (ms918827, no GUID value printed).
 */

#ifndef AKARI_MLANG_H
#define AKARI_MLANG_H

#include "Windef.h"    /* DWORD, UINT, INT, BYTE, WCHAR, LANGID, LCID, LPINT, LPSTR, LPWSTR */
#include "Winnt.h"     /* WCHAR array bases */
#include "Objbase.h"   /* HRESULT, BSTR, IStream */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/*  Enumerations (printed C enums; values as published)                */
/* ------------------------------------------------------------------ */

/* ms918819 "MIMECONTF" (13 values printed). */
typedef enum tagMIMECONTF {
    MIMECONTF_MAILNEWS = 0x00000001,
    MIMECONTF_BROWSER = 0x00000002,
    MIMECONTF_MINIMAL = 0x00000004,
    MIMECONTF_IMPORT = 0x00000008,
    MIMECONTF_SAVABLE_MAILNEWS = 0x00000100,
    MIMECONTF_SAVABLE_BROWSER = 0x00000200,
    MIMECONTF_EXPORT = 0x00000400,
    MIMECONTF_PRIVCONVERTER = 0x00010000,
    MIMECONTF_VALID = 0x00020000,
    MIMECONTF_VALID_NLS = 0x00040000,
    MIMECONTF_MIME_IE4 = 0x10000000,
    MIMECONTF_MIME_LATEST = 0x20000000,
    MIMECONTF_MIME_REGISTRY = 0x40000000
} MIMECONTF;

/* ms918823 "MLCONVCHAR" (the page's tag is tagMLCONVCHARF; values
 * printed as decimal 0/1/2/4/8/16). */
typedef enum tagMLCONVCHARF {
    MLCONVCHARF_NONE = 0,
    MLCONVCHARF_AUTODETECT = 1,
    MLCONVCHARF_NCR_ENTITIZE = 2,
    MLCONVCHARF_NAME_ENTITIZE = 4,
    MLCONVCHARF_USEDEFCHAR = 8,
    MLCONVCHARF_NOBESTFITCHARS = 16
} MLCONVCHAR;

/* ms918824 "MLCP" (tag tagMLCPF, MLDETECTF_* names as printed). */
typedef enum tagMLCPF {
    MLDETECTF_MAILNEWS = 0x0001,
    MLDETECTF_BROWSER = 0x0002,
    MLDETECTF_VALID = 0x0004,
    MLDETECTF_VALID_NLS = 0x0008,
    MLDETECTF_PRESERVE_ORDER = 0x0010,
    MLDETECTF_PREFERRED_ONLY = 0x0020,
    MLDETECTF_FILTER_SPECIALCHAR = 0x0040
} MLCP;

/* ms918825 "MLDETECTCP". */
typedef enum tagMLDETECTCP {
    MLDETECTCP_NONE = 0,
    MLDETECTCP_7BIT = 1,
    MLDETECTCP_8BIT = 2,
    MLDETECTCP_DBCS = 4,
    MLDETECTCP_HTML = 8
} MLDETECTCP;

/* ms918854 "SCRIPTCONTF" (implicit values from 0; the two Far-East
 * range aliases printed with sidHangul / sidHan). */
typedef enum tagSCRIPTCONTF {
    sidDefault,
    sidMerge,
    sidAsciiSym,
    sidAsciiLatin,
    sidLatin,
    sidGreek,
    sidCyrillic,
    sidArmenian,
    sidHebrew,
    sidArabic,
    sidDevanagari,
    sidBengali,
    sidGurmukhi,
    sidGujarati,
    sidOriya,
    sidTamil,
    sidTelugu,
    sidKannada,
    sidMalayalam,
    sidThai,
    sidLao,
    sidTibetan,
    sidGeorgian,
    sidHangul,
    sidKana,
    sidBopomofo,
    sidHan,
    sidEthiopic,
    sidCanSyllabic,
    sidCherokee,
    sidYi,
    sidBraille,
    sidRunic,
    sidOgham,
    sidSinhala,
    sidSyriac,
    sidBurmese,
    sidKhmer,
    sidThaana,
    sidMongolian,
    sidLim,
    sidFEFirst = sidHangul,
    sidFELast = sidHan
} SCRIPTCONTF;

/* ms918856 "SCRIPTFONTCONTF". */
typedef enum tagSCRIPTFONTCONTF {
    SCRIPTCONTF_FIXED_FONT = 0x00000001,
    SCRIPTCONTF_PROPORTIONAL_FONT = 0x00000002,
    SCRIPTCONTF_SCRIPT_USER = 0x00010000,
    SCRIPTCONTF_SCRIPT_HIDE = 0x00020000,
    SCRIPTCONTF_SCRIPT_SYSTEM = 0x00040000
} SCRIPTFONTCONTF;

/*
 * SCRIPT_ID -- derivation (absolutely public information only): the
 * type name is printed by SCRIPTINFO's member list (ms918857) and by
 * the IMLangFontLink2 method signatures CodePageToScriptID
 * (aa452370) and GetScriptFontInfo (aa452373); the latter states a
 * SCRIPT_ID value "can be one of the SCRIPTCONTF values", and the
 * SCRIPTCONTF page (ms918854) is the published list of script
 * identifiers.  SCRIPT_ID is therefore the SCRIPTCONTF script
 * identifier type.
 */
typedef SCRIPTCONTF SCRIPT_ID;

/* ------------------------------------------------------------------ */
/*  Structures (verbatim CE prints)                                    */
/* ------------------------------------------------------------------ */

/* ms918861 "UNICODERANGE". */
typedef struct tagUNICODERANGE {
    WCHAR wcFrom;
    WCHAR wcTo;
} UNICODERANGE;

/* aa452152 "DetectEncodingInfo" (pointer typedef spelling
 * "pDetectEncodingInfo" exactly as printed). */
typedef struct tagDetectEncodingInfo {
    UINT nLangID;
    UINT nCodePage;
    INT  nDocPercent;
    INT  nConfidence;
} DetectEncodingInfo, *pDetectEncodingInfo;

/* ================================================================== */
/* M96 value adoption -- values adopted from the CeGCC-lineage w32api
 * reference (R1, public domain; docs/clean-room.md par.4
 * revision 2026-09-10).  Every name below is documented by
 * the official CE pages WITHOUT a value (see the record
 * comments and the held ledger in this header); the value
 * is a CE-era ABI fact carried by the CE lineage itself.
 * Desktop mingw-w64 was considered and EXCLUDED as a source
 * (desktop-era values; policy note in clean-room.md).  R1's
 * license-exception files (winsock*, gl*) are unused.
 * ================================================================== */

/* ---- MAX_ family (6 names; R1) ---- */
#define MAX_RFC1766_NAME                             0x0006
#define MAX_LOCALE_NAME                              0x0020
#define MAX_MIMEFACE_NAME                            0x0020
#define MAX_SCRIPT_NAME                              0x0030
#define MAX_MIMECSET_NAME                            0x0032
#define MAX_MIMECP_NAME                              0x0040


/* ------------------------------------------------------------------ */
/* Carrier structures.  Member lists are the CE pages' own printed      */
/* declarations (ms918820 MIMECPINFO, ms918821 MIMECSETINFO,            */
/* ms918852 RFC1766INFO, ms918857 SCRIPTINFO -- the page tag prints     */
/* "tagSCRIPINFO"); the array-length constants the pages name without   */
/* values were ADOPTED from R1 (M96 section at the end of this header). */
/* SCRIPTFONTINFO has no CE page (referenced by aa452373) -- opaque.    */
/* ------------------------------------------------------------------ */
typedef struct tagMIMECPINFO {
    DWORD dwFlags;
    UINT uiCodePage;
    UINT uiFamilyCodePage;
    WCHAR wszDescription[MAX_MIMECP_NAME];
    WCHAR wszWebCharset[MAX_MIMECSET_NAME];
    WCHAR wszHeaderCharset[MAX_MIMECSET_NAME];
    WCHAR wszBodyCharset[MAX_MIMECSET_NAME];
    WCHAR wszFixedWidthFont[MAX_MIMEFACE_NAME];
    WCHAR wszProportionalFont[MAX_MIMEFACE_NAME];
    BYTE bGDICharset;
} MIMECPINFO, *PMIMECPINFO;
typedef struct tagMIMECSETINFO {
    UINT uiCodePage;
    UINT uiInternetEncoding;
    WCHAR wszCharset[MAX_MIMECSET_NAME];
} MIMECSETINFO, *PMIMECSETINFO;
typedef struct tagRFC1766INFO {
    LCID lcid;
    WCHAR wszRfc1766[MAX_RFC1766_NAME];
    WCHAR wszLocaleName[MAX_LOCALE_NAME];
} RFC1766INFO, *PRFC1766INFO;
typedef struct tagSCRIPINFO {      /* page tag misprint kept in the tag */
    SCRIPT_ID ScriptId;
    UINT uiCodePage;
    WCHAR wszDescription[MAX_SCRIPT_NAME];
    WCHAR wszFixedWidthFont[MAX_MIMEFACE_NAME];
    WCHAR wszProportionalFont[MAX_MIMEFACE_NAME];
} SCRIPTINFO, *PSCRIPTINFO;
typedef struct SCRIPTFONTINFO SCRIPTFONTINFO;   /* no page; opaque */

/* ------------------------------------------------------------------ */
/*  MLang functions (Mlang.dll)                                        */
/* ------------------------------------------------------------------ */

/* aa452124 "ConvertINetMultiByteToUnicode". */
AKARI_CE_IMPORT HRESULT WINAPI ConvertINetMultiByteToUnicode(
    LPDWORD lpdwMode, DWORD dwSrcEncoding, LPCSTR lpSrcStr,
    LPINT lpnMultiCharCount, LPWSTR lpDstStr,
    LPINT lpnWideCharCount) AKARI_CE_NAME(ConvertINetMultiByteToUnicode);

/* aa452127 "ConvertINetString". */
AKARI_CE_IMPORT HRESULT WINAPI ConvertINetString(LPDWORD lpdwMode,
    DWORD dwSrcEncoding, DWORD dwDstEncoding, LPCSTR lpSrcStr,
    LPINT lpnSrcSize, LPBYTE lpDstStr, LPINT lpnDstSize)
    AKARI_CE_NAME(ConvertINetString);

/* aa452129 "ConvertINetUnicodeToMultiByte". */
AKARI_CE_IMPORT HRESULT WINAPI ConvertINetUnicodeToMultiByte(
    LPDWORD lpdwMode, DWORD dwEncoding, LPCWSTR lpSrcStr,
    LPINT lpnWideCharCount, LPSTR lpDstStr, LPINT lpnMultiCharCount)
    AKARI_CE_NAME(ConvertINetUnicodeToMultiByte);

/* ms918805 "IsConvertINetStringAvailable". */
AKARI_CE_IMPORT HRESULT WINAPI IsConvertINetStringAvailable(
    DWORD dwSrcEncoding, DWORD dwDstEncoding)
    AKARI_CE_NAME(IsConvertINetStringAvailable);

/* ms918817 "LcidToRfc1766" (LPTSTR parameter as printed; the page
 * publishes this single name -- no A/W pair is documented). */
AKARI_CE_IMPORT HRESULT WINAPI LcidToRfc1766(LCID Locale,
    LPTSTR pszRfc1766, int nChar) AKARI_CE_NAME(LcidToRfc1766);

/* ms918853 "Rfc1766ToLcid". */
AKARI_CE_IMPORT HRESULT WINAPI Rfc1766ToLcid(LCID* pLocale,
    LPTSTR pszRfc1766) AKARI_CE_NAME(Rfc1766ToLcid);

/* ------------------------------------------------------------------ */
/*  Interfaces (opaque; no page prints a vtable layout)                */
/* ------------------------------------------------------------------ */

/* ms906426 "IEnumCodePage" (Next/Reset/Skip documented; the CE book
 * has no Clone page).  CE caveat: "not supported on all Windows
 * CE-based operating systems". */
typedef struct IEnumCodePage IEnumCodePage;

/* ms906430 "IEnumRfc1766" (Next/Reset/Skip documented; no Clone
 * page).  CE caveat: not supported on all CE-based OSes. */
typedef struct IEnumRfc1766 IEnumRfc1766;

/* aa452258 "IEnumScript" (Clone/Next/Reset/Skip).  CE caveat: not
 * supported on all CE-based OSes. */
typedef struct IEnumScript IEnumScript;

/* aa452355 "IMLangCodePages" (4 methods).  CE caveat: not supported
 * on all CE-based OSes. */
typedef struct IMLangCodePages IMLangCodePages;

/* aa452360 "IMLangConvertCharset" (7 methods).  CE caveat: not
 * supported on all CE-based OSes. */
typedef struct IMLangConvertCharset IMLangConvertCharset;

/* aa452368 "IMLangFontLink" (inherits IMLangCodePages; 4 own
 * methods).  CE caveat: not supported on all CE-based OSes. */
typedef struct IMLangFontLink IMLangFontLink;

/* aa452369 "IMLangFontLink2" (inherits IMLangCodePages; subsumes
 * IMLangFontLink; 7 own methods).  CE caveat: not supported on all
 * CE-based OSes. */
typedef struct IMLangFontLink2 IMLangFontLink2;

/* aa452389 "IMLangLineBreakConsole" (2 methods).  CE caveat: not
 * supported on all CE-based OSes. */
typedef struct IMLangLineBreakConsole IMLangLineBreakConsole;

/* ms918295 "IMultiLanguage" (14 methods; "supported on all Windows
 * CE-based operating systems that include Mlang functionality"). */
typedef struct IMultiLanguage IMultiLanguage;

/* ms918297 "IMultiLanguage2" (23 methods).  CE caveat: not supported
 * on all CE-based OSes. */
typedef struct IMultiLanguage2 IMultiLanguage2;

/* ms918323 "IMultiLanguage3" (inherits IMultiLanguage2; 2 own
 * methods).  CE caveat: not supported on all CE-based OSes. */
typedef struct IMultiLanguage3 IMultiLanguage3;

/* ------------------------------------------------------------------ */
/*  Interface records (opaque; documented method signatures)           */
/* ------------------------------------------------------------------ */

/*
 * All interfaces carry the IUnknown methods (AddRef, QueryInterface,
 * Release) per their pages.  Archive print artifacts (missing spaces
 * like "HRESULTNext") are normalized; page ids are per method.
 *
 * IEnumCodePage (ms906426):
 *   ms906427  HRESULT Next(ULONG celt, PMIMECPINFO rgelt,
 *              ULONG* pceltFetched);  [PMIMECPINFO held with
 *              MIMECPINFO]
 *   ms906428  HRESULT Reset(void);
 *   ms906429  HRESULT Skip(ULONG celt);
 *
 * IEnumRfc1766 (ms906430):
 *   ms906431  HRESULT Next(ULONG celt, PRFC1766INFO rgelt,
 *              ULONG* pceltFetched);  [PRFC1766INFO held]
 *   ms906432  HRESULT Reset(void);
 *   ms906433  HRESULT Skip(ULONG celt);
 *
 * IEnumScript (aa452258):
 *   aa452277  HRESULT Clone(IEnumScript** ppEnum);
 *   aa452279  HRESULT Next(ULONG celt, PSCRIPTINFO rgelt,
 *              ULONG* pceltFetched);  [PSCRIPTINFO held]
 *   aa452281  HRESULT Reset(void);
 *   aa452283  HRESULT Skip(ULONG celt);
 *
 * IMLangCodePages (aa452355):
 *   aa452356  HRESULT CodePagesToCodePage(DWORD dwCodePages,
 *              UINT uDefaultCodePage, UINT* puCodePage);
 *   aa452357  HRESULT CodePageToCodePages(UINT uCodePage,
 *              DWORD* pdwCodePages);
 *   aa452358  HRESULT GetCharCodePages(WCHAR chSrc,
 *              DWORD* pdwCodePages);
 *   aa452359  HRESULT GetStrCodePages(const WCHAR* pszSrc,
 *              long cchSrc, DWORD dwPriorityCodePages,
 *              DWORD* pdwCodePages, long* pcchCodePages);
 *
 * IMLangConvertCharset (aa452360):
 *   aa452361  HRESULT DoConversion(BYTE* pSrcStr, UINT* pcSrcSize,
 *              BYTE* pDstStr, UINT* pcDstSize);
 *   aa452362  HRESULT DoConversionFromUnicode(WCHAR* pSrcStr,
 *              UINT* pcSrcSize, CHAR* pDstStr, UINT* pcDstSize);
 *   aa452363  HRESULT DoConversionToUnicode(CHAR* pSrcStr,
 *              UINT* pcSrcSize, WCHAR* pDstStr, UINT* pcDstSize);
 *   aa452364  HRESULT GetDestinationCodePage(UINT* puiDstCodePage);
 *   aa452365  HRESULT GetProperty(DWORD* pdwProperty);
 *   aa452366  HRESULT GetSourceCodePage(UINT* puiSrcCodePage);
 *   aa452367  HRESULT Initialize(UINT uiSrcCodePage,
 *              UINT uiDstCodePage, DWORD dwProperty);
 *
 * IMLangFontLink (aa452368; inherits IMLangCodePages):
 *   aa452382  HRESULT GetFontCodePages(HDC hDC, HFONT hFont,
 *              DWORD* pdwCodePages);
 *   aa452384  HRESULT MapFont(HDC hDC, DWORD dwCodePages,
 *              HFONT hSrcFont, HFONT* phDestFont);
 *   aa452386  HRESULT ReleaseFont(HFONT hFont);
 *   aa452387  HRESULT ResetFontMapping(void);
 *
 * IMLangFontLink2 (aa452369; inherits IMLangCodePages; subsumes
 * IMLangFontLink):
 *   aa452370  HRESULT CodePageToScriptID(UINT uiCodePage,
 *              SCRIPT_ID* pSid);
 *   aa452371  HRESULT GetFontCodePages(HDC hDC, HFONT hFont,
 *              DWORD* pdwCodePages);
 *   aa452372  HRESULT GetFontUnicodeRanges(HDC hDC, UINT* puiRanges,
 *              UNICODERANGE* pUranges);
 *   aa452373  HRESULT GetScriptFontInfo(SCRIPT_ID sid,
 *              DWORD dwFlags, UINT* puiFonts, SCRIPTFONTINFO*
 *              pScriptFont);  [SCRIPTFONTINFO held; the parameter
 *              text calls it "SCRIPTINFO str..." -- print artifact]
 *   aa452375  HRESULT MapFont(HDC hDC, DWORD dwCodePages,
 *              WCHAR chSrc, HFONT* pFont);
 *   aa452377  HRESULT ReleaseFont(HFONT hFont);
 *   aa452379  HRESULT ResetFontMapping(void);
 *
 * IMLangLineBreakConsole (aa452389):
 *   aa452391  HRESULT BreakLineA(LCID locale, UINT uCodePage,
 *              const CHAR* pszSrc, long cchSrc, long cMaxColumns,
 *              long* pcchLine, long* pcchSkip);
 *   ms918284  HRESULT BreakLineW(LCID locale, const WCHAR* pszSrc,
 *              long cchSrc, long cMaxColumns, long* pcchLine,
 *              long* pcchSkip);
 *
 * IMultiLanguage (ms918295; 14 methods):
 *   ms918324  HRESULT ConvertString(DWORD* pdwMode,
 *              DWORD dwSrcEncoding, DWORD dwDstEncoding,
 *              BYTE* pSrcStr, UINT* pcSrcSize, BYTE* pDstStr,
 *              UINT* pcDstSize);
 *   ms918325  HRESULT ConvertStringFromUnicode(DWORD* pdwMode,
 *              DWORD dwEncoding, WCHAR* pSrcStr, UINT* pcSrcSize,
 *              CHAR* pDstStr, UINT* pcDstSize);
 *   ms918326  HRESULT ConvertStringToUnicode(DWORD* pdwMode,
 *              DWORD dwEncoding, CHAR* pSrcStr, UINT* pcSrcSize,
 *              WCHAR* pDstStr, UINT* pcDstSize);
 *   ms918327  HRESULT CreateConvertCharset(UINT uiSrcCodePage,
 *              UINT uiDstCodePage, DWORD dwProperty,
 *              IMLangConvertCharset** ppMLangConvertCharset);
 *   ms918328  HRESULT EnumCodePages(DWORD grfFlags,
 *              IEnumCodePage** ppEnumCodePage);
 *   ms918329  HRESULT EnumRfc1766(IEnumRfc1766** ppEnumRfc1766);
 *   ms918330  HRESULT GetCharsetInfo(BSTR Charset,
 *              PMIMECSETINFO pCharsetInfo);  [PMIMECSETINFO held]
 *   ms918331  HRESULT GetCodePageInfo(UINT uiCodePage,
 *              PMIMECPINFO pCodePageInfo);  [PMIMECPINFO held]
 *   ms918332  HRESULT GetFamilyCodePage(UINT uiCodePage,
 *              UINT* puiFamilyCodePage);
 *   ms918334  HRESULT GetLcidFromRfc1766(LCID* pLocale,
 *              BSTR bstrRfc1766);
 *   ms918335  HRESULT GetNumberOfCodePageInfo(UINT* pcCodePage);
 *   ms918336  HRESULT GetRfc1766FromLcid(LCID Locale,
 *              BSTR* pbstrRfc1766);
 *   ms918337  HRESULT GetRfc1766Info(LCID Locale,
 *              PRFC1766INFO pRfc1766Info);  [PRFC1766INFO held]
 *   ms918338  HRESULT IsConvertible(DWORD dwSrcEncoding,
 *              DWORD dwDstEncoding);  [not currently implemented]
 *
 * IMultiLanguage2 (ms918297; 23 methods):
 *   ms918298  HRESULT ConvertString(DWORD* pdwMode,
 *              DWORD dwSrcEncoding, DWORD dwDstEncoding,
 *              BYTE* pSrcStr, UINT* pcSrcSize, BYTE* pDstStr,
 *              UINT* pcDstSize);
 *   ms918299  HRESULT ConvertStringFromUnicode(DWORD* pdwMode,
 *              DWORD dwEncoding, WCHAR* pSrcStr, UINT* pcSrcSize,
 *              CHAR* pDstStr, UINT* pcDstSize);
 *   ms918300  HRESULT ConvertStringFromUnicodeEx(DWORD* pdwMode,
 *              DWORD dwEncoding, WCHAR* pSrcStr, UINT* pcSrcSize,
 *              CHAR* pDstStr, UINT* pcDstSize, DWORD dwFlag,
 *              WCHAR* lpFallBack);
 *   ms918301  HRESULT ConvertStringInIStream(DWORD* pdwMode,
 *              DWORD dwFlag, WCHAR* lpFallBack, DWORD dwSrcEncoding,
 *              DWORD dwDstEncoding, IStream* pstmIn,
 *              IStream* pstmOut);
 *   ms918302  HRESULT ConvertStringToUnicode(DWORD* pdwMode,
 *              DWORD dwEncoding, CHAR* pSrcStr, UINT* pcSrcSize,
 *              WCHAR* pDstStr, UINT* pcDstSize);
 *   ms918303  HRESULT ConvertStringToUnicodeEx(DWORD* pdwMode,
 *              DWORD dwEncoding, CHAR* pSrcStr, UINT* pcSrcSize,
 *              WCHAR* pDstStr, UINT* pcDstSize, DWORD dwFlag,
 *              WCHAR* lpFallBack);
 *   ms918304  HRESULT CreateConvertCharset(UINT uiSrcCodePage,
 *              UINT uiDstCodePage, DWORD dwProperty,
 *              IMLangConvertCharset** ppMLangConvertCharset);
 *   ms918305  HRESULT DetectCodepageInIStream(DWORD dwFlag,
 *              DWORD dwPrefWinCodePage, IStream* pstmIn,
 *              DetectEncodingInfo* lpEncoding, INT* pnScores);
 *   ms918306  HRESULT DetectInputCodepage(DWORD dwFlag,
 *              DWORD dwPrefWinCodePage, CHAR* pSrcStr,
 *              INT* pcSrcSize, DetectEncodingInfo* lpEncoding,
 *              INT* pnScores);
 *   ms918307  HRESULT EnumCodePages(DWORD grfFlags, LANGID LangId,
 *              IEnumCodePage** ppEnumCodePage);
 *   ms918308  HRESULT EnumRfc1766(LANGID LangId,
 *              IEnumRfc1766** ppEnumRfc1766);
 *   ms918309  HRESULT EnumScripts(DWORD dwFlags, LANGID LangId,
 *              IEnumScript** ppEnumScript);
 *   ms918310  HRESULT GetCharsetInfo(BSTR Charset,
 *              PMIMECSETINFO pCharsetInfo);  [PMIMECSETINFO held]
 *   ms918311  HRESULT GetCodePageDescription(UINT uiCodePage,
 *              LCID lcid, LPWSTR lpWideCharStr, int cchWideChar);
 *   ms918312  HRESULT GetCodePageInfo(UINT uiCodePage,
 *              LANGID LangId, PMIMECPINFO pCodePageInfo);
 *              [PMIMECPINFO held]
 *   ms918313  HRESULT GetFamilyCodePage(UINT uiCodePage,
 *              UINT* puiFamilyCodePage);
 *   ms918314  HRESULT GetLcidFromRfc1766(LCID* pLocale,
 *              BSTR bstrRfc1766);
 *   ms918315  HRESULT GetNumberOfCodePageInfo(UINT* pcCodePage);
 *   ms918316  HRESULT GetNumberOfScripts(UINT* pnScripts);
 *   ms918317  HRESULT GetRfc1766FromLcid(LCID Locale,
 *              BSTR* pbstrRfc1766);
 *   ms918318  HRESULT GetRfc1766Info(LCID Locale, LANGID LangId,
 *              PRFC1766INFO pRfc1766Info);  [PRFC1766INFO held]
 *   ms918319  HRESULT IsConvertible(DWORD dwSrcEncoding,
 *              DWORD dwDstEncoding);  [not currently implemented]
 *   ms918320  HRESULT SetMimeDBSource(MIMECONTF dwSource);
 *
 * IMultiLanguage3 (ms918323; inherits IMultiLanguage2):
 *   ms918321  HRESULT DetectOutboundCodePage(DWORD dwFlags,
 *              LPCWSTR lpWideCharStr, UINT cchWideChar,
 *              UINT* puiPreferredCodePages, UINT nPreferredCodePages,
 *              UINT* puiDetectedCodePages, UINT* pnDetectedCodePages,
 *              WCHAR* lpSpecialChar);
 *   ms918322  HRESULT DetectOutboundCodePageInIStream(
 *              DWORD dwFlags, IStream* pStrIn,
 *              UINT* puiPreferredCodePages, UINT nPreferredCodePages,
 *              UINT* puiDetectedCodePages, UINT* pnDetectedCodePages,
 *              WCHAR* lpSpecialChar);
 */

/* ================================================================== */
/* M97 vtable adoption -- COM interfaces made callable from C.  Vtable
 * ORDER adopted from R1 (CeGCC-lineage w32api, public
 * domain; docs/clean-room.md par.4 revision 2026-09-10);
 * method names/types are the CE pages' own printed
 * signatures (the records above).  Methods the CE pages do
 * not document but R1 carries are INCLUDED and tagged
 * "(R1)" -- dropping a middle slot would shift the layout.
 * Calling convention: plain function pointers (WINAPI is
 * empty here: CE-wide cdecl; R1's __stdcall NOT adopted). */
/* ================================================================== */

/* ---- IEnumCodePage: 3 documented method pages; order R1 ---- */
typedef struct IEnumCodePageVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IEnumCodePage*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IEnumCodePage*);  /* (R1) */
    ULONG (WINAPI *Release)(IEnumCodePage*);  /* (R1) */
    /* IEnumCodePage */
    HRESULT (WINAPI *Clone)(IEnumCodePage*, IEnumCodePage**);  /* (R1) */
    HRESULT (WINAPI *Next)(IEnumCodePage*, ULONG celt, PMIMECPINFO rgelt, ULONG* pceltFetched);  /* ms906427 */
    HRESULT (WINAPI *Reset)(IEnumCodePage*);  /* ms906428 */
    HRESULT (WINAPI *Skip)(IEnumCodePage*, ULONG celt);  /* ms906429 */
} IEnumCodePageVtbl;
struct IEnumCodePage { const IEnumCodePageVtbl *lpVtbl; };
#define IEnumCodePage_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IEnumCodePage_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IEnumCodePage_Release(T) ((T)->lpVtbl->Release(T))
#define IEnumCodePage_Clone(T,a) ((T)->lpVtbl->Clone(T,a))
#define IEnumCodePage_Next(T,a,b,c) ((T)->lpVtbl->Next(T,a,b,c))
#define IEnumCodePage_Reset(T) ((T)->lpVtbl->Reset(T))
#define IEnumCodePage_Skip(T,a) ((T)->lpVtbl->Skip(T,a))

/* ---- IEnumRfc1766: 3 documented method pages; order R1 ---- */
typedef struct IEnumRfc1766Vtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IEnumRfc1766*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IEnumRfc1766*);  /* (R1) */
    ULONG (WINAPI *Release)(IEnumRfc1766*);  /* (R1) */
    /* IEnumRfc1766 */
    HRESULT (WINAPI *Clone)(IEnumRfc1766*, IEnumRfc1766**);  /* (R1) */
    HRESULT (WINAPI *Next)(IEnumRfc1766*, ULONG celt, PRFC1766INFO rgelt, ULONG* pceltFetched);  /* ms906431 */
    HRESULT (WINAPI *Reset)(IEnumRfc1766*);  /* ms906432 */
    HRESULT (WINAPI *Skip)(IEnumRfc1766*, ULONG celt);  /* ms906433 */
} IEnumRfc1766Vtbl;
struct IEnumRfc1766 { const IEnumRfc1766Vtbl *lpVtbl; };
#define IEnumRfc1766_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IEnumRfc1766_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IEnumRfc1766_Release(T) ((T)->lpVtbl->Release(T))
#define IEnumRfc1766_Clone(T,a) ((T)->lpVtbl->Clone(T,a))
#define IEnumRfc1766_Next(T,a,b,c) ((T)->lpVtbl->Next(T,a,b,c))
#define IEnumRfc1766_Reset(T) ((T)->lpVtbl->Reset(T))
#define IEnumRfc1766_Skip(T,a) ((T)->lpVtbl->Skip(T,a))

/* ---- IEnumScript: 4 documented method pages; order R1 ---- */
typedef struct IEnumScriptVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IEnumScript*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IEnumScript*);  /* (R1) */
    ULONG (WINAPI *Release)(IEnumScript*);  /* (R1) */
    /* IEnumScript */
    HRESULT (WINAPI *Clone)(IEnumScript*, IEnumScript** ppEnum);  /* aa452277 */
    HRESULT (WINAPI *Next)(IEnumScript*, ULONG celt, PSCRIPTINFO rgelt, ULONG* pceltFetched);  /* aa452279 */
    HRESULT (WINAPI *Reset)(IEnumScript*);  /* aa452281 */
    HRESULT (WINAPI *Skip)(IEnumScript*, ULONG celt);  /* aa452283 */
} IEnumScriptVtbl;
struct IEnumScript { const IEnumScriptVtbl *lpVtbl; };
#define IEnumScript_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IEnumScript_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IEnumScript_Release(T) ((T)->lpVtbl->Release(T))
#define IEnumScript_Clone(T,a) ((T)->lpVtbl->Clone(T,a))
#define IEnumScript_Next(T,a,b,c) ((T)->lpVtbl->Next(T,a,b,c))
#define IEnumScript_Reset(T) ((T)->lpVtbl->Reset(T))
#define IEnumScript_Skip(T,a) ((T)->lpVtbl->Skip(T,a))

/* ---- IMLangCodePages: 4 documented method pages; order R1 ---- */
typedef struct IMLangCodePagesVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IMLangCodePages*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IMLangCodePages*);  /* (R1) */
    ULONG (WINAPI *Release)(IMLangCodePages*);  /* (R1) */
    /* IMLangCodePages */
    HRESULT (WINAPI *GetCharCodePages)(IMLangCodePages*, WCHAR chSrc, DWORD* pdwCodePages);  /* aa452358 */
    HRESULT (WINAPI *GetStrCodePages)(IMLangCodePages*, const WCHAR* pszSrc, long cchSrc, DWORD dwPriorityCodePages, DWORD* pdwCodePages, long* pcchCodePages);  /* aa452359 */
    HRESULT (WINAPI *CodePageToCodePages)(IMLangCodePages*, UINT uCodePage, DWORD* pdwCodePages);  /* aa452357 */
    HRESULT (WINAPI *CodePagesToCodePage)(IMLangCodePages*, DWORD dwCodePages, UINT uDefaultCodePage, UINT* puCodePage);  /* aa452356 */
} IMLangCodePagesVtbl;
struct IMLangCodePages { const IMLangCodePagesVtbl *lpVtbl; };
#define IMLangCodePages_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IMLangCodePages_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IMLangCodePages_Release(T) ((T)->lpVtbl->Release(T))
#define IMLangCodePages_GetCharCodePages(T,a,b) ((T)->lpVtbl->GetCharCodePages(T,a,b))
#define IMLangCodePages_GetStrCodePages(T,a,b,c,d,e) ((T)->lpVtbl->GetStrCodePages(T,a,b,c,d,e))
#define IMLangCodePages_CodePageToCodePages(T,a,b) ((T)->lpVtbl->CodePageToCodePages(T,a,b))
#define IMLangCodePages_CodePagesToCodePage(T,a,b,c) ((T)->lpVtbl->CodePagesToCodePage(T,a,b,c))

/* ---- IMLangConvertCharset: 7 documented method pages; order R1 ---- */
typedef struct IMLangConvertCharsetVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IMLangConvertCharset*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IMLangConvertCharset*);  /* (R1) */
    ULONG (WINAPI *Release)(IMLangConvertCharset*);  /* (R1) */
    /* IMLangConvertCharset */
    HRESULT (WINAPI *Initialize)(IMLangConvertCharset*, UINT uiSrcCodePage, UINT uiDstCodePage, DWORD dwProperty);  /* aa452367 */
    HRESULT (WINAPI *GetSourceCodePage)(IMLangConvertCharset*, UINT* puiSrcCodePage);  /* aa452366 */
    HRESULT (WINAPI *GetDestinationCodePage)(IMLangConvertCharset*, UINT* puiDstCodePage);  /* aa452364 */
    HRESULT (WINAPI *GetProperty)(IMLangConvertCharset*, DWORD* pdwProperty);  /* aa452365 */
    HRESULT (WINAPI *DoConversion)(IMLangConvertCharset*, BYTE* pSrcStr, UINT* pcSrcSize, BYTE* pDstStr, UINT* pcDstSize);  /* aa452361 */
    HRESULT (WINAPI *DoConversionToUnicode)(IMLangConvertCharset*, CHAR* pSrcStr, UINT* pcSrcSize, WCHAR* pDstStr, UINT* pcDstSize);  /* aa452363 */
    HRESULT (WINAPI *DoConversionFromUnicode)(IMLangConvertCharset*, WCHAR* pSrcStr, UINT* pcSrcSize, CHAR* pDstStr, UINT* pcDstSize);  /* aa452362 */
} IMLangConvertCharsetVtbl;
struct IMLangConvertCharset { const IMLangConvertCharsetVtbl *lpVtbl; };
#define IMLangConvertCharset_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IMLangConvertCharset_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IMLangConvertCharset_Release(T) ((T)->lpVtbl->Release(T))
#define IMLangConvertCharset_Initialize(T,a,b,c) ((T)->lpVtbl->Initialize(T,a,b,c))
#define IMLangConvertCharset_GetSourceCodePage(T,a) ((T)->lpVtbl->GetSourceCodePage(T,a))
#define IMLangConvertCharset_GetDestinationCodePage(T,a) ((T)->lpVtbl->GetDestinationCodePage(T,a))
#define IMLangConvertCharset_GetProperty(T,a) ((T)->lpVtbl->GetProperty(T,a))
#define IMLangConvertCharset_DoConversion(T,a,b,c,d) ((T)->lpVtbl->DoConversion(T,a,b,c,d))
#define IMLangConvertCharset_DoConversionToUnicode(T,a,b,c,d) ((T)->lpVtbl->DoConversionToUnicode(T,a,b,c,d))
#define IMLangConvertCharset_DoConversionFromUnicode(T,a,b,c,d) ((T)->lpVtbl->DoConversionFromUnicode(T,a,b,c,d))

/* ---- IMLangFontLink: 4 documented method pages; order R1 ---- */
typedef struct IMLangFontLinkVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IMLangFontLink*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IMLangFontLink*);  /* (R1) */
    ULONG (WINAPI *Release)(IMLangFontLink*);  /* (R1) */
    /* IMLangCodePages */
    HRESULT (WINAPI *GetCharCodePages)(IMLangFontLink*, WCHAR, DWORD*);  /* (R1) */
    HRESULT (WINAPI *GetStrCodePages)(IMLangFontLink*, const WCHAR*, long, DWORD, DWORD*, long*);  /* (R1) */
    HRESULT (WINAPI *CodePageToCodePages)(IMLangFontLink*, UINT, DWORD*);  /* (R1) */
    HRESULT (WINAPI *CodePagesToCodePage)(IMLangFontLink*, DWORD, UINT, UINT*);  /* (R1) */
    /* IMLangFontLink */
    HRESULT (WINAPI *GetFontCodePages)(IMLangFontLink*, HDC hDC, HFONT hFont, DWORD* pdwCodePages);  /* aa452382 */
    HRESULT (WINAPI *MapFont)(IMLangFontLink*, HDC hDC, DWORD dwCodePages, HFONT hSrcFont, HFONT* phDestFont);  /* aa452384 */
    HRESULT (WINAPI *ReleaseFont)(IMLangFontLink*, HFONT hFont);  /* aa452386 */
    HRESULT (WINAPI *ResetFontMapping)(IMLangFontLink*);  /* aa452387 */
} IMLangFontLinkVtbl;
struct IMLangFontLink { const IMLangFontLinkVtbl *lpVtbl; };
#define IMLangFontLink_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IMLangFontLink_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IMLangFontLink_Release(T) ((T)->lpVtbl->Release(T))
#define IMLangFontLink_GetCharCodePages(T,a,b) ((T)->lpVtbl->GetCharCodePages(T,a,b))
#define IMLangFontLink_GetStrCodePages(T,a,b,c,d,e) ((T)->lpVtbl->GetStrCodePages(T,a,b,c,d,e))
#define IMLangFontLink_CodePageToCodePages(T,a,b) ((T)->lpVtbl->CodePageToCodePages(T,a,b))
#define IMLangFontLink_CodePagesToCodePage(T,a,b,c) ((T)->lpVtbl->CodePagesToCodePage(T,a,b,c))
#define IMLangFontLink_GetFontCodePages(T,a,b,c) ((T)->lpVtbl->GetFontCodePages(T,a,b,c))
#define IMLangFontLink_MapFont(T,a,b,c,d) ((T)->lpVtbl->MapFont(T,a,b,c,d))
#define IMLangFontLink_ReleaseFont(T,a) ((T)->lpVtbl->ReleaseFont(T,a))
#define IMLangFontLink_ResetFontMapping(T) ((T)->lpVtbl->ResetFontMapping(T))

/* ---- IMLangFontLink2: 7 documented method pages; order R1 ---- */
typedef struct IMLangFontLink2Vtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IMLangFontLink2*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IMLangFontLink2*);  /* (R1) */
    ULONG (WINAPI *Release)(IMLangFontLink2*);  /* (R1) */
    /* IMLangCodePages */
    HRESULT (WINAPI *GetCharCodePages)(IMLangFontLink2*, WCHAR, DWORD*);  /* (R1) */
    HRESULT (WINAPI *GetStrCodePages)(IMLangFontLink2*, const WCHAR*, long, DWORD, DWORD*, long*);  /* (R1) */
    HRESULT (WINAPI *CodePageToCodePages)(IMLangFontLink2*, UINT, DWORD*);  /* (R1) */
    HRESULT (WINAPI *CodePagesToCodePage)(IMLangFontLink2*, DWORD, UINT, UINT*);  /* (R1) */
    /* IMLangFontLink2 */
    HRESULT (WINAPI *GetFontCodePages)(IMLangFontLink2*, HDC hDC, HFONT hFont, DWORD* pdwCodePages);  /* aa452371 */
    HRESULT (WINAPI *ReleaseFont)(IMLangFontLink2*, HFONT hFont);  /* aa452377 */
    HRESULT (WINAPI *ResetFontMapping)(IMLangFontLink2*);  /* aa452379 */
    HRESULT (WINAPI *MapFont)(IMLangFontLink2*, HDC hDC, DWORD dwCodePages, WCHAR chSrc, HFONT* pFont);  /* aa452375 */
    HRESULT (WINAPI *GetFontUnicodeRanges)(IMLangFontLink2*, HDC hDC, UINT* puiRanges, UNICODERANGE* pUranges);  /* aa452372 */
    HRESULT (WINAPI *GetScriptFontInfo)(IMLangFontLink2*, SCRIPT_ID sid, DWORD dwFlags, UINT* puiFonts, SCRIPTFONTINFO* pScriptFont);  /* aa452373 */
    HRESULT (WINAPI *CodePageToScriptID)(IMLangFontLink2*, UINT uiCodePage, SCRIPT_ID* pSid);  /* aa452370 */
} IMLangFontLink2Vtbl;
struct IMLangFontLink2 { const IMLangFontLink2Vtbl *lpVtbl; };
#define IMLangFontLink2_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IMLangFontLink2_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IMLangFontLink2_Release(T) ((T)->lpVtbl->Release(T))
#define IMLangFontLink2_GetCharCodePages(T,a,b) ((T)->lpVtbl->GetCharCodePages(T,a,b))
#define IMLangFontLink2_GetStrCodePages(T,a,b,c,d,e) ((T)->lpVtbl->GetStrCodePages(T,a,b,c,d,e))
#define IMLangFontLink2_CodePageToCodePages(T,a,b) ((T)->lpVtbl->CodePageToCodePages(T,a,b))
#define IMLangFontLink2_CodePagesToCodePage(T,a,b,c) ((T)->lpVtbl->CodePagesToCodePage(T,a,b,c))
#define IMLangFontLink2_GetFontCodePages(T,a,b,c) ((T)->lpVtbl->GetFontCodePages(T,a,b,c))
#define IMLangFontLink2_ReleaseFont(T,a) ((T)->lpVtbl->ReleaseFont(T,a))
#define IMLangFontLink2_ResetFontMapping(T) ((T)->lpVtbl->ResetFontMapping(T))
#define IMLangFontLink2_MapFont(T,a,b,c,d) ((T)->lpVtbl->MapFont(T,a,b,c,d))
#define IMLangFontLink2_GetFontUnicodeRanges(T,a,b,c) ((T)->lpVtbl->GetFontUnicodeRanges(T,a,b,c))
#define IMLangFontLink2_GetScriptFontInfo(T,a,b,c,d) ((T)->lpVtbl->GetScriptFontInfo(T,a,b,c,d))
#define IMLangFontLink2_CodePageToScriptID(T,a,b) ((T)->lpVtbl->CodePageToScriptID(T,a,b))

/* ---- IMLangLineBreakConsole: 2 documented method pages; order R1 ---- */
typedef struct IMLangLineBreakConsoleVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IMLangLineBreakConsole*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IMLangLineBreakConsole*);  /* (R1) */
    ULONG (WINAPI *Release)(IMLangLineBreakConsole*);  /* (R1) */
    /* IMLangLineBreakConsole */
    HRESULT (WINAPI *BreakLineML)(IMLangLineBreakConsole*);  /* (R1) */
    HRESULT (WINAPI *BreakLineW)(IMLangLineBreakConsole*, LCID locale, const WCHAR* pszSrc, long cchSrc, long cMaxColumns, long* pcchLine, long* pcchSkip);  /* ms918284 */
    HRESULT (WINAPI *BreakLineA)(IMLangLineBreakConsole*, LCID locale, UINT uCodePage, const CHAR* pszSrc, long cchSrc, long cMaxColumns, long* pcchLine, long* pcchSkip);  /* aa452391 */
} IMLangLineBreakConsoleVtbl;
struct IMLangLineBreakConsole { const IMLangLineBreakConsoleVtbl *lpVtbl; };
#define IMLangLineBreakConsole_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IMLangLineBreakConsole_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IMLangLineBreakConsole_Release(T) ((T)->lpVtbl->Release(T))
#define IMLangLineBreakConsole_BreakLineML(T) ((T)->lpVtbl->BreakLineML(T))
#define IMLangLineBreakConsole_BreakLineW(T,a,b,c,d,e,f) ((T)->lpVtbl->BreakLineW(T,a,b,c,d,e,f))
#define IMLangLineBreakConsole_BreakLineA(T,a,b,c,d,e,f,g) ((T)->lpVtbl->BreakLineA(T,a,b,c,d,e,f,g))

/* ---- IMultiLanguage: 14 documented method pages; order R1 ---- */
typedef struct IMultiLanguageVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IMultiLanguage*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IMultiLanguage*);  /* (R1) */
    ULONG (WINAPI *Release)(IMultiLanguage*);  /* (R1) */
    /* IMultiLanguage */
    HRESULT (WINAPI *GetNumberOfCodePageInfo)(IMultiLanguage*, UINT* pcCodePage);  /* ms918335 */
    HRESULT (WINAPI *GetCodePageInfo)(IMultiLanguage*, UINT uiCodePage, PMIMECPINFO pCodePageInfo);  /* ms918331 */
    HRESULT (WINAPI *GetFamilyCodePage)(IMultiLanguage*, UINT uiCodePage, UINT* puiFamilyCodePage);  /* ms918332 */
    HRESULT (WINAPI *EnumCodePages)(IMultiLanguage*, DWORD grfFlags, IEnumCodePage** ppEnumCodePage);  /* ms918328 */
    HRESULT (WINAPI *GetCharsetInfo)(IMultiLanguage*, BSTR Charset, PMIMECSETINFO pCharsetInfo);  /* ms918330 */
    HRESULT (WINAPI *IsConvertible)(IMultiLanguage*, DWORD dwSrcEncoding, DWORD dwDstEncoding);  /* ms918338 */
    HRESULT (WINAPI *ConvertString)(IMultiLanguage*, DWORD* pdwMode, DWORD dwSrcEncoding, DWORD dwDstEncoding, BYTE* pSrcStr, UINT* pcSrcSize, BYTE* pDstStr, UINT* pcDstSize);  /* ms918324 */
    HRESULT (WINAPI *ConvertStringToUnicode)(IMultiLanguage*, DWORD* pdwMode, DWORD dwEncoding, CHAR* pSrcStr, UINT* pcSrcSize, WCHAR* pDstStr, UINT* pcDstSize);  /* ms918326 */
    HRESULT (WINAPI *ConvertStringFromUnicode)(IMultiLanguage*, DWORD* pdwMode, DWORD dwEncoding, WCHAR* pSrcStr, UINT* pcSrcSize, CHAR* pDstStr, UINT* pcDstSize);  /* ms918325 */
    HRESULT (WINAPI *ConvertStringReset)(IMultiLanguage*);  /* (R1) */
    HRESULT (WINAPI *GetRfc1766FromLcid)(IMultiLanguage*, LCID Locale, BSTR* pbstrRfc1766);  /* ms918336 */
    HRESULT (WINAPI *GetLcidFromRfc1766)(IMultiLanguage*, LCID* pLocale, BSTR bstrRfc1766);  /* ms918334 */
    HRESULT (WINAPI *EnumRfc1766)(IMultiLanguage*, IEnumRfc1766** ppEnumRfc1766);  /* ms918329 */
    HRESULT (WINAPI *GetRfc1766Info)(IMultiLanguage*, LCID Locale, PRFC1766INFO pRfc1766Info);  /* ms918337 */
    HRESULT (WINAPI *CreateConvertCharset)(IMultiLanguage*, UINT uiSrcCodePage, UINT uiDstCodePage, DWORD dwProperty, IMLangConvertCharset** ppMLangConvertCharset);  /* ms918327 */
} IMultiLanguageVtbl;
struct IMultiLanguage { const IMultiLanguageVtbl *lpVtbl; };
#define IMultiLanguage_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IMultiLanguage_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IMultiLanguage_Release(T) ((T)->lpVtbl->Release(T))
#define IMultiLanguage_GetNumberOfCodePageInfo(T,a) ((T)->lpVtbl->GetNumberOfCodePageInfo(T,a))
#define IMultiLanguage_GetCodePageInfo(T,a,b) ((T)->lpVtbl->GetCodePageInfo(T,a,b))
#define IMultiLanguage_GetFamilyCodePage(T,a,b) ((T)->lpVtbl->GetFamilyCodePage(T,a,b))
#define IMultiLanguage_EnumCodePages(T,a,b) ((T)->lpVtbl->EnumCodePages(T,a,b))
#define IMultiLanguage_GetCharsetInfo(T,a,b) ((T)->lpVtbl->GetCharsetInfo(T,a,b))
#define IMultiLanguage_IsConvertible(T,a,b) ((T)->lpVtbl->IsConvertible(T,a,b))
#define IMultiLanguage_ConvertString(T,a,b,c,d,e,f,g) ((T)->lpVtbl->ConvertString(T,a,b,c,d,e,f,g))
#define IMultiLanguage_ConvertStringToUnicode(T,a,b,c,d,e,f) ((T)->lpVtbl->ConvertStringToUnicode(T,a,b,c,d,e,f))
#define IMultiLanguage_ConvertStringFromUnicode(T,a,b,c,d,e,f) ((T)->lpVtbl->ConvertStringFromUnicode(T,a,b,c,d,e,f))
#define IMultiLanguage_ConvertStringReset(T) ((T)->lpVtbl->ConvertStringReset(T))
#define IMultiLanguage_GetRfc1766FromLcid(T,a,b) ((T)->lpVtbl->GetRfc1766FromLcid(T,a,b))
#define IMultiLanguage_GetLcidFromRfc1766(T,a,b) ((T)->lpVtbl->GetLcidFromRfc1766(T,a,b))
#define IMultiLanguage_EnumRfc1766(T,a) ((T)->lpVtbl->EnumRfc1766(T,a))
#define IMultiLanguage_GetRfc1766Info(T,a,b) ((T)->lpVtbl->GetRfc1766Info(T,a,b))
#define IMultiLanguage_CreateConvertCharset(T,a,b,c,d) ((T)->lpVtbl->CreateConvertCharset(T,a,b,c,d))

/* ---- IMultiLanguage2: 23 documented method pages; order R1 ---- */
typedef struct IMultiLanguage2Vtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IMultiLanguage2*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IMultiLanguage2*);  /* (R1) */
    ULONG (WINAPI *Release)(IMultiLanguage2*);  /* (R1) */
    /* IMultiLanguage2 */
    HRESULT (WINAPI *GetNumberOfCodePageInfo)(IMultiLanguage2*, UINT* pcCodePage);  /* ms918315 */
    HRESULT (WINAPI *GetCodePageInfo)(IMultiLanguage2*, UINT uiCodePage, LANGID LangId, PMIMECPINFO pCodePageInfo);  /* ms918312 */
    HRESULT (WINAPI *GetFamilyCodePage)(IMultiLanguage2*, UINT uiCodePage, UINT* puiFamilyCodePage);  /* ms918313 */
    HRESULT (WINAPI *EnumCodePages)(IMultiLanguage2*, DWORD grfFlags, LANGID LangId, IEnumCodePage** ppEnumCodePage);  /* ms918307 */
    HRESULT (WINAPI *GetCharsetInfo)(IMultiLanguage2*, BSTR Charset, PMIMECSETINFO pCharsetInfo);  /* ms918310 */
    HRESULT (WINAPI *IsConvertible)(IMultiLanguage2*, DWORD dwSrcEncoding, DWORD dwDstEncoding);  /* ms918319 */
    HRESULT (WINAPI *ConvertString)(IMultiLanguage2*, DWORD* pdwMode, DWORD dwSrcEncoding, DWORD dwDstEncoding, BYTE* pSrcStr, UINT* pcSrcSize, BYTE* pDstStr, UINT* pcDstSize);  /* ms918298 */
    HRESULT (WINAPI *ConvertStringToUnicode)(IMultiLanguage2*, DWORD* pdwMode, DWORD dwEncoding, CHAR* pSrcStr, UINT* pcSrcSize, WCHAR* pDstStr, UINT* pcDstSize);  /* ms918302 */
    HRESULT (WINAPI *ConvertStringFromUnicode)(IMultiLanguage2*, DWORD* pdwMode, DWORD dwEncoding, WCHAR* pSrcStr, UINT* pcSrcSize, CHAR* pDstStr, UINT* pcDstSize);  /* ms918299 */
    HRESULT (WINAPI *ConvertStringReset)(IMultiLanguage2*);  /* (R1) */
    HRESULT (WINAPI *GetRfc1766FromLcid)(IMultiLanguage2*, LCID Locale, BSTR* pbstrRfc1766);  /* ms918317 */
    HRESULT (WINAPI *GetLcidFromRfc1766)(IMultiLanguage2*, LCID* pLocale, BSTR bstrRfc1766);  /* ms918314 */
    HRESULT (WINAPI *EnumRfc1766)(IMultiLanguage2*, LANGID LangId, IEnumRfc1766** ppEnumRfc1766);  /* ms918308 */
    HRESULT (WINAPI *GetRfc1766Info)(IMultiLanguage2*, LCID Locale, LANGID LangId, PRFC1766INFO pRfc1766Info);  /* ms918318 */
    HRESULT (WINAPI *CreateConvertCharset)(IMultiLanguage2*, UINT uiSrcCodePage, UINT uiDstCodePage, DWORD dwProperty, IMLangConvertCharset** ppMLangConvertCharset);  /* ms918304 */
    HRESULT (WINAPI *ConvertStringInIStream)(IMultiLanguage2*, DWORD* pdwMode, DWORD dwFlag, WCHAR* lpFallBack, DWORD dwSrcEncoding, DWORD dwDstEncoding, IStream* pstmIn, IStream* pstmOut);  /* ms918301 */
    HRESULT (WINAPI *ConvertStringToUnicodeEx)(IMultiLanguage2*, DWORD* pdwMode, DWORD dwEncoding, CHAR* pSrcStr, UINT* pcSrcSize, WCHAR* pDstStr, UINT* pcDstSize, DWORD dwFlag, WCHAR* lpFallBack);  /* ms918303 */
    HRESULT (WINAPI *ConvertStringFromUnicodeEx)(IMultiLanguage2*, DWORD* pdwMode, DWORD dwEncoding, WCHAR* pSrcStr, UINT* pcSrcSize, CHAR* pDstStr, UINT* pcDstSize, DWORD dwFlag, WCHAR* lpFallBack);  /* ms918300 */
    HRESULT (WINAPI *DetectCodepageInIStream)(IMultiLanguage2*, DWORD dwFlag, DWORD dwPrefWinCodePage, IStream* pstmIn, DetectEncodingInfo* lpEncoding, INT* pnScores);  /* ms918305 */
    HRESULT (WINAPI *DetectInputCodepage)(IMultiLanguage2*, DWORD dwFlag, DWORD dwPrefWinCodePage, CHAR* pSrcStr, INT* pcSrcSize, DetectEncodingInfo* lpEncoding, INT* pnScores);  /* ms918306 */
    HRESULT (WINAPI *ValidateCodePage)(IMultiLanguage2*);  /* (R1) */
    HRESULT (WINAPI *GetCodePageDescription)(IMultiLanguage2*, UINT uiCodePage, LCID lcid, LPWSTR lpWideCharStr, int cchWideChar);  /* ms918311 */
    HRESULT (WINAPI *IsCodePageInstallable)(IMultiLanguage2*);  /* (R1) */
    HRESULT (WINAPI *SetMimeDBSource)(IMultiLanguage2*, MIMECONTF dwSource);  /* ms918320 */
    HRESULT (WINAPI *GetNumberOfScripts)(IMultiLanguage2*, UINT* pnScripts);  /* ms918316 */
    HRESULT (WINAPI *EnumScripts)(IMultiLanguage2*, DWORD dwFlags, LANGID LangId, IEnumScript** ppEnumScript);  /* ms918309 */
} IMultiLanguage2Vtbl;
struct IMultiLanguage2 { const IMultiLanguage2Vtbl *lpVtbl; };
#define IMultiLanguage2_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IMultiLanguage2_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IMultiLanguage2_Release(T) ((T)->lpVtbl->Release(T))
#define IMultiLanguage2_GetNumberOfCodePageInfo(T,a) ((T)->lpVtbl->GetNumberOfCodePageInfo(T,a))
#define IMultiLanguage2_GetCodePageInfo(T,a,b,c) ((T)->lpVtbl->GetCodePageInfo(T,a,b,c))
#define IMultiLanguage2_GetFamilyCodePage(T,a,b) ((T)->lpVtbl->GetFamilyCodePage(T,a,b))
#define IMultiLanguage2_EnumCodePages(T,a,b,c) ((T)->lpVtbl->EnumCodePages(T,a,b,c))
#define IMultiLanguage2_GetCharsetInfo(T,a,b) ((T)->lpVtbl->GetCharsetInfo(T,a,b))
#define IMultiLanguage2_IsConvertible(T,a,b) ((T)->lpVtbl->IsConvertible(T,a,b))
#define IMultiLanguage2_ConvertString(T,a,b,c,d,e,f,g) ((T)->lpVtbl->ConvertString(T,a,b,c,d,e,f,g))
#define IMultiLanguage2_ConvertStringToUnicode(T,a,b,c,d,e,f) ((T)->lpVtbl->ConvertStringToUnicode(T,a,b,c,d,e,f))
#define IMultiLanguage2_ConvertStringFromUnicode(T,a,b,c,d,e,f) ((T)->lpVtbl->ConvertStringFromUnicode(T,a,b,c,d,e,f))
#define IMultiLanguage2_ConvertStringReset(T) ((T)->lpVtbl->ConvertStringReset(T))
#define IMultiLanguage2_GetRfc1766FromLcid(T,a,b) ((T)->lpVtbl->GetRfc1766FromLcid(T,a,b))
#define IMultiLanguage2_GetLcidFromRfc1766(T,a,b) ((T)->lpVtbl->GetLcidFromRfc1766(T,a,b))
#define IMultiLanguage2_EnumRfc1766(T,a,b) ((T)->lpVtbl->EnumRfc1766(T,a,b))
#define IMultiLanguage2_GetRfc1766Info(T,a,b,c) ((T)->lpVtbl->GetRfc1766Info(T,a,b,c))
#define IMultiLanguage2_CreateConvertCharset(T,a,b,c,d) ((T)->lpVtbl->CreateConvertCharset(T,a,b,c,d))
#define IMultiLanguage2_ConvertStringInIStream(T,a,b,c,d,e,f,g) ((T)->lpVtbl->ConvertStringInIStream(T,a,b,c,d,e,f,g))
#define IMultiLanguage2_ConvertStringToUnicodeEx(T,a,b,c,d,e,f,g,h) ((T)->lpVtbl->ConvertStringToUnicodeEx(T,a,b,c,d,e,f,g,h))
#define IMultiLanguage2_ConvertStringFromUnicodeEx(T,a,b,c,d,e,f,g,h) ((T)->lpVtbl->ConvertStringFromUnicodeEx(T,a,b,c,d,e,f,g,h))
#define IMultiLanguage2_DetectCodepageInIStream(T,a,b,c,d,e) ((T)->lpVtbl->DetectCodepageInIStream(T,a,b,c,d,e))
#define IMultiLanguage2_DetectInputCodepage(T,a,b,c,d,e,f) ((T)->lpVtbl->DetectInputCodepage(T,a,b,c,d,e,f))
#define IMultiLanguage2_ValidateCodePage(T) ((T)->lpVtbl->ValidateCodePage(T))
#define IMultiLanguage2_GetCodePageDescription(T,a,b,c,d) ((T)->lpVtbl->GetCodePageDescription(T,a,b,c,d))
#define IMultiLanguage2_IsCodePageInstallable(T) ((T)->lpVtbl->IsCodePageInstallable(T))
#define IMultiLanguage2_SetMimeDBSource(T,a) ((T)->lpVtbl->SetMimeDBSource(T,a))
#define IMultiLanguage2_GetNumberOfScripts(T,a) ((T)->lpVtbl->GetNumberOfScripts(T,a))
#define IMultiLanguage2_EnumScripts(T,a,b,c) ((T)->lpVtbl->EnumScripts(T,a,b,c))

#ifdef __cplusplus
}
#endif

#endif /* AKARI_MLANG_H */
