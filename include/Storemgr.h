/* Storemgr.h -- Storage Manager partition/store API (Storeapi.lib).
 *
 * Source pages: File Systems and Data Store book, Storage Manager
 * Functions (22 pages, Link Library: Storeapi.lib) plus the
 * structure pages PARTINFO (ms891424), STOREINFO (ms892106),
 * CE_VOLUME_INFO (aa517292), STORAGEDEVICEINFO (ms892022),
 * STORAGECONTEXT (ms892014), fetched as
 * tools/manifests/fsd-types.manifest.  The array-size constants
 * (*NAMESIZE, PROFILENAMESIZE) and the SECTORNUM type are not
 * printed by any CE page, so every structure embedding them is
 * recorded verbatim and closed opaquely; functions taking those
 * structures by pointer are declared.  CreatePartition and
 * CreatePartitionEx take SECTORNUM by value and CeGetVolumeInfo
 * takes the unpublished CE_VOLUME_INFO_LEVEL, so those three are
 * recorded.  See docs/inventory.md M79a.
 */

#ifndef AKARI_STOREMGR_H
#define AKARI_STOREMGR_H

#include "Windef.h"    /* BOOL, DWORD, HANDLE, BYTE, LPCTSTR */
#include "Winbase.h"   /* FILETIME, WINAPI */

/* --- Held structures (unpublished size constants; prints recorded). */
/* ms892022 "STORAGEDEVICEINFO": print `typedef struct
 * tagSTORAGEDEVICEINFO {DWORD cbSize;TCHAR szProfile[PROFILENAMESIZE];
 * DWORD dwDeviceClass;DWORD dwDeviceType;DWORD dwDeviceFlags;}
 * STORAGEDEVICEINFO, *PSTORAGEDEVICEINFO;` -- PROFILENAMESIZE is not
 * printed by any CE page; held. */
typedef struct tagSTORAGEDEVICEINFO STORAGEDEVICEINFO, *PSTORAGEDEVICEINFO;

/* ms891424 "PARTINFO": print `typedef struct {DWORD cbSize;TCHAR
 * szPartitionName[PARTITIONNAMESIZE];TCHAR szFileSys[FILESYSNAMESIZE];
 * TCHAR szVolumeName[VOLUMENAMESIZE];SECTORNUM snNumSectors;FILETIME
 * ftCreated;FILETIME ftLastModified;DWORD dwAttributes;BYTE bPartType;}
 * PARTINFO, *PPARTINFO;` -- the three *NAMESIZE constants and SECTORNUM
 * are not printed by any CE page; held. */
typedef struct _PARTINFO PARTINFO, *PPARTINFO;

/* ms892106 "STOREINFO (Storage Manager)": print `typedef struct {DWORD
 * cbSize;TCHAR szDeviceName[DEVICENAMESIZE];TCHAR szStoreName
 * [STORENAMESIZE];DWORD dwDeviceClass;DWORD dwDeviceType;
 * STORAGEDEVICEINFOsdi; DWORD dwDeviceFlags;SECTORNUM snNumSectors;
 * DWORD dwBytesPerSector;SECTORNUM snFreeSectors;SECTORNUM
 * snBiggestPartCreatable;FILETIME ftCreated;FILETIME ftLastModified;
 * DWORD dwAttributes;DWORD dwPartitionCount;DWORD dwMountCount;}
 * STOREINFO, *PSTOREINFO;` -- held (NAMESIZE constants, SECTORNUM,
 * embedded held STORAGEDEVICEINFO). */
/* Collision note: the Cesync/COM STOREINFO (ms896271, tag tagStoreInfo,
 * placed in Objbase.h M73b) owns the STOREINFO / PSTOREINFO typedef
 * names repo-wide; this Storage Manager struct (anonymous tag in the
 * print) is closed under the qualified pointer name and the function
 * declarations below use it, with the documented PSTOREINFO spelling
 * preserved in the quoted prints. */
