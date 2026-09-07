/* TU smoke test for the Akari API headers (host, compile-only).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Compiled with -c for each CE generation value of _WIN32_WCE
 * (0x420, 0x500, 0x600).  Exercises every shipped declaration and the
 * generic-text mappings; verifies the target-independent type widths.
 * Pointer sizes are verified when the host is 32-bit; the 32-bit
 * pointer model itself is checked on the real CE toolchain later
 * (see docs/verification.md).
 */

#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <msgqueue.h>
#include <excpt.h>
#include <dbgapi.h>
#include <errorrep.h>
#include <celog.h>
#include <natedit.h>
#include <commctrl.h>
#include <stddef.h>

/* Type-width invariants of the CE ABI (32-bit, 16-bit wchar). */
typedef char assert_wchar_size[(sizeof(WCHAR) == 2) ? 1 : -1];
typedef char assert_dword_size[(sizeof(DWORD) == 4) ? 1 : -1];
typedef char assert_long_size[(sizeof(LONG) == 4) ? 1 : -1];
typedef char assert_handle_pointer[(sizeof(HANDLE) == sizeof(void *)) ? 1 : -1];

#if __SIZEOF_POINTER__ == 4
typedef char assert_ce_pointer_size[(sizeof(HANDLE) == 4) ? 1 : -1];
typedef char assert_ce_ulongptr_size[(sizeof(ULONG_PTR) == 4) ? 1 : -1];
/* M22: MSGQUEUEOPTIONS (ms886759) / MSGQUEUEINFO (ms886758) 32-bit CE
 * layout as transcribed from the official pages (Msqqueue.h; no tag
 * published, plain DWORD/BOOL/WORD members, 4-byte alignment). */
typedef char assert_msgqopt_size[(sizeof(MSGQUEUEOPTIONS) == 20) ? 1 : -1];
typedef char assert_msgqopt_ro[(offsetof(MSGQUEUEOPTIONS, bReadAccess) == 16) ? 1 : -1];
typedef char assert_msgqinfo_size[(sizeof(MSGQUEUEINFO) == 28) ? 1 : -1];
typedef char assert_msgqinfo_wo[(offsetof(MSGQUEUEINFO, wNumWriters) == 26) ? 1 : -1];
typedef char assert_msgqinfo_cm[(offsetof(MSGQUEUEINFO, dwCurrentMessages) == 16) ? 1 : -1];
/* M23: serial COMMTIMEOUTS (ms885171, 5 DWORDs) and DCB (ms885192,
 * page bit-field layout) 32-bit CE sizes. */
typedef char assert_ctmo_size[(sizeof(COMMTIMEOUTS) == 20) ? 1 : -1];
typedef char assert_dcb_size[(sizeof(DCB) == 28) ? 1 : -1];
/* M24: SEH/debugging 32-bit layout as transcribed from the CE pages:
 * EXCEPTION_RECORD (ms885216) = 80, DEBUG_EVENT (ms885195) = 96. */
typedef char assert_exrec_size[(sizeof(EXCEPTION_RECORD) == 80) ? 1 : -1];
typedef char assert_dbev_size[(sizeof(DEBUG_EVENT) == 96) ? 1 : -1];
#endif

