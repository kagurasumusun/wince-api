# Windows CE documentation across versions 1.0–6.0 (coverage census)

Scope question asked repeatedly: "load every MSDN/learn page for
Windows CE 1–6 without omission and reconcile fully."  This file
records what the official Learn archive actually publishes per CE
version, what was downloaded, and how the reconciliation is driven.
Everything below is transcribed from the official index
`https://learn.microsoft.com/en-us/previous-versions/windows/embedded/toc.json`
(the same official TOC `tools/ce-manifest.py` and
`tools/ce-versions.py` walk) and from pages of that archive.

## 1. Official trees published per CE version (leaf-page counts)

Under the "Windows Embedded Compact" subtree of the Learn archive the
CE-era product documentations exist as **separate per-version trees**:

| Product tree in the archive | leaves | href family | notes |
|---|---|---|---|
| Windows CE 2.1 | 1 | `(v=winembedded.21)` | stub only, no API reference |
| Windows CE 3.0 | 1 | `(v=winembedded.0)` | stub only, no API reference |
| Windows CE .NET (4.0–4.2 docs) | 6,363 | `(v=msdn.10)` | earliest **complete** archive; pages carry Requirements "Windows CE 1.0 and later" … "CE .NET x.x" |
| Windows CE 5.0 | 22,918 | `(v=msdn.10)` | the set implemented book-by-book here |
| Windows Embedded CE 6.0 | 23,760 | `(v=winembedded.60)` | same API corpus re-published with new ids (`ee…`, `bb…`) |
| Windows Embedded Compact 7 | 20,286 | `(v=winembedded.70)` | beyond CE 6; listed for completeness |
| Windows Embedded Compact 2013 | 16,863 | `(v=winembedded.80)` | beyond CE 6; listed for completeness |

Windows CE 1.0 / 2.0 / 2.1x / 3.0 full documentation was **never
republished on Learn**; their API availability survives only as the
"OS Versions: Windows CE x.0 and later" Requirement rows carried on
the CE .NET / CE 5.0 pages.  CE 2.1 and CE 3.0 exist in the archive as
single landing stubs.

Snapshot artifacts (generated from the official TOC, all page ids +
titles, one line per leaf):

    tools/catalogs/catalog-windows-ce-net.tsv             (6,363 leaves)
    tools/catalogs/catalog-windows-ce-50.tsv             (22,918 leaves)
    tools/catalogs/catalog-windows-embedded-ce-60.tsv    (23,760 leaves)
    tools/catalogs/books-<tree>.tsv                       (book -> leaves)

`tools/ce-versions.py` regenerates them; `tools/ce-fetch.py` now
accepts full ids like `ee504802(v=winembedded.60)` (it reads the
`(v=…)` tag from the id instead of assuming `msdn.10`).

## 2. Same API, different page ids per version

The version trees **do not share page ids**: the same function has an
independent page in each archive (e.g. CloseMsgQueue: `ms885168`
(CE 5.0), `ee488787(v=winembedded.60)` (CE 6.0), plus a CE .NET twin).
"Complete reconciliation" therefore means a **name-based** union across
trees: for each API name, read every version's page and fold the
differences (earlier archive documents older semantics; the newest page
documents the OS-version span last).  Per-book CE 5.0 manifests are the
primary ladder; each batch records the twin ids it finds (see the M22
inventory row for the CE 6.0 twins).

## 3. Where the work stands (percentages, honestly)

"0.0001%" is not a meaningful unit for this corpus.  Concrete numbers:

* Total CE-era leaves the archive publishes: ~90k (CE .NET … Compact
  2013).  Most are concept / Platform Builder / driver / CETK pages —
  not user-mode API facts.
* User-mode API *reference* leaves (functions / structures / enums /
  constants with a Requirements row) are the implementable subset.
  Windows CE 5.0 "Core OS Reference" alone has 340 leaves across 17
  books; the Feature-area reference books (GWES, GDI, shell, …
  ~15–20k reference leaves) are still largely un-harvested.
* Pages harvested into `build/rows.json` (each page read once): 203
  (Core OS Reference books) → **827** after the GWES window-manager
  books (M26, 156 leaves) and the full **GDI Reference** book
  (M27: 132 GDI Functions + 29 GDI Structures, 161 leaves) were added,
  then → **939** with the M28 window-control function layer
  (Menus/Dialog Boxes/Buttons/Clipboards/Printing/Resources/System
  Information functions and structures + Notify Reference + the
  owner-draw/icon support structures, 112 leaf pages), then → **1175**
  with M29 (Image List Reference book + GWES message/notification
  constant units), which re-fetched the full committed CE 5.0 manifest
  set (69 manifests) and regenerated `build/rows.json` from scratch —
  the 236-row delta includes the Combo/List/Edit message and style
  book leaves harvested for the first time.
  Every page is an official `(v=msdn.10)` CE 5.0 page; GDI, M28 and
  M29 (Image List) function signatures were additionally recovered
  from the official CE 6.0 `(v=winembedded.60)` twins of the same
  books.
