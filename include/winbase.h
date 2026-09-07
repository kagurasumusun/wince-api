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
#define LMEM_FIXED     0x0000u
#define LMEM_ZEROINIT  0x0040u
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

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WINBASE_H */
