/*
 * wince-api: Clean-room Windows CE API implementation for LLVM/Clang
 * File: wingdi.h
 *
 * Windows CE Graphics Device Interface (GDI) definitions.
 */

#ifndef _WINGDI_H_
#define _WINGDI_H_

#include <sdkddkver.h>
#include <windef.h>
#include <winnt.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef DWORD COLORREF;
#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#define GetRValue(rgb)      (LOBYTE(rgb))
#define GetGValue(rgb)      (LOBYTE(((WORD)(rgb)) >> 8))
#define GetBValue(rgb)      (LOBYTE((rgb)>>16))

/* Stock Objects */
#define WHITE_BRUSH         0
#define LTGRAY_BRUSH        1
#define GRAY_BRUSH          2
#define DKGRAY_BRUSH        3
#define BLACK_BRUSH         4
#define NULL_BRUSH          5
#define HOLLOW_BRUSH        NULL_BRUSH
#define WHITE_PEN           6
#define BLACK_PEN           7
#define NULL_PEN            8
#define SYSTEM_FONT         13
#define DEFAULT_GUI_FONT    17

HGDIOBJ WINAPI GetStockObject(int i);
HGDIOBJ WINAPI SelectObject(HDC hdc, HGDIOBJ h);
BOOL    WINAPI DeleteObject(HGDIOBJ ho);

COLORREF WINAPI SetTextColor(HDC hdc, COLORREF color);
COLORREF WINAPI SetBkColor(HDC hdc, COLORREF color);
int      WINAPI SetBkMode(HDC hdc, int mode);

#define OPAQUE      2
#define TRANSPARENT 1

BOOL WINAPI TextOutW(HDC hdc, int x, int y, LPCWSTR lpString, int c);
#define TextOut TextOutW

BOOL WINAPI Rectangle(HDC hdc, int left, int top, int right, int bottom);
BOOL WINAPI Ellipse(HDC hdc, int left, int top, int right, int bottom);

#ifdef __cplusplus
}
#endif

#endif /* _WINGDI_H_ */
