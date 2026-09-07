/*
 * wingdi.h -- GDI declarations for Windows CE (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Spec basis: the official Microsoft Windows
 * CE documentation -- the CE 5.0-era "GDI Reference" pages of the
 * (v=msdn.10) archive (identifiers below) and their (v=winembedded.60)
 * CE 6.0 twins, which still carry whitespace-preserved prototypes.
 * No code from w32api, mingwrt, mingw32ce, MinGW-w64, Wine or any
 * other third-party tree appears here; each declaration below is
 * commented with the official page identifier it is derived from.
 *
 * Header-name note: the CE 5.0 archive's Requirement rows list
 * "Header: Windows.h" for the GDI items below (the CE 5.0 headers were
 * monolithic).  This substitute groups them in wingdi.h -- the
 * component header of the CE 6.0 era, and the header TEXTMETRIC's own
 * CE 5.0 page (ms901146) already names -- and include/windows.h
 * includes this file, so both "include <windows.h>" (CE 5 style) and
 * "include <wingdi.h>" (CE 6 style) compile the same surface.
 *
 * Conventions (see windef.h): Windows CE is Unicode-only; CE APIs are
 * __cdecl and Microsoft documents several prototypes below with
 * WINGDIAPI/WINAPI decorations that expand to nothing on CE targets,
 * so they are omitted here (noted per declaration).
 */

#ifndef AKARI_WINGDI_H
#define AKARI_WINGDI_H

#include "windef.h"
#include "winnt.h"     /* FLOAT, GUID */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Colors and color types                                             */
/* ------------------------------------------------------------------ */

/* ms928589 "COLORREF": 32-bit color value; the low-order byte is red
 * (0x00bbggrr).  CE 1.0+; Header Windows.h. */
typedef DWORD COLORREF;
typedef DWORD *LPCOLORREF;

/* ms929207 "GetBValue", ms929246 "GetGValue", aa453161 "GetRValue":
 * COLORREF byte accessors.  Each official CE page prints the macro
 * body verbatim ("The GetBValue macro is defined as follows") and
 * carries no Link Library row, so these are macros, not exports. */
#define GetRValue(rgb)  ((BYTE)(rgb))
#define GetGValue(rgb)  ((BYTE)(((WORD)(rgb)) >> 8))
#define GetBValue(rgb)  ((BYTE)((rgb) >> 16))

/* ms939815 "RGBQUAD": table entry used by DIB color tables. */
typedef struct tagRGBQUAD {
    BYTE rgbBlue;
    BYTE rgbGreen;
    BYTE rgbRed;
    BYTE rgbReserved;
} RGBQUAD;

/* ms939824 "RGBTRIPLE": 24-bit color entry of the OS/2-style
 * BITMAPCOREINFO table. */
typedef struct tagRGBTRIPLE {
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
} RGBTRIPLE;

/* ms911913 "PALETTEENTRY": single logical-palette entry. */
typedef struct tagPALETTEENTRY {
    BYTE peRed;
    BYTE peGreen;
    BYTE peBlue;
    BYTE peFlags;
} PALETTEENTRY, *PPALETTEENTRY, *LPPALETTEENTRY;

/* COLOR16: 16-bit color component used by TRIVERTEX (fixed Win32 ABI;
 * the CE GRADIENT_FILL/TRIVERTEX pages type the components COLOR16). */
typedef WORD COLOR16;

/* BCHAR/CCHDEVICENAME/CCHFORMNAME: DEVMODE naming constants (CE
 * DEVMODE page aa452943 prints dmDeviceName as WCHAR[CCHDEVICENAME]
 * and dmFormName as BCHAR[CCHFORMNAME]; on Unicode-only CE, BCHAR is
 * WCHAR).  The 32-slot sizes are the documented Win32 ABI values. */
typedef WCHAR BCHAR;
#define CCHDEVICENAME 32
#define CCHFORMNAME   32

/* ------------------------------------------------------------------ */
/* Bitmap structures (GDI Structures book)                            */
/* ------------------------------------------------------------------ */

