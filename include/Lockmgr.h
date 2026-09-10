/* Lockmgr.h -- FSD lock-manager acquire entry (record-only).
 *
 * Source page: FSDMGR_AcquireFileLock (aa517919), the single row
 * printing "Header: lockmgr.h".  Its print names the
 * PRELEASEFILELOCKSTATE type (never printed by any CE page) and
 * drops the separators between the first three parameters, so the
 * function is recorded rather than declared; the acquire callback
 * type itself is grounded in Lockmgrtypes.h.
 * See docs/inventory.md M79b.
 */

#ifndef AKARI_LOCKMGR_H
#define AKARI_LOCKMGR_H

/* aa517919 "FSDMGR_AcquireFileLock" (Fsdmgr.lib row): print `BOOL
 * FSDMGR_AcquireFileLock( PACQUIREFILELOCKSTATE pAcquireFileLockState
 * PRELEASEFILELOCKSTATE pReleaseFileLockState DWORD dwHandle,
 * DWORDdwFlags, DWORDdwReserved, DWORDnNumberOfBytesToLockLow,
 * DWORDnNumberOfBytesToLockHigh, LPOVERLAPPEDlpOverlapped );` --
 * PRELEASEFILELOCKSTATE unpublished, separator dropout; recorded. */

#endif /* AKARI_LOCKMGR_H */
