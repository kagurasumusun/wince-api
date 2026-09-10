/*
 * Msime.h -- Japanese Pocket IME conversion-service dictionary API.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE pages of
 * the International book (Japanese Pocket IME reference,
 * tools/manifests/intl-book.manifest): CreateIFEDictionaryInstance
 * ms904718 and CreateIImeIPointInstance ms904719 (Link Library rows
 * print the module form "Imejpp.dll"), the IFEDictionary (ms905450),
 * IImeIPoint2 (ms905460) and IImeIPointNotifySink (ms905470)
 * interfaces, the IMESHF/IMEWRD/POSTBL/IPCANDIDATE structure pages and
 * the IPCTRL_* control-identifier pages.  Interface/method pages
 * print "Link Library: Uuid.lib" (GUID linkage -- no def; the M44
 * objbase interface-record policy).  See docs/inventory.md M84.
 *
 * The CE Pocket IME interfaces are C++ COM: no page publishes a vtable
 * layout, so -- following the M44/M69/M80 interface-record policy --
 * each interface is carried as an opaque forward declaration plus
 * verbatim method-signature records.
 */

#ifndef AKARI_MSIME_H
#define AKARI_MSIME_H

#include "Windef.h"    /* WORD, DWORD, ULONG, INT, VOID, WCHAR, CHAR */
#include "Objbase.h"   /* REFCLSID */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Structures (full prints).                                           */
/* ------------------------------------------------------------------ */

/* ms905982 "IMESHF": print `typedef struct {WORDcbShf;WORDverDic;
 * CHARszTitle[48];CHARszDescription[256];CHARszCopyright[128];}
 * IMESHF;` (glued tokens split; anonymous struct tag as printed). */
typedef struct {
    WORD cbShf;
    WORD verDic;
    CHAR szTitle[48];
    CHAR szDescription[256];
    CHAR szCopyright[128];
} IMESHF;

/* ms906229 "POSTBL": print `typedef struct _POSTBL {WORDnPos;BYTE*
 * szName;} POSTBL;` (the POS string is Shift-JIS encoded per the
 * page Remarks). */
typedef struct _POSTBL {
    WORD nPos;
    BYTE *szName;
} POSTBL;

/* "IPCANDIDATE": print `typedef struct tagIPCANDIDATE {DWORD dwSize;
 * DWORD dwFlags;INT iSelIndex;INT nCandidate;DWORD
 * dwPrivateDataOffset;DWORD dwPrivateDataSize;DWORD dwOffset[1];}`
 * (flexible tail array as printed). */
typedef struct tagIPCANDIDATE {
    DWORD dwSize;
    DWORD dwFlags;
    INT iSelIndex;
    INT nCandidate;
    DWORD dwPrivateDataOffset;
    DWORD dwPrivateDataSize;
    DWORD dwOffset[1];
} IPCANDIDATE;

/* ms905983 "IMEWRD" -- HELD (verbatim print recorded; the member
 * `IMEUCT uct` names IMEUCT, for which no CE page exists):
 * `typedef struct _IMEWRD {WCHAR* pwchReading;WCHAR* pwchDisplay;
 * Union{ULONGulPos;Struct{ WORDnPos1; WORDnPos2;};};ULONG*
 * rgulAttrs[2];INTcbComment;IMEUCTuct;VOID* pvComment;}IMEWRD,
 * *PIMEWRD;` ("Union"/"Struct" keywords are print spellings of
 * union/struct). */

/* ------------------------------------------------------------------ */
/* Interfaces (opaque forwards + method records; no vtable printed).   */
/* ------------------------------------------------------------------ */

typedef struct IFEDictionary IFEDictionary;
typedef struct IImeIPoint2 IImeIPoint2;
typedef struct IImeIPointNotifySink IImeIPointNotifySink;

