/*
 * winbase.h -- base OS API declarations for Windows CE (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (CE-era MSDN pages, learn.microsoft.com previous-versions archive,
 * IDs of the form msnnnnnn / aannnnnn under (v=msdn.10)); the
 * per-page "Requirements" lines (OS Versions / Header / Link Library)
 * are transcribed in docs/inventory.md.  No third-party header text is
 * used.
 *
 * Naming: Windows CE exports the wide spellings (GetModuleHandleW,
 * GetModuleFileNameW, GetCommandLineW, GetProcAddressW) and, for
 * GetProcAddress, also the ASCII spelling from CE 3.0 on; the base
 * names are provided as macros mapping to the wide forms, which is the
 * mapping the CE documentation describes ("Windows CE supports only
 * the Unicode version of this function").
 */

#ifndef AKARI_WINBASE_H
#define AKARI_WINBASE_H

#include "windef.h"
#include "winnt.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Process and thread termination                                     */
/* ------------------------------------------------------------------ */

/* ExitProcess is declared in windows.h: ms885217 lists Header:
 * Windows.h for it (see there for the export-surface conflict note). */

/* aa450927 "TerminateProcess (Windows CE 5.0)":
 * BOOL TerminateProcess(HANDLE, DWORD).  CE 1.0+; Winbase.h;
 * Coredll.lib.  Unconditionally ends the process; the exit path of
 * the companion CRT (wince-crt) uses it with the current-process
 * pseudo-handle. */
BOOL TerminateProcess(HANDLE hProcess, DWORD uExitCode);

/* ms885219 "ExitThread (Windows CE 5.0)": VOID ExitThread(DWORD).
 * CE 1.0+; Winbase.h; Coredll.lib. */
VOID ExitThread(DWORD dwExitCode);

/* aa450930 "TerminateThread (Windows CE 5.0)":
 * BOOL TerminateThread(HANDLE, DWORD).  CE 1.01+; Winbase.h;
 * Coredll.lib. */
BOOL TerminateThread(HANDLE hThread, DWORD dwExitCode);

/* ------------------------------------------------------------------ */
/* Module management                                                  */
/* ------------------------------------------------------------------ */

/* ms885630 "GetModuleHandle (Windows CE 5.0)":
 * HMODULE GetModuleHandle(LPCTSTR).  CE 2.10+; Winbase.h;
 * Coredll.lib (page lists "Coredll.lib, Nk.lib").  NULL returns a
 * pseudo-handle of the current process.  Export is GetModuleHandleW
 * (verified import surface; CE is Unicode-only). */
HMODULE GetModuleHandleW(LPCWSTR lpModuleName);
#define GetModuleHandle GetModuleHandleW

/* ms885629 "GetModuleFileName (Windows CE 5.0)":
 * DWORD GetModuleFileName(HMODULE, LPWSTR, DWORD).  CE 2.0+;
 * Winbase.h; Coredll.lib.  nSize is in characters; NULL hModule asks
 * for the calling process's file.  Export is GetModuleFileNameW. */
DWORD GetModuleFileNameW(HMODULE hModule, LPWSTR lpFilename,
                         DWORD nSize);
#define GetModuleFileName GetModuleFileNameW

/* ------------------------------------------------------------------ */
/* Command line                                                       */
/* ------------------------------------------------------------------ */

/* ms885605 "GetCommandLine (Windows CE 5.0)":
 * LPTSTR GetCommandLine(void).  CE 3.0+; Winbase.h; Coredll.lib.
 * Remarks: "Windows CE supports only the Unicode version of this
 * function."  Export is GetCommandLineW. */
LPWSTR GetCommandLineW(void);
#define GetCommandLine GetCommandLineW

/* ------------------------------------------------------------------ */
/* Dynamic-link resolution                                            */
/* ------------------------------------------------------------------ */

/* ms885634 "GetProcAddress (Windows CE 5.0)":
 * FARPROC GetProcAddress(HMODULE, LPCWSTR) -- lpProcName is Unicode;
 * CE 1.0+; Winbase.h; Coredll.lib.  Remarks: "For Windows CE 3.0 and
 * later, the ASCII version of this function, GetProcAddressA, is
 * supported."  Both exports are present in the CE 4/5/6 import
 * libraries (verified).  Base name maps to the W form. */
FARPROC GetProcAddressW(HMODULE hModule, LPCWSTR lpProcName);
FARPROC GetProcAddressA(HMODULE hModule, LPCSTR lpProcName);
#define GetProcAddress GetProcAddressW

/* ------------------------------------------------------------------ */
/* Local memory                                                        */
/* ------------------------------------------------------------------ */

/* ms886739 "LocalAlloc (Windows CE 5.0)":
 * HLOCAL LocalAlloc(UINT, UINT).  CE 1.0+; Winbase.h; Coredll.lib.
 * Page notes: "In the linear Windows CE API environment, there is no
 * difference between the local heap and the global heap"; flags:
 * LMEM_FIXED allocates fixed memory, LMEM_ZEROINIT initializes to
 * zero, LPTR combines both; NULL means failure.  Flag values below
 * are the documented Win32 ABI values (Microsoft's official
 * memory-management reference). */

/* LMEM_MOVEABLE and LMEM_MODIFY are named (with the behaviour above)
 * by the LocalReAlloc page ms886742; numeric values are the Win32
 * ABI values from Microsoft's official memory-management reference
 * (LMEM_MODIFY applies to LocalReAlloc's fuFlags only). */
#define LMEM_FIXED     0x0000u
#define LMEM_MOVEABLE  0x0002u
#define LMEM_ZEROINIT  0x0040u
#define LMEM_MODIFY    0x0080u
#define LPTR           (LMEM_FIXED | LMEM_ZEROINIT)

HLOCAL LocalAlloc(UINT uFlags, UINT uBytes);

/* ms886741 "LocalFree (Windows CE 5.0)": HLOCAL LocalFree(HLOCAL).
 * CE 1.0+; Winbase.h; Coredll.lib.  Page notes: return value NULL
 * indicates success (a handle indicates failure); freeing NULL is
 * ignored and returns NULL. */
HLOCAL LocalFree(HLOCAL hMem);

/* ------------------------------------------------------------------ */
/* Error handling                                                      */
/* ------------------------------------------------------------------ */

/* ms885627 "GetLastError (Windows CE 5.0)": DWORD GetLastError(void).
 * CE 1.0+; Winbase.h; "Coredll.lib, Nk.lib".  Per-thread last error;
 * error codes are 32-bit values, bit 29 reserved for application
 * codes.  The page points to the official *Error Values* page
 * (aa450740) and the SDK header WINERROR.H for the code list; those
 * constants land in a later batch (winerror.h) transcribed from
 * aa450740. */
DWORD GetLastError(void);

/* ------------------------------------------------------------------ */
/* Process and thread creation                                        */
/* ------------------------------------------------------------------ */

/* On Windows CE the security/startup parameters of CreateProcess and
 * CreateThread are NOT supported and must be NULL/FALSE (documented
 * per page, below); the structures are therefore left as opaque tags
 * here (pointer use compiles, instantiation is impossible) until
 * their official structure pages are processed into a later batch.
 * PROCESS_INFORMATION is the one real output structure and is fully
 * defined below (fields per the official PROCESS_INFORMATION page,
 * ms886775, referenced by the CreateProcess page). */

typedef struct _SECURITY_ATTRIBUTES SECURITY_ATTRIBUTES;
typedef SECURITY_ATTRIBUTES *LPSECURITY_ATTRIBUTES;
/* CE: "Not supported; set to NULL" (ms885182). */

typedef struct _STARTUPINFOW STARTUPINFOW;
typedef STARTUPINFOW *LPSTARTUPINFOW;
/* CE: "Not supported; set to NULL" (ms885182). */

typedef struct _PROCESS_INFORMATION {
    HANDLE hProcess;    /* process handle, PROCESS_ALL_ACCESS */
    HANDLE hThread;     /* primary-thread handle, THREAD_ALL_ACCESS */
    DWORD  dwProcessId; /* 32-bit process identifier */
    DWORD  dwThreadId;  /* 32-bit thread identifier */
} PROCESS_INFORMATION, *LPPROCESS_INFORMATION;

/* Thread entry type (CreateThread ms885186; the ThreadProc page is
 * aa450940). */
typedef DWORD (WINAPI *LPTHREAD_START_ROUTINE)(LPVOID lpvThreadParam);

/* ms885186 "CreateThread (Windows CE 5.0)":
 * HANDLE CreateThread(LPSECURITY_ATTRIBUTES, DWORD,
 *                     LPTHREAD_START_ROUTINE, LPVOID, DWORD, LPDWORD).
 * CE 1.01+; Winbase.h; Coredll.lib.  CE notes: lpsa ignored, must be
 * NULL; cbStack ignored unless STACK_SIZE_PARAM_IS_A_RESERVATION
 * (a CE-only flag); default reservation 64 KB; NULL return on
 * failure; flag values are transcribed with the official constants
 * batch. */
HANDLE CreateThread(LPSECURITY_ATTRIBUTES lpsa, DWORD cbStack,
                    LPTHREAD_START_ROUTINE lpStartAddr,
                    LPVOID lpvThreadParam, DWORD fdwCreate,
                    LPDWORD lpIDThread);

