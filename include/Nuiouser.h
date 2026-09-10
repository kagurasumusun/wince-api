/* Nuiouser.h -- NDISUIO (NDIS user-mode I/O) driver interface.
 *
 * Source pages: Network Driver Reference rows printing
 * "Header: Nuiouser.h" (7) and "Header: Nuiouser.h, Ntddndis.h"
 * (10).  The IOCTL_* pages are prose-only (no values printed);
 * the six structure pages print layouts.  NDISUIO_OPEN_CONTEXT
 * embeds LIST_ENTRY / NUIO_LOCK / PFILE_OBJECT (none printed by
 * any CE page) and is recorded, opaquely closed.
 * See docs/inventory.md M78c.
 */

#ifndef AKARI_NUIOUSER_H
#define AKARI_NUIOUSER_H

#include "Windef.h"    /* DWORD, ULONG, UINT, UCHAR, HANDLE, TCHAR */
#include "Ndis.h"      /* NDIS_OID (ms904076) */

/* "NDISUIO_DEVICE_NOTIFICATION": print `typedef struct {DWORD
 * dwNotificationType;TCHAR ptcDeviceName[MAX_PATH]; UINT
 * uiOffsetToStatusBuffer; UINT uiStatusBufferSize;}
 * NDISUIO_DEVICE_NOTIFICATION, *PNDISUIO_DEVICE_NOTIFICATION;` */
typedef struct _NDISUIO_DEVICE_NOTIFICATION {
    DWORD dwNotificationType;
    TCHAR ptcDeviceName[MAX_PATH];
    UINT  uiOffsetToStatusBuffer;
    UINT  uiStatusBufferSize;
} NDISUIO_DEVICE_NOTIFICATION, *PNDISUIO_DEVICE_NOTIFICATION;

/* "NDISUIO_QUERY_BINDING": print `typedef struct
 * _NDISUIO_QUERY_BINDING{ULONG BindingIndex;ULONG DeviceNameOffset;
 * ULONG DeviceNameLength;ULONG DeviceDescrOffset;ULONG ...;}`
 * (glued tokens split; full member list as printed). */
typedef struct _NDISUIO_QUERY_BINDING {
    ULONG BindingIndex;
    ULONG DeviceNameOffset;
    ULONG DeviceNameLength;
    ULONG DeviceDescrOffset;
    ULONG DeviceDescrLength;
} NDISUIO_QUERY_BINDING, *PNDISUIO_QUERY_BINDING;

/* "NDISUIO_QUERY_OID" / "NDISUIO_SET_OID": prints `typedef struct
 * _NDISUIO_QUERY_OID {NDIS_OID Oid;#ifdef UNDER_CEPTCHAR
 * ptcDeviceName;#endifUCHAR Data[sizeof(ULONG)];}` (SET_OID
 * identical) -- the `#ifdef UNDER_CE` blocks are genuine prints
 * (glue split); reproduced with the conditional as printed. */
typedef struct _NDISUIO_QUERY_OID {
    NDIS_OID Oid;
#ifdef UNDER_CE
    PTCHAR   ptcDeviceName;
#endif
    UCHAR    Data[sizeof(ULONG)];
} NDISUIO_QUERY_OID, *PNDISUIO_QUERY_OID;

typedef struct _NDISUIO_SET_OID {
    NDIS_OID Oid;
#ifdef UNDER_CE
    PTCHAR   ptcDeviceName;
#endif
    UCHAR    Data[sizeof(ULONG)];
} NDISUIO_SET_OID, *PNDISUIO_SET_OID;

/* "NDISUIO_REQUEST_NOTIFICATION": print `typedef struct{ HANDLE
 * hMsgQueue; DWORD dwNotificationTypes; }NDISUIO_REQUEST_NOTIFICATION,
 * *PNDISUIO_REQUEST_NOTIFICATION;` */
typedef struct _NDISUIO_REQUEST_NOTIFICATION {
    HANDLE hMsgQueue;
    DWORD  dwNotificationTypes;
} NDISUIO_REQUEST_NOTIFICATION, *PNDISUIO_REQUEST_NOTIFICATION;

/* "NIC_STATISTICS": print (ULONGLONG counters; full member list as
 * printed). */
typedef struct _NIC_STATISTICS {
    ULONG     Size;
    PTCHAR    ptcDeviceName;
    ULONG     DeviceState;
    ULONG     MediaType;
    ULONG     MediaState;
    ULONG     PhysicalMediaType;
    ULONG     LinkSpeed;
    ULONGLONG PacketsSent;
    ULONGLONG PacketsReceived;
    ULONG     InitTime;
    ULONG     ConnectTime;
    ULONGLONG BytesSent;
    ULONGLONG BytesReceived;
    ULONGLONG DirectedBytesReceived;
    ULONGLONG DirectedPacketsReceived;
    ULONG     PacketsReceiveErrors;
    ULONG     PacketsSendErrors;
    ULONG     ResetCount;
    ULONG     MediaSenseConnectCount;
    ULONG     MediaSenseDisconnectCount;
} NIC_STATISTICS, *PNIC_STATISTICS;

/* --- Held. ------------------------------------------------------ */
/* "NDISUIO_OPEN_CONTEXT": print `typedef struct
 * _NDISUIO_OPEN_CONTEXT {LIST_ENTRYLink;ULONGFlags;ULONG RefCount;
 * NUIO_LOCK Lock;PFILE_OBJECT pFileObject;NDIS_HANDLE...}` --
 * LIST_ENTRY / NUIO_LOCK / PFILE_OBJECT are not printed by any CE
 * page (driver-internal context); held. */
typedef struct _NDISUIO_OPEN_CONTEXT NDISUIO_OPEN_CONTEXT,
    *PNDISUIO_OPEN_CONTEXT;

/* --- Recorded IOCTL names (prose pages; no values printed). ---
 * IOCTL_CANCEL_READ, IOCTL_NDISUIO_CANCEL_NOTIFICATION,
 * IOCTL_NDISUIO_NIC_STATISTICS, IOCTL_NDISUIO_OPEN_DEVICE,
 * IOCTL_NDISUIO_OPEN_WRITE_DEVICE, IOCTL_NDISUIO_QUERY_BINDING,
 * IOCTL_NDISUIO_QUERY_OID_VALUE, IOCTL_NDISUIO_REQUEST_NOTIFICATION,
 * IOCTL_NDISUIO_SET_ETHER_TYPE, IOCTL_NDISUIO_SET_OID_VALUE. */

#endif /* AKARI_NUIOUSER_H */
