/* Ndis.h -- Network Driver Interface Specification (NDIS).
 *
 * Source pages: Network Driver Reference book (msdn.10 archive),
 * tools/manifests/ndis.manifest (779 leaves).  This header carries
 * the Ndis.h rows: 354 pages whose Requirements row prints
 * Header: Ndis.h.
 *
 * Link Library rows print Ndis.lib (109 rows), Ndis.dll (58 rows,
 * module form of the same NDIS driver library -- mapped onto the
 * ndis.lib token in tools/gen-doc-def.py) and Ndislib.lib (15 rows:
 * the Protocol* driver-supplied callback set and the NDIS XXX_Init
 * stream entry -- driver-side code, not imports, so no def is
 * written for it).  Export def: def/ndis-doc.def (152 entries).
 *
 * CE generations: the pages carry "Windows CE .NET 4.0 and later"
 * rows (NDIS 5.0 miniport/protocol model).  Structure prints are
 * reproduced verbatim; glued tokens are split and documented typos
 * are repaired with a note at each site.  Types the CE
 * documentation never prints (MDL, UNICODE_STRING, the opaque NDIS
 * objects, the *_HANDLER callback typedefs, NDIS_REQUEST_TYPE,
 * NDIS_WAN_QUALITY, NDIS_CLASS_ID, NDIS_TASK, NDIS_ENCAPSULATION,
 * NDIS_MEDIUM, NDIS_PACKET_PRIVATE, MaxPerPacketInfo, ...) are
 * held: structures embedding them are recorded verbatim below and
 * functions taking them by value or through unpublished pointer
 * types are recorded, not declared.  See docs/inventory.md M78a.
 */

#ifndef AKARI_NDIS_H
#define AKARI_NDIS_H

#include "Windef.h"    /* PVOID, ULONG, UINT, BOOLEAN, UCHAR, ... */
#include "Winnt.h"     /* LARGE_INTEGER, ULONGLONG, ULONG_PTR */
#include "CEDDK.h"     /* INTERFACE_TYPE (ms901367) grounds the
                        * NDIS_INTERFACE_TYPE value names */

/* --- Annotation tokens printed by NDIS signatures (compat macros).
 * OPTIONAL, IN and OUT appear in the printed function signatures
 * (e.g. "PVOID* OPTIONAL" on NdisQueryBuffer, aa447917); CONST
 * prints in "CONST VOID*" parameter forms.  Desktop-equivalent
 * definitions, recorded as print-driven compat macros. */
#define OPTIONAL
#define IN
#define OUT
#define CONST const

/* --- Base types (printed on their own data-type pages). -------- */
/* aa447986 "NDIS_HANDLE":
 * `typedef PVOID NDIS_HANDLE,*PNDIS_HANDLE;` */
typedef PVOID NDIS_HANDLE, *PNDIS_HANDLE;

/* ms904981 "NDIS_STATUS":
 * `typedef int NDIS_STATUS, *PNDIS_STATUS;` */
typedef int NDIS_STATUS, *PNDIS_STATUS;

/* ms904076 "NDIS_OID":
 * `typedef ULONG NDIS_OID, *PNDIS_OID;` */
typedef ULONG NDIS_OID, *PNDIS_OID;

/* aa447948 "NDIS_ERROR_CODE":
 * `#define NDIS_ERROR_CODE ULONG` */
#define NDIS_ERROR_CODE ULONG

/* ms904092 "NDIS_PHYSICAL_ADDRESS": print
 * `typedefPHYSICAL_ADDRESS NDIS_PHYSICAL_ADDRESS,
 * *PNDIS_PHYSICAL_ADDRESS;` (typedef/name glued).  The page remark
 * prints PHYSICAL_ADDRESS as "equivalent to the system-defined
 * LARGE_INTEGER type"; PHYSICAL_ADDRESS is closed on Winnt.h
 * LARGE_INTEGER (recorded path). */
typedef LARGE_INTEGER PHYSICAL_ADDRESS, *PPHYSICAL_ADDRESS;
typedef PHYSICAL_ADDRESS NDIS_PHYSICAL_ADDRESS, *PNDIS_PHYSICAL_ADDRESS;

/* aa447913 "NDIS_BUFFER":
 * `typedef MDL NDIS_BUFFER, *PNDIS_BUFFER;` -- MDL is not printed
 * by any CE page (the page remark describes "a length, a pointer,
 * and a next field" only), so MDL is closed opaquely and every
 * documented use stays pointer-only. */
struct _MDL;
typedef struct _MDL MDL, *PMDL;
typedef MDL NDIS_BUFFER, *PNDIS_BUFFER;

/* ms904983 "NDIS_STRING":
 * `typedef UNICODE_STRING NDIS_STRING, *PNDIS_STRING;` --
 * UNICODE_STRING is not printed by any CE page ("counted,
 * zero-terminated Unicode string" per the page); opaque closure,
 * pointer-only uses. */
struct _UNICODE_STRING;
typedef struct _UNICODE_STRING UNICODE_STRING, *PUNICODE_STRING;
typedef UNICODE_STRING NDIS_STRING, *PNDIS_STRING;

/* ANSI twin (NdisAnsiStringToUnicodeString and
 * NdisUnicodeStringToAnsiString signatures print
 * PNDIS_ANSI_STRING): ANSI_STRING is not printed by any CE page;
 * opaque closure. */
struct _ANSI_STRING;
typedef struct _ANSI_STRING NDIS_ANSI_STRING, *PNDIS_ANSI_STRING;

/* ms904098 "NDIS_PROC": print `typedefVOID (*NDIS_PROC)
 * (struct _NDIS_WORK_ITEM *,PVOID);` (typedef/VOID glued).  The
 * tag is forward-declared so the prototype-scope struct does not
 * shadow the NDIS_WORK_ITEM definition below. */
struct _NDIS_WORK_ITEM;
typedef VOID (*NDIS_PROC)(struct _NDIS_WORK_ITEM *, PVOID);

/* ms905054 "NDIS_WORK_ITEM": print `Typedefstruct _NDIS_WORK_ITEM
 * {PVOID Context; NDIS_PROC Routine; UCHAR WrapperReserved;);`
 * (Typedef/struct glued; the trailing `);` is a doc typo for `];`
 * per the member table "WrapperReserved: array of 16 UCHAR
 * reserved" -- reproduced as printed, see remark below). */
typedef struct _NDIS_WORK_ITEM {
    PVOID     Context;
    NDIS_PROC Routine;
    UCHAR     WrapperReserved;
} NDIS_WORK_ITEM, *PNDIS_WORK_ITEM;

/* --- Enumerations (printed). ----------------------------------- */

/* ms904999 "NDIS_PARAMETER_TYPE": print (implicit successors). */
typedef enum _NDIS_PARAMETER_TYPE {
    NdisParameterInteger,
    NdisParameterHexInteger,
    NdisParameterString,
    NdisParameterBinary
} NDIS_PARAMETER_TYPE, *PNDIS_PARAMETER_TYPE;

/* "NDIS_INTERFACE_TYPE" (Ndis.h data-type row): print
 * `typedef enum _NDIS_INTERFACE_TYPE {NdisInterfaceInternal =
 * Internal, NdisInterfaceIsa = Isa, NdisInterfaceEisa = Eisa,
 * NdisInterfaceMca = MicroChannel, NdisInterfaceTurboChannel =
 * TurboChannel, NdisInterfacePci = PCIBus, NdisInterfacePcMcia =
 * PCMCIABus, NdisInterfaceCBus = CBus, NdisInterfaceMPIBus =
 * MPIBus, NdisInterfaceMPSABus = MPSABus,
 * NdisInterfaceProcessorInternal = ProcessorInternal,
 * NdisInterfaceInternalPowerBus = InternalPowerBus,
 * NdisInterfacePNPISABus = PNPISABus, NdisInterfacePNPBus =
 * PNPBus, NdisMaximumInterfaceType,} NDIS_INTERFACE_TYPE,
 * *PNDIS_INTERFACE_TYPE;` -- every value expression is an
 * INTERFACE_TYPE enumerator printed by CEDDK.h (ms901367). */
typedef enum _NDIS_INTERFACE_TYPE {
    NdisInterfaceInternal         = Internal,
    NdisInterfaceIsa              = Isa,
    NdisInterfaceEisa             = Eisa,
    NdisInterfaceMca              = MicroChannel,
    NdisInterfaceTurboChannel     = TurboChannel,
    NdisInterfacePci              = PCIBus,
    NdisInterfacePcMcia           = PCMCIABus,
    NdisInterfaceCBus             = CBus,
    NdisInterfaceMPIBus           = MPIBus,
    NdisInterfaceMPSABus          = MPSABus,
    NdisInterfaceProcessorInternal = ProcessorInternal,
    NdisInterfaceInternalPowerBus = InternalPowerBus,
    NdisInterfacePNPISABus        = PNPISABus,
    NdisInterfacePNPBus           = PNPBus,
    NdisMaximumInterfaceType
} NDIS_INTERFACE_TYPE, *PNDIS_INTERFACE_TYPE;

/* aa448018 "NDIS_INTERRUPT_MODE": print
 * `typedef KINTERRUPT_MODE NDIS_INTERRUPT_MODE,
 * *PNDIS_INTERRUPT_MODE;` -- KINTERRUPT_MODE is not printed by any
 * CE page.  The page member table prints the two mode names
 * (NdisInterruptLatched / NdisInterruptLevelSensitive); the enum
 * is closed on those names (implicit successors), KINTERRUPT_MODE
 * print recorded. */
typedef enum {
    NdisInterruptLatched,
    NdisInterruptLevelSensitive
} NDIS_INTERRUPT_MODE, *PNDIS_INTERRUPT_MODE;

/* --- Structures whose print is fully grounded. ----------------- */

/* ms904087 "NDIS_PACKET_OOB_DATA": print `typedef struct
 * _NDIS_PACKET_OOB_DATA {union { ULONGLONG TimeToSend; ULONGLONG
 * TimeSent;};ULONGLONG TimeReceived;UINT HeaderSize;UINT
 * SizeMediaSpecificInfo;PVOID MediaSpecificInformation;
 * NDIS_STATUS Status;} NDIS_PACKET_OOB_DATA, *PNDIS_PACKET_OOB_DATA;` */
typedef struct _NDIS_PACKET_OOB_DATA {
    union {
        ULONGLONG TimeToSend;
        ULONGLONG TimeSent;
    };
    ULONGLONG TimeReceived;
    UINT      HeaderSize;
    UINT      SizeMediaSpecificInfo;
    PVOID     MediaSpecificInformation;
    NDIS_STATUS Status;
} NDIS_PACKET_OOB_DATA, *PNDIS_PACKET_OOB_DATA;

/* ms904089 "NDIS_PACKET_STACK": print (glued tokens split). */
typedef struct _NDIS_PACKET_STACK {
    ULONG_PTR IMReserved[2];
    ULONG_PTR NdisReserved[4];
} NDIS_PACKET_STACK, *PNDIS_PACKET_STACK;

/* "TRANSPORT_HEADER_OFFSET" (Ndis.h data-type row): print. */
typedef struct _TRANSPORT_HEADER_OFFSET {
    USHORT ProtocolType;
    USHORT HeaderOffset;
} TRANSPORT_HEADER_OFFSET, *PTRANSPORT_HEADER_OFFSET;

/* aa448020 "NDIS_MAC_LINE_DOWN": print. */
typedef struct _NDIS_MAC_LINE_DOWN {
    NDIS_HANDLE NdisLinkContext;
} NDIS_MAC_LINE_DOWN, *PNDIS_MAC_LINE_DOWN;

/* aa448019 "NDIS_MAC_FRAGMENT": print (`ULONGErrors` glued). */
typedef struct _NDIS_MAC_FRAGMENT {
    NDIS_HANDLE NdisLinkContext;
    ULONG       Errors;
} NDIS_MAC_FRAGMENT, *PNDIS_MAC_FRAGMENT;

/* ms905047 "NDIS_WAN_LINE_DOWN": print. */
typedef struct _NDIS_WAN_LINE_DOWN {
    UCHAR RemoteAddress[6];
    UCHAR LocalAddress[6];
} NDIS_WAN_LINE_DOWN, *PNDIS_WAN_LINE_DOWN;

/* ms905046 "NDIS_WAN_INFO": print (glued tokens split). */
typedef struct _NDIS_WAN_INFO {
    ULONG               MaxFrameSize;
    ULONG               MaxTransmit;
    ULONG               HeaderPadding;
    ULONG               TailPadding;
    ULONG               Endpoints;
    UINT                MemoryFlags;
    NDIS_PHYSICAL_ADDRESS HighestAcceptableAddress;
    ULONG               FramingBits;
    ULONG               DesiredACCM;
} NDIS_WAN_INFO, *PNDIS_WAN_INFO;

/* ms905042 "NDIS_WAN_COMPRESS_INFO": print (glued tokens split). */
typedef struct _NDIS_WAN_COMPRESS_INFO {
    UCHAR  SessionKey[8];
    ULONG  MSCompType;
    UCHAR  CompType;
    USHORT CompLength;
    union {
        struct {
            UCHAR CompOUI[3];
            UCHAR CompSubType;
            UCHAR CompValues[32];
        } Proprietary;
        struct {
            UCHAR CompValues[32];
        } Public;
    };
} NDIS_WAN_COMPRESS_INFO;

/* "NDIS_WAN_GET_LINK_INFO" (Ndis.h data-type row): print. */
typedef struct _NDIS_WAN_GET_LINK_INFO {
    NDIS_HANDLE NdisLinkHandle;
    ULONG       MaxSendFrameSize;
    ULONG       MaxRecvFrameSize;
    ULONG       HeaderPadding;
    ULONG       TailPadding;
    ULONG       SendFramingBits;
    ULONG       RecvFramingBits;
    ULONG       SendCompressionBits;
    ULONG       RecvCompressionBits;
    ULONG       SendACCM;
    ULONG       RecvACCM;
} NDIS_WAN_GET_LINK_INFO, *PNDIS_WAN_GET_LINK_INFO;

/* "NDIS_WAN_SET_LINK_INFO" (Ndis.h data-type row): print. */
typedef struct _NDIS_WAN_SET_LINK_INFO {
    NDIS_HANDLE NdisLinkHandle;
    ULONG       MaxSendFrameSize;
    ULONG       MaxRecvFrameSize;
    ULONG       HeaderPadding;
    ULONG       TailPadding;
    ULONG       SendFramingBits;
    ULONG       RecvFramingBits;
    ULONG       SendCompressionBits;
    ULONG       RecvCompressionBits;
    ULONG       SendACCM;
    ULONG       RecvACCM;
} NDIS_WAN_SET_LINK_INFO, *PNDIS_WAN_SET_LINK_INFO;

/* "NDIS_WAN_GET_COMP_INFO" (Ndis.h data-type row): print. */
typedef struct _NDIS_WAN_GET_COMP_INFO {
    NDIS_HANDLE           NdisLinkHandle;
    NDIS_WAN_COMPRESS_INFO SendCapabilities;
    NDIS_WAN_COMPRESS_INFO RecvCapabilities;
} NDIS_WAN_GET_COMP_INFO, *PNDIS_WAN_GET_COMP_INFO;

/* "NDIS_WAN_SET_COMP_INFO" (Ndis.h data-type row): print. */
typedef struct _NDIS_WAN_SET_COMP_INFO {
    NDIS_HANDLE           NdisLinkHandle;
    NDIS_WAN_COMPRESS_INFO SendCapabilities;
    NDIS_WAN_COMPRESS_INFO RecvCapabilities;
} NDIS_WAN_SET_COMP_INFO, *PNDIS_WAN_SET_COMP_INFO;

/* "NDIS_WAN_GET_STATS_INFO" (Ndis.h data-type row): print. */
typedef struct _NDIS_WAN_GET_STATS_INFO {
    NDIS_HANDLE NdisLinkHandle;
    ULONG       BytesSent;
    ULONG       BytesRcvd;
    ULONG       FramesSent;
    ULONG       FramesRcvd;
    ULONG       CRCErrors;
    ULONG       TimeoutErrors;
    ULONG       AlignmentErrors;
    ULONG       SerialOverrunErrors;
    ULONG       FramingErrors;
    ULONG       BufferOverrunErrors;
    ULONG       BytesTransmittedUncompressed;
    ULONG       BytesReceivedUncompressed;
    ULONG       BytesTransmittedCompressed;
    ULONG       BytesReceivedCompressed;
} NDIS_WAN_GET_STATS_INFO, *PNDIS_WAN_GET_STATS_INFO;

/* ms905025 "NDIS_TASK_TCP_IP_CHECKSUM": print. */
typedef struct _NDIS_TASK_TCP_IP_CHECKSUM {
    struct {
        ULONG IpOptionsSupported;
        ULONG TcpOptionsSupported;
        ULONG TcpChecksum;
        ULONG UdpChecksum;
        ULONG IpChecksum;
    } V4Transmit;
    struct {
        ULONG IpOptionsSupported;
        ULONG TcpOptionsSupported;
        ULONG TcpChecksum;
        ULONG UdpChecksum;
        ULONG IpChecksum;
    } V4Receive;
    struct {
        ULONG IpOptionsSupported;
        ULONG TcpOptionsSupported;
        ULONG TcpChecksum;
        ULONG UdpChecksum;
    } V6Transmit;
    struct {
        ULONG IpOptionsSupported;
        ULONG TcpOptionsSupported;
        ULONG TcpChecksum;
        ULONG UdpChecksum;
    } V6Receive;
} NDIS_TASK_TCP_IP_CHECKSUM, *PNDIS_TASK_TCP_IP_CHECKSUM;

/* ms905026 "NDIS_TASK_TCP_LARGE_SEND": print. */
typedef struct _NDIS_TASK_TCP_LARGE_SEND {
    ULONG   Version;
    ULONG   MaxOffLoadSize;
    ULONG   MinSegmentCount;
    BOOLEAN TcpOptions;
    BOOLEAN IpOptions;
} NDIS_TASK_TCP_LARGE_SEND, *PNDIS_TASK_TCP_LARGE_SEND;

/* "NDIS_TCP_IP_CHECKSUM_PACKET_INFO" (Ndis.h data-type row): print
 * (one-bit bitfields, Value alias). */
typedef struct _NDIS_TCP_IP_CHECKSUM_PACKET_INFO {
    union {
        struct {
            ULONG NdisPacketChecksumV4:1;
            ULONG NdisPacketChecksumV6:1;
            ULONG NdisPacketTcpChecksum:1;
            ULONG NdisPacketUdpChecksum:1;
            ULONG NdisPacketIpChecksum:1;
        } Transmit;
        struct {
            ULONG NdisPacketTcpChecksumFailed:1;
            ULONG NdisPacketUdpChecksumFailed:1;
            ULONG NdisPacketIpChecksumFailed:1;
            ULONG NdisPacketTcpChecksumSucceeded:1;
            ULONG NdisPacketUdpChecksumSucceeded:1;
            ULONG NdisPacketIpChecksumSucceeded:1;
            ULONG NdisPacketLoopback:1;
        } Receive;
        ULONG Value;
    };
} NDIS_TCP_IP_CHECKSUM_PACKET_INFO, *PNDIS_TCP_IP_CHECKSUM_PACKET_INFO;

/* --- Held structures: the CE documentation prints the layout but
 *     embeds a type no CE page prints.  Each print is recorded
 *     verbatim and the struct is closed opaquely (pointer-only). - */

/* ms904419 "NDIS_REQUEST": print `typedef struct _ NDIS_REQUEST
 * {UCHARMacReserved[16];NDIS_REQUEST_TYPERequestType;union _DATA {
 * struct QUERY_INFORMATION { NDIS_OIDOid; PVOIDInformationBuffer;
 * UINTInformationBufferLength; UINTBytesWritten; UINTBytesNeeded; }
 * QUERY_INFORMATION; ... } NDIS_REQUEST, *PNDIS_REQUEST;` -- the
 * tag prints "_ NDIS_REQUEST" (stray space, repaired in the
 * forward below); NDIS_REQUEST_TYPE is not printed by any CE page,
 * so the layout is held. */
typedef struct _NDIS_REQUEST NDIS_REQUEST, *PNDIS_REQUEST;

/* ms904084 "NDIS_PACKET": print `typedef struct _NDIS_PACKET
 * {NDIS_PACKET_PRIVATE Private;union { struct { UCHAR
 * MiniportReserved[2*sizeof(PVOID)]; UCHAR
 * WrapperReserved[2*sizeof(PVOID)]; }; ... } NDIS_PACKET,
 * *PNDIS_PACKET;` -- NDIS_PACKET_PRIVATE is not printed by any CE
 * page; held (glued tokens split, layout recorded). */
typedef struct _NDIS_PACKET NDIS_PACKET, *PNDIS_PACKET;

/* ms904085 "NDIS_PACKET_EXTENSION": print `typedef struct
 * _NDIS_PACKET_EXTENSION {PVOID NdisPacketInfo[MaxPerPacketInfo];}
 * NDIS_PACKET_EXTENSION, *PNDIS_PACKET_EXTENSION;` -- the
 * MaxPerPacketInfo constant is not printed by any CE page; held. */
typedef struct _NDIS_PACKET_EXTENSION NDIS_PACKET_EXTENSION, *PNDIS_PACKET_EXTENSION;

/* ms904418 "NDIS_CONFIGURATION_PARAMETER": print `typedef struct
 * _NDIS_CONFIGURATION_PARAMETER {NDIS_PARAMETER_TYPE ParameterType;
 * union { ULONG IntegerData; NDIS_STRING StringData; BINARY_DATA
 * BinaryData;} ParameterData;} NDIS_CONFIGURATION_PARAMETER,
 * *PNDIS_CONFIGURATION_PARAMETER;` -- BINARY_DATA is not printed
 * by any CE page; held. */
typedef struct _NDIS_CONFIGURATION_PARAMETER NDIS_CONFIGURATION_PARAMETER,
    *PNDIS_CONFIGURATION_PARAMETER;