/* ms885182 "CreateProcess (Windows CE 5.0)":
 * BOOL CreateProcess(LPCWSTR pszImageName, LPCWSTR pszCmdLine,
 *                    LPSECURITY_ATTRIBUTES psaProcess,
 *                    LPSECURITY_ATTRIBUTES psaThread,
 *                    BOOL fInheritHandles, DWORD fdwCreate,
 *                    LPVOID pvEnvironment, LPWSTR pszCurDir,
 *                    LPSTARTUPINFOW psiStartInfo,
 *                    LPPROCESS_INFORMATION pProcInfo).
 * CE 1.0+; Winbase.h; Coredll.lib.  CE notes: image name must be
 * non-NULL and name the module; psaProcess/psaThread/fInheritHandles/
 * pvEnvironment/pszCurDir/psiStartInfo are not supported (NULL/FALSE);
 * pszCmdLine NULL means the image name is used as the command line;
 * ".EXE" is appended when the name has no extension; CE has no
 * priority classes; search order: \windows, root, OEM dir (and
 * \ceshell from CE 2.10); do not call from DllMain.  Export is
 * CreateProcessW. */
BOOL CreateProcessW(LPCWSTR pszImageName, LPCWSTR pszCmdLine,
                    LPSECURITY_ATTRIBUTES psaProcess,
                    LPSECURITY_ATTRIBUTES psaThread,
                    BOOL fInheritHandles, DWORD fdwCreate,
                    LPVOID pvEnvironment, LPWSTR pszCurDir,
                    LPSTARTUPINFOW psiStartInfo,
                    LPPROCESS_INFORMATION pProcInfo);
#define CreateProcess CreateProcessW

/* ------------------------------------------------------------------ */
/* Dynamic loading of modules (LoadLibrary/FreeLibrary)               */
/* ------------------------------------------------------------------ */

/* ms886736 "LoadLibrary (Windows CE 5.0)": HINSTANCE
 * LoadLibrary(LPCTSTR).  CE 1.0+; Winbase.h; Coredll.lib.  CE notes:
 * a DLL is loaded once and mapped per process; module names ignore
 * paths (name collisions load the first); ".cpl" is treated as
 * ".dll"; default extension ".dll" is appended; search order:
 * explicit path, .exe launch directory, \windows, ROM, OEM path;
 * registry HKEY_LOCAL_MACHINE\Loader\SystemPath (<= 260 chars) adds
 * search paths; not safe from DllMain.  Export is LoadLibraryW. */
HINSTANCE LoadLibraryW(LPCWSTR lpLibFileName);
#define LoadLibrary LoadLibraryW

/* ms885601 "FreeLibrary (Windows CE 5.0)": BOOL FreeLibrary(HMODULE).
 * CE 1.0+; Winbase.h; Coredll.lib.  Decrements the per-process
 * reference count; at zero the system calls DllMain with
 * DLL_PROCESS_DETACH before unmapping; not safe from DllMain. */
BOOL FreeLibrary(HMODULE hLibModule);

/* ------------------------------------------------------------------ */
/* Handles, process queries                                           */
/* ------------------------------------------------------------------ */

/* aa517300 "CloseHandle (Windows CE 5.0)": BOOL CloseHandle(HANDLE).
 * CE 1.0+; Winbase.h; Coredll.lib.  Closes handles to files, events,
 * mutexes, processes, threads, sockets, etc.; does not terminate a
 * thread. */
BOOL CloseHandle(HANDLE hObject);

/* ms886766 "OpenProcess (Windows CE 5.0)":
 * HANDLE OpenProcess(DWORD, BOOL, DWORD).  CE 2.0+; Winbase.h;
 * Coredll.lib.  CE notes: fdwAccess "Not supported; set to zero";
 * fInherit "Not supported; set to FALSE". */
HANDLE OpenProcess(DWORD fdwAccess, BOOL fInherit, DWORD IDProcess);

/* ms885622 "GetExitCodeProcess (Windows CE 5.0)":
 * BOOL GetExitCodeProcess(HANDLE, LPDWORD).  CE 2.0+; Winbase.h;
 * Coredll.lib.  STILL_ACTIVE (winerror.h) is returned while the
 * process runs; after termination the status is the ExitProcess/
 * TerminateProcess exit value, the return value of the process's
 * main/WinMain, or an exception value. */
BOOL GetExitCodeProcess(HANDLE hProcess, LPDWORD lpExitCode);

/* ms886817 "SetLastError (Windows CE 5.0)": VOID
 * SetLastError(DWORD).  CE 1.0+; Winbase.h; Coredll.lib.  Last-error
 * code is per-thread (thread local storage); error codes are 32-bit,
 * bit 29 reserved for application-defined codes. */
VOID SetLastError(DWORD dwErrCode);

/* ------------------------------------------------------------------ */
/* Thread scheduling (Suspend/Resume, exit status)                    */
/* ------------------------------------------------------------------ */

/* aa450913 "SuspendThread (Windows CE 5.0)":
 * DWORD SuspendThread(HANDLE).  CE 1.0+; Winbase.h; Coredll.lib.
 * Suspends the thread and increments its suspend count (max
 * MAXIMUM_SUSPEND_COUNT); previous suspend count is returned,
 * 0xFFFFFFFF on failure.  CE note: suspending a thread that is
 * making a kernel call fails -- the call may need to be repeated. */
DWORD SuspendThread(HANDLE hThread);

/* ms886801 "ResumeThread (Windows CE 5.0)": DWORD
 * ResumeThread(HANDLE).  CE 1.0+; Winbase.h; Coredll.lib.
 * Decrements the suspend count; resumes execution when it reaches
 * zero.  Return: previous suspend count; 0xFFFFFFFF on failure;
 * 0 = the thread was not suspended; 1 = suspended, now running. */
DWORD ResumeThread(HANDLE hThread);

/* ms885623 "GetExitCodeThread (Windows CE 5.0)":
 * BOOL GetExitCodeThread(HANDLE, LPDWORD).  CE 1.01+; Winbase.h;
 * Coredll.lib.  STILL_ACTIVE while the thread runs; after
 * termination the status is the ExitThread/TerminateThread exit
 * value, the return value of the thread function, or the exit value
 * of the thread's process. */
BOOL GetExitCodeThread(HANDLE hThread, LPDWORD lpExitCode);

/* aa450900 "Sleep (Windows CE 5.0)": VOID Sleep(DWORD).  CE 1.0+;
 * Winbase.h; Coredll.lib.  Suspends the current thread for the
 * given number of milliseconds.  dwMilliseconds zero relinquishes
 * the rest of the time slice; INFINITE delays forever.  CE note:
 * Sleep(INFINITE) equals SuspendThread(GetCurrentThread()) -- the
 * thread remains resumable via ResumeThread, unlike on desktop. */
VOID Sleep(DWORD dwMilliseconds);

/* INFINITE: infinite-delay constant, cited by the CE Sleep page
 * (aa450900); value per the Win32 ABI. */
#define INFINITE 0xFFFFFFFFu

/* Thread priority values (legacy functions).  aa450596 "Priority
 * Levels": CE 3.0+ has 256 levels, 0 = highest, 255 = lowest;
 * application threads use levels 248-255, which are the mapping of
 * the original 8 levels (0-7) of CE 2.12 and earlier.  The legacy
 * GetThreadPriority/SetThreadPriority operate on that original
 * 8-level scale (aa450596: "the functions have access only to the
 * original 8 priority levels"), so the THREAD_PRIORITY_* constants
 * are the old-scale numbers 0..7 with NORMAL = 3.  That is
 * consistent with the new-scale normal value 251 on ms885643 and
 * aa450891 because old level n maps to new level 248+n (aa450596:
 * the original eight levels are mapped to 255..248).  The relative
 * table on ms885643 then fixes TIME_CRITICAL (3 above NORMAL) = 0,
 * HIGHEST = 1, ABOVE_NORMAL = 2, BELOW_NORMAL = 4, LOWEST = 5,
 * ABOVE_IDLE = 6, IDLE (4 below NORMAL) = 7; values cross-checked
 * against the CeGCC tree (parity only). */
#define THREAD_PRIORITY_TIME_CRITICAL  0
#define THREAD_PRIORITY_HIGHEST        1
#define THREAD_PRIORITY_ABOVE_NORMAL   2
#define THREAD_PRIORITY_NORMAL         3
#define THREAD_PRIORITY_BELOW_NORMAL   4
#define THREAD_PRIORITY_LOWEST         5
#define THREAD_PRIORITY_ABOVE_IDLE     6
#define THREAD_PRIORITY_IDLE           7

/* THREAD_PRIORITY_ERROR_RETURN: GetThreadPriority failure value
 * (ms885643 names it; Win32 ABI value 0x7FFFFFFF = 2147483647). */
#define THREAD_PRIORITY_ERROR_RETURN   ((int)0x7FFFFFFF)

/* ms885643 "GetThreadPriority (Windows CE 5.0)":
 * int GetThreadPriority(HANDLE).  CE 1.0+; Winbase.h; Coredll.lib.
 * Returns the thread's base priority level; THREAD_PRIORITY_ERROR_
 * RETURN on failure.  CE has no priority classes; scheduling order
 * is determined by thread priority alone.  For real-time priorities
 * (0-247) use CeGetThreadPriority (aa450795) -- later batch. */
int GetThreadPriority(HANDLE hThread);

