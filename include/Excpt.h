/*
 * Excpt.h -- structured exception handling declarations for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration below is annotated with the
 * official Microsoft Windows CE documentation page it is taken from
 * (CE-era MSDN pages, learn.microsoft.com previous-versions archive,
 * (v=msdn.10) IDs).  The Exception Reference pages state Header:
 * Excpt.h for GetExceptionCode / GetExceptionInformation /
 * AbnormalTermination and for the EXCEPTION_POINTERS structure, and
 * the pages note "The Excpt.h file must be explicitly included to use"
 * these functions.  CE supports structured exception handling through
 * the compiler/toolchain; on Windows CE the documented Header row is
 * Excpt.h and the Link Library row is Coredll.lib.
 */

#ifndef AKARI_EXCPT_H
#define AKARI_EXCPT_H

#include "Windef.h"
#include "Winnt.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ms885215 "EXCEPTION_POINTERS (Windows CE 5.0)": returned by
 * GetExceptionInformation; points to the EXCEPTION_RECORD describing
 * the exception and the CONTEXT with the machine state.  CE 1.0+;
 * Excpt.h.  (CONTEXT is an incomplete type here; its layout is not
 * published on the documentation pages -- see winnt.h.) */
typedef struct _EXCEPTION_POINTERS {
    PEXCEPTION_RECORD ExceptionRecord;
    PCONTEXT          ContextRecord;
} EXCEPTION_POINTERS, *PEXCEPTION_POINTERS, *LPEXCEPTION_POINTERS;

/* aa450784 "AbnormalTermination (Windows CE 5.0)":
 * BOOL AbnormalTermination(void).  CE 1.0+; Excpt.h; Coredll.lib.
 * Callable only from the finally block of a try-finally; nonzero
 * means the try block terminated abnormally (return/goto/continue/
 * break out of the block). */
BOOL AbnormalTermination(void);

/* ms885620 "GetExceptionCode (Windows CE 5.0)":
 * DWORD GetExceptionCode(void).  CE 1.0+; Excpt.h; Coredll.lib.
 * Callable only from the filter expression or handler block of a
 * try-except; returns the exception code (see the EXCEPTION_* values
 * in winnt.h). */
DWORD GetExceptionCode(void);

/* ms885621 "GetExceptionInformation (Windows CE 5.0)":
 * LPEXCEPTION_POINTERS GetExceptionInformation(void).  CE 1.0+;
 * Excpt.h; Coredll.lib.  Callable only from the filter expression of
 * a try-except; returns a pointer to an EXCEPTION_POINTERS. */
LPEXCEPTION_POINTERS GetExceptionInformation(void);

/* ------------------------------------------------------------------
 * Book surface: core-exception-reference (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa450741 Exception Functions */
/* aa450743 Exception Structures */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_EXCPT_H */
