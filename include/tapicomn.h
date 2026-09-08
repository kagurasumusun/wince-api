/* tapicomn.h -- Telephony Service Provider Interface (TSPI) functions
 * for Windows CE.
 *
 * Evidence model (clean room; same as winsock2.h / tapi.h):
 *
 *  (a) every prototype is transcribed from the official CE 5.0 "TSPI
 *      Reference" function pages: 52 TSPI_line* pages (aa451008..
 *      aa451095), 21 TSPI_phone* pages (aa451096..aa451126) and 8
 *      TSPI_provider* pages (aa451127..aa451134).  Every function
 *      page's Requirements rows state: Header: Tapicomn.h, Link
 *      Library: Coredll.lib, OS: Windows CE 3.0 and later (the
 *      per-page records are docs/inventory.md, M43 section).
 *
 *  (b) the CE 5.0 archive strips whitespace inside the code blocks;
 *      the type/name boundaries in the parameter lists are restored
 *      against the documented types of tapi.h (no CE page needs the
 *      documented CE 6.0 twin procedure).
 *
 *  (c) recorded-not-defined: TSPI_lineSetCurrentLocation ("This
 *      function is obsolete" -- no prototype printed) and
 *      TSPI_lineConditionalMediaDetection (the archive prototype is
 *      corrupted beyond unambiguous restoration:
 *      "(HDRVLINEhdLine,hdConsultCalldwMediaModes,hdConsultCallconst
 *      lpCallParams)").  TSPI_lineForward was held in M43 for the
 *      unpublished LINEFORWARD element layout; it is declared in M45
 *      through the opaque LPLINEFORWARDLIST pointer (tapi.h note
 *      (e)).  docs/inventory.md (M43/M45) records each.
 */

#ifndef _TAPICOMN_H
#define _TAPICOMN_H

#include "tapi.h"   /* TAPI types, structures, TSPIAPI, callback types */

/* ------------------------------------------------------------------ */
/* TSPI line device functions                         */
/* ------------------------------------------------------------------ */

AKARI_CE_IMPORT LONG TSPI_lineAccept(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall,
    LPCSTR lpsUserUserInfo,
    DWORD dwSize)
    AKARI_CE_NAME(TSPI_lineAccept);

AKARI_CE_IMPORT LONG TSPI_lineAddToConference(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdConfCall,
    HDRVCALL hdConsultCall)
    AKARI_CE_NAME(TSPI_lineAddToConference);

AKARI_CE_IMPORT LONG TSPI_lineAnswer(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall,
    LPCSTR lpsUserUserInfo,
    DWORD dwSize)
    AKARI_CE_NAME(TSPI_lineAnswer);

AKARI_CE_IMPORT LONG TSPI_lineBlindTransfer(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall,
    LPCWSTR lpszDestAddress,
    DWORD dwCountryCode)
    AKARI_CE_NAME(TSPI_lineBlindTransfer);

AKARI_CE_IMPORT LONG TSPI_lineClose(
    HDRVLINE hdLine)
    AKARI_CE_NAME(TSPI_lineClose);

AKARI_CE_IMPORT LONG TSPI_lineCloseCall(
    HDRVCALL hdCall)
    AKARI_CE_NAME(TSPI_lineCloseCall);

AKARI_CE_IMPORT LONG TSPI_lineCompleteTransfer(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall,
    HDRVCALL hdConsultCall,
    HTAPICALL htConfCall,
    LPHDRVCALL lphdConfCall,
    DWORD dwTransferMode)
    AKARI_CE_NAME(TSPI_lineCompleteTransfer);

AKARI_CE_IMPORT LONG TSPI_lineConfigDialogEdit(
    DWORD dwDeviceID,
    HWND hwndOwner,
    LPCWSTR lpszDeviceClass,
    LPVOID const lpDeviceConfigIn,
    DWORD dwSize,
    LPVARSTRING lpDeviceConfigOut)
    AKARI_CE_NAME(TSPI_lineConfigDialogEdit);

AKARI_CE_IMPORT LONG TSPI_lineDevSpecific(
    DRV_REQUESTID dwRequestID,
    HDRVLINE hdLine,
    DWORD dwAddressID,
    HDRVCALL hdCall,
    LPVOID lpParams,
    DWORD dwSize)
    AKARI_CE_NAME(TSPI_lineDevSpecific);

