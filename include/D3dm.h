/*
 * D3dm.h -- Direct3D Mobile types, constants and COM interface records
 * for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs; Graphics and Multimedia Technologies > Graphics > Direct3D Mobile
 * book, 416 leaves harvested under tools/manifests/d3dm.manifest, M67).
 *
 * Requirements rows print "Header: D3dm.h" (API/interfaces/functions +
 * D3DMERR), "D3dmtypes.h" (types/enums/structs/macros) and "D3dmcaps.h"
 * (D3DMCAPS); this file carries the D3dm.h name (the include-compat
 * surface) and everything the book publishes.  The CE D3DM is a C++ COM
 * API: no page publishes a vtable layout, so -- following the M44
 * objbase.h interface-record policy -- each interface is carried as an
 * opaque forward declaration plus verbatim method-signature records.
 *
 * Import surface: the single free function Direct3DMobileCreate has a
 * "Link Library: D3dm.lib" row to itself (def/d3dm-doc.def).  All other
 * D3dm.lib / D3dmguid.lib rows sit on interface/method pages (virtual
 * calls and GUID linkage) and yield no import entries.
 */

#ifndef AKARI_D3DM_H
#define AKARI_D3DM_H

#include "Windef.h"
#include "Winnt.h"     /* GUID, LARGE_INTEGER, TCHAR via windef */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Data types (D3dmtypes.h): verbatim prints.                          */
/* ------------------------------------------------------------------ */

/* ms907756 "D3DMVALUE": typedef signed int D3DMVALUE;  (generic 32-bit
 * value, fixed or floating point) */
typedef signed int D3DMVALUE;

/* ms939142 "D3DMCOLOR": typedef ULONG D3DMCOLOR;  (D3DMFMT_A8R8G8B8) */
typedef ULONG D3DMCOLOR;

/* ------------------------------------------------------------------ */
/* Enumerated types (D3dmtypes.h): verbatim prints, values printed.    */
/* ------------------------------------------------------------------ */

typedef enum _D3DMBACKBUFFER_TYPE {
    D3DMBACKBUFFER_TYPE_MONO = 0,
    D3DMBACKBUFFER_TYPE_FORCE_DWORD = 0x7fffffff
} D3DMBACKBUFFER_TYPE;

typedef enum _D3DMBLEND {
    D3DMBLEND_ZERO = 1,
    D3DMBLEND_ONE = 2,
    D3DMBLEND_SRCCOLOR = 3,
    D3DMBLEND_INVSRCCOLOR = 4,
    D3DMBLEND_SRCALPHA = 5,
    D3DMBLEND_INVSRCALPHA = 6,
    D3DMBLEND_DESTALPHA = 7,
    D3DMBLEND_INVDESTALPHA = 8,
    D3DMBLEND_DESTCOLOR = 9,
    D3DMBLEND_INVDESTCOLOR = 10,
    D3DMBLEND_SRCALPHASAT = 11,
    D3DMBLEND_FORCE_ULONG = 0x7fffffff
} D3DMBLEND;

typedef enum _D3DMBLENDOP {
    D3DMBLENDOP_ADD = 1,
    D3DMBLENDOP_SUBTRACT = 2,
    D3DMBLENDOP_REVSUBTRACT = 3,
    D3DMBLENDOP_MIN = 4,
    D3DMBLENDOP_MAX = 5,
    D3DMBLENDOP_FORCE_ULONG = 0x7fffffff
} D3DMBLENDOP;

typedef enum _D3DMCMPFUNC {
    D3DMCMP_NEVER = 1,
    D3DMCMP_LESS = 2,
    D3DMCMP_EQUAL = 3,
    D3DMCMP_LESSEQUAL = 4,
    D3DMCMP_GREATER = 5,
    D3DMCMP_NOTEQUAL = 6,
    D3DMCMP_GREATEREQUAL = 7,
    D3DMCMP_ALWAYS = 8,
    D3DMCMP_FORCE_ULONG = 0x7fffffff
} D3DMCMPFUNC;

typedef enum _D3DMCULL {
    D3DMCULL_NONE = 1,
    D3DMCULL_CW = 2,
    D3DMCULL_CCW = 3,
    D3DMCULL_FORCE_ULONG = 0x7fffffff
} D3DMCULL;

typedef enum _D3DMDEVTYPE {
    D3DMDEVTYPE_DEFAULT = 0,
    D3DMDEVTYPE_FORCE_ULONG = 0x7fffffff
} D3DMDEVTYPE;

typedef enum _D3DMFILLMODE {
    D3DMFILL_POINT = 1,
    D3DMFILL_WIREFRAME = 2,
    D3DMFILL_SOLID = 3,
    D3DMFILL_FORCE_ULONG = 0x7fffffff
} D3DMFILLMODE;

typedef enum _D3DMFOGMODE {
    D3DMFOG_NONE = 0,
    D3DMFOG_EXP = 1,
    D3DMFOG_EXP2 = 2,
    D3DMFOG_LINEAR = 3,
    D3DMFOG_FORCE_ULONG = 0x7fffffff
} D3DMFOGMODE;

typedef enum _D3DMFORMAT {
    D3DMFMT_UNKNOWN = 0,
    D3DMFMT_R8G8B8 = 1,
    D3DMFMT_A8R8G8B8 = 2,
    D3DMFMT_X8R8G8B8 = 3,
    D3DMFMT_R5G6B5 = 4,
    D3DMFMT_X1R5G5B5 = 5,
    D3DMFMT_A1R5G5B5 = 6,
    D3DMFMT_A4R4G4B4 = 7,
    D3DMFMT_R3G3B2 = 8,
    D3DMFMT_A8R3G3B2 = 9,
    D3DMFMT_X4R4G4B4 = 10,
    D3DMFMT_A8P8 = 11,
    D3DMFMT_P8 = 12,
    D3DMFMT_A8 = 13,
    D3DMFMT_UYVY = 14,
    D3DMFMT_YUY2 = 15,
    D3DMFMT_DXT1 = 16,
    D3DMFMT_DXT2 = 17,
    D3DMFMT_DXT3 = 18,
    D3DMFMT_DXT4 = 19,
    D3DMFMT_DXT5 = 20,
    D3DMFMT_D32 = 21,
    D3DMFMT_D15S1 = 22,
    D3DMFMT_D24S8 = 23,
    D3DMFMT_D16 = 24,
    D3DMFMT_D24X8 = 25,
    D3DMFMT_D24X4S4 = 26,
    D3DMFMT_INDEX16 = 27,
    D3DMFMT_INDEX32 = 28,
    D3DMFMT_VERTEXDATA = 29,
    D3DMFMT_D3DMVALUE_FLOAT = 30,
    D3DMFMT_D3DMVALUE_FIXED = 31,
    D3DMFMT_NUMFORMAT = 32,
    D3DMFMT_FORCE_ULONG = 0xFFFFFFFF
} D3DMFORMAT;

typedef enum _D3DMLIGHTTYPE {
    D3DMLIGHT_POINT = 1,
    D3DMLIGHT_DIRECTIONAL = 3,
    D3DMLIGHT_FORCE_ULONG = 0x7fffffff
} D3DMLIGHTTYPE;

typedef enum _D3DMMATERIALCOLORSOURCE {
    D3DMMCS_MATERIAL = 0,
    D3DMMCS_COLOR1 = 1,
    D3DMMCS_COLOR2 = 2,
    D3DMMCS_FORCE_ULONG = 0x7fffffff
} D3DMMATERIALCOLORSOURCE;

typedef enum _D3DMMULTISAMPLE_TYPE {
    D3DMMULTISAMPLE_NONE = 0,
    D3DMMULTISAMPLE_2_SAMPLES = 2,
    D3DMMULTISAMPLE_3_SAMPLES = 3,
    D3DMMULTISAMPLE_4_SAMPLES = 4,
    D3DMMULTISAMPLE_5_SAMPLES = 5,
    D3DMMULTISAMPLE_6_SAMPLES = 6,
    D3DMMULTISAMPLE_7_SAMPLES = 7,
    D3DMMULTISAMPLE_8_SAMPLES = 8,
    D3DMMULTISAMPLE_9_SAMPLES = 9,
    D3DMMULTISAMPLE_10_SAMPLES = 10,
    D3DMMULTISAMPLE_11_SAMPLES = 11,
    D3DMMULTISAMPLE_12_SAMPLES = 12,
    D3DMMULTISAMPLE_13_SAMPLES = 13,
    D3DMMULTISAMPLE_14_SAMPLES = 14,
    D3DMMULTISAMPLE_15_SAMPLES = 15,
    D3DMMULTISAMPLE_16_SAMPLES = 16,
    D3DMMULTISAMPLE_FORCE_ULONG = 0x7fffffff
} D3DMMULTISAMPLE_TYPE;

typedef enum _D3DMPOOL {
    D3DMPOOL_VIDEOMEM = 0,
    D3DMPOOL_SYSTEMMEM = 1,
    D3DMPOOL_MANAGED = 2,
    D3DMPOOL_FORCE_ULONG = 0x7fffffff
} D3DMPOOL;

typedef enum _D3DMPRIMITIVETYPE {
    D3DMPT_POINTLIST = 1,
    D3DMPT_LINELIST = 2,
    D3DMPT_LINESTRIP = 3,
    D3DMPT_TRIANGLELIST = 4,
    D3DMPT_TRIANGLESTRIP = 5,
    D3DMPT_TRIANGLEFAN = 6,
    D3DMPT_FORCE_ULONG = 0x7fffffff
} D3DMPRIMITIVETYPE;

typedef enum _D3DMPROFILE {
    D3DMPROFILE_BASE = 0,
    D3DMPROFILE_FORCE_DWORD = 0x7fffffff
} D3DMPROFILE;

typedef enum _D3DMRENDERSTATETYPE {
    D3DMRS_FILLMODE = 0,
    D3DMRS_SHADEMODE = 1,
    D3DMRS_ZWRITEENABLE = 2,
    D3DMRS_ALPHATESTENABLE = 3,
    D3DMRS_LASTPIXEL = 4,
    D3DMRS_SRCBLEND = 5,
    D3DMRS_DESTBLEND = 6,
    D3DMRS_CULLMODE = 7,
    D3DMRS_ZFUNC = 8,
    D3DMRS_ALPHAREF = 9,
    D3DMRS_ALPHAFUNC = 10,
    D3DMRS_DITHERENABLE = 11,
    D3DMRS_ALPHABLENDENABLE = 12,
    D3DMRS_FOGENABLE = 13,
    D3DMRS_SPECULARENABLE = 14,
    D3DMRS_FOGCOLOR = 15,
    D3DMRS_FOGTABLEMODE = 16,
    D3DMRS_FOGSTART = 17,
    D3DMRS_FOGEND = 18,
    D3DMRS_FOGDENSITY = 19,
    D3DMRS_DEPTHBIAS = 20,
    D3DMRS_RANGEFOGENABLE = 21,
    D3DMRS_STENCILENABLE = 22,
    D3DMRS_STENCILFAIL = 23,
    D3DMRS_STENCILZFAIL = 24,
    D3DMRS_STENCILPASS = 25,
    D3DMRS_STENCILFUNC = 26,
    D3DMRS_STENCILREF = 27,
    D3DMRS_STENCILMASK = 28,
    D3DMRS_STENCILWRITEMASK = 29,
    D3DMRS_TEXTUREFACTOR = 30,
    D3DMRS_TEXTUREPERSPECTIVE = 31,
    D3DMRS_WRAP0 = 32,
    D3DMRS_WRAP1 = 33,
    D3DMRS_WRAP2 = 34,
    D3DMRS_WRAP3 = 35,
    D3DMRS_CLIPPING = 36,
    D3DMRS_LIGHTING = 37,
    D3DMRS_AMBIENT = 38,
    D3DMRS_FOGVERTEXMODE = 39,
    D3DMRS_COLORVERTEX = 40,
    D3DMRS_LOCALVIEWER = 41,
    D3DMRS_NORMALIZENORMALS = 42,
    D3DMRS_DIFFUSEMATERIALSOURCE = 43,
    D3DMRS_SPECULARMATERIALSOURCE = 44,
    D3DMRS_AMBIENTMATERIALSOURCE = 45,
    D3DMRS_COLORWRITEENABLE = 46,
    D3DMRS_BLENDOP = 47,
    D3DMRS_ZENABLE = 48,
    D3DMRS_SLOPESCALEDEPTHBIAS = 49,
    D3DM_MAXRENDERSTATES = 50,
    D3DMRS_FORCE_ULONG = 0x7fffffff
} D3DMRENDERSTATETYPE;

