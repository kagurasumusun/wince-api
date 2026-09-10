/*
 * Bt_api.h -- Bluetooth OS API for Windows CE (Bt_api.h layer).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  Source book: CE 5.0 "Bluetooth OS Functions" (the Bth* leaves of
 * tools/manifests/bt-os.manifest, fetched M57).  Requirement rows print
 * "Header: Bt_api.h. Link Library: Btdrt.lib." (50 C functions) -- the
 * import surface is def/btdrt-doc.def.  OS Versions: "Windows CE .NET
 * 4.0 and later" unless a page states otherwise.
 *
 * The BthNsSetService page (ms887870) prints no signature; the clean
 * CE 6.0 twin ee495417 prints "INT BthNsSetService(LPWSAQUERYSET
 * lpqsRegInfo, WSAESETSERVICEOP essoperation, DWORD dwControlFlags);"
 * and is used for it (recorded per item).
 *
 * Held families (names documented, values/bodies not published in the
 * official CE documentation -- see docs/inventory.md M57):
 *   - IOCTL_BLUETOOTH_GET_PEER_DEVICE (ms891157) and
 *     IOCTL_BLUETOOTH_GET_RFCOMM_CHANNEL (ms891159): names only, no
 *     CTL_CODE values printed.
 *   - the GET_NAP / GET_SAP / SET_NAP_SAP macros of the SOCKADDR_BTH
 *     page (aa450944) are printed comment-only.
 */

#ifndef AKARI_BT_API_H
#define AKARI_BT_API_H

#include "Windef.h"
#include "Winnt.h"      /* GUID (PORTEMUPortParams member) */
#include "Winsock2.h"   /* LPWSAQUERYSET, WSAESETSERVICEOP (BthNs* pages) */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Address type.                                                       */
/* ------------------------------------------------------------------ */

/* ms896282 "PORTEMUPortParams" page prints the address typedef:
 * "typedef ULONGLONG bt_addr, *pbt_addr, BT_ADDR, *PBT_ADDR;". */
typedef ULONGLONG bt_addr, *pbt_addr, BT_ADDR, *PBT_ADDR;

/* ------------------------------------------------------------------ */
/* Structures (Bluetooth Application Development Structures).          */
/* ------------------------------------------------------------------ */

/* aa450296 "BASEBAND_CONNECTION": printed with bitfields
 * "UINT fLinkType : 1; UINT fEncrypted : 1; UINT fAuthenticated : 1;
 *  UINT fMode : 3;". */
typedef struct _BASEBAND_CONNECTION {
    USHORT   hConnection;
    BT_ADDR  baAddress;
    int      cDataPacketsPending;
    UINT     fLinkType : 1;
    UINT     fEncrypted : 1;
    UINT     fAuthenticated : 1;
    UINT     fMode : 3;
} BASEBAND_CONNECTION, *PBASEBAND_CONNECTION;

/* ms896282 "PORTEMUPortParams": tag _portemu_port_params as printed. */
typedef struct _portemu_port_params {
    int      channel;
    int      flocal;
    BT_ADDR  device;
    int      imtu;
    int      iminmtu;
    int      imaxmtu;
    int      isendquota;
    int      irecvquota;
    GUID     uuidService;
    unsigned int uiportflags;
} PORTEMUPortParams;
/* CROSS-GENERATION (M86 sweep): the CE 4.0 twin ms920295 prints the
 * device member as `BD_ADDR device` (the CE 5.0 print above carries
 * BT_ADDR -- the same ULONGLONG address typedef family, different
 * spelling); the CE 6.0 twin ee495940 matches the CE 5.0 BT_ADDR
 * form. */

/* ms887862 "BthInquiryResult" is a Ws2bth.h structure; the tag
 * __bth_inquiry_result is forward-declared here because
 * BthPerformInquiry (ms887872) takes "BthInquiryResult* InquiryList".
 * The full definition lives in ws2bth.h (included below completes it). */
typedef struct __bth_inquiry_result BthInquiryResult;

#include "Ws2bth.h"     /* completes BthInquiryResult (ms887862) */

/* ------------------------------------------------------------------ */
/* Functions (Bluetooth OS Functions; Btdrt.lib).                      */
/* ------------------------------------------------------------------ */

