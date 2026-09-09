/*
 * Btagpub.h -- documented include-name alias for btagpub.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Btagpub.h" (28 pages);
 * documented-case alias.  This project carries the declarations in btagpub.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Btagpub.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Btagpub.h with btagpub.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "btagpub.h"
