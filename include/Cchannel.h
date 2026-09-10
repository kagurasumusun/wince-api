/*
 * Cchannel.h -- Terminal Services virtual-channel client API for
 *               Windows CE (Cchannel.h / Pchannel.h layers).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  Source book: CE 5.0 "Remote Desktop Protocol :: RDP Reference"
 * (tools/manifests/rdp.manifest, 105 leaves); whitespace-preserved
 * prototypes were cross-read against the CE 6.0 (v=winembedded.60) twins
 * (tools/manifests/m54-ce60.manifest).
 *
 * Requirement rows: the VirtualChannel* pages print Header Cchannel.h
 * (Pchannel.h for CHANNEL_DEF / CHANNEL_PDU_HEADER) and "Link Library:
 * Developer implemented" -- the add-in DLL resolves these entry points
 * through the CHANNEL_ENTRY_POINTS structure, so no import-library def
 * is generated (developer-implemented rows carry no library token).
 * OS Versions: "Windows CE .NET 4.0 and later" unless noted otherwise.
 *
 * Derived values (recorded derivation paths, see docs/inventory.md M54):
 *   * CHANNEL_NAME_LEN -- the CE CHANNEL_DEF page (aa513856) prints
 *     "char name[CHANNEL_NAME_LEN + 1]" without a value; the Microsoft
 *     open-specification [MS-RDPBCGR] 2.2.1.3.4.1 "Channel Definition
 *     Structure (CHANNEL_DEF)" publishes name as an 8-byte array of
 *     seven ANSI characters -> CHANNEL_NAME_LEN = 7 (page preserved in
 *     corpus pagesw/openspecs-msrdpbcgr-channel-def.html).
 *   * CHANNEL_OPTION_* -- values published by [MS-RDPBCGR] 2.2.1.3.4.1
 *     (same structure, same flag names; the spec prints
 *     REMOTE_CONTROL_PERSISTENT where the CE page prints
 *     CHANNEL_OPTION_REMOTE_CONTROL_PERSISTENT).
 *   * CHANNEL_FLAG_FIRST/LAST -- values published by [MS-RDPBCGR]
 *     2.2.6.1.1 "Channel PDU Header (CHANNEL_PDU_HEADER)" (page
 *     preserved in corpus pagesw/openspecs-msrdpbcgr-channel-pdu-header.html).
 *   * CHANNEL_FLAG_MIDDLE -- 0: [MS-RDPBCGR] 2.2.6.1.1 "If neither the
 *     CHANNEL_FLAG_FIRST nor the CHANNEL_FLAG_LAST flag is present, the
 *     chunk is from the middle of a sequence".
 *   * CHANNEL_FLAG_ONLY -- (CHANNEL_FLAG_FIRST | CHANNEL_FLAG_LAST):
 *     the CE VirtualChannelOpenEvent page (ms879661) prints "Combines
 *     the CHANNEL_FLAG_FIRST and CHANNEL_FLAG_LAST values".
 *
 * VCAPITYPE: printed by every prototype; its expansion is not published
 * -- mapped to the empty-on-CE convention like WINAPI (windef.h),
 * i.e. the CE default __cdecl.
 *
 * The referral/event callback pointer typedefs
 * (PCHANNEL_INIT_EVENT_FN etc.) are built from the documented event
 * prototypes -- the same model as the M51 IMENUMPROC decision.
 */

#ifndef AKARI_CCHANNEL_H
#define AKARI_CCHANNEL_H

#include "Windef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VCAPITYPE     /* empty on Windows CE (see windef.h) */

/* Virtual-channel name capacity: derived, see header note. */
#define CHANNEL_NAME_LEN  7

/* aa513856 "CHANNEL_DEF" (Pchannel.h): "typedef struct tagCHANNEL_DEF
 * {char name[CHANNEL_NAME_LEN + 1]; ULONG options;} CHANNEL_DEF,
 * *PCHANNEL_DEF, **PPCHANNEL_DEF;".  32-bit size 12, TU-asserted. */
typedef struct tagCHANNEL_DEF {
    char     name[CHANNEL_NAME_LEN + 1];
    ULONG    options;
} CHANNEL_DEF, *PCHANNEL_DEF, **PPCHANNEL_DEF;

/* aa513859 "CHANNEL_PDU_HEADER" (Pchannel.h): "typedef struct
 * tagCHANNEL_PDU_HEADER {UINT32 length; UINT32 flags;}
 * CHANNEL_PDU_HEADER, *PCHANNEL_PDU_HEADER;".  32-bit size 8,
 * TU-asserted. */
typedef struct tagCHANNEL_PDU_HEADER {
    UINT32   length;
    UINT32   flags;
} CHANNEL_PDU_HEADER, *PCHANNEL_PDU_HEADER;

