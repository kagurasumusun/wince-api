/* Winsock2.h -- Windows Sockets (Winsock 2.2) for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * M39: core Winsock surface of the official CE "Windows Sockets
 * Reference" book (Windows CE 5.0 archive, (v=msdn.10)): the Winsock
 * 1.1 socket functions, the WSA core functions, the socket
 * structures, and the constants the official pages document.
 *
 * Evidence model (clean room):
 *
 *  (a) every prototype, structure layout, member name and parameter
 *      name is transcribed from the official CE 5.0 documentation
 *      pages (107 pages; the per-page record is
 *      docs/inventory.md (M39 section)).  The CE 5.0 archive strips
 *      whitespace inside some code blocks; for the five pages whose
 *      prototype could not be spaced unambiguously (WSAStartup,
 *      WSASocket, WSASetEvent, WSASetLastError, WSASetService) the
 *      official Windows CE 6.0 twin pages are used, the same
 *      documented-twin procedure as M27.
 *
 *  (b) numeric constant values are taken from official pages that
 *      print them: the Win32 socket()/shutdown()/WSASocket()/
 *      ADDRINFOA/WSAPROTOCOL_INFO/WSADATA/fd_set reference tables
 *      (AF_*, SOCK_*, IPPROTO_TCP/UDP, SD_*, WSA_FLAG_*, SG_*,
 *      AI_*, WSADESCRIPTION_LEN, WSAPROTOCOL_LEN, FD_SETSIZE,
 *      SO_KEEPALIVE, SO_CONDITIONAL_ACCEPT), the IANA protocol
 *      numbers registry (IPPROTO_IP 0 / IPPROTO_IPV6 41), and the
 *      official "Windows Sockets Error Codes" table (all WSAE*
 *      values).  The CE pages name the constants but do not print
 *      numeric values; the documented values above are the Winsock
 *      2.2 ABI that the CE Ws2.dll implements (Winsock 2.2 per the
 *      official ws2 Module page).
 *
 *  (c) three values are NOT published by any official page found
 *      (the CE pages reference the constant but no official page
 *      prints a number): WSASYS_STATUS_LEN, FD_MAX_EVENTS and
 *      MAX_PROTOCOL_CHAIN.  The structures that embed them
 *      (WSADATA, WSANETWORKEVENTS, WSAPROTOCOLCHAIN) must be
 *      complete, so the values below are flagged design decisions;
 *      an on-device Ws2.dll cross-check is required before relying
 *      on the affected members.  Every other constant whose value
 *      is not officially published (SOL_SOCKET -- SOL_IRLMP now has
 *      its R1 value (see the M96 adoption below; R1 af_irda.h is
 *      public domain, not a README exception file) -- the
 *      remaining SO_ options, the FD_ event bits, MSG_ flags, the
 *      FIO and SIO ioctl codes, CF_ constants, SOMAXCONN,
 *      PVD_CONFIG) is deliberately NOT defined; the gap list is
 *      docs/inventory.md (M39 section).
 *
 *  The CE pages print FAR pointer qualifiers (a Winsock 1.1 /
 *  16-bit relic).  Windows CE has a single 32-bit flat address
 *  model, so FAR is a no-op; the declarations below use plain
 *  pointers (documented design decision, see inventory).
 */

#ifndef _WINSOCK2_H
#define _WINSOCK2_H

#include "Windef.h"   /* DWORD, BOOL, WORD, HANDLE, LPVOID, LPINT, LPDWORD, MAKEWORD */
#include "Winnt.h"    /* GUID (WSAPROTOCOL_INFO.ProviderId) */

/* The CE pages print some WSA prototypes with the WSAAPI calling
 * convention.  Windows CE has one undecorated calling convention,
 * so WSAAPI is empty exactly like WINAPI in windef.h. */
#define WSAAPI  WINAPI

/* ------------------------------------------------------------------ */
/* Basic types                                                         */
/* ------------------------------------------------------------------ */

/* Winsock 1.1 unsigned types, named by the CE prototypes
 * (htonl/htons/ntohl/ntohs, sockaddr, fd_set, in_addr, ...). */
typedef unsigned char  u_char;
typedef unsigned short u_short;
typedef unsigned int   u_int;
typedef unsigned long  u_long;

/* Socket descriptor.  The official "Socket Data Type" page: "Because
 * the SOCKET type is unsigned ..." and a handle "may take any value
 * in the range 0 to INVALID_SOCKET-1" -> INVALID_SOCKET is the
 * largest representable unsigned value (documented derivation). */
typedef unsigned int   SOCKET;
#define INVALID_SOCKET ((SOCKET)(~0u))
#define SOCKET_ERROR   (-1)

/* socklen_t: address-length parameter type named by the CE
 * getnameinfo prototype; a 32-bit int in the CE ABI. */
typedef int socklen_t;

/* QOS: the CE WSAConnect/WSAJoinLeaf pages mark lpSQOS/lpGQOS
 * "Reserved" (the CE service provider does not support
 * connection-time QoS), so an opaque type is the documented form;
 * callers pass NULL. */
typedef struct QOS QOS;
typedef QOS *LPQOS;

/* WSA event object: the CE WSAEventSelect/WSACreateEvent pages call
 * it "a handle identifying the event object". */
typedef HANDLE WSAEVENT;
typedef WSAEVENT *LPWSAEVENT;

/* Socket-group identifier passed to WSASocket/WSAJoinLeaf.  The CE
 * WSASocket page: "g ... Group ID - For Winsock, this must be
 * zero."  The carrier type is DWORD (documented design decision). */
typedef DWORD GROUP;

/* ------------------------------------------------------------------ */
/* Version encoding                                                    */
/* ------------------------------------------------------------------ */

/* The CE WSAStartup page, wVersionRequested parameter: "The
 * high-order byte specifies the minor version (revision) number; the
 * low-order byte specifies the major version number", with the
 * documented example wVersionRequested = MAKEWORD( 2, 2 ) (Winsock
 * 2.2). */
#define WSAVersion(major, minor)  MAKEWORD(minor, major)

/* ------------------------------------------------------------------ */
/* Length constants                                                    */
/* ------------------------------------------------------------------ */

/* WSADATA page (ms898735): szDescription holds "text (up to 256
 * characters in length)".  (c)-flagged: the CE page references
 * WSASYS_STATUS_LEN without a published value; the WSADATA layout is
 * kept complete with the flagged value 128. */
#define WSADESCRIPTION_LEN  256
#define WSASYS_STATUS_LEN   128   /* (c) value not officially published */

/* WSAPROTOCOL_INFO page (ms898760): "The maximum number of
 * characters allowed is WSAPROTOCOL_LEN, which is defined to be
 * 255." */
#define WSAPROTOCOL_LEN     255

/* fd_set page (aa450370): "The variable FD_SETSIZE defaults to 64." */
#define FD_SETSIZE          64

/* (c)-flagged: the WSANETWORKEVENTS page (ms898754) references
 * FD_MAX_EVENTS without a published value; 16 covers every
 * documented FD_ event (6 standard + 2 CE extensions) with room. */
#define FD_MAX_EVENTS       16

/* (c)-flagged: the WSAPROTOCOLCHAIN page (ms898759) references
 * MAX_PROTOCOL_CHAIN without a published value; 7 is the flagged
 * depth of the Winsock 2.2 provider chain. */
#define MAX_PROTOCOL_CHAIN  7

/* ------------------------------------------------------------------ */
/* Address families, socket types, protocols                           */
/* ------------------------------------------------------------------ */

/* Names documented by the CE socket() page (aa450958) and the
 * sockaddr/sockaddr_in/sockaddr_in6 pages; values from the official
 * Win32 socket() reference tables and the IANA protocol numbers
 * registry (TCP 6 / UDP 17 agree with the socket() table). */
#define AF_UNSPEC      0
#define AF_INET        2
#define AF_INET6       23

#define SOCK_STREAM    1
#define SOCK_DGRAM     2
#define SOCK_RAW       3

#define IPPROTO_IP     0
#define IPPROTO_TCP    6
#define IPPROTO_UDP    17
#define IPPROTO_IPV6   41

/* ------------------------------------------------------------------ */
/* shutdown() how flags                                                */
/* ------------------------------------------------------------------ */

/* Official shutdown() reference table (winsock2.h naming; the CE
 * shutdown page (aa450939) documents the how parameter without
 * printing the constant names). */
#define SD_RECEIVE  0
#define SD_SEND     1
#define SD_BOTH     2

/* ------------------------------------------------------------------ */
/* getaddrinfo() ai_flags                                              */
/* ------------------------------------------------------------------ */

/* Named by the CE addrinfo page (aa450282); values from the
 * official ADDRINFOA reference table. */
#define AI_PASSIVE      0x01
#define AI_CANONNAME    0x02
#define AI_NUMERICHOST  0x04

/* ------------------------------------------------------------------ */
/* WSASocket() creation flags and socket-group IDs                     */
/* ------------------------------------------------------------------ */

/* Official WSASocket() reference table; the CE WSASocket page
 * (ms898773) documents dwFlags and g. */
#define WSA_FLAG_OVERLAPPED               0x01
#define WSA_FLAG_MULTIPOINT_C_ROOT        0x02
#define WSA_FLAG_MULTIPOINT_C_LEAF        0x04
#define WSA_FLAG_MULTIPOINT_D_ROOT        0x08
#define WSA_FLAG_MULTIPOINT_D_LEAF        0x10
#define WSA_FLAG_ACCESS_SYSTEM_SECURITY   0x40
#define WSA_FLAG_NO_HANDLE_INHERIT        0x80

#define SG_UNCONSTRAINED_GROUP  0x01
#define SG_CONSTRAINED_GROUP    0x02

/* ------------------------------------------------------------------ */
/* Socket options with officially published values                     */
/* ------------------------------------------------------------------ */

/* The CE SOL_SOCKET page (ms884940) names the option; the official
 * SO_KEEPALIVE / SO_CONDITIONAL_ACCEPT pages publish the value. */
#define SO_KEEPALIVE           0x0008
#define SO_CONDITIONAL_ACCEPT  0x3002

/* ------------------------------------------------------------------ */
/* Windows Sockets error codes                                         */
/* ------------------------------------------------------------------ */

/* Official "Windows Sockets Error Codes" table (Winsock 2.2).  The
 * CE pages reference these codes throughout their Return Values
 * tables (see inventory for the per-page name list). */
#define WSABASEERR                 10000
#define WSAEINTR                   10004
#define WSAEBADF                   10009
#define WSAEACCES                  10013
#define WSAEFAULT                  10014
#define WSAEINVAL                  10022
#define WSAEMFILE                  10024
#define WSAEWOULDBLOCK             10035
#define WSAEINPROGRESS             10036
#define WSAEALREADY                10037
#define WSAENOTSOCK                10038
#define WSAEDESTADDRREQ            10039
#define WSAEMSGSIZE                10040
#define WSAEPROTOTYPE              10041
#define WSAENOPROTOOPT             10042
#define WSAEPROTONOSUPPORT         10043
#define WSAESOCKTNOSUPPORT         10044
#define WSAEOPNOTSUPP              10045
#define WSAEPFNOSUPPORT            10046
#define WSAEAFNOSUPPORT            10047
#define WSAEADDRINUSE              10048
#define WSAEADDRNOTAVAIL           10049
#define WSAENETDOWN                10050
#define WSAENETUNREACH             10051
#define WSAENETRESET               10052
#define WSAECONNABORTED            10053
#define WSAECONNRESET              10054
#define WSAENOBUFS                 10055
#define WSAEISCONN                 10056
#define WSAENOTCONN                10057
#define WSAESHUTDOWN               10058
#define WSAETOOMANYREFS            10059
#define WSAETIMEDOUT               10060
#define WSAECONNREFUSED            10061
#define WSAELOOP                   10062
#define WSAENAMETOOLONG            10063
#define WSAEHOSTDOWN               10064
#define WSAEHOSTUNREACH            10065
#define WSAENOTEMPTY               10066
#define WSAEPROCLIM                10067
#define WSAEUSERS                  10068
#define WSAEDQUOT                  10069
#define WSAESTALE                  10070
#define WSAEREMOTE                 10071
#define WSASYSNOTREADY             10091
#define WSAVERNOTSUPPORTED         10092
#define WSANOTINITIALISED          10093
#define WSAEDISCON                 10101
#define WSAENOMORE                 10102
#define WSAECANCELLED              10103
#define WSAEINVALIDPROCTABLE       10104
#define WSAEINVALIDPROVIDER        10105
#define WSAEPROVIDERFAILEDINIT     10106
#define WSASYSCALLFAILURE          10107
#define WSASERVICE_NOT_FOUND       10108
#define WSATYPE_NOT_FOUND          10109
#define WSA_E_NO_MORE              10110
#define WSA_E_CANCELLED            10111
#define WSAEREFUSED                10112
#define WSAHOST_NOT_FOUND          11001
#define WSATRY_AGAIN               11002
#define WSANO_RECOVERY             11003
#define WSANO_DATA                 11004
#define WSA_QOS_RECEIVERS          11005
#define WSA_QOS_SENDERS            11006
#define WSA_QOS_NO_SENDERS         11007
#define WSA_QOS_NO_RECEIVERS       11008
#define WSA_QOS_REQUEST_CONFIRMED  11009
#define WSA_QOS_ADMISSION_FAILURE  11010
#define WSA_QOS_POLICY_FAILURE     11011
#define WSA_QOS_BAD_STYLE          11012
#define WSA_QOS_BAD_OBJECT         11013
#define WSA_QOS_TRAFFIC_CTRL_ERROR 11014
#define WSA_QOS_GENERIC_ERROR      11015
#define WSA_QOS_ESERVICETYPE       11016
#define WSA_QOS_EFLOWSPEC          11017
#define WSA_QOS_EPROVSPECBUF       11018
#define WSA_QOS_EFILTERSTYLE       11019
#define WSA_QOS_EFILTERTYPE        11020
#define WSA_QOS_EFILTERCOUNT       11021
#define WSA_QOS_EOBJLENGTH         11022
#define WSA_QOS_EFLOWCOUNT         11023
#define WSA_QOS_EUNKOWNPSOBJ       11024
#define WSA_QOS_EPOLICYOBJ         11025
#define WSA_QOS_EFLOWDESC          11026
#define WSA_QOS_EPSFLOWSPEC        11027
#define WSA_QOS_EPSFILTERSPEC      11028
#define WSA_QOS_ESDMODEOBJ         11029
#define WSA_QOS_ESHAPERATEOBJ      11030
#define WSA_QOS_RESERVED_PETYPE    11031

