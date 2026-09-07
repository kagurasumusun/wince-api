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

**M23 batch — Serial Communications Reference (winbase.h):** all 16
functions + COMMTIMEOUTS/COMSTAT/DCB/COMMPROP structures from the CE
5.0 archive pages (ms885166-885173, 885192, 885213, 885606-885610,
886785, 886804-886807, aa450896/450957/450985).  Function pages:
Header Winbase.h, Link Library Serdev.lib (new def/serdev-doc.def, 16
exports; NOT in coredll).  EscapeCommFunction is CE 2.10+, the rest
CE 1.0+.  WaitCommEvent lpOverlapped ignored/set NULL on CE; serial
constants' values unpublished on the pages -> unknown, not defined.
Host check passes; six-target clang crosscheck pending re-acquisition
of the (session-deleted) LLVM-WinCE toolchain.

**M24 batch — Exception Reference + Debugging Reference (bulk):**
new headers excpt.h (AbnormalTermination/GetExceptionCode/
GetExceptionInformation/EXCEPTION_POINTERS), dbgapi.h (DBGPARAM,
NKDbgPrintfW, RegisterDbgZones, WriteDebugLED), errorrep.h (ReportFault
ms886799); winnt.h gained EXCEPTION_RECORD (ms885216), CONTEXT opaque
(ms885174, layout unpublished -> incomplete), the ms885620 EXCEPTION_*
codes, EXCEPTION_MAXIMUM_PARAMETERS and continuable flags; winbase.h
gained RaiseException, DebugBreak, ContinueDebugEvent,
DebugActiveProcess, WaitForDebugEvent, OutputDebugString(W) and the
DEBUG_EVENT record family + event-code/DBG_* constants.  Debug macro
pages recorded but not expanded (driver/zone machinery).  SEH
intrinsics excluded from export def (NOT_EXPORTS).  coredll def 164 ->
171.  Host + six CE targets pass; all defs llvm-dlltool-armce verified.

**M25 batch — Error Values + NAT Reference + CeLog functions (bulk):**
winerror.h completed to the full official System Errors page (aa450919:
+427 rows to code 6118) and the NTE/CRYPT/CERTSRV/TRUST namespaces
(+91; aa451033/026/023/035); RAS (ms886792 "RASBASE+n") and NERR
(ms886761/762 conflict with desktop Net Error Codes) recorded unknown.
251 -> 769 defines.  FormatMessageW (ms885599; Fmtmsg.lib) +
FORMAT_MESSAGE_* flags in winbase.h; new def/fmtmsg-doc.def.  New
include/natedit.h (NAT Reference: Natedit.h / Coredll.dll rows;
IP_NAT_DIRECTION, IP_NAT_SESSION_MAPPING_STATISTICS, IPRcvBuf, ticket/
session/editor APIs, PNAT_LOG_* typedefs; IP_NAT_REGISTER_EDITOR as
incomplete type -- PNAT_EDITOR_* member types unpublished).  New
include/celog.h (seven CeLog functions, Celog.h/Coredll.lib; CEL_*
event-record pages recorded not transcribed).  windef.h ABI typedefs
UCHAR..NTSTATUS added.  coredll def 171 -> 192 exports (192 + coreloc
23 + toolhelp 13 + serdev 16 + fmtmsg 1 + lmem 1 + loadstr 1 = 247).
Host + six CE targets pass; toolchain re-acquired from the Actions
artifact; all defs llvm-dlltool-armce verified.

**M26 batch — GWES window-manager core (Windows / Window Class /
Window Properties / Windows Timer / Carets / Atoms / Message Queue /
Message Synchronization / Keyboard / Scroll Bars books):** first
user-interface batch.  New `include/winuser.h` declares the window,
class, property (typedefs only), timer, caret, atom, message-queue,
keyboard and scroll API surface; Header-home follows each page's
Header row, so window properties, atoms, GetMessageQueueReadyTimeStamp,
SendMessageTimeout and ScrollDC (pages print Windows.h) live in
windows.h and KillTimer + MsgWaitForMultipleObjects(Ex) (Winbase.h)
in winbase.h.  windef.h gained the fixed Win32-ABI window/message
types (HWND/HMENU/.../HKL, ATOM, WPARAM/LPARAM/LRESULT/DWORD_PTR,
POINT/RECT/SIZE, SHORT, MAKELONG).  Transcribed structures:
CREATESTRUCT/STYLESTRUCT/WINDOWPOS, ACCEL (WORD pad member),
KEYBDINPUT/MOUSEINPUT/INPUT + HARDWAREINPUT (fixed layout from MS's
official Win32 structure reference; no CE leaf), SCROLLINFO (CE 5
Scroll-Bars-Structures book points at the CE 6 twin ee504371).
Message books (28 WM_* pages) fetched and recorded; CE pages publish
no numeric message values so WM_* constants wait for the follow-on
messages batch.  Six OEM Keyboard leaves (Header Pwinuser.h/Keybd.h,
GET_FOREGROUND_INFO/KEY_STATE_FLAGS types) deferred to an
OEM/input-method batch (KEY_STATE_FLAGS values unpublished).  Export
surface: 14 GWES manifests (156 pages, rows 510 -> 666) add coredll
192 -> 221 and eleven new component-module defs (accel, caret,
foregnd, hotkey, kbdui, coreimm, msgque, sbcmn, uibase, winmgr,
wmgr_c): 7 -> 18 defs.  All 18 defs llvm-dlltool-armce verified;
host + six CE targets pass.

