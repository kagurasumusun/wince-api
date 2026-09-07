/*
 * notify.h -- user notification API for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  The Notify Reference book of the CE 5.0 GWES documentation is
 * the source book; its pages print Header: Notify.h and Link Library:
 * Coredll.lib, so the export rows feed def/coredll-doc.def.
 *
 * Windows CE is Unicode-only: the text members below are wide strings
 * exactly as the pages type them (TCHAR* / WCHAR* on a Unicode build).
 */

#ifndef AKARI_NOTIFY_H
#define AKARI_NOTIFY_H

#include "windef.h"
#include "winbase.h"   /* SYSTEMTIME (winbase.h) for time triggers */

#ifdef __cplusplus
extern "C" {
#endif

/* ms908083 "CE_NOTIFICATION_TRIGGER": the event (or time period) that
 * activates a notification.  CE 2.12+; Notify.h.  dwType selects among
 * CNT_EVENT / CNT_TIME / CNT_PERIOD / CNT_CLASSICTIME. */
typedef struct UserNotificationTrigger {
    DWORD      dwSize;
    DWORD      dwType;
    DWORD      dwEvent;         /* NOTIFICATION_EVENT_* when dwType is CNT_EVENT */
    WCHAR     *lpszApplication;
    WCHAR     *lpszArguments;
    SYSTEMTIME stStartTime;
    SYSTEMTIME stEndTime;
} CE_NOTIFICATION_TRIGGER, *PCE_NOTIFICATION_TRIGGER;

/* ms908106 "CE_USER_NOTIFICATION": user-notification dialog/sound
 * preferences.  CE 2.12+; Notify.h.  ActionFlags combines the PUN_*
 * flags. */
typedef struct UserNotificationType {
    DWORD  ActionFlags;       /* PUN_LED / PUN_VIBRATE / PUN_DIALOG / ... */
    TCHAR *pwszDialogTitle;
    TCHAR *pwszDialogText;
    TCHAR *pwszSound;
    DWORD  nMaxSound;
    DWORD  dwReserved;
} CE_USER_NOTIFICATION, *PCE_USER_NOTIFICATION;

/* ms908082 "CE_NOTIFICATION_INFO_HEADER": header of the buffer filled by
 * CeGetUserNotification.  CE 2.12+; Notify.h.  dwStatus is CNS_SIGNALLED
 * when the notification is active. */
typedef struct UserNotificationInfoHeader {
    HANDLE                    hNotification;
    DWORD                     dwStatus;
    CE_NOTIFICATION_TRIGGER  *pcent;
    CE_USER_NOTIFICATION     *pceun;
} CE_NOTIFICATION_INFO_HEADER, *PCE_NOTIFICATION_INFO_HEADER;

/* Notify Reference functions (Header Notify.h; Link Library
 * Coredll.lib). */
AKARI_CE_IMPORT BOOL   CeClearUserNotification(HANDLE hNotification) AKARI_CE_NAME(CeClearUserNotification);              /* ms908074 */
AKARI_CE_IMPORT BOOL   CeGetUserNotification(HANDLE hNotification,                 /* ms908076 */
                             DWORD cBufferSize, LPDWORD pcBytesNeeded,
                             LPBYTE pBuffer) AKARI_CE_NAME(CeGetUserNotification);
AKARI_CE_IMPORT BOOL   CeGetUserNotificationHandles(HANDLE* rghNotifications,      /* ms908077 */
                                    DWORD cHandles,
                                    LPDWORD pcHandlesNeeded) AKARI_CE_NAME(CeGetUserNotificationHandles);
AKARI_CE_IMPORT BOOL   CeGetUserNotificationPreferences(HWND hWndParent,           /* ms908078 */
                                        PCE_USER_NOTIFICATION
                                            lpNotification) AKARI_CE_NAME(CeGetUserNotificationPreferences);
AKARI_CE_IMPORT BOOL   CeHandleAppNotifications(TCHAR* pwszAppName) AKARI_CE_NAME(CeHandleAppNotifications);               /* ms908079 */
AKARI_CE_IMPORT BOOL   CeRunAppAtEvent(TCHAR* pwszAppName, LONG lWhichEvent) AKARI_CE_NAME(CeRunAppAtEvent);      /* ms908102 */
AKARI_CE_IMPORT BOOL   CeRunAppAtTime(TCHAR* pwszAppName, SYSTEMTIME* lpTime) AKARI_CE_NAME(CeRunAppAtTime);     /* ms908103 */
AKARI_CE_IMPORT HANDLE CeSetUserNotification(HANDLE hNotification, TCHAR* pwszAppName,
                             SYSTEMTIME* lpTime,                   /* ms908104 */
                             PCE_USER_NOTIFICATION lpUserNotification) AKARI_CE_NAME(CeSetUserNotification);
AKARI_CE_IMPORT HANDLE CeSetUserNotificationEx(HANDLE hNotification,               /* ms908105 */
                               CE_NOTIFICATION_TRIGGER* pcnt,
                               CE_USER_NOTIFICATION* pceun) AKARI_CE_NAME(CeSetUserNotificationEx);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_NOTIFY_H */