typedef enum _D3DMRESOURCETYPE {
    D3DMRTYPE_SURFACE = 1,
    D3DMRTYPE_TEXTURE = 3,
    D3DMRTYPE_VERTEXBUFFER = 6,
    D3DMRTYPE_INDEXBUFFER = 7,
    D3DMRTYPE_FORCE_ULONG = 0x7fffffff
} D3DMRESOURCETYPE;

typedef enum _D3DMSHADEMODE {
    D3DMSHADE_FLAT = 1,
    D3DMSHADE_GOURAUD = 2,
    D3DMSHADE_FORCE_ULONG = 0x7fffffff
} D3DMSHADEMODE;

typedef enum _D3DMSTENCILOP {
    D3DMSTENCILOP_KEEP = 1,
    D3DMSTENCILOP_ZERO = 2,
    D3DMSTENCILOP_REPLACE = 3,
    D3DMSTENCILOP_INCRSAT = 4,
    D3DMSTENCILOP_DECRSAT = 5,
    D3DMSTENCILOP_INVERT = 6,
    D3DMSTENCILOP_INCR = 7,
    D3DMSTENCILOP_DECR = 8,
    D3DMSTENCILOP_FORCE_ULONG = 0x7fffffff
} D3DMSTENCILOP;

typedef enum _D3DMSWAPEFFECT {
    D3DMSWAPEFFECT_DISCARD = 1,
    D3DMSWAPEFFECT_FLIP = 2,
    D3DMSWAPEFFECT_COPY = 3,
    D3DMSWAPEFFECT_COPY_VSYNC = 4,
    D3DMSWAPEFFECT_FORCE_ULONG = 0x7fffffff
} D3DMSWAPEFFECT;

typedef enum _D3DMTEXTUREADDRESS {
    D3DMTADDRESS_WRAP = 1,
    D3DMTADDRESS_MIRROR = 2,
    D3DMTADDRESS_CLAMP = 3,
    D3DMTADDRESS_BORDER = 4,
    D3DMTADDRESS_FORCE_ULONG = 0x7fffffff
} D3DMTEXTUREADDRESS;

typedef enum _D3DMTEXTUREFILTERTYPE {
    D3DMTEXF_NONE = 0,
    D3DMTEXF_POINT = 1,
    D3DMTEXF_LINEAR = 2,
    D3DMTEXF_ANISOTROPIC = 3,
    D3DMTEXF_FORCE_ULONG = 0x7fffffff
} D3DMTEXTUREFILTERTYPE;

typedef enum _D3DMTEXTUREOP {
    D3DMTOP_DISABLE = 1,
    D3DMTOP_SELECTARG1 = 2,
    D3DMTOP_SELECTARG2 = 3,
    D3DMTOP_MODULATE = 4,
    D3DMTOP_MODULATE2X = 5,
    D3DMTOP_MODULATE4X = 6,
    D3DMTOP_ADD = 7,
    D3DMTOP_ADDSIGNED = 8,
    D3DMTOP_ADDSIGNED2X = 9,
    D3DMTOP_SUBTRACT = 10,
    D3DMTOP_ADDSMOOTH = 11,
    D3DMTOP_BLENDDIFFUSEALPHA = 12,
    D3DMTOP_BLENDTEXTUREALPHA = 13,
    D3DMTOP_BLENDFACTORALPHA = 14,
    D3DMTOP_BLENDTEXTUREALPHAPM = 15,
    D3DMTOP_BLENDCURRENTALPHA = 16,
    D3DMTOP_PREMODULATE = 17,
    D3DMTOP_MODULATEALPHA_ADDCOLOR = 18,
    D3DMTOP_MODULATECOLOR_ADDALPHA = 19,
    D3DMTOP_MODULATEINVALPHA_ADDCOLOR = 20,
    D3DMTOP_MODULATEINVCOLOR_ADDALPHA = 21,
    D3DMTOP_DOTPRODUCT3 = 24,
    D3DMTOP_MULTIPLYADD = 25,
    D3DMTOP_LERP = 26,
    D3DMTOP_FORCE_ULONG = 0x7fffffff
} D3DMTEXTUREOP;

typedef enum _D3DMTEXTURESTAGESTATETYPE {
    D3DMTSS_COLOROP = 1,
    D3DMTSS_COLORARG1 = 2,
    D3DMTSS_COLORARG2 = 3,
    D3DMTSS_ALPHAOP = 4,
    D3DMTSS_ALPHAARG1 = 5,
    D3DMTSS_ALPHAARG2 = 6,
    D3DMTSS_TEXCOORDINDEX = 7,
    D3DMTSS_ADDRESSU = 8,
    D3DMTSS_ADDRESSV = 9,
    D3DMTSS_BORDERCOLOR = 10,
    D3DMTSS_MAGFILTER = 11,
    D3DMTSS_MINFILTER = 12,
    D3DMTSS_MIPFILTER = 13,
    D3DMTSS_MIPMAPLODBIAS = 14,
    D3DMTSS_MAXMIPLEVEL = 15,
    D3DMTSS_MAXANISOTROPY = 16,
    D3DMTSS_TEXTURETRANSFORMFLAGS = 17,
    D3DMTSS_ADDRESSW = 18,
    D3DMTSS_COLORARG0 = 19,
    D3DMTSS_ALPHAARG0 = 20,
    D3DMTSS_RESULTARG = 21,
    D3DMTSS_MAXTEXTURESTATES = 22,
    D3DMTSS_FORCE_ULONG = 0x7fffffff
} D3DMTEXTURESTAGESTATETYPE;

typedef enum _D3DMTEXTURETRANSFORMFLAGS {
    D3DMTTFF_DISABLE = 0,
    D3DMTTFF_COUNT1 = 1,
    D3DMTTFF_COUNT2 = 2,
    D3DMTTFF_COUNT3 = 3,
    D3DMTTFF_PROJECTED = 256,
    D3DMTTFF_FORCE_ULONG = 0x7fffffff
} D3DMTEXTURETRANSFORMFLAGS;

typedef enum _D3DMTRANSFORMSTATETYPE {
    D3DMTS_WORLD = 0,
    D3DMTS_VIEW = 1,
    D3DMTS_PROJECTION = 2,
    D3DMTS_TEXTURE0 = 3,
    D3DMTS_TEXTURE1 = 4,
    D3DMTS_TEXTURE2 = 5,
    D3DMTS_TEXTURE3 = 6,
    D3DMTS_NUMTRANSFORM = 7,
    D3DMTS_FORCE_ULONG = 0x7fffffff
} D3DMTRANSFORMSTATETYPE;

typedef enum _D3DMZBUFFERTYPE {
    D3DMZB_FALSE = 0,
    D3DMZB_TRUE = 1,
    D3DMZB_USEW = 2,
    D3DMZB_FORCE_DWORD = 0x7fffffff
} D3DMZBUFFERTYPE;

typedef struct _D3DMVECTOR {
    D3DMVALUE x;
    D3DMVALUE y;
    D3DMVALUE z;
} D3DMVECTOR;

/* ------------------------------------------------------------------ */
/* Structures (D3dmtypes.h / D3dmcaps.h): verbatim prints.             */
/* D3DMADAPTER_IDENTIFIER (ms939133) is HELD as a record: its verbatim */
/* print references MAX_DEVICE_IDENTIFIER_STRING, whose value no CE    */
/* page (and no CE 6.0 twin) publishes -- the array cannot be sized    */
/* without inventing it (zero-gap policy).                             */
/*   typedef struct _D3DMADAPTER_IDENTIFIER { TCHAR
 *     Driver[MAX_DEVICE_IDENTIFIER_STRING]; TCHAR
 *     Description[MAX_DEVICE_IDENTIFIER_STRING]; LARGE_INTEGER
 *     DriverVersion; ULONG VendorId; ULONG DeviceId; ULONG SubSysId;
 *     ULONG Revision; GUID DeviceIdentifier;} D3DMADAPTER_IDENTIFIER; */
/* The "Texture Coordinate Formats" concept page (aa451366) prints the
 * CustomVertexFormat example struct (CVF tag); it is an example, not
 * API, and is not compiled.                                          */
/* ------------------------------------------------------------------ */

typedef struct _D3DMCAPS {
    D3DMDEVTYPE DeviceType;
    UINT AdapterOrdinal;
    ULONG PresentationIntervals;
    ULONG DevCaps;
    ULONG SurfaceCaps;
    ULONG PrimitiveMiscCaps;
    ULONG RasterCaps;
    ULONG ZCmpCaps;
    ULONG SrcBlendCaps;
    ULONG DestBlendCaps;
    ULONG BlendOpCaps;
    ULONG AlphaCmpCaps;
    ULONG ShadeCaps;
    ULONG TextureCaps;
    ULONG TextureFilterCaps;
    ULONG TextureAddressCaps;
    ULONG LineCaps;
    ULONG MaxTextureWidth;
    ULONG MaxTextureHeight;
    ULONG MaxTextureRepeat;
    ULONG MaxTextureAspectRatio;
    ULONG MaxAnisotropy;
    D3DMVALUE MaxVertexW;
    LONG GuardBandLeft;
    LONG GuardBandTop;
    LONG GuardBandRight;
    LONG GuardBandBottom;
    D3DMVALUE ExtentsAdjust;
    ULONG StencilCaps;
    ULONG StencilCmpCaps;
    ULONG TextureOpCaps;
    ULONG MaxTextureBlendStages;
    ULONG MaxSimultaneousTextures;
    ULONG VertexProcessingCaps;
    ULONG MaxActiveLights;
    ULONG MaxPrimitiveCount;
    ULONG MaxVertexIndex;
    ULONG NativeCursorWidth;
    ULONG NativeCursorHeight;
    ULONG MaxBackBuffer;
} D3DMCAPS;

typedef struct _D3DMCLIPSTATUS {
    ULONG ClipUnion;
    ULONG ClipIntersection;
} D3DMCLIPSTATUS;

typedef struct _D3DMCOLORVALUE {
    D3DMVALUE r;
    D3DMVALUE g;
    D3DMVALUE b;
    D3DMVALUE a;
} D3DMCOLORVALUE;

typedef struct _D3DMDEVICE_CREATION_PARAMETERS {
    UINT AdapterOrdinal;
    D3DMDEVTYPE DeviceType;
    HWND hFocusWindow;
    ULONG BehaviorFlags;
} D3DMDEVICE_CREATION_PARAMETERS;

typedef struct _D3DMDISPLAYMODE {
    UINT Width;
    UINT Height;
    UINT RefreshRate;
    D3DMFORMAT Format;
} D3DMDISPLAYMODE;

typedef struct _D3DMINDEXBUFFER_DESC {
    D3DMFORMAT Format;
    D3DMRESOURCETYPE Type;
    ULONG Usage;
    D3DMPOOL Pool;
    UINT Size;
} D3DMINDEXBUFFER_DESC;

typedef struct _D3DMLIGHT {
    D3DMLIGHTTYPE Type;
    D3DMCOLORVALUE Diffuse;
    D3DMCOLORVALUE Specular;
    D3DMCOLORVALUE Ambient;
    D3DMVECTOR Position;
    D3DMVECTOR Direction;
    float Range;
    float Attenuation0;
    float Attenuation1;
    float Attenuation2;
} D3DMLIGHT;

typedef struct _D3DMLOCKED_RECT {
    INT Pitch;
    void* pBits;
} D3DMLOCKED_RECT;