AKARI_CE_IMPORT LONG TSPI_lineDial(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall,
    LPCWSTR lpszDestAddress,
    DWORD dwCountryCode)
    AKARI_CE_NAME(TSPI_lineDial);

AKARI_CE_IMPORT LONG TSPI_lineDrop(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall,
    LPCSTR lpsUserUserInfo,
    DWORD dwSize)
    AKARI_CE_NAME(TSPI_lineDrop);

/* M45: the M43 hold is resolved -- the LPLINEFORWARDLIST parameter
 * is declared as an opaque pointer (tapi.h note (e)), which is all
 * the prototype needs.  Prototype restored from the glued archive
 * print of page aa451032 against the documented tapi.h types. */
AKARI_CE_IMPORT LONG TSPI_lineForward(
    DRV_REQUESTID dwRequestID,
    HDRVLINE hdLine,
    DWORD bAllAddresses,
    DWORD dwAddressID,
    LPLINEFORWARDLIST const lpForwardList,
    DWORD dwNumRingsNoAnswer,
    HTAPICALL htConsultCall,
    LPHDRVCALL lphdConsultCall,
    LPLINECALLPARAMS const lpCallParams)
    AKARI_CE_NAME(TSPI_lineForward);

AKARI_CE_IMPORT LONG TSPI_lineGenerateDigits(
    HDRVCALL hdCall,
    DWORD dwEndToEndID,
    DWORD dwDigitMode,
    LPCWSTR lpszDigits,
    DWORD dwDuration)
    AKARI_CE_NAME(TSPI_lineGenerateDigits);

AKARI_CE_IMPORT LONG TSPI_lineGenerateTone(
    HDRVCALL hdCall,
    DWORD dwEndToEndID,
    DWORD dwToneMode,
    DWORD dwDuration,
    DWORD dwNumTones,
    LPLINEGENERATETONE const lpTones)
    AKARI_CE_NAME(TSPI_lineGenerateTone);

AKARI_CE_IMPORT LONG TSPI_lineGetAddressCaps(
    DWORD dwDeviceID,
    DWORD dwAddressID,
    DWORD dwTSPIVersion,
    DWORD dwExtVersion,
    LPLINEADDRESSCAPS lpAddressCaps)
    AKARI_CE_NAME(TSPI_lineGetAddressCaps);

AKARI_CE_IMPORT LONG TSPI_lineGetAddressID(
    HDRVLINE hdLine,
    LPDWORD lpdwAddressID,
    DWORD dwAddressMode,
    LPCWSTR lpsAddress,
    DWORD dwSize)
    AKARI_CE_NAME(TSPI_lineGetAddressID);

AKARI_CE_IMPORT LONG TSPI_lineGetAddressStatus(
    HDRVLINE hdLine,
    DWORD dwAddressID,
    LPLINEADDRESSSTATUS lpAddressStatus)
    AKARI_CE_NAME(TSPI_lineGetAddressStatus);

AKARI_CE_IMPORT LONG TSPI_lineGetCallAddressID(
    HDRVCALL hdCall,
    LPDWORD lpdwAddressID)
    AKARI_CE_NAME(TSPI_lineGetCallAddressID);

AKARI_CE_IMPORT LONG TSPI_lineGetCallInfo(
    HDRVCALL hdCall,
    LPLINECALLINFO lpCallInfo)
    AKARI_CE_NAME(TSPI_lineGetCallInfo);

AKARI_CE_IMPORT LONG TSPI_lineGetCallStatus(
    HDRVCALL hdCall,
    LPLINECALLSTATUS lpCallStatus)
    AKARI_CE_NAME(TSPI_lineGetCallStatus);

AKARI_CE_IMPORT LONG TSPI_lineGetDevCaps(
    DWORD dwDeviceID,
    DWORD dwTSPIVersion,
    DWORD dwExtVersion,
    LPLINEDEVCAPS lpLineDevCaps)
    AKARI_CE_NAME(TSPI_lineGetDevCaps);

