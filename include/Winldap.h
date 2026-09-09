/*
 * Winldap.h -- documented include-name alias for winldap.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Winldap.h" (101 pages);
 * documented-case alias.  This project carries the declarations in winldap.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Winldap.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Winldap.h with winldap.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "winldap.h"
