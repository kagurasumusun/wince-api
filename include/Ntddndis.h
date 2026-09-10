/* Ntddndis.h -- NDIS network-device IOCTL/OID support types.
 *
 * Source pages: Network Driver Reference book, the rows whose
 * Requirements print "Header: Ntddndis.h" (126 pages) or
 * "Header: Ntddndis.h and Ndistapi.h" (69 pages, the
 * NDIS_TAPI_* request structures -- emitted here, once, with the
 * joint home noted; see also Ndistapi.h).
 *
 * The 131 OID_* object-identifier pages and the
 * IOCTL_NDIS_GET_LOG_DATA page document names and prose only --
 * no CE page prints any OID/IOCTL value, so the identifiers are
 * recorded as names below and not emitted as macros.
 *
 * Types whose prints embed types no CE page prints
 * (NDIS_DEVICE_POWER_STATE, the HDRV_ and HTAPI_ driver-side
 * TAPI handles, the LINE_* TAPI structures) are recorded verbatim
 * and closed opaquely.  NDIS_WLAN_BSSID is printed by a page
 * whose Requirements row says "Header: Ndis.h" (ms905053); it is
 * co-located here because every member type is one of the
 * 802.11 types below and the BSSID list embeds it by
 * value (home note recorded; Ndis.h does not define it).
 * See docs/inventory.md M78b.
 */

#ifndef AKARI_NTDDNDIS_H
#define AKARI_NTDDNDIS_H

#include "Windef.h"    /* ULONG, UCHAR, LONG, BOOLEAN, UINT */
#include "Winnt.h"     /* LARGE_INTEGER */

/* --- 802.11 scalar types (printed on their own data-type pages). */
/* aa447876 "NDIS_802_11_ANTENNA":
 * `typedef ULONG NDIS_802_11_ANTENNA;` */
typedef ULONG NDIS_802_11_ANTENNA;

/* aa447881 "NDIS_802_11_FRAGMENTATION_THRESHOLD":
 * `typedef ULONG NDIS_802_11_FRAGMENTATION_THRESHOLD;` */
typedef ULONG NDIS_802_11_FRAGMENTATION_THRESHOLD;

/* aa447882 "NDIS_802_11_KEY_INDEX":
 * `typedef ULONG NDIS_802_11_KEY_INDEX;` */
typedef ULONG NDIS_802_11_KEY_INDEX;

/* aa447892 "NDIS_802_11_RSSI":
 * `typedef LONG NDIS_802_11_RSSI;` */
typedef LONG NDIS_802_11_RSSI;

/* aa447893 "NDIS_802_11_RTS_THRESHOLD":
 * `typedef ULONG NDIS_802_11_RTS_THRESHOLD;` */
typedef ULONG NDIS_802_11_RTS_THRESHOLD;

/* aa447896 "NDIS_802_11_TX_POWER_LEVEL":
 * `typedef ULONG NDIS_802_11_TX_POWER_LEVEL;` */
typedef ULONG NDIS_802_11_TX_POWER_LEVEL;

/* aa447883 "NDIS_802_11_MAC_ADDRESS":
 * `typedef UCHAR NDIS_802_11_MAC_ADDRESS[6];` */
typedef UCHAR NDIS_802_11_MAC_ADDRESS[6];

/* aa447890 "NDIS_802_11_RATES":
 * `typedef UCHAR NDIS_802_11_RATES[8];` */
typedef UCHAR NDIS_802_11_RATES[8];

/* --- 802.11 enumerations (printed, implicit successors). -------- */
/* aa447877 "NDIS_802_11_AUTHENTICATION_MODE": print. */
typedef enum _NDIS_802_11_AUTHENTICATION_MODE {
    Ndis802_11AuthModeOpen,
    Ndis802_11AuthModeShared,
    Ndis802_11AuthModeAutoSwitch,
    Ndis802_11AuthModeMax
} NDIS_802_11_AUTHENTICATION_MODE, *PNDIS_802_11_AUTHENTICATION_MODE;

/* aa447884 "NDIS_802_11_NETWORK_INFRASTRUCTURE": print. */
typedef enum _NDIS_802_11_NETWORK_INFRASTRUCTURE {
    Ndis802_11IBSS,
    Ndis802_11Infrastructure,
    Ndis802_11AutoUnknown,
    Ndis802_11InfrastructureMax
} NDIS_802_11_NETWORK_INFRASTRUCTURE, *PNDIS_802_11_NETWORK_INFRASTRUCTURE;

/* aa447885 "NDIS_802_11_NETWORK_TYPE": print. */
typedef enum _NDIS_802_11_NETWORK_TYPE {
    Ndis802_11FH,
    Ndis802_11DS,
    Ndis802_11NetworkTypeMax
} NDIS_802_11_NETWORK_TYPE, *PNDIS_802_11_NETWORK_TYPE;

