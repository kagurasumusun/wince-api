/* Tapi.h -- Telephony API (TAPI) types, structures, callbacks and
 * constants for Windows CE.
 *
 * Evidence model (clean room; same as winsock2.h):
 *
 *  (a) every structure layout, member name and constant value is
 *      transcribed from the official CE 5.0 "Telephony API"
 *      documentation: the TAPI Structures pages (27 of which declare
 *      a typedef; 26 are declared here), the TAPI Constants pages
 *      (65, of which 63 publish values -- 643 name/value pairs in
 *      total, no cross-page conflicts), and the three TSPI callback
 *      function pages (LINEEVENT ms894144, PHONEEVENT ms895922,
 *      ASYNC_COMPLETION aa450289).  The per-page records are in
 *      docs/inventory.md (M43 section).
 *
 *  (b) the CE 5.0 archive strips whitespace inside code blocks; this
 *      file restores the documented spacing mechanically (verified
 *      member by member).  One documented restoration: the LINEDEVCAPS
 *      page prints "dwDevSpecificOffset" and "dwLineFeatures" with no
 *      separator between them; the semicolon is restored (each is a
 *      separate DWORD field of the documented layout).
 *
 *  (c) the CE pages print `FAR` pointer qualifiers; Windows CE has a
 *      single 32-bit flat address model, so the declarations use plain
 *      pointers (documented design decision, same as winsock2.h).
 *
 *  (d) TAPI handle types: the TAPI message pages document
 *      HTAPILINE / HTAPICALL / HTAPIPHONE as "The TAPI opaque object
 *      handle to the ..." line/call/phone; the provider-side HDRV*
 *      types are the corresponding SPI handles used by the TSPI
 *      prototypes, and HLINE appears as a member of LINECALLINFO.
 *      No CE page publishes the carrier types, so all are declared as
 *      HANDLE and DRV_REQUESTID as DWORD (documented design decision).
 *
 *  (e) LINEFORWARDLIST (page ms894148) documents a layout whose array
 *      element type LINEFORWARD has no layout page in any official CE
 *      tree (CE 5.0 / CE .NET / CE 6.0 catalogs), so the structure
 *      cannot be completed in C.  LPLINEFORWARDLIST is therefore
 *      declared as a pointer to an incomplete tag (documented design
 *      decision); the client lineForward (M45) and TSPI_lineForward
 *      (resolved in M45 from the M43 hold) take that pointer type.
 *      The LINE_* / PHONE_* callback-message values (17 TSPI message
 *      pages) publish names without numeric values:
 *      recorded-not-defined.
 */

#ifndef _TAPI_H
#define _TAPI_H

#include "Windef.h"   /* DWORD, WORD, BOOL, LONG, HANDLE, HWND, HICON,
                        LPVOID, LPDWORD, LPCWSTR, LPCSTR, LPSTR,
                        DWORD_PTR, CALLBACK */
#include "Winbase.h"  /* SYSTEMTIME (LINECALLSTATUS.tStateEntryTime) */
#include "Winreg.h"   /* HKEY (TSPI provider functions) */

/* The CE TAPI/TSPI prototypes print the TAPIAPI / TSPIAPI calling
 * conventions; Windows CE has one undecorated calling convention, so
 * both are empty exactly like WINAPI. */
#define TAPIAPI   WINAPI
#define TSPIAPI   WINAPI

/* ------------------------------------------------------------------ */
/* TAPI opaque object handles (see header note (d))                    */
/* ------------------------------------------------------------------ */

typedef HANDLE HTAPILINE;      /* "TAPI handle for the line on which the event occurred" */
typedef HANDLE HTAPICALL;      /* "TAPI handle for the call" (LINEEVENT page)            */
typedef HANDLE HTAPIPHONE;     /* "TAPI handle for the phone" (PHONEEVENT page)          */
typedef HANDLE HDRVLINE;       /* provider-side line handle (TSPI prototypes)            */
typedef HANDLE HDRVCALL;       /* provider-side call handle (TSPI prototypes)            */
typedef HANDLE HDRVPHONE;      /* provider-side phone handle (TSPI prototypes)           */
typedef HANDLE HLINE;          /* LINECALLINFO.hLine member (the TAPI line handle)       */
typedef DWORD  DRV_REQUESTID;  /* "the identifier passed in the original request"        */

/* Client-side opaque object handles (M45).  The official client
 * function pages document each as a TAPI object handle without
 * publishing a carrier type, so they are declared as HANDLE exactly
 * like the M43 set above (documented design decision):
 *   HLINEAPP  "Handle to the application's registration with TAPI."
 *             (lineOpen hLineApp parameter, ms894420; lineInitialize
 *             lphLineApp, ms894369: "Pointer to a location that is
 *             filled with the application's usage handle for TAPI.")
 *   HCALL     "Pointer to an HCALL handle." (lineMakeCall lphCall
 *             parameter, ms894387)
 *   HPHONE    "Pointer to an HPHONE handle that identifies the open
 *             phone device." (phoneOpen lphPhone parameter, ms895944)
 *   HPHONEAPP "Handle to the application's registration with TAPI."
 *             (phoneOpen hPhoneApp parameter, ms895944)             */
typedef HANDLE HLINEAPP;
typedef HANDLE HCALL;
typedef HANDLE HPHONE;
typedef HANDLE HPHONEAPP;

typedef HDRVLINE  *LPHDRVLINE;
typedef HDRVCALL  *LPHDRVCALL;
typedef HDRVPHONE *LPHDRVPHONE;
typedef HANDLE HPROVIDER;   /* TSPI provider handle (provider function pages) */
typedef HICON  *LPHICON;   /* GetIcon pairs (TSPI_line/phoneGetIcon) */

typedef HLINE     *LPHLINE;      /* lineOpen lphLine (ms894420)               */
typedef HLINEAPP  *LPHLINEAPP;   /* lineInitialize lphLineApp (ms894369)      */
typedef HCALL     *LPHCALL;      /* lineMakeCall lphCall (ms894387)           */
typedef HPHONE    *LPHPHONE;     /* phoneOpen lphPhone (ms895944)             */
typedef HPHONEAPP *LPHPHONEAPP;  /* phoneInitializeEx lphPhoneApp (ms895937)  */

/* LINEFORWARDLIST page (ms894148) prints the typedef
 *     struct lineforwardlist_tag { DWORD dwTotalSize;
 *         DWORD dwNumEntries; LINEFORWARD ForwardList[1]; }
 * and documents the element type LINEFORWARD, but no CE archive page
 * (CE 5.0 / CE .NET / CE 6.0 catalogs) publishes the LINEFORWARD
 * layout, so the structure cannot be completed in C.  The pointer
 * alias is declared against an incomplete tag (same policy as header
 * note (e)); callers pass a buffer assembled from the documented
 * list header.  CE 3.0 and later (the page's Requirements). */
typedef struct LINEFORWARDLIST *LPLINEFORWARDLIST;

/* ------------------------------------------------------------------ */
/* TSPI callback prototypes (the TSPI Callback Functions pages)        */
/* ------------------------------------------------------------------ */

/* LINEEVENT page (ms894144): "This type is a callback function
 * implemented by TAPI and supplied to the service provider as a
 * parameter to the TSPI_lineOpen function." */
typedef void (CALLBACK *LINEEVENT)(HTAPILINE htLine, HTAPICALL htCall,
                                   DWORD dwMsg, DWORD dwParam1,
                                   DWORD dwParam2, DWORD dwParam3);

/* PHONEEVENT page (ms895922): same for TSPI_phoneOpen. */
typedef void (CALLBACK *PHONEEVENT)(HTAPIPHONE htPhone, DWORD dwMsg,
                                    DWORD dwParam1, DWORD dwParam2,
                                    DWORD dwParam3);

/* ASYNC_COMPLETION page (aa450289): same for TSPI_providerInit. */
typedef void (CALLBACK *ASYNC_COMPLETION)(DRV_REQUESTID dwRequestID,
                                          LONG lResult);

/* ------------------------------------------------------------------ */
/* TAPI client callback prototypes (the client Callback pages)         */
/* ------------------------------------------------------------------ */

/* lineCallbackFunc page (ms893424): "This function is a placeholder
 * for the application-supplied function name."  Printed shape:
 *   VOID FAR PASCAL lineCallbackFunc(DWORD hDevice, DWORD dwMsg,
 *       DWORD dwCallbackInstance, DWORD dwParam1, DWORD dwParam2,
 *       DWORD dwParam3);
 * The page's hDevice note: "Applications must use the DWORD type for
 * this parameter because using the HANDLE type makes the code not
 * portable" -- hence DWORD, not HANDLE.  FAR/PASCAL reduce to the
 * single CE calling convention (header note (c) model). */
typedef void (CALLBACK *LINECALLBACK)(DWORD hDevice, DWORD dwMsg,
                                      DWORD dwCallbackInstance,
                                      DWORD dwParam1, DWORD dwParam2,
                                      DWORD dwParam3);

/* phoneCallbackFunc page (ms895910): same placeholder model for the
 * phone device; its printed shape types the first parameter HANDLE
 * ("Handle to a phone device associated with the callback."). */
typedef void (CALLBACK *PHONECALLBACK)(HANDLE hDevice, DWORD dwMsg,
                                       DWORD dwCallbackInstance,
                                       DWORD dwParam1, DWORD dwParam2,
                                       DWORD dwParam3);

/* ------------------------------------------------------------------ */
/* TAPI structures (the TAPI Structures pages)                         */
/* ------------------------------------------------------------------ */
/* LINEADDRESSCAPS page (ms893350). */
typedef struct lineaddresscaps_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwLineDeviceID;
    DWORD dwAddressSize;
    DWORD dwAddressOffset;
    DWORD dwDevSpecificSize;
    DWORD dwDevSpecificOffset;
    DWORD dwAddressSharing;
    DWORD dwAddressStates;
    DWORD dwCallInfoStates;
    DWORD dwCallerIDFlags;
    DWORD dwCalledIDFlags;
    DWORD dwConnectedIDFlags;
    DWORD dwRedirectionIDFlags;
    DWORD dwRedirectingIDFlags;
    DWORD dwCallStates;
    DWORD dwDialToneModes;
    DWORD dwBusyModes;
    DWORD dwSpecialInfo;
    DWORD dwDisconnectModes;
    DWORD dwMaxNumActiveCalls;
    DWORD dwMaxNumOnHoldCalls;
    DWORD dwMaxNumOnHoldPendingCalls;
    DWORD dwMaxNumConference;
    DWORD dwMaxNumTransConf;
    DWORD dwAddrCapFlags;
    DWORD dwCallFeatures;
    DWORD dwRemoveFromConfCaps;
    DWORD dwRemoveFromConfState;
    DWORD dwTransferModes;
    DWORD dwParkModes;
    DWORD dwForwardModes;
    DWORD dwMaxForwardEntries;
    DWORD dwMaxSpecificEntries;
    DWORD dwMinFwdNumRings;
    DWORD dwMaxFwdNumRings;
    DWORD dwMaxCallCompletions;
    DWORD dwCallCompletionConds;
    DWORD dwCallCompletionModes;
    DWORD dwNumCompletionMessages;
    DWORD dwCompletionMsgTextEntrySize;
    DWORD dwCompletionMsgTextSize;
    DWORD dwCompletionMsgTextOffset;
    DWORD dwAddressFeatures;
    DWORD dwPredictiveAutoTransferStates;
    DWORD dwNumCallTreatments;
    DWORD dwCallTreatmentListSize;
    DWORD dwCallTreatmentListOffset;
    DWORD dwDeviceClassesSize;
    DWORD dwDeviceClassesOffset;
    DWORD dwMaxCallDataSize;
    DWORD dwCallFeatures2;
    DWORD dwMaxNoAnswerTimeout;
    DWORD dwConnectedModes;
    DWORD dwOfferingModes;
    DWORD dwAvailableMediaModes;
} LINEADDRESSCAPS;
typedef LINEADDRESSCAPS *LPLINEADDRESSCAPS;

/* LINEADDRESSSTATUS page (ms893382). */
typedef struct lineaddressstatus_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwNumInUse;
    DWORD dwNumActiveCalls;
    DWORD dwNumOnHoldCalls;
    DWORD dwNumOnHoldPendCalls;
    DWORD dwAddressFeatures;
    DWORD dwNumRingsNoAnswer;
    DWORD dwForwardNumEntries;
    DWORD dwForwardSize;
    DWORD dwForwardOffset;
    DWORD dwTerminalModesSize;
    DWORD dwTerminalModesOffset;
    DWORD dwDevSpecificSize;
    DWORD dwDevSpecificOffset;
} LINEADDRESSSTATUS;
typedef LINEADDRESSSTATUS *LPLINEADDRESSSTATUS;

/* LINEDIALPARAMS page (ms894138). */
typedef struct linedialparams_tag {
    DWORD dwDialPause;
    DWORD dwDialSpeed;
    DWORD dwDigitDuration;
    DWORD dwWaitForDialtone;
} LINEDIALPARAMS;
typedef LINEDIALPARAMS *LPLINEDIALPARAMS;

