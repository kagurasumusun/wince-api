/*
 * ceddk.h -- CEDDK dynamic-link library API for Windows CE (CEDDK.h layer).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  Source book: CE 5.0 "CEDDK Dynamic-Link Library" (the bus-
 * access / I-O / address-mapping / DMA leaves of
 * tools/manifests/ceddk-{bus,io,addr,dma}.manifest, fetched M57; CE 6.0
 * twins in build/pages6 cross-read where the CE 5.0 print is damaged).
 * OS Versions: "Windows CE .NET 4.0 and later".
 *
 * Import surface: the pages whose Requirements rows print
 * "Link Library: CEDDK.lib" (36 functions -- the HAL/bus-data, port and
 * register I/O, address-mapping and common-buffer sets) are pinned to
 * def/ceddk-doc.def.  The bus-access handle functions (BusIoControl,
 * CreateBusAccessHandle, ...) print no Link Library row: they are
 * declared without import pins and enter no def (the prsht.h M55
 * no-library model).
 *
 * Print artifacts resolved via twins (each noted per item):
 *   - CalibrateStallCounter (aa448302) prints the StallExecution body;
 *   - WRITE_PORT_BUFFER_USHORT (ms923673) prints the WRITE_PORT_BUFFER_
 *     ULONG body.
 *
 * Derived values (repo derived-value rule; paths recorded):
 *   - PHYSICAL_ADDRESS: no CE page of any generation defines the type
 *     (confirmed against the full CE 5.0 catalog and the CE 6.0 tree),
 *     but the CEDDK prototypes use it by value and by pointer.  The
 *     official Windows Drivers DDI page for IWDFDevice3::MapIoSpace
 *     (wudfddi.h) prints "The PHYSICAL_ADDRESS type is defined ...
 *     typedef LARGE_INTEGER PHYSICAL_ADDRESS;" -- derived as the
 *     LARGE_INTEGER of winnt.h.  Preserved page:
 *     build/pagesw/wudfddi-nf-wudfddi-iwdfdevice3-mapiospace.html
 */

#ifndef AKARI_CEDDK_H
#define AKARI_CEDDK_H

#include "windef.h"
#include "winnt.h"     /* LARGE_INTEGER (PHYSICAL_ADDRESS basis) */
#include "winbase.h"   /* LPOVERLAPPED (BusIoControl), DEVMGR_DEVICE_
                          INFORMATION (GetParentDeviceInfo, ms898294) */
#include "pm.h"        /* CEDEVICE_POWER_STATE (aa447663) */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Types.                                                              */
/* ------------------------------------------------------------------ */

/* PHYSICAL_ADDRESS / PPHYSICAL_ADDRESS: derived -- see header note
 * (LARGE_INTEGER basis, wudfddi MapIoSpace page). */
typedef LARGE_INTEGER PHYSICAL_ADDRESS, *PPHYSICAL_ADDRESS;

/* PPVOID: the pointer-to-PVOID parameter type printed by the
 * BusTransBusAddrToStatic / BusTransBusAddrToVirtual /
 * TransBusAddrToStatic / TransBusAddrToVirtual prototypes
 * (ms896153/ms896154/aa448211/aa448212). */
typedef PVOID *PPVOID;

/* ms896151 "BUS_DATA_TYPE": values via implicit successors as printed
 * (ConfigurationSpaceUndefined = -1, then Cmos..PNPISAConfiguration,
 * MaximumBusDataType). */
typedef enum _BUS_DATA_TYPE {
    ConfigurationSpaceUndefined = -1,
    Cmos,
    EisaConfiguration,
    Pos,
    CbusConfiguration,
    PCIConfiguration,
    VMEConfiguration,
    NuBusConfiguration,
    PCMCIAConfiguration,
    MPIConfiguration,
    MPSAConfiguration,
    PNPISAConfiguration,
    MaximumBusDataType
} BUS_DATA_TYPE, *PBUS_DATA_TYPE;

/* ms901367 "INTERFACE_TYPE": values via implicit successors as
 * printed. */
typedef enum _INTERFACE_TYPE {
    InterfaceTypeUndefined = -1,
    Internal,
    Isa,
    Eisa,
    MicroChannel,
    TurboChannel,
    PCIBus,
    VMEBus,
    NuBus,
    PCMCIABus,
    CBus,
    MPIBus,
    MPSABus,
    ProcessorInternal,
    InternalPowerBus,
    PNPISABus,
    PNPBus,
    MaximumInterfaceType
} INTERFACE_TYPE, *PINTERFACE_TYPE;

