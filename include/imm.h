/* imm.h -- Input Method Manager (IMM) API for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Evidence model (clean room; same as winsock2.h / tapi.h):
 *
 *  (a) every prototype and structure below is transcribed from the
 *      official CE 5.0 "Input Method Manager" reference pages
 *      (learn.microsoft.com previous-versions/windows/embedded,
 *      (v=msdn.10)): the 55 Coreimm.lib function pages ms905984..
 *      ms906041 (Requirements rows Header: Imm.h, Link Library:
 *      Coreimm.lib, Windows CE .NET 4.0 and later), the twelve TAPI-
 *      free structure pages (CANDIDATEFORM ms904636 ... STYLEBUF
 *      ms906434) and the EnumRegisterWordProc callback page
 *      ms904955.  Per-page records are in docs/inventory.md (M46).
 *
 *  (b) the CE 5.0 archive strips whitespace inside code blocks; the
 *      type/name boundaries were restored mechanically against the
 *      documented types of this header (the documented restoration
 *      model of the M43/M45 TAPI batches).
 *
 *  (c) documented print artifacts fixed (each noted at the site):
 *      ImmAssociateContextEx prints the second parameter type "HINC"
 *      -- the page's own parameter text says "Handle to the input
 *      method context", so the type is HIMC; ImmRegisterWord prints
 *      "LPCTSR lpszReading" -- LPCTSTR.
 *
 *  (d) three structures cannot be completed from official
 *      information, so only their pointer aliases are declared
 *      (opaque tag -- the LINEFORWARDLIST precedent, tapi.h note
 *      (e)):
 *        INPUTCONTEXT     (ms906185: the documented lfFont union
 *                         needs the LOGFONTA layout; the official CE
 *                         trees document LOGFONT only, CE being
 *                         Unicode-only)
 *        IMEMENUITEMINFO  (ms905980: szString[IMEMENUITEM_STRING_SIZE]
 *                         -- no CE tree publishes the constant value)
 *        IMECHARPOSITION  (ms905972: the cLineHeight member is typed
 *                         UNIT; no CE tree publishes the width of
 *                         UNIT)
 *
 *  (e) recorded-not-defined: the 83 IMM constant pages (IME_CMODE_*,
 *      GCS_*, IME_CHOTKEY_*, IME_SMODE_*, IME_ESC_*, IMC_*, IMN_*,
 *      IMR_*, IPCTRL_*, WM_IME_*) publish names without numeric
 *      values in both the CE 5.0 and the CE 6.0 archive trees --
 *      same policy as the held Winsock constant sets (M39-M41).
 *
 *  (f) ImmGetConversionStatusForeground (ms906006) is recorded, not
 *      declared: its Requirements rows read Header: Pwinuser.h and
 *      "Linked during platform build" (a Platform Builder row, not a
 *      user-mode link library).
 */

#ifndef _IMM_H
#define _IMM_H

#include "windef.h"   /* DWORD, BOOL, UINT, WORD, CHAR, WCHAR, HWND, HKL,
                         HANDLE, POINT/LPPOINT, RECT, LPVOID, LPCVOID,
                         LPDWORD, LPCTSTR, LPTSTR, WPARAM, LPARAM,
                         LRESULT, CALLBACK, LPHKL, LPUINT */
#include "wingdi.h"   /* LOGFONT / LPLOGFONT (ImmGet/SetCompositionFont) */

/* ------------------------------------------------------------------ */
/* IMM handles                                                         */
/* ------------------------------------------------------------------ */

/* HIMC: "Handle to the input method context." (parameter text of the
 * ImmGetContext / ImmAssociateContextEx pages, ms906003 / ms905985);
 * ImmGetContext returns it.  No carrier type is published -> HANDLE,
 * the documented design decision used for every CE opaque handle. */
typedef HANDLE HIMC;

/* HIMCC: returned by ImmCreateIMCC / ImmReSizeIMCC and taken by the
 * IMCC lock/size functions (pages ms905988 / ms906028); the handle
 * of an input-method-context component memory block.  HANDLE carrier
 * (no published carrier type). */
