/*
 * Celog.h -- CeLog event-tracking API for Windows CE (kernel profiler).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE pages of
 * the "CeLog Event Tracking Reference" book (CE-era MSDN archive,
 * learn.microsoft.com previous-versions, (v=msdn.10) IDs).  All of the
 * function pages below print Header: Celog.h and Link Library:
 * Coredll.lib.  OS Versions per function are recorded inline.
 *
 * This header covers the seven *function* pages of the CeLog book.
 * The CEL_* event-record structures (CEL_EVENT_CREATE, CEL_HEADER,
 * MAPHEADER, ... 60+ pages), the event-identifiers pages and the zone
 * list page record the *payload format* of kernel event-log entries
 * (consumed through the CeLog driver stream); they carry no function
 * declarations and no Header/Link rows, and are recorded in
 * docs/inventory.md rather than transcribed here.
 */

#ifndef AKARI_CELOG_H
#define AKARI_CELOG_H

#include "Windef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* aa450823 "CeLogData (Windows CE 5.0)":
 * void CeLogData(BOOL, WORD, PVOID, WORD, DWORD, DWORD, WORD, BOOL).
 * CE 3.0+; Celog.h; Coredll.lib.  Called by the kernel whenever a
 * loggable event occurs; apps/drivers normally reach it through the
 * zone macros. */
AKARI_CE_IMPORT void CeLogData(BOOL fTimeStamp, WORD wID, PVOID pData, WORD wLen,
               DWORD dwZoneUser, DWORD dwZoneCE, WORD wFlag,
               BOOL fFlagged) AKARI_CE_NAME(CeLogData);

/* aa450824 "CeLogGetZones (Windows CE 5.0)":
 * BOOL CeLogGetZones(LPDWORD, LPDWORD, LPDWORD, LPDWORD).  CE .NET
 * 4.0+; Celog.h; Coredll.lib.  Returns the active user zones, active
 * predefined system zones, the processes being logged, and the zones
 * the kernel supports (any output pointer may be NULL). */
AKARI_CE_IMPORT BOOL CeLogGetZones(LPDWORD lpdwZoneUser, LPDWORD lpdwZoneCE,
                   LPDWORD lpdwZoneProcess, LPDWORD lpdwAvailableZones) AKARI_CE_NAME(CeLogGetZones);

/* aa451043 "CeLogInterrupt (Windows CE 5.0)":
 * void CeLogInterrupt(DWORD).  CE .NET 3.0+; Celog.h; Coredll.lib.
 * Called by the kernel twice per interrupt (before the ISR and when
 * the ISR returns).  The value packs the CEL_INT_DATA wSysIntr (upper
 * word) and wNestingLevel (lower word) members; the nesting level's
 * upper bit marks interrupt entry vs exit. */
AKARI_CE_IMPORT void CeLogInterrupt(DWORD dwlogvalue) AKARI_CE_NAME(CeLogInterrupt);

/* aa450825 "CeLogMsg (Windows CE 5.0)":
 * void CeLogMsg(WCHAR *format, ...).  CE .NET 4.0+; Celog.h;
 * Coredll.lib.  Prints a formatted Unicode string to CeLogData; the
 * RETAILCELOGMSG / DEBUGCELOGMSG macros output conditionally. */
AKARI_CE_IMPORT void CeLogMsg(WCHAR *format, ...) AKARI_CE_NAME(CeLogMsg);

/* aa450826 "CeLogQueryZones (Windows CE 5.0)":
 * BOOL CeLogQueryZones(LPDWORD, LPDWORD, LPDWORD).  CE .NET 4.0+;
 * Celog.h (page: "Not applicable"); Coredll.lib.  Called by the kernel
 * to query zone state from the event-tracking DLL. */
AKARI_CE_IMPORT BOOL CeLogQueryZones(LPDWORD lpdwZoneUser, LPDWORD lpdwZoneCE,
                     LPDWORD ldpwZoneProcess) AKARI_CE_NAME(CeLogQueryZones);

/* aa450827 "CeLogReSync (Windows CE 5.0)":
 * BOOL CeLogReSync(void).  CE 3.0+; Celog.h; Coredll.lib.  Tells the
 * logging engine to dump all current threads and processes (for an
 * event viewer that restarts logging); the page notes this function is
 * part of the kernel and generates CeLogData calls. */
AKARI_CE_IMPORT BOOL CeLogReSync(void) AKARI_CE_NAME(CeLogReSync);

/* aa450828 "CeLogSetZones (Windows CE 5.0)":
 * void CeLogSetZones(DWORD, DWORD, DWORD).  CE 3.0+; Celog.h;
 * Coredll.lib.  Changes the active logging zones: user zones, OS zones
 * (default 0xFFBFFFFF, KCALLS off) and logged processes (default
 * 0xFFFFFFFF, all). */
AKARI_CE_IMPORT void CeLogSetZones(DWORD dwZoneUser, DWORD dwZoneCE, DWORD dwZoneProcess) AKARI_CE_NAME(CeLogSetZones);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_CELOG_H */
