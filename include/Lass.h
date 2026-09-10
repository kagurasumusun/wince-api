/*
 * Lass.h -- Local Authentication Subsystem (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE
 * documentation (learn.microsoft.com previous-versions archive;
 * page ids cited per record).  This is the "Lass.h." row of the
 * Security book harvest (M95): one function (Coredll.lib).
 */

#ifndef AKARI_LASS_H
#define AKARI_LASS_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ms926124 "LASSReloadConfig" (trusted applications only; resets
 * all AEs to their initial states and reloads the LAP; implicitly
 * calls VerifyUser when master key protection is implemented). */
AKARI_CE_IMPORT BOOL LASSReloadConfig(void)
    AKARI_CE_NAME(LASSReloadConfig);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_LASS_H */
