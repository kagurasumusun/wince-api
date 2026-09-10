/* Partdrv.h -- partition driver (partdrv) DDI (record surface).
 *
 * Source pages: File Systems and Data Store book, Partition Manager
 * rows printing "Header: Partdrv.h" (17 PD_* function pages + the
 * PD_PARTINFO / PD_STOREINFO structure pages ms891440 / ms891443).
 * The PD_* entry points are implemented by the partition driver
 * (driver-supplied, MyFSD callback precedent); prototypes are
 * recorded.  The structures embed the unpublished SECTORNUM type,
 * so they are held (prints recorded, opaque closure).
 * See docs/inventory.md M79b.
 */

#ifndef AKARI_PARTDRV_H
#define AKARI_PARTDRV_H

/* --- Held structures (SECTORNUM unpublished). ------------------- */
/* ms891440 "PD_PARTINFO": print `typedef struct _PD_PARTINFO {DWORD
 * cbSize;TCHAR szPartitionName[PARTITIONNAMESIZE];SECTORNUM
 * snNumSectors;FILETIME ftCreated;FILETIME ftLastModified;DWORD
 * dwAttributes;BYTE bPartType;} PD_PARTINFO, *PPD_PARTINFO;` --
 * PARTITIONNAMESIZE and SECTORNUM are not printed by any CE page;
 * held. */
typedef struct _PD_PARTINFO PD_PARTINFO, *PPD_PARTINFO;

/* ms891443 "PD_STOREINFO": print `typedef struct _PD_STOREINFO {DWORD
 * cbSize;SECTORNUM snNumSectors;DWORD dwBytesPerSector;SECTORNUM
 * snFreeSectors;SECTORNUM snBiggestPartCreatable;FILETIME ftCreated;
 * FILETIME ftLastModified;DWORD dwAttributes;} PD_STOREINFO,
 * *PPD_STOREINFO;` -- held (SECTORNUM). */
typedef struct _PD_STOREINFO PD_STOREINFO, *PPD_STOREINFO;

/* --- Recorded driver-supplied prototypes. ---------------------- */
/* `PD_ClosePartition void PD_ClosePartition(DWORD dwPartitionId);` */
/* `PD_CloseStore void PD_CloseStore(DWORDdwStoreId);` */
/* `PD_CreatePartition DWORD PD_CreatePartition(DWORD dwStoreId,LPCTSTR szPartName,BYTE bPartType, SECTORNUM numSectors, BOOL bAuto);` */
/* `PD_DeletePartition DWORD PD_DeletePartition(DWORD dwStoreId, LPCTSTR szPartName);` */
/* `PD_DeviceIoControl DWORD PD_DeviceIoControl(DWORD dwPartitionId, DWORD dwCode, PBYTE pInBuf, DWORD nInBufSize, PBYTE pOutBuf, DWORD nOutBufSize, PDWORD pBytesReturned);` */
/* `PD_FindPartitionClose void PD_FindPartitionClose(DWORDdwSearchId);` */
/* `PD_FindPartitionNext DWORD PD_FindPartitionNext(DWORDdwSearchId, PD_PARTINFO* pInfo);` */
/* `PD_FindPartitionStart DWORD PD_FindPartitionStart(DWORD dwStoreId, LPDWORD pdwSearchId);` */
/* `PD_FormatPartition DWORD PD_FormatPartition(DWORDdwStoreId, LPCTSTR szPartName, BYTE bPartType, BOOL bAuto);` */
/* `PD_FormatStore DWORD PD_FormatStore(DWORDdwStoreId);` */
/* `PD_GetPartitionInfo DWORD PD_GetPartitionInfo(DWORDdwStoreId, LPCTSTR szPartName, PD_PARTINFO* pInfo);` */
/* `PD_GetStoreInfo DWORD PD_GetStoreInfo(DWORDdwStoreId,PD_STOREINFO* pInfo);` */
/* `PD_IsStoreFormatted DWORD PD_IsStoreFormatted(DWORDdwStoreId);` */
/* `PD_OpenPartition DWORD PD_OpenPartition(DWORD dwStoreId, LPCTSTR szPartName, LPDWORD pdwPartitionId);` */
/* `PD_OpenStore DWORD PD_OpenStore(HANDLE hDisk, LPDWORD pdwStoreId);` */
/* `PD_RenamePartition DWORD PD_RenamePartition(DWORD dwStoreId, LPCTSTR szOldName, LPCTSTR szNewName);` */
/* `PD_SetPartitionAttrs DWORD PD_SetPartitionAttrs(DWORDdwStoreId, LPCTSTR szPartName, DWORD dwAttr);` */

#endif /* AKARI_PARTDRV_H */
