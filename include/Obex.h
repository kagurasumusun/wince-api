/* Obex.h -- Object Exchange Protocol (OBEX) API (Windows CE .NET 4.0+).
 *
 * Pages: tools/manifests/servers.manifest (Servers book, Object
 * Exchange Protocol node); the interface pages print Header:
 * "Obex.h, Obex.idl" with Link Library Uuid.lib (no import
 * surface).  See docs/inventory.md M75c.
 */

#ifndef AKARI_OBEX_H
#define AKARI_OBEX_H

#include "Windef.h"    /* DWORD, BOOL, byte */
#include "Winbase.h"   /* LPCWSTR */
#include "Objbase.h"   /* IStream */

/* --- Interfaces (Uuid.lib rows): opaque forwards + records. ---- */
typedef struct IDeviceEnum IDeviceEnum;
typedef struct IHeaderCollection IHeaderCollection;
typedef struct IHeaderEnum IHeaderEnum;
typedef struct IObex IObex;
typedef struct IObexDevice IObexDevice;
typedef struct IObexSink IObexSink;
typedef struct IPropertyBagEnum IPropertyBagEnum;

/* IDeviceEnum (-):
 *   IDeviceEnum::Clone (ms900495)
 *   IDeviceEnum::Next (ms890398)
 *   IDeviceEnum::Reset (ms890399)
 *   IDeviceEnum::Skip (ms890400)
 *   IDeviceEnum:IUnknown (ms890397)
 */

/* IHeaderCollection (-):
 *   IHeaderCollection::AddAppParams (ms890891)
 *   IHeaderCollection::AddBody (ms890893)
 *   IHeaderCollection::AddByte (ms890897)
 *   IHeaderCollection::AddByteArray (ms890900)
 *   IHeaderCollection::AddConnectionId (ms890902)
 *   IHeaderCollection::AddCount (ms890906)
 *   IHeaderCollection::AddDescription (ms890910)
 *   IHeaderCollection::AddEndOfBody (ms890914)
 *   IHeaderCollection::AddHTTP (ms890916)
 *   IHeaderCollection::AddLength (ms890920)
 *   IHeaderCollection::AddLong (ms890922)
 *   IHeaderCollection::AddName (ms890925)
 *   IHeaderCollection::AddObjectClass (ms890927)
 *   IHeaderCollection::AddTarget (ms890931)
 *   IHeaderCollection::AddTime (ms890933)
 *   IHeaderCollection::AddTimeOld (ms890938)
 *   IHeaderCollection::AddType (ms890942)
 *   IHeaderCollection::AddUnicodeString (ms890944)
 *   IHeaderCollection::AddWho (ms890947)
 *   IHeaderCollection::EnumHeaders (ms890950)
 *   IHeaderCollection::Remove (ms890955)
 *   IHeaderCollection::RemoveAll (ms890957)
 *   IHeaderCollection:IUnknown (ms890953)
 */

/* IHeaderEnum (-):
 *   IHeaderEnum::Clone (ms890961)
 *   IHeaderEnum::Next (ms890966)
 *   IHeaderEnum::Reset (ms890969)
 *   IHeaderEnum:IUnknown (ms890964)
 */

/* IObex (-):
 *   IObex::BindToDevice (ms890990)
 *   IObex::EnumDevices (ms891030)
 *   IObex::EnumTransports (ms891033)
 *   IObex::Initialize (ms891037)
 *   IObex::Shutdown (ms891044)
 *   IObex::StartDeviceEnum (ms891054)
 *   IObex::StopDeviceEnum (ms891057)
 *   IObex:IUnknown (ms891039)
 */

/* IObexDevice (-):
 *   IObexDevice::Abort (ms890995)
 *   IObexDevice::Connect (ms890998)
 *   IObexDevice::Disconnect (ms891002)
 *   IObexDevice::EnumProperties (ms891005)
 *   IObexDevice::Get (ms891008)
 *   IObexDevice::Put (ms891015)
 *   IObexDevice::SetPassword (ms891017)
 *   IObexDevice::SetPath (ms891020)
 *   IObexDevice:IUnknown (ms891011)
 */

