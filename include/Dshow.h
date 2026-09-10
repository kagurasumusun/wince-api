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
#include "Mmsystem.h"   /* WAVEFORMATEX (CreateAudioMediaType, M88) */
#include "Wingdi.h"    /* COLORREF, RGBQUAD, BITMAPINFOHEADER, DIBSECTION,
                          HBITMAP */
#include "Objbase.h"   /* IUnknown (opaque forward) */
#include "Ddraw.h"     /* DDCAPS, LPDIRECTDRAW (IDirectDrawVideo vtable
                          parameters -- real since M97) */

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

/* ------------------------------------------------------------------
 * M74: DirectShow error message function (Quartz.lib row).
 * ------------------------------------------------------------------ */

/* ms925335 "AMGetErrorText" (CE 2.12+, DXPAK 1.0 for 2.12): print
 * `DWORD AMGetErrorText(HRESULT hr,TCHAR* pBuffer,DWORD MaxLen);`
 * Include file: "All DirectShow applications use the Dshow.h header
 * file" (aa451220, Building DirectShow Applications).  Link library:
 * Quartz.lib -- "Exports the AMGetErrorText function" (aa451220); the
 * function page itself prints no Link Library row, so the def
 * generator (which keys on Requirements rows) emits no quartz def. */
AKARI_CE_IMPORT DWORD AMGetErrorText(HRESULT hr, TCHAR *pBuffer,
                    DWORD MaxLen) AKARI_CE_NAME(AMGetErrorText);

/* ------------------------------------------------------------------
 * M88: DirectShow Base Classes reference -- utility functions,
 * macros and event notification codes (dshow-func.manifest 68
 * rows / dshow-macro.manifest 72 rows, group-header rows excluded;
 * Windows Media Event Notification Codes group, graphics-book
 * harvest).  Every page's Requirements block prints the "different
 * include file and link library requirements" pointer (see Setting
 * Up the Build Environment), OS "Windows CE 2.12 and later.
 * Version 2.12 requires DXPAK 1.0 or later", and an EMPTY Header
 * row; the documented include home is this header (aa451220
 * "Building DirectShow Applications": "All DirectShow applications
 * use the Dshow.h header file").  No page prints a Link Library
 * row, so the def generator emits nothing new (the Quartz.lib
 * AMGetErrorText note above is unchanged).
 *
 * C++-only signatures are recorded, not declared: AreEqualVideoTypes
 * and the CCritSec helpers name C++ classes with no CE pages;
 * FreeMediaType/ReadInt/ConvertToMilliseconds print C++ reference
 * parameters; WaitDispatchingMessages prints C++ default arguments
 * (declared here in C form, four required parameters).  STDAPI
 * prints are carried as HRESULT (Objbase.h STDAPI policy).
 * ------------------------------------------------------------------ */

/* --- Functions (declared; page prints verbatim in each note). --- */

/* aa451723 "GetBitCount":
 * `WORD GetBitCount(const GUID *pSubtype);`. */
AKARI_CE_IMPORT WORD GetBitCount(const GUID *pSubtype)
                     AKARI_CE_NAME(GetBitCount);

/* ms926782 "ContainsPalette":
 * `BOOL ContainsPalette(const VIDEOINFOHEADER *pVideoInfo);`. */
AKARI_CE_IMPORT BOOL ContainsPalette(const VIDEOINFOHEADER *pVideoInfo)
                     AKARI_CE_NAME(ContainsPalette);

/* aa451726 "GetBitmapSize":
 * `DWORD GetBitmapSize(const BITMAPINFOHEADER *pHeader);`. */
AKARI_CE_IMPORT DWORD GetBitmapSize(const BITMAPINFOHEADER *pHeader)
                      AKARI_CE_NAME(GetBitmapSize);

/* aa451724 "GetBitmapFormatSize":
 * `LONG GetBitmapFormatSize(const BITMAPINFOHEADER *pHeader);`. */
AKARI_CE_IMPORT LONG GetBitmapFormatSize(const BITMAPINFOHEADER *pHeader)
                     AKARI_CE_NAME(GetBitmapFormatSize);

/* aa451727 "GetBitmapSubtype":
 * `const GUID GetBitmapSubtype(const BITMAPINFOHEADER *pHeader);`
 * (top-level const on the return type has no effect in C; dropped). */
AKARI_CE_IMPORT GUID GetBitmapSubtype(const BITMAPINFOHEADER *pHeader)
                           AKARI_CE_NAME(GetBitmapSubtype);

/* aa451741 "GetTrueColorType":
 * `const GUID GetTrueColorType(const BITMAPINFOHEADER *pHeader);`
 * (top-level const on the return type has no effect in C; dropped). */
AKARI_CE_IMPORT GUID GetTrueColorType(const BITMAPINFOHEADER *pHeader)
                           AKARI_CE_NAME(GetTrueColorType);

/* aa451740 "GetSubtypeName":
 * `TCHAR * GetSubtypeName(const GUID *pSubtype);`. */
AKARI_CE_IMPORT TCHAR * GetSubtypeName(const GUID *pSubtype)
                        AKARI_CE_NAME(GetSubtypeName);

/* aa451725 "GetBitmapPalette":
 * `const RGBQUAD * GetBitmapPalette(const VIDEOINFOHEADER *pVideoInfo);`. */
AKARI_CE_IMPORT const RGBQUAD * GetBitmapPalette(const VIDEOINFOHEADER *pVideoInfo)
                                AKARI_CE_NAME(GetBitmapPalette);

/* aa452474 "WriteBSTR" (print `STDAPI WriteBSTR(...)`):
 * `HRESULT WriteBSTR(BSTR *pstrDest, LPCWSTR szSrc);`. */
AKARI_CE_IMPORT HRESULT WriteBSTR(BSTR *pstrDest, LPCWSTR szSrc)
                        AKARI_CE_NAME(WriteBSTR);

/* aa451719 "FreeBSTR" (print `STDAPI FreeBSTR(...)`):
 * `HRESULT FreeBSTR(BSTR *pstr);`. */
AKARI_CE_IMPORT HRESULT FreeBSTR(BSTR *pstr)
                        AKARI_CE_NAME(FreeBSTR);

/* ms912061 "IntToWstr":
 * `void IntToWstr(int i, LPWSTR wstrDest);`. */
AKARI_CE_IMPORT void IntToWstr(int i, LPWSTR wstrDest)
                     AKARI_CE_NAME(IntToWstr);

/* aa452476 "WstrToInt":
 * `int WstrToInt(LPCWSTR wstrSrc);`. */
AKARI_CE_IMPORT int WstrToInt(LPCWSTR wstrSrc)
                    AKARI_CE_NAME(WstrToInt);

/* ms926785 "ConvertVideoInfoToVideoInfo2" (print `STDAPI ...`):
 * `HRESULT ConvertVideoInfoToVideoInfo2(AM_MEDIA_TYPE *pmt);`. */
AKARI_CE_IMPORT HRESULT ConvertVideoInfoToVideoInfo2(AM_MEDIA_TYPE *pmt)
                        AKARI_CE_NAME(ConvertVideoInfoToVideoInfo2);

/* ms907274 "CreateAudioMediaType" (print `STDAPI ...`):
 * `HRESULT CreateAudioMediaType(const WAVEFORMATEX *pwfx, AM_MEDIA_TYPE *pmt, BOOL bSetFormat);`. */
AKARI_CE_IMPORT HRESULT CreateAudioMediaType(const WAVEFORMATEX *pwfx, AM_MEDIA_TYPE *pmt, BOOL bSetFormat)
                        AKARI_CE_NAME(CreateAudioMediaType);

/* ms907276 "CreateMediaType":
 * `AM_MEDIA_TYPE * WINAPI CreateMediaType(AM_MEDIA_TYPE const *pSrc);`. */
AKARI_CE_IMPORT AM_MEDIA_TYPE * WINAPI CreateMediaType(AM_MEDIA_TYPE const *pSrc)
                                       AKARI_CE_NAME(CreateMediaType);

/* ms926786 "CopyMediaType":
 * `void WINAPI CopyMediaType(AM_MEDIA_TYPE *pmtTarget, const AM_MEDIA_TYPE *pmtSource);`. */
AKARI_CE_IMPORT void WINAPI CopyMediaType(AM_MEDIA_TYPE *pmtTarget, const AM_MEDIA_TYPE *pmtSource)
                            AKARI_CE_NAME(CopyMediaType);

/* aa451572 "DeleteMediaType":
 * `void WINAPI DeleteMediaType(AM_MEDIA_TYPE *pmt);`. */
AKARI_CE_IMPORT void WINAPI DeleteMediaType(AM_MEDIA_TYPE *pmt)
                            AKARI_CE_NAME(DeleteMediaType);

/* aa451697 "EqualPins":
 * `BOOL EqualPins(IUnknown *pPin1, IUnknown *pPin2);`. */
AKARI_CE_IMPORT BOOL EqualPins(IUnknown *pPin1, IUnknown *pPin2)
                     AKARI_CE_NAME(EqualPins);

/* aa451732 "GetInterface" (page title "GetInterface (DirectShow)"):
 * `HRESULT GetInterface(LPUNKNOWN pUnk, void **ppv);`. */
AKARI_CE_IMPORT HRESULT GetInterface(LPUNKNOWN pUnk, void **ppv)
                        AKARI_CE_NAME(GetInterface);

/* ms925336 "AMGetWideString" (print `STDAPI ...`):
 * `HRESULT AMGetWideString(LPCWSTR pszString, LPWSTR *ppszReturn);`. */
AKARI_CE_IMPORT HRESULT AMGetWideString(LPCWSTR pszString, LPWSTR *ppszReturn)
                        AKARI_CE_NAME(AMGetWideString);

/* ms925338 "AMovieDllRegisterServer":
 * `HRESULT AMovieDllRegisterServer(void);`. */
AKARI_CE_IMPORT HRESULT AMovieDllRegisterServer(void)
                        AKARI_CE_NAME(AMovieDllRegisterServer);

/* ms925339 "AMovieDllUnregisterServer":
 * `HRESULT AMovieDllUnregisterServer(void);`. */
AKARI_CE_IMPORT HRESULT AMovieDllUnregisterServer(void)
                        AKARI_CE_NAME(AMovieDllUnregisterServer);

/* ms932024 "LoadOLEAut32" (print `LoadOLEAut32( );`):
 * `HINSTANCE LoadOLEAut32(void);`. */
AKARI_CE_IMPORT HINSTANCE LoadOLEAut32(void)
                          AKARI_CE_NAME(LoadOLEAut32);

/* ms932023 "llMulDiv":
 * `LONGLONG WINAPI llMulDiv(LONGLONG a, LONGLONG b, LONGLONG c, LONGLONG rnd);`. */
