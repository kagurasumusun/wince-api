/*
 * winnt.h -- base NT-style types and helpers for Windows CE (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Basis: Microsoft's official data-type and
 * structure references (the 64-bit integer types and the
 * LARGE_INTEGER/ULARGE_INTEGER unions are the Win32 ABI forms
 * documented in Microsoft's official Windows Data Types /
 * LARGE_INTEGER reference; RTL_CRITICAL_SECTION members are the
 * layout Microsoft's official debugger documentation publishes:
 * DebugInfo pointer, LockCount, RecursionCount, OwningThread,
 * LockSemaphore, SpinCount at offsets 0x0/0x4/0x8/0xc/0x10/0x14 on
 * 32-bit targets).  Windows CE does not publish a separate layout for
 * the critical-section object, so the desktop-official layout is used
 * for source and binary compatibility and is recorded as such in
 * docs/inventory.md.  No third-party header text appears here.
 */

#ifndef AKARI_WINNT_H
#define AKARI_WINNT_H

#include "windef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* 64-bit integer types (Win32 ABI: 64-bit on all CE targets)         */
/* ------------------------------------------------------------------ */

typedef long long          LONGLONG;
typedef unsigned long long ULONGLONG;

/* LARGE_INTEGER: union used by the performance-counter and file-size
 * APIs (QueryPerformanceCounter ms891120, GetFileSizeEx and the
 * LARGE_INTEGER official structure reference).  The anonymous struct
 * exposes LowPart/HighPart directly. */
typedef union _LARGE_INTEGER {
    struct {
        DWORD LowPart;   /* low-order 32 bits */
        LONG  HighPart;  /* high-order 32 bits */
    };
    LONGLONG QuadPart;   /* the full 64-bit value */
} LARGE_INTEGER, *PLARGE_INTEGER;

typedef union _ULARGE_INTEGER {
    struct {
        DWORD LowPart;
        DWORD HighPart;
    };
    ULONGLONG QuadPart;
} ULARGE_INTEGER, *PULARGE_INTEGER;

/* ------------------------------------------------------------------ */
/* Critical section object                                            */
/* ------------------------------------------------------------------ */

/* Opaque debug record pointer (the debug structure itself is not
 * documented for public use; only the pointer is stored in
 * RTL_CRITICAL_SECTION). */
typedef struct _RTL_CRITICAL_SECTION_DEBUG RTL_CRITICAL_SECTION_DEBUG;
typedef RTL_CRITICAL_SECTION_DEBUG *PRTL_CRITICAL_SECTION_DEBUG;

/* RTL_CRITICAL_SECTION -- critical-section object layout.  Members
 * per Microsoft's official debugger reference (DebugInfo at 0x0,
 * LockCount at 0x4, RecursionCount at 0x8, OwningThread at 0xc,
 * LockSemaphore at 0x10, SpinCount at 0x14; 24 bytes on 32-bit).
 * Applications must treat the contents as opaque; the object is only
 * passed by address to the critical-section functions. */
typedef struct _RTL_CRITICAL_SECTION {
    PRTL_CRITICAL_SECTION_DEBUG DebugInfo;
    LONG                         LockCount;
    LONG                         RecursionCount;
    HANDLE                       OwningThread;
    HANDLE                       LockSemaphore;
    ULONG_PTR                    SpinCount;
} RTL_CRITICAL_SECTION, *PRTL_CRITICAL_SECTION;

typedef RTL_CRITICAL_SECTION CRITICAL_SECTION;
typedef PRTL_CRITICAL_SECTION PCRITICAL_SECTION;
typedef PCRITICAL_SECTION LPCRITICAL_SECTION;

/* SecureZeroMemory: writes zero bytes to a buffer without the
 * compiler being able to remove the store (official SecureZeroMemory
 * page; the function pages list Header: Winnt.h). */
#define SecureZeroMemory(pv, cb) do {                    \
    volatile unsigned char *_szm_p =                     \
        (volatile unsigned char *)(pv);                  \
    size_t _szm_i;                                       \
    for (_szm_i = 0; _szm_i < (cb); _szm_i++)            \
        _szm_p[_szm_i] = 0;                              \
} while (0)

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WINNT_H */
