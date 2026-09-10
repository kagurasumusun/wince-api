/*
 * Wininet.h -- Windows Internet Services (WinInet) API for Windows CE.
 *
 * Row accounting (M93): 83 Wininet.lib rows = 82 function pages +
 * ms918386 INTERNET_STATUS_CALLBACK (held typedef record).  82 function
 * rows: 35 declared, 47 recorded.  aa452197 FindFirstUrlCacheEntry is
 * the one function page whose Requirements prints NO Header row (only
 * OS + Link Library: Wininet.lib) -- the header home is implicit and
 * the M92 header-row sweep missed it; all parameter types resolve
 * (INTERNET_CACHE_ENTRY_INFO is compiled below) so it declares.
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

/* ms926106 "InternetCanonicalizeUrl" (Security book row, Windows CE
 * 2.0 and later; the page's Requirements print "Header: Wininet.h.
 * Link Library: Secur32.lib." -- the archive's own cross-book quirk;
 * the def placement follows the printed Link Library row, so the
 * import is carried by def/secur32-doc.def): print `BOOL WINAPI InternetCanonicalizeUrl(LPCTSTRlpszUrl,LPWSTRlpszBuffer,LPDWORDlpdwBufferLength,DWORDdwFlags );`
 *.  dwFlags: the ICU_* modifiers (values in the M96 section). */
AKARI_CE_IMPORT BOOL WINAPI InternetCanonicalizeUrl(LPCTSTR lpszUrl,
    LPWSTR lpszBuffer, LPDWORD lpdwBufferLength, DWORD dwFlags)
                        AKARI_CE_NAME(InternetCanonicalizeUrl);

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

/* aa452197 "FindFirstUrlCacheEntry": print `HANDLE FindFirstUrlCacheEntry( LPCTSTR lpszUrlSearchPattern,LPINTERNET_CACHE_ENTRY_INFO lpFirstCacheEntryInfo,LPDWORD lpdwFirstCacheEntryInfoBufferSize);`
 *. */
AKARI_CE_IMPORT HANDLE FindFirstUrlCacheEntry(LPCTSTR lpszUrlSearchPattern, LPINTERNET_CACHE_ENTRY_INFO lpFirstCacheEntryInfo, LPDWORD lpdwFirstCacheEntryInfoBufferSize)
                        AKARI_CE_NAME(FindFirstUrlCacheEntry);

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

/* ================================================================== */
/* M96 value adoption -- values adopted from the CeGCC-lineage w32api
 * reference (R1, public domain; docs/clean-room.md par.4
 * revision 2026-09-10).  Every name below is documented by
 * the official CE pages WITHOUT a value (see the record
 * comments and the held ledger in this header); the value
 * is a CE-era ABI fact carried by the CE lineage itself.
 * Desktop mingw-w64 was considered and EXCLUDED as a source
 * (desktop-era values; policy note in clean-room.md).  R1's
 * license-exception files (winsock*, gl*) are unused.
 * ================================================================== */

/* ---- CACHE_ family (7 names; R1) ---- */
#define CACHE_ENTRY_ATTRIBUTE_FC                     0x0004
#define CACHE_ENTRY_HITRATE_FC                       0x0010
#define CACHE_ENTRY_MODTIME_FC                       0x0040
#define CACHE_ENTRY_EXPTIME_FC                       0x0080
#define CACHE_ENTRY_ACCTIME_FC                       0x0100
#define CACHE_ENTRY_SYNCTIME_FC                      0x0200
#define CACHE_ENTRY_HEADERINFO_FC                    0x0400

/* ---- COOKIE_ family (1 names; R1) ---- */
#define COOKIE_CACHE_ENTRY                           0x100000

/* ---- ERROR_ family (14 names; R1) ---- */
#define ERROR_INTERNET_EXTENDED_ERROR                0x2EE3
#define ERROR_INTERNET_INVALID_URL                   0x2EE5
#define ERROR_INTERNET_INCORRECT_PASSWORD            0x2EEE
#define ERROR_INTERNET_CANNOT_CONNECT                0x2EFD
#define ERROR_INTERNET_CONNECTION_RESET              0x2EFF
#define ERROR_INTERNET_FORCE_RETRY                   0x2F00
#define ERROR_INTERNET_SEC_CERT_DATE_INVALID         0x2F05
#define ERROR_INTERNET_SEC_CERT_CN_INVALID           0x2F06
#define ERROR_INTERNET_HTTP_TO_HTTPS_ON_REDIR        0x2F07
#define ERROR_INTERNET_HTTPS_TO_HTTP_ON_REDIR        0x2F08
#define ERROR_INTERNET_POST_IS_NON_SECURE            0x2F0B
#define ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED       0x2F0C
#define ERROR_INTERNET_INVALID_CA                    0x2F0D
#define ERROR_HTTP_HEADER_NOT_FOUND                  0x2F76

