/*
 * Natedit.h -- documented include-name alias for natedit.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Natedit.h" (20 pages);
 * documented-case alias.  This project carries the declarations in natedit.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Natedit.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Natedit.h with natedit.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "natedit.h"
