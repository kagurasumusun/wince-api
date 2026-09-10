/*
 * Sip.h -- Software-based Input Panel IM/IME layer for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  The Software-based Input Panel Reference book of the CE 5.0
 * documentation (book root aa453941) is the source book: the IMINFO and
 * LMDATA structures and the IIMCallback / IIMCallback2 / IInputMethod /
 * IInputMethod2 interfaces all print Header: Sip.h (Link Library:
 * Uuid.lib on the interface pages -- interfaces are not DLL exports, so
 * no def file carries them; the structures print no library row).
 *
 * Model notes (recorded per item in docs/inventory.md):
 *  (a) The four interfaces are application-/IM-implemented COM
 *      callback interfaces (the software-based input panel calls
 *      them); like the M44 objbase.h and M50 aygshell.h interface
 *      sets, their vtable layouts are not published as C structures,
 *      so they are carried as opaque interface tags with the
 *      documented method records below.
 *  (b) The IInputMethod root page prints "Windows CE 2.12 and later"
 *      while its method pages print "Windows CE 2.01 and later" --
 *      an internal inconsistency of the book, recorded verbatim.
 *  (c) IInputMethod2::RegisterCallback prints the parameter type
 *      "IIMCallback*" while its prose describes "a pointer to an
 *      IIMCallback2 interface" -- the printed signature wins, the
 *      prose inconsistency is recorded.  Its sibling method
 *      RegisterCallback2 takes IIMCallback2*.
 *  (d) SendCharEvents' uKeyFlags / puShift reference the Keybd.h
 *      KEY_STATE_FLAGS values (page ms902150 exists but belongs to
 *      the deferred OEM keybd batch; the printed signature types
 *      them UINT / UINT*, so no dependency is needed here).
 *      SendVirtualKey's dwFlags takes KEYEVENTF_KEYUP /
 *      KEYEVENTF_SILENT -- names published without values (held set,
 *      cf. the keybd_event record in winuser.h).
 *  (e) SendAlternatives2 delivers the LMDATA to the IME via the
 *      WM_SYSCOPYDATA message (aa453912, Header: Pwinuser.h, CE 2.12+)
 *      with wParam = WMSCD_CHAR_RANKED_ALTS; both the message value
 *      and the WMSCD_* constant are published as names only (held
 *      set), and the message's documented home Pwinuser.h belongs to
 *      the deferred OEM layer, so the shape is recorded here and held
 *      in docs/inventory.md.  lParam is a PCOPYDATASTRUCT (winuser.h,
 *      M31).
 */

#ifndef AKARI_SIP_H
#define AKARI_SIP_H

#include "Windows.h"   /* RECT, HWND, BOOL, DWORD, HRESULT, LPTSTR */
#include "Commctrl.h"  /* HIMAGELIST (IMINFO members) */
#include "Sipapi.h"    /* SIPINFO (IInputMethod::ReceiveSipInfo) */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Structures                                                           */
/* ------------------------------------------------------------------ */

/* ms909842 "IMINFO" (Windows CE 2.01 and later; Sip.h; no Link Library
 * row; CE 6.0 twin ee503199 prints the identical layout).  Size and
 * available bitmaps of an input method, filled by the IM for
 * IInputMethod::GetInfo / IIMCallback::SetImInfo.  fdwFlags combines
 * the SIP state bit names -- the page table prints SIPF_DOCKED /
 * SIPF_LOCKED / "SIP_OFF" (sic -- the SIPINFO table spells the same
 * off state SIPF_OFF; recorded verbatim) / SIPF_ON, all published
 * without values (held set).  Anonymous tag as printed. */
typedef struct {
    DWORD      cbSize;          /* sizeof(IMINFO); set by the SIP */
    HIMAGELIST hImageNarrow;    /* narrow 16x16 masked bitmaps */
    HIMAGELIST hImageWide;      /* wide 32x16 masked bitmaps */
    int        iNarrow;         /* index into hImageNarrow */
    int        iWide;           /* index into hImageWide */
    DWORD      fdwFlags;        /* SIP state bits (names held) */
    RECT       rcSipRect;       /* panel size/placement, screen coords */
} IMINFO;

