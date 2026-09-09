/* Winnetwk.h -- Windows Networking (WNet) API (Windows CE).
 * Pages: tools/manifests/netgen.manifest; Link Library rows print
 * Coredll.lib (def/coredll-doc.def).  See docs/inventory.md M77b. */

#ifndef AKARI_WINNETWK_H
#define AKARI_WINNETWK_H

#include "Windef.h"    /* DWORD, BOOL, HWND, HANDLE, LPHANDLE,
                        * LPTSTR, LPCTSTR, LPVOID, LPDWORD */

/* NETRESOURCE (title, print `typedef struct _NETRESOURCE {DWORD dwScope;
 * DWORD dwType; DWORD dwDisplayType; DWORD dwUsage; LPTSTR lpLocalName;
 * LPTSTR lpRemoteName; LPTSTR lpComment; LPTSTR lpProvider; }`). */
typedef struct _NETRESOURCE {
    DWORD  dwScope;
    DWORD  dwType;
    DWORD  dwDisplayType;
    DWORD  dwUsage;
    LPTSTR lpLocalName;
    LPTSTR lpRemoteName;
    LPTSTR lpComment;
    LPTSTR lpProvider;
} NETRESOURCE, *LPNETRESOURCE;

/* CONNECTDLGSTRUCT (tagless print; tag closed on typedef name). */
typedef struct CONNECTDLGSTRUCT {
    DWORD          cbStructure;
    HWND           hwndOwner;
    LPNETRESOURCE  lpConnRes;
    DWORD          dwFlags;
    DWORD          dwDevNum;
} CONNECTDLGSTRUCT, *LPCONNECTDLGSTRUCT;

/* DISCDLGSTRUCT: print `typedef struct _wcesdk_win32_DISCDLGSTRUCT_str
 * {DWORD cbStructure;HWND hwndOwner;LPTSTR lpLocalName;
 * LPTSTR lpRemoteName;DWORD dwFlags;} DISCDLGSTRUCT;` (wcesdk tag). */
typedef struct _wcesdk_win32_DISCDLGSTRUCT_str {
    DWORD  cbStructure;
    HWND   hwndOwner;
    LPTSTR lpLocalName;
    LPTSTR lpRemoteName;
    DWORD  dwFlags;
} DISCDLGSTRUCT, *LPDISCDLGSTRUCT;

typedef struct _REMOTE_NAME_INFO {
    LPTSTR lpUniversalName;
    LPTSTR lpConnectionName;
    LPTSTR lpRemainingPath;
} REMOTE_NAME_INFO, *LPREMOTE_NAME_INFO;

typedef struct _UNIVERSAL_NAME_INFO {
    LPTSTR lpUniversalName;
} UNIVERSAL_NAME_INFO, *LPUNIVERSAL_NAME_INFO;


/* ms898713 "WNetOpenEnum" */
AKARI_CE_IMPORT DWORD WNetOpenEnum(DWORD dwScope, DWORD dwType, DWORD dwUsage,
                    LPNETRESOURCE lpNetResource, LPHANDLE lphEnum)
                    AKARI_CE_NAME(WNetOpenEnum);

/* ms898709 "WNetEnumResource" */
AKARI_CE_IMPORT DWORD WNetEnumResource(HANDLE hEnum, LPDWORD lpcCount, LPVOID lpBuffer,
                    LPDWORD lpBufferSize)
                    AKARI_CE_NAME(WNetEnumResource);

/* ms898606 "WNetCloseEnum" */
AKARI_CE_IMPORT DWORD WNetCloseEnum(HANDLE hEnum)
                    AKARI_CE_NAME(WNetCloseEnum);

/* ms898589 "WNetAddConnection3" */
AKARI_CE_IMPORT DWORD WNetAddConnection3(HWND hwndOwner, LPNETRESOURCE lpNetResource,
                    LPTSTR lpPassword, LPTSTR lpUserName,
                    DWORD dwFlags)
                    AKARI_CE_NAME(WNetAddConnection3);

/* ms898597 "WNetCancelConnection2" */
AKARI_CE_IMPORT DWORD WNetCancelConnection2(LPTSTR lpName, DWORD dwFlags, BOOL fForce)
                    AKARI_CE_NAME(WNetCancelConnection2);

/* ms898611 "WNetConnectionDialog1" */
AKARI_CE_IMPORT DWORD WNetConnectionDialog1(LPCONNECTDLGSTRUCT lpConnectDlgStruct)
                    AKARI_CE_NAME(WNetConnectionDialog1);

/* ms898697 "WNetDisconnectDialog" */
AKARI_CE_IMPORT DWORD WNetDisconnectDialog(HWND hwnd, DWORD dwType)
                    AKARI_CE_NAME(WNetDisconnectDialog);

/* ms898705 "WNetDisconnectDialog1" */
AKARI_CE_IMPORT DWORD WNetDisconnectDialog1(LPDISCDLGSTRUCT lpDiscDlgStruct)
                    AKARI_CE_NAME(WNetDisconnectDialog1);

/* ms898710 "WNetGetConnection" */
AKARI_CE_IMPORT DWORD WNetGetConnection(LPCTSTR lpLocalName, LPTSTR lpRemoteName,
                    LPDWORD lpnLength)
                    AKARI_CE_NAME(WNetGetConnection);

/* ms898711 "WNetGetUniversalName" */
AKARI_CE_IMPORT DWORD WNetGetUniversalName(LPCTSTR lpLocalPath, DWORD dwInfoLevel,
                    LPVOID lpBuffer, LPDWORD lpBufferSize)
                    AKARI_CE_NAME(WNetGetUniversalName);

/* ms898712 "WNetGetUser" */
AKARI_CE_IMPORT DWORD WNetGetUser(LPCTSTR lpName, LPTSTR lpUserName, LPDWORD lpnLength)
                    AKARI_CE_NAME(WNetGetUser);

#endif /* AKARI_WINNETWK_H */
