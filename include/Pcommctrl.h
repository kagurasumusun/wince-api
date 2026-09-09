/*
 * Pcommctrl.h -- documented include-name alias for commctrl.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Pcommctrl.h" (3 pages);
 * the ListView_*WorkAreas macro pages print Pcommctrl.h; the macros are declared in commctrl.h.  This project carries the declarations in commctrl.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Pcommctrl.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Pcommctrl.h with commctrl.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "commctrl.h"
