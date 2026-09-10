/* Iphlpapi.h -- IP Helper API (Windows CE .NET 4.0+).
 *
 * Pages: tools/manifests/netgen.manifest (Networking - General);
 * Link Library rows print Iphlpapi.lib (def/iphlpapi-doc.def).
 * See docs/inventory.md M77a.
 */

#ifndef AKARI_IPHLPAPI_H
#define AKARI_IPHLPAPI_H

#include "Windef.h"    /* DWORD, ULONG, UINT, BOOL, PDWORD, PVOID */
#include "Winbase.h"   /* PHANDLE, LPOVERLAPPED, LPWSTR */
#include "Iptypes.h"     /* IP_ADAPTER_INFO, FIXED_INFO,
                          * IP_PER_ADAPTER_INFO, IP_ADAPTER_ADDRESSES */
#include "Iprtrmib.h"    /* MIB_* rows/tables */
#include "Ipexport.h"    /* IP_INTERFACE_INFO, IP_ADAPTER_INDEX_MAP,
                          * IP_UNIDIRECTIONAL_ADAPTER_ADDRESS */
#include "Winsock2.h"    /* struct sockaddr (GetBestInterfaceEx) */

/* --- Functions (Iphlpapi.lib -> def/iphlpapi-doc.def). ---------- */

/* ms887916 "CreateIpForwardEntry" */
AKARI_CE_IMPORT DWORD CreateIpForwardEntry(PMIB_IPFORWARDROW pRoute) AKARI_CE_NAME(CreateIpForwardEntry);

/* aa450325 "DeleteIpForwardEntry" */
AKARI_CE_IMPORT DWORD DeleteIpForwardEntry(PMIB_IPFORWARDROW pRoute) AKARI_CE_NAME(DeleteIpForwardEntry);

/* aa450922 "SetIpForwardEntry" */
AKARI_CE_IMPORT DWORD SetIpForwardEntry(PMIB_IPFORWARDROW pRoute) AKARI_CE_NAME(SetIpForwardEntry);

/* ms887917 "CreateIpNetEntry" */
AKARI_CE_IMPORT DWORD CreateIpNetEntry(PMIB_IPNETROW pArpEntry) AKARI_CE_NAME(CreateIpNetEntry);

/* aa450326 "DeleteIpNetEntry" */
AKARI_CE_IMPORT DWORD DeleteIpNetEntry(PMIB_IPNETROW pArpEntry) AKARI_CE_NAME(DeleteIpNetEntry);

/* aa450924 "SetIpNetEntry" */
AKARI_CE_IMPORT DWORD SetIpNetEntry(PMIB_IPNETROW pArpEntry) AKARI_CE_NAME(SetIpNetEntry);

/* ms887918 "CreateProxyArpEntry" */
AKARI_CE_IMPORT DWORD CreateProxyArpEntry(DWORD dwAddress, DWORD dwMask, DWORD dwIfIndex) AKARI_CE_NAME(CreateProxyArpEntry);

/* aa450327 "DeleteProxyArpEntry" */
AKARI_CE_IMPORT DWORD DeleteProxyArpEntry(DWORD dwAddress, DWORD dwMask, DWORD dwIfIndex) AKARI_CE_NAME(DeleteProxyArpEntry);

/* aa450382 "FlushIpNetTable" */
AKARI_CE_IMPORT DWORD FlushIpNetTable(DWORD dwIfIndex) AKARI_CE_NAME(FlushIpNetTable);

/* aa450394 "GetAdaptersInfo" */
AKARI_CE_IMPORT DWORD GetAdaptersInfo(PIP_ADAPTER_INFO pAdapterInfo, PULONG pOutBufLen) AKARI_CE_NAME(GetAdaptersInfo);

/* aa450393 "GetAdaptersAddresses" */
AKARI_CE_IMPORT DWORD GetAdaptersAddresses(ULONG Family, DWORD Flags, PVOID Reserved,
                    PIP_ADAPTER_ADDRESSES pAdapterAddresses,
                    PULONG pOutBufLen) AKARI_CE_NAME(GetAdaptersAddresses);

/* aa450392 "GetAdapterIndex" */
AKARI_CE_IMPORT DWORD GetAdapterIndex(LPWSTR AdapterName, PULONG IfIndex) AKARI_CE_NAME(GetAdapterIndex);

