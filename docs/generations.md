# Official information by CE generation

Microsoft's public Windows CE documentation is spread over several
archives; each CE generation a target program runs on maps to a
specific requirement row.  This file records, per generation, which
official pages exist, were fetched, and what they certify.  Only
official pages (learn.microsoft.com previous-versions / msdn.com
redirects) count as evidence.

## The three generations and their official sources

| Target | Official doc set | Form of per-function pages |
|---|---|---|
| CE 4.x (.NET 4.0–4.2) | pages in the `(v=msdn.10)` "Windows Embedded / MSDN" archive whose Requirements say "Windows CE .NET 4.x and later", plus the CE 3.0-era pages (`ms9xxxxx`, e.g. TerminateProcess `ms913239`, WideCharToMultiByte `ms915519`) for functions older than CE .NET | same page layout with OS-Versions row |
| CE 5.0 | the CE 5.0 documentation in the `(v=msdn.10)` archive (`wce50lrf*.htm` pages, built 2006) | per-function pages fetched for this project |
| CE 6.0 | surviving `(v=winembedded.60)` set on Learn (Platform Builder + CE 6.0 run-time overview pages, dated 2010); per-function API reference pages for the core APIs were not found in this archive — the reference used by CE 6.0 remains the `(v=msdn.10)` per-function set | overview pages e.g. `ee479262` |

## Pages fetched per generation for this project

**CE 3.0-era (covers CE 1.0–3.0 functions; minimum-version rows):
GetCommandLine `ms928607` (Unicode-only note), TerminateProcess
`ms913239` (CE 1.0+, Coredll.lib), WideCharToMultiByte `ms915519` and
MultiByteToWideChar `ms961248` (both with the official "OEM may not
support this API" note).

**CE 5.0 archive (`(v=msdn.10)`), all with Requirements transcribed
in `inventory.md`: TerminateProcess `aa450927`, TerminateThread
`aa450930`, ExitThread `ms885219`, ExitProcess `ms885217` (conflict
recorded), GetModuleHandle `ms885630`, GetModuleFileName `ms885629`,
GetCommandLine `ms885605`, GetProcAddress `ms885634`, LocalAlloc
`ms886739`, LocalFree `ms886741`, CreateProcess `ms885182`,
CreateThread `ms885186`, GetLastError `ms885627`, LoadLibrary
`ms886736`, FreeLibrary `ms885601`, plus the CRT/entry set
(ms859579–ms859596, ms885202, ms914104, ms859584, ms859588,
aa449732, ms885217 etc. — see wince-crt).

**M4–M8 batches — additional `(v=msdn.10)` CE 5.0 pages fetched and
transcribed (full per-function list with Requirements in
`docs/inventory.md`):** CloseHandle `aa517300`, OpenProcess
`ms886766`, GetExitCodeProcess `ms885622`, SetLastError `ms886817`,
SuspendThread `aa450913`, ResumeThread `ms886801`, GetExitCodeThread
`ms885623`, Sleep `aa450900`, GetThreadPriority `ms885643`,
SetThreadPriority `aa450891`, TLS `aa450945`/`aa450947`/`aa450951`/
`aa450949`, LoadLibraryEx `ms886737`, CreateFile `aa517318`,
DeleteFile `ms889001`, GetFileAttributes `ms890895`, FindFirstFile/
FindNextFile/FindClose `ms889678`/`ms889873`/`ms889619`, FILETIME
`ms885586`, WIN32_FIND_DATA `ms892378`, SYSTEMTIME `aa450923`,
GetLocalTime `ms885628`, GetSystemTime `ms885640`, SetLocalTime
`ms886818`, SetSystemTime `aa450867`, the four file-time conversions
`ms885589`/`ms886740`/`ms885593`/`aa450925`, ReadFile `ms891445`,
WriteFile `ms892380`, GetFileSize `ms890939`, SetFilePointer
`ms891933`, SetEndOfFile `ms891916`, FlushFileBuffers `ms890238`,
MoveFile `ms891388`, CopyFile `aa517309`, CreateDirectory
`aa517316`, RemoveDirectory `ms891470`, SetFileAttributes `ms891925`;
error table System Errors - Numerical Order `aa450919`; index page
Error Values `aa450740`; priority levels `aa450596`; kernel-scope
kfuncs pages `ms885613`–`ms885616` (conflict rows only).

**CE 6.0 archive (`(v=winembedded.60)`): Input and Output
`ee479262` (CE 6.0 run-time I/O overview: CE 6.0 CRT includes the
security-enhanced `_s` variants and deprecates plain forms; the
overview points to the shared Alphabetical Function Reference).

## What the generation rows certify for the shipped headers

Every shipped function's minimum OS-Versions row is at or below all
three targets (minima seen: CE 1.0, 1.01, 2.0, 2.10, 3.0), so one
declaration serves CE 4.2/5.0/6.0.  CE 6.0-specific deltas observed
in official pages so far are CRT-side (`_s` variants — libc scope,
not this repository) and export-surface additions in the sysroot
defs (e.g. GetProcAddressInProcess, CE 6 only) — no delta affects a
shipped header yet; any future delta is recorded here when its page
is fetched.

## Next batches (zero-gap policy)

The M1–M8 shipped declarations cover process/thread/module/TLS/
scheduling/file-I/O/directory/time and the error-code table.  Queued
next, each function page fetched (from official See-Also lists) and
transcribed before its declaration ships: synchronization objects
(CreateEvent/SetEvent/ResetEvent/WaitForSingleObject/...), heap and
local/global memory completion, string functions (lstrlen/lstrcpy/
...), and the winuser.h (GUI) / winreg.h (registry) header sets.
Category index pages to mine: Process and Thread Functions
`aa450760` and the winuser/winreg category indices.
