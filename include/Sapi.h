/*
 * Sapi.h -- Microsoft Speech API (SAPI 5.0) types, constants and COM
 * interface records for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs; Applications and Services Development > Speech API (SAPI) 5.0
 * book, 491 leaves harvested under tools/manifests/sapi.manifest, M68).
 *
 * Requirements rows print "Header: Sapi.h, Sapi.idl" (app interfaces) and
 * "Sapiddk.h, Sapiddk.idl" (engine-side DDI interfaces); the file name
 * sapi.h is the include-compat surface.  The CE SAPI is a C++ COM API:
 * no page publishes a vtable layout, so -- following the M44 objbase.h
 * interface-record policy -- each interface is carried as an opaque
 * forward declaration plus verbatim method-signature records.
 *
 * Import surface: none is documentable.  Every "Link Library:
 * Sapilib.lib" row sits on an interface/method page (virtual calls) or
 * on the Sphelper.h helper-function pages, whose prints are C++ inline
 * functions / templates (SPBindToFile, SpCreateObjectFromToken, ...)
 * -- header-side code, not import-library symbols (the MSXML
 * Uuid.lib / shobjidl.h "Implementation dependent" precedent).
 *
 * WAVEFORMATEX (SAPI) re-prints the mmsystem.h structure identically
 * (see the SAPI Structures book page); this header includes mmsystem.h
 * rather than redefining it.
 */

#ifndef AKARI_SAPI_H
#define AKARI_SAPI_H

#include "Windef.h"
#include "Winnt.h"
#include "Objbase.h"    /* VARIANT, BSTR, IDispatch carriers */
#include "Mmsystem.h"   /* WAVEFORMATEX (SAPI page re-print) */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/* Handle/id carrier types -- recorded own-design closures (no CE      */
/* page prints their typedefs; they appear only as member/parameter    */
/* types in the printed structures and method signatures; the          */
/* project handle convention is an opaque pointer, the phoneme id is   */
/* carried per the szPronunciation array print):                       */
/*   SPSTATEHANDLE, SPGRAMMARHANDLE, SPRULEHANDLE -- opaque engine     */
/*     handles (SPPARSEINFO hRule, SPRECORESULTINFO hGrammar,          */
/*     SPRULEENTRY hInitialState/hNextState prints)                    */
/*   SPTRANSITIONID -- transition id (SPTRANSITIONENTRY print)         */
/*   SPPHONEID -- phoneme id (SPVOICESTATUS PhonemeId,                 */
/*     SPPHRASEELEMENT szPronunciation prints)                         */
/* Replace each with the official print when one appears.             */
/* ------------------------------------------------------------------ */
typedef void  *SPSTATEHANDLE;
typedef void  *SPGRAMMARHANDLE;
typedef void  *SPRULEHANDLE;
typedef void  *SPTRANSITIONID;
typedef WCHAR  SPPHONEID;

typedef struct ISpAudio ISpAudio;
typedef struct ISpCFGInterpreter ISpCFGInterpreter;
typedef struct ISpCFGInterpreterSite ISpCFGInterpreterSite;
typedef struct ISpContainerLexicon ISpContainerLexicon;
typedef struct ISpDataKey ISpDataKey;
typedef struct ISpErrorLog ISpErrorLog;
typedef struct ISpEventSink ISpEventSink;
typedef struct ISpEventSource ISpEventSource;
typedef struct ISpGramCompBackend ISpGramCompBackend;
typedef struct ISpGrammarBuilder ISpGrammarBuilder;
typedef struct ISpGrammarCompiler ISpGrammarCompiler;
typedef struct ISpITNProcessor ISpITNProcessor;
typedef struct ISpLexicon ISpLexicon;
typedef struct ISpMMSysAudio ISpMMSysAudio;
typedef struct ISpNotifyCallback ISpNotifyCallback;
typedef struct ISpNotifySink ISpNotifySink;
typedef struct ISpNotifySource ISpNotifySource;
typedef struct ISpNotifyTranslator ISpNotifyTranslator;
typedef struct ISpObjectToken ISpObjectToken;
typedef struct ISpObjectTokenCategory ISpObjectTokenCategory;
typedef struct ISpObjectTokenEnumBuilder ISpObjectTokenEnumBuilder;
typedef struct ISpObjectTokenInit ISpObjectTokenInit;
typedef struct ISpObjectWithToken ISpObjectWithToken;
typedef struct ISpPhoneConverter ISpPhoneConverter;
typedef struct ISpPhrase ISpPhrase;
typedef struct ISpPhraseAlt ISpPhraseAlt;
typedef struct ISpPhraseBuilder ISpPhraseBuilder;
typedef struct ISpRecoContext ISpRecoContext;
typedef struct ISpRecoGrammar ISpRecoGrammar;
typedef struct ISpRecoResult ISpRecoResult;
typedef struct ISpRecognizer ISpRecognizer;
typedef struct ISpRegDataKey ISpRegDataKey;
typedef struct ISpResourceManager ISpResourceManager;
typedef struct ISpSRAlternates ISpSRAlternates;
typedef struct ISpSREngine ISpSREngine;
typedef struct ISpSREngineSite ISpSREngineSite;
typedef struct ISpStream ISpStream;
typedef struct ISpStreamFormat ISpStreamFormat;
typedef struct ISpStreamFormatConverter ISpStreamFormatConverter;
typedef struct ISpTTSEngine ISpTTSEngine;
typedef struct ISpTTSEngineSite ISpTTSEngineSite;
typedef struct ISpTask ISpTask;
typedef struct ISpTaskManager ISpTaskManager;
typedef struct ISpThreadControl ISpThreadControl;
typedef struct ISpThreadTask ISpThreadTask;
typedef struct ISpTokenUI ISpTokenUI;
typedef struct ISpTranscript ISpTranscript;
typedef struct ISpVoice ISpVoice;
typedef struct ISpPhraseBuilder ISpPhraseBuilder;   /* SPPHRASEALT print; no CE 5.0 page of its own */


/* ------------------------------------------------------------------ */
/* SAPI interfaces (SAPI Interfaces book lists 49 overview pages; the
 * 50th record below, ISpPhraseBuilder, appears inside the printed
 * structures and method signatures).  Opaque forward declarations
 * (M44 policy).                                                       */
/* ------------------------------------------------------------------ */
typedef struct ISpPhraseBuilder ISpPhraseBuilder;   /* SPPHRASEALT print; no CE 5.0 page of its own */


typedef struct SPAUDIOBUFFERINFO {
    ULONG   ulMsMinNotification;
    ULONG   ulMsBufferSize;
    ULONG   ulMsEventBias;
} SPAUDIOBUFFERINFO;

typedef enum SPAUDIOOPTIONS {
    SPAO_NONE = 0,
    SPAO_RETAIN_AUDIO = (1 << 0),
} SPAUDIOOPTIONS;

typedef struct SPBINARYGRAMMAR {
    ULONG ulTotalSerializedSize;
} SPBINARYGRAMMAR;

typedef enum SPBOOKMARKOPTIONS {
    SPBO_NONE = 0,
    SPBO_PAUSE = 1,
} SPBOOKMARKOPTIONS;

typedef enum SPCFGNOTIFY {
    SPCFGN_ADD,
    SPCFGN_REMOVE,
    SPCFGN_INVALIDATE,
    SPCFGN_ACTIVATE,
    SPCFGN_DEACTIVATE,
} SPCFGNOTIFY;

typedef enum SPCFGRULEATTRIBUTES {
    SPRAF_TopLevel = (1 << 0),
    SPRAF_Active = (1 << 1),
    SPRAF_Export = (1 << 2),
    SPRAF_Import = (1 << 3),
    SPRAF_Interpreter = (1 << 4),
    SPRAF_Dynamic = (1 << 5),
    SPRAF_AutoPause = (1 << 16),
} SPCFGRULEATTRIBUTES;

typedef enum SPCONTEXTSTATE {
    SPCS_DISABLED = 0,
    SPCS_ENABLED = 1,
} SPCONTEXTSTATE;

typedef enum SPDATAKEYLOCATION {
    SPDKL_DefaultLocation = 0,
    SPDKL_CurrentUser = 1,
    SPDKL_LocalMachine = 2,
    SPDKL_CurrentConfig = 5,
} SPDATAKEYLOCATION;

typedef enum SPEAKFLAGS {
    SPF_DEFAULT = 0,  /* SpVoice flags */
    SPF_ASYNC = (1L << 0),
    SPF_PURGEBEFORESPEAK = (1L << 1),
    SPF_IS_FILENAME = (1L << 2),
    SPF_IS_XML = (1L << 3),
    SPF_IS_NOT_XML = (1L << 4),
    SPF_PERSIST_XML = (1L << 5),
    SPF_NLP_SPEAK_PUNC = (1L << 6),  /* Normalizer flags */
    SPF_NLP_MASK = (SPF_NLP_SPEAK_PUNC),  /* Masks */
    SPF_VOICE_MASK = (SPF_ASYNC|SPF_PURGEBEFORESPEAK|SPF_IS_FILENAME| SPF_IS_XML|SPF_IS_NOT_XML|SPF_NLP_MASK|SPF_PERSIST_XML),
    SPF_UNUSED_FLAGS = ~(SPF_VOICE_MASK),
} SPEAKFLAGS;

typedef enum SPENDSRSTREAMFLAGS {
    SPESF_NONE = 0,
    SPESF_STREAM_RELEASED = (1 << 0),
} SPENDSRSTREAMFLAGS;

typedef struct SPEVENT {
    WORD eEventId;
    WORD elParamType;
    ULONG ulStreamNum;
    ULONGLONG ullAudioStreamOffset;
    WPARAM wParam;
    LPARAM lParam;
} SPEVENT;

typedef enum SPINTERFERENCE {
    SPINTERFERENCE_NONE = 0,
    SPINTERFERENCE_NOISE,
    SPINTERFERENCE_NOSIGNAL,
    SPINTERFERENCE_TOOLOUD,
    SPINTERFERENCE_TOOQUIET,
    SPINTERFERENCE_TOOFAST,
    SPINTERFERENCE_TOOSLOW,
} SPINTERFERENCE;

