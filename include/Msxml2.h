/*
 * Msxml2.h -- documented include-name alias for msxml2.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Msxml2.h" (282 pages);
 * documented-case alias.  This project carries the declarations in msxml2.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Msxml2.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Msxml2.h with msxml2.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "msxml2.h"
