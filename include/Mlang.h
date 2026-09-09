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

/*
 * HELD structures (prints recorded; array-length constants not
 * published anywhere official -- see the header note):
 *   ms918820 MIMECPINFO: typedef struct tagMIMECPINFO { DWORD
 *     dwFlags; UINT uiCodePage; UINT uiFamilyCodePage; WCHAR
 *     wszDescription[MAX_MIMECP_NAME]; WCHAR
 *     wszWebCharset[MAX_MIMECSET_NAME]; WCHAR
 *     wszHeaderCharset[MAX_MIMECSET_NAME]; WCHAR
 *     wszBodyCharset[MAX_MIMECSET_NAME]; WCHAR
 *     wszFixedWidthFont[MAX_MIMEFACE_NAME]; WCHAR
 *     wszProportionalFont[MAX_MIMEFACE_NAME]; BYTE bGDICharset; }
 *     MIMECPINFO;
 *   ms918821 MIMECSETINFO: typedef struct tagMIMECSETINFO { UINT
 *     uiCodePage; UINT uiInternetEncoding; WCHAR
 *     wszCharset[MAX_MIMECSET_NAME]; } MIMECSETINFO, *PMIMECSETINFO;
 *   ms918852 RFC1766INFO: typedef struct tagRFC1766INFO { LCID lcid;
 *     WCHAR wszRfc1766[MAX_RFC1766_NAME]; WCHAR
 *     wszLocaleName[MAX_LOCALE_NAME]; } RFC1766INFO, *PRFC1766INFO;
 *   ms918857 SCRIPTINFO (page tag prints "tagSCRIPINFO"): typedef
 *     struct tagSCRIPINFO { SCRIPT_ID ScriptId; UINT uiCodePage;
 *     WCHAR wszDescription[MAX_SCRIPT_NAME]; WCHAR
 *     wszFixedWidthFont[MAX_MIMEFACE_NAME]; WCHAR
 *     wszProportionalFont[MAX_MIMEFACE_NAME]; } SCRIPTINFO,
 *     *PSCRIPTINFO;
 *   aa452373 references SCRIPTFONTINFO* (no page).
 */

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

#ifdef __cplusplus
}
#endif

#endif /* AKARI_MLANG_H */