typedef struct _STOREMGR_STOREINFO *PSTOREMGR_STOREINFO;

/* aa517292 "CE_VOLUME_INFO": print `typedef struct _CE_VOLUME_INFO
 * {DWORD cbSize;DWORD dwAttributes;DWORD dwFlags; DWORD dwBlockSize;
 * TCHAR szStoreName[STORENAMESIZE];TCHARszPartitionName
 * [PARTITIONNAMESIZE]; } CE_VOLUME_INFO, *PCE_VOLUME_INFO,
 * *LPCE_VOLUME_INFO;` -- held (NAMESIZE constants). */
typedef struct _CE_VOLUME_INFO CE_VOLUME_INFO, *PCE_VOLUME_INFO,
    *LPCE_VOLUME_INFO;

/* ms892014 "STORAGECONTEXT": print embeds STOREINFO and PARTINFO by
 * value (both held); held. */
typedef struct tagSTORAGECONTEXT STORAGECONTEXT, *PSTORAGECONTEXT;

/* --- Functions (Storeapi.lib). --------------------------------- */
/* "DeletePartition": print `BOOL WINAPI DeletePartition(HANDLE hStore,LPCTSTR szPartitionName)` */
AKARI_CE_IMPORT BOOL WINAPI DeletePartition(HANDLE hStore, LPCTSTR szPartitionName)
                    AKARI_CE_NAME(DeletePartition);

/* "DismountPartition": print `BOOL WINAPI DismountPartition(HANDLE hPartition)` */
AKARI_CE_IMPORT BOOL WINAPI DismountPartition(HANDLE hPartition)
                    AKARI_CE_NAME(DismountPartition);

/* "DismountStore": print `BOOL WINAPI DismountStore(HANDLE hStore)` */
AKARI_CE_IMPORT BOOL WINAPI DismountStore(HANDLE hStore)
                    AKARI_CE_NAME(DismountStore);

/* "FindClosePartition": print `BOOL WINAPI FindClosePartition(HANDLE hSearch)` */
AKARI_CE_IMPORT BOOL WINAPI FindClosePartition(HANDLE hSearch)
                    AKARI_CE_NAME(FindClosePartition);

/* "FindCloseStore": print `BOOL WINAPI FindCloseStore(HANDLE hSearch)` */
AKARI_CE_IMPORT BOOL WINAPI FindCloseStore(HANDLE hSearch)
                    AKARI_CE_NAME(FindCloseStore);

/* "FindFirstPartition": print `HANDLE WINAPI FindFirstPartition(HANDLE hStore,PPARTINFO pPartInfo)` */
AKARI_CE_IMPORT HANDLE WINAPI FindFirstPartition(HANDLE hStore, PPARTINFO pPartInfo)
                    AKARI_CE_NAME(FindFirstPartition);

/* "FindFirstStore": print `HANDLE WINAPI FindFirstStore(PSTOREINFO pStoreInfo)` */
AKARI_CE_IMPORT HANDLE WINAPI FindFirstStore(PSTOREMGR_STOREINFO pStoreInfo)
                    AKARI_CE_NAME(FindFirstStore);

/* "FindNextPartition": print `BOOL WINAPI FindNextPartition(HANDLE hSearch,PPARTINFO pPartInfo)` */
AKARI_CE_IMPORT BOOL WINAPI FindNextPartition(HANDLE hSearch, PPARTINFO pPartInfo)
                    AKARI_CE_NAME(FindNextPartition);

/* "FindNextStore": print `BOOL WINAPI FindNextStore(HANDLE hSearch,PSTOREINFO pStoreInfo)` */
AKARI_CE_IMPORT BOOL WINAPI FindNextStore(HANDLE hSearch, PSTOREMGR_STOREINFO pStoreInfo)
                    AKARI_CE_NAME(FindNextStore);

/* "FormatPartition": print `BOOL WINAPI FormatPartition(HANDLE hPartition)` */
AKARI_CE_IMPORT BOOL WINAPI FormatPartition(HANDLE hPartition)
                    AKARI_CE_NAME(FormatPartition);

