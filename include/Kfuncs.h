/*
 * Kfuncs.h -- documented include-name alias for winbase.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Kfuncs.h" (8 pages);
 * the Kfuncs.h pages (DebugBreak, GetCurrentProcess/Thread/Id, SetEvent, ResetEvent) declare kernel helpers already carried in winbase.h.  This project carries the declarations in winbase.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Kfuncs.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Kfuncs.h with winbase.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "Winbase.h"/* ------------------------------------------------------------------
 * Book surface: core-process-and-thread-reference (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa450792 CeGetCallerTrust: print `DWORD CeGetCallerTrust (void);` */
AKARI_CE_IMPORT DWORD CeGetCallerTrust(void)
    AKARI_CE_NAME(CeGetCallerTrust);
/* ms885614 GetCurrentProcessId: print `` */
AKARI_CE_IMPORT DWORD GetCurrentProcessId(void)
    AKARI_CE_NAME(GetCurrentProcessId);
/* ms885616 GetCurrentThreadId: print `` */
AKARI_CE_IMPORT DWORD GetCurrentThreadId(void)
    AKARI_CE_NAME(GetCurrentThreadId);

