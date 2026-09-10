/*
 * Shobjidl.h -- Shell COM interface records and view constants for
 * Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  This header holds the Standard Shell Interfaces and the SHGNO
 * enumeration whose CE 5.0 pages print Header: Shobjidl.h (Shobjidl.idl).
 *
 * The CE pages document each interface through its method pages only;
 * no page publishes a vtable layout, so -- following the M44 objbase.h
 * interface-record policy -- each interface is carried as an opaque
 * forward declaration plus a verbatim method-signature record, never
 * as an invented C vtable.  The pages print "Link Library:
 * Implementation dependent", so no import-library def is derived.
 */

#ifndef AKARI_SHOBJIDL_H
#define AKARI_SHOBJIDL_H

#include "Windef.h"
#include "Objbase.h"   /* HRESULT, REFIID, IBindCtx/LPBC, IDataObject,
                          POINTL (OLE carriers, M44); the interface
                          method records below reference HWND / POINT /
                          LPMSG textually only */
#include "Winuser.h"   /* LPMSG (IShellView::TranslateAccelerator --
                          a real vtable parameter since M97) */
#include "Prsht.h"     /* LPFNADDPROPSHEETPAGE (AddPropertySheetPages) */
#include "Shtypes.h"   /* STRRET/LPSTRRET (GetDisplayNameOf) */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* aa453709 "SHGNO" (Windows CE .NET 4.2 and later; Shobjidl.h).       */
/* Selector values for IShellFolder::GetDisplayNameOf / SetNameOf.     */
/* The page publishes the five-element enum body without initializers  */
/* and states "The numeric value of SHGDN_NORMAL is zero" -- only that */
/* one value is published.  The desktop Win32 _SHGDNF reference page   */
/* (shobjidl_core.h) publishes SHGDN_INFOLDER = 0x1,                   */
/* SHGDN_FOREDITING = 0x1000, SHGDN_FORADDRESSBAR = 0x4000 and         */
/* SHGDN_FORPARSING = 0x8000, but the CE page's bare sequential enum   */
/* body is an equally admissible reading, so the four unpublished      */
/* values are not uniquely derivable and stay held (M53 derivation     */
/* analysis in docs/inventory.md).                                     */
/* ------------------------------------------------------------------ */
typedef enum tagSHGDN {
    SHGDN_NORMAL = 0    /* value published: "the numeric value of
                           SHGDN_NORMAL is zero" (aa453709) */
} SHGNO;

/* SHGDN names whose values are held (aa453709 enum order):
 *   SHGDN_INFOLDER      relative name (relative to the folder)
 *   SHGDN_FOREDITING   (modifier) name for in-place renaming
 *   SHGDN_FORADDRESSBAR (modifier) name for an address-bar combo box
 *   SHGDN_FORPARSING   (modifier) name for ParseDisplayName
 */

/* ------------------------------------------------------------------ */
/* IShellFolder::GetAttributesOf (ms909872) publishes the SFGAO_*      */
/* capability/display/contents/miscellaneous flags WITH values ("Flag  */
/* (value)" tables).  The rgfInOut parameter is typed "address of a    */
/* single ULONG value" on the page; the SFGAOF carrier name from the   */
/* published signature is carried as a typedef below.                  */
/* ------------------------------------------------------------------ */
typedef ULONG SFGAOF;

/* ms909872: capability flags. */
#define SFGAO_CANCOPY       0x00000001   /* = DROPEFFECT_COPY */
#define SFGAO_CANMOVE       0x00000002   /* = DROPEFFECT_MOVE */
#define SFGAO_CANLINK       0x00000004
#define SFGAO_CANRENAME     0x00000010
#define SFGAO_CANDELETE     0x00000020
#define SFGAO_HASPROPSHEET  0x00000040
#define SFGAO_DROPTARGET    0x00000100
#define SFGAO_CAPABILITYMASK 0x00000177
#define SFGAO_CANMONIKER    0x00400000
/* ms909872: display attributes. */
#define SFGAO_GHOSTED       0x00080000
#define SFGAO_LINK          0x00010000
#define SFGAO_READONLY      0x00040000
#define SFGAO_SHARE         0x00020000
#define SFGAO_DISPLAYATTRMASK 0x000F0000
/* ms909872: contents flags. */
#define SFGAO_HASSUBFOLDER  0x80000000
#define SFGAO_CONTENTSMASK  0x80000000
/* ms909872: miscellaneous attributes. */
#define SFGAO_BROWSABLE     0x08000000
#define SFGAO_COMPRESSED    0x04000000
#define SFGAO_FILESYSTEM    0x40000000
#define SFGAO_FILESYSANCESTOR 0x10000000
#define SFGAO_FOLDER        0x20000000
#define SFGAO_NEWCONTENT    0x00200000
#define SFGAO_NONENUMERATED 0x00100000
#define SFGAO_REMOVABLE     0x02000000
#define SFGAO_VALIDATE      0x01000000

