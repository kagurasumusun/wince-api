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

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WINBASE_H */
