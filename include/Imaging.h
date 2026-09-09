/*
 * Imaging.h -- Imaging API types, constants and COM interface records
 * for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs; Graphics and Multimedia Technologies > Graphics > Imaging book,
 * 120 leaves harvested under tools/manifests/imaging.manifest, M64).
 *
 * The CE 5.0 Imaging API is a C++ COM API (CoCreateInstance with
 * CLSID_ImagingFactory, Imaging.h, Imaging.lib).  The CE pages document
 * each interface through its method pages only; no page publishes a
 * vtable layout, so -- following the M44 objbase.h interface-record
 * policy -- each interface is carried as an opaque forward declaration
 * plus a verbatim method-signature record, never as an invented C
 * vtable.  The documented "Link Library: Imaging.lib" rows sit on those
 * METHOD pages (virtual calls, not import-library symbols), so no
 * import-library def is derived from this book (the shobjidl.h
 * "Implementation dependent" precedent).
 *
 * No GUID VALUES are published anywhere in the CE Imaging book (the
 * Imaging GUIDs page aa452249 prints names only and instructs the
 * INITGUID + windows.h include pattern), so every GUID name is held
 * (catalogued below), per the zero-gap policy.
 */

#ifndef AKARI_IMAGING_H
#define AKARI_IMAGING_H

#include "Windef.h"    /* UINT, UINT_PTR, VOID, WCHAR, DWORD, BYTE */
#include "Winnt.h"     /* GUID, FLOAT */
#include "objbase.h"   /* CLSID, IStream, HRESULT */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Imaging Types book (aa452253; three pages).                         */
/* ------------------------------------------------------------------ */

/* ms925572 "ARGB" (Windows CE 5.0 and later; Imaging.h):
 *   typedef DWORD ARGB;  (verbatim print) */
typedef DWORD ARGB;

/* ms932257 "PixelFormat" (Windows CE 5.0 and later; Imaging.h):
 *   typedef INT PixelFormat;  (verbatim print) */
typedef INT PixelFormat;

/* ms932258 "PixelFormatID" (Windows CE 5.0 and later; Imaging.h):
 *   typedef PixelFormat PixelFormatID;  (verbatim print) */
typedef PixelFormat PixelFormatID;

/* ------------------------------------------------------------------ */
/* PROPID -- own-design closure (recorded per the zero-gap policy).    */
/* The CE prints use PROPID as a member/parameter type (ms932269       */
/* PropertyItem "PROPID id"; aa452122/aa452125/aa452126/aa452137       */
/* "PROPID propId") but no CE page and no Learn page publishes the     */
/* underlying typedef (checked: no CE PROPID page; the desktop         */
/* propidl.h pages use the name without printing its typedef).  The    */
/* PropertyTag values the id member carries are printed up to 0x509B   */
/* (ms932271), which requires 32 bits; closure: ULONG (32-bit          */
/* unsigned property identifier).  Replace when an official print      */
/* appears.                                                           */
/* ------------------------------------------------------------------ */
#ifndef PROPID
typedef ULONG PROPID;      /* own-design closure; see note above */
#endif

/* UNALIGNED -- spelling carrier from the ms932269 PropertyItem print  */
/* ("UNALIGNED VOID* value").  No CE page documents its expansion; on  */
/* the 32-bit CE targets it compiles to nothing (no-op qualifier).     */
#ifndef UNALIGNED
#define UNALIGNED
#endif

/* ------------------------------------------------------------------ */
/* ms932026 "MAKEARGB" (Windows CE 5.0 and later; Imaging.h).          */
/* Fully printed macro family (verbatim):                              */
/*   #define ALPHA_SHIFT 24                                            */
/*   #define RED_SHIFT 16                                              */
/*   #define GREEN_SHIFT 8                                             */
/*   #define BLUE_SHIFT 0                                              */
/*   #define ALPHA_MASK ((ARGB) 0xff << ALPHA_SHIFT)                   */
/* ------------------------------------------------------------------ */
#define ALPHA_SHIFT 24
#define RED_SHIFT 16
#define GREEN_SHIFT 8
#define BLUE_SHIFT 0
#define ALPHA_MASK ((ARGB) 0xff << ALPHA_SHIFT)

#define MAKEARGB(a, r, g, b) \
    (((ARGB) ((a) & 0xff) << ALPHA_SHIFT) | \
     ((ARGB) ((r) & 0xff) << RED_SHIFT) | \
     ((ARGB) ((g) & 0xff) << GREEN_SHIFT) | \
     ((ARGB) ((b) & 0xff) << BLUE_SHIFT))

/* ------------------------------------------------------------------ */
/* Imaging Classes book (aa452247; five classes) + Structures          */
/* (aa452252; ImageInfo) + ColorPalette.  All bodies are verbatim CE   */
/* 5.0 prints; the CE 6.0 twins print identical bodies (ee491598       */
/* BitmapData, ee490848 ImageCodecInfo, ee490096 ImageInfo,            */
/* ee490079 ColorPalette, ee491100 PropertyItem, ee491044              */
/* EncoderParameter, ee490672 EncoderParameters -- compared            */
/* token-for-token, identical).  The prints say "class"; the members   */
/* are all public data, so a C struct carries the same layout.         */
/* ------------------------------------------------------------------ */

/* ms925969 "BitmapData" (Windows CE 5.0 and later; Imaging.h):
 *   class BitmapData { public: UINT Width; UINT Height; INT Stride;
 *     PixelFormat PixelFormat; VOID* Scan0; UINT_PTR Reserved;}; */
typedef struct tagBitmapData {
    UINT        Width;
    UINT        Height;
    INT         Stride;
    PixelFormat PixelFormat;
    VOID       *Scan0;
    UINT_PTR    Reserved;
} BitmapData;

