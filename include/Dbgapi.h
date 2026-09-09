/*
 * Dbgapi.h -- documented include-name alias for dbgapi.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Dbgapi.h" (14 pages);
 * documented-case alias.  This project carries the declarations in dbgapi.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Dbgapi.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Dbgapi.h with dbgapi.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "dbgapi.h"