AKARI_CE_IMPORT LONGLONG WINAPI llMulDiv(LONGLONG a, LONGLONG b, LONGLONG c, LONGLONG rnd)
                                AKARI_CE_NAME(llMulDiv);

/* ms912016 "Int64x32Div32":
 * `LONGLONG WINAPI Int64x32Div32(LONGLONG a, LONG b, LONG c, LONG rnd);`. */
AKARI_CE_IMPORT LONGLONG WINAPI Int64x32Div32(LONGLONG a, LONG b, LONG c, LONG rnd)
                                AKARI_CE_NAME(Int64x32Div32);

/* ms931812 "IsEqualObject":
 * `BOOL WINAPI IsEqualObject(IUnknown *pFirst, IUnknown *pSecond);`. */
AKARI_CE_IMPORT BOOL WINAPI IsEqualObject(IUnknown *pFirst, IUnknown *pSecond)
                            AKARI_CE_NAME(IsEqualObject);

/* ms925597 "atoi" (DirectShow decimal-only variant):
 * `int WINAPI atoi(const TCHAR *sz);`. */
AKARI_CE_IMPORT int WINAPI atoi(const TCHAR *sz)
                           AKARI_CE_NAME(atoi);

/* aa452418 "WaitDispatchingMessages" (print carries C++ default arguments `hwnd = NULL, uMsg = 0` -- declared here without defaults (C)):
 * `DWORD WINAPI WaitDispatchingMessages(HANDLE hObject, DWORD dwWait, HWND hwnd, UINT uMsg);`. */
AKARI_CE_IMPORT DWORD WINAPI WaitDispatchingMessages(HANDLE hObject, DWORD dwWait, HWND hwnd, UINT uMsg)
                             AKARI_CE_NAME(WaitDispatchingMessages);

/* aa452475 "WriteInt" (print `STDAPI WriteInt(...)`):
 * `HRESULT WriteInt(IStream *pIStream, int n);`. */
AKARI_CE_IMPORT HRESULT WriteInt(IStream *pIStream, int n)
                        AKARI_CE_NAME(WriteInt);

/* ms907278 "CreatePosPassThru" (print `STDAPI ...`; creates the CPosPassThru COM object):
 * `HRESULT CreatePosPassThru(LPUNKNOWN pAgg, BOOL bRenderer, IPin *pPin, IUnknown **ppPassThru);`. */
AKARI_CE_IMPORT HRESULT CreatePosPassThru(LPUNKNOWN pAgg, BOOL bRenderer, IPin *pPin, IUnknown **ppPassThru)
                        AKARI_CE_NAME(CreatePosPassThru);

/* ms907766 "DbgAssert":
 * `void WINAPI DbgAssert(const TCHAR *pCondition, const TCHAR *pFileName, INT iLine);`. */
AKARI_CE_IMPORT void WINAPI DbgAssert(const TCHAR *pCondition, const TCHAR *pFileName, INT iLine)
                            AKARI_CE_NAME(DbgAssert);

/* ms907780 "DbgKernelAssert":
 * `void WINAPI DbgKernelAssert(const TCHAR *pCondition, const TCHAR *pFileName, INT iLine);`. */
AKARI_CE_IMPORT void WINAPI DbgKernelAssert(const TCHAR *pCondition, const TCHAR *pFileName, INT iLine)
                            AKARI_CE_NAME(DbgKernelAssert);

/* ms907768 "DbgBreakPoint":
 * `void WINAPI DbgBreakPoint(const TCHAR *pCondition, const TCHAR *pFileName, INT iLine);`. */
AKARI_CE_IMPORT void WINAPI DbgBreakPoint(const TCHAR *pCondition, const TCHAR *pFileName, INT iLine)
                            AKARI_CE_NAME(DbgBreakPoint);

/* ms907782 "DbgOutString":
 * `void WINAPI DbgOutString(LPCTSTR psz);`. */
AKARI_CE_IMPORT void WINAPI DbgOutString(LPCTSTR psz)
                            AKARI_CE_NAME(DbgOutString);

/* ms907769 "DbgDumpObjectRegister" (print `DbgDumpObjectRegister( );`):
 * `void WINAPI DbgDumpObjectRegister(void);`. */
AKARI_CE_IMPORT void WINAPI DbgDumpObjectRegister(void)
                            AKARI_CE_NAME(DbgDumpObjectRegister);

/* ms907783 "DbgSetWaitTimeout":
 * `void WINAPI DbgSetWaitTimeout(DWORD dwTimeout);`. */
AKARI_CE_IMPORT void WINAPI DbgSetWaitTimeout(DWORD dwTimeout)
                            AKARI_CE_NAME(DbgSetWaitTimeout);

/* ms907784 "DbgWaitForMultipleObjects":
 * `DWORD WINAPI DbgWaitForMultipleObjects(DWORD nCount, CONST HANDLE *lpHandles, BOOL bWaitAll);`. */
AKARI_CE_IMPORT DWORD WINAPI DbgWaitForMultipleObjects(DWORD nCount, CONST HANDLE *lpHandles, BOOL bWaitAll)
                             AKARI_CE_NAME(DbgWaitForMultipleObjects);

/* ms907785 "DbgWaitForSingleObject":
 * `DWORD WINAPI DbgWaitForSingleObject(HANDLE h);`. */
AKARI_CE_IMPORT DWORD WINAPI DbgWaitForSingleObject(HANDLE h)
                             AKARI_CE_NAME(DbgWaitForSingleObject);

/* --- Functions (recorded; C++ classes / reference parameters). --- */

/* ms925565 "AreEqualVideoTypes": `BOOL WINAPI AreEqualVideoTypes (CMediaType* pmt1,CMediaType* pmt2);` -- CMediaType (C++ class) has no CE page. */
/* aa451720 "FreeMediaType": `void WINAPI FreeMediaType(AM_MEDIA_TYPE& mt);` -- C++ reference parameter. */
/* ms932275 "ReadInt": `STDAPI_(int)ReadInt(IStream* pIStream,HRESULT &hr);` -- C++ reference parameter (print `STDAPI_(int)`); returns the integer value, or zero on error. */
/* ms926784 "ConvertToMilliseconds": `LONGLONG WINAPI ConvertToMilliseconds(const REFERENCE_TIME& RT);` -- C++ const-reference parameter. */
/* aa451614 "DumpGraph": `void WINAPI (IfilterGraph* pGraph,DWORD dwLevel)` -- print DROPS the function name and misspells the interface (`IfilterGraph`; IFilterGraph) -- archive print artifact; body describes DumpGraph, debug output of a filter graph. */
/* ms938830 "CritCheckIn": `BOOL WINAPI CritCheckIn(CCritSec* pcCrit);` -- CCritSec (C++ class) has no CE page. */
/* ms938831 "CritCheckOut": `BOOL WINAPI CritCheckOut(CCritSec* pcCrit);` -- CCritSec (C++ class) has no CE page. */
/* ms907781 "DbgLockTrace": `void WINAPI DbgLockTrace(CCritSec* pcCrit,BOOL fTrace);` -- CCritSec (C++ class) has no CE page. */

/* --- Macros (usage prints only; no #define bodies are published,
 * so all are recorded -- the WM_SIDESHOW_* M82 precedent). --- */

/* aa451579 "DIBSIZE": usage `DIBSIZE(bi)` -- byte size of the specified DIB (BITMAPINFOHEADER bi). */
/* aa451744 "HEADER": usage `HEADER(pVideoInfo)` -- pointer to the BITMAPINFOHEADER of a VIDEOINFOHEADER. */
/* ms926776 "COLORS": usage `COLORS(pbmi)` -- pointer to the RGBQUAD palette array of a VIDEOINFOHEADER. */
/* ms936830 "BITMASKS": usage `BITMASKS(pbmi)` -- pointer to the bitmask array of a VIDEOINFOHEADER. */
/* ms936839 "BIT_MASKS_MATCH": usage `BIT_MASKS_MATCH(pbmi1,pbmi2)` -- TRUE if the two VIDEOINFOHEADER bitmasks match. */
/* ms932251 "PALETTISED": usage `PALETTISED(pbmi)` -- nonzero if the image's palette is 8-bit or less. */
/* aa452395 "TRUECOLOR": usage `TRUECOLOR (pbmi)` -- pointer to the TRUECOLORINFO (palette + bitmasks) of a VIDEOINFOHEADER. */
/* ms932250 "PALETTE_ENTRIES": usage `PALETTE_ENTRIES(pbmi)` -- number of palette entries of a VIDEOINFOHEADER. */
/* ms932288 "RESET_HEADER": usage `RESET_HEADER(pbmi)` -- clears the BITMAPINFOHEADER of the video image. */
/* ms932289 "RESET_MASKS": usage `RESET_MASKS(pbmi)` -- clears the bitmask array of the video image. */
/* ms932290 "RESET_PALETTE": usage `RESET_PALETTE(pbmi)` -- clears the palette array of the video image. */
/* ms932308 "SIZE_EGA_PALETTE": usage `SIZE_EGA_PALETTE` -- size, in bytes, of an EGA palette. */
/* ms932309 "SIZE_MASKS": usage `SIZE_MASKS` -- size, in bytes, of a bitmask's color palette (three colors). */
/* ms932311 "SIZE_PALETTE": usage `SIZE_PALETTE` -- size, in bytes, of a bitmap's color palette. */
/* ms932312 "SIZE_PREHEADER": usage `SIZE_PREHEADER` -- size of the BITMAPINFOHEADER prefix of a VIDEOINFOHEADER. */
/* ms932313 "SIZE_VIDEOHEADER": usage `SIZE_VIDEOHEADER` -- combined size of all VIDEOINFOHEADER data members. */
/* ms932310 "SIZE_MPEG1VIDEOINFO": usage `SIZE_MPEG1VIDEOINFO` -- size of an MPEG1VIDEOINFO, including the sequence header. */
/* ms932231 "MPEG1_SEQUENCE_INFO": usage `MPEG1_SEQUENCE_INFO(pv)` -- bSequenceHeader member of an MPEG1VIDEOINFO. */
/* aa451569 "DECLARE_IUNKNOWN": usage `#define DECLARE_IUNKNOWN` -- declares the three IUnknown methods for a new interface; the page prints the #define with NO body -- recorded only. */
/* ms932236 "MSR_START": usage `#define MSR_START(int Id)` -- records the start time of a performance event; print shows the #define with parameter list -- body not printed. */
/* ms932237 "MSR_STOP": usage `#define MSR_STOP(int Id)` -- records the stop time of a performance event; body not printed. */
/* ms907767 "DbgBreak": usage `DbgBreak(strLiteral)` -- breakpoint macro; displays the string if executed. */
/* ms932018 "KDbgBreak": usage `KDbgBreak(strLiteral)` -- kernel breakpoint macro (does not display the string). */
/* ms932239 "NAME": usage `NAME(strLiteral)` -- generates a debug-only string. */
/* ms932286 "REMIND": usage `REMIND(strLiteral)` -- generates a compile-time string (source file + line). */
/* ms932242 "NOTE through NOTE5 Macros": usage `NOTE(pFormat);NOTEx(pFormat,[a-e]);` -- printf-style debugger output macros, NOTE through NOTE5. */
/* aa451530 "CheckPointer": usage `CheckPointer(p,ret)` -- returns ret if p is NULL; page prints no #define body. */
/* aa452402 "ValidateReadPtr": usage `ValidateReadPtr(const void *p,UINT cb);` -- read-pointer check (calls DbgBreak); active only when DEBUG/VFWROBUST is defined. */
/* aa452403 "ValidateReadWritePtr": usage `ValidateReadWritePtr(p,cb)` -- read-write pointer check. */
/* aa452404 "ValidateStringPtr": usage `ValidateStringPtr(p)` -- string pointer check. */
/* aa452405 "ValidateStringPtrA": usage `ValidateStringPtrA(p)` -- ANSI string pointer check. */
/* aa452406 "ValidateStringPtrW": usage `ValidateStringPtrW(p)` -- wide string pointer check. */
/* aa452407 "ValidateWritePtr": usage `ValidateWritePtr(p,cb)` -- write pointer check. */

