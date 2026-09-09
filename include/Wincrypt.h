/*
 * Wincrypt.h -- documented include-name alias for wincrypt.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Wincrypt.h" (201 pages);
 * documented-case alias.  This project carries the declarations in wincrypt.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Wincrypt.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Wincrypt.h with wincrypt.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "wincrypt.h"
