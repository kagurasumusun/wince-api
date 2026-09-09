/*
 * Tvout.h -- documented include-name alias for tvout.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Tvout.h" (1 pages);
 * documented-case alias.  This project carries the declarations in tvout.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Tvout.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Tvout.h with tvout.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "tvout.h"
