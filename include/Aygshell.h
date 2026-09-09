/*
 * Aygshell.h -- documented include-name alias for aygshell.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Aygshell.h" (6 pages);
 * documented-case alias.  This project carries the declarations in aygshell.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Aygshell.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Aygshell.h with aygshell.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "aygshell.h"
