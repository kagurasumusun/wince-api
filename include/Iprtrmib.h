/* Iprtrmib.h -- MIB II router structures (IP Helper, Windows CE).
 * Pages: tools/manifests/netgen.manifest (Networking - General);
 * used by the Iphlpapi.h functions (Iphlpapi.lib).  Size constants
 * MAX_INTERFACE_NAME_LEN, MAXLEN_PHYSADDR and ANY_SIZE are not
 * published on any CE page -- the structs that need them are
 * recorded verbatim and kept pointer-only.  See docs/inventory.md
 * M77a.
 */

#ifndef AKARI_IPRTRMIB_H
#define AKARI_IPRTRMIB_H

#include "Windef.h"    /* DWORD, BYTE, WCHAR, ULONG */

/* ms895078 "MIBICMPSTATS" / ms895077 "MIBICMPINFO" / ms895075
 * "MIB_ICMP" (print `typedef struct_MIB_ICMP {MIBICMPINFOstats;}`)
 * -- all-DWORD, compiled as printed. */
typedef struct _MIBICMPSTATS {
    DWORD dwMsgs;
    DWORD dwErrors;
    DWORD dwDestUnreachs;
    DWORD dwTimeExcds;
    DWORD dwParmProbs;
    DWORD dwSrcQuenchs;
    DWORD dwRedirects;
    DWORD dwEchos;
    DWORD dwEchoReps;
    DWORD dwTimestamps;
    DWORD dwTimestampReps;
    DWORD dwAddrMasks;
    DWORD dwAddrMaskReps;
} MIBICMPSTATS;

typedef struct _MIBICMPINFO {
    MIBICMPSTATS icmpInStats;
    MIBICMPSTATS icmpOutStats;
} MIBICMPINFO;

typedef struct _MIB_ICMP {
    MIBICMPINFO stats;   /* print spells `MIBICMPINFOstats;` */
} MIB_ICMP, *PMIB_ICMP;

/* ms895069 "MIB_IPADDRROW": all-DWORD (+unsigned short), compiled. */
typedef struct _MIB_IPADDRROW {
    DWORD          dwAddr;
    DWORD          dwIndex;
    DWORD          dwMask;
    DWORD          dwBCastAddr;
    DWORD          dwReasmSize;
    unsigned short unused1;
    unsigned short unused2;
} MIB_IPADDRROW, *PMIB_IPADDRROW;

/* ms894631 "MIB_IPFORWARDROW": all-DWORD, compiled. */
typedef struct _MIB_IPFORWARDROW {
    DWORD dwForwardDest;
    DWORD dwForwardMask;
    DWORD dwForwardPolicy;
    DWORD dwForwardNextHop;
    DWORD dwForwardIfIndex;
    DWORD dwForwardType;
    DWORD dwForwardProto;
    DWORD dwForwardAge;
    DWORD dwForwardNextHopAS;
    DWORD dwForwardMetric1;
    DWORD dwForwardMetric2;
    DWORD dwForwardMetric3;
    DWORD dwForwardMetric4;
    DWORD dwForwardMetric5;
} MIB_IPFORWARDROW, *PMIB_IPFORWARDROW;

/* ms895076 "MIB_IPSTATS": all-DWORD, compiled. */
typedef struct _MIB_IPSTATS {
    DWORD dwForwarding;
    DWORD dwDefaultTTL;
    DWORD dwInReceives;
    DWORD dwInHdrErrors;
    DWORD dwInAddrErrors;
    DWORD dwForwDatagrams;
    DWORD dwInUnknownProtos;
    DWORD dwInDiscards;
    DWORD dwInDelivers;
    DWORD dwOutRequests;
    DWORD dwRoutingDiscards;
    DWORD dwOutDiscards;
    DWORD dwOutNoRoutes;
    DWORD dwReasmTimeout;
    DWORD dwReasmReqds;
    DWORD dwReasmOks;
    DWORD dwReasmFails;
    DWORD dwFragOks;
    DWORD dwFragFails;
    DWORD dwFragCreates;
    DWORD dwNumIf;
    DWORD dwNumAddr;
    DWORD dwNumRoutes;
} MIB_IPSTATS, *PMIB_IPSTATS;

/* ms895087 "MIB_PROXYARP": all-DWORD, compiled. */
typedef struct _MIB_PROXYARP {
    DWORD dwAddress;
    DWORD dwMask;
    DWORD dwIfIndex;
} MIB_PROXYARP, *PMIB_PROXYARP;

