/*
 * Notify.h -- documented include-name alias for notify.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Notify.h" (12 pages);
 * documented-case alias.  This project carries the declarations in notify.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Notify.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Notify.h with notify.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "notify.h"
