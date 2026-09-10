/*
 * Bthapi.h -- Bluetooth SDP interfaces for Windows CE (Bthapi.h layer).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  Source book: CE 5.0 "Bluetooth Application Development ::
 * Interfaces" (the Bthapi.h / Bthapi.idl leaves of
 * tools/manifests/bt-appdev.manifest, fetched M57).  OS Versions:
 * "Windows CE .NET 4.0 and later".
 *
 * The interface pages (ISdpNodeContainer, ISdpRecord, ISdpStream,
 * ISdpWalk and their methods) carry "Link Library: Btdrt.lib" rows, but
 * they are IDL interface methods (vtable entries), not DLL exports --
 * the M54 discodlg.h / Mstsax def-less record model: opaque interface
 * records, method lists and signatures recorded in comments.  The vtable
 * order is not published by the documentation, so no vtable structs are
 * synthesized.  Nothing here enters def/btdrt-doc.def.
 *
 * Held types (layouts never printed in the official CE documentation,
 * neither on the CE 5.0 pages nor on the CE 6.0 twins -- see
 * docs/inventory.md M57):
 *   - NodeData (ms895699) / NodeDataUnion (ms895706): the union members
 *     int128/uint128/str/url are typed DP_LARGE_INTEGER_16 /
 *     SDP_ULARGE_INTEGER_16 / SdpString, and no page of any CE
 *     generation (or of the desktop/driver documentation trees)
 *     publishes those layouts.  Forward-declared here (the documented
 *     method signatures take NodeData*).
 *   - SDP_ULARGE_INTEGER_16 / SDP_LARGE_INTEGER_16 (pointer forms named
 *     PSDP_ULARGE_INTEGER_16 / PSDP_LARGE_INTEGER_16 by the ISdpStream
 *     ByteSwap and Retrieve family pages aa450599/aa450605): layouts
 *     not published; forward-declared (pointer-only use).
 */

#ifndef AKARI_BTHAPI_H
#define AKARI_BTHAPI_H

#include "Windef.h"
#include "Winnt.h"        /* GUID, LPGUID */
#include "Bthsdpdef.h"    /* SDP_TYPE, SDP_SPECIFICTYPE, NODECONTAINERTYPE */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Held data types (forward declarations only; see header note).       */
/* ------------------------------------------------------------------ */

typedef union NodeDataUnion    NodeDataUnion;    /* ms895706: held layout */
typedef struct NodeData        NodeData;         /* ms895699: held layout */
typedef union DP_LARGE_INTEGER_16 DP_LARGE_INTEGER_16;   /* aa450599 name */
typedef union SDP_ULARGE_INTEGER_16 SDP_ULARGE_INTEGER_16; /* aa450599 */
typedef union SDP_LARGE_INTEGER_16  SDP_LARGE_INTEGER_16;  /* aa450599 */
typedef struct SdpString       SdpString;        /* ms895706 member name */

/* ------------------------------------------------------------------ */
/* Opaque interface records (M44/M53/M54 model).                       */
/* ------------------------------------------------------------------ */

/* aa450551 "ISdpNodeContainer" (Bthapi.h, Bthapi.idl; Btdrt.lib row,
 * def-less).  Documented methods, each on its own page:
 *   aa450534  HRESULT AppendNode(NodeData* pData);
 *   aa450536  HRESULT CreateFromStream(UCHAR* pStream, ULONG size);
 *   aa450539  HRESULT CreateStream(UCHAR** ppStream, ULONG* pSize);
 *   aa450540  HRESULT GetNode(ULONG nodeIndex, NodeData* pData);
 *   aa450543  HRESULT GetNodeCount(ULONG* pNodeCount);
 *   aa450545  HRESULT GetNodeStringData(ULONG nodeIndex, NodeData* pData);
 *   aa450547  HRESULT GetStreamSize(ULONG* pSize);
 *   aa450549  HRESULT GetType(NodeContainerType* pType);
 *             (NODECONTAINERTYPE enum type, ms895690)
 *   aa450553  HRESULT LockContainer(UCHAR lock);
 *   aa450556  HRESULT SetNode(ULONG nodeIndex, NodeData* pData);
 *   aa450557  HRESULT SetType(NodeContainerType type);
 *   aa450560  HRESULT Walk(ISdpWalk* pWalk);
 *   aa450562  HRESULT WriteStream(UCHAR* pStream, ULONG* pNumBytesWritten);
 */
typedef struct ISdpNodeContainer ISdpNodeContainer;

