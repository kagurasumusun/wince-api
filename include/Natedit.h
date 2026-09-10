/*
 * Natedit.h -- Network Address Translation (NAT) editor API, Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE pages of
 * the "Network Address Translation Reference" book (CE-era MSDN
 * archive, learn.microsoft.com previous-versions, (v=msdn.10) IDs).
 * Every CE page of this book prints Header: Natedit.h and Link
 * Library: Coredll.dll; OS Versions are "Windows CE 3.0 and later"
 * (the NAT editor API) except the logging callback pages ms886745..
 * ms886748 = "Windows CE .NET 4.1 and later".
 *
 * The NAT editor interface lets protocol editors hook into the NAT
 * driver's session/port-mapping machinery.  Most "functions" in this
 * book are editor-implemented callbacks whose prototypes the pages
 * publish in full; the exported entry points are the RegisterEditor and
 * EditorInitialize pair, CreateTicket and DeleteTicket, EditSession,
 * TimeoutSession and DisassociateSession.
 *
 * Clean-room boundaries recorded in docs/inventory.md: the structure
 * IP_NAT_REGISTER_EDITOR (ms885683) is documented as an *anonymous*
 * typedef whose members reference PNAT_EDITOR_* callback types that no
 * CE page defines separately, so only the structure type name and the
 * two pointer spellings the function pages use (PIP_NAT_REGISTER_EDITOR,
 * PNAT_REGISTER_EDITOR) are provided here -- the type is incomplete.
 * The IPRcvBuf page (ms885685) prints its members with lowercase type
 * tokens (uint, uchar) that are treated as the page's rendering of
 * the fixed types UINT and UCHAR (see the struct comments).
 */

#ifndef AKARI_NATEDIT_H
#define AKARI_NATEDIT_H

#include "Windef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ms885682 "IP_NAT_DIRECTION (Windows CE 5.0)": direction of a NAT
 * session mapping.  The page prints the enum without explicit values,
 * so the enumerators take the sequential values 0 and 1. */
enum IP_NAT_DIRECTION {
    NatInboundDirection,
    NatOutboundDirection,
};

/* ms885684 "IP_NAT_SESSION_MAPPING_STATISTICS (Windows CE 5.0)":
 * per-session byte/packet/reject counters (ULONG64 each), filled by
 * QueryInfoSession.  CE 3.0+; Natedit.h. */
typedef struct {
    ULONG64 BytesForward;
    ULONG64 BytesReverse;
    ULONG64 PacketsForward;
    ULONG64 PacketsReverse;
    ULONG64 RejectsForward;
    ULONG64 RejectsReverse;
} IP_NAT_SESSION_MAPPING_STATISTICS;
typedef IP_NAT_SESSION_MAPPING_STATISTICS *PIP_NAT_SESSION_MAPPING_STATISTICS;

/* ms885685 "IPRcvBuf (Windows CE 5.0)": received-packet buffer passed
 * to DataHandler/EditSession.  CE 3.0+; Natedit.h.  The page prints
 * the member types as lowercase tokens ("uint"/"uchar"); those are
 * read as the fixed Win32 types UINT and UCHAR * that the NAT pages
 * use everywhere (recorded in inventory). */
typedef struct IPRcvBuf {
    struct IPRcvBuf *ipr_next;   /* next buffer in the chain */
    UINT            ipr_reserved1;
    UCHAR          *ipr_buffer;  /* packet data */
    UINT            ipr_size;
    UINT            ipr_reserved2;
} IPRcvBuf;
typedef IPRcvBuf *PIPRCVBUF;     /* parameter type used by the pages */