/* ------------------------------------------------------------------ */
/* IShellView::SelectItem (ms909891) and GetItemObject (ms909887) and  */
/* UIActivate (ms909893) publish the SVSI_*, SVGIO_* and SVUIA_*       */
/* selector names in their parameter tables.  Values: the desktop      */
/* Win32 _SVSIF and _SVGIO reference pages (shobjidl_core.h) publish   */
/* the shared flag numbering, so the CE names that exist on both      */
/* platforms carry the desktop-published values (M52 derived-value     */
/* policy: same name, same semantics, fixed shared flag ABI, no        */
/* contradicting CE publication); the derivation paths are recorded    */
/* in docs/inventory.md M53.                                           */
/* ------------------------------------------------------------------ */

/* ms909891 (SelectItem uFlags) / desktop _SVSIF page: */
#define SVSI_DESELECT       0x00000000
#define SVSI_SELECT         0x00000001
#define SVSI_EDIT           0x00000003
#define SVSI_DESELECTOTHERS 0x00000004
#define SVSI_ENSUREVISIBLE  0x00000008
#define SVSI_FOCUSED        0x00000010
#define SVSI_TRANSLATEPT    0x00000020
#define SVSI_SELECTIONMARK  0x00000040
#define SVSI_POSITIONITEM   0x00000080
#define SVSI_CHECK          0x00000100
/* SVSI_NOSTATECHANGE (ms909891) is a CE-only selector name with no
 * desktop counterpart and no published value: held. */

/* ms909887 (GetItemObject uItem) / desktop _SVGIO page: */
#define SVGIO_BACKGROUND      0x00000000
#define SVGIO_SELECTION       0x00000001
#define SVGIO_ALLVIEW         0x00000002
#define SVGIO_CHECKED         0x00000003
#define SVGIO_TYPE_MASK       0x0000000F
#define SVGIO_FLAG_VIEWORDER  0x80000000

/* SVUIA_* (ms909893, UIActivate uState) -- names only:
 *   SVUIA_ACTIVATE_FOCUS, SVUIA_ACTIVATE_NOFOCUS,
 *   SVUIA_DEACTIVATE, SVUIA_IN_PLACEACTIVATE
 * No API reference page (CE or desktop) publishes their values; held. */

/* ------------------------------------------------------------------ */
/* Standard Shell Interfaces (CE 5.0 "Shell Reference > Standard Shell */
/* Reference > Standard Shell Interfaces").  Opaque forward            */
/* declarations (M44 objbase.h policy: the docs publish method         */
/* signatures, never vtable layouts).                                  */
/* ------------------------------------------------------------------ */
typedef struct IDropTarget      IDropTarget;
typedef struct IPersistFolder   IPersistFolder;
typedef struct IShellFolder     IShellFolder;
typedef struct IShellView       IShellView;
typedef struct ITaskbarList     ITaskbarList;
typedef struct ITaskbarList2    ITaskbarList2;

/* Auxiliary interface names that appear inside the published method
 * signatures but have no CE 5.0 page of their own (recorded, not
 * declared): IEnumIDList (EnumObjects out-parameter, printed
 * "IENUMIDLIST**"), IShellBrowser (CreateViewWindow).  FOLDERSETTINGS
 * (CreateViewWindow / GetCurrentInfo) and the SHCONTF enumerated type
 * (EnumObjects -- the page references "the SHCONTF enumerated type"
 * but no CE 5.0 SHCONTF page exists) are likewise dangling references
 * from the CE pages; the DROPEFFECT_* effect names and the MK_* key
 * state names of the IDropTarget pages have no CE value tables either.
 * All are listed as gaps in docs/inventory.md M53.  The
 * LPFNADDPROPSHEETPAGE parameter of ms909882 AddPropertySheetPages is
 * no longer dangling: the M55 Property Sheets book documents
 * AddPropSheetPageProc (aa452848) and prsht.h declares the pointer
 * type. */

