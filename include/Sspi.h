/*
 * Sspi.h -- Security Support Provider Interface (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE
 * documentation (learn.microsoft.com previous-versions archive;
 * page ids cited per record).  This is the "Security.h, Sspi.h."
 * and "Sspi.h." row set of the Security book harvest (M95a,
 * tools/manifests/security-book.manifest): 19 functions and 12
 * structures, plus the SSPI Handles carrier page (ms926453).
 * Every function page prints "Link Library: Secur32.lib"
 * (def/secur32-doc.def).
 *
 * Transcription notes:
 *   - The pages print the SEC_FAR qualifier and the SEC_ENTRY
 *     calling-convention spelling without defining either; SEC_FAR
 *     is defined empty (address-space decoration, R1 security.h
 *     agrees) and SEC_ENTRY empty (CE-wide cdecl, the project
 *     convention -- R1's WINAPI maps to the same code here).
 *   - SEC_CHAR / SEC_WCHAR / SECURITY_STATUS / TimeStamp have no
 *     dedicated CE type pages; declared as the carriers the
 *     prototypes need (own design, R1 security.h corroborates the
 *     shapes: char / wchar_t / long, SECURITY_INTEGER two-long).
 *   - SEC_GET_KEY_FN is only referenced as a parameter type
 *     (ms937013); declared as an unspecified callback pointer
 *     (R1 sspi.h spells it the same loose way).
 *   - ms926437 prints the DceInfo tag "_SecPkgContex_DceInfo"
 *     (missing 't') -- the misprint is kept in the tag, the type
 *     name is spelled correctly.
 *   - ms926441 prints the Names pointer alias lowercase
 *     ("*pSecPkgContext_Names"); normalized to the P convention.
 *   - ms926445 prints "typedefstruct" and "unsignedlong" glued;
 *     split for compilation, noted here.
 *   - ms926485 (SealMessage) prints a missing comma after fQOP and
 *     a trailing comma before the closing paren; both fixed.
 *   - ms926451 names the dispatch table type
 *     SECURITY_FUNCTION_TABLE_W / SecurityFunctionTableW, while the
 *     function pages print the unsuffixed PSecurityFunctionTable
 *     (ms926095); the unsuffixed spelling is provided as an alias.
 *     The member ORDER is the page's own print (26 slots incl.
 *     Reserved2..Reserved8); R1 sspi.h prints the same order.
 *     SealMessage / UnsealMessage are CE-book functions with no
 *     table slots -- the page table ends at DecryptMessage.
 */

#ifndef AKARI_SSPI_H
#define AKARI_SSPI_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* SSPI base spellings (pages print them without definitions)           */
/* ------------------------------------------------------------------ */

#define SEC_FAR                              /* address-space decoration */
#define SEC_ENTRY                            /* CE-wide cdecl */

typedef CHAR   SEC_CHAR;                     /* R1 security.h agrees */
typedef WCHAR  SEC_WCHAR;

typedef LONG   SECURITY_STATUS, *PSECURITY_STATUS;   /* own design,
    R1 security.h corroborates (long) */

/* ms926453 "SSPI Handles": the handle carriers, page syntax. */
typedef struct _SecHandle {
    ULONG_PTR dwLower;
    ULONG_PTR dwUpper;
} SecHandle, *PSecHandle;
typedef SecHandle CredHandle;
typedef PSecHandle PCredHandle;
typedef SecHandle CtxtHandle;
typedef PSecHandle PCtxtHandle;

/* TimeStamp carrier (no CE type page; own design, R1 shape). */
typedef struct _SECURITY_INTEGER {
    unsigned long LowPart;
    long HighPart;
} SECURITY_INTEGER;
typedef SECURITY_INTEGER TimeStamp, *PTimeStamp;

/* Unspecified credential-key callback (ms937013 parameter type). */
typedef void (*SEC_GET_KEY_FN)(void);

/* ------------------------------------------------------------------ */
/* Structures (page syntax; glued misprints split, noted above)         */
/* ------------------------------------------------------------------ */