/* ms905050 "NDIS_WAN_PACKET": print `typedef struct _NDIS_WAN_PACKET
 * {LIST_ENTRY WanPacketQueue;PUCHAR CurrentBuffer;ULONG
 * CurrentLength;PUCHAR StartBuffer;PUCHAR EndBuffer;PVOID
 * ProtocolReserved1;...;PVOID MiniportReserved1;...} NDIS_WAN_PACKET,
 * *PNDIS_WAN_PACKET;` -- LIST_ENTRY is not printed by any CE page;
 * held. */
typedef struct _NDIS_WAN_PACKET NDIS_WAN_PACKET, *PNDIS_WAN_PACKET;

/* ms904099 "NDIS_PROTOCOL_CHARACTERISTICS": print `typedef struct
 * _NDIS_PROTOCOL_CHARACTERISTICS{UCHARMajorNdisVersion; UCHAR
 * MinorNdisVersion; UINTReserved; OPEN_ADAPTER_COMPLETE_HANDLER
 * OpenAdapterCompleteHandler; ...; NDIS_STRINGName; ...;
 * UNLOAD_PROTOCOL_HANDLERUnloadHandler;}NDIS_PROTOCOL_CHARACTERISTICS,
 * *PNDIS_PROTOCOL_CHARACTERISTICS` -- all eighteen *_HANDLER
 * callback typedefs are unpublished on CE pages; held (full print
 * recorded in docs/inventory.md M78a). */
typedef struct _NDIS_PROTOCOL_CHARACTERISTICS NDIS_PROTOCOL_CHARACTERISTICS,
    *PNDIS_PROTOCOL_CHARACTERISTICS;

/* aa448041 "NDIS_MINIPORT_CHARACTERISTICS": print `typedef struct
 * _NDIS_MINIPORT_CHARACTERISTICS { UCHARMajorNdisVersion;UCHAR
 * MinorNdisVersion; UINTReserved; W_CHECK_FOR_HANG_HANDLER
 * CheckForHangHandler;W_DISABLE_INTERRUPT_HANDLER
 * DisableInterruptHandler; W_ENABLE_INTERRUPT_HANDLER
 * EnableInterruptHandler; ... } NDIS_MINIPORT_CHARACTERISTICS,
 * *PNDIS_MINIPORT_CHARACTERISTICS;` -- the W_*_HANDLER callback
 * typedefs are unpublished on CE pages; held. */
typedef struct _NDIS_MINIPORT_CHARACTERISTICS NDIS_MINIPORT_CHARACTERISTICS,
    *PNDIS_MINIPORT_CHARACTERISTICS;

/* ms905023 "NDIS_TASK_OFFLOAD": print `typedef struct _NDIS_TASK_OFFLOAD
 * {ULONG Version;ULONG Size;NDIS_TASK Task;ULONG OffsetNextTask;
 * ULONG TaskBufferLength;UCHAR TaskBuffer[1];} NDIS_TASK_OFFLOAD,
 * *PNDIS_TASK_OFFLOAD;` -- NDIS_TASK is not printed by any CE page
 * (it is a union of NDIS_TASK_TCP_IP_CHECKSUM / TCP_LARGE_SEND /
 * IPSEC offload bodies per the page prose); held. */
typedef struct _NDIS_TASK_OFFLOAD NDIS_TASK_OFFLOAD, *PNDIS_TASK_OFFLOAD;

/* aa447943 "NDIS_ENCAPSULATION_FORMAT": print `typedef struct
 * _NDIS_ENCAPSULATION_FORMAT {NDIS_ENCAPSULATION Encapsulation;
 * struct{ ULONG FixedHeaderSize:1;ULONG Reserved:31;} Flags;ULONG
 * EncapsulationHeaderSize;} NDIS_ENCAPSULATION_FORMAT,
 * *PNDIS_ENCAPSULATION_FORMAT;` -- the NDIS_ENCAPSULATION
 * enumeration is not printed by any CE page; held. */
typedef struct _NDIS_ENCAPSULATION_FORMAT NDIS_ENCAPSULATION_FORMAT,
    *PNDIS_ENCAPSULATION_FORMAT;

/* "NDIS_TASK_OFFLOAD_HEADER" (Ndis.h data-type row): print embeds
 * NDIS_ENCAPSULATION_FORMAT by value (unpublished member type);
 * held. */
typedef struct _NDIS_TASK_OFFLOAD_HEADER NDIS_TASK_OFFLOAD_HEADER,
    *PNDIS_TASK_OFFLOAD_HEADER;

/* aa447840 "MediaSpecificInformation": print `typedef struct
 * MediaSpecificInformation {UINTNextEntryOffset;NDIS_CLASS_IDClassId;
 * UINTSize;UCHARClassInformation[1];} MEDIA_SPECIFIC_INFORMATION;`
 * -- NDIS_CLASS_ID is not printed by any CE page; held (typedef
 * name MEDIA_SPECIFIC_INFORMATION, tag without underscore as
 * printed). */
typedef struct MediaSpecificInformation MEDIA_SPECIFIC_INFORMATION,
    *PMEDIA_SPECIFIC_INFORMATION;

/* aa448021 "NDIS_MAC_LINE_UP": print `typedef struct _NDIS_MAC_LINE_UP
 * {ULONG LinkSpeed;NDIS_WAN_QUALITY Quality;USHORT SendWindow;
 * NDIS_HANDLE ConnectionWrapperID;NDIS_HANDLE NdisLinkHandle;
 * NDIS_HANDLE NdisLinkContext;} NDIS_MAC_LINE_UP, *PNDIS_MAC_LINE_UP;`
 * -- NDIS_WAN_QUALITY is not printed by any CE page; held. */
typedef struct _NDIS_MAC_LINE_UP NDIS_MAC_LINE_UP, *PNDIS_MAC_LINE_UP;

/* ms905048 "NDIS_WAN_LINE_UP": print `typedef struct _NDIS_WAN_LINE_UP
 * {ULONG LinkSpeed;ULONG MaximumTotalSize;NDIS_WAN_QUALITY Quality;
 * USHORT SendWindow;UCHAR RemoteAddress[6];UCHAR LocalAddress[6];
 * ULONG ProtocolBufferLength;PUCHAR ProtocolBuffer;USHORT
 * ProtocolType;NDIS_STRIN...} NDIS_WAN_LINE_UP, *PNDIS_WAN_LINE_UP;`
 * -- NDIS_WAN_QUALITY is not printed by any CE page; held. */
typedef struct _NDIS_WAN_LINE_UP NDIS_WAN_LINE_UP, *PNDIS_WAN_LINE_UP;

/* "NETWORK_ADDRESS" (Ndis.h data-type row): print `typedef struct
 * _NETWORK_ADDRESS { LONGAddressCount; USHORTAddressType;
 * NETWORK_ADDRESSAddress[1];} NETWORK_ADDRESS, *PNETWORK_ADDRESS;`
 * -- the printed body self-references NETWORK_ADDRESS (the page
 * duplicates the _LIST body; doc bug), so no member layout is
 * grounded; held. */
typedef struct _NETWORK_ADDRESS NETWORK_ADDRESS, *PNETWORK_ADDRESS;

/* "NETWORK_ADDRESS_LIST" (Ndis.h data-type row): print `typedef
 * struct _NETWORK_ADDRESS_LIST { LONGAddressCount; USHORTAddressType;
 * NETWORK_ADDRESSAddress[1];} NETWORK_ADDRESS_LIST,
 * *PNETWORK_ADDRESS_LIST;` -- embeds the held NETWORK_ADDRESS;
 * held. */
typedef struct _NETWORK_ADDRESS_LIST NETWORK_ADDRESS_LIST,
    *PNETWORK_ADDRESS_LIST;

/* --- Opaque NDIS objects (no CE page prints the layout; every
 *     documented use is through a pointer). ----------------------- */
typedef struct _NDIS_SPIN_LOCK NDIS_SPIN_LOCK, *PNDIS_SPIN_LOCK;
typedef struct _NDIS_RW_LOCK NDIS_RW_LOCK, *PNDIS_RW_LOCK;
typedef struct _LOCK_STATE LOCK_STATE, *PLOCK_STATE;
typedef struct _NDIS_TIMER NDIS_TIMER, *PNDIS_TIMER;
typedef struct _NDIS_EVENT NDIS_EVENT, *PNDIS_EVENT;
typedef struct _NDIS_MINIPORT_INTERRUPT NDIS_MINIPORT_INTERRUPT, *PNDIS_MINIPORT_INTERRUPT;
typedef struct _NDIS_MINIPORT_TIMER NDIS_MINIPORT_TIMER, *PNDIS_MINIPORT_TIMER;
typedef struct _NET_PNP_EVENT NET_PNP_EVENT, *PNET_PNP_EVENT;
typedef struct _NDIS_RESOURCE_LIST NDIS_RESOURCE_LIST, *PNDIS_RESOURCE_LIST;

/* --- Functions. ------------------------------------------------- */
/* Every Ndis.h function page whose printed signature is fully
 * grounded in printed types is declared below (the print is quoted
 * at each site; glued tokens split, IN/OUT/OPTIONAL annotations
 * dropped per the compat macros above).  Functions whose prints
 * name a type no CE page prints (NDIS_DMA_SIZE,
 * ADAPTER_SHUTDOWN_HANDLER, PNDIS_TIMER_FUNCTION, NTSTATUS,
 * PNDIS_MEDIUM, NDIS_PER_PACKET_INFO_Id, NDIS_PACKET_OP,
 * PNDIS_PHYSICAL_ADDRESS_UNIT, the lookaside-list types, STRING,
 * MM_PAGE_PRIORITY) are recorded verbatim in the record section.
 */

/* "NdisAcquireReadWriteLock" (aa447900): print `VOID NdisAcquireReadWriteLock(PNDIS_RW_LOCKLock,BOOLEANfWrite,PLOCK_STATELockState)` */
AKARI_CE_IMPORT VOID  NdisAcquireReadWriteLock(PNDIS_RW_LOCK Lock, BOOLEAN fWrite, PLOCK_STATE LockState)
                    AKARI_CE_NAME(NdisAcquireReadWriteLock);

/* "NdisAcquireSpinLock" (aa447901): print `VOID NdisAcquireSpinLock(PNDIS_SPIN_LOCKSpinLock)` */
AKARI_CE_IMPORT VOID  NdisAcquireSpinLock(PNDIS_SPIN_LOCK SpinLock)
                    AKARI_CE_NAME(NdisAcquireSpinLock);

/* "NdisAdjustBufferLength" (aa447902): print `VOID NdisAdjustBufferLength(PNDIS_BUFFER Buffer,UINT Length)` */
AKARI_CE_IMPORT VOID  NdisAdjustBufferLength(PNDIS_BUFFER Buffer, UINT Length)
                    AKARI_CE_NAME(NdisAdjustBufferLength);

/* "NdisAllocateBuffer" (aa447903): print `VOID NdisAllocateBuffer(PNDIS_STATUS Status,PNDIS_BUFFER* Buffer,NDIS_HANDLE PoolHandle,PVOID VirtualAddress,UINT Length)` */
AKARI_CE_IMPORT VOID  NdisAllocateBuffer(PNDIS_STATUS Status, PNDIS_BUFFER*Buffer, NDIS_HANDLE PoolHandle, PVOID VirtualAddress, UINT Length)
                    AKARI_CE_NAME(NdisAllocateBuffer);

/* "NdisAllocateBufferPool" (aa447904): print `VOID NdisAllocateBufferPool(PNDIS_STATUSStatus,PNDIS_HANDLEPoolHandle,UINTNumberOfDescriptors)` */
AKARI_CE_IMPORT VOID  NdisAllocateBufferPool(PNDIS_STATUS Status, PNDIS_HANDLE PoolHandle, UINT NumberOfDescriptors)
                    AKARI_CE_NAME(NdisAllocateBufferPool);

/* "NdisAllocateMemory" (aa447905): print `NDIS_STATUS NdisAllocateMemory(PVOID* VirtualAddress,UINTLength,UINTMemoryFlags,NDIS_PHYSICAL_ADDRESSHighestAcceptableAddress)` */
AKARI_CE_IMPORT NDIS_STATUS  NdisAllocateMemory(PVOID*VirtualAddress, UINT Length, UINT MemoryFlags, NDIS_PHYSICAL_ADDRESS HighestAcceptableAddress)
                    AKARI_CE_NAME(NdisAllocateMemory);

/* "NdisAllocateMemoryWithTag" (aa447906): print `NDIS_STATUS NdisAllocateMemoryWithTag(PVOID* VirtualAddress,UINTLength,ULONGTag)` */
AKARI_CE_IMPORT NDIS_STATUS  NdisAllocateMemoryWithTag(PVOID*VirtualAddress, UINT Length, ULONG Tag)
                    AKARI_CE_NAME(NdisAllocateMemoryWithTag);

/* "NdisAllocatePacket" (aa447907): print `VOID NdisAllocatePacket(PNDIS_STATUSStatus,PNDIS_PACKET* Packet,NDIS_HANDLEPoolHandle)` */
AKARI_CE_IMPORT VOID  NdisAllocatePacket(PNDIS_STATUS Status, PNDIS_PACKET*Packet, NDIS_HANDLE PoolHandle)
                    AKARI_CE_NAME(NdisAllocatePacket);

/* "NdisAllocatePacketPool" (aa447908): print `VOID NdisAllocatePacketPool(PNDIS_STATUSStatus,PNDIS_HANDLEPoolHandle,UINTNumberOfDescriptors,UINTProtocolReservedLength)` */
AKARI_CE_IMPORT VOID  NdisAllocatePacketPool(PNDIS_STATUS Status, PNDIS_HANDLE PoolHandle, UINT NumberOfDescriptors, UINT ProtocolReservedLength)
                    AKARI_CE_NAME(NdisAllocatePacketPool);

/* "NdisAllocateSpinLock" (aa447910): print `VOID NdisAllocateSpinLock(PNDIS_SPIN_LOCKSpinLock)` */
AKARI_CE_IMPORT VOID  NdisAllocateSpinLock(PNDIS_SPIN_LOCK SpinLock)
                    AKARI_CE_NAME(NdisAllocateSpinLock);

/* "NdisAnsiStringToUnicodeString" (aa447911): print `NDIS_STATUS NdisAnsiStringToUnicodeString(PNDIS_STRING DestinationString,PNDIS_ANSI_STRING SourceString)` */
AKARI_CE_IMPORT NDIS_STATUS  NdisAnsiStringToUnicodeString(PNDIS_STRING DestinationString, PNDIS_ANSI_STRING SourceString)
                    AKARI_CE_NAME(NdisAnsiStringToUnicodeString);

/* "NdisBindProtocolsToAdapter" (aa447912): print `VOID NdisBindProtocolsToAdapter(PNDIS_STATUSpStatus,PWSTRwszAdapterInstanceName,PWSTRwszProtocolName)` */
AKARI_CE_IMPORT VOID  NdisBindProtocolsToAdapter(PNDIS_STATUS pStatus, PWSTR wszAdapterInstanceName, PWSTR wszProtocolName)
                    AKARI_CE_NAME(NdisBindProtocolsToAdapter);

/* "NdisBufferLength" (aa447914): print `ULONG NdisBufferLength(PNDIS_BUFFERBuffer)` */
AKARI_CE_IMPORT ULONG  NdisBufferLength(PNDIS_BUFFER Buffer)
                    AKARI_CE_NAME(NdisBufferLength);

/* "NdisBufferVirtualAddress" (aa447917): print `PVOID NdisBufferVirtualAddress(PNDIS_BUFFERBuffer)` */
AKARI_CE_IMPORT PVOID  NdisBufferVirtualAddress(PNDIS_BUFFER Buffer)
                    AKARI_CE_NAME(NdisBufferVirtualAddress);

/* "NdisCancelSendPackets" (aa447919): print `VOID NdisCancelSendPackets(NDIS_HANDLE NdisBindingHandle,ULONG_PTR CancelId)` */
AKARI_CE_IMPORT VOID  NdisCancelSendPackets(NDIS_HANDLE NdisBindingHandle, ULONG_PTR CancelId)
                    AKARI_CE_NAME(NdisCancelSendPackets);

/* "NdisCancelTimer" (aa447920): print `VOID NdisCancelTimer(PNDIS_TIMERTimer,PBOOLEANTimerCanceled)` */
AKARI_CE_IMPORT VOID  NdisCancelTimer(PNDIS_TIMER Timer, PBOOLEAN TimerCanceled)
                    AKARI_CE_NAME(NdisCancelTimer);

/* "NdisChainBufferAtBack" (aa447921): print `VOID NdisChainBufferAtBack(PNDIS_PACKET Packet,PNDIS_BUFFER Buffer)` */
AKARI_CE_IMPORT VOID  NdisChainBufferAtBack(PNDIS_PACKET Packet, PNDIS_BUFFER Buffer)
                    AKARI_CE_NAME(NdisChainBufferAtBack);

/* "NdisChainBufferAtFront" (aa447922): print `VOID NdisChainBufferAtFront(PNDIS_PACKETPacket,PNDIS_BUFFERBuffer)` */
AKARI_CE_IMPORT VOID  NdisChainBufferAtFront(PNDIS_PACKET Packet, PNDIS_BUFFER Buffer)
                    AKARI_CE_NAME(NdisChainBufferAtFront);

/* "NdisCloseAdapter" (aa447923): print `VOID NdisCloseAdapter(PNDIS_STATUSStatus,NDIS_HANDLENdisBindingHandle)` */
AKARI_CE_IMPORT VOID  NdisCloseAdapter(PNDIS_STATUS Status, NDIS_HANDLE NdisBindingHandle)
                    AKARI_CE_NAME(NdisCloseAdapter);

/* "NdisCloseConfiguration" (aa447924): print `VOID NdisCloseConfiguration(NDIS_HANDLEConfigurationHandle)` */
AKARI_CE_IMPORT VOID  NdisCloseConfiguration(NDIS_HANDLE ConfigurationHandle)
                    AKARI_CE_NAME(NdisCloseConfiguration);

/* "NdisCloseFile" (aa447925): print `VOID NdisCloseFile(NDIS_HANDLEFileHandle)` */
AKARI_CE_IMPORT VOID  NdisCloseFile(NDIS_HANDLE FileHandle)
                    AKARI_CE_NAME(NdisCloseFile);

/* "NdisCompleteBindAdapter" (aa447926): print `VOID NdisCompleteBindAdapter(NDIS_HANDLEBindAdapterContext,NDIS_STATUSStatus,NDIS_STATUSOpenStatus)` */
AKARI_CE_IMPORT VOID  NdisCompleteBindAdapter(NDIS_HANDLE BindAdapterContext, NDIS_STATUS Status, NDIS_STATUS OpenStatus)
                    AKARI_CE_NAME(NdisCompleteBindAdapter);

/* "NdisCompleteUnbindAdapter" (aa447927): print `VOID NdisCompleteUnbindAdapter(NDIS_HANDLEUnbindAdapterContext,NDIS_STATUSStatus)` */
AKARI_CE_IMPORT VOID  NdisCompleteUnbindAdapter(NDIS_HANDLE UnbindAdapterContext, NDIS_STATUS Status)
                    AKARI_CE_NAME(NdisCompleteUnbindAdapter);

/* "NdisCopyBuffer" (aa447929): print `VOID NdisCopyBuffer(PNDIS_STATUSStatus,PNDIS_BUFFER* Buffer,NDIS_HANDLEPoolHandle,PVOIDMemoryDescriptor,UINTOffset,UINTLength)` */
AKARI_CE_IMPORT VOID  NdisCopyBuffer(PNDIS_STATUS Status, PNDIS_BUFFER*Buffer, NDIS_HANDLE PoolHandle, PVOID MemoryDescriptor, UINT Offset, UINT Length)
                    AKARI_CE_NAME(NdisCopyBuffer);

/* "NdisCopyFromPacketToPacket" (aa447930): print `VOID NdisCopyFromPacketToPacket(PNDIS_PACKETDestination,UINTDestinationOffset,UINTBytesToCopy,PNDIS_PACKETSource,UINTSourceOffset,PUINTBytesCopied)` */
AKARI_CE_IMPORT VOID  NdisCopyFromPacketToPacket(PNDIS_PACKET Destination, UINT DestinationOffset, UINT BytesToCopy, PNDIS_PACKET Source, UINT SourceOffset, PUINT BytesCopied)
                    AKARI_CE_NAME(NdisCopyFromPacketToPacket);

/* "NdisCopyLookaheadData" (aa447931): print `VOID NdisCopyLookaheadData(PVOIDDestination,PVOIDSource,ULONGLength,ULONGMacOptions)` */
AKARI_CE_IMPORT VOID  NdisCopyLookaheadData(PVOID Destination, PVOID Source, ULONG Length, ULONG MacOptions)
                    AKARI_CE_NAME(NdisCopyLookaheadData);

/* "NdisCreateLookaheadBufferFromSharedMemory" (aa447932): print `VOIDNdisCreateLookaheadBufferFromSharedMemory(PVOIDpSharedMemory,UINTLookaheadLength,PVOID* pLookaheadBuffer)` */
AKARI_CE_IMPORT VOID NdisCreateLookaheadBufferFromSharedMemory(PVOID pSharedMemory, UINT LookaheadLength, PVOID*pLookaheadBuffer)
                    AKARI_CE_NAME(NdisCreateLookaheadBufferFromSharedMemory);

/* "NdisDeregisterAdapter" (aa447934): print `VOID NdisDeregisterAdapter(PNDIS_STATUSStatus,PWSTR AdapterInstanceName)` */
AKARI_CE_IMPORT VOID  NdisDeregisterAdapter(PNDIS_STATUS Status, PWSTR AdapterInstanceName)
                    AKARI_CE_NAME(NdisDeregisterAdapter);