/* aa447887 "NDIS_802_11_POWER_MODE": print. */
typedef enum _NDIS_802_11_POWER_MODE {
    Ndis802_11PowerModeCAM,
    Ndis802_11PowerModeMAX_PSP,
    Ndis802_11PowerModeFast_PSP,
    Ndis802_11PowerModeMax
} NDIS_802_11_POWER_MODE, *PNDIS_802_11_POWER_MODE;

/* aa447889 "NDIS_802_11_PRIVACY_FILTER": print. */
typedef enum _NDIS_802_11_PRIVACY_FILTER {
    Ndis802_11PrivFilterAcceptAll,
    Ndis802_11PrivFilter8021xWEP
} NDIS_802_11_PRIVACY_FILTER, *PNDIS_802_11_PRIVACY_FILTER;

/* aa447891 "NDIS_802_11_RELOAD_DEFAULTS": print. */
typedef enum _NDIS_802_11_RELOAD_DEFAULTS {
    Ndis802_11ReloadWEPKeys
} NDIS_802_11_RELOAD_DEFAULTS, *PNDIS_802_11_RELOAD_DEFAULTS;

/* aa447898 "NDIS_802_11_WEP_STATUS": print (two typedef name
 * pairs as printed; the `Ndis802_11Encryption1KeyAbsent =
 * Ndis802_11WEPNotSupported` anchor is reproduced verbatim -- it
 * is a suspected doc misprint for Ndis802_11WEPKeyAbsent but the
 * intended right-hand side is not certain, so no repair). */
typedef enum _NDIS_802_11_WEP_STATUS {
    Ndis802_11WEPEnabled,
    Ndis802_11Encryption1Enabled = Ndis802_11WEPEnabled,
    Ndis802_11WEPDisabled,
    Ndis802_11EncryptionDisabled = Ndis802_11WEPDisabled,
    Ndis802_11WEPKeyAbsent,
    Ndis802_11Encryption1KeyAbsent = Ndis802_11WEPKeyAbsent,
    Ndis802_11WEPNotSupported,
    Ndis802_11EncryptionNotSupported = Ndis802_11WEPNotSupported,
    Ndis802_11Encryption2Enabled,
    Ndis802_11Encryption2KeyAbsent,
    Ndis802_11Encryption3Enabled,
    Ndis802_11Encryption3KeyAbsent
} NDIS_802_11_WEP_STATUS, *PNDIS_802_11_WEP_STATUS,
  NDIS_802_11_ENCRYPTION_STATUS, *PNDIS_802_11_ENCRYPTION_STATUS;

/* aa447899 "NDIS_802_5_RING_STATE": print (anchor = 1). */
typedef enum _NDIS_802_5_RING_STATE {
    NdisRingStateOpened = 1,
    NdisRingStateClosed,
    NdisRingStateOpening,
    NdisRingStateClosing,
    NdisRingStateOpenFailure,
    NdisRingStateRingFailure
} NDIS_802_5_RING_STATE, *PNDIS_802_5_RING_STATE;

/* aa448032 "NDIS_MEDIUM": print (this page is the grounded source
 * for the medium list; NdisOpenAdapter in Ndis.h stays recorded
 * because its print also names the unpublished PSTRING type). */
typedef enum _NDIS_MEDIUM {
    NdisMedium802_3,
    NdisMedium802_5,
    NdisMediumWan,
    NdisMediumDix,
    NdisMediumWirelessWan,
    NdisMediumIrda,
    NdisMediumBpc,
    NdisMediumCoWan,
    NdisMedium1394,
    NdisMediumMax
} NDIS_MEDIUM, *PNDIS_MEDIUM;

/* ms905049 "NDIS_WAN_MEDIUM_SUBTYPE": print. */
typedef enum _NDIS_WAN_MEDIUM_SUBTYPE {
    NdisWanMediumHub,
    NdisWanMediumX_25,
    NdisWanMediumIsdn,
    NdisWanMediumSerial,
    NdisWanMediumFrameRelay,
    NdisWanMediumAtm,
    NdisWanMediumSonet,
    NdisWanMediumSW56K,
    NdisWanMediumPPTP,
    NdisWanMediumL2TP,
    NdisWanMediumIrda,
    NdisWanMediumParallel,
    NdisWanMediumPppoe
} NDIS_WAN_MEDIUM_SUBTYPE, *PNDIS_WAN_MEDIUM_SUBTYPE;