/* aa450891 "SetThreadPriority (Windows CE 5.0)":
 * BOOL SetThreadPriority(HANDLE, int).  CE 1.0+; Winbase.h;
 * Coredll.lib.  Sets the base priority level; nonzero on success.
 * All threads start at THREAD_PRIORITY_NORMAL.  No priority
 * classes on CE.  Real-time range via CeSetThreadPriority
 * (ms885155) -- later batch. */
BOOL SetThreadPriority(HANDLE hThread, int nPriority);

/* ------------------------------------------------------------------ */
/* Thread local storage (TLS)                                         */
/* ------------------------------------------------------------------ */

/* aa450945 "TlsAlloc (Windows CE 5.0)": DWORD TlsAlloc(void).
 * CE 1.0+; Header listed as Winuser.h on the page; Coredll.lib.
 * Returns a TLS index; 0xFFFFFFFF (TLS_OUT_OF_INDEXES) on failure.
 * TLS indexes are not valid across process boundaries; typical use:
 * allocate at process/DLL attach, TlsSetValue per thread, TlsFree at
 * process detach.  TLS_MINIMUM_AVAILABLE is guaranteed at least 64. */
DWORD TlsAlloc(void);

/* aa450947 "TlsFree (Windows CE 5.0)": BOOL TlsFree(DWORD).
 * CE 1.0+; Winbase.h; Coredll.lib.  Releases a TLS index for reuse;
 * does NOT free dynamic storage stored in the slot (free it first);
 * DLLs are expected to call it from their process-detach routine. */
BOOL TlsFree(DWORD dwTlsIndex);

/* aa450951 "TlsSetValue (Windows CE 5.0)":
 * BOOL TlsSetValue(DWORD, LPVOID).  CE 1.0+; Winbase.h; Coredll.lib.
 * Stores a value in the calling thread's TLS slot; slots are
 * initialized to NULL.  Minimal parameter validation: succeeds for
 * index 0 .. TLS_MINIMUM_AVAILABLE-1. */
BOOL TlsSetValue(DWORD dwTlsIndex, LPVOID lpTlsValue);

/* aa450949 "TlsGetValue (Windows CE 5.0)":
 * LPVOID TlsGetValue(DWORD).  CE 1.0+; Winbase.h; Coredll.lib.
 * Retrieves the calling thread's TLS slot value; a stored zero is
 * indistinguishable from failure, so on success the function clears
 * the thread's last error (GetLastError then returns NO_ERROR).
 * CE note: for CE 3.0 and later, NULL is returned when called before
 * TlsSetValue; on CE 1.0-2.12 the value is not guaranteed NULL. */
LPVOID TlsGetValue(DWORD dwTlsIndex);

/* TLS_MINIMUM_AVAILABLE: minimum number of TLS indexes per process.
 * The TlsAlloc page guarantees "at least 64"; the ABI value used by
 * the CE/Win32 runtimes is 64. */
#define TLS_MINIMUM_AVAILABLE 64

/* TLS_OUT_OF_INDEXES: TlsAlloc failure return (aa450945 documents
 * the failure value 0xFFFFFFFF). */
#define TLS_OUT_OF_INDEXES ((DWORD)0xFFFFFFFFu)

/* ------------------------------------------------------------------ */
/* Extended module loading (LoadLibraryEx)                            */
/* ------------------------------------------------------------------ */

/* ms886737 "LoadLibraryEx (Windows CE 5.0)":
 * HMODULE LoadLibraryEx(LPCTSTR, HANDLE, DWORD).  CE 3.0+; Winbase.h;
 * Coredll.lib.  hFile is reserved and must be NULL.  dwFlags = 0
 * behaves exactly like LoadLibrary.  CE-specific: a module is loaded
 * only once, so the dwFlags settings apply to all further loads of
 * the same module.  Because Windows CE is Unicode-only, the export
 * is LoadLibraryExW. */
HINSTANCE LoadLibraryExW(LPCWSTR lpLibFileName, HANDLE hFile,
                         DWORD dwFlags);
#define LoadLibraryEx LoadLibraryExW

/* LoadLibraryEx dwFlags (ms886737).  DONT_RESOLVE_DLL_REFERENCES
 * maps the DLL without calling DllMain and without loading its
 * imports; LOAD_LIBRARY_AS_DATAFILE maps the file as a data file
 * (implies DONT_RESOLVE_DLL_REFERENCES) for resource extraction;
 * LOAD_WITH_ALTERED_SEARCH_PATH is listed as "Windows CE: not
 * supported."  Values are the Win32 ABI constants given in
 * Microsoft's official LoadLibraryExW reference page. */
#define DONT_RESOLVE_DLL_REFERENCES   0x00000001u
#define LOAD_LIBRARY_AS_DATAFILE      0x00000002u
#define LOAD_WITH_ALTERED_SEARCH_PATH 0x00000008u

/* ------------------------------------------------------------------ */
/* File management                                                    */
/* ------------------------------------------------------------------ */

/* ms885586 "FILETIME (Windows CE 5.0)": 64-bit value counting
 * 100-nanosecond intervals since January 1, 1601; used by the file
 * time conversion functions.  CE 1.0+; Winbase.h. */
typedef struct _FILETIME {
    DWORD dwLowDateTime;   /* low 32 bits of the date/time value */
    DWORD dwHighDateTime;  /* upper 32 bits of the date/time value */
} FILETIME, *PFILETIME, *LPFILETIME;

/* ms892378 "WIN32_FIND_DATA (Windows CE 5.0)": filled by
 * FindFirstFile/FindNextFile.  CE 1.0+; Winbase.h.  CE layout per
 * the page: the file times are UTC (zero if the file system does
 * not support them), the size is nFileSizeHigh*2^32+nFileSizeLow,
 * dwOID is the object-store object identifier, cFileName is a
 * null-terminated name (long names appear in full).  Unlike the
 * desktop layout there is no cAlternateFileName member on CE. */
typedef struct _WIN32_FIND_DATAW {
    DWORD    dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD    nFileSizeHigh;
    DWORD    nFileSizeLow;
    DWORD    dwOID;
    WCHAR    cFileName[MAX_PATH];
} WIN32_FIND_DATAW, *PWIN32_FIND_DATAW, *LPWIN32_FIND_DATAW;
typedef WIN32_FIND_DATAW WIN32_FIND_DATA;
typedef LPWIN32_FIND_DATAW LPWIN32_FIND_DATA;

/* File attribute constants.  The common values below are the
 * Win32/CE ABI bit values published in Microsoft's official File
 * Attribute Constants reference (WinNT.h); FILE_ATTRIBUTE_INROM and
 * FILE_ATTRIBUTE_ROMMODULE are the CE ROM-file attributes named by
 * the CE WIN32_FIND_DATA (ms892378) and GetFileAttributes (ms890895)
 * pages -- their CE bit values were cross-checked for parity only
 * (INROM reuses the desktop DEVICE bit position 0x40, ROMMODULE the
 * NOT_CONTENT_INDEXED position 0x2000).  FILE_ATTRIBUTE_ROMSTATICREF
 * is named by the same CE pages but its value is not defined here
 * pending an official numeric source. */
#define FILE_ATTRIBUTE_READONLY   0x00000001u
#define FILE_ATTRIBUTE_HIDDEN     0x00000002u
#define FILE_ATTRIBUTE_SYSTEM     0x00000004u
#define FILE_ATTRIBUTE_DIRECTORY  0x00000010u
#define FILE_ATTRIBUTE_ARCHIVE    0x00000020u
#define FILE_ATTRIBUTE_INROM      0x00000040u
#define FILE_ATTRIBUTE_NORMAL     0x00000080u
#define FILE_ATTRIBUTE_TEMPORARY  0x00000100u
#define FILE_ATTRIBUTE_SPARSE_FILE 0x00000200u
#define FILE_ATTRIBUTE_REPARSE_POINT 0x00000400u
#define FILE_ATTRIBUTE_COMPRESSED 0x00000800u
#define FILE_ATTRIBUTE_ROMMODULE  0x00002000u
#define FILE_ATTRIBUTE_ENCRYPTED  0x00004000u

/* Generic access rights (CreateFile dwDesiredAccess; values per
 * Microsoft's official Generic Access Rights reference). */
#define GENERIC_READ    0x80000000u
#define GENERIC_WRITE   0x40000000u
#define GENERIC_EXECUTE 0x20000000u
#define GENERIC_ALL     0x10000000u

/* Share modes (CreateFile dwShareMode; ms885182 CreateFile page
 * lists FILE_SHARE_READ/FILE_SHARE_WRITE; Win32 ABI values). */
#define FILE_SHARE_READ   0x00000001u
#define FILE_SHARE_WRITE  0x00000002u

/* Creation dispositions (CreateFile dwCreationDisposition; per the
 * CE CreateFile page aa517318; Win32 ABI values). */
#define CREATE_NEW          1u
#define CREATE_ALWAYS       2u
#define OPEN_EXISTING       3u
#define OPEN_ALWAYS         4u
#define TRUNCATE_EXISTING   5u

/* Flags and attributes (CreateFile dwFlagsAndAttributes; per the CE
 * CreateFile page aa517318; Win32 ABI values).  FILE_ATTRIBUTE_
 * values are above; FILE_FLAG_OVERLAPPED is listed by the CE page as
 * "not supported", but the name/value is kept for source
 * compatibility with code written for the Win32 ABI. */
#define FILE_FLAG_WRITE_THROUGH   0x80000000u
#define FILE_FLAG_OVERLAPPED      0x40000000u
#define FILE_FLAG_RANDOM_ACCESS   0x10000000u