/* IDropTarget: documented methods (4 pages; Windows CE .NET 4.2 and
 * later; Shobjidl.h/Shobjidl.idl; Link Library: Implementation
 * dependent).  grfKeyState combines the MK_ALT / MK_CONTROL /
 * MK_LBUTTON / MK_MBUTTON / MK_RBUTTON / MK_SHIFT names (published
 * without values); *pdwEffect returns a DROPEFFECT_* name.
 *   ms929937 DragEnter: HRESULT DragEnter(IDataObject* pDataObject, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
 *   ms929938 DragLeave: HRESULT DragLeave(void)
 *   ms929939 DragOver:  HRESULT DragOver(DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
 *   ms929940 Drop:      HRESULT Drop(IDataObject* pDataObject, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
 */

/* IPersistFolder: documented methods (1 page; Windows CE .NET 4.2 and
 * later).
 *   ms909861 Initialize: HRESULT Initialize(LPCITEMIDLIST pidl)
 */

/* IShellFolder: documented methods (9 pages; Windows CE .NET 4.2 and
 * later).
 *   ms909868 BindToObject:      HRESULT BindToObject(LPCITEMIDLIST pidl, LPBC pbc, REFIID riid, VOID** ppvOut)
 *   ms909869 CompareIDs:        HRESULT CompareIDs(LPARAM lParam, LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2)
 *   ms909870 CreateViewObject:  HRESULT CreateViewObject(HWND hwndOwner, REFIID riid, VOID** ppvOut)
 *   ms909871 EnumObjects:       HRESULT EnumObjects(HWND hwndOwner, SHCONTF grfFlags, IENUMIDLIST** ppenumIDList)
 *   ms909872 GetAttributesOf:   HRESULT GetAttributesOf(UINT cidl, LPCITEMIDLIST* apidl, SFGAOF* rgfInOut)
 *   ms909873 GetDisplayNameOf:  HRESULT GetDisplayNameOf(LPCITEMIDLIST pidl, DWORD uFlags, LPSTRRET lpName)
 *   ms909874 GetUIObjectOf:     HRESULT GetUIObjectOf(HWND hwndOwner, UINT cidl, LPCITEMIDLIST* apidl, REFIID riid, UINT* rgfReserved, VOID** ppv)
 *   ms909875 ParseDisplayName:  HRESULT ParseDisplayName(HWND hwnd, LPBC pbc, LPOLESTR pwszDisplayName, ULONG* pchEaten, LPITEMIDLIST* ppidl, ULONG* pdwAttributes)
 *   ms909876 SetNameOf:         HRESULT SetNameOf(HWND hwndOwner, LPCITEMIDLIST pidl, LPCOLESTR lpszName, DWORD uFlags, LPITEMIDLIST* ppidlOut)
 */

/* IShellView: documented methods (12 pages; Windows CE 5.0 and later).
 *   ms909882 AddPropertySheetPages: HRESULT AddPropertySheetPages(DWORD dwReserved, LPFNADDPROPSHEETPAGE lpfn, LPARAM lparam)
 *   ms909883 CreateViewWindow:      HRESULT CreateViewWindow(IShellView* psvPrevious, LPCFOLDERSETTINGS pfs, IShellBrowser* psb, RECT* prcView, HWND* phWnd)
 *   ms909884 DestroyViewWindow:     HRESULT DestroyViewWindow(void)
 *   ms909885 EnableModeless:         HRESULT EnableModeless(BOOL fEnable)
 *   ms909886 GetCurrentInfo:         HRESULT GetCurrentInfo(LPFOLDERSETTINGS lpfs)
 *   ms909887 GetItemObject:          HRESULT GetItemObject(UINT uItem, REFIID riid, LPVOID* ppv)
 *   ms909889 Refresh:                HRESULT Refresh(VOID)
 *   ms909890 SaveViewState:          HRESULT SaveViewState(void)
 *   ms909891 SelectItem:             HRESULT SelectItem(LPCITEMIDLIST pidlItem, UINT uFlags)
 *   ms909892 TranslateAccelerator:   HRESULT TranslateAccelerator(LPMSG lpmsg)
 *   ms909893 UIActivate:             HRESULT UIActivate(UINT uState)
 */

/* ITaskbarList: documented methods (5 pages; Windows CE 5.0 and later).
 *   aa453239 ActivateTab: HRESULT ActivateTab(HWND hwnd)
 *   aa453240 AddTab:      HRESULT AddTab(HWND hwnd)
 *   aa453241 DeleteTab:   HRESULT DeleteTab(HWND hwnd)
 *   aa453242 HrInit:      HRESULT HrInit(VOID)
 *   aa453243 SetActiveAlt: HRESULT SetActiveAlt(HWND hwnd)
 */

