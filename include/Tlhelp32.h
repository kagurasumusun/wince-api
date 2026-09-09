/*
 * Tlhelp32.h -- documented include-name alias for tlhelp32.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Tlhelp32.h" (16 pages);
 * documented-case alias.  This project carries the declarations in tlhelp32.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Tlhelp32.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Tlhelp32.h with tlhelp32.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "tlhelp32.h"
