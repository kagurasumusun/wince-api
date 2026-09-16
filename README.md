# Akari SDK (cellvm-sdk)

Clean-room **Win32 API layer for Windows CE 4.x / 5.x / 6.x**. The project provides the headers and import-library definitions needed by WinCE-targeted builds on a plain host (Linux, macOS, ...), together with the Windows CE program-startup support kept in `crt/`.

Targets:

- `arm-pc-wince` (ARM/armel)
- `i386-pc-wince` (x86 CE)
- Windows CE 4.2 / 5.0 / 6.0

## Scope

| Concern | Provider |
|---|---|
| Win32 **API headers** for CE | **Akari SDK** (`include/`, `windows.h` umbrella) |
| Coredll **import-library definitions** | **Akari SDK** (`def/`) |
| Windows CE **program-startup support** | **Akari SDK** (`crt/`) |

Akari SDK is focused on the Windows CE API surface and the pieces required to describe and link that surface. It does **not** attempt to be a general-purpose language library or platform SDK.

## Documentation policy

- **Official public information only.** Declarations are based on Microsoft's official Windows CE documentation and the official Win32/PE/ABI references where a CE-specific page does not exist. Sources are recorded in `docs/inventory.md`.
- **CE is not desktop Win32.** A declaration is included only when its CE availability and shape can be established from the documented CE surface. Desktop-only declarations are not added merely because they exist on modern Windows.
- **Clean-room implementation.** No declarations or implementation material are copied from w32api, mingwrt, mingw32ce, MinGW-w64, CeGCC, or other third-party SDK trees.
- **MIT licensed.** See `LICENSE`; source files carry the applicable SPDX notice.

## Export definitions and import libraries

The export definitions are derived from the official Microsoft CE documentation. The pipeline is:

1. `tools/ce-manifest.py` reads the official Learn table of contents and creates a page manifest.
2. `tools/ce-fetch.py` downloads the documented pages and extracts their Requirements information into `build/rows.json`.
3. `tools/gen-doc-def.py` generates `def/*-doc.def` from that record set.

The generated definitions are committed so the repository remains self-contained. After harvesting additional categories, regenerate them with `make defdoc`.

```sh
python3 tools/ce-fetch.py tools/manifests/core-synchronization-reference.manifest
make defdoc

llvm-dlltool -m armce -d def/coredll-doc.def -l coredll.lib
llvm-dlltool -m i386 --no-leading-underscore -d def/coredll-doc.def \
    -l coredll-x86.lib
```

## Layout

```text
crt/                Windows CE program-startup support
include/windows.h   umbrella header
include/windef.h    base types and macros
include/winuser.h   user-interface API
include/wingdi.h    GDI API
include/tvout.h     TV-out declarations
include/winnt.h     base system types and helpers
include/winnls.h    NLS and code-page API
include/winreg.h    registry API
include/commctrl.h  image-list API
include/winbase.h   process/thread/module/file/synchronization API
def/                documentation-derived import definitions
tools/              documentation harvest and generation tools
docs/inventory.md   per-declaration official-source matrix
tests/host/         host compile checks
tests/e2e/          end-to-end link consumers
Makefile            build and verification entry points
```

## Build and check

```sh
make check
make crosscheck WINCECLANG=/path/to/LLVM-WinCE/clang
make crt WINCECLANG=/path/to/LLVM-WinCE/clang
make e2e WINCECLANG=/path/to/LLVM-WinCE/clang
```

`make check` verifies the headers for CE 4.2, 5.0 and 6.0. `make crosscheck` performs real-toolchain compile checks for the ARM and x86 CE targets. `make e2e` builds the documentation-derived import libraries, links the end-to-end consumers, and checks the resulting PE images.

## Status

The SDK is developed incrementally from the official CE documentation. Each batch records its declarations and source references in `docs/inventory.md`.
