# CE 5.0 documented reference surface (census)

Counts are leaf pages under every official book whose title ends in
"Reference", computed from the Learn previous-versions TOC
(`https://learn.microsoft.com/en-us/previous-versions/windows/embedded/toc.json`,
the same official index `tools/ce-manifest.py` walks).  The counts
include concept pages, how-to pages and Platform Builder/IDE/driver
material; the *user-mode API* pages (functions/structures/constants
that carry a Requirements row) are a smaller subset that
`tools/ce-fetch.py` records into `build/rows.json`.  This file exists
so the target is understood as a finite, documented CE 5.0 surface —
not "a fraction of desktop w32api".

## Windows CE 5.0 Product Documentation — reference books by feature area

| Area (under Windows CE Features) | books | reference pages |
|---|---|---|
| Shell and User Interface | 65 | 4080 |
| Applications and Services Development | 17 | 2818 |
| Graphics and Multimedia Technologies | 13 | 2360 |
| Communication Services and Networking | 43 | 2186 |
| File Systems and Data Store | 19 | 848 |
| Core OS Services | 18 | 787 |
| Voice over IP Phone Services | 4 | 504 |
| Internet Client Services | 11 | 454 |
| International | 10 | 376 |
| Security | 6 | 311 |
| Applications - End User | 3 | 288 |
| Device Management | 2 | 164 |
| Windows CE Error Reporting | 2 | 44 |
| Fonts | 1 | 32 |
| SideShow | 1 | 42 |

Non-application material (BSP bring-up, drivers, Platform Builder,
test kit, C run-time docs, safe-string docs) adds the remaining
reference books of the Product Documentation; the full product
documentation totals ~19.8k reference leaves.

## Progress markers (update as batches land)

* `build/rows.json` pages harvested with Requirements rows: 666
  manifest lines parsed across all current manifests (page corpus
  re-fetched each session into the non-committed `build/`; see
  docs/version-coverage.md).  Core OS Reference user-mode books landed
  through the Exception / Debugging / Serial / Message Queue / CeLog /
  NAT / Error Values books; the Feature-area reference books are now
  open with the GWES window-manager core (Windows/Class/Property/
  Timer/Caret/Atom/Message-Queue/Keyboard/Scroll, 156 pages: M26);
  GDI, control (Combo/List/Edit/Buttons), Shell, resources and the
  network/comms reference books remain as the backlog.
* Shipped declarations: see `make check` / `def/coredll-doc.def`
  (name-only doc-derived exports, one per harvested Link-Library row
  whose export is declared by these headers).
* Every shipped item maps to an official page ID recorded in
  `docs/inventory.md`; every inventory row derives from the page's
  Requirements (OS Versions / Header / Link Library).
