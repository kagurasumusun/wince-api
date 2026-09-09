/*
 * Shtypes.h -- Shell base types for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  This header holds the Standard Shell Structures whose CE 5.0
 * pages print Header: Shtypes.h.
 */

#ifndef AKARI_SHTYPES_H
#define AKARI_SHTYPES_H

#include "Windef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* aa453718 "SHITEMID" (Windows CE 1.0 and later; Shtypes.h).  An item
 * identifier: cb is the size of the identifier in bytes including cb
 * itself; abID is the variable-length identifier (declared [1] on the
 * page; the array is open-ended in practice). */
typedef struct _SHITEMID {
    USHORT cb;
    BYTE   abID[1];
} SHITEMID;

/* ms940377 "STRRET" (Windows CE .NET 4.2 and later; Shtypes.h).  The
 * string carrier returned by the IShellFolder::GetDisplayNameOf method
 * (shobjidl.h).  uType selects the union arm; the page publishes the
 * three selector names but no numeric values, and the desktop Win32
 * STRRET reference page is names-only as well -- so the STRRET_CSTR /
 * STRRET_OFFSET / STRRET_WSTR values are held in docs/inventory.md
 * (M53 derivation analysis) rather than defined here.  pOleStr memory
 * must be allocated and freed with the shell's IMalloc (SHGetMalloc,
 * shlobj.h); cStr is MAX_PATH bytes. */
typedef struct _STRRET {
    UINT uType;                        /* STRRET_* selector (names held) */
    union {
        LPWSTR pOleStr;                /* STRRET_WSTR: OLE string */
        UINT   uOffset;                /* STRRET_OFFSET: bytes into the pidl */
        char   cStr[MAX_PATH];         /* STRRET_CSTR: inline buffer */
    } DUMMYUNIONNAME;
} STRRET, *LPSTRRET;

/* STRRET selector names (ms940377 table; values not published):
 *   STRRET_CSTR    the string is returned in the cStr member
 *   STRRET_OFFSET  uOffset gives the byte offset into the item id list
 *   STRRET_WSTR    the string is at the address in pOleStr
 */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_SHTYPES_H */