/* aa453406 "LMDATA" (Windows CE 2.12 and later; Sip.h; no Link Library
 * row; CE 6.0 twin ee499697 repeats the print).  Alternatives-list
 * payload sent from an input method to an IME by
 * IIMCallback2::SendAlternatives2.  dwVersion must be 0x00010000 (the
 * one published value).  flags combine the LMDATA_SYMBOL_* /
 * LMDATA_SKIP_* / LMDATA_SCORE_* names (twelve, published without
 * values -- held set); the offsets are measured from the end of this
 * structure.  Tag as printed (_tagLMDATA). */
typedef struct _tagLMDATA {
    DWORD dwVersion;         /* set to 0x00010000 */
    DWORD flags;             /* LMDATA_* combination (names held) */
    DWORD cnt;               /* number of rows (symbol [+ skip] + score) */
    DWORD dwOffsetSymbols;   /* offset to the symbol table */
    DWORD dwOffsetSkip;      /* offset to the skip table */
    DWORD dwOffsetScore;     /* offset to the score table */
} LMDATA;

/* ------------------------------------------------------------------ */
/* Interfaces (application/IM-implemented; opaque tags, note (a))       */
/* ------------------------------------------------------------------ */

/* ms929942 "IIMCallback" (Windows CE 2.01 and later; Sip.h; Uuid.lib).
 * Handed to the IM by the SIP through IInputMethod::RegisterCallback;
 * the IM calls the methods to send keystrokes to the current
 * application and to change the Input Panel button bitmaps.  Methods
 * in the page-table order:
 *   SetImInfo       ms929952: HRESULT SetImInfo(IMINFO* pimi)
 *   SendVirtualKey  ms929951: HRESULT SendVirtualKey(BYTE bVk,
 *                                                   DWORD dwFlags)
 *   SendCharEvents  ms929949: HRESULT SendCharEvents(UINT uVK,
 *                       UINT uKeyFlags, UINT uChars, UINT* puShift,
 *                       UINT* puChars)
 *   SendString      ms929950: HRESULT SendString(LPTSTR ptszStr,
 *                                                DWORD dwSize)
 */
typedef struct IIMCallback IIMCallback;

/* ms929943 "IIMCallback2" (Windows CE 2.12 and later; Sip.h;
 * Uuid.lib).  IIMCallback extended for IME alternatives delivery;
 * methods in the page-table order (SetImInfo / SendVirtualKey /
 * SendCharEvents / SendString shapes identical to IIMCallback's,
 * ms929948 / ms929947 / ms929945 / ms929946):
 *   SetImInfo        ms929948: HRESULT SetImInfo(IMINFO* pimi)
 *   SendVirtualKey   ms929947: HRESULT SendVirtualKey(BYTE bVk,
 *                                                    DWORD dwFlags)
 *   SendCharEvents   ms929945: HRESULT SendCharEvents(UINT uVK,
 *                       UINT uKeyFlags, UINT uChars, UINT* puShift,
 *                       UINT* puChars)
 *   SendString       ms929946: HRESULT SendString(LPTSTR ptszStr,
 *                                                 DWORD dwSize)
 *   SendAlternatives2 ms929944: HRESULT SendAlternatives2(
 *                                  LMDATA* plmd)
 */
typedef struct IIMCallback2 IIMCallback2;

