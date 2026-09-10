#!/usr/bin/env python3
"""gen-book.py -- generate headers of record for a harvested book.

Driven by build/rows.json (the harvest record set) plus the locally
preserved official pages (build/pages).  Rows are grouped by their
documented Header row; every group lands in include/<Header>.h
(merged into the existing file when one is already carried -- only
names not yet present anywhere are emitted).  For each row whose
documented name is not yet carried:

  * function rows with a parsed signature -- a verbatim record comment
    (page id + printed signature) plus, when every type is resolvable,
    a compiled prototype (AKARI_CE_IMPORT when the page prints a
    Link Library *.lib token; plain prototype otherwise -- DDI/
    provider-side).  Pointer-only references to unpublished types get
    opaque carriers (the M44 pattern); by-value unknowns stay
    record-only.
  * type rows (structures / enumerations) -- the page's own printed
    declaration, compiled when every member type is resolvable, held
    (comment-only) otherwise.
  * method / property / constant rows -- verbatim records (M44/M58).

Usage:
    python3 tools/gen-book.py <manifest> [<manifest> ...]
"""

import importlib.util
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
_TOOLS = os.path.join(ROOT, 'tools')

_spec = importlib.util.spec_from_file_location('av', os.path.join(_TOOLS, 'adopt-vtables.py'))
av = importlib.util.module_from_spec(_spec)
av.__name__ = 'av'
_spec.loader.exec_module(av)
split_params = av.split_params

_spec2 = importlib.util.spec_from_file_location('rt', os.path.join(_TOOLS, 'rtctext.py'))
rt = importlib.util.module_from_spec(_spec2)
rt.__name__ = 'rt'
_spec2.loader.exec_module(rt)

PRIMS = {
    'void', 'int', 'unsigned', 'long', 'short', 'char', 'float', 'double',
    'BOOL', 'VOID', 'CHAR', 'WCHAR', 'BYTE', 'WORD', 'DWORD', 'LONG',
    'ULONG', 'USHORT', 'UCHAR', 'INT', 'UINT', 'LONGLONG', 'ULONGLONG',
    'HANDLE', 'HWND', 'HDC', 'HINSTANCE', 'HKEY', 'HFONT', 'HMENU',
    'LPCSTR', 'LPSTR', 'LPCWSTR', 'LPWSTR', 'LPCTSTR', 'LPTSTR',
    'LPVOID', 'LPCVOID', 'PVOID', 'PCVOID', 'SIZE_T', 'DWORD_PTR',
    'ULONG_PTR', 'LONG_PTR', 'INT_PTR', 'UINT_PTR', 'LRESULT', 'WPARAM',
    'LPARAM', 'HRESULT', 'BOOLEAN', 'GUID', 'RECT', 'POINT', 'SIZE',
    'FILETIME', 'SYSTEMTIME', 'SOCKET', 'time_t', 'va_list', 'NTSTATUS',
    'PWSTR', 'PCWSTR', 'PWCHAR', 'PCHAR', 'LPBYTE', 'PBYTE', 'LPDWORD',
    'PDWORD', 'LPBOOL', 'PBOOL', 'LPWORD', 'PWORD', 'PLONG', 'PULONG',
    'PUINT', 'LPLONG', 'TCHAR', 'OLECHAR', 'BSTR', 'VARIANT', 'DATE',
    'REFGUID', 'REFCLSID', 'REFIID', 'SCODE', 'LPFN', 'FARPROC',
    'HGLOBAL', 'HLOCAL', 'HMODULE', 'HRGN', 'HBRUSH', 'HPEN', 'HBITMAP',
    'HACCEL', 'HICON', 'HCURSOR', 'HDROP', 'HDWP', 'HWINSTA', 'HDESK',
    'LPCCH', 'LPCH', 'LPCWCH', 'LPWCH', 'PCCH', 'PWCH', 'PZH',
}

MISPRINT = {
    'LPCSTSTR': 'LPCTSTR',
    'WINAPIVC': 'WINAPIV',
    'WINDWORD': 'DWORD',
    '_MAX_PATH': 'MAX_PATH',      # page print carries the underscore
    '_MAX_FNAME': 'MAX_FNAME',    # spellings; the tree declares the
    '_MAX_EXT': 'MAX_EXT',        # classic names (stdlib spelling)
    '_MAX_DRIVE': 'MAX_DRIVE',
}

