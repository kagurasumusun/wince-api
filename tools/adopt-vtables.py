#!/usr/bin/env python3
"""adopt-vtables.py -- make the record-only COM interfaces callable
from C by emitting explicit vtable structs (M97).

Order source (docs/clean-room.md par.4, revision 2026-09-10): R1, the
CeGCC-lineage w32api fork (public domain) -- its DECLARE_INTERFACE_
blocks carry the CE-lineage vtable orders.  Method NAMES, parameter
NAMES and TYPES come from THIS project's own page records (the CE
pages' printed signatures in the header's comments); R1 supplies the
ORDER and the IUnknown/I* base chains, plus fill-in signatures for
R1-carried methods the CE pages do not document (kept, commented --
dropping a middle slot would shift the layout).

Calling convention: plain function pointers, i.e. WINAPI (which is
empty in this project: CE-wide cdecl).  R1's STDMETHODCALLTYPE =
__stdcall is NOT adopted (CeGCC-GCC attribute behaviour, not the CE
ABI; decision recorded in docs/inventory.md M95a-era notes).

Usage:
  python3 tools/adopt-vtables.py map <header.h>    # report only
  python3 tools/adopt-vtables.py write <header.h>  # insert the section
"""
import os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
R1 = '/home/user/.cache/w32api-ref/include'
EXCEPTION_FILES = {'winsock.h', 'winsock2.h', 'ws2tcpip.h',
                   'gl.h', 'glext.h', 'glu.h'}

MARK = 'M97 vtable adoption'

# ------------------------------------------------------------------ R1

STDMETHOD_RE = re.compile(
    r'STDMETHOD_\(\s*(\w+)\s*,\s*(\w+)\s*\)\s*\(\s*THIS\s*\)'
    r'|STDMETHOD\(\s*(\w+)\s*\)\s*\(\s*THIS\s*\)'
    r'|STDMETHOD_\(\s*(\w+)\s*,\s*(\w+)\s*\)\s*\(\s*THIS_\s*([^)]*)\)'
    r'|STDMETHOD\(\s*(\w+)\s*\)\s*\(\s*THIS_\s*([^)]*)\)')
DECL_INTF_RE = re.compile(
    r'DECLARE_INTERFACE(_)?\(\s*(\w+)\s*(?:,\s*(\w+)\s*)?\)')


def filter_conditionals(body):
    """Resolve simple preprocessor conditionals inside an interface
    body: for #ifdef take the #else branch (w32api default: the macro
    is undefined), for #ifndef/#if-nonzero take the then branch, for
    '#if 0' take nothing.  Unbalanced/unknown constructs keep the
    text (visible in map output as duplicates)."""
    out = []
    stack = []            # each entry: 'keep' | 'skip'
    for line in body.split('\n'):
        st = line.strip()
        m = re.match(r'#\s*ifdef\s+(\w+)', st)
        m2 = re.match(r'#\s*ifndef\s+(\w+)', st)
        m3 = re.match(r'#\s*if\s+(.*)', st)
        if m or m2 or m3:
            if m:
                stack.append('skip')          # wait for #else
            elif m2:
                stack.append('keep')
            else:
                stack.append('skip' if m3.group(1).strip() == '0' else 'keep')
            continue
        if re.match(r'#\s*else\b', st):
            if stack:
                stack[-1] = 'keep' if stack[-1] == 'skip' else 'skip'
            continue
        if re.match(r'#\s*endif\b', st):
            if stack:
                stack.pop()
            continue
        if st.startswith('#'):
            continue
        if any(x == 'skip' for x in stack):
            continue
        out.append(line)
    return '\n'.join(out)


