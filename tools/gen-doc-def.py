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
}

ROOT = os.path.join(os.path.dirname(__file__), "..")
INCLUDE = os.path.join(ROOT, "include")
DEFDIR = os.path.join(ROOT, "def")
DB = os.path.join(ROOT, "build", "rows.json")

# Export spellings declared by this repository's headers: every
# function-like declaration (identifier followed by '(') in the
# shipped headers, minus macro/typedef noise caught by the pattern.
_DECL_RE = re.compile(
    r"^[A-Za-z_][A-Za-z0-9_]*\s+"
    r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", re.M)


def declared_exports():
    names = set()
    for fn in os.listdir(INCLUDE):
        if not fn.endswith(".h"):
            continue
        txt = open(os.path.join(INCLUDE, fn), encoding="utf-8").read()
        for m in _DECL_RE.finditer(txt):
            names.add(m.group(1))
    # Keep only names that look like exports (function declarations);
    # drop common false positives from type/macro text.
    drop = {"if", "for", "while", "do", "switch", "sizeof", "return",
            "typedef", "struct", "union", "enum", "static", "extern",
            "define"}
    return {n for n in names if n not in drop and
            not n.startswith("_RTL_") and
            re.match(r"^[A-Z][A-Za-z0-9]+$|^[a-z][A-Za-z0-9]{2,}$", n)}


def short_title(title):
    return re.sub(r"\s*\(Windows CE [^)]*\)\s*$", "", title).strip()


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
        for token in re.findall(r"[a-z0-9]+\.lib", lib):
            bylib.setdefault(token, {})[sn] = r["id"]

    os.makedirs(DEFDIR, exist_ok=True)
    for token, pages in sorted(bylib.items()):
        if token != "coredll.lib":
            continue
        entries, skipped = [], []
        for sn, pid in sorted(pages.items()):
            export = UNICODE_ONLY.get(sn, sn)
            # membership check: the export must be declared by our
            # headers (either as the export name itself or as the
            # generic macro base name).
            ok = export in declared or sn in declared
            if ok:
                entries.append((export, pid, sn))
            else:
                skipped.append((sn, pid))
        stem = token.replace(".lib", "").replace(".", "-")
        if stem == "coredll":
            stem = "coredll"
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
            fh.write("LIBRARY coredll.dll\nEXPORTS\n")
            for export, pid, sn in entries:
                fh.write(f"  {export}\n")
        n = len(entries)
        print(f"{out}: {n} exports from {token} "
              f"(skipped {len(skipped)}: not declared by headers)")
        if skipped:
            print("   skipped: " + ", ".join(f"{s}({p})" for s, p in skipped))


if __name__ == "__main__":
    main()
