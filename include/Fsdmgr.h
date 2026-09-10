/* Fsdmgr.h -- File System Driver (FSD) Manager helper library.
 *
 * Source pages: File Systems and Data Store book, FSD Functions +
 * Partition Manager rows printing "Header: Fsdmgr.h" (55 pages),
 * plus FILELOCKSTATE (aa517917), FILTERHOOK (ms889612),
 * FSD_VOLUME_INFO (aa517924), FSD_SCATTER_GATHER_INFO (ms890842),
 * FSD_SCATTER_GATHER_RESULTS (ms890852) from the FSD supplement.
 *
 * The FSD-supplied MyFSD_* entry points are driver-implemented
 * (Miniport / Protocol callback precedent) and recorded, not
 * declared.  The
 * HDSK / HVOL handle types, the FDI / FBI / FNFSG types and the
 * FILTERHOOK callback-pointer members are not printed by any CE
 * page, so every function taking HDSK or HVOL by value (or the
 * filter hook) is recorded; pointer-only surfaces are declared.
 * The lock
 * helpers live in Lockmgrhelp.h / Lockmgr.h / Lockmgrtypes.h.
 * See docs/inventory.md M79b.
 */

#ifndef AKARI_FSDMGR_H
#define AKARI_FSDMGR_H

#include "Windef.h"    /* DWORD, BOOL, HANDLE, PVOID, PWSTR */
#include "Winbase.h"   /* LPCRITICAL_SECTION, LPOVERLAPPED */

/* --- FSD-opaque objects (no CE page prints the layout; all
 *     documented uses are through pointers). ---------------------- */
typedef struct _FSD_VOLUME VOLUME, *PVOLUME;
typedef struct _FSD_FILE FILE, *PFILE;
typedef struct _FSD_SEARCH SEARCH, *PSEARCH;

/* aa517917 "FILELOCKSTATE": print `typedef struct _FILELOCKSTATE
 * { DWORD dwPosLow; DWORD dwPosHigh; DWORD dwAccess;
 * LPCRITICAL_SECTION lpcs; BOOL fTerminal; HANDLE hevUnlock; DWORD
 * cQueue; PVOID pvLockContainer;} FILELOCKSTATE, * PFILELOCKSTATE;`
 * (spaced * as printed) -- fully grounded via Winbase.h
 * LPCRITICAL_SECTION. */
typedef struct _FILELOCKSTATE {
    DWORD             dwPosLow;
    DWORD             dwPosHigh;
    DWORD             dwAccess;
    LPCRITICAL_SECTION lpcs;
    BOOL              fTerminal;
    HANDLE            hevUnlock;
    DWORD             cQueue;
    PVOID             pvLockContainer;
} FILELOCKSTATE, *PFILELOCKSTATE;

/* ms890852 "FSD_SCATTER_GATHER_RESULTS": print (glued tokens split). */
typedef struct _FSD_SCATTER_GATHER_RESULTS {
    DWORD dwFlags;
    DWORD cSectorsTransferred;
} FSD_SCATTER_GATHER_RESULTS, *PFSGR;

/* --- Held FSD types (prints recorded; opaque closure). ---------- */
/* ms890842 "FSD_SCATTER_GATHER_INFO": print `typedef struct
 * _FSD_SCATTER_GATHER_INFO{DWORD dwFlags;DWORD idDsk;DWORD dwSector;
 * DWORD cSectors;PFDI pfdi;DWORD cfbi;PFBI pfbi;PFNFSG pfnCallBack;}
 * FSD_SCATTER_GATHER_INFO, *PFSGI;` -- FDI / FBI / FNFSG are not
 * printed by any CE page; held (pointer-only below). */
typedef struct _FSD_SCATTER_GATHER_INFO FSD_SCATTER_GATHER_INFO, *PFSGI;

/* ms889612 "FILTERHOOK": print `typedef struct tagFILTERHOOK {DWORD
 * cbSize;DWORD hVolume;PCLOSEVOLUME pCloseVolume;PCREATEDIRECTORYW
 * pCreateDirectoryW; ...;PFINDNEXTFILEW pFindNextFileW;...}` -- the
 * twenty P* filter-callback typedefs are not printed by any CE page;
 * held (full print in docs/inventory.md M79b). */
typedef struct tagFILTERHOOK FILTERHOOK, *PFILTERHOOK;

/* aa517924 "FSD_VOLUME_INFO": print `typedef struct _FSD_VOLUME_INFO
 * { DWORD cbSize; DWORD dwFSVersion ; TCHAR szFSDDesc
 * [MAX_FSD_DESCRIPTOR]; TCHAR szFSDSubType[MAX_FSD_DESCRIPTOR]; DWORD
 * dwAttributes; DWORD dwBlockSize; DWORD dwFlags; } FSD_VOLUME_INFO,
 * *PFSD_VOLUME_INFO;` -- MAX_FSD_DESCRIPTOR is not printed by any CE
 * page; held. */
