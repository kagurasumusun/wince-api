/*
 * Cchannel.h -- documented include-name alias for cchannel.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Cchannel.h" (16 pages);
 * documented-case alias.  This project carries the declarations in cchannel.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Cchannel.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Cchannel.h with cchannel.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "cchannel.h"
