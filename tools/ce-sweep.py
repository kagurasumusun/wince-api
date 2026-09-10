#!/usr/bin/env python3
"""ce-sweep.py -- the CE 4/5/6 three-generation sweep.

Compiles the shipped surface (include/) and the harvested Requirement
rows (build/rows.json, CE 5.0) against the CE .NET (4.x) and Windows
Embedded CE 6.0 twin pages resolved by tools/ce-twins.py:

  inventory   scan include/ for typedefs with a citing page id and
              name-only held entries; write build/sweep/inventory.json
  struct      member-list diff of every compiled struct/enum/union
              against its CE4/CE6 twin page (both generations)
  req         Requirements-row diff (OS Versions / Header / Link
              Library / DLL) CE5 vs CE4 (build/rows4.json) and CE6
              (parsed from build/pages6)
  values      mine every page tree (pages5/pages4/pages6/pagesw) for
              printed values of the held name-only entries

Reports are TSV under build/sweep/ (not committed).
"""
import html
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INC = os.path.join(ROOT, "include")
SWEEP = os.path.join(ROOT, "build", "sweep")

TREES = {
    "5": os.path.join(ROOT, "build", "pages"),
    "4": os.path.join(ROOT, "build", "pages4"),
    "6": os.path.join(ROOT, "build", "pages6"),
    "w": os.path.join(ROOT, "build", "pagesw"),
}

TYPEDEF_RE = re.compile(
    r"typedef\s+(struct|enum|union)\s*(\w+)?\s*\{(.*?)\}\s*([\w\s,.*]+?);",
    re.S)


# ---------------------------------------------------------------- pages
def page_text(tree, pid):
    f = os.path.join(TREES[tree], pid.split("(")[0] + ".html")
    if not os.path.exists(f):
        return None
    s = open(f, encoding="utf-8", errors="replace").read()
    s = re.sub(r"<script[\s\S]*?</script>", "", s)
    s = re.sub(r"<style[\s\S]*?</style>", "", s)
    s = re.sub(r"<br\s*/?>", "\n", s)
    s = re.sub(r"</(p|div|li|tr|h1|h2|h3|pre|code)>", "\n", s)
    s = re.sub(r"<[^>]+>", " ", s)
    s = html.unescape(s)
    s = re.sub(r"[ \t]+", " ", s)
    return s


def members_of(kind, body):
    if kind == "enum":
        return [m.group(1) for m in re.finditer(
            r"([A-Za-z_]\w*)\s*(?:=|,|$)", body)]
    out = []
    for b in body.split(";"):
        b = b.strip()
        if not b:
            continue
        m = re.search(r"([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*$", b)
        out.append(m.group(1) if m else b[:24])
    return out


# ------------------------------------------------------------- twins
def load_twins(tree):
    """{ce5-bare-id: twin-tagged-id} from tools/ce-twins.py output."""
    cat = {
        "6": "windows-embedded-ce-60",
        "4": "windows-ce-net",
    }[tree]
    tw = {}
    # regenerate deterministically from the committed catalogs
    sys.path.insert(0, os.path.join(ROOT, "tools"))
    import ce_twins  # noqa: F401  (not importable: name has a dash)
    return tw


def page_title(tree, pid):
    f = os.path.join(TREES[tree], pid.split("(")[0] + ".html")
    if not os.path.exists(f):
        return None
    raw = open(f, encoding="utf-8", errors="replace").read()
    m = re.search(r"<title>(.*?)(?:\s*\|\s*Microsoft Learn)?</title>",
                  raw, re.S)
    return html.unescape(m.group(1)).strip() if m else ""


def twins_map(tree):
    """{ce5_bare: twin_tagged} via the same catalog match ce-twins uses.
    The twin page's own <title> is verified against the manifest title
    when the page is local: TOC labels occasionally mislabel pages
    (e.g. catalog-windows-ce-net title 'IP_DAD_STATE' serves the
    DMTASKINFO page ms898362); such pairs are dropped."""
    cat = {"6": "windows-embedded-ce-60", "4": "windows-ce-net"}[tree]
    path = os.path.join(ROOT, "tools", "catalogs",
                        f"catalog-{cat}.tsv")
    by_title = {}
    for line in open(path, encoding="utf-8"):
        line = line.rstrip("\n")
        if not line or "\t" not in line:
            continue
        pid, title = line.split("\t", 1)
        by_title.setdefault(title.strip(), []).append(pid.strip())
    import glob
    tw = {}
    for mf in sorted(glob.glob(os.path.join(ROOT, "tools",
                                            "manifests", "*.manifest"))):
        for line in open(mf, encoding="utf-8"):
            line = line.rstrip("\n")
            if not line or "\t" not in line:
                continue
            pid, title = line.split("\t", 1)
            title = title.strip()
            if title not in by_title:
                continue
            ce5 = pid.split("(")[0]
            if ce5 in tw:
                continue
            for cand in by_title[title]:
                pt = page_title(tree, cand)
                if pt is None or norm(pt.split("(")[0]) == norm(
                        title.split("(")[0]):
                    tw[ce5] = cand
                    break
    return tw