/* ms898303 "DMA_ADAPTER_OBJECT": the page prints the tag
 * "_DMA_ADAPTER_OBJECT_" (trailing underscore) -- reproduced. */
typedef struct _DMA_ADAPTER_OBJECT_ {
    USHORT         ObjectSize;
    INTERFACE_TYPE InterfaceType;
    ULONG          BusNumber;
} DMA_ADAPTER_OBJECT, *PDMA_ADAPTER_OBJECT;

/* ------------------------------------------------------------------ */
/* Bus access functions (no Link Library row -- no pins, no def).     */
/* ------------------------------------------------------------------ */

/* aa447690 "CreateBusAccessHandle". */
HANDLE CreateBusAccessHandle(LPCTSTR lpActiveRegPath);

/* aa447670 "CloseBusAccessHandle". */
VOID CloseBusAccessHandle(HANDLE hBusAccess);

/* ms896152 "BusIoControl". */
BOOL BusIoControl(HANDLE hBusAccess, DWORD dwIoControlCode,
                  LPVOID lpInBuffer, DWORD nInBufferSize,
                  LPVOID lpOutBuffer, DWORD nOutBufferSize,
                  LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped);

/* ms896153 "BusTransBusAddrToStatic". */
BOOL BusTransBusAddrToStatic(HANDLE hBusAccess, INTERFACE_TYPE InterfaceType,
                             ULONG BusNumber, PHYSICAL_ADDRESS BusAddress,
                             ULONG Length, ULONG *AddressSpace,
                             PPVOID MappedAddress);

/* ms896154 "BusTransBusAddrToVirtual". */
BOOL BusTransBusAddrToVirtual(HANDLE hBusAccess, INTERFACE_TYPE InterfaceType,
                              ULONG BusNumber, PHYSICAL_ADDRESS BusAddress,
                              ULONG Length, ULONG *AddressSpace,
                              PPVOID MappedAddress);

/* aa447824 "GetBusNamePrefix". */
BOOL GetBusNamePrefix(HANDLE hBusAccess, LPTSTR lpReturnStr,
                      DWORD dwSizeInCharacters);

/* aa447825 "GetChildDeviceRemoveState". */
BOOL GetChildDeviceRemoveState(HANDLE hBusAccess, PDWORD lpdChildDeviceState);

/* aa447827 "GetDeviceConfigurationData". */
ULONG GetDeviceConfigurationData(HANDLE hBusAccess, DWORD dwSpace,
                                 DWORD BusNumber, DWORD SlotNumber,
                                 DWORD dwOffset, DWORD dwLength,
                                 PVOID pBuffer);

/* ms920576 "SetDeviceConfigurationData". */
ULONG SetDeviceConfigurationData(HANDLE hBusAccess, DWORD dwSpace,
                                 DWORD BusNumber, DWORD SlotNumber,
                                 DWORD dwOffset, DWORD dwLength,
                                 PVOID pBuffer);

/* aa447832 "GetDevicePowerState". */
BOOL GetDevicePowerState(HANDLE hBusAccess, PCEDEVICE_POWER_STATE pPowerState,
                         PVOID pReserved);

/* ms920590 "SetDevicePowerState". */
BOOL SetDevicePowerState(HANDLE hBusAccess, CEDEVICE_POWER_STATE PowerState,
                         PVOID pReserved);

/* ms899309 "GetParentDeviceInfo". */
BOOL GetParentDeviceInfo(HANDLE hBusAccess,
                         PDEVMGR_DEVICE_INFORMATION pDeviceInfo);

/* aa448213 "TranslateBusAddr". */
BOOL TranslateBusAddr(HANDLE hBusAccess, INTERFACE_TYPE InterfaceType,
                      ULONG BusNumber, PHYSICAL_ADDRESS BusAddress,
                      PULONG AddressSpace, PPHYSICAL_ADDRESS TranslatedAddress);

/* aa448215 "TranslateSystemAddr". */
BOOL TranslateSystemAddr(HANDLE hBusAccess, INTERFACE_TYPE InterfaceType,
                         ULONG BusNumber, PHYSICAL_ADDRESS SystemAddress,
                         PPHYSICAL_ADDRESS TranslatedAddress);