/* ---- FLAGS_ family (3 names; R1) ---- */
#define FLAGS_ERROR_UI_FILTER_FOR_ERRORS             0x0001
#define FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS          0x0002
#define FLAGS_ERROR_UI_FLAGS_GENERATE_DATA           0x0004

/* ---- HTTP_ family (19 names; R1) ---- */
#define HTTP_QUERY_CONTENT_TRANSFER_ENCODING         0x0002
#define HTTP_QUERY_CONTENT_DESCRIPTION               0x0004
#define HTTP_QUERY_CONTENT_LENGTH                    0x0005
#define HTTP_QUERY_MESSAGE_ID                        0x000C
#define HTTP_QUERY_DERIVED_FROM                      0x000E
#define HTTP_QUERY_COST                              0x000F
#define HTTP_QUERY_LINK                              0x0010
#define HTTP_QUERY_FORWARDED                         0x001E
#define HTTP_QUERY_ORIG_URI                          0x0022
#define HTTP_QUERY_CUSTOM                            0xFFFF
#define HTTP_ADDREQ_FLAG_COALESCE_WITH_SEMICOLON     0x1000000
#define HTTP_ADDREQ_FLAG_ADD_IF_NEW                  0x10000000
#define HTTP_ADDREQ_FLAG_ADD                         0x20000000
#define HTTP_QUERY_FLAG_NUMBER                       0x20000000
#define HTTP_ADDREQ_FLAG_COALESCE                    0x40000000
#define HTTP_ADDREQ_FLAG_COALESCE_WITH_COMMA         0x40000000
#define HTTP_QUERY_FLAG_SYSTEMTIME                   0x40000000
#define HTTP_ADDREQ_FLAG_REPLACE                     0x80000000
#define HTTP_QUERY_FLAG_REQUEST_HEADERS              0x80000000

/* ---- ICU_ family (6 names; R1) ---- */
#define ICU_ENCODE_SPACES_ONLY                       0x4000000
#define ICU_NO_META                                  0x8000000
#define ICU_DECODE                                   0x10000000
#define ICU_NO_ENCODE                                0x20000000
#define ICU_USERNAME                                 0x40000000
#define ICU_ESCAPE                                   0x80000000

