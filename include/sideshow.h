/* sideshow.h -- Windows Embedded CE SideShow gadget-manager API.
 *
 * Source pages: the SideShow book (Windows Embedded CE 6.0 /
 * NavReady 2009-era pages, tools/manifests/sideshow-book.manifest,
 * 51 leaves).  The Requirements rows print "Header: sideshow.h /
 * Library: sideshowapi.lib" in the colon-less table form (the row
 * parser records them empty; noted here) -> def/sideshowapi-doc.def.
 * OS rows: "Windows Embedded CE Windows CE 5.0, Windows Embedded
 * NavReady 2009" (the gadget manager also exists on the CE 5.0
 * NavReady profile).
 *
 * 22 of the 25 SideShowMgr_* pages print full prototypes and are
 * declared; SideShowMgr_FindItemClose / _ForceConnect /
 * _ForceDisconnect print no return type and are recorded.  The 17
 * WM_SIDESHOW_* message pages publish wParam/lParam semantics but
 * no numeric values -- names recorded.  See docs/inventory.md M82.
 */

#ifndef AKARI_SIDESHOW_H
#define AKARI_SIDESHOW_H

#include "Windef.h"    /* BOOL, DWORD, UINT, INT, BYTE, WCHAR, HWND, HANDLE */
#include "Winnt.h"     /* GUID */
#include "Winbase.h"   /* FILETIME */

/* --- Functions (sideshowapi.lib). ------------------------------- */
/* cc664381 "SideShowMgr_FindFirstItem": print `HANDLE SideShowMgr_FindFirstItem( UINT uiGadget, UINT* lpFirstItemSize )` */
AKARI_CE_IMPORT HANDLE SideShowMgr_FindFirstItem(UINT uiGadget, UINT * lpFirstItemSize)
                    AKARI_CE_NAME(SideShowMgr_FindFirstItem);

/* cc700961 "SideShowMgr_FindNextItem": print `BOOL SideShowMgr_FindNextItem( HANDLE hSearch, UINT* lpItemId, BYTE* lpBuffer, UINT* lpuiItemSize, UINT* lpNextItemSize )` */
AKARI_CE_IMPORT BOOL SideShowMgr_FindNextItem(HANDLE hSearch, UINT * lpItemId, BYTE * lpBuffer, UINT * lpuiItemSize, UINT * lpNextItemSize)
                    AKARI_CE_NAME(SideShowMgr_FindNextItem);

/* cc664367 "SideShowMgr_GetAvailableUserNames": print `BOOL SideShowMgr_GetAvailableUserNames( WCHAR* wcNames, DWORD dwAllocatedCharacters, INT* iCurrentUserIndex )` */
AKARI_CE_IMPORT BOOL SideShowMgr_GetAvailableUserNames(WCHAR * wcNames, DWORD dwAllocatedCharacters, INT * iCurrentUserIndex)
                    AKARI_CE_NAME(SideShowMgr_GetAvailableUserNames);

/* cc664369 "SideShowMgr_GetCurrentCacheSize": print `DWORD SideShowMgr_GetCurrentCacheSize()` (empty parens -> void) */
AKARI_CE_IMPORT DWORD SideShowMgr_GetCurrentCacheSize(void)
                    AKARI_CE_NAME(SideShowMgr_GetCurrentCacheSize);

/* cc664397 "SideShowMgr_GetGadgetCount": print `int SideShowMgr_GetGadgetCount()` (empty parens -> void) */
AKARI_CE_IMPORT int SideShowMgr_GetGadgetCount(void)
                    AKARI_CE_NAME(SideShowMgr_GetGadgetCount);

/* cc664402 "SideShowMgr_GetGadgetInfo": print `BOOL SideShowMgr_GetGadgetInfo( UINT* lpuiGadgetId, WCHAR* wcName, UINT uiNameLen, GUID* pguidEndPoint, BOOL* lpfOnlineOnly, BYTE* lpbIcon48, UINT uiIcon48, BYTE* lpbIcon32, UINT uiIcon32, BYTE* lpbIcon16, UINT uiIcon16 )` */
AKARI_CE_IMPORT BOOL SideShowMgr_GetGadgetInfo(UINT * lpuiGadgetId, WCHAR * wcName, UINT uiNameLen, GUID * pguidEndPoint, BOOL * lpfOnlineOnly, BYTE * lpbIcon48, UINT uiIcon48, BYTE * lpbIcon32, UINT uiIcon32, BYTE * lpbIcon16, UINT uiIcon16)
                    AKARI_CE_NAME(SideShowMgr_GetGadgetInfo);

