/*
 * wince-api: Clean-room Windows CE API implementation for LLVM/Clang
 * File: sipapi.h
 *
 * Windows CE Software Input Panel (SIP) API definitions.
 */

#ifndef _SIPAPI_H_
#define _SIPAPI_H_

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    DWORD cbSize;
    DWORD fdwFlags;
    RECT  rcSipRect;
    DWORD dwImDataSize;
    VOID  *pvImData;
} SIPINFO, *PSIPINFO;

#define SIPF_OFF        0x00000000
#define SIPF_ON         0x00000001
#define SIPF_DOCKED     0x00000002
#define SIPF_LOCKED     0x00000004

BOOL WINAPI SipShowIM(DWORD dwFlags);
BOOL WINAPI SipGetInfo(SIPINFO *pSipInfo);
BOOL WINAPI SipSetInfo(SIPINFO *pSipInfo);
BOOL WINAPI SipRegisterNotification(HWND hWnd);

#ifdef __cplusplus
}
#endif

#endif /* _SIPAPI_H_ */
