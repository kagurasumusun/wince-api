/*
 * Cred_prov.h -- Credential Manager type-provider entry points
 * (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE
 * documentation (learn.microsoft.com previous-versions archive;
 * page ids cited per record).  This is the "Cred_prov.h." row set
 * of the Security book harvest (M95): the five entry points a
 * credential type provider implements ("type providers" -- the
 * credential manager calls these ON the provider DLL).  They are
 * user-side exports, not imports: declared as plain prototypes,
 * and excluded from the def files (gen-doc-def NOT_EXPORTS, the
 * CePimCommand/LAP precedent), even though the pages' Requirements
 * boilerplate prints Coredll.lib.
 *
 * Transcription notes:
 *   - ms926136/ms926454 are TITLED "Load Function (Credential
 *     Manager)" / "Unload Function (Credential Manager)" but print
 *     the callee names Load / UnLoad in the signatures; the printed
 *     names are used (title-vs-print, recorded).
 */

#ifndef AKARI_CRED_PROV_H
#define AKARI_CRED_PROV_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef BOOL *PBOOL;   /* the pages' pointer spelling (not in Windef) */

/* ms906527 "HandleBlob". */
DWORD HandleBlob(DWORD dwType, PWCHAR szTarget, PWCHAR szUser,
    PBYTE pInBlob, DWORD dwInSize, PBYTE pOutBlob, PDWORD pdwOutSize,
    DWORD dwFlag);

/* ms926136 "Load Function (Credential Manager)" (prints "Load"). */
DWORD Load(DWORD dwType, DWORD dwFlags);

/* ms926147 "MatchTarget". */
DWORD MatchTarget(DWORD dwType, PWSTR wszSrc, PWSTR wszDest,
    DWORD dwFlag, PBOOL pbMatch);

/* ms926153 "MatchUser". */
DWORD MatchUser(DWORD dwType, PWSTR wszSrc, PWSTR wszDest,
    DWORD dwFlag, PBOOL pbMatch);

/* ms926454 "Unload Function (Credential Manager)" (prints "UnLoad";
 * the capital L spelling is the page's own). */
DWORD UnLoad(DWORD dwType, DWORD dwFlags);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_CRED_PROV_H */