/* LINECALLINFO page (ms893611). */
typedef struct linecallinfo_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    HLINE hLine;
    DWORD dwLineDeviceID;
    DWORD dwAddressID;
    DWORD dwBearerMode;
    DWORD dwRate;
    DWORD dwMediaMode;
    DWORD dwAppSpecific;
    DWORD dwCallID;
    DWORD dwRelatedCallID;
    DWORD dwCallParamFlags;
    DWORD dwCallStates;
    DWORD dwMonitorDigitModes;
    DWORD dwMonitorMediaModes;
    LINEDIALPARAMS DialParams;
    DWORD dwOrigin;
    DWORD dwReason;
    DWORD dwCompletionID;
    DWORD dwNumOwners;
    DWORD dwNumMonitors;
    DWORD dwCountryCode;
    DWORD dwTrunk;
    DWORD dwCallerIDFlags;
    DWORD dwCallerIDSize;
    DWORD dwCallerIDOffset;
    DWORD dwCallerIDNameSize;
    DWORD dwCallerIDNameOffset;
    DWORD dwCalledIDFlags;
    DWORD dwCalledIDSize;
    DWORD dwCalledIDOffset;
    DWORD dwCalledIDNameSize;
    DWORD dwCalledIDNameOffset;
    DWORD dwConnectedIDFlags;
    DWORD dwConnectedIDSize;
    DWORD dwConnectedIDOffset;
    DWORD dwConnectedIDNameSize;
    DWORD dwConnectedIDNameOffset;
    DWORD dwRedirectionIDFlags;
    DWORD dwRedirectionIDSize;
    DWORD dwRedirectionIDOffset;
    DWORD dwRedirectionIDNameSize;
    DWORD dwRedirectionIDNameOffset;
    DWORD dwRedirectingIDFlags;
    DWORD dwRedirectingIDSize;
    DWORD dwRedirectingIDOffset;
    DWORD dwRedirectingIDNameSize;
    DWORD dwRedirectingIDNameOffset;
    DWORD dwAppNameSize;
    DWORD dwAppNameOffset;
    DWORD dwDisplayableAddressSize;
    DWORD dwDisplayableAddressOffset;
    DWORD dwCalledPartySize;
    DWORD dwCalledPartyOffset;
    DWORD dwCommentSize;
    DWORD dwCommentOffset;
    DWORD dwDisplaySize;
    DWORD dwDisplayOffset;
    DWORD dwUserUserInfoSize;
    DWORD dwUserUserInfoOffset;
    DWORD dwHighLevelCompSize;
    DWORD dwHighLevelCompOffset;
    DWORD dwLowLevelCompSize;
    DWORD dwLowLevelCompOffset;
    DWORD dwChargingInfoSize;
    DWORD dwChargingInfoOffset;
    DWORD dwTerminalModesSize;
    DWORD dwTerminalModesOffset;
    DWORD dwDevSpecificSize;
    DWORD dwDevSpecificOffset;
} LINECALLINFO;
typedef LINECALLINFO *LPLINECALLINFO;

/* LINECALLLIST page (ms893660). */
typedef struct linecalllist_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwCallsNumEntries;
    DWORD dwCallsSize;
    DWORD dwCallsOffset;
} LINECALLLIST;
typedef LINECALLLIST *LPLINECALLLIST;

/* LINECALLPARAMS page (ms893776). */
typedef struct linecallparams_tag {
    DWORD dwTotalSize;
    DWORD dwBearerMode;
    DWORD dwMinRate;
    DWORD dwMaxRate;
    DWORD dwMediaMode;
    DWORD dwCallParamFlags;
    DWORD dwAddressMode;
    DWORD dwAddressID;
    LINEDIALPARAMS DialParams;
    DWORD dwOrigAddressSize;
    DWORD dwOrigAddressOffset;
    DWORD dwDisplayableAddressSize;
    DWORD dwDisplayableAddressOffset;
    DWORD dwCalledPartySize;
    DWORD dwCalledPartyOffset;
    DWORD dwCommentSize;
    DWORD dwCommentOffset;
    DWORD dwUserUserInfoSize;
    DWORD dwUserUserInfoOffset;
    DWORD dwHighLevelCompSize;
    DWORD dwHighLevelCompOffset;
    DWORD dwLowLevelCompSize;
    DWORD dwLowLevelCompOffset;
    DWORD dwDevSpecificSize;
    DWORD dwDevSpecificOffset;
    DWORD dwPredictiveAutoTransferStates;
    DWORD dwTargetAddressSize;
    DWORD dwTargetAddressOffset;
    DWORD dwSendingFlowspecSize;
    DWORD dwSendingFlowspecOffset;
    DWORD dwReceivingFlowspecSize;
    DWORD dwReceivingFlowspecOffset;
    DWORD dwDeviceClassSize;
    DWORD dwDeviceClassOffset;
    DWORD dwDeviceConfigSize;
    DWORD dwDeviceConfigOffset;
    DWORD dwCallDataSize;
    DWORD dwCallDataOffset;
    DWORD dwNoAnswerTimeout;
    DWORD dwCallingPartyIDSize;
    DWORD dwCallingPartyIDOffset;
    DWORD dwAddressType;
} LINECALLPARAMS;
typedef LINECALLPARAMS *LPLINECALLPARAMS;

/* LINECALLSTATUS page (ms894104). */
typedef struct linecallstatus_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwCallState;
    DWORD dwCallStateMode;
    DWORD dwCallPrivilege;
    DWORD dwCallFeatures;
    DWORD dwDevSpecificSize;
    DWORD dwDevSpecificOffset;
    DWORD dwCallFeatures2;
    SYSTEMTIME tStateEntryTime;
} LINECALLSTATUS;
typedef LINECALLSTATUS *LPLINECALLSTATUS;

/* LINECALLTREATMENTENTRY page (ms894117). */
typedef struct linecalltreatmententry_tag {
    DWORD dwCallTreatmentID;
    DWORD dwCallTreatmentNameSize;
    DWORD dwCallTreatmentNameOffset;
} LINECALLTREATMENTENTRY;
typedef LINECALLTREATMENTENTRY *LPLINECALLTREATMENTENTRY;

/* LINEDEVCAPS page (ms894130). */
typedef struct linedevcaps_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwProviderInfoSize;
    DWORD dwProviderInfoOffset;
    DWORD dwSwitchInfoSize;
    DWORD dwSwitchInfoOffset;
    DWORD dwPermanentLineID;
    DWORD dwLineNameSize;
    DWORD dwLineNameOffset;
    DWORD dwStringFormat;
    DWORD dwAddressModes;
    DWORD dwNumAddresses;
    DWORD dwBearerModes;
    DWORD dwMaxRate;
    DWORD dwMediaModes;
    DWORD dwGenerateToneModes;
    DWORD dwGenerateToneMaxNumFreq;
    DWORD dwGenerateDigitModes;
    DWORD dwMonitorToneMaxNumFreq;
    DWORD dwMonitorToneMaxNumEntries;
    DWORD dwMonitorDigitModes;
    DWORD dwGatherDigitsMinTimeout;
    DWORD dwGatherDigitsMaxTimeout;
    DWORD dwMedCtlDigitMaxListSize;
    DWORD dwMedCtlMediaMaxListSize;
    DWORD dwMedCtlToneMaxListSize;
    DWORD dwMedCtlCallStateMaxListSize;
    DWORD dwDevCapFlags;
    DWORD dwMaxNumActiveCalls;
    DWORD dwAnswerMode;
    DWORD dwRingModes;
    DWORD dwLineStates;
    DWORD dwUUIAcceptSize;
    DWORD dwUUIAnswerSize;
    DWORD dwUUIMakeCallSize;
    DWORD dwUUIDropSize;
    DWORD dwUUISendUserUserInfoSize;
    DWORD dwUUICallInfoSize;
    LINEDIALPARAMS MinDialParams;
    LINEDIALPARAMS MaxDialParams;
    LINEDIALPARAMS DefaultDialParams;
    DWORD dwNumTerminals;
    DWORD dwTerminalCapsSize;
    DWORD dwTerminalCapsOffset;
    DWORD dwTerminalTextEntrySize;
    DWORD dwTerminalTextSize;
    DWORD dwTerminalTextOffset;
    DWORD dwDevSpecificSize;
    DWORD dwDevSpecificOffset;
    DWORD dwLineFeatures;
    DWORD dwSettableDevStatus;
    DWORD dwDeviceClassesSize;
    DWORD dwDeviceClassesOffset;
} LINEDEVCAPS;
typedef LINEDEVCAPS *LPLINEDEVCAPS;

/* LINEDEVSTATUS page (ms894135). */
typedef struct linedevstatus_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwNumOpens;
    DWORD dwOpenMediaModes;
    DWORD dwNumActiveCalls;
    DWORD dwNumOnHoldCalls;
    DWORD dwNumOnHoldPendCalls;
    DWORD dwLineFeatures;
    DWORD dwNumCallCompletions;
    DWORD dwRingMode;
    DWORD dwSignalLevel;
    DWORD dwBatteryLevel;
    DWORD dwRoamMode;
    DWORD dwDevStatusFlags;
    DWORD dwTerminalModesSize;
    DWORD dwTerminalModesOffset;
    DWORD dwDevSpecificSize;
    DWORD dwDevSpecificOffset;
} LINEDEVSTATUS;
typedef LINEDEVSTATUS *LPLINEDEVSTATUS;


/* LINEEXTENSIONID page (ms894145). */
typedef struct lineextensionid_tag {
    DWORD dwExtensionID0;
    DWORD dwExtensionID1;
    DWORD dwExtensionID2;
    DWORD dwExtensionID3;
} LINEEXTENSIONID;
typedef LINEEXTENSIONID *LPLINEEXTENSIONID;

/* LINEGENERATETONE page (ms894155). */
typedef struct linegeneratetone_tag {
    DWORD dwFrequency;
    DWORD dwCadenceOn;
    DWORD dwCadenceOff;
    DWORD dwVolume;
} LINEGENERATETONE;
typedef LINEGENERATETONE *LPLINEGENERATETONE;

/* LINEINITIALIZEEXPARAMS page (ms894378). */
typedef struct lineinitializeexparams_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwOptions;
    union{HANDLE hEvent;HANDLE hCompletionPort; } Handles;
    DWORD dwCompletionKey;
} LINEINITIALIZEEXPARAMS;
typedef LINEINITIALIZEEXPARAMS *LPLINEINITIALIZEEXPARAMS;

/* LINELOCATIONENTRY page (ms894383). */
typedef struct linelocationentry_tag {
    DWORD dwPermanentLocationID;
    DWORD dwLocationNameSize;
    DWORD dwLocationNameOffset;
    DWORD dwCountryCode;
    DWORD dwCityCodeSize;
    DWORD dwCityCodeOffset;
    DWORD dwPreferredCardID;
    DWORD dwLocalAccessCodeSize;
    DWORD dwLocalAccessCodeOffset;
    DWORD dwLongDistanceAccessCodeSize;
    DWORD dwLongDistanceAccessCodeOffset;
    DWORD dwTollPrefixListSize;
    DWORD dwTollPrefixListOffset;
    DWORD dwCountryID;
    DWORD dwOptions;
    DWORD dwCancelCallWaitingSize;
    DWORD dwCancelCallWaitingOffset;
} LINELOCATIONENTRY;
typedef LINELOCATIONENTRY *LPLINELOCATIONENTRY;

/* LINEMESSAGE page (ms894390). */
typedef struct linemessage_tag {
    DWORD hDevice;
    DWORD dwMessageID;
    DWORD_PTR dwCallbackInstance;
    DWORD_PTR dwParam1;
    DWORD_PTR dwParam2;
    DWORD_PTR dwParam3;
} LINEMESSAGE;
typedef LINEMESSAGE *LPLINEMESSAGE;

/* LINEPROVIDERENTRY page (ms894431). */
typedef struct lineproviderentry_tag {
    DWORD dwPermanentProviderID;
    DWORD dwProviderFilenameSize;
    DWORD dwProviderFilenameOffset;
} LINEPROVIDERENTRY;
typedef LINEPROVIDERENTRY *LPLINEPROVIDERENTRY;

/* LINEPROVIDERLIST page (ms894433). */
typedef struct lineproviderlist_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwNumProviders;
    DWORD dwProviderListSize;
    DWORD dwProviderListOffset;
} LINEPROVIDERLIST;
typedef LINEPROVIDERLIST *LPLINEPROVIDERLIST;

/* LINETRANSLATECAPS page (ms894541). */
typedef struct linetranslatecaps_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwNumLocations;
    DWORD dwLocationListSize;
    DWORD dwLocationListOffset;
    DWORD dwCurrentLocationID;
    DWORD dwNumCards;
    DWORD dwCardListSize;
    DWORD dwCardListOffset;
    DWORD dwCurrentPreferredCardID;
} LINETRANSLATECAPS;
typedef LINETRANSLATECAPS *LPLINETRANSLATECAPS;

/* LINETRANSLATEOUTPUT page (ms894550). */
typedef struct linetranslateoutput_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwDialableStringSize;
    DWORD dwDialableStringOffset;
    DWORD dwDisplayableStringSize;
    DWORD dwDisplayableStringOffset;
    DWORD dwCurrentCountry;
    DWORD dwDestCountry;
    DWORD dwTranslateResults;
} LINETRANSLATEOUTPUT;
typedef LINETRANSLATEOUTPUT *LPLINETRANSLATEOUTPUT;

/* PHONECAPS page (ms895911). */
typedef struct phonecaps_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwProviderInfoSize;
    DWORD dwProviderInfoOffset;
    DWORD dwPhoneInfoSize;
    DWORD dwPhoneInfoOffset;
    DWORD dwPermanentPhoneID;
    DWORD dwPhoneNameSize;
    DWORD dwPhoneNameOffset;
    DWORD dwStringFormat;
    DWORD dwPhoneStates;
    DWORD dwHookSwitchDevs;
    DWORD dwHandsetHookSwitchModes;
    DWORD dwSpeakerHookSwitchModes;
    DWORD dwHeadsetHookSwitchModes;
    DWORD dwVolumeFlags;
    DWORD dwGainFlags;
    DWORD dwDisplayNumRows;
    DWORD dwDisplayNumColumns;
    DWORD dwNumRingModes;
    DWORD dwNumButtonLamps;
    DWORD dwButtonModesSize;
    DWORD dwButtonModesOffset;
    DWORD dwButtonModesFunctionsSize;
    DWORD dwButtonModesFunctionsOffset;
    DWORD dwLampModesSize;
    DWORD dwLampModesOffset;
    DWORD dwNumSetData;
    DWORD dwSetDataSize;
    DWORD dwSetDataOffset;
    DWORD dwNumGetData;
    DWORD dwGetDataSize;
    DWORD dwGetDataOffset;
    DWORD dwDevSpecificSize;
    DWORD dwDevSpecificOffset;
    DWORD dwDeviceClassesSize;
    DWORD dwDeviceClassesOffset;
    DWORD dwPhoneFeatures;
    DWORD dwSettableHandsetHookSwitchModes;
    DWORD dwSettableSpeakerHookSwitchModes;
    DWORD dwSettableHeadsetHookSwitchModes;
    DWORD dwMonitoredHandsetHookSwitchModes;
    DWORD dwMonitoredSpeakerHookSwitchModes;
    DWORD dwMonitoredHeadsetHookSwitchModes;
} PHONECAPS;
/* The CE page declares the structure without a pointer alias;
 * TSPI_phoneGetDevCaps (aa451031) names LPPHONECAPS, so the
 * standard lp alias is added. */
