/*
 * Urlmon.h -- documented include-name alias for urlmon.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Urlmon.h" (168 pages);
 * documented-case alias.  This project carries the declarations in urlmon.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Urlmon.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Urlmon.h with urlmon.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "urlmon.h"
