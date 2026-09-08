/*
 * winuser.h -- window, message, keyboard and input API for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (CE-era MSDN pages in the learn.microsoft.com previous-versions
 * archive, (v=msdn.10) IDs; Header row Winuser.h for these items
 * unless a comment says otherwise).  The Windows Functions / Window
 * Class / Window Properties / Windows Timer / Carets / Atoms /
 * Message Queue / Message Synchronization / Keyboard / Scroll Bars
 * reference books of the CE 5.0 GWES documentation are the source
 * books.
 *
 * Link Library rows in this book vary: the GWES *message-queue* and
 * several keyboard functions print "Coredll.lib"; many window-manager
 * pages print *no* Link Library row at all (they are GWES services of
 * the OS image) -- def membership follows the published rows exactly
 * (see docs/inventory.md).  Other pages print component-module rows
 * (e.g. Accel.lib, Kbdui.lib, Wmgr_c.lib, Caret.lib, Sbcmn.lib,
 * Uibase.lib, Hotkey.lib, Msgque.lib, Coreimm.lib) that are recorded
 * as those documented modules.
 *
 * Functions whose pages take text parameters are Unicode-only on
 * Windows CE (W export + generic macro), following the repo rule that
 * a page showing a base name with no A/W spelling is the wide export
 * plus the base-name macro.  Functions whose pages show no text
 * parameter are declared under that documented base name directly (no
 * A/W pair exists on CE).
 *
 * Items whose official pages list Header: Windows.h or Winbase.h
 * (window properties, SendMessageTimeout, ScrollDC, MsgWaitForMultiple
 * Objects, KillTimer) live in windows.h / winbase.h respectively and
 * are noted there; the typedefs they need (PROPENUMPROCEX) live here.
 */

#ifndef AKARI_WINUSER_H
#define AKARI_WINUSER_H

#include "windef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Core message / class / callback types.  MSG is filled by           */
/* GetMessage/PeekMessage (aa453135/ms911928) and read by             */
/* DispatchMessage/TranslateMessage (aa452956/aa453776).  WNDCLASS is */
/* used by RegisterClass (ms913089) and GetClassInfo (ms929211).      */
/* The layouts are the fixed Win32 ABI forms the CE pages type        */
/* against; CE pages do not republish the member layouts.             */
/* ------------------------------------------------------------------ */

typedef struct tagMSG {
    HWND   hwnd;      /* window whose procedure receives the message */
    UINT   message;   /* message identifier */
    WPARAM wParam;    /* message parameter */
    LPARAM lParam;    /* message parameter */
    DWORD  time;      /* time the message was posted */
    POINT  pt;        /* cursor position when the message was posted */
} MSG, *PMSG, *LPMSG;

typedef LRESULT (CALLBACK *WNDPROC)(HWND hWnd, UINT Msg, WPARAM wParam,
                                    LPARAM lParam);
typedef BOOL (CALLBACK *WNDENUMPROC)(HWND hwnd, LPARAM lParam);
typedef BOOL (CALLBACK *PROPENUMPROCEX)(HWND hwnd, LPTSTR lpszString,
                                        HANDLE hData, ULONG_PTR dwData);
typedef VOID (CALLBACK *TIMERPROC)(HWND hwnd, UINT uMsg, UINT idEvent,
                                   DWORD dwTime);

typedef struct tagWNDCLASS {
    UINT      style;         /* class styles */
    WNDPROC   lpfnWndProc;   /* window procedure */
    int       cbClsExtra;    /* per-class extra bytes */
    int       cbWndExtra;    /* per-window extra bytes */
    HINSTANCE hInstance;     /* module that registered the class */
    HICON     hIcon;         /* class icon */
    HCURSOR   hCursor;       /* class cursor */
    HBRUSH    hbrBackground; /* background brush */
    LPCTSTR   lpszMenuName;  /* menu resource name */
    LPCTSTR   lpszClassName; /* class name */
} WNDCLASS, *LPWNDCLASS, *PWNDCLASS;

/* ------------------------------------------------------------------ */
/* Window-creation / window-manager structures.                       */
/* ------------------------------------------------------------------ */

/* ms908189 "CREATESTRUCT (Windows CE 5.0)": creation parameters passed
 * to a window procedure on WM_CREATE.  CE 1.0+. */
typedef struct tagCREATESTRUCT {
    LPVOID    lpCreateParams;  /* the lpParam of CreateWindow(Ex) */
    HINSTANCE hInstance;
    HMENU     hMenu;
    HWND      hwndParent;
    int       cy;
    int       cx;
    int       y;
    int       x;
    LONG      style;
    LPCTSTR   lpszName;
    LPCTSTR   lpszClass;
    DWORD     dwExStyle;
} CREATESTRUCT, *LPCREATESTRUCT;

/* ms940380 "STYLESTRUCT (Windows CE 5.0)": old/new window styles
 * (WM_STYLECHANGED). */
typedef struct tagSTYLESTRUCT {
    DWORD styleOld;
    DWORD styleNew;
} STYLESTRUCT, *LPSTYLESTRUCT;

/* ms914101 "WINDOWPOS (Windows CE 5.0)": position/size/flags passed
 * with WM_WINDOWPOSCHANGING / WM_WINDOWPOSCHANGED. */
typedef struct _WINDOWPOS {
    HWND hwnd;
    HWND hwndInsertAfter;
    int  x;
    int  y;
    int  cx;
    int  cy;
    UINT flags;    /* SWP_* flags */
} WINDOWPOS, *LPWINDOWPOS;

/* Message-parameter packing macros (Windows Structures pages
 * aa453543 / ms911640 / ms911780).  The CE pages print the
 * definitions using MAKELONG with a cast to the parameter type;
 * MAKEWPARAM's page prints "(LPARAM)" where the cast must be to
 * WPARAM (documentation typo; conflict recorded in docs/inventory). */
#define MAKEWPARAM(l, h) ((WPARAM) MAKELONG((l), (h)))
#define MAKELPARAM(l, h) ((LPARAM) MAKELONG((l), (h)))
#define MAKELRESULT(l, h) ((LRESULT) MAKELONG((l), (h)))

/* ------------------------------------------------------------------ */
/* Keyboard / input structures (Header Winuser.h).                    */
/* ------------------------------------------------------------------ */

/* aa452837 "ACCEL (Windows CE 5.0)": accelerator-table entry. */
typedef struct tagACCEL {
    BYTE fVirt;    /* FVIRTKEY / FNOINVERT / FSHIFT / FCONTROL / FALT */
    WORD key;
    WORD cmd;
    WORD pad;      /* page member; unused, present for ABI alignment */
} ACCEL, *LPACCEL;

/* aa453247 "KEYBDINPUT": keyboard input event (SendInput). */
typedef struct tagKEYBDINPUT {
    WORD      wVk;
    WORD      wScan;
    DWORD     dwFlags;
    DWORD     time;
    ULONG_PTR dwExtraInfo;
} KEYBDINPUT, *PKEYBDINPUT;

/* ms931454 "MOUSEINPUT": mouse input event (SendInput). */
typedef struct tagMOUSEINPUT {
    LONG      dx;
    LONG      dy;
    DWORD     mouseData;
    DWORD     dwFlags;
    DWORD     time;
    ULONG_PTR dwExtraInfo;
} MOUSEINPUT, *PMOUSEINPUT;

/* HARDWAREINPUT: the ms909851 "INPUT (Windows CE 5.0)" page's union
 * references HARDWAREINPUT, but none of the CE GWES books fetched
 * publishes the type's members (CE Keyboard Structures leaves cover
 * ACCEL/KEYBDINPUT/MOUSEINPUT/INPUT only).  The layout below is the
 * fixed Win32 ABI form from Microsoft's official HARDWAREINPUT
 * structure reference (winuser.h): DWORD uMsg; WORD wParamL;
 * WORD wParamH.  Provenance recorded in docs/inventory.md. */
typedef struct tagHARDWAREINPUT {
    DWORD uMsg;     /* message generated by the input hardware */
    WORD  wParamL;  /* low-order word of the lParam for uMsg */
    WORD  wParamH;  /* high-order word of the lParam for uMsg */
} HARDWAREINPUT, *PHARDWAREINPUT, *LPHARDWAREINPUT;

/* ms909851 "INPUT": a synthesized input event (SendInput). */
typedef struct tagINPUT {
    DWORD type;      /* INPUT_MOUSE / INPUT_KEYBOARD / INPUT_HARDWARE */
    union {
        MOUSEINPUT   mi;
        KEYBDINPUT   ki;
        HARDWAREINPUT hi;
    };
} INPUT, *PINPUT, *LPINPUT;

/* ------------------------------------------------------------------ */
/* Scroll Bars structures and value macros.                           */
/* ------------------------------------------------------------------ */

/* GetScrollInfo / SetScrollInfo operate on a SCROLLINFO.  The CE 5.0
 * archive's Scroll Bars Structures book points at the WinCE 6.0
 * archive (ee504371) for SCROLLINFO, so the fixed Win32-ABI layout is
 * used (UINT cbSize; UINT fMask; int nMin; int nMax; UINT nPage;
 * int nPos; int nTrackPos).  The SIF_* masks / SB_* bar identifiers /
 * SW_* ScrollWindowEx flags are the fixed Win32-ABI values of the
 * official scroll-bar reference used by the CE function pages. */
typedef struct tagSCROLLINFO {
    UINT cbSize;    /* sizeof(SCROLLINFO) */
    UINT fMask;     /* SIF_* flags indicating valid members */
    int  nMin;      /* minimum scrolling position */
    int  nMax;      /* maximum scrolling position */
    UINT nPage;     /* page size */
    int  nPos;      /* current position */
    int  nTrackPos; /* immediate tracking position */
} SCROLLINFO, *LPSCROLLINFO;

#define SIF_RANGE            0x0001
#define SIF_PAGE             0x0002
#define SIF_POS              0x0004
#define SIF_DISABLENOSCROLL  0x0008
#define SIF_TRACKPOS         0x0010
#define SIF_ALL              (SIF_RANGE | SIF_PAGE | SIF_POS | \
                              SIF_TRACKPOS)
#define SB_HORZ              0
#define SB_VERT              1
#define SB_CTL               2
#define SB_BOTH              3
#define SW_SCROLLCHILDREN    0x0001
#define SW_INVALIDATE        0x0002
#define SW_ERASE             0x0004
#define SW_SMOOTHSCROLL      0x0010

/* ------------------------------------------------------------------ */
/* Windows Functions (Header: Winuser.h unless noted).               */
/* ------------------------------------------------------------------ */

/* ms908193 "CreateWindowEx (Windows CE 5.0)": extended-style window
 * creation.  CE 1.0+. */