/* aa450303 "BthAcceptSCOConnections". */
AKARI_CE_IMPORT int BthAcceptSCOConnections(BOOL fAccept) AKARI_CE_NAME(BthAcceptSCOConnections);

/* ms887570 "BthAuthenticate". */
AKARI_CE_IMPORT int BthAuthenticate(BT_ADDR *pba) AKARI_CE_NAME(BthAuthenticate);

/* ms887558 "BthAnswerPairRequest". */
AKARI_CE_IMPORT int BthAnswerPairRequest(BT_ADDR *pba, int cPinLength,
                                         unsigned char *ppin) AKARI_CE_NAME(BthAnswerPairRequest);

/* ms887578 "BthCancelInquiry". */
AKARI_CE_IMPORT int BthCancelInquiry(void) AKARI_CE_NAME(BthCancelInquiry);

/* ms887586 "BthClearInquiryFilter". */
AKARI_CE_IMPORT int BthClearInquiryFilter(void) AKARI_CE_NAME(BthClearInquiryFilter);

/* ms887598 "BthCloseConnection". */
AKARI_CE_IMPORT int BthCloseConnection(unsigned short handle) AKARI_CE_NAME(BthCloseConnection);

/* ms887605 "BthCreateACLConnection". */
AKARI_CE_IMPORT int BthCreateACLConnection(BT_ADDR *pbt,
                                           unsigned short *phandle) AKARI_CE_NAME(BthCreateACLConnection);

/* ms887612 "BthCreateSCOConnection". */
AKARI_CE_IMPORT int BthCreateSCOConnection(BT_ADDR *pbt,
                                           unsigned short *phandle) AKARI_CE_NAME(BthCreateSCOConnection);

/* ms887712 "BthEnterHoldMode". */
AKARI_CE_IMPORT int BthEnterHoldMode(BT_ADDR *pba, unsigned short hold_mode_max,
                                     unsigned short hold_mode_min,
                                     unsigned short *pinterval) AKARI_CE_NAME(BthEnterHoldMode);

/* ms887822 "BthEnterParkMode". */
AKARI_CE_IMPORT int BthEnterParkMode(BT_ADDR *pba, unsigned short beacon_max,
                                     unsigned short beacon_min,
                                     unsigned short *pinterval) AKARI_CE_NAME(BthEnterParkMode);

/* ms887829 "BthEnterSniffMode". */
AKARI_CE_IMPORT int BthEnterSniffMode(BT_ADDR *pba, unsigned short sniff_mode_max,
                                      unsigned short sniff_mode_min,
                                      unsigned short sniff_attempt,
                                      unsigned short sniff_timeout,
                                      unsigned short *pinterval) AKARI_CE_NAME(BthEnterSniffMode);

/* ms887830 "BthExitParkMode". */
AKARI_CE_IMPORT int BthExitParkMode(BT_ADDR *pba) AKARI_CE_NAME(BthExitParkMode);

/* ms887831 "BthExitSniffMode". */
AKARI_CE_IMPORT int BthExitSniffMode(BT_ADDR *pba) AKARI_CE_NAME(BthExitSniffMode);

/* ms887833 "BthGetAddress". */
AKARI_CE_IMPORT int BthGetAddress(unsigned short handle,
                                  BT_ADDR *pba) AKARI_CE_NAME(BthGetAddress);

/* ms887834 "BthGetBasebandConnections". */
AKARI_CE_IMPORT int BthGetBasebandConnections(int cConnections,
                                              BASEBAND_CONNECTION *pConnections,
                                              int *pcConnectionsReturned) AKARI_CE_NAME(BthGetBasebandConnections);

/* ms887835 "BthGetBasebandHandles". */
AKARI_CE_IMPORT int BthGetBasebandHandles(int cHandles, unsigned short *pHandles,
                                          int *pcHandlesReturned) AKARI_CE_NAME(BthGetBasebandHandles);

/* ms887836 "BthGetCurrentMode". */
AKARI_CE_IMPORT int BthGetCurrentMode(BT_ADDR *pba,
                                      unsigned char *pmode) AKARI_CE_NAME(BthGetCurrentMode);

/* ms887837 "BthGetHardwareStatus". */
AKARI_CE_IMPORT int BthGetHardwareStatus(int *pistatus) AKARI_CE_NAME(BthGetHardwareStatus);

