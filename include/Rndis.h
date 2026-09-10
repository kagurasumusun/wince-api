/* Rndis.h -- Remote NDIS (USB networking) message protocol types.
 *
 * Source pages: Network Driver Reference rows printing
 * "Header: Rndis.h" (23 pages).  The five scalar typedefs print
 * `typedef UINT32 NAME;`; the REMOTE_NDIS_* message pages print
 * their layouts as flattened "NAME(Type)Member;" lists -- the
 * members, types and order are printed, and are reproduced as
 * structs below (format note at each site; no pointer typedefs are
 * printed for these, so none are invented).
 *
 * RNDIS_HANDLE and RNDIS_MESSAGE are not printed by any CE page,
 * so the messages embedding them, and RNDIS_PACKET, are recorded
 * and closed opaquely; REMOTE_NDIS_INITIALIZE_CMPLT and
 * REMOTE_NDIS_PACKET_MSG print no layout (names recorded).
 * See docs/inventory.md M78c.
 */

#ifndef AKARI_RNDIS_H
#define AKARI_RNDIS_H

#include "Windef.h"    /* UINT32 (Windef.h KEY_STATE_FLAGS print) */

/* ms919868 "RNDIS_CLASS_ID": `typedef UINT32 RNDIS_CLASS_ID;` */
typedef UINT32 RNDIS_CLASS_ID;

/* ms919872 "RNDIS_MEDIUM": `typedef UINT32 RNDIS_MEDIUM;` */
typedef UINT32 RNDIS_MEDIUM;

/* ms919875 "RNDIS_OID": `typedef UINT32 RNDIS_OID;` */
typedef UINT32 RNDIS_OID;

/* ms919887 "RNDIS_REQUEST_ID": `typedef UINT32 RNDIS_REQUEST_ID;` */
typedef UINT32 RNDIS_REQUEST_ID;

/* ms919889 "RNDIS_STATUS": `typedef UINT32 RNDIS_STATUS;` */
typedef UINT32 RNDIS_STATUS;

/* ms919870 "RNDIS_DIAGNOSTIC_INFO": print (glued tokens split). */
typedef struct _RNDIS_DIAGNOSTIC_INFO {
    RNDIS_STATUS DiagStatus;
    UINT32       ErrorOffset;
} RNDIS_DIAGNOSTIC_INFO, *PRNDIS_DIAGNOSTIC_INFO;

/* ms919877 "RNDIS_OOBD": print (glued tokens split). */
typedef struct _RNDIS_OOBD {
    UINT32        Size;
    RNDIS_CLASS_ID Type;
    UINT32        ClassInformationOffset;
} RNDIS_OOBD, *PRNDIS_OOBD;

/* ms919884 "RNDIS_PER_PACKET_INFO": print (glued tokens split). */
typedef struct _RNDIS_PER_PACKET_INFO {
    UINT32 Size;
    UINT32 Type;
    UINT32 PerPacketInformationOffset;
} RNDIS_PER_PACKET_INFO, *PRNDIS_PER_PACKET_INFO;

/* --- REMOTE_NDIS_* messages (printed as "NAME(Type)Member;"
 *     flattened layouts; reproduced as structs). --------------- */
/* ms919807 "REMOTE_NDIS_HALT_MSG": flattened print */
typedef struct _REMOTE_NDIS_HALT_MSG {
    UINT32             NdisMessageType;
    UINT32             MessageLength;
    RNDIS_REQUEST_ID   RequestId;
} REMOTE_NDIS_HALT_MSG;

/* ms919811 "REMOTE_NDIS_INITIALIZE_MSG": flattened print */
typedef struct _REMOTE_NDIS_INITIALIZE_MSG {
    UINT32             NdisMessageType;
    UINT32             MessageLength;
    RNDIS_REQUEST_ID   RequestId;
    UINT32             MajorVersion;
    UINT32             MinorVersion;
    UINT32             MaxTransferSize;
} REMOTE_NDIS_INITIALIZE_MSG;

/* ms919813 "REMOTE_NDIS_KEEPALIVE_CMPLT": flattened print */
typedef struct _REMOTE_NDIS_KEEPALIVE_CMPLT {
    UINT32             NdisMessageType;
    UINT32             MessageLength;
    RNDIS_REQUEST_ID   RequestId;
    RNDIS_STATUS       Status;
} REMOTE_NDIS_KEEPALIVE_CMPLT;

