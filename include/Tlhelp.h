/*
 * Tlhelp.h -- documented include-name alias for tlhelp32.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Tlhelp.h" (2 pages);
 * the Heap32* pages print Tlhelp.h; the tool help declarations live in tlhelp32.h.  This project carries the declarations in tlhelp32.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Tlhelp.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Tlhelp.h with tlhelp32.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "Tlhelp32.h"
