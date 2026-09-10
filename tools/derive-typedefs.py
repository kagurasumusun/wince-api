#!/usr/bin/env python3
"""derive-typedefs.py -- materialize the held callback/struct entries
whose prototypes the CE pages themselves print (M99 sweep).

For every remaining name-only held entry the tool reads the cited CE
page, extracts the printed declaration (function-pointer typedef,
bare callback prototype with glued tokens, or structure print), and
emits it as a real declaration with the page citation.  Entries whose
page prints no declaration stay held.

A KNOWN-type set (every type declared in include/ plus C/Windows
primitives) gates emission: signatures referencing unknown types are
reported for a chained pass instead of being emitted broken.
"""
import html
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INC = os.path.join(ROOT, "include")
PAGES = os.path.join(ROOT, "build", "pages")

HELD = re.compile(
    r"/\*\s*((?:ms|aa|ee)\d{4,})\s+(\w+):\s*"
    r"documented name-only \(no value published; held\)\s*\*/")

PRIMS = {
    "void", "VOID", "BOOL", "BOOLEAN", "BYTE", "CHAR", "UCHAR", "SHORT",
    "USHORT", "WORD", "int", "INT", "UINT", "long", "LONG", "ULONG",
    "DWORD", "LONGLONG", "ULONGLONG", "float", "FLOAT", "double",
    "DOUBLE", "WCHAR", "TCHAR", "HANDLE", "HWND", "HRESULT", "STATUS",
    "DWORD_PTR", "ULONG_PTR", "LONG_PTR", "UINT_PTR", "INT_PTR",
    "SIZE_T", "LPVOID", "LPCVOID", "PVOID", "PBYTE", "LPSTR", "LPCSTR",
    "LPWSTR", "LPCWSTR", "BOOL", "unsigned", "struct", "enum", "union",
    "LPDWORD", "PDWORD", "PULONG", "PUSHORT", "PUCHAR", "PCHAR", "PWSTR",
    "INT8", "UINT8", "INT16", "UINT16", "INT32", "UINT32", "INT64",
    "UINT64", "NTSTATUS", "LPCWSTR", "WPARAM", "LPARAM", "UINT8",
}

# header text cache for the exists-check of renamed prints
HEADER_TEXT = {}
_cur_header = [""]


def page_text(pid):
    f = os.path.join(PAGES, pid.split("(")[0] + ".html")
    if not os.path.exists(f):
        return None
    s = open(f, encoding="utf-8", errors="replace").read()
    s = re.sub(r"<script[\s\S]*?</script>", "", s)
    s = re.sub(r"<style[\s\S]*?</style>", "", s)
    s = re.sub(r"<br\s*/?>", "\n", s)
    s = re.sub(r"</(p|div|li|tr|h1|h2|h3|pre|code)>", "\n", s)
    s = re.sub(r"<[^>]+>", " ", s)
    s = html.unescape(s)
    return re.sub(r"[ \t]+", " ", s)


def strip_m99(text):
    """Normalize a header by removing prior M99 chained sections
    (late banner .. guard #endif, early banner .. next comment) so
    that known-type collection and re-emission both work from the
    same clean base -- the tool is idempotent."""
    text = re.sub(r"\n/\* -{20,}\n \* M99 chained structures"
                  r"[\s\S]*?(?=\n#endif)", "\n", text)
    text = re.sub(r"/\* -{20,}\n \* M99 chained types"
                  r"[\s\S]*?(?=\n/\* )", "", text)
    text = re.sub(r"/\* M99 chained definitions "
                  r"\(needed before the derived declarations\)\. "
                  r"\*/\n([\s\S]*?)(?=\n/\* )", "", text)
    text = re.sub(r"\n{3,}", "\n\n", text)   # converge blank-line drift
    return text


def load_known():
    known = set(PRIMS)
    for fn in os.listdir(INC):
        if not fn.endswith(".h"):
            continue
        t = open(os.path.join(INC, fn), encoding="utf-8",
                 errors="replace").read()
        t = strip_m99(t)
        t = re.sub(r"/\*[\s\S]*?\*/", "", t)   # comments are not decls
        t = re.sub(r"//[^\n]*", "", t)
        for m in re.finditer(
                r"^\s*(?:typedef\s+)?(?:struct|enum|union)\s+"
                r"[\w]*\s*\{[\s\S]*?\}\s*([\w\s,.*]+?);", t, re.M):
            for a in re.split(r"[,\s]+", m.group(1)):
                a = a.strip(" *")
                if a:
                    known.add(a)
        for m in re.finditer(r"typedef\s+[\w\s\*]+?\(\s*\*\s*(\w+)\s*\)",
                             t):
            known.add(m.group(1))
        for m in re.finditer(r"typedef\s+[\w]+\s+(\w+)\s*;", t):
            known.add(m.group(1))
        for m in re.finditer(r"AKARI_CE_NAME\((\w+)\)", t):
            known.add(m.group(1))
        for m in re.finditer(r"\b(?:class|struct)\s+(\w+)", t):
            known.add(m.group(1))
    return known


