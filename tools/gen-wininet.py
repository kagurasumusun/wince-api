#!/usr/bin/env python3
"""Emit include/Wininet.h, include/Wininetui.h, include/Urlmonui.h (M92)."""
import json, sys, re, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from rtctext import page_text

# ---- function table: (name, id, print, kind) kind: D=declare R=record
D, R = 'D', 'R'
FUNCS = [
 ("InternetAttemptConnect","ms918340","DWORD InternetAttemptConnect(DWORDdwReserved);",D),
 ("InternetCheckConnection","ms918346","BOOL InternetCheckConnection(LPCTSTRlpszUrl,DWORDdwFlags,DWORDdwReserved);",D),
 ("InternetConfirmZoneCrossing","ms918350","DWORDInternetConfirmZoneCrossing(HWNDhWnd,LPTSTRszUrlPrev,LPTSTRszUrlNew,BOOLbPost);",D),
 ("InternetCombineUrl","ms918349","BOOL WINAPI InternetCombineUrl(LPCTSTR lpszBaseUrl, LPCTSTR lpszRelativeUrl, LPTSTR lpszBuffer, LPDWORD lpdwBufferLength, DWORD dwFlags);",D),
 ("InternetCreateUrl","ms918355","BOOL WINAPI InternetCreateUrl(LPURL_COMPONENTS lpUrlComponents, DWORD dwFlags, LPTSTR lpszUrl, LPDWORD lpdwUrlLength );",R),
 ("InternetCrackUrl","ms918354","BOOL WINAPIInternetCrackUrl(LPCTSTRlpszUrl,DWORDdwUrlLength,DWORDdwFlags,LPURL_COMPONENTSlpUrlComponents);",R),
 ("InternetEnumPerSiteCookieDecisionA","ms918356","BOOL InternetEnumPerSiteCookieDecisionA( LPSTR pszSiteName, unsigned long *pcSiteNameSize, unsigned long *pdwDecision, unsigned long dwIndex);",D),
 ("InternetEnumPerSiteCookieDecisionW","ms918357","BOOL InternetEnumPerSiteCookieDecisionW( LPSTR pszSiteName, unsigned long *pcSiteNameSize, unsigned long *pdwDecision, unsigned long dwIndex);",D),
 ("InternetGetConnectedState","ms918360","BOOL InternetGetConnectedState(LPDWORD lpdwFlags,DWORD dwReserved);",D),
 ("InternetGetConnectedStateEx","ms918361","BOOLInternetGetConnectedStateEx(LPDWORDlpdwFlags,LPTSTRlpszConnectionName,DWORDdwNameLen,DWORDdwReserved);",D),
 ("InternetGetCookie","ms918362","BOOL InternetGetCookie(LPCTSTR lpszUrl,LPCTSTR lpszCookieName,LPSTR lpCookieData,LPDWORD lpdwSize);",D),
 ("InternetGetLastResponseInfo","ms918363","BOOL WINAPI InternetGetLastResponseInfo( LPDWORD lpdwError, LPTSTR lpszBuffer, LPDWORD lpdwBufferLength);",D),
 ("InternetGetPerSiteCookieDecisionA","ms918364","BOOL InternetGetPerSiteCookieDecisionA ( LPCSTR pchHostName, unsigned long* pResult);",D),
 ("InternetGetPerSiteCookieDecisionW","ms918365","BOOL InternetGetPerSiteCookieDecisionW ( LPCSTR pchHostName, unsigned long* pResult);",D),
 ("InternetGoOnline","ms918366","BOOL InternetGoOnline(LPTSTR lpszURL,HWND hwndParent,DWORD dwReserved);",D),
 ("InternetSetCookie","ms918378","BOOL InternetSetCookie(LPCTSTR lpszUrl, LPCTSTR lpszCookieName, LPCTSTR lpszCookieData);",D),
 ("InternetSetCookieEx","ms918379","BOOL InternetSetCookieEx( LPCTSTRlpszUrl,LPCTSTRlpszCookieName,LPCTSTRlpszCookieData,DWORDdwFlags,DWORD_PTRdwReserved);",D),
 ("InternetSetPerSiteCookieDecisionA","ms918383","BOOL InternetSetPerSiteCookieDecisionA( LPCSTR pchHostName, DWORD dwDecision);",D),
 ("InternetSetPerSiteCookieDecisionW","ms918384","BOOL InternetSetPerSiteCookieDecisionW( LPCSTR pchHostName, DWORD dwDecision);",D),
 ("InternetTimeFromSystemTime","ms918387","BOOL WINAPI InternetTimeFromSystemTime(CONST SYSTEMTIME* pst, DWORD dwRFC, LPTSTR lpszTime, DWORD cbTime);",D),
 ("InternetTimeToSystemTime","ms918388","BOOL InternetTimeToSystemTime(LPCTSTR lpszTime, SYSTEMTIME* pst, DWORD dwReserved);",D),
 ("InternetUnlockRequestFile","ms918389","BOOL InternetUnlockRequestFile(HANDLE hLockRequestInfo);",D),
 ("InternetWriteFile","ms918391","BOOL InternetWriteFile(HINTERNET hFile,LPCVOIDlpBuffer,DWORDdwNumberOfBytesToWrite,LPDWORDlpdwNumberOfBytesWritten);",R),
 ("CommitUrlCacheEntry","aa452121","BOOL CommitUrlCacheEntry( LPCTSTR lpszUrlName,LPCTSTR lpszLocalFileName,FILETIME ExpireTime,FILETIME LastModifiedTime,DWORD CacheEntryType,LPBYTE lpHeaderInfo,DWORD dwHeaderSize,LPCTSTR lpszFileExtension,DWORD dwReserved);",D),
 ("CreateUrlCacheEntry","aa452142","BOOL CreateUrlCacheEntry( LPCTSTR lpszUrlName,DWORD dwExpectedFileSize,LPCTSTR lpszFileExtension,LPSTR lpszFileName,DWORD dwReserved);",D),
 ("DeleteUrlCacheEntry","aa452150","BOOL DeleteUrlCacheEntry( LPCTSTR lpszUrlName);",D),
 ("FindCloseUrlCache","aa452195","BOOL FindCloseUrlCache( HANDLE hEnumHandle);",D),
 ("FindNextUrlCacheEntry","ms919204","BOOL FindNextUrlCacheEntry( HANDLE hEnumHandle,LPINTERNET_CACHE_ENTRY_INFO lpNextCacheEntryInfo,LPDWORD lpdwNextCacheEntryInfoBufferSize);",D),
 ("FindNextUrlCacheEntryEx","aa452206","BOOLAPI FindNextUrlCacheEntryEx( HANDLE hEnumHandle,LPINTERNET_CACHE_ENTRY_INFO lpFirstCacheEntryInfo,LPDWORD lpdwFirstCacheEntryInfoBufferSize,LPVOID lpGroupAttributes,LPDWORD pcbGroupAttributes,LPVOID lpReserved);",D),
 ("GetUrlCacheEntryInfo","ms906320","BOOL GetUrlCacheEntryInfo( LPCTSTR lpszUrlName,LPINTERNET_CACHE_ENTRY_INFO lpCacheEntryInfo,LPDWORD lpdwCacheEntryInfoBufferSize);",D),
 ("GetUrlCacheEntryInfoEx","ms906328","BOOL GetUrlCacheEntryInfoEx( LPCSTR lpszUrl,LPINTERNET_CACHE_ENTRY_INFO lpCacheEntryInfo,LPDWORD lpdwCacheEntryInfoBufSize,LPSTRlpszReserved,LPDWORDlpdwReserved,LPVOIDlpReserved,DWORDdwFlags);",D),
 ("ReadUrlCacheEntryStream","aa452489","BOOL ReadUrlCacheEntryStream( HANDLE hUrlCacheStream,DWORD dwLocation, LPVOIDlpBuffer,LPDWORDlpdwLen, DWORDdwReserved );",D),
 ("RetrieveUrlCacheEntryStream","aa452490","HANDLE RetrieveUrlCacheEntryStream( LPCTSTR lpszUrlName LPINTERNET_CACHE_ENTRY_INFO lpCacheEntryInfo, LPDWORD lpdwCacheEntryInfoBufferSize, BOOL fRandomRead, DWORD dwReserved);",D),
 ("RetrieveUrlCacheEntryFile","ms918849","BOOLRetrieveUrlCacheEntryFile(LPCTSTRlpszUrlName, LPINTERNET_CACHE_ENTRY_INFOlpCacheEntryInfo,LPDWORDlpdwCacheEntryInfoBufferSize, DWORDdwReserved);",D),
 ("SetUrlCacheEntryInfo","ms918858","BOOLSetUrlCacheEntryInfo(LPCSTRlpszUrlName,LPINTERNET_CACHE_ENTRY_INFOlpCacheEntryInfo,DWORDdwFieldControl);",D),
 ("UnlockUrlCacheEntryFile","ms918862","BOOLUnlockUrlCacheEntryFile(LPCSTRlpszUrlName,DWORDdwReserved);",D),
 ("UnlockUrlCacheEntryStream","aa452493","BOOL UnlockUrlCacheEntryStream( LHANDLE hUrlCacheStream, DWORD dwReserved);",D),
 # HINTERNET-by-value set (recorded)
 ("InternetCloseHandle","ms918348","BOOL WINAPI InternetCloseHandle(HINTERNEThInternet);",R),
 ("InternetConnect","ms918351","HINTERNET WINAPI InternetConnect(HINTERNET hInternet, LPCTSTR lpszServerName, INTERNET_PORT nServerPort, LPCTSTR lpszUserName, LPCTSTR lpszPassword, DWORD dwService, DWORD dwFlags, DWORD dwContext);",R),
 ("InternetErrorDlg","ms918358","DWORD InternetErrorDlg(HWND hWnd, HINTERNET hRequest,DWORD dwError,DWORD dwFlags,LPVOID* lppvData);",R),
 ("InternetFindNextFile","ms918359","BOOL WINAPI InternetFindNextFile(HINTERNET hFind, LPVOID lpvFindData);",R),
 ("InternetLockRequestFile","ms918367","BOOL InternetLockRequestFile(HINTERNEThInternet,HANDLE* lphLockRequestInfo);",R),
 ("InternetOpen","ms918368","HINTERNET WINAPI InternetOpen(LPCTSTRlpszAgent,DWORD dwAccessType, LPCTSTR lpszProxy, LPCTSTR lpszProxyBypass, DWORD dwFlags);",R),
 ("InternetOpenUrl","ms918369","HINTERNET InternetOpenUrl( HINTERNET hInternetSession, LPCTSTR lpszUrl, LPCTSTR lpszHeaders, DWORD dwHeadersLength, DWORD dwFlags, DWORD dwContext);",R),
 ("InternetQueryDataAvailable","ms918373","BOOL WINAPI InternetQueryDataAvailable(HINTERNET hFile, LPDWORD lpdwNumberOfBytesAvailable, DWORD dwFlags, DWORD dwContext);",R),
 ("InternetQueryOption","ms918374","BOOL WINAPI InternetQueryOption(HINTERNET hInternet, DWORD dwOption, LPVOID lpBuffer OPTIONAL, LPDWORD lpdwBufferLength);",R),
 ("InternetReadFile","ms918375","BOOL WINAPI InternetReadFile(HINTERNEThFile,LPVOIDlpBuffer,DWORDdwNumberOfBytesToRead,LPDWORDlpdwNumberOfBytesRead);",R),
 ("InternetReadFileEx","ms918376","BOOL InternetReadFileEx(HINTERNEThFile,LPINTERNET_BUFFERS lpBuffersOut,DWORD dwFlags,DWORD dwContext);",R),
 ("InternetSetFilePointer","ms918380","DWORD InternetSetFilePointer(HINTERNET hFile,LONG lDistanceToMove, PVOID pReserved, DWORD dwMoveMethod,DWORD dwContext);",R),
 ("InternetSetOption","ms918381","BOOL WINAPI InternetSetOption(HINTERNET hInternet, DWORD dwOption, LPVOID lpBuffer, DWORD dwBufferLength);",R),
 ("InternetSetOptionEx","ms918382","(stub: the page states it only calls InternetSetOption and has no functionality of its own; no signature printed)",R),
 ("InternetSetStatusCallback","ms918385","INTERNET_STATUS_CALLBACK WINAPIInternetSetStatusCallback(HINTERNEThInternet,...",R),
 ("FtpCommand","aa452208","BOOL WINAPI FtpCommand(HINTERNET hConnect, BOOL fExpectResponse, DWORD dwFlags, LPCTSTR lpszCommand, DWORD dwContext);",R),
 ("FtpCreateDirectory","aa452210","BOOL WINAPI FtpCreateDirectory(HINTERNET hConnect, LPCTSTR lpszDirectory);",R),
 ("FtpDeleteFile","aa452212","BOOL WINAPI FtpDeleteFile(HINTERNET hConnect, LPCTSTR lpszFileName);",R),
 ("FtpFindFirstFile","aa452214","HINTERNET FtpFindFirstFile(HINTERNET hConnect, LPCTSTR lpszSearchFile, LPWIN32_FIND_DATA lpFindFileData, DWORD dwFlags, DWORD dwContext);",R),
 ("FtpGetCurrentDirectory","aa452216","BOOL WINAPI FtpGetCurrentDirectory(HINTERNET hConnect, LPCTSTR lpszCurrentDirectory, LPDWORD lpdwCurrentDirectory);",R),
 ("FtpGetFile","aa452218","BOOL WINAPI FtpGetFile(HINTERNET hConnect, LPCTSTR lpszRemoteFile, LPCTSTR lpszNewFile, BOOL fFailIfExists, DWORD dwFlagsAndAttributes, DWORD dwFlags, DWORD dwContext);",R),
 ("FtpGetFileEx","aa452230","BOOL WINAPI FtpGetFileEx(HINTERNEThFtpSession,LPCTSTR lpszRemoteFile, LPCTSTR lpszNewFile, BOOL fFailIfExists, DWORD dwFlagsAndAttributes, DWORD dwFlags, DWORD dwContext);",R),
 ("FtpGetFileSize","aa452232","DWORD FtpGetFileSize(HINTERNEThFile,LPDWORDlpdwFileSizeHigh);",R),
 ("FtpOpenFile","aa452234","HINTERNET FtpOpenFile(HINTERNET hConnect, LPCTSTR lpszFileName, DWORD dwAccess, DWORD dwFlags, DWORD dwContext);",R),
 ("FtpPutFile","aa452236","BOOL WINAPI FtpPutFile(HINTERNET hConnect, LPCTSTR lpszLocalFile, LPCTSTR lpszNewRemoteFile, DWORD dwFlags, DWORD dwContext);",R),
 ("FtpPutFileEx","aa452238","BOOLAPI FtpPutFileEx(HINTERNET hFtpSession, LPCTSTR lpszLocalFile, LPCTSTR lpszNewRemoteFile, DWORD dwFlags, DWORD dwContext);",R),
 ("FtpRemoveDirectory","aa452240","BOOL WINAPI FtpRemoveDirectory(HINTERNET hConnect, LPCTSTR lpszDirectory);",R),
 ("FtpRenameFile","ms906192","BOOL WINAPI FtpRenameFile(HINTERNET hConnect, LPCTSTR lpszExisting, LPCTSTR lpszNew);",R),
 ("FtpSetCurrentDirectory","ms906282","BOOL WINAPI FtpSetCurrentDirectory(HINTERNET hConnect, LPCTSTR lpszDirectory);",R),
 ("HttpAddRequestHeaders","ms906344","BOOL WINAPI HttpAddRequestHeaders(HINTERNET hHttpRequest, LPCTSTR lpszHeaders, DWORD dwHeadersLength, DWORD dwModifiers);",R),
 ("HttpEndRequest","ms906345","BOOL HttpEndRequest(HINTERNET hRequest,LPINTERNET_BUFFERS lpBuffersOut, DWORD dwFlags,DWORD dwContext);",R),
 ("HttpOpenRequest","ms906346","HINTERNET WINAPI HttpOpenRequest(HINTERNET hConnect, LPCTSTR lpszVerb, LPCTSTR lpszObjectName, LPCTSTR lpszVersion, LPCTSTR lpszReferrer, LPCTSTR* lplpszAcceptTypes, DWORD dwFlags, DWORD dwContext );",R),
 ("HttpQueryInfo","ms906347","BOOL WINAPI HttpQueryInfo(HINTERNET hRequest, DWORD dwInfoLevel, LPVOID lpBuffer, LPDWORD lpdwBufferLength, LPDWORD lpdwIndex);",R),
 ("HttpSendRequest","ms906349","BOOL WINAPI HttpSendRequest(HINTERNET hRequest, LPCTSTR lpszHeaders, DWORD dwHeadersLength, LPVOID lpOptional, DWORD dwOptionalLength);",R),
 ("HttpSendRequestEx","ms906350","BOOL HttpSendRequestEx(HINTERNET hRequest, LPINTERNET_BUFFERS lpBuffersIn,LPINTERNET_BUFFERS lpBuffersOut,DWORD dwFlags,DWORD dwContext);",R),
 # GROUPID-by-value set (recorded)
 ("CreateUrlCacheGroup","aa452433","GROUPID CreateUrlCacheGroup( DWORDdwFlags, LPVOIDlpReserved);",R),
 ("DeleteUrlCacheGroup","aa452434","BOOL DeleteUrlCacheGroup( GROUPIDGroupId, DWORDdwFlags, LPVOIDlpReserved)",R),
 ("FindFirstUrlCacheEntryEx","ms919201","HANDLE FindFirstUrlCacheEntryEx( LPCWSTR lpszUrlSearchPattern,DWORD dwFlags,DWORD dwFilter,GROUPID GroupId,LPINTERNET_CACHE_ENTRY_INFO lpFirstCacheEntryInfo,LPDWORD lpdwFirstCacheEntryInfoBufferSize,LPVOID lpGroupAttributes,LPDWORD pcbGroupAttributes,LPVOID lpReserved);",R),
 ("FindFirstUrlCacheGroup","aa452486","BOOL FindFirstUrlCacheGroup( DWORDdwFlags, DWORDdwFilter, LPVOIDlpSearchCondition, DWORDdwSearchCondition, GROUPID*lpGroupId, LPVOIDlpReserved);",R),
 ("FindNextUrlCacheGroup","aa452487","BOOL FindNextUrlCacheGroup( HANDLEhFind, GROUPID*lpGroupId, LPVOIDlpReserved);",R),
 ("GetUrlCacheGroupAttribute","aa452488","BOOL GetUrlCacheGroupAttribute( GROUPIDgid, DWORDdwFlags, DWORDdwAttributes, LPINTERNET_CACHE_GROUP_INFOlpGroupInfo, LPWORDlpdwGroupInfo, LPVOIDlpReserved);",R),
 ("SetUrlCacheEntryGroup","aa452491","BOOL SetUrlCacheEntryGroup( LPCTSTR lpszUrlName, DWORD dwFlags, GROUPID GroupId, LPBYTE pbGroupAttributes, DWORD cbGroupAttributes, LPVOID lpReserved);",R),
 ("SetUrlCacheGroupAttribute","aa452492","BOOL SetUrlCacheGroupAttribute( GROUPID gid, DWORD dwFlags, DWORD dwAttributes, LPINTERNET_CACHE_GROUP_INFO lpGroupInfo, LPVOID lpReserved);",R),
 ("SetUrlCacheConfigInfo","ms905355","BOOLAPI SetUrlCacheConfigInfoA(LPINTERNET_CACHE_CONFIG_INFOAlpCacheConfigInfo, DWORDdwFieldControl);",R),
]

