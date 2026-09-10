/* Voipmanager.h -- VoIP Application Interface Layer (VAIL) record
 * surface.
 *
 * Source pages: the VoIP Phone Services book, VAIL reference rows
 * (tools/manifests/vail.manifest, 183 pages).  The VAIL API is a COM
 * interface set documented on IDL pages: the interfaces carry no
 * printable C signatures or vtable orders, so this header records
 * every interface and method name with its page id (Av_upnp.h M76 /
 * Remoteui.h M77c record-only precedent) and defines no types.
 *
 * Homes as printed: "Voipmanager.h, Voipmanager.idl" (IVoIPMgr,
 * IVoIPMgr2, IVoIPCurrentCall, IVoIPCurrentCall2,
 * IVoIPCurrentCallEnumerator, IVoIPUI, IVoIPDirectoryClient); the
 * remaining interfaces print pure-IDL homes and are recorded here
 * with their printed home noted (Voipmediamanager.idl: IVoIPMediaMgr;
 * Voipstore.idl: IVoIPCallLogDB, IVoIPCallLogDBEnum, IVoIPCallRecord,
 * IVoIPCallerInfoDB, IVoIPCallerInfoDBEnum, IVoIPCallerInfoRecord;
 * Voipprov.idl: IVoIPConfigurationDataStore provisioning rows;
 * IVoIPConfigurationDataStore itself is recorded in
 * Voipconfigurationdatastore.h, its C home).
 * See docs/inventory.md M80.
 */

#ifndef AKARI_VOIPMANAGER_H
#define AKARI_VOIPMANAGER_H

#include <Windows.h>
#include "Rtccore.h"   /* RTCSS_* session states (merged struct members) */

/* --- Recorded VAIL interfaces and methods (names + page ids). ---
 * IVoIPCurrentCall (16 methods; Voipmanager.h, Voipmanager.idl.):
 *   RTCParticipant(ms911835), RTCSession(ms911839), StartTime(ms911843),
 *   Status(ms911847), Type(ms911852), Unhold(ms911857), URI(ms911943),
 *   VoIPName(ms911949), Answer(ms931626), Duration(ms931630),
 *   FriendlyName(ms931657), Hangup(ms931662), Hold(ms931667),
 *   Ignore(ms931672), NetworkStatus(ms931679), Redirect(ms931684)
 * IVoIPCurrentCall2 (5 methods; Voipmanager.h, Voipmanager.idl.):
 *   AddParticipantToConference(ms931501), ConferenceHost(ms931602),
 *   ConferenceParticipants(ms931606), IsConferenceHost(ms931612),
 *   IsConferenceParticipant(ms931615)
 * IVoIPCurrentCallEnumerator (3 methods; Voipmanager.h, Voipmanager.idl.):
 *   Next(ms931643), Reset(ms931646), Skip(ms931654)
 * IVoIPMgr (23 methods; Voipmanager.h, Voipmanager.idl.):
 *   ActiveCurrentCall(ms912178), AutoForwardURI(ms912184), Call(ms912189),
 *   CallerInfoDB(ms912195), CallLogDB(ms912201),
 *   CurrentCallEnumerator(ms912207), Initialize(ms912217),
 *   MicrophoneMute(ms912240), MicrophoneVolume(ms912244),
 *   MissedCallTimeout(ms912253), MyServer(ms912258), MyURI(ms912263),
 *   Parameters(ms912269), PlayProgressTone(ms912274), Reregister(ms912279),
 *   RingTone(ms912285), RTCClient(ms912291), SendDTMF(ms912299),
 *   SpeakerMute(ms912302), SpeakerVolume(ms912307), State(ms912311),
 *   StopProgressTone(ms912319), Uninitialize(ms912325)
 * IVoIPMgr2 (2 methods; Voipmanager.h, Voipmanager.idl.):
 *   InitializeEx(ms912146), RegisterWithSIPServer(ms912171)
 * IVoIPUI (2 methods; Voipmanager.h, Voipmanager.idl.):
 *   OnCallEvent(ms912339), OnSystemEvent(ms912343)
 * IVoIPMediaMgr (21 methods; Voipmediamanager.idl.):
 *   ConferenceSessions(aa525641), OnSessionOperationCompleteEvent(aa525642),
 *   AnswerSession(ms911989), CreatePCToPCSession(ms911998),
 *   EvaluateSessionDescription(ms912006), HoldSession(ms912013),
 *   Initialize(ms912020), InitializeRTCClient(ms912027),
 *   MicrophoneMute(ms912036), MicrophoneVolume(ms912043),
 *   OnReinviteEvent(ms912055), OnSessionStateChangeEvent(ms912064),
 *   PlayProgressTone(ms912071), PlaySound(ms912081), SendDTMF(ms912089),
 *   SpeakerMute(ms912098), SpeakerVolume(ms912109),
 *   StopProgressTone(ms912118), StopSound(ms912124), UnholdSession(ms912130),
 *   Uninitialize(ms912137)
 * IVoIPCallLogDB (6 methods; Voipstore.idl.):
 *   Capacity(ms911663), CreateRecord(ms911664), IncomingEnumerator(ms911670),
 *   Init(ms911671), MissedEnumerator(ms911673), OutgoingEnumerator(ms911674)
 * IVoIPCallLogDBEnum (3 methods; Voipstore.idl.):
 *   Next(ms911667), Reset(ms911668), Skip(ms911669)
 * IVoIPCallRecord (9 methods; Voipstore.idl.):
 *   CallType(ms911675), Commit(ms911676), DeleteFromDB(ms911677),
 *   Duration(ms911678), EndTime(ms911679), FriendlyName(ms911680),
 *   StartTime(ms911682), URI(ms911683), VoIPName(ms911684)
 * IVoIPCallerInfoDB (7 methods; Voipstore.idl.):
 *   CreateRecord(ms911532), Enumerator(ms911539),
 *   FriendlyNameEnumerator(ms911634), Init(ms911647),
 *   SpeedDialEnumerator(ms911651), FindCallerInfoBySpeedDialEntry(ms931238),
 *   FindCallerInfoByURI(ms931345)
 * IVoIPCallerInfoDBEnum (3 methods; Voipstore.idl.):
 *   Next(ms911553), Reset(ms911567), Skip(ms931185)
 * IVoIPCallerInfoRecord (9 methods; Voipstore.idl.):
 *   Blocked(ms911652), Commit(ms911654), DeleteFromDB(ms911655),
 *   ForwardingURI(ms911656), FriendlyName(ms911657), RingTone(ms911659),
 *   SpeedDialEntry(ms911660), URI(ms911661), VoIPName(ms911662)
 * IVoIPDirectoryClient (3 methods; Voipprov.idl.):
 *   RegistrationParameters(ms911968), SipPassword(ms911977),
 *   SipServerParameters(ms911983)
 */

