/* Ipsec_api.h -- IPsec configuration API (Windows CE; Ipsec_api.lib,
 * def/ipsec_api-doc.def).  See docs/inventory.md M77c. */

#ifndef AKARI_IPSEC_API_H
#define AKARI_IPSEC_API_H

#include "Windef.h"    /* DWORD, PVOID, PBYTE */
#include "Objbase.h"   /* HRESULT */

/* "IPSEC_API_PARAM": print `typedef struct { DWORD id; PVOID val;
 * DWORD valSize;} IPSEC_API_PARAM, *PIPSEC_API_PARAM;` */
typedef struct {
    DWORD id;
    PVOID val;
    DWORD valSize;
} IPSEC_API_PARAM, *PIPSEC_API_PARAM;

/* "IPSEC_API_MODE_INFO": print. */
typedef struct {
    DWORD inAction;
    DWORD outAction;
    DWORD auth;
    PBYTE authInfo;
    DWORD authInfoSize;
    DWORD mmHashMask;
    DWORD mmEncMask;
    DWORD qmHashMask;
    DWORD qmEncMask;
    DWORD dhMask;
    DWORD protocol;
    DWORD scrIP;
} IPSEC_API_MODE_INFO, *PIPSEC_API_MODE_INFO;

AKARI_CE_IMPORT HRESULT IsIPSecRunning(void)
                    AKARI_CE_NAME(IsIPSecRunning);
AKARI_CE_IMPORT HRESULT StartIPSec(void) AKARI_CE_NAME(StartIPSec);
AKARI_CE_IMPORT HRESULT StopIPSec(void) AKARI_CE_NAME(StopIPSec);

/* ResetIPSecMode: print `HRESULT ResetIPSecMode( DWORD srcIP
 * DWORD flags);` -- missing comma repaired. */
AKARI_CE_IMPORT HRESULT ResetIPSecMode(DWORD srcIP, DWORD flags)
                    AKARI_CE_NAME(ResetIPSecMode);

/* SetIPSecConfig: print `HRESULT SetIPSecConfig(
 * IPSEC_API_PARAM param, DWORD flags);` */
AKARI_CE_IMPORT HRESULT SetIPSecConfig(IPSEC_API_PARAM param,
                    DWORD flags) AKARI_CE_NAME(SetIPSecConfig);

/* SetIPSecMode: print `HRESULT SetIPSecMode(
 * IPSEC_API_MODE_INFO modeInfo, DWORD flags);` */
AKARI_CE_IMPORT HRESULT SetIPSecMode(IPSEC_API_MODE_INFO modeInfo,
                    DWORD flags) AKARI_CE_NAME(SetIPSecMode);

#endif /* AKARI_IPSEC_API_H */
