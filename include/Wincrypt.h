/*
 * Windows CE Cryptography API -- base CSP unit
 *
 * Header of record for every page of this unit (CE 5.0 archive): Wincrypt.h
 * (see the Requirements row of each ms937014/ms937733/... page).
 *
 * Scope (MSDN catalog Windows CE 5.0, book "Cryptography"):
 *   - ALG_ID (ms937014), HCRYPTHASH (ms906535), HCRYPTKEY (ms906545),
 *     HCRYPTPROV (ms925987)
 *   - BLOB (Cryptography) (ms937016) -- _CRYPTOAPI_BLOB + all documented
 *     alias names (DATA_BLOB et al.)
 *   - CMSG_STREAM_INFO (ms937724), VTableProvStruc (ms926457)
 *   - CPAcquireContext (ms937726) -- CSP-authoring entry point; its page
 *     lists "Link Library: Developer defined." so it is declared but is
 *     NOT a coredll import (provider DLLs export it).
 *   - 42 Crypt* functions, all "Link Library: Coredll.lib"
 *     (CryptAcquireContext ms937733 ... CryptVerifySignature ms938383,
 *     incl. the CryptMsg* family and CryptProtectData/CryptUnprotectData).
 *   - Certificate store / encode-OID / PFX unit (M48): 83 functions,
 *     all "Link Library: Crypt32.lib" (CertAddCertificateContextToStore
 *     ms937018 ... PFXVerifyPassword ms926241), plus the CERT_* /
 *     CMSG_* / CRYPT_* structure trees and the callback pointer types.
 *
 * Transcription notes:
 *   - The CE archive prints the calling-convention qualifier CRYPTFUNC
 *     (or WINAPI) on these prototypes. Windows CE has a single calling
 *     convention, so both are empty; declarations follow the repository
 *     model and omit the qualifier (CRYPTFUNC is provided as a no-op
 *     macro for fidelity).
 *   - Numeric values (PROV_*, AT_*, CALG_*, HP_*, KP_*, PP_*,
 *     CRYPT_VERIFYCONTEXT, CRYPTPROTECT_* flags, CMSG_* parameter ids,
 *     CERT_* prop/encoding-type ids) are absent from the public CE
 *     archive -- names only, no defines.
 *   - Spelling as printed: CryptExportKey's last parameter is
 *     pdwbDataLen (ms938025); ms938096 prints the lowercase variant
 *     "CryptGethashParam" -- the topic title CryptGetHashParam is the
 *     declared name (title-print fix-ups, same model as M44).
 *   - A few layouts in the archive print incomplete/aliased struct
 *     tails (CERT_SIGNED_CONTENT_INFO ms937701, CMSG_SIGNED_ENCODE_INFO
 *     ms937721) or reuse a sibling name (CMSG_HASHED_ENCODE_INFO
 *     ms937719 prints the ENVELOPED tag); each is completed from the
 *     same page print and noted at the typedef.  Pointer members whose
 *     target has no layout page in the CE archive are forward-declared
 *     (documented design decision), keeping every documented struct
 *     complete.
 */
#ifndef _WINCRYPT_H
#define _WINCRYPT_H

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Calling-convention qualifier printed by the CE crypto pages; empty on
 * CE (single calling convention), same as WINAPI. */
#ifndef CRYPTFUNC
#define CRYPTFUNC WINAPI
#endif

/* ------------------------------------------------------------------ */
/* Fundamental crypto types (all documented verbatim).                 */
/* ------------------------------------------------------------------ */

/* ms937014: "typedef unsigned int ALG_ID;" */
typedef unsigned int ALG_ID;

/* ms906535: "typedef unsigned long HCRYPTHASH;" */
typedef unsigned long HCRYPTHASH;

/* ms906545: "typedef unsigned long HCRYPTKEY;" */
typedef unsigned long HCRYPTKEY;

/* ms925987: "typedef unsigned long HCRYPTPROV;" */
typedef unsigned long HCRYPTPROV;

/* HCRYPTMSG has no dedicated data-type page in the CE archive; the
 * CryptMsg* prototypes (ms938232, ms938239, ms938251, ms938271, ...)
 * pass and return it. Handle-carrier design, per the repository model. */
typedef ULONG_PTR HCRYPTMSG;

/* ms937016 BLOB (Cryptography): tag _CRYPTOAPI_BLOB with the 13
 * documented alias typedef names (no self-named CRYPTOAPI_BLOB
 * typedef is printed on the page). */
typedef struct _CRYPTOAPI_BLOB {
    DWORD   cbData;
    BYTE   *pbData;
} CRYPT_INTEGER_BLOB, *PCRYPT_INTEGER_BLOB,
  CRYPT_UINT_BLOB, *PCRYPT_UINT_BLOB,
  CRYPT_OBJID_BLOB, *PCRYPT_OBJID_BLOB,
  CERT_NAME_BLOB, *PCERT_NAME_BLOB,
  CERT_RDN_VALUE_BLOB, *PCERT_RDN_VALUE_BLOB,
  CERT_BLOB, *PCERT_BLOB,
  CRL_BLOB, *PCRL_BLOB,
  DATA_BLOB, *PDATA_BLOB,
  CRYPT_DATA_BLOB, *PCRYPT_DATA_BLOB,
  CRYPT_HASH_BLOB, *PCRYPT_HASH_BLOB,
  CRYPT_DIGEST_BLOB, *PCRYPT_DIGEST_BLOB,
  CRYPT_DER_BLOB, *PCRYPT_DER_BLOB,
  CRYPT_ATTR_BLOB, *PCRYPT_ATTR_BLOB;

/* ms937724 CMSG_STREAM_INFO; the page documents the callback shape:
 * BOOL WINAPI CmsgStreamOutputCallback(const void *pvArg, BYTE *pbData,
 *                                      DWORD cbData, BOOL fFinal); */
typedef BOOL (WINAPI *PFN_CMSG_STREAM_OUTPUT)(const void *pvArg,
                                              BYTE *pbData,
                                              DWORD cbData,
                                              BOOL fFinal);

typedef struct _CMSG_STREAM_INFO {
    DWORD                   cbContent;
    PFN_CMSG_STREAM_OUTPUT  pfnStreamOutput;
    void                   *pvArg;
} CMSG_STREAM_INFO, *PCMSG_STREAM_INFO;

/* ms926457 VTableProvStruc (Windows CE: Version member is 3). */
typedef struct _VTableProvStruc {
    DWORD    Version;
    FARPROC  FuncVerifyImage;
    FARPROC  FuncReturnhWnd;
    DWORD    dwProvType;
    BYTE    *pbContextInfo;
    DWORD    cbContextInfo;
    LPWSTR   pszProvName;
} VTableProvStruc, *PVTableProvStruc;

/* ------------------------------------------------------------------ */
/* Certificate / message unit (M48/M49) -- every typedef below is     */
/* transcribed from the official CE 5.0 structure page cited in the    */
/* comment (tools/manifests/crypt-structs.manifest harvest).           */
/* ------------------------------------------------------------------ */

/* Handle carriers with no dedicated data-type page in the CE archive;
 * the Cert and Crypt prototypes pass and return them (repository
 * handle-carrier design, same as HCRYPTMSG above). */
typedef ULONG_PTR HCERTSTORE;         /* CertOpenStore ms937683 ... */
typedef ULONG_PTR HCERTCHAINENGINE;   /* CertGetCertificateChain ms937660 */
typedef ULONG_PTR HCRYPTOIDFUNCSET;   /* CryptInitOIDFunctionSet ms938191 */
typedef ULONG_PTR HCRYPTOIDFUNCADDR;  /* CryptGetOIDFunctionAddress ms938109 */
typedef ULONG_PTR HCRYPTDEFAULTCONTEXT; /* CryptInstallDefaultContext ms938197 */

/* ms937736 */
typedef struct _CRYPT_BIT_BLOB {
    DWORD   cbData;
    BYTE   *pbData;
    DWORD   cUnusedBits;
} CRYPT_BIT_BLOB, *PCRYPT_BIT_BLOB;

/* ms937734 */
typedef struct _CRYPT_ALGORITHM_IDENTIFIER {
    LPSTR           pszObjId;
    CRYPT_OBJID_BLOB Parameters;
} CRYPT_ALGORITHM_IDENTIFIER, *PCRYPT_ALGORITHM_IDENTIFIER;

/* ms937735 */
typedef struct _CRYPT_ATTRIBUTE {
    LPSTR            pszObjId;
    DWORD            cValue;
    PCRYPT_ATTR_BLOB rgValue;
} CRYPT_ATTRIBUTE, *PCRYPT_ATTRIBUTE;

/* ms938388 (CMSG_ATTR is the documented alias). */
typedef struct _CRYPT_ATTRIBUTES {
    DWORD           cAttr;
    PCRYPT_ATTRIBUTE rgAttr;
} CRYPT_ATTRIBUTES, *PCRYPT_ATTRIBUTES, CMSG_ATTR;

/* ms938221 */
typedef struct _CRYPT_KEY_PROV_PARAM {
    DWORD  dwParam;
    BYTE  *pbData;
    DWORD  cbData;
    DWORD  dwFlags;
} CRYPT_KEY_PROV_PARAM, *PCRYPT_KEY_PROV_PARAM;

/* ms938212 */
typedef struct _CRYPT_KEY_PROV_INFO {
    LPWSTR               pwszContainerName;
    LPWSTR               pwszProvName;
    DWORD                dwProvType;
    DWORD                dwFlags;
    DWORD                cProvParam;
    PCRYPT_KEY_PROV_PARAM rgProvParam;
    DWORD                dwKeySpec;
} CRYPT_KEY_PROV_INFO, *PCRYPT_KEY_PROV_INFO;

/* ms938293 */
typedef struct _CRYPT_OID_FUNC_ENTRY {
    LPCSTR  pszOID;
    void   *pvFuncAddr;
} CRYPT_OID_FUNC_ENTRY, *PCRYPT_OID_FUNC_ENTRY;

