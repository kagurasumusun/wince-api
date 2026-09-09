/*
 * Bthsdpdef.h -- Bluetooth SDP definitions for Windows CE (Bthsdpdef.h layer).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  Source books: CE 5.0 "Bluetooth Application Development" (the
 * enumerations and structures of tools/manifests/bt-appdev.manifest,
 * fetched M57; CE 6.0 twins in build/pages6 cross-read where the CE 5.0
 * print is damaged).  OS Versions: "Windows CE .NET 4.0 and later".
 *
 * The structure pages carry no Link Library row, so no def is generated
 * for this header (no import surface is documented).
 *
 * Held families (names documented, values/bodies not published in the
 * official CE documentation -- see docs/inventory.md M57):
 *   - the GET_NAP / GET_SAP / SET_NAP_SAP macros of the SOCKADDR_BTH page
 *     (aa450944) are printed comment-only, with no macro bodies.
 * Derived values are marked with their derivation path below.
 */

#ifndef AKARI_BTHSDPDEF_H
#define AKARI_BTHSDPDEF_H

#include "Windef.h"
#include "Winnt.h"    /* GUID (SdpQueryUuidUnion member type) */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Enumerations (Bluetooth Application Development Enumerations).      */
/* ------------------------------------------------------------------ */

/* aa450880 "SDP_TYPE": printed complete with values. */
typedef enum {
    SDP_TYPE_NIL         = 0x00,
    SDP_TYPE_UINT        = 0x01,
    SDP_TYPE_INT         = 0x02,
    SDP_TYPE_UUID        = 0x03,
    SDP_TYPE_STRING      = 0x04,
    SDP_TYPE_BOOLEAN     = 0x05,
    SDP_TYPE_SEQUENCE    = 0x06,
    SDP_TYPE_ALTERNATIVE = 0x07,
    SDP_TYPE_URL         = 0x08,
    SDP_TYPE_CONTAINER   = 0x20
} SDP_TYPE;

/* aa450879 "SDP_SPECIFICTYPE": printed complete with values.
 * [sic] the page prints SDP_ST_UUID32 = 0x0220, the same value as
 * SDP_ST_INT32 (both are 0x0220 in the official page); reproduced as
 * printed. */
typedef enum {
    SDP_ST_NONE    = 0x0000,
    SDP_ST_UINT8   = 0x0010,
    SDP_ST_UINT16  = 0x0110,
    SDP_ST_UINT32  = 0x0210,
    SDP_ST_UINT64  = 0x0310,
    SDP_ST_UINT128 = 0x0410,
    SDP_ST_INT8    = 0x0020,
    SDP_ST_INT16   = 0x0120,
    SDP_ST_INT32   = 0x0220,
    SDP_ST_INT64   = 0x0320,
    SDP_ST_INT128  = 0x0420,
    SDP_ST_UUID16  = 0x0130,
    SDP_ST_UUID32  = 0x0220,   /* [sic] duplicate of SDP_ST_INT32 (page) */
    SDP_ST_UUID128 = 0x0430
} SDP_SPECIFICTYPE;

/* ms895690 "NODECONTAINERTYPE": the page prints
 * "NODECONTAINERTYPEALTERNATIVE = NodeContainerTypeSequence + 1" -- a
 * case typo for NODECONTAINERTYPESEQUENCE (the only enumerator of the
 * enum); the successor spelling is used, per the page, with the + 1
 * relation reproduced. */
typedef enum {
    NODECONTAINERTYPESEQUENCE     = 0,
    NODECONTAINERTYPEALTERNATIVE  = NODECONTAINERTYPESEQUENCE + 1
} NODECONTAINERTYPE;

/* ------------------------------------------------------------------ */
/* SDP query structures (Bluetooth Application Development Structures).*/
/* ------------------------------------------------------------------ */

/* aa450878 "SdpQueryUuidUnion": printed as "typedef [switch_type]
 * union SdpQueryUuidUnion {GUID uuid128; ULONG uuid32; USHORT
 * uuid16;}" (the archive prints an IDL [switch_type] attribute inside
 * the typedef -- a page artifact); the union body is as printed.
 * 16 bytes (GUID is the largest member). */
typedef union SdpQueryUuidUnion {
    GUID   uuid128;
    ULONG  uuid32;
    USHORT uuid16;
} SdpQueryUuidUnion;

/* aa450877 "SdpQueryUuid". */
typedef struct _SdpQueryUuid {
    SdpQueryUuidUnion u;
    USHORT            uuidType;
} SdpQueryUuid;

/* aa450876 "SdpAttributeRange": printed as
 * "struct _SdpAttributeRange {USHORT minAttribute; USHORT maxAttribute;}
 *  SdpAttributeRange;" -- no typedef keyword on the page; the plain
 * struct form is shipped (same type and tag as printed). */
struct _SdpAttributeRange {
    USHORT minAttribute;
    USHORT maxAttribute;
};

/* MAX_UUIDS_IN_QUERY: the BTHNS_RESTRICTIONBLOB page (ms887868, and the
 * CE 6.0 twin ee495874) prints "SdpQueryUuid uuids[MAX_UUIDS_IN_QUERY];"
 * without publishing the macro value.  Derived value (derivation path
 * recorded per the repo derived-value rule): the official Windows
 * Drivers DDI page for bthioctl.h BTH_SDP_SERVICE_ATTRIBUTE_SEARCH_REQUEST
 * documents the same MAX_UUIDS_IN_QUERY-sized SdpQueryUuid array and
 * states "there can be a maximum of 12 entries" -- so
 * MAX_UUIDS_IN_QUERY = 12.  Preserved page:
 * build/pagesw/bthioctl-ns-bthioctl-_bth_sdp_service_attribute_search_request.html */
#define MAX_UUIDS_IN_QUERY 12

/* ms887868 "BTHNS_RESTRICTIONBLOB" (CE 6.0 twin ee495874 identical). */
typedef struct _BTHNS_RESTRICTIONBLOB {
    ULONG              type;
    ULONG              serviceHandle;
    SdpQueryUuid       uuids[MAX_UUIDS_IN_QUERY];
    ULONG              numRange;
    struct _SdpAttributeRange pRange[1];
} BTHNS_RESTRICTIONBLOB, *PBTHNS_RESTRICTIONBLOB;

/* ms887864 "BTHNS_INQUIRYBLOB": the page prints "ULONGLAP;" (= ULONG
 * LAP, missing space) and "unsigned charlength;" (= unsigned char
 * length, missing space) -- page print artifacts, member types are
 * ULONG / unsigned char. */
typedef struct _BTHNS_INQUIRYBLOB {
    ULONG          LAP;
    unsigned char  length;
    unsigned char  num_responses;
} BTHNS_INQUIRYBLOB, *PBTHNS_INQUIRYBLOB;

/* ms887869 "BTHNS_SETBLOB". */
typedef struct _BTHNS_SETBLOB {
    ULONG *pRecordHandle;
    ULONG fSecurity;
    ULONG fOptions;
    ULONG ulRecordLength;
    UCHAR pRecord[1];
} BTHNS_SETBLOB, *PBTHNS_SETBLOB;

#ifdef __cplusplus
}
#endif

#endif /* AKARI_BTHSDPDEF_H */