typedef PHONECAPS *LPPHONECAPS;

/* PHONEEXTENSIONID page (ms895923). */
typedef struct phoneextensionid_tag {
    DWORD dwExtensionID0;
    DWORD dwExtensionID1;
    DWORD dwExtensionID2;
    DWORD dwExtensionID3;
} PHONEEXTENSIONID;
typedef PHONEEXTENSIONID *LPPHONEEXTENSIONID;

/* PHONEINITIALIZEEXPARAMS page (ms895939). */
typedef struct phoneinitializeexparams_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwOptions;
    union {HANDLE hEvent;HANDLE hCompletionPort;} Handles;
    DWORD dwCompletionKey;
} PHONEINITIALIZEEXPARAMS;
typedef PHONEINITIALIZEEXPARAMS *LPPHONEINITIALIZEEXPARAMS;

/* PHONEMESSAGE page (ms895941). */
typedef struct phonemessage_tag {
    DWORD hDevice;
    DWORD dwMessageID;
    DWORD dwCallbackInstance;
    DWORD dwParam1;
    DWORD dwParam2;
    DWORD dwParam3;
} PHONEMESSAGE;
typedef PHONEMESSAGE *LPPHONEMESSAGE;

/* PHONESTATUS page (ms896250). */
typedef struct phonestatus_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwStatusFlags;
    DWORD dwNumOwners;
    DWORD dwNumMonitors;
    DWORD dwRingMode;
    DWORD dwRingVolume;
    DWORD dwHandsetHookSwitchMode;
    DWORD dwHandsetVolume;
    DWORD dwHandsetGain;
    DWORD dwSpeakerHookSwitchMode;
    DWORD dwSpeakerVolume;
    DWORD dwSpeakerGain;
    DWORD dwHeadsetHookSwitchMode;
    DWORD dwHeadsetVolume;
    DWORD dwHeadsetGain;
    DWORD dwDisplaySize;
    DWORD dwDisplayOffset;
    DWORD dwLampModesSize;
    DWORD dwLampModesOffset;
    DWORD dwOwnerNameSize;
    DWORD dwOwnerNameOffset;
    DWORD dwDevSpecificSize;
    DWORD dwDevSpecificOffset;
    DWORD dwPhoneFeatures;
} PHONESTATUS;
typedef PHONESTATUS *LPPHONESTATUS;

/* VARSTRING page (ms898569). */
typedef struct varstring_tag {
    DWORD dwTotalSize;
    DWORD dwNeededSize;
    DWORD dwUsedSize;
    DWORD dwStringFormat;
    DWORD dwStringSize;
    DWORD dwStringOffset;
} VARSTRING;
typedef VARSTRING *LPVARSTRING;
/* ------------------------------------------------------------------ */
/* TAPI constants (the TAPI Constants pages: 63 pages, 643 values;     */
/* the 2 constant pages that publish no values are recorded, not      */
/* defined -- docs/inventory.md M43).                                 */
/* ------------------------------------------------------------------ */
/* LINEADDRCAPFLAGS (ms893345) */
#define LINEADDRCAPFLAGS_ACCEPTTOALERT 0x00010000
#define LINEADDRCAPFLAGS_AUTORECONNECT 0x00000400
#define LINEADDRCAPFLAGS_BLOCKIDDEFAULT 0x00000008
#define LINEADDRCAPFLAGS_BLOCKIDOVERRIDE 0x00000010
#define LINEADDRCAPFLAGS_CONFDROP    0x00200000
#define LINEADDRCAPFLAGS_CONFERENCEHELD 0x00004000
#define LINEADDRCAPFLAGS_CONFERENCEMAKE 0x00008000
#define LINEADDRCAPFLAGS_DESTOFFHOOK 0x00000080
#define LINEADDRCAPFLAGS_DIALED      0x00000020
#define LINEADDRCAPFLAGS_FWDBUSYNAADDR 0x00080000
#define LINEADDRCAPFLAGS_FWDCONSULT  0x00000100
#define LINEADDRCAPFLAGS_FWDINTEXTADDR 0x00040000
#define LINEADDRCAPFLAGS_FWDNUMRINGS 0x00000001
#define LINEADDRCAPFLAGS_FWDSTATUSVALID 0x00020000
#define LINEADDRCAPFLAGS_HOLDMAKESNEW 0x04000000
#define LINEADDRCAPFLAGS_NOEXTERNALCALLS 0x10000000
#define LINEADDRCAPFLAGS_NOINTERNALCALLS 0x08000000
#define LINEADDRCAPFLAGS_ORIGOFFHOOK 0x000000040
#define LINEADDRCAPFLAGS_PARTIALDIAL 0x0001000
#define LINEADDRCAPFLAGS_PICKUPCALLWAIT 0x0040000
#define LINEADDRCAPFLAGS_PICKUPGROUPID 0x00000002
#define LINEADDRCAPFLAGS_PREDICTIVEDIALER 0x0080000
#define LINEADDRCAPFLAGS_QUEUE       0x0100000
#define LINEADDRCAPFLAGS_ROUTEPOINT  0x0200000
#define LINEADDRCAPFLAGS_SECURE      0x00000004
#define LINEADDRCAPFLAGS_SETCALLINGID 0x2000000
#define LINEADDRCAPFLAGS_SETUPCONFNULL 0x00000200
#define LINEADDRCAPFLAGS_TRANSFERHELD 0x00001000
#define LINEADDRCAPFLAGS_TRANSFERMAKE 0x00002000

/* LINEADDRESSMODE (ms893356) */
#define LINEADDRESSMODE_ADDRESSID    0x00000001
#define LINEADDRESSMODE_DIALABLEADDR 0x00000002

/* LINEADDRESSSHARING (ms893362) */
#define LINEADDRESSSHARING_PRIVATE   0x00000001
#define LINEADDRESSSHARING_BRIDGEDEXCL 0x00000002
#define LINEADDRESSSHARING_BRIDGEDNEW 0x00000004
#define LINEADDRESSSHARING_BRIDGEDSHARED 0x00000008
#define LINEADDRESSSHARING_MONITORED 0x00000010

/* LINEADDRESSSTATE (ms893367) */
#define LINEADDRESSSTATE_CAPSCHANGE  0x00000100
#define LINEADDRESSSTATE_DEVSPECIFIC 0x00000002
#define LINEADDRESSSTATE_FORWARD     0x00000040
#define LINEADDRESSSTATE_INUSEMANY   0x00000010
#define LINEADDRESSSTATE_INUSEONE    0x00000008
#define LINEADDRESSSTATE_INUSEZERO   0x00000004
#define LINEADDRESSSTATE_NUMCALLS    0x00000020
#define LINEADDRESSSTATE_OTHER       0x00000001
#define LINEADDRESSSTATE_TERMINALS   0x00000080

/* LINEADDRESSTYPE (ms893386) */
#define LINEADDRESSTYPE_PHONENUMBER  0x00000001
#define LINEADDRESSTYPE_SDP          0x00000002
#define LINEADDRESSTYPE_EMAILNAME    0x00000004
#define LINEADDRESSTYPE_DOMAINNAME   0x00000008
#define LINEADDRESSTYPE_IPADDRESS    0x00000010

/* LINEADDRFEATURE (ms898980) */
#define LINEADDRFEATURE_FORWARD      0x00000001
#define LINEADDRFEATURE_MAKECALL     0x00000002
#define LINEADDRFEATURE_PICKUP       0x00000004
#define LINEADDRFEATURE_PICKUPDIRECT 0x00000400
#define LINEADDRFEATURE_PICKUPGROUP  0x00000200
#define LINEADDRFEATURE_PICKUPHELD   0x00000100
#define LINEADDRFEATURE_PICKUPWAITING 0x00000800
#define LINEADDRFEATURE_SETMEDIACONTROL 0x00000008
#define LINEADDRFEATURE_SETTERMINAL  0x00000010
#define LINEADDRFEATURE_SETUPCONF    0x00000020
#define LINEADDRFEATURE_UNCOMPLETECALL 0x00000040
#define LINEADDRFEATURE_UNPARK       0x00000080
#define LINEADDRFEATURE_FORWARDDND   0x00001000
#define LINEADDRFEATURE_FORWARDFWD   0x00002000

/* LINEANSWERMODE (ms898981) */
#define LINEANSWERMODE_DROP          0x00000002
#define LINEANSWERMODE_HOLD          0x00000004
#define LINEANSWERMODE_NONE          0x00000001

/* LINEBEARERMODE (ms893407) */
#define LINEBEARERMODE_ALTSPEECHDATA 0x00000010
#define LINEBEARERMODE_DATA          0x00000008
#define LINEBEARERMODE_MULTIUSE      0x00000004
#define LINEBEARERMODE_NONCALLSIGNALING 0x00000020
#define LINEBEARERMODE_PASSTHROUGH   0x00000040
#define LINEBEARERMODE_RESTRICTEDDATA 0x00000080
#define LINEBEARERMODE_SPEECH        0x00000002
#define LINEBEARERMODE_VOICE         0x00000001

/* LINEBUSYMODE (ms893419) */
#define LINEBUSYMODE_STATION         0x00000001
#define LINEBUSYMODE_TRUNK           0x00000002
#define LINEBUSYMODE_UNKNOWN         0x00000004
#define LINEBUSYMODE_UNAVAIL         0x00000008

/* LINECALLCOMPLCOND (ms893430) */
#define LINECALLCOMPLCOND_BUSY       0x00000001
#define LINECALLCOMPLCOND_NOANSWER   0x00000002

/* LINECALLCOMPLMODE (ms893519) */
#define LINECALLCOMPLMODE_CALLBACK   0x00000002
#define LINECALLCOMPLMODE_CAMPON     0x00000001
#define LINECALLCOMPLMODE_INTRUDE    0x00000004
#define LINECALLCOMPLMODE_MESSAGE    0x00000008

/* LINECALLFEATURE (ms893582) */
#define LINECALLFEATURE_ACCEPT       0x000000001
#define LINECALLFEATURE_ADDTOCONF    0x00000002
#define LINECALLFEATURE_ANSWER       0x00000004
#define LINECALLFEATURE_BLINDTRANSFER 0x00000008
#define LINECALLFEATURE_COMPLETETRANSF 0x00000020
#define LINECALLFEATURE_DIAL         0x00000040
#define LINECALLFEATURE_DROP         0x00000080
#define LINECALLFEATURE_GENERATEDIGITS 0x00000200
#define LINECALLFEATURE_GENERATETONE 0x00000400
#define LINECALLFEATURE_HOLD         0x00000800
#define LINECALLFEATURE_MONITORDIGITS 0x00001000
#define LINECALLFEATURE_MONITORMEDIA 0x00002000
#define LINECALLFEATURE_PREPAREADDCONF 0x00010000
#define LINECALLFEATURE_REDIRECT     0x00020000
#define LINECALLFEATURE_RELEASEUSERUSERINFO 0x10000000
#define LINECALLFEATURE_REMOVEFROMCONF 0x00040000
#define LINECALLFEATURE_SENDUSERUSER 0x00100000
#define LINECALLFEATURE_SETCALLPARAMS 0x00200000
#define LINECALLFEATURE_SETQOS       0x40000000
#define LINECALLFEATURE_SETTERMINAL  0x00800000
#define LINECALLFEATURE_SETUPCONF    0x01000000
#define LINECALLFEATURE_SETTREATMENT 0x20000000
#define LINECALLFEATURE_SETUPTRANSFER 0x02000000
#define LINECALLFEATURE_SWAPHOLD     0x04000000
#define LINECALLFEATURE_UNHOLD       0x08000000

/* LINECALLFEATURE2 (ms893599) */
#define LINECALLFEATURE2_NOHOLDCONFERENCE 0x00000001
#define LINECALLFEATURE2_ONESTEPTRANSFER 0x00000002
#define LINECALLFEATURE2_TRANSFERCONF 0x00000080
#define LINECALLFEATURE2_TRANSFERNORM 0x00000040