/* aa452881 "BITMAPCOREHEADER": OS/2-compatible DIB header. */
typedef struct tagBITMAPCOREHEADER {
    DWORD bcSize;
    WORD  bcWidth;
    WORD  bcHeight;
    WORD  bcPlanes;
    WORD  bcBitCount;
} BITMAPCOREHEADER;

/* aa452885 "BITMAPINFOHEADER": DIB header (biBitCount/biCompression
 * are adjacent on the official page; the page's code block drops the
 * separating punctuation). */
typedef struct tagBITMAPINFOHEADER {
    DWORD biSize;
    LONG  biWidth;
    LONG  biHeight;
    WORD  biPlanes;
    WORD  biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG  biXPelsPerMeter;
    LONG  biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BITMAPINFOHEADER;

/* aa452883 "BITMAPFILEHEADER": BMP file header. */
typedef struct tagBITMAPFILEHEADER {
    WORD  bfType;
    DWORD bfSize;
    WORD  bfReserved1;
    WORD  bfReserved2;
    DWORD bfOffBits;
} BITMAPFILEHEADER;

/* aa452880 "BITMAP": logical bitmap descriptor. */
typedef struct tagBITMAP {
    LONG  bmType;
    LONG  bmWidth;
    LONG  bmHeight;
    LONG  bmWidthBytes;
    WORD  bmPlanes;
    WORD  bmBitsPixel;
    LPVOID bmBits;
} BITMAP;

/* aa452882 "BITMAPCOREINFO": OS/2-style DIB info. */
typedef struct _BITMAPCOREINFO {
    BITMAPCOREHEADER bmciHeader;
    RGBTRIPLE        bmciColors[1];
} BITMAPCOREINFO;

/* aa452884 "BITMAPINFO": DIB info (header + color table). */
typedef struct tagBITMAPINFO {
    BITMAPINFOHEADER bmiHeader;
    RGBQUAD          bmiColors[1];
} BITMAPINFO;

/* aa452953 "DIBSECTION": describe a section created by CreateDIBSection. */
typedef struct tagDIBSECTION {
    BITMAP           dsBm;
    BITMAPINFOHEADER dsBmih;
    DWORD            dsBitfields[3];
    HANDLE           dshSection;
    DWORD            dsOffset;
} DIBSECTION;

/* ------------------------------------------------------------------ */
/* Palette, brush and pen structures                                  */
/* ------------------------------------------------------------------ */

/* aa453419 "LOGPALETTE": logical color-palette header. */
typedef struct tagLOGPALETTE {
    WORD         palVersion;
    WORD         palNumEntries;
    PALETTEENTRY palPalEntry[1];
} LOGPALETTE;

/* aa453418 "LOGBRUSH": logical-brush descriptor. */
typedef struct tagLOGBRUSH {
    UINT     lbStyle;
    COLORREF lbColor;
    LONG     lbHatch;
} LOGBRUSH;

/* aa453420 "LOGPEN": logical-pen descriptor (lopnWidth is a POINT:
 * only its x member is used, as the pen width). */
typedef struct tagLOGPEN {
    UINT     lopnStyle;
    POINT    lopnWidth;
    COLORREF lopnColor;
} LOGPEN;

/* aa452889 "BLENDFUNCTION": alpha-blend control for AlphaBlend. */
typedef struct _BLENDFUNCTION {
    BYTE BlendOp;
    BYTE BlendFlags;
    BYTE SourceConstantAlpha;
    BYTE AlphaFormat;
} BLENDFUNCTION, *PBLENDFUNCTION, *LPBLENDFUNCTION;

/* ------------------------------------------------------------------ */
/* Gradient, display and device-mode structures                       */
/* ------------------------------------------------------------------ */

/* aa453818 "TRIVERTEX": vertex for GradientFill. */
typedef struct _TRIVERTEX {
    LONG    x;
    LONG    y;
    COLOR16 Red;
    COLOR16 Green;
    COLOR16 Blue;
    COLOR16 Alpha;
} TRIVERTEX, *PTRIVERTEX, *LPTRIVERTEX;

/* aa453193 "GRADIENT_RECT": triangle/rectangle index pair for
 * GradientFill (GDI+ header for the GRADIENT_FILL_* mode values is
 * used with ulMode). */
typedef struct _GRADIENT_RECT {
    ULONG UpperLeft;
    ULONG LowerRight;
} GRADIENT_RECT, *PGRADIENT_RECT;

/* aa452943 "DEVMODE": device-mode data (EnumDisplaySettings,
 * ChangeDisplaySettingsEx, CreateDC).  The page prints the struct tag
 * lowercase (_devicemode) and names both strings with the CE
 * Unicode-only types. */
typedef struct _devicemode {
    WCHAR dmDeviceName[CCHDEVICENAME];
    WORD  dmSpecVersion;
    WORD  dmDriverVersion;
    WORD  dmSize;
    WORD  dmDriverExtra;
    DWORD dmFields;
    short dmOrientation;
    short dmPaperSize;
    short dmPaperLength;
    short dmPaperWidth;
    short dmScale;
    short dmCopies;
    short dmDefaultSource;
    short dmPrintQuality;
    short dmColor;
    short dmDuplex;
    short dmYResolution;
    short dmTTOption;
    short dmCollate;
    BCHAR dmFormName[CCHFORMNAME];
    WORD  dmLogPixels;
    DWORD dmBitsPerPel;
    DWORD dmPelsWidth;
    DWORD dmPelsHeight;
    DWORD dmDisplayFlags;
    DWORD dmDisplayFrequency;
    DWORD dmDisplayOrientation;
} DEVMODE, *PDEVMODE, *LPDEVMODE;

/* aa452957 "DISPLAY_DEVICE": display-adapter descriptor returned by
 * EnumDisplayDevices.  CE .NET 4.2+; Header Windows.h. */
typedef struct _DISPLAY_DEVICE {
    DWORD  cb;
    WCHAR  DeviceName[32];
    WCHAR  DeviceString[128];
    DWORD  StateFlags;
    WCHAR  DeviceID[128];
    WCHAR  DeviceKey[128];
} DISPLAY_DEVICE, *PDISPLAY_DEVICE;

/* ------------------------------------------------------------------ */
/* Region structures                                                   */
/* ------------------------------------------------------------------ */

/* ms939847 "RGNDATAHEADER": header of the region data buffer used by
 * GetRegionData/ExtCreateRegion. */
typedef struct _RGNDATAHEADER {
    DWORD dwSize;
    DWORD iType;
    DWORD nCount;
    DWORD nRgnSize;
    RECT  rcBound;
} RGNDATAHEADER;

/* ms939837 "RGNDATA": region data buffer (rcBound in the header is in
 * logical units; region coordinates are 27-bit signed integers per the
 * ExtCreateRegion page aa453061). */
typedef struct _RGNDATA {
    RGNDATAHEADER rdh;
    char          Buffer[1];
} RGNDATA, *PRGNDATA, *LPRGNDATA;

/* ------------------------------------------------------------------ */
/* Transformation and font structures                                 */
/* ------------------------------------------------------------------ */

/* XFORM: 2x3 affine transform matrix used by ExtCreateRegion
 * (aa453061, "CONST XFORM* lpXform", [in] "Not supported; set to
 * NULL" on CE).  The CE archive documents no XFORM structure page, so
 * the fixed Win32 ABI body (six FLOATs) is provided; recorded in
 * docs/inventory.md. */
typedef struct _XFORM {
    FLOAT eM11;
    FLOAT eM12;
    FLOAT eM21;
    FLOAT eM22;
    FLOAT eDx;
    FLOAT eDy;
} XFORM;

/* PANOSE: font-classification numbers embedded in OUTLINETEXTMETRICW
 * (ms934025 names the member otmPanoseNumber PANOSE).  The CE archive
 * has no PANOSE page; the fixed Win32 ABI body (ten BYTEs) is
 * provided, recorded in docs/inventory.md. */
typedef struct tagPANOSE {
    BYTE bFamilyType;
    BYTE bSerifStyle;
    BYTE bWeight;
    BYTE bProportion;
    BYTE bContrast;
    BYTE bStrokeVariation;
    BYTE bArmStyle;
    BYTE bLetterForm;
    BYTE bMidline;
    BYTE bXHeight;
} PANOSE;

/* TEXTMETRIC: physical-font metrics.  Official pages ms901146
 * (CE 5.0, Header Wingdi.h) / ms900735 (CE .NET) / ee489884 (CE 6.0);
 * the pages type the glyph members tmFirstChar..tmBreakChar as char. */
typedef struct tagTEXTMETRIC {
    LONG tmHeight;
    LONG tmAscent;
    LONG tmDescent;
    LONG tmInternalLeading;
    LONG tmExternalLeading;
    LONG tmAveCharWidth;
    LONG tmMaxCharWidth;
    LONG tmWeight;
    LONG tmOverhang;
    LONG tmDigitizedAspectX;
    LONG tmDigitizedAspectY;
    char tmFirstChar;
    char tmLastChar;
    char tmDefaultChar;
    char tmBreakChar;
    BYTE tmItalic;
    BYTE tmUnderlined;
    BYTE tmStruckOut;
    BYTE tmPitchAndFamily;
    BYTE tmCharSet;
} TEXTMETRIC;

/* ms934025 "OUTLINETEXTMETRICW": outline-font metrics (CE 5.0+;
 * Header Windows.h).  Text pointers are PSTR/char* on the page. */
typedef struct _OUTLINETEXTMETRICW {
    UINT  otmSize;
    TEXTMETRIC otmTextMetrics;
    BYTE  otmFiller;
    PANOSE otmPanoseNumber;
    UINT  otmfsSelection;
    UINT  otmfsType;
    int   otmsCharSlopeRise;
    int   otmsCharSlopeRun;
    int   otmItalicAngle;
    UINT  otmEMSquare;
    int   otmAscent;
    int   otmDescent;
    UINT  otmLineGap;
    UINT  otmsCapEmHeight;
    UINT  otmsXHeight;
    RECT  otmrcFontBox;
    int   otmMacAscent;
    int   otmMacDescent;
    UINT  otmMacLineGap;
    UINT  otmusMinimumPPEM;
    POINT otmptSubscriptSize;
    POINT otmptSubscriptOffset;
    POINT otmptSuperscriptSize;
    POINT otmptSuperscriptOffset;
    UINT  otmsStrikeoutSize;
    int   otmsStrikeoutPosition;
    int   otmsUnderscoreSize;
    int   otmsUnderscorePosition;
    PSTR  otmpFamilyName;
    PSTR  otmpFaceName;
    PSTR  otmpStyleName;
    PSTR  otmpFullName;
} OUTLINETEXTMETRICW, *POUTLINETEXTMETRICW, *LPOUTLINETEXTMETRICW;

/* ------------------------------------------------------------------ */
/* GDI Functions                                                      */
/*                                                                     */
/* Unless a declaration below says otherwise, its CE 5.0 Requirement   */
/* row is "Header: Windows.h.  Link Library: Coredll.lib."             */
/* ------------------------------------------------------------------ */

/* aa452850 "AlphaBlend" */
BOOL AlphaBlend(HDC hdcDest, int nXOriginDest, int nYOriginDest,
    int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc,
    int nYOriginSrc, int nWidthSrc, int nHeightSrc,
    BLENDFUNCTION blendFunction);
/* aa452879 "BitBlt" */
BOOL BitBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight,
    HDC hdcSrc, int nXSrc, int nYSrc, DWORD dwRop);