/* IObexSink (-):
 *   IObexSink::Notify (ms891050)
 *   IObexSink:IUnknown (ms891046)
 */

/* IPropertyBagEnum (ms900498):
 *   IPropertyBagEnum::Clone (ms900502)
 *   IPropertyBagEnum::Next (ms900507)
 *   IPropertyBagEnum::Reset (ms900511)
 *   IPropertyBagEnum::Skip (ms900514)
 */

/* ms895790 "OBEX_EVENT": print
 * `typedef enum _OBEX_EVENT {OE_QUERY_PASSWORD = 0,
 * OE_NEW_CONNECTION = OE_QUERY_PASSWORD + 1,OE_NEW_COMMAND =
 * OE_NEW_CONNECTION + 1,OE_ABORT = OE_NEW_COMMAND + 1,
 * OE_DISCONNECT = OE_ABORT + 1,OE_DEVICE_ARRIVAL = OE_DISCONNECT + 1,
 * OE_DEVICE_DEPARTURE = OE_DEVICE_ARRIVAL + 1,OE_DEVICE_UPDATE =
 * OE_DEVICE_DEPARTURE + 1 } OBEX_EVENT, *LPOBEX_EVENT;` */
typedef enum _OBEX_EVENT {
    OE_QUERY_PASSWORD = 0,
    OE_NEW_CONNECTION = OE_QUERY_PASSWORD + 1,
    OE_NEW_COMMAND = OE_NEW_CONNECTION + 1,
    OE_ABORT = OE_NEW_COMMAND + 1,
    OE_DISCONNECT = OE_ABORT + 1,
    OE_DEVICE_ARRIVAL = OE_DISCONNECT + 1,
    OE_DEVICE_DEPARTURE = OE_DEVICE_ARRIVAL + 1,
    OE_DEVICE_UPDATE = OE_DEVICE_DEPARTURE + 1
} OBEX_EVENT, *LPOBEX_EVENT;

/* ms895798 "OBEX_REQUEST": print
 * `typedef struct _OBEX_REQUEST {DWORD dwRequest;DWORD dwFlags;
 * IHeaderCollection* pHeaderCol;BOOL fStream;IStream* pStream;}
 * OBEX_REQUEST, *POBEX_REQUEST;` */
typedef struct _OBEX_REQUEST {
    DWORD              dwRequest;
    DWORD              dwFlags;
    IHeaderCollection *pHeaderCol;
    BOOL               fStream;
    IStream           *pStream;
} OBEX_REQUEST, *POBEX_REQUEST;

/* ms890978 "INBOX_EVENT_DATA": print
 * `typedef struct _INBOX_EVENT_DATA {DWORDdwRequest;
 * DWORDdwInboxEvent;LPCWSTRpszName;LPCWSTRpszInboxDestination;
 * IHeaderCollection* pHeaderCol;IStream* pStream;}
 * INBOX_EVENT_DATA, *PINBOX_EVENT_DATA;` */
typedef struct _INBOX_EVENT_DATA {
    DWORD              dwRequest;
    DWORD              dwInboxEvent;
    LPCWSTR            pszName;
    LPCWSTR            pszInboxDestination;
    IHeaderCollection *pHeaderCol;
    IStream           *pStream;
} INBOX_EVENT_DATA, *PINBOX_EVENT_DATA;

/* ms900565 "ServerCallback" / ms900568 "ServiceCallback"
 * (Obexserver.h rows; developer-implemented): prints
 * `typedef int (*ServerCallback)(unsigned int uiOp,
 *  unsigned int uiId, struct _obex_command * pCommand);`
 * `typedef int (*ServiceCallback)(struct _obex_transaction * pTrans);`
 * -- the referenced structs are the record-only ObexCommand /
 * ObexTransaction below, so the tags stay incomplete here. */
struct _obex_command;
struct _obex_transaction;
typedef int (*ServerCallback)(unsigned int uiOp, unsigned int uiId,
                             struct _obex_command *pCommand);
typedef int (*ServiceCallback)(struct _obex_transaction *pTrans);

