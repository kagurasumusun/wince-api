/*
 * D3dmcaps.h -- documented include-name alias for d3dm.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: D3dmcaps.h" (17 pages);
 * D3DMCAPS is carried in d3dm.h (M67).  This project carries the declarations in d3dm.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <D3dmcaps.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide D3dmcaps.h with d3dm.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "D3dm.h"