/* ms885683 "IP_NAT_REGISTER_EDITOR (Windows CE 5.0)" documents the
 * registration structure with ULONG Version/Flags, UCHAR Protocol,
 * USHORT Port, an IP_NAT_DIRECTION Direction, a PVOID EditorContext,
 * and PNAT_EDITOR_* callback members (CreateHandler, DeleteHandler,
 * Forward/ReverseDataHandler, CreateTicket, DeleteTicket, Deregister,
 * DisassociateSession, EditSession, QueryInfoSession, ...).  The
 * PNAT_EDITOR_* callback types are not defined by any CE page (they
 * are only consumed as member types here), so the complete layout
 * cannot be reproduced clean-room; only the published type name and
 * the two pointer spellings used by RegisterEditor (ms886796) and
 * EditorInitialize (ms885210) are provided, as an incomplete type. */
typedef struct IP_NAT_REGISTER_EDITOR_ IP_NAT_REGISTER_EDITOR;
typedef IP_NAT_REGISTER_EDITOR *PIP_NAT_REGISTER_EDITOR;
typedef IP_NAT_REGISTER_EDITOR *PNAT_REGISTER_EDITOR;

/* --- NAT driver entry points (ms885210/ms886796, CE 3.0+). --------- */

/* ms885210 "EditorInitialize (Windows CE 5.0)":
 * NTSTATUS EditorInitialize(PNAT_REGISTER_EDITOR).  Lets the OS
 * initialize a NAT editor (called by the driver with the editor's
 * registration entry). */
AKARI_CE_IMPORT NTSTATUS EditorInitialize(PNAT_REGISTER_EDITOR RegisterEditor) AKARI_CE_NAME(EditorInitialize);

/* ms886796 "RegisterEditor (Windows CE 5.0)":
 * NTSTATUS RegisterEditor(PIP_NAT_REGISTER_EDITOR).  Registers a NAT
 * editor with the NAT driver. */
AKARI_CE_IMPORT NTSTATUS RegisterEditor(PIP_NAT_REGISTER_EDITOR RegisterContext) AKARI_CE_NAME(RegisterEditor);

/* --- Editor-implemented callback prototypes (pages publish them in
 * full; the driver calls into the registered editor). -------------- */

/* ms885179 "CreateHandler (Windows CE 5.0)": called by the NAT driver
 * when a mapping associated with a registered editor is created. */
AKARI_CE_IMPORT NTSTATUS CreateHandler(PVOID EditorContext, ULONG PrivateAddress,
                       USHORT PrivatePort, ULONG PublicAddress,
                       USHORT PublicPort, ULONG RemoteAddress,
                       USHORT RemotePort, PVOID *EditorSessionContextp) AKARI_CE_NAME(CreateHandler);

/* ms885191 "DataHandler (Windows CE 5.0)": called by the NAT driver
 * for each packet received during an editor-controlled session. */
AKARI_CE_IMPORT NTSTATUS DataHandler(PVOID InterfaceHandle, PVOID SessionHandle,
                     PVOID DataHandle, PVOID EditorContext,
                     PVOID EditorSessionContext, PIPRCVBUF RecvBuffer,
                     ULONG DataOffset) AKARI_CE_NAME(DataHandler);

/* ms885198 "DeleteHandler (Windows CE 5.0)": called by the NAT driver
 * when a mapping associated with an editor is removed. */
AKARI_CE_IMPORT NTSTATUS DeleteHandler(PVOID InterfaceHandle, PVOID SessionHandle,
                       PVOID EditorContext, PVOID EditorSessionContext) AKARI_CE_NAME(DeleteHandler);

/* --- NAT ticket (port mapping) management. ------------------------ */

/* ms885188 "CreateTicket (Windows CE 5.0)": creates a port mapping for
 * an inbound session.  Protocol is one of the NAT_PROTOCOL_* values of
 * IPNat.h (values not published on this page; recorded unknown). */
AKARI_CE_IMPORT NTSTATUS CreateTicket(PVOID InterfaceHandle, UCHAR Protocol,
                      ULONG PrivateAddress, USHORT PrivatePort,
                      ULONG RemoteAddress, USHORT RemotePort,
                      PULONG PublicAddress, PUSHORT PublicPort) AKARI_CE_NAME(CreateTicket);

/* ms885199 "DeleteTicket (Windows CE 5.0)": removes a NAT editor port
 * mapping (public endpoint identified by address/port/protocol). */
