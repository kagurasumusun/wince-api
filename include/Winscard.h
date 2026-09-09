/*
 * Windows CE Smart Card API (M49)
 *
 * Header of record for every page of this unit (CE 5.0 archive):
 * Winscard.h.  The 28 documented SCard* functions all list
 * "Link Library: Winscard.lib".
 *
 * Scope (MSDN catalog Windows CE 5.0, book "Cryptography" -> Smart
 * Card):
 *   - 28 SCard* functions (SCardBeginTransaction ms938481 ...
 *     SCardTransmit ms926431), tools/manifests/smartcard.manifest.
 *   - SCARD_ATRMASK (ms938473), SCARD_IO_REQUEST (ms926417),
 *     SCARD_READERSTATE (ms926425).
 *
 * Transcription notes:
 *   - SCARDCONTEXT / SCARDHANDLE have no dedicated data-type pages in
 *     the CE archive; the prototypes pass them as resource-manager /
 *     card handles, so they are declared as handle carriers
 *     (repository design, same as HCRYPTMSG).
 *   - ms926424 (SCardLocateCardsByATR) prints the SCardLocateCards
 *     name on its prototype row; the topic title declares the actual
 *     function (title-print fix-up, same model as M44).
 *   - ms938564 (SCardFreeMemory) prints a trailing comma after the
 *     last parameter; removed.
 *   - ms926431 (SCardTransmit) prints LPCSCARD_I0_REQUEST (zero);
 *     the declared type is the const pointer to SCARD_IO_REQUEST.
 *   - The state/protocol/attribute/scope value pages (SCARD_STATE_*,
 *     SCARD_PROTOCOL_*, SCARD_ATTR_*, SCARD_SCOPE_*, SCARD_SHARE_*,
 *     SCARD_LEAVE_*, SCARD_READERSTATE state bits) are absent from
 *     the CE archive as numbered constant pages -- names only, no
 *     defines (the held-set policy).
 */
#ifndef _WINSCARD_H
#define _WINSCARD_H

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Resource-manager context and card handles (no type pages published;
 * handle carriers). */
typedef ULONG_PTR SCARDCONTEXT;
typedef SCARDCONTEXT *PSCARDCONTEXT, *LPSCARDCONTEXT;
typedef ULONG_PTR SCARDHANDLE;
typedef SCARDHANDLE *PSCARDHANDLE, *LPSCARDHANDLE;

/* ms926417: anonymous tag as printed; the pointer forms are named by
 * the SCardTransmit prototype. */
typedef struct {
    DWORD  dwProtocol;
    DWORD  cbPciLength;
} SCARD_IO_REQUEST, *PSCARD_IO_REQUEST, *LPSCARD_IO_REQUEST;
typedef const SCARD_IO_REQUEST *LPCSCARD_IO_REQUEST;

/* ms926425 */
typedef struct {
    LPCTSTR  szReader;
    LPVOID   pvUserData;
    DWORD    dwCurrentState;
    DWORD    dwEventState;
    DWORD    cbAtr;
    BYTE     rgbAtr[36];
} SCARD_READERSTATE, *PSCARD_READERSTATE, *LPSCARD_READERSTATE;

/* ms938473 (CE .NET 4.1+). */
typedef struct _SCARD_ATRMASK {
    DWORD  cbAtr;
    BYTE   rgbAtr[36];
    BYTE   rgbMask[36];
} SCARD_ATRMASK, *PSCARD_ATRMASK, *LPSCARD_ATRMASK;

/* ------------------------------------------------------------------ */
/* Functions (all Winscard.lib).                                       */
/* ------------------------------------------------------------------ */

AKARI_CE_IMPORT LONG SCardBeginTransaction(SCARDHANDLE hCard) AKARI_CE_NAME(SCardBeginTransaction);

AKARI_CE_IMPORT LONG SCardCancel(SCARDCONTEXT hContext) AKARI_CE_NAME(SCardCancel);