typedef struct _D3DMMATERIAL {
    D3DMCOLORVALUE Diffuse;
    D3DMCOLORVALUE Ambient;
    D3DMCOLORVALUE Specular;
    float Power;
} D3DMMATERIAL;

typedef struct _D3DMPRESENT_PARAMETERS_ {
    UINT BackBufferWidth;
    UINT BackBufferHeight;
    D3DMFORMAT BackBufferFormat;
    UINT BackBufferCount;
    D3DMMULTISAMPLE_TYPE MultiSampleType;
    D3DMSWAPEFFECT SwapEffect;
    BOOL Windowed;
    BOOL EnableAutoDepthStencil;
    D3DMFORMAT AutoDepthStencilFormat;
    ULONG Flags;
    UINT FullScreen_PresentationInterval;
} D3DMPRESENT_PARAMETERS;

typedef struct _D3DMSURFACE_DESC {
    D3DMFORMAT Format;
    D3DMRESOURCETYPE Type;
    ULONG Usage;
    D3DMPOOL Pool;
    UINT Size;
    D3DMMULTISAMPLE_TYPE MultiSampleType;
    UINT Width;
    UINT Height;
} D3DMSURFACE_DESC;



typedef struct _D3DMVERTEXBUFFER_DESC {
    D3DMFORMAT Format;
    D3DMRESOURCETYPE Type;
    ULONG Usage;
    D3DMPOOL Pool;
    UINT Size;
    ULONG FVF;
} D3DMVERTEXBUFFER_DESC;

typedef struct _D3DMVIEWPORT {
    ULONG X;
    ULONG Y;
    ULONG Width;
    ULONG Height;
    float MinZ;
    float MaxZ;
} D3DMVIEWPORT;

/* ms907720 "D3DMMATRIX" -- verbatim union print:
 *   typedef struct _D3DMMATRIX { union { struct { D3DMVALUE _11, _12,
 *     _13, _14; D3DMVALUE _21, _22, _23, _24; D3DMVALUE _31, _32, _33,
 *     _34; D3DMVALUE _41, _42, _43, _44; }; D3DMVALUE m[4][4]; };}
 *     D3DMMATRIX;                                                         */
typedef struct _D3DMMATRIX {
    union {
        struct {
            D3DMVALUE _11, _12, _13, _14;
            D3DMVALUE _21, _22, _23, _24;
            D3DMVALUE _31, _32, _33, _34;
            D3DMVALUE _41, _42, _43, _44;
        };
        D3DMVALUE m[4][4];
    };
} D3DMMATRIX;


/* ------------------------------------------------------------------ */
/* ms932027 "MAKE_D3DMHRESULT" + aa451582 "D3DMERR Values"
 * (D3dm.h): verbatim prints.  MAKE_HRESULT itself is not defined by
 * any CE page; the CE print references it, and its expansion is
 * published by the official desktop winerror.h page
 * (learn.microsoft.com nf-winerror-make_hresult) -- added to this
 * project's winerror.h under that grounding (recorded there).
 * ------------------------------------------------------------------ */

#define _FACD3DM 0x877
#define MAKE_D3DMHRESULT(code) MAKE_HRESULT(1, _FACD3DM, code)
#define D3DMERR_ALREADYLOCKED MAKE_D3DMHRESULT(2158)
#define D3DMERR_CONFLICTINGRENDERSTATE MAKE_D3DMHRESULT(2081)
#define D3DMERR_CONFLICTINGTEXTUREFILTER MAKE_D3DMHRESULT(2078)
#define D3DMERR_CONFLICTINGTEXTUREPALETTE MAKE_D3DMHRESULT(2086)
#define D3DMERR_DEVICELOST MAKE_D3DMHRESULT(2152)
#define D3DMERR_DEVICENOTRESET MAKE_D3DMHRESULT(2153)
#define D3DMERR_DRIVERINTERNALERROR MAKE_D3DMHRESULT(2087)
#define D3DMERR_DRIVERINVALIDCALL MAKE_D3DMHRESULT(2157)
#define D3DMERR_DRIVERUNSUPPORTED MAKE_D3DMHRESULT(2088)
#define D3DMERR_INVALIDCALL MAKE_D3DMHRESULT(2156)
#define D3DMERR_INVALIDDEVICE MAKE_D3DMHRESULT(2155)
#define D3DMERR_MEMORYPOOLEMPTY MAKE_D3DMHRESULT(380)
#define D3DMERR_MOREDATA MAKE_D3DMHRESULT(2151)
#define D3DMERR_NOTAVAILABLE MAKE_D3DMHRESULT(2154)
#define D3DMERR_NOTFOUND MAKE_D3DMHRESULT(2150)
#define D3DMERR_TOOMANYOPERATIONS MAKE_D3DMHRESULT(2077)
#define D3DMERR_UNSUPPORTEDALPHAARG MAKE_D3DMHRESULT(2076)
#define D3DMERR_UNSUPPORTEDALPHAOPERATION MAKE_D3DMHRESULT(2075)
#define D3DMERR_UNSUPPORTEDCOLORARG MAKE_D3DMHRESULT(2074)
#define D3DMERR_UNSUPPORTEDCOLOROPERATION MAKE_D3DMHRESULT(2073)
#define D3DMERR_UNSUPPORTEDFACTORVALUE MAKE_D3DMHRESULT(2079)
#define D3DMERR_UNSUPPORTEDTEXTUREFILTER MAKE_D3DMHRESULT(2082)
#define D3DMERR_WRONGTEXTUREFORMAT MAKE_D3DMHRESULT(2072)
/* ------------------------------------------------------------------ */
/* Interfaces (8 overview pages + IDirect3DMobileBaseTexture, which has
 * method pages but no overview page -- dangling, recorded).  Opaque
 * forward declarations (M44 policy).  IDirect3DMobileResource methods
 * apply to the inheriting interfaces (BaseTexture, IndexBuffer,
 * Surface, Texture, VertexBuffer -- ms929153 print).
 * ------------------------------------------------------------------ */
typedef struct IDirect3DMobile              IDirect3DMobile;
typedef struct IDirect3DMobileDevice        IDirect3DMobileDevice;
typedef struct IDirect3DMobileResource      IDirect3DMobileResource;
typedef struct IDirect3DMobileBaseTexture   IDirect3DMobileBaseTexture;
typedef struct IDirect3DMobileSurface       IDirect3DMobileSurface;
typedef struct IDirect3DMobileTexture       IDirect3DMobileTexture;
typedef struct IDirect3DMobileVertexBuffer  IDirect3DMobileVertexBuffer;
typedef struct IDirect3DMobileIndexBuffer   IDirect3DMobileIndexBuffer;
typedef struct IDirect3DMobileSwapChain     IDirect3DMobileSwapChain;

/* ------------------------------------------------------------------ */
/* aa451581 "Direct3DMobileCreate" (Windows CE 5.0 and later; D3dm.h;
 * Link Library: D3dm.lib): the entry point.  SDKVersion takes the
 * D3D_SDK_VERSION value, which no CE page publishes (held; recorded
 * below).  Returns NULL on failure (GetLastError for details).
 * ------------------------------------------------------------------ */
AKARI_CE_IMPORT IDirect3DMobile* WINAPI Direct3DMobileCreate(UINT SDKVersion)
    AKARI_CE_NAME(Direct3DMobileCreate);

/* ------------------------------------------------------------------ */
/* Printed macros (D3dmtypes.h pages), verbatim:
 *   ms939145 D3DMCOLOR_ARGB(a,r,g,b)
 *   ms939146 D3DMCOLOR_RGBA(r,g,b,a) = D3DMCOLOR_ARGB(a,r,g,b)
 *   ms939147 D3DMCOLOR_XRGB(r,g,b)   = D3DMCOLOR_ARGB(0xff,r,g,b)
 *   ms907711 D3DMFVF_TEXCOORDSIZE1/2/3(CoordIndex)  (the SIZE2 and
 *            SIZE3 prints drop the shift factor that SIZE1 prints;
 *            recorded exactly as printed)
 *   ms907709 D3DMFVF_TEXCOORDFIXED(CoordIndex)
 *   ms907710 D3DMFVF_TEXCOORDFLOAT(CoordIndex)
 *   ms907764 D3DM_MAKE_RSVALUE(Value)
 *   ms907738 D3DMRENDERSTATE_WRAPBIAS 32
 * ------------------------------------------------------------------ */
#define D3DMCOLOR_ARGB(a,r,g,b) \
    ((D3DMCOLOR)((((a)&0xff)<<24)|(((r)&0xff)<<16)| \
    (((g)&0xff)<<8)|((b)&0xff)))
#define D3DMCOLOR_RGBA(r,g,b,a) D3DMCOLOR_ARGB(a,r,g,b)
#define D3DMCOLOR_XRGB(r,g,b) D3DMCOLOR_ARGB(0xff,r,g,b)
#define D3DMFVF_TEXCOORDSIZE1(CoordIndex) (D3DMFVF_TEXCOORDCOUNT1 << \
    (CoordIndex*2 + 16))
#define D3DMFVF_TEXCOORDSIZE2(CoordIndex) (D3DMFVF_TEXCOORDCOUNT2)
#define D3DMFVF_TEXCOORDSIZE3(CoordIndex) (D3DMFVF_TEXCOORDCOUNT3 << \
    (CoordIndex*2 + 16))
#define D3DMFVF_TEXCOORDFIXED(CoordIndex) \
    (D3DMFVF_TEXCOORDFORMAT_FIXED << (CoordIndex*2 + 24))
#define D3DMFVF_TEXCOORDFLOAT(CoordIndex) (D3DMFVF_TEXCOORDFORMAT_FLOAT)
#define D3DM_MAKE_RSVALUE(Value) (*(ULONG *)(&(Value)))
#define D3DMRENDERSTATE_WRAPBIAS 32
#define D3DMPV_DONOTCOPYDATA (1 << 0)
#define D3DMPV_VALID D3DMPV_DONOTCOPYDATA

/* ms907763 "D3DM_MAKE_D3DMVALUE": printed as C++ inline overloads
 * (inline D3DMVALUE D3DM_MAKE_D3DMVALUE(D3DMVALUE/float/unsigned int/
 * double Value); compile-time assert when the converted type is not
 * the same size as D3DMVALUE).  Not expressible in C; recorded
 * verbatim, not compiled. */

/* ------------------------------------------------------------------ */
/* Held name families (zero-gap policy: names catalogued on the Values
 * pages, values not published -- do not invent): D3DMCLEAR, D3DMLOCK,
 * D3DMUSAGE, D3DMFVF (incl. the D3DMFVF_TEXCOORDCOUNTn /
 * D3DMFVF_TEXCOORDFORMAT_* names the macros above reference),
 * D3DMCREATE (MULTITHREADED etc.), D3DMPRESENT, D3DMPSHADECAPS,
 * D3DMPBLENDCAPS, D3DMPCMPCAPS, D3DMPMISCCAPS, D3DMPRASTERCAPS,
 * D3DMPTADDRESSCAPS, D3DMPTEXTURECAPS, D3DMPTFILTERCAPS, D3DMSTENCILCAPS,
 * D3DMSURFCAPS, D3DMTEXOPCAPS, D3DMVTXPCAPS, D3DMDEVCAPS, D3DMLINECAPS,
 * D3DMBLENDOPCAPS, D3DMPV (beyond the two printed above),
 * D3DMPRESENTFLAG (LOCKABLE_BACKBUFFER), D3DMTA, D3DMTSS_TCI, D3DMWRAPCOORD,
 * D3DMCS, D3DMCURRENT_DISPLAY_MODE, D3DMADAPTER, D3DMERR (beyond the 23
 * printed codes above), D3DM_DRIVER / D3DM_GETINFO / D3DMRTYPEFLAG /
 * D3DMTSS_TEXTUREOP (driver-side DDI value pages).
 * Interface Identifiers for Direct3D Mobile (ms912040): the IID_
 * GUID names are listed, values are not published (D3dmguid.lib
 * linkage implied).  D3D_SDK_VERSION (aa451581 remark): value not
 * published.  MAX_DEVICE_IDENTIFIER_STRING (ms939133): value not
 * published (holds D3DMADAPTER_IDENTIFIER, above).
 * ------------------------------------------------------------------ */

