/*
 * Shobjidl.h -- documented include-name alias for shobjidl.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Shobjidl.h" (31 pages);
 * documented-case alias.  This project carries the declarations in shobjidl.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Shobjidl.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Shobjidl.h with shobjidl.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "shobjidl.h"
