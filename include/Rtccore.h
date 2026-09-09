/*
 * Rtccore.h -- documented include-name alias for rtccore.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Rtccore.h"; documented-case alias (349 pages);
 * this project carries the declarations in rtccore.h.  On a case-sensitive
 * filesystem (the LLVM-WinCE cross toolchain) this alias keeps
 * #include <Rtccore.h> compiling.  NOTE: a case-insensitive checkout
 * (Windows) may collide Rtccore.h with another header -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "rtccore.h"
