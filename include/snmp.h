/*
 * snmp.h -- SNMP Extension Agent / Utility API for Windows CE (Snmp.h layer).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  Source book: CE 5.0 "Device Management :: Simple Network
 * Management Protocol :: SNMP Reference" (tools/manifests/snmp.manifest +
 * snmp-structs.manifest, fetched M57; CE 6.0 twins in build/pages6 and
 * the desktop snmp.h pages preserved in build/pagesw/snmp-nf-*.html
 * cross-read where the CE 5.0 print is damaged).  OS Versions: "Windows
 * CE 3.0 and later".
 *
 * Import surfaces (per-page Link Library rows): "Snmp.lib" (the six
 * SnmpExtension* entry points, def/snmp-doc.def) and "Snmpapi.lib" (the
 * SnmpSvc/SnmpUtil utility set, def/snmpapi-doc.def; SnmpUtilMemAlloc
 * is documented in Snmpapi.h and lives in snmpapi.h here).
 *
 * The CE 5.0 signature blocks of several pages print a corrupted
 * prototype (a sibling function's name, dropped pointer stars, or a
 * return type contradicting the page's own Return Values section).
 * Every such case is resolved from (a) the page's parameter text
 * ("Pointer to an AsnOctetString structure..."), (b) the page's Return
 * Values text, (c) the CE 6.0 twin, and (d) the desktop snmp.h page
 * (official, same API family), and is noted per item below.
 *
 * Derived values (repo derived-value rule; derivation paths recorded):
 *   - the ASN_* / SNMP_EXCEPTION_* / SNMP_PDU_* / SNMP_EXTENSION_* /
 *     SNMP_GENERICTRAP_* / SNMP_ERRORSTATUS_* / SNMP_LOG* / SNMP_OUTPUT*
 *     families are names-only on the CE pages (values not published) --
 *     HELD, see docs/inventory.md M57.
 *   - typedefs whose underlying types the CE pages name but never lay
 *     out are shipped with recorded derivations (each marked below).
 */

#ifndef AKARI_SNMP_H
#define AKARI_SNMP_H

#include "windef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Return type.                                                        */
/* ------------------------------------------------------------------ */

/* SNMPAPI: the return type printed by the SnmpUtil* pages (e.g.
 * ms896044 "SNMPAPI SnmpUtilOidCmp(...)").  Its underlying type is not
 * printed by any CE page.  Derived: the comparison pages document
 * "greater than zero / zero / less than zero" results (ms896039,
 * ms896044) and the copy pages "nonzero / zero" -- a signed scalar;
 * on the 32-bit CE ABI the signed scalar is LONG (windef.h). */
typedef LONG SNMPAPI;

/* ------------------------------------------------------------------ */
/* ASN value types.                                                    */
/* ------------------------------------------------------------------ */

/* AsnInteger32: AsnAny member "number" -- "Accesses a 32-bit signed
 * integer variable" (ms894988).  Derived: 32-bit signed -> LONG. */
typedef LONG AsnInteger32;

/* AsnUnsigned32: AsnAny member "unsigned32" -- "Accesses a 32-bit
 * unsigned integer variable" (ms894988).  Derived -> ULONG. */
typedef ULONG AsnUnsigned32;

/* AsnCounter32: AsnAny member "counter32" -- "Accesses a counter
 * variable that increases until it reaches a maximum value of
 * (2^32) - 1" (ms894988).  Derived -> ULONG. */
typedef ULONG AsnCounter32;

/* AsnGauge32: AsnAny member "gauge" -- "Accesses a gauge variable"
 * (ms894988); the desktop AsnAny page ties ASN_GAUGE32 to the RFC 1902
 * Unsigned32 type (0..4294967295).  Derived -> ULONG. */
typedef ULONG AsnGauge32;

/* AsnTimeTicks: AsnAny member "ticks" -- "Accesses a timeticks counter
 * variable that is relative to a specific timer event" (ms894988);
 * RFC 1155 TimeTicks ::= INTEGER (0..4294967295).  Derived -> ULONG. */
typedef ULONG AsnTimeTicks;

/* ------------------------------------------------------------------ */
/* ASN structures (printed complete by the CE pages).                  */
/* ------------------------------------------------------------------ */

/* ms894991 "AsnObjectIdentifier". */
typedef struct {
    UINT  idLength;
    UINT *ids;
} AsnObjectIdentifier;