/* aa450397 "GetBestInterfaceEx" (page spells it GetBestInterfaceEX) */
AKARI_CE_IMPORT DWORD GetBestInterfaceEx(struct sockaddr *pDestAddr, PDWORD pdwBestIfIndex) AKARI_CE_NAME(GetBestInterfaceEx);

/* aa450398 "GetBestRoute" */
AKARI_CE_IMPORT DWORD GetBestRoute(DWORD dwDestAddr, DWORD dwSourceAddr,
                    PMIB_IPFORWARDROW pBestRoute) AKARI_CE_NAME(GetBestRoute);

/* aa450401 "GetFriendlyIfIndex" */
AKARI_CE_IMPORT DWORD GetFriendlyIfIndex(DWORD IfIndex) AKARI_CE_NAME(GetFriendlyIfIndex);

/* aa450406 "GetIcmpStatistics" */
AKARI_CE_IMPORT DWORD GetIcmpStatistics(PMIB_ICMP pStats) AKARI_CE_NAME(GetIcmpStatistics);

/* aa450407 "GetIcmpStatisticsEx" */
AKARI_CE_IMPORT DWORD GetIcmpStatisticsEx(PMIB_ICMP pStats, DWORD dwFamily) AKARI_CE_NAME(GetIcmpStatisticsEx);

/* aa450408 "GetIfEntry" */
AKARI_CE_IMPORT DWORD GetIfEntry(PMIB_IFROW pIfRow) AKARI_CE_NAME(GetIfEntry);

/* aa450409 "GetIfTable" */
AKARI_CE_IMPORT DWORD GetIfTable(PMIB_IFTABLE pIfTable, PULONG pdwSize, BOOL bOrder) AKARI_CE_NAME(GetIfTable);

/* aa450410 "GetInterfaceInfo" */
AKARI_CE_IMPORT DWORD GetInterfaceInfo(PIP_INTERFACE_INFO pIfTable, PULONG dwOutBufLen) AKARI_CE_NAME(GetInterfaceInfo);

/* aa450411 "GetIpAddrTable" */
AKARI_CE_IMPORT DWORD GetIpAddrTable(PMIB_IPADDRTABLE pIpAddrTable, PULONG pdwSize,
                    BOOL bOrder) AKARI_CE_NAME(GetIpAddrTable);

/* aa450412 "GetIpForwardTable" */
AKARI_CE_IMPORT DWORD GetIpForwardTable(PMIB_IPFORWARDTABLE pIpForwardTable,
                    PULONG pdwSize, BOOL bOrder) AKARI_CE_NAME(GetIpForwardTable);

/* aa450413 "GetIpNetTable" */
AKARI_CE_IMPORT DWORD GetIpNetTable(PMIB_IPNETTABLE pIpNetTable, PULONG pdwSize,
                    BOOL bOrder) AKARI_CE_NAME(GetIpNetTable);

/* aa450414 "GetIpStatistics" */
AKARI_CE_IMPORT DWORD GetIpStatistics(PMIB_IPSTATS pStats) AKARI_CE_NAME(GetIpStatistics);

/* aa450415 "GetIpStatisticsEx" */
AKARI_CE_IMPORT DWORD GetIpStatisticsEx(PMIB_IPSTATS pStats, DWORD dwFamily) AKARI_CE_NAME(GetIpStatisticsEx);

/* aa450417 "GetNetworkParams" */
AKARI_CE_IMPORT DWORD GetNetworkParams(FIXED_INFO *pFixedInfo, PULONG pOutBufLen) AKARI_CE_NAME(GetNetworkParams);

/* aa450418 "GetNumberOfInterfaces" */
AKARI_CE_IMPORT DWORD GetNumberOfInterfaces(PDWORD pdwNumIf) AKARI_CE_NAME(GetNumberOfInterfaces);

/* aa450421 "GetPerAdapterInfo" */
AKARI_CE_IMPORT DWORD GetPerAdapterInfo(ULONG IfIndex,
                    PIP_PER_ADAPTER_INFO pPerAdapterInfo,
                    PULONG pOutBufLen) AKARI_CE_NAME(GetPerAdapterInfo);

/* ms890306 "GetTcpStatistics" */
AKARI_CE_IMPORT DWORD GetTcpStatistics(PMIB_TCPSTATS pStats) AKARI_CE_NAME(GetTcpStatistics);

/* ms890307 "GetTcpStatisticsEx" */
AKARI_CE_IMPORT DWORD GetTcpStatisticsEx(PMIB_TCPSTATS pStats, DWORD dwFamily) AKARI_CE_NAME(GetTcpStatisticsEx);