HWND CreateWindowExW(DWORD dwExStyle, LPCTSTR lpClassName,
                     LPCTSTR lpWindowName, DWORD dwStyle, int x, int y,
                     int nWidth, int nHeight, HWND hWndParent,
                     HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
#define CreateWindowEx CreateWindowExW

/* ms908192 "CreateWindow (Windows CE 5.0)": window creation without
 * extended styles.  CE 1.0+.  (Page signature: HANDLE hInstance and
 * PVOID lpParam.) */
HWND CreateWindowW(LPCTSTR lpClassName, LPCTSTR lpWindowName,
                   DWORD dwStyle, int x, int y, int nWidth, int nHeight,
                   HWND hWndParent, HMENU hMenu, HANDLE hInstance,
                   PVOID lpParam);
#define CreateWindow CreateWindowW

/* ms913089 "RegisterClass (Windows CE 5.0)": registers a window class;
 * returns an ATOM identifying the class.  CE 1.0+. */
ATOM RegisterClassW(const WNDCLASS *lpWndClass);
#define RegisterClass RegisterClassW

/* ms914082 "UnregisterClass (Windows CE 5.0)".  CE 1.0+. */
BOOL UnregisterClassW(LPCTSTR lpClassName, HINSTANCE hInstance);
#define UnregisterClass UnregisterClassW

/* ms929211 "GetClassInfo (Windows CE 5.0)": fills a WNDCLASS for a
 * registered class.  CE 1.0+. */
BOOL GetClassInfoW(HINSTANCE hInstance, LPCTSTR lpClassName,
                   LPWNDCLASS lpWndClass);
#define GetClassInfo GetClassInfoW

/* ms929212 "GetClassLong (Windows CE 5.0)": retrieves a class-long
 * value (GCL_* index).  CE 1.0+. */
DWORD GetClassLongW(HWND hWnd, int nIndex);
#define GetClassLong GetClassLongW

/* ms940014 "SetClassLong (Windows CE 5.0)".  CE 1.0+. */
DWORD SetClassLongW(HWND hWnd, int nIndex, LONG dwNewLong);
#define SetClassLong SetClassLongW

/* ms929213 "GetClassName (Windows CE 5.0)".  CE 1.0+. */
int GetClassNameW(HWND hWnd, LPTSTR lpClassName, int nMaxCount);
#define GetClassName GetClassNameW

/* aa453180 "GetWindowLong (Windows CE 5.0)" / aa453661 "SetWindowLong":
 * per-window long values (GWL_* / DWL_* index).  CE 1.0+. */
LONG GetWindowLongW(HWND hWnd, int nIndex);
#define GetWindowLong GetWindowLongW
LONG SetWindowLongW(HWND hWnd, int nIndex, LONG dwNewLong);
#define SetWindowLong SetWindowLongW

/* ms929229 "GetDesktopWindow (Windows CE 5.0)".  CE 1.0+. */
HWND GetDesktopWindow(void);

/* ms929244 "GetForegroundWindow" / ms940024 "SetForegroundWindow"
 * (CE 1.0+).  SetForegroundWindow's page documents the CE "special
 * HWND" convention (((HWND)((ULONG)hwnd)|0x01) for the background
 * process). */
HWND GetForegroundWindow(void);
BOOL SetForegroundWindow(HWND hWnd);

/* aa453233 "IsWindow" / aa453235 "IsWindowVisible" / ms909862 "IsChild"
 * (CE 1.0+). */
BOOL IsWindow(HWND hWnd);
BOOL IsWindowVisible(HWND hWnd);
BOOL IsChild(HWND hWndParent, HWND hWnd);

/* aa453152 "GetParent" / aa453645 "SetParent" (CE 1.0+). */
HWND GetParent(HWND hWnd);
HWND SetParent(HWND hWndChild, HWND hWndNewParent);

/* aa453070 "FindWindow (Windows CE 5.0)": finds a top-level window by
 * class name and/or window name (NULL = wildcard).  CE 1.0+. */
HWND FindWindowW(LPCTSTR lpClassName, LPCTSTR lpWindowName);
#define FindWindow FindWindowW

/* ms928578 "ChildWindowFromPoint" / ms914099 "WindowFromPoint". */
HWND ChildWindowFromPoint(HWND hWndParent, POINT Point);
HWND WindowFromPoint(POINT Point);

/* aa453051 "EnumWindows": enumerates top-level windows; aa453052
 * "EnumWindowsProc" documents the callback. */
BOOL EnumWindows(WNDENUMPROC lpEnumFunc, LPARAM lParam);

/* aa453178 "GetWindow": returns the window with the given relationship
 * (GW_* command) to hWnd. */
HWND GetWindow(HWND hWnd, UINT uCmd);

/* Window rectangles and text. */
BOOL GetClientRect(HWND hWnd, LPRECT lpRect);        /* ms929214 */
BOOL GetWindowRect(HWND hWnd, LPRECT lpRect);        /* aa453181 */
int  GetWindowTextLengthW(HWND hWnd);                /* aa453184 */
#define GetWindowTextLength GetWindowTextLengthW
int  GetWindowTextW(HWND hWnd, LPTSTR lpString,      /* aa453183 */
                    int nMaxCount);
#define GetWindowText GetWindowTextW
BOOL SetWindowTextW(HWND hWnd, LPCTSTR lpString);    /* aa453664 */
#define SetWindowText SetWindowTextW

/* aa453185 "GetWindowThreadProcessId": returns the thread that created
 * the window and (optionally) its process id. */
DWORD GetWindowThreadProcessId(HWND hWnd, LPDWORD lpdwProcessId);

/* Show / move / size / z-order. */
BOOL ShowWindow(HWND hWnd, int nCmdShow);            /* aa453731 */
BOOL BringWindowToTop(HWND hWnd);                    /* aa452899 */
BOOL MoveWindow(HWND hWnd, int X, int Y, int nWidth, int nHeight,
                BOOL bRepaint);                      /* ms931458 */
BOOL SetWindowPos(HWND hWnd, HWND hWndInsertAfter,   /* aa453662 */
                  int X, int Y, int cx, int cy, UINT uFlags);

/* aa452849 "AdjustWindowRectEx": computes the required window size for
 * a desired client rectangle and styles. */
BOOL AdjustWindowRectEx(LPRECT lpRect, DWORD dwStyle, BOOL bMenu,
                        DWORD dwExStyle);

/* aa452929 "DefWindowProc": default window-procedure behavior.
 * aa452919 "CallWindowProc": calls another window procedure. */
LRESULT DefWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
LRESULT CallWindowProc(WNDPROC lpPrevWndFunc, HWND hWnd, UINT Msg,
                       WPARAM wParam, LPARAM lParam);

/* aa452942 "DestroyWindow". */
BOOL DestroyWindow(HWND hWnd);

/* Deferred window positioning (CE 2.10+). */
HDWP BeginDeferWindowPos(int nNumWindows);           /* aa452870 */
HDWP DeferWindowPos(HDWP hWinPosInfo, HWND hWnd,     /* ms908210 */
                    HWND hWndInsertAfter, int x, int y, int cx,
                    int cy, UINT uFlags);
BOOL EndDeferWindowPos(HDWP hWinPosInfo);            /* aa453037 */

/* ------------------------------------------------------------------ */
/* Window Properties Reference.  The pages' Header row is Windows.h   */
/* (CE .NET 4.0+), so the declarations live in windows.h; the         */
/* enumeration callback typedef PROPENUMPROCEX is declared above.     */
/* ------------------------------------------------------------------ */

/* ------------------------------------------------------------------ */
/* Windows Timer Reference functions.                                 */
/* ------------------------------------------------------------------ */

/* aa453657 "SetTimer": creates a timer; if lpTimerFunc is NULL WM_TIMER
 * messages are posted to hWnd.  CE 2.0+.  KillTimer's page (aa453248)
 * prints Header: Winbase.h, so it is declared in winbase.h. */
UINT SetTimer(HWND hWnd, UINT nIDEvent, UINT uElapse,
              TIMERPROC lpTimerFunc);

/* ms940382 "SystemIdleTimerReset": resets the system idle timer so the
 * screen saver/power manager does not engage.  CE 2.0+. */
void SystemIdleTimerReset(void);

/* aa453746 "TimerProc" documents the timer-callback prototype (typedef
 * TIMERPROC above). */

/* ------------------------------------------------------------------ */
/* Carets Reference functions (CE 1.0+).                              */
/* ------------------------------------------------------------------ */

AKARI_CE_IMPORT BOOL CreateCaret(HWND hWnd, HBITMAP hBitmap, int nWidth,  /* ms908164 */
                 int nHeight) AKARI_CE_NAME(CreateCaret);
AKARI_CE_IMPORT BOOL DestroyCaret(void) AKARI_CE_NAME(DestroyCaret);                                  /* aa452936 */
AKARI_CE_IMPORT UINT GetCaretBlinkTime(void) AKARI_CE_NAME(GetCaretBlinkTime);                             /* ms929209 */
AKARI_CE_IMPORT BOOL GetCaretPos(LPPOINT lpPoint) AKARI_CE_NAME(GetCaretPos);                        /* ms929210 */
AKARI_CE_IMPORT BOOL HideCaret(HWND hWnd) AKARI_CE_NAME(HideCaret);                                /* ms929930 */
AKARI_CE_IMPORT BOOL SetCaretBlinkTime(UINT uMSeconds) AKARI_CE_NAME(SetCaretBlinkTime);                   /* ms940012 */
AKARI_CE_IMPORT BOOL SetCaretPos(int X, int Y) AKARI_CE_NAME(SetCaretPos);                           /* ms940013 */
AKARI_CE_IMPORT BOOL ShowCaret(HWND hWnd) AKARI_CE_NAME(ShowCaret);                                /* aa453729 */

/* ------------------------------------------------------------------ */
/* Atoms Reference functions.  The official pages (aa453188/aa453189/ */
/* aa453190) print Header: Windows.h (CE .NET 4.0+), so the atoms are */
/* declared in windows.h.                                             */
/* ------------------------------------------------------------------ */

/* ------------------------------------------------------------------ */
/* GWES Message Queue functions (Header: Winuser.h except where the   */
/* page prints Windows.h -- see windows.h; pages with a Coredll.lib   */
/* Link Library row feed def/coredll-doc.def).                        */
/* ------------------------------------------------------------------ */

AKARI_CE_IMPORT BOOL GetMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin,    /* aa453135 */
                 UINT wMsgFilterMax) AKARI_CE_NAME(GetMessage);
AKARI_CE_IMPORT BOOL PeekMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin,   /* ms911928 */
                  UINT wMsgFilterMax, UINT wRemoveMsg) AKARI_CE_NAME(PeekMessage);

/* aa452956 "DispatchMessage": dispatches to the window procedure.  The
 * page prints LONG as the return type. */
