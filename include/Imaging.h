/*
 * Imaging.h -- documented include-name alias for imaging.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Imaging.h" (97 pages);
 * documented-case alias.  This project carries the declarations in imaging.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Imaging.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Imaging.h with imaging.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "imaging.h"
