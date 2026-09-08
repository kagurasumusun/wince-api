/*
 * objbase.h -- COM / OLE / Storage / Automation umbrella header for
 * Windows CE (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE
 * documentation (CE-era MSDN / learn.microsoft.com previous-versions
 * archive; page ids msnnnnnn cited per declaration).  This unit covers
 * the 635 corpus pages whose "Requirements -> Header" line names one
 * of the COM-family headers:
 *
 *   Objbase.h                    87 pages   (Co* activation/marshaling)
 *   Objidl.h (+Objidl.idl)      131 pages   (OLE data structures)
 *   Oaidl.h (+Oaidl.idl)        141 pages   (OLE Automation types)
 *   Wtypes.h                       6 pages  (CLSCTX / COAUTH* / ...)
 *   Unknwn.h (+Unknwn.idl)         3 pages  (IUnknown)
 *   Oleauto.h                    227 pages  (Variant/SafeArray/BSTR)
 *   Ocidl.h (+Ocidl.idl)          40 pages  (OLE control interfaces)
 *
 * The link libraries named by those pages are ole32.dll (84 exported
 * functions) and oleaut32.dll (223; the import table carries 222 --
 * UnRegisterTypeLib's page prints "Link Library: None"); the import
 * tables are def/ole32-doc.def and def/oleaut32-doc.def.
 *
 * The CE SDK's <Objbase.h> includes Objidl.h, Oaidl.h, Wtypes.h and
 * Unknwn.h; this single umbrella covers those headers plus
 * Oleauto.h/Ocidl.h, and each declaration notes the header named by
 * its page.
 *
 * Transcription conventions (documented deviations from the printed
 * pages):
 *   - FAR / FARSTRUCT / __RPC_FAR / HUGEP: pointer qualifiers with no
 *     effect on CE's 32-bit flat address space; dropped.
 *   - "UNION_NAME(u)" in the printed TYPEDESC / VARDESC expands to the
 *     named union member "u".
 *   - MIDL attributes ([switch_type(...)], [case(...)], [unique])
 *     printed on the CE 5.0 STGMEDIUM page are stripped.
 *   - Archive print artifacts are fixed at the site and noted:
 *       * IDLDESC: missing closing brace;
 *       * ELEMDESC: alias printed as "ELEMDES";
 *       * VARDESC: missing terminating semicolon;
 *       * TYPEDESC: first union member printed twice with garbage
 *         prefixes ("ESC", "tagTYPEDSC");
 *       * VARTYPE page: the flag tail printed without separators;
 *       * LoadRegTypeLib / UnRegisterTypeLib: missing comma between
 *         wVerMajor and wVerMinor;
 *       * SafeArrayCreate: "SAFEARRRAYBOUND" (three R's);
 *       * VarI4FromUI1: page ms891659 duplicates ms891668 with a wrong
 *         DATE parameter -- ms891668's spelling is used;
 *       * page ms891846 is titled VarR8FromI4 but prints "ULONG ulIn"
 *         -- that is the VarR8FromUI4 signature, declared as such;
 *       * CURRENTY -> CURRENCY, DOUBLE -> char/double, Ulong -> ULONG,
 *         ItypeInfo -> ITypeInfo, IerrorInfo -> IErrorInfo,
 *         VarR8FromDips -> VarR8FromDisp;
 *       * SafeArrayGetDim / SafeArrayGetElemsize: the printed return
 *         type is HRESULT, but each page's own "Return Values" text
 *         says the function returns the dimension count / element
 *         size, so both are declared ULONG;
 *       * SystemTimeToVariantTime / DispInvoke: the parameter printed
 *         by value is documented by the page as a pointer -- declared
 *         as a pointer.
 *   - Interface vtable layouts are not published in the CE corpus:
 *     every COM interface is an opaque pointer type; the methods the
 *     corpus documents for each interface are listed in a comment.
 *   - Names referenced by the pages but whose definitions the corpus
 *     does not publish are declared opaque (or as documented scalar
 *     equivalents) with a note.
 *
 * 32-bit structure sizes are asserted in tests/.
 */

#ifndef AKARI_OBJBASE_H
#define AKARI_OBJBASE_H

#include "windef.h"
#include "winbase.h"  /* FILETIME, HGLOBAL, SYSTEMTIME, SECURITY_ATTRIBUTES */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Calling-convention tokens printed by the CE pages.  All are empty  */
/* on CE's 32-bit flat model.                                         */
/* ------------------------------------------------------------------ */
#define STDAPI
#define WINOLEAPI
#define WINOLEAUTAPI
#define STDAPICALLTYPE

/* ------------------------------------------------------------------ */
/* Scalar types (Wtypes.h / Oaidl.h family)                           */
/* ------------------------------------------------------------------ */

/* OLECHAR: the BSTR page (ms886145) prints "typedef OLECHAR FAR* BSTR"
 * and describes BSTR as a pointer to a wide character string --
 * OLECHAR is the 16-bit OLE/COM character, i.e. WCHAR on CE. */
typedef WCHAR            OLECHAR;
typedef OLECHAR         *LPOLESTR;    /* CE doc spelling, used throughout */
typedef const OLECHAR   *LPCOLESTR;   /* CE doc spelling, used throughout */
typedef OLECHAR         *BSTR;        /* ms886145 */

/* HRESULT: the 32-bit COM result type (documented return of every
 * COM API).  The S_OK / S_FALSE / E_* constant names are referenced by
 * the pages; their numeric values are not published in the CE corpus,
 * so they are not defined here. */
typedef LONG             HRESULT;

/* GUID (the 16-byte COM identifier) and LPGUID are declared in
 * winnt.h; the layout is fixed by the binary form the
 * StringFromGUID2 / CoCreateGuid / CLSIDFromString pages document
 * (DWORD, USHORT, USHORT, 8 BYTE). */

typedef GUID             CLSID;       /* class identifier (ms886232) */
typedef GUID             IID;         /* interface identifier (ms886232) */
typedef GUID            *LPIID;       /* ms891281 IIDFromString */
typedef GUID            *LPCLSID;     /* ms886181 CLSIDFromProgID */

/* REF*: "reference to" an identifier.  The CE C prototypes take the
 * identifier by reference, which in C is a pointer to a const object
 * (the documented call sites pass addresses of identifiers). */
#define REFGUID           const GUID *
#define REFCLSID          const CLSID *
#define REFIID            const IID *

/* LCID is declared in windef.h (DWORD); the page ms890741 prints
 * "typedef unsigned long LCID" -- consistent, not redeclared. */

typedef LONG             DISPID;      /* ms886967: "Typedef LONG DISPID" */
typedef DISPID           MEMBERID;    /* ms890763: "Typedef DISPID MEMBERID" */
typedef ULONG            HREFTYPE;    /* ms886994: "typedef unsigned long HREFTYPE" */

/* VARIANT_BOOL / DATE / SCODE: members of the VARIANT / EXCEPINFO
 * unions (ms891678 / ms886984); the corpus has no standalone pages --
 * the 16-bit Automation boolean, the double OLE date and the 32-bit
 * HRESULT error code the Automation pages document. */
typedef unsigned short   VARIANT_BOOL;
typedef double           DATE;
typedef LONG             SCODE;

/* CY / CURRENCY (ms886958).  The page's _MAC branch is not the CE
 * branch; CE uses the little-endian 32-bit layout. */
typedef union _tagCY {
    struct {
        unsigned long Lo;
        long          Hi;
    };
    LONGLONG int64;
} CY;
typedef CY               CURRENCY;    /* ms886958 */

/* VARTYPE / VARENUM (ms891853). */
typedef unsigned short   VARTYPE;
typedef enum VARENUM {
    VT_EMPTY = 0, VT_NULL = 1, VT_I2 = 2, VT_I4 = 3, VT_R4 = 4,
    VT_R8 = 5, VT_CY = 6, VT_DATE = 7, VT_BSTR = 8, VT_DISPATCH = 9,
    VT_ERROR = 10, VT_BOOL = 11, VT_VARIANT = 12, VT_UNKNOWN = 13,
    VT_UI1 = 17
} VARENUM;
/* The flag tail of the page prints without separators; transcribed: */
#define VT_ARRAY          0x2000
#define VT_BYREF          0x4000
#define VT_RESERVED       0x8000

/* Opaque types referenced by the documented prototypes but whose
 * definitions the CE corpus does not publish (declared so the
 * documented signatures compile). */
typedef struct _SNB SNB;                                /* storage name buffer (StgOpenStorage) */
typedef struct _PARAMDESCEX PARAMDESCEX;                /* extended parameter description (PARAMDESC) */
typedef PARAMDESCEX     *LPPARAMDESCEX;
typedef struct _SOLE_AUTHENTICATION_LIST SOLE_AUTHENTICATION_LIST; /* CoInitializeSecurity */
typedef void           *RPC_AUTHZ_HANDLE;               /* CoQueryClientBlanket */
typedef void           *RPC_AUTH_IDENTITY_HANDLE;       /* CoQueryProxyBlanket */
typedef struct _SECURITY_DESCRIPTOR SECURITY_DESCRIPTOR; /* CoInitializeSecurity */
typedef SECURITY_DESCRIPTOR *PSECURITY_DESCRIPTOR;
typedef struct _DECIMAL DECIMAL;                        /* Decimal (Var*FromDec) */
typedef struct _UDATE UDATE;                            /* UDATE (VarDateFromUdate) */
typedef struct _NUMPARSE NUMPARSE;                      /* VarParseNumFromStr */
typedef void           *HENHMETAFILE;                   /* enhanced metafile handle (STGMEDIUM) */
typedef void           *HMETAFILEPICT;                  /* metafile picture handle (STGMEDIUM) */

/* SIZEL: the CE spelling of the {LONG cx, LONG cy} size (SIZE) used
 * by the Ocidl.h pages (DVEXTENTINFO). */
typedef struct _SIZEL {
    LONG cx;
    LONG cy;
} SIZEL;

/* ------------------------------------------------------------------ */
/* Enumeration types (Oaidl.h / Objidl.h / Wtypes.h / Ocidl.h)        */
/* ------------------------------------------------------------------ */

/* CLSCTX (ms886177; Wtypes.h). */
typedef enum _tagCLSCTX {
    CLSCTX_INPROC_SERVER  = 0x1,
    CLSCTX_INPROC_HANDLER = 0x2,
    CLSCTX_LOCAL_SERVER   = 0x4,
    CLSCTX_REMOTE_SERVER  = 0x10
} CLSCTX;
#define CLSCTX_SERVER (CLSCTX_INPROC_SERVER | CLSCTX_LOCAL_SERVER | CLSCTX_REMOTE_SERVER)
#define CLSCTX_ALL    (CLSCTX_INPROC_HANDLER | CLSCTX_SERVER)

/* DVASPECT (ms886976; Wtypes.h). */
typedef enum _tagDVASPECT {
    DVASPECT_CONTENT   = 1,
    DVASPECT_THUMBNAIL = 2,
    DVASPECT_ICON      = 4,
    DVASPECT_DOCPRINT  = 8
} DVASPECT;

/* TYMED (ms891298). */
typedef enum _tagTYMED {
    TYMED_NULL     = 0,
    TYMED_HGLOBAL  = 1,
    TYMED_FILE     = 2,
    TYMED_ISTREAM  = 4,
    TYMED_ISTORAGE = 8
} TYMED;

/* STGC (ms891270; Wtypes.h). */
typedef enum _tagSTGC {
    STGC_DEFAULT                 = 0,
    STGC_OVERWRITE               = 1,
    STGC_ONLYIFCURRENT           = 2,
    STGC_DANGEROUSLYCOMMITMERELYTODISKCACHE = 4
} STGC;

/* STGM (ms891273). */
enum {
    STGM_DIRECT         = 0x00000000L,
    STGM_READ           = 0x00000000L,
    STGM_FAILIFTHERE    = 0x00000000L,
    STGM_WRITE          = 0x00000001L,
    STGM_READWRITE      = 0x00000002L,
    STGM_SHARE_EXCLUSIVE= 0x00000010L,
    STGM_SHARE_DENY_WRITE = 0x00000020L,
    STGM_SHARE_DENY_READ  = 0x00000030L,
    STGM_SHARE_DENY_NONE  = 0x00000040L,
    STGM_CREATE         = 0x00001000L,
    STGM_PRIORITY       = 0x00040000L,
    STGM_CONVERT        = 0x00020000L,
    STGM_TRANSACTED     = 0x00010000L,
    STGM_SIMPLE         = 0x08000000L,
    STGM_DELETEONRELEASE= 0x04000000L,
    STGM_NOSCRATCH      = 0x00100000L,
    STGM_NOSNAPSHOT     = 0x00200000L,
    STGM_DIRECT_SWMR    = 0x00400000L
};

/* MKSYS (ms890786). */
typedef enum _tagMKSYS {
    MKSYS_NONE             = 0,
    MKSYS_GENERICCOMPOSITE = 1,
    MKSYS_FILEMONIKER      = 2,
    MKSYS_ANTIMONIKER      = 3,
    MKSYS_ITEMMONIKER      = 4,
    MKSYS_POINTERMONIKER   = 5,
    MKSYS_CLASSMONIKER     = 7,
    MKSYS_OBJREFMONIKER    = 8,
    MKSYS_SESSIONMONIKER   = 9
} MKSYS;

/* MKRREDUCE (ms890778). */
typedef enum _tagMKRREDUCE {
    MKRREDUCE_ONE          = 3 << 16,
    MKRREDUCE_TOUSER       = 2 << 16,
    MKRREDUCE_THROUGHUSER  = 1 << 16,
    MKRREDUCE_ALL          = 0
} MKRREDUCE;

/* BIND_FLAGS (ms886128). */
typedef enum _tagBIND_FLAGS {
    BIND_MAYBOTHERUSER     = 1,
    BIND_JUSTTESTEXISTENCE = 2
} BIND_FLAGS;

/* SYSKIND (ms891289). */
typedef enum _tagSYSKIND {
    SYS_WIN16 = 0,
    SYS_WIN32 = SYS_WIN16 + 1,
    SYS_MAC   = SYS_WIN32 + 1
} SYSKIND;

/* TYPEKIND (ms891302). */
typedef enum _tagTYPEKIND {
    TKIND_ENUM = 0,
    TKIND_RECORD,
    TKIND_MODULE,
    TKIND_INTERFACE,
    TKIND_DISPATCH,
    TKIND_COCLASS,
    TKIND_ALIAS,
    TKIND_UNION,
    TKIND_MAX
} TYPEKIND;

/* VARKIND (ms891679). */
typedef enum _tagVARKIND {
    VAR_PERINSTANCE = 0,
    VAR_STATIC      = VAR_PERINSTANCE + 1,
    VAR_CONST       = VAR_STATIC + 1,
    VAR_DISPATCH    = VAR_CONST + 1
} VARKIND;

/* CALLCONV (ms886161). */
typedef enum _tagCALLCONV {
    CC_CDECL      = 1,
    CC_MSCPASCAL  = 2,
    CC_PASCAL     = CC_MSCPASCAL,
    CC_MACPASCAL  = 3,
    CC_STDCALL    = 4,
    CC_RESERVED   = 5,
    CC_SYSCALL    = 6,
    CC_MPWCDECL   = 7,
    CC_MPWPASCAL  = 8,
    CC_MAX        = 9
} CALLCONV;

/* FUNCKIND (ms886987). */
typedef enum _tagFUNCKIND {
    FUNC_VIRTUAL     = 0,
    FUNC_PUREVIRTUAL,
    FUNC_NONVIRTUAL,
    FUNC_STATIC,
    FUNC_DISPATCH
} FUNCKIND;

/* INVOKEKIND (ms889336).  The page prints the members as aliases of
 * the DISPATCH_* constants; the CE corpus does not publish the
 * DISPATCH_* values, so the documented ordinal order is transcribed. */
typedef enum _tagINVOKEKIND {
    INVOKE_FUNC          = 0,   /* page: DISPATCH_METHOD */
    INVOKE_PROPERTYGET,         /* page: DISPATCH_PROPERTYGET */
    INVOKE_PROPERTYPUT,         /* page: DISPATCH_PROPERTYPUT */
    INVOKE_PROPERTYPUTREF       /* page: DISPATCH_PROPERTYPUTREF */
} INVOKEKIND;

