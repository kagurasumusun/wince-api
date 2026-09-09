/*
 * Btagpub.h -- Bluetooth Audio Gateway public interface for Windows CE
 * (Btagpub.h layer).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  Source book: CE 5.0 "Audio Gateway" (the Btagpub.h leaves of
 * tools/manifests/bt-os.manifest, fetched M57; CE 6.0 twins in
 * build/pages6 cross-read where the CE 5.0 print is damaged).
 * OS Versions: "Windows CE 5.0 and later".
 *
 * Import surfaces: "Link Library: Btagsvc_phoneext.lib" (9 functions,
 * def/btagsvc_phoneext-doc.def) and "Link Library: Btagsvc_network.lib"
 * (11 functions, def/btagsvc_network-doc.def).  The AT-command entry
 * points BthAGATHandler / BthAGATSetCallback are documented with
 * "Header: Developer defined. Link library: Developer defined." rows --
 * declared without import pins and without def entries.
 *
 * Print artifacts (CE 5.0 signature blocks that print a different
 * function's name in the prototype; the page title is the function --
 * resolved via the CE 6.0 twins and the parameter text):
 *   BthAGPhoneExtInit (aa450311) prints "BthAGInitPhoneExt";
 *   BthAGNetworkDropCall (aa450316) prints "BthAGNetworkHangupCall";
 *   BthAGNetworkHoldCall (aa450317) prints "BthAgNetworkHoldCall".
 *
 * Held families (names documented, values not published -- see
 * docs/inventory.md M57): AG_PHONE_EVENT_* (ms880975) and the
 * IOCTL_AG_* codes (ms891134..ms891153) are names-only.
 */

#ifndef AKARI_BTAGPUB_H
#define AKARI_BTAGPUB_H

#include "Windef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Callback types (header excerpts printed by the official pages).     */
/* ------------------------------------------------------------------ */

/* aa450305 "BthAGATSetServiceCallback" [sic] -- the page prints the
 * function-pointer declaration from btagpub.h verbatim:
 * "typedef DWORD (*PFN_SendATCommand) (LPSTR szCommand, DWORD cbCommand);" */
typedef DWORD (*PFN_SendATCommand)(LPSTR szCommand, DWORD cbCommand);

/* aa450310 "BthAGSetServiceCallback": "typedef void
 * (*PFN_PhoneExtServiceCallback) (BOOL fHaveService);" (verbatim). */
typedef void (*PFN_PhoneExtServiceCallback)(BOOL fHaveService);

/* ------------------------------------------------------------------ */
/* Call-state flags (values printed on the official pages).            */
/* ------------------------------------------------------------------ */

/* aa450316 "BthAGNetworkDropCall" flag table. */
#define NETWORK_FLAGS_DROP_ACTIVE    0x01
#define NETWORK_FLAGS_DROP_HOLD      0x02
#define NETWORK_FLAGS_DROP_OFFERING  0x04
#define NETWORK_FLAGS_DROP_OUTGOING  0x08
#define NETWORK_FLAGS_DROP_ALL       0x0f

/* aa450315 "BthAGNetworkGetCallState" flag table. */
#define NETWORK_FLAGS_STATE_ACTIVE   0x01
#define NETWORK_FLAGS_STATE_HOLD     0x02
#define NETWORK_FLAGS_STATE_OFFERING 0x04
#define NETWORK_FLAGS_STATE_OUTGOING 0x08

/* ------------------------------------------------------------------ */
/* Phone-Extension component (Btagpub.h, Btagsvc_phoneext.lib).        */
/* ------------------------------------------------------------------ */

/* aa450311 "BthAGPhoneExtInit": CE 5.0 signature block prints
 * "BthAGInitPhoneExt" (artifact); parameters None, ERROR_SUCCESS
 * return documented; the CE 6.0 twin ee495665 prints the same body. */
AKARI_CE_IMPORT DWORD BthAGPhoneExtInit(void) AKARI_CE_NAME(BthAGPhoneExtInit);

/* aa450306 "BthAGPhoneExtDeinit": CE 5.0 page prints no signature;
 * CE 6.0 twin ee495979: "void BthAGPhoneExtDeinit(void);". */
AKARI_CE_IMPORT void BthAGPhoneExtDeinit(void) AKARI_CE_NAME(BthAGPhoneExtDeinit);

/* ms880975 "BthAGPhoneExtEvent": called by the AG service; the event
 * values AG_PHONE_EVENT_* are names-only (held). */
AKARI_CE_IMPORT void BthAGPhoneExtEvent(DWORD dwEvent, DWORD dwParam,
                                        VOID *pvParam2) AKARI_CE_NAME(BthAGPhoneExtEvent);

/* aa450307 "BthAGGetLastDialed". */
AKARI_CE_IMPORT BOOL BthAGGetLastDialed(LPWSTR pwszNumber) AKARI_CE_NAME(BthAGGetLastDialed);

