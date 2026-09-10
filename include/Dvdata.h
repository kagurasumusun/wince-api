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

/* ------------------------------------------------------------------
 * Book surface: graphics-book (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa452397 DVD-Video API Data Types/UNICODE_PATH (Header: Dvdata.h, Dvdata.idl.) */
/* aa451672 DVD-Video API Enumerated Types/EDVDDomainType (Header: Dvdata.h, Dvdata.idl.) */
/* aa451678 DVD-Video API Enumerated Types/ENavCmdArea (Header: Dvdata.h, Dvdata.idl.) */
/* aa451695 DVD-Video API Enumerated Types/EPGCLinkType (Header: Dvdata.h, Dvdata.idl.) */
/* aa451696 DVD-Video API Enumerated Types/EPGCPlaybackMode (Header: Dvdata.h, Dvdata.idl.) */
/* aa451819 DVD-Video API Interfaces/IDVDDataSearchInfo (Header: Dvdata.h, Dvdata.idl.) */
/* aa451834 DVD-Video API Interfaces/IDVDDomain (Header: Dvdata.h, Dvdata.idl.) */
/* aa451848 DVD-Video API Interfaces/IDVDHighlightInfo (Header: Dvdata.h, Dvdata.idl.) */
/* aa451862 DVD-Video API Interfaces/IDVDMenu (Header: Dvdata.h, Dvdata.idl.) */
/* aa451865 DVD-Video API Interfaces/IDVDNavDataStatusSink (Header: Dvdata.h, Dvdata.idl.) */
/* aa451878 DVD-Video API Interfaces/IDVDNavigatorSink (Header: Dvdata.h, Dvdata.idl.) */
/* aa451905 DVD-Video API Interfaces/IDVDParentalManagementTable (Header: Dvdata.h, Dvdata.idl.) */
/* aa451909 DVD-Video API Interfaces/IDVDProgramChain (Header: Dvdata.h, Dvdata.idl.) */
/* aa451941 DVD-Video API Interfaces/IDVDROM (Header: Dvdata.h, Dvdata.idl.) */
/* aa451959 DVD-Video API Interfaces/IDVDStreamAttributes (Header: Dvdata.h, Dvdata.idl.) */
/* aa451972 DVD-Video API Interfaces/IDVDStreamControlInfo (Header: Dvdata.h, Dvdata.idl.) */
/* aa452042 DVD-Video API Interfaces/IDVDTextManager (Header: Dvdata.h, Dvdata.idl.) */
/* aa452046 DVD-Video API Interfaces/IDVDTimeMap (Header: Dvdata.h, Dvdata.idl.) */
/* aa452050 DVD-Video API Interfaces/IDVDTitleSet (Header: Dvdata.h, Dvdata.idl.) */
/* ms930853 DVD-Video API Interfaces/IDVDVideoVolume (Header: Dvdata.h, Dvdata.idl.) */
/* ms910434 DVD-Video API Interfaces/IEnumDVD_XXXX (Header: Dvdata.h, Dvdata.idl.) */
/* ms925307 DVD-Video API Reference/DVD-Video API Macros (Header: Dvdata.h, Dvdnav.h, Dvdata.idl, Dvdnav.idl.) */
/* aa451618 DVD-Video API Structures/DVD_AUDIO_STREAM_ATTR (Header: Dvdata.h, Dvdata.idl.) */
/* aa451619 DVD-Video API Structures/DVD_CELL_PIECE (Header: Dvdata.h, Dvdata.idl.) */
/* aa451620 DVD-Video API Structures/DVD_CELL_PLAYBACK (Header: Dvdata.h, Dvdata.idl.) */
/* aa451621 DVD-Video API Structures/DVD_ISRC (Header: Dvdata.h, Dvdata.idl.) */
/* aa451622 DVD-Video API Structures/DVD_NAV_CMD (Header: Dvdata.h, Dvdata.idl.) */
/* aa451623 DVD-Video API Structures/DVD_POS_CODE (Header: Dvdata.h, Dvdata.idl.) */
/* aa451624 DVD-Video API Structures/DVD_PROVIDER_ID (Header: Dvdata.h, Dvdata.idl.) */
/* aa451625 DVD-Video API Structures/DVD_RECT (Header: Dvdata.h, Dvdata.idl.) */
/* aa451626 DVD-Video API Structures/DVD_SUBPICTURE_STREAM_ATTR (Header: Dvdata.h, Dvdata.idl.) */
/* aa451627 DVD-Video API Structures/DVD_TEXT_ITEM (Header: Dvdata.h, Dvdata.idl.) */
/* aa451628 DVD-Video API Structures/DVD_TEXT_LANGUAGE_UNIT (Header: Dvdata.h, Dvdata.idl.) */
/* aa451629 DVD-Video API Structures/DVD_TITLE_SET_INFO (Header: Dvdata.h, Dvdata.idl.) */
/* aa451820 IDVDDataSearchInfo/IDVDDataSearchInfo::GetAudioGapInfo (Header: Dvdata.h, Dvdata.idl.) */
/* aa451821 IDVDDataSearchInfo/IDVDDataSearchInfo::GetC_IDN (Header: Dvdata.h, Dvdata.idl.) */
/* aa451822 IDVDDataSearchInfo/IDVDDataSearchInfo::GetControlInfo (Header: Dvdata.h, Dvdata.idl.) */
/* aa451823 IDVDDataSearchInfo/IDVDDataSearchInfo::GetInterleavedUnitEndAddress (Header: Dvdata.h, Dvdata.idl.) */
/* aa451824 IDVDDataSearchInfo/IDVDDataSearchInfo::GetNextInterleavedUnit (Header: Dvdata.h, Dvdata.idl.) */
/* aa451825 IDVDDataSearchInfo/IDVDDataSearchInfo::GetRefPictureAddress (Header: Dvdata.h, Dvdata.idl.) */
/* aa451826 IDVDDataSearchInfo/IDVDDataSearchInfo::GetSCRBase (Header: Dvdata.h, Dvdata.idl.) */
/* aa451827 IDVDDataSearchInfo/IDVDDataSearchInfo::GetSeamlessAngleChangeAddress (Header: Dvdata.h, Dvdata.idl.) */
/* aa451828 IDVDDataSearchInfo/IDVDDataSearchInfo::GetSeamlessCategory (Header: Dvdata.h, Dvdata.idl.) */
/* aa451829 IDVDDataSearchInfo/IDVDDataSearchInfo::GetSyncAudioAddress (Header: Dvdata.h, Dvdata.idl.) */
/* aa451830 IDVDDataSearchInfo/IDVDDataSearchInfo::GetSyncSPAddress (Header: Dvdata.h, Dvdata.idl.) */
/* aa451831 IDVDDataSearchInfo/IDVDDataSearchInfo::GetUnitEndAddress (Header: Dvdata.h, Dvdata.idl.) */
/* aa451832 IDVDDataSearchInfo/IDVDDataSearchInfo::GetUnitStepAddress (Header: Dvdata.h, Dvdata.idl.) */
/* aa451833 IDVDDataSearchInfo/IDVDDataSearchInfo::GetVOB_ID (Header: Dvdata.h, Dvdata.idl.) */
/* aa451835 IDVDDomain/IDVDDomain::GetCellPieceEnumerator (Header: Dvdata.h, Dvdata.idl.) */
/* aa451836 IDVDDomain/IDVDDomain::GetPGC (Header: Dvdata.h, Dvdata.idl.) */
/* aa451837 IDVDDomain/IDVDDomain::GetPGCCount (Header: Dvdata.h, Dvdata.idl.) */
/* aa451838 IDVDDomain/IDVDDomain::GetSpace (Header: Dvdata.h, Dvdata.idl.) */
/* aa451839 IDVDDomain/IDVDDomain::GetStreamAttributes (Header: Dvdata.h, Dvdata.idl.) */
/* aa451840 IDVDDomain/IDVDDomain::GetTimeMap (Header: Dvdata.h, Dvdata.idl.) */
/* aa451841 IDVDDomain/IDVDDomain::GetTitleSet (Header: Dvdata.h, Dvdata.idl.) */
/* aa451842 IDVDDomain/IDVDDomain::GetTotalVideoObjects (Header: Dvdata.h, Dvdata.idl.) */
/* aa451843 IDVDDomain/IDVDDomain::GetTotalVOBUnits (Header: Dvdata.h, Dvdata.idl.) */
/* aa451844 IDVDDomain/IDVDDomain::GetType (Header: Dvdata.h, Dvdata.idl.) */
/* aa451845 IDVDDomain/IDVDDomain::GetVOBFileID (Header: Dvdata.h, Dvdata.idl.) */
/* aa451846 IDVDDomain/IDVDDomain::GetVOBUTablePtr (Header: Dvdata.h, Dvdata.idl.) */
/* aa451847 IDVDDomain/IDVDDomain::GetVolume (Header: Dvdata.h, Dvdata.idl.) */
/* aa451849 IDVDHighlightInfo/IDVDHighlightInfo::GetAdjacentButton (Header: Dvdata.h, Dvdata.idl.) */
/* aa451850 IDVDHighlightInfo/IDVDHighlightInfo::GetButtonColorInfo (Header: Dvdata.h, Dvdata.idl.) */
/* aa451851 IDVDHighlightInfo/IDVDHighlightInfo::GetButtonCommand (Header: Dvdata.h, Dvdata.idl.) */
/* aa451852 IDVDHighlightInfo/IDVDHighlightInfo::GetButtonCount (Header: Dvdata.h, Dvdata.idl.) */
/* aa451853 IDVDHighlightInfo/IDVDHighlightInfo::GetButtonMode (Header: Dvdata.h, Dvdata.idl.) */
/* aa451854 IDVDHighlightInfo/IDVDHighlightInfo::GetButtonOffset (Header: Dvdata.h, Dvdata.idl.) */
/* aa451855 IDVDHighlightInfo/IDVDHighlightInfo::GetButtonPositionInfo (Header: Dvdata.h, Dvdata.idl.) */
/* aa451856 IDVDHighlightInfo/IDVDHighlightInfo::GetDefaultActionButton (Header: Dvdata.h, Dvdata.idl.) */
/* aa451857 IDVDHighlightInfo/IDVDHighlightInfo::GetHLIStatus (Header: Dvdata.h, Dvdata.idl.) */
/* aa451858 IDVDHighlightInfo/IDVDHighlightInfo::GetInitialSelectionButton (Header: Dvdata.h, Dvdata.idl.) */
/* aa451859 IDVDHighlightInfo/IDVDHighlightInfo::GetNumberedButtonCount (Header: Dvdata.h, Dvdata.idl.) */
/* aa451860 IDVDHighlightInfo/IDVDHighlightInfo::GetPTMs (Header: Dvdata.h, Dvdata.idl.) */
/* aa451861 IDVDHighlightInfo/IDVDHighlightInfo::GetStreamingInfo (Header: Dvdata.h, Dvdata.idl.) */
/* aa451863 IDVDMenu/IDVDMenu::GetDomain (Header: Dvdata.h, Dvdata.idl.) */
/* aa451864 IDVDMenu/IDVDMenu::GetMenuLanguageInfo (Header: Dvdata.h, Dvdata.idl.) */
/* aa451866 IDVDNavDataStatusSink/IDVDNavDataStatusSink::NotifyNewPCI (Header: Dvdata.h, Dvdata.idl.) */
/* aa451907 IDVDParentalManagementTable/IDVDParentalManagementTable::ConvertParentalLevelToID (Header: Dvdata.h, Dvdata.idl.) */
/* aa451911 IDVDProgramChain/IDVDProgramChain::GetAudioStreamSelector (Header: Dvdata.h, Dvdata.idl.) */
/* aa451913 IDVDProgramChain/IDVDProgramChain::GetCellPlaybackInfo (Header: Dvdata.h, Dvdata.idl.) */
/* aa451915 IDVDProgramChain/IDVDProgramChain::GetCellPosition (Header: Dvdata.h, Dvdata.idl.) */
/* aa451917 IDVDProgramChain/IDVDProgramChain::GetContents (Header: Dvdata.h, Dvdata.idl.) */
/* aa451919 IDVDProgramChain/IDVDProgramChain::GetDomain (Header: Dvdata.h, Dvdata.idl.) */
/* aa451921 IDVDProgramChain/IDVDProgramChain::GetLink (Header: Dvdata.h, Dvdata.idl.) */
/* aa451923 IDVDProgramChain/IDVDProgramChain::GetNavCommand (Header: Dvdata.h, Dvdata.idl.) */
/* aa451925 IDVDProgramChain/IDVDProgramChain::GetNavCommandsCount (Header: Dvdata.h, Dvdata.idl.) */
/* aa451927 IDVDProgramChain/IDVDProgramChain::GetPGCN (Header: Dvdata.h, Dvdata.idl.) */
/* aa451929 IDVDProgramChain/IDVDProgramChain::GetPlaybackMode (Header: Dvdata.h, Dvdata.idl.) */
/* aa451931 IDVDProgramChain/IDVDProgramChain::GetPlaybackTime (Header: Dvdata.h, Dvdata.idl.) */
/* aa451933 IDVDProgramChain/IDVDProgramChain::GetProgramEntryCell (Header: Dvdata.h, Dvdata.idl.) */
/* aa451934 IDVDProgramChain/IDVDProgramChain::GetSubpicturePalette (Header: Dvdata.h, Dvdata.idl.) */
/* aa451936 IDVDProgramChain/IDVDProgramChain::GetSubpictureStreamSelector (Header: Dvdata.h, Dvdata.idl.) */
/* aa451939 IDVDProgramChain/IDVDProgramChain::GetUserOperationControlMask (Header: Dvdata.h, Dvdata.idl.) */
/* aa451945 IDVDROM/IDVDROM::CloseVOB (Header: Dvdata.h, Dvdata.idl.) */
/* aa451947 IDVDROM/IDVDROM::OpenVOB (Header: Dvdata.h, Dvdata.idl.) */
/* aa451949 IDVDROM/IDVDROM::ReadVMGI (Header: Dvdata.h, Dvdata.idl.) */
/* aa451951 IDVDROM/IDVDROM::ReadVOB (Header: Dvdata.h, Dvdata.idl.) */
/* aa451953 IDVDROM/IDVDROM::ReadVTSI (Header: Dvdata.h, Dvdata.idl.) */
/* aa451955 IDVDROM/IDVDROM::ReleaseMem (Header: Dvdata.h, Dvdata.idl.) */
/* aa451961 IDVDStreamAttributes/IDVDStreamAttributes::GetAudioAttr (Header: Dvdata.h, Dvdata.idl.) */
/* aa451962 IDVDStreamAttributes/IDVDStreamAttributes::GetAudioCount (Header: Dvdata.h, Dvdata.idl.) */
/* aa451964 IDVDStreamAttributes/IDVDStreamAttributes::GetAudioMultichannelUseAttr (Header: Dvdata.h, Dvdata.idl.) */
/* aa451966 IDVDStreamAttributes/IDVDStreamAttributes::GetSubpictureAttr (Header: Dvdata.h, Dvdata.idl.) */
/* aa451968 IDVDStreamAttributes/IDVDStreamAttributes::GetSubpictureCount (Header: Dvdata.h, Dvdata.idl.) */
/* aa451970 IDVDStreamAttributes/IDVDStreamAttributes::GetVideoAttr (Header: Dvdata.h, Dvdata.idl.) */
/* aa451974 IDVDStreamControlInfo/IDVDStreamControlInfo::GetBlockAddress (Header: Dvdata.h, Dvdata.idl.) */
/* aa451976 IDVDStreamControlInfo/IDVDStreamControlInfo::GetCategory (Header: Dvdata.h, Dvdata.idl.) */
/* aa451978 IDVDStreamControlInfo/IDVDStreamControlInfo::GetCellRelativeStartTime (Header: Dvdata.h, Dvdata.idl.) */
/* aa451980 IDVDStreamControlInfo/IDVDStreamControlInfo::GetDataSearchInfo (Header: Dvdata.h, Dvdata.idl.) */
/* aa451982 IDVDStreamControlInfo/IDVDStreamControlInfo::GetEndSequencePTM (Header: Dvdata.h, Dvdata.idl.) */
/* aa451984 IDVDStreamControlInfo/IDVDStreamControlInfo::GetHighlightInfo (Header: Dvdata.h, Dvdata.idl.) */
/* aa451986 IDVDStreamControlInfo/IDVDStreamControlInfo::GetNonSeamlessAngleChangeAddress (Header: Dvdata.h, Dvdata.idl.) */
/* aa451987 IDVDStreamControlInfo/IDVDStreamControlInfo::GetPresentationTimes (Header: Dvdata.h, Dvdata.idl.) */
/* aa452034 IDVDStreamControlInfo/IDVDStreamControlInfo::GetRecordingAudioInfo (Header: Dvdata.h, Dvdata.idl.) */
/* aa452035 IDVDStreamControlInfo/IDVDStreamControlInfo::GetRecordingSubpictureGroup (Header: Dvdata.h, Dvdata.idl.) */
/* aa452036 IDVDStreamControlInfo/IDVDStreamControlInfo::GetRecordingSubpictureInfo (Header: Dvdata.h, Dvdata.idl.) */
/* aa452037 IDVDStreamControlInfo/IDVDStreamControlInfo::GetRecordingVideoInfo (Header: Dvdata.h, Dvdata.idl.) */
/* aa452038 IDVDStreamControlInfo/IDVDStreamControlInfo::GetUserOperationControlMask (Header: Dvdata.h, Dvdata.idl.) */
/* aa452039 IDVDStreamControlInfo/IDVDStreamControlInfo::ReaderLock (Header: Dvdata.h, Dvdata.idl.) */
/* aa452040 IDVDStreamControlInfo/IDVDStreamControlInfo::ReaderUnlock (Header: Dvdata.h, Dvdata.idl.) */
/* aa452041 IDVDStreamControlInfo/IDVDStreamControlInfo::SetNavigationPack (Header: Dvdata.h, Dvdata.idl.) */
/* aa452043 IDVDTextManager/IDVDTextManager::EnumerateTextLanguageUnits (Header: Dvdata.h, Dvdata.idl.) */
/* aa452044 IDVDTextManager/IDVDTextManager::EnumerateTitleTextItems (Header: Dvdata.h, Dvdata.idl.) */
/* aa452045 IDVDTextManager/IDVDTextManager::GetTextItemsCount (Header: Dvdata.h, Dvdata.idl.) */
/* aa452048 IDVDTimeMap/IDVDTimeMap::GetTableHeader (Header: Dvdata.h, Dvdata.idl.) */
/* aa452049 IDVDTimeMap/IDVDTimeMap::GetVOBUAddress (Header: Dvdata.h, Dvdata.idl.) */
/* aa452051 IDVDTitleSet/IDVDTitleSet::GetCategory (Header: Dvdata.h, Dvdata.idl.) */
/* aa452052 IDVDTitleSet/IDVDTitleSet::GetDomain (Header: Dvdata.h, Dvdata.idl.) */
/* aa452053 IDVDTitleSet/IDVDTitleSet::GetMenu (Header: Dvdata.h, Dvdata.idl.) */
/* aa452054 IDVDTitleSet/IDVDTitleSet::GetSpecVersion (Header: Dvdata.h, Dvdata.idl.) */
/* aa452055 IDVDTitleSet/IDVDTitleSet::GetTitlePart (Header: Dvdata.h, Dvdata.idl.) */
/* aa452056 IDVDTitleSet/IDVDTitleSet::GetTotalTitleUnitCount (Header: Dvdata.h, Dvdata.idl.) */
/* aa452057 IDVDTitleSet/IDVDTitleSet::GetVolume (Header: Dvdata.h, Dvdata.idl.) */
/* aa452058 IDVDTitleSet/IDVDTitleSet::GetVTSN (Header: Dvdata.h, Dvdata.idl.) */
/* ms930862 IDVDVideoVolume/IDVDVideoVolume::GetCategory (Header: Dvdata.h, Dvdata.idl.) */
/* ms930869 IDVDVideoVolume/IDVDVideoVolume::GetFirstPlay (Header: Dvdata.h, Dvdata.idl.) */
/* ms930874 IDVDVideoVolume/IDVDVideoVolume::GetMenu (Header: Dvdata.h, Dvdata.idl.) */
/* ms930879 IDVDVideoVolume/IDVDVideoVolume::GetParentalManagementTable (Header: Dvdata.h, Dvdata.idl.) */
/* ms930889 IDVDVideoVolume/IDVDVideoVolume::GetPOSCode (Header: Dvdata.h, Dvdata.idl.) */
/* ms930895 IDVDVideoVolume/IDVDVideoVolume::GetProviderID (Header: Dvdata.h, Dvdata.idl.) */
/* ms910269 IDVDVideoVolume/IDVDVideoVolume::GetSpecVersion (Header: Dvdata.h, Dvdata.idl.) */
/* ms910295 IDVDVideoVolume/IDVDVideoVolume::GetTextDataManager (Header: Dvdata.h, Dvdata.idl.) */
/* ms910303 IDVDVideoVolume/IDVDVideoVolume::GetTitleSet (Header: Dvdata.h, Dvdata.idl.) */
/* ms910315 IDVDVideoVolume/IDVDVideoVolume::GetTitleSetAttributes (Header: Dvdata.h, Dvdata.idl.) */
/* ms910321 IDVDVideoVolume/IDVDVideoVolume::GetTitleUnitInfo (Header: Dvdata.h, Dvdata.idl.) */
/* ms910332 IDVDVideoVolume/IDVDVideoVolume::GetTotalTitleUnitCount (Header: Dvdata.h, Dvdata.idl.) */
/* ms910343 IDVDVideoVolume/IDVDVideoVolume::GetVideoTitleSetsCount (Header: Dvdata.h, Dvdata.idl.) */
/* ms910354 IDVDVideoVolume/IDVDVideoVolume::GetVolumeSetInfo (Header: Dvdata.h, Dvdata.idl.) */
/* ms910361 IDVDVideoVolume/IDVDVideoVolume::InitData (Header: Dvdata.h, Dvdata.idl.) */
/* ms910367 IDVDVideoVolume/IDVDVideoVolume::Lock (Header: Dvdata.h, Dvdata.idl.) */
/* ms910374 IDVDVideoVolume/IDVDVideoVolume::UnLock (Header: Dvdata.h, Dvdata.idl.) */
/* ms910411 IEnumDVD_XXXX/IEnumDVD_CELL_PIECE (Header: Dvdata.h, Dvdata.idl.) */
/* ms910419 IEnumDVD_XXXX/IEnumDVD_TEXT_ITEM (Header: Dvdata.h, Dvdata.idl.) */
/* ms910425 IEnumDVD_XXXX/IEnumDVD_TEXT_LANGUAGE_UNIT (Header: Dvdata.h, Dvdata.idl.) */
/* ms910442 IEnumDVD_XXXX/IEnumDVD_XXXX::Clone (Header: Dvdata.h, Dvdata.idl.) */
/* ms910451 IEnumDVD_XXXX/IEnumDVD_XXXX::Next (Header: Dvdata.h, Dvdata.idl.) */
/* ms910520 IEnumDVD_XXXX/IEnumDVD_XXXX::Reset (Header: Dvdata.h, Dvdata.idl.) */
/* ms910529 IEnumDVD_XXXX/IEnumDVD_XXXX::Skip (Header: Dvdata.h, Dvdata.idl.) */

