/*
 * Snmpexts.h -- SnmpTfx framework API for Windows CE (Snmpexts.h layer).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  Source book: CE 5.0 "SNMP Application Development :: SnmpTfx
 * Framework" (tools/manifests/snmp-tfx.manifest + the SnmpTfx leaves of
 * tools/manifests/snmp.manifest, fetched M57; CE 6.0 twins
 * ee489090/ee489248/ee489056 in build/pages6 cross-read).  OS Versions:
 * "Windows CE 3.0 and later".  Requirement rows: "Header: Snmpexts.h.
 * Link Library: Snmpapi.lib" (def/snmpapi-doc.def).
 *
 * The SnmpTfx Framework Structures book (ms894645) documents that
 * Snmpexts.h "includes data definitions for all of the structures that
 * are used" (SnmpMibView, SnmpMibEntry array, SnmpMibTable array), but
 * no page of any CE generation prints those layouts, and they are
 * initialized through the sample-framework macros (MIB_VIEW, MIB_*),
 * not through this API: the layouts are HELD (see docs/inventory.md
 * M57); SnmpMibView is forward-declared so the SnmpTfxOpen prototype
 * compiles exactly as printed.
 *
 * Derived values (repo derived-value rule; paths recorded):
 *   - SnmpTfxHandle: ms896029 Return Values -- "The SnmpTfxOpen
 *     function returns a HANDLE value" -> typedef HANDLE.
 */

#ifndef AKARI_SNMPEXTS_H
#define AKARI_SNMPEXTS_H

#include "Windef.h"
#include "Snmp.h"      /* RFC1157VarBindList, AsnInteger (ms896030) */

#ifdef __cplusplus
extern "C" {
#endif

/* SnmpTfxHandle: derived from the ms896029 Return Values text
 * ("returns a HANDLE value that is used to associate further calls to
 * the SnmpTfxQuery function"). */
typedef HANDLE SnmpTfxHandle;

/* SnmpMibView: layout held (see header note; pages ms894616/ee489056
 * document the MIB_VIEW macro initialization, not the members).  The
 * forward declaration keeps the documented SnmpTfxOpen prototype. */
typedef struct SnmpMibView SnmpMibView;

/* ms896029 "SnmpTfxOpen" (CE 6.0 twin ee489090 identical):
 * "SnmpTfxHandle WINAPI SnmpTfxOpen(DWORD numViews,
 *  SnmpMibView* supportedViews );" ("DWORDnumViews" on the CE 5.0 page
 * is a missing-space artifact). */
AKARI_CE_IMPORT SnmpTfxHandle WINAPI SnmpTfxOpen(DWORD numViews,
                                                 SnmpMibView *supportedViews
                                                 ) AKARI_CE_NAME(SnmpTfxOpen);

/* ms896030 "SnmpTfxQuery" (CE 6.0 twin ee489248 identical): the
 * RequestType values SNMP_PDU_GET / GETNEXT / SET / GETBULK are
 * names-only (held). */
AKARI_CE_IMPORT BOOL WINAPI SnmpTfxQuery(SnmpTfxHandle tfxHandle,
                                         BYTE RequestType,
                                         RFC1157VarBindList *pVarBindList,
                                         AsnInteger *pErrorStatus,
                                         AsnInteger *pErrorIndex
                                         ) AKARI_CE_NAME(SnmpTfxQuery);

/* ms896028 "SnmpTfxClose" (CE 6.0 twin ee489435 identical):
 * "VOID WINAPI SnmpTfxClose(SnmpTfxHandletfxHandle );"
 * (missing-space artifact on the parameter). */
AKARI_CE_IMPORT VOID WINAPI SnmpTfxClose(SnmpTfxHandle tfxHandle) AKARI_CE_NAME(SnmpTfxClose);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_SNMPEXTS_H */