/* ms938300 */
typedef struct _CRYPT_OID_INFO {
    DWORD    cbSize;
    LPCSTR   pszOID;
    LPCWSTR  pwszName;
    DWORD    dwGroupId;
    union {
        DWORD   dwValue;
        ALG_ID  Algid;
        DWORD   dwLength;
    };
    CRYPT_DATA_BLOB ExtraInfo;
} CRYPT_OID_INFO, *PCRYPT_OID_INFO;
typedef const CRYPT_OID_INFO CCRYPT_OID_INFO, *PCCRYPT_OID_INFO;

/* ms925995 (tag printed _HMAC_Info). */
typedef struct _HMAC_Info {
    ALG_ID  HashAlgid;
    BYTE   *pbInnerString;
    DWORD   cbInnerString;
    BYTE   *pbOuterString;
    DWORD   cbOuterString;
} HMAC_INFO, *PHMAC_INFO;

/* ms906557 */
typedef struct _PROV_ENUMALGS {
    ALG_ID  aiAlgid;
    DWORD   dwBitLen;
    DWORD   dwNameLen;
    WCHAR   szName[20];
} PROV_ENUMALGS;

/* ms938451 */
typedef struct _PROV_ENUMALGS_EX {
    ALG_ID  aiAlgid;
    DWORD   dwDefaultLen;
    DWORD   dwMinLen;
    DWORD   dwMaxLen;
    DWORD   dwProtocols;
    DWORD   dwNameLen;
    WCHAR   szName[20];
    DWORD   dwLongNameLen;
    WCHAR   szLongName[40];
} PROV_ENUMALGS_EX;

/* ms938453 (BLOBHEADER is the documented alias). */
typedef struct _PUBLICKEYSTRUC {
    BYTE    bType;
    BYTE    bVersion;
    WORD    reserved;
    ALG_ID  aiKeyAlg;
} BLOBHEADER, PUBLICKEYSTRUC;

/* ms938465 */
typedef struct _RSAPUBKEY {
    DWORD  magic;
    DWORD  bitlen;
    DWORD  pubexp;
} RSAPUBKEY;

/* ms938410 (CTL_USAGE aliases CERT_ENHKEY_USAGE). */
typedef struct _CTL_USAGE {
    DWORD   cUsageIdentifier;
    LPSTR  *rgpszUsageIdentifier;
} CTL_USAGE, *PCTL_USAGE, CERT_ENHKEY_USAGE, *PCERT_ENHKEY_USAGE;

/* ms937707 */
typedef struct _CERT_TRUST_STATUS {
    DWORD  dwErrorStatus;
    DWORD  dwInfoStatus;
} CERT_TRUST_STATUS, *PCERT_TRUST_STATUS;

/* ms937651 */
typedef struct _CERT_EXTENSION {
    LPSTR            pszObjId;
    BOOL             fCritical;
    CRYPT_OBJID_BLOB Value;
} CERT_EXTENSION, *PCERT_EXTENSION;

/* ms937675 */
typedef struct _CERT_ISSUER_SERIAL_NUMBER {
    CERT_NAME_BLOB     Issuer;
    CRYPT_INTEGER_BLOB SerialNumber;
} CERT_ISSUER_SERIAL_NUMBER, *PCERT_ISSUER_SERIAL_NUMBER;

/* ms937689 */
typedef struct _CERT_PRIVATE_KEY_VALIDITY {
    FILETIME  NotBefore;
    FILETIME  NotAfter;
} CERT_PRIVATE_KEY_VALIDITY, *PCERT_PRIVATE_KEY_VALIDITY;

/* ms937690 */
typedef struct _CERT_PUBLIC_KEY_INFO {
    CRYPT_ALGORITHM_IDENTIFIER  Algorithm;
    CRYPT_BIT_BLOB              PublicKey;
} CERT_PUBLIC_KEY_INFO, *PCERT_PUBLIC_KEY_INFO;

/* ms937672 -- completing the M47 hold. */
typedef struct _CERT_INFO {
    DWORD                    dwVersion;
    CRYPT_INTEGER_BLOB       SerialNumber;
    CRYPT_ALGORITHM_IDENTIFIER SignatureAlgorithm;
    CERT_NAME_BLOB           Issuer;
    FILETIME                 NotBefore;
    FILETIME                 NotAfter;
    CERT_NAME_BLOB           Subject;
    CERT_PUBLIC_KEY_INFO     SubjectPublicKeyInfo;
    CRYPT_BIT_BLOB           IssuerUniqueId;
    CRYPT_BIT_BLOB           SubjectUniqueId;
    DWORD                    cExtension;
    PCERT_EXTENSION          rgExtension;
} CERT_INFO, *PCERT_INFO;

/* ms937040 */
typedef struct _CERT_CONTEXT {
    DWORD       dwCertEncodingType;
    BYTE       *pbCertEncoded;
    DWORD       cbCertEncoded;
    PCERT_INFO  pCertInfo;
    HCERTSTORE  hCertStore;
} CERT_CONTEXT, *PCERT_CONTEXT;
typedef const CERT_CONTEXT *PCCERT_CONTEXT;

/* ms937692 / ms937691 / ms937680 */
typedef struct _CERT_RDN_ATTR {
    LPSTR                 pszObjId;
    DWORD                 dwValueType;
    CERT_RDN_VALUE_BLOB   Value;
} CERT_RDN_ATTR, *PCERT_RDN_ATTR;

typedef struct _CERT_RDN {
    DWORD           cRDNAttr;
    PCERT_RDN_ATTR  rgRDNAttr;
} CERT_RDN, *PCERT_RDN;

typedef struct _CERT_NAME_INFO {
    DWORD      cRDN;
    PCERT_RDN  rgRDN;
} CERT_NAME_INFO, *PCERT_NAME_INFO;

/* ms937688 / ms937686 / ms937687 / ms937685 */
typedef struct _CERT_POLICY_QUALIFIER_INFO {
    LPSTR            pszPolicyQualifierId;
    CRYPT_OBJID_BLOB Qualifier;
} CERT_POLICY_QUALIFIER_INFO, *PCERT_POLICY_QUALIFIER_INFO;

typedef struct _CERT_POLICY_ID {
    DWORD    cCertPolicyElementId;
    LPSTR   *rgpszCertPolicyElementId;
} CERT_POLICY_ID, *PCERT_POLICY_ID;

typedef struct _CERT_POLICY_INFO {
    LPSTR                       pszPolicyIdentifier;
    DWORD                       cPolicyQualifier;
    CERT_POLICY_QUALIFIER_INFO *rgPolicyQualifier;
} CERT_POLICY_INFO, *PCERT_POLICY_INFO;

typedef struct _CERT_POLICIES_INFO {
    DWORD             cPolicyInfo;
    CERT_POLICY_INFO *rgPolicyInfo;
} CERT_POLICIES_INFO, *PCERT_POLICIES_INFO;

/* ms937676 */
typedef struct _CERT_KEY_ATTRIBUTES_INFO {
    CRYPT_DATA_BLOB             KeyId;
    CRYPT_BIT_BLOB              IntendedKeyUsage;
    PCERT_PRIVATE_KEY_VALIDITY  pPrivateKeyUsagePeriod;
} CERT_KEY_ATTRIBUTES_INFO, *PCERT_KEY_ATTRIBUTES_INFO;

/* ms937677 */
typedef struct _CERT_KEY_CONTEXT {
    DWORD       cbSize;
    HCRYPTPROV  hCryptProv;
    DWORD       dwKeySpec;
} CERT_KEY_CONTEXT, *PCERT_KEY_CONTEXT;

/* ms937679 */
typedef struct _CERT_KEY_USAGE_RESTRICTION_INFO {
    DWORD            cCertPolicyId;
    PCERT_POLICY_ID  rgCertPolicyId;
    CRYPT_BIT_BLOB   RestrictedKeyUsage;
} CERT_KEY_USAGE_RESTRICTION_INFO, *PCERT_KEY_USAGE_RESTRICTION_INFO;

/* ms937678 */
typedef struct _CERT_KEYGEN_REQUEST_INFO {
    DWORD                 dwVersion;
    CERT_PUBLIC_KEY_INFO  SubjectPublicKeyInfo;
    LPWSTR                pwszChallengeString;
} CERT_KEYGEN_REQUEST_INFO, *PCERT_KEYGEN_REQUEST_INFO;

/* ms937671 */
typedef struct _CERT_ID {
    DWORD  dwIdChoice;
    union {
        CERT_ISSUER_SERIAL_NUMBER  IssuerSerialNumber;
        CRYPT_HASH_BLOB            KeyId;
        CRYPT_HASH_BLOB            HashId;
    };
} CERT_ID, *PCERT_ID;

/* CERT_OTHER_NAME has no layout page in the CE archive; it is used
 * only through a pointer member of CERT_ALT_NAME_ENTRY, so the
 * forward-declared tag keeps the union complete (documented design
 * decision). */
typedef struct _CERT_OTHER_NAME *PCERT_OTHER_NAME;

/* ms937024 */
typedef struct _CERT_ALT_NAME_ENTRY {
    DWORD  dwAltNameChoice;
    union {
        PCERT_OTHER_NAME    pOtherName;
        LPWSTR              pwszRfc822Name;
        LPWSTR              pwszDNSName;
        CERT_NAME_BLOB      DirectoryName;
        LPWSTR              pwszURL;
        CRYPT_DATA_BLOB     IPAddress;
        LPSTR               pszRegisteredID;
    };
} CERT_ALT_NAME_ENTRY, *PCERT_ALT_NAME_ENTRY;

/* ms937025 */
typedef struct _CERT_ALT_NAME_INFO {
    DWORD                 cAltEntry;
    PCERT_ALT_NAME_ENTRY  rgAltEntry;
} CERT_ALT_NAME_INFO, *PCERT_ALT_NAME_INFO;

/* ms937017 / ms937026 */
typedef struct _CERT_ACCESS_DESCRIPTION {
    LPSTR                pszAccessMethod;
    CERT_ALT_NAME_ENTRY  AccessLocation;
} CERT_ACCESS_DESCRIPTION, *PCERT_ACCESS_DESCRIPTION;

