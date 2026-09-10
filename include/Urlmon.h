/*
 * Urlmon.h -- URL Moniker Services for Windows CE (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE .NET 4.0+
 * documentation (learn.microsoft.com previous-versions archive; page ids
 * cited per declaration).  Sources are the four books of the URL Moniker
 * Services documentation tree (191 pages, tools/manifests/urlmon*.manifest):
 *
 *   URL Moniker Services Reference            88 pages  (aa452074..aa452146,
 *     ms9188xx, ms9062xx/ms9063xx)
 *   Asynchronous Pluggable Protocols          48 pages  (ms905670..aa452344)
 *   URL Security Zones                        50 pages  (ms9188xx, aa4520xx)
 *   Hit Logging                                5 pages  (ms905677..ms918878)
 *
 * Every Requirements row prints "Header: Urlmon.h, Urlmon.idl." and, for
 * function/interface pages, "Link Library: Urlmon.lib."; the OS row is
 * "Windows CE .NET 4.0 and later".  The four books share one header and
 * one import library, so they are covered by this single unit and one
 * def file (def/urlmon-doc.def).
 *
 * Layout policy: the enumeration pages print complete C enums -- the
 * value-bearing families verbatim (explicit values), the others with
 * the printed starter value and C implicit-successor semantics; print
 * artifacts (missing spaces, a duplicated enumerator, a doubled
 * CFSTR_MIME_X_MSVIDEO row) are normalized and recorded in
 * docs/inventory.md (M60).  Interfaces are opaque exactly as their
 * pages and the function signatures use them; every documented method
 * signature is recorded in the interface record comments (the M58
 * pattern).  BINDINFO is already provided by objbase.h (ms928761);
 * the URL Moniker Services BINDINFO page (aa452099) prints the same
 * member list, and this unit records that corroboration.
 *
 * HELD (names documented, values not published anywhere official):
 * INET_E_* error codes (ms918870, 26 names), URLACTION_* (ms918863,
 * 30+ names), URLPOLICY_* (ms918874, 24 names),
 * CLSID_InternetSecurityManager / CLSID_InternetZoneManager (aa452025 /
 * aa452026 -- creation only, no GUID values), ZONEATTRIBUTES (ms918891
 * -- the szDescription array length MAX_ZONE_DESCRIPTION is not
 * published in the CE docs, the desktop docs set, or the Learn search
 * index), IInternetZoneManager::LogAction / PromptAction and
 * IBinding::SetPriority / Suspend (interface-table rows without method
 * pages; signatures unpublished).
 */

#ifndef AKARI_URLMON_H
#define AKARI_URLMON_H

#include "Windef.h"    /* DWORD, BOOL, ULONG, UINT, VOID, LPVOID, LPSTR, LPCSTR, HWND */
#include "Winnt.h"     /* LARGE_INTEGER, ULARGE_INTEGER, GUID/IID/CLSID bases */
#include "Winbase.h"   /* SYSTEMTIME (HIT_LOGGING_INFO) */
#include "Objbase.h"   /* HRESULT, IUnknown, IMoniker, IBindCtx/LPBC, IStream,
                          IEnumFORMATETC, FORMATETC, STGMEDIUM, BINDINFO,
                          LPOLESTR, LPMONIKER, LPSTREAM, LPUNKNOWN, REFIID,
                          REFCLSID, REFGUID, CLSID, IID, BSTR */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * CLIPFORMAT -- the clipboard-format code type used by
 * RegisterMediaTypes (ms918847) and FindMediaType (aa452199).
 * Derivation (absolutely public information only): the CE FORMATETC
 * page (ms886985) prints cfFormat as "unsigned long"; the desktop
 * FORMATETC documentation (objidl.h, learn.microsoft.com) prints the
 * same member as "CLIPFORMAT cfFormat"; the RegisterMediaTypes page
 * describes rgcfTypes as "an array of the 32-bit values assigned to
 * corresponding media types".  CLIPFORMAT is therefore the 32-bit
 * clipboard-format code: unsigned long.
 */
typedef unsigned long CLIPFORMAT;

/*
 * Registered media-type / clipboard-format name constants printed by
 * the RegisterMediaTypes page (ms918847) with their string values.
 * The page prints CFSTR_MIME_X_MSVIDEO twice (once for
 * "video/x-msvideo" and once for "video/x-sgi-movie"); the second
 * row is a print artifact and is recorded in the inventory.
 */
#define CF_NULL                     0
#define SZ_URLCONTEXT              L"URL Context"
#define CFSTR_MIME_FRACTALS        TEXT("application/fractals")
#define CFSTR_MIME_POSTSCRIPT      TEXT("application/postscript")
#define CFSTR_MIME_RAWDATA         TEXT("application/octet")
#define CFSTR_MIME_AIIF            TEXT("audio/aiif")
#define CFSTR_MIME_BASICAUDIO      TEXT("audio/basic")
#define CFSTR_MIME_WAV             TEXT("audio/wav")
#define CFSTR_MIME_X_AIIF          TEXT("audio/x-aiif")
#define CFSTR_MIME_X_REALAUDIO     TEXT("audio/x-pn-realaudio")
#define CFSTR_MIME_X_WAV           TEXT("audio/x-wav")
#define CFSTR_MIME_BMP             TEXT("image/bmp")
#define CFSTR_MIME_GIF             TEXT("image/gif")
#define CFSTR_MIME_JPEG            TEXT("image/jpeg")
#define CFSTR_MIME_TIFF            TEXT("image/tiff")
#define CFSTR_MIME_XBM             TEXT("image/xbm")
#define CFSTR_MIME_X_BITMAP        TEXT("image/x-bitmap")
#define CFSTR_MIME_HTML            TEXT("text/html")
#define CFSTR_MIME_TEXT            TEXT("text/plain")
#define CFSTR_MIME_AVI             TEXT("video/avi")
#define CFSTR_MIME_MPEG            TEXT("video/mpeg")
#define CFSTR_MIME_X_MSVIDEO       TEXT("video/x-msvideo")

/* ------------------------------------------------------------------ */
/*  Interfaces (opaque; no page prints a vtable layout)                */
/* ------------------------------------------------------------------ */

/* aa452292 "IInternet": "allows client programs to determine if
 * asynchronous pluggable protocols are supported"; no methods listed. */
typedef struct IInternet IInternet;

/* ms906353 "IAsyncMoniker": IUnknown-only ("provides an implementation
 * of the IUnknown interface ... No additional methods are supported"). */
typedef struct IAsyncMoniker IAsyncMoniker;

/* ms906354 "IAuthenticate" (1 method). */
typedef struct IAuthenticate IAuthenticate;

/* ms906356 "IBindHost" (3 methods). */
typedef struct IBindHost IBindHost;

/* ms906360 "IBinding" (table lists Abort, GetBindResult, GetPriority,
 * Resume, SetPriority, Suspend; method pages exist for the first four
 * -- SetPriority and Suspend have no pages, signatures unpublished). */
typedef struct IBinding IBinding;

/* ms906365 "IBindStatusCallback" (8 methods incl. OnLowResource, which
 * the interface page marks "Not currently implemented" with no page). */
typedef struct IBindStatusCallback IBindStatusCallback;

/* aa452285 "IHttpNegotiate" (2 methods). */
typedef struct IHttpNegotiate IHttpNegotiate;

/* aa452290 "IHttpSecurity" (1 method). */
typedef struct IHttpSecurity IHttpSecurity;

/* ms918293 "IMonikerProp" (1 method). */
typedef struct IMonikerProp IMonikerProp;

/* ms918766 "IPersistMoniker" (6 methods). */
typedef struct IPersistMoniker IPersistMoniker;

/* ms918811 "IWindowForBindingUI" (1 method). */
typedef struct IWindowForBindingUI IWindowForBindingUI;

/* ms918813 "IWinInetHttpInfo" (1 method). */
typedef struct IWinInetHttpInfo IWinInetHttpInfo;

/* ms918815 "IWinInetInfo" (1 method). */
typedef struct IWinInetInfo IWinInetInfo;

/* aa452340 "IInternetSession" (4 methods). */
typedef struct IInternetSession IInternetSession;