AKARI_CE_IMPORT LONG SCardConnect(SCARDCONTEXT hContext, LPCTSTR szReader,
                                  DWORD dwShareMode,
                                  DWORD dwPreferredProtocols,
                                  LPSCARDHANDLE phCard,
                                  LPDWORD pdwActiveProtocol) AKARI_CE_NAME(SCardConnect);

AKARI_CE_IMPORT LONG SCardControl(SCARDHANDLE hCard, DWORD dwControlCode,
                                  LPCVOID lpInBuffer, DWORD nInBufferSize,
                                  LPVOID lpOutBuffer, DWORD nOutBufferSize,
                                  LPDWORD lpBytesReturned) AKARI_CE_NAME(SCardControl);

AKARI_CE_IMPORT LONG SCardDisconnect(SCARDHANDLE hCard,
                                     DWORD dwDisposition) AKARI_CE_NAME(SCardDisconnect);

AKARI_CE_IMPORT LONG SCardEndTransaction(SCARDHANDLE hCard,
                                         DWORD dwDisposition) AKARI_CE_NAME(SCardEndTransaction);

AKARI_CE_IMPORT LONG SCardEstablishContext(DWORD dwScope,
                                           LPCVOID pvReserved1,
                                           LPCVOID pvReserved2,
                                           LPSCARDCONTEXT phContext) AKARI_CE_NAME(SCardEstablishContext);

AKARI_CE_IMPORT LONG SCardForgetCardType(SCARDCONTEXT hContext,
                                         LPCTSTR szCardName) AKARI_CE_NAME(SCardForgetCardType);

AKARI_CE_IMPORT LONG SCardForgetReader(SCARDCONTEXT hContext,
                                       LPCTSTR szReaderName) AKARI_CE_NAME(SCardForgetReader);

/* ms938564 (CE 5.0+): the page print has a trailing comma after
 * pvMem; removed. */
AKARI_CE_IMPORT LONG SCardFreeMemory(SCARDCONTEXT hContext,
                                     LPCVOID pvMem) AKARI_CE_NAME(SCardFreeMemory);

AKARI_CE_IMPORT LONG SCardGetAttrib(SCARDHANDLE hCard, DWORD dwAttrId,
                                    LPBYTE pbAttr,
                                    LPDWORD pcbAttrLen) AKARI_CE_NAME(SCardGetAttrib);

AKARI_CE_IMPORT LONG SCardGetCardTypeProviderName(SCARDCONTEXT hContext,
                                                  LPCTSTR szCardName,
                                                  DWORD dwProviderId,
                                                  LPTSTR szProvider,
                                                  LPDWORD pcchProvider) AKARI_CE_NAME(SCardGetCardTypeProviderName);

AKARI_CE_IMPORT LONG SCardGetProviderId(SCARDCONTEXT hContext,
                                        LPCTSTR szCard,
                                        LPGUID pguidProviderId) AKARI_CE_NAME(SCardGetProviderId);

AKARI_CE_IMPORT LONG SCardGetStatusChange(SCARDCONTEXT hContext,
                                          DWORD dwTimeout,
                                          LPSCARD_READERSTATE rgReaderStates,
                                          DWORD cReaders) AKARI_CE_NAME(SCardGetStatusChange);

AKARI_CE_IMPORT LONG SCardIntroduceCardType(SCARDCONTEXT hContext,
                                            LPCTSTR szCardName,
                                            LPGUID pguidPrimaryProvider,
                                            LPGUID rgguidInterfaces,
                                            DWORD dwInterfaceCount,
                                            LPCBYTE pbAtr, LPCBYTE pbAtrMask,
                                            DWORD cbAtrLen) AKARI_CE_NAME(SCardIntroduceCardType);

AKARI_CE_IMPORT LONG SCardIntroduceReader(SCARDCONTEXT hContext,
                                          LPCTSTR szReaderName,
                                          LPCTSTR szDeviceName) AKARI_CE_NAME(SCardIntroduceReader);

