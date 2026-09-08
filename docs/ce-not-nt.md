# Windows CE is not Windows NT -- official-source readout

Question (raised in project review): is Windows CE really a separate
(non-NT) operating system, and does this repository correctly target
it?  Everything below is quoted only from official Microsoft public
pages (learn.microsoft.com archives).

## 1. Windows CE has its own kernel

MSDN Magazine (Microsoft's official magazine, hosted at
`learn.microsoft.com/en-us/archive/msdn-magazine/2006/december/mobilize-explore-the-new-features-in-windows-embedded-ce-6-0`):

* "Windows Embedded CE 6.0 (CE 6.0) introduces a **new kernel** that
  overcomes limitations of **earlier kernels**" -- CE kernels are a
  distinct lineage, re-designed in 6.0.
* "Starting with the first version of Windows CE and including every
  version up to Windows CE 5.0, the Win32 APIs were deployed using
  client/server architecture **similar to that found in early versions
  of Windows NT** ... There are similarities, but **it is important
  to note the differences between the Windows CE implementation and
  the one on Windows NT**."
* "**Unlike Windows NT, Windows CE was designed to be configurable**"
  (Platform Builder catalog model).
* CE kernel limits through 5.0: "the limit on total number of
  processes (32), and the small virtual address space (32MB) of
  previous generations of Windows CE kernels" -- CE-specific limits
  that never applied to NT.
* CE 6.0 split the OS core: "the kernel (**kernel.dll**) and the OEM
  Adaptation Layer (**nk.exe**)" built as two separate modules, with
  system APIs moved into kernel-mode DLLs.

Official CE 6.0 documentation page `ee482762` "Kernel Servers:
Windows CE 5.0 vs. Windows Embedded CE 6.0"
(`learn.microsoft.com/en-us/previous-versions/windows/embedded/ee482762(v=winembedded.60)`):

* CE 5.0: "a process server library (PSL) is a **process** that
  implements a set of APIs for applications to call."
* CE 6.0: "Kernel.dll, filesys.dll, device.dll, gwes.dll, and most of
  device drivers are kernel-mode servers.  The kernel-mode servers
  are supported by a kernel-only version of coredll named
  **kcoredll.dll**."

## 2. Consequence for this repository

Windows CE 1.x-6.x is a separate operating system family with its own
kernel (not built on the Windows NT kernel, no shared NT lineage);
it shares the Win32 API *surface* with NT-based Windows, which is why
a clean-room w32api replacement can reuse Win32 names/shapes while
targeting different binaries:

* CE executables link against **coredll.dll** (and documented
  component DLLs: coreimm.dll, ws2.dll, ole32.dll, oleaut32.dll,
  coreloc.dll, toolhelp.dll, ...), never against NT's kernel32/user32.
* CE PE images use **subsystem 9 (IMAGE_SUBSYSTEM_WINDOWS_CE_GUI)**
  rather than NT's console/GUI subsystems; our `make e2e` asserts
  `IMAGE_SUBSYSTEM_WINDOWS_CE_GUI` on every target.
* The toolchain triples are `arm/i386-pc-wince{4.2,5.0,6.0}`
  (kagurasumusun/llvm-project, branch LLVM-WinCE).

The archived public documentation trees harvested by this project are
Windows CE .NET (4.x), Windows CE 5.0 and Windows Embedded CE 6.0
(`tools/catalogs/catalog-*.tsv`).  The CE 1.0/2.x/3.0 book contents
are no longer present in the learn.microsoft.com archive; the API
shape they described is preserved through the CE .NET-6.0 pages that
this repository harvests (Requirement rows state "Windows CE 2.10 and
later" / "Windows CE 3.0 and later" for the old surfaces, e.g. the
M47 Cryptography functions).
