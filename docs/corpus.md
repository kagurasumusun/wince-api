# Page corpus preservation (export / push / delete / refetch)

Per the owner's workflow, every official Microsoft Learn page that this
project reads must be:

1. **fully saved and pushed** (to GitHub), then
2. **deleted from the working session**, and
3. **re-fetched from GitHub** at the start of the next session.

## Where pages live

* Working downloads during a session: `build/pages/` (CE 5.0,
  `(v=msdn.10)`) and `build/pages6/` (Windows Embedded CE 6.0,
  `(v=winembedded.60)`).  `build/` is gitignored and is *not* part of
  the session snapshot — it must not be treated as durable.
* Preservation repository: **`kagurasumusun/wince-docs-corpus`**
  (public; raw Microsoft Learn HTML, CC BY 4.0 with attribution).  The
  MIT clean-room `wince-api` tree never contains raw MS pages.
* Durable book lists stay in `tools/manifests/*.manifest` (committed to
  wince-api); the corpus repo additionally keeps `rows.json`, the
  official TOC snapshots (`catalogs/*.tsv`) and `INDEX.txt`.

## Round trip

`tools/ce-corpus.py` performs the copy in both directions.

At session start (after a fresh workspace):

```sh
git clone https://github.com/kagurasumusun/wince-docs-corpus
python3 tools/ce-corpus.py import --corpus ../wince-docs-corpus
```

This restores all previously preserved pages into `build/` (files
already present are skipped, so a mid-session partial fetch can be
resumed) and restores `rows.json` and the catalogs.

Before the end of a session (after any harvesting):

```sh
python3 tools/ce-corpus.py export --corpus ../wince-docs-corpus
git -C ../wince-docs-corpus add -A
git -C ../wince-docs-corpus commit -m "corpus: <tree> <n> pages"
git -C ../wince-docs-corpus push
```

Then delete the corpus clone and `build/` from the session.

## External-official trees (M52 derived-value policy)

* `pagesw/`: desktop Win32 reference pages
  (learn.microsoft.com/windows/win32) read as the fixed-ABI value
  source for M52/M53 derivations: winuser-nf-keybd_event.html
  (KEYEVENTF_EXTENDEDKEY 0x0001 / KEYEVENTF_KEYUP 0x0002) and
  winuser-ns-input.html (INPUT_MOUSE 0 / INPUT_KEYBOARD 1 /
  INPUT_HARDWARE 2); and, for M53, the 14 pages listed in
  `tools/manifests/stdshell-desktop.manifest` (NOTIFYICONDATAA /
  Shell_NotifyIconW / SHELLEXECUTEINFOA / SHGetFileInfoW / BROWSEINFOA
  / _SHGDNF / _SVSIF / _SVGIO value tables, the
  WM_CHOOSEFONT_GETLOGFONT formula page, and the CSIDL / STRRET /
  SHFILEOPSTRUCTA / SHBrowseForFolderA / SHAddToRecentDocs pages
  checked valueless to ground the held sets).  Each derivation is
  recorded per item in docs/inventory.md M52/M53.
* `pageswm/`: Windows Mobile 6.5 documentation pages, extracted from
  the official Microsoft Download Center CHM
  (download.microsoft.com/download/d/5/3/d532530a-507f-488e-9747-1f8757071d92/windowsmobile6.5.chm,
  linked from the learn.microsoft.com archive page dn887939; CC BY
  attribution as published).  34 pages: the value-sweep evidence
  (SIPSTATE / SHIC_FEATURE / SHNP declaration pages, "Keys and Key
  Codes for Windows Mobile", the AYGShell/SIP/keyboard pages checked
  for the negative results) and, for M53, the three gesture pages
  (wm65-NMRGINFO, wm65-GN_CONTEXTMENU, wm65-NM_RECOGNIZEGESTURE -- the
  sole official sources: no CE 5.0/6.0/Compact 7/Compact 2013 page
  exists for them).  The CHM itself (63 MB) is not committed;
  the URL above is the durable official source.

## Current corpus (2026-09-09, M53)