typedef enum SPEVENTENUM {
    SPEI_UNDEFINED = 0,
    SPEI_START_INPUT_STREAM = 1,  /* TTS engine */
    SPEI_END_INPUT_STREAM = 2,
    SPEI_VOICE_CHANGE = 3,
    SPEI_TTS_BOOKMARK = 4,  /* LPARAM_IS_TOKEN */
    SPEI_WORD_BOUNDARY = 5,  /* LPARAM_IS_STRING */
    SPEI_PHONEME = 6,
    SPEI_SENTENCE_BOUNDARY = 7,
    SPEI_VISEME = 8,
    SPEI_TTS_AUDIO_LEVEL = 9,
    SPEI_TTS_PRIVATE = 15,  /* Engine vendors use these reserved bits */
    SPEI_MIN_TTS = 1,
    SPEI_MAX_TTS = 15,  /* minimum TTS event value */
    SPEI_END_SR_STREAM = 34,  /* maximum TTS event value //--- Speech Recognition */
    SPEI_SOUND_START = 35,  /* SR engine has reached the end of an input stream */
    SPEI_SOUND_END = 36,  /* SR engine has detected the start of nontrivial audio data */
    SPEI_PHRASE_START = 37,  /* SR engine has detected the end of nontrivial audio data */
    SPEI_RECOGNITION = 38,  /* SR engine has detected the start of a recognizable phrase */
    SPEI_HYPOTHESIS = 39,  /* SR engine's best hypothesis for the audio data */
    SPEI_SR_BOOKMARK = 40,  /* SR engine's interim hypothesis for the result of the audio data */
    SPEI_PROPERTY_NUM_CHANGE = 41,  /* SR engine has reached the specified point in the audio stream */
    /* LPARAM points to a string */
    SPEI_PROPERTY_STRING_CHANGE = 42,  /* WPARAM is the attrib value */
    SPEI_FALSE_RECOGNITION = 43,  /* LPARAM pointer to buffer. Two concatinated null terminated strings. */
    SPEI_INTERFERENCE = 44,  /* apparent speech with no valid recognition */
    SPEI_REQUEST_UI = 45,  /* LPARAM is any combination of SPINTERFERENCE flags */
    SPEI_RECO_STATE_CHANGE = 46,  /* LPARAM is string. */
    SPEI_ADAPTATION = 47,  /* wParam contains new reco state */
    SPEI_START_SR_STREAM = 48,  /* the adaptation buffer is now ready to be accepted */
    SPEI_RECO_OTHER_CONTEXT = 49,  /* SR engine has reached the start of an input stream */
    /* Phrase finished and recognized */
    SPEI_SR_AUDIO_LEVEL = 50,  /* but for other context */
    SPEI_SR_PRIVATE = 52,  /* input audio volume level // Engine vendors use these reserved bits */
    SPEI_MIN_SR = 34,
    SPEI_MAX_SR = 52,  /* minimum SR event value */
    SPEI_RESERVED1 = 30,  /* maximum SR event value */
    SPEI_RESERVED2 = 33,  /* do not use */
    SPEI_RESERVED3 = 63 // do not use,  /* do not use */
} SPEVENTENUM;

typedef enum SPEVENTLPARAMTYPE {
    SPET_LPARAM_IS_UNDEFINED = 0,
    SPET_LPARAM_IS_TOKEN,
    SPET_LPARAM_IS_OBJECT,
    SPET_LPARAM_IS_POINTER,
    SPET_LPARAM_IS_STRING,
} SPEVENTLPARAMTYPE;

typedef struct SPEVENTSOURCEINFO {
    ULONGLONG ullEventInterest;
    ULONGLONG ullQueuedInterest;
    ULONG ulCount;
} SPEVENTSOURCEINFO;

typedef enum SPFILEMODE {
    SPFM_OPEN_READONLY,
    SPFM_OPEN_READWRITE,
    SPFM_CREATE,
    SPFM_CREATE_ALWAYS,
    SPFM_NUM_MODES,
} SPFILEMODE;

typedef enum SPGRAMMARSTATE {
    SPGS_ENABLED = 0,
    SPGS_DISABLED = 1,
    SPGS_EXCLUSIVE = 3,
} SPGRAMMARSTATE;

typedef enum SPGRAMMARWORDTYPE {
    SPWT_DISPLAY,
    SPWT_LEXICAL,
    SPWT_PRONUNCIATION,
} SPGRAMMARWORDTYPE;

typedef enum SPLEXICONTYPE {
    eLEXTYPE_USER = (1L << 0),
    eLEXTYPE_APP = (1L << 1),
    eLEXTYPE_RESERVED1 = (1L << 2),
    eLEXTYPE_RESERVED2 = (1L << 3),
    eLEXTYPE_RESERVED3 = (1L << 4),
    eLEXTYPE_RESERVED4 = (1L << 5),
    eLEXTYPE_RESERVED5 = (1L << 6),
    eLEXTYPE_RESERVED6 = (1L << 7),
    eLEXTYPE_RESERVED7 = (1L << 8),
    eLEXTYPE_RESERVED8 = (1L << 9),
    eLEXTYPE_RESERVED9 = (1L << 10),
    eLEXTYPE_RESERVED10 = (1L << 11),
    eLEXTYPE_PRIVATE1 = (1L << 12),
    eLEXTYPE_PRIVATE2 = (1L << 13),
    eLEXTYPE_PRIVATE3 = (1L << 14),
    eLEXTYPE_PRIVATE4 = (1L << 15),
    eLEXTYPE_PRIVATE5 = (1L << 16),
    eLEXTYPE_PRIVATE6 = (1L << 17),
    eLEXTYPE_PRIVATE7 = (1L << 18),
    eLEXTYPE_PRIVATE8 = (1L << 19),
    eLEXTYPE_PRIVATE9 = (1L << 20),
    eLEXTYPE_PRIVATE10 = (1L << 21),
    eLEXTYPE_PRIVATE11 = (1L << 22),
    eLEXTYPE_PRIVATE12 = (1L << 23),
    eLEXTYPE_PRIVATE13 = (1L << 24),
    eLEXTYPE_PRIVATE14 = (1L << 25),
    eLEXTYPE_PRIVATE15 = (1L << 26),
    eLEXTYPE_PRIVATE16 = (1L << 27),
    eLEXTYPE_PRIVATE17 = (1L << 28),
    eLEXTYPE_PRIVATE18 = (1L << 29),
    eLEXTYPE_PRIVATE19 = (1L << 30),
    eLEXTYPE_PRIVATE20 = (1L << 31),
} SPLEXICONTYPE;

typedef enum SPLOADOPTIONS {
    SPLO_STATIC = 0,
    SPLO_DYNAMIC = 1,
} SPLOADOPTIONS;

typedef struct SPPHRASEELEMENT {
    ULONG ulAudioTimeOffset;
    ULONG ulAudioSizeTime;
    ULONG ulAudioStreamOffset;
    ULONG ulAudioSizeBytes;
    ULONG ulRetainedStreamOffset;
    ULONG ulRetainedSizeBytes;
    const WCHAR * pszDisplayText;
    const WCHAR * pszLexicalForm;
    const SPPHONEID * pszPronunciation;
    BYTE bDisplayAttributes;
    char RequiredConfidence;
    char ActualConfidence;
    BYTE Reserved;
    float SREngineConfidence;
} SPPHRASEELEMENT;

typedef struct SPPATHENTRY {
    union {   SPTRANSITIONID hTransition;
    SPPHRASEELEMENT elem;
    };
} SPPATHENTRY;

typedef struct SPPARSEINFO {
    ULONG cbSize;
    SPRULEHANDLE hRule;
    ULONGLONG ullAudioStreamPosition;
    ULONG ulAudioSize;
    ULONG cTransitions;
    SPPATHENTRY * pPath;
    BOOL fHypothesis;
    GUID SREngineID;
    ULONG ulSREnginePrivateDataSize;
    const BYTE * pSREnginePrivateData;
} SPPARSEINFO;

typedef enum SPPARTOFSPEECH {
    SPPS_NotOverriden = -1,  /* --- SAPI5 public POS category values (bits 28-31) */
    SPPS_Unknown = 0,
    SPPS_Noun = 0x1000,
    SPPS_Verb = 0x2000,
    SPPS_Modifier = 0x3000,
    SPPS_Function = 0x4000,
    SPPS_Interjection = 0x5000,
} SPPARTOFSPEECH;

typedef enum SPPHRASERNG {
    SPPR_ALL_ELEMENTS = -1,
} SPPHRASERNG;

typedef enum SPPROPSRC {
    SPPROPSRC_RECO_INST,
    SPPROPSRC_RECO_CTX,
    SPPROPSRC_RECO_GRAMMAR,
} SPPROPSRC;

typedef struct SPRECOCONTEXTSTATUS {
    SPINTERFERENCE eInterference;
    WCHAR szRequestTypeOfUI [ 255 ];
    DWORD dwReserved1;
    DWORD dwReserved2;
} SPRECOCONTEXTSTATUS;

typedef enum SPRECOEVENTFLAGS {
    SPREF_AutoPause = (1 << 0), SPREF_Emulated = (1 << 1),
} SPRECOEVENTFLAGS;

typedef enum SPRESULTTYPE {
    SPRT_CFG = 0,
    SPRT_SLM = 1,
    SPRT_PROPRIETARY = 2,
    SPRT_FALSE_RECOGNITION = (1 << 1),
} SPRESULTTYPE;

typedef struct SPRECORESULTINFO {
    ULONG cbSize;
    SPRESULTTYPE ResultType;
    BOOL fHypothesis;
    BOOL fProprietaryAutoPause;
    ULONGLONG ullStreamPosStart;
    ULONGLONG ullStreamPosEnd;
    SPGRAMMARHANDLE hGrammar;
    ULONG ulSizeEngineData;
    void * pvEngineData;
    ISpPhraseBuilder * pPhrase;
} SPRECORESULTINFO;

typedef struct SPRECORESULTTIMES {
    FILETIME ftStreamTime;
    ULONGLONG ullLength;
    DWORD dwTickCount;
    ULONGLONG ullStart;
} SPRECORESULTTIMES;

typedef enum SPRECOSTATE {
    SPRST_INACTIVE,
    SPRST_ACTIVE,
    SPRST_ACTIVE_ALWAYS,
    SPRST_INACTIVE_WITH_PURGE,
    SPRST_NUM_STATES,
} SPRECOSTATE;

typedef struct SPRULEENTRY {
    SPRULEHANDLE hRule;
    SPSTATEHANDLE hInitialState;
    DWORD Attributes;
    void * pvClientContext;
    void * pvClientGrammarContext;
} SPRULEENTRY;

typedef enum SPRULEINFOOPT {
    SPRIO_NONE = 0,
} SPRULEINFOOPT;

typedef enum SPRULESTATE {
    SPRS_INACTIVE = 0,
    SPRS_ACTIVE = 1,
    SPRS_ACTIVE_WITH_AUTO_PAUSE = 3,
} SPRULESTATE;

typedef enum SPRUNSTATE {
    SPRS_DONE = (1L << 0),
    SPRS_IS_SPEAKING = (1L << 1),
} SPRUNSTATE;

typedef struct SPSERIALIZEDEVENT {
    WORD eEventId;
    WORD elParamType;
    ULONG ulStreamNum;
    ULONGLONG ullAudioStreamOffset;
    ULONG SerializedwParam;
    LONG SerializedlParam;
} SPSERIALIZEDEVENT;

typedef struct SPSERIALIZEDEVENT64 {
    WORD eEventId;
    WORD elParamType;
    ULONG ulStreamNum;
    ULONGLONG ullAudioStreamOffset;
    ULONGLONG SerializedwParam;
    LONG LONGSerializedlParam;
} SPSERIALIZEDEVENT64;

typedef struct SPSERIALIZEDRESULT {
    ULONG ulSerializedSize;
} SPSERIALIZEDRESULT;

typedef struct SPWORDPRONUNCIATION {
    struct SPWORDPRONUNCIATION * pNextWordPronunciation;
    SPLEXICONTYPE eLexiconType;
    LANGID LangID;
    WORD wReserved;
    SPPARTOFSPEECH ePartOfSpeech;
    SPPHONEID szPronunciation [ 1 ];
} SPWORDPRONUNCIATION;

typedef enum SPWORDTYPE {
    eWORDTYPE_ADDED = (1L << 0),
    eWORDTYPE_DELETED = (1L << 1),
} SPWORDTYPE;

typedef struct SPWORD {
    struct SPWORD * pNextWord;
    LANGID LangID;
    WORD wReserved;
    SPWORDTYPE eWordType;
    WCHAR * pszWord;
    SPWORDPRONUNCIATION * pFirstWordPronunciation;
} SPWORD;

typedef struct SPTRANSITIONENTRY {
    SPTRANSITIONID ID;
    SPSTATEHANDLE hNextState;
    BYTE Type;
    char RequiredConfidence;
    struct   {   DWORD fHasProperty;
    };
    float Weight;
    union   {   struct   {   SPSTATEHANDLE hRuleInitialState;
    SPRULEHANDLE hRule;
    void * pvClientRuleContext;
    };
    struct   {   SPWORD HANDLEhWord;
    void * pvClientWordContext;
    };
    struct   {   void * pvGrammarCookie;
    };
    };
} SPTRANSITIONENTRY;

