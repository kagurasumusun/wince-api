#!/usr/bin/env python3
"""adopt-values.py -- adopt ABI constant values from the public-domain
CeGCC-lineage w32api reference (docs/clean-room.md par.4, revision
2026-09-10; R2/mingw-w64 removed the same day by user direction):

  R1 = CeGCC-lineage w32api fork (kagurasumusun/w32api; "THIS SOFTWARE
       IS NOT COPYRIGHTED ... public domain"), the CE parity target
       itself.  Its values ARE the CE-era ABI facts this project needs.
       The README's license-exception files (winsock.h / winsock2.h /
       ws2tcpip.h BSD, gl.h Mesa, glext.h/glu.h SGI) are NOT used:
       no fact is adopted from them.

The CE pages publish many constant NAMES without values; this tool
resolves those names against R1 and emits #define sections with
per-family provenance.  Names the official CE pages never mention
("not published" ledger entries) are not adopted.  Where an official
page prints a value, the page already won and no adoption happens
(the tool only targets names include/ does not #define).

Usage:
  python3 tools/adopt-values.py map <header.h>     # report what could be adopted
  python3 tools/adopt-values.py emit <header.h>    # print the C section
  python3 tools/adopt-values.py write <header.h>   # insert into the header
"""
import os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
R1 = '/home/user/.cache/w32api-ref/include'

# R1 README license-exception files: no fact may be adopted from them.
EXCEPTION_FILES = {
    'winsock.h', 'winsock2.h', 'ws2tcpip.h',
    'gl.h', 'glext.h', 'glu.h',
}

# Names never to adopt even if the reference carries them (project
# macros / guard macro families of our own).
EXCLUDE = {
    'AKARI_CE_NAME', 'AKARI_CE_IMPORT', '_M_IX86', '_X86_', '_WIN32_WCE',
    'UNDER_CE', 'WINAPI', 'CALLBACK', 'APIENTRY',
}

# Ledger entries whose names are NOT published on any official CE page
# (documented absence): the name is not part of the documented surface,
# so it is not adopted even though R1 carries it.
NOT_PUBLISHED = {
    'Commctrl.h': {'ANIMATE_CLASS', 'STATUSCLASSNAME'},
}

# Names whose documented home is ANOTHER project header; never
# adopted here even though this header's pages mention them in
# passing (home decided by the family's own ledger/records).
REHOME = {
    'Winuser.h': {'NM_RCLICK'},        # NM_* family: Commctrl.h ledger
    'aygshell.h': {'WM_LBUTTONDOWN'},  # core WM_*: Winuser.h
    'Commctrl.h': {'GN_CONTEXTMENU'},  # GN_ gesture: aygshell.h
}

# Page-spelled name -> R1 spelling (value adopted under the page
# spelling, the reference spelling noted in the emitted comment).
ALIASES = {
    'Shobjidl.h': {'SVUIA_IN_PLACEACTIVATE': 'SVUIA_INPLACEACTIVATE'},
}

# Page-harvested names are adopted only when R1 carries them in one
# of these fork files (prevents cross-family leakage through passing
# mentions on pages).  Comment/ledger-sourced names trust our own
# Requirements records and may come from any (non-exception) file.
FORK_HOME = {
    'Commctrl.h': {'commctrl.h', 'prsht.h'},
    'Prsht.h': {'prsht.h'},
    'Wininet.h': {'wininet.h'},
    'Urlmon.h': set(),
    'Shobjidl.h': {'shlobj.h', 'oleidl.h', 'objidl.h'},
    'aygshell.h': {'aygshell.h', 'sipapi.h'},
    'Sipapi.h': {'sipapi.h'},
    'Winuser.h': {'winuser.h'},
    'Wincrypt.h': {'wincrypt.h'},
    'Winscard.h': set(),
    'Tapi.h': set(),
    'Imm.h': {'imm.h'},
    'Winsock2.h': {'af_irda.h'},
    'Ws2tcpip.h': set(),
    'Mlang.h': {'mlang.h'},
}

