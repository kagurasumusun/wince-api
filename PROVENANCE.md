# Clean-Room Provenance & Technical Architecture Specification

## 1. Overview and Project Scope

`wince-api` is an independent, clean-room development layer and header library for building Windows CE applications targeting ARM architectures (specifically NXP i.MX28 / ARM926EJ-S ARMv5TE) using LLVM/Clang and LLD toolchains (e.g., `kagurasumusun/llvm-project`).

The primary purpose is to provide a modern, legally clean, independently authored WinCE API header suite and import library definition framework as a replacement for legacy toolchain headers (e.g., CeGCC `w32api`), without copying implementation code from any third-party software.

## 2. Clean-Room Methodology and Provenance Policy

1. **Independent Implementation**:
   - All code in this repository is authored independently based on public specifications, published Microsoft Windows CE API documentation, official Windows SDK specifications, ABI specifications, and observable binary specifications.
2. **Strict Prohibition**:
   - No code has been or may be copied, adapted, translated, or mechanically rewritten from CeGCC, MinGW, MinGW-w64, ReactOS, Wine, Microsoft SDKs, or any other open-source or proprietary Windows API implementation repository.
3. **Reference-Only Policy**:
   - External implementations are strictly treated as reference material or compatibility verification targets. Facts such as function names, constants, structure field layouts, enum values, exported DLL symbol names, and ordinals are factual API/ABI specifications permitted for independent clean-room implementation.

## 3. Target Platform Specifications & Research Facts

- **Primary SoC Target**: NXP i.MX28 / Freescale i.MX28 family (ARM926EJ-S core, ARMv5TE architecture).
- **Target Subsystem / OS**: Windows CE 4.x, 5.x, 6.x (Windows Embedded Compact).
- **Architecture Triple**: `armv5te-unknown-wince-pe` / `arm-wince-pe`.
- **Character Set / Encoding**: Windows CE is natively Unicode (`WCHAR` / `UTF-16LE`). Standard string APIs in WinCE map directly to Wide Character (`W`) variants.
- **Calling Convention**: On ARM WinCE, C-calling convention (`__cdecl`), standard call (`__stdcall`), and fast call (`__fastcall`) map to the standard ARM C calling convention (AAPCS / WinCE ARM ABI).
- **Default OS Version (`_WIN32_WCE`)**: `0x0500` (Windows CE 5.0), configurable via compiler definitions to `0x0400` (CE 4.x) or `0x0600` (CE 6.x).
- **Core DLL Architecture**: In Windows CE, core Win32 subsystem APIs (Kernel, User, GDI) are consolidated into `coredll.dll` rather than split across `kernel32.dll`, `user32.dll`, `gdi32.dll`.

## 4. Primary API Specifications Implemented

- **`sdkddkver.h`**: Version macros `_WIN32_WCE_CE400`, `_WIN32_WCE_CE500`, `_WIN32_WCE_CE600`, `WINVER`, `_WIN32_WINNT`.
- **`windef.h`**: Base data types (`DWORD`, `BOOL`, `BYTE`, `WORD`, `HANDLE`, `RECT`, `POINT`, `SIZE`, `WPARAM`, `LPARAM`, `LRESULT`), calling conventions (`WINAPI`, `CALLBACK`).
- **`winnt.h`**: Processor architecture constants (`_ARM_`, `PROCESSOR_ARCHITECTURE_ARM`), memory protection flags (`PAGE_READWRITE`, `MEM_COMMIT`), status codes (`S_OK`, `E_FAIL`), `CRITICAL_SECTION`.
- **`winerror.h`**: Standard Win32/WinCE error codes (`ERROR_SUCCESS`, `ERROR_FILE_NOT_FOUND`, `ERROR_ACCESS_DENIED`, etc.).
- **`winbase.h`**: Kernel memory, file I/O, threads/processes, synchronization, and module loading functions.
- **`winuser.h`**: Windowing, message loops, window procedure callbacks, and message boxes.
- **`wingdi.h`**: Basic GDI drawing, pens, brushes, stock objects, and text output.
- **`kfuncs.h`**: WinCE-specific low-level kernel routines (`CacheSync`, `CacheRangeFlush`, `InterruptInitialize`).
- **`tchar.h`**: Generic-text macros mapped to wide-character functions.
- **`excpt.h`**: SEH exception disposition codes.
- **`aygshell.h` & `sipapi.h`**: WinCE Software Input Panel (SIP) and handheld shell extensions.
- **`commctrl.h`**: Common controls initialization (`InitCommonControlsEx`).
- **`winsock2.h` & `ws2def.h`**: Winsock 2 socket definitions and functions for WinCE networking.
- **`.def` files**: Import library module definition specifications for `coredll.dll`, `aygshell.dll`, `ws2.dll`, `commctrl.dll`, `ceshell.dll`.

## 5. Verification Framework

Verification is automated using CMake and CTest with Clang (`clang -target armv5te-unknown-wince-pe -fshort-wchar -fsyntax-only`):

1. Syntax and type validation for each individual header.
2. Structure size and alignment checks (`C_ASSERT` compile-time assertions).
3. Integration testing across umbrella header `windows.h` and application tests.