/* aa452241 "ImageCodecInfo" (Windows CE 5.0 and later; Imaging.h):
 *   class ImageCodecInfo { public: CLSID Clsid; GUID FormatID;
 *     const WCHAR* CodecName; const WCHAR* DllName;
 *     const WCHAR* FormatDescription; const WCHAR* FilenameExtension;
 *     const WCHAR* MimeType; DWORD Flags; DWORD Version;
 *     DWORD SigCount; DWORD SigSize; const BYTE* SigPattern;
 *     const BYTE* SigMask;}; */
typedef struct tagImageCodecInfo {
    CLSID         Clsid;
    GUID          FormatID;
    const WCHAR  *CodecName;
    const WCHAR  *DllName;
    const WCHAR  *FormatDescription;
    const WCHAR  *FilenameExtension;
    const WCHAR  *MimeType;
    DWORD         Flags;
    DWORD         Version;
    DWORD         SigCount;
    DWORD         SigSize;
    const BYTE   *SigPattern;
    const BYTE   *SigMask;
} ImageCodecInfo;

/* aa452243 "ImageInfo (Imaging API)" (Windows CE 5.0 and later;
 * Imaging.h; verbatim print):
 *   typedef struct tagImageInfo { GUID RawDataFormat;
 *     PixelFormatID PixelFormat; UINT Width; UINT Height;
 *     UINT TileWidth; UINT TileHeight; double Xdpi; double Ydpi;
 *     UINT Flags;} ImageInfo; */
typedef struct tagImageInfo {
    GUID          RawDataFormat;
    PixelFormatID PixelFormat;
    UINT          Width;
    UINT          Height;
    UINT          TileWidth;
    UINT          TileHeight;
    double        Xdpi;
    double        Ydpi;
    UINT          Flags;
} ImageInfo;

/* ms926775 "ColorPalette" (Windows CE 5.0 and later; Imaging.h):
 *   typedef struct tagColorPalette { UINT Flags; UINT Count;
 *     ARGB Entries[1];} ColorPalette; */
typedef struct tagColorPalette {
    UINT Flags;
    UINT Count;
    ARGB Entries[1];
} ColorPalette;

/* ms932269 "PropertyItem" (Windows CE 5.0 and later; Imaging.h):
 *   class PropertyItem { public: PROPID id; ULONG length; WORD type;
 *     UNALIGNED VOID* value;}; */
typedef struct tagPropertyItem {
    PROPID        id;        /* PROPID: own-design closure (see above) */
    ULONG         length;
    WORD          type;
    UNALIGNED VOID *value;   /* UNALIGNED: spelling carrier (no-op) */
} PropertyItem;

/* aa451679 "EncoderParameter" (Windows CE 5.0 and later; Imaging.h):
 *   class EncoderParameter { public: GUID Guid; ULONG NumberOfValues;
 *     ULONG Type; VOID* Value;}; */
typedef struct tagEncoderParameter {
    GUID   Guid;
    ULONG  NumberOfValues;
    ULONG  Type;
    VOID  *Value;
} EncoderParameter;

/* aa451680 "EncoderParameters" (Windows CE 5.0 and later; Imaging.h):
 *   class EncoderParameters { public: UINT Count;
 *     EncoderParameter Parameter[1];}; */
typedef struct tagEncoderParameters {
    UINT             Count;
    EncoderParameter Parameter[1];
} EncoderParameters;

/* ------------------------------------------------------------------ */
/* Imaging Enumerations book (aa452248; nine pages).  Bodies below     */
/* are verbatim CE 5.0 prints (values printed where shown).            */
/* ------------------------------------------------------------------ */

/* ms936849 "BufferDisposalFlag" (Windows CE 5.0 and later; Imaging.h)
 * -- bare enum body, no initializers printed.  The CE 6.0 twin
 * (ee491040) prints the same bare body; no other official page
 * publishes values for these four names.  The printed body has a
 * unique C reading (default sequential initialization), so the values
 * below are that reading, not an import. */
enum BufferDisposalFlag {
    BufferDisposalFlagNone         = 0,   /* sequential (bare body) */
    BufferDisposalFlagGlobalFree   = 1,
    BufferDisposalFlagCoTaskMemFree= 2,
    BufferDisposalFlagUnmapView    = 3
};

/* aa451570 "DecoderInitFlag" (Windows CE 5.0 and later; Imaging.h)
 * -- values printed. */
enum DecoderInitFlag {
    DecoderInitFlagNone      = 0,
    DecoderInitFlagNoBlock   = 0x0001,
    DecoderInitFlagBuiltIn1st= 0x0002
};

/* aa451681 "EncoderParameterValueType" (Windows CE 5.0 and later;
 * Imaging.h) -- values printed. */
enum EncoderParameterValueType {
    EncoderParameterValueTypeByte          = 1,
    EncoderParameterValueTypeASCII         = 2,
    EncoderParameterValueTypeShort         = 3,
    EncoderParameterValueTypeLong          = 4,
    EncoderParameterValueTypeRational      = 5,
    EncoderParameterValueTypeLongRange     = 6,
    EncoderParameterValueTypeUndefined     = 7,
    EncoderParameterValueTypeRationalRange = 8
};

/* aa451682 "EncoderValue" (Windows CE 5.0 and later; Imaging.h) --
 * bare 25-element enum body, no initializers printed; the CE 6.0 twin
 * (ee490328) prints the same bare body.  Derivation: the printed body
 * has a unique C reading (default sequential initialization); the
 * desktop GDI+ concept page "Using the EncoderValue Enumeration"
 * (learn.microsoft.com, Win32 apps docs) prints the same members in
 * the same order with the explicit values 0..23 (trailing comments),
 * agreeing with the sequential reading of the first 24 CE members.
 * The desktop-only members EncoderValueColorTypeGray and
 * EncoderValueColorTypeRGB are NOT part of the CE body and are not
 * defined here. */