/* Win32 API error codes returned by Winsock on the same
 * WSAGetLastError channel (official table rows; the CE WSAIoctl page
 * documents WSA_IO_PENDING as a WSAIoctl return value). */
#define WSA_INVALID_HANDLE         6
#define WSA_NOT_ENOUGH_MEMORY      8
#define WSA_INVALID_PARAMETER      87
#define WSA_OPERATION_ABORTED      995
#define WSA_IO_INCOMPLETE          996
#define WSA_IO_PENDING             997

/* ------------------------------------------------------------------ */
/* Structures                                                          */
/* ------------------------------------------------------------------ */

/* CE sockaddr page (aa450942): sa_data[14]; "except for the
 * sa_family member, sockaddr contents are expressed in network byte
 * order". */
struct sockaddr {
    u_short sa_family;
    char    sa_data[14];
};
typedef struct sockaddr SOCKADDR;
typedef SOCKADDR *LPSOCKADDR;

/* CE in_addr page (ms890973): the Winsock 1.1 S_un union layout. */
struct in_addr {
    union {
        struct { u_char s_b1, s_b2, s_b3, s_b4; } S_un_b;
        struct { u_short s_w1, s_w2; }            S_un_w;
        u_long S_addr;
    } S_un;
};
typedef struct in_addr IN_ADDR;

/* CE sockaddr_in page (aa450946): sin_family "must be AF_INET";
 * sin_zero pads to sizeof(sockaddr). */
struct sockaddr_in {
    short    sin_family;
    u_short  sin_port;
    IN_ADDR  sin_addr;
    char     sin_zero[8];
};

/* CE in6_addr page (ms890972, Windows CE .NET 4.1 and later). */
struct in6_addr {
    union {
        u_char  Byte[16];
        u_short Word[8];
    } u;
};

/* CE sockaddr_in6 page (aa450948, Windows CE .NET 4.1 and later):
 * sin6_family "must be AF_INET6". */
struct sockaddr_in6 {
    short           sin6_family;
    u_short         sin6_port;
    u_long          sin6_flowinfo;
    struct in6_addr sin6_addr;
    u_long          sin6_scope_id;
};

/* CE linger page (ms894561). */
struct linger {
    u_short l_onoff;
    u_short l_linger;
};

/* CE hostent page (ms890319): "only one copy of this structure is
 * allocated per thread ... copy any information that you need before
 * issuing any other Windows Sockets API calls". */
struct hostent {
    char *   h_name;
    char **  h_aliases;
    short    h_addrtype;
    short    h_length;
    char **  h_addr_list;
};

/* CE servent page (aa450886). */
struct servent {
    char *  s_name;
    char ** s_aliases;
    short   s_port;
    char *  s_proto;
};

/* CE protoent page (ms896341). */
struct protoent {
    char *  p_name;
    char ** p_aliases;
    short   p_proto;
};

/* CE timeval page (aa450970). */
struct timeval {
    long tv_sec;
    long tv_usec;
};

/* CE fd_set page (aa450370): a counted socket array (unlike the
 * desktop bitset layout).  The FD_SET/FD_CLR/FD_ISSET/FD_ZERO macro
 * semantics are documented by the official FD_ macro pages:
 * FD_SET "adds a file descriptor to the fd_set. If the file
 * descriptor already exist within the set, a duplicate will not be
 * added"; FD_CLR removes; FD_ISSET tests; FD_ZERO empties. */
struct fd_set {
    u_int  fd_count;
    SOCKET fd_array[FD_SETSIZE];
};
typedef struct fd_set fd_set;

static __inline int akari_fd_isset(SOCKET s, const fd_set *set)
{
    u_int i;
    for (i = 0; i < set->fd_count; ++i)
        if (set->fd_array[i] == s)
            return 1;
    return 0;
}
#define FD_ISSET(s, set)  akari_fd_isset((s), (set))
#define FD_ZERO(set) \
    do { (set)->fd_count = 0; } while (0)
#define FD_SET(s, set) \
    do { \
        if (!FD_ISSET((s), (set)) && (set)->fd_count < FD_SETSIZE) \
            (set)->fd_array[(set)->fd_count++] = (s); \
    } while (0)
#define FD_CLR(s, set) \
    do { \
        u_int akari_i; \
        for (akari_i = 0; akari_i < (set)->fd_count; ++akari_i) \
            if ((set)->fd_array[akari_i] == (s)) { \
                (set)->fd_array[akari_i] = \
                    (set)->fd_array[--(set)->fd_count]; \
                break; \
            } \
    } while (0)

/* CE WSADATA page (ms898735). */
typedef struct WSAData {
    WORD   wVersion;
    WORD   wHighVersion;
    char   szDescription[WSADESCRIPTION_LEN + 1];
    char   szSystemStatus[WSASYS_STATUS_LEN + 1];
    unsigned short iMaxSockets;
    unsigned short iMaxUdpDg;
    char  *lpVendorInfo;
} WSADATA, *LPWSADATA;

/* CE WSABUF page (ms898729). */
typedef struct __WSABUF {
    u_long len;
    char  *buf;
} WSABUF, *LPWSABUF;

/* CE WSAEVENT pages: the event object is a Win32 handle.  The CE
 * WSAOVERLAPPED page (ms898758). */
typedef struct _WSAOVERLAPPED {
    DWORD    Internal;
    DWORD    InternalHigh;
    DWORD    Offset;
    DWORD    OffsetHigh;
    WSAEVENT hEvent;
} WSAOVERLAPPED, *LPWSAOVERLAPPED;

/* CE AFPROTOCOLS page (aa450284): protocol query constraint list. */
typedef struct _AFPROTOCOLS {
    INT iAddressFamily;
    INT iProtocol;
} AFPROTOCOLS, *PAFPROTOCOLS, *LPAFPROTOCOLS;

/* CE PROTOCOL_INFO page (ms896340). */
typedef struct _PROTOCOL_INFO {
    DWORD  dwServiceFlags;
    INT    iAddressFamily;
    INT    iMaxSockAddr;
    INT    iMinSockAddr;
    INT    iSocketType;
    INT    iProtocol;
    DWORD  dwMessageSize;
    LPTSTR lpProtocol;
} PROTOCOL_INFO;

/* CE WSAPROTOCOLCHAIN page (ms898759). */
typedef struct _WSAPROTOCOLCHAIN {
    int    ChainLen;
    DWORD  ChainEntries[MAX_PROTOCOL_CHAIN];
} WSAPROTOCOLCHAIN, *LPWSAPROTOCOLCHAIN;

/* CE WSAPROTOCOL_INFO page (ms898760): 21-member layout. */
typedef struct _WSAPROTOCOL_INFO {
    DWORD            dwServiceFlags1;
    DWORD            dwServiceFlags2;
    DWORD            dwServiceFlags3;
    DWORD            dwServiceFlags4;
    DWORD            dwProviderFlags;
    GUID             ProviderId;
    DWORD            dwCatalogEntryId;
    WSAPROTOCOLCHAIN ProtocolChain;
    int              iVersion;
    int              iAddressFamily;
    int              iMaxSockAddr;
    int              iMinSockAddr;
    int              iSocketType;
    int              iProtocol;
    int              iProtocolMaxOffset;
    int              iNetworkByteOrder;
    int              iSecurityScheme;
    DWORD            dwMessageSize;
    DWORD            dwProviderReserved;
    TCHAR            szProtocol[WSAPROTOCOL_LEN + 1];
} WSAPROTOCOL_INFO, *LPWSAPROTOCOL_INFO;

/* CE SOCKET_ADDRESS page (aa450954). */
typedef struct _SOCKET_ADDRESS {
    LPSOCKADDR lpSockaddr;
    INT        iSockaddrLength;
} SOCKET_ADDRESS, *PSOCKET_ADDRESS;

/* CE WSANETWORKEVENTS page (ms898754): "Indicates which of the
 * FD_XXX network events have occurred" in lNetworkEvents. */
typedef struct _WSANETWORKEVENTS {
    long lNetworkEvents;
    int  iErrorCode[FD_MAX_EVENTS];
} WSANETWORKEVENTS, *LPWSANETWORKEVENTS;

/* CE TRANSMIT_FILE_BUFFERS page (aa450974). */
typedef struct _TRANSMIT_FILE_BUFFERS {
    PVOID Head;
    DWORD HeadLength;
    PVOID Tail;
    DWORD TailLength;
} TRANSMIT_FILE_BUFFERS;

/* CE addrinfo page (aa450282, Windows CE .NET 4.1 and later). */
struct addrinfo {
    int             ai_flags;
    int             ai_family;
    int             ai_socktype;
    int             ai_protocol;
    size_t          ai_addrlen;
    char           *ai_canonname;
    struct sockaddr *ai_addr;
    struct addrinfo *ai_next;
};

/* ------------------------------------------------------------------ */
/* Callback prototypes                                                 */
/* ------------------------------------------------------------------ */

/* Overlapped completion routine: the CE WSAIoctl page (ms898745)
 * prints the prototype
 *   void CALLBACK CompletionRoutine(IN DWORD dwError,
 *       IN DWORD cbTransferred, IN LPWSAOVERLAPPED lpOverlapped,
 *       IN DWORD dwFlags); */
typedef void (WSAAPI *LPWSAOVERLAPPED_COMPLETION_ROUTINE)(
    DWORD dwError, DWORD cbTransferred,
    LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags);

/* WSAAccept condition function: the CE WSAAccept page (ms898727)
 * prints the prototype
 *   int CALLBACK ConditionFunc(IN LPWSABUF lpCallerId,
 *       IN LPWSABUF lpCallerData, IN OUT LPQOS lpSQOS,
 *       IN OUT LPQOS lpGQOS, IN LPWSABUF lpCalleeId,
 *       OUT LPWSABUF lpCalleeData, OUT GROUP FAR* g,
 *       IN DWORD dwCallbackData); */
typedef int (WSAAPI *LPCONDITIONPROC)(
    LPWSABUF lpCallerId, LPWSABUF lpCallerData,
    LPQOS lpSQOS, LPQOS lpGQOS,
    LPWSABUF lpCalleeId, LPWSABUF lpCalleeData,
    GROUP *g, DWORD dwCallbackData);

/* ------------------------------------------------------------------ */
/* Name service (Winsock name spaces)                                  */
/* ------------------------------------------------------------------ */

/* CE WSAECOMPARATOR page (ms898736): "This enumeration is used for
 * Winsock version comparison semantics."  The page prints the syntax
 *     typedef enum _WSAEcomparator {COMP_EQUAL = 0,COMP_NOTLESS}
 *     WSAECOMPARATOR, *PWSAECOMPARATOR;
 * and documents COMP_EQUAL as "determining whether version values
 * are equal" and COMP_NOTLESS as "no less than a specified value". */
typedef enum _WSAEcomparator {
    COMP_EQUAL   = 0,
    COMP_NOTLESS
} WSAECOMPARATOR;
typedef WSAECOMPARATOR *PWSAECOMPARATOR;

/* The CE WSAQUERYSET page (ms898762) documents the member
 * "LPWSAVERSION lpVersion ... References desired version number and
 * provides version comparison semantics", but no CE page publishes
 * the WSAVERSION layout, so the type is opaque here (the documented
 * use is by pointer only). */
typedef struct _WSAVERSION WSAVERSION;
typedef WSAVERSION *LPWSAVERSION;

/* CE BLOB page (aa450302): "derived from a binary large object (BLOB)
 * and contains information about a block of data. For Bluetooth, this
 * structure defines values in the SDP record." */
typedef struct _BLOB {
    ULONG cbSize;
    BYTE  *pBlobData;
} BLOB, *LPBLOB;

/* CE CSADDR_INFO page (ms887919): "contains Windows Sockets address
 * information for a network service or name space provider."  The CE
 * form carries the two SOCKET_ADDRESS members directly; iSocketType
 * is one of the SOCK_* socket types, iProtocol the protocol. */
typedef struct _CSADDR_INFO {
    SOCKET_ADDRESS LocalAddr;
    SOCKET_ADDRESS RemoteAddr;
    INT            iSocketType;
    INT            iProtocol;
} CSADDR_INFO;
typedef CSADDR_INFO *LPCSAADDR_INFO;   /* named by the WSAQUERYSET page */

/* CE WSAQUERYSET page (ms898762): "provides relevant information
 * about a given service, including service class ID, service name,
 * applicable name-space identifier and protocol information, as well
 * as a set of transport addresses at which the service listens." */
typedef struct _WSAQuerySet {
    DWORD            dwSize;
    LPTSTR           lpszServiceInstanceName;
    LPGUID           lpServiceClassId;
    LPWSAVERSION     lpVersion;
    LPTSTR           lpszComment;
    DWORD            dwNameSpace;
    LPGUID           lpNSProviderId;
    LPTSTR           lpszContext;
    DWORD            dwNumberOfProtocols;
    LPAFPROTOCOLS    lpafpProtocols;
    LPTSTR           lpszQueryString;
    DWORD            dwNumberOfCsAddrs;
    LPCSAADDR_INFO   lpcsaBuffer;
    DWORD            dwOutputFlags;
    LPBLOB           lpBlob;
} WSAQUERYSET;
typedef WSAQUERYSET *PWSAQUERYSETW;
typedef WSAQUERYSET *LPWSAQUERYSET;   /* named by the CE prototypes */

/* CE WSANAMESPACE_INFO page (ms898753): "contains all registration
 * information for a name space provider." */
