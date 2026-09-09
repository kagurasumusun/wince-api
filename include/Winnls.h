/*
 * Winnls.h -- documented include-name alias for winnls.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Winnls.h" (38 pages);
 * documented-case alias.  This project carries the declarations in winnls.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Winnls.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Winnls.h with winnls.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "winnls.h"
