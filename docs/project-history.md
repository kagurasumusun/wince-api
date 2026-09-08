# wince-api Project History

This document is the canonical historical record of `kagurasumusun/wince-api` (Akari API).
It records the development lineage from the wider WinCE work through the current clean-room
WinCE API/sysroot implementation. It deliberately distinguishes historical implementation
choices from the rules of the current tree.

## 1. Origin and wider WinCE work

The project originated from a broader effort to make Windows CE development, analysis and
software execution usable with modern open-source tooling rather than depending on the old
CeGCC/MSVC-era environment.

The work progressed through several related areas:

- investigation of Windows CE as a distinct operating-system/API/ABI target;
- analysis of CeGCC and its `w32api`/runtime model;
- investigation of Microsoft Windows CE 4.x/5.x/6.x documentation and source material;
- development of an LLVM/Clang/LLD-based WinCE toolchain direction;
- development of `wince-crt` for the CRT/startup/runtime side;
- development of `wince-api` for the Windows API/sysroot side;
- preservation and analysis of WinCE source/documentation material;
- WinCE system, PE, ABI, loader and device research;
- experimentation around native WinCE execution/loading and the QEMU-based Brain/i.MX28
  environment.

The API project was split out so that the responsibilities remained clear instead of placing
headers, CRT startup code, libc, compiler support and system emulation into one repository.

## 2. Toolchain direction

LLVM/Clang/LLD became the target toolchain direction for WinCE.

The supported API target model was established as:

- `arm-pc-wince4.2`
- `arm-pc-wince5.0`
- `arm-pc-wince6.0`
- `i386-pc-wince4.2`
- `i386-pc-wince5.0`
- `i386-pc-wince6.0`

The architecture focus includes ARM/ARM-EL and x86 32-bit CE environments, with the CE API
selected by `_WIN32_WCE` and per-declaration OS-version availability.

The resulting responsibility split became:

- `LLVM-WinCE`: compiler, target support, assembler/linker integration and WinCE-specific
  toolchain behavior;
- `wince-api`: WinCE API headers and import-library definitions;
- `wince-crt`: CRT startup/runtime glue;
- libc: separate responsibility;
- emulator/loader/device work: separate system-level projects.

## 3. API/sysroot problem

The central problem was that WinCE-targeted Clang/LLD builds need CE-compatible headers and
import libraries, while the historical CE GCC ecosystem normally supplied this through a
`w32api`-style sysroot.

The goal became to provide that API/sysroot role independently, without making a third-party
`w32api` tree part of the implementation.

CeGCC, `w32api`, mingwrt, mingw32ce, MinGW-w64 and related projects were investigated for
scope, compatibility, ABI behavior and historical reference, but the current implementation
is not copied, ported or adapted from those trees.

## 4. M1: initial API foundation

The first repository milestone established `wince-api` as an independent WinCE API layer.
The initial headers were `windef.h`, `winbase.h`, and `windows.h`, with a small process,
thread, module, command-line and local-memory function set.

Every declaration was tied to an official Microsoft CE documentation page, and host
compilation checks were established for CE 4.2, 5.0 and 6.0.

## 5. M2: API semantics and clean-room methodology

M2 expanded the process/thread/module surface and documented the clean-room methodology,
source hierarchy, generation-specific Microsoft documentation and the distinction between
public API documentation and third-party implementation trees.

The intended parity target was defined as the API/sysroot role historically provided by
CeGCC/w32api, not reproduction of an entire Windows SDK implementation.

## 6. M3: API expansion and early validation

M3 expanded the WinCE API surface with additional process, handle and system declarations,
together with `winerror.h` coverage.

The project continued to establish API declarations against documented Windows CE behavior
while refining the validation model for the supported CE generations and architectures.

## 7. M4-M10: core WinBase expansion and toolchain validation

The next milestones systematically expanded:

- TLS and thread scheduling;
- Sleep and thread priority APIs;
- file creation, deletion, attributes and enumeration;
- file I/O and directory management;
- time and `SYSTEMTIME`/`FILETIME` conversion APIs;
- synchronization;
- memory and heap management;
- system management;
- NLS/code-page APIs;
- fibers;
- foundational error values.

The verification model matured from host-only checks to the six-target LLVM-WinCE cross-
compilation matrix.

## 8. Documentation corpus and official-source transition

As the API surface grew, the project moved to a reproducible Microsoft documentation-harvest
pipeline. Microsoft Learn's archived Windows CE documentation became the authoritative source
for declaration metadata such as names, OS availability, headers, link libraries, prototypes,
constants and structures.

The project harvested and reconciled the CE 5.0, CE 6.0 and Windows CE .NET documentation
trees. The harvested Microsoft pages were preserved separately in `wince-docs-corpus` so the
MIT implementation repository does not need to ship a copy of the documentation corpus.

Missing, contradictory or insufficient documentation is recorded rather than silently filled
with desktop-Windows assumptions.

## 9. M22-M29: system, exception, GWES and GDI expansion

The API surface expanded from core WinBase into:

- message queues;
- exceptions and debugging;
- serial communications;
- CeLog and NAT;
- expanded system errors;
- GWES/window management;
- GDI;
- menus, dialogs, clipboard, resources, icons and printing;
- image lists;
- window/message/style constants.

The batch-based development model was established: each group is tied to a Microsoft
reference section, every uncertain item is recorded in the inventory, and ABI-sensitive
structures receive compile-time layout checks.

## 10. M30: reproducible clean-room provenance

M30 was a major provenance turning point. The repository introduced the page-corpus
preservation pipeline and audited harvested documentation rows against the header surface.