/* aa452930 "DeleteDC" */
BOOL DeleteDC(HDC hdc);
/* aa452933 "DeleteObject" */
BOOL DeleteObject(HGDIOBJ hObject);
/* aa452968 "DrawEdge" */
BOOL DrawEdge(HDC hdc, LPRECT qrc, UINT edge, UINT grfFlags);
/* aa452969 "DrawFocusRect" */
BOOL DrawFocusRect(HDC hDC, const RECT* lprc);
/* aa452997 "Ellipse" */
BOOL Ellipse(HDC hdc, int nLeftRect, int nTopRect, int nRightRect,
    int nBottomRect);
/* aa453048 "EnumDisplayDevices" */
BOOL EnumDisplayDevices(LPCTSTR lpDevice, DWORD iDevNum,
    PDISPLAY_DEVICE lpDisplayDevice, DWORD dwFlags);
/* aa453049 "EnumDisplaySettings" */
BOOL EnumDisplaySettings(LPCTSTR lpszDeviceName, DWORD iModeNum,
    LPDEVMODE lpDevMode);
/* aa453056 "EqualRgn" */
BOOL EqualRgn(HRGN hSrcRgn1, HRGN hSrcRgn2);
/* aa453058 "ExcludeClipRect" */
int ExcludeClipRect(HDC hdc, int nLeftRect, int nTopRect, int nRightRect,
    int nBottomRect);
