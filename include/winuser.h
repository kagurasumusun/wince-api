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

BOOL CreateCaret(HWND hWnd, HBITMAP hBitmap, int nWidth,  /* ms908164 */
                 int nHeight);
BOOL DestroyCaret(void);                                  /* aa452936 */
UINT GetCaretBlinkTime(void);                             /* ms929209 */
BOOL GetCaretPos(LPPOINT lpPoint);                        /* ms929210 */
BOOL HideCaret(HWND hWnd);                                /* ms929930 */
BOOL SetCaretBlinkTime(UINT uMSeconds);                   /* ms940012 */
BOOL SetCaretPos(int X, int Y);                           /* ms940013 */
BOOL ShowCaret(HWND hWnd);                                /* aa453729 */

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

BOOL GetMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin,    /* aa453135 */
                 UINT wMsgFilterMax);
BOOL PeekMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin,   /* ms911928 */
                  UINT wMsgFilterMax, UINT wRemoveMsg);

/* aa452956 "DispatchMessage": dispatches to the window procedure.  The
 * page prints LONG as the return type. */
LONG DispatchMessage(const MSG *lpmsg);

/* aa453776 "TranslateMessage": translates virtual-key messages into
 * character messages. */
BOOL TranslateMessage(const MSG *lpMsg);

/* ms911937 "PostMessage" / ms911939 "PostThreadMessage" /
 * ms939980 "SendMessage" / ms939983 "SendNotifyMessage". */
