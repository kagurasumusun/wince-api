/*
 * winerror.h -- error-code constants for Windows CE (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Each name here is one that appears in an
 * official Windows CE function page (cited per group below); the
 * numeric values are the Win32 error-code ABI values published in
 * Microsoft's official System Error Codes reference.  The complete CE
 * error list is the official *Error Values* page (aa450740); this
 * header is expanded from it in later batches.
 */

#ifndef AKARI_WINERROR_H
#define AKARI_WINERROR_H

#ifdef __cplusplus
extern "C" {
#endif

/* General error values. */
#define ERROR_SUCCESS                0L   /* The operation completed successfully. */
#define ERROR_INVALID_FUNCTION       1L   /* Incorrect function. */
#define ERROR_FILE_NOT_FOUND         2L   /* The system cannot find the file. */
#define ERROR_PATH_NOT_FOUND         3L   /* The system cannot find the path. */
#define ERROR_ACCESS_DENIED          5L   /* Access is denied. */
#define ERROR_INVALID_HANDLE         6L   /* The handle is invalid. */
#define ERROR_NOT_ENOUGH_MEMORY      8L   /* Not enough storage is available. */
#define ERROR_OUTOFMEMORY           14L   /* Not enough storage is available
                                             to complete this operation. */

/* ERROR_INVALID_PARAMETER: cited by the CE CreateThread page
 * (ms885186: NULL start address returns ERROR_INVALID_PARAMETER). */
#define ERROR_INVALID_PARAMETER     87L

/* ERROR_INSUFFICIENT_BUFFER / ERROR_NO_UNICODE_TRANSLATION: cited by
 * the CE conversion-function pages (ms915519 / ms961248). */
#define ERROR_INSUFFICIENT_BUFFER  122L
#define ERROR_NO_UNICODE_TRANSLATION 1113L

/* ERROR_ALREADY_EXISTS: cited by the CE WinMain page (ms914104: a
 * uniquely named mutex fails with ERROR_ALREADY_EXISTS when a prior
 * instance exists). */
#define ERROR_ALREADY_EXISTS       183L

/* STILL_ACTIVE: cited by the CE GetExitCodeProcess page (ms885622)
 * and the CE CreateProcess page (ms885182) as the termination status
 * of a process that has not terminated. */
#define STILL_ACTIVE               259L

#ifdef __cplusplus
}
#endif

#endif /* AKARI_WINERROR_H */
