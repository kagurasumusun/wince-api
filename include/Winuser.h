/*
 * Winuser.h -- documented include-name alias for winuser.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Winuser.h" (373 pages);
 * documented-case alias.  This project carries the declarations in winuser.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Winuser.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Winuser.h with winuser.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "winuser.h"