# Full spellings the comment ledgers abbreviate.
EXPLICIT_TARGETS = {
    'Wininet.h': [
        'HTTP_QUERY_FLAG_NUMBER', 'HTTP_QUERY_FLAG_SYSTEMTIME',
        'HTTP_QUERY_FLAG_REQUEST_HEADERS', 'HTTP_QUERY_CUSTOM',
        'HTTP_QUERY_CONTENT_TRANSFER_ENCODING',
    ],
}

MARKERS = {h: 'M96 value adoption' for h in (
    'Commctrl.h', 'Prsht.h', 'Wininet.h', 'Urlmon.h', 'Shobjidl.h',
    'aygshell.h', 'Sipapi.h', 'Winuser.h', 'Wincrypt.h', 'Winscard.h',
    'Tapi.h', 'Imm.h', 'Winsock2.h', 'Ws2tcpip.h', 'Mlang.h',
)}

DEFINE_RE = re.compile(
    r'^\s*#\s*define\s+([A-Za-z_][A-Za-z0-9_]*)\s+(.+)$')
ENUM_RE = re.compile(r'enum\s*\w*\s*\{([^{}]*)\}', re.S)
PAGEID_RE = re.compile(r'\b(?:ms|aa)(\d{6})\b')
NAME_RE = re.compile(r'\b[A-Z][A-Z0-9]{1,}(?:_[A-Z0-9]+)+\b')

SUFFIX_RE = re.compile(r'(0[xX][0-9A-Fa-f]+|\d+)[uUlL]+')
# Integer casts are value-preserving here (all adopted values fit).
CAST_RE = re.compile(
    r'\(\s*(?:unsigned\s+)?(?:int|long|short|char|UINT|WORD|DWORD|INT|'
    r'LONG|WPARAM|LPARAM|LRESULT|INT_PTR|UINT_PTR|LONG_PTR|ATOM|HANDLE|'
    r'HRESULT|SCODE|HLOCAL|HGLOBAL)'
    r'\s*\)')
IDENT_RE = re.compile(r'\b[A-Za-z_][A-Za-z0-9_]*\b')
SAFE_RE = re.compile(r'^[0-9a-fA-FxX+\-*/%()~|^&<> \t]*$')


def parse_tree(root):
    """(name -> (raw expression, source file), [enum member lists]).
    Object-like macros carry their expression; enum members carry
    their explicit '= expr', '#+1' (previous member of the SAME enum
    + 1) or '#0' (first member, implicit 0).  Files in
    EXCEPTION_FILES are skipped entirely (license)."""
    out = {}
    enums = []
    if not os.path.isdir(root):
        return out, enums
    for fn in sorted(os.listdir(root)):
        if not fn.endswith('.h') or fn in EXCEPTION_FILES:
            continue
        try:
            text = open(os.path.join(root, fn), encoding='utf-8',
                        errors='replace').read()
        except OSError:
            continue
        text = re.sub(r'/\*.*?\*/', ' ', text, flags=re.S)
        text = re.sub(r'//[^\n]*', '', text)
        text = text.replace('\\\n', ' ')
        for line in text.split('\n'):
            m = DEFINE_RE.match(line)
            if m:
                name, expr = m.group(1), m.group(2).strip()
                if expr.startswith('(') and name not in out:
                    # function-like macro ("#define F(x) ..."): expr
                    # begins with the parameter list -- never a value
                    if re.match(r'^\(\s*[A-Za-z_]\w*\s*[,)]', expr):
                        continue
                if expr and name not in out:
                    out[name] = (expr, fn)
        for em in ENUM_RE.finditer(text):
            body = em.group(1)
            members = []
            for item in body.split(','):
                item = item.strip()
                if not item:
                    continue
                mm = re.match(r'^([A-Za-z_]\w*)\s*(?:=\s*(.+))?$', item)
                if not mm:
                    continue
                name, expr = mm.group(1), mm.group(2)
                if name in out:
                    continue
                if expr:
                    out[name] = (expr.strip(), fn)
                else:
                    out[name] = ('#0' if not members else '#+1', fn)
                members.append(name)
            if members:
                enums.append(members)
    return out, enums


