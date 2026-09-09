/*
 * Snmpapi.h -- documented include-name alias for snmpapi.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Snmpapi.h" (1 pages);
 * documented-case alias.  This project carries the declarations in snmpapi.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Snmpapi.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Snmpapi.h with snmpapi.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "snmpapi.h"
