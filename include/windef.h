/*
 * windef.h -- base types and macros for Windows CE (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Spec basis: official Microsoft Windows CE
 * documentation (CE-era MSDN pages on learn.microsoft.com, served as
 * the (v=msdn.10) "Windows Embedded / MSDN archive") and the verified
 * WinCE toolchain ABI (kagurasumusun/llvm-project, branch LLVM-WinCE).
 * No code from w32api, mingwrt, mingw32ce, MinGW-w64 or any other
 * third-party tree appears here.
 *
 * Conventions documented by the CE pages and the verified toolchain:
 *   - Windows CE is Unicode-only (each wide API's CE page states
 *     "Windows CE supports only the Unicode version"); TCHAR maps to
 *     WCHAR unconditionally.
 *   - CE calling convention: Microsoft documents CE functions as
 *     __cdecl and CE x86 export names carry no @n decoration (verified
 *     import surface: undecorated __imp_<name>), so WINAPI/APIENTRY/
 *     CALLBACK expand to nothing.  On ARM __cdecl and __stdcall
 *     coincide anyway.
 *   - WCHAR is 16-bit (the CE wchar_t ABI of the toolchain target).
 */

#ifndef AKARI_WINDEF_H
#define AKARI_WINDEF_H

#include <stddef.h>   /* NULL, size_t */
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Calling conventions and decoration                                 */
/* ------------------------------------------------------------------ */

#define WINAPI        /* empty on Windows CE (see header note) */
#define APIENTRY      WINAPI
#define CALLBACK      WINAPI
#define WINAPIV       WINAPI   /* varargs public API (e.g. NKDbgPrintfW) */
#define STDMETHODCALLTYPE WINAPI

#define CONST const

/* ------------------------------------------------------------------ */
/* Fundamental types                                                  */
/* ------------------------------------------------------------------ */

typedef void            VOID;
typedef char            CHAR;       /* 8-bit character */
typedef uint16_t        WCHAR;      /* 16-bit Unicode character (CE ABI) */
typedef uint8_t         BYTE;
typedef uint16_t        WORD;
typedef uint32_t        DWORD;
typedef int32_t         LONG;
typedef uint32_t        ULONG;
typedef int             INT;
typedef unsigned int    UINT;
typedef int             BOOL;
typedef unsigned char   BYTE;   /* single byte (IsDBCSLeadByte pages) */
typedef BYTE           *LPBYTE; /* byte pointer (registry value data)  */
typedef WORD           *LPWORD; /* WORD pointer (GetStringType* arrays) */

/* Locale/language identifier types: LANGID = WORD, LCID = DWORD.
 * Base-level types so both winnt.h (MAKELANGID/MAKELCID macros) and
 * winnls.h can use them (official NLS pages, e.g. ms905298/ms905289). */
typedef WORD   LANGID;  /* language identifier (16-bit) */
typedef DWORD  LCID;    /* locale identifier (32-bit)   */

typedef int32_t         LONG_PTR;
typedef uint32_t        ULONG_PTR;
typedef uintptr_t       UINT_PTR;
typedef intptr_t        INT_PTR;

/* Fixed Win32-ABI integer typedefs used by CE documentation pages that
 * were not yet covered above (Network Address Translation Reference
 * pages, e.g. ms885188/ms885684/ms885685; debugging/driver pages use
 * the same ABI spellings).  All are plain fixed-width aliases. */
typedef unsigned char   UCHAR;    /* ms885188: "unsigned character"  */
typedef unsigned short  USHORT;   /* ms885188: "unsigned short"      */
typedef uint64_t        ULONG64;  /* ms885684 IP_NAT_SESSION_MAPPING_ */
                                   /* STATISTICS counter members      */
typedef unsigned char   BOOLEAN;  /* logical boolean (CE docs, e.g.  */
                                   /* ms886745 InboundConnection)     */
typedef ULONG          *PULONG;   /* ULONG pointer (ms886786)         */
typedef USHORT         *PUSHORT;  /* USHORT pointer (ms886786)        */
typedef UCHAR          *PUCHAR;   /* UCHAR pointer (ms885211)         */
typedef LONG            NTSTATUS; /* NT status result type (NAT pages)*/

typedef void           *LPVOID;
typedef const void     *LPCVOID;
typedef void           *PVOID;   /* generic pointer (Interlocked*Pointer) */
typedef CHAR           *LPSTR;
typedef const CHAR     *LPCSTR;
typedef WCHAR          *LPWSTR;
typedef const WCHAR    *LPCWSTR;
typedef DWORD *LPDWORD;
typedef DWORD *PDWORD;  /* DWORD pointer (VirtualProtect aa450980) */
typedef LONG  *PLONG;   /* signed-32-bit pointer (SetFilePointer ms891933) */
typedef LONG  *LPLONG;  /* LONG pointer (synchronization functions) */

/* MAX_PATH: default path length limit, cited by the CE CreateFile
 * (aa517318), FindFirstFile (ms889678) and GetFileAttributes
 * (ms890895) pages as the default string size limit for paths
 * (Win32 ABI value 260). */
#define MAX_PATH 260

/* Windows CE is Unicode-only: the generic-text forms are the wide ones. */
typedef WCHAR           TCHAR;
typedef WCHAR          *LPTSTR;
typedef const WCHAR    *LPCTSTR;
typedef BOOL           *LPBOOL;  /* BOOL pointer (WideCharToMultiByte aa450989) */

/* Handle types: opaque pointers (module base addresses on CE; a module
 * handle equals its base address per the CE DllMain documentation). */
typedef void           *HANDLE;
typedef HANDLE          HINSTANCE;
typedef HANDLE          HMODULE;
typedef HANDLE          HLOCAL;
typedef HANDLE          HGLOBAL;
typedef HANDLE         *LPHANDLE;  /* HANDLE pointer (DuplicateHandle ms885208) */

typedef UINT_PTR (WINAPI *FARPROC)(void);

#define FALSE 0
#define TRUE  1

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WINDEF_H */
