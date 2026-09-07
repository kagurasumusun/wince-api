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

## Current corpus (2026-09-08)

* `pages5/`: 1175 CE 5.0 pages (the full committed manifest set —
  69 manifests, every harvest through M30).
* `pages6/`: **1133 CE 6.0 twins** of the full harvested CE 5.0
  corpus (every resolvable leaf; the CE 5.0 index pages have no CE 6.0
  leaf).  Reconciliation: `docs/ce6-reconciliation.md`; twin map
  `docs/ce6-twins.tsv`.
* `rows.json`: 1175 Requirement-row records.
* CE 6.0 fetch URL form: `https://learn.microsoft.com/.../previous-versions/
  windows/embedded/<id>(v=winembedded.60)` (the official catalog stores
  the id *with* the `(v=winembedded.60)` suffix; strip it before
  building the URL).

New trees (CE .NET `(v=msdn.10)` API leaves) will be added as
`pages4/` when those books are opened (see `docs/ce-api-census.md` /
`docs/version-coverage.md` for the per-version tree sizes).