/* cc664224 "SideShowMgr_GetGadgetInfoSizes": print `BOOL SideShowMgr_GetGadgetInfoSizes( UINT* lpuiNameLen, UINT* lpuiIcon48, UINT* lpuiIcon32, UINT* lpuiIcon16 )` */
AKARI_CE_IMPORT BOOL SideShowMgr_GetGadgetInfoSizes(UINT * lpuiNameLen, UINT * lpuiIcon48, UINT * lpuiIcon32, UINT * lpuiIcon16)
                    AKARI_CE_NAME(SideShowMgr_GetGadgetInfoSizes);

/* cc664399 "SideShowMgr_GetGadgetOrder": print `int SideShowMgr_GetGadgetOrder( UINT* lpuiGadgetIds, int iGadgetIdBufferSize )` */
AKARI_CE_IMPORT int SideShowMgr_GetGadgetOrder(UINT * lpuiGadgetIds, int iGadgetIdBufferSize)
                    AKARI_CE_NAME(SideShowMgr_GetGadgetOrder);

/* cc664368 "SideShowMgr_GetGuidsFromGadgetId": print `BOOL SideShowMgr_GetGuidsFromGadgetId( UINT uiGadgetId, GUID* pguidGadget, GUID* pguidEndPoint )` */
AKARI_CE_IMPORT BOOL SideShowMgr_GetGuidsFromGadgetId(UINT uiGadgetId, GUID * pguidGadget, GUID * pguidEndPoint)
                    AKARI_CE_NAME(SideShowMgr_GetGuidsFromGadgetId);

/* cc700960 "SideShowMgr_GetItemData": print `BOOL SideShowMgr_GetItemData( UINT uiGadgetId, DWORD dwItemId, BYTE* lpData, DWORD dwDataSize )` */
AKARI_CE_IMPORT BOOL SideShowMgr_GetItemData(UINT uiGadgetId, DWORD dwItemId, BYTE * lpData, DWORD dwDataSize)
                    AKARI_CE_NAME(SideShowMgr_GetItemData);

/* cc664231 "SideShowMgr_GetItemDataSize": print `DWORD SideShowMgr_GetItemDataSize( UINT uiGadgetId, DWORD dwItemId )` */
AKARI_CE_IMPORT DWORD SideShowMgr_GetItemDataSize(UINT uiGadgetId, DWORD dwItemId)
                    AKARI_CE_NAME(SideShowMgr_GetItemDataSize);

/* cc664227 "SideShowMgr_GetItemDataSizeTimeout": print `DWORD SideShowMgr_GetItemDataSizeTimeout( UINT uiGadgetId, DWORD dwItemId, DWORD dwTimeout )` */
AKARI_CE_IMPORT DWORD SideShowMgr_GetItemDataSizeTimeout(UINT uiGadgetId, DWORD dwItemId, DWORD dwTimeout)
                    AKARI_CE_NAME(SideShowMgr_GetItemDataSizeTimeout);

/* cc700970 "SideShowMgr_GetNotificationInfo": print `BOOL SideShowMgr_GetNotificationInfo( UINT* lpuiGadgetId, UINT* lpuiNotificationId, FILETIME* lpftExpirationTime, WCHAR* wcTitle, UINT uiTitle, WCHAR* wcText, UINT uiText, BYTE* lpbIconData, UINT uiIconData )` */
AKARI_CE_IMPORT BOOL SideShowMgr_GetNotificationInfo(UINT * lpuiGadgetId, UINT * lpuiNotificationId, FILETIME * lpftExpirationTime, WCHAR * wcTitle, UINT uiTitle, WCHAR * wcText, UINT uiText, BYTE * lpbIconData, UINT uiIconData)
                    AKARI_CE_NAME(SideShowMgr_GetNotificationInfo);

/* cc664400 "SideShowMgr_GetNotificationInfoSizes": print `BOOL SideShowMgr_GetNotificationInfoSizes( UINT* lpuiTitle, UINT* lpuiText, UINT* lpuiIcon )` */
AKARI_CE_IMPORT BOOL SideShowMgr_GetNotificationInfoSizes(UINT * lpuiTitle, UINT * lpuiText, UINT * lpuiIcon)
                    AKARI_CE_NAME(SideShowMgr_GetNotificationInfoSizes);

/* cc664373 "SideShowMgr_GetSizeOfAvailableUserNames": print `DWORD SideShowMgr_GetSizeOfAvailableUserNames()` (empty parens -> void) */
AKARI_CE_IMPORT DWORD SideShowMgr_GetSizeOfAvailableUserNames(void)
                    AKARI_CE_NAME(SideShowMgr_GetSizeOfAvailableUserNames);