# ---------------------------------------------------------- inventory
COMMENT_ID_RE = re.compile(r"/\*\s*((?:ms|aa|ee)\d{})".format(r"{4,}"))
ID_TOKEN = re.compile(r"\b((?:ms|aa|ee)\d{4,})\b")


def inventory():
    inv = {"typedefs": [], "held": []}
    for fn in sorted(os.listdir(INC)):
        if not fn.endswith(".h"):
            continue
        text = open(os.path.join(INC, fn), encoding="utf-8",
                    errors="replace").read()
        # held name-only ledger entries
        for m in re.finditer(
                r"/\*\s*((?:ms|aa|ee)\d{4,})\s+(\w+):\s*"
                r"documented name-only \(no value published; held\)\s*\*/",
                text):
            inv["held"].append({"header": fn, "id": m.group(1),
                                "name": m.group(2)})
        # typedefs preceded by a comment citing a page id
        for m in re.finditer(
                r"/\*(?P<c>[\s\S]*?)\*/\s*\n(?P<t>typedef\s+"
                r"(?:struct|enum|union)\b[\s\S]*?;)",
                text):
            ids = ID_TOKEN.findall(m.group("c"))
            if not ids:
                continue
            td = TYPEDEF_RE.search(m.group("t"))
            if not td:
                continue
            inv["typedefs"].append({
                "header": fn, "id": ids[0], "kind": td.group(1),
                "tag": td.group(2) or "", "alias": td.group(4).strip(),
                "members": members_of(td.group(1), td.group(3)),
                "text": re.sub(r"\s+", " ", m.group("t"))[:400],
            })
    os.makedirs(SWEEP, exist_ok=True)
    json.dump(inv, open(os.path.join(SWEEP, "inventory.json"), "w"),
              indent=1)
    print(f"[sweep] inventory: {len(inv['typedefs'])} typedefs, "
          f"{len(inv['held'])} held entries")
    return inv


# ------------------------------------------------------------- struct
def cmd_struct():
    inv = inventory()
    rows = []
    for gen in ("4", "6"):
        tw = twins_map(gen)
        for td in inv["typedefs"]:
            twin = tw.get(td["id"].split("(")[0])
            if not twin:
                continue
            txt = page_text(gen, twin)
            if not txt:
                rows.append((gen, td["header"], td["id"], twin,
                             td["alias"].split(",")[0].strip(),
                             "NO-PAGE", "", ""))
                continue
            m6 = None
            # pick the twin-page typedef that matches OUR name (the
            # page may print several; the first is not always ours)
            want = {td["alias"].split(",")[0].strip().lstrip("*"),
                    (td["tag"] or "").lstrip("_"),
                    td["alias"].split(",")[0].strip().lstrip("*").lstrip("_")}
            best = None
            for m in TYPEDEF_RE.finditer(txt):
                names = {m.group(4).split(",")[0].strip().lstrip("*"),
                         m.group(4).split(",")[0].strip().lstrip("*").lstrip("_"),
                         (m.group(2) or "").lstrip("_")}
                if names & want:
                    best = m
                    break
            m6 = best
            if not m6:
                rows.append((gen, td["header"], td["id"], twin,
                             td["alias"].split(",")[0].strip(),
                             "NO-DECL", "", ""))
                continue
            theirs = members_of(m6.group(1), m6.group(3))
            ours = td["members"]
            verdict = ("SAME" if theirs == ours else
                       "SAME-ORDER" if sorted(theirs) == sorted(ours)
                       else "DIFF")
            rows.append((gen, td["header"], td["id"], twin,
                         td["alias"].split(",")[0].strip(), verdict,
                         "|".join(ours), "|".join(theirs)))
    out = os.path.join(SWEEP, "struct-diff.tsv")
    with open(out, "w", encoding="utf-8") as fh:
        fh.write("gen\theader\tce5_id\ttwin_id\tname\tverdict\t"
                 "ours\ttheirs\n")
        for r in rows:
            fh.write("\t".join(r) + "\n")
    from collections import Counter
    print("[sweep] struct:", dict(Counter(r[5] for r in rows)),
          f"-> {out}")
    for r in rows:
        if r[5] == "DIFF":
            print("  DIFF", r[0], r[4], r[3])


