/*
 * Windowsx.h -- documented include-name alias for windowsx.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Windowsx.h" (2 pages);
 * documented-case alias.  This project carries the declarations in windowsx.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Windowsx.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Windowsx.h with windowsx.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "windowsx.h"