**M27 batch — GDI Reference, GDI Functions + GDI Structures (bulk):**
second graphics/user-interface batch, landed together as one unit with
the whole GDI book of the CE 5.0 archive: 132 GDI Functions + 29 GDI
Structures leaves (manifests tools/manifests/gdi-*.manifest), rows 666
-> 827.  Prototype recovery: the CE 5.0 (v=msdn.10) migration strips
whitespace inside <pre> prototypes (99 of 161 GDI pages parse
"no-sig"), so each signature was recovered from the official CE 6.0
(v=winembedded.60) twin of the same page (161/161 fetched, spaced
intact) and cross-checked to the CE 5.0 body; both archives' page ids
are on the declarations.  New include/wingdi.h (129 declared GDI
functions + bitmap/color/palette/pen/brush/region/DEVMODE/display/
gradient/font structures; the GDI items whose CE 5.0 rows name Header
Windows.h) and include/tvout.h (VIDEOPARAMETERS ms914096, Header
Tvout.h); windef.h gains the fixed-ABI GDI handles HGDIOBJ/HPEN/
HPALETTE and the Windef.h-row structures POINTS/RECTL; winuser.h gains
the 27 Header-Winuser.h items (paint/DC/update/coordinate/rectangle)
plus PAINTSTRUCT; winbase.h gains InflateRect and SetRect (Header
Winbase.h rows).  GetRValue/GetGValue/GetBValue are documented by the
official pages as macros with verbatim bodies and no Link Library row
and are defined as macros (not exports).  Fixed Win32-ABI types the CE
pages reference but never define are provided with records: XFORM
(ExtCreateRegion aa453061, "not supported; set NULL"), PANOSE
(OUTLINETEXTMETRICW ms934025), GUID (VIDEOPARAMETERS ms914096),
FLOAT/COLOR16/BCHAR/CCHDEVICENAME/CCHFORMNAME.  Page typos preserved
with notes: TransparentBlt 8th parameter "hHeightDest" (sic), SetLayout
stray trailing comma, BITMAPINFOHEADER code block missing a separator
(authoritative member list used).  Seven viewport/window origin/extent
pages omit the prototype return type; their "Return Values" text fixes
BOOL.  Export surface: coredll 221 -> 335, winmgr 1 -> 17, new defs
rectapi-doc.def (11), loadbmp-doc.def (1), nclient-doc.def (1): 18 ->
21 def files, 457 name-only exports, all llvm-dlltool-armce verified.
gen-doc-def.py gained trailing-annotation stripping in short_title
("CreatePalette (GDI)" -> export CreatePalette) and host TU exercises
all 129 functions with typed calls plus structure-layout checks.  Host
+ six CE targets (arm/i386 x 4.2/5.0/6.0) pass warning-free.

**M29 batch — Image List Reference book + GWES message/notification
constants (two units landed together):** new `include/commctrl.h` for
the full CE 5.0 **Image Lists** book (Functions 32 / Macros 4 /
Structures 2 = 38 leaves; Header Commctrl.h, Link Library rows
Commctrl.lib + Imgctl.lib; HIMAGELIST supplied as an opaque handle
typedef, the pages use the type without republishing it), with every
signature recovered from the official CE 6.0 `(v=winembedded.60)`
twins (the CE 5.0 migration strips prototype whitespace) and the twin
ids on the declarations.  `include/winuser.h` gains the GWES
message/notification constant surface: the Buttons / Static Controls /
Menus / Dialog Boxes / Clipboards / GDI message leaves (BM/BN/STM/STN/
WM_COMMAND/WM_CONTEXTMENU/menu/dialog/clipboard/CTLCOLOR numbers), the
M26-announced numeric transcription of the Windows-Messages and
Keyboard-Messages leaves, the Combo/List/Edit message and notification
identifiers (CB_*/CBN_*, LB_*/LBN_*, EM_*/EN_*), and the
IMAGE_BITMAP/ICON/CURSOR uType values (IMAGE_ENHMETAFILE is not
documented for CE and is not shipped); `include/wingdi.h` gains the
ternary/binary ROP code macros
(SRC*/PAT*/R2_*).  CE pages document message names and parameters but
not the numeric identifiers, so all numeric values are recorded as the
fixed Win32 ABI values of the message protocol GWES implements
(CE-6-twin-checked; notification codes with CE pages keep their page
ids).  EN_* edit codes use the fixed 0x0100-range values
(EN_SETFOCUS 0x0100 .. EN_VSCROLL 0x0602).  rows.json 939 -> 1175
(69 manifests; the full committed CE 5.0 manifest set was re-fetched
and `build/rows.json` regenerated from scratch, harvesting for the
first time the Combo/List/Edit message and style book leaves).
Export surface: 31 -> 33 def files via new commctrl-doc.def and
imgctl-doc.def (31 exports each, from the documented Link Library
rows), coredll unchanged, 543 -> 605 name-only exports, both new defs
llvm-dlltool-`-m armce` verified.  ImageList_Destroy (ms909811) is
declared but carries no Link Library row in either archive and enters
no import def (recorded).  Host TU type-checks all 32 Image List calls
and static-asserts IMAGEINFO = 32 and IMAGELISTDRAWPARAMS = 56 bytes
on the 32-bit ABI; host + six CE targets (arm/i386 x 4.2/5.0/6.0)
pass warning-free.


