#!/usr/bin/env python3
"""ce-rows-local.py -- append page records to build/rows.json from local pages.

tools/ce-fetch.py both downloads the official page
(learn.microsoft.com previous-versions, (v=msdn.10)) and parses it into a
row of build/rows.json.  When pages were already downloaded by another
fetcher (e.g. the batch loader in the build tree), this tool performs only
the parse half so rows.json stays the harvested record set without
re-fetching.  ids already present in rows.json are skipped.

Usage:
    python3 tools/ce-rows-local.py tools/manifests/gwes-dialog-functions.manifest [...]
"""

import importlib.util
import json
import os
import sys

_TOOLS = os.path.dirname(os.path.abspath(__file__))
_spec = importlib.util.spec_from_file_location(
    "ce_fetch", os.path.join(_TOOLS, "ce-fetch.py"))
ce_fetch = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(ce_fetch)


def main():
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    rows = []
    dbpath = os.path.join(os.path.dirname(__file__), "..", "build", "rows.json")
    if os.path.exists(dbpath):
        rows = json.load(open(dbpath, encoding="utf-8"))
    have = {ce_fetch.split_id(r["id"])[0] for r in rows}
    added = 0
    for manifest in sys.argv[1:]:
        for line in open(manifest, encoding="utf-8"):
            line = line.rstrip("\n")
            if not line.strip() or "\t" not in line:
                continue
            pid, title = line.split("\t", 1)
            root, _ = ce_fetch.split_id(pid)
            if root in have:
                continue
            rec = ce_fetch.parse(pid, title)
            if "error" not in rec:
                have.add(root)
                added += 1
            rows.append(rec)
            print(f"{pid}\t{title[:52]:54} lib={rec.get('lib','') or '-':20} "
                  f"hdr={rec.get('header','') or '-':14} sig={bool(rec.get('sig'))}")
    rows.sort(key=lambda r: (r["id"], r["title"]))
    with open(dbpath, "w", encoding="utf-8") as fh:
        json.dump(rows, fh, ensure_ascii=False, indent=1)
    print(f"added {added} rows; total {len(rows)}")


if __name__ == "__main__":
    main()