/* ---- INTERNET_ family (112 names; R1) ---- */
#define INTERNET_INVALID_PORT_NUMBER                 0x0000
#define INTERNET_OPEN_TYPE_PRECONFIG                 0x0000
#define INTERNET_RFC1123_FORMAT                      0x0000
#define INTERNET_CONNECTION_MODEM                    0x0001
#define INTERNET_FIRST_OPTION                        0x0001
#define INTERNET_FLAG_TRANSFER_ASCII                 0x0001
#define INTERNET_HANDLE_TYPE_INTERNET                0x0001
#define INTERNET_OPEN_TYPE_DIRECT                    0x0001
#define INTERNET_OPTION_CALLBACK                     0x0001
#define INTERNET_REQFLAG_FROM_CACHE                  0x0001
#define INTERNET_SERVICE_FTP                         0x0001
#define INTERNET_STATE_CONNECTED                     0x0001
#define INTERNET_CONNECTION_LAN                      0x0002
#define INTERNET_FLAG_TRANSFER_BINARY                0x0002
#define INTERNET_HANDLE_TYPE_CONNECT_FTP             0x0002
#define INTERNET_OPTION_CONNECT_TIMEOUT              0x0002
#define INTERNET_SERVICE_GOPHER                      0x0002
#define INTERNET_STATE_DISCONNECTED                  0x0002
#define INTERNET_OPEN_TYPE_PROXY                     0x0003
#define INTERNET_OPTION_CONNECT_RETRIES              0x0003
#define INTERNET_SERVICE_HTTP                        0x0003
#define INTERNET_CONNECTION_PROXY                    0x0004
#define INTERNET_HANDLE_TYPE_CONNECT_HTTP            0x0004
#define INTERNET_OPTION_CONNECT_BACKOFF              0x0004
#define INTERNET_HANDLE_TYPE_FTP_FIND                0x0005
#define INTERNET_OPTION_CONTROL_SEND_TIMEOUT         0x0005
#define INTERNET_OPTION_SEND_TIMEOUT                 0x0005
#define INTERNET_HANDLE_TYPE_FTP_FIND_HTML           0x0006
#define INTERNET_OPTION_CONTROL_RECEIVE_TIMEOUT      0x0006
#define INTERNET_OPTION_RECEIVE_TIMEOUT              0x0006
#define INTERNET_HANDLE_TYPE_FTP_FILE                0x0007
#define INTERNET_OPTION_DATA_SEND_TIMEOUT            0x0007
#define INTERNET_CONNECTION_MODEM_BUSY               0x0008
#define INTERNET_HANDLE_TYPE_FTP_FILE_HTML           0x0008
#define INTERNET_OPTION_DATA_RECEIVE_TIMEOUT         0x0008
#define INTERNET_SCHEME_SOCKS                        0x0008
#define INTERNET_OPTION_HANDLE_TYPE                  0x0009
#define INTERNET_OPTION_CONTEXT_VALUE                0x000A
#define INTERNET_STATUS_RESOLVING_NAME               0x000A
#define INTERNET_STATUS_NAME_RESOLVED                0x000B
#define INTERNET_OPTION_READ_BUFFER_SIZE             0x000C
#define INTERNET_HANDLE_TYPE_HTTP_REQUEST            0x000D
#define INTERNET_OPTION_WRITE_BUFFER_SIZE            0x000D
#define INTERNET_FLAG_MUST_CACHE_REQUEST             0x0010
#define INTERNET_RAS_INSTALLED                       0x0010
#define INTERNET_STATE_DISCONNECTED_BY_USER          0x0010
#define INTERNET_STATUS_CONNECTING_TO_SERVER         0x0014
#define INTERNET_DEFAULT_FTP_PORT                    0x0015
#define INTERNET_OPTION_PARENT_HANDLE                0x0015
#define INTERNET_STATUS_CONNECTED_TO_SERVER          0x0015
#define INTERNET_OPTION_REQUEST_FLAGS                0x0017
#define INTERNET_OPTION_EXTENDED_ERROR               0x0018
#define INTERNET_OPTION_USERNAME                     0x001C
#define INTERNET_OPTION_PASSWORD                     0x001D
#define INTERNET_RFC1123_BUFSIZE                     0x001E
#define INTERNET_STATUS_SENDING_REQUEST              0x001E
#define INTERNET_OPTION_SECURITY_FLAGS               0x001F
#define INTERNET_STATUS_REQUEST_SENT                 0x001F
#define INTERNET_CONNECTION_OFFLINE                  0x0020
#define INTERNET_OPTION_SECURITY_CERTIFICATE_STRUCT  0x0020
#define INTERNET_OPTION_DATAFILE_NAME                0x0021
#define INTERNET_OPTION_URL                          0x0022
#define INTERNET_OPTION_SECURITY_CERTIFICATE         0x0023
#define INTERNET_OPTION_SECURITY_KEY_BITNESS         0x0024
#define INTERNET_OPTION_REFRESH                      0x0025
#define INTERNET_OPTION_PROXY                        0x0026
#define INTERNET_OPTION_SETTINGS_CHANGED             0x0027
#define INTERNET_OPTION_VERSION                      0x0028
#define INTERNET_STATUS_RECEIVING_RESPONSE           0x0028
#define INTERNET_OPTION_USER_AGENT                   0x0029
#define INTERNET_STATUS_RESPONSE_RECEIVED            0x0029
#define INTERNET_OPTION_END_BROWSER_SESSION          0x002A
#define INTERNET_STATUS_CTL_RESPONSE_RECEIVED        0x002A
#define INTERNET_OPTION_PROXY_USERNAME               0x002B
#define INTERNET_STATUS_PREFETCH                     0x002B
#define INTERNET_OPTION_PROXY_PASSWORD               0x002C
#define INTERNET_LAST_OPTION                         0x0032
#define INTERNET_OPTION_CONNECTED_STATE              0x0032
#define INTERNET_STATUS_CLOSING_CONNECTION           0x0032
#define INTERNET_STATUS_CONNECTION_CLOSED            0x0033
#define INTERNET_STATUS_HANDLE_CREATED               0x003C
#define INTERNET_CONNECTION_CONFIGURED               0x0040
#define INTERNET_STATUS_HANDLE_CLOSING               0x0046
#define INTERNET_DEFAULT_HTTP_PORT                   0x0050
#define INTERNET_STATUS_REQUEST_COMPLETE             0x0064
#define INTERNET_STATUS_REDIRECT                     0x006E
#define INTERNET_FLAG_PRAGMA_NOCACHE                 0x0100
#define INTERNET_STATE_IDLE                          0x0100
#define INTERNET_DEFAULT_HTTPS_PORT                  0x01BB
#define INTERNET_FLAG_NO_UI                          0x0200
#define INTERNET_STATE_BUSY                          0x0200
#define INTERNET_FLAG_HYPERLINK                      0x0400
#define INTERNET_DEFAULT_SOCKS_PORT                  0x0438
#define INTERNET_FLAG_RESYNCHRONIZE                  0x0800
#define INTERNET_FLAG_IGNORE_CERT_CN_INVALID         0x1000
#define INTERNET_FLAG_IGNORE_CERT_DATE_INVALID       0x2000
#define INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS       0x4000
#define INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP        0x8000
#define INTERNET_FLAG_NO_AUTH                        0x40000
#define INTERNET_FLAG_NO_COOKIES                     0x80000
#define INTERNET_FLAG_READ_PREFETCH                  0x100000
#define INTERNET_FLAG_NO_AUTO_REDIRECT               0x200000
#define INTERNET_FLAG_KEEP_CONNECTION                0x400000
#define INTERNET_FLAG_SECURE                         0x800000
#define INTERNET_FLAG_OFFLINE                        0x1000000
#define INTERNET_FLAG_DONT_CACHE                     0x4000000
#define INTERNET_FLAG_NO_CACHE_WRITE                 0x4000000
#define INTERNET_FLAG_PASSIVE                        0x8000000
#define INTERNET_FLAG_ASYNC                          0x10000000
#define INTERNET_FLAG_EXISTING_CONNECT               0x20000000
#define INTERNET_FLAG_RAW_DATA                       0x40000000
#define INTERNET_FLAG_RELOAD                         0x80000000