typedef struct _WSANAMESPACE_INFO {
    GUID   NSProviderId;
    DWORD  dwNameSpace;
    BOOL   fActive;
    DWORD  dwVersion;
    LPTSTR lpszIdentifier;
} WSANAMESPACE_INFO;
typedef WSANAMESPACE_INFO *PWSANAMESPACE_INFO;
typedef WSANAMESPACE_INFO *LPWSANAMESPACE_INFO;   /* named by the page */

/* CE WSASERVICECLASSINFO page (ms898768): "For each service class in
 * Windows Sockets 2, there is a single WSASERVICECLASSINFO
 * structure."  No CE page publishes the WSANSCLASSINFOW layout, so
 * only the pointer form is documented. */
typedef struct _WSANSCLASSINFOW WSANSCLASSINFOW;
typedef WSANSCLASSINFOW *LPWSANSCLASSINFOW;
typedef struct _WSAServiceClassInfo {
    LPGUID lpServiceClassId;
    LPTSTR lpszServiceClassName;
    DWORD  dwCount;
    LPWSANSCLASSINFOW lpClassInfos;
} WSASERVICECLASSINFO;
typedef WSASERVICECLASSINFO *PWSASERVICECLASSINFOW;

/* Name-service registration structures: CE pages aa450894
 * (SERVICE_ADDRESS), aa450895 (SERVICE_ADDRESSES), aa450902
 * (SERVICE_INFO), aa450910 (SERVICE_TYPE_INFO_ABS), aa450912
 * (SERVICE_TYPE_VALUE_ABS), ms895775 (NS_SERVICE_INFO).  The CE
 * pages publish the flag/display-hint constant NAMES (the
 * SERVICE_ADDRESS_FLAG_*, RESOURCEDISPLAYTYPE_* and NS_* tables)
 * without numeric values, so those constants are held as gaps in
 * docs/inventory.md rather than defined here. */
typedef struct _SERVICE_ADDRESS {
    DWORD dwAddressType;
    DWORD dwAddressFlags;
    DWORD dwAddressLength;
    DWORD dwPrincipalLength;
    BYTE  *lpAddress;
    BYTE  *lpPrincipal;
} SERVICE_ADDRESS;

typedef struct _SERVICE_ADDRESSES {
    DWORD           dwAddressCount;
    SERVICE_ADDRESS Addresses[1];
} SERVICE_ADDRESSES;
typedef SERVICE_ADDRESSES *LPSERVICE_ADDRESSES;

typedef struct _SERVICE_INFO {
    LPGUID                lpServiceType;
    LPTSTR                lpServiceName;
    LPTSTR                lpComment;
    LPTSTR                lpLocale;
    DWORD                 dwDisplayHint;
    DWORD                 dwVersion;
    DWORD                 dwTime;
    LPTSTR                lpMachineName;
    LPSERVICE_ADDRESSES   lpServiceAddress;
    BLOB                  ServiceSpecificInfo;
} SERVICE_INFO;

typedef struct _NS_SERVICE_INFO {
    DWORD        dwNameSpace;
    SERVICE_INFO ServiceInfo;
} NS_SERVICE_INFO;

typedef struct _SERVICE_TYPE_VALUE_ABS {
    DWORD  dwNameSpace;
    DWORD  dwValueType;
    DWORD  dwValueSize;
    LPTSTR lpValueName;
    PVOID  lpValue;
} SERVICE_TYPE_VALUE_ABS;

typedef struct _SERVICE_TYPE_INFO_ABS {
    LPTSTR                 lpTypeName;
    DWORD                  dwValueCount;
    SERVICE_TYPE_VALUE_ABS Values[1];
} SERVICE_TYPE_INFO_ABS;

/* CE WSASetService page (ms898772): essOperation is the
 * WSAESETSERVICEOP enumeration, listed as RNRSERVICE_REGISTER,
 * RNRSERVICE_DEREGISTER, RNRSERVICE_DELETE; the page publishes no
 * numeric values, so the ordinals follow the documented listing
 * order.  (c)-flagged: values not officially published. */
typedef enum _WSAESETSERVICEOP {
    RNRSERVICE_REGISTER    = 0,   /* (c) value not officially published */
    RNRSERVICE_DEREGISTER,        /* (c) value not officially published */
    RNRSERVICE_DELETE             /* (c) value not officially published */
} WSAESETSERVICEOP;

/* ------------------------------------------------------------------ */
/* Winsock 1.1 socket functions (CE 1.0 and later unless noted)        */
/* ------------------------------------------------------------------ */

AKARI_CE_IMPORT SOCKET accept(SOCKET s, struct sockaddr *addr,
                              int *addrlen) AKARI_CE_NAME(accept);
AKARI_CE_IMPORT int bind(SOCKET s, const struct sockaddr *name,
                         int namelen) AKARI_CE_NAME(bind);
AKARI_CE_IMPORT int closesocket(SOCKET s) AKARI_CE_NAME(closesocket);
AKARI_CE_IMPORT int connect(SOCKET s, const struct sockaddr *name,
                            int namelen) AKARI_CE_NAME(connect);
AKARI_CE_IMPORT struct hostent *gethostbyaddr(const char *addr, int len,
                                              int type) AKARI_CE_NAME(gethostbyaddr);
AKARI_CE_IMPORT struct hostent *gethostbyname(const char *name)
    AKARI_CE_NAME(gethostbyname);
AKARI_CE_IMPORT int gethostname(char *name, int namelen)
    AKARI_CE_NAME(gethostname);
AKARI_CE_IMPORT int getpeername(SOCKET s, struct sockaddr *name,
                                int *namelen) AKARI_CE_NAME(getpeername);
AKARI_CE_IMPORT int getsockname(SOCKET s, struct sockaddr *name,
                                int *namelen) AKARI_CE_NAME(getsockname);
AKARI_CE_IMPORT int getsockopt(SOCKET s, int level, int optname,
                               char *optval, int *optlen)
    AKARI_CE_NAME(getsockopt);
AKARI_CE_IMPORT u_long htonl(u_long hostlong) AKARI_CE_NAME(htonl);
AKARI_CE_IMPORT u_short htons(u_short hostshort) AKARI_CE_NAME(htons);
AKARI_CE_IMPORT unsigned long inet_addr(const char *cp)
    AKARI_CE_NAME(inet_addr);
AKARI_CE_IMPORT char *inet_ntoa(struct in_addr in)
    AKARI_CE_NAME(inet_ntoa);
AKARI_CE_IMPORT int ioctlsocket(SOCKET s, long cmd, u_long *argp)
    AKARI_CE_NAME(ioctlsocket);
AKARI_CE_IMPORT int listen(SOCKET s, int backlog) AKARI_CE_NAME(listen);
AKARI_CE_IMPORT u_long ntohl(u_long netlong) AKARI_CE_NAME(ntohl);
AKARI_CE_IMPORT u_short ntohs(u_short netshort) AKARI_CE_NAME(ntohs);
AKARI_CE_IMPORT int recv(SOCKET s, char *buf, int len, int flags)
    AKARI_CE_NAME(recv);
AKARI_CE_IMPORT int recvfrom(SOCKET s, char *buf, int len, int flags,
                             struct sockaddr *from, int *fromlen)
    AKARI_CE_NAME(recvfrom);
AKARI_CE_IMPORT int select(int nfds, fd_set *readfds, fd_set *writefds,
                           fd_set *exceptfds, const struct timeval *timeout)
    AKARI_CE_NAME(select);
AKARI_CE_IMPORT int send(SOCKET s, const char *buf, int len, int flags)
    AKARI_CE_NAME(send);
AKARI_CE_IMPORT int sendto(SOCKET s, const char *buf, int len, int flags,
                           const struct sockaddr *to, int tolen)
    AKARI_CE_NAME(sendto);
AKARI_CE_IMPORT int sethostname(char *pName, int cName)
    AKARI_CE_NAME(sethostname);
AKARI_CE_IMPORT int setsockopt(SOCKET s, int level, int optname,
                               const char *optval, int optlen)
    AKARI_CE_NAME(setsockopt);
AKARI_CE_IMPORT int shutdown(SOCKET s, int how) AKARI_CE_NAME(shutdown);
AKARI_CE_IMPORT SOCKET socket(int af, int type, int protocol)
    AKARI_CE_NAME(socket);

/* ------------------------------------------------------------------ */
/* WSA core functions                                                  */
/* ------------------------------------------------------------------ */

/* WSASocket/WSAStartup/WSASetEvent/WSASetLastError prototypes from
 * the CE 6.0 twin pages (ee493507/ee495252/ee494648/ee493103); all
 * other prototypes from the CE 5.0 pages.  WSA* extensions require
 * Windows CE .NET 4.0 and later except where noted. */
AKARI_CE_IMPORT SOCKET WSAAccept(SOCKET s, struct sockaddr *addr,
                                 int *addrlen,
                                 LPCONDITIONPROC lpfnCondition,
                                 DWORD dwCallbackData)
    AKARI_CE_NAME(WSAAccept);
AKARI_CE_IMPORT INT WSAAddressToString(LPSOCKADDR lpsaAddress,
                                       DWORD dwAddressLength,
                                       LPWSAPROTOCOL_INFO lpProtocolInfo,
                                       LPTSTR lpszAddressString,
                                       LPDWORD lpdwAddressStringLength)
    AKARI_CE_NAME(WSAAddressToString);
AKARI_CE_IMPORT int WSACleanup(void) AKARI_CE_NAME(WSACleanup);
AKARI_CE_IMPORT BOOL WSACloseEvent(WSAEVENT hEvent)
    AKARI_CE_NAME(WSACloseEvent);
AKARI_CE_IMPORT int WSAConnect(SOCKET s, const struct sockaddr *name,
                               int namelen, LPWSABUF lpCallerData,
                               LPWSABUF lpCalleeData, LPQOS lpSQOS,
                               LPQOS lpGQOS) AKARI_CE_NAME(WSAConnect);
AKARI_CE_IMPORT WSAEVENT WSACreateEvent(void)
    AKARI_CE_NAME(WSACreateEvent);
AKARI_CE_IMPORT int WSAEnumNetworkEvents(SOCKET s, WSAEVENT hEventObject,
                                         LPWSANETWORKEVENTS lpNetworkEvents)
    AKARI_CE_NAME(WSAEnumNetworkEvents);
/* CE WSAEnumNameSpaceProviders page (ms898737): "retrieves
 * information about available name spaces."  Returns the number of
 * WSANAMESPACE_INFO structures copied, or SOCKET_ERROR. */
AKARI_CE_IMPORT INT WSAEnumNameSpaceProviders(LPDWORD lpdwBufferLength,
                                              PWSANAMESPACE_INFO lpnspBuffer)
    AKARI_CE_NAME(WSAEnumNameSpaceProviders);
AKARI_CE_IMPORT int WSAEnumProtocols(LPINT lpiProtocols,
                                     LPWSAPROTOCOL_INFO lpProtocolBuffer,
                                     LPDWORD lpdwBufferLength)
    AKARI_CE_NAME(WSAEnumProtocols);
AKARI_CE_IMPORT int WSAEventSelect(SOCKET s, WSAEVENT hEventObject,
                                   long lNetworkEvents)
    AKARI_CE_NAME(WSAEventSelect);
AKARI_CE_IMPORT int WSAGetLastError(void) AKARI_CE_NAME(WSAGetLastError);
AKARI_CE_IMPORT BOOL WSAGetOverlappedResult(SOCKET s,
                                            LPWSAOVERLAPPED lpOverlapped,
                                            LPDWORD lpcbTransfer,
                                            BOOL fWait, LPDWORD lpdwFlags)
    AKARI_CE_NAME(WSAGetOverlappedResult);
AKARI_CE_IMPORT int WSAHtonl(SOCKET s, u_long hostlong, u_long *lpnetlong)
    AKARI_CE_NAME(WSAHtonl);
AKARI_CE_IMPORT int WSAHtons(SOCKET s, u_short hostshort,
                             u_short *lpnetshort) AKARI_CE_NAME(WSAHtons);
AKARI_CE_IMPORT int WSAIoctl(SOCKET s, DWORD dwIoControlCode,
                             LPVOID lpvInBuffer, DWORD cbInBuffer,
                             LPVOID lpvOutBuffer, DWORD cbOutBuffer,
                             LPDWORD lpcbBytesReturned,
                             LPWSAOVERLAPPED lpOverlapped,
                             LPWSAOVERLAPPED_COMPLETION_ROUTINE
                                 lpCompletionRoutine)
    AKARI_CE_NAME(WSAIoctl);
AKARI_CE_IMPORT SOCKET WSAJoinLeaf(SOCKET s, const struct sockaddr *name,
                                   int namelen, LPWSABUF lpCallerData,
                                   LPWSABUF lpCalleeData, LPQOS lpSQOS,
                                   LPQOS lpGQOS, DWORD dwFlags)
    AKARI_CE_NAME(WSAJoinLeaf);
/* CE WSALookupServiceBegin page (ms898748): "initiates a client query
 * that is constrained by the information contained within a
 * WSAQUERYSET structure. This function only returns a handle, which
 * should be used by subsequent calls to WSALookupServiceNext to get
 * the actual results."  dwControlFlags takes the LUP_* flags listed
 * on the page (values unpublished: gaps in docs/inventory.md). */
AKARI_CE_IMPORT INT WSALookupServiceBegin(LPWSAQUERYSET lpqsRestrictions,
                                          DWORD dwControlFlags,
                                          LPHANDLE lphLookup)
    AKARI_CE_NAME(WSALookupServiceBegin);
/* CE WSALookupServiceEnd page (ms898750): "called to free the handle
 * after previous calls to WSALookupServiceBegin and
 * WSALookupServiceNext."  If another thread's WSALookupServiceNext is
 * blocked, the end call cancels it. */
AKARI_CE_IMPORT INT WSALookupServiceEnd(HANDLE hLookup)
    AKARI_CE_NAME(WSALookupServiceEnd);
