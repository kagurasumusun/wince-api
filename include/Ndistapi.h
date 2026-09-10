/* Ndistapi.h -- NDIS/WAN TAPI driver-side support (record-only).
 *
 * Source pages: the Network Driver Reference rows printing
 * "Header: Ntddndis.h and Ndistapi.h" (the NDIS_TAPI_* request
 * structures -- emitted in Ntddndis.h, once, with the joint home
 * noted there) and the single "Header: Ndistapi.h" row:
 * NDIS_TAPI_EVENT (ms904995).
 *
 * NDIS_TAPI_EVENT embeds the HTAPI_LINE / HTAPI_CALL handles,
 * which no CE page prints; the print is recorded verbatim and the
 * struct is closed opaquely.  The OID_TAPI_* object identifiers
 * (34 pages) are recorded in Ntddndis.h.  See docs/inventory.md
 * M78b.
 */

#ifndef AKARI_NDISTAPI_H
#define AKARI_NDISTAPI_H

/* ms904995 "NDIS_TAPI_EVENT": print `typedef struct _NDIS_TAPI_EVENT
 * {HTAPI_LINEhtLine,HTAPI_CALLhtCall,ULONGulMsg,ULONGulParam1,
 * ULONGulParam2,ULONGulParam3} NDIS_TAPI_EVENT, *PNDIS_TAPI_EVENT;`
 * (glued tokens split) -- HTAPI_LINE / HTAPI_CALL are not printed
 * by any CE page; held. */
typedef struct _NDIS_TAPI_EVENT NDIS_TAPI_EVENT, *PNDIS_TAPI_EVENT;

#endif /* AKARI_NDISTAPI_H */
