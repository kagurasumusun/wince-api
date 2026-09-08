/*
 * aygshell.h -- AYGShell (Ayutthaya shell) extensions for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  The AYGShell Reference book of the CE 5.0 Shell documentation
 * (Shell and User Interface :: Shell :: Shell Reference :: AYGShell
 * Reference) is the source book: AYGShell Functions (34 pages),
 * AYGShell Structures (8), AYGShell Macros (3), AYGShell Messages (9),
 * AYGShell Interfaces (INewMenuItemServer, IShellNotificationCallback),
 * AYGShell Enumerations (SHNP) and AYGShell Controls (WC_SIPPREF).
 *
 * Requirement rows: the pages print Header: aygshell.h with the library
 * row labelled "Link Library:" or "Library:" (both spellings appear in
 * this book) reading aygshell.lib -- those rows feed
 * def/aygshell-doc.def.  Items whose rows name other homes live in the
 * headers that own them: SHInitDialog (Header: shellsdk.h) in
 * shellsdk.h, SHGetAutoRunPath (Header: windows.h) in windows.h, the
 * NMN_* messages and NMNEWMENU (Header: newmenu.h) in newmenu.h, and
 * WM_FILECHANGEINFO / FILECHANGENOTIFY (shlobj.h homes) in shlobj.h
 * (with FILECHANGEINFO in extfile.h per its Extfile.h row).
 *
 * Transcription notes (all recorded per item in docs/inventory.md):
 *  (a) The CE 5.0 migration strips code spacing; the whitespace-
 *      preserved prototypes of the CE 6.0 (v=winembedded.60) twins are
 *      noted per declaration where the CE 5.0 print is mangled
 *      (SHGetInputContext / SHSetInputContext).
 *  (b) Some prototypes print the WINSHELLAPI decoration
 *      (SHHandleWMActivate, SHHandleWMSettingChange, SHRecognizeGesture)
 *      and some print WINAPI (SHChangeNotifyDeregister/Free/Register,
 *      SHFindMenuBar, SHSipInfo); Windows CE has one undecorated
 *      calling convention, so WINAPI is empty (windef.h) and the
 *      import decoration is this tree's AKARI_CE_IMPORT pin instead
 *      (documented design decision, same model as commctrl.h).
 *  (c) The SHCMBM_* menu-bar messages, the SHIDIF_* / SHCMBF_* /
 *      SHDB_* / SHFS_* / SHRG_* / SHNF_* / SHNUM_* / SPI_*SIPINFO /
 *      SHIC_FEATURE flag sets and the GN_CONTEXTMENU notification
 *      value are published as NAMES without numeric values on both the
 *      CE 5.0 pages and their CE 6.0 twins; they are held as gaps in
 *      docs/inventory.md rather than defined here (the M39-M41
 *      held-set policy).  The three AYGShell macros that expand to
 *      SendMessage calls on SHCMBM_* messages (SHGetMenu, SHGetSubMenu,
 *      SHSetSubMenu) are recorded verbatim below but not defined for
 *      the same reason.
 *  (d) SHSipPreference (aa453741) is held entirely: its parameter type
 *      SIPSTATE has no published definition in any official CE tree
 *      (no SIPSTATE page in the CE 5.0 / CE .NET / CE 6.0 catalogs),
 *      so the documented signature cannot be typed in C without
 *      inventing the enum (see docs/inventory.md).
 *  (e) The SHNOTIFICATIONDATA layout below is the CE 5.0 page print
 *      (ends at lParam).  The CE 6.0 twin ee499049 extends the layout
 *      with "union { SOFTKEYMENU skm; SOFTKEYNOTIFY
 *      rgskn[NOTIF_NUM_SOFTKEYS]; }" plus pszTodaySK / pszTodayExec
 *      members; SOFTKEYMENU / SOFTKEYNOTIFY / NOTIF_NUM_SOFTKEYS have
 *      no pages in any official CE catalog, so the extension is held
 *      (the CE 5.0 page's own code example uses rgskn / pszTodaySK /
 *      pszTodayExec -- an internal inconsistency of the CE 5.0 page,
 *      recorded in docs/inventory.md).
 */