/* Reference every declared function (no calls, compile-only). */
static const void *const api_symbols[] = {
    /* M26: GWES window/class/property/timer/caret/atom/message-queue/
     * keyboard/scroll surface (winuser.h/winbase.h/windows.h). */
    (const void *) &CreateWindowExW, (const void *) &CreateWindowW,
    (const void *) &RegisterClassW, (const void *) &UnregisterClassW,
    (const void *) &GetClassInfoW, (const void *) &GetClassLongW,
    (const void *) &SetClassLongW, (const void *) &GetClassNameW,
    (const void *) &GetWindowLongW, (const void *) &SetWindowLongW,
    (const void *) &GetDesktopWindow, (const void *) &GetForegroundWindow,
    (const void *) &SetForegroundWindow, (const void *) &IsWindow,
    (const void *) &IsWindowVisible, (const void *) &IsChild,
    (const void *) &GetParent, (const void *) &SetParent,
    (const void *) &FindWindowW, (const void *) &ChildWindowFromPoint,
    (const void *) &WindowFromPoint, (const void *) &EnumWindows,
    (const void *) &GetWindow, (const void *) &GetClientRect,
    (const void *) &GetWindowRect, (const void *) &GetWindowTextLengthW,
    (const void *) &GetWindowTextW, (const void *) &SetWindowTextW,
    (const void *) &GetWindowThreadProcessId, (const void *) &ShowWindow,
    (const void *) &BringWindowToTop, (const void *) &MoveWindow,
    (const void *) &SetWindowPos, (const void *) &AdjustWindowRectEx,
    (const void *) &DefWindowProc, (const void *) &CallWindowProc,
    (const void *) &DestroyWindow, (const void *) &BeginDeferWindowPos,
    (const void *) &DeferWindowPos, (const void *) &EndDeferWindowPos,
    (const void *) &SetTimer, (const void *) &KillTimer,
    (const void *) &SystemIdleTimerReset, (const void *) &CreateCaret,
    (const void *) &DestroyCaret, (const void *) &GetCaretBlinkTime,
    (const void *) &GetCaretPos, (const void *) &HideCaret,
    (const void *) &SetCaretBlinkTime, (const void *) &SetCaretPos,
    (const void *) &ShowCaret, (const void *) &GlobalAddAtomW,
    (const void *) &GlobalDeleteAtom, (const void *) &GlobalFindAtomW,
    (const void *) &GetMessage, (const void *) &PeekMessage,
    (const void *) &DispatchMessage, (const void *) &TranslateMessage,
    (const void *) &PostMessage, (const void *) &PostThreadMessage,
    (const void *) &SendMessage, (const void *) &SendNotifyMessage,
    (const void *) &PostQuitMessage, (const void *) &RegisterWindowMessageW,
    (const void *) &GetMessagePos, (const void *) &GetMessageQueueReadyTimeStamp,
    (const void *) &GetMessageSource, (const void *) &GetQueueStatus,
    (const void *) &InSendMessage, (const void *) &GetKeyState,
    (const void *) &GetAsyncKeyState, (const void *) &GetFocus,
    (const void *) &SetFocus, (const void *) &GetActiveWindow,
    (const void *) &SetActiveWindow, (const void *) &EnableWindow,
    (const void *) &IsWindowEnabled, (const void *) &ActivateKeyboardLayout,
    (const void *) &GetKeyboardLayout, (const void *) &GetKeyboardLayoutList,
    (const void *) &GetKeyboardLayoutNameW, (const void *) &GetKeyboardStatus,
    (const void *) &GetKeyboardType, (const void *) &MapVirtualKey,
    (const void *) &keybd_event, (const void *) &LoadKeyboardLayout,
    (const void *) &RegisterHotKey, (const void *) &UnregisterHotKey,
    (const void *) &CreateAcceleratorTable, (const void *) &LoadAcceleratorsW,
    (const void *) &DestroyAcceleratorTable, (const void *) &TranslateAccelerator,
    (const void *) &SendInput, (const void *) &GetScrollInfo,
    (const void *) &SetScrollInfo, (const void *) &SetScrollPos,
    (const void *) &SetScrollRange, (const void *) &ScrollWindowEx,
    (const void *) &ScrollDC, (const void *) &SetPropW,
    (const void *) &GetPropW, (const void *) &RemovePropW,
    (const void *) &EnumPropsExW, (const void *) &SendMessageTimeout,
    (const void *) &MsgWaitForMultipleObjects,
    (const void *) &MsgWaitForMultipleObjectsEx,
    /* M25: Error Values + NAT + CeLog (winbase.h/celog.h/natedit.h). */
    (const void *) &FormatMessageW, (const void *) &FormatMessage,
    (const void *) &CeLogData,
    (const void *) &CeLogGetZones,
    (const void *) &CeLogInterrupt,
    (const void *) &CeLogMsg,
    (const void *) &CeLogQueryZones,
    (const void *) &CeLogReSync,
    (const void *) &CeLogSetZones,
    (const void *) &EditorInitialize,
    (const void *) &RegisterEditor,
    (const void *) &CreateHandler,
    (const void *) &DataHandler,
    (const void *) &DeleteHandler,
    (const void *) &CreateTicket,
    (const void *) &DeleteTicket,
    (const void *) &EditSession,
    (const void *) &QueryInfoSession,
    (const void *) &TimeoutSession,
    (const void *) &DisassociateSession,
    (const void *) &EditorDeregister,
    /* M24: SEH + debugging (winbase.h/excpt.h/dbgapi.h/errorrep.h). */
    (const void *) &RaiseException,
    (const void *) &DebugBreak,
    (const void *) &ContinueDebugEvent,
    (const void *) &DebugActiveProcess,
    (const void *) &WaitForDebugEvent,
    (const void *) &OutputDebugStringW,
    (const void *) &NKDbgPrintfW,
    (const void *) &RegisterDbgZones,
    (const void *) &WriteDebugLED,
    (const void *) &ReportFault,
    (const void *) &AbnormalTermination,
    (const void *) &GetExceptionCode,
    (const void *) &GetExceptionInformation,
    /* M23: serial communications (winbase.h; Serdev.lib). */
    (const void *) &ClearCommBreak,
    (const void *) &ClearCommError,
    (const void *) &EscapeCommFunction,
    (const void *) &GetCommMask,
    (const void *) &GetCommModemStatus,
    (const void *) &GetCommProperties,
    (const void *) &GetCommState,
    (const void *) &GetCommTimeouts,
    (const void *) &PurgeComm,
    (const void *) &SetCommBreak,
    (const void *) &SetCommMask,
    (const void *) &SetCommState,
    (const void *) &SetCommTimeouts,
    (const void *) &SetupComm,
    (const void *) &TransmitCommChar,
    (const void *) &WaitCommEvent,
    /* M22: point-to-point message queues (msgqueue.h; Coredll.lib). */
    (const void *) &CloseMsgQueue,
    (const void *) &CreateMsgQueue,
    (const void *) &GetMsgQueueInfo,
    (const void *) &OpenMsgQueue,
    (const void *) &ReadMsgQueue,
    (const void *) &WriteMsgQueue,
    (const void *) &TerminateProcess,
    (const void *) &TerminateThread,
    (const void *) &ExitThread,
    (const void *) &ExitProcess,
    (const void *) &GetModuleHandleW,
    (const void *) &GetModuleHandle,
    (const void *) &GetModuleFileNameW,
    (const void *) &GetModuleFileName,
    (const void *) &GetCommandLineW,
    (const void *) &GetCommandLine,
    (const void *) &GetProcAddressW,
    (const void *) &GetProcAddressA,
    (const void *) &GetProcAddress,
    (const void *) &LocalAlloc,
    (const void *) &LocalFree,
    (const void *) &GetLastError,
    (const void *) &CreateThread,
    (const void *) &CreateProcessW,
    (const void *) &CreateProcess,
    (const void *) &LoadLibraryW,
    (const void *) &LoadLibrary,
    (const void *) &FreeLibrary,
    (const void *) &CloseHandle,
    (const void *) &OpenProcess,
    (const void *) &GetExitCodeProcess,
    (const void *) &SetLastError,
    (const void *) &GetExitCodeThread,
    (const void *) &SuspendThread,
    (const void *) &ResumeThread,
    (const void *) &Sleep,
    (const void *) &GetThreadPriority,
    (const void *) &SetThreadPriority,
    (const void *) &TlsAlloc,
    (const void *) &TlsFree,
    (const void *) &TlsSetValue,
    (const void *) &TlsGetValue,
    (const void *) &LoadLibraryEx,
    (const void *) &LoadLibraryExW,
    (const void *) &CreateFile,
    (const void *) &CreateFileW,
    (const void *) &DeleteFile,
    (const void *) &DeleteFileW,
    (const void *) &FindFirstFile,
    (const void *) &FindFirstFileW,
    (const void *) &FindNextFile,
    (const void *) &FindNextFileW,
    (const void *) &FindClose,
    (const void *) &GetFileAttributes,
    (const void *) &GetFileAttributesW,
    (const void *) &ReadFile,
    (const void *) &WriteFile,
    (const void *) &GetFileSize,
    (const void *) &SetFilePointer,
    (const void *) &SetEndOfFile,
    (const void *) &FlushFileBuffers,
    (const void *) &MoveFileW,
    (const void *) &MoveFile,
    (const void *) &CopyFileW,
    (const void *) &CopyFile,
    (const void *) &CreateDirectoryW,
    (const void *) &CreateDirectory,
    (const void *) &RemoveDirectoryW,
    (const void *) &RemoveDirectory,
    (const void *) &SetFileAttributesW,
    (const void *) &SetFileAttributes,
    (const void *) &CreateEventW,
    (const void *) &CreateEvent,
    (const void *) &OpenEventW,
    (const void *) &OpenEvent,
    (const void *) &SetEvent,
    (const void *) &ResetEvent,
    (const void *) &PulseEvent,
    (const void *) &CreateMutexW,
    (const void *) &CreateMutex,
    (const void *) &ReleaseMutex,
    (const void *) &CreateSemaphoreW,
    (const void *) &CreateSemaphore,
    (const void *) &ReleaseSemaphore,
    (const void *) &WaitForSingleObject,
    (const void *) &WaitForMultipleObjects,
    (const void *) &DuplicateHandle,
    (const void *) &InitializeCriticalSection,
    (const void *) &EnterCriticalSection,
    (const void *) &LeaveCriticalSection,
    (const void *) &DeleteCriticalSection,
    (const void *) &TryEnterCriticalSection,
    (const void *) &InterlockedExchange,
    (const void *) &InterlockedIncrement,
    (const void *) &InterlockedDecrement,
    (const void *) &InterlockedExchangeAdd,
    (const void *) &InterlockedCompareExchange,
    (const void *) &InterlockedTestExchange,
    (const void *) &InterlockedExchangePointer,
    (const void *) &InterlockedCompareExchangePointer,
    (const void *) &GetLocalTime,
    (const void *) &GetSystemTime,
    (const void *) &SetLocalTime,
    (const void *) &SetSystemTime,
    (const void *) &FileTimeToLocalFileTime,
    (const void *) &LocalFileTimeToFileTime,
    (const void *) &FileTimeToSystemTime,
    (const void *) &SystemTimeToFileTime,
    /* M10: memory management (heaps/local/status/probes). */
    (const void *) &GetProcessHeap,
    (const void *) &HeapCreate,
    (const void *) &HeapDestroy,
    (const void *) &HeapAlloc,
    (const void *) &HeapFree,
    (const void *) &HeapReAlloc,
    (const void *) &HeapSize,
    (const void *) &HeapValidate,
    (const void *) &HeapCompact,
    (const void *) &LocalReAlloc,
    (const void *) &LocalSize,
    (const void *) &GlobalMemoryStatus,
    (const void *) &IsBadCodePtr,
    (const void *) &IsBadReadPtr,
    (const void *) &IsBadWritePtr,
    /* M10: ticks/file times/time helpers. */
    (const void *) &GetTickCount,
    (const void *) &GetFileTime,
    (const void *) &SetFileTime,
    (const void *) &CompareFileTime,
    (const void *) &GetCurrentFT,
    (const void *) &GetIdleTime,
    (const void *) &Random,
    (const void *) &SetDaylightTime,
    (const void *) &QueryPerformanceCounter,
    (const void *) &QueryPerformanceFrequency,
    /* M11: system information. */
    (const void *) &GetSystemInfo,
    (const void *) &GetVersionEx,
    (const void *) &SignalStarted,
    /* M12: virtual memory / time zone / times. */
    (const void *) &VirtualAlloc,
    (const void *) &VirtualFree,
    (const void *) &VirtualProtect,
    (const void *) &VirtualQuery,
    (const void *) &FlushInstructionCache,
    (const void *) &GetProcessVersion,
    (const void *) &GetDllVersion,
    (const void *) &GetThreadTimes,
    (const void *) &GetTimeZoneInformation,
    (const void *) &SetTimeZoneInformation,
    /* M13: code-page / NLS (winnls.h). */
    (const void *) &MultiByteToWideChar,
    (const void *) &WideCharToMultiByte,
    (const void *) &IsDBCSLeadByte,
    (const void *) &IsDBCSLeadByteEx,
    /* M14: fibers (CE .NET 4.0+). */
    (const void *) &CreateFiber,
    (const void *) &ConvertThreadToFiber,
    (const void *) &DeleteFiber,
    (const void *) &GetCurrentFiber,
    (const void *) &GetFiberData,
    (const void *) &SwitchToFiber,
    /* M16: NLS locale/code-page (winnls.h). */
    (const void *) &GetACP,
    (const void *) &GetOEMCP,
    (const void *) &GetSystemDefaultLCID,
    (const void *) &GetUserDefaultLCID,
    (const void *) &GetSystemDefaultLangID,
    (const void *) &GetUserDefaultLangID,
    (const void *) &IsValidCodePage,
    (const void *) &IsValidLocale,
    (const void *) &CompareStringW, (const void *) &CompareString,
    (const void *) &ConvertDefaultLocale,
    (const void *) &GetCPInfo,
    (const void *) &GetStringTypeW,
    (const void *) &GetStringTypeExW, (const void *) &GetStringTypeEx,
    /* M21: store info + Ce* file helpers (winbase.h). */
    (const void *) &GetStoreInformation,
    (const void *) &CeGenRandom,
    (const void *) &CeGetCanonicalPathName,
    (const void *) &CeGetFileNotificationInfo,
    /* M20/M20b: file mapping + DLL entry helpers (winbase.h/psapi.h). */
    (const void *) &CreateFileForMappingW, (const void *) &CreateFileForMapping,
    (const void *) &CreateFileMappingW, (const void *) &CreateFileMapping,
    (const void *) &MapViewOfFile,
    (const void *) &UnmapViewOfFile,
    (const void *) &FlushViewOfFile,
    (const void *) &DisableThreadLibraryCalls,
    (const void *) &GetModuleInformation,
    /* M19: strings (winbase.h; Coreloc.lib except CharNext Coredll). */
    (const void *) &CharLowerW, (const void *) &CharLower,
    (const void *) &CharLowerBuffW, (const void *) &CharLowerBuff,
    (const void *) &CharUpperW, (const void *) &CharUpper,
    (const void *) &CharUpperBuffW, (const void *) &CharUpperBuff,
    (const void *) &CharNextW, (const void *) &CharNext,
    (const void *) &CharPrevW, (const void *) &CharPrev,
    (const void *) &IsCharAlphaW, (const void *) &IsCharAlpha,
    (const void *) &IsCharAlphaNumericW, (const void *) &IsCharAlphaNumeric,
    (const void *) &IsCharLowerW, (const void *) &IsCharLower,
    (const void *) &IsCharUpperW, (const void *) &IsCharUpper,
    (const void *) &LoadStringW, (const void *) &LoadString,
    (const void *) &wsprintfW, (const void *) &wsprintf,
    (const void *) &wvsprintfW, (const void *) &wvsprintf,
    /* M18: Toolhelp32 (tlhelp32.h; Toolhelp.lib). */
    (const void *) &CreateToolhelp32Snapshot,
    (const void *) &CloseToolhelp32Snapshot,
    (const void *) &Process32First,
    (const void *) &Process32Next,
    (const void *) &Thread32First,
    (const void *) &Thread32Next,
    (const void *) &Module32First,
    (const void *) &Module32Next,
    (const void *) &Heap32ListFirst,
    (const void *) &Heap32ListNext,
    (const void *) &Heap32First,
    (const void *) &Heap32Next,
    (const void *) &Toolhelp32ReadProcessMemory,
    /* M17: file I/O continuation (winbase.h). */
    (const void *) &FindFirstChangeNotification,
    (const void *) &FindNextChangeNotification,
    (const void *) &FindCloseChangeNotification,
    (const void *) &FindFirstFileEx,
    (const void *) &GetFileAttributesEx,
    (const void *) &GetDiskFreeSpaceEx,
    (const void *) &GetFileInformationByHandle,
    (const void *) &GetTempPath,
    (const void *) &GetTempFileName,
    (const void *) &LockFileEx,
    (const void *) &UnlockFileEx,
    (const void *) &DeleteAndRenameFile,
    (const void *) &GetFileVersionInfoSize,
    (const void *) &GetFileVersionInfo,
    /* M15: registry (winreg.h). */
    (const void *) &RegOpenKeyExW, (const void *) &RegOpenKeyEx,
    (const void *) &RegCreateKeyExW, (const void *) &RegCreateKeyEx,
    (const void *) &RegDeleteKeyW, (const void *) &RegDeleteKey,
    (const void *) &RegDeleteValueW, (const void *) &RegDeleteValue,
    (const void *) &RegEnumKeyExW, (const void *) &RegEnumKeyEx,
    (const void *) &RegEnumValueW, (const void *) &RegEnumValue,
    (const void *) &RegQueryInfoKeyW, (const void *) &RegQueryInfoKey,
    (const void *) &RegQueryValueExW, (const void *) &RegQueryValueEx,
    (const void *) &RegSetValueExW, (const void *) &RegSetValueEx,
    (const void *) &RegFlushKeyW, (const void *) &RegFlushKey,
    (const void *) &CeFindFirstRegChange,
    (const void *) &CeFindNextRegChange,
    (const void *) &CeFindCloseRegChange,
    /* M27: GDI bulk (wingdi.h/winuser.h/winbase.h): 129 GDI
     * Functions declared as exports + 3 GDI color macros
     * (GetRValue/GetGValue/GetBValue) that the official
     * pages define as macros (no Link Library row). */
    (const void *) &AlphaBlend,
    (const void *) &BeginPaint,
    (const void *) &BitBlt,
    (const void *) &ChangeDisplaySettingsEx,
    (const void *) &ClientToScreen,
    (const void *) &CombineRgn,
    (const void *) &CopyRect,
    (const void *) &CreateBitmap,
    (const void *) &CreateCompatibleBitmap,
    (const void *) &CreateCompatibleDC,
    (const void *) &CreateDC,
    (const void *) &CreateDIBPatternBrushPt,
    (const void *) &CreateDIBSection,
    (const void *) &CreatePalette,
    (const void *) &CreatePatternBrush,
    (const void *) &CreatePen,
    (const void *) &CreatePenIndirect,
    (const void *) &CreateRectRgn,
    (const void *) &CreateRectRgnIndirect,
    (const void *) &CreateSolidBrush,
    (const void *) &DeleteDC,
    (const void *) &DeleteObject,
    (const void *) &DrawEdge,
    (const void *) &DrawFocusRect,
    (const void *) &DrawFrameControl,
    (const void *) &Ellipse,
    (const void *) &EndPaint,
    (const void *) &EnumDisplayDevices,
    (const void *) &EnumDisplaySettings,
    (const void *) &EqualRect,
    (const void *) &EqualRgn,
    (const void *) &ExcludeClipRect,
    (const void *) &ExtCreateRegion,
    (const void *) &ExtEscape,
    (const void *) &FillRect,
    (const void *) &FillRgn,
    (const void *) &GetBkColor,
    (const void *) &GetBkMode,
    (const void *) &GetClipBox,
    (const void *) &GetClipRgn,
    (const void *) &GetCurrentObject,
    (const void *) &GetCurrentPositionEx,
    (const void *) &GetDC,
    (const void *) &GetDCEx,
    (const void *) &GetDeviceCaps,
    (const void *) &GetDIBColorTable,
    (const void *) &GetLayout,
    (const void *) &GetNearestColor,
    (const void *) &GetNearestPaletteIndex,
    (const void *) &GetObject,
    (const void *) &GetObjectType,
    (const void *) &GetOutlineTextMetrics,
    (const void *) &GetPaletteEntries,
    (const void *) &GetPixel,
    (const void *) &GetRegionData,
    (const void *) &GetRgnBox,
    (const void *) &GetROP2,
    (const void *) &GetStockObject,
    (const void *) &GetStretchBltMode,
    (const void *) &GetSysColorBrush,
    (const void *) &GetSystemPaletteEntries,
    (const void *) &GetUpdateRect,
    (const void *) &GetUpdateRgn,
    (const void *) &GetViewportExtEx,
    (const void *) &GetViewportOrgEx,
    (const void *) &GetWindowDC,
    (const void *) &GetWindowExtEx,
    (const void *) &GetWindowOrgEx,
    (const void *) &GetWindowRgn,
    (const void *) &GradientFill,
    (const void *) &InflateRect,
    (const void *) &IntersectClipRect,
    (const void *) &IntersectRect,
    (const void *) &InvalidateRect,
    (const void *) &InvalidateRgn,
    (const void *) &InvertRect,
    (const void *) &IsRectEmpty,
    (const void *) &LineTo,
    (const void *) &LoadBitmap,
    (const void *) &MapWindowPoints,
    (const void *) &MaskBlt,
    (const void *) &MoveToEx,
    (const void *) &OffsetRect,
    (const void *) &OffsetRgn,
    (const void *) &OffsetViewportOrgEx,
    (const void *) &PatBlt,
    (const void *) &Polygon,
    (const void *) &Polyline,
    (const void *) &PtInRect,
    (const void *) &PtInRegion,
    (const void *) &RealizePalette,
    (const void *) &Rectangle,
    (const void *) &RectInRegion,
    (const void *) &RectVisible,
    (const void *) &RedrawWindow,
    (const void *) &ReleaseDC,
    (const void *) &RestoreDC,
    (const void *) &RoundRect,
    (const void *) &SaveDC,
    (const void *) &ScreenToClient,
    (const void *) &SelectClipRgn,
    (const void *) &SelectObject,
    (const void *) &SelectPalette,
    (const void *) &SetBitmapBits,
    (const void *) &SetBkColor,
    (const void *) &SetBkMode,
    (const void *) &SetBrushOrgEx,
    (const void *) &SetDIBColorTable,
    (const void *) &SetDIBitsToDevice,
    (const void *) &SetLayout,
    (const void *) &SetPaletteEntries,
    (const void *) &SetPixel,
    (const void *) &SetRect,
    (const void *) &SetRectEmpty,
    (const void *) &SetRectRgn,
    (const void *) &SetROP2,
    (const void *) &SetStretchBltMode,
    (const void *) &SetViewportOrgEx,
    (const void *) &SetWindowOrgEx,
    (const void *) &SetWindowRgn,
    (const void *) &StretchBlt,
    (const void *) &StretchDIBits,
    (const void *) &SubtractRect,
    (const void *) &TransparentBlt,
    (const void *) &TransparentImage,
    (const void *) &UnionRect,
    (const void *) &UpdateWindow,
    (const void *) &ValidateRect,
    (const void *) &ValidateRgn,
    /* M28: window-control function layer (dialog/menu/clipboard/button
     * + resource/icon + printing + system-info + notification).  Base
     * names below expand through their generic-text macros where the
     * CE pages are Unicode-only (see the headers). */
    (const void *) &AppendMenu, (const void *) &CheckMenuItem,
    (const void *) &CheckMenuRadioItem, (const void *) &CreateMenu,
    (const void *) &CreatePopupMenu, (const void *) &DeleteMenu,
    (const void *) &DestroyMenu, (const void *) &DrawMenuBar,
    (const void *) &EnableMenuItem, (const void *) &GetMenuItemInfo,
    (const void *) &GetSubMenu, (const void *) &GetSystemMenu,
    (const void *) &InsertMenu, (const void *) &LoadMenu,
    (const void *) &RemoveMenu, (const void *) &SetMenuItemInfo,
    (const void *) &TrackPopupMenu, (const void *) &TrackPopupMenuEx,
    (const void *) &CreateDialog, (const void *) &CreateDialogIndirect,
    (const void *) &CreateDialogIndirectParam, (const void *) &CreateDialogParam,
    (const void *) &DefDlgProc, (const void *) &DialogBox,
    (const void *) &DialogBoxIndirect, (const void *) &DialogBoxIndirectParam,
    (const void *) &DialogBoxParam, (const void *) &EndDialog,
    (const void *) &GetDialogBaseUnits, (const void *) &GetDlgCtrlID,
    (const void *) &GetDlgItem, (const void *) &GetDlgItemInt,
    (const void *) &GetDlgItemText, (const void *) &GetNextDlgGroupItem,
    (const void *) &GetNextDlgTabItem, (const void *) &IsDialogMessage,
    (const void *) &MapDialogRect, (const void *) &SendDlgItemMessage,
    (const void *) &SetDlgItemInt, (const void *) &SetDlgItemText,
    (const void *) &MessageBox, (const void *) &MessageBeep,
    (const void *) &CheckDlgButton, (const void *) &IsDlgButtonChecked,
    (const void *) &CheckRadioButton,
    (const void *) &CloseClipboard, (const void *) &CountClipboardFormats,
    (const void *) &EmptyClipboard, (const void *) &EnumClipboardFormats,
    (const void *) &GetClipboardData, (const void *) &GetClipboardDataAlloc,
    (const void *) &GetClipboardFormatName, (const void *) &GetClipboardOwner,
    (const void *) &GetOpenClipboardWindow,
    (const void *) &GetPriorityClipboardFormat,
    (const void *) &IsClipboardFormatAvailable, (const void *) &OpenClipboard,
    (const void *) &RegisterClipboardFormat, (const void *) &SetClipboardData,
    (const void *) &CreateIconIndirect, (const void *) &DestroyIcon,
    (const void *) &DrawIconEx, (const void *) &GetIconInfo,
    (const void *) &LoadIcon, (const void *) &LoadImage,
    (const void *) &FindResource, (const void *) &LoadResource,
    (const void *) &LockResource, (const void *) &SizeofResource,
    (const void *) &ExtractIconEx,
    (const void *) &AbortDoc, (const void *) &EndDoc, (const void *) &EndPage,
    (const void *) &SetAbortProc, (const void *) &StartDoc,
    (const void *) &StartPage,
    (const void *) &EnableHardwareKeyboard, (const void *) &GetSysColor,
    (const void *) &GetSystemMetrics, (const void *) &SystemParametersInfo,
    (const void *) &SetSysColors, (const void *) &GetSystemPowerStatusEx,
    (const void *) &GetSystemPowerStatusEx2,
    (const void *) &CeClearUserNotification,
    (const void *) &CeGetUserNotification,
    (const void *) &CeGetUserNotificationHandles,
    (const void *) &CeGetUserNotificationPreferences,
    (const void *) &CeHandleAppNotifications,
    (const void *) &CeRunAppAtEvent, (const void *) &CeRunAppAtTime,
    (const void *) &CeSetUserNotification, (const void *) &CeSetUserNotificationEx,
    /* M29: Image List API (commctrl.h; Header Commctrl.h rows). */
    (const void *) &ImageList_Add, (const void *) &ImageList_AddMasked,
    (const void *) &ImageList_BeginDrag, (const void *) &ImageList_Copy,
    (const void *) &ImageList_Create, (const void *) &ImageList_Destroy,
    (const void *) &ImageList_DragEnter, (const void *) &ImageList_DragLeave,
    (const void *) &ImageList_DragMove,
    (const void *) &ImageList_DragShowNolock, (const void *) &ImageList_Draw,
    (const void *) &ImageList_DrawEx, (const void *) &ImageList_DrawIndirect,
    (const void *) &ImageList_Duplicate, (const void *) &ImageList_EndDrag,
    (const void *) &ImageList_GetBkColor, (const void *) &ImageList_GetDragImage,
    (const void *) &ImageList_GetIcon, (const void *) &ImageList_GetIconSize,
    (const void *) &ImageList_GetImageCount,
    (const void *) &ImageList_GetImageInfo, (const void *) &ImageList_LoadImage,
    (const void *) &ImageList_Merge, (const void *) &ImageList_Remove,
    (const void *) &ImageList_RemoveAll, (const void *) &ImageList_Replace,
    (const void *) &ImageList_ReplaceIcon, (const void *) &ImageList_SetBkColor,
    (const void *) &ImageList_SetDragCursorImage,
    (const void *) &ImageList_SetIconSize, (const void *) &ImageList_SetImageCount,
    (const void *) &ImageList_SetOverlayImage,
};

