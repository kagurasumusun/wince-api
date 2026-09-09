/* Autodial.h -- Autodial helper module (Windows CE; Autodial.lib).
 * See docs/inventory.md M77b. */

#ifndef AKARI_AUTODIAL_H
#define AKARI_AUTODIAL_H

#include "Windef.h"    /* DWORD, TCHAR */

AKARI_CE_IMPORT DWORD AutoDialCleanupModule(void)
                    AKARI_CE_NAME(AutoDialCleanupModule);
AKARI_CE_IMPORT DWORD AutoDialEndConnection(void)
                    AKARI_CE_NAME(AutoDialEndConnection);
AKARI_CE_IMPORT DWORD AutoDialInitializeModule(void)
                    AKARI_CE_NAME(AutoDialInitializeModule);
AKARI_CE_IMPORT DWORD AutoDialStartConnection(TCHAR *szUseDialEntry)
                    AKARI_CE_NAME(AutoDialStartConnection);

/* AutoDialGetConnectionStatus: print `DWORD
 * AutoDialGetConnectionStatus( RASCONNSTATUS* lpRasConn,
 * TCHAR* szRasName);` -- the RASCONNSTATUS type is not published on
 * any CE page (Ras.h M75f hold family); recorded verbatim. */

#endif /* AKARI_AUTODIAL_H */
