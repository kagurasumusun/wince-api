#!/usr/bin/env python3
"""gen-doc-def.py -- generate export def files from official-page records.

Source of truth: build/rows.json produced by tools/ce-fetch.py from
the official Microsoft CE documentation pages (Requirements rows of
the (v=msdn.10) archive).  This tool writes def/*-doc.def with

  * one def file per documented link-library token found in the rows
    (currently coredll; the naming scheme is coredll-doc.def), and
  * only names that are (a) documented on an official page whose
    Requirements row names that library and (b) declared as exports by
    this repository's headers (so the def is exactly the import
    surface the header set can be linked against).

The Unicode-only mapping table below records, for functions whose
official pages state that Windows CE exports only the Unicode
version, the actual coredll export spelling (e.g. page "CreateEvent"
-> export "CreateEventW").  Every row is grounded in an official page
recorded in docs/inventory.md.

Ordinals are not published by the documentation, so entries are
name-only.

Usage: python3 tools/gen-doc-def.py   (reads build/rows.json)
"""

import json
import os
import re
import sys

# Page title (short name) -> actual coredll export spelling, for
# functions whose pages document a Unicode-only export.
UNICODE_ONLY = {
    "CreateEvent": "CreateEventW",
    "OpenEvent": "OpenEventW",
    "CreateMutex": "CreateMutexW",
    "CreateSemaphore": "CreateSemaphoreW",
    "CreateProcess": "CreateProcessW",
    "GetCommandLine": "GetCommandLineW",
    "GetModuleHandle": "GetModuleHandleW",
    "GetModuleFileName": "GetModuleFileNameW",
    "GetProcAddress": "GetProcAddressW",
    "LoadLibrary": "LoadLibraryW",
    "LoadLibraryEx": "LoadLibraryExW",
    "CreateFile": "CreateFileW",
    "DeleteFile": "DeleteFileW",
    "GetFileAttributes": "GetFileAttributesW",
    "FindFirstFile": "FindFirstFileW",
    "FindNextFile": "FindNextFileW",
    "MoveFile": "MoveFileW",
    "CopyFile": "CopyFileW",
    "CopyFileEx": "CopyFileExW",
    "CreateDirectory": "CreateDirectoryW",
    "RemoveDirectory": "RemoveDirectoryW",
    "SetFileAttributes": "SetFileAttributesW",
    "GetModuleFileNameEx": "GetModuleFileNameExW",
    # Registry (CE is Unicode-only; the exported spellings are the W
    # forms documented by the CE registry pages' base names).
    "RegCloseKey": "RegCloseKeyW",
    "RegOpenKeyEx": "RegOpenKeyExW",
    "RegCreateKeyEx": "RegCreateKeyExW",
    "RegDeleteKey": "RegDeleteKeyW",
    "RegDeleteValue": "RegDeleteValueW",
    "RegEnumKeyEx": "RegEnumKeyExW",
    "RegEnumValue": "RegEnumValueW",
    "RegQueryInfoKey": "RegQueryInfoKeyW",
    "RegQueryValueEx": "RegQueryValueExW",
    "RegSetValueEx": "RegSetValueExW",
    "RegFlushKey": "RegFlushKeyW",
    # Strings/char functions whose pages state "Windows CE supports
    # only the Unicode version of this function".
    "CharLower": "CharLowerW",
    "CharLowerBuff": "CharLowerBuffW",
    "CharUpper": "CharUpperW",
    "CharUpperBuff": "CharUpperBuffW",
    "CharNext": "CharNextW",
    "CharPrev": "CharPrevW",
    "IsCharAlpha": "IsCharAlphaW",
    "IsCharAlphaNumeric": "IsCharAlphaNumericW",
    "IsCharLower": "IsCharLowerW",
    "IsCharUpper": "IsCharUpperW",
    "LoadString": "LoadStringW",
    "wsprintf": "wsprintfW",
    "wvsprintf": "wvsprintfW",
    # NLS comparison/typing (Unicode-only CE).
    "CompareString": "CompareStringW",
    "GetStringTypeEx": "GetStringTypeExW",
    # NLS string mapping / code-page enumeration (Coreloc.lib): the
    # FoldString page ms905209 and LCMapString page ms906221 state that
    # CE supports only the Unicode version; EnumSystemCodePages
    # ms905062 follows the same Unicode-only rule (its callback receives
    # wide code-page strings).
    "FoldString": "FoldStringW",
    "LCMapString": "LCMapStringW",
    "EnumSystemCodePages": "EnumSystemCodePagesW",
    # Directory-service user-name query (Coredll.lib): the CE page
    # aa517595 types the buffer LPTSTR and Windows CE is Unicode-only.
    "GetUserNameEx": "GetUserNameExW",
    # File I/O functions whose CE exports are the wide spellings.
    "FindFirstChangeNotification": "FindFirstChangeNotificationW",
    "FindFirstFileEx": "FindFirstFileExW",
    "GetFileAttributesEx": "GetFileAttributesExW",
    "GetDiskFreeSpaceEx": "GetDiskFreeSpaceExW",
    "GetTempFileName": "GetTempFileNameW",
    "GetTempPath": "GetTempPathW",
    "GetFileVersionInfoSize": "GetFileVersionInfoSizeW",
    "GetFileVersionInfo": "GetFileVersionInfoW",
    "CreateFileForMapping": "CreateFileForMappingW",
    "CreateFileMapping": "CreateFileMappingW",
    "GetModuleInformation": "GetModuleInformation",
    "FormatMessage": "FormatMessageW",
    # M26 GWES: window-property, atom and window-message text functions
    # (pages aa453647/aa453155/ms939781/aa453050/aa453188/aa453190/
    # ms939737); CE is Unicode-only so the exports are the wide forms.
    "RegisterWindowMessage": "RegisterWindowMessageW",
    "SetProp": "SetPropW",
    "GetProp": "GetPropW",
    "RemoveProp": "RemovePropW",
    "EnumPropsEx": "EnumPropsExW",
    "GlobalAddAtom": "GlobalAddAtomW",
    "GlobalFindAtom": "GlobalFindAtomW",
    "GetKeyboardLayoutName": "GetKeyboardLayoutNameW",
    "LoadAccelerators": "LoadAcceleratorsW",
    # M28 window-control text functions (Menus / Dialog Boxes / Clipboards
    # / Resources / System-Information pages; CE is Unicode-only, so the
    # exported spellings are the wide forms, matching the repo rule).
    "AppendMenu": "AppendMenuW",
    "InsertMenu": "InsertMenuW",
    "LoadMenu": "LoadMenuW",
    "CreateDialog": "CreateDialogW",
    "CreateDialogParam": "CreateDialogParamW",
    "DialogBox": "DialogBoxW",
    "DialogBoxParam": "DialogBoxParamW",
    "GetDlgItemText": "GetDlgItemTextW",
    "SetDlgItemText": "SetDlgItemTextW",
    "MessageBox": "MessageBoxW",
    "LoadIcon": "LoadIconW",
    "LoadImage": "LoadImageW",
    "RegisterClipboardFormat": "RegisterClipboardFormatW",
    "GetClipboardFormatName": "GetClipboardFormatNameW",
    "SystemParametersInfo": "SystemParametersInfoW",
    "FindResource": "FindResourceW",
    "ExtractIconEx": "ExtractIconExW",
    # M30: version-information helper (CE is Unicode-only, so the
    # exported spelling is the wide form of the LPTSTR sub-block
    # parameter; repo Unicode-only rule, page aa450973).
    "VerQueryValue": "VerQueryValueW",
    # M32: NLS formatting / locale-info functions (CE is Unicode-only;
    # the exported spellings are the wide forms; pages ms905229/
    # ms905250/ms905235/ms905310/ms905243/ms906277).
    "GetCurrencyFormat": "GetCurrencyFormatW",
    "GetNumberFormat": "GetNumberFormatW",
    "GetDateFormat": "GetDateFormatW",
    "GetTimeFormat": "GetTimeFormatW",
    "GetLocaleInfo": "GetLocaleInfoW",
    "SetLocaleInfo": "SetLocaleInfoW",
    # M36 GDI fonts-and-text functions whose CE pages take LPCTSTR/
    # LPTSTR parameters; Windows CE is Unicode-only, so the exports are
    # the wide spellings (pages ms901109/ms901120/ms901121/ms901123/
    # ms901124/ms901126/ms901129/ms901130/ms901131/ms901135/ms901136/
    # ms901137/ms901138/ms901139/ms901142; CE 6.0 twins ee489896..).
    "AddFontResource": "AddFontResourceW",
    "CreateFontIndirect": "CreateFontIndirectW",
    "DrawText": "DrawTextW",
    "EnumFontFamilies": "EnumFontFamiliesW",
    "EnumFontFamiliesEx": "EnumFontFamiliesExW",
    "EnumFonts": "EnumFontsW",
    "ExtTextOut": "ExtTextOutW",
    "GetCharABCWidths": "GetCharABCWidthsW",
    "GetCharWidth32": "GetCharWidth32W",
    "GetTextExtentExPoint": "GetTextExtentExPointW",
    "GetTextExtentPoint": "GetTextExtentPointW",
    "GetTextExtentPoint32": "GetTextExtentPoint32W",
    "GetTextFace": "GetTextFaceW",
    "GetTextMetrics": "GetTextMetricsW",
    "RemoveFontResource": "RemoveFontResourceW",
}