/* File structures: layout checks (winbase.h).  CE 32-bit: each
 * FILETIME = 8 bytes; WIN32_FIND_DATAW has no alternate-name member
 * on CE (dwOID instead), so offsetof(cFileName) must be 4+3*8+4+4+4
 * = 40 and the total size 40+260*2 = 560. */
typedef char assert_filetime_size[sizeof(FILETIME) == 8 ? 1 : -1];
typedef char assert_finddata_offsets[
    (offsetof(WIN32_FIND_DATAW, ftCreationTime) == 4 &&
     offsetof(WIN32_FIND_DATAW, ftLastWriteTime) == 20 &&
     offsetof(WIN32_FIND_DATAW, nFileSizeHigh) == 28 &&
     offsetof(WIN32_FIND_DATAW, dwOID) == 36 &&
     offsetof(WIN32_FIND_DATAW, cFileName) == 40 &&
     sizeof(WIN32_FIND_DATAW) == 560) ? 1 : -1];

/* File constants exercised (winbase.h + winerror.h). */
typedef char assert_file_vals[
    (MAX_PATH == 260 &&
     FILE_ATTRIBUTE_READONLY == 1u &&
     FILE_ATTRIBUTE_DIRECTORY == 0x10u &&
     FILE_ATTRIBUTE_ENCRYPTED == 0x4000u &&
     GENERIC_READ == 0x80000000u &&
     GENERIC_WRITE == 0x40000000u &&
     FILE_SHARE_READ == 1u &&
     CREATE_NEW == 1u && CREATE_ALWAYS == 2u &&
     OPEN_EXISTING == 3u && OPEN_ALWAYS == 4u &&
     TRUNCATE_EXISTING == 5u &&
     FILE_FLAG_WRITE_THROUGH == 0x80000000u &&
     ERROR_NO_MORE_FILES == 18L) ? 1 : -1];

/* File-pointer constants (winbase.h, ms891933 + Win32 ABI values). */
typedef char assert_fileptr_vals[
    (FILE_BEGIN == 0u && FILE_CURRENT == 1u && FILE_END == 2u &&
     INVALID_SET_FILE_POINTER == (DWORD)0xFFFFFFFFu) ? 1 : -1];

/* Synchronization constants (winbase.h; names per CE pages
 * ms885177/aa450988/aa450987/ms885208; numeric values are the fixed
 * Win32 ABI values). */
typedef char assert_sync_vals[
    (WAIT_OBJECT_0 == 0u && WAIT_ABANDONED_0 == 0x80u &&
     WAIT_TIMEOUT == 0x102u && WAIT_FAILED == (DWORD)0xFFFFFFFFu &&
     MAXIMUM_WAIT_OBJECTS == 64 &&
     DUPLICATE_CLOSE_SOURCE == 1u && DUPLICATE_SAME_ACCESS == 2u &&
     EVENT_ALL_ACCESS == 0x1F0003u) ? 1 : -1];

/* 64-bit integer forms and their unions (winnt.h). */
typedef char assert_large_int_size[sizeof(LARGE_INTEGER) == 8 ? 1 : -1];
typedef char assert_ll_size[sizeof(LONGLONG) == 8 ? 1 : -1];

#if __SIZEOF_POINTER__ == 4
/* CRITICAL_SECTION layout on 32-bit (desktop-official member order
 * recorded in winnt.h): the six fields occupy 24 bytes. */
typedef char assert_cs_layout[
    (offsetof(CRITICAL_SECTION, DebugInfo) == 0 &&
     offsetof(CRITICAL_SECTION, LockCount) == 4 &&
     offsetof(CRITICAL_SECTION, RecursionCount) == 8 &&
     offsetof(CRITICAL_SECTION, OwningThread) == 12 &&
     offsetof(CRITICAL_SECTION, LockSemaphore) == 16 &&
     offsetof(CRITICAL_SECTION, SpinCount) == 20 &&
     sizeof(CRITICAL_SECTION) == 24) ? 1 : -1];
typedef char assert_li_layout[
    (offsetof(LARGE_INTEGER, QuadPart) == 0) ? 1 : -1];
#endif
typedef char assert_tls_vals[
    (TLS_MINIMUM_AVAILABLE == 64 &&
     TLS_OUT_OF_INDEXES == (DWORD)0xFFFFFFFFu) ? 1 : -1];

/* LoadLibraryEx flags (winbase.h, values per official Win32 ABI). */
typedef char assert_loadlib_flags[
    (DONT_RESOLVE_DLL_REFERENCES == 1u &&
     LOAD_LIBRARY_AS_DATAFILE == 2u &&
     LOAD_WITH_ALTERED_SEARCH_PATH == 8u) ? 1 : -1];

/* CE thread-priority constants (winbase.h): legacy 8-level scale
 * with NORMAL = 3 (old level n maps to new level 248+n, so NORMAL's
 * new-scale value is 251 per ms885643/aa450891). */
typedef char assert_priority_vals[
    (THREAD_PRIORITY_TIME_CRITICAL == 0 &&
     THREAD_PRIORITY_NORMAL == 3 &&
     THREAD_PRIORITY_IDLE == 7 &&
     THREAD_PRIORITY_ERROR_RETURN == (int)0x7FFFFFFF &&
     INFINITE == 0xFFFFFFFFu) ? 1 : -1];

/* Error constants exercised (values from winerror.h, per the official
 * CE numeric table aa450919 rows 0-1078; spot checks cover each
 * numeric group edge plus the independently cited constants). */
typedef char assert_winerror_vals[
    (ERROR_SUCCESS == 0 && NO_ERROR == 0 &&
     ERROR_TOO_MANY_OPEN_FILES == 4 && ERROR_ACCESS_DENIED == 5 &&
     ERROR_OUTOFMEMORY == 14 && ERROR_NO_MORE_FILES == 18 &&
     ERROR_HANDLE_DISK_FULL == 39 && ERROR_NOT_SUPPORTED == 50 &&
     ERROR_NETNAME_DELETED == 64 && ERROR_FILE_EXISTS == 80 &&
     ERROR_INVALID_PARAMETER == 87 && ERROR_TOO_MANY_SEMAPHORES == 100 &&
     ERROR_BROKEN_PIPE == 109 && ERROR_BUFFER_OVERFLOW == 111 &&
     ERROR_DISK_FULL == 112 && ERROR_CALL_NOT_IMPLEMENTED == 120 &&
     ERROR_INSUFFICIENT_BUFFER == 122 && ERROR_INVALID_NAME == 123 &&
     ERROR_MOD_NOT_FOUND == 126 && ERROR_PROC_NOT_FOUND == 127 &&
     ERROR_DIR_NOT_EMPTY == 145 && ERROR_SIGNAL_PENDING == 162 &&
     ERROR_BUSY == 170 && ERROR_ALREADY_EXISTS == 183 &&
     ERROR_BAD_EXE_FORMAT == 193 && ERROR_EXE_MACHINE_TYPE_MISMATCH == 216 &&
     ERROR_BAD_PIPE == 230 && ERROR_PIPE_BUSY == 231 &&
     ERROR_NO_DATA == 232 && ERROR_MORE_DATA == 234 &&
     ERROR_NO_MORE_ITEMS == 259 && STILL_ACTIVE == 259 &&
     ERROR_DIRECTORY == 267 && ERROR_NOT_OWNER == 288 &&
     ERROR_PARTIAL_COPY == 299 && ERROR_PIPE_LISTENING == 536 &&
     ERROR_IO_PENDING == 997 && ERROR_NOACCESS == 998 &&
     ERROR_STACK_OVERFLOW == 1001 && ERROR_UNRECOGNIZED_VOLUME == 1005 &&
     ERROR_BADDB == 1009 && ERROR_KEY_DELETED == 1018 &&
     ERROR_DUPLICATE_SERVICE_NAME == 1078 &&
     ERROR_NO_UNICODE_TRANSLATION == 1113) ? 1 : -1];

/* Time structures (winbase.h): SYSTEMTIME is eight WORDs in the
 * documented order (aa450923), so sizeof must be 16. */
typedef char assert_systemtime_size[sizeof(SYSTEMTIME) == 16 ? 1 : -1];
typedef char assert_systemtime_offsets[
    (offsetof(SYSTEMTIME, wYear) == 0 &&
     offsetof(SYSTEMTIME, wMonth) == 2 &&
     offsetof(SYSTEMTIME, wDayOfWeek) == 4 &&
     offsetof(SYSTEMTIME, wDay) == 6 &&
     offsetof(SYSTEMTIME, wHour) == 8 &&
     offsetof(SYSTEMTIME, wMinute) == 10 &&
     offsetof(SYSTEMTIME, wSecond) == 12 &&
     offsetof(SYSTEMTIME, wMilliseconds) == 14) ? 1 : -1];

/* M10 memory constants (winbase.h): heap flags (numeric values are
 * the fixed Win32 ABI values) and the local-allocation flags. */
typedef char assert_heap_vals[
    (HEAP_NO_SERIALIZE == 0x1u && HEAP_ZERO_MEMORY == 0x8u &&
     MAXDWORD == (DWORD)0xFFFFFFFFu) ? 1 : -1];

/* M10 MEMORYSTATUS layout (winbase.h, ms886753): eight DWORDs,
 * dwAvailVirtual last (no desktop-only dwAvailExtendedVirtual). */
typedef char assert_memstatus_layout[
    (offsetof(MEMORYSTATUS, dwLength) == 0 &&
     offsetof(MEMORYSTATUS, dwMemoryLoad) == 4 &&
     offsetof(MEMORYSTATUS, dwAvailVirtual) == 28 &&
     sizeof(MEMORYSTATUS) == 32) ? 1 : -1];

/* M11 system-information layout (winbase.h, from the CE pages):
 * SYSTEM_INFO is 36 bytes on 32-bit CE (union + 7 DWORDs + 2 WORDs)
 * with the anonymous dwOemId union first; OSVERSIONINFO is
 * 5 DWORDs + 128 TCHARs = 276 bytes. */
#if __SIZEOF_POINTER__ == 4
/* SYSTEM_INFO layout is pointer-dependent; checked only on 32-bit
 * hosts and, precisely, by the CE toolchain matrix (32-bit model). */
typedef char assert_sysinfo_layout[
    (offsetof(SYSTEM_INFO, dwPageSize) == 4 &&
     offsetof(SYSTEM_INFO, lpMinimumApplicationAddress) == 8 &&
     offsetof(SYSTEM_INFO, dwAllocationGranularity) == 28 &&
     offsetof(SYSTEM_INFO, wProcessorLevel) == 32 &&
     offsetof(SYSTEM_INFO, wProcessorRevision) == 34 &&
     sizeof(SYSTEM_INFO) == 36) ? 1 : -1];
#endif
typedef char assert_osversioninfo_layout[
    (offsetof(OSVERSIONINFO, dwPlatformId) == 16 &&
     offsetof(OSVERSIONINFO, szCSDVersion) == 20 &&
     sizeof(OSVERSIONINFO) == 276) ? 1 : -1];
typedef char assert_sysinfo_vals[
    (PROCESSOR_ARCHITECTURE_INTEL == 0 &&
     PROCESSOR_ARCHITECTURE_ARM == 5 &&
     PROCESSOR_ARCHITECTURE_UNKNOWN == 0xFFFF &&
     VER_PLATFORM_WIN32s == 0 &&
     VER_PLATFORM_WIN32_WINDOWS == 1 &&
     VER_PLATFORM_WIN32_NT == 2 &&
     VER_PLATFORM_WIN32_CE == 3) ? 1 : -1];

/* M12 memory/time-zone constants (winbase.h/winnt.h; values per the
 * fixed Win32 ABI). */
typedef char assert_m12_vals[
    (MEM_COMMIT == 0x1000u && MEM_RESERVE == 0x2000u &&
     MEM_DECOMMIT == 0x4000u && MEM_RELEASE == 0x8000u &&
     MEM_FREE == 0x10000u && MEM_PRIVATE == 0x20000u &&
     MEM_MAPPED == 0x40000u && MEM_IMAGE == 0x1000000u &&
     PAGE_NOACCESS == 0x1u && PAGE_READONLY == 0x2u &&
     PAGE_READWRITE == 0x4u && PAGE_EXECUTE_READWRITE == 0x40u &&
     PAGE_GUARD == 0x100u && PAGE_NOCACHE == 0x200u &&
     TIME_ZONE_ID_UNKNOWN == 0 && TIME_ZONE_ID_STANDARD == 1 &&
     TIME_ZONE_ID_DAYLIGHT == 2) ? 1 : -1];
#if __SIZEOF_POINTER__ == 4
typedef char assert_mbi_layout[
    (offsetof(MEMORY_BASIC_INFORMATION, AllocationBase) == 4 &&
     offsetof(MEMORY_BASIC_INFORMATION, RegionSize) == 12 &&
     offsetof(MEMORY_BASIC_INFORMATION, State) == 16 &&
     offsetof(MEMORY_BASIC_INFORMATION, Type) == 24 &&
     sizeof(MEMORY_BASIC_INFORMATION) == 28) ? 1 : -1];
