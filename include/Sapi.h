/*
 * Sapi.h -- documented include-name alias for sapi.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Sapi.h" (259 pages);
 * documented-case alias.  This project carries the declarations in sapi.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Sapi.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Sapi.h with sapi.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "sapi.h"