/* FUNCFLAGS (ms886002). */
typedef enum _tagFUNCFLAGS {
    FUNCFLAG_FRESTRICTED       = 0x1,
    FUNCFLAG_FSOURCE           = 0x2,
    FUNCFLAG_FBINDABLE         = 0x4,
    FUNCFLAG_FREQUESTEDIT      = 0x8,
    FUNCFLAG_FDISPLAYBIND      = 0x10,
    FUNCFLAG_FDEFAULTBIND      = 0x20,
    FUNCFLAG_FHIDDEN           = 0x40,
    FUNCFLAG_FUSESGETLASTERROR = 0x80,
    FUNCFLAG_FDEFAULTCOLLELEM  = 0x100,
    FUNCFLAG_FUIDEFAULT        = 0x200,
    FUNCFLAG_FNONBROWSABLE     = 0x400,
    FUNCFLAG_FREPLACEABLE      = 0x800,
    FUNCFLAG_FIMMEDIATEBIND    = 0x1000
} FUNCFLAGS;

/* ADVF (ms886084). */
typedef enum _tagADVF {
    ADVF_NODATA          = 1,
    ADVF_PRIMEFIRST      = 2,
    ADVF_ONLYONCE        = 4,
    ADVFCACHE_NOHANDLER  = 8,
    ADVFCACHE_FORCEBUILTIN = 16,
    ADVFCACHE_ONSAVE     = 32,
    ADVF_DATAONSTOP      = 64
} ADVF;

/* TYPEFLAGS (ms891301). */
typedef enum _tagTYPEFLAGS {
    TYPEFLAG_FAPPOBJECT     = 0x0001,
    TYPEFLAG_FCANCREATE     = 0x0002,
    TYPEFLAG_FLICENSED      = 0x0004,
    TYPEFLAG_FPREDECLID     = 0x0008,
    TYPEFLAG_FHIDDEN        = 0x0010,
    TYPEFLAG_FCONTROL       = 0x0020,
    TYPEFLAG_FDUAL          = 0x0040,
    TYPEFLAG_FNONEXTENSIBLE = 0x0080,
    TYPEFLAG_FOLEAUTOMATION = 0x0100,
    TYPEFLAG_FRESTRICTED    = 0x0200,
    TYPEFLAG_FAGGREGATABLE  = 0x0400,
    TYPEFLAG_FREPLACEABLE   = 0x0800,
    TYPEFLAG_FDISPATCHABLE  = 0x1000,
    TYPEFLAG_FREVERSEBIND   = 0x2000
} TYPEFLAGS;

/* DATADIR (ms886961). */
typedef enum _tagDATADIR {
    DATADIR_GET = 1,
    DATADIR_SET = 2
} DATADIR;

/* DESCKIND (ms886963). */
typedef enum _tagDESCKIND {
    DESCKIND_NONE         = 0,
    DESCKIND_FUNCDESC,
    DESCKIND_VARDESC,
    DESCKIND_TYPECOMP,
    DESCKIND_IMPLICITAPPOBJ
} DESCKIND;

/* DVASPECT2 (ms886977; Ocidl.h). */
typedef enum _tagDVASPECT2 {
    DVASPECT_OPAQUE     = 16,
    DVASPECT_TRANSPARENT= 32
} DVASPECT2;

/* DVASPECTINFOFLAG (ms886979; Ocidl.h). */
typedef enum _tagDVASPECTINFOFLAG {
    DVASPECTINFOFLAG_CANOPTIMIZE = 1
} DVASPECTINFOFLAG;

/* DVEXTENTMODE (ms886981; Ocidl.h). */
typedef enum _tagDVEXTENTMODE {
    DVEXTENT_CONTENT   = 0,
    DVEXTENT_INTEGRAL  = DVEXTENT_CONTENT + 1
} DVEXTENTMODE;

/* HITRESULT (ms886993; Ocidl.h). */
typedef enum _tagHITRESULT {
    HITRESULT_OUTSIDE     = 0,
    HITRESULT_TRANSPARENT = 1,
    HITRESULT_CLOSE       = 2,
    HITRESULT_HIT         = 3
} HITRESULT;

/* VIEWSTATUS (ms892127; Ocidl.h). */
typedef enum _tagVIEWSTATUS {
    VIEWSTATUS_OPAQUE              = 1,
    VIEWSTATUS_SOLIDBKGND          = 2,
    VIEWSTATUS_DVASPECTOPAQUE      = 4,
    VIEWSTATUS_DVASPECTTRANSPARENT = 8
} VIEWSTATUS;

/* ------------------------------------------------------------------ */
/* COM interfaces (opaque).  The CE corpus publishes the documented   */
/* methods per interface but not vtable layouts, so each interface is */
/* an opaque pointer type; the documented methods are listed per      */
/* interface.  The LPX pointer aliases are the CE doc spellings.      */
/* ------------------------------------------------------------------ */
typedef struct IAdviseSink IAdviseSink;
typedef IAdviseSink *LPIAdviseSink;
typedef struct IBindCtx IBindCtx;
typedef IBindCtx *LPIBindCtx;
typedef IBindCtx *LPBC;   /* documented short spelling */
typedef struct IClassActivator IClassActivator;
typedef IClassActivator *LPIClassActivator;
typedef struct IClassFactory IClassFactory;
typedef IClassFactory *LPIClassFactory;
typedef struct IClassFactory2 IClassFactory2;
typedef IClassFactory2 *LPIClassFactory2;
typedef struct IClientSecurity IClientSecurity;
typedef IClientSecurity *LPIClientSecurity;
typedef struct IConnectionPoint IConnectionPoint;
typedef IConnectionPoint *LPIConnectionPoint;
typedef struct IConnectionPointContainer IConnectionPointContainer;
typedef IConnectionPointContainer *LPIConnectionPointContainer;
typedef struct ICreateErrorInfo ICreateErrorInfo;
typedef ICreateErrorInfo *LPICreateErrorInfo;
typedef struct ICreateTypeInfo ICreateTypeInfo;
typedef ICreateTypeInfo *LPICreateTypeInfo;
typedef struct ICreateTypeInfo2 ICreateTypeInfo2;
typedef ICreateTypeInfo2 *LPICreateTypeInfo2;
typedef struct ICreateTypeLib ICreateTypeLib;
typedef ICreateTypeLib *LPICreateTypeLib;
typedef struct ICreateTypeLib2 ICreateTypeLib2;
typedef ICreateTypeLib2 *LPICreateTypeLib2;
typedef struct IDataObject IDataObject;
typedef IDataObject *LPIDataObject;
typedef struct IDispatch IDispatch;
typedef IDispatch *LPIDispatch;
typedef struct IEnumConnectionPoints IEnumConnectionPoints;
typedef IEnumConnectionPoints *LPIEnumConnectionPoints;
typedef struct IEnumConnections IEnumConnections;
typedef IEnumConnections *LPIEnumConnections;
typedef struct IEnumFORMATETC IEnumFORMATETC;
typedef IEnumFORMATETC *LPIEnumFORMATETC;
typedef struct IEnumMoniker IEnumMoniker;
typedef IEnumMoniker *LPIEnumMoniker;
typedef struct IEnumSTATDATA IEnumSTATDATA;
typedef IEnumSTATDATA *LPIEnumSTATDATA;
typedef struct IEnumSTATSTG IEnumSTATSTG;
typedef IEnumSTATSTG *LPIEnumSTATSTG;
typedef struct IEnumString IEnumString;
typedef IEnumString *LPIEnumString;
typedef struct IEnumVARIANT IEnumVARIANT;
typedef IEnumVARIANT *LPIEnumVARIANT;
typedef struct IErrorInfo IErrorInfo;
typedef IErrorInfo *LPIErrorInfo;
typedef struct IErrorlog IErrorlog;
typedef IErrorlog *LPIErrorlog;
typedef struct IExternalConnection IExternalConnection;
typedef IExternalConnection *LPIExternalConnection;
typedef struct IFillLockBytes IFillLockBytes;
typedef IFillLockBytes *LPIFillLockBytes;
typedef struct IGlobalInterfaceTable IGlobalInterfaceTable;
typedef IGlobalInterfaceTable *LPIGlobalInterfaceTable;
typedef struct ILockBytes ILockBytes;
typedef ILockBytes *LPILockBytes;
typedef struct IMalloc IMalloc;
typedef IMalloc *LPIMalloc;
typedef IMalloc *LPMALLOC;   /* documented short spelling */
typedef struct IMallocSpy IMallocSpy;
typedef IMallocSpy *LPIMallocSpy;
typedef IMallocSpy *LPMALLOCSPY;   /* documented short spelling */
typedef struct IMarshal IMarshal;
typedef IMarshal *LPIMarshal;
typedef IMarshal *LPMARSHAL;   /* documented short spelling */
typedef struct IMessageFilter IMessageFilter;
typedef IMessageFilter *LPIMessageFilter;
typedef IMessageFilter *LPMESSAGEFILTER;   /* documented short spelling */
typedef struct IMoniker IMoniker;
typedef IMoniker *LPIMoniker;
typedef IMoniker *LPMONIKER;   /* documented short spelling */
typedef struct IMultiQI IMultiQI;
typedef IMultiQI *LPIMultiQI;
typedef struct IOleItemContainer IOleItemContainer;
typedef IOleItemContainer *LPIOleItemContainer;
typedef struct IPersistFile IPersistFile;
typedef IPersistFile *LPIPersistFile;
typedef struct IPersistPropertyBag IPersistPropertyBag;
typedef IPersistPropertyBag *LPIPersistPropertyBag;
typedef struct IPropertyBag IPropertyBag;
typedef IPropertyBag *LPIPropertyBag;
typedef struct IRunningObjectTable IRunningObjectTable;
typedef IRunningObjectTable *LPIRunningObjectTable;
typedef IRunningObjectTable *LPRUNNINGOBJECTTABLE;   /* documented short spelling */
typedef struct IStorage IStorage;
typedef IStorage *LPIStorage;
typedef struct IStream IStream;
typedef IStream *LPIStream;
typedef IStream *LPSTREAM;   /* documented short spelling */
typedef struct ISurrogate ISurrogate;
typedef ISurrogate *LPISurrogate;
typedef struct ITypeComp ITypeComp;
typedef ITypeComp *LPITypeComp;
typedef struct ITypeInfo ITypeInfo;
typedef ITypeInfo *LPITypeInfo;
typedef struct ITypeInfo2 ITypeInfo2;
typedef ITypeInfo2 *LPITypeInfo2;
typedef struct ITypeLib ITypeLib;
typedef ITypeLib *LPITypeLib;
typedef struct ITypeLib2 ITypeLib2;
typedef ITypeLib2 *LPITypeLib2;
typedef struct IUnknown IUnknown;
typedef IUnknown *LPIUnknown;
typedef IUnknown *LPUNKNOWN;   /* documented short spelling */
typedef struct IViewObjectEx IViewObjectEx;
typedef IViewObjectEx *LPIViewObjectEx;

/* IAdviseSink: documented methods (5 pages).
 *   ms887005 OnClose: void OnClose()
 *   ms887006 OnDataChange: void OnDataChange(FORMATETC* pFormatetc, STGMEDIUM* pStgmed)
 *   ms887007 OnRename: void OnRename(IMoniker* pmk)
 *   ms887008 OnSave: void OnSave()
 *   ms887009 OnViewChange: void OnViewChange(DWORD dwAspect, LONG lindex)
 */

/* IBindCtx: documented methods (10 pages).
 *   ms887010 EnumObjectParam: HRESULT EnumObjectParam(IEnumString** ppenum)
 *   ms887011 GetBindOptions: HRESULT GetBindOptions(BIND_OPTS* pbindopts)
 *   ms887012 GetObjectParam: HRESULT GetObjectParam(LPOLESTR pszKey, IUnknown** ppunk)
 *   ms887013 GetRunningObjectTable: HRESULT GetRunningObjectTable(IRunningObjectTable** pprot)
 *   ms887015 RegisterObjectBound: HRESULT RegisterObjectBound(IUnknown* punk)
 *   ms887016 RegisterObjectParam: HRESULT RegisterObjectParam(LPOLESTR pszKey, IUnknown* punk)
 *   ms887017 ReleaseBoundObjects: HRESULT ReleaseBoundObjects(void)
 *   ms887018 RevokeObjectBound: HRESULT RevokeObjectBound(IUnknown* punk)
 *   ms887019 RevokeObjectParam: HRESULT RevokeObjectParam(LPOLESTR pszKey)
 *   ms887020 SetBindOptions: HRESULT SetBindOptions(BIND_OPTS* pbindopts)
 */

/* IClassActivator: documented methods (1 pages).
 *   ms887268 GetClassObject: HRESULT GetClassObject(REFCLSID* pClassID, DWORD dwClsContext, LCID locale, REFIID riid, void** ppv)
 */

/* IClassFactory: documented methods (2 pages).
 *   ms887274 CreateInstance: HRESULT CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppvObject)
 *   ms887276 LockServer: HRESULT LockServer(BOOL fLock)
 */

/* IClassFactory2: documented methods (3 pages).
 *   ms887270 CreateInstanceLic: HRESULT CreateInstanceLic(IUnknown* pUnkOuter, IUnknown* pUnkReserved, REFIID riid, BSTR bstrKey, void**...
 *   ms887271 GetLicInfo: HRESULT GetLicInfo(LICINFO* pLicInfo)
 *   ms887273 RequestLicKey: HRESULT RequestLicKey(DWORD dwReserved, BSTR* pbstrKey)
 */

/* IClientSecurity: documented methods (3 pages).
 *   ms887277 CopyProxy: HRESULT CopyProxy(IUnknown* pProxy, IUnknown** ppCopy)
 *   ms887279 QueryBlanket: HRESULT QueryBlanket(IUnknown* pProxy, DWORD* pAuthnSvc, DWORD* pAuthzSvc, OLECHAR** pServerPrincName, DW...
 *   ms887280 SetBlanket: HRESULT SetBlanket(IUnknown* pProxy, DWORD dwAuthnSvc, DWORD dwAuthzSvc, OLECHAR* pServerPrincName, DWORD...
 */

/* IConnectionPoint: documented methods (5 pages).
 *   ms887281 Advise: HRESULT Advise(IUnknown* pUnk, DWORD* pdwCookie)
 *   ms887286 EnumConnections: HRESULT EnumConnections(IEnumConnections** ppEnum)
 *   ms887287 GetConnectionInterface: HRESULT GetConnectionInterface(IID* pIID)
 *   ms887288 GetConnectionPointContainer: HRESULT GetConnectionPointContainer(IConnectionPointContainer** ppCPC)
 *   ms887290 Unadvise: HRESULT Unadvise(DWORD dwCookie)
 */

/* IConnectionPointContainer: documented methods (2 pages).
 *   ms887283 EnumConnectionPoints: HRESULT EnumConnectionPoints(IEnumConnectionPoints** ppEnum)
 *   ms887284 FindConnectionPoint: HRESULT FindConnectionPoint(REFIID riid, IConnectionPoint** ppCP)
 */

/* ICreateErrorInfo: documented methods (5 pages).
 *   ms887295 SetDescription: HRESULT SetDescription(LPCOLESTR* szDescription)
 *   ms887296 SetGUID: HRESULT SetGUID(REFGUID rguid)
 *   ms887297 SetHelpContext: HRESULT SetHelpContext(DWORD dwHelpContext)
 *   ms887298 SetHelpFile: HRESULT SetHelpFile(LPCOLESTR szHelpFile)
 *   ms887299 SetSource: HRESULT SetSource(LPCOLESTR szSource)
 */