KNOWN = set()      # mentioned anywhere (glue splitting)
DECLARED = set()   # actually declared (prototype validity)


def scan_declared(txt):
    txt = re.sub(r'/\*.*?\*/', ' ', txt, flags=re.S)
    txt = re.sub(r'//[^\n]*', ' ', txt)
    for m in re.finditer(r'typedef[^;]{0,500}?\b([A-Za-z_]\w*)\s*;', txt):
        DECLARED.add(m.group(1))
    for m in re.finditer(r'\}\s*([\w\s,.*]+?);', txt):
        for a in m.group(1).split(','):
            DECLARED.add(a.strip().lstrip('*').strip())
    for m in re.finditer(r'#define\s+([A-Za-z_]\w*)', txt):
        DECLARED.add(m.group(1))
    for m in re.finditer(r'\b(?:struct|enum|union)\s+([A-Za-z_]\w*)\s*\{', txt):
        DECLARED.add(m.group(1))
    for m in re.finditer(r'\b([A-Za-z_]\w*)\s*\(', txt):
        pass  # function names -- not types


def load_registry():
    for fn in sorted(os.listdir(os.path.join(ROOT, 'include'))):
        if fn.endswith('.h'):
            txt = open(os.path.join(ROOT, 'include', fn),
                       encoding='utf-8', errors='replace').read()
            KNOWN.update(re.findall(r'\b([A-Za-z_]\w*)\b', txt))
            scan_declared(txt)
    DECLARED.update(PRIMS)
    KNOWN.update(PRIMS)


def page_text(pid):
    try:
        return rt.page_text(pid.split('(')[0])
    except Exception:
        return ''


def norm_type(t):
    t = t.strip()
    t = t.replace('SEC_FAR', '').replace('_RPC_FAR', '')
    t = re.sub(r'\s+', ' ', t)
    b = base_of(t)
    if b in MISPRINT:
        t = t.replace(b, MISPRINT[b])
    for k, v in getattr(av, 'EXACT_TYPE_MAP', {}).items():
        if b == k:
            t = t.replace(b, v)
            break
    return t


def base_of(t):
    t = norm_type0(t)
    t = re.sub(r'^(const\s+|struct\s+)+', '', t)
    t = t.split('*')[0].strip()
    return t


def norm_type0(t):
    t = t.strip().replace('SEC_FAR', '').replace('_RPC_FAR', '')
    return re.sub(r'\s+', ' ', t)


def is_ptr(t):
    return '*' in norm_type0(t)


def known_type(t):
    b = base_of(t)
    return bool(b) and (b in PRIMS or b in DECLARED)


def split_glued(piece):
    """'LPWSTRlpszPassword' / 'PSMARTCARD_EXTENSIONSmartcardExtension'
    -> (type, name): try every split point, longest known-type prefix
    with a lowercase/underscore-headed remainder wins."""
    piece = piece.strip()
    best = None
    if ' ' in piece or '*' in piece:
        return None            # spaced/starred pieces are not glued
    for i in range(len(piece) - 1, 0, -1):
        pre, name = piece[:i], piece[i:]
        p = pre.rstrip('*')
        if (p in KNOWN or p in PRIMS) and name and \
                (name[0].islower() or name[0] == '_') and \
                re.search(r'[a-z]', name) and not \
                re.match(r'^_?[A-Z0-9_]+$', name):
            best = (pre, name)
            break
    return best


def parse_piece(piece):
    piece = re.sub(r'\[.*?\]', '', piece).strip()
    piece = piece.replace('OPTIONAL', '').strip()
    # SAL-style annotation tokens the DDI pages print inline
    piece = re.sub(r'\b(IN|OUT|IN_OUT|__in|__out|__inout|__in_opt|__out_opt)\b',
                   ' ', piece).strip()
    if not piece:
        return None
    if re.match(r'^(void|VOID)$', piece):
        return ('void', '')
    sp = split_glued(piece)
    if sp:
        return sp
    m = re.match(r'^(.*?[\s*])\**\s*([A-Za-z_]\w*)$', piece)
    if m:
        t = m.group(1).strip()
        return t, m.group(2)
    if known_type(piece):
        return piece, ''
    return None