/* ms926418 (CE .NET 4.1+). */
AKARI_CE_IMPORT LONG SCardIsValidContext(SCARDCONTEXT hContext) AKARI_CE_NAME(SCardIsValidContext);

AKARI_CE_IMPORT LONG SCardListCards(SCARDCONTEXT hContext, LPCBYTE pbAtr,
                                    LPCGUID rgguidInterfaces,
                                    DWORD cguidInterfaceCount,
                                    LPTSTR mszCards,
                                    LPDWORD pcchCards) AKARI_CE_NAME(SCardListCards);

AKARI_CE_IMPORT LONG SCardListInterfaces(SCARDCONTEXT hContext,
                                         LPCTSTR szCard,
                                         LPGUID pguidInterfaces,
                                         LPDWORD pcguidInterfaces) AKARI_CE_NAME(SCardListInterfaces);

AKARI_CE_IMPORT LONG SCardListReaders(SCARDCONTEXT hContext,
                                      LPCTSTR mszGroups, LPTSTR mszReaders,
                                      LPDWORD pcchReaders) AKARI_CE_NAME(SCardListReaders);

AKARI_CE_IMPORT LONG SCardLocateCards(SCARDCONTEXT hContext,
                                      LPCTSTR mszCards,
                                      LPSCARD_READERSTATE rgReaderStates,
                                      DWORD cReaders) AKARI_CE_NAME(SCardLocateCards);

/* ms926424 (CE .NET 4.1+): the page prints the SCardLocateCards name;
 * the topic title declares SCardLocateCardsByATR. */
AKARI_CE_IMPORT LONG SCardLocateCardsByATR(SCARDCONTEXT hContext,
                                           LPSCARD_ATRMASK rgAtrMasks,
                                           DWORD cAtrs,
                                           LPSCARD_READERSTATE rgReaderStates,
                                           DWORD cReaders) AKARI_CE_NAME(SCardLocateCardsByATR);

AKARI_CE_IMPORT LONG SCardReconnect(SCARDHANDLE hCard, DWORD dwShareMode,
                                    DWORD dwPreferredProtocols,
                                    DWORD dwInitialization,
                                    LPDWORD pdwActiveProtocol) AKARI_CE_NAME(SCardReconnect);

AKARI_CE_IMPORT LONG SCardReleaseContext(SCARDCONTEXT hContext) AKARI_CE_NAME(SCardReleaseContext);

AKARI_CE_IMPORT LONG SCardSetAttrib(SCARDHANDLE hCard, DWORD dwAttrId,
                                    LPCBYTE pbAttr,
                                    DWORD cbAttrLen) AKARI_CE_NAME(SCardSetAttrib);

AKARI_CE_IMPORT LONG SCardSetCardTypeProviderName(SCARDCONTEXT hContext,
                                                  LPCTSTR szCardName,
                                                  DWORD dwProviderId,
                                                  LPCTSTR szProvider) AKARI_CE_NAME(SCardSetCardTypeProviderName);

AKARI_CE_IMPORT LONG SCardStatus(SCARDHANDLE hCard, LPTSTR szReaderName,
                                 LPDWORD pcchReaderLen, LPDWORD pdwState,
                                 LPDWORD pdwProtocol, LPBYTE pbAtr,
                                 LPDWORD pbcAtrLen) AKARI_CE_NAME(SCardStatus);

/* ms926431: the page prints LPCSCARD_I0_REQUEST; the declared type is
 * the const pointer to SCARD_IO_REQUEST. */
AKARI_CE_IMPORT LONG SCardTransmit(SCARDHANDLE hCard,
                                   LPCSCARD_IO_REQUEST pioSendPci,
                                   LPCBYTE pbSendBuffer, DWORD cbSendLength,
                                   LPSCARD_IO_REQUEST pioRecvPci,
                                   LPBYTE pbRecvBuffer,
                                   LPDWORD pcbRecvLength) AKARI_CE_NAME(SCardTransmit);

#ifdef __cplusplus
}
#endif

#endif /* _WINSCARD_H */
