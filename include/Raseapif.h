/* Raseapif.h -- RAS Extensible Authentication Protocol types
 * (Windows CE; no import surface -- the RasEap* entry points are
 * members of PPP_EAP_INFO, implemented by the EAP DLL).
 * See docs/inventory.md M77c. */

#ifndef AKARI_RASEAPIF_H
#define AKARI_RASEAPIF_H

#include "Windef.h"    /* DWORD, BOOL, BYTE, WCHAR, HANDLE, PVOID,
                        * PBYTE, VOID */

/* "RAS_AUTH_ATTRIBUTE_TYPE": print (explicit value anchors as
 * printed; sequential between anchors). */
typedef enum _RAS_AUTH_ATTRIBUTE_TYPE_ {
    raatMinimum = 0,
    raatUserName,
    raatUserPassword,
    raatMD5CHAPPassword,
    raatNASIPAddress,
    raatNASPort,
    raatServiceType,
    raatFramedProtocol,
    raatFramedIPAddress,
    raatFramedIPNetmask,
    raatFramedRouting = 10,
    raatFilterId,
    raatFramedMTU,
    raatFramedCompression,
    raatLoginIPHost,
    raatLoginService,
    raatLoginTCPPort,
    raatUnassigned17,
    raatReplyMessage,
    raatCallbackNumber = 20,
    raatCallbackId,
    raatUnassigned21,
    raatFramedRoute,
    raatFramedIPXNetwork,
    raatState,
    raatClass,
    raatVendorSpecific,
    raatSessionTimeout,
    raatIdleTimeout,
    raatTerminationAction,
    raatCalledStationId = 30,
    raatCallingStationId,
    raatNASIdentifier,
    raatProxyState,
    raatLoginLATService,
    raatLoginLATNode,
    raatLoginLATGroup,
    raatFramedAppleTalkLink,
    raatFramedAppleTalkNetwork,
    raatFramedAppleTalkZone,
    raatAcctStatusType = 40,
    raatAcctDelayTime,
    raatAcctInputOctets,
    raatAcctOutputOctets,
    raatAcctSessionId,
    raatAcctAuthentic,
    raatAcctSessionTime,
    raatAcctInputPackets,
    raatAcctOutputPackets,
    raatAcctTerminateCause,
    raatAcctMultiSessionId = 50,
    raatAcctLinkCount,
    raatAcctEventTimeStamp = 55,
    raatMD5CHAPChallenge = 60,
    raatNASPortType,
    raatPortLimit,
    raatLoginLATPort,
    raatTunnelType,
    raatTunnelMediumType,
    raatTunnelClientEndpoint,
    raatTunnelServerEndpoint,
    raatARAPPassword = 70,
    raatARAPFeatures,
    raatARAPZoneAccess,
    raatARAPSecurity,
    raatARAPSecurityData,
    raatPasswordRetry,
    raatPrompt,
    raatConnectInfo,
    raatConfigurationToken,
    raatEAPMessage,
    raatSignature = 80,
    raatARAPChallengeResponse = 84,
    raatAcctInterimInterval = 85,
    raatARAPGuestLogon = 8096,
    raatReserved = 0xFFFFFFFF,
} RAS_AUTH_ATTRIBUTE_TYPE;

/* "RAS_AUTH_ATTRIBUTE": print. */
typedef struct _RAS_AUTH_ATTRIBUTE {
    RAS_AUTH_ATTRIBUTE_TYPE raaType;
    DWORD                   dwLength;
    PVOID                   Value;
} RAS_AUTH_ATTRIBUTE, *PRAS_AUTH_ATTRIBUTE;

/* "PPP_EAP_PACKET": print (pointer typedef really is *PPPP_EAP_PACKET). */
typedef struct _PPP_EAP_PACKET {
    BYTE Code;
    BYTE Id;
    BYTE Length[2];
    BYTE Data[1];
} PPP_EAP_PACKET, *PPPP_EAP_PACKET;   /* pointer spelling as printed (4 P) */

/* "PPP_EAP_ACTION": print (sequential). */
typedef enum _PPP_EAP_ACTION {
    EAPACTION_NoAction,
    EAPACTION_Authenticate,
    EAPACTION_Done,
    EAPACTION_SendAndDone,
    EAPACTION_Send,
    EAPACTION_SendWithTimeout,
    EAPACTION_SendWithTimeoutInteractive
} PPP_EAP_ACTION;

/* "PPP_EAP_INPUT": print. */
typedef struct _PPP_EAP_INPUT {
    DWORD               dwSizeInBytes;
    DWORD               fFlags;
    BOOL                fAuthenticator;
    WCHAR              *pwszIdentity;
    WCHAR              *pwszPassword;
    BYTE                bInitialId;
    RAS_AUTH_ATTRIBUTE *pUserAttributes;
    BOOL                fAuthenticationComplete;
    DWORD               dwAuthResultCode;
    HANDLE              hTokenImpersonateUser;
    BOOL                fSuccessPacketReceived;
    BOOL                fDataReceivedFromInteractiveUI;
    PBYTE               pDataFromInteractiveUI;
    DWORD               dwSizeOfDataFromInteractiveUI;
    PBYTE               pConnectionData;
    DWORD               dwSizeOfConnectionData;
    PBYTE               pUserData;
    DWORD               dwSizeOfUserData;
    HANDLE              hReserved;
} PPP_EAP_INPUT, *PPPP_EAP_INPUT;   /* pointer spelling as printed (4 P) */

/* "PPP_EAP_OUTPUT": print (pointer typedef really is *PPPP_EAP_OUTPUT). */
typedef struct _PPP_EAP_OUTPUT {
    DWORD               dwSizeInBytes;
    PPP_EAP_ACTION      Action;
    DWORD               dwAuthResultCode;
    RAS_AUTH_ATTRIBUTE *pUserAttributes;
    BOOL                fInvokeInteractiveUI;
    PBYTE               pUIContextData;
    DWORD               dwSizeOfUIContextData;
    BOOL                fSaveConnectionData;
    PBYTE               pConnectionData;
    DWORD               dwSizeOfConnectionData;
    BOOL                fSaveUserData;
    PBYTE               pUserData;
    DWORD               dwSizeOfUserData;
} PPP_EAP_OUTPUT, *PPPP_EAP_OUTPUT;  /* pointer spelling as printed (4 P) */

/* "PPP_EAP_INFO": print (RasEap* member signatures verbatim). */
typedef struct _PPP_EAP_INFO {
    DWORD dwSizeInBytes;
    DWORD dwEapTypeId;
    DWORD (*RasEapInitialize)(BOOL fInitialize);
    DWORD (*RasEapBegin)(VOID **ppWorkBuffer,
                         PPP_EAP_INPUT *pPppEapInput);
    DWORD (*RasEapEnd)(VOID *pWorkBuffer);
    DWORD (*RasEapMakeMessage)(VOID *pWorkBuf,
                    PPP_EAP_PACKET *pReceivePacket,
                    PPP_EAP_PACKET *pSendPacket,
                    DWORD cbSendPacket,
                    PPP_EAP_OUTPUT *pEapOutput,
                    PPP_EAP_INPUT *pEapInput);
} PPP_EAP_INFO, *PPPP_EAP_INFO;     /* pointer spelling as printed (4 P) */

#endif /* AKARI_RASEAPIF_H */