AKARI_CE_IMPORT LONG DispatchMessage(const MSG *lpmsg) AKARI_CE_NAME(DispatchMessage);

/* aa453776 "TranslateMessage": translates virtual-key messages into
 * character messages. */
AKARI_CE_IMPORT BOOL TranslateMessage(const MSG *lpMsg) AKARI_CE_NAME(TranslateMessage);

/* ms911937 "PostMessage" / ms911939 "PostThreadMessage" /
 * ms939980 "SendMessage" / ms939983 "SendNotifyMessage". */
AKARI_CE_IMPORT BOOL PostMessage(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) AKARI_CE_NAME(PostMessage);
AKARI_CE_IMPORT BOOL PostThreadMessage(DWORD idThread, UINT Msg, WPARAM wParam,
                        LPARAM lParam) AKARI_CE_NAME(PostThreadMessage);
AKARI_CE_IMPORT LRESULT SendMessage(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) AKARI_CE_NAME(SendMessage);
AKARI_CE_IMPORT BOOL SendNotifyMessage(HWND hWnd, UINT Msg, WPARAM wParam,
                        LPARAM lParam) AKARI_CE_NAME(SendNotifyMessage);

/* ms911938 "PostQuitMessage": posts WM_QUIT (wParam = nExitCode). */
AKARI_CE_IMPORT void PostQuitMessage(int nExitCode) AKARI_CE_NAME(PostQuitMessage);

/* ms939737 "RegisterWindowMessage": registers a unique message number
 * for the given string.  CE 2.0+. */
AKARI_CE_IMPORT UINT RegisterWindowMessageW(LPCTSTR lpString) AKARI_CE_NAME(RegisterWindowMessageW);
#define RegisterWindowMessage RegisterWindowMessageW

/* aa453136 "GetMessagePos": cursor position packed into a DWORD
 * (x = low word, y = high word) at the last message read. */
AKARI_CE_IMPORT DWORD GetMessagePos(void) AKARI_CE_NAME(GetMessagePos);

/* aa453137 "GetMessageQueueReadyTimeStamp": the page prints Header:
 * Windows.h, so it is declared in windows.h. */

/* aa453138 "GetMessageSource": returns a value identifying the source
 * of the current message. */
AKARI_CE_IMPORT UINT GetMessageSource(void) AKARI_CE_NAME(GetMessageSource);

/* aa453156 "GetQueueStatus": returns the QS_* queue-status flags of
 * the calling thread's queue (CE .NET 4.2+). */
AKARI_CE_IMPORT DWORD GetQueueStatus(UINT flags) AKARI_CE_NAME(GetQueueStatus);

/* ms909852 "InSendMessage": TRUE while processing a sent message. */
AKARI_CE_IMPORT BOOL InSendMessage(VOID) AKARI_CE_NAME(InSendMessage);

/* ------------------------------------------------------------------ */
/* Keyboard Reference functions (Header: Winuser.h unless noted).     */
/*                                                                     */
/* Six further CE Keyboard-Functions leaves are OEM-layout pages whose */
/* Header rows name Pwinuser.h (GetAsyncShiftFlags aa453955,           */
/* GetForegroundInfo ms929241, GetForegroundKeyboardLayoutHandle       */
/* ms929242, GetForegroundKeyboardTarget ms929243, KeybdGetDeviceInfo  */
/* aa453246, PostKeybdMessage ms911936) and depend on the OEM keybd     */
/* types (GET_FOREGROUND_INFO aa453186, KEY_STATE_FLAGS ms902150,      */
/* Header Keybd.h).  They are deferred to the OEM/input-method batch   */
/* and recorded in docs/inventory.md.                                  */
/* ------------------------------------------------------------------ */

AKARI_CE_IMPORT SHORT GetKeyState(int nVirtKey) AKARI_CE_NAME(GetKeyState);                       /* aa453132 */
AKARI_CE_IMPORT SHORT GetAsyncKeyState(int vKey) AKARI_CE_NAME(GetAsyncKeyState);                      /* ms929204 */
AKARI_CE_IMPORT HWND  GetFocus(void) AKARI_CE_NAME(GetFocus);                                  /* ms929240 */
AKARI_CE_IMPORT HWND  SetFocus(HWND hWnd) AKARI_CE_NAME(SetFocus);                             /* ms940023 */
AKARI_CE_IMPORT HWND  GetActiveWindow(void) AKARI_CE_NAME(GetActiveWindow);                           /* ms929203 */
AKARI_CE_IMPORT HWND  SetActiveWindow(HWND hWnd) AKARI_CE_NAME(SetActiveWindow);                      /* ms939986 */
AKARI_CE_IMPORT BOOL  EnableWindow(HWND hWnd, BOOL bEnable) AKARI_CE_NAME(EnableWindow);           /* aa453035 */
AKARI_CE_IMPORT BOOL  IsWindowEnabled(HWND hWnd) AKARI_CE_NAME(IsWindowEnabled);                      /* aa453234 */

/* Keyboard layout (HKL). */
AKARI_CE_IMPORT HKL   ActivateKeyboardLayout(HKL hkl, UINT Flags) AKARI_CE_NAME(ActivateKeyboardLayout);     /* aa452845 */
AKARI_CE_IMPORT HKL   GetKeyboardLayout(DWORD idThread) AKARI_CE_NAME(GetKeyboardLayout);               /* ms929249 */
AKARI_CE_IMPORT UINT  GetKeyboardLayoutList(int nBuff, HKL *lpList) AKARI_CE_NAME(GetKeyboardLayoutList);   /* ms929250 */
AKARI_CE_IMPORT BOOL  GetKeyboardLayoutNameW(LPTSTR pwszKLID) AKARI_CE_NAME(GetKeyboardLayoutNameW);         /* ms929252 */
#define GetKeyboardLayoutName GetKeyboardLayoutNameW
AKARI_CE_IMPORT DWORD GetKeyboardStatus(VOID) AKARI_CE_NAME(GetKeyboardStatus);                         /* ms929253 */
AKARI_CE_IMPORT int   GetKeyboardType(int nTypeFlag) AKARI_CE_NAME(GetKeyboardType);                  /* ms929254 */

/* ms911789 "MapVirtualKey". */
AKARI_CE_IMPORT UINT MapVirtualKey(UINT uCode, UINT uMapType) AKARI_CE_NAME(MapVirtualKey);

/* keybd_event (aa453245): synthesizes a keystroke; dwFlags is
 * KEYEVENTF_EXTENDEDKEY / KEYEVENTF_KEYUP. */
AKARI_CE_IMPORT VOID keybd_event(BYTE bVk, BYTE bScan, DWORD dwFlags, DWORD dwExtraInfo) AKARI_CE_NAME(keybd_event);

/* LoadKeyboardLayout (aa453414): the page's signature takes LPCSTR
 * pwszKLID (a layout identifier string). */
AKARI_CE_IMPORT HKL LoadKeyboardLayout(LPCSTR pwszKLID, UINT Flags) AKARI_CE_NAME(LoadKeyboardLayout);

/* Hot keys (CE 2.0+). */
AKARI_CE_IMPORT BOOL RegisterHotKey(HWND hWnd, int id, UINT fsModifiers, UINT vk) AKARI_CE_NAME(RegisterHotKey);
BOOL UnregisterHotKey(HWND hWnd, int id);

/* Accelerator tables (CE 1.0+; Link Library Accel.lib). */
AKARI_CE_IMPORT HACCEL CreateAcceleratorTable(LPACCEL lpaccl, int cEntries) AKARI_CE_NAME(CreateAcceleratorTable); /* ms908162 */
AKARI_CE_IMPORT HACCEL LoadAcceleratorsW(HINSTANCE hInstance,                /* aa453407 */
                         LPCTSTR lpTableName) AKARI_CE_NAME(LoadAcceleratorsW);
#define LoadAccelerators LoadAcceleratorsW
AKARI_CE_IMPORT BOOL   DestroyAcceleratorTable(HACCEL hAccel) AKARI_CE_NAME(DestroyAcceleratorTable);              /* aa452935 */
AKARI_CE_IMPORT int    TranslateAccelerator(HWND hWnd, HACCEL hAccTable,    /* aa453775 */
                            LPMSG lpMsg) AKARI_CE_NAME(TranslateAccelerator);

/* ms932719 "SendInput": synthesizes mouse/keyboard/hardware input. */
AKARI_CE_IMPORT UINT SendInput(UINT nInputs, LPINPUT pInputs, int cbSize) AKARI_CE_NAME(SendInput);

/* ------------------------------------------------------------------ */
/* Scroll Bars Reference functions (Header: Winuser.h).              */
/* ------------------------------------------------------------------ */

AKARI_CE_IMPORT BOOL GetScrollInfo(HWND hwnd, int fnBar, LPSCROLLINFO lpsi) AKARI_CE_NAME(GetScrollInfo); /* aa453163 */
AKARI_CE_IMPORT int  SetScrollInfo(HWND hwnd, int fnBar, LPSCROLLINFO lpsi,  /* aa453652 */
                   BOOL fRedraw) AKARI_CE_NAME(SetScrollInfo);
AKARI_CE_IMPORT int  SetScrollPos(HWND hWnd, int nBar, int nPos, BOOL bRedraw) AKARI_CE_NAME(SetScrollPos); /* aa453653 */
AKARI_CE_IMPORT BOOL SetScrollRange(HWND hWnd, int nBar, int nMinPos,          /* aa453654 */
                    int nMaxPos, BOOL bRedraw) AKARI_CE_NAME(SetScrollRange);
AKARI_CE_IMPORT int  ScrollWindowEx(HWND hWnd, int dx, int dy,                 /* ms932713 */
                    const RECT *prcScroll, const RECT *prcClip,
                    HRGN hrgnUpdate, LPRECT prcUpdate, UINT flags) AKARI_CE_NAME(ScrollWindowEx);

/* ------------------------------------------------------------------ */
/* Entry-point and window-procedure prototypes published by the CE    */
/* Windows book (Header: Winuser.h).                                  */
/* ------------------------------------------------------------------ */

/* ms914104 "WinMain (Windows CE 5.0)": CE application entry point.
 * (The page prints LPWSTR for the command line.) */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPWSTR lpCmdLine, int nShowCmd);

/* ms914102 "WindowProc (Windows CE 5.0)": the window-procedure
 * prototype documented by the CE page. */
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam);

/* ------------------------------------------------------------------ */
/* M27: GDI Reference items whose CE 5.0 pages list Header: Winuser.h. */
/*                                                                     */
/* Painting/DC, coordinate, window-region and rectangle helpers.  Page */
/* "Link Library" rows name Coredll.lib (+Winmgr.lib for the window-   */
/* manager set), Rectapi.lib for the rectangle helpers, Nclient.lib    */
/* for DrawFrameControl and Loadbmp.lib for LoadBitmap; see the        */
/* per-page comments in docs/inventory.md.                             */
/* ------------------------------------------------------------------ */

