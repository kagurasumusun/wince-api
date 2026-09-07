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
