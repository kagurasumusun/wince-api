/*
 * Wininet.h -- Windows Internet Services (WinInet) API for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE pages of
 * the Internet Client Services book (tools/manifests/
 * internetclient-book.manifest, M92 harvest; Requirements rows print
 * "Header: Wininet.h" and "Link Library: Wininet.lib").  Print repairs
 * are noted per site (BOOLAPI -> BOOL WINAPI, glued tokens, a dropped
 * comma in RetrieveUrlCacheEntryStream, LHANDLE -> HANDLE in
 * UnlockUrlCacheEntryStream, OPTIONAL annotation on InternetQueryOption).
 *
 * HOLD POLICY (the M79 FSD HDSK/HVOL precedent): the handle types
 * HINTERNET, GROUPID, INTERNET_PORT and the structures INTERNET_CACHE_
 * GROUP_INFO / INTERNET_CACHE_CONFIG_INFOA are USED by the printed
 * signatures but are not defined by any CE page in the corpus (verified
 * by full-corpus typedef search), so every function taking them BY
 * VALUE is recorded with its verbatim print rather than declared; the
 * functions whose parameter types all resolve (cache-entry, cookie,
 * URL-string, time and connection-state groups) are declared.
 * See docs/inventory.md M92.
 */

#ifndef AKARI_WININET_H
#define AKARI_WININET_H

#include "Windef.h"    /* BOOL, DWORD, LPVOID, HANDLE, LPTSTR, LPCTSTR */
#include "Winbase.h"   /* FILETIME, SYSTEMTIME, WINAPI */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Structures (full prints, compiled verbatim).                        */
/* ------------------------------------------------------------------ */

/* ms906352 "HTTP_VERSION_INFO": print `typedef struct
 * {DWORDdwMajorVersion;DWORDdwMinorVersion;} HTTP_VERSION_INFO,
 * *LPHTTP_VERSION_INFO;`. */
typedef struct {
    DWORD dwMajorVersion;
    DWORD dwMinorVersion;
} HTTP_VERSION_INFO, *LPHTTP_VERSION_INFO;

/* ms918339 "INTERNET_ASYNC_RESULT": print `typedef struct
 * {DWORDdwResult;DWORDdwError;} INTERNET_ASYNC_RESULT,
 * *LPINTERNET_ASYNC_RESULT;`. */
typedef struct {
    DWORD dwResult;
    DWORD dwError;
} INTERNET_ASYNC_RESULT, *LPINTERNET_ASYNC_RESULT;

/* ms918342 "INTERNET_BUFFERS": print `typedef struct _INTERNET_BUFFERS
 * {DWORDdwStructSize;_INTERNET_BUFFERS* Next;LPCTSTRlpcszHeader;
 * DWORDdwHeadersLength;DWORDdwHeadersTotal;LPVOIDlpvBuffer;
 * DWORDdwBufferLength;DWORDdwBufferTotal;DWORDdwOffsetLow;
 * DWORDdwOffsetHigh;} INTERNET_BUFFERS, *LPINTERNET_BUFFERS;`
 * (self-referential Next member as printed). */
typedef struct _INTERNET_BUFFERS {
    DWORD dwStructSize;
    struct _INTERNET_BUFFERS *Next;
    LPCTSTR lpcszHeader;
    DWORD dwHeadersLength;
    DWORD dwHeadersTotal;
    LPVOID lpvBuffer;
    DWORD dwBufferLength;
    DWORD dwBufferTotal;
    DWORD dwOffsetLow;
    DWORD dwOffsetHigh;
} INTERNET_BUFFERS, *LPINTERNET_BUFFERS;

/* ms918343 "INTERNET_CACHE_ENTRY_INFO": print (members verbatim; the
 * trailing anonymous union {DWORDdwReserved;DWORDdwExemptDelta;} as
 * printed). */
typedef struct _INTERNET_CACHE_ENTRY_INFO {
    DWORD dwStructSize;
    LPTSTR lpszSourceUrlName;
    LPTSTR lpszLocalFileName;
    DWORD CacheEntryType;
    DWORD dwUseCount;
    DWORD dwHitRate;
    DWORD dwSizeLow;
    DWORD dwSizeHigh;
    FILETIME LastModifiedTime;
    FILETIME ExpireTime;
    FILETIME LastAccessTime;
    FILETIME LastSyncTime;
    LPBYTE lpHeaderInfo;
    DWORD dwHeaderInfoSize;
    LPTSTR lpszFileExtension;
    union {
        DWORD dwReserved;
        DWORD dwExemptDelta;
    };
} INTERNET_CACHE_ENTRY_INFO, *LPINTERNET_CACHE_ENTRY_INFO;

/* ms918344 "INTERNET_CACHE_TIMESTAMPS": print `typedef struct
 * _INTERNET_CACHE_TIMESTAMPS {FILETIME ftExpires;FILETIME
 * ftLastModified;} INTERNET_CACHE_TIMESTAMPS,
 * *LPINTERNET_CACHE_TIMESTAMPS;`. */
typedef struct _INTERNET_CACHE_TIMESTAMPS {
    FILETIME ftExpires;
    FILETIME ftLastModified;
} INTERNET_CACHE_TIMESTAMPS, *LPINTERNET_CACHE_TIMESTAMPS;

/* ms918345 "INTERNET_CERTIFICATE_INFO": print (members verbatim). */
typedef struct {
    FILETIME ftExpiry;
    FILETIME ftStart;
    LPTSTR lpszSubjectInfo;
    LPTSTR lpszIssuerInfo;
    LPTSTR lpszProtocolName;
    LPTSTR lpszSignatureAlgName;
    LPTSTR lpszEncryptionAlgName;
    DWORD dwKeySize;
} INTERNET_CERTIFICATE_INFO, *LPINTERNET_CERTIFICATE_INFO;

/* ms918352 "INTERNET_CONNECTED_INFO": print `typedef struct
 * {DWORDdwConnectedState;DWORDdwFlags;} INTERNET_CONNECTED_INFO,
 * *LPINTERNET_CONNECTED_INFO;`. */
typedef struct {
    DWORD dwConnectedState;
    DWORD dwFlags;
} INTERNET_CONNECTED_INFO, *LPINTERNET_CONNECTED_INFO;

/* ms918370 "INTERNET_PER_CONN_OPTION": print `typedef struct
 * {DWORDdwOption;union {DWORDdwValue;LPTSTRpszValue;FILETIMEftValue;}
 * Value;} INTERNET_PER_CONN_OPTION, *LPINTERNET_PER_CONN_OPTION;`. */
typedef struct {
    DWORD dwOption;
    union {
        DWORD dwValue;
        LPTSTR pszValue;
        FILETIME ftValue;
    } Value;
} INTERNET_PER_CONN_OPTION, *LPINTERNET_PER_CONN_OPTION;

/* ms918371 "INTERNET_PER_CONN_OPTION_LIST": print `typedef struct
 * {DWORDdwSize;LPTSTRpszConnection;DWORDdwOptionCount;
 * DWORDdwOptionError;LPINTERNET_PER_CONN_OPTIONpOptions;}
 * INTERNET_PER_CONN_OPTION_LIST, *LPINTERNET_PER_CONN_OPTION_LIST;`. */