/* aa450617 "ISdpWalk" (Bthapi.h, Bthapi.idl; Btdrt.lib row, def-less).
 * Documented methods:
 *   aa450619  HRESULT WalkNode(NODEDATA* pData, ULONG state);
 *             (the page spells the NodeData type in capitals; same
 *              type as ms895699 NodeData)
 *   aa450622  HRESULT WalkStream(UCHAR elementType, ULONG elementSize,
 *                                UCHAR* pStream);
 */
typedef struct ISdpWalk ISdpWalk;

/* aa450590 "ISdpRecord" (Bthapi.h, Bthapi.idl; Btdrt.lib row, def-less).
 * Documented methods:
 *   aa450579  HRESULT CreateFromStream(UCHAR* pStream, ULONG size);
 *   aa450582  HRESULT GetAttribute(USHORT attribute, NodeData* pNode);
 *   aa450583  HRESULT GetAttributeAsStream(USHORT attribute,
 *                                          CHAR** ppStream, ULONG* pSize);
 *   aa450586  HRESULT GetAttributeList(USHORT** ppList, ULONG* pListSize);
 *   aa450588  HRESULT GetServiceClass(LPGUID pServiceClass);
 *   aa450591  HRESULT SetAttribute(USHORT attribute, NodeData* pNode);
 *   aa450593  HRESULT SetAttributeFromStream(USHORT attribute,
 *                                            UCHAR* pStream, ULONG size);
 *   aa450595  HRESULT Walk(ISdpWalk* pWalk);
 *   aa450597  HRESULT WriteToStream(UCHAR** ppStream, ULONG* pStreamSize,
 *                                   ULONG preSize, ULONG postSize);
 */
typedef struct ISdpRecord ISdpRecord;

/* aa450601 "ISdpStream" (Bthapi.h, Bthapi.idl; Btdrt.lib row, def-less).
 * Documented methods (the ByteSwap family page aa450599 and the
 * Retrieve family page aa450605 each print the instance list below):
 *   aa450599  HRESULT ByteSwapUuid128(GUID* pInUuid128, GUID* pOutUuid128);
 *             HRESULT ByteSwapUint128(PSDP_ULARGE_INTEGER_16 pInUint128,
 *                                     PSDP_ULARGE_INTEGER_16 pOutUint128);
 *             HRESULT ByteSwapUint64(ULONGLONG inUint64,
 *                                    ULONGLONG* pOutUint64);
 *             HRESULT ByteSwapUint32(ULONG uint32, ULONG* pUint32);
 *             HRESULT ByteSwapUint16(USHORT uint16, USHORT* pUint16);
 *             HRESULT ByteSwapInt128(PSDP_LARGE_INTEGER_16 pInInt128,
 *                                    PSDP_LARGE_INTEGER_16 pOutInt128);
 *             HRESULT ByteSwapInt64(LONGLONG inInt64, LONGLONG* pOutInt64);
 *             HRESULT ByteSwapInt32(LONG int32, LONG* pInt32);
 *             HRESULT ByteSwapInt16(SHORT int16, SHORT* pInt16);
 *   aa450605  HRESULT RetrieveUuid128(UCHAR* pStream, GUID* pUuid128);
 *             HRESULT RetrieveUint128(UCHAR* pStream,
 *                                     PSDP_ULARGE_INTEGER_16 pUint128);
 *             HRESULT RetrieveUint64(UCHAR* pStream, ULONGLONG* pUint64);
 *             HRESULT RetrieveUint32(UCHAR* pStream, ULONG* pUint32);
 *             HRESULT RetrieveUint16(UCHAR* pStream, USHORT* pUint16);
 *             HRESULT RetrieveInt128(UCHAR* pStream,
 *                                    PSDP_LARGE_INTEGER_16 pInt128);
 *             HRESULT RetrieveInt64(UCHAR* pStream, LONGLONG* pInt64);
 *             HRESULT RetrieveInt32(UCHAR* pStream, LONG* pInt32);
 *             HRESULT RetrieveInt16(UCHAR* pStream, SHORT* pInt16);
 *   aa450603  HRESULT NormalizeUuid(NODEDATA* pDataUuid,
 *                                   GUID* pNormalizeUuid);
 *   aa450607  HRESULT RetrieveElementInfo(UCHAR* pStream,
 *             SDP_TYPE* pElementType, SDP_SPECIFICTYPE* pElementSpecificType,
 *             ULONG* pElementSize, ULONG* pStorageSize, UCHAR** ppData);
 *   aa450609  HRESULT RetrieveRecords(UCHAR* pStream, ULONG size,
 *             ISdpRecord** ppSdpRecords, ULONG* pNumRecords);
 *   aa450611  HRESULT Validate(UCHAR* pStream, ULONG size,
 *             ULONG_PTR* pErrorByte);
 *   aa450613  HRESULT VerifySequenceOf(UCHAR* pStream, ULONG size,
 *             SDP_TYPE ofType, UCHAR* pSpecificSizes, ULONG* pNumFound);
 *   aa450615  HRESULT Walk(ISdpWalk* pWalk);
 */