def parse_r1():
    """interface -> {'base': name|None, 'file': fn,
    'methods': [(name, ret, [param types])]} (own methods only)."""
    out = {}
    for fn in sorted(os.listdir(R1)):
        if not fn.endswith('.h') or fn in EXCEPTION_FILES:
            continue
        text = open(os.path.join(R1, fn), encoding='utf-8',
                    errors='replace').read()
        text = re.sub(r'/\*.*?\*/', ' ', text, flags=re.S)
        text = re.sub(r'//[^\n]*', '', text)
        text = text.replace('\\\n', ' ')
        for m in DECL_INTF_RE.finditer(text):
            name, base = m.group(2), m.group(3)
            body_start = m.end()
            body_end = text.find('};', body_start)
            if body_end == -1:
                continue
            body = filter_conditionals(text[body_start:body_end])
            methods = []
            for sm in STDMETHOD_RE.finditer(body):
                if sm.group(1):      # STDMETHOD_(ret,name)(THIS)
                    methods.append((sm.group(2), sm.group(1), []))
                elif sm.group(3):    # STDMETHOD(name)(THIS)
                    methods.append((sm.group(3), 'HRESULT', []))
                elif sm.group(4):    # STDMETHOD_(ret,name)(THIS_ ...)
                    types = [t.strip() for t in sm.group(6).split(',')
                             if t.strip()]
                    methods.append((sm.group(5), sm.group(4), types))
                else:                # STDMETHOD(name)(THIS_ ...)
                    types = [t.strip() for t in sm.group(8).split(',')
                             if t.strip()]
                    methods.append((sm.group(7), 'HRESULT', types))
            if methods:
                out[name] = {'base': base, 'file': fn, 'methods': methods}
    return out


def flatten(r1, name):
    """(ordered methods [(segment, name, ret, [types])], base chain).
    R1 (w32api style) lists the COMPLETE vtable -- base methods
    included -- in every interface; the chain only labels segments."""
    chain = []
    n = name
    while n and n in r1:
        chain.append(n)
        n = r1[n]['base']
    chain.reverse()                          # base-most first
    basesets = [{m[0] for m in r1[i]['methods']} for i in chain[:-1]]
    methods = []
    for (mname, ret, types) in r1[name]['methods']:
        seg = name
        for i, bs in zip(chain[:-1], basesets):
            if mname in bs:
                seg = i                      # base-most declaring iface
                break
        methods.append((seg, mname, ret, types))
    return methods, chain


# ------------------------------------------------------------- our records

BANNER_RE = re.compile(r'/\*\s*(\w+):\s*documented methods\b')

# Type words the pages glue directly onto parameter names (longWidth,
# HRESULTNext, unsigned longfoo ...).  Longest first.
GLUE_TYPES = [
    'unsigned short', 'unsigned int', 'unsigned long', 'unsigned char',
    'REFERENCE_TIME', 'LONGLONG', 'ULONGLONG', 'OAHWND',
    'HRESULT', 'SCODE', 'long', 'int', 'short', 'char', 'float',
    'double', 'void',
]

# Return types the pages glue onto the method name in the signature.
RET_TYPES = ('HRESULT', 'ULONG', 'DWORD', 'LONG', 'BOOL', 'UINT',
             'LONGLONG', 'ULONGLONG', 'OAHWND', 'void', 'VOID')
RECORD_RE = re.compile(
    r'\s*\*\s+(?:ms|aa)(\d{6})\s+(\w+):\s+(.+)$')


def split_params(params):
    """Parameter list -> [(type, name)].  Handles the pages' glued
    misprints (HRESULTAlloc, DWORDdwFlags, REFERENCE_TIMErtNow) and
    trailing [] array parameters."""
    plist = []
    if params.strip() not in ('', 'void', 'VOID'):
        for p in params.split(','):
            p = p.split('//')[0].strip()   # strip inline page comments
            if not p:
                continue                    # empty piece (mangled record)
            is_array = p.endswith('[]')
            if is_array:
                p = p[:-2].strip()
            # array parameters decay to pointers (also permits opaque
            # element types, e.g. CATEGORYINFO)
            mm = re.match(r'^(.*?[\s*])\s*([A-Za-z_]\w*)$', p)
            if mm and mm.group(1).strip():
                plist.append((mm.group(1).strip() + ('*' if is_array else ''),
                              mm.group(2)))
                continue
            # glued misprints with a KNOWN type word (longWidth,
            # HRESULTNext, DWORDgrfFlags, REFERENCE_TIMErtNow)
            for gt in GLUE_TYPES:
                if p.startswith(gt):
                    rest = p[len(gt):]
                    if rest and re.match(r'^[A-Za-z_]\w*$', rest):
                        p = gt
                        plist.append((gt + ('*' if is_array else ''), rest))
                        break
            else:
                mm = re.match(r'^([A-Z][A-Z0-9_]*[A-Z_])([a-z]\w*)$', p)
                if mm:
                    plist.append((mm.group(1) + ('*' if is_array else ''),
                                  mm.group(2)))
                    continue
                plist.append((p + ('*' if is_array else ''), ''))
            continue
    return plist