def parse_sig(sig):
    sig = re.sub(r'\s+', ' ', sig.strip())
    sig = sig.rstrip(';').strip()
    lp = sig.find('(')
    if lp == -1:
        return None
    rp = sig.rfind(')')
    if rp == -1 or rp < lp:
        return None
    head = sig[:lp].strip()
    params_txt = sig[lp + 1:rp]
    m = re.match(r'^(.*?)([A-Za-z_]\w*)$', head)
    if not m:
        return None
    rest, name = m.group(1).strip(), m.group(2)
    conv = ''
    ret = rest
    for c in ('WINAPI', 'CALLBACK', '__cdecl', 'SEC_ENTRY', 'WINAPIV'):
        if ret == c:
            ret = ''
            conv = c
            break
        if ret.endswith(' ' + c):
            ret = ret[:-len(c) - 1].strip()
            conv = c
            break
    if not ret:
        for p in sorted(PRIMS, key=len, reverse=True):
            if name.startswith(p) and len(name) > len(p):
                ret = p
                name = name[len(p):]
                break
        if not ret:
            ret = 'void'
    params = []
    if params_txt.strip():
        for piece in params_txt.split(','):
            piece = piece.strip()
            if not piece:
                continue
            if '//' in piece:
                piece = piece.split('//')[0].strip()
            if not piece:
                continue
            pp = parse_piece(piece)
            if pp is None:
                return None
            params.append(pp)
    return ret, conv, name, params


TYPEDEF_RE = re.compile(
    r'typedef\s+(struct|enum|union)\s*(\w+)?\s*\{(.*?)\}\s*([\w\s,.*]+?);',
    re.S)


def extract_sig_from_page(pid, name):
    """for function rows whose signature the row parser missed: pull
    the page's own Syntax print (flattened)."""
    t = page_text(pid)
    if not t:
        return None
    t = re.sub(r'\s+', ' ', t)
    m = re.search(
        r'((?:[A-Za-z_][\w]*\s+){0,3}[A-Za-z_][\w\s\*]{0,40}?)\b'
        + re.escape(name) + r'\s*\((.*?)\)\s*;', t)
    if not m:
        # glued return+name print (BOOLCeCheckPassword(...))
        mg = re.search(r'\b([A-Za-z_]\w*)' + re.escape(name)
                       + r'\s*\((.*?)\)\s*;', t)
        if mg and (mg.group(1) in PRIMS or mg.group(1) in KNOWN):
            return f'{mg.group(1)} {name}({mg.group(2).strip()});'
        return None
    ret = m.group(1).strip()
    if not ret or not re.match(r'^[A-Za-z_]', ret):
        return None
    # trim leading prose words: keep the last type-ish token run
    toks = ret.split(' ')
    while len(toks) > 1 and toks[0].lower() in (
            'syntax', 'this', 'the', 'a', 'an', 'in', 'function',
            'returns', 'return', 'values', 'value', 'and', 'of'):
        toks = toks[1:]
    ret = ' '.join(toks)
    if not re.match(r'^[A-Za-z_][\w]*(\s+[A-Za-z_][\w]*){0,2}$', ret):
        return None
    return f'{ret} {name}({m.group(2).strip()});'


def extract_type_decl(pid):
    t = page_text(pid)
    if not t:
        return None
    t = re.sub(r'\s+', ' ', t)
    m = TYPEDEF_RE.search(t)
    if not m:
        return None
    return m.group(1), m.group(2), m.group(3), \
        [a.strip() for a in m.group(4).split(',')]


def member_type_known(mt):
    mt = mt.strip()
    if not mt:
        return False
    # array dimensions must be declared constants or literals
    for dim in re.findall(r'\[([^\]]*)\]', mt):
        dim = dim.strip()
        if dim and not dim.isdigit():
            if not all(t in DECLARED or t in PRIMS
                       for t in dim.replace('*', ' ').split()):
                return False
    mt = re.sub(r'\[.*?\]', '', mt)
    mt = mt.split(':')[0].strip()
    m = re.match(r'^(.*?)([A-Za-z_]\w*)$', mt)
    if not m:
        return known_type(mt)
    return known_type(m.group(1)) or known_type(mt)