/* aa517318 "CreateFile (Windows CE 5.0)":
 * HANDLE CreateFile(LPCTSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES,
 *                   DWORD, DWORD, HANDLE).  CE 1.0+; Winbase.h;
 * Coredll.lib.  Creates/opens files, COM ports, devices, services,
 * consoles.  CE notes: lpSecurityAttributes ignored (NULL);
 * hTemplateFile ignored; no current-directory concept (relative
 * names resolve against \Windows and the root); ROM modules cannot
 * be opened; CONn: opens the console if present; use CloseHandle on
 * the returned handle; INVALID_HANDLE_VALUE on failure.  Export is
 * CreateFileW. */
HANDLE CreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess,
                   DWORD dwShareMode,
                   LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                   DWORD dwCreationDisposition,
                   DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
#define CreateFile CreateFileW

/* ms889001 "DeleteFile (Windows CE 5.0)": BOOL DeleteFile(LPCTSTR).
 * CE 1.0+; Winbase.h; Coredll.lib.  Fails if the file does not
 * exist or is open for I/O or memory-mapped; does not delete
 * directories (use RemoveDirectory).  Export is DeleteFileW. */
BOOL DeleteFileW(LPCWSTR lpFileName);
#define DeleteFile DeleteFileW

/* ms890895 "GetFileAttributes (Windows CE 5.0)":
 * DWORD GetFileAttributes(LPCTSTR).  CE 1.0+; Winbase.h; Coredll.lib.
 * Returns the file/directory attributes (one or more FILE_ATTRIBUTE_
 * values); 0xFFFFFFFF on failure.  Export is GetFileAttributesW. */
DWORD GetFileAttributesW(LPCWSTR lpFileName);
#define GetFileAttributes GetFileAttributesW

/* ms889678 "FindFirstFile (Windows CE 5.0)":
 * HANDLE FindFirstFile(LPCTSTR, LPWIN32_FIND_DATA).  CE 1.0+;
 * Winbase.h; Coredll.lib.  Opens a search handle and returns data
 * on the first match; * and ? wildcards allowed in the name; fails
 * with INVALID_HANDLE_VALUE; close the handle with FindClose.
 * Export is FindFirstFileW. */
HANDLE FindFirstFileW(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData);
#define FindFirstFile FindFirstFileW

/* ms889873 "FindNextFile (Windows CE 5.0)":
 * BOOL FindNextFile(HANDLE, LPWIN32_FIND_DATA).  CE 1.0+; Winbase.h;
 * Coredll.lib.  Continues the search from FindFirstFile; when no
 * more files match, fails and GetLastError returns
 * ERROR_NO_MORE_FILES.  Export is FindNextFileW. */
BOOL FindNextFileW(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData);
#define FindNextFile FindNextFileW

/* ms889619 "FindClose (Windows CE 5.0)": BOOL FindClose(HANDLE).
 * CE 1.0+; Winbase.h; Coredll.lib.  Closes a search handle opened
 * by FindFirstFile; the handle must not be used afterwards. */
BOOL FindClose(HANDLE hFindFile);

/* INVALID_HANDLE_VALUE: failure return of handle-opening functions
 * (cited by the CE CreateFile aa517318 and FindFirstFile ms889678
 * pages). */
#define INVALID_HANDLE_VALUE ((HANDLE)-1)

/* ------------------------------------------------------------------ */
/* File I/O (synchronous) and file/directory management               */
/* ------------------------------------------------------------------ */

/* Windows CE does not support asynchronous ("overlapped") file I/O:
 * the ReadFile (ms891445) and WriteFile (ms892380) pages state that
 * the lpOverlapped parameter is unsupported and must be NULL.
 * OVERLAPPED is therefore an opaque tag here: source that passes the
 * required NULL compiles, while code that instantiates an OVERLAPPED
 * (an unsupported CE construct) does not. */
typedef struct _OVERLAPPED OVERLAPPED;
typedef OVERLAPPED *LPOVERLAPPED;
/* CE: "Unsupported; set to NULL" (ms891445, ms892380). */

/* SetFilePointer dwMoveMethod starting points (ms891933 lists the
 * FILE_BEGIN/FILE_CURRENT/FILE_END names; the numeric values are the
 * Win32 ABI values of Microsoft's official File Management
 * Constants reference). */
#define FILE_BEGIN    0u
#define FILE_CURRENT  1u
#define FILE_END      2u

/* INVALID_SET_FILE_POINTER: the SetFilePointer failure return.  The
 * CE page (ms891933) notes that 0xFFFFFFFF is at the same time a
 * valid new file pointer position (CE file sizes are limited to
 * 0xFFFFFFFF), so failure must be distinguished with GetLastError.
 * Name/value per the Win32 ABI. */
#define INVALID_SET_FILE_POINTER ((DWORD)0xFFFFFFFFu)

/* ms891445 "ReadFile (Windows CE 5.0)":
 * BOOL ReadFile(HANDLE, LPVOID, DWORD, LPDWORD, LPOVERLAPPED).
 * CE 1.0+; Winbase.h; Coredll.lib.  Reads up to
 * nNumberOfBytesToRead bytes from the current file pointer of hFile
 * (which must have been opened with GENERIC_READ and cannot be a
 * socket handle).  lpNumberOfBytesRead receives the count read; it is
 * set to zero before any work or error checking.  lpOverlapped is
 * unsupported -- set to NULL.  At end of file ReadFile returns
 * nonzero and stores zero in lpNumberOfBytesRead. */
BOOL ReadFile(HANDLE hFile, LPVOID lpBuffer,
              DWORD nNumberOfBytesToRead,
              LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);

/* ms892380 "WriteFile (Windows CE 5.0)":
 * BOOL WriteFile(HANDLE, LPCVOID, DWORD, LPDWORD, LPOVERLAPPED).
 * CE 1.0+; Winbase.h; Coredll.lib.  Writes up to
 * nNumberOfBytesToWrite bytes from lpBuffer at the current file
 * pointer (hFile must have GENERIC_WRITE).  lpNumberOfBytesWritten
 * receives the count and is zeroed before any work/error checking.
 * A zero byte count is a "null write": no bytes are written but the
 * file time stamp changes.  WriteFile never truncates -- use
 * SetEndOfFile.  lpOverlapped is unsupported -- set to NULL. */
BOOL WriteFile(HANDLE hFile, LPCVOID lpBuffer,
               DWORD nNumberOfBytesToWrite,
               LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);

/* ms890939 "GetFileSize (Windows CE 5.0)":
 * DWORD GetFileSize(HANDLE, LPDWORD).  CE 1.0+; Winbase.h;
 * Coredll.lib.  Returns the low 32 bits of the file size; when
 * lpFileSizeHigh is non-NULL it receives the high 32 bits.  A return
 * of 0xFFFFFFFF signals failure -- call GetLastError to distinguish
 * it from a legitimate 32-bit size. */
DWORD GetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh);

/* ms891933 "SetFilePointer (Windows CE 5.0)":
 * DWORD SetFilePointer(HANDLE, LONG, PLONG, DWORD).  CE 1.0+;
 * Winbase.h; Coredll.lib.  Moves the file pointer by
 * lDistanceToMove bytes from the dwMoveMethod starting point and
 * returns the new pointer position.  CE notes: lpDistanceToMoveHigh
 * is not supported and must be NULL or point to a value of zero; CE
 * file sizes are limited to 0xFFFFFFFF so the pointer cannot be moved
 * past that value.  The return value 0xFFFFFFFF is ambiguous (it is
 * also a valid position), so failure must be confirmed with
 * GetLastError.  Not usable on non-seeking devices such as
 * communications devices. */
DWORD SetFilePointer(HANDLE hFile, LONG lDistanceToMove,
                     PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod);

/* ms891916 "SetEndOfFile (Windows CE 5.0)":
 * BOOL SetEndOfFile(HANDLE).  CE 1.0+; Winbase.h; Coredll.lib.
 * Truncates or extends the file so its end is at the current file
 * pointer position (hFile must have GENERIC_WRITE; not usable on
 * non-seeking devices).  When a file is extended, the contents
 * between the old and new end positions are undefined. */
BOOL SetEndOfFile(HANDLE hFile);

/* ms890238 "FlushFileBuffers (Windows CE 5.0)":
 * BOOL FlushFileBuffers(HANDLE).  CE 1.0+; Winbase.h; Coredll.lib.
 * Writes the buffered data of hFile to the underlying storage; for a
 * communications-device handle it flushes the transmit buffer.  The
 * handle must have GENERIC_WRITE access. */
BOOL FlushFileBuffers(HANDLE hFile);

/* ms891388 "MoveFile (Windows CE 5.0)":
 * BOOL MoveFile(LPCTSTR, LPCTSTR).  CE 1.0+; Winbase.h; Coredll.lib.
 * Renames or moves an existing file or directory, including all its
 * children.  The new name must not already exist.  A file may be
 * moved to a different file system or drive; a directory move across
 * volumes fails.  Windows CE is Unicode-only, so the export is
 * MoveFileW. */
BOOL MoveFileW(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName);
#define MoveFile MoveFileW