typedef struct {
    DWORD dwSize;
    LPTSTR pszConnection;
    DWORD dwOptionCount;
    DWORD dwOptionError;
    LPINTERNET_PER_CONN_OPTION pOptions;
} INTERNET_PER_CONN_OPTION_LIST, *LPINTERNET_PER_CONN_OPTION_LIST;

/* ms918372 "INTERNET_PROXY_INFO": print `typedef struct
 * {DWORDdwAccessType;LPCTSTRlpszProxy;LPCTSTRlpszProxyBypass;}
 * INTERNET_PROXY_INFO, *LPINTERNET_PROXY_INFO;`. */
typedef struct {
    DWORD dwAccessType;
    LPCTSTR lpszProxy;
    LPCTSTR lpszProxyBypass;
} INTERNET_PROXY_INFO, *LPINTERNET_PROXY_INFO;

/* ms918390 "INTERNET_VERSION_INFO": print `typedef struct
 * {DWORDdwMajorVersion;DWORDdwMinorVersion;} INTERNET_VERSION_INFO,
 * *LPINTERNET_VERSION_INFO;`. */
typedef struct {
    DWORD dwMajorVersion;
    DWORD dwMinorVersion;
} INTERNET_VERSION_INFO, *LPINTERNET_VERSION_INFO;

/* ms918377 "INTERNET_SCHEME": print `typedef enum {
 * INTERNET_SCHEME_PARTIAL = -2, INTERNET_SCHEME_UNKNOWN = -1,
 * INTERNET_SCHEME_DEFAULT = 0, INTERNET_SCHEME_FTP,
 * INTERNET_SCHEME_GOPHER, INTERNET_SCHEME_HTTP, INTERNET_SCHEME_HTTPS,
 * INTERNET_SCHEME_FILE, INTERNET_SCHEME_NEWS, INTERNET_SCHEME_MAILTO,
 * INTERNE...` (implicit values 1.. follow the printed order). */
typedef enum {
    INTERNET_SCHEME_PARTIAL = -2,
    INTERNET_SCHEME_UNKNOWN = -1,
    INTERNET_SCHEME_DEFAULT = 0,
    INTERNET_SCHEME_FTP,
    INTERNET_SCHEME_GOPHER,
    INTERNET_SCHEME_HTTP,
    INTERNET_SCHEME_HTTPS,
    INTERNET_SCHEME_FILE,
    INTERNET_SCHEME_NEWS,
    INTERNET_SCHEME_MAILTO
} INTERNET_SCHEME;

/* ------------------------------------------------------------------ */
/* HTTP status codes (ms906351; values printed in parentheses).        */
/* ------------------------------------------------------------------ */

#define HTTP_STATUS_CONTINUE                 100
#define HTTP_STATUS_SWITCH_PROTOCOLS         101
#define HTTP_STATUS_OK                       200
#define HTTP_STATUS_CREATED                  201
#define HTTP_STATUS_ACCEPTED                 202
#define HTTP_STATUS_PARTIAL                  203
#define HTTP_STATUS_NO_CONTENT               204
#define HTTP_STATUS_RESET_CONTENT            205
#define HTTP_STATUS_PARTIAL_CONTENT          206
#define HTTP_STATUS_AMBIGUOUS                300
#define HTTP_STATUS_MOVED                    301
#define HTTP_STATUS_REDIRECT                 302
#define HTTP_STATUS_REDIRECT_METHOD          303
#define HTTP_STATUS_NOT_MODIFIED             304
#define HTTP_STATUS_USE_PROXY                305
#define HTTP_STATUS_REDIRECT_KEEP_VERB       307
#define HTTP_STATUS_BAD_REQUEST              400
#define HTTP_STATUS_DENIED                   401
#define HTTP_STATUS_FORBIDDEN                403
#define HTTP_STATUS_NOT_FOUND                404
#define HTTP_STATUS_BAD_METHOD               405
#define HTTP_STATUS_NONE_ACCEPTABLE          406
#define HTTP_STATUS_PROXY_AUTH_REQ           407
#define HTTP_STATUS_REQUEST_TIMEOUT          408
#define HTTP_STATUS_CONFLICT                 409
#define HTTP_STATUS_GONE                     410
#define HTTP_STATUS_LENGTH_REQUIRED          411
#define HTTP_STATUS_PRECOND_FAILED           412
#define HTTP_STATUS_REQUEST_TOO_LARGE        413
#define HTTP_STATUS_URI_TOO_LONG             414
#define HTTP_STATUS_UNSUPPORTED_MEDIA        415
#define HTTP_STATUS_RETRY_WITH               449
#define HTTP_STATUS_SERVER_ERROR             500
#define HTTP_STATUS_NOT_SUPPORTED            501
#define HTTP_STATUS_BAD_GATEWAY              502
#define HTTP_STATUS_SERVICE_UNAVAIL          503
#define HTTP_STATUS_GATEWAY_TIMEOUT          504
#define HTTP_STATUS_VERSION_NOT_SUP          505

/* ms918353 "InternetCookieState" -- enum print with values: */
typedef enum InternetCookieState {
    COOKIE_STATE_UNKNOWN = 0x0,
    COOKIE_STATE_ACCEPT = 0x1,
    COOKIE_STATE_PROMPT = 0x2,
    COOKIE_STATE_LEASH = 0x3,
    COOKIE_STATE_DOWNGRADE = 0x4,
    COOKIE_STATE_REJECT = 0x5,
    COOKIE_STATE_MAX = COOKIE_STATE_REJECT
} InternetCookieState;

