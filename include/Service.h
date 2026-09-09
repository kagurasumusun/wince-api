/* Service.h -- Services.exe service API (Windows CE .NET 4.0+).
 *
 * Pages: tools/manifests/servers.manifest (Servers book,
 * Services.exe node); Link Library rows print Coredll.lib.  See
 * docs/inventory.md M75e.
 */

#ifndef AKARI_SERVICE_H
#define AKARI_SERVICE_H

#include "Windef.h"    /* HANDLE, BOOL, DWORD, LPVOID, LPCWSTR */
#include "Winsock2.h"  /* SOCKADDR */

/* aa450899 "ServiceEnumInfo": print (sic)
 * `Typedef struct_ServiceEnumInfo {WCHARszPrefix[6];
 * WCHAR szDllName;HANDLE hServiceHandle;DWORD dwServiceState;}
 * ServiceEnumInfo;` -- szDllName is printed as a scalar WCHAR
 * (the desktop array spelling is not printed on the CE page);
 * kept verbatim. */
typedef struct _ServiceEnumInfo {
    WCHAR  szPrefix[6];
    WCHAR  szDllName;
    HANDLE hServiceHandle;
    DWORD  dwServiceState;
} ServiceEnumInfo;

/* Record-only (unpublished members): aa450906
 * "ServicesexeCallbackFunctions" prints `typedef struct
 * _ServicesExeCallbackFunctions { PFN_SERVICE_SHUTDOWN
 * pfnServiceShutdown;} ServicesExeCallbackFunctions;` (the
 * PFN_SERVICE_SHUTDOWN signature is not printed on any CE page);
 * aa450908 "ServicesExeCommandLineParams" prints `typedef struct
 * _ServicesExeCommandLineParams { DWORD dwArgs; const WCHAR*
 * ppwszArgs[SERVICES_EXE_MAX_CMD_LINE_OPTIONS];}
 * ServicesExeCommandLineParams;` (SERVICES_EXE_MAX_CMD_LINE_OPTIONS
 * value not printed). */
typedef struct _ServicesExeCallbackFunctions ServicesExeCallbackFunctions;
typedef struct _ServicesExeCommandLineParams ServicesExeCommandLineParams;

/* IOCTL_SERVICE_* names (18): recorded only -- no CE page prints
 * the CTL_CODE values: IOCTL_SERVICE_CALLBACK_FUNCTIONS,
 * IOCTL_SERVICE_COMMAND_LINE_PARAMS, IOCTL_SERVICE_CONNECTION,
 * IOCTL_SERVICE_CONSOLE, IOCTL_SERVICE_CONTROL,
 * IOCTL_SERVICE_DEBUG, IOCTL_SERVICE_DEREGISTER_SOCKADDR,
 * IOCTL_SERVICE_INSTALL, IOCTL_SERVICE_NOTIFY_ADDR_CHANGE,
 * IOCTL_SERVICE_QUERY_CAN_DEINIT, IOCTL_SERVICE_REFRESH,
 * IOCTL_SERVICE_REGISTER_SOCKADDR, IOCTL_SERVICE_START,
 * IOCTL_SERVICE_STARTED, IOCTL_SERVICE_STATUS,
 * IOCTL_SERVICE_STOP, IOCTL_SERVICE_UNINSTALL,
 * IOCTL_SERVICE_UNLOAD. */

/* aa450897 "RegisterService": print
 * `HANDLE RegisterService(LPCWSTRlpszType,DWORD dwIndex,
 * LPCWSTR lpszLib,DWORD dwInfo);` */
AKARI_CE_IMPORT HANDLE RegisterService(LPCWSTR lpszType,
                    DWORD dwIndex, LPCWSTR lpszLib, DWORD dwInfo)
                    AKARI_CE_NAME(RegisterService);

/* aa450886 "DeregisterService": print
 * `BOOL DeregisterService(HANDLEhDevice);` */
