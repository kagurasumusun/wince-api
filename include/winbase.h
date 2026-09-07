/*
 * wince-api: Clean-room Windows CE API implementation for LLVM/Clang
 * File: winbase.h
 *
 * Core WinCE base/kernel APIs: File I/O, memory, process, thread, synchronization, module loading.
 */

#ifndef _WINBASE_H_
#define _WINBASE_H_

#include <sdkddkver.h>
#include <windef.h>
#include <winnt.h>
#include <winerror.h>

#ifdef __cplusplus
extern "C" {
#endif

/* System Info Structure */
typedef struct _SYSTEM_INFO {
    union {
        DWORD dwOemId;
        struct {
            WORD wProcessorArchitecture;
            WORD wReserved;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;
    DWORD dwPageSize;
    LPVOID lpMinimumApplicationAddress;
    LPVOID lpMaximumApplicationAddress;
    DWORD_PTR dwActiveProcessorMask;
    DWORD dwNumberOfProcessors;
    DWORD dwProcessorType;
    DWORD dwAllocationGranularity;
    WORD wProcessorLevel;
    WORD wProcessorRevision;
} SYSTEM_INFO, *LPSYSTEM_INFO;

/* File Time & System Time Structures */
typedef struct _FILETIME {
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;

typedef struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;

/* WIN32 Find Data Structure */
typedef struct _WIN32_FIND_DATAW {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
    DWORD dwOID;
    WCHAR cFileName[MAX_PATH];
} WIN32_FIND_DATAW, *PWIN32_FIND_DATAW, *LPWIN32_FIND_DATAW;

typedef WIN32_FIND_DATAW WIN32_FIND_DATA;
typedef PWIN32_FIND_DATAW PWIN32_FIND_DATA;
typedef LPWIN32_FIND_DATAW LPWIN32_FIND_DATA;

/* Memory Management APIs */
LPVOID WINAPI VirtualAlloc(LPVOID lpAddress, DWORD dwSize, DWORD flAllocationType, DWORD flProtect);
BOOL   WINAPI VirtualFree(LPVOID lpAddress, DWORD dwSize, DWORD dwFreeType);
BOOL   WINAPI VirtualProtect(LPVOID lpAddress, DWORD dwSize, DWORD flNewProtect, PDWORD lpflOldProtect);
DWORD  WINAPI VirtualQuery(LPCVOID lpAddress, void *lpBuffer, DWORD dwLength);

HLOCAL WINAPI LocalAlloc(UINT uFlags, DWORD uBytes);
HLOCAL WINAPI LocalFree(HLOCAL hMem);
HLOCAL WINAPI LocalReAlloc(HLOCAL hMem, DWORD uBytes, UINT uFlags);
LPVOID WINAPI LocalLock(HLOCAL hMem);
BOOL   WINAPI LocalUnlock(HLOCAL hMem);
DWORD  WINAPI LocalSize(HLOCAL hMem);

#define LMEM_FIXED          0x0000
#define LMEM_MOVEABLE       0x0002
#define LMEM_ZEROINIT       0x0040
#define LPTR                (LMEM_FIXED | LMEM_ZEROINIT)

/* Synchronization APIs */
VOID WINAPI InitializeCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
VOID WINAPI DeleteCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
VOID WINAPI EnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
VOID WINAPI LeaveCriticalSection(LPCRITICAL_SECTION lpCriticalSection);

HANDLE WINAPI CreateEventW(void *lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCWSTR lpName);
#define CreateEvent CreateEventW

BOOL WINAPI SetEvent(HANDLE hEvent);
BOOL WINAPI ResetEvent(HANDLE hEvent);
BOOL WINAPI PulseEvent(HANDLE hEvent);

#define WAIT_OBJECT_0       0x00000000L
#define WAIT_ABANDONED     0x00000080L
#define WAIT_TIMEOUT       0x00000102L
#define WAIT_FAILED        0xFFFFFFFFL
#define INFINITE           0xFFFFFFFFL

DWORD WINAPI WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds);
DWORD WINAPI WaitForMultipleObjects(DWORD nCount, const HANDLE *lpHandles, BOOL bWaitAll, DWORD dwMilliseconds);

/* File I/O APIs */
#define CREATE_NEW          1
#define CREATE_ALWAYS       2
#define OPEN_EXISTING       3
#define OPEN_ALWAYS         4
#define TRUNCATE_EXISTING   5

#define FILE_ATTRIBUTE_READONLY             0x00000001
#define FILE_ATTRIBUTE_HIDDEN               0x00000002
#define FILE_ATTRIBUTE_SYSTEM               0x00000004
#define FILE_ATTRIBUTE_DIRECTORY            0x00000010
#define FILE_ATTRIBUTE_ARCHIVE              0x00000020
#define FILE_ATTRIBUTE_NORMAL               0x00000080
#define FILE_ATTRIBUTE_TEMPORARY            0x00000100

HANDLE WINAPI CreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, void *lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
#define CreateFile CreateFileW

BOOL WINAPI ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, void *lpOverlapped);
BOOL WINAPI WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, void *lpOverlapped);
BOOL WINAPI CloseHandle(HANDLE hObject);

#define FILE_BEGIN           0
#define FILE_CURRENT         1
#define FILE_END             2

DWORD WINAPI SetFilePointer(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod);
DWORD WINAPI GetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh);

HANDLE WINAPI FindFirstFileW(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData);
#define FindFirstFile FindFirstFileW
BOOL WINAPI FindNextFileW(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData);
#define FindNextFile FindNextFileW
BOOL WINAPI FindClose(HANDLE hFindFile);

/* Process, Thread, and Module APIs */
typedef DWORD (WINAPI *LPTHREAD_START_ROUTINE)(LPVOID lpThreadParameter);

HANDLE WINAPI CreateThread(void *lpThreadAttributes, DWORD dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);
VOID   WINAPI ExitThread(DWORD dwExitCode);
DWORD  WINAPI GetCurrentThreadId(void);
HANDLE WINAPI GetCurrentThread(void);
DWORD  WINAPI GetCurrentProcessId(void);
HANDLE WINAPI GetCurrentProcess(void);

VOID WINAPI Sleep(DWORD dwMilliseconds);

HMODULE WINAPI LoadLibraryW(LPCWSTR lpLibFileName);
#define LoadLibrary LoadLibraryW
FARPROC WINAPI GetProcAddressW(HMODULE hModule, LPCWSTR lpProcName);
#define GetProcAddress GetProcAddressW
BOOL    WINAPI FreeLibrary(HMODULE hLibModule);

DWORD WINAPI GetLastError(void);
VOID  WINAPI SetLastError(DWORD dwErrCode);

/* System Info and Time */
VOID WINAPI GetSystemInfo(LPSYSTEM_INFO lpSystemInfo);
VOID WINAPI GetSystemTime(LPSYSTEMTIME lpSystemTime);
VOID WINAPI GetLocalTime(LPSYSTEMTIME lpSystemTime);
DWORD WINAPI GetTickCount(void);

#ifdef __cplusplus
}
#endif

#endif /* _WINBASE_H_ */
