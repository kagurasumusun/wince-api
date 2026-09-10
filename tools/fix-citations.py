#!/usr/bin/env python3
"""fix-citations.py -- repair wrong page-id citations in include/.

The three-generation sweep's citation audit found headers citing the
wrong page id (mostly off-by-N id transcription slips from the
harvest era, e.g. Iptypes.h cited ms895041 = DMTASKINFO for
IP_DAD_STATE).  This tool:

  1. extracts *name citations*  /* msXXXX "NAME" ... */  and
     /* msXXXX NAME: ... */  (including the held-ledger records),
  2. flags those whose cited page's own <title> is a different
     symbol,
  3. resolves the correct id through the preserved-corpus title
     index (corpus INDEX.txt + build/rows.json titles), and
  4. verifies the candidate page actually prints the name, then
     rewrites the citation in place.

Prose citations (book-index references, member-of-struct notes where
no same-named page exists) are left untouched.  Every change is
printed; --dry shows what would change.
"""
import html
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INC = os.path.join(ROOT, "include")
INDEX = "/home/user/.cache/wince-docs-corpus/INDEX.txt"

CITE_RE = re.compile(
    r"/\*\s*((?:ms|aa|ee)\d{4,})\s+(?:\"([A-Za-z_][\w]*)\"|"
    r"([A-Za-z_]\w*):)")


def norm(s):
    return re.sub(r"[^a-z0-9]+", " ", s.lower()).strip()


def load_title_index():
    """{normtitle: [bare ids]} from the corpus INDEX + rows.json."""
    idx = {}
    def add(title, pid):
        t = norm(title.split("(")[0])
        if t:
            idx.setdefault(t, []).append(pid.split("(")[0])
    try:
        for line in open(INDEX, encoding="utf-8"):
            parts = line.rstrip("\n").split("\t")
            if len(parts) >= 3:
                add(parts[1], parts[0])
    except OSError:
        pass
    for r in json.load(open(os.path.join(ROOT, "build", "rows.json"))):
        add(r["title"], r["id"])
    return idx


def page_title(pid):
    for tree in ("pages", "pages4", "pages6"):
        p = os.path.join(ROOT, "build", tree, pid.split("(")[0] + ".html")
        if os.path.exists(p):
            raw = open(p, encoding="utf-8", errors="replace").read()
            m = re.search(r"<title>(.*?)(?:\s*\|\s*Microsoft Learn)?"
                          r"</title>", raw, re.S)
            return html.unescape(m.group(1)).strip() if m else ""
    return None


def page_prints(pid, name):
    for tree in ("pages", "pages4", "pages6"):
        p = os.path.join(ROOT, "build", tree, pid.split("(")[0] + ".html")
        if os.path.exists(p):
            raw = open(p, encoding="utf-8", errors="replace").read()
            return name in raw
    return False


def main():
    dry = "--dry" in sys.argv
    idx = load_title_index()
    changes = skips = 0
    for fn in sorted(os.listdir(INC)):
        if not fn.endswith(".h"):
            continue
        path = os.path.join(INC, fn)
        t = open(path, encoding="utf-8", errors="replace").read()
        out = []
        pos = 0
        for m in CITE_RE.finditer(t):
            pid, quoted, coloned = m.group(1), m.group(2), m.group(3)
            name = quoted or coloned
            out.append(t[pos:m.start()])
            pos = m.end()
            title = page_title(pid)
            if title is None:
                out.append(m.group(0))
                continue
            tn = norm(title.split("(")[0])
            nn = norm(name.split("(")[0])
            if not nn or tn == nn or nn in tn or tn in nn:
                out.append(m.group(0))
                continue
            # wrong citation? find the page that really is `name`
            cands = [c for c in idx.get(nn, [])
                     if c != pid.split("(")[0]]
            fixed = None
            for c in cands:
                ct = page_title(c)
                if ct and norm(ct.split("(")[0]) == nn and \
                        page_prints(c, name):
                    fixed = c
                    break
            if fixed:
                new = m.group(0).replace(pid, fixed)
                out.append(new)
                print(f"[fix] {fn}: {pid} -> {fixed} "
                      f"({name}; cited page was {title.split('(')[0]})")
                changes += 1
            else:
                if re.match(r"^[A-Z][A-Za-z_:]*$", name) or quoted:
                    print(f"[skip] {fn}: {pid} cited for {name} "
                          f"but page is {title.split('(')[0]!r}; "
                          f"no same-titled page")
                skips += 1
                out.append(m.group(0))
        out.append(t[pos:])
        new_t = "".join(out)
        if new_t != t and not dry:
            open(path, "w", encoding="utf-8").write(new_t)
    print(f"[fix-citations] changed {changes}, left {skips} flagged")
    return 0


if __name__ == "__main__":
    sys.exit(main())
