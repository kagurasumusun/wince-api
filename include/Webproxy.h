/* Webproxy.h -- Web Proxy filter interface (Windows CE .NET 4.1+).
 * Link Library rows print "Not applicable" (filter entry points
 * loaded by the web proxy, not an import lib).  See
 * docs/inventory.md M75e. */

#ifndef AKARI_WEBPROXY_H
#define AKARI_WEBPROXY_H

#include "Windef.h"    /* DWORD */

/* ms896347 "PROXY_HTTP_INFORMATION": print
 * `typedef struct _PROXY_HTTP_INFORMATION { DWORD dwSize;
 * DWORD dwProxyVersion;} PROXY_HTTP_INFORMATION,
 * *PPROXY_HTTP_INFORMATION;` */
typedef struct _PROXY_HTTP_INFORMATION {
    DWORD dwSize;
    DWORD dwProxyVersion;
} PROXY_HTTP_INFORMATION, *PPROXY_HTTP_INFORMATION;

/* ms896348 "PROXY_HTTP_REQUEST": print (missing semicolon after
 * cbsaClient repaired in the record below; members point at
 * SOCKADDR_STORAGE, which is not defined on any CE page -- the
 * struct is recorded, not compiled):
 * `typedef struct _PROXY_HTTP_REQUEST { DWORD dwSize;
 * const SOCKADDR_STORAGE* psaClient; int cbsaClient;
 * const char* szUser; int cchUser; const char* szURL;
 * int cchURL; char* szURLOut; int cbURLOut;
 * const SOCKADDR_STORAGE* psaProxy; int cbsaProxy;}
 * PROXY_HTTP_REQUEST, *PPROXY_HTTP_REQUEST;` */

/* ms896346 "ProxyInitializeFilter": print
 * `DWORD WINAPI ProxyInitializeFilter( PPROXY_HTTP_INFORMATION
 * pInfo);` */
AKARI_CE_IMPORT DWORD WINAPI ProxyInitializeFilter(
                    PPROXY_HTTP_INFORMATION pInfo)
                    AKARI_CE_NAME(ProxyInitializeFilter);

/* ProxyUninitializeFilter / ProxyNotifyAddrChange /
 * ProxySignalFilter: prints `DWORD WINAPI
 * ProxyUninitializeFilter (void);`, `DWORD WINAPI
 * ProxyNotifyAddrChange(void);`, `DWORD ProxySignalFilter(
 * DWORD dwSignal);` */
AKARI_CE_IMPORT DWORD WINAPI ProxyUninitializeFilter(void)
                    AKARI_CE_NAME(ProxyUninitializeFilter);
AKARI_CE_IMPORT DWORD WINAPI ProxyNotifyAddrChange(void)
                    AKARI_CE_NAME(ProxyNotifyAddrChange);
AKARI_CE_IMPORT DWORD ProxySignalFilter(DWORD dwSignal)
                    AKARI_CE_NAME(ProxySignalFilter);

/* ProxyFilterHttpRequest (ms896345): HELD -- the print
 * `DWORD ProxyFilterHttpRequest( PPROXY_HTTP_REQUEST pRequest);`
 * takes PPROXY_HTTP_REQUEST, whose members point at the
 * unpublished SOCKADDR_STORAGE.  Recorded. */

/* ------------------------------------------------------------------
 * Book surface: servers (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ------------------------------------------------------------------
 * Book surface: servers (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms891164 IOCTL_SERVICE_PRX_SIGNAL_FILTER: documented name-only (no value published; held) */
#endif /* AKARI_WEBPROXY_H */