typedef struct ISdpStream ISdpStream;

/* ------------------------------------------------------------------
 * Book surface: bt-appdev (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa450534 ISdpNodeContainer::AppendNode (Header: Bthapi.h, Bthapi.idl.) */
/* aa450536 ISdpNodeContainer::CreateFromStream (Header: Bthapi.h, Bthapi.idl.) */
/* aa450539 ISdpNodeContainer::CreateStream (Header: Bthapi.h, Bthapi.idl.) */
/* aa450540 ISdpNodeContainer::GetNode (Header: Bthapi.h, Bthapi.idl.) */
/* aa450543 ISdpNodeContainer::GetNodeCount (Header: Bthapi.h, Bthapi.idl.) */
/* aa450545 ISdpNodeContainer::GetNodeStringData (Header: Bthapi.h, Bthapi.idl.) */
/* aa450547 ISdpNodeContainer::GetStreamSize (Header: Bthapi.h, Bthapi.idl.) */
/* aa450549 ISdpNodeContainer::GetType (Header: Bthapi.h, Bthapi.idl.) */
/* aa450553 ISdpNodeContainer::LockContainer (Header: Bthapi.h, Bthapi.idl.) */
/* aa450556 ISdpNodeContainer::SetNode (Header: Bthapi.h, Bthapi.idl.) */
/* aa450557 ISdpNodeContainer::SetType (Header: Bthapi.h, Bthapi.idl.) */
/* aa450560 ISdpNodeContainer::Walk (Header: Bthapi.h, Bthapi.idl.) */
/* aa450562 ISdpNodeContainer::WriteStream (Header: Bthapi.h, Bthapi.idl.) */
/* aa450579 ISdpRecord::CreateFromStream (Header: Bthapi.h, Bthapi.idl.) */
/* aa450582 ISdpRecord::GetAttribute (Header: Bthapi.h, Bthapi.idl.) */
/* aa450583 ISdpRecord::GetAttributeAsStream (Header: Bthapi.h, Bthapi.idl.) */
/* aa450586 ISdpRecord::GetAttributeList (Header: Bthapi.h, Bthapi.idl.) */
/* aa450588 ISdpRecord::GetServiceClass (Header: Bthapi.h, Bthapi.idl.) */
/* aa450591 ISdpRecord::SetAttribute (Header: Bthapi.h, Bthapi.idl.) */
/* aa450593 ISdpRecord::SetAttributeFromStream (Header: Bthapi.h, Bthapi.idl.) */
/* aa450595 ISdpRecord::Walk (Header: Bthapi.h, Bthapi.idl.) */
/* aa450597 ISdpRecord::WriteToStream (Header: Bthapi.h, Bthapi.idl.) */
/* aa450599 ISdpStream::ByteSwap* (Header: Bthapi.h, Bthapi.idl.) */
/* aa450603 ISdpStream::NormalizeUuid (Header: Bthapi.h, Bthapi.idl.) */
/* aa450605 ISdpStream::Retrieve* (Header: Bthapi.h, Bthapi.idl.) */
/* aa450607 ISdpStream::RetrieveElementInfo (Header: Bthapi.h, Bthapi.idl.) */
/* aa450609 ISdpStream::RetrieveRecords (Header: Bthapi.h, Bthapi.idl.) */
/* aa450611 ISdpStream::Validate (Header: Bthapi.h, Bthapi.idl.) */
/* aa450613 ISdpStream::VerifySequenceOf (Header: Bthapi.h, Bthapi.idl.) */
/* aa450615 ISdpStream::Walk (Header: Bthapi.h, Bthapi.idl.) */
/* aa450619 ISdpWalk::WalkNode (Header: Bthapi.h, Bthapi.idl.) */
/* aa450622 ISdpWalk::WalkStream (Header: Bthapi.h, Bthapi.idl.) */

