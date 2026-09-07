/*
 * wince-api: Clean-room Windows CE API implementation for LLVM/Clang
 * File: tchar.h
 *
 * Windows CE Generic-Text Mappings (Unicode Native).
 */

#ifndef _TCHAR_H_
#define _TCHAR_H_

#include <sdkddkver.h>
#include <windef.h>
#include <winnt.h>

#ifndef _TCHAR_DEFINED
#define _TCHAR_DEFINED
typedef wchar_t _TCHAR;
typedef wchar_t _TSCHAR;
typedef wchar_t _TUCHAR;
#endif

#define _TEXT(x)    L##x
#define _T(x)       _TEXT(x)

#define _tcslen     wcslen
#define _tcscpy     wcscpy
#define _tcsncpy    wcsncpy
#define _tcscat     wcscat
#define _tcscmp     wcscmp
#define _tcsncmp    wcsncmp
#define _tcschr     wcschr
#define _tcsrchr    wcsrchr
#define _tcsstr     wcsstr
#define _stprintf   swprintf
#define _sntprintf  _snwprintf
#define _tprintf    wprintf

#endif /* _TCHAR_H_ */
