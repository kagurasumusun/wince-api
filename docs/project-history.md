# wince-api Project History

This document is the canonical historical record of `kagurasumusun/wince-api` (Akari API).
It records how the project evolved from a small WinCE header experiment into a clean-room
WinCE API/sysroot component for the LLVM-WinCE toolchain. It deliberately distinguishes
historical implementation choices from the rules of the current tree.

## 1. Origin and purpose

`wince-api` was created to solve the API/sysroot side of the Windows CE toolchain problem:
WinCE-targeted Clang/LLD builds need CE-compatible headers and import-library descriptions,
but relying on the historical `w32api`/CeGCC ecosystem would make the new toolchain depend
on an external API tree and would complicate clean-room provenance.

The project therefore became the WinCE counterpart to `wince-crt`:

- `wince-api` provides the WinCE API headers and documented import-library definitions.
- `wince-crt` provides CRT startup/runtime glue.
- `LLVM-WinCE` provides the compiler, target support, assembler/linker integration and
  WinCE-specific toolchain behavior.
- A libc implementation remains outside the scope of `wince-api`.

The target model is CE 4.2/5.0/6.0 on 32-bit ARM/ARM-EL and x86, with the same API header
set selected by `_WIN32_WCE` and per-declaration OS-version availability.

## 2. M1: initial API foundation

The first repository milestone established the project as an independent WinCE API layer.
The initial headers were `windef.h`, `winbase.h`, and `windows.h`, with a small process,
thread, module, command-line and local-memory function set. Every declaration was tied to
an official Microsoft CE documentation page, and host compilation checks were established
for CE 4.2, 5.0 and 6.0.

This established the basic engineering rule that the implementation should be based on
published API information rather than blindly copying an existing Windows API header tree.

## 3. M2: API semantics and clean-room methodology

M2 expanded the process/thread/module surface and, importantly, documented the clean-room
methodology itself. The repository began recording the evidence hierarchy, generation-specific
Microsoft documentation sources, and the distinction between public API documentation and
third-party implementation trees.

The project also defined the intended parity target: replacing the API/sysroot role that a
CE GCC/CeGCC environment traditionally obtained from `w32api`, rather than attempting to
reproduce an entire Windows SDK implementation.

## 4. M3: first import-library generation model — historical phase

M3 introduced generated `coredll` export definitions and architecture/generation-specific
import surfaces, together with `winerror.h` and additional process/handle APIs.

**Important historical note:** the M3 export-definition process still used a
device-dump-audited export surface as an implementation/audit input. That was an early
engineering phase and is **not the provenance rule of the current project**.

The later project direction deliberately removed this dependency and made the committed
API/import definitions documentation-derived instead. This distinction is part of the
project's provenance history and must not be erased when describing the project.

## 5. M4-M10: core WinBase expansion and real-toolchain validation

The next milestones expanded the core operating-system API in a systematic way:

- TLS and thread scheduling.
- Sleep and thread priority APIs.
- File creation, deletion, attributes and enumeration.
- File I/O and directory management.
- Time and `SYSTEMTIME`/`FILETIME` conversion APIs.
- Synchronization, memory, heap and related base APIs.
- Error values and other foundational WinCE declarations.

The verification model matured from host-only syntax checks to a six-target cross-compilation
matrix:

- `arm-pc-wince4.2`
- `arm-pc-wince5.0`
- `arm-pc-wince6.0`
- `i386-pc-wince4.2`
- `i386-pc-wince5.0`
- `i386-pc-wince6.0`

This established the principle that a declaration is not considered finished merely because
it parses on the host; its 32-bit ABI and real LLVM-WinCE compilation behavior must also be
checked.

## 6. Documentation corpus and official-source transition

As the API surface grew, the project moved toward a reproducible documentation-harvesting
pipeline. Microsoft Learn's archived Windows CE documentation became the authoritative
source for declaration metadata such as:

- function/type name;
- OS-version availability;
- header name;
- link library;
- documented prototype;
- published constants and structures.

The project harvested the CE 5.0 catalog, reconciled CE 6.0 twins, and subsequently read the
Windows CE .NET documentation tree. The harvested pages were preserved separately in the
`wince-docs-corpus` repository so that the MIT clean-room implementation repository does not
need to ship a copy of the Microsoft documentation corpus.

The project explicitly records missing or contradictory documentation instead of inventing
values or silently importing desktop-Windows assumptions.

## 7. M24-M29: exceptions, debugging, GWES and GDI

The API surface expanded beyond the original WinBase foundation:

- exception/debugging declarations and CE exception structures;
- serial communication;
- message queues;
- system error values;
- NAT and CeLog surfaces;
- GWES window-manager APIs;
- GDI functions and structures;
- menus, dialogs, clipboard, resources, icons, printing and system information;
- Image List APIs and GWES message/notification constants.

These milestones established the project's present style: each batch is tied to a specific
Microsoft documentation reference section, every uncertain item is recorded in the inventory,
and ABI-sensitive structures receive compile-time size/layout checks.

## 8. M30: clean-room provenance was made explicit and reproducible

M30 was a major architectural/provenance turning point. The repository introduced a page-
corpus preservation pipeline and audited the harvested documentation rows against the header
surface.

Most importantly, the export-definition workflow was changed to derive import definitions
from **official Microsoft documentation Requirements rows**, rather than from third-party
or device-derived export lists. The committed `def/*-doc.def` files became documentation-
derived artifacts.

From this point forward, third-party projects such as w32api, mingwrt, mingw32ce, MinGW-w64
and CeGCC could be inspected for comparison/parity questions, but their implementation code
was not to be copied, ported or adapted into this repository.

This is the provenance model represented by the current README.

## 9. M31-M36: systematic gap closure and broad API coverage

The following milestones filled documented gaps and broadened the Windows CE surface:

