/*
 * Commdlg.h -- documented include-name alias for commdlg.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Commdlg.h" (20 pages);
 * documented-case alias.  This project carries the declarations in commdlg.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Commdlg.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Commdlg.h with commdlg.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "commdlg.h"