The project formalized a reproducible clean-room process in which third-party projects could
still be inspected for comparison, parity, existence and gap analysis, but their implementation
code was not to be copied, ported or adapted into this repository.

## 11. M31-M36: systematic gap closure

The following work broadened the API surface through:

- cross-process memory and thread-context APIs;
- version-resource support;
- character-set translation;
- NLS/locale formatting and mapping;
- CE 6.0 twin reconciliation;
- GWES styles;
- GDI font/text and multi-monitor APIs;
- additional Windows/user/GDI structures and fixed-ABI support types.

A conservative classification became standard:

1. implemented;
2. recorded-not-defined / recorded-not-declared;
3. out of scope / kernel / OEM / platform-builder surface.

## 12. M37-M38: LLVM-WinCE integration and PE import correctness

M37 established end-to-end WinCE linking as a first-class requirement.

The repository verified x86 CE import-name behavior and added the required `dllimport` and
assembly-name handling so LLVM-generated objects resolve the CE component-DLL names.

The end-to-end harness linked WinCE PE images with LLD and checked machine type, CE subsystem
and import names across all six targets.

M38 continued the API expansion with `CopyFileExW` and related WinBase coverage.

At this stage `wince-api` had become a directly testable component of the LLVM-WinCE build
pipeline rather than only a header collection.

## 13. M39-M42: Winsock 2 and provider interfaces

M39 introduced the clean-room Winsock 2 surface (`winsock2.h`, `ws2tcpip.h`) and its
WinCE networking API coverage.

M41 completed the documented Winsock name-service surface. M42 added the Winsock Service
Provider Interface (`ws2spi.h`).

Structures and 32-bit layouts were checked across all six target triples, while documented-
but-unresolved values and prototypes were recorded rather than guessed.

## 14. M43-M45: TAPI/TSPI and client telephony

M43 introduced the TAPI/TSPI foundation (`tapi.h`, `tapicomn.h`).

M44 added the COM/OLE/Storage/Automation surface (`objbase.h`, `Ole32.lib`, `Oleaut32.lib`).

M45 completed the documented TAPI client surface, including line/phone functions, callbacks,
client handles and the previously held `TSPI_lineForward` case.

## 15. M46-M49: advanced subsystems

The latest milestones expanded the API into additional CE subsystems:

- **M46:** Input Method Manager (`imm.h`, `Coreimm.lib`), 55 documented functions and the
  associated structures/handles/callbacks.
- **M47:** Cryptography base CSP (`wincrypt.h`, `Coredll.lib`), 42 documented `Crypt*`
  functions and the documented crypto type/structure surface.
- **M48:** certificate/encoding/OID/PFX support (`Crypt32.lib`), including the certificate
  and encoding structure trees and 83 documented imports.
- **M49:** Smart Card support (`winscard.h`, `Winscard.lib`), including 28 documented
  `SCard*` functions and the documented smart-card structures/handles.

The M49 state is the latest committed API milestone as of 2026-09-09.

## 16. Wider WinCE system and device work

In parallel with the API/sysroot work, the wider WinCE effort progressed into system-level
research and execution support:

- WinCE PE image and loader analysis;
- WinCE DLL import resolution and function-table/Thunk-layer work;
- WinCE runtime support including path handling, Unicode conversion and system API shims;
- WinCE partition/eMMC image analysis and boot/layout investigation;
- Sharp Brain / i.MX28 platform investigation;
- QEMU-based Brain machine/peripheral work for display, touch and keyboard support;
- investigation of native Linux-side loading/execution of WinCE binaries without emulating
the CPU itself;
- WinCE application investigation using real binaries and crash/log analysis.

These efforts are related to the overall WinCE platform work but remain architecturally
separate from `wince-api`.

## 17. Current architectural position

The overall architecture has converged on a clear separation:

```text
LLVM-WinCE
  compiler / target / assembler / LLD integration / CE ABI behavior
          |
          +---- wince-api
          |       WinCE API headers
          |       documentation-derived import definitions
          |
          +---- wince-crt
          |       startup / CRT glue / argv / constructors / runtime support
          |
          +---- libc
          |       separate C library responsibility
          |
          +---- WinCE system/device work
                  loader / runtime integration / QEMU / platform research
```

`wince-api` is not a reimplementation of Windows CE, not a libc, and not a CPU emulator.
It is the API/sysroot component required to compile and link WinCE applications with the
LLVM-WinCE toolchain.

## 18. Current provenance rules

The current canonical rules are:

- Microsoft public documentation is the primary source for API declarations.
- Official Microsoft Win32/PE/ABI documentation may be used when a CE page references a
  fixed ABI fact but the CE archive does not reproduce the layout/value.
- Third-party trees may be inspected for comparison, existence, compatibility and gap
  analysis, but their implementation code is not copied, ported or adapted.
- Device dumps are not implementation sources for the committed API definitions.
- Where official CE documentation is insufficient, the project records the gap instead of
  fabricating a signature, value or export.
- Import definitions are derived from documented link-library information and do not claim
  undocumented ordinals or device-specific exports.
- ABI-sensitive layouts are checked on the actual 32-bit WinCE targets supported by
  LLVM-WinCE.

Earlier milestones may have used older engineering approaches; those historical facts are
retained above so the development history is accurate rather than retroactively rewritten.

## 19. Present goal

The present goal is a complete, reproducible and independently maintained WinCE API/sysroot
layer for LLVM/Clang/LLD, covering the documented CE 4.2/5.0/6.0 application API surface as
far as the available official information permits, while keeping the API, CRT, libc and
system-emulation responsibilities separate.
