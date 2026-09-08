#!/usr/bin/env python3
"""ce-fetch.py -- download and parse official CE reference pages.

For every page id in a manifest (see ce-manifest.py) this tool:

1. downloads the official page
   https://learn.microsoft.com/en-us/previous-versions/windows/embedded/<id>(v=msdn.10)
   into build/pages/<id>.html (cached), and
2. parses the page into build/pages/<id>.json containing only facts:
   the documented C prototype, the Requirements rows (OS Versions /
   Header / Link Library), the parameter list ([in]/[out], type, name,
   CE-specific constraints such as "Unsupported; set to NULL"), and a
   short list of CE-relevant notes.

Nothing is copied into headers automatically: the parsed records are
the *evidence* the header text is written from (the repo's zero-gap
policy).  Output lives under build/ which is not committed.

Usage:
    python3 tools/ce-fetch.py tools/manifests/synchronization.manifest
"""

import html
import json
import os
import re
import subprocess
import sys
import time
import urllib.request

BASE = "https://learn.microsoft.com/en-us/previous-versions/windows/embedded/{}"
UA = ("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 "
      "(KHTML, like Gecko) Chrome/120 Safari/537.36")
OUT = "build/pages"
# leave the tree: keep per-run caching outside the repo snapshot
CACHE = os.path.join(os.path.dirname(__file__), "..", "build", "pages")


def split_id(pid):
    """'ms891279(v=msdn.10)' -> ('ms891279', 'v=msdn.10').  A bare id
    (as in the per-book manifests) defaults to the CE 5.0 archive tag.
    The tag always carries its 'v=' prefix: Learn serves the archive
    only under the full '(v=...)' version tag (a bare '(msdn.10)'
    path 404s -- the platform started enforcing the tag strictly,
    which is why older no-tag fetches that once resolved now 404)."""
    pid = pid.strip()
    m = re.match(r"^(.*?)\((v=[\w.]+)\)$", pid)
    if m:
        return m.group(1), m.group(2)
    return pid, "v=msdn.10"


def fetch(pid):
    root, tag = split_id(pid)
    path = os.path.join(CACHE, root + ".html")
    if os.path.exists(path) and os.path.getsize(path) > 20000:
        return path
    url = BASE.format(root + "(" + tag + ")")
    req = urllib.request.Request(url, headers={"User-Agent": UA})
    # Transient 404s are observed under Learn rate limiting: retry
    # them with long backoff before giving up.
    for attempt in range(4):
        try:
            with urllib.request.urlopen(req, timeout=60) as resp:
                data = resp.read()
            break
        except urllib.error.HTTPError as exc:
            if exc.code == 404 and attempt < 3:
                time.sleep(30 * (attempt + 1))
                continue
            raise
        except Exception:  # noqa: BLE001
            if attempt == 3:
                raise
            time.sleep(2 * (attempt + 1))
    os.makedirs(CACHE, exist_ok=True)
    tmp = path + ".tmp"
    with open(tmp, "wb") as fh:
        fh.write(data)
    os.replace(tmp, path)
    time.sleep(0.15)
    return path


def strip_tags(seg):
    seg = re.sub(r"<[^>]+>", "", seg)
    return html.unescape(seg)


def text_of(raw):
    raw = re.sub(r"<script.*?</script>", " ", raw, flags=re.S | re.I)
    raw = re.sub(r"<style.*?</style>", " ", raw, flags=re.S | re.I)
    txt = re.sub(r"<[^>]+>", " ", raw)
    txt = html.unescape(txt)
    return re.sub(r"\s+", " ", txt)


