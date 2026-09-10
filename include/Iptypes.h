/* Iptypes.h -- IP Helper adapter types (Windows CE).
 * Pages: tools/manifests/netgen.manifest.  The MAX_ADAPTER_* /
 * MAX_HOSTNAME_LEN family of size constants is not published on
 * any CE page -- IP_ADAPTER_INFO, FIXED_INFO and
 * IP_ADAPTER_ADDRESSES are recorded verbatim and kept pointer-only.
 * See docs/inventory.md M77a.
 */

#ifndef AKARI_IPTYPES_H
#define AKARI_IPTYPES_H

#include "Windef.h"    /* DWORD, UINT, BYTE, ULONG, ULONGLONG, PCHAR */
#include "Winsock2.h"  /* SOCKET_ADDRESS */

/* ms895038 "IP_ADDRESS_STRING": print
 * `typedef struct { char String[4 * 4];} IP_ADDRESS_STRING,
 * *PIP_ADDRESS_STRING, IP_MASK_STRING, *PIP_MASK_STRING;` */
typedef struct {
    char String[4 * 4];
} IP_ADDRESS_STRING, *PIP_ADDRESS_STRING, IP_MASK_STRING, *PIP_MASK_STRING;

/* ms891175 "IP_ADDR_STRING": print. */
typedef struct _IP_ADDR_STRING {
    struct _IP_ADDR_STRING *Next;
    IP_ADDRESS_STRING       IpAddress;
    IP_MASK_STRING          IpMask;
    DWORD                   Context;
} IP_ADDR_STRING, *PIP_ADDR_STRING;

/* ms895046 "IP_PER_ADAPTER_INFO": print. */
typedef struct _IP_PER_ADAPTER_INFO {
    UINT            AutoconfigEnabled;
    UINT            AutoconfigActive;
    IP_ADDR_STRING *CurrentDnsServer;
    IP_ADDR_STRING  DnsServerList;
} IP_PER_ADAPTER_INFO, *PIP_PER_ADAPTER_INFO;

/* ms890886 "IF_OPER_STATUS": print (explicit values). */
typedef enum {
    IfOperStatusUp = 1,
    IfOperStatusDown,
    IfOperStatusTesting,
    IfOperStatusUnknown,
    IfOperStatusDormant,
    IfOperStatusNotPresent,
    IfOperStatusLowerLayerDown
} IF_OPER_STATUS;

/* ms891176 "IP_DAD_STATE": print (explicit values). */
typedef enum {
    IpDadStateInvalid = 0,
    IpDadStateTentative,
    IpDadStateDuplicate,
    IpDadStateDeprecated,
    IpDadStatePreferred
} IP_DAD_STATE;

/* ms895049 "IP_PREFIX_ORIGIN": print (explicit values). */
typedef enum {
    IpPrefixOriginOther = 0,
    IpPrefixOriginManual,
    IpPrefixOriginWellKnown,
    IpPrefixOriginDhcp,
    IpPrefixOriginRouterAdvertisement
} IP_PREFIX_ORIGIN;

/* ms895051 "IP_SUFFIX_ORIGIN": print (explicit values). */
typedef enum {
    IpSuffixOriginOther = 0,
    IpSuffixOriginManual,
    IpSuffixOriginWellKnown,
    IpSuffixOriginDhcp,
    IpSuffixOriginLinkLayerAddress,
    IpSuffixOriginRandom
} IP_SUFFIX_ORIGIN;

/* ms895055 "SCOPE_LEVEL": print (explicit values). */
typedef enum {
    ScopeLevelInterface = 1,
    ScopeLevelLink = 2,
    ScopeLevelSubnet = 3,
    ScopeLevelAdmin = 4,
    ScopeLevelSite = 5,
    ScopeLevelOrganization = 8,
    ScopeLevelGlobal = 14
} SCOPE_LEVEL;

/* ms891173 "IP_ADAPTER_UNICAST_ADDRESS": print (typedef-name
 * placement `} IP_ADAPTER_UNICAST_ADDRESS*, PIP_ADAPTER...;` is a
 * doc typo for `} IP_ADAPTER_UNICAST_ADDRESS, *PIP_...;`). */
typedef struct _IP_ADAPTER_UNICAST_ADDRESS {
    union {
        ULONGLONG Alignment;
        struct { ULONG Length; DWORD Flags; };
    };
    struct _IP_ADAPTER_UNICAST_ADDRESS *Next;
    SOCKET_ADDRESS      Address;
    IP_PREFIX_ORIGIN    PrefixOrigin;
    IP_SUFFIX_ORIGIN    SuffixOrigin;
    IP_DAD_STATE        DadState;
    ULONG               ValidLifetime;
    ULONG               PreferredLifetime;
    ULONG               LeaseLifetime;
} IP_ADAPTER_UNICAST_ADDRESS, *PIP_ADAPTER_UNICAST_ADDRESS;

