/*
 * Schnlsp.h -- Schannel security package structures (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE
 * documentation (learn.microsoft.com previous-versions archive;
 * page ids cited per record).  This is the "Schnlsp.h." row set of
 * the Security book harvest (M95): 7 structures, no functions (the
 * package is reached through the Sspi.h SSPI entry points; no Link
 * Library row prints on these pages, no def file).
 *
 * Transcription notes:
 *   - Every page prints the member list glued (DWORDdwVersion etc.);
 *     split for compilation, noted here once.
 *   - ms926432 (SCHANNEL_CRED) ends with a "DWORDreserved" member
 *     (lowercase, page print kept as dwReserved?  NO: the page
 *     spells the member "reserved" -- the spelling is kept).
 *   - The flag/protocol names (SCH_CRED_*, SP_PROT_*) and
 *     SCHANNEL_CRED_VERSION are published without values; the values
 *     are adopted from R1 in the M96 section at the end of this
 *     header (schannel.h/schnlsp.h, public domain).
 *   - struct _HMAPPER is an opaque forward reference on ms926432.
 */

#ifndef AKARI_SCHNLSP_H
#define AKARI_SCHNLSP_H

#include <Windows.h>
#include "Wincrypt.h"   /* ALG_ID, PCCERT_CONTEXT, HCERTSTORE */
#include "Sspi.h"       /* SEC_WCHAR / SEC_FAR carriers */

#ifdef __cplusplus
extern "C" {
#endif

struct _HMAPPER;         /* opaque (ms926432 forward reference) */

/* ms926432 "SCHANNEL_CRED". */
typedef struct _SCHANNEL_CRED {
    DWORD dwVersion;             /* SCHANNEL_CRED_VERSION (M96) */
    DWORD cCreds;
    PCCERT_CONTEXT *paCred;
    HCERTSTORE hRootStore;
    DWORD cMappers;
    struct _HMAPPER **aphMappers;
    DWORD cSupportedAlgs;
    ALG_ID *palgSupportedAlgs;
    DWORD grbitEnabledProtocols; /* SP_PROT_* bits (M96) */
    DWORD dwMinimumCipherStrength;
    DWORD dwMaximumCipherStrength;
    DWORD dwSessionLifespan;
    DWORD dwFlags;               /* SCH_CRED_* bits (M96) */
    DWORD reserved;
} SCHANNEL_CRED, *PSCHANNEL_CRED;

/* ms926436 "SecPkgContext_ConnectionInfo". */
typedef struct _SecPkgContext_ConnectionInfo {
    DWORD dwProtocol;            /* SP_PROT_* value (M96) */
    ALG_ID aiCipher;
    DWORD dwCipherStrength;
    ALG_ID aiHash;
    DWORD dwHashStrength;
    ALG_ID aiExch;
    DWORD dwExchStrength;
} SecPkgContext_ConnectionInfo, *PSecPkgContext_ConnectionInfo;

/* ms926438 "SecPkgContext_IssuerListInfoEx". */
typedef struct _SecPkgContext_IssuerListInfoEx {
    PCERT_NAME_BLOB aIssuers;
    DWORD cIssuers;
} SecPkgContext_IssuerListInfoEx, *PSecPkgContext_IssuerListInfoEx;

/* ms926442 "SecPkgContext_ProtoInfo". */
typedef struct _SecPkgContext_ProtoInfo {
    SEC_WCHAR SEC_FAR *sProtocolName;
    unsigned long majorVersion;
    unsigned long minorVersion;
} SecPkgContext_ProtoInfo, *PSecPkgContext_ProtoInfo;

/* ms926446 "SecPkgCred_CipherStrengths". */
typedef struct _SecPkgCred_CipherStrengths {
    DWORD dwMinimumCipherStrength;
    DWORD dwMaximumCipherStrength;
} SecPkgCred_CipherStrengths, *PSecPkgCred_CipherStrengths;

/* ms926448 "SecPkgCred_SupportedAlgs". */
typedef struct _SecPkgCred_SupportedAlgs {
    DWORD cSupportedAlgs;
    ALG_ID *palgSupportedAlgs;
} SecPkgCred_SupportedAlgs, *PSecPkgCred_SupportedAlgs;

/* ms926449 "SecPkgCred_SupportedProtocols". */
typedef struct _SecPkgCred_SupportedProtocols {
    DWORD grbitProtocol;         /* SP_PROT_* bits (M96) */
} SecPkgCred_SupportedProtocols, *PSecPkgCred_SupportedProtocols;

#ifdef __cplusplus
}
#endif

/* ================================================================== */
/* M96 value adoption -- values adopted from the CeGCC-lineage w32api
 * reference (R1, public domain; docs/clean-room.md par.4
 * revision 2026-09-10).  Every name below is documented by
 * the official CE pages WITHOUT a value (see the record
 * comments and the held ledger in this header); the value
 * is a CE-era ABI fact carried by the CE lineage itself.
 * Desktop mingw-w64 was considered and EXCLUDED as a source
 * (desktop-era values; policy note in clean-room.md).  R1's
 * license-exception files (winsock*, gl*) are unused.
 * ================================================================== */

/* ---- SCH_ family (6 names; R1) ---- */
#define SCH_CRED_NO_SYSTEM_MAPPER                    0x0002
#define SCH_CRED_NO_SERVERNAME_CHECK                 0x0004
#define SCH_CRED_MANUAL_CRED_VALIDATION              0x0008
#define SCH_CRED_NO_DEFAULT_CREDS                    0x0010
#define SCH_CRED_AUTO_CRED_VALIDATION                0x0020
#define SCH_CRED_USE_DEFAULT_CREDS                   0x0040

/* ---- SCHANNEL_ family (1 names; R1) ---- */
#define SCHANNEL_CRED_VERSION                        0x0004

/* ---- SP_ family (6 names; R1) ---- */
#define SP_PROT_SSL2_SERVER                          0x0004
#define SP_PROT_SSL2_CLIENT                          0x0008
#define SP_PROT_SSL3_SERVER                          0x0010
#define SP_PROT_SSL3_CLIENT                          0x0020
#define SP_PROT_TLS1_SERVER                          0x0040
#define SP_PROT_TLS1_CLIENT                          0x0080

#endif /* AKARI_SCHNLSP_H */