enum EncoderValue {
    EncoderValueColorTypeCMYK             = 0,
    EncoderValueColorTypeYCCK             = 1,
    EncoderValueCompressionLZW            = 2,
    EncoderValueCompressionCCITT3         = 3,
    EncoderValueCompressionCCITT4         = 4,
    EncoderValueCompressionRle            = 5,
    EncoderValueCompressionNone           = 6,
    EncoderValueScanMethodInterlaced      = 7,
    EncoderValueScanMethodNonInterlaced   = 8,
    EncoderValueVersionGif87              = 9,
    EncoderValueVersionGif89              = 10,
    EncoderValueRenderProgressive         = 11,
    EncoderValueRenderNonProgressive      = 12,
    EncoderValueTransformRotate90         = 13,
    EncoderValueTransformRotate180        = 14,
    EncoderValueTransformRotate270        = 15,
    EncoderValueTransformFlipHorizontal   = 16,
    EncoderValueTransformFlipVertical     = 17,
    EncoderValueMultiFrame                = 18,
    EncoderValueLastFrame                 = 19,
    EncoderValueFlush                     = 20,
    EncoderValueFrameDimensionTime        = 21,
    EncoderValueFrameDimensionResolution  = 22,
    EncoderValueFrameDimensionPage        = 23
};

/* aa452239 "ImageCodecFlags" (Windows CE 5.0 and later; Imaging.h)
 * -- values printed. */
enum ImageCodecFlags {
    ImageCodecFlagsEncoder        = 0x00000001,
    ImageCodecFlagsDecoder        = 0x00000002,
    ImageCodecFlagsSupportBitmap  = 0x00000004,
    ImageCodecFlagsSupportVector  = 0x00000008,
    ImageCodecFlagsSeekableEncode = 0x00000010,
    ImageCodecFlagsBlockingDecode = 0x00000020,
    ImageCodecFlagsBuiltin        = 0x00010000,
    ImageCodecFlagsSystem         = 0x00020000,
    ImageCodecFlagsUser           = 0x00040000
};

/* aa452242 "ImageFlags" (Windows CE 5.0 and later; Imaging.h)
 * -- values printed. */
enum ImageFlags {
    ImageFlagsNone              = 0,
    ImageFlagsScalable          = 0x0001,
    ImageFlagsHasAlpha          = 0x0002,
    ImageFlagsHasTranslucent    = 0x0004,
    ImageFlagsPartiallyScalable = 0x0008,
    ImageFlagsColorSpaceRGB     = 0x0010,
    ImageFlagsColorSpaceCMYK    = 0x0020,
    ImageFlagsColorSpaceGRAY    = 0x0040,
    ImageFlagsColorSpaceYCBCR   = 0x0080,
    ImageFlagsColorSpaceYCCK    = 0x0100,
    ImageFlagsHasRealDPI        = 0x1000,
    ImageFlagsHasRealPixelSize  = 0x2000,
    ImageFlagsReadOnly          = 0x00010000,
    ImageFlagsCaching           = 0x00020000,
    ImageFlagsValid             = 0x00030000
};

/* aa452244 "ImageLockMode" (Windows CE 5.0 and later; Imaging.h)
 * -- values printed. */
enum ImageLockMode {
    ImageLockModeRead        = 0x0001,
    ImageLockModeWrite       = 0x0002,
    ImageLockModeUserInputBuf= 0x0004
};

/* ms912048 "InterpolationHint" (Windows CE 5.0 and later; Imaging.h)
 * -- bare enum body, no initializers printed; the CE 6.0 twin
 * (ee490849) prints the same bare body, and no desktop page carries
 * this CE-only enum (the desktop GDI+ InterpolationMode is a different
 * enumeration).  Unique C reading: default sequential. */
enum InterpolationHint {
    InterpolationHintDefault        = 0,
    InterpolationHintNearestNeighbor= 1,
    InterpolationHintBilinear       = 2,
    InterpolationHintAveraging      = 3,
    InterpolationHintBicubic        = 4
};

/* ms932307 "SinkFlags" (Windows CE 5.0 and later; Imaging.h) -- values
 * printed (the first three alias the ImageFlags values). */
enum SinkFlags {
    SinkFlagsScalable        = ImageFlagsScalable,
    SinkFlagsHasAlpha        = ImageFlagsHasAlpha,
    SinkFlagsPartiallyScalable = ImageFlagsPartiallyScalable,
    SinkFlagsTopDown         = 0x00010000,
    SinkFlagsBottomUp        = 0x00020000,
    SinkFlagsFullWidth       = 0x00040000,
    SinkFlagsMultipass       = 0x00080000,
    SinkFlagsComposite       = 0x00100000,
    SinkFlagsWantProps       = 0x00200000
};