/* ms911912 "PAINTSTRUCT": paint information filled by BeginPaint. */
typedef struct tagPAINTSTRUCT {
    HDC  hdc;
    BOOL fErase;
    RECT rcPaint;
    BOOL fRestore;
    BOOL fIncUpdate;
    BYTE rgbReserved[32];
} PAINTSTRUCT, *LPPAINTSTRUCT;

/* aa452871 "BeginPaint" */
AKARI_CE_IMPORT HDC BeginPaint(HWND hwnd, LPPAINTSTRUCT lpPaint) AKARI_CE_NAME(BeginPaint);
/* ms928584 "ClientToScreen" */
AKARI_CE_IMPORT BOOL ClientToScreen(HWND hWnd, LPPOINT lpPoint) AKARI_CE_NAME(ClientToScreen);
/* ms908152 "CopyRect" */
AKARI_CE_IMPORT BOOL CopyRect(LPRECT lprcDst, const RECT* lprcSrc) AKARI_CE_NAME(CopyRect);
/* aa452970 "DrawFrameControl" */
AKARI_CE_IMPORT BOOL DrawFrameControl(HDC hdc, LPRECT lprc, UINT uType, UINT uState) AKARI_CE_NAME(DrawFrameControl);
/* aa453041 "EndPaint" */
AKARI_CE_IMPORT BOOL EndPaint(HWND hWnd, CONST PAINTSTRUCT* lpPaint) AKARI_CE_NAME(EndPaint);
/* aa453055 "EqualRect" */
AKARI_CE_IMPORT BOOL EqualRect(const RECT* lprc1, const RECT* lprc2) AKARI_CE_NAME(EqualRect);
/* ms929227 "GetDC" */
AKARI_CE_IMPORT HDC GetDC(HWND hWnd) AKARI_CE_NAME(GetDC);
/* ms929228 "GetDCEx" */
AKARI_CE_IMPORT HDC GetDCEx(HWND hWnd, HRGN hrgnClip, DWORD flags) AKARI_CE_NAME(GetDCEx);
/* aa453174 "GetUpdateRect" */
AKARI_CE_IMPORT BOOL GetUpdateRect(HWND hWnd, LPRECT lpRect, BOOL bErase) AKARI_CE_NAME(GetUpdateRect);
/* aa453175 "GetUpdateRgn" */
AKARI_CE_IMPORT int GetUpdateRgn(HWND hWnd, HRGN hRgn, BOOL bErase) AKARI_CE_NAME(GetUpdateRgn);
/* aa453179 "GetWindowDC" */
AKARI_CE_IMPORT HDC GetWindowDC(HWND hWnd) AKARI_CE_NAME(GetWindowDC);
/* aa453182 "GetWindowRgn" */
AKARI_CE_IMPORT int GetWindowRgn(HWND hWnd, HRGN hRgn) AKARI_CE_NAME(GetWindowRgn);
/* ms909856 "IntersectRect" */
AKARI_CE_IMPORT BOOL IntersectRect(LPRECT lprcDst, const RECT* lprcSrc1,
    const RECT* lprcSrc2) AKARI_CE_NAME(IntersectRect);
/* ms909857 "InvalidateRect" */
AKARI_CE_IMPORT BOOL InvalidateRect(HWND hWnd, const RECT* lpRect, BOOL bErase) AKARI_CE_NAME(InvalidateRect);
/* ms909894 "IsRectEmpty" */
AKARI_CE_IMPORT BOOL IsRectEmpty(const RECT* lprc) AKARI_CE_NAME(IsRectEmpty);
/* aa453409 "LoadBitmap" */
AKARI_CE_IMPORT HBITMAP LoadBitmap(HINSTANCE hInstance, LPCTSTR lpBitmapName) AKARI_CE_NAME(LoadBitmap);
/* ms911790 "MapWindowPoints" */
AKARI_CE_IMPORT int MapWindowPoints(HWND hWndFrom, HWND hWndTo, LPPOINT lpPoints,
    UINT cPoints) AKARI_CE_NAME(MapWindowPoints);
/* ms911891 "OffsetRect" */
AKARI_CE_IMPORT BOOL OffsetRect(LPRECT lprc, int dx, int dy) AKARI_CE_NAME(OffsetRect);
/* aa453601 "PtInRect" */
AKARI_CE_IMPORT BOOL PtInRect(const RECT* lprc, POINT pt) AKARI_CE_NAME(PtInRect);
/* ms939760 "ReleaseDC" */
AKARI_CE_IMPORT int ReleaseDC(HWND hWnd, HDC hDC) AKARI_CE_NAME(ReleaseDC);
/* ms932582 "ScreenToClient" */
AKARI_CE_IMPORT BOOL ScreenToClient(HWND hWnd, LPPOINT lpPoint) AKARI_CE_NAME(ScreenToClient);
/* aa453649 "SetRectEmpty" */
AKARI_CE_IMPORT BOOL SetRectEmpty(LPRECT lprc) AKARI_CE_NAME(SetRectEmpty);
/* aa453663 "SetWindowRgn" */
AKARI_CE_IMPORT int SetWindowRgn(HWND hWnd, HRGN hRgn, BOOL bRedraw) AKARI_CE_NAME(SetWindowRgn);
/* ms940381 "SubtractRect" */
AKARI_CE_IMPORT BOOL SubtractRect(LPRECT lprcDst, const RECT* lprcSrc1, const RECT* lprcSrc2) AKARI_CE_NAME(SubtractRect);
/* ms914081 "UnionRect" */
AKARI_CE_IMPORT BOOL UnionRect(LPRECT lprcDst, const RECT* lprcSrc1, const RECT* lprcSrc2) AKARI_CE_NAME(UnionRect);
/* ms914085 "UpdateWindow" */
AKARI_CE_IMPORT BOOL UpdateWindow(HWND hWnd) AKARI_CE_NAME(UpdateWindow);
/* ms914091 "ValidateRect" */
AKARI_CE_IMPORT BOOL ValidateRect(HWND hWnd, const RECT* lpRect) AKARI_CE_NAME(ValidateRect);

/* ------------------------------------------------------------------ */
/* M28: Dialog Boxes / Menus / Clipboards / Resources(icon) / System-  */
/* Information Reference books.  All items in this block have official  */
/* pages whose Requirements row prints Header: Winuser.h unless a       */
/* comment says otherwise; per-page Link Library rows are noted and     */
/* feed the export defs under def/.                                     */
/* ------------------------------------------------------------------ */

/* aa452951 "DialogProc (Windows CE 5.0)" documents the dialog-callback */
/* prototype (BOOL CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM));    */
/* DLGPROC is the typedef used by the CreateDialog / DialogBox family.  */
typedef BOOL (CALLBACK *DLGPROC)(HWND hDlg, UINT uMsg, WPARAM wParam,
                                 LPARAM lParam);

/* aa452958 "DLGITEMTEMPLATE": in-memory standard dialog template for   */
/* one control (combined with DLGTEMPLATE).  CE 1.0+; Winuser.h.        */
typedef struct {
    DWORD style;         /* window + control styles (WS_*, BS_*, ...)  */
    DWORD dwExtendedStyle;
    short x;             /* dialog-box units */
    short y;
    short cx;
    short cy;
    WORD  id;            /* control identifier */
} DLGITEMTEMPLATE;

/* aa452960 "DLGTEMPLATE": in-memory standard dialog template header.   */
/* CE 1.0+; Winuser.h.  (The CE page notes Windows CE does not support  */
/* dialog menus.)                                                       */
typedef struct {
    DWORD style;         /* window + DS_* styles */
    DWORD dwExtendedStyle;
    WORD  cdit;          /* number of DLGITEMTEMPLATE structures */
    short x;             /* dialog-box units */
    short y;
    short cx;
    short cy;
} DLGTEMPLATE;

typedef DLGTEMPLATE       *LPDLGTEMPLATE;
typedef const DLGTEMPLATE *LPCDLGTEMPLATE;
typedef DLGITEMTEMPLATE   *LPDLGITEMTEMPLATE;
typedef const DLGITEMTEMPLATE *LPCDLGITEMTEMPLATE;

/* ms911822 "MENUITEMINFO": menu-item information (Get/SetMenuItemInfo).*/
/* CE 1.0+; Winuser.h.  (CE member list: UINT wID and DWORD dwItemData; */
/* dwTypeData carries the item text for MIIM_TYPE / MFT_STRING.)        */
typedef struct tagMENUITEMINFO {
    UINT    cbSize;        /* sizeof(MENUITEMINFO) */
    UINT    fMask;         /* MIIM_* */
    UINT    fType;         /* MFT_* */
    UINT    fState;        /* MFS_* */
    UINT    wID;           /* application-defined menu-item id */
    HMENU   hSubMenu;
    HBITMAP hbmpChecked;
    HBITMAP hbmpUnchecked;
    DWORD   dwItemData;
    LPTSTR  dwTypeData;    /* item text */
    UINT    cch;           /* length of dwTypeData in characters */
} MENUITEMINFO, *LPMENUITEMINFO, *LPCMENUITEMINFO;

/* aa453766 "TPMPARAMS": extended TrackPopupMenuEx parameters.  CE     */
/* 1.0+; Winuser.h.                                                     */
typedef struct tagTPMPARAMS {
    UINT cbSize;          /* sizeof(TPMPARAMS) */
    RECT rcExclude;       /* rectangle to exclude (screen coords) */
} TPMPARAMS, *LPTPMPARAMS;

/* ms928818 "COMBOBOXINFO": combo box status (CB_GETCOMBOBOXINFO).      */
typedef struct tagCOMBOBOXINFO {
    DWORD cbSize;         /* sizeof(COMBOBOXINFO); caller sets */
    RECT  rcItem;         /* edit-box rectangle */
    RECT  rcButton;       /* drop-down button rectangle */
    DWORD stateButton;    /* unsupported on CE */
    HWND  hwndCombo;
    HWND  hwndItem;       /* edit control */
    HWND  hwndList;       /* drop-down list */
} COMBOBOXINFO, *PCOMBOBOXINFO, *LPCOMBOBOXINFO;

/* ms911820 "MEASUREITEMSTRUCT": owner-drawn dimensions (WM_MEASUREITEM).*/
typedef struct tagMEASUREITEMSTRUCT {
    UINT  CtlType;        /* ODT_* */
    UINT  CtlID;
    UINT  itemID;
    UINT  itemWidth;
    UINT  itemHeight;
    DWORD itemData;
} MEASUREITEMSTRUCT;

