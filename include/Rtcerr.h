/*
 * Rtcerr.h -- documented include-name alias for rtccore.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Rtcerr.h"; RTC_E_/RTC_S_ values carried in rtccore.h (M69);
 * this project carries the declarations in rtccore.h.  On a case-sensitive
 * filesystem (the LLVM-WinCE cross toolchain) this alias keeps
 * #include <Rtcerr.h> compiling.  NOTE: a case-insensitive checkout
 * (Windows) may collide Rtcerr.h with another header -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "rtccore.h"
