/*
 * Mmsystem.h -- Waveform Audio / Audio Mixer / Timer Driver services
 * for Windows CE (Akari API).
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch from the official Microsoft Windows CE 5.0
 * documentation (learn.microsoft.com previous-versions archive; page
 * ids cited per declaration).  Sources:
 *
 *   "Waveform Audio Reference" book (124 leaves,
 *     tools/manifests/waveaudio.manifest) -- PlaySound / sndPlaySound,
 *     the waveIn* (16) and waveOut* (23) functions, waveInProc /
 *     waveOutProc callbacks, WAVEFORMATEX / WAVEHDR / WAVEINCAPS /
 *     WAVEOUTCAPS / STREAMPROPS / AUDIOGAINCLASS, the Hardware Audio
 *     Mixer layer (mixer* 10 functions, MIXERCAPS / MIXERCONTROL /
 *     MIXERCONTROLDETAILS{,_BOOLEAN,_LISTTEXT,_SIGNED,_UNSIGNED} /
 *     MIXERLINE / MIXERLINECONTROLS) and the WIM_/WOM_/MM_ message
 *     pages.  Headers: Mmsystem.h; Link Library: Coredll.lib.
 *   "Timer Driver Reference" book (13 leaves,
 *     tools/manifests/timerdriver.manifest) -- the time* functions
 *     (9), MMTIME and TIMECAPS.  Header: Mmsystem.h; Link Library:
 *     Mmtimer.lib (def/mmtimer-doc.def).
 *
 * Layout policy: structures are transcribed verbatim from the CE 5.0
 * prints (member order, types, union grouping).  The CE 6.0 twin
 * WAVEOUTCAPS (ee487573) prints the identical layout.
 *
 * Derived / own-design scalar constants (recorded per the project
 * verification rules; see docs/inventory.md M63):
 *
 *   MMRESULT = UINT -- derived: the CE waveInGetErrorText page types
 *   its error-code parameter "MMRESULT mmrError" while waveOutGetError
 *   Text types the identical parameter "UINT mmrError" (aa452425 /
 *   aa452446); the two pages document the same value set, so the
 *   CE docs themselves interchange MMRESULT with UINT.
 *
 *   MMVERSION = UINT, MIXER_SHORT_NAME_CHARS = 16,
 *   MIXER_LONG_NAME_CHARS = 64, MAXERRORLENGTH = 256 -- own-design
 *   gap closures (README rule 2): no CE page, CE 6.0 twin or desktop
 *   mmeapi reference page prints these widths (checked aa452442,
 *   ee487573, desktop ns-mmeapi-waveoutcaps which prints VERSION,
 *   ns-mmeapi-mixercontrol which prints the same constant names;
 *   Learn search returns no value page).  They are layout-only
 *   scalars of the documented structure set; chosen to the desktop
 *   mmeapi structure-family ABI and recorded here so they can be
 *   re-audited.  MAXPNAMELEN = 32 IS printed by the pages and is
 *   grounded.
 *
 * Every flag / message / error family of the two books is documented
 * by NAME ONLY (no numeric values published; tables list names and
 * descriptions): SND_* (ms932262), CALLBACK_* (aa452431/aa452455),
 * WAVE_FORMAT_* (aa452419/aa452442), WAVECAPS_* (aa452442), WHDR_*
 * (aa452420), WIM_/WOM_ + MM_WIM_/MM_WOM_/MM_MIXM_ messages
 * (ms932057..63, aa452468..473, ms932055/56; MM_WOM_ATTENUATED is a
 * CE-specific message), MMSYSERR_, WAVERR_ and MIXERR_ return codes
 * (ms923396 et al.), TIME_* formats and event flags (aa447864,
 * aa448195), WAGC_CLASS_ and WAGC_PRIORITY_ families (ms925607, aa452383),
 * MIXER_OBJECT_ plus the
 * MIXER_GETLINEINFOF_, MIXER_GETLINECONTROLSF_,
 * MIXER_GETCONTROLDETAILSF_ and MIXER_SETCONTROLDETAILSF_ families (ms932044-49,
 * ms932053), MIXERLINE_COMPONENTTYPE_, MIXERLINE_LINEF_ and
 * MIXERLINE_TARGETTYPE_ families (ms932050), MIXERCONTROL_CT_CLASS_, MIXERCONTROL_CONTROLTYPE_ and
 * MIXERCONTROL_CONTROLF_ families (ms932038),
 * MXDM_* (ms932052), WAVE_MAPPER.  Per the zero-gap policy they are
 * NOT defined here; the families are catalogued in docs/inventory.md
 * (M63).
 */