/* ms929953 "IInputMethod" (Windows CE 2.12 and later per the root
 * page -- its method pages print 2.01+, note (b); Sip.h; Uuid.lib).
 * Implemented by the IM component; the SIP calls the methods to
 * notify the IM of state changes and to request information.  Methods
 * in the page-table order (the remarks sequence Select -> GetInfo ->
 * ReceiveSipInfo -> RegisterCallback is the documented initialization
 * call order):
 *   Select           ms909669: HRESULT Select(HWND hwndSip)
 *   Deselect         ms930093: HRESULT Deselect(void)
 *   Showing          ms909766: HRESULT Showing(void)
 *   Hiding           ms930118: HRESULT Hiding(void)
 *   GetInfo          ms930107: HRESULT GetInfo(IMINFO* pimi)
 *   ReceiveSipInfo   ms930126: HRESULT ReceiveSipInfo(SIPINFO* psi)
 *   RegisterCallback ms930132: HRESULT RegisterCallback(
 *                                 IIMCallback* pIMCallback)
 *   GetImData        ms930101: HRESULT GetImData(DWORD dwSize,
 *                                                void* pvImData)
 *   SetImData        ms909763: HRESULT SetImData(DWORD dwSize,
 *                                                void* pvImData)
 *   UserOptionsDlg   ms909775: HRESULT UserOptionsDlg(
 *                                 HWND hwndParent)
 */
typedef struct IInputMethod IInputMethod;

/* ms929954 "IInputMethod2" (Windows CE 2.12 and later; Sip.h;
 * Uuid.lib).  IInputMethod extended for the IMM active context and
 * the IIMCallback2 delivery; methods in the page-table order (the
 * IInputMethod shapes as above; notes (c) for RegisterCallback):
 *   Select              ms929962: HRESULT Select(HWND hwndSip)
 *   Deselect            ms929955: HRESULT Deselect(void)
 *   Showing             ms929965: HRESULT Showing(void)
 *   Hiding              ms929958: HRESULT Hiding(void)
 *   GetInfo             ms929957: HRESULT GetInfo(IMINFO* pimi)
 *   ReceiveSipInfo      ms929959: HRESULT ReceiveSipInfo(SIPINFO* psi)
 *   RegisterCallback    ms929960: HRESULT RegisterCallback(
 *                                    IIMCallback* pIMCallback)
 *   GetImData           ms929956: HRESULT GetImData(DWORD dwSize,
 *                                                   void* pvImData)
 *   SetImData           ms929963: HRESULT SetImData(DWORD dwSize,
 *                                                   void* pvImData)
 *   UserOptionsDlg      ms930035: HRESULT UserOptionsDlg(
 *                                    HWND hwndParent)
 *   SetIMMActiveContext ms929964: HRESULT SetIMMActiveContext(
 *                                    HWND hwnd, BOOL bOpen,
 *                                    DWORD dwConversion,
 *                                    DWORD dwSentence, DWORD hkl)
 *       (hkl printed as DWORD; the page prose names it "a handle to
 *       the current active keyboard layout"; called whenever
 *       ImmSetActiveContext is called on a window control)
 *   RegisterCallback2   ms929961: HRESULT RegisterCallback2(
 *                                    IIMCallback2* pIMCallback2)
 */
typedef struct IInputMethod2 IInputMethod2;

/* ------------------------------------------------------------------
 * Book surface: sip (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms929944 IIMCallback2::SendAlternatives2 (Header: Sip.h.) */
