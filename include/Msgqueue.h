/*
 * Msgqueue.h -- documented include-name alias for msgqueue.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Msgqueue.h" (8 pages);
 * documented-case alias.  This project carries the declarations in msgqueue.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Msgqueue.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Msgqueue.h with msgqueue.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "msgqueue.h"
