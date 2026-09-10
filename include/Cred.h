/*
 * Cred.h -- Credential Manager (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE
 * documentation (learn.microsoft.com previous-versions archive;
 * page ids cited per record).  This is the "Cred.h." row set of the
 * Security book harvest (M95): the CRED structure and 5 functions
 * (Coredll.lib), replacing the deprecated Credmgr.h API set.
 *
 * Transcription notes:
 *   - ms936976 prints "typedefstruct_CRED{...}" glued; split for
 *     compilation.  The member spellings are kept, including the
 *     WSTR pointer spelling (declared below as the page's own
 *     carrier: a wide string pointer).
 *   - HELD (names documented, values not published anywhere
 *     official; no legal CE-lineage source carries them):
 *     CRED_VER_1 (ms936976 dwVersion), CRED_MAX_TARGET_LEN
 *     (ms936977/984/985 dwTargetLimit), and the CRED_TYPE_* names
 *     (CRED_TYPE_NTLM, CRED_TYPE_KERBEROS, CRED_TYPE_DOMAIN_
 *     PASSWORD, CRED_TYPE_CERTIFICATE, CRED_TYPE_GENERIC,
 *     CRED_TYPE_DOMAIN_CERTIFICATE, CRED_TYPE_DOMAIN_VISIBLE_
 *     PASSWORD -- ms936977 / ms937730 tables).
 */

#ifndef AKARI_CRED_H
#define AKARI_CRED_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef WCHAR *WSTR;    /* the pages' own pointer spelling */

/* ms936976 "CRED". */
typedef struct _CRED {
    DWORD dwVersion;    /* CRED_VER_1 (value held) */
    DWORD dwType;       /* CRED_TYPE_* (values held) */
    WSTR wszUser;
    DWORD dwUserLen;
    WSTR wszTarget;
    DWORD dwTargetLen;
    PBYTE pBlob;
    DWORD dwBlobSize;
    DWORD dwFlags;
} CRED, *PCRED, **PPCRED;

/* ms936977 "CredDelete". */
AKARI_CE_IMPORT HRESULT CredDelete(WSTR wszTarget, DWORD dwTargetLen,
    DWORD dwType, DWORD dwFlags) AKARI_CE_NAME(CredDelete);

/* ms936983 "CredFree". */
AKARI_CE_IMPORT HRESULT CredFree(PBYTE pvBuffer)
    AKARI_CE_NAME(CredFree);

/* ms936984 "CredRead". */
AKARI_CE_IMPORT HRESULT CredRead(WSTR wszTarget, DWORD dwTargetLen,
    DWORD dwType, DWORD dwFlags, PPCRED ppCred) AKARI_CE_NAME(CredRead);

/* ms936985 "CredUpdate". */
AKARI_CE_IMPORT HRESULT CredUpdate(WSTR wszTarget, DWORD dwTargetLen,
    DWORD dwType, PCRED pCred, DWORD dwFlags) AKARI_CE_NAME(CredUpdate);

/* ms936986 "CredWrite". */
AKARI_CE_IMPORT HRESULT CredWrite(PCRED pCred, DWORD dwFlags)
    AKARI_CE_NAME(CredWrite);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_CRED_H */
