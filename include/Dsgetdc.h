/* Dsgetdc.h -- DS GetDcName (Windows CE; Netapi32.lib row).
 * See docs/inventory.md M77b. */

#ifndef AKARI_DSGETDC_H
#define AKARI_DSGETDC_H

#include "Windef.h"    /* DWORD, ULONG, LPCTSTR, LPTSTR */
#include "Winnt.h"     /* GUID */

/* "DOMAIN_CONTROLLER_INFO": print `typedef struct
 * _DOMAIN_CONTROLLER_INFO { LPTSTR DomainControllerName;
 * LPTSTR DomainControllerAddress; ULONG DomainControllerAddressType;
 * GUID DomainGuid; LPTSTR DomainName; LPTSTR DnsForestName;
 * ULONG Flags; LPTSTR DcSiteName; LPTSTR ClientSiteName; ... }
 * DOMAIN_CONTROLLER_INFO, *PDOMAIN_CONTROLLER_INFO;` */
typedef struct _DOMAIN_CONTROLLER_INFO {
    LPTSTR DomainControllerName;
    LPTSTR DomainControllerAddress;
    ULONG  DomainControllerAddressType;
    GUID   DomainGuid;
    LPTSTR DomainName;
    LPTSTR DnsForestName;
    ULONG  Flags;
    LPTSTR DcSiteName;
    LPTSTR ClientSiteName;
} DOMAIN_CONTROLLER_INFO, *PDOMAIN_CONTROLLER_INFO;

/* "DsGetDcName" (Netapi32.lib): print `DWORD DsGetDcName(
 * LPCTSTR ComputerName, LPCTSTR DomainName, GUID* DomainGuid,
 * LPCTSTR SiteName, ULONG Flags,
 * PDOMAIN_CONTROLLER_INFO* DomainControllerInfo);` */
AKARI_CE_IMPORT DWORD DsGetDcName(LPCTSTR ComputerName,
                    LPCTSTR DomainName, GUID *DomainGuid,
                    LPCTSTR SiteName, ULONG Flags,
                    PDOMAIN_CONTROLLER_INFO *DomainControllerInfo)
                    AKARI_CE_NAME(DsGetDcName);

/* NetApiBufferFree (Netapi32.lib row): print
 * `NET_API_STATUS NetApiBufferFree( LPVOID Buffer);` -- the
 * NET_API_STATUS typedef is not published on any CE page;
 * recorded verbatim. */

#endif /* AKARI_DSGETDC_H */
