#!/usr/bin/env python3
"""mine-values.py -- whole-corpus value mining for held names.

For every name-only held entry (the ``documented name-only (no value
published; held)`` ledger) this scans ALL preserved page trees
(build/pages, pages4, pages6, pagesw, pageswm) for a printed constant
value near the name -- value tables, #define prints, "name (0x...)"
rows.  Official Microsoft pages only (the trees are the Learn
archives; pagesw is the desktop Win32 reference).

Pass 1 is GNU grep (DFA, C speed) over the raw HTML for candidate
files; pass 2 is a Python window scan around each word-bounded name
hit.  Output: build/sweep/mine-values.tsv (name, header, cited_id,
tree, page_id, value, context) -- the adoption feed for the sweep.
"""
import html
import json
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INC = os.path.join(ROOT, "include")
SWEEP = os.path.join(ROOT, "build", "sweep")
TREES = ["pages", "pages4", "pages6", "pagesw", "pageswm"]

HELD_RE = re.compile(
    r"/\*\s*((?:ms|aa|ee)\d{4,})\s+(\w+):\s*"
    r"documented name-only \(no value published; held\)\s*\*/")

NUM_RE = re.compile(r"(0[xX][0-9A-Fa-f]{2,8}|\d{2,10})")


def clean(s):
    s = re.sub(r"<[^>]+>", " ", s)
    return html.unescape(re.sub(r"\s+", " ", s)).strip()


def main():
    names = {}
    for fn in sorted(os.listdir(INC)):
        if not fn.endswith(".h"):
            continue
        t = open(os.path.join(INC, fn), encoding="utf-8",
                 errors="replace").read()
        for m in HELD_RE.finditer(t):
            names.setdefault(m.group(2), (fn, m.group(1)))
    print(f"[mine] {len(names)} held names", flush=True)
    os.makedirs(SWEEP, exist_ok=True)
    patfile = os.path.join(SWEEP, "names.pat")
    with open(patfile, "w", encoding="utf-8") as fh:
        fh.write("\\b(" + "|".join(sorted(
            (re.escape(n) for n in names), key=len, reverse=True)) +
            ")\\b")
    cands = []
    for tree in TREES:
        d = os.path.join(ROOT, "build", tree)
        if not os.path.isdir(d):
            continue
        r = subprocess.run(
            ["grep", "-rlE", "-f", patfile, d],
            capture_output=True, text=True)
        fs = [f for f in r.stdout.split("\n") if f]
        print(f"[mine] {tree}: {len(fs)} candidate files", flush=True)
        cands += [(tree, f) for f in fs]
    name_re = re.compile(open(patfile).read())
    hits = {}
    for tree, path in cands:
        pid = os.path.basename(path)[:-5]
        raw = open(path, encoding="utf-8", errors="replace").read()
        # strip link/anchor hrefs: page-id urls precede names in the
        # raw HTML and pollute the window scan
        raw = re.sub(r'(?:href|src|id|data-[a-z-]+)="[^"]*"', "", raw)
        for m in name_re.finditer(raw):
            nm = m.group(1)
            win = raw[m.end():m.end() + 140]
            cwin = clean(win)
            vm = NUM_RE.search(cwin[:70])
            if not vm:
                continue
            gap = cwin[:vm.start()]
            # the value must sit right after the name (separators
            # only): " = 0x..", ": 0x..", "(0x..)", " 0x.." --
            # not after a prose run
            if len(gap) > 6 or re.search(r"[a-z]", gap):
                continue
            val = vm.group(1)
            # hex values, or decimal only in a #define print
            if not val.lower().startswith("0x") and \
                    "define" not in clean(raw[max(0, m.start() - 20):
                                              m.start()]).lower():
                continue
            if val.isdigit() and int(val) < 16:
                continue
            key = (nm, tree, pid)
            if key not in hits:
                seg = clean(raw[m.start():m.start() + 90])
                hits[key] = (val, seg[:70])
    out = os.path.join(SWEEP, "mine-values.tsv")
    with open(out, "w", encoding="utf-8") as fh:
        fh.write("name\theader\tcited_id\ttree\tpage_id\tvalue\tctx\n")
        for (nm, tree, pid), (val, ctx) in sorted(hits.items()):
            fh.write(f"{nm}\t{names[nm][0]}\t{names[nm][1]}\t{tree}\t"
                     f"{pid}\t{val}\t{ctx}\n")
    print(f"[mine] {len(hits)} (name,page) hits -> {out}")
    pername = {}
    for (nm, tree, pid), (val, ctx) in hits.items():
        pername.setdefault(nm, set()).add(val.lower())
    agree = {n: v for n, v in pername.items() if len(v) == 1}
    disagree = {n: v for n, v in pername.items() if len(v) > 1}
    print(f"[mine] unique-value names: {len(agree)}, "
          f"conflicting: {len(disagree)}")
    for n, v in list(disagree.items())[:25]:
        print("  CONFLICT", n, sorted(v))
    json.dump({n: sorted(v) for n, v in pername.items()},
              open(os.path.join(SWEEP, "mine-summary.json"), "w"),
              indent=1)


if __name__ == "__main__":
    main()