/* ------------------------------------------------------------------ */
/* Channel options (CHANNEL_DEF.options; names on aa513856, values     */
/* derived from [MS-RDPBCGR] 2.2.1.3.4.1 -- see header note).          */
/* ------------------------------------------------------------------ */
#define CHANNEL_OPTION_INITIALIZED           0x80000000
#define CHANNEL_OPTION_ENCRYPT_RDP           0x40000000
#define CHANNEL_OPTION_ENCRYPT_SC            0x20000000
#define CHANNEL_OPTION_ENCRYPT_CS            0x10000000
#define CHANNEL_OPTION_PRI_HIGH              0x08000000
#define CHANNEL_OPTION_PRI_MED               0x04000000
#define CHANNEL_OPTION_PRI_LOW               0x02000000
#define CHANNEL_OPTION_COMPRESS_RDP          0x00800000
#define CHANNEL_OPTION_COMPRESS              0x00400000
#define CHANNEL_OPTION_SHOW_PROTOCOL         0x00200000
#define CHANNEL_OPTION_REMOTE_CONTROL_PERSISTENT 0x00100000

/* ------------------------------------------------------------------ */
/* Data flags (VirtualChannelOpenEvent dataFlags; names on ms879661 /
 * aa514754, values derived -- see header note).                       */
/* ------------------------------------------------------------------ */
#define CHANNEL_FLAG_FIRST      0x00000001
#define CHANNEL_FLAG_LAST       0x00000002
#define CHANNEL_FLAG_MIDDLE     0x00000000
#define CHANNEL_FLAG_ONLY       (CHANNEL_FLAG_FIRST | CHANNEL_FLAG_LAST)

/* HELD (named on the CE pages, values not published -- see
 * docs/inventory.md M54): CHANNEL_MAX_COUNT (ms879621 etc.),
 * CHANNEL_EVENT_CONNECTED / _DISCONNECTED / _INITIALIZED / _TERMINATED
 * / _V1_CONNECTED (ms879628), CHANNEL_EVENT_DATA_RECEIVED /
 * _WRITE_CANCELLED / _WRITE_COMPLETE (ms879661), and the CHANNEL_RC_*
 * return codes (CHANNEL_RC_OK, _ALREADY_INITIALIZED, _ALREADY_CONNECTED,
 * _NOT_IN_VIRTUALCHANNELENTRY, _TOO_MANY_CHANNELS, _BAD_CHANNEL,
 * _BAD_INIT_HANDLE, _BAD_PROC, _BAD_CHANNEL_HANDLE,
 * _UNKNOWN_CHANNEL_NAME). */

/* ------------------------------------------------------------------ */
/* Event callbacks the add-in implements (Cchannel.h).                 */
/* ------------------------------------------------------------------ */

/* ms879628 "VirtualChannelInitEvent": "VOID VCAPITYPE
 * VirtualChannelInitEvent(LPVOID pInitHandle, UINT event, LPVOID pData,
 * UINT dataLength);" -- pointer type PCHANNEL_INIT_EVENT_FN named by
 * the VirtualChannelInit parameter (ms879621). */
typedef VOID (VCAPITYPE *PCHANNEL_INIT_EVENT_FN)(
    LPVOID pInitHandle, UINT event, LPVOID pData, UINT dataLength);

/* ms879661 "VirtualChannelOpenEvent": "VOID VCAPITYPE
 * VirtualChannelOpenEvent(DWORD openHandle, UINT event, LPVOID pData,
 * UINT32 dataLength, UINT32 totalLength, UINT32 dataFlags);" --
 * pointer type PCHANNEL_OPEN_EVENT_FN named by VirtualChannelOpen
 * (ms879649). */
typedef VOID (VCAPITYPE *PCHANNEL_OPEN_EVENT_FN)(
    DWORD openHandle, UINT event, LPVOID pData,
    UINT32 dataLength, UINT32 totalLength, UINT32 dataFlags);

/* aa514727 "VirtualChannelInitEventEx": "typedef VOID VCAPITYPE
 * VirtualChannelInitEventEx(LPVOID lpUserParam, LPVOID pInitHandle,
 * UINT event, LPVOID pData, UINT dataLength);" -- pointer type
 * PCHANNEL_INIT_EVENT_EX_FN named by VirtualChannelInitEx (ms879634). */
typedef VOID (VCAPITYPE *PCHANNEL_INIT_EVENT_EX_FN)(
    LPVOID lpUserParam, LPVOID pInitHandle, UINT event,
    LPVOID pData, UINT dataLength);