/* ms906348 "HTTP Response Headers" -- indices printed in parens. */
/* HTTP_QUERY_TITLE is on this page but absent from the ms918842   */
/* name list; the five ms918842-only modifiers stay value-less:     */
/* CONTENT_TRANSFER_ENCODING, CUSTOM, FLAG_NUMBER,                  */
/* FLAG_REQUEST_HEADERS, FLAG_SYSTEMTIME.                           */
#define HTTP_QUERY_MIME_VERSION                0
#define HTTP_QUERY_CONTENT_TYPE                1
#define HTTP_QUERY_CONTENT_ID                  3
#define HTTP_QUERY_CONTENT_LANGUAGE            6
#define HTTP_QUERY_ALLOW                       7
#define HTTP_QUERY_PUBLIC                      8
#define HTTP_QUERY_DATE                        9
#define HTTP_QUERY_EXPIRES                     10
#define HTTP_QUERY_LAST_MODIFIED               11
#define HTTP_QUERY_URI                         13
#define HTTP_QUERY_PRAGMA                      17
#define HTTP_QUERY_VERSION                     18
#define HTTP_QUERY_STATUS_CODE                 19
#define HTTP_QUERY_STATUS_TEXT                 20
#define HTTP_QUERY_RAW_HEADERS                 21
#define HTTP_QUERY_RAW_HEADERS_CRLF            22
#define HTTP_QUERY_CONNECTION                  23
#define HTTP_QUERY_ACCEPT                      24
#define HTTP_QUERY_ACCEPT_CHARSET              25
#define HTTP_QUERY_ACCEPT_ENCODING             26
#define HTTP_QUERY_ACCEPT_LANGUAGE             27
#define HTTP_QUERY_AUTHORIZATION               28
#define HTTP_QUERY_CONTENT_ENCODING            29
#define HTTP_QUERY_FROM                        31
#define HTTP_QUERY_IF_MODIFIED_SINCE           32
#define HTTP_QUERY_LOCATION                    33
#define HTTP_QUERY_REFERER                     35
#define HTTP_QUERY_RETRY_AFTER                 36
#define HTTP_QUERY_SERVER                      37
#define HTTP_QUERY_TITLE                       38
#define HTTP_QUERY_USER_AGENT                  39
#define HTTP_QUERY_WWW_AUTHENTICATE            40
#define HTTP_QUERY_PROXY_AUTHENTICATE          41
#define HTTP_QUERY_ACCEPT_RANGES               42
#define HTTP_QUERY_SET_COOKIE                  43
#define HTTP_QUERY_COOKIE                      44
#define HTTP_QUERY_REQUEST_METHOD              45
#define HTTP_QUERY_AGE                         48
#define HTTP_QUERY_CACHE_CONTROL               49
#define HTTP_QUERY_CONTENT_BASE                50
#define HTTP_QUERY_CONTENT_LOCATION            51
#define HTTP_QUERY_CONTENT_MD5                 52
#define HTTP_QUERY_CONTENT_RANGE               53
#define HTTP_QUERY_ETAG                        54
#define HTTP_QUERY_HOST                        55
#define HTTP_QUERY_IF_MATCH                    56
#define HTTP_QUERY_IF_NONE_MATCH               57
#define HTTP_QUERY_IF_RANGE                    58
#define HTTP_QUERY_IF_UNMODIFIED_SINCE         59
#define HTTP_QUERY_MAX_FORWARDS                60
#define HTTP_QUERY_PROXY_AUTHORIZATION         61
#define HTTP_QUERY_RANGE                       62
#define HTTP_QUERY_TRANSFER_ENCODING           63
#define HTTP_QUERY_UPGRADE                     64
#define HTTP_QUERY_VARY                        65
#define HTTP_QUERY_VIA                         66
#define HTTP_QUERY_WARNING                     67
#define HTTP_QUERY_EXPECT                      68
#define HTTP_QUERY_PROXY_CONNECTION            69
#define HTTP_QUERY_UNLESS_MODIFIED_SINCE       70
#define HTTP_QUERY_MAX                         75

/* ------------------------------------------------------------------ */
/* Held structures / types (used by prints, never defined on any CE
 * page -- full-corpus typedef search, M92):
 *   URL_COMPONENTS (ms918864): embeds INTERNET_PORT nPort by value.
 *   INTERNET_AUTH_NOTIFY_DATA (ms918341): print `typedef struct
 *     {DWORDcbStruct;DWORDdwOptions;PFN_PUTHNOTIFYpfnNotify;
 *     DWORD_PTRdwContext;} INTERNET_AUTH_NOTIFY_DATA;` -- the callback
 *     type is printed "PFN_PUTHNOTIFY" (archive typo for
 *     PFN_AUTHNOTIFY) and has no page of its own.
 *   INTERNET_STATUS_CALLBACK (ms918386): print `typedef void
 *     (CALLBACK* INTERNET_STATUS_CALLBACK) (HINTERNEThInternet,
 *     DWORD_PTRdwContext,DWORDdwInternetStatus,LPVOID
 *     lpvStatusInformation,DWORDdwStatusInformat...` -- HINTERNET by
 *     value in the callback shape; recorded.
 *   INTERNET_STATE_CONNECTED / _ONLINE / _DISCONNECTED / _OFFLINE /
 *     _DISCONNECTED_BY_USER / _OFFLINE_USER / _IDLE / _BUSY
 *     (ms918352 value table): names recorded, no values printed.
 * ------------------------------------------------------------------ */

/* ------------------------------------------------------------------ */
/* Flag name lists (value tables print NO values -- names recorded    */
/* only, the WM_SIDESHOW_* M82 precedent).                            */
/* ------------------------------------------------------------------ */

/* aa452096 "API Flags": 31 names, no values printed:
 *   INTERNET_FLAG_ASYNC INTERNET_FLAG_CACHE_ASYNC
 *   INTERNET_FLAG_CACHE_IF_NET_FAIL INTERNET_FLAG_DONT_CACHE
 *   INTERNET_FLAG_EXISTING_CONNECT INTERNET_FLAG_FORMS_SUBMIT
 *   INTERNET_FLAG_FROM_CACHE INTERNET_FLAG_FWD_BACK
 *   INTERNET_FLAG_HYPERLINK INTERNET_FLAG_IGNORE_CERT_CN_INVALID
 *   INTERNET_FLAG_IGNORE_CERT_DATE_INVALID
 *   INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP
 *   INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS INTERNET_FLAG_KEEP_CONNECTION
 *   INTERNET_FLAG_MUST_CACHE_REQUEST INTERNET_FLAG_NEED_FILE
 *   INTERNET_FLAG_NO_AUTH INTERNET_FLAG_NO_AUTO_REDIRECT
 *   INTERNET_FLAG_NO_CACHE_WRITE INTERNET_FLAG_NO_COOKIES
 *   INTERNET_FLAG_NO_UI INTERNET_FLAG_OFFLINE INTERNET_FLAG_PASSIVE
 *   INTERNET_FLAG_PRAGMA_NOCACHE INTERNET_FLAG_RAW_DATA
 *   INTERNET_FLAG_READ_PREFETCH INTERNET_FLAG_RELOAD
 *   INTERNET_FLAG_RESYNCHRONIZE INTERNET_FLAG_SECURE
 *   INTERNET_FLAG_TRANSFER_ASCII INTERNET_FLAG_TRANSFER_BINARY
 */

