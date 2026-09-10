/*
 * Wingdi.h -- GDI declarations for Windows CE (Akari API).
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

#include "Windef.h"
#include "Winnt.h"     /* FLOAT, GUID */

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
typedef TEXTMETRIC *LPTEXTMETRIC;  /* GetTextMetrics ms901139 lptm */

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
AKARI_CE_IMPORT BOOL AlphaBlend(HDC hdcDest, int nXOriginDest, int nYOriginDest,
    int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc,
    int nYOriginSrc, int nWidthSrc, int nHeightSrc,
    BLENDFUNCTION blendFunction) AKARI_CE_NAME(AlphaBlend);
/* aa452879 "BitBlt" */
AKARI_CE_IMPORT BOOL BitBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight,
    HDC hdcSrc, int nXSrc, int nYSrc, DWORD dwRop) AKARI_CE_NAME(BitBlt);
/* aa452930 "DeleteDC" */
AKARI_CE_IMPORT BOOL DeleteDC(HDC hdc) AKARI_CE_NAME(DeleteDC);
/* aa452933 "DeleteObject" */
AKARI_CE_IMPORT BOOL DeleteObject(HGDIOBJ hObject) AKARI_CE_NAME(DeleteObject);
/* aa452968 "DrawEdge" */
AKARI_CE_IMPORT BOOL DrawEdge(HDC hdc, LPRECT qrc, UINT edge, UINT grfFlags) AKARI_CE_NAME(DrawEdge);
/* aa452969 "DrawFocusRect" */
AKARI_CE_IMPORT BOOL DrawFocusRect(HDC hDC, const RECT* lprc) AKARI_CE_NAME(DrawFocusRect);
/* aa452997 "Ellipse" */
AKARI_CE_IMPORT BOOL Ellipse(HDC hdc, int nLeftRect, int nTopRect, int nRightRect,
    int nBottomRect) AKARI_CE_NAME(Ellipse);
/* aa453048 "EnumDisplayDevices" */
AKARI_CE_IMPORT BOOL EnumDisplayDevices(LPCTSTR lpDevice, DWORD iDevNum,
    PDISPLAY_DEVICE lpDisplayDevice, DWORD dwFlags) AKARI_CE_NAME(EnumDisplayDevices);
/* aa453049 "EnumDisplaySettings" */
AKARI_CE_IMPORT BOOL EnumDisplaySettings(LPCTSTR lpszDeviceName, DWORD iModeNum,
    LPDEVMODE lpDevMode) AKARI_CE_NAME(EnumDisplaySettings);
/* aa453056 "EqualRgn" */
AKARI_CE_IMPORT BOOL EqualRgn(HRGN hSrcRgn1, HRGN hSrcRgn2) AKARI_CE_NAME(EqualRgn);
/* aa453058 "ExcludeClipRect" */
AKARI_CE_IMPORT int ExcludeClipRect(HDC hdc, int nLeftRect, int nTopRect, int nRightRect,
    int nBottomRect) AKARI_CE_NAME(ExcludeClipRect);
/* aa453061 "ExtCreateRegion" */
AKARI_CE_IMPORT HRGN ExtCreateRegion(CONST XFORM* lpXform, DWORD nCount,
    CONST RGNDATA* lpRgnData) AKARI_CE_NAME(ExtCreateRegion);
/* aa453063 "ExtEscape" */
AKARI_CE_IMPORT int ExtEscape(HDC hdc, int nEscape, int cbInput, LPCSTR lpszInData,
    int cbOutput, LPSTR lpszOutData) AKARI_CE_NAME(ExtEscape);
/* aa453067 "FillRect" */
AKARI_CE_IMPORT int FillRect(HDC hDC, CONST RECT* lprc, HBRUSH hbr) AKARI_CE_NAME(FillRect);
/* aa453068 "FillRgn" */
AKARI_CE_IMPORT BOOL FillRgn(HDC hdc, HRGN hrgn, HBRUSH hbr) AKARI_CE_NAME(FillRgn);
/* aa453133 "GetLayout" */
AKARI_CE_IMPORT DWORD GetLayout(HDC hdc) AKARI_CE_NAME(GetLayout);
/* aa453140 "GetNearestColor" */
AKARI_CE_IMPORT COLORREF GetNearestColor(HDC hdc, COLORREF crColor) AKARI_CE_NAME(GetNearestColor);
/* aa453141 "GetNearestPaletteIndex" */
AKARI_CE_IMPORT UINT GetNearestPaletteIndex(HPALETTE hpal, COLORREF crColor) AKARI_CE_NAME(GetNearestPaletteIndex);
/* aa453147 "GetObject" */
AKARI_CE_IMPORT int GetObject(HGDIOBJ hgdiobj, int cbBuffer, LPVOID lpvObject) AKARI_CE_NAME(GetObject);
/* aa453148 "GetObjectType" */
AKARI_CE_IMPORT DWORD GetObjectType(HGDIOBJ h) AKARI_CE_NAME(GetObjectType);
/* aa453151 "GetPaletteEntries" */
AKARI_CE_IMPORT UINT GetPaletteEntries(HPALETTE hpal, UINT iStartIndex, UINT nEntries,
    LPPALETTEENTRY lppe) AKARI_CE_NAME(GetPaletteEntries);
/* aa453153 "GetPixel" */
AKARI_CE_IMPORT COLORREF GetPixel(HDC hdc, int nXPos, int nYPos) AKARI_CE_NAME(GetPixel);
/* aa453157 "GetRegionData" */
AKARI_CE_IMPORT DWORD GetRegionData(HRGN hRgn, DWORD dwCount, LPRGNDATA lpRgnData) AKARI_CE_NAME(GetRegionData);
/* aa453159 "GetRgnBox" */
AKARI_CE_IMPORT int GetRgnBox(HRGN hrgn, LPRECT lprc) AKARI_CE_NAME(GetRgnBox);
/* aa453160 "GetROP2" */
AKARI_CE_IMPORT int GetROP2(HDC hdc) AKARI_CE_NAME(GetROP2);
/* aa453164 "GetStockObject" */
AKARI_CE_IMPORT HGDIOBJ GetStockObject(int fnObject) AKARI_CE_NAME(GetStockObject);
/* aa453165 "GetStretchBltMode" */
AKARI_CE_IMPORT int GetStretchBltMode(HDC hdc) AKARI_CE_NAME(GetStretchBltMode);
/* aa453168 "GetSysColorBrush" */
AKARI_CE_IMPORT HBRUSH GetSysColorBrush(int nIndex) AKARI_CE_NAME(GetSysColorBrush);
/* aa453656 "SetSysColors": its prototype takes CONST COLORREF*, so it is
 * declared with the GDI types here even though the official page prints
 * Header: Winuser.h (COLORREF lives with the GDI types; the header
 * layout deviation is recorded in docs/inventory.md).  Link Library row
 * Winmgr.lib (def/winmgr-doc.def). */