typedef struct _FSD_VOLUME_INFO FSD_VOLUME_INFO, *PFSD_VOLUME_INFO;

/* --- Declared functions (Fsdmgr.lib). -------------------------- */
/* "FSDMGR_ReadDiskEx": print `DWORD FSDMGR_ReadDiskEx( PFSGIpfsgi,
 * PFSGR pfsgr);` (glued tokens split). */
AKARI_CE_IMPORT DWORD FSDMGR_ReadDiskEx(PFSGI pfsgi, PFSGR pfsgr)
                    AKARI_CE_NAME(FSDMGR_ReadDiskEx);

/* "FSDMGR_WriteDiskEx": print `DWORD FSDMGR_WriteDiskEx( PFSGIpfsgi,
 * PFSGR pfsgr);`. */
AKARI_CE_IMPORT DWORD FSDMGR_WriteDiskEx(PFSGI pfsgi, PFSGR pfsgr)
                    AKARI_CE_NAME(FSDMGR_WriteDiskEx);

/* "FSD_UnhookVolume": print `BOOL FSD_UnhookVolume(PVOLUME pvol);`. */
AKARI_CE_IMPORT BOOL FSD_UnhookVolume(PVOLUME pvol)
                    AKARI_CE_NAME(FSD_UnhookVolume);

/* --- Recorded functions (HDSK / HVOL / unpublished types by value). */
/* "FSDMGR_DeviceHandleToHDSK": `HDSK FSDMGR_DeviceHandleToHDSK(
 * HANDLEhDisk);` -- HDSK unpublished. */
/* "FSDMGR_CreateFileHandle": `HANDLE FSDMGR_CreateFileHandle( HVOLhVol,
 * HANDLE hProc,PFILE pFile);` -- HVOL unpublished. */
/* "FSDMGR_CreateSearchHandle": `HANDLE FSDMGR_CreateSearchHandle(
 * HVOLhVol,HANDLE hProc,PSEARCH pSearch);` -- HVOL unpublished. */
/* "FSDMGR_DeregisterVolume": `void FSDMGR_DeregisterVolume( HVOLhVol);`
 * -- HVOL unpublished. */
/* "FSDMGR_DiskIoControl": `DWORD FSDMGR_DiskIoControl( HDSKhDsk,DWORD
 * dwIoControlCode,LPVOID lpInBuf,DWORD nInBufSize,LPVOID lpOutBuf,DWORD
 * nOutBufSize,LPDWORD lpBytesReturned,LPOVERLAPPED lpOverlapped);` --
 * HDSK unpublished. */
/* "FSDMGR_GetDiskInfo": `DWORD FSDMGR_GetDiskInfo( HDSKhDsk,PFDI pfdi);`
 * -- HDSK and FDI unpublished. */
/* "FSDMGR_GetRegistryFlag": `BOOL FSDMGR_GetRegistryFlag( HDSK hDsk,
 * PCTSTR szValueName,PDWORD pdwFlag,DWORD dwSet);` -- HDSK unpub. */
/* "FSDMGR_GetRegistryString": `BOOL FSDMGR_GetRegistryString(HDSK hDsk,
 * PCTSTR szValueName,PTSTR szValue,DWORD dwSize);` -- HDSK unpub. */
/* "FSDMGR_GetRegistryValue": `BOOL FSDMGR_GetRegistryValue( HDSK hDsk,
 * PCTSTR szValueName,PDWORD pdwValue);` -- HDSK unpublished. */
/* "FSDMGR_GetVolumeName": `INT FSDMGR_GetVolumeName( HVOLhVol,PWSTR
 * pwsName,int cchMax);` -- HVOL unpublished. */
/* "FSDMGR_ReadDisk" / "FSDMGR_WriteDisk": `DWORD FSDMGR_ReadDisk(
 * HDSKhDsk,DWORD dwSector,DWORD cSectors,PBYTE pBuffer,DWORD
 * cbBuffer);` (WriteDisk identical) -- HDSK unpublished. */
/* "FSDMGR_RegisterVolume": `HVOL FSDMGR_RegisterVolume( HDSKhDsk,PWSTR
 * pwsName,PVOLUME pVolume);` -- HDSK / HVOL unpublished. */
/* "FSD_HookVolume": `PVOLUME FSD_HookVolume(HDSK hdsk,PFILTERHOOK
 * pFilterHook);` -- HDSK unpublished (PFILTERHOOK is the held
 * FILTERHOOK pointer). */
