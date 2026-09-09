/*
 * Extfile.h -- documented include-name alias for extfile.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Extfile.h" (1 pages);
 * documented-case alias.  This project carries the declarations in extfile.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Extfile.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Extfile.h with extfile.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "extfile.h"
