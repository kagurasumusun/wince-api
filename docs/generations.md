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

**M9 batch — harvested from the official TOC (learn.microsoft.com
`previous-versions/windows/embedded/toc.json`) with
`tools/ce-manifest.py` + `tools/ce-fetch.py`; manifests in
`tools/manifests/core-*.manifest`:**

* *Core OS Reference → Synchronization Reference* (26 pages):
  CreateEvent `ms885177`, CreateMutex `ms885181`, CreateSemaphore
  `ms885184`, DeleteCriticalSection `ms885196`, DuplicateHandle
  `ms885208`, EnterCriticalSection `ms885212`, InitializeCriticalSection
  `ms885665`, the interlocked family `ms885667`–`ms885674`,
  LeaveCriticalSection `ms886733`, OpenEvent `ms886764`, PulseEvent
  `ms886784`, ReleaseMutex `ms886797`, ReleaseSemaphore `ms886798`,
  ResetEvent `ms886800`, SetEvent `ms886810`, TryEnterCriticalSection
  `aa450959`, WaitForMultipleObjects `aa450987`, WaitForSingleObject
  `aa450988`.
* Also manifested and fetched for the next batches (records in
  `build/rows.json`, def membership validated there): *Memory
  Management Reference* (28), *Time Reference* (25), *Process and
  Thread Reference* (41), *Strings Reference* (14), *Unicode
  Reference* (11), *System Management Reference* (17), *DLL Reference*
  (13), *ToolHelp Reference* (20), *Fiber Reference* (8).
* Cross-book page count fetched and parsed so far: 203 official pages.

The 25 M9 synchronization declarations (plus `winnt.h`) are shipped;
their page rows (including the Nk.lib / Coremain.lib rows) and the
critical-section layout basis are transcribed in `docs/inventory.md`.

**M10 batch — Time Reference + Memory Management Reference**
(no new fetches: the 203 harvested rows already covered these books;
the pages are the same `(v=msdn.10)` CE 5.0 archive):

* *Time Reference* (10 shipped): GetTickCount `ms885645`, GetFileTime
  `ms885625`, SetFileTime `ms886812`, CompareFileTime `ms885172`,
  GetCurrentFT `aa451027`, GetIdleTime `ms885626`, Random `ms886791`,
  SetDaylightTime `ms886808`, QueryPerformanceCounter `ms886788`,
  QueryPerformanceFrequency `ms886789`.
* *Memory Management Reference* (16 shipped): GetProcessHeap
  `ms885635` (Lmem.lib row), HeapCreate `ms885656`, HeapDestroy
  `ms885657`, HeapAlloc `ms885654`, HeapFree `ms885659`, HeapReAlloc
  `ms885661`, HeapSize `ms885662`, HeapValidate `ms885663`,
  HeapCompact `ms885655`, LocalReAlloc `ms886742`, LocalSize
  `ms886743`, GlobalMemoryStatus `ms885649`, IsBadCodePtr `ms885687`,
  IsBadReadPtr `ms885688`, IsBadWritePtr `ms885689`, plus the
  `MEMORYSTATUS` structure page `ms886753`.
* Both M10 batches are shipped in winbase.h; def regenerated
  (53 → 77 exports).  Full rows in `docs/inventory.md`.

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

**M11 batch — System Management Reference (part 1):** GetSystemInfo
`ms885638`, SYSTEM_INFO `aa450921`, GetVersionEx `ms885648`,
OSVERSIONINFO `ms886768`, SignalStarted `aa450898` (+ the
PROCESSOR_ARCHITECTURE_* and VER_PLATFORM_* constants with fixed
Win32 ABI values).  QueryInstructionSet `ms886787`,
IsProcessorFeaturePresent `ms886726` and VerQueryValue `aa450973` are
recorded as deferred (unpublished numeric flag values / Coredll.dll
row); rows in `docs/inventory.md`.  Def: 77 -> 80 exports.

