/*
 * Dmoimpl.h -- DirectShow Media Object (DMO) implementation template.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE DMO Base
 * Class Reference pages (harvested into build/rows.json; Requirements
 * rows print Header Dmoimpl.h).  The API is a C++ class template --
 * aa451296 prints the declaration syntax `template <class _DERIVED_,
 * int NUMBEROFINPUTS, int NUMBEROFOUTPUTS> class IMediaObjectImpl :
 * public IMediaObject` -- so it has no C-callable surface and is
 * recorded only (M80 record-only policy; IMediaObject and
 * DMO_MEDIA_TYPE are carried by Dmo.h).  See docs/inventory.md M85.
 */

#ifndef AKARI_DMOIMPL_H
#define AKARI_DMOIMPL_H

#ifdef __cplusplus
extern "C" {
#endif

/* aa451296 "Declaring the Derived Class": template declaration
 * syntax recorded above; a derived class is created by inheriting
 * IMediaObjectImpl<CMyDmoClass, inputs, outputs>. */

/* _DERIVED_ helper overrides (aa451573-aa451577, class C++ methods):
 *  - `HRESULT InternalAcceptingInput(DWORDdwInputStreamIndex);`
 *  - `HRESULT InternalCheckInputType(DWORDdwInputStreamIndex,
 *    const DMO_MEDIA_TYPE* pmt);`
 *  - `HRESULT InternalCheckOutputType(DWORDdwOutputStreamIndex,
 *    const DMO_MEDIA_TYPE* pmt);`
 *  - `void Lock(void);`
 *  - `void Unlock(void);` */

/* ms924129 "LockIt Internal Class": internal helper class; print
 * `LockIt(_DERIVED_* p);` (constructor locks the object, destructor
 * unlocks it). */

/* IMediaObjectImpl public helpers (ms931406-ms931411, C++ methods):
 *  - `bool CheckTypesSet(void);` (ms931406)
 *  - `const DMO_MEDIA_TYPE *InputType(DWORDulInputStreamIndex);`
 *    (ms931408)
 *  - `bool InputTypeSet(DWORDulInputStreamIndex);` (ms931409)
 *  - `const DMO_MEDIA_TYPE *OutputType(DWORDulOutputStreamIndex);`
 *    (ms931410)
 *  - `bool OutputTypeSet(DWORDulOutputStreamIndex);` (ms931411) */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_DMOIMPL_H */