/* --- Event notification codes (DirectShow Macros sub-book; the
 * pages print lParam1/lParam2 semantics but NO numeric values --
 * names recorded only). --- */

/* aa451631 "EC_ACTIVATE": An audio or video renderer is losing or gaining activation. The audio or video renderer sends this event notification -- no value printed; name recorded only. */
/* aa451633 "EC_BUFFERING_DATA": The buffering status is changing -- no value printed; name recorded only. */
/* aa451634 "EC_CLOCK_CHANGED": The filter graph has changed from one reference clock to another -- no value printed; name recorded only. */
/* aa451635 "EC_COMPLETE": All data has been rendered. Renderers send this event notification -- no value printed; name recorded only. */
/* aa451670 "EC_DRM_LEVEL": This event code notifies when content protected by digital rights management (DRM) requests some form of analog content protection. This event is not supported in Windows Media DRM 7.1 -- no value printed; name recorded only. */
/* aa451638 "EC_END_OF_SEGMENT": This macro notifies that a segment end has been reached -- no value printed; name recorded only. */
/* aa451642 "EC_ERROR_STILLPLAYING": A playback error has occurred, but the graph is still playing -- no value printed; name recorded only. */
/* aa451640 "EC_ERRORABORT": An error forced the termination of a requested operation -- no value printed; name recorded only. */
/* aa451644 "EC_FULLSCREEN_LOST": The video renderer is switching out of full-screen mode -- no value printed; name recorded only. */
/* aa451647 "EC_NEED_RESTART": The current graph must be stopped and restarted -- no value printed; name recorded only. */
/* aa451648 "EC_NOTIFY_WINDOW": Pass the window handle around during pin connection -- no value printed; name recorded only. */
/* aa451649 "EC_OLE_EVENT": A filter is passing a text string to the application -- no value printed; name recorded only. */
/* aa451650 "EC_OPENING_FILE": The open file status is changing -- no value printed; name recorded only. */
/* aa451651 "EC_PALETTE_CHANGED": The video palette has changed -- no value printed; name recorded only. */
/* aa451653 "EC_QUALITY_CHANGE": The playback quality has changed -- no value printed; name recorded only. */
/* aa451654 "EC_REPAINT": A repaint is required. Paused or stopped video renderers send this message when they receive a WM_PAINT message and there is no data to display -- no value printed; name recorded only. */
/* aa451655 "EC_SEGMENT_STARTED": This macro notifies that a new segment has been started -- no value printed; name recorded only. */
/* aa451656 "EC_SHUTTING_DOWN": The shutdown of the filter graph is starting -- no value printed; name recorded only. */
/* aa451657 "EC_STARVATION": A filter has detected starvation -- no value printed; name recorded only. */
/* aa451659 "EC_STREAM_CONTROL_STARTED": A previous call to the IAMStreamControl::StartAt method has taken effect -- no value printed; name recorded only. */
/* aa451660 "EC_STREAM_CONTROL_STOPPED": A previous call to the IAMStreamControl::StopAt method has taken effect -- no value printed; name recorded only. */
/* aa451661 "EC_STREAM_ERROR_STILLPLAYING": The stream is still playing, but should not be playing -- no value printed; name recorded only. */
/* aa451662 "EC_STREAM_ERROR_STOPPED": The stream has stopped, but should not have stopped -- no value printed; name recorded only. */
/* aa451663 "EC_TIME": The requested reference time occurred -- no value printed; name recorded only. */
/* aa451664 "EC_USERABORT": A user has forced the termination of a requested operation -- no value printed; name recorded only. */
/* aa451668 "EC_VIDEO_SIZE_CHANGED": The size of the native video has changed -- no value printed; name recorded only. */
/* aa451667 "EC_VIDEO_SIZE_AR_CHANGED": The size or aspect ratio of the native video has changed -- no value printed; name recorded only. */
/* aa451669 "EC_WINDOW_DESTROYED": The video renderer's filter is being removed or destroyed. Video renderers send this event notification so that resources that depend on window focus can be passed to other filters -- no value printed; name recorded only. */

/* --- Windows Media event notification codes (graphics-book
 * harvest; these pages print NO Requirements rows at all -- no
 * header, no library; lParam semantics only, no values). --- */

/* aa451632 "EC_BANDWIDTHCHANGE": This event code is sent when the bandwidth level of the streaming data has changed -- no value printed; no Requirements row; name recorded only. */
/* aa451636 "EC_CONTENTPROPERTY_CHANGED": This event code is sent when a streaming media filter receives a change in the stream's description information -- no value printed; no Requirements row; name recorded only. */
/* aa451637 "EC_DRMSTATUS": This event code is sent when various points during the digital rights management (DRM) process are reached -- no value printed; no Requirements row; name recorded only. */
/* aa451639 "EC_EOS_SOON": This event code indicates that the source filter is about to deliver an end-of-stream (EOS) message downstream -- no value printed; no Requirements row; name recorded only. */
/* aa451641 "EC_ERRORABORTEX": This event code indicates that the operation aborted because of an error -- no value printed; no Requirements row; name recorded only. */
/* aa451643 "EC_FILE_CLOSED": This event code is sent when the file is involuntarily closed -- no value printed; no Requirements row; name recorded only. */
/* aa451645 "EC_LOADSTATUS": This event code is sent when various points are reached while a network file is being loaded -- no value printed; no Requirements row; name recorded only. */
/* aa451646 "EC_MARKER_HIT": This event code indicates that a marker has just been passed -- no value printed; no Requirements row; name recorded only. */
/* aa451652 "EC_PLEASE_REOPEN": This event code indicates that the graph should be re-rendered -- no value printed; no Requirements row; name recorded only. */
/* aa451658 "EC_STATUS": This event code allows arbitrary status messages to be passed to the application -- no value printed; no Requirements row; name recorded only. */
/* aa451665 "EC_VIDEOFRAMEREADY": This event code is sent to notify the application that the first video frame is about to be drawn -- no value printed; no Requirements row; name recorded only. */
/* ================================================================== */
/* ================================================================== */
/* ================================================================== */
/* ================================================================== */
/* OAHWND: the automation-compatible window-handle alias the IVideoWindow
 * pages print (the DShow IDL spells it as a 32-bit long; on CE that is
 * the same width as HWND).  Own design, ABI-safe. */
typedef LONG OAHWND;

/* ================================================================== */
/* Parameter-carrier spellings the M97 vtables reference.  The enum
 * ORDERS/VALUES and the OAFilterState/HEVENT/HSEMAPHORE spellings are
 * R1 (strmif.h) ABI facts (public domain; docs/clean-room.md par.4);
 * the CE pages print the names in the signatures without defining
 * them. */
typedef long OAFilterState;
typedef unsigned int HEVENT;
typedef HANDLE HSEMAPHORE;
typedef IDispatch *LPDISPATCH;
typedef enum tagAMTunerModeType {
    AMTUNER_MODE_DEFAULT = 0x0000,
    AMTUNER_MODE_TV      = 0x0001,
    AMTUNER_MODE_FM_RADIO= 0x0002,
    AMTUNER_MODE_AM_RADIO= 0x0004,
    AMTUNER_MODE_DSS     = 0x0008
} AMTunerModeType;
typedef enum {
    TunerInputCable,                /* R1 order: 0 */
    TunerInputAntenna               /* 1 */
} TunerInputType;

/* M97 vtable adoption -- COM interfaces made callable from C.  Vtable
 * ORDER adopted from R1 (CeGCC-lineage w32api, public
 * domain; docs/clean-room.md par.4 revision 2026-09-10);
 * method names/types are the CE pages' own printed
 * signatures (the records above).  Methods the CE pages do
 * not document but R1 carries are INCLUDED and tagged
 * "(R1)" -- dropping a middle slot would shift the layout.
 * Calling convention: plain function pointers (WINAPI is
 * empty here: CE-wide cdecl; R1's __stdcall NOT adopted). */
/* ================================================================== */

/* ---- IAMStreamConfig: 4 documented method pages; order R1 ---- */
typedef struct IAMStreamConfigVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IAMStreamConfig*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IAMStreamConfig*);  /* (R1) */
    ULONG (WINAPI *Release)(IAMStreamConfig*);  /* (R1) */
    /* IAMStreamConfig */
    HRESULT (WINAPI *SetFormat)(IAMStreamConfig*, AM_MEDIA_TYPE* pmt);  /* 908823 */
    HRESULT (WINAPI *GetFormat)(IAMStreamConfig*, AM_MEDIA_TYPE** pmt);  /* 908804 */
    HRESULT (WINAPI *GetNumberOfCapabilities)(IAMStreamConfig*, int* piCount, int* piSize);  /* 908807 */
    HRESULT (WINAPI *GetStreamCaps)(IAMStreamConfig*, int iIndex, AM_MEDIA_TYPE** pmt, BYTE* pSCC);  /* 908811 */
} IAMStreamConfigVtbl;
struct IAMStreamConfig { const IAMStreamConfigVtbl *lpVtbl; };
#define IAMStreamConfig_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IAMStreamConfig_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IAMStreamConfig_Release(T) ((T)->lpVtbl->Release(T))
#define IAMStreamConfig_SetFormat(T,a) ((T)->lpVtbl->SetFormat(T,a))
#define IAMStreamConfig_GetFormat(T,a) ((T)->lpVtbl->GetFormat(T,a))
#define IAMStreamConfig_GetNumberOfCapabilities(T,a,b) ((T)->lpVtbl->GetNumberOfCapabilities(T,a,b))
#define IAMStreamConfig_GetStreamCaps(T,a,b,c) ((T)->lpVtbl->GetStreamCaps(T,a,b,c))