AKARI_CE_IMPORT LONG TSPI_lineGetDevConfig(
    DWORD dwDeviceID,
    LPVARSTRING lpDeviceConfig,
    LPCWSTR lpszDeviceClass)
    AKARI_CE_NAME(TSPI_lineGetDevConfig);

AKARI_CE_IMPORT LONG TSPI_lineGetExtensionID(
    DWORD dwDeviceID,
    DWORD dwTSPIVersion,
    LPLINEEXTENSIONID lpExtensionID)
    AKARI_CE_NAME(TSPI_lineGetExtensionID);

AKARI_CE_IMPORT LONG TSPI_lineGetIcon(
    DWORD dwDeviceID,
    LPCWSTR lpszDeviceClass,
    LPHICON lphIcon)
    AKARI_CE_NAME(TSPI_lineGetIcon);

AKARI_CE_IMPORT LONG TSPI_lineGetID(
    HDRVLINE hdLine,
    DWORD dwAddressID,
    HDRVCALL hdCall,
    DWORD dwSelect,
    LPVARSTRING lpDeviceID,
    LPCWSTR lpszDeviceClass,
    HANDLE hTargetProcess)
    AKARI_CE_NAME(TSPI_lineGetID);

AKARI_CE_IMPORT LONG TSPI_lineGetLineDevStatus(
    HDRVLINE hdLine,
    LPLINEDEVSTATUS lpLineDevStatus)
    AKARI_CE_NAME(TSPI_lineGetLineDevStatus);

AKARI_CE_IMPORT LONG TSPI_lineGetNumAddressIDs(
    HDRVLINE hdLine,
    LPDWORD lpdwNumAddressIDs)
    AKARI_CE_NAME(TSPI_lineGetNumAddressIDs);

AKARI_CE_IMPORT LONG TSPI_lineHold(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall)
    AKARI_CE_NAME(TSPI_lineHold);

AKARI_CE_IMPORT LONG TSPI_lineMakeCall(
    DRV_REQUESTID dwRequestID,
    HDRVLINE hdLine,
    HTAPICALL htCall,
    LPHDRVCALL lphdCall,
    LPCWSTR lpszDestAddress,
    DWORD dwCountryCode,
    LPLINECALLPARAMS const lpCallParams)
    AKARI_CE_NAME(TSPI_lineMakeCall);

AKARI_CE_IMPORT LONG TSPI_lineMonitorDigits(
    HDRVCALL hdCall,
    DWORD dwDigitModes)
    AKARI_CE_NAME(TSPI_lineMonitorDigits);

AKARI_CE_IMPORT LONG TSPI_lineMonitorMedia(
    HDRVCALL hdCall,
    DWORD dwMediaModes)
    AKARI_CE_NAME(TSPI_lineMonitorMedia);

AKARI_CE_IMPORT LONG TSPI_lineNegotiateExtVersion(
    DWORD dwDeviceID,
    DWORD dwTSPIVersion,
    DWORD dwLowVersion,
    DWORD dwHighVersion,
    LPDWORD lpdwExtVersion)
    AKARI_CE_NAME(TSPI_lineNegotiateExtVersion);

AKARI_CE_IMPORT LONG TSPI_lineNegotiateTSPIVersion(
    DWORD dwDeviceID,
    DWORD dwLowVersion,
    DWORD dwHighVersion,
    LPDWORD lpdwTSPIVersion)
    AKARI_CE_NAME(TSPI_lineNegotiateTSPIVersion);

AKARI_CE_IMPORT LONG TSPI_lineOpen(
    DWORD dwDeviceID,
    HTAPILINE htLine,
    LPHDRVLINE lphdLine,
    DWORD dwTSPIVersion,
    LINEEVENT lpfnEventProc)
    AKARI_CE_NAME(TSPI_lineOpen);

AKARI_CE_IMPORT LONG TSPI_linePickup(
    DRV_REQUESTID dwRequestID,
    HDRVLINE hdLine,
    DWORD dwAddressID,
    HTAPICALL htCall,
    LPHDRVCALL lphdCall,
    LPCWSTR lpszDestAddress,
    LPCWSTR lpszGroupID)
    AKARI_CE_NAME(TSPI_linePickup);