/* ICreateTypeInfo: documented methods (21 pages).
 *   ms887315 AddFuncDesc: HRESULT AddFuncDesc(unsigned int index, FUNCDESC * pFuncDesc)
 *   ms887316 AddImplType: HRESULT AddImplType(unsigned int index, HREFTYPE hRefType)
 *   ms887317 AddRefTypeInfo: HRESULT AddRefTypeInfo(ITypeInfo * pTInfo, HREFTYPE * phRefType)
 *   ms887318 AddVarDesc: HRESULT AddVarDesc(unsigned int index, VARDESC * pVarDesc)
 *   ms887319 DefineFuncAsDllEntry: HRESULT DefineFuncAsDllEntry(unsigned int index, OLECHAR * szDllName, OLECHAR * szProcName)
 *   ms887321 LayOut: HRESULT LayOut()
 *   ms887322 SetAlignment: HRESULT SetAlignment(unsigned short cbAlignment)
 *   ms887323 SetDocString: HRESULT SetDocString(OLECHAR * pStrDoc)
 *   ms887324 SetFuncAndParamNames: HRESULT SetFuncAndParamNames(unsigned int index, OLECHAR ** rgszNames, unsigned int cNames)
 *   ms887325 SetFuncDocString: HRESULT SetFuncDocString(unsigned int index, OLECHAR * szDocString)
 *   ms887326 SetFuncHelpContext: HRESULT SetFuncHelpContext(unsigned int index, unsigned long dwHelpContext)
 *   ms887327 SetGuid: HRESULT SetGuid(REFGUID guid)
 *   ms887328 SetHelpContext: HRESULT SetHelpContext(unsigned long dwHelpContext)
 *   ms887329 SetImplTypeFlags: HRESULT SetImplTypeFlags(unsigned int index, int implTypeFlags)
 *   ms887330 SetMops: HRESULT SetMops(unsigned int index, BSTR bstrMops)
 *   ms887331 SetTypeDescAlias: HRESULT SetTypeDescAlias(TYPEDESC * pTDescAlias)
 *   ms887332 SetTypeFlags: HRESULT SetTypeFlags(unsigned int uTypeFlags)
 *   ms887334 SetVarDocString: HRESULT SetVarDocString(unsigned int index, OLECHAR * szDocString)
 *   ms887335 SetVarHelpContext: HRESULT SetVarHelpContext(unsigned int index, unsigned long dwHelpContext)
 *   ms887336 SetVarName: HRESULT SetVarName(unsigned int index, OLECHAR * szName)
 *   ms887337 SetVersion: HRESULT SetVersion(unsigned short wMajorVerNum, unsigned short wMinorVerNum)
 */

/* ICreateTypeInfo2: documented methods (14 pages).
 *   ms887300 DeleteFuncDesc: HRESULT DeleteFuncDesc(unsigned int index)
 *   ms887301 DeleteFuncDescByMemId: HRESULT DeleteFuncDescByMemId(MEMBERID memid, INVOKEKIND invKind)
 *   ms887302 DeleteImplType: HRESULT DeleteImplType(unsigned int index)
 *   ms887303 DeleteVarDesc: HRESULT DeleteVarDesc(unsigned int index)
 *   ms887304 DeleteVarDescByMemId: HRESULT DeleteVarDescByMemId(MEMBERID memid)
 *   ms887306 SetCustData: HRESULT SetCustData(REFGUID guid, VARIANT* pVarVal)
 *   ms887307 SetFuncCustData: HRESULT SetFuncCustData(unsigned int index, REFGUID guid, VARIANT* pVarVal)
 *   ms887308 SetFuncHelpStringContext: HRESULT SetFuncHelpStringContext(unsigned int index, DWORD dwHelpStringContext)
 *   ms887309 SetHelpStringContext: HRESULT SetHelpStringContext(DWORD* dwHelpStringContext)
 *   ms887310 SetImplTypeCustData: HRESULT SetImplTypeCustData(unsigned int index, REFGUID guid, VARIANT* pVarVal)
 *   ms887311 SetName: HRESULT SetName(OLECHAR * szName)
 *   ms887312 SetParamCustData: HRESULT SetParamCustData(unsigned int indexFunc, unsigned int indexParam, REFGUID guid, VARIANT* pVarVal)
 *   ms887313 SetVarCustData: HRESULT SetVarCustData(unsigned int index, REFGUID guid, VARIANT* pVarVal)
 *   ms887314 SetVarHelpStringContext: HRESULT SetVarHelpStringContext(unsigned int index, DWORD dwHelpStringContext)
 */

/* ICreateTypeLib: documented methods (8 pages).
 *   ms887343 CreateTypeInfo: HRESULT CreateTypeInfo(OLECHAR * szName, TYPEKIND tkind, ICreateTypeInfo ** ppCTInfo)
 *   ms887345 SetGuid: HRESULT SetGuid(REFGUID guid)
 *   ms887346 SetHelpContext: HRESULT SetHelpContext(unsigned long dwHelpContext)
 *   ms887347 SetHelpFileName: HRESULT SetHelpFileName(OLECHAR * szHelpFileName)
 *   ms887348 SetLcid: HRESULT SetLcid(LCID lcid)
 *   ms887349 SetLibFlags: HRESULT SetLibFlags(unsigned int uLibFlags)
 *   ms887350 SetName: HRESULT SetName(OLECHAR * szName)
 *   ms887351 SetVersion: HRESULT SetVersion(unsigned short wMajorVerNum, unsigned short wMinorVerNum)
 */

/* ICreateTypeLib2: documented methods (4 pages).
 *   ms887338 DeleteTypeInfo: HRESULT DeleteTypeInfo(OLECHAR * szName)
 *   ms887340 SetCustData: HRESULT SetCustData(REFGUID guid, VARIANT* pVarVal)
 *   ms887341 SetHelpStringContext: HRESULT SetHelpStringContext(DWORD* dwHelpStringContext)
 *   ms887342 SetHelpStringDll: HRESULT SetHelpStringDll(LPOLESTR szFileName)
 */

/* IDataObject: documented methods (9 pages).
 *   ms887353 DAdvise: HRESULT DAdvise(FORMATETC* pFormatetc, DWORD advf, IAdviseSink* pAdvSink, DWORD* pdwConnection)
 *   ms887354 DUnadvise: HRESULT DUnadvise(DWORD dwConnection)
 *   ms887355 EnumDAdvise: HRESULT EnumDAdvise(IEnumSTATDATA** ppenumAdvise)
 *   ms887356 EnumFormatEtc: HRESULT EnumFormatEtc(DWORD dwDirection, IEnumFORMATETC** ppenumFormatetc)
 *   ms887357 GetCanonicalFormatEtc: HRESULT GetCanonicalFormatEtc(FORMATETC* pFormatetcIn, FORMATETC* pFormatetcOut)
 *   ms887358 GetData: HRESULT GetData(FORMATETC* pFormatetc, STGMEDIUM* pmedium)
 *   ms887359 GetDataHere: HRESULT GetDataHere(FORMATETC* pFormatetc, STGMEDIUM* pmedium)
 *   ms887360 QueryGetData: HRESULT QueryGetData(FORMATETC* pFormatetc)
 *   ms887361 SetData: HRESULT SetData(FORMATETC* pFormatetc, STGMEDIUM* pmedium, BOOL fRelease)
 */

/* IDispatch: documented methods (4 pages).
 *   ms887721 GetIDsOfNames: HRESULT GetIDsOfNames(REFIID riid, OLECHAR ** rgszNames, unsigned int cNames, LCID lcid, DISPID * rgDispId)
 *   ms887722 GetTypeInfo: HRESULT GetTypeInfo(unsigned int iTInfo, LCID lcid, ITypeInfo ** ppTInfo)
 *   ms887723 GetTypeInfoCount: HRESULT GetTypeInfoCount(unsigned int * pctinfo)
 *   ms887724 Invoke: HRESULT Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS * pDispParams, VARIAN...
 */

/* IEnumConnectionPoints: documented methods (4 pages).
 *   ms887727 Clone: HRESULT Clone(IEnumConnectionPoints** ppEnum)
 *   ms887729 Next: HRESULT Next(ULONG cConnections, IConnectionPoint** rgpcn, ULONG* pcFetched)
 *   ms887730 Reset: HRESULT Reset(void)
 *   ms887731 Skip: HRESULT Skip(ULONG cConnections)
 */

/* IEnumConnections: documented methods (4 pages).
 *   ms887732 Clone: HRESULT Clone(IEnumConnectionPoints** ppEnum)
 *   ms887734 Next: HRESULT Next(ULONG cConnections, CONNECTDATA** rgpcd, ULONG* pcFetched)
 *   ms887735 Reset: HRESULT Reset(void)
 *   ms887736 Skip: HRESULT Skip(ULONG cConnections)
 */

/* IEnumFORMATETC: documented methods (4 pages).
 *   ms887738 Clone: HRESULT Clone(IEnumFORMATETC** ppenum)
 *   ms887739 Next: HRESULT Next(ULONG celt, FORMATETC* rgelt, ULONG* pceltFetched)
 *   ms887740 Reset: HRESULT Reset(void)
 *   ms887741 Skip: HRESULT Skip(ULONG celt)
 */

/* IEnumMoniker: documented methods (4 pages).
 *   ms887742 Clone: HRESULT Clone(IEnumMoniker** ppenum)
 *   ms887744 Next: HRESULT Next(ULONG celt, IMoniker* rgelt, ULONG* pceltFetched)
 *   ms887745 Reset: HRESULT Reset(void)
 *   ms887746 Skip: HRESULT Skip(ULONG celt)
 */

/* IEnumSTATDATA: documented methods (4 pages).
 *   ms887747 Clone: HRESULT Clone(Ienum<ELT_T>** ppenum)
 *   ms887749 Next: HRESULT Next(ULONG celt, ELT_T[ ] rgelt, ULONG* pceltFetched)
 *   ms887750 Reset: HRESULT Reset(void)
 *   ms887751 Skip: HRESULT Skip(ULONG celt)
 */

/* IEnumSTATSTG: documented methods (4 pages).
 *   ms887752 Clone: HRESULT Clone(Ienum<ELT_T>** ppenum)
 *   ms887754 Next: HRESULT Next(ULONG celt, ELT_T[ ] rgelt, ULONG* pceltFetched)
 *   ms887755 Reset: HRESULT Reset(void)
 *   ms887756 Skip: HRESULT Skip(ULONG celt)
 */

/* IEnumString: documented methods (4 pages).
 *   ms887758 Clone: HRESULT Clone(IEnumString** ppenum)
 *   ms887759 Next: HRESULT Next(ULONG celt, LPOLESTR* rgelt, ULONG* pceltFetched)
 *   ms887760 Reset: HRESULT Reset(void)
 *   ms887761 Skip: HRESULT Skip(ULONG celt)
 */

/* IEnumVARIANT: documented methods (4 pages).
 *   ms887763 Clone: HRESULT Clone(IEnumVARIANT ** ppEnum)
 *   ms887765 Next: HRESULT Next(unsigned long celt, VARIANT * rgVar, unsigned long * pCeltFetched)
 *   ms887766 Reset: HRESULT Reset()
 *   ms887767 Skip: HRESULT Skip(unsigned long celt)
 */

/* IErrorInfo: documented methods (5 pages).
 *   ms887768 GetDescription: HRESULT GetDescription(BSTR* pBstrDescription)
 *   ms887769 GetGUID: HRESULT GetGUID(GUID* pGUID)
 *   ms887780 GetHelpContext: HRESULT GetHelpContext(DWORD* pdwHelpContext)
 *   ms887781 GetHelpFile: HRESULT GetHelpFile(BSTR* pBstrHelpFile)
 *   ms887782 GetSource: HRESULT GetSource(BSTR* pBstrSource)
 */

/* IErrorlog: documented methods (1 pages).
 *   ms886009 AddError: HRESULT AddError(LPCOLESTR pszPropName, EXCEPINFO* pExcepInfo)
 */

/* IExternalConnection: documented methods (2 pages).
 *   ms887785 AddConnection: HRESULT AddConnection(DWORD exconn, DWORD dwreserved)
 *   ms887786 ReleaseConnection: HRESULT ReleaseConnection(DWORD extconn, DWORD dwreserved, BOOL fLastReleaseCloses)
 */

/* IFillLockBytes: documented methods (4 pages).
 *   ms887788 FillAppend: HRESULT FillAppend(void const* pv, ULONG cb, ULONG* pcbWritten)
 *   ms887789 FillAt: HRESULT FillAt(ULARGE_INTEGER uIOffset, void const* pv, ULONG cb, ULONG* pcbWritten)
 *   ms887791 SetFillSize: HRESULT SetFillSize(ULARGE_INTEGER uISize)
 *   ms887792 Terminate: HRESULT Terminate(BOOL bCanceled)
 */

/* IGlobalInterfaceTable: documented methods (3 pages).
 *   ms887794 GetInterfaceFromGlobal: HRESULT GetInterfaceFromGlobal(DWORD dwCookie, REFIID riid, void** ppv)
 *   ms887795 RegisterInterfaceInGlobal: HRESULT RegisterInterfaceInGlobal(IUnknown* pUnk, REFIID riid, DWORD* pdwCookie)
 *   ms887796 RevokeInterfaceFromGlobal: HRESULT RevokeInterfaceFromGlobal(DWORD dwCookie)
 */

/* ILockBytes: documented methods (7 pages).
 *   ms887798 Flush: HRESULT Flush(void)
 *   ms887800 LockRegion: HRESULT LockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
 *   ms887801 ReadAt: HRESULT ReadAt(ULARGE_INTEGER ulOffset, void* pv, ULONG cb, ULONG* pcbRead)
 *   ms887802 SetSize: HRESULT SetSize(ULARGE_INTEGER cb)
 *   ms887803 Stat: HRESULT Stat(STATSTG* pstatstg, DWORD grfStatFlag)
 *   ms887804 UnlockRegion: HRESULT UnlockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
 *   ms887805 WriteAt: HRESULT WriteAt(ULARGE_INTEGER ulOffset, void const* pv, ULONG cb, ULONG* pcbWritten)
 */

/* IMalloc: documented methods (6 pages).
 *   ms887807 Alloc: void* Alloc(ULONG cb)
 *   ms887808 DidAlloc: int DidAlloc(void* pv)
 *   ms887809 Free: void Free(void* pv)
 *   ms887810 GetSize: ULONG GetSize(void* pv)
 *   ms887811 HeapMinimize: void HeapMinimize()
 *   ms887812 Realloc: void* Realloc(void* pv, ULONG cb)
 */

/* IMallocSpy: documented methods (12 pages).
 *   ms887814 PostAlloc: void* PostAlloc(void* pActual)
 *   ms887815 PostDidAlloc: int PostDidAlloc(void* pRequest, BOOL fSpyed, int fActual)
 *   ms887816 PostFree: void PostFree(BOOL fSpyed)
 *   ms887817 PostGetSize: ULONG PostGetSize(ULONG cbActual, BOOL fSpyed)
 *   ms887818 PostHeapMinimize: void PostHeapMinimize(void)
 *   ms887819 PostRealloc: void* PostRealloc(void* pActual, BOOL fSpyed)
 *   ms887820 PreAlloc: ULONG PreAlloc(ULONG cbRequest)
 *   ms887921 PreDidAlloc: void* PreDidAlloc(void* pRequest, BOOL fSpyed)
 *   ms887929 PreFree: void* PreFree(void* pRequest, BOOL fSpyed)
 *   ms887937 PreGetSize: void* PreGetSize(void* pRequest, BOOL fSpyed)
 *   ms887943 PreHeapMinimize: void PreHeapMinimize(void)
 *   ms887950 PreRealloc: ULONG PreRealloc(void* pRequest, ULONG cbRequest, void** ppNewRequest, BOOL fSpyed)
 */

/* IMarshal: documented methods (6 pages).
 *   ms887969 DisconnectObject: HRESULT DisconnectObject(DWORD dwReserved)
 *   ms887979 GetMarshalSizeMax: HRESULT GetMarshalSizeMax(REFIID riid, void* pv, DWORD dwDestContext, void* pvDestContext, DWORD mshlflag...
 *   ms887985 GetUnmarshalClass: HRESULT GetUnmarshalClass(REFIID riid, void* pv, DWORD dwDestContext, void* pvDestContext, DWORD mshlflag...
 *   ms889003 MarshalInterface: HRESULT MarshalInterface(IStream* pStm, REFIID riid, void* pv, DWORD dwDestContext, void* pvDestContext,...
 *   ms889299 ReleaseMarshalData: HRESULT ReleaseMarshalData(IStream* pStm)
 *   ms889306 UnmarshalInterface: HRESULT UnmarshalInterface(IStream* pStm, REFIID riid, void** ppv)
 */

/* IMessageFilter: documented methods (3 pages).
 *   ms889308 HandleInComingCall: DWORD HandleInComingCall(DWORD dwCallType, HTASK threadIDCaller, DWORD dwTickCount, LPINTERFACEINFO lpInt...
 *   ms889310 MessagePending: DWORD MessagePending(HTASK threadIDCallee, DWORD dwTickCount, DWORD dwPendingType)
 *   ms889311 RetryRejectedCall: DWORD RetryRejectedCall(HTASK threadIDCallee, DWORD dwTickCount, DWORD dwRejectType)
 */

