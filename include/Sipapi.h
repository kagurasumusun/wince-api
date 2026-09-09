/*
 * Sipapi.h -- Software-based Input Panel application layer for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  The Software-based Input Panel Reference book of the CE 5.0
 * documentation (Shell and User Interface :: User Interface ::
 * Software-based Input Panel, book root aa453941; reference aa452750) is
 * the source book: Software-Based Input Panel Functions (10 pages),
 * Software-Based Input Panel Structures (SIPINFO, IMENUMINFO here;
 * IMINFO, LMDATA in sip.h) and Software-Based Input Panel Interfaces
 * (sip.h).
 *
 * Requirement rows: every Sip* function page prints Header: Sipapi.h /
 * Link Library: Coredll.lib, OS Versions: Windows CE 2.10 and later
 * (the CE 6.0 twins repeat sipapi.h / coredll.lib), so the functions
 * feed def/coredll-doc.def.  SIPINFO prints Sipapi.h with no library
 * row; IMENUMINFO prints Sipapi.h with no library row.
 *
 * Transcription notes (recorded per item in docs/inventory.md):
 *  (a) The CE 5.0 archive strips code spacing (SipEnumIM printed
 *      "IMENUMPROCpEnumIMProc", SipRegisterNotification "HWNDhWnd",
 *      SipShowIM "DWORDdwFlag", SipSetDefaultRect "BOOLSipSetDefaultRect");
 *      the whitespace-preserved CE 6.0 twins (ee502586 / ee505491 /
 *      ee502869 / ee504359) fix the spacing.
 *  (b) IMENUMPROC is named by the SipEnumIM parameter but has no page
 *      of its own; it is carried as a function-pointer typedef built
 *      from the two documented signatures (SipEnumIM's "pointer to the
 *      SipEnumIMProc callback function" and SipEnumIMProc's own
 *      prototype) -- a documented design decision, like the M45
 *      callback carriers.
 *  (c) The SipShowIM flag names (SIPF_ON / SIPF_OFF), the SIPINFO
 *      fdwFlags bit names (SIPF_DOCKED / SIPF_LOCKED / SIPF_OFF /
 *      SIPF_ON) and the SipStatus return names (SIP_STATUS_AVAILABLE /
 *      SIP_STATUS_UNAVAILABLE) are published as NAMES without numeric
 *      values on both the CE 5.0 pages and the CE 6.0 twins; they are
 *      held as gaps in docs/inventory.md rather than defined here (the
 *      M39-M41 held-set policy).  The IMINFO table prints "SIP_OFF"
 *      (no F) for the off state -- see sip.h.
 */

#ifndef AKARI_SIPAPI_H
#define AKARI_SIPAPI_H

#include "Windows.h"   /* RECT, HWND, BOOL, DWORD, TCHAR, MAX_PATH */
#include "objbase.h"   /* CLSID */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Structures                                                           */
/* ------------------------------------------------------------------ */

/* ms932860 "SIPINFO" (Windows CE 2.01 and later; Sipapi.h; no Link
 * Library row; CE 6.0 twin ee499105 prints the identical layout).
 * State of the software-based input panel: fdwFlags combines the
 * SIPF_* bit names (held set, note (c)); rcVisibleDesktop is the
 * desktop area not obscured by the panel; rcSipRect is the panel
 * window rectangle in screen coordinates; pvImData points to
 * IM-defined data of dwImDataSize bytes (set dwImDataSize to 0 before
 * SipGetInfo unless the IM is known to provide data).  Anonymous tag
 * as printed.  This is the structure the M50 SHSipInfo SPI_*SIPINFO
 * actions point at. */
typedef struct {
    DWORD  cbSize;             /* sizeof(SIPINFO); set by the application */
    DWORD  fdwFlags;           /* SIPF_* combination (names held) */
    RECT   rcVisibleDesktop;   /* desktop area not obscured by the panel */
    RECT   rcSipRect;          /* panel window rectangle, screen coords */
    DWORD  dwImDataSize;       /* size of the data pointed to by pvImData */
    VOID  *pvImData;           /* IM-defined data (can be NULL) */
} SIPINFO;

/* ms909841 "IMENUMINFO" (Windows CE 2.10 and later; Sipapi.h; no Link
 * Library row; CE 6.0 twin ee503605 repeats the print).  Information
 * on one installed input method, passed to the SipEnumIMProc callback
 * by SipEnumIM.  The page prints the declaration without the typedef
 * keyword ("struct_IMENUMINFO{...}IMENUMINFO;"); the obvious typedef
 * is restored (transcription note, same model as the M49/M50
 * print fixes) and the tag is the printed "_IMENUMINFO". */