#endif
typedef char assert_tzi_layout[
    (offsetof(TIME_ZONE_INFORMATION, StandardName) == 4 &&
     offsetof(TIME_ZONE_INFORMATION, StandardBias) == 84 &&
     offsetof(TIME_ZONE_INFORMATION, DaylightName) == 88 &&
     offsetof(TIME_ZONE_INFORMATION, DaylightBias) == 168 &&
     sizeof(TIME_ZONE_INFORMATION) == 172) ? 1 : -1];

static const unsigned api_flags[] = {
    LMEM_FIXED, LMEM_ZEROINIT, LPTR,
    HEAP_NO_SERIALIZE, HEAP_ZERO_MEMORY,
};

/* Generic-text forms are the wide ones on CE. */
typedef char assert_tchar_wide[(sizeof(TCHAR) == sizeof(WCHAR)) ? 1 : -1];
typedef char assert_lpctstr_wide[(sizeof(LPCTSTR) == sizeof(LPCWSTR)) ? 1 : -1];

/* PROCESS_INFORMATION field order (official structure page ms886775
 * is pending full transcription; layout below is the standard
 * hProcess/hThread/dwProcessId/dwThreadId order). */
typedef char assert_pi_first[(offsetof(PROCESS_INFORMATION, hProcess) == 0) ? 1 : -1];

/* CE-shaped usage snippets (compile-only): process creation passes
 * NULL/FALSE for every unsupported parameter, per ms885182; the
 * thread entry type is exercised through CreateThread's signature. */
static DWORD worker(LPVOID p)
{
    return p != 0;
}

/* Wide-string literals are 32-bit wchar_t on the host but 16-bit on
 * the CE target; build explicit WCHAR strings so the TU is
 * host-independent. */
static const WCHAR w_app[] = { 'a', 'p', 'p', '.', 'e', 'x', 'e', 0 };
static const WCHAR w_cmd[] = {
    'a', 'p', 'p', '.', 'e', 'x', 'e', ' ', 'a', 'r', 'g', 0
};
static const WCHAR w_file[] = {
    't', 'm', 'p', '\\', 'f', '.', 't', 'x', 't', 0
};
static const WCHAR w_copy[] = {
    't', 'm', 'p', '\\', 'f', '2', '.', 't', 'x', 't', 0
};
static const WCHAR w_moved[] = {
    't', 'm', 'p', '\\', 'f', '3', '.', 't', 'x', 't', 0
};
static const WCHAR w_dir[] = {
    't', 'm', 'p', '\\', 'd', 'i', 'r', 0
};

static int ce_shaped_usage(void)
{
    PROCESS_INFORMATION pi;
    SYSTEMTIME st;
    FILETIME ft1, ft2;
    HANDLE h, hf;
    DWORD tid, cb, nread, nwrote, sizehi;
    BOOL ok;
    char io_buf[8] = "abcdefg";

    if (!CreateProcessW(w_app, w_cmd, NULL, NULL,
                        FALSE, 0, NULL, NULL, NULL, &pi))
        return (int) GetLastError();
    h = CreateThread(NULL, 0, worker, NULL, 0, &tid);
    if (h == NULL)
        return (int) GetLastError();

    /* Time round trip (compile + exercise): the conversions must
     * succeed for the current clock value on any host. */
    GetLocalTime(&st);
    if (!SystemTimeToFileTime(&st, &ft1))
        return (int) GetLastError();
    if (!FileTimeToLocalFileTime(&ft1, &ft2))
        return (int) GetLastError();
    if (!LocalFileTimeToFileTime(&ft2, &ft1))
        return (int) GetLastError();
    if (!FileTimeToSystemTime(&ft1, &st))
        return (int) GetLastError();
    GetSystemTime(&st);

    /* Synchronous file I/O and file/directory management: exercises
     * the argument types of every declaration of the file batch
     * (ReadFile ms891445, WriteFile ms892380, GetFileSize ms890939,
     * SetFilePointer ms891933, SetEndOfFile ms891916,
     * FlushFileBuffers ms890238, MoveFileW ms891388, CopyFileW
     * aa517309, CreateDirectoryW aa517316, RemoveDirectoryW
     * ms891470, SetFileAttributesW ms891925).  Compile-only: the
     * checks never link or run these calls. */
    hf = CreateFileW(w_file, GENERIC_READ | GENERIC_WRITE,
                     FILE_SHARE_READ, NULL, CREATE_ALWAYS,
                     FILE_ATTRIBUTE_NORMAL, NULL);
    if (hf == INVALID_HANDLE_VALUE)
        return (int) GetLastError();
    ok = WriteFile(hf, io_buf, (DWORD) sizeof(io_buf), &nwrote,
                   NULL) != 0;
    ok = FlushFileBuffers(hf) && ok;
    ok = (SetFilePointer(hf, 0, NULL, FILE_BEGIN)
          != INVALID_SET_FILE_POINTER) && ok;
    cb = GetFileSize(hf, &sizehi);
    ok = (cb != INVALID_SET_FILE_POINTER) && ok;
    ok = SetEndOfFile(hf) && ok;
    ok = ReadFile(hf, io_buf, (DWORD) sizeof(io_buf), &nread,
                  NULL) && ok;
    ok = CloseHandle(hf) && ok;
    ok = CreateDirectoryW(w_dir, NULL) && ok;
    ok = SetFileAttributesW(w_file, FILE_ATTRIBUTE_NORMAL) && ok;
    ok = CopyFileW(w_file, w_copy, FALSE) && ok;
    ok = MoveFileW(w_copy, w_moved) && ok;
    ok = DeleteFileW(w_moved) && ok;
    ok = RemoveDirectoryW(w_dir) && ok;
    if (!ok)
        return (int) GetLastError();
    return (int) (pi.dwProcessId + tid + st.wSecond + cb + nread
                  + nwrote + sizehi);
}

/* Synchronization usage shapes (compile-only; never run): events,
 * mutexes, semaphores, wait functions, critical sections and the
 * interlocked calls, with the CE parameter rules applied (attributes
 * NULL, OpenEvent's EVENT_ALL_ACCESS and bInheritHandle FALSE,
 * DuplicateHandle with bInheritHandle FALSE).  The process handle
 * that DuplicateHandle needs is supplied by a helper that is never
 * executed (the CE kernel-scope GetCurrentProcess is not part of
 * this user-mode header set). */
static HANDLE shape_current_process(void)
{
    return (HANDLE) 0;
}

static DWORD sync_worker(LPVOID p)
{
    LONG x = 0;
    (void) p;
    InterlockedIncrement(&x);
    InterlockedExchangeAdd(&x, 1);
    InterlockedCompareExchange(&x, 0, 1);
    InterlockedTestExchange(&x, 1, 0);
    return (DWORD) x;
}

static int sync_shaped_usage(void)
{
    HANDLE hev, hmut, hsem, hdup;
    CRITICAL_SECTION cs;
    LONG prev;
    DWORD rc;
    LPVOID p = 0;

    InitializeCriticalSection(&cs);
    EnterCriticalSection(&cs);
    if (!TryEnterCriticalSection(&cs))
        return (int) GetLastError();
    LeaveCriticalSection(&cs);
    DeleteCriticalSection(&cs);

    hev = CreateEventW(NULL, FALSE, FALSE, NULL);
    hmut = CreateMutexW(NULL, FALSE, NULL);
    hsem = CreateSemaphoreW(NULL, 0, 1, NULL);
    if (hev == NULL || hmut == NULL || hsem == NULL)
        return (int) GetLastError();
    SetEvent(hev);
    ResetEvent(hev);
    PulseEvent(hev);
    ReleaseMutex(hmut);
    ReleaseSemaphore(hsem, 1, &prev);
    rc = WaitForSingleObject(hev, INFINITE);
    if (rc != WAIT_OBJECT_0)
        return (int) rc;
    rc = WaitForMultipleObjects(1, (const HANDLE[]) { hev }, FALSE,
                                INFINITE);
    hdup = 0;
    if (!DuplicateHandle(shape_current_process(), hev,
                         shape_current_process(), &hdup, 0,
                         FALSE, DUPLICATE_SAME_ACCESS))
        return (int) GetLastError();
    CloseHandle(hdup);
    CloseHandle(hev);
    CloseHandle(hmut);
    CloseHandle(hsem);
    (void) sync_worker(p);
    return 0;
}

/* M10 usage shapes (winbase.h memory + time batch; compile-only for
 * the resource-hungry calls): process heap, private heaps, the local
 * memory completion pair, the memory status/probe functions, ticks,
 * file times, and the performance counter.  Runtime side effects are
 * avoided (no file created: GetFileTime/SetFileTime are only called
 * with INVALID_HANDLE_VALUE and their failure accepted). */
static int m10_shaped_usage(void)
{
    HANDLE hheap, hproc, hf;
    LPVOID blk;
    MEMORYSTATUS ms;
    FILETIME ft, ftc, fta, ftw;
    LARGE_INTEGER qpc, qpf;
    DWORD ticks, idle, rnd, sz;
    BOOL ok = FALSE;
    HLOCAL hloc;

    hproc = GetProcessHeap();
    if (hproc == NULL)
        return (int) GetLastError();
    blk = HeapAlloc(hproc, HEAP_ZERO_MEMORY, 64u);
    if (blk == NULL)
        return (int) GetLastError();
    sz = HeapSize(hproc, 0, blk);
    blk = HeapReAlloc(hproc, HEAP_ZERO_MEMORY, blk, 128u);
    if (blk == NULL)
        return (int) GetLastError();
    ok = (sz >= 64u && HeapSize(hproc, 0, blk) >= sz) && ok;
    ok = HeapFree(hproc, 0, blk) != 0;
    ok = HeapValidate(hproc, 0, NULL) && ok;

    hheap = HeapCreate(0, 0, 0);
    if (hheap == NULL)
        return (int) GetLastError();
    blk = HeapAlloc(hheap, 0, 32u);
    if (blk == NULL)
        return (int) GetLastError();
    ok = HeapSize(hheap, 0, blk) >= 32u && ok;
    ok = HeapFree(hheap, 0, blk) && ok;
    (void) HeapCompact(hheap, 0);
    ok = HeapDestroy(hheap) && ok;

    hloc = LocalReAlloc((HLOCAL) 0, 16u, LMEM_MOVEABLE);
    if (hloc != NULL)
        ok = LocalSize(hloc) != 0 && ok;
    GlobalMemoryStatus(&ms);
    ok = ms.dwLength == sizeof(MEMORYSTATUS) && ok;

    /* Memory-integrity probes (compile shape only). */
    ok = (IsBadCodePtr((FARPROC) 0) != 0) && ok;
    ok = (IsBadReadPtr((const void *) 0, 0u) == 0) && ok;
    ok = (IsBadWritePtr((LPVOID) 0, 0u) == 0) && ok;

    /* Time/tick surface. */
    ticks = GetTickCount();
    idle = GetIdleTime();
    rnd = Random();
    (void) idle; (void) rnd;
    SetDaylightTime(0);
    GetCurrentFT(&ft);
    if (GetFileTime(INVALID_HANDLE_VALUE, &ftc, &fta, &ftw))
        return (int) GetLastError();
    (void) CompareFileTime(&ftc, &ftw);
    hf = CreateFileW(w_file, GENERIC_WRITE, FILE_SHARE_READ, NULL,
                     CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hf != INVALID_HANDLE_VALUE) {
        (void) SetFileTime(hf, NULL, NULL, &ft);
        ok = CloseHandle(hf) && ok;
    }
    ok = (QueryPerformanceCounter(&qpc) != 0) && ok;
    ok = (QueryPerformanceFrequency(&qpf) != 0 && qpf.QuadPart != 0)
         && ok;
    (void) qpc.QuadPart;
    return (ticks == (DWORD) -1) ? (int) ERROR_INVALID_PARAMETER : ok;
}

/* M11 usage shape: system-information report (compile-only; never
 * linked/run). */
static int m11_shaped_usage(void)
{
    SYSTEM_INFO si;
    OSVERSIONINFO ovi;

    GetSystemInfo(&si);
    if (si.dwPageSize == 0)
        return (int) GetLastError();
    ovi.dwOSVersionInfoSize = (DWORD) sizeof(OSVERSIONINFO);
    if (!GetVersionEx(&ovi))
        return (int) GetLastError();
    SignalStarted(0);
    return ovi.dwPlatformId == VER_PLATFORM_WIN32_CE ? 0 : 1;
}

/* M12 usage shape: virtual memory + time zone + process/DLL/thread
 * version & timing helpers (compile-only; never linked/run). */
static int m12_shaped_usage(void)
{
    LPVOID p;
    MEMORY_BASIC_INFORMATION mbi;
    TIME_ZONE_INFORMATION tzi;
    FILETIME ft1, ft2, ft3, ft4;
    DWORD oldp, tzid, cb;

    p = VirtualAlloc(NULL, 4096u, MEM_RESERVE | MEM_COMMIT,
                     PAGE_READWRITE);
    if (p == NULL)
        return (int) GetLastError();
    if (!VirtualProtect(p, 4096u, PAGE_READONLY, &oldp))
        return (int) GetLastError();
    cb = VirtualQuery(p, &mbi, sizeof(mbi));
    if (cb != sizeof(mbi) || mbi.State != MEM_COMMIT)
        return (int) ERROR_INVALID_PARAMETER;
    if (!VirtualFree(p, 0, MEM_RELEASE))
        return (int) GetLastError();
    if (GetProcessVersion(0) == 0)
        return (int) GetLastError();
    if (GetDllVersion((HMODULE) 0) == 0)
        return (int) GetLastError();
    if (!FlushInstructionCache(INVALID_HANDLE_VALUE, p, 0))
        return (int) GetLastError();
    if (!GetThreadTimes(INVALID_HANDLE_VALUE, &ft1, &ft2, &ft3, &ft4))
        return (int) GetLastError();
    tzid = GetTimeZoneInformation(&tzi);
    if (tzid == TIME_ZONE_ID_UNKNOWN && GetLastError() != 0)
        return (int) GetLastError();
    (void) SetTimeZoneInformation(&tzi);
    return 0;
}

/* M16 NLS constants/macros (winnls.h + winnt.h). */
typedef char assert_nls2_vals[
    (CT_CTYPE1 == 1u && CT_CTYPE2 == 2u && CT_CTYPE3 == 4u &&
     LCID_INSTALLED == 1u && LCID_SUPPORTED == 2u &&
     CSTR_LESS_THAN == 1 && CSTR_EQUAL == 2 &&
     CSTR_GREATER_THAN == 3 &&
     MAX_DEFAULTCHAR == 2 && MAX_LEADBYTES == 12 &&
     MAKELANGID(9, 1) == 0x409 &&
     PRIMARYLANGID(0x409) == 9 && SUBLANGID(0x409) == 1 &&
     MAKELCID(0x409, 0) == 0x409) ? 1 : -1];

/* M18 Toolhelp32 layout checks (tlhelp32.h; layouts from the CE page
 * structure dumps).  Non-pointer offsets/sizes hold on every host;
 * pointer-bearing members are checked only for the 32-bit model
 * (precisely verified by the CE toolchain matrix). */
typedef char assert_th_layouts[
    (sizeof(HEAPLIST32) == 16 && sizeof(THREADENTRY32) == 36 &&
     offsetof(THREADENTRY32, th32CurrentProcessID) == 32 &&
     offsetof(PROCESSENTRY32, szExeFile) == 36) ? 1 : -1];