/* cc700962 "SideShowMgr_IsServiceRunning": print `BOOL SideShowMgr_IsServiceRunning()` (empty parens -> void) */
AKARI_CE_IMPORT BOOL SideShowMgr_IsServiceRunning(void)
                    AKARI_CE_NAME(SideShowMgr_IsServiceRunning);

/* cc664228 "SideShowMgr_SendApplicationEvent": print `BOOL SideShowMgr_SendApplicationEvent( UINT uiGadgetId, UINT uiEventType, BYTE* lpEventData, DWORD dwEventDataSize )` */
AKARI_CE_IMPORT BOOL SideShowMgr_SendApplicationEvent(UINT uiGadgetId, UINT uiEventType, BYTE * lpEventData, DWORD dwEventDataSize)
                    AKARI_CE_NAME(SideShowMgr_SendApplicationEvent);

/* cc664392 "SideShowMgr_SetMaximumCacheSize": print `BOOL SideShowMgr_SetMaximumCacheSize( DWORD size )` */
AKARI_CE_IMPORT BOOL SideShowMgr_SetMaximumCacheSize(DWORD size)
                    AKARI_CE_NAME(SideShowMgr_SetMaximumCacheSize);

/* cc664223 "SideShowMgr_Start": print `BOOL SideShowMgr_Start( HWND hShellNotificationWindow, UINT uiGuidCount, GUID* pguidContent )` */
AKARI_CE_IMPORT BOOL SideShowMgr_Start(HWND hShellNotificationWindow, UINT uiGuidCount, GUID * pguidContent)
                    AKARI_CE_NAME(SideShowMgr_Start);

/* cc664220 "SideShowMgr_Stop": print `BOOL SideShowMgr_Stop()` (empty parens -> void) */
AKARI_CE_IMPORT BOOL SideShowMgr_Stop(void)
                    AKARI_CE_NAME(SideShowMgr_Stop);

/* cc700964 "SideShowMgr_UserChangeRequest": print `BOOL SideShowMgr_UserChangeRequest( WCHAR* wcUserName )` */
AKARI_CE_IMPORT BOOL SideShowMgr_UserChangeRequest(WCHAR * wcUserName)
                    AKARI_CE_NAME(SideShowMgr_UserChangeRequest);

/* cc664225 "SideShowMgr_UserChangeRequestCch": print `BOOL SideShowMgr_UserChangeRequestCch( WCHAR* wcUserName, DWORD dwAllocatedCharacters )` */
AKARI_CE_IMPORT BOOL SideShowMgr_UserChangeRequestCch(WCHAR * wcUserName, DWORD dwAllocatedCharacters)
                    AKARI_CE_NAME(SideShowMgr_UserChangeRequestCch);

/* --- Recorded (print lacks the return type). -------------------- */
/* cc700959 "SideShowMgr_FindItemClose": `SideShowMgr_FindItemClose( HANDLE hSearch )` */
/* cc700967 "SideShowMgr_ForceConnect": `SideShowMgr_ForceConnect()` */
/* cc664383 "SideShowMgr_ForceDisconnect": `SideShowMgr_ForceDisconnect()` */

/* --- Recorded WM_SIDESHOW_* messages (names only). --------------
 *   WM_SIDESHOW_ADD_GADGET(cc664370),
 *   WM_SIDESHOW_ADD_NOTIFICATION(cc664382),
 *   WM_SIDESHOW_CACHE_ITEMS_CLEARED(cc664394),
 *   WM_SIDESHOW_CACHE_ITEM_ADDED(cc664226),
 *   WM_SIDESHOW_CACHE_ITEM_DELETED(cc664385),
 *   WM_SIDESHOW_CACHE_ITEM_UPDATED(cc664398),
 *   WM_SIDESHOW_CONNECTED(cc664376),
 *   WM_SIDESHOW_CONNECTION_RESULT(cc700956),
 *   WM_SIDESHOW_DELETE_ALL_GADGETS(cc664396),
 *   WM_SIDESHOW_DELETE_ALL_NOTIFICATIONS(cc664219),
 *   WM_SIDESHOW_DELETE_GADGET(cc700966),
 *   WM_SIDESHOW_DELETE_NOTIFICATION(cc664390),
 *   WM_SIDESHOW_DISCONNECTED(cc700957),
 *   WM_SIDESHOW_SELECT_USER(cc664221),
 *   WM_SIDESHOW_SERVICE_STOPPING(cc664393),
 *   WM_SIDESHOW_SET_GADGET_ORDER(cc664374),
 *   WM_SIDESHOW_USER_CHANGED(cc664232)
 */

#endif /* AKARI_SIDESHOW_H */
