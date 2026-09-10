#!/usr/bin/env python3
"""ce-text.py -- print the main article text of a fetched official CE page.

Usage:  python3 tools/ce-text.py ms885177 [ms886764 ...]

Reads build/pages/<id>.html (created by ce-fetch.py) and prints the
article body text (headings, syntax, parameters, remarks, requirements)
with the surrounding chrome removed -- a compact reference for writing
the header declarations.
"""

import html
import os
import re
import sys

CACHE = os.path.join(os.path.dirname(__file__), "..", "build", "pages")


def article_text(pid):
    raw = open(os.path.join(CACHE, pid + ".html"), encoding="utf-8",
               errors="replace").read()
    # main content: from the article <h1> (the first one in the page)
    # to the copyright line at the foot of the article.
    start = raw.find("<h1")
    if start < 0:
        start = 0
    end = raw.find("© 2006", start)
    if end < 0:
        end = raw.find('id="feedback"', start)
    if end < 0:
        end = len(raw)
    body = raw[start:end]
    body = re.sub(r"<script.*?</script>", " ", body, flags=re.S | re.I)
    body = re.sub(r"<style.*?</style>", " ", body, flags=re.S | re.I)
    # keep heading markers for readability
    body = re.sub(r"<h([1-6])[^>]*>", r"\n\n### \n", body)
    body = re.sub(r"<br\s*/?>", "\n", body)
    body = re.sub(r"</li>", "\n", body)
    body = re.sub(r"</p>|</tr>", "\n", body)
    body = re.sub(r"<[^>]+>", " ", body)
    body = html.unescape(body)
    lines = [re.sub(r"[ \t]+", " ", ln).strip() for ln in body.split("\n")]
    out = []
    blank = 0
    for ln in lines:
        if not ln:
            blank += 1
            if blank > 1:
                continue
        else:
            blank = 0
        out.append(ln)
    return "\n".join(out)


def main():
    for pid in sys.argv[1:]:
        print("=" * 24, pid, "=" * 24)
        try:
            print(article_text(pid))
        except FileNotFoundError:
            print(f"(page {pid} not fetched; run ce-fetch.py first)")


if __name__ == "__main__":
    main()