/* ms905450 "IFEDictionary" (Vtable order: IUnknown then Create, Open,
 * Close, ExistWord, RegisterWord, GetWords, NextWords, GetHeader,
 * GetPosTable -- order recorded on the page table):
 *  - ms905451 Close:           `HRESULT IFEDictionary::Close(void);`
 *  - ms905452 Create:          `HRESULT IFEDictionary::Create(
 *                              CHAR* pchFileName,IMESHF* pShf);`
 *  - ms905453 ExistWord:       `HRESULT::ExistWord(IMEWRD* pWrd);`
 *                              (interface name dropped by the print)
 *  - ms905459 RegisterWord:    `HRESULT::RegisterWord(IMEREG reg,
 *                              IMEWRD* pWrd);` (IMEREG has no page;
 *                              reg values JDIC_REG_HEAD "Registers the
 *                              word" / IFED_REG_DEL "Deletes the word"
 *                              print names without values; return
 *                              IFED_S_WORD_EXISTS prints name only)
 *  - ms905456 GetWords:        `HRESULT IFEDictionary::GetWords(
 *                              WCHAR* pwchFirst,WCHAR* pwchLast,WCHAR*
 *                              pwchDisplay,ULONG ulPos,ULONG ulSelect,
 *                              ULONG ulWordSrc,UCHAR* pchBuffer,ULONG
 *                              cbBuffer,ULONG* pcWrd);`
 *  - ms905457 NextWords:       `HRESULT IFEDictionary::NextWords(
 *                              UCHAR* pchBuffer,ULONG cbBuffer,ULONG*
 *                              pcWrd);`
 *  - ms905454 GetHeader:       `HRESULT IFEDictionary::GetHeader(
 *                              CHAR* pchFileName,IMESHF* pShf,IMEFMT*
 *                              pjfmt,ULONG* pdicat);` (IMEFMT has no
 *                              CE page)
 *  - ms905455 GetPosTable:     `HRESULT IFEDictionary::GetPosTable(
 *                              POSTBL** prgPosTbl,int* pcPosTbl);` */

/* ms905460 "IImeIPoint2" (Vtable order: IUnknown then the methods
 * below as listed on the page table):
 *  - ms905464 Initialize:      `STDMETHOD UpdateContext(VOID*
 *                              pCallBack);` (the prototype line
 *                              misprints the sibling method name; the
 *                              page body describes Initialize and its
 *                              pCallBack = IImeIPointNotifySink
 *                              instance)
 *  - ms905469 UpdateContext:   `UpdateContext(BOOLfGenerateMessage);`
 *  - ms905462 ControlIME:      `STDMETHODControlIME(DWORDdwIMEFuncID,
 *                              LPARAMlparam);` (dwIMEFuncID takes the
 *                              IPCTRL_* identifiers below)
 *  - ms905465 DeleteCompString: `STDMETHOD DeleteCompString(INTiPos,
 *                              INTcchSzDel);`
 *  - ms905463 GetAllCompositionInfo: `STDMETHODGetAllCompositionInfo(
 *                              WCHAR** ppwSzCompStr,DWORD** ppdwCharID,
 *                              INT*pcchCompStr,INT*piIPPos,INT*
 *                              piStartUndetStrPos,INT* pcchUndetStr,
 *                              INT* piEditStart,INT*piEditLen);`
 *  - ms905466 InsertImeItem:  `STDMETHOD InsertImeItem(IPCANDIDATE*
 *                              pImeItem,INTiPos,DWORD*lpdwCharId);`
 *  - ms905467 InsertStringEx: `STDMETHOD InsertStringEx(WCHAR*
 *                              pwSzInsert,INTcchSzInsert,DWORD*
 *                              lpdwCharId);`
 *  - ms905468 ReplaceCompString: `STDMETHOD ReplaceCompString(INTiPos,
 *                              INTiTargetLen,WCHAR*pwSzInsert,INT
 *                              cchSzInsert,DWORD*lpdwCharId);`
 *  - ms905461 SelectIpCandidate: `STDMETHODSelectIpCandidate(DWORD
 *                              dwCharId,INT iselno);` */