ENUM_BODY_RE = re.compile(r'^\s*([A-Za-z_]\w*)\s*(=\s*([^,]+))?\s*$')


def compile_type(decl):
    kind, tag, body, aliases = decl
    if kind == 'enum':
        members = [b.strip() for b in body.split(',') if b.strip()]
        # flattened tables glue members ('A = 0 B = 1'): re-split on
        # NAME(= value) boundaries -- a mechanical re-split of the
        # page's own printed member/value pairs
        fixed = []
        for mem in members:
            if mem.count('=') > 1 or re.search(r'\w\s+\w+=', mem):
                fixed.extend(x.strip() for x in
                             re.findall(r'[A-Za-z_]\w*\s*=\s*-?[A-Za-z0-9_]+'
                                        r'(?=\s|$)|[A-Za-z_]\w*', mem)
                             if x.strip())
            else:
                fixed.append(mem)
        members = fixed
    else:
        members = [b.strip() for b in body.split(';') if b.strip()]
    if kind == 'enum':
        lines = []
        for mem in members:
            m2 = ENUM_BODY_RE.match(mem)
            if not m2:
                return None
            lines.append('    ' + m2.group(1) +
                         (f' = {m2.group(3)}' if m2.group(3) else '') + ',')
        if lines:
            lines[-1] = lines[-1].rstrip(',')
    else:
        lines = []
        for mem in members:
            mem = re.sub(r'\s+', ' ', mem)
            for k, v in MISPRINT.items():
                if k in mem:
                    mem = mem.replace(k, v)
            if not member_type_known(mem):
                return None
            lines.append('    ' + mem + ';')
    return 'typedef ' + kind + ' ' + (tag or '') + ' {\n' + \
        '\n'.join(lines) + '\n} ' + ', '.join(aliases) + ';'


def canonical_hdr(doc_hdr):
    """documented Header spelling -> our file name"""
    h = doc_hdr.strip().rstrip('.').strip()
    h = h.split(',')[0].split(' and ')[0].split(' or ')[0].strip()
    if not h:
        return None
    if re.search(r'\.(cpp|c|idl|def)$', h):
        return None                      # sample-source reference
    if not h.endswith('.h'):
        if h.lower() in ('usbdi', 'developer defined', 'developer implemented'):
            h = h + '.h' if h.lower() == 'usbdi' else None
            if h is None:
                return None
        else:
            h = h + '.h'
    # case-variant existing file wins
    d = os.path.join(ROOT, 'include')
    for fn in os.listdir(d):
        if fn.lower() == h.lower():
            return fn
    return h[0].upper() + h[1:]


GUARD_CLOSE_RE = re.compile(
    r'\n#ifdef __cplusplus\n\}\n#endif\n(\n#endif[^\n]*\n?)$', re.S)


def merge_into(path, section):
    """append a section to an existing header (before the guard close)"""
    txt = open(path, encoding='utf-8').read()
    m = GUARD_CLOSE_RE.search(txt)
    if m:
        txt = txt[:m.start()] + '\n' + section + '\n' + txt[m.start():]
    else:
        i = txt.rfind('#endif')
        txt = txt[:i] + section + '\n' + txt[i:]
    open(path, 'w', encoding='utf-8').write(txt)


def raw_all():
    raw = ''
    for fn in sorted(os.listdir(os.path.join(ROOT, 'include'))):
        if fn.endswith('.h'):
            raw += open(os.path.join(ROOT, 'include', fn),
                        encoding='utf-8', errors='replace').read()
    return raw


