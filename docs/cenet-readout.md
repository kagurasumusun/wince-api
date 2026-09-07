# Windows CE .NET archive readout (M34)

The Windows CE .NET tree (`tools/catalogs/catalog-windows-ce-net.tsv`,
6,363 leaf rows) is the **earliest complete CE documentation published
in the Learn archive**: it documents Windows CE .NET 4.0–4.2 and, via
its Requirement rows, the whole CE 1.0 → CE .NET 4.2 span (the pages
carry "Windows CE 1.0 and later", "Windows CE 2.0 and later", …,
"Windows CE .NET 4.2 and later" rows).  This milestone read the tree
**in full** (every leaf page saved, pushed to the page-corpus
repository, and reconciled against the CE 5.0 / CE 6.0 trees).

## 1. Harvest result

* Catalog snapshot: 6,363 leaf rows, 6,362 unique ids, all
  `(v=msdn.10)`.
* Two snapshot anomalies, both recorded (not silent):
  1. `dd320882(v=vs.100)` "IsValidPtrIn" is a **foreign** leaf — a
     Visual Studio reference that the archived TOC cross-links inside
     the CE .NET subtree.  Its CE URL is a verified HTTP 404; it is
     excluded from the CE .NET page corpus.
  2. one catalog row duplicates an id (snapshot artifact; harmless).
* CE .NET leaves harvested and preserved: **6,361 / 6,361** (100%).
  One preserved page (`ms938306`) is literally titled `#message` in
  the archived TOC and serves the sign-in-gated stub; it is kept as
  published.
* Preserved in the page-corpus repository as `pages4/`; working copy
  `build/pages4/` (deleted at end of the session per the workflow).

Fetch notes recorded for the next big tree: the Learn CDN rate-limits
bursts with HTTP 429 after roughly a thousand rapid requests; the
working pattern is bursts of ~550 pages at 6 parallel workers with a
150 s pause between bursts (0 throttling observed across all 12
bursts), plus a 404 retry list.  Catalog ids must be fetched with the
tag they carry (one row is not `(v=msdn.10)`).

## 2. Parsed records (`build/rows4.json`, regenerable)

| set | count |
|---|---|
| every CE .NET leaf, parsed | 6,361 |
| with a Requirements/OS/Header/Library row | 4,030 |
| with a documented prototype (sig) | 1,709 |

OS-span rows carried by these pages (evidence for CE 1.0–4.x):

| OS span | pages |
|---|---|
| Windows CE 1.0 and later | 207 |
| Windows CE 1.01 and later | 28 |
| Windows CE 2.0 and later | 547 |
| Windows CE 2.10 and later | 190 |
| Windows CE 2.12 and later | 176 |
| Windows CE 3.0 and later | 772 |
| Windows CE 3.1 and later | 2 |
| Windows CE .NET 4.0 and later | 1,918 |
| Windows CE .NET 4.1 and later | 110 |
| Windows CE .NET 4.2 and later | 69 |
| (no OS row — concepts/PB/driver/IDE) | 2,331 |

## 3. What the tree actually documents

Unlike the CE 5.0 tree (which carries the base Win32-style API
reference: LocalAlloc, CreateThread, …), the CE .NET archive
documents the CE 1.0–4.2 **component and add-on API layer** plus
Platform Builder / driver / compiler material:

| Link-Library / module row | pages | signature pages by Header |
|---|---|---|
| Coredll.lib | 318 | oleauto.h 217, wincrypt.h 105, winsock2.h 46, windows.h 38, winnls.h 31 |
| OLE/COM/Automation (ole32/oleaut32/uuid, urlmon, mlang) | ~880 | objbase.h 85, urlmon.h 37 |
| Multimedia (DirectDraw ddraw, DirectSound dsound, DMO dmoguid, mstsax, ddvdids) | ~370 | |
| Security/crypto (crypt32, winscard, wldap32, snmpapi) | ~190 | winldap.h 44, snmp.h 29 |
| Networking (ws2 winsock, TAPI tapi/tapicomn, mstsax) | ~180 | tapi.h 91, winsock2.h 46 |
| Bluetooth (btdrt.lib; bt_api.h) | 82 | bt_api.h 46 |
| Input Method (coreimm.lib; imm.h) | 55 | imm.h 56 |
| OEM/driver (ceddk, blcommon, kitl, nk) | ~95 | ceddk.h 33 |
| compiler intrinsics (armintr/mipsintr/shintr/cmnintrin) | ~280 | |
| (no lib row) | 3,866 | |

## 4. Cross-tree reconciliation (name-based union)

Same API → independent page per tree; the name-based union is the
reconciliation key.  For the 1,674 CE .NET signature leaves with a
plain-identifier title:

* **1,373 also exist in both** the CE 5.0 (`(v=msdn.10)`) and CE 6.0
  (`(v=winembedded.60)`) catalogs by exact title,
* 42 CE 5.0-only, 6 CE 6.0-only,
* 253 neither — almost all CE-compiler intrinsics (`_abs_ps`, …) and
  CE .NET-only component functions.

Example union rows (catalog ids) for the M34a implemented names:

| name | CE .NET | CE 5.0 | CE 6.0 |
|---|---|---|---|
| LCMapString | ms921462 | ms906221 | ee491201 |
| FoldString | ms919269 | ms905209 | ee491930 |
| EnumSystemCodePages | ms919231 | ms905062 | ee491962 |
| EnumCodePagesProc | ms919189 | ms904723 | ee491122 |
| GetUserNameEx | ms902915 | aa517595 | ee489621 |
| EXTENDED_NAME_FORMAT | ms902883 | aa450831 | ee483142 |

## 5. Gap numbers (the honest scale)

* Of the 304 distinct Coredll.lib function names documented on CE .NET
  signature pages, 23 were already declared in wince-api headers at
  M34a; the rest are the backlog (most have CE 5.0/CE 6.0 twins that
  are the canonical implementation basis, harvested per batch in the
  CE 5.0 book ladder).
* The CE .NET tree adds ~880 OLE/COM, ~370 multimedia, ~190
  security/network helper and 82 Bluetooth reference leaves that are
  outside the CE 5.0 Core/GWES books opened so far — each is a future
  header unit with full provenance now in the corpus.