/* aa517309 "CopyFile (Windows CE 5.0)":
 * BOOL CopyFile(LPCTSTR, LPCTSTR, BOOL).  CE 1.0+; Winbase.h;
 * Coredll.lib.  Copies an existing file to a new file; the attribute
 * bits of the source (for example FILE_ATTRIBUTE_READONLY) are copied
 * to the destination.  bFailIfExists TRUE fails when the destination
 * already exists, FALSE overwrites it.  CopyFile does not operate on
 * directories.  Export is CopyFileW. */
BOOL CopyFileW(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName,
               BOOL bFailIfExists);
#define CopyFile CopyFileW

/* aa517316 "CreateDirectory (Windows CE 5.0)":
 * BOOL CreateDirectory(LPCTSTR, LPSECURITY_ATTRIBUTES).  CE 1.0+;
 * Winbase.h; Coredll.lib.  Creates a new directory.  Only the final
 * component of the path is created -- the function is not recursive,
 * and a missing parent fails with ERROR_PATH_NOT_FOUND.  MAX_PATH is
 * the default path length limit.  lpSecurityAttributes is ignored
 * (set to NULL).  In CE 5.0 and later the path is canonicalized
 * before use, so trailing backslashes are ignored.  Export is
 * CreateDirectoryW. */
BOOL CreateDirectoryW(LPCWSTR lpPathName,
                      LPSECURITY_ATTRIBUTES lpSecurityAttributes);
#define CreateDirectory CreateDirectoryW

/* ms891470 "RemoveDirectory (Windows CE 5.0)":
 * BOOL RemoveDirectory(LPCTSTR).  CE 1.0+; Winbase.h; Coredll.lib.
 * Deletes an existing empty directory; the caller must have delete
 * access to it.  For non-empty directories, applications first
 * enumerate the contents with FindFirstFile/FindNextFile and delete
 * the children with DeleteFile/RemoveDirectory.  Export is
 * RemoveDirectoryW. */
BOOL RemoveDirectoryW(LPCWSTR lpPathName);
#define RemoveDirectory RemoveDirectoryW

/* ms891925 "SetFileAttributes (Windows CE 5.0)":
 * BOOL SetFileAttributes(LPCTSTR, DWORD).  CE 1.0+; Winbase.h;
 * Coredll.lib.  Sets the given FILE_ATTRIBUTE_* combination on a
 * file; any other value overrides FILE_ATTRIBUTE_NORMAL (which is
 * valid only alone).  FILE_ATTRIBUTE_DIRECTORY cannot be set with
 * this function, and directories are created with CreateDirectory.
 * The ROM file system is not affected (attribute support depends on
 * the underlying file system driver).  MAX_PATH is the default path
 * length limit.  Export is SetFileAttributesW. */
BOOL SetFileAttributesW(LPCWSTR lpFileName, DWORD dwFileAttributes);
#define SetFileAttributes SetFileAttributesW

/* ------------------------------------------------------------------ */
/* Synchronization: event / mutex / semaphore objects                 */
/* ------------------------------------------------------------------ */

/* Wait-function return values (ms885177 and aa450988 return tables;
 * the numeric values are the fixed Win32 ABI values of the wait
 * results).  WAIT_OBJECT_0 is the base value: WaitForMultipleObjects
 * returns WAIT_OBJECT_0+n for the n-th satisfied object and
 * WAIT_ABANDONED_0+n for abandoned mutexes. */
#define WAIT_OBJECT_0      0x00000000u
#define WAIT_ABANDONED     0x00000080u
#define WAIT_ABANDONED_0   0x00000080u
#define WAIT_TIMEOUT       0x00000102u
#define WAIT_FAILED        ((DWORD)0xFFFFFFFFu)

/* MAXIMUM_WAIT_OBJECTS: nCount limit cited by the CE
 * WaitForMultipleObjects page (aa450987); the Win32 ABI value is 64.
 * nCount must be in 1..MAXIMUM_WAIT_OBJECTS. */
#define MAXIMUM_WAIT_OBJECTS 64

/* Event object access right required by OpenEvent (ms886764 lists
 * EVENT_ALL_ACCESS as the required value); value per Microsoft's
 * official synchronization access-rights reference. */
#define EVENT_ALL_ACCESS 0x001F0003u

/* ms885177 "CreateEvent (Windows CE 5.0)":
 * HANDLE CreateEvent(LPSECURITY_ATTRIBUTES, BOOL, BOOL, LPTSTR).
 * CE 1.0+; Winbase.h; Coredll.lib, Nk.lib.  Creates a named or
 * unnamed event object.  lpEventAttributes is ignored (NULL).
 * bManualReset TRUE creates a manual-reset event (ResetEvent must
 * reset it), FALSE an auto-reset event (reset automatically after a
 * single waiting thread is released).  bInitialState TRUE starts the
 * event signaled.  Names are limited to MAX_PATH characters, may not
 * contain a backslash, compare case-sensitively, and are ignored for
 * an existing object.  A handle to an already existing object returns
 * success with GetLastError == ERROR_ALREADY_EXISTS.  The returned
 * handle has EVENT_ALL_ACCESS.  Export is CreateEventW. */
HANDLE CreateEventW(LPSECURITY_ATTRIBUTES lpEventAttributes,
                    BOOL bManualReset, BOOL bInitialState,
                    LPCWSTR lpName);
#define CreateEvent CreateEventW

/* ms886764 "OpenEvent (Windows CE 5.0)":
 * HANDLE OpenEvent(DWORD, BOOL, LPTSTR).  CE .NET 4.0 and later
 * (present in CE 4.x/5.x/6.x); Winbase.h; Coredll.lib.  Opens an
 * existing named event object; dwDesiredAccess must be
 * EVENT_ALL_ACCESS and bInheritHandle must be FALSE.  Name
 * comparison is case sensitive.  Export is OpenEventW. */
HANDLE OpenEventW(DWORD dwDesiredAccess, BOOL bInheritHandle,
                  LPCWSTR lpName);
#define OpenEvent OpenEventW

/* ms886810 "SetEvent (Windows CE 5.0)":
 * BOOL SetEvent(HANDLE).  CE 1.0+; the page lists Header: Kfuncs.h;
 * Coredll.lib (kernel-scope header row; the function is the user-mode
 * event API and is exported by Coredll).  Sets the event object to
 * the signaled state; the event stays signaled until a waiting
 * thread is released (auto-reset) or ResetEvent is called
 * (manual-reset). */
BOOL SetEvent(HANDLE hEvent);

/* ms886800 "ResetEvent (Windows CE 5.0)":
 * BOOL ResetEvent(HANDLE).  CE 1.0+; Header: Kfuncs.h per page;
 * Coredll.lib (see SetEvent note).  Sets the event object to the
 * nonsignaled state. */
BOOL ResetEvent(HANDLE hEvent);

/* ms886784 "PulseEvent (Windows CE 5.0)":
 * BOOL PulseEvent(HANDLE).  CE 1.0+; Winbase.h; Coredll.lib.  Sets
 * the event signaled, releases the appropriate number of waiting
 * threads, then resets it to nonsignaled in one operation.  A CE
 * note on timing: only threads already waiting are released. */
BOOL PulseEvent(HANDLE hEvent);

/* ms885181 "CreateMutex (Windows CE 5.0)":
 * HANDLE CreateMutex(LPSECURITY_ATTRIBUTES, BOOL, LPTSTR).  CE 1.01+;
 * Winbase.h; Coredll.lib, Nk.lib.  Creates a named or unnamed mutex.
 * lpMutexAttributes is ignored (NULL); bInitialOwner TRUE gives the
 * calling thread initial ownership.  If the named mutex already
 * exists the function succeeds with ERROR_ALREADY_EXISTS.  Export is
 * CreateMutexW. */
HANDLE CreateMutexW(LPSECURITY_ATTRIBUTES lpMutexAttributes,
                    BOOL bInitialOwner, LPCWSTR lpName);
#define CreateMutex CreateMutexW

/* ms886797 "ReleaseMutex (Windows CE 5.0)":
 * BOOL ReleaseMutex(HANDLE).  CE 1.01+; Winbase.h; Nk.lib row on the
 * page.  Releases ownership of the mutex object; fails if the calling
 * thread does not own the mutex. */
BOOL ReleaseMutex(HANDLE hMutex);

/* ms885184 "CreateSemaphore (Windows CE 5.0)":
 * HANDLE CreateSemaphore(LPSECURITY_ATTRIBUTES, LONG, LONG, LPTSTR).
 * CE 3.0+; Winbase.h; Nk.lib row on the page.  Creates a named or
 * unnamed semaphore with initial count lInitialCount (0 ..
 * lMaximumCount) and maximum count lMaximumCount (>= 1).
 * lpSemaphoreAttributes is ignored (NULL).  Export is
 * CreateSemaphoreW. */
HANDLE CreateSemaphoreW(LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
                        LONG lInitialCount, LONG lMaximumCount,
                        LPCWSTR lpName);
#define CreateSemaphore CreateSemaphoreW

/* ms886798 "ReleaseSemaphore (Windows CE 5.0)":
 * BOOL ReleaseSemaphore(HANDLE, LONG, LPLONG).  CE 3.0+; Winbase.h;
 * Coredll.lib.  Increases the semaphore count by lReleaseCount (which
 * must be > 0); lpPreviousCount receives the previous count when
 * non-NULL.  Fails when the count would exceed the maximum. */
BOOL ReleaseSemaphore(HANDLE hSemaphore, LONG lReleaseCount,
                      LPLONG lpPreviousCount);