/* aa452931 "DELETEITEMSTRUCT": deleted list/combo item (WM_DELETEITEM).*/
typedef struct tagDELETEITEMSTRUCT {
    UINT CtlType;         /* ODT_LISTBOX / ODT_COMBOBOX */
    UINT CtlID;
    UINT itemID;
    HWND hwndItem;
    UINT itemData;
} DELETEITEMSTRUCT;

/* ms929934 "ICONINFO (Windows CE 5.0)": the official page lists Header:*/
/* Commctrl.h; CreateIconIndirect (ms908175) and GetIconInfo (ms929247) */
/* list Header: Winuser.h.  Fixed Win32-ABI member layout.             */
typedef struct _ICONINFO {
    BOOL    fIcon;        /* TRUE = icon, FALSE = cursor */
    DWORD   xHotspot;
    DWORD   yHotspot;
    HBITMAP hbmMask;
    HBITMAP hbmColor;
} ICONINFO, *PICONINFO, *LPICONINFO;

/* aa453542 "MAKEINTRESOURCE": converts an integer resource identifier  */
/* into a resource-name string pointer.  The CE page prints the macro   */
/* body; Header: Winuser.h.                                             */
#define MAKEINTRESOURCE(i) ((LPTSTR) ((DWORD) ((WORD) (i))))

/* ------------------------------------------------------------------ */
/* Menus Reference functions (CE 1.0+, Header Winuser.h).             */
/* ------------------------------------------------------------------ */

BOOL  AppendMenuW(HMENU hMenu, UINT uFlags, UINT uIDNewItem,
                  LPCTSTR lpNewItem);                 /* aa452862 */
#define AppendMenu AppendMenuW
AKARI_CE_IMPORT BOOL  CheckMenuItem(HMENU hmenu, UINT uIDCheckItem, UINT uCheck) AKARI_CE_NAME(CheckMenuItem); /* ms928575 */
AKARI_CE_IMPORT BOOL  CheckMenuRadioItem(HMENU hmenu, UINT idFirst, UINT idLast,  /* ms928576 */
                         UINT idCheck, UINT uFlags) AKARI_CE_NAME(CheckMenuRadioItem);
AKARI_CE_IMPORT HMENU CreateMenu(void) AKARI_CE_NAME(CreateMenu);                               /* ms908177 */
AKARI_CE_IMPORT HMENU CreatePopupMenu(void) AKARI_CE_NAME(CreatePopupMenu);                          /* ms908182 */
AKARI_CE_IMPORT BOOL  DeleteMenu(HMENU hMenu, UINT uPosition, UINT uFlags) AKARI_CE_NAME(DeleteMenu);       /* aa452932 */
AKARI_CE_IMPORT BOOL  DestroyMenu(HMENU hMenu) AKARI_CE_NAME(DestroyMenu);                       /* aa452940 */
AKARI_CE_IMPORT BOOL  DrawMenuBar(HWND hWnd) AKARI_CE_NAME(DrawMenuBar);                         /* aa452975 */
AKARI_CE_IMPORT BOOL  EnableMenuItem(HMENU hMenu, UINT uIDEnableItem, UINT uEnable) AKARI_CE_NAME(EnableMenuItem); /* aa453034 */
AKARI_CE_IMPORT BOOL  GetMenuItemInfo(HMENU hMenu, UINT uItem, BOOL fByPosition,
                      LPMENUITEMINFO lpmii) AKARI_CE_NAME(GetMenuItemInfo);          /* aa453134 */
AKARI_CE_IMPORT HMENU GetSubMenu(HMENU hMenu, int nPos) AKARI_CE_NAME(GetSubMenu);              /* aa453166 */
AKARI_CE_IMPORT HMENU GetSystemMenu(HWND hWnd, BOOL bRevert) AKARI_CE_NAME(GetSystemMenu);         /* aa453169 */
AKARI_CE_IMPORT BOOL  InsertMenuW(HMENU hMenu, UINT uPosition, UINT uFlags,
                  UINT uIDNewItem, LPCTSTR lpNewItem) AKARI_CE_NAME(InsertMenuW);             /* ms909853 */
#define InsertMenu InsertMenuW
AKARI_CE_IMPORT HMENU LoadMenuW(HINSTANCE hInstance, LPCTSTR lpMenuName) AKARI_CE_NAME(LoadMenuW);          /* aa453415 */
#define LoadMenu LoadMenuW
AKARI_CE_IMPORT BOOL  RemoveMenu(HMENU hMenu, UINT uPosition, UINT uFlags) AKARI_CE_NAME(RemoveMenu);        /* ms939775 */
AKARI_CE_IMPORT BOOL  SetMenuItemInfo(HMENU hMenu, UINT uItem, BOOL fByPosition,
                      LPCMENUITEMINFO lpmii) AKARI_CE_NAME(SetMenuItemInfo);        /* ms940027 */
AKARI_CE_IMPORT BOOL  TrackPopupMenu(HMENU hMenu, UINT uFlags, int x, int y,
                     int nReserved, HWND hWnd, const RECT* prcRect) AKARI_CE_NAME(TrackPopupMenu); /* aa453773 */
AKARI_CE_IMPORT BOOL  TrackPopupMenuEx(HMENU hmenu, UINT uFlags, int x, int y,     /* aa453774 */
                       HWND hwnd, LPTPMPARAMS lptpm) AKARI_CE_NAME(TrackPopupMenuEx);

/* ------------------------------------------------------------------ */
/* Dialog Boxes Reference functions.  Header Winuser.h except where    */
/* noted: MessageBox / CheckDlgButton / IsDlgButtonChecked print       */
/* Header Windows.h (windows.h); MessageBeep prints Header Winbase.h   */
/* (winbase.h).                                                        */
/* ------------------------------------------------------------------ */

HWND CreateDialogW(HINSTANCE hInstance, LPCTSTR lpTemplate,       /* ms908169 */
                   HWND hWndParent, DLGPROC lpDialogFunc);
#define CreateDialog CreateDialogW
AKARI_CE_IMPORT HWND CreateDialogIndirect(HINSTANCE hInstance,                    /* ms908170 */
                          LPCDLGTEMPLATE lpTemplate, HWND hWndParent,
                          DLGPROC lpDialogFunc) AKARI_CE_NAME(CreateDialogIndirect);
AKARI_CE_IMPORT HWND CreateDialogIndirectParam(HINSTANCE hInstance,               /* ms908171 */
                               LPCDLGTEMPLATE lpTemplate, HWND hWndParent,
                               DLGPROC lpDialogFunc, LPARAM lParamInit) AKARI_CE_NAME(CreateDialogIndirectParam);
HWND CreateDialogParamW(HINSTANCE hInstance, LPCTSTR lpTemplateName, /* ms908172 */
                        HWND hWndParent, DLGPROC lpDialogFunc,
                        LPARAM dwInitParam);
#define CreateDialogParam CreateDialogParamW
AKARI_CE_IMPORT LRESULT DefDlgProc(HWND hDlg, UINT Msg, WPARAM wParam,            /* ms908209 */
                   LPARAM lParam) AKARI_CE_NAME(DefDlgProc);
int    DialogBoxW(HINSTANCE hInstance, LPCTSTR lpTemplate,        /* aa452947 */
                  HWND hWndParent, DLGPROC lpDialogFunc);
#define DialogBox DialogBoxW
int    DialogBoxIndirect(HINSTANCE hInstance, LPDLGTEMPLATE lpTemplate, /* aa452948 */
                         HWND hWndParent, DLGPROC lpDialogFunc);
AKARI_CE_IMPORT int    DialogBoxIndirectParam(HINSTANCE hInstance,                /* aa452949 */
                              LPCDLGTEMPLATE hDialogTemplate, HWND hWndParent,
                              DLGPROC lpDialogFunc, LPARAM dwInitParam) AKARI_CE_NAME(DialogBoxIndirectParam);
int    DialogBoxParamW(HINSTANCE hInstance, LPCTSTR lpTemplateName, /* aa452950 */
                       HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam);
#define DialogBoxParam DialogBoxParamW
AKARI_CE_IMPORT BOOL   EndDialog(HWND hDlg, int nResult) AKARI_CE_NAME(EndDialog);                         /* aa453038 */
AKARI_CE_IMPORT LONG   GetDialogBaseUnits(void) AKARI_CE_NAME(GetDialogBaseUnits);                                  /* ms929231 */
AKARI_CE_IMPORT int    GetDlgCtrlID(HWND hwndCtl) AKARI_CE_NAME(GetDlgCtrlID);                                /* ms929233 */
AKARI_CE_IMPORT HWND   GetDlgItem(HWND hDlg, int nIDDlgItem) AKARI_CE_NAME(GetDlgItem);                     /* ms929234 */
AKARI_CE_IMPORT UINT   GetDlgItemInt(HWND hDlg, int nIDDlgItem, BOOL* lpTranslated,
                     BOOL bSigned) AKARI_CE_NAME(GetDlgItemInt);                               /* ms929235 */
AKARI_CE_IMPORT UINT   GetDlgItemTextW(HWND hDlg, int nIDDlgItem, LPTSTR lpString,
                       int nMaxCount) AKARI_CE_NAME(GetDlgItemTextW);                            /* ms929236 */
#define GetDlgItemText GetDlgItemTextW
AKARI_CE_IMPORT HWND   GetNextDlgGroupItem(HWND hDlg, HWND hCtl, BOOL bPrevious) AKARI_CE_NAME(GetNextDlgGroupItem);  /* aa453145 */
AKARI_CE_IMPORT HWND   GetNextDlgTabItem(HWND hDlg, HWND hCtl, BOOL bPrevious) AKARI_CE_NAME(GetNextDlgTabItem);    /* aa453146 */
AKARI_CE_IMPORT BOOL   IsDialogMessage(HWND hDlg, LPMSG lpMsg) AKARI_CE_NAME(IsDialogMessage);                   /* ms909864 */
AKARI_CE_IMPORT BOOL   MapDialogRect(HWND hDlg, LPRECT lpRect) AKARI_CE_NAME(MapDialogRect);                   /* ms911788 */
AKARI_CE_IMPORT LONG   SendDlgItemMessage(HWND hDlg, int nIDDlgItem, UINT Msg,    /* ms932717 */
                          WPARAM wParam, LPARAM lParam) AKARI_CE_NAME(SendDlgItemMessage);
AKARI_CE_IMPORT BOOL   SetDlgItemInt(HWND hDlg, int nIDDlgItem, UINT uValue,      /* ms940020 */
                     BOOL bSigned) AKARI_CE_NAME(SetDlgItemInt);
AKARI_CE_IMPORT BOOL   SetDlgItemTextW(HWND hDlg, int nIDDlgItem, LPCTSTR lpString) AKARI_CE_NAME(SetDlgItemTextW); /* ms940021 */
#define SetDlgItemText SetDlgItemTextW