/* ms919814 "REMOTE_NDIS_KEEPALIVE_MSG": flattened print */
typedef struct _REMOTE_NDIS_KEEPALIVE_MSG {
    UINT32             NdisMessageType;
    UINT32             MessageLength;
    RNDIS_REQUEST_ID   RequestId;
} REMOTE_NDIS_KEEPALIVE_MSG;

/* ms919817 "REMOTE_NDIS_QUERY_CMPLT": flattened print */
typedef struct _REMOTE_NDIS_QUERY_CMPLT {
    UINT32             NdisMessageType;
    UINT32             MessageLength;
    RNDIS_REQUEST_ID   RequestId;
    RNDIS_STATUS       Status;
    UINT32             InformationBufferLength;
    UINT32             InformationBufferOffset;
} REMOTE_NDIS_QUERY_CMPLT;

/* ms919820 "REMOTE_NDIS_RESET_CMPLT": flattened print */
typedef struct _REMOTE_NDIS_RESET_CMPLT {
    UINT32             NdisMessageType;
    UINT32             MessageLength;
    RNDIS_STATUS       Status;
    UINT32             AddressingReset;
} REMOTE_NDIS_RESET_CMPLT;

/* ms919822 "REMOTE_NDIS_RESET_MSG": flattened print */
typedef struct _REMOTE_NDIS_RESET_MSG {
    UINT32             NdisMessageType;
    UINT32             MessageLength;
    UINT32             Reserved;
} REMOTE_NDIS_RESET_MSG;

/* ms919824 "REMOTE_NDIS_SET_CMPLT": flattened print  The print spells the
 * RequestId type `RNDIS_REQUEST`; every sibling message prints
 * `RNDIS_REQUEST_ID` -- repaired (noted). */
typedef struct _REMOTE_NDIS_SET_CMPLT {
    UINT32             NdisMessageType;
    UINT32             MessageLength;
    RNDIS_REQUEST_ID   RequestId;
    RNDIS_STATUS       Status;
} REMOTE_NDIS_SET_CMPLT;

/* --- Held / no-print REMOTE_NDIS_* rows. ----------------------- */
/* ms919809 "REMOTE_NDIS_INDICATE_STATUS_MSG": flattened print
 * `REMOTE_NDIS_INDICATE_STATUS_MSG(UINT32)NdisMessageType;
 * (UINT32)MessageLength;(RNDIS_STATUS)Status;(UINT32)
 * StatusBufferLength;(UINT32)StatusBufferOffset;(RNDIS_STATUS)
 * DiagStatus;(UINT32)ErrorOffset;(RNDIS_MESSAGE)Message;` --
 * RNDIS_MESSAGE is not printed by any CE page; held. */
typedef struct _REMOTE_NDIS_INDICATE_STATUS_MSG
    REMOTE_NDIS_INDICATE_STATUS_MSG;

/* ms919819 "REMOTE_NDIS_QUERY_MSG" / ms919826 "REMOTE_NDIS_SET_MSG":
 * flattened prints embed `(RNDIS_HANDLE)DeviceVcHandle`;
 * RNDIS_HANDLE is not printed by any CE page; held. */
typedef struct _REMOTE_NDIS_QUERY_MSG REMOTE_NDIS_QUERY_MSG;
typedef struct _REMOTE_NDIS_SET_MSG REMOTE_NDIS_SET_MSG;

/* "REMOTE_NDIS_INITIALIZE_CMPLT" (ms919810) and
 * "REMOTE_NDIS_PACKET_MSG" (ms919887-adjacent row): pages print no
 * layout -- names recorded. */

/* ms919879 "RNDIS_PACKET": print `typedef struct _RNDIS_PACKET
 * {UINT32DataOffset;UINT32DataLength;UINT32OOBDataOffset;UINT32
 * OOBDataLength;UINT32NumOOBDataElements;UINT32PerPacketInfoOffset;
 * UINT32PerPacketInfoLength;RNDIS_HANDLEVcHandle;UINT32Reserved;}
 * RNDIS_PACKET, *PRNDIS_PACKET;` -- RNDIS_HANDLE is not printed by
 * any CE page; held. */
typedef struct _RNDIS_PACKET RNDIS_PACKET, *PRNDIS_PACKET;

#endif /* AKARI_RNDIS_H */