/* aa514754 "VirtualChannelOpenEventEx": "typedef VOID VCAPITYPE
 * VirtualChannelOpenEventEx(LPVOID lpUserParam, DWORD openHandle,
 * UINT event, LPVOID pData, UINT32 dataLength, UINT32 totalLength,
 * UINT32 dataFlags);" -- pointer type PCHANNEL_OPEN_EVENT_EX_FN named
 * by VirtualChannelOpenEx (ms879670). */
typedef VOID (VCAPITYPE *PCHANNEL_OPEN_EVENT_EX_FN)(
    LPVOID lpUserParam, DWORD openHandle, UINT event, LPVOID pData,
    UINT32 dataLength, UINT32 totalLength, UINT32 dataFlags);

/* ------------------------------------------------------------------ */
/* Function types named by the entry-points tables (Cchannel.h).       */
/* The base pages print plain prototypes for the non-Ex entry points   */
/* and typedef forms for VirtualChannelInit and the Ex set; the        */
/* typedef'd shapes are reproduced verbatim here.                      */
/* ------------------------------------------------------------------ */

/* ms879621 "VirtualChannelInit": "typedef UINT VCAPITYPE
 * VIRTUALCHANNELINIT(LPVOID FAR * ppInitHandle, PCHANNEL_DEF pChannel,
 * INT channelCount, ULONG versionRequested, PCHANNEL_INIT_EVENT_FN
 * pChannelInitEventProc);". */
typedef UINT VCAPITYPE VIRTUALCHANNELINIT(
    LPVOID FAR *ppInitHandle, PCHANNEL_DEF pChannel, INT channelCount,
    ULONG versionRequested, PCHANNEL_INIT_EVENT_FN pChannelInitEventProc);
typedef VIRTUALCHANNELINIT *PVIRTUALCHANNELINIT;

/* ms879649 "VirtualChannelOpen": "UINT VCAPITYPE VirtualChannelOpen(
 * LPVOID pInitHandle, LPDWORD pOpenHandle, PCHAR pChannelName,
 * PCHANNEL_OPEN_EVENT_FN pChannelOpenEventProc);". */
typedef UINT VCAPITYPE VIRTUALCHANNELOPEN(
    LPVOID pInitHandle, LPDWORD pOpenHandle, PCHAR pChannelName,
    PCHANNEL_OPEN_EVENT_FN pChannelOpenEventProc);
typedef VIRTUALCHANNELOPEN *PVIRTUALCHANNELOPEN;

/* ms864586 "VirtualChannelClose": "UINT VCAPITYPE VirtualChannelClose(
 * DWORD openHandle);". */
typedef UINT VCAPITYPE VIRTUALCHANNELCLOSE(DWORD openHandle);
typedef VIRTUALCHANNELCLOSE *PVIRTUALCHANNELCLOSE;

/* ms879680 "VirtualChannelWrite": "UINT VCAPITYPE VirtualChannelWrite(
 * DWORD openHandle, LPVOID pData, ULONG dataLength, LPVOID pUserData);". */
typedef UINT VCAPITYPE VIRTUALCHANNELWRITE(
    DWORD openHandle, LPVOID pData, ULONG dataLength, LPVOID pUserData);
typedef VIRTUALCHANNELWRITE *PVIRTUALCHANNELWRITE;

/* ms879634 "VirtualChannelInitEx": "typedef UINT VCAPITYPE
 * VIRTUALCHANNELINITEX(LPVOID lpUserParam, LPVOID pInitHandle,
 * PCHANNEL_DEF pChannel, INT channelCount, ULONG versionRequested,
 * PCHANNEL_INIT_EVENT_EX_FN pChannelInitEventProcEx);". */
typedef UINT VCAPITYPE VIRTUALCHANNELINITEX(
    LPVOID lpUserParam, LPVOID pInitHandle, PCHANNEL_DEF pChannel,
    INT channelCount, ULONG versionRequested,
    PCHANNEL_INIT_EVENT_EX_FN pChannelInitEventProcEx);
typedef VIRTUALCHANNELINITEX *PVIRTUALCHANNELINITEX;

/* ms879670 "VirtualChannelOpenEx": "typedef UINT VCAPITYPE
 * VIRTUALCHANNELOPENEX( LPVOID pInitHandle, LPDWORD pOpenHandle,
 * PCHAR pChannelName, PCHANNEL_OPEN_EVENT_EX_FN pChannelOpenEventProcEx);". */
typedef UINT VCAPITYPE VIRTUALCHANNELOPENEX(
    LPVOID pInitHandle, LPDWORD pOpenHandle, PCHAR pChannelName,
    PCHANNEL_OPEN_EVENT_EX_FN pChannelOpenEventProcEx);
typedef VIRTUALCHANNELOPENEX *PVIRTUALCHANNELOPENEX;

/* ms864696 "VirtualChannelCloseEx": "typedef UINT VCAPITYPE
 * VIRTUALCHANNELCLOSEEX(LPVOID pInitHandle, DWORD openHandle);". */