/* ------------------------------------------------------------------ */
/* ms932271 "PropertyTag Values" (Windows CE 5.0 and later; Imaging.h). */
/* 217 property tags, every value printed on the page (column "Tag"); */
/* archive-print line-joins were re-parsed entry-by-entry.  The type   */
/* column names PropertyTagType constants, whose own values are NOT    */
/* published anywhere (see held catalogue below).                      */
/* ------------------------------------------------------------------ */
#define PropertyTagArtist                         0x013B
#define PropertyTagBitsPerSample                  0x0102
#define PropertyTagCellHeight                     0x0109
#define PropertyTagCellWidth                      0x0108
#define PropertyTagChrominanceTable               0x5091
#define PropertyTagColorMap                       0x0140
#define PropertyTagColorTransferFunction          0x501A
#define PropertyTagCompression                    0x0103
#define PropertyTagCopyright                      0x8298
#define PropertyTagDateTime                       0x0132
#define PropertyTagDocumentName                   0x010D
#define PropertyTagDotRange                       0x0150
#define PropertyTagEquipMake                      0x010F
#define PropertyTagEquipModel                     0x0110
#define PropertyTagExifAperture                   0x9202
#define PropertyTagExifBrightness                 0x9203
#define PropertyTagExifCfaPattern                 0xA302
#define PropertyTagExifColorSpace                 0xA001
#define PropertyTagExifCompBPP                    0x9102
#define PropertyTagExifCompConfig                 0x9101
#define PropertyTagExifDTDigitized                0x9004
#define PropertyTagExifDTDigSS                    0x9292
#define PropertyTagExifDTOrig                     0x9003
#define PropertyTagExifDTOrigSS                   0x9291
#define PropertyTagExifDTSubsec                   0x9290
#define PropertyTagExifExposureBias               0x9204
#define PropertyTagExifExposureIndex              0xA215
#define PropertyTagExifExposureProg               0x8822
#define PropertyTagExifExposureTime               0x829A
#define PropertyTagExifFileSource                 0xA300
#define PropertyTagExifFlash                      0x9209
#define PropertyTagExifFlashEnergy                0xA20B
#define PropertyTagExifFNumber                    0x829D
#define PropertyTagExifFocalLength                0x920A
#define PropertyTagExifFocalResUnit               0xA210
#define PropertyTagExifFocalXRes                  0xA20E
#define PropertyTagExifFocalYRes                  0xA20F
#define PropertyTagExifFPXVer                     0xA000
#define PropertyTagExifIFD                        0x8769
#define PropertyTagExifInterop                    0xA005
#define PropertyTagExifISOSpeed                   0x8827
#define PropertyTagExifLightSource                0x9208
#define PropertyTagExifMakerNote                  0x927C
#define PropertyTagExifMaxAperture                0x9205
#define PropertyTagExifMeteringMode               0x9207
#define PropertyTagExifOECF                       0x8828
#define PropertyTagExifPixXDim                    0xA002
#define PropertyTagExifPixYDim                    0xA003
#define PropertyTagExifRelatedWav                 0xA004
#define PropertyTagExifSceneType                  0xA301
#define PropertyTagExifSensingMethod              0xA217
#define PropertyTagExifShutterSpeed               0x9201
#define PropertyTagExifSpatialFR                  0xA20C
#define PropertyTagExifSpectralSense              0x8824
#define PropertyTagExifSubjectDist                0x9206
#define PropertyTagExifSubjectLoc                 0xA214
#define PropertyTagExifUserComment                0x9286
#define PropertyTagExifVer                        0x9000
#define PropertyTagExtraSamples                   0x0152
#define PropertyTagFillOrder                      0x010A
#define PropertyTagFrameDelay                     0x5100
#define PropertyTagFreeByteCounts                 0x0121
#define PropertyTagFreeOffset                     0x0120
#define PropertyTagGamma                          0x0301
#define PropertyTagGlobalPalette                  0x5102
#define PropertyTagGpsAltitude                    0x0006
#define PropertyTagGpsAltitudeRef                 0x0005
#define PropertyTagGpsDestBear                    0x0018
#define PropertyTagGpsDestBearRef                 0x0017
#define PropertyTagGpsDestDist                    0x001A
#define PropertyTagGpsDestDistRef                 0x0019
#define PropertyTagGpsDestLat                     0x0014
#define PropertyTagGpsDestLatRef                  0x0013
#define PropertyTagGpsDestLong                    0x0016
#define PropertyTagGpsDestLongRef                 0x0015
#define PropertyTagGpsGpsDop                      0x000B
#define PropertyTagGpsGpsMeasureMode              0x000A
#define PropertyTagGpsGpsSatellites               0x0008
#define PropertyTagGpsGpsStatus                   0x0009
#define PropertyTagGpsGpsTime                     0x0007
#define PropertyTagGpsIFD                         0x8825
#define PropertyTagGpsImgDir                      0x0011
#define PropertyTagGpsImgDirRef                   0x0010
#define PropertyTagGpsLatitude                    0x0002
#define PropertyTagGpsLatitudeRef                 0x0001
#define PropertyTagGpsLongitude                   0x0004
#define PropertyTagGpsLongitudeRef                0x0003
#define PropertyTagGpsMapDatum                    0x0012
#define PropertyTagGpsSpeed                       0x000D
#define PropertyTagGpsSpeedRef                    0x000C
#define PropertyTagGpsTrack                       0x000F
#define PropertyTagGpsTrackRef                    0x000E
#define PropertyTagGpsVer                         0x0000
#define PropertyTagGrayResponseCurve              0x0123
#define PropertyTagGrayResponseUnit               0x0122
#define PropertyTagGridSize                       0x5011
#define PropertyTagHalftoneDegree                 0x500C
#define PropertyTagHalftoneHints                  0x0141
#define PropertyTagHalftoneLPI                    0x500A
#define PropertyTagHalftoneLPIUnit                0x500B
#define PropertyTagHalftoneMisc                   0x500E
#define PropertyTagHalftoneScreen                 0x500F
#define PropertyTagHalftoneShape                  0x500D
#define PropertyTagHostComputer                   0x013C
#define PropertyTagICCProfile                     0x8773
#define PropertyTagICCProfileDescriptor           0x0302
#define PropertyTagImageDescription               0x010E
#define PropertyTagImageHeight                    0x0101
#define PropertyTagImageTitle                     0x0320
#define PropertyTagImageWidth                     0x0100
#define PropertyTagIndexBackground                0x5103
#define PropertyTagIndexTransparent               0x5104
#define PropertyTagInkNames                       0x014D
#define PropertyTagInkSet                         0x014C
#define PropertyTagJPEGACTables                   0x0209
#define PropertyTagJPEGDCTables                   0x0208
#define PropertyTagJPEGInterFormat                0x0201
#define PropertyTagJPEGInterLength                0x0202
#define PropertyTagJPEGLosslessPredictors         0x0205
#define PropertyTagJPEGPointTransforms            0x0206
#define PropertyTagJPEGProc                       0x0200
#define PropertyTagJPEGQTables                    0x0207
#define PropertyTagJPEGQuality                    0x5010
#define PropertyTagJPEGRestartInterval            0x0203
#define PropertyTagLoopCount                      0x5101
#define PropertyTagLuminanceTable                 0x5090
#define PropertyTagMaxSampleValue                 0x0119
#define PropertyTagMinSampleValue                 0x0118
#define PropertyTagNewSubfileType                 0x00FE
#define PropertyTagNumberOfInks                   0x014E
#define PropertyTagOrientation                    0x0112
#define PropertyTagPageName                       0x011D
#define PropertyTagPageNumber                     0x0129
#define PropertyTagPaletteHistogram               0x5113
#define PropertyTagPhotometricInterp              0x0106
#define PropertyTagPixelPerUnitX                  0x5111
#define PropertyTagPixelPerUnitY                  0x5112
#define PropertyTagPixelUnit                      0x5110
#define PropertyTagPlanarConfig                   0x011C
#define PropertyTagPredictor                      0x013D
#define PropertyTagPrimaryChromaticities          0x013F
#define PropertyTagPrintFlags                     0x5005
#define PropertyTagPrintFlagsBleedWidth           0x5008
#define PropertyTagPrintFlagsBleedWidthScale      0x5009
#define PropertyTagPrintFlagsCrop                 0x5007
#define PropertyTagPrintFlagsVersion              0x5006
#define PropertyTagREFBlackWhite                  0x0214
#define PropertyTagResolutionUnit                 0x0128
#define PropertyTagResolutionXLengthUnit          0x5003
#define PropertyTagResolutionXUnit                0x5001
#define PropertyTagResolutionYLengthUnit          0x5004
#define PropertyTagResolutionYUnit                0x5002
#define PropertyTagRowsPerStrip                   0x0116
#define PropertyTagSampleFormat                   0x0153
#define PropertyTagSamplesPerPixel                0x0115
#define PropertyTagSMaxSampleValue                0x0155
#define PropertyTagSMinSampleValue                0x0154
#define PropertyTagSoftwareUsed                   0x0131
#define PropertyTagSRGBRenderingIntent            0x0303
#define PropertyTagStripBytesCount                0x0117
#define PropertyTagStripOffsets                   0x0111
#define PropertyTagSubfileType                    0x00FF
#define PropertyTagT4Option                       0x0124
#define PropertyTagT6Option                       0x0125
#define PropertyTagTargetPrinter                  0x0151
#define PropertyTagThreshHolding                  0x0107
#define PropertyTagThumbnailArtist                0x5034
#define PropertyTagThumbnailBitsPerSample         0x5022
#define PropertyTagThumbnailColorDepth            0x5015
#define PropertyTagThumbnailCompressedSize        0x5019
#define PropertyTagThumbnailCompression           0x5023
#define PropertyTagThumbnailCopyRight             0x503B
#define PropertyTagThumbnailData                  0x501B
#define PropertyTagThumbnailDateTime              0x5033
#define PropertyTagThumbnailEquipMake             0x5026
#define PropertyTagThumbnailEquipModel            0x5027
#define PropertyTagThumbnailFormat                0x5012
#define PropertyTagThumbnailHeight                0x5014
#define PropertyTagThumbnailImageDescription      0x5025
#define PropertyTagThumbnailImageHeight           0x5021
#define PropertyTagThumbnailImageWidth            0x5020
#define PropertyTagThumbnailOrientation           0x5029
#define PropertyTagThumbnailPhotometricInterp     0x5024
#define PropertyTagThumbnailPlanarConfig          0x502F
#define PropertyTagThumbnailPlanes                0x5016
#define PropertyTagThumbnailPrimaryChromaticities 0x5036
#define PropertyTagThumbnailRawBytes              0x5017
#define PropertyTagThumbnailRefBlackWhite         0x503A
#define PropertyTagThumbnailResolutionUnit        0x5030
#define PropertyTagThumbnailResolutionX           0x502D
#define PropertyTagThumbnailResolutionY           0x502E
#define PropertyTagThumbnailRowsPerStrip          0x502B
#define PropertyTagThumbnailSamplesPerPixel       0x502A
#define PropertyTagThumbnailSize                  0x5018
#define PropertyTagThumbnailSoftwareUsed          0x5032
#define PropertyTagThumbnailStripBytesCount       0x502C
#define PropertyTagThumbnailStripOffsets          0x5028
#define PropertyTagThumbnailTransferFunction      0x5031
#define PropertyTagThumbnailWhitePoint            0x5035
#define PropertyTagThumbnailWidth                 0x5013
#define PropertyTagThumbnailYCbCrCoefficients     0x5037
#define PropertyTagThumbnailYCbCrPositioning      0x5039
#define PropertyTagThumbnailYCbCrSubsampling      0x5038
#define PropertyTagTileByteCounts                 0x0145
#define PropertyTagTileLength                     0x0143
#define PropertyTagTileOffset                     0x0144
#define PropertyTagTileWidth                      0x0142
#define PropertyTagTransferFunction               0x012D
#define PropertyTagTransferRange                  0x0156
#define PropertyTagWhitePoint                     0x013E
#define PropertyTagXPosition                      0x011E
#define PropertyTagXResolution                    0x011A
#define PropertyTagYCbCrCoefficients              0x0211
#define PropertyTagYCbCrPositioning               0x0213
#define PropertyTagYCbCrSubsampling               0x0212
#define PropertyTagYPosition                      0x011F
#define PropertyTagYResolution                    0x011B

