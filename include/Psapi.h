/*
 * Psapi.h -- documented include-name alias for psapi.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Psapi.h" (2 pages);
 * documented-case alias.  This project carries the declarations in psapi.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Psapi.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Psapi.h with psapi.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "psapi.h"
