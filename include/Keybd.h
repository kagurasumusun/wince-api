/*
 * Keybd.h -- documented include-name alias for keybd.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Keybd.h" (1 pages);
 * documented-case alias.  This project carries the declarations in keybd.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Keybd.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Keybd.h with keybd.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "keybd.h"