typedef HANDLE HIMCC;

/* ------------------------------------------------------------------ */
/* IMM structures (the twelve CE structure pages)                      */
/* ------------------------------------------------------------------ */

/* CANDIDATEFORM page (ms904636). */
typedef struct _CANDIDATEFORM {
    DWORD  dwIndex;
    DWORD  dwStyle;
    POINT  ptCurrentPos;
    RECT   rcArea;
} CANDIDATEFORM;
typedef CANDIDATEFORM *LPCANDIDATEFORM;   /* ImmGet/SetCandidateWindow */

/* CANDIDATEINFO page (ms904637). */
typedef struct tagCANDIDATEINFO {
    DWORD  dwSize;
    DWORD  dwCount;
    DWORD  dwOffset[32];
    DWORD  dwPrivateSize;
    DWORD  dwPrivateOffset;
} CANDIDATEINFO;

/* CANDIDATELIST page (ms904638); dwOffset[] is printed as an
 * open-ended array -- a C flexible array member. */
typedef struct _CANDIDATELIST {
    DWORD  dwSize;
    DWORD  dwStyle;
    DWORD  dwCount;
    DWORD  dwSelection;
    DWORD  dwPageStart;
    DWORD  dwPageSize;
    DWORD  dwOffset[];
} CANDIDATELIST;
typedef CANDIDATELIST *LPCANDIDATELIST;   /* ImmGetCandidateList / ImmGetConversionList */

/* COMPOSITIONFORM page (ms904714); the archive prints
 * "Typedef struct_tag..." -- casing/spacing restored. */
typedef struct _COMPOSITIONFORM {
    DWORD  dwStyle;
    POINT  ptCurrentPos;
    RECT   rcArea;
} COMPOSITIONFORM;
typedef COMPOSITIONFORM *LPCOMPOSITIONFORM;  /* ImmGet/SetCompositionWindow */

/* COMPOSITIONSTR page (ms904715): 25 documented DWORD members. */
typedef struct tagCOMPOSITIONSTR {
    DWORD  dwSize;
    DWORD  dwCompReadAttrLen;
    DWORD  dwCompReadAttrOffset;
    DWORD  dwCompReadClsLen;
    DWORD  dwCompReadClsOffset;
    DWORD  dwCompReadStrLen;
    DWORD  dwCompReadStrOffset;
    DWORD  dwCompAttrLen;
    DWORD  dwCompAttrOffset;
    DWORD  dwCompClsLen;
    DWORD  dwCompClsOffset;
    DWORD  dwCompStrLen;
    DWORD  dwCompStrOffset;
    DWORD  dwCursorPos;
    DWORD  dwDeltaStart;
    DWORD  dwResultReadClsLen;
    DWORD  dwResultReadClsOffset;
    DWORD  dwResultReadStrLen;
    DWORD  dwResultReadStrOffset;
    DWORD  dwResultClsLen;
    DWORD  dwResultClsOffset;
    DWORD  dwResultStrLen;
    DWORD  dwResultStrOffset;
    DWORD  dwPrivateSize;
    DWORD  dwPrivateOffset;
} COMPOSITIONSTR;

/* GUIDELINE page (ms905340). */
typedef struct tagGUIDELINE {
    DWORD  dwSize;
    DWORD  dwLevel;
    DWORD  dwIndex;
    DWORD  dwStrLen;
    DWORD  dwStrOffset;
    DWORD  dwPrivateSize;
    DWORD  dwPrivateOffset;
} GUIDELINE;

/* RECONVERTSTRING page (ms906231); NEAR/FAR pointer qualifiers
 * dropped (single 32-bit flat CE address model, the M39 decision). */