/* "FSD_MountDisk" / "FSD_UnmountDisk" (Fsdmgr.lib rows): prints
 * `BOOLFSD_MountDisk( HDSKhdsk);` / `BOOLFSD_UnmountDisk( HDSKhdsk);`
 * -- HDSK is not printed by any CE page (recorded; page-text
 * recovery M91, the M79 note "no signature" was a rows-sig
 * extraction gap). */

/* aa517921 "FSDMGR_EmptyLockContainer" (Fsdmgr.lib row): print
 * `BOOL MyFSD_EmptyLockContainer( PFILELOCKSTATE pFileLockState );`
 * (the prototype line misprints the callee as MyFSD_ -- the page
 * describes the FSDMGR helper; archive typo).  PFILELOCKSTATE is
 * the Fsdmgr.h opaque FILELOCKSTATE pointer, so unlike the
 * HDSK/HVOL-by-value set this one is declared. */
AKARI_CE_IMPORT BOOL FSDMGR_EmptyLockContainer(PFILELOCKSTATE pFileLockState)
                    AKARI_CE_NAME(FSDMGR_EmptyLockContainer);

/* --- Recorded FSD-supplied entry points (MyFSD_*). -------------- */
/* MyFSD_* are implemented by the file system driver and called by
 * the FSD manager, not imported.  Pages with printed prototypes:
 * MyFSD_CloseVolume `BOOL MyFSD_CloseVolume( PVOLUMEpVolume);`,
 * MyFSD_DeleteAndRenameFileW `BOOL MyFSD_DeleteAndRenameFileW(
 * PVOLUME pVolume,LPCWSTRpwsOldFileName,LPCWSTRpwsNewFileName);`,
 * MyFSD_DeviceIoControl `BOOL MyFSD_DeviceIoControl( PFILEpFile,DWORD
 * dwIoControlCode,PVOIDpInBuf,DWORDnInBufSize,PVOIDpOutBuf,DWORD
 * nOutBufSize,PDWORDpBytesReturned,OVERLAPPED* pOverlapped);`,
 * MyFSD_FlushFileBuffers `BOOL MyFSD_FlushFileBuffers( PFILE pFile);`,
 * MyFSD_GetVolumeInfo `MyFSD_GetVolumeInfo( DWORD dwVolume,
 * FSD_VOLUME_INFO *pInfo );`, MyFSD_LockFileEx / MyFSD_UnLockFileEx
 * (LPOVERLAPPED lock forms), MyFSD_Notify `void MyFSD_Notify(
 * PVOLUMEpVolume,DWORDdwFlags);`, MyFSD_ReadFileWithSeek /
 * MyFSD_WriteFileWithSeek (OVERLAPPED* seek forms),
 * MyFSD_RegisterFileSystemFunction `BOOL
 * MyFSD_RegisterFileSystemFunction( PVOLUMEpVolume,
 * SHELLFILECHANGEFUNC_tpfn);` (Extfile.h).  Pages printing no
 * signature: MyFSD_CloseFile, MyFSD_CreateDirectoryW,
 * MyFSD_CreateFileW, MyFSD_DeleteFileW, MyFSD_FindClose,
 * MyFSD_FindFirstFileW, MyFSD_FindNextFileW, MyFSD_FsIoControl,
 * MyFSD_GetDiskFreeSpaceW, MyFSD_GetFileAttributesW,
 * MyFSD_GetFileInformationByHandle, MyFSD_GetFileSize,
 * MyFSD_GetFileTime, MyFSD_MoveFileW, MyFSD_ReadFile,
 * MyFSD_ReadFileScatter, MyFSD_RemoveDirectoryW, MyFSD_SetEndOfFile,
 * MyFSD_SetFileAttributesW, MyFSD_SetFilePointer, MyFSD_SetFileTime,
 * MyFSD_UnmountDisk, MyFSD_MountDisk, MyFSD_WriteFile,
 * MyFSD_WriteFileGather. */

/* ------------------------------------------------------------------
 * Book surface: fsds-remainder (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms885120 Accessing Files on Other Storage Media */
/* ms885325 Creating and Opening a File or Directory */
/* ms885351 Deleting a File or a Directory */
/* ms885363 Determining Available Disk Space */
/* ms885416 File-Naming Limitations */
/* ms885501 Manipulating File Times */
/* ms885512 Memory Mapping a File */
/* ms885849 Moving and Copying Files and Directories */
/* ms885978 Querying for Version Information */
/* ms886040 Read/Write Example */
/* ms886005 Reading and Writing File Attributes */
/* ms886029 Reading from a File */
/* ms886095 Retrieving File and Directory Information */
/* ms886105 Searching for a File or Directory */
/* ms886160 Setting the File Pointer */
/* aa516903 Synchronization and Device I/O */
/* aa516923 Writing to a File */
#endif /* AKARI_FSDMGR_H */
