/* Upnpdevapi.h -- UPnP C Device Host API (Windows CE .NET 4.0+).
 *
 * Pages: tools/manifests/servers.manifest (Servers book,
 * Universal Plug and Play (UPnP) node); Link Library rows print
 * Upnpcapi.lib (def/upnpcapi-doc.def).  See docs/inventory.md M75b.
 */

#ifndef AKARI_UPNPDEVAPI_H
#define AKARI_UPNPDEVAPI_H

#include "Windef.h"    /* DWORD, BOOL, PVOID, PDWORD, WINAPI */

/* aa451143 "UPNPCB_ID": print
 * `typedef enum {UPNPCB_INIT,UPNPCB_SUBSCRIBING,UPNPCB_UNSUBSCRIBING,
 * UPNPCB_CONTROL,UPNPCB_IDLE,UPNPCB_WAKEUP,UPNPCB_SHUTDOWN}
 * UPNPCB_ID;` -- no explicit values; sequential from 0 per C
 * semantics. */
typedef enum {
    UPNPCB_INIT,
    UPNPCB_SUBSCRIBING,
    UPNPCB_UNSUBSCRIBING,
    UPNPCB_CONTROL,
    UPNPCB_IDLE,
    UPNPCB_WAKEUP,
    UPNPCB_SHUTDOWN
} UPNPCB_ID;

/* aa451148 "UPNPPARAM": print
 * `typedef struct {PCWSTRpszName;PCWSTRpszValue;} UPNPPARAM;` */
typedef struct {
    PCWSTR pszName;
    PCWSTR pszValue;
} UPNPPARAM;

/* ms896349 "PUPNPCALLBACK": print
 * `typedef DWORD (*PUPNPCALLBACK) (UPNPCB_IDcallbackId,
 * PVOID pvUserContext,PVOIDpvSvcParam);` */
typedef DWORD (*PUPNPCALLBACK)(UPNPCB_ID callbackId,
                               PVOID pvUserContext,
                               PVOID pvSvcParam);

/* aa451144 "UPNPDEVICEINFO": print
 * `typedef struct {DWORDcbStruct;PWSTRpszDeviceDescription;
 * PWSTR pszDeviceName;PWSTRpszUDN;DWORD cachecontrol;
 * PUPNPCALLBACKpfCallback;PVOIDpvUserDevContext;} UPNPDEVICEINFO;` */
typedef struct {
    DWORD         cbStruct;
    PWSTR         pszDeviceDescription;
    PWSTR         pszDeviceName;
    PWSTR         pszUDN;
    DWORD         cachecontrol;
    PUPNPCALLBACK pfCallback;
    PVOID         pvUserDevContext;
} UPNPDEVICEINFO;

/* ms898418 "UPNPSERVICECONTROL": print
 * `typedef struct {PCWSTRpszRequestXML;PCWSTRpszSID;
 * PCWSTRpszServiceType;PCWSTRpszAction;PCWSTR pszUDN;DWORDiAction;
 * DWORDcInArgs;UPNPPARAM* pInArgs;PVOIDReserved1;}
 * UPNPSERVICECONTROL;` */
typedef struct {
    PCWSTR     pszRequestXML;
    PCWSTR     pszSID;
    PCWSTR     pszServiceType;
    PCWSTR     pszAction;
    PCWSTR     pszUDN;
    DWORD      iAction;
    DWORD      cInArgs;
    UPNPPARAM *pInArgs;
    PVOID      Reserved1;
} UPNPSERVICECONTROL;

/* ms898558 "UPNPSUBSCRIPTION": print
 * `typedef struct {PCWSTRpszUDN;PCWSTRpszSID;} UPNPSUBSCRIPTION,
 * *PUNPNSUBSCRIPTION;` (pointer spelling as printed, including the
 * doc typo PUNPNSUBSCRIPTION). */
typedef struct {
    PCWSTR pszUDN;
    PCWSTR pszSID;
} UPNPSUBSCRIPTION, *PUNPNSUBSCRIPTION;

/* --- Functions (Upnpcapi.lib -> def/upnpcapi-doc.def). ---------- */

/* aa451138 "UpnpAddDevice": print
 * `BOOL WINAPI UpnpAddDevice(UPNPDEVICEINFO* pDevInfo);` */