/* ------------------------------------------------------------------
 * Book surface: vail (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms912595 SIPServerRegistrationParameters (page print, compiled) */
typedef struct SIPServerRegistrationParameters {
    const WCHAR* wszURI;
    const WCHAR* wszServer;
    const WCHAR* wszAccountName;
    const WCHAR* wszAccountPassword;
    const WCHAR* wszTransport;
    const WCHAR* wszAuthType;
} SIPServerRegistrationParameters;
/* ms912597 VoIPCallEvent (page print, compiled) */
typedef enum VoIPCallEvent {
    e_vceInvalid = 0,
    e_vceStatusChanged,
    e_vceMissed,
    e_vceAutoBlocked,
    e_vceAutoForwarded,
    e_vceDropped,
    e_vceRedirectSucceeded,
    e_vceRedirectFailed
} VoIPCallEvent;
/* ms912598 VoIPCallStatus (page print, compiled) */
typedef enum VoIPCallStatus {
    e_vcsInvalid = 0,
    e_vcsIdle = RTCSS_IDLE,
    e_vcsIncoming = RTCSS_INCOMING,
    e_vcsAnswering = RTCSS_ANSWERING,
    e_vcsInProgress = RTCSS_INPROGRESS,
    e_vcsConnected = RTCSS_CONNECTED,
    e_vcsDisconnected = RTCSS_DISCONNECTED,
    e_vcsHolding = RTCSS_HOLD,
    e_vcsReferring = RTCSS_REFER,
    e_vcsInConference = RTCSS_REFER+1
} VoIPCallStatus;
/* ms912599 VoIPCallType (page print, compiled) */
typedef enum VoIPCallType {
    e_vctInvalid = 0,
    e_vctIncoming,
    e_vctOutgoing,
    e_vctMissed
} VoIPCallType;
/* ms912606 VoIPSystemEvent (page print, compiled) */
typedef enum VoIPSystemEvent {
    e_vseInvalid = 0,
    e_vseTerminated,
    e_vseRegistering,
    e_vseRegistrationSucceeded,
    e_vseRegistrationFailed
} VoIPSystemEvent;
/* ms909306 DirectoryClientRegParams -- HELD (page print; member types unpublished):
 *   typedef struct  { ... } DirectoryClientRegParams; */
