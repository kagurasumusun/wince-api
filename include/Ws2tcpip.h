/* Ws2tcpip.h -- getaddrinfo() name-resolution surface for
 *                Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * M39: the three name-resolution functions whose official CE pages
 * name Ws2tcpip.h as the header and Ws2.lib as the link library
 * (all "Windows CE .NET 4.1 and later"):
 *
 *   getaddrinfo   aa450395  (v=msdn.10)
 *   freeaddrinfo  aa450383  (v=msdn.10)
 *   getnameinfo   aa450416  (v=msdn.10)
 *
 * The addrinfo structure (aa450282), the AI_ flag values and the
 * AF_/SOCK_/IPPROTO_ names used by its members live in
 * winsock2.h, which this header includes first.  The AI_ numeric
 * values come from the official ADDRINFOA reference table (see
 * winsock2.h for the evidence model); docs/inventory.md (M39 section)
 * records the per-page details.
 */

#ifndef _WS2TCPIP_H
#define _WS2TCPIP_H

#include "Winsock2.h"

AKARI_CE_IMPORT int getaddrinfo(const char *nodename,
                                const char *servname,
                                const struct addrinfo *hints,
                                struct addrinfo **res)
    AKARI_CE_NAME(getaddrinfo);
AKARI_CE_IMPORT void freeaddrinfo(struct addrinfo *ai)
    AKARI_CE_NAME(freeaddrinfo);
AKARI_CE_IMPORT int getnameinfo(const struct sockaddr *sa,
                                socklen_t salen,
                                char *host, DWORD hostlen,
                                char *serv, DWORD servlen,
                                int flags)
    AKARI_CE_NAME(getnameinfo);

/* ------------------------------------------------------------------
 * Book surface: netgen (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa450282 addrinfo (Header: Ws2tcpip.h.) */
/* ms890972 in6_addr (Header: Ws2tcpip.h.) */
/* aa450948 sockaddr_in6 (Header: Ws2tcpip.h.) */
/* ------------------------------------------------------------------
 * Book surface: wsock-structures (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa450282 addrinfo (Header: Ws2tcpip.h.) */
/* ms890972 in6_addr (Header: Ws2tcpip.h.) */
/* aa450948 sockaddr_in6 (Header: Ws2tcpip.h.) */
#endif  /* _WS2TCPIP_H */
