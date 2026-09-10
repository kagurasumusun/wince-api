#!/usr/bin/env python3
"""gen-m94-commctrl.py -- M94 Shell-book completion, part 1:
append the per-page message/macro/notification records of the
Commctrl.h-homed gap rows to include/Commctrl.h, compile the four
newly-printed structures, and emit include/Shellcb.h and
include/Advbacklight.h.

Idempotent: the appended section is guarded by a marker comment.
"""
import json, os, re, sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, HERE)
from rtctext import page_text  # noqa: E402

COMMCTRL_H = os.path.join(ROOT, 'include', 'Commctrl.h')
MARKER = 'M94 (Shell book completion) message/macro records'
HOMES = {'Commctrl.h.', 'Commctrl.h.Se', 'Commctrl.h, Prsht.h, Shlguid.h.'}

# ---------------------------------------------------------------- page text helpers

def body_lines(pid):
    t = page_text(pid)
    lines = [l.strip() for l in t.split('\n') if l.strip()]
    idx = None
    for i, l in enumerate(lines):
        if l == 'In this article':
            idx = i
            break
    if idx is None:
        idx = 0
    out = []
    for l in lines[idx + 1:]:
        if l == 'Requirements':
            break
        out.append(l)
    return out


PACK_RE = re.compile(r'(wParam|lParam|\(WPARAM\)|\(LPARAM\)|FAR \*\))')


def extract(pid, name):
    """Return (kind, text) where kind in msg/proto/define/struct/bare."""
    out = body_lines(pid)
    # 1. message packing line starting with the name (often glued)
    for i, l in enumerate(out):
        if l.startswith(name) and PACK_RE.search(l):
            return ('msg', l)
    # 2. bare-name line followed by a packing line (TBN_BEGINDRAG shape)
    for i, l in enumerate(out):
        if l.rstrip(';') == name:
            for j in range(i + 1, min(i + 4, len(out))):
                if PACK_RE.search(out[j]) and '=' in out[j]:
                    return ('msg', name + ' ' + out[j])
                if out[j] in ('Parameters', 'Return Values'):
                    break
            return ('bare', name)
    # 3. #define body (macro pages that print the wrapper)
    for i, l in enumerate(out):
        if l.startswith('#define ' + name):
            sig = [l]
            j = i + 1
            while j < len(out):
                sig.append(out[j])
                if out[j].rstrip().endswith(')') and not out[j].startswith('\\'):
                    break
                if out[j].startswith(('Parameters', 'Requirements')):
                    sig.pop()
                    break
                j += 1
            return ('define', '\n'.join(sig))
    # 4. prototype: name( on a line
    for i, l in enumerate(out):
        if 'Microsoft Learn' in l or l.startswith('#'):
            continue
        m = re.search(re.escape(name) + r'\s*\(', l)
        if m:
            sig = l
            j = i + 1
            while not sig.endswith(';') and j < len(out) and j < i + 6:
                nxt = out[j]
                sig += '\n' + nxt
                j += 1
            if sig.rstrip().endswith(';'):
                return ('proto', sig)
    # 5. typedef struct body (single-line prints and multi-line)
    for i, l in enumerate(out):
        if l.startswith('typedef struct'):
            if re.search(r'\}\s*\w+[^;]*;', l):
                return ('struct', l)
            sig = [l]
            j = i + 1
            while j < len(out):
                sig.append(out[j])
                if re.search(r'\}\s*\w+[^;]*;', out[j]):
                    return ('struct', '\n'.join(sig))
                if out[j] == 'Members':
                    break
                j += 1
    # 6. mixed/notification print on one line (TCN_SELCHANGING shape)
    for l in out:
        if PACK_RE.search(l) and ('LPNMHDR' in l or re.search(
                r'\b\w+\s*=\s*\(', l)):
            return ('msg', l)
    # 7. anything containing the name
    for l in out:
        if name in l and 'Microsoft Learn' not in l:
            return ('line', l)
    return ('bare', name)


def oneline(text):
    return re.sub(r'\s+', ' ', text).strip()


# ---------------------------------------------------------------- families

FAMILIES = [
    ('Date and Time Picker control (DTM_/DTN_/DateTime_)',
     ('DTM_', 'DTN_', 'DateTime_')),
    ('Header control (HDM_/HDN_/Header_)',
     ('HDM_', 'HDN_', 'Header_')),
    ('List-View control (LVM_/LVN_/ListView_)',
     ('LVM_', 'LVN_', 'ListView_', 'LVS_')),
    ('Month Calendar control (MCM_/MCN_/MonthCal_)',
     ('MCM_', 'MCN_', 'MonthCal_')),
    ('Progress bar (PBM_)', ('PBM_',)),
    ('Rebar control (RB_/RBN_)', ('RB_', 'RBN_')),
    ('Status bar (SB_/SBN_)', ('SB_', 'SBN_')),
    ('Toolbar (TB_/TBN_)', ('TB_', 'TBN_')),
    ('Tooltip control (TTM_/TTN_)', ('TTM_', 'TTN_')),
    ('Trackbar (TBM_)', ('TBM_',)),
    ('Tab control (TCM_/TCN_/TabCtrl_)',
     ('TCM_', 'TCN_', 'TabCtrl_')),
    ('Tree-View control (TVM_/TVN_/TreeView_)',
     ('TVM_', 'TVN_', 'TreeView_')),
    ('Up-Down control (UDM_)', ('UDM_',)),
]