typedef struct _IMENUMINFO {
    TCHAR szName[MAX_PATH];    /* IM default name from the registry */
    CLSID clsid;               /* CLSID of the installed IM */
} IMENUMINFO;

/* ------------------------------------------------------------------ */
/* Callback carrier (note (b))                                          */
/* ------------------------------------------------------------------ */

/* aa453742 types the SipEnumIM parameter "IMENUMPROC pEnumIMProc" --
 * "pointer to the SipEnumIMProc callback function"; aa453743 prints
 * the callback prototype "int SipEnumIMProc(IMENUMINFO* pIMInfo)".
 * No CE page publishes the IMENUMPROC typedef, so it is carried here
 * as the function-pointer type those two documented signatures define
 * (documented design decision).  The callback returns nonzero to
 * continue enumeration, zero to stop it. */
typedef int (*IMENUMPROC)(IMENUMINFO *pIMInfo);

/* aa453743 "SipEnumIMProc" (Windows CE 2.10 and later; Header and
 * Link Library both print "Developer defined" -- the application
 * implements it).  Declared without the import pin: it is the
 * documented callback shape the application defines and passes to
 * SipEnumIM (same model as the M47 CPAcquireContext declaration). */
int SipEnumIMProc(IMENUMINFO *pIMInfo);

/* ------------------------------------------------------------------ */
/* Functions (Header: Sipapi.h; Link Library: Coredll.lib;              */
/* Windows CE 2.10 and later)                                           */
/* ------------------------------------------------------------------ */

/* aa453742: enumerates the available input methods; pEnumIMProc NULL
 * returns the count.  Returns the number of available IMs (0 = none;
 * -1 = error on CE 3.0 and later).  Does not initialize the SIP
 * environment (with SipStatus / SipSetDefaultRect /
 * SipRegisterNotification). */
AKARI_CE_IMPORT int SipEnumIM(IMENUMPROC pEnumIMProc) AKARI_CE_NAME(SipEnumIM);

/* aa453744: returns the CLSID of the current input method. */
AKARI_CE_IMPORT BOOL SipGetCurrentIM(CLSID *pClsid) AKARI_CE_NAME(SipGetCurrentIM);

/* aa453745: receives the SIP state, the unobscured desktop area, the
 * panel rectangle and the current IM data (set dwImDataSize to 0
 * first unless the IM is known to provide data). */
AKARI_CE_IMPORT BOOL SipGetInfo(SIPINFO *pSipInfo) AKARI_CE_NAME(SipGetInfo);

/* ms932947: registers the single window that receives the WM_IM_INFO
 * notifications (winuser.h record) about the current IM; the
 * registration survives until cold or warm boot.  Does not initialize
 * the SIP environment. */
AKARI_CE_IMPORT BOOL SipRegisterNotification(HWND hWnd) AKARI_CE_NAME(SipRegisterNotification);

/* ms940337: sets the CLSID of the current IM; if the SIP cannot load
 * it the default IM is loaded instead (verify with SipGetCurrentIM).
 * An IM is a COM object. */
AKARI_CE_IMPORT BOOL SipSetCurrentIM(CLSID *pClsid) AKARI_CE_NAME(SipSetCurrentIM);

/* ms940340: sets the default size and position of the panel window;
 * takes effect when a new IM is loaded.  Does not initialize the SIP
 * environment. */
AKARI_CE_IMPORT BOOL SipSetDefaultRect(RECT *pRect) AKARI_CE_NAME(SipSetDefaultRect);

/* ms940341: sets the panel state / desktop area / rectangle and
 * IM-defined data from a SIPINFO structure (clear the structure
 * beforehand; the panel window cannot be resized by this call). */
AKARI_CE_IMPORT BOOL SipSetInfo(SIPINFO *pSipInfo) AKARI_CE_NAME(SipSetInfo);

/* ms940342: shows (SIPF_ON) or hides (SIPF_OFF) the current panel
 * window -- flag names published without values (held set, note (c));
 * the values needed to call this are owed by the documented on-device
 * readback.  When it fails it returns an HRESULT error code. */
AKARI_CE_IMPORT BOOL SipShowIM(DWORD dwFlag) AKARI_CE_NAME(SipShowIM);

/* ms940343: returns SIP_STATUS_AVAILABLE (installed) or
 * SIP_STATUS_UNAVAILABLE (not installed) -- names published without
 * values (held set, note (c)).  Does not initialize the SIP
 * environment. */
AKARI_CE_IMPORT DWORD SipStatus(void) AKARI_CE_NAME(SipStatus);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_SIPAPI_H */