/* ms926433 "SecBuffer". */
typedef struct _SecBuffer {
    ULONG cbBuffer;
    ULONG BufferType;
    PVOID pvBuffer;
} SecBuffer, *PSecBuffer;

/* ms926434 "SecBufferDesc". */
typedef struct _SecBufferDesc {
    ULONG ulVersion;
    ULONG cBuffers;
    PSecBuffer pBuffers;
} SecBufferDesc, *PSecBufferDesc;

/* ms926435 "SecPkgContext_Authority". */
typedef struct _SecPkgContext_Authority {
    SEC_CHAR SEC_FAR *sAuthorityName;
} SecPkgContext_Authority, *PSecPkgContext_Authority;

/* ms926437 "SecPkgContext_DceInfo" (tag misprint kept). */
typedef struct _SecPkgContex_DceInfo {
    ULONG AuthzSvc;
    PVOID SEC_FAR *pPac;
} SecPkgContext_DceInfo, *PSecPkgContext_DceInfo;

/* ms926439 "SecPkgContext_KeyInfo". */
typedef struct _SecPkgContext_KeyInfo {
    SEC_CHAR SEC_FAR *sSignatureAlgorithmName;
    SEC_CHAR SEC_FAR *sEncryptAlgorithmName;
    ULONG KeySize;
    ULONG SignatureAlgorithm;
    ULONG EncryptAlgorithm;
} SecPkgContext_KeyInfo, *PSecPkgContext_KeyInfo;

/* ms926440 "SecPkgContext_Lifespan". */
typedef struct _SecPkgContext_Lifespan {
    TimeStamp tsStart;
    TimeStamp tsExpiry;
} SecPkgContext_Lifespan, *PSecPkgContext_Lifespan;

/* ms926441 "SecPkgContext_Names". */
typedef struct _SecPkgContext_Names {
    SEC_CHAR SEC_FAR *sUserName;
} SecPkgContext_Names, *PSecPkgContext_Names;

/* ms926443 "SecPkgContext_Sizes". */
typedef struct _SecPkgContext_Sizes {
    ULONG cbMaxToken;
    ULONG cbMaxSignature;
    ULONG cbBlockSize;
    ULONG cbSecurityTrailer;
} SecPkgContext_Sizes, *PSecPkgContext_Sizes;

/* ms926445 "SecPkgContext_StreamSizes" (glued print split). */
typedef struct _SecPkgContext_StreamSizes {
    unsigned long cbHeader;
    unsigned long cbTrailer;
    unsigned long cbMaximumMessage;
    unsigned long cBuffers;
    unsigned long cbBlockSize;
} SecPkgContext_StreamSizes, *PSecPkgContext_StreamSizes;

/* ms926447 "SecPkgCredentials_Names". */
typedef struct _SecPkgCredentials_Names {
    SEC_CHAR SEC_FAR *sUserName;
} SecPkgCredentials_Names, *PSecPkgCredentials_Names;

/* ms926450 "SecPkgInfo". */
typedef struct _SecPkgInfo {
    ULONG fCapabilities;          /* SECPKG_FLAG_* names (no values) */
    USHORT wVersion;
    USHORT wRPCID;
    ULONG cbMaxToken;
    SEC_CHAR SEC_FAR *Name;
    SEC_CHAR SEC_FAR *Comment;
} SecPkgInfo, SEC_FAR *PSecPkgInfo;

/* ------------------------------------------------------------------ */
/* SecurityFunctionTable (ms926451; member order = page print)          */
/* ------------------------------------------------------------------ */

typedef SECURITY_STATUS (SEC_ENTRY *ENUMERATE_SECURITY_PACKAGES_FN_W)(
    PULONG, PSecPkgInfo SEC_FAR *);
typedef SECURITY_STATUS (SEC_ENTRY *QUERY_CREDENTIALS_ATTRIBUTES_FN_W)(
    PCredHandle, ULONG, PVOID);