/* LINECALLINFOSTATE (ms893623) */
#define LINECALLINFOSTATE_APPSPECIFIC 0x00000020
#define LINECALLINFOSTATE_BEARERMODE 0x00000004
#define LINECALLINFOSTATE_CALLDATA   0x40000000
#define LINECALLINFOSTATE_CALLEDID   0x00010000
#define LINECALLINFOSTATE_CALLERID   0x00008000
#define LINECALLINFOSTATE_CALLID     0x00000040
#define LINECALLINFOSTATE_CHARGINGINFO 0x01000000
#define LINECALLINFOSTATE_COMPLETIONID 0x00000400
#define LINECALLINFOSTATE_CONNECTEDID 0x00020000
#define LINECALLINFOSTATE_DEVSPECIFIC 0x00000002
#define LINECALLINFOSTATE_DIALPARAMS 0x04000000
#define LINECALLINFOSTATE_DISPLAY    0x00100000
#define LINECALLINFOSTATE_HIGHLEVELCOMP 0x00400000
#define LINECALLINFOSTATE_LOWLEVELCOMP 0x00800000
#define LINECALLINFOSTATE_MEDIAMODE  0x00000010
#define LINECALLINFOSTATE_MONITORMODES 0x08000000
#define LINECALLINFOSTATE_NUMMONITORS 0x00002000
#define LINECALLINFOSTATE_NUMOWNERDECR 0x00001000
#define LINECALLINFOSTATE_NUMOWNERINCR 0x00000800
#define LINECALLINFOSTATE_ORIGIN     0x00000100
#define LINECALLINFOSTATE_OTHER      0x00000001
#define LINECALLINFOSTATE_QOS        0x2000000
#define LINECALLINFOSTATE_RATE       0x00000008
#define LINECALLINFOSTATE_REASON     0x00000200
#define LINECALLINFOSTATE_REDIRECTINGID 0x00080000
#define LINECALLINFOSTATE_REDIRECTIONID 0x00040000
#define LINECALLINFOSTATE_RELATEDCALLID 0x00000080
#define LINECALLINFOSTATE_TERMINAL   0x02000000
#define LINECALLINFOSTATE_TREATMENT  0x10000000
#define LINECALLINFOSTATE_TRUNK      0x00004000
#define LINECALLINFOSTATE_USERUSERINFO 0x00200000

/* LINECALLORIGIN (ms893672) */
#define LINECALLORIGIN_CONFERENCE    0x00000040
#define LINECALLORIGIN_EXTERNAL      0x00000004
#define LINECALLORIGIN_INBOUND       0x00000080
#define LINECALLORIGIN_INTERNAL      0x00000002
#define LINECALLORIGIN_OUTBOUND      0x00000001
#define LINECALLORIGIN_UNAVAIL       0x00000020
#define LINECALLORIGIN_UNKNOWN       0x00000010

/* LINECALLPARAMFLAGS (ms893682) */
#define LINECALLPARAMFLAGS_BLOCKID   0x00000004
#define LINECALLPARAMFLAGS_DESTOFFHOOK 0x00000010
#define LINECALLPARAMFLAGS_IDLE      0x00000002
#define LINECALLPARAMFLAGS_NOHOLDCONFERENCE 0x00000020
#define LINECALLPARAMFLAGS_ONESTEPTRANSFER 0x00000080
#define LINECALLPARAMFLAGS_ORIGOFFHOOK 0x00000008
#define LINECALLPARAMFLAGS_PREDICTIVEDIAL 0x00000040
#define LINECALLPARAMFLAGS_SECURE    0x00000001

/* LINECALLPARTYID (ms893855) */
#define LINECALLPARTYID_ADDRESS      0x00000008
#define LINECALLPARTYID_BLOCKED      0x00000001
#define LINECALLPARTYID_NAME         0x00000004
#define LINECALLPARTYID_OUTOFAREA    0x00000002
#define LINECALLPARTYID_PARTIAL      0x00000010
#define LINECALLPARTYID_UNAVAIL      0x00000040
#define LINECALLPARTYID_UNKNOWN      0x00000020

/* LINECALLPRIVILEGE (ms893958) */
#define LINECALLPRIVILEGE_MONITOR    0x00000002
#define LINECALLPRIVILEGE_NONE       0x00000001
#define LINECALLPRIVILEGE_OWNER      0x00000004

/* LINECALLREASON (ms893966) */
#define LINECALLREASON_CALLCOMPLETION 0x00000080
#define LINECALLREASON_CAMPEDON      0x00004000
#define LINECALLREASON_DIRECT        0x00000001
#define LINECALLREASON_FWDBUSY       0x00000002
#define LINECALLREASON_FWDNOANSWER   0x00000004
#define LINECALLREASON_FWDUNCOND     0x00000008
#define LINECALLREASON_INTRUDE       0x00001000
#define LINECALLREASON_PARKED        0x000002000
#define LINECALLREASON_PICKUP        0x00000010
#define LINECALLREASON_REDIRECT      0x00000040
#define LINECALLREASON_REMINDER      0x00000200
#define LINECALLREASON_ROUTEREQUEST  0x00008000
#define LINECALLREASON_TRANSFER      0x00000100
#define LINECALLREASON_UNAVAIL       0x00000800
#define LINECALLREASON_UNKNOWN       0x00000400
#define LINECALLREASON_UNPARK        0x00000020

/* LINECALLSELECT (ms893976) */
#define LINECALLSELECT_ADDRESS       0x00000002
#define LINECALLSELECT_CALL          0x00000004
#define LINECALLSELECT_CALLID        0x00000010
#define LINECALLSELECT_DEVICEID      0x00000008
#define LINECALLSELECT_LINE          0x00000001

/* LINECALLSTATE (ms893984) */
#define LINECALLSTATE_ACCEPTED       0x00000004
#define LINECALLSTATE_BUSY           0x00000040
#define LINECALLSTATE_CONFERENCED    0x00000800
#define LINECALLSTATE_CONNECTED      0x00000100
#define LINECALLSTATE_DIALING        0x0000010
#define LINECALLSTATE_DIALTONE       0x00000008
#define LINECALLSTATE_DISCONNECTED   0x00004000
#define LINECALLSTATE_IDLE           0x00000001
#define LINECALLSTATE_OFFERING       0x000000002
#define LINECALLSTATE_ONHOLD         0x00000400
#define LINECALLSTATE_ONHOLDPENDCONF 0x00001000
#define LINECALLSTATE_ONHOLDPENDTRANSFER 0x00002000
#define LINECALLSTATE_PROCEEDING     0x00000200
#define LINECALLSTATE_RINGBACK       0x00000020
#define LINECALLSTATE_SPECIALINFO    0x00000080
#define LINECALLSTATE_UNKNOWN        0x00008000

/* LINECALLTREATMENT (ms894115) */
#define LINECALLTREATMENT_BUSY       0x00000003
#define LINECALLTREATMENT_MUSIC      0x00000004
#define LINECALLTREATMENT_RINGBACK   0x00000002
#define LINECALLTREATMENT_SILENCE    0x00000001

/* LINECONNECTEDMODE (ms894124) */
#define LINECONNECTEDMODE_ACTIVE     0x00000001
#define LINECONNECTEDMODE_ACTIVEHELD 0x00000004
#define LINECONNECTEDMODE_CONFIRMED  0x00000010
#define LINECONNECTEDMODE_INACTIVE   0x00000002
#define LINECONNECTEDMODE_INACTIVEHELD 0x00000008

/* LINEDEVCAPFLAGS (ms894129) */
#define LINEDEVCAPFLAGS_CALLHUB      0x00000400
#define LINEDEVCAPFLAGS_CALLHUBTRACKING 0x00000800
#define LINEDEVCAPFLAGS_CLOSEDROP    0x00000020
#define LINEDEVCAPFLAGS_CROSSADDRCONF 0x00000001
#define LINEDEVCAPFLAGS_HIGHLEVCOMP  0x00000002
#define LINEDEVCAPFLAGS_LOWLEVCOMP   0x00000004
#define LINEDEVCAPFLAGS_MEDIACONTROL 0x00000008
#define LINEDEVCAPFLAGS_MSP          0x00000200
#define LINEDEVCAPFLAGS_MULTIPLEADDR 0x00000010
#define LINEDEVCAPFLAGS_PRIVATEOBJECTS 0x00001000

/* LINEDEVSTATE (ms894134) */
#define LINEDEVSTATE_BATTERY         0x00008000
#define LINEDEVSTATE_CAPSCHANGE      0x00100000
#define LINEDEVSTATE_CLOSE           0x00000400
#define LINEDEVSTATE_CONFIGCHANGE    0x00200000
#define LINEDEVSTATE_CONNECTED       0x00000004
#define LINEDEVSTATE_DEVSPECIFIC     0x00020000
#define LINEDEVSTATE_DISCONNECTED    0x00000008
#define LINEDEVSTATE_INSERVICE       0x00000040
#define LINEDEVSTATE_LOCK            0x00080000
#define LINEDEVSTATE_MAINTENANCE     0x00000100
#define LINEDEVSTATE_MSGWAITOFF      0x00000020
#define LINEDEVSTATE_MSGWAITON       0x00000010
#define LINEDEVSTATE_NUMCALLS        0x00000800
#define LINEDEVSTATE_NUMCOMPLETIONS  0x00001000
#define LINEDEVSTATE_OPEN            0x00000200
#define LINEDEVSTATE_OTHER           0x00000001
#define LINEDEVSTATE_OUTOFSERVICE    0x00000080
#define LINEDEVSTATE_REINIT          0x00040000
#define LINEDEVSTATE_REMOVED         0x01000000
#define LINEDEVSTATE_RINGING         0x00000002
#define LINEDEVSTATE_ROAMMODE        0x00004000
#define LINEDEVSTATE_SIGNAL          0x00010000
#define LINEDEVSTATE_TERMINALS       0x00002000
#define LINEDEVSTATE_TRANSLATECHANGE 0x00400000

/* LINEDEVSTATUSFLAGS (ms894136) */
#define LINEDEVSTATUSFLAGS_INSERVICE 0x00000004
#define LINEDEVSTATUSFLAGS_LOCKED    0x00000008
#define LINEDEVSTATUSFLAGS_MSGWAIT   0x00000002

/* LINEDIALTONEMODE (ms894139) */
#define LINEDIALTONEMODE_EXTERNAL    0x00000008
#define LINEDIALTONEMODE_INTERNAL    0x00000004
#define LINEDIALTONEMODE_NORMAL      0x00000001
#define LINEDIALTONEMODE_SPECIAL     0x00000002
#define LINEDIALTONEMODE_UNAVAIL     0x00000020
#define LINEDIALTONEMODE_UNKNOWN     0x00000010

/* LINEDIGITMODE (ms894140) */
#define LINEDIGITMODE_DTMF           0x00000002
#define LINEDIGITMODE_DTMFEND        0x00000004
#define LINEDIGITMODE_PULSE          0x00000001

/* LINEDISCONNECTMODE (ms894141) */
#define LINEDISCONNECTMODE_BADADDRESS 0x00000080
#define LINEDISCONNECTMODE_BLOCKED   0x00020000
#define LINEDISCONNECTMODE_BUSY      0x00000020
#define LINEDISCONNECTMODE_CANCELLED 0x00080000
#define LINEDISCONNECTMODE_CONGESTION 0x00000200
#define LINEDISCONNECTMODE_DONOTDISTURB 0x00040000
#define LINEDISCONNECTMODE_FORWARDED 0x00000010
#define LINEDISCONNECTMODE_INCOMPATIBLE 0x00000400
#define LINEDISCONNECTMODE_NOANSWER  0x00000040
#define LINEDISCONNECTMODE_NODIALTONE 0x00001000
#define LINEDISCONNECTMODE_NORMAL    0x00000001
#define LINEDISCONNECTMODE_NUMBERCHANGED 0x00002000
#define LINEDISCONNECTMODE_OUTOFORDER 0x00004000
#define LINEDISCONNECTMODE_PICKUP    0x00000008
#define LINEDISCONNECTMODE_QOSUNAVAIL 0x00010000
#define LINEDISCONNECTMODE_REJECT    0x00000004
#define LINEDISCONNECTMODE_TEMPFAILURE 0x00008000
#define LINEDISCONNECTMODE_UNAVAIL   0x00000800
#define LINEDISCONNECTMODE_UNKNOWN   0x00000002
#define LINEDISCONNECTMODE_UNREACHABLE 0x00000100

