/*
 * Dmo.h -- DirectX Media Objects (DMO) for the Akari API.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Declarations are annotated with the
 * official Microsoft Windows CE 5.0 documentation pages they are
 * taken from ((v=msdn.10) Learn-archive IDs), harvested from the
 * *Graphics and Multimedia Technologies -> Media -> DirectShow ->
 * DMO Reference* book (93 leaves, tools/manifests/dmo.manifest; see
 * docs/inventory.md M71c).
 *
 * Header rows: 65 pages print **Dmo.h**; one function page prints
 * **Dmoreg.h** (aa452529 DMORegisterFilter -> include/dmoreg.h).
 * The 12 Dmoimpl.h pages (the _DERIVED_ / IMediaObjectImpl C++ base
 * class helpers: aa451573 InternalAcceptingInput, aa451574
 * InternalCheckInputType, aa451575 InternalCheckOutputType,
 * aa451576 Lock, aa451577 Unlock and siblings) are deferred to a
 * C++-class milestone (recorded gap).
 *
 * Link Library rows: Dmoguid.lib on the interface/structure pages
 * (GUID linkage, no export surface -- the Uuid.lib precedent) and
 * **Msdmo.lib** on 12 function pages -> def/msdmo-doc.def
 * (name-only; ordinals are not published).  DMORegister (aa451608)
 * prints NO Requirements block at all (no Header, no Link Library
 * row) -- its signature is declared here with that recorded, and it
 * is excluded from the def file.
 *
 * OS Versions rows: "Windows CE .NET 4.1 and later." throughout the
 * book (inside this tree's CE 4.2+ scope; unguarded).
 *
 * Archive artifacts (spacing-only repairs, prints recorded):
 * DMO_MEDIA_TYPE's glued tokens (GUIDmajortype, ULONGlSampleSize),
 * its bare "[size_is(cbFormat)]" IDL annotation (kept in brackets),
 * and DMOUnregisterFilter's trailing parameter comma
 * "(REFCLSIDclsidAutoWrap,)" -- the trailing comma is dropped for
 * compilation, print recorded.
 */

#ifndef AKARI_DMO_H
#define AKARI_DMO_H

#include "Windef.h"    /* DWORD, BOOL, ULONG, WCHAR, LPCWSTR */
#include "Winnt.h"     /* GUID, CLSID, BYTE */
#include "Objbase.h"   /* IUnknown, REFGUID, REFCLSID */
#include "Dshow.h"     /* REFERENCE_TIME carrier (M70b closure) */

