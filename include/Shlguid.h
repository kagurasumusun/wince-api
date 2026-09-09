/*
 * Shlguid.h -- documented include-name alias for aygshell.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Shlguid.h" (1 pages);
 * the FILECHANGENOTIFY page prints Shlguid.h; the declaration is carried in aygshell.h.  This project carries the declarations in aygshell.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Shlguid.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Shlguid.h with aygshell.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "aygshell.h"