/* ITaskbarList2: documented methods (1 page; Windows CE 5.0 and later).
 *   aa453238 MarkFullscreenWindow: HRESULT MarkFullscreenWindow(HWND hwnd, BOOL fFullscreen)
 */

/* ------------------------------------------------------------------ */
/* Auxiliary types the vtable signatures below reference.  They are    */
/* dangling references in the M53 gap notes -- declared here (own      */
/* design, ABI-safe) so the adopted vtables type-check:                */
/*   POINTL           the OLE 2-D point (LONG x, LONG y) -- same       */
/*                    shape as POINT (Wtypes); not page-documented.    */
/*   SHCONTF          "the SHCONTF enumerated type" (EnumObjects page  */
/*                    reference) -- a flags dword.                     */
/*   IEnumIDList / IShellBrowser / FOLDERSETTINGS: recorded in the     */
/*                    notes above as CE-page dangling references;      */
/*                    opaque here (pointer-only use in the vtables).   */
/* ------------------------------------------------------------------ */
/* POINTL/SHCONTF and the other carriers: declared in Objbase.h
 * (M97 OLE carrier block) since Objbase.h's own vtables use them. */
typedef DWORD SHCONTF;
/* ITEMIDLIST carrier: completed in Shlobj.h (aa453244); the vtables
 * here use it through pointers only.  C11 permits the identical
 * typedef redeclaration Shlobj.h performs. */
typedef struct _ITEMIDLIST ITEMIDLIST, *LPITEMIDLIST;
typedef const ITEMIDLIST *LPCITEMIDLIST;
typedef struct IEnumIDList      IEnumIDList,      *LPENUMIDLIST;
typedef struct IShellBrowser    IShellBrowser,    *LPSHELLBROWSER;
typedef struct FOLDERSETTINGS   FOLDERSETTINGS,   *LPFOLDERSETTINGS,
                                *LPCFOLDERSETTINGS;

/* ================================================================== */
/* ================================================================== */
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

/* ---- IDropTarget: 4 documented method pages; order R1 ---- */
typedef struct IDropTargetVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IDropTarget*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IDropTarget*);  /* (R1) */
    ULONG (WINAPI *Release)(IDropTarget*);  /* (R1) */
    /* IDropTarget */
    HRESULT (WINAPI *DragEnter)(IDropTarget*, IDataObject* pDataObject, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect);  /* 929937 */
    HRESULT (WINAPI *DragOver)(IDropTarget*, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect);  /* 929939 */
    HRESULT (WINAPI *DragLeave)(IDropTarget*);  /* 929938 */
    HRESULT (WINAPI *Drop)(IDropTarget*, IDataObject* pDataObject, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect);  /* 929940 */
} IDropTargetVtbl;
struct IDropTarget { const IDropTargetVtbl *lpVtbl; };
#define IDropTarget_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IDropTarget_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IDropTarget_Release(T) ((T)->lpVtbl->Release(T))
#define IDropTarget_DragEnter(T,a,b,c,d) ((T)->lpVtbl->DragEnter(T,a,b,c,d))
#define IDropTarget_DragOver(T,a,b,c) ((T)->lpVtbl->DragOver(T,a,b,c))
#define IDropTarget_DragLeave(T) ((T)->lpVtbl->DragLeave(T))
#define IDropTarget_Drop(T,a,b,c,d) ((T)->lpVtbl->Drop(T,a,b,c,d))

/* ---- IPersistFolder: 1 documented method pages; order R1 ---- */
typedef struct IPersistFolderVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IPersistFolder*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IPersistFolder*);  /* (R1) */
    ULONG (WINAPI *Release)(IPersistFolder*);  /* (R1) */
    /* IPersist */
    HRESULT (WINAPI *GetClassID)(IPersistFolder*, CLSID*);  /* (R1) */
    /* IPersistFolder */
    HRESULT (WINAPI *Initialize)(IPersistFolder*, LPCITEMIDLIST pidl);  /* 909861 */
} IPersistFolderVtbl;
struct IPersistFolder { const IPersistFolderVtbl *lpVtbl; };
#define IPersistFolder_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IPersistFolder_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IPersistFolder_Release(T) ((T)->lpVtbl->Release(T))
#define IPersistFolder_GetClassID(T,a) ((T)->lpVtbl->GetClassID(T,a))
#define IPersistFolder_Initialize(T,a) ((T)->lpVtbl->Initialize(T,a))

