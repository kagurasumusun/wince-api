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

/* ms889597 "FILE_NOTIFY_INFORMATION (Windows CE 5.0)": record
 * describing one file-system change, returned by
 * CeGetFileNotificationInfo.  CE 1.01+; Header Winnt.h per the page.
 * NextEntryOffset 0 marks the last record; Action is one of the
 * FILE_ACTION_* values; FileName is a variable-length array. */
typedef struct _FILE_NOTIFY_INFORMATION {
    DWORD NextEntryOffset;   /* bytes to the next record; 0 = last */
    DWORD Action;            /* FILE_ACTION_* change type */
    DWORD FileNameLength;    /* FileName length, in bytes */
    WCHAR FileName[1];       /* variable-length file name */
} FILE_NOTIFY_INFORMATION, *PFILE_NOTIFY_INFORMATION;

/* Change-action codes for the FILE_NOTIFY_INFORMATION Action member
 * (names per ms889597; numeric values are the fixed Win32 ABI
 * values of the official File Management FILE_ACTION_* reference). */
#define FILE_ACTION_ADDED            1
#define FILE_ACTION_REMOVED          2
#define FILE_ACTION_MODIFIED         3
#define FILE_ACTION_RENAMED_OLD_NAME 4
#define FILE_ACTION_RENAMED_NEW_NAME 5

/* ms886752 "MEMORY_BASIC_INFORMATION (Windows CE 5.0)": page-range
 * report filled by VirtualQuery.  CE 1.0+; Header Winnt.h (per the
 * page).  CE 32-bit layout: two pointers + six DWORDs = 32 bytes.
 * State = MEM_COMMIT/MEM_FREE/MEM_RESERVE; Type =
 * MEM_IMAGE/MEM_MAPPED/MEM_PRIVATE. */
/* Language/locale id macros (official NLS pages, Header row Winnt.h).
 * ms906230 prints the PRIMARYLANGID formula and ms906441 the
 * SUBLANGID formula verbatim: primary id = low 10 bits of the LANGID,
 * sublanguage id = the upper 6 bits (bits 10-15).  MAKELANGID is the
 * documented inverse (ms906225) and MAKELCID (ms906226) packs a sort
 * id into the high 16 bits of the LCID.  Macro argument evaluation is
 * standard-practice (parens around every use). */
#define PRIMARYLANGID(lgid) ((WORD) (lgid) & 0x3ff)
#define SUBLANGID(lgid)     ((WORD) (lgid) >> 10)
#define MAKELANGID(p, s)    ((((WORD) (s)) << 10) | (WORD) (p))
#define MAKELCID(lgid, srtid) \
    ((LCID) ((((DWORD) (srtid)) << 16) | ((DWORD) (lgid))))

typedef struct _MEMORY_BASIC_INFORMATION {
    PVOID  BaseAddress;       /* base address of the region */
    PVOID  AllocationBase;    /* base of the VirtualAlloc range */
    DWORD  AllocationProtect; /* protection at allocation time */
    DWORD  RegionSize;        /* size of the region, in bytes */
    DWORD  State;             /* MEM_COMMIT / MEM_FREE / MEM_RESERVE */
    DWORD  Protect;           /* current access protection */
    DWORD  Type;              /* MEM_IMAGE / MEM_MAPPED / MEM_PRIVATE */
} MEMORY_BASIC_INFORMATION, *PMEMORY_BASIC_INFORMATION;

#ifdef __cplusplus
}
#endif

/* ------------------------------------------------------------------ */
/* M24: structured exception handling base types (Exception Reference)*/
/* ------------------------------------------------------------------ */

/* ms885216 "EXCEPTION_RECORD (Windows CE 5.0)": machine-independent
 * description of an exception (filled by GetExceptionInformation).
 * CE 1.0+; Winnt.h.  The page prints ExceptionInformation as a DWORD
 * array bounded by EXCEPTION_MAXIMUM_PARAMETERS (the bound symbol is
 * used by RaiseException ms886790 too; its value is the fixed Win32
 * ABI 15 -- no CE page prints a number for it). */
#define EXCEPTION_MAXIMUM_PARAMETERS 15   /* Win32 ABI array bound */
typedef struct _EXCEPTION_RECORD {
    DWORD  ExceptionCode;                 /* type of exception */
    DWORD  ExceptionFlags;                /* continuable or not */
    struct _EXCEPTION_RECORD *ExceptionRecord; /* chained record */
    PVOID  ExceptionAddress;              /* address of the exception */
    DWORD  NumberParameters;              /* count in the tail array */
    DWORD  ExceptionInformation[EXCEPTION_MAXIMUM_PARAMETERS];
} EXCEPTION_RECORD;
typedef EXCEPTION_RECORD *PEXCEPTION_RECORD; /* type used by
    EXCEPTION_POINTERS (ms885215) */

/* Exception-code names listed by ms885620 (GetExceptionCode) for the
 * exceptions most likely from common programming errors.  The names
 * are that CE page's list; the numeric values are the fixed Win32 ABI
 * codes of the desktop exception reference (recorded provenance). */
#define EXCEPTION_ACCESS_VIOLATION         0xC0000005L
#define EXCEPTION_BREAKPOINT               0x80000003L
#define EXCEPTION_DATATYPE_MISALIGNMENT    0x80000002L
#define EXCEPTION_SINGLE_STEP              0x80000004L
#define EXCEPTION_ARRAY_BOUNDS_EXCEEDED    0xC000008CL
#define EXCEPTION_FLT_DENORMAL_OPERAND     0xC000008DL
#define EXCEPTION_FLT_DIVIDE_BY_ZERO       0xC000008EL
#define EXCEPTION_FLT_INEXACT_RESULT       0xC000008FL
#define EXCEPTION_FLT_INVALID_OPERATION    0xC0000090L
#define EXCEPTION_FLT_OVERFLOW             0xC0000091L
#define EXCEPTION_FLT_STACK_CHECK          0xC0000092L
#define EXCEPTION_FLT_UNDERFLOW            0xC0000093L
#define EXCEPTION_INT_DIVIDE_BY_ZERO       0xC0000094L
#define EXCEPTION_INT_OVERFLOW             0xC0000095L
#define EXCEPTION_PRIV_INSTRUCTION         0xC0000096L
#define EXCEPTION_NONCONTINUABLE_EXCEPTION 0xC0000025L

/* ms886790 "RaiseException (Windows CE 5.0)": dwExceptionFlags is
 * zero (continuable) or EXCEPTION_NONCONTINUABLE; continuing a
 * noncontinuable exception raises EXCEPTION_NONCONTINUABLE_EXCEPTION.
 * Fixed Win32 ABI flag values. */
#define EXCEPTION_CONTINUABLE      0x00000000L
#define EXCEPTION_NONCONTINUABLE   0x00000001L

/* ms885174 "CONTEXT (Windows CE 5.0)": processor-specific register
 * data (Intel/MIPS/Alpha/SHx/ARM).  The page says the definitions
 * live in the Winnt.h *header file* -- no layout is published on the
 * documentation pages -- so only an incomplete type is provided here
 * (usable by pointer, as PCONTEXT in EXCEPTION_POINTERS ms885215). */
typedef struct _CONTEXT CONTEXT;
typedef CONTEXT *PCONTEXT;

#endif /* AKARI_WINNT_H */
