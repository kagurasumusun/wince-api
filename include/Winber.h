/*
 * Winber.h -- documented include-name alias for winber.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Winber.h" (13 pages);
 * documented-case alias.  This project carries the declarations in winber.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Winber.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Winber.h with winber.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "winber.h"
