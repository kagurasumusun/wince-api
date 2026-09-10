#!/usr/bin/env python3
"""Surface-completion metrics for the Akari WinCE API headers.

Reads build/rows.json (harvested official CE documentation rows) and
the include/ headers, and prints the surface-completion measures that
docs/coverage.md records:

  fn rows        rows whose sig parses as `ret title(...)`  -> function pages
  fn declared    of those, names declared via AKARI_CE_NAME(...)
  symbol rows    rows with a title that names a symbol (fn, type,
                 constant, message) -- fn rows plus non-fn sig rows
  symbols shipped of those, names appearing verbatim in include/*.h
                 (as any token: decl, typedef, enum member, #define)
  header tokens  distinct Header-row tokens across all rows
  headers shipped of those tokens, files present in include/

Usage: python3 tools/surface-metrics.py
"""
import json, re, glob, os, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

def main():
    rows = json.load(open(os.path.join(ROOT, 'build/rows.json')))
    declared = set()
    for f in glob.glob(os.path.join(ROOT, 'include/*.h')):
        for m in re.finditer(r'AKARI_CE_NAME\(\s*([A-Za-z_][A-Za-z0-9_]*)\s*\)',
                             open(f, errors='ignore').read()):
            declared.add(m.group(1))
    # every identifier that appears anywhere in the shipped headers
    hdr_tokens = set()
    for f in glob.glob(os.path.join(ROOT, 'include/*.h')):
        for m in re.finditer(r'\b([A-Za-z_][A-Za-z0-9_]*)\b',
                             open(f, errors='ignore').read()):
            hdr_tokens.add(m.group(1))

    fn_rows = 0; fn_decl = 0; sym_rows = 0; sym_ship = 0
    for r in rows:
        t = (r.get('title') or '').strip()
        s = (r.get('sig') or '').strip()
        if not t:
            continue
        is_fn = False
        if s:
            m = re.match(r'^[A-Za-z_][A-Za-z0-9_ \*]*?([A-Za-z_][A-Za-z0-9_]*)\s*\(', s)
            is_fn = bool(m and m.group(1) == t)
        if is_fn:
            fn_rows += 1
            if t in declared:
                fn_decl += 1
        elif s or re.fullmatch(r'[A-Z][A-Za-z0-9_]*', t):
            # a printed signature that is not a function (type) or an
            # ALL-Caps constant/message/enum row
            sym_rows += 1
            if t in hdr_tokens:
                sym_ship += 1

    htoks = set()
    for r in rows:
        h = (r.get('header') or '').strip().rstrip('.')
        if re.fullmatch(r'[A-Za-z0-9_]+\.h', h):
            htoks.add(h.lower())
    shipped = {os.path.basename(f).lower()
               for f in glob.glob(os.path.join(ROOT, 'include/*.h'))}

    print(f"rows total           {len(rows)}")
    print(f"fn rows              {fn_rows}")
    print(f"fn declared          {fn_decl} ({100*fn_decl/max(fn_rows,1):.0f}%)")
    print(f"other symbol rows    {sym_rows}")
    print(f"symbols shipped      {sym_ship} ({100*sym_ship/max(sym_rows,1):.0f}%)")
    print(f"header tokens        {len(htoks)}")
    print(f"headers shipped      {len(shipped & htoks)}/{len(htoks)}")
    unsh = sorted(htoks - shipped)
    print(f"unshipped tokens     {len(unsh)}: {' '.join(unsh)}")

if __name__ == '__main__':
    sys.exit(main())
