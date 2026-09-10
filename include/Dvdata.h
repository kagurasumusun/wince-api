/*
 * Dvdata.h -- Windows CE DVD-Video API data/volume objects.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE pages of
 * the Graphics and Multimedia Technologies > DVD-Video API book
 * (tools/manifests/graphics-book.manifest, M87).  Requirements rows
 * print "Header: Dvdata.h, Dvdata.idl" and
 * "Link Library: Ddvdids.lib" (GUID linkage -- Uuid.lib precedent, no
 * def).  The interfaces are C++ COM: no page publishes a vtable
 * layout, so each is carried as an opaque forward declaration plus
 * verbatim method-signature records (M44/M69/M80 interface-record
 * policy).  Structures and enumerations print in full and are
 * compiled verbatim.  See docs/inventory.md M87.
 */

#ifndef AKARI_DVDATA_H
#define AKARI_DVDATA_H

#include "Windef.h"    /* UINT8/UINT16/UINT32 (see Windef.h), BYTE, BOOL */
#include "Winnt.h"     /* WCHAR */

#ifdef __cplusplus
extern "C" {
#endif

/* aa452397 "UNICODE_PATH": print `#define MAX_PATH 128typedef
 * [string] WCHAR UNICODE_PATH [MAX_PATH];` (IDL attribute).  The
 * DVD-local `#define MAX_PATH 128` is NOT emitted: Windef.h owns
 * MAX_PATH (260, ms913243) and redefining it would break the system
 * surface.  UNICODE_PATH is defined as a 128-WCHAR array per the
 * page text ("holds a string of 128 Unicode characters") and the
 * printed array bound. */
typedef WCHAR UNICODE_PATH[128];

/* ------------------------------------------------------------------ */
/* Structures (full prints, compiled verbatim).                      */
/* ------------------------------------------------------------------ */

/* aa451617 "DVD_AUDIO_MU_ATTR": print
 * `typedef struct _structDVD_AUDIO_MU_ATTR {UINT8atr1[8];struct {UINT8alpha;UINT8beta;}atr2[8];} DVD_AUDIO_MU_ATTR, *PDVD_AUDIO_MU_ATTR;` (glued tokens split). */
typedef struct _structDVD_AUDIO_MU_ATTR {
    UINT8 atr1[8];
    struct {
        UINT8 alpha;
        UINT8 beta;
    } atr2[8];
} DVD_AUDIO_MU_ATTR, *PDVD_AUDIO_MU_ATTR;

/* aa451618 "DVD_AUDIO_STREAM_ATTR": print
 * `typedef struct _structDVD_AUDIO_STREAM_ATTR {UINT16attr;UINT16reserved[3];} DVD_AUDIO_STREAM_ATTR, *PDVD_AUDIO_STREAM_ATTR;` (glued tokens split). */
typedef struct _structDVD_AUDIO_STREAM_ATTR {
    UINT16 attr;
    UINT16 reserved[3];
} DVD_AUDIO_STREAM_ATTR, *PDVD_AUDIO_STREAM_ATTR;

/* aa451619 "DVD_CELL_PIECE": print
 * `typedef struct {UINT16 vob_id;UINT8 c_idn;UINT32 start;UINT32 end;} DVD_CELL_PIECE, *PDVD_CELL_PIECE;` (glued tokens split). */
typedef struct {
    UINT16 vob_id;
    UINT8 c_idn;
    UINT32 start;
    UINT32 end;
} DVD_CELL_PIECE, *PDVD_CELL_PIECE;

/* aa451620 "DVD_CELL_PLAYBACK": print
 * `typedef struct {UINT32cellCategory;UINT32cellPlaybackTime;UINT32startFirstVobu;UINT32endFirstIlvu;UINT32startLastVobu;UINT32endLastVobu;} DVD_CELL_PLAYBACK;` (glued tokens split). */
typedef struct {
    UINT32 cellCategory;
    UINT32 cellPlaybackTime;
    UINT32 startFirstVobu;
    UINT32 endFirstIlvu;
    UINT32 startLastVobu;
    UINT32 endLastVobu;
} DVD_CELL_PLAYBACK;

/* aa451621 "DVD_ISRC": print
 * `typedef struct {UINT8valid;UINT8countryCode[2];UINT8copyrightHolder[3];UINT8bcdYear;UINT8bcdNumber[3];} DVD_ISRC;` (glued tokens split). */
typedef struct {
    UINT8 valid;
    UINT8 countryCode[2];
    UINT8 copyrightHolder[3];
    UINT8 bcdYear;
    UINT8 bcdNumber[3];
} DVD_ISRC;

/* aa451622 "DVD_NAV_CMD": print
 * `typedef struct {UINT8cmd[8];} DVD_NAV_CMD;` (glued tokens split). */
typedef struct {
    UINT8 cmd[8];
} DVD_NAV_CMD;

/* aa451623 "DVD_POS_CODE": print
 * `typedef struct _structDVD_POS_CODE {UINT8posCode[8];} DVD_POS_CODE;` (glued tokens split). */
typedef struct _structDVD_POS_CODE {
    UINT8 posCode[8];
} DVD_POS_CODE;

/* aa451624 "DVD_PROVIDER_ID": print
 * `typedef struct _structDVD_PROVIDER_ID {UINT8providerID[32];} DVD_PROVIDER_ID;` (glued tokens split). */
typedef struct _structDVD_PROVIDER_ID {
    UINT8 providerID[32];
} DVD_PROVIDER_ID;

/* aa451625 "DVD_RECT": print
 * `typedef struct {UINT16xStart;UINT16xEnd;UINT16yStart;UINT16yEnd;} DVD_RECT;` (glued tokens split). */
typedef struct {
    UINT16 xStart;
    UINT16 xEnd;
    UINT16 yStart;
    UINT16 yEnd;
} DVD_RECT;

/* aa451626 "DVD_SUBPICTURE_STREAM_ATTR": print
 * `typedef struct _structDVD_SUBPICTURE_STREAM_ATTR {UINT16modetype;UINT16specificCode;UINT16extension;} DVD_SUBPICTURE_STREAM_ATTR, *PDVD_SUBPICTURE_STREAM_ATTR;` (glued tokens split). */
typedef struct _structDVD_SUBPICTURE_STREAM_ATTR {
    UINT16 modetype;
    UINT16 specificCode;
    UINT16 extension;
} DVD_SUBPICTURE_STREAM_ATTR, *PDVD_SUBPICTURE_STREAM_ATTR;

/* aa451627 "DVD_TEXT_ITEM": print
 * `typedef struct _structDVD_TEXT_ITEM {UINT8* pTextData;UINT8 itemCode;} DVD_TEXT_ITEM, *PDVD_TEXT_ITEM;` (glued tokens split). */
typedef struct _structDVD_TEXT_ITEM {
    UINT8 *pTextData;
    UINT8 itemCode;
} DVD_TEXT_ITEM, *PDVD_TEXT_ITEM;

/* aa451628 "DVD_TEXT_LANGUAGE_UNIT": print
 * `typedef struct _structDVD_TEXT_LANGUAGE_UNIT {UINT16 tdlc;UINT8 charset;} DVD_TEXT_LANGUAGE_UNIT, *PDVD_TEXT_LANGUAGE_UNIT;` (glued tokens split). */
typedef struct _structDVD_TEXT_LANGUAGE_UNIT {
    UINT16 tdlc;
    UINT8 charset;
} DVD_TEXT_LANGUAGE_UNIT, *PDVD_TEXT_LANGUAGE_UNIT;

/* aa451629 "DVD_TITLE_SET_INFO": print
 * `typedef struct _structDVD_TITLE_SET_INFO {UINT16nParts;UINT16parentalID;UINT8titlePlaybackType;UINT8nAngles;UINT8vtsn;UINT8vts_ttn;} DVD_TITLE_SET_INFO;` (glued tokens split). */
typedef struct _structDVD_TITLE_SET_INFO {
    UINT16 nParts;
    UINT16 parentalID;
    UINT8 titlePlaybackType;
    UINT8 nAngles;
    UINT8 vtsn;
    UINT8 vts_ttn;
} DVD_TITLE_SET_INFO;

/* ------------------------------------------------------------------ */
/* Enumerated types (full prints).                                   */
/* ------------------------------------------------------------------ */

/* aa451672 "EDVDDomainType": print
 * `typedef enum {DVD_FP_DOM,DVD_VMGM_DOM,DVD_VTSM_DOM,DVD_TT_DOM} EDVDDomainType;` (as printed). */
typedef enum {
    DVD_FP_DOM,
    DVD_VMGM_DOM,
    DVD_VTSM_DOM,
    DVD_TT_DOM,
} EDVDDomainType;

/* aa451678 "ENavCmdArea": print
 * `typedef enum {DVD_PRE_CMD = 0,DVD_POST_CMD = 1,DVD_CELL_CMD = 2} ENavCmdArea;` (as printed). */
typedef enum {
    DVD_PRE_CMD = 0,
    DVD_POST_CMD = 1,
    DVD_CELL_CMD = 2,
} ENavCmdArea;

/* aa451695 "EPGCLinkType": print
 * `typedef enum {DVD_NEXT_PGC,DVD_PREVIOUS_PGC,DVD_UP_PGC} EPGCLinkType;` (as printed). */
typedef enum {
    DVD_NEXT_PGC,
    DVD_PREVIOUS_PGC,
    DVD_UP_PGC,
} EPGCLinkType;

/* aa451696 "EPGCPlaybackMode": print
 * `typedef enum {DVD_PLAYMODE_SEQUENTIAL,DVD_PLAYMODE_RANDOM,DVD_PLAYMODE_SHUFFLE} EPGCPlaybackMode;` (as printed). */
typedef enum {
    DVD_PLAYMODE_SEQUENTIAL,
    DVD_PLAYMODE_RANDOM,
    DVD_PLAYMODE_SHUFFLE,
} EPGCPlaybackMode;

/* ------------------------------------------------------------------ */
/* Interfaces (opaque forwards + method records).                    */
/* ------------------------------------------------------------------ */

/* ------------------------------------------------------------------ */
/* IDVDDataSearchInfo (aa451819; Requirements rows print Header: Dvdata.h, Dvdata.idl,
 * Link Library: Ddvdids.lib -- GUID linkage, no def).  No vtable
 * layout is published; opaque forward + method records
 * (M44/M69/M80 interface-record policy).  Pages list the methods
 * "in the order the compiler calls them"; records follow the
 * archive page order.  IUnknown (QueryInterface/AddRef/Release)
 * heads every vtable per the page tables. */
typedef struct IDVDDataSearchInfo IDVDDataSearchInfo;
/* aa451820 GetAudioGapInfo: `HRESULT GetAudioGapInfo(UINT8 streamNo,UINT8 gapNo,UINT32* pMpegStart,UINT32* pMpegEnd);` */
/* aa451821 GetC_IDN: `HRESULT GetC_IDN(UINT8* pC_IDN);` */
/* aa451822 GetControlInfo: `HRESULT GetControlInfo(IDVDStreaControlInfo** ppStream);` */
/* aa451823 GetInterleavedUnitEndAddress: `HRESULT GetInterleavedUnitEndAddress(UINT32* pRLBN);` */
/* aa451824 GetNextInterleavedUnit: `HRESULT GetNextInterleavedUnit(UINT32* pRLBN,UINT16* pLBSize);` */
/* aa451825 GetRefPictureAddress: `HRESULT GetRefPictureAddress(UINT8 refNo,UINT32* pRLBN);` */
/* aa451826 GetSCRBase: `HRESULT GetSCRBase(UINT32* pSCR);` */
/* aa451827 GetSeamlessAngleChangeAddress: `HRESULT GetSearmlessAngleChangeAddress(UINT8 angle,UINT32* pRLBN,UINT32* pLBSize);`  [page title is GetSeamlessAngleChangeAddress; the print misprints the callee as GetSearmlessAngleChangeAddress -- archive typo] */
/* aa451828 GetSeamlessCategory: `HRESULT GetSeamlessCategory(UINT16* pCat);` */
/* aa451829 GetSyncAudioAddress: `HRESULT GetSyncAudioAddress(UINT8 streamN,UINT16* pRLBN);` */
/* aa451830 GetSyncSPAddress: `HRESULT GetSyncSPAddress(UINT8 streamN,UINT32* pRLBN);` */
/* aa451831 GetUnitEndAddress: `HRESULT GetUnitEndAddress(UINT32* pRLBN);` */
/* aa451832 GetUnitStepAddress: `HRESULT GetUnitStepAddress(UINT8 dir,INT16 stepIndex,UINT32* pAddress);` */
/* aa451833 GetVOB_ID: `HRESULT GetVOB_ID(UINT16* pVOB_ID);` */

/* ------------------------------------------------------------------ */
/* IDVDDomain (aa451834; Requirements rows print Header: Dvdata.h, Dvdata.idl,
 * Link Library: Ddvdids.lib -- GUID linkage, no def).  No vtable
 * layout is published; opaque forward + method records
 * (M44/M69/M80 interface-record policy).  Pages list the methods
 * "in the order the compiler calls them"; records follow the
 * archive page order.  IUnknown (QueryInterface/AddRef/Release)
 * heads every vtable per the page tables. */
typedef struct IDVDDomain IDVDDomain;
/* aa451835 GetCellPieceEnumerator: `HRESULT GetCellPieceEnumerator(IEnumDVD_CELL_PIECE** ppEnumPiecesUINT32* pPieceCount );` */
/* aa451836 GetPGC: `HRESULT GetPGC(UINT16 pgcn,IDVDProgamChain* pPGC,UINT32* pPGCCat);` */
/* aa451837 GetPGCCount: `HRESULT GetPGC(UINT16* pCount);`  [page title is GetPGCCount; the print misprints the callee as GetPGC -- archive typo] */
/* aa451838 GetSpace: `HRESULT GetSpace(UINT8* pSpaceSet );` */
/* aa451839 GetStreamAttributes: `HRESULT GetStreamAttributes(IDVDStreamAttributes** ppAttr);` */
/* aa451840 GetTimeMap: `HRESULT GetTimeMap( UINT16 pgcn,IDVDTimeMap** ppTimeMap );` */
/* aa451841 GetTitleSet: `HRESULT GetTimeMap(IDVDTitleSet** ppTitleSet );`  [page title is GetTitleSet; the print misprints the callee as GetTimeMap -- archive typo] */
/* aa451842 GetTotalVideoObjects: `HRESULT GetTotalVideoObjects(UINT16* pTotalVobs,UINT32* pCellPieceCount);` */
/* aa451843 GetTotalVOBUnits: `HRESULT GetTotalVOBUnit(UINT32* pVobus );`  [page title is GetTotalVOBUnits; the print misprints the callee as GetTotalVOBUnit -- archive typo] */
/* aa451844 GetType: `HRESULT GetType(EDVDDomainType* pDType);` */
/* aa451845 GetVOBFileID: `HRESULT GetVOBFileID(UINT16* pFileID );` */
/* aa451846 GetVOBUTablePtr: `HRESULT GetVOBTablePtr(UINT32** ppVOBUAddressArray );`  [page title is GetVOBUTablePtr; the print misprints the callee as GetVOBTablePtr -- archive typo] */
/* aa451847 GetVolume: `HRESULT GetVolume(IDVDVideoVolume** ppVolume);` */

/* ------------------------------------------------------------------ */
/* IDVDHighlightInfo (aa451848; Requirements rows print Header: Dvdata.h, Dvdata.idl,
 * Link Library: Ddvdids.lib -- GUID linkage, no def).  No vtable
 * layout is published; opaque forward + method records
 * (M44/M69/M80 interface-record policy).  Pages list the methods
 * "in the order the compiler calls them"; records follow the
 * archive page order.  IUnknown (QueryInterface/AddRef/Release)
 * heads every vtable per the page tables. */
typedef struct IDVDHighlightInfo IDVDHighlightInfo;
/* aa451849 GetAdjacentButton: `HRESULT GetAdjacentButton(UINT8 byteButton,UINT8 byteDir,UINT8* pbyteButtonNumber);` */
/* aa451850 GetButtonColorInfo: `HRESULT GetButtonColorInfo(UINT8 byteButtonColor,UINT32* pSelectionColors,UINT32* pActionColors);` */
/* aa451851 GetButtonCommand: `HRESULT GetButtonCommand(UINT8 byteButtonNumber,DVD_NAV_CMD* pCmd);` */
/* aa451852 GetButtonCount: `HRESULT GetButtonCount(UINT8* pbyteCount);` */
/* aa451853 GetButtonMode: `HRESULT GetButtonMode(UINT16* pMode);` */
/* aa451854 GetButtonOffset: `HRESULT GetButtonOffset(UINT8* pByteOffset);` */
/* aa451855 GetButtonPositionInfo: `HRESULT GetButtonPositionInfo(UINT8 byteButton,UINT8* pbyteButtonColor,UINT8* pbyteActionMode,DVD_RECT* pArea);` */
/* aa451856 GetDefaultActionButton: `HRESULT GetDefaultActionButton(UINT8* pActionButton);` */
/* aa451857 GetHLIStatus: `HRESULT GetHLIStatus(UINT16* pStatus);` */
/* aa451858 GetInitialSelectionButton: `HRESULT GetButtonPositionInfo(UINT8* pInitialSelection);`  [page title is GetInitialSelectionButton; the print misprints the callee as GetButtonPositionInfo -- archive typo] */
/* aa451859 GetNumberedButtonCount: `HRESULT GetButtonPositionInfo(UINT8* pbyteCount);`  [page title is GetNumberedButtonCount; the print misprints the callee as GetButtonPositionInfo -- archive typo] */
/* aa451860 GetPTMs: `HRESULT GetPTMs(UINT32* puiStart,UINT32* puiEnd,UINT32* puiSelectionEnd);` */
/* aa451861 GetStreamingInfo: `HRESULT GetStreamingInfo(IDVDStreamControlInfo** pControlInfo);` */

/* ------------------------------------------------------------------ */
/* IDVDMenu (aa451862; Requirements rows print Header: Dvdata.h, Dvdata.idl,
 * Link Library: Ddvdids.lib -- GUID linkage, no def).  No vtable
 * layout is published; opaque forward + method records
 * (M44/M69/M80 interface-record policy).  Pages list the methods
 * "in the order the compiler calls them"; records follow the
 * archive page order.  IUnknown (QueryInterface/AddRef/Release)
 * heads every vtable per the page tables. */
typedef struct IDVDMenu IDVDMenu;
/* aa451863 GetDomain: `HRESULT GetDomain(UINT16 languageCode,IDVDDomain** ppDomain,UINT8* pExistFlag );` */
/* aa451864 GetMenuLanguageInfo: `HRESULT GetMenuLanguageInfo(UNIT16* plangcount,UINT16* pLCBuffer,UINT8* pFlagsBuffer);` */

/* ------------------------------------------------------------------ */
/* IDVDNavDataStatusSink (aa451865; Requirements rows print Header: Dvdata.h, Dvdata.idl,
 * Link Library: Ddvdids.lib -- GUID linkage, no def).  No vtable
 * layout is published; opaque forward + method records
 * (M44/M69/M80 interface-record policy).  Pages list the methods
 * "in the order the compiler calls them"; records follow the
 * archive page order.  IUnknown (QueryInterface/AddRef/Release)
 * heads every vtable per the page tables. */
typedef struct IDVDNavDataStatusSink IDVDNavDataStatusSink;
/* aa451866 NotifyNewPCI: `HRESULT NotifyNewPCI();` */

/* ------------------------------------------------------------------ */
/* IDVDNavigatorSink (aa451878; Requirements rows print Header: Dvdata.h, Dvdata.idl,
 * Link Library: Ddvdids.lib -- GUID linkage, no def).  No vtable
 * layout is published; opaque forward + method records
 * (M44/M69/M80 interface-record policy).  Pages list the methods
 * "in the order the compiler calls them"; records follow the
 * archive page order.  IUnknown (QueryInterface/AddRef/Release)
 * heads every vtable per the page tables. */
typedef struct IDVDNavigatorSink IDVDNavigatorSink;
/* aa451880 ConfirmTemporaryParentalLevel: `HRESULT ConfirmTemporaryParentalLevel(UINT8requestedLevel);`  [method page Requirements print Header: Dvdnav.h] */
/* aa451882 InitializeSystemParameters: `HRESULT InitializeSystemParameters( EDVDSParamEvent eventCode);`  [method page Requirements print Header: Dvdnav.h] */
/* aa451884 OnDiskReadError: `HRESULT OnDiskReadError(DWORDosCode);`  [method page Requirements print Header: Dvdnav.h] */
/* aa451886 OnGOPUserData: `HRESULT OnGOPUserData(DVDUserGOPData* pData);`  [method page Requirements print Header: Dvdnav.h] */
/* aa451889 OnGPRMChange: `HRESULT OnGPRMChange(UINT8no,UINT16wValue,BOOLbCounter);`  [method page Requirements print Header: Dvdnav.h] */
/* aa451891 OnNavigationException: `HRESULT OnNavigationException(EDVDNavExceptionexcCode);`  [method page Requirements print Header: Dvdnav.h] */
/* aa451893 OnNewCell: `HRESULT OnNewCell(UINT8cellNo);`  [method page Requirements print Header: Dvdnav.h] */
/* aa451895 OnNewProgram: `HRESULT OnNewProgram(UINT8progNo);`  [method page Requirements print Header: Dvdnav.h] */
/* aa451897 OnNewProgramChain: `HRESULT OnNewProgramChain(IDVDProgramChain* pChain);`  [method page Requirements print Header: Dvdnav.h] */
/* aa451899 OnPlaybackStateChange: `HRESULT OnPlaybackStateChange(EDDVDPlaybackStateeState);`  [method page Requirements print Header: Dvdnav.h] */
/* aa451901 OnSPRMChange: `HRESULT OnSPRMChange(UINT8no,UINT16wValue);`  [method page Requirements print Header: Dvdnav.h] */
/* aa451903 OnUOPChange: `HRESULT OnUOPChange(UINT32newUOPMask);`  [method page Requirements print Header: Dvdnav.h] */

/* ------------------------------------------------------------------ */
/* IDVDParentalManagementTable (aa451905; Requirements rows print Header: Dvdata.h, Dvdata.idl,
 * Link Library: Ddvdids.lib -- GUID linkage, no def).  No vtable
 * layout is published; opaque forward + method records
 * (M44/M69/M80 interface-record policy).  Pages list the methods
 * "in the order the compiler calls them"; records follow the
 * archive page order.  IUnknown (QueryInterface/AddRef/Release)
 * heads every vtable per the page tables. */
typedef struct IDVDParentalManagementTable IDVDParentalManagementTable;
/* aa451907 ConvertParentalLevelToID: `HRESULT ConvertParentalLevelToID(UINT8level,UINT16countryCode,UINT16vtsn,UINT16* parentalID);` */

/* ------------------------------------------------------------------ */
/* IDVDProgramChain (aa451909; Requirements rows print Header: Dvdata.h, Dvdata.idl,
 * Link Library: Ddvdids.lib -- GUID linkage, no def).  No vtable
 * layout is published; opaque forward + method records
 * (M44/M69/M80 interface-record policy).  Pages list the methods
 * "in the order the compiler calls them"; records follow the
 * archive page order.  IUnknown (QueryInterface/AddRef/Release)
 * heads every vtable per the page tables. */
typedef struct IDVDProgramChain IDVDProgramChain;
/* aa451911 GetAudioStreamSelector: `HRESULT GetAudioStreamSelector(UINT8 streamN,UINT16* pSelector);` */
/* aa451913 GetCellPlaybackInfo: `HRESULT GetCellPlaybackInfo(UINT8cn,DVD_CELL_PLAYBACK* pInfo);` */
/* aa451915 GetCellPosition: `HRESULT GetCellPosition(UINT8cn,UINT16* pVOB_ID,UINT8* pC_IDN);` */
/* aa451917 GetContents: `HRESULT GetContents(UINT32* pContents);` */
/* aa451919 GetDomain: `HRESULT GetDomain(IDVDDomain** ppDomain);` */
/* aa451921 GetLink: `HRESULT GetLink(EPGCLinkTypeeType,UINT16* pgcn);` */
/* aa451923 GetNavCommand: `HRESULT GetNavCommand(ENavCmdAreaarea,UINT16commandN,DVD_NAV_CMD* pCmd);` */
/* aa451925 GetNavCommandsCount: `HRESULT GetNavCommandsCount(ENavCmdAreaeArea,UINT16* pCount);` */
/* aa451927 GetPGCN: `HRESULTGetPGCN ( UINT16* pPGCN);` */
/* aa451929 GetPlaybackMode: `HRESULT GetPlaybackMode(EPGCPlaybackMode* pMode,UINT8* pRepeatCount,UINT8* pStillTime);` */
/* aa451931 GetPlaybackTime: `HRESULT GetPlaybackTime(UINT32* pbcdTime);` */
/* aa451933 GetProgramEntryCell: `HRESULT GetProgramEntryCell(UINT16pgno,UINT8* pEntryCN);` */
/* aa451934 GetSubpicturePalette: `HRESULT GetSubpicturePalette(UINT32* pBuf);` */
/* aa451936 GetSubpictureStreamSelector: `HRESULT GetSubpictureStreamSelector(UINT8streamN,UINT32* pSPSel);` */
/* aa451939 GetUserOperationControlMask: `HRESULT GetUserOperationControlMask(UINT32* pmask);` */

/* ------------------------------------------------------------------ */
/* IDVDROM (aa451941; Requirements rows print Header: Dvdata.h, Dvdata.idl,
 * Link Library: Ddvdids.lib -- GUID linkage, no def).  No vtable
 * layout is published; opaque forward + method records
 * (M44/M69/M80 interface-record policy).  Pages list the methods
 * "in the order the compiler calls them"; records follow the
 * archive page order.  IUnknown (QueryInterface/AddRef/Release)
 * heads every vtable per the page tables. */
typedef struct IDVDROM IDVDROM;
/* aa451943 Bind: `HRESULT Bind(UNICODE_PATH path );` */
/* aa451945 CloseVOB: `HRESULT OpenVOB(UINT16 hVOB);`  [page title is CloseVOB; the print misprints the callee as OpenVOB -- archive typo] */
/* aa451947 OpenVOB: `HRESULT OpenVOB(UINT16* hVOB,INT16 obVTSN);` */
/* aa451949 ReadVMGI: `HRESULT ReadVMGIUINT32* length,UINT8** bufptr,);`  [page title is ReadVMGI; the print names it ReadVMGIUINT32] */
/* aa451951 ReadVOB: `HRESULT ReadVOB(UINT16 hVOB,INT8* buf,UINT32 startBlock,UINT32 endBlock);` */
/* aa451953 ReadVTSI: `HRESULT ReadVTSIUINT16zbVTSN, UINT32* length,UINT8** bufPtr );`  [page title is ReadVTSI; the print names it ReadVTSIUINT16zbVTSN] */
/* aa451955 ReleaseMem: `HRESULT ReleaseMem(HRESULT* bufptr);` */
/* aa451957 Unbind: `HRESULT Unbind(void);` */

/* ------------------------------------------------------------------ */
/* IDVDStreamAttributes (aa451959; Requirements rows print Header: Dvdata.h, Dvdata.idl,
 * Link Library: Ddvdids.lib -- GUID linkage, no def).  No vtable
 * layout is published; opaque forward + method records
 * (M44/M69/M80 interface-record policy).  Pages list the methods
 * "in the order the compiler calls them"; records follow the
 * archive page order.  IUnknown (QueryInterface/AddRef/Release)
 * heads every vtable per the page tables. */
typedef struct IDVDStreamAttributes IDVDStreamAttributes;
/* aa451961 GetAudioAttr: `HRESULT GetAudioAttr(UINTnStreamNo,DVD_AUDIO_STREAM_ATTR* pAudioAttr);` */
/* aa451962 GetAudioCount: `HRESULT GetAudioCount(UINT8* pStreamCount);` */
/* aa451964 GetAudioMultichannelUseAttr: `HRESULT GetAudioMultichannelUseAttr(UINT8nStreamNo,DVD_AUDIO_MU_ATTR* pMuse);` */
/* aa451966 GetSubpictureAttr: `HRESULT GetSubpictureAttr(UINT8nStreamNo,DVD_SUBPICTURE_STREAM_ATTR* pSPAttr);` */
/* aa451968 GetSubpictureCount: `HRESULT GetSubpictureCount(UINT8* pStreamCount);` */
/* aa451970 GetVideoAttr: `HRESULT GetVideoAttr(UINT16* pVideoAttr);` */

/* ------------------------------------------------------------------ */
/* IDVDStreamControlInfo (aa451972; Requirements rows print Header: Dvdata.h, Dvdata.idl,
 * Link Library: Ddvdids.lib -- GUID linkage, no def).  No vtable
 * layout is published; opaque forward + method records
 * (M44/M69/M80 interface-record policy).  Pages list the methods
 * "in the order the compiler calls them"; records follow the
 * archive page order.  IUnknown (QueryInterface/AddRef/Release)
 * heads every vtable per the page tables. */
typedef struct IDVDStreamControlInfo IDVDStreamControlInfo;
/* aa451974 GetBlockAddress: `HRESULT GetBlockAddress(UINT32* pLBN);` */
/* aa451976 GetCategory: `HRESULT GetCategory(UINT16* pCat);` */
/* aa451978 GetCellRelativeStartTime: `HRESULT GetCellRelativeStartTime(UINT32* pBCDTime);` */
/* aa451980 GetDataSearchInfo: `HRESULT GetDataSearchInfo(IDVDDataSearchInfo** ppDSI);` */
/* aa451982 GetEndSequencePTM: `HRESULT GetEndSequencePTM(UINT32* pMpegTime);` */
/* aa451984 GetHighlightInfo: `HRESULT GetHighlightInfo(IDVDHighlightInfo** ppHLI);` */
/* aa451986 GetNonSeamlessAngleChangeAddress: `HRESULT GetNonSeamlessAngleChangeAddress(UINT8angle,UINT32* pRLBN);` */
/* aa451987 GetPresentationTimes: `HRESULT GetPresentationTimes(UINT32* pMpegStart,UINT32* pMpegEnd);` */
/* aa452034 GetRecordingAudioInfo: `HRESULT GetRecordingAudioInfo(UINT8stream,DVD_ISRC* pAudio);` */
/* aa452035 GetRecordingSubpictureGroup: `HRESULT GetRecordingSubpictureGroup(UINT8* pSelector);` */
/* aa452036 GetRecordingSubpictureInfo: `HRESULT GetRecordingSubpictureInfo(UINT8bin,DVD_ISRC* pSubInfo);` */
/* aa452037 GetRecordingVideoInfo: `HRESULT GetRecordingVideoInfo(DVD_ISRC* pVideo);` */
/* aa452038 GetUserOperationControlMask: `HRESULT GetUserOperationControlMask(UINT32* pMask);` */
/* aa452039 ReaderLock: `HRESULT ReaderLock(void);` */
/* aa452040 ReaderUnlock: `HRESULT ReaderUnlock(void);` */
/* aa452041 SetNavigationPack: `HRESULT SetNavigationPack(UINT8* pPack);` */

/* ------------------------------------------------------------------ */
/* IDVDTextManager (aa452042; Requirements rows print Header: Dvdata.h, Dvdata.idl,
 * Link Library: Ddvdids.lib -- GUID linkage, no def).  No vtable
 * layout is published; opaque forward + method records
 * (M44/M69/M80 interface-record policy).  Pages list the methods
 * "in the order the compiler calls them"; records follow the
 * archive page order.  IUnknown (QueryInterface/AddRef/Release)
 * heads every vtable per the page tables. */
typedef struct IDVDTextManager IDVDTextManager;
/* aa452043 EnumerateTextLanguageUnits: `HRESULT EnumerateTextLanguageUnits(IEnumDVD_TEXT_LANGUAGE_UNIT** ppEnum);` */
/* aa452044 EnumerateTitleTextItems: `HRESULT EnumerateTitleTextItems(DVD_TEXT_LANGUAGE_UNIT* pTLU,UINT8title,IEnumDVD_TEXT_ITEM** ppEnum);` */
/* aa452045 GetTextItemsCount: `HRESULT GetTextItemsCount(DVD_TEXT_LANGUAGE_UNIT* pTLU,UINT8title,UINT16* pCount);` */

/* ------------------------------------------------------------------ */
/* IDVDTimeMap (aa452046; Requirements rows print Header: Dvdata.h, Dvdata.idl,
 * Link Library: Ddvdids.lib -- GUID linkage, no def).  No vtable
 * layout is published; opaque forward + method records
 * (M44/M69/M80 interface-record policy).  Pages list the methods
 * "in the order the compiler calls them"; records follow the
 * archive page order.  IUnknown (QueryInterface/AddRef/Release)
 * heads every vtable per the page tables. */
typedef struct IDVDTimeMap IDVDTimeMap;
/* aa452048 GetTableHeader: `HRESULT GetTableHeader(UINT8* pTMU,UINT16* pnEntries);` */
/* aa452049 GetVOBUAddress: `HRESULT GetVOBUAddress(UINT16nEntryIndex,UINT32* pVobuRlbn);` */

/* ------------------------------------------------------------------ */
/* IDVDTitleSet (aa452050; Requirements rows print Header: Dvdata.h, Dvdata.idl,
 * Link Library: Ddvdids.lib -- GUID linkage, no def).  No vtable
 * layout is published; opaque forward + method records
 * (M44/M69/M80 interface-record policy).  Pages list the methods
 * "in the order the compiler calls them"; records follow the
 * archive page order.  IUnknown (QueryInterface/AddRef/Release)
 * heads every vtable per the page tables. */
typedef struct IDVDTitleSet IDVDTitleSet;
/* aa452051 GetCategory: `HRESULT GetCategory(UINT32* pCategory);` */
/* aa452052 GetDomain: `HRESULT GetDomain(IDVDDomain** ppDomain);` */
/* aa452053 GetMenu: `HRESULT GetMenu(IDVDMenu** ppMenu);` */
/* aa452054 GetSpecVersion: `HRESULT GetSpecVersion(UINT16* pVersion);` */
/* aa452055 GetTitlePart: `HRESULT GetTitlePart(UINT16ttu,UINT16ptt,UINT16* pPgcn,UINT8* pPgn);` */
/* aa452056 GetTotalTitleUnitCount: `HRESULT GetTotalTitleUnitCount(UINT16* pTtuCount);` */
/* aa452057 GetVolume: `HRESULT GetVolume(IDVDVideoVolume** pVolume);` */
/* aa452058 GetVTSN: `HRESULT GetVTSN(UINT16* pVTSN);` */

/* ------------------------------------------------------------------ */
/* IDVDVideoVolume (ms930853; Requirements rows print Header: Dvdata.h, Dvdata.idl,
 * Link Library: Ddvdids.lib -- GUID linkage, no def).  No vtable
 * layout is published; opaque forward + method records
 * (M44/M69/M80 interface-record policy).  Pages list the methods
 * "in the order the compiler calls them"; records follow the
 * archive page order.  IUnknown (QueryInterface/AddRef/Release)
 * heads every vtable per the page tables. */
typedef struct IDVDVideoVolume IDVDVideoVolume;
/* ms910269 GetSpecVersion: `HRESULT GetSpecVersion(UINT16* pVersion);` */
/* ms910295 GetTextDataManager: `HRESULT GetTextDataManager(IDVDTextManager** ppTxtMgr);` */
/* ms910303 GetTitleSet: `HRESULT GetTitleSet(UINT16* zbVtsn,IDVDTitleSet** ppTitleSet);` */
/* ms910315 GetTitleSetAttributes: `HRESULT GetTitleSetAttributes(UINT16 vtsn,UINT32** pVTSCategory,IDVDStreamAttributes** ppVideoAttr);` */
/* ms910321 GetTitleUnitInfo: `HRESULT GetTitleUnitInfo(UINT16* ttu,DVD_TITLE_SET_INFO* pTUInfo);` */
/* ms910332 GetTotalTitleUnitCount: `HRESULT GetTotalTitleUnitCount(UINT16* ppTTUCount);` */
/* ms910343 GetVideoTitleSetsCount: `HRESULT GetVideoTitleSetsCount(UINT16* pCount );` */
/* ms910354 GetVolumeSetInfo: `HRESULT GetVolumeSetInfo(UINT16* pVolumeSetSizeUINT16* pVolumeNoUINT8* pSide);` */
/* ms910361 InitData: `HRESULT InitData(IDVDROM* pDisk );` */
/* ms910367 Lock: `HRESULT Lock(void);` */
/* ms910374 UnLock: `HRESULT Unlock(void);`  [page title is UnLock; the print misprints the callee as Unlock -- archive typo] */
/* ms930862 GetCategory: `HRESULT GetCategory(UINT32* pCat);` */
/* ms930869 GetFirstPlay: `HRESULT GetFirstPlay(IDVDDomain* ppDomain);` */
/* ms930874 GetMenu: `HRESULT GetMenu(IDVDMenu* ppMenu);` */
/* ms930879 GetParentalManagementTable: `HRESULT GetParentManagementInfo(IDVDParentalManagementTable** ppTable);`  [page title is GetParentalManagementTable; the print misprints the callee as GetParentManagementInfo -- archive typo] */
/* ms930889 GetPOSCode: `HRESULT GetPOSCode(DVD_POS_CODE* pPOSCode );` */
/* ms930895 GetProviderID: `HRESULT GetProviderID(DVD_PROVIDER_ID* pProvider);` */

/* ------------------------------------------------------------------ */
/* IEnumDVD_CELL_PIECE (ms910411; Requirements rows print Header: Dvdata.h, Dvdata.idl,
 * Link Library: Ddvdids.lib -- GUID linkage, no def).  No vtable
 * layout is published; opaque forward + method records
 * (M44/M69/M80 interface-record policy).  Pages list the methods
 * "in the order the compiler calls them"; records follow the
 * archive page order.  IUnknown (QueryInterface/AddRef/Release)
 * heads every vtable per the page tables. */
typedef struct IEnumDVD_CELL_PIECE IEnumDVD_CELL_PIECE;
/* (no method pages preserved for IEnumDVD_CELL_PIECE) */

/* ------------------------------------------------------------------ */
/* IEnumDVD_TEXT_ITEM (ms910419; Requirements rows print Header: Dvdata.h, Dvdata.idl,
 * Link Library: Ddvdids.lib -- GUID linkage, no def).  No vtable
 * layout is published; opaque forward + method records
 * (M44/M69/M80 interface-record policy).  Pages list the methods
 * "in the order the compiler calls them"; records follow the
 * archive page order.  IUnknown (QueryInterface/AddRef/Release)
 * heads every vtable per the page tables. */
typedef struct IEnumDVD_TEXT_ITEM IEnumDVD_TEXT_ITEM;
/* (no method pages preserved for IEnumDVD_TEXT_ITEM) */

/* ------------------------------------------------------------------ */
/* IEnumDVD_TEXT_LANGUAGE_UNIT (ms910425; Requirements rows print Header: Dvdata.h, Dvdata.idl,
 * Link Library: Ddvdids.lib -- GUID linkage, no def).  No vtable
 * layout is published; opaque forward + method records
 * (M44/M69/M80 interface-record policy).  Pages list the methods
 * "in the order the compiler calls them"; records follow the
 * archive page order.  IUnknown (QueryInterface/AddRef/Release)
 * heads every vtable per the page tables. */
typedef struct IEnumDVD_TEXT_LANGUAGE_UNIT IEnumDVD_TEXT_LANGUAGE_UNIT;
/* (no method pages preserved for IEnumDVD_TEXT_LANGUAGE_UNIT) */

/* ------------------------------------------------------------------ */
/* IEnumDVD_XXXX (ms910434; Requirements rows print Header: Dvdata.h, Dvdata.idl,
 * Link Library: Ddvdids.lib -- GUID linkage, no def).  No vtable
 * layout is published; opaque forward + method records
 * (M44/M69/M80 interface-record policy).  Pages list the methods
 * "in the order the compiler calls them"; records follow the
 * archive page order.  IUnknown (QueryInterface/AddRef/Release)
 * heads every vtable per the page tables. */
typedef struct IEnumDVD_XXXX IEnumDVD_XXXX;
/* ms910442 Clone: `HRESULT Clone(IEnumDVD_XXXX** ppenum);` */
/* ms910451 Next: `HRESULT Next(ULONG celt,DVD_XXXX* rgelt,ULONG* pceltFetched);` */
/* ms910520 Reset: `HRESULT Reset(void)`  [page title is Reset; the print misprints the callee as Reset -- archive typo] */
/* ms910529 Skip: `HRESULT Skip(ULONG celt);` */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_DVDATA */