/* aa452303 "IInternetProtocol" (4 methods). */
typedef struct IInternetProtocol IInternetProtocol;

/* aa452304 "IInternetProtocolInfo" (4 methods). */
typedef struct IInternetProtocolInfo IInternetProtocolInfo;

/* aa452311 "IInternetProtocolRoot" (Abort, Continue, Start, Terminate;
 * Resume and Suspend are marked "Not implemented" with no pages). */
typedef struct IInternetProtocolRoot IInternetProtocolRoot;

/* aa452317 "IInternetProtocolSink" (4 methods). */
typedef struct IInternetProtocolSink IInternetProtocolSink;

/* aa452321 "IInternetProtocolSinkStackable" (3 methods). */
typedef struct IInternetProtocolSinkStackable IInternetProtocolSinkStackable;

/* aa452293 "IInternetBindInfo" (2 methods). */
typedef struct IInternetBindInfo IInternetBindInfo;

/* aa452300 "IInternetPriority" (2 methods). */
typedef struct IInternetPriority IInternetPriority;

/* aa452296 "IInternetHostSecurityManager" (3 methods). */
typedef struct IInternetHostSecurityManager IInternetHostSecurityManager;

/* aa452327 "IInternetSecurityManager" (8 methods). */
typedef struct IInternetSecurityManager IInternetSecurityManager;

/* aa452337 "IInternetSecurityMgrSite" (2 methods). */
typedef struct IInternetSecurityMgrSite IInternetSecurityMgrSite;

/* aa452345 "IInternetZoneManager" (11 table rows; LogAction and
 * PromptAction are "Not currently implemented" with no pages). */
typedef struct IInternetZoneManager IInternetZoneManager;

/* Pointer-typedef spellings printed by the function signatures
 * themselves: URLDownloadToFile / URLOpenPullStream / URLOpenStream /
 * URLOpenBlockingStream print "LPBINDSTATUSCALLBACK lpfnCB" (ms918866 /
 * ms918872 / ms918873 / ms918871), CoGetClassObjectFromURL prints
 * "LPBINDCTX pBindCtx" (aa452108).  Composition of the printed names
 * with the published interface typedefs above (derivation recorded). */
typedef IBindStatusCallback *LPBINDSTATUSCALLBACK;
typedef IBindCtx *LPBINDCTX;

/* ------------------------------------------------------------------ */
/*  Enumerations (printed C enums; values as published)                */
/* ------------------------------------------------------------------ */

/* aa452098 "BINDF" (24 values printed). */
typedef enum {
    BINDF_ASYNCHRONOUS = 0x00000001,
    BINDF_ASYNCSTORAGE = 0x00000002,
    BINDF_NOPROGRESSIVERENDERING = 0x00000004,
    BINDF_OFFLINEOPERATION = 0x00000008,
    BINDF_GETNEWESTVERSION = 0x00000010,
    BINDF_NOWRITECACHE = 0x00000020,
    BINDF_NEEDFILE = 0x00000040,
    BINDF_PULLDATA = 0x00000080,
    BINDF_IGNORESECURITYPROBLEM = 0x00000100,
    BINDF_RESYNCHRONIZE = 0x00000200,
    BINDF_HYPERLINK = 0x00000400,
    BINDF_NO_UI = 0x00000800,
    BINDF_SILENTOPERATION = 0x00001000,
    BINDF_PRAGMA_NO_CACHE = 0x00002000,
    BINDF_GETCLASSOBJECT = 0x00004000,
    BINDF_RESERVED_1 = 0x00008000,
    BINDF_FREE_THREADED = 0x00010000,
    BINDF_DIRECT_READ = 0x00020000,
    BINDF_FORMS_SUBMIT = 0x00040000,
    BINDF_GETFROMCACHE_IF_NET_FAIL = 0x00080000,
    BINDF_FROMURLMON = 0x00100000,
    BINDF_FWD_BACK = 0x00200000,
    BINDF_PREFERDEFAULTHANDLER = 0x00400000,
    BINDF_RESERVED_3 = 0x00800000
} BINDF;

/* ms918833 "PI_FLAGS" (14 values printed; the last row prints the name
 * PD_FORCE_SWITCH, kept exactly as published). */
typedef enum _tagPI_FLAGS {
    PI_PARSE_URL = 0x00000001,
    PI_FILTER_MODE = 0x00000002,
    PI_FORCE_ASYNC = 0x00000004,
    PI_USE_WORKERTHREAD = 0x00000008,
    PI_MIMEVERIFICATION = 0x00000010,
    PI_CLSIDLOOKUP = 0x00000020,
    PI_DATAPROGRESS = 0x00000040,
    PI_SYNCHRONOUS = 0x00000080,
    PI_APARTMENTTHREADED = 0x00000100,
    PI_CLASSINSTALL = 0x00000200,
    PI_PASSONBINDCTX = 0x00002000,
    PI_NOMIMEHANDLER = 0x00008000,
    PI_LOADAPPDIRECT = 0x00004000,
    PD_FORCE_SWITCH = 0x00010000
} PI_FLAGS;

/* aa452101 "BINDINFO_OPTIONS" (5 values printed). */
typedef enum {
    BINDINFO_OPTIONS_WININETFLAG = 0x00010000,
    BINDINFO_OPTIONS_ENABLE_UTF8 = 0x00020000,
    BINDINFO_OPTIONS_DISABLE_UTF8 = 0x00040000,
    BINDINFO_OPTIONS_USE_IE_ENCODING = 0x00080000,
    BINDINFO_OPTIONS_BINDTOOBJECT = 0x00100000
} BINDINFO_OPTIONS;

/* ms918826 "MONIKERPROPERTY" (1 value printed). */
typedef enum {
    MIMETYPEPROP = 0x00000000
} MONIKERPROPERTY;

/* ms918867 "URL_ENCODING" (3 values printed). */
typedef enum {
    URL_ENCODING_NONE = 0x00000000,
    URL_ENCODING_ENABLE_UTF8 = 0x10000000,
    URL_ENCODING_DISABLE_UTF8 = 0x20000000
} URL_ENCODING;

/* ms918841 "PUAF" (9 values printed). */
typedef enum {
    PUAF_DEFAULT = 0x0000000,
    PUAF_NOUI = 0x00000001,
    PUAF_ISFILE = 0x00000002,
    PUAF_WARN_IF_DENIED = 0x00000004,
    PUAF_FORCEUI_FOREGROUND = 0x00000008,
    PUAF_CHECK_TIFS = 0x00000010,
    PUAF_DONTCHECKBOXINDIALOG = 0x00000020,
    PUAF_TRUSTED = 0x00000040,
    PUAF_ACCEPT_WILDCARD_SCHEME = 0x00000080
} PUAF;

/* ms918860 "SZM_FLAGS" (2 values printed). */
typedef enum {
    SZM_CREATE = 0x00000000,
    SZM_DELETE = 0x00000001
} SZM_FLAGS;

/* ms918875 "URLTEMPLATE" (7 values printed; URLTEMPLATE_LOW shares
 * URLTEMPLATE_PREDEFINED_MIN's value 0x10000 as printed). */
typedef enum tagURLTEMPLATE {
    URLTEMPLATE_CUSTOM = 0x00000,
    URLTEMPLATE_PREDEFINED_MIN = 0x10000,
    URLTEMPLATE_LOW = 0x10000,
    URLTEMPLATE_MEDLOW = 0x10500,
    URLTEMPLATE_MEDIUM = 0x11000,
    URLTEMPLATE_HIGH = 0x12000,
    URLTEMPLATE_PREDEFINED_MAX = 0x20000
} URLTEMPLATE;

/* ms918890 "ZAFLAGS" (8 values printed). */
typedef enum {
    ZAFLAGS_CUSTOM_EDIT = 0x00000001,
    ZAFLAGS_ADD_SITES = 0x00000002,
    ZAFLAGS_REQUIRE_VERIFICATION = 0x00000004,
    ZAFLAGS_INCLUDE_PROXY_OVERRIDE = 0x00000008,
    ZAFLAGS_INCLUDE_INTRANET_SITES = 0x00000010,
    ZAFLAGS_NO_UI = 0x00000020,
    ZAFLAGS_SUPPORTS_VERIFICATION = 0x00000040,
    ZAFLAGS_UNC_AS_INTRANET = 0x00000080
} ZAFLAGS;

