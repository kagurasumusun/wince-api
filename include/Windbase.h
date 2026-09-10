/*
 * Windbase.h -- Windows CE databases (CEDB + EDB) for the Akari API.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (CE 5.0 Learn-archive pages, (v=msdn.10) IDs), harvested from the
 * *File Systems and Data Store -> Data Store -> Database Reference*
 * book (CEDB Reference + EDB Reference, 106 leaves, see
 * tools/manifests/dbref.manifest and docs/inventory.md M70).
 *
 * Header rows: 99 Requirement rows print **Windbase.h** and one row
 * (aa516982, CeChangeDatabaseLCID (CEDB)) prints **Pwindbas.h**; the
 * include/Windbase.h and include/Pwindbas.h aliases carry those
 * documented spellings.  Link Library row: Coredll.lib for every
 * function below (def/coredll-doc.def).
 *
 * Version policy (keep CE generations distinct, docs/inventory.md):
 *  - CEDB items are documented "Windows CE 1.0/1.01/2.10/.NET 4.0 and
 *    later"; this tree targets CE 4.2+, so they are declared
 *    unguarded (each comment carries its OS Versions row verbatim).
 *  - EDB items are documented "Windows CE 5.0 and later" and are
 *    wrapped in `#if !defined(_WIN32_WCE) || (_WIN32_WCE) >= 0x500`
 *    (default-visible so freestanding toolchain and cross checks
 *    still compile them; exactly hidden when building for CE 4.x).
 *
 * Zero-gap policy notes:
 *  - No numeric value for any CEVT_ or CEDB_ flag family member,
 *    nor for CEDB_MAXDBASENAMELEN / CEDB_MAXSORTORDER /
 *    CEDB_MAXSORTPROP / CCH_MAX_PASSWORD, is published on any CE
 *    page: the CE 5.0 harvest (6422 pages at M70, 6605 at M70b) was
 *    scanned, and the M71a twin check additionally fetched the CE
 *    6.0 twins (29 pages, (v=winembedded.60)) and the Windows CE
 *    .NET twins of the six DB_CEOID_* message pages -- values are
 *    absent from all three official trees (manifest:
 *    tools/manifests/dbref-ce6-twins.manifest).  Those names are
 *    recorded below as comments only -- nothing is invented.
 *  - Structures whose layout depends on those unpublished array
 *    sizes are therefore recorded verbatim but declared as
 *    INCOMPLETE types (pointer-only), which is exactly how the
 *    documented function signatures use them.
 *  - CEOID / CEPROPID / CEGUID / CEDBISOLATIONLEVEL are not printed
 *    by any CE page; they are closed below with recorded derivation
 *    paths (marked "closure") and are replaced if a page ever prints
 *    them.
 */

#ifndef AKARI_WINDBASE_H
#define AKARI_WINDBASE_H

#include "Windef.h"    /* DWORD, WORD, BOOL, HANDLE, HWND, UINT, ULONG,
                          USHORT, LPBYTE, LPWORD, LPDWORD, LPWSTR, LOWORD,
                          MAX_PATH */
#include "Winbase.h"   /* FILETIME (winbase.h line ~429 in this tree) */