/* IMoniker: documented methods (15 pages).
 *   ms889312 BindToObject: HRESULT BindToObject(IBindCtx* pbc, IMoniker* pmkToLeft, REFIID riidResult, void** ppvResult)
 *   ms889313 BindToStorage: HRESULT BindToStorage(IBindCtx* pbc, IMoniker* pmkToLeft, REFIID riid, void** ppvObj)
 *   ms889314 CommonPrefixWith: HRESULT CommonPrefixWith(IMoniker* pmkOther, IMoniker** ppmkPrefix)
 *   ms889316 ComposeWith: HRESULT ComposeWith(IMoniker* pmkRight, BOOL fOnlyIfNotGeneric, IMoniker** ppmkComposite)
 *   ms889317 Enum: HRESULT Enum(BOOL fForward, IEnumMoniker** ppenumMoniker)
 *   ms889318 GetDisplayName: HRESULT GetDisplayName(IBindCtx* pbc, IMoniker* pmkToLeft, LPOLESTR* ppszDisplayName)
 *   ms889319 GetTimeOfLastChange: HRESULT GetTimeOfLastChange(IBindCtx* pbc, IMoniker* pmkToLeft, FILETIME* pFileTime)
 *   ms889320 Hash: HRESULT Hash(DWORD* pdwHash)
 *   ms889321 Inverse: HRESULT Inverse(IMoniker** ppmk)
 *   ms889322 IsEqual: HRESULT IsEqual(IMoniker* pmkOtherMoniker)
 *   ms889323 IsRunning: HRESULT IsRunning(IBindCtx* pbc, IMoniker* pmkToLeft, IMoniker* pmkNewlyRunning)
 *   ms889324 IsSystemMoniker: HRESULT IsSystemMoniker(DWORD* pdwMksys)
 *   ms889326 ParseDisplayName: HRESULT ParseDisplayName(IBindCtx* pbc, IMoniker* pmkToLeft, LPOLESTR* pszDisplayName, ULONG* pchEaten, I...
 *   ms889327 Reduce: HRESULT Reduce(IBindCtx* pbc, DWORD dwReduceHowFar, IMoniker** ppmkToLeft, IMoniker** ppmkReduced)
 *   ms889328 RelativePathTo: HRESULT RelativePathTo(IMoniker* pmkOther, IMoniker** ppmkRelPath)
 */

/* IMultiQI: documented methods (1 pages).
 *   ms889331 QueryMultipleInterfaces: HRESULT QueryMultipleInterfaces(ULONG cMQIs, MULTI_QI* pMQIs)
 */

/* IOleItemContainer: documented methods (3 pages).
 *   ms889355 GetObject: HRESULT GetObject(LPOLESTR pszItem, DWORD dwSpeedNeeded, IBindCtx* pbc, REFIID riid, void** ppvObject)
 *   ms889356 GetObjectStorage: HRESULT GetObjectStorage(LPOLESTR pszItem, IBindCtx* pbc, REFIID riid, void** ppvStorage)
 *   ms889357 IsRunning: HRESULT IsRunning(LPOLESTR pszItem)
 */

/* IPersistFile: documented methods (2 pages).
 *   ms889394 GetCurFile: HRESULT GetCurFile(LPOLESTR* ppszFileName)
 *   ms889395 IsDirty: HRESULT IsDirty(void)
 */

/* IPersistPropertyBag: documented methods (3 pages).
 *   ms886021 InitNew: HRESULT InitNew(void)
 *   ms886038 Load: HRESULT Load(IPropertyBag* pPropBag, IErrorlog* pErrorLog)
 *   ms886047 Save: HRESULT Save(IPropertyBag* pPropBag, BOOL fClearDirty, BOOL fSaveAllProperties)
 */

/* IPropertyBag: documented methods (2 pages).
 *   ms886063 Read: HRESULT Read(LPCOLESTR pszPropName, VARIANT* pVar, IErrorlog* pErrorLog)
 *   ms886069 Write: HRESULT Write(LPCOLESTR pszPropName, VARIANT* pVar)
 */

/* IRunningObjectTable: documented methods (0 pages).
 *   (referenced by documented prototypes; no method pages in the corpus)
 */

/* IStorage: documented methods (0 pages).
 *   (referenced by documented prototypes; no method pages in the corpus)
 */

/* IStream: documented methods (0 pages).
 *   (referenced by documented prototypes; no method pages in the corpus)
 */

/* ISurrogate: documented methods (0 pages).
 *   (referenced by documented prototypes; no method pages in the corpus)
 */

/* ITypeComp: documented methods (0 pages).
 *   (referenced by documented prototypes; no method pages in the corpus)
 */

/* ITypeInfo: documented methods (19 pages).
 *   ms890484 AddressOfMember: HRESULT AddressOfMember(MEMBERID memid, INVOKEKIND invKind, VOID ** ppv)
 *   ms890488 CreateInstance: HRESULT CreateInstance(IUnknown * pUnkOuter, REFIID riid, VOID ** ppvObj)
 *   ms890493 GetContainingTypeLib: HRESULT GetContainingTypeLib(ITypeLib ** ppTLib, unsigned int * pIndex)
 *   ms890496 GetDllEntry: HRESULT GetDllEntry(MEMBERID memid, INVOKEKIND invKind, BSTR * pBstrDllName, BSTR * pBstrName, unsigned s...
 *   ms890501 GetDocumentation: HRESULT GetDocumentation(MEMBERID memid, BSTR * pBstrName, BSTR * pBstrDocString, unsigned long * pdwHelp...
 *   ms890506 GetFuncDesc: HRESULT GetFuncDesc(unsigned int index, FUNCDESC ** ppFuncDesc)
 *   ms890510 GetIDsOfNames: HRESULT GetIDsOfNames(OLECHAR ** rgszNames, unsigned int cNames, MEMBERID * pMemId)
 *   ms890517 GetImplTypeFlags: HRESULT GetImplTypeFlags(unsigned int index, int* pImplTypeFlags)
 *   ms890520 GetMops: HRESULT GetMops(MEMBERID memid, BSTR * pBstrMops)
 *   ms890524 GetNames: HRESULT GetNames(MEMBERID memid, BSTR * rgBstrNames, unsigned int cMaxNames, unsigned int * pcNames)
 *   ms890529 GetRefTypeInfo: HRESULT GetRefTypeInfo(HREFTYPE hRefType, ITypeInfo ** ppTInfo)
 *   ms890533 GetRefTypeOfImplType: HRESULT GetRefTypeOfImplType(unsigned int index, HREFTYPE * pRefType)
 *   ms890537 GetTypeAttr: HRESULT GetTypeAttr(TYPEATTR ** ppTypeAttr)
 *   ms890541 GetTypeComp: HRESULT GetTypeComp(ITypeComp ** ppTComp)
 *   ms890548 GetVarDesc: HRESULT GetVarDesc(unsigned int index, VARDESC ** ppVarDesc)
 *   ms890551 Invoke: HRESULT Invoke(VOID * pvInstance, MEMBERID memid, unsigned short wFlags, DISPPARAMS * pDispParams, VARIAN...
 *   ms890564 ReleaseFuncDesc: HRESULT ReleaseFuncDesc(FUNCDESC * pFuncDesc)
 *   ms890570 ReleaseTypeAttr: HRESULT ReleaseTypeAttr(TYPEATTR * pTypeAttr)
 *   ms890575 ReleaseVarDesc: HRESULT ReleaseVarDesc(VARDESC * pVarDesc)
 */

/* ITypeInfo2: documented methods (14 pages).
 *   ms890300 GetAllFuncCustData: HRESULT GetAllFuncCustData(unsigned int index, CUSTDATA* pCustData)
 *   ms890409 GetAllImplTypeCustData: HRESULT GetAllImplTypeCustData(unsigned int index, CUSTDATA* pCustData)
 *   ms890417 GetAllParamCustData: HRESULT GetAllParamCustData(unsigned int indexFunc, unsigned int indexParam, CUSTDATA* pCustData)
 *   ms890424 GetAllVarCustData: HRESULT GetAllVarCustData(unsigned int index, CUSTDATA* pCustData)
 *   ms890431 GetCustData: HRESULT GetCustData(REFGUID guid, VARIANT* pVarVal)
 *   ms890439 GetDocumentation2: HRESULT GetDocumentation2(MEMID memid, LCID lcid, BSTR * pbstrHelpString, unsigned long * pdwHelpStringCo...
 *   ms890446 GetFuncCustData: HRESULT GetFuncCustData(unsigned int index, REFGUID guid, VARIANT* pVarVal)
 *   ms890451 GetFuncIndexOfMemId: HRESULT GetFuncIndexOfMemId(MEMBERID memid, INVOKEKIND invKind, unsigned int* pFuncIndex)
 *   ms890455 GetImplTypeCustData: HRESULT GetImplTypeCustData(unsigned int index, REFGUID guid, VARIANT* pVarVal)
 *   ms890459 GetParamCustData: HRESULT GetParamCustData(unsigned int indexFunc, unsigned int indexParam, REFGUID guid, VARIANT* pVarVal)
 *   ms890464 GetTypeFlags: HRESULT GetTypeFlags(unsigned long* pTypeFlags)
 *   ms890468 GetTypeKind: HRESULT GetTypeKind(TYPEKIND* pTypeKind)
 *   ms890473 GetVarCustData: HRESULT GetVarCustData(unsigned int index, REFGUID guid, VARIANT* pVarVal)
 *   ms890476 GetVarIndexOfMemId: HRESULT GetVarIndexOfMemId(MEMBERID memid, unsigned int* pVarIndex)
 */

/* ITypeLib: documented methods (10 pages).
 *   ms890598 FindName: HRESULT FindName(OLECHAR * szNameBuf, unsigned long lHashVal, ITypeInfo ** ppTInfo, MEMBERID * rgMemId, u...
 *   ms890602 GetDocumentation: HRESULT GetDocumentation(int index, BSTR * pBstrName, BSTR * pBstrDocString, unsigned long * pdwHelpConte...
 *   ms890605 GetLibAttr: HRESULT GetLibAttr(TLIBATTR ** ppTLibAttrr)
 *   ms890610 GetTypeComp: HRESULT GetLibAttr(ITypeComp ** ppTComp)
 *   ms890614 GetTypeInfo: HRESULT GetTypeInfo(unsigned int index, ITypeInfo ** ppTInfo)
 *   ms890620 GetTypeInfoCount: HRESULT GetTypeInfoCount()
 *   ms890629 GetTypeInfoOfGuid: HRESULT GetTypeInfoOfGuid(REFGUID guid, ITypeInfo ** ppTinfo)
 *   ms890632 GetTypeInfoType: HRESULT GetTypeInfoType(unsigned int index, TYPEKIND * pTKind)
 *   ms890638 IsName: HRESULT IsName(OLECHAR * szNameBuf, unsigned long lHashVal, BOOL pfName)
 *   ms890649 ReleaseTLibAttr: HRESULT ReleaseTLibAttr(TLIBATTR * pTLibAttr)
 */

/* ITypeLib2: documented methods (4 pages).
 *   ms890578 GetAllCustData: HRESULT GetAllCustData(CUSTDATA* pCustData)
 *   ms890582 GetCustData: HRESULT GetCustData(REFGUID guid, VARIANT* pVarVal)
 *   ms890587 GetDocumentation2: HRESULT GetDocumentation2(in] int index, LCID lcid, BSTR * pbstrHelpString, unsigned long * pdwHelpString...
 *   ms890591 GetLibStatistics: HRESULT GetLibStatistics(unsigned long* pcUniqueNames, unsigned long* pcchUniqueNames)
 */

/* IUnknown: documented methods (3 pages).
 *   ms890658 AddRef: ULONG AddRef(void)
 *   ms890661 QueryInterface: HRESULT QueryInterface(REFIID iid, void** ppvObject)
 *   ms890669 Release: ULONG Release(void)
 */

/* IViewObjectEx: documented methods (5 pages).
 *   ms890692 GetNaturalExtent: HRESULT GetNaturalExtent(DWORD dwAspect, LONG lindex, DVTARGETDEVICE* ptd, HDC hicTargetDev, DVEXTENTINFO...
 *   ms890696 GetRect: HRESULT GetRect(DWORD dwAspect, LPRECTL pRect)
 *   ms890701 GetViewStatus: HRESULT GetViewStatus(DWORD* pdwStatus)
 *   ms890707 QueryHitPoint: HRESULT QueryHitPoint(DWORD dwAspect, LPRECT pRectBounds, POINTL ptlLoc, LONG lCloseHint, DWORD* pHitResult)
 *   ms890711 QueryHitRect: HRESULT QueryHitRect(DWORD dwAspect, LPRECT pRectBounds, LPRECT pRectLoc, LONG lCloseHint, DWORD* pHitRes...
 */

/* ------------------------------------------------------------------ */
/* OLE Automation types (Oaidl.h / Oleauto.h)                         */
/* ------------------------------------------------------------------ */

/* SAFEARRAYBOUND (ms892134). */
typedef struct _SAFEARRAYBOUND {
    unsigned long cElements;
    long          lLbound;
} SAFEARRAYBOUND;

/* SAFEARRAY (ms892133). */
typedef struct _SAFEARRAY {
    unsigned short cDims;
    unsigned short fFeatures;
    unsigned short cbElements;
    unsigned short cLocks;
    unsigned long  handle;
    void          *pvData;
    SAFEARRAYBOUND rgsabound[1];
} SAFEARRAY;

/* FADF_*: the SAFEARRAY page (ms892133). */
#define FADF_AUTO         0x0001
#define FADF_STATIC       0x0002
#define FADF_EMBEDDED     0x0004
#define FADF_FIXEDSIZE    0x0010
#define FADF_BSTR         0x0100
#define FADF_UNKNOWN      0x0200
#define FADF_DISPATCH     0x0400
#define FADF_VARIANT      0x0800
#define FADF_RESERVED     0xF0E8

/* VARIANT and VARIANTARG (ms891678): the page prints the union as
 * anonymous. */
typedef struct _tagVARIANT VARIANT;   /* forward (self-reference in the union) */

typedef struct _tagVARIANT {
    VARTYPE        vt;
    unsigned short wReserved1;
    unsigned short wReserved2;
    unsigned short wReserved3;
    union {
        unsigned char  bVal;
        short          iVal;
        long           lVal;
        float          fltVal;
        double         dblVal;
        VARIANT_BOOL   boolVal;
        SCODE          scode;
        CY             cyVal;
        DATE           date;
        BSTR           bstrVal;
        IUnknown      *punkVal;
        IDispatch     *pdispVal;
        SAFEARRAY     *parray;
        unsigned char *pbVal;
        short         *piVal;
        long          *plVal;
        float         *pfltVal;
        double        *pdblVal;
        VARIANT_BOOL  *pboolVal;
        SCODE         *pscode;
        CY            *pcyVal;
        DATE          *pdate;
        BSTR          *pbstrVal;
        IUnknown     **ppunkVal;
        IDispatch   **ppdispVal;
        SAFEARRAY   **pparray;
        VARIANT       *pvarVal;
        void          *byref;
    };
} VARIANT;
typedef struct _tagVARIANT VARIANTARG;   /* ms891678 */

/* DISPPARAMS (ms886970; Header: Oleauto.h). */
typedef struct _tagDISPPARAMS {
    VARIANTARG *rgvarg;
    DISPID     *rgdispidNamedArgs;
    unsigned int cArgs;
    unsigned int cNamedArgs;
} DISPPARAMS;

/* EXCEPINFO (ms886984). */
typedef struct _tagEXCEPINFO {
    unsigned short wCode;
    unsigned short wReserved;
    BSTR           bstrSource;
    BSTR           bstrDescription;
    BSTR           bstrHelpFile;
    unsigned long  dwHelpContext;
    void          *pvReserved;
    HRESULT (STDAPICALLTYPE *pfnDeferredFillIn)(struct _tagEXCEPINFO *);
    SCODE          scode;
} EXCEPINFO;

/* PARAMDATA (ms891225; Oleauto.h). */
typedef struct _tagPARAMDATA {
    OLECHAR *szName;
    VARTYPE  vtReturn;
} PARAMDATA;

/* METHODDATA (ms890768; Oleauto.h). */
typedef struct _tagMETHODDATA {
    OLECHAR *szName;
    PARAMDATA *ppData;
    DISPID   dispid;
    unsigned int iMeth;
    CALLCONV cc;
    unsigned int cArgs;
    unsigned short wFlags;
    VARTYPE  vtReturn;
} METHODDATA;

/* ------------------------------------------------------------------ */
/* Type library structures (Oaidl.h)                                  */
/* ------------------------------------------------------------------ */

/* TLIBATTR (ms891296). */
typedef struct _tagTLIBATTR {
    GUID   guid;
    LCID   lcid;
    SYSKIND syskind;
    unsigned short wMajorVerNum;
    unsigned short wMinorVerNum;
    unsigned short wLibFlags;
} TLIBATTR, *LPTLIBATTR;