/* ms918840 "PSUACTION" (PSU_DEFAULT = 1 printed; successor per the
 * printed C enum). */
typedef enum _tagPSUACTION {
    PSU_DEFAULT = 1,
    PSU_SECURITY_URL_ONLY
} PSUACTION;

/* aa452103 "BINDSTRING" (BINDSTRING_HEADERS = 1 printed; successors
 * per the printed C enum). */
typedef enum tagBINDSTRING {
    BINDSTRING_HEADERS = 1,
    BINDSTRING_ACCEPT_MIMES,
    BINDSTRING_EXTRA_URL,
    BINDSTRING_LANGUAGE,
    BINDSTRING_USERNAME,
    BINDSTRING_PASSWORD,
    BINDSTRING_UA_PIXELS,
    BINDSTRING_UA_COLOR,
    BINDSTRING_OS,
    BINDSTRING_USERAGENT,
    BINDSTRING_ACCEPT_ENCODINGS,
    BINDSTRING_POST_COOKIE,
    BINDSTRING_POST_DATA_MIME,
    BINDSTRING_URL,
    BINDSTRING_IID,
    BINDSTRING_FLAG_BIND_TO_OBJECT,
    BINDSTRING_PTR_BIND_CONTEXT
} BINDSTRING;

/* ms918832 "PARSEACTION" (PARSE_CANONICALIZE = 1 printed; successors
 * per the printed C enum). */
typedef enum _tagPARSEACTION {
    PARSE_CANONICALIZE = 1,
    PARSE_FRIENDLY,
    PARSE_SECURITY_URL,
    PARSE_ROOTDOCUMENT,
    PARSE_DOCUMENT,
    PARSE_ANCHOR,
    PARSE_ENCODE,
    PARSE_DECODE,
    PARSE_PATH_FROM_URL,
    PARSE_URL_FROM_PATH,
    PARSE_MIME,
    PARSE_SERVER,
    PARSE_SCHEMA,
    PARSE_SITE,
    PARSE_DOMAIN,
    PARSE_LOCATION,
    PARSE_SECURITY_DOMAIN,
    PARSE_ESCAPE,
    PARSE_UNESCAPE
} PARSEACTION;

/* ms918843 "QUERYOPTION" (QUERY_EXPIRATION_DATE = 1 printed;
 * successors per the printed C enum). */
typedef enum _tagQUERYOPTION {
    QUERY_EXPIRATION_DATE = 1,
    QUERY_TIME_OF_LAST_CHANGE,
    QUERY_CONTENT_ENCODING,
    QUERY_CONTENT_TYPE,
    QUERY_REFRESH,
    QUERY_RECOMBINE,
    QUERY_CAN_NAVIGATE,
    QUERY_USES_NETWORK,
    QUERY_IS_CACHED,
    QUERY_IS_INSTALLEDENTRY,
    QUERY_IS_CACHED_OR_MAPPED,
    QUERY_USES_CACHE,
    QUERY_IS_SECURE,
    QUERY_IS_SAFE
} QUERYOPTION;

/* ms918876 "URLZONE" (values printed as shown). */
typedef enum tagURLZONE {
    URLZONE_PREDEFINED_MIN = 0,
    URLZONE_LOCAL_MACHINE = 0,
    URLZONE_INTRANET,
    URLZONE_TRUSTED,
    URLZONE_INTERNET,
    URLZONE_UNTRUSTED,
    URLZONE_PREDEFINED_MAX = 999,
    URLZONE_USER_MIN = 1000,
    URLZONE_USER_MAX = 10000
} URLZONE;

/* ms918877 "URLZONEREG" (URLZONEREG_DEFAULT = 0 printed). */
typedef enum _URLZONEREG {
    URLZONEREG_DEFAULT = 0,
    URLZONEREG_HKLM,
    URLZONEREG_HKCU
} URLZONEREG;

/* aa452100 "BINDINFOF" (no values printed; first value 0 and successor
 * per the printed C enum). */
typedef enum tagBINDINFOF {
    BINDINFOF_URLENCODESTGMEDDATA,
    BINDINFOF_URLENCODEDEXTRAINFO
} BINDINFOF;

/* aa452104 "BINDVERB" (no values printed; implicit 0..3). */
typedef enum {
    BINDVERB_GET,
    BINDVERB_POST,
    BINDVERB_PUT,
    BINDVERB_CUSTOM
} BINDVERB;

/* aa452105 "BSCF" (no values printed; implicit 0..4). */
typedef enum {
    BSCF_FIRSTDATANOTIFICATION,
    BSCF_INTERMEDIATEDATANOTIFICATION,
    BSCF_LASTDATANOTIFICATION,
    BSCF_DATAFULLYAVAILABLE,
    BSCF_AVAILABLEDATASIZEUNKNOWN
} BSCF;

/*
 * aa452102 "BINDSTATUS" (no values printed; implicit 0..49 below).
 * Print artifacts recorded: the page prints the enumerator
 * BINDSTATUS_COOKIE_STATE_PROMPT twice (once after COOKIE_STATE_REJECT
 * and once after COOKIE_STATE_LEASH); a C enum cannot repeat an
 * enumerator name, so the second occurrence is dropped here, and
 * enumerators after it number one less than a "count the duplicate"
 * reading.  The page also prints "VERFIEDMIMETYPEAVAILABLE" (spelling
 * kept) and drops the comma between BINDSTATUS_ACCEPTRANGES and
 * BINDSTATUS_COOKIE_SENT (spacing artifact).
 */
typedef enum tagBINDSTATUS {
    BINDSTATUS_FINDINGRESOURCE,
    BINDSTATUS_CONNECTING,
    BINDSTATUS_REDIRECTING,
    BINDSTATUS_BEGINDOWNLOADDATA,
    BINDSTATUS_DOWNLOADINGDATA,
    BINDSTATUS_ENDDOWNLOADDATA,
    BINDSTATUS_BEGINDOWNLOADCOMPONENTS,
    BINDSTATUS_INSTALLINGCOMPONENTS,
    BINDSTATUS_ENDDOWNLOADCOMPONENTS,
    BINDSTATUS_USINGCACHEDCOPY,
    BINDSTATUS_SENDINGREQUEST,
    BINDSTATUS_CLASSIDAVAILABLE,
    BINDSTATUS_MIMETYPEAVAILABLE,
    BINDSTATUS_CACHEFILENAMEAVAILABLE,
    BINDSTATUS_BEGINSYNCOPERATION,
    BINDSTATUS_ENDSYNCOPERATION,
    BINDSTATUS_BEGINUPLOADDATA,
    BINDSTATUS_UPLOADINGDATA,
    BINDSTATUS_ENDUPLOADDATA,
    BINDSTATUS_PROTOCOLCLASSID,
    BINDSTATUS_ENCODING,
    BINDSTATUS_VERFIEDMIMETYPEAVAILABLE,
    BINDSTATUS_CLASSINSTALLLOCATION,
    BINDSTATUS_DECODING,
    BINDSTATUS_LOADINGMIMEHANDLER,
    BINDSTATUS_CONTENTDISPOSITIONATTACH,
    BINDSTATUS_FILTERREPORTMIMETYPE,
    BINDSTATUS_CLSIDCANINSTANTIATE,
    BINDSTATUS_IUNKNOWNAVAILABLE,
    BINDSTATUS_DIRECTBIND,
    BINDSTATUS_RAWMIMETYPE,
    BINDSTATUS_PROXYDETECTING,
    BINDSTATUS_ACCEPTRANGES,
    BINDSTATUS_COOKIE_SENT,
    BINDSTATUS_COMPACT_POLICY_RECEIVED,
    BINDSTATUS_COOKIE_SUPPRESSED,
    BINDSTATUS_COOKIE_STATE_UNKNOWN,
    BINDSTATUS_COOKIE_STATE_ACCEPT,
    BINDSTATUS_COOKIE_STATE_REJECT,
    BINDSTATUS_COOKIE_STATE_PROMPT,
    BINDSTATUS_COOKIE_STATE_LEASH,
    BINDSTATUS_COOKIE_STATE_DOWNGRADE,
    BINDSTATUS_POLICY_HREF,
    BINDSTATUS_P3P_HEADER,
    BINDSTATUS_PERSISTENT_COOKIE_RECEIVED,
    BINDSTATUS_SESSION_COOKIE_RECEIVED,
    BINDSTATUS_SESSION_COOKIES_ALLOWED,
    BINDSTATUS_CACHECONTROL,
    BINDSTATUS_SIZEAVAILABLE
} BINDSTATUS;