def main():
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    manifests = sys.argv[1:]
    load_registry()
    rows = json.load(open(os.path.join(ROOT, 'build', 'rows.json')))
    book = {}
    for m in manifests:
        mf = os.path.join(ROOT, 'tools', 'manifests', m + '.manifest')
        for l in open(mf):
            l = l.strip()
            if l:
                book[l.split('\t')[0].split('(')[0]] = m
    rows = [r for r in rows if r['id'].split('(')[0] in book]
    raw = raw_all()

    def carried(name):
        return bool(name) and re.search(
            r'\b' + re.escape(name) + r'\b', raw)

    # group by documented header
    groups = {}
    primary = {}
    for r in rows:
        dh = (r.get('header') or '').strip()
        key = canonical_hdr(dh) if dh else None
        if key is None:
            key = '__records__'
        groups.setdefault(key, []).append(r)
    # primary header for a manifest = the most frequent real header
    for m in manifests:
        cnt = {}
        for r in rows:
            if book[r['id'].split('(')[0]] != m:
                continue
            dh = (r.get('header') or '').strip()
            k = canonical_hdr(dh) if dh else None
            if k and k != '__records__':
                cnt[k] = cnt.get(k, 0) + 1
        if cnt:
            primary[m] = max(cnt, key=cnt.get)

    for key in sorted(groups):
        rs = groups[key]
        if key == '__records__':
            for m in manifests:
                sub = [r for r in rs if book[r['id'].split('(')[0]] == m]
                if not sub:
                    continue
                target = primary.get(m)
                if not target:
                    print(f'[{m}] {len(sub)} orphan rows: no primary header; skipped')
                    continue
                emit_group(target, sub, m, raw, merge=True)
            continue
        emit_group(key, rs, ','.join(sorted({book[r['id'].split('(')[0]] for r in rs})), raw)


