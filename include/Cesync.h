/*
 * Cesync.h -- documented-case alias for the CE Sync COM surface.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * The CE Sync (COM) pages print Header: Cesync.h; their one harvested
 * symbol -- STOREINFO (COM) ms896271, tag tagStoreInfo, with the
 * SCF_SINGLE_THREAD / SCF_SIMULATE_RTS uFlags rows -- is carried by
 * Objbase.h (M73b, which owns the STOREINFO / PSTOREINFO typedef per
 * the Storemgr.h collision note).  Objidl.h alias precedent.
 */
#include "Objbase.h"
