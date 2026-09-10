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

#include <Windows.h>
#include <Tlhelp32.h>
#include <Psapi.h>
#include <Msgqueue.h>
#include <Excpt.h>
#include <Dbgapi.h>
#include <ErrorRep.h>
#include <Celog.h>
#include <Natedit.h>
#include <Commctrl.h>
#include <Winsock2.h>
#include <Wininet.h>
#include <Wininetui.h>
#include <Urlmonui.h>
#include <Ws2tcpip.h>
#include <Ws2spi.h>
#include <Tapi.h>
#include <Tapicomn.h>
#include <Imm.h>
#include <Wincrypt.h>
#include <Winscard.h>
#include <Objbase.h>
#include <Mq.h>
#include <Upnpdevapi.h>
#include <Upnp.h>
#include <Upnphost.h>
#include <Obex.h>
#include <p2p.h>
#include <Service.h>
#include <Smbconfig.h>
#include <Webproxy.h>
#include <Httpfilt.h>
#include <Httpext.h>
#include <Ras.h>
#include <Iphlpapi.h>
#include <Icmpapi.h>
#include <Winnetwk.h>
#include <Windns.h>
#include <Dsgetdc.h>
#include <Autodial.h>
#include <Fwapi.h>
#include <Rules.h>
#include <Ipsec_api.h>
#include <Raseapif.h>
#include <Routprot.h>
#include <Ndis.h>
#include <Ntddndis.h>
#include <Ndistapi.h>
#include <Rndis.h>
#include <Rndismini.h>
#include <Nuiouser.h>
#include <Wzcsapi.h>
#include <Externs.h>
#include <Windot11.h>
#include <Usp10.h>
#include <Cesync.h>
#include <Dvdata.h>
#include <Dvdnav.h>
#include <Msime.h>
#include <Msimeui.h>
#include <Imjpskin.h>
#include <Mspyime.h>
#include <Recog.h>
#include <DwCeDump.h>
#include <Pkfuncs.h>
#include <sideshow.h>
#include <Voiplap.h>
#include <Voiperrorcodes.h>
#include <Storemgr.h>
#include <Extfile.h>
#include <Fsdmgr.h>
#include <Partdrv.h>
#include <Lockmgrtypes.h>
#include <Lockmgrhelp.h>
#include <Lockmgr.h>
#include <aygshell.h>
#include <shellsdk.h>
#include <newmenu.h>
#include <Shlobj.h>
#include <Extfile.h>
#include <Sipapi.h>
#include <Sip.h>
#include <Keybd.h>
#include <Pwinuser.h>
#include <Shtypes.h>
#include <Shobjidl.h>
#include <Shellapi.h>
#include <Cpl.h>
#include <Shelwapi.h>
#include <Windowsx.h>
#include <Commdlg.h>
#include <Winldap.h>
#include <Winber.h>
#include <Cchannel.h>
#include <Discodlg.h>
#include <Prsht.h>
#include <Bthsdpdef.h>
#include <Bt_api.h>
#include <Ws2bth.h>
#include <Bthapi.h>
#include <Btagpub.h>
#include <Btagnetwork.h>
#include <Snmp.h>
#include <Snmpapi.h>
#include <Snmpexts.h>
#include <pm.h>
#include <CEDDK.h>
#include <dvddrvr.h>
#include <dvdcss.h>
#include <Ddraw.h>
#include <Dvp.h>
#include <Urlmon.h>
#include <Mlang.h>
#include <Mmsystem.h>
#include <Imaging.h>
#include <Pimstore.h>
#include <Msxml2.h>
#include <D3dm.h>
#include <Sapi.h>
#include <Rtccore.h>
#include <Rtccore.h>
#include <Windbase.h>
#include <Windbase.h>
#include <Pwindbas.h>
#include <Dshow.h>
#include <dvdmedia.h>
#include <Dmo.h>
#include <Dmoreg.h>
#include <strmif.h>
#include <Playlist.h>
#include <Dmodshow.h>
#include <Shobjvidl.h>
#include <Oleauto.h>
#include <Oaidl.h>
#include <stddef.h>
/* M69a: documented-case include aliases (docs print these spellings). */
#include <Commctrl.h>
#include <Windows.h>
#include <Winbase.h>
#include <Mmsystem.h>
#include <Imaging.h>
#include <Pimstore.h>
#include <Msxml2.h>
#include <D3dm.h>
#include <D3dmtypes.h>
#include <Sapi.h>
#include <Sapiddk.h>
#include <Sphelper.h>
#include <Tlhelp32.h>
#include <aygshell.h>
#include <Kfuncs.h>

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
    (const void *) &CopyFileExW,
    (const void *) &CopyFileEx,
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
    /* M30: remaining Winbase.h/Windows.h documented functions. */
    (const void *) &FreeLibraryAndExitThread, (const void *) &CeZeroPointer,
    (const void *) &CeGetThreadQuantum, (const void *) &CeSetThreadQuantum,
    (const void *) &VerQueryValueW, (const void *) &IsProcessorFeaturePresent,
    (const void *) &QueryInstructionSet, (const void *) &SetUserDefaultLCID,
    /* M31: cross-process read / thread context / charset translation /
     * version-resource helpers. */
    (const void *) &ReadProcessMemory, (const void *) &GetThreadContext,
    (const void *) &TranslateCharsetInfo,
    /* M32: NLS formatting / locale-info (winnls.h; Coreloc.lib). */
    (const void *) &GetCurrencyFormatW, (const void *) &GetNumberFormatW,
    (const void *) &GetDateFormatW, (const void *) &GetTimeFormatW,
    (const void *) &GetLocaleInfoW, (const void *) &SetLocaleInfoW,
    /* M34: NLS string mapping / code-page enumeration (Coreloc.lib) +
     * directory-service user-name query (Coredll.lib). */
    (const void *) &FoldStringW, (const void *) &LCMapStringW,
    (const void *) &EnumSystemCodePagesW, (const void *) &GetUserNameExW,
    /* M36: Fonts-and-text (wingdi.h) and MultiMonitor functions. */
    (const void *) &AddFontResourceW, (const void *) &CreateFontIndirectW,
    (const void *) &DrawTextW, (const void *) &EnumFontFamiliesW,
    (const void *) &EnumFontFamiliesExW, (const void *) &EnumFontsW,
    (const void *) &ExtTextOutW, (const void *) &GetCharABCWidthsW,
    (const void *) &GetCharWidth32W, (const void *) &GetFontData,
    (const void *) &GetTextAlign, (const void *) &GetTextCharacterExtra,
    (const void *) &GetTextColor, (const void *) &GetTextExtentExPointW,
    (const void *) &GetTextExtentPointW,
    (const void *) &GetTextExtentPoint32W, (const void *) &GetTextFaceW,
    (const void *) &GetTextMetricsW, (const void *) &RemoveFontResourceW,
    (const void *) &SetTextAlign, (const void *) &SetTextCharacterExtra,
    (const void *) &SetTextColor, (const void *) &EnumDisplayMonitors,
    (const void *) &GetMonitorInfo, (const void *) &MonitorFromPoint,
    (const void *) &MonitorFromRect, (const void *) &MonitorFromWindow,
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

/* CopyFileEx (winbase.h; CE 5.0+, aa517311 / ee490791): the
 * progress constants are the fixed Win32 ABI values, and the
 * documented LPPROGRESS_ROUTINE shape must accept a nine-argument
 * callback (official Win32 reference prototype; the CE page names
 * only the parameter type). */
static DWORD tu_progress_stub(LARGE_INTEGER TotalFileSize,
                              LARGE_INTEGER TotalBytesTransferred,
                              LARGE_INTEGER StreamSize,
                              LARGE_INTEGER StreamBytesTransferred,
                              DWORD dwStreamNumber,
                              DWORD dwCallbackReason,
                              HANDLE hSourceFile,
                              HANDLE hDestinationFile,
                              LPVOID lpData)
{
    (void)TotalFileSize; (void)TotalBytesTransferred;
    (void)StreamSize; (void)StreamBytesTransferred;
    (void)dwStreamNumber; (void)dwCallbackReason;
    (void)hSourceFile; (void)hDestinationFile; (void)lpData;
    return PROGRESS_CONTINUE;
}
typedef char assert_progress_vals[
    (PROGRESS_CONTINUE == 0 && PROGRESS_CANCEL == 1 &&
     PROGRESS_STOP == 2 &&
     COPY_FILE_FAIL_IF_EXISTS == 0x1u && COPY_FILE_RESTARTABLE == 0x2u &&
     COPY_FILE_ALLOW_DECRYPTED_DESTINATION == 0x8u) ? 1 : -1];
static LPPROGRESS_ROUTINE tu_progress_assign = tu_progress_stub;

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

/* M31 32-bit ABI layout checks (wingdi.h / winbase.h). */
#if __SIZEOF_POINTER__ == 4
_Static_assert(sizeof(FONTSIGNATURE) == 24, "FONTSIGNATURE 32-bit size");
_Static_assert(sizeof(CHARSETINFO) == 32, "CHARSETINFO 32-bit size");
_Static_assert(sizeof(VS_FIXEDFILEINFO) == 52, "VS_FIXEDFILEINFO 32-bit size");
_Static_assert(sizeof(CURRENCYFMT) == 32, "CURRENCYFMT 32-bit size");
_Static_assert(sizeof(NUMBERFMT) == 24, "NUMBERFMT 32-bit size");
/* aa450831 EXTENDED_NAME_FORMAT members (CE-specific value included). */
_Static_assert(NameUnknown == 0 && NameFullyQualifiedDN == 1 &&
               NameSamCompatible == 2 && NameDisplay == 3 &&
               NameUniqueId == 6 && NameCanonical == 7 &&
               NameUserPrincipal == 8 && NameCanonicalEx == 9 &&
               NameServicePrincipal == 10,
               "EXTENDED_NAME_FORMAT low members");
_Static_assert((unsigned) NameWindowsCeLocal == 0x80000001u,
               "EXTENDED_NAME_FORMAT NameWindowsCeLocal");
/* M35: GWES style bits -- composite/alias relations documented on the
 * CE pages, and ABI value pins against the header literals. */
_Static_assert(WS_CAPTION == (WS_BORDER | WS_DLGFRAME),
               "WS_CAPTION = WS_BORDER | WS_DLGFRAME");
_Static_assert(WS_EX_OVERLAPPEDWINDOW ==
               (WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE),
               "WS_EX_OVERLAPPEDWINDOW composite");
_Static_assert(LBS_STANDARD == (LBS_NOTIFY | LBS_SORT),
               "LBS_STANDARD composite");
_Static_assert(MB_ICONERROR == MB_ICONHAND && MB_ICONSTOP == MB_ICONHAND,
               "MB_ICONERROR/STOP alias MB_ICONHAND");
_Static_assert(MB_ICONWARNING == MB_ICONEXCLAMATION &&
               MB_ICONINFORMATION == MB_ICONASTERISK,
               "MB icon aliases");
_Static_assert(WS_CHILD == 0x40000000u && WS_POPUP == 0x80000000u,
               "WS_CHILD/WS_POPUP ABI");
_Static_assert(WS_VISIBLE == 0x10000000u && WS_DISABLED == 0x08000000u,
               "WS_VISIBLE/WS_DISABLED ABI");
_Static_assert((unsigned) WS_CAPTION == 0x00C00000u &&
               (unsigned) WS_BORDER == 0x00800000u,
               "WS_CAPTION/WS_BORDER ABI");
_Static_assert((unsigned) WS_SYSMENU == 0x00080000u &&
               (unsigned) WS_SIZEBOX == 0x00040000u &&
               WS_GROUP == 0x00020000u && WS_TABSTOP == 0x00010000u,
               "WS_* low ABI pins");
_Static_assert(BS_DEFPUSHBUTTON == 0x0001 && BS_CHECKBOX == 0x0002 &&
               BS_AUTOCHECKBOX == 0x0003 && BS_RADIOBUTTON == 0x0004,
               "BS_* low ABI pins");
_Static_assert(BS_3STATE == 0x0005 && BS_AUTO3STATE == 0x0006 &&
               BS_AUTORADIOBUTTON == 0x0009 && BS_OWNERDRAW == 0x000B,
               "BS_* low ABI pins 2");
_Static_assert(BS_RIGHTBUTTON == 0x0020 && BS_LEFT == 0x0100 &&
               BS_RIGHT == 0x0200 && BS_CENTER == 0x0300,
               "BS_* alignment ABI");
_Static_assert(BS_TOP == 0x0400 && BS_BOTTOM == 0x0800 &&
               BS_VCENTER == 0x0C00 && BS_PUSHLIKE == 0x1000 &&
               BS_NOTIFY == 0x4000,
               "BS_* layout ABI");
_Static_assert(ES_MULTILINE == 0x0004 && ES_PASSWORD == 0x0020 &&
               ES_AUTOVSCROLL == 0x0040 && ES_AUTOHSCROLL == 0x0080 &&
               ES_READONLY == 0x0800 && ES_WANTRETURN == 0x1000 &&
               ES_NUMBER == 0x2000,
               "ES_* ABI pins");
_Static_assert(LBS_NOTIFY == 0x0001 && LBS_SORT == 0x0002 &&
               LBS_MULTIPLESEL == 0x0008 && LBS_HASSTRINGS == 0x0040 &&
               LBS_EXTENDEDSEL == 0x0800 && LBS_DISABLENOSCROLL == 0x1000 &&
               LBS_NOSEL == 0x4000,
               "LBS_* ABI pins");
_Static_assert(CBS_DROPDOWN == 0x0002 && CBS_DROPDOWNLIST == 0x0003 &&
               CBS_SORT == 0x0100 && CBS_HASSTRINGS == 0x0200 &&
               CBS_NOINTEGRALHEIGHT == 0x0400 &&
               CBS_DISABLENOSCROLL == 0x0800 && CBS_UPPERCASE == 0x2000 &&
               CBS_LOWERCASE == 0x4000,
               "CBS_* ABI pins");
_Static_assert(SBS_HORZ == 0x0000 && SBS_VERT == 0x0001,
               "SBS_* ABI pins");
_Static_assert(SS_ICON == 0x0003 && SS_LEFTNOWORDWRAP == 0x000C &&
               SS_BITMAP == 0x000E && SS_NOPREFIX == 0x0080 &&
               SS_NOTIFY == 0x0100 && SS_CENTERIMAGE == 0x0200,
               "SS_* ABI pins");
_Static_assert(DS_ABSALIGN == 0x0001 && DS_SYSMODAL == 0x0002 &&
               DS_3DLOOK == 0x0004 && DS_FIXEDSYS == 0x0008 &&
               DS_NOFAILCREATE == 0x0010 && DS_LOCALEDIT == 0x0020 &&
               DS_SETFONT == 0x0040 && DS_MODALFRAME == 0x0080,
               "DS_* ABI pins");
_Static_assert(DS_NOIDLEMSG == 0x0100 && DS_SETFOREGROUND == 0x0200 &&
               DS_CONTROL == 0x0400 && DS_CENTER == 0x0800 &&
               DS_CENTERMOUSE == 0x1000 && DS_CONTEXTHELP == 0x2000,
               "DS_* ABI pins 2");
_Static_assert(WS_EX_DLGMODALFRAME == 0x00000001 &&
               WS_EX_TOPMOST == 0x00000008 &&
               WS_EX_WINDOWEDGE == 0x00000100 &&
               WS_EX_CLIENTEDGE == 0x00000200 &&
               WS_EX_CONTEXTHELP == 0x00000400 &&
               (unsigned) WS_EX_STATICEDGE == 0x00020000u,
               "WS_EX_* ABI pins");
_Static_assert(MB_OK == 0x0000 && MB_OKCANCEL == 0x0001 &&
               MB_ABORTRETRYIGNORE == 0x0002 && MB_YESNOCANCEL == 0x0003 &&
               MB_YESNO == 0x0004 && MB_RETRYCANCEL == 0x0005,
               "MB_* button ABI pins");
_Static_assert(MB_ICONHAND == 0x0010 && MB_ICONQUESTION == 0x0020 &&
               MB_ICONEXCLAMATION == 0x0030 && MB_ICONASTERISK == 0x0040 &&
               MB_DEFBUTTON2 == 0x0100 && MB_DEFBUTTON3 == 0x0200,
               "MB_* icon/default ABI pins");
_Static_assert(sizeof(COPYDATASTRUCT) == 12, "COPYDATASTRUCT 32-bit size");
#endif

/* M36: Fonts-and-text and MultiMonitor ABI pins.
 *
 * Layout checks: the structures below contain no pointers, so their
 * sizes are pointer-width independent.  The member transcriptions come
 * from the CE pages cited in wingdi.h (LOGFONT ms901140, TEXTMETRIC
 * ms901146, ENUMLOGFONT ms901128, NEWTEXTMETRIC ms901141, ABC ms901108,
 * MONITORINFO ms932213) -- 11 LONGs then 4 glyph chars/BCHARs, the
 * BYTE attribute block, and for NEWTEXTMETRIC the four DWORD/UINT
 * extensions. */
_Static_assert(sizeof(TEXTMETRIC) == 56, "TEXTMETRIC size");
_Static_assert(sizeof(LOGFONT) == 92, "LOGFONT size");
_Static_assert(offsetof(LOGFONT, lfFaceName) == 28,
               "LOGFONT lfFaceName offset");
_Static_assert(offsetof(LOGFONT, lfCharSet) == 23,
               "LOGFONT lfCharSet offset");
_Static_assert(sizeof(ENUMLOGFONT) == 284, "ENUMLOGFONT size");
_Static_assert(offsetof(ENUMLOGFONT, elfFullName) == 92,
               "ENUMLOGFONT elfFullName offset");
_Static_assert(sizeof(NEWTEXTMETRIC) == 76, "NEWTEXTMETRIC size");
_Static_assert(offsetof(NEWTEXTMETRIC, ntmFlags) == 60,
               "NEWTEXTMETRIC ntmFlags offset");
_Static_assert(sizeof(ABC) == 12, "ABC size");
_Static_assert(sizeof(MONITORINFO) == 40, "MONITORINFO size");
_Static_assert(offsetof(MONITORINFO, rcMonitor) == 4 &&
               offsetof(MONITORINFO, dwFlags) == 36,
               "MONITORINFO member offsets");

/* Value pins (fixed Win32 ABI values, per repo policy; the CE pages
 * publish the names, meanings and bit-field layouts documented in
 * wingdi.h). */
_Static_assert(LF_FACESIZE == 32 && LF_FULLFACESIZE == 64,
               "LF_FACESIZE / LF_FULLFACESIZE");
_Static_assert(RASTER_FONTTYPE == 1 && DEVICE_FONTTYPE == 2 &&
               TRUETYPE_FONTTYPE == 4, "font-type constants");
_Static_assert(DT_TOP == 0 && DT_LEFT == 0 && DT_CENTER == 1 &&
               DT_RIGHT == 2 && DT_VCENTER == 4 && DT_BOTTOM == 8 &&
               DT_WORDBREAK == 0x10 && DT_SINGLELINE == 0x20 &&
               DT_EXPANDTABS == 0x40 && DT_TABSTOP == 0x80 &&
               DT_NOCLIP == 0x100 && DT_EXTERNALLEADING == 0x200 &&
               DT_CALCRECT == 0x400 && DT_NOPREFIX == 0x800 &&
               DT_INTERNAL == 0x1000 && DT_END_ELLIPSIS == 0x8000 &&
               DT_RTLREADING == 0x20000 && DT_WORD_ELLIPSIS == 0x40000,
               "DT_* fixed ABI values");
_Static_assert(ETO_OPAQUE == 2 && ETO_CLIPPED == 4 &&
               ETO_RTLREADING == 0x80, "ETO_* fixed ABI values");
_Static_assert(TA_NOUPDATECP == 0 && TA_LEFT == 0 && TA_UPDATECP == 1 &&
               TA_RIGHT == 2 && TA_CENTER == 6 && TA_TOP == 0 &&
               TA_BOTTOM == 8 && TA_BASELINE == 0x18 &&
               TA_RTLREADING == 0x100, "TA_* fixed ABI values");
_Static_assert(MONITOR_DEFAULTTONULL == 0 &&
               MONITOR_DEFAULTTOPRIMARY == 1 &&
               MONITOR_DEFAULTTONEAREST == 2 && MONITORINFOF_PRIMARY == 1,
               "monitor flag values");


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

/* M39: Winsock (Winsock 2.2) 32-bit CE layouts transcribed from the
 * official CE 5.0 pages (docs/inventory-m39-ws2.md).  sockaddr and
 * sockaddr_in are both 16 bytes (the page documents sin_zero as
 * "Padding to make structure the same size as SOCKADDR"); WSADATA
 * embeds szDescription[257] + szSystemStatus[129] and the trailing
 * pointer is 4-byte aligned (flagged WSASYS_STATUS_LEN, see
 * winsock2.h); fd_set is the CE counted-array layout;
 * WSAPROTOCOL_INFO carries the 32-byte WSAPROTOCOLCHAIN (flagged
 * MAX_PROTOCOL_CHAIN = 7) and the 256 TCHAR szProtocol member. */
#if __SIZEOF_POINTER__ == 4
typedef char assert_sockaddr_size[(sizeof(struct sockaddr) == 16) ? 1 : -1];
typedef char assert_sockaddr_data[(offsetof(struct sockaddr, sa_data) == 2) ? 1 : -1];
typedef char assert_in_addr_size[(sizeof(struct in_addr) == 4) ? 1 : -1];
typedef char assert_sockaddr_in_size[(sizeof(struct sockaddr_in) == 16) ? 1 : -1];
typedef char assert_sockaddr_in_zero[(offsetof(struct sockaddr_in, sin_zero) == 8) ? 1 : -1];
typedef char assert_in6_addr_size[(sizeof(struct in6_addr) == 16) ? 1 : -1];
typedef char assert_sockaddr_in6_size[(sizeof(struct sockaddr_in6) == 28) ? 1 : -1];
typedef char assert_linger_size[(sizeof(struct linger) == 4) ? 1 : -1];
typedef char assert_hostent_size[(sizeof(struct hostent) == 16) ? 1 : -1];
typedef char assert_servent_size[(sizeof(struct servent) == 16) ? 1 : -1];
typedef char assert_protoent_size[(sizeof(struct protoent) == 12) ? 1 : -1];
typedef char assert_timeval_size[(sizeof(struct timeval) == 8) ? 1 : -1];
typedef char assert_fd_set_size[(sizeof(fd_set) == 4 + 4 * FD_SETSIZE) ? 1 : -1];
typedef char assert_fd_set_array[(offsetof(fd_set, fd_array) == 4) ? 1 : -1];
typedef char assert_wsadata_size[(sizeof(WSADATA) == 400) ? 1 : -1];
typedef char assert_wsabuf_size[(sizeof(WSABUF) == 8) ? 1 : -1];
typedef char assert_wsaoverlapped_size[(sizeof(WSAOVERLAPPED) == 20) ? 1 : -1];
typedef char assert_afprotocols_size[(sizeof(AFPROTOCOLS) == 8) ? 1 : -1];
typedef char assert_protocol_info_size[(sizeof(PROTOCOL_INFO) == 32) ? 1 : -1];
typedef char assert_wsaprotocolchain_size[(sizeof(WSAPROTOCOLCHAIN) == 4 + 4 * MAX_PROTOCOL_CHAIN) ? 1 : -1];
typedef char assert_wsaprotocol_info_size[(sizeof(WSAPROTOCOL_INFO) == 628) ? 1 : -1];
typedef char assert_wsaprotocol_chain_at[(offsetof(WSAPROTOCOL_INFO, ProtocolChain) == 40) ? 1 : -1];
typedef char assert_socket_address_size[(sizeof(SOCKET_ADDRESS) == 8) ? 1 : -1];
typedef char assert_wsanetworkevents_size[(sizeof(WSANETWORKEVENTS) == 4 + 4 * FD_MAX_EVENTS) ? 1 : -1];
typedef char assert_transmit_file_size[(sizeof(TRANSMIT_FILE_BUFFERS) == 16) ? 1 : -1];
typedef char assert_addrinfo_size[(sizeof(struct addrinfo) == 32) ? 1 : -1];
#endif

/* M39: documented constant values (official sources in winsock2.h). */
typedef char assert_ws2_constants[
    (AF_UNSPEC == 0 && AF_INET == 2 && AF_INET6 == 23) ? 1 : -1];
typedef char assert_ws2_socket[
    (SOCK_STREAM == 1 && SOCK_DGRAM == 2 && SOCK_RAW == 3) ? 1 : -1];
typedef char assert_ws2_ipproto[
    (IPPROTO_IP == 0 && IPPROTO_TCP == 6 && IPPROTO_UDP == 17 &&
     IPPROTO_IPV6 == 41) ? 1 : -1];
typedef char assert_ws2_sd[
    (SD_RECEIVE == 0 && SD_SEND == 1 && SD_BOTH == 2) ? 1 : -1];
typedef char assert_ws2_ai[
    (AI_PASSIVE == 0x01 && AI_CANONNAME == 0x02 &&
     AI_NUMERICHOST == 0x04) ? 1 : -1];
typedef char assert_ws2_flags[
    (WSA_FLAG_OVERLAPPED == 0x01 && WSA_FLAG_MULTIPOINT_C_ROOT == 0x02 &&
     WSA_FLAG_MULTIPOINT_C_LEAF == 0x04 && WSA_FLAG_MULTIPOINT_D_ROOT == 0x08 &&
     WSA_FLAG_MULTIPOINT_D_LEAF == 0x10 &&
     WSA_FLAG_ACCESS_SYSTEM_SECURITY == 0x40 &&
     WSA_FLAG_NO_HANDLE_INHERIT == 0x80 &&
     SG_UNCONSTRAINED_GROUP == 0x01 && SG_CONSTRAINED_GROUP == 0x02) ? 1 : -1];
typedef char assert_ws2_so[
    (SO_KEEPALIVE == 0x0008 && SO_CONDITIONAL_ACCEPT == 0x3002) ? 1 : -1];
typedef char assert_ws2_len[
    (WSADESCRIPTION_LEN == 256 && WSAPROTOCOL_LEN == 255 &&
     FD_SETSIZE == 64 && WSASYS_STATUS_LEN == 128 &&
     FD_MAX_EVENTS == 16 && MAX_PROTOCOL_CHAIN == 7) ? 1 : -1];
typedef char assert_ws2_err[
    (WSABASEERR == 10000 && WSAEWOULDBLOCK == 10035 &&
     WSAEINPROGRESS == 10036 && WSAEALREADY == 10037 &&
     WSAENOTSOCK == 10038 && WSAEDESTADDRREQ == 10039 &&
     WSAEMSGSIZE == 10040 && WSAEPROTOTYPE == 10041 &&
     WSAENOPROTOOPT == 10042 && WSAEPROTONOSUPPORT == 10043 &&
     WSAESOCKTNOSUPPORT == 10044 && WSAEOPNOTSUPP == 10045 &&
     WSAEPFNOSUPPORT == 10046 && WSAEAFNOSUPPORT == 10047 &&
     WSAEADDRINUSE == 10048 && WSAEADDRNOTAVAIL == 10049 &&
     WSAENETDOWN == 10050 && WSAENETUNREACH == 10051 &&
     WSAENETRESET == 10052 && WSAECONNABORTED == 10053 &&
     WSAECONNRESET == 10054 && WSAENOBUFS == 10055 && WSAEISCONN == 10056 &&
     WSAENOTCONN == 10057 && WSAESHUTDOWN == 10058 &&
     WSAETIMEDOUT == 10060 && WSAECONNREFUSED == 10061 &&
     WSAEHOSTUNREACH == 10065 && WSAEPROCLIM == 10067 &&
     WSASYSNOTREADY == 10091 && WSAVERNOTSUPPORTED == 10092 &&
     WSANOTINITIALISED == 10093 && WSAEDISCON == 10101 &&
     WSAENOMORE == 10102 && WSAECANCELLED == 10103 &&
     WSAHOST_NOT_FOUND == 11001 && WSATRY_AGAIN == 11002 &&
     WSANO_RECOVERY == 11003 && WSANO_DATA == 11004) ? 1 : -1];
typedef char assert_ws2_win32err[
    (WSA_INVALID_HANDLE == 6 && WSA_NOT_ENOUGH_MEMORY == 8 &&
     WSA_INVALID_PARAMETER == 87 && WSA_OPERATION_ABORTED == 995 &&
     WSA_IO_INCOMPLETE == 996 && WSA_IO_PENDING == 997) ? 1 : -1];
typedef char assert_ws2_invalid[(INVALID_SOCKET == (SOCKET)(~0u)) ? 1 : -1];
typedef char assert_ws2_version[
    (WSAVersion(2, 2) == MAKEWORD(2, 2) && WSAVersion(2, 2) == 0x0202) ? 1 : -1];

static int m39_condfunc(LPWSABUF lpCallerId, LPWSABUF lpCallerData,
                        LPQOS lpSQOS, LPQOS lpGQOS,
                        LPWSABUF lpCalleeId, LPWSABUF lpCalleeData,
                        GROUP *g, DWORD dwCallbackData)
{
    (void) lpCallerId; (void) lpCallerData; (void) lpSQOS;
    (void) lpGQOS; (void) lpCalleeId; (void) lpCalleeData;
    (void) g; (void) dwCallbackData;
    return 0;
}

static void m39_completion(DWORD dwError, DWORD cbTransferred,
                           LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
{
    (void) dwError; (void) cbTransferred;
    (void) lpOverlapped; (void) dwFlags;
}

static int m39_shaped_usage(void)
{
    SOCKET s;
    int v;
    int err;
    WORD ver = WSAVersion(2, 2);
    WSADATA data = {0};
    struct sockaddr sa = {0};
    struct sockaddr_in sa4 = {0};
    struct sockaddr_in6 sa6 = {0};
    struct in_addr iaddr = {0};
    struct linger linger;
    struct hostent *he;
    struct servent *se;
    struct protoent *pe;
    struct timeval tv = {0};
    fd_set rset, wset;
    WSABUF buf;
    WSAOVERLAPPED ov = {0};
    WSAEVENT ev;
    LPWSANETWORKEVENTS nev;
    struct addrinfo *ai;
    TRANSMIT_FILE_BUFFERS tfb;
    SOCKET_ADDRESS sad;
    AFPROTOCOLS afp;
    PROTOCOL_INFO pi;
    WSAPROTOCOL_INFO wpi;
    WSAPROTOCOLCHAIN pc;

    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET)
        return 1;
    (void) closesocket(s);
    (void) bind(s, (struct sockaddr *)&sa4, sizeof(sa4));
    (void) connect(s, (struct sockaddr *)&sa4, sizeof(sa4));
    (void) listen(s, 16);
    (void) accept(s, &sa, (int *)&v);
    (void) getsockname(s, &sa, (int *)&v);
    (void) getpeername(s, &sa, (int *)&v);
    (void) recv(s, (char *)0, 0, 0);
    (void) send(s, (const char *)0, 0, 0);
    (void) recvfrom(s, (char *)0, 0, 0, &sa, (int *)&v);
    (void) sendto(s, (const char *)0, 0, 0, &sa, 0);
    FD_ZERO(&rset);
    FD_ZERO(&wset);
    FD_SET(s, &rset);
    (void) FD_ISSET(s, &rset);
    FD_SET(s, &rset);               /* duplicate: not added */
    FD_CLR(s, &rset);
    (void) select(0, &rset, &wset, (fd_set *)0, &tv);
    v = 1;
    (void) setsockopt(s, 0, SO_KEEPALIVE, (const char *)&v, sizeof v);
    (void) getsockopt(s, 0, SO_KEEPALIVE, (char *)&v, (int *)&v);
    (void) shutdown(s, SD_BOTH);
    (void) ioctlsocket(s, 0, (u_long *)&v);
    (void) gethostname((char *)0, 0);
    (void) sethostname((char *)0, 0);
    (void) htonl((u_long)0);
    (void) htons((u_short)0);
    (void) ntohl((u_long)0);
    (void) ntohs((u_short)0);
    (void) inet_addr("0.0.0.0");
    (void) inet_ntoa(iaddr);
    he = gethostbyname((const char *)0);
    if (he)
        (void) he->h_name;
    (void) gethostbyaddr((const char *)0, 0, 0);
    /* in_addr S_un union access (documented layout). */
    iaddr.S_un.S_addr = htonl((u_long)0x7f000001);
    (void) iaddr.S_un.S_un_b.s_b4;
    (void) iaddr.S_un.S_un_w.s_w1;
    sa4.sin_family = AF_INET;
    sa4.sin_port = htons((u_short)0);
    sa4.sin_addr = iaddr;
    sa6.sin6_family = AF_INET6;
    sa6.sin6_port = htons((u_short)0);
    sa6.sin6_flowinfo = 0;
    sa6.sin6_scope_id = 0;
    (void) sa6.sin6_addr.u.Word[0];
    (void) sa6.sin6_addr.u.Byte[0];
    sa.sa_family = AF_UNSPEC;
    (void) sa.sa_data[0];
    linger.l_onoff = 0;
    linger.l_linger = 0;
    (void) linger;
    se = (struct servent *)0;
    pe = (struct protoent *)0;
    (void) se; (void) pe;
    tv.tv_sec = 0;
    tv.tv_usec = 0;

    err = WSAStartup(ver, &data);
    if (err != 0)
        return 1;
    (void) WSACleanup();
    (void) WSAGetLastError();
    WSASetLastError(WSAEWOULDBLOCK);
    ev = WSACreateEvent();
    (void) WSASetEvent(ev);
    (void) WSAResetEvent(ev);
    (void) WSACloseEvent(ev);
    (void) WSAEventSelect(s, ev, 0);
    (void) WSAWaitForMultipleEvents(0, (const WSAEVENT *)0, FALSE, 0, FALSE);
    nev = (LPWSANETWORKEVENTS)0;
    (void) WSAEnumNetworkEvents(s, ev, nev);
    (void) WSAEnumProtocols((LPINT)0, (LPWSAPROTOCOL_INFO)0, (LPDWORD)0);
    (void) WSAGetOverlappedResult(s, &ov, (LPDWORD)0, TRUE, (LPDWORD)0);
    (void) WSAHtonl(s, 0, (u_long *)0);
    (void) WSAHtons(s, 0, (u_short *)0);
    (void) WSANtohl(s, 0, (u_long *)0);
    (void) WSANtohs(s, 0, (u_short *)0);
    (void) WSAIoctl(s, 0, (LPVOID)0, 0, (LPVOID)0, 0, (LPDWORD)0, &ov,
                    (LPWSAOVERLAPPED_COMPLETION_ROUTINE)0);
    (void) WSAAccept(s, &sa, (int *)&v,
                     (LPCONDITIONPROC)m39_condfunc, 0);
    (void) WSAConnect(s, (const struct sockaddr *)0, 0, (LPWSABUF)0,
                      (LPWSABUF)0, (LPQOS)0, (LPQOS)0);
    (void) WSAJoinLeaf(s, (const struct sockaddr *)0, 0, (LPWSABUF)0,
                       (LPWSABUF)0, (LPQOS)0, (LPQOS)0, 0);
    buf.len = 0;
    buf.buf = (char *)0;
    (void) WSARecv(s, &buf, 1, (LPDWORD)0, (LPDWORD)0, &ov,
                   (LPWSAOVERLAPPED_COMPLETION_ROUTINE)m39_completion);
    (void) WSARecvFrom(s, &buf, 1, (LPDWORD)0, (LPDWORD)0, &sa,
                       (LPINT)0, &ov, (LPWSAOVERLAPPED_COMPLETION_ROUTINE)0);
    (void) WSASend(s, &buf, 1, (LPDWORD)0, 0, &ov,
                   (LPWSAOVERLAPPED_COMPLETION_ROUTINE)0);
    (void) WSASendTo(s, &buf, 1, (LPDWORD)0, 0, (const struct sockaddr *)0,
                     0, &ov, (LPWSAOVERLAPPED_COMPLETION_ROUTINE)0);
    (void) WSASocket(AF_UNSPEC, SOCK_STREAM, 0, (LPWSAPROTOCOL_INFO)0,
                     (GROUP)0, WSA_FLAG_OVERLAPPED);
    (void) WSAAddressToString((LPSOCKADDR)&sa4, sizeof(sa4),
                              (LPWSAPROTOCOL_INFO)0, (LPTSTR)0, (LPDWORD)0);
    (void) WSAStringToAddress((LPTSTR)0, AF_INET,
                              (LPWSAPROTOCOL_INFO)0, (LPSOCKADDR)0,
                              (LPINT)0);

    /* getaddrinfo surface (Ws2tcpip.h, Ws2.lib, CE .NET 4.1+). */
    (void) getaddrinfo((const char *)0, (const char *)0,
                       (const struct addrinfo *)0, &ai);
    if (ai)
        freeaddrinfo(ai);
    (void) getnameinfo((const struct sockaddr *)&sa4,
                       (socklen_t)sizeof(sa4), (char *)0, 0,
                       (char *)0, 0, 0);

    /* structure members exercised for layout. */
    tfb.Head = (PVOID)0; tfb.HeadLength = 0;
    tfb.Tail = (PVOID)0; tfb.TailLength = 0;
    (void) tfb;
    sad.lpSockaddr = (LPSOCKADDR)&sa;
    sad.iSockaddrLength = sizeof(sa);
    (void) sad;
    afp.iAddressFamily = AF_INET;
    afp.iProtocol = IPPROTO_UDP;
    (void) afp;
    pi.dwServiceFlags = 0;
    pi.iAddressFamily = AF_INET;
    pi.iMaxSockAddr = 0; pi.iMinSockAddr = 0;
    pi.iSocketType = SOCK_STREAM; pi.iProtocol = IPPROTO_TCP;
    pi.dwMessageSize = 0;
    pi.lpProtocol = (LPTSTR)0;
    (void) pi;
    pc.ChainLen = 0;
    pc.ChainEntries[0] = 0;
    (void) pc;
    wpi.dwServiceFlags1 = 0; wpi.dwServiceFlags2 = 0;
    wpi.dwServiceFlags3 = 0; wpi.dwServiceFlags4 = 0;
    wpi.dwProviderFlags = 0;
    wpi.dwCatalogEntryId = 0;
    wpi.ProtocolChain = pc;
    wpi.iVersion = 0; wpi.iAddressFamily = 0; wpi.iMaxSockAddr = 0;
    wpi.iMinSockAddr = 0; wpi.iSocketType = 0; wpi.iProtocol = 0;
    wpi.iProtocolMaxOffset = 0; wpi.iNetworkByteOrder = 0;
    wpi.iSecurityScheme = 0; wpi.dwMessageSize = 0;
    wpi.dwProviderReserved = 0;
    wpi.szProtocol[0] = (TCHAR)0;
    (void) wpi;
    data.wVersion = 0; data.wHighVersion = 0;
    data.iMaxSockets = 0; data.iMaxUdpDg = 0;
    data.lpVendorInfo = (char *)0;
    (void) data;
    (void) v; (void) s;
    return 0;
}

/* M41: Winsock name-service (name space) types, per the official CE
 * pages (WSAECOMPARATOR ms898736, BLOB aa450302, CSADDR_INFO
 * ms887919, WSAQUERYSET ms898762, WSANAMESPACE_INFO ms898753,
 * WSASERVICECLASSINFO ms898768, SERVICE_* aa450894/aa450895/
 * aa450902/aa450910/aa450912, NS_SERVICE_INFO ms895775). */
_Static_assert(COMP_EQUAL == 0 && COMP_NOTLESS == 1,
               "WSAECOMPARATOR documented ordinals");
#if __SIZEOF_POINTER__ == 4
_Static_assert(sizeof(BLOB) == 8, "BLOB 32-bit size");
_Static_assert(sizeof(WSAECOMPARATOR) == 4, "WSAECOMPARATOR 32-bit size");
_Static_assert(sizeof(WSAESETSERVICEOP) == 4, "WSAESETSERVICEOP 32-bit size");
_Static_assert(sizeof(CSADDR_INFO) == 24, "CSADDR_INFO 32-bit size");
_Static_assert(sizeof(WSAQUERYSET) == 60, "WSAQUERYSET 32-bit size");
_Static_assert(sizeof(WSANAMESPACE_INFO) == 32, "WSANAMESPACE_INFO 32-bit size");
_Static_assert(sizeof(WSASERVICECLASSINFO) == 16,
               "WSASERVICECLASSINFO 32-bit size");
_Static_assert(sizeof(SERVICE_ADDRESS) == 24, "SERVICE_ADDRESS 32-bit size");
_Static_assert(sizeof(SERVICE_ADDRESSES) == 28,
               "SERVICE_ADDRESSES 32-bit size");
_Static_assert(sizeof(SERVICE_INFO) == 44, "SERVICE_INFO 32-bit size");
_Static_assert(sizeof(NS_SERVICE_INFO) == 48, "NS_SERVICE_INFO 32-bit size");
_Static_assert(sizeof(SERVICE_TYPE_VALUE_ABS) == 20,
               "SERVICE_TYPE_VALUE_ABS 32-bit size");
_Static_assert(sizeof(SERVICE_TYPE_INFO_ABS) == 28,
               "SERVICE_TYPE_INFO_ABS 32-bit size");
#endif

static int m41_shaped_usage(void)
{
    DWORD blen = 0;
    HANDLE hLookup = (HANDLE)0;
    WSANAMESPACE_INFO nsi = {0};
    WSAQUERYSET qs = {0};
    CSADDR_INFO csi = {0};
    BLOB blob = {0};
    WSAVERSION *pver = (WSAVERSION *)0;
    WSANSCLASSINFOW *pcls = (WSANSCLASSINFOW *)0;
    WSAESETSERVICEOP op = RNRSERVICE_DEREGISTER;
    INT r;

    (void) WSAEnumNameSpaceProviders(&blen, &nsi);
    qs.dwSize = sizeof(qs);
    qs.lpszServiceInstanceName = (LPTSTR)0;
    qs.lpServiceClassId = (LPGUID)0;
    qs.lpVersion = pver;
    qs.dwNameSpace = 0;
    qs.lpNSProviderId = (LPGUID)0;
    qs.dwNumberOfProtocols = 0;
    qs.lpafpProtocols = (LPAFPROTOCOLS)0;
    qs.dwNumberOfCsAddrs = 1;
    qs.lpcsaBuffer = &csi;
    qs.lpBlob = &blob;
    blob.cbSize = 0;
    blob.pBlobData = (BYTE *)0;
    csi.LocalAddr.lpSockaddr = (LPSOCKADDR)0;
    csi.LocalAddr.iSockaddrLength = 0;
    csi.RemoteAddr.lpSockaddr = (LPSOCKADDR)0;
    csi.RemoteAddr.iSockaddrLength = 0;
    csi.iSocketType = 0;
    csi.iProtocol = 0;
    r = WSALookupServiceBegin(&qs, 0, &hLookup);
    (void) WSALookupServiceNext(hLookup, 0, &blen, &qs);
    (void) WSALookupServiceEnd(hLookup);
    (void) WSASetService(&qs, op, 0);
    (void) pcls;
    (void) r;
    return 0;
}

/* M42: Winsock SPI (Ws2spi.h) types, per the official CE 5.0
 * "Winsock SPI Reference" pages (WSPDATA ms900586, WSATHREADID
 * ms898776, NSP_Routine ms895763). */
#if __SIZEOF_POINTER__ == 4
_Static_assert(sizeof(WSPDATA) == 518, "WSPDATA 32-bit size");
_Static_assert(sizeof(WSATHREADID) == 8, "WSATHREADID 32-bit size");
_Static_assert(sizeof(NSP_ROUTINE) == 44, "NSP_ROUTINE 32-bit size");
#endif

static int m42_shaped_usage(void)
{
    INT err = 0;
    DWORD len = 0;
    WORD ver = WSAVersion(2, 2);
    WSPDATA wsd = {0};
    WSATHREADID tid = {0};
    NSP_ROUTINE nsp = {0};
    LPWSAPROTOCOL_INFOW pinfo = (LPWSAPROTOCOL_INFOW)0;
    LPWSAQUERYSETW pqs = (LPWSAQUERYSETW)0;
    LPWSPDATAW pw = &wsd;
    LPWSPPROC_TABLE procs = (LPWSPPROC_TABLE)0;
    const WSPUPCALLTABLE *upcalls = (const WSPUPCALLTABLE *)0;
    HANDLE hLookup = (HANDLE)0;
    GUID guid = {0};

    wsd.wVersion = ver;
    wsd.wHighVersion = ver;
    (void) WSPStartup(ver, pw, pinfo, upcalls, procs);
    (void) WSPAccept((SOCKET)0, (struct sockaddr *)0, &err, (LPCONDITIONPROC)0, 0, &err);
    (void) WSPAddressToString((LPSOCKADDR)0, 0, pinfo, (LPWSTR)0, &len, &err);
    (void) WSPAsyncSelect((SOCKET)0, (HWND)0, 0, 0, &err);
    (void) WSPBind((SOCKET)0, (const struct sockaddr *)0, 0, &err);
    (void) WSPCleanup(&err);
    (void) WSPCloseSocket((SOCKET)0, &err);
    (void) WSPConnect((SOCKET)0, (const struct sockaddr *)0, 0, (LPWSABUF)0,
                      (LPWSABUF)0, (LPQOS)0, (LPQOS)0, &err);
    (void) WSPDuplicateSocket((SOCKET)0, 0, pinfo, &err);
    (void) WSPEnumNetworkEvents((SOCKET)0, (WSAEVENT)0, (LPWSANETWORKEVENTS)0, &err);
    (void) WSPEventSelect((SOCKET)0, (WSAEVENT)0, 0, &err);
    (void) WSPGetOverlappedResult((SOCKET)0, (LPWSAOVERLAPPED)0, &len, FALSE,
                                  (LPDWORD)0, &err);
    (void) WSPGetPeerName((SOCKET)0, (struct sockaddr *)0, &err, &err);
    (void) WSPGetSockName((SOCKET)0, (struct sockaddr *)0, &err, &err);
    (void) WSPGetSockOpt((SOCKET)0, 0, 0, (char *)0, &err, &err);
    (void) WSPIoctl((SOCKET)0, 0, (LPVOID)0, 0, (LPVOID)0, 0, (LPDWORD)0,
                    (LPWSAOVERLAPPED)0, (LPWSAOVERLAPPED_COMPLETION_ROUTINE)0,
                    &tid, &err);
    (void) WSPJoinLeaf((SOCKET)0, (const struct sockaddr *)0, 0, (LPWSABUF)0,
                       (LPWSABUF)0, (LPQOS)0, (LPQOS)0, 0, &err);
    (void) WSPListen((SOCKET)0, 0, &err);
    (void) WSPRecv((SOCKET)0, (LPWSABUF)0, 0, (LPDWORD)0, (LPDWORD)0,
                   (LPWSAOVERLAPPED)0, (LPWSAOVERLAPPED_COMPLETION_ROUTINE)0,
                   &tid, &err);
    (void) WSPRecvDisconnect((SOCKET)0, (LPWSABUF)0, &err);
    (void) WSPRecvFrom((SOCKET)0, (LPWSABUF)0, 0, (LPDWORD)0, (LPDWORD)0,
                       (struct sockaddr *)0, &err, (LPWSAOVERLAPPED)0,
                       (LPWSAOVERLAPPED_COMPLETION_ROUTINE)0, &tid, &err);
    (void) WSPSelect(0, (fd_set *)0, (fd_set *)0, (fd_set *)0,
                     (const struct timeval *)0, &err);
    (void) WSPSend((SOCKET)0, (LPWSABUF)0, 0, (LPDWORD)0, 0,
                   (LPWSAOVERLAPPED)0, (LPWSAOVERLAPPED_COMPLETION_ROUTINE)0,
                   &tid, &err);
    (void) WSPSendDisconnect((SOCKET)0, (LPWSABUF)0, &err);
    (void) WSPSendTo((SOCKET)0, (LPWSABUF)0, 0, (LPDWORD)0, 0,
                     (const struct sockaddr *)0, 0, (LPWSAOVERLAPPED)0,
                     (LPWSAOVERLAPPED_COMPLETION_ROUTINE)0, &tid, &err);
    (void) WSPSetSockOpt((SOCKET)0, 0, 0, (const char *)0, 0, &err);
    (void) WSPShutdown((SOCKET)0, 0, &err);
    (void) WSPSocket(0, 0, 0, pinfo, (GROUP)0, 0, &err);
    (void) WSPStringToAddress((LPWSTR)0, 0, pinfo, (LPSOCKADDR)0, &err, &err);
    (void) NSPCleanup(&guid);
    (void) NSPGetServiceClassInfo(&guid, &len, (LPWSASERVICECLASSINFOW)0);
    (void) NSPInstallServiceClass(&guid, (LPWSASERVICECLASSINFOW)0);
    (void) NSPLookupServiceBegin(&guid, pqs, (LPWSASERVICECLASSINFOW)0, 0,
                                 &hLookup);
    (void) NSPLookupServiceEnd(hLookup);
    (void) NSPLookupServiceNext(hLookup, 0, &len, (LPWSAQUERYSET)0);
    (void) NSPRemoveServiceClass(&guid, &guid);
    (void) NSPSetService(&guid, (LPWSASERVICECLASSINFOW)0, pqs,
                         RNRSERVICE_REGISTER, 0);
    nsp.cbSize = sizeof(nsp);
    (void) nsp;
    (void) tid;
    (void) wsd;
    (void) err;
    return 0;
}

/* ------------------------------------------------------------------ */
/* M43: TAPI/TSPI -- tapi.h (types/structs/callbacks/constants) +     */
/*      tapicomn.h (the TSPI service-provider entry points; 78 in     */
/*      M43, 79 since the M45 TSPI_lineForward closure).              */
/* ------------------------------------------------------------------ */

#if __SIZEOF_POINTER__ == 4
_Static_assert(sizeof(LINEDIALPARAMS) == 16, "LINEDIALPARAMS 32-bit size");
_Static_assert(sizeof(LINEEXTENSIONID) == 16, "LINEEXTENSIONID 32-bit size");
_Static_assert(sizeof(PHONEEXTENSIONID) == 16, "PHONEEXTENSIONID 32-bit size");
_Static_assert(sizeof(LINEGENERATETONE) == 16, "LINEGENERATETONE 32-bit size");
_Static_assert(sizeof(LINECALLTREATMENTENTRY) == 12, "LINECALLTREATMENTENTRY 32-bit size");
_Static_assert(sizeof(LINECALLLIST) == 24, "LINECALLLIST 32-bit size");
_Static_assert(sizeof(LINEPROVIDERENTRY) == 12, "LINEPROVIDERENTRY 32-bit size");
_Static_assert(sizeof(LINEPROVIDERLIST) == 24, "LINEPROVIDERLIST 32-bit size");
_Static_assert(sizeof(LINEMESSAGE) == 24, "LINEMESSAGE 32-bit size");
_Static_assert(sizeof(PHONEMESSAGE) == 24, "PHONEMESSAGE 32-bit size");
_Static_assert(sizeof(VARSTRING) == 24, "VARSTRING 32-bit size");
_Static_assert(sizeof(LINEINITIALIZEEXPARAMS) == 24, "LINEINITIALIZEEXPARAMS 32-bit size");
_Static_assert(sizeof(PHONEINITIALIZEEXPARAMS) == 24, "PHONEINITIALIZEEXPARAMS 32-bit size");
_Static_assert(sizeof(LINEADDRESSSTATUS) == 64, "LINEADDRESSSTATUS 32-bit size");
_Static_assert(sizeof(LINECALLSTATUS) == 56, "LINECALLSTATUS 32-bit size");
_Static_assert(sizeof(LINECALLPARAMS) == 180, "LINECALLPARAMS 32-bit size");
_Static_assert(sizeof(LINELOCATIONENTRY) == 68, "LINELOCATIONENTRY 32-bit size");
_Static_assert(sizeof(LINETRANSLATECAPS) == 44, "LINETRANSLATECAPS 32-bit size");
_Static_assert(sizeof(LINETRANSLATEOUTPUT) == 40, "LINETRANSLATEOUTPUT 32-bit size");
_Static_assert(sizeof(LINECALLINFO) == 296, "LINECALLINFO 32-bit size");
_Static_assert(sizeof(LINEADDRESSCAPS) == 228, "LINEADDRESSCAPS 32-bit size");
_Static_assert(sizeof(LINEDEVSTATUS) == 76, "LINEDEVSTATUS 32-bit size");
_Static_assert(sizeof(LINEDEVCAPS) == 252, "LINEDEVCAPS 32-bit size");
_Static_assert(sizeof(PHONECAPS) == 180, "PHONECAPS 32-bit size");
_Static_assert(sizeof(PHONESTATUS) == 104, "PHONESTATUS 32-bit size");
#endif

static void m43_line_event(HTAPILINE htLine, HTAPICALL htCall, DWORD dwMsg,
                           DWORD dwParam1, DWORD dwParam2, DWORD dwParam3)
{ (void) htLine; (void) htCall; (void) dwMsg; (void) dwParam1;
  (void) dwParam2; (void) dwParam3; }

static void m43_phone_event(HTAPIPHONE htPhone, DWORD dwMsg, DWORD dwParam1,
                            DWORD dwParam2, DWORD dwParam3)
{ (void) htPhone; (void) dwMsg; (void) dwParam1; (void) dwParam2;
  (void) dwParam3; }

static void m43_async_completion(DRV_REQUESTID dwRequestID, LONG lResult)
{ (void) dwRequestID; (void) lResult; }

/* M44: COM/OLE/Storage/Automation (objbase.h).  32-bit sizes of the
 * documented structures; the CE toolchain is the arbiter. */
#if __SIZEOF_POINTER__ == 4
typedef char m44_size_guid[sizeof(GUID) == 16 ? 1 : -1];
typedef char m44_size_clsid[sizeof(CLSID) == 16 ? 1 : -1];
typedef char m44_size_iid[sizeof(IID) == 16 ? 1 : -1];
typedef char m44_size_cy[sizeof(CY) == 8 ? 1 : -1];
typedef char m44_size_currency[sizeof(CURRENCY) == 8 ? 1 : -1];
typedef char m44_size_variant[sizeof(VARIANT) == 16 ? 1 : -1];
typedef char m44_size_variantarg[sizeof(VARIANTARG) == 16 ? 1 : -1];
typedef char m44_size_safearraybound[sizeof(SAFEARRAYBOUND) == 8 ? 1 : -1];
typedef char m44_size_safearray[sizeof(SAFEARRAY) == 24 ? 1 : -1];
typedef char m44_size_dispparams[sizeof(DISPPARAMS) == 16 ? 1 : -1];
typedef char m44_size_excepinfo[sizeof(EXCEPINFO) == 32 ? 1 : -1];
typedef char m44_size_paramdata[sizeof(PARAMDATA) == 8 ? 1 : -1];
typedef char m44_size_methoddata[sizeof(METHODDATA) == 28 ? 1 : -1];
typedef char m44_size_tlibattr[sizeof(TLIBATTR) == 32 ? 1 : -1];
typedef char m44_size_typedescl[sizeof(TYPEDESC) == 8 ? 1 : -1];
typedef char m44_size_arraydesc[sizeof(ARRAYDESC) == 20 ? 1 : -1];
typedef char m44_size_idldesc[sizeof(IDLDESC) == 8 ? 1 : -1];
typedef char m44_size_paramdesc[sizeof(PARAMDESC) == 8 ? 1 : -1];
typedef char m44_size_elemdesc[sizeof(ELEMDESC) == 16 ? 1 : -1];
typedef char m44_size_funcdesc[sizeof(FUNCDESC) == 52 ? 1 : -1];
typedef char m44_size_vardesc[sizeof(VARDESC) == 36 ? 1 : -1];
typedef char m44_size_interfaceinfo[sizeof(INTERFACEINFO) == 24 ? 1 : -1];
typedef char m44_size_bindptr[sizeof(BINDPTR) == 4 ? 1 : -1];
typedef char m44_size_typeattr[sizeof(TYPEATTR) == 76 ? 1 : -1];
typedef char m44_size_custdataitem[sizeof(CUSTDATAITEM) == 32 ? 1 : -1];
typedef char m44_size_custdata[sizeof(CUSTDATA) == 8 ? 1 : -1];
typedef char m44_size_coauthidentity[sizeof(COAUTHIDENTITY) == 28 ? 1 : -1];
typedef char m44_size_coauthinfo[sizeof(COAUTHINFO) == 28 ? 1 : -1];
typedef char m44_size_coserverinfo[sizeof(COSERVERINFO) == 16 ? 1 : -1];
typedef char m44_size_sole_auth[sizeof(SOLE_AUTHENTICATION_SERVICE) == 16 ? 1 : -1];
typedef char m44_size_multi_qi[sizeof(MULTI_QI) == 12 ? 1 : -1];
typedef char m44_size_dvtargetdevice[sizeof(DVTARGETDEVICE) == 16 ? 1 : -1];
typedef char m44_size_formatetc[sizeof(FORMATETC) == 20 ? 1 : -1];
typedef char m44_size_stgmedium[sizeof(STGMEDIUM) == 12 ? 1 : -1];
typedef char m44_size_statstg[sizeof(STATSTG) == 72 ? 1 : -1];
typedef char m44_size_bind_opts[sizeof(BIND_OPTS) == 16 ? 1 : -1];
typedef char m44_size_bind_opts2[sizeof(BIND_OPTS2) == 32 ? 1 : -1];
typedef char m44_size_bindinfo[sizeof(BINDINFO) == 84 ? 1 : -1];
typedef char m44_size_licinfo[sizeof(LICINFO) == 12 ? 1 : -1];
typedef char m44_size_connectdata[sizeof(CONNECTDATA) == 8 ? 1 : -1];
typedef char m44_size_controlinfo[sizeof(CONTROLINFO) == 16 ? 1 : -1];
typedef char m44_size_dvaspectinfo[sizeof(DVASPECTINFO) == 8 ? 1 : -1];
typedef char m44_size_dvextentinfo[sizeof(DVEXTENTINFO) == 16 ? 1 : -1];
typedef char m44_size_sizel[sizeof(SIZEL) == 8 ? 1 : -1];
typedef char m44_size_secattr[sizeof(SECURITY_ATTRIBUTES) == 12 ? 1 : -1];
typedef char m44_size_hresult[(sizeof(HRESULT) == sizeof(LONG)) ? 1 : -1];
typedef char m44_size_variantbool[(sizeof(VARIANT_BOOL) == 2) ? 1 : -1];
typedef char m44_size_date[(sizeof(DATE) == sizeof(double)) ? 1 : -1];
#endif

static int m44_shaped_usage(void)
{
    HRESULT    hr;
    GUID       clsid;
    GUID       iid;
    MULTI_QI   mq;
    BSTR       bstr;
    OLECHAR    sz[8];
    (void)sz;
    OLECHAR   *pwsz;
    VARIANT    var;
    VARIANTARG vararg;
    DISPPARAMS dispparams;
    EXCEPINFO  excepinfo;
    SAFEARRAYBOUND bound;
    SAFEARRAY  sa;
    SAFEARRAY *psa;
    CURRENCY   cy;
    DISPID     dispid;
    LCID       lcid;
    VARTYPE    vt;
    BOOL       b;
    ULONG      n;

    GUID class_id = {0x000C30C9, 0x0CD2, 0x4D62, {0xA0, 0x85, 0xC3, 0x48, 0xDB, 0x9A, 0x2F, 0xD1}};
    GUID int_id   = {0x00000001, 0x0000, 0x0000, {0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

    /* scalar forms */
    sz[0] = (OLECHAR)'t';
    static const WCHAR w_m44[] = { 't', 'e', 's', 't', 0 };
    pwsz = (LPOLESTR)w_m44;
    clsid = class_id;
    iid = int_id;
    {
        const OLECHAR *pcsz = (LPCOLESTR)pwsz;
        BSTR bb = (BSTR)pwsz;
        CLSID c2 = (CLSID)clsid;
        IID i2 = (IID)iid;
        const GUID *g2 = (REFGUID)&clsid;
        const IID *i3 = (REFIID)&iid;
        (void)pcsz; (void)bb; (void)c2; (void)i2; (void)g2; (void)i3;
    }
    cy.int64 = 123;
    cy.Lo = 1;
    {
        CURRENCY c3 = (CURRENCY)cy;
        (void)c3;
    }
    vt = VT_I4;
    if (!(vt == (VARTYPE)(VT_I4 | VT_ARRAY))) return 1;
    if (!(vt == (VARTYPE)(VT_BYREF | VT_R8))) return 1;
    dispid = 0;
    lcid = 0;
    b = 0;
    n = 0;

    /* VARIANT / VARIANTARG / DISPPARAMS / EXCEPINFO */
    hr = VariantInit(&vararg);
    var = vararg;
    var.vt = VT_BOOL;
    var.boolVal = 0;
    vararg.vt = VT_I4;
    vararg.lVal = 42;
    hr = VariantCopy(&vararg, &vararg);
    hr = VariantChangeTypeEx(&vararg, &var, lcid, 0, VT_I4);
    hr = VariantClear(&vararg);
    dispparams.rgvarg = &vararg;
    dispparams.rgdispidNamedArgs = &dispid;
    dispparams.cArgs = 1;
    dispparams.cNamedArgs = 0;
    excepinfo.wCode = 0;
    excepinfo.bstrSource = (BSTR)0;
    excepinfo.pvReserved = (void *)0;
    excepinfo.pfnDeferredFillIn = (HRESULT (STDAPICALLTYPE *)(struct _tagEXCEPINFO *))(0);
    excepinfo.scode = 0;
    (void)excepinfo;

    /* SAFEARRAY */
    bound.cElements = 4;
    bound.lLbound = 0;
    sa = (SAFEARRAY){0};
    sa.rgsabound[0] = bound;
    psa = &sa;
    hr = SafeArrayCreate(VT_I4, 1, &bound);
    hr = SafeArrayCreateVector(VT_UI1, 0, 4);
    hr = SafeArrayDestroy(psa);
    hr = SafeArrayAccessData(psa, (void **)0);
    hr = SafeArrayGetElement(psa, (long *)0, (void *)0);
    hr = SafeArrayPutElement(psa, (long *)0, (void *)0);
    hr = SafeArrayGetLBound(psa, 0, (long *)0);
    hr = SafeArrayGetUBound(psa, 0, (long *)0);
    hr = SafeArrayLock(psa);
    hr = SafeArrayUnlock(psa);
    hr = SafeArrayRedim(psa, &bound);
    n = SafeArrayGetDim(psa);
    n = SafeArrayGetElemsize(psa);
    if (!(n & (FADF_STATIC | FADF_FIXEDSIZE))) return 1;

    /* BSTR / string / date */
    bstr = SysAllocString(pwsz);
    hr = SysFreeString(bstr);
    hr = SysReAllocStringLen(&bstr, pwsz, 2);
    n = SysStringLen(bstr);
    n = SysStringByteLen(bstr);
    {
        SYSTEMTIME st;
        double vt2;
        n = SystemTimeToVariantTime(&st, &vt2);
        n = VariantTimeToSystemTime(vt2, &st);
    }
    hr = VarBoolFromI4(1, &b);
    hr = VarI4FromBool(b, (long *)0);
    hr = VarCyFromI4(1, (CURRENCY *)0);
    hr = VarR8FromI4(1, (double *)0);
    hr = VarDateFromI4(1, (DATE *)0);
    hr = VarBstrFromI4(1, lcid, 0, (BSTR)0);
    hr = VarUI2FromI4(1, (USHORT *)0);
    hr = VarUI4FromStr((OLECHAR *)0, lcid, 0, (ULONG *)0);
    hr = VarDecFromI4(1, (DECIMAL *)0);
    hr = VarR4FromI1(0, (float *)0);
    hr = VarR8FromDisp((IDispatch *)0, lcid, (double *)0);
    hr = VarI1FromI4(1, (char *)0);
    hr = VarUdateFromDate((DATE *)0, 0, (UDATE *)0);
    hr = VarParseNumFromStr((OLECHAR *)0, lcid, 0, (NUMPARSE *)0, (unsigned char *)0);
    hr = VarNumFromParseNum((NUMPARSE *)0, (unsigned char *)0, 0, (VARIANT *)0);
    hr = VectorFromBstr((BSTR)0, &psa);
    hr = BstrFromVector(psa, &bstr);

    /* type library forms */
    {
        TLIBATTR tlib;
        TYPEATTR typeattr;
        TYPEDESC td;
        ELEMDESC ed;
        FUNCDESC fd;
        VARDESC vd;
        ARRAYDESC ad;
        IDLDESC idl = {0, 0};
        PARAMDESC pd;
        INTERFACEINFO ii;
        CUSTDATA cd;
        CUSTDATAITEM cdi;
        METHODDATA md;
        PARAMDATA pdt;
        BINDPTR bp;
        tlib.syskind = SYS_WIN32;
        if (!(tlib.syskind == (SYSKIND)(SYS_WIN16 + 1))) return 1;
        typeattr.typekind = TKIND_ENUM;
        if (!(typeattr.typekind == (TYPEKIND)(TKIND_MAX - 1))) return 1;
        td.vt = VT_VARIANT;
        td.u.hreftype = 0;
        ed.tdesc = td;
        ed.u.idldesc = idl;
        (void)ed;
        fd.funckind = FUNC_STATIC;
        fd.invkind = INVOKE_FUNC;
        fd.callconv = CC_CDECL;
        if (!(fd.callconv == (CALLCONV)(CC_PASCAL))) return 1;
        vd.varkind = VAR_STATIC;
        if (!(vd.varkind == (VARKIND)(VAR_CONST))) return 1;
        ad.tdescElem = td;
        ad.rgbounds[0] = bound;
        idl.wIDLFlags = 0;
        pd.wParamFlags = 0;
        ii.iid = iid;
        cd.prgCustData = &cdi;
        cdi.varValue = vararg;
        md.cc = CC_STDCALL;
        md.vtReturn = VT_I4;
        pdt.vtReturn = VT_R8;
        bp.lptcomp = (ITypeComp *)0;
        (void)tlib; (void)typeattr; (void)td; (void)fd; (void)vd; (void)ad;
        (void)idl; (void)pd; (void)ii; (void)cd; (void)cdi; (void)md; (void)pdt; (void)bp;
    }

    /* OLE activation / moniker / storage forms */
    {
        COSERVERINFO coserver;
        COAUTHINFO coauth;
        COAUTHIDENTITY coauthid;
        SOLE_AUTHENTICATION_SERVICE solesvc;
        FORMATETC fmt;
        DVTARGETDEVICE dvt;
        STGMEDIUM medium;
        STATSTG statstg;
        BIND_OPTS bo;
        BIND_OPTS2 bo2;
        BINDINFO bi;
        LICINFO lic;
        CONNECTDATA cdd;
        CONTROLINFO cinfo;
        DVASPECTINFO dvi;
        DVEXTENTINFO dvi2;
        SIZEL szl;
        coserver.pwszName = pwsz;
        coauth.dwAuthnSvc = 0;
        coauth.pAuthIdentityData = &coauthid;
        coauthid.User = (USHORT *)0;
        solesvc.pPrincipalName = pwsz;
        solesvc.hr = 0;
        mq.pIID = &iid;
        mq.hr = 0;
        fmt.dwAspect = DVASPECT_CONTENT;
        fmt.tymed = TYMED_HGLOBAL;
        if (!(fmt.dwAspect == (DWORD)(DVASPECT_ICON | DVASPECT_DOCPRINT))) return 1;
        dvt.tdSize = 0;
        medium.tymed = TYMED_ISTREAM;
        medium.u.pstm = (IStream *)0;
        medium.pUnkForRelease = (IUnknown *)0;
        statstg.clsid = clsid;
        statstg.grfMode = STGM_READWRITE;
        if (!(statstg.grfMode == (DWORD)(STGM_CREATE | STGM_PRIORITY))) return 1;
        bo.grfMode = STGM_READ;
        bo2.dwClassContext = CLSCTX_INPROC_SERVER;
        if (!(bo2.dwClassContext == (DWORD)(CLSCTX_SERVER | CLSCTX_ALL))) return 1;
        bi.stgmedData = medium;
        bi.iid = iid;
        lic.cbLicInfo = 0;
        cdd.pUnk = (IUnknown *)0;
        cinfo.hAccel = (HACCEL)0;
        dvi.dwFlags = 0;
        dvi2.dwExtentMode = DVEXTENT_INTEGRAL;
        szl.cx = 0;
        szl.cy = 0;
        (void)coserver; (void)coauth; (void)coauthid; (void)solesvc; (void)mq;
        (void)fmt; (void)dvt; (void)medium; (void)statstg; (void)bo; (void)bo2;
        (void)bi; (void)lic; (void)cdd; (void)cinfo; (void)dvi; (void)dvi2; (void)szl;
    }

    /* free-function call shapes (Ole32 + Oleaut32) */
    hr = CoInitialize((LPVOID)0);
    hr = CoInitializeEx((LPVOID)0, 0);
    hr = CoCreateGuid(&clsid);
    hr = CoCreateInstance((REFCLSID)&clsid, (LPUNKNOWN)0, CLSCTX_INPROC_SERVER, (REFIID)&iid, (LPVOID)0);
    hr = CoCreateInstanceEx((REFCLSID)&clsid, (IUnknown *)0, CLSCTX_INPROC_SERVER, (COSERVERINFO *)0, 1, &mq);
    hr = CoGetClassObject((REFCLSID)&clsid, 0, (COSERVERINFO *)0, (REFIID)&iid, (LPVOID)0);
    hr = CoGetMalloc(0, (LPMALLOC *)0);
    CoTaskMemFree(CoTaskMemAlloc(4));
    CoUninitialize();
    hr = CoDisconnectObject((IUnknown *)0, 0);
    n = CoAddRefServerProcess();
    n = CoReleaseServerProcess();
    hr = CoGetCallContext((REFIID)&iid, (void **)0);
    hr = CoGetMarshalSizeMax(&n, (REFIID)&iid, (IUnknown *)0, 0, (LPVOID)0, 0);
    hr = CoMarshalInterface((IStream *)0, (REFIID)&iid, (IUnknown *)0, 0, (LPVOID)0, 0);
    hr = CoUnmarshalInterface((IStream *)0, (REFIID)&iid, (void **)0);
    hr = CoRevokeClassObject(0);
    hr = CoRegisterClassObject((REFCLSID)&clsid, (IUnknown *)0, CLSCTX_INPROC_SERVER, 0, (LPDWORD)0);
    hr = CLSIDFromString((LPOLESTR)0, (LPCLSID)0);
    hr = CLSIDFromProgID((LPCOLESTR)0, (LPCLSID)0);
    hr = ProgIDFromCLSID((REFCLSID)&clsid, (LPOLESTR *)0);
    hr = IIDFromString((LPOLESTR)0, (LPIID)0);
    n = StringFromGUID2((REFGUID)&clsid, (LPOLESTR)0, 0);
    hr = StringFromCLSID((REFCLSID)&clsid, (LPOLESTR *)0);
    hr = StringFromIID((REFIID)&iid, (LPOLESTR *)0);
    {
        LPMONIKER pmk = (LPMONIKER)0;
        LPMONIKER pmk2 = (LPMONIKER)0;
        LPBC pbc = (LPBC)0;
        hr = CreateBindCtx(0, &pbc);
        hr = CreateFileMoniker((LPCOLESTR)0, &pmk);
        hr = CreateItemMoniker((LPCOLESTR)0, (LPCOLESTR)0, &pmk);
        hr = CreatePointerMoniker((LPUNKNOWN)0, &pmk);
        hr = CreateClassMoniker((REFCLSID)&clsid, (IMoniker **)0);
        hr = CreateAntiMoniker(&pmk);
        hr = CreateGenericComposite(pmk, pmk2, &pmk);
        hr = MkParseDisplayName(pbc, (LPCOLESTR)0, &n, &pmk);
        hr = BindMoniker(pmk, 0, (REFIID)&iid, (LPVOID)0);
        hr = MonikerCommonPrefixWith(pmk, pmk2, &pmk2);
        hr = MonikerRelativePathTo(pmk, pmk2, &pmk2, 0);
        hr = GetRunningObjectTable(0, (LPRUNNINGOBJECTTABLE *)0);
        (void)(HRESULT (WINOLEAPI *)(const WCHAR *, IStorage *, DWORD, SNB, DWORD, IStorage **))StgOpenStorage;
        hr = StgCreateDocfile((const WCHAR *)0, STGM_READWRITE, 0, (IStorage **)0);
        (void)(HRESULT (WINOLEAPI *)(ILockBytes *, IStorage *, DWORD, SNB, DWORD, IStorage **))StgOpenStorageOnILockBytes;
        hr = StgCreateDocfileOnILockBytes((ILockBytes *)0, STGM_WRITE, 0, (IStorage **)0);
        hr = GetClassFile((LPCWSTR)0, (CLSID *)0);
        (void)pmk; (void)pmk2; (void)pbc;
    }
    hr = CreateErrorInfo((ICreateErrorInfo **)0);
    hr = GetErrorInfo(0, (IErrorInfo **)0);
    hr = SetErrorInfo(0, (IErrorInfo *)0);
    hr = DispGetIDsOfNames((ITypeInfo *)0, (OLECHAR **)0, 0, (DISPID *)0);
    hr = DispInvoke((LPVOID)0, (ITypeInfo *)0, dispid, 0, &dispparams, &var, &excepinfo, &n);
    hr = DispGetParam(&dispparams, 0, vt, &var, &n);
    hr = LoadTypeLib((OLECHAR *)0, (ITypeLib **)0);
    hr = LoadRegTypeLib((REFGUID)&clsid, 1, 0, lcid, (ITypeLib **)0);
    hr = RegisterTypeLib((ITypeLib *)0, (OLECHAR *)0, (OLECHAR *)0);
    hr = UnRegisterTypeLib((REFGUID)&clsid, 1, 0, lcid, SYS_WIN32);
    hr = CreateTypeLib2(SYS_WIN32, (LPOLESTR)0, (ICreateTypeLib2 **)0);

    (void)hr;
    return 0;
}

static int m43_shaped_usage(void)
{
    HDRVLINE   hdLine   = (HDRVLINE)0;
    HDRVCALL   hdCall   = (HDRVCALL)0;
    HDRVPHONE  hdPhone  = (HDRVPHONE)0;
    HTAPILINE  htLine   = (HTAPILINE)0;
    HTAPICALL  htCall   = (HTAPICALL)0;
    HTAPIPHONE htPhone  = (HTAPIPHONE)0;
    HPROVIDER  hProvider = (HPROVIDER)0;
    HKEY       hActive  = (HKEY)0;
    HWND       hwnd     = (HWND)0;
    HICON      hIcon    = (HICON)0;
    DWORD      dw       = 0;
    DWORD      dw2      = 0;

    LINEDIALPARAMS       dial    = {0};
    LINEEXTENSIONID      lext    = {0};
    PHONEEXTENSIONID     pext    = {0};
    LINEGENERATETONE     tone    = {0};
    LINECALLPARAMS       cparams = {0};
    LINECALLINFO         cinfo   = {0};
    LINECALLSTATUS       cstat   = {0};
    LINEADDRESSCAPS      acaps   = {0};
    LINEADDRESSSTATUS    astat   = {0};
    LINEDEVCAPS          dcaps   = {0};
    LINEDEVSTATUS        dstat   = {0};
    PHONECAPS            pcaps   = {0};
    PHONESTATUS          pstat   = {0};
    VARSTRING            vs      = {0};

    /* the provider entry points (8) */
    (void) TSPI_providerInit(0, 0, 0, 0, 0, 0,
                             m43_async_completion, &dw);
    (void) TSPI_providerEnumDevices(0, &dw, &dw2, hProvider,
                                    m43_line_event, m43_phone_event);
    (void) TSPI_providerCreateLineDevice(hActive, (LPCWSTR)0, (LPCWSTR)0);
    (void) TSPI_providerCreatePhoneDevice(hActive, (LPCWSTR)0, (LPCWSTR)0);
    (void) TSPI_providerInstall(hwnd, 0);
    (void) TSPI_providerRemove(hwnd, 0);
    (void) TSPI_providerRemoveDevice((LPCWSTR)0);
    (void) TSPI_providerShutdown(0, 0);

    /* line device TSPI (49) */
    (void) TSPI_lineOpen(0, htLine, &hdLine, 0, m43_line_event);
    (void) TSPI_lineNegotiateTSPIVersion(0, 0, 0, &dw);
    (void) TSPI_lineNegotiateExtVersion(0, 0, 0, 0, &dw2);
    (void) TSPI_lineGetDevCaps(0, 0, 0, &dcaps);
    (void) TSPI_lineGetAddressCaps(0, 0, 0, 0, &acaps);
    (void) TSPI_lineGetAddressStatus(hdLine, 0, &astat);
    (void) TSPI_lineGetAddressID(hdLine, &dw, 0, (LPCWSTR)0, 0);
    (void) TSPI_lineGetNumAddressIDs(hdLine, &dw);
    (void) TSPI_lineGetDevConfig(0, &vs, (LPCWSTR)0);
    (void) TSPI_lineSetDevConfig(0, (LPVOID)0, 0, (LPCWSTR)0);
    (void) TSPI_lineGetIcon(0, (LPCWSTR)0, &hIcon);
    (void) TSPI_lineGetExtensionID(0, 0, &lext);
    (void) TSPI_lineGetLineDevStatus(hdLine, &dstat);
    (void) TSPI_lineMakeCall(0, hdLine, htCall, &hdCall, (LPCWSTR)0, 0,
                             (LPLINECALLPARAMS)&cparams);
    (void) TSPI_lineDial(0, hdCall, (LPCWSTR)0, 0);
    (void) TSPI_lineAnswer(0, hdCall, (LPCSTR)0, 0);
    (void) TSPI_lineAccept(0, hdCall, (LPCSTR)0, 0);
    (void) TSPI_lineDrop(0, hdCall, (LPCSTR)0, 0);
    (void) TSPI_lineRedirect(0, hdCall, (LPCWSTR)0, 0);
    (void) TSPI_lineHold(0, hdCall);
    (void) TSPI_lineUnhold(0, hdCall);
    (void) TSPI_lineSwapHold(0, hdCall, (HDRVCALL)0);
    (void) TSPI_lineBlindTransfer(0, hdCall, (LPCWSTR)0, 0);
    (void) TSPI_lineSetupTransfer(0, hdCall, htCall, &hdCall,
                                  (LPLINECALLPARAMS)&cparams);
    (void) TSPI_lineCompleteTransfer(0, hdCall, (HDRVCALL)0, htCall,
                                     &hdCall, 0);
    (void) TSPI_lineSetupConference(0, hdCall, hdLine, htCall, &hdCall,
                                    htCall, &hdCall, 0,
                                    (LPLINECALLPARAMS)&cparams);
    (void) TSPI_lineAddToConference(0, hdCall, (HDRVCALL)0);
    (void) TSPI_lineRemoveFromConference(0, hdCall);
    (void) TSPI_lineGenerateDigits(hdCall, 0, 0, (LPCWSTR)0, 0);
    (void) TSPI_lineGenerateTone(hdCall, 0, 0, 0, 0,
                                 (LPLINEGENERATETONE)&tone);
    (void) TSPI_lineMonitorDigits(hdCall, 0);
    (void) TSPI_lineMonitorMedia(hdCall, 0);
    (void) TSPI_lineSetMediaMode(hdCall, 0);
    (void) TSPI_lineSetDefaultMediaDetection(hdLine, 0);
    (void) TSPI_lineSetStatusMessages(hdLine, 0, 0);
    (void) TSPI_lineSetCallParams(0, hdCall, 0, 0, 0,
                                  (LPLINEDIALPARAMS)&dial);
    (void) TSPI_lineGetCallInfo(hdCall, &cinfo);
    (void) TSPI_lineGetCallStatus(hdCall, &cstat);
    (void) TSPI_lineGetCallAddressID(hdCall, &dw);
    (void) TSPI_lineGetID(hdLine, 0, hdCall, 0, &vs, (LPCWSTR)0, (HANDLE)0);
    (void) TSPI_lineSendUserUserInfo(0, hdCall, (LPCSTR)0, 0);
    (void) TSPI_lineReleaseUserUserInfo(0, hdCall);
    (void) TSPI_lineDevSpecific(0, hdLine, 0, hdCall, (LPVOID)0, 0);
    (void) TSPI_lineClose(hdLine);
    (void) TSPI_lineCloseCall(hdCall);

    /* phone device TSPI (21) */
    (void) TSPI_phoneOpen(0, htPhone, &hdPhone, 0, m43_phone_event);
    (void) TSPI_phoneNegotiateTSPIVersion(0, 0, 0, &dw);
    (void) TSPI_phoneNegotiateExtVersion(0, 0, 0, 0, &dw2);
    (void) TSPI_phoneGetDevCaps(0, 0, 0, &pcaps);
    (void) TSPI_phoneGetStatus(hdPhone, &pstat);
    (void) TSPI_phoneGetGain(hdPhone, 0, &dw);
    (void) TSPI_phoneSetGain(0, hdPhone, 0, 0);
    (void) TSPI_phoneGetVolume(hdPhone, 0, &dw);
    (void) TSPI_phoneSetVolume(0, hdPhone, 0, 0);
    (void) TSPI_phoneGetHookSwitch(hdPhone, &dw);
    (void) TSPI_phoneSetHookSwitch(0, hdPhone, 0, 0);
    (void) TSPI_phoneGetRing(hdPhone, &dw, &dw2);
    (void) TSPI_phoneSetRing(0, hdPhone, 0, 0);
    (void) TSPI_phoneSetStatusMessages(hdPhone, 0, 0, 0);
    (void) TSPI_phoneGetIcon(0, (LPCWSTR)0, &hIcon);
    (void) TSPI_phoneGetID(hdPhone, &vs, (LPCWSTR)0, (HANDLE)0);
    (void) TSPI_phoneGetExtensionID(0, 0, &pext);
    (void) TSPI_phoneSelectExtVersion(hdPhone, 0);
    (void) TSPI_phoneConfigDialog(0, hwnd, (LPCWSTR)0);
    (void) TSPI_phoneDevSpecific(0, hdPhone, (LPVOID)0, 0);
    (void) TSPI_phoneClose(hdPhone);

    /* callback typedef shapes */
    LINEEVENT      le = m43_line_event;
    PHONEEVENT     pe = m43_phone_event;
    ASYNC_COMPLETION ac = m43_async_completion;
    (void) le; (void) pe; (void) ac;
    return 0;
}

/* ------------------------------------------------------------------ */
/* M45: TAPI client runtime -- the 89 documented TAPI client          */
/*      functions (66 line* + 23 phone*) plus the LINECALLBACK /      */
/*      PHONECALLBACK shapes and the TSPI_lineForward hold closure.   */
/* ------------------------------------------------------------------ */

static void m45_line_callback(DWORD hDevice, DWORD dwMsg,
                              DWORD dwCallbackInstance, DWORD dwParam1,
                              DWORD dwParam2, DWORD dwParam3)
{ (void) hDevice; (void) dwMsg; (void) dwCallbackInstance;
  (void) dwParam1; (void) dwParam2; (void) dwParam3; }

static void m45_phone_callback(HANDLE hDevice, DWORD dwMsg,
                               DWORD dwCallbackInstance, DWORD dwParam1,
                               DWORD dwParam2, DWORD dwParam3)
{ (void) hDevice; (void) dwMsg; (void) dwCallbackInstance;
  (void) dwParam1; (void) dwParam2; (void) dwParam3; }

static int m45_shaped_usage(void)
{
    HLINEAPP   hLineApp  = (HLINEAPP)0;
    HLINE      hLine     = (HLINE)0;
    HCALL      hCall     = (HCALL)0;
    HPHONEAPP  hPhoneApp = (HPHONEAPP)0;
    HPHONE     hPhone    = (HPHONE)0;
    HINSTANCE  hInst     = (HINSTANCE)0;
    HWND       hwnd      = (HWND)0;
    HICON      hIcon     = (HICON)0;
    DWORD      dw        = 0;
    DWORD      dw2       = 0;
    DWORD_PTR  dp        = 0;

    LPHLINE      lphLine     = &hLine;
    LPHLINEAPP   lphLineApp  = &hLineApp;
    LPHCALL      lphCall     = &hCall;
    LPHPHONE     lphPhone    = &hPhone;
    LPHPHONEAPP  lphPhoneApp = &hPhoneApp;

    LINECALLPARAMS          cparams = {0};
    LINECALLINFO            cinfo   = {0};
    LINECALLSTATUS          cstat   = {0};
    LINECALLLIST            clist   = {0};
    LINEADDRESSCAPS         acaps   = {0};
    LINEADDRESSSTATUS       astat   = {0};
    LINEDEVCAPS             dcaps   = {0};
    LINEDEVSTATUS           dstat   = {0};
    LINEDIALPARAMS          dial    = {0};
    LINEEXTENSIONID         lext    = {0};
    LINEGENERATETONE        tone    = {0};
    LINEINITIALIZEEXPARAMS  lix     = {0};
    LINEMESSAGE             lmsg    = {0};
    LINEPROVIDERLIST        plist   = {0};
    LINETRANSLATECAPS       tcaps   = {0};
    LINETRANSLATEOUTPUT     tout    = {0};
    PHONECAPS               pcaps   = {0};
    PHONESTATUS             pstat   = {0};
    PHONEMESSAGE            pmsg    = {0};
    PHONEEXTENSIONID        pext    = {0};
    PHONEINITIALIZEEXPARAMS pix     = {0};
    VARSTRING               vs      = {0};
    LPLINEFORWARDLIST       fwd     = (LPLINEFORWARDLIST)0;

    /* callback typedef shapes (lineCallbackFunc ms893424 prints the
     * hDevice parameter as DWORD; phoneCallbackFunc ms895910 as
     * HANDLE -- both assignments below must fit). */
    LINECALLBACK  lc = m45_line_callback;
    PHONECALLBACK pc = m45_phone_callback;
    (void) lc; (void) pc;

    /* line initialization / shutdown */
    (void) lineInitialize(lphLineApp, hInst, m45_line_callback,
                          (LPCWSTR)0, &dw);
    (void) lineInitializeEx(lphLineApp, hInst, m45_line_callback,
                            (LPCWSTR)0, &dw, &dw2, &lix);
    (void) lineShutdown(hLineApp);
    (void) lineNegotiateAPIVersion(hLineApp, 0, 0, 0, &dw, &lext);
    (void) lineNegotiateExtVersion(hLineApp, 0, 0, 0, 0, &dw);
    (void) lineGetMessage(hLineApp, &lmsg, 0);
    (void) lineSetCurrentLocation(hLineApp, 0);
    (void) lineAddProvider((LPCWSTR)0, hwnd, &dw);
    (void) lineGetProviderList(0, &plist);

    /* line device open / close / capabilities */
    (void) lineOpen(hLineApp, 0, lphLine, 0, 0, 0, 0, 0,
                    (LPLINECALLPARAMS)&cparams);
    (void) lineClose(hLine);
    (void) lineGetDevCaps(hLineApp, 0, 0, 0, &dcaps);
    (void) lineGetLineDevStatus(hLine, &dstat);
    (void) lineGetAddressCaps(hLineApp, 0, 0, 0, 0, &acaps);
    (void) lineGetAddressStatus(hLine, 0, &astat);
    (void) lineGetAddressID(hLine, &dw, 0, (LPCWSTR)0, 0);
    (void) lineGetID(hLine, 0, hCall, 0, &vs, (LPCWSTR)0);
    (void) lineGetIcon(0, (LPCWSTR)0, &hIcon);
    (void) lineGetStatusMessages(hLine, &dw, &dw2);
    (void) lineSetStatusMessages(hLine, 0, 0);
    (void) lineGetNewCalls(hLine, 0, 0, &clist);
    (void) lineGetNumRings(hLine, 0, &dw);
    (void) lineSetNumRings(hLine, 0, 0);

    /* call setup / control */
    (void) lineMakeCall(hLine, lphCall, (LPCWSTR)0, 0,
                        (LPLINECALLPARAMS)&cparams);
    (void) lineAnswer(hCall, (LPCSTR)0, 0);
    (void) lineAccept(hCall, (LPCSTR)0, 0);
    (void) lineDeallocateCall(hCall);
    (void) lineDrop(hCall, (LPCTSTR)0, 0);
    (void) lineDial(hCall, (LPCWSTR)0, 0);
    (void) lineHold(hCall);
    (void) lineUnhold(hCall);
    (void) lineSwapHold(hCall, (HCALL)0);
    (void) linePickup(hLine, 0, lphCall, (LPCSTR)0, (LPCSTR)0);
    (void) lineRedirect(hCall, (LPCSTR)0, 0);
    (void) lineForward(hLine, 0, 0, fwd, 0, lphCall,
                       (LPLINECALLPARAMS)&cparams);
    (void) lineHandoff(hCall, (LPCSTR)0, 0);

    /* call information */
    (void) lineGetCallInfo(hCall, &cinfo);
    (void) lineGetCallStatus(hCall, &cstat);
    (void) lineGetConfRelatedCalls(hCall, &clist);
    (void) lineSetCallParams(hCall, 0, 0, 0,
                             (LPLINEDIALPARAMS)&dial);
    (void) lineSetCallPrivilege(hCall, 0);
    (void) lineSetMediaMode(hCall, 0);
    (void) lineSetTerminal(hLine, 0, hCall, 0, 0, 0, 0);
    (void) lineMonitorDigits(hCall, 0);
    (void) lineMonitorMedia(hCall, 0);
    (void) lineGenerateDigits(hCall, 0, (LPCWSTR)0, 0);
    (void) lineGenerateTone(hCall, 0, 0, 0,
                            (LPLINEGENERATETONE)&tone);
    (void) lineSendUserUserInfo(hCall, (LPCSTR)0, 0);
    (void) lineReleaseUserUserInfo(hCall);
    (void) lineDevSpecific(hLine, 0, hCall, (LPVOID)0, 0);

    /* conference and transfer */
    (void) lineAddToConference(hCall, (HCALL)0);
    (void) lineRemoveFromConference(hCall);
    (void) lineSetupConference(hCall, hLine, lphCall, lphCall, 0,
                               (LPLINECALLPARAMS)&cparams);
    (void) linePrepareAddToConference(hCall, lphCall,
                                      (LPLINECALLPARAMS)&cparams);
    (void) lineSetupTransfer(hCall, lphCall,
                             (LPLINECALLPARAMS)&cparams);
    (void) lineCompleteTransfer(hCall, (HCALL)0, lphCall, 0);
    (void) lineBlindTransfer(hCall, (LPCWSTR)0, 0);

    /* device configuration / translation / priority */
    (void) lineGetDevConfig(0, &vs, (LPCSTR)0);
    (void) lineSetDevConfig(0, (LPVOID)0, 0, (LPCTSTR)0);
    (void) lineConfigDialogEdit(0, hwnd, (LPCWSTR)0, (LPVOID)0, 0,
                                &vs);
    (void) lineGetTranslateCaps(hLineApp, 0, &tcaps);
    (void) lineTranslateAddress(hLineApp, 0, 0, (LPCWSTR)0, 0, 0,
                                &tout);
    (void) lineTranslateDialog(hLineApp, 0, 0, hwnd, (LPCWSTR)0);
    (void) lineSetTollList(hLineApp, 0, (LPCWSTR)0, 0);
    (void) lineGetAppPriority((LPCWSTR)0, 0, &lext, 0, &vs, &dw);
    (void) lineSetAppPriority((LPCSTR)0, 0, &lext, 0, (LPCSTR)0, 0);

    /* phone device functions */
    (void) phoneInitializeEx(lphPhoneApp, hInst, m45_phone_callback,
                             (LPCWSTR)0, &dw, &dw2, &pix);
    (void) phoneShutdown(hPhoneApp);
    (void) phoneOpen(hPhoneApp, 0, lphPhone, 0, 0, dp, 0);
    (void) phoneClose(hPhone);
    (void) phoneNegotiateAPIVersion(hPhoneApp, 0, 0, 0, &dw, &pext);
    (void) phoneNegotiateExtVersion(hPhoneApp, 0, 0, 0, 0, &dw);
    (void) phoneGetMessage(hPhoneApp, &pmsg, 0);
    (void) phoneGetDevCaps(hPhoneApp, 0, 0, 0, &pcaps);
    (void) phoneGetStatus(hPhone, &pstat);
    (void) phoneGetGain(hPhone, 0, &dw);
    (void) phoneSetGain(hPhone, 0, 0);
    (void) phoneGetVolume(hPhone, 0, &dw);
    (void) phoneSetVolume(hPhone, 0, 0);
    (void) phoneGetHookSwitch(hPhone, &dw);
    (void) phoneSetHookSwitch(hPhone, 0, 0);
    (void) phoneGetRing(hPhone, &dw, &dw2);
    (void) phoneSetRing(hPhone, 0, 0);
    (void) phoneGetStatusMessages(hPhone, &dw, &dw2, &dw);
    (void) phoneSetStatusMessages(hPhone, 0, 0, 0);
    (void) phoneGetIcon(0, (LPCWSTR)0, &hIcon);
    (void) phoneGetID(hPhone, &vs, (LPCWSTR)0);
    (void) phoneConfigDialog(0, hwnd, (LPCSTR)0);
    (void) phoneDevSpecific(hPhone, (LPVOID)0, 0);

    /* M43 hold closed: TSPI_lineForward through the opaque list
     * pointer (aa451032). */
    (void) TSPI_lineForward(0, (HDRVLINE)0, 0, 0, fwd, 0,
                            (HTAPICALL)0, (LPHDRVCALL)0,
                            (LPLINECALLPARAMS)&cparams);
    return 0;
}

/* ------------------------------------------------------------------ */
/* M46: Input Method Manager (imm.h; Coreimm.lib) -- the 55           */
/*      documented IMM functions, the nine complete structures, the   */
/*      three opaque pointer sets and the REGISTERWORDENUMPROC shape. */
/* ------------------------------------------------------------------ */

#if __SIZEOF_POINTER__ == 4
_Static_assert(sizeof(CANDIDATEFORM) == 32, "CANDIDATEFORM 32-bit size");
_Static_assert(sizeof(CANDIDATEINFO) == 144, "CANDIDATEINFO 32-bit size");
_Static_assert(sizeof(CANDIDATELIST) == 24, "CANDIDATELIST 32-bit size");
_Static_assert(sizeof(COMPOSITIONFORM) == 28, "COMPOSITIONFORM 32-bit size");
_Static_assert(sizeof(COMPOSITIONSTR) == 100, "COMPOSITIONSTR 32-bit size");
_Static_assert(sizeof(GUIDELINE) == 28, "GUIDELINE 32-bit size");
_Static_assert(sizeof(RECONVERTSTRING) == 32, "RECONVERTSTRING 32-bit size");
_Static_assert(sizeof(REGISTERWORD) == 8, "REGISTERWORD 32-bit size");
_Static_assert(sizeof(STYLEBUF) == 36, "STYLEBUF 32-bit size");
#endif

static UINT CALLBACK m46_enum_register_word(LPCTSTR lpszReading,
    DWORD dwStyle, LPCTSTR lpszString, LPVOID lpData)
{ (void) lpszReading; (void) dwStyle; (void) lpszString;
  (void) lpData; return 0; }

static int m46_shaped_usage(void)
{
    HWND    hwnd    = (HWND)0;
    HKL     hKL     = (HKL)0;
    HIMC    hIMC    = (HIMC)0;
    HIMCC   hIMCC   = (HIMCC)0;
    DWORD   dw      = 0;
    DWORD   dw2     = 0;
    UINT    u       = 0;
    UINT    u2      = 0;

    CANDIDATEFORM   cform = {0};
    CANDIDATEINFO   cinfo = {0};
    COMPOSITIONFORM compform = {0};
    COMPOSITIONSTR  compstr = {0};
    GUIDELINE       gl    = {0};
    RECONVERTSTRING rstr  = {0};
    REGISTERWORD    rw    = {0};
    STYLEBUF        sbuf  = {0};
    LOGFONT         lf    = {0};
    POINT           pt    = {0};

    /* callback typedef shape (EnumRegisterWordProc ms904955) */
    REGISTERWORDENUMPROC ewp = m46_enum_register_word;
    (void) ewp;

    /* input-context management */
    hIMC = ImmGetContext(hwnd);
    (void) ImmReleaseContext(hwnd, hIMC);
    hIMC = ImmCreateContext();
    (void) ImmDestroyContext(hIMC);
    hIMC = ImmAssociateContext(hwnd, (HIMC)0);
    (void) ImmAssociateContextEx(hwnd, hIMC, 0);
    (void) ImmLockIMC(hIMC);
    (void) ImmUnlockIMC(hIMC);
    (void) ImmGetIMCLockCount(hIMC);

    /* IMCC memory blocks */
    hIMCC = ImmCreateIMCC(0);
    (void) ImmDestroyIMCC(hIMCC);
    hIMCC = ImmReSizeIMCC(hIMCC, 0);
    (void) ImmLockIMCC(hIMCC);
    (void) ImmUnlockIMCC(hIMCC);
    (void) ImmGetIMCCSize(hIMCC);
    (void) ImmGetIMCCLockCount(hIMCC);

    /* candidate list / window */
    (void) ImmGetCandidateList(hIMC, 0, (LPCANDIDATELIST)0, 0);
    (void) ImmGetCandidateListCount(hIMC, &dw);
    (void) ImmGetCandidateWindow(hIMC, 0, &cform);
    (void) ImmSetCandidateWindow(hIMC, &cform);

    /* composition string / window / font */
    (void) ImmGetCompositionString(hIMC, 0, (LPVOID)0, 0);
    (void) ImmSetCompositionString(hIMC, 0, (LPCVOID)0, 0,
                                   (LPCVOID)0, 0);
    (void) ImmGetCompositionWindow(hIMC, &compform);
    (void) ImmSetCompositionWindow(hIMC, &compform);
    (void) ImmGetCompositionFont(hIMC, &lf);
    (void) ImmSetCompositionFont(hIMC, &lf);

    /* conversion status / list */
    (void) ImmGetConversionStatus(hIMC, &dw, &dw2);
    (void) ImmSetConversionStatus(hIMC, 0, 0);
    (void) ImmGetConversionList(hKL, hIMC, (LPCTSTR)0,
                                (LPCANDIDATELIST)0, 0, 0);

    /* status window / open status / properties */
    (void) ImmGetOpenStatus(hIMC);
    (void) ImmSetOpenStatus(hIMC, 0);
    (void) ImmGetStatusWindowPos(hIMC, &pt);
    (void) ImmSetStatusWindowPos(hIMC, &pt);
    (void) ImmGetDefaultIMEWnd(hwnd);
    (void) ImmGetProperty(hKL, 0);
    (void) ImmGetGuideLine(hIMC, 0, (LPTSTR)0, 0);
    (void) ImmGetImeMenuItems(hIMC, 0, 0, (LPIMEMENUITEMINFO)0,
                              (LPIMEMENUITEMINFO)0, 0);

    /* keyboard layout / IME identity */
    (void) ImmIsIME(hKL);
    (void) ImmGetDescription(hKL, (LPTSTR)0, 0);
    (void) ImmGetIMEFileName(hKL, (LPTSTR)0, 0);
    (void) ImmConfigureIME(hKL, hwnd, 0, (LPVOID)0);
    (void) ImmEscape(hKL, hIMC, 0, (LPVOID)0);
    (void) ImmIsUIMessage(hwnd, 0, (WPARAM)0, (LPARAM)0);
    (void) ImmGenerateMessage(hIMC);
    (void) ImmGetVirtualKey(hwnd);

    /* hot keys */
    (void) ImmGetHotKey(0, &u, &u2, (LPHKL)0);
    (void) ImmSetHotKey(0, 0, 0, hKL);
    (void) ImmSimulateHotKey(hwnd, 0);

    /* user dictionary (register words) */
    (void) ImmRegisterWord(hKL, (LPCTSTR)0, 0, (LPCTSTR)0);
    (void) ImmUnregisterWord(hKL, (LPCTSTR)0, 0, (LPCTSTR)0);
    (void) ImmEnumRegisterWord(hKL, m46_enum_register_word,
                               (LPCTSTR)0, 0, (LPCTSTR)0, (LPVOID)0);
    (void) ImmGetRegisterWordStyle(hKL, 0, &sbuf);

    /* IME control / CE-specific */
    (void) ImmNotifyIME(hIMC, 0, 0, 0);
    (void) ImmDisableIME(0);
    (void) ImmSIPanelState(0, (LPVOID)0);

    /* keep the nine structures referenced */
    (void) cinfo; (void) compstr; (void) gl; (void) rstr; (void) rw;
    return 0;
}

/* ------------------------------------------------------------------ */
/* M47: Cryptography base CSP unit (wincrypt.h; Coredll.lib) -- the   */
/*      42 documented Crypt* functions, CPAcquireContext (CSP         */
/*      authoring entry point), the fundamental crypto types and the  */
/*      documented BLOB alias set, CMSG_STREAM_INFO and               */
/*      VTableProvStruc.                                              */
/* ------------------------------------------------------------------ */

#if __SIZEOF_POINTER__ == 4
/* _CRYPTOAPI_BLOB has no self-typedef name on the page; the alias
 * list (CRYPT_INTEGER_BLOB .. CRYPT_ATTR_BLOB) is what it defines. */
_Static_assert(sizeof(struct _CRYPTOAPI_BLOB) == 8, "_CRYPTOAPI_BLOB 32-bit size");
_Static_assert(sizeof(DATA_BLOB) == 8, "DATA_BLOB 32-bit size");
_Static_assert(sizeof(CRYPT_INTEGER_BLOB) == 8, "CRYPT_INTEGER_BLOB 32-bit size");
_Static_assert(sizeof(CMSG_STREAM_INFO) == 12, "CMSG_STREAM_INFO 32-bit size");
_Static_assert(sizeof(VTableProvStruc) == 28, "VTableProvStruc 32-bit size");
#endif

static BOOL WINAPI m47_stream_output(const void *pvArg, BYTE *pbData,
                                     DWORD cbData, BOOL fFinal)
{ (void) pvArg; (void) pbData; (void) cbData; (void) fFinal;
  return TRUE; }

static int m47_shaped_usage(void)
{
    HCRYPTPROV  hProv  = 0;
    HCRYPTKEY   hKey   = 0;
    HCRYPTHASH  hHash  = 0;
    HCRYPTMSG   hMsg   = 0;
    ALG_ID      algid  = 0;
    DWORD       dw     = 0;
    BYTE        buf[8] = {0};
    WCHAR       wdesc[] = { 'd', 0 };
    LPWSTR      pwstr  = (LPWSTR)0;

    DATA_BLOB             blob = {0};
    DATA_BLOB             din = {0}, dout = {0};
    CMSG_STREAM_INFO      csi = {0};
    VTableProvStruc       vts = {0};
    PCERT_INFO            pcertinfo = (PCERT_INFO)0;
    PFN_CMSG_STREAM_OUTPUT pfn = m47_stream_output;

    /* callback typedef shape */
    csi.cbContent = 0;
    csi.pfnStreamOutput = pfn;
    csi.pvArg = (void *)0;
    (void) csi;

    /* provider acquisition / reference / release */
    (void) CryptAcquireContext(&hProv, (LPCTSTR)0, (LPCTSTR)0, 0, 0);
    (void) CryptContextAddRef(hProv, &dw, 0);

    /* key management */
    (void) CryptGenKey(hProv, algid, 0, &hKey);
    (void) CryptDeriveKey(hProv, algid, hHash, 0, &hKey);
    (void) CryptGetUserKey(hProv, 0, &hKey);
    (void) CryptImportKey(hProv, buf, dw, hKey, 0, &hKey);
    (void) CryptExportKey(hKey, hKey, 0, 0, buf, &dw);
    (void) CryptDuplicateKey(hKey, &dw, 0, &hKey);
    (void) CryptGetKeyParam(hKey, 0, buf, &dw, 0);
    (void) CryptSetKeyParam(hKey, 0, buf, 0);
    (void) CryptDestroyKey(hKey);

    /* hashing */
    (void) CryptCreateHash(hProv, algid, hKey, 0, &hHash);
    (void) CryptHashData(hHash, buf, dw, 0);
    (void) CryptHashSessionKey(hHash, hKey, 0);
    (void) CryptDuplicateHash(hHash, &dw, 0, &hHash);
    (void) CryptGetHashParam(hHash, 0, buf, &dw, 0);
    (void) CryptSetHashParam(hHash, 0, buf, 0);
    (void) CryptDestroyHash(hHash);

    /* encrypt / decrypt */
    (void) CryptEncrypt(hKey, hHash, TRUE, 0, buf, &dw, dw);
    (void) CryptDecrypt(hKey, hHash, TRUE, 0, buf, &dw);

    /* signing / verification */
    (void) CryptSignHash(hHash, 0, (LPCTSTR)0, 0, buf, &dw);
    (void) CryptVerifySignature(hHash, buf, dw, hKey, (LPCTSTR)0, 0);

    /* random */
    (void) CryptGenRandom(hProv, dw, buf);

    /* provider enumeration / selection */
    (void) CryptEnumProviders(0, &dw, 0, &dw, (LPTSTR)0, &dw);
    (void) CryptEnumProviderTypes(0, &dw, 0, &dw, (LPTSTR)0, &dw);
    (void) CryptGetDefaultProvider(0, &dw, 0, (LPTSTR)0, &dw);
    (void) CryptSetProvider((LPCTSTR)0, 0);
    (void) CryptSetProviderEx((LPCTSTR)0, 0, &dw, 0);
    (void) CryptGetProvParam(hProv, 0, buf, &dw, 0);
    (void) CryptSetProvParam(hProv, 0, buf, 0);
    (void) CryptReleaseContext(hProv, 0);

    /* localized name lookup (wide-string only) */
    (void) CryptFindLocalizedName((LPCWSTR)0);

    /* CryptMsg family */
    hMsg = CryptMsgOpenToEncode(0, 0, 0, (const void *)0, (LPSTR)0,
                                (PCMSG_STREAM_INFO)0);
    (void) CryptMsgUpdate(hMsg, (const BYTE *)0, 0, TRUE);
    (void) CryptMsgGetParam(hMsg, 0, 0, (void *)0, &dw);
    (void) CryptMsgControl(hMsg, 0, 0, (const void *)0);
    hMsg = CryptMsgDuplicate(hMsg);
    (void) CryptMsgClose(hMsg);
    hMsg = CryptMsgOpenToDecode(0, 0, 0, hProv, pcertinfo,
                                (PCMSG_STREAM_INFO)0);
    dw = CryptMsgCalculateEncodedLength(0, 0, 0, (const void *)0,
                                        (LPSTR)0, 0);
    (void) CryptMsgClose(hMsg);

    /* protected data (CE .NET 4.0+) */
    din.pbData = buf;
    din.cbData = sizeof(buf);
    (void) CryptProtectData(&din, wdesc, &blob, (PVOID)0,
                            (struct CRYPTPROTECT_PROMPTSTRUCT *)0, 0,
                            &dout);
    (void) CryptUnprotectData(&dout, &pwstr, &blob, (PVOID)0,
                              (struct CRYPTPROTECT_PROMPTSTRUCT *)0, 0,
                              &din);

    /* CPAcquireContext (CSP authoring; Link Library: Developer
     * defined -- not a coredll import, exercised for shape only). */
    vts.Version = 3;
    vts.FuncVerifyImage = (FARPROC)0;
    vts.FuncReturnhWnd = (FARPROC)0;
    vts.dwProvType = 0;
    vts.pbContextInfo = buf;
    vts.cbContextInfo = sizeof(buf);
    vts.pszProvName = wdesc;
    (void) CPAcquireContext(&hProv, wdesc, 0, &vts);
    (void) vts;
    return 0;
}

/* ------------------------------------------------------------------ */
/* M48: Cryptography certificate / encode / OID / PFX unit            */
/*      (wincrypt.h; Crypt32.lib) -- the 83 documented Crypt32.lib    */
/*      functions, the CERT_* / CMSG_* / CRYPT_* structure trees and  */
/*      the callback pointer shapes.                                  */
/* ------------------------------------------------------------------ */

/* Pointer-free M48 layouts (hold on every host). */
_Static_assert(sizeof(PROV_ENUMALGS) == 52, "PROV_ENUMALGS size");
_Static_assert(sizeof(PROV_ENUMALGS_EX) == 148, "PROV_ENUMALGS_EX size");
_Static_assert(sizeof(PUBLICKEYSTRUC) == 8, "PUBLICKEYSTRUC size");
_Static_assert(sizeof(BLOBHEADER) == 8, "BLOBHEADER alias size");
_Static_assert(sizeof(RSAPUBKEY) == 12, "RSAPUBKEY size");
_Static_assert(sizeof(CERT_SYSTEM_STORE_INFO) == 4,
               "CERT_SYSTEM_STORE_INFO size");
_Static_assert(sizeof(CERT_TRUST_STATUS) == 8, "CERT_TRUST_STATUS size");

/* Pointer-bearing M48 layouts -- 32-bit CE model only (the CE
 * toolchain matrix is the arbiter). */
/* All sizes below measured on the CE 32-bit target with the
 * LLVM-WinCE toolchain (-fdump-record-layouts), i.e. the CE ABI
 * itself, not a calculation. */
#if __SIZEOF_POINTER__ == 4
_Static_assert(sizeof(CTL_USAGE) == 8, "CTL_USAGE 32-bit size");
_Static_assert(sizeof(CERT_ENHKEY_USAGE) == 8,
               "CERT_ENHKEY_USAGE alias 32-bit size");
_Static_assert(sizeof(CRYPT_BIT_BLOB) == 12, "CRYPT_BIT_BLOB 32-bit size");
_Static_assert(sizeof(CRYPT_ALGORITHM_IDENTIFIER) == 12,
               "CRYPT_ALGORITHM_IDENTIFIER 32-bit size");
_Static_assert(sizeof(CRYPT_ATTRIBUTE) == 12, "CRYPT_ATTRIBUTE 32-bit size");
_Static_assert(sizeof(CRYPT_ATTRIBUTES) == 8, "CRYPT_ATTRIBUTES 32-bit size");
_Static_assert(sizeof(CRYPT_KEY_PROV_PARAM) == 16,
               "CRYPT_KEY_PROV_PARAM 32-bit size");
_Static_assert(sizeof(CRYPT_KEY_PROV_INFO) == 28,
               "CRYPT_KEY_PROV_INFO 32-bit size");
_Static_assert(sizeof(CRYPT_OID_INFO) == 28, "CRYPT_OID_INFO 32-bit size");
_Static_assert(sizeof(CRYPT_ENCODE_PARA) == 12, "CRYPT_ENCODE_PARA 32-bit size");
_Static_assert(sizeof(HMAC_INFO) == 20, "HMAC_INFO 32-bit size");
_Static_assert(sizeof(CERT_EXTENSION) == 16, "CERT_EXTENSION 32-bit size");
_Static_assert(sizeof(CERT_ISSUER_SERIAL_NUMBER) == 16,
               "CERT_ISSUER_SERIAL_NUMBER 32-bit size");
_Static_assert(sizeof(CERT_PRIVATE_KEY_VALIDITY) == 16,
               "CERT_PRIVATE_KEY_VALIDITY 32-bit size");
_Static_assert(sizeof(CERT_PUBLIC_KEY_INFO) == 24,
               "CERT_PUBLIC_KEY_INFO 32-bit size");
_Static_assert(sizeof(CERT_INFO) == 112, "CERT_INFO 32-bit size");
_Static_assert(sizeof(CERT_CONTEXT) == 20, "CERT_CONTEXT 32-bit size");
_Static_assert(sizeof(CERT_RDN_ATTR) == 16, "CERT_RDN_ATTR 32-bit size");
_Static_assert(sizeof(CERT_RDN) == 8, "CERT_RDN 32-bit size");
_Static_assert(sizeof(CERT_NAME_INFO) == 8, "CERT_NAME_INFO 32-bit size");
_Static_assert(sizeof(CERT_POLICY_QUALIFIER_INFO) == 12,
               "CERT_POLICY_QUALIFIER_INFO 32-bit size");
_Static_assert(sizeof(CERT_POLICY_ID) == 8, "CERT_POLICY_ID 32-bit size");
_Static_assert(sizeof(CERT_POLICY_INFO) == 12, "CERT_POLICY_INFO 32-bit size");
_Static_assert(sizeof(CERT_POLICIES_INFO) == 8, "CERT_POLICIES_INFO 32-bit size");
_Static_assert(sizeof(CERT_KEY_ATTRIBUTES_INFO) == 24,
               "CERT_KEY_ATTRIBUTES_INFO 32-bit size");
_Static_assert(sizeof(CERT_KEY_CONTEXT) == 12, "CERT_KEY_CONTEXT 32-bit size");
_Static_assert(sizeof(CERT_KEY_USAGE_RESTRICTION_INFO) == 20,
               "CERT_KEY_USAGE_RESTRICTION_INFO 32-bit size");
_Static_assert(sizeof(CERT_KEYGEN_REQUEST_INFO) == 32,
               "CERT_KEYGEN_REQUEST_INFO 32-bit size");
_Static_assert(sizeof(CERT_ID) == 20, "CERT_ID 32-bit size");
_Static_assert(sizeof(CERT_ALT_NAME_ENTRY) == 12,
               "CERT_ALT_NAME_ENTRY 32-bit size");
_Static_assert(sizeof(CERT_ALT_NAME_INFO) == 8, "CERT_ALT_NAME_INFO 32-bit size");
_Static_assert(sizeof(CERT_ACCESS_DESCRIPTION) == 16,
               "CERT_ACCESS_DESCRIPTION 32-bit size");
_Static_assert(sizeof(CERT_AUTHORITY_INFO_ACCESS) == 8,
               "CERT_AUTHORITY_INFO_ACCESS 32-bit size");
_Static_assert(sizeof(CERT_AUTHORITY_KEY_ID_INFO) == 24,
               "CERT_AUTHORITY_KEY_ID_INFO 32-bit size");
_Static_assert(sizeof(CERT_AUTHORITY_KEY_ID2_INFO) == 24,
               "CERT_AUTHORITY_KEY_ID2_INFO 32-bit size");
_Static_assert(sizeof(CERT_BASIC_CONSTRAINTS_INFO) == 28,
               "CERT_BASIC_CONSTRAINTS_INFO 32-bit size");
_Static_assert(sizeof(CERT_BASIC_CONSTRAINTS2_INFO) == 12,
               "CERT_BASIC_CONSTRAINTS2_INFO 32-bit size");
_Static_assert(sizeof(CERT_REQUEST_INFO) == 44, "CERT_REQUEST_INFO 32-bit size");
_Static_assert(sizeof(CERT_SIGNED_CONTENT_INFO) == 32,
               "CERT_SIGNED_CONTENT_INFO 32-bit size");
_Static_assert(sizeof(CERT_USAGE_MATCH) == 12, "CERT_USAGE_MATCH 32-bit size");
_Static_assert(sizeof(CERT_CHAIN_ELEMENT) == 20, "CERT_CHAIN_ELEMENT 32-bit size");
_Static_assert(sizeof(CERT_SIMPLE_CHAIN) == 24, "CERT_SIMPLE_CHAIN 32-bit size");
_Static_assert(sizeof(CERT_CHAIN_CONTEXT) == 20,
               "CERT_CHAIN_CONTEXT 32-bit size");
_Static_assert(sizeof(CERT_CHAIN_ENGINE_CONFIG) == 40,
               "CERT_CHAIN_ENGINE_CONFIG 32-bit size");
_Static_assert(sizeof(CERT_CHAIN_PARA) == 16, "CERT_CHAIN_PARA 32-bit size");
_Static_assert(sizeof(CERT_TRUST_LIST_INFO) == 12,
               "CERT_TRUST_LIST_INFO 32-bit size");
_Static_assert(sizeof(CERT_SYSTEM_STORE_RELOCATE_PARA) == 8,
               "CERT_SYSTEM_STORE_RELOCATE_PARA 32-bit size");
_Static_assert(sizeof(CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR_PARA) == 16,
               "CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR_PARA 32-bit size");
_Static_assert(sizeof(CMSG_CTRL_DECRYPT_PARA) == 16,
               "CMSG_CTRL_DECRYPT_PARA 32-bit size");
_Static_assert(sizeof(CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA) == 12,
               "CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA 32-bit size");
_Static_assert(sizeof(CMSG_CTRL_KEY_AGREE_DECRYPT_PARA) == 36,
               "CMSG_CTRL_KEY_AGREE_DECRYPT_PARA 32-bit size");
_Static_assert(sizeof(CMSG_CTRL_VERIFY_SIGNATURE_EX_PARA) == 20,
               "CMSG_CTRL_VERIFY_SIGNATURE_EX_PARA 32-bit size");
_Static_assert(sizeof(CMSG_KEY_TRANS_RECIPIENT_INFO) == 44,
               "CMSG_KEY_TRANS_RECIPIENT_INFO 32-bit size");
_Static_assert(sizeof(CMSG_MAIL_LIST_RECIPIENT_INFO) == 44,
               "CMSG_MAIL_LIST_RECIPIENT_INFO 32-bit size");
_Static_assert(sizeof(CMSG_CMS_RECIPIENT_INFO) == 8,
               "CMSG_CMS_RECIPIENT_INFO 32-bit size");
_Static_assert(sizeof(CMSG_CMS_SIGNER_INFO) == 72,
               "CMSG_CMS_SIGNER_INFO 32-bit size");
_Static_assert(sizeof(CMSG_SIGNER_INFO) == 68, "CMSG_SIGNER_INFO 32-bit size");
_Static_assert(sizeof(CMSG_SIGNER_ENCODE_INFO) == 84,
               "CMSG_SIGNER_ENCODE_INFO 32-bit size");
_Static_assert(sizeof(CMSG_SIGNED_ENCODE_INFO) == 36,
               "CMSG_SIGNED_ENCODE_INFO 32-bit size");
_Static_assert(sizeof(CMSG_ENVELOPED_ENCODE_INFO) == 68,
               "CMSG_ENVELOPED_ENCODE_INFO 32-bit size");
_Static_assert(sizeof(CMSG_HASHED_ENCODE_INFO) == 24,
               "CMSG_HASHED_ENCODE_INFO 32-bit size");
#endif

static BOOL WINAPI m48_enum_system_store(const void *pvSystemStore,
                                         DWORD dwFlags,
                                         PCERT_SYSTEM_STORE_INFO pStoreInfo,
                                         void *pvReserved, void *pvArg)
{ (void) pvSystemStore; (void) dwFlags; (void) pStoreInfo;
  (void) pvReserved; (void) pvArg; return TRUE; }

static BOOL WINAPI m48_enum_store_location(LPCWSTR pvszStoreLoocations,
                                           DWORD dwFlags, void *pvReserved,
                                           void *pvArg)
{ (void) pvszStoreLoocations; (void) dwFlags; (void) pvReserved;
  (void) pvArg; return TRUE; }

static int m48_shaped_usage(void)
{
    HCERTSTORE           hStore = 0;
    HCRYPTPROV           hProv  = 0;
    HCRYPTKEY            hKey   = 0;
    HCRYPTOIDFUNCSET     hFuncSet = 0;
    HCRYPTOIDFUNCADDR    hFuncAddr = 0;
    HCRYPTDEFAULTCONTEXT hDefCtx = 0;
    PCCERT_CONTEXT       pCert  = (PCCERT_CONTEXT)0;
    PCCERT_CHAIN_CONTEXT pChain = (PCCERT_CHAIN_CONTEXT)0;
    DWORD                dw     = 0;
    BYTE                 buf[8] = {0};
    FILETIME             ft     = {0};

    CERT_INFO                     cinfo = {0};
    CERT_CONTEXT                  cctx  = {0};
    CERT_EXTENSION                cext  = {0};
    CERT_PUBLIC_KEY_INFO          pki   = {0};
    CERT_NAME_BLOB                name  = {0};
    CERT_RDN_ATTR                 rattr = {0};
    CERT_NAME_INFO                cname = {0};
    CERT_ENHKEY_USAGE             eku   = {0};
    CERT_CHAIN_PARA               cpara = {0};
    CERT_CHAIN_ENGINE_CONFIG      ceng  = {0};
    CERT_SYSTEM_STORE_INFO        ssi   = {0};
    CERT_SYSTEM_STORE_RELOCATE_PARA srp = {0};
    CRYPT_ALGORITHM_IDENTIFIER    algid = {0};
    CRYPT_ATTRIBUTE               cattr = {0};
    CRYPT_ATTRIBUTES              cattrs = {0};
    CRYPT_BIT_BLOB                bits  = {0};
    CRYPT_ENCODE_PARA             encpara = {0};
    CRYPT_OID_INFO                oidinfo = {0};
    CRYPT_OID_FUNC_ENTRY          oidentry = {0};
    CRYPT_KEY_PROV_INFO           kpi   = {0};
    CRYPT_KEY_PROV_PARAM          kpp   = {0};
    CRYPT_DATA_BLOB               data  = {0};
    CRYPT_HASH_BLOB               hash  = {0};
    CMSG_SIGNED_ENCODE_INFO       sgn   = {0};
    CMSG_ENVELOPED_ENCODE_INFO    env   = {0};
    CMSG_HASHED_ENCODE_INFO       hsd   = {0};
    CMSG_CTRL_DECRYPT_PARA        dec   = {0};
    CMSG_CTRL_VERIFY_SIGNATURE_EX_PARA vsx = {0};
    CMSG_SIGNER_INFO              sgni  = {0};
    CMSG_CMS_SIGNER_INFO          cmsi  = {0};
    CMSG_CMS_RECIPIENT_INFO       rcpt  = {0};
    CMSG_KEY_TRANS_RECIPIENT_INFO ktri  = {0};
    CMSG_MAIL_LIST_RECIPIENT_INFO mlri  = {0};
    PUBLICKEYSTRUC                pks   = {0};
    BLOBHEADER                    bh    = {0};
    RSAPUBKEY                     rsa   = {0};
    PROV_ENUMALGS                 pea   = {0};
    PROV_ENUMALGS_EX              peaex = {0};
    HMAC_INFO                     hmac  = {0};
    CERT_ID                       cid   = {0};
    CERT_USAGE_MATCH              um    = {0};
    CERT_TRUST_STATUS             tstat = {0};
    PFN_CERT_ENUM_SYSTEM_STORE          pfnss = m48_enum_system_store;
    PFN_CERT_ENUM_SYSTEM_STORE_LOCATION pfnsl = m48_enum_store_location;

    /* callback typedef shapes */
    (void) pfnss; (void) pfnsl;

    /* certificate store management */
    hStore = CertOpenStore((LPCSTR)0, 0, hProv, 0, (const void *)0);
    hStore = CertOpenSystemStore(hProv, (LPCTSTR)0);
    (void) CertCloseStore(hStore, 0);
    hStore = CertDuplicateStore(hStore);
    (void) CertControlStore(hStore, 0, 0, (const void *)0);
    (void) CertSaveStore(hStore, 0, 0, 0, (void *)0, 0);
    (void) CertGetStoreProperty(hStore, 0, (void *)0, &dw);
    (void) CertSetStoreProperty(hStore, 0, 0, (const void *)0);

    /* certificate context management */
    pCert = CertCreateCertificateContext(0, (const BYTE *)0, 0);
    pCert = CertDuplicateCertificateContext(pCert);
    (void) CertAddCertificateContextToStore(hStore, pCert, 0, &pCert);
    (void) CertAddCertificateLinkToStore(hStore, pCert, 0, &pCert);
    (void) CertAddEncodedCertificateToStore(hStore, 0, (const BYTE *)0, 0,
                                            0, &pCert);
    (void) CertDeleteCertificateFromStore(pCert);
    pCert = CertEnumCertificatesInStore(hStore, pCert);
    pCert = CertFindCertificateInStore(hStore, 0, 0, 0, (const void *)0,
                                       pCert);
    pCert = CertGetIssuerCertificateFromStore(hStore, pCert, pCert, &dw);
    pCert = CertGetSubjectCertificateFromStore(hStore, 0, &cinfo);
    (void) CertFreeCertificateContext(pCert);
    (void) CertGetCertificateContextProperty(pCert, 0, (void *)0, &dw);
    (void) CertSetCertificateContextProperty(pCert, 0, 0, (const void *)0);
    dw = CertEnumCertificateContextProperties(pCert, 0);
    (void) CertSerializeCertificateStoreElement(pCert, 0, buf, &dw);
    (void) CertAddSerializedElementToStore(hStore, (const BYTE *)0, 0, 0,
                                           0, 0, &dw, (const void **)0);

    /* certificate comparison / naming / properties */
    (void) CertCompareCertificate(0, &cinfo, &cinfo);
    (void) CertCompareCertificateName(0, &name, &name);
    (void) CertCompareIntegerBlob((PCRYPT_INTEGER_BLOB)0,
                                  (PCRYPT_INTEGER_BLOB)0);
    (void) CertComparePublicKeyInfo(0, &pki, &pki);
    dw = CertGetNameString(pCert, 0, 0, (void *)0, (LPTSTR)0, 0);
    dw = CertNameToStr(0, &name, 0, (LPTSTR)0, 0);
    dw = CertRDNValueToStr(0, (PCERT_RDN_VALUE_BLOB)0, (LPTSTR)0, 0);
    (void) CertStrToName(0, (LPCTSTR)0, 0, (void *)0, buf, &dw,
                         (LPCTSTR *)0);
    (void) CertIsRDNAttrsInCertificateName(0, 0, &name, (PCERT_RDN)0);
    (void) CertAddEnhancedKeyUsageIdentifier(pCert, (LPCSTR)0);
    (void) CertRemoveEnhancedKeyUsageIdentifier(pCert, (LPCSTR)0);
    (void) CertGetEnhancedKeyUsage(pCert, 0, &eku, &dw);
    (void) CertSetEnhancedKeyUsage(pCert, &eku);
    (void) CertGetIntendedKeyUsage(0, &cinfo, buf, 0);
    dw = CertGetPublicKeyLength(0, &pki);

    /* OID <-> algorithm id mapping */
    (void) CertAlgIdToOID(0);
    dw = CertOIDToAlgId((LPCSTR)0);

    /* find helpers */
    (void) CertFindAttribute((LPCSTR)0, 0, (CRYPT_ATTRIBUTE *)0);
    (void) CertFindExtension((LPCSTR)0, 0, (CERT_EXTENSION *)0);
    (void) CertFindRDNAttr((LPCSTR)0, &cname);

    /* enumeration callbacks */
    (void) CertEnumSystemStore(0, (void *)0, (void *)0, pfnss);
    (void) CertEnumSystemStoreLocation(0, (void *)0, pfnsl);
    (void) CertEnumPhysicalStore((const void *)0, 0, (void *)0,
                                 (PFN_CERT_ENUM_PHYSICAL_STORE)0);
    (void) CertGetValidUsages(0, &pCert, (int *)0, (LPSTR *)0, &dw);

    /* verification */
    (void) CertVerifySubjectCertificateContext(pCert, pCert, &dw);
    (void) CertVerifyTimeValidity(&ft, &cinfo);
    (void) CertVerifyValidityNesting(&cinfo, &cinfo);

    /* certificate chains */
    (void) CertGetCertificateChain((HCERTCHAINENGINE)0, pCert, &ft,
                                   hStore, &cpara, 0, (LPVOID)0, &pChain);
    pChain = CertDuplicateCertificateChain(pChain);
    CertFreeCertificateChain(pChain);

    /* key identifier / private key access */
    (void) CryptAcquireCertificatePrivateKey(pCert, 0, (void *)0, &hProv,
                                             &dw, (BOOL *)0);
    (void) CryptCreateKeyIdentifierFromCSP(0, (LPCSTR)0, &pks, 0, 0,
                                           (void *)0, buf, &dw);
    (void) CryptEnumKeyIdentifierProperties(&hash, 0, 0, (LPCWSTR)0,
                                            (void *)0, (void *)0,
                                            (PFN_CRYPT_ENUM_KEYID_PROP)0);
    (void) CryptGetKeyIdentifierProperty(&hash, 0, 0, (LPCWSTR)0,
                                         (void *)0, (void *)0, &dw);
    (void) CryptSetKeyIdentifierProperty(&hash, 0, 0, (LPCWSTR)0,
                                         (void *)0, (const void *)0);
    (void) CryptFindCertificateKeyProvInfo(pCert, 0, (void *)0);

    /* encode / decode */
    (void) CryptEncodeObjectEx(0, (LPCSTR)0, (const void *)0, 0,
                               &encpara, (void *)0, &dw);
    (void) CryptDecodeObjectEx(0, (LPCSTR)0, (const BYTE *)0, 0, 0,
                               (PCRYPT_DECODE_PARA)0, (void *)0, &dw);
    (void) CryptSignAndEncodeCertificate(hProv, 0, 0, (LPCSTR)0,
                                         (const void *)0, &algid,
                                         (const void *)0, (PBYTE)0, &dw);
    (void) CryptSignCertificate(hProv, 0, 0, (const BYTE *)0, 0, &algid,
                                (const void *)0, buf, &dw);
    (void) CryptVerifyCertificateSignature(hProv, 0, buf, 0, &pki);
    (void) CryptHashCertificate(hProv, 0, 0, (const BYTE *)0, 0, buf,
                                &dw);
    (void) CryptHashPublicKeyInfo(hProv, 0, 0, 0, &pki, buf, &dw);
    (void) CryptHashToBeSigned(hProv, 0, (const BYTE *)0, 0, buf, &dw);

    /* public key import/export */
    (void) CryptExportPublicKeyInfoEx(hProv, 0, 0, (LPSTR)0, 0,
                                      (void *)0, &pki, &dw);
    (void) CryptImportPublicKeyInfoEx(hProv, 0, &pki, 0, 0, (void *)0,
                                      &hKey);

    /* OID registry */
    (void) CryptFindOIDInfo(0, (void *)0, 0);
    (void) CryptEnumOIDInfo(0, 0, (void *)0,
                            (PFN_CRYPT_ENUM_OID_INFO)0);
    hFuncSet = CryptInitOIDFunctionSet((LPCSTR)0, 0);
    (void) CryptGetOIDFunctionAddress(hFuncSet, 0, (LPCSTR)0, 0,
                                      (void **)0, &hFuncAddr);
    (void) CryptGetDefaultOIDFunctionAddress(hFuncSet, 0, (LPCWSTR)0, 0,
                                             (void **)0, &hFuncAddr);
    (void) CryptInstallOIDFunctionAddress((HMODULE)0, 0, (LPCSTR)0, 0,
                                          &oidentry, 0);
    (void) CryptFreeOIDFunctionAddress(hFuncAddr, 0);

    /* default contexts */
    (void) CryptInstallDefaultContext(hProv, 0, (const void *)0, 0,
                                      (void *)0, &hDefCtx);
    (void) CryptUninstallDefaultContext(hDefCtx, 0, (void *)0);

    /* PFX */
    (void) PFXExportCertStoreEx(hStore, &data, (LPCWSTR)0, (void *)0, 0);
    hStore = PFXImportCertStore(&data, (LPCWSTR)0, 0);
    (void) PFXIsPFXBlob(&data);
    (void) PFXVerifyPassword(&data, (LPCWSTR)0, 0);

    /* keep the structure trees referenced */
    (void) cctx; (void) cext; (void) rattr; (void) srp; (void) cattr;
    (void) cattrs; (void) bits; (void) oidinfo; (void) kpi; (void) kpp;
    (void) sgn; (void) env; (void) hsd; (void) dec; (void) vsx;
    (void) sgni; (void) cmsi; (void) rcpt; (void) ktri; (void) mlri;
    (void) bh; (void) rsa; (void) pea; (void) peaex; (void) hmac;
    (void) cid; (void) um; (void) tstat; (void) ssi; (void) ceng;
    (void) dw;
    return 0;
}


/* ------------------------------------------------------------------ */
/* M49: Smart Card subsystem (winscard.h; Winscard.lib) -- the 28     */
/*      documented SCard* functions and the three documented          */
/*      structures.                                                   */
/* ------------------------------------------------------------------ */

/* Pointer-free smart-card layouts. */
_Static_assert(sizeof(SCARD_IO_REQUEST) == 8, "SCARD_IO_REQUEST size");
_Static_assert(sizeof(SCARD_ATRMASK) == 76, "SCARD_ATRMASK size");
#if __SIZEOF_POINTER__ == 4
_Static_assert(sizeof(SCARD_READERSTATE) == 56,
               "SCARD_READERSTATE 32-bit size");
#endif

static int m49_shaped_usage(void)
{
    SCARDCONTEXT    hContext = 0;
    SCARDHANDLE     hCard    = 0;
    DWORD           dw       = 0;
    BYTE            atr[36]  = {0};
    GUID            guid     = {0};
    SCARD_IO_REQUEST   io    = {0};
    SCARD_READERSTATE  rs    = {0};
    SCARD_ATRMASK      mask  = {0};

    /* resource-manager context */
    (void) SCardEstablishContext(0, (LPCVOID)0, (LPCVOID)0, &hContext);
    (void) SCardIsValidContext(hContext);
    (void) SCardReleaseContext(hContext);
    (void) SCardCancel(hContext);

    /* reader / card database */
    (void) SCardIntroduceReader(hContext, (LPCTSTR)0, (LPCTSTR)0);
    (void) SCardForgetReader(hContext, (LPCTSTR)0);
    (void) SCardIntroduceCardType(hContext, (LPCTSTR)0, &guid, &guid, 0,
                                  atr, atr, 0);
    (void) SCardForgetCardType(hContext, (LPCTSTR)0);
    (void) SCardSetCardTypeProviderName(hContext, (LPCTSTR)0, 0,
                                        (LPCTSTR)0);
    (void) SCardGetCardTypeProviderName(hContext, (LPCTSTR)0, 0,
                                        (LPTSTR)0, &dw);
    (void) SCardGetProviderId(hContext, (LPCTSTR)0, &guid);
    (void) SCardListReaders(hContext, (LPCTSTR)0, (LPTSTR)0, &dw);
    (void) SCardListCards(hContext, atr, (LPCGUID)0, 0, (LPTSTR)0, &dw);
    (void) SCardListInterfaces(hContext, (LPCTSTR)0, &guid, &dw);

    /* monitoring */
    (void) SCardGetStatusChange(hContext, 0, &rs, 0);
    (void) SCardLocateCards(hContext, (LPCTSTR)0, &rs, 0);
    (void) SCardLocateCardsByATR(hContext, &mask, 0, &rs, 0);

    /* card connect / transact */
    (void) SCardConnect(hContext, (LPCTSTR)0, 0, 0, &hCard, &dw);
    (void) SCardReconnect(hCard, 0, 0, 0, &dw);
    (void) SCardBeginTransaction(hCard);
    (void) SCardEndTransaction(hCard, 0);
    (void) SCardStatus(hCard, (LPTSTR)0, &dw, &dw, &dw, atr, &dw);
    (void) SCardGetAttrib(hCard, 0, atr, &dw);
    (void) SCardSetAttrib(hCard, 0, atr, 0);
    (void) SCardControl(hCard, 0, (LPCVOID)0, 0, (LPVOID)0, 0, &dw);
    (void) SCardTransmit(hCard, &io, atr, 0, &io, atr, &dw);
    (void) SCardDisconnect(hCard, 0);
    (void) SCardFreeMemory(hContext, (LPCVOID)0);
    return 0;
}


/* ------------------------------------------------------------------ */
/* M50: AYGShell unit (aygshell.h / shellsdk.h / newmenu.h /          */
/*      shlobj.h / extfile.h; Aygshell.lib) -- the 31 declared        */
/*      SH* functions, the documented structures and the dependency   */
/*      records (NMHDR, WM_NOTIFY/WM_SETTINGCHANGE in winuser.h,      */
/*      SHGetAutoRunPath in windows.h).                                */
/* ------------------------------------------------------------------ */

/* Pointer-free layouts. */
_Static_assert(sizeof(FILECHANGEINFO) == 36, "FILECHANGEINFO size");
#if __SIZEOF_POINTER__ == 4
_Static_assert(sizeof(NMHDR) == 12, "NMHDR 32-bit size");
_Static_assert(sizeof(FILECHANGENOTIFY) == 40,
               "FILECHANGENOTIFY 32-bit size");
_Static_assert(sizeof(SHACTIVATEINFO) == 12, "SHACTIVATEINFO 32-bit size");
_Static_assert(sizeof(SHCHANGENOTIFYENTRY) == 12,
               "SHCHANGENOTIFYENTRY 32-bit size");
_Static_assert(sizeof(SHINITDLGINFO) == 12, "SHINITDLGINFO 32-bit size");
_Static_assert(sizeof(SHMENUBARINFO) == 36, "SHMENUBARINFO 32-bit size");
_Static_assert(sizeof(SHNOTIFICATIONDATA) == 56,
               "SHNOTIFICATIONDATA 32-bit size");
_Static_assert(sizeof(SHRGINFO) == 20, "SHRGINFO 32-bit size");
_Static_assert(sizeof(NMNEWMENU) == 196, "NMNEWMENU 32-bit size");
#endif

static int m50_shaped_usage(void)
{
    HWND                hwnd      = (HWND)0;
    CLSID               clsid     = {0};
    GUID                guid      = {0};
    SHACTIVATEINFO      sai       = {0};
    SHMENUBARINFO       mbi       = {0};
    SHNOTIFICATIONDATA  nd        = {0};
    SHRGINFO            shrg      = {0};
    SHINITDLGINFO       shidi     = {0};
    SHCHANGENOTIFYENTRY shcne     = {0};
    NMNEWMENU           nmnm      = {0};
    FILECHANGENOTIFY    fcn       = {0};
    NMHDR               nmh       = {0};
    TCHAR               buf[MAX_PATH] = {0};
    HPROPSHEETPAGE      hpsp      = 0;
    IShellPropSheetExt *ispse     = 0;
    IUnknown           *punk      = 0;
    IPropertyBag       *ppb       = 0;
    HANDLE              hCMExt    = 0;
    int                 cPages    = 0;
    BYTE                vk        = 0;

    /* dialog / full-screen / input-panel management */
    shidi.dwMask = SHIDIM_FLAGS;
    shidi.hDlg = hwnd;
    (void) SHInitDialog(&shidi);
    (void) SHInitExtraControls();
    (void) SHFullScreen(hwnd, 0);
    (void) SHDoneButton(hwnd, 0);
    (void) SHInputDialog(hwnd, WM_ACTIVATE, 0);
    (void) SHHandleWMActivate(hwnd, 0, 0, &sai, 0);
    (void) SHHandleWMSettingChange(hwnd, 0, 0, &sai);
    (void) SHSipInfo(0, 0, (PVOID)0, 0);

    /* menu bar */
    (void) SHCreateMenuBar(&mbi);
    (void) SHFindMenuBar(hwnd);
    (void) SHSetNavBarText(hwnd, (LPCTSTR)0);

    /* New button / context menus */
    (void) SHCreateNewItem(hwnd, &clsid);
    (void) SHLoadContextMenuExtensions(punk, (LPCTSTR)0, (LPCTSTR)0,
                                       (HMENU)0, 0, 0, &hCMExt);
    (void) SHInvokeContextMenuCommand(hwnd, 0, hCMExt);
    (void) SHFreeContextMenuExtensions(hCMExt);

    /* property-sheet handler enumeration (stub on plain CE) */
    (void) SHEnumPropSheetHandlers((HKEY)0, &cPages, &hpsp, &ispse);

    /* notifications */
    nd.clsid = clsid;
    nd.npPriority = SHNP_ICONIC;
    (void) SHNotificationAdd(&nd);
    (void) SHNotificationGetData(&clsid, 0, &nd);
    (void) SHNotificationUpdate(0, &nd);
    (void) SHNotificationRemove(&clsid, 0);

    /* gestures */
    shrg.hwndClient = hwnd;
    (void) SHRecognizeGesture(&shrg);

    /* application-key / memory / back navigation */
    (void) SHSetAppKeyWndAssoc(vk, hwnd);
    (void) SHGetAppKeyAssoc((LPCTSTR)0);
    (void) SHCloseApps(0);
    (void) SHNavigateBack();
    (void) SHSetBack(0, hwnd);

    /* input context (stub on plain CE) */
    (void) SHGetInputContext(hwnd, 0, (LPVOID)0, (LPDWORD)0);
    (void) SHSetInputContext(hwnd, 0, (const LPVOID)0);

    /* file change notifications (WM_FILECHANGEINFO layer) */
    (void) SHChangeNotifyRegister(hwnd, &shcne);
    (void) SHChangeNotifyDeregister(hwnd);
    (void) SHChangeNotifyFree(&fcn);

    /* autorun path (windows.h home; aygshell.lib link row) */
    (void) SHGetAutoRunPath(buf);

    /* emergency call list (stub on plain CE) */
    (void) SHGetEmergencyCallList(buf, MAX_PATH);

    /* NMNEWMENU / NMHDR / WM_NOTIFY layer */
    nmnm.hdr = nmh;
    nmnm.clsid = guid;
    nmnm.pppropbag = &ppb;
    (void) nmnm;
    (void) WM_NOTIFY;
    (void) WM_SETTINGCHANGE;
    (void) WC_SIPPREF;
    return 0;
}


/* ------------------------------------------------------------------ */
/* M51: Software-based Input Panel unit.                                */
/*      sipapi.h (SIPINFO, IMENUMINFO, IMENUMPROC, the nine Sip*      */
/*      Coredll.lib functions + the application-defined               */
/*      SipEnumIMProc callback shape) and sip.h (IMINFO, LMDATA, the  */
/*      IIMCallback / IIMCallback2 / IInputMethod / IInputMethod2     */
/*      interface records; WM_IM_INFO record in winuser.h).           */
/* ------------------------------------------------------------------ */

/* Pointer-free layouts. */
_Static_assert(sizeof(LMDATA) == 24, "LMDATA size");
#if __SIZEOF_POINTER__ == 4
_Static_assert(sizeof(SIPINFO) == 48, "SIPINFO 32-bit size");
_Static_assert(sizeof(IMENUMINFO) == 536, "IMENUMINFO 32-bit size");
_Static_assert(sizeof(IMINFO) == 40, "IMINFO 32-bit size");
#endif

static int m51_shaped_usage(void)
{
    HWND           hwnd  = (HWND)0;
    CLSID          clsid = {0};
    SIPINFO        si    = {0};
    IMENUMINFO     iei   = {0};
    IMINFO         imi   = {0};
    LMDATA         lmd   = {0};
    RECT           rc    = {0, 0, 0, 0};
    IMENUMPROC     pEnumIMProc = SipEnumIMProc;

    /* application layer (Sipapi.h / Coredll.lib) */
    si.cbSize = sizeof(si);
    iei.clsid = clsid;
    imi.cbSize = sizeof(imi);
    lmd.dwVersion = 0x00010000;
    (void) SipEnumIM(pEnumIMProc);
    (void) SipEnumIM(NULL);
    (void) SipEnumIMProc(&iei);
    (void) SipGetCurrentIM(&clsid);
    (void) SipGetInfo(&si);
    (void) SipRegisterNotification(hwnd);
    (void) SipSetCurrentIM(&clsid);
    (void) SipSetDefaultRect(&rc);
    (void) SipSetInfo(&si);
    (void) SipShowIM(0);
    (void) SipStatus();

    /* IM/IME layer (Sip.h): the four interfaces are opaque tags with
     * documented method records (M44 model) -- only pointer use is
     * compilable here. */
    {
        IIMCallback    *piimcb  = (IIMCallback *)0;
        IIMCallback2   *piimcb2 = (IIMCallback2 *)0;
        IInputMethod   *piim    = (IInputMethod *)0;
        IInputMethod2  *piim2   = (IInputMethod2 *)0;
        (void) piimcb;
        (void) piimcb2;
        (void) piim;
        (void) piim2;
        (void) imi;
        (void) lmd;
    }
    return 0;
}


/* ------------------------------------------------------------------ */
/* M52: OEM keyboard / virtual-key / derived-value unit.               */
/*      winuser.h (VK_* set incl. OEM/DBE/manufacturer tables,        */
/*      KEYEVENTF_ and INPUT_ derived values, PostKeybdMessage),     */
/*      keybd.h (KEY_STATE_FLAGS), pwinuser.h (GET_FOREGROUND_INFO +  */
/*      the five OEM functions), aygshell.h (SIPSTATE +               */
/*      SHSipPreference, SHIC_FEATURE, VK_APP1-6; all M52             */
/*      derivations with recorded paths).                             */
/* ------------------------------------------------------------------ */

/* Published-value spot checks (ms927178 / aa452679 / derivations). */
_Static_assert(VK_RETURN == 0x0D, "VK_RETURN");
_Static_assert(VK_ESCAPE == 0x1B, "VK_ESCAPE");
_Static_assert(VK_LWIN == 0x5B, "VK_LWIN");
_Static_assert(VK_F22 == 0x85, "VK_F22");
_Static_assert(VK_NUMLOCK == 0x90, "VK_NUMLOCK");
_Static_assert(VK_PACKET == 0xE7, "VK_PACKET");
_Static_assert(VK_OEM_CLEAR == 0xFE, "VK_OEM_CLEAR");
_Static_assert(VK_KEYLOCK == 0x85, "VK_KEYLOCK (derived)");
_Static_assert(VK_DBE_ALPHANUMERIC == 0xF0, "VK_DBE_ALPHANUMERIC");
_Static_assert(VK_DBE_NOCODEINPUT == 0xFB, "VK_DBE_NOCODEINPUT");
_Static_assert(VK_ERICSSON_BASE == 0xE8, "VK_ERICSSON_BASE");
_Static_assert(VK_OEM_BACKTAB == (VK_ERICSSON_BASE + 13), "VK_OEM_BACKTAB");
_Static_assert(VK_APP1 == 0xC1 && VK_APP6 == 0xC6, "VK_APP1-6 (derived)");
_Static_assert(KEYEVENTF_EXTENDEDKEY == 0x0001, "KEYEVENTF_EXTENDEDKEY (derived)");
_Static_assert(KEYEVENTF_KEYUP == 0x0002, "KEYEVENTF_KEYUP (derived)");
_Static_assert(INPUT_MOUSE == 0 && INPUT_KEYBOARD == 1 && INPUT_HARDWARE == 2,
               "INPUT_* (derived)");
_Static_assert(SIP_UP == 0 && SIP_DOWN == 1 && SIP_FORCEDOWN == 2 &&
               SIP_UNCHANGED == 3 && SIP_INPUTDIALOG == 4,
               "SIPSTATE (derived)");
_Static_assert(SHIC_FEATURE_RESTOREDEFAULT == 0 &&
               SHIC_FEATURE_AUTOCORRECT == 0x00000001 &&
               SHIC_FEATURE_CLASS == 0x00000004,
               "SHIC_FEATURE (derived)");

/* Pointer-free layouts. */
#if __SIZEOF_POINTER__ == 4
_Static_assert(sizeof(GET_FOREGROUND_INFO) == 36,
               "GET_FOREGROUND_INFO 32-bit size");
#endif

static int m52_shaped_usage(void)
{
    HWND               hwnd = (HWND)0;
    GET_FOREGROUND_INFO gfi;
    KEY_STATE_FLAGS    ksf;
    UINT               shift = 0;
    UINT               chars = 0;

    gfi.hwndActive = hwnd;
    ksf = (KEY_STATE_FLAGS)0;

    /* winuser.h keyboard layer (Kbdui.lib) */
    (void) PostKeybdMessage(hwnd, VK_RETURN, ksf, 0, &shift, &chars);
    (void) keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
    {
        INPUT inp;
        inp.type = INPUT_KEYBOARD;
        inp.ki.wVk = VK_RETURN;
        (void) inp;
    }

    /* pwinuser.h OEM layer */
    (void) GetAsyncShiftFlags(VK_RETURN);
    (void) GetForegroundInfo(&gfi);
    (void) GetForegroundKeyboardLayoutHandle();
    (void) GetForegroundKeyboardTarget();
    (void) KeybdGetDeviceInfo(0, (LPVOID)0);

    /* aygshell.h derived unit */
    (void) SHSipPreference(hwnd, SIP_UP);
    (void) SHSipPreference(hwnd, SIP_INPUTDIALOG);
    (void) SHSetAppKeyWndAssoc((BYTE)VK_APP1, hwnd);
    {
        SHIC_FEATURE f = SHIC_FEATURE_AUTOSUGGEST;
        (void) f;
    }
    return 0;
}



/* ------------------------------------------------------------------ */
/* M53: Standard Shell Reference book + WM gesture supplement.         */
/*      shlobj.h (ITEMIDLIST, BROWSEINFO, folder functions, CSIDL),    */
/*      shobjidl.h (interface records, SHGNO, SFGAO/SVSI/SVGIO),       */
/*      shtypes.h (SHITEMID, STRRET), shellapi.h (NOTIFYICONDATA,      */
/*      SHELLEXECUTEINFO, SHFILEINFO, SHFILEOPSTRUCT + functions),     */
/*      cpl.h (CPlApplet, CPLINFO, NEWCPLINFO), shelwapi.h             */
/*      (StrRetToBuf), windowsx.h (MapWindowRect), commdlg.h           */
/*      (WM_CHOOSEFONT_GETLOGFONT), winuser.h (WM_KEYFIRST),           */
/*      aygshell.h (NMRGINFO + GN_CONTEXTMENU record), commctrl.h      */
/*      (NM_RECOGNIZEGESTURE record).                                  */
/* ------------------------------------------------------------------ */

/* Published-value spot checks (aa453707 CSIDL table, ms909872 SFGAO
 * "Flag (value)" tables, aa453709 SHGDN_NORMAL remark; desktop
 * fixed-ABI derivations recorded in docs/inventory.md M53). */
_Static_assert(CSIDL_DESKTOP == 0x0000, "CSIDL_DESKTOP");
_Static_assert(CSIDL_PROGRAMS == 0x0002, "CSIDL_PROGRAMS");
_Static_assert(CSIDL_PERSONAL == 0x0005, "CSIDL_PERSONAL");
_Static_assert(CSIDL_MYMUSIC == 0x000D, "CSIDL_MYMUSIC");
_Static_assert(CSIDL_APPDATA == 0x001A, "CSIDL_APPDATA");
_Static_assert(CSIDL_WINDOWS == 0x0024, "CSIDL_WINDOWS");
_Static_assert(CSIDL_MYPICTURES == 0x0027, "CSIDL_MYPICTURES");
_Static_assert(SFGAO_CANCOPY == 0x00000001, "SFGAO_CANCOPY");
_Static_assert(SFGAO_CANDELETE == 0x00000020, "SFGAO_CANDELETE");
_Static_assert(SFGAO_FOLDER == 0x20000000, "SFGAO_FOLDER");
_Static_assert(SFGAO_FILESYSTEM == 0x40000000, "SFGAO_FILESYSTEM");
_Static_assert(SFGAO_CAPABILITYMASK == 0x00000177, "SFGAO_CAPABILITYMASK");
_Static_assert(SHGDN_NORMAL == 0, "SHGDN_NORMAL (published)");
_Static_assert(NIF_MESSAGE == 0x1 && NIF_ICON == 0x2 && NIF_TIP == 0x4,
               "NIF_* (derived)");
_Static_assert(NIM_ADD == 0x0 && NIM_MODIFY == 0x1 && NIM_DELETE == 0x2,
               "NIM_* (derived)");
_Static_assert(SEE_MASK_NOCLOSEPROCESS == 0x40 &&
               SEE_MASK_FLAG_NO_UI == 0x400, "SEE_MASK_* (derived)");
_Static_assert(SE_ERR_FNF == 2 && SE_ERR_DLLNOTFOUND == 32,
               "SE_ERR_* (derived)");
_Static_assert(SHGFI_ICON == 0x100 && SHGFI_SYSICONINDEX == 0x4000 &&
               SHGFI_SELECTED == 0x10000, "SHGFI_* (derived)");
_Static_assert(BIF_STATUSTEXT == 0x4 && BIF_EDITBOX == 0x10 &&
               BIF_VALIDATE == 0x20, "BIF_* (derived)");
_Static_assert(SVSI_SELECT == 0x1 && SVSI_CHECK == 0x100,
               "SVSI_* (derived)");
_Static_assert(SVGIO_SELECTION == 0x1 && SVGIO_TYPE_MASK == 0xF,
               "SVGIO_* (derived)");
_Static_assert(WM_KEYFIRST == 0x0100, "WM_KEYFIRST (derived)");
_Static_assert(WM_CHOOSEFONT_GETLOGFONT == (WM_USER + 1),
               "WM_CHOOSEFONT_GETLOGFONT (derived formula)");

/* Pointer-free layouts (32-bit). */
#if __SIZEOF_POINTER__ == 4
_Static_assert(sizeof(CPLINFO) == 16, "CPLINFO 32-bit size");
_Static_assert(sizeof(NEWCPLINFO) == 468, "NEWCPLINFO 32-bit size");
_Static_assert(sizeof(SHFILEOPSTRUCT) == 32, "SHFILEOPSTRUCT 32-bit size");
_Static_assert(sizeof(BROWSEINFO) == 32, "BROWSEINFO 32-bit size");
_Static_assert(sizeof(SHFILEINFO) == 692, "SHFILEINFO 32-bit size");
_Static_assert(sizeof(NOTIFYICONDATA) == 152, "NOTIFYICONDATA 32-bit size");
_Static_assert(sizeof(SHELLEXECUTEINFO) == 60, "SHELLEXECUTEINFO 32-bit size");
_Static_assert(sizeof(SHITEMID) == 4, "SHITEMID 32-bit size");
_Static_assert(sizeof(ITEMIDLIST) == 4, "ITEMIDLIST 32-bit size");
_Static_assert(sizeof(NMRGINFO) == 24, "NMRGINFO 32-bit size");
#endif

/* ------------------------------------------------------------------ */
/* M54: Common Controls batch 1 (Common/Common Dialogs/Animation/      */
/* CapEdit/Command Bands/Command Bars/Custom Draw/Progress/SbEdit/    */
/* Status Bars/Toolbar/ToolTips/Trackbar/Up-Down + REBARBANDINFO),    */
/* LDAP Client (Winldap.h/Winber.h) and RDP (Cchannel.h/Pchannel.h/   */
/* Discodlg.h).                                                        */
/* ------------------------------------------------------------------ */

/* -- pointer-free layouts -- */
_Static_assert(sizeof(LDAP_TIMEVAL) == 8, "LDAP_TIMEVAL size");
_Static_assert(sizeof(CHANNEL_DEF) == 12, "CHANNEL_DEF size");
_Static_assert(sizeof(CHANNEL_PDU_HEADER) == 8, "CHANNEL_PDU_HEADER size");
_Static_assert(sizeof(INITCOMMONCONTROLSEX) == 8,
               "INITCOMMONCONTROLSEX size");
_Static_assert(sizeof(TBBUTTON) == 20, "TBBUTTON size");
_Static_assert(sizeof(PBRANGE) == 8, "PBRANGE size");
_Static_assert(sizeof(UDACCEL) == 8, "UDACCEL size");
_Static_assert(sizeof(DEVNAMES) == 8, "DEVNAMES size");
_Static_assert(sizeof(COMMANDBANDSRESTOREINFO) == 20,
               "COMMANDBANDSRESTOREINFO size");

#if __SIZEOF_POINTER__ == 4
/* -- 32-bit CE layouts containing handles or pointers -- */
_Static_assert(sizeof(BerElement) == 4, "BerElement 32-bit size");
_Static_assert(sizeof(BERVAL) == 8, "berval 32-bit size");
_Static_assert(sizeof(LDAPControl) == 16, "LDAPControl 32-bit size");
_Static_assert(sizeof(LDAPMod) == 12, "LDAPMod 32-bit size");
_Static_assert(sizeof(LDAPSortKey) == 12, "LDAPSortKey 32-bit size");
_Static_assert(sizeof(LDAP_REFERRAL_CALLBACK) == 16,
               "LDAP_REFERRAL_CALLBACK 32-bit size");
_Static_assert(sizeof(CHANNEL_ENTRY_POINTS) == 24,
               "CHANNEL_ENTRY_POINTS 32-bit size");
_Static_assert(sizeof(CHANNEL_ENTRY_POINTS_EX) == 24,
               "CHANNEL_ENTRY_POINTS_EX 32-bit size");
_Static_assert(sizeof(NMKEY) == 20, "NMKEY 32-bit size");
_Static_assert(sizeof(NMMOUSE) == 28, "NMMOUSE 32-bit size");
_Static_assert(sizeof(NMCUSTOMDRAW) == 48, "NMCUSTOMDRAW 32-bit size");
_Static_assert(sizeof(NMTTCUSTOMDRAW) == 52, "NMTTCUSTOMDRAW 32-bit size");
_Static_assert(sizeof(TBBUTTONINFOA) == 32, "TBBUTTONINFO 32-bit size");
_Static_assert(sizeof(TBADDBITMAP) == 8, "TBADDBITMAP 32-bit size");
_Static_assert(sizeof(TBREPLACEBITMAP) == 20, "TBREPLACEBITMAP 32-bit size");
_Static_assert(sizeof(NMTOOLBAR) == 44, "NMTOOLBAR 32-bit size");
_Static_assert(sizeof(TTTOOLINFO) == 44, "TOOLINFO 32-bit size");
_Static_assert(sizeof(TTHITTESTINFO) == 56, "TTHITTESTINFO 32-bit size");
_Static_assert(sizeof(NMTTDISPINFO) == 188, "NMTTDISPINFO 32-bit size");
_Static_assert(sizeof(NMUPDOWN) == 20, "NMUPDOWN 32-bit size");
_Static_assert(sizeof(REBARBANDINFO) == 76, "REBARBANDINFO 32-bit size");
#endif

/* -- winldap.h values (ms892299 LDAP_RETCODE, ms892279, ms893453) -- */
_Static_assert(LDAP_SUCCESS == 0x00, "LDAP_SUCCESS value");
_Static_assert(LDAP_REFERRAL_V2 == 0x09 && LDAP_PARTIAL_RESULTS == 0x09,
               "LDAP_REFERRAL_V2/LDAP_PARTIAL_RESULTS values");
_Static_assert(LDAP_REFERRAL == 0x0a, "LDAP_REFERRAL value");
_Static_assert(LDAP_REFERRAL_LIMIT_EXCEEDED == 0x61,
               "LDAP_RETCODE last member value");
_Static_assert(LDAP_MOD_ADD == 0x00 && LDAP_MOD_DELETE == 0x01 &&
               LDAP_MOD_REPLACE == 0x02, "LDAP_MOD_* values");
_Static_assert(LDAP_OPT_DESC == 0x01 && LDAP_OPT_DEREF == 0x02 &&
               LDAP_OPT_SIZELIMIT == 0x03 && LDAP_OPT_TIMELIMIT == 0x04 &&
               LDAP_OPT_REFERRALS == 0x08 && LDAP_OPT_RESTART == 0x09 &&
               LDAP_OPT_SSL == 0x0a &&
               LDAP_OPT_REFERRAL_HOP_LIMIT == 0x10 &&
               LDAP_OPT_PROTOCOL_VERSION == 0x11 &&
               LDAP_OPT_VERSION == 0x11, "LDAP_OPT_* core values");
_Static_assert(LDAP_OPT_HOST_NAME == 0x30 &&
               LDAP_OPT_ERROR_NUMBER == 0x31 &&
               LDAP_OPT_ERROR_STRING == 0x32 &&
               LDAP_OPT_SERVER_ERROR == 0x33 &&
               LPDA_OPT_SERVER_EXT_ERROR == 0x34 &&
               LDAP_OPT_DNSDOMAIN_NAME == 0x3B &&
               LDAP_OPT_HOST_REACHABLE == 0x3E &&
               LDAP_OPT_PROMPT_CREDENTIALS == 0x3F &&
               LDAP_OPT_AUTO_RECONNECT == 0x91 &&
               LDAP_OPT_SSPI_FLAGS == 0x92 &&
               LDAP_OPT_AREC_EXCLUSIVE == 0x98, "LDAP_OPT_* extended values");
_Static_assert(PING_KEEP_ALIVE == 0x36 && PING_WAIT_TIME == 0x37 &&
               PING_LIMIT == 0x38, "PING_* values");
_Static_assert(LDAP_DEREF_NEVER == 0x00 && LDAP_DEREF_SEARCHING == 0x01 &&
               LDAP_DEREF_FINDING == 0x02 && LDAP_DEREF_ALWAYS == 0x03,
               "LDAP_DEREF_* values");
_Static_assert(LDAP_NO_LIMIT == 0, "LDAP_NO_LIMIT value");
_Static_assert(LBER_USE_DER == 0x01, "LBER_USE_DER value");

/* -- discodlg.h enumeration (aa513913) -- */
_Static_assert(exDiscReasonNoInfo == 0x0000 &&
               exDiscReasonServerDeniedConnection == 0x0007 &&
               exDiscReasonLicenseInternal == 0x0100 &&
               exDiscReasonLicenseNoRemoteConnections == 0x010A,
               "ExtendedDisconnectReasonCode values");

/* -- cchannel.h derived values (aa513856/aa513859/aa513858/aa513861
 *    + MS-RDPBCGR 2.2.1.3.4.1 / 2.2.6.1.1) -- */
_Static_assert(CHANNEL_NAME_LEN == 7, "CHANNEL_NAME_LEN derived value");
_Static_assert(CHANNEL_OPTION_INITIALIZED == 0x80000000 &&
               CHANNEL_OPTION_ENCRYPT_RDP == 0x40000000 &&
               CHANNEL_OPTION_ENCRYPT_SC == 0x20000000 &&
               CHANNEL_OPTION_ENCRYPT_CS == 0x10000000 &&
               CHANNEL_OPTION_PRI_HIGH == 0x08000000 &&
               CHANNEL_OPTION_PRI_MED == 0x04000000 &&
               CHANNEL_OPTION_PRI_LOW == 0x02000000 &&
               CHANNEL_OPTION_COMPRESS_RDP == 0x00800000 &&
               CHANNEL_OPTION_COMPRESS == 0x00400000 &&
               CHANNEL_OPTION_SHOW_PROTOCOL == 0x00200000 &&
               CHANNEL_OPTION_REMOTE_CONTROL_PERSISTENT == 0x00100000,
               "CHANNEL_OPTION_* derived values");
_Static_assert(CHANNEL_FLAG_FIRST == 0x1 && CHANNEL_FLAG_LAST == 0x2 &&
               CHANNEL_FLAG_MIDDLE == 0x0 &&
               CHANNEL_FLAG_ONLY == (CHANNEL_FLAG_FIRST | CHANNEL_FLAG_LAST),
               "CHANNEL_FLAG_* derived values");

#if __SIZEOF_POINTER__ == 4
/* -- commdlg.h 32-bit CE layouts -- */
_Static_assert(sizeof(CHOOSECOLOR) == 36, "CHOOSECOLOR 32-bit size");
_Static_assert(sizeof(CHOOSEFONTW) == 60, "CHOOSEFONT 32-bit size");
_Static_assert(sizeof(OPENFILENAME) == 76, "OPENFILENAME 32-bit size");
_Static_assert(sizeof(OFNOTIFY) == 20, "OFNOTIFY 32-bit size");
_Static_assert(sizeof(PAGESETUPDLG) == 84, "PAGESETUPDLG 32-bit size");
_Static_assert(sizeof(PRINTDLG) == 68, "PRINTDLG 32-bit size");
#endif

/* -- winuser.h M54 controls messages (fixed-ABI values, M29 policy) -- */
_Static_assert(WM_SETFONT == 0x0030, "WM_SETFONT fixed-ABI value");
_Static_assert(WM_GETFONT == 0x0031, "WM_GETFONT fixed-ABI value");

static int m54_shaped_usage(void)
{
    INITCOMMONCONTROLSEX   icc;
    CHOOSECOLOR            cc;
    CHOOSEFONTW            cf;
    OPENFILENAME           ofn;
    PAGESETUPDLG           psd;
    PRINTDLG               pd;
    LDAPControl            lc;
    LDAPMod                lm;
    LDAP_TIMEVAL           tv;
    LDAPSortKey            sk;
    struct berval          bv;
    LDAP_REFERRAL_CALLBACK rcb;
    CHANNEL_DEF            cdef;
    CHANNEL_PDU_HEADER     cpdu;
    CHANNEL_ENTRY_POINTS   cep;
    CHANNEL_ENTRY_POINTS_EX cepx;
    REBARBANDINFO          rbbi;
    COMMANDBANDSRESTOREINFO cbri;
    TBBUTTON               tbb;
    TBBUTTONINFOA          tbbi;
    TBADDBITMAP            tbab;
    NMTOOLBAR              nmtb;
    TTTOOLINFO             tti;
    TTHITTESTINFO          ttht;
    NMTTDISPINFO           nttdi;
    NMCUSTOMDRAW           nmcd;
    PBRANGE                pbr;
    NMUPDOWN               nmud;
    UDACCEL                uda;
    ExtendedDisconnectReasonCode exd;
    LDAP                  *ld = (LDAP *)0;
    BerElement            *be = (BerElement *)0;
    BERVAL                *bvp = (BERVAL *)0;
    HWND                   hwnd = (HWND)0;
    HINSTANCE              hinst = (HINSTANCE)0;
    HIMAGELIST             himl = (HIMAGELIST)0;
    int                    id = 0; /* the printed FORWARD_WM_NOTIFY body
                                     * references (id); see commctrl.h */
    void                 (*fn)(HWND, int, NMHDR *) =
                             (void (*)(HWND, int, NMHDR *))0;
    void                 (*fn4)(HWND, UINT, WPARAM, LPARAM) =
                             (void (*)(HWND, UINT, WPARAM, LPARAM))0;
    NMHDR                  nmh;

    icc.dwSize   = sizeof(INITCOMMONCONTROLSEX);
    cc.lStructSize = sizeof(CHOOSECOLOR);
    cf.lStructSize = sizeof(CHOOSEFONTW);
    ofn.lStructSize = sizeof(OPENFILENAME);
    psd.lStructSize = sizeof(PAGESETUPDLG);
    pd.cbStruct  = sizeof(PRINTDLG);
    lc.ldctl_iscritical = (BOOLEAN)1;
    lm.mod_op    = LDAP_MOD_REPLACE;
    tv.tv_sec    = 0;
    sk.sk_reverseorder = (BOOLEAN)0;
    bv.bv_len    = 0;
    rcb.SizeOfCallbacks = sizeof(rcb);
    cdef.options = CHANNEL_OPTION_SHOW_PROTOCOL;
    cpdu.flags   = CHANNEL_FLAG_FIRST | CHANNEL_FLAG_LAST;
    cep.cbSize   = sizeof(cep);
    cepx.cbSize  = sizeof(cepx);
    rbbi.cbSize  = sizeof(REBARBANDINFO);
    cbri.cbSize  = sizeof(COMMANDBANDSRESTOREINFO);
    tbb.idCommand = 0;
    tbbi.cbSize  = sizeof(TBBUTTONINFOA);
    tbab.nID     = 0;
    nmtb.iItem   = 0;
    tti.cbSize   = sizeof(TTTOOLINFO);
    ttht.hwnd    = hwnd;
    nttdi.hdr.code = 0;
    nmcd.dwDrawStage = 0;
    pbr.iLow     = 0;
    nmud.iDelta  = 0;
    uda.nInc     = 0;
    exd          = exDiscReasonServerDeniedConnection;
    nmh.code     = 0;

    /* Commctrl.lib import surface (M54 batch). */
    (void) InitCommonControls();
    (void) InitCommonControlsEx(&icc);
    (void) CommandBar_Create(hinst, hwnd, 1);
    (void) CommandBar_AddAdornments(hwnd, 0, 0);
    (void) CommandBar_AddBitmap(hwnd, hinst, 0, 0, 16, 16);
    (void) CommandBar_AlignAdornments(hwnd);
    (void) CommandBar_DrawMenuBar(hwnd, 0);
    (void) CommandBar_GetMenu(hwnd, 0);
    (void) CommandBar_Height(hwnd);
    (void) CommandBar_InsertComboBox(hwnd, hinst, 100, 0, 1, 0);
    (void) CommandBar_InsertMenubar(hwnd, hinst, 1, 0);
    (void) CommandBar_InsertMenubarEx(hwnd, hinst, (LPTSTR)L"MENU", 0);
    (void) CommandBar_Show(hwnd, TRUE);
    (void) CommandBands_Create(hinst, hwnd, 1, 0, himl);
    (void) CommandBands_AddAdornments(hwnd, hinst, 0, &rbbi);
    (void) CommandBands_AddBands(hwnd, hinst, 1, &rbbi);
    (void) CommandBands_GetCommandBar(hwnd, 0);
    (void) CommandBands_GetRestoreInformation(hwnd, 0, &cbri);
    (void) CommandBands_Show(hwnd, TRUE);
    (void) CreateStatusWindow(0, (LPSTR)0, hwnd, 1);
    (void) DrawStatusText((HDC)0, (LPRECT)0, (LPCWSTR)0, 0);
    (void) CreateToolbarEx(hwnd, 0, 1, 1, hinst, 0, &tbb, 1, 16, 16,
                           16, 16, sizeof(TBBUTTON));
    (void) CreateUpDownControl(0, 0, 0, 10, 10, hwnd, 1, hinst, hwnd,
                               100, 0, 50);

    /* Wldap32.lib import surface. */
    (void) cldap_open((PTCHAR)0, 389);
    (void) ldap_init((PTCHAR)0, 389);
    (void) ldap_open((PTCHAR)0, 389);
    (void) ldap_sslinit((PTCHAR)0, 389, 0);
    (void) ldap_unbind(ld);
    (void) ldap_unbind_s(ld);
    (void) ldap_connect(ld, (PLDAP_TIMEVAL *)&tv);
    (void) ldap_get_option(ld, LDAP_OPT_DESC, (void *)0);
    (void) ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, (void *)0);
    (void) ldap_simple_bind(ld, (PTCHAR)0, (PTCHAR)0);
    (void) ldap_simple_bind_s(ld, (PTCHAR)0, (PTCHAR)0);
    (void) ldap_search_s(ld, (PTCHAR)0, 0, (PTCHAR)0,
                         (PTCHAR *)0, 0, (LDAPMessage **)0);
    (void) ldap_first_entry(ld, (LDAPMessage *)0);
    (void) ldap_next_entry(ld, (LDAPMessage *)0);
    (void) ldap_count_entries(ld, (LDAPMessage *)0);
    (void) ldap_msgfree((LDAPMessage *)0);
    (void) ldap_get_values(ld, (LDAPMessage *)0, (PTCHAR)0);
    (void) ldap_get_values_len(ld, (LDAPMessage *)0, (PTCHAR)0);
    (void) ldap_value_free((PTCHAR *)0);
    (void) ldap_value_free_len((struct berval **)0);
    (void) ldap_control_free(&lc);
    (void) ldap_controls_free((LDAPControl **)0);
    (void) ldap_explode_dn((PTCHAR)0, 0);
    (void) ldap_dn2ufn((PTCHAR)0);
    (void) ldap_err2string(LDAP_PROTOCOL_ERROR);
    (void) ldap_result2error(ld, (LDAPMessage *)0, 0);
    (void) LdapGetLastError();
    (void) LdapMapErrorToWin32(LDAP_SERVER_DOWN);
    (void) LdapUnicodeToUTF8((LPCWSTR)0, 0, (LPSTR)0, 0);
    (void) LdapUTF8ToUnicode((LPCSTR)0, 0, (LPWSTR)0, 0);
    (void) ber_alloc_t(LBER_USE_DER);
    (void) ber_init(bvp);
    (void) ber_free(be, 0);
    (void) ber_bvfree(bvp);
    (void) ber_bvecfree((BERVAL **)0);
    (void) ber_printf(be, (PTCHAR)0, 0);
    (void) ber_scanf(be, (PTCHAR)0, 0);

    /* Cchannel developer-implemented surface (no def; compile-only). */
    (void) VirtualChannelEntry(&cep);
    (void) VirtualChannelInitEvent((LPVOID)0, 0, (LPVOID)0, 0);
    (void) VirtualChannelOpenEvent(0, 0, (LPVOID)0, 0, 0, 0);

    /* Commdlg/Fileopen import surface. */
    (void) ChooseColor(&cc);
    (void) ChooseFont((LPCHOOSEFONT)&cf);
    (void) CommDlgExtendedError();
    (void) GetOpenFileName(&ofn);
    (void) GetSaveFileName(&ofn);
    (void) PageSetupDlg(&psd);
    (void) PrintDlg(&pd);
    (void) CCHookProc((HWND)0, 0, (WPARAM)0, (LPARAM)0);
    (void) PagePaintHook((HWND)0, 0, (WPARAM)0, (LPARAM)0);
    (void) PageSetupHook((HWND)0, 0, (WPARAM)0, (LPARAM)0);
    (void) PrintHookProc((HWND)0, 0, (WPARAM)0, (LPARAM)0);

    /* Common-control macros with printed bodies. */
    (void) INDEXTOSTATEIMAGEMASK(3);
    (void) HANDLE_WM_NOTIFY(hwnd, (WPARAM)0, (LPARAM)&nmh, fn);
    (void) FORWARD_WM_NOTIFY(hwnd, id, &nmh, fn4);

    /* Class-name literals (aa452920 / ms939903). */
    (void) WC_CAPEDIT;
    (void) WC_SBEDIT;

    (void) himl; (void) bvp; (void) sk; (void) ttht; (void) nmcd;
    (void) nttdi; (void) nmtb; (void) tbab; (void) tbbi; (void) tbb;
    (void) cbri; (void) rbbi; (void) cepx; (void) cep; (void) cpdu;
    (void) cdef; (void) rcb; (void) bv; (void) lm; (void) lc; (void) exd;
    (void) id; (void) fn; (void) fn4; (void) nmh; (void) tti; (void) uda; (void) nmud;
    (void) pbr; (void) be; (void) ld; (void) pd; (void) psd; (void) ofn;
    (void) cf; (void) cc; (void) icc; (void) tv; (void) himl;
    return 0;
}

/* ------------------------------------------------------------------ */
/* M55: Property Sheets (Prsht.h; no Link Library rows -- the          */
/* Shell_NotifyIcon def-less precedent).                               */
/* ------------------------------------------------------------------ */
#if __SIZEOF_POINTER__ == 4
_Static_assert(sizeof(PROPSHEETPAGE) == 40, "PROPSHEETPAGE 32-bit size");
_Static_assert(sizeof(PROPSHEETHEADER) == 40, "PROPSHEETHEADER 32-bit size");
_Static_assert(sizeof(PSHNOTIFY) == 16, "PSHNOTIFY 32-bit size");
#endif

static int m55_shaped_usage(void)
{
    PROPSHEETPAGE    psp;
    PROPSHEETHEADER  psh;
    PSHNOTIFY        psn;
    HPROPSHEETPAGE   hpsp = (HPROPSHEETPAGE)0;

    psp.dwSize   = sizeof(PROPSHEETPAGE);
    psh.dwSize   = sizeof(PROPSHEETHEADER);
    psn.hdr.code = 0;
    (void) CreatePropertySheetPage(&psp);
    (void) DestroyPropertySheetPage(hpsp);
    (void) PropertySheet(&psh);
    (void) ExtensionPropSheetPageProc((LPVOID)0,
                                      (LPFNADDPROPSHEETPAGE)0, 0);
    (void) PropSheetPageProc((HWND)0, 0, &psp);
    (void) PropSheetProc((HWND)0, 0, 0);
    (void) AddPropSheetPageProc(hpsp, 0);
    (void) psn;
    return 0;
}


/* ------------------------------------------------------------------ */
/* M56: Common Controls batch 2 structures (Rebar, Header, Tab, DTP,   */
/* MonthCal, Tree View, List View; no Link Library rows).              */
/* ------------------------------------------------------------------ */
#if __SIZEOF_POINTER__ == 4
_Static_assert(sizeof(REBARINFO) == 12, "REBARINFO 32-bit size");
_Static_assert(sizeof(NMRBAUTOSIZE) == 48, "NMRBAUTOSIZE 32-bit size");
_Static_assert(sizeof(NMREBAR) == 28, "NMREBAR 32-bit size");
_Static_assert(sizeof(RBHITTESTINFO) == 16, "RBHITTESTINFO 32-bit size");
_Static_assert(sizeof(HDITEM) == 36, "HDITEM 32-bit size");
_Static_assert(sizeof(HD_LAYOUT) == 8, "HD_LAYOUT 32-bit size");
_Static_assert(sizeof(HD_HITTESTINFO) == 16, "HD_HITTESTINFO 32-bit size");
_Static_assert(sizeof(NMHDDISPINFO) == 36, "NMHDDISPINFO 32-bit size");
_Static_assert(sizeof(NMHEADER) == 24, "NMHEADER 32-bit size");
_Static_assert(sizeof(TCITEM) == 28, "TCITEM 32-bit size");
_Static_assert(sizeof(TCITEMHEADER) == 24, "TCITEMHEADER 32-bit size");
_Static_assert(sizeof(TCHITTESTINFO) == 12, "TCHITTESTINFO 32-bit size");
_Static_assert(sizeof(NMTCKEYDOWN) == 20, "NMTCKEYDOWN 32-bit size");
_Static_assert(sizeof(NMDATETIMECHANGE) == 32,
               "NMDATETIMECHANGE 32-bit size");
_Static_assert(sizeof(NMDATETIMEFORMAT) == 164,
               "NMDATETIMEFORMAT 32-bit size");
_Static_assert(sizeof(NMDATETIMEFORMATQUERY) == 24,
               "NMDATETIMEFORMATQUERY 32-bit size");
_Static_assert(sizeof(NMDATETIMESTRING) == 36,
               "NMDATETIMESTRING 32-bit size");
_Static_assert(sizeof(NMDATETIMEWMKEYDOWN) == 36,
               "NMDATETIMEWMKEYDOWN 32-bit size");
_Static_assert(sizeof(MCHITTESTINFO) == 32, "MCHITTESTINFO 32-bit size");
_Static_assert(sizeof(NMSELCHANGE) == 44, "NMSELCHANGE 32-bit size");
_Static_assert(sizeof(NMDAYSTATE) == 36, "NMDAYSTATE 32-bit size");
_Static_assert(sizeof(TVITEM) == 40, "TVITEM 32-bit size");
_Static_assert(sizeof(TV_INSERTSTRUCT) == 48,
               "TV_INSERTSTRUCT 32-bit size");
_Static_assert(sizeof(TV_HITTESTINFO) == 16,
               "TV_HITTESTINFO 32-bit size");
_Static_assert(sizeof(TVSORTCB) == 12, "TVSORTCB 32-bit size");
_Static_assert(sizeof(NM_TREEVIEW) == 104, "NM_TREEVIEW 32-bit size");
_Static_assert(sizeof(TV_DISPINFO) == 52, "TV_DISPINFO 32-bit size");
_Static_assert(sizeof(NMTVCUSTOMDRAW) == 56, "NMTVCUSTOMDRAW 32-bit size");
_Static_assert(sizeof(NMTVKEYDOWN) == 20, "NMTVKEYDOWN 32-bit size");
_Static_assert(sizeof(LVITEM) == 40, "LVITEM 32-bit size");
_Static_assert(sizeof(LVCOLUMN) == 32, "LVCOLUMN 32-bit size");
_Static_assert(sizeof(LVBKIMAGE) == 24, "LVBKIMAGE 32-bit size");
_Static_assert(sizeof(LVFINDINFO) == 24, "LVFINDINFO 32-bit size");
_Static_assert(sizeof(LVHITTESTINFO) == 20, "LVHITTESTINFO 32-bit size");
_Static_assert(sizeof(NMLISTVIEW) == 44, "NMLISTVIEW 32-bit size");
_Static_assert(sizeof(NMLVCACHEHINT) == 20, "NMLVCACHEHINT 32-bit size");
_Static_assert(sizeof(NMLVCUSTOMDRAW) == 80,
               "NMLVCUSTOMDRAW 32-bit size");
_Static_assert(sizeof(NMLVFINDITEM) == 40, "NMLVFINDITEM 32-bit size");
_Static_assert(sizeof(NMLVGETINFOTIP) == 36,
               "NMLVGETINFOTIP 32-bit size");
_Static_assert(sizeof(NMLVKEYDOWN) == 20, "NMLVKEYDOWN 32-bit size");
_Static_assert(sizeof(NMLVODSTATECHANGE) == 28,
               "NMLVODSTATECHANGE 32-bit size");
_Static_assert(sizeof(LV_DISPINFO) == 52, "LV_DISPINFO 32-bit size");
#endif

/* ------------------------------------------------------------------ */
/* M57: Bluetooth / SNMP / CEDDK wave (32-bit layout asserts).         */
/* ------------------------------------------------------------------ */
#if __SIZEOF_POINTER__ == 4
_Static_assert(sizeof(BASEBAND_CONNECTION) == 24,
               "BASEBAND_CONNECTION 32-bit size");
_Static_assert(sizeof(PORTEMUPortParams) == 56,
               "PORTEMUPortParams 32-bit size");
_Static_assert(sizeof(SOCKADDR_BTH) == 40, "SOCKADDR_BTH 32-bit size");
_Static_assert(sizeof(BTH_LOCAL_VERSION) == 18,
               "BTH_LOCAL_VERSION 32-bit size");
_Static_assert(sizeof(BTH_REMOTE_VERSION) == 14,
               "BTH_REMOTE_VERSION 32-bit size");
_Static_assert(sizeof(BTH_REMOTE_NAME) == 504,
               "BTH_REMOTE_NAME 32-bit size");
_Static_assert(sizeof(BTH_SOCKOPT_SECURITY) == 32,
               "BTH_SOCKOPT_SECURITY 32-bit size");
_Static_assert(sizeof(BTH_HOLD_MODE) == 6, "BTH_HOLD_MODE 32-bit size");
_Static_assert(sizeof(BTH_PARK_MODE) == 6, "BTH_PARK_MODE 32-bit size");
_Static_assert(sizeof(BTH_SNIFF_MODE) == 10, "BTH_SNIFF_MODE 32-bit size");
_Static_assert(sizeof(BthInquiryResult) == 24,
               "BthInquiryResult 32-bit size");
_Static_assert(sizeof(SdpQueryUuidUnion) == 16,
               "SdpQueryUuidUnion 32-bit size");
_Static_assert(sizeof(SdpQueryUuid) == 20, "SdpQueryUuid 32-bit size");
_Static_assert(sizeof(struct _SdpAttributeRange) == 4,
               "SdpAttributeRange 32-bit size");
_Static_assert(sizeof(BTHNS_RESTRICTIONBLOB) == 256,
               "BTHNS_RESTRICTIONBLOB 32-bit size");
_Static_assert(sizeof(BTHNS_INQUIRYBLOB) == 8,
               "BTHNS_INQUIRYBLOB 32-bit size");
_Static_assert(sizeof(BTHNS_SETBLOB) == 20, "BTHNS_SETBLOB 32-bit size");
_Static_assert(MAX_UUIDS_IN_QUERY == 12, "MAX_UUIDS_IN_QUERY derived 12");
_Static_assert(sizeof(AsnObjectIdentifier) == 8,
               "AsnObjectIdentifier 32-bit size");
_Static_assert(sizeof(AsnOctetString) == 12, "AsnOctetString 32-bit size");
_Static_assert(sizeof(AsnCounter64) == 8, "AsnCounter64 32-bit size");
_Static_assert(sizeof(AsnAny) == 16, "AsnAny 32-bit size");
_Static_assert(sizeof(SnmpVarBind) == 24, "SnmpVarBind 32-bit size");
_Static_assert(sizeof(SnmpVarBindList) == 8, "SnmpVarBindList 32-bit size");
_Static_assert(sizeof(SNMPAPI) == 4 && sizeof(AsnInteger32) == 4 &&
               sizeof(AsnGauge32) == 4 && sizeof(AsnTimeTicks) == 4,
               "SNMP scalar typedefs are 32-bit");
_Static_assert(sizeof(SnmpTfxHandle) == sizeof(HANDLE),
               "SnmpTfxHandle is a HANDLE (ms896029)");
_Static_assert(sizeof(CEDEVICE_POWER_STATE) == 4,
               "CEDEVICE_POWER_STATE enum size");
_Static_assert(sizeof(PHYSICAL_ADDRESS) == 8 &&
               sizeof(PPHYSICAL_ADDRESS) == 4,
               "PHYSICAL_ADDRESS = LARGE_INTEGER basis");
_Static_assert(sizeof(DMA_ADAPTER_OBJECT) == 12,
               "DMA_ADAPTER_OBJECT 32-bit size");
_Static_assert(sizeof(NetworkCallFailedInfo) == 8,
               "NetworkCallFailedInfo 32-bit size");
_Static_assert(sizeof(DEVMGR_DEVICE_INFORMATION) == 1584,
               "DEVMGR_DEVICE_INFORMATION 32-bit size");
_Static_assert(SDP_TYPE_NIL == 0x00 && SDP_TYPE_CONTAINER == 0x20,
               "SDP_TYPE values (aa450880)");
_Static_assert(SDP_ST_NONE == 0x0000 && SDP_ST_UINT128 == 0x0410 &&
               SDP_ST_UUID32 == 0x0220 && SDP_ST_INT32 == 0x0220,
               "SDP_SPECIFICTYPE values incl. [sic] 0x0220 (aa450879)");
_Static_assert(NODECONTAINERTYPESEQUENCE == 0 &&
               NODECONTAINERTYPEALTERNATIVE == 1,
               "NODECONTAINERTYPE values (ms895690)");
_Static_assert(NETWORK_FLAGS_DROP_ACTIVE == 0x01 &&
               NETWORK_FLAGS_DROP_ALL == 0x0f &&
               NETWORK_FLAGS_STATE_OUTGOING == 0x08,
               "NETWORK_FLAGS values (aa450315/aa450316)");
_Static_assert((int)ConfigurationSpaceUndefined == -1 &&
               PCIConfiguration == 4 && MaximumBusDataType == 11,
               "BUS_DATA_TYPE values (ms896151)");
_Static_assert((int)InterfaceTypeUndefined == -1 && PCIBus == 5 &&
               MaximumInterfaceType == 16,
               "INTERFACE_TYPE values (ms901367)");
_Static_assert((int)PwrDeviceUnspecified == -1 && D0 == 0 && D4 == 4 &&
               PwrDeviceMaximum == 5,
               "CEDEVICE_POWER_STATE values (aa447663)");

/* M58: DVD-Video renderer enum/macro values. */
_Static_assert(DVD_ASPECT_RATIO_MODE_LETTERBOX == 0 &&
               DVD_ASPECT_RATIO_MODE_PANSCAN == 1,
               "EDVDAspectRatioMode values (aa447766)");
_Static_assert(DVD_AUDIO_FREQ_48KHZ == 0 && DVD_AUDIO_FREQ_96KHZ == 1,
               "EDVDAudioFreq values (aa447767)");
_Static_assert(DVD_AUDIO_TYPE_AC3 == 2 && DVD_AUDIO_TYPE_MPEG == 3 &&
               DVD_AUDIO_TYPE_LPCM == 4 && DVD_AUDIO_TYPE_DTS == 5 &&
               DVD_AUDIO_TYPE_SDDS == 6,
               "EDVDAudioStreamType values (aa447768)");
_Static_assert(DVD_DISPLAY_ASPECT_4x3 == 0 && DVD_DISPLAY_ASPECT_16x9 == 3,
               "EDVDDisplayAspectRatio values (aa447769)");
_Static_assert(DVD_LPCM_16 == 0 && DVD_LPCM_20 == 1 && DVD_LPCM_24 == 2,
               "EDVDLpcmQuantization values (aa447780)");
_Static_assert(DVD_NAV_PACK_EVENT == 0 && DVD_HIGHLIGHT_EVENT == 1 &&
               DVD_PLAYBACK_EVENT == 2 && DVD_CC_DATA_EVENT == 3,
               "EDVDSyncEventType values (aa447781)");
_Static_assert(HIGHLIGHT_SELECT == 1 && UNHIGHLIGHT == 2 &&
               ACTIVATE_BUTTON == 3 && ACTIVATE_SELECTED == 4 &&
               SELECT_AUTO_ACTIVATED == 5,
               "EHighlightAction values (aa447783)");
_Static_assert(DVD_AUDIOCAP_AC3 == 0x4000 && DVD_AUDIOCAP_MPEG == 0x1000 &&
               DVD_AUDIOCAP_DTS == 0x0800 && DVD_AUDIOCAP_SDDS == 0x0400 &&
               DVD_AUDIOCAP_LPCM_KARAOKE == 0x0080 &&
               DVD_AUDIOCAP_AC3_KARAOKE == 0x0040 &&
               DVD_AUDIOCAP_MPEG_KARAOKE == 0x0010 &&
               DVD_AUDIOCAP_DTS_KARAOKE == 0x0008 &&
               DVD_AUDIOCAP_SDDS_KARAOKE == 0x0004,
               "DVD_AUDIOCAP_* values (ms892143)");
_Static_assert(DVD_SCANCAP_FORWARD_SCAN == 0x1 &&
               DVD_SCANCAP_FORWARD_SLOW == 0x2 &&
               DVD_SCANCAP_FORWARD_SINGLE == 0x4 &&
               DVD_SCANCAP_BACKWARD_SCAN == 0x8 &&
               DVD_SCANCAP_BACKWARD_SLOW == 0x10 &&
               DVD_SCANCAP_BACKWARD_SINGLE == 0x20,
               "DVD_SCANCAP_* values (ms892143)");
#endif

static int m56_shaped_usage(void)
{
    REBARINFO          ri;
    NMRBAUTOSIZE       nmrba;
    HDITEM             hdi;
    HDLAYOUT           hdl;
    NMHEADER           nmhd;
    TCITEM             tci;
    TCHITTESTINFO      tchti;
    NMDATETIMECHANGE   nmdtc;
    MCHITTESTINFO      mchti;
    NMSELCHANGE        nmsc;
    NMDAYSTATE         nmds;
    TVITEM             tvi;
    TV_INSERTSTRUCT    tvis;
    TVSORTCB           tvscb;
    NM_TREEVIEW        nmtv;
    NMTVCUSTOMDRAW     nmtvcd;
    LVITEM             lvi;
    LVCOLUMN           lvc;
    LVBKIMAGE          lvbk;
    LVFINDINFO         lvfi;
    LVHITTESTINFO      lvhti;
    NMLISTVIEW         nmlv;
    NMLVCUSTOMDRAW     nmlvcd;
    LV_DISPINFO        lvdi;

    ri.cbSize     = sizeof(REBARINFO);
    nmrba.hdr.code = 0;
    hdi.mask      = 0;
    hdl.prc       = (RECT FAR *)0;
    nmhd.iItem    = 0;
    tci.mask      = 0;
    tchti.pt.x    = 0;
    nmdtc.st.wYear = 2026;
    mchti.cbSize  = sizeof(MCHITTESTINFO);
    nmsc.stSelStart.wMonth = 9;
    nmds.cDayState = 0;
    tvi.hItem     = (HTREEITEM)0;
    tvis.hParent  = (HTREEITEM)0;
    tvscb.lpfnCompare = (PFNTVCOMPARE)0;
    nmtv.action   = 0;
    nmtvcd.clrText = 0;
    lvi.iItem     = 0;
    lvc.cx        = 0;
    lvbk.hbm      = (HBITMAP)0;
    lvfi.psz      = (LPCTSTR)0;
    lvhti.iItem   = 0;
    nmlv.iItem    = 0;
    nmlvcd.clrTextBk = 0;
    lvdi.item.mask = 0;

    /* alias bridges (title vs printed spellings) */
    {
        HD_ITEM      *p1 = &hdi;
        HDLAYOUT     *p2 = &hdl;
        HDHITTESTINFO *p3 = (HDHITTESTINFO *)0;
        TV_ITEM      *p4 = &tvi;
        TVHITTESTINFO *p5 = (TV_HITTESTINFO *)0;
        TV_SORTCB    *p6 = &tvscb;
        TV_KEYDOWN   *p7 = (TV_KEYDOWN *)0;
        LV_FINDINFO  *p8 = &lvfi;
        (void) p1; (void) p2; (void) p3; (void) p4; (void) p5;
        (void) p6; (void) p7; (void) p8;
    }
    (void) ri; (void) nmrba; (void) hdi; (void) hdl; (void) nmhd;
    (void) tci; (void) tchti; (void) nmdtc; (void) mchti; (void) nmsc;
    (void) nmds; (void) tvi; (void) tvis; (void) tvscb; (void) nmtv;
    (void) nmtvcd; (void) lvi; (void) lvc; (void) lvbk; (void) lvfi;
    (void) lvhti; (void) nmlv; (void) nmlvcd; (void) lvdi;
    return 0;
}

/* M57: Bluetooth / SNMP / CEDDK shaped usage (declarations + calls). */
static int m57_shaped_usage(void)
{
    BASEBAND_CONNECTION   bbcon;
    PORTEMUPortParams     pep;
    SOCKADDR_BTH          sabth;
    BTH_LOCAL_VERSION     blv;
    BTH_REMOTE_VERSION    brv;
    BTH_REMOTE_NAME       brn;
    BTH_SOCKOPT_SECURITY  bsec;
    BTH_SNIFF_MODE        bsm;
    BthInquiryResult      inq;
    SdpQueryUuid          squ;
    SdpQueryUuidUnion     squu;
    BTHNS_RESTRICTIONBLOB rbl;
    BTHNS_INQUIRYBLOB     ibl;
    BTHNS_SETBLOB         sbl;
    ISdpNodeContainer    *pc = (ISdpNodeContainer *)0;
    ISdpRecord           *pr = (ISdpRecord *)0;
    ISdpStream           *ps = (ISdpStream *)0;
    ISdpWalk             *pw = (ISdpWalk *)0;
    NodeData             *pnd = (NodeData *)0;
    NodeDataUnion        *pndu = (NodeDataUnion *)0;
    SDP_TYPE              sdt = SDP_TYPE_NIL;
    SDP_SPECIFICTYPE      sst = SDP_ST_NONE;
    NODECONTAINERTYPE     nct = NODECONTAINERTYPESEQUENCE;
    PFN_SendATCommand     pfnAT = (PFN_SendATCommand)0;
    PFN_PhoneExtServiceCallback pfnSvc = (PFN_PhoneExtServiceCallback)0;
    NetworkCallFailedInfo ncfi;
    AsnAny                aa;
    AsnObjectIdentifier   aoi;
    AsnOctetString        aos;
    AsnCounter64          ac64;
    SnmpVarBind           svb;
    SnmpVarBindList       svbl;
    SnmpMibView          *pmv = (SnmpMibView *)0;
    SnmpTfxHandle         tfx = (SnmpTfxHandle)0;
    CEDEVICE_POWER_STATE  dps = D0;
    PHYSICAL_ADDRESS      pa;
    DMA_ADAPTER_OBJECT    dao;
    DEVMGR_DEVICE_INFORMATION ddi;
    BUS_DATA_TYPE         bdt = PCIConfiguration;
    INTERFACE_TYPE        ift = PCIBus;

    bbcon.hConnection = 0;
    pep.channel = 0;
    sabth.port = 0;
    blv.hci_version = 0;
    brv.lmp_version = 0;
    brn.szNameBuffer[0] = 0;
    bsec.iLength = 0;
    bsm.interval = 0;
    inq.cod = 0;
    squ.uuidType = 0;
    squu.uuid16 = 0;
    rbl.type = 0;
    ibl.LAP = 0;
    sbl.ulRecordLength = 0;
    ncfi.usCallType = 0;
    aa.asnType = 0;
    aoi.idLength = 0;
    aos.length = 0;
    ac64.LowPart = 0;
    svb.name.idLength = 0;
    svbl.len = 0;
    pa.QuadPart = 0;
    dao.ObjectSize = 0;
    ddi.dwSize = 0;
    tfx = SnmpTfxOpen(1, pmv);
    (void) SnmpTfxQuery(tfx, 0, (RFC1157VarBindList *)0,
                        (AsnInteger *)0, (AsnInteger *)0);
    (void) SnmpTfxClose(tfx);
    (void) BthReadLocalAddr((BT_ADDR *)0);
    (void) BthPerformInquiry(0, 0, 0, 0, (unsigned int *)0, &inq);
    (void) BthNsSetService((LPWSAQUERYSET)0, RNRSERVICE_REGISTER, 0);
    (void) BthAGPhoneExtInit();
    (void) BthAGNetworkDropCall(NETWORK_FLAGS_DROP_ALL);
    (void) BthAGOnNetworkEvent(0, (LPSTR)0);
    (void) BthAGATHandler((LPSTR)0, 0);
    BthAGATSetCallback(pfnAT);
    BthAGSetServiceCallback(pfnSvc);
    (void) SnmpUtilOctetsCmp(&aos, &aos);
    (void) SnmpUtilOidCmp(&aoi, &aoi);
    (void) SnmpUtilAsnAnyCpy(&aa, &aa);
    (void) SnmpUtilMemAlloc(0);
    (void) SnmpExtensionQuery(0, &svbl, (AsnInteger32 *)0,
                              (AsnInteger32 *)0);
    (void) HalTranslateBusAddress(ift, 0, pa, (PULONG)0,
                                  (PPHYSICAL_ADDRESS)0);
    (void) READ_PORT_ULONG((PULONG)0);
    (void) GetDevicePowerState((HANDLE)0, &dps, (PVOID)0);
    (void) GetParentDeviceInfo((HANDLE)0, &ddi);
    (void) StallExecution(1);
    (void) CalibrateStallCounter();

    (void) pc; (void) pr; (void) ps; (void) pw; (void) pnd; (void) pndu;
    (void) sdt; (void) sst; (void) nct; (void) bdt; (void) ift; (void) dps;
    (void) bbcon; (void) pep; (void) sabth; (void) blv; (void) brv;
    (void) brn; (void) bsec; (void) bsm; (void) inq; (void) squ;
    (void) squu; (void) rbl; (void) ibl; (void) sbl; (void) ncfi;
    (void) aa; (void) aoi; (void) aos; (void) ac64; (void) svb;
    (void) svbl; (void) pa; (void) dao; (void) ddi; (void) tfx;
    return 0;
}

/* M58: DVD-Video renderer shaped usage. */
static int m58_shaped_usage(void)
{
    EDVDAspectRatioMode     arm = DVD_ASPECT_RATIO_MODE_LETTERBOX;
    EDVDAudioFreq           aaf = DVD_AUDIO_FREQ_96KHZ;
    EDVDAudioStreamType     ast = DVD_AUDIO_TYPE_LPCM;
    EDVDDisplayAspectRatio  dar = DVD_DISPLAY_ASPECT_16x9;
    EDVDLpcmQuantization    lpq = DVD_LPCM_24;
    EDVDSyncEventType       set = DVD_NAV_PACK_EVENT;
    EHighlightAction        hla = HIGHLIGHT_SELECT;
    DWORD                   caps = DVD_AUDIOCAP_AC3 | DVD_SCANCAP_FORWARD_SCAN;
    IDMAChannel            *pchan = (IDMAChannel *)0;
    IBitstreamProcessor    *pbps = (IBitstreamProcessor *)0;
    IDVDRenderer           *prend = (IDVDRenderer *)0;
    IDVDDecoderCSS         *pcss = (IDVDDecoderCSS *)0;

    (void) arm; (void) aaf; (void) ast; (void) dar; (void) lpq;
    (void) set; (void) hla; (void) caps;
    (void) pchan; (void) pbps; (void) prend; (void) pcss;
    return 0;
}

#if __SIZEOF_POINTER__ == 4
/* M59: DirectDraw 32-bit CE layout as printed by the CE 5.0 pages
 * (Ddraw.h / Dvp.h; member-by-member counts of the transcribed
 * definitions, all-DWORD/pointer/GUID members with natural 4-byte
 * alignment, DD_ROP_SPACE = 8 derived from the DDK DDCORECAPS
 * array description + the 256-code SDK raster-operation space). */
_Static_assert(DD_ROP_SPACE == 8, "DD_ROP_SPACE derivation (ms907789)");
_Static_assert(sizeof(DDCOLORKEY) == 8, "DDCOLORKEY 32-bit size (ms907791)");
_Static_assert(sizeof(DDSCAPS) == 4, "DDSCAPS 32-bit size (ms907796)");
_Static_assert(sizeof(DDSCAPS2) == 16, "DDSCAPS2 32-bit size (ms907797)");
_Static_assert(sizeof(DDSCAPSEX) == 12, "DDSCAPSEX 32-bit size (ms907798)");
_Static_assert(sizeof(DDPIXELFORMAT) == 32, "DDPIXELFORMAT 32-bit size (ms907795)");
_Static_assert(offsetof(DDPIXELFORMAT, dwRGBBitCount) == 12,
               "DDPIXELFORMAT first union (ms907795)");
_Static_assert(offsetof(DDPIXELFORMAT, dwRBitMask) == 16,
               "DDPIXELFORMAT second union (ms907795)");
_Static_assert(sizeof(DDSURFACEDESC) == 108, "DDSURFACEDESC 32-bit size (ms907799)");
_Static_assert(sizeof(DDSURFACEDESC2) == 124, "DDSURFACEDESC2 32-bit size (ms907800)");
_Static_assert(offsetof(DDSURFACEDESC2, dwTextureStage) == 120,
               "DDSURFACEDESC2 tail member (ms907800)");
_Static_assert(sizeof(DDBLTFX) == 100, "DDBLTFX 32-bit size (ms907788)");
_Static_assert(offsetof(DDBLTFX, ddckDestColorkey) == 84,
               "DDBLTFX union block size (ms907788)");
_Static_assert(sizeof(DDOVERLAYFX) == 56, "DDOVERLAYFX 32-bit size (ms907794)");
_Static_assert(sizeof(DDCOLORCONTROL) == 40, "DDCOLORCONTROL 32-bit size (ms907790)");
_Static_assert(sizeof(DDCAPS) == 380, "DDCAPS 32-bit size (ms907789)");
_Static_assert(offsetof(DDCAPS, dwRops) == 100, "DDCAPS dwRops offset (ms907789)");
_Static_assert(offsetof(DDCAPS, ddsCaps) == 364, "DDCAPS ddsCaps tail (ms907789)");
_Static_assert(sizeof(DDVIDEOPORTBANDWIDTH) == 32, "DDVIDEOPORTBANDWIDTH size (ms907801)");
_Static_assert(sizeof(DDVIDEOPORTCAPS) == 72, "DDVIDEOPORTCAPS size (ms907802)");
_Static_assert(sizeof(DDVIDEOPORTCONNECT) == 32, "DDVIDEOPORTCONNECT size (ms907803)");
_Static_assert(offsetof(DDVIDEOPORTCONNECT, guidTypeID) == 8,
               "DDVIDEOPORTCONNECT GUID member (ms907803)");
_Static_assert(sizeof(DDVIDEOPORTDESC) == 72, "DDVIDEOPORTDESC size (ms907804)");
_Static_assert(sizeof(DDVIDEOPORTINFO) == 64, "DDVIDEOPORTINFO size (ms907805)");
_Static_assert(offsetof(DDVIDEOPORTINFO, rCrop) == 16, "DDVIDEOPORTINFO RECT (ms907805)");
_Static_assert(sizeof(DDVIDEOPORTSTATUS) == 56, "DDVIDEOPORTSTATUS size (ms907806)");
#endif

/* M59: DirectDraw shaped usage (structures + opaque interfaces +
 * callback typedefs + the four Ddraw.lib functions). */
static int m59_shaped_usage(void)
{
    DDCOLORKEY          ddk;
    DDSCAPS             dsc;
    DDSCAPS2            dsc2;
    DDPIXELFORMAT       dpf;
    DDSURFACEDESC       dsd;
    DDSURFACEDESC2      dsd2;
    DDBLTFX             dbfx;
    DDOVERLAYFX         dof;
    DDCOLORCONTROL      dcc;
    DDCAPS              dcap;
    LPDIRECTDRAW        pdd = (LPDIRECTDRAW)0;
    LPDIRECTDRAW4       pdd4 = (LPDIRECTDRAW4)0;
    LPDIRECTDRAWSURFACE4 pds4 = (LPDIRECTDRAWSURFACE4)0;
    LPDIRECTDRAWSURFACE5 pds5 = (LPDIRECTDRAWSURFACE5)0;
    LPDIRECTDRAWCLIPPER pddc = (LPDIRECTDRAWCLIPPER)0;
    LPDIRECTDRAWPALETTE pddp = (LPDIRECTDRAWPALETTE)0;
    LPDIRECTDRAWCOLORCONTROL pddcc = (LPDIRECTDRAWCOLORCONTROL)0;
    LPDDENUMCALLBACK    pecb = (LPDDENUMCALLBACK)0;
    LPDDENUMCALLBACKEX  pecbx = (LPDDENUMCALLBACKEX)0;
    LPDDENUMMODESCALLBACK  pemcb = (LPDDENUMMODESCALLBACK)0;
    LPDDENUMMODESCALLBACK2 pemcb2 = (LPDDENUMMODESCALLBACK2)0;
    LPDDENUMSURFACESCALLBACK  pescb = (LPDDENUMSURFACESCALLBACK)0;
    LPDDENUMSURFACESCALLBACK2 pescb2 = (LPDDENUMSURFACESCALLBACK2)0;
    DDVIDEOPORTBANDWIDTH dvpb;
    DDVIDEOPORTCAPS     dvpc;
    DDVIDEOPORTCONNECT  dvpcn;
    DDVIDEOPORTDESC     dvpd;
    DDVIDEOPORTINFO     dvpi;
    DDVIDEOPORTSTATUS   dvps;
    LPDDVIDEOPORTCONTAINER pdvpc = (LPDDVIDEOPORTCONTAINER)0;
    LPDIRECTDRAWVIDEOPORT pdvp = (LPDIRECTDRAWVIDEOPORT)0;
    LPDDENUMVIDEOCALLBACK pevb = (LPDDENUMVIDEOCALLBACK)0;

    ddk.dwColorSpaceLowValue  = 0;
    dsc.dwCaps  = 0;
    dsc2.dwCaps = 0;
    dpf.dwSize  = sizeof(DDPIXELFORMAT);
    dpf.dwRGBBitCount = 16;
    dsd.dwSize  = sizeof(DDSURFACEDESC);
    dsd.lPitch  = 0;
    dsd2.dwSize = sizeof(DDSURFACEDESC2);
    dsd2.dwTextureStage = 0;
    dbfx.dwSize = sizeof(DDBLTFX);
    dbfx.dwFillColor = 0;
    dof.dwSize  = sizeof(DDOVERLAYFX);
    dof.dckDestColorkey.dwColorSpaceLowValue = 0;
    dcc.dwSize  = sizeof(DDCOLORCONTROL);
    dcc.lBrightness = 0;
    dcap.dwSize = sizeof(DDCAPS);
    dcap.dwRops[0] = 0;
    dcap.ddsCaps.dwCaps = 0;
    dvpb.dwSize = sizeof(DDVIDEOPORTBANDWIDTH);
    dvpc.dwSize = sizeof(DDVIDEOPORTCAPS);
    dvpc.wNumFilterTapsX = 0;
    dvpcn.dwSize = sizeof(DDVIDEOPORTCONNECT);
    dvpcn.guidTypeID.Data1 = 0;
    dvpd.dwSize = sizeof(DDVIDEOPORTDESC);
    dvpd.VideoPortType.dwPortWidth = 0;
    dvpi.dwSize = sizeof(DDVIDEOPORTINFO);
    dvpi.rCrop.left = 0;
    dvps.dwSize = sizeof(DDVIDEOPORTSTATUS);
    dvps.bInUse = FALSE;

    /* Ddraw.lib import surface (aa451583/aa451584/aa451585/aa451586). */
    (void) DirectDrawCreate((GUID FAR *)0, &pdd, (IUnknown FAR *)0);
    (void) DirectDrawCreateClipper(0u, &pddc, (IUnknown FAR *)0);
    (void) DirectDrawEnumerate(pecb, (LPVOID)0);
    (void) DirectDrawEnumerateEx(pecbx, (LPVOID)0, 0u);

    (void) pdd4; (void) pds4; (void) pds5; (void) pddp; (void) pddcc;
    (void) pemcb; (void) pemcb2; (void) pescb; (void) pescb2;
    (void) pdvpc; (void) pdvp; (void) pevb;
    (void) ddk; (void) dsc; (void) dsc2; (void) dpf; (void) dsd;
    (void) dsd2; (void) dbfx; (void) dof; (void) dcc; (void) dcap;
    (void) dvpb; (void) dvpc; (void) dvpcn; (void) dvpd; (void) dvpi;
    (void) dvps;
    return 0;
}

static int m53_shaped_usage(void)
{
    BROWSEINFO        bi;
    CPLINFO           ci;
    NEWCPLINFO        nci;
    NOTIFYICONDATA    nid;
    SHELLEXECUTEINFO  sei;
    SHFILEINFO        sfi;
    SHFILEOPSTRUCT    fos;
    STRRET            sr;
    ITEMIDLIST        idl;
    NMRGINFO          nmrgi;
    LPITEMIDLIST      pidl = (LPITEMIDLIST)0;
    HWND              hwnd = (HWND)0;

    bi.hwndOwner   = hwnd;
    ci.idIcon      = 0;
    nci.dwSize     = sizeof(NEWCPLINFO);
    nid.cbSize     = sizeof(NOTIFYICONDATA);
    sei.cbSize     = sizeof(SHELLEXECUTEINFO);
    sfi.iIcon      = 0;
    fos.hwnd       = hwnd;
    sr.uType       = 0;
    idl.mkid.cb    = 0;
    nmrgi.dwItemSpec = 0;

    /* Ceshell.lib import surface (Standard Shell Reference). */
    (void) SHBrowseForFolder(&bi);
    (void) SHBindToParent((LPCITEMIDLIST)pidl, (REFIID)0,
                          (VOID **)0, (LPCITEMIDLIST *)0);
    (void) SHGetDesktopFolder((IShellFolder **)0);
    (void) SHGetMalloc((LPMALLOC *)0);
    (void) SHGetSpecialFolderLocation(hwnd, CSIDL_FAVORITES, &pidl);
    (void) SHGetDocumentsFolder((LPCTSTR)0, (LPTSTR)0);
    (void) SHFileOperation(&fos);
    (void) StrRetToBuf(&sr, (LPCITEMIDLIST)pidl, (LPTSTR)0, 0u);
    (void) SHGetPathFromIDList((LPCITEMIDLIST)pidl, (LPSTR)0);
    /* Coredll.lib additions. */
    (void) SHAddToRecentDocs(0u, (LPCVOID)0);
    (void) SHCreateShortcut((LPTSTR)0, (LPTSTR)0);
    (void) SHCreateShortcutEx((LPTSTR)0, (LPTSTR)0, (LPTSTR)0,
                              (LPDWORD)0);
    (void) ShellExecuteEx(&sei);
    (void) SHGetShortcutTarget((LPTSTR)0, (LPTSTR)0, 0);
    (void) SHGetSpecialFolderPath(hwnd, (LPTSTR)0, CSIDL_PROGRAMS, 0);
    (void) SHLoadDIBitmap((LPCTSTR)0);
    /* Shmisc.lib. */
    (void) SHShowOutOfMemory(hwnd, 0u);
    /* Pages without a Link Library row (no def; link-checked via the
     * host compile only). */
    (void) Shell_NotifyIcon(NIM_ADD, &nid);
    (void) SHGetFileInfo((LPCTSTR)0, 0u, &sfi, (UINT)sizeof(sfi),
                         SHGFI_ICON);
    /* Macros / callback shapes. */
    {
        RECT r;
        r.left = 0;
        MapWindowRect((HWND)0, (HWND)0, &r);
        (void) r;
    }
    (void) ((BFFCALLBACK)0);
    (void) ((SHGNO)SHGDN_NORMAL);
    (void) CPlApplet(hwnd, 0, 0, 0);
    (void) idl;
    (void) nmrgi;
    (void) ci;
    (void) nci;
    return 0;
}

#if __SIZEOF_POINTER__ == 4
/* M61: MLang 32-bit CE sizes + the published enum values. */
_Static_assert(sizeof(UNICODERANGE) == 4, "UNICODERANGE size (ms918861)");
_Static_assert(sizeof(DetectEncodingInfo) == 16,
               "DetectEncodingInfo size (aa452152)");
_Static_assert(MIMECONTF_MAILNEWS == 0x1 &&
               MIMECONTF_MIME_REGISTRY == 0x40000000,
               "MIMECONTF values (ms918819)");
_Static_assert(MLCONVCHARF_NONE == 0 && MLCONVCHARF_NOBESTFITCHARS == 16,
               "MLCONVCHAR values (ms918823)");
_Static_assert(MLDETECTF_MAILNEWS == 0x0001 &&
               MLDETECTF_FILTER_SPECIALCHAR == 0x0040,
               "MLCP values (ms918824)");
_Static_assert(MLDETECTCP_NONE == 0 && MLDETECTCP_HTML == 8,
               "MLDETECTCP values (ms918825)");
_Static_assert(SCRIPTCONTF_FIXED_FONT == 0x00000001 &&
               SCRIPTCONTF_SCRIPT_SYSTEM == 0x00040000,
               "SCRIPTFONTCONTF values (ms918856)");
_Static_assert(sidDefault == 0 && sidHangul == 23 && sidHan == 26 &&
               sidLim == 40 && sidFEFirst == sidHangul &&
               sidFELast == sidHan,
               "SCRIPTCONTF implicit values + aliases (ms918854)");
#endif

/* M61: MLang shaped usage (enums, structures, opaque interfaces +
 * the six Mlang.dll functions). */
static int m61_shaped_usage(void)
{
    MIMECONTF         mc = MIMECONTF_MAILNEWS;
    MLCONVCHAR        mcc = MLCONVCHARF_NONE;
    MLCP              mlcp = MLDETECTF_VALID;
    MLDETECTCP        mdc = MLDETECTCP_8BIT;
    SCRIPTCONTF       sc = sidHangul;
    SCRIPTFONTCONTF   sfc = SCRIPTCONTF_FIXED_FONT;
    SCRIPT_ID         sid = sidDefault;
    UNICODERANGE      ur;
    DetectEncodingInfo dei;
    pDetectEncodingInfo pdei = (pDetectEncodingInfo)0;
    IEnumCodePage    *pecp = (IEnumCodePage *)0;
    IEnumRfc1766     *pecr = (IEnumRfc1766 *)0;
    IEnumScript      *pecs = (IEnumScript *)0;
    IMLangCodePages   *pmcp = (IMLangCodePages *)0;
    IMLangConvertCharset *pmcc = (IMLangConvertCharset *)0;
    IMLangFontLink   *pmfl = (IMLangFontLink *)0;
    IMLangFontLink2  *pmfl2 = (IMLangFontLink2 *)0;
    IMLangLineBreakConsole *pmlb = (IMLangLineBreakConsole *)0;
    IMultiLanguage   *pml = (IMultiLanguage *)0;
    IMultiLanguage2  *pml2 = (IMultiLanguage2 *)0;
    IMultiLanguage3  *pml3 = (IMultiLanguage3 *)0;
    LCID              lcid = 0;
    DWORD             mode = 0;
    INT               n = 0;

    ur.wcFrom = 0; ur.wcTo = 0;
    dei.nLangID = 0; dei.nCodePage = 0; dei.nDocPercent = 0;
    dei.nConfidence = 0;

    /* Mlang.dll import surface (aa452124..ms918853). */
    (void) ConvertINetMultiByteToUnicode(&mode, 0u, (LPCSTR)0, &n,
                                         (LPWSTR)0, &n);
    (void) ConvertINetString(&mode, 0u, 0u, (LPCSTR)0, &n,
                             (LPBYTE)0, &n);
    (void) ConvertINetUnicodeToMultiByte(&mode, 0u, (LPCWSTR)0, &n,
                                         (LPSTR)0, &n);
    (void) IsConvertINetStringAvailable(0u, 0u);
    (void) LcidToRfc1766(lcid, (LPTSTR)0, 0);
    (void) Rfc1766ToLcid(&lcid, (LPTSTR)0);

    /* M61b: Nk-scope closure (winbase.h additions). */
    (void) CeGetThreadPriority((HANDLE)0);
    (void) CeSetThreadPriority((HANDLE)0, 248);
    (void) SetThreadContext((HANDLE)0, (CONST CONTEXT *)0);
    (void) WriteProcessMemory((HANDLE)0, (LPVOID)0, (LPVOID)0, 0u,
                              (LPDWORD)0);

    (void) mc; (void) mcc; (void) mlcp; (void) mdc; (void) sc;
    (void) sfc; (void) sid; (void) ur; (void) dei; (void) pdei;
    (void) pecp; (void) pecr; (void) pecs; (void) pmcp; (void) pmcc;
    (void) pmfl; (void) pmfl2; (void) pmlb; (void) pml; (void) pml2;
    (void) pml3; (void) lcid; (void) mode; (void) n;
    return 0;
}

#if __SIZEOF_POINTER__ == 4
/* M60: URL Moniker Services 32-bit CE sizes + the published enum
 * values (value tables and starter values transcribed from the
 * official pages; successors follow the printed C enums). */
_Static_assert(sizeof(PROTOCOLDATA) == 16, "PROTOCOLDATA size (ms918838)");
_Static_assert(sizeof(PROTOCOLFILTERDATA) == 20, "PROTOCOLFILTERDATA size (ms918839)");
_Static_assert(sizeof(HIT_LOGGING_INFO) == 44, "HIT_LOGGING_INFO size (ms906339)");
_Static_assert(offsetof(HIT_LOGGING_INFO, EndTime) == 24,
               "HIT_LOGGING_INFO SYSTEMTIME members (ms906339)");
_Static_assert(offsetof(PROTOCOLFILTERDATA, pProtocol) == 8,
               "PROTOCOLFILTERDATA member order (ms918839)");
_Static_assert(BINDF_ASYNCHRONOUS == 0x1 && BINDF_RESERVED_3 == 0x00800000,
               "BINDF values (aa452098)");
_Static_assert(PI_PARSE_URL == 0x1 && PD_FORCE_SWITCH == 0x00010000,
               "PI_FLAGS values (ms918833)");
_Static_assert(BINDINFO_OPTIONS_BINDTOOBJECT == 0x00100000,
               "BINDINFO_OPTIONS values (aa452101)");
_Static_assert(MIMETYPEPROP == 0x00000000, "MONIKERPROPERTY (ms918826)");
_Static_assert(URL_ENCODING_ENABLE_UTF8 == 0x10000000,
               "URL_ENCODING values (ms918867)");
_Static_assert(PUAF_DEFAULT == 0x0 && PUAF_ACCEPT_WILDCARD_SCHEME == 0x80,
               "PUAF values (ms918841)");
_Static_assert(SZM_CREATE == 0x0 && SZM_DELETE == 0x1,
               "SZM_FLAGS values (ms918860)");
_Static_assert(URLTEMPLATE_CUSTOM == 0x0 && URLTEMPLATE_MEDLOW == 0x10500 &&
               URLTEMPLATE_PREDEFINED_MAX == 0x20000,
               "URLTEMPLATE values (ms918875)");
_Static_assert(ZAFLAGS_CUSTOM_EDIT == 0x1 && ZAFLAGS_UNC_AS_INTRANET == 0x80,
               "ZAFLAGS values (ms918890)");
_Static_assert(PSU_DEFAULT == 1 && PSU_SECURITY_URL_ONLY == 2,
               "PSUACTION values (ms918840)");
_Static_assert(BINDSTRING_HEADERS == 1 && BINDSTRING_PTR_BIND_CONTEXT == 17,
               "BINDSTRING values (aa452103)");
_Static_assert(PARSE_CANONICALIZE == 1 && PARSE_UNESCAPE == 19,
               "PARSEACTION values (ms918832)");
_Static_assert(QUERY_EXPIRATION_DATE == 1 && QUERY_IS_SAFE == 14,
               "QUERYOPTION values (ms918843)");
_Static_assert(URLZONE_LOCAL_MACHINE == 0 && URLZONE_INTERNET == 3 &&
               URLZONE_UNTRUSTED == 4 && URLZONE_USER_MIN == 1000 &&
               URLZONE_USER_MAX == 10000, "URLZONE values (ms918876)");
_Static_assert(URLZONEREG_DEFAULT == 0 && URLZONEREG_HKCU == 2,
               "URLZONEREG values (ms918877)");
_Static_assert(BINDINFOF_URLENCODESTGMEDDATA == 0 &&
               BINDINFOF_URLENCODEDEXTRAINFO == 1,
               "BINDINFOF values (aa452100)");
_Static_assert(BINDVERB_GET == 0 && BINDVERB_CUSTOM == 3,
               "BINDVERB values (aa452104)");
_Static_assert(BSCF_FIRSTDATANOTIFICATION == 0 &&
               BSCF_AVAILABLEDATASIZEUNKNOWN == 4, "BSCF values (aa452105)");
_Static_assert(BINDSTATUS_FINDINGRESOURCE == 0 && BINDSTATUS_SIZEAVAILABLE == 48,
               "BINDSTATUS implicit values, duplicate dropped (aa452102)");
_Static_assert(CF_NULL == 0, "CF_NULL (ms918847)");
#endif

/* M60: URL Moniker Services shaped usage (enums, structures, opaque
 * interfaces + the 38 Urlmon.lib functions). */
static int m60_shaped_usage(void)
{
    BINDF             bf = BINDF_ASYNCHRONOUS;
    PI_FLAGS          pif = PI_PARSE_URL;
    BINDINFO_OPTIONS  bio = BINDINFO_OPTIONS_BINDTOOBJECT;
    MONIKERPROPERTY   mkp = MIMETYPEPROP;
    URL_ENCODING      ue = URL_ENCODING_NONE;
    PUAF              puaf = PUAF_DEFAULT;
    SZM_FLAGS         szm = SZM_CREATE;
    URLTEMPLATE       ut = URLTEMPLATE_MEDIUM;
    ZAFLAGS           zaf = ZAFLAGS_NO_UI;
    PSUACTION         psu = PSU_DEFAULT;
    BINDSTRING        bs = BINDSTRING_HEADERS;
    PARSEACTION       pa = PARSE_CANONICALIZE;
    QUERYOPTION       qo = QUERY_EXPIRATION_DATE;
    URLZONE           uz = URLZONE_INTERNET;
    URLZONEREG        uzr = URLZONEREG_HKLM;
    BINDINFOF         bif = BINDINFOF_URLENCODESTGMEDDATA;
    BINDVERB          bv = BINDVERB_GET;
    BSCF              bscf = BSCF_FIRSTDATANOTIFICATION;
    BINDSTATUS        bst = BINDSTATUS_FINDINGRESOURCE;
    PROTOCOLDATA      pd;
    PROTOCOLFILTERDATA pfd;
    HIT_LOGGING_INFO  hli;
    CLIPFORMAT        cf = CF_NULL;
    BINDINFO          bi;      /* objbase.h definition (ms928761) */
    IInternetSession *pses = (IInternetSession *)0;
    IMoniker         *pmk = (IMoniker *)0;
    IBindCtx         *pbc = (IBindCtx *)0;
    LPBINDSTATUSCALLBACK pbsc = (LPBINDSTATUSCALLBACK)0;
    LPBINDCTX         pbcx = (LPBINDCTX)0;

    pd.grfFlags = 0; pd.dwState = 0; pd.pData = 0; pd.cbData = 0;
    pfd.cbSize = sizeof(PROTOCOLFILTERDATA); pfd.pProtocolSink = 0;
    pfd.pProtocol = 0; pfd.pUnk = 0; pfd.dwFilterFlags = 0;
    hli.dwStructSize = sizeof(HIT_LOGGING_INFO);
    hli.lpszLoggedUrlName = (LPSTR)0;
    hli.StartTime.wYear = 2026; hli.EndTime.wYear = 2026;
    hli.lpszExtendedInfo = (LPSTR)0;
    bi.cbSize = sizeof(BINDINFO);
    bi.dwBindVerb = (DWORD)bv;
    bi.grfBindInfoF = (DWORD)bif;

    /* Urlmon.lib import surface (aa452108..ms918878). */
    (void) CoGetClassObjectFromURL((REFCLSID)0, (LPCWSTR)0, 0u, 0u,
                                   (LPCWSTR)0, pbcx, 0u, (LPVOID)0,
                                   (REFIID)0, (VOID **)0);
    (void) CoInternetCombineUrl((LPCWSTR)0, (LPCWSTR)0, 0u, (LPWSTR)0,
                                0u, (DWORD *)0, 0u);
    (void) CoInternetGetProtocolFlags((LPCWSTR)0, (DWORD *)0, 0u);
    (void) CoInternetGetSecurityUrl((LPCWSTR)0, (LPWSTR *)0, psu, 0u);
    (void) CoInternetGetSession(0u, &pses, 0u);
    (void) CoInternetParseUrl((LPCWSTR)0, pa, 0u, (LPWSTR)0, 0u,
                              (DWORD *)0, 0u);
    (void) CoInternetQueryInfo((LPCWSTR)0, qo, 0u, (LPVOID)0, 0u,
                               (DWORD *)0, 0u);
    (void) CopyBindInfo((const BINDINFO *)&bi, &bi);
    (void) CopyStgMedium((const STGMEDIUM *)0, (STGMEDIUM *)0);
    (void) CreateAsyncBindCtx(0u, (IBindStatusCallback *)0,
                              (IEnumFORMATETC *)0, &pbc);
    (void) CreateAsyncBindCtxEx((IBindCtx *)0, 0u,
                                (IBindStatusCallback *)0,
                                (IEnumFORMATETC *)0, &pbc, 0u);
    (void) CreateFormatEnumerator(0u, (FORMATETC *)0,
                                  (IEnumFORMATETC **)0);
    (void) CreateURLMoniker((IMoniker *)0, (LPWSTR)0, &pmk);
    (void) CreateURLMonikerEx((LPMONIKER)0, (LPCWSTR)0,
                              (LPMONIKER *)0, 0u);
    (void) FindMediaType((LPCSTR)0, &cf);
    (void) FindMediaTypeClass((LPBC)0, (LPCSTR)0, (CLSID *)0, 0u);
    (void) FindMimeFromData((LPBC)0, (LPCWSTR)0, (LPVOID)0, 0u,
                            (LPCWSTR)0, 0u, (LPWSTR *)0, 0u);
    (void) GetClassFileOrMime((LPBC)0, (LPCWSTR)0, (LPVOID)0, 0u,
                              (LPCWSTR)0, 0u, (CLSID *)0);
    (void) IsAsyncMoniker((IMoniker *)0);
    (void) IsLoggingEnabledW((LPCTSTR)0);
    (void) IsValidURL((LPBC)0, (LPCWSTR)0, 0u);
    (void) MkParseDisplayNameEx((IBindCtx *)0, (LPWSTR)0,
                                (ULONG *)0, &pmk);
    (void) ObtainUserAgentString(0u, (LPCSTR)0, (DWORD *)0);
    (void) RegisterBindStatusCallback((IBindCtx *)0,
                                      (IBindStatusCallback *)0,
                                      (IBindStatusCallback **)0, 0u);
    (void) RegisterFormatEnumerator((LPBC)0,
                                    (IEnumFORMATETC *)0, 0u);
    (void) RegisterMediaTypeClass((LPBC)0, 0u, (LPCSTR *)0,
                                  (CLSID *)0, 0u);
    (void) RegisterMediaTypes(0u, (LPCSTR *)0, &cf);
    (void) ReleaseBindInfo(&bi);
    (void) RevokeBindStatusCallback((IBindCtx *)0,
                                    (IBindStatusCallback *)0);
    (void) RevokeFormatEnumerator((LPBC)0, (IEnumFORMATETC *)0);
    (void) URLDownloadToCacheFileW((LPUNKNOWN)0, (LPCSTR)0,
                                   (LPTSTR)0, 0u, 0u,
                                   (IBindStatusCallback *)0);
    (void) URLDownloadToFileW((LPUNKNOWN)0, (LPCTSTR)0, (LPCTSTR)0,
                              0u, pbsc);
    (void) URLOpenBlockingStream((LPUNKNOWN)0, (LPCSTR)0,
                                 (LPSTREAM *)0, 0u, pbsc);
    (void) URLOpenPullStream((LPUNKNOWN)0, (LPCSTR)0, 0u, pbsc);
    (void) URLOpenStream((LPUNKNOWN)0, (LPCSTR)0, 0u, pbsc);
    (void) UrlMkGetSessionOption(0u, (LPVOID)0, 0u, (DWORD *)0, 0u);
    (void) UrlMkSetSessionOption(0u, (LPVOID)0, 0u, 0u);
    (void) WriteHitLogging(&hli);

    (void) bf; (void) pif; (void) bio; (void) mkp; (void) ue;
    (void) puaf; (void) szm; (void) ut; (void) zaf; (void) psu;
    (void) bs; (void) pa; (void) qo; (void) uz; (void) uzr;
    (void) bif; (void) bv; (void) bscf; (void) bst; (void) cf;
    (void) pd; (void) pfd; (void) hli; (void) bi; (void) pses;
    (void) pmk; (void) pbc; (void) pbsc; (void) pbcx;
    return 0;
}

#if __SIZEOF_POINTER__ == 4
/* M63: Waveform Audio / Mixer / Timer 32-bit CE sizes (transcribed CE
 * 5.0 prints; MMVERSION=UINT and the MIXER_*_NAME_CHARS /
 * MAXERRORLENGTH lengths are recorded own-design closures). */
_Static_assert(sizeof(WAVEFORMATEX) == 20, "WAVEFORMATEX size (aa452419)");
_Static_assert(sizeof(WAVEHDR) == 32, "WAVEHDR size (aa452420)");
_Static_assert(sizeof(WAVEINCAPS) == 48, "WAVEINCAPS size (aa452422)");
_Static_assert(sizeof(WAVEOUTCAPS) == 52, "WAVEOUTCAPS size (aa452442)");
_Static_assert(sizeof(STREAMPROPS) == 8, "STREAMPROPS size (aa452383)");
_Static_assert(sizeof(AUDIOGAINCLASS) == 8, "AUDIOGAINCLASS size (ms925607)");
_Static_assert(sizeof(MMTIME) == 12, "MMTIME size (aa447864)");
_Static_assert(offsetof(MMTIME, u) == 4, "MMTIME union offset (aa447864)");
_Static_assert(sizeof(TIMECAPS) == 8, "TIMECAPS size (aa448189)");
_Static_assert(sizeof(MIXERCAPS) == 80, "MIXERCAPS size (ms932036)");
_Static_assert(sizeof(MIXERCONTROL) == 148, "MIXERCONTROL size (ms932038)");
_Static_assert(offsetof(MIXERCONTROL, Bounds) == 100,
               "MIXERCONTROL name arrays (ms932038)");
_Static_assert(sizeof(MIXERCONTROLDETAILS) == 24, "MIXERCONTROLDETAILS size (ms932039)");
_Static_assert(sizeof(MIXERCONTROLDETAILS_LISTTEXT) == 72,
               "MIXERCONTROLDETAILS_LISTTEXT size (ms932041)");
_Static_assert(sizeof(MIXERCONTROLDETAILS_BOOLEAN) == 4, "ms932040");
_Static_assert(sizeof(MIXERCONTROLDETAILS_SIGNED) == 4, "ms932042");
_Static_assert(sizeof(MIXERCONTROLDETAILS_UNSIGNED) == 4, "ms932043");
_Static_assert(sizeof(MIXERLINE) == 168, "MIXERLINE size (ms932050)");
_Static_assert(offsetof(MIXERLINE, Target) == 120, "MIXERLINE Target offset (ms932050)");
_Static_assert(sizeof(MIXERLINECONTROLS) == 24, "MIXERLINECONTROLS size (ms932051)");
_Static_assert(MAXPNAMELEN == 32, "MAXPNAMELEN printed value (aa452442)");
#endif

/* M63: Waveform Audio / Mixer / Timer shaped usage. */
static int m63_shaped_usage(void)
{
    WAVEFORMATEX   wfx;
    WAVEHDR        wh;
    WAVEINCAPS     wic;
    WAVEOUTCAPS    woc;
    MMTIME         mmt;
    TIMECAPS       tc;
    MIXERCAPS      mxc;
    MIXERCONTROL   mxctl;
    MIXERCONTROLDETAILS mxcd;
    MIXERLINE      mxl;
    MIXERLINECONTROLS mxlc;
    STREAMPROPS    sp;
    AUDIOGAINCLASS agc;
    HWAVEIN        hwi = (HWAVEIN)0;
    HWAVEOUT       hwo = (HWAVEOUT)0;
    HMIXER         hmx = (HMIXER)0;
    HMIXEROBJ      hmxo = (HMIXEROBJ)0;
    LPTIMECALLBACK tcb = (LPTIMECALLBACK)0;
    DWORD          dw = 0;

    wfx.wFormatTag = 1; wfx.nChannels = 1; wfx.nSamplesPerSec = 8000;
    wfx.nAvgBytesPerSec = 8000; wfx.nBlockAlign = 1;
    wfx.wBitsPerSample = 8; wfx.cbSize = 0;
    wh.lpData = (LPSTR)0; wh.dwBufferLength = 0; wh.dwFlags = 0;
    wic.wMid = 0; woc.wMid = 0;
    mmt.wType = 0; mmt.u.ms = 0;
    tc.wPeriodMin = 0;
    mxc.cDestinations = 0;
    mxctl.cbStruct = sizeof(MIXERCONTROL);
    mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS); mxcd.cbDetails = 0;
    mxl.cbStruct = sizeof(MIXERLINE);
    mxlc.cbStruct = sizeof(MIXERLINECONTROLS);
    sp.dwClassID = 0; agc.dwPriority = 0;

    (void) PlaySound((LPCSTR)0, (HMODULE)0, 0u);
    (void) sndPlaySound((LPCTSTR)0, 0u);
    (void) waveInOpen(&hwi, 0u, &wfx, 0u, 0u, 0u);
    (void) waveInAddBuffer(hwi, &wh, sizeof(WAVEHDR));
    (void) waveInPrepareHeader(hwi, &wh, sizeof(WAVEHDR));
    (void) waveInUnprepareHeader(hwi, &wh, sizeof(WAVEHDR));
    (void) waveInGetDevCaps(0u, &wic, sizeof(WAVEINCAPS));
    (void) waveInGetErrorText(0u, (LPTSTR)0, 0u);
    (void) waveInGetID(hwi, (PUINT)0);
    (void) waveInGetPosition(hwi, &mmt, sizeof(MMTIME));
    (void) waveInGetProperty(0u, (const GUID *)0, 0u, (LPVOID)0, 0u,
                             (LPVOID)0, 0u, (PULONG)0);
    (void) waveInMessage(hwi, 0u, 0u, 0u);
    (void) waveInReset(hwi);
    (void) waveInSetProperty(0u, (const GUID *)0, 0u, (LPVOID)0, 0u,
                             (LPVOID)0, 0u);
    (void) waveInStart(hwi);
    (void) waveInStop(hwi);
    (void) waveInClose(hwi);
    (void) waveOutOpen(&hwo, 0u, &wfx, 0u, 0u, 0u);
    (void) waveOutWrite(hwo, &wh, sizeof(WAVEHDR));
    (void) waveOutGetDevCaps(0u, &woc, sizeof(WAVEOUTCAPS));
    (void) waveOutGetPitch(hwo, &dw);
    (void) waveOutGetPlaybackRate(hwo, &dw);
    (void) waveOutGetVolume(hwo, &dw);
    (void) waveOutSetVolume(hwo, dw);
    (void) waveOutPause(hwo);
    (void) waveOutRestart(hwo);
    (void) waveOutReset(hwo);
    (void) waveOutBreakLoop(hwo);
    (void) waveOutClose(hwo);
    (void) mixerOpen(&hmx, 0u, 0u, 0u, 0u);
    (void) mixerGetDevCaps(0u, &mxc, sizeof(MIXERCAPS));
    (void) mixerGetLineInfo(hmxo, &mxl, 0u);
    (void) mixerGetLineControls(hmxo, &mxlc, 0u);
    (void) mixerGetControlDetails(hmxo, &mxcd, 0u);
    (void) mixerSetControlDetails(hmxo, &mxcd, 0u);
    (void) mixerGetID(hmxo, (UINT *)0, 0u);
    (void) mixerMessage(hmx, 0u, 0u, 0u);
    (void) mixerClose(hmx);
    (void) timeBeginPeriod(1u);
    (void) timeEndPeriod(1u);
    (void) timeGetDevCaps(&tc, sizeof(TIMECAPS));
    (void) timeSetEvent(1u, 0u, tcb, 0u, 0u);
    (void) timeKillEvent(0u);
    (void) timeGetSystemTime(&mmt, sizeof(MMTIME));
    dw = timeGetTime();
    dw = timeGetHardwareFrequency();
    dw = timeGetTimeSinceInterrupt();

    (void) wfx; (void) wh; (void) wic; (void) woc; (void) mmt;
    (void) tc; (void) mxc; (void) mxctl; (void) mxcd; (void) mxl;
    (void) mxlc; (void) sp; (void) agc; (void) hwi; (void) hwo;
    (void) hmx; (void) hmxo; (void) tcb; (void) dw;
    return 0;
}

#if __SIZEOF_POINTER__ == 4
/* M64: Imaging API 32-bit CE sizes (transcribed CE 5.0 prints; the CE
 * 6.0 twins print identical bodies -- ee491598/ee490848/ee490096/
 * ee490079/ee491100/ee491044/ee490672). */
_Static_assert(sizeof(BitmapData) == 24, "BitmapData size (ms925969)");
_Static_assert(offsetof(BitmapData, Scan0) == 16, "BitmapData print (ms925969)");
_Static_assert(sizeof(ImageCodecInfo) == 76, "ImageCodecInfo size (aa452241)");
_Static_assert(offsetof(ImageCodecInfo, MimeType) == 48, "aa452241");
_Static_assert(sizeof(ImageInfo) == 64, "ImageInfo size incl. double align (aa452243)");
_Static_assert(offsetof(ImageInfo, Xdpi) == 40, "ImageInfo double offset (aa452243)");
_Static_assert(sizeof(ColorPalette) == 12, "ColorPalette size (ms926775)");
_Static_assert(sizeof(PropertyItem) == 16, "PropertyItem size (ms932269)");
_Static_assert(sizeof(EncoderParameter) == 28, "EncoderParameter size (aa451679)");
_Static_assert(sizeof(EncoderParameters) == 32, "EncoderParameters size (aa451680)");
/* M64 enum values (printed) + sequential readings (recorded). */
_Static_assert(DecoderInitFlagNoBlock == 0x0001 && DecoderInitFlagBuiltIn1st == 0x0002, "aa451570");
_Static_assert(EncoderParameterValueTypeRationalRange == 8, "aa451681");
_Static_assert(ImageCodecFlagsUser == 0x00040000, "aa452239");
_Static_assert(ImageFlagsValid == 0x00030000, "aa452242");
_Static_assert(ImageLockModeUserInputBuf == 0x0004, "aa452244");
_Static_assert(SinkFlagsWantProps == 0x00200000, "ms932307");
_Static_assert((int)SinkFlagsScalable == (int)ImageFlagsScalable, "ms932307 alias");
_Static_assert(BufferDisposalFlagUnmapView == 3, "ms936849 sequential");
_Static_assert(InterpolationHintBicubic == 4, "ms912048 sequential");
_Static_assert(EncoderValueFrameDimensionPage == 23, "aa451682 sequential");
/* M64: PropertyTag Values -- printed tags (ms932271), spot checks. */
_Static_assert(PropertyTagArtist == 0x013B, "ms932271");
_Static_assert(PropertyTagCompression == 0x0103, "ms932271");
_Static_assert(PropertyTagExifPixXDim == 0xA002, "ms932271");
_Static_assert(PropertyTagExifPixYDim == 0xA003, "ms932271");
_Static_assert(PropertyTagThumbnailResolutionY == 0x502E, "ms932271");
_Static_assert(PropertyTagLuminanceTable == 0x5090, "ms932271");
#endif

/* M64: Imaging API shaped usage (COM types only; no import surface). */
static int m64_shaped_usage(void)
{
    BitmapData       bd;
    ImageCodecInfo   ici;
    ImageInfo        ii;
    ColorPalette     cp;
    PropertyItem     pi;
    EncoderParameter ep;
    EncoderParameters eps;
    ARGB             argb;
    PixelFormat      pf;
    PixelFormatID    pfid;
    IImagingFactory *pif = (IImagingFactory *)0;
    IImage          *pimg = (IImage *)0;
    IBitmapImage    *pbmp = (IBitmapImage *)0;
    IBasicBitmapOps *pbbo = (IBasicBitmapOps *)0;
    IImageDecoder   *pdec = (IImageDecoder *)0;
    IImageEncoder   *penc = (IImageEncoder *)0;
    IImageSink      *psink = (IImageSink *)0;
    IStream         *pstm = (IStream *)0;

    bd.Width = 1; bd.Height = 1; bd.Stride = 1;
    bd.PixelFormat = 1; bd.Scan0 = 0; bd.Reserved = 0;
    ici.Clsid = ici.FormatID; ici.CodecName = ici.MimeType;
    ici.Flags = ImageCodecFlagsDecoder; ici.SigCount = 0;
    ii.RawDataFormat = ici.FormatID; ii.PixelFormat = 0;
    ii.Width = ii.Height = ii.TileWidth = ii.TileHeight = 0;
    ii.Xdpi = 96.0; ii.Ydpi = 96.0; ii.Flags = ImageFlagsNone;
    cp.Flags = 0; cp.Count = 1; cp.Entries[0] = MAKEARGB(0xff, 0x12, 0x34, 0x56);
    pi.id = PropertyTagArtist; pi.length = 6;
    pi.type = 0; pi.value = (VOID *)0;
    ep.Guid = ii.RawDataFormat; ep.NumberOfValues = 1;
    ep.Type = EncoderParameterValueTypeLong; ep.Value = (VOID *)0;
    eps.Count = 1; eps.Parameter[0] = ep;
    argb = MAKEARGB(0x0a, 0xbc, 0xde, 0xf0);
    pf = (PixelFormat)ImageFlagsNone;
    pfid = (PixelFormatID)0;
    (void) pif; (void) pimg; (void) pbmp; (void) pbbo; (void) pdec;
    (void) penc; (void) psink; (void) pstm; (void) pf; (void) argb;
    (void) BufferDisposalFlagGlobalFree; (void) InterpolationHintBilinear;
    (void) EncoderValueTransformRotate90; (void) SinkFlagsTopDown;
    (void) ImageLockModeRead; (void) DecoderInitFlagNoBlock;
    (void) bd; (void) ici; (void) ii; (void) cp; (void) pi; (void) ep;
    (void) eps;
    return (int)(argb & ALPHA_MASK) + (int)pfid;
}

#if __SIZEOF_POINTER__ == 4
/* M65: POOM constants -- printed values (aa513746). */
_Static_assert(olFolderInfrared == 102, "aa513746");
_Static_assert(olRecursYearNth == 6, "aa513746");
_Static_assert(olSaturday == 64, "aa513746");
_Static_assert(olOutOfOffice == 3, "aa513746");
_Static_assert(PT_CONTACT == 2, "ms863874 PIMTYPE print");
#endif

/* M65: POOM shaped usage (COM surface + add-in entry point). */
static int m65_shaped_usage(void)
{
    HWND        hwnd = (HWND)0;
    HANDLE      h = (HANDLE)0;
    PIMTYPE     pt = PT_CALENDAR;
    PFNCEPIMCOMMAND pfn = (PFNCEPIMCOMMAND)0;
    IPOutlookApp         *app = (IPOutlookApp *)0;
    IAppointment         *appt = (IAppointment *)0;
    IContact             *ct = (IContact *)0;
    ITask                *tk = (ITask *)0;
    IRecurrencePattern   *rp = (IRecurrencePattern *)0;
    IException           *ex = (IException *)0;
    IExceptions          *exs = (IExceptions *)0;
    IFolder              *fld = (IFolder *)0;
    IPOutlookItemCollection *ic = (IPOutlookItemCollection *)0;
    IPOlRecipient        *polr = (IPOlRecipient *)0;
    IRecipient           *rc = (IRecipient *)0;
    IRecipients          *rcs = (IRecipients *)0;
    ITimeZone            *tz = (ITimeZone *)0;

    CePimCommand(hwnd, pt, 1u, &h, (void *)0);
    pt = (PIMTYPE)(olAppointmentItem | olContactItem | olTaskItem);
    (void) pfn; (void) app; (void) appt; (void) ct; (void) tk;
    (void) rp; (void) ex; (void) exs; (void) fld; (void) ic;
    (void) polr; (void) rc; (void) rcs; (void) tz;
    return (int)olFolderTasks + olRecursMonthly + olWednesday +
           olSound + olBusy + olPrivate + olMeeting + olImportanceHigh +
           (int)PT_TASKS + (int)PT_CONTACT;
}

#if __SIZEOF_POINTER__ == 4
/* M66: MSXML DOMNodeType -- printed values (ms897200; NODE_INVALID=0 by
 * position, no description printed). */
_Static_assert(NODE_ELEMENT == 1 && NODE_ATTRIBUTE == 2, "ms897200");
_Static_assert(NODE_TEXT == 3 && NODE_CDATA_SECTION == 4, "ms897200");
_Static_assert(NODE_ENTITY_REFERENCE == 5 && NODE_ENTITY == 6, "ms897200");
_Static_assert(NODE_PROCESSING_INSTRUCTION == 7 && NODE_COMMENT == 8, "ms897200");
_Static_assert(NODE_DOCUMENT == 9 && NODE_DOCUMENT_TYPE == 10, "ms897200");
_Static_assert(NODE_DOCUMENT_FRAGMENT == 11 && NODE_NOTATION == 12, "ms897200");
#endif

/* M66: MSXML shaped usage (COM surface only; no import surface). */
static int m66_shaped_usage(void)
{
    DOMNodeType nt = NODE_ELEMENT;
    IXMLDOMNode             *node = (IXMLDOMNode *)0;
    IXMLDOMDocument2        *doc = (IXMLDOMDocument2 *)0;
    IXMLDOMElement          *el = (IXMLDOMElement *)0;
    IXMLDOMSelection        *sel = (IXMLDOMSelection *)0;
    IXMLDOMSchemaCollection *sc = (IXMLDOMSchemaCollection *)0;
    IXMLDOMParseError       *pe = (IXMLDOMParseError *)0;
    IXMLHTTPRequest         *hr = (IXMLHTTPRequest *)0;
    IXTLRuntime             *xt = (IXTLRuntime *)0;
    ISAXXMLReader           *saxr = (ISAXXMLReader *)0;
    ISAXContentHandler      *saxc = (ISAXContentHandler *)0;
    ISAXAttributes          *saxa = (ISAXAttributes *)0;
    ISAXErrorHandler        *saxe = (ISAXErrorHandler *)0;
    IMXWriter               *mw = (IMXWriter *)0;
    IMXAttributes           *ma = (IMXAttributes *)0;
    IMXReaderControl        *mrc = (IMXReaderControl *)0;
    ISAXXMLFilter           *sf = (ISAXXMLFilter *)0;
    ISAXLocator             *sl = (ISAXLocator *)0;
    ISAXLexicalHandler      *slh = (ISAXLexicalHandler *)0;
    ISAXDeclHandler         *sdh = (ISAXDeclHandler *)0;
    ISAXDTDHandler          *sdtd = (ISAXDTDHandler *)0;
    ISAXEntityResolver      *ser = (ISAXEntityResolver *)0;

    nt = NODE_DOCUMENT;
    (void) node; (void) doc; (void) el; (void) sel; (void) sc; (void) pe;
    (void) hr; (void) xt; (void) saxr; (void) saxc; (void) saxa;
    (void) saxe; (void) mw; (void) ma; (void) mrc; (void) sf; (void) sl;
    (void) slh; (void) sdh; (void) sdtd; (void) ser;
    return (int)nt;
}

#if __SIZEOF_POINTER__ == 4
/* M67: D3DM sizes (verbatim CE 5.0 prints; D3DMVALUE = signed int). */
_Static_assert(sizeof(D3DMDISPLAYMODE) == 16, "ms907703");
_Static_assert(sizeof(D3DMCOLORVALUE) == 16, "ms939143");
_Static_assert(sizeof(D3DMVECTOR) == 12, "ms907757");
_Static_assert(sizeof(D3DMMATRIX) == 64, "ms907720 union print");
_Static_assert(sizeof(D3DMCLIPSTATUS) == 8, "ms939140");
_Static_assert(sizeof(D3DMLOCKED_RECT) == 8, "ms907718");
_Static_assert(sizeof(D3DMVIEWPORT) == 24, "ms907759");
/* M67: D3DM enum values (printed). */
_Static_assert(D3DMPOOL_MANAGED == 2, "ms907725");
_Static_assert(D3DMFMT_D24S8 == 23 && D3DMFMT_INDEX32 == 28, "ms907707");
_Static_assert(D3DMBLEND_SRCALPHASAT == 11, "ms939135");
_Static_assert(D3DMRENDERSTATE_WRAPBIAS == 32, "ms907738");
_Static_assert(D3DMPV_VALID == D3DMPV_DONOTCOPYDATA, "ms907762 print");
_Static_assert(D3DMERR_DEVICELOST == MAKE_D3DMHRESULT(2152), "aa451582");
_Static_assert(D3DMERR_ALREADYLOCKED == MAKE_D3DMHRESULT(2158), "aa451582");
_Static_assert(MAKE_D3DMHRESULT(0) ==
               MAKE_HRESULT(1, 0x877, 0), "ms932027");
#endif

/* M67: D3DM shaped usage. */
static int m67_shaped_usage(void)
{
    D3DMDISPLAYMODE dm;
    D3DMMATRIX       mx;
    D3DMVIEWPORT     vp;
    D3DMLIGHT        lt;
    IDirect3DMobile           *d3d = (IDirect3DMobile *)0;
    IDirect3DMobileDevice     *dev = (IDirect3DMobileDevice *)0;
    IDirect3DMobileResource   *res = (IDirect3DMobileResource *)0;
    IDirect3DMobileBaseTexture *btex = (IDirect3DMobileBaseTexture *)0;
    IDirect3DMobileSurface    *surf = (IDirect3DMobileSurface *)0;
    IDirect3DMobileTexture    *tex = (IDirect3DMobileTexture *)0;
    IDirect3DMobileVertexBuffer *vb = (IDirect3DMobileVertexBuffer *)0;
    IDirect3DMobileIndexBuffer *ib = (IDirect3DMobileIndexBuffer *)0;
    IDirect3DMobileSwapChain   *sc = (IDirect3DMobileSwapChain *)0;
    D3DMCOLOR c;

    dm.Width = 240; dm.Height = 320; dm.RefreshRate = 0;
    dm.Format = D3DMFMT_R5G6B5;
    mx.m[0][0] = 1; mx._11 = 1;
    vp.X = 0; vp.Y = 0; vp.Width = 240; vp.Height = 320;
    vp.MinZ = 0.0f; vp.MaxZ = 1.0f;
    lt.Type = D3DMLIGHT_POINT;
    c = D3DMCOLOR_ARGB(0xff, 0x80, 0x40, 0x20);
    c = D3DMCOLOR_XRGB(1, 2, 3);
    d3d = Direct3DMobileCreate(0u);

    (void) dm; (void) vp; (void) lt; (void) c; (void) mx;
    (void) d3d; (void) dev; (void) res; (void) btex; (void) surf;
    (void) tex; (void) vb; (void) ib; (void) sc;
    return (int)c;
}

#if __SIZEOF_POINTER__ == 4
/* M68: SAPI sizes (verbatim prints; WPARAM/LPARAM are 4-byte on CE). */
_Static_assert(sizeof(SPEVENT) == 24, "ms895371 print");
_Static_assert(sizeof(SPAUDIOBUFFERINFO) == 12, "ms893505 print");
_Static_assert(sizeof(SPPHRASEALT) == 24, "ms895681 print");
/* M68: SAPI enum values (printed). */
_Static_assert(SPEI_UNDEFINED == 0 && SPEI_TTS_BOOKMARK == 4, "SPEVENTENUM");
_Static_assert(SPAS_RUN == 3, "SPAUDIOSTATE sequential");
_Static_assert(SPF_ASYNC == (1L << 0) && SPF_PERSIST_XML == (1L << 5), "SPEAKFLAGS");
_Static_assert(SPFM_CREATE == 2, "SPFILEMODE sequential");
_Static_assert(SPSF_Default == -1 && SPSF_8kHz16BitMono != 0, "SPSTREAMFORMAT");
_Static_assert(SPPS_Noun == 0x1000 && SPPS_Interjection == 0x5000, "SPPARTOFSPEECH");
_Static_assert(eWORDTYPE_DELETED == (1L << 1), "SPWORDTYPE");
_Static_assert(SPVFEATURE_STRESSED == (1L << 0), "SPVFEATURE");
_Static_assert(SPMAX_RATE == 10 && SPMIN_RATE == -10, "SPVLIMITS");
_Static_assert(SPRAF_AutoPause == (1L << 16), "SPCFGRULEATTRIBUTES");
#endif

/* M68: SAPI shaped usage (COM surface only; no import surface). */
static int m68_shaped_usage(void)
{
    SPEVENT              ev;
    SPAUDIOBUFFERINFO    abi;
    SPPHRASEALT          alt;
    SPVSTATE             vst;
    SPPHONEID            ph;
    ISpVoice            *voice = (ISpVoice *)0;
    ISpRecognizer       *rec = (ISpRecognizer *)0;
    ISpRecoContext      *rctx = (ISpRecoContext *)0;
    ISpRecoGrammar      *rgrm = (ISpRecoGrammar *)0;
    ISpPhrase           *phr = (ISpPhrase *)0;
    ISpPhraseBuilder    *phb = (ISpPhraseBuilder *)0;
    ISpDataKey          *dk = (ISpDataKey *)0;
    ISpObjectToken      *tok = (ISpObjectToken *)0;
    ISpObjectTokenCategory *cat = (ISpObjectTokenCategory *)0;
    ISpEventSource      *es = (ISpEventSource *)0;
    ISpNotifySource     *ns = (ISpNotifySource *)0;
    ISpStream           *stm = (ISpStream *)0;
    ISpAudio            *aud = (ISpAudio *)0;
    ISpLexicon          *lex = (ISpLexicon *)0;
    ISpContainerLexicon *clex = (ISpContainerLexicon *)0;
    ISpTTSEngine        *tts = (ISpTTSEngine *)0;
    ISpSREngine         *sre = (ISpSREngine *)0;
    ISpMMSysAudio       *mma = (ISpMMSysAudio *)0;
    ISpStreamFormat     *sf = (ISpStreamFormat *)0;
    ISpGrammarBuilder   *gb = (ISpGrammarBuilder *)0;

    ev.eEventId = SPEI_TTS_BOOKMARK; ev.elParamType = SPET_LPARAM_IS_STRING;
    ev.ulStreamNum = 0; ev.ullAudioStreamOffset = 0; ev.wParam = 0;
    ev.lParam = 0;
    abi.ulMsMinNotification = 10; abi.ulMsBufferSize = 1000;
    abi.ulMsEventBias = 0;
    alt.pPhrase = phb; alt.ulStartElementInParent = 0; alt.cElementsInParent = 1;
    alt.cElementsInAlternate = 1; alt.pvAltExtra = 0; alt.cbAltExtra = 0;
    vst.eAction = SPVA_Speak; ph = (SPPHONEID)L'x';

    (void) voice; (void) rec; (void) rctx; (void) rgrm; (void) phr;
    (void) phb; (void) dk; (void) tok; (void) cat; (void) es;
    (void) ns; (void) stm; (void) aud; (void) lex; (void) clex;
    (void) tts; (void) sre; (void) mma; (void) sf;
    (void) gb; (void) vst; (void) ph;
    return (int)ev.eEventId + (int)abi.ulMsBufferSize + (int)alt.cElementsInAlternate;
}

#if __SIZEOF_POINTER__ == 4
/* M69: RTC constants -- printed values (Rtccore.h/Rtcerr.h pages). */
_Static_assert(RTCEF_CLIENT == 0x00000001, "ms931693");
_Static_assert(RTCEF_ALL == 0x01FFFFFF, "ms931693");
_Static_assert(RTCMT_T120_SENDRECV == 0x00000010, "RTCMT_ page");
_Static_assert(RTCSI_PHONE_TO_PHONE == 0x00000004, "RTCSI_ page");
_Static_assert(RTCTR_TLS == 0x00000004, "ms912587");
_Static_assert(RTC_E_CLIENT_NOT_INITIALIZED == 0x80EE0025L, "ms931795");
_Static_assert(RTC_S_ROAMING_NOT_SUPPORTED == 0x80EE0041L, "ms912578");
#endif

/* M69: RTC shaped usage (COM surface only; no import surface). */
static int m69_shaped_usage(void)
{
    RTC_EVENT          ev = RTCE_CLIENT;
    RTC_SESSION_TYPE   st = RTCST_IM;
    RTC_SESSION_STATE  ss = RTCSS_IDLE;
    RTC_ANSWER_MODE    am = RTCAM_AUTOMATICALLY_ACCEPT;
    RTC_DTMF           dt = RTC_DTMF_STAR;
    OAHWND             hwnd = (OAHWND)0;
    IRTCClient              *cli = (IRTCClient *)0;
    IRTCClient2             *cli2 = (IRTCClient2 *)0;
    IRTCClientPresence      *cp = (IRTCClientPresence *)0;
    IRTCClientPresence2     *cp2 = (IRTCClientPresence2 *)0;
    IRTCClientProvisioning  *cprov = (IRTCClientProvisioning *)0;
    IRTCProfile             *prof = (IRTCProfile *)0;
    IRTCProfile2            *prof2 = (IRTCProfile2 *)0;
    IRTCSession             *sess = (IRTCSession *)0;
    IRTCSession2            *sess2 = (IRTCSession2 *)0;
    IRTCParticipant         *part = (IRTCParticipant *)0;
    IRTCBuddy               *bud = (IRTCBuddy *)0;
    IRTCBuddyGroup          *grp = (IRTCBuddyGroup *)0;
    IRTCWatcher             *wat = (IRTCWatcher *)0;
    IRTCEventNotification   *en = (IRTCEventNotification *)0;
    IRTCMediaEvent          *mev = (IRTCMediaEvent *)0;
    IRTCMessagingEvent      *msev = (IRTCMessagingEvent *)0;
    IRTCRegistrationStateChangeEvent *rsce = (IRTCRegistrationStateChangeEvent *)0;
    IRTCSessionStateChangeEvent *ssce = (IRTCSessionStateChangeEvent *)0;
    IRTCIntensityEvent      *iev = (IRTCIntensityEvent *)0;
    IRTCPortManager         *pm = (IRTCPortManager *)0;
    IRTCUserSearch          *us = (IRTCUserSearch *)0;
    IRTCUserSearchQuery     *usq = (IRTCUserSearchQuery *)0;
    IRTCCollection          *col = (IRTCCollection *)0;

    ev = RTCE_SESSION_STATE_CHANGE; st = RTCST_PC_TO_PC;
    ss = RTCSS_CONNECTED; am = RTCAM_AUTOMATICALLY_REJECT; dt = RTC_DTMF_POUND;
    (void) hwnd; (void) cli; (void) cli2; (void) cp; (void) cp2;
    (void) cprov; (void) prof; (void) prof2; (void) sess; (void) sess2;
    (void) part; (void) bud; (void) grp; (void) wat; (void) en;
    (void) mev; (void) msev; (void) rsce; (void) ssce; (void) iev;
    (void) pm; (void) us; (void) usq; (void) col;
    return (int)ev + (int)st + (int)ss + (int)am + (int)dt +
           RTCEF_MESSAGING + RTCIF_DISABLE_UPNP + RTCRF_REGISTER_NOTIFY +
           RTCRMF_WATCHER_ROAMING + RTCAU_NTLM + RTCCS_FORCE_PROFILE;
}

#if __SIZEOF_POINTER__ == 4
/* M70: CEDB structure sizes (verbatim prints; 32-bit pointer model).
 * CEVALUNION/CEPROPVAL embed 8-byte double + pointers, CEBLOB and
 * CEPROPSPEC embed pointers, so these only hold on the CE ABI. */
_Static_assert(sizeof(CEGUID) == 16, "closure: Data1..Data4 DWORDs");
_Static_assert(sizeof(CEOID) == 4 && sizeof(CEPROPID) == 4, "carrier closures");
_Static_assert(sizeof(CEBLOB) == 8, "aa516981 print");
_Static_assert(sizeof(CEVALUNION) == 8, "aa517283 print");
_Static_assert(sizeof(SORTORDERSPEC) == 8, "ms891997 print");
_Static_assert(sizeof(CEPROPVAL) == 16, "aa517227 print");
_Static_assert(sizeof(CERECORDINFO) == 4, "aa517237 print");
_Static_assert(sizeof(CEFILEINFO) == 540, "aa517101 print, MAX_PATH 260");
_Static_assert(sizeof(CEDIRINFO) == 528, "aa517001 print, MAX_PATH 260");
_Static_assert(sizeof(CENOTIFICATION) == 36, "aa517186 print");
_Static_assert(sizeof(CENOTIFYREQUEST) == 20, "aa517189 print");
#if !defined(_WIN32_WCE) || (_WIN32_WCE) >= 0x500
_Static_assert(sizeof(CEPROPSPEC) == 20, "aa517225 print (EDB)");
#endif
#endif

/* M70: the CREATE_ and CHECK_ macro families expand to memset and
   bitwise tests; the TU is freestanding (no <string.h>), so memset is
   declared here with the exact builtin prototype (size_t via the
   already-included stddef.h). */
void *memset(void *s, int c, size_t n);

/* M70: windbase shaped usage (CEDB unguarded + EDB under the CE5
   guard; calls are never executed, TU is compile-only). */
static int m70_shaped_usage(void)
{
    CEGUID          guid;
    HANDLE          hdb;
    CEBLOB          blob;
    CEPROPVAL       propval;
    CEFILEINFO      fileinfo;
    CEDIRINFO       dirinfo;
    CENOTIFYREQUEST notifyreq;
    SORTORDERSPEC   sortspec;
    CEOID           oid;
    PCEOID          poid = (PCEOID)0;

    CREATE_SYSTEMGUID(&guid);
    if (!CHECK_SYSTEMGUID(&guid))
        return 1;
    if (CHECK_INVALIDGUID(&guid))   /* all-zero GUID is not "invalid" */
        return 2;
    CREATE_INVALIDGUID(&guid);
    if (!CHECK_INVALIDGUID(&guid))
        return 3;
    if (CHECK_SYSTEMGUID(&guid))
        return 4;
    if (TypeFromPropID(0x00140005u) != 5)   /* ms892256: LOWORD */
        return 5;

    blob.dwCount = 0; blob.lpb = (LPBYTE)0;
    propval.propid = 0x00140005u; propval.wLenData = 0;
    propval.wFlags = 0; propval.val.ulVal = 7u;
    fileinfo.dwAttributes = 0; fileinfo.oidParent = 0;
    fileinfo.szFileName[0] = 0;
    fileinfo.ftLastChanged.dwLowDateTime = 0;
    fileinfo.ftLastChanged.dwHighDateTime = 0;
    fileinfo.dwLength = 0;
    dirinfo.dwAttributes = 0; dirinfo.oidParent = 0;
    dirinfo.szDirName[0] = 0;
    notifyreq.dwSize = sizeof(notifyreq); notifyreq.hwnd = (HWND)0;
    notifyreq.dwFlags = 0; notifyreq.hHeap = (HANDLE)0;
    notifyreq.dwParam = 0;
    sortspec.propid = 0x00140005u; sortspec.dwFlags = 0;

    oid = CeCreateDatabase((LPWSTR)0, 0u, 0u, &sortspec);
    oid = CeCreateDatabaseEx(&guid, (CEDBASEINFO *)0);
    oid = CeCreateDatabaseEx2(&guid, (CEDBASEINFOEX *)0);
    CeChangeDatabaseLCID(&guid, 0u);
    oid = CeFindNextDatabase((HANDLE)0);
    oid = CeFindNextDatabaseEx((HANDLE)0, &guid);
    hdb = CeOpenDatabase(poid, (LPWSTR)0, 0x00140005u, 0u, (HWND)0);
    hdb = CeOpenDatabaseEx2(&guid, poid, (LPWSTR)0,
                            (SORTORDERSPECEX *)0, 0u, &notifyreq);
    oid = CeReadRecordPropsEx((HANDLE)0, 0u, (LPWORD)0, (CEPROPID *)0,
                              (LPBYTE *)0, (LPDWORD)0, (HANDLE)0);
    oid = CeSeekDatabaseEx((HANDLE)0, 0u, 0u, 0u, (LPDWORD)0);
    oid = CeWriteRecordProps((HANDLE)0, (CEOID)0, 1u, &propval);
    (void)CeMountDBVol(&guid, (LPWSTR)0, 0u);
    (void)CeOidGetInfoEx2(&guid, (CEOID)0, (CEOIDINFOEX *)0);
    (void)CeGetDBInformationByHandle((HANDLE)0,
                                     (LPBY_HANDLE_DB_INFORMATION)0);
    (void)CeFreeNotification(&notifyreq, (PCENOTIFICATION)0);
    (void)blob; (void)fileinfo; (void)dirinfo; (void)propval;

#if !defined(_WIN32_WCE) || (_WIN32_WCE) >= 0x500
    {
        CEPROPSPEC         propspec;
        CEDBISOLATIONLEVEL isolevel = 0;
        CESORTORDERSPECEX *psoex = (CESORTORDERSPECEX *)0;

        propspec.wVersion = 0; propspec.propid = 0x00140005u;
        propspec.dwFlags = 0; propspec.pwszPropName = (LPWSTR)0;
        propspec.cchPropName = 0;
        hdb = CeCreateSession(&guid);
        (void)CeBeginTransaction((HANDLE)0, isolevel);
        (void)CeEndTransaction((HANDLE)0, 0);
        oid = CeCreateDatabaseWithProps(&guid, (CEDBASEINFOEX *)0, 1u,
                                        &propspec);
        hdb = CeOpenDatabaseInSession((HANDLE)0, &guid, poid, (LPWSTR)0,
                                       (SORTORDERSPECEX *)0, 0u,
                                       &notifyreq);
        hdb = CeOpenStream((HANDLE)0, 0x00140005u, 0u);
        (void)CeMountDBVolEx(&guid, (LPWSTR)0, (CEVOLUMEOPTIONS *)0, 0u);
        (void)CeStreamRead((HANDLE)0, (LPBYTE)0, 0u, (LPDWORD)0);
        (void)CeStreamSeek((HANDLE)0, 0u, 0u, (LPDWORD)0);
        (void)CeSetSessionOption((HANDLE)0, 0u, 0u);
        (void)CeRemoveDatabaseProps(&guid, (CEOID)0, 0u, (CEPROPID *)0);
        (void)psoex; (void)propspec;
    }
#endif
    (void)oid; (void)hdb;
    return 0;
}

#if __SIZEOF_POINTER__ == 4
/* M70b: DirectShow structure sizes (verbatim prints; 32-bit CE ABI;
 * REFERENCE_TIME/LONGLONG members pin the 8-byte alignment rows). */
_Static_assert(sizeof(ALLOCATOR_PROPERTIES) == 16, "ms925330 print");
_Static_assert(sizeof(AM_MEDIA_TYPE) == 72, "ms925337 print");
_Static_assert(sizeof(AM_SAMPLE2_PROPERTIES) == 48, "ms925343 print");
_Static_assert(sizeof(AM_STREAM_INFO) == 32, "ms925345 print");
_Static_assert(sizeof(AMOVIESETUP_MEDIATYPE) == 8, "ms925341 print");
_Static_assert(sizeof(AMOVIESETUP_PIN) == 36, "ms925342 print");
_Static_assert(sizeof(AMOVIESETUP_FILTER) == 20, "ms925340 print");
_Static_assert(sizeof(AMVPSIZE) == 8, "ms925349 print");
_Static_assert(sizeof(AUDIO_STREAM_CONFIG_CAPS) == 52, "ms925720 print (GUID + 9 ULONG)");
_Static_assert(sizeof(COLORKEY) == 16, "ms926774 print");
_Static_assert(sizeof(DIBDATA) == 100, "aa451578 print");
_Static_assert(sizeof(FILTER_INFO) == 260, "aa451713 print");
_Static_assert(sizeof(VIDEOINFOHEADER) == 88, "aa452412 print");
_Static_assert(sizeof(VIDEOINFOHEADER2) == 112, "aa452413 print");
_Static_assert(sizeof(MPEG1VIDEOINFO) == 104, "ms932232 print (align 8 via REFERENCE_TIME)");
_Static_assert(sizeof(MPEG2VIDEOINFO) == 136, "ms932235 print");
_Static_assert(sizeof(PIN_INFO) == 264, "ms932256 print");
_Static_assert(sizeof(Quality) == 24, "ms932272 print");
_Static_assert(sizeof(REGFILTER) == 20, "ms932283 print");
_Static_assert(sizeof(REGPINTYPES) == 8, "ms932285 print");
_Static_assert(sizeof(REGFILTERPINS) == 36, "ms932284 print");
_Static_assert(sizeof(TIMECODE) == 6, "aa452390 print");
_Static_assert(sizeof(TIMECODE_SAMPLE) == 24, "aa452392 print");
_Static_assert(sizeof(VIDEO_STREAM_CONFIG_CAPS) == 128, "aa452415 print");
#endif
/* M70b: DirectShow enum values (printed). */
_Static_assert(State_Running == 2 && State_Stopped == 0, "FILTER_STATE");
_Static_assert(PINDIR_OUTPUT == 1 && PINDIR_INPUT == 0, "PIN_DIRECTION");
_Static_assert(AnalogVideo_NTSC_M == 0x00000001, "AnalogVideoStandard");
_Static_assert(MERIT_PREFERRED == 0x800000 && MERIT_HW_COMPRESSOR == 0x100050, "Merit");
_Static_assert(AM_SAMPLE_SPLICEPOINT == 0x01 && AM_STREAM_CONTROL == 1, "AM_SAMPLE_PROPERTY_FLAGS");
_Static_assert(AM_STREAM_INFO_DISCARDING == 0x00000004, "AM_STREAM_INFO_FLAGS");
_Static_assert(STREAMBUFFER_EC_TIMEHOLE == 0x326 && STREAMBUFFER_EC_RATE_CHANGED == 0x32c, "STREAMBUFFER_EC");
_Static_assert(KS_AM_RATE_Step == 4, "KS_AM_PROPERTY_TS_RATE_CHANGE");

/* M70b: dshow/dvdmedia shaped usage (data surface; no import calls --
   the book's function pages carry no Link Library rows). */
static int m70b_shaped_usage(void)
{
    FILTER_STATE         fst = State_Stopped;
    PIN_DIRECTION        pdir = PINDIR_INPUT;
    QualityMessageType   qmt = Famine;
    AM_MEDIA_TYPE        mt;
    AM_SAMPLE2_PROPERTIES sp2;
    AM_STREAM_INFO       si;
    AMOVIESETUP_FILTER   asf;
    ALLOCATOR_PROPERTIES ap;
    FILTER_INFO          fi;
    PIN_INFO             pi;
    VIDEOINFOHEADER      vih;
    VIDEOINFOHEADER2     vih2;
    MPEG2VIDEOINFO       mp2v;
    VIDEO_STREAM_CONFIG_CAPS vscc;
    Quality              q;
    TIMECODE_SAMPLE      tcs;
    struct __POSITION    pos;
    IBaseFilter          *bf = (IBaseFilter *)0;
    IFilterGraph         *fg = (IFilterGraph *)0;
    TRUECOLORINFO        *ptci = (TRUECOLORINFO *)0;
    VIDEOINFO            *pvi = (VIDEOINFO *)0;
    AMVPDATAINFO         *pavp = (AMVPDATAINFO *)0;
    LPAMVPDATAINFO       lpavp = (LPAMVPDATAINFO)0;
    STRMBUF_CAPTURE_MODE scm = STRMBUF_TEMPORARY_RECORDING;
    KS_AM_PROPERTY_TS_RATE_CHANGE rc = KS_AM_RATE_Step;

    memset(&mt, 0, sizeof(mt));
    mt.bFixedSizeSamples = 1; mt.lSampleSize = 0; mt.cbFormat = 0;
    mt.pUnk = (IUnknown *)0; mt.pbFormat = (BYTE *)0;
    sp2.cbData = sizeof(sp2); sp2.dwSampleFlags = AM_SAMPLE_TIMEVALID;
    sp2.tStart = 0; sp2.tStop = 1; sp2.pMediaType = &mt;
    si.tStart = 0; si.tStop = 0; si.dwFlags = AM_STREAM_INFO_DISCARDING;
    asf.clsID = (const CLSID *)0; asf.strName = (LPWSTR)0;
    asf.dwMerit = MERIT_NORMAL; asf.nPins = 0; asf.lpPin = (LPAMOVIESETUP_PIN)0;
    ap.cBuffers = 1; ap.cbBuffer = 2; ap.cbAlign = 4; ap.cbPrefix = 0;
    fi.achName[0] = 0; fi.pGraph = fg;
    pi.pFilter = bf; pi.dir = pdir; pi.achName[0] = 0;
    vih.rcSource.left = 0; vih.dwBitRate = 0; vih.AvgTimePerFrame = 0;
    vih2.dwInterlaceFlags = 0; vih2.dwPictAspectRatioX = 4; vih2.dwPictAspectRatioY = 3;
    mp2v.hdr = vih2; mp2v.dwProfile = MPEG2Profile_Main; mp2v.dwLevel = MPEG2Level_Main;
    memset(&vscc, 0, sizeof(vscc));
    vscc.VideoStandard = AnalogVideo_NTSC_M; vscc.MinFrameInterval = 1;
    q.Type = qmt; q.Proportion = 1000; q.Late = 0; q.TimeStamp = 0;
    tcs.qwTick = 0; tcs.timecode.wFrameRate = 30; tcs.timecode.dwFrames = 0;
    tcs.dwUser = 0; tcs.dwFlags = 0;
    pos.unused = 0;
    (void)fst; (void)scm; (void)rc; (void)ptci; (void)pvi; (void)pavp;
    (void)lpavp; (void)mt; (void)sp2; (void)si; (void)asf; (void)ap;
    (void)fi; (void)pi; (void)vih; (void)vih2; (void)mp2v; (void)vscc;
    (void)q; (void)tcs; (void)pos; (void)bf; (void)fg;
    return (int)fst + (int)pdir + (int)q.Type + (int)scm + (int)rc;
}

/* M71b: DirectShow interface forwards (61 opaque COM interfaces,
   M44/rtccore policy; method records are comment-only). */
static int m71_shaped_usage(void)
{
    IBaseFilter           *p_IBaseFilter = (IBaseFilter *)0;
    IFilterGraph          *p_IFilterGraph = (IFilterGraph *)0;
    IAMDevMemoryAllocator *p_IAMDevMemoryAllocator = (IAMDevMemoryAllocator *)0;
    IAMDevMemoryControl   *p_IAMDevMemoryControl = (IAMDevMemoryControl *)0;
    IAMDroppedFrames      *p_IAMDroppedFrames = (IAMDroppedFrames *)0;
    IAMMediaContent       *p_IAMMediaContent = (IAMMediaContent *)0;
    IAMMediaContentEx     *p_IAMMediaContentEx = (IAMMediaContentEx *)0;
    IAMPlayList           *p_IAMPlayList = (IAMPlayList *)0;
    IAMPlayListItem       *p_IAMPlayListItem = (IAMPlayListItem *)0;
    IAMStreamConfig       *p_IAMStreamConfig = (IAMStreamConfig *)0;
    IAMStreamControl      *p_IAMStreamControl = (IAMStreamControl *)0;
    IAMStreamSelect       *p_IAMStreamSelect = (IAMStreamSelect *)0;
    IAMTVTuner            *p_IAMTVTuner = (IAMTVTuner *)0;
    IAMTuner              *p_IAMTuner = (IAMTuner *)0;
    IAMovieSetup          *p_IAMovieSetup = (IAMovieSetup *)0;
    IAsyncReader          *p_IAsyncReader = (IAsyncReader *)0;
    IBasicAudio           *p_IBasicAudio = (IBasicAudio *)0;
    IBasicVideo           *p_IBasicVideo = (IBasicVideo *)0;
    IDMOWrapperFilter     *p_IDMOWrapperFilter = (IDMOWrapperFilter *)0;
    IDVREngineHelpers     *p_IDVREngineHelpers = (IDVREngineHelpers *)0;
    IDirectDrawVideo      *p_IDirectDrawVideo = (IDirectDrawVideo *)0;
    IDistributorNotify    *p_IDistributorNotify = (IDistributorNotify *)0;
    IEnumFilters          *p_IEnumFilters = (IEnumFilters *)0;
    IEnumMediaTypes       *p_IEnumMediaTypes = (IEnumMediaTypes *)0;
    IEnumPins             *p_IEnumPins = (IEnumPins *)0;
    IEnumRegFilters       *p_IEnumRegFilters = (IEnumRegFilters *)0;
    IFileSourceFilter     *p_IFileSourceFilter = (IFileSourceFilter *)0;
    IFilterGraph2         *p_IFilterGraph2 = (IFilterGraph2 *)0;
    IFilterMapper         *p_IFilterMapper = (IFilterMapper *)0;
    IGraphBuilder         *p_IGraphBuilder = (IGraphBuilder *)0;
    IGraphVersion         *p_IGraphVersion = (IGraphVersion *)0;
    IKsPropertySet        *p_IKsPropertySet = (IKsPropertySet *)0;
    IMediaControl         *p_IMediaControl = (IMediaControl *)0;
    IMediaEvent           *p_IMediaEvent = (IMediaEvent *)0;
    IMediaEventEx         *p_IMediaEventEx = (IMediaEventEx *)0;
    IMediaEventSink       *p_IMediaEventSink = (IMediaEventSink *)0;
    IMediaFilter          *p_IMediaFilter = (IMediaFilter *)0;
    IMediaPosition        *p_IMediaPosition = (IMediaPosition *)0;
    IMediaSample          *p_IMediaSample = (IMediaSample *)0;
    IMediaSample2         *p_IMediaSample2 = (IMediaSample2 *)0;
    IMediaSeeking         *p_IMediaSeeking = (IMediaSeeking *)0;
    IMediaStream          *p_IMediaStream = (IMediaStream *)0;
    IMemAllocator         *p_IMemAllocator = (IMemAllocator *)0;
    IMemInputPin          *p_IMemInputPin = (IMemInputPin *)0;
    IMultiMediaStream     *p_IMultiMediaStream = (IMultiMediaStream *)0;
    INonDelegatingUnknown *p_INonDelegatingUnknown = (INonDelegatingUnknown *)0;
    IOverlay              *p_IOverlay = (IOverlay *)0;
    IOverlayNotify        *p_IOverlayNotify = (IOverlayNotify *)0;
    IPin                  *p_IPin = (IPin *)0;
    IQualProp             *p_IQualProp = (IQualProp *)0;
    IQualityControl       *p_IQualityControl = (IQualityControl *)0;
    IReferenceClock       *p_IReferenceClock = (IReferenceClock *)0;
    ISeekingPassThru      *p_ISeekingPassThru = (ISeekingPassThru *)0;
    IStreamBufferCapture  *p_IStreamBufferCapture = (IStreamBufferCapture *)0;
    IStreamBufferPlayback *p_IStreamBufferPlayback = (IStreamBufferPlayback *)0;
    IStreamSample         *p_IStreamSample = (IStreamSample *)0;
    IVPBaseConfig         *p_IVPBaseConfig = (IVPBaseConfig *)0;
    IVPBaseNotify         *p_IVPBaseNotify = (IVPBaseNotify *)0;
    IVPConfig             *p_IVPConfig = (IVPConfig *)0;
    IVPNotify             *p_IVPNotify = (IVPNotify *)0;
    IVideoWindow          *p_IVideoWindow = (IVideoWindow *)0;

    (void)p_IBaseFilter; (void)p_IFilterGraph; (void)p_IAMDevMemoryAllocator; (void)p_IAMDevMemoryControl; (void)p_IAMDroppedFrames; (void)p_IAMMediaContent; (void)p_IAMMediaContentEx; (void)p_IAMPlayList; (void)p_IAMPlayListItem; (void)p_IAMStreamConfig; (void)p_IAMStreamControl; (void)p_IAMStreamSelect; (void)p_IAMTVTuner; (void)p_IAMTuner; (void)p_IAMovieSetup; (void)p_IAsyncReader; (void)p_IBasicAudio; (void)p_IBasicVideo; (void)p_IDMOWrapperFilter; (void)p_IDVREngineHelpers; (void)p_IDirectDrawVideo; (void)p_IDistributorNotify; (void)p_IEnumFilters; (void)p_IEnumMediaTypes; (void)p_IEnumPins; (void)p_IEnumRegFilters; (void)p_IFileSourceFilter; (void)p_IFilterGraph2; (void)p_IFilterMapper; (void)p_IGraphBuilder; (void)p_IGraphVersion; (void)p_IKsPropertySet; (void)p_IMediaControl; (void)p_IMediaEvent; (void)p_IMediaEventEx; (void)p_IMediaEventSink; (void)p_IMediaFilter; (void)p_IMediaPosition; (void)p_IMediaSample; (void)p_IMediaSample2; (void)p_IMediaSeeking; (void)p_IMediaStream; (void)p_IMemAllocator; (void)p_IMemInputPin; (void)p_IMultiMediaStream; (void)p_INonDelegatingUnknown; (void)p_IOverlay; (void)p_IOverlayNotify; (void)p_IPin; (void)p_IQualProp; (void)p_IQualityControl; (void)p_IReferenceClock; (void)p_ISeekingPassThru; (void)p_IStreamBufferCapture; (void)p_IStreamBufferPlayback; (void)p_IStreamSample; (void)p_IVPBaseConfig; (void)p_IVPBaseNotify; (void)p_IVPConfig; (void)p_IVPNotify; (void)p_IVideoWindow;
    return 0;
}

/* M71c: DMO values (printed tables/enums). */
_Static_assert(DMO_E_INVALIDSTREAMINDEX == 0x80040201L, "aa451595 table");
_Static_assert(DMO_E_NO_MORE_ITEMS == 0x80040206L, "aa451595 table");
#if __SIZEOF_POINTER__ == 4
_Static_assert(sizeof(DMO_MEDIA_TYPE) == 72, "aa451601 print");
_Static_assert(sizeof(DMO_OUTPUT_DATA_BUFFER) == 24, "aa451602 print");
_Static_assert(sizeof(DMO_PARTIAL_MEDIATYPE) == 32, "aa451605 print (GUID + GUID)");
#endif
_Static_assert(DMO_ENUMF_INCLUDE_KEYED == 0x00000001, "DMO_ENUM_FLAGS");
_Static_assert(DMO_INPUT_STREAMF_HOLDS_BUFFERS == 0x00000008, "DMO_INPUT_STREAM_INFO_FLAGS");
_Static_assert(DMO_OUTPUT_DATA_BUFFERF_INCOMPLETE == 0x01000000, "DMO_OUTPUT_DATA_BUFFER_FLAGS");
_Static_assert(DMO_OUTPUT_STREAMF_OPTIONAL == 0x00000010, "DMO_OUTPUT_STREAM_INFO_FLAGS");
_Static_assert(DMO_REGISTERF_IS_KEYED == 0x00000001, "DMO_REGISTER_FLAGS");
_Static_assert(DMO_SET_TYPEF_CLEAR == 0x00000002, "DMO_SET_TYPE_FLAGS");
_Static_assert(DMO_VOSF_NEEDS_PREVIOUS_SAMPLE == 0x00000001, "DMO_VIDEO_OUTPUT_STREAM_FLAGS");

/* M71c: DMO shaped usage (Msdmo.lib import surface + records). */
static int m71c_shaped_usage(void)
{
    DMO_MEDIA_TYPE         mt;
    DMO_OUTPUT_DATA_BUFFER ob;
    DMO_PARTIAL_MEDIATYPE  pmt;
    GUID                   guid = { 0 };
    CLSID                  clsid = { 0 };
    IEnumDMO               *pe = (IEnumDMO *)0;
    IMediaBuffer           *mb = (IMediaBuffer *)0;
    IMediaObject           *mo = (IMediaObject *)0;
    IMediaObjectInPlace    *mip = (IMediaObjectInPlace *)0;
    IDMOQualityControl     *qc = (IDMOQualityControl *)0;
    IDMOVideoOutputOptimizations *vo = (IDMOVideoOutputOptimizations *)0;
    HRESULT                hr;

    memset(&mt, 0, sizeof(mt));
    mt.majortype = mt.subtype = mt.formattype = guid;
    mt.bFixedSizeSamples = 1; mt.lSampleSize = 0; mt.cbFormat = 0;
    mt.pUnk = (IUnknown *)0; mt.pbFormat = (BYTE *)0;
    ob.pBuffer = mb; ob.dwStatus = DMO_OUTPUT_DATA_BUFFERF_SYNCPOINT;
    ob.rtTimestamp = 0; ob.rtTimelength = 1;
    pmt.type = guid; pmt.subtype = guid;

    hr = DMOEnum(&guid, DMO_ENUMF_INCLUDE_KEYED, 0, &pmt, 0, &pmt, &pe);
    hr = DMOGetTypes(&clsid, 0, (unsigned long *)0, (DMO_PARTIAL_MEDIATYPE *)0,
                     0, (unsigned long *)0, (DMO_PARTIAL_MEDIATYPE *)0);
    hr = DMOGetName(&clsid, (WCHAR *)0);
    hr = DMOUnregister(&clsid, &guid);
    hr = DMOUnregisterFilter(&clsid);
    hr = DMORegisterFilter((LPCWSTR)0, &clsid, &guid, &clsid,
                           DMO_REGISTERF_IS_KEYED, 0, &pmt, 0, &pmt);
    hr = DMORegister((LPCWSTR)0, &clsid, &guid, &clsid, 0, 0, &pmt, 0, &pmt);
    hr = MoInitMediaType(&mt, 0);
    hr = MoFreeMediaType(&mt);
    hr = MoCopyMediaType(&mt, (const DMO_MEDIA_TYPE *)0);
    {
        DMO_MEDIA_TYPE *pmtOut = (DMO_MEDIA_TYPE *)0;
        hr = MoCreateMediaType(&pmtOut, 0);
        hr = MoDeleteMediaType(&mt);
        hr = MoDuplicateMediaType(&pmtOut, (const DMO_MEDIA_TYPE *)0);
        (void)pmtOut;
    }
    (void)ob; (void)mo; (void)mip; (void)qc; (void)vo; (void)hr; (void)pe;
    return 0;
}

/* M73a: automation completion (Oleauto.h/Oaidl.h alias surface). */
static int m73a_shaped_usage(void)
{
    PROPVARIANT *pv = (PROPVARIANT *)0;
    DATE         d = 0.0;
    long         l = 0;
    HRESULT      hr;

    hr = VarI4FromDate(d, &l);
    hr = PropVariantClear(pv);
    hr = PropVariantCopy(pv, (const PROPVARIANT *)0);
    hr = FreePropVariantArray(0u, pv);
    (void)hr;
    return (int)l;
}

static int m73b_shaped_usage(void)
{
    OLEVERB        verb;
    STATDATA       sd;
    OLEGETMONIKER  gm   = OLEGETMONIKER_ONLYIFTHERE;
    OLEUPDATE      ou   = OLEUPDATE_ONCALL;
    OLEWHICHMK     wm   = OLEWHICHMK_OBJFULL;
    OLELINKBIND    lb   = OLELINKBIND_EVENIFCLASSDIFF;
    STOREINFO      si;
    LPOLEOBJECT    po  = (LPOLEOBJECT)0;
    GUID           g1  = { 0 }, g2 = { 0 };
    LPSTREAM       pstm = (LPSTREAM)0;
    HRESULT        hr;

    si.cbStruct = sizeof(STOREINFO);
    verb.lVerb = 0; verb.grfAttribs = (DWORD)gm; verb.fuFlags = 0u;
    sd.Formatetc.dwAspect = (DWORD)gm; sd.dwConnection = (DWORD)ou;
    (void)verb; (void)sd; (void)wm; (void)lb; (void)po;
    hr = IsEqualGUID(&g1, &g2);
    hr = CreateStreamOnHGlobal((HGLOBAL)0, 0, &pstm);
    hr = OleRun((LPUNKNOWN)0);
    (void)OleIsRunning(po);
    (void)ReadClassStg((IStorage *)0, (CLSID *)0);
    (void)ReleaseStgMedium((STGMEDIUM *)0);
    (void)hr;
    return (int)si.cbStruct;
}

static int m74_shaped_usage(void)
{
    DWORD n = AMGetErrorText((HRESULT)0, (TCHAR *)0, 0u);
    return (int)n;
}

static int m75a_shaped_usage(void)
{
    MQQUEUEPROPS *qp = (MQQUEUEPROPS *)0;
    QUEUEHANDLE   qh  = (QUEUEHANDLE)0;
    HRESULT       hr;

    hr = MQOpenQueue((LPCWSTR)0, 0u, 0u, &qh);
    hr = MQCloseQueue(qh);
    hr = MQGetQueueProperties((LPCWSTR)0, qp);
    (void)MQFreeMemory((PVOID)0);
    (void)hr;
    return 0;
}

static int m75b_shaped_usage(void)
{
    UPNPDEVICEINFO di;
    UPNPPARAM       prm = { (PCWSTR)0, (PCWSTR)0 };
    UPNPCB_ID       cb  = UPNPCB_CONTROL;
    BOOL            ok;

    di.cbStruct = sizeof(UPNPDEVICEINFO);
    di.pfCallback = (PUPNPCALLBACK)0;
    ok = UpnpAddDevice(&di);
    ok = UpnpPublishDevice((PCWSTR)0);
    (void)UpnpSetControlResponse((UPNPSERVICECONTROL *)0, 0u, &prm);
    (void)cb;
    return (int)ok;
}

static int m75c_shaped_usage(void)
{
    OBEX_REQUEST     req;
    OBEX_EVENT       ev  = OE_DEVICE_ARRIVAL;
    INBOX_EVENT_DATA ied;
    ServerCallback   scb = (ServerCallback)0;

    req.pHeaderCol = (IHeaderCollection *)0;
    ied.pStream = req.pStream;
    (void)ev; (void)scb;
    return (int)ied.dwRequest + (req.dwFlags != 0u);
}

static int m75d_shaped_usage(void)
{
    HPEERENUM      he  = (HPEERENUM)0;
    PEER_ADDRESS   pa;
    PEER_DATA      pd;
    PEER_NAME_PAIR np;
    PWSTR          wz  = (PWSTR)0;
    HRESULT        hr;

    pa.dwSize = sizeof(PEER_ADDRESS);
    np.dwSize = sizeof(PEER_NAME_PAIR);
    pd.cbData = pa.dwSize + np.dwSize;
    hr = PeerCreatePeerName((PCWSTR)0, (PCWSTR)0, &wz);
    hr = PeerEndEnumeration(he);
    (void)PeerFreeData((PVOID)0);
    (void)hr;
    return (int)pd.cbData;
}

static int m75e_shaped_usage(void)
{
    ServiceEnumInfo sei;
    PPROXY_HTTP_INFORMATION pi = (PPROXY_HTTP_INFORMATION)0;
    HANDLE h;

    sei.dwServiceState = 0u;
    h = RegisterService((LPCWSTR)0, sei.dwServiceState, (LPCWSTR)0, 0u);
    (void)DeregisterService(h);
    (void)Add_Share((const WCHAR *)0, 0u, (const WCHAR *)0);
    (void)ProxySignalFilter(0u);
    return (int)pi->dwProxyVersion;
}

static int m75f_shaped_usage(void)
{
    HTTP_FILTER_CONTEXT      fc;
    HTTP_FILTER_PREPROC_HEADERS ph;
    HTTP_FILTER_SEND_RESPONSE sr;
    RASCNTL_SERVERSTATUS     st;
    RASCNTL_SERVER_IPV6_NET_PREFIX v6;
    HSE_SEND_HEADER_EX_INFO  hi = { (LPCSTR)0, (LPCSTR)0, 0u, 0u, 0 };
    enum SF_REQ_TYPE         rq = SF_REQ_SEND_RESPONSE_HEADER;

    fc.cbSize = sizeof(HTTP_FILTER_CONTEXT);
    ph.dwReserved = 0u;
    sr.HttpStatus = (DWORD)rq;
    st.dwNumLines = 0u;
    v6.IPV6NetPrefixBitLength = 0u;
    return (int)hi.cchStatus + fc.cbSize + (ph.HttpStatus != 0u)
           + (sr.dwReserved != 0u) + st.dwNumLines
           + (v6.IPV6NetPrefixCount != 0u);
}

static int m77a_shaped_usage(void)
{
    MIB_TCPSTATS      ts;
    MIB_TCPROW        tr;
    MIB_IPFORWARDROW  fr;
    IP_ADDR_STRING    as;
    IP_PER_ADAPTER_INFO pai;
    IP_ADAPTER_PREFIX ap;
    DWORD             d;

    ts.dwNumConns = 0u;
    tr.dwState = 0u;
    fr.dwForwardMetric1 = 0u;
    as.Context = 0u;
    pai.AutoconfigEnabled = 0u;
    ap.PrefixLength = 0u;
    d = GetTcpStatistics(&ts);
    d = GetTcpStatisticsEx(&ts, 0u);
    d = SetTcpEntry(&tr);
    d = GetBestRoute(0u, 0u, &fr);
    d = GetPerAdapterInfo(0u, &pai, (PULONG)0);
    d = GetNumberOfInterfaces((PDWORD)0);
    d = NotifyAddrChange((PHANDLE)0, (LPOVERLAPPED)0);
    (void)d;
    return (int)ap.PrefixLength + ts.dwNumConns + (as.Context != 0u);
}

static int m77b_shaped_usage(void)
{
    NETRESOURCE           nr;
    CONNECTDLGSTRUCT      cs;
    DISCDLGSTRUCT         ds;
    DNS_RECORD_FLAGS      rf;
    IP_OPTION_INFORMATION io;
    DOMAIN_CONTROLLER_INFO dci;
    HANDLE                hh;
    DWORD                 d;

    nr.dwType = 0u; cs.cbStructure = sizeof(CONNECTDLGSTRUCT);
    ds.cbStructure = 0u; rf.Section = 0; io.Ttl = 128;
    dci.Flags = 0u;
    d = WNetOpenEnum(0u, 0u, 0u, &nr, &hh);
    d = WNetCloseEnum(hh);
    d = DsGetDcName((LPCTSTR)0, (LPCTSTR)0, (GUID *)0,
                    (LPCTSTR)0, 0u, (PDOMAIN_CONTROLLER_INFO *)0);
    (void)d;
    return (int)io.Ttl + cs.cbStructure + (ds.dwFlags != 0u)
           + rf.Section + (dci.Flags != 0u);
}

static int m77c_shaped_usage(void)
{
    FW_IP_ADDRESS     fa;
    FW_ACTIONS        act = FWA_BLOCK;
    FW_RULE_MASKS     fm  = FWM_PORT;
    IPSEC_API_PARAM   ip;
    RAS_AUTH_ATTRIBUTE raa;
    PPP_EAP_PACKET    ep;
    MIB_BEST_IF       bi;
    DWORD             d;

    fa.Family = 0u; ip.id = 0u; raa.dwLength = 0u; ep.Code = 0u;
    bi.dwIfIndex = 0u;
    d = FirewallEnable(0u, 0, 0);
    d = IsIPSecRunning();
    d = SetIPSecConfig(ip, 0u);
    (void)d;
    return (int)act + fm + fa.Family + raa.dwLength + ep.Code
           + bi.dwIfIndex + (ip.valSize != 0u);
}

static int m78a_shaped_usage(void)
{
    NDIS_HANDLE           nh;
    NDIS_STATUS           ns;
    NDIS_OID              no;
    NDIS_PHYSICAL_ADDRESS npa;
    NDIS_WORK_ITEM        nwi;
    NDIS_PACKET_OOB_DATA  oob;
    NDIS_PACKET_STACK     pstk;
    TRANSPORT_HEADER_OFFSET tho;
    NDIS_MAC_LINE_DOWN    mld;
    NDIS_MAC_FRAGMENT     mfr;
    NDIS_WAN_LINE_DOWN    wld;
    NDIS_WAN_INFO         wi;
    NDIS_WAN_COMPRESS_INFO wci;
    NDIS_WAN_GET_LINK_INFO wgli;
    NDIS_WAN_SET_COMP_INFO wsci;
    NDIS_WAN_GET_STATS_INFO wgsi;
    NDIS_TASK_TCP_IP_CHECKSUM ttc;
    NDIS_TASK_TCP_LARGE_SEND tls;
    NDIS_TCP_IP_CHECKSUM_PACKET_INFO tpi;
    NDIS_CONFIGURATION_PARAMETER *pcp;
    NDIS_REQUEST          *preq;
    NDIS_PACKET           *ppkt;
    NDIS_PROTOCOL_CHARACTERISTICS *ppc;
    NDIS_MINIPORT_CHARACTERISTICS *pmc;
    NDIS_SPIN_LOCK        *psl;
    NDIS_RW_LOCK          *prwl;
    LOCK_STATE            *pls;
    NDIS_EVENT            *pev;
    NDIS_TIMER            *ptm;
    NDIS_MINIPORT_INTERRUPT *pmi;
    NDIS_MINIPORT_TIMER   *pmt;
    NDIS_INTERFACE_TYPE   ift = NdisInterfacePci;
    NDIS_INTERRUPT_MODE   im  = NdisInterruptLatched;
    NDIS_PARAMETER_TYPE   pt  = NdisParameterString;
    PVOID                 pv;
    UINT                  u;
    BOOLEAN               b;

    nh = NULL; no = 0u; npa.QuadPart = 0; nwi.Context = NULL;
    nwi.Routine = NULL; nwi.WrapperReserved = 0u;
    oob.TimeReceived = 0u; oob.Status = 0; pstk.IMReserved[0] = 0u;
    tho.HeaderOffset = 0u; mld.NdisLinkContext = NULL;
    mfr.Errors = 0u; wld.RemoteAddress[0] = 0u; wi.Endpoints = 0u;
    wci.CompType = 0u; wgli.SendACCM = 0u; wsci.RecvCapabilities.CompType = 0u;
    wgsi.BytesSent = 0u; ttc.V4Transmit.TcpChecksum = 0u;
    tls.MaxOffLoadSize = 0u; tpi.Value = 0u;
    pcp = NULL; preq = NULL; ppkt = NULL; ppc = NULL; pmc = NULL;
    psl = NULL; prwl = NULL; pls = NULL; pev = NULL; ptm = NULL;
    pmi = NULL; pmt = NULL; pv = NULL; u = 0u; b = 0;
    ns = NdisGetVersion();
    no = 0u; (void)no;
    ns = NdisReadPcmciaAttributeMemory(nh, u, pv, u);
    NdisCancelTimer(ptm, &b);
    NdisInitializeEvent(pev);
    NdisAcquireReadWriteLock(prwl, b, pls);
    NdisMInitializeTimer(pmt, nh, NULL, pv);
    ns = NdisMMapIoSpace(&pv, nh, npa, u);
    ns = NdisEqualMemory(pv, pv, u);
    u = NdisGetCacheFillSize();
    NdisTerminateWrapper(nh, pv);
    return (int)ift + (int)im + (int)pt + ns + (int)b
           + (pcp || preq || ppkt || ppc || pmc || psl || prwl
              || pls || pev || ptm || pmi || pmt ? 1 : 0)
           + (int)oob.Status + (int)wci.CompType + (int)tho.HeaderOffset
           + (mld.NdisLinkContext != NULL) + (int)mfr.Errors
           + (int)wld.RemoteAddress[0] + (int)wi.Endpoints
           + (int)wgli.SendACCM + (int)wsci.RecvCapabilities.CompType + (int)wgsi.BytesSent
           + (int)ttc.V4Transmit.TcpChecksum + (int)tls.MaxOffLoadSize
           + (int)tpi.Value + (int)pstk.IMReserved[0]
           + (int)npa.QuadPart + (int)nwi.WrapperReserved;
}

static int m78b_shaped_usage(void)
{
    NDIS_802_11_SSID              ssid;
    NDIS_802_11_MAC_ADDRESS       mac;
    NDIS_802_11_RATES             rates;
    NDIS_802_11_CONFIGURATION     cfg;
    NDIS_802_11_CONFIGURATION_FH  fh;
    NDIS_802_11_WEP               wep;
    NDIS_802_11_STATISTICS        st;
    NDIS_WLAN_BSSID               wb;
    NDIS_802_11_BSSID_LIST       *pbl;
    NDIS_PM_PACKET_PATTERN        pp;
    VAR_STRING                    vs;
    NDIS_TAPI_CONFIG_DIALOG       cd;
    NDIS_TAPI_NEGOTIATE_EXT_VERSION nev;
    NDIS_TAPI_PROVIDER_INITIALIZE pi;
    NDIS_TAPI_PROVIDER_SHUTDOWN   psh;
    NDIS_TAPI_SET_DEV_CONFIG      sdc;
    NDIS_TAPI_GET_DEV_CAPS       *gdc;
    NDIS_TAPI_EVENT              *tev;
    NDIS_MEDIUM                   med = NdisMedium802_3;
    NDIS_802_11_WEP_STATUS        ws  = Ndis802_11WEPEnabled;
    NDIS_802_11_AUTHENTICATION_MODE am = Ndis802_11AuthModeOpen;
    NDIS_802_11_NETWORK_TYPE      nt  = Ndis802_11FH;
    NDIS_WAN_MEDIUM_SUBTYPE       wms = NdisWanMediumSerial;
    NDIS_802_5_RING_STATE         rs  = NdisRingStateOpened;
    ULONG                         ul;

    ssid.SsidLength = 0u; mac[0] = 0u; rates[0] = 0u;
    fh.DwellTime = 0u; cfg.BeaconPeriod = 0u; cfg.FHConfig = fh;
    wep.KeyLength = 0u; st.FailedCount.QuadPart = 0;
    wb.Length = 0u; wb.Configuration = cfg; wb.Ssid = ssid;
    pp.MaskSize = 0u; vs.ulTotalSize = 0u;
    cd.ulDeviceID = 0u; nev.ulExtVersion = 0u; pi.ulProviderID = 0u;
    psh.ulRequestID = 0u; sdc.ulDeviceID = 0u;
    pbl = NULL; gdc = NULL; tev = NULL; ul = 0u;
    (void)pbl; (void)gdc; (void)tev; (void)ul;
    return (int)med + (int)ws + (int)am + (int)nt + (int)wms
           + (int)rs + (int)fh.DwellTime + (int)cfg.BeaconPeriod
           + (int)wep.KeyLength + (int)st.FailedCount.QuadPart
           + (int)wb.Length + (int)pp.MaskSize + (int)vs.ulTotalSize
           + (int)cd.ulDeviceID + (int)nev.ulExtVersion
           + (int)pi.ulProviderID + (int)psh.ulRequestID
           + (int)sdc.ulDeviceID + (int)mac[0] + (int)rates[0];
}

static int m78c_shaped_usage(void)
{
    RNDIS_CLASS_ID             rcid = 0;
    RNDIS_MEDIUM              rmed = 0;
    RNDIS_OID                  roid = 0;
    RNDIS_REQUEST_ID           rrid = 0;
    RNDIS_STATUS               rsts = 0;
    RNDIS_DIAGNOSTIC_INFO      rdi;
    RNDIS_OOBD                 roo;
    RNDIS_PER_PACKET_INFO      rppi;
    REMOTE_NDIS_HALT_MSG       rhm;
    REMOTE_NDIS_INITIALIZE_MSG rim;
    REMOTE_NDIS_KEEPALIVE_CMPLT rkc;
    REMOTE_NDIS_QUERY_CMPLT    rqc;
    REMOTE_NDIS_RESET_CMPLT    rrc;
    REMOTE_NDIS_SET_CMPLT      rsc;
    RNDIS_PACKET              *prp;
    REMOTE_NDIS_QUERY_MSG     *prq;
    DATA_WRAPPER              *pdw;
    RNDIS_PDD_CHARACTERISTICS *prpc;
    PFN_PDD_GET                pget = NULL;
    INTF_KEY_ENTRY             ike;
    INTFS_KEY_TABLE            ikt;
    WZC_CONTEXT                wctx;
    WZC_EAPOL_PARAMS           wep;
    INTF_ENTRY                *pie;
    WZC_WLAN_CONFIG           *pwwc;
    WZC_802_11_CONFIG_LIST    *pwcl;
    NDISUIO_DEVICE_NOTIFICATION ndn;
    NDISUIO_QUERY_BINDING      nqb;
    NDISUIO_QUERY_OID          nqo;
    NDISUIO_SET_OID           *pnso;
    NDISUIO_REQUEST_NOTIFICATION nrn;
    NIC_STATISTICS             nst;
    DWORD                      dwd;

    rdi.ErrorOffset = 0u; roo.Size = 0u; rppi.Type = 0u;
    rhm.RequestId = 0u; rim.MaxTransferSize = 0u; rkc.Status = 0u;
    rqc.InformationBufferOffset = 0u; rrc.AddressingReset = 0u;
    rsc.RequestId = 0u;
    prp = NULL; prq = NULL; pdw = NULL; prpc = NULL; pget = NULL;
    ike.wszGuid = NULL; ikt.dwNumIntfs = 0u; wctx.dwFlags = 0u;
    wep.dwEapType = 0u; pie = NULL; pwwc = NULL; pwcl = NULL;
    ndn.dwNotificationType = 0u; nqb.BindingIndex = 0u;
    nqo.Oid = 0u; pnso = NULL; nrn.hMsgQueue = NULL;
    nst.LinkSpeed = 0u; dwd = 0u;
    dwd = WZCEnumInterfaces(NULL, &ikt);
    dwd += WZCQueryContext(NULL, 0u, &wctx, NULL);
    WZCDeleteIntfObj(pie);
    pdw = MDDAllocDataWrapper();
    MDDFreeMem(NULL);
    dwd += (DWORD)PDDInit(prpc, NULL);
    return (int)rcid + (int)rmed + (int)roid + (int)rrid + (int)rsts
           + (int)rdi.ErrorOffset + (int)roo.Size + (int)rppi.Type
           + (int)rhm.RequestId + (int)rim.MaxTransferSize
           + (int)rkc.Status + (int)rqc.InformationBufferOffset
           + (int)rrc.AddressingReset + (int)rsc.RequestId
           + (ike.wszGuid != NULL) + (int)ikt.dwNumIntfs + (int)wctx.dwFlags
           + (int)wep.dwEapType + (int)ndn.dwNotificationType
           + (int)nqb.BindingIndex + (int)nqo.Oid + (int)nst.LinkSpeed
           + (nrn.hMsgQueue != NULL)
           + (int)dwd + (prp || prq || pie || pwwc || pwcl || pnso ? 1 : 0)
           + (pdw != NULL) + (pget != NULL);
}

static int m79_shaped_usage(void)
{
    FILELOCKSTATE           fls;
    FSD_SCATTER_GATHER_RESULTS fsgr;
    PFSGI                   pfsgi = NULL;
    PVOLUME                 pvol = NULL;
    PFILE                   pfile = NULL;
    PSEARCH                 psearch = NULL;
    PARTINFO               *ppi = NULL;
    PSTOREMGR_STOREINFO     psi = NULL;
    CE_VOLUME_INFO          *pcvi = NULL;
    STORAGEDEVICEINFO       *psdi = NULL;
    STORAGECONTEXT          *psc = NULL;
    PD_PARTINFO            *ppdpi = NULL;
    PD_STOREINFO           *ppdsi = NULL;
    FILTERHOOK             *pfh = NULL;
    FSD_VOLUME_INFO        *pfvi = NULL;
    FILECHANGEINFO           fci;
    SHELLFILECHANGEFUNC_t    sfcf = NULL;
    PACQUIREFILELOCKSTATE    pafls = NULL;
    DWORD                   d;

    fls.dwPosLow = 0u; fls.fTerminal = 0; fls.pvLockContainer = NULL;
    fsgr.cSectorsTransferred = 0u; fci.cbSize = 0u; fci.nFileSize = 0u;
    d = FSDMGR_ReadDiskEx(pfsgi, &fsgr);
    d += FSDMGR_WriteDiskEx(pfsgi, &fsgr);
    d += FSD_UnhookVolume(pvol);
    FSDMGR_OpenFileLockState(&fls);
    FSDMGR_CloseFileLockState(&fls);
    d += FindFirstStore(psi) != NULL;
    d += FindNextPartition(NULL, ppi) != 0;
    d += GetStoreInfo(NULL, psi) != 0;
    d += OpenStore((LPCSTR)NULL) != NULL;
    d += FormatStore(NULL) != 0;
    return (int)d + (pfile || psearch || pcvi || psdi || psc || ppdpi
                     || ppdsi || pfh || pfvi ? 1 : 0)
           + (sfcf != NULL) + (pafls != NULL)
           + (int)fls.dwPosLow + (int)fsgr.cSectorsTransferred
           + (int)fci.cbSize + (int)fci.nFileSize;
}

static int m80_shaped_usage(void)
{
    DWORD d;
    HRESULT hr;
    WCHAR wbuf[8] = {0};
    INT  ci;
    LONG l;

    d = AttemptConnection();
    hr = GetPCSyncName(wbuf, 8);
    hr = SetPCSyncName(wbuf);
    l = VOIPLAP_E_NOSERVER;
    l += VOIPLAP_S_PCLOCKED;
    l += VOIP_E_ENUMOUTOFDATE;
    l += VOIP_S_DONT_TERMINATE;
    ci = 0;
    return (int)d + (hr != 0) + (int)l + ci + wbuf[0];
}

static int m82_shaped_usage(void)
{
    MINIDUMP_STREAM_TYPE mst = ceStreamSystemInfo;
    MINIDUMP_HEADER     *pmh = NULL;
    MINIDUMP_DIRECTORY  *pmd = NULL;
    CEDUMP_EXCEPTION    *pce = NULL;
    MINIDUMP_STRING     *pms = NULL;
    GUID                 g1  = {0};
    UINT                 u;
    DWORD                d;
    BOOL                 b;

    mst = ceStreamException;
    pmh = NULL; pmd = NULL; pce = NULL; pms = NULL; u = 0u; d = 0u;
    b = CaptureDumpFileOnDevice(0u, 0u, NULL);
    b = SideShowMgr_Start(NULL, 1u, &g1);
    b = SideShowMgr_Stop();
    b = SideShowMgr_IsServiceRunning();
    d = SideShowMgr_GetCurrentCacheSize();
    b = SideShowMgr_SetMaximumCacheSize(d);
    u = SideShowMgr_GetGadgetCount();
    return (int)mst + (int)u + b + (pmh || pmd || pce || pms ? 1 : 0);
}

static int m83_shaped_usage(void)
{
    GOFFSET                 goff;
    SCRIPT_ANALYSIS         sa;
    SCRIPT_CONTROL          sc;
    SCRIPT_STATE            ss;
    SCRIPT_DIGITSUBSTITUTE  sds;
    SCRIPT_FONTPROPERTIES  sfp;
    SCRIPT_ITEM             si;
    SCRIPT_LOGATTR          sla;
    SCRIPT_PROPERTIES      *psp = NULL;
    SCRIPT_TABDEF           std_;
    SCRIPT_VISATTR          sva;
    SCRIPT_JUSTIFY          sj = SCRIPT_JUSTIFY_ARABIC_KASHIDA;
    SCRIPT_CACHE            scache = NULL;
    SCRIPT_STRING_ANALYSIS  ssa = NULL;
    HWXGUIDE                hg;
    HWXRESULTS              hr_;
    LANGID                  lg;
    ABC                     abc;
    UINT                    u;
    DWORD                   dwd;
    BOOL                    b;

    goff.du = 0; sa.eScript = 0; sc.uDefaultLanguage = 0;
    ss.uBidiLevel = 0; sds.DigitSubstitute = 0; sfp.cBytes = 0;
    si.iCharPos = 0; sla.fCharStop = 0; std_.cTabStops = 0;
    sva.fClusterStart = 0; hg.cHorzBox = 0; hr_.indxBox = 0;
    u = 0u; dwd = 0u; b = 0; abc.abcB = 0;
    b = ScriptFreeCache(&scache);
    b = HwxConfig();
    b = GetPinyinType(&dwd);
    b = SetPinyinType(dwd);
    b = EnableEUDC(b);
    b = GetCharABCWidthsI(NULL, 0u, 0u, NULL, &abc);
    lg = GetSystemDefaultUILanguage();
    lg = GetUserDefaultUILanguage();
    b = SetUserDefaultUILanguage(lg);
    b = EnumUILanguages(NULL, 0u);
    return (int)sj + (int)goff.du + (int)sa.eScript + (int)ss.uBidiLevel
           + (int)sfp.cBytes + (int)si.iCharPos + (int)sla.fCharStop
           + (int)std_.cTabStops + (int)sva.fClusterStart
           + (int)hg.cHorzBox + (int)hr_.indxBox + (int)lg + b
           + (psp != NULL) + (scache != NULL) + (ssa != NULL)
           + (int)sc.uDefaultLanguage + (int)sds.DigitSubstitute
           + (int)abc.abcB + (int)u;
}

static int m84_shaped_usage(void)
{
    IMESHF        shf;
    POSTBL        ptbl;
    IPCANDIDATE   ipc;
    MARGINS       marg;
    IFEDictionary *pifed = NULL;
    HRESULT       hr;

    shf.cbShf = 0; ptbl.nPos = 0; ipc.dwSize = 0;
    marg.cxLeftWidth = 0;
    hr = CreateIFEDictionaryInstance((VOID **)&pifed);
    hr = CreateIImeIPointInstance(NULL, (VOID **)&pifed);
    ImeGetUIClassName(NULL);
    return (int)shf.cbShf + (int)ptbl.nPos + (int)ipc.dwSize
           + marg.cxLeftWidth + (int)hr + (pifed != NULL);
}

static int m85_alias_usage(void)
{
    /* Cesync.h alias resolves to the Objbase.h STOREINFO (COM) M73b
     * definition; Dinput/Bthid/bt_ddi/Dmoimpl are record-only. */
    STOREINFO   csi;

    csi.cbStruct = 0;
    return (int)csi.cbStruct;
}

static int m87_shaped_usage(void)
{
    DVD_AUDIO_MU_ATTR   ama;
    DVD_CELL_PIECE      ccp;
    DVD_CELL_PLAYBACK   cbp;
    DVD_ISRC            isrc;
    DVD_NAV_CMD         ncmd;
    DVD_POS_CODE        pcode;
    DVD_PROVIDER_ID      pid;
    DVD_SUBPICTURE_STREAM_ATTR ssa;
    DVD_TEXT_ITEM       ti;
    DVD_TITLE_SET_INFO  tsi;
    DVDUserGOPData      gop;
    DVD_RECT            dr;
    EDDVDPlaybackState  pbs;
    EDVDDomainType      dom;
    ENavCmdArea         nca;
    EPGCPlaybackMode    pbm;
    IDVDUserOperation  *puo = NULL;
    UNICODE_PATH        upath;
    WCHAR               w;

    ama.atr1[0] = 0; ccp.vob_id = 0; cbp.cellCategory = 0;
    isrc.valid = 0; ncmd.cmd[0] = 0; pcode.posCode[0] = 0;
    pid.providerID[0] = 0; ssa.modetype = 0; ti.itemCode = 0;
    tsi.nParts = 0; gop.userData[0] = 0; dr.xStart = 0;
    pbs = DVD_PAUSED; dom = DVD_TT_DOM; nca = DVD_CELL_CMD;
    pbm = DVD_PLAYMODE_SHUFFLE;
    upath[0] = 0; w = 0;
    return (int)ama.atr1[0] + (int)ccp.vob_id + (int)cbp.cellCategory
           + (int)isrc.valid + (int)ncmd.cmd[0] + (int)pcode.posCode[0]
           + (int)pid.providerID[0] + (int)ssa.modetype + (int)ti.itemCode
           + (int)tsi.nParts + (int)gop.userData[0] + (int)dr.xStart
           + (int)pbs + (int)dom + (int)nca + (int)pbm
           + (puo != NULL) + (int)upath[0] + (int)w
           + SPRM_REGION + DVD_SCANCAP_BACKWARD_SINGLE
           + (int)sizeof(UNICODE_PATH);
}

static int m88_shaped_usage(void)
{
    VIDEOINFOHEADER  vih;
    BITMAPINFOHEADER bmih;
    AM_MEDIA_TYPE     amt;
    GUID              guid = {0};
    RGBQUAD           rgb;
    BSTR              bstr = NULL;
    IStream          *pstm = NULL;
    IUnknown         *punk = NULL;
    TCHAR             tc[4];
    WCHAR             wbuf[16];
    LONG              l;
    WORD              w;
    DWORD             dw;
    int               i;

    vih.bmiHeader.biSize = 0; bmih.biSize = 0;
    amt.majortype = guid; rgb.rgbBlue = 0;
    l = GetBitmapFormatSize(&bmih);
    w = GetBitCount(&guid);
    dw = GetBitmapSize(&bmih);
    guid = GetBitmapSubtype(&bmih);
    guid = GetTrueColorType(&bmih);
    wbuf[0] = 0; i = WstrToInt(wbuf);
    tc[0] = 0; wbuf[0] = 0;
    l = ContainsPalette(&vih); dw = (DWORD)l;
    i = (int)WaitDispatchingMessages(NULL, 0u, NULL, 0u);
    i = (int)IsEqualObject(punk, punk);
    dw = (DWORD)llMulDiv(1, 2, 3, 4);
    i = (int)Int64x32Div32(1, 2, 3, 4);
    return (int)bmih.biSize + (int)w + (int)dw + i + (bstr != NULL)
           + (pstm != NULL) + (punk != NULL) + tc[0] + wbuf[0]
           + (int)rgb.rgbBlue + (int)sizeof(amt);
}

static int m89_shaped_usage(void)
{
    MONITORINFOEX miex;

    miex.cbSize = 0; miex.rcMonitor.left = 0; miex.dwFlags = 0;
    miex.szDevice[0] = 0;
    return (int)miex.cbSize + (int)miex.dwFlags + (int)miex.szDevice[0];
}

static int m91_fsd_usage(void)
{
    FILELOCKSTATE fls;

    fls.cQueue = 0;
    return (int)fls.cQueue
           + (FSDMGR_EmptyLockContainer(&fls) ? 1 : 0)
           + (FSDMGR_OpenFileLockState(&fls), 0)
           + (FSDMGR_CloseFileLockState(&fls), 0);
}

static int m92_wininet_usage(void)
{
    HTTP_VERSION_INFO         hvi;
    INTERNET_BUFFERS          ib;
    INTERNET_CACHE_ENTRY_INFO icei;
    INTERNET_CACHE_TIMESTAMPS icts;
    INTERNET_CERTIFICATE_INFO cert;
    INTERNET_CONNECTED_INFO   ici;
    INTERNET_PER_CONN_OPTION  ipco;
    INTERNET_PER_CONN_OPTION_LIST ipcol;
    INTERNET_PROXY_INFO       ipi;
    INTERNET_VERSION_INFO     ivi;
    INTERNET_SCHEME           sch;
    InternetCookieState       ics;
    FILETIME                  ft;
    DWORD                     dw;

    hvi.dwMajorVersion = 0; ib.dwStructSize = 0; icei.dwStructSize = 0;
    icts.ftExpires.dwLowDateTime = 0; cert.dwKeySize = 0;
    ici.dwConnectedState = 0; ipco.dwOption = 0; ipcol.dwSize = 0;
    ipi.dwAccessType = 0; ivi.dwMinorVersion = 0;
    sch = INTERNET_SCHEME_HTTPS; ics = COOKIE_STATE_ACCEPT;
    ft.dwLowDateTime = 0;
    dw = 0;
    dw = InternetAttemptConnect(0u);
    dw += (DWORD)InternetCheckConnection(NULL, 0u, 0u);
    dw += (DWORD)InternetGetCookie(NULL, NULL, NULL, &dw);
    dw += (DWORD)InternetGetLastResponseInfo(&dw, NULL, NULL);
    dw += (DWORD)InternetGoOnline(NULL, NULL, 0u);
    dw += (DWORD)InternetTimeToSystemTime(NULL, NULL, 0u);
    dw += (DWORD)InternetUnlockRequestFile(NULL);
    dw += InternetConfirmZoneCrossing(NULL, NULL, NULL, FALSE);
    dw += (DWORD)DeleteUrlCacheEntry(NULL);
    dw += (DWORD)FindCloseUrlCache(NULL);
    dw += (DWORD)UnlockUrlCacheEntryFile(NULL, 0u);
    dw += IsMessageBoxHandled(NULL, 0u, 0u, 0u);
    dw += IsDialogBoxHandled(NULL, 0u, 0u, NULL);
    return (int)dw + (int)hvi.dwMajorVersion + (int)ib.dwStructSize
           + (int)icei.dwStructSize + (int)icts.ftExpires.dwLowDateTime
           + (int)cert.dwKeySize + (int)ici.dwConnectedState
           + (int)ipco.dwOption + (int)ipcol.dwSize + (int)ipi.dwAccessType
           + (int)ivi.dwMinorVersion + (int)sch
           + HTTP_STATUS_VERSION_NOT_SUP + HTTP_QUERY_SET_COOKIE
           + (int)ft.dwLowDateTime + (int)ics;
}

int host_tu_entry(void)
{
    (void) api_symbols;
    (void) api_flags;
    (void) tu_progress_assign;
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
    if (m39_shaped_usage() != 0)
        return 1;
    if (m41_shaped_usage() != 0)
        return 1;
    if (m42_shaped_usage() != 0)
        return 1;
    if (m43_shaped_usage() != 0)
        return 1;
    if (m44_shaped_usage() != 0)
        return 1;
    if (m45_shaped_usage() != 0)
        return 1;
    if (m46_shaped_usage() != 0)
        return 1;
    if (m47_shaped_usage() != 0)
        return 1;
    if (m48_shaped_usage() != 0)
        return 1;
    if (m49_shaped_usage() != 0)
        return 1;
    if (m50_shaped_usage() != 0)
        return 1;
    if (m51_shaped_usage() != 0)
        return 1;
    if (m52_shaped_usage() != 0)
        return 1;
    if (m53_shaped_usage() != 0)
        return 1;
    if (m54_shaped_usage() != 0)
        return 1;
    if (m55_shaped_usage() != 0)
        return 1;
    if (m56_shaped_usage() != 0)
        return 1;
    if (m57_shaped_usage() != 0)
        return 1;
    if (m58_shaped_usage() != 0)
        return 1;
    if (m59_shaped_usage() != 0)
        return 1;
    if (m60_shaped_usage() != 0)
        return 1;
    if (m61_shaped_usage() != 0)
        return 1;
    if (m63_shaped_usage() != 0)
        return 1;
    if (m64_shaped_usage() != 0)
        return 1;
    if (m65_shaped_usage() != 0)
        return 1;
    if (m66_shaped_usage() != 0)
        return 1;
    if (m67_shaped_usage() != 0)
        return 1;
    if (m68_shaped_usage() != 0)
        return 1;
    if (m69_shaped_usage() != 0)
        return 1;
    if (m70_shaped_usage() != 0)
        return 1;
    if (m70b_shaped_usage() != 0)
        return 1;
    if (m71_shaped_usage() != 0)
        return 1;
    if (m71c_shaped_usage() != 0)
        return 1;
    if (m73a_shaped_usage() != 0)
        return 1;
    if (m73b_shaped_usage() != 0)
        return 1;
    if (m74_shaped_usage() != 0)
        return 1;
    if (m75a_shaped_usage() != 0)
        return 1;
    if (m75b_shaped_usage() != 0)
        return 1;
    if (m75c_shaped_usage() != 0)
        return 1;
    if (m75d_shaped_usage() != 0)
        return 1;
    if (m75e_shaped_usage() != 0)
        return 1;
    if (m75f_shaped_usage() != 0)
        return 1;
    if (m77a_shaped_usage() != 0)
        return 1;
    if (m77b_shaped_usage() != 0)
        return 1;
    if (m77c_shaped_usage() != 0)
        return 1;
    if (m78a_shaped_usage() != 0)
        return 1;
    if (m78b_shaped_usage() != 0)
        return 1;
    if (m78c_shaped_usage() != 0)
        return 1;
    if (m79_shaped_usage() != 0)
        return 1;
    if (m80_shaped_usage() != 0)
        return 1;
    if (m82_shaped_usage() != 0)
        return 1;
    if (m83_shaped_usage() != 0)
        return 1;
    if (m84_shaped_usage() != 0)
        return 1;
    if (m85_alias_usage() != 0)
        return 1;
    if (m87_shaped_usage() != 0)
        return 1;
    if (m88_shaped_usage() != 0)
        return 1;
    if (m89_shaped_usage() != 0)
        return 1;
    if (m91_fsd_usage() != 0)
        return 1;
    if (m92_wininet_usage() != 0)
        return 1;
    return 0;
}