AKARI_CE_IMPORT BOOL SetSysColors(int cElements, CONST INT* lpaElements,
                  CONST COLORREF* lpaRgbValues) AKARI_CE_NAME(SetSysColors);
/* aa453171 "GetSystemPaletteEntries" */
AKARI_CE_IMPORT UINT GetSystemPaletteEntries(HDC hdc, UINT iStartIndex, UINT nEntries,
    LPPALETTEENTRY lppe) AKARI_CE_NAME(GetSystemPaletteEntries);
/* aa453192 "GradientFill" */
AKARI_CE_IMPORT BOOL GradientFill(HDC hdc, PTRIVERTEX pVertex, ULONG nVertex, PVOID pMesh,
    ULONG nCount, ULONG ulMode) AKARI_CE_NAME(GradientFill);
/* aa453296 "LineTo" (CE6 page renders "WINGDIAPI BOOL WINAPI"; CE ABI is __cdecl) */
AKARI_CE_IMPORT BOOL LineTo(HDC hdc, int nXEnd, int nYEnd) AKARI_CE_NAME(LineTo);
/* aa453602 "PtInRegion" */
AKARI_CE_IMPORT BOOL PtInRegion(HRGN hrgn, int X, int Y) AKARI_CE_NAME(PtInRegion);
/* aa453638 "RealizePalette" */
AKARI_CE_IMPORT UINT RealizePalette(HDC hdc) AKARI_CE_NAME(RealizePalette);
/* aa453646 "SetPixel" */
AKARI_CE_IMPORT COLORREF SetPixel(HDC hdc, int X, int Y, COLORREF crColor) AKARI_CE_NAME(SetPixel);
/* aa453650 "SetRectRgn" */
AKARI_CE_IMPORT BOOL SetRectRgn(HRGN hrgn, int nLeftRect, int nTopRect, int nRightRect,
    int nBottomRect) AKARI_CE_NAME(SetRectRgn);
/* aa453651 "SetROP2" */
AKARI_CE_IMPORT int SetROP2(HDC hdc, int fnDrawMode) AKARI_CE_NAME(SetROP2);
/* aa453655 "SetStretchBltMode" */
AKARI_CE_IMPORT int SetStretchBltMode(HDC hdc, int iStretchMode) AKARI_CE_NAME(SetStretchBltMode);
/* aa453660 "SetViewportOrgEx" (official page omits the return type in the prototype; Return Values "nonzero success / zero failure" => BOOL) */
AKARI_CE_IMPORT BOOL SetViewportOrgEx(HDC hdc, int X, int Y, LPPOINT lpPoint) AKARI_CE_NAME(SetViewportOrgEx);
/* aa453778 "TransparentBlt" (CE5/CE6 pages print the 8th parameter as "int hHeightDest" (sic); parameter is nHeightDest) */
AKARI_CE_IMPORT BOOL TransparentBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest,
    int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc,
    int nYOriginSrc, int nWidthSrc, int nHeightSrc, UINT crTransparent) AKARI_CE_NAME(TransparentBlt);
/* aa453779 "TransparentImage" */
AKARI_CE_IMPORT BOOL TransparentImage(HDC hdcDest, LONG DstX, LONG DstY, LONG DstCx,
    LONG DstCy, HANDLE hSrc, LONG SrcX, LONG SrcY, LONG SrcCx, LONG SrcCy,
    COLORREF TransparentColor) AKARI_CE_NAME(TransparentImage);
/* aa453949 "GetViewportExtEx" (official page omits the return type in the prototype; Return Values "nonzero success / zero failure" => BOOL) */
AKARI_CE_IMPORT BOOL GetViewportExtEx(HDC hdc, LPSIZE lpSize) AKARI_CE_NAME(GetViewportExtEx);
/* aa453950 "GetViewportOrgEx" (official page omits the return type in the prototype; Return Values "nonzero success / zero failure" => BOOL) */
AKARI_CE_IMPORT BOOL GetViewportOrgEx(HDC hdc, LPPOINT lpPoint) AKARI_CE_NAME(GetViewportOrgEx);
/* aa453951 "GetWindowExtEx" (official page omits the return type in the prototype; Return Values "nonzero success / zero failure" => BOOL) */
AKARI_CE_IMPORT BOOL GetWindowExtEx(HDC hdc, LPSIZE lpSize) AKARI_CE_NAME(GetWindowExtEx);
/* aa453952 "GetWindowOrgEx" (official page omits the return type in the prototype; Return Values "nonzero success / zero failure" => BOOL) */
AKARI_CE_IMPORT BOOL GetWindowOrgEx(HDC hdc, LPPOINT lpPoint) AKARI_CE_NAME(GetWindowOrgEx);
/* aa453953 "OffsetViewportOrgEx" (official page omits the return type in the prototype; Return Values "nonzero success / zero failure" => BOOL) */
AKARI_CE_IMPORT BOOL OffsetViewportOrgEx(HDC hdc, int nXOffset, int nYOffset,
    LPPOINT lpPoint) AKARI_CE_NAME(OffsetViewportOrgEx);
/* aa453954 "SetWindowOrgEx" (official page omits the return type in the prototype; Return Values "nonzero success / zero failure" => BOOL) */
AKARI_CE_IMPORT BOOL SetWindowOrgEx(HDC hdc, int X, int Y, LPPOINT lpPoint) AKARI_CE_NAME(SetWindowOrgEx);
/* ms908108 "ChangeDisplaySettingsEx" */
AKARI_CE_IMPORT LONG ChangeDisplaySettingsEx(LPCTSTR lpszDeviceName, LPDEVMODE lpDevMode,
    HWND hwnd, DWORD dwflags, LPVOID lParam) AKARI_CE_NAME(ChangeDisplaySettingsEx);
/* ms908163 "CreateBitmap" */
AKARI_CE_IMPORT HBITMAP CreateBitmap(int nWidth, int nHeight, UINT cPlanes, UINT cBitsPerPel,
    CONST VOID* lpvBits) AKARI_CE_NAME(CreateBitmap);
/* ms908165 "CreateCompatibleBitmap" */
AKARI_CE_IMPORT HBITMAP CreateCompatibleBitmap(HDC hdc, int nWidth, int nHeight) AKARI_CE_NAME(CreateCompatibleBitmap);
/* ms908166 "CreateCompatibleDC" */
AKARI_CE_IMPORT HDC CreateCompatibleDC(HDC hdc) AKARI_CE_NAME(CreateCompatibleDC);
/* ms908168 "CreateDC" */
AKARI_CE_IMPORT HDC CreateDC(LPCTSTR lpszDriver, LPCTSTR lpszDevice, LPCTSTR lpszOutput,
    CONST DEVMODE* lpInitData) AKARI_CE_NAME(CreateDC);
