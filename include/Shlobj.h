/*
 * Shlobj.h -- documented include-name alias for shlobj.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Shlobj.h" (14 pages);
 * documented-case alias.  This project carries the declarations in shlobj.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Shlobj.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Shlobj.h with shlobj.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "shlobj.h"
