/*
 * pm.h -- device power states for Windows CE (Pm.h layer).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  The declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * page in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * ID).  Source book: CE 5.0 "CEDDK Dynamic-Link Library" dependency
 * (tools/manifests/ceddk-dep.manifest, fetched M57; CE 6.0 twin
 * ee497766 in build/pages6 cross-read).  OS Versions: "Windows CE .NET
 * 4.0 and later".
 *
 * The page prints no Link Library row, so no def is generated.
 */

#ifndef AKARI_PM_H
#define AKARI_PM_H

#include "Windef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* aa447663 "CEDEVICE_POWER_STATE": values printed (implicit
 * successors: D1..D4 follow D0 = 0; PwrDeviceMaximum follows D4). */
typedef enum _CEDEVICE_POWER_STATE {
    PwrDeviceUnspecified = -1,
    D0 = 0,
    D1,
    D2,
    D3,
    D4,
    PwrDeviceMaximum
} CEDEVICE_POWER_STATE, *PCEDEVICE_POWER_STATE;

/* ------------------------------------------------------------------
 * Book surface: powerman (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms890485 Activity Timer Behavior */
/* ms890491 Activity Timer Events */
/* ms890495 Activity Timer Resets */
/* ms890509 Activity Timer Time-outs and the Power Control Panel Utility */
/* ms890589 Application Suspend Time-outs */
/* aa448265 Best Practices for Faster Suspend Times */
/* ms891075 Class-Qualified Device Names */
/* aa447476 Device and System Power State Names */
/* aa447460 Device Control IOCTLs */
/* aa447464 Device Initialization Responsibilities */
/* aa447472 Device Power Capabilities */
/* aa447471 Device Power States */
/* aa447475 Device State D3 and System Wakeup */
/* aa447523 Driver-to-Power Manager APIs */
/* ms892149 Example System Power States */
/* ms892164 GWES Suspend Time-outs */
/* ms895488 How to Add Power Management to a Device Driver */
/* ms892451 IOCTL_POWER_SET Request Processing */
/* ms892548 Notification Interface */
/* ms892558 Other Power Management APIs */
/* aa447557 Power Management Implementation in Drivers */
/* ms894041 Power Management Implementation in Stream Interface Drivers */
/* aa447560 Power Manager and ACPI/APM */
/* aa447563 Power Manager Suspend Time-outs */
/* aa447565 Power Requirements on Devices */
/* aa447552 Power-Manageable Device Drivers */
/* ms894011 Self-Management Example */
/* ms894050 Suspend and Resume Handling */
/* ms894051 Suspend and Resume Power Callbacks */
/* ms894057 System Power State Setting */
/* ms894059 System Power State to Device Power State Mapping */
/* ms894060 System Power State Transitions */

/* ------------------------------------------------------------------
 * Book surface: powerman (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms919667 POWER_BROADCAST (page print, compiled) */
typedef struct _POWER_BROADCAST {
    DWORD Message;
    DWORD Flags;
    DWORD Length;
    WCHAR SystemPowerState[1];
} POWER_BROADCAST, *PPOWER_BROADCAST;
/* ms919670 POWER_BROADCAST_POWER_INFO (page print, compiled) */
typedef struct _POWER_BROADCAST_POWER_INFO {
    DWORD dwBatteryLifeTime;
    DWORD dwBatteryFullLifeTime;
    DWORD dwBackupBatteryLifeTime;
    DWORD dwBackupBatteryFullLifeTime;
    BYTE bACLineStatus;
    BYTE bBatteryFlag;
    BYTE bBatteryLifePercent;
    BYTE bBackupBatteryFlag;
    BYTE bBackupBatteryLifePercent;
} POWER_BROADCAST_POWER_INFO, *PPOWER_BROADCAST_POWER_INFO;
/* ms919672 POWER_CAPABILITIES (page print, compiled) */
typedef struct _POWER_CAPABILITIES {
    UCHAR DeviceDx;
    UCHAR WakeFromDx;
    UCHAR InrushDx;
    DWORD Power[5];
    DWORD Latency[5];
    DWORD Flags;
} POWER_CAPABILITIES, *PPOWER_CAPABILITIES;
/* ms919681 POWER_RELATIONSHIP (page print, compiled) */
typedef struct _POWER_RELATIONSHIP {
    HANDLE hParent;
    LPCWSTR pwsParent;
    HANDLE hChild;
    LPCWSTR pwsChild;
} POWER_RELATIONSHIP, *PPOWER_RELATIONSHIP;
typedef struct IOCTL_POWER_CAPABILITIES IOCTL_POWER_CAPABILITIES;   /* referenced; no page prints a layout */
typedef struct IOCTL_POWER_GET IOCTL_POWER_GET;   /* referenced; no page prints a layout */
typedef struct IOCTL_POWER_QUERY IOCTL_POWER_QUERY;   /* referenced; no page prints a layout */
typedef struct IOCTL_POWER_SET IOCTL_POWER_SET;   /* referenced; no page prints a layout */
typedef struct IOCTL_REGISTER_POWER_RELATIONSHIP IOCTL_REGISTER_POWER_RELATIONSHIP;   /* referenced; no page prints a layout */
/* ms898291 DevicePowerNotify: print `DWORD DevicePowerNotify(PVOID pvDevice, CEDEVICE_POWER_STATE DeviceState, DWORD Flags);` */
AKARI_CE_IMPORT DWORD DevicePowerNotify(PVOID pvDevice, CEDEVICE_POWER_STATE DeviceState, DWORD Flags)
    AKARI_CE_NAME(DevicePowerNotify);
