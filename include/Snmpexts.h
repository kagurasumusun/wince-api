/*
 * Snmpexts.h -- documented include-name alias for snmpexts.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Snmpexts.h" (3 pages);
 * documented-case alias.  This project carries the declarations in snmpexts.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Snmpexts.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Snmpexts.h with snmpexts.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "snmpexts.h"
