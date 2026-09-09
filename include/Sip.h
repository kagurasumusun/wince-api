/*
 * Sip.h -- documented include-name alias for sip.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Sip.h" (37 pages);
 * documented-case alias.  This project carries the declarations in sip.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Sip.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Sip.h with sip.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "sip.h"