/* ------------------------------------------------------------------ */
/* Verbatim method-signature records (101 pages; D3dm.h; Link Library:
 * D3dm.lib, D3dmguid.lib).  Vtable layouts are not published.
 * ------------------------------------------------------------------ */

/* IDirect3DMobile: documented methods (14 pages; Windows CE 5.0
 * and later; D3dm.h; Link Library: D3dm.lib, D3dmguid.lib).
 * Vtable layouts are not published; signatures recorded verbatim.
 *   ms909127 CheckDepthStencilMatch: HRESULT CheckDepthStencilMatch( UINT
 *      Adapter, D3DMDEVTYPE DeviceType, D3DMFORMAT AdapterFormat, D3DMFORMAT
 *      RenderTargetFormat, D3DMFORMAT DepthStencilFormat);
 *   ms909128 CheckDeviceFormat: HRESULT CheckDeviceFormat( UINT Adapter,
 *      D3DMDEVTYPE DeviceType, D3DMFORMAT AdapterFormat, ULONG Usage,
 *      D3DMRESOURCETYPE RType, D3DMFORMAT CheckFormat);
 *   ms923411 CheckDeviceFormatConversion: HRESULT
 *      CheckDeviceFormatConversion( UINT Adapter, D3DMDEVTYPE DeviceType,
 *      D3DMFORMAT SourceFormat, D3DMFORMAT DestFormat);
 *   ms909129 CheckDeviceMultiSampleType: HRESULT CheckDeviceMultiSampleType(
 *      UINT Adapter, D3DMDEVTYPE DeviceType, D3DMFORMAT SurfaceFormat, BOOL
 *      Windowed, D3DMMULTISAMPLE_TYPE MultiSampleType);
 *   ms909130 CheckDeviceType: HRESULT CheckDeviceType( UINT Adapter,
 *      D3DMDEVTYPE CheckType, D3DMFORMAT DisplayFormat, D3DMFORMAT
 *      BackBufferFormat, BOOL Windowed);
 *   ms909131 CheckProfile: HRESULT CheckProfile( UINT Adapter, D3DMDEVTYPE
 *      DeviceType, D3DMPROFILE Profile);
 *   ms909132 CreateDevice: HRESULT CreateDevice( UINT Adapter, D3DMDEVTYPE
 *      DeviceType, HWND hFocusWindow, ULONG BehaviorFlags,
 *      D3DMPRESENT_PARAMETERS* pPresentationParameters,
 *      IDirect3DMobileDevice** ppReturnedDeviceInterface);
 *   ms929139 EnumAdapterModes: HRESULT EnumAdapterModes( UINT Adapter, UINT
 *      Mode, D3DMDISPLAYMODE* pMode);
 *   ms929140 GetAdapterCount: UINT GetAdapterCount();
 *   ms929141 GetAdapterDisplayMode: HRESULT GetAdapterDisplayMode( UINT
 *      Adapter, D3DMDISPLAYMODE* pMode);
 *   ms929142 GetAdapterIdentifier: HRESULT GetAdapterIdentifier( UINT
 *      Adapter, ULONG Flags, D3DMADAPTER_IDENTIFIER* pIdentifier);
 *   ms929143 GetAdapterModeCount: UINT GetAdapterModeCount( UINT Adapter);
 *   ms929144 GetDeviceCaps: HRESULT GetDeviceCaps( UINT Adapter, D3DMDEVTYPE
 *      DeviceType, D3DMCAPS* pCaps);
 *   ms929149 RegisterSoftwareDevice: HRESULT RegisterSoftwareDevice( VOID*
 *      pInitializeFunction);
 */

/* IDirect3DMobileBaseTexture: documented methods (3 pages; Windows CE 5.0
 * and later; D3dm.h; Link Library: D3dm.lib, D3dmguid.lib).
 * Vtable layouts are not published; signatures recorded verbatim.
 *   ms909125 GetLOD: DWORD GetLOD();
 *   ms909124 GetLevelCount: DWORD GetLevelCount();
 *   ms909126 SetLOD: DWORD SetLOD( DWORD LODNew);
 */

/* IDirect3DMobileDevice: documented methods (59 pages; Windows CE 5.0
 * and later; D3dm.h; Link Library: D3dm.lib, D3dmguid.lib).
 * Vtable layouts are not published; signatures recorded verbatim.
 *   ms909134 BeginScene: HRESULT BeginScene();
 *   ms909135 Clear: HRESULT Clear( DWORD Count, CONST RECT* pRects, DWORD
 *      Flags, D3DMCOLOR Color, float Z, DWORD Stencil);
 *   ms909136 ColorFill: HRESULT ColorFill( IDirect3DMobileSurface* pSurface,
 *      CONST RECT* pRect, D3DMCOLOR Color);
 *   ms909137 CopyRects: HRESULT CopyRects( IDirect3DMobileSurface*
 *      pSourceSurface, CONST RECT* pSourceRectsArray, UINT cRects,
 *      IDirect3DMobileSurface* pDestinationSurface, CONST POINT*
 *      pDestPointsArray);
 *   ms909138 CreateAdditionalSwapChain: HRESULT CreateAdditionalSwapChain(
 *      D3DMPRESENT_PARAMETERS* pPresentationParameters,
 *      IDirect3DMobileSwapChain** pSwapChain);
 *   ms909139 CreateDepthStencilSurface: HRESULT CreateDepthStencilSurface(
 *      UINT Width, UINT Height, D3DMFORMAT Format, D3DMMULTISAMPLE_TYPE
 *      MultiSample, IDirect3DMobileSurface** ppSurface);
 *   ms909140 CreateImageSurface: HRESULT CreateImageSurface( UINT Width,
 *      UINT Height, D3DMFORMAT Format, IDirect3DMobileSurface** ppSurface);
 *   ms909141 CreateIndexBuffer: HRESULT CreateIndexBuffer( UINT Length,
 *      DWORD Usage, D3DMFORMAT Format, D3DMPOOL Pool,
 *      IDirect3DMobileIndexBuffer** ppIndexBuffer);
 *   ms909142 CreateRenderTarget: HRESULT CreateRenderTarget( UINT Width,
 *      UINT Height, D3DMFORMAT Format, D3DMMULTISAMPLE_TYPE MultiSample,
 *      BOOL Lockable, IDirect3DMobileSurface** ppSurface);
 *   ms909143 CreateTexture: HRESULT CreateTexture( UINT Width, UINT Height,
 *      UINT Levels, DWORD Usage, D3DMFORMAT Format, D3DMPOOL Pool,
 *      IDirect3DMobileTexture** ppTexture);
 *   ms909144 CreateVertexBuffer: HRESULT CreateVertexBuffer( UINT Length,
 *      DWORD Usage, DWORD FVF, D3DMPOOL Pool, IDirect3DMobileVertexBuffer**
 *      ppVertexBuffer);
 *   ms909145 DrawIndexedPrimitive: HRESULT DrawIndexedPrimitive(
 *      D3DMPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT minIndex,
 *      UINT NumVertices, UINT startIndex, UINT primCount);
 *   ms909146 DrawPrimitive: HRESULT DrawPrimitive( D3DMPRIMITIVETYPE
 *      PrimitiveType, UINT StartVertex, UINT PrimitiveCount);
 *   ms929092 EndScene: HRESULT EndScene();
 *   ms929093 GetAvailableTextureMem: UNIT GetAvailableTextureMem();
 *   ms929094 GetBackBuffer: HRESULT GetBackBuffer( UINT BackBuffer,
 *      D3DMBACKBUFFER_TYPE Type, IDirect3DMobileSurface** ppBackBuffer);
 *   ms929095 GetClipStatus: HRESULT GetClipStatus( D3DMCLIPSTATUS*
 *      pClipStatus);
 *   ms929096 GetCreationParameters: HRESULT GetCreationParameters(
 *      D3DMDEVICE_CREATION_PARAMETERS* pParameters);
 *   ms929097 GetCurrentTexturePalette: HRESULT GetCurrentTexturePalette(
 *      UINT* PaletteNumber);
 *   ms929098 GetDepthStencilSurface: HRESULT GetDepthStencilSurface(
 *      IDirect3DMobileSurface** ppZStencilSurface);
 *   ms929099 GetDeviceCaps: HRESULT GetDeviceCaps( D3DMCAPS* pCaps);
 *   ms929100 GetDirect3D: HRESULT GetDirect3D( IDirect3DMobile** ppD3DM);
 *   ms929101 GetDisplayMode: HRESULT GetDisplayMode( D3DMDISPLAYMODE* pMode);
 *   ms929102 GetFrontBuffer: HRESULT GetFrontBuffer(
 *      IDirect3DMobileSurface** pFrontBuffer);
 *   ms929103 GetIndices: HRESULT GetIndices( IDirect3DMobileIndexBuffer**
 *      ppIndexData);
 *   ms929104 GetInfo: HRESULT GetInfo( DWORD DevInfoID, void*
 *      pDevInfoStruct, DWORD DevInfoStructSize);
 *   ms929105 GetLight: HRESULT GetLight( DWORD Index, D3DMLIGHT* pLight,
 *      D3DMFORMAT* pFormat);
 *   ms929106 GetLightEnable: HRESULT GetLightEnable( DWORD Index, BOOL*
 *      pEnable);
 *   ms929107 GetMaterial: HRESULT GetMaterial( D3DMMATERIAL* pMaterial,
 *      D3DMFORMAT* pFormat);
 *   ms929108 GetPaletteEntries: HRESULT GetPaletteEntries( UINT
 *      PaletteNumber, PALETTEENTRY* pEntries);
 *   ms929109 GetRenderState: HRESULT GetRenderState( D3DMRENDERSTATETYPE
 *      State, DWORD* pValue);
 *   ms929110 GetRenderTarget: HRESULT GetRenderTarget(
 *      IDirect3DMobileSurface** ppRenderTarget);
 *   ms929112 GetStreamSource: HRESULT GetStreamSource( UINT StreamNumber,
 *      IDirect3DMobileVertexBuffer** ppStreamData, UINT* pStride);
 *   ms929113 GetTexture: HRESULT GetTexture( DWORD Stage,
 *      IDirect3DMobileBaseTexture** ppTexture);
 *   ms929114 GetTextureStageState: HRESULT GetTextureStageState( DWORD
 *      Stage, D3DMTEXTURESTAGESTATETYPE Type, DWORD* pValue);
 *   ms929115 GetTransform: HRESULT GetTransform( D3DMTRANSFORMSTATETYPE
 *      State, D3DMMATRIX* pMatrix, D3DMFORMAT* pFormat);
 *   ms929116 GetViewport: HRESULT GetViewport( D3DMVIEWPORT* pViewport);
 *   ms929117 LightEnable: HRESULT LightEnable( DWORD Index, BOOL Enable);
 *   ms929118 Present: HRESULT Present( CONST RECT* pSourceRect, CONST RECT*
 *      pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion);
 *   ms929119 ProcessVertices: HRESULT ProcessVertices( UINT SrcStartIndex,
 *      UINT DestIndex, UINT VertexCount, IDirect3DMobileVertexBuffer*
 *      pDestBuffer, DWORD Flags);
 *   ms929120 Reset: HRESULT Reset( D3DMPRESENT_PARAMETERS*
 *      pPresentationParameters);
 *   ms929121 ResourceManagerDiscardBytes: HRESULT
 *      ResourceManagerDiscardBytes( DWORD Bytes);
 *   ms929122 SetClipStatus: HRESULT SetClipStatus( CONST D3DMCLIPSTATUS*
 *      pClipStatus);
 *   ms929123 SetCurrentTexturePalette: HRESULT SetCurrentTexturePalette(
 *      UINT PaletteNumber);
 *   ms929124 SetIndices: HRESULT SetIndices( IDirect3DMobileIndexBuffer*
 *      pIndexData);
 *   ms929125 SetLight: HRESULT SetLight( DWORD Index, CONST D3DMLIGHT*
 *      pLight, D3DMFORMAT Format);
 *   ms929126 SetMaterial: HRESULT SetMaterial( CONST D3DMMATERIAL*
 *      pMaterial, D3DMFORMAT Format);
 *   ms929127 SetPaletteEntries: HRESULT SetPaletteEntries( UINT
 *      PaletteNumber, CONST PALETTEENTRY* pEntries);
 *   ms929128 SetRenderState: HRESULT SetRenderState( D3DMRENDERSTATETYPE
 *      State, DWORD Value);
 *   ms929129 SetRenderTarget: HRESULT SetRenderTarget(
 *      IDirect3DMobileSurface* pRenderTarget, IDirect3DMobileSurface*
 *      pNewZStencil);
 *   ms929130 SetStreamSource: HRESULT SetStreamSource( UINT StreamNumber,
 *      IDirect3DMobileVertexBuffer* pStreamData, UINT Stride);
 *   ms929131 SetTexture: HRESULT SetTexture( DWORD Stage,
 *      IDirect3DMobileBaseTexture* pTexture);
 *   ms929132 SetTextureStageState: HRESULT SetTextureStageState( DWORD
 *      Stage, D3DMTEXTURESTAGESTATETYPE Type, DWORD Value);
 *   ms929133 SetTransform: HRESULT SetTransform( D3DMTRANSFORMSTATETYPE
 *      State, CONST D3DMMATRIX* pMatrix, D3DMFORMAT Format);
 *   ms929134 SetViewport: HRESULT SetViewport( CONST D3DMVIEWPORT*
 *      pViewport);
 *   ms929135 StretchRect: HRESULT StretchRect( IDirect3DMobileSurface*
 *      pSourceSurface, CONST RECT* pSourceRect, IDirect3DMobileSurface*
 *      pDestSurface, CONST RECT* pDestRect, D3DMTEXTUREFILTERTYPE Filter);
 *   ms929136 TestCooperativeLevel: HRESULT TestCooperativeLevel();
 *   ms929137 UpdateTexture: HRESULT UpdateTexture(
 *      IDirect3DMobileBaseTexture* pSourceTexture,
 *      IDirect3DMobileBaseTexture* pDestinationTexture);
 *   ms929138 ValidateDevice: HRESULT ValidateDevice( DWORD* pNumPasses);
 */