/* ms887838 "BthGetLinkKey": "unsigned char key[16]" as printed. */
AKARI_CE_IMPORT int BthGetLinkKey(BT_ADDR *pba,
                                  unsigned char key[16]) AKARI_CE_NAME(BthGetLinkKey);

/* ms887839 "BthGetPINRequest". */
AKARI_CE_IMPORT int BthGetPINRequest(BT_ADDR *pbt) AKARI_CE_NAME(BthGetPINRequest);

/* ms887840 "BthGetRemoteCOD". */
AKARI_CE_IMPORT int BthGetRemoteCOD(BT_ADDR *pbt,
                                    unsigned int *pcod) AKARI_CE_NAME(BthGetRemoteCOD);

/* ms887865 "BthNsLookupServiceBegin". */
AKARI_CE_IMPORT INT BthNsLookupServiceBegin(LPWSAQUERYSET pQuerySet, DWORD dwFlags,
                                            LPHANDLE lphLookup) AKARI_CE_NAME(BthNsLookupServiceBegin);

/* ms887866 "BthNsLookupServiceEnd". */
AKARI_CE_IMPORT INT BthNsLookupServiceEnd(HANDLE hLookup) AKARI_CE_NAME(BthNsLookupServiceEnd);

/* ms887867 "BthNsLookupServiceNext". */
AKARI_CE_IMPORT INT BthNsLookupServiceNext(HANDLE hLookup, DWORD dwFlags,
                                            LPDWORD lpdwBufferLength,
                                            LPWSAQUERYSET pResults) AKARI_CE_NAME(BthNsLookupServiceNext);

/* ms887870 "BthNsSetService": CE 5.0 page prints no signature; the
 * CE 6.0 twin ee495417 prints the full prototype. */
AKARI_CE_IMPORT INT BthNsSetService(LPWSAQUERYSET lpqsRegInfo,
                                    WSAESETSERVICEOP essoperation,
                                    DWORD dwControlFlags) AKARI_CE_NAME(BthNsSetService);

/* ms887871 "BthPairRequest". */
AKARI_CE_IMPORT int BthPairRequest(BT_ADDR *pba, int cPinLength,
                                   unsigned char *ppin) AKARI_CE_NAME(BthPairRequest);

/* ms887872 "BthPerformInquiry". */
AKARI_CE_IMPORT int BthPerformInquiry(unsigned int LAP, unsigned char length,
                                      unsigned char num_responses,
                                      unsigned int cBuffer,
                                      unsigned int *pcDiscoveredDevices,
                                      BthInquiryResult *InquiryList) AKARI_CE_NAME(BthPerformInquiry);

/* ms887873 "BthReadAuthenticationEnable". */
AKARI_CE_IMPORT int BthReadAuthenticationEnable(unsigned char *pae) AKARI_CE_NAME(BthReadAuthenticationEnable);

/* ms887874 "BthReadCOD". */
AKARI_CE_IMPORT int BthReadCOD(unsigned int *pcod) AKARI_CE_NAME(BthReadCOD);

/* ms887875 "BthReadLinkPolicySettings". */
AKARI_CE_IMPORT int BthReadLinkPolicySettings(BT_ADDR *pba,
                                              unsigned short *plps) AKARI_CE_NAME(BthReadLinkPolicySettings);

/* ms887876 "BthReadLocalAddr". */
AKARI_CE_IMPORT int BthReadLocalAddr(BT_ADDR *pba) AKARI_CE_NAME(BthReadLocalAddr);

/* ms887877 "BthReadLocalVersion": lmp_features[8] as printed. */
AKARI_CE_IMPORT int BthReadLocalVersion(unsigned char *phci_version,
                                        unsigned short *phci_revision,
                                        unsigned char *plmp_version,
                                        unsigned short *plmp_subversion,
                                        unsigned short *pmanufacturer,
                                        unsigned char *plmp_features) AKARI_CE_NAME(BthReadLocalVersion);

/* ms887878 "BthReadPageTimeout". */
AKARI_CE_IMPORT int BthReadPageTimeout(unsigned short *ptimeout) AKARI_CE_NAME(BthReadPageTimeout);