# declarable signature translation table (unglued C forms)
COOKIE_STATE = [
 ("COOKIE_STATE_UNKNOWN", "0x0"), ("COOKIE_STATE_ACCEPT", "0x1"),
 ("COOKIE_STATE_PROMPT", "0x2"), ("COOKIE_STATE_LEASH", "0x3"),
 ("COOKIE_STATE_DOWNGRADE", "0x4"), ("COOKIE_STATE_REJECT", "0x5"),
]
HTTP_QUERY_VALS = [
 ("HTTP_QUERY_MIME_VERSION", 0), ("HTTP_QUERY_CONTENT_TYPE", 1),
 ("HTTP_QUERY_CONTENT_ID", 3), ("HTTP_QUERY_CONTENT_LANGUAGE", 6),
 ("HTTP_QUERY_ALLOW", 7), ("HTTP_QUERY_PUBLIC", 8),
 ("HTTP_QUERY_DATE", 9), ("HTTP_QUERY_EXPIRES", 10),
 ("HTTP_QUERY_LAST_MODIFIED", 11), ("HTTP_QUERY_URI", 13),
 ("HTTP_QUERY_PRAGMA", 17), ("HTTP_QUERY_VERSION", 18),
 ("HTTP_QUERY_STATUS_CODE", 19), ("HTTP_QUERY_STATUS_TEXT", 20),
 ("HTTP_QUERY_RAW_HEADERS", 21), ("HTTP_QUERY_RAW_HEADERS_CRLF", 22),
 ("HTTP_QUERY_CONNECTION", 23), ("HTTP_QUERY_ACCEPT", 24),
 ("HTTP_QUERY_ACCEPT_CHARSET", 25), ("HTTP_QUERY_ACCEPT_ENCODING", 26),
 ("HTTP_QUERY_ACCEPT_LANGUAGE", 27), ("HTTP_QUERY_AUTHORIZATION", 28),
 ("HTTP_QUERY_CONTENT_ENCODING", 29), ("HTTP_QUERY_FROM", 31),
 ("HTTP_QUERY_IF_MODIFIED_SINCE", 32), ("HTTP_QUERY_LOCATION", 33),
 ("HTTP_QUERY_REFERER", 35), ("HTTP_QUERY_RETRY_AFTER", 36),
 ("HTTP_QUERY_SERVER", 37), ("HTTP_QUERY_TITLE", 38),
 ("HTTP_QUERY_USER_AGENT", 39), ("HTTP_QUERY_WWW_AUTHENTICATE", 40),
 ("HTTP_QUERY_PROXY_AUTHENTICATE", 41), ("HTTP_QUERY_ACCEPT_RANGES", 42),
 ("HTTP_QUERY_SET_COOKIE", 43), ("HTTP_QUERY_COOKIE", 44),
 ("HTTP_QUERY_REQUEST_METHOD", 45), ("HTTP_QUERY_AGE", 48),
 ("HTTP_QUERY_CACHE_CONTROL", 49), ("HTTP_QUERY_CONTENT_BASE", 50),
 ("HTTP_QUERY_CONTENT_LOCATION", 51), ("HTTP_QUERY_CONTENT_MD5", 52),
 ("HTTP_QUERY_CONTENT_RANGE", 53), ("HTTP_QUERY_ETAG", 54),
 ("HTTP_QUERY_HOST", 55), ("HTTP_QUERY_IF_MATCH", 56),
 ("HTTP_QUERY_IF_NONE_MATCH", 57), ("HTTP_QUERY_IF_RANGE", 58),
 ("HTTP_QUERY_IF_UNMODIFIED_SINCE", 59), ("HTTP_QUERY_MAX_FORWARDS", 60),
 ("HTTP_QUERY_PROXY_AUTHORIZATION", 61), ("HTTP_QUERY_RANGE", 62),
 ("HTTP_QUERY_TRANSFER_ENCODING", 63), ("HTTP_QUERY_UPGRADE", 64),
 ("HTTP_QUERY_VARY", 65), ("HTTP_QUERY_VIA", 66),
 ("HTTP_QUERY_WARNING", 67), ("HTTP_QUERY_EXPECT", 68),
 ("HTTP_QUERY_PROXY_CONNECTION", 69),
 ("HTTP_QUERY_UNLESS_MODIFIED_SINCE", 70), ("HTTP_QUERY_MAX", 75),
]

