/*
 * CEDDK.h -- documented include-name alias for ceddk.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: CEDDK.h" (55 pages);
 * documented-case alias.  This project carries the declarations in ceddk.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <CEDDK.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide CEDDK.h with ceddk.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "ceddk.h"