/* ---- IShellFolder: 9 documented method pages; order R1 ---- */
typedef struct IShellFolderVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IShellFolder*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IShellFolder*);  /* (R1) */
    ULONG (WINAPI *Release)(IShellFolder*);  /* (R1) */
    /* IShellFolder */
    HRESULT (WINAPI *ParseDisplayName)(IShellFolder*, HWND hwnd, LPBC pbc, LPOLESTR pwszDisplayName, ULONG* pchEaten, LPITEMIDLIST* ppidl, ULONG* pdwAttributes);  /* 909875 */
    HRESULT (WINAPI *EnumObjects)(IShellFolder*, HWND hwndOwner, SHCONTF grfFlags, IEnumIDList** ppenumIDList);  /* 909871 */
    HRESULT (WINAPI *BindToObject)(IShellFolder*, LPCITEMIDLIST pidl, LPBC pbc, REFIID riid, VOID** ppvOut);  /* 909868 */
    HRESULT (WINAPI *BindToStorage)(IShellFolder*, LPCITEMIDLIST, LPBC, REFIID, PVOID*);  /* (R1) */
    HRESULT (WINAPI *CompareIDs)(IShellFolder*, LPARAM lParam, LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2);  /* 909869 */
    HRESULT (WINAPI *CreateViewObject)(IShellFolder*, HWND hwndOwner, REFIID riid, VOID** ppvOut);  /* 909870 */
    HRESULT (WINAPI *GetAttributesOf)(IShellFolder*, UINT cidl, LPCITEMIDLIST* apidl, SFGAOF* rgfInOut);  /* 909872 */
    HRESULT (WINAPI *GetUIObjectOf)(IShellFolder*, HWND hwndOwner, UINT cidl, LPCITEMIDLIST* apidl, REFIID riid, UINT* rgfReserved, VOID** ppv);  /* 909874 */
    HRESULT (WINAPI *GetDisplayNameOf)(IShellFolder*, LPCITEMIDLIST pidl, DWORD uFlags, LPSTRRET lpName);  /* 909873 */
    HRESULT (WINAPI *SetNameOf)(IShellFolder*, HWND hwndOwner, LPCITEMIDLIST pidl, LPCOLESTR lpszName, DWORD uFlags, LPITEMIDLIST* ppidlOut);  /* 909876 */
} IShellFolderVtbl;
struct IShellFolder { const IShellFolderVtbl *lpVtbl; };
#define IShellFolder_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IShellFolder_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IShellFolder_Release(T) ((T)->lpVtbl->Release(T))
#define IShellFolder_ParseDisplayName(T,a,b,c,d,e,f) ((T)->lpVtbl->ParseDisplayName(T,a,b,c,d,e,f))
#define IShellFolder_EnumObjects(T,a,b,c) ((T)->lpVtbl->EnumObjects(T,a,b,c))
#define IShellFolder_BindToObject(T,a,b,c,d) ((T)->lpVtbl->BindToObject(T,a,b,c,d))
#define IShellFolder_BindToStorage(T,a,b,c,d) ((T)->lpVtbl->BindToStorage(T,a,b,c,d))
#define IShellFolder_CompareIDs(T,a,b,c) ((T)->lpVtbl->CompareIDs(T,a,b,c))
#define IShellFolder_CreateViewObject(T,a,b,c) ((T)->lpVtbl->CreateViewObject(T,a,b,c))
#define IShellFolder_GetAttributesOf(T,a,b,c) ((T)->lpVtbl->GetAttributesOf(T,a,b,c))
#define IShellFolder_GetUIObjectOf(T,a,b,c,d,e,f) ((T)->lpVtbl->GetUIObjectOf(T,a,b,c,d,e,f))
#define IShellFolder_GetDisplayNameOf(T,a,b,c) ((T)->lpVtbl->GetDisplayNameOf(T,a,b,c))
#define IShellFolder_SetNameOf(T,a,b,c,d,e) ((T)->lpVtbl->SetNameOf(T,a,b,c,d,e))

