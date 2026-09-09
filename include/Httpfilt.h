/* Httpfilt.h -- ISAPI Filters (Windows CE Web Server).
 *
 * Pages: tools/manifests/servers.manifest (Servers book, File
 * Transfer/HTTP filter surface); Link Library rows print "Not
 * applicable" (filter entry points are exported by the filter DLL,
 * not imported).  See docs/inventory.md M75f.
 */

#ifndef AKARI_HTTPFILT_H
#define AKARI_HTTPFILT_H

#include "Windef.h"    /* BOOL, DWORD, VOID, PVOID, LPSTR */

struct _HTTP_FILTER_CONTEXT;   /* forward: callback typedefs below */

/* ms900577 "SF_REQ_TYPE": print `enum SF_REQ_TYPE{
 * SF_REQ_SEND_RESPONSE_HEADER, SF_REQ_ADD_HEADERS_ON_DENIAL,
 * SF_REQ_SET_NEXT_READ_SIZE, SF_REQ_SET_PROXY_INFO,
 * SF_REQ_GET_CONNID, SF_REQ_SET_CERTIFICATE_INFO,
 * SF_REQ_GET_PROPERTY, SF_REQ_NORMALIZE_URL,
 * SF_REQ_DISABLE_NOTIFICATIONS} ;` -- no explicit values;
 * sequential from 0 per C semantics.  Page note: only
 * SF_REQ_ADD_HEADERS_ON_DENIAL, SF_REQ_DISABLE_NOTIFICATIONS and
 * SF_REQ_SEND_RESPONSE_HEADER are supported on Windows CE. */
enum SF_REQ_TYPE {
    SF_REQ_SEND_RESPONSE_HEADER,
    SF_REQ_ADD_HEADERS_ON_DENIAL,
    SF_REQ_SET_NEXT_READ_SIZE,
    SF_REQ_SET_PROXY_INFO,
    SF_REQ_GET_CONNID,
    SF_REQ_SET_CERTIFICATE_INFO,
    SF_REQ_GET_PROPERTY,
    SF_REQ_NORMALIZE_URL,
    SF_REQ_DISABLE_NOTIFICATIONS
};

/* --- Callback member signatures (documented on their own pages). - */

/* aa450424 "GetServerVariable (ISAPI Filters)": print
 * `BOOL (WINAPI* GetServerVariable) ( PHTTP_FILTER_CONTEXT pfc,
 * LPSTR lpszVariableName, LPVOID lpvBuffer, LPDWORD lpdwSize);` */
typedef BOOL (WINAPI *PFN_SF_GET_SERVER_VARIABLE)(
                    struct _HTTP_FILTER_CONTEXT *pfc,
                    LPSTR lpszVariableName, LPVOID lpvBuffer,
                    LPDWORD lpdwSize);

/* aa450281 "AddResponseHeaders": print
 * `BOOL WINAPI* AddResponseHeaders(PHTTP_FILTER_CONTEXTpfc,
 * LPSTRlpszHeaders,LPSTR dwReserved);` */
typedef BOOL (WINAPI *PFN_SF_ADD_RESPONSE_HEADERS)(
                    struct _HTTP_FILTER_CONTEXT *pfc,
                    LPSTR lpszHeaders, LPSTR dwReserved);

/* ms898726 "WriteClient (ISAPI Filters)": print
 * `BOOL (WINAPI* WriteClient)( PHTTP_FILTER_CONTEXT pfc,
 * LPVOID Buffer, LPDWORD lpdwBytes, DWORD dwReserved);` */
typedef BOOL (WINAPI *PFN_SF_WRITE_CLIENT)(
                    struct _HTTP_FILTER_CONTEXT *pfc,
                    LPVOID Buffer, LPDWORD lpdwBytes,
                    DWORD dwReserved);

/* aa450285 "AllocMem": print
 * `VOID* WINAPI* AllocMem(PHTTP_FILTER_CONTEXTpfc,DWORD cbSize,
 * DWORD dwReserved);` */
typedef VOID *(WINAPI *PFN_SF_ALLOC_MEM)(
                    struct _HTTP_FILTER_CONTEXT *pfc,
                    DWORD cbSize, DWORD dwReserved);

