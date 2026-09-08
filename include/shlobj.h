/*
 * shlobj.h -- shell object / file-change notification / folder browsing
 * layer for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  The AYGShell Reference and Standard Shell Reference books of the
 * CE 5.0 Shell documentation are the source books.
 *
 * Header homes, per the official Requirements rows:
 *   - WM_FILECHANGEINFO (aa453860): Header shlobj.h, Library ceshell.lib,
 *     Windows CE 3.0 and later.  The page prints the message shape
 *     (wParam reserved 0, lParam = FILECHANGENOTIFY*) but no numeric
 *     value, so the message identifier is held as a gap in
 *     docs/inventory.md rather than defined here.
 *   - FILECHANGENOTIFY (aa453066): the CE 5.0 main Requirements row
 *     prints the multi-header list "Commctrl.h, Prsht.h, Shlguid.h."
 *     (recorded verbatim; the Prsht.h/Shlguid.h homes belong to the
 *     unharvested Property Sheets / GUID books and the row carries no
 *     Link Library), while the page's Windows Mobile Requirements row
 *     and the WM_FILECHANGEINFO carrier message both name shlobj.h +     * ceshell.lib.  The structure is therefore co-located with its
 *     carrier message here (documented design decision); the CE 6.0
 *     twin ee500811 repeats the same multi-header list.
 *   - ITEMIDLIST (aa453244), BROWSEINFO (aa452901), BrowseCallbackProc
 *     (aa452900), SHBindToParent (aa453668), SHBrowseForFolder
 *     (aa453669), SHGetDesktopFolder (aa453697), SHGetMalloc (aa453702),
 *     SHGetSpecialFolderLocation (aa453706): Header Shlobj.h (the
 *     Standard Shell Reference book, M53).
 *   - SHGetDocumentsFolder (aa453698): the Requirements row prints the
 *     multi-header list "shlobj.h, commctrl.h" with Library ceshell.lib;
 *     the declaration is placed here (shlobj.h, first-listed home; the
 *     commctrl.h co-listing is recorded verbatim).
 *
 * Windows CE is Unicode-only; the notification strings referenced by the
 * event semantics are wide strings on CE.
 */

#ifndef AKARI_SHLOBJ_H
#define AKARI_SHLOBJ_H

#include "windef.h"   /* HWND, POINT, CALLBACK, LPTSTR, LPARAM */
#include "extfile.h"   /* FILECHANGEINFO (fci member) */
#include "shtypes.h"   /* SHITEMID (mkid member) */
#include "shobjidl.h"  /* IShellFolder, SFGAOF, SHGNO carriers */