#if __SIZEOF_POINTER__ == 4
typedef char assert_th_layouts32[
    (sizeof(HEAPENTRY32) == 36 && sizeof(MODULEENTRY32) == 1076 &&
     sizeof(PROCESSENTRY32) == 564 &&
     offsetof(MODULEENTRY32, modBaseAddr) == 20 &&
     offsetof(MODULEENTRY32, szModule) == 32) ? 1 : -1];
#endif
typedef char assert_th_vals[
    (TH32CS_SNAPHEAPLIST == 1u && TH32CS_SNAPPROCESS == 2u &&
     TH32CS_SNAPTHREAD == 4u && TH32CS_SNAPMODULE == 8u &&
     TH32CS_SNAPALL == 0xFu && TH32CS_SNAPNOHEAPS == 0x40000000u &&
     TH32CS_GETALLMODS == 0x80000000u) ? 1 : -1];

/* M17 file-info structure layouts (winbase.h, from the CE pages). */
typedef char assert_fileinfo_layouts[
    (sizeof(BY_HANDLE_FILE_INFORMATION) == 56 &&
     offsetof(BY_HANDLE_FILE_INFORMATION, dwVolumeSerialNumber) == 28 &&
     offsetof(BY_HANDLE_FILE_INFORMATION, nFileIndexLow) == 48 &&
     offsetof(BY_HANDLE_FILE_INFORMATION, dwOID) == 52 &&
     sizeof(WIN32_FILE_ATTRIBUTE_DATA) == 36 &&
     offsetof(WIN32_FILE_ATTRIBUTE_DATA, nFileSizeLow) == 32) ? 1 : -1];
typedef char assert_m17_vals[
    (FILE_NOTIFY_CHANGE_FILE_NAME == 1u &&
     FILE_NOTIFY_CHANGE_DIR_NAME == 2u &&
     FILE_NOTIFY_CHANGE_SIZE == 8u &&
     FILE_NOTIFY_CHANGE_LAST_WRITE == 0x10u &&
     LOCKFILE_FAIL_IMMEDIATELY == 1u &&
     LOCKFILE_EXCLUSIVE_LOCK == 2u) ? 1 : -1];

/* M15 registry constants (winreg.h; values per fixed Win32 ABI). */
typedef char assert_reg_vals[
    (REG_NONE == 0 && REG_SZ == 1 && REG_EXPAND_SZ == 2 &&
     REG_BINARY == 3 && REG_DWORD == 4 &&
     REG_DWORD_LITTLE_ENDIAN == 4 && REG_DWORD_BIG_ENDIAN == 5 &&
     REG_LINK == 6 && REG_MULTI_SZ == 7 && REG_RESOURCE_LIST == 8 &&
     REG_OPTION_NON_VOLATILE == 0u && REG_OPTION_VOLATILE == 1u &&
     REG_CREATED_NEW_KEY == 1u && REG_OPENED_EXISTING_KEY == 2u &&
     REG_NOTIFY_CHANGE_NAME == 1u &&
     REG_NOTIFY_CHANGE_LAST_SET == 4u) ? 1 : -1];

/* M13 NLS constants (winnls.h; values per fixed Win32 ABI). */
typedef char assert_nls_vals[
    (CP_ACP == 0 && CP_OEMCP == 1 && CP_UTF7 == 65000 &&
     CP_UTF8 == 65001 &&
     MB_PRECOMPOSED == 1u && MB_ERR_INVALID_CHARS == 8u &&
     WC_SEPCHARS == 0x20u && WC_DEFAULTCHAR == 0x40u &&
     WC_COMPOSITECHECK == 0x200u) ? 1 : -1];

/* M13 usage shape (compile-only). */
static int m13_shaped_usage(void)
{
    WCHAR wbuf[16];
    char abuf[16];
    int n;

    n = MultiByteToWideChar(CP_UTF8, 0, "abc", 3, wbuf, 16);
    if (n <= 0)
        return (int) GetLastError();
    n = WideCharToMultiByte(CP_UTF8, WC_SEPCHARS, wbuf, n,
                            abuf, 16, NULL, NULL);
    if (n <= 0)
        return (int) GetLastError();
    if (!IsDBCSLeadByte((BYTE) 0))
        return (int) GetLastError();
    if (!IsDBCSLeadByteEx(CP_ACP, (BYTE) 0))
        return (int) GetLastError();
    return 0;
}

/* M14 usage shape (compile-only): fiber callbacks and handles. */
static VOID CALLBACK fiber_proc_shaper(PVOID lpParam)
{
    (void) lpParam;
}

static int m14_shaped_usage(void)
{
    LPVOID fiber, mainfiber;

    mainfiber = ConvertThreadToFiber(NULL);
    if (mainfiber == NULL)
        return (int) GetLastError();
    fiber = CreateFiber(0, fiber_proc_shaper, NULL);
    if (fiber == NULL)
        return (int) GetLastError();
    (void) GetCurrentFiber();
    (void) GetFiberData();
    SwitchToFiber(fiber);
    DeleteFiber(fiber);
    SwitchToFiber(mainfiber);
    DeleteFiber(mainfiber);
    return 0;
}

/* M16 usage shape (compile-only). */
static int m16_shaped_usage(void)
{
    static const WCHAR w_a[] = { 'a', 0 };
    static const WCHAR w_b[] = { 'b', 0 };
    CPINFO cpi;
    WORD ctypes[4] = { 0, 0, 0, 0 };
    LCID lcid;
    LANGID lang;
    UINT cp;

    cp = GetACP();
    if (cp == 0)
        return (int) GetLastError();
    (void) GetOEMCP();
    lcid = GetSystemDefaultLCID();
    (void) GetUserDefaultLCID();
    lang = GetSystemDefaultLangID();
    (void) GetUserDefaultLangID();
    if (!IsValidCodePage(CP_ACP))
        return (int) GetLastError();
    if (!IsValidLocale(lcid, LCID_INSTALLED))
        return (int) GetLastError();
    if (CompareStringW(lcid, 0, w_a, -1, w_b, -1) == 0)
        return (int) GetLastError();
    (void) ConvertDefaultLocale(lcid);
    if (GetCPInfo(CP_ACP, &cpi) == 0)
        return (int) GetLastError();
    (void) GetStringTypeW(CT_CTYPE1, w_a, -1, ctypes);
    (void) GetStringTypeExW(lcid, CT_CTYPE1, w_a, -1, ctypes);
    (void) lang;
    (void) PRIMARYLANGID(lang);
    (void) SUBLANGID(lang);
    (void) MAKELCID(lang, 0);
    return 0;
}

/* M17 usage shape (compile-only). */
static int m17_shaped_usage(void)
{
    static const WCHAR v_dir[] = { 't', 'm', 'p', 0 };
    static const WCHAR v_pref[] = { 'a', 'k', 0 };
    BY_HANDLE_FILE_INFORMATION bhi;
    WIN32_FILE_ATTRIBUTE_DATA wad;
    ULARGE_INTEGER freeavail, total, freebytes;
    HANDLE hch, hsrch;
    WCHAR wbuf[260];
    DWORD n;

    hch = FindFirstChangeNotification(v_dir, TRUE,
                                      FILE_NOTIFY_CHANGE_LAST_WRITE);
    if (hch != INVALID_HANDLE_VALUE) {
        (void) FindNextChangeNotification(hch);
        (void) FindCloseChangeNotification(hch);
    }
    n = GetTempPath(260u, wbuf);
    if (n == 0 || n > 260u)
        return (int) GetLastError();
    if (GetTempFileName(v_dir, v_pref, 0, wbuf) == 0)
        return (int) GetLastError();
    hsrch = FindFirstFileEx(v_dir, FindExInfoStandard, &wad,
                            FindExSearchLimitToDirectories, NULL, 0);
    if (hsrch != INVALID_HANDLE_VALUE)
        (void) FindClose(hsrch);
    (void) GetFileAttributesEx(v_dir, GetFileExInfoStandard, &wad);
    (void) GetDiskFreeSpaceEx(v_dir, &freeavail, &total, &freebytes);
    (void) GetFileInformationByHandle(INVALID_HANDLE_VALUE, &bhi);
    (void) DeleteAndRenameFile(wbuf, v_dir);
    (void) LockFileEx(INVALID_HANDLE_VALUE, LOCKFILE_EXCLUSIVE_LOCK,
                      0, 0, 0, NULL);
    (void) UnlockFileEx(INVALID_HANDLE_VALUE, 0, 0, 0, NULL);
    (void) GetFileVersionInfoSize(wbuf, NULL);
    (void) GetFileVersionInfo(wbuf, 0, 0u, wbuf);
    return 0;
}

/* M15 usage shape (compile-only): registry round trip on a
 * volatile test key under HKEY_CURRENT_USER.  Never run/linked. */
static int m15_shaped_usage(void)
{
    static const WCHAR w_key[] = { 't', 0 };
    static const WCHAR w_val[] = { 'v', 0 };
    static const WCHAR w_sub[] = { 's', 0 };
    HKEY hk = NULL, hsub = NULL;
    LONG lr;
    DWORD disp, type = 0, cb = sizeof(DWORD), cch;
    DWORD dw = 7;

    if ((HKEY) (LONG_PTR) 0x80000001 != HKEY_CURRENT_USER)
        return (int) ERROR_INVALID_PARAMETER;
    if (HKEY_LOCAL_MACHINE == HKEY_CLASSES_ROOT)
        return (int) ERROR_INVALID_PARAMETER;
    lr = RegCreateKeyExW(HKEY_CURRENT_USER, w_key, 0, NULL,
                         REG_OPTION_VOLATILE, 0, NULL, &hk, &disp);
    if (lr != ERROR_SUCCESS)
        return (int) lr;
    lr = RegSetValueExW(hk, w_val, 0, REG_DWORD,
                        (const BYTE *) &dw, sizeof(dw));
    if (lr == ERROR_SUCCESS) {
        dw = 0;
        lr = RegQueryValueExW(hk, w_val, NULL, &type,
                              (LPBYTE) &dw, &cb);
    }
    if (lr == ERROR_SUCCESS && (type != REG_DWORD || dw != 7))
        lr = ERROR_INVALID_PARAMETER;
    if (lr == ERROR_SUCCESS)
        lr = RegCreateKeyExW(hk, w_sub, 0, NULL, REG_OPTION_VOLATILE,
                             0, NULL, &hsub, NULL);
    if (lr == ERROR_SUCCESS && hsub != NULL) {
        cch = 0;
        (void) RegEnumKeyExW(hk, 0, NULL, &cch, NULL, NULL, NULL,
                             NULL);
        (void) RegQueryInfoKeyW(hk, NULL, NULL, NULL, NULL, NULL,
                                NULL, NULL, NULL, NULL, NULL, NULL);
        RegDeleteKeyW(hk, w_sub);
    }
    if (lr == ERROR_SUCCESS)
        RegDeleteValueW(hk, w_val);
    RegFlushKeyW(hk);
    RegCloseKeyW(hk);
    return 0;
}

/* M18 usage shape (compile-only). */
static int m18_shaped_usage(void)
{
    HANDLE snap;
    PROCESSENTRY32 pe;
    THREADENTRY32 te;
    MODULEENTRY32 me;
    DWORD cb = 0;

    snap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    if (snap == INVALID_HANDLE_VALUE)
        return (int) GetLastError();
    pe.dwSize = sizeof(pe);
    if (Process32First(snap, &pe))
        (void) Process32Next(snap, &pe);
    te.dwSize = sizeof(te);
    if (Thread32First(snap, &te))
        (void) Thread32Next(snap, &te);
    me.dwSize = sizeof(me);
    if (Module32First(snap, &me))
        (void) Module32Next(snap, &me);
    (void) Toolhelp32ReadProcessMemory(pe.th32ProcessID, NULL,
                                       (LPVOID) &cb, sizeof(cb), &cb);
    (void) CloseToolhelp32Snapshot(snap);
    return 0;
}

/* M19 usage shape (compile-only). */
static int m19_shaped_usage(void)
{
    static const WCHAR w_fmt[] = { '%', 'd', 0 };
    WCHAR buf[64];
    (void) CharLowerW(buf);
    (void) CharUpperW(buf);
    (void) CharLowerBuffW(buf, 4u);
    (void) CharUpperBuffW(buf, 4u);
    (void) CharNextW(buf);
    (void) CharPrevW(buf, buf);
    (void) IsCharAlphaW(buf[0]);
    (void) IsCharAlphaNumericW(buf[0]);
    (void) IsCharLowerW(buf[0]);
    (void) IsCharUpperW(buf[0]);
    (void) wsprintfW(buf, w_fmt, 3);
    (void) LoadStringW((HINSTANCE) 0, 1u, buf, 64);
    return 0;
}

