/*
 * Cpl.h -- documented include-name alias for cpl.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Cpl.h" (9 pages);
 * documented-case alias.  This project carries the declarations in cpl.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Cpl.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Cpl.h with cpl.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "cpl.h"
