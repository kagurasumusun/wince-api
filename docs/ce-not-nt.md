# Windows CE is not NT-family (design note)

Windows CE (5.0/6.0) is not a member of the Windows NT family and is
not a "stripped-down" NT.  It is an independent, modular, real-time
OS whose user-mode API deliberately implements a *subset of the Win32
API* -- the compatibility that gives CE its familiar programming
model.  Microsoft's own documentation places the Win32-API pages
under the *Windows CE* / *Windows Embedded Compact* product
documentation, not under the NT-based SDK.

Consequences for this repository (clean-room, official pages only):

* The **authority for every declaration is the Windows CE page** the
  item is annotated with.  CE pages state the API's own Header,
  OS-Versions and Link Library rows, and those rows are what we
  transcribe.
* The header *file names* (windef.h, winbase.h, winnt.h, winnls.h,
  tlhelp32.h, ...) mirror the **Windows CE SDK's own include set**,
  not the NT kernel.  winnt.h is a CE SDK header name; its content
  here is only the small set of types/objects CE pages and Win32-ABI
  facts require (64-bit integer unions, the critical-section object,
  SecureZeroMemory).  Nothing NT-kernel-internal is reproduced.
* Where a CE page does not publish a layout or numeric value (e.g.
  the critical-section object, some flag constants), the repository
  records the item as either (a) fixed Win32 ABI facts referenced
  from Microsoft's official Win32/ABI reference, or (b) *unknown and
  deliberately undefined* -- never invented from NT internals.
* NT semantics are never assumed: CE has no security attributes, no
  ANSI/Unicode dual exports, no priority classes, no OneCore, and its
  kernel APIs live behind Nk.lib/Kfuncs.h rows that are kept separate
  from the user-mode surface (documented conflict model).

## Official-evidence appendix (checked 2026-09-07)

Q: "is Windows CE really not NT-family? prove it from official public
information, versions 1.0–6.0."  Every CE version (1.0, 2.x, 3.0,
CE .NET 4.x, 5.0, Windows Embedded CE 6.0) belongs to the independent
CE/Windows Embedded Compact lineage, not to the Windows NT lineage.
Official public sources say so structurally:

* **Microsoft's own archive keeps the product lines in separate doc
  trees.**  Learn's previous-versions index publishes
  *Windows CE .NET*, *Windows CE 5.0* and *Windows Embedded CE 6.0*
  as three independent product-documentation trees (see
  docs/version-coverage.md for the counts and page-id families) — it
  never routes CE APIs through the NT-based Windows SDK.  In the same
  archive, the NT-based embedded products (Windows Embedded Standard /
  XP Embedded etc.) live in their own trees and are described as
  Windows XP/Vista/7-based.

* **CE's own pages describe an independent, modular, real-time OS.**
  Official CE .NET FAQ / Welcome page, "Windows CE Application
  Development Frequently Asked Questions", archived as
  ms920900(v=msdn.10):
  "With Windows CE, Microsoft is providing an open, standards-based
  platform…"; "Microsoft Windows CE .NET is the successor to Windows
  CE 3.0.  It is the robust, real-time operating system…"; CE .NET
  "includes over 400 professionally-tested lightweight configurable
  components, a hard real-time and preemptive multitasking kernel…
  built-in support for over 200 different 32-bit CPUs".  The lineage
  named is *CE 3.0 → CE .NET*, never Windows NT; the "hard real-time"
  and "configurable components" claims are not NT properties.

* **Microsoft Research's official "Experiment 19" description
  (microsoft.com/en-us/research) states the two kernels side by side
  as different things:** Windows Phone 7 ran "the Windows CE kernel,
  the same OS kernel used in Windows Phone 7", while Windows Phone 8
  ran "the Windows NT kernel, the same OS kernel used in Windows 8";
  Microsoft announced on 2012-06-20 that Windows Phone 8 would use
  "the same Windows core as Windows 8".  A "move *to* the NT kernel
  in 2012" only makes sense if CE never had the NT kernel before.

* **Windows CE 6.0 official pages** (winembedded.60 archive) document
  the same CE-kernel object (nk.exe / OAL / GWES / kernel API rows)
  and its 6.0 redesign as *CE* history ("Kernel Migration… for
  Windows Embedded CE 6.0"), not as adoption of NT internals.


* **Windows Embedded team member, official MSDN archive blog "Windows CE
  is NOT dead!" (Olivier Bloch, Windows Embedded team, May 4, 2010,
  learn.microsoft.com/en-us/archive/blogs/obloch/windows-ce-is-not-dead).**
  Asked how Windows Embedded CE/Compact differs from Windows, the
  response states outright: "Windows Embedded CE and its next version,
  Windows Embedded Compact 7 are **not based on Windows binaries** (vs.
  Windows Embedded Standard which is a componentized embedded version
  of Windows).  Windows CE has been developed **from scratch with a
  different OS architecture and driver model** ensuring hard real time
  and very small footprint."  This is a Microsoft-published, first-party
  statement distinguishing the CE/Compact lineage (independent kernel,
  own driver model, cross-CPU) from the NT-based embedded line
  (Windows Embedded Standard = componentized Windows/NT) -- the same
  structural claim the Learn archive trees make (see above).

Consequence for this repository is unchanged: nothing NT-kernel-internal
is imported; CE SDK header names and the Win32-API subset shape are
what Microsoft's CE pages document.
