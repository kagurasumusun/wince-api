/*
 * Winnt.h -- documented include-name alias for winnt.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Winnt.h" (9 pages);
 * documented-case alias.  This project carries the declarations in winnt.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Winnt.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Winnt.h with winnt.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "winnt.h"
