/*
 * Shellapi.h -- documented include-name alias for shellapi.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Shellapi.h" (16 pages);
 * documented-case alias.  This project carries the declarations in shellapi.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Shellapi.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Shellapi.h with shellapi.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "shellapi.h"
