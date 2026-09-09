/*
 * Tapicomn.h -- documented include-name alias for tapicomn.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Tapicomn.h" (83 pages);
 * documented-case alias.  This project carries the declarations in tapicomn.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Tapicomn.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Tapicomn.h with tapicomn.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "tapicomn.h"
