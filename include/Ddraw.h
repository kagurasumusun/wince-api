/*
 * Ddraw.h -- documented include-name alias for ddraw.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Ddraw.h" (102 pages);
 * documented-case alias.  This project carries the declarations in ddraw.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Ddraw.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Ddraw.h with ddraw.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "ddraw.h"
