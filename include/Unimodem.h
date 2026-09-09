/*
 * Unimodem.h -- documented include-name alias for tapi.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Unimodem.h" (1 pages);
 * the PHONECAPS page prints Unimodem.h; PHONECAPS is declared in tapi.h.  This project carries the declarations in tapi.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Unimodem.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Unimodem.h with tapi.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "Tapi.h"
