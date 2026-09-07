/*
 * tlhelp32.h -- Toolhelp32 snapshot API for Windows CE (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (CE-era MSDN pages, learn.microsoft.com previous-versions archive,
 * (v=msdn.10) IDs); per-page Requirements rows (OS Versions / Header /
 * Link Library) are transcribed in docs/inventory.md.
 *
 * The CE pages' Header row is Tlhelp32.h (two heap pages print the
 * shorter "Tlhelp.h" -- recorded in the inventory, treated as the same
 * header).  Link Library: Toolhelp.lib on every function page (the
 * import library is not Coredll.lib, so none of these names appear in
 * def/coredll-doc.def).
 */

#ifndef AKARI_TLHELP32_H
#define AKARI_TLHELP32_H

#include "windef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Snapshot scope flags for CreateToolhelp32Snapshot (names per
 * ms885189; numeric values are the fixed Win32 ABI values). */
#define TH32CS_SNAPHEAPLIST 0x00000001u
#define TH32CS_SNAPPROCESS  0x00000002u
#define TH32CS_SNAPTHREAD   0x00000004u
#define TH32CS_SNAPMODULE   0x00000008u
#define TH32CS_SNAPALL      (TH32CS_SNAPHEAPLIST | TH32CS_SNAPPROCESS | \
                             TH32CS_SNAPTHREAD | TH32CS_SNAPMODULE)
#define TH32CS_SNAPNOHEAPS  0x40000000u
#define TH32CS_GETALLMODS   0x80000000u

/* ms886774 "PROCESSENTRY32 (Windows CE 5.0)": a process entry of a
 * snapshot, filled by Process32First/Process32Next.  CE 1.0+;
 * Tlhelp32.h.  Layout verbatim from the page (TCHAR = WCHAR on CE;
 * szExeFile[MAX_PATH]); the CE-only trailing th32MemoryBase and
 * th32AccessKey are part of the published structure.  dwSize must be
 * sizeof(PROCESSENTRY32) before the First call. */
typedef struct tagPROCESSENTRY32 {
    DWORD dwSize;
    DWORD cntUsage;
    DWORD th32ProcessID;
    DWORD th32DefaultHeapID;
    DWORD th32ModuleID;
    DWORD cntThreads;
    DWORD th32ParentProcessID;
    LONG  pcPriClassBase;
    DWORD dwFlags;
    TCHAR szExeFile[MAX_PATH];
    DWORD th32MemoryBase;   /* CE-only */
    DWORD th32AccessKey;    /* CE-only */
} PROCESSENTRY32, *PPROCESSENTRY32, *LPPROCESSENTRY32;

/* aa450938 "THREADENTRY32 (Windows CE 5.0)": a thread entry of a
 * snapshot.  CE 1.0+; Tlhelp32.h.  CE-only trailing th32AccessKey and
 * th32CurrentProcessID are published members. */
typedef struct tagTHREADENTRY32 {
    DWORD dwSize;
    DWORD cntUsage;
    DWORD th32ThreadID;
    DWORD th32OwnerProcessID;
    LONG  tpBasePri;
    LONG  tpDeltaPri;
    DWORD dwFlags;
    DWORD th32AccessKey;       /* CE-only */
    DWORD th32CurrentProcessID;/* CE-only */
} THREADENTRY32, *PTHREADENTRY32, *LPTHREADENTRY32;

/* ms886756 "MODULEENTRY32 (Windows CE 5.0)": a module entry of a
 * snapshot.  CE 1.0+; Tlhelp32.h.  modBaseAddr is a BYTE* and the two
 * name strings are full path/long name on CE. */
typedef struct tagMODULEENTRY32 {
    DWORD   dwSize;
    DWORD   th32ModuleID;
    DWORD   th32ProcessID;
    DWORD   GlblcntUsage;
    DWORD   ProccntUsage;
    BYTE   *modBaseAddr;
    DWORD   modBaseSize;
    HMODULE hModule;
    TCHAR   szModule[MAX_PATH];
    TCHAR   szExePath[MAX_PATH];
    DWORD   dwFlags;
} MODULEENTRY32, *PMODULEENTRY32, *LPMODULEENTRY32;

/* ms885660 "HEAPLIST32 (Windows CE 5.0)": heap list entry of a
 * snapshot (process's heaps), filled by Heap32ListFirst/Next. */
typedef struct tagHEAPLIST32 {
    DWORD dwSize;
    DWORD th32ProcessID;
    DWORD th32HeapID;
    DWORD dwFlags;
} HEAPLIST32, *PHEAPLIST32, *LPHEAPLIST32;

/* ms885658 "HEAPENTRY32 (Windows CE 5.0)": heap block entry of a
 * snapshot, filled by Heap32First/Heap32Next. */
typedef struct tagHEAPENTRY32 {
    DWORD  dwSize;
    HANDLE hHandle;
    DWORD  dwAddress;
    DWORD  dwBlockSize;
    DWORD  dwFlags;
    DWORD  dwLockCount;
    DWORD  dwResvd;
    DWORD  th32ProcessID;
    DWORD  th32HeapID;
} HEAPENTRY32, *PHEAPENTRY32, *LPHEAPENTRY32;

/* ms885189 "CreateToolhelp32Snapshot (Windows CE 5.0)":
 * HANDLE WINAPI CreateToolhelp32Snapshot(DWORD, DWORD).  CE 2.0+;
 * Tlhelp32.h; Toolhelp.lib.  Takes a snapshot of processes, threads,
 * modules and heaps; INVALID_HANDLE_VALUE on failure. */