SIGS = {
 "InternetAttemptConnect":"DWORD InternetAttemptConnect(DWORD dwReserved)",
"InternetConfirmZoneCrossing":"DWORD InternetConfirmZoneCrossing(HWND hWnd, LPTSTR szUrlPrev, LPTSTR szUrlNew, BOOL bPost)",
 "InternetCheckConnection":"BOOL InternetCheckConnection(LPCTSTR lpszUrl, DWORD dwFlags, DWORD dwReserved)",
 "InternetCombineUrl":"BOOL WINAPI InternetCombineUrl(LPCTSTR lpszBaseUrl, LPCTSTR lpszRelativeUrl, LPTSTR lpszBuffer, LPDWORD lpdwBufferLength, DWORD dwFlags)",
 "InternetCreateUrl":"BOOL WINAPI InternetCreateUrl(LPURL_COMPONENTS lpUrlComponents, DWORD dwFlags, LPTSTR lpszUrl, LPDWORD lpdwUrlLength)",
 "InternetCrackUrl":"BOOL WINAPI InternetCrackUrl(LPCTSTR lpszUrl, DWORD dwUrlLength, DWORD dwFlags, LPURL_COMPONENTS lpUrlComponents)",
 "InternetEnumPerSiteCookieDecisionA":"BOOL InternetEnumPerSiteCookieDecisionA(LPSTR pszSiteName, unsigned long *pcSiteNameSize, unsigned long *pdwDecision, unsigned long dwIndex)",
 "InternetEnumPerSiteCookieDecisionW":"BOOL InternetEnumPerSiteCookieDecisionW(LPSTR pszSiteName, unsigned long *pcSiteNameSize, unsigned long *pdwDecision, unsigned long dwIndex)",
 "InternetGetConnectedState":"BOOL InternetGetConnectedState(LPDWORD lpdwFlags, DWORD dwReserved)",
 "InternetGetConnectedStateEx":"BOOL InternetGetConnectedStateEx(LPDWORD lpdwFlags, LPTSTR lpszConnectionName, DWORD dwNameLen, DWORD dwReserved)",
 "InternetGetCookie":"BOOL InternetGetCookie(LPCTSTR lpszUrl, LPCTSTR lpszCookieName, LPSTR lpCookieData, LPDWORD lpdwSize)",
 "InternetGetLastResponseInfo":"BOOL WINAPI InternetGetLastResponseInfo(LPDWORD lpdwError, LPTSTR lpszBuffer, LPDWORD lpdwBufferLength)",
 "InternetGetPerSiteCookieDecisionA":"BOOL InternetGetPerSiteCookieDecisionA(LPCSTR pchHostName, unsigned long *pResult)",
 "InternetGetPerSiteCookieDecisionW":"BOOL InternetGetPerSiteCookieDecisionW(LPCSTR pchHostName, unsigned long *pResult)",
 "InternetGoOnline":"BOOL InternetGoOnline(LPTSTR lpszURL, HWND hwndParent, DWORD dwReserved)",
 "InternetSetCookie":"BOOL InternetSetCookie(LPCTSTR lpszUrl, LPCTSTR lpszCookieName, LPCTSTR lpszCookieData)",
 "InternetSetCookieEx":"BOOL InternetSetCookieEx(LPCTSTR lpszUrl, LPCTSTR lpszCookieName, LPCTSTR lpszCookieData, DWORD dwFlags, DWORD_PTR dwReserved)",
 "InternetSetPerSiteCookieDecisionA":"BOOL InternetSetPerSiteCookieDecisionA(LPCSTR pchHostName, DWORD dwDecision)",
 "InternetSetPerSiteCookieDecisionW":"BOOL InternetSetPerSiteCookieDecisionW(LPCSTR pchHostName, DWORD dwDecision)",
 "InternetTimeFromSystemTime":"BOOL WINAPI InternetTimeFromSystemTime(const SYSTEMTIME *pst, DWORD dwRFC, LPTSTR lpszTime, DWORD cbTime)",
 "InternetTimeToSystemTime":"BOOL InternetTimeToSystemTime(LPCTSTR lpszTime, SYSTEMTIME *pst, DWORD dwReserved)",
 "InternetUnlockRequestFile":"BOOL InternetUnlockRequestFile(HANDLE hLockRequestInfo)",
 "CommitUrlCacheEntry":"BOOL CommitUrlCacheEntry(LPCTSTR lpszUrlName, LPCTSTR lpszLocalFileName, FILETIME ExpireTime, FILETIME LastModifiedTime, DWORD CacheEntryType, LPBYTE lpHeaderInfo, DWORD dwHeaderSize, LPCTSTR lpszFileExtension, DWORD dwReserved)",
 "CreateUrlCacheEntry":"BOOL CreateUrlCacheEntry(LPCTSTR lpszUrlName, DWORD dwExpectedFileSize, LPCTSTR lpszFileExtension, LPSTR lpszFileName, DWORD dwReserved)",
 "DeleteUrlCacheEntry":"BOOL DeleteUrlCacheEntry(LPCTSTR lpszUrlName)",
 "FindCloseUrlCache":"BOOL FindCloseUrlCache(HANDLE hEnumHandle)",
 "FindNextUrlCacheEntry":"BOOL FindNextUrlCacheEntry(HANDLE hEnumHandle, LPINTERNET_CACHE_ENTRY_INFO lpNextCacheEntryInfo, LPDWORD lpdwNextCacheEntryInfoBufferSize)",
 "FindNextUrlCacheEntryEx":"BOOL WINAPI FindNextUrlCacheEntryEx(HANDLE hEnumHandle, LPINTERNET_CACHE_ENTRY_INFO lpFirstCacheEntryInfo, LPDWORD lpdwFirstCacheEntryInfoBufferSize, LPVOID lpGroupAttributes, LPDWORD pcbGroupAttributes, LPVOID lpReserved)",
 "GetUrlCacheEntryInfo":"BOOL GetUrlCacheEntryInfo(LPCTSTR lpszUrlName, LPINTERNET_CACHE_ENTRY_INFO lpCacheEntryInfo, LPDWORD lpdwCacheEntryInfoBufferSize)",
 "GetUrlCacheEntryInfoEx":"BOOL GetUrlCacheEntryInfoEx(LPCSTR lpszUrl, LPINTERNET_CACHE_ENTRY_INFO lpCacheEntryInfo, LPDWORD lpdwCacheEntryInfoBufSize, LPSTR lpszReserved, LPDWORD lpdwReserved, LPVOID lpReserved, DWORD dwFlags)",
 "ReadUrlCacheEntryStream":"BOOL ReadUrlCacheEntryStream(HANDLE hUrlCacheStream, DWORD dwLocation, LPVOID lpBuffer, LPDWORD lpdwLen, DWORD dwReserved)",
 "RetrieveUrlCacheEntryStream":"HANDLE RetrieveUrlCacheEntryStream(LPCTSTR lpszUrlName, LPINTERNET_CACHE_ENTRY_INFO lpCacheEntryInfo, LPDWORD lpdwCacheEntryInfoBufferSize, BOOL fRandomRead, DWORD dwReserved)",
 "RetrieveUrlCacheEntryFile":"BOOL RetrieveUrlCacheEntryFile(LPCTSTR lpszUrlName, LPINTERNET_CACHE_ENTRY_INFO lpCacheEntryInfo, LPDWORD lpdwCacheEntryInfoBufferSize, DWORD dwReserved)",
 "SetUrlCacheEntryInfo":"BOOL SetUrlCacheEntryInfo(LPCSTR lpszUrlName, LPINTERNET_CACHE_ENTRY_INFO lpCacheEntryInfo, DWORD dwFieldControl)",
 "UnlockUrlCacheEntryFile":"BOOL UnlockUrlCacheEntryFile(LPCSTR lpszUrlName, DWORD dwReserved)",
 "UnlockUrlCacheEntryStream":"BOOL UnlockUrlCacheEntryStream(HANDLE hUrlCacheStream, DWORD dwReserved)",
}