#ifndef AKARI_AYGSHELL_H
#define AKARI_AYGSHELL_H

#include "windows.h"   /* base + GWES types, HKEY, COLORREF, HICON, ... */
#include "objbase.h"   /* CLSID, REFCLSID, IUnknown, IPropertyBag */
#include "shlobj.h"    /* FILECHANGENOTIFY (SHChangeNotifyFree) */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Handle carriers and interface types named by the documented          */
/* prototypes but not published as type pages (design decision:        */
/* handle carriers like the M45 TAPI handles; opaque interface tags    */
/* like the M44 objbase.h set).                                        */
/* ------------------------------------------------------------------ */

/* aa453688 (SHEnumPropSheetHandlers) types its array parameter
 * "HPROPSHEETPAGE*"; no CE page publishes the HPROPSHEETPAGE carrier
 * (its home is the unharvested Property Sheets book), so it is carried
 * as HANDLE. */
typedef HANDLE HPROPSHEETPAGE;

/* aa453688 types the interface-pointer array "IShellPropSheetExt **";
 * no CE page in any catalog documents the IShellPropSheetExt interface
 * (the page's Remarks name its AddPages method), so it is an opaque
 * interface tag (same model as the M44 objbase.h interfaces). */
typedef struct IShellPropSheetExt IShellPropSheetExt;

/* ------------------------------------------------------------------ */
/* Enumerations                                                         */
/* ------------------------------------------------------------------ */

/* aa453728 "SHNP" (Windows CE 3.0 and later; aygshell.h).  Notification
 * priority for SHNOTIFICATIONDATA.npPriority.  The page prints the
 * complete enum body; the enumerators take their implicit values.
 * SHNP_INFORM: bubble displays for the set duration, then disappears.
 * SHNP_ICONIC: no bubble; an icon displays for the set duration. */
typedef enum _SHNP {
    SHNP_INFORM,
    SHNP_ICONIC
} SHNP;

/* ------------------------------------------------------------------ */
/* Structures                                                           */
/* ------------------------------------------------------------------ */

/* aa453665 "SHACTIVATEINFO" (Windows CE 3.0 and later; aygshell.h;
 * aygshell.lib).  Input-panel activation state carried between
 * SHHandleWMActivate / SHHandleWMSettingChange calls; must be
 * zero-initialized before the first call (memset + cbSize).  The page
 * prints the bitfield members with stray periods after the names
 * ("cbSize.", "fSipUp.:1"); removed.  Anonymous tag as printed. */
typedef struct {
    DWORD cbSize;
    HWND  hwndLastFocus;
    UINT  fSipUp          : 1;
    UINT  fSipOnDeactivation : 1;
    UINT  fActive         : 1;
    UINT  fReserved       : 29;
} SHACTIVATEINFO, *PSHACTIVATEINFO;

/* aa453671 "SHCHANGENOTIFYENTRY" (Windows CE .NET 4.2 and later;
 * aygshell.h).  Event selection for SHChangeNotifyRegister.  dwEventMask
 * combines the SHCNE_* event names (published without values -- held
 * set); a NULL pshcne requests all file system, network and media
 * notifications.  The page marks fRecursive "Not supported." (the
 * Windows Mobile row documents the recursive behaviour). */
typedef struct tagSHCHANGENOTIFYENTRY {
    DWORD  dwEventMask;    /* SHCNE_* combination (names held, no values) */
    LPTSTR pszWatchDir;    /* fully qualified path; NULL = whole file system */
    BOOL   fRecursive;     /* "Not supported" on the CE 5.0 page */
} SHCHANGENOTIFYENTRY;