/* ---- IRF_ family (4 names; R1) ---- */
#define IRF_ASYNC                                    0x0001
#define IRF_SYNC                                     0x0004
#define IRF_NO_WAIT                                  0x0008
#define IRF_USE_CONTEXT                              0x0008

/* ---- NORMAL_ family (1 names; R1) ---- */
#define NORMAL_CACHE_ENTRY                           0x0001

/* ---- SECURITY_ family (13 names; R1) ---- */
#define SECURITY_FLAG_SECURE                         0x0001
#define SECURITY_FLAG_IGNORE_REVOCATION              0x0080
#define SECURITY_FLAG_IGNORE_UNKNOWN_CA              0x0100
#define SECURITY_FLAG_IGNORE_WRONG_USAGE             0x0200
#define SECURITY_FLAG_IGNORE_CERT_CN_INVALID         0x1000
#define SECURITY_FLAG_IGNORE_CERT_DATE_INVALID       0x2000
#define SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTPS       0x4000
#define SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTP        0x8000
#define SECURITY_FLAG_40BIT                          0x10000000
#define SECURITY_FLAG_NORMALBITNESS                  0x10000000
#define SECURITY_FLAG_128BIT                         0x20000000
#define SECURITY_FLAG_56BIT                          0x40000000
#define SECURITY_FLAG_UNKNOWNBIT                     0x80000000

/* ---- SPARSE_ family (1 names; R1) ---- */
#define SPARSE_CACHE_ENTRY                           0x10000

/* ---- STICKY_ family (1 names; R1) ---- */
#define STICKY_CACHE_ENTRY                           0x0004

/* ---- URLHISTORY_ family (1 names; R1) ---- */
#define URLHISTORY_CACHE_ENTRY                       0x200000

/* ---- WININET_ family (3 names; R1) ---- */
#define WININET_API_FLAG_ASYNC                       0x0001
#define WININET_API_FLAG_SYNC                        0x0004
#define WININET_API_FLAG_USE_CONTEXT                 0x0008

/* ------------------------------------------------------------------
 * Book surface: internetclient-book (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa452096 API Flags (Header: Wininet.h.) */
