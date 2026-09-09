/*
 * dshow.h -- DirectShow core data surface for the Akari API.
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

#include "windef.h"    /* BOOL, DWORD, LONG, WORD, UINT, ULONG, WCHAR,
                          LPWSTR, RECT, SIZE, HANDLE */
#include "winnt.h"     /* GUID, CLSID, LONGLONG, BYTE */
#include "wingdi.h"    /* COLORREF, RGBQUAD, BITMAPINFOHEADER, DIBSECTION,
                          HBITMAP */
#include "objbase.h"   /* IUnknown (opaque forward) */

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

#ifdef __cplusplus
}
#endif

#endif /* AKARI_DSHOW_H */
