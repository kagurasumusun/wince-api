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

## Current corpus (2026-09-08, M45)

* `pages5/`: 1568 CE 5.0 `(v=msdn.10)` pages — the full committed
  manifest set (81 manifests incl. the M43 TAPI/TSPI manifests and
  the M45 `tapi-client-functions.manifest`, 89 pages harvested in
  M45) plus the M34a type/callback pages (aa450831
  EXTENDED_NAME_FORMAT, ms904723 EnumCodePagesProc).
* `pages6/`: 1170 CE 6.0 `(v=winembedded.60)` pages — the twins of the
  CE 5.0 corpus (1133, every resolvable leaf; the index pages have no
  CE 6.0 leaf) plus the M34a twins ee483142 / ee491122 and the M44
  CE 6.0 twins.
* `pages4/`: **6468 Windows CE .NET `(v=msdn.10)` pages — the full
  earliest-complete CE tree, read end-to-end in M34**
  (see `docs/cenet-readout.md`).  One catalog leaf,
  `dd320882(v=vs.100)` "IsValidPtrIn", is a foreign Visual Studio page
  cross-linked by the archived TOC: its CE URL is a verified 404 and
  it is excluded; one preserved page (ms938306) is the archive's
  `#message` sign-in-gated stub, kept as published.
* `rows.json`: 1649 CE 5.0 Requirement-row records (1560 pre-M45 +
  the 89 M45 TAPI client function pages); `rows4.json` (in
  `build/`, regenerable via `tools/cenet-rows.py`) holds the CE
  .NET parsed records.
* Catalog caveats: the CE 6.0 catalog stores ids with the
  `(v=winembedded.60)` suffix (strip it before fetching); the CE .NET
  catalog is `(v=msdn.10)` except the single foreign `(v=vs.100)`
  row.  Rate limiting: the Learn CDN returns HTTP 429 after ~1000
  rapid requests; harvest in bursts (~550 at 6 parallel) with pauses
  (see docs/cenet-readout.md).