/* aa448325 "StallExecution". */
VOID StallExecution(UINT MicrosecondsToStall);

/* aa448302 "CalibrateStallCounter": the CE 5.0 page prints the
 * StallExecution body (artifact); the CE 6.0 twin ee481529 prints
 * "VOID CalibrateStallCounter(void);". */
VOID CalibrateStallCounter(void);

/* ------------------------------------------------------------------ */
/* HAL / bus-data functions (CEDDK.lib).                               */
/* ------------------------------------------------------------------ */

/* ms899356 "HalGetBusData" ("BUS_DATA_TYPEBusDataType" is a
 * missing-space artifact on the page). */
AKARI_CE_IMPORT ULONG HalGetBusData(BUS_DATA_TYPE BusDataType, ULONG BusNumber,
                                    ULONG SlotNumber, PVOID Buffer,
                                    ULONG Length) AKARI_CE_NAME(HalGetBusData);

/* ms899357 "HalGetBusDataByOffset". */
AKARI_CE_IMPORT ULONG HalGetBusDataByOffset(BUS_DATA_TYPE BusDataType,
                                            ULONG BusNumber, ULONG SlotNumber,
                                            PVOID Buffer, ULONG Offset,
                                            ULONG Length) AKARI_CE_NAME(HalGetBusDataByOffset);

/* ms899359 "HalSetBusData". */
AKARI_CE_IMPORT ULONG HalSetBusData(BUS_DATA_TYPE BusDataType, ULONG BusNumber,
                                    ULONG SlotNumber, PVOID Buffer,
                                    ULONG Length) AKARI_CE_NAME(HalSetBusData);

/* ms899360 "HalSetBusDataByOffset". */
AKARI_CE_IMPORT ULONG HalSetBusDataByOffset(BUS_DATA_TYPE BusDataType,
                                            ULONG BusNumber, ULONG SlotNumber,
                                            PVOID Buffer, ULONG Offset,
                                            ULONG Length) AKARI_CE_NAME(HalSetBusDataByOffset);

/* ms899361 "HalTranslateBusAddress". */
AKARI_CE_IMPORT BOOL HalTranslateBusAddress(INTERFACE_TYPE InterfaceType,
                                            ULONG BusNumber,
                                            PHYSICAL_ADDRESS BusAddress,
                                            PULONG AddressSpace,
                                            PPHYSICAL_ADDRESS TranslatedAddress
                                            ) AKARI_CE_NAME(HalTranslateBusAddress);

/* ms899362 "HalTranslateSystemAddress". */
AKARI_CE_IMPORT BOOLEAN HalTranslateSystemAddress(INTERFACE_TYPE InterfaceType,
                                                  ULONG BusNumber,
                                                  PHYSICAL_ADDRESS SystemAddress,
                                                  PPHYSICAL_ADDRESS TranslatedAddress
                                                  ) AKARI_CE_NAME(HalTranslateSystemAddress);

/* ------------------------------------------------------------------ */
/* Port and register I/O functions (CEDDK.lib).                        */
/* ------------------------------------------------------------------ */

/* ms919746 "READ_PORT_BUFFER_UCHAR". */
AKARI_CE_IMPORT VOID READ_PORT_BUFFER_UCHAR(PUCHAR Port, PUCHAR Buffer,
                                            ULONG Count) AKARI_CE_NAME(READ_PORT_BUFFER_UCHAR);

/* ms919752 "READ_PORT_BUFFER_USHORT". */
AKARI_CE_IMPORT VOID READ_PORT_BUFFER_USHORT(PUSHORT Port, PUSHORT Buffer,
                                             ULONG Count) AKARI_CE_NAME(READ_PORT_BUFFER_USHORT);

/* ms919750 "READ_PORT_BUFFER_ULONG". */
AKARI_CE_IMPORT VOID READ_PORT_BUFFER_ULONG(PULONG Port, PULONG Buffer,
                                            ULONG Count) AKARI_CE_NAME(READ_PORT_BUFFER_ULONG);

/* ms919756 "READ_PORT_UCHAR". */
AKARI_CE_IMPORT UCHAR READ_PORT_UCHAR(PUCHAR Port) AKARI_CE_NAME(READ_PORT_UCHAR);