/* aa453714 "SHINITDLGINFO" (Windows CE 3.0 and later; aygshell.h;
 * aygshell.lib).  Parameters for SHInitDialog (shellsdk.h).  dwMask
 * takes SHIDIM_FLAGS (value published); dwFlags combines the SHIDIF_*
 * flag names (published without values -- held set). */
typedef struct tagSHINITDIALOG {
    DWORD dwMask;          /* SHIDIM_FLAGS selects dwFlags */
    HWND  hDlg;            /* handle to the dialog box (required) */
    DWORD dwFlags;         /* SHIDIF_* combination (names held) */
} SHINITDLGINFO, *PSHINITDLGINFO;

/* aa453714: the dwMask bit is published with its value. */
#define SHIDIM_FLAGS   0x0001

/* aa453721 "SHMENUBARINFO" (Windows CE 3.0 and later; aygshell.h;
 * aygshell.lib).  Parameters for SHCreateMenuBar.  dwFlags combines the
 * SHCMBF_* flag names (published without values -- held set); with
 * SHCMBF_HMENU, nToolBarId is a menu identifier (or an in-memory hmenu
 * when HIWORD is zero), otherwise a toolbar identifier loaded from
 * hInstRes.  nBmpId / cBmpImages are NULL for soft-key creation. */
typedef struct tagSHMENUBARINFO {
    DWORD     cbSize;
    HWND      hwndParent;   /* window to control the command bar window */
    DWORD     dwFlags;      /* SHCMBF_* combination (names held) */
    UINT      nToolBarId;   /* toolbar / menu resource identifier */
    HINSTANCE hInstRes;     /* instance that controls the resources */
    int       nBmpId;       /* bitmap resource for button images */
    int       cBmpImages;   /* number of images in that bitmap */
    HWND      hwndMB;       /* out: window handle to the menu bar */
    COLORREF  clrBk;        /* menu-bar background color (SHCMBF_COLORBK) */
} SHMENUBARINFO, *PSHMENUBARINFO;

/* aa453724 "SHNOTIFICATIONDATA" (Windows CE 3.0 and later; aygshell.h).
 * Notification description for SHNotificationAdd / GetData / Remove /
 * Update.  grfFlags combines the SHNF_* flag names (published without
 * values -- held set; the page prints "SHNF_SHNF_SPINNERS", doubled,
 * recorded verbatim in docs/inventory.md).  npPriority is the SHNP
 * enumeration; csDuration is seconds (-1 = until dismissed); hwndSink
 * receives the command choices; pszHTML / pszTitle are Unicode strings
 * on CE.  The CE 6.0 layout extension is held (header note (e)). */
typedef struct _SHNOTIFICATIONDATA {
    DWORD   cbStruct;      /* size of the structure, for verification */
    DWORD   dwID;          /* identifier for this notification */
    SHNP    npPriority;    /* SHNP_INFORM / SHNP_ICONIC */
    DWORD   csDuration;    /* duration in seconds; -1 = infinite */
    HICON   hicon;         /* icon for the notification */
    DWORD   grfFlags;      /* SHNF_* combination (names held) */
    CLSID   clsid;         /* unique identifier for the class */
    HWND    hwndSink;      /* window to receive command choices */
    LPCTSTR pszHTML;       /* HTML content for the bubble */
    LPCTSTR pszTitle;      /* optional bubble title */
    LPARAM  lParam;        /* user-defined parameter */
} SHNOTIFICATIONDATA;

/* aa453733 "SHRGINFO" (Windows CE 3.0 and later; aygshell.h;
 * aygshell.lib).  Parameters for SHRecognizeGesture.  dwFlags combines
 * the SHRG_* flag names (published without values -- held set).  The
 * page prints the tag "tagSHRGI". */
typedef struct tagSHRGI {
    DWORD cbSize;
    HWND  hwndClient;      /* window calling SHRecognizeGesture */
    POINT ptDown;          /* X/Y client coordinates of the mouse-down */
    DWORD dwFlags;         /* SHRG_* combination (names held) */
} SHRGINFO, *PSHRGINFO;