/* ------------------------------------------------------------------
 * Book surface: graphics-book (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa451223 Adding More Player Capabilities/Callbacks */
/* aa451230 Adding More Player Capabilities/Changing Discs */
/* aa451233 Adding More Player Capabilities/Checking Region Codes */
/* ms924617 Adding More Player Capabilities/Scan Modes and Capabilities */
/* aa451413 Adding More Player Capabilities/User Navigation */
/* ms940061 Advanced Capture Topics/Handling Repaint Events in Video Capture */
/* ms940075 Advanced Capture Topics/Using the Smart Tee Filter */
/* ms940083 Advanced Capture Topics/Working with Pin Categories */
/* aa451172 Advanced DirectDraw Information/Alpha Blitting */
/* aa451258 Advanced DirectDraw Information/Converting Between YUV and RGB */
/* aa451306 Advanced DirectDraw Information/Determining the Capabilities of the Display Hardware */
/* aa451330 Advanced DirectDraw Information/DirectDraw Applications and Window Styles */
/* aa451357 Advanced DirectDraw Information/Displaying a Window in Full-Screen Mode */
/* ms923387 Advanced DirectDraw Information/Getting the Flip and Blit Status */
/* ms924136 Advanced DirectDraw Information/Matching True RGB Colors to the Frame Buffer's Color Space */
/* ms924571 Advanced DirectDraw Information/Porting Older DirectDraw Code */
/* ms924647 Advanced DirectDraw Information/Storing Bitmaps in Display Memory */
/* ms924664 Advanced DirectDraw Information/Taking Advantage of DMA Support */
/* aa451405 Advanced DirectDraw Information/Triple Buffering */
/* aa451425 Advanced DirectDraw Information/Using DirectDraw Palettes in Windowed Mode */
/* aa451460 Advanced DirectDraw Information/Video Ports */
/* aa451255 Advanced DVD Player Application Topics/Content Protection */
/* ms923202 Advanced DVD Player Application Topics/DVD-Video in a Window */
/* ms923357 Advanced DVD Player Application Topics/Examining the DVDSample Sample Application */
/* ms924153 Advanced DVD Player Application Topics/Mouse Navigation */
/* aa451395 Advanced DVD Player Application Topics/Time Calculation */
/* ms923393 Alternative Video Renderers/Handling Dynamic Format Changes */
/* ms923394 Alternative Video Renderers/Handling EC_REPAINT Notifications */
/* ms923395 Alternative Video Renderers/Handling End-of-stream and Flushing Notifications */
/* ms923397 Alternative Video Renderers/Handling Notifications in Full-Screen Mode */
/* ms923399 Alternative Video Renderers/Handling Persistent Properties */
/* ms923400 Alternative Video Renderers/Handling State Changes and Pause Completion */
/* ms923401 Alternative Video Renderers/Handling Termination */
/* ms924652 Alternative Video Renderers/Summary of Notifications */
/* ms925287 Alternative Video Renderers/Writing an Alternative Renderer */
/* ms923173 Architectural Overview of the DVD-Video API/DVD-Video API Interface Map */
/* ms923178 Architectural Overview of the DVD-Video API/DVD-Video API Object Architecture */
/* ms923193 Architectural Overview of the DVD-Video API/DVD-Video API Rendering */
/* ms925328 ASX Elements Reference/ABSTRACT */
/* ms925588 ASX Elements Reference/ASX */
/* ms925730 ASX Elements Reference/AUTHOR */
/* ms925786 ASX Elements Reference/BASE */
/* ms926787 ASX Elements Reference/COPYRIGHT */
/* aa451616 ASX Elements Reference/DURATION (ASX Element) */
/* aa451683 ASX Elements Reference/ENDMARKER */
/* aa451685 ASX Elements Reference/ENTRY */
/* aa451687 ASX Elements Reference/ENTRYREF */
/* aa451705 ASX Elements Reference/EVENT */
/* ms932215 ASX Elements Reference/MOREINFO */
/* ms932252 ASX Elements Reference/PARAM */
/* ms932281 ASX Elements Reference/REF */
/* ms932287 ASX Elements Reference/REPEAT */
/* ms932317 ASX Elements Reference/STARTMARKER */
/* ms932318 ASX Elements Reference/STARTTIME */
/* aa452393 ASX Elements Reference/TITLE (ASX Element) */
/* ms940067 Audio and Video Capture Support/Pin Property Set */
/* ms940077 Audio and Video Capture Support/Video Capture */
/* ms940082 Audio and Video Capture Support/Windows Media Applications */
/* aa451187 Audio/Audio Compression Manager */
/* ms940101 Audio/Waveform Audio */
/* aa451195 AVI RIFF File Reference/AVI Main Header */
/* aa451197 AVI RIFF File Reference/AVI RIFF Form */
/* aa451198 AVI RIFF File Reference/AVI Stream Headers */
/* ms924648 AVI RIFF File Reference/Stream Data (LIST 'movi' Chunk) */
/* aa451239 Base Classes that Implement Interfaces/Clock Base Classes */
/* ms923232 Base Classes that Implement Interfaces/Enumerator Base Classes */
/* ms923365 Base Classes that Implement Interfaces/Filter Base Classes */
/* ms924201 Base Classes that Implement Interfaces/Pin Base Classes */
/* aa451401 Base Classes that Implement Interfaces/Transport Base Classes */
/* aa451201 Base Classes/Base Classes that Implement Interfaces */
/* aa451227 Base Classes/CBaseObject and CUnknown Classes */
/* aa451245 Basic Concepts of Surfaces/Color Keying */
/* ms924203 Basic Concepts of Surfaces/Pixel Formats */
/* ms924659 Basic Concepts of Surfaces/Surface Interfaces */
/* ms925253 Basic Concepts of Surfaces/What Are Surfaces? */
/* ms925262 Basic Concepts of Surfaces/Width vs. Pitch */
/* aa451208 Blitting to Surfaces/Blit Timing */
/* aa451210 Blitting to Surfaces/Blitting Basics */
/* aa451212 Blitting to Surfaces/Blitting to Multiple Windows */
/* aa451214 Blitting to Surfaces/Blitting with Blt */
/* aa451215 Blitting to Surfaces/Blitting with BltFast */
/* aa451243 Blitting to Surfaces/Color Fills */
/* aa451400 Blitting to Surfaces/Transparent Blitting */
/* ms940049 Capturing Video to a File/Capturing to Multiple Files */
/* ms940051 Capturing Video to a File/Capturing Video to a Windows Media File */
/* ms940052 Capturing Video to a File/Combining Video Capture and Preview */
/* ms940058 Capturing Video to a File/Custom File Formats */
/* aa451418 Color Controls/Using Color Controls */
/* ms925249 Color Controls/What Are Color Controls? */
/* ms924594 COM Reference Count Semantics for Surfaces/Reference Counts for Complex Surfaces */
/* ms924598 COM Reference Count Semantics for Surfaces/Releasing Surfaces */
/* ms925258 COM Reference Count Semantics for Surfaces/When Reference Counts will Change */
/* ms923406 Connecting Transform Filters/Allocator Negotiation */
/* aa451252 Connecting Transform Filters/Connecting Filter Graphs: An Example */
/* ms923245 Connecting Transform Filters/Establishing Media Type Connections */
/* aa451385 Connecting Transform Filters/The Connection Process: A Summary */
/* ms925256 Connecting Transform Filters/When Reconnections Occur */
/* ms924665 Cooperative Levels/Testing Cooperative Levels */
/* ms923183 Creating a Simple DVD Player/DVD-Video API Objects */
/* ms923381 Creating a Simple DVD Player/Fundamental DVD-Video API Interfaces */
/* ms923418 Creating a Simple DVD Player/Implementing First Play */
/* ms924606 Creating a Simple DVD Player/Responding to User Commands */
/* aa451302 Creating a Transform Filter/Determine if the Filter Must Copy Media Samples */
/* aa451303 Creating a Transform Filter/Determine Which Base Classes to Use */
/* ms923427 Creating a Transform Filter/Instantiate the Filter */
/* ms924133 Creating a Transform Filter/Make Added Interfaces Available Through NonDelegatingQueryInterface */
/* ms924181 Creating a Transform Filter/Override the Base Class Member Functions */
/* ms925284 Creating a Transform Filter/Write a Transform Filter */
/* ms940044 Creating ASF Files in DirectShow/Building a Filter Graph for ASF Output */
/* ms940055 Creating ASF Files in DirectShow/Configuring the ASF Writer */
/* aa451267 Creating Surfaces/Creating an Off-Screen Surface */
/* aa451271 Creating Surfaces/Creating Client Memory Surfaces */
/* aa451272 Creating Surfaces/Creating Complex Surfaces and Flipping Chains */
/* aa451285 Creating Surfaces/Creating the Primary Surface */
/* aa451288 Creating Surfaces/Creating Wide Surfaces */
/* ms923376 Creating Surfaces/Flipping Surfaces */
/* ms940060 Data Flow in the Filter Graph/Filter States */
/* ms923384 Data Flow in the Filter Graph/Generating New Samples */
/* ms924579 Data Flow in the Filter Graph/Processing a Sample */
/* ms924586 Data Flow in the Filter Graph/Push versus Pull */
/* aa451393 Data Flow in the Filter Graph/Thread Usage */
/* aa452477 Digital Rights Management/DRM Application Development */
/* ms923153 Digital Rights Management/DRM Migration */
/* aa451316 Digital Rights Management/DRM OS Design Development */
/* ms932679 Digital Rights Management/DRM Samples */
/* aa451317 Digital Rights Management/DRM Security */
/* aa451165 DirectDraw Application Development/Advanced DirectDraw Information */
/* ms923363 DirectDraw Application Development/Exploring Graphics Concepts */
/* ms923386 DirectDraw Application Development/Getting Started with DirectDraw */
/* ms925277 DirectDraw Application Development/Working with DirectDraw Clippers */
/* ms925278 DirectDraw Application Development/Working with DirectDraw Objects */
/* ms925279 DirectDraw Application Development/Working with DirectDraw Palettes */
/* ms925280 DirectDraw Application Development/Working with DirectDraw Surfaces */
/* ms925281 DirectDraw Application Development/Working with Graphics Devices */
/* aa451182 DirectDraw Middleware Architecture/Architectural Overview for DirectDraw */
/* aa451334 DirectDraw Middleware Architecture/DirectDraw Object Types */
/* ms923402 DirectDraw Middleware Architecture/Hardware Abstraction Layer */
/* ms924638 DirectDraw Middleware Architecture/Software Emulation */
/* ms924663 DirectDraw Middleware Architecture/System Integration */
/* ms932573 DirectDraw/DirectDraw Application Development */
/* aa451332 DirectDraw/DirectDraw Migration */
/* aa451335 DirectDraw/DirectDraw OS Design Development */
/* ms925295 DirectDraw/DirectDraw Reference */
/* aa451336 DirectDraw/DirectDraw Registry Settings */
/* aa451338 DirectDraw/DirectDraw Samples */
/* aa451339 DirectDraw/DirectDraw Security */
/* aa451266 DirectShow and COM/Creating a DLL in DirectShow */
/* ms923419 DirectShow and COM/Implementing IUnknown in DirectShow */
/* ms924596 DirectShow and COM/Registering DirectShow Filters */
/* aa451185 DirectShow Application Development/Audio and Video Capture Support */
/* aa451343 DirectShow Application Development/DirectShow Architecture */
/* aa451345 DirectShow Application Development/DirectShow C++ Class Library */
/* ms932597 DirectShow Application Development/Getting Started with DirectShow */
/* ms925289 DirectShow Application Development/Writing DirectShow Filters */
/* ms923409 DirectShow Architecture for Filter Developers/Connection Implementation in the Base Classes */
/* aa451292 DirectShow Architecture for Filter Developers/Data Flow in the Filter Graph */
/* ms924192 DirectShow Architecture for Filter Developers/Overview of the Filter Connection Process */
/* ms924587 DirectShow Architecture for Filter Developers/Quality-Control Management */
/* aa451394 DirectShow Architecture for Filter Developers/Time and Clocks in DirectShow */
/* aa451354 DirectShow Architecture/DirectShow System Overview */
/* aa451390 DirectShow Architecture/Elements of the Filter Graph */
/* ms923350 DirectShow Architecture/Event Notification in DirectShow */
/* ms923389 DirectShow Architecture/Graph Building with Intelligent Connect */
/* ms924154 DirectShow Architecture/Movement of Data Through the Filter Graph */
/* aa451200 DirectShow C++ Class Library/Base Classes */
/* aa451450 DirectShow C++ Class Library/Utility Classes */
/* ms925297 DirectShow Reference/DirectShow Classes */
/* ms925298 DirectShow Reference/DirectShow Enumerations */
/* ms925299 DirectShow Reference/DirectShow Functions */
/* ms925300 DirectShow Reference/DirectShow Interfaces */
/* ms925301 DirectShow Reference/DirectShow Macros */
/* ms925303 DirectShow Reference/DirectShow Structures */
/* aa452398 DirectShow Reference/Unsupported DirectShow Items */
/* ms932581 DirectShow/DirectShow Application Development */
/* aa451349 DirectShow/DirectShow Migration */
/* aa451350 DirectShow/DirectShow OS Design Development */
/* ms925302 DirectShow/DirectShow Reference */
/* aa451351 DirectShow/DirectShow Registry Settings */
/* ms932673 DirectShow/DirectShow Samples */
/* aa451353 DirectShow/DirectShow Security */
/* aa451355 DirectShow/DirectX Media Objects */
/* aa451607 DirectShow/DMO Reference */
/* ms932033 DirectShow/Media Types */
/* ms924654 DirectShow/Supported Audio Codecs and Renderers */
/* ms924655 DirectShow/Supported DirectShow Filters */
/* ms924656 DirectShow/Supported Video Codecs */
/* aa451360 DirectX Media Objects/DMOs and Media Types */
/* ms923433 DirectX Media Objects/Introduction to DirectX Media Objects */
/* aa451426 DirectX Media Objects/Using DirectX Media Objects */
/* aa451427 DirectX Media Objects/Using DMOs in a DirectShow Application */
/* aa451155 Display Modes/About Display Modes */
/* aa451305 Display Modes/Determining Supported Display Modes */
/* ms924623 Display Modes/Setting Display Modes */
/* aa451297 DMOs and Media Types/Decoders and Compressors */
/* ms924143 DMOs and Media Types/Media Types in the Registry */
/* ms924191 DMOs and Media Types/Overview of Media Types */
/* ms924574 DMOs and Media Types/Preferred Media Types */
/* ms924629 DMOs and Media Types/Setting the Media Types */
/* ms925288 DRM Application Development/Developing Applications on DRM-Enabled Platforms */
/* ms923104 DRM Application Development/DRM for Portable Devices */
/* ms923147 DRM Application Development/DRM in DirectShow and Windows Media Player */
/* ms923437 DRM Application Development/License Acquisition */
/* aa451159 DVD-Video API Application Development/About the DVD-Video API Documentation */
/* aa451409 DVD-Video API Application Development/Understanding the DVD-Video API */
/* aa451440 DVD-Video API Application Development/Using the DVD-Video API */
/* ms912026 DVD-Video API Macros/DVD-Video API Interface Identifiers */
/* ms923168 DVD-Video API Reference/DVD-Video API Common Terms */
/* ms925304 DVD-Video API Reference/DVD-Video API Data Types */
/* ms925305 DVD-Video API Reference/DVD-Video API Enumerated Types */
/* ms925306 DVD-Video API Reference/DVD-Video API Interfaces */
/* ms925309 DVD-Video API Reference/DVD-Video API Structures */
/* ms923161 DVD-Video API/DVD-Video API Application Development */
/* ms923157 DVD-Video API/DVD-Video API Migration */
/* ms923190 DVD-Video API/DVD-Video API OS Design Development */
/* ms925308 DVD-Video API/DVD-Video API Reference */
/* ms932690 DVD-Video API/DVD-Video API Samples */
/* ms923200 DVD-Video API/DVD-Video API Security */
/* aa451168 Elements of the Filter Graph/Allocators */
/* aa451240 Elements of the Filter Graph/Clocks */
/* ms923368 Elements of the Filter Graph/Filters */
/* ms924141 Elements of the Filter Graph/Media Samples */
/* ms924202 Elements of the Filter Graph/Pins */
/* aa451389 Elements of the Filter Graph/The Filter Graph */
/* ms923436 Event Notification in DirectShow/Learning When an Event Occurs */
/* ms924189 Event Notification in DirectShow/Overview of Event Notification */
/* ms924608 Event Notification in DirectShow/Retrieving Events */
/* aa451183 Examining the DVDSample Sample Application/Architectural Overview of DVDSample */
/* aa451224 Examining the DVDSample Sample Application/Callbacks in DVDSample */
/* ms924632 Examining the DVDSample Sample Application/Setting up DirectDraw in DVDSample */
/* aa451386 Examining the DVDSample Sample Application/The DVDSample Control Panel */
/* aa451387 Examining the DVDSample Sample Application/The DVDSample Startup Sequence */
/* aa451209 Exploring Graphics Concepts/Blitting */
/* aa451219 Exploring Graphics Concepts/Bounding Rectangles */
/* aa451309 Exploring Graphics Concepts/Device-Independent Bitmaps */
/* aa451363 Exploring Graphics Concepts/Drawing Surfaces */
/* ms924193 Exploring Graphics Concepts/Page Flipping and Back Buffering */
/* ms940043 Exposing Capture and Compression Formats/Audio Capabilities */
/* ms940070 Exposing Capture and Compression Formats/Reconnecting Your Input to Ensure Specific Output Types */
/* ms940076 Exposing Capture and Compression Formats/Video Capabilities */
/* aa451194 File Formats/AVI 2.0 File Format Extensions */
/* aa451196 File Formats/AVI RIFF File Reference */
/* aa451348 File Formats/DirectShow Graph File Format */
/* ms924595 File Formats/Registering a Custom File Type */
/* ms923369 Full-Screen Video Renderer/Finding a Filter That Can Be Stretched Full-Screen at No Cost */
/* ms923370 Full-Screen Video Renderer/Finding a Filter That Supports Full-Screen Mode */
/* ms923421 Full-Screen Video Renderer/Implications of Full-Screen Support for the Application */
/* ms924651 Full-Screen Video Renderer/Stretching the Output of a Renderer Full-Screen */
/* ms924653 Full-Screen Video Renderer/Supplying a Full-Screen Renderer Filter */
/* aa451442 Full-Screen Video Renderer/Using the IVideoWindow PID to Implement Full-Screen Support */
/* aa451260 Getting Started with DirectDraw/Cooperative Levels */
/* aa451331 Getting Started with DirectDraw/DirectDraw Middleware Architecture */
/* aa451358 Getting Started with DirectDraw/Display Modes */
/* ms925259 Getting Started with DirectDraw/Why Use DirectDraw? */
/* ms923432 Getting Started with DirectShow/Introduction to DirectShow Application Programming */
/* ms924206 Getting Started with DirectShow/Playing a Media File */
/* ms924605 Getting Started with DirectShow/Responding to Events */
/* ms924630 Getting Started with DirectShow/Setting the Video Window */
/* aa451163 Graph Building with Intelligent Connect/Adding Filters to the Graph */
/* ms923372 Graph Building with Intelligent Connect/Finding the Filters */
/* ms940065 Graph Building with Intelligent Connect/Intelligent Connect */
/* ms940099 Graphics and Multimedia Technologies */
/* aa451190 Graphics and Multimedia Technologies/Audio */
/* ms923392 Graphics and Multimedia Technologies/Graphics */
/* ms923391 Graphics and Multimedia Technologies/Graphics and Multimedia Technologies Catalog Items */
/* ms924142 Graphics and Multimedia Technologies/Media */
/* ms924620 Graphics and Multimedia Technologies/Security with Multimedia */
/* aa451169 Graphics/AlphaBlend API */
/* aa452478 Graphics/Direct3D Mobile */
/* ms932564 Graphics/DirectDraw */
/* ms923388 Graphics/Gradient Fill Support */
/* ms932606 Graphics/Imaging */
/* ms940100 Graphics/Multiple Screens */
/* ms924591 Graphics/Raster Fonts Support */
/* aa451451 Graphics/V1 Font Compatibility */
/* ms923435 Implementing IUnknown in DirectShow/IUnknown Basics */
/* aa451422 Implementing IUnknown in DirectShow/Using CUnknown */
/* ms923367 Introduction to DirectShow Application Programming/Filter Graphs */
/* ms925286 Introduction to DirectShow Application Programming/Writing a DirectShow Application */
/* ms923407 Introduction to DirectX Media Objects/Differences Between DMOs and DirectShow Filters */
/* ms925260 Introduction to DirectX Media Objects/Why Use DMOs? */
/* aa451186 Media/Audio Codecs and Renderers */
/* ms940097 Media/Digital Rights Management */
/* ms940098 Media/DirectShow */
/* ms932590 Media/DVD-Video API */
/* ms923379 Media/Four-Character Codes (FOURCC) */
/* ms924140 Media/Media Formats */
/* ms924649 Media/Streaming Media Playback */
/* aa451458 Media/Video Codecs and Renderers */
/* ms932641 Media/Windows Media */
/* ms925275 Media/WMA and MP3 Local Playback */
/* ms925276 Media/WMA and MP3 Streaming */
/* ms923224 Multiple Screens Application Development/Enumerating Screens */
/* ms923405 Multiple Screens Application Development/HMONITOR and the Device Context */
/* ms924169 Multiple Screens Application Development/Obtaining System Metrics for Multiple Screens */
/* ms924572 Multiple Screens Application Development/Positioning Objects on Multiple Screens */
/* aa451392 Multiple Screens Application Development/The Virtual Screen */
/* aa451420 Multiple Screens Application Development/Using Colors on Multiple Displays */
/* aa451431 Multiple Screens Application Development/Using Multiple Screen Applications on Different Systems */
/* aa451432 Multiple Screens Application Development/Using Older Programs on Multiple Screen Systems */
/* ms925327 Multiple Screens How-to Topics/How to Support Multiple Screens on a Device */
/* ms925315 Multiple Screens Reference/Multiple Screens Functions */
/* ms925317 Multiple Screens Reference/Multiple Screens Structures */
/* ms932614 Multiple Screens/Multiple Screens Application Development */
/* ms932620 Multiple Screens/Multiple Screens How-to Topics */
/* ms924161 Multiple Screens/Multiple Screens Migration */
/* ms924162 Multiple Screens/Multiple Screens OS Design Development */
/* ms925316 Multiple Screens/Multiple Screens Reference */
/* ms924163 Multiple Screens/Multiple Screens Registry Settings */
/* ms932708 Multiple Screens/Multiple Screens Samples */
/* ms924164 Multiple Screens/Multiple Screens Security */
/* aa451218 Overlay Surfaces/Boundary and Size Alignment */
/* aa451276 Overlay Surfaces/Creating Overlay Surfaces */
/* ms923374 Overlay Surfaces/Flipping Overlay Surfaces */
/* ms924146 Overlay Surfaces/Minimum and Maximum Stretch Factors */
/* ms924175 Overlay Surfaces/Overlay Color Keys */
/* ms924176 Overlay Surfaces/Overlay Surface Overview */
/* ms924178 Overlay Surfaces/Overlay Z-Orders */
/* ms924573 Overlay Surfaces/Positioning Overlay Surfaces */
/* ms924637 Overlay Surfaces/Significant DDCAPS Members and Flags */
/* ms924641 Overlay Surfaces/Source and Destination Rectangles */
/* ms924180 Override the Base Class Member Functions/Override Pin Member Functions */
/* ms924182 Override the Base Class Member Functions/Override the CBaseOutput::DecideAllocator Member Function */
/* ms924183 Override the Base Class Member Functions/Override the CheckInputType Member Function */
/* ms924184 Override the Base Class Member Functions/Override the CheckTransform Member Function */
/* ms924185 Override the Base Class Member Functions/Override the DecideBufferSize Member Function */
/* ms924186 Override the Base Class Member Functions/Override the GetMediaType Member Function */
/* ms924188 Override the Base Class Member Functions/Override the Transform Member Function */
/* ms924207 Playing a Media File/Playing the File */
/* ms924615 Playing a Media File/Sample Playback Program */
/* ms923385 Porting Older DirectDraw Code/Getting an IDirectDraw4 Interface */
/* ms924168 Porting Older DirectDraw Code/New Functionality in IDirectDraw4 */
/* aa451352 Responding to Events/DirectShow Sample Code */
/* ms923408 Responding to Events/Event Notification for Filters */
/* aa451428 Responding to Events/Using Event Notification */
/* ms924616 Setting the Video Window/Sample Video Window Program */
/* aa451391 Setting the Video Window/The Video Window */
/* aa451441 Setting the Video Window/Using the IVideoWindow Interface */
/* ms924156 Supported Audio Codecs and Renderers/MPEG-1 Layer 1 and 2 Audio Codec */
/* ms925704 Supported Audio Codecs and Renderers/Waveform Audio Renderer */
/* ms925329 Supported DirectShow Filters/ACM Wrapper Filter */
/* aa452494 Supported DirectShow Filters/Audio Lip Sync Filter */
/* ms940087 Supported DirectShow Filters/Audio Renderer (WaveOut) Filter */
/* ms925761 Supported DirectShow Filters/AVI Filter */
/* ms940088 Supported DirectShow Filters/Color Space Converter Filter */
/* aa452414 Supported DirectShow Filters/DirectShow Video Renderer Filter */
/* aa451613 Supported DirectShow Filters/DMO Wrapper Filter */
/* aa452532 Supported DirectShow Filters/DVR Sink Filter */
/* aa452533 Supported DirectShow Filters/DVR Source Filter */
/* aa451710 Supported DirectShow Filters/File Source (Async) Filter */
/* aa451711 Supported DirectShow Filters/File Source (URL) Filter */
/* aa451712 Supported DirectShow Filters/Filter Categories */
/* aa452497 Supported DirectShow Filters/Generic Streamer Filter */
/* ms940095 Supported DirectShow Filters/Image Sink Filter */
/* ms924155 Supported DirectShow Filters/MPEG-1 Parser/Splitter */
/* aa452531 Supported DirectShow Filters/MPEG-2 Program Stream DeMultiplexer Filter */
/* aa452498 Supported DirectShow Filters/MPEG-2 Program Stream Multiplexer Filter */
/* ms932249 Supported DirectShow Filters/Overlay Mixer */
/* ms940073 Supported DirectShow Filters/Smart Tee Filter */
/* aa452563 Supported DirectShow Filters/VBI Renderer Filter */
/* ms925754 Supported DirectShow Filters/Video/Image Compression Manager */
/* aa452467 Supported DirectShow Filters/WAVE/AIFF/au/snd File Parser */
/* ms940096 Supported DirectShow Filters/WM ASF Writer Filter */
/* ms924157 Supported Video Codecs/MPEG-1 Video Codec */
/* ms923371 Surfaces and Device Contexts/Finding a Surface with a Device Context */
/* ms924613 Surfaces and Device Contexts/Retrieving the Device Context for a Surface */
/* aa451156 Taking Advantage of DMA Support/About DMA Device Support */
/* ms924667 Taking Advantage of DMA Support/Testing for DMA Support */
/* aa451407 Taking Advantage of DMA Support/Typical Scenarios for DMA */
/* aa451191 The DVD Standard/Audio, Video, and Subpicture Data */
/* aa451293 The DVD Standard/Data Organization and Navigation */
/* aa451362 The DVD Standard/Domains */
/* ms923209 The DVD Standard/DVD-Video Menus */
/* ms924166 The DVD Standard/Navigation Control Data */
/* ms924196 The DVD Standard/Parental Management Levels */
/* aa451414 The DVD Standard/User Operation Controls */
/* ms924204 The DVDSample Control Panel/Playback in DVDSample */
/* ms923373 The DVDSample Startup Sequence/First Play in DVDSample */
/* aa451157 Transform Filters/About Effect Filters */
/* aa451253 Transform Filters/Connecting Transform Filters */
/* aa451270 Transform Filters/Creating a Transform Filter */
/* aa451437 Transform Filters/Using the CTransformFilter and CTransInPlaceFilter Transform Base Classes */
/* ms925285 Transform Filters/Write a Transform Filter in C/C++ */
/* aa451216 Transparent Blitting/Blitting with Color Keys */
/* aa451244 Transparent Blitting/Color Key Format */
/* ms924622 Transparent Blitting/Setting Color Keys */
/* ms924139 Transport Base Classes/Media Control and Positioning Classes */
/* aa451181 Understanding the DVD-Video API/Architectural Overview of the DVD-Video API */
/* aa451388 Understanding the DVD-Video API/The DVD Standard */
/* aa451268 Using DirectDraw Palettes in Windowed Mode/Creating a Palette in Windowed Mode */
/* ms924626 Using DirectDraw Palettes in Windowed Mode/Setting Palette Entries in Windowed Mode */
/* aa451406 Using DirectDraw Palettes in Windowed Mode/Types of Palette Entries in Windowed Mode */
/* aa451291 Using DirectX Media Objects/Data Flow */
/* aa451356 Using DirectX Media Objects/Discardable and Optional Streams */
/* ms923426 Using DirectX Media Objects/In-Place DMOs */
/* ms924580 Using DirectX Media Objects/Processing Data with DMOs */
/* ms924650 Using DirectX Media Objects/Streams and Buffers */
/* aa451361 Using DMOs in a DirectShow Application/DMOs in DirectShow */
/* aa451439 Using DMOs in a DirectShow Application/Using the DMO Wrapper Filter */
/* aa451184 Using the CTransformFilter and CTransInPlaceFilter Transform Base Classes/A Sample Transform Filter Declaration */
/* ms923430 Using the CTransformFilter and CTransInPlaceFilter Transform Base Classes/Introducing the CTransformFilter and CTransInPlaceFilter Classes */
/* ms925255 Using the CTransformFilter and CTransInPlaceFilter Transform Base Classes/What the Derived Class Must Provide */
/* aa451164 Using the DVD-Video API/Adding More Player Capabilities */
/* aa451166 Using the DVD-Video API/Advanced DVD Player Application Topics */
/* aa451269 Using the DVD-Video API/Creating a Simple DVD Player */
/* aa451251 Utility Classes/COM Utility Classes */
/* aa451295 Utility Classes/Debugging Classes */
/* ms924126 Utility Classes/List and Queue Classes */
/* ms924158 Utility Classes/Multimedia Data Type Classes */
/* ms925264 Utility Classes/Win32 Classes */
/* ms940048 Video Capture Tasks/Capturing an Image From a Still Image Pin */
/* ms940053 Video Capture Tasks/Configure the Video Output Format */
/* ms940054 Video Capture Tasks/Configure the Video Quality */
/* ms940071 Video Capture Tasks/Setting the Capture Frame Rate */
/* ms940072 Video Capture Tasks/Setting the Color Format for Video Capture */
/* ms940042 Video Capture/Advanced Capture Topics */
/* ms940045 Video Capture/Building Graphs with the Capture Graph Builder */
/* aa452495 Video Capture/Camera Rotation */
/* ms940046 Video Capture/Capture Device Selection */
/* ms940047 Video Capture/Capture Graph Builder */
/* aa452496 Video Capture/Capture Performance */
/* ms940050 Video Capture/Capturing Video to a File */
/* ms940056 Video Capture/Controlling a Capture Graph */
/* ms940066 Video Capture/Interfaces for Capture Applications */
/* ms940078 Video Capture/Video Capture Filters */
/* ms940079 Video Capture/Video Capture Tasks */
/* ms940080 Video Capture/Video Previews */
/* aa451154 Video Ports/About DirectDraw Video-Port Extensions */
/* aa451192 Video Ports/Auto-Flipping */
/* ms923362 Video Ports/Exploiting Hardware Capabilities */
/* ms923410 Video Ports/HREF, VREF, and Connections */
/* ms924639 Video Ports/Solutions to Common Video Artifacts */
/* ms924640 Video Ports/Solving Problems Caused by Half-Lines */
/* aa451457 Video Ports/Vertical Blanking Interval Data */
/* aa451459 Video Ports/Video Frames and Fields */
/* aa451461 Video Ports/Video-Port Technology Overview */
/* ms925254 Video Ports/What Are Video Ports? */
/* aa451176 Video Renderers/Alternative Video Renderers */
/* aa451256 Video Renderers/Control Distributors */
/* ms923380 Video Renderers/Full-Screen Video Renderer */
/* ms924209 Video Renderers/Plug-in Distributors and Extensibility */
/* ms924642 Video Renderers/Source and Target Rectangles in Video Renderers */
/* ms940057 Windows Media Applications/Creating ASF Files in DirectShow */
/* aa451632 Windows Media Event Notification Codes/EC_BANDWIDTHCHANGE */
/* aa451636 Windows Media Event Notification Codes/EC_CONTENTPROPERTY_CHANGED */
/* aa451637 Windows Media Event Notification Codes/EC_DRMSTATUS */
/* aa451639 Windows Media Event Notification Codes/EC_EOS_SOON */
/* aa451641 Windows Media Event Notification Codes/EC_ERRORABORTEX */
/* aa451643 Windows Media Event Notification Codes/EC_FILE_CLOSED */
/* aa451645 Windows Media Event Notification Codes/EC_LOADSTATUS */
/* aa451646 Windows Media Event Notification Codes/EC_MARKER_HIT */
/* aa451652 Windows Media Event Notification Codes/EC_PLEASE_REOPEN */
/* aa451658 Windows Media Event Notification Codes/EC_STATUS */
/* aa451665 Windows Media Event Notification Codes/EC_VIDEOFRAMEREADY */
/* aa451226 Windows Media Player Control Application Development/Capturing Keyboard and Mouse Events */
/* aa451254 Windows Media Player Control Application Development/Codecs and Formats */
/* aa451247 Windows Media Player Control Application Development/Compatibility Modes */
/* aa451290 Windows Media Player Control Application Development/Customizing the Windows Media Player Control User Interface */
/* ms924152 Windows Media Player Control Application Development/Monitoring Stream Status and Network Reception */
/* ms924205 Windows Media Player Control Application Development/Playback Methods and Properties */
/* ms924581 Windows Media Player Control Application Development/Processing Embedded Script Commands */
/* ms924611 Windows Media Player Control Application Development/Retrieving Presentation Information */
/* aa451433 Windows Media Player Control Application Development/Using Playlists */
/* ms925546 Windows Media Player Control Application Development/Windows Media Player Control Architecture */
/* ms923240 Windows Media Player Control Application Development/Windows Media Player Control Error Handling */
/* aa452399 Windows Media Player Control Application Development/Windows Media Player Control Unsupported Items */
/* ms925324 Windows Media Player Control Reference/Windows Media Player Events */
/* ms925325 Windows Media Player Control Reference/Windows Media Player Methods */
/* ms925326 Windows Media Player Control Reference/Windows Media Player Properties */
/* ms923398 Windows Media Player Control Unsupported Items/Handling of Unsupported Items */
/* ms932653 Windows Media Player Control/Windows Media Player Control Application Development */
/* ms925267 Windows Media Player Control/Windows Media Player Control Migration */
/* ms925268 Windows Media Player Control/Windows Media Player Control OS Design Development */
/* ms925323 Windows Media Player Control/Windows Media Player Control Reference */
/* ms925269 Windows Media Player Control/Windows Media Player Control Registry Settings */
/* ms940038 Windows Media Player Control/Windows Media Player Control Samples */
/* ms925270 Windows Media Player Control/Windows Media Player Control Security */
/* ms936850 Windows Media Player Events/Buffering */
/* aa451531 Windows Media Player Events/Click */
/* ms907786 Windows Media Player Events/DblClick */
/* aa451587 Windows Media Player Events/Disconnect */
/* aa451684 Windows Media Player Events/EndOfStream */
/* aa451698 Windows Media Player Events/Error */
/* ms932019 Windows Media Player Events/KeyDown */
/* ms932020 Windows Media Player Events/KeyPress */
/* ms932021 Windows Media Player Events/KeyUp */
/* ms932029 Windows Media Player Events/MarkerHit */
/* ms932217 Windows Media Player Events/MouseDown */
/* ms932218 Windows Media Player Events/MouseMove */
/* ms932219 Windows Media Player Events/MouseUp */
/* ms932240 Windows Media Player Events/NewStream */
/* ms932246 Windows Media Player Events/OpenComplete */
/* ms932248 Windows Media Player Events/OpenStateChange */
/* ms932264 Windows Media Player Events/PlayStateChange */
/* ms932267 Windows Media Player Events/PositionChange */
/* ms932277 Windows Media Player Events/ReadyStateChange */
/* ms932292 Windows Media Player Events/ScriptCommand */
/* aa452374 Windows Media Player Events/StateChange */
/* ms936895 Windows Media Player Methods/Cancel */
/* aa451707 Windows Media Player Methods/FastForward */
/* aa451708 Windows Media Player Methods/FastReverse */
/* aa451728 Windows Media Player Methods/GetCodecDescription */
/* aa451729 Windows Media Player Methods/GetCodecInstalled */
/* aa451730 Windows Media Player Methods/GetCodecURL */
/* aa451731 Windows Media Player Methods/GetCurrentEntry */
/* aa451733 Windows Media Player Methods/GetMarkerName */
/* aa451734 Windows Media Player Methods/GetMarkerTime */
/* aa451735 Windows Media Player Methods/GetMediaInfoString */
/* aa451736 Windows Media Player Methods/GetMediaParameter */
/* aa451737 Windows Media Player Methods/GetMediaParameterName */
/* ms932241 Windows Media Player Methods/Next */
/* ms932245 Windows Media Player Methods/Open */
/* ms932253 Windows Media Player Methods/Pause (Windows Media Player) */
/* ms932260 Windows Media Player Methods/Play (Windows Media Player) */
/* ms932268 Windows Media Player Methods/Previous */
/* ms932291 Windows Media Player Methods/Run (Windows Media Player) */
/* ms932301 Windows Media Player Methods/SetCurrentEntry */
/* aa452376 Windows Media Player Methods/Stop (Windows Media Player) */
/* ms925331 Windows Media Player Properties/AllowChangeDisplaySize */
/* ms925332 Windows Media Player Properties/AllowHideControls */
/* ms925334 Windows Media Player Properties/AllowScan */
/* ms925711 Windows Media Player Properties/AudioStream */
/* ms925734 Windows Media Player Properties/AutoRewind */
/* ms925740 Windows Media Player Properties/AutoSize (Windows Media Player) */
/* ms925744 Windows Media Player Properties/AutoStart */
/* ms925771 Windows Media Player Properties/Balance */
/* ms925778 Windows Media Player Properties/Bandwidth */
/* ms925879 Windows Media Player Properties/BaseURL */
/* ms936851 Windows Media Player Properties/BufferingCount */
/* ms936852 Windows Media Player Properties/BufferingProgress */
/* ms936853 Windows Media Player Properties/BufferingTime */
/* ms936896 Windows Media Player Properties/CanScan */
/* ms936897 Windows Media Player Properties/CanSeek */
/* ms936898 Windows Media Player Properties/CanSeekToMarkers */
/* aa451527 Windows Media Player Properties/ChannelDescription */
/* aa451528 Windows Media Player Properties/ChannelName */
/* aa451529 Windows Media Player Properties/ChannelURL */
/* aa451532 Windows Media Player Properties/ClickToPlay */
/* ms926773 Windows Media Player Properties/CodecCount */
/* ms926779 Windows Media Player Properties/ContactAddress */
/* ms926780 Windows Media Player Properties/ContactEmail */
/* ms926781 Windows Media Player Properties/ContactPhone */
/* ms907280 Windows Media Player Properties/CreationDate */
/* ms939121 Windows Media Player Properties/CurrentMarker */
/* ms939122 Windows Media Player Properties/CurrentPosition */
/* ms939123 Windows Media Player Properties/CurrentState */
/* aa451571 Windows Media Player Properties/DefaultFrame */
/* aa451588 Windows Media Player Properties/DisplayBackColor */
/* aa451589 Windows Media Player Properties/DisplayForeColor */
/* aa451590 Windows Media Player Properties/DisplaySize */
/* aa451615 Windows Media Player Properties/Duration (Windows Media Player) */
/* aa451675 Windows Media Player Properties/Enabled */
/* aa451676 Windows Media Player Properties/EnablePositionControls */
/* aa451677 Windows Media Player Properties/EnableTracker */
/* aa451686 Windows Media Player Properties/EntryCount */
/* aa451700 Windows Media Player Properties/ErrorCode */
/* aa451702 Windows Media Player Properties/ErrorCorrection */
/* aa451703 Windows Media Player Properties/ErrorDescription */
/* aa451709 Windows Media Player Properties/FileName */
/* aa451721 Windows Media Player Properties/FullScreenMode */
/* aa451739 Windows Media Player Properties/GetMoreInfoURL */
/* aa451742 Windows Media Player Properties/HasError */
/* aa451743 Windows Media Player Properties/HasMultipleItems */
/* aa452245 Windows Media Player Properties/ImageSourceHeight */
/* aa452246 Windows Media Player Properties/ImageSourceWidth */
/* ms912073 Windows Media Player Properties/InvokeURLs */
/* ms931808 Windows Media Player Properties/IsBroadcast */
/* ms931809 Windows Media Player Properties/IsDurationValid */
/* ms932022 Windows Media Player Properties/Language */
/* ms932025 Windows Media Player Properties/LostPackets */
/* ms932028 Windows Media Player Properties/MarkerCount */
/* ms932230 Windows Media Player Properties/MovieWindowSize */
/* ms932238 Windows Media Player Properties/Mute */
/* ms932247 Windows Media Player Properties/OpenState */
/* ms932261 Windows Media Player Properties/PlayCount */
/* ms932263 Windows Media Player Properties/PlayState */
/* ms932274 Windows Media Player Properties/Rate */
/* ms932276 Windows Media Player Properties/ReadyState */
/* ms932278 Windows Media Player Properties/ReceivedPackets */
/* ms932279 Windows Media Player Properties/ReceptionQuality */
/* ms932280 Windows Media Player Properties/RecoveredPackets */
/* ms932293 Windows Media Player Properties/SelectionEnd */
/* ms932294 Windows Media Player Properties/SelectionStart */
/* ms932295 Windows Media Player Properties/SendErrorEvents */
/* ms932296 Windows Media Player Properties/SendKeyboardEvents */
/* ms932297 Windows Media Player Properties/SendMouseClickEvents */
/* ms932298 Windows Media Player Properties/SendMouseMoveEvents */
/* ms932299 Windows Media Player Properties/SendOpenStateChangeEvents */
/* ms932300 Windows Media Player Properties/SendPlayStateChangeEvents */
/* ms932302 Windows Media Player Properties/ShowAudioControls */
/* ms932303 Windows Media Player Properties/ShowControls */
/* ms932304 Windows Media Player Properties/ShowPositionControls */
/* ms932305 Windows Media Player Properties/ShowStatusBar */
/* ms932306 Windows Media Player Properties/ShowTracker */
/* ms932315 Windows Media Player Properties/SourceLink */
/* ms932316 Windows Media Player Properties/SourceProtocol */
/* aa452380 Windows Media Player Properties/StreamCount */
/* aa452394 Windows Media Player Properties/TransparentAtStart */
/* aa452408 Windows Media Player Properties/VideoBorder3D */
/* aa452409 Windows Media Player Properties/VideoBorderColor */
/* aa452410 Windows Media Player Properties/VideoBorderWidth */
/* aa452416 Windows Media Player Properties/Volume */
/* ms925291 Windows Media Technologies/ASX Elements Reference */
/* ms925322 Windows Media Technologies/Windows Media Event Notification Codes */
/* ms932664 Windows Media Technologies/Windows Media Technologies Application Development */
/* ms925271 Windows Media Technologies/Windows Media Technologies Migration */
/* ms925272 Windows Media Technologies/Windows Media Technologies OS Design Development */
/* ms925273 Windows Media Technologies/Windows Media Technologies Registry Settings */
/* ms940041 Windows Media Technologies/Windows Media Technologies Samples */
/* ms925274 Windows Media Technologies/Windows Media Technologies Security */
/* ms925266 Windows Media/Windows Media Player */
/* ms940102 Windows Media/Windows Media Player Control */
/* ms940103 Windows Media/Windows Media Technologies */
/* aa451237 Working with DirectDraw Clippers/Clip Lists */
/* ms923422 Working with DirectDraw Clippers/Independent DirectDrawClipper Objects */
/* ms924635 Working with DirectDraw Clippers/Sharing DirectDrawClipper Objects */
/* aa451415 Working with DirectDraw Clippers/Using a Clipper with Multiple Windows */
/* aa451416 Working with DirectDraw Clippers/Using a Clipper with the System Cursor */
/* ms925240 Working with DirectDraw Clippers/What Are Clippers? */
/* ms924160 Working with DirectDraw Objects/Multiple DirectDraw Objects per Process */
/* ms924197 Working with DirectDraw Objects/Parent and Child Object Lifetimes */
/* ms925251 Working with DirectDraw Objects/What Are DirectDraw Objects? */
/* ms924194 Working with DirectDraw Palettes/Palette Animation */
/* ms924195 Working with DirectDraw Palettes/Palette Types */
/* ms924627 Working with DirectDraw Palettes/Setting Palettes on Nonprimary Surfaces */
/* ms924636 Working with DirectDraw Palettes/Sharing Palettes */
/* ms925252 Working with DirectDraw Palettes/What Are Palettes? */
/* aa451162 Working with DirectDraw Surfaces/Accessing Surface Memory Directly */
/* aa451202 Working with DirectDraw Surfaces/Basic Concepts of Surfaces */
/* aa451213 Working with DirectDraw Surfaces/Blitting to Surfaces */
/* aa451242 Working with DirectDraw Surfaces/Color Controls */
/* aa451250 Working with DirectDraw Surfaces/COM Reference Count Semantics for Surfaces */
/* aa451259 Working with DirectDraw Surfaces/Converting Color and Format */
/* aa451277 Working with DirectDraw Surfaces/Creating Surfaces */
/* ms923228 Working with DirectDraw Surfaces/Enumerating Surfaces */
/* ms924131 Working with DirectDraw Surfaces/Losing and Restoring Surfaces */
/* ms924177 Working with DirectDraw Surfaces/Overlay Surfaces */
/* ms924578 Working with DirectDraw Surfaces/Private Surface Data */
/* ms924662 Working with DirectDraw Surfaces/Surface Uniqueness Values */
/* ms924661 Working with DirectDraw Surfaces/Surfaces and Device Contexts */
/* aa451412 Working with DirectDraw Surfaces/Updating Surface Characteristics */
/* ms923390 Working with Graphics Devices/Graphic Objects and Modes */
/* ms924144 Working with Graphics Devices/Memory Device Contexts */
/* aa451417 Working with Graphics Devices/Using Bitmaps */
/* aa451419 Working with Graphics Devices/Using Colors */
/* aa451160 Write a Transform Filter in C/C++/Access Additional Interfaces */
/* aa451265 Write a Transform Filter in C/C++/Create Registry Information */
/* aa451298 Write a Transform Filter in C/C++/Define and Instantiate Your Filter Class */
/* ms924179 Write a Transform Filter in C/C++/Override CheckInputType */
/* ms924187 Write a Transform Filter in C/C++/Override the Transform Function */
/* ms940059 Writing Capture Filters/Exposing Capture and Compression Formats */
/* ms940064 Writing Capture Filters/Implementing a Preview Pin */
/* ms940068 Writing Capture Filters/Pin Requirements for Capture Filters */
/* ms940069 Writing Capture Filters/Producing Data in a Capture Filter */
/* aa451342 Writing DirectShow Filters/DirectShow and COM */
/* aa451344 Writing DirectShow Filters/DirectShow Architecture for Filter Developers */
/* ms923364 Writing DirectShow Filters/File Formats */
/* aa451399 Writing DirectShow Filters/Transform Filters */
/* aa451462 Writing DirectShow Filters/Video Renderers */
/* ms940084 Writing DirectShow Filters/Writing Capture Filters */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_DVDATA */