typedef SECURITY_STATUS (SEC_ENTRY *ACQUIRE_CREDENTIALS_HANDLE_FN_W)(
    SEC_WCHAR SEC_FAR *, SEC_WCHAR SEC_FAR *, ULONG, VOID SEC_FAR *,
    VOID SEC_FAR *, SEC_GET_KEY_FN, VOID SEC_FAR *, PCredHandle,
    PTimeStamp);
typedef SECURITY_STATUS (SEC_ENTRY *FREE_CREDENTIALS_HANDLE_FN)(
    PCredHandle);
typedef SECURITY_STATUS (SEC_ENTRY *INITIALIZE_SECURITY_CONTEXT_FN_W)(
    PCredHandle, PCtxtHandle, SEC_WCHAR SEC_FAR *, ULONG, ULONG, ULONG,
    PSecBufferDesc, ULONG, PCtxtHandle, PSecBufferDesc, PULONG,
    PTimeStamp);
typedef SECURITY_STATUS (SEC_ENTRY *ACCEPT_SECURITY_CONTEXT_FN)(
    PCredHandle, PCtxtHandle, PSecBufferDesc, ULONG, ULONG,
    PCtxtHandle, PSecBufferDesc, PULONG, PTimeStamp);
typedef SECURITY_STATUS (SEC_ENTRY *COMPLETE_AUTH_TOKEN_FN)(
    PCtxtHandle, PSecBufferDesc);
typedef SECURITY_STATUS (SEC_ENTRY *DELETE_SECURITY_CONTEXT_FN)(
    PCtxtHandle);
typedef SECURITY_STATUS (SEC_ENTRY *APPLY_CONTROL_TOKEN_FN)(
    PCtxtHandle, PSecBufferDesc);
typedef SECURITY_STATUS (SEC_ENTRY *QUERY_CONTEXT_ATTRIBUTES_FN_W)(
    PCtxtHandle, ULONG, PVOID);
typedef SECURITY_STATUS (SEC_ENTRY *IMPERSONATE_SECURITY_CONTEXT_FN)(
    PCtxtHandle);                 /* table-only member: no CE function
                                     page; shape R1 sspi.h (ABI fact) */
typedef SECURITY_STATUS (SEC_ENTRY *REVERT_SECURITY_CONTEXT_FN)(
    PCtxtHandle);                 /* table-only, same note */
typedef SECURITY_STATUS (SEC_ENTRY *MAKE_SIGNATURE_FN)(
    PCtxtHandle, ULONG, PSecBufferDesc, ULONG);
typedef SECURITY_STATUS (SEC_ENTRY *VERIFY_SIGNATURE_FN)(
    PCtxtHandle, PSecBufferDesc, ULONG, PULONG);
typedef SECURITY_STATUS (SEC_ENTRY *FREE_CONTEXT_BUFFER_FN)(
    VOID SEC_FAR *);
typedef SECURITY_STATUS (SEC_ENTRY *QUERY_SECURITY_PACKAGE_INFO_FN_W)(
    SEC_WCHAR SEC_FAR *, PSecPkgInfo SEC_FAR *);
typedef SECURITY_STATUS (SEC_ENTRY *QUERY_SECURITY_CONTEXT_TOKEN_FN)(
    PCtxtHandle, VOID SEC_FAR * SEC_FAR *);   /* table-only, R1 shape */
typedef SECURITY_STATUS (SEC_ENTRY *ENCRYPT_MESSAGE_FN)(
    PCtxtHandle, ULONG, PSecBufferDesc, ULONG);
typedef SECURITY_STATUS (SEC_ENTRY *DECRYPT_MESSAGE_FN)(
    PCtxtHandle, PSecBufferDesc, ULONG, PULONG);

/* ms926451 "SecurityFunctionTable" -- the W-form dispatch table, in
 * the page's own member order (R1 sspi.h prints the same order). */
