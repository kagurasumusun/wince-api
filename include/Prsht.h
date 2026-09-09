/*
 * Prsht.h -- documented include-name alias for prsht.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: Prsht.h" (33 pages);
 * documented-case alias.  This project carries the declarations in prsht.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <Prsht.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide Prsht.h with prsht.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "prsht.h"