/* ms918831 "Option Flags": 46 names, no values printed:
 *   INTERNET_OPTION_BYPASS_EDITED_ENTRY INTERNET_OPTION_CACHE_TIMESTAMPS
 *   INTERNET_OPTION_CALLBACK INTERNET_OPTION_CLIENT_CERT_CONTEXT
 *   INTERNET_OPTION_CONNECTED_STATE INTERNET_OPTION_CONNECT_RETRIES
 *   INTERNET_OPTION_CONNECT_TIMEOUT INTERNET_OPTION_CONTEXT_VALUE
 *   INTERNET_OPTION_CONTROL_RECEIVE_TIMEOUT
 *   INTERNET_OPTION_CONTROL_SEND_TIMEOUT INTERNET_OPTION_DATAFILE_NAME
 *   INTERNET_OPTION_DIGEST_AUTH_UNLOAD
 *   INTERNET_OPTION_END_BROWSER_SESSION INTERNET_OPTION_ERROR_MASK
 *   INTERNET_OPTION_EXTENDED_ERROR INTERNET_OPTION_FROM_CACHE_TIMEOUT
 *   INTERNET_OPTION_HANDLE_TYPE INTERNET_OPTION_HTTP_VERSION
 *   INTERNET_OPTION_IGNORE_OFFLINE
 *   INTERNET_OPTION_MAX_CONNS_PER_1_0_SERVER
 *   INTERNET_OPTION_MAX_CONNS_PER_SERVER INTERNET_OPTION_PARENT_HANDLE
 *   INTERNET_OPTION_PASSWORD INTERNET_OPTION_PER_CONNECTION_OPTION
 *   INTERNET_OPTION_PROXY INTERNET_OPTION_PROXY_PASSWORD
 *   INTERNET_OPTION_PROXY_USERNAME INTERNET_OPTION_READ_BUFFER_SIZE
 *   INTERNET_OPTION_RECEIVE_THROUGHPUT INTERNET_OPTION_RECEIVE_TIMEOUT
 *   INTERNET_OPTION_REFRESH INTERNET_OPTION_REQUEST_FLAGS
 *   INTERNET_OPTION_REQUEST_PRIORITY
 *   INTERNET_OPTION_RESET_URLCACHE_SESSION
 *   INTERNET_OPTION_SECONDARY_CACHE_KEY
 *   INTERNET_OPTION_SECURITY_CERTIFICATE
 *   INTERNET_OPTION_SECURITY_CERTIFICATE_STRUCT
 *   INTERNET_OPTION_SECURITY_FLAGS INTERNET_OPTION_SECURITY_KEY_BITNESS
 *   INTERNET_OPTION_SEND_TIMEOUT INTERNET_OPTION_SETTINGS_CHANGED
 *   INTERNET_OPTION_URL INTERNET_OPTION_USERNAME
 *   INTERNET_OPTION_USER_AGENT INTERNET_OPTION_VERSION
 *   INTERNET_OPTION_WRITE_BUFFER_SIZE
 */

/* ms918842 "Query Info Flags": 66 names, no values printed:
 *   HTTP_QUERY_ACCEPT HTTP_QUERY_ACCEPT_CHARSET
 *   HTTP_QUERY_ACCEPT_ENCODING HTTP_QUERY_ACCEPT_LANGUAGE
 *   HTTP_QUERY_ACCEPT_RANGES HTTP_QUERY_AGE HTTP_QUERY_ALLOW
 *   HTTP_QUERY_AUTHORIZATION HTTP_QUERY_CACHE_CONTROL
 *   HTTP_QUERY_CONNECTION HTTP_QUERY_CONTENT_BASE
 *   HTTP_QUERY_CONTENT_ENCODING HTTP_QUERY_CONTENT_ID
 *   HTTP_QUERY_CONTENT_LANGUAGE HTTP_QUERY_CONTENT_LENGTH
 *   HTTP_QUERY_CONTENT_LOCATION HTTP_QUERY_CONTENT_MD5
 *   HTTP_QUERY_CONTENT_RANGE HTTP_QUERY_CONTENT_TRANSFER_ENCODING
 *   HTTP_QUERY_CONTENT_TYPE HTTP_QUERY_COOKIE HTTP_QUERY_CUSTOM
 *   HTTP_QUERY_DATE HTTP_QUERY_ETAG HTTP_QUERY_EXPECT HTTP_QUERY_EXPIRES
 *   HTTP_QUERY_FLAG_NUMBER HTTP_QUERY_FLAG_REQUEST_HEADERS
 *   HTTP_QUERY_FLAG_SYSTEMTIME HTTP_QUERY_FROM HTTP_QUERY_HOST
 *   HTTP_QUERY_IF_MATCH HTTP_QUERY_IF_MODIFIED_SINCE
 *   HTTP_QUERY_IF_NONE_MATCH HTTP_QUERY_IF_RANGE
 *   HTTP_QUERY_IF_UNMODIFIED_SINCE HTTP_QUERY_LAST_MODIFIED
 *   HTTP_QUERY_LOCATION HTTP_QUERY_MAX HTTP_QUERY_MAX_FORWARDS
 *   HTTP_QUERY_MIME_VERSION HTTP_QUERY_PRAGMA
 *   HTTP_QUERY_PROXY_AUTHENTICATE HTTP_QUERY_PROXY_AUTHORIZATION
 *   HTTP_QUERY_PROXY_CONNECTION HTTP_QUERY_PUBLIC HTTP_QUERY_RANGE
 *   HTTP_QUERY_RAW_HEADERS HTTP_QUERY_RAW_HEADERS_CRLF
 *   HTTP_QUERY_REFERER HTTP_QUERY_REQUEST_METHOD HTTP_QUERY_RETRY_AFTER
 *   HTTP_QUERY_SERVER HTTP_QUERY_SET_COOKIE HTTP_QUERY_STATUS_CODE
 *   HTTP_QUERY_STATUS_TEXT HTTP_QUERY_TRANSFER_ENCODING
 *   HTTP_QUERY_UNLESS_MODIFIED_SINCE HTTP_QUERY_UPGRADE HTTP_QUERY_URI
 *   HTTP_QUERY_USER_AGENT HTTP_QUERY_VARY HTTP_QUERY_VERSION
 *   HTTP_QUERY_VIA HTTP_QUERY_WARNING HTTP_QUERY_WWW_AUTHENTICATE
 */

/* ms918835 "Privacy Flags": 11 names, no values printed:
 *   PRIVACY_TEMPLATE_ADVANCED PRIVACY_TEMPLATE_CUSTOM
 *   PRIVACY_TEMPLATE_HIGH PRIVACY_TEMPLATE_LOW PRIVACY_TEMPLATE_MAX
 *   PRIVACY_TEMPLATE_MEDIUM PRIVACY_TEMPLATE_MEDIUM_LOW
 *   PRIVACY_TEMPLATE_NO_COOKIES PRIVACY_TEMPLATE__MEDIUM_HIGH
 *   PRIVACY_TYPE_FIRST_PARTY PRIVACY_TYPE_THIRD_PARTY
 */

/* ------------------------------------------------------------------ */
/* Functions -- declared (parameter types all resolve).               */
/* ------------------------------------------------------------------ */

/* ms918340 "InternetAttemptConnect": print `DWORD InternetAttemptConnect(DWORDdwReserved);`
 *. */
AKARI_CE_IMPORT DWORD InternetAttemptConnect(DWORD dwReserved)
                        AKARI_CE_NAME(InternetAttemptConnect);

/* ms918346 "InternetCheckConnection": print `BOOL InternetCheckConnection(LPCTSTRlpszUrl,DWORDdwFlags,DWORDdwReserved);`
 *. */
AKARI_CE_IMPORT BOOL InternetCheckConnection(LPCTSTR lpszUrl, DWORD dwFlags, DWORD dwReserved)
                        AKARI_CE_NAME(InternetCheckConnection);

/* ms918350 "InternetConfirmZoneCrossing": print `DWORDInternetConfirmZoneCrossing(HWNDhWnd,LPTSTRszUrlPrev,LPTSTRszUrlNew,BOOLbPost);`
 *. */
AKARI_CE_IMPORT DWORD InternetConfirmZoneCrossing(HWND hWnd, LPTSTR szUrlPrev, LPTSTR szUrlNew, BOOL bPost)
                        AKARI_CE_NAME(InternetConfirmZoneCrossing);

/* ms918349 "InternetCombineUrl": print `BOOL WINAPI InternetCombineUrl(LPCTSTR lpszBaseUrl, LPCTSTR lpszRelativeUrl, LPTSTR lpszBuffer, LPDWORD lpdwBufferLength, DWORD dwFlags);`
 *. */
