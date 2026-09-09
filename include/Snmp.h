/*
 * Snmp.h -- documented include-name alias for snmp.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Snmp.h" (38 pages);
 * documented-case alias.  This project carries the declarations in snmp.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Snmp.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Snmp.h with snmp.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "snmp.h"