/* M20 usage shape (compile-only): file mapping round trip. */
static int m20_shaped_usage(void)
{
    static const WCHAR m_name[] = { 'm', 'a', 'p', 0 };
    HANDLE hf, hm;
    LPVOID view;

    hf = CreateFileForMappingW(m_name, GENERIC_READ | GENERIC_WRITE,
                               FILE_SHARE_READ, NULL, OPEN_ALWAYS,
                               FILE_ATTRIBUTE_NORMAL, NULL);
    if (hf == INVALID_HANDLE_VALUE)
        return (int) GetLastError();
    hm = CreateFileMappingW(hf, NULL, PAGE_READWRITE, 0, 4096u, NULL);
    if (hm == NULL) {
        (void) CloseHandle(hf);
        return (int) GetLastError();
    }
    view = MapViewOfFile(hm, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    if (view != NULL) {
        (void) FlushViewOfFile(view, 4096u);
        (void) UnmapViewOfFile(view);
    }
    (void) CloseHandle(hm);
    (void) CloseHandle(hf);
    return 0;
}

static int m20b_shaped_usage(void)
{
    MODULEINFO mi;

    (void) DisableThreadLibraryCalls((HMODULE) 0);
    (void) GetModuleInformation((HANDLE) 0, (HMODULE) 0, &mi,
                                sizeof(mi));
    return (DLL_PROCESS_ATTACH == 1 && DLL_PROCESS_DETACH == 0 &&
            DLL_THREAD_ATTACH == 2 && DLL_THREAD_DETACH == 3) ? 0 : 1;
}

/* M21 usage shape (compile-only). */
static int m21_shaped_usage(void)
{
    static const WCHAR c_path[] = { 't', 'm', 'p', 0 };
    STORE_INFORMATION si;
    WCHAR canon[MAX_PATH];
    BYTE rnd[8];
    DWORD cbret = 0, cbavail = 0;

    (void) GetStoreInformation(&si);
    (void) CeGenRandom(sizeof(rnd), rnd);
    (void) CeGetCanonicalPathName(c_path, canon, MAX_PATH, 0);
    (void) CeGetFileNotificationInfo((HANDLE) 0, 0, NULL, 0,
                                     &cbret, &cbavail);
    return (FILE_ACTION_ADDED == 1 && FILE_ACTION_RENAMED_NEW_NAME == 5
            && si.dwStoreSize == 0) ? 0 : 1;
}

/* M22 usage shape (compile-only; msgqueue.h). */
static int m22_shaped_usage(void)
{
    static const WCHAR qname[] = { 'A', 'k', 'a', 'r', 'i', 'Q', 0 };
    BYTE buf[64];
    MSGQUEUEOPTIONS opt;
    MSGQUEUEINFO info;
    DWORD cb = 0, got = 0;
    HANDLE q = 0, q2 = 0;

    opt.dwSize = sizeof(MSGQUEUEOPTIONS);
    opt.dwFlags = 0;              /* flag values unpublished on the CE
                                     pages (MSGQUEUE_NOPRECOMMIT etc.) */
    opt.dwMaxMessages = 8;
    opt.cbMaxMessage = 64;
    opt.bReadAccess = TRUE;
    q = CreateMsgQueue(qname, &opt);
    q2 = OpenMsgQueue((HANDLE) 0, q, &opt);
    (void) CloseMsgQueue(q2);
    (void) CloseMsgQueue(q);
    (void) GetMsgQueueInfo(q, &info);
    (void) ReadMsgQueue(q, buf, sizeof(buf), &cb, 0, &got);
    (void) WriteMsgQueue(q, buf, sizeof(buf), 0, 0);
    return (info.dwCurrentMessages == 0
            && opt.cbMaxMessage == 64 && opt.bReadAccess == TRUE) ? 0 : 1;
}

/* M23 usage shape (compile-only; winbase.h serial API). */
static int m23_shaped_usage(void)
{
    DCB dcb;
    COMMTIMEOUTS cto;
    COMMPROP prop;
    COMSTAT stat;
    DWORD mask = 0, errs = 0;

    dcb.DCBlength = sizeof(DCB);
    dcb.BaudRate = 9600u;         /* CBR_* named values unpublished */
    dcb.fBinary = 1;
    dcb.fParity = 0;
    dcb.fDtrControl = 0;
    dcb.fRtsControl = 0;
    dcb.fDummy2 = 0;
    dcb.ByteSize = 8;
    dcb.Parity = 0;
    dcb.StopBits = 0;
    (void) GetCommState((HANDLE) 0, &dcb);
    (void) SetCommState((HANDLE) 0, &dcb);
    (void) SetCommTimeouts((HANDLE) 0, &cto);
    (void) GetCommTimeouts((HANDLE) 0, &cto);
    (void) GetCommProperties((HANDLE) 0, &prop);
    (void) ClearCommError((HANDLE) 0, &errs, &stat);
    (void) GetCommModemStatus((HANDLE) 0, &mask);
    (void) PurgeComm((HANDLE) 0, 0);
    (void) WaitCommEvent((HANDLE) 0, &mask, NULL);
    (void) TransmitCommChar((HANDLE) 0, 'A');
    (void) SetupComm((HANDLE) 0, 4096u, 4096u);
    return (dcb.fBinary == 1 && dcb.ByteSize == 8) ? 0 : 1;
}

/* M24 usage shape (compile-only; SEH/debugging declarations). */
static int m24_shaped_usage(void)
{
    static const WCHAR zone_fmt[] = { 'z','o','n','e','=','%','x','\n',0 };
    static const WCHAR boot_msg[] = { 'b','o','o','t','\n',0 };
    DBGPARAM zones;
    DEBUG_EVENT de;
    EXCEPTION_POINTERS ep;
    EXCEPTION_RECORD er;

    zones.lpszName[0] = L'D';
    zones.ulZoneMask = 0;
    (void) RegisterDbgZones((HMODULE) 0, &zones);
    (void) NKDbgPrintfW(zone_fmt, zones.ulZoneMask);
    (void) WriteDebugLED(0, 1);
    (void) ReportFault(&ep, 0);
    (void) WaitForDebugEvent(&de, 0);
    (void) DebugActiveProcess((DWORD) 0);
    (void) ContinueDebugEvent(0, 0, DBG_CONTINUE);
    er.ExceptionCode = EXCEPTION_ACCESS_VIOLATION;
    ep.ExceptionRecord = &er;
    (void) RaiseException(er.ExceptionCode, EXCEPTION_NONCONTINUABLE,
                          0, NULL);
    (void) OutputDebugStringW(boot_msg);
    (void) DebugBreak();
    return (DBG_EXCEPTION_NOT_HANDLED == 0x80010001L
            && EXCEPTION_DEBUG_EVENT == 1
            && OUTPUT_DEBUG_STRING_EVENT == 8
            && de.dwDebugEventCode == 0 && de.u.Exception.dwFirstChance == 0)
           ? 0 : 1;
}

/* M25 usage shape (compile-only; winerror/FormatMessage/NAT/CeLog). */
static int m25_shaped_usage(void)
{
    static const WCHAR mfmt[] = { '%','1','\n',0 };
    WCHAR zstr[] = { 'z','\n',0 };
    DWORD dwZoneUser = 0, dwZoneCE = 0, dwProc = 0, dwAvail = 0;
    WCHAR buf[80];
    va_list vl;
    DWORD n;

    n = FormatMessageW(FORMAT_MESSAGE_FROM_STRING
                       | FORMAT_MESSAGE_IGNORE_INSERTS,
                       (LPCVOID) mfmt, 0, 0, buf, 80, &vl);
    (void) n;
    (void) CeLogSetZones(dwZoneUser, dwZoneCE, dwProc);
    (void) CeLogGetZones(&dwZoneUser, &dwZoneCE, &dwProc, &dwAvail);
    (void) CeLogQueryZones(&dwZoneUser, &dwZoneCE, &dwProc);
    (void) CeLogMsg(zstr);
    (void) CeLogInterrupt(0);
    (void) CeLogReSync();
    (void) EditorDeregister((PVOID) 0);
    (void) TimeoutSession((PVOID) 0, (PVOID) 0);
    (void) DisassociateSession((PVOID) 0, (PVOID) 0);
    return (FORMAT_MESSAGE_ALLOCATE_BUFFER == 0x100
            && FORMAT_MESSAGE_ARGUMENT_ARRAY == 0x2000
            && ERROR_SUCCESS == 0
            && NatInboundDirection == 0 && NatOutboundDirection == 1
            && dwZoneCE == 0) ? 0 : 1;
}

/* M26 usage shape (compile-only; GWES winuser surface).  Exercises the
 * declared prototypes, the struct layouts used by the official pages,
 * and the fixed ABI values currently in the headers. */
static BOOL CALLBACK tu_enumproc(HWND hwnd, LPARAM lParam)
{
    (void) hwnd;
    (void) lParam;
    return TRUE;
}

static LRESULT CALLBACK tu_wndproc(HWND hwnd, UINT uMsg, WPARAM wParam,
                                   LPARAM lParam)
{
    (void) hwnd;
    (void) uMsg;
    (void) wParam;
    (void) lParam;
    return 0;
}

static VOID CALLBACK tu_timerproc(HWND hwnd, UINT uMsg, UINT idEvent,
                                  DWORD dwTime)
{
    (void) hwnd;
    (void) uMsg;
    (void) idEvent;
    (void) dwTime;
}

static BOOL CALLBACK tu_propenum(HWND hwnd, LPTSTR lpszString,
                                 HANDLE hData, ULONG_PTR dwData)
{
    (void) hwnd;
    (void) lpszString;
    (void) hData;
    (void) dwData;
    return TRUE;
}

static int m26_shaped_usage(void)
{
    WCHAR cls[] = { 'C', 0 };
    WNDCLASS wc;
    MSG msg;
    INPUT inp;
    ACCEL acc;
    SCROLLINFO si;
    CREATESTRUCT cs;
    STYLESTRUCT ss;
    WINDOWPOS wp;
    RECT rc = { 0, 0, 0, 0 };
    POINT pt = { 0, 0 };
    HWND hwnd;
    WPARAM wp_lo;
    HKL kl;

    wc.style = 0;
    wc.lpfnWndProc = tu_wndproc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = (HINSTANCE) 0;
    wc.hIcon = (HICON) 0;
    wc.hCursor = (HCURSOR) 0;
    wc.hbrBackground = (HBRUSH) 0;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = cls;
    (void) RegisterClassW(&wc);
    (void) GetClassInfoW((HINSTANCE) 0, cls, &wc);
    hwnd = CreateWindowW(cls, NULL, 0, 0, 0, 100, 100, (HWND) 0,
                         (HMENU) 0, (HANDLE) 0, NULL);
    (void) CreateWindowExW(0, cls, NULL, 0, 0, 0, 100, 100,
                           (HWND) 0, (HMENU) 0, (HINSTANCE) 0, NULL);
    (void) GetClassLongW(hwnd, 0);
    (void) SetClassLongW(hwnd, 0, 0);
    (void) GetClassNameW(hwnd, (LPTSTR) cls, 2);
    (void) GetWindowLongW(hwnd, 0);
    (void) SetWindowLongW(hwnd, 0, 0);
    (void) GetDesktopWindow();
    (void) GetForegroundWindow();
    (void) SetForegroundWindow(hwnd);
    (void) IsWindow(hwnd);
    (void) IsWindowVisible(hwnd);
    (void) IsChild(hwnd, hwnd);
    (void) GetParent(hwnd);
    (void) SetParent(hwnd, hwnd);
    (void) FindWindowW(cls, NULL);
    (void) ChildWindowFromPoint(hwnd, pt);
    (void) WindowFromPoint(pt);
    (void) EnumWindows(tu_enumproc, 0);
    (void) GetWindow(hwnd, 0);
    (void) GetClientRect(hwnd, &rc);
    (void) GetWindowRect(hwnd, &rc);
    (void) GetWindowTextLengthW(hwnd);
    (void) SetWindowTextW(hwnd, cls);
    (void) GetWindowThreadProcessId(hwnd, NULL);
    (void) ShowWindow(hwnd, 0);
    (void) BringWindowToTop(hwnd);
    (void) MoveWindow(hwnd, 0, 0, 100, 100, TRUE);
    (void) SetWindowPos(hwnd, (HWND) 0, 0, 0, 100, 100, 0);
    (void) AdjustWindowRectEx(&rc, 0, FALSE, 0);
    (void) DefWindowProc(hwnd, 0, 0, 0);
    (void) CallWindowProc(tu_wndproc, hwnd, 0, 0, 0);
    (void) BeginDeferWindowPos(1);
    (void) SetTimer(hwnd, 1, 100, tu_timerproc);
    (void) KillTimer(hwnd, 1);
    (void) SystemIdleTimerReset();
    (void) CreateCaret(hwnd, (HBITMAP) 0, 1, 1);
    (void) GetCaretPos(&pt);
    (void) SetCaretPos(1, 1);
    (void) GlobalAddAtomW(cls);
    (void) GetMessage(&msg, hwnd, 0, 0);
    (void) PeekMessage(&msg, hwnd, 0, 0, 0);
    (void) DispatchMessage(&msg);
    (void) TranslateMessage(&msg);
    (void) PostMessage(hwnd, 0, 0, 0);
    (void) PostThreadMessage(0, 0, 0, 0);
    (void) SendMessage(hwnd, 0, 0, 0);
    (void) SendNotifyMessage(hwnd, 0, 0, 0);
    (void) PostQuitMessage(0);
    (void) RegisterWindowMessageW(cls);
    (void) GetMessagePos();
    (void) GetQueueStatus(0);
    (void) GetAsyncKeyState(0);
    (void) SetFocus(hwnd);
    (void) SetActiveWindow(hwnd);
    (void) EnableWindow(hwnd, TRUE);
    (void) IsWindowEnabled(hwnd);
    kl = ActivateKeyboardLayout((HKL) 0, 0);
    (void) GetKeyboardLayoutList(0, NULL);
    (void) MapVirtualKey(0, 0);
    (void) keybd_event(0, 0, 0, 0);
    (void) LoadKeyboardLayout("00000409", 0);
    (void) RegisterHotKey(hwnd, 1, 0, 0);
    (void) UnregisterHotKey(hwnd, 1);
    acc.fVirt = 0;
    acc.key = 0;
    acc.cmd = 0;
    acc.pad = 0;
    (void) CreateAcceleratorTable(&acc, 1);
    inp.type = 0;
    inp.ki.wVk = 0;
    inp.ki.wScan = 0;
    inp.ki.dwFlags = 0;
    (void) SendInput(1, &inp, (int) sizeof(inp));
    si.cbSize = (UINT) sizeof(SCROLLINFO);
    si.fMask = SIF_ALL;
    si.nMin = 0;
    si.nMax = 100;
    (void) GetScrollInfo(hwnd, SB_VERT, &si);
    (void) SetScrollInfo(hwnd, SB_VERT, &si, FALSE);
    (void) SetScrollPos(hwnd, SB_HORZ, 0, FALSE);
    (void) SetScrollRange(hwnd, SB_VERT, 0, 100, FALSE);
    (void) ScrollWindowEx(hwnd, 0, -1, NULL, NULL, (HRGN) 0, NULL, 0);
    (void) ScrollDC((HDC) 0, 0, 0, &rc, NULL, (HRGN) 0, NULL);
    (void) SetPropW(hwnd, cls, (HANDLE) 1);
    (void) GetPropW(hwnd, cls);
    (void) RemovePropW(hwnd, cls);
    (void) EnumPropsExW(hwnd, tu_propenum, 0);
    (void) SendMessageTimeout(hwnd, 0, 0, 0, 0, 0, NULL);
    (void) MsgWaitForMultipleObjects(0, NULL, TRUE, 0, 0);
    (void) MsgWaitForMultipleObjectsEx(0, NULL, 0, 0, 0);
    cs.lpCreateParams = NULL;
    cs.hwndParent = hwnd;
    cs.dwExStyle = 0;
    ss.styleOld = 0;
    ss.styleNew = 0;
    wp.hwnd = hwnd;
    wp.flags = 0;
    (void) cs;
    (void) ss;
    (void) wp;
    (void) kl;
    wp_lo = MAKEWPARAM(0x1234, 0x5678);
    (void) wp_lo;
    return (SIF_RANGE == 0x0001 && SIF_PAGE == 0x0002
            && SIF_POS == 0x0004 && SIF_DISABLENOSCROLL == 0x0008
            && SIF_TRACKPOS == 0x0010 && SIF_ALL == 0x0017
            && SB_HORZ == 0 && SB_VERT == 1 && SB_CTL == 2 && SB_BOTH == 3
            && SW_SCROLLCHILDREN == 0x0001 && SW_INVALIDATE == 0x0002
            && SW_ERASE == 0x0004 && SW_SMOOTHSCROLL == 0x0010
            && MAKEWPARAM(0x1234, 0x5678) == ((WPARAM) 0x56781234)
            && MAKELPARAM(0x1234, 0x5678) == ((LPARAM) 0x56781234)
            && MAKELRESULT(0, 1) == ((LRESULT) 0x10000))
           ? 0 : 1;
}

/* M27: GDI Reference -- exercise every GDI declaration with typed
 * null arguments; verify the documented (pointer-free) structure
 * layouts and the GetR/GetG/GetB color-byte macros.
 * BITMAPFILEHEADER is 14 bytes on disk; its in-memory C layout
 * (natural DWORD alignment) is 16 bytes, like the desktop SDK. */
static int m27_shaped_usage(void)
{
    if (sizeof(BITMAPINFOHEADER) != 40
        || sizeof(BITMAPFILEHEADER) != 16
        || sizeof(BITMAPCOREHEADER) != 12
        || sizeof(RGBQUAD) != 4
        || sizeof(RGBTRIPLE) != 3
        || sizeof(PALETTEENTRY) != 4
        || sizeof(BLENDFUNCTION) != 4
        || sizeof(TRIVERTEX) != 16
        || sizeof(GRADIENT_RECT) != 8
        || sizeof(LOGBRUSH) != 12
        || sizeof(LOGPEN) != 16
        || sizeof(LOGPALETTE) != 8
        || sizeof(POINTS) != 4
        || sizeof(RECTL) != 16
        || sizeof(RGNDATAHEADER) != 32
        || sizeof(COLORREF) != 4)
        return 1;
    if (!(GetRValue(0x112233u) == 0x33
          && GetGValue(0x112233u) == 0x22
          && GetBValue(0x112233u) == 0x11))
        return 1;
    (void) AlphaBlend((HDC)0, (int)0, (int)0, (int)0, (int)0, (HDC)0, (int)0, (int)0, (int)0, (int)0, (BLENDFUNCTION){0, 0, 0, 0});
    (void) BeginPaint((HWND)0, (LPPAINTSTRUCT)0);
    (void) BitBlt((HDC)0, (int)0, (int)0, (int)0, (int)0, (HDC)0, (int)0, (int)0, (DWORD)0);
    (void) ChangeDisplaySettingsEx((LPCTSTR)0, (LPDEVMODE)0, (HWND)0, (DWORD)0, (LPVOID)0);
    (void) ClientToScreen((HWND)0, (LPPOINT)0);
    (void) CombineRgn((HRGN)0, (HRGN)0, (HRGN)0, (int)0);
    (void) CopyRect((LPRECT)0, (const RECT*)0);
    (void) CreateBitmap((int)0, (int)0, (UINT)0, (UINT)0, (CONST VOID*)0);
    (void) CreateCompatibleBitmap((HDC)0, (int)0, (int)0);
    (void) CreateCompatibleDC((HDC)0);
    (void) CreateDC((LPCTSTR)0, (LPCTSTR)0, (LPCTSTR)0, (CONST DEVMODE*)0);
    (void) CreateDIBPatternBrushPt((const void*)0, (UINT)0);
    (void) CreateDIBSection((HDC)0, (const BITMAPINFO*)0, (UINT)0, (void**)0, (HANDLE)0, (DWORD)0);
    (void) CreatePalette((CONST LOGPALETTE*)0);
    (void) CreatePatternBrush((HBITMAP)0);
    (void) CreatePen((int)0, (int)0, (COLORREF)0);
    (void) CreatePenIndirect((const LOGPEN*)0);
    (void) CreateRectRgn((int)0, (int)0, (int)0, (int)0);
    (void) CreateRectRgnIndirect((const RECT*)0);
    (void) CreateSolidBrush((COLORREF)0);
    (void) DeleteDC((HDC)0);
    (void) DeleteObject((HGDIOBJ)0);
    (void) DrawEdge((HDC)0, (LPRECT)0, (UINT)0, (UINT)0);
    (void) DrawFocusRect((HDC)0, (const RECT*)0);
    (void) DrawFrameControl((HDC)0, (LPRECT)0, (UINT)0, (UINT)0);
    (void) Ellipse((HDC)0, (int)0, (int)0, (int)0, (int)0);
    (void) EndPaint((HWND)0, (CONST PAINTSTRUCT*)0);
    (void) EnumDisplayDevices((LPCTSTR)0, (DWORD)0, (PDISPLAY_DEVICE)0, (DWORD)0);
    (void) EnumDisplaySettings((LPCTSTR)0, (DWORD)0, (LPDEVMODE)0);
    (void) EqualRect((const RECT*)0, (const RECT*)0);
    (void) EqualRgn((HRGN)0, (HRGN)0);
    (void) ExcludeClipRect((HDC)0, (int)0, (int)0, (int)0, (int)0);
    (void) ExtCreateRegion((CONST XFORM*)0, (DWORD)0, (CONST RGNDATA*)0);
    (void) ExtEscape((HDC)0, (int)0, (int)0, (LPCSTR)0, (int)0, (LPSTR)0);
    (void) FillRect((HDC)0, (CONST RECT*)0, (HBRUSH)0);
    (void) FillRgn((HDC)0, (HRGN)0, (HBRUSH)0);
    (void) GetBkColor((HDC)0);
    (void) GetBkMode((HDC)0);
    (void) GetClipBox((HDC)0, (LPRECT)0);
    (void) GetClipRgn((HDC)0, (HRGN)0);
    (void) GetCurrentObject((HDC)0, (UINT)0);
    (void) GetCurrentPositionEx((HDC)0, (LPPOINT)0);
    (void) GetDC((HWND)0);
    (void) GetDCEx((HWND)0, (HRGN)0, (DWORD)0);
    (void) GetDeviceCaps((HDC)0, (int)0);
    (void) GetDIBColorTable((HDC)0, (UINT)0, (UINT)0, (RGBQUAD*)0);
    (void) GetLayout((HDC)0);
    (void) GetNearestColor((HDC)0, (COLORREF)0);
    (void) GetNearestPaletteIndex((HPALETTE)0, (COLORREF)0);
    (void) GetObject((HGDIOBJ)0, (int)0, (LPVOID)0);
    (void) GetObjectType((HGDIOBJ)0);
    (void) GetOutlineTextMetrics((HDC)0, (UINT)0, (LPOUTLINETEXTMETRICW)0);
    (void) GetPaletteEntries((HPALETTE)0, (UINT)0, (UINT)0, (LPPALETTEENTRY)0);
    (void) GetPixel((HDC)0, (int)0, (int)0);
    (void) GetRegionData((HRGN)0, (DWORD)0, (LPRGNDATA)0);
    (void) GetRgnBox((HRGN)0, (LPRECT)0);
    (void) GetROP2((HDC)0);
    (void) GetStockObject((int)0);
    (void) GetStretchBltMode((HDC)0);
    (void) GetSysColorBrush((int)0);
    (void) GetSystemPaletteEntries((HDC)0, (UINT)0, (UINT)0, (LPPALETTEENTRY)0);
    (void) GetUpdateRect((HWND)0, (LPRECT)0, (BOOL)0);
    (void) GetUpdateRgn((HWND)0, (HRGN)0, (BOOL)0);
    (void) GetViewportExtEx((HDC)0, (LPSIZE)0);
    (void) GetViewportOrgEx((HDC)0, (LPPOINT)0);
    (void) GetWindowDC((HWND)0);
    (void) GetWindowExtEx((HDC)0, (LPSIZE)0);
    (void) GetWindowOrgEx((HDC)0, (LPPOINT)0);
    (void) GetWindowRgn((HWND)0, (HRGN)0);
    (void) GradientFill((HDC)0, (PTRIVERTEX)0, (ULONG)0, (PVOID)0, (ULONG)0, (ULONG)0);
    (void) InflateRect((LPRECT)0, (int)0, (int)0);
    (void) IntersectClipRect((HDC)0, (int)0, (int)0, (int)0, (int)0);
    (void) IntersectRect((LPRECT)0, (const RECT*)0, (const RECT*)0);
    (void) InvalidateRect((HWND)0, (const RECT*)0, (BOOL)0);
    (void) InvalidateRgn((HWND)0, (HRGN)0, (BOOL)0);
    (void) InvertRect((HDC)0, (CONST RECT*)0);
    (void) IsRectEmpty((const RECT*)0);
    (void) LineTo((HDC)0, (int)0, (int)0);
    (void) LoadBitmap((HINSTANCE)0, (LPCTSTR)0);
    (void) MapWindowPoints((HWND)0, (HWND)0, (LPPOINT)0, (UINT)0);
    (void) MaskBlt((HDC)0, (int)0, (int)0, (int)0, (int)0, (HDC)0, (int)0, (int)0, (HBITMAP)0, (int)0, (int)0, (DWORD)0);
    (void) MoveToEx((HDC)0, (int)0, (int)0, (LPPOINT)0);
    (void) OffsetRect((LPRECT)0, (int)0, (int)0);
    (void) OffsetRgn((HRGN)0, (int)0, (int)0);
    (void) OffsetViewportOrgEx((HDC)0, (int)0, (int)0, (LPPOINT)0);
    (void) PatBlt((HDC)0, (int)0, (int)0, (int)0, (int)0, (DWORD)0);
    (void) Polygon((HDC)0, (const POINT*)0, (int)0);
    (void) Polyline((HDC)0, (const POINT*)0, (int)0);
    (void) PtInRect((const RECT*)0, (POINT){0, 0});
    (void) PtInRegion((HRGN)0, (int)0, (int)0);
    (void) RealizePalette((HDC)0);
    (void) Rectangle((HDC)0, (int)0, (int)0, (int)0, (int)0);
    (void) RectInRegion((HRGN)0, (const RECT*)0);
    (void) RectVisible((HDC)0, (CONST RECT*)0);
    (void) RedrawWindow((HWND)0, (CONST RECT*)0, (HRGN)0, (UINT)0);
    (void) ReleaseDC((HWND)0, (HDC)0);
    (void) RestoreDC((HDC)0, (int)0);
    (void) RoundRect((HDC)0, (int)0, (int)0, (int)0, (int)0, (int)0, (int)0);
    (void) SaveDC((HDC)0);
    (void) ScreenToClient((HWND)0, (LPPOINT)0);
    (void) SelectClipRgn((HDC)0, (HRGN)0);
    (void) SelectObject((HDC)0, (HGDIOBJ)0);
    (void) SelectPalette((HDC)0, (HPALETTE)0, (BOOL)0);
    (void) SetBitmapBits((HBITMAP)0, (DWORD)0, (CONST VOID *)0);
    (void) SetBkColor((HDC)0, (COLORREF)0);
    (void) SetBkMode((HDC)0, (int)0);
    (void) SetBrushOrgEx((HDC)0, (int)0, (int)0, (LPPOINT)0);
    (void) SetDIBColorTable((HDC)0, (UINT)0, (UINT)0, (CONST RGBQUAD*)0);
    (void) SetDIBitsToDevice((HDC)0, (int)0, (int)0, (DWORD)0, (DWORD)0, (int)0, (int)0, (UINT)0, (UINT)0, (CONST VOID*)0, (CONST BITMAPINFO*)0, (UINT)0);
    (void) SetLayout((HDC)0, (DWORD)0);
    (void) SetPaletteEntries((HPALETTE)0, (UINT)0, (UINT)0, (CONST PALETTEENTRY*)0);
    (void) SetPixel((HDC)0, (int)0, (int)0, (COLORREF)0);
    (void) SetRect((LPRECT)0, (int)0, (int)0, (int)0, (int)0);
    (void) SetRectEmpty((LPRECT)0);
    (void) SetRectRgn((HRGN)0, (int)0, (int)0, (int)0, (int)0);
    (void) SetROP2((HDC)0, (int)0);
    (void) SetStretchBltMode((HDC)0, (int)0);
    (void) SetViewportOrgEx((HDC)0, (int)0, (int)0, (LPPOINT)0);
    (void) SetWindowOrgEx((HDC)0, (int)0, (int)0, (LPPOINT)0);
    (void) SetWindowRgn((HWND)0, (HRGN)0, (BOOL)0);
    (void) StretchBlt((HDC)0, (int)0, (int)0, (int)0, (int)0, (HDC)0, (int)0, (int)0, (int)0, (int)0, (DWORD)0);
    (void) StretchDIBits((HDC)0, (int)0, (int)0, (int)0, (int)0, (int)0, (int)0, (int)0, (int)0, (CONST VOID*)0, (CONST BITMAPINFO*)0, (UINT)0, (DWORD)0);
    (void) SubtractRect((LPRECT)0, (const RECT*)0, (const RECT*)0);
    (void) TransparentBlt((HDC)0, (int)0, (int)0, (int)0, (int)0, (HDC)0, (int)0, (int)0, (int)0, (int)0, (UINT)0);
    (void) TransparentImage((HDC)0, (LONG)0, (LONG)0, (LONG)0, (LONG)0, (HANDLE)0, (LONG)0, (LONG)0, (LONG)0, (LONG)0, (COLORREF)0);
    (void) UnionRect((LPRECT)0, (const RECT*)0, (const RECT*)0);
    (void) UpdateWindow((HWND)0);
    (void) ValidateRect((HWND)0, (const RECT*)0);
    (void) ValidateRgn((HWND)0, (HRGN)0);
    return 0;
}

/* M28: window-control function layer -- exercise every declaration with
 * typed null arguments and verify the documented CE structure layouts.
 * Pointer-bearing structures are checked under the 32-bit pointer guard
 * (CE is always 32-bit; the CE toolchain matrix verifies the model). */
static int m28_shaped_usage(void)
{
    /* Menus */
    (void) AppendMenu((HMENU)0, (UINT)0, (UINT)0, (LPCTSTR)0);
    (void) CheckMenuItem((HMENU)0, (UINT)0, (UINT)0);
    (void) CheckMenuRadioItem((HMENU)0, (UINT)0, (UINT)0, (UINT)0, (UINT)0);
    (void) CreateMenu();
    (void) CreatePopupMenu();
    (void) DeleteMenu((HMENU)0, (UINT)0, (UINT)0);
    (void) DestroyMenu((HMENU)0);
    (void) DrawMenuBar((HWND)0);
    (void) EnableMenuItem((HMENU)0, (UINT)0, (UINT)0);
    (void) GetMenuItemInfo((HMENU)0, (UINT)0, (BOOL)0, (LPMENUITEMINFO)0);
    (void) GetSubMenu((HMENU)0, (int)0);
    (void) GetSystemMenu((HWND)0, (BOOL)0);
    (void) InsertMenu((HMENU)0, (UINT)0, (UINT)0, (UINT)0, (LPCTSTR)0);
    (void) LoadMenu((HINSTANCE)0, (LPCTSTR)0);
    (void) RemoveMenu((HMENU)0, (UINT)0, (UINT)0);
    (void) SetMenuItemInfo((HMENU)0, (UINT)0, (BOOL)0, (LPCMENUITEMINFO)0);
    (void) TrackPopupMenu((HMENU)0, (UINT)0, (int)0, (int)0, (int)0,
                          (HWND)0, (const RECT*)0);
    (void) TrackPopupMenuEx((HMENU)0, (UINT)0, (int)0, (int)0, (HWND)0,
                            (LPTPMPARAMS)0);
    /* Dialog boxes */
    (void) CreateDialog((HINSTANCE)0, (LPCTSTR)0, (HWND)0, (DLGPROC)0);
    (void) CreateDialogIndirect((HINSTANCE)0, (LPCDLGTEMPLATE)0, (HWND)0,
                                (DLGPROC)0);
    (void) CreateDialogIndirectParam((HINSTANCE)0, (LPCDLGTEMPLATE)0, (HWND)0,
                                     (DLGPROC)0, (LPARAM)0);
    (void) CreateDialogParam((HINSTANCE)0, (LPCTSTR)0, (HWND)0, (DLGPROC)0,
                             (LPARAM)0);
    (void) DefDlgProc((HWND)0, (UINT)0, (WPARAM)0, (LPARAM)0);
    (void) DialogBox((HINSTANCE)0, (LPCTSTR)0, (HWND)0, (DLGPROC)0);
    (void) DialogBoxIndirect((HINSTANCE)0, (LPDLGTEMPLATE)0, (HWND)0,
                             (DLGPROC)0);
    (void) DialogBoxIndirectParam((HINSTANCE)0, (LPCDLGTEMPLATE)0, (HWND)0,
                                  (DLGPROC)0, (LPARAM)0);
    (void) DialogBoxParam((HINSTANCE)0, (LPCTSTR)0, (HWND)0, (DLGPROC)0,
                          (LPARAM)0);
    (void) EndDialog((HWND)0, (int)0);
    (void) GetDialogBaseUnits();
    (void) GetDlgCtrlID((HWND)0);
    (void) GetDlgItem((HWND)0, (int)0);
    (void) GetDlgItemInt((HWND)0, (int)0, (BOOL*)0, (BOOL)0);
    (void) GetDlgItemText((HWND)0, (int)0, (LPTSTR)0, (int)0);
    (void) GetNextDlgGroupItem((HWND)0, (HWND)0, (BOOL)0);
    (void) GetNextDlgTabItem((HWND)0, (HWND)0, (BOOL)0);
    (void) IsDialogMessage((HWND)0, (LPMSG)0);
    (void) MapDialogRect((HWND)0, (LPRECT)0);
    (void) SendDlgItemMessage((HWND)0, (int)0, (UINT)0, (WPARAM)0, (LPARAM)0);
    (void) SetDlgItemInt((HWND)0, (int)0, (UINT)0, (BOOL)0);
    (void) SetDlgItemText((HWND)0, (int)0, (LPCTSTR)0);
    (void) MessageBox((HWND)0, (LPCTSTR)0, (LPCTSTR)0, (UINT)0);
    (void) MessageBeep((UINT)0);
    (void) CheckDlgButton((HWND)0, (int)0, (UINT)0);
    (void) IsDlgButtonChecked((HWND)0, (int)0);
    (void) CheckRadioButton((HWND)0, (int)0, (int)0, (int)0);
    /* Clipboard */
    (void) CloseClipboard();
    (void) CountClipboardFormats();
    (void) EmptyClipboard();
    (void) EnumClipboardFormats((UINT)0);
    (void) GetClipboardData((UINT)0);
    (void) GetClipboardDataAlloc((UINT)0);
    (void) GetClipboardFormatName((UINT)0, (LPTSTR)0, (int)0);
    (void) GetClipboardOwner();
    (void) GetOpenClipboardWindow();
    (void) GetPriorityClipboardFormat((UINT*)0, (int)0);
    (void) IsClipboardFormatAvailable((UINT)0);
    (void) OpenClipboard((HWND)0);
    (void) RegisterClipboardFormat((LPCWSTR)0);
    (void) SetClipboardData((UINT)0, (HANDLE)0);
    /* Resources: icons/images/modules */
    (void) CreateIconIndirect((PICONINFO)0);
    (void) DestroyIcon((HICON)0);
    (void) DrawIconEx((HDC)0, (int)0, (int)0, (HICON)0, (int)0, (int)0,
                      (UINT)0, (HBRUSH)0, (UINT)0);
    (void) GetIconInfo((HICON)0, (PICONINFO)0);
    (void) LoadIcon((HINSTANCE)0, (LPCTSTR)0);
    (void) LoadImage((HINSTANCE)0, (LPCTSTR)0, (UINT)0, (int)0, (int)0,
                     (UINT)0);
    (void) FindResource((HMODULE)0, (LPCWSTR)0, (LPCWSTR)0);
    (void) LoadResource((HMODULE)0, (HRSRC)0);
    (void) LockResource((HGLOBAL)0);
    (void) SizeofResource((HMODULE)0, (HRSRC)0);
    (void) ExtractIconEx((LPCTSTR)0, (int)0, (HICON*)0, (HICON*)0, (UINT)0);
    /* Printing */
    (void) AbortDoc((HDC)0);
    (void) EndDoc((HDC)0);
    (void) EndPage((HDC)0);
    (void) SetAbortProc((HDC)0, (ABORTPROC)0);
    (void) StartDoc((HDC)0, (CONST DOCINFO*)0);
    (void) StartPage((HDC)0);
    /* System information */
    (void) EnableHardwareKeyboard((BOOL)0);
    (void) GetSysColor((int)0);
    (void) GetSystemMetrics((int)0);
    (void) SystemParametersInfo((UINT)0, (UINT)0, (PVOID)0, (UINT)0);
    (void) SetSysColors((int)0, (CONST INT*)0, (CONST COLORREF*)0);
    (void) GetSystemPowerStatusEx((PSYSTEM_POWER_STATUS_EX)0, (BOOL)0);
    (void) GetSystemPowerStatusEx2((PSYSTEM_POWER_STATUS_EX2)0, (DWORD)0,
                                   (BOOL)0);
    /* Notifications (notify.h) */
    (void) CeClearUserNotification((HANDLE)0);
    (void) CeGetUserNotification((HANDLE)0, (DWORD)0, (LPDWORD)0, (LPBYTE)0);
    (void) CeGetUserNotificationHandles((HANDLE*)0, (DWORD)0, (LPDWORD)0);
    (void) CeGetUserNotificationPreferences((HWND)0, (PCE_USER_NOTIFICATION)0);
    (void) CeHandleAppNotifications((TCHAR*)0);
    (void) CeRunAppAtEvent((TCHAR*)0, (LONG)0);
    (void) CeRunAppAtTime((TCHAR*)0, (SYSTEMTIME*)0);
    (void) CeSetUserNotification((HANDLE)0, (TCHAR*)0, (SYSTEMTIME*)0,
                                 (PCE_USER_NOTIFICATION)0);
    (void) CeSetUserNotificationEx((HANDLE)0, (CE_NOTIFICATION_TRIGGER*)0,
                                   (CE_USER_NOTIFICATION*)0);

    /* Pointer-free layouts (verified on every host). */
    if (sizeof(DLGITEMTEMPLATE) != 20 || sizeof(DLGTEMPLATE) != 20
        || sizeof(TPMPARAMS) != 20 || sizeof(MEASUREITEMSTRUCT) != 24
        || sizeof(DELETEITEMSTRUCT) != 20
        || sizeof(SYSTEM_POWER_STATUS_EX) != 24
        || sizeof(SYSTEM_POWER_STATUS_EX2) != 56)
        return 1;
#if __SIZEOF_POINTER__ == 4
    if (sizeof(MENUITEMINFO) != 44
        || offsetof(MENUITEMINFO, dwTypeData) != 36
        || sizeof(ICONINFO) != 20 || sizeof(COMBOBOXINFO) != 52
        || sizeof(DOCINFO) != 20
        || sizeof(CE_NOTIFICATION_TRIGGER) != 52
        || sizeof(CE_USER_NOTIFICATION) != 24
        || sizeof(CE_NOTIFICATION_INFO_HEADER) != 16)
        return 1;
#endif
    return 0;
}

/* M29: Image List API + message/ROP constants -- typed calls and
 * pointer-free layout checks; representative constant spot-checks. */
static int m29_shaped_usage(void)
{
    HIMAGELIST himl = (HIMAGELIST)0;
    (void) himl;
    (void) ImageList_Add(himl, (HBITMAP)0, (HBITMAP)0);
    (void) ImageList_AddMasked(himl, (HBITMAP)0, (COLORREF)0);
    (void) ImageList_BeginDrag(himl, (int)0, (int)0, (int)0);
    (void) ImageList_Copy(himl, (int)0, himl, (int)0, (UINT)0);
    (void) ImageList_Create((int)0, (int)0, ILC_COLOR8 | ILC_MASK, (int)0, (int)0);
    (void) ImageList_Destroy(himl);
    (void) ImageList_DragEnter((HWND)0, (int)0, (int)0);
    (void) ImageList_DragLeave((HWND)0);
    (void) ImageList_DragMove((int)0, (int)0);
    (void) ImageList_DragShowNolock((BOOL)0);
    (void) ImageList_Draw(himl, (int)0, (HDC)0, (int)0, (int)0, ILD_NORMAL);
    (void) ImageList_DrawEx(himl, (int)0, (HDC)0, (int)0, (int)0, (int)0,
                            (int)0, CLR_NONE, CLR_DEFAULT, ILD_TRANSPARENT);
    (void) ImageList_DrawIndirect((IMAGELISTDRAWPARAMS*)0);
    (void) ImageList_Duplicate(himl);
    (void) ImageList_EndDrag();
    (void) ImageList_GetBkColor(himl);
    (void) ImageList_GetDragImage((POINT*)0, (POINT*)0);
    (void) ImageList_GetIcon(himl, (int)0, (UINT)0);
    (void) ImageList_GetIconSize(himl, (int*)0, (int*)0);
    (void) ImageList_GetImageCount(himl);
    (void) ImageList_GetImageInfo(himl, (int)0, (IMAGEINFO*)0);
    (void) ImageList_LoadImage((HINSTANCE)0, (LPCSTR)0, (int)0, (int)0,
                               (COLORREF)0, IMAGE_BITMAP, (UINT)0);
    (void) ImageList_Merge(himl, (int)0, himl, (int)0, (int)0, (int)0);
    (void) ImageList_Remove(himl, (int)0);
    (void) ImageList_RemoveAll(himl);
    (void) ImageList_Replace(himl, (int)0, (HBITMAP)0, (HBITMAP)0);
    (void) ImageList_ReplaceIcon(himl, (int)0, (HICON)0);
    (void) ImageList_SetBkColor(himl, (COLORREF)0);
    (void) ImageList_SetDragCursorImage(himl, (int)0, (int)0, (int)0);
    (void) ImageList_SetIconSize(himl, (int)0, (int)0);
    (void) ImageList_SetImageCount(himl, (UINT)0);
    (void) ImageList_SetOverlayImage(himl, (int)0, (int)0);
    (void) ImageList_AddIcon(himl, (HICON)0);
    (void) ImageList_LoadBitmap((HINSTANCE)0, (LPCSTR)0, (int)0, (int)0,
                                (COLORREF)0);
    (void) ImageList_ExtractIcon((HINSTANCE)0, himl, (int)0);
    /* Message identifiers + notification codes (spot checks + one
     * expression spanning the control-notification space). */
    if (!(WM_USER == 0x0400 && WM_CREATE == 0x0001 && WM_COMMAND == 0x0111
          && WM_KEYDOWN == 0x0100 && WM_CHAR == 0x0102
          && WM_DESTROY == 0x0002 && WM_QUIT == 0x0012
          && WM_CTLCOLORBTN == 0x0135 && WM_CTLCOLORSTATIC == 0x0138
          && WM_CTLCOLOREDIT == 0x0133 && WM_CTLCOLORLISTBOX == 0x0134
          && BM_CLICK == 0x00F5 && STM_SETIMAGE == 0x0172
          && DM_GETDEFID == 0x0400 && DM_SETDEFID == 0x0401
          && CB_ADDSTRING == 0x0143 && LB_ADDSTRING == 0x0180
          && EM_GETSEL == 0x00B0 && WM_UNDO == 0x0304
          && WM_PAINT == 0x000F && WM_SETREDRAW == 0x000B
          && WM_SYSCOLORCHANGE == 0x0015 && WM_QUERYNEWPALETTE == 0x030F
          && WM_PALETTECHANGED == 0x0311 && WM_CUT == 0x0300
          && WM_RENDERALLFORMATS == 0x0306 && WM_GETDLGCODE == 0x0087
          && WM_NEXTDLGCTL == 0x0028 && WM_MENUCHAR == 0x0120
          && WM_SYSCOMMAND == 0x0112 && WM_HOTKEY == 0x0312
          && WM_INITMENUPOPUP == 0x0117 && WM_CONTEXTMENU == 0x007B))
        return 1;
    if (!(SRCCOPY == 0x00CC0020L && SRCPAINT == 0x00EE0086L
          && SRCAND == 0x008800C6L && SRCINVERT == 0x00660046L
          && NOTSRCCOPY == 0x00330008L && PATCOPY == 0x00F00021L
          && PATPAINT == 0x00FB0A09L && DSTINVERT == 0x00550009L
          && BLACKNESS == 0x00000042L && WHITENESS == 0x00FF0062L
          && MERGECOPY == 0x00C000CAL && MERGEPAINT == 0x00BB0226L
          && NOTSRCERASE == 0x001100A6L && SRCERASE == 0x00440328L
          && PATINVERT == 0x005A0049L && R2_BLACK == 1 && R2_COPYPEN == 13
          && R2_XORPEN == 7 && R2_NOT == 6 && R2_NOP == 11 && R2_WHITE == 16))
        return 1;
    if (!(IMAGE_BITMAP == 0 && IMAGE_ICON == 1 && IMAGE_CURSOR == 2))
        return 1;
#if __SIZEOF_POINTER__ == 4
    /* IMAGEINFO (ms909781): 2 handles + 2 ints + RECT = 32 bytes on the
     * 32-bit CE ABI; IMAGELISTDRAWPARAMS (ms909819) = 56 bytes. */
    _Static_assert(sizeof(IMAGEINFO) == 32, "IMAGEINFO 32-bit size");
    _Static_assert(sizeof(IMAGELISTDRAWPARAMS) == 56,
                   "IMAGELISTDRAWPARAMS 32-bit size");
#endif
    return 0;
}

int host_tu_entry(void)
{
    (void) api_symbols;
    (void) api_flags;
    (void) LocalAlloc(LPTR, 16u);
    if (m26_shaped_usage() != 0)
        return 1;
    if (ce_shaped_usage() != 0)
        return 1;
    if (sync_shaped_usage() != 0)
        return 1;
    if (m10_shaped_usage() != 0)
        return 1;
    if (m11_shaped_usage() != 0)
        return 1;
    if (m12_shaped_usage() != 0)
        return 1;
    if (m13_shaped_usage() != 0)
        return 1;
    if (m14_shaped_usage() != 0)
        return 1;
    if (m15_shaped_usage() != 0)
        return 1;
    if (m16_shaped_usage() != 0)
        return 1;
    if (m17_shaped_usage() != 0)
        return 1;
    if (m18_shaped_usage() != 0)
        return 1;
    if (m19_shaped_usage() != 0)
        return 1;
    if (m20_shaped_usage() != 0)
        return 1;
    if (m20b_shaped_usage() != 0)
        return 1;
    if (m21_shaped_usage() != 0)
        return 1;
    if (m22_shaped_usage() != 0)
        return 1;
    if (m23_shaped_usage() != 0)
        return 1;
    if (m24_shaped_usage() != 0)
        return 1;
    if (m25_shaped_usage() != 0)
        return 1;
    if (m27_shaped_usage() != 0)
        return 1;
    if (m28_shaped_usage() != 0)
        return 1;
    if (m29_shaped_usage() != 0)
        return 1;
    return 0;
}