/* CE WSALookupServiceNext page (ms898752): retrieves the requested
 * service information from the handle obtained from
 * WSALookupServiceBegin; "The client should continue to call this
 * function until it returns WSA_E_NOMORE, indicating that all of
 * WSAQUERYSET has been returned."  The CE provider ignores
 * dwControlFlags (silently). */
AKARI_CE_IMPORT INT WSALookupServiceNext(HANDLE hLookup,
                                         DWORD dwControlFlags,
                                         LPDWORD lpdwBufferLength,
                                         LPWSAQUERYSET lpqsResults)
    AKARI_CE_NAME(WSALookupServiceNext);
AKARI_CE_IMPORT int WSANtohl(SOCKET s, u_long netlong, u_long *lphostlong)
    AKARI_CE_NAME(WSANtohl);
AKARI_CE_IMPORT int WSANtohs(SOCKET s, u_short netshort,
                             u_short *lphostshort) AKARI_CE_NAME(WSANtohs);
AKARI_CE_IMPORT int WSARecv(SOCKET s, LPWSABUF lpBuffers,
                            DWORD dwBufferCount,
                            LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags,
                            LPWSAOVERLAPPED lpOverlapped,
                            LPWSAOVERLAPPED_COMPLETION_ROUTINE
                                lpCompletionRoutine)
    AKARI_CE_NAME(WSARecv);
AKARI_CE_IMPORT int WSARecvFrom(SOCKET s, LPWSABUF lpBuffers,
                                DWORD dwBufferCount,
                                LPDWORD lpNumberOfBytesRecvd,
                                LPDWORD lpFlags, struct sockaddr *lpFrom,
                                LPINT lpFromlen,
                                LPWSAOVERLAPPED lpOverlapped,
                                LPWSAOVERLAPPED_COMPLETION_ROUTINE
                                    lpCompletionRoutine)
    AKARI_CE_NAME(WSARecvFrom);
AKARI_CE_IMPORT BOOL WSAResetEvent(WSAEVENT hEvent)
    AKARI_CE_NAME(WSAResetEvent);
AKARI_CE_IMPORT int WSASend(SOCKET s, LPWSABUF lpBuffers,
                            DWORD dwBufferCount,
                            LPDWORD lpNumberOfBytesSent, DWORD dwFlags,
                            LPWSAOVERLAPPED lpOverlapped,
                            LPWSAOVERLAPPED_COMPLETION_ROUTINE
                                lpCompletionRoutine)
    AKARI_CE_NAME(WSASend);
AKARI_CE_IMPORT int WSASendTo(SOCKET s, LPWSABUF lpBuffers,
                              DWORD dwBufferCount,
                              LPDWORD lpNumberOfBytesSent, DWORD dwFlags,
                              const struct sockaddr *lpTo, int iToLen,
                              LPWSAOVERLAPPED lpOverlapped,
                              LPWSAOVERLAPPED_COMPLETION_ROUTINE
                                  lpCompletionRoutine)
    AKARI_CE_NAME(WSASendTo);
AKARI_CE_IMPORT BOOL WSASetEvent(WSAEVENT hEvent)
    AKARI_CE_NAME(WSASetEvent);
AKARI_CE_IMPORT void WSASetLastError(int iError)
    AKARI_CE_NAME(WSASetLastError);
/* CE WSASetService page (ms898772, prototype from the documented
 * CE 6.0 twin ee493906): "registers or removes from the registry a
 * service instance within one or more name spaces."  Not supported by
 * the default DNS/WINS namespace provider (Nspm.dll) in CE; supported
 * by the PNRP provider. */
AKARI_CE_IMPORT INT WSASetService(LPWSAQUERYSET lpqsRegInfo,
                                  WSAESETSERVICEOP essOperation,
                                  DWORD dwControlFlags)
    AKARI_CE_NAME(WSASetService);
AKARI_CE_IMPORT SOCKET WSASocket(int af, int type, int protocol,
                                 LPWSAPROTOCOL_INFO lpProtocolInfo,
                                 GROUP g, DWORD dwFlags)
    AKARI_CE_NAME(WSASocket);
AKARI_CE_IMPORT int WSAStartup(WORD wVersionRequested,
                               LPWSADATA lpWSAData)
    AKARI_CE_NAME(WSAStartup);
AKARI_CE_IMPORT INT WSAStringToAddress(LPTSTR AddressString,
                                       INT AddressFamily,
                                       LPWSAPROTOCOL_INFO lpProtocolInfo,
                                       LPSOCKADDR lpAddress,
                                       LPINT lpAddressLength)
    AKARI_CE_NAME(WSAStringToAddress);
AKARI_CE_IMPORT DWORD WSAWaitForMultipleEvents(DWORD cEvents,
                                               const WSAEVENT *lphEvents,
                                               BOOL fWaitAll,
                                               DWORD dwTimeout,
                                               BOOL fAlertable)
    AKARI_CE_NAME(WSAWaitForMultipleEvents);

/* ================================================================== */
/* M96 value adoption -- values adopted from the CeGCC-lineage w32api
 * reference (R1, public domain; docs/clean-room.md par.4
 * revision 2026-09-10).  Every name below is documented by
 * the official CE pages WITHOUT a value (see the record
 * comments and the held ledger in this header); the value
 * is a CE-era ABI fact carried by the CE lineage itself.
 * Desktop mingw-w64 was considered and EXCLUDED as a source
 * (desktop-era values; policy note in clean-room.md).  R1's
 * license-exception files (winsock*, gl*) are unused.
 * ================================================================== */

/* ---- SOL_ family (1 names; R1) ---- */
#define SOL_IRLMP                                    0x00FF

/* ------------------------------------------------------------------
 * Book surface: netgen (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa450370 fd_set (Header: Winsock2.h.) */
/* ms890319 hostent (Header: Winsock2.h.) */
/* ms890973 in_addr (Header: Winsock2.h.) */
/* ms894561 linger (Header: Winsock2.h.) */
/* ms896341 protoent (Header: Winsock2.h.) */
/* aa450886 servent (Header: Winsock2.h.) */
/* aa450942 sockaddr (Header: Winsock2.h.) */
/* aa450946 sockaddr_in (Header: Winsock2.h.) */
/* aa450970 timeval (Header: Winsock2.h.) */
/* ------------------------------------------------------------------
 * Book surface: netgen (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms898755 WSANSPIoctl: print `int WSAAPI WSANSPIoctl( HANDLE hLookup, DWORD dwControlCode, LPVOID lpvInBuffer, DWORD cbInBuffer, LPVOID lpvOutBuffer, DWORD cbOutBuffer, LPDWORD lpcbBytesReturned, LPWSACOMPLETION lpCompletion);` */