typedef UINT VCAPITYPE VIRTUALCHANNELCLOSEEX(
    LPVOID pInitHandle, DWORD openHandle);
typedef VIRTUALCHANNELCLOSEEX *PVIRTUALCHANNELCLOSEEX;

/* ms879690 "VirtualChannelWriteEx": "typedef UINT VCAPITYPE
 * VIRTUALCHANNELWRITEEX( LPVOID pInitHandle, DWORD openHandle,
 * LPVOID pData, ULONG dataLength, LPVOID pUserData);". */
typedef UINT VCAPITYPE VIRTUALCHANNELWRITEEX(
    LPVOID pInitHandle, DWORD openHandle, LPVOID pData,
    ULONG dataLength, LPVOID pUserData);
typedef VIRTUALCHANNELWRITEEX *PVIRTUALCHANNELWRITEEX;

/* ------------------------------------------------------------------ */
/* The entry-points tables the client passes to the add-in            */
/* (after the function types their members point to).                  */
/* ------------------------------------------------------------------ */

/* aa513858 "CHANNEL_ENTRY_POINTS" (Cchannel.h): "typedef struct
 * tagCHANNEL_ENTRY_POINTS {DWORD cbSize; DWORD protocolVersion;
 * PVIRTUALCHANNELINIT pVirtualChannelInit; PVIRTUALCHANNELOPEN
 * pVirtualChannelOpen; PVIRTUALCHANNELCLOSE pVirtualChannelClose;
 * PVIRTUALCHANNELWRITE pVirtualChannelWrite;} CHANNEL_ENTRY_POINTS,
 * *PCHANNEL_ENTRY_POINTS;".  32-bit size 24, TU-asserted. */
typedef struct tagCHANNEL_ENTRY_POINTS {
    DWORD    cbSize;
    DWORD    protocolVersion;
    PVIRTUALCHANNELINIT   pVirtualChannelInit;
    PVIRTUALCHANNELOPEN   pVirtualChannelOpen;
    PVIRTUALCHANNELCLOSE  pVirtualChannelClose;
    PVIRTUALCHANNELWRITE  pVirtualChannelWrite;
} CHANNEL_ENTRY_POINTS, *PCHANNEL_ENTRY_POINTS;

/* aa513861 "CHANNEL_ENTRY_POINTS_EX" (Cchannel.h): "typedef struct
 * tagCHANNEL_ENTRY_POINTS_EX { DWORD cbSize; DWORD protocolVersion;
 * PVIRTUALCHANNELINITEX pVirtualChannelInitEx; PVIRTUALCHANNELOPENEX
 * pVirtualChannelOpenEx; PVIRTUALCHANNELCLOSEEX pVirtualChannelCloseEx;
 * PVIRTUALCHANNELWRITEEX pVirtualChannelWriteEx;}
 * CHANNEL_ENTRY_POINTS_EX, FAR * PCHANNEL_ENTRY_POINTS_EX;".  32-bit
 * size 24, TU-asserted. */
typedef struct tagCHANNEL_ENTRY_POINTS_EX {
    DWORD    cbSize;
    DWORD    protocolVersion;
    PVIRTUALCHANNELINITEX   pVirtualChannelInitEx;
    PVIRTUALCHANNELOPENEX   pVirtualChannelOpenEx;
    PVIRTUALCHANNELCLOSEEX  pVirtualChannelCloseEx;
    PVIRTUALCHANNELWRITEEX  pVirtualChannelWriteEx;
} CHANNEL_ENTRY_POINTS_EX, *PCHANNEL_ENTRY_POINTS_EX;

/* ------------------------------------------------------------------ */
/* The add-in's exported entry points (developer implemented).         */
/* ------------------------------------------------------------------ */

/* ms879597 "VirtualChannelEntry": "BOOL VCAPITYPE VirtualChannelEntry(
 * PCHANNEL_ENTRY_POINTS pEntryPoints);". */
BOOL VCAPITYPE VirtualChannelEntry(PCHANNEL_ENTRY_POINTS pEntryPoints);

/* ms879610 "VirtualChannelEntryEx": "typedef BOOL VCAPITYPE
 * VIRTUALCHANNELENTRYEX(PCHANNEL_ENTRY_POINTS_EX pEntryPointsEx,
 * PVOID pInitHandle);". */
typedef BOOL VCAPITYPE VIRTUALCHANNELENTRYEX(
    PCHANNEL_ENTRY_POINTS_EX pEntryPointsEx, PVOID pInitHandle);

/* ms879628 "VirtualChannelInitEvent": event callback prototype (see
 * the PCHANNEL_INIT_EVENT_FN note above). */
