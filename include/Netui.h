/*
 * Netui.h -- documented include-name alias for tapi.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Netui.h" (1 pages);
 * the LINECONFIGDATA page prints Netui.h; LINECONFIGDATA is declared in tapi.h.  This project carries the declarations in tapi.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Netui.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Netui.h with tapi.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "Tapi.h"