/* IDirect3DMobileIndexBuffer: documented methods (3 pages; Windows CE 5.0
 * and later; D3dm.h; Link Library: D3dm.lib, D3dmguid.lib).
 * Vtable layouts are not published; signatures recorded verbatim.
 *   ms929146 GetDesc: HRESULT GetDesc( D3DMINDEXBUFFER_DESC* pDesc);
 *   ms929147 Lock: HRESULT Lock( UINT OffsetToLock, UINT SizeToLock, BYTE**
 *      ppbData, DWORD Flags);
 *   ms929148 Unlock: HRESULT Unlock();
 */

/* IDirect3DMobileResource: documented methods (5 pages; Windows CE 5.0
 * and later; D3dm.h; Link Library: D3dm.lib, D3dmguid.lib).
 * Vtable layouts are not published; signatures recorded verbatim.
 *   ms929151 GetDevice: HRESULT GetDevice( IDirect3DMobileDevice** ppDevice);
 *   ms929152 GetPriority: DWORD GetPriority();
 *   ms929153 GetType: D3DMRESOURCETYPE GetType() PURE;
 *   ms929154 PreLoad: void PreLoad();
 *   ms929155 SetPriority: DWORD SetPriority( DWORD PriorityNew);
 */

/* IDirect3DMobileSurface: documented methods (7 pages; Windows CE 5.0
 * and later; D3dm.h; Link Library: D3dm.lib, D3dmguid.lib).
 * Vtable layouts are not published; signatures recorded verbatim.
 *   ms929511 GetContainer: HRESULT GetContainer( REFIID riid, void**
 *      ppContainer);
 *   ms929619 GetDC: HRESULT GetDC( HDC* phdc);
 *   ms929621 GetDesc: HRESULT GetDesc( D3DMSURFACE_DESC* pDesc);
 *   ms929622 GetDevice: HRESULT GetDevice( IDirect3DMobileDevice** ppDevice);
 *   ms929623 LockRect: HRESULT LockRect( D3DMLOCKED_RECT* pLockedRect, CONST
 *      RECT* pRect, DWORD Flags);
 *   ms929624 ReleaseDC: HRESULT ReleaseDC( HDC hdc);
 *   ms929625 UnlockRect: HRESULT UnlockRect();
 */

/* IDirect3DMobileSwapChain: documented methods (2 pages; Windows CE 5.0
 * and later; D3dm.h; Link Library: D3dm.lib, D3dmguid.lib).
 * Vtable layouts are not published; signatures recorded verbatim.
 *   ms929627 GetBackBuffer: HRESULT GetBackBuffer( UINT BackBuffer,
 *      D3DMBACKBUFFER_TYPE Type, IDirect3DMobileSurface** ppBackBuffer);
 *   ms929628 Present: HRESULT Present( CONST RECT* pSourceRect, CONST RECT*
 *      pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion);
 */

/* IDirect3DMobileTexture: documented methods (5 pages; Windows CE 5.0
 * and later; D3dm.h; Link Library: D3dm.lib, D3dmguid.lib).
 * Vtable layouts are not published; signatures recorded verbatim.
 *   ms929630 AddDirtyRect: HRESULT AddDirtyRect( CONST RECT* pDirtyRect);
 *   ms929631 GetLevelDesc: HRESULT GetLevelDesc( UINT Level,
 *      D3DMSURFACE_DESC* pDesc);
 *   ms929632 GetSurfaceLevel: HRESULT GetSurfaceLevel( UINT Level,
 *      IDirect3DMobileSurface** ppSurfaceLevel);
 *   ms929633 LockRect: HRESULT LockRect( UINT Level, D3DMLOCKED_RECT*
 *      pLockedRect, CONST RECT* pRect, DWORD Flags);
 *   ms929634 UnlockRect: HRESULT UnlockRect( UINT Level);
 */

/* IDirect3DMobileVertexBuffer: documented methods (3 pages; Windows CE 5.0
 * and later; D3dm.h; Link Library: D3dm.lib, D3dmguid.lib).
 * Vtable layouts are not published; signatures recorded verbatim.
 *   ms929636 GetDesc: HRESULT GetDesc( D3DMVERTEXBUFFER_DESC* pDesc);
 *   ms929637 Lock: HRESULT Lock( UINT OffsetToLock, UINT SizeToLock, BYTE**
 *      ppbData, DWORD Flags);
 *   ms929638 Unlock: HRESULT Unlock();
 */
/* ------------------------------------------------------------------
 * Book surface: d3dm (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms907765 D3DM Values (Header: D3dm.h.) */
/* ms939132 D3DMADAPTER Values (Header: D3dm.h.) */
/* aa451582 D3DMERR Values (Header: D3dm.h.) */
/* ms909127 IDirect3DMobile::CheckDepthStencilMatch (Header: D3dm.h.) */
/* ms909128 IDirect3DMobile::CheckDeviceFormat (Header: D3dm.h.) */
/* ms923411 IDirect3DMobile::CheckDeviceFormatConversion (Header: D3dm.h.) */
/* ms909129 IDirect3DMobile::CheckDeviceMultiSampleType (Header: D3dm.h.) */
/* ms909130 IDirect3DMobile::CheckDeviceType (Header: D3dm.h.) */
/* ms909131 IDirect3DMobile::CheckProfile (Header: D3dm.h.) */
/* ms909132 IDirect3DMobile::CreateDevice (Header: D3dm.h.) */
/* ms929139 IDirect3DMobile::EnumAdapterModes (Header: D3dm.h.) */
/* ms929140 IDirect3DMobile::GetAdapterCount (Header: D3dm.h.) */
/* ms929141 IDirect3DMobile::GetAdapterDisplayMode (Header: D3dm.h.) */
/* ms929142 IDirect3DMobile::GetAdapterIdentifier (Header: D3dm.h.) */
/* ms929143 IDirect3DMobile::GetAdapterModeCount (Header: D3dm.h.) */
/* ms929144 IDirect3DMobile::GetDeviceCaps (Header: D3dm.h.) */
/* ms929149 IDirect3DMobile::RegisterSoftwareDevice (Header: D3dm.h.) */
/* ms909124 IDirect3DMobileBaseTexture::GetLevelCount (Header: D3dm.h.) */
/* ms909125 IDirect3DMobileBaseTexture::GetLOD (Header: D3dm.h.) */
/* ms909126 IDirect3DMobileBaseTexture::SetLOD (Header: D3dm.h.) */
/* ms909134 IDirect3DMobileDevice::BeginScene (Header: D3dm.h.) */
/* ms909135 IDirect3DMobileDevice::Clear (Header: D3dm.h.) */
/* ms909136 IDirect3DMobileDevice::ColorFill (Header: D3dm.h.) */
/* ms909137 IDirect3DMobileDevice::CopyRects (Header: D3dm.h.) */
/* ms909138 IDirect3DMobileDevice::CreateAdditionalSwapChain (Header: D3dm.h.) */
/* ms909139 IDirect3DMobileDevice::CreateDepthStencilSurface (Header: D3dm.h.) */
/* ms909140 IDirect3DMobileDevice::CreateImageSurface (Header: D3dm.h.) */
/* ms909141 IDirect3DMobileDevice::CreateIndexBuffer (Header: D3dm.h.) */
/* ms909142 IDirect3DMobileDevice::CreateRenderTarget (Header: D3dm.h.) */
/* ms909143 IDirect3DMobileDevice::CreateTexture (Header: D3dm.h.) */
/* ms909144 IDirect3DMobileDevice::CreateVertexBuffer (Header: D3dm.h.) */
/* ms909145 IDirect3DMobileDevice::DrawIndexedPrimitive (Header: D3dm.h.) */
/* ms909146 IDirect3DMobileDevice::DrawPrimitive (Header: D3dm.h.) */
/* ms929092 IDirect3DMobileDevice::EndScene (Header: D3dm.h.) */
/* ms929093 IDirect3DMobileDevice::GetAvailableTextureMem (Header: D3dm.h.) */
/* ms929094 IDirect3DMobileDevice::GetBackBuffer (Header: D3dm.h.) */
/* ms929095 IDirect3DMobileDevice::GetClipStatus (Header: D3dm.h.) */
/* ms929096 IDirect3DMobileDevice::GetCreationParameters (Header: D3dm.h.) */
/* ms929097 IDirect3DMobileDevice::GetCurrentTexturePalette (Header: D3dm.h.) */
/* ms929098 IDirect3DMobileDevice::GetDepthStencilSurface (Header: D3dm.h.) */
/* ms929099 IDirect3DMobileDevice::GetDeviceCaps (Header: D3dm.h.) */
/* ms929100 IDirect3DMobileDevice::GetDirect3D (Header: D3dm.h.) */
/* ms929101 IDirect3DMobileDevice::GetDisplayMode (Header: D3dm.h.) */
/* ms929102 IDirect3DMobileDevice::GetFrontBuffer (Header: D3dm.h.) */
/* ms929103 IDirect3DMobileDevice::GetIndices (Header: D3dm.h.) */
/* ms929104 IDirect3DMobileDevice::GetInfo (Header: D3dm.h.) */
/* ms929105 IDirect3DMobileDevice::GetLight (Header: D3dm.h.) */
/* ms929106 IDirect3DMobileDevice::GetLightEnable (Header: D3dm.h.) */
/* ms929107 IDirect3DMobileDevice::GetMaterial (Header: D3dm.h.) */
/* ms929108 IDirect3DMobileDevice::GetPaletteEntries (Header: D3dm.h.) */
/* ms929109 IDirect3DMobileDevice::GetRenderState (Header: D3dm.h.) */
/* ms929110 IDirect3DMobileDevice::GetRenderTarget (Header: D3dm.h.) */
/* ms929112 IDirect3DMobileDevice::GetStreamSource (Header: D3dm.h.) */
/* ms929113 IDirect3DMobileDevice::GetTexture (Header: D3dm.h.) */
/* ms929114 IDirect3DMobileDevice::GetTextureStageState (Header: D3dm.h.) */
/* ms929115 IDirect3DMobileDevice::GetTransform (Header: D3dm.h.) */
/* ms929116 IDirect3DMobileDevice::GetViewport (Header: D3dm.h.) */
/* ms929117 IDirect3DMobileDevice::LightEnable (Header: D3dm.h.) */
/* ms929118 IDirect3DMobileDevice::Present (Header: D3dm.h.) */
/* ms929119 IDirect3DMobileDevice::ProcessVertices (Header: D3dm.h.) */
/* ms929120 IDirect3DMobileDevice::Reset (Header: D3dm.h.) */
/* ms929121 IDirect3DMobileDevice::ResourceManagerDiscardBytes (Header: D3dm.h.) */
/* ms929122 IDirect3DMobileDevice::SetClipStatus (Header: D3dm.h.) */
/* ms929123 IDirect3DMobileDevice::SetCurrentTexturePalette (Header: D3dm.h.) */
/* ms929124 IDirect3DMobileDevice::SetIndices (Header: D3dm.h.) */
/* ms929125 IDirect3DMobileDevice::SetLight (Header: D3dm.h.) */
/* ms929126 IDirect3DMobileDevice::SetMaterial (Header: D3dm.h.) */
/* ms929127 IDirect3DMobileDevice::SetPaletteEntries (Header: D3dm.h.) */
/* ms929128 IDirect3DMobileDevice::SetRenderState (Header: D3dm.h.) */
/* ms929129 IDirect3DMobileDevice::SetRenderTarget (Header: D3dm.h.) */
/* ms929130 IDirect3DMobileDevice::SetStreamSource (Header: D3dm.h.) */
/* ms929131 IDirect3DMobileDevice::SetTexture (Header: D3dm.h.) */
/* ms929132 IDirect3DMobileDevice::SetTextureStageState (Header: D3dm.h.) */
/* ms929133 IDirect3DMobileDevice::SetTransform (Header: D3dm.h.) */
/* ms929134 IDirect3DMobileDevice::SetViewport (Header: D3dm.h.) */
/* ms929135 IDirect3DMobileDevice::StretchRect (Header: D3dm.h.) */
/* ms929136 IDirect3DMobileDevice::TestCooperativeLevel (Header: D3dm.h.) */
/* ms929137 IDirect3DMobileDevice::UpdateTexture (Header: D3dm.h.) */
/* ms929138 IDirect3DMobileDevice::ValidateDevice (Header: D3dm.h.) */
/* ms929146 IDirect3DMobileIndexBuffer::GetDesc (Header: D3dm.h.) */
/* ms929147 IDirect3DMobileIndexBuffer::Lock (Header: D3dm.h.) */
/* ms929148 IDirect3DMobileIndexBuffer::Unlock (Header: D3dm.h.) */
/* ms929151 IDirect3DMobileResource::GetDevice (Header: D3dm.h.) */
/* ms929152 IDirect3DMobileResource::GetPriority (Header: D3dm.h.) */
/* ms929153 IDirect3DMobileResource::GetType (Header: D3dm.h.) */
/* ms929154 IDirect3DMobileResource::PreLoad (Header: D3dm.h.) */
/* ms929155 IDirect3DMobileResource::SetPriority (Header: D3dm.h.) */
/* ms929511 IDirect3DMobileSurface::GetContainer (Header: D3dm.h.) */
/* ms929619 IDirect3DMobileSurface::GetDC (Header: D3dm.h.) */
/* ms929621 IDirect3DMobileSurface::GetDesc (Header: D3dm.h.) */
/* ms929622 IDirect3DMobileSurface::GetDevice (Header: D3dm.h.) */
/* ms929623 IDirect3DMobileSurface::LockRect (Header: D3dm.h.) */
/* ms929624 IDirect3DMobileSurface::ReleaseDC (Header: D3dm.h.) */
/* ms929625 IDirect3DMobileSurface::UnlockRect (Header: D3dm.h.) */
/* ms929627 IDirect3DMobileSwapChain::GetBackBuffer (Header: D3dm.h.) */
/* ms929628 IDirect3DMobileSwapChain::Present (Header: D3dm.h.) */
/* ms929630 IDirect3DMobileTexture::AddDirtyRect (Header: D3dm.h.) */
/* ms929631 IDirect3DMobileTexture::GetLevelDesc (Header: D3dm.h.) */
/* ms929632 IDirect3DMobileTexture::GetSurfaceLevel (Header: D3dm.h.) */
/* ms929633 IDirect3DMobileTexture::LockRect (Header: D3dm.h.) */
/* ms929634 IDirect3DMobileTexture::UnlockRect (Header: D3dm.h.) */
/* ms929636 IDirect3DMobileVertexBuffer::GetDesc (Header: D3dm.h.) */
/* ms929637 IDirect3DMobileVertexBuffer::Lock (Header: D3dm.h.) */
/* ms929638 IDirect3DMobileVertexBuffer::Unlock (Header: D3dm.h.) */
/* ms912040 Interface Identifiers for Direct3D Mobile (Header: D3dm.h.) */