/* ------------------------------------------------------------------ */
/* Held name families (zero-gap policy: names catalogued, values not   */
/* published by any official page -- do not invent).                   */
/* ------------------------------------------------------------------ */

/* ms932270 "PropertyTagType Values" -- eight names, no values on the
 * CE page; the desktop "Image property tag type constants" page
 * (Gdiplusimaging.h) prints the same names with descriptions only.
 *   PropertyTagTypeASCII      null-terminated ASCII string
 *   PropertyTagTypeByte       array of bytes
 *   PropertyTagTypeLong       array of unsigned long (32-bit)
 *   PropertyTagTypeRational   array of unsigned long pairs (fraction)
 *   PropertyTagTypeShort      array of unsigned short (16-bit)
 *   PropertyTagTypeSLONG      array of signed long (32-bit)
 *   PropertyTagTypeSRational  array of signed long pairs (fraction)
 *   PropertyTagTypeUndefined  array of bytes, any data type
 */

/* aa451701 "Error Codes for the Imaging API" -- standard error codes
 * (E_INVALIDARG, E_OUTOFMEMORY, E_NOTIMPL, E_ACCESSDENIED, E_PENDING:
 * names only; the CE Imaging book does not print their values, and
 * this project's winerror.h does not yet carry them) and the
 * Imaging-unique codes, names only:
 *   IMGERR_OBJECTBUSY            IMGERR_NOPALETTE
 *   IMGERR_BADLOCK               IMGERR_BADUNLOCK
 *   IMGERR_NOCONVERSION          IMGERR_CODECNOTFOUND
 *   IMGERR_NOFRAME               IMGERR_ABORT
 *   IMGERR_FAILLOADCODEC         IMGERR_PROPERTYNOTFOUND
 *   IMGERR_PROPERTYNOTSUPPORTED
 */