typedef struct _CERT_AUTHORITY_INFO_ACCESS {
    DWORD                     cAccDescr;
    PCERT_ACCESS_DESCRIPTION  rgAccDescr;
} CERT_AUTHORITY_INFO_ACCESS, *PCERT_AUTHORITY_INFO_ACCESS;

/* ms937028 / ms937027 */
typedef struct _CERT_AUTHORITY_KEY_ID_INFO {
    CRYPT_DATA_BLOB     KeyId;
    CERT_NAME_BLOB      CertIssuer;
    CRYPT_INTEGER_BLOB  CertSerialNumber;
} CERT_AUTHORITY_KEY_ID_INFO, *PCERT_AUTHORITY_KEY_ID_INFO;

typedef struct _CERT_AUTHORITY_KEY_ID2_INFO {
    CRYPT_DATA_BLOB       KeyId;
    CERT_ALT_NAME_INFO    AuthorityCertIssuer;
    CRYPT_INTEGER_BLOB    AuthorityCertSerialNumber;
} CERT_AUTHORITY_KEY_ID2_INFO, *PCERT_AUTHORITY_KEY_ID2_INFO;

/* ms937030 / ms937029 */
typedef struct _CERT_BASIC_CONSTRAINTS_INFO {
    CRYPT_BIT_BLOB    SubjectType;
    BOOL              fPathLenConstraint;
    DWORD             dwPathLenConstraint;
    DWORD             cSubtreesConstraint;
    CERT_NAME_BLOB   *rgSubtreesConstraint;
} CERT_BASIC_CONSTRAINTS_INFO, *PCERT_BASIC_CONSTRAINTS_INFO;

typedef struct _CERT_BASIC_CONSTRAINTS2_INFO {
    BOOL   fCA;
    BOOL   fPathLenConstraint;
    DWORD  dwPathLenConstraint;
} CERT_BASIC_CONSTRAINTS2_INFO, *PCERT_BASIC_CONSTRAINTS2_INFO;

/* ms937695 */
typedef struct _CERT_REQUEST_INFO {
    DWORD                 dwVersion;
    CERT_NAME_BLOB        Subject;
    CERT_PUBLIC_KEY_INFO  SubjectPublicKeyInfo;
    DWORD                 cAttribute;
    PCRYPT_ATTRIBUTE      rgAttribute;
} CERT_REQUEST_INFO, *PCERT_REQUEST_INFO;

/* ms937701: the page print is truncated after the Signature member;
 * the closing brace/alias list is completed from the same print. */
typedef struct _CERT_SIGNED_CONTENT_INFO {
    CRYPT_DER_BLOB             ToBeSigned;
    CRYPT_ALGORITHM_IDENTIFIER SignatureAlgorithm;
    CRYPT_BIT_BLOB             Signature;
} CERT_SIGNED_CONTENT_INFO, *PCERT_SIGNED_CONTENT_INFO;

/* ms937708 */
typedef struct _CERT_USAGE_MATCH {
    DWORD             dwType;
    CERT_ENHKEY_USAGE Usage;
} CERT_USAGE_MATCH, *PCERT_USAGE_MATCH;

/* Structures referenced by pointer only, with no layout page in the
 * CE archive -- forward-declared tags (documented design decision):
 * CERT_REVOCATION_INFO (CERT_CHAIN_ELEMENT ms937032 member),
 * CTL_ENTRY / CTL_CONTEXT (CERT_TRUST_LIST_INFO ms937706 members). */
typedef struct _CERT_REVOCATION_INFO *PCERT_REVOCATION_INFO;
typedef struct _CTL_ENTRY *PCTL_ENTRY;
typedef struct _CTL_CONTEXT *PCCTL_CONTEXT;
typedef struct _CERT_TRUST_LIST_INFO *PCERT_TRUST_LIST_INFO;

/* ms937032 */
typedef struct _CERT_CHAIN_ELEMENT {
    DWORD                  cbSize;
    PCCERT_CONTEXT         pCertContext;
    CERT_TRUST_STATUS      TrustStatus;
    PCERT_REVOCATION_INFO  pRevocationInfo;
} CERT_CHAIN_ELEMENT, *PCERT_CHAIN_ELEMENT;

/* ms937702 */
typedef struct _CERT_SIMPLE_CHAIN {
    DWORD                cbSize;
    CERT_TRUST_STATUS    TrustStatus;
    DWORD                cElement;
    PCERT_CHAIN_ELEMENT *rgpElement;
    PCERT_TRUST_LIST_INFO pTrustListInfo;
} CERT_SIMPLE_CHAIN, *PCERT_SIMPLE_CHAIN;

/* ms937031 (PCERT_TRUST_LIST_INFO is the pointer to the struct that
 * follows in the archive's member-order; declared after this use by
 * the CERT_SIMPLE_CHAIN pointer, which is all the compiler needs). */
typedef struct _CERT_CHAIN_CONTEXT {
    DWORD               cbSize;
    CERT_TRUST_STATUS   TrustStatus;
    DWORD               cChain;
    PCERT_SIMPLE_CHAIN *rgpChain;
} CERT_CHAIN_CONTEXT, *PCERT_CHAIN_CONTEXT;
typedef const CERT_CHAIN_CONTEXT *PCCERT_CHAIN_CONTEXT;

/* ms937033 */
typedef struct _CERT_CHAIN_ENGINE_CONFIG {
    DWORD        cbSize;
    HCERTSTORE   hRestrictedRoot;
    HCERTSTORE   hRestrictedTrust;
    HCERTSTORE   hRestrictedOther;
    DWORD        cAdditionalStore;
    HCERTSTORE  *rghAdditionalStore;
    DWORD        dwFlags;
    DWORD        dwUrlRetrievalTimeout;
    DWORD        MaximumCachedCertificates;
    DWORD        CycleDetectionModulus;
} CERT_CHAIN_ENGINE_CONFIG, *PCERT_CHAIN_ENGINE_CONFIG;

/* ms937034 */
typedef struct _CERT_CHAIN_PARA {
    DWORD             cbSize;
    CERT_USAGE_MATCH  RequestedUsage;
} CERT_CHAIN_PARA, *PCERT_CHAIN_PARA;

/* ms937706 */
typedef struct _CERT_TRUST_LIST_INFO {
    DWORD           cbSize;
    PCTL_ENTRY      pCtlEntry;
    PCCTL_CONTEXT   pCtlContext;
} CERT_TRUST_LIST_INFO, *PCERT_TRUST_LIST_INFO;

/* ms937704 */
typedef struct _CERT_SYSTEM_STORE_INFO {
    DWORD  cbSize;
} CERT_SYSTEM_STORE_INFO, *PCERT_SYSTEM_STORE_INFO;

/* ms937705 */
typedef struct _CERT_SYSTEM_STORE_RELOCATE_PARA {
    union {
        HKEY    hKeyBase;
        void   *pvBase;
    };
    union {
        void   *pvSystemStore;
        LPCSTR  pszSystemStore;
        LPCWSTR pwszSystemStore;
    };
} CERT_SYSTEM_STORE_RELOCATE_PARA, *PCERT_SYSTEM_STORE_RELOCATE_PARA;

/* ------------------------------------------------------------------ */
/* Cryptographic message (CMSG) structures.                            */
/* ------------------------------------------------------------------ */

/* ms937714 (member name BLOB as printed). */
typedef struct _CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR_PARA {
    DWORD            cbSize;
    DWORD            dwSignerIndex;
    CRYPT_DATA_BLOB  BLOB;
} CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR_PARA, *PCMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR_PARA;

/* ms937715 */
typedef struct _CMSG_CTRL_DECRYPT_PARA {
    DWORD       cbSize;
    HCRYPTPROV  hCryptProv;
    DWORD       dwKeySpec;
    DWORD       dwRecipientIndex;
} CMSG_CTRL_DECRYPT_PARA, *PCMSG_CTRL_DECRYPT_PARA;

/* ms937716 */
typedef struct _CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA {
    DWORD  cbSize;
    DWORD  dwSignerIndex;
    DWORD  dwUnauthAttrIndex;
} CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA, *PCMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA;

/* CMSG_KEY_AGREE_RECIPIENT_INFO has no layout page in the CE archive
 * (pointer member only -- documented design decision). */
typedef struct _CMSG_KEY_AGREE_RECIPIENT_INFO *PCMSG_KEY_AGREE_RECIPIENT_INFO;

/* ms937717 */
typedef struct _CMSG_CTRL_KEY_AGREE_DECRYPT_PARA {
    DWORD                        cbSize;
    HCRYPTPROV                   hCryptProv;
    DWORD                        dwKeySpec;
    PCMSG_KEY_AGREE_RECIPIENT_INFO pKeyAgree;
    DWORD                        dwRecipientIndex;
    DWORD                        dwRecipientEncryptedKeyIndex;
    CRYPT_BIT_BLOB               OriginatorPublicKey;
} CMSG_CTRL_KEY_AGREE_DECRYPT_PARA, *PCMSG_CTRL_KEY_AGREE_DECRYPT_PARA;

/* ms937718 */
typedef struct _CMSG_CTRL_VERIFY_SIGNATURE_EX_PARA {
    DWORD       cbSize;
    HCRYPTPROV  hCryptProv;
    DWORD       dwSignerIndex;
    DWORD       dwSignerType;
    void       *pvSigner;
} CMSG_CTRL_VERIFY_SIGNATURE_EX_PARA, *PCMSG_CTRL_VERIFY_SIGNATURE_EX_PARA;

/* ms938404 */
typedef struct _CMSG_KEY_TRANS_RECIPIENT_INFO {
    DWORD                       dwVersion;
    CERT_ID                     RecipientId;
    CRYPT_ALGORITHM_IDENTIFIER  KeyEncryptionAlgorithm;
    CRYPT_DATA_BLOB             EncryptedKey;
} CMSG_KEY_TRANS_RECIPIENT_INFO, *PCMSG_KEY_TRANS_RECIPIENT_INFO;

/* CRYPT_ATTRIBUTE_TYPE_VALUE has no layout page in the CE archive
 * (pointer member only -- documented design decision). */