/* ------------------------------------------------------------------ */
/*  Structures (verbatim CE prints)                                    */
/* ------------------------------------------------------------------ */

/* ms918838 "PROTOCOLDATA" (Asynchronous Pluggable Protocols). */
typedef struct _tagPROTOCOLDATA {
    DWORD   grfFlags;
    DWORD   dwState;
    LPVOID  pData;
    ULONG   cbData;
} PROTOCOLDATA;

/* ms918839 "PROTOCOLFILTERDATA" (Asynchronous Pluggable Protocols). */
typedef struct _tagPROTOCOLFILTERDATA {
    DWORD                  cbSize;
    IInternetProtocolSink *pProtocolSink;
    IInternetProtocol     *pProtocol;
    IUnknown              *pUnk;
    DWORD                  dwFilterFlags;
} PROTOCOLFILTERDATA;

/* ms906339 "HIT_LOGGING_INFO" (Hit Logging). */
typedef struct _HIT_LOGGING_INFO {
    DWORD      dwStructSize;
    LPSTR      lpszLoggedUrlName;
    SYSTEMTIME StartTime;
    SYSTEMTIME EndTime;
    LPSTR      lpszExtendedInfo;
} HIT_LOGGING_INFO, *LPHIT_LOGGING_INFO;

/*
 * BINDINFO is defined in objbase.h (ms928761, the Objidl.h BINDINFO
 * page of the COM documentation).  The URL Moniker Services BINDINFO
 * page (aa452099) prints the identical member list (cbSize ..
 * dwReserved with the embedded SECURITY_ATTRIBUTES, IID and IUnknown*
 * members), corroborating that definition; both books name the same
 * Urlmon-family usage of the structure.  ZONEATTRIBUTES (ms918891) is
 * HELD: the szDescription array length MAX_ZONE_DESCRIPTION is not
 * published on any official page.
 */

/* ------------------------------------------------------------------ */
/*  URL Moniker Services functions (Urlmon.lib)                        */
/* ------------------------------------------------------------------ */

/* aa452108 "CoGetClassObjectFromURL" (page prints LPBINDCTX). */
AKARI_CE_IMPORT HRESULT WINAPI CoGetClassObjectFromURL(REFCLSID rclsid,
    LPCWSTR szCodeURL, DWORD dwFileVersionMS, DWORD dwFileVersionLS,
    LPCWSTR szContentType, LPBINDCTX pBindCtx, DWORD dwClsContext,
    LPVOID pvReserved, REFIID riid, VOID** ppv)
    AKARI_CE_NAME(CoGetClassObjectFromURL);

/* aa452109 "CoInternetCombineUrl" */
AKARI_CE_IMPORT HRESULT WINAPI CoInternetCombineUrl(LPCWSTR pwzBaseUrl,
    LPCWSTR pwzRelativeUrl, DWORD dwCombineFlags, LPWSTR pwzResult,
    DWORD cchResult, DWORD* pcchResult, DWORD dwReserved)
    AKARI_CE_NAME(CoInternetCombineUrl);

/* aa452110 "CoInternetGetProtocolFlags" (page prints STDAPI). */
AKARI_CE_IMPORT HRESULT WINAPI CoInternetGetProtocolFlags(LPCWSTR pwzUrl,
    DWORD* pdwFlags, DWORD dwReserved)
    AKARI_CE_NAME(CoInternetGetProtocolFlags);

/* aa452113 "CoInternetGetSecurityUrl" (the page's signature block
 * prints the name "CoInternetGetSecurityURL"; the page title spelling
 * is implemented). */
AKARI_CE_IMPORT HRESULT WINAPI CoInternetGetSecurityUrl(LPCWSTR pwzUrl,
    LPWSTR* ppwzSecUrl, PSUACTION psuAction, DWORD dwReserved)
    AKARI_CE_NAME(CoInternetGetSecurityUrl);

/* aa452114 "CoInternetGetSession" (page prints STDAPI). */
AKARI_CE_IMPORT HRESULT WINAPI CoInternetGetSession(DWORD dwSessionMode,
    IInternetSession** ppIInternetSession, DWORD dwReserved)
    AKARI_CE_NAME(CoInternetGetSession);

/* aa452117 "CoInternetParseUrl" (page prints STDAPI). */
AKARI_CE_IMPORT HRESULT WINAPI CoInternetParseUrl(LPCWSTR pwzUrl,
    PARSEACTION ParseAction, DWORD dwFlags, LPWSTR pszResult,
    DWORD cchResult, DWORD* pcchResult, DWORD dwReserved)
    AKARI_CE_NAME(CoInternetParseUrl);

/* aa452118 "CoInternetQueryInfo". */
AKARI_CE_IMPORT HRESULT WINAPI CoInternetQueryInfo(LPCWSTR pwzUrl,
    QUERYOPTION QueryOption, DWORD dwQueryFlags, LPVOID pvBuffer,
    DWORD cbBuffer, DWORD* pcbBuffer, DWORD dwReserved)
    AKARI_CE_NAME(CoInternetQueryInfo);

/* aa452131 "CopyBindInfo" (BINDINFO from objbase.h, see above). */
AKARI_CE_IMPORT HRESULT WINAPI CopyBindInfo(const BINDINFO* pcbiSrc,
    BINDINFO* pcbiDest) AKARI_CE_NAME(CopyBindInfo);

/* aa452132 "CopyStgMedium". */
AKARI_CE_IMPORT HRESULT WINAPI CopyStgMedium(const STGMEDIUM* pcstgmedSrc,
    STGMEDIUM* pstgmedDest) AKARI_CE_NAME(CopyStgMedium);

/* aa452136 "CreateAsyncBindCtx". */
AKARI_CE_IMPORT HRESULT WINAPI CreateAsyncBindCtx(DWORD dwReserved,
    IBindStatusCallback* pbsc, IEnumFORMATETC* penumfmtetc,
    IBindCtx** ppbc) AKARI_CE_NAME(CreateAsyncBindCtx);

/* aa452138 "CreateAsyncBindCtxEx". */
AKARI_CE_IMPORT HRESULT WINAPI CreateAsyncBindCtxEx(IBindCtx* pbc,
    DWORD dwOptions, IBindStatusCallback* pBSCb, IEnumFORMATETC* pEnum,
    IBindCtx** ppBC, DWORD reserved) AKARI_CE_NAME(CreateAsyncBindCtxEx);

/* aa452140 "CreateFormatEnumerator". */
AKARI_CE_IMPORT HRESULT WINAPI CreateFormatEnumerator(UINT cfmtetc,
    FORMATETC* rgfmtetc, IEnumFORMATETC** ppenumfmtetc)
    AKARI_CE_NAME(CreateFormatEnumerator);

/* aa452144 "CreateURLMoniker". */
AKARI_CE_IMPORT HRESULT WINAPI CreateURLMoniker(IMoniker* pmkContext,
    LPWSTR szURL, IMoniker** ppmk) AKARI_CE_NAME(CreateURLMoniker);

/* aa452146 "CreateURLMonikerEx" (page prints LPMONIKER). */
AKARI_CE_IMPORT HRESULT WINAPI CreateURLMonikerEx(LPMONIKER pMkCtx,
    LPCWSTR szURL, LPMONIKER* ppmk, DWORD dwFlags)
    AKARI_CE_NAME(CreateURLMonikerEx);

/* aa452199 "FindMediaType". */
AKARI_CE_IMPORT HRESULT WINAPI FindMediaType(LPCSTR rgszTypes,
    CLIPFORMAT* rgcfTypes) AKARI_CE_NAME(FindMediaType);