/* aa452249 "Imaging GUIDs" -- every GUID is a name-only publication
 * (the page instructs the INITGUID + windows.h + imaging.h include
 * pattern and prints NO values):
 *   Image format identifiers: ImageFormatUndefined,
 *     ImageFormatMemoryBMP, ImageFormatBMP, ImageFormatEMF (marked
 *     "Not supported"), ImageFormatWMF (marked "Not supported"),
 *     ImageFormatJPEG, ImageFormatPNG, ImageFormatGIF,
 *     ImageFormatTIFF, ImageFormatEXIF, ImageFormatIcon
 *   Multi-frame dimension identifiers: FrameDimensionTime,
 *     FrameDimensionResolution, FrameDimensionPage
 *   Property set identifiers: FormatIDImageInformation,
 *     FormatIDJpegAppHeaders
 *   Decoder parameter identifiers: DECODER_TRANSCOLOR,
 *     DECODER_TRANSRANGE, DECODER_OUTPUTCHANNEL, DECODER_ICONRES,
 *     DECODER_USEICC
 *   Encoder parameter identifiers: EncoderCompression,
 *     EncoderColorDepth, EncoderScanMethod, EncoderVersion,
 *     EncoderRenderMethod, EncoderQuality, EncoderTransformation,
 *     EncoderLuminanceTable, EncoderChrominanceTable,
 *     EncoderSaveFlag, CodecIImageBytes
 *   aa452202 additionally names CLSID_ImagingFactory (obtain
 *     IImagingFactory via CoCreateInstance with it).
 */

/* ms932259 "PixelFormat Values" -- the nine format-flag names are
 * printed WITHOUT values, so the 16 printed composite definitions
 * (which reference those flags) and PixelFormatMax cannot be given
 * numeric definitions here without inventing the flag values (the
 * desktop gdiplusenums.h PixelFormat page publishes flag values,
 * recorded here for a future on-device readback, but the CE page
 * does not -- WinCE is not Win32).  Held flag names:
 *   PixelFormatIndexed, PixelFormatGDI, PixelFormatAlpha,
 *   PixelFormatPAlpha, PixelFormatExtended, PixelFormatCanonical,
 *   PixelFormatUndefined, PixelFormatDontCare
 * Printed composite definitions (verbatim, in page order; the flags
 * they reference are the held names above):
 *   PixelFormat1bppIndexed    (1 | (1 << 8) | PixelFormatIndexed | PixelFormatGDI)
 *   PixelFormat4bppIndexed    (2 | (4 << 8) | PixelFormatIndexed | PixelFormatGDI)
 *   PixelFormat8bppIndexed    (3 | (8 << 8) | PixelFormatIndexed | PixelFormatGDI)
 *   PixelFormat16bppGrayScale (4 | (16 << 8) | PixelFormatExtended)
 *   PixelFormat16bppRGB555    (5 | (16 << 8) | PixelFormatGDI)
 *   PixelFormat16bppRGB565    (6 | (16 << 8) | PixelFormatGDI)
 *   PixelFormat16bppARGB1555  (7 | (16 << 8) | PixelFormatAlpha | PixelFormatGDI)
 *   PixelFormat24bppRGB       (8 | (24 << 8) | PixelFormatGDI)
 *   PixelFormat32bppRGB       (9 | (32 << 8) | PixelFormatGDI)
 *   PixelFormat32bppARGB      (10 | (32 << 8) | PixelFormatAlpha | PixelFormatGDI | PixelFormatCanonical)
 *   PixelFormat32bppPARGB     (11 | (32 << 8) | PixelFormatAlpha | PixelFormatPAlpha | PixelFormatGDI)
 *   PixelFormat48bppRGB       (12 | (48 << 8) | PixelFormatExtended)
 *   PixelFormat64bppARGB      (13 | (64 << 8) | PixelFormatAlpha | PixelFormatCanonical | PixelFormatExtended)
 *   PixelFormat64bppPARGB     (14 | (64 << 8) | PixelFormatAlpha | PixelFormatPAlpha | PixelFormatExtended)
 *   PixelFormatMax            (the page gives no Definition line; the
 *     remarks say its "underlying value ... can be used literally as
 *     the upper bound of a loop through all the other pixel formats")
 */