/* ms909866 "IsDlgButtonChecked" and ms928573 "CheckDlgButton" are     */
/* declared in windows.h (their pages list Header Windows.h).           */

/* Buttons Reference: ms928577 "CheckRadioButton" (Header Winuser.h).   */
AKARI_CE_IMPORT BOOL CheckRadioButton(HWND hDlg, int nIDFirstButton, int nIDLastButton,
                      int nIDCheckButton) AKARI_CE_NAME(CheckRadioButton);

/* ------------------------------------------------------------------ */
/* Clipboards Reference functions (Header Winuser.h).                 */
/* ------------------------------------------------------------------ */

AKARI_CE_IMPORT BOOL   CloseClipboard(void) AKARI_CE_NAME(CloseClipboard);                       /* ms928586 */
AKARI_CE_IMPORT int    CountClipboardFormats(void) AKARI_CE_NAME(CountClipboardFormats);                /* ms908153 */
AKARI_CE_IMPORT BOOL   EmptyClipboard(void) AKARI_CE_NAME(EmptyClipboard);                       /* aa453019 */
AKARI_CE_IMPORT UINT   EnumClipboardFormats(UINT format) AKARI_CE_NAME(EnumClipboardFormats);          /* aa453047 */
AKARI_CE_IMPORT HANDLE GetClipboardData(UINT uFormat) AKARI_CE_NAME(GetClipboardData);             /* ms929215 */
AKARI_CE_IMPORT HANDLE GetClipboardDataAlloc(UINT uFormat) AKARI_CE_NAME(GetClipboardDataAlloc);        /* ms929216 */
AKARI_CE_IMPORT int    GetClipboardFormatNameW(UINT format, LPTSTR lpszFormatName,
                               int cchMaxCount) AKARI_CE_NAME(GetClipboardFormatNameW);   /* ms929217 */
#define GetClipboardFormatName GetClipboardFormatNameW
AKARI_CE_IMPORT HWND   GetClipboardOwner(void) AKARI_CE_NAME(GetClipboardOwner);                    /* ms929218 */
AKARI_CE_IMPORT HWND   GetOpenClipboardWindow(void) AKARI_CE_NAME(GetOpenClipboardWindow);               /* aa453149 */
AKARI_CE_IMPORT int    GetPriorityClipboardFormat(UINT* paFormatPriorityList,
                                  int cFormats) AKARI_CE_NAME(GetPriorityClipboardFormat);   /* aa453154 */
AKARI_CE_IMPORT BOOL   IsClipboardFormatAvailable(UINT format) AKARI_CE_NAME(IsClipboardFormatAvailable);    /* ms909863 */
AKARI_CE_IMPORT BOOL   OpenClipboard(HWND hWndNewOwner) AKARI_CE_NAME(OpenClipboard);           /* ms911905 */
AKARI_CE_IMPORT UINT   RegisterClipboardFormatW(LPCWSTR lpszFormat) AKARI_CE_NAME(RegisterClipboardFormatW); /* ms913094; the page
                                                      * states only the
                                                      * Unicode version */
#define RegisterClipboardFormat RegisterClipboardFormatW
AKARI_CE_IMPORT HANDLE SetClipboardData(UINT uFormat, HANDLE hMem) AKARI_CE_NAME(SetClipboardData); /* ms940015 */

/* ------------------------------------------------------------------ */
/* Resources Reference icon/image functions (Header Winuser.h).        */
/* ------------------------------------------------------------------ */

AKARI_CE_IMPORT HICON  CreateIconIndirect(PICONINFO piconinfo) AKARI_CE_NAME(CreateIconIndirect);     /* ms908175 */
AKARI_CE_IMPORT BOOL   DestroyIcon(HICON hIcon) AKARI_CE_NAME(DestroyIcon);                    /* aa452938 */
AKARI_CE_IMPORT BOOL   DrawIconEx(HDC hdc, int xLeft, int yTop, HICON hIcon,
                  int cxWidth, int cyWidth, UINT istepIfAniCur,
                  HBRUSH hbrFlickerFreeDraw, UINT diFlags) AKARI_CE_NAME(DrawIconEx);   /* aa452972 */
AKARI_CE_IMPORT BOOL   GetIconInfo(HICON hIcon, PICONINFO piconinfo) AKARI_CE_NAME(GetIconInfo);         /* ms929247 */
AKARI_CE_IMPORT HICON  LoadIconW(HINSTANCE hInstance, LPCTSTR lpIconName) AKARI_CE_NAME(LoadIconW);    /* aa453411 */
#define LoadIcon LoadIconW
AKARI_CE_IMPORT HANDLE LoadImageW(HINSTANCE hinst, LPCTSTR lpszName, UINT uType,
                  int cxDesired, int cyDesired, UINT fuLoad) AKARI_CE_NAME(LoadImageW);  /* aa453413 */
#define LoadImage LoadImageW

/* ------------------------------------------------------------------ */
/* System Information Reference functions (Header Winuser.h).          */
/* ------------------------------------------------------------------ */

AKARI_CE_IMPORT BOOL  EnableHardwareKeyboard(BOOL bEnable) AKARI_CE_NAME(EnableHardwareKeyboard);          /* aa453033 */
AKARI_CE_IMPORT DWORD GetSysColor(int nIndex) AKARI_CE_NAME(GetSysColor);                       /* aa453167 */
AKARI_CE_IMPORT int   GetSystemMetrics(int nIndex) AKARI_CE_NAME(GetSystemMetrics);                  /* aa453170 */
AKARI_CE_IMPORT BOOL  SystemParametersInfoW(UINT uiAction, UINT uiParam, PVOID pvParam,
                            UINT fWinIni) AKARI_CE_NAME(SystemParametersInfoW);           /* ms940383; the page
                                                      * states only the
                                                      * Unicode version */
#define SystemParametersInfo SystemParametersInfoW

/* aa453656 "SetSysColors" takes CONST COLORREF*, and COLORREF is
 * defined with the GDI types in wingdi.h -- see wingdi.h for the
 * declaration (its official page prints Header Winuser.h). */

/* ------------------------------------------------------------------ */
/* WM_COPYDATA support: aa453921 "WM_COPYDATA (Windows CE 5.0)" types */
/* lParam with a pointer to a COPYDATASTRUCT (pcds) but the CE GWES   */
/* books publish no structure leaf for it; the fixed layout is taken  */
/* from Microsoft's official Win32 *COPYDATASTRUCT* structure         */
/* reference (winuser.h, learn.microsoft.com) -- a fixed-ABI record   */
/* (same policy as HARDWAREINPUT / CRITICAL_SECTION).                  */
/* ------------------------------------------------------------------ */
typedef struct tagCOPYDATASTRUCT {
    ULONG_PTR dwData;   /* application-defined data type tag */
    DWORD     cbData;   /* size, in bytes, of lpData */
    PVOID     lpData;   /* data to pass; can be NULL */
} COPYDATASTRUCT, *PCOPYDATASTRUCT;

/* ------------------------------------------------------------------ */
/* M50: NMHDR (ms931479, Windows CE 1.0 and later; Header Winuser.h):  */
/* the notification header carried by the lParam of WM_NOTIFY          */
/* (aa453890 types it LPNMHDR; the NMN_* New-button notifications of   */
/* newmenu.h and the WM_NOTIFY-based common-control notifications      */
/* embed it as the first member of their structures).  The page also   */
/* lists the NM_RCLICK / NM_RDBCLICK (sic -- page spelling) common     */
/* notification-code names "if you include mouse support in your       */
/* device platform" without values; they belong to the unharvested     */
/* Common Controls notifications book and are held in                  */
/* docs/inventory.md.                                                  */
/* ------------------------------------------------------------------ */
typedef struct tagNMHDR {
    HWND hwndFrom;   /* window handle of the control sending the message */
    UINT idFrom;     /* identifier of the control sending the message */
    UINT code;       /* notification code */
} NMHDR, *LPNMHDR;

/* ------------------------------------------------------------------ */
/* M29: window/control message identifiers and notification codes.   */
/*                                                                     */
/* Names and semantics come from the CE 5.0 GWES message books (each  */
/* name carries its official (v=msdn.10) page id; notification-code   */
/* pages belong to the owning control message book).  Windows CE GWES */
/* implements the standard Win32 message protocol: the CE pages       */
/* document each name, wParam and lParam without republishing the     */
/* numeric identifier, so the numeric values are the fixed Win32 ABI  */
/* message numbers (the same fixed-ABI policy as the SIF / SB / SW    */
/* value macros above).  WM_USER (0x0400) is the base of the          */
/* application-defined message range.                                 */
/* ------------------------------------------------------------------ */
#define WM_USER 0x0400

/* --- GDI Messages --- */
#define WM_PAINT                       0x000F         /* aa453891 */
#define WM_SETREDRAW                   0x000B         /* aa453904 */
#define WM_SYSCOLORCHANGE              0x0015         /* aa453910 */
#define WM_QUERYNEWPALETTE             0x030F         /* aa453894 */
#define WM_PALETTECHANGED              0x0311         /* aa453892 */

/* --- Windows Messages --- */
#define WM_CANCELMODE                  0x001F         /* ms914108 */
#define WM_CLOSE                       0x0010         /* ms914114 */
#define WM_CREATE                      0x0001         /* ms914118 */
#define WM_DESTROY                     0x0002         /* aa453854 */
#define WM_ENABLE                      0x000A         /* aa453856 */
#define WM_ERASEBKGND                  0x0014         /* aa453858 */
#define WM_GETTEXT                     0x000D         /* aa453864 */
#define WM_GETTEXTLENGTH               0x000E         /* aa453865 */
#define WM_MOVE                        0x0003         /* aa453887 */
#define WM_NOTIFY                      0x004E         /* aa453890 */
#define WM_QUIT                        0x0012         /* aa453895 */
#define WM_SETTEXT                     0x000C         /* aa453905 */
#define WM_SETTINGCHANGE               0x001A         /* aa453906 */
#define WM_SIZE                        0x0005         /* aa453907 */
#define WM_STYLECHANGED                0x007D         /* aa453908 */
#define WM_WINDOWPOSCHANGED            0x0047         /* aa453920 */

/* --- Keyboard Messages --- */
#define WM_ACTIVATE                    0x0006         /* ms914105 */
#define WM_CHAR                        0x0102         /* ms914110 */
#define WM_HOTKEY                      0x0312         /* aa453868 */
#define WM_INITMENUPOPUP               0x0117         /* aa453872 */
#define WM_KEYDOWN                     0x0100         /* aa453873 */
#define WM_KEYUP                       0x0101         /* aa453876 */
#define WM_KILLFOCUS                   0x0008         /* aa453877 */
#define WM_MENUCHAR                    0x0120         /* aa453884 */
#define WM_SETFOCUS                    0x0007         /* aa453901 */
#define WM_SYSCHAR                     0x0106         /* aa453909 */
#define WM_SYSCOMMAND                  0x0112         /* aa453911 */
#define WM_SYSDEADCHAR                 0x0107         /* aa453913 */
#define WM_SYSKEYDOWN                  0x0104         /* aa453914 */
#define WM_SYSKEYUP                    0x0105         /* aa453915 */