/* ------------------------------------------------------------------ */
/* AYGShell controls                                                    */
/* ------------------------------------------------------------------ */

/* ms914097 "WC_SIPPREF" (Windows CE .NET 4.2 and later; Aygshell.h;
 * Aygshell.lib).  Control class implementing default input-panel
 * behavior in a dialog box (raise the SIP on focus, lower it on focus
 * loss) for edit boxes, CAPEDIT, CBS_DROPDOWN combo boxes and date and
 * time picker controls; add it as the last control of the dialog
 * template and call SHInitExtraControls first.  The page publishes the
 * value. */
#define WC_SIPPREF   L"SIPPREF"

/* ------------------------------------------------------------------ */
/* AYGShell interfaces (application-implemented; not DLL exports)       */
/* ------------------------------------------------------------------ */

/* ms909845 "INewMenuItemServer" (Windows CE .NET 4.2 and later;
 * Aygshell.h; Link Library: Application-defined).  Object handler for
 * items created by the New button; obtained through CoCreateInstance
 * with IID_INewMenuItemServer.  Documented methods (the STDMETHOD
 * shapes are recorded as printed; the interface vtable layout is not
 * published as a C structure, same model as the M44 objbase.h set):
 *   ms909846 CreateNewItem: HRESULT CreateNewItem(HWND hwndParent)
 */
typedef struct INewMenuItemServer INewMenuItemServer;

/* ms909877 "IShellNotificationCallback" (Windows CE 3.0 and later;
 * aygshell.h; aygshell.lib).  Callback interface the shell uses to
 * advise the notification owner of actions taken on the notification
 * (the application implements it; not a DLL export).  Methods in vtable
 * order (page table): IUnknown methods, then
 *   OnShow            -- Reserved. Returns E_NOTIMPL (no signature page)
 *   OnCommandSelected -- ms909878: STDMETHOD(OnCommandSelected)(
 *                          THIS_ DWORD dwID, WORD wCmdID) PURE
 *   OnLinkSelected    -- ms909880: STDMETHOD(OnLinkSelected)(
 *                          THIS_ DWORD dwID, LPCTSTR pszLink,
 *                          LPARAM lParam) PURE
 *   OnDismiss         -- ms909879: STDMETHOD(OnDismiss)(
 *                          THIS_ DWORD dwID, BOOL fTimeout,
 *                          LPARAM lParam) PURE
 */
typedef struct IShellNotificationCallback IShellNotificationCallback;

/* ------------------------------------------------------------------ */
/* AYGShell macros (aa453703 SHGetMenu, aa453708 SHGetSubMenu,          */
/* aa453738 SHSetSubMenu) -- recorded verbatim, held (they expand to     */
/* SendMessage calls on the SHCMBM_* messages whose values are not      */
/* published):                                                          */
/*                                                                      */
/*   #define SHGetMenu(hWndMB) (HMENU)SendMessage((hWndMB), \           */
/*           SHCMBM_GETMENU, (WPARAM)0, (LPARAM)0);                     */
/*   #define SHGetSubMenu(hWndMB,ID_MENU) (HMENU)SendMessage(           */
/*           (hWndMB), \ SHCMBM_GETSUBMENU, (WPARAM)0,                  */
/*           (LPARAM)ID_MENU);                                          */
/*   #define SHSetSubMenu(hWndMB,ID_MENU) (HMENU)SendMessage(           */
/*           (hWndMB), \ SHCMBM_SETSUBMENU, (WPARAM)0,                  */
/*           (LPARAM)ID_MENU);                                          */
/*                                                                      */
/* AYGShell messages (aygshell.h; shapes documented, values held):      */
/*   SHCMBM_GETMENU    wParam = 0; lParam = 0          (aa453675)       */
/*   SHCMBM_GETSUBMENU wParam = 0; lParam = menuid     (aa453676)       */
/*   SHCMBM_SETSUBMENU wParam = wParam; lParam = (HMENU) hmenu          */
/*                                                       (aa453677)     */
/* ------------------------------------------------------------------ */