AKARI_CE_IMPORT BOOL WINAPI InternetCombineUrl(LPCTSTR lpszBaseUrl, LPCTSTR lpszRelativeUrl, LPTSTR lpszBuffer, LPDWORD lpdwBufferLength, DWORD dwFlags)
                        AKARI_CE_NAME(InternetCombineUrl);

/* ms918356 "InternetEnumPerSiteCookieDecisionA": print `BOOL InternetEnumPerSiteCookieDecisionA( LPSTR pszSiteName, unsigned long *pcSiteNameSize, unsigned long *pdwDecision, unsigned long dwIndex);`
 *. */
AKARI_CE_IMPORT BOOL InternetEnumPerSiteCookieDecisionA(LPSTR pszSiteName, unsigned long *pcSiteNameSize, unsigned long *pdwDecision, unsigned long dwIndex)
                        AKARI_CE_NAME(InternetEnumPerSiteCookieDecisionA);

/* ms918357 "InternetEnumPerSiteCookieDecisionW": print `BOOL InternetEnumPerSiteCookieDecisionW( LPSTR pszSiteName, unsigned long *pcSiteNameSize, unsigned long *pdwDecision, unsigned long dwIndex);`
 *. */
AKARI_CE_IMPORT BOOL InternetEnumPerSiteCookieDecisionW(LPSTR pszSiteName, unsigned long *pcSiteNameSize, unsigned long *pdwDecision, unsigned long dwIndex)
                        AKARI_CE_NAME(InternetEnumPerSiteCookieDecisionW);

/* ms918360 "InternetGetConnectedState": print `BOOL InternetGetConnectedState(LPDWORD lpdwFlags,DWORD dwReserved);`
 *. */
AKARI_CE_IMPORT BOOL InternetGetConnectedState(LPDWORD lpdwFlags, DWORD dwReserved)
                        AKARI_CE_NAME(InternetGetConnectedState);

/* ms918361 "InternetGetConnectedStateEx": print `BOOLInternetGetConnectedStateEx(LPDWORDlpdwFlags,LPTSTRlpszConnectionName,DWORDdwNameLen,DWORDdwReserved);`
 * (glued "BOOLInternetGetConnectedStateEx" split). */
AKARI_CE_IMPORT BOOL InternetGetConnectedStateEx(LPDWORD lpdwFlags, LPTSTR lpszConnectionName, DWORD dwNameLen, DWORD dwReserved)
                        AKARI_CE_NAME(InternetGetConnectedStateEx);

/* ms918362 "InternetGetCookie": print `BOOL InternetGetCookie(LPCTSTR lpszUrl,LPCTSTR lpszCookieName,LPSTR lpCookieData,LPDWORD lpdwSize);`
 *. */
AKARI_CE_IMPORT BOOL InternetGetCookie(LPCTSTR lpszUrl, LPCTSTR lpszCookieName, LPSTR lpCookieData, LPDWORD lpdwSize)
                        AKARI_CE_NAME(InternetGetCookie);

/* ms918363 "InternetGetLastResponseInfo": print `BOOL WINAPI InternetGetLastResponseInfo( LPDWORD lpdwError, LPTSTR lpszBuffer, LPDWORD lpdwBufferLength);`
 *. */
AKARI_CE_IMPORT BOOL WINAPI InternetGetLastResponseInfo(LPDWORD lpdwError, LPTSTR lpszBuffer, LPDWORD lpdwBufferLength)
                        AKARI_CE_NAME(InternetGetLastResponseInfo);

/* ms918364 "InternetGetPerSiteCookieDecisionA": print `BOOL InternetGetPerSiteCookieDecisionA ( LPCSTR pchHostName, unsigned long* pResult);`
 *. */
AKARI_CE_IMPORT BOOL InternetGetPerSiteCookieDecisionA(LPCSTR pchHostName, unsigned long *pResult)
                        AKARI_CE_NAME(InternetGetPerSiteCookieDecisionA);

/* ms918365 "InternetGetPerSiteCookieDecisionW": print `BOOL InternetGetPerSiteCookieDecisionW ( LPCSTR pchHostName, unsigned long* pResult);`
 *. */
AKARI_CE_IMPORT BOOL InternetGetPerSiteCookieDecisionW(LPCSTR pchHostName, unsigned long *pResult)
                        AKARI_CE_NAME(InternetGetPerSiteCookieDecisionW);

/* ms918366 "InternetGoOnline": print `BOOL InternetGoOnline(LPTSTR lpszURL,HWND hwndParent,DWORD dwReserved);`
 *. */
AKARI_CE_IMPORT BOOL InternetGoOnline(LPTSTR lpszURL, HWND hwndParent, DWORD dwReserved)
                        AKARI_CE_NAME(InternetGoOnline);

/* ms918378 "InternetSetCookie": print `BOOL InternetSetCookie(LPCTSTR lpszUrl, LPCTSTR lpszCookieName, LPCTSTR lpszCookieData);`
 *. */
AKARI_CE_IMPORT BOOL InternetSetCookie(LPCTSTR lpszUrl, LPCTSTR lpszCookieName, LPCTSTR lpszCookieData)
                        AKARI_CE_NAME(InternetSetCookie);

/* ms918379 "InternetSetCookieEx": print `BOOL InternetSetCookieEx( LPCTSTRlpszUrl,LPCTSTRlpszCookieName,LPCTSTRlpszCookieData,DWORDdwFlags,DWORD_PTRdwReserved);`
 *. */
AKARI_CE_IMPORT BOOL InternetSetCookieEx(LPCTSTR lpszUrl, LPCTSTR lpszCookieName, LPCTSTR lpszCookieData, DWORD dwFlags, DWORD_PTR dwReserved)
                        AKARI_CE_NAME(InternetSetCookieEx);

/* ms918383 "InternetSetPerSiteCookieDecisionA": print `BOOL InternetSetPerSiteCookieDecisionA( LPCSTR pchHostName, DWORD dwDecision);`
 *. */
AKARI_CE_IMPORT BOOL InternetSetPerSiteCookieDecisionA(LPCSTR pchHostName, DWORD dwDecision)
                        AKARI_CE_NAME(InternetSetPerSiteCookieDecisionA);

/* ms918384 "InternetSetPerSiteCookieDecisionW": print `BOOL InternetSetPerSiteCookieDecisionW( LPCSTR pchHostName, DWORD dwDecision);`
 *. */
AKARI_CE_IMPORT BOOL InternetSetPerSiteCookieDecisionW(LPCSTR pchHostName, DWORD dwDecision)
                        AKARI_CE_NAME(InternetSetPerSiteCookieDecisionW);

/* ms918387 "InternetTimeFromSystemTime": print `BOOL WINAPI InternetTimeFromSystemTime(CONST SYSTEMTIME* pst, DWORD dwRFC, LPTSTR lpszTime, DWORD cbTime);`
 *. */
AKARI_CE_IMPORT BOOL WINAPI InternetTimeFromSystemTime(const SYSTEMTIME *pst, DWORD dwRFC, LPTSTR lpszTime, DWORD cbTime)
                        AKARI_CE_NAME(InternetTimeFromSystemTime);

