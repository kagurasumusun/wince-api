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

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WINUSER_H */