/* "NdisDeregisterProtocol" (aa447935): print `VOID NdisDeregisterProtocol(PNDIS_STATUSStatus,NDIS_HANDLENdisProtocolHandle)` */
AKARI_CE_IMPORT VOID  NdisDeregisterProtocol(PNDIS_STATUS Status, NDIS_HANDLE NdisProtocolHandle)
                    AKARI_CE_NAME(NdisDeregisterProtocol);

/* "NdisDestroyLookaheadBufferFromSharedMemory" (aa447936): print `VOID NdisDestroyLookaheadBufferFromSharedMemory(PVOIDpLookaheadBuffer)` */
AKARI_CE_IMPORT VOID  NdisDestroyLookaheadBufferFromSharedMemory(PVOID pLookaheadBuffer)
                    AKARI_CE_NAME(NdisDestroyLookaheadBufferFromSharedMemory);

/* "NdisDprAcquireSpinLock" (aa447937): print `VOIDNdisDprAcquireSpinLock(PNDIS_SPIN_LOCK SpinLock)` */
AKARI_CE_IMPORT VOID NdisDprAcquireSpinLock(PNDIS_SPIN_LOCK SpinLock)
                    AKARI_CE_NAME(NdisDprAcquireSpinLock);

/* "NdisDprAllocatePacket" (aa447938): print `VOID NdisDprAllocatePacket(PNDIS_STATUSStatus,PNDIS_PACKET* Packet,NDIS_HANDLEPoolHandle)` */
AKARI_CE_IMPORT VOID  NdisDprAllocatePacket(PNDIS_STATUS Status, PNDIS_PACKET*Packet, NDIS_HANDLE PoolHandle)
                    AKARI_CE_NAME(NdisDprAllocatePacket);

/* "NdisDprAllocatePacketNonInterlocked" (aa447939): print `VOID NdisDprAllocatePacketNonInterlocked(PNDIS_STATUSStatus,PNDIS_PACKET* Packet,NDIS_HANDLEPoolHandle)` */
AKARI_CE_IMPORT VOID  NdisDprAllocatePacketNonInterlocked(PNDIS_STATUS Status, PNDIS_PACKET*Packet, NDIS_HANDLE PoolHandle)
                    AKARI_CE_NAME(NdisDprAllocatePacketNonInterlocked);

/* "NdisDprFreePacket" (aa447940): print `VOID NdisDprFreePacket(PNDIS_PACKETPacket)` */
AKARI_CE_IMPORT VOID  NdisDprFreePacket(PNDIS_PACKET Packet)
                    AKARI_CE_NAME(NdisDprFreePacket);

/* "NdisDprFreePacketNonInterlocked" (aa447941): print `VOID NdisDprFreePacketNonInterlocked(PNDIS_PACKETPacket)` */
AKARI_CE_IMPORT VOID  NdisDprFreePacketNonInterlocked(PNDIS_PACKET Packet)
                    AKARI_CE_NAME(NdisDprFreePacketNonInterlocked);

/* "NdisDprReleaseSpinLock" (aa447942): print `VOIDNdisDprReleaseSpinLock(PNDIS_SPIN_LOCKSpinLock)` */
AKARI_CE_IMPORT VOID NdisDprReleaseSpinLock(PNDIS_SPIN_LOCK SpinLock)
                    AKARI_CE_NAME(NdisDprReleaseSpinLock);

/* "NdisEqualAnsiString" (aa447944): print `BOOLEAN NdisEqualAnsiString(PNDIS_STRINGString1,PNDIS_STRINGString2,BOOLEANCaseInSensitive)` */
AKARI_CE_IMPORT BOOLEAN  NdisEqualAnsiString(PNDIS_STRING String1, PNDIS_STRING String2, BOOLEAN CaseInSensitive)
                    AKARI_CE_NAME(NdisEqualAnsiString);

/* "NdisEqualMemory" (aa447945): print `ULONG NdisEqualMemory(CONST VOID* Source1,CONST VOID* Source2,ULONG Length)` */
AKARI_CE_IMPORT ULONG  NdisEqualMemory(CONST VOID*Source1, CONST VOID*Source2, ULONG Length)
                    AKARI_CE_NAME(NdisEqualMemory);

/* "NdisEqualString" (aa447946): print `BOOLEANNdisEqualString(PNDIS_STRINGString1,PNDIS_STRINGString2,BOOLEANCaseInsensitive)` */
AKARI_CE_IMPORT BOOLEAN NdisEqualString(PNDIS_STRING String1, PNDIS_STRING String2, BOOLEAN CaseInsensitive)
                    AKARI_CE_NAME(NdisEqualString);

/* "NdisEqualUnicodeString" (aa447947): print `BOOLEAN NdisEqualUnicodeString(PNDIS_STRINGString1,PNDIS_STRINGString2,BOOLEANCaseInSensitive)` */
AKARI_CE_IMPORT BOOLEAN  NdisEqualUnicodeString(PNDIS_STRING String1, PNDIS_STRING String2, BOOLEAN CaseInSensitive)
                    AKARI_CE_NAME(NdisEqualUnicodeString);

/* "NdisFillMemory" (aa447949): print `VOID NdisFillMemory(PVOIDDestination,ULONGLength,UCHARFill)` */
AKARI_CE_IMPORT VOID  NdisFillMemory(PVOID Destination, ULONG Length, UCHAR Fill)
                    AKARI_CE_NAME(NdisFillMemory);

/* "NdisFlushBuffer" (aa447950): print `VOID NdisFlushBuffer(PNDIS_BUFFER Buffer,BOOLEAN WriteToDevice)` */
AKARI_CE_IMPORT VOID  NdisFlushBuffer(PNDIS_BUFFER Buffer, BOOLEAN WriteToDevice)
                    AKARI_CE_NAME(NdisFlushBuffer);

/* "NdisFreeBuffer" (aa447951): print `VOID NdisFreeBuffer(PNDIS_BUFFER Buffer)` */
AKARI_CE_IMPORT VOID  NdisFreeBuffer(PNDIS_BUFFER Buffer)
                    AKARI_CE_NAME(NdisFreeBuffer);

/* "NdisFreeBufferPool" (aa447952): print `VOID NdisFreeBufferPool(NDIS_HANDLE PoolHandle)` */
AKARI_CE_IMPORT VOID  NdisFreeBufferPool(NDIS_HANDLE PoolHandle)
                    AKARI_CE_NAME(NdisFreeBufferPool);

/* "NdisFreeEvent" (aa447953): print `VOID NdisFreeEvent(PNDIS_EVENT Event)` */
AKARI_CE_IMPORT VOID  NdisFreeEvent(PNDIS_EVENT Event)
                    AKARI_CE_NAME(NdisFreeEvent);

/* "NdisFreeMemory" (aa447954): print `VOIDNdisFreeMemory(PVOIDVirtualAddress,UINTLength,UINTMemoryFlags)` */
AKARI_CE_IMPORT VOID NdisFreeMemory(PVOID VirtualAddress, UINT Length, UINT MemoryFlags)
                    AKARI_CE_NAME(NdisFreeMemory);

/* "NdisFreePacket" (aa447955): print `VOID NdisFreePacket(PNDIS_PACKETPacket)` */
AKARI_CE_IMPORT VOID  NdisFreePacket(PNDIS_PACKET Packet)
                    AKARI_CE_NAME(NdisFreePacket);

/* "NdisFreePacketPool" (aa447956): print `VOID NdisFreePacketPool(NDIS_HANDLE PoolHandle)` */
AKARI_CE_IMPORT VOID  NdisFreePacketPool(NDIS_HANDLE PoolHandle)
                    AKARI_CE_NAME(NdisFreePacketPool);

/* "NdisFreeReadWriteLock" (aa447957): print `VOID NdisFreeReadWriteLock(PNDIS_RW_LOCK Lock)` */
AKARI_CE_IMPORT VOID  NdisFreeReadWriteLock(PNDIS_RW_LOCK Lock)
                    AKARI_CE_NAME(NdisFreeReadWriteLock);

/* "NdisFreeSpinLock" (aa447958): print `VOIDNdisFreeSpinLock(PNDIS_SPIN_LOCKSpinLock)` */
AKARI_CE_IMPORT VOID NdisFreeSpinLock(PNDIS_SPIN_LOCK SpinLock)
                    AKARI_CE_NAME(NdisFreeSpinLock);

/* "NdisFreeString" (aa447959): print `VOID NdisFreeString(NDIS_STRING String)` */
AKARI_CE_IMPORT VOID  NdisFreeString(NDIS_STRING String)
                    AKARI_CE_NAME(NdisFreeString);

/* "NdisGeneratePartialCancelId" (aa447960): print `UCHAR NdisGeneratePartialCancelId(void)` */
AKARI_CE_IMPORT UCHAR  NdisGeneratePartialCancelId(void)
                    AKARI_CE_NAME(NdisGeneratePartialCancelId);

/* "NdisGetAdapterBindings" (aa447961): print `VOID NdisGetAdapterBindings(PNDIS_STATUS pStatus,PWSTRwszAdapterInstanceName,PBYTE pOutBuf,DWORD cbOutBufSize,PDWORD pcbReturned)` */
AKARI_CE_IMPORT VOID  NdisGetAdapterBindings(PNDIS_STATUS pStatus, PWSTR wszAdapterInstanceName, PBYTE pOutBuf, DWORD cbOutBufSize, PDWORD pcbReturned)
                    AKARI_CE_NAME(NdisGetAdapterBindings);

/* "NdisGetAdapterNames" (aa447962): print `VOID NdisGetAdapterNames(PNDIS_STATUS Status,PBYTE pOutBuf,DWORD cbOutBufSize,PDWORD pcbReturned)` */
AKARI_CE_IMPORT VOID  NdisGetAdapterNames(PNDIS_STATUS Status, PBYTE pOutBuf, DWORD cbOutBufSize, PDWORD pcbReturned)
                    AKARI_CE_NAME(NdisGetAdapterNames);

/* "NdisGetCacheFillSize" (aa447963): print `ULONG NdisGetCacheFillSize()` */
AKARI_CE_IMPORT ULONG  NdisGetCacheFillSize(void)
                    AKARI_CE_NAME(NdisGetCacheFillSize);

/* "NdisGetCurrentSystemTime" (aa447964): print `VOID NdisGetCurrentSystemTime(PLARGE_INTEGERpSystemTime)` */
AKARI_CE_IMPORT VOID  NdisGetCurrentSystemTime(PLARGE_INTEGER pSystemTime)
                    AKARI_CE_NAME(NdisGetCurrentSystemTime);

/* "NdisGetDriverHandle" (aa447965): print `VOID NdisGetDriverHandle(PNDIS_HANDLENdisBindingHandle,PNDIS_HANDLENdisDriverHandle)` */
AKARI_CE_IMPORT VOID  NdisGetDriverHandle(PNDIS_HANDLE NdisBindingHandle, PNDIS_HANDLE NdisDriverHandle)
                    AKARI_CE_NAME(NdisGetDriverHandle);

/* "NdisGetFirstBufferFromPacket" (aa447966): print `VOIDNdisGetFirstBufferFromPacket(PNDIS_PACKETPacket,PNDIS_BUFFER* FirstBuffer,PVOID* FirstBufferVA,PUINTFirstBufferLength,PUINTTotalBufferLength)` */
AKARI_CE_IMPORT VOID NdisGetFirstBufferFromPacket(PNDIS_PACKET Packet, PNDIS_BUFFER*FirstBuffer, PVOID*FirstBufferVA, PUINT FirstBufferLength, PUINT TotalBufferLength)
                    AKARI_CE_NAME(NdisGetFirstBufferFromPacket);

/* "NdisGetNextBuffer" (aa447968): print `VOID NdisGetNextBuffer(PNDIS_BUFFER CurrentBuffer,PNDIS_BUFFER* NextBuffer)` */
AKARI_CE_IMPORT VOID  NdisGetNextBuffer(PNDIS_BUFFER CurrentBuffer, PNDIS_BUFFER*NextBuffer)
                    AKARI_CE_NAME(NdisGetNextBuffer);

/* "NdisGetPacketCancelId" (aa447970): print `PVOID NdisGetPacketCancelId(PNDIS_PACKETPacket)` */
AKARI_CE_IMPORT PVOID  NdisGetPacketCancelId(PNDIS_PACKET Packet)
                    AKARI_CE_NAME(NdisGetPacketCancelId);

/* "NdisGetPacketFlags" (aa447972): print `UINT NdisGetPacketFlags(PNDIS_PACKET Packet)` */
AKARI_CE_IMPORT UINT  NdisGetPacketFlags(PNDIS_PACKET Packet)
                    AKARI_CE_NAME(NdisGetPacketFlags);

/* "NdisGetPhysicalAddressHigh" (aa447980): print `ULONG NdisGetPhysicalAddressHigh(NDIS_PHYSICAL_ADDRESS PhysicalAddress)` */
AKARI_CE_IMPORT ULONG  NdisGetPhysicalAddressHigh(NDIS_PHYSICAL_ADDRESS PhysicalAddress)
                    AKARI_CE_NAME(NdisGetPhysicalAddressHigh);

/* "NdisGetPhysicalAddressLow" (aa447981): print `ULONG NdisGetPhysicalAddressLow(NDIS_PHYSICAL_ADDRESS PhysicalAddress)` */
AKARI_CE_IMPORT ULONG  NdisGetPhysicalAddressLow(NDIS_PHYSICAL_ADDRESS PhysicalAddress)
                    AKARI_CE_NAME(NdisGetPhysicalAddressLow);

/* "NdisGetPoolFromPacket" (aa447982): print `NDIS_HANDLE NdisGetPoolFromPacket(PNDIS_PACKET Packet)` */
AKARI_CE_IMPORT NDIS_HANDLE  NdisGetPoolFromPacket(PNDIS_PACKET Packet)
                    AKARI_CE_NAME(NdisGetPoolFromPacket);

/* "NdisGetProtocolNames" (aa447983): print `VOID NdisGetProtocolNames(PNDIS_STATUS pStatus,PBYTE pOutBuf,DWORDcbOutBufSize,PDWORDpcbReturned)` */
AKARI_CE_IMPORT VOID  NdisGetProtocolNames(PNDIS_STATUS pStatus, PBYTE pOutBuf, DWORD cbOutBufSize, PDWORD pcbReturned)
                    AKARI_CE_NAME(NdisGetProtocolNames);

/* "NdisGetReceivedPacket" (aa447984): print `PNDIS_PACKET NdisGetReceivedPacket(PNDIS_HANDLENdisBindingHandle,PNDIS_HANDLEMacContext)` */
AKARI_CE_IMPORT PNDIS_PACKET  NdisGetReceivedPacket(PNDIS_HANDLE NdisBindingHandle, PNDIS_HANDLE MacContext)
                    AKARI_CE_NAME(NdisGetReceivedPacket);

/* "NdisGetSystemUpTime" (aa447985): print `VOID NdisGetSystemUpTime(PULONGpSystemUpTime)` */
AKARI_CE_IMPORT VOID  NdisGetSystemUpTime(PULONG pSystemUpTime)
                    AKARI_CE_NAME(NdisGetSystemUpTime);

/* "NdisIMAssociateMiniport" (aa447987): print `VOID NdisIMAssociateMiniport(NDIS_HANDLEDriverHandle,NDIS_HANDLEProtocolHandle)` */
AKARI_CE_IMPORT VOID  NdisIMAssociateMiniport(NDIS_HANDLE DriverHandle, NDIS_HANDLE ProtocolHandle)
                    AKARI_CE_NAME(NdisIMAssociateMiniport);

/* "NdisIMCancelInitializeDeviceInstance" (aa447988): print `NDIS_STATUS NdisIMCancelInitializeDeviceInstance(NDIS_HANDLEDriverHandle,PNDIS_STRINGDeviceInstance)` */
AKARI_CE_IMPORT NDIS_STATUS  NdisIMCancelInitializeDeviceInstance(NDIS_HANDLE DriverHandle, PNDIS_STRING DeviceInstance)
                    AKARI_CE_NAME(NdisIMCancelInitializeDeviceInstance);

/* "NdisIMCopySendCompletePerPacketInfo" (aa447989): print `VOID NdisIMCopySendCompletePerPacketInfo(PNDIS_PACKETDstPacket,PNDIS_PACKETSrcPacket)` */
AKARI_CE_IMPORT VOID  NdisIMCopySendCompletePerPacketInfo(PNDIS_PACKET DstPacket, PNDIS_PACKET SrcPacket)
                    AKARI_CE_NAME(NdisIMCopySendCompletePerPacketInfo);

/* "NdisIMCopySendPerPacketInfo" (aa447990): print `VOID NdisIMCopySendPerPacketInfo(PNDIS_PACKETDstPacket,PNDIS_PACKETSrcPacket)` */
AKARI_CE_IMPORT VOID  NdisIMCopySendPerPacketInfo(PNDIS_PACKET DstPacket, PNDIS_PACKET SrcPacket)
                    AKARI_CE_NAME(NdisIMCopySendPerPacketInfo);

/* "NdisIMDeInitializeDeviceInstance" (aa447991): print `NDIS_STATUS NdisIMDeInitializeDeviceInstance(NDIS_HANDLENdisMiniportHandle)` */
AKARI_CE_IMPORT NDIS_STATUS  NdisIMDeInitializeDeviceInstance(NDIS_HANDLE NdisMiniportHandle)
                    AKARI_CE_NAME(NdisIMDeInitializeDeviceInstance);

/* "NdisIMDeregisterLayeredMiniport" (aa447992): print `VOID NdisIMDeregisterLayeredMiniport(NDIS_HANDLEDriverHandle)` */
AKARI_CE_IMPORT VOID  NdisIMDeregisterLayeredMiniport(NDIS_HANDLE DriverHandle)
                    AKARI_CE_NAME(NdisIMDeregisterLayeredMiniport);

/* "NdisIMGetBindingContext" (aa447993): print `NDIS_HANDLE NdisIMGetBindingContext(NDIS_HANDLENdisBindingHandle)` */
AKARI_CE_IMPORT NDIS_HANDLE  NdisIMGetBindingContext(NDIS_HANDLE NdisBindingHandle)
                    AKARI_CE_NAME(NdisIMGetBindingContext);

/* "NdisIMGetCurrentPacketStack" (aa447994): print `PNDIS_PACKET_STACK NdisIMGetCurrentPacketStack(PNDIS_PACKET Packet,BOOLEAN* StacksRemaining)` */
AKARI_CE_IMPORT PNDIS_PACKET_STACK  NdisIMGetCurrentPacketStack(PNDIS_PACKET Packet, BOOLEAN*StacksRemaining)
                    AKARI_CE_NAME(NdisIMGetCurrentPacketStack);

/* "NdisIMGetDeviceContext" (aa447995): print `NDIS_HANDLE NdisIMGetDeviceContext(NDIS_HANDLEMiniportAdapterHandle)` */
AKARI_CE_IMPORT NDIS_HANDLE  NdisIMGetDeviceContext(NDIS_HANDLE MiniportAdapterHandle)
                    AKARI_CE_NAME(NdisIMGetDeviceContext);

/* "NdisIMInitializeDeviceInstance" (aa447996): print `NDIS_STATUS NdisIMInitializeDeviceInstance(NDIS_HANDLEDriverHandle,PNDIS_STRINGDeviceInstance)` */
AKARI_CE_IMPORT NDIS_STATUS  NdisIMInitializeDeviceInstance(NDIS_HANDLE DriverHandle, PNDIS_STRING DeviceInstance)
                    AKARI_CE_NAME(NdisIMInitializeDeviceInstance);

/* "NdisIMInitializeDeviceInstanceEx" (aa447997): print `NDIS_STATUS NdisIMInitializeDeviceInstanceEx(NDIS_HANDLEDriverHandle,PNDIS_STRINGDriverInstance,NDIS_HANDLEDeviceContextOPTIONAL)` */
AKARI_CE_IMPORT NDIS_STATUS  NdisIMInitializeDeviceInstanceEx(NDIS_HANDLE DriverHandle, PNDIS_STRING DriverInstance, NDIS_HANDLE DeviceContext)
                    AKARI_CE_NAME(NdisIMInitializeDeviceInstanceEx);

/* "NdisIMNotifyPnPEvent" (aa447998): print `NDIS_STATUS NdisIMNotifyPnPEvent(NDIS_HANDLE MiniportHandle,PNET_PNP_EVENT NetPnPEvent)` */
AKARI_CE_IMPORT NDIS_STATUS  NdisIMNotifyPnPEvent(NDIS_HANDLE MiniportHandle, PNET_PNP_EVENT NetPnPEvent)
                    AKARI_CE_NAME(NdisIMNotifyPnPEvent);

/* "NdisIMRegisterLayeredMiniport" (aa448001): print `NDIS_STATUS NdisIMRegisterLayeredMiniport(NDIS_HANDLENdisWrapperHandle,PNDIS_MINIPORT_CHARACTERISTICSMiniportCharacteristics,UINTCharacteristicsLength,PNDIS_HANDLEDriverHandle)` */
AKARI_CE_IMPORT NDIS_STATUS  NdisIMRegisterLayeredMiniport(NDIS_HANDLE NdisWrapperHandle, PNDIS_MINIPORT_CHARACTERISTICS MiniportCharacteristics, UINT CharacteristicsLength, PNDIS_HANDLE DriverHandle)
                    AKARI_CE_NAME(NdisIMRegisterLayeredMiniport);

/* "NdisInitAnsiString" (aa448002): print `VOIDNdisInitAnsiString(PNDIS_ANSI_STRINGDestinationString,PCSTRSourceString)` */
AKARI_CE_IMPORT VOID NdisInitAnsiString(PNDIS_ANSI_STRING DestinationString, PCSTR SourceString)
                    AKARI_CE_NAME(NdisInitAnsiString);

/* "NdisInitializeEvent" (aa448004): print `VOID NdisInitializeEvent(PNDIS_EVENTEvent)` */
AKARI_CE_IMPORT VOID  NdisInitializeEvent(PNDIS_EVENT Event)
                    AKARI_CE_NAME(NdisInitializeEvent);