/* ms929945 IIMCallback2::SendCharEvents (Header: Sip.h.) */
/* ms929946 IIMCallback2::SendString (Header: Sip.h.) */
/* ms929947 IIMCallback2::SendVirtualKey (Header: Sip.h.) */
/* ms929948 IIMCallback2::SetImInfo (Header: Sip.h.) */
/* ms929949 IIMCallback::SendCharEvents (Header: Sip.h.) */
/* ms929950 IIMCallback::SendString (Header: Sip.h.) */
/* ms929951 IIMCallback::SendVirtualKey (Header: Sip.h.) */
/* ms929952 IIMCallback::SetImInfo (Header: Sip.h.) */
/* ms929955 IInputMethod2::Deselect (Header: Sip.h.) */
/* ms929956 IInputMethod2::GetImData (Header: Sip.h.) */
/* ms929957 IInputMethod2::GetInfo (Header: Sip.h.) */
/* ms929958 IInputMethod2::Hiding (Header: Sip.h.) */
/* ms929959 IInputMethod2::ReceiveSipInfo (Header: Sip.h.) */
/* ms929960 IInputMethod2::RegisterCallback (Header: Sip.h.) */
/* ms929961 IInputMethod2::RegisterCallback2 (Header: Sip.h.) */
/* ms929962 IInputMethod2::Select (Header: Sip.h.) */
/* ms929963 IInputMethod2::SetImData (Header: Sip.h.) */
/* ms929964 IInputMethod2::SetIMMActiveContext (Header: Sip.h.) */
/* ms929965 IInputMethod2::Showing (Header: Sip.h.) */
/* ms930035 IInputMethod2::UserOptionsDlg (Header: Sip.h.) */
/* ms930093 IInputMethod::Deselect (Header: Sip.h.) */
/* ms930101 IInputMethod::GetImData (Header: Sip.h.) */
/* ms930107 IInputMethod::GetInfo (Header: Sip.h.) */
/* ms930118 IInputMethod::Hiding (Header: Sip.h.) */
/* ms930126 IInputMethod::ReceiveSipInfo (Header: Sip.h.) */
/* ms930132 IInputMethod::RegisterCallback (Header: Sip.h.) */
/* ms909669 IInputMethod::Select (Header: Sip.h.) */
/* ms909763 IInputMethod::SetImData (Header: Sip.h.) */
/* ms909766 IInputMethod::Showing (Header: Sip.h.) */
/* ms909775 IInputMethod::UserOptionsDlg (Header: Sip.h.) */

/* ------------------------------------------------------------------
 * Book surface: sip (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms929944 IIMCallback2::SendAlternatives2 (Header: Sip.h.) */
/* ms929945 IIMCallback2::SendCharEvents (Header: Sip.h.) */
/* ms929946 IIMCallback2::SendString (Header: Sip.h.) */
/* ms929947 IIMCallback2::SendVirtualKey (Header: Sip.h.) */
/* ms929948 IIMCallback2::SetImInfo (Header: Sip.h.) */
/* ms929949 IIMCallback::SendCharEvents (Header: Sip.h.) */
/* ms929950 IIMCallback::SendString (Header: Sip.h.) */
/* ms929951 IIMCallback::SendVirtualKey (Header: Sip.h.) */
/* ms929952 IIMCallback::SetImInfo (Header: Sip.h.) */
/* ms929955 IInputMethod2::Deselect (Header: Sip.h.) */
/* ms929956 IInputMethod2::GetImData (Header: Sip.h.) */
/* ms929957 IInputMethod2::GetInfo (Header: Sip.h.) */
/* ms929958 IInputMethod2::Hiding (Header: Sip.h.) */
/* ms929959 IInputMethod2::ReceiveSipInfo (Header: Sip.h.) */
/* ms929960 IInputMethod2::RegisterCallback (Header: Sip.h.) */
/* ms929961 IInputMethod2::RegisterCallback2 (Header: Sip.h.) */
/* ms929962 IInputMethod2::Select (Header: Sip.h.) */
/* ms929963 IInputMethod2::SetImData (Header: Sip.h.) */
/* ms929964 IInputMethod2::SetIMMActiveContext (Header: Sip.h.) */
/* ms929965 IInputMethod2::Showing (Header: Sip.h.) */
/* ms930035 IInputMethod2::UserOptionsDlg (Header: Sip.h.) */
/* ms930093 IInputMethod::Deselect (Header: Sip.h.) */
/* ms930101 IInputMethod::GetImData (Header: Sip.h.) */
/* ms930107 IInputMethod::GetInfo (Header: Sip.h.) */
/* ms930118 IInputMethod::Hiding (Header: Sip.h.) */
/* ms930126 IInputMethod::ReceiveSipInfo (Header: Sip.h.) */
/* ms930132 IInputMethod::RegisterCallback (Header: Sip.h.) */
/* ms909669 IInputMethod::Select (Header: Sip.h.) */
/* ms909763 IInputMethod::SetImData (Header: Sip.h.) */
/* ms909766 IInputMethod::Showing (Header: Sip.h.) */
/* ms909775 IInputMethod::UserOptionsDlg (Header: Sip.h.) */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_SIP_H */