/* TYPEDESC (ms891300).  The page prints the first union member twice
 * with garbage prefixes ("ESC", "tagTYPEDSC" archive artifacts); the
 * documented union is { TYPEDESC*, ARRAYDESC*, HREFTYPE }. */
typedef struct _tagTYPEDESC {
    union {
        struct _tagTYPEDESC *lptdesc;
        struct _tagARRAYDESC *lpadesc;
        HREFTYPE hreftype;
    } u;
    VARTYPE vt;
} TYPEDESC;

/* ARRAYDESC (ms886091). */
typedef struct _tagARRAYDESC {
    TYPEDESC tdescElem;
    unsigned short cDims;
    SAFEARRAYBOUND rgbounds[1];
} ARRAYDESC, *LPARRAYDESC;

/* IDLDESC (ms892132).  The page prints "};IDLDESC" -- the closing
 * brace is restored. */
typedef struct _tagIDLDESC {
    ULONG  dwReserved;
    USHORT wIDLFlags;
} IDLDESC, *LPIDLDESC;

/* PARAMDESC (ms891232).  PARAMDESCEX is opaque (no corpus page). */
typedef struct _tagPARAMDESC {
    LPPARAMDESCEX pparamdescex;
    USHORT        wParamFlags;
} PARAMDESC;

/* ELEMDESC (ms886983).  The page prints the alias as "ELEMDES"
 * (archive typo); the LPELEMDESC pointer alias names the full type. */
typedef struct _tagELEMDESC {
    TYPEDESC tdesc;
    union {
        IDLDESC   idldesc;
        PARAMDESC paramdesc;
    } u;
} ELEMDESC, *LPELEMDESC;

/* FUNCDESC (ms886986). */
typedef struct _tagFUNCDESC {
    MEMBERID memid;
    SCODE   *lprgscode;
    ELEMDESC *lprgelemdescParam;
    FUNCKIND funckind;
    INVOKEKIND invkind;
    CALLCONV callconv;
    short    cParams;
    short    cParamsOpt;
    short    oVft;
    short    cScodes;
    ELEMDESC elemdescFunc;
    WORD     wFuncFlags;
} FUNCDESC;

/* VARDESC (ms891630).  The page's terminating semicolon is missing;
 * "UNION_NAME(u)" expands to the member "u". */
typedef struct _tagVARDESC {
    MEMBERID memid;
    OLECHAR *lpstrSchema;
    union {
        ULONG   oInst;
        VARIANT *lpvarValue;
    } u;
    ELEMDESC elemdescVar;
    USHORT   wVarFlags;
    VARKIND  varkind;
} VARDESC, *LPVARDESC;

/* INTERFACEINFO (ms889334). */
typedef struct _tagINTERFACEINFO {
    LPUNKNOWN pUnk;
    IID       iid;
    WORD      wMethod;
} INTERFACEINFO, *LPINTERFACEINFO;

/* BINDPTR (ms886124). */
typedef union _tagBINDPTR {
    FUNCDESC *lpfuncdesc;
    VARDESC  *lpvardesc;
    ITypeComp *lptcomp;
} BINDPTR;

/* TYPEATTR (ms891299). */
typedef struct _tagTYPEATTR {
    GUID     guid;
    LCID     lcid;
    ULONG    dwReserved;
    MEMBERID memidConstructor;
    MEMBERID memidDestructor;
    OLECHAR *lpstrSchema;
    ULONG    cbSizeInstance;
    TYPEKIND typekind;
    unsigned short cFuncs;
    unsigned short cVars;
    unsigned short cImplTypes;
    unsigned short cbAlignment;
    unsigned short wTypeFlags;
    unsigned short wMajorVerNum;
    unsigned short wMinorVerNum;
    TYPEDESC tdescAlias;
    IDLDESC  idldescType;
} TYPEATTR, *LPTYPEATTR;

/* CUSTDATA / CUSTDATAITEM (ms886959 / ms886960). */
typedef struct _tagCUSTDATAITEM {
    GUID     guid;
    VARIANTARG varValue;
} CUSTDATAITEM, *LPCUSTDATAITEM;

typedef struct _tagCUSTDATA {
    ULONG          cCustData;
    LPCUSTDATAITEM prgCustData;
} CUSTDATA, *LPCUSTDATA;

/* SECURITY_ATTRIBUTES: winbase.h forward-declares it (the CE kernel
 * pages pass it by pointer) and the CE corpus has no standalone page
 * for it; BINDINFO (ms928761) embeds it by value, so the layout is
 * declared here in the form the official Win32 documentation
 * specifies (length / descriptor pointer / inherit flag; typedef
 * redefinition, same type). */
typedef struct _SECURITY_ATTRIBUTES {
    DWORD  nLength;
    LPVOID lpSecurityDescriptor;
    BOOL   bInheritHandle;
} SECURITY_ATTRIBUTES;

/* ------------------------------------------------------------------ */
/* OLE structures (Objidl.h / Wtypes.h)                               */
/* ------------------------------------------------------------------ */

/* COAUTHIDENTITY (ms886203; Wtypes.h). */
typedef struct _COAUTHIDENTITY {
    USHORT *User;
    ULONG   UserLength;
    USHORT *Domain;
    ULONG   DomainLength;
    USHORT *Password;
    ULONG   PasswordLength;
    ULONG   Flags;
} COAUTHIDENTITY;

/* COAUTHINFO (ms886208; Wtypes.h). */
typedef struct _COAUTHINFO {
    DWORD            dwAuthnSvc;
    DWORD            dwAuthzSvc;
    LPWSTR           pwszServerPrincName;
    DWORD            dwAuthnLevel;
    DWORD            dwImpersonationLevel;
    COAUTHIDENTITY  *pAuthIdentityData;
    DWORD            dwCapabilities;
} COAUTHINFO;

/* COSERVERINFO (ms886935; Wtypes.h). */
typedef struct _COSERVERINFO {
    DWORD       dwReserved1;
    LPWSTR      pwszName;
    COAUTHINFO *pAuthInfo;
    DWORD       dwReserved2;
} COSERVERINFO;

/* SOLE_AUTHENTICATION_SERVICE (ms891267). */
typedef struct _SOLE_AUTHENTICATION_SERVICE {
    DWORD    dwAuthnSvc;
    DWORD    dwAuthzSvc;
    OLECHAR *pPrincipalName;
    HRESULT  hr;
} SOLE_AUTHENTICATION_SERVICE;

/* MULTI_QI (ms890798). */
typedef struct _MULTI_QI {
    const IID *pIID;
    IUnknown  *pItf;
    HRESULT    hr;
} MULTI_QI;

/* DVTARGETDEVICE (ms886982). */
typedef struct _DVTARGETDEVICE {
    DWORD tdSize;
    WORD  tdDriverNameOffset;
    WORD  tdDeviceNameOffset;
    WORD  tdPortNameOffset;
    WORD  tdExtDevmodeOffset;
    BYTE  tdData;
} DVTARGETDEVICE;

/* FORMATETC (ms886985). */
typedef struct _FORMATETC {
    unsigned long    cfFormat;
    DVTARGETDEVICE  *ptd;
    unsigned long    dwAspect;
    long             lindex;
    unsigned long    tymed;
} FORMATETC, *LPFORMATETC;

/* STGMEDIUM (ms891275; the CE 5.0 page ms928939 prints MIDL
 * attributes, stripped here). */
typedef struct _tagSTGMEDIUM {
    unsigned long tymed;
    union {
        HBITMAP       hBitmap;
        HMETAFILEPICT hMetaFilePict;
        HENHMETAFILE  hEnhMetaFile;
        HGLOBAL       hGlobal;
        LPOLESTR      lpszFileName;
        IStream      *pstm;
        IStorage     *pstg;
    } u;
    IUnknown *pUnkForRelease;
} STGMEDIUM, *LPSTGMEDIUM;

/* STATSTG (ms891269). */
typedef struct _tagSTATSTG {
    LPOLESTR        pwcsName;
    DWORD           type;
    ULARGE_INTEGER  cbSize;
    FILETIME        mtime;
    FILETIME        ctime;
    FILETIME        atime;
    DWORD           grfMode;
    DWORD           grfLocksSupported;
    CLSID           clsid;
    DWORD           grfStateBits;
    DWORD           reserved;
} STATSTG;

/* BIND_OPTS (ms886131). */
typedef struct _tagBIND_OPTS {
    DWORD cbStruct;
    DWORD grfFlags;
    DWORD grfMode;
    DWORD dwTickCountDeadline;
} BIND_OPTS, *LPBIND_OPTS;

/* BIND_OPTS2 (ms886139). */
typedef struct _tagBIND_OPTS2 {
    DWORD          cbStruct;
    DWORD          grfFlags;
    DWORD          grfMode;
    DWORD          dwTickCountDeadline;
    DWORD          dwTrackFlags;
    DWORD          dwClassContext;
    LCID           locale;
    COSERVERINFO  *pServerInfo;
} BIND_OPTS2, *LPBIND_OPTS2;

/* BINDINFO (ms928761). */
typedef struct _tagBINDINFO {
    ULONG              cbSize;
    LPWSTR             szExtraInfo;
    STGMEDIUM          stgmedData;
    DWORD              grfBindInfoF;
    DWORD              dwBindVerb;
    LPWSTR             szCustomVerb;
    DWORD              cbStgmedData;
    DWORD              dwOptions;
    DWORD              dwOptionsFlags;
    DWORD              dwCodePage;
    SECURITY_ATTRIBUTES securityAttributes;
    IID                iid;
    IUnknown          *pUnk;
    DWORD              dwReserved;
} BINDINFO;

/* LICINFO (ms890747; Ocidl.h). */
typedef struct _tagLICINFO {
    ULONG cbLicInfo;
    BOOL  fRuntimeKeyAvail;
    BOOL  fLicVerified;
} LICINFO;

/* Ocidl.h structures. */
typedef struct _tagCONNECTDATA {   /* ms886466 */
    IUnknown *pUnk;
    DWORD     dwCookie;
} CONNECTDATA;

typedef struct _tagCONTROLINFO {   /* ms886467 */
    ULONG   cb;
    HACCEL  hAccel;
    USHORT  cAccel;
    DWORD   dwFlags;
} CONTROLINFO;

typedef struct _tagDVASPECTINFO {  /* ms886978: page prints "struct
                                    * STRUCT ... UNIT cb" (typos) */
    ULONG cb;
    DWORD dwFlags;
} DVASPECTINFO;

typedef struct _tagDVEXTENTINFO {  /* ms886980 */
    ULONG    cb;
    DWORD    dwExtentMode;
    SIZEL    sizelProposed;
} DVEXTENTINFO;

/* ------------------------------------------------------------------ */
/* Free functions                                                      */
/* ------------------------------------------------------------------ */

/* ---- OLE (ole32.dll) (84 functions) ---- */

/* ms886121 "BindMoniker" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT BindMoniker(LPMONIKER pmk, DWORD grfOpt, REFIID iidResult, LPVOID * ppvResult) AKARI_CE_NAME(BindMoniker);

/* ms886181 "CLSIDFromProgID" (Header: Objbase.h; Windows CE 2.10 and later).
 */
AKARI_CE_IMPORT HRESULT CLSIDFromProgID(LPCOLESTR lpszProgID, LPCLSID pclsid) AKARI_CE_NAME(CLSIDFromProgID);

/* ms886190 "CLSIDFromString" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT CLSIDFromString(LPOLESTR lpsz, LPCLSID pclsid) AKARI_CE_NAME(CLSIDFromString);

/* ms886201 "CoAddRefServerProcess" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT ULONG CoAddRefServerProcess(void) AKARI_CE_NAME(CoAddRefServerProcess);

/* ms886216 "CoCopyProxy" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoCopyProxy(IUnknown* pProxy, IUnknown** ppCopy) AKARI_CE_NAME(CoCopyProxy);

/* ms886221 "CoCreateFreeThreadedMarshaler" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoCreateFreeThreadedMarshaler(LPUNKNOWN punkOuter, LPUNKNOWN* ppunkMarshaler) AKARI_CE_NAME(CoCreateFreeThreadedMarshaler);

/* ms886229 "CoCreateGuid" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoCreateGuid(GUID* pguid) AKARI_CE_NAME(CoCreateGuid);

/* ms886232 "CoCreateInstance" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoCreateInstance(REFCLSID rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext, REFIID riid, LPVOID* ppv) AKARI_CE_NAME(CoCreateInstance);

/* ms886235 "CoCreateInstanceEx" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoCreateInstanceEx(REFCLSID rclsid, IUnknown* punkOuter, DWORD dwClsCtx, COSERVERINFO* pServerInfo, ULONG cmq, MULTI_QI* pResults) AKARI_CE_NAME(CoCreateInstanceEx);

/* ms886239 "CoDisconnectObject" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoDisconnectObject(IUnknown* pUnk, DWORD dwReserved) AKARI_CE_NAME(CoDisconnectObject);

/* ms886243 "CoFileTimeNow" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoFileTimeNow(FILETIME* lpFileTime) AKARI_CE_NAME(CoFileTimeNow);

/* ms886248 "CoFreeAllLibraries" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT void CoFreeAllLibraries(void) AKARI_CE_NAME(CoFreeAllLibraries);

/* ms886250 "CoFreeLibrary" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT void CoFreeLibrary(HINSTANCE hInst) AKARI_CE_NAME(CoFreeLibrary);

/* ms886254 "CoFreeUnusedLibraries" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT void CoFreeUnusedLibraries(void) AKARI_CE_NAME(CoFreeUnusedLibraries);

/* ms886256 "CoGetCallContext" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoGetCallContext(REFIID riid, void** ppInterface) AKARI_CE_NAME(CoGetCallContext);

/* ms886259 "CoGetClassObject" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoGetClassObject(REFCLSID rclsid, WORD dwClsContext, COSERVERINFO* pServerInfo, REFIID riid, LPVOID* ppv) AKARI_CE_NAME(CoGetClassObject);

/* ms886262 "CoGetCurrentProcess" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT DWORD CoGetCurrentProcess(void) AKARI_CE_NAME(CoGetCurrentProcess);

/* ms886267 "CoGetInstanceFromFile" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoGetInstanceFromFile(COSERVERINFO* pServerInfo, CLSID* pclsid, IUnknown* punkOuter, DWORD dwClsCtx, DWORD grfMode, OLECHAR* szName, ULONG cmq, MULTI_QI* rgmqResults) AKARI_CE_NAME(CoGetInstanceFromFile);

/* ms886271 "CoGetInstanceFromIStorage" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoGetInstanceFromIStorage(COSERVERINFO* pServerInfo, CLSID* pclsid, IUnknown* punkOuter, DWORD dwClsCtx, IStorage* pstg, ULONG cmq, MULTI_QI* rgmqResults) AKARI_CE_NAME(CoGetInstanceFromIStorage);

/* ms886275 "CoGetInterfaceAndReleaseStream" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoGetInterfaceAndReleaseStream(LPSTREAM pStm, REFIID riid, LPVOID* ppv) AKARI_CE_NAME(CoGetInterfaceAndReleaseStream);

/* ms886278 "CoGetMalloc" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoGetMalloc(DWORD dwMemContext, LPMALLOC* ppMalloc) AKARI_CE_NAME(CoGetMalloc);

/* ms886282 "CoGetMarshalSizeMax" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoGetMarshalSizeMax(ULONG* pulSize, REFIID riid, IUnknown* pUnk, DWORD dwDestContext, LPVOID pvDestContext, DWORD mshlflags) AKARI_CE_NAME(CoGetMarshalSizeMax);

/* ms886284 "CoGetObject" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoGetObject(LPCWSTR pszName, BIND_OPTS* pBindOptions, REFIID riid, void** ppv) AKARI_CE_NAME(CoGetObject);

/* ms886289 "CoGetPSClsid" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoGetPSClsid(REFIID riid, CLSID* pclsid) AKARI_CE_NAME(CoGetPSClsid);

/* ms886292 "CoGetStandardMarshal" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoGetStandardMarshal(REFIID riid, IUnknown* pUnk, DWORD dwDestContext, LPVOID pvDestContext, DWORD mshlflags, LPMARSHAL* ppMarshal) AKARI_CE_NAME(CoGetStandardMarshal);

/* ms886297 "CoGetTreatAsClass" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoGetTreatAsClass(REFCLSID clsidOld, LPCLSID pclsidNew) AKARI_CE_NAME(CoGetTreatAsClass);

/* ms886299 "CoImpersonateClient" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoImpersonateClient(void) AKARI_CE_NAME(CoImpersonateClient);

/* ms886303 "CoInitialize" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoInitialize(LPVOID pvReserved) AKARI_CE_NAME(CoInitialize);

/* ms886306 "CoInitializeEx" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoInitializeEx(LPVOID pvReserved, DWORD dwCoInit) AKARI_CE_NAME(CoInitializeEx);

/* ms886314 "CoInitializeSecurity" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoInitializeSecurity(PSECURITY_DESCRIPTOR pVoid, LONG cAuthSvc, SOLE_AUTHENTICATION_SERVICE* asAuthSvc, void* pReserved1, DWORD dwAuthnLevel, DWORD dwImpLevel, SOLE_AUTHENTICATION_LIST* pAuthList, DWORD dwCapabilities, void* pReserved3) AKARI_CE_NAME(CoInitializeSecurity);

/* ms886324 "CoIsHandlerConnected" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT BOOL CoIsHandlerConnected(LPUNKNOWN pUnk) AKARI_CE_NAME(CoIsHandlerConnected);

/* ms886335 "CoIsOle1Class" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT BOOL CoIsOle1Class(REFCLSID rclsid) AKARI_CE_NAME(CoIsOle1Class);

/* ms886346 "CoLoadLibrary" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HINSTANCE CoLoadLibrary(LPOLESTR lpszLibName, BOOL bAutoFree) AKARI_CE_NAME(CoLoadLibrary);

/* ms886357 "CoLockObjectExternal" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoLockObjectExternal(IUnknown* pUnk, BOOL fLock, BOOL fLastUnlockReleases) AKARI_CE_NAME(CoLockObjectExternal);

/* ms886365 "CoMarshalHresult" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoMarshalHresult(IStream* pStm, HRESULT hresult) AKARI_CE_NAME(CoMarshalHresult);

/* ms886456 "CoMarshalInterface" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoMarshalInterface(IStream* pStm, REFIID riid, IUnknown* pUnk, DWORD dwDestContext, void* pvDestContext, DWORD mshlflags) AKARI_CE_NAME(CoMarshalInterface);

/* ms886464 "CoMarshalInterThreadInterfaceInStream" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoMarshalInterThreadInterfaceInStream(REFIID riid, LPUNKNOWN pUnk, LPSTREAM* ppStm) AKARI_CE_NAME(CoMarshalInterThreadInterfaceInStream);

/* ms886468 "CoQueryAuthenticationServices" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoQueryAuthenticationServices(DWORD* pcAuthSvc, SOLE_AUTHENTICATION_SERVICE** asAuthSvc) AKARI_CE_NAME(CoQueryAuthenticationServices);

/* ms886469 "CoQueryClientBlanket" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoQueryClientBlanket(DWORD* pAuthnSvc, DWORD* pAuthzSvc, OLECHAR** pServerPrincName, DWORD* pAuthnLevel, DWORD* pImpLevel, RPC_AUTHZ_HANDLE* pPrivs, DWORD** pCapabilities) AKARI_CE_NAME(CoQueryClientBlanket);

/* ms886470 "CoQueryProxyBlanket" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoQueryProxyBlanket(IUnknown* pProxy, DWORD* pAuthnSvc, DWORD* pAuthzSvc, OLECHAR** pServerPrincName, DWORD* pAuthnLevel, DWORD* pImpLevel, RPC_AUTH_IDENTITY_HANDLE* ppAuthInfo, DWORD* pCapabilities) AKARI_CE_NAME(CoQueryProxyBlanket);

/* ms886471 "CoRegisterClassObject" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoRegisterClassObject(REFCLSID rclsid, IUnknown* pUnk, DWORD dwClsContext, DWORD flags, LPDWORD lpdwRegister) AKARI_CE_NAME(CoRegisterClassObject);

/* ms886472 "CoRegisterMallocSpy" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoRegisterMallocSpy(LPMALLOCSPY pMallocSpy) AKARI_CE_NAME(CoRegisterMallocSpy);

/* ms886491 "CoRegisterMessageFilter" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoRegisterMessageFilter(LPMESSAGEFILTER lpMessageFilter, LPMESSAGEFILTER* lplpMessageFilter) AKARI_CE_NAME(CoRegisterMessageFilter);

/* ms886499 "CoRegisterPSClsid" (Header: Objbase.h; Windows CE 3.0 and later).
 * Page artifact: printed prototype says CoRegisterPSCLsid; the documented title (and export name) is CoRegisterPSClsid.
 */
