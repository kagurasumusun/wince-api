#!/usr/bin/env python3
"""ce-manifest.py -- build a page manifest from the official Learn TOC.

The Microsoft Learn "previous-versions/windows/embedded" table of
contents (the machine-readable toc.json published at
https://learn.microsoft.com/en-us/previous-versions/windows/embedded/toc.json)
is the official index of the CE-era documentation.  This tool walks
that TOC, locates a named reference book under the Windows CE 5.0
Product Documentation, and writes the book's leaf pages to a manifest
file, one line per page:

    <page-id>\t<page title>

Example:

    python3 tools/ce-manifest.py /tmp/toc.json "Synchronization Reference" \
        tools/manifests/synchronization.manifest

The manifest therefore contains only OS-fact identifiers (official
page addresses/titles) transcribed from the official index -- it is
not third-party content.

Run after downloading toc.json from the official URL above.
"""

import json
import re
import sys


def walk(node, ancestors=()):
    """Yield (title, href, ancestors) for every node in the TOC."""
    if isinstance(node, list):
        for child in node:
            yield from walk(child, ancestors)
        return
    title = node.get("toc_title") or node.get("title") or ""
    yield title, node.get("href") or "", ancestors
    for child in node.get("children") or []:
        yield from walk(child, ancestors + (title,))


def find_book(root, book_title, anchors=()):
    """Return the first node titled book_title that lives under the
    Windows CE 5.0 Product Documentation index; when *anchors* are
    given every one of them must appear among the node's ancestors
    (this disambiguates books whose names repeat, e.g. under the
    driver documentation)."""
    for title, href, anc in walk(root):
        if (title == book_title and "Windows CE 5.0" in anc
                and "Product Documentation" in anc
                and all(a in anc for a in anchors)):
            return title, href, anc
    return None


def main():
    if len(sys.argv) < 4:
        sys.exit(__doc__)
    toc_path, book_title, out_path = sys.argv[1], sys.argv[2], sys.argv[3]
    anchors = tuple(sys.argv[4:])

    with open(toc_path, encoding="utf-8") as fh:
        toc = json.load(fh)

    found = find_book(toc["items"], book_title, anchors)
    if not found:
        sys.exit(f"book {book_title!r} not found under Windows CE 5.0 "
                 "Product Documentation (anchors: "
                 + ", ".join(anchors) + ")")
    title, _href, anc = found

    # Re-walk to collect this book's subtree (nodes are shared, so walk
    # by (title,ancestors) prefix).
    prefix = anc + (title,)
    rows = []
    for t, h, a in walk(toc["items"]):
        if not a[: len(prefix)] == prefix:
            continue
        if not h:  # intermediate node (has children, no page)
            continue
        m = re.search(r"([a-z]{2}\d+)\(v=msdn\.10\)$", h)
        if m:
            rows.append((m.group(1), t))
        else:
            # out-of-archive hrefs (rare) are recorded so coverage is
            # visible, with an empty id marker.
            rows.append(("", t + "  [" + h + "]"))

    with open(out_path, "w", encoding="utf-8") as fh:
        for pid, t in rows:
            fh.write(f"{pid}\t{t}\n")
    n = sum(1 for pid, _ in rows if pid)
    print(f"book: {' / '.join(prefix)}\n{len(rows)} leaf pages, "
          f"{n} in the (v=msdn.10) archive -> {out_path}")


if __name__ == "__main__":
    main()