**M12 batch — virtual memory / time zone / version-timing:** VirtualAlloc
`aa450975`, VirtualFree `aa450979`, VirtualProtect `aa450980`,
VirtualQuery `aa450981` (+ MEMORY_BASIC_INFORMATION `ms886752` in
winnt.h, MEM_*/PAGE_* constants), FlushInstructionCache `ms885595`,
GetProcessVersion `ms885636`, GetDllVersion `ms885617`, GetThreadTimes
`ms885644`, TIME_ZONE_INFORMATION `aa450943`, GetTimeZoneInformation
`ms885646`, SetTimeZoneInformation `aa450893`, TIME_ZONE_ID_*
constants.  Def: 80 -> 90 exports.

**M13 batch — code-page / NLS (new header `winnls.h`):**
MultiByteToWideChar `ms886760`, WideCharToMultiByte `aa450989`,
IsDBCSLeadByte `ms886515`, IsDBCSLeadByteEx `ms886608` + CP_*, MB_*,
WC_* constants; `BYTE`/`LPBOOL` added to windef.h.  Def: 90 -> 94
exports.

**M14 batch — Fiber Reference:** CreateFiber `ms885178`,
ConvertThreadToFiber `ms885176`, DeleteFiber `ms885197`,
GetCurrentFiber `ms885611`, GetFiberData `ms885624`, SwitchToFiber
`aa450915`, LPFIBER_START_ROUTINE/PFIBER_START_ROUTINE per FiberProc
`ms885221`.  Def: 94 -> 100 exports.

**M15 batch — Registry Reference (new header `winreg.h`):**
RegCloseKey `ms891448`, RegCreateKeyEx `ms891450`, RegDeleteKey
`ms891451`, RegDeleteValue `ms891452`, RegEnumKeyEx `ms891453`,
RegEnumValue `ms891454`, RegFlushKey `ms891455`, RegOpenKeyEx
`ms891460`, RegQueryInfoKey `ms891461`, RegQueryValueEx `ms891462`,
RegSetValueEx `ms891469`, CeFindFirstRegChange `aa517116`,
CeFindNextRegChange `aa517123`, CeFindCloseRegChange `aa517103` +
HKEY/PHKEY/REGSAM types, predefined-key and REG_*/REG_OPTION_*/REG_
NOTIFY_* constants.  Def: 100 -> 114 exports.  New manifests:
`tools/manifests/core-registry-reference.manifest` (16 pages) and
`core-nls-reference.manifest` (46 pages); harvested rows 203 -> 265.

**M16 batch — NLS Reference (part 1):** GetACP `ms905215`, GetOEMCP
`ms905256`, GetSystemDefaultLCID `ms905298`, GetUserDefaultLCID
`ms905323`, GetSystemDefaultLangID `ms905289`, GetUserDefaultLangID
`ms905315`, IsValidCodePage `ms906218`, IsValidLocale `ms906219`,
CompareString `ms904713`, ConvertDefaultLocale `ms904716`, GetCPInfo
`ms905221` + CPINFO `ms904717`, GetStringTypeW `ms905272` (Coredll.lib
row), GetStringTypeEx `ms905283`; CT_*/LCID_*/CSTR_*/MAX_* constants;
LANGID/LCID types (windef.h); PRIMARYLANGID/SUBLANGID/MAKELANGID/
MAKELCID macros (winnt.h, formulas printed on the pages).  Def:
114 -> 115 exports.

**M17 batch — File I/O Reference continuation:** FindFirst/Next/
CloseChangeNotification `ms889670`/`ms889784`/`ms889625`, FindFirstFileEx
`ms889683` + FINDEX_INFO_LEVELS/FINDEX_SEARCH_OPS `ms889654`/`ms889664`,
GetFileAttributesEx `ms890909` + WIN32_FILE_ATTRIBUTE_DATA `ms892377`,
GetDiskFreeSpaceEx `ms890887`, GetFileInformationByHandle `ms890926` +
BY_HANDLE_FILE_INFORMATION `aa516973` (CE dwOID member), GetTempPath
`ms891189`, GetTempFileName `ms891186`, LockFileEx `ms891385`,
UnlockFileEx `ms892364`, DeleteAndRenameFile `ms887981`,
GetFileVersionInfoSize/GetFileVersionInfo `ms890963`/`ms890951`.
New manifest `tools/manifests/file-io-reference.manifest` (51 pages);
rows 265 -> 316.  Def: 115 -> 147 exports (file I/O rows now included
in the public record set, e.g. CreateFileW/ReadFile/WriteFile).