/* ---- IShellView: 11 documented method pages; order R1 ---- */
typedef struct IShellViewVtbl {
    /* IUnknown */
    HRESULT (WINAPI *QueryInterface)(IShellView*, REFIID, PVOID*);  /* (R1) */
    ULONG (WINAPI *AddRef)(IShellView*);  /* (R1) */
    ULONG (WINAPI *Release)(IShellView*);  /* (R1) */
    /* IOleWindow */
    HRESULT (WINAPI *GetWindow)(IShellView*, HWND*);  /* (R1) */
    HRESULT (WINAPI *ContextSensitiveHelp)(IShellView*, BOOL);  /* (R1) */
    /* IShellView */
    HRESULT (WINAPI *TranslateAccelerator)(IShellView*, LPMSG lpmsg);  /* 909892 */
    HRESULT (WINAPI *EnableModeless)(IShellView*, BOOL fEnable);  /* 909885 */
    HRESULT (WINAPI *UIActivate)(IShellView*, UINT uState);  /* 909893 */
    HRESULT (WINAPI *Refresh)(IShellView*);  /* 909889 */
    HRESULT (WINAPI *CreateViewWindow)(IShellView*, IShellView* psvPrevious, LPCFOLDERSETTINGS pfs, IShellBrowser* psb, RECT* prcView, HWND* phWnd);  /* 909883 */
    HRESULT (WINAPI *DestroyViewWindow)(IShellView*);  /* 909884 */
    HRESULT (WINAPI *GetCurrentInfo)(IShellView*, LPFOLDERSETTINGS lpfs);  /* 909886 */
    HRESULT (WINAPI *AddPropertySheetPages)(IShellView*, DWORD dwReserved, LPFNADDPROPSHEETPAGE lpfn, LPARAM lparam);  /* 909882 */
    HRESULT (WINAPI *SaveViewState)(IShellView*);  /* 909890 */
    HRESULT (WINAPI *SelectItem)(IShellView*, LPCITEMIDLIST pidlItem, UINT uFlags);  /* 909891 */
    HRESULT (WINAPI *GetItemObject)(IShellView*, UINT uItem, REFIID riid, LPVOID* ppv);  /* 909887 */
} IShellViewVtbl;
struct IShellView { const IShellViewVtbl *lpVtbl; };
#define IShellView_QueryInterface(T,a,b) ((T)->lpVtbl->QueryInterface(T,a,b))
#define IShellView_AddRef(T) ((T)->lpVtbl->AddRef(T))
#define IShellView_Release(T) ((T)->lpVtbl->Release(T))
#define IShellView_GetWindow(T,a) ((T)->lpVtbl->GetWindow(T,a))
#define IShellView_ContextSensitiveHelp(T,a) ((T)->lpVtbl->ContextSensitiveHelp(T,a))
#define IShellView_TranslateAccelerator(T,a) ((T)->lpVtbl->TranslateAccelerator(T,a))
#define IShellView_EnableModeless(T,a) ((T)->lpVtbl->EnableModeless(T,a))
#define IShellView_UIActivate(T,a) ((T)->lpVtbl->UIActivate(T,a))
#define IShellView_Refresh(T) ((T)->lpVtbl->Refresh(T))
#define IShellView_CreateViewWindow(T,a,b,c,d,e) ((T)->lpVtbl->CreateViewWindow(T,a,b,c,d,e))
#define IShellView_DestroyViewWindow(T) ((T)->lpVtbl->DestroyViewWindow(T))
#define IShellView_GetCurrentInfo(T,a) ((T)->lpVtbl->GetCurrentInfo(T,a))
#define IShellView_AddPropertySheetPages(T,a,b,c) ((T)->lpVtbl->AddPropertySheetPages(T,a,b,c))
#define IShellView_SaveViewState(T) ((T)->lpVtbl->SaveViewState(T))
#define IShellView_SelectItem(T,a,b) ((T)->lpVtbl->SelectItem(T,a,b))
#define IShellView_GetItemObject(T,a,b,c) ((T)->lpVtbl->GetItemObject(T,a,b,c))

#ifdef __cplusplus
}
#endif

/* ================================================================== */
/* M96 value adoption -- values adopted from the CeGCC-lineage w32api
 * reference (R1, public domain; docs/clean-room.md par.4
 * revision 2026-09-10).  Every name below is documented by
 * the official CE pages WITHOUT a value (see the record
 * comments and the held ledger in this header); the value
 * is a CE-era ABI fact carried by the CE lineage itself.
 * Desktop mingw-w64 was considered and EXCLUDED as a source
 * (desktop-era values; policy note in clean-room.md).  R1's
 * license-exception files (winsock*, gl*) are unused.
 * ================================================================== */

/* ---- DROPEFFECT_ family (3 names; R1) ---- */
#define DROPEFFECT_COPY                              0x0001
#define DROPEFFECT_MOVE                              0x0002
#define DROPEFFECT_LINK                              0x0004

