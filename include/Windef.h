/*
 * Windef.h -- documented include-name alias for windef.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Windef.h" (4 pages);
 * documented-case alias.  This project carries the declarations in windef.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Windef.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Windef.h with windef.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "windef.h"