/* --- 802.11 structures (printed). ------------------------------ */
/* aa447894 "NDIS_802_11_SSID": print (`UCHAR Ssid [32]` spacing). */
typedef struct _NDIS_802_11_SSID {
    ULONG SsidLength;
    UCHAR Ssid[32];
} NDIS_802_11_SSID, *PNDIS_802_11_SSID;

/* aa447880 "NDIS_802_11_CONFIGURATION_FH": print (glued tokens
 * split). */
typedef struct _NDIS_802_11_CONFIGURATION_FH {
    ULONG Length;
    ULONG HopPattern;
    ULONG HopSet;
    ULONG DwellTime;
} NDIS_802_11_CONFIGURATION_FH, *PNDIS_802_11_CONFIGURATION_FH;

/* aa447879 "NDIS_802_11_CONFIGURATION": print. */
typedef struct _NDIS_802_11_CONFIGURATION {
    ULONG Length;
    ULONG BeaconPeriod;
    ULONG ATIMWindow;
    ULONG DSConfig;
    NDIS_802_11_CONFIGURATION_FH FHConfig;
} NDIS_802_11_CONFIGURATION, *PNDIS_802_11_CONFIGURATION;

/* aa447886 "NDIS_802_11_NETWORK_TYPE_LIST": print. */
typedef struct _NDIS_802_11_NETWORK_TYPE_LIST {
    ULONG NumberOfItems;
    NDIS_802_11_NETWORK_TYPE NetworkType[1];
} NDIS_802_11_NETWORK_TYPE_LIST, *PNDIS_802_11_NETWORK_TYPE_LIST;

/* aa447895 "NDIS_802_11_STATISTICS": print (LARGE_INTEGER
 * counters; Winnt.h). */
typedef struct _NDIS_802_11_STATISTICS {
    ULONG          Length;
    LARGE_INTEGER  TransmittedFragmentCount;
    LARGE_INTEGER  MulticastTransmittedFrameCount;
    LARGE_INTEGER  FailedCount;
    LARGE_INTEGER  RetryCount;
    LARGE_INTEGER  MultipleRetryCount;
    LARGE_INTEGER  RTSSuccessCount;
    LARGE_INTEGER  RTSFailureCount;
    LARGE_INTEGER  ACKFailureCount;
    LARGE_INTEGER  FrameDuplicateCount;
    LARGE_INTEGER  ReceivedFragmentCount;
    LARGE_INTEGER  MulticastReceivedFrameCount;
    LARGE_INTEGER  FCSErrorCount;
} NDIS_802_11_STATISTICS, *PNDIS_802_11_STATISTICS;

/* aa447897 "NDIS_802_11_WEP": print. */
typedef struct _NDIS_802_11_WEP {
    ULONG Length;
    ULONG KeyIndex;
    ULONG KeyLength;
    UCHAR KeyMaterial[1];
} NDIS_802_11_WEP, *PNDIS_802_11_WEP;

/* ms905053 "NDIS_WLAN_BSSID" (page Requirements: Header Ndis.h;
 * co-located here, see header comment): print `struct
 * _NDIS_WLAN_BSSID{ ULONGLength; NDIS_802_11_MAC_ADDRESSMacAddress;
 * UcharReserved[2];NDIS_802_11_SSIDSsid;ULONG Privacy;
 * NDIS_802_11_RSSIRssi; NDIS_802_11_NETWORK_TYPENetworkTypeInUse;
 * NDIS_802_11_CONFIGURATIONConfiguration;NDIS_802_11_NETWORK_
 * INFRASTRUCTUREInfrastructureMode;NDIS_802_11_RATESSupportedRates;}
 * NDIS_WLAN_BSSID, *PNDIS_WLAN_BSSID;` -- the print spells
 * `Uchar` (Ulong/Uchar normalization precedent, Natedit.h
 * ms885685) and omits the `typedef` keyword; both noted. */
typedef struct _NDIS_WLAN_BSSID {
    ULONG                               Length;
    NDIS_802_11_MAC_ADDRESS             MacAddress;
    UCHAR                               Reserved[2];
    NDIS_802_11_SSID                    Ssid;
    ULONG                               Privacy;
    NDIS_802_11_RSSI                    Rssi;
    NDIS_802_11_NETWORK_TYPE            NetworkTypeInUse;
    NDIS_802_11_CONFIGURATION           Configuration;
    NDIS_802_11_NETWORK_INFRASTRUCTURE  InfrastructureMode;
    NDIS_802_11_RATES                   SupportedRates;
} NDIS_WLAN_BSSID, *PNDIS_WLAN_BSSID;

/* aa447878 "NDIS_802_11_BSSID_LIST": print. */
typedef struct _NDIS_802_11_BSSID_LIST {
    ULONG            NumberOfItems;
    NDIS_WLAN_BSSID  Bssid[1];
} NDIS_802_11_BSSID_LIST, *PNDIS_802_11_BSSID_LIST;