VOID VCAPITYPE VirtualChannelInitEvent(LPVOID pInitHandle, UINT event,
                                       LPVOID pData, UINT dataLength);

/* ms879661 "VirtualChannelOpenEvent": event callback prototype (see
 * the PCHANNEL_OPEN_EVENT_FN note above). */
VOID VCAPITYPE VirtualChannelOpenEvent(DWORD openHandle, UINT event,
                                       LPVOID pData, UINT32 dataLength,
                                       UINT32 totalLength,
                                       UINT32 dataFlags);

/* ------------------------------------------------------------------
 * Book surface: rdp (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms861195 Bitmap and Caching Properties of IMsRdpClientAdvancedSettings */
/* ms861243 Connection, Timeout, Interval and Event Properties of IMsRdpClientAdvancedSettings */
/* aa513922 IMsRdpClient Properties (Header: Discodlg.h. Mstsax.idl.) */
/* aa513913 IMsRdpClient::get_ExtendedDisconnectReason (Header: Discodlg.h. Mstsax.idl.) */
/* aa513915 IMsRdpClient::GetVirtualChannelOptions (Header: Discodlg.h. Mstsax.idl.) */
/* aa513927 IMsRdpClient::RequestClose (Header: Discodlg.h. Mstsax.idl.) */
/* aa513936 IMsRdpClient::SetVirtualChannelOptions (Header: Discodlg.h. Mstsax.idl.) */
/* aa513909 IMsRdpClientAdvancedSettings Properties */
/* aa513910 IMsRdpClientAdvancedSettings Property Descriptions */
/* aa513918 IMsRdpClientNonScriptable::NotifyRedirectDeviceChange (Header: Discodlg.h. Mstsax.idl.) */
/* aa513920 IMsRdpClientNonScriptable::SendKeys (Header: Discodlg.h. Mstsax.idl.) */
/* aa513933 IMsRdpClientSecuredSettings Properties (Header: Discodlg.h. Mstsax.idl.) */
/* aa513942 IMsTscAdvancedSettings::get_allowBackgroundInput (Header: Discodlg.h. Mstsax.idl.) */
/* aa513944 IMsTscAdvancedSettings::get_BitmapPersistence (Header: Discodlg.h. Mstsax.idl.) */
/* aa513946 IMsTscAdvancedSettings::get_Compress (Header: Discodlg.h. Mstsax.idl.) */
/* aa513948 IMsTscAdvancedSettings::get_ContainerHandledFullScreen (Header: Discodlg.h. Mstsax.idl.) */
/* aa513952 IMsTscAdvancedSettings::get_DisableRdpdr (Header: Discodlg.h. Mstsax.idl.) */
/* aa513953 IMsTscAdvancedSettings::put_allowBackgroundInput (Header: Discodlg.h. Mstsax.idl.) */
/* aa513954 IMsTscAdvancedSettings::put_BitmapPersistence (Header: Discodlg.h. Mstsax.idl.) */
/* aa513955 IMsTscAdvancedSettings::put_Compress (Header: Discodlg.h. Mstsax.idl.) */
/* aa513956 IMsTscAdvancedSettings::put_ContainerHandledFullScreen (Header: Discodlg.h. Mstsax.idl.) */
/* aa513958 IMsTscAdvancedSettings::put_IconFile (Header: Discodlg.h. Mstsax.idl.) */
/* aa513959 IMsTscAdvancedSettings::put_IconIndex (Header: Discodlg.h. Mstsax.idl.) */
/* aa513960 IMsTscAdvancedSettings::put_KeyBoardLayoutStr (Header: Discodlg.h. Mstsax.idl.) */
/* aa513961 IMsTscAdvancedSettings::put_PluginDlls (Header: Discodlg.h. Mstsax.idl.) */
/* aa513963 IMsTscAx::Connect (Header: Discodlg.h. Mstsax.idl.) */
/* aa513964 IMsTscAx::CreateVirtualChannels (Header: Discodlg.h. Mstsax.idl.) */
/* aa513965 IMsTscAx::Disconnect (Header: Discodlg.h. Mstsax.idl.) */
/* aa513976 IMsTscAx::get_AdvancedSettings (Header: Discodlg.h. Mstsax.idl.) */
/* aa513977 IMsTscAx::get_CipherStrength (Header: Discodlg.h. Mstsax.idl.) */
/* aa514247 IMsTscAx::get_Connected (Header: Discodlg.h. Mstsax.idl.) */
/* aa514248 IMsTscAx::get_ConnectingText (Header: Discodlg.h. Mstsax.idl.) */
/* aa514249 IMsTscAx::get_DesktopHeight (Header: Discodlg.h. Mstsax.idl.) */
/* aa514250 IMsTscAx::get_DesktopWidth (Header: Discodlg.h. Mstsax.idl.) */
/* aa514252 IMsTscAx::get_DisconnectedText (Header: Discodlg.h. Mstsax.idl.) */
/* aa514253 IMsTscAx::get_Domain (Header: Discodlg.h. Mstsax.idl.) */
/* aa514254 IMsTscAx::get_HorizontalScrollBarVisible (Header: Discodlg.h. Mstsax.idl.) */
/* aa514256 IMsTscAx::get_SecuredSettings2 (Header: Discodlg.h. Mstsax.idl.) */
/* aa514258 IMsTscAx::get_Server (Header: Discodlg.h. Mstsax.idl.) */
/* aa514260 IMsTscAx::get_UserName (Header: Discodlg.h. Mstsax.idl.) */
/* aa514262 IMsTscAx::get_Version (Header: Discodlg.h. Mstsax.idl.) */
/* aa514265 IMsTscAx::get_VerticalScrollBarVisible (Header: Discodlg.h. Mstsax.idl.) */
/* aa514268 IMsTscAx::put_ConnectingText (Header: Discodlg.h. Mstsax.idl.) */
/* aa514270 IMsTscAx::put_DisconnectedText (Header: Discodlg.h. Mstsax.idl.) */
/* aa514271 IMsTscAx::put_Domain (Header: Discodlg.h. Mstsax.idl.) */
/* aa514273 IMsTscAx::put_Server (Header: Discodlg.h. Mstsax.idl.) */
/* aa514276 IMsTscAx::put_UserName (Header: Discodlg.h. Mstsax.idl.) */
/* aa514278 IMsTscAx::SendOnVirtualChannel (Header: Discodlg.h. Mstsax.idl.) */
/* aa513967 IMsTscAxEvents::OnConfirmClose (Header: Discodlg.h. Mstsax.idl.) */
/* aa513968 IMsTscAxEvents::OnConnected (Header: Discodlg.h. Mstsax.idl.) */
/* aa513969 IMsTscAxEvents::OnConnecting (Header: Discodlg.h. Mstsax.idl.) */
/* aa513970 IMsTscAxEvents::OnDisconnected (Header: Discodlg.h. Mstsax.idl.) */
/* aa513971 IMsTscAxEvents::OnFatalError (Header: Discodlg.h. Mstsax.idl.) */
/* aa513972 IMsTscAxEvents::OnIdleTimeoutNotification (Header: Discodlg.h. Mstsax.idl.) */
/* aa513973 IMsTscAxEvents::OnLoginComplete (Header: Discodlg.h. Mstsax.idl.) */
/* aa513974 IMsTscAxEvents::OnRequestContainerMinimize (Header: Discodlg.h. Mstsax.idl.) */
/* aa513975 IMsTscAxEvents::OnWarning (Header: Discodlg.h. Mstsax.idl.) */
/* aa514281 IMsTscNonScriptable::get_BinaryPassword (Header: Discodlg.h. Mstsax.idl.) */
/* aa514283 IMsTscNonScriptable::get_BinarySalt (Header: Discodlg.h. Mstsax.idl.) */
/* aa514285 IMsTscNonScriptable::get_PortablePassword (Header: Discodlg.h. Mstsax.idl.) */
/* aa514287 IMsTscNonScriptable::get_PortableSalt (Header: Discodlg.h. Mstsax.idl.) */
/* aa514289 IMsTscNonScriptable::put_BinaryPassword (Header: Discodlg.h. Mstsax.idl.) */
/* aa514290 IMsTscNonScriptable::put_BinarySalt (Header: Discodlg.h. Mstsax.idl.) */
/* aa514292 IMsTscNonScriptable::put_ClearTextPassword (Header: Discodlg.h. Mstsax.idl.) */
/* aa514295 IMsTscNonScriptable::put_PortablePassword (Header: Discodlg.h. Mstsax.idl.) */
/* aa514297 IMsTscNonScriptable::put_PortableSalt (Header: Discodlg.h. Mstsax.idl.) */
/* aa514299 IMsTscNonScriptable::ResetPassword (Header: Discodlg.h. Mstsax.idl.) */
/* aa514302 IMsTscSecuredSettings::get_StartProgram (Header: Discodlg.h. Mstsax.idl.) */
/* aa514303 IMsTscSecuredSettings::get_WorkDir (Header: Discodlg.h. Mstsax.idl.) */
/* aa514305 IMsTscSecuredSettings::put_StartProgram (Header: Discodlg.h. Mstsax.idl.) */
/* aa514307 IMsTscSecuredSettings::put_WorkDir (Header: Discodlg.h. Mstsax.idl.) */
/* aa514412 Keyboard and Mouse Properties of IMsRdpClientAdvancedSettings */
/* aa514423 Other IMsRdpClientAdvancedSettings Properties */
/* aa513318 RDP Functions */
/* aa513320 RDP Structures */
/* ms861737 Redirection Properties of IMsRdpClientAdvancedSettings */
/* ms861766 Remote Desktop ActiveX Control Interface */

