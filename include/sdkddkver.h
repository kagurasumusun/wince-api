/*
 * wince-api: Clean-room Windows CE API implementation for LLVM/Clang
 * File: sdkddkver.h
 *
 * Windows CE SDK version definitions.
 * Documented version macros for Windows CE 4.x, 5.x, 6.x.
 */

#ifndef _SDKDDKVER_H_
#define _SDKDDKVER_H_

/* Windows CE Version Identifiers */
#define _WIN32_WCE_CE300    0x0300
#define _WIN32_WCE_CE400    0x0400
#define _WIN32_WCE_CE410    0x0410
#define _WIN32_WCE_CE420    0x0420
#define _WIN32_WCE_CE500    0x0500
#define _WIN32_WCE_CE501    0x0501
#define _WIN32_WCE_CE600    0x0600
#define _WIN32_WCE_CE700    0x0700

/* Default Windows CE Target Version if not explicitly defined */
#ifndef _WIN32_WCE
#define _WIN32_WCE 0x0500
#endif

/* WINVER mapping for WinCE compatibility */
#ifndef WINVER
#if (_WIN32_WCE >= 0x0600)
#define WINVER 0x0600
#elif (_WIN32_WCE >= 0x0500)
#define WINVER 0x0500
#else
#define WINVER 0x0400
#endif
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT WINVER
#endif

#endif /* _SDKDDKVER_H_ */