/* ms887879 "BthReadRemoteVersion". */
AKARI_CE_IMPORT int BthReadRemoteVersion(BT_ADDR *pba, unsigned char *plmp_version,
                                         unsigned short *plmp_subversion,
                                         unsigned short *pmanufacturer,
                                         unsigned char *plmp_features) AKARI_CE_NAME(BthReadRemoteVersion);

/* ms887880 "BthReadScanEnableMask". */
AKARI_CE_IMPORT int BthReadScanEnableMask(unsigned char *pmask) AKARI_CE_NAME(BthReadScanEnableMask);

/* ms887881 "BthRefusePINRequest". */
AKARI_CE_IMPORT int BthRefusePINRequest(BT_ADDR *pbt) AKARI_CE_NAME(BthRefusePINRequest);

/* ms887883 "BthRemoteNameQuery". */
AKARI_CE_IMPORT int BthRemoteNameQuery(BT_ADDR *pba, unsigned int cBuffer,
                                       unsigned int *pcRequired,
                                       WCHAR *szString) AKARI_CE_NAME(BthRemoteNameQuery);

/* ms887885 "BthRevokeLinkKey". */
AKARI_CE_IMPORT int BthRevokeLinkKey(BT_ADDR *pba) AKARI_CE_NAME(BthRevokeLinkKey);

/* ms887886 "BthRevokePIN". */
AKARI_CE_IMPORT int BthRevokePIN(BT_ADDR *pba) AKARI_CE_NAME(BthRevokePIN);

/* ms887887 "BthSetEncryption". */
AKARI_CE_IMPORT int BthSetEncryption(BT_ADDR *pba, int fOn) AKARI_CE_NAME(BthSetEncryption);

/* ms887889 "BthSetInquiryFilter". */
AKARI_CE_IMPORT int BthSetInquiryFilter(BT_ADDR *pba) AKARI_CE_NAME(BthSetInquiryFilter);

/* ms887890 "BthSetLinkKey". */
AKARI_CE_IMPORT int BthSetLinkKey(BT_ADDR *pba,
                                  unsigned char key[16]) AKARI_CE_NAME(BthSetLinkKey);

/* ms887891 "BthSetPIN". */
AKARI_CE_IMPORT int BthSetPIN(BT_ADDR *pba, int cPinLength,
                              unsigned char *ppin) AKARI_CE_NAME(BthSetPIN);

/* ms887892 "BthSetSecurityUI". */
AKARI_CE_IMPORT int BthSetSecurityUI(HANDLE hEvent, DWORD dwStoreTimeout,
                                     DWORD dwProcTimeout) AKARI_CE_NAME(BthSetSecurityUI);

/* ms887895 "BthTerminateIdleConnections". */
AKARI_CE_IMPORT int BthTerminateIdleConnections(void) AKARI_CE_NAME(BthTerminateIdleConnections);

/* ms887896 "BthWriteAuthenticationEnable". */
AKARI_CE_IMPORT int BthWriteAuthenticationEnable(unsigned char ae) AKARI_CE_NAME(BthWriteAuthenticationEnable);

/* ms887897 "BthWriteCOD". */
AKARI_CE_IMPORT int BthWriteCOD(unsigned int cod) AKARI_CE_NAME(BthWriteCOD);

/* ms887898 "BthWriteLinkPolicySettings". */
AKARI_CE_IMPORT int BthWriteLinkPolicySettings(BT_ADDR *pba,
                                               unsigned short lps) AKARI_CE_NAME(BthWriteLinkPolicySettings);

/* ms887899 "BthWritePageTimeout". */
AKARI_CE_IMPORT int BthWritePageTimeout(unsigned short timeout) AKARI_CE_NAME(BthWritePageTimeout);

/* ms887900 "BthWriteScanEnableMask". */
AKARI_CE_IMPORT int BthWriteScanEnableMask(unsigned char mask) AKARI_CE_NAME(BthWriteScanEnableMask);

/* ------------------------------------------------------------------
 * Book surface: bt-os (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms886640 Bluetooth OS Functions */
/* ms880965 Bluetooth OS IOCTLs */
/* ms886639 Bluetooth OS Messages */
/* ms886638 Bluetooth OS Object Identifiers */
/* ms880966 Bluetooth OS Structures */
/* ms886707 PAN Profile Object Identifiers */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_BT_API_H */