/* ms908173 "CreateDIBPatternBrushPt" */
AKARI_CE_IMPORT HBRUSH CreateDIBPatternBrushPt(const void* lpPackedDIB, UINT iUsage) AKARI_CE_NAME(CreateDIBPatternBrushPt);
/* ms908174 "CreateDIBSection" */
AKARI_CE_IMPORT HBITMAP CreateDIBSection(HDC hdc, const BITMAPINFO* pbmi, UINT iUsage,
    void** ppvBits, HANDLE hSection, DWORD dwOffset) AKARI_CE_NAME(CreateDIBSection);
/* ms908178 "CreatePalette (GDI)" */
AKARI_CE_IMPORT HPALETTE CreatePalette(CONST LOGPALETTE* lplgpl) AKARI_CE_NAME(CreatePalette);
/* ms908179 "CreatePatternBrush" */
AKARI_CE_IMPORT HBRUSH CreatePatternBrush(HBITMAP hbmp) AKARI_CE_NAME(CreatePatternBrush);
/* ms908180 "CreatePen" */
AKARI_CE_IMPORT HPEN CreatePen(int fnPenStyle, int nWidth, COLORREF crColor) AKARI_CE_NAME(CreatePen);
/* ms908181 "CreatePenIndirect" */
AKARI_CE_IMPORT HPEN CreatePenIndirect(const LOGPEN* lplgpn) AKARI_CE_NAME(CreatePenIndirect);
/* ms908184 "CreateRectRgn" */
AKARI_CE_IMPORT HRGN CreateRectRgn(int nLeftRect, int nTopRect, int nRightRect,
    int nBottomRect) AKARI_CE_NAME(CreateRectRgn);
/* ms908185 "CreateRectRgnIndirect" */
AKARI_CE_IMPORT HRGN CreateRectRgnIndirect(const RECT* lprc) AKARI_CE_NAME(CreateRectRgnIndirect);
/* ms908187 "CreateSolidBrush" */
AKARI_CE_IMPORT HBRUSH CreateSolidBrush(COLORREF crColor) AKARI_CE_NAME(CreateSolidBrush);
/* ms909855 "IntersectClipRect" */
AKARI_CE_IMPORT int IntersectClipRect(HDC hdc, int nLeftRect, int nTopRect, int nRightRect,
    int nBottomRect) AKARI_CE_NAME(IntersectClipRect);
/* ms909858 "InvalidateRgn" (CE6 page renders "BOOL WINAPI"; CE ABI is __cdecl) */
AKARI_CE_IMPORT BOOL InvalidateRgn(HWND hWnd, HRGN hRgn, BOOL fErase) AKARI_CE_NAME(InvalidateRgn);
/* ms909859 "InvertRect" */
AKARI_CE_IMPORT BOOL InvertRect(HDC hDC, CONST RECT* lprc) AKARI_CE_NAME(InvertRect);
/* ms911792 "MaskBlt" */
AKARI_CE_IMPORT BOOL MaskBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight,
    HDC hdcSrc, int nXSrc, int nYSrc, HBITMAP hbmMask, int xMask, int yMask,
    DWORD dwRop) AKARI_CE_NAME(MaskBlt);
/* ms911892 "OffsetRgn" */
AKARI_CE_IMPORT int OffsetRgn(HRGN hrgn, int nXOffset, int nYOffset) AKARI_CE_NAME(OffsetRgn);
/* ms911916 "PatBlt" */
AKARI_CE_IMPORT BOOL PatBlt(HDC hdc, int nXLeft, int nYLeft, int nWidth, int nHeight,
    DWORD dwRop) AKARI_CE_NAME(PatBlt);
/* ms911933 "Polygon" */
AKARI_CE_IMPORT BOOL Polygon(HDC hdc, const POINT* lpPoints, int nCount) AKARI_CE_NAME(Polygon);
/* ms911934 "Polyline" */
AKARI_CE_IMPORT BOOL Polyline(HDC hdc, const POINT* lppt, int cPoints) AKARI_CE_NAME(Polyline);
/* ms912947 "Rectangle" */
AKARI_CE_IMPORT BOOL Rectangle(HDC hdc, int nLeftRect, int nTopRect, int nRightRect,
    int nBottomRect) AKARI_CE_NAME(Rectangle);
/* ms913051 "RectInRegion" */
AKARI_CE_IMPORT BOOL RectInRegion(HRGN hrgn, const RECT* lprc) AKARI_CE_NAME(RectInRegion);
/* ms913070 "RectVisible" */
AKARI_CE_IMPORT BOOL RectVisible(HDC hdc, CONST RECT* lprc) AKARI_CE_NAME(RectVisible);
/* ms913080 "RedrawWindow" (CE6 page renders "BOOL WINAPI"; CE ABI is __cdecl) */
AKARI_CE_IMPORT BOOL RedrawWindow(HWND hwnd, CONST RECT* lprcUpdate, HRGN hrgnUpdate,
    UINT flags) AKARI_CE_NAME(RedrawWindow);
/* ms914092 "ValidateRgn" (CE6 page renders "BOOL WINAPI"; CE ABI is __cdecl) */
AKARI_CE_IMPORT BOOL ValidateRgn(HWND hWnd, HRGN hRgn) AKARI_CE_NAME(ValidateRgn);
/* ms928608 "CombineRgn" */
AKARI_CE_IMPORT int CombineRgn(HRGN hrgnDest, HRGN hrgnSrc1, HRGN hrgnSrc2,
    int fnCombineMode) AKARI_CE_NAME(CombineRgn);
/* ms929205 "GetBkColor" */
AKARI_CE_IMPORT COLORREF GetBkColor(HDC hdc) AKARI_CE_NAME(GetBkColor);
/* ms929206 "GetBkMode" */
AKARI_CE_IMPORT int GetBkMode(HDC hdc) AKARI_CE_NAME(GetBkMode);
/* ms929219 "GetClipBox" */
AKARI_CE_IMPORT int GetClipBox(HDC hdc, LPRECT lprc) AKARI_CE_NAME(GetClipBox);
/* ms929221 "GetClipRgn" */
AKARI_CE_IMPORT int GetClipRgn(HDC hdc, HRGN hrgn) AKARI_CE_NAME(GetClipRgn);
/* ms929223 "GetCurrentObject" */
AKARI_CE_IMPORT HGDIOBJ GetCurrentObject(HDC hdc, UINT uObjectType) AKARI_CE_NAME(GetCurrentObject);
/* ms929224 "GetCurrentPositionEx" (CE6 page renders "WINGDIAPI BOOL WINAPI"; CE ABI is __cdecl, so no decoration) */
AKARI_CE_IMPORT BOOL GetCurrentPositionEx(HDC hdc, LPPOINT lpPoint) AKARI_CE_NAME(GetCurrentPositionEx);
/* ms929230 "GetDeviceCaps" */
AKARI_CE_IMPORT int GetDeviceCaps(HDC hdc, int nIndex) AKARI_CE_NAME(GetDeviceCaps);
/* ms929232 "GetDIBColorTable" (CE6 page renders "WINGDIAPI UINT WINAPI"; CE ABI is __cdecl) */
AKARI_CE_IMPORT UINT GetDIBColorTable(HDC hdc, UINT uStartIndex, UINT cEntries,
    RGBQUAD* pColors) AKARI_CE_NAME(GetDIBColorTable);