/* ---- IAMTVTuner: 11 documented method pages; order R1 ---- */
typedef struct IAMTVTunerVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IAMTVTuner*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IAMTVTuner*);  /* (R1) */
    ULONG (WINAPI *Release)(IAMTVTuner*);  /* (R1) */
    /* IAMTVTuner */
    HRESULT (WINAPI *put_Channel)(IAMTVTuner*, long, long, long);  /* (R1) */
    HRESULT (WINAPI *get_Channel)(IAMTVTuner*, long*, long*, long*);  /* (R1) */
    HRESULT (WINAPI *ChannelMinMax)(IAMTVTuner*, long*, long*);  /* (R1) */
    HRESULT (WINAPI *put_CountryCode)(IAMTVTuner*, long);  /* (R1) */
    HRESULT (WINAPI *get_CountryCode)(IAMTVTuner*, long*);  /* (R1) */
    HRESULT (WINAPI *put_TuningSpace)(IAMTVTuner*, long);  /* (R1) */
    HRESULT (WINAPI *get_TuningSpace)(IAMTVTuner*, long*);  /* (R1) */
    HRESULT (WINAPI *Logon)(IAMTVTuner*, HANDLE);  /* (R1) */
    HRESULT (WINAPI *Logout)(IAMTVTuner*);  /* (R1) */
    HRESULT (WINAPI *SignalPresen)(IAMTVTuner*, long*);  /* (R1) */
    HRESULT (WINAPI *put_Mode)(IAMTVTuner*, AMTunerModeType);  /* (R1) */
    HRESULT (WINAPI *get_Mode)(IAMTVTuner*, AMTunerModeType*);  /* (R1) */
    HRESULT (WINAPI *GetAvailableModes)(IAMTVTuner*, long*);  /* (R1) */
    HRESULT (WINAPI *get_AvailableTVFormats)(IAMTVTuner*, long* lAnalogVideoStandard);  /* 452518 */
    HRESULT (WINAPI *get_TVFormat)(IAMTVTuner*, long* plAnalogVideoStandard);  /* 452522 */
    HRESULT (WINAPI *AutoTune)(IAMTVTuner*, long lChannel, long* plFoundSignal);  /* 452516 */
    HRESULT (WINAPI *StoreAutoTune)(IAMTVTuner*);  /* 452527 */
    HRESULT (WINAPI *get_NumInputConnections)(IAMTVTuner*, long* plNumInputConnections);  /* 452521 */
    HRESULT (WINAPI *put_InputType)(IAMTVTuner*, long lIndex, TunerInputType InputType);  /* 452526 */
    HRESULT (WINAPI *get_InputType)(IAMTVTuner*, long lIndex, TunerInputType* pInputType);  /* 452520 */
    HRESULT (WINAPI *put_ConnectInput)(IAMTVTuner*, long lIndex);  /* 452525 */
    HRESULT (WINAPI *get_ConnectInput)(IAMTVTuner*, long* plIndex);  /* 452519 */
    HRESULT (WINAPI *get_VideoFrequency)(IAMTVTuner*, long* lFreq);  /* 452523 */
    HRESULT (WINAPI *get_AudioFrequency)(IAMTVTuner*, long* lFreq);  /* 452517 */
} IAMTVTunerVtbl;
struct IAMTVTuner { const IAMTVTunerVtbl *lpVtbl; };
#define IAMTVTuner_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IAMTVTuner_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IAMTVTuner_Release(T) ((T)->lpVtbl->Release(T))
#define IAMTVTuner_put_Channel(T,a,b,c) ((T)->lpVtbl->put_Channel(T,a,b,c))
#define IAMTVTuner_get_Channel(T,a,b,c) ((T)->lpVtbl->get_Channel(T,a,b,c))
#define IAMTVTuner_ChannelMinMax(T,a,b) ((T)->lpVtbl->ChannelMinMax(T,a,b))
#define IAMTVTuner_put_CountryCode(T,a) ((T)->lpVtbl->put_CountryCode(T,a))
#define IAMTVTuner_get_CountryCode(T,a) ((T)->lpVtbl->get_CountryCode(T,a))
#define IAMTVTuner_put_TuningSpace(T,a) ((T)->lpVtbl->put_TuningSpace(T,a))
#define IAMTVTuner_get_TuningSpace(T,a) ((T)->lpVtbl->get_TuningSpace(T,a))
#define IAMTVTuner_Logon(T,a) ((T)->lpVtbl->Logon(T,a))
#define IAMTVTuner_Logout(T) ((T)->lpVtbl->Logout(T))
#define IAMTVTuner_SignalPresen(T,a) ((T)->lpVtbl->SignalPresen(T,a))
#define IAMTVTuner_put_Mode(T,a) ((T)->lpVtbl->put_Mode(T,a))
#define IAMTVTuner_get_Mode(T,a) ((T)->lpVtbl->get_Mode(T,a))
#define IAMTVTuner_GetAvailableModes(T,a) ((T)->lpVtbl->GetAvailableModes(T,a))
#define IAMTVTuner_get_AvailableTVFormats(T,a) ((T)->lpVtbl->get_AvailableTVFormats(T,a))
#define IAMTVTuner_get_TVFormat(T,a) ((T)->lpVtbl->get_TVFormat(T,a))
#define IAMTVTuner_AutoTune(T,a,b) ((T)->lpVtbl->AutoTune(T,a,b))
#define IAMTVTuner_StoreAutoTune(T) ((T)->lpVtbl->StoreAutoTune(T))
#define IAMTVTuner_get_NumInputConnections(T,a) ((T)->lpVtbl->get_NumInputConnections(T,a))
#define IAMTVTuner_put_InputType(T,a,b) ((T)->lpVtbl->put_InputType(T,a,b))
#define IAMTVTuner_get_InputType(T,a,b) ((T)->lpVtbl->get_InputType(T,a,b))
#define IAMTVTuner_put_ConnectInput(T,a) ((T)->lpVtbl->put_ConnectInput(T,a))
#define IAMTVTuner_get_ConnectInput(T,a) ((T)->lpVtbl->get_ConnectInput(T,a))
#define IAMTVTuner_get_VideoFrequency(T,a) ((T)->lpVtbl->get_VideoFrequency(T,a))
#define IAMTVTuner_get_AudioFrequency(T,a) ((T)->lpVtbl->get_AudioFrequency(T,a))

/* ---- IBaseFilter: 5 documented method pages; order R1 ---- */
typedef struct IBaseFilterVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IBaseFilter*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IBaseFilter*);  /* (R1) */
    ULONG (WINAPI *Release)(IBaseFilter*);  /* (R1) */
    /* IBaseFilter */
    HRESULT (WINAPI *GetClassID)(IBaseFilter*, CLSID*pClassID);  /* (R1) */
    HRESULT (WINAPI *Stop)(IBaseFilter*);  /* (R1) */
    HRESULT (WINAPI *Pause)(IBaseFilter*);  /* (R1) */
    HRESULT (WINAPI *Run)(IBaseFilter*, REFERENCE_TIME tStart);  /* (R1) */
    HRESULT (WINAPI *GetState)(IBaseFilter*, unsigned long, void*);  /* (R1) */
    HRESULT (WINAPI *SetSyncSource)(IBaseFilter*, struct IReferenceClock*);  /* (R1) */
    HRESULT (WINAPI *GetSyncSource)(IBaseFilter*, struct IReferenceClock**);  /* (R1) */
    HRESULT (WINAPI *EnumPins)(IBaseFilter*, IEnumPins** ppEnum);  /* 939490 */
    HRESULT (WINAPI *FindPin)(IBaseFilter*, LPCWSTR Id, IPin** ppPin);  /* 939495 */
    HRESULT (WINAPI *QueryFilterInfo)(IBaseFilter*, FILTER_INFO* pInfo);  /* 939507 */
    HRESULT (WINAPI *JoinFilterGraph)(IBaseFilter*, IFilterGraph* pGraph, LPCWSTR pName);  /* 939504 */
    HRESULT (WINAPI *QueryVendorInfo)(IBaseFilter*, LPWSTR* pVendorInfo);  /* 939511 */
} IBaseFilterVtbl;
struct IBaseFilter { const IBaseFilterVtbl *lpVtbl; };
#define IBaseFilter_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IBaseFilter_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IBaseFilter_Release(T) ((T)->lpVtbl->Release(T))
#define IBaseFilter_GetClassID(T,a) ((T)->lpVtbl->GetClassID(T,a))
#define IBaseFilter_Stop(T) ((T)->lpVtbl->Stop(T))
#define IBaseFilter_Pause(T) ((T)->lpVtbl->Pause(T))
#define IBaseFilter_Run(T,a) ((T)->lpVtbl->Run(T,a))
#define IBaseFilter_GetState(T,a,b) ((T)->lpVtbl->GetState(T,a,b))
#define IBaseFilter_SetSyncSource(T,a) ((T)->lpVtbl->SetSyncSource(T,a))
#define IBaseFilter_GetSyncSource(T,a) ((T)->lpVtbl->GetSyncSource(T,a))
#define IBaseFilter_EnumPins(T,a) ((T)->lpVtbl->EnumPins(T,a))
#define IBaseFilter_FindPin(T,a,b) ((T)->lpVtbl->FindPin(T,a,b))
#define IBaseFilter_QueryFilterInfo(T,a) ((T)->lpVtbl->QueryFilterInfo(T,a))
#define IBaseFilter_JoinFilterGraph(T,a,b) ((T)->lpVtbl->JoinFilterGraph(T,a,b))
#define IBaseFilter_QueryVendorInfo(T,a) ((T)->lpVtbl->QueryVendorInfo(T,a))

