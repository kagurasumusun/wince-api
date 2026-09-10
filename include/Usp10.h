/* Usp10.h -- Uniscribe complex-script shaping API (Uspce.lib).
 *
 * Source pages: the Fonts book Uniscribe reference rows printing
 * "Header: Usp10.h" (45 pages: 31 Script* function pages, Link
 * Library: Uspce.lib -> def/uspce-doc.def, and the 14 data-type
 * pages whose prints are compiled below; SCRIPT_CACHE and
 * SCRIPT_STRING_ANALYSIS print as void* handles).
 *
 * Print repairs (each noted at its site): ScriptApplyLogicalWidth
 * prints the return type "HESULT"; ScriptApplyLogicalWidth,
 * ScriptGetGlyphABCWidth and ScriptGetLogicalWidths end their
 * parameter lists with a stray comma.
 * See docs/inventory.md M83.
 */

#ifndef AKARI_USP10_H
#define AKARI_USP10_H

#include "Windef.h"    /* WORD, DWORD, BYTE, BOOL, UINT, WCHAR, LCID,
 * HDC, RECT, SIZE, LONG */
#include "Wingdi.h"   /* ABC (ms862... Wingdi.h home) */
#include "Objbase.h"  /* HRESULT */

/* --- Data types (printed on their own pages). ------------------ */
/* GOFFSET (page ms905336): print
 * `typedef struct tagGOFFSET { LONG du; LONG dv;} GOFFSET;` */
typedef struct tagGOFFSET {
    LONG du;
    LONG dv;
} GOFFSET;

/* SCRIPT_STATE (page ms906273): print (WORD members as
 * printed -- the WORD-typed f* members are one-bit fields per the
 * page tables; reproduced verbatim). */
typedef struct tag_SCRIPT_STATE {
    WORD uBidiLevel;
    WORD fOverrideDirection;
    WORD fInhibitSymSwap;
    WORD fCharShape;
    WORD fDigitSubstitute;
    WORD fInhibitLigate;
    WORD fDisplayZWG;
    WORD fArabicNumContext;
    WORD fGcpClusters;
    WORD fReserved;
    WORD fEngineReserved;
} SCRIPT_STATE;

/* SCRIPT_ANALYSIS (page ms906264): print. */
typedef struct tag_SCRIPT_ANALYSIS {
    WORD         eScript;
    WORD         fRTL;
    WORD         fLayoutRTL;
    WORD         fLinkBefore;
    WORD         fLinkAfter;
    WORD         fLogicalOrder;
    WORD         fNoGlyphIndex;
    SCRIPT_STATE s;
} SCRIPT_ANALYSIS;

/* SCRIPT_CONTROL (page ms906266): print. */
typedef struct tag_SCRIPT_CONTROL {
    DWORD uDefaultLanguage;
    DWORD fContextDigits;
    DWORD fInvertPreBoundDir;
    DWORD fInvertPostBoundDir;
    DWORD fLinkStringBefore;
    DWORD fLinkStringAfter;
    DWORD fNeutralOverride;
    DWORD fNumericOverride;
    DWORD fLegacyBidiClass;
    DWORD fReserved;
} SCRIPT_CONTROL;

/* SCRIPT_DIGITSUBSTITUTE (page ms906267): print. */
typedef struct tag_SCRIPT_DIGITSUBSTITUTE {
    DWORD NationalDigitLanguage;
    DWORD TraditionalDigitLanguage;
    DWORD DigitSubstitute;
    DWORD dwReserved;
} SCRIPT_DIGITSUBSTITUTE;

/* SCRIPT_FONTPROPERTIES (page ms906268): print (anonymous tag). */
typedef struct tag_SCRIPT_FONTPROPERTIES {
    int  cBytes;
    WORD wgBlank;
    WORD wgDefault;
    WORD wgInvalid;
    WORD wgKashida;
    int  iKashidaWidth;
} SCRIPT_FONTPROPERTIES;

/* SCRIPT_ITEM (page ms906269): print. */
typedef struct tag_SCRIPT_ITEM {
    int             iCharPos;
    SCRIPT_ANALYSIS a;
} SCRIPT_ITEM;