/* ms918388 "InternetTimeToSystemTime": print `BOOL InternetTimeToSystemTime(LPCTSTR lpszTime, SYSTEMTIME* pst, DWORD dwReserved);`
 *. */
AKARI_CE_IMPORT BOOL InternetTimeToSystemTime(LPCTSTR lpszTime, SYSTEMTIME *pst, DWORD dwReserved)
                        AKARI_CE_NAME(InternetTimeToSystemTime);

/* ms918389 "InternetUnlockRequestFile": print `BOOL InternetUnlockRequestFile(HANDLE hLockRequestInfo);`
 *. */
AKARI_CE_IMPORT BOOL InternetUnlockRequestFile(HANDLE hLockRequestInfo)
                        AKARI_CE_NAME(InternetUnlockRequestFile);

/* aa452121 "CommitUrlCacheEntry": print `BOOL CommitUrlCacheEntry( LPCTSTR lpszUrlName,LPCTSTR lpszLocalFileName,FILETIME ExpireTime,FILETIME LastModifiedTime,DWORD CacheEntryType,LPBYTE lpHeaderInfo,DWORD dwHeaderSize,LPCTSTR lpszFileExtension,DWORD dwReserved);`
 *. */
AKARI_CE_IMPORT BOOL CommitUrlCacheEntry(LPCTSTR lpszUrlName, LPCTSTR lpszLocalFileName, FILETIME ExpireTime, FILETIME LastModifiedTime, DWORD CacheEntryType, LPBYTE lpHeaderInfo, DWORD dwHeaderSize, LPCTSTR lpszFileExtension, DWORD dwReserved)
                        AKARI_CE_NAME(CommitUrlCacheEntry);

/* aa452142 "CreateUrlCacheEntry": print `BOOL CreateUrlCacheEntry( LPCTSTR lpszUrlName,DWORD dwExpectedFileSize,LPCTSTR lpszFileExtension,LPSTR lpszFileName,DWORD dwReserved);`
 *. */
AKARI_CE_IMPORT BOOL CreateUrlCacheEntry(LPCTSTR lpszUrlName, DWORD dwExpectedFileSize, LPCTSTR lpszFileExtension, LPSTR lpszFileName, DWORD dwReserved)
                        AKARI_CE_NAME(CreateUrlCacheEntry);

/* aa452150 "DeleteUrlCacheEntry": print `BOOL DeleteUrlCacheEntry( LPCTSTR lpszUrlName);`
 *. */
AKARI_CE_IMPORT BOOL DeleteUrlCacheEntry(LPCTSTR lpszUrlName)
                        AKARI_CE_NAME(DeleteUrlCacheEntry);

/* aa452195 "FindCloseUrlCache": print `BOOL FindCloseUrlCache( HANDLE hEnumHandle);`
 *. */
AKARI_CE_IMPORT BOOL FindCloseUrlCache(HANDLE hEnumHandle)
                        AKARI_CE_NAME(FindCloseUrlCache);

/* ms919204 "FindNextUrlCacheEntry": print `BOOL FindNextUrlCacheEntry( HANDLE hEnumHandle,LPINTERNET_CACHE_ENTRY_INFO lpNextCacheEntryInfo,LPDWORD lpdwNextCacheEntryInfoBufferSize);`
 *. */
AKARI_CE_IMPORT BOOL FindNextUrlCacheEntry(HANDLE hEnumHandle, LPINTERNET_CACHE_ENTRY_INFO lpNextCacheEntryInfo, LPDWORD lpdwNextCacheEntryInfoBufferSize)
                        AKARI_CE_NAME(FindNextUrlCacheEntry);

/* aa452206 "FindNextUrlCacheEntryEx": print `BOOLAPI FindNextUrlCacheEntryEx( HANDLE hEnumHandle,LPINTERNET_CACHE_ENTRY_INFO lpFirstCacheEntryInfo,LPDWORD lpdwFirstCacheEntryInfoBufferSize,LPVOID lpGroupAttributes,LPDWORD pcbGroupAttributes,LPVOID lpReserved);`
 * (print "BOOLAPI" read as BOOL WINAPI). */
AKARI_CE_IMPORT BOOL WINAPI FindNextUrlCacheEntryEx(HANDLE hEnumHandle, LPINTERNET_CACHE_ENTRY_INFO lpFirstCacheEntryInfo, LPDWORD lpdwFirstCacheEntryInfoBufferSize, LPVOID lpGroupAttributes, LPDWORD pcbGroupAttributes, LPVOID lpReserved)
                        AKARI_CE_NAME(FindNextUrlCacheEntryEx);

/* ms906320 "GetUrlCacheEntryInfo": print `BOOL GetUrlCacheEntryInfo( LPCTSTR lpszUrlName,LPINTERNET_CACHE_ENTRY_INFO lpCacheEntryInfo,LPDWORD lpdwCacheEntryInfoBufferSize);`
 *. */
AKARI_CE_IMPORT BOOL GetUrlCacheEntryInfo(LPCTSTR lpszUrlName, LPINTERNET_CACHE_ENTRY_INFO lpCacheEntryInfo, LPDWORD lpdwCacheEntryInfoBufferSize)
                        AKARI_CE_NAME(GetUrlCacheEntryInfo);

/* ms906328 "GetUrlCacheEntryInfoEx": print `BOOL GetUrlCacheEntryInfoEx( LPCSTR lpszUrl,LPINTERNET_CACHE_ENTRY_INFO lpCacheEntryInfo,LPDWORD lpdwCacheEntryInfoBufSize,LPSTRlpszReserved,LPDWORDlpdwReserved,LPVOIDlpReserved,DWORDdwFlags);`
 *. */
AKARI_CE_IMPORT BOOL GetUrlCacheEntryInfoEx(LPCSTR lpszUrl, LPINTERNET_CACHE_ENTRY_INFO lpCacheEntryInfo, LPDWORD lpdwCacheEntryInfoBufSize, LPSTR lpszReserved, LPDWORD lpdwReserved, LPVOID lpReserved, DWORD dwFlags)
                        AKARI_CE_NAME(GetUrlCacheEntryInfoEx);

/* aa452489 "ReadUrlCacheEntryStream": print `BOOL ReadUrlCacheEntryStream( HANDLE hUrlCacheStream,DWORD dwLocation, LPVOIDlpBuffer,LPDWORDlpdwLen, DWORDdwReserved );`
 *. */
AKARI_CE_IMPORT BOOL ReadUrlCacheEntryStream(HANDLE hUrlCacheStream, DWORD dwLocation, LPVOID lpBuffer, LPDWORD lpdwLen, DWORD dwReserved)
                        AKARI_CE_NAME(ReadUrlCacheEntryStream);

/* aa452490 "RetrieveUrlCacheEntryStream": print `HANDLE RetrieveUrlCacheEntryStream( LPCTSTR lpszUrlName LPINTERNET_CACHE_ENTRY_INFO lpCacheEntryInfo, LPDWORD lpdwCacheEntryInfoBufferSize, BOOL fRandomRead, DWORD dwReserved);`
 * (print drops the comma between lpszUrlName and the info pointer). */