/* --- Power-management / TAPI support types. -------------------- */
/* ms904094 "NDIS_PM_PACKET_PATTERN": print (glued tokens split). */
typedef struct _NDIS_PM_PACKET_PATTERN {
    ULONG Priority;
    ULONG Reserved;
    ULONG MaskSize;
    ULONG PatternOffset;
    ULONG PatternSize;
    ULONG PatternFlags;
} NDIS_PM_PACKET_PATTERN, *PNDIS_PM_PACKET_PATTERN;

/* ms923263 "VAR_STRING" (pages print "Header: Ntddndis.h and
 * Ndistapi.h"): print. */
typedef struct _VAR_STRING {
    ULONG ulTotalSize;
    ULONG ulNeededSize;
    ULONG ulUsedSize;
    ULONG ulStringFormat;
    ULONG ulStringSize;
    ULONG ulStringOffset;
} VAR_STRING, *PVAR_STRING;

/* --- NDIS_TAPI_* request structures whose prints are fully
 *     grounded (ULONG/CHAR members only).  The full NDIS_TAPI_*
 *     set lives on pages printing "Header: Ntddndis.h and
 *     Ndistapi.h"; each struct is emitted once, here. --------- */
/* ms904990 "NDIS_TAPI_CONFIG_DIALOG": print (glued tokens split; OUT annotations dropped). */
typedef struct _NDIS_TAPI_CONFIG_DIALOG {
    ULONG ulRequestID;
    ULONG ulDeviceID;
    ULONG ulDeviceClassSize;
    ULONG ulDeviceClassOffset;
    ULONG ulLibraryNameTotalSize;
    ULONG ulLibraryNameNeededSize;
    CHAR  szLibraryName[1];
} NDIS_TAPI_CONFIG_DIALOG, *PNDIS_TAPI_CONFIG_DIALOG;

/* ms905010 "NDIS_TAPI_NEGOTIATE_EXT_VERSION": print (glued tokens split; OUT annotations dropped). */
typedef struct _NDIS_TAPI_NEGOTIATE_EXT_VERSION {
    ULONG ulRequestID;
    ULONG ulDeviceID;
    ULONG ulLowVersion;
    ULONG ulHighVersion;
    ULONG ulExtVersion;
} NDIS_TAPI_NEGOTIATE_EXT_VERSION, *PNDIS_TAPI_NEGOTIATE_EXT_VERSION;

/* ms905012 "NDIS_TAPI_PROVIDER_INITIALIZE": print (glued tokens split; OUT annotations dropped). */
typedef struct _NDIS_TAPI_PROVIDER_INITIALIZE {
    ULONG ulRequestID;
    ULONG ulDeviceIDBase;
    ULONG ulNumLineDevs;
    ULONG ulProviderID;
} NDIS_TAPI_PROVIDER_INITIALIZE, *PNDIS_TAPI_PROVIDER_INITIALIZE;

/* ms905013 "NDIS_TAPI_PROVIDER_SHUTDOWN": print (glued tokens split; OUT annotations dropped). */
typedef struct _NDIS_TAPI_PROVIDER_SHUTDOWN {
    ULONG ulRequestID;
} NDIS_TAPI_PROVIDER_SHUTDOWN, *PNDIS_TAPI_PROVIDER_SHUTDOWN;

/* ms905020 "NDIS_TAPI_SET_DEV_CONFIG": print (glued tokens split; OUT annotations dropped). */
typedef struct _NDIS_TAPI_SET_DEV_CONFIG {
    ULONG ulRequestID;
    ULONG ulDeviceID;
    ULONG ulDeviceClassSize;
    ULONG ulDeviceClassOffset;
    ULONG ulDeviceConfigSize;
    UCHAR DeviceConfig[1];
} NDIS_TAPI_SET_DEV_CONFIG, *PNDIS_TAPI_SET_DEV_CONFIG;

/* --- Held NDIS_TAPI_* structures: prints embed the HDRV_CALL,
 *     HDRV_LINE, HTAPI_CALL, HTAPI_LINE driver-side handles or
 *     LINE_* TAPI structures, none of which any CE page prints.
 *     Prints recorded verbatim; opaque forward for pointer use. - */
