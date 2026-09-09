/*
 * Pimstore.h -- documented include-name alias for pimstore.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Pimstore.h" (67 pages);
 * documented-case alias.  This project carries the declarations in pimstore.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Pimstore.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Pimstore.h with pimstore.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "pimstore.h"
