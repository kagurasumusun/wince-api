/*
 * Bthsdpdef.h -- documented include-name alias for bthsdpdef.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Bthsdpdef.h" (9 pages);
 * documented-case alias.  This project carries the declarations in bthsdpdef.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Bthsdpdef.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Bthsdpdef.h with bthsdpdef.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "bthsdpdef.h"
