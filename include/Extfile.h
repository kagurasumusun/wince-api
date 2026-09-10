/*
 * Extfile.h -- file-change event information for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  The File I/O Structures book of the CE 5.0 documentation is the
 * source (page ms889030); its Requirements row prints Header: Extfile.h /
 * OS Versions: Windows CE 2.10 and later, and no Link Library row.
 *
 * Harvested as a dependency of the M50 AYGShell unit: FILECHANGENOTIFY
 * (Shlobj.h, see shlobj.h) carries this structure as its fci member, and
 * the CE 6.0 twin ee490403 prints the identical layout plus a
 * "extfile.h, shlobj.h / ceshell.lib" Requirements table.
 *
 * The page prints the layout without the typedef keyword
 * ("struct _FILECHANGEINFO { ... } FILECHANGEINFO, *LPFILECHANGEINFO;");
 * the declaration below restores the obvious typedef (transcription
 * note, same model as the M49 title-print fix-ups).
 *
 * The wEventId / uFlags value tables on the page publish the SHCNE_* and
 * SHCNF_* constant NAMES without numeric values; those constants are
 * held as gaps in docs/inventory.md rather than defined here (the
 * M39-M41 held-set policy).
 */

#ifndef AKARI_EXTFILE_H
#define AKARI_EXTFILE_H

#include "Windef.h"
#include "Winbase.h"   /* FILETIME (ftModified member) */

#ifdef __cplusplus
extern "C" {
#endif

/* ms889030 "FILECHANGEINFO" (CE 2.10 and later; Extfile.h).  Filled by
 * the file system driver for a file system event.  wEventId takes the
 * SHCNE_* event names, uFlags the SHCNF_* type/flusion flags -- names
 * only on the page, no values (held set). */
typedef struct _FILECHANGEINFO {
    DWORD    cbSize;
    LONG     wEventId;      /* SHCNE_* (names published without values) */
    ULONG    uFlags;        /* SHCNF_* (names published without values) */
    DWORD    dwItem1;       /* first event-dependent value */
    DWORD    dwItem2;       /* second event-dependent value */
    DWORD    dwAttributes;  /* attributes of the file/folder/item */
    FILETIME ftModified;    /* time when the event occurred */
    ULONG    nFileSize;     /* size of the file/folder/item */
} FILECHANGEINFO, *LPFILECHANGEINFO;

/* M79a: the FSD supplement page SHELLFILECHANGEFUNC_t (ms891992) also
 * prints "Header: Extfile.h".  Its parameter spelling LPCFILECHANGEINFO
 * is grounded by the same print; the const-pointer typedef is closed
 * on the compiled FILECHANGEINFO above. */
typedef const FILECHANGEINFO *LPCFILECHANGEINFO;

/* ms891992 "SHELLFILECHANGEFUNC_t": print `typedef BOOL
 * (*SHELLFILECHANGEFUNC_t) { LPCFILECHANGEINFO lpfci};` -- the `{` is
 * a doc typo for `(` (function-pointer declarator); repaired, noted.
 * Used by MyFSD_RegisterFileSystemFunction (Fsdmgr.h, recorded). */
typedef BOOL (*SHELLFILECHANGEFUNC_t)(LPCFILECHANGEINFO lpfci);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_EXTFILE_H */