ROOT = os.path.join(os.path.dirname(__file__), "..")
INCLUDE = os.path.join(ROOT, "include")
DEFDIR = os.path.join(ROOT, "def")
DB = os.path.join(ROOT, "build", "rows.json")

# Export spellings declared by this repository's headers: every
# function-like declaration (identifier followed by '(') in the
# shipped headers, minus macro/typedef noise caught by the pattern.
# The optional AKARI_CE_IMPORT prefix is the x86 dllimport pin of
# windef.h (M37): the line is
#   AKARI_CE_IMPORT <ret> <name>(...
_DECL_RE = re.compile(
    r"^(?:AKARI_CE_IMPORT\s+)?"
    r"[A-Za-z_][A-Za-z0-9_]*\s+"
    r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", re.M)

# Compiler-provided SEH intrinsics.  The Exception Reference pages
# (ms885620/ms885621/aa450784) print a Link Library: Coredll.lib
# row, but the functions are callable only inside try/except/finally
# constructs and are provided by the CE compiler, not imported from
# Coredll.dll -- so they must not appear in the export def.
NOT_EXPORTS = {"GetExceptionCode", "GetExceptionInformation",
               "AbnormalTermination"}


def declared_exports():
    names = set()
    for fn in os.listdir(INCLUDE):
        if not fn.endswith(".h"):
            continue
        txt = open(os.path.join(INCLUDE, fn), encoding="utf-8").read()
        for m in _DECL_RE.finditer(txt):
            names.add(m.group(1))
        # AKARI_CE_IMPORT lines whose return type is multi-word or a
        # pointer (e.g. "struct hostent *gethostbyaddr",
        # "unsigned long inet_addr"): _DECL_RE above only matches a
        # single-token return type, so take the last identifier
        # before the first '(' of the line as the export name.
        for line in txt.splitlines():
            s = line.strip()
            if not s.startswith("AKARI_CE_IMPORT"):
                continue
            body = s[len("AKARI_CE_IMPORT"):].strip()
            i = body.find("(")
            if i < 0:
                continue
            parts = body[:i].strip().split()
            if not parts:
                continue
            names.add(parts[-1].lstrip("*"))
    # Keep only names that look like exports (function declarations);
    # drop common false positives from type/macro text.
    drop = {"if", "for", "while", "do", "switch", "sizeof", "return",
            "typedef", "struct", "union", "enum", "static", "extern",
            "define"}
    return {n for n in names if n not in drop and
            not n.startswith("_RTL_") and
            re.match(r"^[A-Z][A-Za-z0-9_]+$|^[a-z][A-Za-z0-9_]{2,}$", n)}


def short_title(title):
    t = re.sub(r"\s*\(Windows CE [^)]*\)\s*$", "", title).strip()
    # Disambiguation suffixes appended by the archive (e.g. the GDI
    # book prints "CreatePalette (GDI)" for the page whose export is
    # CreatePalette) are annotations, not part of the export name.
    t = re.sub(r"\s*\([^)]*\)\s*$", "", t).strip()
    return t


def main():
    if not os.path.exists(DB):
        sys.exit("build/rows.json missing - run tools/ce-fetch.py first")
    rows = json.load(open(DB, encoding="utf-8"))
    declared = declared_exports()
    print(f"declared exports in headers: {len(declared)}")

    # by-doc-lib records: short page name -> page id/title, restricted
    # to pages whose Requirements name the library.
    bylib = {}
    for r in rows:
        lib = (r.get("lib") or "").lower()
        if not lib:
            continue
        sn = short_title(r.get("title", ""))
        tokens = re.findall(r"[a-z0-9_]+\.lib", lib)
        # Some CE3-era pages print "Link Library: Coredll.dll." (module
        # form).  Map that documented module token onto the coredll.lib
        # export group (module Coredll.dll).
        if not tokens and re.search(r"coredll\.dll", lib):
            tokens = ["coredll.lib"]
        for token in tokens:
            bylib.setdefault(token, {})[sn] = r["id"]

    # Kernel-scope link rows (Nk.lib / Coremain.lib) are tracked but
    # kept out of import defs (documented conflict model, inventory).
    # The remaining tokens are user-mode import libraries whose rows
    # the official pages publish.
    KERNEL_TOKENS = {"nk.lib", "coremain.lib"}
    os.makedirs(DEFDIR, exist_ok=True)
    for token, pages in sorted(bylib.items()):
        if token in KERNEL_TOKENS:
            continue
        entries, skipped = [], []
        for sn, pid in sorted(pages.items()):
            export = UNICODE_ONLY.get(sn, sn)
            # membership check: the export must be declared by our
            # headers (either as the export name itself or as the
            # generic macro base name).
            ok = (export in declared or sn in declared) and \
                 export not in NOT_EXPORTS and sn not in NOT_EXPORTS
            if ok:
                entries.append((export, pid, sn))
            else:
                skipped.append((sn, pid))
        if not entries:
            # Co-listed library token (e.g. Uuid.lib next to Ole32.lib)
            # with no page documenting a sole-link export: no def file
            # is written for it (remove a stale one if present).
            stale = os.path.join(DEFDIR, f"{token.replace('.lib', '')}-doc.def")
            if os.path.exists(stale):
                os.remove(stale)
            print(f"{stale}: no sole-link exports documented "
                  f"({len(skipped)} co-listed pages skipped); no def written")
            continue
        stem = token.replace(".lib", "").replace(".", "-")
        out = os.path.join(DEFDIR, f"{stem}-doc.def")
        with open(out, "w", encoding="utf-8") as fh:
            # ';' comment style: GNU/LLVM dlltool rejects '#' lines.
            fh.write(f"; {os.path.basename(out)} -- {token} export surface "
                     "for Windows CE.\n")
            fh.write(";\n; Copyright (c) 2026 Akari API contributors\n")
            fh.write("; SPDX-License-Identifier: MIT\n;\n")
            fh.write("; Derived exclusively from the official Microsoft CE\n")
            fh.write("; documentation pages: each name below appears on the\n")
            fh.write("; listed page whose Requirements row names this link\n")
            fh.write("; library (tools/ce-manifest.py + tools/ce-fetch.py\n")
            fh.write("; harvest; docs/inventory.md records every page).  No\n")
            fh.write("; shared-source/device-dump/VS/PB-derived name is used.\n")
            fh.write("; Ordinals are not published; entries are name-only.\n")
            if token == "coredll.lib":
                fh.write("LIBRARY coredll.dll\nEXPORTS\n")
            else:
                # Only the import-library name (the page's Link
                # Library row) is documented for the auxiliary
                # libraries; the module name is not published, so the
                # LIBRARY tag below is the row token itself.
                fh.write("; LIBRARY tag = documented Link Library row "
                         "(" + token + "); the on-device module name is\n"
                         "; not published by the CE documentation.\n")
                fh.write(f"LIBRARY {stem}.dll\nEXPORTS\n")
            for export, pid, sn in entries:
                fh.write(f"  {export}\n")
        n = len(entries)
        print(f"{out}: {n} exports from {token} "
              f"(skipped {len(skipped)}: not declared by headers)")
        if skipped:
            print("   skipped: " + ", ".join(f"{s}({p})" for s, p in skipped))


if __name__ == "__main__":
    main()