/* ms890308 "GetTcpTable" */
AKARI_CE_IMPORT DWORD GetTcpTable(PMIB_TCPTABLE pTcpTable, PDWORD pdwSize, BOOL bOrder) AKARI_CE_NAME(GetTcpTable);

/* ms890309 "GetUdpStatistics" */
AKARI_CE_IMPORT DWORD GetUdpStatistics(PMIB_UDPSTATS pStats) AKARI_CE_NAME(GetUdpStatistics);

/* ms890310 "GetUdpStatisticsEx" */
AKARI_CE_IMPORT DWORD GetUdpStatisticsEx(PMIB_UDPSTATS pStats, DWORD dwFamily) AKARI_CE_NAME(GetUdpStatisticsEx);

/* ms890311 "GetUdpTable" */
AKARI_CE_IMPORT DWORD GetUdpTable(PMIB_UDPTABLE pUdpTable, PDWORD pdwSize, BOOL bOrder) AKARI_CE_NAME(GetUdpTable);

/* ms890312 "GetUniDirectionalAdapterInfo" */
AKARI_CE_IMPORT DWORD GetUniDirectionalAdapterInfo(PIP_UNIDIRECTIONAL_ADAPTER_ADDRESS pIPIfInfo,
                    PULONG dwOutBufLen) AKARI_CE_NAME(GetUniDirectionalAdapterInfo);

/* aa450426 "IpReleaseAddress" */
AKARI_CE_IMPORT DWORD IpReleaseAddress(PIP_ADAPTER_INDEX_MAP Adapter) AKARI_CE_NAME(IpReleaseAddress);

/* aa450427 "IpRenewAddress" */
AKARI_CE_IMPORT DWORD IpRenewAddress(PIP_ADAPTER_INDEX_MAP Adapter) AKARI_CE_NAME(IpRenewAddress);

/* ms895712 "NotifyAddrChange" */
AKARI_CE_IMPORT DWORD NotifyAddrChange(PHANDLE Handle, LPOVERLAPPED overlapped) AKARI_CE_NAME(NotifyAddrChange);

/* ms895720 "NotifyRouteChange" */
AKARI_CE_IMPORT DWORD NotifyRouteChange(PHANDLE Handle, LPOVERLAPPED overlapped) AKARI_CE_NAME(NotifyRouteChange);

/* aa450920 "SetIfEntry" */
AKARI_CE_IMPORT DWORD SetIfEntry(PMIB_IFROW pIfRow) AKARI_CE_NAME(SetIfEntry);

/* aa450929 "SetIpStatistics" */
AKARI_CE_IMPORT DWORD SetIpStatistics(PMIB_IPSTATS pIpStats) AKARI_CE_NAME(SetIpStatistics);

/* aa450931 "SetIpTTL" */
AKARI_CE_IMPORT DWORD SetIpTTL(UINT nTTL) AKARI_CE_NAME(SetIpTTL);

/* aa450937 "SetTcpEntry" */
AKARI_CE_IMPORT DWORD SetTcpEntry(PMIB_TCPROW pTcpRow) AKARI_CE_NAME(SetTcpEntry);

/* --- Held (IPAddr / IPMask scalar typedefs unpublished). ---------
 * Recorded verbatim; the IPAddr and IPMask typedefs are printed
 * by these signatures but not published on any CE page:
 *   aa450280 AddIPAddress: `DWORD AddIPAddress(IPAddr Address,
 *     IPMask IpMask,DWORD IfIndex,PULONG NTEContext,
 *     PULONG NTEInstance);`
 *   aa450884 SendARP: `DWORD SendARP(IPAddr DestIP,IPAddr SrcIP,
 *     PULONG pMacAddr,PULONG PhyAddrLen );`
 *   aa450396 GetBestInterface: `DWORDGetBestInterface(IPAddrdwDestAddr,
 *     PDWORDpdwBestIfIndex);` (use GetBestInterfaceEx instead)
 *   aa450422 GetRTTAndHopCount: `BOOLGetRTTAndHopCount(IPAddrDestIpAddress,
 *     PULONGHopCount, ULONGMaxHops, PULONG RTT);` */

/* ------------------------------------------------------------------
 * Book surface: netgen (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms887920 DeleteIPAddress: print `DWORD DeleteIPAddress(ULONGNTEContext);` -- recorded verbatim (no compiled prototype) */
#endif /* AKARI_IPHLPAPI_H */
