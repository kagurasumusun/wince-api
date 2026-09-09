/*
 * Pchannel.h -- documented include-name alias for cchannel.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Pchannel.h" (2 pages);
 * the CHANNEL_DEF/CHANNEL_PDU_HEADER pages print Pchannel.h; the declarations live in cchannel.h.  This project carries the declarations in cchannel.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Pchannel.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Pchannel.h with cchannel.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "cchannel.h"
