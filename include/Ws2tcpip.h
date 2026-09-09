/*
 * Ws2tcpip.h -- documented include-name alias for ws2tcpip.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Ws2tcpip.h" (6 pages);
 * documented-case alias.  This project carries the declarations in ws2tcpip.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Ws2tcpip.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Ws2tcpip.h with ws2tcpip.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "ws2tcpip.h"