HTTP_STATUS = [
 ("HTTP_STATUS_CONTINUE",100),("HTTP_STATUS_SWITCH_PROTOCOLS",101),("HTTP_STATUS_OK",200),
 ("HTTP_STATUS_CREATED",201),("HTTP_STATUS_ACCEPTED",202),("HTTP_STATUS_PARTIAL",203),
 ("HTTP_STATUS_NO_CONTENT",204),("HTTP_STATUS_RESET_CONTENT",205),("HTTP_STATUS_PARTIAL_CONTENT",206),
 ("HTTP_STATUS_AMBIGUOUS",300),("HTTP_STATUS_MOVED",301),("HTTP_STATUS_REDIRECT",302),
 ("HTTP_STATUS_REDIRECT_METHOD",303),("HTTP_STATUS_NOT_MODIFIED",304),("HTTP_STATUS_USE_PROXY",305),
 ("HTTP_STATUS_REDIRECT_KEEP_VERB",307),("HTTP_STATUS_BAD_REQUEST",400),("HTTP_STATUS_DENIED",401),
 ("HTTP_STATUS_FORBIDDEN",403),("HTTP_STATUS_NOT_FOUND",404),("HTTP_STATUS_BAD_METHOD",405),
 ("HTTP_STATUS_NONE_ACCEPTABLE",406),("HTTP_STATUS_PROXY_AUTH_REQ",407),("HTTP_STATUS_REQUEST_TIMEOUT",408),
 ("HTTP_STATUS_CONFLICT",409),("HTTP_STATUS_GONE",410),("HTTP_STATUS_LENGTH_REQUIRED",411),
 ("HTTP_STATUS_PRECOND_FAILED",412),("HTTP_STATUS_REQUEST_TOO_LARGE",413),("HTTP_STATUS_URI_TOO_LONG",414),
 ("HTTP_STATUS_UNSUPPORTED_MEDIA",415),("HTTP_STATUS_RETRY_WITH",449),("HTTP_STATUS_SERVER_ERROR",500),
 ("HTTP_STATUS_NOT_SUPPORTED",501),("HTTP_STATUS_BAD_GATEWAY",502),("HTTP_STATUS_SERVICE_UNAVAIL",503),
 ("HTTP_STATUS_GATEWAY_TIMEOUT",504),("HTTP_STATUS_VERSION_NOT_SUP",505),
]