AKARI_CE_IMPORT NTSTATUS DeleteTicket(PVOID InterfaceHandle, ULONG PublicAddress,
                      UCHAR Protocol, USHORT PublicPort,
                      ULONG RemoteAddress, USHORT RemotePort) AKARI_CE_NAME(DeleteTicket);

/* ms885211 "EditSession (Windows CE 5.0)": replaces one range of bytes
 * in a packet with another range of bytes. */
AKARI_CE_IMPORT NTSTATUS EditSession(PVOID DataHandle, PIPRCVBUF RecvBuffer,
                     ULONG OldDataOffset, ULONG OldDataLength,
                     PUCHAR NewData, ULONG NewDataLength) AKARI_CE_NAME(EditSession);

/* ms886786 "QueryInfoSession (Windows CE 5.0)": obtains statistics for
 * a session; the endpoint output pointers are optional. */
AKARI_CE_IMPORT NTSTATUS QueryInfoSession(PVOID SessionHandle, PULONG PrivateAddress,
                          PUSHORT PrivatePort, PULONG RemoteAddress,
                          PUSHORT RemotePort, PULONG PublicAddress,
                          PUSHORT PublicPort,
                          PIP_NAT_SESSION_MAPPING_STATISTICS Statistics) AKARI_CE_NAME(QueryInfoSession);

/* aa450941 "TimeoutSession (Windows CE 5.0)": causes a session to time
 * out. */
AKARI_CE_IMPORT NTSTATUS TimeoutSession(PVOID EditorHandle, PVOID SessionHandle) AKARI_CE_NAME(TimeoutSession);

/* ms885201 "DisassociateSession (Windows CE 5.0)": stops an editor from
 * editing data on a specific session. */
AKARI_CE_IMPORT NTSTATUS DisassociateSession(PVOID EditorHandle, PVOID SessionHandle) AKARI_CE_NAME(DisassociateSession);

/* ms885209 "EditorDeregister (Windows CE 5.0)": removes the
 * registration of an editor. */
AKARI_CE_IMPORT NTSTATUS EditorDeregister(PVOID EditorHandle) AKARI_CE_NAME(EditorDeregister);

/* --- NAT logging callback prototypes (client monitoring DLLs;
 * ms886745..ms886748, CE .NET 4.1+).  The pages document these as
 * typedefs the client implements. ---------------------------------- */

/* ms886745: connection-creation monitor. */
typedef VOID (*PNAT_LOG_CONNECTION_CREATION)(
    DWORD LocalAddress, DWORD RemoteAddress,
    USHORT LocalPort, USHORT RemotePort,
    UCHAR Protocol, BOOLEAN InboundConnection);

/* ms886746: connection-deletion monitor. */
typedef VOID (*PNAT_LOG_CONNECTION_DELETION)(
    DWORD LocalAddress, DWORD RemoteAddress,
    USHORT LocalPort, USHORT RemotePort,
    UCHAR Protocol, BOOLEAN InboundConnection);

/* ms886747: dropped-packet monitor. */
typedef VOID (*PNAT_LOG_DROPPED_PACKET)(
    DWORD SourceAddr, DWORD DestAddr,
    USHORT SourcePort, USHORT DestPort, DWORD PacketSize,
    BYTE Protocol, DWORD Proto1, DWORD Proto2, DWORD Proto3, DWORD Proto4);

/* ms886748: initialization monitor. */
typedef VOID (*PNAT_LOG_INIT)(void);

/* ------------------------------------------------------------------
 * Book surface: core-nat-reference (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms886745 LogConnectionCreation: documented name-only (no value published; held) */
/* ms886746 LogConnectionDeletion: documented name-only (no value published; held) */
/* ms886747 LogDroppedPacket: documented name-only (no value published; held) */
/* ms886748 LogInit: documented name-only (no value published; held) */

/* ------------------------------------------------------------------
 * Book surface: core-nat-reference (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa450757 Network Address Translation Functions */
/* aa450759 Network Address Translation Structures */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_NATEDIT_H */
