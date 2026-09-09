/*
 * Mmsystem.h -- documented include-name alias for mmsystem.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Mmsystem.h" (94 pages);
 * documented-case alias.  This project carries the declarations in mmsystem.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Mmsystem.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Mmsystem.h with mmsystem.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "mmsystem.h"