#ifdef __cplusplus
extern "C" {
#endif

/* --- Interfaces (opaque forwards + verbatim records, M44 policy). --- */

typedef struct IDMOQualityControl IDMOQualityControl;
typedef struct IDMOVideoOutputOptimizations IDMOVideoOutputOptimizations;
typedef struct IEnumDMO IEnumDMO;
typedef struct IMediaBuffer IMediaBuffer;
typedef struct IMediaObject IMediaObject;
typedef struct IMediaObjectInPlace IMediaObjectInPlace;

/* --- Structures (verbatim prints, Dmo.h rows). ---------------------- */

/* aa451601 "DMO_MEDIA_TYPE": Dmoguid.lib row (GUID linkage).  The
 * print glues the member types to the names and carries the bare
 * IDL annotation "[size_is(cbFormat)]" (neutralized to brackets;
 * identical shape to AM_MEDIA_TYPE, ms925337). */
typedef struct _DMOMediaType {
    GUID  majortype;
    GUID  subtype;
    BOOL  bFixedSizeSamples;
    BOOL  bTemporalCompression;
    ULONG lSampleSize;
    GUID  formattype;
    IUnknown *pUnk;
    ULONG cbFormat;
    /* [size_is(cbFormat)] */
    BYTE  *pbFormat;
} DMO_MEDIA_TYPE;

/* aa451602 "DMO_OUTPUT_DATA_BUFFER" (+ P alias as printed). */
typedef struct _DMO_OUTPUT_DATA_BUFFER {
    IMediaBuffer *pBuffer;
    DWORD dwStatus;
    REFERENCE_TIME rtTimestamp;
    REFERENCE_TIME rtTimelength;
} DMO_OUTPUT_DATA_BUFFER, *PDMO_OUTPUT_DATA_BUFFER;

/* aa451605 "DMO_PARTIAL_MEDIATYPE" (+ P alias as printed). */
typedef struct _DMO_PARTIAL_MEDIATYPE {
    GUID type;
    GUID subtype;
} DMO_PARTIAL_MEDIATYPE, *PDMO_PARTIAL_MEDIATYPE;

/* --- Enumerated types (verbatim prints, all values printed). -------- */

/* aa451594 "DMO_ENUM_FLAGS". */
enum DMO_ENUM_FLAGS {
    DMO_ENUMF_INCLUDE_KEYED = 0x00000001
};

/* aa451599 "DMO_INPUT_DATA_BUFFER_FLAGS". */
enum _DMO_INPUT_DATA_BUFFER_FLAGS {
    DMO_INPUT_DATA_BUFFERF_SYNCPOINT   = 0x00000001,
    DMO_INPUT_DATA_BUFFERF_TIME        = 0x00000002,
    DMO_INPUT_DATA_BUFFERF_TIMELENGTH  = 0x00000004
};

/* aa451600 "DMO_INPUT_STREAM_INFO_FLAGS". */
enum _DMO_INPUT_STREAM_INFO_FLAGS {
    DMO_INPUT_STREAMF_WHOLE_SAMPLES             = 0x00000001,
    DMO_INPUT_STREAMF_SINGLE_SAMPLE_PER_BUFFER  = 0x00000002,
    DMO_INPUT_STREAMF_FIXED_SAMPLE_SIZE         = 0x00000004,
    DMO_INPUT_STREAMF_HOLDS_BUFFERS             = 0x00000008
};

/* aa451603 "DMO_OUTPUT_DATA_BUFFER_FLAGS". */
enum _DMO_OUTPUT_DATA_BUFFER_FLAGS {
    DMO_OUTPUT_DATA_BUFFERF_SYNCPOINT   = 0x00000001,
    DMO_OUTPUT_DATA_BUFFERF_TIME        = 0x00000002,
    DMO_OUTPUT_DATA_BUFFERF_TIMELENGTH  = 0x00000004,
    DMO_OUTPUT_DATA_BUFFERF_INCOMPLETE  = 0x01000000
};

/* aa451604 "DMO_OUTPUT_STREAM_INFO_FLAGS". */
enum _DMO_OUTPUT_STREAM_INFO_FLAGS {
    DMO_OUTPUT_STREAMF_WHOLE_SAMPLES            = 0x00000001,
    DMO_OUTPUT_STREAMF_SINGLE_SAMPLE_PER_BUFFER = 0x00000002,
    DMO_OUTPUT_STREAMF_FIXED_SAMPLE_SIZE        = 0x00000004,
    DMO_OUTPUT_STREAMF_DISCARDABLE              = 0x00000008,
    DMO_OUTPUT_STREAMF_OPTIONAL                 = 0x00000010
};

/* aa451606 "DMO_PROCESS_OUTPUT_FLAGS". */
enum _DMO_PROCESS_OUTPUT_FLAGS {
    DMO_PROCESS_OUTPUT_DISCARD_WHEN_NO_BUFFER = 0x00000001
};

/* aa451609 "DMO_REGISTER_FLAGS". */
enum DMO_REGISTER_FLAGS {
    DMO_REGISTERF_IS_KEYED = 0x00000001
};

/* aa451610 "DMO_SET_TYPE_FLAGS". */
enum _DMO_SET_TYPE_FLAGS {
    DMO_SET_TYPEF_TEST_ONLY = 0x00000001,
    DMO_SET_TYPEF_CLEAR     = 0x00000002
};

/* aa451612 "DMO_VIDEO_OUTPUT_STREAM_FLAGS". */
enum _DMO_VIDEO_OUTPUT_STREAM_FLAGS {
    DMO_VOSF_NEEDS_PREVIOUS_SAMPLE = 0x00000001
};

/* --- Error codes (aa451595 "DMO Error Codes": full value table). --- */

#define DMO_E_INVALIDSTREAMINDEX   0x80040201L
#define DMO_E_INVALIDTYPE          0x80040202L
#define DMO_E_TYPE_NOT_SET         0x80040203L
#define DMO_E_NOTACCEPTING         0x80040204L
#define DMO_E_TYPE_NOT_ACCEPTED    0x80040205L
#define DMO_E_NO_MORE_ITEMS        0x80040206L

/* --- DMO category GUIDs (aa451598 "DMO GUIDs"): names recorded;
 * the page prints NO GUID values -- held (zero-gap policy):
 *   DMOCATEGORY_AUDIO_DECODER      DMOCATEGORY_AUDIO_EFFECT
 *   DMOCATEGORY_AUDIO_ENCODER      DMOCATEGORY_VIDEO_DECODER
 *   DMOCATEGORY_VIDEO_EFFECT       DMOCATEGORY_VIDEO_ENCODER
 *   DMOCATEGORY_AUDIO_CAPTURE_EFFECT
 */

/* --- Functions (Msdmo.lib rows -> def/msdmo-doc.def). ---------------- */

/* aa451593 "DMOEnum". */
AKARI_CE_IMPORT HRESULT DMOEnum(REFGUID guidCategory, DWORD dwFlags,
                    DWORD cInTypes, const DMO_PARTIAL_MEDIATYPE *pInTypes,
                    DWORD cOutTypes, const DMO_PARTIAL_MEDIATYPE *pOutTypes,
                    IEnumDMO **ppEnum) AKARI_CE_NAME(DMOEnum);

/* aa451597 "DMOGetTypes": the print uses `unsigned long` (kept). */
AKARI_CE_IMPORT HRESULT DMOGetTypes(REFCLSID clsidDMO,
                    unsigned long ulInputTypesRequested,
                    unsigned long *pulInputTypesSupplied,
                    DMO_PARTIAL_MEDIATYPE *pInputTypes,
                    unsigned long ulOutputTypesRequested,
                    unsigned long *pulOutputTypesSupplied,
                    DMO_PARTIAL_MEDIATYPE *pOutputTypes) AKARI_CE_NAME(DMOGetTypes);

/* aa451596 "DMOGetName": the print's array parameter is
 * `WCHARszName[]` (glued; kept as the unsized array print). */
AKARI_CE_IMPORT HRESULT DMOGetName(REFCLSID clsidDMO,
                    WCHAR szName[]) AKARI_CE_NAME(DMOGetName);

/* aa451611 "DMOUnregister". */
AKARI_CE_IMPORT HRESULT DMOUnregister(REFCLSID clsidDMO,
                    REFGUID guidCategory) AKARI_CE_NAME(DMOUnregister);

/* aa452530 "DMOUnregisterFilter": the print carries a trailing
 * parameter comma ("REFCLSIDclsidAutoWrap,"); dropped for
 * compilation, print recorded. */
AKARI_CE_IMPORT HRESULT DMOUnregisterFilter(
                    REFCLSID clsidAutoWrap) AKARI_CE_NAME(DMOUnregisterFilter);

/* ms932077 "MoInitMediaType". */
AKARI_CE_IMPORT HRESULT MoInitMediaType(DMO_MEDIA_TYPE *pmt,
                    DWORD cbFormat) AKARI_CE_NAME(MoInitMediaType);

/* ms932068 "MoFreeMediaType". */
AKARI_CE_IMPORT HRESULT MoFreeMediaType(DMO_MEDIA_TYPE *pmt) AKARI_CE_NAME(MoFreeMediaType);

/* ms932064 "MoCopyMediaType". */
AKARI_CE_IMPORT HRESULT MoCopyMediaType(DMO_MEDIA_TYPE *pmtDest,
                    const DMO_MEDIA_TYPE *pmtSrc) AKARI_CE_NAME(MoCopyMediaType);

/* ms932065 "MoCreateMediaType". */
AKARI_CE_IMPORT HRESULT MoCreateMediaType(DMO_MEDIA_TYPE **ppmt,
                    DWORD cbFormat) AKARI_CE_NAME(MoCreateMediaType);

/* ms932066 "MoDeleteMediaType". */
AKARI_CE_IMPORT HRESULT MoDeleteMediaType(DMO_MEDIA_TYPE *pmt) AKARI_CE_NAME(MoDeleteMediaType);

/* ms932067 "MoDuplicateMediaType". */
AKARI_CE_IMPORT HRESULT MoDuplicateMediaType(DMO_MEDIA_TYPE **ppmtDest,
                    const DMO_MEDIA_TYPE *pmtSrc) AKARI_CE_NAME(MoDuplicateMediaType);

/* aa451608 "DMORegister": the page prints NO Requirements block (no
 * Header row, no Link Library row) -- declared for completeness,
 * excluded from def/msdmo-doc.def (no documented link library). */
AKARI_CE_IMPORT HRESULT DMORegister(LPCWSTR szName, REFCLSID clsidDMO,
                    REFGUID guidCategory, REFCLSID clsidAutoWrap,
                    DWORD dwFlags, DWORD cInTypes,
                    const DMO_PARTIAL_MEDIATYPE *pInTypes, DWORD cOutTypes,
                    const DMO_PARTIAL_MEDIATYPE *pOutTypes) AKARI_CE_NAME(DMORegister);

/* --- Interface method records (verbatim). ---------------------------- */

/* IDMOQualityControl: documented methods (3 pages; Dmo.h rows; Link Library
 * Dmoguid.lib -- GUID linkage, no export).  Signatures verbatim.
 *   aa451809 GetStatus: HRESULT GetStatus(DWORD* pdwFlags);
 *   aa451810 SetNow: HRESULT SetNow(REFERENCE_TIMErtNow);
 *   aa451811 SetStatus: HRESULT SetStatus(DWORDdwFlags);
 */
/* IDMOVideoOutputOptimizations: documented methods (4 pages; Dmo.h rows; Link Library
 * Dmoguid.lib -- GUID linkage, no export).  Signatures verbatim.
 *   aa451813 GetCurrentOperationMode: HRESULT GetCurrentOperationMode(ULONGulOutputStreamIndex,DWORD* pdwEnabledFeatures);
 *   aa451814 GetCurrentSampleRequirements: HRESULT GetCurrentSampleRequirements(ULONGulOutputStreamIndex,DWORD* pdwRequestedFeatures);
 *   aa451815 QueryOperationModePreferences: HRESULT QueryOperationModePreferences(ULONGulOutputStreamIndex,DWORD* pdwRequestedCapabilities);
 *   aa451816 SetOperationMode: HRESULT SetOperationMode(ULONGulOutputStreamIndex,DWORDdwEnabledFeatures);
 */
/* IEnumDMO: documented methods (4 pages; Dmo.h rows; Link Library
 * Dmoguid.lib -- GUID linkage, no export).  Signatures verbatim.
 *   ms910385 Clone: HRESULT Clone(IEnumDMO** ppEnum);
 *   ms910392 Next: HRESULT Next(DWORDcItemsToFetch,CLSID* pCLSID,WCHAR** Names,DWORD* pcItemsFetched);
 *   ms910398 Reset: HRESULT Reset(void);
 *   ms910405 Skip: HRESULT Skip(DWORDcItemsToSkip);
 */
/* IMediaBuffer: documented methods (3 pages; Dmo.h rows; Link Library
 * Dmoguid.lib -- GUID linkage, no export).  Signatures verbatim.
 *   aa452255 GetBufferAndLength: HRESULT GetBufferAndLength(BYTE** ppBuffer,DWORD* pcbLength);
 *   aa452256 GetMaxLength: HRESULT GetMaxLength(DWORD* pcbMaxLength);
 *   aa452257 SetLength: HRESULT SetLength(DWORDcbLength);
 */
/* IMediaObject: documented methods (21 pages; Dmo.h rows; Link Library
 * Dmoguid.lib -- GUID linkage, no export).  Signatures verbatim.
 *   ms931391 AllocateStreamingResources: HRESULT AllocateStreamingResources(void);
 *   ms931392 Discontinuity: HRESULT Discontinuity(DWORDdwInputStreamIndex);
 *   ms931393 Flush: HRESULT Flush(void);
 *   ms931394 FreeStreamingResources: HRESULT FreeStreamingResources(void);
 *   ms931395 GetInputCurrentType: HRESULT GetInputCurrentType(DWORDdwInputStreamIndex,DMO_MEDIA_TYPE* pmt);
 *   ms931396 GetInputMaxLatency: HRESULT GetInputMaxLatency(DWORDdwInputStreamIndex,REFERENCE_TIME* prtMaxLatency);
 *   ms931397 GetInputSizeInfo: HRESULT GetInputSizeInfo(DWORDdwInputStreamIndex,DWORD* pcbSize,DWORD* pcbMaxLookahead,DWORD* pcbAlignment);
 *   ms931398 GetInputStatus: HRESULT GetInputStatus(DWORDdwInputStreamIndex,DWORD* dwFlags);
 *   ms931399 GetInputStreamInfo: HRESULT GetInputStreamInfo(DWORDdwInputStreamIndex,DWORD* pdwFlags);
 *   ms931400 GetInputType: HRESULT GetInputType(DWORDdwInputStreamIndex,DWORDdwTypeIndex,DMO_MEDIA_TYPE* pmt);
 *   ms931401 GetOutputCurrentType: HRESULT GetOutputCurrentType(DWORDdwOutputStreamIndex,DMO_MEDIA_TYPE* pmt);
 *   ms931402 GetOutputSizeInfo: HRESULT GetOutputSizeInfo(DWORDdwOutputStreamIndex,DWORD* pcbSize,DWORD* pcbAlignment);
 *   ms931403 GetOutputStreamInfo: HRESULT GetOutputStreamInfo(DWORDdwOutputStreamIndex,DWORD* pdwFlags);
 *   ms931404 GetOutputType: HRESULT GetOutputType(DWORDdwOutputStreamIndex,DWORDdwTypeIndex,DMO_MEDIA_TYPE* pmt);
 *   ms931405 GetStreamCount: HRESULT GetStreamCount(DWORD* pcInputStreams,DWORD* pcOutputStreams);
 *   ms931416 Lock: HRESULT Lock(LONGbLock);
 *   ms931418 ProcessInput: HRESULT ProcessInput(DWORDdwInputStreamIndex,IMediaBuffer* pBuffer,DWORDdwFlags,REFERENCE_TIMErtTimestamp,REFERENCE_TIMErtTimelength);
 *   ms931419 ProcessOutput: HRESULT ProcessOutput(DWORDdwFlags,DWORDcOutputBufferCount,DMO_OUTPUT_DATA_BUFFER* pOutputBuffers,DWORD* pdwStatus);
 *   ms931420 SetInputMaxLatency: HRESULT SetInputMaxLatency(DWORDdwInputStreamIndex,REFERENCE_TIMErtMaxLatency);
 *   ms931421 SetInputType: HRESULT SetInputType(DWORDdwInputStreamIndex,const DMO_MEDIA_TYPE* pmt,DWORDdwFlags);
 *   ms931422 SetOutputType: HRESULT SetOutputType(DWORDdwOutputStreamIndex,const DMO_MEDIA_TYPE* pmt,DWORDdwFlags);
 */
/* IMediaObjectInPlace: documented methods (3 pages; Dmo.h rows; Link Library
 * Dmoguid.lib -- GUID linkage, no export).  Signatures verbatim.
 *   ms931413 Clone: HRESULT Clone(IMediaObjectInPlace** ppMediaObject);
 *   ms931414 GetLatency: HRESULT GetLatency(REFERENCE_TIME* pLatencyTime);
 *   ms931415 Process: HRESULT Process(ULONGulSize,BYTE* pDataREFERENCE_TIME refTimeStart,DWORDdwFlags);
 */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_DMO_H */