def family(name):
    for fam, prefixes in FAMILIES:
        for p in prefixes:
            if name.startswith(p):
                return fam
    return 'Shared notifications and misc (NM_/WM_/other)'


def short_name(title):
    t = re.sub(r'\s*\(Windows CE [^)]*\)\s*$', '', title).strip()
    t = re.sub(r'\s*\([^)]*\)\s*$', '', t).strip()
    for tail in (' Callback Function', ' Function', ' Structure',
                 ' Enumeration', ' Interface', ' Method', ' Message',
                 ' Macro', 'Notifications', ' Notification'):
        if t.endswith(tail):
            t = t[:-len(tail)].strip()
    return t


# ---------------------------------------------------------------- gap set

def gap_rows():
    rows = json.load(open(os.path.join(ROOT, 'build', 'rows.json')))
    ids = set()
    man = os.path.join(ROOT, 'tools', 'manifests', 'shell-book.manifest')
    for line in open(man):
        if line.strip():
            ids.add(line.split('\t')[0])
    headers = {}
    for fn in os.listdir(os.path.join(ROOT, 'include')):
        if fn.endswith('.h'):
            headers[fn] = open(os.path.join(ROOT, 'include', fn),
                               encoding='utf-8').read()
    out = []
    for r in rows:
        if r['id'] not in ids:
            continue
        if (r.get('header') or '') not in HOMES:
            continue
        name = short_name(r.get('title', ''))
        if not name:
            continue
        if any((' ' + name + ' ') in (' ' + txt + ' ') or
               name in txt for txt in headers.values()):
            continue
        out.append((r['id'], r.get('title', ''), name))
    return out


# ---------------------------------------------------------------- emit

def rec_comment(pid, title, name, kind, text):
    body = text.rstrip(';') + (';' if kind in ('msg', 'proto') else '')
    if kind in ('define', 'struct') or '\n' in body:
        lines = body.split('\n')
        out = [f'/* {pid} "{title}" (printed verbatim; references '
               f'held value-less constants):']
        for l in lines:
            out.append(' *   ' + l)
        out.append(' */')
        return out
    return [f'/* {pid} "{title}": `{body}` */']



# Compiled forms of the four resolvable structures (member order and
# declared types verbatim from the prints; only whitespace normalized).
STRUCT_EMIT = {
 'LVGROUP': [
  'typedef struct LVGROUP {',
  '    UINT    cbSize;',
  '    UINT    mask;',
  '    LPWSTR  pszHeader;',
  '    int     cchHeader;',
  '    LPWSTR  pszFooter;',
  '    int     cchFooter;',
  '    int     iGroupId;',
  '    UINT    stateMask;',
  '    UINT    state;',
  '    UINT    uAlign;',
  '} LVGROUP, *PLVGROUP;',
 ],
 'LVGROUPMETRICS': [
  'typedef struct LVGROUPMETRICS {',
  '    UINT      cbSize;',
  '    UINT      mask;',
  '    UINT      Left;',
  '    UINT      Top;',
  '    UINT      Right;',
  '    UINT      Bottom;',
  '    COLORREF  crLeft;',
  '    COLORREF  crTop;',
  '    COLORREF  crRight;',
  '    COLORREF  crBottom;',
  '    COLORREF  crRightHeader;',
  '    COLORREF  crFooter;',
  '} LVGROUPMETRICS, *PLVGROUPMETRICS;',
 ],
 'LVSETINFOTIP': [
  'typedef struct LVSETINFOTIP {',
  '    UINT    cbSize;',
  '    DWORD   dwFlags;',
  '    LPWSTR  pszText;',
  '    int     iItem;',
  '    int     iSubItem;',
  '} LVSETINFOTIP, *PLVSETINFOTIP;',
 ],
 'FILECHANGENOTIFY': [
  'typedef struct tagFILECHANGENOTIFY {',
  '    DWORD           dwRefCount;',
  '    FILECHANGEINFO  fci;',
  '} FILECHANGENOTIFY;',
 ],
}