AKARI_CE_IMPORT LONG TSPI_linePrepareAddToConference(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdConfCall,
    HTAPICALL htConsultCall,
    LPHDRVCALL lphdConsultCall,
    LPLINECALLPARAMS const lpCallParams)
    AKARI_CE_NAME(TSPI_linePrepareAddToConference);

AKARI_CE_IMPORT LONG TSPI_lineRedirect(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall,
    LPCWSTR lpszDestAddress,
    DWORD dwCountryCode)
    AKARI_CE_NAME(TSPI_lineRedirect);

AKARI_CE_IMPORT LONG TSPI_lineReleaseUserUserInfo(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall)
    AKARI_CE_NAME(TSPI_lineReleaseUserUserInfo);

AKARI_CE_IMPORT LONG TSPI_lineRemoveFromConference(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall)
    AKARI_CE_NAME(TSPI_lineRemoveFromConference);

AKARI_CE_IMPORT LONG TSPI_lineSendUserUserInfo(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall,
    LPCSTR lpsUserUserInfo,
    DWORD dwSize)
    AKARI_CE_NAME(TSPI_lineSendUserUserInfo);

AKARI_CE_IMPORT LONG TSPI_lineSetCallParams(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall,
    DWORD dwBearerMode,
    DWORD dwMinRate,
    DWORD dwMaxRate,
    LPLINEDIALPARAMS const lpDialParams)
    AKARI_CE_NAME(TSPI_lineSetCallParams);

AKARI_CE_IMPORT LONG TSPI_lineSetDefaultMediaDetection(
    HDRVLINE hdLine,
    DWORD dwMediaModes)
    AKARI_CE_NAME(TSPI_lineSetDefaultMediaDetection);

AKARI_CE_IMPORT LONG TSPI_lineSetDevConfig(
    DWORD dwDeviceID,
    LPVOID const lpDeviceConfig,
    DWORD dwSize,
    LPCWSTR lpszDeviceClass)
    AKARI_CE_NAME(TSPI_lineSetDevConfig);

AKARI_CE_IMPORT LONG TSPI_lineSetMediaMode(
    HDRVCALL hdCall,
    DWORD dwMediaMode)
    AKARI_CE_NAME(TSPI_lineSetMediaMode);

AKARI_CE_IMPORT LONG TSPI_lineSetStatusMessages(
    HDRVLINE hdLine,
    DWORD dwLineStates,
    DWORD dwAddressStates)
    AKARI_CE_NAME(TSPI_lineSetStatusMessages);

AKARI_CE_IMPORT LONG TSPI_lineSetTerminal(
    DRV_REQUESTID dwRequestID,
    HDRVLINE hdLine,
    DWORD dwAddressID,
    HDRVCALL hdCall,
    DWORD dwSelect,
    DWORD dwTerminalModes,
    DWORD dwTerminalID,
    DWORD bEnable)
    AKARI_CE_NAME(TSPI_lineSetTerminal);

AKARI_CE_IMPORT LONG TSPI_lineSetupConference(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall,
    HDRVLINE hdLine,
    HTAPICALL htConfCall,
    LPHDRVCALL lphdConfCall,
    HTAPICALL htConsultCall,
    LPHDRVCALL lphdConsultCall,
    DWORD dwNumParties,
    LPLINECALLPARAMS const lpCallParams)
    AKARI_CE_NAME(TSPI_lineSetupConference);

AKARI_CE_IMPORT LONG TSPI_lineSetupTransfer(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall,
    HTAPICALL htConsultCall,
    LPHDRVCALL lphdConsultCall,
    LPLINECALLPARAMS const lpCallParams)
    AKARI_CE_NAME(TSPI_lineSetupTransfer);

AKARI_CE_IMPORT LONG TSPI_lineSwapHold(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdActiveCall,
    HDRVCALL hdHeldCall)
    AKARI_CE_NAME(TSPI_lineSwapHold);

AKARI_CE_IMPORT LONG TSPI_lineUnhold(
    DRV_REQUESTID dwRequestID,
    HDRVCALL hdCall)
    AKARI_CE_NAME(TSPI_lineUnhold);

/* ------------------------------------------------------------------ */
/* TSPI phone device functions                        */
/* ------------------------------------------------------------------ */

AKARI_CE_IMPORT long TSPI_phoneClose(
    HDRVPHONE hdPhone)
    AKARI_CE_NAME(TSPI_phoneClose);