/* "NdisInitializeReadWriteLock" (aa448006): print `VOID NdisInitializeReadWriteLock(PNDIS_RW_LOCKLock)` */
AKARI_CE_IMPORT VOID  NdisInitializeReadWriteLock(PNDIS_RW_LOCK Lock)
                    AKARI_CE_NAME(NdisInitializeReadWriteLock);

/* "NdisInitializeString" (aa448007): print `VOIDNdisInitializeString(PNDIS_STRINGDestinationString,PUCHARSourceString)` */
AKARI_CE_IMPORT VOID NdisInitializeString(PNDIS_STRING DestinationString, PUCHAR SourceString)
                    AKARI_CE_NAME(NdisInitializeString);

/* "NdisInitializeTimer" (aa448008): print `VOID NdisInitializeTimer(PNDIS_TIMERTimer,PNDIS_TIMER_FUNCTIONTimerFunction,PVOIDFunctionContext)` */
AKARI_CE_IMPORT VOID  NdisInitializeTimer(PNDIS_TIMER Timer, PNDIS_TIMER _FUNCTIONTimerFunction, PVOID FunctionContext)
                    AKARI_CE_NAME(NdisInitializeTimer);

/* "NdisInitializeWorkItem" (aa448009): print `VOID NdisInitializeWorkItem(PNDIS_WORK_ITEMWorkItem,NDIS_PROCRoutine,PVOIDContext)` */
AKARI_CE_IMPORT VOID  NdisInitializeWorkItem(PNDIS_WORK_ITEM WorkItem, NDIS_PROC Routine, PVOID Context)
                    AKARI_CE_NAME(NdisInitializeWorkItem);

/* "NdisInitUnicodeString" (aa448010): print `VOIDNdisInitUnicodeString(PNDIS_STRINGDestinationString,PCWSTRSourceString)` */
AKARI_CE_IMPORT VOID NdisInitUnicodeString(PNDIS_STRING DestinationString, PCWSTR SourceString)
                    AKARI_CE_NAME(NdisInitUnicodeString);

/* "NdisInterlockedAddUlong" (aa448012): print `VOID NdisInterlockedAddUlong(PULONGAddend,ULONGIncrement,PNDIS_SPIN_LOCKSpinLock)` */
AKARI_CE_IMPORT VOID  NdisInterlockedAddUlong(PULONG Addend, ULONG Increment, PNDIS_SPIN_LOCK SpinLock)
                    AKARI_CE_NAME(NdisInterlockedAddUlong);

/* "NdisInterlockedDecrement" (aa448013): print `LONG NdisInterlockedDecrement(PLONGAddend)` */
AKARI_CE_IMPORT LONG  NdisInterlockedDecrement(PLONG Addend)
                    AKARI_CE_NAME(NdisInterlockedDecrement);

/* "NdisInterlockedIncrement" (aa448014): print `LONG NdisInterlockedIncrement(PLONGAddend)` */
AKARI_CE_IMPORT LONG  NdisInterlockedIncrement(PLONG Addend)
                    AKARI_CE_NAME(NdisInterlockedIncrement);

/* "NdisMAllocateSharedMemory" (aa448023): print `VOID NdisMAllocateSharedMemory(NDIS_HANDLE MiniportAdapterHandle,ULONG Length,BOOLEAN Cached,PVOID* VirtualAddress,PNDIS_PHYSICAL_ADDRESS PhysicalAddress)` */
AKARI_CE_IMPORT VOID  NdisMAllocateSharedMemory(NDIS_HANDLE MiniportAdapterHandle, ULONG Length, BOOLEAN Cached, PVOID*VirtualAddress, PNDIS_PHYSICAL_ADDRESS PhysicalAddress)
                    AKARI_CE_NAME(NdisMAllocateSharedMemory);

/* "NdisMapFile" (aa448024): print `VOID NdisMapFile(PNDIS_STATUSStatus,PVOID* MappedBuffer,NDIS_HANDLEFileHandle)` */
AKARI_CE_IMPORT VOID  NdisMapFile(PNDIS_STATUS Status, PVOID*MappedBuffer, NDIS_HANDLE FileHandle)
                    AKARI_CE_NAME(NdisMapFile);

/* "NdisMCancelTimer" (aa448025): print `VOID NdisMCancelTimer(PNDIS_MINIPORT_TIMER Timer,PBOOLEAN TimerCanceled)` */
AKARI_CE_IMPORT VOID  NdisMCancelTimer(PNDIS_MINIPORT_TIMER Timer, PBOOLEAN TimerCanceled)
                    AKARI_CE_NAME(NdisMCancelTimer);

/* "NdisMCloseLog" (aa448026): print `VOID NdisMCloseLog(NDIS_HANDLELogHandle)` */
AKARI_CE_IMPORT VOID  NdisMCloseLog(NDIS_HANDLE LogHandle)
                    AKARI_CE_NAME(NdisMCloseLog);

/* "NdisMCompleteBufferPhysicalMapping" (aa448027): print `VOID NdisMCompleteBufferPhysicalMapping(NDIS_HANDLEMiniportAdapterHandle,PNDIS_BUFFER Buffer,ULONG PhysicalMapRegister)` */
AKARI_CE_IMPORT VOID  NdisMCompleteBufferPhysicalMapping(NDIS_HANDLE MiniportAdapterHandle, PNDIS_BUFFER Buffer, ULONG PhysicalMapRegister)
                    AKARI_CE_NAME(NdisMCompleteBufferPhysicalMapping);

/* "NdisMCreateLog" (aa448028): print `NDIS_STATUS NdisMCreateLog(NDIS_HANDLEMiniportAdapterHandle,UINTSize,PNDIS_HANDLELogHandle)` */
AKARI_CE_IMPORT NDIS_STATUS  NdisMCreateLog(NDIS_HANDLE MiniportAdapterHandle, UINT Size, PNDIS_HANDLE LogHandle)
                    AKARI_CE_NAME(NdisMCreateLog);

/* "NdisMDeregisterAdapterShutdownHandler" (aa448029): print `VOID NdisMDeregisterAdapterShutdownHandler(NDIS_HANDLE MiniportHandle)` */
AKARI_CE_IMPORT VOID  NdisMDeregisterAdapterShutdownHandler(NDIS_HANDLE MiniportHandle)
                    AKARI_CE_NAME(NdisMDeregisterAdapterShutdownHandler);

/* "NdisMDeregisterInterrupt" (aa448030): print `VOID NdisMDeregisterInterrupt(PNDIS_MINIPORT_INTERRUPT Interrupt)` */
AKARI_CE_IMPORT VOID  NdisMDeregisterInterrupt(PNDIS_MINIPORT_INTERRUPT Interrupt)
                    AKARI_CE_NAME(NdisMDeregisterInterrupt);

/* "NdisMDeregisterIoPortRange" (aa448031): print `VOID NdisMDeregisterIoPortRange(NDIS_HANDLEMiniportAdapterHandle,UINTInitialPort,UINTNumberOfPorts,PVOIDPortOffset)` */
AKARI_CE_IMPORT VOID  NdisMDeregisterIoPortRange(NDIS_HANDLE MiniportAdapterHandle, UINT InitialPort, UINT NumberOfPorts, PVOID PortOffset)
                    AKARI_CE_NAME(NdisMDeregisterIoPortRange);

/* "NdisMEthIndicateReceive" (aa448033): print `VOID NdisMEthIndicateReceive(NDIS_HANDLEMiniportAdapterHandle,NDIS_HANDLEMiniportReceiveContext,PVOIDHeaderBuffer,UINTHeaderBufferSize,PVOIDLookaheadBuffer,UINTLookaheadBufferSize,UINTPacketSize)` */
AKARI_CE_IMPORT VOID  NdisMEthIndicateReceive(NDIS_HANDLE MiniportAdapterHandle, NDIS_HANDLE MiniportReceiveContext, PVOID HeaderBuffer, UINT HeaderBufferSize, PVOID LookaheadBuffer, UINT LookaheadBufferSize, UINT PacketSize)
                    AKARI_CE_NAME(NdisMEthIndicateReceive);

/* "NdisMEthIndicateReceiveComplete" (aa448034): print `VOID NdisMEthIndicateReceiveComplete(NDIS_HANDLE MiniportAdapterHandle)` */
AKARI_CE_IMPORT VOID  NdisMEthIndicateReceiveComplete(NDIS_HANDLE MiniportAdapterHandle)
                    AKARI_CE_NAME(NdisMEthIndicateReceiveComplete);

/* "NdisMFlushLog" (aa448035): print `VOID NdisMFlushLog(NDIS_HANDLELogHandle)` */
AKARI_CE_IMPORT VOID  NdisMFlushLog(NDIS_HANDLE LogHandle)
                    AKARI_CE_NAME(NdisMFlushLog);

/* "NdisMFreeMapRegisters" (aa448036): print `VOID NdisMFreeMapRegisters(NDIS_HANDLEMiniportAdapterHandle)` */
AKARI_CE_IMPORT VOID  NdisMFreeMapRegisters(NDIS_HANDLE MiniportAdapterHandle)
                    AKARI_CE_NAME(NdisMFreeMapRegisters);

/* "NdisMFreeSharedMemory" (aa448037): print `VOID NdisMFreeSharedMemory(NDIS_HANDLE MiniportAdapterHandle,ULONG Length,BOOLEAN Cached,PVOID VirtualAddress,NDIS_PHYSICAL_ADDRESS PhysicalAddress)` */
AKARI_CE_IMPORT VOID  NdisMFreeSharedMemory(NDIS_HANDLE MiniportAdapterHandle, ULONG Length, BOOLEAN Cached, PVOID VirtualAddress, NDIS_PHYSICAL_ADDRESS PhysicalAddress)
                    AKARI_CE_NAME(NdisMFreeSharedMemory);

/* "NdisMIndicateReceivePacket" (aa448038): print `VOIDNdisMIndicateReceivePacket(NDIS_HANDLEMiniportAdapterHandle,PPNDIS_PACKETReceivePackets,UINTNumberOfPackets)` */
AKARI_CE_IMPORT VOID NdisMIndicateReceivePacket(NDIS_HANDLE MiniportAdapterHandle, PNDIS_PACKET*ReceivePackets, UINT NumberOfPackets)
                    AKARI_CE_NAME(NdisMIndicateReceivePacket);

/* "NdisMIndicateStatus" (aa448039): print `VOID NdisMIndicateStatus(NDIS_HANDLEMiniportAdapterHandle,NDIS_STATUSGeneralStatus,PVOIDStatusBuffer,UINTStatusBufferSize)` */
AKARI_CE_IMPORT VOID  NdisMIndicateStatus(NDIS_HANDLE MiniportAdapterHandle, NDIS_STATUS GeneralStatus, PVOID StatusBuffer, UINT StatusBufferSize)
                    AKARI_CE_NAME(NdisMIndicateStatus);

/* "NdisMIndicateStatusComplete" (aa448040): print `VOID NdisMIndicateStatusComplete(NDIS_HANDLE MiniportAdapterHandle)` */
AKARI_CE_IMPORT VOID  NdisMIndicateStatusComplete(NDIS_HANDLE MiniportAdapterHandle)
                    AKARI_CE_NAME(NdisMIndicateStatusComplete);

/* "NdisMInitializeTimer" (aa448042): print `VOID NdisMInitializeTimer(PNDIS_MINIPORT_TIMERTimer,NDIS_HANDLEMiniportAdapterHandle,PNDIS_TIMER_FUNCTIONTimerFunction,PVOIDFunctionContext)` */
AKARI_CE_IMPORT VOID  NdisMInitializeTimer(PNDIS_MINIPORT_TIMER Timer, NDIS_HANDLE MiniportAdapterHandle, PNDIS_TIMER _FUNCTIONTimerFunction, PVOID FunctionContext)
                    AKARI_CE_NAME(NdisMInitializeTimer);

/* "NdisCompletePnPEvent" (aa448313): print `VOID NdisCompletePnPEvent( IN NDIS_STATUS Status, IN NDIS_HANDLE NdisBindingHandle, IN PNET_PNP_EVENT NetPnPEvent )` */
AKARI_CE_IMPORT VOID  NdisCompletePnPEvent(NDIS_STATUS Status, NDIS_HANDLE NdisBindingHandle, PNET_PNP_EVENT NetPnPEvent)
                    AKARI_CE_NAME(NdisCompletePnPEvent);

/* "NdisGetVersion" (aa448316): print `UINT NdisGetVersion()` */
AKARI_CE_IMPORT UINT  NdisGetVersion(void)
                    AKARI_CE_NAME(NdisGetVersion);

/* "NdisIMRevertBack" (aa448318): print `VOIDNdisIMRevertBack(NDIS_HANDLE MiniportAdapterHandle,NDIS_HANDLESwitchHandle)` */
AKARI_CE_IMPORT VOID NdisIMRevertBack(NDIS_HANDLE MiniportAdapterHandle, NDIS_HANDLE SwitchHandle)
                    AKARI_CE_NAME(NdisIMRevertBack);

/* "NdisIMSwitchToMiniport" (aa448319): print `BOOLEAN NdisIMSwitchToMiniport( IN NDIS_HANDLE MiniportAdapterHandle, OUT PNDIS_HANDLE SwitchHandle )` */
AKARI_CE_IMPORT BOOLEAN  NdisIMSwitchToMiniport(NDIS_HANDLE MiniportAdapterHandle, PNDIS_HANDLE SwitchHandle)
                    AKARI_CE_NAME(NdisIMSwitchToMiniport);

/* "NdisPacketSize" (aa448321): print `UINT NdisPacketSize( IN UINT ProtocolReservedSize )` */
AKARI_CE_IMPORT UINT  NdisPacketSize(UINT ProtocolReservedSize)
                    AKARI_CE_NAME(NdisPacketSize);

/* "NdisSetPacketPoolProtocolId" (aa448322): print `VOID NdisSetPacketPoolProtocolId( IN NDIS_HANDLEPacketPoolHandle, IN UINT ProtocolId )` */
AKARI_CE_IMPORT VOID  NdisSetPacketPoolProtocolId(NDIS_HANDLE PacketPoolHandle, UINT ProtocolId)
                    AKARI_CE_NAME(NdisSetPacketPoolProtocolId);

/* "NdisMInitializeWrapper" (ms904029): print `VOID NdisMInitializeWrapper(PNDIS_HANDLENdisWrapperHandle,PVOIDSystemSpecific1,PVOIDSystemSpecific2,PVOIDSystemSpecific3)` */
AKARI_CE_IMPORT VOID  NdisMInitializeWrapper(PNDIS_HANDLE NdisWrapperHandle, PVOID SystemSpecific1, PVOID SystemSpecific2, PVOID SystemSpecific3)
                    AKARI_CE_NAME(NdisMInitializeWrapper);

/* "NdisMMapIoSpace" (ms904037): print `NDIS_STATUS NdisMMapIoSpace(PVOID* VirtualAddress,NDIS_HANDLE MiniportAdapterHandle,NDIS_PHYSICAL_ADDRESS PhysicalAddress,UINT Length)` */
AKARI_CE_IMPORT NDIS_STATUS  NdisMMapIoSpace(PVOID*VirtualAddress, NDIS_HANDLE MiniportAdapterHandle, NDIS_PHYSICAL_ADDRESS PhysicalAddress, UINT Length)
                    AKARI_CE_NAME(NdisMMapIoSpace);

/* "NdisMoveFromMappedMemory" (ms904038): print `VOID NdisMoveFromMappedMemory(PVOIDDestination,PVOIDSource,ULONGLength)` */
AKARI_CE_IMPORT VOID  NdisMoveFromMappedMemory(PVOID Destination, PVOID Source, ULONG Length)
                    AKARI_CE_NAME(NdisMoveFromMappedMemory);

/* "NdisMoveMappedMemory" (ms904039): print `VOID NdisMoveMappedMemory(PVOIDDestination,PVOIDSource,ULONGLength)` */
AKARI_CE_IMPORT VOID  NdisMoveMappedMemory(PVOID Destination, PVOID Source, ULONG Length)
                    AKARI_CE_NAME(NdisMoveMappedMemory);

/* "NdisMoveMemory" (ms904040): print `VOIDNdisMoveMemory(PVOIDDestination,PVOIDSource,ULONGLength)` */
AKARI_CE_IMPORT VOID NdisMoveMemory(PVOID Destination, PVOID Source, ULONG Length)
                    AKARI_CE_NAME(NdisMoveMemory);

/* "NdisMoveToMappedMemory" (ms904041): print `VOIDNdisMoveToMappedMemory(PVOIDDestination,PVOIDSource,ULONGLength)` */
AKARI_CE_IMPORT VOID NdisMoveToMappedMemory(PVOID Destination, PVOID Source, ULONG Length)
                    AKARI_CE_NAME(NdisMoveToMappedMemory);

/* "NdisMPciAssignResources" (ms904042): print `NDIS_STATUS NdisMPciAssignResources(NDIS_HANDLE MiniportHandle,ULONG SlotNumber,PNDIS_RESOURCE_LIST* AssignedResources)` */
AKARI_CE_IMPORT NDIS_STATUS  NdisMPciAssignResources(NDIS_HANDLE MiniportHandle, ULONG SlotNumber, PNDIS_RESOURCE_LIST*AssignedResources)
                    AKARI_CE_NAME(NdisMPciAssignResources);

/* "NdisMPromoteMiniport" (ms904043): print `NDIS_STATUS NdisMPromoteMiniport(NDIS_HANDLEMiniportAdapterHandle)` */
AKARI_CE_IMPORT NDIS_STATUS  NdisMPromoteMiniport(NDIS_HANDLE MiniportAdapterHandle)
                    AKARI_CE_NAME(NdisMPromoteMiniport);

/* "NdisMQueryAdapterInstanceName" (ms904044): print `NDIS_STATUS NdisMQueryAdapterInstanceName(PNDIS_STRINGAdapterInstanceName,NDIS_HANDLEMiniportAdapterHandle)` */
AKARI_CE_IMPORT NDIS_STATUS  NdisMQueryAdapterInstanceName(PNDIS_STRING AdapterInstanceName, NDIS_HANDLE MiniportAdapterHandle)
                    AKARI_CE_NAME(NdisMQueryAdapterInstanceName);

/* "NdisMQueryAdapterResources" (ms904045): print `VOID NdisMQueryAdapterResources(PNDIS_STATUSStatus,NDIS_HANDLEWrapperConfigurationContext,PNDIS_RESOURCE_LISTResourceList,PUINTBufferSize)` */
AKARI_CE_IMPORT VOID  NdisMQueryAdapterResources(PNDIS_STATUS Status, NDIS_HANDLE WrapperConfigurationContext, PNDIS_RESOURCE_LIST ResourceList, PUINT BufferSize)
                    AKARI_CE_NAME(NdisMQueryAdapterResources);

/* "NdisMQueryInformationComplete" (ms904046): print `VOID NdisMQueryInformationComplete(NDIS_HANDLE MiniportAdapterHandle,NDIS_STATUS Status)` */
AKARI_CE_IMPORT VOID  NdisMQueryInformationComplete(NDIS_HANDLE MiniportAdapterHandle, NDIS_STATUS Status)
                    AKARI_CE_NAME(NdisMQueryInformationComplete);

/* "NdisMRebindProtocolsToAdapter" (ms904047): print `VOID NdisMRebindProtocolsToAdapter(NDIS_HANDLE MiniportAdapterHandle)` */
AKARI_CE_IMPORT VOID  NdisMRebindProtocolsToAdapter(NDIS_HANDLE MiniportAdapterHandle)
                    AKARI_CE_NAME(NdisMRebindProtocolsToAdapter);

/* "NdisMRegisterInterrupt" (ms904049): print `NDIS_STATUS NdisMRegisterInterrupt(PNDIS_MINIPORT_INTERRUPT Interrupt,NDIS_HANDLE MiniportAdapterHandle,UINT InterruptVector,UINT InterruptLevel,BOOLEAN RequestIsr,BOOLEAN SharedInterrupt,NDIS_INTERRUPT_MODE InterruptMode)` */
AKARI_CE_IMPORT NDIS_STATUS  NdisMRegisterInterrupt(PNDIS_MINIPORT_INTERRUPT Interrupt, NDIS_HANDLE MiniportAdapterHandle, UINT InterruptVector, UINT InterruptLevel, BOOLEAN RequestIsr, BOOLEAN SharedInterrupt, NDIS_INTERRUPT_MODE InterruptMode)
                    AKARI_CE_NAME(NdisMRegisterInterrupt);

/* "NdisMRegisterIoPortRange" (ms904051): print `NDIS_STATUS NdisMRegisterIoPortRange(PVOID* PortOffset,NDIS_HANDLEMiniportAdapterHandle,UINTInitialPort,UINTNumberOfPorts)` */
AKARI_CE_IMPORT NDIS_STATUS  NdisMRegisterIoPortRange(PVOID*PortOffset, NDIS_HANDLE MiniportAdapterHandle, UINT InitialPort, UINT NumberOfPorts)
                    AKARI_CE_NAME(NdisMRegisterIoPortRange);

/* "NdisMRegisterMiniport" (ms904052): print `NDIS_STATUS NdisMRegisterMiniport(NDIS_HANDLE NdisWrapperHandle,PNDIS_MINIPORT_CHARACTERISTICS MiniportCharacteristics,UINT CharacteristicsLength)` */
AKARI_CE_IMPORT NDIS_STATUS  NdisMRegisterMiniport(NDIS_HANDLE NdisWrapperHandle, PNDIS_MINIPORT_CHARACTERISTICS MiniportCharacteristics, UINT CharacteristicsLength)
                    AKARI_CE_NAME(NdisMRegisterMiniport);

/* "NdisMRemoveMiniport" (ms904054): print `NDIS_STATUS NdisMRemoveMiniport(NDIS_HANDLEMiniportAdapterHandle)` */
AKARI_CE_IMPORT NDIS_STATUS  NdisMRemoveMiniport(NDIS_HANDLE MiniportAdapterHandle)
                    AKARI_CE_NAME(NdisMRemoveMiniport);