def parse(pid, title):
    root, _tag = split_id(pid)
    raw = open(os.path.join(CACHE, root + ".html"), encoding="utf-8",
               errors="replace").read()
    flat = text_of(raw)
    rec = {"id": pid, "title": title, "sig": "", "os": "", "header": "",
           "lib": "", "dll": "", "params": [], "notes": []}

    # --- signature: first <pre>/<code> block that contains the page's
    # function name and balanced parentheses.
    blocks = re.findall(r"<(?:pre|code)[^>]*>(.*?)</(?:pre|code)>",
                        raw, flags=re.S | re.I)
    # Strip the archive's disambiguation suffixes from the page title
    # ("socket (Windows Sockets)", "BLOB (Windows Sockets)") so the
    # prototype search key is the bare function/structure name.
    short = re.sub(r"\s*\(Windows (?:CE )?[^)]*\)\s*$", "", title).strip()
    for b in blocks:
        clean = re.sub(r"\s+", " ", strip_tags(b)).strip()
        if len(clean) > 320 or "(" not in clean or ")" not in clean:
            continue
        if not re.search(r"\b" + re.escape(short) + r"\s*\(", clean):
            continue
        rec["sig"] = clean
        break

    # --- Requirements rows (inside the "Requirements" section, where
    # fields are <strong>OS Versions:</strong> ... <br> ... </p>).
    # The archive prints the field label in two shapes:
    # <strong>OS Versions:</strong> ... (colon inside the
    # label tag) and <strong>OS Versions</strong>: ... (colon
    # outside it, sometimes with a leading space); match both.
    # The AYGShell book (M50) prints three more shapes: labels carry
    # non-breaking spaces (<strong>OS&nbsp;Versions:</strong>), the
    # library row is labelled "Library:" instead of "Link Library:"
    # (<strong>Library:</strong> aygshell.lib), and a following
    # "Windows Mobile Requirements" subsection carries the Windows
    # Mobile platform rows (Header: shlobj.h / Library: ceshell.lib).
    # The main section is the Windows CE layer: the segment stops at
    # the Windows Mobile subsection, whose rows are recorded
    # separately in rec["wm"] and never override the CE rows.
    seg = ""
    m = re.search(r'id="requirements"(.*?)'
                  r'(?:id="windows-mobile-requirements"|id="see-also"|'
                  r'id="feedback"|\Z)',
                  raw, flags=re.S | re.I)
    if m:
        seg = m.group(1).replace("&nbsp;", " ")
    if seg:
        # Alternation order matters: "Link Library" is preferred over
        # the shorter "Library" tail of the same label (the leftmost
        # match wins), so both label spellings parse.
        for key, field in (("OS Versions", "os"), ("Header", "header"),
                           ("Link Library|Library", "lib")):
            fm = re.search(r"\b(?:" + key + r")" +
                           r"(?:\s*</\w+>)?\s*:\s*(.*?)" +
                           r"(?:<br\s*/?>|</p>|<h\d)",
                           seg, flags=re.S | re.I)
            if fm:
                rec[field] = re.sub(r"\s+", " ", strip_tags(fm.group(1))).strip()
    wm = re.search(r'id="windows-mobile-requirements"(.*?)'
                   r'(?:id="see-also"|id="feedback"|\Z)',
                   raw, flags=re.S | re.I)
    if wm:
        wseg = wm.group(1).replace("&nbsp;", " ")
        wrows = []
        for key in ("Header", "Library", "OS Versions"):
            fm = re.search(r"\b" + key +
                           r"(?:\s*</\w+>)?\s*:\s*(.*?)"
                           r"(?:<br\s*/?>|</p>|<h\d)",
                           wseg, flags=re.S | re.I)
            if fm:
                wrows.append(key + ": " +
                             re.sub(r"\s+", " ",
                                    strip_tags(fm.group(1))).strip())
        if wrows:
            rec["wm"] = "; ".join(wrows)
    if not seg:  # fallback: textual scan of the last occurrences
        for key, field in (("OS Versions:", "os"), ("Header:", "header"),
                           ("Link Library:", "lib")):
            fm = re.search(re.escape(key) + r"\s*([^.]*?\.)", flat)
            if fm:
                rec[field] = fm.group(1).strip()
    m = re.search(r"DLL:\s*([A-Za-z0-9_.]+\.dll)", flat)
    if m:
        rec["dll"] = m.group(1).lower()

    # --- Parameters section (list items under the Parameters heading).
    pm = re.search(r"<h\d[^>]*id=\"parameters\"(.*?)"
                   r"<h\d[^>]*id=\"(?:return-values|remarks)\"",
                   raw, flags=re.S | re.I)
    if not pm:
        pm = re.search(r"(?is)<h[23][^>]*>.*?Parameters.*?</h[23]>(.*?)"
                       r"<h[23]", raw)
    if pm:
        for li in re.findall(r"<li>(.*?)</li>", pm.group(1),
                             flags=re.S | re.I):
            item = re.sub(r"<[^>]+>", " ", li)
            item = html.unescape(item)
            item = re.sub(r"\s+", " ", item).strip()
            if not item:
                continue
            pm_name = re.match(r"\s*[^ ]+\s*(\[[^\]]+\])?\s*(.*)$", item)
            rec["params"].append(item[:240])

    # --- CE-relevant note sentences (short markers only).
    markers = [
        "Unsupported; set to NULL", "not supported", "must be NULL",
        "must be set to NULL", "ignored", "Windows CE supports only the "
        "Unicode version", "cannot be a socket", "does not exist on ",
        "not recursive", "only operates on empty", "reserved",
    ]
    for mk in markers:
        for m in re.finditer(re.escape(mk), flat):
            start = max(0, m.start() - 90)
            rec["notes"].append(flat[start:m.start() + 200])
            break  # one note per marker is enough
    return rec


def main():
    if len(sys.argv) != 2:
        sys.exit(__doc__)
    manifest = sys.argv[1]
    rows = []
    with open(manifest, encoding="utf-8") as fh:
        for line in fh:
            line = line.rstrip("\n")
            if not line.strip():
                continue
            pid, title = line.split("\t", 1)
            if not pid:
                continue
            rows.append((pid, title))
    out = []
    dbpath = os.path.join(CACHE, "..", "rows.json")
    if os.path.exists(dbpath):
        with open(dbpath, encoding="utf-8") as fh:
            out = json.load(fh)
    # Error records (transient 404s etc.) are not "have": drop them so
    # a re-fetch replaces them with the parsed record.
    out = [r for r in out if "error" not in r]
    have = {split_id(r["id"])[0] for r in out}
    for pid, title in rows:
        root, _tag = split_id(pid)
        if root in have:
            print(f"{pid}\t{title[:52]:54} (cached)")
            continue
        try:
            fetch(pid)
            rec = parse(pid, title)
        except Exception as exc:  # noqa: BLE001
            print(f"!! {pid} {title}: {exc}", file=sys.stderr)
            rec = {"id": pid, "title": title, "error": str(exc)}
        out.append(rec)
        status = "sig" if rec.get("sig") else "no-sig"
        print(f"{pid}\t{title[:52]:54} {rec.get('lib','') or '-':18} "
              f"{rec.get('os','')[:34]:36} {status}")
    out.sort(key=lambda r: (r["id"], r["title"]))
    with open(dbpath, "w", encoding="utf-8") as fh:
        json.dump(out, fh, ensure_ascii=False, indent=1)


if __name__ == "__main__":
    main()
