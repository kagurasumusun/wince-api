/* Ws2spi.h -- Winsock Service Provider Interface (SPI) for Windows CE.
 *
 * Evidence model (clean room; same as winsock2.h):
 *
 *  (a) every prototype and structure layout is transcribed from the
 *      official CE 5.0 "Winsock SPI Reference" documentation pages:
 *      the 29 WSP* transport-SPI function pages (ms898783..ms898915),
 *      the 8 NSP* name-space-SPI function pages (ms895725..ms895766),
 *      the WSPDATA (ms900586) / WSATHREADID (ms898776) /
 *      NSP_Routine (ms895763) structure pages, and the "Upcalls
 *      Exposed by Ws2.dll" page (ms885421).  Every function page's
 *      Requirements rows state: Header: Ws2spi.h, Link Library:
 *      Ws2.lib, OS: Windows CE .NET 4.0 and later (the per-page
 *      records are docs/inventory.md, M42 section).
 *
 *  (b) the CE 5.0 archive strips whitespace inside some code blocks;
 *      no SPI page needed the documented CE 6.0 twin procedure.
 *
 *  (c) the CE pages print `FAR` pointer qualifiers (a Winsock 1.1 /
 *      16-bit relic); Windows CE has a single 32-bit flat address
 *      model, so the declarations use plain pointers (documented
 *      design decision, same as winsock2.h).
 *
 *  (d) the WPU* upcall functions (WPUCloseEvent, WPUCloseSocketHandle,
 *      WPUCreateEvent, WPUCreateSocketHandle, WPUFDIsSet,
 *      WPUQuerySocketHandleContext, WPUResetEvent, WPUSetEvent) are
 *      named and described by the "Upcalls Exposed by Ws2.dll" page
 *      but no CE archive page prints their prototypes: recorded, not
 *      declared.
 *
 *  (e) the NSPLookupServiceNext page (ms895756) prints the prototype
 *      without a "Syntax" heading and with the WSA-prefixed function
 *      name (an archive typo: `int NSPAPI WSALookupServiceNext(...)`);
 *      the declaration below uses the page's title/name
 *      NSPLookupServiceNext with the printed parameter list.
 */

#ifndef _WS2SPI_H
#define _WS2SPI_H

#include "Winsock2.h"   /* SOCKET, WSABUF, WSA* types, WSPDESCRIPTION_LEN */

/* The CE NSPLookupServiceNext page prints the NSPAPI calling
 * convention; Windows CE has one undecorated calling convention, so
 * NSPAPI is empty exactly like WSAAPI in winsock2.h. */
#define NSPAPI  WINAPI

/* The CE SPI prototypes name the W-suffixed forms of the documented
 * (Unicode) structures.  On Windows CE the A/W distinction is nominal
 * (TCHAR is WCHAR), so these are documented-nominal aliases of the
 * M39/M41 types. */
typedef WSAPROTOCOL_INFO  WSAPROTOCOL_INFOW;
typedef WSAPROTOCOL_INFO *LPWSAPROTOCOL_INFOW;
typedef WSAQUERYSET       WSAQUERYSETW;
typedef WSAQUERYSET      *LPWSAQUERYSETW;
/* named by the CE NSP function prototypes (ms895733 / ms895740 /
 * ms895748 / ms895766). */
typedef WSASERVICECLASSINFO *LPWSASERVICECLASSINFOW;

/* WSPDATA page (ms900586): "This structure is used to store
 * information about Windows sockets and is called by WSAStartup."
 * szDescription: "The text (up to 256 characters in length) can
 * contain any characters except control and formatting characters"
 * -- the page prints the array bound as WSPDESCRIPTION_LEN. */
#define WSPDESCRIPTION_LEN  256
typedef struct WSPData {
    WORD  wVersion;
    WORD  wHighVersion;
    WCHAR szDescription[WSPDESCRIPTION_LEN + 1];
} WSPDATA;
typedef WSPDATA *LPWSPDATA;
typedef WSPDATA *LPWSPDATAW;

/* WSATHREADID page (ms898776): "This structure enables a provider to
 * identify the thread to run." */
