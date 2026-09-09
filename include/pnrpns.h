/* pnrpns.h -- PNRP namespace structures (Windows CE 5.0+; p2p.lib
 * rows).  Pages: tools/manifests/servers.manifest.  The two
 * payload structures embed unpublished enum types (PNRP_SCOPE,
 * PNRP_REGISTERED_ID_STATE -- each named on its using page only),
 * so they are recorded verbatim and kept pointer-only.
 * See docs/inventory.md M75d. */

#ifndef AKARI_PNRPNS_H
#define AKARI_PNRPNS_H

#include "Windef.h"    /* DWORD, ULONG, INT, LPWSTR */
#include "Winsock2.h"  /* SOCKET_ADDRESS */
#include "pnrpdef.h"   /* PNRP_CLOUD_STATE, PNRP_CLOUD_FLAGS */

/* ms896279 "PNRP_CLOUD_ID": print `typedef struct _PNRP_CLOUD_ID
 * { INT AddressFamily; PNRP_SCOPE Scope; ULONG ScopeID;}
 * PNRP_CLOUD_ID, *PPNRP_CLOUD_ID;` -- PNRP_SCOPE is not published
 * on any CE page (named only here) -- recorded, pointer-only. */
typedef struct _PNRP_CLOUD_ID PNRP_CLOUD_ID;

/* ms896270 "PNRPCLOUDINFO": print `typedef struct _PNRPCLOUDINFO
 * { DWORD dwSize; PNRP_CLOUD_ID Cloud; PNRP_CLOUD_STATE enCloudState;
 * PNRP_CLOUD_FLAGS enCloudFlags;} PNRPCLOUDINFO, *PPNRPCLOUDINFO;`
 * (embeds the pointer-only PNRP_CLOUD_ID) -- recorded,
 * pointer-only. */
typedef struct _PNRPCLOUDINFO PNRPCLOUDINFO;

/* ms896275 "PNRPINFO": print `typedef struct _PNRPINFO
 * { DWORD dwSize; LPWSTR lpwszIdentity; DWORD nMaxResolve;
 * DWORD dwTimeout; DWORD dwLifetime; PNRP_RESOLVE_CRITERIA
 * enResolveCriteria; DWORD dwFlags; SOCKET_ADDRESS saHint;
 * PNRP_REGISTERED_ID_STATE enNameState;} PNRPINFO, *PPNRPINFO;`
 * -- PNRP_REGISTERED_ID_STATE is not published on any CE page
 * (named only here) -- recorded, pointer-only. */
typedef struct _PNRPINFO PNRPINFO;

#endif /* AKARI_PNRPNS_H */
