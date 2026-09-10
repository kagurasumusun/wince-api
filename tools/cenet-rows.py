#!/usr/bin/env python3
"""cenet-rows.py -- parse a harvested Windows CE .NET page tree into rows.

The Windows CE .NET archive (the earliest *complete* CE product
documentation published on Learn; ~6.4k leaves, all `(v=msdn.10)`)
shares the same page layout as the CE 5.0 books: a Requirements
paragraph with `OS Versions: / Header: / Link Library:` labels.  This
tool reuses the CE 5.0 parser (`tools/ce-fetch.py`) against the page
cache in `build/pages4/` and writes `build/rows4.json`.

Usage:
    python3 tools/cenet-rows.py            # parse every page present in
                                           #   build/pages4/ (catalog order)
    python3 tools/cenet-rows.py --limit N  # parse at most N pages (dev)

Every record keeps its catalog title (`tools/catalogs/catalog-*.tsv`)
so later name-based twin reconciliation across the three CE trees
(CE .NET / CE 5.0 / CE 6.0) can be driven from the committed catalogs
alone.  ids already present in rows4.json are skipped, so a partial
harvest can be re-parsed after a resume fetch.
"""

import importlib.util
import json
import os
import sys

_TOOLS = os.path.dirname(os.path.abspath(__file__))
_ROOT = os.path.join(_TOOLS, "..")
PAGES4 = os.path.join(_ROOT, "build", "pages4")
CATALOG = os.path.join(_TOOLS, "catalogs", "catalog-windows-ce-net.tsv")
OUT = os.path.join(_ROOT, "build", "rows4.json")

_spec = importlib.util.spec_from_file_location(
    "ce_fetch", os.path.join(_TOOLS, "ce-fetch.py"))
ce_fetch = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(ce_fetch)


def main():
    limit = None
    args = sys.argv[1:]
    if "--limit" in args:
        limit = int(args[args.index("--limit") + 1])
    os.makedirs(os.path.dirname(OUT), exist_ok=True)
    rows = []
    if os.path.exists(OUT):
        rows = json.load(open(OUT, encoding="utf-8"))
    have = {r["id"].split("(")[0] for r in rows}
    # point the shared parser's cache at the CE .NET tree
    ce_fetch.CACHE = os.path.normpath(PAGES4)
    added = 0
    for line in open(CATALOG, encoding="utf-8"):
        line = line.rstrip("\n")
        if not line:
            continue
        pid, title = line.split("\t", 1)
        root = pid.split("(")[0]
        if root in have:
            continue
        if not os.path.exists(os.path.join(PAGES4, root + ".html")):
            continue
        rec = ce_fetch.parse(pid, title)
        if "error" in rec:
            continue
        rows.append(rec)
        have.add(root)
        added += 1
        if limit is not None and added >= limit:
            break
    rows.sort(key=lambda r: r["id"])
    with open(OUT, "w", encoding="utf-8") as fh:
        json.dump(rows, fh, ensure_ascii=False, indent=1)
    print(f"added {added} rows; total {len(rows)}")


if __name__ == "__main__":
    main()