typedef struct _CRYPT_ATTRIBUTE_TYPE_VALUE *PCRYPT_ATTRIBUTE_TYPE_VALUE;

/* ms937720 */
typedef struct _CMSG_MAIL_LIST_RECIPIENT_INFO {
    DWORD                       dwVersion;
    CRYPT_DATA_BLOB             KeyId;
    CRYPT_ALGORITHM_IDENTIFIER  KeyEncryptionAlgorithm;
    CRYPT_DATA_BLOB             EncryptedKey;
    FILETIME                    Date;
    PCRYPT_ATTRIBUTE_TYPE_VALUE pOtherAttr;
} CMSG_MAIL_LIST_RECIPIENT_INFO, *PCMSG_MAIL_LIST_RECIPIENT_INFO;

/* ms937712 */
typedef struct _CMSG_CMS_RECIPIENT_INFO {
    DWORD  dwRecipientChoice;
    union {
        PCMSG_KEY_TRANS_RECIPIENT_INFO   pKeyTrans;
        PCMSG_KEY_AGREE_RECIPIENT_INFO   pKeyAgree;
        PCMSG_MAIL_LIST_RECIPIENT_INFO   pMailList;
    };
} CMSG_CMS_RECIPIENT_INFO, *PCMSG_CMS_RECIPIENT_INFO;

/* ms937713 */
typedef struct _CMSG_CMS_SIGNER_INFO {
    DWORD                       dwVersion;
    CERT_ID                     SignerId;
    CRYPT_ALGORITHM_IDENTIFIER  HashAlgorithm;
    CRYPT_ALGORITHM_IDENTIFIER  HashEncryptionAlgorithm;
    CRYPT_DATA_BLOB             EncryptedHash;
    CRYPT_ATTRIBUTES            AuthAttrs;
    CRYPT_ATTRIBUTES            UnauthAttrs;
} CMSG_CMS_SIGNER_INFO, *PCMSG_CMS_SIGNER_INFO;

/* ms937723 */
typedef struct _CMSG_SIGNER_INFO {
    DWORD                       dwVersion;
    CERT_NAME_BLOB              Issuer;
    CRYPT_INTEGER_BLOB          SerialNumber;
    CRYPT_ALGORITHM_IDENTIFIER  HashAlgorithm;
    CRYPT_ALGORITHM_IDENTIFIER  HashEncryptionAlgorithm;
    CRYPT_DATA_BLOB             EncryptedHash;
    CRYPT_ATTRIBUTES            AuthAttrs;
    CRYPT_ATTRIBUTES            UnauthAttrs;
} CMSG_SIGNER_INFO, *PCMSG_SIGNER_INFO;

/* ms937722 */
typedef struct _CMSG_SIGNER_ENCODE_INFO {
    DWORD                       cbSize;
    PCERT_INFO                  pCertInfo;
    HCRYPTPROV                  hCryptProv;
    DWORD                       dwKeySpec;
    CRYPT_ALGORITHM_IDENTIFIER  HashAlgorithm;
    void                       *pvHashAuxInfo;
    DWORD                       cAuthAttr;
    PCRYPT_ATTRIBUTE            rgAuthAttr;
    DWORD                       cUnauthAttr;
    PCRYPT_ATTRIBUTE            rgUnauthAttr;
    CERT_ID                     SignerId;
    CRYPT_ALGORITHM_IDENTIFIER  HashEncryptionAlgorithm;
    void                       *pvHashEncryptionAuxInfo;
} CMSG_SIGNER_ENCODE_INFO, *PCMSG_SIGNER_ENCODE_INFO;

/* ms937721: the page print omits the pointer alias in the closing
 * list; completed from the same print (note the printed member
 * spelling cAttrCertlEncoded). */
typedef struct _CMSG_SIGNED_ENCODE_INFO {
    DWORD                      cbSize;
    DWORD                      cSigners;
    PCMSG_SIGNER_ENCODE_INFO   rgSigners;
    DWORD                      cCertEncoded;
    PCERT_BLOB                 rgCertEncoded;
    DWORD                      cCrlEncoded;
    PCRL_BLOB                  rgCrlEncoded;
    DWORD                      cAttrCertlEncoded;
    PCERT_BLOB                 rgAttrCertEncoded;
} CMSG_SIGNED_ENCODE_INFO, *PCMSG_SIGNED_ENCODE_INFO;

/* CMSG_RECIPIENT_ENCODE_INFO has no layout page in the CE archive
 * (pointer member only -- documented design decision). */
typedef struct _CMSG_RECIPIENT_ENCODE_INFO *PCMSG_RECIPIENT_ENCODE_INFO;

/* ms938395 */
typedef struct _CMSG_ENVELOPED_ENCODE_INFO {
    DWORD                        cbSize;
    HCRYPTPROV                   hCryptProv;
    CRYPT_ALGORITHM_IDENTIFIER   ContentEncryptionAlgorithm;
    void                        *pvEncryptionAuxInfo;
    DWORD                        cRecipients;
    PCERT_INFO                  *rgpRecipients;
    PCMSG_RECIPIENT_ENCODE_INFO  rgCmsRecipients;
    DWORD                        cCertEncoded;
    PCERT_BLOB                   rgCertEncoded;
    DWORD                        cCrlEncoded;
    PCRL_BLOB                    rgCrlEncoded;
    DWORD                        cAttrCertEncoded;
    PCERT_BLOB                   rgAttrCertEncoded;
    DWORD                        cUnprotectedAttr;
    PCRYPT_ATTRIBUTE             rgUnprotectedAttr;
} CMSG_ENVELOPED_ENCODE_INFO, *PCMSG_ENVELOPED_ENCODE_INFO;

/* ms937719: the page print reuses the ENVELOPED struct name; the
 * topic title declares CMSG_HASHED_ENCODE_INFO. */
typedef struct _CMSG_HASHED_ENCODE_INFO {
    DWORD                       cbSize;
    HCRYPTPROV                  hCryptProv;
    CRYPT_ALGORITHM_IDENTIFIER  HashAlgorithm;
    void                       *pvHashAuxInfo;
} CMSG_HASHED_ENCODE_INFO, *PCMSG_HASHED_ENCODE_INFO;

/* ------------------------------------------------------------------ */
/* Encode/decode para structures and callback pointer types.           */
/* ------------------------------------------------------------------ */

/* The CE page for CRYPT_ENCODE_PARA (ms937748) documents pfnAlloc /
 * pfnFree as allocation/free callback pointers but publishes no
 * callback signatures; FARPROC is the repository's generic function
 * pointer (documented design decision). */
typedef FARPROC PFN_CRYPT_ALLOC;
typedef FARPROC PFN_CRYPT_FREE;

/* ms937748 */
typedef struct _CRYPT_ENCODE_PARA {
    DWORD           cbSize;
    PFN_CRYPT_ALLOC pfnAlloc;
    PFN_CRYPT_FREE  pfnFree;
} CRYPT_ENCODE_PARA, *PCRYPT_ENCODE_PARA;

/* CRYPT_DECODE_PARA has no layout page in the CE archive; it is used
 * only through PCRYPT_DECODE_PARA by CryptDecodeObjectEx (ms937740)
 * -- forward-declared tag (documented design decision). */
typedef struct _CRYPT_DECODE_PARA *PCRYPT_DECODE_PARA;

/* Documented callback shapes:
 * - ms937645 CertEnumSystemStore prints CertEnumSystemStoreCallback.
 * - ms937650 CertEnumSystemStoreLocation prints
 *   CertEnumStoreLocationCallback (parameter spelling
 *   pvszStoreLoocations as printed).
 * The three other callback pointer types appear in prototypes whose
 * CE pages publish no callback signature: PFN_CERT_ENUM_PHYSICAL_STORE
 * (aa452564), PFN_CRYPT_ENUM_KEYID_PROP (ms937995),
 * PFN_CRYPT_ENUM_OID_INFO (ms938004) -- declared as the generic
 * function pointer (documented design decision). */
typedef BOOL (WINAPI *PFN_CERT_ENUM_SYSTEM_STORE)(const void *pvSystemStore,
                                                  DWORD dwFlags,
                                                  PCERT_SYSTEM_STORE_INFO pStoreInfo,
                                                  void *pvReserved,
                                                  void *pvArg);
typedef BOOL (WINAPI *PFN_CERT_ENUM_SYSTEM_STORE_LOCATION)(LPCWSTR pvszStoreLoocations,
                                                           DWORD dwFlags,
                                                           void *pvReserved,
                                                           void *pvArg);
typedef FARPROC PFN_CERT_ENUM_PHYSICAL_STORE;
typedef FARPROC PFN_CRYPT_ENUM_KEYID_PROP;
typedef FARPROC PFN_CRYPT_ENUM_OID_INFO;

/* CRYPTPROTECT_PROMPTSTRUCT: the CryptProtectData page (ms938309)
 * documents that this parameter "Must be set to NULL because the
 * CRYPTPROTECT_PROMPTSTRUCT structure is not used" on Windows CE; the
 * layout is therefore never needed and kept as an opaque tag. */
struct CRYPTPROTECT_PROMPTSTRUCT;

/* ------------------------------------------------------------------ */
/* Functions -- all imported from coredll.dll unless noted.            */
/* ------------------------------------------------------------------ */

/* ms937726: CSP entry point; "Link Library: Developer defined." --
 * exported by provider DLLs, not a coredll import. */
AKARI_CE_IMPORT BOOL WINAPI CPAcquireContext(HCRYPTPROV *phProv, WCHAR *pszContainer,
                               DWORD dwFlags,
                               PVTableProvStruc pVTable) AKARI_CE_NAME(CPAcquireContext);

/* ms937733 (CE 2.10+): page prints BOOLEAN as the return type. */
AKARI_CE_IMPORT BOOLEAN CryptAcquireContext(HCRYPTPROV *phProv,
                                            LPCTSTR pszContainer,
                                            LPCTSTR pszProvider,
                                            DWORD dwProvType,
                                            DWORD dwFlags) AKARI_CE_NAME(CryptAcquireContext);

