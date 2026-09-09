/*
 * D3dm.h -- documented include-name alias for d3dm.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: D3dm.h" (118 pages);
 * documented-case alias.  This project carries the declarations in d3dm.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <D3dm.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide D3dm.h with d3dm.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "d3dm.h"