AKARI_CE_IMPORT LONG TSPI_phoneConfigDialog(
    DWORD dwDeviceID,
    HWND hwndOwner,
    LPCWSTR lpszDeviceClass)
    AKARI_CE_NAME(TSPI_phoneConfigDialog);

AKARI_CE_IMPORT LONG TSPI_phoneDevSpecific(
    DRV_REQUESTID dwRequestID,
    HDRVPHONE hdPhone,
    LPVOID lpParams,
    DWORD dwSize)
    AKARI_CE_NAME(TSPI_phoneDevSpecific);

AKARI_CE_IMPORT LONG TSPI_phoneGetDevCaps(
    DWORD dwDeviceID,
    DWORD dwTSPIVersion,
    DWORD dwExtVersion,
    LPPHONECAPS lpPhoneCaps)
    AKARI_CE_NAME(TSPI_phoneGetDevCaps);

AKARI_CE_IMPORT LONG TSPI_phoneGetExtensionID(
    DWORD dwDeviceID,
    DWORD dwTSPIVersion,
    LPPHONEEXTENSIONID lpExtensionID)
    AKARI_CE_NAME(TSPI_phoneGetExtensionID);

AKARI_CE_IMPORT LONG TSPI_phoneGetGain(
    HDRVPHONE hdPhone,
    DWORD dwHookSwitchDev,
    LPDWORD lpdwGain)
    AKARI_CE_NAME(TSPI_phoneGetGain);

AKARI_CE_IMPORT LONG TSPI_phoneGetHookSwitch(
    HDRVPHONE hdPhone,
    LPDWORD lpdwHookSwitchDevs)
    AKARI_CE_NAME(TSPI_phoneGetHookSwitch);

AKARI_CE_IMPORT LONG TSPI_phoneGetIcon(
    DWORD dwDeviceID,
    LPCWSTR lpszDeviceClass,
    LPHICON lphIcon)
    AKARI_CE_NAME(TSPI_phoneGetIcon);

AKARI_CE_IMPORT LONG TSPI_phoneGetID(
    HDRVPHONE hdPhone,
    LPVARSTRING lpDeviceID,
    LPCWSTR lpszDeviceClass,
    HANDLE hTargetProcess)
    AKARI_CE_NAME(TSPI_phoneGetID);

AKARI_CE_IMPORT LONG TSPI_phoneGetRing(
    HDRVPHONE hdPhone,
    LPDWORD lpdwRingMode,
    LPDWORD lpdwVolume)
    AKARI_CE_NAME(TSPI_phoneGetRing);

AKARI_CE_IMPORT LONG TSPI_phoneGetStatus(
    HDRVPHONE hdPhone,
    LPPHONESTATUS lpPhoneStatus)
    AKARI_CE_NAME(TSPI_phoneGetStatus);

AKARI_CE_IMPORT LONG TSPI_phoneGetVolume(
    HDRVPHONE hdPhone,
    DWORD dwHookSwitchDev,
    LPDWORD lpdwVolume)
    AKARI_CE_NAME(TSPI_phoneGetVolume);

AKARI_CE_IMPORT LONG TSPI_phoneNegotiateExtVersion(
    DWORD dwDeviceID,
    DWORD dwTSPIVersion,
    DWORD dwLowVersion,
    DWORD dwHighVersion,
    LPDWORD lpdwExtVersion)
    AKARI_CE_NAME(TSPI_phoneNegotiateExtVersion);

AKARI_CE_IMPORT LONG TSPI_phoneNegotiateTSPIVersion(
    DWORD dwDeviceID,
    DWORD dwLowVersion,
    DWORD dwHighVersion,
    LPDWORD lpdwTSPIVersion)
    AKARI_CE_NAME(TSPI_phoneNegotiateTSPIVersion);

AKARI_CE_IMPORT LONG TSPI_phoneOpen(
    DWORD dwDeviceID,
    HTAPIPHONE htPhone,
    LPHDRVPHONE lphdPhone,
    DWORD dwTSPIVersion,
    PHONEEVENT lpfnEventProc)
    AKARI_CE_NAME(TSPI_phoneOpen);