- cross-process memory and thread-context APIs;
- version-resource and character-set translation support;
- NLS/locale formatting and mapping;
- complete CE 6.0 twin reconciliation;
- GWES style constants;
- GDI font/text and multi-monitor APIs;
- additional Windows/user/GDI structures and fixed-ABI support types.

The project increasingly used a conservative three-way classification:

1. **implemented** — the official source provides enough information;
2. **recorded-not-defined / recorded-not-declared** — the API is known but the CE archive
   does not publish enough information to implement it safely;
3. **out of scope / kernel or OEM surface** — the documentation describes a platform-build,
   kernel or OEM interface rather than a normal application import.

## 10. M37-M38: LLVM-WinCE integration and PE import correctness

M37 established end-to-end WinCE linking as a first-class project requirement. The repository
verified the x86 CE import-name behavior and added the necessary `dllimport`/assembly-name
handling so that LLVM-generated objects reference the undecorated CE component-DLL names.

The end-to-end harness then built documentation-derived import libraries with the LLVM-WinCE
`llvm-dlltool`, linked CE PE images with LLD and checked machine type, CE subsystem and import
names. The matrix covered ARM and x86 across CE 4.2/5.0/6.0.

M38 continued this model with additional `winbase.h` API coverage, including `CopyFileExW`.

This is where `wince-api` ceased to be only a header project and became a directly testable
part of the LLVM-WinCE build pipeline.

## 11. M39-M42: Winsock 2 and provider interfaces

M39 introduced the clean-room Winsock 2 surface (`winsock2.h` and `ws2tcpip.h`) and
documentation-derived `ws2.dll` definitions.

M41 completed the documented Winsock name-service portion, while M42 added the Winsock
Service Provider Interface (`ws2spi.h`). Structures and 32-bit layouts were checked across
all six target triples, and documented-but-unresolved constants/prototypes were explicitly
recorded instead of guessed.

## 12. M43-M45: TAPI/TSPI and client telephony APIs

M43 introduced the TAPI/TSPI foundation (`tapi.h` and `tapicomn.h`), including the documented
service-provider entry points and TAPI structures/constants.

M45 completed the held TAPI client surface, adding the documented line/phone functions,
callback forms and opaque client handles. The previously deferred `TSPI_lineForward` case
was also closed through the documented opaque list type.

The result was a single tested telephony surface covering both provider and client sides
where the official CE documentation is sufficient.

## 13. M44: COM/OLE/Automation/Storage

M44 added the broad COM/OLE/Storage/Automation surface through `objbase.h`, including
`Ole32.lib` and `Oleaut32.lib` import definitions, documented structures, interfaces and
methods, and end-to-end import checks.

The project also began explicitly distinguishing declared functions from functions that the
official CE Requirements table says have no link library or are platform-builder-only. This
prevents an apparently complete header from silently claiming unsupported exports.

## 14. M46-M49: advanced subsystems

The latest milestones expanded the project into additional CE subsystems:

- **M46:** Input Method Manager (`imm.h`, `Coreimm.lib`), with 55 documented functions,
  structures and handle/callback types.
- **M47:** Cryptography base CSP (`wincrypt.h`, `Coredll.lib`), including 42 documented
  `Crypt*` functions and the documented crypto type/structure surface.
- **M48:** certificate/encoding/OID/PFX support (`Crypt32.lib`), including 83 import
  definitions and the corresponding certificate/crypto structure trees.
- **M49:** Smart Card support (`winscard.h`, `Winscard.lib`), including 28 documented
  `SCard*` functions and the documented smart-card structures/handles.

The M48/M49 state is the latest committed project state as of 2026-09-09.

## 15. Current architectural position

The historical direction has converged on a clear division of responsibility:

```text
LLVM-WinCE
  compiler / target / assembler / LLD integration / CE ABI behavior
          |
          +---- wince-api
          |       WinCE API headers
          |       documentation-derived import definitions
          |
          +---- wince-crt
                  startup / CRT glue / argv / constructors and related runtime support
```

`wince-api` is therefore **not** a reimplementation of Windows CE itself, not a libc, and
not a replacement CPU/runtime emulator. Its job is the API/sysroot layer needed to compile
and link WinCE applications with the LLVM-WinCE toolchain.

## 16. Provenance rules that define the current project

The current canonical rules are:

- Microsoft public documentation is the primary source for API declarations.
- Official Microsoft Win32/PE/ABI documentation may be used when a CE page references a
  fixed ABI fact but the CE archive does not reproduce the layout/value.
- Third-party trees may be inspected for comparison, existence, compatibility and gap
  analysis, but their implementation code is not copied, ported or adapted.
- Device dumps are not implementation sources for the committed API definitions.
- Where official CE documentation does not provide enough information, the project records
  the gap rather than fabricating a signature, value or export.
- Import definitions are generated from documented link-library information; they do not
  claim undocumented ordinals or undocumented device-specific exports.
- ABI-sensitive layouts are checked on the actual 32-bit WinCE targets supported by
  LLVM-WinCE.

These rules describe the **current** state of the project. Earlier milestones may have used
older engineering approaches; those historical facts are retained above so that the project
history remains accurate rather than retroactively rewriting the development process.

## 17. Relationship to the wider WinCE work

`wince-api` is one component of a broader effort to make Windows CE development and analysis
usable with modern open-source tooling. The surrounding work includes the LLVM-WinCE
compiler/toolchain, `wince-crt`, WinCE source/documentation preservation, and WinCE system
and device research.

The purpose of keeping this history here is to make the API layer's role unambiguous: it is
the clean-room, documentation-grounded WinCE API/sysroot component that allows the modern
LLVM/Clang/LLD toolchain to target CE without making a third-party `w32api` tree part of the
implementation.