/* aa453061 "ExtCreateRegion" */
HRGN ExtCreateRegion(CONST XFORM* lpXform, DWORD nCount,
    CONST RGNDATA* lpRgnData);
/* aa453063 "ExtEscape" */
int ExtEscape(HDC hdc, int nEscape, int cbInput, LPCSTR lpszInData,
    int cbOutput, LPSTR lpszOutData);
/* aa453067 "FillRect" */
int FillRect(HDC hDC, CONST RECT* lprc, HBRUSH hbr);
/* aa453068 "FillRgn" */
BOOL FillRgn(HDC hdc, HRGN hrgn, HBRUSH hbr);
/* aa453133 "GetLayout" */
DWORD GetLayout(HDC hdc);
/* aa453140 "GetNearestColor" */
COLORREF GetNearestColor(HDC hdc, COLORREF crColor);
/* aa453141 "GetNearestPaletteIndex" */
UINT GetNearestPaletteIndex(HPALETTE hpal, COLORREF crColor);
/* aa453147 "GetObject" */
int GetObject(HGDIOBJ hgdiobj, int cbBuffer, LPVOID lpvObject);
/* aa453148 "GetObjectType" */
DWORD GetObjectType(HGDIOBJ h);
/* aa453151 "GetPaletteEntries" */
UINT GetPaletteEntries(HPALETTE hpal, UINT iStartIndex, UINT nEntries,
    LPPALETTEENTRY lppe);