/* ms912603 VoIPMgrParameters -- HELD (page print; member types unpublished):
 *   typedef struct  { ... } VoIPMgrParameters; */
/* ms931501 IVoIPCurrentCall2::AddParticipantToConference (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931602 IVoIPCurrentCall2::ConferenceHost (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931606 IVoIPCurrentCall2::ConferenceParticipants (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931612 IVoIPCurrentCall2::IsConferenceHost (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931615 IVoIPCurrentCall2::IsConferenceParticipant (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931626 IVoIPCurrentCall::Answer (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931630 IVoIPCurrentCall::Duration (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931657 IVoIPCurrentCall::FriendlyName (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931662 IVoIPCurrentCall::Hangup (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931667 IVoIPCurrentCall::Hold (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931672 IVoIPCurrentCall::Ignore (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931679 IVoIPCurrentCall::NetworkStatus (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931684 IVoIPCurrentCall::Redirect (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms911835 IVoIPCurrentCall::RTCParticipant (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms911839 IVoIPCurrentCall::RTCSession (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms911843 IVoIPCurrentCall::StartTime (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms911847 IVoIPCurrentCall::Status (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms911852 IVoIPCurrentCall::Type (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms911857 IVoIPCurrentCall::Unhold (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms911943 IVoIPCurrentCall::URI (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms911949 IVoIPCurrentCall::VoIPName (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931643 IVoIPCurrentCallEnumerator::Next (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931646 IVoIPCurrentCallEnumerator::Reset (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931654 IVoIPCurrentCallEnumerator::Skip (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912146 IVoIPMgr2::InitializeEx (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912171 IVoIPMgr2::RegisterWithSIPServer (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912178 IVoIPMgr::ActiveCurrentCall (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912184 IVoIPMgr::AutoForwardURI (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912189 IVoIPMgr::Call (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912195 IVoIPMgr::CallerInfoDB (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912201 IVoIPMgr::CallLogDB (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912207 IVoIPMgr::CurrentCallEnumerator (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912217 IVoIPMgr::Initialize (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912240 IVoIPMgr::MicrophoneMute (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912244 IVoIPMgr::MicrophoneVolume (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912253 IVoIPMgr::MissedCallTimeout (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912258 IVoIPMgr::MyServer (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912263 IVoIPMgr::MyURI (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912269 IVoIPMgr::Parameters (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912274 IVoIPMgr::PlayProgressTone (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912279 IVoIPMgr::Reregister (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912285 IVoIPMgr::RingTone (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912291 IVoIPMgr::RTCClient (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912299 IVoIPMgr::SendDTMF (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912302 IVoIPMgr::SpeakerMute (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912307 IVoIPMgr::SpeakerVolume (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912311 IVoIPMgr::State (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912319 IVoIPMgr::StopProgressTone (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912325 IVoIPMgr::Uninitialize (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912339 IVoIPUI::OnCallEvent (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912343 IVoIPUI::OnSystemEvent (Header: Voipmanager.h, Voipmanager.idl.) */
/* ------------------------------------------------------------------
 * Book surface: vail (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms912604 VoIPProgressTone (page print, compiled) */
