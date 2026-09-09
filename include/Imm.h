/*
 * Imm.h -- documented include-name alias for imm.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Imm.h" (116 pages);
 * documented-case alias.  This project carries the declarations in imm.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Imm.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Imm.h with imm.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "imm.h"