def parse_records(header):
    """interface -> {'pages': n, 'methods': [(page, name, ret,
    [(type, pname), ...])]} from the `/* IName: documented methods`
    record banners (the M53/M94 format)."""
    text = open(os.path.join(ROOT, 'include', header),
                encoding='utf-8').read()
    out = {}
    cur = None
    for line in text.split('\n'):
        bm = BANNER_RE.search(line)
        if bm:
            cur = bm.group(1)
            out.setdefault(cur, {'pages': 0, 'methods': []})
            continue
        if cur is None:
            continue
        rm = RECORD_RE.match(line)
        if rm and cur in out:
            page, name, sig = rm.groups()
            sig = sig.rstrip().rstrip(';').strip()
            lp = sig.find('(')
            rp = sig.rfind(')')
            if lp == -1 or rp < lp:
                continue
            head = sig[:lp]
            hm = re.match(r'^([A-Za-z_]\w*)[\s]?([A-Za-z_]\w*)?$', head.strip())
            if hm and hm.group(2):
                if hm.group(2) != name:
                    continue          # not a plain signature line
                ret = hm.group(1)
            else:
                # glued return+name (HRESULTNext, HRESULTRenderFile)
                ret = None
                for rt in RET_TYPES:
                    if head.strip() == rt + name:
                        ret = rt
                        break
                if ret is None:
                    continue          # not a plain signature line
            plist = split_params(sig[lp + 1:rp])
            out[cur]['pages'] += 1
            out[cur]['methods'].append((page, name, ret, plist))
    return out


# ------------------------------------------------------------- compose

PTR_STYLE = [('__IView_pfncont', 'LPFNCONTINUE'), ('PVOID', 'VOID*'), ('PULONG', 'ULONG*'), ('PUINT', 'UINT*'),
             ('PUSHORT', 'USHORT*'), ('PUCHAR', 'UCHAR*')]

# Page-printed ALL-CAPS spellings -> the project's canonical typedefs.
TYPE_MAP = {'IENUMIDLIST': 'IEnumIDList',
            'LPENUMSTATDATA': 'IEnumSTATDATA*'}
# Page-printed case-misprint spellings (exact match).
EXACT_TYPE_MAP = {'IENumSTATDATA': 'IEnumSTATDATA',
                  'byte': 'BYTE',
                  '__IView_pfncont': 'LPFNCONTINUE',
                  'IEnumOleVerb': 'IEnumOLEVERB',
                  'IbaseFilter': 'IBaseFilter'}


def r1_type(t):
    for a, b in PTR_STYLE:
        if t == a:
            return b
        if t.startswith(a + ' '):     # R1 token with an embedded name
            return b + t[len(a):]
    return t


def compose(header):
    """-> list of (interface, rows, info) where rows =
    [(segment_iface, name, ret, 'page'|'R1', pageid, [params])]
    plus problems []."""
    recs = parse_records(header)
    r1 = parse_r1()
    problems = []
    result = []
    for iface in recs:
        if not recs[iface]['methods']:
            continue
        if iface not in r1:
            problems.append(f'{iface}: not carried by R1')
            continue
        flat, chain = flatten(r1, iface)
        if not chain or chain[0] != 'IUnknown':
            problems.append(f'{iface}: base chain {chain} has no IUnknown')
            continue
        own = {m[1]: m for m in recs[iface]['methods']}
        rows = []
        used = set()
        for (seg, mname, ret, types) in flat:
            if mname in own:
                page, name, pret, plist = own[mname]
                if len(plist) != len(types):
                    problems.append(
                        f'{iface}::{mname}: page has {len(plist)} params,'
                        f' R1 has {len(types)} -- ABI-safe R1 signature'
                        f' emitted, page record kept above')
                    rows.append((seg, mname, ret, 'R1', None,
                                 [(r1_type(t), '') for t in types]))
                else:
                    rows.append((seg, mname, pret, 'page', page, plist))
                used.add(mname)
            else:
                rows.append((seg, mname, ret, 'R1', None,
                             [(r1_type(t), '') for t in types]))
        missing = set(own) - used
        if missing:
            problems.append(
                f'{iface}: CE-documented methods absent from R1: '
                + ', '.join(sorted(missing)) + ' -- interface SKIPPED')
            continue
        result.append((iface, rows, recs[iface]['pages']))
    return result, problems