def flaglist(pid, pref):
    txt = page_text(pid)
    return sorted(set(re.findall(r'\b' + pref + r'\w+', txt)))

L = []
A = L.append
A('''/*
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
''')
for name, val in HTTP_STATUS:
    A(f"#define {name:<36} {val}")
A("")
A("/* ms918353 \"InternetCookieState\" -- enum print with values: */")
A("typedef enum InternetCookieState {")
for name, val in COOKIE_STATE:
    A(f"    {name} = {val},")
A("    COOKIE_STATE_MAX = COOKIE_STATE_REJECT")
A("} InternetCookieState;")
A("")
A("/* ms906348 \"HTTP Response Headers\" -- indices printed in parens. */")
A("/* HTTP_QUERY_TITLE is on this page but absent from the ms918842   */")
A("/* name list; the five ms918842-only modifiers stay value-less:     */")
A("/* CONTENT_TRANSFER_ENCODING, CUSTOM, FLAG_NUMBER,                  */")
A("/* FLAG_REQUEST_HEADERS, FLAG_SYSTEMTIME.                           */")
for name, val in HTTP_QUERY_VALS:
    A(f"#define {name:<38} {val}")
A("")
A("/* ------------------------------------------------------------------ */")
A("/* Held structures / types (used by prints, never defined on any CE")
A(" * page -- full-corpus typedef search, M92):")
A(" *   URL_COMPONENTS (ms918864): embeds INTERNET_PORT nPort by value.")
A(" *   INTERNET_AUTH_NOTIFY_DATA (ms918341): print `typedef struct")
A(" *     {DWORDcbStruct;DWORDdwOptions;PFN_PUTHNOTIFYpfnNotify;")
A(" *     DWORD_PTRdwContext;} INTERNET_AUTH_NOTIFY_DATA;` -- the callback")
A(" *     type is printed \"PFN_PUTHNOTIFY\" (archive typo for")
A(" *     PFN_AUTHNOTIFY) and has no page of its own.")
A(" *   INTERNET_STATUS_CALLBACK (ms918386): print `typedef void")
A(" *     (CALLBACK* INTERNET_STATUS_CALLBACK) (HINTERNEThInternet,")
A(" *     DWORD_PTRdwContext,DWORDdwInternetStatus,LPVOID")
A(" *     lpvStatusInformation,DWORDdwStatusInformat...` -- HINTERNET by")
A(" *     value in the callback shape; recorded.")
A(" *   INTERNET_STATE_CONNECTED / _ONLINE / _DISCONNECTED / _OFFLINE /")
A(" *     _DISCONNECTED_BY_USER / _OFFLINE_USER / _IDLE / _BUSY")
A(" *     (ms918352 value table): names recorded, no values printed.")
A(" * ------------------------------------------------------------------ */")
A("")
A("/* ------------------------------------------------------------------ */")
A("/* Flag name lists (value tables print NO values -- names recorded    */")
A("/* only, the WM_SIDESHOW_* M82 precedent).                            */")
A("/* ------------------------------------------------------------------ */")
A("")
for pid, pref, label in (
        ('aa452096', 'INTERNET_FLAG_', 'aa452096 "API Flags"'),
        ('ms918831', 'INTERNET_OPTION_', 'ms918831 "Option Flags"'),
        ('ms918842', 'HTTP_QUERY_', 'ms918842 "Query Info Flags"'),
        ('ms918835', 'PRIVACY_', 'ms918835 "Privacy Flags"')):
    names = flaglist(pid, pref)
    A(f"/* {label}: {len(names)} names, no values printed:")
    line = " *   "
    for n in names:
        if len(line) + len(n) + 1 > 74:
            A(line.rstrip())
            line = " *   "
        line += n + " "
    if line.strip():
        A(line.rstrip())
    A(" */")
    A("")
