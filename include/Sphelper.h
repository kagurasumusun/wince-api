/*
 * Sphelper.h -- documented include-name alias for sapi.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Sphelper.h" (28 pages);
 * Sphelper.h helper-function records are carried in sapi.h (M68).  This project carries the declarations in sapi.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Sphelper.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Sphelper.h with sapi.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "Sapi.h"/* ------------------------------------------------------------------
 * Book surface: sapi (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
typedef struct constCLSID constCLSID;   /* opaque carrier (layout unpublished) */
typedef struct constWCHAR constWCHAR;   /* opaque carrier (layout unpublished) */
/* ms893493 SpCreateNewToken (By Category ID): print `` */
/* (record-only: parameter or return type unpublished) */
/* ms893494 SpCreateNewToken (By Token ID): print `` */
/* (record-only: parameter or return type unpublished) */
/* ms893495 SpCreateNewTokenEx (By Category ID): print `` */
/* (record-only: parameter or return type unpublished) */
/* ms893496 SpCreateNewTokenEx (By Token ID): print `` */
/* (record-only: parameter or return type unpublished) */