# ------------------------------------------------------------- emit

def cptr_type(t):
    t = re.sub(r'\s*\*\s*', '*', t)
    core = t.rstrip('*')
    if core in EXACT_TYPE_MAP:
        return EXACT_TYPE_MAP[core] + t[len(core):]
    m = re.match(r'^([A-Z][A-Z0-9_]*)(\**)$', t)
    if m and m.group(1) in TYPE_MAP:
        return TYPE_MAP[m.group(1)] + m.group(2)
    return t


def emit(header):
    result, problems = compose(header)
    L = []
    L.append('/* ================================================================== */')
    L.append(f'/* {MARK} -- COM interfaces made callable from C.  Vtable')
    L.append(' * ORDER adopted from R1 (CeGCC-lineage w32api, public')
    L.append(' * domain; docs/clean-room.md par.4 revision 2026-09-10);')
    L.append(' * method names/types are the CE pages\' own printed')
    L.append(' * signatures (the records above).  Methods the CE pages do')
    L.append(' * not document but R1 carries are INCLUDED and tagged')
    L.append(' * "(R1)" -- dropping a middle slot would shift the layout.')
    L.append(' * Calling convention: plain function pointers (WINAPI is')
    L.append(' * empty here: CE-wide cdecl; R1\'s __stdcall NOT adopted). */')
    L.append('/* ================================================================== */')
    for iface, rows, pages in result:
        L.append('')
        L.append(f'/* ---- {iface}: {pages} documented method pages; order R1 ---- */')
        L.append(f'typedef struct {iface}Vtbl {{')
        last_seg = None
        for (seg, mname, ret, src, page, plist) in rows:
            if seg != last_seg:
                L.append(f'    /* {seg} */')
                last_seg = seg
            args = [f'{iface}*']
            for (t, pn) in plist:
                args.append(cptr_type(t) + (' ' + pn if pn else ''))
            tag = f'  /* {page} */' if page else '  /* (R1) */'
            L.append(f'    {ret} (WINAPI *{mname})({", ".join(args)});{tag}')
        L.append(f'}} {iface}Vtbl;')
        L.append(f'struct {iface} {{ const {iface}Vtbl *lpVtbl; }};')
        for (seg, mname, ret, src, page, plist) in rows:
            n = len(plist)
            names = ['T'] + [chr(ord('a') + i) for i in range(n)]
            L.append(f'#define {iface}_{mname}({",".join(names)}) '
                     f'((T)->lpVtbl->{mname}({",".join(names)}))')
    return L, result, problems


M97_ANCHOR = '#ifdef __cplusplus\n}\n#endif'


def strip_m97(text):
    i = text.find('/* ' + MARK)
    if i == -1:
        return text
    j = text.rfind(M97_ANCHOR)
    assert j >= i, 'anchor before section'
    return text[:i] + text[j:]


def main():
    if len(sys.argv) < 3 or sys.argv[1] not in ('map', 'write'):
        sys.exit(__doc__)
    mode, header = sys.argv[1], sys.argv[2]
    L, result, problems = emit(header)
    if mode == 'map':
        for iface, rows, pages in result:
            r1only = [r[1] for r in rows if r[3] == 'R1']
            print(f'{iface}: {pages} pages, {len(rows)} vtable slots'
                  f' (R1-only: {", ".join(r1only) if r1only else "none"})')
        for p in problems:
            print('  ' + p)
        return 0
    if not result:
        print(f'{header}: no convertible interfaces')
        return 0
    path = os.path.join(ROOT, 'include', header)
    text = open(path, encoding='utf-8').read()
    text = strip_m96 = strip_m97(text)
    i = text.rfind(M97_ANCHOR)
    assert i != -1, 'extern-C close not found'
    block = '\n'.join(L) + '\n\n'
    text = text[:i] + block + text[i:]
    with open(path, 'w', encoding='utf-8') as fh:
        fh.write(text)
    print(f'{header}: wrote vtables for {len(result)} interfaces '
          f'({len(problems)} problems)')
    for p in problems:
        print('  ' + p)
    return 0


if __name__ == '__main__':
    sys.exit(main())