#ifdef __cplusplus
extern "C" {
#endif

/* --- Carrier types (closures; see header banner). ------------------
 *
 * CEOID: no CE page prints the typedef.  Closure `ULONG`: the POOM
 * book prints the SAME object-store identifier both as CEOID
 * (ms883912 IOutlookItemCollection::GetItemFromOid(CEOID oid,...))
 * and as a 32-bit long (ITask/IContact/IAppointment::get_Oid
 * `[out] long *plOid`), so the identifier is 32 bits wide; ULONG is
 * the unsigned carrier (pimstore.h M65 records both pages). */
typedef ULONG CEOID;

/* CEPROPID: no CE page prints the typedef.  Closure `ULONG`: the
 * CEPROPVAL page (aa517227) documents that the high-order word of a
 * property ID is application-defined and the low-order word is the
 * predefined type constant (and TypeFromPropID, ms892256, is
 * LOWORD(propid)) -- a 32-bit value. */
typedef ULONG CEPROPID;

/* CEGUID: no CE page prints the struct.  Member names and count ARE
 * printed by the CHECK_INVALIDGUID / CHECK_SYSTEMGUID macros
 * (aa517295/aa517298 dereference Data1..Data4), and CREATE_INVALID_
 * GUID (aa517332) memsets the whole struct to -1, so CEGUID is a
 * plain 4-word bit carrier.  Closure: four DWORD Data members
 * (16-byte GUID-width carrier). */
typedef struct _CEGUID {
    DWORD Data1;
    DWORD Data2;
    DWORD Data3;
    DWORD Data4;
} CEGUID;

typedef CEGUID *PCEGUID;   /* pointer form used by every page print */
typedef CEOID *PCEOID;     /* aa517213 CeOpenDatabase print */

/* --- Database macros (verbatim prints). -----------------------------
 *
 * aa517295 "CHECK_INVALIDGUID (Windows CE 5.0)": the archive print
 * glues the macro name to its `!~((pguid)->...` body; spacing
 * restored.  CE 2.10+; Windbase.h. */
#define CHECK_INVALIDGUID(pguid) \
    (!~((pguid)->Data1 & (pguid)->Data2 & \
        (pguid)->Data3 & (pguid)->Data4))

/* aa517298 "CHECK_SYSTEMGUID (Windows CE 5.0)": CE 2.10+. */
#define CHECK_SYSTEMGUID(pguid) \
    (!((pguid)->Data1 | (pguid)->Data2 | \
        (pguid)->Data3 | (pguid)->Data4))

/* aa517332 "CREATE_INVALIDGUID (Windows CE 5.0)": CE 2.10+.  The
 * macro body is memset((pguid), -1, sizeof(CEGUID)) verbatim; the
 * caller's environment must provide memset (the CRT on device). */
#define CREATE_INVALIDGUID(pguid) (memset((pguid), -1, sizeof(CEGUID)))

/* aa517336 "CREATE_SYSTEMGUID (Windows CE 5.0)": CE 2.10+. */
#define CREATE_SYSTEMGUID(pguid) (memset((pguid), 0, sizeof(CEGUID)))

/* ms892256 "TypeFromPropID (Windows CE 5.0)": CE 1.0+.  The page
 * prints `#define TypeFromPropID(propid) LOWORD(propid)` verbatim,
 * but no CE page in the harvest defines LOWORD (the generic macro
 * is not in the CE archive), so the low-order-word extraction is
 * provided as a private helper instead of importing a desktop
 * LOWORD: the page describes the macro as extracting the low-order
 * word of the property ID and WORD is 16 bits (windef.h), hence
 * the 0xffff mask (derivation recorded, replace on an official
 * print). */
#define AKARI_WINDBASE_LOWORD(w) ((WORD)((DWORD)(w) & 0xffffu))
#define TypeFromPropID(propid) AKARI_WINDBASE_LOWORD(propid)

/* --- CEDB structures (compiled, verbatim prints). -------------------
 *
 * aa516981 "CEBLOB (Windows CE 5.0)": CE 1.01+; Windbase.h.  The
 * archive print glues `DWORDdwCount;LPBYTElpb;` -- spacing restored. */
typedef struct _CEBLOB {
    DWORD dwCount;
    LPBYTE lpb;
} CEBLOB;

/* aa517283 "CEVALUNION (Windows CE 5.0)": CE 1.01+; Windbase.h.
 * Verbatim (scalar member spellings `short`/`long` kept as printed). */
typedef union _CEVALUNION {
    short     iVal;
    USHORT    uiVal;
    long      lVal;
    ULONG     ulVal;
    FILETIME  filetime;
    LPWSTR    lpwstr;
    CEBLOB    blob;
    BOOL      boolVal;
    double    dblVal;
} CEVALUNION;

/* aa517227 "CEPROPVAL (Windows CE 5.0)": CE 1.01+; Windbase.h. */
typedef struct _CEPROPVAL {
    CEPROPID   propid;
    WORD       wLenData;
    WORD       wFlags;
    CEVALUNION val;
} CEPROPVAL;

/* aa517237 "CERECORDINFO (Windows CE 5.0)": CE 1.01+; Windbase.h. */
typedef struct _CERECORDINFO {
    CEOID oidParent;
} CERECORDINFO;

/* ms891997 "SORTORDERSPEC (Windows CE 5.0)": CE 1.0+; Windbase.h. */
typedef struct _SORTORDERSPEC {
    CEPROPID propid;
    DWORD    dwFlags;
} SORTORDERSPEC;

/* aa517101 "CEFILEINFO (Windows CE 5.0)": CE 1.01+; Windbase.h.
 * szFileName is MAX_PATH wide (MAX_PATH = 260, windef.h). */
typedef struct _CEFILEINFO {
    DWORD    dwAttributes;
    CEOID    oidParent;
    WCHAR    szFileName[MAX_PATH];
    FILETIME ftLastChanged;
    DWORD    dwLength;
} CEFILEINFO;

/* aa517001 "CEDIRINFO (Windows CE 5.0)": CE 1.01+; Windbase.h. */
typedef struct _CEDIRINFO {
    DWORD dwAttributes;
    CEOID oidParent;
    WCHAR szDirName[MAX_PATH];
} CEDIRINFO;

/* aa517186 "CENOTIFICATION (Windows CE 5.0)": CE 2.10+; Windbase.h. */
typedef struct _CENOTIFICATION {
    DWORD dwSize;
    DWORD dwParam;
    UINT  uType;
    CEGUID guid;
    CEOID oid;
    CEOID oidParent;
} CENOTIFICATION;
typedef CENOTIFICATION *PCENOTIFICATION;

/* aa517189 "CENOTIFYREQUEST (Windows CE 5.0)": CE 2.10+; Windbase.h. */
typedef struct _CENOTIFYREQUEST {
    DWORD dwSize;
    HWND  hwnd;
    DWORD dwFlags;
    HANDLE hHeap;
    DWORD dwParam;
} CENOTIFYREQUEST;
typedef CENOTIFYREQUEST *PCENOTIFYREQUEST;

/* --- CEDB structures held as incomplete types (layout unpublished).-
 *
 * The four array-length constants these structures need
 * (CEDB_MAXDBASENAMELEN, CEDB_MAXSORTORDER, CEDB_MAXSORTPROP,
 * CCH_MAX_PASSWORD) are not printed with values on ANY harvested CE
 * page, so the layouts cannot be compiled without inventing ABI.
 * The tags below ARE printed, so pointer-only use (exactly how the
 * documented signatures use them) compiles; the verbatim prints are
 * recorded for the day the values are confirmed.
 *
 * aa516991 "CEDBASEINFO (Windows CE 5.0)" -- CE 1.01+; verbatim:
 *   typedef struct _CEDBASEINFO {
 *     DWORD dwFlags;
 *     WCHAR szDbaseName[CEDB_MAXDBASENAMELEN];
 *     DWORD dwDbaseType; WORD wNumRecords; WORD wNumSortOrder;
 *     DWORD dwSize; FILETIME ftLastModified;
 *     SORTORDERSPEC rgSortSpecs[CEDB_MAXSORTORDER];
 *   } CEDBASEINFO;
 */
typedef struct _CEDBASEINFO CEDBASEINFO;

/* aa516992 "CEDBASEINFOEX (CEDB) (Windows CE 5.0)" -- CE .NET 4.0+;
 * verbatim print:
 *   typedef struct _CEDBASEINFOEX { WORD wVersion; DWORD dwFlags;
 *     WCHAR szDbaseName[CEDB_MAXDBASENAMELEN]; DWORD dwDbaseType;
 *     DWORD dwNumRecords; WORD wNumSortOrder; DWORD dwSize;
 *     FILETIME ftLastModified;
 *     SORTORDERSPECEX rgSortSpecs[CEDB_MAXSORTORDER];
 *   } CEDBASEINFOEX;
 * TWIN CONFLICT: the EDB twin page aa516993 (CE 5.0+) prints a
 * DIFFERENT member order (wVersion, wNumSortOrder, dwFlags, ...) and
 * no struct tag, so the two CE 5.0 pages cannot both be the layout.
 * TWIN CHECK (M71a): the CE 6.0 twins ee490380 (CEDB) and ee490234
 * (EDB) print the SAME body for both -- the CE 5.0 EDB order
 * (wVersion, wNumSortOrder, dwFlags, ...) -- making the CE 5.0 CEDB
 * print aa516992 the outlier.  Recorded; body still unpublished
 * (array sizes), both CE 5.0 prints kept above. */
typedef struct _CEDBASEINFOEX CEDBASEINFOEX;

/* ms892001 "SORTORDERSPECEX (CEDB) (Windows CE 5.0)" -- CE .NET 4.0+;
 * verbatim:
 *   typedef struct _SORTORDERSPECEX { WORD wVersion; WORD wNumProps;
 *     WORD wKeyFlags; CEPROPID rgPropID[CEDB_MAXSORTPROP];
 *     DWORD rgdwFlags[CEDB_MAXSORTPROP];
 *   } SORTORDERSPECEX;
 */
typedef struct _SORTORDERSPECEX SORTORDERSPECEX;
/* CROSS-GENERATION (M86 sweep): CE 5.0 twin ms892010 prints the tag
 * `CESORTORDERSPECEX` with `WORD wReserved;` between wKeyFlags and
 * rgPropID and the archive typo `DWROD rgdwFlags[...]` (DWORD); the
 * CE 6.0 twin ee490012 corroborates that shape (wReserved present,
 * DWORD rgdwFlags, tag CESORTORDERSPECEX).  The ms892001 print above
 * lacks wReserved -- intra-CE 5.0 twin conflict, recorded. */

/* aa517207 "CEOIDINFO (Windows CE 5.0)" -- CE 1.01+; verbatim:
 *   typedef struct _CEOIDINFO { WORD wObjType; WORD wPad;
 *     union { CEFILEINFO infFile; CEDIRINFO infDirectory;
 *       CEDBASEINFO infDatabase; CERECORDINFO infRecord; };
 *   } CEOIDINFO;
 */
typedef struct _CEOIDINFO CEOIDINFO;

/* aa517208 "CEOIDINFOEX (CEDB) (Windows CE 5.0)" -- CE .NET 4.0+;
 * verbatim:
 *   typedef struct _CEOIDINFOEX { WORD wVersion; WORD wObjType;
 *     union { CEFILEINFO infFile; CEDIRINFO infDirectory;
 *       CEDBASEINFOEX infDatabase; CERECORDINFO infRecord; };
 *   } CEOIDINFOEX;
 * TWIN CONFLICT: the EDB twin aa517210 (CE 5.0+) prints the same
 * shape but its union member is CEDBASEINFO (not ...EX) -- recorded;
 * body unpublished. */
typedef struct _CEOIDINFOEX CEOIDINFOEX;

/* CROSS-GENERATION (M86 sweep): the CE 6.0 twin ee490409 inserts
 * `WORD wReserved;` after wVersion and prints no pointer typedef;
 * the CE 4.0 twin ms923774 matches the CE 5.0 form above.  Recorded
 * (CE generations kept distinct). */
/* aa516972 "BY_HANDLE_DB_INFORMATION (CEDB) (Windows CE 5.0)" --
 * CE .NET 4.0+; verbatim:
 *   typedef struct _BY_HANDLE_DB_INFORMATION { WORD wVersion;
 *     CEGUID guidVol; CEOID oidDbase; CEDBASEINFOEX infDatabase;
 *   } BY_HANDLE_DB_INFORMATION;
 * Held incomplete: CEDBASEINFOEX layout unpublished (see above).
 * TWIN NOTE (M71a): the EDB prints are NOT identical -- aa516974
 * (CE 5.0) and ee490409 (CE 6.0) both add `WORD wReserved;` after
 * wVersion, while the CEDB prints (aa516972, ee490788) do not; the
 * CE 5.0 EDB print:
 *   typedef struct BY_HANDLE_DB_INFORMATION { WORD wVersion;
 *     WORD wReserved; CEGUID guidVol; CEOID oidDbase;
 *     CEDBASEINFOEX infDatabase; } BY_HANDLE_DB_INFORMATION; */
typedef struct _BY_HANDLE_DB_INFORMATION BY_HANDLE_DB_INFORMATION;
typedef BY_HANDLE_DB_INFORMATION *LPBY_HANDLE_DB_INFORMATION;

/* --- CEDB functions (Coredll.lib on every page). --------------------
 * Archive prints frequently glue the return type / parameter type to
 * the following identifier (e.g. `CEOIDCeCreateDatabase`,
 * `PCEGUIDpceguid`); spacing is restored, nothing else is changed.
 * Obsolete-in-doc functions are kept (their pages still document
 * the exports). */

/* aa516985 "CeCreateDatabase (Windows CE 5.0)": CE 1.01+. */
AKARI_CE_IMPORT CEOID CeCreateDatabase(LPWSTR lpszName, DWORD dwDbaseType,
                    WORD wNumSortOrder,
                    SORTORDERSPEC *rgSortSpecs) AKARI_CE_NAME(CeCreateDatabase);

/* aa516986 "CeCreateDatabaseEx (CEDB) (Windows CE 5.0)": CE 2.10+. */
AKARI_CE_IMPORT CEOID CeCreateDatabaseEx(PCEGUID pceguid,
                    CEDBASEINFO *lpCEDBInfo) AKARI_CE_NAME(CeCreateDatabaseEx);

/* aa516987 "CeCreateDatabaseEx2 (CEDB) (Windows CE 5.0)": CE .NET 4.0+. */
AKARI_CE_IMPORT CEOID CeCreateDatabaseEx2(PCEGUID pguid,
                    CEDBASEINFOEX *pInfo) AKARI_CE_NAME(CeCreateDatabaseEx2);

/* aa516982 "CeChangeDatabaseLCID (CEDB) (Windows CE 5.0)": CE 2.10+.
 * This is the ONE page whose Header row prints Pwindbas.h (the
 * include/Pwindbas.h alias).  The CEDB print's second parameter is
 * `DWORDLCID` (capitalised by the archive); the EDB twin aa516983
 * prints the same shape as `DWORDlcid`. */
AKARI_CE_IMPORT VOID CeChangeDatabaseLCID(PCEGUID pceguid,
                    DWORD lcid) AKARI_CE_NAME(CeChangeDatabaseLCID);

/* aa516994 "CeDeleteDatabase (CEDB) (Windows CE 5.0)": CE 1.01+. */
AKARI_CE_IMPORT BOOL CeDeleteDatabase(CEOID oidDbase) AKARI_CE_NAME(CeDeleteDatabase);

/* aa516996 "CeDeleteDatabaseEx (CEDB) (Windows CE 5.0)": CE 2.10+. */
AKARI_CE_IMPORT BOOL CeDeleteDatabaseEx(PCEGUID pguid,
                    CEOID oid) AKARI_CE_NAME(CeDeleteDatabaseEx);

/* aa516997 "CeDeleteRecord (CEDB) (Windows CE 5.0)": CE 1.01+. */
AKARI_CE_IMPORT BOOL CeDeleteRecord(HANDLE hDatabase,
                    CEOID oidRecord) AKARI_CE_NAME(CeDeleteRecord);

/* aa517003 "CeEnumDBVolumes (CEDB) (Windows CE 5.0)": CE 2.10+. */
AKARI_CE_IMPORT BOOL CeEnumDBVolumes(PCEGUID pceguid, LPWSTR lpBuf,
                    DWORD dwNumChars) AKARI_CE_NAME(CeEnumDBVolumes);

/* aa517106 "CeFindFirstDatabase (CEDB) (Windows CE 5.0)": CE 1.01+. */
AKARI_CE_IMPORT HANDLE CeFindFirstDatabase(DWORD dwDbaseType) AKARI_CE_NAME(CeFindFirstDatabase);

/* aa517109 "CeFindFirstDatabaseEx (CEDB) (Windows CE 5.0)": CE 2.10+. */
AKARI_CE_IMPORT HANDLE CeFindFirstDatabaseEx(PCEGUID pceguid,
                    DWORD dwDbaseType) AKARI_CE_NAME(CeFindFirstDatabaseEx);

/* aa517118 "CeFindNextDatabase (CEDB) (Windows CE 5.0)": CE 1.01+. */
AKARI_CE_IMPORT CEOID CeFindNextDatabase(HANDLE hEnum) AKARI_CE_NAME(CeFindNextDatabase);

/* aa517120 "CeFindNextDatabaseEx (CEDB) (Windows CE 5.0)": CE 2.10+. */
AKARI_CE_IMPORT CEOID CeFindNextDatabaseEx(HANDLE hEnum,
                    PCEGUID pceguid) AKARI_CE_NAME(CeFindNextDatabaseEx);

/* aa517128 "CeFlushDBVol (CEDB) (Windows CE 5.0)": CE 2.10+. */
AKARI_CE_IMPORT BOOL CeFlushDBVol(PCEGUID pceguid) AKARI_CE_NAME(CeFlushDBVol);

/* aa517132 "CeFreeNotification (CEDB) (Windows CE 5.0)": CE 2.10+. */
AKARI_CE_IMPORT BOOL CeFreeNotification(PCENOTIFYREQUEST pRequest,
                    PCENOTIFICATION pNotify) AKARI_CE_NAME(CeFreeNotification);

/* aa517152 "CeGetDBInformationByHandle (CEDB) (Windows CE 5.0)":
 * CE .NET 4.0+.  (The EDB twin aa517155 prints the same shape with
 * `BY_HANDLE_DB_INFORMATION* lpDBInfo`.) */
AKARI_CE_IMPORT BOOL CeGetDBInformationByHandle(HANDLE hDbase,
                    LPBY_HANDLE_DB_INFORMATION lpDBInfo) AKARI_CE_NAME(CeGetDBInformationByHandle);

/* aa517177 "CeMountDBVol (CEDB) (Windows CE 5.0)": CE 2.10+. */
AKARI_CE_IMPORT BOOL CeMountDBVol(PCEGUID pceguid, LPWSTR lpszDBVol,
                    DWORD dwFlags) AKARI_CE_NAME(CeMountDBVol);

/* aa517194 "CeOidGetInfo (CEDB) (Windows CE 5.0)": CE 1.01+;
 * documented obsolete in favor of CeOidGetInfoEx2. */
AKARI_CE_IMPORT BOOL CeOidGetInfo(CEOID oid,
                    CEOIDINFO *poidInfo) AKARI_CE_NAME(CeOidGetInfo);

/* aa517197 "CeOidGetInfoEx (CEDB) (Windows CE 5.0)": CE 2.10+;
 * documented obsolete in favor of CeOidGetInfoEx2. */
AKARI_CE_IMPORT BOOL CeOidGetInfoEx(PCEGUID pceguid, CEOID oid,
                    CEOIDINFO *poidInfo) AKARI_CE_NAME(CeOidGetInfoEx);

/* aa517198 "CeOidGetInfoEx2 (CEDB) (Windows CE 5.0)": CE .NET 4.0+.
 * TWIN CONFLICT: the EDB twin page aa517204 (CE 5.0+) prints the
 * third parameter as `CEOIDINFO* poidInfo` while this CEDB page
 * prints `CEOIDINFOEX*`; the declaring prototype follows the CEDB
 * page (the name's origin, CE .NET 4.0) and both are recorded. */
AKARI_CE_IMPORT BOOL CeOidGetInfoEx2(PCEGUID pceguid, CEOID oid,
                    CEOIDINFOEX *poidInfo) AKARI_CE_NAME(CeOidGetInfoEx2);

/* aa517213 "CeOpenDatabase (CEDB) (Windows CE 5.0)": CE 1.01+. */
AKARI_CE_IMPORT HANDLE CeOpenDatabase(PCEOID poid, LPWSTR lpszName,
                    CEPROPID propid, DWORD dwFlags,
                    HWND hwndNotify) AKARI_CE_NAME(CeOpenDatabase);

/* aa517216 "CeOpenDatabaseEx (CEDB) (Windows CE 5.0)": CE 2.10+. */
AKARI_CE_IMPORT HANDLE CeOpenDatabaseEx(PCEGUID pceguid, PCEOID poid,
                    LPWSTR lpszName, CEPROPID propid, DWORD dwFlags,
                    CENOTIFYREQUEST *pReq) AKARI_CE_NAME(CeOpenDatabaseEx);

/* aa517218 "CeOpenDatabaseEx2 (CEDB) (Windows CE 5.0)": CE .NET 4.0+. */
AKARI_CE_IMPORT HANDLE CeOpenDatabaseEx2(PCEGUID pguid, PCEOID poid,
                    LPWSTR lpszName, SORTORDERSPECEX *psort, DWORD dwFlags,
                    CENOTIFYREQUEST *pRequest) AKARI_CE_NAME(CeOpenDatabaseEx2);

/* aa517229 "CeReadRecordProps (CEDB) (Windows CE 5.0)": CE 2.10+. */
AKARI_CE_IMPORT CEOID CeReadRecordProps(HANDLE hDbase, DWORD dwFlags,
                    LPWORD lpcPropID, CEPROPID *rgPropID, LPBYTE *lplpBuffer,
                    LPDWORD lpcbBuffer) AKARI_CE_NAME(CeReadRecordProps);

/* aa517235 "CeReadRecordPropsEx (CEDB) (Windows CE 5.0)": CE 2.10+. */
AKARI_CE_IMPORT CEOID CeReadRecordPropsEx(HANDLE hDbase, DWORD dwFlags,
                    LPWORD lpcPropID, CEPROPID *rgPropID, LPBYTE *lplpBuffer,
                    LPDWORD lpcbBuffer,
                    HANDLE hHeap) AKARI_CE_NAME(CeReadRecordPropsEx);

/* aa517246 "CeSeekDatabase (CEDB) (Windows CE 5.0)": CE 1.01+.
 * dwSeekType takes the CEDB_SEEK_* constants (names recorded below,
 * values unpublished). */
AKARI_CE_IMPORT CEOID CeSeekDatabase(HANDLE hDatabase, DWORD dwSeekType,
                    DWORD dwValue,
                    LPDWORD lpdwIndex) AKARI_CE_NAME(CeSeekDatabase);

/* aa517251 "CeSeekDatabaseEx (CEDB) (Windows CE 5.0)": CE .NET 4.0+. */
AKARI_CE_IMPORT CEOID CeSeekDatabaseEx(HANDLE hDatabase, DWORD dwSeekType,
                    DWORD dwValue, WORD wNumVals,
                    LPDWORD lpdwIndex) AKARI_CE_NAME(CeSeekDatabaseEx);

/* aa517254 "CeSetDatabaseInfo (CEDB) (Windows CE 5.0)": CE 1.01+. */
AKARI_CE_IMPORT BOOL CeSetDatabaseInfo(CEOID oidDbase,
                    CEDBASEINFO *pNewInfo) AKARI_CE_NAME(CeSetDatabaseInfo);

/* aa517258 "CeSetDatabaseInfoEx (CEDB) (Windows CE 5.0)": CE 2.10+. */
AKARI_CE_IMPORT BOOL CeSetDatabaseInfoEx(PCEGUID pceguid, CEOID oidDbase,
                    CEDBASEINFO *pNewInfo) AKARI_CE_NAME(CeSetDatabaseInfoEx);

/* aa517259 "CeSetDatabaseInfoEx2 (CEDB) (Windows CE 5.0)":
 * CE .NET 4.0+. */
AKARI_CE_IMPORT BOOL CeSetDatabaseInfoEx2(PCEGUID pguid, CEOID oidDbase,
                    CEDBASEINFOEX *pNewInfo) AKARI_CE_NAME(CeSetDatabaseInfoEx2);

/* aa517280 "CeUnmountDBVol (CEDB) (Windows CE 5.0)": CE 2.10+. */
AKARI_CE_IMPORT BOOL CeUnmountDBVol(PCEGUID pceguid) AKARI_CE_NAME(CeUnmountDBVol);

/* aa517285 "CeWriteRecordProps (CEDB) (Windows CE 5.0)": CE 1.01+. */
AKARI_CE_IMPORT CEOID CeWriteRecordProps(HANDLE hDbase, CEOID oidRecord,
                    WORD cPropID,
                    CEPROPVAL *rgPropVal) AKARI_CE_NAME(CeWriteRecordProps);

/* --- Database messages (names recorded; values unpublished). --------
 *
 * The Database Messages book pages document WM_DBNOTIFICATION and
 * the DB_CEOID_* notification values carried in its WPARAM, but no
 * page prints a numeric value for any of them, so none is defined
 * (zero-gap policy; they are recorded here for the day values are
 * confirmed):
 *   ms892379 WM_DBNOTIFICATION            CE 2.10+ (posted message)
 *   aa517338 DB_CEOID_CHANGED             CE 1.01+
 *   aa517339 DB_CEOID_CREATED             CE 1.01+
 *   aa517340 DB_CEOID_DATABASE_DELETED    CE 1.01+
 *   aa517341 DB_CEOID_DIRECTORY_DELETED   CE 1.01+
 *   ms887719 DB_CEOID_FILE_DELETED        CE 1.01+
 *   ms887825 DB_CEOID_RECORD_DELETED      CE 1.01+
 */

/* --- Flag constants (names recorded; values unpublished). -----------
 *
 * No CE page prints numeric values for any of these families (all
 * 6422 harvested pages scanned); the names appear on the cited pages
 * as parameter/flag documentation.  Nothing is invented; the lists
 * are recorded so the surface is traceable:
 *
 * CEVT_* property value types (aa517227 CEPROPVAL et al.):
 *   CEVT_I2 CEVT_UI2 CEVT_I4 CEVT_UI4 CEVT_FILETIME CEVT_LPWSTR
 *   CEVT_BOOL CEVT_R8 CEVT_BLOB CEVT_STREAM (EDB stream property,
 *   aa516932/aa516979/aa516989)
 * CEDB volume/database flags (aa516991/aa516992/aa516993/aa517254):
 *   CEDB_VALID CEDB_VALIDNAME CEDB_VALIDTYPE CEDB_VALIDSORTSPEC
 *   CEDB_VALIDDBFLAGS CEDB_VALIDMODTIME CEDB_SYSTEMDB CEDB_NOCOMPRESS
 * CEDB open/record flags (aa517213/aa517229/aa517227/aa517285):
 *   CEDB_AUTOINCREMENT CEDB_ALLOWREALLOC CEDB_PROPDELETE
 *   CEDB_PROPNOTFOUND CEDB_EXNOTIFICATION (aa517189)
 * CEDB_SEEK_* seek types (aa517246/aa517250/aa517251/aa517253):
 *   CEDB_SEEK_BEGINNING CEDB_SEEK_CURRENT CEDB_SEEK_END
 *   CEDB_SEEK_CEOID CEDB_SEEK_PREFIX CEDB_SEEK_VALUEFIRSTEQUAL
 *   CEDB_SEEK_VALUENEXTEQUAL CEDB_SEEK_VALUEGREATER
 *   CEDB_SEEK_VALUEGREATEROREQUAL CEDB_SEEK_VALUESMALLER
 *   CEDB_SEEK_VALUESMALLEROREQUAL
 * CEDB_SORT_* sort-order flags (ms891997/ms892001/ms892010):
 *   CEDB_SORT_DESCENDING CEDB_SORT_CASEINSENSITIVE
 *   CEDB_SORT_IGNORENONSPACE CEDB_SORT_IGNOREKANATYPE
 *   CEDB_SORT_IGNOREWIDTH CEDB_SORT_IGNORESYMBOLS CEDB_SORT_UNKNOWNFIRST
 *   CEDB_SORT_NONNULL CEDB_SORT_UNIQUE CEDB_SORT_PRIMARYKEY (EDB)
 *   CEDB_SORT_NO_POSITIONAL (EDB)
 * CEVOLUMEOPTIONS flags + limits (aa516924, EDB):
 *   CEDB_BUFFERPOOL CEDB_AUTOSHRINKPERCENT CEDB_FLUSHINTERVAL
 *   CEDB_MAXNOTIFYCHANGES CEDB_DEFAULTTIMEOUT CEDB_PASSWORD
 * Array-size constants (struct members above):
 *   CEDB_MAXDBASENAMELEN CEDB_MAXSORTORDER CEDB_MAXSORTPROP
 *   CCH_MAX_PASSWORD
 */

/* ================= EDB (Windows CE 5.0 and later) ================= */
#if !defined(_WIN32_WCE) || (_WIN32_WCE) >= 0x500

/* CEDBISOLATIONLEVEL: referenced by value by CeBeginTransaction
 * (aa516980) but no CE page prints the enum or its values.  Closure
 * `int` (the C enum carrier on the 32-bit CE ABI); the documented
 * names -- CEDB_ISOLEVEL_DEFAULT, CEDB_ISOLEVEL_READCOMMITTED,
 * CEDB_ISOLEVEL_REPEATABLEREAD, CEDB_ISOLEVEL_SERIALIZABLE
 * (aa516980 remarks) -- are recorded, values not invented. */
typedef int CEDBISOLATIONLEVEL;

/* aa517225 "CEPROPSPEC (EDB) (Windows CE 5.0)": CE 5.0+; Windbase.h.
 * Verbatim (no tag printed; the self-named struct form is kept). */
typedef struct CEPROPSPEC {
    WORD     wVersion;
    CEPROPID propid;
    DWORD    dwFlags;
    LPWSTR   pwszPropName;
    DWORD    cchPropName;
} CEPROPSPEC;

/* ms892010 "SORTORDERSPECEX (EDB) (Windows CE 5.0)": CE 5.0+.  The
 * EDB print names the type CESORTORDERSPECEX (distinct from the
 * CEDB SORTORDERSPECEX) and prints `DWROD rgdwFlags[...]` -- the
 * page's own typo for DWORD; the CE 6.0 twin ee490012 prints DWORD
 * there (typo repaired upstream).  The layout is held
 * (CEDB_MAXSORTPROP unpublished), tag from the print:
 *   typedef struct CESORTORDERSPECEX { WORD wVersion; WORD
 *     wNumProps; WORD wKeyFlags; WORD wReserved;
 *     CEPROPID rgPropID[CEDB_MAXSORTPROP];
 *     DWROD rgdwFlags[CEDB_MAXSORTPROP];
 *   } CESORTORDERSPECEX;
 */
typedef struct CESORTORDERSPECEX CESORTORDERSPECEX;

/* aa516924 "CEVOLUMEOPTIONS (EDB) (Windows CE 5.0)": CE 5.0+.  Held
 * (CCH_MAX_PASSWORD unpublished); verbatim print:
 *   typedef struct CEVOLUMEOPTIONS { WORD wVersion;
 *     DWORD cbBufferPool; DWORD dwAutoShrinkPercent;
 *     DWORD dwFlushInterval; DWORD cMaxNotifyChanges;
 *     DWORD dwDefaultTimeout; WCHAR wszPassword[CCH_MAX_PASSWORD + 1];
 *     DWORD dwFlags; } CEVOLUMEOPTIONS;
 */
typedef struct CEVOLUMEOPTIONS CEVOLUMEOPTIONS;

/* --- EDB functions (Coredll.lib on every page; CE 5.0+). ------------ */

/* aa516979 "CeAddDatabaseProps (EDB) (Windows CE 5.0)". */
AKARI_CE_IMPORT BOOL CeAddDatabaseProps(PCEGUID pGuid, CEOID oidDb,
                    DWORD cProps,
                    CEPROPSPEC *prgProps) AKARI_CE_NAME(CeAddDatabaseProps);

/* aa516980 "CeBeginTransaction (EDB) (Windows CE 5.0)". */
AKARI_CE_IMPORT BOOL CeBeginTransaction(HANDLE hSession,
                    CEDBISOLATIONLEVEL isoLevel) AKARI_CE_NAME(CeBeginTransaction);

/* aa516983 "CeChangeDatabaseLCID (EDB) (Windows CE 5.0)": same-name
 * EDB twin of the CEDB declaration above (identical shape). */

/* aa516988 "CeCreateDatabaseEx2 (EDB) (Windows CE 5.0)": same-name
 * EDB twin of the CEDB declaration above (identical shape). */

/* aa516989 "CeCreateDatabaseWithProps (EDB) (Windows CE 5.0)". */
AKARI_CE_IMPORT CEOID CeCreateDatabaseWithProps(PCEGUID pGuid,
                    CEDBASEINFOEX *pInfo, DWORD cProps,
                    CEPROPSPEC *prgProps) AKARI_CE_NAME(CeCreateDatabaseWithProps);

/* aa516990 "CeCreateSession (EDB) (Windows CE 5.0)". */
AKARI_CE_IMPORT HANDLE CeCreateSession(CEGUID *pGuid) AKARI_CE_NAME(CeCreateSession);

/* aa516995 "CeDeleteDatabase (EDB) (Windows CE 5.0)": same-name EDB
 * twin (shape identical, parameter printed `oid`). */

/* aa516998 "CeDeleteRecord (EDB) (Windows CE 5.0)": same-name EDB
 * twin (identical shape). */

/* aa517002 "CeEndTransaction (EDB) (Windows CE 5.0)". */
AKARI_CE_IMPORT BOOL CeEndTransaction(HANDLE hSession,
                    BOOL fCommit) AKARI_CE_NAME(CeEndTransaction);

/* aa517004 "CeEnumDBVolumes (EDB) (Windows CE 5.0)": same-name EDB
 * twin (parameters printed pwszName/cchMaxName). */

/* aa517114 "CeFindFirstDatabaseEx (EDB) (Windows CE 5.0)": same-name
 * EDB twin (parameter printed pGuid). */

/* aa517122 "CeFindNextDatabaseEx (EDB) (Windows CE 5.0)": same-name
 * EDB twin (parameter printed pGuid). */

/* aa517130 "CeFlushDBVol (EDB) (Windows CE 5.0)": same-name EDB twin. */

/* aa517135 "CeFreeNotification (EDB) (Windows CE 5.0)": same-name
 * EDB twin (pointer parameters printed as CENOTIFYREQUEST and
 * CENOTIFICATION pointers). */

/* aa517146 "CeGetDatabaseProps (EDB) (Windows CE 5.0)".  (The print
 * carries a stray space in `CeGetDatabaseProps (`; normalized.) */
AKARI_CE_IMPORT BOOL CeGetDatabaseProps(HANDLE hDatabase, LPWORD lpcPropID,
                    CEPROPID *prgPropID,
                    CEPROPSPEC *prgProps) AKARI_CE_NAME(CeGetDatabaseProps);

/* aa517147 "CeGetDatabaseSession (EDB) (Windows CE 5.0)". */
AKARI_CE_IMPORT HANDLE CeGetDatabaseSession(HANDLE hDatabase) AKARI_CE_NAME(CeGetDatabaseSession);

/* aa517155 "CeGetDBInformationByHandle (EDB) (Windows CE 5.0)":
 * same-name EDB twin (pointer form printed BY_HANDLE_DB_INFORMATION*). */

/* aa517180 "CeMountDBVol (EDB) (Windows CE 5.0)": same-name EDB twin. */

/* aa517182 "CeMountDBVolEx (EDB) (Windows CE 5.0)". */
AKARI_CE_IMPORT BOOL CeMountDBVolEx(PCEGUID pGuid, LPWSTR lpwszDBVol,
                    CEVOLUMEOPTIONS *pOptions,
                    DWORD dwFlags) AKARI_CE_NAME(CeMountDBVolEx);

/* aa517204 "CeOidGetInfoEx2 (EDB) (Windows CE 5.0)": same-name EDB
 * twin; see the TWIN CONFLICT note on the CEDB declaration above. */

/* aa517220 "CeOpenDatabaseInSession (EDB) (Windows CE 5.0)". */
AKARI_CE_IMPORT HANDLE CeOpenDatabaseInSession(HANDLE hSession, PCEGUID pGuid,
                    PCEOID poid, LPWSTR lpwszName, SORTORDERSPECEX *pSort,
                    DWORD dwFlags,
                    CENOTIFYREQUEST *pRequest) AKARI_CE_NAME(CeOpenDatabaseInSession);

/* aa517223 "CeOpenStream (EDB) (Windows CE 5.0)". */
AKARI_CE_IMPORT HANDLE CeOpenStream(HANDLE hDatabase, CEPROPID propid,
                    DWORD dwMode) AKARI_CE_NAME(CeOpenStream);

/* aa517232 "CeReadRecordProps (EDB) (Windows CE 5.0)": same-name EDB
 * twin (identical shape). */

/* aa517236 "CeReadRecordPropsEx (EDB) (Windows CE 5.0)": same-name
 * EDB twin (identical shape). */

/* aa517242 "CeRemoveDatabaseProps (EDB) (Windows CE 5.0)". */
AKARI_CE_IMPORT BOOL CeRemoveDatabaseProps(PCEGUID pGuid, CEOID oidDb,
                    DWORD cProps,
                    CEPROPID *prgProps) AKARI_CE_NAME(CeRemoveDatabaseProps);

/* aa517250 "CeSeekDatabase (EDB) (Windows CE 5.0)": same-name EDB
 * twin (parameter printed hDatabase). */

/* aa517253 "CeSeekDatabaseEx (EDB) (Windows CE 5.0)": same-name EDB
 * twin (adds the EDB CEDB_SEEK_PREFIX / CEDB_SEEK_VALUEGREATEROREQUAL
 * / CEDB_SEEK_VALUESMALLEROREQUAL seek types, names recorded above). */

/* aa517256 "CeSetDatabaseInfo (EDB) (Windows CE 5.0)": same-name EDB
 * twin (identical shape). */

/* aa517268 "CeSetSessionOption (EDB) (Windows CE 5.0)". */
AKARI_CE_IMPORT BOOL CeSetSessionOption(HANDLE hSession, ULONG ulOptionId,
                    DWORD dwValue) AKARI_CE_NAME(CeSetSessionOption);

/* aa517270 "CeStreamRead (EDB) (Windows CE 5.0)". */
AKARI_CE_IMPORT BOOL CeStreamRead(HANDLE hStream, LPBYTE lprgbBuffer,
                    DWORD cbRead,
                    LPDWORD lpcbRead) AKARI_CE_NAME(CeStreamRead);

/* aa517272 "CeStreamSaveChanges (EDB) (Windows CE 5.0)". */
AKARI_CE_IMPORT BOOL CeStreamSaveChanges(HANDLE hStream) AKARI_CE_NAME(CeStreamSaveChanges);

/* aa517274 "CeStreamSeek (EDB) (Windows CE 5.0)". */
AKARI_CE_IMPORT BOOL CeStreamSeek(HANDLE hStream, DWORD cbMove,
                    DWORD dwOrigin,
                    LPDWORD lpcbNewOffset) AKARI_CE_NAME(CeStreamSeek);

/* aa517275 "CeStreamSetSize (EDB) (Windows CE 5.0)". */
AKARI_CE_IMPORT BOOL CeStreamSetSize(HANDLE hStream, DWORD cbSize) AKARI_CE_NAME(CeStreamSetSize);

/* aa517278 "CeStreamWrite (EDB) (Windows CE 5.0)". */
AKARI_CE_IMPORT BOOL CeStreamWrite(HANDLE hStream, LPBYTE lprgbBuffer,
                    DWORD cbWrite,
                    LPDWORD lpcbWritten) AKARI_CE_NAME(CeStreamWrite);

/* aa517282 "CeUnmountDBVol (EDB) (Windows CE 5.0)": same-name EDB twin. */

/* aa517288 "CeWriteRecordProps (EDB) (Windows CE 5.0)": same-name
 * EDB twin (parameters printed hDatabase/prgPropVal). */

#endif /* EDB: _WIN32_WCE >= 0x500 (or undefined) */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WINDBASE_H */
