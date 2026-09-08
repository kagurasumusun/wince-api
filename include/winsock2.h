/* winsock2.h -- Windows Sockets (Winsock 2.2) for Windows CE.
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
 *      is not officially published (SOL_SOCKET, SOL_IRLMP, the
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

#include "windef.h"   /* DWORD, BOOL, WORD, HANDLE, LPVOID, LPINT, LPDWORD, MAKEWORD */
#include "winnt.h"    /* GUID (WSAPROTOCOL_INFO.ProviderId) */

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

#endif  /* _WINSOCK2_H */