/* (record-only: parameter or return type unpublished) */
/* ms880914 Accessing Remote File Systems */
/* ms880923 Adding an Entry to the IP Forward Table */
/* ms899602 Adding an IPv6 Route */
/* ms880924 Additional DHCP Settings */
/* ms880926 Address Registry Settings */
/* ms880927 Address Resolution Protocol */
/* ms880925 Addresses for Hosts and Routers */
/* ms886631 Allowing Inbound IPSec (IPv6) Traffic to Private Hosts */
/* ms880930 Annotated Client Code with Checkv4 Output */
/* ms880931 Annotated Server Code with Checkv4 Output */
/* ms880932 Anycast IPv6 Addresses */
/* ms880933 Application Registry Settings */
/* ms880934 Applications and Services that Support IPv6 */
/* ms880938 Assigning an IPv4 Address to a Device */
/* ms880939 Assigning an IPv6 Address to a Device */
/* ms880946 Authentication Protocol Initialization */
/* ms880949 Auto Dial for ICS */
/* ms880950 Auto Dial Registry Settings */
/* ms880951 Auto Dial Registry Subkeys */
/* ms880952 Automatic Client Configuration for IPv4 */
/* ms880954 Backward Compatibility for Windows Sockets 1.1 Applications */
/* ms880956 Basic Approach for getXbyY in the SPI */
/* ms886633 Best Practices for the IP Firewall */
/* ms880958 Binding to a Local Address */
/* ms880959 Blocking Input/Output */
/* ms880976 Byte Ordering Assumptions */
/* ms880984 Certificate Authentication */
/* ms880985 Challenge-Handshake Authentication Protocol (CHAP) */
/* ms899604 Changing the Application Source Code to Support IPv6 */
/* ms880987 Changing the Default Gateway */
/* ms880988 Changing the Properties of an Existing Route */
/* ms880989 Classless Interdomain Routing (CIDR) for IPv4 */
/* ms880990 Classless Interdomain Routing (CIDR) for IPv6 */
/* ms880991 Client-Side Configuration User Interface */
/* ms880994 Closing Sockets */
/* ms880998 Compatible Name Resolution for TCP/IP in the Windows Sockets 1.1 API */
/* ms881001 Compatible Name Resolution for TCP/IP in the Windows Sockets 1.1 SPI */
/* ms881003 Completion of the Authentication Session */
/* ms881006 Configuration User Interface */
/* ms899606 Configuring a Device with a Static Address for the IPv6 Test Lab */
/* ms899607 Configuring CLIENT1 */
/* ms899608 Configuring CLIENT2 */
/* ms899611 Configuring IPv6 Interface Attributes */
/* ms899612 Configuring ROUTER1 */
/* ms899613 Configuring ROUTER2 */
/* ms881338 Connecting to a Default Peer */
/* ms881346 Connecting to a Network */
/* ms881367 Connecting to the Test Internet (6bone) */
/* ms881495 Connection Sharing Registry Settings */
/* ms881505 Connection Shutdown */
/* ms881617 Converting to IPv6 */
/* ms881631 Core Protocol Stack for IPv4 */
/* ms881635 Core Protocol Stack for IPv6 */
/* ms899597 Core Protocols of IPv4 */
/* ms881626 Core Protocols of IPv6 */
/* ms881640 Creating a New Project for Converting to IPv4/IPv6 */
/* ms899622 Creating a Socket Client Application */
/* ms881657 Creating a Socket Server Application */
/* ms899623 Creating a Static Routing Infrastructure in the IPv6 Test Lab */
/* ms881658 Creating a UDP Datagram Socket Application */
/* ms881652 Creating an Application to Convert to IPv4/IPv6 */
/* ms881644 Creating an Internal Exposed Host */
/* ms881651 Creating an IP Multicast Application */
/* ms881663 Creating Event Objects */
/* ms886651 Creating Rules Based on Time */
/* ms886652 Creating Rules for an IPv6 Subnet */
/* ms899731 Creating the Run-Time Images for the IPv6 Test Lab */
/* ms881674 Data Transport Providers */
/* ms881675 Dead Gateway Detection */
/* ms899748 Deciding How to Display IP Addresses */
/* ms881677 Default Address Selection for IPv6 */
/* ms881678 Default IP Firewall Rules */
/* ms881679 Delayed Acknowledgments */
/* ms881680 Deleting an Entry to the IP Forward Table */
/* ms881683 Destroying Event Objects */
/* ms881684 Determining Available Network Resources */
/* ms899755 Determining if a Network Connection is Present */
/* ms881685 Determining Local and Remote Names */
/* ms881687 Determining the Status of One or More Sockets */
/* ms881700 DHCP Allocator */
/* ms881701 DHCP Allocator Operation */
/* ms881702 DhcpOptions */
/* ms881703 DhcpSendOptions */
/* ms881704 DHCPv6 Lite Registry Settings */
/* ms881705 DHCPv6 Non-Configurable Registry Settings */
/* ms881706 Diagnosing Connections */
/* ms899598 Diagnosing Connectivity Problems using the Network Connection Status UI */
/* ms886653 DNS Functions */
/* ms881714 DNS Proxy */
/* aa451151 DNS Proxy Registry Settings */
/* ms886655 DNS Reference */
/* ms886654 DNS Structures */
/* ms898953 Domain Discovery */
/* ms881715 Domain Discovery Application Development */
/* ms898954 Domain Discovery Functions */
/* ms881716 Domain Discovery Migration */
/* ms881717 Domain Discovery OS Design Development */
/* ms898955 Domain Discovery Reference */
/* ms881718 Domain Discovery Samples */
/* ms881719 Domain Discovery Security */
/* aa450365 Domain Discovery Structures */
/* ms881720 Dual Stack Architecture */
/* ms881721 Duplicate IP Address Detection for IPv4 */
/* ms881722 Duplicate IP Address Detection for IPv6 */
/* ms881854 EAP Application Development */
/* ms881723 EAP Authentication Protocols */
/* ms886656 EAP Enumerations */
/* ms886657 EAP Functions */
/* ms881724 EAP Implementation Details */
/* ms881725 EAP Initialization */
/* ms881726 EAP Installation */
/* ms898956 EAP Migration */
/* ms881855 EAP OS Design Development */
/* ms886658 EAP Reference */
/* ms881728 EAP Registry Settings */
/* ms898957 EAP Samples */
/* ms881729 EAP Security */
/* ms886659 EAP Structures */
/* ms881832 Enabling Auto Dial for ICS */
/* ms899760 Enabling IPv4 Routing */
/* ms899766 Enabling IPv6 Forwarding */
/* ms881834 Enabling IPv6 Routing */
/* ms881836 Enabling NAT */
/* ms881837 Enabling the DHCP Allocator */
/* ms881838 Enabling the DNS Proxy */
/* ms881839 Enhanced Functionality at Connect Time */
/* ms881842 Error Reporting and Parameter Validation */
/* ms881844 Establishing a Network Connection */
/* ms881851 Event Object Signaling */
/* ms881852 Event Objects in the Winsock SPI */
/* ms881849 EVENTLOG */
/* ms881853 Extended Byte-Order Conversion Routines */
/* ms898958 Extensible Authentication Protocol */
/* ms881863 FIREWALL */
/* ms898960 Firewall */
/* ms898961 Firewall Rule Examples */
/* ms881866 Flow Control Using ICMP for IPv4 */
/* ms881880 Function Interface Model */
/* ms898964 Gateway Logging */
/* ms881881 Gateway Logging Registry Settings */
/* ms898965 General Firewall Rule Examples */
/* ms881884 Generic Data Transport Functions */
/* ms881886 gethostbyaddr Function in the SPI */
/* ms881887 gethostbyname Function in the SPI */
/* ms881889 gethostname Function in the SPI */
/* ms881910 Host Name Resolution for Dual Stack (IPv4/IPv6) */
/* ms881909 Host Name Resolution for IPv4 */
/* ms881911 Host Name Resolution for IPv6 */
/* ms881912 Host Name Resolution Using a DNS Server for IPv4 */
/* ms881913 Host Name Resolution Using a NetBIOS Server for IPv4 */
/* ms881914 Host Name Resolution Using Registry Entries */
/* ms881908 HOSTNAME */
/* aa450273 How to Convert an Application from IPv4 to IPv4/IPv6 */
/* aa450274 How to Set Up and Use an IPv6 Test Lab */
/* ms886676 ICMP Functions */
/* ms886677 ICMP Reference */
/* ms886678 ICMP Structures */
/* ms898969 ICS Application Development */
/* ms886679 ICS Functions */
/* ms898966 ICS Migration */
/* aa450033 ICS OS Design Development */
/* ms886680 ICS Reference */
/* aa450034 ICS Registry Settings */
/* ms898967 ICS Samples */
/* aa450035 ICS Security */
/* ms881921 IKE Authentication */
/* ms881923 Implementing a Secure Socket */
/* aa450026 Installation Functions */
/* aa450110 Installing an LSP */
/* aa450032 Interactive User Interface */
/* ms898968 Internet Connection Sharing */
/* aa450037 Internet Control Message Protocol (ICMP) */
/* aa450036 Internet Control Message Protocol for IPv6 (ICMPv6) */
/* aa450038 Internet Group Management Protocol (IGMP) */
/* aa450041 Internet Protocol (IP) for IPv4 */
/* aa450042 Internet Protocol (IP) for IPv6 */
/* aa450040 Internet Protocol Helper APIs */
/* aa450043 Internet Protocol version 4 Address Classes */
/* ms898970 Internet Protocol Version 6 */
/* aa450046 Internet Router Discovery Protocol (IRDP) for IPv4 */
/* aa450053 IP Firewall Application Development */
/* ms886672 IP Firewall Data Types */
/* ms886673 IP Firewall Enumerations */
/* ms886674 IP Firewall Functions */
/* ms886684 IP Firewall Logging Reference */
/* aa450054 IP Firewall Logging Registry Settings */
/* aa450055 IP Firewall Migration */
/* aa450052 IP Firewall OS Design Development */
/* ms886685 IP Firewall Reference */
/* aa450056 IP Firewall Registry Settings */
/* aa450057 IP Firewall Samples */
/* aa450058 IP Firewall Security */
/* ms886675 IP Firewall Structures */
/* aa450059 IP Helper Code Samples */
/* ms886686 IP Helper Enumerations */
/* ms886687 IP Helper Functions */
/* ms886688 IP Helper Reference */
/* ms886689 IP Helper Structures */
/* ms898971 IP Independent Source Code Examples */
/* aa450060 IP Multicasting for IPv4 */
/* aa450061 IP Multicasting for IPv6 */
/* aa450062 IP NAT Registry Settings */
/* aa450050 IP/ARP Extensions for IPv4 Multicasting */
/* aa450051 IPConfig */
/* aa450063 IPPROTO_IP */
/* aa450064 IPPROTO_IPV6 */
/* aa450065 IPPROTO_TCP */
/* aa450066 IPPROTO_UDP */
/* aa450067 IPSec Application Development */
/* ms886690 IPSec Functions */
/* aa450068 IPSec Migration */
/* aa450069 IPSec OS Design Development */
/* ms886691 IPSec Reference */
/* aa450070 IPSec Registry Settings */
/* aa450071 IPSec Samples */
/* aa450072 IPSec Security */
/* ms886692 IPSec Structures */
/* ms898972 IPSec v4 */
/* aa450073 IPv4-only Client Code */
/* aa450074 IPv4-only Server Code */
/* ms898973 IPv4-only Source Code Examples */
/* aa450077 IPv6 */
/* aa450078 IPv6 Address Autoconfiguration */
/* aa450079 IPv6 Addresses */
/* aa450081 IPv6 Addresses to Configure */
/* aa450044 IPv6 Addressing */
/* aa450432 IPv6 adu */
/* aa450080 IPv6 and IPv4 Coexistence */
/* aa450087 IPv6 Application Development */
/* aa450084 IPv6 Characteristics */
/* ms900518 IPv6 dp6dns */
/* ms900530 IPv6 dp6domain */
/* ms900531 IPv6 dp6enum */
/* ms900540 IPv6 dp6pd */
/* ms900542 IPv6 dp6rf */
/* aa450433 IPv6 gp */
/* aa450434 IPv6 gpu */
/* aa450435 IPv6 gpu MaxTempDADAttempts */
/* aa450436 IPv6 gpu MaxTempLifetime */
/* aa450437 IPv6 gpu MaxTempRandomTime */
/* aa450438 IPv6 gpu NeighborCacheLimit */
/* aa450439 IPv6 gpu RouteCacheLimit */
/* aa450440 IPv6 gpu TempRandomTime */
/* aa450441 IPv6 gpu TempRegenerateTime */
/* aa450442 IPv6 gpu UseTemporaryAddresses */
/* aa450443 IPv6 if */
/* aa450445 IPv6 ifc */
/* aa450446 IPv6 ifd */
/* aa450083 IPv6 Implementations */
/* aa450085 IPv6 Interface Identifiers */
/* ms898974 Ipv6 Migration */
/* aa450447 IPv6 nc */
/* aa450448 IPv6 ncf */
/* ms898975 IPv6 OS Design Development */
/* aa450086 IPv6 Overview */
/* aa450045 IPv6 Packets */
/* aa450449 IPv6 ppd */
/* aa450450 IPv6 ppt */
/* aa450451 IPv6 ppu */
/* aa450452 IPv6 rc */
/* aa450453 IPv6 rcf */
/* aa450088 IPv6 References */
/* aa450454 IPv6 renew */
/* aa450089 IPv6 RFCs and Internet Drafts */
/* aa450455 IPv6 rlu */
/* aa450456 IPv6 rt */
/* aa450457 IPv6 rtu */
/* ms898976 Ipv6 Samples */
/* aa450090 IPv6 Security */
/* aa450458 IPv6 spt */
/* aa450459 IPv6 spu */
/* aa450091 IPv6 Test Lab Requirements */
/* aa450092 IPv6 Traffic Between Nodes in Different Sites Across the Internet (6to4) */
/* aa450093 IPv6 Traffic Between Nodes on Different Subnets of an IPv4 Internetwork */
/* aa450094 IPv6 Traffic Between Nodes on Different Subnets of an IPv6 Internetwork */
/* aa450075 IPv6-Enabled Client Code */
/* aa450076 IPv6-Enabled Server Code */
/* aa450460 IPv6tun */
/* aa450103 Joining and Leaving a Multicast Group */
/* aa450109 Layered Protocols and Provider Chains */
/* aa450114 Link Layer Functionality */
/* aa450115 Listing Addresses */
/* aa450117 Locating a Printer on a Network */
/* ms886695 Logging Blocked Inbound Packets */
/* aa450118 Machine Name to IP Address Maps */
/* aa450120 Maintaining Route Tables for IPv4 */
/* aa450121 Maintaining Route Tables for IPv6 */
/* aa450123 Managing Interfaces */
/* ms882519 Managing IP Addresses */
/* ms882649 Managing IPv4 Routes */
/* ms882660 Managing IPv6 Routes */
/* ms882630 Managing Network Adapters */
/* ms882641 Managing Network Connections with WNet */
/* ms882665 Managing Routing */
/* ms882681 Manually Configuring an IPv4 Address */
/* ms899789 Manually Configuring IPv6 Addresses */
/* ms882704 Mapping an IP Multicast Address */
/* ms882717 Maximum Transmission Unit (MTU) */
/* aa450082 Methods for Configuring IPv6 Addresses */
/* ms882787 Microsoft Challenge-Handshake Authentication Protocol 2.0 (MS CHAP V2) */
/* ms882814 MODULESLIST */
/* ms882863 Multicast Extensions to Windows Sockets */
/* ms882950 Multicast IPv6 Addresses */
/* ms882958 Multicast Listener Discovery (MLD) */
/* ms882965 Multihoming for IPv4 */
/* ms882973 Multihoming for IPv6 */
/* ms882984 Multiple Public Interface Support */
/* ms882991 Multiple Transport Protocols */
/* ms883014 Multipoint Attributes in the WSAPROTOCOL_INFOW Structure */
/* ms883026 Multipoint Socket Attributes */
/* ms883035 Multipoint Taxonomy and Glossary */
/* ms883043 Nagle Algorithm */
/* ms883051 Name Registration for IPv4 */
/* ms883059 Name Resolution and Winsock */
/* ms883065 Name Resolution Data Structures */
/* ms883073 Name Resolution Data Structures in the SPI */
/* ms883081 Name Resolution Division of Responsibilities Between DLL and Service Providers */
/* ms883100 Name Resolution for IPv4 Using the Cache */
/* ms883089 Name Resolution for IPv6 Using the Cache */
/* ms883096 Name Resolution Functions */
/* ms883098 Name Resolution Model */
/* ms883099 Name Resolution Service Provider Requirements */
/* ms883101 Namespace Organization */
/* ms883102 Namespace Provider Architecture */
/* ms883104 Namespace Provider Initialization and Cleanup */
/* ms883103 Namespace Provider Installation */
/* ms883106 Naming Conventions */
/* ms883107 NAT */
/* ms883108 NAT and Applications */
/* ms883109 NAT Editor */
/* ms883110 NAT Editor Functions */
/* ms883112 NAT Editor Initialization and Registration */
/* ms883113 NAT Editor Operation */
/* ms883114 NAT Firewall Packet Logging */
/* ms883121 NAT Packet Filter */
/* ms883122 NAT Traversal */
/* ms883123 NAT Traversal in Internet Gateways */
/* ms883124 NAT Traversal Operation */
/* ms883120 NATIVEWIFI */
/* ms898987 NDIS Packet Capturing */
/* ms883126 NDIS Packet Capturing Application Development */
/* ms883127 NDIS Packet Capturing Migration */
/* ms883125 NDIS Packet Capturing OS Development */
/* ms883128 NDIS Packet Capturing Security */
/* ms883129 Neighbor Discovery (ND) */
/* ms883130 NETLOG */
/* ms886701 Netlog */
/* ms883131 Netlogctl */
/* ms895675 Netstat */
/* ms883132 NETWORK */
/* ms883134 Network Address Translation */
/* ms898988 Network Bridging */
/* ms898989 Network Bridging Application Development */
/* ms883135 Network Bridging Architecture */
/* ms898990 Network Bridging Migration */
/* ms883136 Network Bridging Object Identifiers */
/* ms883137 Network Bridging OS Design Development */
/* ms883138 Network Bridging Queriable Object Identifiers */
/* ms898991 Network Bridging Reference */
/* ms883139 Network Bridging Registry Settings */
/* ms883140 Network Bridging Sample Registry Configuration */
/* ms898992 Network Bridging Samples */
/* ms883141 Network Bridging Security */
/* ms883142 Network Bridging Settable Object Identifiers */
/* ms883143 Network Bridging Spanning Tree Algorithm */
/* ms883144 Network Driver Interface Specification (NDIS) */
/* ms883145 Network Driver Interface Specification (NDIS) for IPv6 */
/* ms883146 Network Folder */
/* ms898997 Network Utilities */
/* ms898998 Network Utilities Application Development */
/* ms883147 Network Utilities Migration */
/* ms883148 Network Utilities OS Design Development */
/* ms883149 Network Utilities Samples */
/* ms899230 Network Utilities Security */
/* ms883150 Nonblocking Input/Output */
/* ms883151 Notification of Network Events */
/* ms883312 Obtaining Identity Information */
/* ms883321 Obtaining the Buffer Size */
/* ms883385 Operational Characteristics of NDIS Object Identifiers */
/* ms883386 Out-of-Band Data in the SPI */
/* ms883387 Overlapped Completion Indication Mechanisms */
/* ms883388 Overlapped Input/Output */
/* ms883390 Packet Data Handling and Editing */
/* ms883392 PARENTALCONTROLS */
/* ms883399 PASSWORD */
/* ms883400 Path Maximum Transmission Unit (PMTU) Discovery */
/* ms883419 Ping */
/* ms899797 Pinging a Host in the IPv6 Test Lab by Using a Link-Local Address */
/* ms883420 Plug and Play */
/* ms883430 Port States */
/* ms883428 PORTFORWARD */
/* ms883438 Printing on a Network */
/* ms883449 Protected Extensible Authentication Protocol (PEAP) */
/* ms883450 Protocol Basics: Listen, Connect, Accept */
/* ms883452 Protocol-Independent Multicast and Multipoint in the SPI */
/* ms883453 Protocol-Independent Name Resolution */
/* ms883460 RAS */
/* ms883461 RAS and Authentication Protocol Interaction During Authentication */
/* aa450124 Reading Socket Options */
/* aa450125 Receiving an IP Multicast Datagram */
/* aa450126 Receiving an IP Multicast Datagram Sample */
/* aa450129 Receiving Notification of Network Events */
/* aa450131 Reconnecting and Disconnecting */
/* ms899537 Reference Gateway User Interface */
/* aa450133 Reference Gateway User Interface Migration */
/* aa450134 Reference Gateway User Interface OS Design Development */
/* aa450135 Reference Gateway User Interface Samples */
/* aa450136 Reference Gateway User Interface Security */
/* ms899538 Remote Configuration Framework */
/* aa450149 Remote Configuration Framework Application Development */
/* ms899539 Remote Configuration Framework Interfaces */
/* aa450146 Remote Configuration Framework Migration */
/* ms881882 Remote Configuration Framework Modules */
/* ms899540 Remote Configuration Framework OS Design Development */
/* ms899541 Remote Configuration Framework Reference */
/* aa450145 Remote Configuration Framework Registry Settings */
/* aa450147 Remote Configuration Framework Samples */
/* aa450148 Remote Configuration Framework Security */
/* aa450150 REMOTEUTILS */
/* ms899806 Removing an IPv6 Route */
/* aa450229 Restricting Outbound Traffic to Selected TCP Ports */
/* aa450162 Retrieving a Connection Name */
/* aa450163 Retrieving a User Name */
/* aa450164 Retrieving Information About Network Configuration */
/* aa450181 Retrieving Network Data */
/* aa450182 Retrieving Network Errors */
/* ms900298 Retrieving Network Information */
/* aa450166 Retrieving Statistics for IP and ICMP */
/* aa450165 Retrieving Statistics for TCP and UDP */
/* aa450186 ROOTDIRS */
/* aa450187 Route */
/* aa450188 Routing for IPv4 */
/* aa450189 Routing for IPv6 */
/* ms899815 Running the Checkv4 Utility */
/* ms899823 Running the SimpleClient and SimpleServer Applications */
/* aa450194 Scatter/Gather I/O Support */
/* ms885824 Secure Socket Control Codes */
/* aa450204 Sending an IP Multicast Datagram */
/* aa450205 Sending an IP Multicast Datagram Sample */
/* aa450217 Service Installation in the Winsock SPI */
/* aa450219 Service Provider Activation */
/* aa450220 Service Query */
/* aa450221 Service Registry Settings */
/* ms884887 Setting a User Name and Password */
/* ms884896 Setting ForwardMetric Values */
/* ms884912 Shared Sockets in the SPI */
/* ms884916 Silly Window Syndrome (SWS) */
/* ms884918 Single Subnet with Link-Local Addresses */
/* ms884919 SIO_MULTICAST_SCOPE IOCTL */
/* ms884920 SIO_MULTIPOINT_LOOPBACK Ioctl */
/* ms884921 Slow Start Algorithm and Congestion Avoidance */
/* ms884922 SMBFILE */
/* ms884923 SMBPRINT */
/* ms884930 Socket Attribute Flags and Modes */
/* ms884931 Socket Client */
/* ms884933 Socket Connections on Connection-Oriented Protocols */
/* ms884932 Socket Connections on Connectionless Protocols */
/* ms884934 Socket Creation and Descriptor Management */
/* ms884935 Socket Functions */
/* ms884936 Socket I/O */
/* ms899548 Socket Options */
/* ms884937 Socket Options and IOCTLs */
/* ms884938 Socket Options Not Supported */
/* ms884939 Socket Server */
/* ms900408 SOL_IRLMP */
/* ms884940 SOL_SOCKET */
/* ms884941 Spanning Tree Algorithm Functionality */
/* ms884947 Static Port Mappings */
/* ms899832 Stream Socket Application */
/* ms899840 Submitting a Firewall for Certification */
/* ms884950 Summary of Namespace Provider Functions */
/* ms884951 Summary of Socket IOCTL Opcodes */
/* ms884952 Summary of SPI Functions */
/* ms884956 Support for Scatter/Gather Input/Output in the SPI */
/* ms884964 TCP Connections to and from Multihomed Computers */
/* ms884986 TCP Keep-Alive Messages */
/* ms884987 TCP Receive Window Size Calculation and Window Scaling */
/* ms884988 TCP Retransmission Behavior */
/* ms884989 TCP Selective Acknowledgment */
/* ms899549 TCP/IP */
/* ms884967 TCP/IP and Dial-up Support */
/* ms884974 TCP/IP and Dynamic DNS */
/* ms884970 TCP/IP and IP Helper */
/* ms884966 TCP/IP and the DHCP Client */
/* ms884968 TCP/IP and the DNS Client */
/* ms884983 TCP/IP and Windows Sockets */
/* ms884984 TCP/IP and WinHTTP */
/* ms884982 TCP/IP and WinInet */
/* ms884985 TCP/IP and WINS */
/* ms899552 TCP/IP Application Development */
/* ms880936 TCP/IP Architectural Model */
/* ms884965 TCP/IP Best Practices */
/* ms899550 TCP/IP Migration */
/* ms884971 TCP/IP OS Design Development */
/* ms884972 TCP/IP Protocol Suite */
/* ms899553 TCP/IP Reference */
/* ms884973 TCP/IP Registry Settings */
/* ms899554 TCP/IP Samples */
/* ms884975 TCP/IP Security */
/* ms884969 TCP/IP Support in Windows CE */
/* ms884976 TCP/IPv4 and TCP/IPv6 Common Registry Settings */
/* ms884977 TCP/IPv4 Configurable Registry Settings */
/* ms900416 TCP/IPv4 Device Name Registry Settings */
/* ms884978 TCP/IPv4 Non-Configurable Registry Settings */
/* ms884979 TCP/IPv6 Architectural Model */
/* ms884980 TCP/IPv6 Configurable Registry Settings */
/* ms884981 TCP/IPv6 Registry Settings */
/* ms899556 TCP/IPv6 Troubleshooting Tools */
/* ms885274 Terminating a Network Connection */
/* ms899850 Testing an IPv6 Connection by Using the Ping Command */
/* ms899868 Testing IPv6 Connectivity by Using the Ping Command */
/* ms899882 Testing your Application or Device in an IPv6 Environment */
/* ms885292 Throughput Considerations */
/* ms885298 TIMESERVICE */
/* ms885306 Timestamps (RFC 1323) */
/* aa450971 Tracert */
/* ms885312 Transmission Control Protocol (TCP) */
/* ms885323 Transport Installation */
/* ms885336 Transport Level Security (TLS) */
/* ms885344 Transport Mapping Between API and SPI Functions */
/* ms885352 Transport Service Providers */
/* ms899599 Troubleshooting IPv6 */
/* ms899600 Troubleshooting: Setting Up and Using the IPv6 Test Lab */
/* ms885359 Unicast IPv6 Addresses */
/* ms885421 Upcalls Exposed by Ws2.dll */
/* ms900593 USB Flash Config Tool */
/* ms900441 USB Flash Config Tool Architecture */
/* ms900595 USB Flash Config Tool Migration */
/* ms900443 USB Flash Config Tool OS Design Development */
/* ms900447 USB Flash Config Tool Registry Settings */
/* ms900597 USB Flash Config Tool Samples */
/* ms900450 USB Flash Config Tool Security */
/* ms885768 Use of ICMP to Diagnose Problems for IPv4 */
/* ms885769 Use of IGMP by Windows CE */
/* ms885773 User Datagram Protocol (UDP) */
/* ms885774 User Datagram Protocol (UDP) and Name Resolution for IPv4 */
/* ms885775 USERS */
/* ms885776 Using a Deferred Handshake */
/* ms885778 Using Event Objects */
/* ms885779 Using IPV6_PROTECTION_LEVEL */
/* ms900101 Using Temporary Addresses in the IPv6 Test Lab */
/* ms885783 Using the Address Resolution Protocol */
/* ms885781 Using the Remote Configuration Framework */
/* ms885789 Using WSAStartup to Initialize Winsock */
/* ms885790 VERSION */
/* ms900107 Viewing Interface Information */
/* ms900114 Viewing the IPv6 Routing Table */
/* ms900123 Viewing the Neighbor Cache */
/* ms900128 Viewing the Route Cache */
/* ms885794 WATSON */
/* ms899584 Windows Networking API/Redirector */
/* ms885813 Windows Networking API/Redirector Application Development */
/* aa450259 Windows Networking API/Redirector Functions */
/* ms885814 Windows Networking API/Redirector Migration */
/* ms899585 Windows Networking API/Redirector OS Design Development */
/* aa450260 Windows Networking API/Redirector Reference */
/* aa450132 Windows Networking API/Redirector Registry Settings */
/* ms885815 Windows Networking API/Redirector Samples */
/* ms885816 Windows Networking API/Redirector Security */
/* aa450261 Windows Networking API/Redirector Structures */
/* ms899586 Windows Sockets */
/* ms898578 Windows Sockets Reference */
/* ms885818 Windows Sockets Support for IPv6 */
/* ms885819 Windows-Specific Extension Functions */
/* ms885820 Winsock 2.2 */
/* ms885822 Winsock and WOSA */
/* ms899587 Winsock Application Development */
/* ms885821 Winsock Architecture */
/* ms885823 Winsock Completion Indications */
/* aa450262 Winsock Enumerations */
/* aa450263 Winsock Error Codes */
/* ms885825 Winsock Event Objects */
/* aa450264 Winsock Functions */
/* ms886607 Winsock Migration */
/* ms886615 Winsock Name Resolution */
/* ms885817 Winsock OS Design Development */
/* ms886617 Winsock Overlapped I/O and Event Objects */
/* aa450265 Winsock Reference */
/* ms899596 Winsock Samples */
/* ms886618 Winsock Secure Sockets */
/* ms886619 Winsock Security */
/* ms886620 Winsock Service Provider Interface (SPI) */
/* ms886621 Winsock Service Providers */
/* aa450266 Winsock SPI Functions */
/* aa450267 Winsock SPI Reference */
/* aa450269 Winsock Structures */
/* ms886481 Winsock Support in Windows CE */
/* ------------------------------------------------------------------
 * Book surface: wsock-structures (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa450370 fd_set (Header: Winsock2.h.) */
