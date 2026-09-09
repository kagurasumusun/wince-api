/*
 * Sipapi.h -- documented include-name alias for sipapi.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Sipapi.h" (11 pages);
 * documented-case alias.  This project carries the declarations in sipapi.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Sipapi.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Sipapi.h with sipapi.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "sipapi.h"