/* ms894993 "AsnOctetString". */
typedef struct {
    BYTE *stream;
    UINT  length;
    BOOL  dynamic;
} AsnOctetString;

/* AsnBits: AsnAny member "bits" -- "Accesses a variable that is an
 * enumeration of named bits" (ms894988); the BITS value is an octet
 * string (RFC 2578 section 3.5).  Derived: the API's octet-string
 * container type is AsnOctetString (ms894993) -> AsnOctetString. */
typedef AsnOctetString AsnBits;

/* AsnSequence: AsnAny member "sequence" -- "Accesses an ASN sequence
 * variable" (ms894988); a sequence value's content is carried as octets.
 * Derived: the API's octet-string container type -> AsnOctetString. */
typedef AsnOctetString AsnSequence;

/* AsnIPAdress [sic]: AsnAny member "address" -- "Accesses an IP address
 * variable" (ms894988, spelling as printed by the CE page); RFC 1155
 * IpAddress ::= OCTET STRING (SIZE (4)).  Derived: the API's
 * octet-string container type -> AsnOctetString. */
typedef AsnOctetString AsnIPAdress;

/* AsnOpaque: AsnAny member "arbitrary" -- "Accesses an opaque variable"
 * (ms894988); RFC 1155 Opaque ::= OCTET STRING.  Derived: the API's
 * octet-string container type -> AsnOctetString. */
typedef AsnOctetString AsnOpaque;

/* ms894989 "AsnCounter64": printed "typedef struct {ULONG LowPart;
 * ULONGHighPart;} AsnCounter64;" ("ULONGHighPart" is a missing-space
 * artifact) -- LowPart first, HighPart second, as printed. */
typedef struct {
    ULONG LowPart;
    ULONG HighPart;
} AsnCounter64;

/* ms894988 "AsnAny": union member types and order as printed; the
 * member type spellings are the CE page's (AsnIPAdress [sic]). */
typedef struct {
    BYTE asnType;
    union {
        AsnInteger32        number;
        AsnUnsigned32       unsigned32;
        AsnCounter64        counter64;
        AsnOctetString      string;
        AsnBits             bits;
        AsnObjectIdentifier object;
        AsnSequence         sequence;
        AsnIPAdress         address;
        AsnCounter32        counter32;
        AsnGauge32          gauge;
        AsnTimeTicks        ticks;
        AsnOpaque           arbitrary;
    } asnValue;
} AsnAny;

/* AsnObjectName: the SnmpVarBind page (ms896055) types the name member
 * "AsnObjectName" and the desktop SnmpVarBind page documents the name
 * as "the variable's name, as an object identifier"; RFC 1155
 * ObjectName ::= OBJECT IDENTIFIER.  Derived: the API's object-
 * identifier type (ms894991) -> AsnObjectIdentifier. */
typedef AsnObjectIdentifier AsnObjectName;

/* AsnObjectSyntax: the SnmpVarBind page (ms896055) types the value
 * member "AsnObjectSyntax"; the desktop AsnAny page documents AsnAny
 * as "a member of the SnmpVarBind structure" and the value member
 * "Contains the variable's value"; RFC 1155 ObjectSyntax ::= CHOICE
 * over the object syntaxes.  Derived -> AsnAny. */
typedef AsnAny AsnObjectSyntax;

/* AsnInteger: SnmpTfxQuery (ms896030) types its error-status parameters
 * "AsnInteger*" where SnmpExtensionQuery/QueryEx (ms896021/ms896022)
 * type the same-role parameters "AsnInteger32*"; RFC 1157 Integer is a
 * 32-bit signed integer.  Derived -> LONG (32-bit signed, the
 * AsnInteger32 scalar). */
typedef LONG AsnInteger;

/* ms896055 "SnmpVarBind". */
typedef struct {
    AsnObjectName   name;
    AsnObjectSyntax value;
} SnmpVarBind;

/* ms896056 "SnmpVarBindList". */
typedef struct {
    SnmpVarBind *list;
    UINT         len;
} SnmpVarBindList;

/* RFC1157VarBindList: SnmpTfxQuery (ms896030) takes
 * "RFC1157VarBindList* pVarBindList", described as "[in, out] Pointer
 * to the list of variable bindings"; RFC 1157 VarBindList is the
 * SEQUENCE OF VarBind and the API's variable-bindings list type is
 * SnmpVarBindList (ms896056).  Derived -> SnmpVarBindList. */
