/*
 * Commctrl.h -- documented include-name alias for commctrl.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Commctrl.h" (807 pages);
 * documented-case alias.  This project carries the declarations in commctrl.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Commctrl.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Commctrl.h with commctrl.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "commctrl.h"