/* ------------------------------------------------------------------
 * Book surface: d3dm (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa451158 About Render States */
/* aa451161 Accessing the Contents of a Vertex Buffer */
/* aa451170 Alpha Blending */
/* aa451171 Alpha Blending State */
/* aa451173 Alpha Test */
/* aa451174 Alpha Testing State */
/* aa451175 Alpha Texture Blending */
/* aa451177 Ambient Lighting State */
/* aa451178 Anisotropic Texture Filtering */
/* aa451179 Antialiasing */
/* aa451180 Application-Managed Resources and Allocation Strategies */
/* aa451193 Automatic Texture Management */
/* aa451199 Back-Face Culling */
/* aa451203 Basic Lighting Formula */
/* aa451204 Basic Texturing Concepts */
/* aa451205 Beginning and Ending a Scene */
/* aa451211 Blitting in Direct3D Mobile */
/* aa451217 Border Color Texture Address Mode */
/* aa451225 Camera Space Transformation */
/* aa451228 Changing Depth Buffer Comparison Functions */
/* aa451229 Changing Depth Buffer Write Access */
/* aa451234 Clamp Texture Address Mode */
/* aa451235 Clearing Depth Buffers */
/* aa451236 Clearing Surfaces */
/* aa451238 Clipping */
/* aa451246 Color Values for Lights and Materials */
/* aa451436 Common Details for Direct3D Mobile Resources */
/* aa451248 Compressed Texture Formats */
/* aa451249 Compressed Texture Resources */
/* aa451261 Coordinate Transformation Matrices */
/* aa451262 Copying To Surfaces */
/* aa451273 Creating a Depth Buffer */
/* aa451274 Creating a Direct3D Mobile Device */
/* aa451287 Creating a Vertex Buffer */
/* aa451275 Creating Direct3D Mobile Resources */
/* aa451278 Creating Texture Maps in Direct3D Mobile */
/* aa451289 Culling State */
/* aa451299 Depth Buffering */
/* aa451300 Depth Buffering State */
/* aa451301 Depth Buffers */
/* aa451304 Determining Hardware Support */
/* aa451310 Device Limitations for Texture Addressing */
/* aa451311 Device States */
/* aa451312 Device Types */
/* aa451313 Device Types and Index Processing Requirements */
/* aa451314 Device Types and Vertex Processing Requirements */
/* aa451307 Device-Supported Primitive Types */
/* aa451315 Differences Between Direct3D Mobile and Other Versions of Direct3D */
/* aa451340 Direct Light vs. Ambient Light */
/* aa451322 Direct3D Mobile and COM */
/* aa452479 Direct3D Mobile Application Development */
/* aa451318 Direct3D Mobile Application Initialization */
/* aa451319 Direct3D Mobile Application Operation */
/* aa451320 Direct3D Mobile Application Shutdown */
/* aa451321 Direct3D Mobile Architecture */
/* aa451580 Direct3D Mobile Capability Bits */
/* aa451323 Direct3D Mobile Cooperative Levels */
/* aa452480 Direct3D Mobile Data Types */
/* aa451308 Direct3D Mobile Device Capabilities */
/* aa451324 Direct3D Mobile Devices */
/* aa452481 Direct3D Mobile Enumerations */
/* aa452482 Direct3D Mobile Functions */
/* aa452483 Direct3D Mobile Interfaces */
/* aa451325 Direct3D Mobile Light Model vs. Nature */
/* aa452484 Direct3D Mobile Macros */
/* aa452485 Direct3D Mobile Migration */
/* ms913324 Direct3D Mobile OS Design Development */
/* aa451327 Direct3D Mobile Programming */
/* ms913343 Direct3D Mobile Reference */
/* ms932521 Direct3D Mobile Registry Settings */
/* aa451328 Direct3D Mobile Rendering Pipeline */
/* aa451329 Direct3D Mobile Resources */
/* ms932530 Direct3D Mobile Samples */
/* ms932540 Direct3D Mobile Security */
/* ms932554 Direct3D Mobile Structures */
/* aa451326 Direct3DMobile Object */
/* aa451341 Directly Mapping Texels to Pixels */
/* aa451359 Dithering */
/* aa451364 Driver Load Order */
/* ms923219 Enabling and Disabling Lights */
/* ms923211 Enabling Depth Buffering */
/* ms923237 Error Conditions in Direct3D Mobile */
/* ms923375 Flipping Surfaces */
/* ms923377 Fog */
/* ms923378 Fog State */
/* ms923382 FVF Vertex Buffers */
/* ms923383 GDI Interoperation */
/* ms923404 Hardware Considerations for Texturing */
/* ms923423 Index Buffer Descriptions */
/* ms923424 Index Buffers */
/* ms923425 Indexed Primitives */
/* ms923429 Interpolation */
/* ms923431 Introduction to Direct3D Mobile */
/* ms923434 Introduction to Lighting and Materials */
/* ms923438 Light Color */
/* ms923904 Light Direction */
/* ms924108 Light Mapping with Textures */
/* ms924117 Light Objects */
/* ms924119 Light Position, Range, and Attenuation */
/* ms924120 Light Properties */
/* ms924122 Light Type */
/* ms923982 Lighting */
/* ms923997 Lighting and Materials */
/* ms923988 Lighting Equations */
/* ms924006 Lighting State */
/* ms924016 Lighting Support */
/* ms924121 Lights */
/* ms924124 Line Lists */
/* ms924125 Line Strips */
/* ms924123 Linear Texture Filtering */
/* ms924127 Locking Direct3D Mobile Resources */
/* ms924128 Locking Resources */
/* ms924132 Lost Devices */
/* ms924134 Managing Resources */
/* ms924135 Manipulating Resources */
/* ms924137 Material Properties */
/* ms924138 Materials */
/* ms924145 Memory Pools in Direct3D Mobile */
/* ms924147 Mirror Texture Address Mode */
/* ms924151 Mixing Formats Within a Single Texture */
/* ms924159 Multipass Texture Blending */
/* ms924165 Multiple Texture Blending */
/* ms924167 Nearest-Point Sampling */
/* ms924170 Opaque and One-Bit Alpha Textures */
/* ms924173 Other Vertex Data */
/* ms924174 Outline and Fill State */
/* ms924199 Per Pixel Operations */
/* ms924198 Per-Vertex Color State */
/* ms924200 Perspective-Correct Texture Mapping */
/* ms924210 Point Lists */
/* ms924474 Pool and Usage for Index Buffers */
/* ms924562 Pool and Usage for Vertex Buffers */
/* ms924575 Presenting a Scene */
/* ms924576 Primitive Clipping State */
/* ms924577 Primitive Types */
/* ms924582 Processing Vertex Data */
/* ms924583 Processing Vertex Transformations */
/* ms924584 Processing Vertices */
/* ms924585 Projection Transformations */
/* ms924590 Querying for Depth Buffer Support */
/* ms924592 Rasterization */
/* ms924593 Rasterization Rules */
/* ms924597 Registration of a Software Device */
/* ms924602 Render States */
/* ms924599 Rendering */
/* ms924600 Rendering from a Vertex Buffer */
/* ms924601 Rendering Primitives */
/* ms924603 Resource Properties */
/* ms924604 Resource Relationships */
/* ms924607 Retrieving a Depth Buffer */
/* ms924609 Retrieving Light Properties */
/* ms924610 Retrieving Material Properties */
/* ms924614 Retrieving Vertex Buffer Descriptions */
/* ms924618 Scene Presentation */
/* ms924619 Screen Operations */
/* ms924621 Selecting a Device */
/* ms924628 Setting and Retrieving Texture Addressing Modes */
/* ms924624 Setting Light Properties */
/* ms924625 Setting Material Properties */
/* ms924631 Setting Transformations */
/* ms924634 Shading State */
/* ms924644 Stencil Buffer State */
/* ms924643 Stencil Buffers */
/* ms924645 Stencil Operations */
/* aa451408 Storage Efficiency and Texture Compression */
/* ms924657 Surface Formats */
/* ms924658 Surface Interfaces */
/* ms924660 Surfaces */
/* ms924668 Texture Addressing Modes */
/* ms924669 Texture Addressing Modes and Texture Wrapping */
/* aa451365 Texture Blending */
/* aa451366 Texture Coordinate Formats */
/* aa451367 Texture Coordinate Processing */
/* aa451369 Texture Coordinate Transformation */
/* aa451370 Texture Coordinate Transformations */
/* aa451371 Texture Coordinate Wrapping */
/* aa451368 Texture Coordinates */
/* aa451372 Texture Dirty Regions */
/* aa451373 Texture Filtering */
/* aa451374 Texture Filtering with Mipmaps */
/* aa451375 Texture Mapping */
/* aa451376 Texture Read */
/* aa451377 Texture Resources */
/* aa451379 Texture Stage Inputs */
/* aa451380 Texture Stage Operation */
/* aa451381 Texture Stage States */
/* aa451383 Texture Wrapping */
/* aa451384 Texture Wrapping State */
/* aa451378 Textures */
/* aa451382 Textures with Alpha Channels */
/* aa451396 Transformation */
/* aa451397 Transformed and Lit Vertex Functionality */
/* aa451398 Transformed and Lit Vertices */
/* aa451402 Triangle Fans */
/* aa451403 Triangle Lists */
/* aa451404 Triangle Strips */
/* aa451410 Untransformed and Lit Vertices */
/* aa451411 Untransformed and Unlit Vertices */
/* aa451421 Using Compressed Textures */
/* aa451423 Using Devices */
/* aa451424 Using Direct3D Mobile Resources */
/* aa451429 Using Index Buffers */
/* aa451430 Using Lights */
/* aa451447 Using Vertex Buffers */
/* aa451449 Using Z-Bias */
/* aa451452 Vertex Buffer Descriptions */
/* aa451453 Vertex Buffers */
/* aa451454 Vertex Data Description */
/* aa451455 Vertex Formats */
/* aa451456 Vertex Normals */
/* aa451464 View Transformation */
/* aa451463 Viewport Transformation */
/* ms925261 Width vs. Pitch */
/* ms925282 World Transformation */
/* ms925283 Wrap Texture Address Mode */
/* ms925290 Writing Pixels */