AKARI_CE_IMPORT BOOL WINAPI UpnpAddDevice(UPNPDEVICEINFO *pDevInfo)
                    AKARI_CE_NAME(UpnpAddDevice);

/* aa451149 "UpnpPublishDevice": print
 * `BOOL WINAPI UpnpPublishDevice( PCWSTRpszDeviceName);` */
AKARI_CE_IMPORT BOOL WINAPI UpnpPublishDevice(PCWSTR pszDeviceName)
                    AKARI_CE_NAME(UpnpPublishDevice);

/* ms898561 "UpnpUnpublishDevice": print
 * `BOOL WINAPI UpnpUnpublishDevice(PCWSTRpszDeviceName);` */
AKARI_CE_IMPORT BOOL WINAPI UpnpUnpublishDevice(PCWSTR pszDeviceName)
                    AKARI_CE_NAME(UpnpUnpublishDevice);

/* aa451150 "UpnpRemoveDevice": print
 * `BOOL WINAPI UpnpRemoveDevice(PCWSTRpszDeviceName);` */
AKARI_CE_IMPORT BOOL WINAPI UpnpRemoveDevice(PCWSTR pszDeviceName)
                    AKARI_CE_NAME(UpnpRemoveDevice);

/* aa451145 "UpnpGetSCPDPath": print
 * `BOOL WINAPI UpnpGetSCPDPath(PCWSTRpszDeviceName,PCWSTRpszServiceId,
 * PCWSTR pszUDN,PCWSTRpszSCPDFilePath,DWORDcchFilePath);` */
AKARI_CE_IMPORT BOOL WINAPI UpnpGetSCPDPath(
                    PCWSTR pszDeviceName, PCWSTR pszServiceId,
                    PCWSTR pszUDN, PCWSTR pszSCPDFilePath,
                    DWORD cchFilePath) AKARI_CE_NAME(UpnpGetSCPDPath);

/* aa451146 "UpnpGetUDN": print
 * `BOOL WINAPI UpnpGetUDN(PCWSTRpszDeviceName,PCWSTRpszTemplateUDN,
 * PWSTRpszUDNBuf,PDWORDpchBuf);` */
AKARI_CE_IMPORT BOOL WINAPI UpnpGetUDN(
                    PCWSTR pszDeviceName, PCWSTR pszTemplateUDN,
                    PWSTR pszUDNBuf, PDWORD pchBuf)
                    AKARI_CE_NAME(UpnpGetUDN);

/* ms898523 "UpnpSetControlResponse" / ms898533 "UpnpSetErrorResponse" /
 * ms898542 "UpnpSetRawControlResponse": prints omit the return type
 * and the pages carry no Return Values section (every BOOL sibling
 * has one) -- closed as void. */
AKARI_CE_IMPORT void WINAPI UpnpSetControlResponse(
                    UPNPSERVICECONTROL *pUPnPAction, DWORD cOutArgs,
                    UPNPPARAM *aOutArgs)
                    AKARI_CE_NAME(UpnpSetControlResponse);
AKARI_CE_IMPORT void WINAPI UpnpSetErrorResponse(
                    UPNPSERVICECONTROL *pUPnPAction, DWORD dwErrorCode,
                    PCWSTR pszErrorDescription)
                    AKARI_CE_NAME(UpnpSetErrorResponse);
AKARI_CE_IMPORT void WINAPI UpnpSetRawControlResponse(
                    UPNPSERVICECONTROL *pUPnPAction, DWORD dwHttpStatus,
                    PCWSTR pszRespXML)
                    AKARI_CE_NAME(UpnpSetRawControlResponse);

/* ms898553 "UpnpSubmitPropertyEvent": print
 * `BOOL WINAPI UpnpSubmitPropertyEvent(PCWSTRpszDeviceName,
 * PCWSTR pszUDN,PCWSTRpszServiceId,DWORDnArgs,UPNPPARAM* rgArgs);` */
AKARI_CE_IMPORT BOOL WINAPI UpnpSubmitPropertyEvent(
                    PCWSTR pszDeviceName, PCWSTR pszUDN,
                    PCWSTR pszServiceId, DWORD nArgs,
                    UPNPPARAM *rgArgs)
                    AKARI_CE_NAME(UpnpSubmitPropertyEvent);

#endif /* AKARI_UPNPDEVAPI_H */