* Declared exports in the shipped headers: **626** name-only exports
  across 33 def files; `def/coredll-doc.def` lists 364 and
  `def/coreloc-doc.def` 33, every one traced to an official
  Link-Library row in `docs/inventory.md`.  M33 added COPYDATASTRUCT
  (struct-only) and M34a added the NLS string-mapping /
  directory-service user-name batch (LCMapStringW, FoldStringW,
  EnumSystemCodePagesW -> coreloc 33; GetUserNameExW -> coredll 364).
## 4. Staged backlog (CE 5.0 Core OS Reference, remaining user-mode books)

Feature-area GWES/GDI books opened in M26–M28.  The window-manager
slice of the GWES Reference is implemented with **14 manifests**
(`tools/manifests/gwes-*.manifest`, 156 CE 5.0 leaves): Windows
Functions (35) / Window Class (8) / Window Properties (5) / Windows
Timer (4) / Carets (8) / Atoms (3) / Message Queue (16) / Message
Synchronization (2) / Keyboard Functions (30) / Keyboard Structures
(5) / Scroll Bars (6) / Windows Structures (6) / Windows Messages
(14) / Keyboard Messages (14).  The full **GDI Reference** book is
implemented (M27; `tools/manifests/gdi-*.manifest`, 161 leaves) with
every signature recovered from the CE 6.0 `(v=winembedded.60)` twin
pages (the CE 5.0 `(v=msdn.10)` migration strips whitespace inside
prototypes).  **M28** landed the window-control *function* layer:
Menus Functions/Structures, Dialog Boxes Functions/Structures,
Buttons Functions, Clipboards Functions, Printing Functions/
Structures, Resources Functions/Macro, System Information
Functions/Structures, Notify Functions/Structures, the Combo Boxes /
List Boxes owner-draw structures (DRAWITEMSTRUCT etc.) and ICONINFO —
112 leaves across 16 book manifests (all regenerated by
`tools/ce-gwes-manifest.py` over the official TOC; totals cross-check
against `tools/catalogs/books-windows-ce-50.tsv`).

Remaining GWES ladder: the *message/notification constant* books not
yet transcribed -- Control Styles 21, Window and Message Box Styles 3
(harvested leaves; numeric block is a follow-on like M26's was) --
plus the network/comms books; each book = new manifest + batches,
with CE6 twins used where a CE5 leaf is a stub (e.g. SCROLLINFO
`ee504371`).  Landed in M29: the Image-List book (Functions 32 /
Macros 4 / Structures 2), the Buttons/Static/Menus/Dialog/Clipboard/
GDI message books, the numeric transcription of the Windows/Keyboard
message books, and the Combo/List/Edit message and notification
identifier transcription (CB_*/CBN_*, LB_*/LBN_*, EM_*/EN_*).  The CE 5.0
archive currently lives three levels deep in the Learn TOC
(`Mobile and Embedded Development / Windows Embedded / Windows
Embedded Compact / Windows CE 5.0`), which `tools/ce-manifest.py`
and `tools/ce-gwes-manifest.py` locate by title search so the
generators do not depend on the exact nesting.

## 5. Notes for future sessions

* Page caching is per bare id under `build/pages/`.  Later-version
  trees can reuse the *same* numeric id with different `(v=…)` tags
  (e.g. `ee488787(v=winembedded.60)` vs `(v=winembedded.80)`), so a
  cross-version harvest must key its cache by tag as well as id.
* Fetching every leaf of every tree (~90k pages) at ~1 s/page is a
  multi-hour grind and Learn rate-limits burst requests; batch work is
  per-book, and the CE 5.0 ladder plus name-based twins above is the
  reconciliation method.

## M34 status (CE .NET tree + cross-tree union)

* The **Windows CE .NET tree is read in full**: 6,361 of its 6,363
  catalog leaves harvested and preserved (`docs/cenet-readout.md`,
  corpus `pages4/`).  One catalog leaf is foreign
  (`dd320882(v=vs.100)`, a Visual Studio page cross-linked in the
  archived TOC; CE URL verified 404); one preserved page (ms938306) is
  the archive's `#message` sign-in-gated stub.
* 4,030 of the CE .NET leaves carry a Requirements/OS/Header/Library
  row; 1,709 document a prototype.  These pages are the OS-span
  evidence for CE 1.0 -> CE .NET 4.2 (1.0: 207 pages, 2.0: 547,
  2.10: 190, 2.12: 176, 3.0: 772, .NET 4.0: 1918, ...).
* The CE .NET tree is component/add-on API material (OLE/COM ~880
  leaves, multimedia ~370, security/network ~190, Bluetooth 82,
  Coredll.lib function pages 318, coreimm 55, winsock2/tapi/ldap/snmp/
  winscard) plus Platform Builder / driver / IDE / compiler-intrinsic
  pages -- the base Win32-style reference lives in the CE 5.0 tree.
* Name-based union across the three trees (same API, independent page
  per version) is the reconciliation key: 1,373 of 1,674 CE .NET
  signature leaves with plain-identifier titles exist in both the CE
  5.0 and CE 6.0 catalogs by exact title (see the union table in
  docs/cenet-readout.md for the M34a names).