/* ---- MK_ family (6 names; R1) ---- */
#define MK_LBUTTON                                   0x0001
#define MK_RBUTTON                                   0x0002
#define MK_SHIFT                                     0x0004
#define MK_CONTROL                                   0x0008
#define MK_MBUTTON                                   0x0010
#define MK_ALT                                       0x0020

/* ---- SHGDN_ family (4 names; R1) ---- */
#define SHGDN_INFOLDER                               0x0001
#define SHGDN_FOREDITING                             0x1000
#define SHGDN_FORADDRESSBAR                          0x4000
#define SHGDN_FORPARSING                             0x8000

/* ---- SVUIA_ family (5 names; R1) ---- */
#define SVUIA_DEACTIVATE                             0x0000
#define SVUIA_ACTIVATE_NOFOCUS                       0x0001
#define SVUIA_ACTIVATE_FOCUS                         0x0002
#define SVUIA_INPLACEACTIVATE                        0x0003
#define SVUIA_IN_PLACEACTIVATE                       0x0003  /* R1: SVUIA_INPLACEACTIVATE */

/* ------------------------------------------------------------------
 * Book surface: shell-book (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms929937 IDropTarget::DragEnter (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms929938 IDropTarget::DragLeave (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms929939 IDropTarget::DragOver (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms929940 IDropTarget::Drop (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909861 IPersistFolder::Initialize (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909868 IShellFolder::BindToObject (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909869 IShellFolder::CompareIDs (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909870 IShellFolder::CreateViewObject (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909871 IShellFolder::EnumObjects (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909872 IShellFolder::GetAttributesOf (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909873 IShellFolder::GetDisplayNameOf (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909874 IShellFolder::GetUIObjectOf (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909875 IShellFolder::ParseDisplayName (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909882 IShellView::AddPropertySheetPages (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909883 IShellView::CreateViewWindow (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909884 IShellView::DestroyViewWindow (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909885 IShellView::EnableModeless (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909886 IShellView::GetCurrentInfo (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909887 IShellView::GetItemObject (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909889 IShellView::Refresh (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909890 IShellView::SaveViewState (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909891 IShellView::SelectItem (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909892 IShellView::TranslateAccelerator (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909893 IShellView::UIActivate (Header: Shobjidl.h, Shobjidl.idl.) */
/* aa453238 ITaskbarList2::MarkFullscreenWindow (Header: Shobjidl.h, Shobjidl.idl.) */
/* aa453239 ITaskbarList::ActivateTab (Header: Shobjidl.h, Shobjidl.idl.) */
/* aa453240 ITaskbarList::AddTab (Header: Shobjidl.h, Shobjidl.idl.) */
/* aa453241 ITaskbarList::DeleteTab (Header: Shobjidl.h, Shobjidl.idl.) */
/* aa453242 ITaskbarList::HrInit (Header: Shobjidl.h, Shobjidl.idl.) */
/* aa453243 ITaskbarList::SetActiveAlt (Header: Shobjidl.h, Shobjidl.idl.) */
/* ------------------------------------------------------------------
 * Book surface: stdshell (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms929937 IDropTarget::DragEnter (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms929938 IDropTarget::DragLeave (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms929939 IDropTarget::DragOver (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms929940 IDropTarget::Drop (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909861 IPersistFolder::Initialize (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909868 IShellFolder::BindToObject (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909869 IShellFolder::CompareIDs (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909870 IShellFolder::CreateViewObject (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909871 IShellFolder::EnumObjects (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909872 IShellFolder::GetAttributesOf (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909873 IShellFolder::GetDisplayNameOf (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909874 IShellFolder::GetUIObjectOf (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909875 IShellFolder::ParseDisplayName (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909882 IShellView::AddPropertySheetPages (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909883 IShellView::CreateViewWindow (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909884 IShellView::DestroyViewWindow (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909885 IShellView::EnableModeless (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909886 IShellView::GetCurrentInfo (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909887 IShellView::GetItemObject (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909889 IShellView::Refresh (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909890 IShellView::SaveViewState (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909891 IShellView::SelectItem (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909892 IShellView::TranslateAccelerator (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909893 IShellView::UIActivate (Header: Shobjidl.h, Shobjidl.idl.) */