typedef struct _SECURITY_FUNCTION_TABLE_W {
    unsigned long dwVersion;
    ENUMERATE_SECURITY_PACKAGES_FN_W EnumerateSecurityPackagesW;
    QUERY_CREDENTIALS_ATTRIBUTES_FN_W QueryCredentialsAttributesW;
    ACQUIRE_CREDENTIALS_HANDLE_FN_W AcquireCredentialsHandleW;
    FREE_CREDENTIALS_HANDLE_FN FreeCredentialsHandle;
    VOID SEC_FAR *Reserved2;
    INITIALIZE_SECURITY_CONTEXT_FN_W InitializeSecurityContextW;
    ACCEPT_SECURITY_CONTEXT_FN AcceptSecurityContext;
    COMPLETE_AUTH_TOKEN_FN CompleteAuthToken;
    DELETE_SECURITY_CONTEXT_FN DeleteSecurityContext;
    APPLY_CONTROL_TOKEN_FN ApplyControlToken;
    QUERY_CONTEXT_ATTRIBUTES_FN_W QueryContextAttributesW;
    IMPERSONATE_SECURITY_CONTEXT_FN ImpersonateSecurityContext;
    REVERT_SECURITY_CONTEXT_FN RevertSecurityContext;
    MAKE_SIGNATURE_FN MakeSignature;
    VERIFY_SIGNATURE_FN VerifySignature;
    FREE_CONTEXT_BUFFER_FN FreeContextBuffer;
    QUERY_SECURITY_PACKAGE_INFO_FN_W QuerySecurityPackageInfoW;
    VOID SEC_FAR *Reserved3;
    VOID SEC_FAR *Reserved4;
    VOID SEC_FAR *Reserved5;
    VOID SEC_FAR *Reserved6;
    VOID SEC_FAR *Reserved7;
    VOID SEC_FAR *Reserved8;
    QUERY_SECURITY_CONTEXT_TOKEN_FN QuerySecurityContextToken;
    ENCRYPT_MESSAGE_FN EncryptMessage;
    DECRYPT_MESSAGE_FN DecryptMessage;
} SecurityFunctionTableW, SEC_FAR *PSecurityFunctionTableW;

/* The unsuffixed spelling the function pages print (ms926095). */
typedef SecurityFunctionTableW SecurityFunctionTable;
typedef PSecurityFunctionTableW PSecurityFunctionTable;

/* ------------------------------------------------------------------ */
/* SSPI functions (Secur32.lib)                                         */
/* ------------------------------------------------------------------ */

/* ms937012 "AcceptSecurityContext". */
AKARI_CE_IMPORT SECURITY_STATUS SEC_ENTRY AcceptSecurityContext(
    PCredHandle phCredential, PCtxtHandle phContext,
    PSecBufferDesc pInput, ULONG fContextReq, ULONG TargetDataRep,
    PCtxtHandle phNewContext, PSecBufferDesc pOutput,
    ULONG SEC_FAR *pfContextAttr, PTimeStamp ptsExpiry)
    AKARI_CE_NAME(AcceptSecurityContext);

/* ms937013 "AcquireCredentialsHandle". */
AKARI_CE_IMPORT SECURITY_STATUS SEC_ENTRY AcquireCredentialsHandle(
    SEC_WCHAR SEC_FAR *pszPrincipal, SEC_WCHAR SEC_FAR *pszPackage,
    ULONG fCredentialUse, VOID SEC_FAR *pvLogonId,
    VOID SEC_FAR *pAuthData, SEC_GET_KEY_FN pGetKeyFn,
    VOID SEC_FAR *pvGetKeyArgument, PCredHandle phCredential,
    PTimeStamp ptsExpiry)
    AKARI_CE_NAME(AcquireCredentialsHandle);

/* ms937015 "ApplyControlToken". */
AKARI_CE_IMPORT SECURITY_STATUS SEC_ENTRY ApplyControlToken(
    PCtxtHandle phContext, PSecBufferDesc pInput)
    AKARI_CE_NAME(ApplyControlToken);