/* "NdisMResetComplete" (ms904055): print `VOID NdisMResetComplete(NDIS_HANDLEMiniportAdapterHandle,NDIS_STATUSStatus,BOOLEANAddressingReset)` */
AKARI_CE_IMPORT VOID  NdisMResetComplete(NDIS_HANDLE MiniportAdapterHandle, NDIS_STATUS Status, BOOLEAN AddressingReset)
                    AKARI_CE_NAME(NdisMResetComplete);

/* "NdisMSendComplete" (ms904056): print `VOID NdisMSendComplete(NDIS_HANDLE MiniportAdapterHandle,PNDIS_PACKET Packet,NDIS_STATUS Status)` */
AKARI_CE_IMPORT VOID  NdisMSendComplete(NDIS_HANDLE MiniportAdapterHandle, PNDIS_PACKET Packet, NDIS_STATUS Status)
                    AKARI_CE_NAME(NdisMSendComplete);

/* "NdisMSendResourcesAvailable" (ms904057): print `VOID NdisMSendResourcesAvailable(NDIS_HANDLE MiniportAdapterHandle)` */
AKARI_CE_IMPORT VOID  NdisMSendResourcesAvailable(NDIS_HANDLE MiniportAdapterHandle)
                    AKARI_CE_NAME(NdisMSendResourcesAvailable);

/* "NdisMSetAttributes" (ms904058): print `VOID NdisMSetAttributes(NDIS_HANDLE MiniportAdapterHandle,NDIS_HANDLEMiniportAdapterContext,BOOLEAN BusMaster,NDIS_INTERFACE_TYPEAdapterType)` */
AKARI_CE_IMPORT VOID  NdisMSetAttributes(NDIS_HANDLE MiniportAdapterHandle, NDIS_HANDLE MiniportAdapterContext, BOOLEAN BusMaster, NDIS_INTERFACE_TYPE AdapterType)
                    AKARI_CE_NAME(NdisMSetAttributes);

/* "NdisMSetAttributesEx" (ms904059): print `VOID NdisMSetAttributesEx(NDIS_HANDLE MiniportAdapterHandle,NDIS_HANDLEMiniportAdapterContext,UINTCheckForHangTimeInSeconds,ULONGAttributeFlags,NDIS_INTERFACE_TYPEAdapterType)` */
AKARI_CE_IMPORT VOID  NdisMSetAttributesEx(NDIS_HANDLE MiniportAdapterHandle, NDIS_HANDLE MiniportAdapterContext, UINT CheckForHangTimeInSeconds, ULONG AttributeFlags, NDIS_INTERFACE_TYPE AdapterType)
                    AKARI_CE_NAME(NdisMSetAttributesEx);

/* "NdisMSetInformationComplete" (ms904060): print `VOID NdisMSetInformationComplete(NDIS_HANDLE MiniportAdapterHandle,NDIS_STATUS Status)` */
AKARI_CE_IMPORT VOID  NdisMSetInformationComplete(NDIS_HANDLE MiniportAdapterHandle, NDIS_STATUS Status)
                    AKARI_CE_NAME(NdisMSetInformationComplete);

/* "NdisMSetMiniportSecondary" (ms904061): print `NDIS_STATUS NdisMSetMiniportSecondary(NDIS_HANDLEMiniportAdapterHandle, NDIS_HANDLEPrimaryMiniportAdapterHandle)` */
AKARI_CE_IMPORT NDIS_STATUS  NdisMSetMiniportSecondary(NDIS_HANDLE MiniportAdapterHandle, NDIS_HANDLE PrimaryMiniportAdapterHandle)
                    AKARI_CE_NAME(NdisMSetMiniportSecondary);

/* "NdisMSetPeriodicTimer" (ms904062): print `VOID NdisMSetPeriodicTimer(PNDIS_MINIPORT_TIMER Timer,UINT MillisecondsPeriod)` */
AKARI_CE_IMPORT VOID  NdisMSetPeriodicTimer(PNDIS_MINIPORT_TIMER Timer, UINT MillisecondsPeriod)
                    AKARI_CE_NAME(NdisMSetPeriodicTimer);

/* "NdisMSetTimer" (ms904063): print `VOID NdisMSetTimer(PNDIS_MINIPORT_TIMER Timer,UINT MillisecondsToDelay)` */
AKARI_CE_IMPORT VOID  NdisMSetTimer(PNDIS_MINIPORT_TIMER Timer, UINT MillisecondsToDelay)
                    AKARI_CE_NAME(NdisMSetTimer);

/* "NdisMSleep" (ms904064): print `VOIDNdisMSleep(ULONGMicrosecondsToSleep)` */
AKARI_CE_IMPORT VOID NdisMSleep(ULONG MicrosecondsToSleep)
                    AKARI_CE_NAME(NdisMSleep);

/* "NdisMSynchronizeWithInterrupt" (ms904066): print `BOOLEAN NdisMSynchronizeWithInterrupt(PNDIS_MINIPORT_INTERRUPT Interrupt,PVOID SynchronizeFunction,PVOID SynchronizeContext)` */
AKARI_CE_IMPORT BOOLEAN  NdisMSynchronizeWithInterrupt(PNDIS_MINIPORT_INTERRUPT Interrupt, PVOID SynchronizeFunction, PVOID SynchronizeContext)
                    AKARI_CE_NAME(NdisMSynchronizeWithInterrupt);

/* "NdisMTransferDataComplete" (ms904067): print `VOID NdisMTransferDataComplete(NDIS_HANDLE MiniportAdapterHandle,PNDIS_PACKET Packet,NDIS_STATUS Status,UINT BytesTransferred)` */
AKARI_CE_IMPORT VOID  NdisMTransferDataComplete(NDIS_HANDLE MiniportAdapterHandle, PNDIS_PACKET Packet, NDIS_STATUS Status, UINT BytesTransferred)
                    AKARI_CE_NAME(NdisMTransferDataComplete);

/* "NdisMTrIndicateReceive" (ms904068): print `VOID NdisMTrIndicateReceive( NDIS_HANDLEMiniportAdapterHandle, NDIS_HANDLEMiniportReceiveContext, PVOIDHeaderBuffer, UINTHeaderBufferSize, PVOIDLookaheadBuffer, UINTLookaheadBufferSize, UINTPacketSize)` */
AKARI_CE_IMPORT VOID  NdisMTrIndicateReceive(NDIS_HANDLE MiniportAdapterHandle, NDIS_HANDLE MiniportReceiveContext, PVOID HeaderBuffer, UINT HeaderBufferSize, PVOID LookaheadBuffer, UINT LookaheadBufferSize, UINT PacketSize)
                    AKARI_CE_NAME(NdisMTrIndicateReceive);

/* "NdisMTrIndicateReceiveComplete" (ms904069): print `VOID NdisMTrIndicateReceiveComplete( NDIS_HANDLEMiniportAdapterHandle)` */
AKARI_CE_IMPORT VOID  NdisMTrIndicateReceiveComplete(NDIS_HANDLE MiniportAdapterHandle)
                    AKARI_CE_NAME(NdisMTrIndicateReceiveComplete);

/* "NdisMUnmapIoSpace" (ms904070): print `VOID NdisMUnmapIoSpace(NDIS_HANDLE MiniportAdapterHandle,PVOIDVirtualAddress,UINTLength)` */
AKARI_CE_IMPORT VOID  NdisMUnmapIoSpace(NDIS_HANDLE MiniportAdapterHandle, PVOID VirtualAddress, UINT Length)
                    AKARI_CE_NAME(NdisMUnmapIoSpace);

/* "NdisMUpdateSharedMemory" (ms904071): print `VOID NdisMUpdateSharedMemory(NDIS_HANDLEMiniportAdapterHandle,ULONGLength,PVOIDVirtualAddress,NDIS_PHYSICAL_ADDRESSPhysicalAddress)` */
AKARI_CE_IMPORT VOID  NdisMUpdateSharedMemory(NDIS_HANDLE MiniportAdapterHandle, ULONG Length, PVOID VirtualAddress, NDIS_PHYSICAL_ADDRESS PhysicalAddress)
                    AKARI_CE_NAME(NdisMUpdateSharedMemory);

/* "NdisMWanIndicateReceive" (ms904072): print `VOID NdisMWanIndicateReceive( PNDIS_STATUSStatus, NDIS_HANDLEMiniportAdapterHandle, NDIS_HANDLENdisLinkContext, PUCHARPacketBuffer, UINTPacketSize)` */
AKARI_CE_IMPORT VOID  NdisMWanIndicateReceive(PNDIS_STATUS Status, NDIS_HANDLE MiniportAdapterHandle, NDIS_HANDLE NdisLinkContext, PUCHAR PacketBuffer, UINT PacketSize)
                    AKARI_CE_NAME(NdisMWanIndicateReceive);

/* "NdisMWanIndicateReceiveComplete" (ms904073): print `VOID NdisMWanIndicateReceiveComplete( NDIS_HANDLEMiniportAdapterHandle, NDIS_HANDLENdisLinkContext)` */
AKARI_CE_IMPORT VOID  NdisMWanIndicateReceiveComplete(NDIS_HANDLE MiniportAdapterHandle, NDIS_HANDLE NdisLinkContext)
                    AKARI_CE_NAME(NdisMWanIndicateReceiveComplete);

/* "NdisMWanSendComplete" (ms904074): print `VOID NdisMWanSendComplete( NDIS_HANDLEMiniportAdapterHandle, PNDIS_WAN_PACKETPacket, NDIS_STATUSStatus)` */
AKARI_CE_IMPORT VOID  NdisMWanSendComplete(NDIS_HANDLE MiniportAdapterHandle, PNDIS_WAN_PACKET Packet, NDIS_STATUS Status)
                    AKARI_CE_NAME(NdisMWanSendComplete);

/* "NdisMWriteLogData" (ms904075): print `NDIS_STATUS NdisMWriteLogData( NDIS_HANDLELogHandle, PVOIDLogBuffer, UINTLogBufferSize)` */
AKARI_CE_IMPORT NDIS_STATUS  NdisMWriteLogData(NDIS_HANDLE LogHandle, PVOID LogBuffer, UINT LogBufferSize)
                    AKARI_CE_NAME(NdisMWriteLogData);

/* "NdisOpenConfiguration" (ms904079): print `VOIDNdisOpenConfiguration(PNDIS_STATUSStatus,PNDIS_HANDLEConfigurationHandle,NDIS_HANDLEWrapperConfigurationContext)` */
AKARI_CE_IMPORT VOID NdisOpenConfiguration(PNDIS_STATUS Status, PNDIS_HANDLE ConfigurationHandle, NDIS_HANDLE WrapperConfigurationContext)
                    AKARI_CE_NAME(NdisOpenConfiguration);

/* "NdisOpenConfigurationKeyByIndex" (ms904080): print `VOID NdisOpenConfigurationKeyByIndex(PNDIS_STATUSStatus,NDIS_HANDLEConfigurationHandle,ULONGIndex,PNDIS_STRINGKeyName,PNDIS_HANDLEKeyHandle)` */
AKARI_CE_IMPORT VOID  NdisOpenConfigurationKeyByIndex(PNDIS_STATUS Status, NDIS_HANDLE ConfigurationHandle, ULONG Index, PNDIS_STRING KeyName, PNDIS_HANDLE KeyHandle)
                    AKARI_CE_NAME(NdisOpenConfigurationKeyByIndex);

/* "NdisOpenConfigurationKeyByName" (ms904081): print `VOID NdisOpenConfigurationKeyByName(PNDIS_STATUSStatus,NDIS_HANDLEConfigurationHandle,PNDIS_STRINGSubKeyName,PNDIS_HANDLESubKeyHandle)` */
AKARI_CE_IMPORT VOID  NdisOpenConfigurationKeyByName(PNDIS_STATUS Status, NDIS_HANDLE ConfigurationHandle, PNDIS_STRING SubKeyName, PNDIS_HANDLE SubKeyHandle)
                    AKARI_CE_NAME(NdisOpenConfigurationKeyByName);

/* "NdisOpenFile" (ms904082): print `VOID NdisOpenFile(PNDIS_STATUSStatus,PNDIS_HANDLEFileHandle,PUINTFileLength,PNDIS_STRINGFileName,NDIS_PHYSICAL_ADDRESSHighestAcceptableAddress)` */
AKARI_CE_IMPORT VOID  NdisOpenFile(PNDIS_STATUS Status, PNDIS_HANDLE FileHandle, PUINT FileLength, PNDIS_STRING FileName, NDIS_PHYSICAL_ADDRESS HighestAcceptableAddress)
                    AKARI_CE_NAME(NdisOpenFile);

/* "NdisOpenProtocolConfiguration" (ms904083): print `VOIDNdisOpenProtocolConfiguration(PNDIS_STATUSStatus,PNDIS_HANDLEConfigurationHandle,PNDIS_STRINGProtocolSection)` */
AKARI_CE_IMPORT VOID NdisOpenProtocolConfiguration(PNDIS_STATUS Status, PNDIS_HANDLE ConfigurationHandle, PNDIS_STRING ProtocolSection)
                    AKARI_CE_NAME(NdisOpenProtocolConfiguration);

/* "NdisPrintString" (ms904097): print `ULONG NdisPrintString(PNDIS_STRING String)` */
AKARI_CE_IMPORT ULONG  NdisPrintString(PNDIS_STRING String)
                    AKARI_CE_NAME(NdisPrintString);

/* "NdisQueryAdapterInstanceName" (ms904100): print `NDIS_STATUS NdisQueryAdapterInstanceName(PNDIS_STRINGAdapterInstanceName,NDIS_HANDLENdisBindingHandle)` */
AKARI_CE_IMPORT NDIS_STATUS  NdisQueryAdapterInstanceName(PNDIS_STRING AdapterInstanceName, NDIS_HANDLE NdisBindingHandle)
                    AKARI_CE_NAME(NdisQueryAdapterInstanceName);

/* "NdisQueryBuffer" (ms904101): print `VOIDNdisQueryBuffer(PNDIS_BUFFERBuffer,PVOID* VirtualAddressOPTIONAL,PUINTLength)` */
AKARI_CE_IMPORT VOID NdisQueryBuffer(PNDIS_BUFFER Buffer, PVOID*VirtualAddress, PUINT Length)
                    AKARI_CE_NAME(NdisQueryBuffer);

/* "NdisQueryBufferOffset" (ms904102): print `VOID NdisQueryBufferOffset(PNDIS_BUFFER Buffer,PUINT Offset,PUINT Length)` */
AKARI_CE_IMPORT VOID  NdisQueryBufferOffset(PNDIS_BUFFER Buffer, PUINT Offset, PUINT Length)
                    AKARI_CE_NAME(NdisQueryBufferOffset);

/* "NdisQueryPacket" (ms904104): print `VOID NdisQueryPacket(PNDIS_PACKET Packet,PUINT PhysicalBufferCount,PUINT BufferCount,PNDIS_BUFFER* FirstBuffer,PUINT TotalPacketLength)` */
AKARI_CE_IMPORT VOID  NdisQueryPacket(PNDIS_PACKET Packet, PUINT PhysicalBufferCount, PUINT BufferCount, PNDIS_BUFFER*FirstBuffer, PUINT TotalPacketLength)
                    AKARI_CE_NAME(NdisQueryPacket);

/* "NdisQueryPendingIoCount" (ms904105): print `NDIS_STATUS NdisQueryPendingIoCount(PVOID NdisBindingHandle,PULONG IoCount)` */
AKARI_CE_IMPORT NDIS_STATUS  NdisQueryPendingIoCount(PVOID NdisBindingHandle, PULONG IoCount)
                    AKARI_CE_NAME(NdisQueryPendingIoCount);

/* "NdisRawReadPortBufferUchar" (ms904107): print `VOID NdisRawReadPortBufferUchar(ULONG Port,PUCHAR Buffer,ULONG Length)` */
AKARI_CE_IMPORT VOID  NdisRawReadPortBufferUchar(ULONG Port, PUCHAR Buffer, ULONG Length)
                    AKARI_CE_NAME(NdisRawReadPortBufferUchar);

/* "NdisRawReadPortBufferUlong" (ms904108): print `VOID NdisRawReadPortBufferUlong(ULONG Port,PULONG Buffer,ULONG Length)` */
AKARI_CE_IMPORT VOID  NdisRawReadPortBufferUlong(ULONG Port, PULONG Buffer, ULONG Length)
                    AKARI_CE_NAME(NdisRawReadPortBufferUlong);

/* "NdisRawReadPortBufferUshort" (ms904109): print `VOID NdisRawReadPortBufferUshort(ULONG Port,PUSHORT Buffer,ULONG Length)` */
AKARI_CE_IMPORT VOID  NdisRawReadPortBufferUshort(ULONG Port, PUSHORT Buffer, ULONG Length)
                    AKARI_CE_NAME(NdisRawReadPortBufferUshort);

/* "NdisRawReadPortUchar" (ms904110): print `VOID NdisRawReadPortUchar(ULONG Port,PUCHAR Data)` */
AKARI_CE_IMPORT VOID  NdisRawReadPortUchar(ULONG Port, PUCHAR Data)
                    AKARI_CE_NAME(NdisRawReadPortUchar);

/* "NdisRawReadPortUlong" (ms904112): print `VOID NdisRawReadPortUlong(ULONG Port,PULONG Data)` */
AKARI_CE_IMPORT VOID  NdisRawReadPortUlong(ULONG Port, PULONG Data)
                    AKARI_CE_NAME(NdisRawReadPortUlong);

/* "NdisRawReadPortUshort" (ms904113): print `VOID NdisRawReadPortUshort(ULONG Port,PUSHORT Data)` */
AKARI_CE_IMPORT VOID  NdisRawReadPortUshort(ULONG Port, PUSHORT Data)
                    AKARI_CE_NAME(NdisRawReadPortUshort);

/* "NdisRawWritePortBufferUchar" (ms904114): print `VOID NdisRawWritePortBufferUchar(ULONG Port,PUCHAR Buffer,ULONG Length)` */
AKARI_CE_IMPORT VOID  NdisRawWritePortBufferUchar(ULONG Port, PUCHAR Buffer, ULONG Length)
                    AKARI_CE_NAME(NdisRawWritePortBufferUchar);

/* "NdisRawWritePortBufferUlong" (ms904115): print `VOID NdisRawWritePortBufferUlong(ULONG Port,PULONG Buffer,ULONG Length)` */
AKARI_CE_IMPORT VOID  NdisRawWritePortBufferUlong(ULONG Port, PULONG Buffer, ULONG Length)
                    AKARI_CE_NAME(NdisRawWritePortBufferUlong);

/* "NdisRawWritePortBufferUshort" (ms904116): print `VOID NdisRawWritePortBufferUshort(ULONG Port,PUSHORT Buffer,ULONG Length)` */
AKARI_CE_IMPORT VOID  NdisRawWritePortBufferUshort(ULONG Port, PUSHORT Buffer, ULONG Length)
                    AKARI_CE_NAME(NdisRawWritePortBufferUshort);

/* "NdisRawWritePortUchar" (ms904117): print `VOID NdisRawWritePortUchar(ULONG Port,UCHAR Data)` */
AKARI_CE_IMPORT VOID  NdisRawWritePortUchar(ULONG Port, UCHAR Data)
                    AKARI_CE_NAME(NdisRawWritePortUchar);

/* "NdisRawWritePortUlong" (ms904118): print `VOID NdisRawWritePortUlong(ULONG Port,ULONG Data)` */
AKARI_CE_IMPORT VOID  NdisRawWritePortUlong(ULONG Port, ULONG Data)
                    AKARI_CE_NAME(NdisRawWritePortUlong);

/* "NdisRawWritePortUshort" (ms904119): print `VOID NdisRawWritePortUshort(ULONG Port,USHORT Data)` */
AKARI_CE_IMPORT VOID  NdisRawWritePortUshort(ULONG Port, USHORT Data)
                    AKARI_CE_NAME(NdisRawWritePortUshort);

/* "NdisReadConfiguration" (ms904120): print `VOID NdisReadConfiguration(PNDIS_STATUS Status,PNDIS_CONFIGURATION_PARAMETER* ParameterValue,NDIS_HANDLE ConfigurationHandle,PNDIS_STRING Keyword,NDIS_PARAMETER_TYPE ParameterType)` */
AKARI_CE_IMPORT VOID  NdisReadConfiguration(PNDIS_STATUS Status, PNDIS_CONFIGURATION_PARAMETER*ParameterValue, NDIS_HANDLE ConfigurationHandle, PNDIS_STRING Keyword, NDIS_PARAMETER_TYPE ParameterType)
                    AKARI_CE_NAME(NdisReadConfiguration);

/* "NdisReadNetworkAddress" (ms904121): print `VOIDNdisReadNetworkAddress(PNDIS_STATUSStatus,PVOID* NetworkAddress,PUINTNetworkAddressLength,NDIS_HANDLEConfigurationHandle)` */
AKARI_CE_IMPORT VOID NdisReadNetworkAddress(PNDIS_STATUS Status, PVOID*NetworkAddress, PUINT NetworkAddressLength, NDIS_HANDLE ConfigurationHandle)
                    AKARI_CE_NAME(NdisReadNetworkAddress);

/* "NdisReadPciSlotInformation" (ms904122): print `ULONG NdisReadPciSlotInformation(NDIS_HANDLE NdisAdapterHandle,ULONG SlotNumber,ULONG Offset,PVOID Buffer,ULONGLength)` */
AKARI_CE_IMPORT ULONG  NdisReadPciSlotInformation(NDIS_HANDLE NdisAdapterHandle, ULONG SlotNumber, ULONG Offset, PVOID Buffer, ULONG Length)
                    AKARI_CE_NAME(NdisReadPciSlotInformation);

/* "NdisReadPcmciaAttributeMemory" (ms904123): print `ULONG NdisReadPcmciaAttributeMemory(NDIS_HANDLENdisAdapterHandle,ULONG Offset,PVOID Buffer,ULONG Length)` */
AKARI_CE_IMPORT ULONG  NdisReadPcmciaAttributeMemory(NDIS_HANDLE NdisAdapterHandle, ULONG Offset, PVOID Buffer, ULONG Length)
                    AKARI_CE_NAME(NdisReadPcmciaAttributeMemory);