/* ms890319 hostent (Header: Winsock2.h.) */
/* ms890973 in_addr (Header: Winsock2.h.) */
/* ms894561 linger (Header: Winsock2.h.) */
/* ms896341 protoent (Header: Winsock2.h.) */
/* aa450886 servent (Header: Winsock2.h.) */
/* aa450942 sockaddr (Header: Winsock2.h.) */
/* aa450946 sockaddr_in (Header: Winsock2.h.) */
/* aa450970 timeval (Header: Winsock2.h.) */
/* ------------------------------------------------------------------
 * Book surface: netgen (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms898732 WSACOMPLETION: documented name-only (no value published; held) */
/* aa450370 fd_set (Header: Winsock2.h.) */
/* ms890319 hostent (Header: Winsock2.h.) */
/* ms890973 in_addr (Header: Winsock2.h.) */
/* ms894561 linger (Header: Winsock2.h.) */
/* ms896341 protoent (Header: Winsock2.h.) */
/* aa450886 servent (Header: Winsock2.h.) */
/* aa450942 sockaddr (Header: Winsock2.h.) */
/* aa450946 sockaddr_in (Header: Winsock2.h.) */
/* aa450970 timeval (Header: Winsock2.h.) */
/* ------------------------------------------------------------------
 * Book surface: netgen (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms880914 Accessing Remote File Systems */
