#!/usr/bin/env python3
"""ce-versions.py -- snapshot the official Learn CE doc-tree catalogs.

The Microsoft Learn archive serves each Windows CE / Windows Embedded
product documentation set as a subtree of one machine-readable index:

    https://learn.microsoft.com/en-us/previous-versions/windows/embedded/toc.json

(12 MB, ~160k nodes).  That single index contains *all* archived
Windows Embedded trees, including every published Windows CE version:

    Windows CE 2.1        (1 leaf  -- stub only)
    Windows CE 3.0        (1 leaf  -- stub only)
    Windows CE .NET       (~6.4k  leaves, all (v=msdn.10))
    Windows CE 5.0        (~22.9k leaves, all (v=msdn.10))
    Windows Embedded CE 6.0 (~23.8k leaves, (v=winembedded.60))
    Windows Embedded Compact 7      (~20.3k)
    Windows Embedded Compact 2013   (~16.9k)

Windows CE 1.0 / 2.0 / 2.1x / 3.0 full documentation was never
republished on Learn -- only their Requirement rows live on, carried
forward on the CE .NET / CE 5.0 pages ("Windows CE x.0 and later").

This tool writes, for each requested version, a flat catalog TSV of
every leaf page in that subtree:

    <page-id>(v=<version-tag>)   <page title>

plus a books summary (book path -> leaf count).  Catalog lines are
OS-fact identifiers transcribed from the official index; they are not
third-party content.

Usage:
    python3 tools/ce-versions.py toc.json outdir \
        "Windows CE .NET" "Windows CE 5.0" "Windows Embedded CE 6.0"
"""

import json
import os
import sys


def load(path):
    return json.load(open(path, encoding="utf-8"))["items"]


def find(node, pred):
    if isinstance(node, list):
        for c in node:
            r = find(c, pred)
            if r is not None:
                return r
        return None
    if isinstance(node, dict):
        t = node.get("toc_title") or node.get("title") or ""
        if pred(t):
            return node
        for c in node.get("children") or []:
            r = find(c, pred)
            if r is not None:
                return r
    return None


def walk(node, anc=()):
    if isinstance(node, list):
        for c in node:
            yield from walk(c, anc)
        return
    t = node.get("toc_title") or node.get("title") or ""
    a = anc + (t,)
    ch = node.get("children") or []
    for c in ch:
        yield from walk(c, a)
    if not ch:
        yield t, node.get("href") or "", a


def leafcount(node):
    if isinstance(node, list):
        return sum(leafcount(c) for c in node)
    if not isinstance(node, dict):
        return 0
    ch = node.get("children") or []
    if not ch:
        return 1 if node.get("href") else 0
    return sum(leafcount(c) for c in ch)


def main():
    toc, outdir, names = sys.argv[1], sys.argv[2], sys.argv[3:]
    os.makedirs(outdir, exist_ok=True)
    root = load(toc)
    for name in names:
        node = find(root, lambda t: t == name)
        if node is None:
            print(f"!! {name!r} not found in TOC")
            continue
        slug = name.lower().replace(" ", "-").replace(".", "")
        cat = os.path.join(outdir, "catalog-" + slug + ".tsv")
        books = os.path.join(outdir, "books-" + slug + ".tsv")
        with open(cat, "w", encoding="utf-8", newline="\n") as fc, \
             open(books, "w", encoding="utf-8", newline="\n") as fb:
            total = 0
            for t, h, a in walk(node):
                if not h:
                    continue
                total += 1
                fc.write(f"{h}\t{t}\n")
            # book = any ancestor path; count leaves under each ancestor
            from collections import Counter
            cnt = Counter()
            for t, h, a in walk(node):
                if h:
                    cnt[" :: ".join(a[:-1])] += 1
            for book, n in sorted(cnt.items()):
                fb.write(f"{n}\t{book}\n")
            print(f"{name}: {total} leaves -> {cat} + {books}")


if __name__ == "__main__":
    main()