typedef struct _WSATHREADID {
    HANDLE ThreadHandle;
    DWORD  Reserved;
} WSATHREADID;
typedef WSATHREADID *LPWSATHREADID;

/* NSP_Routine page (ms895763): "This structure contains information
 * regarding all the functions implemented by a service provider."
 * Each pointer member is documented as returning WSAENOTIMPLEMENTED
 * when the provider does not implement the function.  "Ws2spi.h
 * contains complete prototypes for all the NSP functions this
 * structure points to" -- the NSP prototypes are declared below. */
typedef struct _NSP_ROUTINE {
    DWORD cbSize;
    DWORD dwMajorVersion;
    DWORD dwMinorVersion;
    INT (*NSPCleanup);
    INT (*NSPLookupServiceBegin);
    INT (*NSPLookupServiceNext);
    INT (*NSPLookupServiceEnd);
    INT (*NSPSetService);
    INT (*NSPInstallServiceClass);
    INT (*NSPRemoveServiceClass);
    INT (*NSPGetServiceClassInfo);
} NSP_ROUTINE;
typedef NSP_ROUTINE *PNSP_ROUTINE;
typedef NSP_ROUTINE *LPNSP_ROUTINE;

/* WSPUPCALLTABLE / WSPPROC_TABLE: the WSPStartup page (ms898913)
 * documents the parameters ("Upcall dispatch table for ws2.dll",
 * "table of SPI function pointers") but no CE archive page (CE 5.0 /
 * CE .NET / CE 6.0) publishes either layout, so both are opaque
 * (documented design decision).  Consequently WSPStartup below
 * declares the upcall table as a pointer rather than the printed
 * by-value form -- the documented SPI client is Ws2.dll itself, so
 * no user-mode ABI is exposed by the deviation. */
typedef struct _WSPUPCALLTABLE WSPUPCALLTABLE;
typedef struct _WSPPROC_TABLE  WSPPROC_TABLE;
typedef WSPPROC_TABLE *LPWSPPROC_TABLE;

/* ------------------------------------------------------------------ */
/* Winsock SPI functions (transport SPI; the documented SPI client)    */
/* ------------------------------------------------------------------ */

AKARI_CE_IMPORT SOCKET WSPAccept(SOCKET s, struct sockaddr *addr,
                                 INT *addrlen, LPCONDITIONPROC lpfnCondition,
                                 DWORD dwCallbackData, INT *lpErrno)
    AKARI_CE_NAME(WSPAccept);
AKARI_CE_IMPORT int WSPAddressToString(LPSOCKADDR lpsaAddress,
                                       DWORD dwAddressLength,
                                       LPWSAPROTOCOL_INFOW lpProtocolInfo,
                                       LPWSTR lpszAddressString,
                                       LPDWORD lpdwAddressStringLength,
                                       INT *lpErrno)
    AKARI_CE_NAME(WSPAddressToString);
AKARI_CE_IMPORT int WSPAsyncSelect(SOCKET s, HWND hWnd,
                                   unsigned int wMsg, long lEvent,
                                   INT *lpErrno)
    AKARI_CE_NAME(WSPAsyncSelect);
AKARI_CE_IMPORT int WSPBind(SOCKET s, const struct sockaddr *name,
                            int namelen, INT *lpErrno)
    AKARI_CE_NAME(WSPBind);
AKARI_CE_IMPORT int WSPCleanup(INT *lpErrno)
    AKARI_CE_NAME(WSPCleanup);
AKARI_CE_IMPORT int WSPCloseSocket(SOCKET s, INT *lpErrno)
    AKARI_CE_NAME(WSPCloseSocket);
AKARI_CE_IMPORT int WSPConnect(SOCKET s, const struct sockaddr *name,
                               int namelen, LPWSABUF lpCallerData,
                               LPWSABUF lpCalleeData, LPQOS lpSQOS,
                               LPQOS lpGQOS, INT *lpErrno)
    AKARI_CE_NAME(WSPConnect);
AKARI_CE_IMPORT int WSPDuplicateSocket(SOCKET s, DWORD dwProcessId,
                                       LPWSAPROTOCOL_INFOW lpProtocolInfo,
                                       INT *lpErrno)
    AKARI_CE_NAME(WSPDuplicateSocket);
