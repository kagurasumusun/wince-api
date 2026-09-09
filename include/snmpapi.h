/*
 * snmpapi.h -- SNMP memory allocator for Windows CE (Snmpapi.h layer).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  The declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * page in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * ID).  Source book: CE 5.0 "SNMP Reference :: SNMP Functions"
 * (tools/manifests/snmp.manifest, fetched M57).  OS Versions: "Windows
 * CE 3.0 and later".
 *
 * ms896036 prints "Header: Snmpapi.h. Link Library: Snmp.lib." (the
 * only Snmpapi.h page of the harvest); the import surface entry lives
 * in def/snmp-doc.def alongside the SnmpExtension* pages.
 *
 * Print artifacts of ms896036: the parameter prints "UINTnBytes"
 * (missing space) and the Return Values section prints "This function
 * has no return values" although the prototype returns LPVOID (the
 * Remarks document the allocated buffer; the prototype return is the
 * documented one).
 */

#ifndef AKARI_SNMPAPI_H
#define AKARI_SNMPAPI_H

#include "windef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ms896036 "SnmpUtilMemAlloc": allocates zeroed memory from the
 * process heap (page Remarks); release it with SnmpUtilMemFree
 * (Snmp.h, ms896037). */
AKARI_CE_IMPORT LPVOID SnmpUtilMemAlloc(UINT nBytes) AKARI_CE_NAME(SnmpUtilMemAlloc);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_SNMPAPI_H */
