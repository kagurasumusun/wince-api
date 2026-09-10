/*
 * Lap.h -- Local Authentication Provider (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE
 * documentation (learn.microsoft.com previous-versions archive;
 * page ids cited per record).  This is the "Lap.h." row set of the
 * Security book harvest (M95): 10 rows -- 2 application-called
 * functions (Coredll.lib), 6 LAP-exported functions (implemented by
 * the LAP DLL itself and consumed by the LASS; declared here as
 * plain prototypes, no import def), the InitLap structure, and the
 * spelling-pair resolution below.
 *
 * Spelling pair (the ImeGetUIClassName precedent): the pages print
 * TWO real spellings for the same family -- ms926083 titles the
 * FUNCTION "InitLAP" while its parameter type is "InitLap*", and
 * ms926088 titles the STRUCTURE "InitLap (structure)".  Both
 * spellings are kept exactly as printed: BOOL InitLAP(InitLap*).
 *
 * VerifyUser pair: ms926456 documents the application-called
 * function (LASS side; wszAEDisplayText spelling) and ms926487 the
 * LAP-exported function ("VerifyUser (LAP)"; pwszAEDisplayText
 * spelling).  The two signatures are type-identical (const GUID*,
 * LPCWSTR, HWND, DWORD, PVOID), so one declaration carries both
 * records; the app-called page grounds the coredll import.
 *
 * HELD (names documented, values not published anywhere official;
 * no legal CE-lineage source carries them): VU_HANDLE_MASTER_KEY
 * (ms926118 dwOptions), VU_UNTIL_SUCCESS (ms926488/489 dwOptions).
 */

#ifndef AKARI_LAP_H
#define AKARI_LAP_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ms926088 "InitLap (structure)". */
typedef struct _InitLap {
    DWORD size;          /* structure size / version information */
    DWORD capabilities;  /* supported-LAP capability bits (unpublished) */
} InitLap;

/* ------------------------------------------------------------------ */
/* Application-called functions (Coredll.lib)                           */
/* ------------------------------------------------------------------ */

/* ms926456 "VerifyUser" / ms926487 "VerifyUser (LAP)" (type-identical
 * signatures; see the header note). */
AKARI_CE_IMPORT BOOL VerifyUser(const GUID *AEKey,
    LPCWSTR wszAEDisplayText, HWND hWndParent, DWORD dwOptions,
    PVOID pExtended) AKARI_CE_NAME(VerifyUser);

/* ms937727 "CreateEnrollmentConfigDialog" (trusted applications
 * only). */
AKARI_CE_IMPORT BOOL CreateEnrollmentConfigDialog(HWND hParentWindow)
    AKARI_CE_NAME(CreateEnrollmentConfigDialog);

/* ------------------------------------------------------------------ */
/* LAP-exported functions (the LAP DLL defines and exposes these;      */
/* the LASS resolves them -- user-side exports, no import def)         */
/* ------------------------------------------------------------------ */

/* ms926083 "InitLAP (function)". */
BOOL InitLAP(InitLap *il);

/* ms926118 "LAPCreateEnrollmentConfigDialog" (dwOptions: the only
 * supported value is the held VU_HANDLE_MASTER_KEY). */
BOOL LAPCreateEnrollmentConfigDialog(HWND hParentWindow, DWORD dwOptions);

/* ms926488 "VerifyUserStart". */
VOID VerifyUserStart(const GUID *AEKey, LPCWSTR pwszAEDisplayText,
    HWND hWndParent, DWORD dwOptions, PVOID pExtended);

/* ms926489 "VerifyUserStop". */
VOID VerifyUserStop(void);

/* ms926490 "VerifyUserToTop". */
VOID VerifyUserToTop(void);

/* ms938427 "DeinitLAP". */
VOID DeinitLAP(void);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_LAP_H */