/* ms931457 "MoveToEx" (CE6 page renders "WINGDIAPI BOOL WINAPI"; CE ABI is __cdecl) */
AKARI_CE_IMPORT BOOL MoveToEx(HDC hdc, int X, int Y, LPPOINT lpPoint) AKARI_CE_NAME(MoveToEx);
/* ms932714 "SelectClipRgn" */
AKARI_CE_IMPORT int SelectClipRgn(HDC hdc, HRGN hrgn) AKARI_CE_NAME(SelectClipRgn);
/* ms932715 "SelectObject" */
AKARI_CE_IMPORT HGDIOBJ SelectObject(HDC hdc, HGDIOBJ hgdiobj) AKARI_CE_NAME(SelectObject);
/* ms932716 "SelectPalette" */
AKARI_CE_IMPORT HPALETTE SelectPalette(HDC hdc, HPALETTE hpal, BOOL bForceBackground) AKARI_CE_NAME(SelectPalette);
/* ms933897 "GetOutlineTextMetrics" */
AKARI_CE_IMPORT UINT GetOutlineTextMetrics(HDC hdc, UINT cbData, LPOUTLINETEXTMETRICW lpOTM) AKARI_CE_NAME(GetOutlineTextMetrics);
/* ms939800 "RestoreDC" */
AKARI_CE_IMPORT BOOL RestoreDC(HDC hdc, int nSavedDC) AKARI_CE_NAME(RestoreDC);
/* ms939867 "RoundRect" */
AKARI_CE_IMPORT BOOL RoundRect(HDC hdc, int nLeftRect, int nTopRect, int nRightRect,
    int nBottomRect, int nWidth, int nHeight) AKARI_CE_NAME(RoundRect);
/* ms939894 "SaveDC" */
AKARI_CE_IMPORT int SaveDC(HDC hdc) AKARI_CE_NAME(SaveDC);
/* ms939987 "SetBitmapBits" */
AKARI_CE_IMPORT LONG SetBitmapBits(HBITMAP hbmp, DWORD cBytes, CONST VOID *lpBits) AKARI_CE_NAME(SetBitmapBits);
/* ms939988 "SetBkColor" */
AKARI_CE_IMPORT COLORREF SetBkColor(HDC hdc, COLORREF crColor) AKARI_CE_NAME(SetBkColor);
/* ms939989 "SetBkMode" */
AKARI_CE_IMPORT int SetBkMode(HDC hdc, int iBkMode) AKARI_CE_NAME(SetBkMode);
/* ms940010 "SetBrushOrgEx" */
AKARI_CE_IMPORT BOOL SetBrushOrgEx(HDC hdc, int nXOrg, int nYOrg, LPPOINT lppt) AKARI_CE_NAME(SetBrushOrgEx);
/* ms940018 "SetDIBColorTable" (CE6 page renders "WINGDIAPI UINT WINAPI"; CE ABI is __cdecl) */
AKARI_CE_IMPORT UINT SetDIBColorTable(HDC hdc, UINT uStartIndex, UINT cEntries,
    CONST RGBQUAD* pColor) AKARI_CE_NAME(SetDIBColorTable);
/* ms940019 "SetDIBitsToDevice" */
AKARI_CE_IMPORT int SetDIBitsToDevice(HDC hdc, int XDest, int YDest, DWORD dwWidth,
    DWORD dwHeight, int XSrc, int YSrc, UINT uStartScan, UINT cScanLines,
    CONST VOID* lpvBits, CONST BITMAPINFO* lpbmi, UINT fuColorUse) AKARI_CE_NAME(SetDIBitsToDevice);
/* ms940026 "SetLayout" (page prints a stray trailing comma in the parameter list) */
AKARI_CE_IMPORT DWORD SetLayout(HDC hdc, DWORD dwLayout) AKARI_CE_NAME(SetLayout);
/* ms940028 "SetPaletteEntries" */
AKARI_CE_IMPORT UINT SetPaletteEntries(HPALETTE hpal, UINT iStart, UINT cEntries,
    CONST PALETTEENTRY* lppe) AKARI_CE_NAME(SetPaletteEntries);
/* ms940373 "StretchBlt" */
AKARI_CE_IMPORT BOOL StretchBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest,
    int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc,
    int nYOriginSrc, int nWidthSrc, int nHeightSrc, DWORD dwRop) AKARI_CE_NAME(StretchBlt);
/* ms940374 "StretchDIBits" (CE6 page renders "WINGDIAPI BOOL WINAPI"; CE ABI is __cdecl) */
AKARI_CE_IMPORT BOOL StretchDIBits(HDC hdc, int XDest, int YDest, int nDestWidth,
    int nDestHeight, int XSrc, int YSrc, int nSrcWidth, int nSrcHeight,
    CONST VOID* lpBits, CONST BITMAPINFO* lpBitsInfo, UINT iUsage,
    DWORD dwRop) AKARI_CE_NAME(StretchDIBits);

/* ------------------------------------------------------------------ */
/* M28: Printing Reference (Header: Wingdi.h, Link Library Mgprint.lib */
/* per the CE 5.0 pages) and the extended dialog-template structures   */
/* (their pages list Header: Wingdi.h).                                */
/* ------------------------------------------------------------------ */

/* aa452964 "DOCINFO": input to StartDoc.  CE 2.0+; Wingdi.h.  The CE
 * page marks lpszDatatype and fwType as unsupported (set to zero). */
typedef struct {
    int      cbSize;        /* sizeof(DOCINFO) */
    LPCTSTR  lpszDocName;
    LPCTSTR  lpszOutput;    /* output-file name, or NULL for the device */
    LPCTSTR  lpszDatatype;  /* unsupported; set to zero */
    DWORD    fwType;        /* unsupported; set to zero */
} DOCINFO;

/* aa452836 "AbortProc": abort callback installed by SetAbortProc; the
 * page documents BOOL CALLBACK AbortProc(HDC, int). */
typedef BOOL (CALLBACK *ABORTPROC)(HDC hdc, int iError);

/* Printing functions (CE 2.0+; Wingdi.h; Mgprint.lib). */
AKARI_CE_IMPORT int  AbortDoc(HDC hdc) AKARI_CE_NAME(AbortDoc);                          /* aa452835 */
AKARI_CE_IMPORT int  EndDoc(HDC hdc) AKARI_CE_NAME(EndDoc);                            /* aa453039 */
AKARI_CE_IMPORT int  EndPage(HDC hdc) AKARI_CE_NAME(EndPage);                           /* aa453040 */
AKARI_CE_IMPORT int  SetAbortProc(HDC hdc, ABORTPROC lpAbortProc) AKARI_CE_NAME(SetAbortProc); /* ms939985 */
AKARI_CE_IMPORT int  StartDoc(HDC hdc, CONST DOCINFO* lpdi) AKARI_CE_NAME(StartDoc);     /* ms940349 */
AKARI_CE_IMPORT int  StartPage(HDC hDC) AKARI_CE_NAME(StartPage);                         /* ms940350 */