AKARI_CE_IMPORT BOOL WINAPI CryptContextAddRef(HCRYPTPROV hProv, DWORD *pdwReserved,
                                 DWORD dwFlags) AKARI_CE_NAME(CryptContextAddRef);

AKARI_CE_IMPORT BOOL WINAPI CryptCreateHash(HCRYPTPROV hProv, ALG_ID Algid,
                              HCRYPTKEY hKey, DWORD dwFlags,
                              HCRYPTHASH *phHash) AKARI_CE_NAME(CryptCreateHash);

AKARI_CE_IMPORT BOOL WINAPI CryptDecrypt(HCRYPTKEY hKey, HCRYPTHASH hHash, BOOL Final,
                           DWORD dwFlags, BYTE *pbData,
                           DWORD *pdwDataLen) AKARI_CE_NAME(CryptDecrypt);

AKARI_CE_IMPORT BOOL WINAPI CryptDeriveKey(HCRYPTPROV hProv, ALG_ID Algid,
                             HCRYPTHASH hBaseData, DWORD dwFlags,
                             HCRYPTKEY *phKey) AKARI_CE_NAME(CryptDeriveKey);

AKARI_CE_IMPORT BOOL WINAPI CryptDestroyHash(HCRYPTHASH hHash) AKARI_CE_NAME(CryptDestroyHash);

AKARI_CE_IMPORT BOOL WINAPI CryptDestroyKey(HCRYPTKEY hKey) AKARI_CE_NAME(CryptDestroyKey);

AKARI_CE_IMPORT BOOL WINAPI CryptDuplicateHash(HCRYPTHASH hHash, DWORD *pdwReserved,
                                 DWORD dwFlags,
                                 HCRYPTHASH *phHash) AKARI_CE_NAME(CryptDuplicateHash);

/* ms937746: the page prints the CryptDuplicateHash name on this row;
 * the topic title CryptDuplicateKey declares the actual function. */
AKARI_CE_IMPORT BOOL WINAPI CryptDuplicateKey(HCRYPTKEY hKey, DWORD *pdwReserved,
                                DWORD dwFlags,
                                HCRYPTKEY *phKey) AKARI_CE_NAME(CryptDuplicateKey);

AKARI_CE_IMPORT BOOL WINAPI CryptEncrypt(HCRYPTKEY hKey, HCRYPTHASH hHash, BOOL Final,
                           DWORD dwFlags, BYTE *pbData, DWORD *pdwDataLen,
                           DWORD dwBufLen) AKARI_CE_NAME(CryptEncrypt);

AKARI_CE_IMPORT BOOL WINAPI CryptEnumProviders(DWORD dwIndex, DWORD *pdwReserved,
                                 DWORD dwFlags, DWORD *pdwProvType,
                                 LPTSTR pszProvName,
                                 DWORD *pcbProvName) AKARI_CE_NAME(CryptEnumProviders);

AKARI_CE_IMPORT BOOL WINAPI CryptEnumProviderTypes(DWORD dwIndex, DWORD *pdwReserved,
                                     DWORD dwFlags, DWORD *pdwProvType,
                                     LPTSTR pszTypeName,
                                     DWORD *pcbTypeName) AKARI_CE_NAME(CryptEnumProviderTypes);

/* ms938025: last parameter printed as pdwbDataLen. */
AKARI_CE_IMPORT BOOL WINAPI CryptExportKey(HCRYPTKEY hKey, HCRYPTKEY hExpKey,
                             DWORD dwBlobType, DWORD dwFlags, BYTE *pbData,
                             DWORD *pdwbDataLen) AKARI_CE_NAME(CryptExportKey);

/* aa452566: wide-string only, as printed (CE 2.10+). */
AKARI_CE_IMPORT LPCWSTR WINAPI CryptFindLocalizedName(LPCWSTR pwszCryptName) AKARI_CE_NAME(CryptFindLocalizedName);

AKARI_CE_IMPORT BOOL WINAPI CryptGenKey(HCRYPTPROV hProv, ALG_ID Algid, DWORD dwFlags,
                          HCRYPTKEY *phKey) AKARI_CE_NAME(CryptGenKey);

AKARI_CE_IMPORT BOOL WINAPI CryptGenRandom(HCRYPTPROV hProv, DWORD dwLen,
                             BYTE *pbBuffer) AKARI_CE_NAME(CryptGenRandom);

AKARI_CE_IMPORT BOOL WINAPI CryptGetDefaultProvider(DWORD dwProvType, DWORD *pdwReserved,
                                      DWORD dwFlags, LPTSTR pszProvName,
                                      DWORD *pcbProvName) AKARI_CE_NAME(CryptGetDefaultProvider);

/* ms938096: the page prints "CryptGethashParam"; the topic title
 * declares CryptGetHashParam. */
AKARI_CE_IMPORT BOOL WINAPI CryptGetHashParam(HCRYPTHASH hHash, DWORD dwParam,
                                BYTE *pbData, DWORD *pdwDataLen,
                                DWORD dwFlags) AKARI_CE_NAME(CryptGetHashParam);

AKARI_CE_IMPORT BOOL WINAPI CryptGetKeyParam(HCRYPTKEY hKey, DWORD dwParam, BYTE *pbData,
                               DWORD *pdwDataLen,
                               DWORD dwFlags) AKARI_CE_NAME(CryptGetKeyParam);

AKARI_CE_IMPORT BOOL WINAPI CryptGetProvParam(HCRYPTPROV hProv, DWORD dwParam,
                                BYTE *pbData, DWORD *pdwDataLen,
                                DWORD dwFlags) AKARI_CE_NAME(CryptGetProvParam);

AKARI_CE_IMPORT BOOL WINAPI CryptGetUserKey(HCRYPTPROV hProv, DWORD dwKeySpec,
                              HCRYPTKEY *phUserKey) AKARI_CE_NAME(CryptGetUserKey);

AKARI_CE_IMPORT BOOL WINAPI CryptHashData(HCRYPTHASH hHash, BYTE *pbData, DWORD dwDataLen,
                            DWORD dwFlags) AKARI_CE_NAME(CryptHashData);

AKARI_CE_IMPORT BOOL WINAPI CryptHashSessionKey(HCRYPTHASH hHash, HCRYPTKEY hKey,
                                  DWORD dwFlags) AKARI_CE_NAME(CryptHashSessionKey);

AKARI_CE_IMPORT BOOL WINAPI CryptImportKey(HCRYPTPROV hProv, BYTE *pbData, DWORD dwDataLen,
                             HCRYPTKEY hPubKey, DWORD dwFlags,
                             HCRYPTKEY *phKey) AKARI_CE_NAME(CryptImportKey);

/* ---- CryptMsg family (all Windows CE 5.0 and later) --------------- */

AKARI_CE_IMPORT DWORD WINAPI CryptMsgCalculateEncodedLength(DWORD dwMsgEncodingType,
                                                            DWORD dwFlags,
                                                            DWORD dwMsgType,
                                                            const void *pvMsgEncodeInfo,
                                                            LPSTR pszInnerContentObjID,
                                                            DWORD cbData) AKARI_CE_NAME(CryptMsgCalculateEncodedLength);

AKARI_CE_IMPORT BOOL WINAPI CryptMsgClose(HCRYPTMSG hCryptMsg) AKARI_CE_NAME(CryptMsgClose);

AKARI_CE_IMPORT BOOL WINAPI CryptMsgControl(HCRYPTMSG hCryptMsg, DWORD dwFlags,
                              DWORD dwCtrlType,
                              const void *pvCtrlPara) AKARI_CE_NAME(CryptMsgControl);

AKARI_CE_IMPORT HCRYPTMSG WINAPI CryptMsgDuplicate(HCRYPTMSG hCryptMsg) AKARI_CE_NAME(CryptMsgDuplicate);

AKARI_CE_IMPORT BOOL WINAPI CryptMsgGetParam(HCRYPTMSG hCryptMsg, DWORD dwParamType,
                               DWORD dwIndex, void *pvData,
                               DWORD *pcbData) AKARI_CE_NAME(CryptMsgGetParam);

AKARI_CE_IMPORT HCRYPTMSG WINAPI CryptMsgOpenToDecode(DWORD dwMsgEncodingType,
                                                      DWORD dwFlags,
                                                      DWORD dwMsgType,
                                                      HCRYPTPROV hCryptProv,
                                                      PCERT_INFO pRecipientInfo,
                                                      PCMSG_STREAM_INFO pStreamInfo) AKARI_CE_NAME(CryptMsgOpenToDecode);

AKARI_CE_IMPORT HCRYPTMSG WINAPI CryptMsgOpenToEncode(DWORD dwMsgEncodingType,
                                                      DWORD dwFlags,
                                                      DWORD dwMsgType,
                                                      const void *pvMsgEncodeInfo,
                                                      LPSTR pszInnerContentObjID,
                                                      PCMSG_STREAM_INFO pStreamInfo) AKARI_CE_NAME(CryptMsgOpenToEncode);

AKARI_CE_IMPORT BOOL WINAPI CryptMsgUpdate(HCRYPTMSG hCryptMsg, const BYTE *pbData,
                             DWORD cbData,
                             BOOL fFinal) AKARI_CE_NAME(CryptMsgUpdate);

/* ---- Protected storage (Windows CE .NET 4.0 and later) ----------- */

AKARI_CE_IMPORT BOOL WINAPI CryptProtectData(DATA_BLOB *pDataIn, LPCWSTR szDataDescr,
                               DATA_BLOB *pOptionalEntropy, PVOID pvReserved,
                               struct CRYPTPROTECT_PROMPTSTRUCT *pPromptStruct,
                               DWORD dwFlags,
                               DATA_BLOB *pDataOut) AKARI_CE_NAME(CryptProtectData);

AKARI_CE_IMPORT BOOL WINAPI CryptUnprotectData(DATA_BLOB *pDataIn, LPWSTR *ppszDataDescr,
                                 DATA_BLOB *pOptionalEntropy, PVOID pvReserved,
                                 struct CRYPTPROTECT_PROMPTSTRUCT *pPromptStruct,
                                 DWORD dwFlags,
                                 DATA_BLOB *pDataOut) AKARI_CE_NAME(CryptUnprotectData);

