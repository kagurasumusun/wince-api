/*
 * Winscard.h -- documented include-name alias for winscard.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Winscard.h" (31 pages);
 * documented-case alias.  This project carries the declarations in winscard.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Winscard.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Winscard.h with winscard.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "winscard.h"