# ---------------------------------------------------------------- req
def req_rows(tree, pid):
    """(os, header, lib, dll) for a twin page, parsed like ce-fetch.py
    (Requirements section on the raw HTML; the same archive layout
    serves all trees)."""
    f = os.path.join(TREES[tree], pid.split("(")[0] + ".html")
    if not os.path.exists(f):
        return None
    raw = open(f, encoding="utf-8", errors="replace").read()

    def strip_tags(seg):
        seg = re.sub(r"<[^>]+>", "", seg)
        return html.unescape(seg)

    flat = re.sub(r"\s+", " ", strip_tags(
        re.sub(r"<script[\s\S]*?</script>", " ", raw)))
    out = {"os": "", "header": "", "lib": "", "dll": ""}
    m = re.search(r'id="requirements"(.*?)'
                  r'(?:id="see-also"|id="feedback"|\Z)',
                  raw, flags=re.S | re.I)
    seg = m.group(1).replace("&nbsp;", " ") if m else ""
    if seg:
        # CE 6.0 pages print Requirements as a two-column table
        # (<tr><td>Header</td><td>winbase.h</td></tr>); the CE 5.0
        # archive uses <strong>Label:</strong> lines.  Parse both.
        for tr in re.finditer(r"<tr[^>]*>(.*?)</tr>", seg, re.S | re.I):
            tds = [re.sub(r"\s+", " ", strip_tags(t)).strip()
                   for t in re.findall(r"<td[^>]*>(.*?)</td>",
                                       tr.group(1), re.S | re.I)]
            if len(tds) < 2 or not tds[0]:
                continue
            lab = tds[0].rstrip(":")
            if lab == "Header":
                out["header"] = tds[1]
            elif lab in ("Windows Embedded CE", "OS Versions",
                         "Windows CE"):
                out["os"] = tds[1]
            elif lab in ("Link Library", "Library"):
                out["lib"] = tds[1]
            elif lab == "DLL":
                out["dll"] = tds[1].lower()
        for key, field in (("OS Versions", "os"), ("Header", "header"),
                           ("Link Library|Library", "lib")):
            if out[field]:
                continue
            fm = re.search(r"\b(?:" + key + r")" +
                           r"(?:\s*</\w+>)?\s*:\s*(.*?)" +
                           r"(?:<br\s*/?>|</p>|<h\d)",
                           seg, flags=re.S | re.I)
            if fm:
                out[field] = re.sub(
                    r"\s+", " ", strip_tags(fm.group(1))).strip()
    if not out["os"] and not out["header"]:
        # fallback: textual scan
        for key, field in (("OS Versions:", "os"), ("Header:", "header"),
                           ("Link Library:", "lib")):
            fm = re.search(re.escape(key) + r"\s*([^.]*?\.|\S[^<]{2,60})",
                           flat)
            if fm:
                out[field] = fm.group(1).strip()
    m = re.search(r"DLL:\s*([A-Za-z0-9_.]+\.dll)", flat)
    if m:
        out["dll"] = m.group(1).lower()
    return out["os"], out["header"], out["lib"], out["dll"]


def norm(s):
    return re.sub(r"[^a-z0-9]+", " ", s.lower()).strip()