/* --- Record-only types (unpublishable members). ------------------
 * ms895794 "OBEX_HEADER": IDL print
 *   typedef struct _OBEX_HEADER {byte bId;
 *     [switch_is(bId & OBEX_HEADER_4BYTE)]union {
 *       [case(OBEX_HEADER_UNICODE)][string] LPWSTR pszData;
 *       [case(OBEX_HEADER_4BYTE)]DWORD dwData;
 *       [case(OBEX_HEADER_1BYTE)]byte bData;
 *       [case(OBEX_HEADER_STREAM)]struct {DWORD dwSize;
 *         [size_is(dwSize)] byte* pbaData;} ba; ...
 *   (MIDL attributes; the OBEX_HEADER_* case constants are not
 *   published on any CE page) -- recorded, not compiled.
 * ms900557 "OBEXCOMMAND": print
 *   typedef struct _obex_command { unsigned int uiOp;
 *     unsigned int uiResp; unsigned int fFinal;
 *     ObexPacketData sPktData; unsigned int cProp;
 *     unsigned int * aPropID; ObexVariant * aPropVar;} ObexCommand;
 *   (ObexPacketData / ObexVariant unpublished) -- recorded.
 * ms900561 "OBEXTRANSACTION": print
 *   typedef struct _obex_transaction {unsigned int uiConnectionId;
 *     unsigned int uiTransactionId; unsigned int uiOp;
 *     ObexCommand * pObex; MemAlloc ObexAlloc; MemFree ObexFree;
 *     ServerCallback ObexExecute;} ObexTransaction;
 *   (MemAlloc / MemFree unpublished) -- recorded. */

/* ------------------------------------------------------------------
 * Book surface: servers (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms900495 IDeviceEnum::Clone (Header: Obex.h, Obex.idl.) */
