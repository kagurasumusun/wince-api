# Akari startup support — Windows CE

This directory contains the Windows CE **program-startup support** used by Akari SDK for Clang/LLVM targets. It is kept in-tree so the startup objects, API headers, and documentation-derived import definitions can be built and verified together.

Akari's startup support is deliberately limited to the transition from a PE/COFF entry point to the application's entry function and the associated Windows CE process-startup bookkeeping. It is not intended to define a general-purpose language or platform library.

## Toolchain

The code is built and link-verified with the Windows CE toolchain from `kagurasumusun/llvm-project` (branch `LLVM-WinCE`): clang/lld with the WinCE driver and the `*-pc-wince` target triples.

Supported targets include:

- ARM/armel Windows CE targets such as `arm-pc-wince`, `arm-pc-wince5.0`, and `arm-pc-wince4.2`
- x86 Windows CE targets such as `i386-pc-wince`
- `windows-gnu` targets used for compatibility checks where supported by the same sources

## What this directory provides

- PE entry objects for Windows CE executables and DLLs
- Command-line and entry-point startup handling
- Windows CE startup data and initialization bookkeeping
- Host-side tests for the startup code
- Build rules for the supported targets

The startup implementation does not define the Windows CE API itself; API declarations and documentation-derived import definitions live in the parent SDK.

## Build products

```text
build/libakari.a         startup support archive
build/akari_crt0.o       executable entry points
build/akari_dllcrt.o     DLL entry points
```

## Building

```sh
make
make TARGET=arm-pc-wince5.0
make TARGET=i386-pc-wince
make TARGET=armv7-unknown-windows-gnu ARCHFLAGS=-mthumb
make CC=/path/to/clang AR=/path/to/llvm-ar
```

The default target is `arm-pc-wince`. The target controls the Windows CE deployment version and the corresponding compiler target settings.

## Host-side checks

```sh
make check
```

Host checks compile the startup sources with the host compiler and run the startup parser tests using host-side stubs for Windows CE imports.

## Repository layout

```text
include/akari/compiler.h   compiler and target macros
include/akari/crt.h        public startup data declarations
include/akari/internal.h   internal shared declarations
src/crt/runtime.c          startup data, command-line handling and initialization
src/crt/crt0.c             executable entry points
src/crt/dllcrt.c           DLL entry points
src/                         implementation sources
tests/host/                   host-side tests
```

For the SDK-wide documentation and verification commands, see the repository root `README.md`.