/* ------------------------------------------------------------------ */
/* Functions (Header: aygshell.h; Library: aygshell.lib).               */
/* ------------------------------------------------------------------ */

/* aa453670 (CE .NET 4.2+): removes a window from the file notification
 * chain (registered with SHChangeNotifyRegister).  Page prints WINAPI. */
AKARI_CE_IMPORT BOOL SHChangeNotifyDeregister(HWND hwnd) AKARI_CE_NAME(SHChangeNotifyDeregister);

/* aa453672 (CE .NET 4.2+): frees the memory allocated for a
 * WM_FILECHANGEINFO change notification; the message processor must
 * call it on receipt (shell memory leak otherwise).  Page prints
 * WINAPI. */
AKARI_CE_IMPORT void SHChangeNotifyFree(FILECHANGENOTIFY *pfcn) AKARI_CE_NAME(SHChangeNotifyFree);

/* aa453673 (CE .NET 4.2+): enlists a window for file change
 * notifications; the window receives WM_FILECHANGEINFO (shlobj.h).  A
 * NULL pshcne requests all file system, network and media
 * notifications.  Recursive notifications are not recognized.  Page
 * prints WINAPI. */
AKARI_CE_IMPORT BOOL SHChangeNotifyRegister(HWND hwnd,
                                            SHCHANGENOTIFYENTRY *pshcne) AKARI_CE_NAME(SHChangeNotifyRegister);

/* aa453674 (CE 3.0+): frees memory by having the shell close other
 * applications with WM_CLOSE (dwMemSought in bytes). */
AKARI_CE_IMPORT BOOL SHCloseApps(DWORD dwMemSought) AKARI_CE_NAME(SHCloseApps);

/* aa453678 (CE .NET 4.2+): creates a menu or soft-key bar associated
 * with the window in SHMENUBARINFO.hwndParent; on success the bar is
 * positioned at the bottom of that window (resize the main window to
 * accommodate it; SHFindMenuBar + GetWindowRect measure it). */
AKARI_CE_IMPORT BOOL SHCreateMenuBar(SHMENUBARINFO *pmb) AKARI_CE_NAME(SHCreateMenuBar);

/* aa453679 (CE 3.0+): creates a new item programmatically, as if
 * chosen from the global New button menu (the OS sends
 * NMN_INVOKECOMMAND to the hosting application first). */
AKARI_CE_IMPORT HRESULT SHCreateNewItem(HWND hwndOwner, REFCLSID clsid) AKARI_CE_NAME(SHCreateNewItem);

/* aa453682 (CE 3.0+): shows or hides the Done (OK) button of a
 * top-level window; dwState takes the SHDB_SHOW / SHDB_HIDE /
 * SHDB_SHOWCANCEL state names (values not published -- held set). */
AKARI_CE_IMPORT BOOL SHDoneButton(HWND hwndRequester, DWORD dwState) AKARI_CE_NAME(SHDoneButton);

/* aa453688 (CE 3.0+): enumerates the property-sheet handler sub-keys
 * under hkey, filling arrays of HPROPSHEETPAGE and IShellPropSheetExt*
 * (both allocated by the caller; release after PropertySheet).  The
 * page states this function is a stub on Windows CE-based devices and
 * returns FALSE there. */
AKARI_CE_IMPORT BOOL SHEnumPropSheetHandlers(HKEY hkey, int *pcPages,
                                             HPROPSHEETPAGE *prghPropPages,
                                             IShellPropSheetExt **prgpispse) AKARI_CE_NAME(SHEnumPropSheetHandlers);