typedef SnmpVarBindList RFC1157VarBindList;

/* ------------------------------------------------------------------ */
/* SNMP Extension Agent API (Snmp.h, Snmp.lib).                        */
/* ------------------------------------------------------------------ */

/* ms896018 "SnmpExtensionClose". */
AKARI_CE_IMPORT VOID SnmpExtensionClose(void) AKARI_CE_NAME(SnmpExtensionClose);

/* ms896019 "SnmpExtensionInit": the CE 5.0 print mangles the second
 * parameter ("Handle dwUptimeReference" -- the twin ee489093 prints
 * the same damaged triple); the parameter text on both CE pages
 * documents phSubagentTrapEvent as "[out] Pointer to an event handle"
 * and pFirstSupportedRegion as "[out] Pointer to an
 * AsnObjectIdentifier structure", matching the desktop page
 * (HANDLE* / AsnObjectIdentifier*). */
AKARI_CE_IMPORT BOOL SnmpExtensionInit(DWORD dwUptimeReference,
                                       HANDLE *phSubagentTrapEvent,
                                       AsnObjectIdentifier *pFirstSupportedRegion
                                       ) AKARI_CE_NAME(SnmpExtensionInit);

/* ms896020 "SnmpExtensionInitEx". */
AKARI_CE_IMPORT BOOL SnmpExtensionInitEx(
    AsnObjectIdentifier *pNextSupportedRegion) AKARI_CE_NAME(SnmpExtensionInitEx);

/* ms896021 "SnmpExtensionQuery": the CE 5.0 print drops the pointer
 * stars; the parameter text ("Pointer to the variable bindings list",
 * "Pointer to a variable in ...") and the desktop page give
 * SnmpVarBindList* / AsnInteger32* / AsnInteger32*.  The bPduType
 * values SNMP_PDU_GET / GETNEXT / SET are names-only (held). */
AKARI_CE_IMPORT BOOL SnmpExtensionQuery(BYTE bPduType,
                                        SnmpVarBindList *pVarBindList,
                                        AsnInteger32 *pErrorStatus,
                                        AsnInteger32 *pErrorIndex) AKARI_CE_NAME(SnmpExtensionQuery);

/* ms896022 "SnmpExtensionQueryEx": pointer stars resolved as above
 * (parameter text + desktop page); the dwRequestType values
 * SNMP_EXTENSION_GET / GET_NEXT / SET_TEST / SET_COMMIT / SET_UNDO /
 * SET_CLEANUP and the pErrorStatus values SNMP_ERRORSTATUS_* are
 * names-only (held). */
AKARI_CE_IMPORT BOOL SnmpExtensionQueryEx(DWORD dwRequestType,
                                          DWORD dwTransactionId,
                                          SnmpVarBindList *pVarBindList,
                                          AsnOctetString *pContextInfo,
                                          AsnInteger32 *pErrorStatus,
                                          AsnInteger32 *pErrorIndex) AKARI_CE_NAME(SnmpExtensionQueryEx);

/* ms896023 "SnmpExtensionTrap": pointer stars resolved as above; the
 * page prints "AsnTimeticks" (case artifact; the AsnAny page ms894988
 * spells the type AsnTimeTicks); pGenericTrapId values
 * SNMP_GENERICTRAP_* are names-only (held). */
AKARI_CE_IMPORT BOOL SnmpExtensionTrap(AsnObjectIdentifier *pEnterpriseOid,
                                       AsnInteger32 *pGenericTrapId,
                                       AsnInteger32 *pSpecificTrapId,
                                       AsnTimeTicks *pTimeStamp,
                                       SnmpVarBindList *pVarBindList) AKARI_CE_NAME(SnmpExtensionTrap);

/* ------------------------------------------------------------------ */
/* SNMP Utility API (Snmp.h, Snmpapi.lib).                             */
/* ------------------------------------------------------------------ */

/* ms896024 "SnmpSvcGetUptime". */
AKARI_CE_IMPORT DWORD SnmpSvcGetUptime(void) AKARI_CE_NAME(SnmpSvcGetUptime);

/* ms896025 "SnmpSvcSetLogLevel": the CE 5.0 print shows a DWORD return
 * but the page's Return Values section states "This function has no
 * return values"; the desktop page prints VOID.  The nLogLevel values
 * (SNMP_LOG_*) are names-only (held). */
