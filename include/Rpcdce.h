/*
 * Rpcdce.h -- RPC client/common carrier used by SSPI (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE
 * documentation (learn.microsoft.com previous-versions archive;
 * page ids cited per record).  The RPC DCE function surface is not
 * part of any harvested book yet; this file currently carries the
 * one Rpcdce.h-homed row of the Security book (M95): the
 * authentication-identity structure passed to AcquireCredentialsHandle.
 *
 * Transcription notes:
 *   - ms926452 prints _RPC_FAR qualifiers and glued member spacing;
 *     the carriers are declared with the same shapes.
 *   - The page names SEC_WINNT_AUTH_IDENTITY_ANSI /
 *     SEC_WINNT_AUTH_IDENTITY_UNICODE (flag values for the Flags
 *     member) without printing values; adopted from R1 rpcdce.h in
 *     the M96 section below (public domain).
 */

#ifndef AKARI_RPCDCE_H
#define AKARI_RPCDCE_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _RPC_FAR                            /* page decoration */

/* ms926452 "SEC_WINNT_AUTH_IDENTITY" (Windows CE 2.0 and later). */
typedef struct _SEC_WINNT_AUTH_IDENTITY {
    unsigned short _RPC_FAR *User;
    unsigned long UserLength;
    unsigned short _RPC_FAR *Domain;
    unsigned long DomainLength;
    unsigned long _RPC_FAR *Password;
    unsigned long PasswordLength;
    unsigned long Flags;         /* SEC_WINNT_AUTH_IDENTITY_* (M96) */
} SEC_WINNT_AUTH_IDENTITY, *PSEC_WINNT_AUTH_IDENTITY;

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

/* ---- SEC_WINNT_AUTH_IDENTITY_ family (2 names; R1) ---- */
#define SEC_WINNT_AUTH_IDENTITY_ANSI                 0x0001
#define SEC_WINNT_AUTH_IDENTITY_UNICODE              0x0002

#ifdef __cplusplus
}
#endif

#endif /* AKARI_RPCDCE_H */