/* ms880923 Adding an Entry to the IP Forward Table */
/* ms899602 Adding an IPv6 Route */
/* ms880924 Additional DHCP Settings */
/* ms880926 Address Registry Settings */
/* ms880927 Address Resolution Protocol */
/* ms880925 Addresses for Hosts and Routers */
/* ms886631 Allowing Inbound IPSec (IPv6) Traffic to Private Hosts */
/* ms880930 Annotated Client Code with Checkv4 Output */
/* ms880931 Annotated Server Code with Checkv4 Output */
/* ms880932 Anycast IPv6 Addresses */
/* ms880933 Application Registry Settings */
/* ms880934 Applications and Services that Support IPv6 */
/* ms880938 Assigning an IPv4 Address to a Device */
/* ms880939 Assigning an IPv6 Address to a Device */
/* ms880946 Authentication Protocol Initialization */
/* ms880949 Auto Dial for ICS */
/* ms880950 Auto Dial Registry Settings */
/* ms880951 Auto Dial Registry Subkeys */
/* ms880952 Automatic Client Configuration for IPv4 */
/* ms880954 Backward Compatibility for Windows Sockets 1.1 Applications */
/* ms880956 Basic Approach for getXbyY in the SPI */
/* ms886633 Best Practices for the IP Firewall */
/* ms880958 Binding to a Local Address */
/* ms880959 Blocking Input/Output */
/* ms880976 Byte Ordering Assumptions */
/* ms880984 Certificate Authentication */
/* ms880985 Challenge-Handshake Authentication Protocol (CHAP) */
/* ms899604 Changing the Application Source Code to Support IPv6 */
/* ms880987 Changing the Default Gateway */
/* ms880988 Changing the Properties of an Existing Route */
/* ms880989 Classless Interdomain Routing (CIDR) for IPv4 */
/* ms880990 Classless Interdomain Routing (CIDR) for IPv6 */
/* ms880991 Client-Side Configuration User Interface */
/* ms880994 Closing Sockets */
/* ms880998 Compatible Name Resolution for TCP/IP in the Windows Sockets 1.1 API */
/* ms881001 Compatible Name Resolution for TCP/IP in the Windows Sockets 1.1 SPI */
/* ms881003 Completion of the Authentication Session */
/* ms881006 Configuration User Interface */
/* ms899606 Configuring a Device with a Static Address for the IPv6 Test Lab */
/* ms899607 Configuring CLIENT1 */
/* ms899608 Configuring CLIENT2 */
/* ms899611 Configuring IPv6 Interface Attributes */
/* ms899612 Configuring ROUTER1 */
/* ms899613 Configuring ROUTER2 */
/* ms881338 Connecting to a Default Peer */
/* ms881346 Connecting to a Network */
/* ms881367 Connecting to the Test Internet (6bone) */
/* ms881495 Connection Sharing Registry Settings */
/* ms881505 Connection Shutdown */
/* ms881617 Converting to IPv6 */
/* ms881631 Core Protocol Stack for IPv4 */
/* ms881635 Core Protocol Stack for IPv6 */
/* ms899597 Core Protocols of IPv4 */
/* ms881626 Core Protocols of IPv6 */
/* ms881640 Creating a New Project for Converting to IPv4/IPv6 */
/* ms899622 Creating a Socket Client Application */
/* ms881657 Creating a Socket Server Application */
/* ms899623 Creating a Static Routing Infrastructure in the IPv6 Test Lab */
/* ms881658 Creating a UDP Datagram Socket Application */
/* ms881652 Creating an Application to Convert to IPv4/IPv6 */
/* ms881644 Creating an Internal Exposed Host */
/* ms881651 Creating an IP Multicast Application */
/* ms881663 Creating Event Objects */
/* ms886651 Creating Rules Based on Time */
/* ms886652 Creating Rules for an IPv6 Subnet */
/* ms899731 Creating the Run-Time Images for the IPv6 Test Lab */
/* ms881674 Data Transport Providers */
/* ms881675 Dead Gateway Detection */
/* ms899748 Deciding How to Display IP Addresses */
/* ms881677 Default Address Selection for IPv6 */
/* ms881678 Default IP Firewall Rules */
/* ms881679 Delayed Acknowledgments */
/* ms881680 Deleting an Entry to the IP Forward Table */
/* ms881683 Destroying Event Objects */
/* ms881684 Determining Available Network Resources */
/* ms899755 Determining if a Network Connection is Present */
/* ms881685 Determining Local and Remote Names */
/* ms881687 Determining the Status of One or More Sockets */
/* ms881700 DHCP Allocator */
/* ms881701 DHCP Allocator Operation */
/* ms881702 DhcpOptions */
/* ms881703 DhcpSendOptions */
/* ms881704 DHCPv6 Lite Registry Settings */
/* ms881705 DHCPv6 Non-Configurable Registry Settings */
/* ms881706 Diagnosing Connections */
/* ms899598 Diagnosing Connectivity Problems using the Network Connection Status UI */
/* ms886653 DNS Functions */
/* ms881714 DNS Proxy */
/* aa451151 DNS Proxy Registry Settings */
/* ms886655 DNS Reference */
/* ms886654 DNS Structures */
/* ms898953 Domain Discovery */
/* ms881715 Domain Discovery Application Development */
/* ms898954 Domain Discovery Functions */
/* ms881716 Domain Discovery Migration */
/* ms881717 Domain Discovery OS Design Development */
/* ms898955 Domain Discovery Reference */
/* ms881718 Domain Discovery Samples */
/* ms881719 Domain Discovery Security */
/* aa450365 Domain Discovery Structures */
/* ms881720 Dual Stack Architecture */
/* ms881721 Duplicate IP Address Detection for IPv4 */
/* ms881722 Duplicate IP Address Detection for IPv6 */
/* ms881854 EAP Application Development */
/* ms881723 EAP Authentication Protocols */
/* ms886656 EAP Enumerations */
/* ms886657 EAP Functions */
/* ms881724 EAP Implementation Details */
/* ms881725 EAP Initialization */
/* ms881726 EAP Installation */
/* ms898956 EAP Migration */
/* ms881855 EAP OS Design Development */
/* ms886658 EAP Reference */
/* ms881728 EAP Registry Settings */
/* ms898957 EAP Samples */
/* ms881729 EAP Security */
/* ms886659 EAP Structures */
/* ms881832 Enabling Auto Dial for ICS */
/* ms899760 Enabling IPv4 Routing */
/* ms899766 Enabling IPv6 Forwarding */
/* ms881834 Enabling IPv6 Routing */
/* ms881836 Enabling NAT */
/* ms881837 Enabling the DHCP Allocator */
/* ms881838 Enabling the DNS Proxy */
/* ms881839 Enhanced Functionality at Connect Time */
/* ms881842 Error Reporting and Parameter Validation */
/* ms881844 Establishing a Network Connection */
/* ms881851 Event Object Signaling */
/* ms881852 Event Objects in the Winsock SPI */
/* ms881849 EVENTLOG */
/* ms881853 Extended Byte-Order Conversion Routines */
/* ms898958 Extensible Authentication Protocol */
/* ms881863 FIREWALL */
/* ms898960 Firewall */
/* ms898961 Firewall Rule Examples */
/* ms881866 Flow Control Using ICMP for IPv4 */
/* ms881880 Function Interface Model */
/* ms898964 Gateway Logging */
/* ms881881 Gateway Logging Registry Settings */
/* ms898965 General Firewall Rule Examples */
/* ms881884 Generic Data Transport Functions */
/* ms881886 gethostbyaddr Function in the SPI */
/* ms881887 gethostbyname Function in the SPI */
/* ms881889 gethostname Function in the SPI */
/* ms881910 Host Name Resolution for Dual Stack (IPv4/IPv6) */
/* ms881909 Host Name Resolution for IPv4 */
/* ms881911 Host Name Resolution for IPv6 */
/* ms881912 Host Name Resolution Using a DNS Server for IPv4 */
/* ms881913 Host Name Resolution Using a NetBIOS Server for IPv4 */
/* ms881914 Host Name Resolution Using Registry Entries */
/* ms881908 HOSTNAME */
/* aa450273 How to Convert an Application from IPv4 to IPv4/IPv6 */
/* aa450274 How to Set Up and Use an IPv6 Test Lab */
/* ms886676 ICMP Functions */
/* ms886677 ICMP Reference */
/* ms886678 ICMP Structures */
/* ms898969 ICS Application Development */
/* ms886679 ICS Functions */
/* ms898966 ICS Migration */
/* aa450033 ICS OS Design Development */
/* ms886680 ICS Reference */
/* aa450034 ICS Registry Settings */
/* ms898967 ICS Samples */
/* aa450035 ICS Security */
/* ms881921 IKE Authentication */
/* ms881923 Implementing a Secure Socket */
/* aa450026 Installation Functions */
/* aa450110 Installing an LSP */
/* aa450032 Interactive User Interface */
/* ms898968 Internet Connection Sharing */
/* aa450037 Internet Control Message Protocol (ICMP) */
/* aa450036 Internet Control Message Protocol for IPv6 (ICMPv6) */
/* aa450038 Internet Group Management Protocol (IGMP) */
/* aa450041 Internet Protocol (IP) for IPv4 */
/* aa450042 Internet Protocol (IP) for IPv6 */
/* aa450040 Internet Protocol Helper APIs */
/* aa450043 Internet Protocol version 4 Address Classes */
/* ms898970 Internet Protocol Version 6 */
/* aa450046 Internet Router Discovery Protocol (IRDP) for IPv4 */
/* aa450053 IP Firewall Application Development */
/* ms886672 IP Firewall Data Types */
/* ms886673 IP Firewall Enumerations */
/* ms886674 IP Firewall Functions */
/* ms886684 IP Firewall Logging Reference */
/* aa450054 IP Firewall Logging Registry Settings */
/* aa450055 IP Firewall Migration */
/* aa450052 IP Firewall OS Design Development */
/* ms886685 IP Firewall Reference */
/* aa450056 IP Firewall Registry Settings */
/* aa450057 IP Firewall Samples */
/* aa450058 IP Firewall Security */
/* ms886675 IP Firewall Structures */
/* aa450059 IP Helper Code Samples */
/* ms886686 IP Helper Enumerations */
/* ms886687 IP Helper Functions */
/* ms886688 IP Helper Reference */
/* ms886689 IP Helper Structures */
/* ms898971 IP Independent Source Code Examples */
/* aa450060 IP Multicasting for IPv4 */
/* aa450061 IP Multicasting for IPv6 */
/* aa450062 IP NAT Registry Settings */
/* aa450050 IP/ARP Extensions for IPv4 Multicasting */
/* aa450051 IPConfig */
/* aa450063 IPPROTO_IP */
/* aa450064 IPPROTO_IPV6 */
/* aa450065 IPPROTO_TCP */
/* aa450066 IPPROTO_UDP */
/* aa450067 IPSec Application Development */
/* ms886690 IPSec Functions */
/* aa450068 IPSec Migration */
/* aa450069 IPSec OS Design Development */
/* ms886691 IPSec Reference */
/* aa450070 IPSec Registry Settings */
/* aa450071 IPSec Samples */
/* aa450072 IPSec Security */
/* ms886692 IPSec Structures */
/* ms898972 IPSec v4 */
/* aa450073 IPv4-only Client Code */
/* aa450074 IPv4-only Server Code */
/* ms898973 IPv4-only Source Code Examples */
/* aa450077 IPv6 */
/* aa450078 IPv6 Address Autoconfiguration */
/* aa450079 IPv6 Addresses */
/* aa450081 IPv6 Addresses to Configure */
/* aa450044 IPv6 Addressing */
/* aa450432 IPv6 adu */
/* aa450080 IPv6 and IPv4 Coexistence */
/* aa450087 IPv6 Application Development */
/* aa450084 IPv6 Characteristics */
/* ms900518 IPv6 dp6dns */
/* ms900530 IPv6 dp6domain */
/* ms900531 IPv6 dp6enum */
/* ms900540 IPv6 dp6pd */
/* ms900542 IPv6 dp6rf */
/* aa450433 IPv6 gp */
/* aa450434 IPv6 gpu */
/* aa450435 IPv6 gpu MaxTempDADAttempts */
/* aa450436 IPv6 gpu MaxTempLifetime */
/* aa450437 IPv6 gpu MaxTempRandomTime */
/* aa450438 IPv6 gpu NeighborCacheLimit */
/* aa450439 IPv6 gpu RouteCacheLimit */
/* aa450440 IPv6 gpu TempRandomTime */
/* aa450441 IPv6 gpu TempRegenerateTime */
/* aa450442 IPv6 gpu UseTemporaryAddresses */
/* aa450443 IPv6 if */
/* aa450445 IPv6 ifc */
/* aa450446 IPv6 ifd */
/* aa450083 IPv6 Implementations */
/* aa450085 IPv6 Interface Identifiers */
/* ms898974 Ipv6 Migration */
/* aa450447 IPv6 nc */
/* aa450448 IPv6 ncf */
/* ms898975 IPv6 OS Design Development */
/* aa450086 IPv6 Overview */
/* aa450045 IPv6 Packets */
/* aa450449 IPv6 ppd */
/* aa450450 IPv6 ppt */
/* aa450451 IPv6 ppu */
/* aa450452 IPv6 rc */
/* aa450453 IPv6 rcf */
/* aa450088 IPv6 References */
/* aa450454 IPv6 renew */
/* aa450089 IPv6 RFCs and Internet Drafts */
/* aa450455 IPv6 rlu */
/* aa450456 IPv6 rt */
/* aa450457 IPv6 rtu */
/* ms898976 Ipv6 Samples */
/* aa450090 IPv6 Security */
/* aa450458 IPv6 spt */
/* aa450459 IPv6 spu */
/* aa450091 IPv6 Test Lab Requirements */
/* aa450092 IPv6 Traffic Between Nodes in Different Sites Across the Internet (6to4) */
/* aa450093 IPv6 Traffic Between Nodes on Different Subnets of an IPv4 Internetwork */
/* aa450094 IPv6 Traffic Between Nodes on Different Subnets of an IPv6 Internetwork */
/* aa450075 IPv6-Enabled Client Code */
/* aa450076 IPv6-Enabled Server Code */
/* aa450460 IPv6tun */
/* aa450103 Joining and Leaving a Multicast Group */
/* aa450109 Layered Protocols and Provider Chains */
/* aa450114 Link Layer Functionality */
/* aa450115 Listing Addresses */
/* aa450117 Locating a Printer on a Network */
/* ms886695 Logging Blocked Inbound Packets */
/* aa450118 Machine Name to IP Address Maps */
/* aa450120 Maintaining Route Tables for IPv4 */
/* aa450121 Maintaining Route Tables for IPv6 */
/* aa450123 Managing Interfaces */
/* ms882519 Managing IP Addresses */
/* ms882649 Managing IPv4 Routes */
/* ms882660 Managing IPv6 Routes */
/* ms882630 Managing Network Adapters */
/* ms882641 Managing Network Connections with WNet */
/* ms882665 Managing Routing */
/* ms882681 Manually Configuring an IPv4 Address */
/* ms899789 Manually Configuring IPv6 Addresses */
/* ms882704 Mapping an IP Multicast Address */
/* ms882717 Maximum Transmission Unit (MTU) */
/* aa450082 Methods for Configuring IPv6 Addresses */
/* ms882787 Microsoft Challenge-Handshake Authentication Protocol 2.0 (MS CHAP V2) */
/* ms882814 MODULESLIST */
/* ms882863 Multicast Extensions to Windows Sockets */
/* ms882950 Multicast IPv6 Addresses */
/* ms882958 Multicast Listener Discovery (MLD) */
/* ms882965 Multihoming for IPv4 */
/* ms882973 Multihoming for IPv6 */
/* ms882984 Multiple Public Interface Support */
/* ms882991 Multiple Transport Protocols */
/* ms883014 Multipoint Attributes in the WSAPROTOCOL_INFOW Structure */
/* ms883026 Multipoint Socket Attributes */
/* ms883035 Multipoint Taxonomy and Glossary */
/* ms883043 Nagle Algorithm */
/* ms883051 Name Registration for IPv4 */
/* ms883059 Name Resolution and Winsock */
/* ms883065 Name Resolution Data Structures */
/* ms883073 Name Resolution Data Structures in the SPI */
/* ms883081 Name Resolution Division of Responsibilities Between DLL and Service Providers */
/* ms883100 Name Resolution for IPv4 Using the Cache */
/* ms883089 Name Resolution for IPv6 Using the Cache */
/* ms883096 Name Resolution Functions */
/* ms883098 Name Resolution Model */
/* ms883099 Name Resolution Service Provider Requirements */
/* ms883101 Namespace Organization */
/* ms883102 Namespace Provider Architecture */
/* ms883104 Namespace Provider Initialization and Cleanup */
/* ms883103 Namespace Provider Installation */
/* ms883106 Naming Conventions */
/* ms883107 NAT */
/* ms883108 NAT and Applications */
/* ms883109 NAT Editor */
/* ms883110 NAT Editor Functions */
/* ms883112 NAT Editor Initialization and Registration */
/* ms883113 NAT Editor Operation */
/* ms883114 NAT Firewall Packet Logging */
/* ms883121 NAT Packet Filter */
/* ms883122 NAT Traversal */
/* ms883123 NAT Traversal in Internet Gateways */
/* ms883124 NAT Traversal Operation */
/* ms883120 NATIVEWIFI */
/* ms898987 NDIS Packet Capturing */
/* ms883126 NDIS Packet Capturing Application Development */
/* ms883127 NDIS Packet Capturing Migration */
/* ms883125 NDIS Packet Capturing OS Development */
/* ms883128 NDIS Packet Capturing Security */
/* ms883129 Neighbor Discovery (ND) */
/* ms883130 NETLOG */
/* ms886701 Netlog */
/* ms883131 Netlogctl */
/* ms895675 Netstat */
/* ms883132 NETWORK */
/* ms883134 Network Address Translation */
/* ms898988 Network Bridging */
/* ms898989 Network Bridging Application Development */
/* ms883135 Network Bridging Architecture */
/* ms898990 Network Bridging Migration */
/* ms883136 Network Bridging Object Identifiers */
/* ms883137 Network Bridging OS Design Development */
/* ms883138 Network Bridging Queriable Object Identifiers */
/* ms898991 Network Bridging Reference */
/* ms883139 Network Bridging Registry Settings */
/* ms883140 Network Bridging Sample Registry Configuration */
/* ms898992 Network Bridging Samples */
/* ms883141 Network Bridging Security */
/* ms883142 Network Bridging Settable Object Identifiers */
/* ms883143 Network Bridging Spanning Tree Algorithm */
/* ms883144 Network Driver Interface Specification (NDIS) */
/* ms883145 Network Driver Interface Specification (NDIS) for IPv6 */
/* ms883146 Network Folder */
/* ms898997 Network Utilities */
/* ms898998 Network Utilities Application Development */
/* ms883147 Network Utilities Migration */
/* ms883148 Network Utilities OS Design Development */
/* ms883149 Network Utilities Samples */
/* ms899230 Network Utilities Security */
/* ms883150 Nonblocking Input/Output */
/* ms883151 Notification of Network Events */
/* ms883312 Obtaining Identity Information */
/* ms883321 Obtaining the Buffer Size */
/* ms883385 Operational Characteristics of NDIS Object Identifiers */
/* ms883386 Out-of-Band Data in the SPI */
/* ms883387 Overlapped Completion Indication Mechanisms */
/* ms883388 Overlapped Input/Output */
/* ms883390 Packet Data Handling and Editing */
/* ms883392 PARENTALCONTROLS */
/* ms883399 PASSWORD */
/* ms883400 Path Maximum Transmission Unit (PMTU) Discovery */
/* ms883419 Ping */
/* ms899797 Pinging a Host in the IPv6 Test Lab by Using a Link-Local Address */
/* ms883420 Plug and Play */
/* ms883430 Port States */
/* ms883428 PORTFORWARD */
/* ms883438 Printing on a Network */
/* ms883449 Protected Extensible Authentication Protocol (PEAP) */
/* ms883450 Protocol Basics: Listen, Connect, Accept */
/* ms883452 Protocol-Independent Multicast and Multipoint in the SPI */
/* ms883453 Protocol-Independent Name Resolution */
/* ms883460 RAS */
/* ms883461 RAS and Authentication Protocol Interaction During Authentication */
/* aa450124 Reading Socket Options */
/* aa450125 Receiving an IP Multicast Datagram */
/* aa450126 Receiving an IP Multicast Datagram Sample */
/* aa450129 Receiving Notification of Network Events */
/* aa450131 Reconnecting and Disconnecting */
/* ms899537 Reference Gateway User Interface */
/* aa450133 Reference Gateway User Interface Migration */
/* aa450134 Reference Gateway User Interface OS Design Development */
/* aa450135 Reference Gateway User Interface Samples */
/* aa450136 Reference Gateway User Interface Security */
/* ms899538 Remote Configuration Framework */
/* aa450149 Remote Configuration Framework Application Development */
/* ms899539 Remote Configuration Framework Interfaces */
/* aa450146 Remote Configuration Framework Migration */
/* ms881882 Remote Configuration Framework Modules */
/* ms899540 Remote Configuration Framework OS Design Development */
/* ms899541 Remote Configuration Framework Reference */
/* aa450145 Remote Configuration Framework Registry Settings */
/* aa450147 Remote Configuration Framework Samples */
/* aa450148 Remote Configuration Framework Security */
/* aa450150 REMOTEUTILS */
/* ms899806 Removing an IPv6 Route */
/* aa450229 Restricting Outbound Traffic to Selected TCP Ports */
/* aa450162 Retrieving a Connection Name */
/* aa450163 Retrieving a User Name */
/* aa450164 Retrieving Information About Network Configuration */
/* aa450181 Retrieving Network Data */
/* aa450182 Retrieving Network Errors */
/* ms900298 Retrieving Network Information */
/* aa450166 Retrieving Statistics for IP and ICMP */
/* aa450165 Retrieving Statistics for TCP and UDP */
/* aa450186 ROOTDIRS */
/* aa450187 Route */
/* aa450188 Routing for IPv4 */
/* aa450189 Routing for IPv6 */
/* ms899815 Running the Checkv4 Utility */
/* ms899823 Running the SimpleClient and SimpleServer Applications */
/* aa450194 Scatter/Gather I/O Support */
/* ms885824 Secure Socket Control Codes */
/* aa450204 Sending an IP Multicast Datagram */
/* aa450205 Sending an IP Multicast Datagram Sample */
/* aa450217 Service Installation in the Winsock SPI */
/* aa450219 Service Provider Activation */
/* aa450220 Service Query */
/* aa450221 Service Registry Settings */
/* ms884887 Setting a User Name and Password */
/* ms884896 Setting ForwardMetric Values */
/* ms884912 Shared Sockets in the SPI */
/* ms884916 Silly Window Syndrome (SWS) */
/* ms884918 Single Subnet with Link-Local Addresses */
/* ms884919 SIO_MULTICAST_SCOPE IOCTL */
/* ms884920 SIO_MULTIPOINT_LOOPBACK Ioctl */
/* ms884921 Slow Start Algorithm and Congestion Avoidance */
/* ms884922 SMBFILE */
/* ms884923 SMBPRINT */
/* ms884930 Socket Attribute Flags and Modes */
/* ms884931 Socket Client */
/* ms884933 Socket Connections on Connection-Oriented Protocols */
/* ms884932 Socket Connections on Connectionless Protocols */
/* ms884934 Socket Creation and Descriptor Management */
/* ms884935 Socket Functions */
/* ms884936 Socket I/O */
/* ms899548 Socket Options */
/* ms884937 Socket Options and IOCTLs */
/* ms884938 Socket Options Not Supported */
/* ms884939 Socket Server */
/* ms900408 SOL_IRLMP */
/* ms884940 SOL_SOCKET */
/* ms884941 Spanning Tree Algorithm Functionality */
/* ms884947 Static Port Mappings */
/* ms899832 Stream Socket Application */
/* ms899840 Submitting a Firewall for Certification */
/* ms884950 Summary of Namespace Provider Functions */
/* ms884951 Summary of Socket IOCTL Opcodes */
/* ms884952 Summary of SPI Functions */
/* ms884956 Support for Scatter/Gather Input/Output in the SPI */
/* ms884964 TCP Connections to and from Multihomed Computers */
/* ms884986 TCP Keep-Alive Messages */
/* ms884987 TCP Receive Window Size Calculation and Window Scaling */
/* ms884988 TCP Retransmission Behavior */
/* ms884989 TCP Selective Acknowledgment */
/* ms899549 TCP/IP */
/* ms884967 TCP/IP and Dial-up Support */
/* ms884974 TCP/IP and Dynamic DNS */
/* ms884970 TCP/IP and IP Helper */
/* ms884966 TCP/IP and the DHCP Client */
/* ms884968 TCP/IP and the DNS Client */
/* ms884983 TCP/IP and Windows Sockets */
/* ms884984 TCP/IP and WinHTTP */
/* ms884982 TCP/IP and WinInet */
/* ms884985 TCP/IP and WINS */
/* ms899552 TCP/IP Application Development */
/* ms880936 TCP/IP Architectural Model */
/* ms884965 TCP/IP Best Practices */
/* ms899550 TCP/IP Migration */
/* ms884971 TCP/IP OS Design Development */
/* ms884972 TCP/IP Protocol Suite */
/* ms899553 TCP/IP Reference */
/* ms884973 TCP/IP Registry Settings */
/* ms899554 TCP/IP Samples */
/* ms884975 TCP/IP Security */
/* ms884969 TCP/IP Support in Windows CE */
/* ms884976 TCP/IPv4 and TCP/IPv6 Common Registry Settings */
/* ms884977 TCP/IPv4 Configurable Registry Settings */
/* ms900416 TCP/IPv4 Device Name Registry Settings */
/* ms884978 TCP/IPv4 Non-Configurable Registry Settings */
/* ms884979 TCP/IPv6 Architectural Model */
/* ms884980 TCP/IPv6 Configurable Registry Settings */
/* ms884981 TCP/IPv6 Registry Settings */
/* ms899556 TCP/IPv6 Troubleshooting Tools */
/* ms885274 Terminating a Network Connection */
/* ms899850 Testing an IPv6 Connection by Using the Ping Command */
/* ms899868 Testing IPv6 Connectivity by Using the Ping Command */
/* ms899882 Testing your Application or Device in an IPv6 Environment */
/* ms885292 Throughput Considerations */
/* ms885298 TIMESERVICE */
/* ms885306 Timestamps (RFC 1323) */
/* aa450971 Tracert */
/* ms885312 Transmission Control Protocol (TCP) */
/* ms885323 Transport Installation */
/* ms885336 Transport Level Security (TLS) */
/* ms885344 Transport Mapping Between API and SPI Functions */
/* ms885352 Transport Service Providers */
/* ms899599 Troubleshooting IPv6 */
/* ms899600 Troubleshooting: Setting Up and Using the IPv6 Test Lab */
/* ms885359 Unicast IPv6 Addresses */
/* ms885421 Upcalls Exposed by Ws2.dll */
/* ms900593 USB Flash Config Tool */
/* ms900441 USB Flash Config Tool Architecture */
/* ms900595 USB Flash Config Tool Migration */
/* ms900443 USB Flash Config Tool OS Design Development */
/* ms900447 USB Flash Config Tool Registry Settings */
/* ms900597 USB Flash Config Tool Samples */
/* ms900450 USB Flash Config Tool Security */
/* ms885768 Use of ICMP to Diagnose Problems for IPv4 */
/* ms885769 Use of IGMP by Windows CE */
/* ms885773 User Datagram Protocol (UDP) */
/* ms885774 User Datagram Protocol (UDP) and Name Resolution for IPv4 */
/* ms885775 USERS */
/* ms885776 Using a Deferred Handshake */
/* ms885778 Using Event Objects */
/* ms885779 Using IPV6_PROTECTION_LEVEL */
/* ms900101 Using Temporary Addresses in the IPv6 Test Lab */
/* ms885783 Using the Address Resolution Protocol */
/* ms885781 Using the Remote Configuration Framework */
/* ms885789 Using WSAStartup to Initialize Winsock */
/* ms885790 VERSION */
/* ms900107 Viewing Interface Information */
/* ms900114 Viewing the IPv6 Routing Table */
/* ms900123 Viewing the Neighbor Cache */
/* ms900128 Viewing the Route Cache */
/* ms885794 WATSON */
/* ms899584 Windows Networking API/Redirector */
/* ms885813 Windows Networking API/Redirector Application Development */
/* aa450259 Windows Networking API/Redirector Functions */
/* ms885814 Windows Networking API/Redirector Migration */
/* ms899585 Windows Networking API/Redirector OS Design Development */
/* aa450260 Windows Networking API/Redirector Reference */
/* aa450132 Windows Networking API/Redirector Registry Settings */
/* ms885815 Windows Networking API/Redirector Samples */
/* ms885816 Windows Networking API/Redirector Security */
/* aa450261 Windows Networking API/Redirector Structures */
/* ms899586 Windows Sockets */
/* ms898578 Windows Sockets Reference */
/* ms885818 Windows Sockets Support for IPv6 */
/* ms885819 Windows-Specific Extension Functions */
/* ms885820 Winsock 2.2 */
/* ms885822 Winsock and WOSA */
/* ms899587 Winsock Application Development */
/* ms885821 Winsock Architecture */
/* ms885823 Winsock Completion Indications */
/* aa450262 Winsock Enumerations */
/* aa450263 Winsock Error Codes */
/* ms885825 Winsock Event Objects */
/* aa450264 Winsock Functions */
/* ms886607 Winsock Migration */
/* ms886615 Winsock Name Resolution */
/* ms885817 Winsock OS Design Development */
/* ms886617 Winsock Overlapped I/O and Event Objects */
/* aa450265 Winsock Reference */
/* ms899596 Winsock Samples */
/* ms886618 Winsock Secure Sockets */
/* ms886619 Winsock Security */
/* ms886620 Winsock Service Provider Interface (SPI) */
/* ms886621 Winsock Service Providers */
/* aa450266 Winsock SPI Functions */
/* aa450267 Winsock SPI Reference */
/* aa450269 Winsock Structures */
/* ms886481 Winsock Support in Windows CE */
/* ------------------------------------------------------------------
 * Book surface: wsock-structures (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa450370 fd_set (Header: Winsock2.h.) */
/* ms890319 hostent (Header: Winsock2.h.) */
/* ms890973 in_addr (Header: Winsock2.h.) */
/* ms894561 linger (Header: Winsock2.h.) */
/* ms896341 protoent (Header: Winsock2.h.) */
/* aa450886 servent (Header: Winsock2.h.) */
/* aa450942 sockaddr (Header: Winsock2.h.) */
/* aa450946 sockaddr_in (Header: Winsock2.h.) */
/* aa450970 timeval (Header: Winsock2.h.) */
#endif  /* _WINSOCK2_H */