AKARI_CE_IMPORT int WSPEnumNetworkEvents(SOCKET s, WSAEVENT hEventObject,
                                         LPWSANETWORKEVENTS lpNetworkEvents,
                                         INT *lpErrno)
    AKARI_CE_NAME(WSPEnumNetworkEvents);
AKARI_CE_IMPORT int WSPEventSelect(SOCKET s, WSAEVENT hEventObject,
                                   long lNetworkEvents, INT *lpErrno)
    AKARI_CE_NAME(WSPEventSelect);
AKARI_CE_IMPORT BOOL WSPGetOverlappedResult(SOCKET s,
                                            LPWSAOVERLAPPED lpOverlapped,
                                            LPDWORD lpcbTransfer,
                                            BOOL fWait, LPDWORD lpdwFlags,
                                            INT *lpErrno)
    AKARI_CE_NAME(WSPGetOverlappedResult);
AKARI_CE_IMPORT int WSPGetPeerName(SOCKET s, struct sockaddr *name,
                                   INT *namelen, INT *lpErrno)
    AKARI_CE_NAME(WSPGetPeerName);
AKARI_CE_IMPORT int WSPGetSockName(SOCKET s, struct sockaddr *name,
                                   INT *namelen, INT *lpErrno)
    AKARI_CE_NAME(WSPGetSockName);
AKARI_CE_IMPORT int WSPGetSockOpt(SOCKET s, int level, int optname,
                                  char *optval, INT *optlen, INT *lpErrno)
    AKARI_CE_NAME(WSPGetSockOpt);
AKARI_CE_IMPORT int WSPIoctl(SOCKET s, DWORD dwIoControlCode,
                             LPVOID lpvInBuffer, DWORD cbInBuffer,
                             LPVOID lpvOutBuffer, DWORD cbOutBuffer,
                             LPDWORD lpcbBytesReturned,
                             LPWSAOVERLAPPED lpOverlapped,
                             LPWSAOVERLAPPED_COMPLETION_ROUTINE
                                 lpCompletionRoutine,
                             LPWSATHREADID lpThreadId, INT *lpErrno)
    AKARI_CE_NAME(WSPIoctl);
AKARI_CE_IMPORT SOCKET WSPJoinLeaf(SOCKET s, const struct sockaddr *name,
                                   int namelen, LPWSABUF lpCallerData,
                                   LPWSABUF lpCalleeData, LPQOS lpSQOS,
                                   LPQOS lpGQOS, DWORD dwFlags, INT *lpErrno)
    AKARI_CE_NAME(WSPJoinLeaf);
AKARI_CE_IMPORT int WSPListen(SOCKET s, int backlog, INT *lpErrno)
    AKARI_CE_NAME(WSPListen);
AKARI_CE_IMPORT int WSPRecv(SOCKET s, LPWSABUF lpBuffers,
                            DWORD dwBufferCount,
                            LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags,
                            LPWSAOVERLAPPED lpOverlapped,
                            LPWSAOVERLAPPED_COMPLETION_ROUTINE
                                lpCompletionRoutine,
                            LPWSATHREADID lpThreadId, INT *lpErrno)
    AKARI_CE_NAME(WSPRecv);
AKARI_CE_IMPORT int WSPRecvDisconnect(SOCKET s,
                                      LPWSABUF lpInboundDisconnectData,
                                      INT *lpErrno)
    AKARI_CE_NAME(WSPRecvDisconnect);
AKARI_CE_IMPORT int WSPRecvFrom(SOCKET s, LPWSABUF lpBuffers,
                                DWORD dwBufferCount,
                                LPDWORD lpNumberOfBytesRecvd,
                                LPDWORD lpFlags, struct sockaddr *lpFrom,
                                INT *lpFromlen, LPWSAOVERLAPPED lpOverlapped,
                                LPWSAOVERLAPPED_COMPLETION_ROUTINE
                                    lpCompletionRoutine,
                                LPWSATHREADID lpThreadId, INT *lpErrno)
    AKARI_CE_NAME(WSPRecvFrom);
AKARI_CE_IMPORT int WSPSelect(int nfds, fd_set *readfds, fd_set *writefds,
                              fd_set *exceptfds, const struct timeval *timeout,
                              INT *lpErrno)
    AKARI_CE_NAME(WSPSelect);