/* aa452201 "FindMediaTypeClass". */
AKARI_CE_IMPORT HRESULT WINAPI FindMediaTypeClass(LPBC pbc, LPCSTR szType,
    CLSID* pclsID, DWORD dwReserved) AKARI_CE_NAME(FindMediaTypeClass);

/* aa452204 "FindMimeFromData". */
AKARI_CE_IMPORT HRESULT WINAPI FindMimeFromData(LPBC pBC,
    LPCWSTR pwzUrl, LPVOID pBuffer, DWORD cbSize,
    LPCWSTR pwzMimeProposed, DWORD dwMimeFlags, LPWSTR* ppwzMimeOut,
    DWORD dwReserved) AKARI_CE_NAME(FindMimeFromData);

/* ms906288 "GetClassFileOrMime". */
AKARI_CE_IMPORT HRESULT WINAPI GetClassFileOrMime(LPBC pBC,
    LPCWSTR szFilename, LPVOID pBuffer, DWORD cbSize, LPCWSTR szMime,
    DWORD dwReserved, CLSID* pclsid) AKARI_CE_NAME(GetClassFileOrMime);

/* ms918804 "IsAsyncMoniker". */
AKARI_CE_IMPORT HRESULT WINAPI IsAsyncMoniker(IMoniker* pmk)
    AKARI_CE_NAME(IsAsyncMoniker);

/* ms918808 "IsLoggingEnabled" (Hit Logging book; the page prints the
 * TCHAR-generic name, CE is Unicode-only -- W form, the CreateFileW
 * pattern of winbase.h). */
AKARI_CE_IMPORT BOOL WINAPI IsLoggingEnabledW(LPCTSTR pszUrl)
    AKARI_CE_NAME(IsLoggingEnabledW);

/* ms918810 "IsValidURL". */
AKARI_CE_IMPORT HRESULT WINAPI IsValidURL(LPBC pBC, LPCWSTR szURL,
    DWORD dwReserved) AKARI_CE_NAME(IsValidURL);

/* ms918822 "MkParseDisplayNameEx". */
AKARI_CE_IMPORT HRESULT WINAPI MkParseDisplayNameEx(IBindCtx* pbc,
    LPWSTR szDisplayName, ULONG* pcchEaten, IMoniker** ppmk)
    AKARI_CE_NAME(MkParseDisplayNameEx);

/* ms918829 "ObtainUserAgentString". */
AKARI_CE_IMPORT HRESULT WINAPI ObtainUserAgentString(DWORD dwOption,
    LPCSTR pcszUAOut, DWORD* cbSize)
    AKARI_CE_NAME(ObtainUserAgentString);

/* ms918844 "RegisterBindStatusCallback". */
AKARI_CE_IMPORT HRESULT WINAPI RegisterBindStatusCallback(IBindCtx* pbc,
    IBindStatusCallback* pbsc, IBindStatusCallback** ppbscPrevious,
    DWORD dwReserved) AKARI_CE_NAME(RegisterBindStatusCallback);

/* ms918845 "RegisterFormatEnumerator". */
AKARI_CE_IMPORT HRESULT WINAPI RegisterFormatEnumerator(LPBC pBC,
    IEnumFORMATETC* pEFetc, DWORD reserved)
    AKARI_CE_NAME(RegisterFormatEnumerator);

/* ms918846 "RegisterMediaTypeClass". */
AKARI_CE_IMPORT HRESULT WINAPI RegisterMediaTypeClass(LPBC pbc,
    UINT ctypes, LPCSTR* rgszTypes, CLSID* rgclsID, DWORD dwReserved)
    AKARI_CE_NAME(RegisterMediaTypeClass);

/* ms918847 "RegisterMediaTypes" (see CLIPFORMAT above). */
AKARI_CE_IMPORT HRESULT WINAPI RegisterMediaTypes(UINT ctypes,
    LPCSTR* rgszTypes, CLIPFORMAT* rgcfTypes)
    AKARI_CE_NAME(RegisterMediaTypes);

/* ms918848 "ReleaseBindInfo". */
AKARI_CE_IMPORT void WINAPI ReleaseBindInfo(BINDINFO* pbindinfo)
    AKARI_CE_NAME(ReleaseBindInfo);

/* ms918850 "RevokeBindStatusCallback". */
AKARI_CE_IMPORT HRESULT WINAPI RevokeBindStatusCallback(IBindCtx* pbc,
    IBindStatusCallback* pbsc) AKARI_CE_NAME(RevokeBindStatusCallback);

/* ms918851 "RevokeFormatEnumerator". */
AKARI_CE_IMPORT HRESULT WINAPI RevokeFormatEnumerator(LPBC pbc,
    IEnumFORMATETC* pEFetc) AKARI_CE_NAME(RevokeFormatEnumerator);

/* ms918865 "URLDownloadToCacheFile" (TCHAR-generic print, W form). */
AKARI_CE_IMPORT HRESULT WINAPI URLDownloadToCacheFileW(LPUNKNOWN lpUnkcaller,
    LPCSTR szURL, LPTSTR szFileName, DWORD dwBufLength, DWORD dwReserved,
    IBindStatusCallback* pBSC) AKARI_CE_NAME(URLDownloadToCacheFileW);

/* ms918866 "URLDownloadToFile" (page prints LPBINDSTATUSCALLBACK;
 * TCHAR-generic print, W form). */
AKARI_CE_IMPORT HRESULT WINAPI URLDownloadToFileW(LPUNKNOWN pCaller,
    LPCTSTR szURL, LPCTSTR szFileName, DWORD dwReserved,
    LPBINDSTATUSCALLBACK lpfnCB) AKARI_CE_NAME(URLDownloadToFileW);

/* ms918871 "URLOpenBlockingStream". */
AKARI_CE_IMPORT HRESULT WINAPI URLOpenBlockingStream(LPUNKNOWN pCaller,
    LPCSTR szURL, LPSTREAM* ppStream, DWORD dwReserved,
    LPBINDSTATUSCALLBACK lpfnCB) AKARI_CE_NAME(URLOpenBlockingStream);

/* ms918872 "URLOpenPullStream". */
AKARI_CE_IMPORT HRESULT WINAPI URLOpenPullStream(LPUNKNOWN pCaller,
    LPCSTR szURL, DWORD dwReserved, LPBINDSTATUSCALLBACK lpfnCB)
    AKARI_CE_NAME(URLOpenPullStream);

/* ms918873 "URLOpenStream". */
AKARI_CE_IMPORT HRESULT WINAPI URLOpenStream(LPUNKNOWN pCaller,
    LPCSTR szURL, DWORD dwReserved, LPBINDSTATUSCALLBACK lpfnCB)
    AKARI_CE_NAME(URLOpenStream);

/* ms918868 "UrlMkGetSessionOption". */
AKARI_CE_IMPORT HRESULT WINAPI UrlMkGetSessionOption(DWORD dwOption,
    LPVOID pBuffer, DWORD dwBufferLength, DWORD* pdwBufferLength,
    DWORD dwReserved) AKARI_CE_NAME(UrlMkGetSessionOption);

/* ms918869 "UrlMkSetSessionOption". */
AKARI_CE_IMPORT HRESULT WINAPI UrlMkSetSessionOption(DWORD dwOption,
    LPVOID pBuffer, DWORD dwBufferLength, DWORD dwReserved)
    AKARI_CE_NAME(UrlMkSetSessionOption);

/* ms918878 "WriteHitLogging" (Hit Logging book). */
AKARI_CE_IMPORT BOOL WINAPI WriteHitLogging(
    LPHIT_LOGGING_INFO lpLogginginfo) AKARI_CE_NAME(WriteHitLogging);

/* ------------------------------------------------------------------ */
/*  Interface records (opaque; documented method signatures)           */
/* ------------------------------------------------------------------ */