/* ms906348 HTTP Response Headers (Header: Wininet.h.) */
/* ms906351 HTTP Status Codes (Header: Wininet.h.) */
/* ms918831 Option Flags (Header: Wininet.h.) */
/* ms918835 Privacy Flags (Header: Wininet.h.) */
/* ms918842 Query Info Flags (Header: Wininet.h.) */
/* ------------------------------------------------------------------
 * Book surface: internetclient-book (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa451874 About Character Sets */
/* aa451877 About DHTML */
/* aa451879 About HINTERNET Handles */
/* aa451881 About the ActiveX Navigation Control */
/* aa451883 About the IMultilanguage Interfaces */
/* aa451885 About the Webview Browser Object */
/* aa451887 Accessing Elements with Script Languages */
/* aa451890 Accessing the HTTP Protocol */
/* aa451892 Accessing URLs Directly */
/* aa451896 Adding Internet Browsing Functionality to Your Application */
/* aa451898 Adding JScript Code to an HTML Page */
/* aa452072 Adding Transitions */
/* aa451900 Adding VBScript Code to an HTML Page */
/* aa451902 Additional Resources for JScript Developers */
/* aa451904 Additional Resources for VBScript Developers */
/* aa452097 apply (Internet Explorer) */
/* ms905675 Applying Filters */
/* aa451910 Browser Registry Settings */
/* aa451914 Changing Fonts with the WebBrowser Control */
/* aa451918 Code Page Detection */
/* aa451922 Conversion Between Character Sets */
/* aa451924 Cookie Headers */
/* aa451926 Cookies */
/* aa451938 Creating a Browser Class */
/* aa451940 Creating a Browser Window */
/* aa451928 Creating a Cache Entry */
/* aa452148 Creating a URL Moniker */
/* aa451946 Creating a Web Browser Object */
/* aa451932 Creating and Cracking URLs */
/* aa451935 Creating and Retrieving Cookies */
/* aa451942 Creating the Browser Control */
/* aa451944 Creating the Navigation Control */
/* ms905302 Customizing the Browser Font Table */
/* aa451948 Customizing the Browser User Interface */
/* aa451950 Customizing the Focus Rectangle */
/* aa451952 Deleting a Cache Entry */
/* aa451954 Deleting Files from an FTP Server */
/* aa451956 DHTML Events */
/* aa451958 Disabling Multiple Windows */
/* aa451960 Displaying the Current Security Zone */
/* aa451963 Enumerating Code Pages and Locales */
/* aa451965 Enumerating Directories */
/* aa451967 Enumerating the Cache */
/* ms905676 Filter and Transition Properties */
/* aa451969 Font Linking */
/* aa451971 FTP Function Handles */
/* aa451977 Handling HTTP Authentication */
/* aa451979 Handling Structures with Variable Size Data */
/* aa451981 Handling Uniform Resource Locators */
/* aa451983 Hit Logging */
/* aa451985 Hosting MSHTML from an Application */
/* aa451988 HTTP and FTP Common Functions */
/* aa451989 HTTP Authentication */
/* aa451991 Identifying Pocket Internet Explorer to a Web Server */
/* aa451993 IESample Registry Settings */
/* aa451996 International Language Functionalities */
/* aa451997 Internet Client Services Catalog Items */
/* ms918893 Internet Explorer 6 Application Development */
/* aa452001 Internet Explorer 6 Architecture */
/* aa452005 Internet Explorer 6 Default Registry Settings */
/* aa452002 Internet Explorer 6 for Windows CE Characteristics */
/* aa452003 Internet Explorer 6 Migration */
/* aa452004 Internet Explorer 6 OS Overview */
/* aa452007 Internet Explorer 6 Security */
/* aa452010 Internet Explorer Browser Control Host Migration */
/* aa452011 Internet Explorer Browser Control Host OS Design Development */
/* ms919019 Internet Explorer Browser Control Host Reference */
/* aa451908 Internet Explorer Browser Control Host Registry Settings */
/* aa452012 Internet Explorer Browser Control Host Samples */
/* aa452013 Internet Explorer MSHTML/DHTML API Migration */
/* ms905101 Internet Explorer MSHTML/DHTML API Registry Settings */
/* aa452015 Internet Explorer MSHTML/DHTML API Samples */
/* aa452017 Internet Explorer Multiple-Language API Migration */
/* aa452016 Internet Explorer Multiple-Language API OS Design Development */
/* ms905072 Internet Explorer Multiple-Language API Registry Settings */
/* aa452018 Internet Explorer Multiple-Language API Samples */
/* aa452019 Internet Explorer RPC Support */
/* aa452021 Internet Explorer TV-Style Navigation Migration */
/* aa452022 Internet Explorer TV-Style Navigation OS Design Development */
/* ms905631 Internet Explorer TV-Style Navigation Registry Settings */
/* aa452023 Internet Explorer TV-Style Navigation Samples */
/* aa452024 Internet Protocols */
/* aa452029 JScript Migration */
/* aa452030 JScript OS Design Development */
/* aa452031 JScript Samples */
/* aa452028 JScript Support in Windows CE */
/* aa452032 Locale-based Text and Line Breaking */
/* ms904973 Manipulating Directories on an FTP Server */
/* ms905065 Mapping Code Pages to Script IDs */
/* ms905088 MSHTML Editing */
/* ms905080 MSHTML/DHTML API Overview */
/* ms905109 Navigating Directories */
/* ms905118 Navigating to a Specified URL */
/* ms905210 Obtaining MIME Information */
/* ms905213 P3P Policy Evaluation Engine */
/* ms905225 Placing Files on an FTP Server */
/* ms918834 play (Internet Explorer) */
/* ms905234 Pocket Internet Explorer Architecture */
/* ms905240 Pocket Internet Explorer Characteristics */
/* ms905244 Pocket Internet Explorer Migration */
/* ms905255 Pocket Internet Explorer Samples */
/* ms905260 Pocket Internet Explorer Security */
/* ms905265 Printing Pages with the WebBrowser Control */
/* ms905270 Privacy Functions */
/* ms905275 Privacy Notification User Interface */
/* ms905281 Privacy Templates */
/* ms905293 Proxy Authentication */
/* ms905299 Registering the Browser Window */
/* ms905307 Renaming Files and Directories on an FTP Server */
/* ms905316 Replacement of the Urlmon User Interface */
/* ms905320 Replacement of the WinInet User Interface */
/* ms905329 Retrieving Cache Entry Data */
/* ms905334 Retrieving Cache Entry Files */
/* ms905338 Retrieving Files from an FTP Server */
/* ms905345 Server Authentication */
/* ms905348 Setting Up Event Sinks */
/* aa451920 Specifying Privacy Settings */
/* ms905622 Starting an FTP Session */
/* ms918859 stop (Internet Explorer) */
/* ms905630 Summary of Browser Characteristics */
/* aa452009 Support for Internet Explorer 6 in Windows CE */
/* ms905632 The IESample Browser */
/* aa451930 The IESimple Browser */
/* ms905633 Theme Hit Test Values */
/* ms905690 Theme Parts and States */
/* ms905286 Theme Property Values */
/* aa452068 Transition Events */
/* ms905637 URL Moniker Services Migration */
/* ms905638 URL Moniker Services Overview */
/* ms905635 URL Moniker Services Registry Settings */
/* ms905639 URL Moniker Services Samples */
/* ms905636 URL Moniker Services Security */
/* ms905640 URL Security Zones */
/* ms905641 URLs, Namespaces, and Monikers */
/* ms905642 Using Asynchronous Pluggable Protocols */
/* ms905643 Using Asynchronous WinInet Functions */
/* ms905644 Using Client Capabilities */
/* ms905645 Using Flags to Control Caching */
/* ms905646 Using HTML Components */
/* ms905647 Using Persistent Caching Functions */
/* ms905649 Using the Travel Log Interfaces */
/* ms905650 Using the URL Moniker Functions */
/* ms905653 Using the WinInet Debug Engine */
/* ms905651 Using the WinInet Functions for FTP Sessions */
/* ms905652 Using WebBrowser Controls */
/* ms905655 VBScript Migration */
/* ms905656 VBScript OS Design Development */
/* ms905657 VBScript Samples */
/* ms905654 VBScript Support in Windows CE */
/* aa452091 WinInet Error Messages */
/* ms905659 WinInet Migration */
/* ms905658 WinInet Overview */
/* ms905660 WinInet Registry Settings */
/* ms905662 WinInet Samples */
/* ms905663 WinInet Security */
/* ms905664 Working with WebBrowser Events */
/* ms905667 XML Data Islands Application Development */
/* ms905668 XML Data Islands Migration */
/* ms918879 XML Data Islands OS Design Development */
/* ms905669 XML Data Islands Samples */
#endif /* AKARI_WININET_H */