/* SCRIPT_JUSTIFY (page ms906270): print `typedef enum tag_SCRIPT_JUSTIFY {
 * SCRIPT_JUSTIFY_NONE = 0, ... }` (values as printed). */
typedef enum tag_SCRIPT_JUSTIFY {
    SCRIPT_JUSTIFY_NONE = 0,
    SCRIPT_JUSTIFY_ARABIC_BLANK = 1,
    SCRIPT_JUSTIFY_CHARACTER = 2,
    SCRIPT_JUSTIFY_RESERVED1 = 3,
    SCRIPT_JUSTIFY_BLANK = 4,
    SCRIPT_JUSTIFY_RESERVED2 = 5,
    SCRIPT_JUSTIFY_RESERVED3 = 6,
    SCRIPT_JUSTIFY_ARABIC_NORMAL = 7,
    SCRIPT_JUSTIFY_ARABIC_KASHIDA = 8,
    SCRIPT_JUSTIFY_ARABIC_ALEF = 9,
    SCRIPT_JUSTIFY_ARABIC_HA = 10,
    SCRIPT_JUSTIFY_ARABIC_RA = 11,
    SCRIPT_JUSTIFY_ARABIC_BA = 12,
    SCRIPT_JUSTIFY_ARABIC_BARA = 13,
    SCRIPT_JUSTIFY_ARABIC_SEEN = 14,
    SCRIPT_JUSTIFY_ARABIC_SEEN_M = 15
} SCRIPT_JUSTIFY;

/* SCRIPT_LOGATTR (page ms906271): print. */
typedef struct tag_SCRIPT_LOGATTR {
    BYTE fSoftBreak;
    BYTE fWhiteSpace;
    BYTE fCharStop;
    BYTE fWordStop;
    BYTE fInvalid;
    BYTE fReserved;
} SCRIPT_LOGATTR;

/* SCRIPT_PROPERTIES (page ms906272): print (anonymous tag). */
typedef struct tag_SCRIPT_PROPERTIES {
    DWORD langid;
    DWORD fNumeric;
    DWORD fComplex;
    DWORD fNeedsWordBreaking;
    DWORD fNeedsCaretInfo;
    DWORD bCharSet;
    DWORD fControl;
    DWORD fPrivateUseArea;
    DWORD fNeedsCharacterJustify;
    DWORD fInvalidGlyph;
    DWORD fInvalidLogAttr;
    DWORD fCDM;
    DWORD fAmbiguousCharSet;
    DWORD fClusterSizeVaries;
    DWORD fRejectInvalid;
} SCRIPT_PROPERTIES;

/* SCRIPT_CACHE (page ms906265): print `typedef void *SCRIPT_CACHE;` */
typedef void *SCRIPT_CACHE;

/* SCRIPT_STRING_ANALYSIS (page ms906274): print
 * `typedef void *SCRIPT_STRING_ANALYSIS;` */
typedef void *SCRIPT_STRING_ANALYSIS;

/* SCRIPT_TABDEF (page ms906275): print. */
typedef struct tag_SCRIPT_TABDEF {
    int  cTabStops;
    int  iScale;
    int *pTabStops;
    int  iTabOrigin;
} SCRIPT_TABDEF;

/* SCRIPT_VISATTR (page ms906276): print. */
typedef struct tag_SCRIPT_VISATTR {
    WORD uJustification;
    WORD fClusterStart;
    WORD fDiacritic;
    WORD fZeroWidth;
    WORD fReserved;
    WORD fShapeReserved;
} SCRIPT_VISATTR;

/* --- Functions (Uspce.lib). ------------------------------------- */
/* ms906233 "ScriptApplyDigitSubstitution": print `HRESULT WINAPI ScriptApplyDigitSubstitution( const SCRIPT_DIGITSUBSTITUTE* psds, SCRIPT_CONTROL* psc, SCRIPT_STATE* pss)` */
AKARI_CE_IMPORT HRESULT WINAPI ScriptApplyDigitSubstitution(SCRIPT_DIGITSUBSTITUTE* psds, SCRIPT_CONTROL* psc, SCRIPT_STATE* pss)
                    AKARI_CE_NAME(ScriptApplyDigitSubstitution);