typedef struct SPSTATEINFO {
    ULONG cAllocatedEntries;
    SPTRANSITIONENTRY * pTransitions;
    ULONG cEpsilons;
    ULONG cRules;
    ULONG cWords;
    ULONG cSpecialTransitions;
} SPSTATEINFO;

typedef enum SPSTREAMFORMAT {
    SPSF_Default = -1,
    SPSF_NoAssignedFormat = 0,
    SPSF_Text,
    SPSF_NonStandardFormat,
    SPSF_ExtendedAudioFormat,
    /* Standard PCM wave formats SPSF_8kHz8BitMono */
    SPSF_8kHz8BitStereo,
    SPSF_8kHz16BitMono,
    SPSF_8kHz16BitStereo,
    SPSF_11kHz8BitMono,
    SPSF_11kHz8BitStereo,
    SPSF_11kHz16BitMono,
    SPSF_11kHz16BitStereo,
    SPSF_12kHz8BitMono,
    SPSF_12kHz8BitStereo,
    SPSF_12kHz16BitMono,
    SPSF_12kHz16BitStereo,
    SPSF_16kHz8BitMono,
    SPSF_16kHz8BitStereo,
    SPSF_16kHz16BitMono,
    SPSF_16kHz16BitStereo,
    SPSF_22kHz8BitMono,
    SPSF_22kHz8BitStereo,
    SPSF_22kHz16BitMono,
    SPSF_22kHz16BitStereo,
    SPSF_24kHz8BitMono,
    SPSF_24kHz8BitStereo,
    SPSF_24kHz16BitMono,
    SPSF_24kHz16BitStereo,
    SPSF_32kHz8BitMono,
    SPSF_32kHz8BitStereo,
    SPSF_32kHz16BitMono,
    SPSF_32kHz16BitStereo,
    SPSF_44kHz8BitMono,
    SPSF_44kHz8BitStereo,
    SPSF_44kHz16BitMono,
    SPSF_44kHz16BitStereo,
    SPSF_48kHz8BitMono,
    SPSF_48kHz8BitStereo,
    SPSF_48kHz16BitMono,
    SPSF_48kHz16BitStereo,
    /* TrueSpeech format SPSF_TrueSpeech_8kHz1BitMono */
    /* A-Law formats SPSF_CCITT_ALaw_8kHzMono */
    SPSF_CCITT_ALaw_8kHzStereo,
    SPSF_CCITT_ALaw_11kHzMono,
    SPSF_CCITT_ALaw_11kHzStereo,
    SPSF_CCITT_ALaw_22kHzMono,
    SPSF_CCITT_ALaw_22kHzStereo,
    SPSF_CCITT_ALaw_44kHzMono,
    SPSF_CCITT_ALaw_44kHzStereo,
    /* u-Law formats SPSF_CCITT_uLaw_8kHzMono */
    SPSF_CCITT_uLaw_8kHzStereo,
    SPSF_CCITT_uLaw_11kHzMono,
    SPSF_CCITT_uLaw_11kHzStereo,
    SPSF_CCITT_uLaw_22kHzMono,
    SPSF_CCITT_uLaw_22kHzStereo,
    SPSF_CCITT_uLaw_44kHzMono,
    SPSF_CCITT_uLaw_44kHzStereo,
    /* ADPCM formats SPSF_ADPCM_8kHzMono */
    SPSF_ADPCM_8kHzStereo,
    SPSF_ADPCM_11kHzMono,
    SPSF_ADPCM_11kHzStereo,
    SPSF_ADPCM_22kHzMono,
    SPSF_ADPCM_22kHzStereo,
    SPSF_ADPCM_44kHzMono,
    SPSF_ADPCM_44kHzStereo,
    /* GSM 6.10 formats SPSF_GSM610_8kHzMono */
    SPSF_GSM610_11kHzMono,
    SPSF_GSM610_22kHzMono,
    SPSF_GSM610_44kHzMono,
    SPSF_NUM_FORMATS,
} SPSTREAMFORMAT;

typedef struct SPTMTHREADINFO {
    long lPoolSize;
    long lPriority;
    ULONG ulConcurrencyLimit;
    ULONG ulMaxQuickAllocThreads;
} SPTMTHREADINFO;

typedef struct SPTRANSITIONPROPERTY {
    const WCHAR * pszName;
    ULONG ulId;
    const WCHAR * pszValue;
    VARIANT vValue;
} SPTRANSITIONPROPERTY;

typedef enum SPTRANSITIONTYPE {
    SPTRANSEPSILON,
    SPTRANSWORD,
    SPTRANSRULE,
    SPTRANSTEXTBUF,
    SPTRANSWILDCARD,
    SPTRANSDICTATION,
} SPTRANSITIONTYPE;

typedef enum SPVACTIONS {
    SPVA_Speak = 0,
    SPVA_Silence,
    SPVA_Pronounce,
    SPVA_Bookmark,
    SPVA_SpellOut,
    SPVA_Section,
    SPVA_ParseUnknownTag,
} SPVACTIONS;

typedef enum SPVALUETYPE {
    SPDF_PROPERTY = 0x00000001,
    SPDF_REPLACEMENT = 0x00000002,
    SPDF_RULE = 0x00000004,
    SPDF_DISPLAYTEXT = 0x00000008,
    SPDF_LEXICALFORM = 0x00000010,
    SPDF_PRONUNCIATION = 0x00000020,
    SPDF_AUDIO = 0x00000040,
    SPDF_ALTERNATES = 0x00000080,
    SPDF_ALL = 0x000000FF,
} SPVALUETYPE;

typedef struct SPVCONTEXT {
    LPCWSTR pCategory;
    LPCWSTR pBefore;
    LPCWSTR pAfter;
} SPVCONTEXT;

typedef enum SPVESACTIONS {
    SPVES_CONTINUE = 0,
    SPVES_ABORT = ( 1L << 0 ),
    SPVES_SKIP = ( 1L << 1 ),
    SPVES_RATE = ( 1L << 2 ),
    SPVES_VOLUME = ( 1L << 3 ),
} SPVESACTIONS;

typedef enum SPVFEATURE {
    SPVFEATURE_STRESSED = (1L << 0),
    SPVFEATURE_EMPHASIS = (1L << 1),
} SPVFEATURE;

typedef enum SPVISEMES {
    SP_VISEME_0 = 0,  /* English examples //------------------ */
    SP_VISEME_1,
    SP_VISEME_2,
    SP_VISEME_3,
    SP_VISEME_4,
    SP_VISEME_5,
    SP_VISEME_6,
    SP_VISEME_7,
    SP_VISEME_8,
    SP_VISEME_9,
    SP_VISEME_10,
    SP_VISEME_11,
    SP_VISEME_12,
    SP_VISEME_13,
    SP_VISEME_14,
    SP_VISEME_15,
    SP_VISEME_16,
    SP_VISEME_17,
    SP_VISEME_18,
    SP_VISEME_19,
    SP_VISEME_20,
    SP_VISEME_21,
} SPVISEMES;

typedef enum SPVLIMITS {
    SPMIN_VOLUME = 0,
    SPMAX_VOLUME = 100,
    SPMIN_RATE = -10,
    SPMAX_RATE = 10,
} SPVLIMITS;

typedef struct SPVOICESTATUS {
    ULONG ulCurrentStream;
    ULONG ulLastStreamQueued;
    HRESULT hrLastResult;
    DWORD dwRunningState;
    ULONG ulInputWordPos;
    ULONG ulInputWordLen;
    ULONG ulInputSentPos;
    ULONG ulInputSentLen;
    LONG lBookmarkId;
    SPPHONEID PhonemeId;
    SPVISEMES VisemeId;
    DWORD dwReserved1;
    DWORD dwReserved2;
} SPVOICESTATUS;

typedef struct SPVPITCH {
    long MiddleAdj;
    long RangeAdj;
} SPVPITCH;

typedef enum SPVPRIORITY {
    SPVPRI_NORMAL = 0,
    SPVPRI_ALERT = (1L << 0),
    SPVPRI_OVER = (1L << 1),
} SPVPRIORITY;

typedef enum SPVSKIPTYPE {
    SPVST_SENTENCE = (1L << 0),
} SPVSKIPTYPE;

typedef struct SPVSTATE {
    SPVACTIONS eAction;
    LANGID LangID;
    WORD wReserved;
    long EmphAdj;
    long RateAdj;
    ULONG Volume;
    SPVPITCH PitchAdj;
    ULONG SilenceMSecs;
    SPPHONEID * pPhoneIds;
    SPPARTOFSPEECH ePartOfSpeech;
    SPVCONTEXT Context;
} SPVSTATE;

typedef struct SPVTEXTFRAG {
    struct SPVTEXTFRAG * pNext;
    SPVSTATE State;
    LPCWSTR pTextStart;
    ULONG ulTextLen;
    ULONG ulTextSrcOffset;
} SPVTEXTFRAG;

typedef enum SPWAVEFORMATTYPE {
    SPWF_INPUT,
    SPWF_SRENGINE,
} SPSTREAMFORMATTYPE;

typedef struct SPWORDENTRY {
    SPWORD HANDLEhWord;
    LANGID LangID;
    const WCHAR * pszDisplayText;
    const WCHAR * pszLexicalForm;
    SPPHONEID * aPhoneId;
    void * pvClientContext;
} SPWORDENTRY;

typedef enum SPWORDINFOOPT {
    SPWIO_NONE = 0,
    SPWIO_WANT_TEXT = 1,
} SPWORDINFOOPT;

typedef struct SPWORDLIST {
    ULONG ulSize;
    BYTE * pvBuffer;
    SPWORD * pFirstWord;
} SPWORDLIST;

typedef enum SPWORDPRONOUNCEABLE {
    SPWP_UNKNOWN_WORD_UNPRONOUNCEABLE = 0,
    SPWP_UNKNOWN_WORD_PRONOUNCEABLE = 1,
    SPWP_KNOWN_WORD_PRONOUNCEABLE = 2,
} SPWORDPRONOUNCEABLE;

typedef struct SPWORDPRONUNCIATIONLIST {
    ULONG ulSize;
    BYTE * pvBuffer;
    SPWORDPRONUNCIATION * pFirstWordPronunciation;
} SPWORDPRONUNCIATIONLIST;

typedef enum _SPAUDIOSTATE {
    SPAS_CLOSED,
    SPAS_STOP,
    SPAS_PAUSE,
    SPAS_RUN,
} SPAUDIOSTATE;

typedef enum tagSPDISPLYATTRIBUTES {
    SPAF_ONE_TRAILING_SPACE = 0x02,
    SPAF_TWO_TRAILING_SPACES = 0x04,
    SPAF_CONSUME_LEADING_SPACES = 0x08,
    SPAF_ALL = 0x0F,
} SPDISPLAYATTRIBUTES;

typedef struct SPAUDIOSTATUS {
    long   cbFreeBuffSpace;
    ULONG   cbNonBlockingIO;
    SPAUDIOSTATE   State;
    ULONGLONG   CurSeekPos;
    ULONGLONG   CurDevicePos;
    DWORD   dwReserved1;
    DWORD   dwReserved2;
} SPAUDIOSTATUS;

typedef struct tagSPPHRASEALT {
    ISpPhraseBuilder * pPhrase;
    ULONG ulStartElementInParent;
    ULONG cElementsInParent;
    ULONG cElementsInAlternate;
    void * pvAltExtra;
    ULONG cbAltExtra;
} SPPHRASEALT;

