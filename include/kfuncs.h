/*
 * wince-api: Clean-room Windows CE API implementation for LLVM/Clang
 * File: kfuncs.h
 *
 * WinCE Kernel / Low-level Function declarations (kfuncs).
 */

#ifndef _KFUNCS_H_
#define _KFUNCS_H_

#include <sdkddkver.h>
#include <windef.h>
#include <winnt.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Kernel Cache & Memory Control APIs */
VOID WINAPI CacheSync(int flags);
VOID WINAPI CacheRangeFlush(LPVOID pAddr, DWORD dwLength, DWORD dwFlags);

#define CACHE_SYNC_DISCARD      0x0001
#define CACHE_SYNC_INSTRUCT     0x0002
#define CACHE_SYNC_WRITEBACK    0x0004
#define CACHE_SYNC_FLUSH        (CACHE_SYNC_DISCARD | CACHE_SYNC_WRITEBACK)

/* Interrupt / System Control */
BOOL WINAPI InterruptInitialize(DWORD idInt, HANDLE hEvent, LPVOID pvData, DWORD cbData);
VOID WINAPI InterruptDone(DWORD idInt);
VOID WINAPI InterruptDisable(DWORD idInt);

/* Kernel System Space Access */
LPVOID WINAPI MapCallerPtr(LPVOID ptr, DWORD dwLen);
LPVOID WINAPI MapPtrToProcess(LPVOID ptr, HANDLE hProc);

#ifdef __cplusplus
}
#endif

#endif /* _KFUNCS_H_ */
