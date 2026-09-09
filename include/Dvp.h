/*
 * Dvp.h -- documented include-name alias for dvp.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Dvp.h" (26 pages);
 * documented-case alias.  This project carries the declarations in dvp.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Dvp.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Dvp.h with dvp.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "dvp.h"
