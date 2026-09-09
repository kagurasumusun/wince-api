/*
 * Pwinuser.h -- documented include-name alias for pwinuser.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Pwinuser.h" (8 pages);
 * documented-case alias.  This project carries the declarations in pwinuser.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Pwinuser.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Pwinuser.h with pwinuser.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "pwinuser.h"