typedef struct tagSPPHRASEALTREQUEST {
    ULONG ulStartElement;
    ULONG cElements;
    ULONG ulRequestAltCount;
    void * pvResultExtra;
    ULONG cbResultExtra;
    ISpPhrase * pPhrase;
    ISpRecoContext * pRecoContext;
} SPPHRASEALTREQUEST;



typedef struct tagSPPROPERTYINFO {
    const WCHAR * pszName;
    ULONG ulId;
    const WCHAR * pszValue;
    VARIANT vValue;
} SPPROPERTYINFO;

typedef struct tagSPPHRASEREPLACEMENT {
    BYTE bDisplayAttributes;
    const WCHAR * pszReplacementText;
    ULONG ulFirstElement;
    ULONG ulCountOfElements;
} SPPHRASEREPLACEMENT;

typedef struct tagSPPHRASERULE {
    const WCHAR * pszName;
    ULONG ulId;
    ULONG ulFirstElement;
    ULONG ulCountOfElements;
    const struct tagSPPHRASERULE * pNextSibling;
    const struct tagSPPHRASERULE * pFirstChild;
    float SREngineConfidence;
    signed charConfidence;
} SPPHRASERULE;

/* ms895689 "SPPHRASEPROPERTY" -- verbatim print (struct-tag form,
 * eaten spaces repaired; self-references use the struct-keyword form):
 *   struct SPPHRASEPROPERTY{ const WCHAR* pszName; ULONG ulId;
 *     const WCHAR* pszValue; VARIANT vValue; ULONG ulFirstElement;
 *     ULONG ulCountOfElements; const SPPHRASEPROPERTY* pNextSibling;
 *     const SPPHRASEPROPERTY* pFirstChild; char SREngineConfidence;
 *     char Confidence;};                                               */
typedef struct SPPHRASEPROPERTY {
    const WCHAR * pszName;
    ULONG   ulId;
    const WCHAR * pszValue;
    VARIANT   vValue;
    ULONG   ulFirstElement;
    ULONG   ulCountOfElements;
    const struct SPPHRASEPROPERTY * pNextSibling;
    const struct SPPHRASEPROPERTY * pFirstChild;
    char   SREngineConfidence;
    char   Confidence;
} SPPHRASEPROPERTY;

typedef struct SPPHRASE {
    ULONG cbSize;
    LANGID LangID;
    WORD wReserved;
    ULONGLONG ullGrammarID;
    ULONGLONG ftStartTime;
    ULONGLONG ullAudioStreamPosition;
    ULONG ulAudioSizeBytes;
    ULONG ulRetainedSizeBytes;
    ULONG ulAudioSizeTime;
    SPPHRASERULE Rule;
    const SPPHRASEPROPERTY *pProperties;
    const SPPHRASEELEMENT * pElements;
    ULONG cReplacements;
    const SPPHRASEREPLACEMENT * pReplacements;
    GUID SREngineID;
    ULONG ulSREnginePrivateDataSize;
    const BYTE * pSREnginePrivateData;
} SPPHRASE;

typedef struct tagSPSERIALIZEDPHRASE {
    ULONG ulSerializedSize;
} SPSERIALIZEDPHRASE;

typedef struct tagSPTEXTSELECTIONINFO {
    ULONG ulStartActiveOffset;
    ULONG cchActiveChars;
    ULONG ulStartSelection;
    ULONG cchSelection;
} SPTEXTSELECTIONINFO;

/* ms895729 "SPRECOGNIZERSTATUS" -- HELD as a verbatim record (not
 * compiled): the print sizes aLangID with SP_MAX_LANGIDS, whose value
 * no CE page (or CE 6.0 twin) publishes; sizing the array would
 * invent an ABI constant (zero-gap policy; the D3DMADAPTER_IDENTIFIER
 * decision, M67).  Verbatim print (eaten spaces repaired):
 *   typedef struct SPRECOGNIZERSTATUS{ SPAUDIOSTATUS AudioStatus;
 *     ULONGLONG ullStreamPos; ULONG ulStreamNumber; ULONG ulNumActive;
 *     CLSID clsidEngine; ULONG cLangIDs; LANGID aLangID[SP_MAX_LANGIDS];
 *     DWORD dwReserved1; DWORD dwReserved2;} SPRECOGNIZERSTATUS;      */

/* Sphelper.h helper functions / SAPI Macros -- printed as C++ inline
 * functions and templates with "Link Library: Sapilib.lib" rows
 * (header-side code, not import symbols; recorded verbatim, not
 * compiled):
 *   ms893484 SPBindToFile: inline HRESULT SPBindToFile(LPCWSTR pFileName,SPFILEMODE eMode,ISpStream** ppStream,const GUID* pFormatId = NULL,const WAVEFORMATEX* pWaveFormatEx = NULL,ULONGLONG* ullEventInterest = SPFEI_ALL_EVENTS);;
 *   ms895404 SPFEI: SPFEI(void* SPEI_ord);;
 *   ms893488 SpClearEvent: inline void SpClearEvent(SPEVENT* pe);;
 *   ms893490 SpConvertStreamFormatEnum: inline HRESULT SpConvertStreamFormatEnum(SPSTREAMFORMAT eFormat,GUID* pFormatId,WAVEFORMATEX** ppCoMemWaveFormatEx);;
 *   ms893491 SpCreateBestObject: HRESULT SpCreateBestObject(constWCHAR* pszCategoryId,constWCHAR* pszReqAttribs,constWCHAR* pszOptAttribs,T** ppObject,IUnknown* pUnkOuter=NULL,DWORDdwClsCtxt=CLSCTX_ALL,);;
 *   ms893492 SpCreateDefaultObjectFromCategoryId: HRESULT SpCreateDefaultObjectFromCategoryId(constWCHAR* pszCategoryId,T** ppObject,IUnknown* pUnkOuter=NULL,DWORDdwClsCtxt=CLSCTX_ALL);;
 *   ms893497 SpCreateObjectFromSubToken: HRESULT SpCreateObjectFromSubToken(ISpObjectToken* pToken,constWCHAR* pszSubKeyName,T** ppObject,IUnknownpUnkOuter= NULL,DWORD* dwClsCtxt= CLSCTX_ALL);;
 *   ms893498 SpCreateObjectFromToken: HRESULT SpCreateObjectFromToken(ISpObjectToken* pToken,T** ppObject,IUnknown* pUnkOuter=NULL,DWORDdwClsCtxt=CLSCTX_ALL);;
 *   ms893499 SpCreateObjectFromTokenId: HRESULT SpCreateObjectFromTokenId(constWCHAR* pszTokenId,T** ppObject,IUnknown* pUnkOuter=NULL,DWORDdwClsCtxt=CLSCTX_ALL);;
 *   ms893500 SpCreatePhoneConverter: inline HRESULT SpCreatePhoneConverter(LANGID* langid,constWCHAR* pszReqAttribs,constWCHAR* pszOptAttribs,ISpPhoneConverter**ppPhoneConverter);;
 *   ms895368 SpEnumTokens: inline HRESULT SpEnumTokens(const WCHAR* pszCategoryId,const WCHAR* pszReqAttribs,const WCHAR* pszOptAttribs,IEnumSpObjectTokens** ppEnum);;
 *   ms895391 SpEventSerializeSize: inline ULONG SpEventSerializeSize(const SPEVENT* pEvent);;
 *   ms895413 SpFindBestToken: inline HRESULT SpFindBestToken(const WCHAR* pszCategoryId, const WCHAR* pszReqAttribs, const WCHAR* pszOptAttribs, ISpObjectToken** ppObjectToken);;
 *   ms895420 SpGetCategoryFromId: inline HRESULT SpGetCategoryFromId(const WCHAR* pszCategoryId,ISpObjectTokenCategory** ppCategory,BOOL fCreateIfNotExist = FALSE);;
 *   ms895426 SpGetDefaultTokenFromCategoryId: inline HRESULT SpGetDefaultTokenFromCategoryId(const WCHAR* pszCategoryId,ISpObjectToken** ppToken, BOOL fCreateCategoryIfNotExist = TRUE);;
 *   ms895516 SpGetDefaultTokenIdFromCategoryId: inline HRESULT SpGetDefaultTokenIdFromCategoryId(const WCHAR* pszCategoryId,WCHAR** ppszTokenId);;
 *   ms895523 SpGetDescription: inline HRESULT SpGetDescription(ISpObjectToken* pObjToken,WCHAR** ppszDescription,LANGID* Language = SpGetUserDefaultUILanguage());;
 *   ms895527 SpGetSubTokenFromToken: inline HRESULT SpGetSubTokenFromToken(ISpObjectToken* pToken,const WCHAR* pszSubKeyName,ISpObjectToken** ppToken,BOOL fCreateIfNotExist = FALSE);;
 *   ms895534 SpGetTokenFromId: inline HRESULT SpGetTokenFromId(const WCHAR* pszTokenId,ISpObjectToken** ppToken,BOOL* fCreateIfNotExist = FALSE);;
 *   ms895542 SpGetUserDefaultUILanguage: inline LANGID SpGetUserDefaultUILanguage(void);;
 *   ms895573 SpInitEvent: inline void SpInitEvent(SPEVENT* pe);;
 *   ms895792 SpSetCommonTokenData: inline HRESULT SpSetCommonTokenData(ISpObjectToken* pToken,const CLSID* pclsid,const WCHAR* pszLangIndependentName,LANGID langid,const WCHAR* pszLangDependentName,ISpDataKey** ppDataKeyAttribs);;
 *   ms895795 SpSetDefaultTokenForCategoryId: inline HRESULT SpSetDefaultTokenForCategoryId(const WCHAR* pszCategoryId,ISpObjectToken* pToken);;
 *   ms895800 SpSetDefaultTokenIdForCategoryId: inline HRESULT SpSetDefaultTokenIdForCategoryId(const WCHAR* pszCategoryId,const WCHAR* pszTokenId);;
 *   ms895805 SpSetDescription: inline HRESULT SpSetDescription(ISpObjectToken* pObjToken,const WCHAR* pszDescription,LANGID Language = SpGetUserDefaultUILanguage(),BOOL fSetLangIndependentId = TRUE);;
 */

/* IEnumSpObjectTokens: documented methods (6 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   aa515641 Clone: HRESULT Clone( IEnumSpObjectTokens** ppEnum);
 *   aa515643 GetCount: HRESULT GetCount( ULONG* pulCount);
 *   aa515645 Item: HRESULT Item( ULONG Index, ISpObjectToken** ppToken);
 *   aa515648 Next: HRESULT Next( ULONG celt, ISpObjectToken** pelt, ULONG*
 *      pceltFetched);
 *   aa515651 Reset: HRESULT Reset(void);
 *   aa515653 Skip: HRESULT Skip( ULONG celt);
 */

/* ISpAudio: documented methods (9 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms886219 EventHandle: HANDLE EventHandle(void);
 *   ms886228 GetBufferInfo: HRESULT GetBufferInfo(SPAUDIOBUFFERINFO*
 *      pBuffInfo);
 *   ms886240 GetBufferNotifySize: HRESULT GetBufferNotifySize(ULONG*
 *      pcbSize);
 *   ms886253 GetDefaultFormat: HRESULT GetDefaultFormat(GUID*
 *      pFormatId,WAVEFORMATEX** ppCoMemWaveFormatEx);
 *   ms886263 GetStatus: HRESULT GetStatus(SPAUDIOSTATUS* pStatus);
 *   ms886272 SetBufferInfo: HRESULT SetBufferInfo(const SPAUDIOBUFFERINFO*
 *      pBuffInfo);
 *   ms886286 SetBufferNotifySize: HRESULT SetBufferNotifySize(ULONG cbSize);
 *   ms886294 SetFormat: HRESULT SetFormat(REFGUID rguidFmtId,const
 *      WAVEFORMATEX* pWaveFormatEx);
 *   ms886301 SetState: HRESULT SetState(SPAUDIOSTATE NewState,ULONGLONG
 *      ullReserved);
 */

