/*
 * D3dmtypes.h -- documented include-name alias for d3dm.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: D3dmtypes.h" (65 pages);
 * D3dmtypes.h types/enums/structures are carried in d3dm.h (M67).  This project carries the declarations in d3dm.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <D3dmtypes.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide D3dmtypes.h with d3dm.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "d3dm.h"