BOOL PostMessage(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL PostThreadMessage(DWORD idThread, UINT Msg, WPARAM wParam,
                        LPARAM lParam);
LRESULT SendMessage(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL SendNotifyMessage(HWND hWnd, UINT Msg, WPARAM wParam,
                        LPARAM lParam);

/* ms911938 "PostQuitMessage": posts WM_QUIT (wParam = nExitCode). */
void PostQuitMessage(int nExitCode);

/* ms939737 "RegisterWindowMessage": registers a unique message number
 * for the given string.  CE 2.0+. */
UINT RegisterWindowMessageW(LPCTSTR lpString);
#define RegisterWindowMessage RegisterWindowMessageW

/* aa453136 "GetMessagePos": cursor position packed into a DWORD
 * (x = low word, y = high word) at the last message read. */
DWORD GetMessagePos(void);

/* aa453137 "GetMessageQueueReadyTimeStamp": the page prints Header:
 * Windows.h, so it is declared in windows.h. */

/* aa453138 "GetMessageSource": returns a value identifying the source
 * of the current message. */
UINT GetMessageSource(void);

/* aa453156 "GetQueueStatus": returns the QS_* queue-status flags of
 * the calling thread's queue (CE .NET 4.2+). */
DWORD GetQueueStatus(UINT flags);

/* ms909852 "InSendMessage": TRUE while processing a sent message. */
BOOL InSendMessage(VOID);

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

SHORT GetKeyState(int nVirtKey);                       /* aa453132 */
SHORT GetAsyncKeyState(int vKey);                      /* ms929204 */
HWND  GetFocus(void);                                  /* ms929240 */
HWND  SetFocus(HWND hWnd);                             /* ms940023 */
HWND  GetActiveWindow(void);                           /* ms929203 */
HWND  SetActiveWindow(HWND hWnd);                      /* ms939986 */
BOOL  EnableWindow(HWND hWnd, BOOL bEnable);           /* aa453035 */
BOOL  IsWindowEnabled(HWND hWnd);                      /* aa453234 */

/* Keyboard layout (HKL). */
HKL   ActivateKeyboardLayout(HKL hkl, UINT Flags);     /* aa452845 */
HKL   GetKeyboardLayout(DWORD idThread);               /* ms929249 */
UINT  GetKeyboardLayoutList(int nBuff, HKL *lpList);   /* ms929250 */
BOOL  GetKeyboardLayoutNameW(LPTSTR pwszKLID);         /* ms929252 */
#define GetKeyboardLayoutName GetKeyboardLayoutNameW
DWORD GetKeyboardStatus(VOID);                         /* ms929253 */
int   GetKeyboardType(int nTypeFlag);                  /* ms929254 */

/* ms911789 "MapVirtualKey". */
UINT MapVirtualKey(UINT uCode, UINT uMapType);

/* keybd_event (aa453245): synthesizes a keystroke; dwFlags is
 * KEYEVENTF_EXTENDEDKEY / KEYEVENTF_KEYUP. */
VOID keybd_event(BYTE bVk, BYTE bScan, DWORD dwFlags, DWORD dwExtraInfo);

/* LoadKeyboardLayout (aa453414): the page's signature takes LPCSTR
 * pwszKLID (a layout identifier string). */
HKL LoadKeyboardLayout(LPCSTR pwszKLID, UINT Flags);

/* Hot keys (CE 2.0+). */
BOOL RegisterHotKey(HWND hWnd, int id, UINT fsModifiers, UINT vk);
BOOL UnregisterHotKey(HWND hWnd, int id);

/* Accelerator tables (CE 1.0+; Link Library Accel.lib). */
HACCEL CreateAcceleratorTable(LPACCEL lpaccl, int cEntries); /* ms908162 */
HACCEL LoadAcceleratorsW(HINSTANCE hInstance,                /* aa453407 */
                         LPCTSTR lpTableName);
#define LoadAccelerators LoadAcceleratorsW
BOOL   DestroyAcceleratorTable(HACCEL hAccel);              /* aa452935 */
int    TranslateAccelerator(HWND hWnd, HACCEL hAccTable,    /* aa453775 */
                            LPMSG lpMsg);

/* ms932719 "SendInput": synthesizes mouse/keyboard/hardware input. */
UINT SendInput(UINT nInputs, LPINPUT pInputs, int cbSize);

/* ------------------------------------------------------------------ */
/* Scroll Bars Reference functions (Header: Winuser.h).              */
/* ------------------------------------------------------------------ */

BOOL GetScrollInfo(HWND hwnd, int fnBar, LPSCROLLINFO lpsi); /* aa453163 */
int  SetScrollInfo(HWND hwnd, int fnBar, LPSCROLLINFO lpsi,  /* aa453652 */
                   BOOL fRedraw);
int  SetScrollPos(HWND hWnd, int nBar, int nPos, BOOL bRedraw); /* aa453653 */
BOOL SetScrollRange(HWND hWnd, int nBar, int nMinPos,          /* aa453654 */
                    int nMaxPos, BOOL bRedraw);
int  ScrollWindowEx(HWND hWnd, int dx, int dy,                 /* ms932713 */
                    const RECT *prcScroll, const RECT *prcClip,
                    HRGN hrgnUpdate, LPRECT prcUpdate, UINT flags);

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
HDC BeginPaint(HWND hwnd, LPPAINTSTRUCT lpPaint);
/* ms928584 "ClientToScreen" */
BOOL ClientToScreen(HWND hWnd, LPPOINT lpPoint);
/* ms908152 "CopyRect" */
BOOL CopyRect(LPRECT lprcDst, const RECT* lprcSrc);
/* aa452970 "DrawFrameControl" */
BOOL DrawFrameControl(HDC hdc, LPRECT lprc, UINT uType, UINT uState);
/* aa453041 "EndPaint" */
BOOL EndPaint(HWND hWnd, CONST PAINTSTRUCT* lpPaint);
/* aa453055 "EqualRect" */
BOOL EqualRect(const RECT* lprc1, const RECT* lprc2);
/* ms929227 "GetDC" */
HDC GetDC(HWND hWnd);
/* ms929228 "GetDCEx" */
HDC GetDCEx(HWND hWnd, HRGN hrgnClip, DWORD flags);
/* aa453174 "GetUpdateRect" */
BOOL GetUpdateRect(HWND hWnd, LPRECT lpRect, BOOL bErase);
/* aa453175 "GetUpdateRgn" */
int GetUpdateRgn(HWND hWnd, HRGN hRgn, BOOL bErase);
/* aa453179 "GetWindowDC" */
HDC GetWindowDC(HWND hWnd);
/* aa453182 "GetWindowRgn" */
int GetWindowRgn(HWND hWnd, HRGN hRgn);
/* ms909856 "IntersectRect" */
BOOL IntersectRect(LPRECT lprcDst, const RECT* lprcSrc1,
    const RECT* lprcSrc2);
/* ms909857 "InvalidateRect" */
BOOL InvalidateRect(HWND hWnd, const RECT* lpRect, BOOL bErase);
/* ms909894 "IsRectEmpty" */
BOOL IsRectEmpty(const RECT* lprc);
/* aa453409 "LoadBitmap" */
HBITMAP LoadBitmap(HINSTANCE hInstance, LPCTSTR lpBitmapName);
/* ms911790 "MapWindowPoints" */
int MapWindowPoints(HWND hWndFrom, HWND hWndTo, LPPOINT lpPoints,
    UINT cPoints);
/* ms911891 "OffsetRect" */
BOOL OffsetRect(LPRECT lprc, int dx, int dy);
/* aa453601 "PtInRect" */
BOOL PtInRect(const RECT* lprc, POINT pt);
/* ms939760 "ReleaseDC" */
int ReleaseDC(HWND hWnd, HDC hDC);
/* ms932582 "ScreenToClient" */
BOOL ScreenToClient(HWND hWnd, LPPOINT lpPoint);
/* aa453649 "SetRectEmpty" */
BOOL SetRectEmpty(LPRECT lprc);
/* aa453663 "SetWindowRgn" */
int SetWindowRgn(HWND hWnd, HRGN hRgn, BOOL bRedraw);
/* ms940381 "SubtractRect" */
BOOL SubtractRect(LPRECT lprcDst, const RECT* lprcSrc1, const RECT* lprcSrc2);
/* ms914081 "UnionRect" */
BOOL UnionRect(LPRECT lprcDst, const RECT* lprcSrc1, const RECT* lprcSrc2);
/* ms914085 "UpdateWindow" */
BOOL UpdateWindow(HWND hWnd);
/* ms914091 "ValidateRect" */
BOOL ValidateRect(HWND hWnd, const RECT* lpRect);

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
BOOL  CheckMenuItem(HMENU hmenu, UINT uIDCheckItem, UINT uCheck); /* ms928575 */
BOOL  CheckMenuRadioItem(HMENU hmenu, UINT idFirst, UINT idLast,  /* ms928576 */
                         UINT idCheck, UINT uFlags);
HMENU CreateMenu(void);                               /* ms908177 */
HMENU CreatePopupMenu(void);                          /* ms908182 */
BOOL  DeleteMenu(HMENU hMenu, UINT uPosition, UINT uFlags);       /* aa452932 */
BOOL  DestroyMenu(HMENU hMenu);                       /* aa452940 */
BOOL  DrawMenuBar(HWND hWnd);                         /* aa452975 */
BOOL  EnableMenuItem(HMENU hMenu, UINT uIDEnableItem, UINT uEnable); /* aa453034 */
BOOL  GetMenuItemInfo(HMENU hMenu, UINT uItem, BOOL fByPosition,
                      LPMENUITEMINFO lpmii);          /* aa453134 */
HMENU GetSubMenu(HMENU hMenu, int nPos);              /* aa453166 */
HMENU GetSystemMenu(HWND hWnd, BOOL bRevert);         /* aa453169 */
BOOL  InsertMenuW(HMENU hMenu, UINT uPosition, UINT uFlags,
                  UINT uIDNewItem, LPCTSTR lpNewItem);             /* ms909853 */
#define InsertMenu InsertMenuW
HMENU LoadMenuW(HINSTANCE hInstance, LPCTSTR lpMenuName);          /* aa453415 */
#define LoadMenu LoadMenuW
BOOL  RemoveMenu(HMENU hMenu, UINT uPosition, UINT uFlags);        /* ms939775 */
BOOL  SetMenuItemInfo(HMENU hMenu, UINT uItem, BOOL fByPosition,
                      LPCMENUITEMINFO lpmii);        /* ms940027 */
BOOL  TrackPopupMenu(HMENU hMenu, UINT uFlags, int x, int y,
                     int nReserved, HWND hWnd, const RECT* prcRect); /* aa453773 */
BOOL  TrackPopupMenuEx(HMENU hmenu, UINT uFlags, int x, int y,     /* aa453774 */
                       HWND hwnd, LPTPMPARAMS lptpm);

/* ------------------------------------------------------------------ */
/* Dialog Boxes Reference functions.  Header Winuser.h except where    */
/* noted: MessageBox / CheckDlgButton / IsDlgButtonChecked print       */
/* Header Windows.h (windows.h); MessageBeep prints Header Winbase.h   */
/* (winbase.h).                                                        */
/* ------------------------------------------------------------------ */

HWND CreateDialogW(HINSTANCE hInstance, LPCTSTR lpTemplate,       /* ms908169 */
                   HWND hWndParent, DLGPROC lpDialogFunc);
#define CreateDialog CreateDialogW
HWND CreateDialogIndirect(HINSTANCE hInstance,                    /* ms908170 */
                          LPCDLGTEMPLATE lpTemplate, HWND hWndParent,
                          DLGPROC lpDialogFunc);
HWND CreateDialogIndirectParam(HINSTANCE hInstance,               /* ms908171 */
                               LPCDLGTEMPLATE lpTemplate, HWND hWndParent,
                               DLGPROC lpDialogFunc, LPARAM lParamInit);
HWND CreateDialogParamW(HINSTANCE hInstance, LPCTSTR lpTemplateName, /* ms908172 */
                        HWND hWndParent, DLGPROC lpDialogFunc,
                        LPARAM dwInitParam);
#define CreateDialogParam CreateDialogParamW
LRESULT DefDlgProc(HWND hDlg, UINT Msg, WPARAM wParam,            /* ms908209 */
                   LPARAM lParam);
int    DialogBoxW(HINSTANCE hInstance, LPCTSTR lpTemplate,        /* aa452947 */
                  HWND hWndParent, DLGPROC lpDialogFunc);
#define DialogBox DialogBoxW
int    DialogBoxIndirect(HINSTANCE hInstance, LPDLGTEMPLATE lpTemplate, /* aa452948 */
                         HWND hWndParent, DLGPROC lpDialogFunc);
int    DialogBoxIndirectParam(HINSTANCE hInstance,                /* aa452949 */
                              LPCDLGTEMPLATE hDialogTemplate, HWND hWndParent,
                              DLGPROC lpDialogFunc, LPARAM dwInitParam);
int    DialogBoxParamW(HINSTANCE hInstance, LPCTSTR lpTemplateName, /* aa452950 */
                       HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam);
#define DialogBoxParam DialogBoxParamW
BOOL   EndDialog(HWND hDlg, int nResult);                         /* aa453038 */
LONG   GetDialogBaseUnits(void);                                  /* ms929231 */
int    GetDlgCtrlID(HWND hwndCtl);                                /* ms929233 */
HWND   GetDlgItem(HWND hDlg, int nIDDlgItem);                     /* ms929234 */
UINT   GetDlgItemInt(HWND hDlg, int nIDDlgItem, BOOL* lpTranslated,
                     BOOL bSigned);                               /* ms929235 */
UINT   GetDlgItemTextW(HWND hDlg, int nIDDlgItem, LPTSTR lpString,
                       int nMaxCount);                            /* ms929236 */
#define GetDlgItemText GetDlgItemTextW
HWND   GetNextDlgGroupItem(HWND hDlg, HWND hCtl, BOOL bPrevious);  /* aa453145 */
HWND   GetNextDlgTabItem(HWND hDlg, HWND hCtl, BOOL bPrevious);    /* aa453146 */
BOOL   IsDialogMessage(HWND hDlg, LPMSG lpMsg);                   /* ms909864 */
BOOL   MapDialogRect(HWND hDlg, LPRECT lpRect);                   /* ms911788 */
LONG   SendDlgItemMessage(HWND hDlg, int nIDDlgItem, UINT Msg,    /* ms932717 */
                          WPARAM wParam, LPARAM lParam);
BOOL   SetDlgItemInt(HWND hDlg, int nIDDlgItem, UINT uValue,      /* ms940020 */
                     BOOL bSigned);
BOOL   SetDlgItemTextW(HWND hDlg, int nIDDlgItem, LPCTSTR lpString); /* ms940021 */
#define SetDlgItemText SetDlgItemTextW

/* ms909866 "IsDlgButtonChecked" and ms928573 "CheckDlgButton" are     */
/* declared in windows.h (their pages list Header Windows.h).           */

/* Buttons Reference: ms928577 "CheckRadioButton" (Header Winuser.h).   */
BOOL CheckRadioButton(HWND hDlg, int nIDFirstButton, int nIDLastButton,
                      int nIDCheckButton);

/* ------------------------------------------------------------------ */
/* Clipboards Reference functions (Header Winuser.h).                 */
/* ------------------------------------------------------------------ */

BOOL   CloseClipboard(void);                       /* ms928586 */
int    CountClipboardFormats(void);                /* ms908153 */
BOOL   EmptyClipboard(void);                       /* aa453019 */
UINT   EnumClipboardFormats(UINT format);          /* aa453047 */
HANDLE GetClipboardData(UINT uFormat);             /* ms929215 */
HANDLE GetClipboardDataAlloc(UINT uFormat);        /* ms929216 */
int    GetClipboardFormatNameW(UINT format, LPTSTR lpszFormatName,
                               int cchMaxCount);   /* ms929217 */
#define GetClipboardFormatName GetClipboardFormatNameW
HWND   GetClipboardOwner(void);                    /* ms929218 */
HWND   GetOpenClipboardWindow(void);               /* aa453149 */
int    GetPriorityClipboardFormat(UINT* paFormatPriorityList,
                                  int cFormats);   /* aa453154 */
BOOL   IsClipboardFormatAvailable(UINT format);    /* ms909863 */
BOOL   OpenClipboard(HWND hWndNewOwner);           /* ms911905 */
UINT   RegisterClipboardFormatW(LPCWSTR lpszFormat); /* ms913094; the page
                                                      * states only the
                                                      * Unicode version */
#define RegisterClipboardFormat RegisterClipboardFormatW
HANDLE SetClipboardData(UINT uFormat, HANDLE hMem); /* ms940015 */

/* ------------------------------------------------------------------ */
/* Resources Reference icon/image functions (Header Winuser.h).        */
/* ------------------------------------------------------------------ */

HICON  CreateIconIndirect(PICONINFO piconinfo);     /* ms908175 */
BOOL   DestroyIcon(HICON hIcon);                    /* aa452938 */
BOOL   DrawIconEx(HDC hdc, int xLeft, int yTop, HICON hIcon,
                  int cxWidth, int cyWidth, UINT istepIfAniCur,
                  HBRUSH hbrFlickerFreeDraw, UINT diFlags);   /* aa452972 */
BOOL   GetIconInfo(HICON hIcon, PICONINFO piconinfo);         /* ms929247 */
HICON  LoadIconW(HINSTANCE hInstance, LPCTSTR lpIconName);    /* aa453411 */
#define LoadIcon LoadIconW
HANDLE LoadImageW(HINSTANCE hinst, LPCTSTR lpszName, UINT uType,
                  int cxDesired, int cyDesired, UINT fuLoad);  /* aa453413 */
#define LoadImage LoadImageW

/* ------------------------------------------------------------------ */
/* System Information Reference functions (Header Winuser.h).          */
/* ------------------------------------------------------------------ */

BOOL  EnableHardwareKeyboard(BOOL bEnable);          /* aa453033 */
DWORD GetSysColor(int nIndex);                       /* aa453167 */
int   GetSystemMetrics(int nIndex);                  /* aa453170 */
BOOL  SystemParametersInfoW(UINT uiAction, UINT uiParam, PVOID pvParam,
                            UINT fWinIni);           /* ms940383; the page
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
#define WM_QUIT                        0x0012         /* aa453895 */
#define WM_SETTEXT                     0x000C         /* aa453905 */
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

/* --- Image-type constants for LoadImage / ImageList_LoadImage uType --- */
#define IMAGE_BITMAP                   0            
#define IMAGE_ICON                     1            
#define IMAGE_CURSOR                   2            

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WINUSER_H */