#ifndef AKARI_MMSYSTEM_H
#define AKARI_MMSYSTEM_H

#include "Windef.h"    /* DWORD, WORD, UINT, BOOL, CHAR, LONG, LPSTR, LPVOID, HWND, CALLBACK, FAR */
#include "Winnt.h"     /* GUID (wave*GetProperty), DWORD_PTR (TIMECALLBACK) */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/*  Scalar types and handles                                           */
/* ------------------------------------------------------------------ */

/* MMRESULT: derived (see the header note; aa452425 vs aa452446). */
typedef UINT MMRESULT;

/* MMVERSION: own-design width closure (see the header note). */
typedef UINT MMVERSION;

typedef void *HWAVEIN;     /* waveIn* signatures (aa452421..aa452440) */
typedef void *HWAVEOUT;    /* waveOut* signatures (aa452441..aa452466) */
typedef void *HMIXER;      /* mixerOpen/mixerClose/mixerMessage */
typedef void *HMIXEROBJ;   /* mixerGet/Set signatures (ms932044..54) */

typedef HWAVEIN  *LPHWAVEIN;    /* waveInOpen phwi (aa452431) */
typedef HWAVEOUT *LPHWAVEOUT;   /* waveOutOpen phwo (aa452455) */
typedef HMIXER   *LPHMIXER;     /* mixerOpen phmx (ms932053) */

/* aa452419 WAVEOUTCAPS/WAVEINCAPS/MIXERCAPS/MIXERLINE pages print:
 * "#define MAXPNAMELEN 32 -- max product name length (including
 * NULL)". */
#define MAXPNAMELEN 32

/* Own-design layout scalars (see the header note): the short/long
 * mixer name array lengths and the error-text buffer length. */
#define MIXER_SHORT_NAME_CHARS 16
#define MIXER_LONG_NAME_CHARS  64
#define MAXERRORLENGTH         256

/* ------------------------------------------------------------------ */
/*  Callbacks                                                          */
/* ------------------------------------------------------------------ */

/* aa452435 "waveInProc": void CALLBACK waveInProc(HWAVEIN hwi,
 * UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);
 * "a placeholder for the application-defined function name".  The
 * pointer typedef is the composition of the printed prototype with
 * the parameter it is passed through (waveInOpen's dwCallback). */
typedef void (CALLBACK *LPWAVEINPROC)(HWAVEIN hwi, UINT uMsg,
    DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);

/* aa452458 "waveOutProc": void CALLBACK waveOutProc(HWAVEOUT hwo,
 * UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2). */
typedef void (CALLBACK *LPWAVEOUTPROC)(HWAVEOUT hwo, UINT uMsg,
    DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);

/* aa448195 "timeSetEvent" prints the callback typedef verbatim:
 * typedef void (CALLBACK TIMECALLBACK)(UINT uTimerID, UINT uMsg,
 *   DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
 * typedef TIMECALLBACK FAR *LPTIMECALLBACK; */