/* aa453153 "GetPixel" */
COLORREF GetPixel(HDC hdc, int nXPos, int nYPos);
/* aa453157 "GetRegionData" */
DWORD GetRegionData(HRGN hRgn, DWORD dwCount, LPRGNDATA lpRgnData);
/* aa453159 "GetRgnBox" */
int GetRgnBox(HRGN hrgn, LPRECT lprc);
/* aa453160 "GetROP2" */
int GetROP2(HDC hdc);
/* aa453164 "GetStockObject" */
HGDIOBJ GetStockObject(int fnObject);
/* aa453165 "GetStretchBltMode" */
int GetStretchBltMode(HDC hdc);
/* aa453168 "GetSysColorBrush" */
HBRUSH GetSysColorBrush(int nIndex);
/* aa453171 "GetSystemPaletteEntries" */
UINT GetSystemPaletteEntries(HDC hdc, UINT iStartIndex, UINT nEntries,
    LPPALETTEENTRY lppe);
/* aa453192 "GradientFill" */
BOOL GradientFill(HDC hdc, PTRIVERTEX pVertex, ULONG nVertex, PVOID pMesh,
    ULONG nCount, ULONG ulMode);
/* aa453296 "LineTo" (CE6 page renders "WINGDIAPI BOOL WINAPI"; CE ABI is __cdecl) */
BOOL LineTo(HDC hdc, int nXEnd, int nYEnd);
/* aa453602 "PtInRegion" */
BOOL PtInRegion(HRGN hrgn, int X, int Y);
/* aa453638 "RealizePalette" */
UINT RealizePalette(HDC hdc);
/* aa453646 "SetPixel" */
COLORREF SetPixel(HDC hdc, int X, int Y, COLORREF crColor);
/* aa453650 "SetRectRgn" */
BOOL SetRectRgn(HRGN hrgn, int nLeftRect, int nTopRect, int nRightRect,
    int nBottomRect);