/* LINEERR (ms894143) */
#define LINEERR_ADDRESSBLOCKED       0x80000053
#define LINEERR_ALLOCATED            0x00000001
#define LINEERR_BADDEVICEID          0x00000002
#define LINEERR_BEARERMODEUNAVAIL    0x00000003
#define LINEERR_BILLINGREJECTED      0x80000054
#define LINEERR_CALLUNAVAIL          0x0000005
#define LINEERR_COMPLETIONOVERRUN    0x0000006
#define LINEERR_CONFERENCEFULL       0x00000007
#define LINEERR_DIALBILLING          0x00000008
#define LINEERR_DIALDIALTONE         0x00000009
#define LINEERR_DIALPROMPT           0x8000000A
#define LINEERR_DIALQUIET            0x8000000B
#define LINEERR_DIALVOICEDETECT      0x8000005C
#define LINEERR_INCOMPATIBLEAPIVERSION 0x8000000C
#define LINEERR_INCOMPATIBLEEXTVERSION 0x8000000D
#define LINEERR_INIFILECORRUPT       0x8000000E
#define LINEERR_INUSE                0x8000000F
#define LINEERR_INVALADDRESS         0x80000010
#define LINEERR_INVALADDRESSID       0x80000011
#define LINEERR_INVALADDRESSMODE     0x80000012
#define LINEERR_INVALADDRESSSTATE    0x80000013
#define LINEERR_INVALAPPHANDLE       0x80000014
#define LINEERR_INVALAPPNAME         0x80000015
#define LINEERR_INVALBEARERMODE      0x80000016
#define LINEERR_INVALCALLHANDLE      0x80000018
#define LINEERR_INVALCALLPARAMS      0x80000019
#define LINEERR_INVALCALLPRIVILEGE   0x8000001A
#define LINEERR_INVALCALLSELECT      0x8000001B
#define LINEERR_INVALCALLSTATE       0x8000001C
#define LINEERR_INVALCALLSTATELIST   0x8000001D
#define LINEERR_INVALCARD            0x8000001E
#define LINEERR_INVALCOMPLETIONID    0x8000001F
#define LINEERR_INVALCONFCALLHANDLE  0x80000020
#define LINEERR_INVALCONSULTCALLHANDLE 0x80000021
#define LINEERR_INVALCOUNTRYCODE     0x80000022
#define LINEERR_INVALDEVICECLASS     0x80000023
#define LINEERR_INVALDEVICEHANDLE    0x80000024
#define LINEERR_INVALDIALPARAMS      0x80000025
#define LINEERR_INVALDIGITLIST       0x80000026
#define LINEERR_INVALDIGITMODE       0x80000027
#define LINEERR_INVALDIGITS          0x80000028
#define LINEERR_INVALEXTVERSION      0x80000029
#define LINEERR_INVALFEATURE         0x80000055
#define LINEERR_INVALGROUPID         0x8000002A
#define LINEERR_INVALLINEHANDLE      0x8000002B
#define LINEERR_INVALLINESTATE       0x8000002C
#define LINEERR_INVALLOCATION        0x8000002D
#define LINEERR_INVALMEDIALIST       0x8000002E
#define LINEERR_INVALMEDIAMODE       0x8000002F
#define LINEERR_INVALMESSAGEID       0x80000030
#define LINEERR_INVALPARAM           0x80000032
#define LINEERR_INVALPARKID          0x80000033
#define LINEERR_INVALPARKMODE        0x80000034
#define LINEERR_INVALPASSWORD        0x80000059
#define LINEERR_INVALPOINTER         0x80000035
#define LINEERR_INVALPRIVSELECT      0x80000036
#define LINEERR_INVALRATE            0x80000037
#define LINEERR_INVALREQUESTMODE     0x80000038
#define LINEERR_INVALTERMINALID      0x80000039
#define LINEERR_INVALTERMINALMODE    0x8000003A
#define LINEERR_INVALTIMEOUT         0x8000003B
#define LINEERR_INVALTONE            0x8000003C
#define LINEERR_INVALTONELIST        0x8000003D
#define LINEERR_INVALTONEMODE        0x8000003E
#define LINEERR_INVALTRANSFERMODE    0x8000003F
#define LINEERR_LINEMAPPERFAILED     0x80000040
#define LINEERR_NOCONFERENCE         0x80000041
#define LINEERR_NODEVICE             0x80000042
#define LINEERR_NODRIVER             0x80000043
#define LINEERR_NOMEM                0x80000044
#define LINEERR_NOMULTIPLEINSTANCE   0x80000056
#define LINEERR_NOREQUEST            0x80000045
#define LINEERR_NOTOWNER             0x80000046
#define LINEERR_NOTREGISTERED        0x80000047
#define LINEERR_OPERATIONFAILED      0x80000048
#define LINEERR_OPERATIONUNAVAIL     0x80000049
#define LINEERR_RATEUNAVAIL          0x8000004A
#define LINEERR_REINIT               0x80000052
#define LINEERR_REQUESTOVERRUN       0x8000004C
#define LINEERR_RESOURCEUNAVAIL      0x8000004B
#define LINEERR_STRUCTURETOOSMALL    0x8000004D
#define LINEERR_TARGETNOTFOUND       0x8000004E
#define LINEERR_TARGETSELF           0x8000004F
#define LINEERR_UNINITIALIZED        0x80000050
#define LINEERR_USERUSERINFOTOOBIG   0x80000051

/* LINEFEATURE (ms894146) */
#define LINEFEATURE_DEVSPECIFIC      0x00000001
#define LINEFEATURE_DEVSPECIFICFEAT  0x00000002
#define LINEFEATURE_FORWARD          0x00000004
#define LINEFEATURE_FORWARDDND       0x00000100
#define LINEFEATURE_FORWARDFWD       0x00000080
#define LINEFEATURE_MAKECALL         0x00000008
#define LINEFEATURE_SETMEDIACONTROL  0x00000010
#define LINEFEATURE_SETTERMINAL      0x00000020

/* LINEFORWARDMODE (ms894149) */
#define LINEFORWARDMODE_BUSY         0x00000010
#define LINEFORWARDMODE_BUSYEXTERNAL 0x00000040
#define LINEFORWARDMODE_BUSYINTERNAL 0x00000020
#define LINEFORWARDMODE_BUSYSPECIFIC 0x00000080
#define LINEFORWARDMODE_BUSYNA       0x00001000
#define LINEFORWARDMODE_BUSYNAEXTERNAL 0x00004000
#define LINEFORWARDMODE_BUSYNAINTERNAL 0x00002000
#define LINEFORWARDMODE_BUSYNASPECIFIC 0x00008000
#define LINEFORWARDMODE_NOANSW       0x00000100
#define LINEFORWARDMODE_NOANSWEXTERNAL 0x00000400
#define LINEFORWARDMODE_NOANSWINTERNAL 0x00000200
#define LINEFORWARDMODE_NOANSWSPECIFIC 0x00000800
#define LINEFORWARDMODE_UNAVAIL      0x00020000
#define LINEFORWARDMODE_UNCOND       0x00000001
#define LINEFORWARDMODE_UNCONDEXTERNAL 0x00000004
#define LINEFORWARDMODE_UNCONDINTERNAL 0x00000002
#define LINEFORWARDMODE_UNCONDSPECIFIC 0x00000008
#define LINEFORWARDMODE_UNKNOWN      0x00010000

/* LINEGATHERTERM (ms894151) */
#define LINEGATHERTERM_BUFFERFULL    0x00000001
#define LINEGATHERTERM_CANCEL        0x00000010
#define LINEGATHERTERM_FIRSTTIMEOUT  0x00000004
#define LINEGATHERTERM_INTERTIMEOUT  0x00000008
#define LINEGATHERTERM_TERMDIGIT     0x00000002

/* LINEGENERATETERM (ms894154) */
#define LINEGENERATETERM_CANCEL      0x00000002
#define LINEGENERATETERM_DONE        0x00000001

/* LINEINITIALIZEEXOPTION (ms894371) */
#define LINEINITIALIZEEXOPTION_USECOMPLETIONPORT 0x00000003
#define LINEINITIALIZEEXOPTION_USEEVENT 0x00000002
#define LINEINITIALIZEEXOPTION_USEHIDDENWINDOW 0x00000001

/* LINEMEDIACONTROL (ms894388) */
#define LINEMEDIACONTROL_NONE        0x00000001
#define LINEMEDIACONTROL_PAUSE       0x00000008
#define LINEMEDIACONTROL_RATENORMAL  0x00000080
#define LINEMEDIACONTROL_RATEDOWN    0x00000040
#define LINEMEDIACONTROL_RATEUP      0x00000020
#define LINEMEDIACONTROL_RESET       0x00000004
#define LINEMEDIACONTROL_RESUME      0x00000010
#define LINEMEDIACONTROL_START       0x00000002
#define LINEMEDIACONTROL_VOLUMEDOWN  0x00000200
#define LINEMEDIACONTROL_VOLUMENORMAL 0x00000400
#define LINEMEDIACONTROL_VOLUMEUP    0x00000100

/* LINEMEDIAMODE (ms894389) */
#define LINEMEDIAMODE_AUTOMATEDVOICE 0x00000008
#define LINEMEDIAMODE_DATAMODEM      0x00000010
#define LINEMEDIAMODE_ADSI           0x00002000
#define LINEMEDIAMODE_DIGITALDATA    0x00000100
#define LINEMEDIAMODE_G3FAX          0x00000020
#define LINEMEDIAMODE_G4FAX          0x00000080
#define LINEMEDIAMODE_INTERACTIVEVOICE 0x00000004
#define LINEMEDIAMODE_MIXED          0x00001000
#define LINEMEDIAMODE_TDD            0x00000040
#define LINEMEDIAMODE_TELETEX        0x00000200
#define LINEMEDIAMODE_TELEX          0x00000800
#define LINEMEDIAMODE_VIDEOTEX       0x00000400
#define LINEMEDIAMODE_VOICEVIEW      0x00004000
#define LINEMEDIAMODE_UNKNOWN        0x00000002

/* LINEOFFERINGMODE (ms894409) */
#define LINEOFFERINGMODE_ACTIVE      0x00000001
#define LINEOFFERINGMODE_INACTIVE    0x00000002

/* LINEOPENOPTION (ms894421) */
#define LINEOPENOPTION_PROXY         0x40000000
#define LINEOPENOPTION_SINGLEADDRESS 0x80000000

/* LINEPARKMODE (ms894422) */
#define LINEPARKMODE_DIRECTED        0x00000001
#define LINEPARKMODE_NONDIRECTED     0x00000002

/* LINEREMOVEFROMCONF (ms894450) */
#define LINEREMOVEFROMCONF_ANY       0x00000003
#define LINEREMOVEFROMCONF_LAST      0x00000002
#define LINEREMOVEFROMCONF_NONE      0x00000001

/* LINEROAMMODE (ms894463) */
#define LINEROAMMODE_HOME            0x00000004
#define LINEROAMMODE_ROAMA           0x00000008
#define LINEROAMMODE_ROAMB           0x00000010
#define LINEROAMMODE_UNAVAIL         0x00000002
#define LINEROAMMODE_UNKNOWN         0x00000001

/* LINESPECIALINFO (ms894520) */
#define LINESPECIALINFO_CUSTIRREG    0x00000002
#define LINESPECIALINFO_NOCIRCUIT    0x00000001
#define LINESPECIALINFO_REORDER      0x00000004
#define LINESPECIALINFO_UNAVAIL      0x00000010
#define LINESPECIALINFO_UNKNOWN      0x00000008

/* LINETERMDEV (ms894525) */
#define LINETERMDEV_HEADSET          0x00000002
#define LINETERMDEV_PHONE            0x00000001
#define LINETERMDEV_SPEAKER          0x00000004

/* LINETERMMODE (ms894528) */
#define LINETERMMODE_BUTTONS         0x00000001
#define LINETERMMODE_DISPLAY         0x00000004
#define LINETERMMODE_HOOKSWITCH      0x00000010
#define LINETERMMODE_LAMPS           0x00000002
#define LINETERMMODE_MEDIABIDIRECT   0x00000080
#define LINETERMMODE_MEDIAFROMLINE   0x00000040
#define LINETERMMODE_MEDIATOLINE     0x00000020
#define LINETERMMODE_RINGER          0x00000008

/* LINETERMSHARING (ms894530) */
#define LINETERMSHARING_PRIVATE      0x00000001
#define LINETERMSHARING_SHAREDCONF   0x00000004
#define LINETERMSHARING_SHAREDEXCL   0x00000002

/* LINETOLLLISTOPTION (ms894532) */
#define LINETOLLLISTOPTION_ADD       0x00000001
#define LINETOLLLISTOPTION_REMOVE    0x00000002

/* LINETONEMODE (ms894535) */
#define LINETONEMODE_BEEP            0x00000008
#define LINETONEMODE_BILLING         0x00000010
#define LINETONEMODE_BUSY            0x00000004
#define LINETONEMODE_CUSTOM          0x00000001
#define LINETONEMODE_RINGBACK        0x00000002

/* LINETRANSFERMODE (ms894537) */
#define LINETRANSFERMODE_CONFERENCE  0x00000002
#define LINETRANSFERMODE_TRANSFER    0x00000001

/* LINETRANSLATEOPTION (ms894546) */
#define LINETRANSLATEOPTION_CANCELCALLWAITING 0x00000002
#define LINETRANSLATEOPTION_CARDOVERRIDE 0x00000001
#define LINETRANSLATEOPTION_FORCELD  0x00000008
#define LINETRANSLATEOPTION_FORCELOCAL 0x00000004

/* LINETRANSLATERESULT (ms894553) */
#define LINETRANSLATERESULT_CANONICAL 0x00000001
#define LINETRANSLATERESULT_DIALBILLING 0x00000040
#define LINETRANSLATERESULT_DIALDIALTONE 0x00000100
#define LINETRANSLATERESULT_DIALPROMPT 0x00000200
#define LINETRANSLATERESULT_DIALQUIET 0x00000080
#define LINETRANSLATERESULT_INTERNATIONAL 0x00000002
#define LINETRANSLATERESULT_INTOLLLIST 0x00000010
#define LINETRANSLATERESULT_LOCAL    0x00000008
#define LINETRANSLATERESULT_LONGDISTANCE 0x00000004
#define LINETRANSLATERESULT_NOTINTOLLLIST 0x00000020
#define LINETRANSLATERESULT_VOICEDETECT 0x00000400

