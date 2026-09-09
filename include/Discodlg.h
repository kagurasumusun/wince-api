/*
 * Discodlg.h -- documented include-name alias for discodlg.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Discodlg.h" (77 pages);
 * documented-case alias.  This project carries the declarations in discodlg.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Discodlg.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Discodlg.h with discodlg.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "discodlg.h"