/* ---- IDirectDrawVideo: 16 documented method pages; order R1 ---- */
typedef struct IDirectDrawVideoVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IDirectDrawVideo*, REFIID, LPVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IDirectDrawVideo*);  /* (R1) */
    ULONG (WINAPI *Release)(IDirectDrawVideo*);  /* (R1) */
    /* IDirectDrawVideo */
    HRESULT (WINAPI *CanUseOverlayStretch)(IDirectDrawVideo*, long* UseOverlayStretch);  /* 451769 */
    HRESULT (WINAPI *CanUseScanLine)(IDirectDrawVideo*, long* UseScanLine);  /* 451770 */
    HRESULT (WINAPI *GetCaps)(IDirectDrawVideo*, DDCAPS* pCaps);  /* 451771 */
    HRESULT (WINAPI *GetDirectDraw)(IDirectDrawVideo*, LPDIRECTDRAW* ppDirectDraw);  /* 451772 */
    HRESULT (WINAPI *GetEmulatedCaps)(IDirectDrawVideo*, DDCAPS* pCaps);  /* 451773 */
    HRESULT (WINAPI *GetFourCCCodes)(IDirectDrawVideo*, DWORD* pCount, DWORD* pCodes);  /* 451774 */
    HRESULT (WINAPI *GetSurfaceDesc)(IDirectDrawVideo*, DDSURFACEDESC* pSurfaceDesc);  /* 451775 */
    HRESULT (WINAPI *GetSurfaceType)(IDirectDrawVideo*, DWORD* pSurfaceType);  /* 451776 */
    HRESULT (WINAPI *GetSwitches)(IDirectDrawVideo*, DWORD* pSwitches);  /* 451778 */
    HRESULT (WINAPI *SetDefault)(IDirectDrawVideo*);  /* 451795 */
    HRESULT (WINAPI *SetDirectDraw)(IDirectDrawVideo*, LPDIRECTDRAW pDirectDraw);  /* 451796 */
    HRESULT (WINAPI *SetSwitches)(IDirectDrawVideo*, DWORD pSwitches);  /* 451797 */
    HRESULT (WINAPI *UseOverlayStretch)(IDirectDrawVideo*, long UseOverlayStretch);  /* 451798 */
    HRESULT (WINAPI *UseScanLine)(IDirectDrawVideo*, long UseScanLine);  /* 451799 */
    HRESULT (WINAPI *UseWhenFullScreen)(IDirectDrawVideo*, long UseWhenFullScreen);  /* 451800 */
    HRESULT (WINAPI *WillUseFullScreen)(IDirectDrawVideo*, long* UseWhenFullScreen);  /* 451801 */
} IDirectDrawVideoVtbl;
struct IDirectDrawVideo { const IDirectDrawVideoVtbl *lpVtbl; };
#define IDirectDrawVideo_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IDirectDrawVideo_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IDirectDrawVideo_Release(T) ((T)->lpVtbl->Release(T))
#define IDirectDrawVideo_CanUseOverlayStretch(T,a) ((T)->lpVtbl->CanUseOverlayStretch(T,a))
#define IDirectDrawVideo_CanUseScanLine(T,a) ((T)->lpVtbl->CanUseScanLine(T,a))
#define IDirectDrawVideo_GetCaps(T,a) ((T)->lpVtbl->GetCaps(T,a))
#define IDirectDrawVideo_GetDirectDraw(T,a) ((T)->lpVtbl->GetDirectDraw(T,a))
#define IDirectDrawVideo_GetEmulatedCaps(T,a) ((T)->lpVtbl->GetEmulatedCaps(T,a))
#define IDirectDrawVideo_GetFourCCCodes(T,a,b) ((T)->lpVtbl->GetFourCCCodes(T,a,b))
#define IDirectDrawVideo_GetSurfaceDesc(T,a) ((T)->lpVtbl->GetSurfaceDesc(T,a))
#define IDirectDrawVideo_GetSurfaceType(T,a) ((T)->lpVtbl->GetSurfaceType(T,a))
#define IDirectDrawVideo_GetSwitches(T,a) ((T)->lpVtbl->GetSwitches(T,a))
#define IDirectDrawVideo_SetDefault(T) ((T)->lpVtbl->SetDefault(T))
#define IDirectDrawVideo_SetDirectDraw(T,a) ((T)->lpVtbl->SetDirectDraw(T,a))
#define IDirectDrawVideo_SetSwitches(T,a) ((T)->lpVtbl->SetSwitches(T,a))
#define IDirectDrawVideo_UseOverlayStretch(T,a) ((T)->lpVtbl->UseOverlayStretch(T,a))
#define IDirectDrawVideo_UseScanLine(T,a) ((T)->lpVtbl->UseScanLine(T,a))
#define IDirectDrawVideo_UseWhenFullScreen(T,a) ((T)->lpVtbl->UseWhenFullScreen(T,a))
#define IDirectDrawVideo_WillUseFullScreen(T,a) ((T)->lpVtbl->WillUseFullScreen(T,a))

/* ---- IEnumMediaTypes: 4 documented method pages; order R1 ---- */
typedef struct IEnumMediaTypesVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IEnumMediaTypes*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IEnumMediaTypes*);  /* (R1) */
    ULONG (WINAPI *Release)(IEnumMediaTypes*);  /* (R1) */
    /* IEnumMediaTypes */
    HRESULT (WINAPI *Clone)(IEnumMediaTypes*, IEnumMediaTypes** ppEnum);  /* 910540 */
    HRESULT (WINAPI *Next)(IEnumMediaTypes*, ULONG cMediaTypes, AM_MEDIA_TYPE** ppMediaTypes, ULONG* pcFetched);  /* 910542 */
    HRESULT (WINAPI *Reset)(IEnumMediaTypes*);  /* 910543 */
    HRESULT (WINAPI *Skip)(IEnumMediaTypes*, ULONG cMediaTypes);  /* 910544 */
} IEnumMediaTypesVtbl;
struct IEnumMediaTypes { const IEnumMediaTypesVtbl *lpVtbl; };
#define IEnumMediaTypes_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IEnumMediaTypes_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IEnumMediaTypes_Release(T) ((T)->lpVtbl->Release(T))
#define IEnumMediaTypes_Clone(T,a) ((T)->lpVtbl->Clone(T,a))
#define IEnumMediaTypes_Next(T,a,b,c) ((T)->lpVtbl->Next(T,a,b,c))
#define IEnumMediaTypes_Reset(T) ((T)->lpVtbl->Reset(T))
#define IEnumMediaTypes_Skip(T,a) ((T)->lpVtbl->Skip(T,a))

/* ---- IEnumPins: 4 documented method pages; order R1 ---- */
typedef struct IEnumPinsVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IEnumPins*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IEnumPins*);  /* (R1) */
    ULONG (WINAPI *Release)(IEnumPins*);  /* (R1) */
    /* IEnumPins */
    HRESULT (WINAPI *Clone)(IEnumPins*, IEnumPins** ppEnum);  /* 910545 */
    HRESULT (WINAPI *Next)(IEnumPins*, ULONG cPins, IPin** ppPins, ULONG* pcFetched);  /* 910547 */
    HRESULT (WINAPI *Reset)(IEnumPins*);  /* 910548 */
    HRESULT (WINAPI *Skip)(IEnumPins*, ULONG cPins);  /* 910549 */
} IEnumPinsVtbl;
struct IEnumPins { const IEnumPinsVtbl *lpVtbl; };
#define IEnumPins_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IEnumPins_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IEnumPins_Release(T) ((T)->lpVtbl->Release(T))
#define IEnumPins_Clone(T,a) ((T)->lpVtbl->Clone(T,a))
#define IEnumPins_Next(T,a,b,c) ((T)->lpVtbl->Next(T,a,b,c))
#define IEnumPins_Reset(T) ((T)->lpVtbl->Reset(T))
#define IEnumPins_Skip(T,a) ((T)->lpVtbl->Skip(T,a))

/* ---- IFilterGraph: 8 documented method pages; order R1 ---- */
typedef struct IFilterGraphVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IFilterGraph*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IFilterGraph*);  /* (R1) */
    ULONG (WINAPI *Release)(IFilterGraph*);  /* (R1) */
    /* IFilterGraph */
    HRESULT (WINAPI *AddFilter)(IFilterGraph*, IBaseFilter* pFilter, LPCWSTR pName);  /* 910561 */
    HRESULT (WINAPI *RemoveFilter)(IFilterGraph*, IBaseFilter* pFilter);  /* 910568 */
    HRESULT (WINAPI *EnumFilters)(IFilterGraph*, IEnumFilters** ppEnum);  /* 910564 */
    HRESULT (WINAPI *FindFilterByName)(IFilterGraph*, LPCWSTR pName, IBaseFilter** ppFilter);  /* 910565 */
    HRESULT (WINAPI *ConnectDirect)(IFilterGraph*, IPin* ppinOut, IPin* ppinIn, const AM_MEDIA_TYPE* pmt);  /* 910562 */
    HRESULT (WINAPI *Reconnect)(IFilterGraph*, IPin* ppin);  /* 910567 */
    HRESULT (WINAPI *Disconnect)(IFilterGraph*, IPin* ppin);  /* 910563 */
    HRESULT (WINAPI *SetDefaultSyncSource)(IFilterGraph*);  /* 910569 */
} IFilterGraphVtbl;
struct IFilterGraph { const IFilterGraphVtbl *lpVtbl; };
#define IFilterGraph_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IFilterGraph_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IFilterGraph_Release(T) ((T)->lpVtbl->Release(T))
#define IFilterGraph_AddFilter(T,a,b) ((T)->lpVtbl->AddFilter(T,a,b))
#define IFilterGraph_RemoveFilter(T,a) ((T)->lpVtbl->RemoveFilter(T,a))
#define IFilterGraph_EnumFilters(T,a) ((T)->lpVtbl->EnumFilters(T,a))
#define IFilterGraph_FindFilterByName(T,a,b) ((T)->lpVtbl->FindFilterByName(T,a,b))
#define IFilterGraph_ConnectDirect(T,a,b,c) ((T)->lpVtbl->ConnectDirect(T,a,b,c))
#define IFilterGraph_Reconnect(T,a) ((T)->lpVtbl->Reconnect(T,a))
#define IFilterGraph_Disconnect(T,a) ((T)->lpVtbl->Disconnect(T,a))
#define IFilterGraph_SetDefaultSyncSource(T) ((T)->lpVtbl->SetDefaultSyncSource(T))

