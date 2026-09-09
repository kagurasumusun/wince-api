/*
 * ErrorRep.h -- documented include-name alias for errorrep.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: ErrorRep.h" (1 pages);
 * documented-case alias.  This project carries the declarations in errorrep.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <ErrorRep.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide ErrorRep.h with errorrep.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "errorrep.h"