AKARI_CE_IMPORT HANDLE CreateToolhelp32Snapshot(DWORD dwFlags, DWORD th32ProcessID) AKARI_CE_NAME(CreateToolhelp32Snapshot);

/* ms885169 "CloseToolhelp32Snapshot (Windows CE 5.0)":
 * BOOL WINAPI CloseToolhelp32Snapshot(HANDLE).  CE 2.0+; Tlhelp32.h;
 * Toolhelp.lib. */
AKARI_CE_IMPORT BOOL CloseToolhelp32Snapshot(HANDLE hSnapshot) AKARI_CE_NAME(CloseToolhelp32Snapshot);

/* Process enumeration (snapshot must include TH32CS_SNAPPROCESS). */

/* ms886772/ms886773 "Process32First/Process32Next (CE 5.0)":
 * BOOL WINAPI Process32First/Next(HANDLE, LPPROCESSENTRY32).
 * CE 2.0+; Tlhelp32.h; Toolhelp.lib.  First/Next process entry. */
AKARI_CE_IMPORT BOOL Process32First(HANDLE hSnapshot, LPPROCESSENTRY32 lppe) AKARI_CE_NAME(Process32First);
AKARI_CE_IMPORT BOOL Process32Next(HANDLE hSnapshot, LPPROCESSENTRY32 lppe) AKARI_CE_NAME(Process32Next);

/* Thread enumeration (snapshot must include TH32CS_SNAPTHREAD). */

/* aa450934/aa450936 "Thread32First/Thread32Next (CE 5.0)":
 * BOOL WINAPI Thread32First/Next(HANDLE, LPTHREADENTRY32).
 * CE 2.0+; Tlhelp32.h; Toolhelp.lib. */
AKARI_CE_IMPORT BOOL Thread32First(HANDLE hSnapshot, LPTHREADENTRY32 lpte) AKARI_CE_NAME(Thread32First);
AKARI_CE_IMPORT BOOL Thread32Next(HANDLE hSnapshot, LPTHREADENTRY32 lpte) AKARI_CE_NAME(Thread32Next);

/* Module enumeration (snapshot must include TH32CS_SNAPMODULE). */

/* ms886754/ms886755 "Module32First/Module32Next (CE 5.0)":
 * BOOL WINAPI Module32First/Next(HANDLE, LPMODULEENTRY32).
 * CE 2.0+; Tlhelp32.h; Toolhelp.lib. */
AKARI_CE_IMPORT BOOL Module32First(HANDLE hSnapshot, LPMODULEENTRY32 lpme) AKARI_CE_NAME(Module32First);
AKARI_CE_IMPORT BOOL Module32Next(HANDLE hSnapshot, LPMODULEENTRY32 lpme) AKARI_CE_NAME(Module32Next);

/* Heap enumeration (snapshot must include TH32CS_SNAPHEAPLIST). */

/* ms885651/ms885652 "Heap32ListFirst/Heap32ListNext (CE 5.0)":
 * BOOL WINAPI Heap32ListFirst/Next(HANDLE, LPHEAPLIST32).
 * CE 2.0+; Tlhelp32.h (page ms885651 prints "Tlhelp.h"); Toolhelp.lib. */
AKARI_CE_IMPORT BOOL Heap32ListFirst(HANDLE hSnapshot, LPHEAPLIST32 lphl) AKARI_CE_NAME(Heap32ListFirst);
AKARI_CE_IMPORT BOOL Heap32ListNext(HANDLE hSnapshot, LPHEAPLIST32 lphl) AKARI_CE_NAME(Heap32ListNext);

/* ms885650/ms885653 "Heap32First/Heap32Next (CE 5.0)":
 * BOOL WINAPI Heap32First(HANDLE, LPHEAPENTRY32, DWORD, DWORD) and
 * Heap32Next(HANDLE, LPHEAPENTRY32).  CE 2.0+; Tlhelp32.h (page
 * ms885650 prints "Tlhelp.h"); Toolhelp.lib.  th32ProcessID/
 * th32HeapID of Heap32First come from a HEAPLIST32 entry. */
AKARI_CE_IMPORT BOOL Heap32First(HANDLE hSnapshot, LPHEAPENTRY32 lphe,
                 DWORD th32ProcessID, DWORD th32HeapID) AKARI_CE_NAME(Heap32First);
AKARI_CE_IMPORT BOOL Heap32Next(HANDLE hSnapshot, LPHEAPENTRY32 lphe) AKARI_CE_NAME(Heap32Next);

/* aa450953 "Toolhelp32ReadProcessMemory (Windows CE 5.0)":
 * BOOL WINAPI Toolhelp32ReadProcessMemory(DWORD, LPCVOID, LPVOID,
 * DWORD, LPDWORD).  CE 2.0+; Tlhelp32.h; Toolhelp.lib.  Reads another
 * process's memory (process identifiers may be cast to handles; other
 * processes require SetProcPermissions per the page). */
AKARI_CE_IMPORT BOOL Toolhelp32ReadProcessMemory(DWORD th32ProcessID,
                                 LPCVOID lpBaseAddress,
                                 LPVOID lpBuffer, DWORD cbRead,
                                 LPDWORD lpNumberOfBytesRead) AKARI_CE_NAME(Toolhelp32ReadProcessMemory);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_TLHELP32_H */