/* ms895082 "MIB_TCPROW" / ms895084 "MIB_TCPSTATS": compiled. */
typedef struct _MIB_TCPROW {
    DWORD dwState;
    DWORD dwLocalAddr;
    DWORD dwLocalPort;
    DWORD dwRemoteAddr;
    DWORD dwRemotePort;
} MIB_TCPROW, *PMIB_TCPROW;

typedef struct _MIB_TCPSTATS {
    DWORD dwRtoAlgorithm;
    DWORD dwRtoMin;
    DWORD dwRtoMax;
    DWORD dwMaxConn;
    DWORD dwActiveOpens;
    DWORD dwPassiveOpens;
    DWORD dwAttemptFails;
    DWORD dwEstabResets;
    DWORD dwCurrEstab;
    DWORD dwInSegs;
    DWORD dwOutSegs;
    DWORD dwRetransSegs;
    DWORD dwInErrs;
    DWORD dwOutRsts;
    DWORD dwNumConns;
} MIB_TCPSTATS, *PMIB_TCPSTATS;

/* ms895092 "MIB_UDPROW" / ms895093 "MIB_UDPSTATS": compiled. */
typedef struct _MIB_UDPROW {
    DWORD dwLocalAddr;
    DWORD dwLocalPort;
} MIB_UDPROW, *PMIB_UDPROW;

typedef struct _MIB_UDPSTATS {
    DWORD dwInDatagrams;
    DWORD dwNoPorts;
    DWORD dwInErrors;
    DWORD dwOutDatagrams;
    DWORD dwNumAddrs;
} MIB_UDPSTATS, *PMIB_UDPSTATS;

/* --- Pointer-only (unpublished size constants); verbatim records. --
 * ms895071 "MIB_IFROW": `typedef struct _MIB_IFROW {WCHAR
 * wszName[MAX_INTERFACE_NAME_LEN];DWORD dwIndex;DWORD dwType;
 * DWORD dwMtu;DWORD dwSpeed;DWORD dwPhysAddrLen;
 * BYTE bPhysAddr[MAXLEN_PHYSADDR];DWORD dwAdminStatus;
 * DWORD dwOperStatus;DWORD dwLastChange;DWORD dwInOctets;...
 *   (MAX_INTERFACE_NAME_LEN / MAXLEN_PHYSADDR unpublished)
 * Tables (dwNumEntries + row table[ANY_SIZE]; ANY_SIZE unpublished):
 *   ms895073 MIB_IFTABLE {DWORD dwNumEntries; MIB_IFROWtable[ANY_SIZE];}
 *   ms895068 MIB_IPADDRTABLE {DWORD dwNumEntries;MIB_IPADDRROWtable[ANY_SIZE];}
 *   ms894632 MIB_IPFORWARDTABLE {DWORD dwNumEntries;MIB_IPFORWARDROWtable[ANY_SIZE];}
 *   ms895079 MIB_IPNETROW {DWORD dwIndex;DWORD dwPhysAddrLen;
 *     BYTE bPhysAddr[MAXLEN_PHYSADDR];DWORD dwAddr;DWORD dwType;}
 *   ms895080 MIB_IPNETTABLE {DWORD dwNumEntries;MIB_IPNETROWtable[ANY_SIZE];}
 *   ms895083 MIB_TCPTABLE {DWORD dwNumEntries; MIB_TCPROW table[ANY_SIZE];}
 *   ms895094 MIB_UDPTABLE {DWORD dwNumEntries;MIB_UDPROWtable[ANY_SIZE];} */
typedef struct _MIB_IFROW MIB_IFROW, *PMIB_IFROW;
typedef struct _MIB_IFTABLE MIB_IFTABLE, *PMIB_IFTABLE;
typedef struct _MIB_IPADDRTABLE MIB_IPADDRTABLE, *PMIB_IPADDRTABLE;
typedef struct _MIB_IPFORWARDTABLE MIB_IPFORWARDTABLE, *PMIB_IPFORWARDTABLE;
typedef struct _MIB_IPNETROW MIB_IPNETROW, *PMIB_IPNETROW;
typedef struct _MIB_IPNETTABLE MIB_IPNETTABLE, *PMIB_IPNETTABLE;
typedef struct _MIB_TCPTABLE MIB_TCPTABLE, *PMIB_TCPTABLE;
typedef struct _MIB_UDPTABLE MIB_UDPTABLE, *PMIB_UDPTABLE;

#endif /* AKARI_IPRTRMIB_H */