def evaluate(expr, table, depth=0):
    """Evaluate a C preprocessor value expression to an int."""
    if depth > 40:
        raise ValueError('recursion too deep: ' + expr)
    expr = expr.strip()
    # mingw-era value-preserving wrappers appear in R1 too; they are
    # the identity for 32-bit values.
    for _ in range(4):
        s2 = re.sub(r'(?:_HRESULT_TYPEDEF_|__MSABI_LONG_?)\s*\(\s*([^()]*?)\s*\)',
                    r'\1', expr)
        if s2 == expr:
            break
        expr = s2
    if expr == '#+1':
        raise ValueError('implicit enum successor (resolved by caller)')
    s = CAST_RE.sub(' ', SUFFIX_RE.sub(r'\1', expr))

    def repl(m):
        tok = m.group(0)
        if tok not in table:
            raise ValueError('unresolved ' + tok)
        return '(' + str(evaluate(table[tok][0], table, depth + 1)) + ')'

    s = IDENT_RE.sub(repl, s)
    if not SAFE_RE.match(s):
        raise ValueError('unsafe expr: ' + s)
    v = eval(s, {'__builtins__': {}}, {})
    if not isinstance(v, int):
        raise ValueError('non-int ' + expr)
    return v


_maps = None


def maps():
    """{'R1': {name: value}} with implicit enum successors resolved
    WITHIN each enum and exception files excluded."""
    global _maps
    if _maps is None:
        _maps = {}
        raw, enums = parse_tree(R1)
        vals = {}
        for name, (expr, _fn) in raw.items():
            if expr in ('#+1', '#0'):
                continue
            try:
                vals[name] = evaluate(expr, raw)
            except Exception:
                pass
        for members in enums:
            cur = None
            for name in members:
                e = raw.get(name, (None, None))[0]
                if e == '#0':
                    v = 0
                elif e == '#+1':
                    v = None if cur is None else cur + 1
                else:
                    v = vals.get(name)
                if v is None:
                    cur = None
                else:
                    vals[name] = v
                    cur = v
        _maps['R1'] = vals
        _maps['R1files'] = {n: raw[n][1] for n in vals}
    return _maps


def ours_defined(exclude=frozenset()):
    """#define names across include/ (value presence filter), minus
    an exclusion set (used to ignore a header's own M96 section when
    re-emitting it)."""
    names = set()
    idir = os.path.join(ROOT, 'include')
    for fn in os.listdir(idir):
        if not fn.endswith('.h'):
            continue
        text = open(os.path.join(idir, fn), encoding='utf-8').read()
        text = re.sub(r'/\*.*?\*/', ' ', text, flags=re.S)
        text = re.sub(r'//[^\n]*', '', text)
        for m in re.finditer(r'^\s*#\s*define\s+([A-Za-z_][A-Za-z0-9_]*)',
                             text, re.M):
            names.add(m.group(1))
    return names - set(exclude)


M96_MARK = 'M96 value adoption -- values adopted'


def strip_m96(text):
    """Remove this header's existing M96 adoption section.
    -> (text_without_section, names_defined_in_section)"""
    i = text.find(M96_MARK)
    if i == -1:
        return text, set()
    start = text.rfind('/*', 0, i)          # banner opener line
    ms = list(re.finditer(r'^[ \t]*#endif[^\n]*$', text, re.M))
    end = ms[-1].start() if ms else len(text)
    sec = text[start:end]
    names = set(re.findall(r'^#define\s+(\w+)', sec, re.M))
    return text[:start] + text[end:], names