/* ISpCFGInterpreter: documented methods (2 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms886319 InitGrammar: HRESULT InitGrammar( const WCHAR* pszGrammarName,
 *      const void** pvGrammarData);
 *   ms886330 Interpret: HRESULT Interpret( ISpPhraseBuilder* pPhrase, const
 *      ULONG ulFirstElement, const ULONG ulCountOfElements,
 *      ISpCFGInterpreterSite* pSite);
 */

/* ISpCFGInterpreterSite: documented methods (3 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms886356 AddProperty: HRESULT AddProperty( const SPPHRASEPROPERTY*
 *      pProperty);
 *   ms886366 AddTextReplacement: HRESULT AddTextReplacement(
 *      SPPHRASEREPLACEMENT* pReplace);
 *   ms886462 GetResourceValue: HRESULT GetResourceValue( const WCHAR*
 *      pszResourceName, WCHAR** ppCoMemResource);
 */

/* ISpContainerLexicon: documented methods (1 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms886487 AddLexicon: HRESULT AddLexicon(ISpLexicon* pAddLexicon,DWORD
 *      dwFlags);
 */

/* ISpDataKey: documented methods (12 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms886494 CreateKey: HRESULT CreateKey( const WCHAR* pszSubKeyName,
 *      ISpDataKey** ppSubKey);
 *   ms886502 DeleteKey: HRESULT DeleteKey( const WCHAR* pszSubKeyName);
 *   ms886614 DeleteValue: HRESULT DeleteValue( const WCHAR* pszValueName);
 *   ms886824 EnumKeys: HRESULT EnumKeys( ULONG Index, WCHAR**
 *      ppszSubKeyName);
 *   ms886831 EnumValues: HRESULT EnumValues( ULONG Index, WCHAR**
 *      ppszValueName);
 *   ms886833 GetDWORD: HRESULT GetDWORD( const WCHAR* pszKeyName, DWORD*
 *      pdwValue);
 *   ms886832 GetData: HRESULT GetData( const WCHAR* pszValueName, ULONG*
 *      pcbData, BYTE* pData);
 *   ms886834 GetStringValue: HRESULT GetStringValue( const WCHAR*
 *      pszValueName, WCHAR** ppszValue);
 *   ms886835 OpenKey: HRESULT OpenKey( const WCHAR* pszSubKeyName,
 *      ISpDataKey** ppSubKey);
 *   ms886837 SetDWORD: HRESULT SetDWORD( const WCHAR* pszKeyName DWORD
 *      dwValue);
 *   ms886836 SetData: HRESULT SetData( const WCHAR* pszValueName, ULONG
 *      cbData, const BYTE* pData);
 *   ms886838 SetStringValue: HRESULT SetStringValue( const WCHAR*
 *      pszValueName, const WCHAR* pszValue);
 */

/* ISpErrorLog: documented methods (1 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms886840 AddError: HRESULT AddError( const long lLineNumber, HRESULT hr,
 *      const WCHAR* pszDescription, const WCHAR* pszHelpFile, DWORD
 *      dwHelpContext);
 */

/* ISpEventSink: documented methods (2 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms886842 AddEvents: HRESULT AddEvents( const SPEVENT* pEventArray, ULONG
 *      ulCount);
 *   ms886843 GetEventInterest: HRESULT GetEventInterest( ULONGLONG*
 *      pullEventInterest);
 */

/* ISpEventSource: documented methods (3 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms886845 GetEvents: HRESULT GetEvents( ULONG ulCount, SPEVENT*
 *      pEventArray, ULONG* pulFetched);
 *   ms886846 GetInfo: HRESULT GetInfo( SPEVENTSOURCEINFO* pInfo);
 *   ms886847 SetInterest: HRESULT SetInterest( ULONGLONG ullEventInterest,
 *      ULONGLONG ullQueuedInterest);
 */

/* ISpGramCompBackend: documented methods (2 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms886849 InitFromBinaryGrammar: HRESULT InitFromBinaryGrammar( const
 *      SPBINARYGRAMMAR* pBinaryData);
 *   ms886850 SetSaveObjects: HRESULT SetSaveObjects( IStream* pStream,
 *      ISpErrorLog* pErrorLog);
 */

/* ISpGrammarBuilder: documented methods (8 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms886852 AddResource: HRESULT AddResource(SPSTATEHANDLE hRuleState,const
 *      WCHAR* pszResourceName,const WCHAR* pszResourceValue);
 *   ms886853 AddRuleTransition: HRESULT AddRuleTransition(SPSTATEHANDLE
 *      hFromState,SPSTATEHANDLE hToState,SPSTATEHANDLE hRule,float
 *      Weight,const SPPROPERTYINFO* pPropInfo);
 *   ms886854 AddWordTransition: HRESULT AddWordTransition(SPSTATEHANDLE
 *      hFromState,SPSTATEHANDLE hToState,const WCHAR* psz,const WCHAR*
 *      pszSeperators,SPGRAMMARWORDTYPE eWordType,float Weight,const
 *      SPPROPERTYINFO* pPropInfo);
 *   ms886855 ClearRule: HRESULT ClearRule(SPSTATEHANDLE hState);
 *   ms886856 Commit: HRESULT Commit(DWORD dwReserved);
 *   ms886857 CreateNewState: HRESULT CreateNewState(SPSTATEHANDLE
 *      hState,SPSTATEHANDLE* phState);
 *   ms886858 GetRule: HRESULT GetRule(const WCHAR* pszRuleName,DWORD
 *      dwRuleId,DWORD dwAttributes,BOOL fCreateIfNotExist,SPSTATEHANDLE*
 *      phInitialState);
 *   ms886859 ResetGrammar: HRESULT ResetGrammar(LANGID NewLanguage);
 */

/* ISpGrammarCompiler: documented methods (1 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms886861 CompileStream: HRESULT CompileStream( IStream* pSource,
 *      IStream* pDest, IStream* pHeader, IUnknown* pReserved, ISpErrorLog*
 *      pErrorLog, DWORD dwFlags);
 */

/* ISpITNProcessor: documented methods (2 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms886863 ITNPhrase: HRESULT ITNPhrase( ISpPhraseBuilder* pPhrase);
 *   ms886864 LoadITNGrammar: HRESULT LoadITNGrammar( WCHAR* pszCLSID);
 */

/* ISpLexicon: documented methods (6 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms886866 AddPronunciation: HRESULT AddPronunciation(const WCHAR*
 *      pszWord,LANGID LangID,SPPARTOFSPEECH ePartOfSpeech,const SPPHONEID*
 *      pszPronunciation);
 *   ms886867 GetGeneration: HRESULT GetGeneration(DWORD* pdwGeneration);
 *   ms886868 GetGenerationChange: HRESULT GetGenerationChange(DWORD
 *      dwFlags,DWORD* pdwGeneration,SPWORDLIST* pWordList);
 *   ms886869 GetPronunciations: HRESULT GetPronunciations(const WCHAR*
 *      pszWord,LANGID LangID,DWORD dwFlags,SPWORDPRONUNCIATIONLIST*
 *      pWordPronunciationList);
 *   ms886870 GetWords: HRESULT GetWords(DWORD dwFlags,DWORD*
 *      pdwGeneration,DWORD* pdwCookie,SPWORDLIST* pWordList);
 *   ms886871 RemovePronunciation: HRESULT RemovePronunciation(const WCHAR*
 *      pszWord,LANGID LangID,SPPARTOFSPEECH ePartOfSpeech,void* pvReserved);
 */

/* ISpMMSysAudio: documented methods (7 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms886873 GetDeviceId: HRESULT GetDeviceId(UINT* puDeviceId);
 *   ms886874 GetLineId: HRESULT GetLineId(UINT* puLineId);
 *   ms886875 GetMMHandle: HRESULT GetMMHandle(void** pHandle);
 *   ms886876 Read: HRESULT Read(void* pv, ULONG cb,ULONG* pcbRead);
 *   ms886877 SetDeviceId: HRESULT SetDeviceId( UINT uDeviceId);
 *   ms886878 SetLineId: HRESULT SetLineId( UINT uLineId);
 *   ms886879 Write: HRESULT Write( const void* pv, ULONG cb,ULONG*
 *      pcbWritten);
 */

/* ISpNotifyCallback: documented methods (1 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms886881 NotifyCallback: HRESULT NotifyCallback( WPARAM wParam, LPARAM
 *      lParam);
 */

/* ISpNotifySink: documented methods (1 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms886883 Notify: HRESULT Notify(void);
 */

/* ISpNotifySource: documented methods (7 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms886885 GetNotifyEventHandle: HANDLE GetNotifyEventHandle(void);
 *   ms886886 SetNotifyCallbackFunction: HRESULT SetNotifyCallbackFunction(
 *      SPNOTIFYCALLBACK* pfnCallback, WPARAM wParam, LPARAM lParam);
 *   ms886887 SetNotifyCallbackInterface: HRESULT SetNotifyCallbackInterface(
 *      ISpNotifyCallback* pSpCallback, WPARAM wParam, LPARAM lParam);
 *   ms886889 SetNotifySink: HRESULT SetNotifySink( ISpNotifySink*
 *      pNotifySink);
 *   ms886890 SetNotifyWin32Event: HRESULT SetNotifyWin32Event(void);
 *   ms886891 SetNotifyWindowMessage: HRESULT SetNotifyWindowMessage( HWND
 *      hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
 *   ms886892 WaitForNotifyEvent: HRESULT WaitForNotifyEvent( DWORD
 *      dwMilliseconds);
 */

/* ISpNotifyTranslator: documented methods (6 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms886894 GetEventHandle: HANDLE GetEventHandle(void);
 *   ms886895 InitCallback: HRESULT InitCallback( SPNOTIFYCALLBACK*
 *      pfnCallback, WPARAM wParam, LPARAM lParam);
 *   ms886896 InitSpNotifyCallback: HRESULT InitSpNotifyCallback(
 *      ISpNotifyCallback* pSpCallback, WPARAM wParam, LPARAM lParam);
 *   ms886897 InitWin32Event: HRESULT InitWin32Event( HANDLE hEvent, BOOL
 *      fCloseHandleOnRelease);
 *   ms886898 InitWindowMessage: HRESULT InitWindowMessage( HWND hWnd, UINT
 *      Msg, WPARAM wParam, LPARAM lParam);
 *   ms886899 Wait: HRESULT Wait( DWORD dwMilliseconds);
 */

