/*
 * wince-api: Clean-room Windows CE API implementation for LLVM/Clang
 * File: aygshell.h
 *
 * Windows CE Handheld / PocketPC Shell Extensions (aygshell).
 */

#ifndef _AYGSHELL_H_
#define _AYGSHELL_H_

#include <windows.h>
#include <sipapi.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Notification Structure */
typedef struct _SHNOTIFICATIONDATA {
    DWORD cbSize;
    DWORD dwID;
    SHANDLE_PTR hicon;
    DWORD clsid;
    DWORD grfFlags;
    UINT npPriority;
    CSSTR csTitle;
    CSSTR csHTML;
    HWND hwndCallback;
    LPARAM lParam;
} SHNOTIFICATIONDATA, *PSHNOTIFICATIONDATA;

/* Command Bar APIs */
HWND WINAPI CommandBar_Create(HINSTANCE hInst, HWND hwndParent, UINT idCmdBar);
BOOL WINAPI CommandBar_Show(HWND hwndCB, BOOL fShow);
BOOL WINAPI CommandBar_Destroy(HWND hwndCB);
BOOL WINAPI CommandBar_AddAdornments(HWND hwndCB, DWORD dwFlags, DWORD dwReserved);
HMENU WINAPI CommandBar_InsertMenubar(HWND hwndCB, HINSTANCE hInst, UINT idMenu, WORD iButton);

#define CDA_DONT_ADD_CLOSE  0x00000001

/* Full Screen Helper */
BOOL WINAPI SHFullScreen(HWND hwndRequester, DWORD dwState);

#define SHFS_SHOWTASKBAR    0x0001
#define SHFS_HIDETASKBAR    0x0002
#define SHFS_SHOWSIPBUTTON  0x0004
#define SHFS_HIDESIPBUTTON  0x0008
#define SHFS_SHOWSTARTICON  0x0010
#define SHFS_HIDESTARTICON  0x0020

#ifdef __cplusplus
}
#endif

#endif /* _AYGSHELL_H_ */