/* ms905470 "IImeIPointNotifySink" (callback interface implemented by
 * the IME UI; Vtable order: IUnknown then the methods below):
 *  - ms905472 GenerateMessage:  `HRESULT GenerateMessage(void);`
 *  - ms905474 IsReadingHalfKana: `HRESULT IsReadingHalfKana(void);`
 *  - ms905477 SetCandidateSelection: `HRESULT SetCandidateSelection(
 *                              UINT iciCandidate);`
 *  - ms905478 SetCandidateStr:  `HRESULT SetCandidateStr(UINT
 *                              ciCandidate,WCHAR* pwsz,UINT cbData);`
 *  - ms905479 SetCompositionAttr: `HRESULT SetCompositionAttr(UINT
 *                              ciAtr,BYTE* pb);`
 *  - ms905480 SetCompositionClause: `HRESULT SetCompositionClause(
 *                              UINTciCls,DWORD* pdw);`
 *  - ms905481 SetCompositionReadAttr: `HRESULT SetCompositionReadAttr(
 *                              UINTciAtr,BYTE* pb);`
 *  - ms905482 SetCompositionReadClause: `HRESULT
 *                              SetCompositionReadClause(UINTciCls,
 *                              DWORD* pdw);`
 *  - ms905483 SetCompositionReadStr: `HRESULT SetCompositionReadStr(
 *                              UINTcwch,WCHAR* pwsz);`
 *  - ms905484 SetCompositionStr: `HRESULT SetCompositionStr(UINTcwch,
 *                              WCHAR* pwsz);`
 *  - ms905485 SetCursorPos:    `HRESULT SetCursorPos(UINT
 *                              uiCursorPos);`
 *  - ms905486 SetDeltaPos:     `HRESULT SetDeltaPos(UINTiDelta);`
 *  - ms905488 SetResultClause: `HRESULT SetResultClause(UINT ciCls,
 *                              DWORD* pdw);`
 *  - ms905489 SetResultReadClause: `HRESULT SetResultReadClause(UINT
 *                              ciCls,DWORD* pdw);`
 *  - ms905490 SetResultReadStr: `HRESULT SetResultReadStr(UINT cwch,
 *                              WCHAR* pwsz);`
 *  - ms905491 SetResultStr:    `HRESULT SetResultStr(UINT cwch,WCHAR*
 *                              pwsz);`
 *  - ms905487 SetTargetClause: `HRESULT SetResultReadClause(UINT
 *                              uiTarget);` (prototype line copy error;
 *                              page body describes SetTargetClause) */

/* ------------------------------------------------------------------ */
/* IPCTRL_* control identifiers for IImeIPoint2::ControlIME -- the
 * pages print semantics but NO numeric values, so the names are
 * recorded only (the WM_SIDESHOW_* M82 precedent):
 *   IPCTRL_CARETBACKSPACE  IPCTRL_CARETBOTTOM   IPCTRL_CARETDELETE
 *   IPCTRL_CARETLEFT       IPCTRL_CARETRIGHT    IPCTRL_CARETSET
 *   IPCTRL_CARETTOP        IPCTRL_CLEARALL      IPCTRL_CONVERTALL
 *   IPCTRL_DETERMINALL     IPCTRL_GETCONVERSIONMODE
 *   IPCTRL_GETERROR        IPCTRL_INSERTFULLSPACE
 *   IPCTRL_INSERTHALFSPACE IPCTRL_INSERTSPACE
 *   IPCTRL_JPN_BUNLENDEC   IPCTRL_JPN_BUNLENINC
 *   IPCTRL_JPN_CRSRLEFT    IPCTRL_JPN_CRSRRIGHT
 *   IPCTRL_JPN_UNDOBUNSETSU IPCTRL_JPN_UNDOCLR
 *   IPCTRL_MAKECANDIDATE   IPCTRL_OFFIME       IPCTRL_ONIME
 *   IPCTRL_PHRASEDELETE    IPCTRL_PRECONVERSION
 *   IPCTRL_RELOADCFG       IPCTRL_SELECTCANDIDATE
 *   IPCTRL_SETCONVERSIONMODE IPCTRL_SETSHIFTSTATE
 * The IPCTRL_CARETLEFT page additionally references IPCTRLPARAM_DEFAULT
 * (parameter default) -- referenced, no page of its own.
 * ------------------------------------------------------------------ */

/* ------------------------------------------------------------------ */
/* Factory functions (Imejpp.dll module-form Library rows).            */
/* ------------------------------------------------------------------ */

/* ms904718 "CreateIFEDictionaryInstance": print
 * `HRESULT CreateIFEDictionaryInstance(VOID** ppvObj);`. */
AKARI_CE_IMPORT HRESULT CreateIFEDictionaryInstance(VOID **ppvObj)
                    AKARI_CE_NAME(CreateIFEDictionaryInstance);

/* ms904719 "CreateIImeIPointInstance": print
 * `HRESULT CreateIImeIPointInstance(REFCLSIDclsid,VOID** ppvObj);`
 * (glued tokens split). */
AKARI_CE_IMPORT HRESULT CreateIImeIPointInstance(REFCLSID clsid,
                    VOID **ppvObj) AKARI_CE_NAME(CreateIImeIPointInstance);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_MSIME_H */