/* aa453651 "SetROP2" */
int SetROP2(HDC hdc, int fnDrawMode);
/* aa453655 "SetStretchBltMode" */
int SetStretchBltMode(HDC hdc, int iStretchMode);
/* aa453660 "SetViewportOrgEx" (official page omits the return type in the prototype; Return Values "nonzero success / zero failure" => BOOL) */
BOOL SetViewportOrgEx(HDC hdc, int X, int Y, LPPOINT lpPoint);
/* aa453778 "TransparentBlt" (CE5/CE6 pages print the 8th parameter as "int hHeightDest" (sic); parameter is nHeightDest) */
BOOL TransparentBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest,
    int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc,
    int nYOriginSrc, int nWidthSrc, int nHeightSrc, UINT crTransparent);
/* aa453779 "TransparentImage" */
BOOL TransparentImage(HDC hdcDest, LONG DstX, LONG DstY, LONG DstCx,
    LONG DstCy, HANDLE hSrc, LONG SrcX, LONG SrcY, LONG SrcCx, LONG SrcCy,
    COLORREF TransparentColor);
/* aa453949 "GetViewportExtEx" (official page omits the return type in the prototype; Return Values "nonzero success / zero failure" => BOOL) */
BOOL GetViewportExtEx(HDC hdc, LPSIZE lpSize);
/* aa453950 "GetViewportOrgEx" (official page omits the return type in the prototype; Return Values "nonzero success / zero failure" => BOOL) */
BOOL GetViewportOrgEx(HDC hdc, LPPOINT lpPoint);
/* aa453951 "GetWindowExtEx" (official page omits the return type in the prototype; Return Values "nonzero success / zero failure" => BOOL) */
BOOL GetWindowExtEx(HDC hdc, LPSIZE lpSize);
/* aa453952 "GetWindowOrgEx" (official page omits the return type in the prototype; Return Values "nonzero success / zero failure" => BOOL) */
BOOL GetWindowOrgEx(HDC hdc, LPPOINT lpPoint);
/* aa453953 "OffsetViewportOrgEx" (official page omits the return type in the prototype; Return Values "nonzero success / zero failure" => BOOL) */
BOOL OffsetViewportOrgEx(HDC hdc, int nXOffset, int nYOffset,
    LPPOINT lpPoint);
/* aa453954 "SetWindowOrgEx" (official page omits the return type in the prototype; Return Values "nonzero success / zero failure" => BOOL) */
BOOL SetWindowOrgEx(HDC hdc, int X, int Y, LPPOINT lpPoint);
/* ms908108 "ChangeDisplaySettingsEx" */
LONG ChangeDisplaySettingsEx(LPCTSTR lpszDeviceName, LPDEVMODE lpDevMode,
    HWND hwnd, DWORD dwflags, LPVOID lParam);
/* ms908163 "CreateBitmap" */
HBITMAP CreateBitmap(int nWidth, int nHeight, UINT cPlanes, UINT cBitsPerPel,
    CONST VOID* lpvBits);
/* ms908165 "CreateCompatibleBitmap" */
HBITMAP CreateCompatibleBitmap(HDC hdc, int nWidth, int nHeight);
/* ms908166 "CreateCompatibleDC" */
HDC CreateCompatibleDC(HDC hdc);
/* ms908168 "CreateDC" */
HDC CreateDC(LPCTSTR lpszDriver, LPCTSTR lpszDevice, LPCTSTR lpszOutput,
    CONST DEVMODE* lpInitData);
/* ms908173 "CreateDIBPatternBrushPt" */
HBRUSH CreateDIBPatternBrushPt(const void* lpPackedDIB, UINT iUsage);
/* ms908174 "CreateDIBSection" */
HBITMAP CreateDIBSection(HDC hdc, const BITMAPINFO* pbmi, UINT iUsage,
    void** ppvBits, HANDLE hSection, DWORD dwOffset);
