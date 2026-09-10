/*
 * Dvdnav.h -- Windows CE DVD-Video API navigation objects, macros, playback enums.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE pages of
 * the Graphics and Multimedia Technologies > DVD-Video API book
 * (tools/manifests/graphics-book.manifest, M87).  Requirements rows
 * print "Header: Dvdnav.h, Dvdnav.idl" and
 * "Link Library: Ddvdids.lib" (GUID linkage -- Uuid.lib precedent, no
 * def).  The interfaces are C++ COM: no page publishes a vtable
 * layout, so each is carried as an opaque forward declaration plus
 * verbatim method-signature records (M44/M69/M80 interface-record
 * policy).  Structures and enumerations print in full and are
 * compiled verbatim.  See docs/inventory.md M87.
 */

#ifndef AKARI_DVDNAV_H
#define AKARI_DVDNAV_H

#include "Windef.h"    /* UINT8/UINT16/UINT32 (see Windef.h), BYTE, BOOL */
#include "Winnt.h"     /* WCHAR */

#ifdef __cplusplus
extern "C" {
#endif

/* ms925307 "DVD-Video API Macros" -- 45 macros, values printed. */
#define DVD_SYSTEM_SPACE_BIT            1
#define DVD_MENU_SPACE_BIT              (DVD_SYSTEM_SPACE_BIT << 1)
#define DVD_VMG_SPACE_BIT               (DVD_MENU_SPACE_BIT << 1)
#define DVD_VTS_SPACE_BIT               (DVD_VMG_SPACE_BIT << 1)
#define DVD_NAVSTATREQ_VOLUME_BIT       1
#define DVD_NAVSTATREQ_HIGHLIGHT_BIT    (DVD_NAVSTATREQ_VOLUME_BIT << 1)
#define DVD_NAVSTATREQ_PCI_BIT          (DVD_NAVSTATREQ_HIGHLIGHT_BIT << 1)
#define DVD_PROGRAM_PREVIOUS            0
#define DVD_PROGRAM_NEXT                1
#define DVD_PROGRAM_TOP                 2
#define DVD_MENU_TITLE                  0
#define DVD_MENU_ROOT                   1
#define DVD_MENU_SUBPICTURE             2
#define DVD_MENU_AUDIO                  3
#define DVD_MENU_ANGLE                  4
#define DVD_MENU_PTT                    5
#define DVD_SELECT_UPPER                0
#define DVD_SELECT_RIGHT                1
#define DVD_SELECT_LOWER                2
#define DVD_SELECT_LEFT                 3
#define DVD_SCANCAP_FORWARD_SCAN        0x1
#define DVD_SCANCAP_FORWARD_SLOW        0x2
#define DVD_SCANCAP_FORWARD_SINGLE      0x4
#define DVD_SCANCAP_BACKWARD_SCAN       0x8
#define DVD_SCANCAP_BACKWARD_SLOW       0x10
#define DVD_SCANCAP_BACKWARD_SINGLE     0x20
#define SPRM_M_LCD                      0
#define SPRM_ASTN                       1
#define SPRM_SPSTN                      2
#define SPRM_AGLN                       3
#define SPRM_TTN                        4
#define SPRM_VTS_TTN                    5
#define SPRM_TT_PGCN                    6
#define SPRM_PTTN                       7
#define SPRM_HL_BTNN                    8
#define SPRM_NV_TMR                     9
#define SPRM_NV_TMR_PGCN                10
#define SPRM_P_AMXMD                    11
#define SPRM_CTY_CD                     12
#define SPRM_PTL_LVL                    13
#define SPRM_P_CFG_VIDEO                14
#define SPRM_P_CFG_AUDIO                15
#define SPRM_INI_LCD_AST                16
#define SPRM_INI_LCD_EXT_AST            17
#define SPRM_INI_LCD_SPST               18
#define SPRM_INI_LCD_EXT_SPST           19
#define SPRM_REGION                     20

/* ------------------------------------------------------------------ */
/* Structures (full prints, compiled verbatim).                      */
/* ------------------------------------------------------------------ */

/* aa451630 "DVDUserGOPData": print
 * `typedef struct {UINT8 userData[9+64*3];} DVDUserGOPData;` (glued tokens split). */
typedef struct {
    UINT8 userData[9+64*3];
} DVDUserGOPData;

/* ------------------------------------------------------------------ */
/* Enumerated types (full prints).                                   */
/* ------------------------------------------------------------------ */

/* aa451671 "EDDVDPlaybackState": print
 * `typedef enum {DVD_STOPPED,DVD_PAUSED,DVD_STILLED,DVD_NORMAL_PLAY,DVD_FORWARD_SCAN,DVD_FORWARD_SLOW,DVD_FORWARD_SINGLE,DVD_BACKWARD_SCAN,DVD_BACKWARD_SLOW,DVD_BACKWARD_SINGLE} EDDVDPlaybackState;` (as printed). */
typedef enum {
    DVD_STOPPED,
    DVD_PAUSED,
    DVD_STILLED,
    DVD_NORMAL_PLAY,
    DVD_FORWARD_SCAN,
    DVD_FORWARD_SLOW,
    DVD_FORWARD_SINGLE,
    DVD_BACKWARD_SCAN,
    DVD_BACKWARD_SLOW,
    DVD_BACKWARD_SINGLE,
} EDDVDPlaybackState;

/* aa451673 "EDVDNavException": print
 * `typedef enum {InsufficientParentalLevel, FatalNavigationError} EDVDNavException;` (as printed). */
typedef enum {
    InsufficientParentalLevel,
    FatalNavigationError,
} EDVDNavException;

/* aa451674 "EDVDSParamEvent": print
 * `typedef enum { InitialAccess, TitlePartTimePlay, MenuCallToVmgmDom, MenuCallToVtsmDom} EDVDSParamEvent;` (as printed). */
typedef enum {
    InitialAccess,
    TitlePartTimePlay,
    MenuCallToVmgmDom,
    MenuCallToVtsmDom,
} EDVDSParamEvent;

/* ------------------------------------------------------------------ */
/* Interfaces (opaque forwards + method records).                    */
/* ------------------------------------------------------------------ */

/* ------------------------------------------------------------------ */
/* IDVDNavigationManager (aa451867; Requirements rows print Header: Dvdnav.h, Dvdnav.idl,
 * Link Library: Ddvdids.lib -- GUID linkage, no def).  No vtable
 * layout is published; opaque forward + method records
 * (M44/M69/M80 interface-record policy).  Pages list the methods
 * "in the order the compiler calls them"; records follow the
 * archive page order.  IUnknown (QueryInterface/AddRef/Release)
 * heads every vtable per the page tables. */
typedef struct IDVDNavigationManager IDVDNavigationManager;
/* aa451868 ButtonSelectDirect: `HRESULT ButtonSelectDirect(BYTEbyteButtonNumber);` */
/* aa451869 GetGParameter: `HRESULT GetGParameter(UINT8no,UINT16* pValue,BOOL* pbCounterMode);` */
/* aa451870 GetPlaybackState: `HRESULT GetPlaybackState(EDDVDPlaybackState* peState);` */
/* aa451871 GetScanCaps: `HRESULT GetScanCaps(UINT16* pMask);` */
/* aa451872 GetSParameter: `HRESULT GetSParameter(UINT8no,UINT16* pValue);` */
/* aa451873 SetSParameter: `HRESULT SetSParameter(UINT8no,UINT16wValue);` */
/* aa451875 SetVolume: `HRESULT SetVolume(IDVDVideoVolume* pVolume);` */
/* aa451876 UseRenderer: `HRESULT UseRenderer(WCHAR* pszRendererName);`
 * (the page TOC path misspells the interface as
 * "IDVDNavigationManger" -- archive typo; title segment used here) */

/* ------------------------------------------------------------------ */
/* IDVDUserOperation (aa452059; Requirements rows print Header: Dvdnav.h, Dvdnav.idl,
 * Link Library: Ddvdids.lib -- GUID linkage, no def).  No vtable
 * layout is published; opaque forward + method records
 * (M44/M69/M80 interface-record policy).  Pages list the methods
 * "in the order the compiler calls them"; records follow the
 * archive page order.  IUnknown (QueryInterface/AddRef/Release)
 * heads every vtable per the page tables. */
typedef struct IDVDUserOperation IDVDUserOperation;
/* aa452060 BackwardScan: `HRESULT BackwardScan(double dblSpeed);` */
/* aa452061 ButtonActivate: `HRESULT ButtonActivate(void);` */
/* aa452062 ButtonSelect: `HRESULT ButtonSelect(BYTE byteDirection);` */
/* aa452063 ButtonSelectAndActivate: `HRESULT ButonSelectAndActivate(BYTE byteButtonNumber);`  [page title is ButtonSelectAndActivate; the print misprints the callee as ButonSelectAndActivate -- archive typo] */
/* aa452064 ChangeAngle: `HRESULT ChangeAngel(BYTE byteAngleNumber );`  [page title is ChangeAngle; the print misprints the callee as ChangeAngel -- archive typo] */
/* aa452065 ChangeAudioStream: `HRESULT ChangeAudioStream(BYTE byteStreamNumber);` */
/* aa452067 ChangeSubPictureStream: `HRESULT ChangeSubPictureStream(BYTE streamNumber,BOOL bDisplayFlag);` */
/* aa452069 ForwardScan: `HRESULT ForwardScan(double dblSpeed);` */
/* aa452071 GoUp: `HRESULT ForwardScan(void);`  [page title is GoUp; the print misprints the callee as ForwardScan -- archive typo] */
/* aa452073 MenuCall: `HRESULT MenuCall(BYTE byteMenu_ID);` */
/* aa452075 MenuLanguageSelect: `HRESULT ManuLanguageSelect(USHORT uhLanguageCode );`  [page title is MenuLanguageSelect; the print misprints the callee as ManuLanguageSelect -- archive typo] */
/* aa452077 ParentalCountrySelect: `HRESULT ParentalCountrySelect(USHORT uhCountryCode );` */
/* ms910052 ParentalLevelSelect: `HRESULT ParentalLevelSelect(BYTE byteLevel);` */
/* ms910143 PartPlay: `HRESULT PartPlay(BYTE byteTitleNumber,USHORT uhPartOfTheTitle);` */
/* ms910154 Pause: `HRESULT Pause(BOOL bOnOff);` */
/* ms910161 ProgramSearch: `HRESULT ProgramSearch(BYTE byteProgramType);` */
/* ms910167 PTTSearch: `HRESULT TimePlay(USHORT uhPartOfTheTitle );`  [page title is PTTSearch; the print misprints the callee as TimePlay -- archive typo] */
/* ms930706 Resume: `HRESULT Resume(void);` */
/* ms930718 StillOff: `HRESULT StillOff(void);` */
/* ms930814 Stop: `HRESULT Stop(void);` */
/* ms930822 TimePlay: `HRESULT TimePlay(BYTE byteTitleNumber,UINT uiBCDTime);` */
/* ms930827 TimeSearch: `HRESULT TimeSearch(UINT uiBCDTime);` */
/* ms930832 TitlePlay: `HRESULT TitlePlay(BYTE byteTitleNumber);` */
/* ms930840 VideoPresentationModeChange: `HRESULT VideoPresentationModeChange(USHORT uhVideoMode);` */

/* ------------------------------------------------------------------
 * Book surface: graphics-book (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa451671 DVD-Video API Enumerated Types/EDDVDPlaybackState (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451673 DVD-Video API Enumerated Types/EDVDNavException (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451674 DVD-Video API Enumerated Types/EDVDSParamEvent (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451867 DVD-Video API Interfaces/IDVDNavigationManager (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452059 DVD-Video API Interfaces/IDVDUserOperation (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451630 DVD-Video API Structures/DVDUserGOPData (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451868 IDVDNavigationManager/IDVDNavigationManager::ButtonSelectDirect (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451869 IDVDNavigationManager/IDVDNavigationManager::GetGParameter (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451870 IDVDNavigationManager/IDVDNavigationManager::GetPlaybackState (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451871 IDVDNavigationManager/IDVDNavigationManager::GetScanCaps (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451872 IDVDNavigationManager/IDVDNavigationManager::GetSParameter (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451873 IDVDNavigationManager/IDVDNavigationManager::SetSParameter (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451875 IDVDNavigationManager/IDVDNavigationManager::SetVolume (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451876 IDVDNavigationManager/IDVDNavigationManger::UseRenderer (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451880 IDVDNavigatorSink/IDVDNavigatorSink::ConfirmTemporaryParentalLevel (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451882 IDVDNavigatorSink/IDVDNavigatorSink::InitializeSystemParameters (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451884 IDVDNavigatorSink/IDVDNavigatorSink::OnDiskReadError (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451886 IDVDNavigatorSink/IDVDNavigatorSink::OnGOPUserData (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451889 IDVDNavigatorSink/IDVDNavigatorSink::OnGPRMChange (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451891 IDVDNavigatorSink/IDVDNavigatorSink::OnNavigationException (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451893 IDVDNavigatorSink/IDVDNavigatorSink::OnNewCell (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451895 IDVDNavigatorSink/IDVDNavigatorSink::OnNewProgram (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451897 IDVDNavigatorSink/IDVDNavigatorSink::OnNewProgramChain (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451899 IDVDNavigatorSink/IDVDNavigatorSink::OnPlaybackStateChange (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451901 IDVDNavigatorSink/IDVDNavigatorSink::OnSPRMChange (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451903 IDVDNavigatorSink/IDVDNavigatorSink::OnUOPChange (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452060 IDVDUserOperation/IDVDUserOperation::BackwardScan (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452061 IDVDUserOperation/IDVDUserOperation::ButtonActivate (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452062 IDVDUserOperation/IDVDUserOperation::ButtonSelect (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452063 IDVDUserOperation/IDVDUserOperation::ButtonSelectAndActivate (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452064 IDVDUserOperation/IDVDUserOperation::ChangeAngle (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452065 IDVDUserOperation/IDVDUserOperation::ChangeAudioStream (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452067 IDVDUserOperation/IDVDUserOperation::ChangeSubPictureStream (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452069 IDVDUserOperation/IDVDUserOperation::ForwardScan (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452071 IDVDUserOperation/IDVDUserOperation::GoUp (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452073 IDVDUserOperation/IDVDUserOperation::MenuCall (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452075 IDVDUserOperation/IDVDUserOperation::MenuLanguageSelect (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452077 IDVDUserOperation/IDVDUserOperation::ParentalCountrySelect (Header: Dvdnav.h, Dvdnav.idl.) */
/* ms910052 IDVDUserOperation/IDVDUserOperation::ParentalLevelSelect (Header: Dvdnav.h, Dvdnav.idl.) */
/* ms910143 IDVDUserOperation/IDVDUserOperation::PartPlay (Header: Dvdnav.h, Dvdnav.idl.) */
/* ms910154 IDVDUserOperation/IDVDUserOperation::Pause (Header: Dvdnav.h, Dvdnav.idl.) */
/* ms910161 IDVDUserOperation/IDVDUserOperation::ProgramSearch (Header: Dvdnav.h, Dvdnav.idl.) */
/* ms910167 IDVDUserOperation/IDVDUserOperation::PTTSearch (Header: Dvdnav.h, Dvdnav.idl.) */
/* ms930706 IDVDUserOperation/IDVDUserOperation::Resume (Header: Dvdnav.h, Dvdnav.idl.) */
/* ms930718 IDVDUserOperation/IDVDUserOperation::StillOff (Header: Dvdnav.h, Dvdnav.idl.) */
/* ms930814 IDVDUserOperation/IDVDUserOperation::Stop (Header: Dvdnav.h, Dvdnav.idl.) */
/* ms930822 IDVDUserOperation/IDVDUserOperation::TimePlay (Header: Dvdnav.h, Dvdnav.idl.) */
/* ms930827 IDVDUserOperation/IDVDUserOperation::TimeSearch (Header: Dvdnav.h, Dvdnav.idl.) */
/* ms930832 IDVDUserOperation/IDVDUserOperation::TitlePlay (Header: Dvdnav.h, Dvdnav.idl.) */
/* ms930840 IDVDUserOperation/IDVDUserOperation::VideoPresentationModeChange (Header: Dvdnav.h, Dvdnav.idl.) */

/* ------------------------------------------------------------------
 * Book surface: graphics-book (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa451671 DVD-Video API Enumerated Types/EDDVDPlaybackState (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451673 DVD-Video API Enumerated Types/EDVDNavException (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451674 DVD-Video API Enumerated Types/EDVDSParamEvent (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451867 DVD-Video API Interfaces/IDVDNavigationManager (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452059 DVD-Video API Interfaces/IDVDUserOperation (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451630 DVD-Video API Structures/DVDUserGOPData (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451868 IDVDNavigationManager/IDVDNavigationManager::ButtonSelectDirect (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451869 IDVDNavigationManager/IDVDNavigationManager::GetGParameter (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451870 IDVDNavigationManager/IDVDNavigationManager::GetPlaybackState (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451871 IDVDNavigationManager/IDVDNavigationManager::GetScanCaps (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451872 IDVDNavigationManager/IDVDNavigationManager::GetSParameter (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451873 IDVDNavigationManager/IDVDNavigationManager::SetSParameter (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451875 IDVDNavigationManager/IDVDNavigationManager::SetVolume (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451876 IDVDNavigationManager/IDVDNavigationManger::UseRenderer (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451880 IDVDNavigatorSink/IDVDNavigatorSink::ConfirmTemporaryParentalLevel (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451882 IDVDNavigatorSink/IDVDNavigatorSink::InitializeSystemParameters (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451884 IDVDNavigatorSink/IDVDNavigatorSink::OnDiskReadError (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451886 IDVDNavigatorSink/IDVDNavigatorSink::OnGOPUserData (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451889 IDVDNavigatorSink/IDVDNavigatorSink::OnGPRMChange (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451891 IDVDNavigatorSink/IDVDNavigatorSink::OnNavigationException (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451893 IDVDNavigatorSink/IDVDNavigatorSink::OnNewCell (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451895 IDVDNavigatorSink/IDVDNavigatorSink::OnNewProgram (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451897 IDVDNavigatorSink/IDVDNavigatorSink::OnNewProgramChain (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451899 IDVDNavigatorSink/IDVDNavigatorSink::OnPlaybackStateChange (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451901 IDVDNavigatorSink/IDVDNavigatorSink::OnSPRMChange (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa451903 IDVDNavigatorSink/IDVDNavigatorSink::OnUOPChange (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452060 IDVDUserOperation/IDVDUserOperation::BackwardScan (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452061 IDVDUserOperation/IDVDUserOperation::ButtonActivate (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452062 IDVDUserOperation/IDVDUserOperation::ButtonSelect (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452063 IDVDUserOperation/IDVDUserOperation::ButtonSelectAndActivate (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452064 IDVDUserOperation/IDVDUserOperation::ChangeAngle (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452065 IDVDUserOperation/IDVDUserOperation::ChangeAudioStream (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452067 IDVDUserOperation/IDVDUserOperation::ChangeSubPictureStream (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452069 IDVDUserOperation/IDVDUserOperation::ForwardScan (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452071 IDVDUserOperation/IDVDUserOperation::GoUp (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452073 IDVDUserOperation/IDVDUserOperation::MenuCall (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452075 IDVDUserOperation/IDVDUserOperation::MenuLanguageSelect (Header: Dvdnav.h, Dvdnav.idl.) */
/* aa452077 IDVDUserOperation/IDVDUserOperation::ParentalCountrySelect (Header: Dvdnav.h, Dvdnav.idl.) */
/* ms910052 IDVDUserOperation/IDVDUserOperation::ParentalLevelSelect (Header: Dvdnav.h, Dvdnav.idl.) */
/* ms910143 IDVDUserOperation/IDVDUserOperation::PartPlay (Header: Dvdnav.h, Dvdnav.idl.) */
/* ms910154 IDVDUserOperation/IDVDUserOperation::Pause (Header: Dvdnav.h, Dvdnav.idl.) */
/* ms910161 IDVDUserOperation/IDVDUserOperation::ProgramSearch (Header: Dvdnav.h, Dvdnav.idl.) */
/* ms910167 IDVDUserOperation/IDVDUserOperation::PTTSearch (Header: Dvdnav.h, Dvdnav.idl.) */
/* ms930706 IDVDUserOperation/IDVDUserOperation::Resume (Header: Dvdnav.h, Dvdnav.idl.) */
/* ms930718 IDVDUserOperation/IDVDUserOperation::StillOff (Header: Dvdnav.h, Dvdnav.idl.) */
/* ms930814 IDVDUserOperation/IDVDUserOperation::Stop (Header: Dvdnav.h, Dvdnav.idl.) */
/* ms930822 IDVDUserOperation/IDVDUserOperation::TimePlay (Header: Dvdnav.h, Dvdnav.idl.) */
/* ms930827 IDVDUserOperation/IDVDUserOperation::TimeSearch (Header: Dvdnav.h, Dvdnav.idl.) */
/* ms930832 IDVDUserOperation/IDVDUserOperation::TitlePlay (Header: Dvdnav.h, Dvdnav.idl.) */
/* ms930840 IDVDUserOperation/IDVDUserOperation::VideoPresentationModeChange (Header: Dvdnav.h, Dvdnav.idl.) */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_DVDNAV */