/* ---- IGraphBuilder: 5 documented method pages; order R1 ---- */
typedef struct IGraphBuilderVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IGraphBuilder*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IGraphBuilder*);  /* (R1) */
    ULONG (WINAPI *Release)(IGraphBuilder*);  /* (R1) */
    /* IGraphBuilder */
    HRESULT (WINAPI *AddFilter)(IGraphBuilder*, IBaseFilter*, LPCWSTR);  /* (R1) */
    HRESULT (WINAPI *RemoveFilter)(IGraphBuilder*, IBaseFilter*);  /* (R1) */
    HRESULT (WINAPI *EnumFilters)(IGraphBuilder*, struct IEnumFilters**);  /* (R1) */
    HRESULT (WINAPI *FindFilterByName)(IGraphBuilder*, LPCWSTR, IBaseFilter**);  /* (R1) */
    HRESULT (WINAPI *ConnectDirect)(IGraphBuilder*, IPin*, IPin*, const AM_MEDIA_TYPE*);  /* (R1) */
    HRESULT (WINAPI *Reconnect)(IGraphBuilder*, IPin*);  /* (R1) */
    HRESULT (WINAPI *Disconnect)(IGraphBuilder*, IPin*);  /* (R1) */
    HRESULT (WINAPI *SetDefaultSyncSource)(IGraphBuilder*);  /* (R1) */
    HRESULT (WINAPI *Connect)(IGraphBuilder*, IPin* ppinOut, IPin* ppinIn);  /* 910580 */
    HRESULT (WINAPI *Render)(IGraphBuilder*, IPin* ppinOut);  /* 910582 */
    HRESULT (WINAPI *RenderFile)(IGraphBuilder*, LPCWSTR lpwstrFile, LPCWSTR lpwstrPlayList);  /* 910583 */
    HRESULT (WINAPI *AddSourceFilter)(IGraphBuilder*, LPCWSTR lpwstrFileName, LPCWSTR lpwstrFilterName, IBaseFilter** ppFilter);  /* 910579 */
    HRESULT (WINAPI *SetLogFile)(IGraphBuilder*, HANDLE hFile);  /* 910584 */
    HRESULT (WINAPI *Abort)(IGraphBuilder*);  /* (R1) */
    HRESULT (WINAPI *ShouldOperationContinue)(IGraphBuilder*);  /* (R1) */
} IGraphBuilderVtbl;
struct IGraphBuilder { const IGraphBuilderVtbl *lpVtbl; };
#define IGraphBuilder_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IGraphBuilder_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IGraphBuilder_Release(T) ((T)->lpVtbl->Release(T))
#define IGraphBuilder_AddFilter(T,a,b) ((T)->lpVtbl->AddFilter(T,a,b))
#define IGraphBuilder_RemoveFilter(T,a) ((T)->lpVtbl->RemoveFilter(T,a))
#define IGraphBuilder_EnumFilters(T,a) ((T)->lpVtbl->EnumFilters(T,a))
#define IGraphBuilder_FindFilterByName(T,a,b) ((T)->lpVtbl->FindFilterByName(T,a,b))
#define IGraphBuilder_ConnectDirect(T,a,b,c) ((T)->lpVtbl->ConnectDirect(T,a,b,c))
#define IGraphBuilder_Reconnect(T,a) ((T)->lpVtbl->Reconnect(T,a))
#define IGraphBuilder_Disconnect(T,a) ((T)->lpVtbl->Disconnect(T,a))
#define IGraphBuilder_SetDefaultSyncSource(T) ((T)->lpVtbl->SetDefaultSyncSource(T))
#define IGraphBuilder_Connect(T,a,b) ((T)->lpVtbl->Connect(T,a,b))
#define IGraphBuilder_Render(T,a) ((T)->lpVtbl->Render(T,a))
#define IGraphBuilder_RenderFile(T,a,b) ((T)->lpVtbl->RenderFile(T,a,b))
#define IGraphBuilder_AddSourceFilter(T,a,b,c) ((T)->lpVtbl->AddSourceFilter(T,a,b,c))
#define IGraphBuilder_SetLogFile(T,a) ((T)->lpVtbl->SetLogFile(T,a))
#define IGraphBuilder_Abort(T) ((T)->lpVtbl->Abort(T))
#define IGraphBuilder_ShouldOperationContinue(T) ((T)->lpVtbl->ShouldOperationContinue(T))

/* ---- IMediaControl: 7 documented method pages; order R1 ---- */
typedef struct IMediaControlVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IMediaControl*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IMediaControl*);  /* (R1) */
    ULONG (WINAPI *Release)(IMediaControl*);  /* (R1) */
    /* IMediaControl */
    HRESULT (WINAPI *GetTypeInfoCount)(IMediaControl*, UINT*);  /* (R1) */
    HRESULT (WINAPI *GetTypeInfo)(IMediaControl*, UINT, LCID, LPTYPEINFO*);  /* (R1) */
    HRESULT (WINAPI *GetIDsOfNames)(IMediaControl*, REFIID, LPOLESTR*, UINT, LCID, DISPID*);  /* (R1) */
    HRESULT (WINAPI *Invoke)(IMediaControl*, DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*);  /* (R1) */
    HRESULT (WINAPI *Run)(IMediaControl*);  /* 452264 */
    HRESULT (WINAPI *Pause)(IMediaControl*);  /* 452262 */
    HRESULT (WINAPI *Stop)(IMediaControl*);  /* 452265 */
    HRESULT (WINAPI *GetState)(IMediaControl*, LONG msTimeout, OAFilterState* pfs);  /* 452260 */
    HRESULT (WINAPI *RenderFile)(IMediaControl*, BSTR strFilename);  /* 452263 */
    HRESULT (WINAPI *AddSourceFilter)(IMediaControl*, BSTR strFilename, IDispatch** ppUnk);  /* 452259 */
    HRESULT (WINAPI *get_FilterCollection)(IMediaControl*, LPDISPATCH*);  /* (R1) */
    HRESULT (WINAPI *get_RegFilterCollection)(IMediaControl*, LPDISPATCH*);  /* (R1) */
    HRESULT (WINAPI *StopWhenReady)(IMediaControl*);  /* 452266 */
} IMediaControlVtbl;
struct IMediaControl { const IMediaControlVtbl *lpVtbl; };
#define IMediaControl_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IMediaControl_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IMediaControl_Release(T) ((T)->lpVtbl->Release(T))
#define IMediaControl_GetTypeInfoCount(T,a) ((T)->lpVtbl->GetTypeInfoCount(T,a))
#define IMediaControl_GetTypeInfo(T,a,b,c) ((T)->lpVtbl->GetTypeInfo(T,a,b,c))
#define IMediaControl_GetIDsOfNames(T,a,b,c,d,e) ((T)->lpVtbl->GetIDsOfNames(T,a,b,c,d,e))
#define IMediaControl_Invoke(T,a,b,c,d,e,f,g,h) ((T)->lpVtbl->Invoke(T,a,b,c,d,e,f,g,h))
#define IMediaControl_Run(T) ((T)->lpVtbl->Run(T))
#define IMediaControl_Pause(T) ((T)->lpVtbl->Pause(T))
#define IMediaControl_Stop(T) ((T)->lpVtbl->Stop(T))
#define IMediaControl_GetState(T,a,b) ((T)->lpVtbl->GetState(T,a,b))
#define IMediaControl_RenderFile(T,a) ((T)->lpVtbl->RenderFile(T,a))
#define IMediaControl_AddSourceFilter(T,a,b) ((T)->lpVtbl->AddSourceFilter(T,a,b))
#define IMediaControl_get_FilterCollection(T,a) ((T)->lpVtbl->get_FilterCollection(T,a))
#define IMediaControl_get_RegFilterCollection(T,a) ((T)->lpVtbl->get_RegFilterCollection(T,a))
#define IMediaControl_StopWhenReady(T) ((T)->lpVtbl->StopWhenReady(T))

/* ---- IMediaFilter: 6 documented method pages; order R1 ---- */
typedef struct IMediaFilterVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IMediaFilter*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IMediaFilter*);  /* (R1) */
    ULONG (WINAPI *Release)(IMediaFilter*);  /* (R1) */
    /* IMediaFilter */
    HRESULT (WINAPI *Stop)(IMediaFilter*);  /* 931389 */
    HRESULT (WINAPI *Pause)(IMediaFilter*);  /* 931255 */
    HRESULT (WINAPI *Run)(IMediaFilter*, REFERENCE_TIME tStart);  /* 931338 */
    HRESULT (WINAPI *GetState)(IMediaFilter*, DWORD dwMilliSecsTimeout, FILTER_STATE* State);  /* 452284 */
    HRESULT (WINAPI *SetSyncSource)(IMediaFilter*, IReferenceClock* pClock);  /* 931385 */
    HRESULT (WINAPI *GetSyncSource)(IMediaFilter*, IReferenceClock** pClock);  /* 452287 */
} IMediaFilterVtbl;
struct IMediaFilter { const IMediaFilterVtbl *lpVtbl; };
#define IMediaFilter_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IMediaFilter_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IMediaFilter_Release(T) ((T)->lpVtbl->Release(T))
#define IMediaFilter_Stop(T) ((T)->lpVtbl->Stop(T))
#define IMediaFilter_Pause(T) ((T)->lpVtbl->Pause(T))
#define IMediaFilter_Run(T,a) ((T)->lpVtbl->Run(T,a))
#define IMediaFilter_GetState(T,a,b) ((T)->lpVtbl->GetState(T,a,b))
#define IMediaFilter_SetSyncSource(T,a) ((T)->lpVtbl->SetSyncSource(T,a))
#define IMediaFilter_GetSyncSource(T,a) ((T)->lpVtbl->GetSyncSource(T,a))