/* --- Buttons Messages --- */
#define BM_CLICK                       0x00F5         /* aa452890 */
#define BM_GETCHECK                    0x00F0         /* aa452891 */
#define BM_GETSTATE                    0x00F2         /* aa452892 */
#define BM_SETCHECK                    0x00F1         /* aa452893 */
#define BM_SETSTATE                    0x00F3         /* aa452894 */
#define BM_SETSTYLE                    0x00F4         /* aa452895 */
#define BN_CLICKED                     0              /* aa452896 */
#define BN_KILLFOCUS                   7              /* aa452897 */
#define BN_SETFOCUS                    6              /* aa452898 */
#define WM_CTLCOLORBTN                 0x0135         /* ms914119 */

/* --- Static Controls Messages --- */
#define STM_SETIMAGE                   0x0172         /* ms940367 */
#define STM_GETIMAGE                   0x0173         /* ms940366 */
#define STN_CLICKED                    0              /* ms940368 */
#define STN_ENABLE                     2              /* ms940370 */
#define STN_DISABLE                    3              /* ms940369 */
#define WM_CTLCOLORSTATIC              0x0138         /* aa453851 */

/* --- Menus Messages --- */
#define WM_COMMAND                     0x0111         /* ms914115 */
#define WM_CONTEXTMENU                 0x007B         /* ms914116 */
#define WM_ENTERMENULOOP               0x0211         /* aa453857 */
#define WM_EXITMENULOOP                0x0212         /* aa453859 */

/* --- Dialog Boxes Messages --- */
#define DM_GETDEFID                    (WM_USER + 0)   /* aa452962 */
#define DM_SETDEFID                    (WM_USER + 1)   /* aa452963 */
#define WM_CTLCOLORDLG                 0x0136         /* aa453847 */
#define WM_GETDLGCODE                  0x0087         /* aa453861 */
#define WM_INITDIALOG                  0x0110         /* aa453871 */
#define WM_NEXTDLGCTL                  0x0028         /* aa453889 */

/* --- Clipboards Messages --- */
#define WM_CLEAR                       0x0303         /* ms914113 */
#define WM_COPY                        0x0301         /* ms914117 */
#define WM_CUT                         0x0300         /* aa453852 */
#define WM_PASTE                       0x0302         /* aa453893 */
#define WM_RENDERALLFORMATS            0x0306         /* aa453898 */
#define WM_RENDERFORMAT                0x0305         /* aa453899 */
#define WM_UNDO                        0x0304         /* aa453917 */

/* --- Combo Boxes Messages --- */
#define CB_GETEDITSEL                  0x0140         /* ms928352 */
#define CB_LIMITTEXT                   0x0141         /* ms908045 */
#define CB_SETEDITSEL                  0x0142         /* ms908063 */
#define CB_ADDSTRING                   0x0143         /* aa452924 */
#define CB_DELETESTRING                0x0144         /* aa452925 */
#define CB_GETCOUNT                    0x0146         /* ms939290 */
#define CB_GETCURSEL                   0x0147         /* ms939382 */
#define CB_GETLBTEXT                   0x0148         /* ms928386 */
#define CB_GETLBTEXTLEN                0x0149         /* ms928395 */
#define CB_INSERTSTRING                0x014A         /* ms908036 */
#define CB_RESETCONTENT                0x014B         /* ms908059 */
#define CB_FINDSTRING                  0x014C         /* aa452926 */
#define CB_SELECTSTRING                0x014D         /* ms908060 */
#define CB_SETCURSEL                   0x014E         /* ms908061 */
#define CB_SHOWDROPDOWN                0x014F         /* ms908070 */
#define CB_GETITEMDATA                 0x0150         /* ms928374 */
#define CB_SETITEMDATA                 0x0151         /* ms908066 */
#define CB_GETDROPPEDCONTROLRECT       0x0152         /* ms928334 */
#define CB_SETITEMHEIGHT               0x0153         /* ms908067 */
#define CB_GETITEMHEIGHT               0x0154         /* ms928376 */
#define CB_SETEXTENDEDUI               0x0155         /* ms908064 */
#define CB_GETEXTENDEDUI               0x0156         /* ms928359 */
#define CB_GETDROPPEDSTATE             0x0157         /* ms928340 */
#define CB_FINDSTRINGEXACT             0x0158         /* aa452927 */
#define CB_SETLOCALE                   0x0159         /* ms908068 */
#define CB_GETLOCALE                   0x015A         /* ms907898 */
#define CB_GETTOPINDEX                 0x015B         /* ms907963 */
#define CB_SETTOPINDEX                 0x015C         /* ms908069 */
#define CB_GETHORIZONTALEXTENT         0x015D         /* ms928366 */
#define CB_SETHORIZONTALEXTENT         0x015E         /* ms908065 */
#define CB_GETDROPPEDWIDTH             0x015F         /* ms928343 */
#define CB_SETDROPPEDWIDTH             0x0160         /* ms908062 */
#define CB_INITSTORAGE                 0x0161         /* ms908027 */
#define CB_GETCOMBOBOXINFO             0x0164         /* aa452928 */
#define CBN_ERRSPACE                   -1           
#define CBN_SELCHANGE                  0x0001       
#define CBN_DBLCLK                     0x0002       
#define CBN_SETFOCUS                   0x0003       
#define CBN_KILLFOCUS                  0x0004       
#define CBN_EDITCHANGE                 0x0005       
#define CBN_EDITUPDATE                 0x0006       
#define CBN_DROPDOWN                   0x0007       
#define CBN_CLOSEUP                    0x0008       
#define CBN_SELENDOK                   0x0009       
#define CBN_SELENDCANCEL               0x000A       

/* --- List Boxes Messages --- */
#define LB_ADDSTRING                   0x0180         /* aa453251 */
#define LB_INSERTSTRING                0x0181         /* aa453271 */
#define LB_DELETESTRING                0x0182         /* aa453252 */
#define LB_SELITEMRANGEEX              0x0183         /* aa453282 */
#define LB_RESETCONTENT                0x0184         /* aa453279 */
#define LB_SETSEL                      0x0185         /* aa453291 */
#define LB_SETCURSEL                   0x0186         /* aa453286 */
#define LB_GETSEL                      0x0187         /* aa453264 */
#define LB_GETCURSEL                   0x0188         /* aa453258 */
#define LB_GETTEXT                     0x0189         /* aa453267 */
#define LB_GETTEXTLEN                  0x018A         /* aa453268 */
#define LB_GETCOUNT                    0x018B         /* aa453257 */
#define LB_SELECTSTRING                0x018C         /* aa453280 */
#define LB_GETTOPINDEX                 0x018E         /* aa453269 */
#define LB_FINDSTRING                  0x018F         /* aa453253 */
#define LB_GETSELCOUNT                 0x0190         /* aa453265 */
#define LB_GETSELITEMS                 0x0191         /* aa453266 */
#define LB_SETTABSTOPS                 0x0192         /* aa453292 */
#define LB_GETHORIZONTALEXTENT         0x0193         /* aa453259 */
#define LB_SETHORIZONTALEXTENT         0x0194         /* aa453287 */
#define LB_SETCOLUMNWIDTH              0x0195         /* aa453285 */
#define LB_SETTOPINDEX                 0x0197         /* aa453293 */
#define LB_GETITEMRECT                 0x0198         /* aa453262 */
#define LB_GETITEMDATA                 0x0199         /* aa453260 */
#define LB_SETITEMDATA                 0x019A         /* aa453288 */
#define LB_SELITEMRANGE                0x019B         /* aa453281 */
#define LB_SETANCHORINDEX              0x019C         /* aa453283 */
#define LB_GETANCHORINDEX              0x019D         /* aa453255 */
#define LB_SETCARETINDEX               0x019E         /* aa453284 */
#define LB_GETCARETINDEX               0x019F         /* aa453256 */
#define LB_SETITEMHEIGHT               0x01A0         /* aa453289 */
#define LB_GETITEMHEIGHT               0x01A1         /* aa453261 */
#define LB_FINDSTRINGEXACT             0x01A2         /* aa453254 */
#define LB_SETLOCALE                   0x01A5         /* aa453290 */
#define LB_GETLOCALE                   0x01A6         /* aa453263 */
#define LB_INITSTORAGE                 0x01A8         /* aa453270 */
#define LB_ITEMFROMPOINT               0x01A9         /* aa453272 */
#define LBN_ERRSPACE                   -2           
#define LBN_SELCHANGE                  0x0001       
#define LBN_DBLCLK                     0x0002       
#define LBN_SELCANCEL                  0x0003       
#define LBN_SETFOCUS                   0x0004       
#define LBN_KILLFOCUS                  0x0005       
#define WM_CTLCOLORLISTBOX             0x0134         /* aa453849 */
#define WM_DRAWITEM                    0x002B         /* aa453855 */
#define WM_DELETEITEM                  0x002D         /* aa453853 */

