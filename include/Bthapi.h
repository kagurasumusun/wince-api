/*
 * Bthapi.h -- documented include-name alias for bthapi.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Bthapi.h" (36 pages);
 * documented-case alias.  This project carries the declarations in bthapi.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Bthapi.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Bthapi.h with bthapi.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "bthapi.h"
