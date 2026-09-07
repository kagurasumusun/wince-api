#!/usr/bin/env python3
"""ce-corpus.py -- manage the preserved official-page corpus.

The user workflow requires that the *full official page downloads* (raw
HTML of every MSDN/learn.microsoft.com CE page that wince-api harvests)
be (a) saved completely and pushed to GitHub, (b) deleted from the
workspace at the end of each working session, and (c) re-fetched from
GitHub at the start of the next session -- so a session never depends
on learn.microsoft.com reachability and the pages are preserved even
though the Learn archive may move.

The wince-api repository itself stays clean-room MIT: raw Microsoft
Learn HTML is NOT committed to it.  It is pushed to the separate
preservation repository `kagurasumusun/wince-docs-corpus` (attribution
+ CC BY 4.0 notice in that repo's README).

Repository layout mirrored by this tool (each "tree" is one Learn
version archive; page ids are unique per archive):

    pages5/<id>.html   ...  CE 5.0 archive      (v=msdn.10)
    pages6/<id>.html   ...  Windows Embedded CE 6.0  (v=winembedded.60)
    (future: pages4/ for the CE .NET tree when harvested)
    rows.json          ...  the harvested Requirement records
    catalogs/*.tsv     ...  official TOC snapshots
    INDEX.txt          ...  id<TAB>title<TAB>tree of every preserved page

Commands (run from the wince-api root; --corpus DIR selects the clone
of kagurasumusun/wince-docs-corpus; default ../wince-docs-corpus):

    export      copy build/pages, build/pages6, build/rows.json and
                tools/catalogs/*.tsv into the corpus clone, rebuild
                INDEX.txt, and `git add -A` (does not commit/push).
    import      copy the preserved corpus back into build/pages,
                build/pages6 (any files already present are skipped so
                a partial refetch can be resumed) and write rows.json.
    verify      report how many manifest leaves exist per tree and how
                many have a preserved page in the corpus.
"""

import argparse
import os
import shutil
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# (source dir under build/, destination dir name in the corpus)
TREES = [
    ("pages", "pages5"),      # CE 5.0 archive, (v=msdn.10)
    ("pages6", "pages6"),     # Windows Embedded CE 6.0 archive
]


def _build(src, dst):
    return os.path.join(ROOT, src), dst


def export_corpus(corpus):
    os.makedirs(corpus, exist_ok=True)
    manifest = []
    for src_rel, dst_dir in TREES:
        src = os.path.join(ROOT, "build", src_rel)
        out = os.path.join(corpus, dst_dir)
        os.makedirs(out, exist_ok=True)
        if not os.path.isdir(src):
            print(f"[corpus] (no build/{src_rel}; nothing to export)")
            continue
        for fn in sorted(os.listdir(src)):
            if not fn.endswith(".html"):
                continue
            shutil.copyfile(os.path.join(src, fn), os.path.join(out, fn))
            manifest.append(f"{os.path.splitext(fn)[0]}\t{fn}\t{dst_dir}")
        print(f"[corpus] exported {len(os.listdir(out))} html -> {dst_dir}/")
    # rows.json
    rows = os.path.join(ROOT, "build", "rows.json")
    if os.path.exists(rows):
        shutil.copyfile(rows, os.path.join(corpus, "rows.json"))
        print("[corpus] exported rows.json")
    # catalogs (official TOC snapshots)
    cat_in = os.path.join(ROOT, "tools", "catalogs")
    cat_out = os.path.join(corpus, "catalogs")
    if os.path.isdir(cat_in):
        os.makedirs(cat_out, exist_ok=True)
        n = 0
        for fn in os.listdir(cat_in):
            if fn.endswith(".tsv"):
                shutil.copyfile(os.path.join(cat_in, fn), os.path.join(cat_out, fn))
                n += 1
        print(f"[corpus] exported {n} catalog tsv")
    with open(os.path.join(corpus, "INDEX.txt"), "w", encoding="utf-8") as fh:
        fh.write("# id<TAB>file<TAB>tree -- preserved official CE pages\n")
        for line in manifest:
            fh.write(line + "\n")
    print(f"[corpus] INDEX.txt: {len(manifest)} pages")


def import_corpus(corpus):
    """Restore pages into build/ from the corpus clone (idempotent)."""
    for src_dir, src_rel in [(d, s) for s, d in TREES]:
        srcdir = os.path.join(corpus, src_dir)
        dst = os.path.join(ROOT, "build", src_rel)
        if not os.path.isdir(srcdir):
            print(f"[corpus] (corpus has no {src_dir}/; nothing to import)")
            continue
        os.makedirs(dst, exist_ok=True)
        n_skip = n_copy = 0
        for fn in sorted(os.listdir(srcdir)):
            if not fn.endswith(".html"):
                continue
            target = os.path.join(dst, fn)
            if os.path.exists(target):
                n_skip += 1
            else:
                shutil.copyfile(os.path.join(srcdir, fn), target)
                n_copy += 1
        print(f"[corpus] {src_dir}: restored {n_copy}, already present {n_skip} -> build/{src_rel}")
    rows = os.path.join(corpus, "rows.json")
    if os.path.exists(rows):
        dst = os.path.join(ROOT, "build", "rows.json")
        os.makedirs(os.path.dirname(dst), exist_ok=True)
        shutil.copyfile(rows, dst)
        print("[corpus] restored rows.json")
    cat_in = os.path.join(corpus, "catalogs")
    if os.path.isdir(cat_in):
        dst = os.path.join(ROOT, "tools", "catalogs")
        os.makedirs(dst, exist_ok=True)
        for fn in os.listdir(cat_in):
            if fn.endswith(".tsv"):
                shutil.copyfile(os.path.join(cat_in, fn), os.path.join(dst, fn))
        print("[corpus] restored catalogs")


def verify_corpus(corpus):
    for src_dir in [d for _, d in TREES]:
        d = os.path.join(corpus, src_dir)
        print(f"[corpus] {src_dir}: {len(os.listdir(d)) if os.path.isdir(d) else 0} pages")
    if os.path.exists(os.path.join(corpus, "rows.json")):
        import json
        n = len(json.load(open(os.path.join(corpus, "rows.json"), encoding="utf-8")))
        print(f"[corpus] rows.json: {n} records")
    print(f"[corpus] INDEX.txt exists: {os.path.exists(os.path.join(corpus, 'INDEX.txt'))}")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("action", choices=["export", "import", "verify"])
    ap.add_argument("--corpus", default=os.path.join(
        os.path.dirname(ROOT), "wince-docs-corpus"))
    a = ap.parse_args()
    if a.action == "export":
        export_corpus(a.corpus)
    elif a.action == "import":
        import_corpus(a.corpus)
    else:
        verify_corpus(a.corpus)


if __name__ == "__main__":
    sys.exit(main())
