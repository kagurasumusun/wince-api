# API-surface coverage audit (M62)

Quantified against the official Microsoft Learn "Windows CE 5.0
Product Documentation" table of contents (toc.json, 13,458 embedded
leaves under *Windows CE Features*; 22,889 under the full CE 5.0
tree).  "have" = pages preserved in the harvested corpus
(wince-docs-corpus, pages5 tree).

## Book-level coverage (Windows CE Features, 13,859 reference leaves)

| Features book | leaves | have | % |
|---|---|---|---|
| Graphics and Multimedia Technologies | 2935 | 130 | 4% |
| Shell and User Interface | 2407 | 1687 | 70% |
| Communication Services and Networking | 2331 | 3078 | 99%+ |
| Applications and Services Development | 2160 | 114 | 5% |
| Voice over IP Phone Services | 639 | 0 | 0% |
| Internet Client Services | 607 | 246 | 40% |
| International | 547 | 194 | 35% |
| Core OS Services | 522 | 359 | 68% |
| File Systems and Data Store | 500 | 68 | 13% |
| Security | 444 | 232 | 52% |
| Applications - End User | 377 | 92 | 24% |
| Device Management | 237 | 49 | 20% |
| Fonts | 67 | 29 | 43% |
| SideShow | 48 | 0 | 0% |
| Windows CE Error Reporting | 38 | 0 | 0% |
| **Total (Features)** | **13859** | **3643** | **26%** |

## Largest uncovered application-API books (queue for M63+)

| Book (path) | leaves | status |
|---|---|---|
| Media > DirectShow | 1680 | 0% |
| Applications and Services > Component Services (COM and DCOM) | 896 | 0%* |
| Graphics > Direct3D Mobile | 360 | 0% |
| Applications and Services > Speech API (SAPI) 5.0 | 431 | 0% |
| Applications and Services > XML Core Services (MSXML) | 429 | 0% |
| VoIP > Real-time Communications (RTC) Client API | 421 | M69 (cached) |
| Communication > Servers | 810 | 0% (server/admin + DDI) |
| Communication > Networking - General | 790 | M77/M78 (harvested) |
| Audio > Waveform Audio | 124 | M63 (harvested) |
| Graphics > Imaging | 105 | 0% |
| Applications and Services > Pocket Outlook Object Model | 71 | 0% |
| File Systems and Data Store Reference | 294 | M78 (harvested, impl pending) |
| Device Management Client | 149 | 0% |

\* the COM/OLE/Objbase surface itself is landed (M44 objbase.h,
635 pages harvested from the COM reference set); the 896-leaf book
contains the DCOM/admin/ActiveX-template and additional reference
leaves not yet triaged.

## Known non-documentable items (cannot be confirmed in official docs)

* **Ordinals**: no CE documentation page publishes DLL ordinal
  numbers; import defs stay name-only (dlltool resolves by name at
  static-link time).  Ordinal-based binding cannot be grounded.
* **DDARGB layout, ZONEATTRIBUTES / MAX_* array lengths, held
  DD* / INET_E_* / URLACTION_* / URLPOLICY_* values**: names only on
  CE pages; no official page publishes the values/layout.

## Plan (M63 - M70)

* M63 Waveform Audio (Mmsystem.h, 124 leaves) - header + coredll def
  additions.
* M64 Imaging API (imaging.h, 105 leaves).
* M65 Pocket Outlook Object Model (pimstore.h, 71 leaves).
* M66 XML Core Services (msxml.h, 429 leaves).
* M67+ Direct3D Mobile (d3dm*.h, 360 leaves), SAPI 5.0 (sapi.h, 431),
  RTC Client (rtccore.h, 421), DirectShow (1680, sliced), CEDB
  remainder -- in that order of application-API value.
* CE 4.x / 6.0 struct-difference sweep (twins already harvested for
  ddraw/cc/m57 batches; extend to new units), compat-macro sweep,
  and the common-HRESULT constant closure (official desktop
  "Common HRESULT Values" page, M52 fixed-ABI reference permission).

## Coverage refresh (M78a; prior refresh M71 post-M71c)

Same methodology as the M62 audit (Features leaves of the official
CE 5.0 toc.json vs pages preserved in build/pages, the corpus
pages5 tree; twin pages in pages6/pages4 are verification material
and are not counted).  Harvests since M62: MSXML (M67 area), SAPI (M68), RTC (M69),
CEDB/EDB Database Reference (M70), DirectShow data surface
(M70b), DirectShow Interfaces (M71b), DMO Reference (M71c),
Servers + NetGen (M75-M77), NDIS Network Driver Reference
(M78, 779), FSD remainder (M78, 120), VAIL/PC-Auth/TUI (M78,
254), plus the earlier D3DM/mmsystem/imaging batches.

| Features book | leaves | have | % |
|---|---|---|---|
| Graphics and Multimedia Technologies | 2935 | 2204 | 75% |
| Shell and User Interface | 2407 | 1687 | 70% |
| Communication Services and Networking | 2331 | 3078 | 99%+ |
| Applications and Services Development | 2160 | 1052 | 48% |
| Voice over IP Phone Services | 639 | 675 | 99%+ |
| Internet Client Services | 607 | 246 | 40% |
| International | 547 | 194 | 35% |
| Core OS Services | 522 | 359 | 68% |
| File Systems and Data Store | 500 | 286 | 57% |
| Security | 444 | 232 | 52% |
| Applications - End User | 377 | 92 | 24% |
| Device Management | 237 | 49 | 20% |
| Fonts | 67 | 29 | 43% |
| SideShow | 48 | 0 | 0% |
| Windows CE Error Reporting | 38 | 0 | 0% |
| **Total (Features)** | **13859** | **10183** | **74%** |