AKARI_CE_IMPORT HANDLE RetrieveUrlCacheEntryStream(LPCTSTR lpszUrlName, LPINTERNET_CACHE_ENTRY_INFO lpCacheEntryInfo, LPDWORD lpdwCacheEntryInfoBufferSize, BOOL fRandomRead, DWORD dwReserved)
                        AKARI_CE_NAME(RetrieveUrlCacheEntryStream);

/* ms918849 "RetrieveUrlCacheEntryFile": print `BOOLRetrieveUrlCacheEntryFile(LPCTSTRlpszUrlName, LPINTERNET_CACHE_ENTRY_INFOlpCacheEntryInfo,LPDWORDlpdwCacheEntryInfoBufferSize, DWORDdwReserved);`
 * (glued "BOOLRetrieveUrlCacheEntryFile" split). */
AKARI_CE_IMPORT BOOL RetrieveUrlCacheEntryFile(LPCTSTR lpszUrlName, LPINTERNET_CACHE_ENTRY_INFO lpCacheEntryInfo, LPDWORD lpdwCacheEntryInfoBufferSize, DWORD dwReserved)
                        AKARI_CE_NAME(RetrieveUrlCacheEntryFile);

/* ms918858 "SetUrlCacheEntryInfo": print `BOOLSetUrlCacheEntryInfo(LPCSTRlpszUrlName,LPINTERNET_CACHE_ENTRY_INFOlpCacheEntryInfo,DWORDdwFieldControl);`
 * (glued "BOOLSetUrlCacheEntryInfo" split). */
AKARI_CE_IMPORT BOOL SetUrlCacheEntryInfo(LPCSTR lpszUrlName, LPINTERNET_CACHE_ENTRY_INFO lpCacheEntryInfo, DWORD dwFieldControl)
                        AKARI_CE_NAME(SetUrlCacheEntryInfo);

/* ms918862 "UnlockUrlCacheEntryFile": print `BOOLUnlockUrlCacheEntryFile(LPCSTRlpszUrlName,DWORDdwReserved);`
 * (glued "BOOLUnlockUrlCacheEntryFile" split). */
AKARI_CE_IMPORT BOOL UnlockUrlCacheEntryFile(LPCSTR lpszUrlName, DWORD dwReserved)
                        AKARI_CE_NAME(UnlockUrlCacheEntryFile);

/* aa452493 "UnlockUrlCacheEntryStream": print `BOOL UnlockUrlCacheEntryStream( LHANDLE hUrlCacheStream, DWORD dwReserved);`
 * (print spells the handle "LHANDLE" -- HANDLE). */
AKARI_CE_IMPORT BOOL UnlockUrlCacheEntryStream(HANDLE hUrlCacheStream, DWORD dwReserved)
                        AKARI_CE_NAME(UnlockUrlCacheEntryStream);

/* ------------------------------------------------------------------ */
/* Functions -- recorded (HINTERNET / GROUPID / INTERNET_PORT /        */
/* INTERNET_CACHE_GROUP_INFO / INTERNET_CACHE_CONFIG_INFOA by value).  */
/* ------------------------------------------------------------------ */