/* "FormatPartitionEx": print `BOOL WINAPI FormatPartitionEx(HANDLE hPartition,BYTE bPartType,BOOL bAuto)` */
AKARI_CE_IMPORT BOOL WINAPI FormatPartitionEx(HANDLE hPartition, BYTE bPartType, BOOL bAuto)
                    AKARI_CE_NAME(FormatPartitionEx);

/* "FormatStore": print `BOOL WINAPI FormatStore(HANDLE hStore)` */
AKARI_CE_IMPORT BOOL WINAPI FormatStore(HANDLE hStore)
                    AKARI_CE_NAME(FormatStore);

/* "GetPartitionInfo": print `BOOL WINAPI GetPartitionInfo(HANDLE hPartition,PPARTINFO pPartInfo)` */
AKARI_CE_IMPORT BOOL WINAPI GetPartitionInfo(HANDLE hPartition, PPARTINFO pPartInfo)
                    AKARI_CE_NAME(GetPartitionInfo);

/* "GetStoreInfo": print `BOOL WINAPI GetStoreInfo(HANDLE hStore,PSTOREINFO pStoreInfo)` */
AKARI_CE_IMPORT BOOL WINAPI GetStoreInfo(HANDLE hStore, PSTOREMGR_STOREINFO pStoreInfo)
                    AKARI_CE_NAME(GetStoreInfo);

/* "MountPartition": print `BOOL WINAPI MountPartition(HANDLE hPartition)` */
AKARI_CE_IMPORT BOOL WINAPI MountPartition(HANDLE hPartition)
                    AKARI_CE_NAME(MountPartition);

/* "OpenPartition": print `HANDLE WINAPI OpenPartition(HANDLE hStore,LPCTSTR szPartitionName)` */
AKARI_CE_IMPORT HANDLE WINAPI OpenPartition(HANDLE hStore, LPCTSTR szPartitionName)
                    AKARI_CE_NAME(OpenPartition);

/* "OpenStore": print `HANDLE OpenStore(LPCSTR szDeviceName)` */
AKARI_CE_IMPORT HANDLE OpenStore(LPCSTR szDeviceName)
                    AKARI_CE_NAME(OpenStore);

/* "RenamePartition": print `BOOL WINAPI RenamePartition(HANDLE hPartition,LPCTSTR szNewName)` */
AKARI_CE_IMPORT BOOL WINAPI RenamePartition(HANDLE hPartition, LPCTSTR szNewName)
                    AKARI_CE_NAME(RenamePartition);

/* "SetPartitionAttributes": print `BOOL WINAPI SetPartitionAttributes(HANDLE hPartition,DWORD dwAttrs)` */
AKARI_CE_IMPORT BOOL WINAPI SetPartitionAttributes(HANDLE hPartition, DWORD dwAttrs)
                    AKARI_CE_NAME(SetPartitionAttributes);

/* --- Recorded (unpublished parameter types). -------------------- */
/* "CreatePartition": `BOOL WINAPI CreatePartition(HANDLE hStore,
 * LPCTSTR szPartitionName,SECTORNUM snNumSectors);` -- SECTORNUM is
 * not printed by any CE page. */
/* "CreatePartitionEx": `BOOL WINAPI CreatePartitionEx(HANDLE hStore,
 * LPCTSTR szPartitionName,BYTE bPartType,SECTORNUM snNumSectors);`
 * -- SECTORNUM unpublished. */
/* "CeGetVolumeInfo": `WINBASEAPI BOOL CeGetVolumeInfo(LPCWSTR
 * pszRootPath,CE_VOLUME_INFO_LEVEL InfoLevel,LPCE_VOLUME_INFO
 * lpVolumeInfo);` -- CE_VOLUME_INFO_LEVEL is not printed by any CE
 * page. */

#endif /* AKARI_STOREMGR_H */