/* ms937725 "CompleteAuthToken". */
AKARI_CE_IMPORT SECURITY_STATUS SEC_ENTRY CompleteAuthToken(
    PCtxtHandle phContext, PSecBufferDesc pToken)
    AKARI_CE_NAME(CompleteAuthToken);

/* ms938416 "DecryptMessage". */
AKARI_CE_IMPORT SECURITY_STATUS SEC_ENTRY DecryptMessage(
    PCtxtHandle phContext, PSecBufferDesc pMessage, ULONG MessageSeqNo,
    PULONG pfQOP) AKARI_CE_NAME(DecryptMessage);

/* ms906494 "DeleteSecurityContext". */
AKARI_CE_IMPORT SECURITY_STATUS SEC_ENTRY DeleteSecurityContext(
    PCtxtHandle phContext) AKARI_CE_NAME(DeleteSecurityContext);

/* ms906502 "EncryptMessage". */
AKARI_CE_IMPORT SECURITY_STATUS SEC_ENTRY EncryptMessage(
    PCtxtHandle phContext, ULONG fQOP, PSecBufferDesc pMessage,
    ULONG MessageSeqNo) AKARI_CE_NAME(EncryptMessage);

/* ms906509 "EnumerateSecurityPackages". */
AKARI_CE_IMPORT SECURITY_STATUS SEC_ENTRY EnumerateSecurityPackages(
    ULONG SEC_FAR *pcPackages, PSecPkgInfo SEC_FAR *ppPackageInfo)
    AKARI_CE_NAME(EnumerateSecurityPackages);

/* ms906515 "FreeContextBuffer". */
AKARI_CE_IMPORT SECURITY_STATUS SEC_ENTRY FreeContextBuffer(
    VOID SEC_FAR *pvContextBuffer) AKARI_CE_NAME(FreeContextBuffer);

/* ms906519 "FreeCredentialsHandle". */
AKARI_CE_IMPORT SECURITY_STATUS SEC_ENTRY FreeCredentialsHandle(
    PCredHandle phCredential) AKARI_CE_NAME(FreeCredentialsHandle);

/* ms926095 "InitSecurityInterface". */
AKARI_CE_IMPORT PSecurityFunctionTable SEC_ENTRY InitSecurityInterface(
    void) AKARI_CE_NAME(InitSecurityInterface);

/* ms926002 "InitializeSecurityContext" (signature from the page;
 * the row parser missed it -- long flag tables). */
AKARI_CE_IMPORT SECURITY_STATUS SEC_ENTRY InitializeSecurityContext(
    PCredHandle phCredential, PCtxtHandle phContext,
    SEC_WCHAR SEC_FAR *pszTargetName, ULONG fContextReq, ULONG Reserved1,
    ULONG TargetDataRep, PSecBufferDesc pInput, ULONG Reserved2,
    PCtxtHandle phNewContext, PSecBufferDesc pOutput,
    ULONG SEC_FAR *pfContextAttr, PTimeStamp ptsExpiry)
    AKARI_CE_NAME(InitializeSecurityContext);

/* ms926142 "MakeSignature". */
AKARI_CE_IMPORT SECURITY_STATUS SEC_ENTRY MakeSignature(
    PCtxtHandle phContext, ULONG fQOP, PSecBufferDesc pMessage,
    ULONG MessageSeqNo) AKARI_CE_NAME(MakeSignature);

/* ms938456 "QueryContextAttributes". */
AKARI_CE_IMPORT SECURITY_STATUS SEC_ENTRY QueryContextAttributes(
    PCtxtHandle phContext, ULONG ulAttribute, VOID SEC_FAR *pBuffer)
    AKARI_CE_NAME(QueryContextAttributes);

/* ms938459 "QueryCredentialsAttributes". */
AKARI_CE_IMPORT SECURITY_STATUS SEC_ENTRY QueryCredentialsAttributes(
    PCredHandle phCredential, ULONG ulAttribute, VOID SEC_FAR *pBuffer)
    AKARI_CE_NAME(QueryCredentialsAttributes);