/* ms885208 "DuplicateHandle (Windows CE 5.0)":
 * BOOL DuplicateHandle(HANDLE, HANDLE, HANDLE, LPHANDLE, DWORD, BOOL,
 *                      DWORD).  CE .NET 4.0 and later; Header
 *                      Windows.h per page; Coredll.lib.  Duplicates
 * an object handle into the target process.  CE notes: the duplicate
 * must be valid in the target process and lpTargetHandle cannot be
 * NULL; dwDesiredAccess is currently ignored; bInheritHandle must be
 * FALSE.  dwOptions may be DUPLICATE_CLOSE_SOURCE and/or
 * DUPLICATE_SAME_ACCESS. */
BOOL DuplicateHandle(HANDLE hSourceProcessHandle, HANDLE hSourceHandle,
                     HANDLE hTargetProcessHandle,
                     LPHANDLE lpTargetHandle, DWORD dwDesiredAccess,
                     BOOL bInheritHandle, DWORD dwOptions);

/* DuplicateHandle dwOptions (Win32 ABI values, official DuplicateHandle
 * reference). */
#define DUPLICATE_CLOSE_SOURCE  0x00000001u
#define DUPLICATE_SAME_ACCESS   0x00000002u

/* aa450988 "WaitForSingleObject (Windows CE 5.0)":
 * DWORD WaitForSingleObject(HANDLE, DWORD).  CE 1.0+; Winbase.h;
 * Coredll.lib.  Returns when the object is signaled or the time-out
 * elapses.  dwMilliseconds zero polls the state; INFINITE waits
 * forever.  CE time-out cap: values between 0x7FFFFFFF and INFINITE
 * (0x80000000..0xFFFFFFFE) are treated as 0x7FFFFFFF.  Returns
 * WAIT_OBJECT_0 / WAIT_TIMEOUT / WAIT_FAILED.  Objects waitable on
 * CE: event, mutex, semaphore (CE 3.0+), process and thread handles.
 * CE 1.0-2.12 cannot wait on semaphores; CE 1.0/1.01 cannot wait on
 * process or thread handles. */
DWORD WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds);

/* aa450987 "WaitForMultipleObjects (Windows CE 5.0)":
 * DWORD WaitForMultipleObjects(DWORD, CONST HANDLE*, BOOL, DWORD).
 * CE 1.01+; Winbase.h; Nk.lib row on the page.  nCount (1 ..
 * MAXIMUM_WAIT_OBJECTS) handles are waited on; fWaitAll TRUE waits
 * for all, FALSE returns when any single object is signaled.  Return
 * values are WAIT_OBJECT_0+n, WAIT_ABANDONED_0+n (mutexes),
 * WAIT_TIMEOUT, WAIT_FAILED. */
DWORD WaitForMultipleObjects(DWORD nCount,
                             const HANDLE *lpHandles,
                             BOOL fWaitAll, DWORD dwMilliseconds);

/* ------------------------------------------------------------------ */
/* Synchronization: critical sections and interlocked access          */
/* ------------------------------------------------------------------ */

/* CRITICAL_SECTION object (RTL_CRITICAL_SECTION in winnt.h).  The CE
 * critical-section pages (ms885665, ms885196, ms885212, ms886733,
 * aa450959) declare the object via LPCRITICAL_SECTION and require no
 * return value; the page rows list Link Library: Coremain.lib for the
 * four base functions (see docs/inventory.md "documented link-library
 * rows" note) and Coredll.lib for TryEnterCriticalSection.  The
 * layout itself is the desktop-official RTL_CRITICAL_SECTION (see
 * winnt.h). */

/* ms885665 "InitializeCriticalSection (Windows CE 5.0)":
 * VOID InitializeCriticalSection(LPCRITICAL_SECTION).  CE 1.0+;
 * Winbase.h; Coremain.lib row.  Initializes a critical-section object
 * for use by a single process. */
VOID InitializeCriticalSection(LPCRITICAL_SECTION lpCriticalSection);

/* ms885212 "EnterCriticalSection (Windows CE 5.0)":
 * VOID EnterCriticalSection(LPCRITICAL_SECTION).  CE 1.0+; Winbase.h;
 * Coremain.lib row.  Waits for ownership of the critical-section
 * object; the calling thread is blocked until it can enter. */
VOID EnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection);

/* ms886733 "LeaveCriticalSection (Windows CE 5.0)":
 * VOID LeaveCriticalSection(LPCRITICAL_SECTION).  CE 1.0+; Winbase.h;
 * Coremain.lib row.  Releases ownership of the critical-section
 * object held by the calling thread. */
VOID LeaveCriticalSection(LPCRITICAL_SECTION lpCriticalSection);

/* ms885196 "DeleteCriticalSection (Windows CE 5.0)":
 * VOID DeleteCriticalSection(LPCRITICAL_SECTION).  CE 1.0+;
 * Winbase.h; Coremain.lib row.  Releases all resources of an
 * initialized critical-section object; the object must not be in use. */
VOID DeleteCriticalSection(LPCRITICAL_SECTION lpCriticalSection);

/* aa450959 "TryEnterCriticalSection (Windows CE 5.0)":
 * BOOL TryEnterCriticalSection(LPCRITICAL_SECTION).  CE 3.0+;
 * Winbase.h; Coredll.lib.  Attempts to enter the critical section
 * without blocking: nonzero if ownership was obtained, zero if
 * another thread owns it. */
BOOL TryEnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection);

/* Interlocked operations.  The CE pages (ms885667..ms885674) declare
 * the classic Win32 interlocked functions and list Link Library:
 * Coredll.lib (Header rows are Windows.h / Winbase.h per page); the
 * x86/ARM code generator lowers the corresponding C11/Clang atomic
 * builtins to calls of these names on Windows CE. */

/* ms885670 "InterlockedExchange": LONG
 * InterlockedExchange(LPLONG Target, LONG Value). */
LONG InterlockedExchange(LPLONG Target, LONG Value);

/* ms885673 "InterlockedIncrement": LONG InterlockedIncrement(LPLONG
 * Addend).  Returns the resulting value. */
LONG InterlockedIncrement(LPLONG Addend);

/* ms885669 "InterlockedDecrement": LONG InterlockedDecrement(LPLONG
 * Addend).  Returns the resulting value. */
LONG InterlockedDecrement(LPLONG Addend);

/* ms885671 "InterlockedExchangeAdd": LONG InterlockedExchangeAdd(
 * LPLONG Addend, LONG Increment).  Returns the original value. */
LONG InterlockedExchangeAdd(LPLONG Addend, LONG Increment);

/* ms885667 "InterlockedCompareExchange": LONG
 * InterlockedCompareExchange(LPLONG Destination, LONG Exchange,
 * LONG Comperand).  Returns the original value of Destination. */
LONG InterlockedCompareExchange(LPLONG Destination, LONG Exchange,
                                LONG Comperand);

/* ms885674 "InterlockedTestExchange": LONG
 * InterlockedTestExchange(LPLONG Target, LONG OldValue, LONG
 * NewValue).  CE-specific conditional set: stores NewValue in Target
 * only when Target currently equals OldValue; returns the value of
 * Target at the time of the call. */
LONG InterlockedTestExchange(LPLONG Target, LONG OldValue,
                             LONG NewValue);

/* ms885672 "InterlockedExchangePointer": PVOID
 * InterlockedExchangePointer(PVOID* Target, PVOID Value). */
PVOID InterlockedExchangePointer(PVOID *Target, PVOID Value);

/* ms885668 "InterlockedCompareExchangePointer": PVOID
 * InterlockedCompareExchangePointer(PVOID* Destination, PVOID
 * ExChange, PVOID Comperand). */
PVOID InterlockedCompareExchangePointer(PVOID *Destination,
                                        PVOID ExChange,
                                        PVOID Comperand);


/* ------------------------------------------------------------------ */
/* Memory management: heaps, process heap, local heap completion      */
/* ------------------------------------------------------------------ */

/* ms886753 "MEMORYSTATUS (Windows CE 5.0)": memory availability
 * report filled by GlobalMemoryStatus.  CE 1.0+; Winbase.h.  CE
 * layout is eight DWORD members (there is no
 * dwAvailExtendedVirtual member on CE).  dwLength must be set to
 * sizeof(MEMORYSTATUS) by the caller. */
typedef struct _MEMORYSTATUS {
    DWORD dwLength;        /* size of the structure, in bytes */
    DWORD dwMemoryLoad;    /* 0..100 estimate of memory use */
    DWORD dwTotalPhys;     /* total physical memory, in bytes */
    DWORD dwAvailPhys;     /* available physical memory, in bytes */
    DWORD dwTotalPageFile; /* bytes storable in the paging file */
    DWORD dwAvailPageFile; /* bytes available in the paging file */
    DWORD dwTotalVirtual;  /* user-mode virtual address space, bytes */
    DWORD dwAvailVirtual;  /* unreserved/uncommitted virtual memory */
} MEMORYSTATUS, *LPMEMORYSTATUS;

/* Heap allocation flags.  The CE HeapAlloc/HeapReAlloc/HeapCreate
 * pages (ms885654/ms885661/ms885656) name HEAP_NO_SERIALIZE (ignored
 * on CE: heaps are always serialized), HEAP_ZERO_MEMORY and
 * HEAP_SHARED_READONLY (HeapCreate; numeric value not published);
 * numeric values for the first two are the fixed Win32 ABI values.
 * HEAP_SHARED_READONLY is intentionally not defined (no official
 * numeric value). */
