/*
 * Btagnetwork.h -- documented include-name alias for btagnetwork.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Btagnetwork.h" (2 pages);
 * documented-case alias.  This project carries the declarations in btagnetwork.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Btagnetwork.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Btagnetwork.h with btagnetwork.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "btagnetwork.h"
