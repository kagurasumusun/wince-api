/*
 * dvddrvr.h -- DVD-Video renderer interfaces for Windows CE
 * (Dvddrvr.idl layer).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs).  Source book: CE 5.0 "DVD-Video Renderer Reference" (the
 * Dvddrvr.idl leaves of tools/manifests/dvd.manifest, fetched M57 for
 * M58).  OS Versions: "Windows CE .NET 4.0 and later".
 *
 * IDMAChannel / IBitstreamProcessor / IDVDRenderer are IDL interfaces
 * (vtable methods, IUnknown-derived) with no Link Library rows and no
 * published vtable order -- the M44/M53/M54/M57 def-less opaque record
 * model: opaque types, method signatures recorded in comments.  Nothing
 * here enters a def.
 *
 * The capability masks are printed with values by ms892143 (the
 * DVD-Video Renderer Macros page); the enumerations print their values
 * (implicit successors where not explicit).
 *
 * Held families (names documented, values/layouts not published -- see
 * docs/inventory.md M58): the interface identifiers IID_IDMAChannel /
 * IID_IBitstreamProcessor / IID_IDVDRenderer / IID_IDVDDecoderCSS
 * (ms892115) are names-only (no GUID values printed); the
 * NOTIFICATION_CALLBACK callback type of IDMAChannel::SetThresholdCallback
 * (ms900179) has no page.
 */

#ifndef AKARI_DVDDRVRR_H
#define AKARI_DVDDRVRR_H

#include "Windef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Enumerations (DVD-Video Renderer Enumerations).                     */
/* ------------------------------------------------------------------ */

/* aa447766 "EDVDAspectRatioMode". */
typedef enum {
    DVD_ASPECT_RATIO_MODE_LETTERBOX,   /* 0 (implicit) */
    DVD_ASPECT_RATIO_MODE_PANSCAN      /* 1 */
} EDVDAspectRatioMode;

/* aa447767 "EDVDAudioFreq". */
typedef enum {
    DVD_AUDIO_FREQ_48KHZ,              /* 0 (implicit) */
    DVD_AUDIO_FREQ_96KHZ               /* 1 */
} EDVDAudioFreq;

/* aa447768 "EDVDAudioStreamType": AC3 = 2, then implicit successors. */
typedef enum {
    DVD_AUDIO_TYPE_AC3  = 2,
    DVD_AUDIO_TYPE_MPEG,               /* 3 */
    DVD_AUDIO_TYPE_LPCM,               /* 4 */
    DVD_AUDIO_TYPE_DTS,                /* 5 */
    DVD_AUDIO_TYPE_SDDS                /* 6 */
} EDVDAudioStreamType;

/* aa447769 "EDVDDisplayAspectRatio": 4x3 = 0, 16x9 = 0x3 as printed.
 * The SetContentAspectRatio (ms901312) and SetDisplayAspectRatio
 * (ms901323) pages list the same two values under the spellings
 * DISPLAY_ASPECT_4_3 / DISPLAY_ASPECT_16_9_DOWNSAMPLE_4_3 -- page
 * spellings recorded here; the enum page's names are the ones shipped. */
typedef enum {
    DVD_DISPLAY_ASPECT_4x3 = 0,
    DVD_DISPLAY_ASPECT_16x9 = 0x3
} EDVDDisplayAspectRatio;

/* aa447780 "EDVDLpcmQuantization". */
typedef enum {
    DVD_LPCM_16,                       /* 0 (implicit) */
    DVD_LPCM_20,                       /* 1 */
    DVD_LPCM_24                        /* 2 */
} EDVDLpcmQuantization;

/* aa447781 "EDVDSyncEventType". */
typedef enum {
    DVD_NAV_PACK_EVENT,                /* 0 (implicit) */
    DVD_HIGHLIGHT_EVENT,               /* 1 */
    DVD_PLAYBACK_EVENT,                /* 2 */
    DVD_CC_DATA_EVENT                  /* 3 */
} EDVDSyncEventType;

/* aa447783 "EHighlightAction": HIGHLIGHT_SELECT = 1, then implicit
 * successors. */
typedef enum {
    HIGHLIGHT_SELECT = 1,
    UNHIGHLIGHT,                       /* 2 */
    ACTIVATE_BUTTON,                   /* 3 */
    ACTIVATE_SELECTED,                 /* 4 */
    SELECT_AUTO_ACTIVATED              /* 5 */
} EHighlightAction;

/* ------------------------------------------------------------------ */
/* Capability masks (DVD-Video Renderer Macros page prints the values).*/
/* ------------------------------------------------------------------ */

/* ms892143: audio capability bits of IDVDRenderer::GetAudioCaps
 * (ms900194). */
#define DVD_AUDIOCAP_AC3           0x4000
#define DVD_AUDIOCAP_MPEG          0x1000
#define DVD_AUDIOCAP_DTS           0x0800
#define DVD_AUDIOCAP_SDDS          0x0400
#define DVD_AUDIOCAP_LPCM_KARAOKE  0x0080
#define DVD_AUDIOCAP_AC3_KARAOKE   0x0040
#define DVD_AUDIOCAP_MPEG_KARAOKE  0x0010
#define DVD_AUDIOCAP_DTS_KARAOKE   0x0008
#define DVD_AUDIOCAP_SDDS_KARAOKE  0x0004

/* ms892143: scan capability bits of IDVDRenderer::GetScanCaps
 * (ms900196). */