def code_identifiers(skip_m96_of=None):
    """Identifiers used in non-comment code anywhere in include/
    (enum members, typedefs, parameter names) -- a #define of such a
    name would shadow or collide, so adoption skips them.  The M96
    section of skip_m96_of is ignored (it is being re-emitted)."""
    names = set()
    idir = os.path.join(ROOT, 'include')
    for fn in os.listdir(idir):
        if not fn.endswith('.h'):
            continue
        text = open(os.path.join(idir, fn), encoding='utf-8').read()
        if fn == skip_m96_of:
            text, _own = strip_m96(text)
        text = re.sub(r'/\*.*?\*/', ' ', text, flags=re.S)
        text = re.sub(r'//[^\n]*', '', text)
        names |= set(re.findall(r'[A-Za-z_]\w*', text))
    return names


NS_CACHE = os.path.join(ROOT, 'build', 'not-supported-names.txt')
NS_SCAN_RE = re.compile(
    r'\b([A-Z][A-Z0-9]{1,}(?:_[A-Z0-9]+)+)\s{0,3}Not supported\b')


def not_supported():
    """Names the CE pages mark 'Not supported' in flag-table rows
    ('NAME Not supported.').  These are documented as ABSENT from the
    CE ABI and are never adopted.  Cached in build/; regenerated by a
    full corpus scan when the cache is missing (the strict
    name-adjacency pattern avoids prose false positives such as
    'INTERNET_FLAG_SECURE is not supported [for FTP]')."""
    if os.path.exists(NS_CACHE):
        return {l.split('\t')[0] for l in open(NS_CACHE) if l.strip()}
    sys.path.insert(0, os.path.join(ROOT, 'tools'))
    from rtctext import page_text
    ns = {}
    pdir = os.path.join(ROOT, 'build', 'pages')
    if os.path.isdir(pdir):
        for fn in sorted(os.listdir(pdir)):
            if not fn.endswith('.html'):
                continue
            try:
                t = re.sub(r'\s+', ' ', page_text(fn[:-5]))
            except Exception:
                continue
            for m in NS_SCAN_RE.finditer(t):
                ns.setdefault(m.group(1), set()).add(fn[:-5])
        os.makedirs(os.path.dirname(NS_CACHE), exist_ok=True)
        with open(NS_CACHE, 'w') as fh:
            for n in sorted(ns):
                fh.write(n + '\t' + ' '.join(sorted(ns[n])) + '\n')
    return set(ns)


def page_text_names(pid):
    sys.path.insert(0, os.path.join(ROOT, 'tools'))
    from rtctext import page_text
    try:
        t = page_text('ms' + pid if pid.isdigit() else pid)
    except Exception:
        return set()
    return set(NAME_RE.findall(t))


def targets(header):
    """Constant-like names this header's CE documentation mentions
    (comment ledgers, record comments, and every page whose id is
    cited in a comment) that include/ does not already #define."""
    text = open(os.path.join(ROOT, 'include', header),
                encoding='utf-8').read()
    ctext = ' '.join(re.findall(r'/\*.*?\*/', text, flags=re.S))
    text0, own_m96 = strip_m96(text)
    defined = ours_defined(exclude=own_m96)
    comment_toks = set(NAME_RE.findall(ctext))
    comment_toks |= set(EXPLICIT_TARGETS.get(header, ()))
    page_toks = set()
    for pid in PAGEID_RE.findall(ctext):
        page_toks |= page_text_names(pid)
    page_toks -= comment_toks
    toks = comment_toks | page_toks
    toks -= NOT_PUBLISHED.get(header, set())
    toks -= REHOME.get(header, set())
    toks -= not_supported() & toks
    toks -= code_identifiers(skip_m96_of=header) & toks
    toks = {t for t in toks if t not in defined and t not in EXCLUDE}
    return {t: ('comment' if t in comment_toks else 'page') for t in toks}


