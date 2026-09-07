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

## 4. What third-party trees are for (and only this)

Third-party trees (CeGCC-lineage w32api/mingwrt etc.) may be
inspected **only** for:

* **Existence / parity scoping** — which header file names exist,
  which DLLs have import libraries, so the replacement's target scope
  can be enumerated (see `docs/parity-target.md`).  File/dll *names*
  are functional requirements of a drop-in replacement, not creative
  content.
* **Comparison / verification** — e.g., confirming that an export name
  exists, or checking a build result.  Nothing from these inspections
  is transcribed, translated, adapted, or mechanically converted into
  this repository.

Forbidden: opening a w32api header and writing our header "from it";
copying def files; porting macros; using web snippets or mirrors of
third-party headers as implementation material.  GitHub-hosted copies
of MS headers are not evidence for anything (they are non-official
mirrors); official Microsoft pages are.

## 5. Process rules

1. Every shipped declaration/constant has a row in
   `docs/inventory.md` naming its official page ID and Requirements.
2. Items not covered by official text are marked *own design* and
   decided from toolchain-observable behavior, never from a
   third-party implementation's behavior alone.
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