/* aa452959 "DLGITEMTEMPLATEEX" / aa452961 "DLGTEMPLATEEX": the extended
 * in-memory dialog template format (CreateDialogIndirectParam /
 * DialogBoxIndirectParam).  Both official pages state the structures
 * are "not defined in any standard header file" and print Header:
 * Wingdi.h; the variable-length arrays (windowClass / title / menu /
 * font, and sz_Or_Ord placeholders) follow each fixed header in
 * memory, so only the fixed prefix is typed here.  CE 2.0+. */
typedef struct {
    DWORD helpID;
    DWORD dwExtendedStyle;
    DWORD style;
    short x;
    short y;
    short cx;
    short cy;
    WORD  id;
} DLGITEMTEMPLATEEX;

typedef struct {
    WORD  dlgVer;          /* must be 1 */
    WORD  signature;       /* 0xFFFF marks an extended template */
    DWORD helpID;
    DWORD exStyle;
    DWORD style;
    WORD  cDlgItems;
    short x;
    short y;
    short cx;
    short cy;
} DLGTEMPLATEEX;

/* ------------------------------------------------------------------ */
/* M29: Raster Operation Codes (book aa452783 Ternary / aa452878       */
/* Binary).  The CE pages name the common ternary codes (published in   */
/* Wingdi.h) and the R2_* drawing modes (GetROP2/SetROP2) and define     */
/* the encoding (32-bit value whose high word is the Boolean operation  */
/* index); the numeric values are the fixed Win32 ABI values, recorded   */
/* per the repo fixed-ABI policy.                                       */
/* ------------------------------------------------------------------ */
#define BLACKNESS       0x00000042L
#define DSTINVERT       0x00550009L
#define MERGECOPY       0x00C000CAL
#define MERGEPAINT      0x00BB0226L
#define NOTSRCCOPY      0x00330008L
#define NOTSRCERASE     0x001100A6L
#define PATCOPY         0x00F00021L
#define PATINVERT       0x005A0049L
#define PATPAINT        0x00FB0A09L
#define SRCAND          0x008800C6L
#define SRCCOPY         0x00CC0020L
#define SRCERASE        0x00440328L
#define SRCINVERT       0x00660046L
#define SRCPAINT        0x00EE0086L
#define WHITENESS       0x00FF0062L

/* Binary raster-operation (ROP2) drawing modes for GetROP2/SetROP2. */
#define R2_BLACK         1
#define R2_NOTMERGEPEN   2
#define R2_MASKNOTPEN    3
#define R2_NOTCOPYPEN    4
#define R2_MASKPENNOT    5
#define R2_NOT           6
#define R2_XORPEN        7
#define R2_NOTMASKPEN    8
#define R2_MASKPEN       9
#define R2_NOTXORPEN    10
#define R2_NOP          11
#define R2_MERGENOTPEN  12
#define R2_COPYPEN      13
#define R2_MERGEPENNOT  14
#define R2_MERGEPEN     15
#define R2_WHITE        16
/* ------------------------------------------------------------------ */
/* M31: character-set translation (Wingdi.h rows).                      */
/*                                                                     */
/* ms885597 "FONTSIGNATURE (CE 2.10+; Wingdi.h)": Unicode-subset       */
/* bitfield fsUsb[4] (128 bits) + code-page bitfield fsCsb[2] (64      */
/* bits), members per the page's prototype.  ms885163 "CHARSETINFO      */
/* (CE 2.11+; Wingdi.h)": ciCharset, ciACP, fs (CE layout has no       */
/* union, exactly as the page's prototype prints).  aa450955            */
/* "TranslateCharsetInfo (CE 2.0+; Wingdi.h; Coredll.lib)": translates  */
/* a charset/code-page/font-signature source into a CHARSETINFO.  The   */
/* page's dwFlags table names TCI_SRCCHARSET, TCI_SRCCODEPAGE and       */
/* TCI_SRCFONTSIG (values are the fixed Win32 ABI ones, recorded per    */
/* repo policy); the character-set constants (ANSI_CHARSET ... ) and    */
/* the FS_* font-signature bits appear in the page's remarks table by   */
/* name only, so they are recorded (docs/inventory.md), not defined.    */
/* ------------------------------------------------------------------ */
typedef struct tagFONTSIGNATURE {
    DWORD fsUsb[4];   /* 128-bit Unicode subset bitfield */
    DWORD fsCsb[2];   /* 64-bit code-page bitfield */
} FONTSIGNATURE;

typedef struct tagCHARSETINFO {
    UINT         ciCharset;   /* character set value */
    UINT         ciACP;       /* ANSI code-page identifier */
    FONTSIGNATURE fs;         /* font signature */
} CHARSETINFO;
typedef CHARSETINFO *LPCHARSETINFO;

#define TCI_SRCCHARSET 1
#define TCI_SRCCODEPAGE 3
#define TCI_SRCFONTSIG  4

/* aa450955 prints the parameter as "DWORD FAR* lpSrc"; FAR is empty
 * on the flat CE/Win32 ABI. */
AKARI_CE_IMPORT UINT TranslateCharsetInfo(DWORD *lpSrc, LPCHARSETINFO lpCs,
                          DWORD dwFlags) AKARI_CE_NAME(TranslateCharsetInfo);

/* ------------------------------------------------------------------ */
/* M36: Fonts-and-text and display-monitor declarations.               */
/*                                                                     */
/* Spec basis: the official CE 5.0 Fonts-and-Text GDI pages and the    */
/* CE .NET 4.0+ MultiMonitor pages of the (v=msdn.10) archive, with    */
/* their (v=winembedded.60) CE 6.0 twins (page identifiers below).     */
/* Requirement rows: Header Windows.h (CE 5.0-era) / Wingdi.h (the     */
/* pages added for CE 5.0/CE 6.0, e.g. ms901124/ee489844, print       */
/* wingdi.h), Link Library Coredll.lib, unless a declaration notes     */
/* otherwise.  Windows CE is Unicode-only, so the wide export         */
/* spellings are declared and the generic names are macro-mapped, per */
/* the repo Unicode-only rule; functions that take no text use their   */
/* plain names.  The pages type the DrawText uFormat parameter UNIT   */
/* (sic) and the LOGFONT/TEXTMETRIC structures exactly as printed      */
/* below (TEXTMETRIC glyph members are char; NEWTEXTMETRIC uses        */
/* BCHAR).                                                             */
/* ------------------------------------------------------------------ */

/* LF_FACESIZE / LF_FULLFACESIZE: typeface-name buffer sizes used by
 * LOGFONT (ms901140/ee489840) and ENUMLOGFONT (ms901128/ee489900).
 * The CE pages name the constants only; the values are the fixed
 * Win32 ABI sizes, recorded per repo policy. */
