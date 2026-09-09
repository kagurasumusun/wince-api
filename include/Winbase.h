/*
 * Winbase.h -- documented include-name alias for winbase.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Winbase.h" (237 pages);
 * documented-case alias.  This project carries the declarations in winbase.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Winbase.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Winbase.h with winbase.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "winbase.h"
