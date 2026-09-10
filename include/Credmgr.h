/*
 * Credmgr.h -- deprecated Credential Manager API (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE
 * documentation (learn.microsoft.com previous-versions archive;
 * page ids cited per record).  This is the "Credmgr.h." row set of
 * the Security book harvest (M95): the deprecated CREDENTIAL
 * structure and 3 functions (Secur32.lib; def/secur32-doc.def),
 * superseded by the Cred.h API set.
 *
 * Transcription notes:
 *   - ms937728 prints the CREDENTIAL definition glued
 *     ("typedefstruct_CREDENTIAL{DWORDFlags;...}"); split for
 *     compilation.
 *   - ms937730 (CeCredRead) and ms937731 (CeCredWrite) print NO
 *     return type and their Return Values sections print "None" --
 *     declared void; ms937729 (CeCredFree) prints none either and
 *     its Return Values section prints "None" as well.
 *   - ms937730's dwCredType table names CRED_TYPE_GENERIC /
 *     DOMAIN_PASSWORD / DOMAIN_CERTIFICATE / DOMAIN_VISIBLE_
 *     PASSWORD without values (held, see Cred.h).
 */

#ifndef AKARI_CREDMGR_H
#define AKARI_CREDMGR_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ms937728 "CREDENTIAL" (deprecated; use Cred.h CRED). */
typedef struct _CREDENTIAL {
    DWORD Flags;
    DWORD Type;
    FILETIME LastWritten;
    DWORD CredentialBlobSize;
    LPBYTE CredentialBlob;
    DWORD Persist;
    LPTSTR UserName;
} CREDENTIAL, *PCREDENTIAL;

/* ms937729 "CeCredFree" (deprecated). */
AKARI_CE_IMPORT VOID CeCredFree(PVOID pCred) AKARI_CE_NAME(CeCredFree);

/* ms937730 "CeCredRead" (deprecated; no return type printed). */
AKARI_CE_IMPORT VOID CeCredRead(PCWSTR pszTarget, DWORD dwCredType,
    DWORD dwFlags, PCREDENTIAL pCred) AKARI_CE_NAME(CeCredRead);

/* ms937731 "CeCredWrite" (deprecated; no return type printed;
 * pCred is printed [out] on its page). */
AKARI_CE_IMPORT VOID CeCredWrite(PCWSTR pszTarget, PCREDENTIAL pCred)
    AKARI_CE_NAME(CeCredWrite);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_CREDMGR_H */
