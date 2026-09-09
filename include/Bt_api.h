/*
 * Bt_api.h -- documented include-name alias for bt_api.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Bt_api.h" (52 pages);
 * documented-case alias.  This project carries the declarations in bt_api.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Bt_api.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Bt_api.h with bt_api.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "bt_api.h"
