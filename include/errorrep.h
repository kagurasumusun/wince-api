/*
 * errorrep.h -- Windows CE Error Reporting API (Error Reporting book).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE page
 * ms886799 "ReportFault (Windows CE 5.0)" (CE-era MSDN archive,
 * learn.microsoft.com previous-versions, (v=msdn.10)).  That page
 * (the CE 5.0 Error Reporting documentation) gives the signature,
 * Header: ErrorRep.h, Link Library: Coredll.lib, OS Versions:
 * Windows CE 5.0 or later.  The return values are named on the page
 * (frrvErrNoDW / frrvOk) with no numeric values published; the
 * EFaultRepRetVal type is provided as an int-sized alias and the
 * frrv* constants are recorded as *unknown* (not defined -- their
 * numbers are not public).  dwOpt is reserved by the page: set to
 * zero.
 */

#ifndef AKARI_ERRORREP_H
#define AKARI_ERRORREP_H

#include "windef.h"
#include "excpt.h"   /* LPEXCEPTION_POINTERS (EXCEPTION_POINTERS ms885215) */

#ifdef __cplusplus
extern "C" {
#endif

/* ms886799 names two return values -- frrvErrNoDW ("no error report
 * generated") and frrvOk ("the function succeeded") -- without numeric
 * values; a successful return does not mean the fault was reported. */
typedef int EFaultRepRetVal;

/* ms886799 "ReportFault (Windows CE 5.0)":
 * EFaultRepRetVal ReportFault(LPEXCEPTION_POINTERS pep, DWORD dwOpt).
 * CE 5.0+; ErrorRep.h; Coredll.lib.  Lets an application that does its
 * own exception handling report faults; dwOpt is reserved (zero). */
AKARI_CE_IMPORT EFaultRepRetVal ReportFault(LPEXCEPTION_POINTERS pep, DWORD dwOpt) AKARI_CE_NAME(ReportFault);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_ERRORREP_H */
