/*
 * Shtypes.h -- documented include-name alias for shtypes.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Shtypes.h" (2 pages);
 * documented-case alias.  This project carries the declarations in shtypes.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Shtypes.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Shtypes.h with shtypes.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "shtypes.h"