/* ms906234 "ScriptApplyLogicalWidth": print `HESULT WINAPI ScriptApplyLogicalWidth( const int* piDx, int cChars, int cGlyphs, const WORD* pwLogClust, const SCRIPT_VISATTR* psva, const int* piAdvance, const SCRIPT_ANALYSIS* psa, ABC* pABC, int* piJustify,)` (print repairs: return type "HESULT" -> HRESULT; stray trailing comma dropped) */
AKARI_CE_IMPORT HRESULT WINAPI ScriptApplyLogicalWidth(int* piDx, int cChars, int cGlyphs, WORD* pwLogClust, SCRIPT_VISATTR* psva, int* piAdvance, SCRIPT_ANALYSIS* psa, ABC* pABC, int* piJustify)
                    AKARI_CE_NAME(ScriptApplyLogicalWidth);

/* ms906235 "ScriptBreak": print `HRESULT WINAPI ScriptBreak( const WCHAR* pwcChars, int cChars, const SCRIPT_ANALYSIS* psa, SCRIPT_LOGATTR* psla)` */
AKARI_CE_IMPORT HRESULT WINAPI ScriptBreak(WCHAR* pwcChars, int cChars, SCRIPT_ANALYSIS* psa, SCRIPT_LOGATTR* psla)
                    AKARI_CE_NAME(ScriptBreak);

/* ms906237 "ScriptCPtoX": print `HRESULT WINAPI ScriptCPtoX( int iCP, BOOL fTrailing, int cChars, int cGlyphs, const WORD* pwLogClust, const SCRIPT_VISATTR* psva, const int* piAdvance, const SCRIPT_ANALYSIS* psa, int* piX)` */
AKARI_CE_IMPORT HRESULT WINAPI ScriptCPtoX(int iCP, BOOL fTrailing, int cChars, int cGlyphs, WORD* pwLogClust, SCRIPT_VISATTR* psva, int* piAdvance, SCRIPT_ANALYSIS* psa, int* piX)
                    AKARI_CE_NAME(ScriptCPtoX);

/* ms906236 "ScriptCacheGetHeight": print `HRESULT WINAPI ScriptCacheGetHeight( HDC hdc, SCRIPT_CACHE* psc, long* tmHeight)` */
AKARI_CE_IMPORT HRESULT WINAPI ScriptCacheGetHeight(HDC hdc, SCRIPT_CACHE* psc, long* tmHeight)
                    AKARI_CE_NAME(ScriptCacheGetHeight);

/* ms906238 "ScriptFreeCache": print `HRESULT WINAPI ScriptFreeCache( SCRIPT_CACHE *psc)` */
AKARI_CE_IMPORT HRESULT WINAPI ScriptFreeCache(SCRIPT_CACHE* psc)
                    AKARI_CE_NAME(ScriptFreeCache);

/* ms906239 "ScriptGetCMap": print `HRESULT WINAPI ScriptGetCMap( HDC hdc, SCRIPT_CACHE *psc, const WCHAR *pwcInChars, int cChars, DWORD dwFlags, WORD *pwOutGlyphs)` */
AKARI_CE_IMPORT HRESULT WINAPI ScriptGetCMap(HDC hdc, SCRIPT_CACHE* psc, WCHAR* pwcInChars, int cChars, DWORD dwFlags, WORD* pwOutGlyphs)
                    AKARI_CE_NAME(ScriptGetCMap);

/* ms906240 "ScriptGetFontProperties": print `HRESULT WINAPI ScriptGetFontProperties( HDC hdc, SCRIPT_CACHE* psc, SCRIPT_FONTPROPERTIES* sfp)` */
AKARI_CE_IMPORT HRESULT WINAPI ScriptGetFontProperties(HDC hdc, SCRIPT_CACHE* psc, SCRIPT_FONTPROPERTIES* sfp)
                    AKARI_CE_NAME(ScriptGetFontProperties);

/* ms906241 "ScriptGetGlyphABCWidth": print `HRESULT WINAPI ScriptGetGlyphABCWidth( HDC hdc, SCRIPT_CACHE* psc, WORD wGlyph, ABC* pABC,)` (print repairs: stray trailing comma dropped) */
AKARI_CE_IMPORT HRESULT WINAPI ScriptGetGlyphABCWidth(HDC hdc, SCRIPT_CACHE* psc, WORD wGlyph, ABC* pABC)
                    AKARI_CE_NAME(ScriptGetGlyphABCWidth);

