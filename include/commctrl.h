/*
 * wince-api: Clean-room Windows CE API implementation for LLVM/Clang
 * File: commctrl.h
 *
 * Windows CE Common Controls definitions.
 */

#ifndef _COMMCTRL_H_
#define _COMMCTRL_H_

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Common Controls Initialization */
typedef struct tagINITCOMMONCONTROLSEX {
    DWORD dwSize;
    DWORD dwICC;
} INITCOMMONCONTROLSEX, *LPINITCOMMONCONTROLSEX;

#define ICC_LISTVIEW_CLASSES   0x00000001
#define ICC_TREEVIEW_CLASSES   0x00000002
#define ICC_BAR_CLASSES        0x00000004
#define ICC_TAB_CLASSES        0x00000008
#define ICC_UPDOWN_CLASS       0x00000010
#define ICC_PROGRESS_CLASS     0x00000020
#define ICC_DATE_CLASSES       0x00000100

BOOL WINAPI InitCommonControlsEx(const INITCOMMONCONTROLSEX *lpInitCtrls);
VOID WINAPI InitCommonControls(void);

#ifdef __cplusplus
}
#endif

#endif /* _COMMCTRL_H_ */
