/*
 * Winsock2.h -- documented include-name alias for winsock2.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Winsock2.h" (106 pages);
 * documented-case alias.  This project carries the declarations in winsock2.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Winsock2.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Winsock2.h with winsock2.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "winsock2.h"