/* aa447831 GetDevicePower: print `DWORD GetDevicePower(PVOID pvDevice, DWORD dwDeviceFlags,PCEDEVICE_POWER_STATE pDeviceState);` */
AKARI_CE_IMPORT DWORD GetDevicePower(PVOID pvDevice, DWORD dwDeviceFlags, PCEDEVICE_POWER_STATE pDeviceState)
    AKARI_CE_NAME(GetDevicePower);
/* ms899319 GetSystemPowerState: print `DWORD GetSystemPowerState(LPWSTR pBuffer,DWORD Length,PDWORD pFlags);` */
AKARI_CE_IMPORT DWORD GetSystemPowerState(LPWSTR pBuffer, DWORD Length, PDWORD pFlags)
    AKARI_CE_NAME(GetSystemPowerState);
/* ms919797 RegisterPowerRelationship: print `HANDLE RegisterPowerRelationship(PVOID pvParent, PVOID pvChild,PPOWER_CAPABILITIES pCaps,DWORD Flags);` */
/* (record-only: parameter or return type unpublished) */
/* ms919802 ReleasePowerRelationship: print `DWORD ReleasePowerRelationship(HANDLE h);` */
AKARI_CE_IMPORT DWORD ReleasePowerRelationship(HANDLE h)
    AKARI_CE_NAME(ReleasePowerRelationship);
/* ms919803 ReleasePowerRequirement: print `DWORD ReleasePowerRequirement(HANDLE hPowerReq);` */
AKARI_CE_IMPORT DWORD ReleasePowerRequirement(HANDLE hPowerReq)
    AKARI_CE_NAME(ReleasePowerRequirement);
/* ms919833 RequestPowerNotifications: print `HANDLE RequestPowerNotifications(HANDLE hMsgQ,DWORD Flags);` */
AKARI_CE_IMPORT HANDLE RequestPowerNotifications(HANDLE hMsgQ, DWORD Flags)
    AKARI_CE_NAME(RequestPowerNotifications);
/* ms920584 SetDevicePower: print `DWORD SetDevicePower(PVOID pvDevice, DWORD dwDeviceFlags,CEDEVICE_POWER_STATE DeviceState);` */
AKARI_CE_IMPORT DWORD SetDevicePower(PVOID pvDevice, DWORD dwDeviceFlags, CEDEVICE_POWER_STATE DeviceState)
    AKARI_CE_NAME(SetDevicePower);
/* ms920689 SetPowerRequirement: print `HANDLE SetPowerRequirement(PVOID pvDevice,CEDEVICE_POWER_STATE DeviceState,ULONG DeviceFlags,PVOID pvSystemState,ULONG StateFlags);` */
AKARI_CE_IMPORT HANDLE SetPowerRequirement(PVOID pvDevice, CEDEVICE_POWER_STATE DeviceState, ULONG DeviceFlags, PVOID pvSystemState, ULONG StateFlags)
    AKARI_CE_NAME(SetPowerRequirement);
/* ms920754 SetSystemPowerState: print `DWORD SetSystemPowerState(LPCWSTR psState,DWORD StateFlags,DWORD Options);` */
AKARI_CE_IMPORT DWORD SetSystemPowerState(LPCWSTR psState, DWORD StateFlags, DWORD Options)
    AKARI_CE_NAME(SetSystemPowerState);
/* aa448148 StopPowerNotifications: print `BOOL StopPowerNotifications(HANDLE h);` */
AKARI_CE_IMPORT BOOL StopPowerNotifications(HANDLE h)
    AKARI_CE_NAME(StopPowerNotifications);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_PM_H */
