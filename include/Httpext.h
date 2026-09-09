/* Httpext.h -- ISAPI Extensions (Windows CE Web Server).
 * Link Library rows print "Not applicable" (extension entry points
 * are exported by the extension DLL).  See docs/inventory.md M75f. */

#ifndef AKARI_HTTPEXT_H
#define AKARI_HTTPEXT_H

#include "Windef.h"    /* BOOL, DWORD, CHAR, LPSTR, LPCSTR */

/* ms890323 "HSE_SEND_HEADER_EX_INFO": print
 * `typedef struct _HSE_SEND_HEADER_EX_INFO{ LPCSTR pszStatus;
 * LPCSTR pszHeader; DWORD cchStatus; DWORD cchHeader;
 * BOOL fKeepConn;} HSE_SEND_HEADER_EX_INFO, *LPHSE_SEND_HEADER_EX_INFO;` */
typedef struct _HSE_SEND_HEADER_EX_INFO {
    LPCSTR pszStatus;
    LPCSTR pszHeader;
    DWORD  cchStatus;
    DWORD  cchHeader;
    BOOL   fKeepConn;
} HSE_SEND_HEADER_EX_INFO, *LPHSE_SEND_HEADER_EX_INFO;

/* ms890321 "HSE_URL_MAPEX_INFO": print
 * `typedef struct_HSE_URL_MAPEX_INFO{CHARlpszPath[MAX_PATH];
 * DWORDdwFlags;DWORDcchMatchingPath;DWORDcchMatchingURL;
 * DWORDdwReserved1;DWORDdwReserved2;} HSE_URL_MAPEX_INFO,
 * *LPHSE_URL_MAPEX_INFO;` (MAX_PATH from Windef.h). */
typedef struct _HSE_URL_MAPEX_INFO {
    CHAR  lpszPath[MAX_PATH];
    DWORD dwFlags;
    DWORD cchMatchingPath;
    DWORD cchMatchingURL;
    DWORD dwReserved1;
    DWORD dwReserved2;
} HSE_URL_MAPEX_INFO, *LPHSE_URL_MAPEX_INFO;

/* --- Record-only. -----------------------------------------------
 * aa450369 "EXTENSION_CONTROL_BLOCK": print (member parameter
 * lists from the callback pages):
 *   typedef struct _EXTENSION_CONTROL_BLOCK{DWORDcbSize;
 *   DWORDdwVersion;HCONNConnID;DWORDdwHttpStatusCode;
 *   CHAR lpszLogData[HSE_LOG_BUFFER_LEN];LPSTRlpszMethod;
 *   LPSTRlpszQueryString;LPSTRlpszPathInfo;LPSTRlpszPathTranslated;
 *   DWORDcbTotalBytes;DWORDcbAvailable;LPBYTElpbData;
 *   LPSTRlpszContentType;BOOL (WINAPI* GetServerVariable);
 *   BOOL (WINAPI* WriteClient);BOOL (WINAPI* ReadClient);
 *   BOOL (WINAPI* ServerSupportFunction);} EXTENSION_CONTROL_BLOCK,
 *   LPEXTENSION_CONTROL_BLOCK;
 * -- HCONN and HSE_LOG_BUFFER_LEN are not published on any CE page.
 * Extension callback signatures (pages):
 *   aa450423 GetServerVariable (ISAPI Extensions):
 *     BOOL (WINAPI* GetServerVariable)(HCONN hConn,
 *       LPSTR lpszVariableName,LPVOID lpvBuffer,LPDWORD lpdwSize);
 *   ms898725 WriteClient (ISAPI Extensions):
 *     BOOL (WINAPI* WriteClient)(HCONN ConnID,LPVOID Buffer,
 *       LPDWORD lpdwBytes,DWORD dwReserved);
 *   aa450868 ReadClient:
 *     BOOL (WINAPI* ReadClient)(HCONN ConnID,LPVOID lpvBuffer,
 *       LPDWORD lpdwSize);
 *   aa450887 ServerSupportFunction (ISAPI Extensions):
 *     BOOL (WINAPI* ServerSupportFunction)( HCONN hConn,
 *       DWORD dwHSERequest, LPVOID lpvBuffer, LPDWORD lpdwSize,
 *       LPDWORD lpdwDataType);
 * ms890322 "HSE_VERSION_INFO": print `typedef struct
 * _HSE_VERSION_INFO{DWORDdwExtensionVersion;
 * CHARlpszExtensionDesc[HSE_MAX_EXT_DLL_NAME_LEN];}
 * HSE_VERSION_INFO,*LPHSE_VERSION_INFO;` -- HSE_MAX_EXT_DLL_NAME_LEN
 * is not published on any CE page.
 * Extension DLL entry points (developer-implemented exports):
 *   aa450399 GetExtensionVersion:
 *     BOOL WINAPIGetExtensionVersion(HSE_VERSION_INFO* pVer );
 *   ms890326 HttpExtensionProc:
 *     DWORD WINAPI HttpExtensionProc(EXTENSION_CONTROL_BLOCK* pECB);
 *   aa450965 TerminateExtension:
 *     BOOL WINAPITerminateExtension(DWORD dwFlags );` */

#endif /* AKARI_HTTPEXT_H */