/*
 * Every record lists the methods as the CE pages document them; all
 * interfaces also carry the IUnknown methods (AddRef, QueryInterface,
 * Release) per the COM model.  Missing-space artifacts of the archive
 * print ("HRESULTGetBindResult", "ockRequest" for LockRequest on
 * aa452309) are normalized; page ids are per method.
 *
 * IAuthenticate (ms906354):
 *   ms906355  HRESULT Authenticate(HWND* phwnd,
 *              LPWSTR* pszUsername, LPWSTR* pszPassword);
 *
 * IBindHost (ms906356):
 *   ms906357  HRESULT CreateMoniker(LPOLESTR szName, IBindCtx* pBC,
 *              IMoniker** ppmk, DWORD dwReserved);
 *   ms906358  HRESULT MonikerBindToObject(IMoniker* pMk, IBindCtx* pBC,
 *              IBindStatusCallback* pBSC, REFIID riid, void** ppvObj);
 *   ms906359  HRESULT MonikerBindToStorage(IMoniker* pMk,
 *              IBindCtx* pBC, IBindStatusCallback* pBSC, REFIID riid,
 *              void** ppvObj);
 *
 * IBinding (ms906360; table also lists SetPriority and Suspend without
 * method pages -- signatures unpublished [held]):
 *   ms906361  HRESULT Abort(VOID);
 *   ms906362  HRESULT GetBindResult(CLSID* pclsidProtocol,
 *              DWORD* pdwResult, LPOLESTR* pszResult,
 *              DWORD* pdwReserved);
 *   ms906363  HRESULT GetPriority(LONG* pnPriority);
 *   ms906364  HRESULT Resume(VOID);  [not currently implemented]
 *
 * IBindStatusCallback (ms906365; OnLowResource "Not currently
 * implemented", no page [held]):
 *   ms906366  HRESULT GetBindInfo(DWORD* grfBINDF,
 *              BINDINFO* pbindinfo);
 *   ms906367  HRESULT GetPriority(LONG* pnPriority);
 *   ms906368  HRESULT OnDataAvailable(DWORD grfBSCF, DWORD dwSize,
 *              FORMATETC* pformatetc, STGMEDIUM* pstgmed);
 *   ms906369  HRESULT OnObjectAvailable(REFIID riid, IUnknown* punk);
 *   ms906370  HRESULT OnProgress(ULONG ulProgress,
 *              ULONG ulProgressMax, ULONG ulStatusCode,
 *              LPCWSTR szStatusText);
 *   ms906371  HRESULT OnStartBinding(DWORD dwReserved, IBinding* pib);
 *   ms906372  HRESULT OnStopBinding(HRESULT hresult,
 *              LPCWSTR szError);
 *
 * IHttpNegotiate (aa452285):
 *   aa452286  HRESULT BeginningTransaction(LPCWSTR szURL,
 *              DWORD dwReserved, LPCWSTR szHeaders,
 *              LPWSTR* pszAdditionalHeaders);
 *   aa452288  HRESULT OnResponse(DWORD dwResponseCode,
 *              LPCWSTR szResponseHeaders, LPCWSTR szRequestHeaders,
 *              LPWSTR* pszAdditionalRequestHeaders);
 *
 * IHttpSecurity (aa452290):
 *   aa452291  HRESULT OnSecurityProblem(DWORD dwProblem);
 *
 * IMonikerProp (ms918293):
 *   ms918294  HRESULT PutProperty(MONIKERPROPERTY mkp, LPCWSTR val);
 *
 * IPersistMoniker (ms918766):
 *   ms918775  HRESULT GetClassID(CLSID* pClassID);
 *   ms918789  HRESULT GetCurMoniker(IMoniker** ppimkName);
 *   ms918798  HRESULT IsDirty(VOID);
 *   ms918800  HRESULT Load(BOOL fFullyAvailable, IMoniker* pimkName,
 *              LPBC pibc, DWORD grfMode);
 *   ms918801  HRESULT Save(IMoniker* pimkName, LPBC pbc,
 *              BOOL fRemember);
 *   ms918802  HRESULT SaveCompleted(IMoniker* pimkName, LPBC pibc);
 *
 * IWindowForBindingUI (ms918811):
 *   ms918812  HRESULT GetWindow(REFGUID rguidReason, HWND* phwnd);
 *
 * IWinInetHttpInfo (ms918813):
 *   ms918814  HRESULT QueryInfo(DWORD dwOption, LPVOID pBuffer,
 *              DWORD* pcbBuf, DWORD* pdwFlags, DWORD* pdwReserved);
 *
 * IWinInetInfo (ms918815):
 *   ms918816  HRESULT QueryOption(DWORD dwOption, LPVOID pBuffer,
 *              DWORD* pcbBuf);
 *
 * IInternetSession (aa452340):
 *   aa452341  HRESULT RegisterMimeFilter(IClassFactory* pCF,
 *              REFCLSID rclsid, LPCWSTR pwzType);
 *   aa452342  HRESULT RegisterNameSpace(IClassFactory* pCF,
 *              REFCLSID rclsid, LPCWSTR pwzProtocol, ULONG cPatterns,
 *              const LPCWSTR* ppwzPatterns, DWORD dwReserved);
 *   aa452343  HRESULT UnregisterMimeFilter(IClassFactory* pCF,
 *              LPCWSTR pwzType);
 *   aa452344  HRESULT UnregisterNameSpace(IClassFactory* pCF,
 *              LPCWSTR pszProtocol);
 *
 * IInternetProtocol (aa452303):
 *   aa452309  HRESULT LockRequest(DWORD dwOptions);
 *   aa452310  HRESULT Read(void* pv, ULONG cb, ULONG* pcbRead);
 *   aa452316  HRESULT Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin,
 *              ULARGE_INTEGER* plibNewPosition);
 *   aa452326  HRESULT UnlockRequest(VOID);
 *
 * IInternetProtocolInfo (aa452304):
 *   aa452305  HRESULT CombineUrl(LPCWSTR pwzBaseUrl,
 *              LPCWSTR pwzRelativeUrl, DWORD dwCombineFlags,
 *              LPWSTR pwzResult, DWORD cchResult, DWORD* pcchResult,
 *              DWORD dwReserved);
 *   aa452306  HRESULT CompareUrl(LPCWSTR pwzUrl1, LPCWSTR pwzUrl2,
 *              DWORD dwCompareFlags);
 *   aa452307  HRESULT ParseUrl(LPCWSTR pwzUrl,
 *              PARSEACTION ParseAction, DWORD dwParseFlags,
 *              LPWSTR pwzResult, DWORD cchResult, DWORD* pcchResult,
 *              DWORD dwReserved);
 *   aa452308  HRESULT QueryInfo(LPCWSTR pwzUrl,
 *              QUERYOPTION OueryOption, DWORD dwQueryFlags,
 *              LPVOID pBuffer, DWORD cbBuffer, DWORD* pcbBuf,
 *              DWORD dwReserved);  [parameter name "OueryOption" as
 *              printed; the type is QUERYOPTION]
 *
 * IInternetProtocolRoot (aa452311; Resume and Suspend "Not
 * implemented", no pages [held]):
 *   aa452312  HRESULT Abort(HRESULT hrReason, DWORD dwOptions);
 *   aa452313  HRESULT Continue(PROTOCOLDATA* pProtocolData);
 *   aa452314  HRESULT Start(LPCWSTR szUrl,
 *              IInternetProtocolSink* pOIProtSink,
 *              IInternetBindInfo* pOIBindInfo, DWORD grfPI,
 *              HANDLE_PTR dwReserved);
 *   aa452315  HRESULT Terminate(DWORD dwOptions);
 *
 * IInternetProtocolSink (aa452317):
 *   aa452318  HRESULT ReportData(DWORD grfBSCF, ULONG ulProgress,
 *              ULONG ulProgressMax);
 *   aa452319  HRESULT ReportProgress(ULONG ulStatusCode,
 *              LPCWSTR szStatusText);
 *   aa452320  HRESULT ReportResult(HRESULT hrResult, DWORD dwError,
 *              LPCWSTR szResult);
 *   aa452325  HRESULT Switch(PROTOCOLDATA* pProtocolData);
 *
 * IInternetProtocolSinkStackable (aa452321):
 *   aa452322  HRESULT CommitSwitch(VOID);
 *   aa452323  HRESULT RollbackSwitch(VOID);
 *   aa452324  HRESULT SwitchSink(IInternetProtocolSink* pOIProtSink);
 *
 * IInternetBindInfo (aa452293):
 *   aa452294  HRESULT GetBindInfo(DWORD* grfBINDF,
 *              BINDINFO* pbindinfo);
 *   aa452295  HRESULT GetBindString(ULONG ulStringType,
 *              LPOLESTR* ppwzStr, ULONG cEl, ULONG* pcElFetched);
 *
 * IInternetPriority (aa452300):
 *   aa452301  HRESULT GetPriority(LONG* pnPriority);
 *   aa452302  HRESULT SetPriority(LONG nPriority);
 *
 * IInternetHostSecurityManager (aa452296):
 *   aa452297  HRESULT GetSecurityId(BYTE* pbSecurityId,
 *              DWORD* pcbSecurityId, DWORD_PTR dwReserved);
 *   aa452298  HRESULT ProcessUrlAction(DWORD dwAction, BYTE* pPolicy,
 *              DWORD cbPolicy, BYTE* pContext, DWORD cbContext,
 *              DWORD dwFlags, DWORD dwReserved);
 *   aa452299  HRESULT QueryCustomPolicy(REFGUID guidKey,
 *              BYTE** ppPolicy, DWORD* pcbPolicy, BYTE* pContext,
 *              DWORD cbContext, DWORD dwReserved);
 *
 * IInternetSecurityManager (aa452327):
 *   aa452328  HRESULT GetSecurityId(LPCWSTR pwszUrl,
 *              BYTE* pbSecurityId, DWORD* pcbSecurityId,
 *              DWORD_PTR dwReserved);
 *   aa452329  HRESULT GetSecuritySite(
 *              IInternetSecurityMgrSite** ppSite);
 *   aa452330  HRESULT GetZoneMappings(DWORD dwZone,
 *              IEnumString** ppenumString, DWORD dwFlags);
 *   aa452331  HRESULT MapUrlToZone(LPCWSTR pwszUrl, DWORD* pdwZone,
 *              DWORD dwFlags);
 *   aa452332  HRESULT ProcessUrlAction(LPCWSTR pwszUrl,
 *              DWORD dwAction, BYTE* pPolicy, DWORD cbPolicy,
 *              BYTE* pContext, DWORD cbContext, DWORD dwFlags,
 *              DWORD dwReserved);
 *   aa452334  HRESULT QueryCustomPolicy(LPCWSTR pwszUrl,
 *              REFGUID guidKey, BYTE** ppPolicy, DWORD* pcbPolicy,
 *              BYTE* pContext, DWORD cbContext, DWORD dwReserved);
 *   aa452335  HRESULT SetSecuritySite(IInternetSecurityMgrSite* pSite);
 *   aa452336  HRESULT SetZoneMapping(DWORD dwZone,
 *              LPCWSTR lpszPattern, DWORD dwFlags);
 *
 * IInternetSecurityMgrSite (aa452337):
 *   aa452338  HRESULT EnableModeless(BOOL fEnable);
 *   aa452339  HRESULT GetWindow(HWND* phwnd);
 *
 * IInternetZoneManager (aa452345; LogAction and PromptAction "Not
 * currently implemented", no pages [held]):
 *   aa452346  HRESULT CreateZoneEnumerator(DWORD* pdwEnum,
 *              DWORD* pdwCount, DWORD dwFlags);
 *   aa452347  HRESULT DestroyZoneEnumerator(DWORD dwEnum);
 *   aa452348  HRESULT GetZoneActionPolicy(DWORD dwZone, DWORD dwAction,
 *              BYTE* pPolicy, DWORD cbPolicy,
 *              URLZONEREG urlZoneReg);
 *   aa452349  HRESULT GetZoneAt(DWORD dwEnum, DWORD dwIndex,
 *              DWORD* pdwZone);
 *   aa452350  HRESULT GetZoneAttributes(DWORD dwZone,
 *              ZONEATTRIBUTES* pZoneAttributes);
 *              [ZONEATTRIBUTES held -- see the structure note above]
 *   aa452351  HRESULT GetZoneCustomPolicy(DWORD dwZone,
 *              REFGUID guidKey, BYTE** ppPolicy, DWORD* pcbPolicy,
 *              URLZONEREG urlZoneReg);
 *   aa452352  HRESULT SetZoneActionPolicy(DWORD dwZone, DWORD dwAction,
 *              BYTE* pPolicy, DWORD cbPolicy,
 *              URLZONEREG urlZoneReg);
 *   aa452353  HRESULT SetZoneAttributes(DWORD dwZone,
 *              ZONEATTRIBUTES* pZoneAttributes);  [ZONEATTRIBUTES held]
 *   aa452354  HRESULT SetZoneCustomPolicy(DWORD dwZone,
 *              REFGUID guidKey, BYTE* pPolicy, DWORD cbPolicy,
 *              URLZONEREG urlZoneReg);
 */