/* aa450890 "ServerSupportFunction (ISAPI Filters)": print
 * `BOOL (WINAPI* ServerSupportFunction)(PHTTP_FILTER_CONTEXTpfc,
 * enum SF_REQ_TYPE sfReq,PVOID pData,DWORDul1,DWORD ul2);` */
typedef BOOL (WINAPI *PFN_SF_SERVER_SUPPORT_FUNCTION)(
                    struct _HTTP_FILTER_CONTEXT *pfc,
                    enum SF_REQ_TYPE sfReq, PVOID pData,
                    DWORD ul1, DWORD ul2);

/* aa450402 "GetHeader": print
 * `BOOL (WINAPI* GetHeader)(PHTTP_FILTER_CONTEXTpfc,
 * LPSTR lpszName,LPVOID lpvBuffer,LPDWORDlpdwSize);`
 * aa450916 "SetHeader": print
 * `BOOL (WINAPI* SetHeader)(PHTTP_FILTER_CONTEXTpfc,
 * LPSTR lpszName,LPSTR lpszValue);`
 * aa450279 "AddHeader": print
 * `BOOL WINAPI* AddHeader(PHTTP_FILTER_CONTEXTpfc,
 * LPSTR lpszName,LPSTR lpszValue);` */
typedef BOOL (WINAPI *PFN_SF_GET_HEADER)(
                    struct _HTTP_FILTER_CONTEXT *pfc,
                    LPSTR lpszName, LPVOID lpvBuffer,
                    LPDWORD lpdwSize);
typedef BOOL (WINAPI *PFN_SF_SET_HEADER)(
                    struct _HTTP_FILTER_CONTEXT *pfc,
                    LPSTR lpszName, LPSTR lpszValue);
typedef BOOL (WINAPI *PFN_SF_ADD_HEADER)(
                    struct _HTTP_FILTER_CONTEXT *pfc,
                    LPSTR lpszName, LPSTR lpszValue);

/* --- Structures. ------------------------------------------------- */

/* ms890327 "HTTP_FILTER_CONTEXT": print (member parameter lists
 * carried by the callback pages above):
 * `typedef struct _HTTP_FILTER_CONTEXT {DWORDcbSize;DWORDRevision;
 * PVOIDServerContext;DWORDulReserved;BOOLfIsSecurePort;
 * PVOIDpFilterContext;BOOL(WINAPI* GetServerVariable);
 * BOOL(WINAPI* AddResponseHeaders);BOOL(WINAPI* WriteClient);
 * VOID* (WINAPI* AllocMem);BOOL (WINAPI* ServerSupportFunction);}
 * HTTP_FILTER_CONTEXT,*PHTTP_FILTER_CONTEXT;` */
typedef struct _HTTP_FILTER_CONTEXT {
    DWORD                       cbSize;
    DWORD                       Revision;
    PVOID                       ServerContext;
    DWORD                       ulReserved;
    BOOL                        fIsSecurePort;
    PVOID                       pFilterContext;
    PFN_SF_GET_SERVER_VARIABLE  GetServerVariable;
    PFN_SF_ADD_RESPONSE_HEADERS AddResponseHeaders;
    PFN_SF_WRITE_CLIENT         WriteClient;
    PFN_SF_ALLOC_MEM            AllocMem;
    PFN_SF_SERVER_SUPPORT_FUNCTION ServerSupportFunction;
} HTTP_FILTER_CONTEXT, *PHTTP_FILTER_CONTEXT;

/* ms900484 "HTTP_FILTER_PREPROC_HEADERS": print (full member
 * signatures printed on the struct page itself). */
typedef struct _HTTP_FILTER_PREPROC_HEADERS {
    BOOL (WINAPI *GetHeader)(struct _HTTP_FILTER_CONTEXT *pfc,
                             LPSTR lpszName, LPVOID lpvBuffer,
                             LPDWORD lpdwSize);
    BOOL (WINAPI *SetHeader)(struct _HTTP_FILTER_CONTEXT *pfc,
                             LPSTR lpszName, LPSTR lpszValue);
    BOOL (WINAPI *AddHeader)(struct _HTTP_FILTER_CONTEXT *pfc,
                             LPSTR lpszName, LPSTR lpszValue);
    DWORD HttpStatus;
    DWORD dwReserved;
} HTTP_FILTER_PREPROC_HEADERS, *PHTTP_FILTER_PREPROC_HEADERS;