def emit_group(target, rs, bookname, raw, merge=False):
    path = os.path.join(ROOT, 'include', target)
    exists = os.path.exists(path)
    if exists:
        # merge: only names not carried anywhere (incl. this file)
        pass

    def carried(name):
        return bool(name) and re.search(r'\b' + re.escape(name) + r'\b', raw)

    funcs, types, records = [], [], []
    for r in sorted(rs, key=lambda x: (x['title'].lower(), x['id'])):
        title = r['title'].strip()
        name = re.sub(r'\s*\(Windows CE[^)]*\)\s*$', '', title)
        name = re.sub(r'\s*\([^)]*\)\s*$', '', name).strip()
        if '::' in name or re.search(r'\s(Method|Property)$', name, re.I):
            records.append(r)
            continue
        if r.get('sig'):
            funcs.append(r)
        elif (r.get('header') and re.match(r'^[A-Za-z_][A-Za-z0-9_]*$', name)
                  and len(name) > 2
                  and extract_sig_from_page(r['id'], name)):
            funcs.append(r)          # page prints a function syntax
        elif r.get('header') and re.match(r'^[A-Z][A-Za-z0-9_]*$', name) and len(name) > 2:
            types.append(r)
        else:
            records.append(r)

    need_carriers = set()
    parsed_funcs = []
    for r in funcs:
        name = re.sub(r'\s*\(Windows CE[^)]*\)\s*$', '', r['title']).strip()
        name = re.sub(r'\s*\([^)]*\)\s*$', '', name).strip()
        if carried(name):
            continue
        sig = r.get('sig') or ''
        if not sig:
            alt = extract_sig_from_page(r['id'], name)
            if alt:
                sig = alt
        if sig.startswith('#define') or sig.startswith('typedef'):
            parsed_funcs.append((r, None))
            continue
        p = parse_sig(sig)
        parsed_funcs.append((r, p))
        if p:
            ret, conv, name2, params = p
            for t, n in params:
                b = base_of(t)
                if b and b not in PRIMS and not known_type(t) and is_ptr(t):
                    need_carriers.add(b)

    compiled, held, opaques = [], [], []
    for r in types:
        name = re.sub(r'\s*\(Windows CE[^)]*\)\s*$', '', r['title']).strip()
        name = re.sub(r'\s*\([^)]*\)\s*$', '', name).strip()
        if carried(name):
            continue
        decl = extract_type_decl(r['id'])
        if decl:
            c = compile_type(decl)
            if c:
                compiled.append((r, c))
                for a in decl[3]:
                    DECLARED.add(a.split('*')[0].strip())
            else:
                held.append((r, decl))
        else:
            opaques.append(r)   # record-only; carriers come from need_carriers

    # compiled typedefs supersede opaque carriers of the same name
    comp_names = set()
    for r, c in compiled:
        for a in re.findall(r'\}\s*([\w\s,.*]+?);', c):
            for x in a.split(','):
                comp_names.add(x.strip().lstrip('*').strip())
    need_carriers = {c for c in need_carriers if c not in comp_names}

    emit = []
    if compiled or held or opaques or parsed_funcs or records:
        emit.append('/* ------------------------------------------------------------------')
        emit.append(f' * Book surface: {bookname} (tools/gen-book.py; page ids per record)')
        emit.append(' * ------------------------------------------------------------------ */')
    for c in sorted(need_carriers):
        emit.append(f'typedef struct {c} {c};   /* opaque carrier (layout unpublished) */')
        DECLARED.add(c)
    for r, c in compiled:
        emit.append(f'/* {r["id"].split("(")[0]} {r["title"].strip()} (page print, compiled) */')
        emit.append(c)
    for r, decl in held:
        kind, tag, body, aliases = decl
        emit.append(f'/* {r["id"].split("(")[0]} {r["title"].strip()} -- HELD (page print;'
                    f' member types unpublished):')
        emit.append(f' *   typedef {kind} {tag or ""} {{ ... }} {", ".join(aliases)}; */')
    for r in opaques:
        name = re.sub(r'\s*\(Windows CE[^)]*\)\s*$', '', r['title']).strip()
        name = re.sub(r'\s*\([^)]*\)\s*$', '', name).strip()
        if not carried(name) and name in need_carriers:
            emit.append(f'typedef struct {name} {name};   /* referenced; no page prints a layout */')
            DECLARED.add(name)
    for r, p in parsed_funcs:
        pid = r['id'].split('(')[0]
        sig = ' '.join((r.get('sig') or '').split())
        if p is None:
            emit.append(f'/* {pid} {r["title"].strip()}: print `{sig}`'
                        f' -- recorded verbatim (no compiled prototype) */')
            continue
        ret, conv, name, params = p
        eff = sig
        emit.append(f'/* {pid} {r["title"].strip()}: print `{eff}` */')
        ok = known_type(ret) or (is_ptr(ret) and known_type(base_of(ret)))
        if is_ptr(ret) and base_of(ret) in need_carriers:
            ok = True
        plist = []
        for t, n in params:
            if not known_type(t):
                if is_ptr(t) and base_of(t) in need_carriers:
                    pass
                else:
                    ok = False
                    break
            plist.append(norm_type(t) + (f' {n}' if n else ''))
        if not ok:
            emit.append('/* (record-only: parameter or return type unpublished) */')
            continue
        lib = r.get('lib') or ''
        toks = re.findall(r'[\w.-]+\.lib', lib)
        body = ', '.join(plist) if plist else 'void'
        cname = conv + ' ' if conv else ''
        if toks:
            emit.append(f'AKARI_CE_IMPORT {ret} {cname}{name}({body})')
            emit.append(f'    AKARI_CE_NAME({name});')
        else:
            emit.append(f'{ret} {cname}{name}({body});')
    for r in records:
        pid = r['id'].split('(')[0]
        extra = f' (Header: {r["header"].strip()})' if r.get('header') else ''
        emit.append(f'/* {pid} {r["title"].strip()}{extra} */')

    if not emit:
        print(f'{target}: nothing new ({len(rs)} rows all carried)')
        return

    section = '\n'.join(emit)
    if exists:
        merge_into(path, section)
        print(f'{target}: merged {len(emit)} lines (rows={len(rs)})')
    else:
        stem = target.split('.')[0]
        banner = f'''/*
 * {target} -- Windows CE book-surface header of record (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE
 * documentation (learn.microsoft.com previous-versions archive;
 * page ids cited per record).  Source book(s): {bookname}.
 * Generated by tools/gen-book.py.  Signatures are the pages' own
 * prints; glued print artifacts are split for compilation and the
 * verbatim prints are recorded in the per-row comments.
 */

#ifndef AKARI_{stem.upper()}_H
#define AKARI_{stem.upper()}_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {{
#endif

{section}

#ifdef __cplusplus
}}
#endif

#endif /* AKARI_{stem.upper()}_H */
'''
        with open(path, 'w', encoding='utf-8') as fh:
            fh.write(banner)
        print(f'{target}: NEW, {len(emit)} lines (rows={len(rs)})')


if __name__ == '__main__':
    main()