typedef struct tagRECONVERTSTRING {
    DWORD  dwSize;
    DWORD  dwVersion;
    DWORD  dwStrLen;
    DWORD  dwStrOffset;
    DWORD  dwCompStrLen;
    DWORD  dwCompStrOffset;
    DWORD  dwTargetStrLen;
    DWORD  dwTargetStrOffset;
} RECONVERTSTRING;
typedef RECONVERTSTRING *PRECONVERTSTRING;
typedef RECONVERTSTRING *NPRECONVERTSTRING;
typedef RECONVERTSTRING *LPRECONVERTSTRING;

/* REGISTERWORD page (ms906232); LPCTSTR = wide (CE Unicode-only). */
typedef struct tagREGISTERWORD {
    LPTSTR lpReading;
    LPTSTR lpWord;
} REGISTERWORD;
typedef REGISTERWORD *LPREGISTERWORD;

/* STYLEBUF page (ms906434). */
typedef struct _STYLEBUF {
    DWORD  dwStyle;
    CHAR   szDescription[32];
} STYLEBUF;
typedef STYLEBUF *LPSTYLEBUF;   /* ImmGetRegisterWordStyle */

/* Opaque structure pointers (header note (d)): the layouts are
 * documented but cannot be completed from official information. */
typedef struct INPUTCONTEXT *PINPUTCONTEXT;
typedef struct INPUTCONTEXT *NPINPUTCONTEXT;
typedef struct INPUTCONTEXT *LPINPUTCONTEXT;     /* ImmLockIMC */
typedef struct IMEMENUITEMINFO *PIMEMENUITEMINFO;
typedef struct IMEMENUITEMINFO *NPIMEMENUITEMINFO;
typedef struct IMEMENUITEMINFO *LPIMEMENUITEMINFO; /* ImmGetImeMenuItems */
typedef struct IMECHARPOSITION *PIMECHARPOSITION;  /* IMR_QUERYCHARPOSITION */

/* ------------------------------------------------------------------ */
/* IMM callback (EnumRegisterWordProc page ms904955)                   */
/* ------------------------------------------------------------------ */

/* "This function is an application-defined callback function used
 * with the ImmEnumRegisterWord function."  Printed shape:
 *   UINT CALLBACK EnumRegisterWordProc(LPCTSTR lpszReading,
 *       DWORD dwStyle, LPCTSTR lpszString, LPVOID lpData); */
typedef UINT (CALLBACK *REGISTERWORDENUMPROC)(LPCTSTR lpszReading,
    DWORD dwStyle, LPCTSTR lpszString, LPVOID lpData);

/* ------------------------------------------------------------------ */
/* IMM functions (55; every page Header: Imm.h, Link Library:          */
/* Coreimm.lib, OS: Windows CE .NET 4.0 and later unless noted)        */
/* ------------------------------------------------------------------ */

/* input-context management */

AKARI_CE_IMPORT HIMC ImmGetContext(HWND hWnd)
    AKARI_CE_NAME(ImmGetContext);                       /* ms906003 */
AKARI_CE_IMPORT BOOL ImmReleaseContext(HWND hWnd, HIMC hIMC)
    AKARI_CE_NAME(ImmReleaseContext);                   /* ms906027 */
AKARI_CE_IMPORT HIMC ImmCreateContext(void)
    AKARI_CE_NAME(ImmCreateContext);                    /* ms905987 */
AKARI_CE_IMPORT BOOL ImmDestroyContext(HIMC hIMC)
    AKARI_CE_NAME(ImmDestroyContext);                   /* ms905989 */
AKARI_CE_IMPORT HIMC ImmAssociateContext(HWND hWnd, HIMC hIMC)
    AKARI_CE_NAME(ImmAssociateContext);                 /* ms905984 */
AKARI_CE_IMPORT BOOL ImmAssociateContextEx(HWND hWnd, HIMC hIMC,
    DWORD dwFlags)
    AKARI_CE_NAME(ImmAssociateContextEx);               /* ms905985: the
    archive prints the second parameter type as HINC; the page's own
    parameter text documents an input-method-context handle (HIMC) */
AKARI_CE_IMPORT LPINPUTCONTEXT WINAPI ImmLockIMC(HIMC hIMC)
    AKARI_CE_NAME(ImmLockIMC);                          /* ms906023 */
