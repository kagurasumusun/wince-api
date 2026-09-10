# Clean-room definition and scope (investigation result)

This document fixes the meaning of "clean-room" for wince-api (and
wince-crt).  It is the binding interpretation of the requirement:
"公式の公開資料のみ / ライセンスの問題もないように / 自分のライセンス
が持てるように / 第三者のコードをコピー・移植・翻案しない".

## 1. The goal

A Win32-for-CE API package (headers + import libraries) that is a
drop-in replacement for the w32api role of the CeGCC-lineage sysroot
(kagurasumusun/w32api), while being an **independent, original
implementation** whose only spec inputs are (a) official Microsoft
public information and (b) facts observable from the OS/toolchain
itself.  The result is licensed MIT under "Akari API contributors"
copyright — a license the author controls, with no code derived from
GPL/LGPL/public-domain-with-unknown-history third-party packages.

## 2. Why this is legally and practically coherent

* The Win32/CE **interfaces** (names, signatures, constants,
  semantics) are dictated by the OS and its official documentation.
  Facts and functional interfaces are not creative expression;
  Microsoft publishes them precisely so that programs can be written
  against them.  Expressing the same interface in our own words is
  interoperability, not copying (this is the settled position behind
  interface re-implementation; the facts here originate from
  Microsoft's own published docs, so no third-party copyright is
  even implicated).
* What **is** protected in a header package is the *expression*:
  comment text, macro tricks, layout order, naming of private
  helpers, formatting.  None of that is taken from w32api/mingwrt/
  CeGCC; every file is written here from the official pages.
* "Clean-room" as a process therefore means: the implementer works
  from the specification (official docs + OS facts) without copying
  protected code — and the paper trail (this repo's per-declaration
  page IDs in `docs/inventory.md`) demonstrates it.

## 3. Evidence hierarchy (allowed spec sources)

1. Official Microsoft public information:
   * CE-era MSDN pages, now `learn.microsoft.com/.../previous-versions/
     windows/embedded/...` — `(v=msdn.10)` (CE 4.x/5.0 API & CRT
     reference; also the older CE 3.0-era `ms9xxxxx` pages) and
     `(v=winembedded.60)` (CE 6.0 Platform Builder/run-time docs).
   * Microsoft's official Win32/PE/COFF/ABI reference pages.
   * Per-page "Requirements" rows (OS Versions / Header / Link
     Library) are transcribed verbatim into `docs/inventory.md`.
2. Observable facts: the verified export surface of the OS/toolchain
   (device-dump-audited coredll import libraries of the sysroot),
   compiler/ABI behavior of the verified toolchain
   (kagurasumusun/llvm-project, branch LLVM-WinCE).
3. Own design decisions, always labeled *own design* in the
   inventory, never dressed up as documentation.

## 4. Third-party trees: permitted uses

**Policy revision (2026-09-10, user direction).**  Sources expanded
from "official only" to *legal, trustworthy, and safe*.  Third-party
material is now permitted as an **ABI-fact source** when, and only
when, it is in the **public domain** or carries an equally
unproblematic license.  The permitted reference set (checked in as
read-only clones outside this repository, never committed):

* **R1 — CeGCC-lineage w32api** (kagurasumusun/w32api, the parity
  target itself).  README: "THIS SOFTWARE IS NOT COPYRIGHTED ...
  offered for use in the public domain".  Exceptions recorded there
  (winsock.h/winsock2.h/ws2tcpip.h BSD Regents/DEC, gl.h Mesa,
  glext.h/glu.h SGI) are used for nothing here.
* **R2 — mingw-w64 headers** (mingw-w64 runtime package, public
  domain per its DISCLAIMER notice).

Third-party trees may be used for:

* **Existence / parity scoping** — as before (see
  `docs/parity-target.md`).
* **Comparison / verification** — as before.
* **ABI facts** (NEW): numeric constant values, enumeration orders,
  vtable member orders, and structure layouts — the uncopyrightable
  functional interface facts required for interoperability — may be
  *adopted* from R1/R2 with per-family provenance recorded in
  `docs/inventory.md` and in the header where they land.  Where a
  fact exists in both R1 and R2 the two must agree; a CE-only fact
  carried only by R1 is adopted single-source and marked so.  All
  *expression* (prose, macro bodies, struct member comments, code)
  is written here, not taken from R1/R2; function macro wrappers are
  built from the CE pages' own printed wParam/lParam packings
  combined with adopted values.

**Still forbidden, unchanged**: shared-source / leaked /
unofficially-posted Microsoft material (e.g. Windows CE Shared
Source), anything whose publication or redistribution is legally
problematic, GPL/LGPL-covered expression (facts may be corroborated
across sources, code may not), and non-official mirrors of MS
headers as *documentation* evidence.  Official Microsoft pages
remain the primary source; R1/R2 fill only the gaps the official CE
pages leave (chiefly: constant values and full vtable orders).

## 5. Process rules

1. Every shipped declaration/constant has a row in
   `docs/inventory.md` naming its official page ID and Requirements.
2. Items not covered by official text are marked *own design* and
   decided from toolchain-observable behavior, never from a
   third-party implementation's behavior alone.  ABI facts adopted
   from the R1/R2 reference set under §4 are marked *adopted* with
   their source and cross-check status (the "derived values need a
   recorded path" rule extends to adopted values).
3. A file is added to `include/` only after its content is fully
   grounded; partial modules are not shipped half-grounded.
4. No third-party license or copyright text appears anywhere in this
   repository (MIT text is our own).
5. Third-party trees are never committed into this repository; parity
   measurements are recorded as numbers and names only.

## 6. Scope of "own license"

Everything in this repository is © 2026 Akari API contributors, MIT.
The interface parity with w32api creates no derivative-work chain,
because the interface facts come from Microsoft's official
documentation and the OS itself, and the expression is original.
If a future consumer needs the exact binary interface, the def/import
libraries produced here express OS facts (function names) that the OS
itself dictates.
