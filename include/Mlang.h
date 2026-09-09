/*
 * Mlang.h -- documented include-name alias for mlang.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Mlang.h" (107 pages);
 * documented-case alias.  This project carries the declarations in mlang.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Mlang.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Mlang.h with mlang.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "mlang.h"