/* ISpObjectToken: documented methods (10 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms886908 CreateInstance: HRESULT CreateInstance( IUnknown* pUnkOuter,
 *      DWORD dwClsContext, REFIID riid, void** ppvObject);
 *   ms886909 DisplayUI: HRESULT DisplayUI( HWND hwndParent, const WCHAR*
 *      pszTitle, const WCHAR pszTypeOfUI, void* pvExtraData, ULONG
 *      cbExtraData, IUnknown* punkObject);
 *   ms886916 GetCategory: HRESULT GetCategory( ISpObjectTokenCategory**
 *      ppTokenCategory);
 *   ms886917 GetId: HRESULT GetId( WCHAR** ppszCoMemTokenId);
 *   ms886918 GetStorageFileName: HRESULT GetStorageFileName( REFCLSID
 *      clsidCaller, const WCHAR* pszValueName, const WCHAR*
 *      pszFileNameSpecifier, ULONG nFolder, WCHAR** ppszFilePath);
 *   ms886921 IsUISupported: HRESULT IsUISupported( const WCHAR* pszTypeOfUI,
 *      void* pvExtraData, ULONG cbExtraData, IUnknown* punkObject, BOOL*
 *      pfSupported);
 *   ms886922 MatchesAttributes: HRESULT MatchesAttributes( const WCHAR*
 *      pszAttributes, BOOL* pfMatches);
 *   ms886923 Remove: HRESULT Remove( const CLSID* pclsidCaller);
 *   ms886924 RemoveStorageFileName: HRESULT RemoveStorageFileName( REFCLSID
 *      clsidCaller, const WCHAR* pszKeyName, BOOL fDeleteFile);
 *   ms886925 SetId: HRESULT SetId( const WCHAR* pszCategoryId, const WCHAR*
 *      pszTokenId, BOOL fCreateIfNotExist);
 */

/* ISpObjectTokenCategory: documented methods (6 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms886902 EnumTokens: HRESULT EnumTokens( const WCHAR* pszReqAttribs,
 *      const WCHAR* pszOptAttribs, IEnumSpObjectTokens** ppEnum);
 *   ms886903 GetDataKey: HRESULT GetDataKey( SPDATAKEYLOCATION spdkl,
 *      ISpDataKey** ppDataKey);
 *   ms886904 GetDefaultTokenId: HRESULT GetDefaultTokenId( const WCHAR**
 *      ppszCoMemTokenId);
 *   ms886905 GetId: HRESULT GetId( WCHAR** ppszCoMemCategoryId);
 *   ms886906 SetDefaultTokenId: HRESULT SetDefaultTokenId( const WCHAR*
 *      pszTokenId);
 *   ms886907 SetId: HRESULT SetId( const WCHAR* pszCategoryId, BOOL
 *      fCreateIfNotExist);
 */

/* ISpObjectTokenEnumBuilder: documented methods (5 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms886911 AddTokens: HRESULT AddTokens(ULONG cTokens,ISpObjectToken**
 *      pToken);
 *   ms886912 AddTokensFromDataKey: HRESULT AddTokensFromDataKey(ISpDataKey*
 *      pDataKey,const WCHAR* pszSubKey,const WCHAR* pszCategoryId);
 *   ms886913 AddTokensFromTokenEnum: HRESULT
 *      AddTokensFromTokenEnum(IEnumSpObjectTokens* pTokenEnum);
 *   ms886914 SetAttribs: HRESULT SetAttribs(const WCHAR* pszReqAttribs,const
 *      WCHAR* pszOptAttribs);
 *   ms886915 Sort: HRESULT Sort(const WCHAR* pszTokenIdToListFirst);
 */

/* ISpObjectTokenInit: documented methods (1 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms886920 InitFromDataKey: HRESULT InitFromDataKey( const WCHAR*
 *      pszCategoryId, const WCHAR* pszTokenId, ISpDataKey* pDataKey);
 */

/* ISpObjectWithToken: documented methods (2 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms886927 GetObjectToken: HRESULT GetObjectToken( ISpObjectToken**
 *      ppToken);
 *   ms886928 SetObjectToken: HRESULT SetObjectToken( ISpObjectToken* pToken);
 */

/* ISpPhoneConverter: documented methods (2 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   aa517023 IdToPhone: HRESULT IdToPhone(const SPPHONEID* pId,WCHAR*
 *      pszPhone);
 *   aa517156 PhoneToId: HRESULT PhoneToId(const WCHAR* pszPhone,SPPHONEID*
 *      pId);
 */

/* ISpPhrase: documented methods (4 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   aa517183 Discard: HRESULT Discard(DWORD dwValueTypes);
 *   aa517184 GetPhrase: HRESULT GetPhrase(SPPHRASE** ppCoMemPhrase);
 *   aa517185 GetSerializedPhrase: HRESULT
 *      GetSerializedPhrase(SPSERIALIZEDPHRASE** ppCoMemPhrase);
 *   aa517187 GetText: HRESULT GetText(ULONG ulStart,ULONG ulCount,BOOL
 *      fUseTextReplacements,WCHAR** ppszCoMemText,BYTE* pbDisplayAttributes);
 */

/* ISpPhraseAlt: documented methods (2 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   aa517165 Commit: HRESULT Commit(void);
 *   aa517166 GetAltInfo: HRESULT GetAltInfo(ISpPhrase** ppParent,ULONG*
 *      pulStartElementInParent,ULONG* pcElementsInParent,ULONG*
 *      pcElementsInAlt);
 */

/* ISpPhraseBuilder: documented methods (6 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   aa517171 AddElements: HRESULT AddElements( ULONG cElements, const
 *      SPPHRASEELEMENT* pElement);
 *   aa517173 AddProperties: HRESULT AddProperties( const
 *      SPPHRASEPROPERTYHANDLE hParent, const SPPHRASEPROPERTY* pProperty,
 *      SPPHRASEPROPERTYHANDLE* phNewProperty);
 *   aa517176 AddReplacements: HRESULT AddReplacements( ULONG cReplacements,
 *      const SPPHRASEREPLACEMENT* pReplacements);
 *   aa517178 AddRules: HRESULT AddRules( const SPPHRASERULEHANDLE hParent,
 *      const SPPHRASERULE* pRule, SPPHRASERULEHANDLE* phNewRule);
 *   aa517179 InitFromPhrase: HRESULT InitFromPhrase( const SPPHRASE*
 *      pSrcPhrase);
 *   aa517181 InitFromSerializedPhrase: HRESULT InitFromSerializedPhrase(
 *      const SPSERIALIZEDPHRASE* pPhrase);
 */

/* ISpRecoContext: documented methods (18 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   aa517190 Bookmark: HRESULT Bookmark(SPBOOKMARKOPTIONS Options,ULONGLONG
 *      ullStreamPosition,LPARAM lParamEvent);
 *   aa517191 CreateGrammar: HRESULT CreateGrammar(ULONGLONG
 *      ullGrammarId,ISpRecoGrammar** ppGrammar);
 *   aa517192 DeserializeResult: HRESULT DeserializeResult(const
 *      SPSERIALIZEDRESULT* pSerializedResult,ISpRecoResult** ppResult);
 *   aa517193 GetAudioOptions: HRESULT GetAudioOptions(SPAUDIOOPTIONS*
 *      Options,GUID* pAudioFormatId,WAVEFORMATEX** ppCoMemWFE);
 *   aa517195 GetContextState: HRESULT GetContextState(SPCONTEXTSTATE*
 *      peContextState);
 *   aa517196 GetMaxAlternates: HRESULT GetMaxAlternates(ULONG*
 *      pcMaxAlternates);
 *   aa517199 GetRecognizer: HRESULT GetRecognizer(ISpRecognizer**
 *      ppRecognizer);
 *   aa517200 GetStatus: HRESULT GetStatus(SPRECOCONTEXTSTATUS* pStatus);
 *   aa517201 GetVoice: HRESULT GetVoice(ISpVoice** ppVoice);
 *   aa517202 GetVoicePurgeEvent: HRESULT GetVoicePurgeEvent(ULONGLONG*
 *      pullEventInterest);
 *   aa517203 Pause: HRESULT Pause(DWORD dwFlags);
 *   aa517205 Resume: HRESULT Resume(DWORD dwReserved);
 *   aa517206 SetAdaptationData: HRESULT SetAdaptationData(const WCHAR*
 *      pAdaptationData,const ULONG cch);
 *   aa517209 SetAudioOptions: HRESULT SetAudioOptions(SPAUDIOOPTIONS
 *      Options,const GUID* pAudioFormatId,const WAVEFORMATEX* pWaveFormatEx);
 *   aa517211 SetContextState: HRESULT SetContextState(SPCONTEXTSTATE
 *      eContextState);
 *   aa517212 SetMaxAlternates: HRESULT SetMaxAlternates(ULONG cAlternates);
 *   aa517214 SetVoice: HRESULT SetVoice(ISpVoice* pVoice,BOOL
 *      fAllowFormatChanges);
 *   aa517215 SetVoicePurgeEvent: HRESULT SetVoicePurgeEvent(ULONGLONG
 *      ullEventInterest);
 */

/* ISpRecoGrammar: documented methods (17 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   aa517252 GetGrammarId: HRESULT GetGrammarId(ULONGLONG* pullGrammarId);
 *   aa517255 GetGrammarState: HRESULT GetGrammarState(SPGRAMMARSTATE*
 *      peGrammarState);
 *   aa517257 GetRecoContext: HRESULT GetRecoContext(ISpRecoContext**
 *      ppRecoCtxt);
 *   aa517260 IsPronounceable: HRESULT IsPronounceable(const WCHAR*
 *      pszWord,SPWORDPRONOUNCEABLE* pfPronounceable);
 *   aa517261 LoadCmdFromFile: HRESULT LoadCmdFromFile(const WCHAR*
 *      pszFileName,SPLOADOPTIONS Options);
 *   aa517263 LoadCmdFromMemory: HRESULT LoadCmdFromMemory(const
 *      SPBINARYGRAMMAR* pBinaryData,SPLOADOPTIONS Options);
 *   aa517265 LoadCmdFromProprietaryGrammar: HRESULT
 *      LoadCmdFromProprietaryGrammar(REFGUID rguidParam,const WCHAR*
 *      pszStringParam,const void* pvDataParam,ULONG cbDataSize,SPLOADOPTIONS
 *      Options);
 *   aa517267 LoadCmdFromResource: HRESULT LoadCmdFromResource(HMODULE
 *      hModule,const WCHAR* pszResourceName,const WCHAR*
 *      pszResourceType,WORD wLanguage,SPLOADOPTIONS Options);
 *   aa517269 LoadDictation: HRESULT LoadDictation(const WCHAR*
 *      pszTopicName,SPLOADOPTIONS Options);
 *   aa517271 SaveCmd: HRESULT SaveCmd(IStream* pSaveStream,WCHAR**
 *      ppCoMemErrorText);
 *   aa517273 SetDictationState: HRESULT SetDictationState(SPRULESTATE
 *      NewState);
 *   aa517276 SetGrammarState: HRESULT SetGrammarState(SPGRAMMARSTATE
 *      eGrammarState);
 *   aa517277 SetRuleIdState: HRESULT SetRuleIdState(ULONG
 *      ulRuleId,SPRULESTATE NewState);
 *   aa517279 SetRuleState: HRESULT SetRuleState(const WCHAR* pszName,void*
 *      pReserved,SPRULESTATE NewState);
 *   aa517281 SetTextSelection: HRESULT SetTextSelection(const
 *      SPTEXTSELECTIONINFO* pInfo);
 *   aa517284 SetWordSequenceData: HRESULT SetWordSequenceData(const WCHAR*
 *      pText,ULONG cchText,const SPTEXTSELECTIONINFO* pInfo);
 *   aa517286 UnloadDictation: HRESULT UnloadDictation(void);
 */