/* ms918355 "InternetCreateUrl": `BOOL WINAPI InternetCreateUrl(LPURL_COMPONENTS lpUrlComponents, DWORD dwFlags, LPTSTR lpszUrl, LPDWORD lpdwUrlLength );` */
/* ms918354 "InternetCrackUrl": `BOOL WINAPIInternetCrackUrl(LPCTSTRlpszUrl,DWORDdwUrlLength,DWORDdwFlags,LPURL_COMPONENTSlpUrlComponents);` */
/* ms918391 "InternetWriteFile": `BOOL InternetWriteFile(HINTERNET hFile,LPCVOIDlpBuffer,DWORDdwNumberOfBytesToWrite,LPDWORDlpdwNumberOfBytesWritten);` */
/* ms918348 "InternetCloseHandle": `BOOL WINAPI InternetCloseHandle(HINTERNEThInternet);` */
/* ms918351 "InternetConnect": `HINTERNET WINAPI InternetConnect(HINTERNET hInternet, LPCTSTR lpszServerName, INTERNET_PORT nServerPort, LPCTSTR lpszUserName, LPCTSTR lpszPassword, DWORD dwService, DWORD dwFlags, DWORD dwContext);` */
/* ms918358 "InternetErrorDlg": `DWORD InternetErrorDlg(HWND hWnd, HINTERNET hRequest,DWORD dwError,DWORD dwFlags,LPVOID* lppvData);` */
/* ms918359 "InternetFindNextFile": `BOOL WINAPI InternetFindNextFile(HINTERNET hFind, LPVOID lpvFindData);` */
/* ms918367 "InternetLockRequestFile": `BOOL InternetLockRequestFile(HINTERNEThInternet,HANDLE* lphLockRequestInfo);` */
/* ms918368 "InternetOpen": `HINTERNET WINAPI InternetOpen(LPCTSTRlpszAgent,DWORD dwAccessType, LPCTSTR lpszProxy, LPCTSTR lpszProxyBypass, DWORD dwFlags);` */
/* ms918369 "InternetOpenUrl": `HINTERNET InternetOpenUrl( HINTERNET hInternetSession, LPCTSTR lpszUrl, LPCTSTR lpszHeaders, DWORD dwHeadersLength, DWORD dwFlags, DWORD dwContext);` */
/* ms918373 "InternetQueryDataAvailable": `BOOL WINAPI InternetQueryDataAvailable(HINTERNET hFile, LPDWORD lpdwNumberOfBytesAvailable, DWORD dwFlags, DWORD dwContext);` */
/* ms918374 "InternetQueryOption": `BOOL WINAPI InternetQueryOption(HINTERNET hInternet, DWORD dwOption, LPVOID lpBuffer OPTIONAL, LPDWORD lpdwBufferLength);` */
/* ms918375 "InternetReadFile": `BOOL WINAPI InternetReadFile(HINTERNEThFile,LPVOIDlpBuffer,DWORDdwNumberOfBytesToRead,LPDWORDlpdwNumberOfBytesRead);` */
/* ms918376 "InternetReadFileEx": `BOOL InternetReadFileEx(HINTERNEThFile,LPINTERNET_BUFFERS lpBuffersOut,DWORD dwFlags,DWORD dwContext);` */
/* ms918380 "InternetSetFilePointer": `DWORD InternetSetFilePointer(HINTERNET hFile,LONG lDistanceToMove, PVOID pReserved, DWORD dwMoveMethod,DWORD dwContext);` */
/* ms918381 "InternetSetOption": `BOOL WINAPI InternetSetOption(HINTERNET hInternet, DWORD dwOption, LPVOID lpBuffer, DWORD dwBufferLength);` */
/* ms918382 "InternetSetOptionEx": `(stub: the page states it only calls InternetSetOption and has no functionality of its own; no signature printed)` */
/* ms918385 "InternetSetStatusCallback": `INTERNET_STATUS_CALLBACK WINAPIInternetSetStatusCallback(HINTERNEThInternet,...` */
/* aa452208 "FtpCommand": `BOOL WINAPI FtpCommand(HINTERNET hConnect, BOOL fExpectResponse, DWORD dwFlags, LPCTSTR lpszCommand, DWORD dwContext);` */
/* aa452210 "FtpCreateDirectory": `BOOL WINAPI FtpCreateDirectory(HINTERNET hConnect, LPCTSTR lpszDirectory);` */
/* aa452212 "FtpDeleteFile": `BOOL WINAPI FtpDeleteFile(HINTERNET hConnect, LPCTSTR lpszFileName);` */
/* aa452214 "FtpFindFirstFile": `HINTERNET FtpFindFirstFile(HINTERNET hConnect, LPCTSTR lpszSearchFile, LPWIN32_FIND_DATA lpFindFileData, DWORD dwFlags, DWORD dwContext);` */
/* aa452216 "FtpGetCurrentDirectory": `BOOL WINAPI FtpGetCurrentDirectory(HINTERNET hConnect, LPCTSTR lpszCurrentDirectory, LPDWORD lpdwCurrentDirectory);` */
/* aa452218 "FtpGetFile": `BOOL WINAPI FtpGetFile(HINTERNET hConnect, LPCTSTR lpszRemoteFile, LPCTSTR lpszNewFile, BOOL fFailIfExists, DWORD dwFlagsAndAttributes, DWORD dwFlags, DWORD dwContext);` */
/* aa452230 "FtpGetFileEx": `BOOL WINAPI FtpGetFileEx(HINTERNEThFtpSession,LPCTSTR lpszRemoteFile, LPCTSTR lpszNewFile, BOOL fFailIfExists, DWORD dwFlagsAndAttributes, DWORD dwFlags, DWORD dwContext);` */
/* aa452232 "FtpGetFileSize": `DWORD FtpGetFileSize(HINTERNEThFile,LPDWORDlpdwFileSizeHigh);` */
/* aa452234 "FtpOpenFile": `HINTERNET FtpOpenFile(HINTERNET hConnect, LPCTSTR lpszFileName, DWORD dwAccess, DWORD dwFlags, DWORD dwContext);` */
/* aa452236 "FtpPutFile": `BOOL WINAPI FtpPutFile(HINTERNET hConnect, LPCTSTR lpszLocalFile, LPCTSTR lpszNewRemoteFile, DWORD dwFlags, DWORD dwContext);` */
/* aa452238 "FtpPutFileEx": `BOOLAPI FtpPutFileEx(HINTERNET hFtpSession, LPCTSTR lpszLocalFile, LPCTSTR lpszNewRemoteFile, DWORD dwFlags, DWORD dwContext);` */
/* aa452240 "FtpRemoveDirectory": `BOOL WINAPI FtpRemoveDirectory(HINTERNET hConnect, LPCTSTR lpszDirectory);` */
/* ms906192 "FtpRenameFile": `BOOL WINAPI FtpRenameFile(HINTERNET hConnect, LPCTSTR lpszExisting, LPCTSTR lpszNew);` */
/* ms906282 "FtpSetCurrentDirectory": `BOOL WINAPI FtpSetCurrentDirectory(HINTERNET hConnect, LPCTSTR lpszDirectory);` */
/* ms906344 "HttpAddRequestHeaders": `BOOL WINAPI HttpAddRequestHeaders(HINTERNET hHttpRequest, LPCTSTR lpszHeaders, DWORD dwHeadersLength, DWORD dwModifiers);` */
/* ms906345 "HttpEndRequest": `BOOL HttpEndRequest(HINTERNET hRequest,LPINTERNET_BUFFERS lpBuffersOut, DWORD dwFlags,DWORD dwContext);` */
/* ms906346 "HttpOpenRequest": `HINTERNET WINAPI HttpOpenRequest(HINTERNET hConnect, LPCTSTR lpszVerb, LPCTSTR lpszObjectName, LPCTSTR lpszVersion, LPCTSTR lpszReferrer, LPCTSTR* lplpszAcceptTypes, DWORD dwFlags, DWORD dwContext );` */
/* ms906347 "HttpQueryInfo": `BOOL WINAPI HttpQueryInfo(HINTERNET hRequest, DWORD dwInfoLevel, LPVOID lpBuffer, LPDWORD lpdwBufferLength, LPDWORD lpdwIndex);` */
/* ms906349 "HttpSendRequest": `BOOL WINAPI HttpSendRequest(HINTERNET hRequest, LPCTSTR lpszHeaders, DWORD dwHeadersLength, LPVOID lpOptional, DWORD dwOptionalLength);` */
/* ms906350 "HttpSendRequestEx": `BOOL HttpSendRequestEx(HINTERNET hRequest, LPINTERNET_BUFFERS lpBuffersIn,LPINTERNET_BUFFERS lpBuffersOut,DWORD dwFlags,DWORD dwContext);` */
/* aa452433 "CreateUrlCacheGroup": `GROUPID CreateUrlCacheGroup( DWORDdwFlags, LPVOIDlpReserved);` */
/* aa452434 "DeleteUrlCacheGroup": `BOOL DeleteUrlCacheGroup( GROUPIDGroupId, DWORDdwFlags, LPVOIDlpReserved)` */
/* ms919201 "FindFirstUrlCacheEntryEx": `HANDLE FindFirstUrlCacheEntryEx( LPCWSTR lpszUrlSearchPattern,DWORD dwFlags,DWORD dwFilter,GROUPID GroupId,LPINTERNET_CACHE_ENTRY_INFO lpFirstCacheEntryInfo,LPDWORD lpdwFirstCacheEntryInfoBufferSize,LPVOID lpGroupAttributes,LPDWORD pcbGroupAttributes,LPVOID lpReserved);` */
/* aa452486 "FindFirstUrlCacheGroup": `BOOL FindFirstUrlCacheGroup( DWORDdwFlags, DWORDdwFilter, LPVOIDlpSearchCondition, DWORDdwSearchCondition, GROUPID*lpGroupId, LPVOIDlpReserved);` */
/* aa452487 "FindNextUrlCacheGroup": `BOOL FindNextUrlCacheGroup( HANDLEhFind, GROUPID*lpGroupId, LPVOIDlpReserved);` */
/* aa452488 "GetUrlCacheGroupAttribute": `BOOL GetUrlCacheGroupAttribute( GROUPIDgid, DWORDdwFlags, DWORDdwAttributes, LPINTERNET_CACHE_GROUP_INFOlpGroupInfo, LPWORDlpdwGroupInfo, LPVOIDlpReserved);` */
/* aa452491 "SetUrlCacheEntryGroup": `BOOL SetUrlCacheEntryGroup( LPCTSTR lpszUrlName, DWORD dwFlags, GROUPID GroupId, LPBYTE pbGroupAttributes, DWORD cbGroupAttributes, LPVOID lpReserved);` */
/* aa452492 "SetUrlCacheGroupAttribute": `BOOL SetUrlCacheGroupAttribute( GROUPID gid, DWORD dwFlags, DWORD dwAttributes, LPINTERNET_CACHE_GROUP_INFO lpGroupInfo, LPVOID lpReserved);` */
/* ms905355 "SetUrlCacheConfigInfo": `BOOLAPI SetUrlCacheConfigInfoA(LPINTERNET_CACHE_CONFIG_INFOAlpCacheConfigInfo, DWORDdwFieldControl);` */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WININET_H */