/* ms890329 "HTTP_FILTER_SEND_RESPONSE": print (GetHeader/SetHeader/
 * AddHeader parameter lists not printed here -- closed with the
 * aa450402/aa450916/aa450279 signatures, same as PREPROC_HEADERS). */
typedef struct HTTP_FILTER_SEND_RESPONSE {
    BOOL (WINAPI *GetHeader)(struct _HTTP_FILTER_CONTEXT *pfc,
                             LPSTR lpszName, LPVOID lpvBuffer,
                             LPDWORD lpdwSize);
    BOOL (WINAPI *SetHeader)(struct _HTTP_FILTER_CONTEXT *pfc,
                             LPSTR lpszName, LPSTR lpszValue);
    BOOL (WINAPI *AddHeader)(struct _HTTP_FILTER_CONTEXT *pfc,
                             LPSTR lpszName, LPSTR lpszValue);
    DWORD HttpStatus;
    DWORD dwReserved;
} HTTP_FILTER_SEND_RESPONSE, *PHTTP_FILTER_SEND_RESPONSE;

/* ms900474 "HTTP_FILTER_ACCESS_DENIED": print. */
typedef struct _HTTP_FILTER_ACCESS_DENIED {
    const CHAR *pszURL;
    const CHAR *pszPhysicalPath;
    DWORD       dwReason;
} HTTP_FILTER_ACCESS_DENIED, *PHTTP_FILTER_ACCESS_DENIED;

/* ms900477 "HTTP_FILTER_AUTHENT": print. */
typedef struct _HTTP_FILTER_AUTHENT {
    CHAR  *pszUser;
    DWORD cbUserBuff;
    CHAR  *pszPassword;
    DWORD cbPasswordBuff;
} HTTP_FILTER_AUTHENT, *PHTTP_FILTER_AUTHENT;

/* ms900480 "HTTP_FILTER_LOG": print. */
typedef struct _HTTP_FILTER_LOG {
    const CHAR *pszClientHostName;
    const CHAR *pszClientUserName;
    const CHAR *pszServerName;
    const CHAR *pszOperation;
    const CHAR *pszTarget;
    const CHAR *pszParameters;
    DWORD       dwHttpStatus;
    DWORD       dwWin32Status;
    DWORD       dwBytesSent;
    DWORD       dwBytesRecvd;
    DWORD       msTimeForProcessing;
} HTTP_FILTER_LOG, *PHTTP_FILTER_LOG;

/* ms900487 "HTTP_FILTER_RAW_DATA": print. */
typedef struct _HTTP_FILTER_RAW_DATA {
    PVOID pvInData;
    DWORD cbInData;
    DWORD cbInBuffer;
    DWORD dwReserved;
} HTTP_FILTER_RAW_DATA, *PHTTP_FILTER_RAW_DATA;

/* ms900491 "HTTP_FILTER_URL_MAP": print. */
typedef struct _HTTP_FILTER_URL_MAP {
    const CHAR *pszURL;
    CHAR       *pszPhysicalPath;
    DWORD       cbPathBuff;
} HTTP_FILTER_URL_MAP, *PHTTP_FILTER_URL_MAP;

/* --- Record-only. -----------------------------------------------
 * ms890330 "HTTP_FILTER_VERSION": print `typedef struct
 * _HTTP_FILTER_VERSION{DWORDdwServerFilterVersion;
 * DWORDdwFilterVersion;CHARlpszFilterDesc[SF_MAX_FILTER_DESC_LEN];
 * DWORDdwFlags;} HTTP_FILTER_VERSION, *PHTTP_FILTER_VERSION;`
 * -- SF_MAX_FILTER_DESC_LEN is not published on any CE page.
 * Filter DLL entry points (developer-implemented exports):
 *   aa450400 GetFilterVersion:
 *     BOOL WINAPI GetFilterVersion(PHTTP_FILTER_VERSION pVer);
 *   ms890328 HttpFilterProc:
 *     DWORD WINAPI HttpFilterProc(PHTTP_FILTER_CONTEXT pfc,
 *       DWORD NotificationType,VOID* pvNotification);
 *   aa450967 TerminateFilter:
 *     BOOL WINAPI TerminateFilter( DWORD dwFlags);` */

#endif /* AKARI_HTTPFILT_H */