/* PHONEBUTTONFUNCTION (ms895905) */
#define PHONEBUTTONFUNCTION_ABBREVDIAL 0x0000000B
#define PHONEBUTTONFUNCTION_BUSY     0x0000001D
#define PHONEBUTTONFUNCTION_BRIDGEDAPP 0x0000001C
#define PHONEBUTTONFUNCTION_CALLAPP  0x0000001E
#define PHONEBUTTONFUNCTION_CALLID   0x00000022
#define PHONEBUTTONFUNCTION_CAMPON   0x0000002B
#define PHONEBUTTONFUNCTION_COVER    0x00000021
#define PHONEBUTTONFUNCTION_CONFERENCE 0x00000001
#define PHONEBUTTONFUNCTION_CONNECT  0x00000007
#define PHONEBUTTONFUNCTION_DATAOFF  0x00000019
#define PHONEBUTTONFUNCTION_DATAON   0x00000018
#define PHONEBUTTONFUNCTION_DATETIME 0x0000001F
#define PHONEBUTTONFUNCTION_DIRECTORY 0x00000020
#define PHONEBUTTONFUNCTION_DISCONNECT 0x00000006
#define PHONEBUTTONFUNCTION_DONOTDISTURB 0x0000001A
#define PHONEBUTTONFUNCTION_DROP     0x00000003
#define PHONEBUTTONFUNCTION_FLASH    0x00000017
#define PHONEBUTTONFUNCTION_FORWARD  0x0000000C
#define PHONEBUTTONFUNCTION_HOLD     0x00000004
#define PHONEBUTTONFUNCTION_INTERCOM 0x0000001B
#define PHONEBUTTONFUNCTION_LASTNUM  0x00000023
#define PHONEBUTTONFUNCTION_MSGINDICATOR 0x00000026
#define PHONEBUTTONFUNCTION_MSGWAITOFF 0x00000009
#define PHONEBUTTONFUNCTION_MSGWAITON 0x00000008
#define PHONEBUTTONFUNCTION_MUTE     0x00000012
#define PHONEBUTTONFUNCTION_NIGHTSRV 0x00000024
#define PHONEBUTTONFUNCTION_NONE     0x0000002E
#define PHONEBUTTONFUNCTION_PARK     0x0000000F
#define PHONEBUTTONFUNCTION_PICKUP   0x0000000D
#define PHONEBUTTONFUNCTION_QUEUECALL 0x0000002D
#define PHONEBUTTONFUNCTION_RECALL   0x00000005
#define PHONEBUTTONFUNCTION_REDIRECT 0x00000011
#define PHONEBUTTONFUNCTION_REJECT   0x00000010
#define PHONEBUTTONFUNCTION_REPDIAL  0x00000027
#define PHONEBUTTONFUNCTION_RINGAGAIN 0x0000000E
#define PHONEBUTTONFUNCTION_SAVEREPEAT 0x0000002C
#define PHONEBUTTONFUNCTION_SELECTRING 0x0000000A
#define PHONEBUTTONFUNCTION_SETREPDIAL 0x00000028
#define PHONEBUTTONFUNCTION_SENDCALLS 0x00000025
#define PHONEBUTTONFUNCTION_SPEAKEROFF 0x00000016
#define PHONEBUTTONFUNCTION_SPEAKERON 0x00000015
#define PHONEBUTTONFUNCTION_STATIONSPEED 0x0000002A
#define PHONEBUTTONFUNCTION_SYSTEMSPEED 0x00000029
#define PHONEBUTTONFUNCTION_TRANSFER 0x00000002
#define PHONEBUTTONFUNCTION_UNKNOWN  0x00000000
#define PHONEBUTTONFUNCTION_VOLUMEDOWN 0x00000014
#define PHONEBUTTONFUNCTION_VOLUMEUP 0x00000013

/* PHONEBUTTONMODE (ms895906) */
#define PHONEBUTTONMODE_CALL         0x00000002
#define PHONEBUTTONMODE_DISPLAY      0x00000020
#define PHONEBUTTONMODE_DUMMY        0x00000001
#define PHONEBUTTONMODE_FEATURE      0x00000004
#define PHONEBUTTONMODE_KEYPAD       0x00000008
#define PHONEBUTTONMODE_LOCAL        0x00000010

/* PHONEBUTTONSTATE (ms895907) */
#define PHONEBUTTONSTATE_DOWN        0x00000002
#define PHONEBUTTONSTATE_UNAVAIL     0x00000008
#define PHONEBUTTONSTATE_UNKNOWN     0x00000004
#define PHONEBUTTONSTATE_UP          0x00000001

/* PHONEERR (ms895921) */
#define PHONEERR_ALLOCATED           0x90000001
#define PHONEERR_BADDEVICEID         0x90000002
#define PHONEERR_INCOMPATIBLEAPIVERSION 0x90000003
#define PHONEERR_INCOMPATIBLEEXTVERSION 0x90000004
#define PHONEERR_INIFILECORRUPT      0x90000005
#define PHONEERR_INUSE               0x90000006
#define PHONEERR_INVALAPPHANDLE      0x90000007
#define PHONEERR_INVALAPPNAME        0x90000008
#define PHONEERR_INVALBUTTONLAMPID   0x90000009
#define PHONEERR_INVALBUTTONMODE     0x9000000A
#define PHONEERR_INVALBUTTONSTATE    0x9000000B
#define PHONEERR_INVALDATAID         0x9000000C
#define PHONEERR_INVALDEVICECLASS    0x9000000D
#define PHONEERR_INVALEXTVERSION     0x9000000E
#define PHONEERR_INVALHOOKSWITCHDEV  0x9000000F
#define PHONEERR_INVALHOOKSWITCHMODE 0x90000010
#define PHONEERR_INVALLAMPMODE       0x90000011
#define PHONEERR_INVALPARAM          0x90000012
#define PHONEERR_INVALPHONEHANDLE    0x90000013
#define PHONEERR_INVALPHONESTATE     0x90000014
#define PHONEERR_INVALPOINTER        0x90000015
#define PHONEERR_INVALPRIVILEGE      0x90000016
#define PHONEERR_INVALRINGMODE       0x90000017
#define PHONEERR_NODEVICE            0x90000018
#define PHONEERR_NODRIVER            0x90000019
#define PHONEERR_NOMEM               0x9000001A
#define PHONEERR_NOTOWNER            0x9000001B
#define PHONEERR_OPERATIONFAILED     0x9000001C
#define PHONEERR_OPERATIONUNAVAIL    0x9000001D
#define PHONEERR_REINIT              0x90000023
#define PHONEERR_REQUESTOVERRUN      0x90000020
#define PHONEERR_RESOURCEUNAVAIL     0x9000001F
#define PHONEERR_STRUCTURETOOSMALL   0x90000021
#define PHONEERR_UNINITIALIZED       0x90000022

/* PHONEFEATURE (ms895924) */
#define PHONEFEATURE_GETGAINHANDSET  0x00000008
#define PHONEFEATURE_GETGAINSPEAKER  0x00000010
#define PHONEFEATURE_GETGAINHEADSET  0x00000020
#define PHONEFEATURE_GETHOOKSWITCHHANDSET 0x00000040
#define PHONEFEATURE_GETHOOKSWITCHSPEAKER 0x00000080
#define PHONEFEATURE_GETHOOKSWITCHHEADSET 0x00000100
#define PHONEFEATURE_GETRING         0x00000400
#define PHONEFEATURE_GETVOLUMEHANDSET 0x00000800
#define PHONEFEATURE_GETVOLUMESPEAKER 0x00001000
#define PHONEFEATURE_GETVOLUMEHEADSET 0x00002000
#define PHONEFEATURE_SETGAINHANDSET  0x00020000
#define PHONEFEATURE_SETGAINSPEAKER  0x00040000
#define PHONEFEATURE_SETGAINHEADSET  0x00080000
#define PHONEFEATURE_SETHOOKSWITCHHANDSET 0x00100000
#define PHONEFEATURE_SETHOOKSWITCHSPEAKER 0x00200000
#define PHONEFEATURE_SETHOOKSWITCHHEADSET 0x00400000
#define PHONEFEATURE_SETRING         0x01000000
#define PHONEFEATURE_SETVOLUMEHANDSET 0x02000000
#define PHONEFEATURE_SETVOLUMESPEAKER 0x04000000
#define PHONEFEATURE_SETVOLUMEHEADSET 0x08000000

/* PHONEHOOKSWITCHDEV (ms895935) */
#define PHONEHOOKSWITCHDEV_HANDSET   0x00000001
#define PHONEHOOKSWITCHDEV_HEADSET   0x00000004
#define PHONEHOOKSWITCHDEV_SPEAKER   0x00000002

/* PHONEHOOKSWITCHMODE (ms895936) */
#define PHONEHOOKSWITCHMODE_MIC      0x00000002
#define PHONEHOOKSWITCHMODE_MICSPEAKER 0x00000008
#define PHONEHOOKSWITCHMODE_ONHOOK   0x00000001
#define PHONEHOOKSWITCHMODE_SPEAKER  0x00000004
#define PHONEHOOKSWITCHMODE_UNKNOWN  0x00000010

/* PHONEINITIALIZEEXOPTION (ms895938) */
#define PHONEINITIALIZEEXOPTION_USECOMPLETIONPORT 0x00000003
#define PHONEINITIALIZEEXOPTION_USEEVENT 0x00000002
#define PHONEINITIALIZEEXOPTION_USEHIDDENWINDOW 0x00000001

/* PHONELAMPMODE (ms895940) */
#define PHONELAMPMODE_DUMMY          0x00000001
#define PHONELAMPMODE_BROKENFLUTTER  0x00000040
#define PHONELAMPMODE_FLASH          0x00000010
#define PHONELAMPMODE_FLUTTER        0x00000020
#define PHONELAMPMODE_OFF            0x00000002
#define PHONELAMPMODE_STEADY         0x00000004
#define PHONELAMPMODE_UNKNOWN        0x00000080
#define PHONELAMPMODE_WINK           0x00000008

/* PHONEPRIVILEGE (ms895945) */
#define PHONEPRIVILEGE_MONITOR       0x00000001
#define PHONEPRIVILEGE_OWNER         0x00000002

/* PHONESTATE (ms896219) */
#define PHONESTATE_CAPSCHANGE        0x00400000
#define PHONESTATE_CONNECTED         0x00000002
#define PHONESTATE_DEVSPECIFIC       0x00100000
#define PHONESTATE_DISCONNECTED      0x00000004
#define PHONESTATE_DISPLAY           0x00000020
#define PHONESTATE_HANDSETGAIN       0x00000800
#define PHONESTATE_HANDSETHOOKSWITCH 0x00000200
#define PHONESTATE_HANDSETVOLUME     0x00000400
#define PHONESTATE_HEADSETHOOKSWITCH 0x00008000
#define PHONESTATE_HEADSETGAIN       0x00020000
#define PHONESTATE_HEADSETVOLUME     0x00010000
#define PHONESTATE_LAMP              0x00000040
#define PHONESTATE_MONITORS          0x00000010
#define PHONESTATE_OTHER             0x00000001
#define PHONESTATE_OWNER             0x00000008
#define PHONESTATE_REINIT            0x00200000
#define PHONESTATE_REMOVED           0x00800000
#define PHONESTATE_RESUME            0x00080000
#define PHONESTATE_RINGMODE          0x00000080
#define PHONESTATE_RINGVOLUME        0x00000100
#define PHONESTATE_SPEAKERHOOKSWITCH 0x00001000
#define PHONESTATE_SPEAKERGAIN       0x00004000
#define PHONESTATE_SPEAKERVOLUME     0x00002000
#define PHONESTATE_SUSPEND           0x00040000

/* PHONESTATUSFLAGS (ms896255) */
#define PHONESTATUSFLAGS_CONNECTED   0x00000001
#define PHONESTATUSFLAGS_SUSPENDED   0x00000002

/* ------------------------------------------------------------------ */
/* TAPI client functions (M45)                                         */
/*                                                                     */
/* Every prototype below is transcribed from its official CE 5.0      */
/* "Telephony API" function page (id in the trailing comment); every  */
/* page's Requirements rows read: Header: Tapi.h, Link Library:       */
/* Coredll.lib.  The CE 5.0 archive strips whitespace inside code     */
/* blocks; the type/name boundaries of the glued prototypes were      */
/* restored against the documented types above (the same mechanical   */
/* restoration documented for the TSPI batch, M43).  The pages print  */
/* `LONG WINAPI`; WINAPI is empty for CE (windef.h) and the           */
/* declarations follow the repository's single-convention style.      */
/* `const` qualifiers on structure-pointer parameters are printed by  */
/* the pages themselves.                                              */
/* ------------------------------------------------------------------ */

/* line initialization / shutdown                     */

AKARI_CE_IMPORT LONG lineInitialize(LPHLINEAPP lphLineApp,
    HINSTANCE hInstance, LINECALLBACK lpfnCallback,
    LPCWSTR lpszAppName, LPDWORD lpdwNumDevs)
    AKARI_CE_NAME(lineInitialize);                          /* ms894369, CE 1.0+  */
AKARI_CE_IMPORT LONG lineInitializeEx(LPHLINEAPP lphLineApp,
    HINSTANCE hInstance, LINECALLBACK lpfnCallback,
    LPCWSTR lpszFriendlyAppName, LPDWORD lpdwNumDevs,
    LPDWORD lpdwAPIVersion,
    LPLINEINITIALIZEEXPARAMS lpLineInitializeExParams)
    AKARI_CE_NAME(lineInitializeEx);                        /* ms894370, CE 3.0+  */
AKARI_CE_IMPORT LONG lineShutdown(HLINEAPP hLineApp)
    AKARI_CE_NAME(lineShutdown);                            /* ms894517, CE 1.0+  */
AKARI_CE_IMPORT LONG lineNegotiateAPIVersion(HLINEAPP hLineApp,
    DWORD dwDeviceID, DWORD dwAPILowVersion,
    DWORD dwAPIHighVersion, LPDWORD lpdwAPIVersion,
    LPLINEEXTENSIONID lpExtensionID)
    AKARI_CE_NAME(lineNegotiateAPIVersion);                 /* ms894402, CE 1.0+  */
AKARI_CE_IMPORT LONG lineNegotiateExtVersion(HLINEAPP hLineApp,
    DWORD dwDeviceID, DWORD dwAPIVersion,
    DWORD dwExtLowVersion, DWORD dwExtHighVersion,
    LPDWORD lpdwExtVersion)
    AKARI_CE_NAME(lineNegotiateExtVersion);                 /* ms894404, CE 1.0+  */
AKARI_CE_IMPORT LONG lineGetMessage(HLINEAPP hLineApp,
    LPLINEMESSAGE lpMessage, DWORD dwTimeout)
    AKARI_CE_NAME(lineGetMessage);                          /* ms894338, CE 3.0+  */
AKARI_CE_IMPORT LONG lineSetCurrentLocation(HLINEAPP hLineApp,
    DWORD dwLocation)
    AKARI_CE_NAME(lineSetCurrentLocation);                  /* ms894481, CE 2.10+ */
AKARI_CE_IMPORT LONG lineAddProvider(LPCWSTR lpszProviderFilename,
    HWND hwndOwner, LPDWORD lpdwPermanentProviderID)
    AKARI_CE_NAME(lineAddProvider);                         /* ms893340, CE 2.0+  */
