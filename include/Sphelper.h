/*
 * Sphelper.h -- documented include-name alias for sapi.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Sphelper.h" (28 pages);
 * Sphelper.h helper-function records are carried in sapi.h (M68).  This project carries the declarations in sapi.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Sphelper.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Sphelper.h with sapi.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "Sapi.h"
