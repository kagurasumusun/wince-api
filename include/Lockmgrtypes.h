/* Lockmgrtypes.h -- FSD lock-manager callback type.
 *
 * Source page: PACQUIREFILELOCKSTATE (aa517930), Requirements row
 * "Header: lockmgrtypes.h".  The twin PRELEASEFILELOCKSTATE type is
 * not printed by any CE page (named by FSDMGR_AcquireFileLock), so
 * that function stays recorded in Lockmgrhelp.h.
 * See docs/inventory.md M79b.
 */

#ifndef AKARI_LOCKMGRTYPES_H
#define AKARI_LOCKMGRTYPES_H

#include "Fsdmgr.h"     /* PFILELOCKSTATE */

/* aa517930 "PACQUIREFILELOCKSTATE": print `typedef VOID
 * (*PACQUIREFILELOCKSTATE)( DWORD dwFile, PFILELOCKSTATE*
 * ppFileLockState );` (FILELOCKSTATE home is Fsdmgr.h, aa517917). */
typedef VOID (*PACQUIREFILELOCKSTATE)(DWORD dwFile,
                                   PFILELOCKSTATE *ppFileLockState);

#endif /* AKARI_LOCKMGRTYPES_H */
