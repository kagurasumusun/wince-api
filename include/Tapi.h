/*
 * Tapi.h -- documented include-name alias for tapi.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Tapi.h" (198 pages);
 * documented-case alias.  This project carries the declarations in tapi.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Tapi.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Tapi.h with tapi.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "tapi.h"
