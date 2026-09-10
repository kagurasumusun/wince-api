#!/usr/bin/env python3
"""ce-gwes-manifest.py -- regenerate GWES Reference sub-book manifests from TOC.

The Microsoft Learn "previous-versions/windows/embedded" table of contents
(machine-readable toc.json published at
https://learn.microsoft.com/en-us/previous-versions/windows/embedded/toc.json)
is the official index of the CE-era documentation.  In the current Learn
navigation the Windows CE 5.0 Product Documentation archive is nested under
"Mobile and Embedded Development / Windows Embedded / Windows Embedded
Compact / Windows CE 5.0"; earlier revisions of this site exposed it
directly under previous-versions.  This tool therefore never assumes a fixed
tree position: it first locates the "Windows CE 5.0" node anywhere in the
TOC and then resolves every target book relative to that node's
"Product Documentation" child.  Only leaves whose href ends in
"(v=msdn.10)" are emitted, so a manifest holds official CE 5.0 page
identifiers only (page id + page title), matching the format written by
tools/ce-manifest.py.

Target books are given as TOC-relative ancestor titles below Product
Documentation, one per line in the targets file, e.g.

    GWES Reference/Window Control Reference/Combo Boxes Reference/Combo Boxes Messages

Leaves strictly below the target path are written to
tools/manifests/gwes-<slug>.manifest where the slug is the final title
lowercased with runs of non-alphanumerics collapsed to '-' (or an explicit
slug may follow a TAB on the line, e.g. "\tcontrol-styles").

Usage:
    python3 tools/ce-gwes-manifest.py /tmp/toc.json [targets-file]

The default targets file is tools/gwes-targets.txt next to this script.
Every sub-book total printed can be cross-checked against the official book
catalog in tools/catalogs/books-windows-ce-50.tsv.
"""

import json
import os
import re
import sys

SUFFIX = re.compile(r"\(v=msdn\.10\)$")
DEFAULT_TARGETS = os.path.join(os.path.dirname(os.path.abspath(__file__)), "gwes-targets.txt")


def find_node(nodes, segs):
    """Depth-first search for the node reached by following *segs* (a list
    of node titles) from *nodes*.  Descends into every child so that the
    CE 5.0 archive is found no matter how deeply Learn nests it."""
    if not segs:
        return None
    for n in nodes:
        ti = n.get("toc_title") or n.get("title") or ""
        if ti == segs[0]:
            if len(segs) == 1:
                return n
            hit = find_node(n.get("children") or [], segs[1:])
            if hit is not None:
                return hit
        else:
            hit = find_node(n.get("children") or [], segs)
            if hit is not None:
                return hit
    return None


def collect(node, rel=()):
    """Yield (ancestor-titles, msdn-id-or-empty, title, href) for every leaf
    strictly below *node* (children are included recursively, the node
    itself is not)."""
    out = []
    for n in node.get("children") or []:
        ti = n.get("toc_title") or n.get("title") or ""
        href = n.get("href") or ""
        rel2 = rel + (ti,)
        m = SUFFIX.search(href)
        pid = href[: m.start()] if m else ""
        out.append((rel2, pid, ti, href))
        out.extend(collect(n, rel2))
    return out


def main():
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    toc_path = sys.argv[1]
    targets_path = sys.argv[2] if len(sys.argv) > 2 else DEFAULT_TARGETS
    toc = json.load(open(toc_path, encoding="utf-8"))
    items = toc.get("items") if isinstance(toc, dict) else toc

    ce5 = find_node(items, ["Windows CE 5.0"])
    if ce5 is None:
        sys.exit("error: Windows CE 5.0 node not found in TOC")
    pd = find_node(ce5.get("children") or [], ["Product Documentation"])
    if pd is None:
        sys.exit("error: Product Documentation node not found under Windows CE 5.0")
    leaves = collect(pd)
    print("CE5 Product Documentation leaves:", len(leaves), file=sys.stderr)

    raw = [l.rstrip("\n") for l in open(targets_path, encoding="utf-8")]
    failures = 0
    for line in raw:
        if not line or line.startswith("#"):
            continue
        path, _, slug = line.partition("\t")
        segs = tuple(s for s in path.split("/") if s)
        if not slug:
            slug = re.sub(r"[^A-Za-z0-9]+", "-", segs[-1].lower()).strip("-")
        # Each rel tuple ends with the page's own title; the book chain is
        # rel[:-1].  A page belongs to the target book when its ancestor
        # chain (rel with the page's own title removed) equals the target's
        # absolute path, i.e. the page sits directly under that book.
        rows = [
            (pid, ti)
            for rel, pid, ti, href in leaves
            if pid and len(rel) == len(segs) + 1 and rel[:-1] == segs
        ]
        out = os.path.join(os.path.dirname(os.path.abspath(__file__)), "manifests", f"gwes-{slug}.manifest")
        with open(out, "w", encoding="utf-8") as fh:
            for pid, ti in rows:
                fh.write(f"{pid}\t{ti}\n")
        print(f"{slug:26s} {len(rows):4d}  {out}", file=sys.stderr)
        if not rows:
            failures += 1
    if failures:
        sys.exit(f"{failures} target(s) produced no leaves (check path spelling)")
    print("ok", file=sys.stderr)


if __name__ == "__main__":
    main()