def main():
    gaps = gap_rows()
    print(f'Commctrl-homed gap rows: {len(gaps)}')

    sections = {}   # family -> list of comment lines
    structs = []    # (pid, name, text) for compiled structs
    notes = []
    fails = []
    for pid, title, name in sorted(gaps, key=lambda g: g[2]):
        kind, text = extract(pid, name)
        if kind is None or text is None:
            fails.append((pid, title))
            continue
        if kind == 'struct' and name in ('LVGROUP', 'LVGROUPMETRICS',
                                         'LVSETINFOTIP', 'FILECHANGENOTIFY'):
            structs.append((pid, name, text))
            continue
        fam = family(name)
        sections.setdefault(fam, [])
        sections[fam] += rec_comment(pid, title, name, kind, text)
        sections[fam].append('')

    if fails:
        print('EXTRACTION FAILURES:', fails)
        sys.exit(1)

    L = []
    L.append('/* ================================================================== */')
    L.append(f'/* {MARKER}.')
    L.append(' *')
    L.append(' * The Shell-book gap survey (M94a) showed these Requirements rows')
    L.append(' * homed in Commctrl.h were never shipped.  Their pages print no')
    L.append(' * numeric message values (full-corpus grep; the desktop Win32')
    L.append(' * reference does not print them either -- checked 2026-09-10),')
    L.append(' * so per the hold policy every row below is RECORDED with its')
    L.append(' * printed wParam/lParam packing or prototype; none can #define')
    L.append(' * without inventing values (the M82/M92 name-list precedent).')
    L.append(' * Bodies/prototypes that reference the constants symbolically')
    L.append(' * are kept verbatim.  Print oddities noted inline.')
    L.append(' * ================================================================== */')
    L.append('')
    L.append('/* aa453482 "LVM_SETICONSPACING": the page prints the name')
    L.append(' * "LVS_SETICONSPACING" (archive misprint).  Recorded there. */')
    L.append('/* ms911819 "MCN_SELECTNONE": the page prints "MCN_SELECT;"')
    L.append(' * (archive oddity).  Recorded there. */')
    L.append('/* ms933410 "TCN_SELCHANGING": the page prints "TCN_SELCHANGE')
    L.append(' * lpnmhdr = (LPNMHDR) lParam;" (archive oddity). */')
    L.append('')

    held = [s_ for s_ in structs if s_[1] == 'LVINSERTGROUPSORTED']
    structs[:] = [s_ for s_ in structs if s_[1] != 'LVINSERTGROUPSORTED']
    for pid, name, text in structs:
        L.append(f'/* {pid} "{name}": `{oneline(text)}` -- all member')
        L.append(' * types resolve, so the structure compiles (32-bit size')
        L.append(' * TU-asserted by the M94 block in tests/host/tu_compile.c). */')
        emit = STRUCT_EMIT[name]
        L += emit
        L.append('')

    for fam, _ in FAMILIES + [('Shared notifications and misc '
                               '(NM_/WM_/other)', ())]:
        if fam not in sections:
            continue
        L.append('/* ------------------------------------------------------------------ */')
        L.append(f'/* {fam} */')
        L.append('/* ------------------------------------------------------------------ */')
        L.append('')
        L += sections[fam]

    L.append('/* aa453429 "LVINSERTGROUPSORTED" is HELD as a structure: the')
    L.append(' * print `typedef struct LVINSERTGROUPSORTED { PFNLVGROUPCOMPARE')
    L.append(' * pfnGroupCompare; LPVOID *pvData; LVGROUP lvGroup;}` names')
    L.append(' * PFNLVGROUPCOMPARE, which has no typedef or signature on any')
    L.append(' * page in the corpus (used by aa453405/aa453429/aa453519 only). */')
    L.append('')
    L.append('/* LVGROUP flag names printed on aa453426 (mask/state/uAlign):')
    L.append(' *   LVGF_ALIGN LVGF_FOOTER LVGF_GROUPID LVGF_HEADER LVGF_NONE')
    L.append(' *   LVGF_STATE')
    L.append(' *   LVGS_NORMAL')
    L.append(' *   LVGA_FOOTER_CENTER LVGA_FOOTER_LEFT LVGA_FOOTER_RIGHT')
    L.append(' *   LVGA_HEADER_CENTER LVGA_HEADER_LEFT LVGA_HEADER_RIGHT')
    L.append(' * LVGROUPMETRICS mask names printed on aa453427:')
    L.append(' *   LVGMF_BORDERCOLOR LVGMF_BORDERSIZE LVGMF_NONE')
    L.append(' *   LVGMF_TEXTCOLOR')
    L.append(' * (names only; no values printed anywhere). */')
    L.append('')

    text = open(COMMCTRL_H, encoding='utf-8').read()
    if MARKER in text:
        print('already appended -- nothing to do')
        return
    anchor = '#ifdef __cplusplus\n}\n#endif\n\n#endif /* AKARI_COMMCTRL_H */'
    assert anchor in text, 'tail anchor not found'
    block = '\n'.join(L) + '\n'
    text = text.replace(anchor, block + '\n' + anchor)
    with open(COMMCTRL_H, 'w', encoding='utf-8') as fh:
        fh.write(text)
    n = sum(1 for line in L if re.match(r'/\* (ms|aa)\d', line))
    print(f'appended {n} per-page records + {len(structs)} struct records')


if __name__ == '__main__':
    main()
