/*
 * Mshtmhst.h -- Windows CE MSHTML host callbacks (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE
 * documentation (learn.microsoft.com previous-versions archive;
 * page ids cited per record).  This is the complete "Mshtmhst.h,
 * Mshtmhst.idl." row set of the Internet Client Services book
 * harvest (M92/M93, tools/manifests/internetclient-book.manifest):
 * the NVFOCUS_DIRECTION enumeration and three host method pages.
 *
 * The three functions are host-container METHODS MSHTML calls on
 * the host (each page opens "This method is called by MSHTML",
 * and the GetFilename code example prints a C++ method`
 * MyContainer::Getfilename`) -- they are recorded, not declared,
 * and no Link Library row is printed on any of the three pages.
 */

#ifndef AKARI_MSHTMHST_H
#define AKARI_MSHTMHST_H

#include "Windef.h"    /* BOOL, DWORD, HWND, LRESULT, RECT */
#include "Objbase.h"   /* HRESULT, LPOLESTR, VARIANT */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* NVFOCUS_DIRECTION (ms918828) -- enum print with values               */
/* ------------------------------------------------------------------ */

/* ms918828 "NVFOCUS_DIRECTION": print `typedef enum
 * _NvFocusDirection {FOCUS_NONE = 0,FOCUS_UP = 1,FOCUS_DOWN = 2,
 * FOCUS_LEFT = 3,FOCUS_RIGHT = 4,} NVFOCUS_DIRECTION;` (trailing
 * comma normalized; OS row: Windows CE .NET 4.1 and later). */
typedef enum _NvFocusDirection {
    FOCUS_NONE = 0,
    FOCUS_UP = 1,
    FOCUS_DOWN = 2,
    FOCUS_LEFT = 3,
    FOCUS_RIGHT = 4,
} NVFOCUS_DIRECTION;

/* ------------------------------------------------------------------ */
/* Recorded -- host methods MSHTML calls on the container               */
/* ------------------------------------------------------------------ */

/* aa451975 "GetFilename": `HRESULT GetFilename( BOOL fSave, HWND hwnd, DWORD idFilterRes, LPOLESTR lpstrFileName, DWORD cchFile, long lCustData);` */
/* ms905429 "ShowInternalMessage": `HRESULT ShowInternalMessage( HWND hwnd, LPOLESTR lpstrText, LPOLESTR lpstrCaption, DWORD dwType, DWORD dwMessageId, LPOLESTR lpstrHelpFile, DWORD dwHelpContext, LRESULT * plResult);` */
/* ms905508 "ShowPrompt": `HRESULT ShowPrompt( HWND hwnd, LPOLESTR lpstrMessage, LPOLESTR lpstrDefault, VARIANT *pvarText, LRESULT *plResult);` */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_MSHTMHST_H */
