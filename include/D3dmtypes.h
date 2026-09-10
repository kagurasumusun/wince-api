/*
 * D3dmtypes.h -- documented include-name alias for d3dm.h.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE-era Requirements rows print "Header: D3dmtypes.h" (65 pages);
 * D3dmtypes.h types/enums/structures are carried in d3dm.h (M67).  This project carries the declarations in d3dm.h; on a
 * case-sensitive filesystem (the LLVM-WinCE cross toolchain) this
 * alias keeps #include <D3dmtypes.h> compiling.  NOTE: a case-insensitive
 * checkout (Windows) would collide D3dmtypes.h with d3dm.h -- see
 * docs/inventory.md (header-name compatibility unit).
 */

#include "D3dm.h"/* ------------------------------------------------------------------
 * Book surface: d3dm (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms939139 D3DMCLEAR Values (Header: D3dmtypes.h.) */
/* ms939144 D3DMCOLORWRITEENABLE Values (Header: D3dmtypes.h.) */
/* ms928308 D3DMCS Values (Header: D3dmtypes.h.) */
/* ms907708 D3DMFVF Values (Header: D3dmtypes.h.) */
/* ms907711 D3DMFVF_TEXCOORDSIZE Macros (Header: D3dmtypes.h.) */
/* ms907717 D3DMLOCK Values (Header: D3dmtypes.h.) */
/* ms907736 D3DMPV Values (Header: D3dmtypes.h.) */
/* ms907746 D3DMTA Values (Header: D3dmtypes.h.) */
/* ms907754 D3DMTSS_TCI Values (Header: D3dmtypes.h.) */
/* ms907755 D3DMUSAGE Values (Header: D3dmtypes.h.) */
/* ms907761 D3DMWRAPCOORD Values (Header: D3dmtypes.h.) */

