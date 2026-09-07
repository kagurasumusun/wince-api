/*
 * wince-api: Clean-room Windows CE API implementation for LLVM/Clang
 * File: windef.h
 *
 * Fundamental Win32 / WinCE type definitions and basic macros.
 */

#ifndef _WINDEF_H_
#define _WINDEF_H_

#include <sdkddkver.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Standard Calling Conventions on ARM WinCE */
#ifndef __cdecl
#define __cdecl
#endif
#ifndef __stdcall
#define __stdcall
#endif
#ifndef __fastcall
#define __fastcall
#endif

#ifndef WINAPI
#define WINAPI __stdcall
#endif
#ifndef APIENTRY
#define APIENTRY WINAPI
#endif
#ifndef APIPRIVATE
#define APIPRIVATE __stdcall
#endif
#ifndef CALLBACK
#define CALLBACK __stdcall
#endif

#ifndef CDECL
#define CDECL __cdecl
#endif

/* Basic Constants */
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif
#ifndef OPTIONAL
#define OPTIONAL
#endif

/* Fundamental Types */
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef BOOL                *PBOOL;
typedef BOOL                *LPBOOL;
typedef BYTE                *PBYTE;
typedef BYTE                *LPBYTE;
typedef int                 *PINT;
typedef int                 *LPINT;
typedef WORD                *PWORD;
typedef WORD                *LPWORD;
typedef long                *LPLONG;
typedef DWORD               *PDWORD;
typedef DWORD               *LPDWORD;
typedef void                *LPVOID;
typedef const void          *LPCVOID;
typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;
typedef WORD                ATOM;

/* Pointer Sized Integer Types (32-bit architecture for ARM WinCE) */
typedef unsigned long       ULONG_PTR;
typedef long                LONG_PTR;
typedef unsigned int        UINT_PTR;
typedef int                 INT_PTR;
typedef ULONG_PTR           DWORD_PTR;

typedef UINT_PTR            WPARAM;
typedef LONG_PTR            LPARAM;
typedef LONG_PTR            LRESULT;

/* Helper Macros */
#define LOBYTE(w)           ((BYTE)(((DWORD_PTR)(w)) & 0xff))
#define HIBYTE(w)           ((BYTE)((((DWORD_PTR)(w)) >> 8) & 0xff))
#define LOWORD(l)           ((WORD)(((DWORD_PTR)(l)) & 0xffff))
#define HIWORD(l)           ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff))
#define MAKEWORD(a, b)      ((WORD)(((BYTE)(((DWORD_PTR)(a)) & 0xff)) | ((WORD)((BYTE)(((DWORD_PTR)(b)) & 0xff))) << 8))
#define MAKELONG(a, b)      ((long)(((WORD)(((DWORD_PTR)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xffff))) << 16))
#define MAKELPARAM(l, h)    ((LPARAM)MAKELONG(l, h))
#define MAKELRESULT(l, h)   ((LRESULT)MAKELONG(l, h))
#define MAKEWPARAM(l, h)    ((WPARAM)MAKELONG(l, h))

#define MAX_PATH 260

/* Handles */
typedef void *HANDLE;
typedef HANDLE *PHANDLE;
typedef HANDLE *LPHANDLE;

#define DECLARE_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name

DECLARE_HANDLE(HWND);
DECLARE_HANDLE(HHOOK);
DECLARE_HANDLE(HEVENT);
DECLARE_HANDLE(HKEY);
typedef HKEY *PHKEY;
DECLARE_HANDLE(HMENU);
DECLARE_HANDLE(HICON);
DECLARE_HANDLE(HCURSOR);
DECLARE_HANDLE(HBRUSH);
DECLARE_HANDLE(HFONT);
DECLARE_HANDLE(HBITMAP);
DECLARE_HANDLE(HDC);
DECLARE_HANDLE(HRGN);
DECLARE_HANDLE(HPALETTE);
DECLARE_HANDLE(HPEN);
DECLARE_HANDLE(HMODULE);
typedef HMODULE HINSTANCE;
DECLARE_HANDLE(HTASK);
DECLARE_HANDLE(HGDIOBJ);
DECLARE_HANDLE(HGLOBAL);
DECLARE_HANDLE(HLOCAL);

typedef int (WINAPI *FARPROC)();
typedef int (WINAPI *NEARPROC)();
typedef int (WINAPI *PROC)();

/* Basic Point, Size, and Rect Structures */
typedef struct tagRECT {
    long left;
    long top;
    long right;
    long bottom;
} RECT, *PRECT, *NPRECT, *LPRECT;

typedef const RECT *LPCRECT;

typedef struct _RECTL {
    long left;
    long top;
    long right;
    long bottom;
} RECTL, *PRECTL, *LPRECTL;

typedef struct tagPOINT {
    long x;
    long y;
} POINT, *PPOINT, *NPPOINT, *LPPOINT;

typedef struct tagSIZE {
    long cx;
    long cy;
} SIZE, *PSIZE, *LPSIZE;

typedef SIZE SIZEL;
typedef SIZE *PSIZEL, *LPSIZEL;

#ifdef __cplusplus
}
#endif

#endif /* _WINDEF_H_ */