AKARI_CE_IMPORT HRESULT CoRegisterPSClsid(REFIID riid, REFCLSID rclsid) AKARI_CE_NAME(CoRegisterPSClsid);

/* ms886609 "CoRegisterSurrogate" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoRegisterSurrogate(ISurrogate* pSurrogate) AKARI_CE_NAME(CoRegisterSurrogate);

/* ms886724 "CoReleaseMarshalData" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoReleaseMarshalData(IStream* pStm) AKARI_CE_NAME(CoReleaseMarshalData);

/* ms886823 "CoReleaseServerProcess" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT ULONG CoReleaseServerProcess(void) AKARI_CE_NAME(CoReleaseServerProcess);

/* ms886929 "CoResumeClassObjects" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoResumeClassObjects(void) AKARI_CE_NAME(CoResumeClassObjects);

/* ms886931 "CoRevertToSelf" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoRevertToSelf(void) AKARI_CE_NAME(CoRevertToSelf);

/* ms886932 "CoRevokeClassObject" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoRevokeClassObject(DWORD dwRegister) AKARI_CE_NAME(CoRevokeClassObject);

/* ms886933 "CoRevokeMallocSpy" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoRevokeMallocSpy(void) AKARI_CE_NAME(CoRevokeMallocSpy);

/* ms886936 "CoSetProxyBlanket" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoSetProxyBlanket(IUnknown* pProxy, DWORD dwAuthnSvc, DWORD dwAuthzSvc, WCHAR* pServerPrincName, DWORD dwAuthnLevel, DWORD dwImpLevel, RPC_AUTH_IDENTITY_HANDLE pAuthInfo, DWORD dwCapabilities) AKARI_CE_NAME(CoSetProxyBlanket);

/* ms886937 "CoSuspendClassObjects" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoSuspendClassObjects(void) AKARI_CE_NAME(CoSuspendClassObjects);

/* ms886938 "CoSwitchCallContext" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoSwitchCallContext(IUnknown* pNewObject, IUnknown** ppOldObject) AKARI_CE_NAME(CoSwitchCallContext);

/* ms886939 "CoTaskMemAlloc" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT LPVOID CoTaskMemAlloc(ULONG cb) AKARI_CE_NAME(CoTaskMemAlloc);

/* ms886940 "CoTaskMemFree" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT void CoTaskMemFree(LPVOID pv) AKARI_CE_NAME(CoTaskMemFree);

/* ms886941 "CoTaskMemRealloc" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT LPVOID CoTaskMemRealloc(LPVOID pv, ULONG cb) AKARI_CE_NAME(CoTaskMemRealloc);

/* ms886942 "CoTreatAsClass" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoTreatAsClass(REFCLSID clsidOld, REFCLSID clsidNew) AKARI_CE_NAME(CoTreatAsClass);

/* ms886943 "CoUninitialize" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT void CoUninitialize(void) AKARI_CE_NAME(CoUninitialize);

/* ms886944 "CoUnmarshalHresult" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoUnmarshalHresult(LPSTREAM pStm, HRESULT* phresult) AKARI_CE_NAME(CoUnmarshalHresult);

/* ms886945 "CoUnmarshalInterface" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CoUnmarshalInterface(IStream* pStm, REFIID riid, void** ppv) AKARI_CE_NAME(CoUnmarshalInterface);

/* ms886946 "CreateAntiMoniker" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CreateAntiMoniker(LPMONIKER * ppmk) AKARI_CE_NAME(CreateAntiMoniker);

/* ms886947 "CreateBindCtx" (Header: Objbase.h; Windows CE 2.10 and later).
 */
AKARI_CE_IMPORT HRESULT CreateBindCtx(DWORD reserved, LPBC * ppbc) AKARI_CE_NAME(CreateBindCtx);

/* ms886948 "CreateClassMoniker" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CreateClassMoniker(REFCLSID rclsid, IMoniker** ppmk) AKARI_CE_NAME(CreateClassMoniker);

/* ms886950 "CreateFileMoniker" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CreateFileMoniker(LPCOLESTR lpszPathName, LPMONIKER * ppmk) AKARI_CE_NAME(CreateFileMoniker);

/* ms886951 "CreateGenericComposite" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CreateGenericComposite(LPMONIKER pmkFirst, LPMONIKER pmkRest, LPMONIKER * ppmkComposite) AKARI_CE_NAME(CreateGenericComposite);

/* ms886952 "CreateItemMoniker" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CreateItemMoniker(LPCOLESTR lpszDelim, LPCOLESTR lpszItem, LPMONIKER * ppmk) AKARI_CE_NAME(CreateItemMoniker);

/* ms886954 "CreatePointerMoniker" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT CreatePointerMoniker(LPUNKNOWN punk, LPMONIKER * ppmk) AKARI_CE_NAME(CreatePointerMoniker);

/* ms886973 "DllGetClassObject" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv) AKARI_CE_NAME(DllGetClassObject);

/* ms886988 "GetClassFile" (Header: Objbase.h; Windows CE 2.10 and later).
 */
AKARI_CE_IMPORT HRESULT GetClassFile(LPCWSTR szFileName, CLSID* pclsid) AKARI_CE_NAME(GetClassFile);

/* ms886991 "GetRunningObjectTable" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT GetRunningObjectTable(DWORD reserved, LPRUNNINGOBJECTTABLE* pprot) AKARI_CE_NAME(GetRunningObjectTable);

/* ms887797 "IIDFromString" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT IIDFromString(LPOLESTR lpsz, LPIID lpiid) AKARI_CE_NAME(IIDFromString);

/* ms890774 "MkParseDisplayName" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT MkParseDisplayName(LPBC pbc, LPCOLESTR szUserName, ULONG * pchEaten, LPMONIKER * ppmk) AKARI_CE_NAME(MkParseDisplayName);

/* ms890790 "MonikerCommonPrefixWith" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT MonikerCommonPrefixWith(LPMONIKER pmkThis, LPMONIKER pmkOther, LPMONIKER * ppmkCommon) AKARI_CE_NAME(MonikerCommonPrefixWith);

/* ms890794 "MonikerRelativePathTo" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT MonikerRelativePathTo(LPMONIKER pmkSrc, LPMONIKER pmkDest, LPMONIKER * ppmkRelPath, BOOL dwReserved) AKARI_CE_NAME(MonikerRelativePathTo);

/* ms891234 "ProgIDFromCLSID" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT HRESULT ProgIDFromCLSID(REFCLSID clsid, LPOLESTR* lplpszProgID) AKARI_CE_NAME(ProgIDFromCLSID);

/* ms891271 "StgCreateDocfile" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT StgCreateDocfile(const WCHAR* pwcsName, DWORD grfMode, DWORD reserved, IStorage** ppstgOpen) AKARI_CE_NAME(StgCreateDocfile);

/* ms891272 "StgCreateDocfileOnILockBytes" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT StgCreateDocfileOnILockBytes(ILockBytes* plkbyt, DWORD grfMode, DWORD reserved, IStorage** ppstgOpen) AKARI_CE_NAME(StgCreateDocfileOnILockBytes);

/* ms891276 "StgOpenStorage" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT StgOpenStorage(const WCHAR* pwcsName, IStorage* pstgPriority, DWORD grfMode, SNB snbExclude, DWORD reserved, IStorage** ppstgOpen) AKARI_CE_NAME(StgOpenStorage);

/* ms891277 "StgOpenStorageOnILockBytes" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT StgOpenStorageOnILockBytes(ILockBytes* plkbyt, IStorage* pStgPriority, DWORD grfMode, SNB snbExclude, DWORD reserved, IStorage** ppstgOpen) AKARI_CE_NAME(StgOpenStorageOnILockBytes);

/* ms891280 "StringFromCLSID" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT StringFromCLSID(REFCLSID rclsid, LPOLESTR* ppsz) AKARI_CE_NAME(StringFromCLSID);

/* ms891281 "StringFromGUID2" (Header: Objbase.h; Windows CE 2.0 and later).
 * Page artifact: printed form lacks a return type; "Return Values" says it returns the character count (int).
 */
AKARI_CE_IMPORT int StringFromGUID2(REFGUID rguid, LPOLESTR lpsz, int cbMax) AKARI_CE_NAME(StringFromGUID2);

/* ms891282 "StringFromIID" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT StringFromIID(REFIID rclsid, LPOLESTR* lplpsz) AKARI_CE_NAME(StringFromIID);

/* ms891304 "UpdateDCOMSettings" (Header: Objbase.h; Windows CE 3.0 and later).
 */
AKARI_CE_IMPORT void UpdateDCOMSettings(void) AKARI_CE_NAME(UpdateDCOMSettings);

/* ---- OLE Automation (oleaut32.dll) (223 functions) ---- */

/* ms886153 "BstrFromVector" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT BstrFromVector(SAFEARRAY * psa, BSTR * pbstr) AKARI_CE_NAME(BstrFromVector);

/* ms886949 "CreateErrorInfo" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT CreateErrorInfo(ICreateErrorInfo** pperrinfo) AKARI_CE_NAME(CreateErrorInfo);

/* ms886956 "CreateTypeLib2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT CreateTypeLib2(SYSKIND syskind, LPOLESTR szFile, ICreateTypeLib2** ppctlib) AKARI_CE_NAME(CreateTypeLib2);

/* ms886965 "DispGetIDsOfNames" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: "ItypeInfo" -> ITypeInfo.
 */
AKARI_CE_IMPORT HRESULT DispGetIDsOfNames(ITypeInfo* ptinfo, OLECHAR **rgszNames, unsigned int cNames, DISPID *rgdispid) AKARI_CE_NAME(DispGetIDsOfNames);

/* ms886966 "DispGetParam" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT DispGetParam(DISPPARAMS * pdispparams, unsigned int position, VARTYPE vtTarg, VARIANT * pvarResult, unsigned int * puArgErr) AKARI_CE_NAME(DispGetParam);

/* ms886969 "DispInvoke" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: page prints pexcepinfo by value; the parameter is documented as a pointer.
 */
AKARI_CE_IMPORT HRESULT DispInvoke(void *_this, ITypeInfo *ptinfo, DISPID dispidMember, unsigned short wFlags, DISPPARAMS *pparams, VARIANT *pvarResult, EXCEPINFO *pexcepinfo, unsigned int *puArgErr) AKARI_CE_NAME(DispInvoke);

/* ms886972 "DllCanUnloadNow" (Header: Objbase.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT DllCanUnloadNow(void) AKARI_CE_NAME(DllCanUnloadNow);

/* ms886989 "GetErrorInfo" (Header: Oleauto.h; Windows CE 2.10 and later).
 * Page artifact: "IerrorInfo" -> IErrorInfo.
 */
AKARI_CE_IMPORT HRESULT GetErrorInfo(DWORD dwReserved, IErrorInfo **pperrinfo) AKARI_CE_NAME(GetErrorInfo);

/* ms890751 "LoadRegTypeLib" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: missing comma between wVerMajor/wVerMinor restored.
 */
AKARI_CE_IMPORT HRESULT LoadRegTypeLib(REFGUID rguid, unsigned short wVerMajor, unsigned short wVerMinor, LCID lcid, ITypeLib **pptlib) AKARI_CE_NAME(LoadRegTypeLib);

/* ms890755 "LoadTypeLib" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT LoadTypeLib(OLECHAR * szFile, ITypeLib ** pptlib) AKARI_CE_NAME(LoadTypeLib);

/* ms891239 "RegisterTypeLib" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT RegisterTypeLib(ITypeLib * ptlib, OLECHAR * szFullPath, OLECHAR * szHelpDir) AKARI_CE_NAME(RegisterTypeLib);

/* ms891243 "SafeArrayAccessData" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayAccessData(SAFEARRAY * psa, void ** ppvData) AKARI_CE_NAME(SafeArrayAccessData);

/* ms891244 "SafeArrayAllocData" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayAllocData(SAFEARRAY * psa) AKARI_CE_NAME(SafeArrayAllocData);

/* ms891245 "SafeArrayAllocDescriptor" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayAllocDescriptor(unsigned int cDims, SAFEARRAY ** ppsaOut) AKARI_CE_NAME(SafeArrayAllocDescriptor);

/* ms891246 "SafeArrayCopy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayCopy(SAFEARRAY * psa, SAFEARRAY ** ppsaOut) AKARI_CE_NAME(SafeArrayCopy);

/* ms891247 "SafeArrayCopyData" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayCopyData(SAFEARRAY * psaSource, SAFEARRAY ** psaTarget) AKARI_CE_NAME(SafeArrayCopyData);

/* ms891248 "SafeArrayCreate" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: "SAFEARRRAYBOUND" (three R) -> SAFEARRAYBOUND.
 */