AKARI_CE_IMPORT BOOL DeregisterService(HANDLE hDevice)
                    AKARI_CE_NAME(DeregisterService);

/* aa450368 "EnumServices": print
 * `BOOL EnumServices(PBYTEpBuffer,DWORD pdwServiceEntries,
 * DWORD pdwBufferLen);` -- pdw* parameters are printed as plain
 * DWORD ([out] counts per the page text); kept verbatim. */
AKARI_CE_IMPORT BOOL EnumServices(PBYTE pBuffer,
                    DWORD pdwServiceEntries, DWORD pdwBufferLen)
                    AKARI_CE_NAME(EnumServices);

/* aa450369 "GetServiceHandle": print
 * `HANDLE GetServiceHandle(LPWSTRszPrefix,LPWSTR szDllName,
 * DWORD pdwDllBufLen);` -- third parameter printed as DWORD;
 * kept verbatim. */
AKARI_CE_IMPORT HANDLE GetServiceHandle(LPWSTR szPrefix,
                    LPWSTR szDllName, DWORD pdwDllBufLen)
                    AKARI_CE_NAME(GetServiceHandle);

/* aa450898 "ActivateService": print
 * `HANDLE ActivateService(LPCWSTRlpszDevKey,DWORD dwClientInfo);` */
AKARI_CE_IMPORT HANDLE ActivateService(LPCWSTR lpszDevKey,
                    DWORD dwClientInfo) AKARI_CE_NAME(ActivateService);

/* aa450392 "ServiceIoControl": print
 * `BOOL ServiceIoControl(HANDLEhService,DWORD dwIoControlCode,
 * LPVOID lpInBuf,DWORD dwInBufLen,LPVOID lpOutBuf,
 * DWORD dwOutBufLen,PDWORD pdwBytesTransferred);` */
AKARI_CE_IMPORT BOOL ServiceIoControl(HANDLE hService,
                    DWORD dwIoControlCode, LPVOID lpInBuf,
                    DWORD dwInBufLen, LPVOID lpOutBuf,
                    DWORD dwOutBufLen,
                    PDWORD pdwBytesTransferred)
                    AKARI_CE_NAME(ServiceIoControl);

/* aa450892 "ServiceAddPort": print
 * `BOOL ServiceAddPort(HANDLEhService,SOCKADDR pSockAddr,
 * INT cbSockAddr,INT iProtocol,WCHAR szRegWritePath);` --
 * pSockAddr and szRegWritePath are printed by value; kept
 * verbatim. */
AKARI_CE_IMPORT BOOL ServiceAddPort(HANDLE hService,
                    SOCKADDR pSockAddr, INT cbSockAddr,
                    INT iProtocol, WCHAR szRegWritePath)
                    AKARI_CE_NAME(ServiceAddPort);

/* aa450393 "ServiceClosePort": print
 * `BOOL ServiceClosePort(HANDLE hService, SOCKADDR* pSockAddr,
 * int cbSockAddr,INT iProtocol);` */
AKARI_CE_IMPORT BOOL ServiceClosePort(HANDLE hService,
                    SOCKADDR *pSockAddr, int cbSockAddr,
                    INT iProtocol) AKARI_CE_NAME(ServiceClosePort);

/* aa450394 "ServiceUnbindPorts": print
 * `BOOL ServiceUnbindPorts(HANDLEhService);` */
AKARI_CE_IMPORT BOOL ServiceUnbindPorts(HANDLE hService)
                    AKARI_CE_NAME(ServiceUnbindPorts);

/* RasIOControl (aa450852, Ras.h): print
 * `RasIOControl IMPLICIT_DECL(LPVOIDhRasConn,DWORDdwCode,
 * PBYTEpBufIn,DWORDdwLenIn,PBYTEpBufOut,DWORDdwLenOut,
 * PDWORDpdwActualOut);` -- IMPLICIT_DECL is not published;
 * recorded only (RAS server RASCNTL_* structures likewise). */

#endif /* AKARI_SERVICE_H */
