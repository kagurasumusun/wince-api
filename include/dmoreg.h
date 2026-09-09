/*
 * dmoreg.h -- DMO filter registration for the Akari API.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  The single DMO Reference page whose
 * Requirements row prints Header: Dmoreg.h:
 *
 *   aa452529 "DMORegisterFilter" -- OS Versions: "Windows CE .NET
 *   4.1 and later."; Link Library: Msdmo.lib (-> def/msdmo-doc.def;
 *   DMORegister itself prints no Requirements block at all, see
 *   dmo.h).  STDAPI return (objbase.h macro) and unsigned long
 *   parameters verbatim from the print.
 */

#ifndef AKARI_DMOREG_H
#define AKARI_DMOREG_H

#include "dmo.h"

#ifdef __cplusplus
extern "C" {
#endif

/* The page prints the return type as STDAPI; objbase.h carries the
 * STDAPI token as an empty convention macro, so the effective type
 * is HRESULT (CoInitialize ms886303 precedent). */
AKARI_CE_IMPORT HRESULT DMORegisterFilter(
                    LPCWSTR szName,
                    REFCLSID clsidDMO,
                    REFGUID guidCategory,
                    REFCLSID clsidAutoWrap,
                    DWORD dwFlags,
                    unsigned long ulInTypes,
                    const DMO_PARTIAL_MEDIATYPE *pInTypes,
                    unsigned long ulOutTypes,
                    const DMO_PARTIAL_MEDIATYPE *pOutTypes) AKARI_CE_NAME(DMORegisterFilter);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_DMOREG_H */