/* ------------------------------------------------------------------ */
/* Imaging Interfaces book (aa452250; seven interfaces, 72 method      */
/* pages).  Opaque forward declarations (M44 objbase.h policy: the     */
/* docs publish method signatures, never vtable layouts).             */
/* ------------------------------------------------------------------ */
typedef struct IImagingFactory  IImagingFactory;
typedef struct IImage           IImage;
typedef struct IBitmapImage     IBitmapImage;
typedef struct IBasicBitmapOps  IBasicBitmapOps;
typedef struct IImageDecoder    IImageDecoder;
typedef struct IImageEncoder    IImageEncoder;
typedef struct IImageSink       IImageSink;

/* Auxiliary names that appear inside the published method signatures  */
/* but have no CE 5.0 page of their own (recorded, not declared):      */
/* IPropertySetStorage (BeginDecode newPropSet), the CodecIImageBytes  */
/* encoder parameter GUID (see the held GUID catalogue above).         */
/* IBasicBitmapOps is obtained through IBitmapImage::QueryInterface    */
/* with IID_IBasicBitmapOps (ms939536; the IID_ value is not           */
/* published).  The OPTIONAL qualifier in the signatures below is      */
/* copied verbatim from the prints.                                    */

/* IImagingFactory: documented methods (13 pages; Windows CE 5.0 and
 * later; Imaging.h; Link Library: Imaging.lib).  vtable order is
 * NOT published -- alphabetical record only.
 *   aa452203 CreateBitmapFromBuffer: HRESULT CreateBitmapFromBuffer( BitmapData* bitmapData, IBitmapImage** bitmap);
 *   aa452205 CreateBitmapFromImage: HRESULT CreateBitmapFromImage( IImage* image, OPTIONAL UINT width, OPTIONAL UINT height, OPTIONAL PixelFormatID pixelFormat, InterpolationHint hints, IBitmapImage** bitmap);
 *   aa452207 CreateImageDecoder: HRESULT CreateImageDecoder( IStream* stream, DecoderInitFlag flags, IImageDecoder** decoder);
 *   aa452209 CreateImageEncoderToFile: HRESULT CreateImageEncoderToFile( const CLSID* clsid, const WCHAR* filename, IImageEncoder** encoder);
 *   aa452211 CreateImageEncoderToStream: HRESULT CreateImageEncoderToStream( const CLSID* clsid, IStream* stream, IImageEncoder** encoder);
 *   aa452213 CreateImageFromBuffer: HRESULT CreateImageFromBuffer( const VOID* buf, UINT size, BufferDisposalFlag disposalFlag, IImage** image);
 *   aa452215 CreateImageFromFile: HRESULT CreateImageFromFile( const WCHAR* filename, IImage** image);
 *   aa452217 CreateImageFromStream: HRESULT CreateImageFromStream( IStream* stream, IImage** image);
 *   aa452219 CreateNewBitmap: HRESULT CreateNewBitmap( UINT width, UINT height, PixelFormatID pixelFormat, IBitmapImage** bitmap);
 *   aa452231 GetInstalledDecoders: HRESULT GetInstalledDecoders( UINT* count, ImageCodecInfo** decoders);
 *   aa452233 GetInstalledEncoders: HRESULT GetInstalledEncoders( UINT* count, ImageCodecInfo** encoders);
 *   aa452235 InstallImageCodec: HRESULT InstallImageCodec( const ImageCodecInfo* codecInfo);
 *   aa452237 UninstallImageCodec: HRESULT UninstallImageCodec( const WCHAR* codecName, UINT flags);
 */

/* IImage: documented methods (6 pages; Windows CE 5.0 and
 * later; Imaging.h; Link Library: Imaging.lib).  vtable order is
 * NOT published -- alphabetical record only.
 *   aa452147 Draw: HRESULT Draw( HDC hdc, const RECT* dstRect, OPTIONAL const RECT* srcRect);
 *   aa452166 GetImageInfo: HRESULT GetImageInfo( ImageInfo* imageInfo);
 *   aa452168 GetPhysicalDimension: HRESULT GetPhysicalDimension( SIZE* size);
 *   aa452169 GetThumbnail: HRESULT GetThumbnail( OPTIONAL UINT thumbWidth, OPTIONAL UINT thumbHeight, IImage** thumbImage);
 *   aa452171 PushIntoSink: HRESULT PushIntoSink( IImageSink* sink);
 *   aa452173 SetImageFlags: HRESULT SetImageFlags( UINT flags);
 */

/* IBitmapImage: documented methods (6 pages; Windows CE 5.0 and
 * later; Imaging.h; Link Library: Imaging.lib).  vtable order is
 * NOT published -- alphabetical record only.
 *   ms909009 GetPalette: HRESULT GetPalette( ColorPalette** palette);
 *   ms909061 GetPixelFormatID: HRESULT GetPixelFormatID( PixelFormatID* pixelFormat);
 *   ms909070 GetSize: HRESULT GetSize( SIZE* size);
 *   ms909078 LockBits: HRESULT LockBits( const RECT* rect, UINT flags, PixelFormatID pixelFormat, BitmapData* lockedBitmapData);
 *   ms909089 SetPalette: HRESULT SetPalette( const ColorPalette* palette);
 *   ms909098 UnlockBits: HRESULT UnlockBits( const BitmapData* lockedBitmapData);
 */

/* IBasicBitmapOps: documented methods (7 pages; Windows CE 5.0 and
 * later; Imaging.h; Link Library: Imaging.lib).  vtable order is
 * NOT published -- alphabetical record only.
 *   ms939542 AdjustBrightness: HRESULT AdjustBrightness( FLOAT percent);
 *   ms939545 AdjustContrast: HRESULT AdjustContrast( FLOAT shadow, FLOAT highlight);
 *   ms939546 AdjustGamma: HRESULT AdjustGamma( FLOAT gamma);
 *   ms939547 Clone: HRESULT Clone( OPTIONAL const RECT* rect, IBitmapImage** outbmp, BOOL bNeedCloneProperty);
 *   ms939548 Flip: HRESULT Flip( BOOL flipX, BOOL flipY, IBitmapImage** outbmp);
 *   ms939549 Resize: HRESULT Resize( UINT newWidth, UINT newHeight, PixelFormatID pixelFormat, InterpolationHint hints, IBitmapImage** outbmp);
 *   ms939550 Rotate: HRESULT Rotate( FLOAT angle, InterpolationHint hints, IBitmapImage** outbmp);
 */