/* ms919763 "READ_PORT_USHORT". */
AKARI_CE_IMPORT USHORT READ_PORT_USHORT(PUSHORT Port) AKARI_CE_NAME(READ_PORT_USHORT);

/* ms919759 "READ_PORT_ULONG". */
AKARI_CE_IMPORT ULONG READ_PORT_ULONG(PULONG Port) AKARI_CE_NAME(READ_PORT_ULONG);

/* ms919766 "READ_REGISTER_BUFFER_UCHAR". */
AKARI_CE_IMPORT VOID READ_REGISTER_BUFFER_UCHAR(PUCHAR Register, PUCHAR Buffer,
                                                ULONG Count) AKARI_CE_NAME(READ_REGISTER_BUFFER_UCHAR);

/* ms919772 "READ_REGISTER_BUFFER_USHORT". */
AKARI_CE_IMPORT VOID READ_REGISTER_BUFFER_USHORT(PUSHORT Register,
                                                 PUSHORT Buffer,
                                                 ULONG Count) AKARI_CE_NAME(READ_REGISTER_BUFFER_USHORT);

/* ms919769 "READ_REGISTER_BUFFER_ULONG". */
AKARI_CE_IMPORT VOID READ_REGISTER_BUFFER_ULONG(PULONG Register, PULONG Buffer,
                                                ULONG Count) AKARI_CE_NAME(READ_REGISTER_BUFFER_ULONG);

/* ms919775 "READ_REGISTER_UCHAR". */
AKARI_CE_IMPORT UCHAR READ_REGISTER_UCHAR(PUCHAR Register) AKARI_CE_NAME(READ_REGISTER_UCHAR);

/* ms919784 "READ_REGISTER_USHORT". */
AKARI_CE_IMPORT USHORT READ_REGISTER_USHORT(PUSHORT Register) AKARI_CE_NAME(READ_REGISTER_USHORT);

/* ms919780 "READ_REGISTER_ULONG". */
AKARI_CE_IMPORT ULONG READ_REGISTER_ULONG(PULONG Register) AKARI_CE_NAME(READ_REGISTER_ULONG);

/* ms923671 "WRITE_PORT_BUFFER_UCHAR". */
AKARI_CE_IMPORT VOID WRITE_PORT_BUFFER_UCHAR(PUCHAR Port, PUCHAR Buffer,
                                             ULONG Count) AKARI_CE_NAME(WRITE_PORT_BUFFER_UCHAR);

/* ms923673 "WRITE_PORT_BUFFER_USHORT": the CE 5.0 page (and the CE 6.0
 * twin ee483607) print the WRITE_PORT_BUFFER_ULONG body (artifact);
 * derived from the documented family shape and the page's own
 * description ("writes a number of USHORT values"): PUSHORT port
 * pointer, PUSHORT buffer, ULONG count. */
AKARI_CE_IMPORT VOID WRITE_PORT_BUFFER_USHORT(PUSHORT Port, PUSHORT Buffer,
                                              ULONG Count) AKARI_CE_NAME(WRITE_PORT_BUFFER_USHORT);

/* ms923672 "WRITE_PORT_BUFFER_ULONG". */
AKARI_CE_IMPORT VOID WRITE_PORT_BUFFER_ULONG(PULONG Port, PULONG Buffer,
                                             ULONG Count) AKARI_CE_NAME(WRITE_PORT_BUFFER_ULONG);

/* ms923674 "WRITE_PORT_UCHAR". */
AKARI_CE_IMPORT VOID WRITE_PORT_UCHAR(PUCHAR Port, UCHAR Value) AKARI_CE_NAME(WRITE_PORT_UCHAR);

/* ms923677 "WRITE_PORT_USHORT". */
AKARI_CE_IMPORT VOID WRITE_PORT_USHORT(PUSHORT Port, USHORT Value) AKARI_CE_NAME(WRITE_PORT_USHORT);

/* ms923676 "WRITE_PORT_ULONG". */
AKARI_CE_IMPORT VOID WRITE_PORT_ULONG(PULONG Port, ULONG Value) AKARI_CE_NAME(WRITE_PORT_ULONG);

/* ms923678 "WRITE_REGISTER_BUFFER_UCHAR". */
AKARI_CE_IMPORT VOID WRITE_REGISTER_BUFFER_UCHAR(PUCHAR Register, PUCHAR Buffer,
                                                 ULONG Count) AKARI_CE_NAME(WRITE_REGISTER_BUFFER_UCHAR);