AKARI_CE_IMPORT LONG TSPI_phoneSelectExtVersion(
    HDRVPHONE hdPhone,
    DWORD dwExtVersion)
    AKARI_CE_NAME(TSPI_phoneSelectExtVersion);

AKARI_CE_IMPORT LONG TSPI_phoneSetGain(
    DRV_REQUESTID dwRequestID,
    HDRVPHONE hdPhone,
    DWORD dwHookSwitchDev,
    DWORD dwGain)
    AKARI_CE_NAME(TSPI_phoneSetGain);

AKARI_CE_IMPORT LONG TSPI_phoneSetHookSwitch(
    DRV_REQUESTID dwRequestID,
    HDRVPHONE hdPhone,
    DWORD dwHookSwitchDevs,
    DWORD dwHookSwitchMode)
    AKARI_CE_NAME(TSPI_phoneSetHookSwitch);

AKARI_CE_IMPORT LONG TSPI_phoneSetRing(
    DRV_REQUESTID dwRequestID,
    HDRVPHONE hdPhone,
    DWORD dwRingMode,
    DWORD dwVolume)
    AKARI_CE_NAME(TSPI_phoneSetRing);

AKARI_CE_IMPORT LONG TSPI_phoneSetStatusMessages(
    HDRVPHONE hdPhone,
    DWORD dwPhoneStates,
    DWORD dwButtonModes,
    DWORD dwButtonStates)
    AKARI_CE_NAME(TSPI_phoneSetStatusMessages);

AKARI_CE_IMPORT LONG TSPI_phoneSetVolume(
    DRV_REQUESTID dwRequestID,
    HDRVPHONE hdPhone,
    DWORD dwHookSwitchDev,
    DWORD dwVolume)
    AKARI_CE_NAME(TSPI_phoneSetVolume);

/* ------------------------------------------------------------------ */
/* TSPI service provider functions                    */
/* ------------------------------------------------------------------ */

AKARI_CE_IMPORT LONG TSPI_providerCreateLineDevice(
    HKEY hActive,
    LPCWSTR szDevKey,
    LPCWSTR szDevName)
    AKARI_CE_NAME(TSPI_providerCreateLineDevice);

AKARI_CE_IMPORT LONG TSPI_providerCreatePhoneDevice(
    HKEY hActive,
    LPCWSTR szDevKey,
    LPCWSTR szDevName)
    AKARI_CE_NAME(TSPI_providerCreatePhoneDevice);

AKARI_CE_IMPORT LONG TSPI_providerEnumDevices(
    DWORD dwPermanentProviderID,
    LPDWORD lpdwNumLines,
    LPDWORD lpdwNumPhones,
    HPROVIDER hProvider,
    LINEEVENT lpfnLineCreateProc,
    PHONEEVENT lpfnPhoneCreateProc)
    AKARI_CE_NAME(TSPI_providerEnumDevices);

AKARI_CE_IMPORT LONG TSPI_providerInit(
    DWORD dwTSPIVersion,
    DWORD dwPermanentProviderID,
    DWORD dwLineDeviceIDBase,
    DWORD dwPhoneDeviceIDBase,
    DWORD_PTR dwNumLines,
    DWORD_PTR dwNumPhones,
    ASYNC_COMPLETION lpfnCompletionProc,
    LPDWORD lpdwTSPIOptions)
    AKARI_CE_NAME(TSPI_providerInit);

AKARI_CE_IMPORT LONG TSPI_providerInstall(
    HWND hwndOwner,
    DWORD dwPermanentProviderID)
    AKARI_CE_NAME(TSPI_providerInstall);

AKARI_CE_IMPORT LONG TSPI_providerRemove(
    HWND hwndOwner,
    DWORD dwPermanentProviderID)
    AKARI_CE_NAME(TSPI_providerRemove);

AKARI_CE_IMPORT LONG TSPI_providerRemoveDevice(
    LPCWSTR lpszDeviceName)
    AKARI_CE_NAME(TSPI_providerRemoveDevice);

AKARI_CE_IMPORT LONG TSPI_providerShutdown(
    DWORD dwTSPIVersion,
    DWORD dwPermanentProviderID)
    AKARI_CE_NAME(TSPI_providerShutdown);

#endif  /* _TAPICOMN_H */