/* "NdisReadPortUchar" (ms904124): print `VOID NdisReadPortUchar(NDIS_HANDLENdisAdapterHandle,ULONG Port,PUCHARData)` */
AKARI_CE_IMPORT VOID  NdisReadPortUchar(NDIS_HANDLE NdisAdapterHandle, ULONG Port, PUCHAR Data)
                    AKARI_CE_NAME(NdisReadPortUchar);

/* "NdisReadPortUlong" (ms904125): print `VOID NdisReadPortUlong(NDIS_HANDLE NdisAdapterHandle,ULONG Port,PULONG Data)` */
AKARI_CE_IMPORT VOID  NdisReadPortUlong(NDIS_HANDLE NdisAdapterHandle, ULONG Port, PULONG Data)
                    AKARI_CE_NAME(NdisReadPortUlong);

/* "NdisReadPortUshort" (ms904126): print `VOIDNdisReadPortUshort(NDIS_HANDLE NdisAdapterHandle,ULONG Port,PUSHORTData)` */
AKARI_CE_IMPORT VOID NdisReadPortUshort(NDIS_HANDLE NdisAdapterHandle, ULONG Port, PUSHORT Data)
                    AKARI_CE_NAME(NdisReadPortUshort);

/* "NdisReadRegisterUchar" (ms904127): print `VOID NdisReadRegisterUchar(PUCHARRegister,PUCHARData)` */
AKARI_CE_IMPORT VOID  NdisReadRegisterUchar(PUCHAR Register, PUCHAR Data)
                    AKARI_CE_NAME(NdisReadRegisterUchar);

/* "NdisReadRegisterUlong" (ms904128): print `VOID NdisReadRegisterUlong(PULONGRegister,PULONGData)` */
AKARI_CE_IMPORT VOID  NdisReadRegisterUlong(PULONG Register, PULONG Data)
                    AKARI_CE_NAME(NdisReadRegisterUlong);

/* "NdisReadRegisterUshort" (ms904129): print `VOID NdisReadRegisterUshort(PUSHORTRegister,PUSHORTData)` */
AKARI_CE_IMPORT VOID  NdisReadRegisterUshort(PUSHORT Register, PUSHORT Data)
                    AKARI_CE_NAME(NdisReadRegisterUshort);

/* "NdisRebindProtocolsToAdapter" (ms904130): print `VOID NdisRebindProtocolsToAdapter( PNDIS_STATUS pStatus,PWSTRwszAdapterInstanceName,PWSTRwszProtocolName)` */
AKARI_CE_IMPORT VOID  NdisRebindProtocolsToAdapter(PNDIS_STATUS pStatus, PWSTR wszAdapterInstanceName, PWSTR wszProtocolName)
                    AKARI_CE_NAME(NdisRebindProtocolsToAdapter);

/* "NdisRecalculatePacketCounts" (ms904131): print `VOID NdisRecalculatePacketCounts(PNDIS_PACKET Packet)` */
AKARI_CE_IMPORT VOID  NdisRecalculatePacketCounts(PNDIS_PACKET Packet)
                    AKARI_CE_NAME(NdisRecalculatePacketCounts);

/* "NdisReEnumerateProtocolBindings" (ms904132): print `VOID NdisReEnumerateProtocolBindings(NDIS_HANDLE NdisProtocolHandle)` */
AKARI_CE_IMPORT VOID  NdisReEnumerateProtocolBindings(NDIS_HANDLE NdisProtocolHandle)
                    AKARI_CE_NAME(NdisReEnumerateProtocolBindings);

/* "NdisRegisterAdapter" (ms904133): print `VOID NdisRegisterAdapter(PNDIS_STATUS Status,PWSTRMiniportDriverName,PWSTR AdapterInstanceName)` */
AKARI_CE_IMPORT VOID  NdisRegisterAdapter(PNDIS_STATUS Status, PWSTR MiniportDriverName, PWSTR AdapterInstanceName)
                    AKARI_CE_NAME(NdisRegisterAdapter);

/* "NdisRegisterProtocol" (ms904134): print `VOIDNdisRegisterProtocol(PNDIS_STATUSStatus,PNDIS_HANDLENdisProtocolHandle,PNDIS_PROTOCOL_CHARACTERISTICSProtocolCharacteristics,UINTCharacteristicsLength)` */
AKARI_CE_IMPORT VOID NdisRegisterProtocol(PNDIS_STATUS Status, PNDIS_HANDLE NdisProtocolHandle, PNDIS_PROTOCOL_CHARACTERISTICS ProtocolCharacteristics, UINT CharacteristicsLength)
                    AKARI_CE_NAME(NdisRegisterProtocol);

/* "NdisReinitializePacket" (ms904135): print `VOID NdisReinitializePacket(PNDIS_PACKET Packet)` */
AKARI_CE_IMPORT VOID  NdisReinitializePacket(PNDIS_PACKET Packet)
                    AKARI_CE_NAME(NdisReinitializePacket);

/* "NdisReleaseReadWriteLock" (ms904136): print `VOID NdisReleaseReadWriteLock(PNDIS_RW_LOCKLock,PLOCK_STATELockState)` */
AKARI_CE_IMPORT VOID  NdisReleaseReadWriteLock(PNDIS_RW_LOCK Lock, PLOCK_STATE LockState)
                    AKARI_CE_NAME(NdisReleaseReadWriteLock);

/* "NdisReleaseSpinLock" (ms904137): print `VOID NdisReleaseSpinLock(PNDIS_SPIN_LOCK SpinLock)` */
AKARI_CE_IMPORT VOID  NdisReleaseSpinLock(PNDIS_SPIN_LOCK SpinLock)
                    AKARI_CE_NAME(NdisReleaseSpinLock);

/* "NdisRequest" (ms904323): print `VOID NdisRequest(PNDIS_STATUS Status,NDIS_HANDLE NdisBindingHandle,PNDIS_REQUEST NdisRequest)` */
AKARI_CE_IMPORT VOID  NdisRequest(PNDIS_STATUS Status, NDIS_HANDLE NdisBindingHandle, PNDIS_REQUEST NdisRequest)
                    AKARI_CE_NAME(NdisRequest);

/* "NdisReset" (ms904619): print `VOID NdisReset(PNDIS_STATUS Status,NDIS_HANDLE NdisBindingHandle)` */
AKARI_CE_IMPORT VOID  NdisReset(PNDIS_STATUS Status, NDIS_HANDLE NdisBindingHandle)
                    AKARI_CE_NAME(NdisReset);

/* "NdisResetEvent" (ms904728): print `VOID NdisResetEvent(PNDIS_EVENTEvent)` */
AKARI_CE_IMPORT VOID  NdisResetEvent(PNDIS_EVENT Event)
                    AKARI_CE_NAME(NdisResetEvent);

/* "NdisRetrieveUlong" (ms904737): print `VOID NdisRetrieveUlong(PULONGDestinationAddress,PULONGSourceAddress)` */
AKARI_CE_IMPORT VOID  NdisRetrieveUlong(PULONG DestinationAddress, PULONG SourceAddress)
                    AKARI_CE_NAME(NdisRetrieveUlong);

/* "NdisReturnPackets" (ms904846): print `VOID NdisReturnPackets(PNDIS_PACKET* PacketsToReturn,UINTNumberOfPackets)` */
AKARI_CE_IMPORT VOID  NdisReturnPackets(PNDIS_PACKET*PacketsToReturn, UINT NumberOfPackets)
                    AKARI_CE_NAME(NdisReturnPackets);

/* "NdisScheduleWorkItem" (ms904952): print `NDIS_STATUS NdisScheduleWorkItem(PNDIS_WORK_ITEMWorkItem)` */
AKARI_CE_IMPORT NDIS_STATUS  NdisScheduleWorkItem(PNDIS_WORK_ITEM WorkItem)
                    AKARI_CE_NAME(NdisScheduleWorkItem);

/* "NdisSend" (ms904960): print `VOID NdisSend(PNDIS_STATUS Status,NDIS_HANDLE NdisBindingHandle,PNDIS_PACKET Packet)` */
AKARI_CE_IMPORT VOID  NdisSend(PNDIS_STATUS Status, NDIS_HANDLE NdisBindingHandle, PNDIS_PACKET Packet)
                    AKARI_CE_NAME(NdisSend);

/* "NdisSendPackets" (ms904962): print `VOID NdisSendPackets(NDIS_HANDLENdisBindingHandle,PPNDIS_PACKETPacketArray,UINTNumberOfPackets)` */
AKARI_CE_IMPORT VOID  NdisSendPackets(NDIS_HANDLE NdisBindingHandle, PNDIS_PACKET*PacketArray, UINT NumberOfPackets)
                    AKARI_CE_NAME(NdisSendPackets);

/* "NdisSetEvent" (ms904963): print `VOID NdisSetEvent(PNDIS_EVENTEvent)` */
AKARI_CE_IMPORT VOID  NdisSetEvent(PNDIS_EVENT Event)
                    AKARI_CE_NAME(NdisSetEvent);

/* "NdisSetPacketCancelId" (ms904966): print `VOID NdisSetPacketCancelId(PNDIS_PACKETPacket,ULONG_PTRCancelId)` */
AKARI_CE_IMPORT VOID  NdisSetPacketCancelId(PNDIS_PACKET Packet, ULONG_PTR CancelId)
                    AKARI_CE_NAME(NdisSetPacketCancelId);

/* "NdisSetPacketFlags" (ms904968): print `VOID NdisSetPacketFlags(PNDIS_PACKET Packet,UINT Flags)` */
AKARI_CE_IMPORT VOID  NdisSetPacketFlags(PNDIS_PACKET Packet, UINT Flags)
                    AKARI_CE_NAME(NdisSetPacketFlags);

/* "NdisSetPhysicalAddressHigh" (ms904976): print `VOID NdisSetPhysicalAddressHigh(NDIS_PHYSICAL_ADDRESS PhysicalAddress,ULONG Value)` */
AKARI_CE_IMPORT VOID  NdisSetPhysicalAddressHigh(NDIS_PHYSICAL_ADDRESS PhysicalAddress, ULONG Value)
                    AKARI_CE_NAME(NdisSetPhysicalAddressHigh);

/* "NdisSetPhysicalAddressLow" (ms904977): print `VOID NdisSetPhysicalAddressLow(NDIS_PHYSICAL_ADDRESS PhysicalAddress,ULONG Value)` */
AKARI_CE_IMPORT VOID  NdisSetPhysicalAddressLow(NDIS_PHYSICAL_ADDRESS PhysicalAddress, ULONG Value)
                    AKARI_CE_NAME(NdisSetPhysicalAddressLow);

/* "NdisSetTimer" (ms904979): print `VOID NdisSetTimer(PNDIS_TIMERTimer,UINTMillisecondsToDelay)` */
AKARI_CE_IMPORT VOID  NdisSetTimer(PNDIS_TIMER Timer, UINT MillisecondsToDelay)
                    AKARI_CE_NAME(NdisSetTimer);

/* "NdisStallExecution" (ms904980): print `VOID NdisStallExecution(UINTMicrosecondsToStall)` */
AKARI_CE_IMPORT VOID  NdisStallExecution(UINT MicrosecondsToStall)
                    AKARI_CE_NAME(NdisStallExecution);

/* "NdisStoreUlong" (ms904982): print `VOID NdisStoreUlong(PULONGDestinationAddress,ULONGValue)` */
AKARI_CE_IMPORT VOID  NdisStoreUlong(PULONG DestinationAddress, ULONG Value)
                    AKARI_CE_NAME(NdisStoreUlong);

/* "NdisSystemProcessorCount" (ms904984): print `CCHAR NdisSystemProcessorCount(VOID)` */
AKARI_CE_IMPORT CCHAR  NdisSystemProcessorCount(void)
                    AKARI_CE_NAME(NdisSystemProcessorCount);

/* "NdisTerminateWrapper" (ms905028): print `VOIDNdisTerminateWrapper(NDIS_HANDLENdisWrapperHandle,PVOIDSystemSpecific)` */
AKARI_CE_IMPORT VOID NdisTerminateWrapper(NDIS_HANDLE NdisWrapperHandle, PVOID SystemSpecific)
                    AKARI_CE_NAME(NdisTerminateWrapper);

/* "NdisTransferData" (ms905029): print `VOID NdisTransferData(PNDIS_STATUS Status,NDIS_HANDLE NdisBindingHandle,NDIS_HANDLE MacReceiveContext,UINT ByteOffset,UINT BytesToTransfer,PNDIS_PACKET Packet,PUINT BytesTransferred)` */
AKARI_CE_IMPORT VOID  NdisTransferData(PNDIS_STATUS Status, NDIS_HANDLE NdisBindingHandle, NDIS_HANDLE MacReceiveContext, UINT ByteOffset, UINT BytesToTransfer, PNDIS_PACKET Packet, PUINT BytesTransferred)
                    AKARI_CE_NAME(NdisTransferData);

/* "NdisUnbindProtocolsFromAdapter" (ms905035): print `VOID NdisUnbindProtocolsFromAdapter( PNDIS_STATUS pStatus,PWSTRwszAdapterInstanceName,PWSTRwszProtocolName,)` */
AKARI_CE_IMPORT VOID  NdisUnbindProtocolsFromAdapter(PNDIS_STATUS pStatus, PWSTR wszAdapterInstanceName, PWSTR wszProtocolName)
                    AKARI_CE_NAME(NdisUnbindProtocolsFromAdapter);

/* "NdisUnchainBufferAtBack" (ms905036): print `VOID NdisUnchainBufferAtBack(PNDIS_PACKET Packet,PNDIS_BUFFER* Buffer)` */
AKARI_CE_IMPORT VOID  NdisUnchainBufferAtBack(PNDIS_PACKET Packet, PNDIS_BUFFER*Buffer)
                    AKARI_CE_NAME(NdisUnchainBufferAtBack);

/* "NdisUnchainBufferAtFront" (ms905037): print `VOID NdisUnchainBufferAtFront(PNDIS_PACKET Packet,PNDIS_BUFFER* Buffer)` */
AKARI_CE_IMPORT VOID  NdisUnchainBufferAtFront(PNDIS_PACKET Packet, PNDIS_BUFFER*Buffer)
                    AKARI_CE_NAME(NdisUnchainBufferAtFront);

/* "NdisUnicodeStringToAnsiString" (ms905038): print `NDIS_STATUS NdisUnicodeStringToAnsiString(PNDIS_ANSI_STRING DestinationString,PNDIS_STRING SourceString)` */
AKARI_CE_IMPORT NDIS_STATUS  NdisUnicodeStringToAnsiString(PNDIS_ANSI_STRING DestinationString, PNDIS_STRING SourceString)
                    AKARI_CE_NAME(NdisUnicodeStringToAnsiString);

/* "NdisUnmapFile" (ms905039): print `VOID NdisUnmapFile(NDIS_HANDLEFileHandle)` */
AKARI_CE_IMPORT VOID  NdisUnmapFile(NDIS_HANDLE FileHandle)
                    AKARI_CE_NAME(NdisUnmapFile);

/* "NdisUpcaseUnicodeString" (ms905040): print `NTSTATUS NdisUpcaseUnicodeString(PUNICODE_STRINGDestinationString,PUNICODE_STRINGSourceString)` */
AKARI_CE_IMPORT NTSTATUS  NdisUpcaseUnicodeString(PUNICODE_STRING DestinationString, PUNICODE_STRING SourceString)
                    AKARI_CE_NAME(NdisUpcaseUnicodeString);

/* "NdisWaitEvent" (ms905041): print `BOOLEAN NdisWaitEvent(PNDIS_EVENTEvent,UINTMsToWait)` */
AKARI_CE_IMPORT BOOLEAN  NdisWaitEvent(PNDIS_EVENT Event, UINT MsToWait)
                    AKARI_CE_NAME(NdisWaitEvent);

/* "NdisWriteConfiguration" (ms905055): print `VOID NdisWriteConfiguration(PNDIS_STATUS Status,NDIS_HANDLE ConfigurationHandle,PNDIS_STRING Keyword,PNDIS_CONFIGURATION_PARAMETER ParameterValue)` */
AKARI_CE_IMPORT VOID  NdisWriteConfiguration(PNDIS_STATUS Status, NDIS_HANDLE ConfigurationHandle, PNDIS_STRING Keyword, PNDIS_CONFIGURATION_PARAMETER ParameterValue)
                    AKARI_CE_NAME(NdisWriteConfiguration);

/* "NdisWriteErrorLogEntry" (ms905056): print `VOIDNdisWriteErrorLogEntry(NDIS_HANDLENdisAdapterHandle,NDIS_ERROR_CODEErrorCode,ULONGNumberOfErrorValues,ULONG ...)` */
AKARI_CE_IMPORT VOID NdisWriteErrorLogEntry(NDIS_HANDLE NdisAdapterHandle, NDIS_ERROR_CODE ErrorCode, ULONG NumberOfErrorValues, ...)
                    AKARI_CE_NAME(NdisWriteErrorLogEntry);

/* "NdisWritePciSlotInformation" (ms905057): print `ULONG NdisWritePciSlotInformation(NDIS_HANDLE NdisAdapterHandle,ULONG SlotNumber,ULONG Offset,PVOID Buffer,ULONGLength)` */
AKARI_CE_IMPORT ULONG  NdisWritePciSlotInformation(NDIS_HANDLE NdisAdapterHandle, ULONG SlotNumber, ULONG Offset, PVOID Buffer, ULONG Length)
                    AKARI_CE_NAME(NdisWritePciSlotInformation);

/* "NdisWritePcmciaAttributeMemory" (ms905058): print `ULONG NdisWritePcmciaAttributeMemory(NDIS_HANDLENdisAdapterHandle,ULONG Offset,PVOID Buffer,ULONG Length)` */
AKARI_CE_IMPORT ULONG  NdisWritePcmciaAttributeMemory(NDIS_HANDLE NdisAdapterHandle, ULONG Offset, PVOID Buffer, ULONG Length)
                    AKARI_CE_NAME(NdisWritePcmciaAttributeMemory);

/* "NdisWritePortUchar" (ms905254): print `VOID NdisWritePortUchar(NDIS_HANDLE NdisAdapterHandle,ULONGPort,UCHARData)` */
AKARI_CE_IMPORT VOID  NdisWritePortUchar(NDIS_HANDLE NdisAdapterHandle, ULONG Port, UCHAR Data)
                    AKARI_CE_NAME(NdisWritePortUchar);

/* "NdisWritePortUlong" (ms905257): print `VOID NdisWritePortUlong(NDIS_HANDLENdisAdapterHandle,ULONGPort,ULONGData)` */
AKARI_CE_IMPORT VOID  NdisWritePortUlong(NDIS_HANDLE NdisAdapterHandle, ULONG Port, ULONG Data)
                    AKARI_CE_NAME(NdisWritePortUlong);

/* "NdisWritePortUshort" (ms905261): print `VOID NdisWritePortUshort(NDIS_HANDLENdisAdapterHandle,ULONGPort,USHORTData)` */
AKARI_CE_IMPORT VOID  NdisWritePortUshort(NDIS_HANDLE NdisAdapterHandle, ULONG Port, USHORT Data)
                    AKARI_CE_NAME(NdisWritePortUshort);

/* "NdisWriteRegisterUchar" (ms905264): print `VOID NdisWriteRegisterUchar(PUCHARRegister,UCHARData)` */
AKARI_CE_IMPORT VOID  NdisWriteRegisterUchar(PUCHAR Register, UCHAR Data)
                    AKARI_CE_NAME(NdisWriteRegisterUchar);

/* "NdisWriteRegisterUlong" (ms905268): print `VOID NdisWriteRegisterUlong(PULONGRegister,ULONGData)` */
AKARI_CE_IMPORT VOID  NdisWriteRegisterUlong(PULONG Register, ULONG Data)
                    AKARI_CE_NAME(NdisWriteRegisterUlong);

/* "NdisWriteRegisterUshort" (ms905271): print `VOID NdisWriteRegisterUshort(PUSHORTRegister,USHORTData)` */
AKARI_CE_IMPORT VOID  NdisWriteRegisterUshort(PUSHORT Register, USHORT Data)
                    AKARI_CE_NAME(NdisWriteRegisterUshort);

/* "NdisZeroMappedMemory" (ms905277): print `VOID NdisZeroMappedMemory(PVOID Destination,ULONG Length)` */
AKARI_CE_IMPORT VOID  NdisZeroMappedMemory(PVOID Destination, ULONG Length)
                    AKARI_CE_NAME(NdisZeroMappedMemory);

/* "NdisZeroMemory" (ms905279): print `VOIDNdisZeroMemory(PVOIDDestination,ULONGLength)` */
AKARI_CE_IMPORT VOID NdisZeroMemory(PVOID Destination, ULONG Length)
                    AKARI_CE_NAME(NdisZeroMemory);

/* --- Record-only: function prints naming types no CE page prints. */
/* NTSTATUS itself is grounded in Windef.h (IP NAT pages, M50); only
 * the prints whose parameter types are ungrounded stay here. */
/* Declared once the missing type gains a grounded print. */