/* ms923680 "WRITE_REGISTER_BUFFER_USHORT". */
AKARI_CE_IMPORT VOID WRITE_REGISTER_BUFFER_USHORT(PUSHORT Register,
                                                  PUSHORT Buffer,
                                                  ULONG Count) AKARI_CE_NAME(WRITE_REGISTER_BUFFER_USHORT);

/* ms923679 "WRITE_REGISTER_BUFFER_ULONG". */
AKARI_CE_IMPORT VOID WRITE_REGISTER_BUFFER_ULONG(PULONG Register,
                                                 PULONG Buffer,
                                                 ULONG Count) AKARI_CE_NAME(WRITE_REGISTER_BUFFER_ULONG);

/* ms923681 "WRITE_REGISTER_UCHAR". */
AKARI_CE_IMPORT VOID WRITE_REGISTER_UCHAR(PUCHAR Register, UCHAR Value) AKARI_CE_NAME(WRITE_REGISTER_UCHAR);

/* ms923683 "WRITE_REGISTER_USHORT". */
AKARI_CE_IMPORT VOID WRITE_REGISTER_USHORT(PUSHORT Register,
                                           USHORT Value) AKARI_CE_NAME(WRITE_REGISTER_USHORT);

/* ms923682 "WRITE_REGISTER_ULONG". */
AKARI_CE_IMPORT VOID WRITE_REGISTER_ULONG(PULONG Register,
                                          ULONG Value) AKARI_CE_NAME(WRITE_REGISTER_ULONG);

/* ------------------------------------------------------------------ */
/* Address mapping functions (CEDDK.lib).                              */
/* ------------------------------------------------------------------ */

/* aa447863 "MmMapIoSpace" ("ULONGNumberOfBytes" is a missing-space
 * artifact on the page). */
AKARI_CE_IMPORT PVOID MmMapIoSpace(PHYSICAL_ADDRESS PhysicalAddress,
                                   ULONG NumberOfBytes,
                                   BOOLEAN CacheEnable) AKARI_CE_NAME(MmMapIoSpace);

/* aa447865 "MmUnmapIoSpace". */
AKARI_CE_IMPORT VOID MmUnmapIoSpace(PVOID BaseAddress,
                                    ULONG NumberOfBytes) AKARI_CE_NAME(MmUnmapIoSpace);

/* aa448212 "TransBusAddrToVirtual". */
AKARI_CE_IMPORT BOOL TransBusAddrToVirtual(INTERFACE_TYPE InterfaceType,
                                           ULONG BusNumber,
                                           PHYSICAL_ADDRESS BusAddress,
                                           ULONG Length, PULONG AddressSpace,
                                           PPVOID MappedAddress) AKARI_CE_NAME(TransBusAddrToVirtual);

/* aa448211 "TransBusAddrToStatic". */
AKARI_CE_IMPORT BOOL TransBusAddrToStatic(INTERFACE_TYPE InterfaceType,
                                          ULONG BusNumber,
                                          PHYSICAL_ADDRESS BusAddress,
                                          ULONG Length, PULONG AddressSpace,
                                          PPVOID MappedAddress) AKARI_CE_NAME(TransBusAddrToStatic);

/* ------------------------------------------------------------------ */
/* Common-buffer DMA functions (CEDDK.lib).                            */
/* ------------------------------------------------------------------ */

/* ms899352 "HalAllocateCommonBuffer". */
AKARI_CE_IMPORT PVOID HalAllocateCommonBuffer(PDMA_ADAPTER_OBJECT DmaAdapter,
                                              ULONG Length,
                                              PPHYSICAL_ADDRESS LogicalAddress,
                                              BOOLEAN CacheEnabled
                                              ) AKARI_CE_NAME(HalAllocateCommonBuffer);

/* ms899355 "HalFreeCommonBuffer". */
AKARI_CE_IMPORT VOID HalFreeCommonBuffer(PDMA_ADAPTER_OBJECT DmaAdapter,
                                         ULONG Length,
                                         PHYSICAL_ADDRESS LogicalAddress,
                                         PVOID VirtualAddress,
                                         BOOLEAN CacheEnabled
                                         ) AKARI_CE_NAME(HalFreeCommonBuffer);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_CEDDK_H */
