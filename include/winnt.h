/*
 * wince-api: Clean-room Windows CE API implementation for LLVM/Clang
 * File: winnt.h
 *
 * System types, CPU architecture constants, security, Unicode, and SEH definitions.
 */

#ifndef _WINNT_H_
#define _WINNT_H_

#include <sdkddkver.h>
#include <windef.h>

#ifndef wchar_t
typedef unsigned short wchar_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Character and String Types */
typedef char                CHAR;
typedef unsigned short      WCHAR;
typedef unsigned char       UCHAR;
typedef unsigned short      USHORT;
typedef unsigned long       ULONG;

typedef CHAR                *PCHAR, *LPSTR, *PSTR;
typedef const CHAR          *LPCSTR, *PCSTR;

typedef WCHAR               *PWCHAR, *LPWSTR, *PWSTR;
typedef const WCHAR         *LPCWSTR, *PCWSTR;

typedef WCHAR               TCHAR, *PTCHAR, *LPTSTR, *PTSTR;
typedef const WCHAR         *LPCTSTR, *PCTSTR;

typedef const CHAR          *CSSTR;

#define __TEXT(quote)       L##quote
#define TEXT(quote)         __TEXT(quote)

/* Signed and Unsigned Primitive Types */
typedef signed char         INT8, *PINT8;
typedef signed short        INT16, *PINT16;
typedef signed int          INT32, *PINT32;
typedef signed long long    INT64, *PINT64;

typedef unsigned char       UINT8, *PUINT8;
typedef unsigned short      UINT16, *PUINT16;
typedef unsigned int        UINT32, *PUINT32;
typedef unsigned long long  UINT64, *PUINT64;

typedef long                LONG, *PLONG, *LPLONG;
typedef unsigned long       ULONG, *PULONG, *LPULONG;
typedef long long           LONGLONG, *PLONGLONG;
typedef unsigned long long  ULONGLONG, *PULONGLONG;

/* Pointer-sized Handle and Status Types */
typedef ULONG_PTR           SHANDLE_PTR;

/* Large Integer Types */
typedef union _LARGE_INTEGER {
    struct {
        DWORD LowPart;
        LONG HighPart;
    } DUMMYSTRUCTNAME;
    struct {
        DWORD LowPart;
        LONG HighPart;
    } u;
    LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;

typedef union _ULARGE_INTEGER {
    struct {
        DWORD LowPart;
        DWORD HighPart;
    } DUMMYSTRUCTNAME;
    struct {
        DWORD LowPart;
        DWORD HighPart;
    } u;
    ULONGLONG QuadPart;
} ULARGE_INTEGER, *PULARGE_INTEGER;

/* Processor Architecture Definitions */
#if defined(__arm__) || defined(_ARM_) || defined(__ARM_ARCH)
#ifndef _ARM_
#define _ARM_
#endif
#define PROCESSOR_ARM_ARM720        820
#define PROCESSOR_ARM_ARM820        821
#define PROCESSOR_ARM_ARM920        822
#define PROCESSOR_ARM_STRONGARM     2577
#define PROCESSOR_ARCHITECTURE_ARM  5
#endif

#ifndef VOID
#define VOID void
typedef void *PVOID;
#endif

#define C_ASSERT(e) typedef char __C_ASSERT__[(e) ? 1 : -1]

/* Handle Constants */
#define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)

/* Memory Access Rights */
#define DELETE                           (0x00010000L)
#define READ_CONTROL                     (0x00020000L)
#define WRITE_DAC                        (0x00040000L)
#define WRITE_OWNER                      (0x00080000L)
#define SYNCHRONIZE                      (0x00100000L)

#define STANDARD_RIGHTS_REQUIRED         (0x000F0000L)
#define STANDARD_RIGHTS_READ             (READ_CONTROL)
#define STANDARD_RIGHTS_WRITE            (READ_CONTROL)
#define STANDARD_RIGHTS_EXECUTE          (READ_CONTROL)
#define STANDARD_RIGHTS_ALL              (0x001F0000L)
#define SPECIFIC_RIGHTS_ALL              (0x0000FFFFL)

#define GENERIC_READ                     (0x80000000L)
#define GENERIC_WRITE                    (0x40000000L)
#define GENERIC_EXECUTE                  (0x20000000L)
#define GENERIC_ALL                      (0x10000000L)

/* Page Allocation & Protection Attributes */
#define PAGE_NOACCESS          0x01
#define PAGE_READONLY          0x02
#define PAGE_READWRITE         0x04
#define PAGE_WRITECOPY         0x08
#define PAGE_EXECUTE           0x10
#define PAGE_EXECUTE_READ      0x20
#define PAGE_EXECUTE_READWRITE 0x40
#define PAGE_EXECUTE_WRITECOPY 0x80
#define PAGE_GUARD             0x100
#define PAGE_NOCACHE           0x200

#define MEM_COMMIT           0x1000
#define MEM_RESERVE          0x2000
#define MEM_DECOMMIT         0x4000
#define MEM_RELEASE          0x8000
#define MEM_FREE            0x10000
#define MEM_PRIVATE         0x20000
#define MEM_MAPPED          0x40000
#define MEM_RESET           0x80000
#define MEM_TOP_DOWN       0x100000

/* Status Values and HRESULT */
typedef LONG HRESULT;
typedef LONG SCODE;

#define SUCCEEDED(hr) (((HRESULT)(hr)) >= 0)
#define FAILED(hr)    (((HRESULT)(hr)) < 0)

#define S_OK          ((HRESULT)0x00000000L)
#define S_FALSE       ((HRESULT)0x00000001L)
#define E_UNEXPECTED  ((HRESULT)0x8000FFFFL)
#define E_NOTIMPL     ((HRESULT)0x80004001L)
#define E_OUTOFMEMORY ((HRESULT)0x8007000EL)
#define E_INVALIDARG  ((HRESULT)0x80070057L)
#define E_NOINTERFACE ((HRESULT)0x80004002L)
#define E_POINTER     ((HRESULT)0x80004003L)
#define E_HANDLE      ((HRESULT)0x80070006L)
#define E_ABORT       ((HRESULT)0x80004004L)
#define E_FAIL        ((HRESULT)0x80004005L)
#define E_ACCESSDENIED ((HRESULT)0x80070005L)

/* Critical Section Definition */
typedef struct _CRITICAL_SECTION {
    unsigned int LockCount;
    unsigned int RecursionCount;
    HANDLE OwnerThread;
    HANDLE LockSemaphore;
    DWORD Reserved;
} CRITICAL_SECTION, *PCRITICAL_SECTION, *LPCRITICAL_SECTION;

#ifdef __cplusplus
}
#endif

#endif /* _WINNT_H_ */