/* ms938462 "QuerySecurityPackageInfo". */
AKARI_CE_IMPORT SECURITY_STATUS SEC_ENTRY QuerySecurityPackageInfo(
    SEC_WCHAR SEC_FAR *pszPackageName, PSecPkgInfo SEC_FAR *ppPackageInfo)
    AKARI_CE_NAME(QuerySecurityPackageInfo);

/* ms926485 "SealMessage" (missing/trailing commas fixed, noted). */
AKARI_CE_IMPORT SECURITY_STATUS SEC_ENTRY SealMessage(
    PCtxtHandle phContext, ULONG fQOP, PSecBufferDesc pMessage,
    ULONG MessageSeqNo) AKARI_CE_NAME(SealMessage);

/* ms926486 "UnsealMessage". */
AKARI_CE_IMPORT SECURITY_STATUS SEC_ENTRY UnsealMessage(
    PCtxtHandle phContext, PSecBufferDesc pMessage, ULONG MessageSeqNo,
    ULONG *pfQOP) AKARI_CE_NAME(UnsealMessage);

/* ms926455 "VerifySignature". */
AKARI_CE_IMPORT SECURITY_STATUS SEC_ENTRY VerifySignature(
    PCtxtHandle phContext, PSecBufferDesc pMessage, ULONG MessageSeqNo,
    ULONG SEC_FAR *pfQOP) AKARI_CE_NAME(VerifySignature);

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

/* ---- ASC_ family (13 names; R1) ---- */
#define ASC_REQ_DELEGATE                             0x0001
#define ASC_REQ_MUTUAL_AUTH                          0x0002
#define ASC_REQ_REPLAY_DETECT                        0x0004
#define ASC_REQ_SEQUENCE_DETECT                      0x0008
#define ASC_REQ_CONFIDENTIALITY                      0x0010
#define ASC_REQ_USE_SESSION_KEY                      0x0020
#define ASC_REQ_ALLOCATE_MEMORY                      0x0100
#define ASC_REQ_USE_DCE_STYLE                        0x0200
#define ASC_REQ_DATAGRAM                             0x0400
#define ASC_REQ_CONNECTION                           0x0800
#define ASC_REQ_EXTENDED_ERROR                       0x8000
#define ASC_REQ_STREAM                               0x10000
#define ASC_REQ_INTEGRITY                            0x20000

/* ---- ISC_ family (16 names; R1) ---- */
#define ISC_REQ_DELEGATE                             0x0001
#define ISC_REQ_MUTUAL_AUTH                          0x0002
#define ISC_REQ_REPLAY_DETECT                        0x0004
#define ISC_REQ_SEQUENCE_DETECT                      0x0008
#define ISC_REQ_CONFIDENTIALITY                      0x0010
#define ISC_REQ_USE_SESSION_KEY                      0x0020
#define ISC_REQ_PROMPT_FOR_CREDS                     0x0040
#define ISC_REQ_USE_SUPPLIED_CREDS                   0x0080
#define ISC_REQ_ALLOCATE_MEMORY                      0x0100
#define ISC_REQ_USE_DCE_STYLE                        0x0200
#define ISC_REQ_DATAGRAM                             0x0400
#define ISC_REQ_CONNECTION                           0x0800
#define ISC_REQ_EXTENDED_ERROR                       0x4000
#define ISC_RET_EXTENDED_ERROR                       0x4000
#define ISC_REQ_STREAM                               0x8000
#define ISC_REQ_INTEGRITY                            0x10000