/* ---- IMediaSample: 16 documented method pages; order R1 ---- */
typedef struct IMediaSampleVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IMediaSample*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IMediaSample*);  /* (R1) */
    ULONG (WINAPI *Release)(IMediaSample*);  /* (R1) */
    /* IMediaSample */
    HRESULT (WINAPI *GetPointer)(IMediaSample*, BYTE** ppBuffer);  /* 911587 */
    HRESULT (WINAPI *GetSize)(IMediaSample*);  /* 911588 */
    HRESULT (WINAPI *GetTime)(IMediaSample*, REFERENCE_TIME* pTimeStart, REFERENCE_TIME* pTimeEnd);  /* 911589 */
    HRESULT (WINAPI *SetTime)(IMediaSample*, REFERENCE_TIME* pTimeStart, REFERENCE_TIME* pTimeEnd);  /* 911600 */
    HRESULT (WINAPI *IsSyncPoint)(IMediaSample*);  /* 911593 */
    HRESULT (WINAPI *SetSyncPoint)(IMediaSample*, BOOL bIsSyncPoint);  /* 911599 */
    HRESULT (WINAPI *IsPreroll)(IMediaSample*);  /* 911592 */
    HRESULT (WINAPI *SetPreroll)(IMediaSample*, BOOL bIsPreroll);  /* 911598 */
    HRESULT (WINAPI *GetActualDataLength)(IMediaSample*);  /* 911584 */
    HRESULT (WINAPI *SetActualDataLength)(IMediaSample*, long lLen);  /* 911594 */
    HRESULT (WINAPI *GetMediaType)(IMediaSample*, AM_MEDIA_TYPE** ppMediaType);  /* 911586 */
    HRESULT (WINAPI *SetMediaType)(IMediaSample*, AM_MEDIA_TYPE* pMediaType);  /* 911597 */
    HRESULT (WINAPI *IsDiscontinuity)(IMediaSample*);  /* 911591 */
    HRESULT (WINAPI *SetDiscontinuity)(IMediaSample*, BOOL bIsDiscontinuity);  /* 911595 */
    HRESULT (WINAPI *GetMediaTime)(IMediaSample*, LONGLONG* pTimeStart, LONGLONG* pTimeEnd);  /* 911585 */
    HRESULT (WINAPI *SetMediaTime)(IMediaSample*, LONGLONG* pTimeStart, LONGLONG* pTimeEnd);  /* 911596 */
} IMediaSampleVtbl;
struct IMediaSample { const IMediaSampleVtbl *lpVtbl; };
#define IMediaSample_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IMediaSample_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IMediaSample_Release(T) ((T)->lpVtbl->Release(T))
#define IMediaSample_GetPointer(T,a) ((T)->lpVtbl->GetPointer(T,a))
#define IMediaSample_GetSize(T) ((T)->lpVtbl->GetSize(T))
#define IMediaSample_GetTime(T,a,b) ((T)->lpVtbl->GetTime(T,a,b))
#define IMediaSample_SetTime(T,a,b) ((T)->lpVtbl->SetTime(T,a,b))
#define IMediaSample_IsSyncPoint(T) ((T)->lpVtbl->IsSyncPoint(T))
#define IMediaSample_SetSyncPoint(T,a) ((T)->lpVtbl->SetSyncPoint(T,a))
#define IMediaSample_IsPreroll(T) ((T)->lpVtbl->IsPreroll(T))
#define IMediaSample_SetPreroll(T,a) ((T)->lpVtbl->SetPreroll(T,a))
#define IMediaSample_GetActualDataLength(T) ((T)->lpVtbl->GetActualDataLength(T))
#define IMediaSample_SetActualDataLength(T,a) ((T)->lpVtbl->SetActualDataLength(T,a))
#define IMediaSample_GetMediaType(T,a) ((T)->lpVtbl->GetMediaType(T,a))
#define IMediaSample_SetMediaType(T,a) ((T)->lpVtbl->SetMediaType(T,a))
#define IMediaSample_IsDiscontinuity(T) ((T)->lpVtbl->IsDiscontinuity(T))
#define IMediaSample_SetDiscontinuity(T,a) ((T)->lpVtbl->SetDiscontinuity(T,a))
#define IMediaSample_GetMediaTime(T,a,b) ((T)->lpVtbl->GetMediaTime(T,a,b))
#define IMediaSample_SetMediaTime(T,a,b) ((T)->lpVtbl->SetMediaTime(T,a,b))

/* ---- IPin: 15 documented method pages; order R1 ---- */
typedef struct IPinVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IPin*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IPin*);  /* (R1) */
    ULONG (WINAPI *Release)(IPin*);  /* (R1) */
    /* IPin */
    HRESULT (WINAPI *Connect)(IPin*, IPin* pReceivePin, const AM_MEDIA_TYPE* pmt);  /* 912252 */
    HRESULT (WINAPI *ReceiveConnection)(IPin*, IPin* pConnector, AM_MEDIA_TYPE* pmt);  /* 931694 */
    HRESULT (WINAPI *Disconnect)(IPin*);  /* 912278 */
    HRESULT (WINAPI *ConnectedTo)(IPin*, IPin** ppPin);  /* 912262 */
    HRESULT (WINAPI *ConnectionMediaType)(IPin*, AM_MEDIA_TYPE* pmt);  /* 912270 */
    HRESULT (WINAPI *QueryPinInfo)(IPin*, PIN_INFO* pInfo);  /* 912352 */
    HRESULT (WINAPI *QueryDirection)(IPin*, PIN_DIRECTION* pPinDir);  /* 912328 */
    HRESULT (WINAPI *QueryId)(IPin*, LPWSTR* Id);  /* 912337 */
    HRESULT (WINAPI *QueryAccept)(IPin*, const AM_MEDIA_TYPE* pmt);  /* 912318 */
    HRESULT (WINAPI *EnumMediaTypes)(IPin*, IEnumMediaTypes** ppEnum);  /* 912300 */
    HRESULT (WINAPI *QueryInternalConnections)(IPin*, IPin** apPin, ULONG* nPin);  /* 912346 */
    HRESULT (WINAPI *EndOfStream)(IPin*);  /* 912294 */
    HRESULT (WINAPI *BeginFlush)(IPin*);  /* 912246 */
    HRESULT (WINAPI *EndFlush)(IPin*);  /* 912286 */
    HRESULT (WINAPI *NewSegment)(IPin*, REFERENCE_TIME tStart, REFERENCE_TIME tStop, double dRate);  /* 912310 */
} IPinVtbl;
struct IPin { const IPinVtbl *lpVtbl; };
#define IPin_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IPin_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IPin_Release(T) ((T)->lpVtbl->Release(T))
#define IPin_Connect(T,a,b) ((T)->lpVtbl->Connect(T,a,b))
#define IPin_ReceiveConnection(T,a,b) ((T)->lpVtbl->ReceiveConnection(T,a,b))
#define IPin_Disconnect(T) ((T)->lpVtbl->Disconnect(T))
#define IPin_ConnectedTo(T,a) ((T)->lpVtbl->ConnectedTo(T,a))
#define IPin_ConnectionMediaType(T,a) ((T)->lpVtbl->ConnectionMediaType(T,a))
#define IPin_QueryPinInfo(T,a) ((T)->lpVtbl->QueryPinInfo(T,a))
#define IPin_QueryDirection(T,a) ((T)->lpVtbl->QueryDirection(T,a))
#define IPin_QueryId(T,a) ((T)->lpVtbl->QueryId(T,a))
#define IPin_QueryAccept(T,a) ((T)->lpVtbl->QueryAccept(T,a))
#define IPin_EnumMediaTypes(T,a) ((T)->lpVtbl->EnumMediaTypes(T,a))
#define IPin_QueryInternalConnections(T,a,b) ((T)->lpVtbl->QueryInternalConnections(T,a,b))
#define IPin_EndOfStream(T) ((T)->lpVtbl->EndOfStream(T))
#define IPin_BeginFlush(T) ((T)->lpVtbl->BeginFlush(T))
#define IPin_EndFlush(T) ((T)->lpVtbl->EndFlush(T))
#define IPin_NewSegment(T,a,b,c) ((T)->lpVtbl->NewSegment(T,a,b,c))

/* ---- IQualProp: 6 documented method pages; order R1 ---- */
typedef struct IQualPropVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IQualProp*, REFIID, LPVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IQualProp*);  /* (R1) */
    ULONG (WINAPI *Release)(IQualProp*);  /* (R1) */
    /* IQualProp */
    HRESULT (WINAPI *get_AvgFrameRate)(IQualProp*, int* piAvgFrameRate);  /* 931726 */
    HRESULT (WINAPI *get_AvgSyncOffset)(IQualProp*, int* piAvg);  /* 931785 */
    HRESULT (WINAPI *get_DevSyncOffset)(IQualProp*, int* piDev);  /* 931794 */
    HRESULT (WINAPI *get_FramesDrawn)(IQualProp*, int* pcFramesDrawn);  /* 931798 */
    HRESULT (WINAPI *get_FramesDroppedInRenderer)(IQualProp*, int* pcFrames);  /* 931799 */
    HRESULT (WINAPI *get_Jitter)(IQualProp*, int* piJitter);  /* 931801 */
} IQualPropVtbl;
struct IQualProp { const IQualPropVtbl *lpVtbl; };
#define IQualProp_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IQualProp_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IQualProp_Release(T) ((T)->lpVtbl->Release(T))
#define IQualProp_get_AvgFrameRate(T,a) ((T)->lpVtbl->get_AvgFrameRate(T,a))
#define IQualProp_get_AvgSyncOffset(T,a) ((T)->lpVtbl->get_AvgSyncOffset(T,a))
#define IQualProp_get_DevSyncOffset(T,a) ((T)->lpVtbl->get_DevSyncOffset(T,a))
#define IQualProp_get_FramesDrawn(T,a) ((T)->lpVtbl->get_FramesDrawn(T,a))
#define IQualProp_get_FramesDroppedInRenderer(T,a) ((T)->lpVtbl->get_FramesDroppedInRenderer(T,a))
#define IQualProp_get_Jitter(T,a) ((T)->lpVtbl->get_Jitter(T,a))

/* ---- IReferenceClock: 4 documented method pages; order R1 ---- */
typedef struct IReferenceClockVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IReferenceClock*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IReferenceClock*);  /* (R1) */
    ULONG (WINAPI *Release)(IReferenceClock*);  /* (R1) */
    /* IReferenceClock */
    HRESULT (WINAPI *GetTime)(IReferenceClock*, REFERENCE_TIME* pTime);  /* 931805 */
    HRESULT (WINAPI *AdviseTime)(IReferenceClock*, REFERENCE_TIME rtBaseTime, REFERENCE_TIME rtStreamTime, HEVENT hEvent, DWORD* pdwAdviseCookie);  /* 931804 */
    HRESULT (WINAPI *AdvisePeriodic)(IReferenceClock*, REFERENCE_TIME rtStartTime, REFERENCE_TIME rtPeriodTime, HSEMAPHORE hSemaphore, DWORD* pdwAdviseCookie);  /* 931803 */
    HRESULT (WINAPI *Unadvise)(IReferenceClock*, DWORD dwAdviseCookie);  /* 931807 */
} IReferenceClockVtbl;
struct IReferenceClock { const IReferenceClockVtbl *lpVtbl; };
#define IReferenceClock_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IReferenceClock_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IReferenceClock_Release(T) ((T)->lpVtbl->Release(T))
#define IReferenceClock_GetTime(T,a) ((T)->lpVtbl->GetTime(T,a))
#define IReferenceClock_AdviseTime(T,a,b,c,d) ((T)->lpVtbl->AdviseTime(T,a,b,c,d))
#define IReferenceClock_AdvisePeriodic(T,a,b,c,d) ((T)->lpVtbl->AdvisePeriodic(T,a,b,c,d))
#define IReferenceClock_Unadvise(T,a) ((T)->lpVtbl->Unadvise(T,a))

