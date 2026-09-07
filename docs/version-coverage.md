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
* Harvested with Requirement rows in `build/rows.json` (each page read
  once): 203 (10 Core OS books) → **337** after the Exception /
  Message-Queue pages were added (two batches this session).
* Declared exports in the shipped headers: 215 across all def files;
  `def/coredll-doc.def` alone lists 164 name-only exports, every one
  traced to an official Link-Library row in `docs/inventory.md`.

## 4. Staged backlog (CE 5.0 Core OS Reference, remaining user-mode books)

Manifests already written (page ids only), not yet implemented:

    tools/manifests/core-msgqueue-reference.manifest    10 leaves  (landed M22)
    tools/manifests/core-exception-reference.manifest   9 leaves  (SEH/raise set)
    tools/manifests/core-debugging-reference.manifest  32 leaves  (debug API + macros)
    tools/manifests/core-serial-reference.manifest     22 leaves  (DCB/COMM* …)

Follow-on books (manifests to generate from the same TOC): Error
Values (13), State and Notifications Broker (12), Network Address
Translation (20).  Feature-area books (GWES/GDI/Shell/….) come after the
Core OS Reference is complete; each is a new manifest + batches.

## 5. Notes for future sessions

* Page caching is per bare id under `build/pages/`.  Later-version
  trees can reuse the *same* numeric id with different `(v=…)` tags
  (e.g. `ee488787(v=winembedded.60)` vs `(v=winembedded.80)`), so a
  cross-version harvest must key its cache by tag as well as id.
* Fetching every leaf of every tree (~90k pages) at ~1 s/page is a
  multi-hour grind and Learn rate-limits burst requests; batch work is
  per-book, and the CE 5.0 ladder plus name-based twins above is the
  reconciliation method.