Movement since M62: total 26% -> 74% (+6540 pages).  "99%+" books:
the harvested manifest page count exceeds the M62 leaf estimate
(harvests include book-index/overview pages beyond the counted
reference leaves).

M98 status: one-pass finish complete.  Whole-corpus close-out
(M98a-M98e): every documented API row in build/rows.json (18139)
is now carried somewhere in include/ -- raw-text gap count 0.
The carried-everywhere measure includes 625 name-only rows (OID_/
CEL_/WIDM_/ACMDM_/WPDM_/IOCTL_/PFN_/Usbdi LP_/AVC_VCR_CMD_/Tapi
LINE_* etc.) recorded as held-ledger comments (documented name
with no published value), plus 13 template/placeholder rows
(XXX_ stream driver template ms923695-705 -> Streams.h;
CGenericList Add*I ms937581-87 -> Dshow.h) recorded manually.
New headers M98: Cardserv.h, Cardsv2.h, Socksv2.h, Tuple.h
(drivers-pccard) plus Streams.h, Dshow.h.  R1 value adoption
landed for Imm.h (198 defines; 24 IMC_* names via page-harvested
names fed to the R1 resolver), Mmsystem.h (15), Msacmdrv.h (4),
Winuser.h (210).  Imm/Mmsystem/Msacmdrv/Winuser adoption and the
250-group held-ledger re-sweep are commits M98d e122b6b /
M98e d4b4bfb.

M78/M90 paragraphs retained for history: NDIS landed M78-M78c;
Graphics 731 / DCOM 896 / File Systems DDI / Core OS DDI /
Internet Client / Apps-EndUser / Security / Shell / Device Mgmt
all closed by M98 (see inventory.md M98 close-out table).

## Surface-completion measures (M98; script tools/surface-metrics.py)

The user-visible completion problem ("only 30%") is measured here
along three axes from build/rows.json (18139 harvested rows of the
official CE documentation) against the shipped include/ headers.
Method is fixed in tools/surface-metrics.py (checked in, rerunnable).

| Measure | M83 | M98 |
|---|---|---|
| Documentation rows harvested | 14959 | 18139 |
| Function rows (sig parses `ret title(...)`) | 2666 | 3195 |
| ... declared via AKARI_CE_NAME | 2009 (75%) | 2185 (68%) |
| Other symbol rows (types/constants/messages) | 4635 | 5481 |
| ... name present verbatim in include/ | 3160 (68%) | 5410 (99%) |
| Documented header tokens | 159 | 248 |
| ... shipped in include/ | 158 (99%) | 247 (99%) |
| Corpus pages preserved | 22727 | 25905 |

The AKARI_CE_NAME share fell 75% -> 68% only because the row
denominator grew (whole-corpus harvest added DDI/provider-side
signatures that ship as plain prototypes or held records, not
AKARI_CE_NAME-API declarations); it is not a regression.  The
other-symbol axis -- the one behind the original "only 30%" report
-- moved 68% -> 99%: M98e's held-ledger close-out carries every
documented name (raw-text gap count 0).  The single unshipped
header token is interned.h -- the "Interned.h .h" archive-typo
rows (aa451906 BeforeWindowOpen, aa452134 Count, aa452193 Event;
the popup-events records are carried in webvw.h; inventory.md M98
residue list, no alias file per the M76a one-file policy).

Unshipped header tokens: the M89 residue dvddata.h (archive typo
for Dvdata.h, IDVDROM::Bind/Unbind pages) cleared during the M98
whole-corpus sweeps (the token normalises away once every citing
row is carried); the current single residue is interned.h above.
The M83 list of 9 closed as: msime/msimeui/koreanimeui/imjpskin
(M84, IME remainder -- 2 factory fns declared, 3 interfaces + 4 C++
classes recorded, 4 structs compiled, 1 held), dinput/dmoimpl/bt_ddi/
bthid/cesync (M85, records/alias; Cesync.h aliases Objbase.h which
already carried STOREINFO (COM) since M73b).

Book-level table above: all books now read 99%+ / done after the
M98 one-pass finish (every manifest harvested to 100% and every
row carried; see the inventory.md M98 close-out table for the
per-book final states).

Priority gaps for M98 close-out (was "M84+"; all closed or
reclassified):
1. Header-name compat gaps: CLOSED -- single residue interned.h
   (archive typo, above).
2. Missing ordinals: none published by CE docs for the new libs
   (def files are name-only by policy).  CLOSED.
3. CE4/5/6 struct differences: swept at M98 close-out via
   docs/ce6-twins.tsv (1175 title-matched CE5->CE6 pairs):
   35 pairs had a compiled structure citing the CE5 page; 34
   identical, 1 apparent difference (GET_FILEEX_INFO_LEVELS
   ms890917 -> ee489792) that is already documented in Winbase.h
   (CE5 FindFirstFileEx page prints FindExInfoStandard /
   FindExInfoMaxInfoLevel; the levels page and the CE6 twin print
   GetFileExInfoStandard; both spellings carried in one enum
   since M87).  Net CE5-vs-CE6 struct mismatches: 0.  The twins
   table predates the M98 harvest; CE6 twins for the M98 driver
   books would need a CE6 TOC pass (future work, noted).
4. Undefined constants / compat macros / Clang-needed types:
   standing held list (HRC, ALC, RVA, ULONG32/64, OAHWND &c.) is
   the recorded backlog of unpublished-but-needed types -- still
   open by nature (nothing more is published in the sources).
5. Graphics 731 remainder, DCOM 896 triage, Core OS DDI books:
   CLOSED by M87-M98 (see inventory.md M98 close-out table).
