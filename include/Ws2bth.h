/*
 * Ws2bth.h -- documented include-name alias for ws2bth.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Ws2bth.h" (11 pages);
 * documented-case alias.  This project carries the declarations in ws2bth.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Ws2bth.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Ws2bth.h with ws2bth.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "ws2bth.h"