#define LF_FACESIZE     32
#define LF_FULLFACESIZE 64

/* ms901140 "LOGFONT" (ee489840): logical-font definition.  OS
 * Windows CE 1.0+; Wingdi.h.  The page prints the typeface member as
 * TCHAR lfFaceName[LF_FACESIZE] (Unicode-only CE) and the glyph/flag
 * members as BYTE. */
typedef struct tagLOGFONT {
    LONG  lfHeight;
    LONG  lfWidth;
    LONG  lfEscapement;
    LONG  lfOrientation;
    LONG  lfWeight;
    BYTE  lfItalic;
    BYTE  lfUnderline;
    BYTE  lfStrikeOut;
    BYTE  lfCharSet;
    BYTE  lfOutPrecision;
    BYTE  lfClipPrecision;
    BYTE  lfQuality;
    BYTE  lfPitchAndFamily;
    TCHAR lfFaceName[LF_FACESIZE];
} LOGFONT;
typedef LOGFONT *LPLOGFONT;  /* EnumFontFamiliesEx ms901124 lpLogfont */

/* ms901128 "ENUMLOGFONT" (ee489900): per-font enumeration record
 * (embedded LOGFONT + full face name + style).  OS CE 1.0+; Wingdi.h. */
typedef struct tagENUMLOGFONT {
    LOGFONT elfLogFont;
    TCHAR   elfFullName[LF_FULLFACESIZE];
    TCHAR   elfStyle[LF_FACESIZE];
} ENUMLOGFONT;

/* ms901141 "NEWTEXTMETRIC" (ee489904): TEXTMETRIC prefix plus the
 * TrueType extension fields (page prints the full member list).  OS
 * CE 1.0+; Wingdi.h.  Unlike TEXTMETRIC -- whose page types the four
 * glyph members tmFirstChar..tmBreakChar as char -- the NEWTEXTMETRIC
 * page types those members BCHAR (the wide character), per page. */
typedef struct tagNEWTEXTMETRIC {
    LONG  tmHeight;
    LONG  tmAscent;
    LONG  tmDescent;
    LONG  tmInternalLeading;
    LONG  tmExternalLeading;
    LONG  tmAveCharWidth;
    LONG  tmMaxCharWidth;
    LONG  tmWeight;
    LONG  tmOverhang;
    LONG  tmDigitizedAspectX;
    LONG  tmDigitizedAspectY;
    BCHAR tmFirstChar;
    BCHAR tmLastChar;
    BCHAR tmDefaultChar;
    BCHAR tmBreakChar;
    BYTE  tmItalic;
    BYTE  tmUnderlined;
    BYTE  tmStruckOut;
    BYTE  tmPitchAndFamily;
    BYTE  tmCharSet;
    DWORD ntmFlags;
    UINT  ntmSizeEM;
    UINT  ntmCellHeight;
    UINT  ntmAvgWidth;
} NEWTEXTMETRIC;

/* ms901108 "ABC" (ee489865): character ABC widths returned by
 * GetCharABCWidths.  OS CE .NET 4.2+; Windows.h.  The page prints the
 * alias PABC; LPABC is the GetCharABCWidths ms901130 parameter type. */
typedef struct _ABC {
    int  abcA;
    UINT abcB;
    int  abcC;
} ABC, *PABC;
typedef ABC *LPABC;

/* Font-type constants of the enumeration callbacks (EnumFontFamProc
 * ms901125 / EnumFontsProc ms901127 FontType tables; also referenced
 * by the RASTER/DEVICE/TRUETYPE descriptions on the EnumFontFamilies
 * page).  Fixed Win32 ABI values. */
#define RASTER_FONTTYPE    1
#define DEVICE_FONTTYPE    2
#define TRUETYPE_FONTTYPE  4

/* FONTENUMPROC: callback-pointer type of the font-enumeration
 * functions.  EnumFontFamilies ms901123 and EnumFonts ms901126 type
 * their callback parameters FONTENUMPROC.  The CE archive publishes no
 * separate FONTENUMPROC typedef page; the shape below is that of the
 * EnumFontFamProc callback page ms901125 that EnumFontFamilies names
 * as the callback it registers.  EnumFonts registers EnumFontsProc
 * (ms901127), whose page spells the two font pointers (LOGFONT* and
 * TEXTMETRIC*) without the const qualifiers. */
typedef int (CALLBACK *FONTENUMPROC)(const LOGFONT* lpelf,
                                     const TEXTMETRIC* lpntm,
                                     DWORD FontType, LPARAM lParam);

/* Formatting, spacing and alignment flag name lists below come from
 * the uFormat (DrawText ms901121), fuOptions (ExtTextOut ms901129) and
 * fmode (SetTextAlign ms901143 / GetTextAlign ms901132) value tables;
 * the CE pages document names and meanings only, so the numeric values
 * are the fixed Win32 ABI values (recorded per repo policy). */

/* DrawText formatting flags (the DT_TABSTOP description on the page
 * defines the tab-stop field as bits 8-15 of uFormat). */
#define DT_TOP            0x0000
#define DT_LEFT           0x0000
#define DT_CENTER         0x0001
#define DT_RIGHT          0x0002
#define DT_VCENTER        0x0004
#define DT_BOTTOM         0x0008
#define DT_WORDBREAK      0x0010
#define DT_SINGLELINE     0x0020
#define DT_EXPANDTABS     0x0040
#define DT_TABSTOP        0x0080
#define DT_NOCLIP         0x0100
#define DT_EXTERNALLEADING 0x0200
#define DT_CALCRECT       0x0400
#define DT_NOPREFIX       0x0800
#define DT_INTERNAL       0x1000
#define DT_END_ELLIPSIS   0x8000
#define DT_RTLREADING     0x20000
#define DT_WORD_ELLIPSIS  0x40000

/* ExtTextOut options. */
#define ETO_OPAQUE        0x0002
#define ETO_CLIPPED       0x0004
#define ETO_RTLREADING    0x0080

/* Text-alignment modes (GetTextAlign / SetTextAlign). */
#define TA_NOUPDATECP     0x0000
#define TA_UPDATECP       0x0001
#define TA_LEFT           0x0000
#define TA_RIGHT          0x0002
#define TA_CENTER         0x0006
#define TA_TOP            0x0000
#define TA_BOTTOM         0x0008
#define TA_BASELINE       0x0018
#define TA_RTLREADING     0x0100

/* Fonts-and-text functions (Header Windows.h / Wingdi.h; Coredll.lib). */

/* ms901109 "AddFontResource" (ee489896): int AddFontResource(LPCTSTR).
 * OS CE 2.0+; Windows.h.  Export AddFontResourceW (CE Unicode-only). */
AKARI_CE_IMPORT int AddFontResourceW(LPCWSTR lpszFilename) AKARI_CE_NAME(AddFontResourceW);
#define AddFontResource AddFontResourceW