typedef enum VoIPProgressTone {
    e_vptInvalid = 0,
    e_vptDial,
    e_vptStutter,
    e_vptOffHookWarning,
    e_vptConfirmation,
    e_vptMessageWaiting,
    e_vptRingback,
    e_vptCallWaiting,
    e_vptReorder,
    e_vptCongestion,
    e_vptClientBusy,
    e_vptNetworkBusy
} VoIPProgressTone;
/* aa525608 Configuration Data Store Example XML */
/* aa525613 Creating an Application That Uses VAIL */
/* aa525614 Current Call */
/* aa525621 Database Store and Call Logging */
/* aa525630 Example VAIL Application Structure */
/* aa525636 How the VAIL Creates the Media Manager */
/* aa525640 IP Phone Provisioning */
/* ms911532 IVoIPCallerInfoDB::CreateRecord (Header: Voipstore.idl.) */
/* ms911539 IVoIPCallerInfoDB::Enumerator (Header: Voipstore.idl.) */
/* ms931238 IVoIPCallerInfoDB::FindCallerInfoBySpeedDialEntry (Header: Voipstore.idl.) */
/* ms931345 IVoIPCallerInfoDB::FindCallerInfoByURI (Header: Voipstore.idl.) */
/* ms911634 IVoIPCallerInfoDB::FriendlyNameEnumerator (Header: Voipstore.idl.) */
/* ms911647 IVoIPCallerInfoDB::Init (Header: Voipstore.idl.) */
/* ms911651 IVoIPCallerInfoDB::SpeedDialEnumerator (Header: Voipstore.idl.) */
/* ms911553 IVoIPCallerInfoDBEnum::Next (Header: Voipstore.idl.) */
/* ms911567 IVoIPCallerInfoDBEnum::Reset (Header: Voipstore.idl.) */
/* ms931185 IVoIPCallerInfoDBEnum::Skip (Header: Voipstore.idl.) */
/* ms911652 IVoIPCallerInfoRecord::Blocked (Header: Voipstore.idl.) */
/* ms911654 IVoIPCallerInfoRecord::Commit (Header: Voipstore.idl.) */
/* ms911655 IVoIPCallerInfoRecord::DeleteFromDB (Header: Voipstore.idl.) */
/* ms911656 IVoIPCallerInfoRecord::ForwardingURI (Header: Voipstore.idl.) */
/* ms911657 IVoIPCallerInfoRecord::FriendlyName (Header: Voipstore.idl.) */
/* ms911659 IVoIPCallerInfoRecord::RingTone (Header: Voipstore.idl.) */
/* ms911660 IVoIPCallerInfoRecord::SpeedDialEntry (Header: Voipstore.idl.) */
/* ms911661 IVoIPCallerInfoRecord::URI (Header: Voipstore.idl.) */
/* ms911662 IVoIPCallerInfoRecord::VoIPName (Header: Voipstore.idl.) */
/* ms911663 IVoIPCallLogDB::Capacity (Header: Voipstore.idl.) */
/* ms911664 IVoIPCallLogDB::CreateRecord (Header: Voipstore.idl.) */
/* ms911670 IVoIPCallLogDB::IncomingEnumerator (Header: Voipstore.idl.) */
/* ms911671 IVoIPCallLogDB::Init (Header: Voipstore.idl.) */
/* ms911673 IVoIPCallLogDB::MissedEnumerator (Header: Voipstore.idl.) */
/* ms911674 IVoIPCallLogDB::OutgoingEnumerator (Header: Voipstore.idl.) */
/* ms911667 IVoIPCallLogDBEnum::Next (Header: Voipstore.idl.) */
/* ms911668 IVoIPCallLogDBEnum::Reset (Header: Voipstore.idl.) */
/* ms911669 IVoIPCallLogDBEnum::Skip (Header: Voipstore.idl.) */
/* ms911675 IVoIPCallRecord::CallType (Header: Voipstore.idl.) */
/* ms911676 IVoIPCallRecord::Commit (Header: Voipstore.idl.) */
/* ms911677 IVoIPCallRecord::DeleteFromDB (Header: Voipstore.idl.) */
/* ms911678 IVoIPCallRecord::Duration (Header: Voipstore.idl.) */
/* ms911679 IVoIPCallRecord::EndTime (Header: Voipstore.idl.) */
/* ms911680 IVoIPCallRecord::FriendlyName (Header: Voipstore.idl.) */
/* ms911682 IVoIPCallRecord::StartTime (Header: Voipstore.idl.) */
/* ms911683 IVoIPCallRecord::URI (Header: Voipstore.idl.) */
/* ms911684 IVoIPCallRecord::VoIPName (Header: Voipstore.idl.) */
/* ms911685 IVoIPConfigurationDataStore::Initialize (Header: Voipconfigurationdatastore.idl, Voipconfigurationdatastore.h.) */
/* ms911687 IVoIPConfigurationDataStore::ReadValue (Header: Voipconfigurationdatastore.idl, Voipconfigurationdatastore.h.) */
/* ms911688 IVoIPConfigurationDataStore::Uninitialize (Header: Voipconfigurationdatastore.idl, Voipconfigurationdatastore.h.) */
/* ms911689 IVoIPConfigurationDataStore::UpdateSettingsFromFile (Header: Voipconfigurationdatastore.idl, Voipconfigurationdatastore.h.) */
/* ms911690 IVoIPConfigurationDataStore::UpdateSettingsFromServer (Header: Voipconfigurationdatastore.idl, Voipconfigurationdatastore.h.) */
/* ms911691 IVoIPConfigurationDataStore::UpdateSettingsFromXML (Header: Voipconfigurationdatastore.idl, Voipconfigurationdatastore.h.) */
/* ms911692 IVoIPConfigurationDataStore::WriteValue (Header: Voipconfigurationdatastore.idl, Voipconfigurationdatastore.h.) */
/* ms911968 IVoIPDirectoryClient::RegistrationParameters (Header: Voipprov.idl.) */
/* ms911977 IVoIPDirectoryClient::SipPassword (Header: Voipprov.idl.) */
/* ms911983 IVoIPDirectoryClient::SipServerParameters (Header: Voipprov.idl.) */
/* ms911989 IVoIPMediaMgr::AnswerSession (Header: Voipmediamanager.idl.) */
/* aa525641 IVoIPMediaMgr::ConferenceSessions (Header: Voipmediamanager.idl.) */
/* ms911998 IVoIPMediaMgr::CreatePCToPCSession (Header: Voipmediamanager.idl.) */
/* ms912006 IVoIPMediaMgr::EvaluateSessionDescription (Header: Voipmediamanager.idl.) */
/* ms912013 IVoIPMediaMgr::HoldSession (Header: Voipmediamanager.idl.) */
/* ms912020 IVoIPMediaMgr::Initialize (Header: Voipmediamanager.idl.) */
/* ms912027 IVoIPMediaMgr::InitializeRTCClient (Header: Voipmediamanager.idl.) */
/* ms912036 IVoIPMediaMgr::MicrophoneMute (Header: Voipmediamanager.idl.) */
/* ms912043 IVoIPMediaMgr::MicrophoneVolume (Header: Voipmediamanager.idl.) */
/* ms912055 IVoIPMediaMgr::OnReinviteEvent (Header: Voipmediamanager.idl.) */
/* aa525642 IVoIPMediaMgr::OnSessionOperationCompleteEvent (Header: Voipmediamanager.idl.) */
/* ms912064 IVoIPMediaMgr::OnSessionStateChangeEvent (Header: Voipmediamanager.idl.) */
/* ms912071 IVoIPMediaMgr::PlayProgressTone (Header: Voipmediamanager.idl.) */
/* ms912081 IVoIPMediaMgr::PlaySound (Header: Voipmediamanager.idl.) */
/* ms912089 IVoIPMediaMgr::SendDTMF (Header: Voipmediamanager.idl.) */
/* ms912098 IVoIPMediaMgr::SpeakerMute (Header: Voipmediamanager.idl.) */
/* ms912109 IVoIPMediaMgr::SpeakerVolume (Header: Voipmediamanager.idl.) */
/* ms912118 IVoIPMediaMgr::StopProgressTone (Header: Voipmediamanager.idl.) */
/* ms912124 IVoIPMediaMgr::StopSound (Header: Voipmediamanager.idl.) */
/* ms912130 IVoIPMediaMgr::UnholdSession (Header: Voipmediamanager.idl.) */
/* ms912137 IVoIPMediaMgr::Uninitialize (Header: Voipmediamanager.idl.) */
/* ms912165 IVoIPMgr2 */
/* aa525648 Media Manager Responsibilities */
/* aa525649 Migrating to New Initialization and Provisioning APIs */
/* aa525681 Retrieving Provisioning Information */
/* ms909273 Using Provisioning Information in VAIL */
/* ms931956 VAIL Application Development */
/* ms909283 VAIL Architecture */
/* ms909276 VAIL as a Part of an IP Phone */
/* ms909277 VAIL Call Conferencing */
/* ms909278 VAIL Configuration Data Store Registry Settings */
/* ms909279 VAIL Configuration Registry Settings */
/* ms909298 VAIL Constants */
/* ms909299 VAIL Enumerations */
/* ms931957 VAIL How-to Topics */
/* ms909300 VAIL Interfaces */
/* ms931958 VAIL Migration */
/* ms909280 VAIL Objects and Interfaces */
/* ms931959 VAIL OS Design Development */
/* ms909281 VAIL Plugin Registry Settings */
/* ms909301 VAIL Reference */
/* ms909282 VAIL Registry Settings */
/* ms931960 VAIL Samples */
/* ms909284 VAIL Security */
/* ms909302 VAIL Structures */
/* ms909285 VoIP Manager */
/* ms909286 VoIP Manager Initialization */
/* aa525638 VoIP Manager Setup */
/* ms909239 VoIP Manager Shutdown */
/* ms909287 VoIP Manager SIP Server Registration */
/* ms909288 VoIP Media Manager */
/* ------------------------------------------------------------------
 * Book surface: vail (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* ms909305 DCRP_VALID_: documented name-only (no value published; held) */