/* ---- SEC_ family (18 names; R1) ---- */
#define SEC_E_INSUFFICIENT_MEMORY                    (-2146893056)
#define SEC_E_INVALID_HANDLE                         (-2146893055)
#define SEC_E_TARGET_UNKNOWN                         (-2146893053)
#define SEC_E_INTERNAL_ERROR                         (-2146893052)
#define SEC_E_SECPKG_NOT_FOUND                       (-2146893051)
#define SEC_E_NOT_OWNER                              (-2146893050)
#define SEC_E_INVALID_TOKEN                          (-2146893048)
#define SEC_E_QOP_NOT_SUPPORTED                      (-2146893046)
#define SEC_E_LOGON_DENIED                           (-2146893044)
#define SEC_E_UNKNOWN_CREDENTIALS                    (-2146893043)
#define SEC_E_NO_CREDENTIALS                         (-2146893042)
#define SEC_E_NO_AUTHENTICATING_AUTHORITY            (-2146893039)
#define SEC_E_INCOMPLETE_MESSAGE                     (-2146893032)
#define SEC_E_OK                                     0x0000
#define SEC_I_CONTINUE_NEEDED                        0x90312
#define SEC_I_COMPLETE_NEEDED                        0x90313
#define SEC_I_COMPLETE_AND_CONTINUE                  0x90314
#define SEC_I_RENEGOTIATE                            0x90321

/* ---- SECBUFFER_ family (11 names; R1) ---- */
#define SECBUFFER_EMPTY                              0x0000
#define SECBUFFER_VERSION                            0x0000
#define SECBUFFER_DATA                               0x0001
#define SECBUFFER_TOKEN                              0x0002
#define SECBUFFER_PKG_PARAMS                         0x0003
#define SECBUFFER_MISSING                            0x0004
#define SECBUFFER_EXTRA                              0x0005
#define SECBUFFER_STREAM_TRAILER                     0x0006
#define SECBUFFER_STREAM_HEADER                      0x0007
#define SECBUFFER_STREAM                             0x000A
#define SECBUFFER_READONLY                           0x80000000

/* ---- SECPKG_ family (29 names; R1) ---- */
#define SECPKG_ATTR_SIZES                            0x0000
#define SECPKG_ATTR_NAMES                            0x0001
#define SECPKG_CRED_ATTR_NAMES                       0x0001
#define SECPKG_CRED_INBOUND                          0x0001
#define SECPKG_FLAG_INTEGRITY                        0x0001
#define SECPKG_ATTR_LIFESPAN                         0x0002
#define SECPKG_CRED_OUTBOUND                         0x0002
#define SECPKG_FLAG_PRIVACY                          0x0002
#define SECPKG_CRED_BOTH                             0x0003
#define SECPKG_ATTR_STREAM_SIZES                     0x0004
#define SECPKG_FLAG_TOKEN_ONLY                       0x0004
#define SECPKG_ATTR_KEY_INFO                         0x0005
#define SECPKG_ATTR_AUTHORITY                        0x0006
#define SECPKG_ATTR_PROTO_INFO                       0x0007
#define SECPKG_FLAG_DATAGRAM                         0x0008
#define SECPKG_FLAG_CONNECTION                       0x0010
#define SECPKG_FLAG_MULTI_REQUIRED                   0x0020
#define SECPKG_FLAG_CLIENT_ONLY                      0x0040
#define SECPKG_ATTR_ISSUER_LIST                      0x0050
#define SECPKG_ATTR_REMOTE_CRED                      0x0051
#define SECPKG_ATTR_LOCAL_CRED                       0x0052
#define SECPKG_ATTR_REMOTE_CERT_CONTEXT              0x0053
#define SECPKG_ATTR_LOCAL_CERT_CONTEXT               0x0054
#define SECPKG_ATTR_ISSUER_LIST_EX                   0x0059
#define SECPKG_ATTR_CONNECTION_INFO                  0x005A
#define SECPKG_FLAG_EXTENDED_ERROR                   0x0080
#define SECPKG_FLAG_IMPERSONATION                    0x0100
#define SECPKG_FLAG_ACCEPT_WIN32_NAME                0x0200
#define SECPKG_FLAG_STREAM                           0x0400

/* ---- SECURITY_ family (1 names; R1) ---- */
#define SECURITY_NATIVE_DREP                         0x0010

#endif /* AKARI_SSPI_H */
