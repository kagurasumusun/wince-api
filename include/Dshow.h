/*
 * Dshow.h -- DirectShow core data surface for the Akari API.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Declarations below are annotated with the
 * official Microsoft Windows CE 5.0 documentation pages they are
 * taken from ((v=msdn.10) Learn-archive IDs), harvested from the
 * *Graphics and Multimedia Technologies -> Media -> DirectShow ->
 * DirectShow Reference* sub-books DirectShow Enumerations (15
 * leaves), Functions (68), Macros (72) and Structures (28) -- see
 * tools/manifests/dshow-{enum,func,macro,struct}.manifest and
 * docs/inventory.md M70b.
 *
 * Scope of this header (the documented Dshow.h data surface):
 *  - the 27 structure pages whose Requirements row prints
 *    Header: Dshow.h (plus AMVPDATAINFO's undeclared AMVPDIMINFO,
 *    see below), and
 *  - the enumerations those structures use; the enumeration pages
 *    print an EMPTY Header row (the Requirements block says
 *    "DirectShow applications and DirectShow filters have different
 *    include file and link library requirements; see Setting Up the
 *    Build Environment" and leaves Header: blank), recorded per item.
 *    The structures' own Dshow.h rows are the carrier grounding.
 *
 * Deliberately deferred (recorded gaps, docs/inventory.md M70b):
 *  - the 53 helper/debug/utility function pages and 60 macro pages
 *    of the DirectShow base-class library (strmbase) -- they carry
 *    empty Header rows and no Link Library row, so no per-page
 *    import surface is documentable (the def-directory policy);
 *    they land
 *    with the DirectShow Classes milestone.
 *  - the 28 EC_* event-notification-code pages (names recorded
 *    below; no page prints a numeric value -- zero-gap policy).
 *
 * Version notes: OS Versions rows print "Windows CE 2.12 and later.
 * Version 2.12 requires DXPAK 1.0 or later." for the core surface;
 * the STRMBUF_* / STREAMBUFFER_EC / dvdmedia.h items are Windows
 * CE 5.0 Networked Media Device Feature Pack era.  Rows are quoted
 * per item.
 *
 * Repairs (archive artifacts, spacing only): VIDEOINFOHEADER's
 * `RECTrcTarget`, AMOVIESETUP_FILTER's missing trailing semicolon,
 * and the RPC marker `__RPC_FAR` (== no-op) on IUnknown/IFilterGraph
 * pointer members are restored/normalized with the print recorded.
 */

#ifndef AKARI_DSHOW_H
#define AKARI_DSHOW_H

#include "Windef.h"    /* BOOL, DWORD, LONG, WORD, UINT, ULONG, WCHAR,
                          LPWSTR, RECT, SIZE, HANDLE */
#include "Winnt.h"     /* GUID, CLSID, LONGLONG, BYTE */
#include "Wingdi.h"    /* COLORREF, RGBQUAD, BITMAPINFOHEADER, DIBSECTION,
                          HBITMAP */
#include "Objbase.h"   /* IUnknown (opaque forward) */