/* ------------------------------------------------------------------
 * Book surface: bt-appdev (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms886634 Bluetooth Application Development Enumerations */
/* ms886635 Bluetooth Application Development Functions */
/* ms886636 Bluetooth Application Development Interfaces */
/* ms886637 Bluetooth Application Development IOCTLs */
/* ms886647 Bluetooth Application Development Structures */

/* ------------------------------------------------------------------
 * Book surface: bt-appdev (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa450534 ISdpNodeContainer::AppendNode (Header: Bthapi.h, Bthapi.idl.) */
/* aa450536 ISdpNodeContainer::CreateFromStream (Header: Bthapi.h, Bthapi.idl.) */
/* aa450539 ISdpNodeContainer::CreateStream (Header: Bthapi.h, Bthapi.idl.) */
/* aa450540 ISdpNodeContainer::GetNode (Header: Bthapi.h, Bthapi.idl.) */
/* aa450543 ISdpNodeContainer::GetNodeCount (Header: Bthapi.h, Bthapi.idl.) */
/* aa450545 ISdpNodeContainer::GetNodeStringData (Header: Bthapi.h, Bthapi.idl.) */
/* aa450547 ISdpNodeContainer::GetStreamSize (Header: Bthapi.h, Bthapi.idl.) */
/* aa450549 ISdpNodeContainer::GetType (Header: Bthapi.h, Bthapi.idl.) */
/* aa450553 ISdpNodeContainer::LockContainer (Header: Bthapi.h, Bthapi.idl.) */
/* aa450556 ISdpNodeContainer::SetNode (Header: Bthapi.h, Bthapi.idl.) */
/* aa450557 ISdpNodeContainer::SetType (Header: Bthapi.h, Bthapi.idl.) */
/* aa450560 ISdpNodeContainer::Walk (Header: Bthapi.h, Bthapi.idl.) */
/* aa450562 ISdpNodeContainer::WriteStream (Header: Bthapi.h, Bthapi.idl.) */
/* aa450579 ISdpRecord::CreateFromStream (Header: Bthapi.h, Bthapi.idl.) */
/* aa450582 ISdpRecord::GetAttribute (Header: Bthapi.h, Bthapi.idl.) */
/* aa450583 ISdpRecord::GetAttributeAsStream (Header: Bthapi.h, Bthapi.idl.) */
/* aa450586 ISdpRecord::GetAttributeList (Header: Bthapi.h, Bthapi.idl.) */
/* aa450588 ISdpRecord::GetServiceClass (Header: Bthapi.h, Bthapi.idl.) */
/* aa450591 ISdpRecord::SetAttribute (Header: Bthapi.h, Bthapi.idl.) */
/* aa450593 ISdpRecord::SetAttributeFromStream (Header: Bthapi.h, Bthapi.idl.) */
/* aa450595 ISdpRecord::Walk (Header: Bthapi.h, Bthapi.idl.) */
/* aa450597 ISdpRecord::WriteToStream (Header: Bthapi.h, Bthapi.idl.) */
/* aa450599 ISdpStream::ByteSwap* (Header: Bthapi.h, Bthapi.idl.) */
/* aa450603 ISdpStream::NormalizeUuid (Header: Bthapi.h, Bthapi.idl.) */
/* aa450605 ISdpStream::Retrieve* (Header: Bthapi.h, Bthapi.idl.) */
/* aa450607 ISdpStream::RetrieveElementInfo (Header: Bthapi.h, Bthapi.idl.) */
/* aa450609 ISdpStream::RetrieveRecords (Header: Bthapi.h, Bthapi.idl.) */
/* aa450611 ISdpStream::Validate (Header: Bthapi.h, Bthapi.idl.) */
/* aa450613 ISdpStream::VerifySequenceOf (Header: Bthapi.h, Bthapi.idl.) */
/* aa450615 ISdpStream::Walk (Header: Bthapi.h, Bthapi.idl.) */
/* aa450619 ISdpWalk::WalkNode (Header: Bthapi.h, Bthapi.idl.) */
/* aa450622 ISdpWalk::WalkStream (Header: Bthapi.h, Bthapi.idl.) */

/* ------------------------------------------------------------------
 * Book surface: bt-appdev (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms886634 Bluetooth Application Development Enumerations */
/* ms886635 Bluetooth Application Development Functions */
/* ms886636 Bluetooth Application Development Interfaces */
/* ms886637 Bluetooth Application Development IOCTLs */
/* ms886647 Bluetooth Application Development Structures */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_BTHAPI_H */