/* ------------------------------------------------------------------
 * Book surface: urlmon-app (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa452294 IInternetBindInfo::GetBindInfo (Header: Urlmon.h, Urlmon.idl.) */
/* aa452295 IInternetBindInfo::GetBindString (Header: Urlmon.h, Urlmon.idl.) */
/* aa452301 IInternetPriority::GetPriority (Header: Urlmon.h, Urlmon.idl.) */
/* aa452302 IInternetPriority::SetPriority (Header: Urlmon.h, Urlmon.idl.) */
/* aa452309 IInternetProtocol::LockRequest (Header: Urlmon.h, Urlmon.idl.) */
/* aa452310 IInternetProtocol::Read (Header: Urlmon.h, Urlmon.idl.) */
/* aa452316 IInternetProtocol::Seek (Header: Urlmon.h, Urlmon.idl.) */
/* aa452326 IInternetProtocol::UnlockRequest (Header: Urlmon.h, Urlmon.idl.) */
/* aa452305 IInternetProtocolInfo::CombineUrl (Header: Urlmon.h, Urlmon.idl.) */
/* aa452306 IInternetProtocolInfo::CompareUrl (Header: Urlmon.h, Urlmon.idl.) */
/* aa452307 IInternetProtocolInfo::ParseUrl (Header: Urlmon.h, Urlmon.idl.) */
/* aa452308 IInternetProtocolInfo::QueryInfo (Header: Urlmon.h, Urlmon.idl.) */
/* aa452312 IInternetProtocolRoot::Abort (Header: Urlmon.h, Urlmon.idl.) */
/* aa452313 IInternetProtocolRoot::Continue (Header: Urlmon.h, Urlmon.idl.) */
/* aa452314 IInternetProtocolRoot::Start (Header: Urlmon.h, Urlmon.idl.) */
/* aa452315 IInternetProtocolRoot::Terminate (Header: Urlmon.h, Urlmon.idl.) */
/* aa452318 IInternetProtocolSink::ReportData (Header: Urlmon.h, Urlmon.idl.) */
/* aa452319 IInternetProtocolSink::ReportProgress (Header: Urlmon.h, Urlmon.idl.) */
/* aa452320 IInternetProtocolSink::ReportResult (Header: Urlmon.h, Urlmon.idl.) */
/* aa452325 IInternetProtocolSink::Switch (Header: Urlmon.h, Urlmon.idl.) */
/* aa452322 IInternetProtocolSinkStackable::CommitSwitch (Header: Urlmon.h, Urlmon.idl.) */
/* aa452323 IInternetProtocolSinkStackable::RollbackSwitch (Header: Urlmon.h, Urlmon.idl.) */
/* aa452324 IInternetProtocolSinkStackable::SwitchSink (Header: Urlmon.h, Urlmon.idl.) */
/* aa452341 IInternetSession::RegisterMimeFilter (Header: Urlmon.h, Urlmon.idl.) */
/* aa452342 IInternetSession::RegisterNameSpace (Header: Urlmon.h, Urlmon.idl.) */
/* aa452343 IInternetSession::UnregisterMimeFilter (Header: Urlmon.h, Urlmon.idl.) */
/* aa452344 IInternetSession::UnregisterNameSpace (Header: Urlmon.h, Urlmon.idl.) */