AKARI_CE_IMPORT BOOL WINAPI ImmUnlockIMC(HIMC hIMC)
    AKARI_CE_NAME(ImmUnlockIMC);                        /* ms906039 */
AKARI_CE_IMPORT DWORD WINAPI ImmGetIMCLockCount(HIMC hIMC)
    AKARI_CE_NAME(ImmGetIMCLockCount);                  /* ms906013 */

/* IMCC (input-method-context component) memory blocks */

AKARI_CE_IMPORT HIMCC WINAPI ImmCreateIMCC(DWORD dwSize)
    AKARI_CE_NAME(ImmCreateIMCC);                       /* ms905988 */
AKARI_CE_IMPORT HIMCC WINAPI ImmDestroyIMCC(HIMCC hIMCC)
    AKARI_CE_NAME(ImmDestroyIMCC);                      /* ms905990 */
AKARI_CE_IMPORT HIMCC WINAPI ImmReSizeIMCC(HIMCC hIMCC, DWORD dwSize)
    AKARI_CE_NAME(ImmReSizeIMCC);                       /* ms906028 */
AKARI_CE_IMPORT LPVOID WINAPI ImmLockIMCC(HIMCC hIMCC)
    AKARI_CE_NAME(ImmLockIMCC);                         /* ms906024 */
AKARI_CE_IMPORT BOOL WINAPI ImmUnlockIMCC(HIMCC hIMCC)
    AKARI_CE_NAME(ImmUnlockIMCC);                       /* ms906040 */
AKARI_CE_IMPORT DWORD WINAPI ImmGetIMCCSize(HIMCC hIMCC)
    AKARI_CE_NAME(ImmGetIMCCSize);                      /* ms906012 */
AKARI_CE_IMPORT DWORD WINAPI ImmGetIMCCLockCount(HIMCC hIMCC)
    AKARI_CE_NAME(ImmGetIMCCLockCount);                 /* ms906011 */

/* candidate list / window */

AKARI_CE_IMPORT DWORD ImmGetCandidateList(HIMC hIMC, DWORD deIndex,
    LPCANDIDATELIST lpCandList, DWORD dwBufLen)
    AKARI_CE_NAME(ImmGetCandidateList);                 /* ms905995 */
AKARI_CE_IMPORT DWORD ImmGetCandidateListCount(HIMC hIMC,
    LPDWORD lpdwListCount)
    AKARI_CE_NAME(ImmGetCandidateListCount);            /* ms905996 */
AKARI_CE_IMPORT BOOL ImmGetCandidateWindow(HIMC hIMC, DWORD dwIndex,
    LPCANDIDATEFORM lpCandidate)
    AKARI_CE_NAME(ImmGetCandidateWindow);               /* ms905997 */
AKARI_CE_IMPORT BOOL ImmSetCandidateWindow(HIMC hIMC,
    LPCANDIDATEFORM lpCandidate)
    AKARI_CE_NAME(ImmSetCandidateWindow);               /* ms906029 */

/* composition string / window / font */

AKARI_CE_IMPORT LONG ImmGetCompositionString(HIMC hIMC, DWORD dwIndex,
    LPVOID lpBuf, DWORD dwBufLen)
    AKARI_CE_NAME(ImmGetCompositionString);             /* ms906001 */
AKARI_CE_IMPORT BOOL ImmSetCompositionString(HIMC hIMC, DWORD dwIndex,
    LPCVOID lpComp, DWORD dwCompLen, LPCVOID lpRead, DWORD dwReadLen)
    AKARI_CE_NAME(ImmSetCompositionString);             /* ms906031 */
AKARI_CE_IMPORT BOOL ImmGetCompositionWindow(HIMC hIMC,
    LPCOMPOSITIONFORM lpCompForm)
    AKARI_CE_NAME(ImmGetCompositionWindow);             /* ms906002 */
AKARI_CE_IMPORT BOOL ImmSetCompositionWindow(HIMC hIMC,
    LPCOMPOSITIONFORM lpCompForm)
    AKARI_CE_NAME(ImmSetCompositionWindow);             /* ms906032 */
