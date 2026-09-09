/*
 * Shelwapi.h -- documented include-name alias for shelwapi.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Shelwapi.h" (1 pages);
 * documented-case alias.  This project carries the declarations in shelwapi.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Shelwapi.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Shelwapi.h with shelwapi.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "shelwapi.h"
