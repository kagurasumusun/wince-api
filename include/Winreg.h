/*
 * Winreg.h -- documented include-name alias for winreg.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Winreg.h" (14 pages);
 * documented-case alias.  This project carries the declarations in winreg.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Winreg.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Winreg.h with winreg.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "winreg.h"