/* IImageDecoder: documented methods (21 pages; Windows CE 5.0 and
 * later; Imaging.h; Link Library: Imaging.lib).  vtable order is
 * NOT published -- alphabetical record only.
 *   ms910589 BeginDecode: HRESULT BeginDecode( IImageSink* sink, OPTIONAL IPropertySetStorage* newPropSet);
 *   ms910590 Decode: HRESULT Decode();
 *   ms910591 EndDecode: HRESULT EndDecode( HRESULT statusCode);
 *   ms910592 GetAllPropertyItems: HRESULT GetAllPropertyItems( UINT totalBufferSize, UINT numProperties, PropertyItem* allItems);
 *   aa452112 GetFrameCount: HRESULT GetFrameCount( const GUID* dimensionID, UINT* count);
 *   aa452115 GetFrameDimensionsCount: HRESULT GetFrameDimensionsCount( UINT* count);
 *   aa452116 GetFrameDimensionsList: HRESULT GetFrameDimensionsList( GUID* dimensionIDs, UINT count);
 *   aa452119 GetImageInfo: HRESULT GetImageInfo( ImageInfo* imageInfo);
 *   aa452120 GetPropertyCount: HRESULT GetPropertyCount( UINT* numOfProperty);
 *   aa452122 GetPropertyIdList: HRESULT GetPropertyIdList( UINT numOfProperty, PROPID* list);
 *   aa452125 GetPropertyItem: HRESULT GetPropertyItem( PROPID propId, UINT propSize, PropertyItem* buffer);
 *   aa452126 GetPropertyItemSize: HRESULT GetPropertyItemSize( PROPID propId, UINT* size);
 *   aa452128 GetPropertySize: HRESULT GetPropertySize( UINT* totalBufferSize, UINT* numProperties);
 *   aa452130 GetThumbnail: HRESULT GetThumbnail( OPTIONAL UINT thumbWidth, OPTIONAL UINT thumbHeight, IImage** thumbImage);
 *   aa452133 InitDecoder: HRESULT InitDecoder( IStream* stream, DecoderInitFlag flags);
 *   aa452135 QueryDecoderParam: HRESULT QueryDecoderParam( GUID Guid);
 *   aa452137 RemovePropertyItem: HRESULT RemovePropertyItem( PROPID propId);
 *   aa452139 SelectActiveFrame: HRESULT SelectActiveFrame( const GUID* dimensionID, UINT frameIndex);
 *   aa452141 SetDecoderParam: HRESULT SetDecoderParam( GUID Guid, UINT Length, PVOID Value);
 *   aa452143 SetPropertyItem: HRESULT SetPropertyItem( PropertyItem item);
 *   aa452145 TerminateDecoder: HRESULT TerminateDecoder();
 */

/* IImageEncoder: documented methods (7 pages; Windows CE 5.0 and
 * later; Imaging.h; Link Library: Imaging.lib).  vtable order is
 * NOT published -- alphabetical record only.
 *   aa452155 GetEncodeSink: HRESULT GetEncodeSink( IImageSink** sink);
 *   aa452151 GetEncoderParameterList: HRESULT GetEncoderParameterList( UINT    size, EncoderParameters* Params);
 *   aa452153 GetEncoderParameterListSize: HRESULT GetEncoderParameterListSize( UINT* size);
 *   aa452158 InitEncoder: HRESULT InitEncoder( IStream* stream);
 *   aa452160 SetEncoderParameters: HRESULT SetEncoderParameters( const EncoderParameters* Param);
 *   aa452162 SetFrameDimension: HRESULT SetFrameDimension( const GUID* dimensionID);
 *   aa452164 TerminateEncoder: HRESULT TerminateEncoder();
 */

/* IImageSink: documented methods (12 pages; Windows CE 5.0 and
 * later; Imaging.h; Link Library: Imaging.lib).  vtable order is
 * NOT published -- alphabetical record only.
 *   aa452177 BeginSink: HRESULT BeginSink( ImageInfo* imageInfo, OPTIONAL RECT* subarea);
 *   aa452180 EndSink: HRESULT EndSink( HRESULT statusCode);
 *   aa452182 GetPixelDataBuffer: HRESULT GetPixelDataBuffer( const RECT* rect, PixelFormatID pixelFormat, BOOL lastPass, BitmapData* bitmapData);
 *   aa452184 GetPropertyBuffer: HRESULT GetPropertyBuffer( UINT uiTotalBufferSize, PropertyItem** ppBuffer);
 *   aa452186 NeedRawProperty: HRESULT NeedRawProperty();
 *   aa452188 NeedTransform: HRESULT NeedTransform( UINT* rotation);
 *   aa452190 PushPixelData: HRESULT PushPixelData( const RECT* rect, const BitmapData* bitmapData, BOOL lastPass);
 *   aa452192 PushPropertyItems: HRESULT PushPropertyItems( UINT numOfItems, UINT uiTotalBufferSize, PropertyItem* item);
 *   aa452194 PushRawData: HRESULT PushRawData( const VOID* buffer, UINT bufsize);
 *   aa452196 PushRawInfo: HRESULT PushRawInfo( void* info);
 *   aa452198 ReleasePixelDataBuffer: HRESULT ReleasePixelDataBuffer( const BitmapData* bitmapData);
 *   aa452200 SetPalette: HRESULT SetPalette( const ColorPalette* palette);
 */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_IMAGING_H */