def split_glued(piece, known):
    if " " in piece or "*" in piece:
        return piece
    for i in range(len(piece) - 1, 1, -1):
        pre, name = piece[:i], piece[i:]
        if pre in known and name and (
                name[0].islower() or name[0] == "_" or
                (name[0].isupper() and not re.fullmatch(r"_?[A-Z0-9_]+",
                                                        name))):
            return pre + " " + name
    return piece


def find_decl(txt, name, known):
    """(kind, decl) printed on the page for `name` (or a renamed
    print of it)."""
    # explicit typedef print (glue-split the printed arguments)
    m = re.search(r"typedef\s+([\w\*\s]+?)\(\s*\*\s*" + re.escape(name) +
                  r"\s*\)\s*\(([^;]{0,300}?)\)\s*;", txt)
    if m:
        args = m.group(2).strip()
        pieces = [split_glued(p.strip(), known)
                  for p in args.split(",")] if args else []
        ret = split_glued(m.group(1).strip(), known)
        return "fnptr", (f"typedef {ret} (*{name})"
                         f"({', '.join(pieces)});")
    # bare callback print:  RET (*NAME)(args);
    m = re.search(r"([\w]+)\s*\(\s*\*\s*" + re.escape(name) +
                  r"\s*\)\s*\(([^;]{0,300}?)\)\s*;", txt)
    if m:
        args = m.group(2).strip()
        pieces = [split_glued(p.strip(), known)
                  for p in args.split(",")] if args else []
        return "fnptr", (f"typedef {m.group(1)} (*{name})"
                         f"({', '.join(pieces)});")
    # structure print: anchor on the closing `} NAME;` and take the
    # body between (nested braces -- unions, nested structs -- are
    # kept verbatim inside the window); the printed pointer aliases
    # (", *PNAME;") are carried on the closer
    m = re.search(r"typedef\s+struct\s+(\w*)\s*\{", txt)
    if m:
        start = m.start()
        close = re.search(r"\}\s*" + re.escape(name) +
                          r"\s*(?:,\s*\*?\w+\s*)?;", txt[start:])
        if close and close.start() < 2400:
            whole = txt[start:start + close.end()]
            tag = m.group(1) or name
            body = whole[whole.find("{"):whole.rfind("}") + 1]
            members = [re.sub(r"\s+", " ", mm).strip()
                       for mm in body[1:-1].split(";") if mm.strip()]
            members = [split_glued(mn, known) for mn in members]
            lines = "\n    ".join(mn + ";" for mn in members)
            closer_m = re.search(r"\}\s*([^;]+);", whole)
            closer = (closer_m.group(1).strip() if closer_m
                      else name)
            items = [c.strip() for c in closer.split(",")]
            if name not in [c.strip(" *") for c in items]:
                items.insert(0, name)
            return "struct", (f"typedef struct {tag} {{\n    "
                             f"{lines}\n}} {', '.join(items)};")
    m = re.search(r"struct\s+(_?" + re.escape(name) +
                  r")\s*\{", txt)
    if m:
        start = m.start()
        close = re.search(r"\}\s*;", txt[start:])
        if close and close.start() < 2400:
            whole = txt[start:start + close.end()]
            body = whole[whole.find("{"):whole.rfind("}") + 1]
            members = [re.sub(r"\s+", " ", mm).strip()
                       for mm in body[1:-1].split(";") if mm.strip()]
            members = [split_glued(mn, known) for mn in members]
            lines = "\n    ".join(mn + ";" for mn in members)
            return "struct", (f"typedef struct {m.group(1)} {{\n    "
                             f"{lines}\n}} {name};")
    # enum print
    m = re.search(r"typedef\s+enum\s+(\w*)\s*\{", txt)
    if m:
        start = m.start()
        close = re.search(r"\}\s*" + re.escape(name) +
                          r"\s*(?:,\s*\*?\w+\s*)?;", txt[start:])
        if close and close.start() < 2400:
            whole = txt[start:start + close.end()]
            tag = m.group(1) or name
            body = whole[whole.find("{"):whole.rfind("}") + 1]
            members = [re.sub(r"\s+", " ", mm).strip().rstrip(",")
                       for mm in body[1:-1].split(",") if mm.strip()]
            members = [mm for mm in members
                       if not mm.startswith("//") and
                       not re.fullmatch(r"/\*.*\*/", mm)]
            lines = "\n    ".join(mn + "," for mn in members)
            return "enum", (f"typedef enum {tag} {{\n    "
                            f"{lines}\n}} {name};")
    # renamed typedef print (page title vs printed symbol differ);
    # only when the header does not already declare the printed symbol
    for m in re.finditer(r"typedef\s+([\w\*]+)\s*\(\s*\*\s*(\w+)\s*\)"
                         r"\s*\(([^;]{0,300}?)\)\s*;", txt):
        hdr_text = HEADER_TEXT.get(_cur_header[0], "")
        if re.search(r"\b" + re.escape(m.group(2)) + r"\s*\)"
                     r"|\(\s*\*\s*" + re.escape(m.group(2)) + r"\s*\)",
                     hdr_text):
            continue
        args = m.group(3).strip()
        pieces = [split_glued(p.strip(), known)
                  for p in args.split(",")] if args else []
        return "renamed", (m.group(2), f"typedef {m.group(1)} "
                         f"(*{m.group(2)})({', '.join(pieces)});")
    return None, None


