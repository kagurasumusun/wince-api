/*
 * Pcommctrl.h -- documented include-name alias for commctrl.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Pcommctrl.h" (3 pages,
 * the ListView_*WorkAreas macro set); the macros are RECORDED in
 * commctrl.h (M94: their pages print the full #define bodies, which
 * reference the held value-less LVM_* constants).  This project carries
 * the records in commctrl.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Pcommctrl.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Pcommctrl.h with commctrl.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "Commctrl.h"
