/*
 * Ws2spi.h -- documented include-name alias for ws2spi.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Ws2spi.h" (40 pages);
 * documented-case alias.  This project carries the declarations in ws2spi.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Ws2spi.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Ws2spi.h with ws2spi.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "ws2spi.h"