* `pages5/`: 2152 CE 5.0 `(v=msdn.10)` pages — the full committed
  manifest set (91 manifests incl. the M43 TAPI/TSPI manifests, the
  M45 `tapi-client-functions.manifest`, the M46
  `imm-reference.manifest`, the M47 `crypt-csp-base.manifest`, the
  M48/M49 `crypt-cert` / `crypt-encode-pfx` / `crypt-structs` /
  `smartcard` manifests, the M50 `aygshell.manifest` and the M51
  `sip.manifest`) plus the M34a type/callback pages (aa450831
  EXTENDED_NAME_FORMAT, ms904723 EnumCodePagesProc) and the five M50
  dependency pages (ms931479 NMHDR, ms889030 FILECHANGEINFO, ms932860
  SIPINFO, aa453890 WM_NOTIFY, aa453906 WM_SETTINGCHANGE) and the M51
  message dependency page aa453870 WM_IM_INFO (aa453912
  WM_SYSCOPYDATA was already preserved) and the three M52 keyboard
  pages (ms902150 KEY_STATE_FLAGS, ms927178 Virtual-Key Codes,
  aa452679 Manufacturer-specific Virtual-Key Codes) and the 82 M53
  Standard Shell Reference pages
  (`tools/manifests/stdshell.manifest`).
 * `pages6/`: 1259 CE 6.0 `(v=winembedded.60)` pages — the twins of the
  CE 5.0 corpus (1133, every resolvable leaf; the index pages have no
  CE 6.0 leaf) plus the M34a twins ee483142 / ee491122, the M44
  CE 6.0 twins, the M46 IMM constant twins (ee490906 / ee491772 /
  ee491563 / ee492116 / ee491945 / ee491174 / ee491913 / ee491163 /
  ee491938 / ee491940), the 63 M50 AYGShell twins
  (`tools/manifests/aygshell-ce60.manifest`; INewMenuItemServer and
  IShellNotificationCallback have no CE 6.0 leaf) plus the twin
  dependency pages ee499390 / ee501447, the 14 M51 SIP twins
  (`tools/manifests/sip-ce60.manifest`; the four interface roots have
  no CE 6.0 leaf under those titles), and the two CE 6.0
  architecture/kernel pages read for docs/ce-not-nt.md (ee504804
  Windows CE OS model, ee482762 Kernel Servers: CE 5.0 vs CE 6.0)
  and the three M53 pages (ee504556 SHGNO + ee505480 SHFILEOPSTRUCT
  twins grounding the held-value analysis, and ee503202
  SHRecognizeGesture -- the CE 6.0 R3 page Learn consolidated into
  its Compact 2013 revision;
  `tools/manifests/stdshell6.manifest`).
* `pages4/`: **6468 Windows CE .NET `(v=msdn.10)` pages — the full
  earliest-complete CE tree, read end-to-end in M34**
  (see `docs/cenet-readout.md`).  One catalog leaf,
  `dd320882(v=vs.100)` "IsValidPtrIn", is a foreign Visual Studio page
  cross-linked by the archived TOC: its CE URL is a verified 404 and
  it is excluded; one preserved page (ms938306) is the archive's
  `#message` sign-in-gated stub, kept as published.
* `rows.json`: 2233 CE 5.0 Requirement-row records (1560 pre-M45 +
  the 89 M45 TAPI client function pages + the 152 M46 IMM reference
  pages + the 51 M47 crypto base-CSP pages + the 181 M48/M49 crypto
  certificate/PFX + smart-card pages, counting 4 struct pages already
  cached in M47 only once + the 66 M50 AYGShell + dependency pages +
  the 48 new M51 SIP book rows and the aa453870 WM_IM_INFO row (the
  SIPINFO and WM_SYSCOPYDATA pages were already preserved) + the 3 M52
  keyboard pages) + the 82 M53 Standard Shell Reference rows;
  `rows4.json` (in `build/`, regenerable
  via `tools/cenet-rows.py`) holds the CE .NET parsed records.
  The 65 M50 CE 6.0 twin pages are preserved in `pages6/` but keep no
  records in `rows.json` (the CE 6.0 Requirements tables are shaped
  differently and are parsed by `build/twin_cmp.py` for cross-checks
  only; see docs/inventory.md M50).
* M48/M49 harvest (cert/encode/PFX + smart card): manifests
  `crypt-cert.manifest` (54), `crypt-encode-pfx.manifest` (29),
  `crypt-structs.manifest` (71; BLOB/CMSG_STREAM_INFO/VTableProvStruc/
  CERT_INFO already harvested) and `smartcard.manifest` (31); plus two
  preserved architecture pages in pages5 (ms905093 Windows CE
  Architecture, ms905342 Overview of Windows CE Development) backing
  docs/ce-not-nt.md.  These 181 pages were re-fetched and pushed in
  the M50 session (the M48/M49 corpus push had not landed; the
  wince-api docs counts had been written ahead of it).
* M50 harvest (AYGShell): `aygshell.manifest` (62 CE 5.0 leaves of
  the AYGShell Reference book, book root ms907090) + 5 dependency
  pages; the 63 CE 6.0 twins by exact-title match live in
  `aygshell-ce60.manifest`.  Parser: `tools/ce-fetch.py` Requirements
  fix for the "Library:"/"Link Library:" label alternation,
  `&nbsp;` entities and the Windows Mobile sub-table boundary
  (WM-subsection rows are stored in the record's `wm` field, not
  `lib`); zero impact on non-AYGShell pages.
* M47 parser fix: `tools/ce-fetch.py` now parses Requirements fields
  whose colon sits outside the label tag (`<strong>OS Versions</strong>:`);
  the whole cached corpus was re-parsed, which corrected 4 CryptMsg*
  records (ms938247/ms938251/ms938271/ms938279) plus 2 earlier rows.
* Catalog caveats: the CE 6.0 catalog stores ids with the
  `(v=winembedded.60)` suffix (strip it before fetching); the CE .NET
  catalog is `(v=msdn.10)` except the single foreign `(v=vs.100)`
  row.  Rate limiting: the Learn CDN returns HTTP 429 after ~1000
  rapid requests; harvest in bursts (~550 at 6 parallel) with pauses
  (see docs/cenet-readout.md).