AKARI_CE_IMPORT LONG lineGetProviderList(DWORD dwAPIVersion,
    LPLINEPROVIDERLIST lpProviderList)
    AKARI_CE_NAME(lineGetProviderList);                     /* ms894352, CE 1.0+  */

/* line device open / close / capabilities            */

AKARI_CE_IMPORT LONG lineOpen(HLINEAPP hLineApp, DWORD dwDeviceID,
    LPHLINE lphLine, DWORD dwAPIVersion, DWORD dwExtVersion,
    DWORD dwCallbackInstance, DWORD dwPrivileges,
    DWORD dwMediaModes, LPLINECALLPARAMS const lpCallParams)
    AKARI_CE_NAME(lineOpen);                                /* ms894420, CE 1.0+  */
AKARI_CE_IMPORT LONG lineClose(HLINE hLine)
    AKARI_CE_NAME(lineClose);                               /* ms894118, CE 1.0+  */
AKARI_CE_IMPORT LONG lineGetDevCaps(HLINEAPP hLineApp,
    DWORD dwDeviceID, DWORD dwAPIVersion, DWORD dwExtVersion,
    LPLINEDEVCAPS lpLineDevCaps)
    AKARI_CE_NAME(lineGetDevCaps);                          /* ms894165, CE 1.0+  */
AKARI_CE_IMPORT LONG lineGetLineDevStatus(HLINE hLine,
    LPLINEDEVSTATUS lpLineDevStatus)
    AKARI_CE_NAME(lineGetLineDevStatus);                    /* ms894336, CE 1.0+  */
AKARI_CE_IMPORT LONG lineGetAddressCaps(HLINEAPP hLineApp,
    DWORD dwDeviceID, DWORD dwAddressID, DWORD dwAPIVersion,
    DWORD dwExtVersion, LPLINEADDRESSCAPS lpAddressCaps)
    AKARI_CE_NAME(lineGetAddressCaps);                      /* ms894158, CE 1.0+  */
AKARI_CE_IMPORT LONG lineGetAddressStatus(HLINE hLine,
    DWORD dwAddressID, LPLINEADDRESSSTATUS lpAddressStatus)
    AKARI_CE_NAME(lineGetAddressStatus);                    /* ms894160, CE 1.0+  */
AKARI_CE_IMPORT LONG lineGetAddressID(HLINE hLine,
    LPDWORD lpdwAddressID, DWORD dwAddressMode,
    LPCWSTR lpsAddress, DWORD dwSize)
    AKARI_CE_NAME(lineGetAddressID);                        /* ms894159, CE 1.0+  */
AKARI_CE_IMPORT LONG lineGetID(HLINE hLine, DWORD dwAddressID,
    HCALL hCall, DWORD dwSelect, LPVARSTRING lpDeviceID,
    LPCWSTR lpszDeviceClass)
    AKARI_CE_NAME(lineGetID);                               /* ms894331, CE 1.0+  */
AKARI_CE_IMPORT LONG lineGetIcon(DWORD dwDeviceID,
    LPCWSTR lpszDeviceClass, LPHICON lphIcon)
    AKARI_CE_NAME(lineGetIcon);                             /* ms894313, CE 1.0+  */
AKARI_CE_IMPORT LONG lineGetStatusMessages(HLINE hLine,
    LPDWORD lpdwLineStates, LPDWORD lpdwAddressStates)
    AKARI_CE_NAME(lineGetStatusMessages);                   /* ms894356, CE 1.0+  */
AKARI_CE_IMPORT LONG lineSetStatusMessages(HLINE hLine,
    DWORD dwLineStates, DWORD dwAddressStates)
    AKARI_CE_NAME(lineSetStatusMessages);                   /* ms894500, CE 1.0+  */
AKARI_CE_IMPORT LONG lineGetNewCalls(HLINE hLine,
    DWORD dwAddressID, DWORD dwSelect,
    LPLINECALLLIST lpCallList)
    AKARI_CE_NAME(lineGetNewCalls);                         /* ms894341, CE 1.0+  */
AKARI_CE_IMPORT LONG lineGetNumRings(HLINE hLine,
    DWORD dwAddressID, LPDWORD lpdwNumRings)
    AKARI_CE_NAME(lineGetNumRings);                         /* ms894350, CE 1.0+  */
AKARI_CE_IMPORT LONG lineSetNumRings(HLINE hLine,
    DWORD dwAddressID, DWORD dwNumRings)
    AKARI_CE_NAME(lineSetNumRings);                         /* ms894494, CE 1.0+  */

/* call setup / control                               */

AKARI_CE_IMPORT LONG lineMakeCall(HLINE hLine, LPHCALL lphCall,
    LPCWSTR lpszDestAddress, DWORD dwCountryCode,
    LPLINECALLPARAMS const lpCallParams)
    AKARI_CE_NAME(lineMakeCall);                            /* ms894387, CE 1.0+  */
AKARI_CE_IMPORT LONG lineAnswer(HCALL hCall,
    LPCSTR lpsUserUserInfo, DWORD dwSize)
    AKARI_CE_NAME(lineAnswer);                              /* ms893395, CE 1.0+  */
AKARI_CE_IMPORT LONG lineAccept(HCALL hCall,
    LPCSTR lpsUserUserInfo, DWORD dwSize)
    AKARI_CE_NAME(lineAccept);                              /* ms893325, CE 1.0+  */
AKARI_CE_IMPORT LONG lineDeallocateCall(HCALL hCall)
    AKARI_CE_NAME(lineDeallocateCall);                      /* ms894128, CE 1.0+  */
AKARI_CE_IMPORT LONG lineDrop(HCALL hCall,
    LPCTSTR lpsUserUserInfo, DWORD dwSize)
    AKARI_CE_NAME(lineDrop);                                /* ms894142, CE 1.0+  */
AKARI_CE_IMPORT LONG lineDial(HCALL hCall,
    LPCWSTR lpszDestAddress, DWORD dwCountryCode)
    AKARI_CE_NAME(lineDial);                                /* ms894137, CE 1.0+  */
AKARI_CE_IMPORT LONG lineHold(HCALL hCall)
    AKARI_CE_NAME(lineHold);                                /* ms894368, CE 1.0+  */
AKARI_CE_IMPORT LONG lineUnhold(HCALL hCall)
    AKARI_CE_NAME(lineUnhold);                              /* ms894557, CE 1.0+  */
AKARI_CE_IMPORT LONG lineSwapHold(HCALL hActiveCall,
    HCALL hHeldCall)
    AKARI_CE_NAME(lineSwapHold);                            /* ms894522, CE 1.0+  */
AKARI_CE_IMPORT LONG linePickup(HLINE hLine, DWORD dwAddressID,
    LPHCALL lphCall, LPCSTR lpszDestAddress,
    LPCSTR lpszGroupID)
    AKARI_CE_NAME(linePickup);                              /* ms894423, CE 1.0+  */
AKARI_CE_IMPORT LONG lineRedirect(HCALL hCall,
    LPCSTR lpszDestAddress, DWORD dwCountryCode)
    AKARI_CE_NAME(lineRedirect);                            /* ms894435, CE 1.0+  */
AKARI_CE_IMPORT LONG lineForward(HLINE hLine, DWORD bAllAddresses,
    DWORD dwAddressID, LPLINEFORWARDLIST const lpForwardList,
    DWORD dwNumRingsNoAnswer, LPHCALL lphConsultCall,
    LPLINECALLPARAMS const lpCallParams)
    AKARI_CE_NAME(lineForward);                             /* ms894147, CE 1.0+  */
AKARI_CE_IMPORT LONG lineHandoff(HCALL hCall,
    LPCSTR lpszFileName, DWORD dwMediaMode)
    AKARI_CE_NAME(lineHandoff);                             /* ms894363, CE 1.0+  */

/* call information                                   */

AKARI_CE_IMPORT LONG lineGetCallInfo(HCALL hCall,
    LPLINECALLINFO lpCallInfo)
    AKARI_CE_NAME(lineGetCallInfo);                         /* ms894162, CE 1.0+  */
AKARI_CE_IMPORT LONG lineGetCallStatus(HCALL hCall,
    LPLINECALLSTATUS lpCallStatus)
    AKARI_CE_NAME(lineGetCallStatus);                       /* ms894163, CE 1.0+  */
AKARI_CE_IMPORT LONG lineGetConfRelatedCalls(HCALL hCall,
    LPLINECALLLIST lpCallList)
    AKARI_CE_NAME(lineGetConfRelatedCalls);                 /* ms894164, CE 1.0+  */
AKARI_CE_IMPORT LONG lineSetCallParams(HCALL hCall,
    DWORD dwBearerMode, DWORD dwMinRate, DWORD dwMaxRate,
    LPLINEDIALPARAMS const lpDialParams)
    AKARI_CE_NAME(lineSetCallParams);                       /* ms894473, CE 1.0+  */
AKARI_CE_IMPORT LONG lineSetCallPrivilege(HCALL hCall,
    DWORD dwCallPrivilege)
    AKARI_CE_NAME(lineSetCallPrivilege);                    /* ms894475, CE 1.0+  */
AKARI_CE_IMPORT LONG lineSetMediaMode(HCALL hCall,
    DWORD dwMediaModes)
    AKARI_CE_NAME(lineSetMediaMode);                        /* ms894491, CE 1.0+  */
AKARI_CE_IMPORT LONG lineSetTerminal(HLINE hLine,
    DWORD dwAddressID, HCALL hCall, DWORD dwSelect,
    DWORD dwTerminalModes, DWORD dwTerminalID, DWORD bEnable)
    AKARI_CE_NAME(lineSetTerminal);                         /* ms894505, CE 1.0+  */
AKARI_CE_IMPORT LONG lineMonitorDigits(HCALL hCall,
    DWORD dwDigitModes)
    AKARI_CE_NAME(lineMonitorDigits);                       /* ms894391, CE 1.0+  */
AKARI_CE_IMPORT LONG lineMonitorMedia(HCALL hCall,
    DWORD dwMediaModes)
    AKARI_CE_NAME(lineMonitorMedia);                        /* ms894395, CE 1.0+  */
AKARI_CE_IMPORT LONG lineGenerateDigits(HCALL hCall,
    DWORD dwDigitMode, LPCWSTR lpszDigits, DWORD dwDuration)
    AKARI_CE_NAME(lineGenerateDigits);                      /* ms894152, CE 1.0+  */
AKARI_CE_IMPORT LONG lineGenerateTone(HCALL hCall,
    DWORD dwToneMode, DWORD dwDuration, DWORD dwNumTones,
    LPLINEGENERATETONE const lpTones)
    AKARI_CE_NAME(lineGenerateTone);                        /* ms894156, CE 1.0+  */
AKARI_CE_IMPORT LONG lineSendUserUserInfo(HCALL hCall,
    LPCSTR lpsUserUserInfo, DWORD dwSize)
    AKARI_CE_NAME(lineSendUserUserInfo);                    /* ms894466, CE 3.0+  */
AKARI_CE_IMPORT LONG lineReleaseUserUserInfo(HCALL hCall)
    AKARI_CE_NAME(lineReleaseUserUserInfo);                 /* ms894438, CE 1.0+  */
AKARI_CE_IMPORT LONG lineDevSpecific(HLINE hLine,
    DWORD dwAddressID, HCALL hCall, LPVOID lpParams,
    DWORD dwSize)
    AKARI_CE_NAME(lineDevSpecific);                         /* ms894131, CE 1.0+  */

/* conference and transfer                            */

AKARI_CE_IMPORT LONG lineAddToConference(HCALL hConfCall,
    HCALL hConsultCall)
    AKARI_CE_NAME(lineAddToConference);                     /* ms893390, CE 1.0+  */
AKARI_CE_IMPORT LONG lineRemoveFromConference(HCALL hCall)
    AKARI_CE_NAME(lineRemoveFromConference);                /* ms894452, CE 1.0+  */
AKARI_CE_IMPORT LONG lineSetupConference(HCALL hCall,
    HLINE hLine, LPHCALL lphConfCall, LPHCALL lphConsultCall,
    DWORD dwNumParties, LPLINECALLPARAMS const lpCallParams)
    AKARI_CE_NAME(lineSetupConference);                     /* ms894512, CE 1.0+  */
AKARI_CE_IMPORT LONG linePrepareAddToConference(HCALL hConfCall,
    LPHCALL lphConsultCall,
    LPLINECALLPARAMS const lpCallParams)
    AKARI_CE_NAME(linePrepareAddToConference);              /* ms894429, CE 1.0+  */
AKARI_CE_IMPORT LONG lineSetupTransfer(HCALL hCall,
    LPHCALL lphConsultCall,
    LPLINECALLPARAMS const lpCallParams)
    AKARI_CE_NAME(lineSetupTransfer);                       /* ms894514, CE 1.0+  */
AKARI_CE_IMPORT LONG lineCompleteTransfer(HCALL hCall,
    HCALL hConsultCall, LPHCALL lphConfCall,
    DWORD dwTransferMode)
    AKARI_CE_NAME(lineCompleteTransfer);                    /* ms894122, CE 1.0+  */
AKARI_CE_IMPORT LONG lineBlindTransfer(HCALL hCall,
    LPCWSTR lpszDestAddress, DWORD dwCountryCode)
    AKARI_CE_NAME(lineBlindTransfer);                       /* ms893412, CE 1.0+  */

/* device configuration / translation / priority      */

AKARI_CE_IMPORT LONG lineGetDevConfig(DWORD dwDeviceID,
    LPVARSTRING lpDeviceConfig, LPCSTR lpszDeviceClass)
    AKARI_CE_NAME(lineGetDevConfig);                        /* ms894177, CE 1.0+  */
AKARI_CE_IMPORT LONG lineSetDevConfig(DWORD dwDeviceID,
    LPVOID const lpDeviceConfig, DWORD dwSize,
    LPCTSTR lpszDeviceClass)
    AKARI_CE_NAME(lineSetDevConfig);                        /* ms894488, CE 1.0+  */
