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


def fetch(pid):
    path = os.path.join(CACHE, pid + ".html")
    if os.path.exists(path) and os.path.getsize(path) > 20000:
        return path
    url = BASE.format(pid + "(v=msdn.10)")
    req = urllib.request.Request(url, headers={"User-Agent": UA})
    for attempt in range(3):
        try:
            with urllib.request.urlopen(req, timeout=60) as resp:
                data = resp.read()
            break
        except Exception as exc:  # noqa: BLE001
            if attempt == 2:
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
    raw = open(os.path.join(CACHE, pid + ".html"), encoding="utf-8",
               errors="replace").read()
    flat = text_of(raw)
    rec = {"id": pid, "title": title, "sig": "", "os": "", "header": "",
           "lib": "", "dll": "", "params": [], "notes": []}

    # --- signature: first <pre>/<code> block that contains the page's
    # function name and balanced parentheses.
    blocks = re.findall(r"<(?:pre|code)[^>]*>(.*?)</(?:pre|code)>",
                        raw, flags=re.S | re.I)
    short = re.sub(r"\s*\(Windows CE [^)]*\)\s*$", "", title).strip()
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
    seg = ""
    m = re.search(r'id="requirements"(.*?)(?:id="see-also"|id="feedback"|\Z)',
                  raw, flags=re.S | re.I)
    if m:
        seg = m.group(1)
    if seg:
        for key, field in (("OS Versions:", "os"), ("Header:", "header"),
                           ("Link Library:", "lib")):
            fm = re.search(re.escape(key) + r"\s*(.*?)(?:<br\s*/?>|</p>)",
                           seg, flags=re.S | re.I)
            if fm:
                rec[field] = re.sub(r"\s+", " ", strip_tags(fm.group(1))).strip()
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
    have = {r["id"] for r in out}
    for pid, title in rows:
        if pid in have:
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