/* ISpRecoResult: documented methods (7 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   aa517290 GetAlternates: HRESULT GetAlternates(ULONG ulStartElement,ULONG
 *      cElements,ULONG ulRequestCount,ISpPhraseAlt** ppPhrases,ULONG*
 *      pcPhrasesReturned);
 *   aa517291 GetAudio: HRESULT GetAudio(ULONG ulStartElement,ULONG
 *      cElements,ISpStreamFormat** ppStream);
 *   aa517293 GetRecoContext: HRESULT GetRecoContext(ISpRecoContext**
 *      ppRecoContext);
 *   aa517294 GetResultTimes: HRESULT GetResultTimes(SPRECORESULTTIMES*
 *      pTimes);
 *   aa517296 ScaleAudio: HRESULT ScaleAudio(const GUID* pAudioFormatId,const
 *      WAVEFORMATEX* pWaveFormatEx);
 *   aa517299 Serialize: HRESULT Serialize(SPSERIALIZEDRESULT**
 *      ppCoMemSerializedResult);
 *   aa517301 SpeakAudio: HRESULT SpeakAudio(ULONG ulStartElement,ULONG
 *      cElements,DWORD dwFlags, ULONG* pulStreamNumber);
 */

/* ISpRecognizer: documented methods (16 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   aa517219 CreateRecoContext: HRESULT CreateRecoContext(ISpRecoContext**
 *      ppNewContext);
 *   aa517221 DisplayUI: HRESULT DisplayUI(HWND hwndParent,const WCHAR*
 *      pszTitle,const WCHAR* pszTypeOfUI,void* pvExtraData,ULONG
 *      cbExtraData);
 *   aa517224 EmulateRecognition: HRESULT EmulateRecognition(ISpPhrase*
 *      pPhrase);
 *   aa517226 GetFormat: HRESULT GetFormat(SPSTREAMFORMATTYPE
 *      WaveFormatType,GUID* pFormatId,WAVEFORMATEX** ppCoMemWFEX);
 *   aa517228 GetInputObjectToken: HRESULT
 *      GetInputObjectToken(ISpObjectToken** ppToken);
 *   aa517230 GetInputStream: HRESULT GetInputStream(ISpStreamFormat**
 *      ppStream);
 *   aa517233 GetRecoProfile: HRESULT GetRecoProfile(ISpObjectToken**
 *      ppToken);
 *   aa517234 GetRecoState: HRESULT GetRecoState(SPRECOSTATE* pState);
 *   aa517231 GetRecognizer: HRESULT GetRecognizer(ISpObjectToken**
 *      ppEngineToken);
 *   aa517238 GetStatus: HRESULT GetStatus(SPRECOGNIZERSTATUS* pStatus);
 *   aa517240 IsSharedInstance: HRESULT IsSharedInstance(void);
 *   aa517241 IsUISupported: HRESULT IsUISupported(const WCHAR*
 *      pszTypeOfUI,void* pvExtraData,ULONG cbExtraData,BOOL* pfSupported);
 *   aa517243 SetInput: HRESULT SetInput(IUnknown* pUnkInput,BOOL
 *      fAllowFormatChanges);
 *   aa517247 SetRecoProfile: HRESULT SetRecoProfile(ISpObjectToken* pToken);
 *   aa517248 SetRecoState: HRESULT SetRecoState(SPRECOSTATE NewState);
 *   aa517245 SetRecognizer: HRESULT SetRecognizer(ISpObjectToken*
 *      pEngineToken);
 */

/* ISpRegDataKey: documented methods (1 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   aa517304 SetKey: HRESULT SetKey( HKEY hkey, BOOL fReadOnly);
 */

/* ISpResourceManager: documented methods (2 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   aa517308 GetObject: HRESULT GetObject( REFGUID guidServiceId, REFCLSID
 *      ObjectCLSID, REFIID ObjectIID, BOOL fReleaseWhenNoRefs, void**
 *      ppObject);
 *   aa517310 SetObject: HRESULT SetObject( REFGUID guidServiceId, IUnknown*
 *      pUnkObject);
 */

/* ISpSRAlternates: documented methods (2 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   aa517314 Commit: HRESULT Commit( SPPHRASEALTREQUEST* pAltRequest,
 *      SPPHRASEALT* pAlt, void** ppvResultExtra, ULONG* pcbResultExtra);
 *   aa517315 GetAlternates: HRESULT GetAlternates( SPPHRASEALTREQUEST*
 *      pAltRequest, SPPHRASEALT** ppAlts, ULONG* pcAlts);
 */

/* ISpSREngine: documented methods (29 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   aa517319 GetInputAudioFormat: HRESULT GetInputAudioFormat(const GUID*
 *      pguidSourceFormatId,const WAVEFORMATEX* pSourceWaveFormatEx,GUID*
 *      pguidDesiredFormatId,WAVEFORMATEX** ppCoMemDesiredWaveFormatEx,);
 *   aa517320 GetPropertyNum: HRESULT GetPropertyNum( SPPROPSRC eSrc, void*
 *      pvSrcObj, const WCHAR* pName, LONG* lValue);
 *   aa517322 GetPropertyString: HRESULT GetPropertyString( SPPROPSRC eSrc,
 *      void* pvSrcObj, const WCHAR* pName, WCHAR** ppCoMemValue);
 *   aa517323 IsPronounceable: HRESULT IsPronounceable( void* pvDrvGrammar,
 *      const WCHAR* pszWord, SPWORDPRONOUNCEABLE* pfPronounceable);
 *   aa517324 LoadProprietaryGrammar: HRESULT LoadProprietaryGrammar( void*
 *      pvEngineGrammar, REFGUID rguidParam, const WCHAR* pszStringParam,
 *      const void* pvDataParam, ULONG ulDataSize, SPLOADOPTIONS Options);
 *   aa517325 LoadSLM: HRESULT LoadSLM( void* pvEngineGrammar, const WCHAR*
 *      pszTopicName);
 *   aa517326 OnCreateGrammar: HRESULT OnCreateGrammar( void*
 *      pvEngineRecoContext, SPGRAMMARHANDLE hSAPIGrammar, void**
 *      ppvEngineGrammar);
 *   aa517327 OnCreateRecoContext: HRESULT OnCreateRecoContext(
 *      SPRECOCONTEXTHANDLE hSAPIRecoContext, void** ppvEngineContext);
 *   aa517328 OnDeleteGrammar: HRESULT OnDeleteGrammar( void*
 *      pvEngineGrammar);
 *   aa517329 OnDeleteRecoContext: HRESULT OnDeleteRecoContext( void*
 *      pvEngineContext);
 *   aa517330 PrivateCall: HRESULT PrivateCall( void* pvEngineContext, PVOID*
 *      pCallFrame, ULONG ulCallFrameSize);
 *   ms887490 PrivateCallEx: HRESULT PrivateCallEx( void* pvEngineContext,
 *      const void* pInCallFrame, ULONG ulInCallFrameSize, void**
 *      ppvCoMemResponse, ULONG* pulResponseSize);
 *   ms887546 RecognizeStream: HRESULT RecognizeStream( REFGUID rguidFmtId,
 *      const WAVEFORMATEX* pWaveFormatEx, HANDLE hRequestSync, HANDLE
 *      hDataAvailable, HANDLE hExit, BOOL fNewAudioStream, BOOL
 *      fRealTimeAudio, ISpObjectToken* pAudioObjectToken);
 *   ms887553 RuleNotify: HRESULT RuleNotify( SPCFGNOTIFY Action, ULONG
 *      cRules, const SPRULEENTRY* pRules);
 *   ms887556 SetAdaptationData: HRESULT SetAdaptationData( void*
 *      pvEngineContext, const WCHAR* pAdaptationData, const ULONG cch);
 *   ms887564 SetContextState: HRESULT SetContextState( void*
 *      pvEngineContext, SPCONTEXTSTATE eContextState);
 *   ms887567 SetGrammarState: HRESULT SetGrammarState( void*
 *      pvEngineGrammar, SPGRAMMARSTATE* eGrammarState);
 *   ms887573 SetPropertyNum: HRESULT SetPropertyNum( SPPROPSRC eSrc, void*
 *      pvSrcObj, const WCHAR* pName, LONG lValue);
 *   ms887576 SetPropertyString: HRESULT SetPropertyString( SPPROPSRC eSrc,
 *      void* pvSrcObj, const WCHAR* pName, const WCHAR* pValue);
 *   ms887580 SetProprietaryRuleIdState: HRESULT SetProprietaryRuleIdState(
 *      void* pvEngineGrammar, DWORD dwRuleId, SPRULESTATE NewState);
 *   ms887584 SetProprietaryRuleState: HRESULT SetProprietaryRuleState( void*
 *      pvEngineGrammar, const WCHAR* pszName, const WCHAR* pszValue,
 *      SPRULESTATE NewState, ULONG* pcRulesChanged);
 *   ms887589 SetRecoProfile: HRESULT SetRecoProfile( ISpObjectToken*
 *      pProfile);
 *   ms887603 SetSLMState: HRESULT SetSLMState( void* pvEngineGrammar,
 *      SPRULESTATE NewState);
 *   ms887595 SetSite: HRESULT SetSite( ISpSREngineSite* pSite);
 *   ms887608 SetTextSelection: HRESULT SetTextSelection( void*
 *      pvEngineGrammar, const SPTEXTSELECTIONINFO* pInfo);
 *   ms887616 SetWordSequenceData: HRESULT SetWordSequenceData( void*
 *      pvEngineGrammar, const WCHAR* pText, ULONG cchText, const
 *      SPTEXTSELECTIONINFO* pInfo);
 *   ms889616 UnloadProprietaryGrammar: HRESULT UnloadProprietaryGrammar(
 *      void* pvEngineGrammar);
 *   ms889623 UnloadSLM: HRESULT UnloadSLM( void* pvEngineGrammar);
 *   ms889630 WordNotify: HRESULT WordNotify( SPCFGNOTIFY Action, ULONG
 *      cWords, const SPWORDENTRY* pWords);
 */

/* ISpSREngineSite: documented methods (18 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms887828 AddEvent: HRESULT AddEvent( const SPEVENT* pEvent,
 *      SPRECOCONTEXTHANDLE hContext);
 *   ms887927 DataAvailable: HRESULT DataAvailable( ULONG* pcb);
 *   ms887940 GetContextMaxAlternates: HRESULT GetContextMaxAlternates(
 *      SPRECOCONTEXTHANDLE hContext, ULONG* pulNumAlts);
 *   ms887951 GetMaxAlternates: HRESULT GetMaxAlternates( SPRULEHANDLE hRule,
 *      ULONG* pulNumAlts);
 *   ms887966 GetResource: HRESULT GetResource( SPRULEHANDLE hRule, WCHAR*
 *      pszResourceName, WCHAR** ppCoMemResource);
 *   ms887975 GetRuleInfo: HRESULT GetRuleInfo( SPRULEENTRY* pRuleEntry,
 *      SPRULEINFOOPT Options);
 *   ms887988 GetStateInfo: HRESULT GetStateInfo( SPSTATEHANDLE hState,
 *      SPSTATEINFO* pStateInfo);
 *   ms887998 GetTransitionProperty: HRESULT GetTransitionProperty(
 *      SPTRANSITIONID ID, SPTRANSITIONPROPERTY** ppCoMemProperty);
 *   ms889010 GetWordInfo: HRESULT GetWordInfo( SPWORDENTRY* pWordEntry,
 *      SPWORDINFOOPT Options);
 *   ms889018 IsAlternate: HRESULT IsAlternate( SPRULEHANDLE hPriRule,
 *      SPRULEHANDLE hAltRule);
 *   ms889025 ParseFromTransitions: HRESULT ParseFromTransitions( const
 *      SPPARSEINFO* pParseInfo, ISpPhraseBuilder** ppPhrase);
 *   ms889032 Read: HRESULT Read( void* pv, ULONG cb, ULONG* pcbRead);
 *   ms889126 Recognition: HRESULT Recognition( SPRECORESULTINFO*
 *      pResultInfo);
 *   ms889208 SetBufferNotifySize: HRESULT SetBufferNotifySize( ULONG cbSize);
 *   ms889303 SetRuleClientContext: HRESULT SetRuleClientContext(
 *      SPRULEHANDLE hRule, void* pvClientContext);
 *   ms889491 SetWordClientContext: HRESULT SetWordClientContext(
 *      SPWORDHANDLE hWord, void* pvClientContext);
 *   ms889601 Synchronize: HRESULT Synchronize( ULONGLONG ullStreamPos);
 *   ms889609 UpdateRecoPos: HRESULT UpdateRecoPos( ULONGLONG ullStreamPos);
 */