def resolve(names, header):
    """-> (adopted{token: (value, ref_spelling)}, unresolved [tokens])
    Values come from R1 only; ALIASES map page spellings to the R1
    spelling (the emitted define keeps the page spelling).  Names
    harvested from page text are adopted only when R1 carries them
    in a FORK_HOME file of this header."""
    m = maps()
    aliases = ALIASES.get(header, {})
    home = FORK_HOME.get(header, set())
    adopted, unresolved = {}, []
    for t in sorted(names):
        ref = aliases.get(t, t)
        v = m['R1'].get(ref)
        if v is not None:
            if names[t] == 'page' and m['R1files'].get(ref) not in home:
                unresolved.append(t)
                continue
            adopted[t] = (v, ref)
        else:
            unresolved.append(t)
    return adopted, unresolved


def fmt(v):
    if v >= 0:
        return '0x%04X' % v
    return '(%d)' % v


def family(t):
    return t.split('_')[0]


def emit_section(header, marker):
    adopted, unresolved = resolve(targets(header), header)
    fams = {}
    for t, (v, ref) in adopted.items():
        fams.setdefault(family(t), []).append((t, v, ref))
    L = []
    L.append('/* ================================================================== */')
    L.append(f'/* {marker} -- values adopted from the CeGCC-lineage w32api')
    L.append(' * reference (R1, public domain; docs/clean-room.md par.4')
    L.append(' * revision 2026-09-10).  Every name below is documented by')
    L.append(' * the official CE pages WITHOUT a value (see the record')
    L.append(' * comments and the held ledger in this header); the value')
    L.append(' * is a CE-era ABI fact carried by the CE lineage itself.')
    L.append(' * Desktop mingw-w64 was considered and EXCLUDED as a source')
    L.append(' * (desktop-era values; policy note in clean-room.md).  R1\'s')
    L.append(' * license-exception files (winsock*, gl*) are unused.')
    L.append(' * ================================================================== */')
    for fam in sorted(fams):
        rows = sorted(fams[fam], key=lambda r: (r[1], r[0]))
        L.append('')
        L.append(f'/* ---- {fam}_ family ({len(rows)} names; R1) ---- */')
        for t, v, ref in rows:
            note = '' if ref == t else f'  /* R1: {ref} */'
            L.append(f'#define {t:<44} {fmt(v)}{note}')
    return L, adopted, unresolved


def main():
    if len(sys.argv) < 3 or sys.argv[1] not in ('map', 'emit', 'write'):
        sys.exit(__doc__)
    mode, header = sys.argv[1], sys.argv[2]
    marker = MARKERS.get(header, 'M96 value adoption')
    if mode == 'map':
        adopted, unresolved = resolve(targets(header), header)
        print(f'{header}: adoptable {len(adopted)}, unresolved {len(unresolved)}')
        print('  unresolved:', ' '.join(sorted(unresolved)[:60]))
        return 0
    L, adopted, unresolved = emit_section(header, marker)
    if mode == 'emit':
        print('\n'.join(L))
        print(f'/* adopted {len(adopted)}, unresolved {len(unresolved)} */')
        return 0
    # write: insert before the trailing extern-C close
    if not adopted:
        print(f'{header}: nothing adoptable from R1 -- no section written')
        return 0
    path = os.path.join(ROOT, 'include', header)
    text = open(path, encoding='utf-8').read()
    if M96_MARK in text:
        text, _own = strip_m96(text)
    # insert before the LAST #endif line (the include guard close)
    ms = list(re.finditer(r'^[ \t]*#endif[^\n]*$', text, re.M))
    assert ms, 'include-guard #endif not found'
    i = ms[-1].start()
    block = '\n'.join(L) + '\n\n'
    text = text[:i] + block + text[i:]
    with open(path, 'w', encoding='utf-8') as fh:
        fh.write(text)
    print(f'{header}: wrote {len(adopted)} defines '
          f'({len(unresolved)} unresolved)')
    return 0


if __name__ == '__main__':
    sys.exit(main())
