/* Lockmgrhelp.h -- FSD lock-manager helpers (Fsdmgr.lib).
 *
 * Source pages: the three rows printing "Header: lockmgrhelp.h":
 * FSDMGR_CloseFileLockState (aa517920), FSDMGR_OpenFileLockState
 * (aa517922), FSDMGR_RemoveFileLock (aa517923, no printed
 * signature).  The Open/Close pair takes the compiled
 * PFILELOCKSTATE (Fsdmgr.h) and is declared.
 * See docs/inventory.md M79b.
 */

#ifndef AKARI_LOCKMGRHELP_H
#define AKARI_LOCKMGRHELP_H

#include "Fsdmgr.h"     /* PFILELOCKSTATE */

/* "FSDMGR_OpenFileLockState": print
 * `void FSDMGR_OpenFileLockState ( PFILELOCKSTATE pFileLockState );`. */
AKARI_CE_IMPORT void FSDMGR_OpenFileLockState(PFILELOCKSTATE pFileLockState)
                    AKARI_CE_NAME(FSDMGR_OpenFileLockState);

/* "FSDMGR_CloseFileLockState": print
 * `void FSDMGR_CloseFileLockState ( PFILELOCKSTATE pFileLockState );`. */
AKARI_CE_IMPORT void FSDMGR_CloseFileLockState(PFILELOCKSTATE pFileLockState)
                    AKARI_CE_NAME(FSDMGR_CloseFileLockState);

/* "FSDMGR_RemoveFileLock" (aa517923, Fsdmgr.lib row): page-text
 * recovery (M91) of the prototype line: `BOOL MyFSD_UnlockFileEx(
 * PACQUIREFILELOCKSTATE pAcquireFileLockState PRELEASEFILELOCKSTATE
 * pReleaseFileLockState DWORD dwHandle, DWORDdwReserved,
 * DWORDnNumberOfBytesToUnlockLow, DWORDnNumberOfBytesToUnlockHigh,
 * LPOVERLAPPEDlpOverlapped );` -- the print misprints the callee as
 * MyFSD_UnlockFileEx, drops the separators between the first three
 * parameters, and names PRELEASEFILELOCKSTATE (unpublished), so the
 * function stays recorded. */

#endif /* AKARI_LOCKMGRHELP_H */