/* ms901120 "CreateFontIndirect" (ee489863): HFONT
 * CreateFontIndirect(const LOGFONT*).  OS CE 1.0+; Windows.h.  Export
 * CreateFontIndirectW. */
AKARI_CE_IMPORT HFONT CreateFontIndirectW(const LOGFONT* lplf) AKARI_CE_NAME(CreateFontIndirectW);
#define CreateFontIndirect CreateFontIndirectW

/* ms901121 "DrawText" (ee489886): int DrawText(HDC, LPCTSTR, int,
 * LPRECT, UNIT uFormat).  OS CE 1.0+; Windows.h.  The page prints the
 * last parameter type "UNIT" (sic); the parameter is UINT, and its
 * DT_TABSTOP bit-field description (bits 8-15) matches UINT.  Export
 * DrawTextW. */
AKARI_CE_IMPORT int DrawTextW(HDC hDC, LPCWSTR lpString, int nCount, LPRECT lpRect,
              UINT uFormat) AKARI_CE_NAME(DrawTextW);
#define DrawText DrawTextW

/* ms901123 "EnumFontFamilies" (ee489908): enumerates type families
 * through the FONTENUMPROC callback.  OS CE 1.0+; Windows.h.  Export
 * EnumFontFamiliesW. */
AKARI_CE_IMPORT int EnumFontFamiliesW(HDC hdc, LPCWSTR lpszFamily,
                      FONTENUMPROC lpEnumFontFamProc, LPARAM lParam) AKARI_CE_NAME(EnumFontFamiliesW);
#define EnumFontFamilies EnumFontFamiliesW

/* ms901124 "EnumFontFamiliesEx" (ee489844): as EnumFontFamilies with
 * an explicit LOGFONT filter.  OS CE 5.0+; Wingdi.h.  dwFlags is "not
 * used; must be 0".  Export EnumFontFamiliesExW. */
AKARI_CE_IMPORT int EnumFontFamiliesExW(HDC hdc, LPLOGFONT lpLogfont,
                        FONTENUMPROC lpEnumFontFamExProc, LPARAM lParam,
                        DWORD dwFlags) AKARI_CE_NAME(EnumFontFamiliesExW);
#define EnumFontFamiliesEx EnumFontFamiliesExW

/* ms901126 "EnumFonts" (ee489905): enumerates typefaces through the
 * FONTENUMPROC callback.  OS CE 1.0+; Windows.h.  Export EnumFontsW. */
AKARI_CE_IMPORT int EnumFontsW(HDC hdc, LPCWSTR lpFaceName, FONTENUMPROC lpFontFunc,
               LPARAM lParam) AKARI_CE_NAME(EnumFontsW);
#define EnumFonts EnumFontsW

/* ms901129 "ExtTextOut" (ee489846): BOOL ExtTextOut(HDC, int, int,
 * UINT, const RECT*, LPCTSTR, UINT, const int* lpDx).  OS CE 1.0+;
 * Windows.h.  Export ExtTextOutW. */
AKARI_CE_IMPORT BOOL ExtTextOutW(HDC hdc, int X, int Y, UINT fuOptions,
                 const RECT* lprc, LPCWSTR lpString, UINT cbCount,
                 const int* lpDx) AKARI_CE_NAME(ExtTextOutW);
#define ExtTextOut ExtTextOutW

/* ms901130 "GetCharABCWidths" (ee489910): BOOL GetCharABCWidths(HDC,
 * UINT, UINT, LPABC).  OS CE .NET 4.2+; Windows.h.  Export
 * GetCharABCWidthsW. */
AKARI_CE_IMPORT BOOL GetCharABCWidthsW(HDC hdc, UINT uFirstChar, UINT uLastChar,
                       LPABC lpabc) AKARI_CE_NAME(GetCharABCWidthsW);
#define GetCharABCWidths GetCharABCWidthsW

/* ms901131 "GetCharWidth32" (ee489848): WINGDIAPI BOOL WINAPI
 * GetCharWidth32(HDC, UINT, UINT, LPINT); CE ABI is __cdecl.  OS
 * CE .NET 4.0+; Windows.h.  Export GetCharWidth32W. */
AKARI_CE_IMPORT BOOL GetCharWidth32W(HDC hdc, UINT iFirstChar, UINT iLastChar,
                     LPINT lpBuffer) AKARI_CE_NAME(GetCharWidth32W);
#define GetCharWidth32 GetCharWidth32W

/* aa520325 "GetFontData" (ee489901): DWORD GetFontData(HDC, DWORD
 * dwTable, DWORD dwOffset, LPVOID, DWORD).  OS CE 5.0+; Windows.h. */
AKARI_CE_IMPORT DWORD GetFontData(HDC hdc, DWORD dwTable, DWORD dwOffset,
                  LPVOID lpvBuffer, DWORD cbData) AKARI_CE_NAME(GetFontData);

/* ms901132 "GetTextAlign" (ee489856): WINGDIAPI UINT WINAPI
 * GetTextAlign(HDC); CE ABI is __cdecl.  OS CE .NET 4.0+; Windows.h. */
AKARI_CE_IMPORT UINT GetTextAlign(HDC hdc) AKARI_CE_NAME(GetTextAlign);

/* ms901133 "GetTextCharacterExtra" (ee489907): int
 * GetTextCharacterExtra(HDC).  OS CE 5.0+; Wingdi.h. */
AKARI_CE_IMPORT int GetTextCharacterExtra(HDC hdc) AKARI_CE_NAME(GetTextCharacterExtra);

/* ms901134 "GetTextColor" (ee489912): COLORREF GetTextColor(HDC).
 * OS CE 1.0+; Windows.h. */
AKARI_CE_IMPORT COLORREF GetTextColor(HDC hdc) AKARI_CE_NAME(GetTextColor);

/* ms901135 "GetTextExtentExPoint" (ee489883): BOOL
 * GetTextExtentExPoint(HDC, LPCTSTR, int, int, LPINT lpnFit,
 * LPINT alpDx, LPSIZE).  OS CE 1.0+; Windows.h.  Export
 * GetTextExtentExPointW. */
AKARI_CE_IMPORT BOOL GetTextExtentExPointW(HDC hdc, LPCWSTR lpszStr, int cchString,
                           int nMaxExtent, LPINT lpnFit, LPINT alpDx,
                           LPSIZE lpSize) AKARI_CE_NAME(GetTextExtentExPointW);
#define GetTextExtentExPoint GetTextExtentExPointW

/* ms901136 "GetTextExtentPoint" (ee489897): BOOL GetTextExtentPoint(
 * HDC, LPCTSTR, int cbString, LPSIZE).  OS CE 2.0+; Windows.h.
 * Export GetTextExtentPointW. */
AKARI_CE_IMPORT BOOL GetTextExtentPointW(HDC hdc, LPCWSTR lpString, int cbString,
                         LPSIZE lpSize) AKARI_CE_NAME(GetTextExtentPointW);
