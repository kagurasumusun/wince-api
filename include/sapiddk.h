/*
 * sapiddk.h -- documented include-name alias for sapi.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: sapiddk.h" (2 pages);
 * lowercase print of the Sapiddk.h rows; records in sapi.h (M68).  This project carries the declarations in sapi.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <sapiddk.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide sapiddk.h with sapi.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "sapi.h"