/* ------------------------------------------------------------------ */

AKARI_CE_IMPORT BOOL WINAPI CryptReleaseContext(HCRYPTPROV hProv,
                                  DWORD dwFlags) AKARI_CE_NAME(CryptReleaseContext);

AKARI_CE_IMPORT BOOL WINAPI CryptSetHashParam(HCRYPTHASH hHash, DWORD dwParam,
                                BYTE *pbData,
                                DWORD dwFlags) AKARI_CE_NAME(CryptSetHashParam);

AKARI_CE_IMPORT BOOL WINAPI CryptSetKeyParam(HCRYPTKEY hKey, DWORD dwParam, BYTE *pbData,
                               DWORD dwFlags) AKARI_CE_NAME(CryptSetKeyParam);

AKARI_CE_IMPORT BOOL WINAPI CryptSetProvider(LPCTSTR pszProvName,
                               DWORD dwProvType) AKARI_CE_NAME(CryptSetProvider);

AKARI_CE_IMPORT BOOL WINAPI CryptSetProviderEx(LPCTSTR pszProvName, DWORD dwProvType,
                                 DWORD *pdwReserved,
                                 DWORD dwFlags) AKARI_CE_NAME(CryptSetProviderEx);

AKARI_CE_IMPORT BOOL WINAPI CryptSetProvParam(HCRYPTPROV hProv, DWORD dwParam,
                                BYTE *pbData,
                                DWORD dwFlags) AKARI_CE_NAME(CryptSetProvParam);

AKARI_CE_IMPORT BOOL WINAPI CryptSignHash(HCRYPTHASH hHash, DWORD dwKeySpec,
                            LPCTSTR sDescription, DWORD dwFlags,
                            BYTE *pbSignature,
                            DWORD *pdwSigLen) AKARI_CE_NAME(CryptSignHash);

AKARI_CE_IMPORT BOOL WINAPI CryptVerifySignature(HCRYPTHASH hHash, BYTE *pbSignature,
                                   DWORD dwSigLen, HCRYPTKEY hPubKey,
                                   LPCTSTR sDescription,
                                   DWORD dwFlags) AKARI_CE_NAME(CryptVerifySignature);
/* ------------------------------------------------------------------ */
/* Certificate store unit (M48; Crypt32.lib -- every page below has   */
/* Requirements row Header: Wincrypt.h / Link Library: Crypt32.lib).  */
/* ------------------------------------------------------------------ */

AKARI_CE_IMPORT BOOL WINAPI CertAddCertificateContextToStore(HCERTSTORE hCertStore,
                                               PCCERT_CONTEXT pCertContext,
                                               DWORD dwAddDisposition,
                                               PCCERT_CONTEXT *ppStoreContext) AKARI_CE_NAME(CertAddCertificateContextToStore);

AKARI_CE_IMPORT BOOL WINAPI CertAddCertificateLinkToStore(HCERTSTORE hCertStore,
                                            PCCERT_CONTEXT pCertContext,
                                            DWORD dwAddDisposition,
                                            PCCERT_CONTEXT *ppStoreContext) AKARI_CE_NAME(CertAddCertificateLinkToStore);

AKARI_CE_IMPORT BOOL WINAPI CertAddEncodedCertificateToStore(HCERTSTORE hCertStore,
                                               DWORD dwCertEncodingType,
                                               const BYTE *pbCertEncoded,
                                               DWORD cbCertEncoded,
                                               DWORD dwAddDisposition,
                                               PCCERT_CONTEXT *ppCertContext) AKARI_CE_NAME(CertAddEncodedCertificateToStore);

AKARI_CE_IMPORT BOOL WINAPI CertAddEnhancedKeyUsageIdentifier(PCCERT_CONTEXT pCertContext,
                                                LPCSTR pszUsageIdentifier) AKARI_CE_NAME(CertAddEnhancedKeyUsageIdentifier);

AKARI_CE_IMPORT BOOL WINAPI CertAddSerializedElementToStore(HCERTSTORE hCertStore,
                                              const BYTE *pbElement,
                                              DWORD cbElement,
                                              DWORD dwAddDisposition,
                                              DWORD dwFlags,
                                              DWORD dwContextTypeFlags,
                                              DWORD *pdwContextType,
                                              const void **ppvContext) AKARI_CE_NAME(CertAddSerializedElementToStore);

AKARI_CE_IMPORT LPCSTR WINAPI CertAlgIdToOID(DWORD dwAlgId) AKARI_CE_NAME(CertAlgIdToOID);

AKARI_CE_IMPORT BOOL WINAPI CertCloseStore(HCERTSTORE hCertStore,
                             DWORD dwFlags) AKARI_CE_NAME(CertCloseStore);

AKARI_CE_IMPORT BOOL WINAPI CertCompareCertificate(DWORD dwCertEncodingType,
                                     PCERT_INFO pCertId1,
                                     PCERT_INFO pCertId2) AKARI_CE_NAME(CertCompareCertificate);

AKARI_CE_IMPORT BOOL WINAPI CertCompareCertificateName(DWORD dwCertEncodingType,
                                         PCERT_NAME_BLOB pCertName1,
                                         PCERT_NAME_BLOB pCertName2) AKARI_CE_NAME(CertCompareCertificateName);

AKARI_CE_IMPORT BOOL WINAPI CertCompareIntegerBlob(PCRYPT_INTEGER_BLOB pInt1,
                                     PCRYPT_INTEGER_BLOB pInt2) AKARI_CE_NAME(CertCompareIntegerBlob);

AKARI_CE_IMPORT BOOL WINAPI CertComparePublicKeyInfo(DWORD dwCertEncodingType,
                                       PCERT_PUBLIC_KEY_INFO pPublicKey1,
                                       PCERT_PUBLIC_KEY_INFO pPublicKey2) AKARI_CE_NAME(CertComparePublicKeyInfo);

AKARI_CE_IMPORT BOOL WINAPI CertControlStore(HCERTSTORE hCertStore, DWORD dwFlags,
                               DWORD dwCtrlType,
                               const void *pvCtrlPara) AKARI_CE_NAME(CertControlStore);

AKARI_CE_IMPORT PCCERT_CONTEXT WINAPI CertCreateCertificateContext(DWORD dwCertEncodingType,
                                                                   const BYTE *pbCertEncoded,
                                                                   DWORD cbCertEncoded) AKARI_CE_NAME(CertCreateCertificateContext);

AKARI_CE_IMPORT BOOL WINAPI CertDeleteCertificateFromStore(PCCERT_CONTEXT pCertContext) AKARI_CE_NAME(CertDeleteCertificateFromStore);

AKARI_CE_IMPORT PCCERT_CHAIN_CONTEXT WINAPI CertDuplicateCertificateChain(PCCERT_CHAIN_CONTEXT pChainContext) AKARI_CE_NAME(CertDuplicateCertificateChain);

AKARI_CE_IMPORT PCCERT_CONTEXT WINAPI CertDuplicateCertificateContext(PCCERT_CONTEXT pCertContext) AKARI_CE_NAME(CertDuplicateCertificateContext);

AKARI_CE_IMPORT HCERTSTORE WINAPI CertDuplicateStore(HCERTSTORE hCertStore) AKARI_CE_NAME(CertDuplicateStore);

AKARI_CE_IMPORT DWORD WINAPI CertEnumCertificateContextProperties(PCCERT_CONTEXT pCertContext,
                                                                  DWORD dwPropId) AKARI_CE_NAME(CertEnumCertificateContextProperties);

AKARI_CE_IMPORT PCCERT_CONTEXT WINAPI CertEnumCertificatesInStore(HCERTSTORE hCertStore,
                                                                  PCCERT_CONTEXT pPrevCertContext) AKARI_CE_NAME(CertEnumCertificatesInStore);

AKARI_CE_IMPORT BOOL WINAPI CertEnumPhysicalStore(const void *pvSystemStore,
                                    DWORD dwFlags, void *pvArg,
                                    PFN_CERT_ENUM_PHYSICAL_STORE pfnEnum) AKARI_CE_NAME(CertEnumPhysicalStore);

AKARI_CE_IMPORT BOOL WINAPI CertEnumSystemStore(DWORD dwFlags,
                                  void *pvSystemStoreLocationPara,
                                  void *pvArg,
                                  PFN_CERT_ENUM_SYSTEM_STORE pfnEnum) AKARI_CE_NAME(CertEnumSystemStore);

AKARI_CE_IMPORT BOOL WINAPI CertEnumSystemStoreLocation(DWORD dwFlags, void *pvArg,
                                          PFN_CERT_ENUM_SYSTEM_STORE_LOCATION pfnEnum) AKARI_CE_NAME(CertEnumSystemStoreLocation);

AKARI_CE_IMPORT PCRYPT_ATTRIBUTE WINAPI CertFindAttribute(LPCSTR pszObjId,
                                                          DWORD cAttr,
                                                          CRYPT_ATTRIBUTE rgAttr[]) AKARI_CE_NAME(CertFindAttribute);

AKARI_CE_IMPORT PCCERT_CONTEXT WINAPI CertFindCertificateInStore(HCERTSTORE hCertStore,
                                                                 DWORD dwCertEncodingType,
                                                                 DWORD dwFindFlags,
                                                                 DWORD dwFindType,
                                                                 const void *pvFindPara,
                                                                 PCCERT_CONTEXT pPrevCertContext) AKARI_CE_NAME(CertFindCertificateInStore);

AKARI_CE_IMPORT PCERT_EXTENSION WINAPI CertFindExtension(LPCSTR pszObjId,
                                                         DWORD cExtensions,
                                                         CERT_EXTENSION rgExtensions[]) AKARI_CE_NAME(CertFindExtension);

AKARI_CE_IMPORT PCERT_RDN_ATTR WINAPI CertFindRDNAttr(LPCSTR pszObjId,
                                                      PCERT_NAME_INFO pName) AKARI_CE_NAME(CertFindRDNAttr);

/* ms937658 prints a void return. */
AKARI_CE_IMPORT void WINAPI CertFreeCertificateChain(PCCERT_CHAIN_CONTEXT pChainContext) AKARI_CE_NAME(CertFreeCertificateChain);