A("/* ------------------------------------------------------------------ */")
A("/* Functions -- declared (parameter types all resolve).               */")
A("/* ------------------------------------------------------------------ */")
A("")
for name, pid, print_, kind in FUNCS:
    if kind != D:
        continue
    A(f"/* {pid} \"{name}\": print `{print_}`")
    extra = ""
    if name == "FindNextUrlCacheEntryEx":
        extra = " (print \"BOOLAPI\" read as BOOL WINAPI)"
    elif name == "InternetCrackUrl":
        extra = " (glued \"WINAPIInternetCrackUrl\" split)"
    elif name == "InternetGetConnectedStateEx":
        extra = " (glued \"BOOLInternetGetConnectedStateEx\" split)"
    elif name == "RetrieveUrlCacheEntryStream":
        extra = " (print drops the comma between lpszUrlName and the info pointer)"
    elif name == "RetrieveUrlCacheEntryFile":
        extra = " (glued \"BOOLRetrieveUrlCacheEntryFile\" split)"
    elif name == "SetUrlCacheEntryInfo":
        extra = " (glued \"BOOLSetUrlCacheEntryInfo\" split)"
    elif name == "UnlockUrlCacheEntryFile":
        extra = " (glued \"BOOLUnlockUrlCacheEntryFile\" split)"
    elif name == "UnlockUrlCacheEntryStream":
        extra = " (print spells the handle \"LHANDLE\" -- HANDLE)"
    A(f" *{extra}. */")
    A(f"AKARI_CE_IMPORT {SIGS[name]}")
    pad = " " * 24
    A(f"{pad}AKARI_CE_NAME({name});")
    A("")
A("/* ------------------------------------------------------------------ */")
A("/* Functions -- recorded (HINTERNET / GROUPID / INTERNET_PORT /        */")
A("/* INTERNET_CACHE_GROUP_INFO / INTERNET_CACHE_CONFIG_INFOA by value).  */")
A("/* ------------------------------------------------------------------ */")
A("")
for name, pid, print_, kind in FUNCS:
    if kind != R:
        continue
    A(f"/* {pid} \"{name}\": `{print_}` */")
A("")
A('''#ifdef __cplusplus
}
#endif

#endif /* AKARI_WININET_H */
''')
open('include/Wininet.h', 'w').write('\n'.join(L))
print('Wininet.h:', len(FUNCS), 'rows,', sum(1 for f in FUNCS if f[3]==D), 'declared,', sum(1 for f in FUNCS if f[3]==R), 'recorded')