/* ms904985 "NDIS_TAPI_ACCEPT": `typedef struct _NDIS_TAPI_ACCEPT { ULONGulRequestID;HDRV_CALLhdCall;ULONGulUserUserInfoSize;UCHARUserUserInfo[1];} NDIS_TAPI_ACCEPT, *PNDIS_TAPI_ACCEPT` */
/* ms904986 "NDIS_TAPI_ANSWER": `typedef struct _NDIS_TAPI_ANSWER { ULONGulRequestID; HDRV_CALLhdCall;ULONGulUserUserInfoSize;UCHARUserUserInfo[1];} NDIS_TAPI_ANSWER, *PNDIS_TAPI_ANSWER` */
/* ms904987 "NDIS_TAPI_CLOSE": `typedef struct _NDIS_TAPI_CLOSE { ULONGulRequestID;HDRV_LINEhdLine;} NDIS_TAPI_CLOSE, *PNDIS_TAPI_CLOSE` */
/* ms904988 "NDIS_TAPI_CLOSE_CALL": `typedef struct _NDIS_TAPI_CLOSE_CALL { ULONGulRequestID;HDRV_CALLhdCall;} NDIS_TAPI_CLOSE_CALL, *PNDIS_TAPI_CLOSE_CALL` */
/* ms904989 "NDIS_TAPI_CONDITIONAL_MEDIA_DETECTION": `typedef struct _NDIS_TAPI_CONDITIONAL_MEDIA_DETECTION { ULONGulRequestID;HDRV_LINEhdLine;ULONGulMediaModes;LINE_CALL_PARAMSLineCallParams;} NDIS_TAPI_CONDITIONAL_MEDIA_DETECTION, *PNDIS_TAPI_CONDITIONAL_MEDIA_DETECTION` */
/* ms904991 "NDIS_TAPI_DEV_SPECIFIC": `typedef struct _NDIS_TAPI_DEV_SPECIFIC { ULONGulRequestID;HDRV_LINEhdLine;ULONGulAddressID;HDRV_CALLhdCall;ULONGulParamsSize;UCHARParams[1];} NDIS_TAPI_DEV_SPECIFIC, *PNDIS_TAPI_DEV_SPECIFIC` */
/* ms904992 "NDIS_TAPI_DIAL": `typedef struct _NDIS_TAPI_DIAL { ULONGulRequestID; HDRV_CALLhdCall; ULONGulDestAddressSize;CHARszDestAddress[1];} NDIS_TAPI_DIAL, *PNDIS_TAPI_DIAL` */
/* ms904993 "NDIS_TAPI_DROP": `typedef struct _NDIS_TAPI_DROP { ULONGulRequestID;HDRV_CALLhdCall; ULONGulUserUserInfoSize; UCHARUserUserInfo[1];} NDIS_TAPI_DROP, *PNDIS_TAPI_DROP` */
/* ms904996 "NDIS_TAPI_GET_ADDRESS_CAPS": `typedef struct _NDIS_TAPI_GET_ADDRESS_CAPS { ULONGulRequestID; ULONG ulDeviceID; ULONGulAddressID;ULONG ulExtVersion; LINE_ADDRESS_CAPSLineAddressCaps;} NDIS_TAPI_GET_ADDRESS_CAPS, *PNDIS_TAPI_GET_ADDRESS_CAPS` */
/* ms904997 "NDIS_TAPI_GET_ADDRESS_ID": `typedef struct _NDIS_TAPI_GET_ADDRESS_ID { ULONGulRequestID;HDRV_LINEhdLine;ULONGulAddressID;ULONGulAddressMode;ULONGulAddressSize;CHARszAddress[1];} NDIS_TAPI_GET_ADDRESS_ID, *PNDIS_TAPI_GET_ADDRESS_ID` */
/* ms904998 "NDIS_TAPI_GET_ADDRESS_STATUS": `typedef struct _NDIS_TAPI_GET_ADDRESS_STATUS { ULONG ulRequestID;HDRV_LINEhdLine;ULONGulAddressID;OUT LINE_ADDRESS_STATUSLineAddressStatus;} NDIS_TAPI_GET_ADDRESS_STATUS, *PNDIS_TAPI_GET_ADDRESS_STATUS` */
/* ms905001 "NDIS_TAPI_GET_CALL_ADDRESS_ID": `typedef struct _NDIS_TAPI_GET_CALL_ADDRESS_ID { ULONG ulRequestID;HDRV_CALLhdCall; ULONGulAddressID;} NDIS_TAPI_GET_CALL_ADDRESS_ID, *PNDIS_TAPI_GET_CALL_ADDRESS_ID` */
/* ms905002 "NDIS_TAPI_GET_CALL_INFO": `typedef struct _NDIS_TAPI_GET_CALL_INFO { ULONGulRequestID;HDRV_CALLhdCall;LINE_CALL_INFOLineCallInfo;} NDIS_TAPI_GET_CALL_INFO, *PNDIS_TAPI_GET_CALL_INFO` */
/* ms905003 "NDIS_TAPI_GET_CALL_STATUS": `typedef struct _NDIS_TAPI_GET_CALL_STATUS { ULONGulRequestID;HDRV_CALLhdCall; OUT LINE_CALL_STATUSLineCallStatus;} NDIS_TAPI_GET_CALL_STATUS, *PNDIS_TAPI_GET_CALL_STATUS` */
/* ms905004 "NDIS_TAPI_GET_DEV_CAPS": `typedef struct _NDIS_TAPI_GET_DEV_CAPS { ULONG ulRequestID;ULONGulDeviceID; ULONGulExtVersion; LINE_DEV_CAPSLineDevCaps;} NDIS_TAPI_GET_DEV_CAPS, *PNDIS_TAPI_GET_DEV_CAPS` */
/* ms905005 "NDIS_TAPI_GET_DEV_CONFIG": `typedef struct _NDIS_TAPI_GET_DEV_CONFIG { ULONGulRequestID;ULONGulDeviceID; ULONGulDeviceClassSize;ULONGulDeviceClassOffset;VAR_STRINGDeviceConfig;} NDIS_TAPI_GET_DEV_CONFIG, *PNDIS_TAPI_GET_DEV_CONFIG` */
/* ms905006 "NDIS_TAPI_GET_EXTENSION_ID": `typedef struct _NDIS_TAPI_GET_EXTENSION_ID { ULONGulRequestID;ULONGulDeviceID;LINE_EXTENSION_IDLineExtensionID;} NDIS_TAPI_GET_EXTENSION_ID, *PNDIS_TAPI_GET_EXTENSION_ID` */
/* ms905007 "NDIS_TAPI_GET_ID": `typedef struct _NDIS_TAPI_GET_ID { ULONGulRequestID;HDRV_LINEhdLine;ULONGulAddressID;HDRV_CALLhdCall;ULONGulSelect;ULONGulDeviceClassSize;ULONGulDeviceClassOffset;VAR_STRINGDeviceID;}NDIS_TAPI_GET_ID, *PNDIS_TAPI_GET_ID` */
/* ms905008 "NDIS_TAPI_GET_LINE_DEV_STATUS": `typedef struct _NDIS_TAPI_GET_LINE_DEV_STATUS { ULONGulRequestID;HDRV_LINEhdLine;LINE_DEV_STATUSLineDevStatus;} NDIS_TAPI_GET_LINE_DEV_STATUS, *PNDIS_TAPI_GET_LINE_DEV_STATUS` */
/* ms905009 "NDIS_TAPI_MAKE_CALL": `typedef struct _NDIS_TAPI_MAKE_CALL { ULONGulRequestID;HDRV_LINEhdLine;HTAPI_CALLhtCall;HDRV_CALLhdCall;ULONGulDestAddressSize;ULONGulDestAddressOffset;BOOLEAN bUseDefaultLineCallParams;LINE_CALL_PARAMSLineCallParams;} NDIS_TAPI_MAKE_CALL, *PNDIS_TAPI_MAKE_CALL` */
/* ms905011 "NDIS_TAPI_OPEN": `typedef struct _NDIS_TAPI_OPEN { ULONGulRequestID;ULONGulDeviceID;HTAPI_LINEhtLine;HDRV_LINEhdLine;} NDIS_TAPI_OPEN, *PNDIS_TAPI_OPEN` */
/* ms905014 "NDIS_TAPI_SECURE_CALL": `typedef struct _NDIS_TAPI_SECURE_CALL { ULONGulRequestID; HDRV_CALLhdCall;} NDIS_TAPI_SECURE_CALL, *PNDIS_TAPI_SECURE_CALL` */
/* ms905015 "NDIS_TAPI_SELECT_EXT_VERSION": `typedef struct _NDIS_TAPI_SELECT_EXT_VERSION { ULONGulRequestID;HDRV_LINEhdLine;ULONGulExtVersion;} NDIS_TAPI_SELECT_EXT_VERSION, *PNDIS_TAPI_SELECT_EXT_VERSION` */
/* ms905016 "NDIS_TAPI_SEND_USER_USER_INFO": `typedef struct _NDIS_TAPI_SEND_USER_USER_INFO { ULONGulRequestID; HDRV_CALLhdCall; ULONGulUserUserInfoSize; UCHARUserUserInfo[1];} NDIS_TAPI_SEND_USER_USER_INFO, *PNDIS_TAPI_SEND_USER_USER_INFO` */
/* ms905017 "NDIS_TAPI_SET_APP_SPECIFIC": `typedef struct _NDIS_TAPI_SET_APP_SPECIFIC { ULONGulRequestID;HDRV_CALLhdCall;ULONGulAppSpecific;} NDIS_TAPI_SET_APP_SPECIFIC, *PNDIS_TAPI_SET_APP_SPECIFIC` */
/* ms905018 "NDIS_TAPI_SET_CALL_PARAMS": `typedef struct _NDIS_TAPI_SET_CALL_PARAMS { ULONGulRequestID;HDRV_CALLhdCall;ULONGulBearerMode;ULONGulMinRate;ULONGulMaxRate;BOOLEANbSetLineDialParams;LINE_DIAL_PARAMSLineDialParams;} NDIS_TAPI_SET_CALL_PARAMS, *PNDIS_TAPI_SET_CALL_PARAMS` */
/* ms905019 "NDIS_TAPI_SET_DEFAULT_MEDIA_DETECTION": `typedef struct _NDIS_TAPI_SET_DEFAULT_MEDIA_DETECTION { ULONGulRequestID; HDRV_LINEhdLine; ULONGulMediaModes;} NDIS_TAPI_SET_DEFAULT_MEDIA_DETECTION, *PNDIS_TAPI_SET_DEFAULT_MEDIA_DETECTION` */
/* ms905021 "NDIS_TAPI_SET_MEDIA_MODE": `typedef struct _NDIS_TAPI_SET_MEDIA_MODE { ULONGulRequestID;HDRV_CALLhdCall;ULONGulMediaMode;} NDIS_TAPI_SET_MEDIA_MODE, *PNDIS_TAPI_SET_MEDIA_MODE` */
/* ms905022 "NDIS_TAPI_SET_STATUS_MESSAGES": `typedef struct _NDIS_TAPI_SET_STATUS_MESSAGES { ULONGulRequestID;HDRV_LINEhdLine;ULONGulLineStates; ULONGulAddressStates;} NDIS_TAPI_SET_STATUS_MESSAGES, *PNDIS_TAPI_SET_STATUS_MESSAGES` */
typedef struct _NDIS_TAPI_ACCEPT NDIS_TAPI_ACCEPT, *PNDIS_TAPI_ACCEPT;
typedef struct _NDIS_TAPI_ANSWER NDIS_TAPI_ANSWER, *PNDIS_TAPI_ANSWER;
typedef struct _NDIS_TAPI_CLOSE NDIS_TAPI_CLOSE, *PNDIS_TAPI_CLOSE;
typedef struct _NDIS_TAPI_CLOSE_CALL NDIS_TAPI_CLOSE_CALL, *PNDIS_TAPI_CLOSE_CALL;
typedef struct _NDIS_TAPI_CONDITIONAL_MEDIA_DETECTION NDIS_TAPI_CONDITIONAL_MEDIA_DETECTION, *PNDIS_TAPI_CONDITIONAL_MEDIA_DETECTION;
typedef struct _NDIS_TAPI_DEV_SPECIFIC NDIS_TAPI_DEV_SPECIFIC, *PNDIS_TAPI_DEV_SPECIFIC;
typedef struct _NDIS_TAPI_DIAL NDIS_TAPI_DIAL, *PNDIS_TAPI_DIAL;
typedef struct _NDIS_TAPI_DROP NDIS_TAPI_DROP, *PNDIS_TAPI_DROP;
typedef struct _NDIS_TAPI_GET_ADDRESS_CAPS NDIS_TAPI_GET_ADDRESS_CAPS, *PNDIS_TAPI_GET_ADDRESS_CAPS;
typedef struct _NDIS_TAPI_GET_ADDRESS_ID NDIS_TAPI_GET_ADDRESS_ID, *PNDIS_TAPI_GET_ADDRESS_ID;
typedef struct _NDIS_TAPI_GET_ADDRESS_STATUS NDIS_TAPI_GET_ADDRESS_STATUS, *PNDIS_TAPI_GET_ADDRESS_STATUS;
typedef struct _NDIS_TAPI_GET_CALL_ADDRESS_ID NDIS_TAPI_GET_CALL_ADDRESS_ID, *PNDIS_TAPI_GET_CALL_ADDRESS_ID;
typedef struct _NDIS_TAPI_GET_CALL_INFO NDIS_TAPI_GET_CALL_INFO, *PNDIS_TAPI_GET_CALL_INFO;
typedef struct _NDIS_TAPI_GET_CALL_STATUS NDIS_TAPI_GET_CALL_STATUS, *PNDIS_TAPI_GET_CALL_STATUS;
typedef struct _NDIS_TAPI_GET_DEV_CAPS NDIS_TAPI_GET_DEV_CAPS, *PNDIS_TAPI_GET_DEV_CAPS;
typedef struct _NDIS_TAPI_GET_DEV_CONFIG NDIS_TAPI_GET_DEV_CONFIG, *PNDIS_TAPI_GET_DEV_CONFIG;
typedef struct _NDIS_TAPI_GET_EXTENSION_ID NDIS_TAPI_GET_EXTENSION_ID, *PNDIS_TAPI_GET_EXTENSION_ID;
typedef struct _NDIS_TAPI_GET_ID NDIS_TAPI_GET_ID, *PNDIS_TAPI_GET_ID;
typedef struct _NDIS_TAPI_GET_LINE_DEV_STATUS NDIS_TAPI_GET_LINE_DEV_STATUS, *PNDIS_TAPI_GET_LINE_DEV_STATUS;
typedef struct _NDIS_TAPI_MAKE_CALL NDIS_TAPI_MAKE_CALL, *PNDIS_TAPI_MAKE_CALL;
typedef struct _NDIS_TAPI_OPEN NDIS_TAPI_OPEN, *PNDIS_TAPI_OPEN;
typedef struct _NDIS_TAPI_SECURE_CALL NDIS_TAPI_SECURE_CALL, *PNDIS_TAPI_SECURE_CALL;
typedef struct _NDIS_TAPI_SELECT_EXT_VERSION NDIS_TAPI_SELECT_EXT_VERSION, *PNDIS_TAPI_SELECT_EXT_VERSION;
typedef struct _NDIS_TAPI_SEND_USER_USER_INFO NDIS_TAPI_SEND_USER_USER_INFO, *PNDIS_TAPI_SEND_USER_USER_INFO;
typedef struct _NDIS_TAPI_SET_APP_SPECIFIC NDIS_TAPI_SET_APP_SPECIFIC, *PNDIS_TAPI_SET_APP_SPECIFIC;
typedef struct _NDIS_TAPI_SET_CALL_PARAMS NDIS_TAPI_SET_CALL_PARAMS, *PNDIS_TAPI_SET_CALL_PARAMS;
typedef struct _NDIS_TAPI_SET_DEFAULT_MEDIA_DETECTION NDIS_TAPI_SET_DEFAULT_MEDIA_DETECTION, *PNDIS_TAPI_SET_DEFAULT_MEDIA_DETECTION;
typedef struct _NDIS_TAPI_SET_MEDIA_MODE NDIS_TAPI_SET_MEDIA_MODE, *PNDIS_TAPI_SET_MEDIA_MODE;
typedef struct _NDIS_TAPI_SET_STATUS_MESSAGES NDIS_TAPI_SET_STATUS_MESSAGES, *PNDIS_TAPI_SET_STATUS_MESSAGES;