/* ------------------------------------------------------------------
 * Book surface: d3dm (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms928109 D3DMCREATE_MULTITHREADED: documented name-only (no value published; held) */
/* ms907765 D3DM Values (Header: D3dm.h.) */
/* ms939132 D3DMADAPTER Values (Header: D3dm.h.) */
/* aa451582 D3DMERR Values (Header: D3dm.h.) */
/* ms909127 IDirect3DMobile::CheckDepthStencilMatch (Header: D3dm.h.) */
/* ms909128 IDirect3DMobile::CheckDeviceFormat (Header: D3dm.h.) */
/* ms923411 IDirect3DMobile::CheckDeviceFormatConversion (Header: D3dm.h.) */
/* ms909129 IDirect3DMobile::CheckDeviceMultiSampleType (Header: D3dm.h.) */
/* ms909130 IDirect3DMobile::CheckDeviceType (Header: D3dm.h.) */
/* ms909131 IDirect3DMobile::CheckProfile (Header: D3dm.h.) */
/* ms909132 IDirect3DMobile::CreateDevice (Header: D3dm.h.) */
/* ms929139 IDirect3DMobile::EnumAdapterModes (Header: D3dm.h.) */
/* ms929140 IDirect3DMobile::GetAdapterCount (Header: D3dm.h.) */
/* ms929141 IDirect3DMobile::GetAdapterDisplayMode (Header: D3dm.h.) */
/* ms929142 IDirect3DMobile::GetAdapterIdentifier (Header: D3dm.h.) */
/* ms929143 IDirect3DMobile::GetAdapterModeCount (Header: D3dm.h.) */
/* ms929144 IDirect3DMobile::GetDeviceCaps (Header: D3dm.h.) */
/* ms929149 IDirect3DMobile::RegisterSoftwareDevice (Header: D3dm.h.) */
/* ms909124 IDirect3DMobileBaseTexture::GetLevelCount (Header: D3dm.h.) */
/* ms909125 IDirect3DMobileBaseTexture::GetLOD (Header: D3dm.h.) */
/* ms909126 IDirect3DMobileBaseTexture::SetLOD (Header: D3dm.h.) */
/* ms909134 IDirect3DMobileDevice::BeginScene (Header: D3dm.h.) */
/* ms909135 IDirect3DMobileDevice::Clear (Header: D3dm.h.) */
/* ms909136 IDirect3DMobileDevice::ColorFill (Header: D3dm.h.) */
/* ms909137 IDirect3DMobileDevice::CopyRects (Header: D3dm.h.) */
/* ms909138 IDirect3DMobileDevice::CreateAdditionalSwapChain (Header: D3dm.h.) */
/* ms909139 IDirect3DMobileDevice::CreateDepthStencilSurface (Header: D3dm.h.) */
/* ms909140 IDirect3DMobileDevice::CreateImageSurface (Header: D3dm.h.) */
/* ms909141 IDirect3DMobileDevice::CreateIndexBuffer (Header: D3dm.h.) */
/* ms909142 IDirect3DMobileDevice::CreateRenderTarget (Header: D3dm.h.) */
/* ms909143 IDirect3DMobileDevice::CreateTexture (Header: D3dm.h.) */
/* ms909144 IDirect3DMobileDevice::CreateVertexBuffer (Header: D3dm.h.) */
/* ms909145 IDirect3DMobileDevice::DrawIndexedPrimitive (Header: D3dm.h.) */
/* ms909146 IDirect3DMobileDevice::DrawPrimitive (Header: D3dm.h.) */
/* ms929092 IDirect3DMobileDevice::EndScene (Header: D3dm.h.) */
/* ms929093 IDirect3DMobileDevice::GetAvailableTextureMem (Header: D3dm.h.) */
/* ms929094 IDirect3DMobileDevice::GetBackBuffer (Header: D3dm.h.) */
/* ms929095 IDirect3DMobileDevice::GetClipStatus (Header: D3dm.h.) */
/* ms929096 IDirect3DMobileDevice::GetCreationParameters (Header: D3dm.h.) */
/* ms929097 IDirect3DMobileDevice::GetCurrentTexturePalette (Header: D3dm.h.) */
/* ms929098 IDirect3DMobileDevice::GetDepthStencilSurface (Header: D3dm.h.) */
/* ms929099 IDirect3DMobileDevice::GetDeviceCaps (Header: D3dm.h.) */
/* ms929100 IDirect3DMobileDevice::GetDirect3D (Header: D3dm.h.) */
/* ms929101 IDirect3DMobileDevice::GetDisplayMode (Header: D3dm.h.) */
/* ms929102 IDirect3DMobileDevice::GetFrontBuffer (Header: D3dm.h.) */
/* ms929103 IDirect3DMobileDevice::GetIndices (Header: D3dm.h.) */
/* ms929104 IDirect3DMobileDevice::GetInfo (Header: D3dm.h.) */
/* ms929105 IDirect3DMobileDevice::GetLight (Header: D3dm.h.) */
/* ms929106 IDirect3DMobileDevice::GetLightEnable (Header: D3dm.h.) */
/* ms929107 IDirect3DMobileDevice::GetMaterial (Header: D3dm.h.) */
/* ms929108 IDirect3DMobileDevice::GetPaletteEntries (Header: D3dm.h.) */
/* ms929109 IDirect3DMobileDevice::GetRenderState (Header: D3dm.h.) */
/* ms929110 IDirect3DMobileDevice::GetRenderTarget (Header: D3dm.h.) */
/* ms929112 IDirect3DMobileDevice::GetStreamSource (Header: D3dm.h.) */
/* ms929113 IDirect3DMobileDevice::GetTexture (Header: D3dm.h.) */
/* ms929114 IDirect3DMobileDevice::GetTextureStageState (Header: D3dm.h.) */
/* ms929115 IDirect3DMobileDevice::GetTransform (Header: D3dm.h.) */
/* ms929116 IDirect3DMobileDevice::GetViewport (Header: D3dm.h.) */
/* ms929117 IDirect3DMobileDevice::LightEnable (Header: D3dm.h.) */
/* ms929118 IDirect3DMobileDevice::Present (Header: D3dm.h.) */
/* ms929119 IDirect3DMobileDevice::ProcessVertices (Header: D3dm.h.) */
/* ms929120 IDirect3DMobileDevice::Reset (Header: D3dm.h.) */
/* ms929121 IDirect3DMobileDevice::ResourceManagerDiscardBytes (Header: D3dm.h.) */
/* ms929122 IDirect3DMobileDevice::SetClipStatus (Header: D3dm.h.) */
/* ms929123 IDirect3DMobileDevice::SetCurrentTexturePalette (Header: D3dm.h.) */
/* ms929124 IDirect3DMobileDevice::SetIndices (Header: D3dm.h.) */
/* ms929125 IDirect3DMobileDevice::SetLight (Header: D3dm.h.) */
/* ms929126 IDirect3DMobileDevice::SetMaterial (Header: D3dm.h.) */
/* ms929127 IDirect3DMobileDevice::SetPaletteEntries (Header: D3dm.h.) */
/* ms929128 IDirect3DMobileDevice::SetRenderState (Header: D3dm.h.) */
/* ms929129 IDirect3DMobileDevice::SetRenderTarget (Header: D3dm.h.) */
/* ms929130 IDirect3DMobileDevice::SetStreamSource (Header: D3dm.h.) */
/* ms929131 IDirect3DMobileDevice::SetTexture (Header: D3dm.h.) */
/* ms929132 IDirect3DMobileDevice::SetTextureStageState (Header: D3dm.h.) */
/* ms929133 IDirect3DMobileDevice::SetTransform (Header: D3dm.h.) */
/* ms929134 IDirect3DMobileDevice::SetViewport (Header: D3dm.h.) */
/* ms929135 IDirect3DMobileDevice::StretchRect (Header: D3dm.h.) */
/* ms929136 IDirect3DMobileDevice::TestCooperativeLevel (Header: D3dm.h.) */
/* ms929137 IDirect3DMobileDevice::UpdateTexture (Header: D3dm.h.) */
/* ms929138 IDirect3DMobileDevice::ValidateDevice (Header: D3dm.h.) */
/* ms929146 IDirect3DMobileIndexBuffer::GetDesc (Header: D3dm.h.) */
/* ms929147 IDirect3DMobileIndexBuffer::Lock (Header: D3dm.h.) */
/* ms929148 IDirect3DMobileIndexBuffer::Unlock (Header: D3dm.h.) */
/* ms929151 IDirect3DMobileResource::GetDevice (Header: D3dm.h.) */
/* ms929152 IDirect3DMobileResource::GetPriority (Header: D3dm.h.) */
/* ms929153 IDirect3DMobileResource::GetType (Header: D3dm.h.) */
/* ms929154 IDirect3DMobileResource::PreLoad (Header: D3dm.h.) */
/* ms929155 IDirect3DMobileResource::SetPriority (Header: D3dm.h.) */
/* ms929511 IDirect3DMobileSurface::GetContainer (Header: D3dm.h.) */
/* ms929619 IDirect3DMobileSurface::GetDC (Header: D3dm.h.) */
/* ms929621 IDirect3DMobileSurface::GetDesc (Header: D3dm.h.) */
/* ms929622 IDirect3DMobileSurface::GetDevice (Header: D3dm.h.) */
/* ms929623 IDirect3DMobileSurface::LockRect (Header: D3dm.h.) */
/* ms929624 IDirect3DMobileSurface::ReleaseDC (Header: D3dm.h.) */
/* ms929625 IDirect3DMobileSurface::UnlockRect (Header: D3dm.h.) */
/* ms929627 IDirect3DMobileSwapChain::GetBackBuffer (Header: D3dm.h.) */
/* ms929628 IDirect3DMobileSwapChain::Present (Header: D3dm.h.) */
/* ms929630 IDirect3DMobileTexture::AddDirtyRect (Header: D3dm.h.) */
/* ms929631 IDirect3DMobileTexture::GetLevelDesc (Header: D3dm.h.) */
/* ms929632 IDirect3DMobileTexture::GetSurfaceLevel (Header: D3dm.h.) */
/* ms929633 IDirect3DMobileTexture::LockRect (Header: D3dm.h.) */
/* ms929634 IDirect3DMobileTexture::UnlockRect (Header: D3dm.h.) */
/* ms929636 IDirect3DMobileVertexBuffer::GetDesc (Header: D3dm.h.) */
/* ms929637 IDirect3DMobileVertexBuffer::Lock (Header: D3dm.h.) */
/* ms929638 IDirect3DMobileVertexBuffer::Unlock (Header: D3dm.h.) */
/* ms912040 Interface Identifiers for Direct3D Mobile (Header: D3dm.h.) */