/* ms912596 VMS_: documented name-only (no value published; held) */
/* ms931501 IVoIPCurrentCall2::AddParticipantToConference (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931602 IVoIPCurrentCall2::ConferenceHost (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931606 IVoIPCurrentCall2::ConferenceParticipants (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931612 IVoIPCurrentCall2::IsConferenceHost (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931615 IVoIPCurrentCall2::IsConferenceParticipant (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931626 IVoIPCurrentCall::Answer (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931630 IVoIPCurrentCall::Duration (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931657 IVoIPCurrentCall::FriendlyName (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931662 IVoIPCurrentCall::Hangup (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931667 IVoIPCurrentCall::Hold (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931672 IVoIPCurrentCall::Ignore (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931679 IVoIPCurrentCall::NetworkStatus (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931684 IVoIPCurrentCall::Redirect (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms911835 IVoIPCurrentCall::RTCParticipant (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms911839 IVoIPCurrentCall::RTCSession (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms911843 IVoIPCurrentCall::StartTime (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms911847 IVoIPCurrentCall::Status (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms911852 IVoIPCurrentCall::Type (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms911857 IVoIPCurrentCall::Unhold (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms911943 IVoIPCurrentCall::URI (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms911949 IVoIPCurrentCall::VoIPName (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931643 IVoIPCurrentCallEnumerator::Next (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931646 IVoIPCurrentCallEnumerator::Reset (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms931654 IVoIPCurrentCallEnumerator::Skip (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912146 IVoIPMgr2::InitializeEx (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912171 IVoIPMgr2::RegisterWithSIPServer (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912178 IVoIPMgr::ActiveCurrentCall (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912184 IVoIPMgr::AutoForwardURI (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912189 IVoIPMgr::Call (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912195 IVoIPMgr::CallerInfoDB (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912201 IVoIPMgr::CallLogDB (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912207 IVoIPMgr::CurrentCallEnumerator (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912217 IVoIPMgr::Initialize (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912240 IVoIPMgr::MicrophoneMute (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912244 IVoIPMgr::MicrophoneVolume (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912253 IVoIPMgr::MissedCallTimeout (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912258 IVoIPMgr::MyServer (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912263 IVoIPMgr::MyURI (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912269 IVoIPMgr::Parameters (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912274 IVoIPMgr::PlayProgressTone (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912279 IVoIPMgr::Reregister (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912285 IVoIPMgr::RingTone (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912291 IVoIPMgr::RTCClient (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912299 IVoIPMgr::SendDTMF (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912302 IVoIPMgr::SpeakerMute (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912307 IVoIPMgr::SpeakerVolume (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912311 IVoIPMgr::State (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912319 IVoIPMgr::StopProgressTone (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912325 IVoIPMgr::Uninitialize (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912339 IVoIPUI::OnCallEvent (Header: Voipmanager.h, Voipmanager.idl.) */
/* ms912343 IVoIPUI::OnSystemEvent (Header: Voipmanager.h, Voipmanager.idl.) */
/* ------------------------------------------------------------------
 * Book surface: vail (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa525608 Configuration Data Store Example XML */