/* ms891168 "IP_ADAPTER_ANYCAST_ADDRESS": print. */
typedef struct _IP_ADAPTER_ANYCAST_ADDRESS {
    union {
        ULONGLONG Alignment;
        struct { ULONG Length; DWORD Flags; };
    };
    struct _IP_ADAPTER_ANYCAST_ADDRESS *Next;
    SOCKET_ADDRESS Address;
} IP_ADAPTER_ANYCAST_ADDRESS, *PIP_ADAPTER_ANYCAST_ADDRESS;

/* ms891171 "IP_ADAPTER_MULTICAST_ADDRESS": print. */
typedef struct _IP_ADAPTER_MULTICAST_ADDRESS {
    union {
        ULONGLONG Alignment;
        struct { ULONG Length; DWORD Flags; };
    };
    struct _IP_ADAPTER_MULTICAST_ADDRESS *Next;
    SOCKET_ADDRESS Address;
} IP_ADAPTER_MULTICAST_ADDRESS, *PIP_ADAPTER_MULTICAST_ADDRESS;

/* ms891172 "IP_ADAPTER_PREFIX": print. */
typedef struct _IP_ADAPTER_PREFIX {
    union {
        ULONGLONG Alignment;
        struct { ULONG Length; DWORD Flags; };
    };
    struct _IP_ADAPTER_PREFIX *Next;
    SOCKET_ADDRESS Address;
    ULONG          PrefixLength;
} IP_ADAPTER_PREFIX, *PIP_ADAPTER_PREFIX;

/* --- Record-only (unpublished size constants). ------------------
 * ms895039 "IP_ADAPTER_INFO": `typedef struct _IP_ADAPTER_INFO{
 * struct _IP_ADAPTER_INFO* Next;DWORD ComboIndex;
 * Char AdapterName[MAX_ADAPTER_NAME_LENGTH + 4];
 * char Description[MAX_ADAPTER_DESCRIPTION_LENGTH + 4];
 * UINT AddressLength;BYTE Address[MAX_ADAPTER_ADDRESS_LENGTH];
 * DWORD Index;UINT Type;UINT DhcpEnabled;PIP_ADDR_STRING Current...
 *   (MAX_ADAPTER_NAME_LENGTH / MAX_ADAPTER_DESCRIPTION_LENGTH /
 *   MAX_ADAPTER_ADDRESS_LENGTH unpublished)
 * ms895035 "FIXED_INFO": `typedef struct {charHostName
 * [MAX_HOSTNAME_LEN + 4];charDomainName [MAX_DOMAIN_NAME_LEN + 4];
 * PIP_ADDR_STRINGCurrentDnsServer;IP_ADDR_STRINGDnsServerList;
 * UINTNodeType;charScopeId [MAX_SCOPE_ID_LEN + 4];UINTEnableRouting;
 * UINTEnableProxy;UINTEnableDns;}FIXED_INFO,*PFIXED_INFO;`
 *   (MAX_HOSTNAME_LEN / MAX_DOMAIN_NAME_LEN / MAX_SCOPE_ID_LEN
 *   unpublished)
 * ms891167 "IP_ADAPTER_ADDRESSES": `typedef struct
 * _IP_ADAPTER_ADDRESSES {union {ULONGLONG Alignment; struct
 * {ULONGLength;DWORDIfIndex;};};struct _IP_ADAPTER_ADDRESSES*Next;
 * PCHARAdapterName;PIP_ADAPTER_UNICAST_ADDRESSFirstUnicastAddress;
 * PIP_ADAPTER_ANYCAST_ADDRESSFirstAnycastAddress;
 * PIP_ADAPTER_MULTICAST_ADDRESSFirstMulticastAddress;
 * PIP_ADAPTER_DNS_SERVER_ADDRESSFirstDnsServerAddress;
 * PWCHARDnsSuffix;PWCHARDescription;PWCHARFriendlyName;
 * BYTE PhysicalAddress[MAX_ADAPTER_ADDRESS_LENGTH];
 * DWORDPhysicalAddressLength;DWORD Flags; DWORDMtu;DWORDIfType;
 * IF_OPER_STATUSOperStatus; DWORD Ipv6IfIndex; DWORD ZoneIndices[16];
 * PIP_ADAPTER_PREFIX FirstPrefix; } IP_ADAPTER_ADDRESSES,
 * *PIP_ADAPTER_ADDRESSES;` -- MAX_ADAPTER_ADDRESS_LENGTH and the
 * IP_ADAPTER_DNS_SERVER_ADDRESS type are unpublished. */
typedef struct _IP_ADAPTER_INFO IP_ADAPTER_INFO, *PIP_ADAPTER_INFO;
/* FIXED_INFO print is tagless -- closed on its own typedef name. */
typedef struct FIXED_INFO FIXED_INFO, *PFIXED_INFO;
typedef struct _IP_ADAPTER_ADDRESSES IP_ADAPTER_ADDRESSES, *PIP_ADAPTER_ADDRESSES;

#endif /* AKARI_IPTYPES_H */