/* ---- IVideoWindow: 39 documented method pages; order R1 ---- */
typedef struct IVideoWindowVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IVideoWindow*, REFIID, void**);  /* (R1) */
    ULONG (WINAPI *AddRef)(IVideoWindow*);  /* (R1) */
    ULONG (WINAPI *Release)(IVideoWindow*);  /* (R1) */
    /* IVideoWindow */
    HRESULT (WINAPI *GetTypeInfoCount)(IVideoWindow*, UINT*);  /* (R1) */
    HRESULT (WINAPI *GetTypeInfo)(IVideoWindow*, UINT, LCID, ITypeInfo**);  /* (R1) */
    HRESULT (WINAPI *GetIDsOfNames)(IVideoWindow*, REFIID, LPOLESTR*, UINT, LCID, DISPID*);  /* (R1) */
    HRESULT (WINAPI *Invoke)(IVideoWindow*, DISPID, REFIID, LCID, WORD, void*, VARIANT*, EXCEPINFO*, UINT*);  /* (R1) */
    HRESULT (WINAPI *put_Caption)(IVideoWindow*, BSTR strCaption);  /* 931977 */
    HRESULT (WINAPI *get_Caption)(IVideoWindow*, BSTR* strCaption);  /* 931823 */
    HRESULT (WINAPI *put_WindowStyle)(IVideoWindow*, long WindowStyle);  /* 931988 */
    HRESULT (WINAPI *get_WindowStyle)(IVideoWindow*, long* pWindowStyle);  /* 912561 */
    HRESULT (WINAPI *put_WindowStyleEx)(IVideoWindow*, long pWindowStyleEx);  /* 931989 */
    HRESULT (WINAPI *get_WindowStyleEx)(IVideoWindow*, long* pWindowStyleEx);  /* 931962 */
    HRESULT (WINAPI *put_AutoShow)(IVideoWindow*, long AutoShow);  /* 931974 */
    HRESULT (WINAPI *get_AutoShow)(IVideoWindow*, long* AutoShow);  /* 931820 */
    HRESULT (WINAPI *put_WindowState)(IVideoWindow*, long WindowState);  /* 931987 */
    HRESULT (WINAPI *get_WindowState)(IVideoWindow*, long* WindowState);  /* 912445 */
    HRESULT (WINAPI *put_BackgroundPalette)(IVideoWindow*, long BackgroundPalette);  /* 931975 */
    HRESULT (WINAPI *get_BackgroundPalette)(IVideoWindow*, long* pBackgroundPalette);  /* 931821 */
    HRESULT (WINAPI *put_Visible)(IVideoWindow*, long Visible);  /* 931985 */
    HRESULT (WINAPI *get_Visible)(IVideoWindow*, long* pVisible);  /* 931833 */
    HRESULT (WINAPI *put_Left)(IVideoWindow*, long Left);  /* 931981 */
    HRESULT (WINAPI *get_Left)(IVideoWindow*, long* pLeft);  /* 931826 */
    HRESULT (WINAPI *put_Width)(IVideoWindow*, long Width);  /* 931986 */
    HRESULT (WINAPI *get_Width)(IVideoWindow*, long* pWidth);  /* 931834 */
    HRESULT (WINAPI *put_Top)(IVideoWindow*, long Top);  /* 931984 */
    HRESULT (WINAPI *get_Top)(IVideoWindow*, long* pTop);  /* 931832 */
    HRESULT (WINAPI *put_Height)(IVideoWindow*, long Height);  /* 931979 */
    HRESULT (WINAPI *get_Height)(IVideoWindow*, long* pHeight);  /* 931825 */
    HRESULT (WINAPI *put_Owner)(IVideoWindow*, OAHWND Owner);  /* 931983 */
    HRESULT (WINAPI *get_Owner)(IVideoWindow*, OAHWND* pOwner);  /* 931830 */
    HRESULT (WINAPI *put_MessageDrain)(IVideoWindow*, OAHWND Drain);  /* 931982 */
    HRESULT (WINAPI *get_MessageDrain)(IVideoWindow*, OAHWND* Drain);  /* 931828 */
    HRESULT (WINAPI *get_BorderColor)(IVideoWindow*, long* pColor);  /* 931822 */
    HRESULT (WINAPI *put_BorderColor)(IVideoWindow*, long Color);  /* 931976 */
    HRESULT (WINAPI *get_FullScreenMode)(IVideoWindow*, long* FullScreenMode);  /* 931824 */
    HRESULT (WINAPI *put_FullScreenMode)(IVideoWindow*, long FullScreenMode);  /* 931978 */
    HRESULT (WINAPI *SetWindowForeground)(IVideoWindow*, long Focus);  /* 931990 */
    HRESULT (WINAPI *NotifyOwnerMessage)(IVideoWindow*, long hwnd, long uMsg, long wParam, long lParam);  /* 931972 */
    HRESULT (WINAPI *SetWindowPosition)(IVideoWindow*, long Left, long Top, long Width, long Height);  /* 931991 */
    HRESULT (WINAPI *GetWindowPosition)(IVideoWindow*, long* pLeft, long* pTop, long* pWidth, long* pHeight);  /* 912426 */
    HRESULT (WINAPI *GetMinIdealImageSize)(IVideoWindow*, long* pWidth, long* pHeight);  /* 931829 */
    HRESULT (WINAPI *GetMaxIdealImageSize)(IVideoWindow*, long* pWidth, long* pHeight);  /* 931827 */
    HRESULT (WINAPI *GetRestorePosition)(IVideoWindow*, long* pLeft, long* pTop, long* pWidth, long* pHeight);  /* 931831 */
    HRESULT (WINAPI *HideCursor)(IVideoWindow*, long HideCursor);  /* 931968 */
    HRESULT (WINAPI *IsCursorHidden)(IVideoWindow*, long* CursorHidden);  /* 931970 */
} IVideoWindowVtbl;
struct IVideoWindow { const IVideoWindowVtbl *lpVtbl; };
#define IVideoWindow_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IVideoWindow_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IVideoWindow_Release(T) ((T)->lpVtbl->Release(T))
#define IVideoWindow_GetTypeInfoCount(T,a) ((T)->lpVtbl->GetTypeInfoCount(T,a))
#define IVideoWindow_GetTypeInfo(T,a,b,c) ((T)->lpVtbl->GetTypeInfo(T,a,b,c))
#define IVideoWindow_GetIDsOfNames(T,a,b,c,d,e) ((T)->lpVtbl->GetIDsOfNames(T,a,b,c,d,e))
#define IVideoWindow_Invoke(T,a,b,c,d,e,f,g,h) ((T)->lpVtbl->Invoke(T,a,b,c,d,e,f,g,h))
#define IVideoWindow_put_Caption(T,a) ((T)->lpVtbl->put_Caption(T,a))
#define IVideoWindow_get_Caption(T,a) ((T)->lpVtbl->get_Caption(T,a))
#define IVideoWindow_put_WindowStyle(T,a) ((T)->lpVtbl->put_WindowStyle(T,a))
#define IVideoWindow_get_WindowStyle(T,a) ((T)->lpVtbl->get_WindowStyle(T,a))
#define IVideoWindow_put_WindowStyleEx(T,a) ((T)->lpVtbl->put_WindowStyleEx(T,a))
#define IVideoWindow_get_WindowStyleEx(T,a) ((T)->lpVtbl->get_WindowStyleEx(T,a))
#define IVideoWindow_put_AutoShow(T,a) ((T)->lpVtbl->put_AutoShow(T,a))
#define IVideoWindow_get_AutoShow(T,a) ((T)->lpVtbl->get_AutoShow(T,a))
#define IVideoWindow_put_WindowState(T,a) ((T)->lpVtbl->put_WindowState(T,a))
#define IVideoWindow_get_WindowState(T,a) ((T)->lpVtbl->get_WindowState(T,a))
#define IVideoWindow_put_BackgroundPalette(T,a) ((T)->lpVtbl->put_BackgroundPalette(T,a))
#define IVideoWindow_get_BackgroundPalette(T,a) ((T)->lpVtbl->get_BackgroundPalette(T,a))
#define IVideoWindow_put_Visible(T,a) ((T)->lpVtbl->put_Visible(T,a))
#define IVideoWindow_get_Visible(T,a) ((T)->lpVtbl->get_Visible(T,a))
#define IVideoWindow_put_Left(T,a) ((T)->lpVtbl->put_Left(T,a))
#define IVideoWindow_get_Left(T,a) ((T)->lpVtbl->get_Left(T,a))
#define IVideoWindow_put_Width(T,a) ((T)->lpVtbl->put_Width(T,a))
#define IVideoWindow_get_Width(T,a) ((T)->lpVtbl->get_Width(T,a))
#define IVideoWindow_put_Top(T,a) ((T)->lpVtbl->put_Top(T,a))
#define IVideoWindow_get_Top(T,a) ((T)->lpVtbl->get_Top(T,a))
#define IVideoWindow_put_Height(T,a) ((T)->lpVtbl->put_Height(T,a))
#define IVideoWindow_get_Height(T,a) ((T)->lpVtbl->get_Height(T,a))
#define IVideoWindow_put_Owner(T,a) ((T)->lpVtbl->put_Owner(T,a))
#define IVideoWindow_get_Owner(T,a) ((T)->lpVtbl->get_Owner(T,a))
#define IVideoWindow_put_MessageDrain(T,a) ((T)->lpVtbl->put_MessageDrain(T,a))
#define IVideoWindow_get_MessageDrain(T,a) ((T)->lpVtbl->get_MessageDrain(T,a))
#define IVideoWindow_get_BorderColor(T,a) ((T)->lpVtbl->get_BorderColor(T,a))
#define IVideoWindow_put_BorderColor(T,a) ((T)->lpVtbl->put_BorderColor(T,a))
#define IVideoWindow_get_FullScreenMode(T,a) ((T)->lpVtbl->get_FullScreenMode(T,a))
#define IVideoWindow_put_FullScreenMode(T,a) ((T)->lpVtbl->put_FullScreenMode(T,a))
#define IVideoWindow_SetWindowForeground(T,a) ((T)->lpVtbl->SetWindowForeground(T,a))
#define IVideoWindow_NotifyOwnerMessage(T,a,b,c,d) ((T)->lpVtbl->NotifyOwnerMessage(T,a,b,c,d))
#define IVideoWindow_SetWindowPosition(T,a,b,c,d) ((T)->lpVtbl->SetWindowPosition(T,a,b,c,d))
#define IVideoWindow_GetWindowPosition(T,a,b,c,d) ((T)->lpVtbl->GetWindowPosition(T,a,b,c,d))
#define IVideoWindow_GetMinIdealImageSize(T,a,b) ((T)->lpVtbl->GetMinIdealImageSize(T,a,b))
#define IVideoWindow_GetMaxIdealImageSize(T,a,b) ((T)->lpVtbl->GetMaxIdealImageSize(T,a,b))
#define IVideoWindow_GetRestorePosition(T,a,b,c,d) ((T)->lpVtbl->GetRestorePosition(T,a,b,c,d))
#define IVideoWindow_HideCursor(T,a) ((T)->lpVtbl->HideCursor(T,a))
#define IVideoWindow_IsCursorHidden(T,a) ((T)->lpVtbl->IsCursorHidden(T,a))

#ifdef __cplusplus
}
#endif

#endif /* AKARI_DSHOW_H */