/* "NdisBufferVirtualAddressSafe" (aa447918): `PVOID NdisBufferVirtualAddressSafe(PNDIS_BUFFERBuffer,MM_PAGE_PRIORITYPriority)` */
/* "NdisGetFirstBufferFromPacketSafe" (aa447967): `VOID NdisGetFirstBufferFromPacketSafe(PNDIS_PACKETPacket,PNDIS_BUFFER* FirstBuffer,PVOID* FirstBufferVA,PUINTFirstBufferLength,PUINTTotalBufferLength,MM_PAGE_PRIORITYPriority)` */
/* "NdisInitializeListHead" (aa448005): `VOIDNdisInitializeListHead(PLIST_ENTRYListHead)` */
/* "NdisInterlockedInsertHeadList" (aa448015): `PLIST_ENTRY NdisInterlockedInsertHeadList(PLIST_ENTRYListHead,PLIST_ENTRYListEntry,PNDIS_SPIN_LOCKSpinLock)` */
/* "NdisInterlockedInsertTailList" (aa448016): `PLIST_ENTRY NdisInterlockedInsertTailList(PLIST_ENTRYListHead,PLIST_ENTRYListEntry,PNDIS_SPIN_LOCKSpinLock)` */
/* "NdisInterlockedRemoveHeadList" (aa448017): `PLIST_ENTRY NdisInterlockedRemoveHeadList(PLIST_ENTRYListHead,PNDIS_SPIN_LOCKSpinLock)` */
/* "NdisMAllocateMapRegisters" (aa448022): `VOID NdisMAllocateMapRegisters(NDIS_HANDLE MiniportAdapterHandle,UINT DmaChannel,NDIS_DMA_SIZE DmaSize,ULONG PhysicalMapRegistersNeeded,ULONG MaximumPhysicalMapping)` */
/* "NdisAllocateFromNPagedLookasideList" (aa448312): `PVOID NdisAllocateFromNPagedLookasideList( IN PNPAGED_LOOKASIDE_LIST Lookaside)` */
/* "NdisDeleteNPagedLookasideList" (aa448314): `VOID NdisDeleteNPagedLookasideList( IN PNPAGED_LOOKASIDE_LIST Lookaside)` */
/* "NdisFreeToNPagedLookasideList" (aa448315): `VOID NdisFreeToNPagedLookasideList( IN PNPAGED_LOOKASIDE_LIST Lookaside, IN PVOID Entry)` */
/* "NdisIMQueueMiniportCallback" (aa448317): `NDIS STATUS_NdisIMQueueMiniportCallback (IN NDIS_HANDLE MiniportAdapterHandle,IN W_MINIPORT_CALLBACKCallbackRoutine,IN PVOIDCallbackContext)` */
/* "NdisInitializeNPagedLookasideList" (aa448320): `VOID NdisInitializeNPagedLookasideList( IN PNPAGED_LOOKASIDE_LISTLookaside, IN PALLOCATE_FUNCTION Allocate OPTIONAL, IN PFREE_FUNCTION Free OPTIONAL, IN ULONG Flags, IN ULONG Size, IN ULONG Tag, IN USHORT Depth)` */
/* "NdisMRegisterAdapterShutdownHandler" (ms904048): `VOID NdisMRegisterAdapterShutdownHandler(NDIS_HANDLE MiniportHandle,PVOID ShutdownContext,ADAPTER_SHUTDOWN_HANDLER ShutdownHandler)` */
/* "NdisMRegisterUnloadHandler" (ms904053): `VOID NdisMRegisterUnloadHandler(NDIS_HANDLENdisWrapperHandle,PDRIVER_UNLOADUnloadHandler)` */
/* "NdisMStartBufferPhysicalMapping" (ms904065): `NdisMStartBufferPhysicalMapping(NDIS_HANDLE MiniportAdapterHandle,PNDIS_BUFFER Buffer,ULONG PhysicalMapRegister,BOOLEAN WriteToDevice,PNDIS_PHYSICAL_ADDRESS_UNIT PhysicalAddressArray,PUINT ArraySize)` */
/* "NdisOpenAdapter" (ms904078): `VOIDNdisOpenAdapter(PNDIS_STATUSStatus,PNDIS_STATUSOpenErrorStatus,PNDIS_HANDLENdisBindingHandle,PUINTSelectedMediumIndex,PNDIS_MEDIUMMediumArray,UINTMediumArraySize,NDIS_HANDLENdisProtocolHandle,NDIS_HANDLEProtocolBindingContext,PNDIS_STRINGAdapterName,UINTOpenOptions,PSTRINGAddressingInformation)` */
/* "NdisQueryBufferSafe" (ms904103): `VOID NdisQueryBufferSafe(PNDIS_BUFFERBuffer,PVOID* VirtualAddressOPTIONAL,PUINTLength,MM_PAGE_PRIORITYPriority)` */

/* --- Record-only: macro prints (Ndis.h). ---------------------- */
/* These pages print macro definitions ("The XX macro is defined
 * as follows. #define ..."), not importable functions: the
 * NDIS_GET/SET_PACKET_x family, the NDIS_BUFFER_x, ETH_x and TR_x
 * token-manipulation helpers, NDIS_PHYSICAL_ADDRESS_CONST,
 * NDIS_INIT_FUNCTION and the *_FROM_PACKET accessors. */
/* "ETH_COPY_NETWORK_ADDRESS" (aa447796): `VOID ETH_COPY_NETWORK_ADDRESS(PCHAR _D,CHAR _S)` */
/* "NDIS_BUFFER_LINKAGE" (aa447915): `PVOID NDIS_BUFFER_LINKAGE(PNDIS_BUFFER Buffer)` */
/* "NDIS_BUFFER_TO_SPAN_PAGES" (aa447916): `ULONG NDIS_BUFFER_TO_SPAN_PAGES(PNDIS_BUFFER _Buffer)` */
/* "NDIS_GET_ORIGINAL_PACKET" (aa447969): `PNDIS_PACKET NDIS_GET_ORIGINAL_PACKET(PNDIS_PACKET_P)` */
/* "NDIS_GET_PACKET_CANCEL_ID" (aa447971): `PVOID NDIS_GET_PACKET_CANCEL_ID(PNDIS_PACKET _P)` */
/* "NDIS_GET_PACKET_HEADER_SIZE" (aa447973): `UINT NDIS_GET_PACKET_HEADER_SIZE(PNDIS_PACKET_Packet)` */
/* "NDIS_GET_PACKET_MEDIA_SPECIFIC_INFO" (aa447974): `VOID NDIS_GET_PACKET_MEDIA_SPECIFIC_INFO(PNDIS_PACKET_Packet,PPVOID_pMediaSpecificInfo,PUINT_pSizeMediaSpecificInfo)` */
/* "NDIS_GET_PACKET_PROTOCOL_TYPE" (aa447975): `UINT NDIS_GET_PACKET_PROTOCOL_TYPE(PNDIS_PACKET_Packet_,)` */
/* "NDIS_GET_PACKET_STATUS" (aa447976): `NDIS_STATUS NDIS_GET_PACKET_STATUS(PNDIS_PACKET_Packet)` */
/* "NDIS_GET_PACKET_TIME_RECEIVED" (aa447977): `ULONGLONG NDIS_GET_PACKET_TIME_RECEIVED(PNDIS_PACKET_Packet)` */
/* "NDIS_GET_PACKET_TIME_SENT" (aa447978): `ULONGLONG NDIS_GET_PACKET_TIME_SENT(PNDIS_PACKET_Packet)` */
/* "NDIS_GET_PACKET_TIME_TO_SEND" (aa447979): `ULONGLONG NDIS_GET_PACKET_TIME_TO_SEND(PNDIS_PACKET_Packet)` */
/* "NDIS_INIT_FUNCTION" (aa448003): `VOID NDIS_INIT_FUNCTION(LPTSTR_F)` */
/* "TR_COMPARE_NETWORK_ADDRESSES" (aa448219): `VOID TR_COMPARE_NETWORK_ADDRESSES(PCHAR_A,PCHAR_B,PINT_Result)` */
/* "TR_COPY_NETWORK_ADDRESS" (aa448220): `VOID TR_COPY_NETWORK_ADDRESS(PCHAR_D,PCHAR_S)` */
/* "TR_IS_BROADCAST" (aa448221): `VOID TR_IS_BROADCAST(PUCHAR_Address,PBOOLEAN_Result)` */
/* "TR_IS_FUNCTIONAL" (aa448223): `VOID TR_IS_FUNCTIONAL(PUCHAR_Address,PBOOLEAN_Result)` */
/* "TR_IS_GROUP" (aa448224): `VOID TR_IS_GROUP(PUCHAR_Address,PBOOLEAN_Result)` */
/* "TR_IS_NOT_DIRECTED" (aa448225): `VOID TR_IS_NOT_DIRECTED(PUCHAR_Address,PBOOLEAN_Result)` */
/* "TR_IS_SOURCE_ROUTING" (aa448226): `VOID TR_IS_SOURCE_ROUTING(PUCHAR_Address,PBOOLEAN_Result)` */
/* "NDIS_OOB_DATA_FROM_PACKET" (ms904077): `PNDIS_PACKET_OOB_DATA NDIS_OOB_DATA_FROM_PACKET(PNDIS_PACKET_P)` */
/* "NDIS_PACKET_EXTENSION_FROM_PACKET" (ms904086): `PNDIS_PACKET_EXTENSION NDIS_PACKET_EXTENSION_FROM_PACKET(PNDIS_PACKET_P)` */
/* "NDIS_PER_PACKET_INFO_FROM_PACKET" (ms904091): `PVOID NDIS_PER_PACKET_INFO_FROM_PACKET(PNDIS_PACKET_P,NDIS_PER_PACKET_INFO_Id)` */
/* "NDIS_PHYSICAL_ADDRESS_CONST" (ms904093): `VOID NDIS_PHYSICAL_ADDRESS_CONST(ULONG _Low,LONG _High)` */
/* "NDIS_PROC" (ms904098): `typedefVOID (*NDIS_PROC) (struct _NDIS_WORK_ITEM *,PVOID)` */
/* "NDIS_SET_ORIGINAL_PACKET" (ms904964): `PNDIS_PACKET NDIS_SET_ORIGINAL_PACKET(PNDIS_PACKET_P,PNDIS_PACKET_OP)` */
/* "NDIS_SET_PACKET_CANCEL_ID" (ms904967): `ULONG_PTR NDIS_SET_PACKET_CANCEL_ID(PNDIS_PACKET _P,ULONG_PTR _cId)` */
/* "NDIS_SET_PACKET_HEADER_SIZE" (ms904969): `UINT NDIS_SET_PACKET_HEADER_SIZE(PNDIS_PACKET _Packet,UINT _HdrSize)` */
/* "NDIS_SET_PACKET_MEDIA_SPECIFIC_INFO" (ms904970): `VOID NDIS_SET_PACKET_MEDIA_SPECIFIC_INFO(PNDIS_PACKET_Packet,PVOID_MediaSpecificInfo,UINT_SizeMediaSpecificInfo)` */
/* "NDIS_SET_PACKET_STATUS" (ms904971): `NDIS_STATUS NDIS_SET_PACKET_STATUS(PNDIS_PACKET _Packet,NDIS_STATUS _Status)` */
/* "NDIS_SET_PACKET_TIME_RECEIVED" (ms904972): `#define NDIS_SET_PACKET_TIME_RECEIVED(_Packet, _TimeReceived) \ ((PNDIS_PACKET_OOB_DATA)((PUCHAR)(_Packet) + \ (_Packet)->Private.NdisPacketOobOffset))->TimeReceived = (_TimeReceived)` */
/* "NDIS_SET_PACKET_TIME_SENT" (ms904974): `ULONGLONG NDIS_SET_PACKET_TIME_SENT(PNDIS_PACKET _Packet,ULONGLONG _TimeSent)` */
/* "NDIS_SET_PACKET_TIME_TO_SEND" (ms904975): `ULONGLONG NDIS_SET_PACKET_TIME_TO_SEND(PNDIS_PACKET _Packet,ULONGLONG _TimeToSend)` */

/* --- Record-only: driver-supplied entry points (Ndis.h pages). - */
/* DriverEntry, the Protocol* callback set and the NDIS XXX_Init
 * stream-interface entry are implemented by the driver, not
 * imported; the pages document their required prototypes. */
/* "DriverEntry" (aa447730): `NDIS_STATUSDriverEntry(PVOIDArgument1,PVOIDArgument2)` */
/* "ProtocolBindAdapter" (ms919689): `VOID ProtocolBindAdapter(PNDIS_STATUSStatus,NDIS_HANDLEBindContext,PNDIS_STRINGDeviceName,PVOIDSystemSpecific1,PVOIDSystemSpecific2)` */
/* "ProtocolCloseAdapterComplete" (ms919691): `VOID ProtocolCloseAdapterComplete(NDIS_HANDLEProtocolBindingContext,NDIS_STATUSStatus)` */
/* "ProtocolOpenAdapterComplete" (ms919693): `VOID ProtocolOpenAdapterComplete(NDIS_HANDLEProtocolBindingContext,NDIS_STATUSStatus,NDIS_STATUSOpenErrorStatus)` */
/* "ProtocolPnPEvent" (ms919695): `NDIS_STATUS ProtocolPnPEvent(NDIS_HANDLEProtocolBindingContext,PNET_PNP_EVENT NetPnPEvent)` */
/* "ProtocolReceive" (ms919698): `NDIS_STATUS ProtocolReceive(NDIS_HANDLEProtocolBindingContext,NDIS_HANDLE MacReceiveContext,PVOIDpHeader,UINT HeaderSize,PVOID LookAheadBuffer,UINT LookAheadBufferSize,UINT PacketSize )` */
/* "ProtocolReceiveComplete" (ms919699): `VOID ProtocolReceiveComplete(NDIS_HANDLEProtocolBindingContext)` */
/* "ProtocolReceivePacket" (ms919702): `INTProtocolReceivePacket(NDIS_HANDLE ProtocolBindingContext,PNDIS_PACKETPacket)` */
/* "ProtocolRequestComplete" (ms919703): `VOID ProtocolRequestComplete(NDIS_HANDLEProtocolBindingContext,PNDIS_REQUESTNdisRequest,NDIS_STATUSStatus)` */
/* "ProtocolResetComplete" (ms919706): `VOID ProtocolResetComplete(NDIS_HANDLEProtocolBindingContext,NDIS_STATUSStatus)` */
/* "ProtocolSendComplete" (ms919707): `VOID ProtocolSendComplete(NDIS_HANDLE ProtocolBindingContext,PNDIS_PACKETPacket,NDIS_STATUSStatus)` */
/* "ProtocolStatus" (ms919710): `VOID ProtocolStatus(NDIS_HANDLEProtocolBindingContext,NDIS_STATUSGeneralStatus,PVOIDStatusBuffer,UINTStatusBufferSize)` */
/* "ProtocolStatusComplete" (ms919712): `VOID ProtocolStatusComplete(NDIS_HANDLEProtocolBindingContext)` */
/* "ProtocolTransferDataComplete" (ms919714): `VOID ProtocolTransferDataComplete(NDIS_HANDLEProtocolBindingContext,PNDIS_PACKETPacket,NDIS_STATUS Status,UINTBytesTransferred)` */
/* "ProtocolUnbindAdapter" (ms919717): `VOID ProtocolUnbindAdapter(PNDIS_STATUSStatus,NDIS_HANDLEProtocolBindingContext,NDIS_HANDLEUnbindContext)` */
/* "XXX_Init (NDIS)" (ms923698): `DWORDXXX_Init( DWORDdwContext)` */

/* ------------------------------------------------------------------
 * Book surface: drivers-network-rem (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ------------------------------------------------------------------
 * Book surface: drivers-network-rem (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms890411 802.1x Object Identifiers */
/* ms890420 802.1x Security */
/* ms890429 802.1x User Administration Issues */
/* ms890447 Accessing OOB Information */
/* ms895483 Adding a DllMain Entry Point to the NDIS Miniport Driver Core Functions */
/* ms895484 Adding an NDIS Miniport Driver to a Run-Time Image */
/* ms895482 Adding Debug Zones to the NDIS Miniport Driver Initialization Functions */
/* ms895485 Adding the Windows-based Desktop NDIS Miniport Driver to the Run-Time Image Build */
/* ms923761 Asynchronous Network I/O */
/* ms890616 AsyncMac Registry Settings */
/* ms890690 Authenticating 802.1x */
/* aa448300 Automatic Configuration Constants */
/* ms890698 Automatic Configuration Subsystem */
/* ms890770 Benefits of Media Sense */
/* ms890997 Built-in Network Adapters */
/* ms891031 Bus Master-DMA Network Adapters */
/* aa448268 CETK NDIS Test Pass Criteria */
/* ms891051 Choosing a Receive Function */
/* ms891059 Choosing a Send Function */
/* aa447428 Communication Class Interface */
/* ms895486 Conditionally Defining Power Management in the NDIS Miniport Driver Object Identifier Functions */
/* aa447429 Configuration Descriptor */
/* aa447432 Considerations For Improving NDIS Driver Performance */
/* aa447434 Control Channel Characteristics */
/* aa447437 Data Class Interface */
/* aa447438 Data In Endpoint Descriptor */
/* aa447439 Data Out Endpoint Descriptor */
/* aa447459 Design Considerations for a Network Performance Test */
/* aa447461 Device Descriptor */
/* ms890534 Evaluation of Network Performance Test Results */
/* ms895487 Filtering Local Variables in the NDIS Miniport Driver PhyDetect and SetupPhy Functions */
/* ms892158 General NDIS Objects */
/* aa448253 Implementing a Network Performance Test */
/* ms892218 Implementing a ProtocolReceive Handler */
/* ms892219 Implementing a ProtocolReceivePacket Handler */
/* ms892232 Initialization of NDIS Protocol Drivers */
/* ms892233 Initializing the NDIS Wrapper */
/* ms892236 Installable ISR Registry Settings */
/* ms892241 Interface Descriptor for Communication Class Interface */
/* ms892242 Interface Descriptor for Data Class Interface */
/* ms892464 IRDA Miniport Drivers */
/* ms892469 IrDA Network Adapters */
/* ms892473 Kernel Memory Allocated for Use by the Networking Stack */
/* ms892482 Kingston PCI NE2000 */
/* ms892487 Linksys ISA NE2000 */
/* ms892490 Media Sense Implementation */
/* ms892495 Miniport Driver Registry Settings */
/* ms892497 Miniport Operations */
/* ms892502 Multi-Packet Messages */
/* ms892505 NDIS Adapter Binding Management APIs */
/* ms892507 NDIS Assumptions for Media Sense Support */
/* aa447933 NDIS Debug */
/* ms892510 NDIS Driver Portability */
/* ms892512 NDIS Driver Upper-Edge Functions */
/* ms892513 NDIS Ethernet Objects */
/* ms892514 NDIS Events */
/* ms892516 NDIS IrDA Objects */
/* ms892517 NDIS Library Functions Used by WAN Miniport Drivers */
/* ms923730 NDIS Miniport Driver Implementation */
/* ms892518 NDIS Miniport Driver Samples */
/* ms892519 NDIS Network Wakeup Objects */
/* ms892521 NDIS Objects for WAN Miniports */
/* ms892522 NDIS Packet Structure */
/* ms892523 NDIS Plug and Play Support */
/* ms892524 NDIS Power Management Objects */
/* ms892525 NDIS Protocol Driver Lower-Edge Functions */
/* ms892526 NDIS Protocol Driver Registration */
/* ms892515 NDIS Support in Windows CE */
/* ms892529 NDIS TAPI Objects */
/* ms892530 NDIS Task Offload Objects */
/* ms892531 NDIS Timers */
/* ms892532 NDIS Token Ring Objects */
/* ms892538 NDIS Wake-on-LAN Support */
/* ms904106 NdisQuerySendFlags */
/* ms904978 NdisSetSendFlags */
/* ms892533 NDISUIO Binding and Unbinding */
/* ms892534 NDISUIO Driver Registration */
/* ms892536 NDISUIO Operations */
/* ms892540 Network Adapter Card Requirements */
/* ms892506 Network Driver Samples */
/* ms892543 Network Keys */
/* ms892544 NIC Instance Specific Registry Settings */
/* ms892547 Notification Endpoint Descriptor */
/* aa448124 OID_GEN_SUPPORTED_LIST */
/* ms919147 OID_TCP_TASK_OFFLOAD */
/* ms892553 Open System and Shared Key Authentication */
/* ms892552 Opening an Adapter Underlying a Protocol Driver */
/* ms892562 Passing Media-Specific Information */
/* aa447533 PC Card Network Adapters */
/* aa447544 PCI Bus Enumerator Template */
/* aa447545 PCMCIA-based Miniport Functional Interrupts */
/* aa447546 Performance Improvements for an NDIS Miniport Driver */
/* aa447562 Power Manager Requests and NDIS */
/* aa447553 Power-Manageable NDIS Miniports */
/* aa447577 Protocol Driver Query and Set */
/* aa447578 Protocol Driver Reset Operations */
/* aa447581 Protocol Driver Unbinding Operations */
/* aa447583 Querying WAN Miniport Driver Information */
/* aa447586 Registering a CheckForHang Handler */
/* aa447587 Registering as a WAN Miniport Driver */
/* aa447593 Remote NDIS Objects */
/* aa447594 Remote NDIS Packet Message */
/* ms895504 Removing DMA Support from the NDIS Miniport Driver Initialization Functions */
/* ms895505 Removing DMA Support From the NDIS Miniport Driver Send and Receive Functions */
/* ms895506 Removing Unused Local Variables from the NDIS Miniport Driver Core Functions */
/* ms895507 Removing WMI Support From the NDIS Miniport Driver Object Identifier Functions */
/* aa447600 Reusing Packets */
/* aa447602 RNDIS Control Messages */
/* aa447604 RNDIS Device Architecture */
/* aa447605 RNDIS Device Control */
/* aa447607 RNDIS Ethernet Objects */
/* aa447608 RNDIS Ethernet Statistics Objects */
/* aa447609 RNDIS General Objects */
/* aa447610 RNDIS General Statistics Objects */
/* aa447612 RNDIS Network Wakeup Objects */
/* aa447614 RNDIS Power Management Objects */
/* aa447615 RNDIS Registry Settings */
/* aa447616 RNDIS Status Values */
/* aa447618 RNDIS Version */
/* aa448282 Running Performance Tests for NDIS Miniport Drivers */
/* aa448281 Running the One-Card NDIS Test */
/* aa448283 Running the Two-Card in Two Machines NDIS Test for Media Sense */
/* aa448284 Running the Two-Card NDIS Test */
/* aa448285 Running the Winsock Stress Test */
/* ms894012 Sending on a WAN Miniport Driver */
/* ms894021 Shared IST for NDIS */
/* ms894024 Simultaneous Access for Multiple Applications */
/* ms894034 Spin Locks */
/* ms894046 Subordinate DMA Network Adapters */
/* ms894066 Token Ring Miniport Drivers */
/* ms894076 USB Configuration Descriptor */
/* ms894077 USB Device Descriptor */
/* ms894718 USB Short Packets */
/* ms894176 USB-Level Termination */
/* ms894362 USB-RNDIS Flow Control */
/* ms894365 USB-RNDIS Power Management */
/* ms894736 WAN Miniport Driver Indications */
/* ms894751 Windows CE Communications Architecture */
/* ms894759 Wireless Network Client Configuration */
/* ------------------------------------------------------------------
 * Book surface: ndis (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ------------------------------------------------------------------
 * Book surface: ndis (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms894762 802.11 Wireless LAN Object Identifiers */