/* ms906242 "ScriptGetLogicalWidths": print `HRESULT WINAPI ScriptGetLogicalWidths( const SCRIPT_ANALYSIS *psa, int cChars, int cGlyphs, const int* piGlyphWidth, const WORD* pwLogClust, const SCRIPT_VISATTR* psva, int* piDx,)` (print repairs: stray trailing comma dropped) */
AKARI_CE_IMPORT HRESULT WINAPI ScriptGetLogicalWidths(SCRIPT_ANALYSIS* psa, int cChars, int cGlyphs, int* piGlyphWidth, WORD* pwLogClust, SCRIPT_VISATTR* psva, int* piDx)
                    AKARI_CE_NAME(ScriptGetLogicalWidths);

/* ms906243 "ScriptGetProperties": print `HRESULT WINAPI ScriptGetProperties( const SCRIPT_PROPERTIES*** ppSp, int* piNumScripts)` */
AKARI_CE_IMPORT HRESULT WINAPI ScriptGetProperties(SCRIPT_PROPERTIES*** ppSp, int* piNumScripts)
                    AKARI_CE_NAME(ScriptGetProperties);

/* ms906244 "ScriptIsComplex": print `HRESULT WINAPI ScriptIsComplex( const WCHAR* pwcInChars, int cInChars, DWORD dwFlags)` */
AKARI_CE_IMPORT HRESULT WINAPI ScriptIsComplex(WCHAR* pwcInChars, int cInChars, DWORD dwFlags)
                    AKARI_CE_NAME(ScriptIsComplex);

/* ms906245 "ScriptItemize": print `HRESULT WINAPI ScriptItemize( const WCHAR* pwcInChars, int cInChars, int cMaxItems, const SCRIPT_CONTROL* psControl, const SCRIPT_STATE* psState, SCRIPT_ITEM* pItems, int* pcItems)` */
AKARI_CE_IMPORT HRESULT WINAPI ScriptItemize(WCHAR* pwcInChars, int cInChars, int cMaxItems, SCRIPT_CONTROL* psControl, SCRIPT_STATE* psState, SCRIPT_ITEM* pItems, int* pcItems)
                    AKARI_CE_NAME(ScriptItemize);

/* ms906246 "ScriptJustify": print `HRESULT WINAPI ScriptJustify( const SCRIPT_VISATTR* psva, const int* piAdvance, int cGlyphs, int iDx, int iMinKashida, int* piJustify)` */
AKARI_CE_IMPORT HRESULT WINAPI ScriptJustify(SCRIPT_VISATTR* psva, int* piAdvance, int cGlyphs, int iDx, int iMinKashida, int* piJustify)
                    AKARI_CE_NAME(ScriptJustify);

/* ms906247 "ScriptLayout": print `HRESULT WINAPI ScriptLayout( int cRuns, const BYTE* pbLevel, int* piVisualToLogical, int* piLogicalToVisual)` */
AKARI_CE_IMPORT HRESULT WINAPI ScriptLayout(int cRuns, BYTE* pbLevel, int* piVisualToLogical, int* piLogicalToVisual)
                    AKARI_CE_NAME(ScriptLayout);

/* ms906248 "ScriptPlace": print `HRESULT WINAPI ScriptPlace( HDC hdc, SCRIPT_CACHE* psc, const WORD* pwGlyphs, int cGlyphs, const SCRIPT_VISATTR* psva, SCRIPT_ANALYSIS* psa, int* piAdvance, GOFFSET* pGoffset, ABC* pABC)` */
AKARI_CE_IMPORT HRESULT WINAPI ScriptPlace(HDC hdc, SCRIPT_CACHE* psc, WORD* pwGlyphs, int cGlyphs, SCRIPT_VISATTR* psva, SCRIPT_ANALYSIS* psa, int* piAdvance, GOFFSET* pGoffset, ABC* pABC)
                    AKARI_CE_NAME(ScriptPlace);

