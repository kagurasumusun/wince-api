/*
 * Windows.h -- documented include-name alias for windows.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Windows.h" (223 pages);
 * documented-case alias.  This project carries the declarations in windows.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Windows.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Windows.h with windows.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "windows.h"