AKARI_CE_IMPORT BOOL WINAPI CertFreeCertificateContext(PCCERT_CONTEXT pCertContext) AKARI_CE_NAME(CertFreeCertificateContext);

AKARI_CE_IMPORT BOOL WINAPI CertGetCertificateChain(HCERTCHAINENGINE hChainEngine,
                                      PCCERT_CONTEXT pCertContext,
                                      LPFILETIME pTime,
                                      HCERTSTORE hAdditionalStore,
                                      PCERT_CHAIN_PARA pChainPara,
                                      DWORD dwFlags, LPVOID pvReserved,
                                      PCCERT_CHAIN_CONTEXT *ppChainContext) AKARI_CE_NAME(CertGetCertificateChain);

AKARI_CE_IMPORT BOOL WINAPI CertGetCertificateContextProperty(PCCERT_CONTEXT pCertContext,
                                                DWORD dwPropId,
                                                void *pvData,
                                                DWORD *pcbData) AKARI_CE_NAME(CertGetCertificateContextProperty);

AKARI_CE_IMPORT BOOL WINAPI CertGetEnhancedKeyUsage(PCCERT_CONTEXT pCertContext,
                                      DWORD dwFlags,
                                      PCERT_ENHKEY_USAGE pUsage,
                                      DWORD *pcbUsage) AKARI_CE_NAME(CertGetEnhancedKeyUsage);

AKARI_CE_IMPORT BOOL WINAPI CertGetIntendedKeyUsage(DWORD dwCertEncodingType,
                                      PCERT_INFO pCertInfo,
                                      BYTE *pbKeyUsage,
                                      DWORD cbKeyUsage) AKARI_CE_NAME(CertGetIntendedKeyUsage);

AKARI_CE_IMPORT PCCERT_CONTEXT WINAPI CertGetIssuerCertificateFromStore(HCERTSTORE hCertStore,
                                                                        PCCERT_CONTEXT pSubjectContext,
                                                                        PCCERT_CONTEXT pPrevIssuerContext,
                                                                        DWORD *pdwFlags) AKARI_CE_NAME(CertGetIssuerCertificateFromStore);

AKARI_CE_IMPORT DWORD WINAPI CertGetNameString(PCCERT_CONTEXT pCertContext,
                                               DWORD dwType, DWORD dwFlags,
                                               void *pvTypePara,
                                               LPTSTR pszNameString,
                                               DWORD cchNameString) AKARI_CE_NAME(CertGetNameString);

AKARI_CE_IMPORT DWORD WINAPI CertGetPublicKeyLength(DWORD dwCertEncodingType,
                                                    PCERT_PUBLIC_KEY_INFO pPublicKey) AKARI_CE_NAME(CertGetPublicKeyLength);

/* ms937668 prints no calling-convention qualifier; transcribed as
 * printed (WINAPI is empty on CE either way). */
AKARI_CE_IMPORT BOOL WINAPI CertGetStoreProperty(HCERTSTORE hCertStore, DWORD dwPropId,
                                   void *pvData,
                                   DWORD *pcbData) AKARI_CE_NAME(CertGetStoreProperty);

AKARI_CE_IMPORT PCCERT_CONTEXT WINAPI CertGetSubjectCertificateFromStore(HCERTSTORE hCertStore,
                                                                         DWORD dwCertEncodingType,
                                                                         PCERT_INFO pCertId) AKARI_CE_NAME(CertGetSubjectCertificateFromStore);

AKARI_CE_IMPORT BOOL WINAPI CertGetValidUsages(DWORD cCerts, PCCERT_CONTEXT *rghCerts,
                                 int *cNumOIDs, LPSTR *rghOIDs,
                                 DWORD *pcbOIDs) AKARI_CE_NAME(CertGetValidUsages);

AKARI_CE_IMPORT BOOL WINAPI CertIsRDNAttrsInCertificateName(DWORD dwCertEncodingType,
                                              DWORD dwFlags,
                                              PCERT_NAME_BLOB pCertName,
                                              PCERT_RDN pRDN) AKARI_CE_NAME(CertIsRDNAttrsInCertificateName);

AKARI_CE_IMPORT DWORD WINAPI CertNameToStr(DWORD dwCertEncodingType,
                                           PCERT_NAME_BLOB pName,
                                           DWORD dwStrType, LPTSTR psz,
                                           DWORD csz) AKARI_CE_NAME(CertNameToStr);

AKARI_CE_IMPORT DWORD WINAPI CertOIDToAlgId(LPCSTR pszObjId) AKARI_CE_NAME(CertOIDToAlgId);

AKARI_CE_IMPORT HCERTSTORE WINAPI CertOpenStore(LPCSTR lpszStoreProvider,
                                                DWORD dwMsgAndCertEncodingType,
                                                HCRYPTPROV hCryptProv,
                                                DWORD dwFlags,
                                                const void *pvPara) AKARI_CE_NAME(CertOpenStore);

AKARI_CE_IMPORT HCERTSTORE WINAPI CertOpenSystemStore(HCRYPTPROV hProv,
                                                      LPCTSTR szSubsystemProtocol) AKARI_CE_NAME(CertOpenSystemStore);

AKARI_CE_IMPORT DWORD WINAPI CertRDNValueToStr(DWORD dwValueType,
                                               PCERT_RDN_VALUE_BLOB pValue,
                                               LPTSTR psz,
                                               DWORD csz) AKARI_CE_NAME(CertRDNValueToStr);

AKARI_CE_IMPORT BOOL WINAPI CertRemoveEnhancedKeyUsageIdentifier(PCCERT_CONTEXT pCertContext,
                                                   LPCSTR pszUsageIdentifier) AKARI_CE_NAME(CertRemoveEnhancedKeyUsageIdentifier);

AKARI_CE_IMPORT BOOL WINAPI CertSaveStore(HCERTSTORE hCertStore,
                            DWORD dwMsgAndCertEncodingType, DWORD dwSaveAs,
                            DWORD dwSaveTo, void *pvSaveToPara,
                            DWORD dwFlags) AKARI_CE_NAME(CertSaveStore);

AKARI_CE_IMPORT BOOL WINAPI CertSerializeCertificateStoreElement(PCCERT_CONTEXT pCertContext,
                                                   DWORD dwFlags,
                                                   BYTE *pbElement,
                                                   DWORD *pcbElement) AKARI_CE_NAME(CertSerializeCertificateStoreElement);

AKARI_CE_IMPORT BOOL WINAPI CertSetCertificateContextProperty(PCCERT_CONTEXT pCertContext,
                                                DWORD dwPropId, DWORD dwFlags,
                                                const void *pvData) AKARI_CE_NAME(CertSetCertificateContextProperty);

AKARI_CE_IMPORT BOOL WINAPI CertSetEnhancedKeyUsage(PCCERT_CONTEXT pCertContext,
                                      PCERT_ENHKEY_USAGE pUsage) AKARI_CE_NAME(CertSetEnhancedKeyUsage);

/* ms937700 prints no calling-convention qualifier; as printed. */
AKARI_CE_IMPORT BOOL WINAPI CertSetStoreProperty(HCERTSTORE hCertStore, DWORD dwPropId,
                                   DWORD dwFlags,
                                   const void *pvData) AKARI_CE_NAME(CertSetStoreProperty);

AKARI_CE_IMPORT BOOL WINAPI CertStrToName(DWORD dwCertEncodingType, LPCTSTR pszX500,
                            DWORD dwStrType, void *pvReserved,
                            BYTE *pbEncoded, DWORD *pcbEncoded,
                            LPCTSTR *ppszError) AKARI_CE_NAME(CertStrToName);

AKARI_CE_IMPORT BOOL WINAPI CertVerifySubjectCertificateContext(PCCERT_CONTEXT pSubject,
                                                  PCCERT_CONTEXT pIssuer,
                                                  DWORD *pdwFlags) AKARI_CE_NAME(CertVerifySubjectCertificateContext);

AKARI_CE_IMPORT LONG WINAPI CertVerifyTimeValidity(LPFILETIME pTimeToVerify,
                                                   PCERT_INFO pCertInfo) AKARI_CE_NAME(CertVerifyTimeValidity);

AKARI_CE_IMPORT BOOL WINAPI CertVerifyValidityNesting(PCERT_INFO pSubjectInfo,
                                        PCERT_INFO pIssuerInfo) AKARI_CE_NAME(CertVerifyValidityNesting);

/* ------------------------------------------------------------------ */
/* Certificate encode/decode/OID/PFX functions (M48, Crypt32.lib).     */
/* ------------------------------------------------------------------ */

AKARI_CE_IMPORT BOOL WINAPI CryptAcquireCertificatePrivateKey(PCCERT_CONTEXT pCert,
                                                DWORD dwFlags,
                                                void *pvReserved,
                                                HCRYPTPROV *phCryptProv,
                                                DWORD *pdwKeySpec,
                                                BOOL *pfCallerFreeProv) AKARI_CE_NAME(CryptAcquireCertificatePrivateKey);

AKARI_CE_IMPORT BOOL WINAPI CryptCreateKeyIdentifierFromCSP(DWORD dwCertEncodingType,
                                              LPCSTR pszPubKeyOID,
                                              const PUBLICKEYSTRUC *pPubKeyStruc,
                                              DWORD cbPubKeyStruc,
                                              DWORD dwFlags,
                                              void *pvReserved,
                                              BYTE *pbHash,
                                              DWORD *pcbHash) AKARI_CE_NAME(CryptCreateKeyIdentifierFromCSP);

AKARI_CE_IMPORT BOOL WINAPI CryptDecodeObjectEx(DWORD dwCertEncodingType,
                                  LPCSTR lpszStructType,
                                  const BYTE *pbEncoded, DWORD cbEncoded,
                                  DWORD dwFlags,
                                  PCRYPT_DECODE_PARA pDecodePara,
                                  void *pvStructInfo,
                                  DWORD *pcbStructInfo) AKARI_CE_NAME(CryptDecodeObjectEx);