/* ms908178 "CreatePalette (GDI)" */
HPALETTE CreatePalette(CONST LOGPALETTE* lplgpl);
/* ms908179 "CreatePatternBrush" */
HBRUSH CreatePatternBrush(HBITMAP hbmp);
/* ms908180 "CreatePen" */
HPEN CreatePen(int fnPenStyle, int nWidth, COLORREF crColor);
/* ms908181 "CreatePenIndirect" */
HPEN CreatePenIndirect(const LOGPEN* lplgpn);
/* ms908184 "CreateRectRgn" */
HRGN CreateRectRgn(int nLeftRect, int nTopRect, int nRightRect,
    int nBottomRect);
/* ms908185 "CreateRectRgnIndirect" */
HRGN CreateRectRgnIndirect(const RECT* lprc);
/* ms908187 "CreateSolidBrush" */
HBRUSH CreateSolidBrush(COLORREF crColor);
/* ms909855 "IntersectClipRect" */
int IntersectClipRect(HDC hdc, int nLeftRect, int nTopRect, int nRightRect,
    int nBottomRect);
/* ms909858 "InvalidateRgn" (CE6 page renders "BOOL WINAPI"; CE ABI is __cdecl) */
BOOL InvalidateRgn(HWND hWnd, HRGN hRgn, BOOL fErase);
/* ms909859 "InvertRect" */
BOOL InvertRect(HDC hDC, CONST RECT* lprc);
/* ms911792 "MaskBlt" */
BOOL MaskBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight,
    HDC hdcSrc, int nXSrc, int nYSrc, HBITMAP hbmMask, int xMask, int yMask,
    DWORD dwRop);
/* ms911892 "OffsetRgn" */
int OffsetRgn(HRGN hrgn, int nXOffset, int nYOffset);
/* ms911916 "PatBlt" */
BOOL PatBlt(HDC hdc, int nXLeft, int nYLeft, int nWidth, int nHeight,
    DWORD dwRop);
/* ms911933 "Polygon" */
BOOL Polygon(HDC hdc, const POINT* lpPoints, int nCount);
/* ms911934 "Polyline" */
BOOL Polyline(HDC hdc, const POINT* lppt, int cPoints);
/* ms912947 "Rectangle" */
BOOL Rectangle(HDC hdc, int nLeftRect, int nTopRect, int nRightRect,
    int nBottomRect);
/* ms913051 "RectInRegion" */
BOOL RectInRegion(HRGN hrgn, const RECT* lprc);
/* ms913070 "RectVisible" */
BOOL RectVisible(HDC hdc, CONST RECT* lprc);
/* ms913080 "RedrawWindow" (CE6 page renders "BOOL WINAPI"; CE ABI is __cdecl) */
BOOL RedrawWindow(HWND hwnd, CONST RECT* lprcUpdate, HRGN hrgnUpdate,
    UINT flags);
/* ms914092 "ValidateRgn" (CE6 page renders "BOOL WINAPI"; CE ABI is __cdecl) */
BOOL ValidateRgn(HWND hWnd, HRGN hRgn);
/* ms928608 "CombineRgn" */
int CombineRgn(HRGN hrgnDest, HRGN hrgnSrc1, HRGN hrgnSrc2,
    int fnCombineMode);
/* ms929205 "GetBkColor" */
COLORREF GetBkColor(HDC hdc);
/* ms929206 "GetBkMode" */
int GetBkMode(HDC hdc);
/* ms929219 "GetClipBox" */
int GetClipBox(HDC hdc, LPRECT lprc);
/* ms929221 "GetClipRgn" */
int GetClipRgn(HDC hdc, HRGN hrgn);
/* ms929223 "GetCurrentObject" */
HGDIOBJ GetCurrentObject(HDC hdc, UINT uObjectType);
/* ms929224 "GetCurrentPositionEx" (CE6 page renders "WINGDIAPI BOOL WINAPI"; CE ABI is __cdecl, so no decoration) */
BOOL GetCurrentPositionEx(HDC hdc, LPPOINT lpPoint);
/* ms929230 "GetDeviceCaps" */
int GetDeviceCaps(HDC hdc, int nIndex);
/* ms929232 "GetDIBColorTable" (CE6 page renders "WINGDIAPI UINT WINAPI"; CE ABI is __cdecl) */
UINT GetDIBColorTable(HDC hdc, UINT uStartIndex, UINT cEntries,
    RGBQUAD* pColors);