#define DVD_SCANCAP_FORWARD_SCAN   0x1
#define DVD_SCANCAP_FORWARD_SLOW   0x2
#define DVD_SCANCAP_FORWARD_SINGLE 0x4
#define DVD_SCANCAP_BACKWARD_SCAN  0x8
#define DVD_SCANCAP_BACKWARD_SLOW  0x10
#define DVD_SCANCAP_BACKWARD_SINGLE 0x20

/* ------------------------------------------------------------------ */
/* Opaque interface records (M44/M53/M54/M57 model).                   */
/* ------------------------------------------------------------------ */

/* ms900175 "IDMAChannel" (Dvddrvr.idl; IUnknown-derived; obtained via
 * QueryInterface with the IID_IDMACHANNEL identifier, ms892115 --
 * name-only, held).  Documented methods, each on its own page:
 *   ms900171  HRESULT AbortAllTransfers();
 *   ms900172  HRESULT GetLabel(GUID* puuidLabelSystem, WCHAR* labelBuf,
 *                               DWORD LabelBufSz);
 *   ms900173  HRESULT GetMaxOutstandingTransfers(DWORD* pdwTransfers,
 *                                                DWORD* pdwMaxSize);
 *   ms900174  HRESULT GetPendingTransferCount(DWORD* pdwPending);
 *             (the page's signature block prints the name
 *              "GetPendingTransfersCount" -- an artifact; the page
 *              title is GetPendingTransferCount)
 *   ms900176  HRESULT OnDiscontinuity();
 *   ms900177  HRESULT RequestTransfer(PHYSICAL_ADDRESS physStart,
 *             DWORD dwSize, VOID* pva, DWORD* pdwPending);
 *             (PHYSICAL_ADDRESS: the CEDDK.h type -- see ceddk.h M57)
 *   ms900178  HRESULT SetDataNotificationThreshold(
 *                          DWORD dwPendingThreshold);
 *   ms900179  HRESULT SetThresholdCallback(PNOTIFICATION_CALLBACK pProc,
 *                                          DWORD arg);
 *             (PNOTIFICATION_CALLBACK: no page publishes the
 *              NOTIFICATION_CALLBACK type -- held)
 */
typedef struct IDMAChannel IDMAChannel;

/* ms900169 "IBitstreamProcessor" (Dvddrvr.idl; IUnknown-derived;
 * IID_IBITSTREAMPROCESSOR, ms892115 -- name-only, held).  Documented
 * methods:
 *   ms900168  HRESULT Init();
 *   ms900170  HRESULT SetBitstreamType(DWORD dwBitstreamType);
 *   ms900167  HRESULT GetLabeledDMAChannel(REFGUID guidLabelSystem,
 *             WCHAR* plabelBuf, IDMAChannel** ppDMAChannel);
 *   ms900166  HRESULT GetDMAChannelCount(DWORD* pdwChannels);
 *   ms900165  HRESULT GetDMAChannel(DWORD dwIndex,
 *                                   IDMAChannel** ppChannel);
 */
typedef struct IBitstreamProcessor IBitstreamProcessor;

/* ms900198 "IDVDRenderer" (Dvddrvr.idl; IUnknown-derived;
 * IID_IDVDRENDERER, ms892115 -- name-only, held).  Documented methods:
 *   ms901070  HRESULT RegisterSyncEvent(EDVDSyncEventType eType,
 *             HANDLE h, void* pDataLock, DWORD dwMaxDataSize,
 *             void* pEventData);
 *   ms901363  HRESULT UnregisterSyncEvent(EDVDSyncEventType etype,
 *             HANDLE h);
 *   ms901009  HRESULT Play();
 *   ms900193  HRESULT Abort();
 *   ms900910  HRESULT Pause(BOOL bOn);
 *   ms901164  HRESULT Scan(BOOL bForward, double dRate,
 *             double* dwActual, DWORD* bVobuSkip);
 *   ms901349  HRESULT Slow(BOOL bForward, double dRate,
 *             double* dwActual);
 *   ms901358  HRESULT Step(BOOL bForward);
 *             (the page's signature block prints "Slow" -- an artifact;
 *              the page title is Step)
 *   ms900197  HRESULT Highlight(BYTE buttonNumber,
 *             EHighlightAction action, BOOL bRelativeMode);
 *   ms900195  HRESULT GetHighlightedButton(BYTE* buttonNumber);
 *   ms900194  HRESULT GetAudioCaps(DWORD* pdwCaps);
 *   ms900196  HRESULT GetScanCaps(DWORD* pdwCaps);
 *   ms901290  HRESULT SetAudioStreamNumber(int iDecodingNumber);
 *   ms901300  HRESULT SetAudioStreamType(
 *             EDVDAudioStreamType dwSelectedDecoder);
 *   ms901342  HRESULT SetSubpictureStreamNumber(int iDecodingNumber,
 *             BOOL bDisplay);
 *   ms901334  HRESULT SetPalette(DWORD* pPalette);
 *   ms901312  HRESULT SetContentAspectRatio(
 *             EDVDDisplayAspectRatio enumDisplayAspectRatio);
 *   ms901323  HRESULT SetDisplayAspectRatio(
 *             EDVDDisplayAspectRatio enumDisplayAspectRatio);
 *   ms901283  HRESULT SetAspectRatioMode(
 *             EDVDAspectRatioMode enumAspectRatioMode);
 *   ms901270  HRESULT SetAPS(DWORD apsType, DWORD* pdwCookie);
 */
typedef struct IDVDRenderer IDVDRenderer;

#ifdef __cplusplus
}
#endif

#endif /* AKARI_DVDDRVRR_H */
