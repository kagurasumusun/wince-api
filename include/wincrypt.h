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
 *
 * Transcription notes:
 *   - The CE archive prints the calling-convention qualifier CRYPTFUNC
 *     (or WINAPI) on these prototypes. Windows CE has a single calling
 *     convention, so both are empty; declarations follow the repository
 *     model and omit the qualifier (CRYPTFUNC is provided as a no-op
 *     macro for fidelity).
 *   - Cert-store/CERT_INFO structures belong to the later certificate
 *     unit; PCERT_INFO is forward-declared only.
 *   - Numeric values (PROV_*, AT_*, CALG_*, HP_*, KP_*, PP_*,
 *     CRYPT_VERIFYCONTEXT, CRYPTPROTECT_* flags, CMSG_* parameter ids)
 *     are absent from the public CE archive -- names only, no defines.
 *   - Spelling as printed: CryptExportKey's last parameter is
 *     pdwbDataLen (ms938025); ms938096 prints the lowercase variant
 *     "CryptGethashParam" -- the topic title CryptGetHashParam is the
 *     declared name (title-print fix-ups, same model as M44).
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

/* Certificate structures belong to the certificate unit; PCERT_INFO is
 * only forward-declared here so the CryptMsg prototypes can be written
 * (CryptMsgOpenToDecode ms938264). */
typedef struct _CERT_INFO *PCERT_INFO;

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

#ifdef __cplusplus
}
#endif

#endif /* _WINCRYPT_H */
