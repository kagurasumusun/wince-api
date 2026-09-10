#!/usr/bin/env python3
"""twin-fetch.py -- fetch the missing CE 6.0 twin pages (sweep feed).

Reads a list of tagged page ids (one per line, e.g.
``ee488506(v=winembedded.60)``) on stdin or from the file given as
argv[1], downloads each from the Learn previous-versions archive into
``build/pages6/<bare-id>.html`` (the corpus naming convention), and
reports failures to ``build/twin-fetch-fail.log``.  Existing files are
skipped, so the run is resumable.

Usage:
    python3 tools/twin-fetch.py /tmp/miss6.txt
"""
import os
import re
import sys
import time
import urllib.request
import urllib.error
from concurrent.futures import ThreadPoolExecutor, as_completed

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BASE = "https://learn.microsoft.com/en-us/previous-versions/windows/embedded/{}"
UA = ("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 "
      "(KHTML, like Gecko) Chrome/120 Safari/537.36")
OUT = os.path.join(ROOT, "build", "pages6")
FAILLOG = os.path.join(ROOT, "build", "twin-fetch-fail.log")
WORKERS = int(os.environ.get("MEGA_WORKERS", "10"))


def split_id(pid):
    m = re.search(r'\((v=[a-z0-9.]+)\)$', pid.strip())
    if m:
        return pid.strip()[:m.start()], m.group(0)
    return pid.strip(), ""


def fetch(pid):
    bare, tag = split_id(pid)
    dest = os.path.join(OUT, bare + ".html")
    if os.path.exists(dest) and os.path.getsize(dest) > 1024:
        return (pid, "have")
    url = BASE.format(pid.strip())
    for attempt in range(4):
        try:
            req = urllib.request.Request(url, headers={"User-Agent": UA})
            with urllib.request.urlopen(req, timeout=45) as r:
                data = r.read()
            if len(data) < 1024:
                raise IOError(f"short page {len(data)}")
            with open(dest, "wb") as fh:
                fh.write(data)
            return (pid, "ok")
        except Exception as e:
            if attempt == 3:
                return (pid, f"FAIL {e}")
            time.sleep(1.5 * (attempt + 1))
    return (pid, "FAIL exhausted")


def main():
    ids = []
    src = sys.argv[1] if len(sys.argv) > 1 else "/tmp/miss6.txt"
    for line in open(src, encoding="utf-8"):
        line = line.strip()
        if line and not line.startswith("#"):
            ids.append(line)
    os.makedirs(OUT, exist_ok=True)
    print(f"[twin-fetch] {len(ids)} pages to fetch -> {OUT}", flush=True)
    fails = []
    done = 0
    with ThreadPoolExecutor(max_workers=WORKERS) as ex:
        futs = {ex.submit(fetch, p): p for p in ids}
        for fut in as_completed(futs):
            pid, status = fut.result()
            done += 1
            if status.startswith("FAIL"):
                fails.append(f"{pid}\t{status}")
            if done % 250 == 0:
                print(f"[twin-fetch] {done}/{len(ids)} ({len(fails)} fails)",
                      flush=True)
    if fails:
        with open(FAILLOG, "w", encoding="utf-8") as fh:
            fh.write("\n".join(fails) + "\n")
    print(f"[twin-fetch] DONE {done}, fails {len(fails)}"
          f" (log: {FAILLOG})", flush=True)
    return 0


if __name__ == "__main__":
    sys.exit(main())