AKARI_CE_IMPORT BOOL WINAPI CryptEncodeObjectEx(DWORD dwCertEncodingType,
                                  LPCSTR lpszStructType,
                                  const void *pvStructInfo, DWORD dwFlags,
                                  PCRYPT_ENCODE_PARA pEncodePara,
                                  void *pvEncoded,
                                  DWORD *pcbEncoded) AKARI_CE_NAME(CryptEncodeObjectEx);

AKARI_CE_IMPORT BOOL WINAPI CryptEnumKeyIdentifierProperties(const CRYPT_HASH_BLOB *pKeyIdentifier,
                                               DWORD dwPropId, DWORD dwFlags,
                                               LPCWSTR pwszComputerName,
                                               void *pvReserved, void *pvArg,
                                               PFN_CRYPT_ENUM_KEYID_PROP pfnEnum) AKARI_CE_NAME(CryptEnumKeyIdentifierProperties);

AKARI_CE_IMPORT BOOL WINAPI CryptEnumOIDInfo(DWORD dwGroupId, DWORD dwFlags, void *pvArg,
                               PFN_CRYPT_ENUM_OID_INFO pfnEnumOIDInfo) AKARI_CE_NAME(CryptEnumOIDInfo);

AKARI_CE_IMPORT BOOL WINAPI CryptExportPublicKeyInfoEx(HCRYPTPROV hCryptProv,
                                         DWORD dwKeySpec,
                                         DWORD dwCertEncodingType,
                                         LPSTR pszPublicKeyObjId,
                                         DWORD dwFlags, void *pvAuxInfo,
                                         PCERT_PUBLIC_KEY_INFO pInfo,
                                         DWORD *pcbInfo) AKARI_CE_NAME(CryptExportPublicKeyInfoEx);

AKARI_CE_IMPORT BOOL WINAPI CryptFindCertificateKeyProvInfo(PCCERT_CONTEXT pCert,
                                              DWORD dwFlags,
                                              void *pvReserved) AKARI_CE_NAME(CryptFindCertificateKeyProvInfo);

AKARI_CE_IMPORT PCCRYPT_OID_INFO WINAPI CryptFindOIDInfo(DWORD dwKeyType,
                                                         void *pvKey,
                                                         DWORD dwGroupId) AKARI_CE_NAME(CryptFindOIDInfo);

AKARI_CE_IMPORT BOOL WINAPI CryptFreeOIDFunctionAddress(HCRYPTOIDFUNCADDR hFuncAddr,
                                          DWORD dwFlags) AKARI_CE_NAME(CryptFreeOIDFunctionAddress);

AKARI_CE_IMPORT BOOL WINAPI CryptGetDefaultOIDFunctionAddress(HCRYPTOIDFUNCSET hFuncSet,
                                                DWORD dwEncodingType,
                                                LPCWSTR pwszDll,
                                                DWORD dwFlags,
                                                void **ppvFuncAddr,
                                                HCRYPTOIDFUNCADDR *phFuncAddr) AKARI_CE_NAME(CryptGetDefaultOIDFunctionAddress);

AKARI_CE_IMPORT BOOL WINAPI CryptGetKeyIdentifierProperty(const CRYPT_HASH_BLOB *pKeyIdentifier,
                                            DWORD dwPropId, DWORD dwFlags,
                                            LPCWSTR pwszComputerName,
                                            void *pvReserved, void *pvData,
                                            DWORD *pcbData) AKARI_CE_NAME(CryptGetKeyIdentifierProperty);

AKARI_CE_IMPORT BOOL WINAPI CryptGetOIDFunctionAddress(HCRYPTOIDFUNCSET hFuncSet,
                                         DWORD dwEncodingType, LPCSTR pszOID,
                                         DWORD dwFlags, void **ppvFuncAddr,
                                         HCRYPTOIDFUNCADDR *phFuncAddr) AKARI_CE_NAME(CryptGetOIDFunctionAddress);

AKARI_CE_IMPORT BOOL WINAPI CryptHashCertificate(HCRYPTPROV hCryptProv, ALG_ID Algid,
                                   DWORD dwFlags, const BYTE *pbEncoded,
                                   DWORD cbEncoded, BYTE *pbComputedHash,
                                   DWORD *pcbComputedHash) AKARI_CE_NAME(CryptHashCertificate);

AKARI_CE_IMPORT BOOL WINAPI CryptHashPublicKeyInfo(HCRYPTPROV hCryptProv, ALG_ID Algid,
                                     DWORD dwFlags, DWORD dwCertEncodingType,
                                     PCERT_PUBLIC_KEY_INFO pInfo,
                                     BYTE *pbComputedHash,
                                     DWORD *pcbComputedHash) AKARI_CE_NAME(CryptHashPublicKeyInfo);

AKARI_CE_IMPORT BOOL WINAPI CryptHashToBeSigned(HCRYPTPROV hCryptProv,
                                  DWORD dwCertEncodingType,
                                  const BYTE *pbEncoded, DWORD cbEncoded,
                                  BYTE *pbComputedHash,
                                  DWORD *pcbComputedHash) AKARI_CE_NAME(CryptHashToBeSigned);

AKARI_CE_IMPORT BOOL WINAPI CryptImportPublicKeyInfoEx(HCRYPTPROV hCryptProv,
                                         DWORD dwCertEncodingType,
                                         PCERT_PUBLIC_KEY_INFO pInfo,
                                         ALG_ID aiKeyAlg, DWORD dwFlags,
                                         void *pvAuxInfo,
                                         HCRYPTKEY *phKey) AKARI_CE_NAME(CryptImportPublicKeyInfoEx);

AKARI_CE_IMPORT HCRYPTOIDFUNCSET WINAPI CryptInitOIDFunctionSet(LPCSTR pszFuncName,
                                                                DWORD dwFlags) AKARI_CE_NAME(CryptInitOIDFunctionSet);

AKARI_CE_IMPORT BOOL WINAPI CryptInstallDefaultContext(HCRYPTPROV hCryptProv,
                                         DWORD dwDefaultType,
                                         const void *pvDefaultPara,
                                         DWORD dwFlags, void *pvReserved,
                                         HCRYPTDEFAULTCONTEXT *phDefaultContext) AKARI_CE_NAME(CryptInstallDefaultContext);

AKARI_CE_IMPORT BOOL WINAPI CryptInstallOIDFunctionAddress(HMODULE hModule,
                                             DWORD dwEncodingType,
                                             LPCSTR pszFuncName,
                                             DWORD cFuncEntry,
                                             CRYPT_OID_FUNC_ENTRY rgFuncEntry[],
                                             DWORD dwFlags) AKARI_CE_NAME(CryptInstallOIDFunctionAddress);

AKARI_CE_IMPORT BOOL WINAPI CryptSetKeyIdentifierProperty(const CRYPT_HASH_BLOB *pKeyIdentifier,
                                            DWORD dwPropId, DWORD dwFlags,
                                            LPCWSTR pwszComputerName,
                                            void *pvReserved,
                                            const void *pvData) AKARI_CE_NAME(CryptSetKeyIdentifierProperty);

AKARI_CE_IMPORT BOOL WINAPI CryptSignAndEncodeCertificate(HCRYPTPROV hCryptProv,
                                            DWORD dwKeySpec,
                                            DWORD dwCertEncodingType,
                                            LPCSTR lpszStructType,
                                            const void *pvStructInfo,
                                            PCRYPT_ALGORITHM_IDENTIFIER pSignatureAlgorithm,
                                            const void *pvHashAuxInfo,
                                            PBYTE pbEncoded,
                                            DWORD *pcbEncoded) AKARI_CE_NAME(CryptSignAndEncodeCertificate);

AKARI_CE_IMPORT BOOL WINAPI CryptSignCertificate(HCRYPTPROV hCryptProv, DWORD dwKeySpec,
                                   DWORD dwCertEncodingType,
                                   const BYTE *pbEncodedToBeSigned,
                                   DWORD cbEncodedToBeSigned,
                                   PCRYPT_ALGORITHM_IDENTIFIER pSignatureAlgorithm,
                                   const void *pvHashAuxInfo,
                                   BYTE *pbSignature,
                                   DWORD *pcbSignature) AKARI_CE_NAME(CryptSignCertificate);

/* aa452567 (CE 2.10+). */
AKARI_CE_IMPORT BOOL WINAPI CryptVerifyCertificateSignature(HCRYPTPROV hCryptProv,
                                              DWORD dwCertEncodingType,
                                              BYTE *pbEncoded,
                                              DWORD cbEncoded,
                                              PCERT_PUBLIC_KEY_INFO pPublicKey) AKARI_CE_NAME(CryptVerifyCertificateSignature);

AKARI_CE_IMPORT BOOL WINAPI CryptUninstallDefaultContext(HCRYPTDEFAULTCONTEXT hDefaultContext,
                                           DWORD dwFlags,
                                           void *pvReserved) AKARI_CE_NAME(CryptUninstallDefaultContext);

/* ---- PFX (CE 5.0 and later) --------------------------------------- */

AKARI_CE_IMPORT BOOL WINAPI PFXExportCertStoreEx(HCERTSTORE hStore,
                                   CRYPT_DATA_BLOB *pPFX, LPCWSTR szPassword,
                                   void *pvReserved,
                                   DWORD dwFlags) AKARI_CE_NAME(PFXExportCertStoreEx);

AKARI_CE_IMPORT HCERTSTORE WINAPI PFXImportCertStore(CRYPT_DATA_BLOB *pPFX,
                                                     LPCWSTR szPassword,
                                                     DWORD dwFlags) AKARI_CE_NAME(PFXImportCertStore);

AKARI_CE_IMPORT BOOL WINAPI PFXIsPFXBlob(CRYPT_DATA_BLOB *pPFX) AKARI_CE_NAME(PFXIsPFXBlob);

AKARI_CE_IMPORT BOOL WINAPI PFXVerifyPassword(CRYPT_DATA_BLOB *pPFX, LPCWSTR szPassword,
                                DWORD dwFlags) AKARI_CE_NAME(PFXVerifyPassword);


#ifdef __cplusplus
}
#endif

#endif /* _WINCRYPT_H */