AKARI_CE_IMPORT BOOL ImmGetCompositionFont(HIMC hIMC, LPLOGFONT lplf)
    AKARI_CE_NAME(ImmGetCompositionFont);               /* ms905998 */
AKARI_CE_IMPORT BOOL ImmSetCompositionFont(HIMC hIMC, LPLOGFONT lplf)
    AKARI_CE_NAME(ImmSetCompositionFont);               /* ms906030 */

/* conversion status / list */

AKARI_CE_IMPORT BOOL ImmGetConversionStatus(HIMC hIMC,
    LPDWORD lpfdwConversion, LPDWORD lpfdwSentence)
    AKARI_CE_NAME(ImmGetConversionStatus);              /* ms906005 */
AKARI_CE_IMPORT BOOL ImmSetConversionStatus(HIMC hIMC,
    DWORD fdwConversion, DWORD fdwSentence)
    AKARI_CE_NAME(ImmSetConversionStatus);              /* ms906033 */
AKARI_CE_IMPORT UINT ImmGetConversionList(HKL hKL, HIMC hIMC,
    LPCTSTR lpSrc, LPCANDIDATELIST lpDst, DWORD dwBufLen, UINT uFlag)
    AKARI_CE_NAME(ImmGetConversionList);                /* ms906004 */

/* status window / open status / properties */

AKARI_CE_IMPORT BOOL ImmGetOpenStatus(HIMC hIMC)
    AKARI_CE_NAME(ImmGetOpenStatus);                    /* ms906016 */
AKARI_CE_IMPORT BOOL ImmSetOpenStatus(HIMC hIMC, BOOL fOpen)
    AKARI_CE_NAME(ImmSetOpenStatus);                    /* ms906035 */
AKARI_CE_IMPORT BOOL ImmGetStatusWindowPos(HIMC hIMC, LPPOINT lpptPos)
    AKARI_CE_NAME(ImmGetStatusWindowPos);               /* ms906019 */
AKARI_CE_IMPORT BOOL ImmSetStatusWindowPos(HIMC hIMC, LPPOINT lpptPos)
    AKARI_CE_NAME(ImmSetStatusWindowPos);               /* ms906036 */
AKARI_CE_IMPORT HWND ImmGetDefaultIMEWnd(HWND hWnd)
    AKARI_CE_NAME(ImmGetDefaultIMEWnd);                 /* ms906007 */
AKARI_CE_IMPORT BOOL ImmGetProperty(HKL hKL, DWORD fdwIndex)
    AKARI_CE_NAME(ImmGetProperty);                      /* ms906017 */
AKARI_CE_IMPORT DWORD ImmGetGuideLine(HIMC hIMC, DWORD dwIndex,
    LPTSTR lpBuf, DWORD dwBufLen)
    AKARI_CE_NAME(ImmGetGuideLine);                     /* ms906009 */
AKARI_CE_IMPORT BOOL WINAPI ImmGetImeMenuItems(HIMC hIMC, DWORD dwFlags,
    DWORD dwType, LPIMEMENUITEMINFO lpImeParentMenu,
    LPIMEMENUITEMINFO lpImeMenu, DWORD dwSize)
    AKARI_CE_NAME(ImmGetImeMenuItems);                  /* ms906015 */

/* keyboard layout / IME identity */

AKARI_CE_IMPORT BOOL ImmIsIME(HKL hKL)
    AKARI_CE_NAME(ImmIsIME);                            /* ms906021 */
AKARI_CE_IMPORT UINT ImmGetDescription(HKL hKL, LPTSTR lpszDescription,
    UINT uBufLen)
    AKARI_CE_NAME(ImmGetDescription);                   /* ms906008 */
AKARI_CE_IMPORT BOOL ImmGetIMEFileName(HKL hKL, LPTSTR lpszFileName,
    UINT uBufLen)
    AKARI_CE_NAME(ImmGetIMEFileName);                   /* ms906014 */