**M18 batch — ToolHelp Reference (new header `tlhelp32.h`):**
CreateToolhelp32Snapshot `ms885189`, CloseToolhelp32Snapshot
`ms885169`, Process32First/Next `ms886772`/`ms886773`,
Thread32First/Next `aa450934`/`aa450936`, Module32First/Next
`ms886754`/`ms886755`, Heap32ListFirst/Next `ms885651`/`ms885652`,
Heap32First/Next `ms885650`/`ms885653`, Toolhelp32ReadProcessMemory
`aa450953` + PROCESSENTRY32 `ms886774` (CE th32MemoryBase/
th32AccessKey), THREADENTRY32 `aa450938` (CE th32AccessKey/
th32CurrentProcessID), MODULEENTRY32 `ms886756`, HEAPLIST32
`ms885660`, HEAPENTRY32 `ms885658`, TH32CS_* flags.  Header per the
pages (Tlhelp32.h); Link Library Toolhelp.lib (not coredll).  Layout
asserts 32-bit model pass on the CE toolchain.

**M19 batch — Strings Reference + multi-lib def generation:**
CharLower/CharLowerBuff `ms885159`/`ms885160`, CharUpper/CharUpperBuff
`ms885164`/`ms885165`, CharNext `ms885161` (Coredll.lib), CharPrev
`ms885162`, IsCharAlpha/IsCharAlphaNumeric/IsCharLower/IsCharUpper
`ms885690`-`ms885693`, LoadString `ms886738` (Loadstr.lib), wsprintf
`aa450993`, wvsprintf `aa450994`.  Most pages state Unicode-only ⇒ W
exports + base macros.  def generation generalized to one def per
documented user-mode Link Library: coredll 148, coreloc 23, toolhelp
13, lmem 1, loadstr 1 (all llvm-dlltool-verified); Nk/Coremain rows
remain excluded.

**M20/M20b batch — File Mapping Reference + DLL entry:**
CreateFileForMapping `aa517321`, CreateFileMapping `aa517331`,
MapViewOfFile `ms891386`, UnmapViewOfFile `ms892373`, FlushViewOfFile
`ms890303`, DisableThreadLibraryCalls `ms885200`, DLL_PROCESS/THREAD_
ATTACH/DETACH constants (per DllMain `ms885202`); new header
`include/psapi.h` with MODULEINFO `ms886757` + GetModuleInformation
`ms885631` (Psapi.h / Coredll.lib rows).  New manifest
`file-mapping-reference.manifest` (6 pages); coredll def
148 -> 154 exports.

**M21 batch — store info + Ce* file helpers + FILE_NOTIFY:**
GetStoreInformation `ms891023` + STORE_INFORMATION `ms891279`
(deprecated by the page; recorded as such), CeGenRandom `aa517140`,
CeGetCanonicalPathName `aa517144`, CeGetFileNotificationInfo
`aa517158` + FILE_NOTIFY_INFORMATION/FILE_ACTION_* (winnt.h,
`ms889597`).  Manifest file-io-reference.manifest 51 -> 52 pages.
coredll def 154 -> 158 exports.

**M22 batch — Message Queue Point-to-Point Reference (msgqueue.h):**
CloseMsgQueue `ms885168`, CreateMsgQueue `ms885180`, GetMsgQueueInfo
`ms885632`, OpenMsgQueue `ms886765`, ReadMsgQueue `ms886793`,
WriteMsgQueue `aa450991`, MSGQUEUEOPTIONS `ms886759`, MSGQUEUEINFO
`ms886758`.  Every page: OS Versions Windows CE .NET 4.0+, Header
Msgqueue.h, Link Library Coredll.lib.  New header include/msgqueue.h,
wired into windows.h + Makefile + host TU (32-bit layout asserts).
Flag values (MSGQUEUE_NOPRECOMMIT / MSGQUEUE_ALLOW_BROKEN /
MSGQUEUE_MSGALERT) unpublished on the pages -> recorded unknown, not
defined.  coredll def 158 -> 164 exports.