/* aa450308 "BthAGGetNameByPhoneNumber". */
AKARI_CE_IMPORT BOOL BthAGGetNameByPhoneNumber(LPCWSTR pwszNumber,
                                               LPWSTR pwszName) AKARI_CE_NAME(BthAGGetNameByPhoneNumber);

/* aa450309 "BthAGGetSpeedDial": the page prints "LPwSTR" (a case
 * artifact for LPWSTR). */
AKARI_CE_IMPORT BOOL BthAGGetSpeedDial(unsigned short usIndex,
                                       LPWSTR pwszNumber) AKARI_CE_NAME(BthAGGetSpeedDial);

/* aa450310 "BthAGSetServiceCallback". */
AKARI_CE_IMPORT DWORD BthAGSetServiceCallback(
    PFN_PhoneExtServiceCallback pfn) AKARI_CE_NAME(BthAGSetServiceCallback);

/* aa450324 "BthAGOverrideCallIn". */
AKARI_CE_IMPORT BOOL BthAGOverrideCallIn(BOOL fHandsfree) AKARI_CE_NAME(BthAGOverrideCallIn);

/* ms887483 "BthAGOverrideCallOut". */
AKARI_CE_IMPORT BOOL BthAGOverrideCallOut(BOOL fHandsfree) AKARI_CE_NAME(BthAGOverrideCallOut);

/* ------------------------------------------------------------------ */
/* AT command extension (Header/Link Library: Developer defined).      */
/* ------------------------------------------------------------------ */

/* aa450304 "BthAGATHandler": BOOL BthAGATHandler(LPSTR szCommand,
 * DWORD cbCommand); -- exported by the developer's extension module,
 * so it is declared without an import pin and enters no def. */
BOOL BthAGATHandler(LPSTR szCommand, DWORD cbCommand);

/* aa450305 "BthAGATSetCallback": CE 5.0 page prints no signature; the
 * CE 6.0 twin ee495634 prints "void BthAGATSetCallback
 * (PFN_SendATCommand pfn);" -- developer-defined, no pin, no def. */
void BthAGATSetCallback(PFN_SendATCommand pfn);

/* ------------------------------------------------------------------ */
/* Network component (Btagpub.h, Btagsvc_network.lib).                 */
/* ------------------------------------------------------------------ */

/* aa450318 "BthAGNetworkInit". */
AKARI_CE_IMPORT DWORD BthAGNetworkInit(HINSTANCE hInstance) AKARI_CE_NAME(BthAGNetworkInit);

/* aa450313 "BthAGNetworkDeinit": CE 5.0 page prints no signature; the
 * CE 6.0 twin ee495426: "void BthAGNetworkDeinit(void);". */
AKARI_CE_IMPORT void BthAGNetworkDeinit(void) AKARI_CE_NAME(BthAGNetworkDeinit);

/* aa450312 "BthAGNetworkAnswerCall". */
AKARI_CE_IMPORT DWORD BthAGNetworkAnswerCall(void) AKARI_CE_NAME(BthAGNetworkAnswerCall);

/* aa450316 "BthAGNetworkDropCall": the CE 5.0 signature block prints
 * "BthAGNetworkHangupCall" (artifact; the CE 6.0 twin ee495838 prints
 * the same body) -- the function is the page title. */
AKARI_CE_IMPORT DWORD BthAGNetworkDropCall(DWORD dwFlags) AKARI_CE_NAME(BthAGNetworkDropCall);

/* aa450314 "BthAGNetworkDialNumber". */
AKARI_CE_IMPORT DWORD BthAGNetworkDialNumber(LPSTR pszNumber) AKARI_CE_NAME(BthAGNetworkDialNumber);

/* aa450315 "BthAGNetworkGetCallState". */
AKARI_CE_IMPORT DWORD BthAGNetworkGetCallState(PDWORD pdwFlags) AKARI_CE_NAME(BthAGNetworkGetCallState);

/* aa450317 "BthAGNetworkHoldCall": the CE 5.0 signature block prints
 * "BthAgNetworkHoldCall" (case artifact). */
AKARI_CE_IMPORT DWORD BthAGNetworkHoldCall(void) AKARI_CE_NAME(BthAGNetworkHoldCall);

/* aa450319 "BthAGNetworkRejectCall". */
AKARI_CE_IMPORT DWORD BthAGNetworkRejectCall(void) AKARI_CE_NAME(BthAGNetworkRejectCall);

/* aa450320 "BthAGNetworkSwapCall". */
AKARI_CE_IMPORT DWORD BthAGNetworkSwapCall(void) AKARI_CE_NAME(BthAGNetworkSwapCall);

/* aa450321 "BthAGNetworkTransmitDTMF". */
AKARI_CE_IMPORT DWORD BthAGNetworkTransmitDTMF(LPSTR pszDTMF) AKARI_CE_NAME(BthAGNetworkTransmitDTMF);

/* aa450322 "BthAGNetworkUnholdCall". */
AKARI_CE_IMPORT DWORD BthAGNetworkUnholdCall(void) AKARI_CE_NAME(BthAGNetworkUnholdCall);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_BTAGPUB_H */