/* ms890398 IDeviceEnum::Next (Header: Obex.h, Obex.idl.) */
/* ms890399 IDeviceEnum::Reset (Header: Obex.h, Obex.idl.) */
/* ms890400 IDeviceEnum::Skip (Header: Obex.h, Obex.idl.) */
/* ms890397 IDeviceEnum:IUnknown (Header: Obex.h, Obex.idl.) */
/* ms890891 IHeaderCollection::AddAppParams (Header: Obex.h, Obex.idl.) */
/* ms890893 IHeaderCollection::AddBody (Header: Obex.h, Obex.idl.) */
/* ms890897 IHeaderCollection::AddByte (Header: Obex.h, Obex.idl.) */
/* ms890900 IHeaderCollection::AddByteArray (Header: Obex.h, Obex.idl.) */
/* ms890902 IHeaderCollection::AddConnectionId (Header: Obex.h, Obex.idl.) */
/* ms890906 IHeaderCollection::AddCount (Header: Obex.h, Obex.idl.) */
/* ms890910 IHeaderCollection::AddDescription (Header: Obex.h, Obex.idl.) */
/* ms890914 IHeaderCollection::AddEndOfBody (Header: Obex.h, Obex.idl.) */
/* ms890916 IHeaderCollection::AddHTTP (Header: Obex.h, Obex.idl.) */
/* ms890920 IHeaderCollection::AddLength (Header: Obex.h, Obex.idl.) */
/* ms890922 IHeaderCollection::AddLong (Header: Obex.h, Obex.idl.) */
/* ms890925 IHeaderCollection::AddName (Header: Obex.h, Obex.idl.) */
/* ms890927 IHeaderCollection::AddObjectClass (Header: Obex.h, Obex.idl.) */
/* ms890931 IHeaderCollection::AddTarget (Header: Obex.h, Obex.idl.) */
/* ms890933 IHeaderCollection::AddTime (Header: Obex.h, Obex.idl.) */
/* ms890938 IHeaderCollection::AddTimeOld (Header: Obex.h, Obex.idl.) */
/* ms890942 IHeaderCollection::AddType (Header: Obex.h, Obex.idl.) */
/* ms890944 IHeaderCollection::AddUnicodeString (Header: Obex.h, Obex.idl.) */
/* ms890947 IHeaderCollection::AddWho (Header: Obex.h, Obex.idl.) */
/* ms890950 IHeaderCollection::EnumHeaders (Header: Obex.h, Obex.idl.) */
/* ms890955 IHeaderCollection::Remove (Header: Obex.h, Obex.idl.) */
/* ms890957 IHeaderCollection::RemoveAll (Header: Obex.h, Obex.idl.) */
/* ms890953 IHeaderCollection:IUnknown (Header: Obex.h, Obex.idl.) */
/* ms890961 IHeaderEnum::Clone (Header: Obex.h, Obex.idl.) */
/* ms890966 IHeaderEnum::Next (Header: Obex.h, Obex.idl.) */
/* ms890969 IHeaderEnum::Reset (Header: Obex.h, Obex.idl.) */
/* ms890964 IHeaderEnum:IUnknown (Header: Obex.h, Obex.idl.) */
/* ms890990 IObex::BindToDevice (Header: Obex.h, Obex.idl.) */
/* ms891030 IObex::EnumDevices (Header: Obex.h, Obex.idl.) */
/* ms891033 IObex::EnumTransports (Header: Obex.h, Obex.idl.) */
/* ms891037 IObex::Initialize (Header: Obex.h, Obex.idl.) */
/* ms891044 IObex::Shutdown (Header: Obex.h, Obex.idl.) */
/* ms891054 IObex::StartDeviceEnum (Header: Obex.h, Obex.idl.) */
/* ms891057 IObex::StopDeviceEnum (Header: Obex.h, Obex.idl.) */
/* ms891039 IObex:IUnknown (Header: Obex.h, Obex.idl.) */
/* ms890995 IObexDevice::Abort (Header: Obex.h, Obex.idl.) */
/* ms890998 IObexDevice::Connect (Header: Obex.h, Obex.idl.) */
/* ms891002 IObexDevice::Disconnect (Header: Obex.h, Obex.idl.) */
/* ms891005 IObexDevice::EnumProperties (Header: Obex.h, Obex.idl.) */
/* ms891008 IObexDevice::Get (Header: Obex.h, Obex.idl.) */
/* ms891015 IObexDevice::Put (Header: Obex.h, Obex.idl.) */
/* ms891017 IObexDevice::SetPassword (Header: Obex.h, Obex.idl.) */
/* ms891020 IObexDevice::SetPath (Header: Obex.h, Obex.idl.) */
/* ms891011 IObexDevice:IUnknown (Header: Obex.h, Obex.idl.) */
/* ms891050 IObexSink::Notify (Header: Obex.h, Obex.idl.) */
/* ms891046 IObexSink:IUnknown (Header: Obex.h, Obex.idl.) */
/* ms900502 IPropertyBagEnum::Clone (Header: Obex.h) */
/* ms900507 IPropertyBagEnum::Next (Header: Obex.h) */
/* ms900511 IPropertyBagEnum::Reset (Header: Obex.h) */
/* ms900514 IPropertyBagEnum::Skip (Header: Obex.h) */
/* ------------------------------------------------------------------
 * Book surface: servers (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms900495 IDeviceEnum::Clone (Header: Obex.h, Obex.idl.) */