/* ------------------------------------------------------------------
 * Book surface: urlmon-app (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms905670 Asynchronous Pluggable Protocols Enumerations */
/* ms905671 Asynchronous Pluggable Protocols Functions */
/* ms905672 Asynchronous Pluggable Protocols Interfaces */
/* ms905674 Asynchronous Pluggable Protocols Structures */

/* ------------------------------------------------------------------
 * Book surface: urlmon-hitlog (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms905677 Hit Logging Functions */
/* ms905679 Hit Logging Structures */

/* ------------------------------------------------------------------
 * Book surface: urlmon-zones (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa452297 IInternetHostSecurityManager::GetSecurityId (Header: Urlmon.h, Urlmon.idl.) */
/* aa452298 IInternetHostSecurityManager::ProcessUrlAction (Header: Urlmon.h, Urlmon.idl.) */
/* aa452299 IInternetHostSecurityManager::QueryCustomPolicy (Header: Urlmon.h, Urlmon.idl.) */
/* aa452328 IInternetSecurityManager::GetSecurityId (Header: Urlmon.h, Urlmon.idl.) */
/* aa452329 IInternetSecurityManager::GetSecuritySite (Header: Urlmon.h, Urlmon.idl.) */
/* aa452330 IInternetSecurityManager::GetZoneMappings (Header: Urlmon.h, Urlmon.idl.) */
/* aa452331 IInternetSecurityManager::MapUrlToZone (Header: Urlmon.h, Urlmon.idl.) */
/* aa452332 IInternetSecurityManager::ProcessUrlAction (Header: Urlmon.h, Urlmon.idl.) */
/* aa452334 IInternetSecurityManager::QueryCustomPolicy (Header: Urlmon.h, Urlmon.idl.) */
/* aa452335 IInternetSecurityManager::SetSecuritySite (Header: Urlmon.h, Urlmon.idl.) */
/* aa452336 IInternetSecurityManager::SetZoneMapping (Header: Urlmon.h, Urlmon.idl.) */
/* aa452338 IInternetSecurityMgrSite::EnableModeless (Header: Urlmon.h, Urlmon.idl.) */
/* aa452339 IInternetSecurityMgrSite::GetWindow (Header: Urlmon.h, Urlmon.idl.) */
/* aa452346 IInternetZoneManager::CreateZoneEnumerator (Header: Urlmon.h, Urlmon.idl.) */
/* aa452347 IInternetZoneManager::DestroyZoneEnumerator (Header: Urlmon.h, Urlmon.idl.) */
/* aa452348 IInternetZoneManager::GetZoneActionPolicy (Header: Urlmon.h, Urlmon.idl.) */
/* aa452349 IInternetZoneManager::GetZoneAt (Header: Urlmon.h, Urlmon.idl.) */
/* aa452350 IInternetZoneManager::GetZoneAttributes (Header: Urlmon.h, Urlmon.idl.) */
/* aa452351 IInternetZoneManager::GetZoneCustomPolicy (Header: Urlmon.h, Urlmon.idl.) */
/* aa452352 IInternetZoneManager::SetZoneActionPolicy (Header: Urlmon.h, Urlmon.idl.) */
/* aa452353 IInternetZoneManager::SetZoneAttributes (Header: Urlmon.h, Urlmon.idl.) */
/* aa452354 IInternetZoneManager::SetZoneCustomPolicy (Header: Urlmon.h, Urlmon.idl.) */
/* aa452025 Internet Security Manager (Header: Urlmon.h, Urlmon.idl.) */
/* aa452026 Internet Zone Manager (Header: Urlmon.h, Urlmon.idl.) */
/* ms918863 URL Action Flags (Header: Urlmon.h, Urlmon.idl.) */
/* ms918874 URL Policy Flags (Header: Urlmon.h, Urlmon.idl.) */

/* ------------------------------------------------------------------
 * Book surface: urlmon-zones (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa452027 Internet Zone Settings */
/* aa452033 Local Intranet Zone Settings */
/* ms905325 Restricted Sites Zone Settings */
/* ms905634 Trusted Sites Zone Settings */
/* aa452082 URL Security Zones Constants */
/* aa452083 URL Security Zones Enumerations */
/* aa452084 URL Security Zones Functions */
/* aa452085 URL Security Zones Interfaces */
/* aa452086 URL Security Zones Objects */
/* ms919149 URL Security Zones Settings */
/* aa452088 URL Security Zones Structures */

/* ------------------------------------------------------------------
 * Book surface: urlmon (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms906355 IAuthenticate::Authenticate (Header: Urlmon.h, Urlmon.idl.) */
/* ms906357 IBindHost::CreateMoniker (Header: Urlmon.h, Urlmon.idl.) */
/* ms906358 IBindHost::MonikerBindToObject (Header: Urlmon.h, Urlmon.idl.) */
/* ms906359 IBindHost::MonikerBindToStorage (Header: Urlmon.h, Urlmon.idl.) */
/* ms906361 IBinding::Abort (Header: Urlmon.h, Urlmon.idl.) */
/* ms906362 IBinding::GetBindResult (Header: Urlmon.h, Urlmon.idl.) */
/* ms906363 IBinding::GetPriority (Header: Urlmon.h, Urlmon.idl.) */
/* ms906364 IBinding::Resume (Header: Urlmon.h, Urlmon.idl.) */
/* ms906366 IBindStatusCallback::GetBindInfo (Header: Urlmon.h, Urlmon.idl.) */
/* ms906367 IBindStatusCallback::GetPriority (Header: Urlmon.h, Urlmon.idl.) */
/* ms906368 IBindStatusCallback::OnDataAvailable (Header: Urlmon.h, Urlmon.idl.) */
/* ms906369 IBindStatusCallback::OnObjectAvailable (Header: Urlmon.h, Urlmon.idl.) */
/* ms906370 IBindStatusCallback::OnProgress (Header: Urlmon.h, Urlmon.idl.) */
/* ms906371 IBindStatusCallback::OnStartBinding (Header: Urlmon.h, Urlmon.idl.) */
/* ms906372 IBindStatusCallback::OnStopBinding (Header: Urlmon.h, Urlmon.idl.) */
/* aa452286 IHttpNegotiate::BeginningTransaction (Header: Urlmon.h, Urlmon.idl.) */
/* aa452288 IHttpNegotiate::OnResponse (Header: Urlmon.h, Urlmon.idl.) */
/* aa452291 IHttpSecurity::OnSecurityProblem (Header: Urlmon.h, Urlmon.idl.) */
/* ms918294 IMonikerProp::PutProperty (Header: Urlmon.h, Urlmon.idl.) */
/* ms918775 IPersistMoniker::GetClassID (Header: Urlmon.h, Urlmon.idl.) */
/* ms918789 IPersistMoniker::GetCurMoniker (Header: Urlmon.h, Urlmon.idl.) */
/* ms918798 IPersistMoniker::IsDirty (Header: Urlmon.h, Urlmon.idl.) */
/* ms918800 IPersistMoniker::Load (Header: Urlmon.h, Urlmon.idl.) */
/* ms918801 IPersistMoniker::Save (Header: Urlmon.h, Urlmon.idl.) */
/* ms918802 IPersistMoniker::SaveCompleted (Header: Urlmon.h, Urlmon.idl.) */
/* ms918812 IWindowForBindingUI::GetWindow (Header: Urlmon.h, Urlmon.idl.) */
/* ms918814 IWinInetHttpInfo::QueryInfo (Header: Urlmon.h, Urlmon.idl.) */
/* ms918816 IWinInetInfo::QueryOption (Header: Urlmon.h, Urlmon.idl.) */
/* ms918870 URL Moniker Error Codes Constants (Header: Urlmon.h, Urlmon.idl.) */

/* ------------------------------------------------------------------
 * Book surface: urlmon (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms918766 IPersistMoniker */
/* aa452074 URL Moniker Services Enumerations */
/* aa452076 URL Moniker Services Errors */
/* aa452078 URL Moniker Services Functions */
/* aa452079 URL Moniker Services Interfaces */
/* aa452081 URL Moniker Services Structures */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_URLMON_H */