/* ms906249 "ScriptRecordDigitSubstitution": print `HRESULT WINAPI ScriptRecordDigitSubstitution( LCID Locale, SCRIPT_DIGITSUBSTITUTE* psds)` */
AKARI_CE_IMPORT HRESULT WINAPI ScriptRecordDigitSubstitution(LCID Locale, SCRIPT_DIGITSUBSTITUTE* psds)
                    AKARI_CE_NAME(ScriptRecordDigitSubstitution);

/* ms906250 "ScriptShape": print `HRESULT WINAPI ScriptShape( HDC hdc, SCRIPT_CACHE* psc, const WCHAR* pwcChars, int cChars, int cMaxGlyphs, SCRIPT_ANALYSIS* psa, WORD* pwOutGlyphs, WORD* pwLogClust, SCRIPT_VISATTR* psva, int* pcGlyphs)` */
AKARI_CE_IMPORT HRESULT WINAPI ScriptShape(HDC hdc, SCRIPT_CACHE* psc, WCHAR* pwcChars, int cChars, int cMaxGlyphs, SCRIPT_ANALYSIS* psa, WORD* pwOutGlyphs, WORD* pwLogClust, SCRIPT_VISATTR* psva, int* pcGlyphs)
                    AKARI_CE_NAME(ScriptShape);

/* ms906251 "ScriptStringAnalyse": print `HRESULT WINAPI ScriptStringAnalyse( HDC hdc, const void* pString, int cString, int cGlyphs, int iCharset, DWORD dwFlags, int iReqWidth, SCRIPT_CONTROL* psControl, SCRIPT_STATE* psState, const int* piDx, SCRIPT_TABDEF* pTabdef, const BYTE* pbInClass, SCRIPT_STRING_ANALYSIS* pssa)` */
AKARI_CE_IMPORT HRESULT WINAPI ScriptStringAnalyse(HDC hdc, void* pString, int cString, int cGlyphs, int iCharset, DWORD dwFlags, int iReqWidth, SCRIPT_CONTROL* psControl, SCRIPT_STATE* psState, int* piDx, SCRIPT_TABDEF* pTabdef, BYTE* pbInClass, SCRIPT_STRING_ANALYSIS* pssa)
                    AKARI_CE_NAME(ScriptStringAnalyse);

/* ms906252 "ScriptStringCPtoX": print `HRESULT WINAPI ScriptStringCPtoX( SCRIPT_STRING_ANALYSIS ssa, int icp, BOOL fTrailing, int* pX)` */
AKARI_CE_IMPORT HRESULT WINAPI ScriptStringCPtoX(SCRIPT_STRING_ANALYSIS ssa, int icp, BOOL fTrailing, int* pX)
                    AKARI_CE_NAME(ScriptStringCPtoX);

/* ms906253 "ScriptStringFree": print `HRESULT WINAPI ScriptStringFree( SCRIPT_STRING_ANALYSIS* pssa)` */
AKARI_CE_IMPORT HRESULT WINAPI ScriptStringFree(SCRIPT_STRING_ANALYSIS* pssa)
                    AKARI_CE_NAME(ScriptStringFree);

/* ms906254 "ScriptStringGetLogicalWidths": print `HRESULT WINAPI ScriptStringGetLogicalWidths( SCRIPT_STRING_ANALYSIS ssa, int* piDx)` */
AKARI_CE_IMPORT HRESULT WINAPI ScriptStringGetLogicalWidths(SCRIPT_STRING_ANALYSIS ssa, int* piDx)
                    AKARI_CE_NAME(ScriptStringGetLogicalWidths);

/* ms906255 "ScriptStringGetOrder": print `HRESULT WINAPI ScriptStringGetOrder( SCRIPT_STRING_ANALYSIS ssa, UINT *puOrder)` */
AKARI_CE_IMPORT HRESULT WINAPI ScriptStringGetOrder(SCRIPT_STRING_ANALYSIS ssa, UINT* puOrder)
                    AKARI_CE_NAME(ScriptStringGetOrder);