AKARI_CE_IMPORT VOID SnmpSvcSetLogLevel(INT nLogLevel) AKARI_CE_NAME(SnmpSvcSetLogLevel);

/* ms896026 "SnmpSvcSetLogType": same print artifact as SetLogLevel;
 * the nLogType values (SNMP_OUTPUT_*) are names-only (held). */
AKARI_CE_IMPORT VOID SnmpSvcSetLogType(INT nLogType) AKARI_CE_NAME(SnmpSvcSetLogType);

/* ms896031 "SnmpUtilAsnAnyCpy". */
AKARI_CE_IMPORT SNMPAPI SnmpUtilAsnAnyCpy(AsnAny *pAnyDest,
                                           AsnAny *pAnySrc) AKARI_CE_NAME(SnmpUtilAsnAnyCpy);

/* ms896032 "SnmpUtilAsnAnyFree": the CE 5.0 print shows an SNMPAPI
 * return but the Return Values section states "This function has no
 * return values"; the desktop page prints VOID. */
AKARI_CE_IMPORT VOID SnmpUtilAsnAnyFree(AsnAny *pAny) AKARI_CE_NAME(SnmpUtilAsnAnyFree);

/* ms896033 "SnmpUtilDbgPrint": the CE 5.0 print shows two parameters;
 * the desktop page documents the printf-style variadic tail
 * "(INT nLogLevel, LPSTR szFormat, ...)". */
AKARI_CE_IMPORT VOID SnmpUtilDbgPrint(INT nLogLevel, LPSTR szFormat, ...) AKARI_CE_NAME(SnmpUtilDbgPrint);

/* ms896034 "SnmpUtilIdsToA": the CE 5.0 print shows "UINT Ids" but the
 * parameter text documents "the array pointed to by the Ids parameter";
 * the desktop page prints UINT* Ids. */
AKARI_CE_IMPORT LPSTR SnmpUtilIdsToA(UINT *Ids,
                                     UINT IdLength) AKARI_CE_NAME(SnmpUtilIdsToA);

/* ms896035 "SnmpUtilIdsToW": as SnmpUtilIdsToA (UINT* Ids); the page
 * documents the Unicode result (CE-specific function). */
AKARI_CE_IMPORT LPTSTR SnmpUtilIdsToW(UINT *Ids,
                                      UINT IdLength) AKARI_CE_NAME(SnmpUtilIdsToW);

/* ms896037 "SnmpUtilMemFree". */
AKARI_CE_IMPORT VOID SnmpUtilMemFree(LPVOID pMem) AKARI_CE_NAME(SnmpUtilMemFree);

/* ms896038 "SnmpUtilMemReAlloc". */
AKARI_CE_IMPORT LPVOID SnmpUtilMemReAlloc(LPVOID pmem,
                                          UINT nBytes) AKARI_CE_NAME(SnmpUtilMemReAlloc);

/* ms896039 "SnmpUtilOctetsCmp": the CE 5.0 print spells the prototype
 * "SnmpUtilOctetsComp" and drops the pointer stars; the parameter text
 * ("Pointer to an AsnOctetString structure") and the desktop page give
 * AsnOctetString*. */
AKARI_CE_IMPORT SNMPAPI SnmpUtilOctetsCmp(AsnOctetString *pOctets1,
                                          AsnOctetString *pOctets2) AKARI_CE_NAME(SnmpUtilOctetsCmp);

/* ms896040 "SnmpUtilOctetsCpy": pointer stars resolved via the
 * parameter text ("Pointer to an AsnOctetString structure to receive
 * the copy" / "... to copy") and the desktop page; parameter names as
 * printed by the CE page. */
AKARI_CE_IMPORT SNMPAPI SnmpUtilOctetsCpy(AsnOctetString *pOctetsDest,
                                          AsnOctetString *pOctetsSrc) AKARI_CE_NAME(SnmpUtilOctetsCpy);

/* ms896041 "SnmpUtilOctetsFree" (parameter name pOctetsDst as printed
 * by the CE page; the Remarks text repeats the function's own name,
 * a page artifact). */
AKARI_CE_IMPORT VOID SnmpUtilOctetsFree(AsnOctetString *pOctetsDst) AKARI_CE_NAME(SnmpUtilOctetsFree);

/* ms896042 "SnmpUtilOctetsNCmp": the CE 5.0 print carries the
 * SnmpUtilOctetsFree prototype name (artifact); parameters and return
 * are as printed, corroborated by the desktop page. */
