/*
 * Excpt.h -- documented include-name alias for excpt.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Excpt.h" (4 pages);
 * documented-case alias.  This project carries the declarations in excpt.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Excpt.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Excpt.h with excpt.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "excpt.h"
