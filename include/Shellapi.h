/*
 * Shellapi.h -- Shell API declarations for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  Sources: the Resources Reference (ExtractIconEx) and the
 * Standard Shell Reference (M53) -- the CE 5.0 Shell documentation
 * pages whose Requirements rows print Header: Shellapi.h.
 *
 * Two Standard Shell function pages print no Link Library row at all
 * (Shell_NotifyIcon aa453686, SHGetFileInfo aa453700): their exports
 * are therefore not derived into any import def (the def policy is
 * page-row-driven); the WM 6.5 documentation prints an aygshell.lib
 * row for SHGetFileInfo, but that is a different platform layer and is
 * recorded in docs/inventory.md M53 rather than used.
 *
 * Windows CE is Unicode-only; every string member and parameter is wide.
 */

#ifndef AKARI_SHELLAPI_H
#define AKARI_SHELLAPI_H

#include "Windef.h"
#include "Windows.h"   /* HWND, HICON, HBITMAP, HINSTANCE, HKEY, SW_* */
#include "Shlobj.h"    /* LPCITEMIDLIST / LPITEMIDLIST (pidl params) */

#ifdef __cplusplus
extern "C" {
#endif

/* aa453065 "ExtractIconEx": extracts icon handles from an executable,
 * DLL, or icon file.  CE 1.0+; Header: Shellapi.h.  Windows CE is
 * Unicode-only, so the wide form is the API (generic macro below). */
HICON ExtractIconExW(LPCTSTR lpszFile, int nIconIndex,
                     HICON* phiconLarge, HICON* phiconSmall, UINT nIcons);
#define ExtractIconEx ExtractIconExW

/* ------------------------------------------------------------------ */
/* Standard Shell Reference (M53): taskbar status area (Shell_NotifyIcon). */
/* ------------------------------------------------------------------ */

/* ms911889 "NOTIFYICONDATA" (Windows CE 1.0 and later; Shellapi.h).
 * Taskbar status area (notification icon) descriptor.  uID values 0
 * through 12 are reserved.  The CE page prints the CE-specific short
 * layout (no szInfo/uTimeout/uVersion members) and szTip as an
 * explicit WCHAR array. */
typedef struct _NOTIFYICONDATA {
    DWORD cbSize;              /* sizeof(NOTIFYICONDATA) */
    HWND  hWnd;                /* window receiving the notifications */
    UINT  uID;                 /* application-defined icon id (0-12 reserved) */
    UINT  uFlags;              /* NIF_* combination */
    UINT  uCallbackMessage;    /* application-defined callback message */
    HICON hIcon;               /* icon to add / modify / delete */
    WCHAR szTip[64];           /* tooltip text */
} NOTIFYICONDATA, *PNOTIFYICONDATA;

/* ms911889 uFlags values.  The CE page publishes the three names
 * without values; the desktop Win32 NOTIFYICONDATAA reference page
 * publishes the shared bit numbering, so the values below are carried
 * per the M52 derived-value policy (derivation path recorded in
 * docs/inventory.md M53). */
#define NIF_MESSAGE  0x00000001
#define NIF_ICON     0x00000002
#define NIF_TIP      0x00000004

/* aa453686 "Shell_NotifyIcon" (Windows CE 1.0 and later; Shellapi.h;
 * no Link Library row on the CE 5.0 page).  Adds, modifies or deletes
 * a taskbar status area icon.  dwMessage takes the NIM_* values below;
 * pnid points to the NOTIFYICONDATA descriptor.  Nonzero return =
 * success.  The page prints the WINSHELLAPI decoration. */
AKARI_CE_IMPORT BOOL WINAPI Shell_NotifyIcon(DWORD dwMessage,
                                              PNOTIFYICONDATA pnid) AKARI_CE_NAME(Shell_NotifyIcon);

/* aa453686 dwMessage values (desktop Shell_NotifyIcon reference page
 * numbering; M52 derived-value policy, path recorded in inventory). */
#define NIM_ADD      0x00000000
#define NIM_MODIFY   0x00000001
#define NIM_DELETE   0x00000002

/* ------------------------------------------------------------------ */
/* Standard Shell Reference (M53): ShellExecuteEx.                      */
/* ------------------------------------------------------------------ */

/* aa453685 "SHELLEXECUTEINFO" (Windows CE 1.0 and later; Shellapi.h).
 * Descriptor for ShellExecuteEx (the page prints the typedef tail
 * "SHELLEXECUTEINFO, FAR* LPSHELLEXECUTEINFO"; the FAR qualifier is
 * dropped per the established objbase.h pointer-qualifier note).
 * CE specifics published on the page:
 * lpDirectory is "Not supported. Set to zero."; lpIDList, lpClass,
 * hkeyClass, dwHotKey and the hIcon/hMonitor union are "Ignored"; the
 * fMask flags are unsupported on CE 1.0/1.01.  hInstApp receives an
 * instance handle or one of the SE_ERR_* values (<= 32) on failure. */
typedef struct _SHELLEXECUTEINFO {
    DWORD     cbSize;          /* sizeof(SHELLEXECUTEINFO) */
    ULONG     fMask;           /* SEE_MASK_* combination */
    HWND      hwnd;            /* parent for any message boxes */
    LPCTSTR   lpVerb;          /* verb: "edit" / "find" / "open" / "print" */
    LPCTSTR   lpFile;          /* fully qualified file name (no CWD on CE) */
    LPCTSTR   lpParameters;    /* parameters; NULL for documents */
    LPCTSTR   lpDirectory;     /* not supported; set to zero */
    int       nShow;           /* SW_* show flag */
    HINSTANCE hInstApp;        /* out: instance handle or SE_ERR_* */
    LPVOID    lpIDList;        /* ignored */
    LPCTSTR   lpClass;         /* ignored */
    HKEY      hkeyClass;       /* ignored */
    DWORD     dwHotKey;        /* ignored */
    union {
        HANDLE hIcon;          /* ignored */
        HANDLE hMonitor;       /* ignored */
    } DUMMYUNIONNAME;
    HANDLE    hProcess;        /* out: process handle (NOCLOSEPROCESS) */
} SHELLEXECUTEINFO, *LPSHELLEXECUTEINFO;

/* aa453685 fMask values (CE 2.0+; desktop SHELLEXECUTEINFOA reference
 * page numbering; M52 derived-value policy, path recorded in
 * inventory). */
#define SEE_MASK_NOCLOSEPROCESS  0x00000040
#define SEE_MASK_FLAG_NO_UI      0x00000400

/* aa453685 hInstApp failure values (desktop SHELLEXECUTEINFOA
 * reference page numbering; M52 derived-value policy). */
#define SE_ERR_FNF            2
#define SE_ERR_PNF            3
#define SE_ERR_ACCESSDENIED   5
#define SE_ERR_OOM            8
#define SE_ERR_SHARE         26
#define SE_ERR_ASSOCINCOMPLETE 27
#define SE_ERR_DDETIMEOUT    28
#define SE_ERR_DDEFAIL       29
#define SE_ERR_DDEBUSY       30
#define SE_ERR_NOASSOC       31
#define SE_ERR_DLLNOTFOUND   32

/* aa453684 "ShellExecuteEx" (Windows CE 1.0 and later; Shellapi.h;
 * Coredll.lib).  Performs an action (verb) on a file.  Nonzero return
 * = success.  The page prints the WINSHELLAPI decoration. */
AKARI_CE_IMPORT BOOL WINAPI ShellExecuteEx(LPSHELLEXECUTEINFO lpExecInfo) AKARI_CE_NAME(ShellExecuteEx);

/* ------------------------------------------------------------------ */
/* Standard Shell Reference (M53): file operations (SHFileOperation).   */
/* ------------------------------------------------------------------ */

/* aa453691 "SHFILEOPSTRUCT" (Windows CE .NET 4.2 and later;
 * Shellapi.h).  Descriptor for SHFileOperation.  pFrom / pTo are
 * double-null-terminated multi-path buffers (fully qualified paths
 * only; pTo rejects wildcards).  CE specifics: fAnyOperationsAborted
 * and hNameMappings are "Not supported"; lpszProgressTitle is used
 * only with FOF_SIMPLEPROGRESS.  FILEOP_FLAGS: the type name is
 * printed by the CE 5.0 and CE 6.0 (ee505480) syntax blocks and by the
 * desktop SHFILEOPSTRUCTA syntax block, but no official doc publishes
 * its width -- WORD is adopted here because it is layout-neutral at
 * this offset (a 16-bit fFlags plus alignment padding places
 * fAnyOperationsAborted at the same offset and yields the same
 * sizeof as a 32-bit member on both ARM and x86), recorded as a
 * width-held type in docs/inventory.md M53. */
typedef WORD FILEOP_FLAGS;
typedef struct _SHFILEOPSTRUCT {
    HWND           hwnd;                /* parent for status dialogs */
    UINT           wFunc;               /* FO_* operation */
    LPCWSTR        pFrom;               /* double-null-terminated sources */
    LPCWSTR        pTo;                 /* double-null-terminated targets */
    FILEOP_FLAGS   fFlags;              /* FOF_* combination */
    BOOL           fAnyOperationsAborted; /* not supported */
    LPVOID         hNameMappings;       /* not supported */
    LPCWSTR        lpszProgressTitle;   /* progress title (SIMPLEPROGRESS) */
} SHFILEOPSTRUCT, *LPSHFILEOPSTRUCT;

/* aa453691 wFunc values (names held: neither the CE pages nor the
 * desktop SHFILEOPSTRUCTA reference page publishes their values):
 *   FO_COPY, FO_DELETE, FO_MOVE, FO_RENAME
 * aa453691 fFlags values (names held, same analysis; "(ns)" marks the
 * members the CE page marks "Not supported"):
 *   FOF_ALLOWUNDO, FOF_FILESONLY (ns), FOF_MULTIDESTFILES (ns),
 *   FOF_NO_CONNECTED_ELEMENTS (ns), FOF_NOCONFIRMATION,
 *   FOF_NOCONFIRMMKDIR, FOF_NOCOPYSECURITYATTRIBS (ns),
 *   FOF_NOERRORUI, FOF_NORECURSION (ns), FOF_RENAMEONCOLLISION,
 *   FOF_SILENT, FOF_SIMPLEPROGRESS, FOF_WANTMAPPINGHANDLE (ns),
 *   FOF_WANTNUKEWARNING (ns)
 */

/* aa453690 "SHFileOperation" (Windows CE .NET 4.2 and later;
 * Shellapi.h; Ceshell.lib).  Copies, moves, renames or deletes file
 * system objects.  Returns zero on success.  Deleting a file named by
 * pFrom alone does not use the Recycle Bin even with FOF_ALLOWUNDO;
 * not thread-safe with relative paths (use fully qualified paths). */
AKARI_CE_IMPORT int SHFileOperation(LPSHFILEOPSTRUCT lpFileOp) AKARI_CE_NAME(SHFileOperation);

/* ------------------------------------------------------------------ */
/* Standard Shell Reference (M53): file-object information.             */
/* ------------------------------------------------------------------ */

/* aa453689 "SHFILEINFO" (Windows CE 1.0 and later; Shellapi.h).  File
 * object information retrieved by SHGetFileInfo. */
typedef struct _SHFILEINFO {
    HICON hIcon;                     /* icon handle (SHGFI_ICON) */
    int   iIcon;                     /* system image-list index */
    DWORD dwAttributes;              /* attributes (SHGFI_ATTRIBUTES) */
    TCHAR szDisplayName[MAX_PATH];   /* display name / icon location */
    TCHAR szTypeName[80];            /* type name description */
} SHFILEINFO;

/* aa453700 "SHGetFileInfo" (Windows CE 1.0 and later; Shellapi.h; no
 * Link Library row on the CE 5.0 page).  Retrieves information about
 * a file system object.  dwFileAttributes takes FILE_ATTRIBUTE_*
 * values and is honored only with SHGFI_USEFILEATTRIBUTES; the page
 * documents the CE additions FILE_ATTRIBUTE_INROM and
 * FILE_ATTRIBUTE_ROMMODULE (names recorded; values not published on
 * this page).  The uFlags values below follow the desktop
 * SHGetFileInfoW reference page numbering (M52 derived-value policy,
 * path recorded in docs/inventory.md M53).  SHGFI_SELECTICON (the
 * page's Windows Mobile-only selector) has no desktop counterpart and
 * is held.  The page prints the WINSHELLAPI decoration. */
AKARI_CE_IMPORT DWORD WINAPI SHGetFileInfo(LPCTSTR pszPath,
                                           DWORD dwFileAttributes,
                                           SHFILEINFO *psfi,
                                           UINT cbFileInfo,
                                           UINT uFlags) AKARI_CE_NAME(SHGetFileInfo);

#define SHGFI_LARGEICON         0x00000000
#define SHGFI_SMALLICON         0x00000001
#define SHGFI_OPENICON          0x00000002
#define SHGFI_SHELLICONSIZE     0x00000004
#define SHGFI_PIDL              0x00000008
#define SHGFI_USEFILEATTRIBUTES 0x00000010
#define SHGFI_ICON              0x00000100
#define SHGFI_DISPLAYNAME       0x00000200
#define SHGFI_TYPENAME          0x00000400
#define SHGFI_ATTRIBUTES        0x00000800
#define SHGFI_ICONLOCATION      0x00001000
#define SHGFI_EXETYPE           0x00002000
#define SHGFI_SYSICONINDEX      0x00004000
#define SHGFI_LINKOVERLAY       0x00008000
#define SHGFI_SELECTED          0x00010000

/* ------------------------------------------------------------------ */
/* Standard Shell Reference (M53): PIDL-to-path, shortcuts, special
 * folders, bitmaps, out-of-memory box.                                 */
/* ------------------------------------------------------------------ */

/* aa453704 "SHGetPathFromIDList" (Windows CE 2.0 and later;
 * Shellapi.h; Ceshell.lib).  Converts an item identifier list to a
 * file system path; pszPath must be at least MAX_PATH characters.
 * The page prints the WINSHELLAPI decoration. */
AKARI_CE_IMPORT BOOL WINAPI SHGetPathFromIDList(LPCITEMIDLIST pidl,
                                                LPSTR pszPath) AKARI_CE_NAME(SHGetPathFromIDList);

/* aa453705 "SHGetShortcutTarget" (Windows CE 1.0 and later;
 * Shellapi.h; Coredll.lib).  Retrieves a shortcut's target path
 * (buffer at least cbMax characters). */
AKARI_CE_IMPORT BOOL SHGetShortcutTarget(LPTSTR szShortcut, LPTSTR szTarget,
                                         int cbMax) AKARI_CE_NAME(SHGetShortcutTarget);

/* aa453707 "SHGetSpecialFolderPath" (Windows CE 3.0 and later;
 * shellapi.h; coredll.lib).  Retrieves the path of the special folder
 * identified by nFolder (CSIDL_* values, shlobj.h); lpszPath must be
 * at least MAX_PATH characters.  In the standard shell returns TRUE
 * on success; with the AYGShell extensions the page documents a FALSE
 * return even on success (Pocket PC 2002 era). */
AKARI_CE_IMPORT BOOL SHGetSpecialFolderPath(HWND hwndOwner, LPTSTR lpszPath,
                                            int nFolder,
                                            BOOL fCreate) AKARI_CE_NAME(SHGetSpecialFolderPath);

/* aa453680 "SHCreateShortcut" (Windows CE 1.0 and later; Shellapi.h;
 * Coredll.lib).  Creates a shortcut.  The page prints the prototype
 * "DWORD WINAPI SHCreateShortcut(LPTSTR szShortcut, LPTSTR szTarget)"
 * and notes the function "is not prototyped correctly in Shellapi.h:
 * it returns a BOOL instead of a DWORD" (recorded verbatim); FALSE is
 * also returned when the shortcut already exists, and a NULL szShortcut
 * yields ERROR_INVALID_PARAMETER. */
AKARI_CE_IMPORT DWORD WINAPI SHCreateShortcut(LPTSTR szShortcut,
                                              LPTSTR szTarget) AKARI_CE_NAME(SHCreateShortcut);

/* aa453681 "SHCreateShortcutEx" (Windows CE .NET 4.2 and later;
 * Shellapi.h; Coredll.lib).  Creates a uniquely named shortcut in
 * lpszDir; szShortcut receives the name (NULL to skip) and
 * lpcbShortcut the maximum length / used length (NULL to skip).  The
 * page repeats the "not prototyped correctly ... returns a BOOL"
 * note. */
AKARI_CE_IMPORT DWORD WINAPI SHCreateShortcutEx(LPTSTR lpszDir, LPTSTR lpszTarget,
                                                LPTSTR szShortcut,
                                                LPDWORD lpcbShortcut) AKARI_CE_NAME(SHCreateShortcutEx);

/* aa453667 "SHAddToRecentDocs" (Windows CE 1.0 and later; Shellapi.h;
 * Coredll.lib).  Adds a document to the recent-documents list (or
 * clears the list when pv is NULL; CE caps the list at ten entries).
 * uFlags takes the SHARD_* selector names -- published without values
 * on every official page (CE 5.0, WM 6.5, desktop) and therefore held:
 *   SHARD_PATH  pv is the address of a path string
 *   SHARD_PIDL  pv is the address of an ITEMIDLIST (PIDL)
 * The page prints the WINSHELLAPI decoration. */
AKARI_CE_IMPORT void WINAPI SHAddToRecentDocs(UINT uFlags, LPCVOID pv) AKARI_CE_NAME(SHAddToRecentDocs);

/* aa453720 "SHLoadDIBitmap" (Windows CE 1.0 and later; Shellapi.h;
 * Coredll.lib).  Loads a device-independent bitmap from a file;
 * the caller deletes it with DeleteObject. */
AKARI_CE_IMPORT HBITMAP SHLoadDIBitmap(LPCTSTR szFileName) AKARI_CE_NAME(SHLoadDIBitmap);

/* aa453739 "SHShowOutOfMemory" (Windows CE 1.0 and later; Shellapi.h;
 * Shmisc.lib).  Displays the system-defined out-of-memory dialog box
 * (OEM helper); grfFlags is reserved and must be zero. */
AKARI_CE_IMPORT int SHShowOutOfMemory(HWND hwndOwner, UINT grfFlags) AKARI_CE_NAME(SHShowOutOfMemory);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_SHELLAPI_H */