AKARI_CE_IMPORT SNMPAPI SnmpUtilOctetsNCmp(AsnOctetString *pOctets1,
                                           AsnOctetString *pOctets2,
                                           UINT nChars) AKARI_CE_NAME(SnmpUtilOctetsNCmp);

/* ms896043 "SnmpUtilOidAppend". */
AKARI_CE_IMPORT SNMPAPI SnmpUtilOidAppend(AsnObjectIdentifier *pOidDst,
                                          AsnObjectIdentifier *pOidSrc) AKARI_CE_NAME(SnmpUtilOidAppend);

/* ms896044 "SnmpUtilOidCmp". */
AKARI_CE_IMPORT SNMPAPI SnmpUtilOidCmp(AsnObjectIdentifier *pOid1,
                                       AsnObjectIdentifier *pOid2) AKARI_CE_NAME(SnmpUtilOidCmp);

/* ms896045 "SnmpUtilOidCpy". */
AKARI_CE_IMPORT SNMPAPI SnmpUtilOidCpy(AsnObjectIdentifier *pOidDst,
                                       AsnObjectIdentifier *pOidSrc) AKARI_CE_NAME(SnmpUtilOidCpy);

/* ms896046 "SnmpUtilOidFree". */
AKARI_CE_IMPORT VOID SnmpUtilOidFree(AsnObjectIdentifier *pOid) AKARI_CE_NAME(SnmpUtilOidFree);

/* ms896047 "SnmpUtilOidNCmp": the CE 5.0 print carries the
 * "VOID SnmpUtilOidFree(...)" prototype (sibling-name artifact); the
 * Return Values section documents the signed comparison result and the
 * desktop page prints SNMPAPI. */
AKARI_CE_IMPORT SNMPAPI SnmpUtilOidNCmp(AsnObjectIdentifier *pOid1,
                                        AsnObjectIdentifier *pOid2,
                                        UINT nSubIds) AKARI_CE_NAME(SnmpUtilOidNCmp);

/* ms896048 "SnmpUtilOidToA": the CE 5.0 print shows the Oid parameter
 * by value; the parameter text documents "the object identifier
 * pointed to by the Oid parameter" and the desktop page prints
 * AsnObjectIdentifier*. */
AKARI_CE_IMPORT LPSTR SnmpUtilOidToA(AsnObjectIdentifier *Oid) AKARI_CE_NAME(SnmpUtilOidToA);

/* ms896049 "SnmpUtilOidToW": as SnmpUtilOidToA (pointer); CE-specific
 * Unicode variant. */
AKARI_CE_IMPORT LPTSTR SnmpUtilOidToW(AsnObjectIdentifier *Oid) AKARI_CE_NAME(SnmpUtilOidToW);

/* ms896050 "SnmpUtilPrintToStrAsnAny" (CE-specific). */
AKARI_CE_IMPORT VOID SnmpUtilPrintToStrAsnAny(AsnAny *pAny) AKARI_CE_NAME(SnmpUtilPrintToStrAsnAny);

/* ms896051 "SnmpUtilVarBindCpy": the CE 5.0 print shows a VOID return
 * but the Return Values section documents nonzero/zero; the desktop
 * page prints SNMPAPI. */
AKARI_CE_IMPORT SNMPAPI SnmpUtilVarBindCpy(SnmpVarBind *pVbDest,
                                           SnmpVarBind *pVbSrc) AKARI_CE_NAME(SnmpUtilVarBindCpy);

/* ms896052 "SnmpUtilVarBindFree". */
AKARI_CE_IMPORT VOID SnmpUtilVarBindFree(SnmpVarBind *pVb) AKARI_CE_NAME(SnmpUtilVarBindFree);

/* ms896053 "SnmpUtilVarBindListCpy": as SnmpUtilVarBindCpy (VOID print
 * vs nonzero/zero Return Values; desktop page prints SNMPAPI). */
AKARI_CE_IMPORT SNMPAPI SnmpUtilVarBindListCpy(SnmpVarBindList *pVblDst,
                                               SnmpVarBindList *pVblSrc) AKARI_CE_NAME(SnmpUtilVarBindListCpy);

/* ms896054 "SnmpUtilVarBindListFree". */
AKARI_CE_IMPORT VOID SnmpUtilVarBindListFree(SnmpVarBindList *pVbl) AKARI_CE_NAME(SnmpUtilVarBindListFree);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_SNMP_H */