/* ------------------------------------------------------------------
 * Book surface: rdp (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms861195 Bitmap and Caching Properties of IMsRdpClientAdvancedSettings */
/* ms861243 Connection, Timeout, Interval and Event Properties of IMsRdpClientAdvancedSettings */
/* aa513922 IMsRdpClient Properties (Header: Discodlg.h. Mstsax.idl.) */
/* aa513913 IMsRdpClient::get_ExtendedDisconnectReason (Header: Discodlg.h. Mstsax.idl.) */
/* aa513915 IMsRdpClient::GetVirtualChannelOptions (Header: Discodlg.h. Mstsax.idl.) */
/* aa513927 IMsRdpClient::RequestClose (Header: Discodlg.h. Mstsax.idl.) */
/* aa513936 IMsRdpClient::SetVirtualChannelOptions (Header: Discodlg.h. Mstsax.idl.) */
/* aa513909 IMsRdpClientAdvancedSettings Properties */
/* aa513910 IMsRdpClientAdvancedSettings Property Descriptions */
/* aa513918 IMsRdpClientNonScriptable::NotifyRedirectDeviceChange (Header: Discodlg.h. Mstsax.idl.) */
/* aa513920 IMsRdpClientNonScriptable::SendKeys (Header: Discodlg.h. Mstsax.idl.) */
/* aa513933 IMsRdpClientSecuredSettings Properties (Header: Discodlg.h. Mstsax.idl.) */
/* aa513942 IMsTscAdvancedSettings::get_allowBackgroundInput (Header: Discodlg.h. Mstsax.idl.) */
/* aa513944 IMsTscAdvancedSettings::get_BitmapPersistence (Header: Discodlg.h. Mstsax.idl.) */
/* aa513946 IMsTscAdvancedSettings::get_Compress (Header: Discodlg.h. Mstsax.idl.) */
/* aa513948 IMsTscAdvancedSettings::get_ContainerHandledFullScreen (Header: Discodlg.h. Mstsax.idl.) */
/* aa513952 IMsTscAdvancedSettings::get_DisableRdpdr (Header: Discodlg.h. Mstsax.idl.) */
/* aa513953 IMsTscAdvancedSettings::put_allowBackgroundInput (Header: Discodlg.h. Mstsax.idl.) */
/* aa513954 IMsTscAdvancedSettings::put_BitmapPersistence (Header: Discodlg.h. Mstsax.idl.) */
/* aa513955 IMsTscAdvancedSettings::put_Compress (Header: Discodlg.h. Mstsax.idl.) */
/* aa513956 IMsTscAdvancedSettings::put_ContainerHandledFullScreen (Header: Discodlg.h. Mstsax.idl.) */
/* aa513958 IMsTscAdvancedSettings::put_IconFile (Header: Discodlg.h. Mstsax.idl.) */
/* aa513959 IMsTscAdvancedSettings::put_IconIndex (Header: Discodlg.h. Mstsax.idl.) */
/* aa513960 IMsTscAdvancedSettings::put_KeyBoardLayoutStr (Header: Discodlg.h. Mstsax.idl.) */
/* aa513961 IMsTscAdvancedSettings::put_PluginDlls (Header: Discodlg.h. Mstsax.idl.) */
/* aa513963 IMsTscAx::Connect (Header: Discodlg.h. Mstsax.idl.) */
/* aa513964 IMsTscAx::CreateVirtualChannels (Header: Discodlg.h. Mstsax.idl.) */
/* aa513965 IMsTscAx::Disconnect (Header: Discodlg.h. Mstsax.idl.) */
/* aa513976 IMsTscAx::get_AdvancedSettings (Header: Discodlg.h. Mstsax.idl.) */
/* aa513977 IMsTscAx::get_CipherStrength (Header: Discodlg.h. Mstsax.idl.) */
/* aa514247 IMsTscAx::get_Connected (Header: Discodlg.h. Mstsax.idl.) */
/* aa514248 IMsTscAx::get_ConnectingText (Header: Discodlg.h. Mstsax.idl.) */
/* aa514249 IMsTscAx::get_DesktopHeight (Header: Discodlg.h. Mstsax.idl.) */
/* aa514250 IMsTscAx::get_DesktopWidth (Header: Discodlg.h. Mstsax.idl.) */
/* aa514252 IMsTscAx::get_DisconnectedText (Header: Discodlg.h. Mstsax.idl.) */
/* aa514253 IMsTscAx::get_Domain (Header: Discodlg.h. Mstsax.idl.) */
/* aa514254 IMsTscAx::get_HorizontalScrollBarVisible (Header: Discodlg.h. Mstsax.idl.) */
/* aa514256 IMsTscAx::get_SecuredSettings2 (Header: Discodlg.h. Mstsax.idl.) */
/* aa514258 IMsTscAx::get_Server (Header: Discodlg.h. Mstsax.idl.) */
/* aa514260 IMsTscAx::get_UserName (Header: Discodlg.h. Mstsax.idl.) */
/* aa514262 IMsTscAx::get_Version (Header: Discodlg.h. Mstsax.idl.) */
/* aa514265 IMsTscAx::get_VerticalScrollBarVisible (Header: Discodlg.h. Mstsax.idl.) */
/* aa514268 IMsTscAx::put_ConnectingText (Header: Discodlg.h. Mstsax.idl.) */
/* aa514270 IMsTscAx::put_DisconnectedText (Header: Discodlg.h. Mstsax.idl.) */
/* aa514271 IMsTscAx::put_Domain (Header: Discodlg.h. Mstsax.idl.) */
/* aa514273 IMsTscAx::put_Server (Header: Discodlg.h. Mstsax.idl.) */
/* aa514276 IMsTscAx::put_UserName (Header: Discodlg.h. Mstsax.idl.) */
/* aa514278 IMsTscAx::SendOnVirtualChannel (Header: Discodlg.h. Mstsax.idl.) */
/* aa513967 IMsTscAxEvents::OnConfirmClose (Header: Discodlg.h. Mstsax.idl.) */
/* aa513968 IMsTscAxEvents::OnConnected (Header: Discodlg.h. Mstsax.idl.) */
/* aa513969 IMsTscAxEvents::OnConnecting (Header: Discodlg.h. Mstsax.idl.) */
/* aa513970 IMsTscAxEvents::OnDisconnected (Header: Discodlg.h. Mstsax.idl.) */
/* aa513971 IMsTscAxEvents::OnFatalError (Header: Discodlg.h. Mstsax.idl.) */
/* aa513972 IMsTscAxEvents::OnIdleTimeoutNotification (Header: Discodlg.h. Mstsax.idl.) */
/* aa513973 IMsTscAxEvents::OnLoginComplete (Header: Discodlg.h. Mstsax.idl.) */
/* aa513974 IMsTscAxEvents::OnRequestContainerMinimize (Header: Discodlg.h. Mstsax.idl.) */
/* aa513975 IMsTscAxEvents::OnWarning (Header: Discodlg.h. Mstsax.idl.) */
/* aa514281 IMsTscNonScriptable::get_BinaryPassword (Header: Discodlg.h. Mstsax.idl.) */
/* aa514283 IMsTscNonScriptable::get_BinarySalt (Header: Discodlg.h. Mstsax.idl.) */
/* aa514285 IMsTscNonScriptable::get_PortablePassword (Header: Discodlg.h. Mstsax.idl.) */
/* aa514287 IMsTscNonScriptable::get_PortableSalt (Header: Discodlg.h. Mstsax.idl.) */
/* aa514289 IMsTscNonScriptable::put_BinaryPassword (Header: Discodlg.h. Mstsax.idl.) */
/* aa514290 IMsTscNonScriptable::put_BinarySalt (Header: Discodlg.h. Mstsax.idl.) */
/* aa514292 IMsTscNonScriptable::put_ClearTextPassword (Header: Discodlg.h. Mstsax.idl.) */
/* aa514295 IMsTscNonScriptable::put_PortablePassword (Header: Discodlg.h. Mstsax.idl.) */
/* aa514297 IMsTscNonScriptable::put_PortableSalt (Header: Discodlg.h. Mstsax.idl.) */
/* aa514299 IMsTscNonScriptable::ResetPassword (Header: Discodlg.h. Mstsax.idl.) */
/* aa514302 IMsTscSecuredSettings::get_StartProgram (Header: Discodlg.h. Mstsax.idl.) */
/* aa514303 IMsTscSecuredSettings::get_WorkDir (Header: Discodlg.h. Mstsax.idl.) */
/* aa514305 IMsTscSecuredSettings::put_StartProgram (Header: Discodlg.h. Mstsax.idl.) */
/* aa514307 IMsTscSecuredSettings::put_WorkDir (Header: Discodlg.h. Mstsax.idl.) */
/* aa514412 Keyboard and Mouse Properties of IMsRdpClientAdvancedSettings */
/* aa514423 Other IMsRdpClientAdvancedSettings Properties */
/* aa513318 RDP Functions */
/* aa513320 RDP Structures */
/* ms861737 Redirection Properties of IMsRdpClientAdvancedSettings */
/* ms861766 Remote Desktop ActiveX Control Interface */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_CCHANNEL_H */