/* aa453692 (CE 3.0+): returns the handle to the menu-bar window created
 * with SHCreateMenuBar for the given window.  Page prints WINAPI. */
AKARI_CE_IMPORT HWND SHFindMenuBar(HWND hwnd) AKARI_CE_NAME(SHFindMenuBar);

/* aa453693 (CE 3.0+): releases the context-menu extension abstraction
 * object allocated by SHLoadContextMenuExtensions. */
AKARI_CE_IMPORT BOOL SHFreeContextMenuExtensions(HANDLE hCMExtensions) AKARI_CE_NAME(SHFreeContextMenuExtensions);

/* aa453694 (CE 3.0+): takes over screen areas (taskbar, Input Panel
 * button, Start icon); dwState combines the SHFS_SHOWTASKBAR /
 * SHFS_HIDETASKBAR / SHFS_SHOWSIPBUTTON / SHFS_HIDESIPBUTTON /
 * SHFS_SHOWSTARTICON / SHFS_HIDESTARTICON names (values not published
 * -- held set).  With an SHFS_HIDE* flag the window must be foreground.
 * (CE 6.0 twin ee499392 prints Header: shellsdk.h -- divergence
 * recorded in docs/inventory.md.) */
AKARI_CE_IMPORT BOOL SHFullScreen(HWND hwndRequester, DWORD dwState) AKARI_CE_NAME(SHFullScreen);

/* aa453695 (CE 3.0+): returns the virtual-key code of the navigation
 * control mapped to the application (0 = no mapping); data comes from
 * HKEY_LOCAL_MACHINE\Software\Microsoft\Shell\Keys. */
AKARI_CE_IMPORT BYTE SHGetAppKeyAssoc(LPCTSTR ptszApp) AKARI_CE_NAME(SHGetAppKeyAssoc);

/* aa453699 (CE 3.0+): gets the list of emergency numbers
 * (NULL-separated, double-NULL-terminated) into a caller-allocated
 * TCHAR buffer.  Stub on Windows CE-based devices: returns E_NOTIMPL
 * there; E_INVALIDARG signals inadequate buffer space. */
AKARI_CE_IMPORT HRESULT SHGetEmergencyCallList(TCHAR *pwszBuffer, UINT uLenBuf) AKARI_CE_NAME(SHGetEmergencyCallList);

/* aa453701 (CE .NET 4.0+): retrieves the state of an input-window
 * context feature; dwFeature takes a value of the SHIC_FEATURE
 * enumeration (no page publishes the enumeration -- name held).  Stub
 * on Windows CE-based devices: always returns E_NOTIMPL.  Signature
 * spacing restored from the CE 6.0 twin ee503391. */
AKARI_CE_IMPORT HRESULT SHGetInputContext(HWND hwnd, DWORD dwFeature,
                                          LPVOID lpValue,
                                          LPDWORD lpdwSize) AKARI_CE_NAME(SHGetInputContext);

/* aa453710 (CE 3.0+): handles WM_ACTIVATE for input-panel state
 * restoration; pass the message's wParam/lParam and the
 * zero-initialized SHACTIVATEINFO also used with
 * SHHandleWMSettingChange.  dwFlags takes SHA_INPUTDIALOG (name held;
 * use with SHSipPreference in large-entry dialog boxes).  Page prints
 * the WINSHELLAPI decoration (header note (b)). */
AKARI_CE_IMPORT BOOL SHHandleWMActivate(HWND hwnd, WPARAM wParam, LPARAM lParam,
                                        SHACTIVATEINFO *psai,
                                        DWORD dwFlags) AKARI_CE_NAME(SHHandleWMActivate);

/* aa453711 (CE 3.0+): handles WM_SETTINGCHANGE by sizing hwnd based on
 * the current input-panel position; pass the same SHACTIVATEINFO as
 * SHHandleWMActivate (wFlag SPI_SETSIPINFO sizes the window).  Page
 * prints the WINSHELLAPI decoration (header note (b)). */