AKARI_CE_IMPORT int WSPSend(SOCKET s, LPWSABUF lpBuffers,
                            DWORD dwBufferCount,
                            LPDWORD lpNumberOfBytesSent, DWORD dwFlags,
                            LPWSAOVERLAPPED lpOverlapped,
                            LPWSAOVERLAPPED_COMPLETION_ROUTINE
                                lpCompletionRoutine,
                            LPWSATHREADID lpThreadId, INT *lpErrno)
    AKARI_CE_NAME(WSPSend);
AKARI_CE_IMPORT int WSPSendDisconnect(SOCKET s,
                                      LPWSABUF lpOutboundDisconnectData,
                                      INT *lpErrno)
    AKARI_CE_NAME(WSPSendDisconnect);
AKARI_CE_IMPORT int WSPSendTo(SOCKET s, LPWSABUF lpBuffers,
                              DWORD dwBufferCount,
                              LPDWORD lpNumberOfBytesSent, DWORD dwFlags,
                              const struct sockaddr *lpTo, int iTolen,
                              LPWSAOVERLAPPED lpOverlapped,
                              LPWSAOVERLAPPED_COMPLETION_ROUTINE
                                  lpCompletionRoutine,
                              LPWSATHREADID lpThreadId, INT *lpErrno)
    AKARI_CE_NAME(WSPSendTo);
AKARI_CE_IMPORT int WSPSetSockOpt(SOCKET s, int level, int optname,
                                  const char *optval, int optlen,
                                  INT *lpErrno)
    AKARI_CE_NAME(WSPSetSockOpt);
AKARI_CE_IMPORT int WSPShutdown(SOCKET s, int how, INT *lpErrno)
    AKARI_CE_NAME(WSPShutdown);
AKARI_CE_IMPORT SOCKET WSPSocket(int af, int type, int protocol,
                                 LPWSAPROTOCOL_INFOW lpProtocolInfo,
                                 GROUP g, DWORD dwFlags, INT *lpErrno)
    AKARI_CE_NAME(WSPSocket);
/* WSPStartup page (ms898913): "This function must be the first Windows
 * Sockets SPI function called by a Windows Sockets SPI client on a
 * per-process basis."  The printed by-value UpcallTable parameter is
 * declared as a pointer because no CE page publishes the
 * WSPUPCALLTABLE layout (see above). */
AKARI_CE_IMPORT int WSPStartup(WORD wVersionRequested,
                               LPWSPDATAW lpWSPData,
                               LPWSAPROTOCOL_INFOW lpProtocolInfo,
                               const WSPUPCALLTABLE *UpcallTable,
                               LPWSPPROC_TABLE lpProcTable)
    AKARI_CE_NAME(WSPStartup);
AKARI_CE_IMPORT int WSPStringToAddress(LPWSTR AddressString,
                                       INT AddressFamily,
                                       LPWSAPROTOCOL_INFOW lpProtocolInfo,
                                       LPSOCKADDR lpAddress,
                                       INT *lpAddressLength, INT *lpErrno)
    AKARI_CE_NAME(WSPStringToAddress);

/* ------------------------------------------------------------------ */
/* Name-space SPI functions (NSP*)                                      */
/* ------------------------------------------------------------------ */

AKARI_CE_IMPORT int NSPCleanup(LPGUID lpProviderId)
    AKARI_CE_NAME(NSPCleanup);
AKARI_CE_IMPORT int NSPGetServiceClassInfo(LPGUID lpProviderId,
                                           LPDWORD lpdwBufSize,
                                           LPWSASERVICECLASSINFOW
                                               lpServiceClassInfo)
    AKARI_CE_NAME(NSPGetServiceClassInfo);
AKARI_CE_IMPORT int NSPInstallServiceClass(LPGUID lpProviderId,
                                           LPWSASERVICECLASSINFOW
                                               lpServiceClassInfo)
    AKARI_CE_NAME(NSPInstallServiceClass);