#define HEAP_NO_SERIALIZE 0x00000001u
#define HEAP_ZERO_MEMORY  0x00000008u

/* ms885635 "GetProcessHeap (Windows CE 5.0)":
 * HANDLE GetProcessHeap(VOID).  CE 1.0+; Winbase.h; the page lists
 * Link Library: Lmem.lib (recorded row; the process-heap handle is
 * used by the heap functions below).  Returns a handle usable in
 * HeapAlloc/HeapReAlloc/HeapFree/HeapSize; not to be destroyed. */
HANDLE GetProcessHeap(void);

/* ms885656 "HeapCreate (Windows CE 5.0)":
 * HANDLE HeapCreate(DWORD, DWORD, DWORD).  CE 1.0+; Winbase.h;
 * Coredll.lib.  Reserves memory for a private heap (dwMaximumSize
 * zero makes it growable; a nonzero dwMaximumSize makes it
 * nongrowable).  Heap functions then allocate from the reserved
 * memory.  HEAP_SHARED_READONLY requires kernel mode; the flag is
 * otherwise documented per page. */
HANDLE HeapCreate(DWORD flOptions, DWORD dwInitialSize,
                  DWORD dwMaximumSize);

/* ms885657 "HeapDestroy (Windows CE 5.0)":
 * BOOL HeapDestroy(HANDLE).  CE 1.0+; Winbase.h; Coredll.lib.
 * Destroys a heap created by HeapCreate (not the process heap) and
 * frees its committed memory. */
BOOL HeapDestroy(HANDLE hHeap);

/* ms885654 "HeapAlloc (Windows CE 5.0)":
 * LPVOID HeapAlloc(HANDLE, DWORD, DWORD).  CE 1.0+; Winbase.h;
 * Coredll.lib.  Allocates a non-movable block from a heap
 * (HeapCreate or GetProcessHeap handle).  HEAP_NO_SERIALIZE is
 * ignored (heaps are always serialized); HEAP_ZERO_MEMORY zero
 * initializes.  NULL indicates failure and no extended error is
 * recorded. */
LPVOID HeapAlloc(HANDLE hHeap, DWORD dwFlags, DWORD dwBytes);

/* ms885659 "HeapFree (Windows CE 5.0)":
 * BOOL HeapFree(HANDLE, DWORD, LPVOID).  CE 1.0+; Winbase.h;
 * Coredll.lib.  Frees a block allocated by HeapAlloc/HeapReAlloc. */
BOOL HeapFree(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem);

/* ms885661 "HeapReAlloc (Windows CE 5.0)":
 * LPVOID HeapReAlloc(HANDLE, DWORD, LPVOID, DWORD).  CE 1.0+;
 * Winbase.h; Coredll.lib.  Reallocates a non-movable heap block;
 * HEAP_NO_SERIALIZE is ignored on CE. */
LPVOID HeapReAlloc(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem,
                   DWORD dwBytes);

/* ms885662 "HeapSize (Windows CE 5.0)":
 * DWORD HeapSize(HANDLE, DWORD, LPCVOID).  CE 1.0+; Winbase.h;
 * Coredll.lib.  Returns the actual size in bytes of an allocated
 * heap block (>= the requested size). */
DWORD HeapSize(HANDLE hHeap, DWORD dwFlags, LPCVOID lpMem);

/* ms885663 "HeapValidate (Windows CE 5.0)":
 * BOOL HeapValidate(HANDLE, DWORD, LPCVOID).  CE 1.0+; Winbase.h;
 * Coredll.lib.  Validates the heap control structures (whole heap
 * when lpMem is NULL, otherwise the single block). */
BOOL HeapValidate(HANDLE hHeap, DWORD dwFlags, LPCVOID lpMem);

/* ms885655 "HeapCompact (Windows CE 5.0)":
 * UINT HeapCompact(HANDLE, DWORD).  CE 5.0 and later; Winbase.h;
 * Coredll.lib.  Coalesces adjacent free blocks and decommits large
 * free blocks; returns the largest committed free block size. */
UINT HeapCompact(HANDLE hHeap, DWORD dwFlags);

/* Local-heap completion (CE: local heap = process heap). */

/* ms886742 "LocalReAlloc (Windows CE 5.0)":
 * HLOCAL LocalReAlloc(HLOCAL, UINT, UINT).  CE 1.0+; Winbase.h;
 * Coredll.lib.  Changes the size of a local memory object (see
 * LocalAlloc/LocalFree above). */
HLOCAL LocalReAlloc(HLOCAL hMem, UINT uBytes, UINT fuFlags);

/* ms886743 "LocalSize (Windows CE 5.0)":
 * UINT LocalSize(HLOCAL).  CE 1.0+; Winbase.h; Coredll.lib.  Returns
 * the current size in bytes of a local memory object. */
UINT LocalSize(HLOCAL hMem);

/* ms885649 "GlobalMemoryStatus (Windows CE 5.0)":
 * VOID GlobalMemoryStatus(LPMEMORYSTATUS).  CE 1.0+; Winbase.h;
 * Coredll.lib.  Fills a MEMORYSTATUS with current memory
 * availability; the caller sets dwLength to sizeof(MEMORYSTATUS)
 * first. */
VOID GlobalMemoryStatus(LPMEMORYSTATUS lpBuffer);

/* Memory-integrity probes (use is discouraged by the pages
 * themselves: "unsafe to use when checking your input parameters"). */

/* ms885687 "IsBadCodePtr (Windows CE 5.0)":
 * BOOL IsBadCodePtr(FARPROC).  CE 1.0+; Winbase.h; Coredll.lib. */
BOOL IsBadCodePtr(FARPROC lpfn);

/* ms885688 "IsBadReadPtr (Windows CE 5.0)":
 * BOOL IsBadReadPtr(const void*, UINT).  CE 1.0+; Winbase.h;
 * Coredll.lib.  A zero block size returns zero (valid). */
BOOL IsBadReadPtr(const void *lp, UINT ucb);

/* ms885689 "IsBadWritePtr (Windows CE 5.0)":
 * BOOL IsBadWritePtr(LPVOID, UINT).  CE 1.0+; Winbase.h; Coredll.lib. */
BOOL IsBadWritePtr(LPVOID lp, UINT ucb);

/* MAXDWORD: 32-bit unsigned maximum; cited by the GetIdleTime page
 * (ms885626: "If GetIdleTime returns MAXDWORD, functionality is not
 * supported"). */
#define MAXDWORD ((DWORD)0xFFFFFFFFu)

/* ------------------------------------------------------------------ */
/* Time management (SYSTEMTIME + time conversion).                    */
/* ------------------------------------------------------------------ */

/* ms885586 "FILETIME (Windows CE 5.0)" (see above) anchors all
 * file-time conversions in this section. */

/* aa450923 "SYSTEMTIME (Windows CE 5.0)": 100-ns-epoch-independent
 * calendar/time structure with one WORD per field; wDayOfWeek is
 * ignored by SetLocalTime and SystemTimeToFileTime.  CE 1.0+;
 * Winbase.h. */
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

/* ms885628 "GetLocalTime (Windows CE 5.0)": fills lpSystemTime with
 * the current local date/time (time-zone and DST adjusted).  CE 1.0+;
 * Winbase.h; Coredll.lib. */
void GetLocalTime(LPSYSTEMTIME lpSystemTime);

/* ms885640 "GetSystemTime (Windows CE 5.0)": fills lpSystemTime with
 * the current system date/time expressed in UTC.  CE 1.0+; Winbase.h;
 * Coredll.lib. */
void GetSystemTime(LPSYSTEMTIME lpSystemTime);

/* ms886818 "SetLocalTime (Windows CE 5.0)": sets the current local
 * time/date; the caller needs the appropriate privilege.  wDayOfWeek
 * is ignored; nonzero success / zero failure (GetLastError).  CE
 * 1.0+; Winbase.h; Coredll.lib. */
BOOL SetLocalTime(const SYSTEMTIME *lpSystemTime);

/* aa450867 "SetSystemTime (Windows CE 5.0)": sets the current system
 * time/date in UTC; nonzero success / zero failure (GetLastError).
 * CE 1.0+; Winbase.h; Coredll.lib. */
BOOL SetSystemTime(const SYSTEMTIME *lpSystemTime);

/* ms885589 "FileTimeToLocalFileTime (Windows CE 5.0)": converts a
 * UTC file time to a local file time using current time-zone and DST
 * settings; lpLocalFileTime must not alias lpFileTime.  Nonzero
 * success / zero failure (GetLastError).  CE 1.0+; Winbase.h;
 * Coredll.lib. */
BOOL FileTimeToLocalFileTime(const FILETIME *lpFileTime,
                             LPFILETIME lpLocalFileTime);

/* ms886740 "LocalFileTimeToFileTime (Windows CE 5.0)": converts a
 * local file time to a UTC file time; lpFileTime must not alias
 * lpLocalFileTime.  Nonzero success / zero failure (GetLastError).
 * CE 1.0+; Winbase.h; Coredll.lib. */
BOOL LocalFileTimeToFileTime(const FILETIME *lpLocalFileTime,
                             LPFILETIME lpFileTime);

/* ms885593 "FileTimeToSystemTime (Windows CE 5.0)": converts a 64-bit
 * file time to SYSTEMTIME; only valid for FILETIME values below
 * 0x8000000000000000 (larger values fail).  Nonzero success / zero
 * failure (GetLastError).  CE 1.0+; Winbase.h; Coredll.lib. */
