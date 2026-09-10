/* Ras.h -- RAS server administration structures (Servers book,
 * RAS Server/PPTP node; used with the RasIOControl record in
 * Service.h).  See docs/inventory.md M75f. */

#ifndef AKARI_RAS_H
#define AKARI_RAS_H

#include "Windef.h"    /* BOOL, DWORD, BYTE */

/* ms896355 "RASCNTL_SERVERSTATUS": print
 * `typedef struct tagRasCntlServerStatus {BOOLbEnable;
 * DWORDbmFlags;BOOLbUseDhcpAddresses;DWORDdwStaticIpAddrStart;
 * DWORDdwStaticIpAddrCount;DWORD bmAuthenticationMethods;
 * DWORDdwNumLines;} RASCNTL_SERVERSTATUS, *PRASCNTL_SERVERSTATUS;` */
typedef struct tagRasCntlServerStatus {
    BOOL  bEnable;
    DWORD bmFlags;
    BOOL  bUseDhcpAddresses;
    DWORD dwStaticIpAddrStart;
    DWORD dwStaticIpAddrCount;
    DWORD bmAuthenticationMethods;
    DWORD dwNumLines;
} RASCNTL_SERVERSTATUS, *PRASCNTL_SERVERSTATUS;

/* ms896358 "RASCNTL_SERVER_IPV6_NET_PREFIX": print
 * `typedef struct tagRasCntlServerIPV6NetPrefix {
 * BYTE IPV6NetPrefix[16]; DWORD IPV6NetPrefixBitLength;
 * DWORD IPV6NetPrefixCount;} RASCNTL_SERVER_IPV6_NET_PREFIX,
 * *PRASCNTL_SERVER_IPV6_NET_PREFIX;` */
typedef struct tagRasCntlServerIPV6NetPrefix {
    BYTE  IPV6NetPrefix[16];
    DWORD IPV6NetPrefixBitLength;
    DWORD IPV6NetPrefixCount;
} RASCNTL_SERVER_IPV6_NET_PREFIX, *PRASCNTL_SERVER_IPV6_NET_PREFIX;

/* --- Record-only (members depend on unpublished types). ----------
 * ms896353 "RasCntlEnum": print (truncated on the page, values
 * absent, several commas missing -- verbatim):
 *   typedef enum tagRasCntlEnum { RASCNTL_SERVER_GET_STATUS,
 *   RASCNTL_SERVER_ENABLE, RASCNTL_SERVER_DISABLE,
 *   RASCNTL_SERVER_GET_PARAMETERS, RASCNTL_SERVER_SET_PARAMETERS,
 *   RASCNTL_SERVER_LINE_ADD, RASCNTL_SERVER_LINE_REMOVE,
 *   RASCNTL_SERVER_LINE_ENABLE, RASCNTL_SERVER_LINE_DISABLE,
 *   RASCNTL_SERVER_LINE_GET_PARAMETERS,
 *   RASCNTL_SERVER_LINE_SET_PARAMETERS,
 *   RASCNTL_SERVER_USER_SET_CREDENTIALS,
 *   RASCNTL_SERVER_USER_DELETE_CREDENTIALS,
 *   RASCNTL_SERVER_GET_IPV6_NET_PREFIX RASCNTL_SERVER_SET_IPV6_NET_PREFIX
 *   RASCNTL_SERVER_LINE_GET_CO... (page ends mid-identifier)
 * ms896354 "RASCNTL_SERVERLINE": `typedef struct tagRasCntlServerLine
 * {RASDEVINFOrasDevInfo;BOOLbEnable;DWORDbmFlags;
 * UINTDisconnectIdleSeconds;DWORDdwDevConfigSize;BYTEDevConfig[1];}
 * RASCNTL_SERVERLINE, *PRASCNTL_SERVERLINE;` (RASDEVINFO unpublished)
 * CROSS-GENERATION (M86 sweep): the CE 4.0 twin ms924959 prints the
 * same members but drops the semicolon after `BYTE DevConfig[1]`
 * (archive print artifact; members identical).
 * ms896356 "RASCNTL_SERVERUSERCREDENTIALS": `typedef struct
 * tagRasCntlServerUser{TCHAR tszUserName[UNLEN + 1];
 * TCHARtszDomainName[DNLEN + 1];BYTEpassword[PWLEN];DWORDcbPassword;}
 * RASCNTL_SERVERUSERCREDENTIALS, *PRASCNTL_SERVERUSERCREDENTIALS;`
 * (UNLEN/DNLEN/PWLEN unpublished)
 * ms896357 "RASCNTL_SERVERCONNECTION": `typedef struct
 * tagRasCntlServerConnection { RASDEVINFO rasDevInfo;
 * HRASCONN hrasconn; DWORD dwServerIpAddress;
 * DWORD dwClientIpAddress; RASCONNSTATE RasConnState;
 * TCHAR tszUserName[DNLEN + 1 + UNLEN + 1];} RASCNTL_SERVERCONNECTION,
 * *PRASCNTL_SERVERCONNECTION;` (RASDEVINFO/HRASCONN/RASCONNSTATE/
 * UNLEN/DNLEN unpublished). */

#endif /* AKARI_RAS_H */