AKARI_CE_IMPORT BOOL SHHandleWMSettingChange(HWND hwnd, WPARAM wParam, LPARAM lParam,
                                             SHACTIVATEINFO *psai) AKARI_CE_NAME(SHHandleWMSettingChange);

/* aa453715 (CE 3.0+): initializes the AYGShell extra controls (call
 * before creating a WC_SIPPREF control). */
AKARI_CE_IMPORT BOOL SHInitExtraControls(void) AKARI_CE_NAME(SHInitExtraControls);

/* aa453716 (CE 3.0+): input-dialog helper; call at the top of the
 * dialog's window procedure: raises the input panel when the dialog is
 * activated and lowers it on deactivation. */
AKARI_CE_IMPORT void SHInputDialog(HWND hwnd, UINT uMsg, WPARAM wParam) AKARI_CE_NAME(SHInputDialog);

/* aa453717 (CE 3.0+): invokes a context-menu command in the extension
 * that added it (hCMExtensions from SHLoadContextMenuExtensions). */
AKARI_CE_IMPORT BOOL SHInvokeContextMenuCommand(HWND hwndOwner, UINT idCmd,
                                                HANDLE hCMExtensions) AKARI_CE_NAME(SHInvokeContextMenuCommand);

/* aa453719 (CE 3.0+): loads the context-menu extensions registered for
 * the pszContext/pszClass pair, adding menu items to hmenu in the range
 * [idCmdFirst, idCmdLast]; free the returned abstraction object with
 * SHFreeContextMenuExtensions.  punkOwner is the application's data
 * abstraction (IUnknown; IOleWindow/IDataObject/IDispatch optional). */
AKARI_CE_IMPORT BOOL SHLoadContextMenuExtensions(IUnknown *punkOwner,
                                                 LPCTSTR pszContext,
                                                 LPCTSTR pszClass,
                                                 HMENU hmenu,
                                                 UINT idCmdFirst,
                                                 UINT idCmdLast,
                                                 HANDLE *phCMExtensions) AKARI_CE_NAME(SHLoadContextMenuExtensions);

/* aa453722 (CE 3.0+): default handling of the Back button (return to
 * the previous application).  Stub in the OS for application
 * compatibility. */
AKARI_CE_IMPORT void SHNavigateBack(void) AKARI_CE_NAME(SHNavigateBack);

/* aa453723 (CE 3.0+): asynchronously adds a notification to the
 * notification tray; returns ERROR_SUCCESS when successful. */
AKARI_CE_IMPORT LRESULT SHNotificationAdd(SHNOTIFICATIONDATA *pndAdd) AKARI_CE_NAME(SHNotificationAdd);

/* aa453725 (CE 3.0+): queries the data of an existing notification
 * back; on success pndBuffer->pszHTML / pszTitle are owned by (and must
 * be freed by) the caller.  Returns ERROR_SUCCESS when successful. */
AKARI_CE_IMPORT LRESULT SHNotificationGetData(const CLSID *pclsid, DWORD dwID,
                                              SHNOTIFICATIONDATA *pndBuffer) AKARI_CE_NAME(SHNotificationGetData);

/* aa453726 (CE 3.0+): removes a notification (dwID must not be 0).
 * Returns ERROR_SUCCESS when successful. */
AKARI_CE_IMPORT LRESULT SHNotificationRemove(const CLSID *pclsid, DWORD dwID) AKARI_CE_NAME(SHNotificationRemove);

/* aa453727 (CE 3.0+): updates members of a pending notification;
 * grnumUpdateMask combines the SHNUM_* flag names (values not
 * published -- held set); pndNew must at least carry dwID and clsid. */
AKARI_CE_IMPORT LRESULT SHNotificationUpdate(DWORD grnumUpdateMask,
                                             SHNOTIFICATIONDATA *pndNew) AKARI_CE_NAME(SHNotificationUpdate);