/* --- Edit Boxes Messages --- */
#define EM_GETSEL                      0x00B0         /* aa453012 */
#define EM_SETSEL                      0x00B1         /* aa453030 */
#define EM_GETRECT                     0x00B2         /* aa453011 */
#define EM_SETRECT                     0x00B3         /* aa453028 */
#define EM_SETRECTNP                   0x00B4         /* aa453029 */
#define EM_SCROLL                      0x00B5         /* aa453021 */
#define EM_LINESCROLL                  0x00B6         /* aa453017 */
#define EM_SCROLLCARET                 0x00B7         /* aa453022 */
#define EM_GETMODIFY                   0x00B8         /* aa453009 */
#define EM_SETMODIFY                   0x00B9         /* aa453025 */
#define EM_GETLINECOUNT                0x00BA         /* aa453007 */
#define EM_LINEINDEX                   0x00BB         /* aa453015 */
#define EM_LINELENGTH                  0x00BF         /* aa453016 */
#define EM_REPLACESEL                  0x00C2         /* aa453020 */
#define EM_GETLINE                     0x00C4         /* aa453006 */
#define EM_LIMITTEXT                   0x00C5         /* aa453013 */
#define EM_CANUNDO                     0x00C6         /* aa452998 */
#define EM_UNDO                        0x00C7         /* aa453032 */
#define EM_FMTLINES                    0x00C8         /* aa453003 */
#define EM_LINEFROMCHAR                0x00C9         /* aa453014 */
#define EM_SETTABSTOPS                 0x00CB         /* aa453031 */
#define EM_SETPASSWORDCHAR             0x00CC         /* aa453026 */
#define EM_EMPTYUNDOBUFFER             0x00CD         /* aa453002 */
#define EM_GETFIRSTVISIBLELINE         0x00CE         /* aa453004 */
#define EM_SETREADONLY                 0x00CF         /* aa453027 */
#define EM_GETPASSWORDCHAR             0x00D2         /* aa453010 */
#define EM_SETMARGINS                  0x00D3         /* aa453024 */
#define EM_GETMARGINS                  0x00D4         /* aa453008 */
#define EM_SETLIMITTEXT                0x00C5         /* aa453023: identical to EM_LIMITTEXT (aa453013) */
#define EM_GETLIMITTEXT                0x00D5         /* aa453005 */
#define EM_POSFROMCHAR                 0x00D6         /* aa453018 */
#define EM_CHARFROMPOS                 0x00D7         /* aa453001 */
#define EN_SETFOCUS                  0x0100         /* aa453046 */
#define EN_KILLFOCUS                 0x0200         /* aa453044 */
#define EN_CHANGE                    0x0300         /* aa453036 */
#define EN_UPDATE                    0x0400         /* aa453053 */
#define EN_ERRSPACE                  0x0500         /* aa453042 */
#define EN_MAXTEXT                   0x0501         /* aa453045 */
#define EN_HSCROLL                   0x0601         /* aa453043 */
#define EN_VSCROLL                   0x0602         /* aa453054 */
#define WM_CTLCOLOREDIT                0x0133         /* aa453848 */
#define WM_MEASUREITEM                 0x002C         /* aa453883 */
#define WM_COPYDATA                    0x004A         /* aa453921 */

/* ------------------------------------------------------------------ */
/* M35: GWES window and control style bits.                            */
/*                                                                     */
/* Name list and CE-supported set come from the official CE 5.0 GWES   */
/* style pages (CE 6.0 twins are listed in parentheses): Basic Window  */
/* Styles aa452869 (ee504355), Non-client Area Styles ms911872         */
/* (ee506097), Message Box Styles ms911829 (ee502245), the button      */
/* style pages aa453604/ms928572/aa453607 (ee501475/ee504569/ee505912), */
/* Edit Control Styles aa452995 (ee504833), List Box Styles aa453299   */
/* (ee501958), Combo Box Styles ms908112 (ee501099), Scroll Bar Styles */
/* ms932612 (ee505682), Static Control Styles ms940359 (ee505845).     */
/*                                                                     */
/* The CE pages document each style name and meaning but do not        */
/* republish the numeric value; Windows CE GWES implements the         */
/* standard Win32 style ABI, so the numeric values are the fixed       */
/* Win32 ABI style bits (same fixed-ABI policy as the message-         */
/* identifier block above).  CE-only styles whose numeric value the    */
/* CE pages do not publish are recorded but intentionally not          */
/* defined here: WS_NONAVDONEBUTTON, WS_EX_NOANIMATION, WS_EX_NODRAG,  */
/* WS_EX_CAPTIONOKBTN.                                                 */
/* ------------------------------------------------------------------ */

/* --- Window styles (aa452869/ee504355 + ms911872/ee506097) --- */
#define WS_OVERLAPPED               0x00000000
#define WS_POPUP                    0x80000000
#define WS_CHILD                    0x40000000
#define WS_VISIBLE                  0x10000000
#define WS_DISABLED                 0x08000000
#define WS_CLIPSIBLINGS             0x04000000
#define WS_CLIPCHILDREN             0x02000000
#define WS_CAPTION                  0x00C00000
#define WS_BORDER                   0x00800000
#define WS_DLGFRAME                 0x00400000
#define WS_VSCROLL                  0x00200000
#define WS_HSCROLL                  0x00100000
#define WS_SYSMENU                  0x00080000
#define WS_SIZEBOX                  0x00040000
#define WS_GROUP                    0x00020000
#define WS_TABSTOP                  0x00010000

/* --- Extended window styles (aa452869/ee504355 + ms911872/ee506097).
 * The page documents WS_EX_OVERLAPPEDWINDOW as the combination of
 * WS_EX_CLIENTEDGE and WS_EX_WINDOWEDGE. --- */
#define WS_EX_DLGMODALFRAME         0x00000001
#define WS_EX_TOPMOST               0x00000008
#define WS_EX_WINDOWEDGE            0x00000100
#define WS_EX_CLIENTEDGE            0x00000200
#define WS_EX_CONTEXTHELP           0x00000400
#define WS_EX_STATICEDGE            0x00020000
#define WS_EX_NOACTIVATE            0x08000000
#define WS_EX_OVERLAPPEDWINDOW      (WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE)

/* --- Message box styles (ms911829/ee502245) --- */
#define MB_OK                       0x0000
#define MB_OKCANCEL                 0x0001
#define MB_ABORTRETRYIGNORE         0x0002
#define MB_YESNOCANCEL              0x0003
#define MB_YESNO                    0x0004
#define MB_RETRYCANCEL              0x0005
#define MB_ICONHAND                 0x0010
#define MB_ICONQUESTION             0x0020
#define MB_ICONEXCLAMATION          0x0030
#define MB_ICONASTERISK             0x0040
#define MB_APPLMODAL                0x0000
#define MB_DEFBUTTON1               0x0000
#define MB_DEFBUTTON2               0x0100
#define MB_DEFBUTTON3               0x0200
#define MB_SETFOREGROUND            0x00010000
#define MB_TOPMOST                  0x00040000
/* aliases the CE page lists in the same cells (same value) */
#define MB_ICONERROR                MB_ICONHAND
#define MB_ICONSTOP                 MB_ICONHAND
#define MB_ICONWARNING              MB_ICONEXCLAMATION
#define MB_ICONINFORMATION          MB_ICONASTERISK

/* --- Button styles: push aa453604/ee501475, check ms928572/ee504569,
 * radio aa453607/ee505912 (the pages also list WS_TABSTOP, which is a
 * window style). --- */
#define BS_PUSHBUTTON               0x0000
#define BS_DEFPUSHBUTTON            0x0001
#define BS_CHECKBOX                 0x0002
#define BS_AUTOCHECKBOX             0x0003
#define BS_RADIOBUTTON              0x0004
#define BS_3STATE                   0x0005
#define BS_AUTO3STATE               0x0006
#define BS_AUTORADIOBUTTON          0x0009
#define BS_OWNERDRAW                0x000B
#define BS_RIGHTBUTTON              0x0020   /* == BS_LEFTTEXT on desktop */
#define BS_LEFT                     0x0100
#define BS_RIGHT                    0x0200
#define BS_CENTER                   0x0300
#define BS_TOP                      0x0400
#define BS_BOTTOM                   0x0800
#define BS_VCENTER                  0x0C00
#define BS_PUSHLIKE                 0x1000
#define BS_NOTIFY                   0x4000

/* --- Edit control styles (aa452995/ee504833) --- */
#define ES_LEFT                     0x0000
#define ES_CENTER                   0x0001
#define ES_RIGHT                    0x0002
#define ES_MULTILINE                0x0004
#define ES_UPPERCASE                0x0008
#define ES_LOWERCASE                0x0010
#define ES_PASSWORD                 0x0020
#define ES_AUTOVSCROLL              0x0040
#define ES_AUTOHSCROLL              0x0080
#define ES_NOHIDESEL                0x0100
#define ES_OEMCONVERT               0x0400
#define ES_READONLY                 0x0800
#define ES_WANTRETURN               0x1000
#define ES_NUMBER                   0x2000

/* --- List box styles (aa453299/ee501958); LBS_STANDARD is documented
 * as the combination of LBS_NOTIFY and LBS_SORT. --- */
#define LBS_NOTIFY                  0x0001
#define LBS_SORT                    0x0002
#define LBS_NOREDRAW                0x0004
#define LBS_MULTIPLESEL             0x0008
#define LBS_OWNERDRAWFIXED          0x0010
#define LBS_OWNERDRAWVARIABLE       0x0020
#define LBS_HASSTRINGS              0x0040
#define LBS_USETABSTOPS             0x0080
#define LBS_NOINTEGRALHEIGHT        0x0100
#define LBS_MULTICOLUMN             0x0200
#define LBS_WANTKEYBOARDINPUT       0x0400
#define LBS_EXTENDEDSEL             0x0800
#define LBS_DISABLENOSCROLL         0x1000
#define LBS_NOSEL                   0x4000
#define LBS_STANDARD                (LBS_NOTIFY | LBS_SORT)

/* --- Combo box styles (ms908112/ee501099) --- */
#define CBS_DROPDOWN                0x0002
#define CBS_DROPDOWNLIST            0x0003
#define CBS_AUTOHSCROLL             0x0040
#define CBS_OEMCONVERT              0x0080
#define CBS_SORT                    0x0100
#define CBS_HASSTRINGS              0x0200
#define CBS_NOINTEGRALHEIGHT        0x0400
#define CBS_DISABLENOSCROLL         0x0800
#define CBS_UPPERCASE               0x2000
#define CBS_LOWERCASE               0x4000

/* --- Scroll bar styles (ms932612/ee505682) --- */
#define SBS_HORZ                    0x0000
#define SBS_VERT                    0x0001

/* --- Static control styles (ms940359/ee505845) --- */
#define SS_LEFT                     0x0000
#define SS_CENTER                   0x0001
#define SS_RIGHT                    0x0002
#define SS_ICON                     0x0003
#define SS_LEFTNOWORDWRAP           0x000C
#define SS_BITMAP                   0x000E
#define SS_NOPREFIX                 0x0080
#define SS_NOTIFY                   0x0100
#define SS_CENTERIMAGE              0x0200

/* --- Dialog box styles (the DLGTEMPLATE aa452960 / DLGTEMPLATEEX
 * aa452961 pages document which DS_* style may be combined into a
 * dialog template; values are the fixed Win32 ABI style bits). --- */
#define DS_ABSALIGN                 0x0001
#define DS_SYSMODAL                 0x0002
#define DS_3DLOOK                   0x0004
#define DS_FIXEDSYS                 0x0008
#define DS_NOFAILCREATE             0x0010
#define DS_LOCALEDIT                0x0020
#define DS_SETFONT                  0x0040
#define DS_MODALFRAME               0x0080
#define DS_NOIDLEMSG                0x0100
#define DS_SETFOREGROUND            0x0200
#define DS_CONTROL                  0x0400
#define DS_CENTER                   0x0800
#define DS_CENTERMOUSE              0x1000
#define DS_CONTEXTHELP              0x2000

/* --- Image-type constants for LoadImage / ImageList_LoadImage uType --- */
#define IMAGE_BITMAP                   0            
#define IMAGE_ICON                     1            
#define IMAGE_CURSOR                   2            

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WINUSER_H */