def decl_types(decl):
    ids = set(re.findall(r"[A-Za-z_]\w*", decl))
    return ids


def main():
    dry = "--dry" in sys.argv
    known = load_known()
    plan = []
    for fn in sorted(os.listdir(INC)):
        if not fn.endswith(".h"):
            continue
        t = open(os.path.join(INC, fn), encoding="utf-8",
                 errors="replace").read()
        for m in HELD.finditer(t):
            plan.append((fn, m.group(1), m.group(2)))
    print(f"[derive] {len(plan)} held entries")
    # cache header texts for the renamed-print exists-check
    for fn in {p[0] for p in plan}:
        HEADER_TEXT[fn] = open(os.path.join(INC, fn), encoding="utf-8",
                               errors="replace").read()
    derivable = {}
    for fn, pid, name in plan:
        _cur_header[0] = fn
        txt = page_text(pid)
        if not txt:
            continue
        kind, decl = find_decl(txt, name, known)
        if not decl:
            continue
        derivable[(fn, pid, name)] = (kind, decl, "root")
    # chained pass: unknown types referenced by derived declarations
    # that have their own page with a printed declaration (e.g. the
    # D3DM_*_DATA structures behind the D3DM_*_PTR callbacks).  Roots
    # include declarations already emitted by an earlier derive run.
    by_title = {}
    for r in json.load(open(os.path.join(ROOT, "build",
                                         "rows.json"))):
        by_title.setdefault(r["title"], r["id"])
    for fn in sorted(os.listdir(INC)):
        if not fn.endswith(".h"):
            continue
        t = strip_m99(open(os.path.join(INC, fn),
                           encoding="utf-8",
                           errors="replace").read())
        for m in re.finditer(
                r"/\* (\w+) (\w+): (?:prototype printed by the page"
                r"|the page prints the prototype under the name \w+ "
                r"\(title/print difference\)); derived at the M99 "
                r"sweep\. \*/\n([\s\S]*?)(?=\n\n|/\*|$)",
                t):
            decl = m.group(3).strip()
            if decl:
                derivable.setdefault((fn, m.group(1), m.group(2)),
                                     ("fnptr", decl, "root"))
    for _round in range(3):
        derived_names = {k[2] for k in derivable}
        new = {}
        for (fn, pid, name), (kind, val, _tg) in list(derivable.items()):
            decl = val[1] if kind == "renamed" else val
            ids = set(re.findall(r"\b([A-Za-z_]\w*)\b", decl))
            for ty in sorted(ids):
                if ty in known or ty in derived_names or \
                        ty in {k[2] for k in new}:
                    continue
                if not re.match(r"^[A-Z][A-Za-z0-9_]*$", ty):
                    continue
                base = ty.lstrip("P")
                cands = [ty, base, ty[1:] if ty.startswith("P") else ty]
                hit = next((by_title[c] for c in cands if c in by_title),
                           None)
                if not hit:
                    continue
                _cur_header[0] = fn
                txt = page_text(hit)
                if not txt:
                    continue
                for nm in (ty, base):
                    k2, d2 = find_decl(txt, nm, known)
                    if d2:
                        new[(fn, hit, nm)] = (k2, d2, ("chain", _round))
                        break
        if not new:
            break
        derivable.update(new)
        known |= {k[2] for k in new}

    # guard: drop derived declarations whose parameter/member TYPES
    # are unknown even after chaining (fixpoint: a dropped type also
    # drops its dependents).  Those entries stay held -- the M98
    # conservative policy for unpublished member types.
    known0 = set(known) - {k[2] for k in derivable
                   if isinstance(k, tuple)}
    # (chain-pass additions are validated through
    #  `alive`, not pre-known)
    KW = PRIMS | {"typedef", "struct", "enum", "union", "const",
                  "volatile", "unsigned", "signed", "static", "extern",
                  "register", "auto", "inline", "__stdcall", "__cdecl",
                  "CALLBACK", "WINAPI", "APIENTRY"}
    def _type_tokens(decl, own):
        toks = set()
        # strip struct/enum framing and the closing alias, keep only
        # identifier-shaped tokens (braces, '=', literals drop out)
        body = re.sub(r"typedef\s+(?:struct|enum)\s*\w*\s*\{", " ", decl)
        body = re.sub(r"\}\s*[\w\s,]*;?", " ", body)
        for piece in re.split(r"[;,]", body):
            piece = re.sub(r"\[[^\]]*\]", " ", piece)   # array sizes
            words = piece.replace("(", " ").replace(")", " ").split()
            words = [w.strip("*") for w in words]
            words = [w for w in words
                     if re.fullmatch(r"[A-Za-z_]\w*", w)]
            if not words:
                continue
            if len(words) >= 2:
                # "TYPE name" -- the head words are candidate types
                toks |= set(words[:-1])
                # a SCREAMING_CASE last word is a type, not a name
                # (unnamed parameter prints, e.g. "(USB_HANDLE)")
                if re.fullmatch(r"[A-Z][A-Z0-9_]+", words[-1]):
                    toks.add(words[-1])
            else:
                toks.add(words[0])   # bare member (macro member etc.)
        toks -= KW
        toks.discard(own)
        return toks

    changed = True
    while changed:
        changed = False
        alive = {v[1][0] if v[0] == "renamed" else k[2]
                 for k, v in derivable.items()}
        # pointer aliases printed on struct closers (", *PNAME;") are
        # emitted with the struct -- they count as alive too
        for k, v in list(derivable.items()):
            if v[0] == "struct":
                alive |= set(re.findall(r"\*\s*(\w+)", v[1]))
        for key in list(derivable):
            kind, val, tag = derivable[key]
            if kind == "enum":
                continue   # enumerators are self-contained
            decl = val[1] if kind == "renamed" else val
            own = val[0] if kind == "renamed" else key[2]
            bad = _type_tokens(decl, own) - known0 - alive
            if bad:
                del derivable[key]
                alive.discard(own)
                changed = True
    # report
    fnptr = {k: v for k, v in derivable.items() if v[0] == "fnptr"}
    renamed = {k: v for k, v in derivable.items() if v[0] == "renamed"}
    struct = {k: v for k, v in derivable.items() if v[0] == "struct"}
    print(f"[derive] fnptr {len(fnptr)}, renamed {len(renamed)}, "
          f"struct {len(struct)}")
    for (fn, pid, name), (kind, decl, _tg) in sorted(fnptr.items()):
        print(f"  [{fn}] {name}: {decl[:110]}")
    for (fn, pid, name), (kind, v, _tg) in sorted(renamed.items()):
        print(f"  [renamed {fn}] {name} -> {v[0]}: {v[1][:100]}")
    for (fn, pid, name), (kind, decl, _tg) in sorted(struct.items()):
        print(f"  [struct {fn}] {name}: {decl[:110]}")
    if not dry:
        # Emit.  Roots replace their held comment in place.  Chained
        # entries (types printed by their own pages, needed by roots)
        # go around them: full struct definitions are appended just
        # before the include guard's #endif; forward typedefs for
        # them are inserted just before the first root, so the
        # scattered root declarations compile.  Chained enums and
        # chained fnptrs that do not reference roots go early too.
        for fn in sorted({k[0] for k in derivable}):
            path = os.path.join(INC, fn)
            t = open(path, encoding="utf-8", errors="replace").read()
            # idempotency: same normalized base as load_known
            t = strip_m99(t)
            roots = []
            chained = []
            for (f2, pid, name), (kind, val, tag) in sorted(
                    derivable.items(), key=lambda kv: -len(kv[0][2])):
                if f2 != fn:
                    continue
                if tag == "root":
                    roots.append(((f2, pid, name), kind, val))
                else:
                    chained.append(((f2, pid, name), kind, val, tag))
            # de-duplicate roots that declare the same symbol (e.g.
            # the D3DM_Xxx page and the D3DM_X_PTR page both print
            # the same D3DM_X_PTR prototype)
            root_syms = set()
            deduped = []
            for (f2, pid, name), kind, val in roots:
                sym = val[0] if kind == "renamed" else name
                if sym in root_syms:
                    deduped.append(((f2, pid, name), "xref", sym))
                    continue
                root_syms.add(sym)
                deduped.append(((f2, pid, name), kind, val))
            roots = deduped
            root_names = {k[2] for k, *_ in roots}
            # roots: replace held comments in place, except roots
            # that reference root symbols emitted LATER in the file --
            # those defer to the M99 section before #endif so every
            # referenced symbol is already declared
            sym_of = {}
            for (f2, pid, name), kind, val in roots:
                sym_of[(f2, pid, name)] = (val[0] if kind ==
                                           "renamed" else name)
            deferred = []
            placed = set()
            # pass 1: in-place roots (no refs, or refs not roots)
            for (f2, pid, name), kind, val in roots:
                if kind == "xref":
                    # cross-reference notes never defer -- they are
                    # comments, not declarations
                    pat = re.compile(
                        r"/\*\s*" + re.escape(pid) + r"\s+" +
                        re.escape(name) + r":\s*"
                        r"documented name-only \(no value published; "
                        r"held\)\s*\*/")
                    note = (f"/* {pid} {name}: this page prints the "
                            f"same {val} prototype (the declaration is "
                            f"carried at its own page record; M99 "
                            f"sweep). */")
                    t = pat.sub(lambda m: note + "\n", t, count=1)
                    continue
                decl = val[1] if kind == "renamed" else val
                refs = {sym_of[k] for k, _k2, _v in roots
                        if sym_of[k] in
                        set(re.findall(r"\b\w+\b", decl)) and
                        sym_of[k] != sym_of[(f2, pid, name)]}
                if refs:
                    deferred.append(((f2, pid, name), kind, val, refs))
                    continue
                pat = re.compile(
                    r"/\*\s*" + re.escape(pid) + r"\s+" +
                    re.escape(name) + r":\s*"
                    r"documented name-only \(no value published; "
                    r"held\)\s*\*/")
                if kind == "renamed":
                    printed, decl2 = val
                    note = (f"/* {pid} {name}: the page prints the "
                            f"prototype under the name {printed} "
                            f"(title/print difference); derived at the "
                            f"M99 sweep. */\n{decl2}")
                elif kind == "xref":
                    note = (f"/* {pid} {name}: this page prints the "
                            f"same {val} prototype (the declaration is "
                            f"carried at its own page record; M99 "
                            f"sweep). */")
                else:
                    note = (f"/* {pid} {name}: prototype printed by "
                            f"the page; derived at the M99 sweep. */\n"
                            f"{val}")
                t = pat.sub(lambda m: note + "\n", t, count=1)
                placed.add(sym_of[(f2, pid, name)])
            t = re.sub(r"\);/\*", ");\n/*", t)
            # pass 2: deferred roots, ordered until refs are satisfied
            defroot = []
            if chained:
                fwd = []
                early = []
                late = []
                seen = set()
                for (f2, pid, name), kind, val, tag in sorted(
                        chained, key=lambda kv: (
                            kv[3][1] if isinstance(kv[3], tuple) else 9,
                            kv[0][2])):
                    if name in seen:
                        continue
                    seen.add(name)
                    if kind == "struct":
                        mtag = re.search(r"typedef struct (\w+)", val)
                        tagname = mtag.group(1) if mtag else name
                        fwd.append(
                            f"typedef struct {tagname} {name};   "
                            f"/* forward (full definition below) */")
                        late.append((pid, name, val, tagname))
                    elif kind == "renamed":
                        printed, decl = val
                        tgt = (late if set(re.findall(r"\w+", decl)) &
                               root_names else early)
                        tgt.append((pid, name,
                                    f"/* {pid} {name}: the page prints "
                                    f"the prototype under the name "
                                    f"{printed} (title/print "
                                    f"difference); derived at the M99 "
                                    f"sweep. */\n{decl}"))
                    elif kind == "enum":
                        early.append(
                            (pid, name,
                             f"/* {pid} {name}: enum print on the "
                             f"page; derived at the M99 sweep. */\n"
                             f"{val}"))
                    else:  # chained fnptr
                        tgt = (late if set(re.findall(r"\w+", val)) &
                               root_names else early)
                        tgt.append((pid, name,
                                    f"/* {pid} {name}: prototype "
                                    f"printed by the page; derived at "
                                    f"the M99 sweep (chained). */\n"
                                    f"{val}"))
                # late: full struct definitions before the final
                # #endif (the include guard); the earlier forward
                # typedefs complete here
                # deferred roots first (they only reference
                # already-placed symbols once ordered here)
                while deferred:
                    progressed = False
                    rest = []
                    for item in deferred:
                        (f2, pid, name), kind, val, refs = item
                        if refs <= placed:
                            if kind == "renamed":
                                printed, decl2 = val
                                defroot.append(
                                    f"/* {pid} {name}: the page prints "
                                    f"the prototype under the name "
                                    f"{printed} (title/print "
                                    f"difference); derived at the M99 "
                                    f"sweep (deferred: references "
                                    f"symbols declared above). */\n"
                                    f"{decl2}")
                            else:
                                defroot.append(
                                    f"/* {pid} {name}: prototype "
                                    f"printed by the page; derived at "
                                    f"the M99 sweep (deferred: "
                                    f"references symbols declared "
                                    f"above). */\n{val}")
                            # note in place of the held comment
                            pat = re.compile(
                                r"/\*\s*" + re.escape(pid) + r"\s+" +
                                re.escape(name) + r":\s*"
                                r"documented name-only \(no value "
                                r"published; held\)\s*\*/")
                            t = pat.sub(lambda m: (
                                f"/* {pid} {name}: derived at the M99 "
                                f"sweep; the declaration sits in the "
                                f"M99 section at the end of this file "
                                f"(it references symbols declared "
                                f"below its record). */\n"), t, count=1)
                            placed.add(name if kind != "renamed"
                                       else val[0])
                            progressed = True
                        else:
                            rest.append(item)
                    deferred = rest
                    if not progressed:
                        break   # cycle: keep those held
                if late or defroot:
                    block = ("\n/* ------------------------------------------------"
                             "------------------\n"
                             " * M99 chained structures -- full page "
                             "prints (completing the forward\n"
                             " * declarations above; source: the cited "
                             "CE reference pages).\n"
                             " * ----------------------------------------"
                             "-------------------------- */\n")
                    for d in defroot:
                        block += d + "\n\n"
                    for pid, name, val, tagname in late:
                        body = val[val.find("{"):val.rfind("}") + 1]
                        block += (f"/* {pid} {name}: structure print "
                                  f"on the page; derived at the M99 "
                                  f"sweep (forward-declared above). */\n"
                                  f"struct {tagname}{body};\n")
                        for alias in re.findall(r"\*\s*(\w+)", val):
                            block += (f"typedef {name} *{alias};"
                                      f"   /* printed alias */\n")
                        block += "\n"
                    i = t.rfind("#endif")
                    t = t[:i] + block + t[i:]
                # early: forward typedefs + early definitions just
                # before the first root emission line
                early_block = ""
                if fwd:
                    early_block += ("/* ------------------------------------------------"
                                    "------------------\n"
                                    " * M99 chained types -- forward "
                                    "declarations (the full page-print\n"
                                    " * definitions sit at the end of "
                                    "this header; the pages are the\n"
                                    " * cited CE reference pages).\n"
                                    " * ----------------------------------------"
                                    "-------------------------- */\n" +
                                    "\n".join(fwd) + "\n\n")
                if early:
                    early_block += ("/* M99 chained definitions "
                                    "(needed before the derived "
                                    "declarations). */\n")
                    for pid, name, decl in early:
                        early_block += decl + "\n\n"
                if early_block:
                    i = t.find("derived at the M99 sweep")
                    assert i >= 0, fn
                    line_start = t.rfind("\n", 0, i) + 1
                    t = t[:line_start] + early_block + t[line_start:]
            t = t.replace(";#endif", ";\n\n#endif")
            open(path, "w", encoding="utf-8").write(t)
        print("[derive] emitted")
    return 0


if __name__ == "__main__":
    sys.exit(main())
