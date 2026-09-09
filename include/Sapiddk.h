/*
 * Sapiddk.h -- documented include-name alias for sapi.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Sapiddk.h" (120 pages);
 * SAPI engine-side DDI interface records are carried in sapi.h (M68).  This project carries the declarations in sapi.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Sapiddk.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Sapiddk.h with sapi.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "sapi.h"
