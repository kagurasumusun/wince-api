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

## Still unverified / next batches (zero-gap policy)

Per-function pages queued with known official IDs (from official
See-Also lists): OpenProcess `ms886766`, GetExitCodeProcess
`ms885622`, GetExitCodeThread `ms885623`, ResumeThread `ms886801`,
CloseHandle `aa517300`, LoadLibraryEx `ms886737`, SetLastError
`ms886817`, ThreadProc `aa450940`, PROCESS_INFORMATION `ms886775`,
Error Values `aa450740`, category index Process and Thread Functions
`aa450760`.  Each is fetched and transcribed before its declaration
ships.
