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

#endif /* AKARI_VOIPMANAGER_H */