/* ms904095 "NDIS_PM_WAKE_UP_CAPABILITIES": print `typedef struct
 * _NDIS_PM_WAKE_UP_CAPABILITIES { NDIS_DEVICE_POWER_STATE
 * MinMagicPacketWakeUp; NDIS_DEVICE_POWER_STATE MinPatternWakeUp;
 * NDIS_DEVICE_POWER_STATE MinLinkChangeWakeUp;}
 * NDIS_PM_WAKE_UP_CAPABILITIES, *PNDIS_PM_WAKE_UP_CAPABILITIES;`
 * -- NDIS_DEVICE_POWER_STATE is not printed by any CE page; held. */
typedef struct _NDIS_PM_WAKE_UP_CAPABILITIES NDIS_PM_WAKE_UP_CAPABILITIES,
    *PNDIS_PM_WAKE_UP_CAPABILITIES;

/* ms904096 "NDIS_PNP_CAPABILITIES": print embeds the held
 * NDIS_PM_WAKE_UP_CAPABILITIES by value; held. */
typedef struct _NDIS_PNP_CAPABILITIES NDIS_PNP_CAPABILITIES,
    *PNDIS_PNP_CAPABILITIES;

/* --- Recorded object identifiers (names only). ------------------
 * The CE pages document each OID_* name, purpose and query/set
 * semantics, but no page prints the numeric value, so none are
 * emitted as macros.  (The NDIS data-type pages above are the
 * only printable definitions in this set.)
 *
 * 802 (7):
 *   OID_802_11_FRAGMENTATION_THRESHOLD, OID_802_11_REMOVE_WEP,
 *   OID_802_11_RSSI, OID_802_11_RSSI_TRIGGER, OID_802_11_RTS_THRESHOLD,
 *   OID_802_11_RX_ANTENNA_SELECTED, OID_802_11_TX_ANTENNA_SELECTED
 */

/* "IOCTL_NDIS_GET_LOG_DATA" (Ntddndis.h row): prose page -- the
 * IOCTL value is not printed by any CE page; name recorded. */

/* ------------------------------------------------------------------
 * Book surface: drivers-network-rem (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ------------------------------------------------------------------
 * Book surface: ndis (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
#endif /* AKARI_NTDDNDIS_H */