/* ISpStream: documented methods (4 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms889643 BindToFile: HRESULT BindToFile(const WCHAR*
 *      pszFileName,SPFILEMODE eMode,const GUID* pguidFormatId,const
 *      WAVEFORMATEX* pWaveFormatEx,ULONGLONG ullEventInterest);
 *   ms889649 Close: HRESULT Close(void);
 *   ms890204 GetBaseStream: HRESULT GetBaseStream(IStream** ppStream);
 *   ms890231 SetBaseStream: HRESULT SetBaseStream(IStream* pStream,REFGUID
 *      rguidFormat,const WAVEFORMATEX* pWaveFormatEx);
 */

/* ISpStreamFormat: documented methods (1 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms890094 GetFormat: HRESULT GetFormat(GUID* pguidFormatId,WAVEFORMATEX**
 *      ppCoMemWaveFormatEx);
 */

/* ISpStreamFormatConverter: documented methods (6 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms889680 GetBaseStream: HRESULT GetBaseStream( ISpStreamFormat**
 *      ppStream);
 *   ms889690 ResetSeekPosition: HRESULT ResetSeekPosition(void);
 *   ms889698 ScaleBaseToConvertedOffset: HRESULT
 *      ScaleBaseToConvertedOffset(ULONGLONG ullOffsetBaseStream,ULONGLONG*
 *      pullOffsetConvertedStream);
 *   ms889785 ScaleConvertedToBaseOffset: HRESULT
 *      ScaleConvertedToBaseOffset(ULONGLONG
 *      ullOffsetConvertedStream,ULONGLONG* pullOffsetBaseStream);
 *   ms889876 SetBaseStream: HRESULT SetBaseStream(ISpStreamFormat*
 *      pStream,BOOL fSetFormatToBaseStreamFormat,BOOL fWriteToBaseStream);
 *   ms889967 SetFormat: HRESULT SetFormat(REFGUID
 *      rguidFormatIdOfConvertedStream,const WAVEFORMATEX*
 *      pWaveFormatExOfConvertedStream);
 */

/* ISpTTSEngine: documented methods (2 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms890274 GetOutputFormat: HRESULT GetOutputFormat(const GUID*
 *      pTargetFmtId,const WAVEFORMATEX* pTargetWaveFormatEx,GUID*
 *      pOutputFormatId,WAVEFORMATEX** ppCoMemOutputWaveFormatEx);
 *   ms890282 Speak: HRESULT Speak(DWORD dwSpeakFlags,REFGUID
 *      rguidFormatId,const WaveFormatEx* pWaveFormatEx,const SPVTEXTFRAG*
 *      pTextFragList,ISpTTSEngineSite* pOutputSite);
 */

/* ISpTTSEngineSite: documented methods (6 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms890276 CompleteSkip: HRESULT CompleteSkip(long ulNumSkipped);
 *   ms890277 GetActions: DWORD GetActions(void);
 *   ms890278 GetRate: HRESULT GetRate(long* pRateAdjust);
 *   ms890279 GetSkipInfo: HRESULT GetSkipInfo(SPVSKIPTYPE* peType,long*
 *      plNumItems);
 *   ms890280 GetVolume: HRESULT GetVolume(USHORT* pusVolume);
 *   ms890281 Write: HRESULT Write(const void* pBuff,ULONG cb,ULONG*
 *      pcbWritten);
 */

/* ISpTask: documented methods (1 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms890241 Execute: virtual HRESULT STDMETHODCALLTYPE Execute( void*
 *      pvTaskData, volatile const BOOL* pfContinueProcessing);
 */

/* ISpTaskManager: documented methods (7 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms890243 CreateReoccurringTask: HRESULT CreateReoccurringTask(ISpTask*
 *      pTask,void* pvTaskData,HANDLE hCompEvent,ISpNotifySink** ppTaskCtrl);
 *   ms890244 CreateThreadControl: HRESULT CreateThreadControl(ISpThreadTask*
 *      pTask,void* pvTaskData,long nPriority,ISpThreadControl**
 *      ppThreadCtrl);
 *   ms890245 GetThreadPoolInfo: HRESULT GetThreadPoolInfo(SPTMTHREADINFO*
 *      pPoolInfo);
 *   ms890246 QueueTask: HRESULT QueueTask(ISpTask pTask, void* pvTaskData,
 *      HANDLE hCompEvent, DWORD** pdwGroupId,DWORD** pTaskID);
 *   ms890248 SetThreadPoolInfo: HRESULT SetThreadPoolInfo(const
 *      SPTMTHREADINFO* pPoolInfo);
 *   ms890249 TerminateTask: HRESULT TerminateTask(DWORD dwTaskId,ULONG
 *      ulWaitPeriod);
 *   ms890250 TerminateTaskGroup: HRESULT TerminateTaskGroup(DWORD
 *      dwGroupId,ULONG ulWaitPeriod);
 */

/* ISpThreadControl: documented methods (9 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms890252 ExitThreadEvent: HANDLE ExitThreadEvent(void);
 *   ms890255 NotifyEvent: HANDLE NotifyEvent(void);
 *   ms890256 StartThread: HRESULT StartThread(DWORD dwFlags,HWND* phwnd);
 *   ms890257 TerminateThread: HRESULT TerminateThread(void);
 *   ms890258 ThreadCompleteEvent: HANDLE ThreadCompleteEvent(void);
 *   ms890259 ThreadHandle: HANDLE ThreadHandle(void);
 *   ms890260 ThreadId: DWORD ThreadId(void);
 *   ms890261 WaitForThreadDone: HRESULT WaitForThreadDone(BOOL
 *      fForceStop,HRESULT* phrThreadResult,ULONG msTimeOut);
 *   ms890262 WindowHandle: HWND WindowHandle(void);
 */

/* ISpThreadTask: documented methods (3 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms890264 InitThread: HRESULT InitThread(ISpThreadControl* pThreadCtrl,
 *      PVOID pvTaskData);
 *   ms890265 ThreadProc: virtual HRESULT STDMETHODCALLTYPE ThreadProc(void*
 *      pvTaskData,HANDLE hExitThreadEvent,HANDLE hNotifyEvent,HWND
 *      hwndWorker,volatile const BOOL* pfContinueProcessing) = 0;
 *   ms890266 WindowMessage: LRESULT WindowMessage(HWND hwnd, UINT uMsg,
 *      WPARAM wParam, LPARAM lParam);
 */

/* ISpTokenUI: documented methods (2 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms890268 DisplayUI: HRESULT DisplayUI(HWND hwndParent,const WCHAR*
 *      pszTitle,const WCHAR* pszTypeOfUI,void* pvExtraData,ULONG
 *      cbExtraData,ISpObjectToken* pToken,IUnknown* punkObject);
 *   ms890269 IsUISupported: HRESULT IsUISupported(const WCHAR*
 *      pszTypeOfUI,void* pvExtraData,ULONG cbExtraData,IUnknown*
 *      punkObject,BOOL* pfSupported);
 */

/* ISpTranscript: documented methods (2 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms890271 AppendTranscript: HRESULT AppendTranscript(const WCHAR*
 *      pszTranscript);
 *   ms890272 GetTranscript: HRESULT GetTranscript(WCHAR** ppszTranscript);
 */

/* ISpVoice: documented methods (25 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms890284 DisplayUI: HRESULT DisplayUI( HWND hwndParent, const WCHAR*
 *      pszTitle, const WCHAR* pszTypeOfUI, void* pvExtraData, ULONG
 *      cbExtraData);
 *   ms890285 GetAlertBoundary: HRESULT GetAlertBoundary( SPEVENTENUM*
 *      peBoundary);
 *   ms890286 GetOutputObjectToken: HRESULT GetOutputObjectToken(
 *      ISpObjectToken** ppObjectToken);
 *   ms890288 GetOutputStream: HRESULT GetOutputStream( ISpStreamFormat**
 *      ppStream);
 *   ms890289 GetPriority: HRESULT GetPriority( SPVPRIORITY* pePriority);
 *   ms890290 GetRate: HRESULT GetRate( long* pRateAdjust);
 *   ms890291 GetStatus: HRESULT GetStatus( SPVOICESTATUS* pStatus, WCHAR**
 *      ppszLastBookmark);
 *   ms890292 GetSyncSpeakTimeout: HRESULT GetSyncSpeakTimeout( ULONG*
 *      pmsTimeout);
 *   ms890352 GetVoice: HRESULT GetVoice( ISpObjectToken** ppToken);
 *   ms890414 GetVolume: HRESULT GetVolume( USHORT* pusVolume);
 *   ms890423 IsUISupported: HRESULT IsUISupported( const WCHAR* pszTypeOfUI,
 *      void* pvExtraData, ULONG cbExtraData, BOOL* pfSupported);
 *   ms890442 Pause: HRESULT Pause(void);
 *   ms890452 Resume: HRESULT Resume(void);
 *   ms890460 SetAlertBoundary: HRESULT SetAlertBoundary(
 *      SPEVENTENUMeBoundary);
 *   ms890466 SetOutput: HRESULT SetOutput( IUnknown* pUnkOutput, BOOL
 *      fAllowFormatChanges);
 *   ms890472 SetPriority: HRESULT SetPriority( SPVPRIORITY ePriority);
 *   ms890479 SetRate: HRESULT SetRate( long RateAdjust);
 *   ms890487 SetSyncSpeakTimeout: HRESULT SetSyncSpeakTimeout( ULONG
 *      msTimeout);
 *   ms890497 SetVoice: HRESULT SetVoice( ISpObjectToken* pToken);
 *   ms890504 SetVolume: HRESULT SetVolume( USHORT usVolume);
 *   ms890513 Skip: HRESULT Skip( WCHAR* pItemType, long lNumItems, ULONG*
 *      pulNumSkipped);
 *   ms890519 Speak: HRESULT Speak( const WCHAR* pwcs, DWORD dwFlags, ULONG*
 *      pulStreamNumber);
 *   ms890525 SpeakCompleteEvent: HANDLE SpeakCompleteEvent(void);
 *   ms890536 SpeakStream: HRESULT SpeakStream( IStream* pStream, DWORD
 *      dwFlags, ULONG* pulStreamNumber);
 *   ms890540 WaitUntilDone: HRESULT WaitUntilDone( ULONG msTimeout);
 */

/* _ISpPrivateEngineCall: documented methods (2 pages; Windows CE
 * .NET 4.1 and later; Sapi.h/Sapi.idl or Sapiddk.h/Sapiddk.idl;
 * Link Library: Sapilib.lib).  Vtable layouts are not published;
 * signatures recorded verbatim (archive type-space traps and the
 * [restricted]/virtual STDMETHOD print forms preserved).
 *   ms897369 CallEngine: HRESULT CallEngine( VOID* pCallFrame, ULONG
 *      ulCallFrameSize);
 *   ms897370 CallEngineEx: HRESULT CallEngineEx( const void* pInFrame, ULONG
 *      ulInFrameSize, void** ppCoMemOutFrame, ULONG* pulOutFrameSize);
 */
#ifdef __cplusplus
}
#endif

#endif /* AKARI_SAPI_H */