AKARI_CE_IMPORT LONG lineConfigDialogEdit(DWORD dwDeviceID,
    HWND hwndOwner, LPCWSTR lpszDeviceClass,
    LPVOID const lpDeviceConfigIn, DWORD dwSize,
    LPVARSTRING lpDeviceConfigOut)
    AKARI_CE_NAME(lineConfigDialogEdit);                    /* ms894123, CE 1.0+  */
AKARI_CE_IMPORT LONG lineGetTranslateCaps(HLINEAPP hLineApp,
    DWORD dwAPIVersion, LPLINETRANSLATECAPS lpTranslateCaps)
    AKARI_CE_NAME(lineGetTranslateCaps);                    /* ms894361, CE 1.0+  */
AKARI_CE_IMPORT LONG lineTranslateAddress(HLINEAPP hLineApp,
    DWORD dwDeviceID, DWORD dwAPIVersion, LPCWSTR lpszAddressIn,
    DWORD dwCard, DWORD dwTranslateOptions,
    LPLINETRANSLATEOUTPUT lpTranslateOutput)
    AKARI_CE_NAME(lineTranslateAddress);                    /* ms894539, CE 1.0+  */
AKARI_CE_IMPORT LONG lineTranslateDialog(HLINEAPP hLineApp,
    DWORD dwDeviceID, DWORD dwAPIVersion, HWND hwndOwner,
    LPCWSTR lpszAddressIn)
    AKARI_CE_NAME(lineTranslateDialog);                     /* ms894543, CE 1.0+  */
AKARI_CE_IMPORT LONG lineSetTollList(HLINEAPP hLineApp,
    DWORD dwDeviceID, LPCWSTR lpszAddressIn,
    DWORD dwTollListOption)
    AKARI_CE_NAME(lineSetTollList);                         /* ms894509, CE .NET 4.0+ */
AKARI_CE_IMPORT LONG lineGetAppPriority(LPCWSTR lpszAppFilename,
    DWORD dwMediaMode, LPLINEEXTENSIONID lpExtensionID,
    DWORD dwRequestMode, LPVARSTRING lpExtensionName,
    LPDWORD lpdwPriority)
    AKARI_CE_NAME(lineGetAppPriority);                      /* ms894161, CE 1.0+  */
AKARI_CE_IMPORT LONG lineSetAppPriority(LPCSTR lpszAppFilename,
    DWORD dwMediaMode, LPLINEEXTENSIONID lpExtensionID,
    DWORD dwRequestMode, LPCSTR lpszExtensionName,
    DWORD dwPriority)
    AKARI_CE_NAME(lineSetAppPriority);                      /* ms894470, CE 1.0+  */

/* phone device functions                             */

AKARI_CE_IMPORT LONG phoneInitializeEx(LPHPHONEAPP lphPhoneApp,
    HINSTANCE hInstance, PHONECALLBACK lpfnCallback,
    LPCWSTR lpszFriendlyAppName, LPDWORD lpdwNumDevs,
    LPDWORD lpdwAPIVersion,
    LPPHONEINITIALIZEEXPARAMS lpPhoneInitializeExParams)
    AKARI_CE_NAME(phoneInitializeEx);                       /* ms895937, CE 3.0+  */
AKARI_CE_IMPORT LONG phoneShutdown(HPHONEAPP hPhoneApp)
    AKARI_CE_NAME(phoneShutdown);                           /* ms896208, CE 3.0+  */
AKARI_CE_IMPORT LONG phoneOpen(HPHONEAPP hPhoneApp,
    DWORD dwDeviceID, LPHPHONE lphPhone, DWORD dwAPIVersion,
    DWORD dwExtVersion, DWORD_PTR dwCallbackInstance,
    DWORD dwPrivilege)
    AKARI_CE_NAME(phoneOpen);                               /* ms895944, CE 3.0+  */
AKARI_CE_IMPORT LONG phoneClose(HPHONE hPhone)
    AKARI_CE_NAME(phoneClose);                              /* ms895912, CE 3.0+  */
AKARI_CE_IMPORT LONG phoneNegotiateAPIVersion(HPHONEAPP hPhoneApp,
    DWORD dwDeviceID, DWORD dwAPILowVersion,
    DWORD dwAPIHighVersion, LPDWORD lpdwAPIVersion,
    LPPHONEEXTENSIONID lpExtensionID)
    AKARI_CE_NAME(phoneNegotiateAPIVersion);                /* ms895942, CE 3.0+  */
AKARI_CE_IMPORT LONG phoneNegotiateExtVersion(HPHONEAPP hPhoneApp,
    DWORD dwDeviceID, DWORD dwAPIVersion,
    DWORD dwExtLowVersion, DWORD dwExtHighVersion,
    LPDWORD lpdwExtVersion)
    AKARI_CE_NAME(phoneNegotiateExtVersion);                /* ms895943, CE 3.0+  */
AKARI_CE_IMPORT LONG phoneGetMessage(HPHONEAPP hPhoneApp,
    LPPHONEMESSAGE lpMessage, DWORD dwTimeout)
    AKARI_CE_NAME(phoneGetMessage);                         /* ms895930, CE 3.0+  */
AKARI_CE_IMPORT LONG phoneGetDevCaps(HPHONEAPP hPhoneApp,
    DWORD dwDeviceID, DWORD dwAPIVersion, DWORD dwExtVersion,
    LPPHONECAPS lpPhoneCaps)
    AKARI_CE_NAME(phoneGetDevCaps);                         /* ms895925, CE 3.0+  */
AKARI_CE_IMPORT LONG phoneGetStatus(HPHONE hPhone,
    LPPHONESTATUS lpPhoneStatus)
    AKARI_CE_NAME(phoneGetStatus);                          /* ms895932, CE 3.0+  */
AKARI_CE_IMPORT LONG phoneGetGain(HPHONE hPhone,
    DWORD dwHookSwitchDev, LPDWORD lpdwGain)
    AKARI_CE_NAME(phoneGetGain);                            /* ms895926, CE 3.0+  */
AKARI_CE_IMPORT LONG phoneSetGain(HPHONE hPhone,
    DWORD dwHookSwitchDev, DWORD dwGain)
    AKARI_CE_NAME(phoneSetGain);                            /* ms896179, CE 3.0+  */
AKARI_CE_IMPORT LONG phoneGetVolume(HPHONE hPhone,
    DWORD dwHookSwitchDev, LPDWORD lpdwVolume)
    AKARI_CE_NAME(phoneGetVolume);                          /* ms895934, CE 3.0+  */
AKARI_CE_IMPORT LONG phoneSetVolume(HPHONE hPhone,
    DWORD dwHookSwitchDev, DWORD dwVolume)
    AKARI_CE_NAME(phoneSetVolume);                          /* ms896201, CE 3.0+  */
AKARI_CE_IMPORT LONG phoneGetHookSwitch(HPHONE hPhone,
    LPDWORD lpdwHookSwitchDevs)
    AKARI_CE_NAME(phoneGetHookSwitch);                      /* ms895927, CE 3.0+  */
AKARI_CE_IMPORT LONG phoneSetHookSwitch(HPHONE hPhone,
    DWORD dwHookSwitchDevs, DWORD dwHookSwitchMode)
    AKARI_CE_NAME(phoneSetHookSwitch);                      /* ms896185, CE 3.0+  */
AKARI_CE_IMPORT LONG phoneGetRing(HPHONE hPhone,
    LPDWORD lpdwRingMode, LPDWORD lpdwVolume)
    AKARI_CE_NAME(phoneGetRing);                            /* ms895931, CE 3.0+  */
AKARI_CE_IMPORT LONG phoneSetRing(HPHONE hPhone, DWORD dwRingMode,
    DWORD dwVolume)
    AKARI_CE_NAME(phoneSetRing);                            /* ms896190, CE 3.0+  */
AKARI_CE_IMPORT LONG phoneGetStatusMessages(HPHONE hPhone,
    LPDWORD lpdwPhoneStates, LPDWORD lpdwButtonModes,
    LPDWORD lpdwButtonStates)
    AKARI_CE_NAME(phoneGetStatusMessages);                  /* ms895933, CE 3.0+  */
AKARI_CE_IMPORT LONG phoneSetStatusMessages(HPHONE hPhone,
    DWORD dwPhoneStates, DWORD dwButtonModes,
    DWORD dwButtonStates)
    AKARI_CE_NAME(phoneSetStatusMessages);                  /* ms896197, CE 3.0+  */
AKARI_CE_IMPORT LONG phoneGetIcon(DWORD dwDeviceID,
    LPCWSTR lpszDeviceClass, LPHICON lphIcon)
    AKARI_CE_NAME(phoneGetIcon);                            /* ms895928, CE 3.0+  */
AKARI_CE_IMPORT LONG phoneGetID(HPHONE hPhone,
    LPVARSTRING lpDeviceID, LPCWSTR lpszDeviceClass)
    AKARI_CE_NAME(phoneGetID);                              /* ms895929, CE 3.0+  */
AKARI_CE_IMPORT LONG phoneConfigDialog(DWORD dwDeviceID,
    HWND hwndOwner, LPCSTR lpszDeviceClass)
    AKARI_CE_NAME(phoneConfigDialog);                       /* ms895915, CE 3.0+  */
AKARI_CE_IMPORT LONG phoneDevSpecific(HPHONE hPhone,
    LPVOID lpParams, DWORD dwSize)
    AKARI_CE_NAME(phoneDevSpecific);                        /* ms895918, CE 3.0+  */

/* ------------------------------------------------------------------
 * Book surface: tapi-structures-constants (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ------------------------------------------------------------------
 * Book surface: tapi-structures-constants (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms885284 The LINECALLINFO Data Structure */
/* ------------------------------------------------------------------
 * Book surface: tspi-all (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ------------------------------------------------------------------
 * Book surface: tapi-structures-constants (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms894406 LINE_NEWCALL: value adopted at the M99 three-generation sweep -- R1 ddk/ndistapi.h: #define LINE_NEWCALL TSPI_MESSAGE_BASE -- the TAPI line-event message numbering (the TSPI-side new-call notification, value TSPI_MESSAGE_BASE = 500; the CE page ms894406 describes the service-provider-to-TAPI direction; the application-side counterpart is LINE_APPNEWCALL). */
#define LINE_NEWCALL                        500
/* ms894385 LINELOCATIONOPTION: documented name-only (no value published; held) */
/* ------------------------------------------------------------------
 * Book surface: tapi-structures-constants (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms885284 The LINECALLINFO Data Structure */
/* ------------------------------------------------------------------
 * Book surface: tspi-all (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms893374 LINE_ADDRESSSTATE: value adopted at the M99 three-generation sweep -- R1 ddk/ndistapi.h: #define LINE_ADDRESSSTATE 0L -- the TAPI line-event message numbering. */
#define LINE_ADDRESSSTATE                   0
/* ms893651 LINE_CALLINFO: value adopted at the M99 three-generation sweep -- R1 ddk/ndistapi.h: #define LINE_CALLINFO 1L -- the TAPI line-event message numbering. */
#define LINE_CALLINFO                       1
/* ms894004 LINE_CALLSTATE: value adopted at the M99 three-generation sweep -- R1 ddk/ndistapi.h: #define LINE_CALLSTATE 2L -- the TAPI line-event message numbering. */
#define LINE_CALLSTATE                      2
/* ms894120 LINE_CLOSE: value adopted at the M99 three-generation sweep -- R1 ddk/ndistapi.h: #define LINE_CLOSE 3L -- the TAPI line-event message numbering. */
#define LINE_CLOSE                          3
/* ms894127 LINE_CREATE: value adopted at the M99 three-generation sweep -- R1 ddk/ndistapi.h: #define LINE_CREATE 19L -- the TAPI line-event message numbering. */
#define LINE_CREATE                         19
/* ms894133 LINE_DEVSPECIFIC: value adopted at the M99 three-generation sweep -- R1 ddk/ndistapi.h: #define LINE_DEVSPECIFIC 4L -- the TAPI line-event message numbering. */
#define LINE_DEVSPECIFIC                    4
/* ms894157 LINE_GENERATE: value adopted at the M99 three-generation sweep -- R1 ddk/ndistapi.h: #define LINE_GENERATE 7L -- the TAPI line-event message numbering. */
#define LINE_GENERATE                       7
/* ms894381 LINE_LINEDEVSTATE: value adopted at the M99 three-generation sweep -- R1 ddk/ndistapi.h: #define LINE_LINEDEVSTATE 8L -- the TAPI line-event message numbering. */
#define LINE_LINEDEVSTATE                   8
/* ms894393 LINE_MONITORDIGITS: value adopted at the M99 three-generation sweep -- R1 ddk/ndistapi.h: #define LINE_MONITORDIGITS 9L -- the TAPI line-event message numbering. */
#define LINE_MONITORDIGITS                  9
/* ms894399 LINE_MONITORMEDIA: value adopted at the M99 three-generation sweep -- R1 ddk/ndistapi.h: #define LINE_MONITORMEDIA 10L -- the TAPI line-event message numbering. */
#define LINE_MONITORMEDIA                   10
/* ms894457 LINE_REMOVE: value adopted at the M99 three-generation sweep -- R1 ddk/ndistapi.h: #define LINE_REMOVE 25L -- the TAPI line-event message numbering. */
#define LINE_REMOVE                         25
/* ms895909 PHONE_BUTTON: documented name-only (no value published; held) */
/* ms895914 PHONE_CLOSE: documented name-only (no value published; held) */
/* ms895917 PHONE_CREATE: documented name-only (no value published; held) */
/* ms895920 PHONE_DEVSPECIFIC: documented name-only (no value published; held) */
/* ms895947 PHONE_REMOVE: documented name-only (no value published; held) */
/* ms896240 PHONE_STATE: documented name-only (no value published; held) */
#endif /* _TAPI_H */