/* ------------------------------------------------------------------
 * Book surface: d3dm (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa451158 About Render States */
/* aa451161 Accessing the Contents of a Vertex Buffer */
/* aa451170 Alpha Blending */
/* aa451171 Alpha Blending State */
/* aa451173 Alpha Test */
/* aa451174 Alpha Testing State */
/* aa451175 Alpha Texture Blending */
/* aa451177 Ambient Lighting State */
/* aa451178 Anisotropic Texture Filtering */
/* aa451179 Antialiasing */
/* aa451180 Application-Managed Resources and Allocation Strategies */
/* aa451193 Automatic Texture Management */
/* aa451199 Back-Face Culling */
/* aa451203 Basic Lighting Formula */
/* aa451204 Basic Texturing Concepts */
/* aa451205 Beginning and Ending a Scene */
/* aa451211 Blitting in Direct3D Mobile */
/* aa451217 Border Color Texture Address Mode */
/* aa451225 Camera Space Transformation */
/* aa451228 Changing Depth Buffer Comparison Functions */
/* aa451229 Changing Depth Buffer Write Access */
/* aa451234 Clamp Texture Address Mode */
/* aa451235 Clearing Depth Buffers */
/* aa451236 Clearing Surfaces */
/* aa451238 Clipping */
/* aa451246 Color Values for Lights and Materials */
/* aa451436 Common Details for Direct3D Mobile Resources */
/* aa451248 Compressed Texture Formats */
/* aa451249 Compressed Texture Resources */
/* aa451261 Coordinate Transformation Matrices */
/* aa451262 Copying To Surfaces */
/* aa451273 Creating a Depth Buffer */
/* aa451274 Creating a Direct3D Mobile Device */
/* aa451287 Creating a Vertex Buffer */
/* aa451275 Creating Direct3D Mobile Resources */
/* aa451278 Creating Texture Maps in Direct3D Mobile */
/* aa451289 Culling State */
/* aa451299 Depth Buffering */
/* aa451300 Depth Buffering State */
/* aa451301 Depth Buffers */
/* aa451304 Determining Hardware Support */
/* aa451310 Device Limitations for Texture Addressing */
/* aa451311 Device States */
/* aa451312 Device Types */
/* aa451313 Device Types and Index Processing Requirements */
/* aa451314 Device Types and Vertex Processing Requirements */
/* aa451307 Device-Supported Primitive Types */
/* aa451315 Differences Between Direct3D Mobile and Other Versions of Direct3D */
/* aa451340 Direct Light vs. Ambient Light */
/* aa451322 Direct3D Mobile and COM */
/* aa452479 Direct3D Mobile Application Development */
/* aa451318 Direct3D Mobile Application Initialization */
/* aa451319 Direct3D Mobile Application Operation */
/* aa451320 Direct3D Mobile Application Shutdown */
/* aa451321 Direct3D Mobile Architecture */
/* aa451580 Direct3D Mobile Capability Bits */
/* aa451323 Direct3D Mobile Cooperative Levels */
/* aa452480 Direct3D Mobile Data Types */
/* aa451308 Direct3D Mobile Device Capabilities */
/* aa451324 Direct3D Mobile Devices */
/* aa452481 Direct3D Mobile Enumerations */
/* aa452482 Direct3D Mobile Functions */
/* aa452483 Direct3D Mobile Interfaces */
/* aa451325 Direct3D Mobile Light Model vs. Nature */
/* aa452484 Direct3D Mobile Macros */
/* aa452485 Direct3D Mobile Migration */
/* ms913324 Direct3D Mobile OS Design Development */
/* aa451327 Direct3D Mobile Programming */
/* ms913343 Direct3D Mobile Reference */
/* ms932521 Direct3D Mobile Registry Settings */
/* aa451328 Direct3D Mobile Rendering Pipeline */
/* aa451329 Direct3D Mobile Resources */
/* ms932530 Direct3D Mobile Samples */
/* ms932540 Direct3D Mobile Security */
/* ms932554 Direct3D Mobile Structures */
/* aa451326 Direct3DMobile Object */
/* aa451341 Directly Mapping Texels to Pixels */
/* aa451359 Dithering */
/* aa451364 Driver Load Order */
/* ms923219 Enabling and Disabling Lights */
/* ms923211 Enabling Depth Buffering */
/* ms923237 Error Conditions in Direct3D Mobile */
/* ms923375 Flipping Surfaces */
/* ms923377 Fog */
/* ms923378 Fog State */
/* ms923382 FVF Vertex Buffers */
/* ms923383 GDI Interoperation */
/* ms923404 Hardware Considerations for Texturing */
/* ms923423 Index Buffer Descriptions */
/* ms923424 Index Buffers */
/* ms923425 Indexed Primitives */
/* ms923429 Interpolation */
/* ms923431 Introduction to Direct3D Mobile */
/* ms923434 Introduction to Lighting and Materials */
/* ms923438 Light Color */
/* ms923904 Light Direction */
/* ms924108 Light Mapping with Textures */
/* ms924117 Light Objects */
/* ms924119 Light Position, Range, and Attenuation */
/* ms924120 Light Properties */
/* ms924122 Light Type */
/* ms923982 Lighting */
/* ms923997 Lighting and Materials */
/* ms923988 Lighting Equations */
/* ms924006 Lighting State */
/* ms924016 Lighting Support */
/* ms924121 Lights */
/* ms924124 Line Lists */
/* ms924125 Line Strips */
/* ms924123 Linear Texture Filtering */
/* ms924127 Locking Direct3D Mobile Resources */
/* ms924128 Locking Resources */
/* ms924132 Lost Devices */
/* ms924134 Managing Resources */
/* ms924135 Manipulating Resources */
/* ms924137 Material Properties */
/* ms924138 Materials */
/* ms924145 Memory Pools in Direct3D Mobile */
/* ms924147 Mirror Texture Address Mode */
/* ms924151 Mixing Formats Within a Single Texture */
/* ms924159 Multipass Texture Blending */
/* ms924165 Multiple Texture Blending */
/* ms924167 Nearest-Point Sampling */
/* ms924170 Opaque and One-Bit Alpha Textures */
/* ms924173 Other Vertex Data */
/* ms924174 Outline and Fill State */
/* ms924199 Per Pixel Operations */
/* ms924198 Per-Vertex Color State */
/* ms924200 Perspective-Correct Texture Mapping */
/* ms924210 Point Lists */
/* ms924474 Pool and Usage for Index Buffers */
/* ms924562 Pool and Usage for Vertex Buffers */
/* ms924575 Presenting a Scene */
/* ms924576 Primitive Clipping State */
/* ms924577 Primitive Types */
/* ms924582 Processing Vertex Data */
/* ms924583 Processing Vertex Transformations */
/* ms924584 Processing Vertices */
/* ms924585 Projection Transformations */
/* ms924590 Querying for Depth Buffer Support */
/* ms924592 Rasterization */
/* ms924593 Rasterization Rules */
/* ms924597 Registration of a Software Device */
/* ms924602 Render States */
/* ms924599 Rendering */
/* ms924600 Rendering from a Vertex Buffer */
/* ms924601 Rendering Primitives */
/* ms924603 Resource Properties */
/* ms924604 Resource Relationships */
/* ms924607 Retrieving a Depth Buffer */
/* ms924609 Retrieving Light Properties */
/* ms924610 Retrieving Material Properties */
/* ms924614 Retrieving Vertex Buffer Descriptions */
/* ms924618 Scene Presentation */
/* ms924619 Screen Operations */
/* ms924621 Selecting a Device */
/* ms924628 Setting and Retrieving Texture Addressing Modes */
/* ms924624 Setting Light Properties */
/* ms924625 Setting Material Properties */
/* ms924631 Setting Transformations */
/* ms924634 Shading State */
/* ms924644 Stencil Buffer State */
/* ms924643 Stencil Buffers */
/* ms924645 Stencil Operations */
/* aa451408 Storage Efficiency and Texture Compression */
/* ms924657 Surface Formats */
/* ms924658 Surface Interfaces */
/* ms924660 Surfaces */
/* ms924668 Texture Addressing Modes */
/* ms924669 Texture Addressing Modes and Texture Wrapping */
/* aa451365 Texture Blending */
/* aa451366 Texture Coordinate Formats */
/* aa451367 Texture Coordinate Processing */
/* aa451369 Texture Coordinate Transformation */
/* aa451370 Texture Coordinate Transformations */
/* aa451371 Texture Coordinate Wrapping */
/* aa451368 Texture Coordinates */
/* aa451372 Texture Dirty Regions */
/* aa451373 Texture Filtering */
/* aa451374 Texture Filtering with Mipmaps */
/* aa451375 Texture Mapping */
/* aa451376 Texture Read */
/* aa451377 Texture Resources */
/* aa451379 Texture Stage Inputs */
/* aa451380 Texture Stage Operation */
/* aa451381 Texture Stage States */
/* aa451383 Texture Wrapping */
/* aa451384 Texture Wrapping State */
/* aa451378 Textures */
/* aa451382 Textures with Alpha Channels */
/* aa451396 Transformation */
/* aa451397 Transformed and Lit Vertex Functionality */
/* aa451398 Transformed and Lit Vertices */
/* aa451402 Triangle Fans */
/* aa451403 Triangle Lists */
/* aa451404 Triangle Strips */
/* aa451410 Untransformed and Lit Vertices */
/* aa451411 Untransformed and Unlit Vertices */
/* aa451421 Using Compressed Textures */
/* aa451423 Using Devices */
/* aa451424 Using Direct3D Mobile Resources */
/* aa451429 Using Index Buffers */
/* aa451430 Using Lights */
/* aa451447 Using Vertex Buffers */
/* aa451449 Using Z-Bias */
/* aa451452 Vertex Buffer Descriptions */
/* aa451453 Vertex Buffers */
/* aa451454 Vertex Data Description */
/* aa451455 Vertex Formats */
/* aa451456 Vertex Normals */
/* aa451464 View Transformation */
/* aa451463 Viewport Transformation */
/* ms925261 Width vs. Pitch */
/* ms925282 World Transformation */
/* ms925283 Wrap Texture Address Mode */
/* ms925290 Writing Pixels */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_D3DM_H */