AKARI_CE_IMPORT int NSPLookupServiceBegin(LPGUID lpProviderId,
                                          LPWSAQUERYSETW lpqsRestrictions,
                                          LPWSASERVICECLASSINFOW
                                              lpServiceClassInfo,
                                          DWORD dwControlFlags,
                                          LPHANDLE lphLookup)
    AKARI_CE_NAME(NSPLookupServiceBegin);
AKARI_CE_IMPORT int NSPLookupServiceEnd(HANDLE hLookup)
    AKARI_CE_NAME(NSPLookupServiceEnd);
/* NSPLookupServiceNext page (ms895756): the archive prints the
 * prototype without a "Syntax" heading and with the WSA-prefixed name
 * (an archive typo); the declaration uses the page's title
 * NSPLookupServiceNext with the printed parameter list.  The page also
 * documents LUP_FLUSHPREVIOUS (value unpublished: recorded-not-defined
 * in docs/inventory.md). */
AKARI_CE_IMPORT int NSPLookupServiceNext(HANDLE hLookup,
                                         DWORD dwControlFlags,
                                         LPDWORD lpdwBufferLength,
                                         LPWSAQUERYSET lpqsResults)
    AKARI_CE_NAME(NSPLookupServiceNext);
AKARI_CE_IMPORT int NSPRemoveServiceClass(LPGUID lpProviderId,
                                          LPGUID lpServiceClassId)
    AKARI_CE_NAME(NSPRemoveServiceClass);
AKARI_CE_IMPORT int NSPSetService(LPGUID lpProviderId,
                                  LPWSASERVICECLASSINFOW lpServiceClassInfo,
                                  LPWSAQUERYSETW lpqsRegInfo,
                                  WSAESETSERVICEOP essOperation,
                                  DWORD dwControlFlags)
    AKARI_CE_NAME(NSPSetService);


/* ================================================================
 * M77c: Winsock service-provider upcall / installation functions
 * (Ws2.lib rows; pages from the Networking - General harvest).
 * ================================================================ */

/* NSPStartup: print `int NSPStartup(LPGUID lpProviderId,
 * LPNSP_ROUTINE lpnspRoutines);` */
AKARI_CE_IMPORT int NSPStartup(LPGUID lpProviderId,
                    LPNSP_ROUTINE lpnspRoutines) AKARI_CE_NAME(NSPStartup);

/* WPUCloseEvent: print `BOOL WPUCloseEvent(WSAEVENT hEvent,
 * LPINT lpErrno);` */
AKARI_CE_IMPORT BOOL WPUCloseEvent(WSAEVENT hEvent, LPINT lpErrno)
                    AKARI_CE_NAME(WPUCloseEvent);

/* WPUCloseSocketHandle: print `int WPUCloseSocketHandle(SOCKET s,
 * LPINT lpErrno );` */
AKARI_CE_IMPORT int WPUCloseSocketHandle(SOCKET s, LPINT lpErrno)
                    AKARI_CE_NAME(WPUCloseSocketHandle);

/* WPUCreateEvent: print `WSAEVENT WPUCreateEvent(LPINT lpErrno );` */
AKARI_CE_IMPORT WSAEVENT WPUCreateEvent(LPINT lpErrno)
                    AKARI_CE_NAME(WPUCreateEvent);

/* WPUCreateSocketHandle: print `SOCKET WPUCreateSocketHandle(
 * DWORD dwCatalogEntryId,DWORD_PTR dwContext,LPINT lpErrno);` */
AKARI_CE_IMPORT SOCKET WPUCreateSocketHandle(DWORD dwCatalogEntryId,
                    DWORD_PTR dwContext, LPINT lpErrno)
                    AKARI_CE_NAME(WPUCreateSocketHandle);

/* WPUFDIsSet: print `int WPUFDIsSet(SOCKET s,fd_set FAR* set );`
 * (FAR is empty on CE). */
AKARI_CE_IMPORT int WPUFDIsSet(SOCKET s, fd_set *set)
                    AKARI_CE_NAME(WPUFDIsSet);

/* WPUGetProviderPath: print `int WPUGetProviderPath(LPGUID
 * lpProviderId,LPWSTR lpszProviderDllPath,LPINT
 * lpProviderDllPathLen,LPINT lpErrno );` */