/* aa453238 ITaskbarList2::MarkFullscreenWindow (Header: Shobjidl.h, Shobjidl.idl.) */
/* aa453239 ITaskbarList::ActivateTab (Header: Shobjidl.h, Shobjidl.idl.) */
/* aa453240 ITaskbarList::AddTab (Header: Shobjidl.h, Shobjidl.idl.) */
/* aa453241 ITaskbarList::DeleteTab (Header: Shobjidl.h, Shobjidl.idl.) */
/* aa453242 ITaskbarList::HrInit (Header: Shobjidl.h, Shobjidl.idl.) */
/* aa453243 ITaskbarList::SetActiveAlt (Header: Shobjidl.h, Shobjidl.idl.) */
/* ------------------------------------------------------------------
 * Book surface: shell-book (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms929937 IDropTarget::DragEnter (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms929938 IDropTarget::DragLeave (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms929939 IDropTarget::DragOver (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms929940 IDropTarget::Drop (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909861 IPersistFolder::Initialize (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909868 IShellFolder::BindToObject (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909869 IShellFolder::CompareIDs (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909870 IShellFolder::CreateViewObject (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909871 IShellFolder::EnumObjects (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909872 IShellFolder::GetAttributesOf (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909873 IShellFolder::GetDisplayNameOf (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909874 IShellFolder::GetUIObjectOf (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909875 IShellFolder::ParseDisplayName (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909882 IShellView::AddPropertySheetPages (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909883 IShellView::CreateViewWindow (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909884 IShellView::DestroyViewWindow (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909885 IShellView::EnableModeless (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909886 IShellView::GetCurrentInfo (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909887 IShellView::GetItemObject (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909889 IShellView::Refresh (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909890 IShellView::SaveViewState (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909891 IShellView::SelectItem (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909892 IShellView::TranslateAccelerator (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909893 IShellView::UIActivate (Header: Shobjidl.h, Shobjidl.idl.) */
/* aa453238 ITaskbarList2::MarkFullscreenWindow (Header: Shobjidl.h, Shobjidl.idl.) */
/* aa453239 ITaskbarList::ActivateTab (Header: Shobjidl.h, Shobjidl.idl.) */
/* aa453240 ITaskbarList::AddTab (Header: Shobjidl.h, Shobjidl.idl.) */
/* aa453241 ITaskbarList::DeleteTab (Header: Shobjidl.h, Shobjidl.idl.) */
/* aa453242 ITaskbarList::HrInit (Header: Shobjidl.h, Shobjidl.idl.) */
/* aa453243 ITaskbarList::SetActiveAlt (Header: Shobjidl.h, Shobjidl.idl.) */
/* ------------------------------------------------------------------
 * Book surface: stdshell (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms929937 IDropTarget::DragEnter (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms929938 IDropTarget::DragLeave (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms929939 IDropTarget::DragOver (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms929940 IDropTarget::Drop (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909861 IPersistFolder::Initialize (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909868 IShellFolder::BindToObject (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909869 IShellFolder::CompareIDs (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909870 IShellFolder::CreateViewObject (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909871 IShellFolder::EnumObjects (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909872 IShellFolder::GetAttributesOf (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909873 IShellFolder::GetDisplayNameOf (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909874 IShellFolder::GetUIObjectOf (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909875 IShellFolder::ParseDisplayName (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909882 IShellView::AddPropertySheetPages (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909883 IShellView::CreateViewWindow (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909884 IShellView::DestroyViewWindow (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909885 IShellView::EnableModeless (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909886 IShellView::GetCurrentInfo (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909887 IShellView::GetItemObject (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909889 IShellView::Refresh (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909890 IShellView::SaveViewState (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909891 IShellView::SelectItem (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909892 IShellView::TranslateAccelerator (Header: Shobjidl.h, Shobjidl.idl.) */
/* ms909893 IShellView::UIActivate (Header: Shobjidl.h, Shobjidl.idl.) */
/* aa453238 ITaskbarList2::MarkFullscreenWindow (Header: Shobjidl.h, Shobjidl.idl.) */
/* aa453239 ITaskbarList::ActivateTab (Header: Shobjidl.h, Shobjidl.idl.) */
/* aa453240 ITaskbarList::AddTab (Header: Shobjidl.h, Shobjidl.idl.) */
/* aa453241 ITaskbarList::DeleteTab (Header: Shobjidl.h, Shobjidl.idl.) */
/* aa453242 ITaskbarList::HrInit (Header: Shobjidl.h, Shobjidl.idl.) */
/* aa453243 ITaskbarList::SetActiveAlt (Header: Shobjidl.h, Shobjidl.idl.) */
#endif /* AKARI_SHOBJIDL_H */
