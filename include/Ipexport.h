/* Ipexport.h -- IP Helper export types (Windows CE).
 * Pages: tools/manifests/netgen.manifest.  All three structures
 * depend on unpublished constants (MAX_ADAPTER_NAME, IPAddr) or on
 * each other -- recorded verbatim, kept pointer-only for the
 * Iphlpapi.h signatures.  See docs/inventory.md M77a.
 */

#ifndef AKARI_IPEXPORT_H
#define AKARI_IPEXPORT_H

#include "Windef.h"    /* ULONG, LONG, WCHAR */

/* ms891169 "IP_ADAPTER_INDEX_MAP": print `typedef struct
 * _IP_ADAPTER_INDEX_MAP{ULONGIndex; WCHARName[MAX_ADAPTER_NAME];}
 * IP_ADAPTER_INDEX_MAP, *PIP_ADAPTER_INDEX_MAP;` -- MAX_ADAPTER_NAME
 * is not published on any CE page. */
typedef struct _IP_ADAPTER_INDEX_MAP IP_ADAPTER_INDEX_MAP, *PIP_ADAPTER_INDEX_MAP;

/* ms891177 "IP_INTERFACE_INFO": print `typedef struct
 * _IP_INTERFACE_INFO{LONG NumAdapters;IP_ADAPTER_INDEX_MAP Adapter[1];}
 * IP_INTERFACE_INFO, *PIP_INTERFACE_INFO;` -- embeds the
 * pointer-only IP_ADAPTER_INDEX_MAP. */
typedef struct _IP_INTERFACE_INFO IP_INTERFACE_INFO, *PIP_INTERFACE_INFO;

/* aa450431 "IP_UNIDIRECTIONAL_ADAPTER_ADDRESS": print `typedef
 * struct _IP_UNIDIRECTIONAL_ADAPTER_ADDRESS{ULONG NumAdapters;
 * IPAddr Address[1];} IP_UNIDIRECTIONAL_ADAPTER_ADDRESS*,
 * PIP_UNIDIRECTIONAL_ADAPTER_ADDRESS;` -- the IPAddr typedef is not
 * published on any CE page (typedef-name placement is a doc typo). */
typedef struct _IP_UNIDIRECTIONAL_ADAPTER_ADDRESS
    IP_UNIDIRECTIONAL_ADAPTER_ADDRESS, *PIP_UNIDIRECTIONAL_ADAPTER_ADDRESS;

#endif /* AKARI_IPEXPORT_H */