AKARI_CE_IMPORT BOOL ImmConfigureIME(HKL hKL, HWND hWnd, DWORD dwMode,
    LPVOID lpData)
    AKARI_CE_NAME(ImmConfigureIME);                     /* ms905986 */
AKARI_CE_IMPORT LRESULT ImmEscape(HKL hKL, HIMC hIMC, UINT uEscape,
    LPVOID lpData)
    AKARI_CE_NAME(ImmEscape);                           /* ms905993 */
AKARI_CE_IMPORT BOOL ImmIsUIMessage(HWND hWndIME, UINT msg,
    WPARAM wParam, LPARAM lParam)
    AKARI_CE_NAME(ImmIsUIMessage);                      /* ms906022 */
AKARI_CE_IMPORT BOOL WINAPI ImmGenerateMessage(HIMC hIMC)
    AKARI_CE_NAME(ImmGenerateMessage);                  /* ms905994 */
AKARI_CE_IMPORT UINT ImmGetVirtualKey(HWND hWnd)
    AKARI_CE_NAME(ImmGetVirtualKey);                    /* ms906020 */

/* hot keys */

AKARI_CE_IMPORT BOOL WINAPI ImmGetHotKey(DWORD dwHotKeyID,
    LPUINT lpuModifiers, LPUINT lpuVKey, LPHKL lphKL)
    AKARI_CE_NAME(ImmGetHotKey);                        /* ms906010 */
AKARI_CE_IMPORT BOOL WINAPI ImmSetHotKey(DWORD dwHotKeyID,
    UINT uModifiers, UINT uVKey, HKL hKL)
    AKARI_CE_NAME(ImmSetHotKey);                        /* ms906034 */
AKARI_CE_IMPORT BOOL ImmSimulateHotKey(HWND hWnd, DWORD dwHotKeyID)
    AKARI_CE_NAME(ImmSimulateHotKey);                   /* ms906037 */

/* user dictionary (register words) */

AKARI_CE_IMPORT BOOL ImmRegisterWord(HKL hKL, LPCTSTR lpszReading,
    DWORD dwStyle, LPCTSTR lpszRegister)
    AKARI_CE_NAME(ImmRegisterWord);                     /* ms906026: the
    archive prints the second parameter type as LPCTSR; LPCTSTR is the
    documented spelling (every other CE page of this set) */
AKARI_CE_IMPORT BOOL ImmUnregisterWord(HKL hKL, LPCTSTR lpszReading,
    DWORD dwStyle, LPCTSTR lpszUnregister)
    AKARI_CE_NAME(ImmUnregisterWord);                   /* ms906041 */
AKARI_CE_IMPORT UINT ImmEnumRegisterWord(HKL hKL,
    REGISTERWORDENUMPROC lpfnEnumProc, LPCTSTR lpszReading,
    DWORD dwStyle, LPCTSTR lpszRegister, LPVOID lpData)
    AKARI_CE_NAME(ImmEnumRegisterWord);                 /* ms905992 */
AKARI_CE_IMPORT UINT ImmGetRegisterWordStyle(HKL hKL, UINT nItem,
    LPSTYLEBUF lpStyleBuf)
    AKARI_CE_NAME(ImmGetRegisterWordStyle);             /* ms906018 */

/* IME control / CE-specific */

AKARI_CE_IMPORT BOOL ImmNotifyIME(HIMC hIMC, DWORD dwAction,
    DWORD dwIndex, DWORD dwValue)
    AKARI_CE_NAME(ImmNotifyIME);                        /* ms906025 */
AKARI_CE_IMPORT BOOL ImmDisableIME(DWORD idThread)
    AKARI_CE_NAME(ImmDisableIME);                       /* ms905991 */
AKARI_CE_IMPORT BOOL ImmSIPanelState(UINT dwCmd, LPVOID pValue)
    AKARI_CE_NAME(ImmSIPanelState);                     /* ms906038: the
    CE-specific software input panel state helper */

#endif /* _IMM_H */