BOOL FileTimeToSystemTime(const FILETIME *lpFileTime,
                          LPSYSTEMTIME lpSystemTime);

/* aa450925 "SystemTimeToFileTime (Windows CE 5.0)": converts a
 * SYSTEMTIME to a 64-bit file time; the wDayOfWeek member is ignored.
 * Nonzero success / zero failure (GetLastError).  CE 1.0+; Winbase.h;
 * Coredll.lib. */
BOOL SystemTimeToFileTime(const SYSTEMTIME *lpSystemTime,
                          LPFILETIME lpFileTime);

/* ------------------------------------------------------------------ */
/* Time: tick/counter, file times, time-zone notes (M10)              */
/* ------------------------------------------------------------------ */

/* ms885645 "GetTickCount (Windows CE 5.0)":
 * DWORD GetTickCount(void).  CE 1.0+; Winbase.h; Coredll.lib.
 * Returns the number of milliseconds since the system started. */
DWORD GetTickCount(void);

/* ms885625 "GetFileTime (Windows CE 5.0)":
 * BOOL GetFileTime(HANDLE, LPFILETIME, LPFILETIME, LPFILETIME).
 * CE 1.0+; Winbase.h; Coredll.lib.  Retrieves the creation, last
 * access and last write times of a file (handle opened with
 * GENERIC_READ).  Any of the three pointers may be NULL when that
 * time is not needed. */
BOOL GetFileTime(HANDLE hFile, LPFILETIME lpCreationTime,
                 LPFILETIME lpLastAccessTime,
                 LPFILETIME lpLastWriteTime);

/* ms886812 "SetFileTime (Windows CE 5.0)":
 * BOOL SetFileTime(HANDLE, const FILETIME*, const FILETIME*, const
 * FILETIME*).  CE 1.0+; Winbase.h; Coredll.lib.  Sets the creation,
 * last access and last write times of a file (handle opened with
 * GENERIC_WRITE); NULL pointers leave the corresponding time
 * unchanged. */
BOOL SetFileTime(HANDLE hFile, const FILETIME *lpCreationTime,
                 const FILETIME *lpLastAccessTime,
                 const FILETIME *lpLastWriteTime);

/* ms885172 "CompareFileTime (Windows CE 5.0)":
 * LONG CompareFileTime(const FILETIME*, const FILETIME*).  CE 1.0+;
 * Header Windows.h per page; Coredll.lib.  Returns -1 when the first
 * time is earlier, 0 when equal, +1 when later. */
LONG CompareFileTime(const FILETIME *lpFileTime1,
                     const FILETIME *lpFileTime2);

/* aa451027 "GetCurrentFT (Windows CE 5.0)":
 * void GetCurrentFT(LPFILETIME).  CE 3.0+; Winbase.h; Coredll.lib.
 * Fills the FILETIME with the current system date and time. */
void GetCurrentFT(LPFILETIME lpFileTime);

/* ms885626 "GetIdleTime (Windows CE 5.0)":
 * DWORD GetIdleTime(void).  CE 3.0+; Winbase.h; Coredll.lib.
 * Returns the number of milliseconds the system has been idle;
 * MAXDWORD means the feature is not supported. */
DWORD GetIdleTime(void);

/* ms886791 "Random (Windows CE 5.0)":
 * DWORD Random(void).  CE 1.0+; Winbase.h; Coredll.lib.  Returns a
 * randomly generated DWORD. */
DWORD Random(void);

/* ms886808 "SetDaylightTime (Windows CE 5.0)":
 * void SetDaylightTime(DWORD).  CE 2.0+; Winbase.h; Coredll.lib.
 * Informs the system whether daylight saving time is in effect:
 * dst 1 = DST in effect, dst 0 = standard time. */
void SetDaylightTime(DWORD dst);

/* ms886788 "QueryPerformanceCounter (Windows CE 5.0)":
 * BOOL QueryPerformanceCounter(LARGE_INTEGER*).  CE 2.0+; Winbase.h;
 * Coredll.lib.  Fills the value with the current high-resolution
 * performance counter (in counts). */
BOOL QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount);

/* ms886789 "QueryPerformanceFrequency (Windows CE 5.0)":
 * BOOL QueryPerformanceFrequency(LARGE_INTEGER*).  CE 2.0+;
 * Winbase.h; Coredll.lib.  Fills the value with the performance
 * counter frequency, in counts per second. */
BOOL QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency);

/* ------------------------------------------------------------------ */
/* System information (M11): GetSystemInfo, GetVersionEx, version     */
/* ------------------------------------------------------------------ */

/* aa450921 "SYSTEM_INFO (Windows CE 5.0)": information about the
 * current computer system filled by GetSystemInfo.  CE 1.0+;
 * Winbase.h.  Layout is the union followed by the six DWORD pointers
 * / masks and the trailing WORD pair exactly as the page prints it
 * (anonymous union/struct, so dwOemId and the architecture WORDs
 * share storage).  Names of the documented wProcessorArchitecture /
 * dwProcessorType values are listed in the member comments; only
 * PROCESSOR_ARCHITECTURE_* macros are defined, with the fixed Win32
 * ABI values. */
typedef struct _SYSTEM_INFO {
    union {
        DWORD dwOemId;                 /* obsolete; do not use */
        struct {
            WORD wProcessorArchitecture;
            WORD wReserved;
        };
    };
    DWORD dwPageSize;
    LPVOID lpMinimumApplicationAddress;
    LPVOID lpMaximumApplicationAddress;
    DWORD dwActiveProcessorMask;
    DWORD dwNumberOfProcessors;
    DWORD dwProcessorType;             /* obsolete; see architecture */
    DWORD dwAllocationGranularity;
    WORD wProcessorLevel;
    WORD wProcessorRevision;
} SYSTEM_INFO, *LPSYSTEM_INFO;

/* wProcessorArchitecture values documented by aa450921 (INTEL, MIPS,
 * UNKNOWN, SHX, ARM); numeric values are the fixed Win32 ABI values
 * (Microsoft's official processor-architecture reference). */
#define PROCESSOR_ARCHITECTURE_INTEL    0
#define PROCESSOR_ARCHITECTURE_MIPS     1
#define PROCESSOR_ARCHITECTURE_SHX      4
#define PROCESSOR_ARCHITECTURE_ARM      5
#define PROCESSOR_ARCHITECTURE_UNKNOWN  0xFFFF

/* dwProcessorType values named by aa450921 (PROCESSOR_INTEL_386/486/
 * PENTIUM/PENTIUMII, PROCESSOR_MIPS_R4000/R5000, PROCESSOR_HITACHI_
 * SH3/SH4, PROCESSOR_ARM720, PROCESSOR_STRONGARM, PROCESSOR_SHx_
 * SH3DSP).  The page marks the member obsolete and publishes no
 * numeric values; none are defined here (unknown facts stay
 * undefined rather than invented). */

/* ms885638 "GetSystemInfo (Windows CE 5.0)":
 * VOID GetSystemInfo(LPSYSTEM_INFO).  CE 1.0+; Winbase.h; Coredll.lib.
 * Fills lpSystemInfo; CeGetSystemInfo is the RAPI equivalent. */
VOID GetSystemInfo(LPSYSTEM_INFO lpSystemInfo);

/* ms886768 "OSVERSIONINFO (Windows CE 5.0)": OS version report filled
 * by GetVersionEx.  CE 1.0+; Winbase.h.  The page typedefs only
 * OSVERSIONINFO (whose szCSDVersion member is TCHAR = WCHAR on CE);
 * LPOSVERSIONINFO is the pointer form the GetVersionEx page's
 * signature uses.  Caller sets dwOSVersionInfoSize first. */
typedef struct _OSVERSIONINFO {
    DWORD dwOSVersionInfoSize;
    DWORD dwMajorVersion;
    DWORD dwMinorVersion;
    DWORD dwBuildNumber;
    DWORD dwPlatformId;
    TCHAR szCSDVersion[128];
} OSVERSIONINFO, *LPOSVERSIONINFO;

/* dwPlatformId values documented by ms886768 (WIN32s / WIN32_WINDOWS
 * / WIN32_NT / WIN32_CE); numeric values are the fixed Win32 ABI
 * values.  GetVersionEx's remarks state CE fills
 * VER_PLATFORM_WIN32_CE. */
#define VER_PLATFORM_WIN32s          0
#define VER_PLATFORM_WIN32_WINDOWS   1
#define VER_PLATFORM_WIN32_NT        2
#define VER_PLATFORM_WIN32_CE        3

/* ms885648 "GetVersionEx (Windows CE 5.0)":
 * BOOL GetVersionEx(LPOSVERSIONINFO).  CE 1.0+; Winbase.h; Coredll.lib.
 * Fills the OSVERSIONINFO the caller sized up front; failure (e.g.
 * bad dwOSVersionInfoSize) sets the last error. */
BOOL GetVersionEx(LPOSVERSIONINFO lpVersionInformation);

/* aa450898 "SignalStarted (Windows CE 5.0)":
 * VOID SignalStarted(DWORD).  CE 2.10+; Winbase.h; Coredll.lib.
 * Called by applications the kernel starts via HKEY_LOCAL_MACHINE\
 * \Init once initialization is complete; dw is the sequence number
 * passed on the command line. */
VOID SignalStarted(DWORD dw);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WINBASE_H */