def cmd_req():
    rows5 = {}
    for r in json.load(open(os.path.join(ROOT, "build", "rows.json"))):
        rows5[r["id"].split("(")[0]] = r
    rows4 = {}
    p4 = os.path.join(ROOT, "build", "rows4.json")
    if os.path.exists(p4):
        for r in json.load(open(p4)):
            rows4[r["id"].split("(")[0]] = r
    os.makedirs(SWEEP, exist_ok=True)
    out = []
    for gen in ("4", "6"):
        tw = twins_map(gen)
        for ce5, twin in tw.items():
            r5 = rows5.get(ce5)
            if not r5:
                continue
            tb = twin.split("(")[0]
            if gen == "4":
                r4 = rows4.get(tb)
                if not r4:
                    out.append((gen, r5["title"], ce5, twin, "ROW",
                                "missing", "", ""))
                    continue
                tvals = (r4.get("os", ""), r4.get("header", ""),
                         r4.get("lib", ""), r4.get("dll", ""))
            else:
                tvals = req_rows(gen, twin)
                if tvals is None:
                    out.append((gen, r5["title"], ce5, twin, "PAGE",
                                "missing", "", ""))
                    continue
            for i, f in enumerate(("os", "header", "lib", "dll")):
                a = r5.get(f, "") or ""
                b = tvals[i] or ""
                if norm(a) != norm(b) and (a or b):
                    out.append((gen, r5["title"], ce5, twin, f, a, b, ""))
    p = os.path.join(SWEEP, "req-diff.tsv")
    with open(p, "w", encoding="utf-8") as fh:
        fh.write("gen\ttitle\tce5_id\ttwin_id\tfield\tce5\ttwin\t\n")
        for r in out:
            fh.write("\t".join(r) + "\n")
    print(f"[sweep] req: {len(out)} differing rows -> {p}")
    return out


# ------------------------------------------------------------- values
VALUE_RE = re.compile(
    r"\b(0x[0-9A-Fa-f]{1,8}|\d{1,10})\b")


def mine_page(tree, pid, names):
    """[(name, value, context)] for names printed with values."""
    f = os.path.join(TREES[tree], pid.split("(")[0] + ".html")
    if not os.path.exists(f):
        return []
    raw = open(f, encoding="utf-8", errors="replace").read()
    hits = []
    # 1) #define NAME value inside <pre> blocks
    for m in re.finditer(r"#define\s+(\w+)\s+(0x[0-9A-Fa-f]+|\d+)", raw):
        if m.group(1) in names:
            hits.append((m.group(1), m.group(2), "define"))
    # 2) flattened text: NAME ... value (value within 40 chars after)
    txt = page_text(tree, pid)
    if txt:
        for nm in names:
            for m in re.finditer(
                    r"\b" + re.escape(nm) + r"\b(.{0,60})", txt, re.S):
                seg = m.group(1)
                vm = VALUE_RE.search(seg)
                if vm and vm.group(1) not in ("0", "1", "2", "32", "64"):
                    # value must sit close and look like a constant row
                    if re.match(r"\s*[:=\s]\s*", seg[:vm.start()]) or \
                       "0x" in vm.group(1):
                        hits.append((nm, vm.group(1), seg[:50].strip()))
                        break
    return hits


def cmd_values():
    inv = inventory()
    held = inv["held"]
    byid = {}
    for h in held:
        byid.setdefault(h["id"].split("(")[0], []).append(h)
    tw = {g: twins_map(g) for g in ("4", "6")}
    out = []
    for ce5, hs in byid.items():
        names = {h["name"] for h in hs}
        cands = []
        # CE5 page itself (was 'no value published' -- verify), twins,
        # and every tree's page with the same title? Only twins here;
        # the whole-corpus mine runs separately via grep.
        for gen in ("4", "6"):
            twin = tw[gen].get(ce5)
            if not twin:
                continue
            for nm, val, ctx in mine_page(gen, twin, names):
                cands.append((gen, twin, nm, val, ctx))
        for gen, twin, nm, val, ctx in cands:
            out.append((nm, next(h["header"] for h in hs
                                 if h["name"] == nm), ce5, gen, twin,
                        val, ctx.replace("\t", " ")))
    p = os.path.join(SWEEP, "value-hits.tsv")
    os.makedirs(SWEEP, exist_ok=True)
    with open(p, "w", encoding="utf-8") as fh:
        fh.write("name\theader\tce5_id\tgen\ttwin_id\tvalue\tctx\n")
        for r in out:
            fh.write("\t".join(r) + "\n")
    print(f"[sweep] values: {len(out)} twin-page hits -> {p}")


def main():
    cmd = sys.argv[1] if len(sys.argv) > 1 else "inventory"
    if cmd == "inventory":
        inventory()
    elif cmd == "struct":
        cmd_struct()
    elif cmd == "req":
        cmd_req()
    elif cmd == "values":
        cmd_values()
    else:
        sys.exit(__doc__)


if __name__ == "__main__":
    main()