/* aa448300 Automatic Configuration Constants */
/* ms894771 Automatic Configuration Functions */
/* aa448301 Automatic Configuration Reference */
/* aa448297 Automatic Configuration Structures */
/* ms894877 Ethernet Object Identifiers */
/* ms894880 General Object Identifiers */
/* ms894947 IrDA Object Identifiers */
/* ms894959 NDIS Data Types */
/* ms894961 NDIS Library Functions */
/* ms895357 NDIS Lower-Edge Functions */
/* ms895360 NDIS Messages */
/* ms895365 NDIS Structures */
/* ms895373 NDIS Upper-Edge Functions */
/* ms904106 NdisQuerySendFlags */
/* ms904978 NdisSetSendFlags */
/* ms895367 NDISTAPI Object Identifiers */
/* ms895377 NDISWAN Object Identifiers */
/* ms895383 Network Driver Data Types */
/* ms895388 Network Driver Enumerations */
/* ms895392 Network Driver Functions */
/* ms895397 Network Driver IOCTLs */
/* ms895401 Network Driver Macros */
/* ms895405 Network Driver Messages */
/* ms895411 Network Driver Object Identifiers */
/* ms895419 Network Driver Structures */
/* aa448124 OID_GEN_SUPPORTED_LIST */
/* ms919147 OID_TCP_TASK_OFFLOAD */
/* ms895435 Plug and Play and Power Management Object Identifiers */
/* ms895446 Remote NDIS Data Types */
/* ms895447 Remote NDIS Functions */
/* ms895448 Remote NDIS Messages */
/* ms895449 Remote NDIS Structures */
/* ms895461 Task Offload Object Identifiers */
/* ms895466 Token Ring Object Identifiers */
/* ------------------------------------------------------------------
 * Book surface: drivers-network-rem (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ------------------------------------------------------------------
 * Book surface: drivers-network-rem (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms890411 802.1x Object Identifiers */
/* ms890420 802.1x Security */
/* ms890429 802.1x User Administration Issues */
/* ms890447 Accessing OOB Information */
/* ms895483 Adding a DllMain Entry Point to the NDIS Miniport Driver Core Functions */
/* ms895484 Adding an NDIS Miniport Driver to a Run-Time Image */
/* ms895482 Adding Debug Zones to the NDIS Miniport Driver Initialization Functions */
/* ms895485 Adding the Windows-based Desktop NDIS Miniport Driver to the Run-Time Image Build */
/* ms923761 Asynchronous Network I/O */
/* ms890616 AsyncMac Registry Settings */
/* ms890690 Authenticating 802.1x */
/* aa448300 Automatic Configuration Constants */
/* ms890698 Automatic Configuration Subsystem */
/* ms890770 Benefits of Media Sense */
/* ms890997 Built-in Network Adapters */
/* ms891031 Bus Master-DMA Network Adapters */
/* aa448268 CETK NDIS Test Pass Criteria */
/* ms891051 Choosing a Receive Function */
/* ms891059 Choosing a Send Function */
/* aa447428 Communication Class Interface */
/* ms895486 Conditionally Defining Power Management in the NDIS Miniport Driver Object Identifier Functions */
/* aa447429 Configuration Descriptor */
/* aa447432 Considerations For Improving NDIS Driver Performance */
/* aa447434 Control Channel Characteristics */
/* aa447437 Data Class Interface */
/* aa447438 Data In Endpoint Descriptor */
/* aa447439 Data Out Endpoint Descriptor */
/* aa447459 Design Considerations for a Network Performance Test */
/* aa447461 Device Descriptor */
/* ms890534 Evaluation of Network Performance Test Results */
/* ms895487 Filtering Local Variables in the NDIS Miniport Driver PhyDetect and SetupPhy Functions */
/* ms892158 General NDIS Objects */
/* aa448253 Implementing a Network Performance Test */
/* ms892218 Implementing a ProtocolReceive Handler */
/* ms892219 Implementing a ProtocolReceivePacket Handler */
/* ms892232 Initialization of NDIS Protocol Drivers */
/* ms892233 Initializing the NDIS Wrapper */
/* ms892236 Installable ISR Registry Settings */
/* ms892241 Interface Descriptor for Communication Class Interface */
/* ms892242 Interface Descriptor for Data Class Interface */
/* ms892464 IRDA Miniport Drivers */
/* ms892469 IrDA Network Adapters */
/* ms892473 Kernel Memory Allocated for Use by the Networking Stack */
/* ms892482 Kingston PCI NE2000 */
/* ms892487 Linksys ISA NE2000 */
/* ms892490 Media Sense Implementation */
/* ms892495 Miniport Driver Registry Settings */
/* ms892497 Miniport Operations */
/* ms892502 Multi-Packet Messages */
/* ms892505 NDIS Adapter Binding Management APIs */
/* ms892507 NDIS Assumptions for Media Sense Support */
/* aa447933 NDIS Debug */
/* ms892510 NDIS Driver Portability */
/* ms892512 NDIS Driver Upper-Edge Functions */
/* ms892513 NDIS Ethernet Objects */
/* ms892514 NDIS Events */
/* ms892516 NDIS IrDA Objects */
/* ms892517 NDIS Library Functions Used by WAN Miniport Drivers */
/* ms923730 NDIS Miniport Driver Implementation */
/* ms892518 NDIS Miniport Driver Samples */
/* ms892519 NDIS Network Wakeup Objects */
/* ms892521 NDIS Objects for WAN Miniports */
/* ms892522 NDIS Packet Structure */
/* ms892523 NDIS Plug and Play Support */
/* ms892524 NDIS Power Management Objects */
/* ms892525 NDIS Protocol Driver Lower-Edge Functions */
/* ms892526 NDIS Protocol Driver Registration */
/* ms892515 NDIS Support in Windows CE */
/* ms892529 NDIS TAPI Objects */
/* ms892530 NDIS Task Offload Objects */
/* ms892531 NDIS Timers */
/* ms892532 NDIS Token Ring Objects */
/* ms892538 NDIS Wake-on-LAN Support */
/* ms904106 NdisQuerySendFlags */
/* ms904978 NdisSetSendFlags */
/* ms892533 NDISUIO Binding and Unbinding */
/* ms892534 NDISUIO Driver Registration */
/* ms892536 NDISUIO Operations */
/* ms892540 Network Adapter Card Requirements */
/* ms892506 Network Driver Samples */
/* ms892543 Network Keys */
/* ms892544 NIC Instance Specific Registry Settings */
/* ms892547 Notification Endpoint Descriptor */
/* aa448124 OID_GEN_SUPPORTED_LIST */
/* ms919147 OID_TCP_TASK_OFFLOAD */
/* ms892553 Open System and Shared Key Authentication */
/* ms892552 Opening an Adapter Underlying a Protocol Driver */
/* ms892562 Passing Media-Specific Information */
/* aa447533 PC Card Network Adapters */
/* aa447544 PCI Bus Enumerator Template */
/* aa447545 PCMCIA-based Miniport Functional Interrupts */
/* aa447546 Performance Improvements for an NDIS Miniport Driver */
/* aa447562 Power Manager Requests and NDIS */
/* aa447553 Power-Manageable NDIS Miniports */
/* aa447577 Protocol Driver Query and Set */
/* aa447578 Protocol Driver Reset Operations */
/* aa447581 Protocol Driver Unbinding Operations */
/* aa447583 Querying WAN Miniport Driver Information */
/* aa447586 Registering a CheckForHang Handler */
/* aa447587 Registering as a WAN Miniport Driver */
/* aa447593 Remote NDIS Objects */
/* aa447594 Remote NDIS Packet Message */
/* ms895504 Removing DMA Support from the NDIS Miniport Driver Initialization Functions */
/* ms895505 Removing DMA Support From the NDIS Miniport Driver Send and Receive Functions */
/* ms895506 Removing Unused Local Variables from the NDIS Miniport Driver Core Functions */
/* ms895507 Removing WMI Support From the NDIS Miniport Driver Object Identifier Functions */
/* aa447600 Reusing Packets */
/* aa447602 RNDIS Control Messages */
/* aa447604 RNDIS Device Architecture */
/* aa447605 RNDIS Device Control */
/* aa447607 RNDIS Ethernet Objects */
/* aa447608 RNDIS Ethernet Statistics Objects */
/* aa447609 RNDIS General Objects */
/* aa447610 RNDIS General Statistics Objects */
/* aa447612 RNDIS Network Wakeup Objects */
/* aa447614 RNDIS Power Management Objects */
/* aa447615 RNDIS Registry Settings */
/* aa447616 RNDIS Status Values */
/* aa447618 RNDIS Version */
/* aa448282 Running Performance Tests for NDIS Miniport Drivers */
/* aa448281 Running the One-Card NDIS Test */
/* aa448283 Running the Two-Card in Two Machines NDIS Test for Media Sense */
/* aa448284 Running the Two-Card NDIS Test */
/* aa448285 Running the Winsock Stress Test */
/* ms894012 Sending on a WAN Miniport Driver */
/* ms894021 Shared IST for NDIS */
/* ms894024 Simultaneous Access for Multiple Applications */
/* ms894034 Spin Locks */
/* ms894046 Subordinate DMA Network Adapters */
/* ms894066 Token Ring Miniport Drivers */
/* ms894076 USB Configuration Descriptor */
/* ms894077 USB Device Descriptor */
/* ms894718 USB Short Packets */
/* ms894176 USB-Level Termination */
/* ms894362 USB-RNDIS Flow Control */
/* ms894365 USB-RNDIS Power Management */
/* ms894736 WAN Miniport Driver Indications */
/* ms894751 Windows CE Communications Architecture */
/* ms894759 Wireless Network Client Configuration */
/* ------------------------------------------------------------------
 * Book surface: drivers-network-rem (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms901396 IOCTL_NDIS_BIND_ADAPTER: documented name-only (no value published; held) */
/* ms901397 IOCTL_NDIS_DEREGISTER_ADAPTER: documented name-only (no value published; held) */
/* ms901398 IOCTL_NDIS_GET_ADAPTER_BINDINGS: documented name-only (no value published; held) */
/* ms901399 IOCTL_NDIS_GET_ADAPTER_NAMES: documented name-only (no value published; held) */
/* ms901401 IOCTL_NDIS_GET_PROTOCOL_NAMES: documented name-only (no value published; held) */
/* ms901402 IOCTL_NDIS_LOAD_MINIPORT: documented name-only (no value published; held) */
/* ms901403 IOCTL_NDIS_REBIND_ADAPTER: documented name-only (no value published; held) */
/* ms901404 IOCTL_NDIS_REGISTER_ADAPTER: documented name-only (no value published; held) */
/* ms901414 IOCTL_NDIS_UNBIND_ADAPTER: documented name-only (no value published; held) */
/* ms919162 OID_WAN_GET_COMP_INFO: documented name-only (no value published; held) */
/* ms919169 OID_WAN_GET_INFO: documented name-only (no value published; held) */
/* ms919178 OID_WAN_GET_LINK_INFO: documented name-only (no value published; held) */
/* ms919186 OID_WAN_GET_STATS_INFO: documented name-only (no value published; held) */
/* ms919200 OID_WAN_LINE_COUNT: documented name-only (no value published; held) */
/* ms919221 OID_WAN_SET_COMP_INFO: documented name-only (no value published; held) */
/* ms919233 OID_WAN_SET_LINK_INFO: documented name-only (no value published; held) */
/* ------------------------------------------------------------------
 * Book surface: drivers-network-rem (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms890411 802.1x Object Identifiers */
/* ms890420 802.1x Security */
/* ms890429 802.1x User Administration Issues */
/* ms890447 Accessing OOB Information */
/* ms895483 Adding a DllMain Entry Point to the NDIS Miniport Driver Core Functions */
/* ms895484 Adding an NDIS Miniport Driver to a Run-Time Image */
/* ms895482 Adding Debug Zones to the NDIS Miniport Driver Initialization Functions */
/* ms895485 Adding the Windows-based Desktop NDIS Miniport Driver to the Run-Time Image Build */
/* ms923761 Asynchronous Network I/O */
/* ms890616 AsyncMac Registry Settings */
/* ms890690 Authenticating 802.1x */
/* aa448300 Automatic Configuration Constants */
/* ms890698 Automatic Configuration Subsystem */
/* ms890770 Benefits of Media Sense */
/* ms890997 Built-in Network Adapters */
/* ms891031 Bus Master-DMA Network Adapters */
/* aa448268 CETK NDIS Test Pass Criteria */
/* ms891051 Choosing a Receive Function */
/* ms891059 Choosing a Send Function */
/* aa447428 Communication Class Interface */
/* ms895486 Conditionally Defining Power Management in the NDIS Miniport Driver Object Identifier Functions */
/* aa447429 Configuration Descriptor */
/* aa447432 Considerations For Improving NDIS Driver Performance */
/* aa447434 Control Channel Characteristics */
/* aa447437 Data Class Interface */
/* aa447438 Data In Endpoint Descriptor */
/* aa447439 Data Out Endpoint Descriptor */
/* aa447459 Design Considerations for a Network Performance Test */
/* aa447461 Device Descriptor */
/* ms890534 Evaluation of Network Performance Test Results */
/* ms895487 Filtering Local Variables in the NDIS Miniport Driver PhyDetect and SetupPhy Functions */
/* ms892158 General NDIS Objects */
/* aa448253 Implementing a Network Performance Test */
/* ms892218 Implementing a ProtocolReceive Handler */
/* ms892219 Implementing a ProtocolReceivePacket Handler */
/* ms892232 Initialization of NDIS Protocol Drivers */
/* ms892233 Initializing the NDIS Wrapper */
/* ms892236 Installable ISR Registry Settings */
/* ms892241 Interface Descriptor for Communication Class Interface */
/* ms892242 Interface Descriptor for Data Class Interface */
/* ms892464 IRDA Miniport Drivers */
/* ms892469 IrDA Network Adapters */
/* ms892473 Kernel Memory Allocated for Use by the Networking Stack */
/* ms892482 Kingston PCI NE2000 */
/* ms892487 Linksys ISA NE2000 */
/* ms892490 Media Sense Implementation */
/* ms892495 Miniport Driver Registry Settings */
/* ms892497 Miniport Operations */
/* ms892502 Multi-Packet Messages */
/* ms892505 NDIS Adapter Binding Management APIs */
/* ms892507 NDIS Assumptions for Media Sense Support */
/* aa447933 NDIS Debug */
/* ms892510 NDIS Driver Portability */
/* ms892512 NDIS Driver Upper-Edge Functions */
/* ms892513 NDIS Ethernet Objects */
/* ms892514 NDIS Events */
/* ms892516 NDIS IrDA Objects */
/* ms892517 NDIS Library Functions Used by WAN Miniport Drivers */
/* ms923730 NDIS Miniport Driver Implementation */
/* ms892518 NDIS Miniport Driver Samples */
/* ms892519 NDIS Network Wakeup Objects */
/* ms892521 NDIS Objects for WAN Miniports */
/* ms892522 NDIS Packet Structure */
/* ms892523 NDIS Plug and Play Support */
/* ms892524 NDIS Power Management Objects */
/* ms892525 NDIS Protocol Driver Lower-Edge Functions */
/* ms892526 NDIS Protocol Driver Registration */
/* ms892515 NDIS Support in Windows CE */
/* ms892529 NDIS TAPI Objects */
/* ms892530 NDIS Task Offload Objects */
/* ms892531 NDIS Timers */
/* ms892532 NDIS Token Ring Objects */
/* ms892538 NDIS Wake-on-LAN Support */
/* ms904106 NdisQuerySendFlags */
/* ms904978 NdisSetSendFlags */
/* ms892533 NDISUIO Binding and Unbinding */
/* ms892534 NDISUIO Driver Registration */
/* ms892536 NDISUIO Operations */
/* ms892540 Network Adapter Card Requirements */
/* ms892506 Network Driver Samples */
/* ms892543 Network Keys */
/* ms892544 NIC Instance Specific Registry Settings */
/* ms892547 Notification Endpoint Descriptor */
/* aa448124 OID_GEN_SUPPORTED_LIST */
/* ms919147 OID_TCP_TASK_OFFLOAD */
/* ms892553 Open System and Shared Key Authentication */
/* ms892552 Opening an Adapter Underlying a Protocol Driver */
/* ms892562 Passing Media-Specific Information */
/* aa447533 PC Card Network Adapters */
/* aa447544 PCI Bus Enumerator Template */
/* aa447545 PCMCIA-based Miniport Functional Interrupts */
/* aa447546 Performance Improvements for an NDIS Miniport Driver */
/* aa447562 Power Manager Requests and NDIS */
/* aa447553 Power-Manageable NDIS Miniports */
/* aa447577 Protocol Driver Query and Set */
/* aa447578 Protocol Driver Reset Operations */
/* aa447581 Protocol Driver Unbinding Operations */
/* aa447583 Querying WAN Miniport Driver Information */
/* aa447586 Registering a CheckForHang Handler */
/* aa447587 Registering as a WAN Miniport Driver */
/* aa447593 Remote NDIS Objects */
/* aa447594 Remote NDIS Packet Message */
/* ms895504 Removing DMA Support from the NDIS Miniport Driver Initialization Functions */
/* ms895505 Removing DMA Support From the NDIS Miniport Driver Send and Receive Functions */
/* ms895506 Removing Unused Local Variables from the NDIS Miniport Driver Core Functions */
/* ms895507 Removing WMI Support From the NDIS Miniport Driver Object Identifier Functions */
/* aa447600 Reusing Packets */
/* aa447602 RNDIS Control Messages */
/* aa447604 RNDIS Device Architecture */
/* aa447605 RNDIS Device Control */
/* aa447607 RNDIS Ethernet Objects */
/* aa447608 RNDIS Ethernet Statistics Objects */
/* aa447609 RNDIS General Objects */
/* aa447610 RNDIS General Statistics Objects */
/* aa447612 RNDIS Network Wakeup Objects */
/* aa447614 RNDIS Power Management Objects */
/* aa447615 RNDIS Registry Settings */
/* aa447616 RNDIS Status Values */
/* aa447618 RNDIS Version */
/* aa448282 Running Performance Tests for NDIS Miniport Drivers */
/* aa448281 Running the One-Card NDIS Test */
/* aa448283 Running the Two-Card in Two Machines NDIS Test for Media Sense */
/* aa448284 Running the Two-Card NDIS Test */
/* aa448285 Running the Winsock Stress Test */
/* ms894012 Sending on a WAN Miniport Driver */
/* ms894021 Shared IST for NDIS */
/* ms894024 Simultaneous Access for Multiple Applications */
/* ms894034 Spin Locks */
/* ms894046 Subordinate DMA Network Adapters */
/* ms894066 Token Ring Miniport Drivers */
/* ms894076 USB Configuration Descriptor */
/* ms894077 USB Device Descriptor */
/* ms894718 USB Short Packets */
/* ms894176 USB-Level Termination */
/* ms894362 USB-RNDIS Flow Control */
/* ms894365 USB-RNDIS Power Management */
/* ms894736 WAN Miniport Driver Indications */
/* ms894751 Windows CE Communications Architecture */
/* ms894759 Wireless Network Client Configuration */
/* ------------------------------------------------------------------
 * Book surface: ndis (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms894762 802.11 Wireless LAN Object Identifiers */
/* aa448300 Automatic Configuration Constants */
/* ms894771 Automatic Configuration Functions */
/* aa448301 Automatic Configuration Reference */
/* aa448297 Automatic Configuration Structures */
/* ms894877 Ethernet Object Identifiers */
/* ms894880 General Object Identifiers */
/* ms894947 IrDA Object Identifiers */
/* ms894959 NDIS Data Types */
/* ms894961 NDIS Library Functions */
/* ms895357 NDIS Lower-Edge Functions */
/* ms895360 NDIS Messages */
/* ms895365 NDIS Structures */
/* ms895373 NDIS Upper-Edge Functions */
/* ms904106 NdisQuerySendFlags */
/* ms904978 NdisSetSendFlags */
/* ms895367 NDISTAPI Object Identifiers */
/* ms895377 NDISWAN Object Identifiers */
/* ms895383 Network Driver Data Types */
/* ms895388 Network Driver Enumerations */
/* ms895392 Network Driver Functions */
/* ms895397 Network Driver IOCTLs */
/* ms895401 Network Driver Macros */
/* ms895405 Network Driver Messages */
/* ms895411 Network Driver Object Identifiers */
/* ms895419 Network Driver Structures */
/* aa448124 OID_GEN_SUPPORTED_LIST */
/* ms919147 OID_TCP_TASK_OFFLOAD */
/* ms895435 Plug and Play and Power Management Object Identifiers */
/* ms895446 Remote NDIS Data Types */
/* ms895447 Remote NDIS Functions */
/* ms895448 Remote NDIS Messages */
/* ms895449 Remote NDIS Structures */
/* ms895461 Task Offload Object Identifiers */
/* ms895466 Token Ring Object Identifiers */
#endif /* AKARI_NDIS_H */