/* aa525613 Creating an Application That Uses VAIL */
/* aa525614 Current Call */
/* aa525621 Database Store and Call Logging */
/* aa525630 Example VAIL Application Structure */
/* aa525636 How the VAIL Creates the Media Manager */
/* aa525640 IP Phone Provisioning */
/* ms911532 IVoIPCallerInfoDB::CreateRecord (Header: Voipstore.idl.) */
/* ms911539 IVoIPCallerInfoDB::Enumerator (Header: Voipstore.idl.) */
/* ms931238 IVoIPCallerInfoDB::FindCallerInfoBySpeedDialEntry (Header: Voipstore.idl.) */
/* ms931345 IVoIPCallerInfoDB::FindCallerInfoByURI (Header: Voipstore.idl.) */
/* ms911634 IVoIPCallerInfoDB::FriendlyNameEnumerator (Header: Voipstore.idl.) */
/* ms911647 IVoIPCallerInfoDB::Init (Header: Voipstore.idl.) */
/* ms911651 IVoIPCallerInfoDB::SpeedDialEnumerator (Header: Voipstore.idl.) */
/* ms911553 IVoIPCallerInfoDBEnum::Next (Header: Voipstore.idl.) */
/* ms911567 IVoIPCallerInfoDBEnum::Reset (Header: Voipstore.idl.) */
/* ms931185 IVoIPCallerInfoDBEnum::Skip (Header: Voipstore.idl.) */
/* ms911652 IVoIPCallerInfoRecord::Blocked (Header: Voipstore.idl.) */
/* ms911654 IVoIPCallerInfoRecord::Commit (Header: Voipstore.idl.) */
/* ms911655 IVoIPCallerInfoRecord::DeleteFromDB (Header: Voipstore.idl.) */
/* ms911656 IVoIPCallerInfoRecord::ForwardingURI (Header: Voipstore.idl.) */
/* ms911657 IVoIPCallerInfoRecord::FriendlyName (Header: Voipstore.idl.) */
/* ms911659 IVoIPCallerInfoRecord::RingTone (Header: Voipstore.idl.) */
/* ms911660 IVoIPCallerInfoRecord::SpeedDialEntry (Header: Voipstore.idl.) */
/* ms911661 IVoIPCallerInfoRecord::URI (Header: Voipstore.idl.) */
/* ms911662 IVoIPCallerInfoRecord::VoIPName (Header: Voipstore.idl.) */
/* ms911663 IVoIPCallLogDB::Capacity (Header: Voipstore.idl.) */
/* ms911664 IVoIPCallLogDB::CreateRecord (Header: Voipstore.idl.) */
/* ms911670 IVoIPCallLogDB::IncomingEnumerator (Header: Voipstore.idl.) */
/* ms911671 IVoIPCallLogDB::Init (Header: Voipstore.idl.) */
/* ms911673 IVoIPCallLogDB::MissedEnumerator (Header: Voipstore.idl.) */
/* ms911674 IVoIPCallLogDB::OutgoingEnumerator (Header: Voipstore.idl.) */
/* ms911667 IVoIPCallLogDBEnum::Next (Header: Voipstore.idl.) */
/* ms911668 IVoIPCallLogDBEnum::Reset (Header: Voipstore.idl.) */
/* ms911669 IVoIPCallLogDBEnum::Skip (Header: Voipstore.idl.) */
/* ms911675 IVoIPCallRecord::CallType (Header: Voipstore.idl.) */
/* ms911676 IVoIPCallRecord::Commit (Header: Voipstore.idl.) */
/* ms911677 IVoIPCallRecord::DeleteFromDB (Header: Voipstore.idl.) */
/* ms911678 IVoIPCallRecord::Duration (Header: Voipstore.idl.) */
/* ms911679 IVoIPCallRecord::EndTime (Header: Voipstore.idl.) */
/* ms911680 IVoIPCallRecord::FriendlyName (Header: Voipstore.idl.) */
/* ms911682 IVoIPCallRecord::StartTime (Header: Voipstore.idl.) */
/* ms911683 IVoIPCallRecord::URI (Header: Voipstore.idl.) */
/* ms911684 IVoIPCallRecord::VoIPName (Header: Voipstore.idl.) */
/* ms911685 IVoIPConfigurationDataStore::Initialize (Header: Voipconfigurationdatastore.idl, Voipconfigurationdatastore.h.) */
/* ms911687 IVoIPConfigurationDataStore::ReadValue (Header: Voipconfigurationdatastore.idl, Voipconfigurationdatastore.h.) */
/* ms911688 IVoIPConfigurationDataStore::Uninitialize (Header: Voipconfigurationdatastore.idl, Voipconfigurationdatastore.h.) */
/* ms911689 IVoIPConfigurationDataStore::UpdateSettingsFromFile (Header: Voipconfigurationdatastore.idl, Voipconfigurationdatastore.h.) */
/* ms911690 IVoIPConfigurationDataStore::UpdateSettingsFromServer (Header: Voipconfigurationdatastore.idl, Voipconfigurationdatastore.h.) */
/* ms911691 IVoIPConfigurationDataStore::UpdateSettingsFromXML (Header: Voipconfigurationdatastore.idl, Voipconfigurationdatastore.h.) */
/* ms911692 IVoIPConfigurationDataStore::WriteValue (Header: Voipconfigurationdatastore.idl, Voipconfigurationdatastore.h.) */
/* ms911968 IVoIPDirectoryClient::RegistrationParameters (Header: Voipprov.idl.) */
/* ms911977 IVoIPDirectoryClient::SipPassword (Header: Voipprov.idl.) */
/* ms911983 IVoIPDirectoryClient::SipServerParameters (Header: Voipprov.idl.) */
/* ms911989 IVoIPMediaMgr::AnswerSession (Header: Voipmediamanager.idl.) */
/* aa525641 IVoIPMediaMgr::ConferenceSessions (Header: Voipmediamanager.idl.) */
/* ms911998 IVoIPMediaMgr::CreatePCToPCSession (Header: Voipmediamanager.idl.) */
/* ms912006 IVoIPMediaMgr::EvaluateSessionDescription (Header: Voipmediamanager.idl.) */
/* ms912013 IVoIPMediaMgr::HoldSession (Header: Voipmediamanager.idl.) */
/* ms912020 IVoIPMediaMgr::Initialize (Header: Voipmediamanager.idl.) */
/* ms912027 IVoIPMediaMgr::InitializeRTCClient (Header: Voipmediamanager.idl.) */
/* ms912036 IVoIPMediaMgr::MicrophoneMute (Header: Voipmediamanager.idl.) */
/* ms912043 IVoIPMediaMgr::MicrophoneVolume (Header: Voipmediamanager.idl.) */
/* ms912055 IVoIPMediaMgr::OnReinviteEvent (Header: Voipmediamanager.idl.) */
/* aa525642 IVoIPMediaMgr::OnSessionOperationCompleteEvent (Header: Voipmediamanager.idl.) */
/* ms912064 IVoIPMediaMgr::OnSessionStateChangeEvent (Header: Voipmediamanager.idl.) */
/* ms912071 IVoIPMediaMgr::PlayProgressTone (Header: Voipmediamanager.idl.) */
/* ms912081 IVoIPMediaMgr::PlaySound (Header: Voipmediamanager.idl.) */
/* ms912089 IVoIPMediaMgr::SendDTMF (Header: Voipmediamanager.idl.) */
/* ms912098 IVoIPMediaMgr::SpeakerMute (Header: Voipmediamanager.idl.) */
/* ms912109 IVoIPMediaMgr::SpeakerVolume (Header: Voipmediamanager.idl.) */
/* ms912118 IVoIPMediaMgr::StopProgressTone (Header: Voipmediamanager.idl.) */
/* ms912124 IVoIPMediaMgr::StopSound (Header: Voipmediamanager.idl.) */
/* ms912130 IVoIPMediaMgr::UnholdSession (Header: Voipmediamanager.idl.) */
/* ms912137 IVoIPMediaMgr::Uninitialize (Header: Voipmediamanager.idl.) */
/* ms912165 IVoIPMgr2 */
/* aa525648 Media Manager Responsibilities */
/* aa525649 Migrating to New Initialization and Provisioning APIs */
/* aa525681 Retrieving Provisioning Information */
/* ms909273 Using Provisioning Information in VAIL */
/* ms931956 VAIL Application Development */
/* ms909283 VAIL Architecture */
/* ms909276 VAIL as a Part of an IP Phone */
/* ms909277 VAIL Call Conferencing */
/* ms909278 VAIL Configuration Data Store Registry Settings */
/* ms909279 VAIL Configuration Registry Settings */
/* ms909298 VAIL Constants */
/* ms909299 VAIL Enumerations */
/* ms931957 VAIL How-to Topics */
/* ms909300 VAIL Interfaces */
/* ms931958 VAIL Migration */
/* ms909280 VAIL Objects and Interfaces */
/* ms931959 VAIL OS Design Development */
/* ms909281 VAIL Plugin Registry Settings */
/* ms909301 VAIL Reference */
/* ms909282 VAIL Registry Settings */
/* ms931960 VAIL Samples */
/* ms909284 VAIL Security */
/* ms909302 VAIL Structures */
/* ms909285 VoIP Manager */
/* ms909286 VoIP Manager Initialization */
/* aa525638 VoIP Manager Setup */
/* ms909239 VoIP Manager Shutdown */
/* ms909287 VoIP Manager SIP Server Registration */
/* ms909288 VoIP Media Manager */
#endif /* AKARI_VOIPMANAGER_H */