AKARI_CE_IMPORT HRESULT SafeArrayCreate(VARTYPE vt, unsigned int cDims, SAFEARRAYBOUND *rgsabound) AKARI_CE_NAME(SafeArrayCreate);

/* ms891250 "SafeArrayCreateVector" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayCreateVector(VARTYPE vt, long lLbound, unsigned int cElements) AKARI_CE_NAME(SafeArrayCreateVector);

/* ms891251 "SafeArrayDestroy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayDestroy(SAFEARRAY * psa) AKARI_CE_NAME(SafeArrayDestroy);

/* ms891252 "SafeArrayDestroyData" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayDestroyData(SAFEARRAY * psa) AKARI_CE_NAME(SafeArrayDestroyData);

/* ms891253 "SafeArrayDestroyDescriptor" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayDestroyDescriptor(SAFEARRAY * psa) AKARI_CE_NAME(SafeArrayDestroyDescriptor);

/* ms891254 "SafeArrayGetDim" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: page prints HRESULT; "Return Values" says the dimension count is returned.
 */
AKARI_CE_IMPORT ULONG SafeArrayGetDim(SAFEARRAY *psa) AKARI_CE_NAME(SafeArrayGetDim);

/* ms891255 "SafeArrayGetElement" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayGetElement(SAFEARRAY * psa, long * rgIndices, void * pv) AKARI_CE_NAME(SafeArrayGetElement);

/* ms891256 "SafeArrayGetElemsize" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: page prints HRESULT; "Return Values" says the element size is returned.
 */
AKARI_CE_IMPORT ULONG SafeArrayGetElemsize(SAFEARRAY *psa) AKARI_CE_NAME(SafeArrayGetElemsize);

/* ms891257 "SafeArrayGetLBound" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayGetLBound(SAFEARRAY * psa, unsigned int nDim, long * plLbound) AKARI_CE_NAME(SafeArrayGetLBound);

/* ms891258 "SafeArrayGetUBound" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayGetUBound(SAFEARRAY * psa, unsigned int nDim, long * plUbound) AKARI_CE_NAME(SafeArrayGetUBound);

/* ms891259 "SafeArrayLock" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayLock(SAFEARRAY * psa) AKARI_CE_NAME(SafeArrayLock);

/* ms891260 "SafeArrayPtrOfIndex" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayPtrOfIndex(SAFEARRAY * psa, long * rgIndices, void ** ppvData) AKARI_CE_NAME(SafeArrayPtrOfIndex);

/* ms891261 "SafeArrayPutElement" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayPutElement(SAFEARRAY * psa, long * rgIndices, void * pv) AKARI_CE_NAME(SafeArrayPutElement);

/* ms891262 "SafeArrayRedim" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayRedim(SAFEARRAY * psa, SAFEARRAYBOUND * psaboundNew) AKARI_CE_NAME(SafeArrayRedim);

/* ms891263 "SafeArrayUnaccessData" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayUnaccessData(SAFEARRAY * psa) AKARI_CE_NAME(SafeArrayUnaccessData);

/* ms891264 "SafeArrayUnlock" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SafeArrayUnlock(SAFEARRAY * psa) AKARI_CE_NAME(SafeArrayUnlock);

/* ms891266 "SetErrorInfo" (Header: Oleauto.h; Windows CE 1.0 and later).
 */
AKARI_CE_IMPORT HRESULT SetErrorInfo(DWORD dwReserved, IErrorInfo* perrinfo) AKARI_CE_NAME(SetErrorInfo);

/* ms891285 "SysAllocString" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT BSTR SysAllocString(OLECHAR * sz) AKARI_CE_NAME(SysAllocString);

/* ms891286 "SysAllocStringByteLen" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT BSTR SysAllocStringByteLen(char * psz, unsigned int len) AKARI_CE_NAME(SysAllocStringByteLen);

/* ms891287 "SysAllocStringLen" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT BSTR SysAllocStringLen(OLECHAR * pch, unsigned int cch) AKARI_CE_NAME(SysAllocStringLen);

/* ms891288 "SysFreeString" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SysFreeString(BSTR bstr) AKARI_CE_NAME(SysFreeString);

/* ms891290 "SysReAllocString" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SysReAllocString(BSTR * pbstr, OLECHAR * sz) AKARI_CE_NAME(SysReAllocString);

/* ms891291 "SysReAllocStringLen" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SysReAllocStringLen(BSTR * pbstr, OLECHAR * pch, unsigned int cch) AKARI_CE_NAME(SysReAllocStringLen);

/* ms891292 "SysStringByteLen" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SysStringByteLen(BSTR bstr) AKARI_CE_NAME(SysStringByteLen);

/* ms891293 "SysStringLen" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT SysStringLen(BSTR bstr) AKARI_CE_NAME(SysStringLen);

/* ms891294 "SystemTimeToVariantTime" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: page prints the parameter by value; the parameter is documented as a pointer.
 */
AKARI_CE_IMPORT int SystemTimeToVariantTime(LPSYSTEMTIME lpSystemTime, double *pvtime) AKARI_CE_NAME(SystemTimeToVariantTime);

/* ms891303 "UnRegisterTypeLib" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: missing comma between wVerMajor/wVerMinor restored; the page Link Library field is blank (archive artifact) -- Oleaut32.lib per the documented sibling registration APIs.
 */
AKARI_CE_IMPORT HRESULT UnRegisterTypeLib(REFGUID libID, unsigned short wVerMajor, unsigned short wVerMinor, LCID lcid, SYSKIND syskind) AKARI_CE_NAME(UnRegisterTypeLib);

/* ms891305 "VarBoolFromCy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromCy(CURRENCY cyIn, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromCy);

/* ms891306 "VarBoolFromDate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromDate(DATE dateIn, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromDate);

/* ms891307 "VarBoolFromDec" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromDec(DECIMAL* pdecIn, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromDec);

/* ms891308 "VarBoolFromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromDisp(IDispatch* pdispIn, LCID lcid, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromDisp);

/* ms891309 "VarBoolFromI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromI1(char cIn, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromI1);

/* ms891310 "VarBoolFromI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromI2(short sIn, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromI2);

/* ms891311 "VarBoolFromI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromI4(long lIn, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromI4);

/* ms891312 "VarBoolFromR4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromR4(float fltIn, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromR4);

/* ms891313 "VarBoolFromR8" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromR8(double dblIn, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromR8);

/* ms891314 "VarBoolFromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromStr(OLECHAR* strIn, LCID lcid, ULONG dwFlags, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromStr);

/* ms891315 "VarBoolFromUI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromUI1(BYTE bIn, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromUI1);

/* ms891316 "VarBoolFromUI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromUI2(USHORT uiIn, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromUI2);

/* ms891317 "VarBoolFromUI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBoolFromUI4(ULONG ulIn, BOOL* pboolOut) AKARI_CE_NAME(VarBoolFromUI4);

/* ms891318 "VarBstrFromBool" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBstrFromBool(BOOL boolIn, LCID lcid, ULONG dwFlags, BSTR pbstrOut) AKARI_CE_NAME(VarBstrFromBool);

/* ms891319 "VarBstrFromCy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBstrFromCy(CURRENCY cyIn, LCID lcid, ULONG dwFlags, BSTR pbstrOut) AKARI_CE_NAME(VarBstrFromCy);

/* ms891320 "VarBstrFromDate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBstrFromDate(DATE dateIn, LCID lcid, ULONG dwFlags, BSTR pbstrOut) AKARI_CE_NAME(VarBstrFromDate);

/* ms891321 "VarBstrFromDec" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBstrFromDec(DECIMAL* pdecIn, LCID lcid, ULONG dwFlags, BSTR* pbstrOut) AKARI_CE_NAME(VarBstrFromDec);

/* ms891322 "VarBstrFromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBstrFromDisp(IDispatch* pdispln, LCID lcid, ULONG dwFlags, BSTR pbstrOut) AKARI_CE_NAME(VarBstrFromDisp);

/* ms891323 "VarBstrFromI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBstrFromI1(char cIn, LCID lcid, ULONG dwFlags, BSTR pbstrOut) AKARI_CE_NAME(VarBstrFromI1);

/* ms891324 "VarBstrFromI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBstrFromI2(short iVal, LCID lcid, ULONG dwFlags, BSTR pbstrOut) AKARI_CE_NAME(VarBstrFromI2);

/* ms891325 "VarBstrFromI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBstrFromI4(long lIn, LCID lcid, ULONG dwFlags, BSTR pbstrOut) AKARI_CE_NAME(VarBstrFromI4);

/* ms891326 "VarBstrFromR4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBstrFromR4(float fltIn, LCID lcid, ULONG dwFlags, BSTR pbstrOut) AKARI_CE_NAME(VarBstrFromR4);

/* ms891327 "VarBstrFromR8" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBstrFromR8(double dblIn, LCID lcid, ULONG dwFlags, BSTR pbstrOut) AKARI_CE_NAME(VarBstrFromR8);

/* ms891328 "VarBstrFromUI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: printed prototype misnames the function and its output type; the title VarBstrFromUI1 and the documented Bstr-from-* 4-parameter form are used.
 */
AKARI_CE_IMPORT HRESULT VarBstrFromUI1(BYTE bIn, LCID lcid, ULONG dwFlags, BSTR pbstrOut) AKARI_CE_NAME(VarBstrFromUI1);

/* ms891329 "VarBstrFromUI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBstrFromUI2(USHORT uiIn, LCID lcid, ULONG dwFlags, BSTR pbstrOut) AKARI_CE_NAME(VarBstrFromUI2);

/* ms891330 "VarBstrFromUI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarBstrFromUI4(ULONG ulIn, LCID lcid, ULONG dwFlags, BSTR pbstrOut) AKARI_CE_NAME(VarBstrFromUI4);

/* ms891331 "VarCyFromBool" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromBool(BOOL boolIn, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromBool);

/* ms891465 "VarCyFromDate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromDate(DATE dateIn, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromDate);

/* ms891479 "VarCyFromDec" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromDec(DECIMAL* pdecIn, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromDec);

/* ms891485 "VarCyFromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromDisp(IDispatch* pdispIn, LCID lcid, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromDisp);

/* ms891500 "VarCyFromI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromI1(char cIn, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromI1);

/* ms891507 "VarCyFromI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromI2(short sIn, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromI2);

/* ms891510 "VarCyFromI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromI4(long lIn, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromI4);

/* ms891516 "VarCyFromR4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromR4(float fltIn, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromR4);

/* ms891523 "VarCyFromR8" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromR8(double dblIn, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromR8);

/* ms891532 "VarCyFromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromStr(OLECHAR* strIn, LCID lcid, ULONG dwFlags, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromStr);

/* ms891539 "VarCyFromUI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromUI1(BYTE bIn, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromUI1);

/* ms891548 "VarCyFromUI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromUI2(USHORT uiIn, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromUI2);

/* ms891557 "VarCyFromUI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarCyFromUI4(ULONG ulIn, CURRENCY* pcyOut) AKARI_CE_NAME(VarCyFromUI4);

/* ms891564 "VarDateFromBool" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromBool(BOOL boolIn, DATE* pdateOut) AKARI_CE_NAME(VarDateFromBool);

/* ms891578 "VarDateFromCy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromCy(CURRENCY cyIn, DATE* pdateOut) AKARI_CE_NAME(VarDateFromCy);

/* ms891584 "VarDateFromDec" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromDec(DECIMAL* pdecIn, DATE* pdateOut) AKARI_CE_NAME(VarDateFromDec);

/* ms891593 "VarDateFromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromDisp(IDispatch* pdispIn, LCID lcid, DATE* pdateOut) AKARI_CE_NAME(VarDateFromDisp);

/* ms891600 "VarDateFromI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromI1(char cIn, DATE* pdateOut) AKARI_CE_NAME(VarDateFromI1);

/* ms891606 "VarDateFromI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromI2(short sIn, DATE* pdateOut) AKARI_CE_NAME(VarDateFromI2);

/* ms891609 "VarDateFromI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromI4(long lIn, DATE* pdateOut) AKARI_CE_NAME(VarDateFromI4);

/* ms891610 "VarDateFromR4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromR4(float fltIn, DATE* pdateOut) AKARI_CE_NAME(VarDateFromR4);

/* ms891611 "VarDateFromR8" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromR8(double dblIn, DATE* pdateOut) AKARI_CE_NAME(VarDateFromR8);

/* ms891612 "VarDateFromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromStr(OLECHAR* strIn, LCID lcid, ULONG dwFlags, DATE* pdateOut) AKARI_CE_NAME(VarDateFromStr);

/* ms891613 "VarDateFromUdate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromUdate(UDATE* pudateIn, unsigned long* dwFlags, DATE* pdateOut) AKARI_CE_NAME(VarDateFromUdate);

/* ms891614 "VarDateFromUI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromUI1(unsigned char bIn, DATE* pdateOut) AKARI_CE_NAME(VarDateFromUI1);

/* ms891615 "VarDateFromUI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromUI2(unsigned short uiIn, DATE* pdateOut) AKARI_CE_NAME(VarDateFromUI2);

/* ms891616 "VarDateFromUI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDateFromUI4(unsigned long ulIn, DATE* pdateOut) AKARI_CE_NAME(VarDateFromUI4);

/* ms891617 "VarDecFromBool" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDecFromBool(BOOL boolIn, DECIMAL* pdecOut) AKARI_CE_NAME(VarDecFromBool);

/* ms891618 "VarDecFromCy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDecFromCy(CURRENCY cIn, DECIMAL* pdecOut) AKARI_CE_NAME(VarDecFromCy);

/* ms891619 "VarDecFromDate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDecFromDate(DATE dateIn, DECIMAL* pdecOut) AKARI_CE_NAME(VarDecFromDate);

/* ms891620 "VarDecFromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDecFromDisp(IDispatch* pdispIn, LCID lcid, DECIMAL* pdecOut) AKARI_CE_NAME(VarDecFromDisp);

/* ms891621 "VarDecFromI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDecFromI1(char cIn, DECIMAL* pdecOut) AKARI_CE_NAME(VarDecFromI1);

/* ms891622 "VarDecFromI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDecFromI2(short sIn, DECIMAL* pdecOut) AKARI_CE_NAME(VarDecFromI2);

/* ms891623 "VarDecFromI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDecFromI4(long lIn, DECIMAL* pdecOut) AKARI_CE_NAME(VarDecFromI4);

/* ms891624 "VarDecFromR4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDecFromR4(float fltIn, DECIMAL* pdecOut) AKARI_CE_NAME(VarDecFromR4);

/* ms891625 "VarDecFromR8" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDecFromR8(double dblIn, DECIMAL* pdecOut) AKARI_CE_NAME(VarDecFromR8);

/* ms891626 "VarDecFromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDecFromStr(OLECHAR* strIn, LCID lcid, ULONG dwFlags, DECIMAL* pdecOut) AKARI_CE_NAME(VarDecFromStr);

/* ms891627 "VarDecFromUI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDecFromUI1(BYTE bIn, DECIMAL* pdecOut) AKARI_CE_NAME(VarDecFromUI1);

/* ms891628 "VarDecFromUI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarDecFromUI2(USHORT uiIn, DECIMAL* pdecOut) AKARI_CE_NAME(VarDecFromUI2);

/* ms891629 "VarDecFromUI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: printed prototype says VarDecFromUI1 with a ULONG parameter; the title VarDecFromUI4 is the documented form.
 */
AKARI_CE_IMPORT HRESULT VarDecFromUI4(ULONG ulIn, DECIMAL *pdecOut) AKARI_CE_NAME(VarDecFromUI4);

