/*
 * Celog.h -- documented include-name alias for celog.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Celog.h" (71 pages);
 * documented-case alias.  This project carries the declarations in celog.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Celog.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Celog.h with celog.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "celog.h"