typedef void (CALLBACK TIMECALLBACK)(UINT uTimerID, UINT uMsg,
    DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
typedef TIMECALLBACK FAR *LPTIMECALLBACK;

/* ------------------------------------------------------------------ */
/*  Structures (verbatim CE 5.0 prints)                                */
/* ------------------------------------------------------------------ */

/* aa452419 "WAVEFORMATEX (Waveform Audio)" (tagless print). */
typedef struct {
    WORD wFormatTag;
    WORD nChannels;
    DWORD nSamplesPerSec;
    DWORD nAvgBytesPerSec;
    WORD nBlockAlign;
    WORD wBitsPerSample;
    WORD cbSize;
} WAVEFORMATEX;
typedef WAVEFORMATEX *LPWAVEFORMATEX;      /* waveInOpen pwfx spelling */
typedef const WAVEFORMATEX *LPCWAVEFORMATEX;

/* aa452420 "WAVEHDR". */
typedef struct {
    LPSTR lpData;
    DWORD dwBufferLength;
    DWORD dwBytesRecorded;
    DWORD dwUser;
    DWORD dwFlags;
    DWORD dwLoops;
    struct wavehdr_tag* lpNext;
    DWORD reserved;
} WAVEHDR;
typedef WAVEHDR *LPWAVEHDR;

/* aa452422 "WAVEINCAPS" (tagless print; MMVERSION own-design note
 * applies to vDriverVersion). */
typedef struct {
    WORD wMid;
    WORD wPid;
    MMVERSION vDriverVersion;
    CHAR szPname[MAXPNAMELEN];
    DWORD dwFormats;
    WORD wChannels;
    WORD wReserved1;
} WAVEINCAPS;
typedef WAVEINCAPS *LPWAVEINCAPS;

/* aa452442 "WAVEOUTCAPS" (CE 6.0 twin ee487573 identical). */
typedef struct {
    WORD wMid;
    WORD wPid;
    MMVERSION vDriverVersion;
    CHAR szPname[MAXPNAMELEN];
    DWORD dwFormats;
    WORD wChannels;
    WORD wReserved1;
    DWORD dwSupport;
} WAVEOUTCAPS;
typedef WAVEOUTCAPS *LPWAVEOUTCAPS;

/* aa452383 "STREAMPROPS". */
typedef struct tagSTREAMPROPS {
    DWORD dwClassID;
    DWORD dwFlags;
} STREAMPROPS, *PSTREAMPROPS;

/* ms925607 "AUDIOGAINCLASS". */
typedef struct tagAUDIOGAINCLASS {
    DWORD dwPriority;
    DWORD dwRelativeGain;
} AUDIOGAINCLASS, * PAUDIOGAINCLASS;

/* aa447864 "MMTIME" (Timer Driver book; the wave*GetPosition
 * functions take LPMMTIME). */
typedef struct mmtime_tag {
    UINT wType;
    union {
        DWORD ms;
        DWORD sample;
        DWORD cb;
        DWORD ticks;
        struct {
            BYTE hour;
            BYTE min;
            BYTE sec;
            BYTE frame;
            BYTE fps;
            BYTE dummy;
            BYTE pad[2];
        } smpte;
        struct {
            DWORD songptrpos;
        } midi;
    } u;
} MMTIME, *LPMMTIME;

/* aa448189 "TIMECAPS". */
typedef struct timecaps_tag {
    UINT wPeriodMin;
    UINT wPeriodMax;
} TIMECAPS, *PTIMECAPS, *LPTIMECAPS;

/* ms932036 "MIXERCAPS" (TCHAR szPname as printed; CE is Unicode). */
typedef struct {
    WORD wMid;
    WORD wPid;
    MMVERSION vDriverVersion;
    TCHAR szPname[MAXPNAMELEN];
    DWORD fdwSupport;
    DWORD cDestinations;
} MIXERCAPS, *LPMIXERCAPS;

/* ms932038 "MIXERCONTROL" (anonymous Bounds/Metrics unions exactly
 * as printed; PMIXERCONTROL/LPMIXERCONTROL pointer typedefs printed
 * on the page). */
typedef struct {
    DWORD cbStruct;
    DWORD dwControlID;
    DWORD dwControlType;
    DWORD fdwControl;
    DWORD cMultipleItems;
    CHAR szShortName[MIXER_SHORT_NAME_CHARS];
    CHAR szName[MIXER_LONG_NAME_CHARS];
    union {
        struct {
            LONG lMinimum;
            LONG lMaximum;
        };
        struct {
            DWORD dwMinimum;
            DWORD dwMaximum;
        };
        DWORD dwReserved[6];
    } Bounds;
    union {
        DWORD cSteps;
        DWORD cbCustomData;
        DWORD dwReserved[6];
    } Metrics;
} MIXERCONTROL, *PMIXERCONTROL, FAR* LPMIXERCONTROL;

/* ms932039 "MIXERCONTROLDETAILS". */
typedef struct {
    DWORD cbStruct;
    DWORD dwControlID;
    DWORD cChannels;
    union {
        HWND hwndOwner;
        DWORD cMultipleItems;
    };
    DWORD cbDetails;
    LPVOID paDetails;
} MIXERCONTROLDETAILS, *LPMIXERCONTROLDETAILS;

/* ms932040 "MIXERCONTROLDETAILS_BOOLEAN". */
typedef struct {
    LONG fValue;
} MIXERCONTROLDETAILS_BOOLEAN;

/* ms932041 "MIXERCONTROLDETAILS_LISTTEXT". */
typedef struct {
    DWORD dwParam1;
    DWORD dwParam2;
    CHAR szName[MIXER_LONG_NAME_CHARS];
} MIXERCONTROLDETAILS_LISTTEXT;

/* ms932042 "MIXERCONTROLDETAILS_SIGNED". */
typedef struct {
    LONG lValue;
} MIXERCONTROLDETAILS_SIGNED;

/* ms932043 "MIXERCONTROLDETAILS_UNSIGNED". */
typedef struct {
    DWORD dwValue;
} MIXERCONTROLDETAILS_UNSIGNED;

/* ms932050 "MIXERLINE" (anonymous Target sub-struct as printed). */
typedef struct {
    DWORD cbStruct;
    DWORD dwDestination;
    DWORD dwSource;
    DWORD dwLineID;
    DWORD fdwLine;
    DWORD dwUser;
    DWORD dwComponentType;
    DWORD cChannels;
    DWORD cConnections;
    DWORD cControls;
    CHAR szShortName[MIXER_SHORT_NAME_CHARS];
    CHAR szName[MIXER_LONG_NAME_CHARS];
    struct {
        DWORD dwType;
        DWORD dwDeviceID;
        WORD wMid;
        WORD wPid;
        MMVERSION vDriverVersion;
        CHAR szPname[MAXPNAMELEN];
    } Target;
} MIXERLINE, *LPMIXERLINE;

/* ms932051 "MIXERLINECONTROLS". */
typedef struct {
    DWORD cbStruct;
    DWORD dwLineID;
    union {
        DWORD dwControlID;
        DWORD dwControlType;
    };
    DWORD cControls;
    DWORD cbmxctrl;
    LPMIXERCONTROL pamxctrl;
} MIXERLINECONTROLS, *LPMIXERLINECONTROLS;

/* ------------------------------------------------------------------ */
/*  Waveform Audio functions (Coredll.lib)                             */
/* ------------------------------------------------------------------ */

/* ms932262 "PlaySound" (LPCSTR parameter spelling as printed). */
AKARI_CE_IMPORT BOOL WINAPI PlaySound(LPCSTR pszSound, HMODULE hmod,
    DWORD fdwSound) AKARI_CE_NAME(PlaySound);

/* ms932314 "sndPlaySound" (LPCTSTR parameter as printed). */
AKARI_CE_IMPORT BOOL sndPlaySound(LPCTSTR lpszSoundName, UINT fuSound)
    AKARI_CE_NAME(sndPlaySound);

/* aa452421 "waveInAddBuffer". */
AKARI_CE_IMPORT MMRESULT waveInAddBuffer(HWAVEIN hwi, LPWAVEHDR pwh,
    UINT cbwh) AKARI_CE_NAME(waveInAddBuffer);

/* aa452423 "waveInClose". */
AKARI_CE_IMPORT MMRESULT waveInClose(HWAVEIN hwi)
    AKARI_CE_NAME(waveInClose);

/* aa452424 "waveInGetDevCaps". */
AKARI_CE_IMPORT MMRESULT waveInGetDevCaps(UINT uDeviceID,
    LPWAVEINCAPS pwic, UINT cbwic) AKARI_CE_NAME(waveInGetDevCaps);

/* aa452425 "waveInGetErrorText" (MMRESULT parameter as printed;
 * waveOutGetErrorText prints UINT for the same value -- artifact
 * recorded in the inventory). */
AKARI_CE_IMPORT MMRESULT waveInGetErrorText(MMRESULT mmrError,
    LPTSTR pszText, UINT cchText) AKARI_CE_NAME(waveInGetErrorText);

/* aa452426 "waveInGetID". */
AKARI_CE_IMPORT MMRESULT waveInGetID(HWAVEIN hwi, PUINT puDeviceID)
    AKARI_CE_NAME(waveInGetID);

/* aa452427 "waveInGetNumDevs". */
AKARI_CE_IMPORT UINT waveInGetNumDevs(void);

/* aa452428 "waveInGetPosition". */
AKARI_CE_IMPORT MMRESULT waveInGetPosition(HWAVEIN hwi,
    LPMMTIME pmmt, UINT cbmmt) AKARI_CE_NAME(waveInGetPosition);

/* aa452429 "waveInGetProperty" (CE-specific property interface). */
AKARI_CE_IMPORT MMRESULT waveInGetProperty(UINT uDeviceID,
    const GUID* pPropSetId, ULONG ulPropId, LPVOID pvPropParams,
    ULONG cbPropParams, LPVOID pvPropData, ULONG cbPropData,
    PULONG pcbReturn) AKARI_CE_NAME(waveInGetProperty);

/* aa452430 "waveInMessage". */
AKARI_CE_IMPORT MMRESULT waveInMessage(HWAVEIN hwi, UINT uMsg,
    DWORD dw1, DWORD dw2) AKARI_CE_NAME(waveInMessage);

/* aa452431 "waveInOpen". */
AKARI_CE_IMPORT MMRESULT waveInOpen(LPHWAVEIN phwi, UINT uDeviceID,
    LPCWAVEFORMATEX pwfx, DWORD dwCallback, DWORD dwInstance,
    DWORD fdwOpen) AKARI_CE_NAME(waveInOpen);

/* aa452432 "waveInPrepareHeader". */
AKARI_CE_IMPORT MMRESULT waveInPrepareHeader(HWAVEIN hwi,
    LPWAVEHDR pwh, UINT cbwh) AKARI_CE_NAME(waveInPrepareHeader);

/* aa452436 "waveInReset". */
AKARI_CE_IMPORT MMRESULT waveInReset(HWAVEIN hwi)
    AKARI_CE_NAME(waveInReset);

/* aa452437 "waveInSetProperty". */
AKARI_CE_IMPORT MMRESULT waveInSetProperty(UINT uDeviceID,
    const GUID* pPropSetId, ULONG ulPropId, LPVOID pvPropParams,
    ULONG cbPropParams, LPVOID pvPropData, ULONG cbPropData)
    AKARI_CE_NAME(waveInSetProperty);

/* aa452438 "waveInStart". */
AKARI_CE_IMPORT MMRESULT waveInStart(HWAVEIN hwi)
    AKARI_CE_NAME(waveInStart);

/* aa452439 "waveInStop". */
AKARI_CE_IMPORT MMRESULT waveInStop(HWAVEIN hwi)
    AKARI_CE_NAME(waveInStop);

/* aa452440 "waveInUnprepareHeader". */
AKARI_CE_IMPORT MMRESULT waveInUnprepareHeader(HWAVEIN hwi,
    LPWAVEHDR pwh, UINT cbwh) AKARI_CE_NAME(waveInUnprepareHeader);

/* aa452441 "waveOutBreakLoop". */
AKARI_CE_IMPORT MMRESULT waveOutBreakLoop(HWAVEOUT hwo)
    AKARI_CE_NAME(waveOutBreakLoop);

/* aa452443 "waveOutClose". */
AKARI_CE_IMPORT MMRESULT waveOutClose(HWAVEOUT hwo)
    AKARI_CE_NAME(waveOutClose);

/* aa452445 "waveOutGetDevCaps". */
AKARI_CE_IMPORT MMRESULT waveOutGetDevCaps(UINT uDeviceID,
    LPWAVEOUTCAPS pwoc, UINT cbwoc) AKARI_CE_NAME(waveOutGetDevCaps);

/* aa452446 "waveOutGetErrorText" (UINT parameter as printed). */
AKARI_CE_IMPORT MMRESULT waveOutGetErrorText(UINT mmrError,
    LPTSTR pszText, UINT cchText) AKARI_CE_NAME(waveOutGetErrorText);

/* aa452447 "waveOutGetID". */
AKARI_CE_IMPORT MMRESULT waveOutGetID(HWAVEOUT hwo,
    LPUINT puDeviceID) AKARI_CE_NAME(waveOutGetID);

/* aa452448 "waveOutGetNumDevs". */
AKARI_CE_IMPORT UINT waveOutGetNumDevs(void);

/* aa452449 "waveOutGetPitch". */
AKARI_CE_IMPORT MMRESULT waveOutGetPitch(HWAVEOUT hwo,
    LPDWORD pdwPitch) AKARI_CE_NAME(waveOutGetPitch);

/* aa452450 "waveOutGetPlaybackRate". */
AKARI_CE_IMPORT MMRESULT waveOutGetPlaybackRate(HWAVEOUT hwo,
    LPDWORD pdwRate) AKARI_CE_NAME(waveOutGetPlaybackRate);

/* aa452451 "waveOutGetPosition". */
AKARI_CE_IMPORT MMRESULT waveOutGetPosition(HWAVEOUT hwo,
    LPMMTIME pmmt, UINT cbmmt) AKARI_CE_NAME(waveOutGetPosition);

/* aa452452 "waveOutGetProperty". */
AKARI_CE_IMPORT MMRESULT waveOutGetProperty(UINT uDeviceID,
    const GUID* pPropSetId, ULONG ulPropId, LPVOID pvPropParams,
    ULONG cbPropParams, LPVOID pvPropData, ULONG cbPropData,
    PULONG pcbReturn) AKARI_CE_NAME(waveOutGetProperty);

/* aa452453 "waveOutGetVolume". */
AKARI_CE_IMPORT MMRESULT waveOutGetVolume(HWAVEOUT hwo,
    LPDWORD pdwVolume) AKARI_CE_NAME(waveOutGetVolume);

/* aa452454 "waveOutMessage". */
AKARI_CE_IMPORT MMRESULT waveOutMessage(HWAVEOUT hwo, UINT uMsg,
    DWORD dw1, DWORD dw2) AKARI_CE_NAME(waveOutMessage);

/* aa452455 "waveOutOpen". */
AKARI_CE_IMPORT MMRESULT waveOutOpen(LPHWAVEOUT phwo, UINT uDeviceID,
    LPCWAVEFORMATEX pwfx, DWORD dwCallback, DWORD dwInstance,
    DWORD fdwOpen) AKARI_CE_NAME(waveOutOpen);

/* aa452456 "waveOutPause". */
AKARI_CE_IMPORT MMRESULT waveOutPause(HWAVEOUT hwo)
    AKARI_CE_NAME(waveOutPause);

/* aa452457 "waveOutPrepareHeader". */
AKARI_CE_IMPORT MMRESULT waveOutPrepareHeader(HWAVEOUT hwo,
    LPWAVEHDR pwh, UINT cbwh) AKARI_CE_NAME(waveOutPrepareHeader);

/* aa452459 "waveOutReset". */
AKARI_CE_IMPORT MMRESULT waveOutReset(HWAVEOUT hwo)
    AKARI_CE_NAME(waveOutReset);

/* aa452460 "waveOutRestart". */
AKARI_CE_IMPORT MMRESULT waveOutRestart(HWAVEOUT hwo)
    AKARI_CE_NAME(waveOutRestart);

/* aa452461 "waveOutSetPitch". */
AKARI_CE_IMPORT MMRESULT waveOutSetPitch(HWAVEOUT hwo, DWORD dwPitch)
    AKARI_CE_NAME(waveOutSetPitch);

/* aa452462 "waveOutSetPlaybackRate". */
AKARI_CE_IMPORT MMRESULT waveOutSetPlaybackRate(HWAVEOUT hwo,
    DWORD dwRate) AKARI_CE_NAME(waveOutSetPlaybackRate);

/* aa452463 "waveOutSetProperty". */
AKARI_CE_IMPORT MMRESULT waveOutSetProperty(UINT uDeviceID,
    const GUID* pPropSetId, ULONG ulPropId, LPVOID pvPropParams,
    ULONG cbPropParams, LPVOID pvPropData, ULONG cbPropData)
    AKARI_CE_NAME(waveOutSetProperty);

/* aa452464 "waveOutSetVolume". */
AKARI_CE_IMPORT MMRESULT waveOutSetVolume(HWAVEOUT hwo, DWORD dwVolume)
    AKARI_CE_NAME(waveOutSetVolume);

/* aa452465 "waveOutUnprepareHeader". */
AKARI_CE_IMPORT MMRESULT waveOutUnprepareHeader(HWAVEOUT hwo,
    LPWAVEHDR pwh, UINT cbwh) AKARI_CE_NAME(waveOutUnprepareHeader);

/* aa452466 "waveOutWrite". */
AKARI_CE_IMPORT MMRESULT waveOutWrite(HWAVEOUT hwo, LPWAVEHDR pwh,
    UINT cbwh) AKARI_CE_NAME(waveOutWrite);

/* ------------------------------------------------------------------ */
/*  Audio Mixer functions (Coredll.lib)                                */
/* ------------------------------------------------------------------ */

/* ms932037 "mixerClose". */
AKARI_CE_IMPORT MMRESULT mixerClose(HMIXER hmx)
    AKARI_CE_NAME(mixerClose);

/* ms932044 "mixerGetControlDetails". */
AKARI_CE_IMPORT MMRESULT mixerGetControlDetails(HMIXEROBJ hmxobj,
    LPMIXERCONTROLDETAILS pmxcd, DWORD fdwDetails)
    AKARI_CE_NAME(mixerGetControlDetails);

/* ms932045 "mixerGetDevCaps". */
AKARI_CE_IMPORT MMRESULT mixerGetDevCaps(UINT uMxId,
    LPMIXERCAPS pmxcaps, UINT cbmxcaps) AKARI_CE_NAME(mixerGetDevCaps);

/* ms932046 "mixerGetID". */
AKARI_CE_IMPORT MMRESULT mixerGetID(HMIXEROBJ hmxobj, UINT* puMxId,
    DWORD fdwId) AKARI_CE_NAME(mixerGetID);

/* ms932047 "mixerGetLineControls". */
AKARI_CE_IMPORT MMRESULT mixerGetLineControls(HMIXEROBJ hmxobj,
    LPMIXERLINECONTROLS pmxlc, DWORD fdwControls)
    AKARI_CE_NAME(mixerGetLineControls);

/* ms932048 "mixerGetLineInfo". */
AKARI_CE_IMPORT MMRESULT mixerGetLineInfo(HMIXEROBJ hmxobj,
    LPMIXERLINE pmxl, DWORD fdwInfo) AKARI_CE_NAME(mixerGetLineInfo);

/* ms932049 "mixerGetNumDevs". */
AKARI_CE_IMPORT UINT mixerGetNumDevs(void);

/* ms932052 "mixerMessage" (DWORD return as printed). */
AKARI_CE_IMPORT DWORD mixerMessage(HMIXER hmx, UINT uMsg,
    DWORD dwParam1, DWORD dwParam2) AKARI_CE_NAME(mixerMessage);

/* ms932053 "mixerOpen". */
AKARI_CE_IMPORT MMRESULT mixerOpen(LPHMIXER phmx, UINT uMxId,
    DWORD dwCallback, DWORD dwInstance, DWORD fdwOpen)
    AKARI_CE_NAME(mixerOpen);

/* ms932054 "mixerSetControlDetails". */
AKARI_CE_IMPORT MMRESULT mixerSetControlDetails(HMIXEROBJ hmxobj,
    LPMIXERCONTROLDETAILS pmxcd, DWORD fdwDetails)
    AKARI_CE_NAME(mixerSetControlDetails);

/* ------------------------------------------------------------------ */
/*  Timer Driver functions (Mmtimer.lib; def/mmtimer-doc.def)          */
/* ------------------------------------------------------------------ */

/* aa448188 "timeBeginPeriod". */
AKARI_CE_IMPORT MMRESULT timeBeginPeriod(UINT uPeriod)
    AKARI_CE_NAME(timeBeginPeriod);

/* aa448190 "timeEndPeriod". */
AKARI_CE_IMPORT MMRESULT timeEndPeriod(UINT uPeriod)
    AKARI_CE_NAME(timeEndPeriod);

/* aa448191 "timeGetDevCaps". */
AKARI_CE_IMPORT MMRESULT timeGetDevCaps(LPTIMECAPS ptc, UINT cbtc)
    AKARI_CE_NAME(timeGetDevCaps);

/* aa448326 "timeGetHardwareFrequency" (CE-specific). */
AKARI_CE_IMPORT DWORD timeGetHardwareFrequency(void)
    AKARI_CE_NAME(timeGetHardwareFrequency);

/* aa448192 "timeGetSystemTime". */
AKARI_CE_IMPORT MMRESULT timeGetSystemTime(LPMMTIME pmmt, UINT cbmmt)
    AKARI_CE_NAME(timeGetSystemTime);

/* aa448193 "timeGetTime". */
AKARI_CE_IMPORT DWORD timeGetTime(void) AKARI_CE_NAME(timeGetTime);

/* aa448327 "timeGetTimeSinceInterrupt" (CE-specific). */
AKARI_CE_IMPORT DWORD timeGetTimeSinceInterrupt(void)
    AKARI_CE_NAME(timeGetTimeSinceInterrupt);

/* aa448194 "timeKillEvent". */
AKARI_CE_IMPORT MMRESULT timeKillEvent(UINT uTimerID)
    AKARI_CE_NAME(timeKillEvent);

/* aa448195 "timeSetEvent". */
AKARI_CE_IMPORT MMRESULT timeSetEvent(UINT uDelay, UINT uResolution,
    LPTIMECALLBACK fptc, DWORD dwUser, UINT fuEvent)
    AKARI_CE_NAME(timeSetEvent);

#ifdef __cplusplus
}
#endif

#endif /* AKARI_MMSYSTEM_H */