/* ms891631 "VarI1FromBool" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromBool(BOOL boolIn, char* pcOut) AKARI_CE_NAME(VarI1FromBool);

/* ms891632 "VarI1FromCy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromCy(CURRENCY cyIn, char* pcOut) AKARI_CE_NAME(VarI1FromCy);

/* ms891633 "VarI1FromDate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromDate(DATE dateIn, char* pcOut) AKARI_CE_NAME(VarI1FromDate);

/* ms891634 "VarI1FromDec" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromDec(DECIMAL* pdecIn, char* pcOut) AKARI_CE_NAME(VarI1FromDec);

/* ms891635 "VarI1FromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromDisp(IDispatch* pdispIn, LCID lcid, char* pcOut) AKARI_CE_NAME(VarI1FromDisp);

/* ms891636 "VarI1FromI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromI2(short sIn, char* pcOut) AKARI_CE_NAME(VarI1FromI2);

/* ms891637 "VarI1FromI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromI4(long lIn, char* pcOut) AKARI_CE_NAME(VarI1FromI4);

/* ms891638 "VarI1FromR4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromR4(float fltIn, char* pcOut) AKARI_CE_NAME(VarI1FromR4);

/* ms891639 "VarI1FromR8" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromR8(double dblIn, char* pcOut) AKARI_CE_NAME(VarI1FromR8);

/* ms891640 "VarI1FromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromStr(BSTR strIn, LCID lcid, ULONG dwFlags, char* pcOut) AKARI_CE_NAME(VarI1FromStr);

/* ms891641 "VarI1FromUI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromUI1(BYTE bIn, char* pcOut) AKARI_CE_NAME(VarI1FromUI1);

/* ms891642 "VarI1FromUI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromUI2(USHORT uiIn, char* pcOut) AKARI_CE_NAME(VarI1FromUI2);

/* ms891643 "VarI1FromUI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI1FromUI4(ULONG ulIn, char* pcOut) AKARI_CE_NAME(VarI1FromUI4);

/* ms891644 "VarI2FromBool" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromBool(BOOL boolIn, short* psOut) AKARI_CE_NAME(VarI2FromBool);

/* ms891645 "VarI2FromCy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromCy(CURRENCY cyIn, short* psOut) AKARI_CE_NAME(VarI2FromCy);

/* ms891646 "VarI2FromDate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromDate(DATE dateIn, short* psOut) AKARI_CE_NAME(VarI2FromDate);

/* ms891647 "VarI2FromDec" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromDec(DECIMAL* pdecIn, short* psOut) AKARI_CE_NAME(VarI2FromDec);

/* ms891648 "VarI2FromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromDisp(IDispatch* pdispIn, LCID lcid, short* psOut) AKARI_CE_NAME(VarI2FromDisp);

/* ms891649 "VarI2FromI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromI1(CHAR cIn, short* psOut) AKARI_CE_NAME(VarI2FromI1);

/* ms891650 "VarI2FromI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromI4(LONG lIn, short* psOut) AKARI_CE_NAME(VarI2FromI4);

/* ms891651 "VarI2FromR4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromR4(float fltIn, short* psOut) AKARI_CE_NAME(VarI2FromR4);

/* ms891652 "VarI2FromR8" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromR8(double dblIn, short* psOut) AKARI_CE_NAME(VarI2FromR8);

/* ms891653 "VarI2FromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromStr(OLECHAR* strIn, LCID lcid, ULONG dwFlags, short* psOut) AKARI_CE_NAME(VarI2FromStr);

/* ms891654 "VarI2FromUI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromUI1(BYTE bIn, short* psOut) AKARI_CE_NAME(VarI2FromUI1);

/* ms891655 "VarI2FromUI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromUI2(USHORT uiIn, short* psOut) AKARI_CE_NAME(VarI2FromUI2);

/* ms891656 "VarI2FromUI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI2FromUI4(ULONG ulIn, short* psOut) AKARI_CE_NAME(VarI2FromUI4);

/* ms891657 "VarI4FromBool" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI4FromBool(BOOL boolIn, long* plOut) AKARI_CE_NAME(VarI4FromBool);

/* ms891658 "VarI4FromCy" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: "CURRENTY" -> CURRENCY.
 */
AKARI_CE_IMPORT HRESULT VarI4FromCy(CURRENCY cyIn, long *plOut) AKARI_CE_NAME(VarI4FromCy);

/* ms891660 "VarI4FromDec" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI4FromDec(DECIMAL* pdecIn, long* plOut) AKARI_CE_NAME(VarI4FromDec);

/* ms891661 "VarI4FromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI4FromDisp(IDispatch* pdispIn, LCID lcid, long* plOut) AKARI_CE_NAME(VarI4FromDisp);

/* ms891662 "VarI4FromI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI4FromI1(CHAR cIn, long* plOut) AKARI_CE_NAME(VarI4FromI1);

/* ms891663 "VarI4FromI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: printed prototype says VarI4FromUI1 with a short parameter; the title VarI4FromI2 is the documented form.
 */
AKARI_CE_IMPORT HRESULT VarI4FromI2(short sIn, long *plOut) AKARI_CE_NAME(VarI4FromI2);

/* ms891664 "VarI4FromR4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI4FromR4(float fltIn, long* plOut) AKARI_CE_NAME(VarI4FromR4);

/* ms891665 "VarI4FromR8" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI4FromR8(double dblIn, long* plOut) AKARI_CE_NAME(VarI4FromR8);

/* ms891667 "VarI4FromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI4FromStr(OLECHAR* strIn, LCID lcid, ULONG dwFlags, long* plOut) AKARI_CE_NAME(VarI4FromStr);

/* ms891668 "VarI4FromUI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI4FromUI1(BYTE bIn, long* plOut) AKARI_CE_NAME(VarI4FromUI1);

/* ms891669 "VarI4FromUI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI4FromUI2(USHORT uiIn, long* plOut) AKARI_CE_NAME(VarI4FromUI2);

/* ms891670 "VarI4FromUI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarI4FromUI4(ULONG ulIn, long* plOut) AKARI_CE_NAME(VarI4FromUI4);

/* ms891671 "VariantChangeType" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VariantChangeType(VARIANTARG * pvargDest, VARIANTARG * pvarSrc, unsigned short wFlags, VARTYPE vt) AKARI_CE_NAME(VariantChangeType);

/* ms891672 "VariantChangeTypeEx" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VariantChangeTypeEx(VARIANTARG * pvargDest, VARIANTARG * pvarSrc, LCID lcid, unsigned short wFlags, VARTYPE vt) AKARI_CE_NAME(VariantChangeTypeEx);

/* ms891673 "VariantClear" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VariantClear(VARIANTARG * pvarg) AKARI_CE_NAME(VariantClear);

/* ms891674 "VariantCopy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VariantCopy(VARIANTARG * pvargDest, VARIANTARG * pvargSrc) AKARI_CE_NAME(VariantCopy);

/* ms891675 "VariantCopyInd" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VariantCopyInd(VARIANT * pvarDest, VARIANTARG * pvargSrc) AKARI_CE_NAME(VariantCopyInd);

/* ms891676 "VariantInit" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VariantInit(VARIANTARG * pvarg) AKARI_CE_NAME(VariantInit);

/* ms891677 "VariantTimeToSystemTime" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT int VariantTimeToSystemTime(double vtime, LPSYSTEMTIME lpSystemTime) AKARI_CE_NAME(VariantTimeToSystemTime);

/* ms891680 "VarNumFromParseNum" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarNumFromParseNum(NUMPARSE* pnumprs, unsigned char* rgbDig, unsigned long dwVtBits, VARIANT* pvar) AKARI_CE_NAME(VarNumFromParseNum);

/* ms891681 "VarParseNumFromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarParseNumFromStr(OLECHAR* strIn, LCID lcid, unsigned long dwFlags, NUMPARSE* pnumprs, unsigned char* rgbDig) AKARI_CE_NAME(VarParseNumFromStr);

/* ms891682 "VarR4FromBool" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR4FromBool(BOOL boolIn, float* pfltOut) AKARI_CE_NAME(VarR4FromBool);

/* ms891683 "VarR4FromCy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR4FromCy(CURRENCY cyIn, float* pfltOut) AKARI_CE_NAME(VarR4FromCy);

/* ms891684 "VarR4FromDate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR4FromDate(DATE dateIn, float* pfltOut) AKARI_CE_NAME(VarR4FromDate);

/* ms891685 "VarR4FromDec" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR4FromDec(DECIMAL* pdecIn, float* pfltOut) AKARI_CE_NAME(VarR4FromDec);

/* ms891686 "VarR4FromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR4FromDisp(IDispatch* pdispIn, LCID lcid, float* pfltOut) AKARI_CE_NAME(VarR4FromDisp);

/* ms891687 "VarR4FromI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: "DOUBLE cIn" -> char cIn (the I1 form).
 */
AKARI_CE_IMPORT HRESULT VarR4FromI1(char cIn, float *pfltOut) AKARI_CE_NAME(VarR4FromI1);

/* ms891688 "VarR4FromI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR4FromI2(short sIn, float* pfltOut) AKARI_CE_NAME(VarR4FromI2);

/* ms891689 "VarR4FromI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR4FromI4(long lIn, float* pfltOut) AKARI_CE_NAME(VarR4FromI4);

/* ms891690 "VarR4FromR8" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: "DOUBLE dblIn" -> double dblIn.
 */
AKARI_CE_IMPORT HRESULT VarR4FromR8(double dblIn, float *pfltOut) AKARI_CE_NAME(VarR4FromR8);

/* ms891691 "VarR4FromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: "Ulong" -> ULONG.
 */
AKARI_CE_IMPORT HRESULT VarR4FromStr(OLECHAR *strIn, LCID lcid, ULONG dwFlags, float *pfltOut) AKARI_CE_NAME(VarR4FromStr);

/* ms891700 "VarR4FromUI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR4FromUI1(BYTE bIn, float* pfltOut) AKARI_CE_NAME(VarR4FromUI1);

/* ms891773 "VarR4FromUI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR4FromUI2(USHORT uiIn, float* pfltOut) AKARI_CE_NAME(VarR4FromUI2);

/* ms891776 "VarR4FromUI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR4FromUI4(ULONG ulIn, float* pfltOut) AKARI_CE_NAME(VarR4FromUI4);

/* ms891785 "VarR8FromBool" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR8FromBool(BOOL boolIn, double* pdblOut) AKARI_CE_NAME(VarR8FromBool);

/* ms891790 "VarR8FromCy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR8FromCy(CURRENCY cyIn, double* pdblOut) AKARI_CE_NAME(VarR8FromCy);

/* ms891796 "VarR8FromDate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR8FromDate(DATE dateIn, double* pdblOut) AKARI_CE_NAME(VarR8FromDate);

/* ms891802 "VarR8FromDec" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR8FromDec(DECIMAL* pdecIn, double* pdblOut) AKARI_CE_NAME(VarR8FromDec);

/* ms891810 "VarR8FromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: "VarR8FromDips" -> VarR8FromDisp.
 */
AKARI_CE_IMPORT HRESULT VarR8FromDisp(IDispatch *pdispIn, LCID lcid, double *pdblOut) AKARI_CE_NAME(VarR8FromDisp);

/* ms891812 "VarR8FromI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR8FromI1(char cIn, double* pdblOut) AKARI_CE_NAME(VarR8FromI1);

/* ms891816 "VarR8FromI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR8FromI2(short sIn, double* pdblOut) AKARI_CE_NAME(VarR8FromI2);

/* ms891823 "VarR8FromI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR8FromI4(long lIn, double* pdblOut) AKARI_CE_NAME(VarR8FromI4);

/* ms891825 "VarR8FromR4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR8FromR4(float fltIn, double* pdblOut) AKARI_CE_NAME(VarR8FromR4);

/* ms891831 "VarR8FromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR8FromStr(OLECHAR* strIn, LCID lcid, ULONG dwFlags, double* pdblOut) AKARI_CE_NAME(VarR8FromStr);

/* ms891836 "VarR8FromUI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR8FromUI1(BYTE bIn, double* pdblOut) AKARI_CE_NAME(VarR8FromUI1);

/* ms891839 "VarR8FromUI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarR8FromUI2(USHORT uiIn, double* pdblOut) AKARI_CE_NAME(VarR8FromUI2);

/* ms891846 "VarR8FromUI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 * Page artifact: page title misprints VarR8FromI4; the printed ULONG parameter is the UI4 form.
 */
AKARI_CE_IMPORT HRESULT VarR8FromUI4(ULONG ulIn, double *pdblOut) AKARI_CE_NAME(VarR8FromUI4);

/* ms891856 "VarUdateFromDate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUdateFromDate(DATE* dateIn, unsigned long dwFlags, UDATE* pudateOut) AKARI_CE_NAME(VarUdateFromDate);

/* ms891863 "VarUI1FromBool" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromBool(BOOL boolIn, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromBool);

/* ms891867 "VarUI1FromCy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromCy(CURRENCY cyIn, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromCy);

/* ms891869 "VarUI1FromDate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromDate(DATE dateIn, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromDate);

/* ms891876 "VarUI1FromDec" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromDec(DECIMAL* pdecIn, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromDec);

/* ms891887 "VarUI1FromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromDisp(IDispatch* pdispIn, LCID lcid, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromDisp);

/* ms891893 "VarUI1FromI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromI1(char cIn, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromI1);

/* ms891901 "VarUI1FromI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromI2(short sIn, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromI2);

/* ms891905 "VarUI1FromI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromI4(long lIn, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromI4);

/* ms891912 "VarUI1FromR4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromR4(float fltIn, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromR4);

/* ms891915 "VarUI1FromR8" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromR8(double dblIn, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromR8);

/* ms891922 "VarUI1FromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromStr(OLECHAR* strIn, LCID lcid, ULONG dwFlags, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromStr);

/* ms891926 "VarUI1FromUI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromUI2(USHORT uiIn, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromUI2);

/* ms891930 "VarUI1FromUI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI1FromUI4(ULONG ulIn, BYTE* pbOut) AKARI_CE_NAME(VarUI1FromUI4);

/* ms891935 "VarUI2FromBool" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromBool(BOOL boolIn, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromBool);

/* ms891940 "VarUI2FromCy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromCy(CURRENCY cyIn, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromCy);

/* ms891947 "VarUI2FromDate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromDate(DATE dateIn, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromDate);

/* ms891951 "VarUI2FromDec" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromDec(DECIMAL* pdecIn, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromDec);

/* ms891955 "VarUI2FromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromDisp(IDispatch* pdispIn, LCID lcid, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromDisp);

/* ms891961 "VarUI2FromI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromI1(char cIn, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromI1);

/* ms891966 "VarUI2FromI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromI2(short uiIn, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromI2);

/* ms891970 "VarUI2FromI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromI4(long lIn, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromI4);

/* ms891981 "VarUI2FromR4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromR4(float fltIn, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromR4);

/* ms891986 "VarUI2FromR8" (Header: Oleauto.h; Windows CE 2.12 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromR8(double dblIn, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromR8);

/* ms891993 "VarUI2FromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromStr(BSTR strIn, LCID lcid, ULONG dwFlags, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromStr);

/* ms891998 "VarUI2FromUI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromUI1(BYTE bIn, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromUI1);

/* ms892004 "VarUI2FromUI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI2FromUI4(ULONG ulIn, USHORT* puiOut) AKARI_CE_NAME(VarUI2FromUI4);

/* ms892011 "VarUI4FromBool" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromBool(BOOL boolIn, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromBool);

/* ms892020 "VarUI4FromCy" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromCy(CURRENCY cyIn, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromCy);

/* ms892026 "VarUI4FromDate" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromDate(DATE dateIn, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromDate);

/* ms892103 "VarUI4FromDec" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromDec(DECIMAL* pdecIn, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromDec);

/* ms892107 "VarUI4FromDisp" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromDisp(IDispatch* pdispIn, LCID lcid, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromDisp);

/* ms892116 "VarUI4FromI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromI1(char cIn, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromI1);

/* ms892117 "VarUI4FromI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromI2(short sIn, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromI2);

/* ms892118 "VarUI4FromI4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromI4(long lIn, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromI4);

/* ms892119 "VarUI4FromR4" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromR4(float fltIn, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromR4);

/* ms892120 "VarUI4FromR8" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromR8(double dblIn, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromR8);

/* ms892121 "VarUI4FromStr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromStr(BSTR strIn, LCID lcid, ULONG dwFlags, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromStr);

/* ms892122 "VarUI4FromUI1" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromUI1(BYTE bIn, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromUI1);

/* ms892123 "VarUI4FromUI2" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VarUI4FromUI2(USHORT uiIn, ULONG* pulOut) AKARI_CE_NAME(VarUI4FromUI2);

/* ms892124 "VectorFromBstr" (Header: Oleauto.h; Windows CE 2.0 and later).
 */
AKARI_CE_IMPORT HRESULT VectorFromBstr(BSTR bstr, SAFEARRAY ** ppsa) AKARI_CE_NAME(VectorFromBstr);


#ifdef __cplusplus
}
#endif

#endif /* AKARI_OBJBASE_H */