#ifdef __cplusplus
extern "C" {
#endif

/* --- Carrier types. -------------------------------------------------
 *
 * REFERENCE_TIME: no CE page prints the typedef (only its use in
 * the structure prints below).  Closure `LONGLONG`: the same pages
 * describe the members as 100-nanosecond reference times and the
 * sibling TIMECODE_SAMPLE page (aa452392) prints the tick member as
 * LONGLONG; LONGLONG is winnt.h's 64-bit carrier.  Replace on an
 * official print. */
typedef LONGLONG REFERENCE_TIME;

/* Opaque interface forwards used by pointer in the structure prints
 * (rtccore.h M69 pattern; the interface overview pages live in the
 * DirectShow Interfaces book, still pending -- no method records
 * are invented here):
 *   PIN_INFO (ms932256):    IBaseFilter* pFilter
 *   FILTER_INFO (aa451713): IFilterGraph __RPC_FAR* pGraph
 */
typedef struct IBaseFilter IBaseFilter;
typedef struct IFilterGraph IFilterGraph;

/* --- Enumerations (verbatim prints, values as printed). -------------- */

/* aa451714 "FILTER_STATE": CE 2.12+ DXPAK 1.0+ (Dshow.h row context).
 * The print chains +1 (kept verbatim). */
typedef enum _FilterState {
    State_Stopped = 0,
    State_Paused = State_Stopped + 1,
    State_Running = State_Paused + 1
} FILTER_STATE;

/* ms932255 "PIN_DIRECTION". */
typedef enum _PinDirection {
    PINDIR_INPUT,
    PINDIR_OUTPUT
} PIN_DIRECTION;

/* ms932273 "QualityMessageType". */
typedef enum {
    Famine,
    Flood
} QualityMessageType;

/* ms925346 "AM_STREAM_INFO_FLAGS". */
typedef enum {
    AM_STREAM_INFO_START_DEFINED    = 0x00000001,
    AM_STREAM_INFO_STOP_DEFINED     = 0x00000002,
    AM_STREAM_INFO_DISCARDING       = 0x00000004,
    AM_STREAM_INFO_STOP_SEND_EXTRA  = 0x00000010
} AM_STREAM_INFO_FLAGS;

/* ms925348 "AMVP_MODE". */
typedef enum _AMVP_MODE {
    AMVP_MODE_WEAVE,
    AMVP_MODE_BOBINTERLEAVED,
    AMVP_MODE_BOBNONINTERLEAVED,
    AMVP_MODE_SKIPEVEN,
    AMVP_MODE_SKIPODD
} AMVP_MODE;

/* ms925439 "AnalogVideoStandard": trailing comma in the print is an
 * archive artifact (dropped); values verbatim. */
typedef enum {
    AnalogVideo_None     = 0x00000000,
    AnalogVideo_NTSC_M   = 0x00000001,
    AnalogVideo_NTSC_M_J = 0x00000002,
    AnalogVideo_NTSC_433 = 0x00000004,
    AnalogVideo_PAL_B    = 0x00000010,
    AnalogVideo_PAL_D    = 0x00000020,
    AnalogVideo_PAL_H    = 0x00000080,
    AnalogVideo_PAL_I    = 0x00000100,
    AnalogVideo_PAL_M    = 0x00000200,
    AnalogVideo_PAL_N    = 0x00000400,
    AnalogVideo_PAL_60   = 0x00000800,
    AnalogVideo_SECAM_B  = 0x00001000,
    AnalogVideo_SECAM_D  = 0x00002000,
    AnalogVideo_SECAM_G  = 0x00004000,
    AnalogVideo_SECAM_H  = 0x00008000,
    AnalogVideo_SECAM_K  = 0x00010000,
    AnalogVideo_SECAM_K1 = 0x00020000,
    AnalogVideo_SECAM_L  = 0x00040000,
    AnalogVideo_SECAM_L1 = 0x00080000
} AnalogVideoStandard;

/* ms932233 "MPEG2Level" (tag-form enum print). */
enum MPEG2Level {
    MPEG2Level_Low = 1,
    MPEG2Level_Main,
    MPEG2Level_High1440,
    MPEG2Level_High
};

/* ms932234 "MPEG2Profile" (tag-form enum print). */
enum MPEG2Profile {
    MPEG2Profile_Simple = 1,
    MPEG2Profile_Main,
    MPEG2Profile_SNRScalable,
    MPEG2Profile_SpatiallyScalable,
    MPEG2Profile_High
};

/* ms932034 "Merit": the print is `typedef enum { ... };` with NO
 * typedef name -- invalid C (useless typedef); compiled as an
 * anonymous enum so the members are the surface, print recorded. */
enum {
    MERIT_PREFERRED    = 0x800000,
    MERIT_NORMAL       = 0x600000,
    MERIT_UNLIKELY     = 0x400000,
    MERIT_DO_NOT_USE   = 0x200000,
    MERIT_SW_COMPRESSOR = 0x100000,
    MERIT_HW_COMPRESSOR = 0x100050
};

/* ms925344 "AM_SAMPLE_PROPERTY_FLAGS": bare `enum tag...` print with
 * the AM_STREAM_* pseudo-members included verbatim. */
enum tagAM_SAMPLE_PROPERTY_FLAGS {
    AM_SAMPLE_SPLICEPOINT      = 0x01,
    AM_SAMPLE_PREROLL          = 0x02,
    AM_SAMPLE_DATADISCONTINUITY = 0x04,
    AM_SAMPLE_TYPECHANGED      = 0x08,
    AM_SAMPLE_TIMEVALID        = 0x10,
    AM_SAMPLE_TIMEDISCONTINUITY = 0x40,
    AM_SAMPLE_FLUSH_ON_PAUSE   = 0x80,
    AM_SAMPLE_STOPVALID        = 0x100,
    AM_SAMPLE_ENDOFSTREAM      = 0x200,
    AM_STREAM_MEDIA            = 0,
    AM_STREAM_CONTROL          = 1
};

/* aa452378 "StreamControlState" (tag-form enum print). */
enum StreamControlState {
    STREAM_FLOWING,
    STREAM_DISCARDING
};

/* aa452561 "STRMBUF_CAPTURE_MODE": Stream Buffer Engine, Windows CE
 * 5.0 Networked Media Device Feature Pack era (page Requirements
 * row prints the Pocket PC/Smartphone split, no header row). */
typedef enum CaptureMode {
    STRMBUF_TEMPORARY_RECORDING = 0,
    STRMBUF_PERMANENT_RECORDING
} STRMBUF_CAPTURE_MODE;

/* aa452562 "STRMBUF_PLAYBACK_TUNE_POLICY" (same era; self-named tag
 * form). */
typedef enum STRMBUF_PLAYBACK_TUNE_POLICY {
    STRMBUF_PLAYBACK_TUNE_FLUSH_AND_GO_TO_LIVE,
    STRMBUF_PLAYBACK_TUNE_IGNORED
} STRMBUF_PLAYBACK_TUNE_POLICY;

/* aa452499 "STREAMBUFFER_EC": print is a nameless `typedef enum`
 * (repaired to an anonymous enum as with Merit above); chains +1
 * from 0x326 kept verbatim; the archive's mid-line breaks are
 * normalized. */
enum {
    STREAMBUFFER_EC_TIMEHOLE             = 0x326,
    STREAMBUFFER_EC_STALE_DATA_READ      = STREAMBUFFER_EC_TIMEHOLE + 1,
    STREAMBUFFER_EC_STALE_FILE_DELETED   = STREAMBUFFER_EC_STALE_DATA_READ + 1,
    STREAMBUFFER_EC_CONTENT_BECOMING_STALE = STREAMBUFFER_EC_STALE_FILE_DELETED + 1,
    STREAMBUFFER_EC_WRITE_FAILURE        = STREAMBUFFER_EC_CONTENT_BECOMING_STALE + 1,
    STREAMBUFFER_EC_READ_FAILURE         = STREAMBUFFER_EC_WRITE_FAILURE + 1,
    STREAMBUFFER_EC_RATE_CHANGED         = STREAMBUFFER_EC_READ_FAILURE + 1
};

/* --- Structures (verbatim prints, Dshow.h rows). --------------------- */

/* ms925330 "ALLOCATOR_PROPERTIES": member prints use `long` (kept). */
typedef struct _AllocatorProperties {
    long cBuffers;
    long cbBuffer;
    long cbAlign;
    long cbPrefix;
} ALLOCATOR_PROPERTIES;

/* ms925337 "AM_MEDIA_TYPE": `__RPC_FAR` (RPC no-op marker) on
 * pbFormat repaired to a plain pointer with the print recorded; the
 * print's IDL comment is kept. */
typedef struct _MediaType {
    GUID    majortype;
    GUID    subtype;
    BOOL    bFixedSizeSamples;
    BOOL    bTemporalCompression;
    ULONG   lSampleSize;
    GUID    formattype;
    IUnknown *pUnk;
    ULONG   cbFormat;
    /* [size_is] */
    BYTE    *pbFormat;
} AM_MEDIA_TYPE;

/* ms925343 "AM_SAMPLE2_PROPERTIES". */
typedef struct tagAM_SAMPLE2_PROPERTIES {
    DWORD          cbData;
    DWORD          dwTypeSpecificFlags;
    DWORD          dwSampleFlags;
    LONG           lActual;
    REFERENCE_TIME tStart;
    REFERENCE_TIME tStop;
    DWORD          dwStreamId;
    AM_MEDIA_TYPE  *pMediaType;
    BYTE           *pbBuffer;
    LONG           cbBuffer;
} AM_SAMPLE2_PROPERTIES;

/* ms925345 "AM_STREAM_INFO": anonymous struct print (no tag). */
typedef struct {
    REFERENCE_TIME tStart;
    REFERENCE_TIME tStop;
    DWORD dwStartCookie;
    DWORD dwStopCookie;
    DWORD dwFlags;
} AM_STREAM_INFO;

/* ms925341 "AMOVIESETUP_MEDIATYPE" (+ LP alias used by the
 * AMOVIESETUP_PIN print). */
typedef struct _AMOVIESETUP_MEDIATYPE {
    const CLSID *clsMajorType;
    const CLSID *clsMinorType;
} AMOVIESETUP_MEDIATYPE;
typedef AMOVIESETUP_MEDIATYPE *LPAMOVIESETUP_MEDIATYPE;

/* ms925342 "AMOVIESETUP_PIN" (+ LP alias used by the
 * AMOVIESETUP_FILTER print). */
typedef struct _AMOVIESETUP_PIN {
    LPWSTR     strName;
    BOOL       bRendered;
    BOOL       bOutput;
    BOOL       bZero;
    BOOL       bMany;
    const CLSID *clsConnectsToFilter;
    LPWSTR     strConnectsToPin;
    UINT       nMediaTypes;
    LPAMOVIESETUP_MEDIATYPE lpMediaType;
} AMOVIESETUP_PIN;
typedef AMOVIESETUP_PIN *LPAMOVIESETUP_PIN;

/* ms925340 "AMOVIESETUP_FILTER": the print's trailing semicolon is
 * eaten by the archive (restored); body verbatim. */
typedef struct _AMOVIESETUP_FILTER {
    const CLSID *clsID;
    LPWSTR      strName;
    DWORD       dwMerit;
    UINT        nPins;
    LPAMOVIESETUP_PIN lpPin;
} AMOVIESETUP_FILTER;

/* ms925349 "AMVPSIZE" (LP alias printed on the page). */
typedef struct _AMVPSIZE {
    DWORD dwWidth;
    DWORD dwHeight;
} AMVPSIZE, *LPAMVPSIZE;

/* ms925347 "AMVPDATAINFO": held INCOMPLETE -- the print embeds
 * `AMVPDIMINFO amvpDimInfo` by value, but no AMVPDIMINFO page
 * exists anywhere in the CE 5.0 archive TOC (checked), so its
 * layout is unpublished.  Verbatim print:
 *   typedef struct _AMVPDATAINFO{DWORD dwSize;
 *     DWORD dwMicrosecondsPerField; AMVPDIMINFO amvpDimInfo;
 *     DWORD dwPictAspectRatioX;DWORD dwPictAspectRatioY;
 *     BOOL bEnableDoubleClock;BOOL bEnableVACT;
 *     BOOL bDataIsInterlaced;LONG lHalfLinesOdd;
 *     BOOL bFieldPolarityInverted;DWORD dwNumLinesInVREF;
 *     LONG lHalfLinesEven;DWORD dwReserved1;
 *   } AMVPDATAINFO, *LPAMVPDATAINFO;
 */
typedef struct AMVPDIMINFO AMVPDIMINFO;
typedef struct _AMVPDATAINFO AMVPDATAINFO;
typedef AMVPDATAINFO *LPAMVPDATAINFO;

/* ms925720 "AUDIO_STREAM_CONFIG_CAPS". */
typedef struct _AUDIO_STREAM_CONFIG_CAPS {
    GUID  guid;
    ULONG MinimumChannels;
    ULONG MaximumChannels;
    ULONG ChannelsGranularity;
    ULONG MinimumBitsPerSample;
    ULONG MaximumBitsPerSample;
    ULONG BitsPerSampleGranularity;
    ULONG MinimumSampleFrequency;
    ULONG MaximumSampleFrequency;
    ULONG SampleFrequencyGranularity;
} AUDIO_STREAM_CONFIG_CAPS;

/* ms926774 "COLORKEY". */
typedef struct tagCOLORKEY {
    DWORD    KeyType;
    DWORD    PaletteIndex;
    COLORREF LowColorValue;
    COLORREF HighColorValue;
} COLORKEY;

/* aa451578 "DIBDATA". */
typedef struct tagDIBDATA {
    LONG      PaletteVersion;
    DIBSECTION DibSection;
    HBITMAP   hBitmap;
    HANDLE    hMapping;
    BYTE      *pBase;
} DIBDATA;

/* aa451713 "FILTER_INFO": `IFilterGraph __RPC_FAR* pGraph` repaired
 * to a plain pointer (print recorded in the banner). */
typedef struct _FilterInfo {
    WCHAR         achName[128];
    IFilterGraph  *pGraph;
} FILTER_INFO;

/* aa452412 "VIDEOINFOHEADER": the print's `RECTrcTarget` space-glue
 * is repaired; body verbatim. */
typedef struct tagVIDEOINFOHEADER {
    RECT           rcSource;
    RECT           rcTarget;
    DWORD          dwBitRate;
    DWORD          dwBitErrorRate;
    REFERENCE_TIME AvgTimePerFrame;
    BITMAPINFOHEADER bmiHeader;
} VIDEOINFOHEADER;

/* aa452413 "VIDEOINFOHEADER2". */
typedef struct tagVIDEOINFOHEADER2 {
    RECT           rcSource;
    RECT           rcTarget;
    DWORD          dwBitRate;
    DWORD          dwBitErrorRate;
    REFERENCE_TIME AvgTimePerFrame;
    DWORD          dwInterlaceFlags;
    DWORD          dwCopyProtectFlags;
    DWORD          dwPictAspectRatioX;
    DWORD          dwPictAspectRatioY;
    DWORD          dwReserved1;
    DWORD          dwReserved2;
    BITMAPINFOHEADER bmiHeader;
} VIDEOINFOHEADER2;

/* ms932232 "MPEG1VIDEOINFO". */
typedef struct tagMPEG1VIDEOINFO {
    VIDEOINFOHEADER hdr;
    DWORD dwStartTimeCode;
    DWORD cbSequenceHeader;
    BYTE  bSequenceHeader[1];
} MPEG1VIDEOINFO;

/* ms932235 "MPEG2VIDEOINFO". */
typedef struct tagMPEG2VIDEOINFO {
    VIDEOINFOHEADER2 hdr;
    DWORD dwStartTimeCode;
    DWORD cbSequenceHeader;
    DWORD dwProfile;
    DWORD dwLevel;
    DWORD dwFlags;
    DWORD dwSequenceHeader[1];
} MPEG2VIDEOINFO;

/* ms932256 "PIN_INFO". */
typedef struct _PinInfo {
    IBaseFilter  *pFilter;
    PIN_DIRECTION dir;
    WCHAR        achName[128];
} PIN_INFO;

/* ms932266 "POSITION": verbatim (self-referential placeholder form
 * printed by the page). */
struct __POSITION {
    int unused;
};

/* ms932272 "Quality": anonymous struct print, typedef name Quality. */
typedef struct {
    QualityMessageType Type;
    long Proportion;
    REFERENCE_TIME Late;
    REFERENCE_TIME TimeStamp;
} Quality;

/* ms932283 "REGFILTER". */
typedef struct {
    CLSID Clsid;
    LPWSTR Name;
} REGFILTER;

/* ms932285 "REGPINTYPES". */
typedef struct {
    const CLSID *clsMajorType;
    const CLSID *clsMinorType;
} REGPINTYPES;

/* ms932284 "REGFILTERPINS". */
typedef struct {
    LPWSTR strName;
    BOOL   bRendered;
    BOOL   bOutput;
    BOOL   bZero;
    BOOL   bMany;
    const CLSID *clsConnectsToFilter;
    const WCHAR *strConnectsToPin;
    UINT   nMediaTypes;
    const REGPINTYPES *lpMediaType;
} REGFILTERPINS;

/* aa452390 "TIMECODE": dwFrames is printed as WORD (kept verbatim;
 * the print governs). */
typedef struct tagTIMECODE {
    WORD wFrameRate;
    WORD wFrameFract;
    WORD dwFrames;
} TIMECODE;

/* aa452392 "TIMECODE_SAMPLE". */
typedef struct tagTIMECODE_SAMPLE {
    LONGLONG  qwTick;
    TIMECODE  timecode;
    DWORD     dwUser;
    DWORD     dwFlags;
} TIMECODE_SAMPLE;

/* aa452415 "VIDEO_STREAM_CONFIG_CAPS" (SIZE from windef.h; int
 * members verbatim). */
typedef struct _VIDEO_STREAM_CONFIG_CAPS {
    GUID      guid;
    ULONG     VideoStandard;
    SIZE      InputSize;
    SIZE      MinCroppingSize;
    SIZE      MaxCroppingSize;
    int       CropGranularityX;
    int       CropGranularityY;
    int       CropAlignX;
    int       CropAlignY;
    SIZE      MinOutputSize;
    SIZE      MaxOutputSize;
    int       OutputGranularityX;
    int       OutputGranularityY;
    int       StretchTapsX;
    int       StretchTapsY;
    int       ShrinkTapsX;
    int       ShrinkTapsY;
    LONGLONG  MinFrameInterval;
    LONGLONG  MaxFrameInterval;
    LONG      MinBitsPerSecond;
    LONG      MaxBitsPerSecond;
} VIDEO_STREAM_CONFIG_CAPS;

/* aa452396 "TRUECOLORINFO" / aa452411 "VIDEOINFO": held INCOMPLETE --
 * their prints are sized by iMASK_COLORS / iPALETTE_COLORS, and no
 * CE page publishes those values (the names appear only inside these
 * two prints in the whole archive).  Verbatim prints:
 *   typedef struct tag_TRUECOLORINFO {
 *     DWORD dwBitMasks[iMASK_COLORS];
 *     RGBQUAD bmiColors[iPALETTE_COLORS];
 *   } TRUECOLORINFO;
 *   typedef struct tagVIDEOINFO {
 *     RECT rcSource,RECT rcTarget,DWORD dwBitRate,
 *     DWORD dwBitErrorRate,REFERENCE_TIME AvgTimePerFrame;
 *     BITMAPINFOHEADER bmiHeader;
 *     union { RGBQUAD bmiColors[iPALETTE_COLORS];
 *       DWORD dwBitMasks[iMASK_COLORS];
 *       TRUECOLORINFO TrueColorInfo; };
 *   } VIDEOINFO;
 */
typedef struct tag_TRUECOLORINFO TRUECOLORINFO;
typedef struct tagVIDEOINFO VIDEOINFO;

/* --- Event notification codes (names recorded; values unpublished). --
 *
 * The 28 event-code pages document DirectShow's system-defined
 * event notification codes ("listed in the Evcode.h header file",
 * aa451706) but no page prints a numeric value for any of them
 * (zero-gap policy; nothing is invented):
 *   aa451631 EC_ACTIVATE            aa451656 EC_SHUTTING_DOWN
 *   aa451633 EC_BUFFERING_DATA      aa451657 EC_STARVATION
 *   aa451634 EC_CLOCK_CHANGED       aa451659 EC_STREAM_CONTROL_STARTED
 *   aa451635 EC_COMPLETE            aa451660 EC_STREAM_CONTROL_STOPPED
 *   aa451670 EC_DRM_LEVEL           aa451661 EC_STREAM_ERROR_STILLPLAYING
 *   aa451638 EC_END_OF_SEGMENT      aa451662 EC_STREAM_ERROR_STOPPED
 *   aa451642 EC_ERROR_STILLPLAYING  aa451663 EC_TIME
 *   aa451640 EC_ERRORABORT          aa451664 EC_USERABORT
 *   aa451644 EC_FULLSCREEN_LOST     aa451668 EC_VIDEO_SIZE_CHANGED
 *   aa451647 EC_NEED_RESTART        aa451667 EC_VIDEO_SIZE_AR_CHANGED
 *   aa451648 EC_NOTIFY_WINDOW       aa451669 EC_WINDOW_DESTROYED
 *   aa451649 EC_OLE_EVENT
 *   aa451650 EC_OPENING_FILE        (STREAMBUFFER_EC_* carry printed
 *   aa451651 EC_PALETTE_CHANGED      values and are compiled above,
 *   aa451653 EC_QUALITY_CHANGE       aa452499.)
 *   aa451654 EC_REPAINT
 *   aa451655 EC_SEGMENT_STARTED
 */


/* --- DirectShow interfaces (DirectShow Interfaces book, 476
 *      leaves; M71b). -------------------------------------------------------
 *
 * Every interface page of the book (63 overview pages, 62 distinct
 * names after the IAMTVTuner TOC duplicate; 413 ::-qualified method
 * pages + ms911601 "CheckCapabilities" whose TOC title lost the
 * IMediaSeeking:: qualifier) is carried per the M44/rtccore policy:
 * an opaque forward declaration per interface and verbatim
 * method-signature records below -- vtable layouts are not
 * published, so no C++-style interface struct is invented.
 *
 * Requirements rows on EVERY page defer include/library choice to
 * "Setting Up the Build Environment" -- no Header row, no Link
 * Library row -- so no import surface is documentable (the def
 * surface is unchanged).  OS Versions rows: "Windows CE 2.12 and
 * later. Version 2.12 requires DXPAK 1.0 or later." unless quoted
 * per interface below.
 *
 * Archive artifacts recorded: the method-page titles spell
 * IVideoWindow as "IVideoWIndow" (capital I; kept in the records);
 * ms908797 prints the return type of IAMPlayListItem::GetSourceURL
 * as RESULT (the page's own typo for HRESULT -- repaired, print
 * recorded); IDL annotations inside prints are neutralized to
 * bracket form to keep the records comment-safe; space-glued
 * tokens (HRESULTAlloc, DWORDdwSourceIndex, the page's
 * ppUnkInnner spelling) are preserved verbatim.
 */

/* Opaque interface forwards (62; IBaseFilter and IFilterGraph are
 * already forwarded in the M70b section above and not repeated). */
typedef struct IAMDevMemoryAllocator IAMDevMemoryAllocator;
typedef struct IAMDevMemoryControl IAMDevMemoryControl;
typedef struct IAMDroppedFrames IAMDroppedFrames;
typedef struct IAMMediaContent IAMMediaContent;
typedef struct IAMMediaContentEx IAMMediaContentEx;
typedef struct IAMPlayList IAMPlayList;
typedef struct IAMPlayListItem IAMPlayListItem;
typedef struct IAMStreamConfig IAMStreamConfig;
typedef struct IAMStreamControl IAMStreamControl;
typedef struct IAMStreamSelect IAMStreamSelect;
typedef struct IAMTVTuner IAMTVTuner;
typedef struct IAMTuner IAMTuner;
typedef struct IAMovieSetup IAMovieSetup;
typedef struct IAsyncReader IAsyncReader;
typedef struct IBasicAudio IBasicAudio;
typedef struct IBasicVideo IBasicVideo;
typedef struct IDMOWrapperFilter IDMOWrapperFilter;
typedef struct IDVREngineHelpers IDVREngineHelpers;
typedef struct IDirectDrawVideo IDirectDrawVideo;
typedef struct IDistributorNotify IDistributorNotify;
typedef struct IEnumFilters IEnumFilters;
typedef struct IEnumMediaTypes IEnumMediaTypes;
typedef struct IEnumPins IEnumPins;
typedef struct IEnumRegFilters IEnumRegFilters;
typedef struct IFileSourceFilter IFileSourceFilter;
typedef struct IFilterGraph2 IFilterGraph2;
typedef struct IFilterMapper IFilterMapper;
typedef struct IGraphBuilder IGraphBuilder;
typedef struct IGraphVersion IGraphVersion;
typedef struct IKsPropertySet IKsPropertySet;
typedef struct IMediaControl IMediaControl;
typedef struct IMediaEvent IMediaEvent;
typedef struct IMediaEventEx IMediaEventEx;
typedef struct IMediaEventSink IMediaEventSink;
typedef struct IMediaFilter IMediaFilter;
typedef struct IMediaPosition IMediaPosition;
typedef struct IMediaSample IMediaSample;
typedef struct IMediaSample2 IMediaSample2;
typedef struct IMediaSeeking IMediaSeeking;
typedef struct IMediaStream IMediaStream;
typedef struct IMemAllocator IMemAllocator;
typedef struct IMemInputPin IMemInputPin;
typedef struct IMultiMediaStream IMultiMediaStream;
typedef struct INonDelegatingUnknown INonDelegatingUnknown;
typedef struct IOverlay IOverlay;
typedef struct IOverlayNotify IOverlayNotify;
typedef struct IPin IPin;
typedef struct IQualProp IQualProp;
typedef struct IQualityControl IQualityControl;
typedef struct IReferenceClock IReferenceClock;
typedef struct ISeekingPassThru ISeekingPassThru;
typedef struct IStreamBufferCapture IStreamBufferCapture;
typedef struct IStreamBufferPlayback IStreamBufferPlayback;
typedef struct IStreamSample IStreamSample;
typedef struct IVPBaseConfig IVPBaseConfig;
typedef struct IVPBaseNotify IVPBaseNotify;
typedef struct IVPConfig IVPConfig;
typedef struct IVPNotify IVPNotify;
typedef struct IVideoWindow IVideoWindow;

/* IAMDevMemoryAllocator: documented methods (5 pages).  Signatures recorded
 * verbatim.
 *   aa451745 Alloc: HRESULTAlloc(BYTE** ppBuffer,DWORD* pdwcbBuffer);
 *   aa451746 CheckMemory: HRESULT CheckMemory(const BYTE* pBuffer);
 *   aa451747 Free: HRESULT Free(BYTE* pBuffer);
 *   aa451748 GetDevMemoryObject: HRESULT GetDevMemoryObject(IUnknown** ppUnkInnner,IUnknown* pUnkOuter);
 *   aa451749 GetInfo: HRESULTGetInfo(DWORD* pdwcbTotalFree,DWORD* pdwcbLargestFree,DWORD* pdwcbTotalMemory,DWORD* pdwcbMinimumChunk);
 */

/* IAMDevMemoryControl: documented methods (3 pages).  Signatures recorded
 * verbatim.
 *   aa451751 GetDevId: HRESULT GetDevId(DWORD* pdwDevId);
 *   aa451753 QueryWriteSync: HRESULT QueryWriteSync( );
 *   aa451754 WriteSync: HRESULT WriteSync( );
 */

/* IAMDroppedFrames: documented methods (4 pages).  Signatures recorded  OS row: Windows CE 5.0 and later.
 * verbatim.
 *   aa452534 GetAverageFrameSize: HRESULT GetAverageFrameSize( long* plAverageSize);
 *   aa452535 GetDroppedInfo: HRESULT GetDroppedInfo( long lSize, long* plArray, long* plNumCopied);
 *   aa452536 GetNumDropped: HRESULT GetNumDropped( long* plDropped);
 *   aa452537 GetNumNotDropped: HRESULT GetNumNotDropped( long* plNotDropped);
 */

/* IAMMediaContent: documented methods (13 pages).  Signatures recorded
 * verbatim.
 *   aa451759 get_AuthorName: HRESULT get_AuthorName(BSTR* pbstrAuthorName);
 *   aa451760 get_BaseURL: HRESULT get_BaseURL(BSTR* pbstrBaseURL);
 *   aa451761 get_Copyright: HRESULT get_Copyright(BSTR* pbstrCopyright);
 *   aa451762 get_Description: HRESULT get_Description(BSTR* pbstrDescription);
 *   aa451763 get_LogoIconURL: HRESULT get_LogoIconURL(BSTR* pbstrLogoURL);
 *   aa451764 get_LogoURL: HRESULT get_LogoURL(BSTR* pbstrLogoURL);
 *   aa451765 get_MoreInfoBannerImage: HRESULT get_MoreInfoBannerImage(BSTR* pbstrMoreInfoBannerImage);
 *   aa451766 get_MoreInfoBannerURL: HRESULT get_MoreInfoBannerURL(BSTR* pbstrMoreInfoBannerURL);
 *   aa451767 get_MoreInfoText: HRESULT get_MoreInfoText(BSTR* pbstrMoreInfoText);
 *   ms908698 get_MoreInfoURL: HRESULT get_MoreInfoURL(BSTR* pbstrMoreInfoURL);
 *   ms908703 get_Rating: HRESULT get_Rating(BSTR* pbstrRating);
 *   ms908713 get_Title: HRESULT get_Title(BSTR* pbstrTitle);
 *   ms908716 get_WatermarkURL: HRESULT get_WatermarkURL(BSTR* pbstrWatermarkURL);
 */

/* IAMMediaContentEx: documented methods (3 pages).  Signatures recorded
 * verbatim.
 *   aa451756 MediaParameter: HRESULT MediaParameter(longEntryNum,BSTRbstrName,BSTR* pbstrValue);
 *   aa451757 MediaParameterName: HRESULT MediaParameterName(longEntryNum,longIndex,BSTR* pbstrName);
 *   aa451758 PlaylistCount: HRESULT PlaylistCount(long* pNumberEntries);
 */

/* IAMPlayList: documented methods (5 pages).  Signatures recorded
 * verbatim.
 *   ms908734 GetFlags: HRESULT GetFlags(DWORD* pdwFlags);
 *   ms908738 GetItem: HRESULT GetItem(DWORDdwItemIndex,IAMPlayListItem** ppItem);
 *   ms908742 GetItemCount: HRESULT GetItemCount(DWORD* pdwItems);
 *   ms908746 GetNamedEvent: HRESULT GetNamedEvent(WCHARpwszEventName,DWORDdwItemIndex,IAMPlayListItem** ppItem,DWORD* pdwFlags);
 *   ms908750 GetRepeatInfo: HRESULT GetRepeatInfo(DWORD* pdwRepeatCount,DWORD* pdwRepeatStart,DWORD* pdwRepeatEnd);
 */

/* IAMPlayListItem: documented methods (11 pages).  Signatures recorded
 * verbatim.  (GetSourceURL prints its return type as RESULT --
 * the page's typo for HRESULT, repaired.)
 *   ms908759 GetFlags: HRESULT GetFlags(DWORD* pdwFlags);
 *   ms908763 GetLinkURL: HRESULT GetLinkURL(BSTR* pbstrURL);
 *   ms908767 GetScanDuration: HRESULT GetScanDuration(DWORDdwSourceIndex,REFERENCE_TIME* prtScanDuration);
 *   ms908770 GetSourceCount: HRESULT GetSourceCount(DWORD* pdwSources);
 *   ms908773 GetSourceDuration: HRESULT GetSourceDuration(DWORDdwSourceIndex,REFERENCE_TIME* prtDuration);
 *   ms908778 GetSourceEndMarker: HRESULT GetSourceEndMarker(DWORDdwSourceIndex,DWORD* pdwMarker);
 *   ms908782 GetSourceEndMarkerName: HRESULT GetSourceEndMarkerName(DWORDdwSourceIndex,BSTR* pbstrEndMarker);
 *   ms908787 GetSourceStart: HRESULT GetSourceStart(DWORDdwSourceIndex,REFERENCE_TIME* prtStart);
 *   ms908790 GetSourceStartMarker: HRESULT GetSourceStartMarker(DWORDdwSourceIndex,DWORD* pdwMarker);
 *   ms908793 GetSourceStartMarkerName: HRESULT GetSourceStartMarkerName(DWORDdwSourceIndex,BSTR* pbstrStartMarker);
 *   ms908797 GetSourceURL: RESULT GetSourceURL(DWORDdwSourceIndex,BSTR* pbstrURL);
 */

/* IAMStreamConfig: documented methods (4 pages).  Signatures recorded
 * verbatim.
 *   ms908804 GetFormat: HRESULT GetFormat(AM_MEDIA_TYPE** pmt);
 *   ms908807 GetNumberOfCapabilities: HRESULT GetNumberOfCapabilities(int* piCount, int* piSize);
 *   ms908811 GetStreamCaps: HRESULT GetStreamCaps(intiIndex,AM_MEDIA_TYPE** pmt,BYTE* pSCC);
 *   ms908823 SetFormat: HRESULT SetFormat(AM_MEDIA_TYPE* pmt);
 */

/* IAMStreamControl: documented methods (3 pages).  Signatures recorded
 * verbatim.
 *   ms908825 GetInfo: HRESULT GetInfo(AM_STREAM_INFO* pInfo);
 *   ms908841 StartAt: HRESULT StartAt(const REFERENCE_TIME* ptStart,DWORD dwCookie);
 *   ms908842 StopAt: HRESULT StopAt(const REFERENCE_TIME* ptStop,BOOL bSendExtra,DWORD dwCookie);
 */

/* IAMStreamSelect: documented methods (3 pages).  Signatures recorded
 * verbatim.
 *   ms908847 Count: HRESULT Count(DWORD* pcStreams);
 *   ms908850 Enable: HRESULT Enable(longlIndex,DWORDdwFlags);
 *   ms908855 Info: HRESULTInfo(longlIndex,AM_MEDIA_TYPE** ppmt,DWORD* pdwFlags,LCID* plcid,DWORD* pdwGroup,WCHAR** ppszName,IUnknown** ppObject,IUnknown** ppUnk);
 */

/* IAMTVTuner: documented methods (11 pages).  Signatures recorded  OS row: Windows CE 5.0 Networked Media Device Feature Pack.
 * verbatim.
 *   aa452516 AutoTune: HRESULT AutoTune( long lChannel, long *plFoundSignal);
 *   aa452517 get_AudioFrequency: HRESULT get_AudioFrequency( long *lFreq);
 *   aa452518 get_AvailableTVFormats: HRESULT get_AvailableTVFormats( long *lAnalogVideoStandard);
 *   aa452519 get_ConnectInput: HRESULT get_ConnectInput ( long *plIndex);
 *   aa452520 get_InputType: HRESULT get_InputType ( long lIndex, TunerInputType *pInputType);
 *   aa452521 get_NumInputConnections: HRESULT get_NumInputConnections( long *plNumInputConnections);
 *   aa452522 get_TVFormat: HRESULT get_TVFormat( long *plAnalogVideoStandard);
 *   aa452523 get_VideoFrequency: HRESULT get_VideoFrequency( long *lFreq);
 *   aa452525 put_ConnectInput: HRESULT put_ConnectInput( long lIndex);
 *   aa452526 put_InputType: HRESULT put_InputType( long lIndex, TunerInputType InputType);
 *   aa452527 StoreAutoTune: HRESULT StoreAutoTune(void);
 */

/* IAMTuner: documented methods (15 pages).  Signatures recorded  OS row: Windows CE 5.0 Networked Media Device Feature Pack.
 * verbatim.
 *   aa452500 ChannelMinMax: HRESULT ChannelMinMax( long *lChannelMin, long *lChannelMax);
 *   aa452501 GetAvailableModes: HRESULT GetAvailableModes( long *plModes);
 *   aa452502 get_Channel: HRESULT get_Channel ( long *plChannel, long *plVideoSubChannel, long *plAudioSubChannel);
 *   aa452503 get_CountryCode: HRESULT get_CountryCode( long *plCountryCode);
 *   aa452504 get_Mode: HRESULT get_Mode( AMTunerModeType *plMode);
 *   aa452505 get_TuningSpace: HRESULT get_TuningSpace( long *plTuningSpace);
 *   aa452507 Logon: HRESULT Logon( HANDLE hCurrentUser);
 *   aa452508 Logout: HRESULT Logout(void);
 *   aa452509 put_Channel: HRESULT put_Channel( long lChannel, long lVideoSubChannel, long lAudioSubChannel);
 *   aa452510 put_CountryCode: HRESULT put_CountryCode( long lCountryCode);
 *   aa452511 put_Mode: HRESULT put_Mode( AMTunerModeType lMode);
 *   aa452512 put_TuningSpace: HRESULT put_TuningSpace( long lTuningSpace);
 *   aa452513 RegisterNotificationCallBack: HRESULT RegisterNotificationCallBack( IAMTunerNotification *pNotify, long lEvents);
 *   aa452514 SignalPresent: HRESULT SignalPresent( long *plSignalStrength);
 *   aa452515 UnRegisterNotificationCallBack: HRESULT UnRegisterNotificationCallBack( IAMTunerNotification *pNotify);
 */

/* IAMovieSetup: documented methods (2 pages).  Signatures recorded  OS row: Windows CE 3.0 and later.
 * verbatim.
 *   ms908728 Register: HRESULT Register( );
 *   ms908731 Unregister: HRESULT Unregister( );
 */

/* IAsyncReader: documented methods (8 pages).  Signatures recorded
 * verbatim.
 *   ms908864 BeginFlush: HRESULT BeginFlush( );
 *   ms908869 EndFlush: HRESULT EndFlush( );
 *   ms908876 Length: HRESULT Length(LONGLONG* pTotal,LONGLONG* pAvailable);
 *   ms939468 Request: HRESULT Request(IMediaSample* pSample,DWORD dwUser);
 *   ms939473 RequestAllocator: HRESULT RequestAllocator(IMemAllocator* pPreferred,ALLOCATOR_PROPERTIES* pProps,IMemAllocator** ppActual);
 *   ms939476 SyncRead: HRESULTSyncRead(LONGLONGllPosition,LONGlLength,BYTE* pBuffer);
 *   ms939481 SyncReadAligned: HRESULT SyncReadAligned(IMediaSample* pSample);
 *   ms939486 WaitForNext: HRESULT WaitForNext(DWORD dwTimeout,IMediaSample** ppSample,DWORD* pdwUser);
 */

/* IBaseFilter: documented methods (5 pages).  Signatures recorded
 * verbatim.
 *   ms939490 EnumPins: HRESULT EnumPins(IEnumPins** ppEnum);
 *   ms939495 FindPin: HRESULT FindPin(LPCWSTR Id,IPin** ppPin);
 *   ms939504 JoinFilterGraph: HRESULT JoinFilterGraph(IFilterGraph* pGraph,LPCWSTR pName);
 *   ms939507 QueryFilterInfo: HRESULT QueryFilterInfo(FILTER_INFO* pInfo);
 *   ms939511 QueryVendorInfo: HRESULT QueryVendorInfo(LPWSTR* pVendorInfo);
 */

/* IBasicAudio: documented methods (4 pages).  Signatures recorded
 * verbatim.
 *   ms939515 get_Balance: HRESULT get_Balance(long* plBalance);
 *   ms939519 get_Volume: HRESULT get_Volume(long* plVolume);
 *   ms939529 put_Balance: HRESULT put_Balance(long lBalance);
 *   ms939532 put_Volume: HRESULT put_Volume(long lVolume);
 */

/* IBasicVideo: documented methods (32 pages).  Signatures recorded
 * verbatim.
 *   ms939551 get_AvgTimePerFrame: HRESULT get_AvgTimePerFrame(REFTIME* pAvgTimePerFrame);
 *   ms939552 get_BitErrorRate: HRESULT get_BitErrorRate(long* pBitErrorRate);
 *   ms939553 get_BitRate: HRESULT get_BitRate(long* pBitRate);
 *   ms939554 GetCurrentImage: HRESULTGetCurrentImage(long* pBufferSize,long* pDIBImage);
 *   ms939556 get_DestinationHeight: HRESULT get_DestinationHeight(long* pDestinationHeight);
 *   ms939557 get_DestinationLeft: HRESULT get_DestinationLeft(long* pDestinationLeft);
 *   ms939558 GetDestinationPosition: HRESULT GetDestinationPosition(long* pLeft,long* pTop,long* pWidth,long* pHeight);
 *   ms939559 get_DestinationTop: HRESULT get_DestinationTop(long* pDestinationTop);
 *   ms939560 get_DestinationWidth: HRESULT get_DestinationWidth(long* pDestinationWidth);
 *   ms939561 get_SourceHeight: HRESULT get_SourceHeight(long* pSourceHeight);
 *   ms939562 get_SourceLeft: HRESULT get_SourceLeft(long* pSourceLeft);
 *   ms939563 GetSourcePosition: HRESULTGetSourcePosition(long* pLeft,long* pTop,long* pWidth,long* pHeight);
 *   ms939564 get_SourceTop: HRESULT get_SourceTop(long* pSourceTop);
 *   ms939565 get_SourceWidth: HRESULT get_SourceWidth(long* pSourceWidth);
 *   ms939566 get_VideoHeight: HRESULT get_VideoHeight(long* pVideoHeight);
 *   ms939567 GetVideoPaletteEntries: HRESULTGetVideoPaletteEntries(longStartIndex,longEntries,long* pRetrieved,long* pPalette);
 *   ms939568 GetVideoSize: HRESULT GetVideoSize(long* pWidth,long* pHeight);
 *   ms939569 get_VideoWidth: HRESULT get_VideoWidth(long* pVideoWidth);
 *   ms939571 IsUsingDefaultDestination: HRESULT IsUsingDefaultDestination( );
 *   ms939572 IsUsingDefaultSource: HRESULT IsUsingDefaultSource( );
 *   ms939573 put_DestinationHeight: HRESULT put_DestinationHeight(long DestinationHeight);
 *   ms939574 put_DestinationLeft: HRESULT put_DestinationLeft(long DestinationLeft);
 *   ms939575 put_DestinationTop: HRESULT put_DestinationTop(long DestinationTop);
 *   ms939576 put_DestinationWidth: HRESULT put_DestinationWidth(long DestinationWidth);
 *   ms939577 put_SourceHeight: HRESULT put_SourceHeight(long SourceHeight);
 *   ms939578 put_SourceLeft: HRESULT put_SourceLeft(long SourceLeft);
 *   ms939579 put_SourceTop: HRESULT put_SourceTop(long SourceTop);
 *   ms939580 put_SourceWidth: HRESULT put_SourceWidth(long SourceWidth);
 *   ms939581 SetDefaultDestinationPosition: HRESULT SetDefaultDestinationPosition( );
 *   ms939582 SetDefaultSourcePosition: HRESULT SetDefaultSourcePosition( );
 *   ms939583 SetDestinationPosition: HRESULT SetDestinationPosition(long Left,long Top,long Width,long Height);
 *   ms939584 SetSourcePosition: HRESULT SetSourcePosition(long Left,long Top,long Width,long Height);
 */

/* IDMOWrapperFilter: documented methods (1 page).  Signatures recorded  OS row: Windows CE .NET 4.1 and later.
 * verbatim.
 *   aa451817 Init: HRESULT Init(REFCLSIDclsidDMO,REFCLSIDcatDMO);
 */

/* IDVREngineHelpers: documented methods (3 pages).  Signatures recorded  OS row: Windows CE 5.0 with the Networked Media Device Feature Pack.
 * verbatim.
 *   aa452539 CleanupOrphanedRecordings: HRESULT CleanupOrphanedRecordings( LPCOLESTR pszDirName);
 *   aa452540 DeleteRecording: HRESULT DeleteRecording( LPCOLESTR pszFileName);
 *   aa452541 GetRecordingSizeOnDisk: HRESULT GetRecordingSizeOnDisk( LPCOLESTR pszRecordingName, LONGLONG* pllBytes);
 */

/* IDirectDrawVideo: documented methods (16 pages).  Signatures recorded
 * verbatim.
 *   aa451769 CanUseOverlayStretch: HRESULT CanUseOverlayStretch(long* UseOverlayStretch);
 *   aa451770 CanUseScanLine: HRESULT CanUseScanLine(long* UseScanLine);
 *   aa451771 GetCaps: HRESULT GetCaps(DDCAPS* pCaps);
 *   aa451772 GetDirectDraw: HRESULT GetDirectDraw(LPDIRECTDRAW* ppDirectDraw);
 *   aa451773 GetEmulatedCaps: HRESULT GetEmulatedCaps(DDCAPS* pCaps);
 *   aa451774 GetFourCCCodes: HRESULT GetFourCCCodes(DWORD* pCount,DWORD* pCodes);
 *   aa451775 GetSurfaceDesc: HRESULT GetSurfaceDesc( DDSURFACEDESC* pSurfaceDesc);
 *   aa451776 GetSurfaceType: HRESULT GetSurfaceType(DWORD* pSurfaceType);
 *   aa451778 GetSwitches: HRESULT GetSwitches(DWORD* pSwitches);
 *   aa451795 SetDefault: HRESULT SetDefault( );
 *   aa451796 SetDirectDraw: HRESULT SetDirectDraw(LPDIRECTDRAW pDirectDraw);
 *   aa451797 SetSwitches: HRESULT SetSwitches(DWORD pSwitches);
 *   aa451798 UseOverlayStretch: HRESULT UseOverlayStretch(long UseOverlayStretch);
 *   aa451799 UseScanLine: HRESULT UseScanLine(long UseScanLine);
 *   aa451800 UseWhenFullScreen: HRESULT UseWhenFullScreen(long UseWhenFullScreen);
 *   aa451801 WillUseFullScreen: HRESULT WillUseFullScreen(long* UseWhenFullScreen);
 */

/* IDistributorNotify: documented methods (5 pages).  Signatures recorded
 * verbatim.
 *   aa451803 NotifyGraphChange: HRESULT NotifyGraphChange( );
 *   aa451804 Pause: HRESULT Pause( );
 *   aa451805 Run: HRESULT Run(REFERENCE_TIME tStart);
 *   aa451806 SetSyncSource: HRESULT SetSyncSource(IReferenceClock* pClock);
 *   aa451807 Stop: HRESULT Stop( );
 */

/* IEnumFilters: documented methods (4 pages).  Signatures recorded
 * verbatim.
 *   ms910534 Clone: HRESULT Clone(IEnumFilters** ppEnum);
 *   ms910536 Next: HRESULTNext(ULONGcFilters,IBaseFilter** ppFilter,ULONG* pcFetched);
 *   ms910538 Reset: HRESULT Reset( );
 *   ms910539 Skip: HRESULT Skip(ULONG cFilter);
 */

/* IEnumMediaTypes: documented methods (4 pages).  Signatures recorded
 * verbatim.
 *   ms910540 Clone: HRESULT Clone(IEnumMediaTypes** ppEnum);
 *   ms910542 Next: HRESULTNext(ULONGcMediaTypes,AM_MEDIA_TYPE** ppMediaTypes,ULONG* pcFetched);
 *   ms910543 Reset: HRESULT Reset( );
 *   ms910544 Skip: HRESULTSkip(ULONGcMediaTypes);
 */

/* IEnumPins: documented methods (4 pages).  Signatures recorded
 * verbatim.
 *   ms910545 Clone: HRESULT Clone(IEnumPins** ppEnum);
 *   ms910547 Next: HRESULTNext(ULONGcPins,IPin** ppPins,ULONG* pcFetched);
 *   ms910548 Reset: HRESULT Reset( );
 *   ms910549 Skip: HRESULT Skip(ULONG cPins);
 */

/* IEnumRegFilters: documented methods (4 pages).  Signatures recorded
 * verbatim.
 *   ms910550 Clone: HRESULT Clone(IEnumRegFilters** ppEnum);
 *   ms910552 Next: HRESULTNext(ULONGcFilters,REGFILTER** apRegFilter,ULONG* pcFetched);
 *   ms910553 Reset: HRESULT Reset( );
 *   ms910554 Skip: HRESULT Skip(ULONG celt);
 */

/* IFileSourceFilter: documented methods (2 pages).  Signatures recorded
 * verbatim.
 *   ms910556 GetCurfile: HRESULT GetCurfile(LPOLESTR* ppszFileName,AM_MEDIA_TYPE* pmt);
 *   ms910558 Load: HRESULT Load(LPCOLESTR pszFileName,const AM_MEDIA_TYPE* pmt);
 */

/* IFilterGraph: documented methods (8 pages).  Signatures recorded
 * verbatim.
 *   ms910561 AddFilter: HRESULT AddFilter(IBaseFilter* pFilter,LPCWSTRpName);
 *   ms910562 ConnectDirect: HRESULT ConnectDirect(IPin* ppinOut,IPin* ppinIn,const AM_MEDIA_TYPE* pmt);
 *   ms910563 Disconnect: HRESULT Disconnect(IPin* ppin);
 *   ms910564 EnumFilters: HRESULT EnumFilters(IEnumFilters** ppEnum);
 *   ms910565 FindFilterByName: HRESULT FindFilterByName(LPCWSTRpName,IBaseFilter** ppFilter);
 *   ms910567 Reconnect: HRESULT Reconnect(IPin* ppin);
 *   ms910568 RemoveFilter: HRESULT RemoveFilter(IBaseFilter* pFilter);
 *   ms910569 SetDefaultSyncSource: HRESULT SetDefaultSyncSource(void);
 */

/* IFilterGraph2: documented methods (1 page).  Signatures recorded
 * verbatim.
 *   ms910560 ReconnectEx: HRESULT ReconnectEx(IPin* ppin,const AM_MEDIA_TYPE* pmt);
 */

/* IFilterMapper: documented methods (8 pages).  Signatures recorded
 * verbatim.
 *   ms910570 EnumMatchingFilters: HRESULTEnumMatchingFilters(IEnumRegFilters** ppEnum,DWORDdwMerit,BOOLbInputNeeded,CLSIDclsInMaj,CLSIDclsInSub,BOOLbRender,BOOLbOutputNeeded,CLSIDclsOutMaj,CLSIDclsOutSub);
 *   ms910572 RegisterFilter: HRESULT RegisterFilter(CLSIDclsid,LPCWSTRName,DWORD dwMerit);
 *   ms910573 RegisterFilterInstance: HRESULT RegisterFilterInstance(CLSIDclsid,LPCWSTRName,CLSID* MRId);
 *   ms910574 RegisterPin: HRESULTRegisterPin(CLSIDFilter,LPCWSTRName,BOOLbRendered,BOOLbOutput,BOOLbZero,BOOLbMany,CLSIDConnectsToFilter,LPWSTRConnectsToPin);
 *   ms910575 RegisterPinType: HRESULT RegisterPinType(CLSIDclsFilter,LPCWSTRstrName,CLSIDclsMajorType,CCLSIDclsSubType);
 *   ms910576 UnregisterFilter: HRESULT UnregisterFilter(CLSIDFilter);
 *   ms910577 UnregisterFilterInstance: HRESULT UnregisterFilterInstance(CLSID MRId);
 *   ms910578 UnregisterPin: HRESULT UnregisterPin(CLSID Filter,LPCWSTR Name);
 */

/* IGraphBuilder: documented methods (5 pages).  Signatures recorded
 * verbatim.
 *   ms910579 AddSourceFilter: HRESULTAddSourceFilter(LPCWSTRlpwstrFileName,LPCWSTRlpwstrFilterName,IbaseFilter** ppFilter);
 *   ms910580 Connect: HRESULT Connect(IPin* ppinOut,IPin* ppinIn);
 *   ms910582 Render: HRESULT Render(IPin* ppinOut);
 *   ms910583 RenderFile: HRESULTRenderFile(LPCWSTRlpwstrFile,LPCWSTRlpwstrPlayList);
 *   ms910584 SetLogFile: HRESULT SetLogFile(HANDLEhFile);
 */

/* IGraphVersion: documented methods (1 page).  Signatures recorded
 * verbatim.
 *   ms910586 QueryVersion: HRESULT QueryVersion(LONG* pVersion);
 */

/* IKsPropertySet: documented methods (3 pages).  Signatures recorded  OS row: Windows CE 5.0 with the Networked Media Device Feature Pack.
 * verbatim.
 *   aa452543 Get: HRESULT Get( REFGUID guidPropSet, DWORD dwPropID, LPVOID pInstanceData, DWORD cbInstanceData, LPVOID pPropData, DWORD cbPropData, DWORD* pcbReturned);
 *   aa452545 QuerySupported: HRESULT QuerySupported( REFGUID guidPropSet, DWORD dwPropID, DWORD* pTypeSupport);
 *   aa452546 Set: HRESULT Set( REFGUID guidPropSet, DWORD dwPropID, LPVOID pInstanceData, DWORD cbInstanceData, LPVOID pPropData, DWORD cbPropData);
 */

/* IMediaControl: documented methods (7 pages).  Signatures recorded
 * verbatim.
 *   aa452259 AddSourceFilter: HRESULT AddSourceFilter(BSTRstrFilename,IDispatch** ppUnk);
 *   aa452260 GetState: HRESULT GetState(LONG msTimeout,OAFilterState* pfs);
 *   aa452262 Pause: HRESULT Pause( );
 *   aa452263 RenderFile: HRESULT RenderFile(BSTRstrFilename);
 *   aa452264 Run: HRESULT Run( );
 *   aa452265 Stop: HRESULT Stop( );
 *   aa452266 StopWhenReady: HRESULT StopWhenReady( );
 */

/* IMediaEvent: documented methods (6 pages).  Signatures recorded
 * verbatim.
 *   aa452267 CancelDefaultHandling: HRESULT CancelDefaultHandling(longlEvCode);
 *   aa452272 FreeEventParams: HRESULT FreeEventParams(longlEventCode,longlParam1,longlParam2);
 *   aa452273 GetEvent: HRESULTGetEvent(long* lEventCode,long* lParam1,long* lParam2,longmsTimeout);
 *   aa452274 GetEventHandle: HRESULT GetEventHandle(OAEVENT* hEvent);
 *   aa452276 RestoreDefaultHandling: HRESULT RestoreDefaultHandling(longlEvCode);
 *   aa452282 WaitForCompletion: HRESULT WaitForCompletion(longmsTimeout,long* pEvCode);
 */

/* IMediaEventEx: documented methods (3 pages).  Signatures recorded
 * verbatim.
 *   aa452268 GetNotifyFlags: HRESULT GetNotifyFlags(long* lplNoNotifyFlags);
 *   aa452270 SetNotifyFlags: HRESULT SetNotifyFlags(longlNoNotifyFlags);
 *   aa452271 SetNotifyWindow: HRESULT SetNotifyWindow(OAHWNDhwnd,longlMsg,longlInstanceData);
 */

/* IMediaEventSink: documented methods (1 page).  Signatures recorded
 * verbatim.
 *   aa452280 Notify: HRESULTNotify(longEventCode,longEventParam1,longEventParam2);
 */

/* IMediaFilter: documented methods (6 pages).  Signatures recorded
 * verbatim.
 *   aa452284 GetState: HRESULT GetState(DWORDdwMilliSecsTimeout,FILTER_STATE* State);
 *   aa452287 GetSyncSource: HRESULT GetSyncSource(IReferenceClock** pClock);
 *   ms931255 Pause: HRESULT Pause(void);
 *   ms931338 Run: HRESULT Run(REFERENCE_TIMEtStart);
 *   ms931385 SetSyncSource: HRESULT SetSyncSource(IReferenceClock* pClock);
 *   ms931389 Stop: HRESULT Stop(void);
 */

/* IMediaPosition: documented methods (11 pages).  Signatures recorded
 * verbatim.
 *   ms911574 get_Rate: HRESULT get_Rate(double* pdRate);
 *   ms911575 get_StopTime: HRESULT get_StopTime(REFTIME* pllTime);
 *   ms911577 put_CurrentPosition: HRESULT put_CurrentPosition(REFTIMEllTime);
 *   ms911578 put_PrerollTime: HRESULT put_PrerollTime(REFTIMEllTime);
 *   ms911579 put_Rate: HRESULT put_Rate(doubledRate);
 *   ms911580 put_StopTime: HRESULT put_StopTime(REFTIMEllTime);
 *   ms931423 CanSeekBackward: HRESULT CanSeekBackward(LONG* pCanSeekBackward);
 *   ms931424 CanSeekForward: HRESULT CanSeekForward(LONG* pCanSeekForward);
 *   ms931425 get_CurrentPosition: HRESULT get_CurrentPosition(REFTIME* pllTime);
 *   ms931426 get_Duration: HRESULT get_Duration(REFTIME* plength);
 *   ms931427 get_PrerollTime: HRESULT get_PrerollTime(REFTIME* pllTime);
 */

/* IMediaSample: documented methods (16 pages).  Signatures recorded
 * verbatim.
 *   ms911584 GetActualDataLength: HRESULT GetActualDataLength(void);
 *   ms911585 GetMediaTime: HRESULT GetMediaTime(LONGLONG* pTimeStart,LONGLONG* pTimeEnd);
 *   ms911586 GetMediaType: HRESULT GetMediaType(AM_MEDIA_TYPE** ppMediaType);
 *   ms911587 GetPointer: HRESULT GetPointer(BYTE** ppBuffer);
 *   ms911588 GetSize: HRESULT GetSize(void);
 *   ms911589 GetTime: HRESULT GetTime(REFERENCE_TIME* pTimeStart,REFERENCE_TIME* pTimeEnd);
 *   ms911591 IsDiscontinuity: HRESULT IsDiscontinuity(void);
 *   ms911592 IsPreroll: HRESULT IsPreroll(void);
 *   ms911593 IsSyncPoint: HRESULT IsSyncPoint(void);
 *   ms911594 SetActualDataLength: HRESULT SetActualDataLength(long lLen);
 *   ms911595 SetDiscontinuity: HRESULT SetDiscontinuity(BOOLbIsDiscontinuity);
 *   ms911596 SetMediaTime: HRESULT SetMediaTime(LONGLONG* pTimeStart, LONGLONG* pTimeEnd);
 *   ms911597 SetMediaType: HRESULT SetMediaType(AM_MEDIA_TYPE* pMediaType);
 *   ms911598 SetPreroll: HRESULT SetPreroll(BOOLbIsPreroll);
 *   ms911599 SetSyncPoint: HRESULT SetSyncPoint(BOOLbIsSyncPoint);
 *   ms911600 SetTime: HRESULT SetTime(REFERENCE_TIME* pTimeStart,REFERENCE_TIME* pTimeEnd);
 */

/* IMediaSample2: documented methods (2 pages).  Signatures recorded
 * verbatim.
 *   ms911581 GetProperties: HRESULTGetProperties(DWORDcbProperties,BYTE* pbProperties);
 *   ms911583 SetProperties: HRESULT SetProperties(DWORDcbProperties,const BYTE* pbProperties);
 */

/* IMediaSeeking: documented methods (17 pages).  Signatures recorded
 * verbatim.  (ms911601's TOC title lost the interface
 * qualifier; recorded here as IMediaSeeking::CheckCapabilities.)
 *   ms911601 CheckCapabilities: HRESULT CheckCapabilities(DWORD* pCapabilities);
 *   ms911602 ConvertTimeFormat: HRESULT ConvertTimeFormat(LONGLONG* pTarget,const GUID* pTargetFormat,LONGLONGSource,const GUID* pSourceFormat);
 *   ms911603 GetAvailable: HRESULT GetAvailable(LONGLONG* pEarliest,LONGLONG* pLatest);
 *   ms911604 GetCapabilities: HRESULT GetCapabilities(DWORD* pCapabilities);
 *   ms911605 GetCurrentPosition: HRESULT GetCurrentPosition(LONGLONG*pCurrent);
 *   ms911606 GetDuration: HRESULT GetDuration(LONGLONG* pDuration);
 *   ms911607 GetPositions: HRESULT GetPositions(LONGLONG* pCurrent,LONGLONG* pStop);
 *   ms911608 GetPreroll: HRESULT GetPreroll(LONGLONG* pllPreroll);
 *   ms911609 GetRate: HRESULT GetRate(double* dRate);
 *   ms911610 GetStopPosition: HRESULT GetStopPosition(LONGLONG* pStop);
 *   ms911611 GetTimeFormat: HRESULT GetTimeFormat(GUID* pFormat);
 *   ms911613 IsFormatSupported: HRESULT IsFormatSupported(const GUID* pFormat);
 *   ms911614 IsUsingTimeFormat: HRESULT IsUsingTimeFormat(const GUID* pFormat);
 *   ms911615 QueryPreferredFormat: HRESULT QueryPreferredFormat(GUID* pFormat);
 *   ms911616 SetPositions: HRESULTSetPositions(LONGLONG* pCurrent,DWORDdwCurrentFlags,LONGLONG* pStop,DWORDdwStopFlags);
 *   ms911617 SetRate: HRESULT SetRate(double dRate);
 *   ms911618 SetTimeFormat: HRESULT SetTimeFormat(const GUID* pFormat);
 */

/* IMediaStream: documented methods (6 pages).  Signatures recorded
 * verbatim.
 *   ms911619 AllocateSample: HRESULT AllocateSample(DWORDdwFlags,IStreamSample** ppSample);
 *   ms911620 CreateSharedSample: HRESULT CreateSharedSample(IStreamSample* pExistingSample,DWORDdwFlags,IStreamSample** ppNewSample);
 *   ms911621 GetInformation: HRESULT GetInformation(MSPID* pPurposeId,STREAM_TYPE* pType);
 *   ms911622 GetMultiMediaStream: HRESULT GetMultiMediaStream(IMultiMediaStream** ppMultiMediaStream);
 *   ms911624 SendEndOfStream: HRESULT SendEndOfStream(DWORD dwFlags);
 *   ms911625 SetSameFormat: HRESULT SetSameFormat(IMediaStream* pStreamThatHasDesiredFormat,DWORD dwFlags);
 */

/* IMemAllocator: documented methods (6 pages).  Signatures recorded
 * verbatim.
 *   ms911626 Commit: HRESULT Commit(void);
 *   ms911627 Decommit: HRESULT Decommit(void);
 *   ms911628 GetBuffer: HRESULT GetBuffer(IMediaSample** ppBuffer,REFERENCE_TIME* pStartTime,REFERENCE_TIME* pEndTime,DWORDdwFlags);
 *   ms911629 GetProperties: HRESULT GetProperties(ALLOCATOR_PROPERTIES* pProps);
 *   ms911631 ReleaseBuffer: HRESULT ReleaseBuffer(IMediaSample* pBuffer);
 *   ms931499 SetProperties: HRESULT SetProperties(ALLOCATOR_PROPERTIES* pRequest,ALLOCATOR_PROPERTIES* pActual);
 */

/* IMemInputPin: documented methods (6 pages).  Signatures recorded
 * verbatim.
 *   ms931604 GetAllocator: HRESULT GetAllocator(IMemAllocator** ppAllocator);
 *   ms931613 GetAllocatorRequirements: HRESULT GetAllocatorRequirements(ALLOCATOR_PROPERTIES* pProps);
 *   ms931631 NotifyAllocator: HRESULT NotifyAllocator(IMemAllocator* pAllocator,BOOLbReadOnly);
 *   ms931640 Receive: HRESULT Receive(IMediaSample* pSample);
 *   ms931649 ReceiveCanBlock: HRESULT ReceiveCanBlock(void);
 *   ms931660 ReceiveMultiple: HRESULTReceiveMultiple(IMediaSample** pSamples,longnSamples,long* nSamplesProcessed);
 */

/* IMultiMediaStream: documented methods (9 pages).  Signatures recorded
 * verbatim.
 *   ms911837 GetInformation: HRESULT GetInformation(DWORD* pdwFlags,STREAM_TYPE* pStreamType);
 *   ms911850 GetMediaStream: HRESULT GetMediaStream(REFMSPID idPurpose,IMediaStream** ppMediaStream);
 *   ms911855 GetState: HRESULT GetState(STREAM_STATE* pCurrentState);
 *   ms911946 GetTime: HRESULT GetTime(STREAM_TIME* pCurrentTime);
 *   ms911969 Seek: HRESULT Seek(STREAM_TIMESeekTime);
 *   ms911980 SetState: HRESULT SetState(STREAM_STATENewState);
 *   ms931669 EnumMediaStreams: HRESULT EnumMediaStreams(longIndex,IMediaStream** ppMediaStream);
 *   ms931676 GetDuration: HRESULT GetDuration(STREAM_TIME* pDuration);
 *   ms931682 GetEndOfStreamEventHandle: HRESULT GetEndOfStreamEventHandle(HANDLE* phEOS);
 */

/* INonDelegatingUnknown: documented methods (1 page).  Signatures recorded
 * verbatim.
 *   ms911992 INonDelegatingUnknown: HRESULT NonDelegatingQueryInterface(REFIIDiid,void **ppvObject);
 */

/* IOverlay: documented methods (10 pages).  Signatures recorded
 * verbatim.
 *   ms912083 Advise: HRESULTAdvise(IOverlayNotify* pOverlayNotify,DWORDdwInterests);
 *   ms912095 GetClipList: HRESULTGetClipList(RECT* pSourceRect,RECT* pDestinationRect,RGNDATA** ppRgnData);
 *   ms912107 GetColorKey: HRESULT GetColorKey(COLORKEY* pColorKey);
 *   ms912119 GetDefaultColorKey: HRESULT GetDefaultColorKey(COLORKEY* pColorKey);
 *   ms912127 GetPalette: HRESULT GetPalette(DWORD* pdwColors,PALETTEENTRY** ppPalette);
 *   ms912134 GetVideoPosition: HRESULT GetVideoPosition( RECT* pSourceRect, RECT* pDestinationRect);
 *   ms912142 GetWindowHandle: HRESULT GetWindowHandle(HWND* pHwnd);
 *   ms912211 SetColorKey: HRESULT SetColorKey(COLORKEY* pColorKey);
 *   ms912218 SetPalette: HRESULT SetPalette(DWORDdwColors,PALETTEENTRY* pPalette);
 *   ms912237 Unadvise: HRESULT Unadvise( );
 */

/* IOverlayNotify: documented methods (4 pages).  Signatures recorded
 * verbatim.
 *   ms912176 OnClipChange: HRESULTOnClipChange(RECT* pSourceRect,RECT* pDestinationRect,RGNDATA* pRgnData);
 *   ms912185 OnColorKeyChange: HRESULT OnColorKeyChange(COLORKEY* pColorKey);
 *   ms912194 OnPaletteChange: HRESULT OnPaletteChange(DWORDdwColors,const PALETTEENTRY* pPalette);
 *   ms912200 OnPositionChange: HRESULT OnPositionChange(const RECT* pSourceRect,const RECT* pDestinationRect);
 */

/* IPin: documented methods (15 pages).  Signatures recorded
 * verbatim.
 *   ms912246 BeginFlush: HRESULT BeginFlush(void);
 *   ms912252 Connect: HRESULT Connect(IPin* pReceivePin,const AM_MEDIA_TYPE* pmt);
 *   ms912262 ConnectedTo: HRESULT ConnectedTo(IPin** ppPin);
 *   ms912270 ConnectionMediaType: HRESULT ConnectionMediaType(AM_MEDIA_TYPE* pmt);
 *   ms912278 Disconnect: HRESULT Disconnect(void);
 *   ms912286 EndFlush: HRESULT EndFlush(void);
 *   ms912294 EndOfStream: HRESULT EndOfStream(void);
 *   ms912300 EnumMediaTypes: HRESULT EnumMediaTypes(IEnumMediaTypes** ppEnum);
 *   ms912310 NewSegment: HRESULT NewSegment(REFERENCE_TIMEtStart,REFERENCE_TIMEtStop,doubledRate);
 *   ms912318 QueryAccept: HRESULT QueryAccept(const AM_MEDIA_TYPE* pmt);
 *   ms912328 QueryDirection: HRESULT QueryDirection(PIN_DIRECTION* pPinDir);
 *   ms912337 QueryId: HRESULT QueryId(LPWSTR* Id);
 *   ms912346 QueryInternalConnections: HRESULT QueryInternalConnections(IPin** apPin,ULONG* nPin);
 *   ms912352 QueryPinInfo: HRESULT QueryPinInfo(PIN_INFO* pInfo);
 *   ms931694 ReceiveConnection: HRESULT ReceiveConnection(IPin* pConnector, AM_MEDIA_TYPE* pmt);
 */

/* IQualProp: documented methods (6 pages).  Signatures recorded
 * verbatim.
 *   ms931726 get_AvgFrameRate: HRESULT get_AvgFrameRate(int* piAvgFrameRate) PURE;
 *   ms931785 get_AvgSyncOffset: HRESULT get_AvgSyncOffset(int* piAvg);
 *   ms931794 get_DevSyncOffset: HRESULT get_DevSyncOffset(int* piDev);
 *   ms931798 get_FramesDrawn: HRESULT get_FramesDrawn(int* pcFramesDrawn);
 *   ms931799 get_FramesDroppedInRenderer: HRESULT get_FramesDroppedInRenderer(int* pcFrames);
 *   ms931801 get_Jitter: HRESULT get_Jitter(int* piJitter);
 */

/* IQualityControl: documented methods (2 pages).  Signatures recorded
 * verbatim.
 *   ms931711 Notify: HRESULT Notify(IBaseFilter* pSelf,Qualityq);
 *   ms931717 SetSink: HRESULT SetSink(IQualityControl* piqc);
 */

/* IReferenceClock: documented methods (4 pages).  Signatures recorded  OS row: Windows CE 3.0 and later.
 * verbatim.
 *   ms931803 AdvisePeriodic: HRESULT AdvisePeriodic(REFERENCE_TIMErtStartTime,REFERENCE_TIMErtPeriodTime,HSEMAPHOREhSemaphore,DWORD* pdwAdviseCookie);
 *   ms931804 AdviseTime: HRESULTAdviseTime(REFERENCE_TIMErtBaseTime,REFERENCE_TIMErtStreamTime,HEVENThEvent,DWORD* pdwAdviseCookie);
 *   ms931805 GetTime: HRESULT GetTime(REFERENCE_TIME* pTime);
 *   ms931807 Unadvise: HRESULT Unadvise(DWORDdwAdviseCookie);
 */

/* ISeekingPassThru: documented methods (1 page).  Signatures recorded
 * verbatim.
 *   ms931810 Init: HRESULTInit(BOOLbSupportRendering,IPin* pPin);
 */

/* IStreamBufferCapture: documented methods (8 pages).  Signatures recorded  OS row: Windows CE 5.0 with the Networked Media Device Feature Pack.
 * verbatim.
 *   aa452547 BeginPermanentRecording: HRESULT BeginPermanentRecording( LONGLONG hyRetainedSizeInMilliseconds, LONGLONG* phyActualRetainedSizeInMillisecs);
 *   aa452548 BeginTemporaryRecording: HRESULT BeginTemporaryRecording( LONGLONG hyBufferSizeInMilliseconds);
 *   aa452549 ConvertToTemporaryRecording: HRESULT ConvertToTemporaryRecording( LPCOLESTR pszFileName);
 *   aa452550 GetBoundToLiveToken: HRESULT GetBoundToLiveToken( LPOLESTR* ppszToken);
 *   aa452551 GetCaptureMode: HRESULT GetCaptureMode( STRMBUF_CAPTURE_MODE* peStrmbufCaptureMode, LONGLONG* phyMaxBufferMilliseconds);
 *   aa452552 GetCurrentPosition: HRESULT GetCurrentPosition( LONGLONG* phyCurrentPosition);
 *   aa452553 GetRecordingPath: HRESULT GetRecordingPath( LPOLESTR* ppszPath);
 *   aa452556 SetRecordingPath: HRESULT SetRecordingPath( LPCOLESTR pszPath);
 */

/* IStreamBufferPlayback: documented methods (3 pages).  Signatures recorded  OS row: Windows CE 5.0 with the Networked Media Device Feature Pack.
 * verbatim.
 *   aa452557 GetTunePolicy: HRESULT GetTunePolicy( STRMBUF_PLAYBACK_TUNE_POLICY* peStrmbufPlaybackTunePolicy);
 *   aa452559 NotifyGraphIsConnected: HRESULT NotifyGraphIsConnected();
 *   aa452560 SetTunePolicy: HRESULT SetTunePolicy( STRMBUF_PLAYBACK_TUNE_POLICY eStrmbufPlaybackTunePolicy);
 */

/* IStreamSample: documented methods (5 pages).  Signatures recorded
 * verbatim.
 *   ms931813 CompletionStatus: HRESULT CompletionStatus(DWORDdwFlags,DWORDdwMilliseconds);
 *   ms931814 GetMediaStream: HRESULT GetMediaStream(IMediaStream** ppMediaStream);
 *   ms931815 GetSampleTimes: HRESULT GetSampleTimes(STREAM_TIME* pStartTime,STREAM_TIME* pEndTime,STREAM_TIME* pCurrentTime);
 *   ms931817 SetSampleTimes: HRESULT SetSampleTimes(const STREAM_TIME* pStartTime,const STREAM_TIME* pEndTime);
 *   ms931818 Update: HRESULTUpdate(DWORDdwFlags,HANDLEhEvent,PAPCFUNCpfnAPC,DWORDdwAPCData);
 */

/* IVPBaseConfig: documented methods (13 pages).  Signatures recorded
 * verbatim.
 *   ms931992 GetConnectInfo: HRESULT GetConnectInfo(LPDWORDpdwNumConnectInfo,LPDDVIDEOPORTCONNECTpddVPConnectInfo);
 *   ms931993 GetMaxPixelRate: HRESULT GetMaxPixelRate(LPAMVPSIZEpamvpSize,LPDWORDpdwMaxPixelsPerSecond);
 *   ms931994 GetOverlaySurface: HRESULT GetOverlaySurface(LPDIRECTDRAWSURFACE* ppddOverlaySurface);
 *   ms931995 GetVideoFormats: HRESULT GetVideoFormats(LPDWORDpdwNumFormats,LPDDPIXELFORMATpddPixelFormats);
 *   ms931996 GetVPDataInfo: HRESULT GetVPDataInfo(LPAMVPDATAINFOpamvpDataInfo);
 *   ms931997 InformVPInputFormats: HRESULT InformVPInputFormats(DWORDdwNumFormats,LPDDPIXELFORMATpDDPixelFormats);
 *   ms932001 SetConnectInfo: HRESULT SetConnectInfo(DWORDdwChosenEntry);
 *   ms932002 SetDDSurfaceKernelHandles: HRESULT SetDDSurfaceKernelHandles(DWORDcHandles, DWORD*rgDDKernelHandles);
 *   ms932003 SetDirectDrawKernelHandle: HRESULT SetDirectDrawKernelHandle(DWORDdwDDKernelHandle);
 *   ms932004 SetInvertPolarity: HRESULT SetInvertPolarity(void);
 *   ms932005 SetSurfaceParameters: HRESULT SetSurfaceParameters(DWORDdwPitch,DWORDdwXOrigin,DWORDdwYOrigin) PURE;
 *   ms932006 SetVideoFormat: HRESULT SetVideoFormat(DWORDdwChosenEntry);
 *   ms932007 SetVideoPortID: HRESULT SetVideoPortID(DWORDdwVideoPortID);
 */

/* IVPBaseNotify: documented methods (1 page).  Signatures recorded
 * verbatim.
 *   ms932009 RenegotiateVPParameters: HRESULT RenegotiateVPParameters(void) PURE;
 */

/* IVPConfig: documented methods (2 pages).  Signatures recorded
 * verbatim.
 *   ms932011 IsVPDecimationAllowed: HRESULT IsVPDecimationAllowed(LPBOOLpbIsDecimationAllowed);
 *   ms932012 SetScalingFactors: HRESULT SetScalingFactors(LPAMVPSIZEpamvpSize);
 */

/* IVPNotify: documented methods (4 pages).  Signatures recorded
 * verbatim.
 *   ms932013 GetColorControls: HRESULT GetColorControls(LPDDCOLORCONTROL* ppColorControl) PURE;
 *   ms932014 GetDeinterlaceMode: HRESULT GetDeinterlaceMode(AMVP_MODE* pmode) PURE;
 *   ms932016 SetColorControls: HRESULT SetColorControls(LPDDCOLORCONTROLpColorControl) PURE;
 *   ms932017 SetDeinterlaceMode: HRESULT SetDeinterlaceMode(AMVP_MODEmode) PURE;
 */

/* IVideoWindow: documented methods (39 pages).  Signatures recorded
 * verbatim.  (Method-page titles spell the interface
 * "IVideoWIndow" -- archive typo, recorded.)
 *   ms912426 GetWindowPosition: HRESULTGetWindowPosition(long* pLeft,long* pTop,long* pWidth,long* pHeight);
 *   ms912445 get_WindowState: HRESULT get_WindowState(long* WindowState);
 *   ms912561 get_WindowStyle: HRESULT get_WindowStyle(long* pWindowStyle);
 *   ms931820 get_AutoShow: HRESULT get_AutoShow(long* AutoShow);
 *   ms931821 get_BackgroundPalette: HRESULT get_BackgroundPalette(long* pBackgroundPalette);
 *   ms931822 get_BorderColor: HRESULT get_BorderColor(long* pColor);
 *   ms931823 get_Caption: HRESULT get_Caption(BSTR* strCaption);
 *   ms931824 get_FullScreenMode: HRESULT get_FullScreenMode(long* FullScreenMode);
 *   ms931825 get_Height: HRESULT get_Height(long* pHeight);
 *   ms931826 get_Left: HRESULT get_Left(long* pLeft);
 *   ms931827 GetMaxIdealImageSize: HRESULT GetMaxIdealImageSize(long* pWidth,long* pHeight);
 *   ms931828 get_MessageDrain: HRESULT get_MessageDrain(OAHWND* Drain);
 *   ms931829 GetMinIdealImageSize: HRESULT GetMinIdealImageSize(long* pWidth,long* pHeight);
 *   ms931830 get_Owner: HRESULT get_Owner(OAHWND* pOwner);
 *   ms931831 GetRestorePosition: HRESULT GetRestorePosition(long* pLeft,long* pTop,long* pWidth,long* pHeight);
 *   ms931832 get_Top: HRESULT get_Top(long* pTop);
 *   ms931833 get_Visible: HRESULT get_Visible(long* pVisible);
 *   ms931834 get_Width: HRESULT get_Width(long* pWidth);
 *   ms931962 get_WindowStyleEx: HRESULT get_WindowStyleEx(long* pWindowStyleEx);
 *   ms931968 HideCursor: HRESULT HideCursor(longHideCursor);
 *   ms931970 IsCursorHidden: HRESULT IsCursorHidden(long* CursorHidden);
 *   ms931972 NotifyOwnerMessage: HRESULT NotifyOwnerMessage(longhwnd,longuMsg,longwParam,longlParam);
 *   ms931974 put_AutoShow: HRESULT put_AutoShow(longAutoShow);
 *   ms931975 put_BackgroundPalette: HRESULT put_BackgroundPalette(longBackgroundPalette);
 *   ms931976 put_BorderColor: HRESULT put_BorderColor(longColor);
 *   ms931977 put_Caption: HRESULT put_Caption(BSTRstrCaption);
 *   ms931978 put_FullScreenMode: HRESULT put_FullScreenMode(longFullScreenMode);
 *   ms931979 put_Height: HRESULT put_Height(longHeight);
 *   ms931981 put_Left: HRESULT put_Left(longLeft);
 *   ms931982 put_MessageDrain: HRESULT put_MessageDrain(OAHWNDDrain);
 *   ms931983 put_Owner: HRESULT put_Owner(OAHWNDOwner);
 *   ms931984 put_Top: HRESULT put_Top(longTop);
 *   ms931985 put_Visible: HRESULT put_Visible(longVisible);
 *   ms931986 put_Width: HRESULT put_Width(longWidth);
 *   ms931987 put_WindowState: HRESULT put_WindowState(longWindowState);
 *   ms931988 put_WindowStyle: HRESULT put_WindowStyle(longWindowStyle);
 *   ms931989 put_WindowStyleEx: HRESULT put_WindowStyleEx(longpWindowStyleEx);
 *   ms931990 SetWindowForeground: HRESULT SetWindowForeground(longFocus);
 *   ms931991 SetWindowPosition: HRESULT SetWindowPosition(longLeft,longTop,longWidth,longHeight);
 */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_DSHOW_H */
