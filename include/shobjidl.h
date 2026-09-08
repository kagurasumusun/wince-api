/*
 * shobjidl.h -- Shell COM interface records and view constants for
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

#include "windef.h"
#include "objbase.h"   /* HRESULT, REFIID, IBindCtx/LPBC, IDataObject,
                          POINTL (OLE carriers, M44); the interface
                          method records below reference HWND / POINT /
                          LPMSG textually only */

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

#ifdef __cplusplus
}
#endif

#endif /* AKARI_SHOBJIDL_H */