/* ms890398 IDeviceEnum::Next (Header: Obex.h, Obex.idl.) */
/* ms890399 IDeviceEnum::Reset (Header: Obex.h, Obex.idl.) */
/* ms890400 IDeviceEnum::Skip (Header: Obex.h, Obex.idl.) */
/* ms890397 IDeviceEnum:IUnknown (Header: Obex.h, Obex.idl.) */
/* ms890891 IHeaderCollection::AddAppParams (Header: Obex.h, Obex.idl.) */
/* ms890893 IHeaderCollection::AddBody (Header: Obex.h, Obex.idl.) */
/* ms890897 IHeaderCollection::AddByte (Header: Obex.h, Obex.idl.) */
/* ms890900 IHeaderCollection::AddByteArray (Header: Obex.h, Obex.idl.) */
/* ms890902 IHeaderCollection::AddConnectionId (Header: Obex.h, Obex.idl.) */
/* ms890906 IHeaderCollection::AddCount (Header: Obex.h, Obex.idl.) */
/* ms890910 IHeaderCollection::AddDescription (Header: Obex.h, Obex.idl.) */
/* ms890914 IHeaderCollection::AddEndOfBody (Header: Obex.h, Obex.idl.) */
/* ms890916 IHeaderCollection::AddHTTP (Header: Obex.h, Obex.idl.) */
/* ms890920 IHeaderCollection::AddLength (Header: Obex.h, Obex.idl.) */
/* ms890922 IHeaderCollection::AddLong (Header: Obex.h, Obex.idl.) */
/* ms890925 IHeaderCollection::AddName (Header: Obex.h, Obex.idl.) */
/* ms890927 IHeaderCollection::AddObjectClass (Header: Obex.h, Obex.idl.) */
/* ms890931 IHeaderCollection::AddTarget (Header: Obex.h, Obex.idl.) */
/* ms890933 IHeaderCollection::AddTime (Header: Obex.h, Obex.idl.) */
/* ms890938 IHeaderCollection::AddTimeOld (Header: Obex.h, Obex.idl.) */
/* ms890942 IHeaderCollection::AddType (Header: Obex.h, Obex.idl.) */
/* ms890944 IHeaderCollection::AddUnicodeString (Header: Obex.h, Obex.idl.) */
/* ms890947 IHeaderCollection::AddWho (Header: Obex.h, Obex.idl.) */
/* ms890950 IHeaderCollection::EnumHeaders (Header: Obex.h, Obex.idl.) */
/* ms890955 IHeaderCollection::Remove (Header: Obex.h, Obex.idl.) */
/* ms890957 IHeaderCollection::RemoveAll (Header: Obex.h, Obex.idl.) */
/* ms890953 IHeaderCollection:IUnknown (Header: Obex.h, Obex.idl.) */
/* ms890961 IHeaderEnum::Clone (Header: Obex.h, Obex.idl.) */
/* ms890966 IHeaderEnum::Next (Header: Obex.h, Obex.idl.) */
/* ms890969 IHeaderEnum::Reset (Header: Obex.h, Obex.idl.) */
/* ms890964 IHeaderEnum:IUnknown (Header: Obex.h, Obex.idl.) */
/* ms890990 IObex::BindToDevice (Header: Obex.h, Obex.idl.) */
/* ms891030 IObex::EnumDevices (Header: Obex.h, Obex.idl.) */
/* ms891033 IObex::EnumTransports (Header: Obex.h, Obex.idl.) */
/* ms891037 IObex::Initialize (Header: Obex.h, Obex.idl.) */
/* ms891044 IObex::Shutdown (Header: Obex.h, Obex.idl.) */
/* ms891054 IObex::StartDeviceEnum (Header: Obex.h, Obex.idl.) */
/* ms891057 IObex::StopDeviceEnum (Header: Obex.h, Obex.idl.) */
/* ms891039 IObex:IUnknown (Header: Obex.h, Obex.idl.) */
/* ms890995 IObexDevice::Abort (Header: Obex.h, Obex.idl.) */
/* ms890998 IObexDevice::Connect (Header: Obex.h, Obex.idl.) */
/* ms891002 IObexDevice::Disconnect (Header: Obex.h, Obex.idl.) */
/* ms891005 IObexDevice::EnumProperties (Header: Obex.h, Obex.idl.) */
/* ms891008 IObexDevice::Get (Header: Obex.h, Obex.idl.) */
/* ms891015 IObexDevice::Put (Header: Obex.h, Obex.idl.) */
/* ms891017 IObexDevice::SetPassword (Header: Obex.h, Obex.idl.) */
/* ms891020 IObexDevice::SetPath (Header: Obex.h, Obex.idl.) */
/* ms891011 IObexDevice:IUnknown (Header: Obex.h, Obex.idl.) */
/* ms891050 IObexSink::Notify (Header: Obex.h, Obex.idl.) */
/* ms891046 IObexSink:IUnknown (Header: Obex.h, Obex.idl.) */
/* ms900502 IPropertyBagEnum::Clone (Header: Obex.h) */
/* ms900507 IPropertyBagEnum::Next (Header: Obex.h) */
/* ms900511 IPropertyBagEnum::Reset (Header: Obex.h) */
/* ms900514 IPropertyBagEnum::Skip (Header: Obex.h) */
#endif /* AKARI_OBEX_H */