AKARI_CE_IMPORT int WPUGetProviderPath(LPGUID lpProviderId,
                    LPWSTR lpszProviderDllPath,
                    LPINT lpProviderDllPathLen, LPINT lpErrno)
                    AKARI_CE_NAME(WPUGetProviderPath);

/* WPUQuerySocketHandleContext: print `int
 * WPUQuerySocketHandleContext(SOCKET s,PDWORD_PTR lpContext,
 * LPINT lpErrno);` */
AKARI_CE_IMPORT int WPUQuerySocketHandleContext(SOCKET s,
                    PDWORD_PTR lpContext, LPINT lpErrno)
                    AKARI_CE_NAME(WPUQuerySocketHandleContext);

/* WPUResetEvent: print `BOOL WPUResetEvent(WSAEVENT hEvent,
 * LPINT lpErrno);` */
AKARI_CE_IMPORT BOOL WPUResetEvent(WSAEVENT hEvent, LPINT lpErrno)
                    AKARI_CE_NAME(WPUResetEvent);

/* WPUSetEvent: print `BOOL WPUSetEvent(WSAEVENT hEvent,
 * LPINT lpErrno);` */
AKARI_CE_IMPORT BOOL WPUSetEvent(WSAEVENT hEvent, LPINT lpErrno)
                    AKARI_CE_NAME(WPUSetEvent);

/* WSCEnumProtocols: print `int WSCEnumProtocols(LPINT lpiProtocols,
 * LPWSAPROTOCOL_INFOW lpProtocolBuffer,LPDWORD lpdwBufferLength,
 * LPINT lpErrno);` */
AKARI_CE_IMPORT int WSCEnumProtocols(LPINT lpiProtocols,
                    LPWSAPROTOCOL_INFOW lpProtocolBuffer,
                    LPDWORD lpdwBufferLength, LPINT lpErrno)
                    AKARI_CE_NAME(WSCEnumProtocols);

/* WSCInstallNameSpace: print `int WSCInstallNameSpace(LPWSTR
 * lpszIdentifier,LPWSTR lpszPathName,DWORD dwNameSpace,
 * DWORD dwVersion,LPGUID lpProviderId );` */
AKARI_CE_IMPORT int WSCInstallNameSpace(LPWSTR lpszIdentifier,
                    LPWSTR lpszPathName, DWORD dwNameSpace,
                    DWORD dwVersion, LPGUID lpProviderId)
                    AKARI_CE_NAME(WSCInstallNameSpace);

/* WSCInstallProvider: print `int WSCInstallProvider(const LPGUID
 * lpProviderId,const LPWSTR lpszProviderDllPath,
 * const LPWSAPROTOCOL_INFOW lpProtocolInfoList,
 * DWORD dwNumberOfEntries,LPINT lpErrno);` */
AKARI_CE_IMPORT int WSCInstallProvider(const LPGUID lpProviderId,
                    const LPWSTR lpszProviderDllPath,
                    const LPWSAPROTOCOL_INFOW lpProtocolInfoList,
                    DWORD dwNumberOfEntries, LPINT lpErrno)
                    AKARI_CE_NAME(WSCInstallProvider);

/* WSCUnInstallNameSpace: print `int WSCUninstallNameSpace(
 * LPGUID lpProviderId);` (title spelling WSCUnInstallNameSpace). */
AKARI_CE_IMPORT int WSCUnInstallNameSpace(LPGUID lpProviderId)
                    AKARI_CE_NAME(WSCUnInstallNameSpace);

/* --- Recorded only. ----------------------------------------------
 * WPUCompleteOverlappedRequest: `int WSPAPI
 * WPUCompleteOverlappedRequest(SOCKETs, LPWSAOVERLAPPEDlpOverlapped,
 * DWORDdwError, DWORDcbTransferred, LPINTlpErrno);` -- the WSPAPI
 * calling-convention macro is not published on any CE page.
 * WPUQueryBlockingCallback: `int WPUQueryBlockingCallback(DWORD
 * dwCatalogEntryId,LPBLOCKINGCALLBACK FAR* lplpfnCallback,
 * PDWORD_PTR lpdwContext,LPINT lpErrno);` -- the BLOCKINGCALLBACK
 * callback type is not published on any CE page. */

#endif  /* _WS2SPI_H */