/* ms906256 "ScriptStringOut": print `HRESULT WINAPI ScriptStringOut( SCRIPT_STRING_ANALYSIS ssa, int iX, int iY, UINT uOptions, const RECT* prc, int iMinSel, int iMaxSel, BOOL fDisabled)` */
AKARI_CE_IMPORT HRESULT WINAPI ScriptStringOut(SCRIPT_STRING_ANALYSIS ssa, int iX, int iY, UINT uOptions, RECT* prc, int iMinSel, int iMaxSel, BOOL fDisabled)
                    AKARI_CE_NAME(ScriptStringOut);

/* ms906257 "ScriptStringValidate": print `HRESULT WINAPI ScriptStringValidate( SCRIPT_STRING_ANALYSIS ssa)` */
AKARI_CE_IMPORT HRESULT WINAPI ScriptStringValidate(SCRIPT_STRING_ANALYSIS ssa)
                    AKARI_CE_NAME(ScriptStringValidate);

/* ms906258 "ScriptStringXtoCP": print `HRESULT WINAPI ScriptStringXtoCP( SCRIPT_STRING_ANALYSIS ssa, int iX, int* piCh, int* piTrailing)` */
AKARI_CE_IMPORT HRESULT WINAPI ScriptStringXtoCP(SCRIPT_STRING_ANALYSIS ssa, int iX, int* piCh, int* piTrailing)
                    AKARI_CE_NAME(ScriptStringXtoCP);

/* ms906260 "ScriptString_pLogAttr": print `const SCRIPT_LOGATTR* WINAPI ScriptString_pLogAttr( SCRIPT_STRING_ANALYSIS ssa)` */
AKARI_CE_IMPORT const SCRIPT_LOGATTR* WINAPI ScriptString_pLogAttr(SCRIPT_STRING_ANALYSIS ssa)
                    AKARI_CE_NAME(ScriptString_pLogAttr);

/* ms906261 "ScriptString_pSize": print `const SIZE* WINAPI ScriptString_pSize( SCRIPT_STRING_ANALYSIS ssa)` */
AKARI_CE_IMPORT const SIZE* WINAPI ScriptString_pSize(SCRIPT_STRING_ANALYSIS ssa)
                    AKARI_CE_NAME(ScriptString_pSize);

/* ms906259 "ScriptString_pcOutChars": print `const int* WINAPI ScriptString_pcOutChars( SCRIPT_STRING_ANALYSIS ssa)` */
AKARI_CE_IMPORT const int* WINAPI ScriptString_pcOutChars(SCRIPT_STRING_ANALYSIS ssa)
                    AKARI_CE_NAME(ScriptString_pcOutChars);

/* ms906262 "ScriptTextOut": print `HRESULT WINAPI ScriptTextOut( const HDC hdc, SCRIPT_CACHE* psc, int x, int y, UINT fuOptions, const RECT* lprc, const SCRIPT_ANALYSIS* psa, const WCHAR* pwcReserved, int iReserved, const WORD* pwGlyphs, int cGlyphs, const int* piAdvance, const int* piJustify, const GOFFSET* pGoffset)` */
AKARI_CE_IMPORT HRESULT WINAPI ScriptTextOut(HDC hdc, SCRIPT_CACHE* psc, int x, int y, UINT fuOptions, RECT* lprc, SCRIPT_ANALYSIS* psa, WCHAR* pwcReserved, int iReserved, WORD* pwGlyphs, int cGlyphs, int* piAdvance, int* piJustify, GOFFSET* pGoffset)
                    AKARI_CE_NAME(ScriptTextOut);

/* ms906263 "ScriptXtoCP": print `HRESULT WINAPI ScriptXtoCP( int iX, int cChars, int cGlyphs, const WORD* pwLogClust, const SCRIPT_VISATTR* psva, const int* piAdvance, const SCRIPT_ANALYSIS* psa, int* piCP, int* piTrailing)` */
AKARI_CE_IMPORT HRESULT WINAPI ScriptXtoCP(int iX, int cChars, int cGlyphs, WORD* pwLogClust, SCRIPT_VISATTR* psva, int* piAdvance, SCRIPT_ANALYSIS* psa, int* piCP, int* piTrailing)
                    AKARI_CE_NAME(ScriptXtoCP);

#endif /* AKARI_USP10_H */