#ifdef __cplusplus
extern "C" {
#endif

/* aa453066 "FILECHANGENOTIFY" (Windows CE .NET 4.2 and later).  The
 * structure pointed to by the lParam of the WM_FILECHANGEINFO message
 * the shell sends (SendNotifyMessage) to a window registered with
 * SHChangeNotifyRegister.  dwRefCount is internal ("should not be used
 * by applications"); fci details the file system change.  The window's
 * message processor must pass the pointer to SHChangeNotifyFree
 * (aygshell.h) -- failure leaks shell memory. */
typedef struct tagFILECHANGENOTIFY {
    DWORD          dwRefCount;   /* internal; not for application use */
    FILECHANGEINFO fci;
} FILECHANGENOTIFY;

/* aa453860 "WM_FILECHANGEINFO" (Windows CE 3.0 and later; shlobj.h,
 * ceshell.lib).  Sent by SendNotifyMessage from the shell to the window
 * registered with SHChangeNotifyRegister:
 *
 *     wParam : reserved for future use; must be 0
 *     lParam : pointer to a FILECHANGENOTIFY structure
 *
 * The page publishes no numeric message value (and WM_FILECHANGEINFO is
 * a CE shell message, not a fixed Win32 ABI identifier), so the name is
 * recorded here and held in docs/inventory.md. */

/* ------------------------------------------------------------------ */
/* Standard Shell Reference (M53): item identifier lists.              */
/* ------------------------------------------------------------------ */

/* aa453244 "ITEMIDLIST" (Windows CE 1.0 and later; Shlobj.h).  A list
 * of item identifiers: mkid is the open-ended SHITEMID array (the page
 * declares the single-element carrier).  LPITEMIDLIST /
 * LPCITEMIDLIST are the pointer spellings the function pages print. */
typedef struct _ITEMIDLIST {
    SHITEMID mkid;
} ITEMIDLIST, *LPITEMIDLIST;
typedef const ITEMIDLIST *LPCITEMIDLIST;

/* ------------------------------------------------------------------ */
/* Standard Shell Reference (M53): Browse For Folder dialog.           */
/* ------------------------------------------------------------------ */

/* aa452900 "BrowseCallbackProc" (Windows CE .NET 4.0 and later;
 * Shlobj.h; Ceshell.lib).  Application-defined callback notified by the
 * SHBrowseForFolder dialog.  uMsg carries the BFFM_INITIALIZED /
 * BFFM_SELCHANGED / BFFM_VALIDATEFAILED event names; the callback can
 * send BFFM_ENABLEOK / BFFM_SETSELECTION / BFFM_SETSTATUSTEXT back to
 * the dialog window.  The page prints the prototype
 * "int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam,
 * LPARAM lpData)" and always returns zero; the BFFCALLBACK typedef name
 * is the one printed by the BROWSEINFO syntax (no CE page publishes the
 * typedef body, so it is carried here as the pointer-to-callback
 * shape). */
typedef int (CALLBACK *BFFCALLBACK)(HWND hwnd, UINT uMsg,
                                    LPARAM lParam, LPARAM lpData);

/* aa452901 "BROWSEINFO" (Windows CE .NET 4.0 and later; Shlobj.h).
 * Parameters for SHBrowseForFolder.  pszDisplayName receives the
 * display name of the selected folder (assumed MAX_PATH bytes); ulFlags
 * combines the BIF_* options; lpfn is the BrowseCallbackProc callback
 * (may be NULL); iImage receives the system image-list index. */
typedef struct _browseinfo {
    HWND           hwndOwner;     /* owning window */
    LPCITEMIDLIST  pidlRoot;      /* root PIDL; NULL = namespace root */
    LPTSTR         pszDisplayName;/* out: display name buffer (MAX_PATH) */
    LPCTSTR        lpszTitle;     /* text above the tree control */
    UINT           ulFlags;       /* BIF_* combination */
    BFFCALLBACK    lpfn;          /* BrowseCallbackProc; may be NULL */
    LPARAM         lParam;        /* application value passed to lpfn */
    int            iImage;        /* out: image-list index */
} BROWSEINFO, *PBROWSEINFO, *LPBROWSEINFO;

/* aa452901 ulFlags values.  The CE 5.0 page publishes the three names
 * without values; the desktop Win32 BROWSEINFOA reference page
 * (shlobj_core.h) publishes the shared bit numbering, so the values
 * below are carried per the M52 derived-value policy (derivation path
 * recorded in docs/inventory.md M53). */
#define BIF_STATUSTEXT   0x0004
#define BIF_EDITBOX      0x0010
#define BIF_VALIDATE     0x0020

/* BFFM_* messages (aa452872..aa452877, Shlobj.h; BrowseCallbackProc
 * events and dialog messages; names held -- no CE, WM 6.5 or desktop
 * reference page publishes their numeric values):
 *   BFFM_INITIALIZED    lParam = 0
 *   BFFM_SELCHANGED     lParam = (LPITEMIDLIST) pidlSelected
 *   BFFM_VALIDATEFAILED lParam = (LPTSTR) lpszInvalid
 *   BFFM_ENABLEOK       wParam = 0; lParam = (LPARAM) fValid
 *   BFFM_SETSELECTION   wParam = (WPARAM) fPath; lParam = folder
 *   BFFM_SETSTATUSTEXT  wParam = 0; lParam = (LPARAM) szStatusText
 */

/* aa453669 "SHBrowseForFolder" (Windows CE .NET 4.0 and later;
 * Shlobj.h; Ceshell.lib).  Displays the folder-selection dialog box;
 * returns the PIDL of the selected folder (NULL = Cancel).  Call
 * InitCommonControls (commctrl.h book) first; free the returned PIDL
 * with the shell allocator (SHGetMalloc). */
AKARI_CE_IMPORT LPITEMIDLIST WINAPI SHBrowseForFolder(LPBROWSEINFO lpbi) AKARI_CE_NAME(SHBrowseForFolder);

/* aa453668 "SHBindToParent" (Windows CE .NET 4.2 and later; Shlobj.h;
 * Ceshell.lib).  Binds a fully qualified PIDL to its parent folder's
 * interface; *ppidlLast receives the child PIDL relative to the parent
 * (free with the shell allocator; NULL suppresses). */
AKARI_CE_IMPORT HRESULT SHBindToParent(LPCITEMIDLIST pidl, REFIID riid,
                                       VOID **ppv,
                                       LPCITEMIDLIST *ppidlLast) AKARI_CE_NAME(SHBindToParent);

/* aa453697 "SHGetDesktopFolder" (Windows CE .NET 4.2 and later;
 * Shlobj.h; Ceshell.lib).  Retrieves the IShellFolder interface of the
 * desktop folder (the namespace root); the caller Releases it. */
AKARI_CE_IMPORT HRESULT SHGetDesktopFolder(IShellFolder **ppshf) AKARI_CE_NAME(SHGetDesktopFolder);

/* aa453702 "SHGetMalloc" (Windows CE 2.12 and later; Shlobj.h;
 * Ceshell.lib).  Retrieves the shell's IMalloc allocator (used to
 * allocate/free PIDLs and STRRET strings; see objbase.h for the
 * interface record).  Returns NOERROR or E_FAIL. */
AKARI_CE_IMPORT HRESULT SHGetMalloc(LPMALLOC *ppMalloc) AKARI_CE_NAME(SHGetMalloc);

/* aa453706 "SHGetSpecialFolderLocation" (Windows CE 2.12 and later;
 * Shlobj.h; Ceshell.lib).  Retrieves the PIDL of a special folder;
 * nFolder takes a CSIDL_* value (below); free the PIDL with the shell
 * allocator.  Returns NOERROR or an OLE error. */
AKARI_CE_IMPORT HRESULT WINAPI SHGetSpecialFolderLocation(HWND hwndOwner,
                                                          int nFolder,
                                                          LPITEMIDLIST *ppidl) AKARI_CE_NAME(SHGetSpecialFolderLocation);

/* aa453698 "SHGetDocumentsFolder" (Windows CE 3.0 and later; shlobj.h,
 * commctrl.h; ceshell.lib).  Retrieves the documents-directory path for
 * the storage volume named by pszVolume; pszDocs must hold at least
 * MAX_PATH characters.  Returns FALSE when the volume has no documents
 * directory (e.g. no storage card inserted). */
AKARI_CE_IMPORT BOOL SHGetDocumentsFolder(LPCTSTR pszVolume,
                                          LPTSTR pszDocs) AKARI_CE_NAME(SHGetDocumentsFolder);

/* ------------------------------------------------------------------ */
/* CSIDL values (SHGetSpecialFolderLocation / SHGetSpecialFolderPath   */
/* nFolder parameter).  The CE 5.0 SHGetSpecialFolderLocation page     */
/* (aa453706) lists the 24 CSIDL names without values; the CE 5.0      */
/* SHGetSpecialFolderPath page (aa453707) prints a value table in its  */
/* Windows Mobile Remarks section -- the 15 constants below carry      */
/* those published values.  The remaining 9 names have no published    */
/* value in any official doc (the desktop CSIDL reference page is      */
/* valueless; the WM 6.5 documentation is valueless) and are held in   */
/* docs/inventory.md M53.                                             */
/* ------------------------------------------------------------------ */
#define CSIDL_DESKTOP           0x0000   /* aa453707 (virtual desktop root) */
#define CSIDL_PROGRAMS          0x0002
#define CSIDL_PERSONAL          0x0005
#define CSIDL_FAVORITES         0x0006
#define CSIDL_STARTUP           0x0007
#define CSIDL_RECENT            0x0008
#define CSIDL_DESKTOPDIRECTORY  0x0010
#define CSIDL_FONTS             0x0014
#define CSIDL_MYMUSIC           0x000D
#define CSIDL_MYVIDEO           0x000E
#define CSIDL_APPDATA           0x001A
#define CSIDL_WINDOWS           0x0024
#define CSIDL_PROGRAM_FILES     0x0026
#define CSIDL_MYPICTURES        0x0027
#define CSIDL_PROFILE           0x0028

/* CSIDL names listed on aa453706 whose values are held (no official
 * value table covers them; "Not supported" rows are on the CE page):
 *   CSIDL_BITBUCKET, CSIDL_CONTROLS (ns), CSIDL_DRIVES,
 *   CSIDL_NETHOOD (ns), CSIDL_NETWORK, CSIDL_PRINTERS (ns),
 *   CSIDL_SENDTO (ns), CSIDL_STARTMENU, CSIDL_TEMPLATES (ns)
 */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_SHLOBJ_H */