**M30 batch — corpus-preservation pipeline + remaining
Winbase.h/Windows.h gap fill:** `tools/ce-corpus.py` (export/import/
verify) + `docs/corpus.md` establish the owner workflow of saving every
official page fully, pushing it to `kagurasumusun/wince-docs-corpus`
(CE 5.0 1175 + CE 6.0 38 pages + rows.json + catalogs, pushed 2026-09),
deleting it at session end and re-fetching from GitHub at the next
session start (raw MS Learn HTML never enters the MIT tree).  A machine
audit of rows.json vs headers found 63 signature-bearing rows without a
declaration; after removing the recorded intentional non-exports
(debug macros, Kfuncs/Pwinuser scope, callbacks, keyword false
positives) the genuine missing user-mode exports were implemented:
FreeLibraryAndExitThread (ms885602), CeZeroPointer (ms885158),
CeGetThreadQuantum (aa450796), CeSetThreadQuantum (ms885156),
VerQueryValueW (aa450973, Unicode-only spelling), IsProcessorFeaturePresent
(ms886726), QueryInstructionSet (ms886787) in winbase.h and
SetUserDefaultLCID (ms906279, Header Windows.h, Coreloc.lib) in
windows.h.  Flag/value sets the CE pages document by name only
(PF_ARM_*, PROCESSOR_*_INSTRUCTION) are recorded, not invented.
Deferred with reasons: CeHeapCreate (OEM Pkfuncs callback prototypes),
thread/process context functions (per-CPU CONTEXT layout unpublished),
TranslateCharsetInfo (needs CHARSETINFO + TCI_*).  Export surface:
coredll 353 -> 360, coreloc 23 -> 24, total name-only exports 605 ->
613 (33 def files); gen-doc-def gains VerQueryValue -> VerQueryValueW.
Host + six CE targets (arm/i386 x 4.2/5.0/6.0) pass warning-free.


**M31 batch — WM_COPYDATA + cross-process read / thread context +
version-resource + character-set units:** second rows.json-vs-headers
audit pass using a word-boundary matcher over all 1175 titles; the
201-item gap triaged to recorded non-exports (index/style/error-table
pages, CEL_* kernel payloads, debug macros, Kfuncs/Pwinuser, NAT
callbacks) plus these implemented units: WM_COPYDATA = 0x004A in
winuser.h (aa453921); ReadProcessMemory (ms886794) and GetThreadContext
(ms885642) in winbase.h (Coredll.lib + Nk.lib rows; CONTEXT stays the
M24 incomplete type, LPCONTEXT alias added in winnt.h); VS_FIXEDFILEINFO
+ the six VS_FF_* flags in winbase.h (aa450983, dwSignature 0xFEEF04BD
as the page documents); FONTSIGNATURE (ms885597), CHARSETINFO +
LPCHARSETINFO (ms885163) and TranslateCharsetInfo with TCI_SRCCHARSET/
TCI_SRCCODEPAGE/TCI_SRCFONTSIG (aa450955) in wingdi.h.  Names-only
documented sets (*_CHARSET, FS_*, WM_SYSCOPYDATA, EXTENDED_NAME_FORMAT,
COPY_FILE_*) and the deferred functions (CopyFileEx, GetUserNameEx,
CeHeapCreate, Nk-only WriteProcessMemory/SetThreadContext) are recorded
in inventory.md with reasons; crypto/NTE/TRUST/CERTSRV/RAS/Net error
tables are not numeric on the CE pages and remain recorded-not-
transcribed.  Export surface: coredll 360 -> 363, total name-only
exports 613 -> 616 (33 def files).  Host + six CE targets pass
warning-free; TU static-asserts FONTSIGNATURE=24 / CHARSETINFO=32 /
VS_FIXEDFILEINFO=52 on the 32-bit ABI.