#define GetTextExtentPoint GetTextExtentPointW

/* ms901137 "GetTextExtentPoint32" (ee489838): BOOL
 * GetTextExtentPoint32(HDC, LPCTSTR, int, LPSIZE).  OS CE 2.0+;
 * Windows.h.  Export GetTextExtentPoint32W. */
AKARI_CE_IMPORT BOOL GetTextExtentPoint32W(HDC hdc, LPCWSTR lpString, int cbString,
                           LPSIZE lpSize) AKARI_CE_NAME(GetTextExtentPoint32W);
#define GetTextExtentPoint32 GetTextExtentPoint32W

/* ms901138 "GetTextFace" (ee489915): int GetTextFace(HDC, int nCount,
 * LPTSTR).  OS CE 1.0+; Windows.h.  Export GetTextFaceW. */
AKARI_CE_IMPORT int GetTextFaceW(HDC hdc, int nCount, LPWSTR lpFaceName) AKARI_CE_NAME(GetTextFaceW);
#define GetTextFace GetTextFaceW

/* ms901139 "GetTextMetrics" (ee489911): BOOL GetTextMetrics(HDC,
 * LPTEXTMETRIC).  OS CE 1.0+; Windows.h.  Export GetTextMetricsW. */
AKARI_CE_IMPORT BOOL GetTextMetricsW(HDC hdc, LPTEXTMETRIC lptm) AKARI_CE_NAME(GetTextMetricsW);
#define GetTextMetrics GetTextMetricsW

/* ms901142 "RemoveFontResource" (ee489851): BOOL
 * RemoveFontResource(LPCTSTR).  OS CE 1.0+; Windows.h.  Export
 * RemoveFontResourceW. */
AKARI_CE_IMPORT BOOL RemoveFontResourceW(LPCWSTR lpFileName) AKARI_CE_NAME(RemoveFontResourceW);
#define RemoveFontResource RemoveFontResourceW

/* ms901143 "SetTextAlign" (ee489853): WINGDIAPI UINT WINAPI
 * SetTextAlign(HDC, UINT fmode); CE ABI is __cdecl.  OS CE .NET 4.0+;
 * Windows.h. */
AKARI_CE_IMPORT UINT SetTextAlign(HDC hdc, UINT fmode) AKARI_CE_NAME(SetTextAlign);

/* ms901144 "SetTextCharacterExtra" (ee489860): int
 * SetTextCharacterExtra(HDC, int nCharExtra).  OS CE 5.0+; Wingdi.h. */
AKARI_CE_IMPORT int SetTextCharacterExtra(HDC hdc, int nCharExtra) AKARI_CE_NAME(SetTextCharacterExtra);

/* ms901145 "SetTextColor" (ee489887): COLORREF SetTextColor(HDC,
 * COLORREF).  OS CE .NET 4.0+; Windows.h. */
AKARI_CE_IMPORT COLORREF SetTextColor(HDC hdc, COLORREF crColor) AKARI_CE_NAME(SetTextColor);

/* ------------------------------------------------------------------ */
/* M36: MultiMonitor functions and types (CE .NET 4.0+ pages; Header   */
/* Windows.h, Link Library Coredll.lib).  The page set is shared with  */
/* the desktop MultiMonitor API surface, but the declarations below    */
/* come from the CE pages: EnumDisplayMonitors aa451688, GetMonitorInfo */
/* aa451738, MonitorEnumProc ms932091, MonitorFromPoint ms932198,       */
/* MonitorFromRect ms932208, MonitorFromWindow ms932212, MONITORINFO    */
/* ms932213 (CE 6.0 twins ee490277 / ee491682 / ee490724 / ee491624 /   */
/* ee491307 / ee490720 / ee491429).  The pages document the screen      */
/* handles and virtual-screen coordinates.                              */
/* ------------------------------------------------------------------ */

/* ms932213 "MONITORINFO": screen information returned by
 * GetMonitorInfo.  rcMonitor / rcWork are virtual-screen RECTs.
 * dwFlags: 0 = not the primary screen; MONITORINFOF_PRIMARY (fixed
 * Win32 ABI value 1) = the primary screen. */
typedef struct tagMONITORINFO {
    DWORD cbSize;
    RECT  rcMonitor;
    RECT  rcWork;
    DWORD dwFlags;
} MONITORINFO, *LPMONITORINFO;

/* ms932214 "MONITORINFOEX" (Multiple Screens Structures, graphics-book
 * M89 harvest; CE .NET 4.0+; page Requirements row prints Header:
 * Windows.h): print `typedef struct tagMONITORINFOEX {DWORD cbSize;
 * RECT rcMonitor;RECT rcWork;DWORD dwFlags;TCHAR szDevice
 * [CCHDEVICENAME];} MONITORINFOEX, *LPMONITORINFOEX;` (glued tokens
 * split; CCHDEVICENAME = 32 above; szDevice = device name string). */
typedef struct tagMONITORINFOEX {
    DWORD cbSize;
    RECT  rcMonitor;
    RECT  rcWork;
    DWORD dwFlags;
    TCHAR szDevice[CCHDEVICENAME];
} MONITORINFOEX, *LPMONITORINFOEX;

#define MONITORINFOF_PRIMARY 1

/* MonitorFrom* dwFlags values (value tables on ms932198/ms932208/
 * ms932212).  Fixed Win32 ABI values. */
#define MONITOR_DEFAULTTONULL     0
#define MONITOR_DEFAULTTOPRIMARY  1
#define MONITOR_DEFAULTTONEAREST  2

/* ms932091 "MonitorEnumProc": application-defined callback of
 * EnumDisplayMonitors.  The page states "A value of type
 * MONITORENUMPROC is a pointer to this function." */
typedef BOOL (CALLBACK *MONITORENUMPROC)(HMONITOR hMonitor,
                                         HDC hdcMonitor,
                                         LPRECT lprcMonitor,
                                         LPARAM dwData);

AKARI_CE_IMPORT BOOL EnumDisplayMonitors(HDC hdc, LPCRECT lprcClip,
                         MONITORENUMPROC lpfnEnum, LPARAM dwData) AKARI_CE_NAME(EnumDisplayMonitors);
AKARI_CE_IMPORT BOOL GetMonitorInfo(HMONITOR hMonitor, LPMONITORINFO lpmi) AKARI_CE_NAME(GetMonitorInfo);
AKARI_CE_IMPORT HMONITOR MonitorFromPoint(POINT pt, DWORD dwFlags) AKARI_CE_NAME(MonitorFromPoint);
AKARI_CE_IMPORT HMONITOR MonitorFromRect(LPCRECT lprc, DWORD dwFlags) AKARI_CE_NAME(MonitorFromRect);
AKARI_CE_IMPORT HMONITOR MonitorFromWindow(HWND hwnd, DWORD dwFlags) AKARI_CE_NAME(MonitorFromWindow);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WINGDI_H */