/* ms931457 "MoveToEx" (CE6 page renders "WINGDIAPI BOOL WINAPI"; CE ABI is __cdecl) */
BOOL MoveToEx(HDC hdc, int X, int Y, LPPOINT lpPoint);
/* ms932714 "SelectClipRgn" */
int SelectClipRgn(HDC hdc, HRGN hrgn);
/* ms932715 "SelectObject" */
HGDIOBJ SelectObject(HDC hdc, HGDIOBJ hgdiobj);
/* ms932716 "SelectPalette" */
HPALETTE SelectPalette(HDC hdc, HPALETTE hpal, BOOL bForceBackground);
/* ms933897 "GetOutlineTextMetrics" */
UINT GetOutlineTextMetrics(HDC hdc, UINT cbData, LPOUTLINETEXTMETRICW lpOTM);
/* ms939800 "RestoreDC" */
BOOL RestoreDC(HDC hdc, int nSavedDC);
/* ms939867 "RoundRect" */
BOOL RoundRect(HDC hdc, int nLeftRect, int nTopRect, int nRightRect,
    int nBottomRect, int nWidth, int nHeight);
/* ms939894 "SaveDC" */
int SaveDC(HDC hdc);
/* ms939987 "SetBitmapBits" */
LONG SetBitmapBits(HBITMAP hbmp, DWORD cBytes, CONST VOID *lpBits);
/* ms939988 "SetBkColor" */
COLORREF SetBkColor(HDC hdc, COLORREF crColor);
/* ms939989 "SetBkMode" */
int SetBkMode(HDC hdc, int iBkMode);
/* ms940010 "SetBrushOrgEx" */
BOOL SetBrushOrgEx(HDC hdc, int nXOrg, int nYOrg, LPPOINT lppt);
/* ms940018 "SetDIBColorTable" (CE6 page renders "WINGDIAPI UINT WINAPI"; CE ABI is __cdecl) */
UINT SetDIBColorTable(HDC hdc, UINT uStartIndex, UINT cEntries,
    CONST RGBQUAD* pColor);
/* ms940019 "SetDIBitsToDevice" */
int SetDIBitsToDevice(HDC hdc, int XDest, int YDest, DWORD dwWidth,
    DWORD dwHeight, int XSrc, int YSrc, UINT uStartScan, UINT cScanLines,
    CONST VOID* lpvBits, CONST BITMAPINFO* lpbmi, UINT fuColorUse);
/* ms940026 "SetLayout" (page prints a stray trailing comma in the parameter list) */
DWORD SetLayout(HDC hdc, DWORD dwLayout);
/* ms940028 "SetPaletteEntries" */
UINT SetPaletteEntries(HPALETTE hpal, UINT iStart, UINT cEntries,
    CONST PALETTEENTRY* lppe);
/* ms940373 "StretchBlt" */
BOOL StretchBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest,
    int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc,
    int nYOriginSrc, int nWidthSrc, int nHeightSrc, DWORD dwRop);
/* ms940374 "StretchDIBits" (CE6 page renders "WINGDIAPI BOOL WINAPI"; CE ABI is __cdecl) */
BOOL StretchDIBits(HDC hdc, int XDest, int YDest, int nDestWidth,
    int nDestHeight, int XSrc, int YSrc, int nSrcWidth, int nSrcHeight,
    CONST VOID* lpBits, CONST BITMAPINFO* lpBitsInfo, UINT iUsage,
    DWORD dwRop);
#ifdef __cplusplus
}
#endif

#endif /* AKARI_WINGDI_H */