/* aa453732 (CE 3.0+): recognizes the stylus tap-and-hold / Action
 * press-and-hold gesture (call during WM_LBUTTONDOWN / WM_KEYDOWN
 * processing).  With SHRG_RETURNCMD the return is the GN_CONTEXTMENU
 * notification (value not published -- held); otherwise a WM_CONTEXTMENU
 * / WM_NOTIFY+GN_CONTEXTMENU is sent per the SHRG_* flags.  Returns 0
 * when no gesture was recognized.  Page prints the WINSHELLAPI
 * decoration (header note (b)). */
AKARI_CE_IMPORT DWORD SHRecognizeGesture(SHRGINFO *shrg) AKARI_CE_NAME(SHRecognizeGesture);

/* aa453734 (CE 3.0+): assigns the window that receives a hardware
 * button's key-press messages; bVk uses the virtual-key codes of the
 * navigation controls (the page's Remarks reference VK_APP1 through
 * VK_APP6 -- names not published as CE pages, recorded in
 * docs/inventory.md). */
AKARI_CE_IMPORT BOOL SHSetAppKeyWndAssoc(BYTE bVk, HWND hwnd) AKARI_CE_NAME(SHSetAppKeyWndAssoc);

/* aa453735 (CE 5.0+): not implemented; a stub for application
 * compatibility -- always returns ERROR_CALL_NOT_IMPLEMENTED. */
AKARI_CE_IMPORT void SHSetBack(int eOp, HWND hwnd) AKARI_CE_NAME(SHSetBack);

/* aa453736 (CE .NET 4.0+): changes an input-window context feature;
 * dwFeature takes a value of the SHIC_FEATURE enumeration (name held).
 * Stub on Windows CE-based devices: always returns E_NOTIMPL.
 * Signature spacing restored from the CE 6.0 twin ee502532. */
AKARI_CE_IMPORT HRESULT SHSetInputContext(HWND hwnd, DWORD dwFeature,
                                          const LPVOID lpValue) AKARI_CE_NAME(SHSetInputContext);

/* aa453737 (CE 3.0+): sets the taskbar title text (NULL resets to the
 * title of hwndRequester). */
AKARI_CE_IMPORT BOOL SHSetNavBarText(HWND hwndRequester, LPCTSTR pszText) AKARI_CE_NAME(SHSetNavBarText);

/* aa453740 (CE 3.0+): queries or sets system-wide input-panel / input
 * method parameters.  uiAction takes the SPI_GETSIPINFO / SPI_SETSIPINFO
 * / SPI_SETCURRENTIM / SPI_GETCURRENTIM action names (values not
 * published -- held set); pvParam points to a SIPINFO structure for the
 * *SIPINFO actions and to a CLSID for the *CURRENTIM actions (the
 * SIPINFO structure is declared by sipapi.h, M51 -- the CE 6.0 twin
 * ee499105 also prints Header: sipapi.h).  fWinIni is reserved: set to
 * 0.  Page prints WINAPI. */
AKARI_CE_IMPORT BOOL SHSipInfo(UINT uiAction, UINT uiParam, PVOID pvParam,
                               UINT fWinIni) AKARI_CE_NAME(SHSipInfo);

/* aa453741 "SHSipPreference" (Windows CE 3.0 and later; aygshell.h;
 * aygshell.lib) is HELD: the documented parameter type
 *     BOOL SHSipPreference(HWND hwnd, SIPSTATE st);
 * names SIPSTATE, for which no official CE tree publishes a definition
 * (no SIPSTATE page in the CE 5.0 / CE .NET / CE 6.0 catalogs, and the
 * SIP_UP / SIP_DOWN / SIP_FORCEDOWN / SIP_UNCHANGED parameter values --
 * like the SIP_INPUTDIALOG name quoted by SHHandleWMActivate -- appear
 * only as prose names without values).  See docs/inventory.md. */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_AYGSHELL_H */
