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
| Communication Services and Networking | 2331 | 443 | 19% |
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
| VoIP > Real-time Communications (RTC) Client API | 421 | 0% |
| Communication > Servers | 810 | 0% (server/admin + DDI) |
| Communication > Networking - General | 790 | 0% (mostly NDIS DDI) |
| Audio > Waveform Audio | 124 | M63 (harvested) |
| Graphics > Imaging | 105 | 0% |
| Applications and Services > Pocket Outlook Object Model | 71 | 0% |
| File Systems and Data Store Reference | 294 | 23% (CEDB remainder) |
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

## M71 refresh (post M69/M70/M70b/M71a/M71b/M71c)

Same methodology as the M62 audit (Features leaves of the official
CE 5.0 toc.json vs pages preserved in build/pages, the corpus
pages5 tree; twin pages in pages6/pages4 are verification material
and are not counted).  Harvests since M62: MSXML (M67 area),
SAPI (M68), RTC (M69), CEDB/EDB Database Reference (M70),
DirectShow data surface (M70b), DirectShow Interfaces (M71b),
DMO Reference (M71c), plus the earlier D3DM/mmsystem/imaging
batches.

| Features book | leaves | have | % |
|---|---|---|---|
| Graphics and Multimedia Technologies | 2935 | 2204 | 75% |
| Shell and User Interface | 2407 | 1687 | 70% |
| Communication Services and Networking | 2331 | 443 | 19% |
| Applications and Services Development | 2160 | 1052 | 48% |
| Voice over IP Phone Services | 639 | 421 | 65% |
| Internet Client Services | 607 | 246 | 40% |
| International | 547 | 194 | 35% |
| Core OS Services | 522 | 359 | 68% |
| File Systems and Data Store | 500 | 166 | 33% |
| Security | 444 | 232 | 52% |
| Applications - End User | 377 | 92 | 24% |
| Device Management | 237 | 49 | 20% |
| Fonts | 67 | 29 | 43% |
| SideShow | 48 | 0 | 0% |
| Windows CE Error Reporting | 38 | 0 | 0% |
| **Total (Features)** | **13859** | **7174** | **52%** |

Movement since M62: total 26% -> 45% (+2679 pages).  Remaining
largest gaps after M73/M74 (DCOM books + DirectShow Classes 922
harvested): Communication 1892 uncovered (Servers 810, NetGen 790),
Graphics 731 remaining (Attributes-era books are Compact-2013-tree
titles; CE 5.0 DirectShow remainder is Unsupported-Items), VoIP 218
(phone UI), File Systems 334 (FAT/registry internals and DDI-heavy
books).

Next queues by value: Servers (810), NetGen (790), remaining Core OS
DDI books.

Next queues by value: DCOM (Applications and Services >
Component Services, 896 leaves, COM/DCOM interfaces), Servers
(810), NetGen (790), DirectShow Classes (855, C++ strmbase --
record-only surface), remaining Core OS DDI books.
