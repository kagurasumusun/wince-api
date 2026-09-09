/*
 * Rtccore.h -- Real-time Communications (RTC) Client API constants,
 * enumerations and COM interface records for Windows CE.
 *
 * Copyright (c) 2026 Akari API contributors
 * SPDX-License-Identifier: MIT
 *
 * Written from scratch.  Every declaration is annotated with the official
 * Microsoft Windows CE documentation page it is taken from (CE-era MSDN
 * pages in the learn.microsoft.com previous-versions archive, (v=msdn.10)
 * IDs; Voice over IP Phone Services > Real-time Communications (RTC)
 * Client API book, 503 leaves harvested under tools/manifests/
 * rtc.manifest, M69).
 *
 * Requirements rows print "Header: Rtccore.h, Rtccore.idl" (interfaces,
 * constants, enumerations) and "Header: Rtcerr.h" (RTC_E_/RTC_S_ return
 * values).  This project carries both under rtccore.h (the desktop RTC
 * spelling) with Rtccore.h/Rtcerr.h case aliases (M69a).
 *
 * The CE RTC is a C++ COM API: no page publishes a vtable layout, so --
 * following the M44 objbase.h interface-record policy -- each interface
 * is carried as an opaque forward declaration plus verbatim
 * method-signature records.  Import surface: none is documentable -- the
 * "Link Library: Uuid.lib" rows sit on interface/method pages (GUID
 * linkage), and the 18 "Link Library: Rtcdll.dll" rows sit on interface
 * overview pages (module-form rows of the implementing DLL, no free
 * functions; the Mlang.dll module-form precedent maps these to no def).
 *
 * OAHWND = LONG_PTR is printed as a constants-table row (ms912349).
 * The RTC_E_/RTC_S_ pages print the HRESULT layout (Sev|C|R|Facility|
 * Code; facilities EE/EF/F0) and every value in hexadecimal; all 174
 * are transcribed below.  The RTC_EVENT print is missing the comma
 * between RTCE_PROFILE and RTCE_USERSEARCH (archive print artifact;
 * repaired, recorded here).
 */

#ifndef AKARI_RTCCORE_H
#define AKARI_RTCCORE_H

#include "Windef.h"
#include "objbase.h"    /* BSTR, VARIANT, VARIANT_BOOL, IDispatch carriers */

#ifdef __cplusplus
extern "C" {
#endif

/* ms912349 "OAHWND": OAHWND = LONG_PTR (printed). */
typedef LONG_PTR OAHWND;

/* ------------------------------------------------------------------ */
/* Constants (RTC Client API Constants book): every value printed.     */
/* ------------------------------------------------------------------ */

/* RTC_E_ (ms931795; Rtccore.h / Rtcerr.h): values printed on the page. */
#define RTC_E_ANOTHER_MEDIA_SESSION_ACTIVE          0x80EE0077L
#define RTC_E_BASIC_AUTH_SET_TLS                    0x80EE003FL
#define RTC_E_CLIENT_ALREADY_INITIALIZED            0x80EE0026L
#define RTC_E_CLIENT_ALREADY_SHUT_DOWN              0x80EE0027L
#define RTC_E_CLIENT_NOT_INITIALIZED                0x80EE0025L
#define RTC_E_DESTINATION_ADDRESS_LOCAL             0x80EE0013L
#define RTC_E_DESTINATION_ADDRESS_MULTICAST         0x80EE0015L
#define RTC_E_DUPLICATE_BUDDY                       0x80EE004AL
#define RTC_E_DUPLICATE_GROUP                       0x80EE0052L
#define RTC_E_DUPLICATE_REALM                       0x80EE0043L
#define RTC_E_DUPLICATE_WATCHER                     0x80EE004BL
#define RTC_E_INSUFFICIENT_SECURITY_LEVEL           0x80EE0047L
#define RTC_E_INVALID_ACL_LIST                      0x80EE0050L
#define RTC_E_INVALID_ADDRESS_LOCAL                 0x80EE0014L
#define RTC_E_INVALID_BUDDY_LIST                    0x80EE004FL
#define RTC_E_INVALID_LISTEN_SOCKET                 0x80EE007BL
#define RTC_E_INVALID_OBJECT_STATE                  0x80EE0061L
#define RTC_E_INVALID_PORTRANGE                     0x80EE005CL
#define RTC_E_INVALID_PROFILE                       0x80EE002EL
#define RTC_E_INVALID_PROXY_ADDRESS                 0x80EE0016L
#define RTC_E_INVALID_REGISTRATION_STATE            0x80EE006DL
#define RTC_E_INVALID_SESSION_STATE                 0x80EE002AL
#define RTC_E_INVALID_SESSION_TYPE                  0x80EE0029L
#define RTC_E_INVITEE_PARTY_TIMEOUT                 0x80EE006BL
#define RTC_E_LISTENING_SOCKET_NOT_EXIST            0x80EE007AL
#define RTC_E_LOCAL_PHONE_NEEDED                    0x80EE002CL
#define RTC_E_MALFORMED_XML                         0x80EE004CL
#define RTC_E_MAX_PENDING_OPERATIONS                0x80EE005AL
#define RTC_E_MAX_REDIRECTS                         0x80EE0078L
#define RTC_E_MEDIA_AEC                             0x80EE0024L
#define RTC_E_MEDIA_CONTROLLER_STATE                0x80EE001FL
#define RTC_E_MEDIA_DISABLED                        0x80EE006EL
#define RTC_E_MEDIA_ENABLED                         0x80EE006FL
#define RTC_E_MEDIA_NEED_TERMINAL                   0x80EE0020L
#define RTC_E_MEDIA_SESSION_IN_HOLD                 0x80EE0076L
#define RTC_E_MEDIA_SESSION_NOT_EXIST               0x80EE0075L
#define RTC_E_MEDIA_VIDEO_DEVICE_NOT_AVAILABLE      0x80EE0022L
#define RTC_E_NO_BUDDY                              0x80EE0054L
#define RTC_E_NO_GROUP                              0x80EE0051L
#define RTC_E_NO_PROFILE                            0x80EE002BL
#define RTC_E_NO_REALM                              0x80EE0056L
#define RTC_E_NO_TRANSPORT                          0x80EE0057L
#define RTC_E_NO_WATCHER                            0x80EE0055L
#define RTC_E_NOT_EXIST                             0x80EE0058L
#define RTC_E_NOT_PRESENCE_PROFILE                  0x80EE006AL
#define RTC_E_POLICY_NOT_ALLOW                      0x80EE0044L
#define RTC_E_PORT_MANAGER_ALREADY_SET              0x80EE007CL
#define RTC_E_PORT_MAPPING_FAILED                   0x80EE0046L
#define RTC_E_PORT_MAPPING_UNAVAILABLE              0x80EE0045L
#define RTC_E_PRESENCE_ENABLED                      0x80EE0062L
#define RTC_E_PRESENCE_NOT_ENABLED                  0x80EE0028L
#define RTC_E_PROFILE_INVALID_SERVER_AUTHMETHOD     0x80EE0038L
#define RTC_E_PROFILE_INVALID_SERVER_PROTOCOL       0x80EE0037L
#define RTC_E_PROFILE_INVALID_SERVER_ROLE           0x80EE0039L
#define RTC_E_PROFILE_INVALID_SESSION               0x80EE003BL
#define RTC_E_PROFILE_INVALID_SESSION_PARTY         0x80EE003CL
#define RTC_E_PROFILE_INVALID_SESSION_TYPE          0x80EE003DL
#define RTC_E_PROFILE_MULTIPLE_REGISTRARS           0x80EE003AL
#define RTC_E_PROFILE_NO_KEY                        0x80EE0030L
#define RTC_E_PROFILE_NO_NAME                       0x80EE0031L
#define RTC_E_PROFILE_NO_PROVISION                  0x80EE002FL
#define RTC_E_PROFILE_NO_SERVER                     0x80EE0034L
#define RTC_E_PROFILE_NO_SERVER_ADDRESS             0x80EE0035L
#define RTC_E_PROFILE_NO_USER                       0x80EE0032L
#define RTC_E_PROFILE_NO_USER_URI                   0x80EE0033L
#define RTC_E_PROFILE_SERVER_UNAUTHORIZED           0x80EE0042L
#define RTC_E_REDIRECT_PROCESSING_FAILED            0x80EE0079L
#define RTC_E_REFER_NOT_ACCEPTED                    0x80EE0070L
#define RTC_E_REFER_NOT_ALLOWED                     0x80EE0071L
#define RTC_E_REFER_NOT_EXIST                       0x80EE0072L
#define RTC_E_REGISTRATION_DEACTIVATED              0x80EE0083L
#define RTC_E_REGISTRATION_REJECTED                 0x80EE0084L
#define RTC_E_REGISTRATION_UNREGISTERED             0x80EE0085L
#define RTC_E_ROAMING_ENABLED                       0x80EE0063L
#define RTC_E_ROAMING_FAILED                        0x80EE004EL
#define RTC_E_ROAMING_OPERATION_INTERRUPTED         0x80EE004DL
#define RTC_E_SDP_CONNECTION_ADDR                   0x80EE000AL
#define RTC_E_SDP_FAILED_TO_BUILD                   0x80EE000DL
#define RTC_E_SDP_MULTICAST                         0x80EE0009L
#define RTC_E_SDP_NO_MEDIA                          0x80EE000BL
#define RTC_E_SDP_NOT_PRESENT                       0x80EE0006L
#define RTC_E_SDP_PARSE_FAILED                      0x80EE0007L
#define RTC_E_SDP_UPDATE_FAILED                     0x80EE0008L
#define RTC_E_SECURITY_LEVEL_NOT_COMPATIBLE         0x80EE007DL
#define RTC_E_SECURITY_LEVEL_NOT_DEFINED            0x80EE0048L
#define RTC_E_SECURITY_LEVEL_NOT_SUPPORTED_BY_PARTICIPANT0x80EE0049L
#define RTC_E_SIP_ADDITIONAL_PARTY_IN_TWO_PARTY_SESSION0x80EE005EL
#define RTC_E_SIP_AUTH_FAILED                       0x80EE0011L
#define RTC_E_SIP_AUTH_HEADER_SENT                  0x80EE000FL
#define RTC_E_SIP_AUTH_TIME_SKEW                    0x80EE006CL
#define RTC_E_SIP_AUTH_TYPE_NOT_SUPPORTED           0x80EE0010L
#define RTC_E_SIP_CALL_CONNECTION_NOT_ESTABLISHED   0x80EE005DL
#define RTC_E_SIP_CALL_DISCONNECTED                 0x80EE0019L
#define RTC_E_SIP_CODECS_DO_NOT_MATCH               0x80EE0000L
#define RTC_E_SIP_DNS_FAIL                          0x80EE0066L
#define RTC_E_SIP_HEADER_NOT_PRESENT                0x80EE0005L
#define RTC_E_SIP_HIGH_SECURITY_SET_TLS             0x80EE0040L
#define RTC_E_SIP_HOLD_OPERATION_PENDING            0x80EE0073L
#define RTC_E_SIP_INCOMPATIBLE_ENCRYPTION           0x80EE0064L
#define RTC_E_SIP_INVALID_CERTIFICATE               0x80EE0065L
#define RTC_E_SIP_INVITE_TRANSACTION_PENDING        0x80EE000EL
#define RTC_E_SIP_NEED_MORE_DATA                    0x80EE0018L
#define RTC_E_SIP_NO_STREAM                         0x80EE0003L
#define RTC_E_SIP_OTHER_PARTY_JOIN_IN_PROGRESS      0x80EE0060L
#define RTC_E_SIP_PARSE_FAILED                      0x80EE0004L
#define RTC_E_SIP_PARTY_ALREADY_IN_SESSION          0x80EE005FL
#define RTC_E_SIP_REQUEST_DESTINATION_ADDR_NOT_PRESENT0x80EE001AL
#define RTC_E_SIP_SSL_NEGOTIATION_TIMEOUT           0x80EE001DL
#define RTC_E_SIP_SSL_TUNNEL_FAILED                 0x80EE001CL
#define RTC_E_SIP_STACK_SHUTDOWN                    0x80EE001EL
#define RTC_E_SIP_STREAM_NOT_PRESENT                0x80EE0002L
#define RTC_E_SIP_STREAM_PRESENT                    0x80EE0001L
#define RTC_E_SIP_TCP_FAIL                          0x80EE0067L
#define RTC_E_SIP_TIMEOUT                           0x80EE000CL
#define RTC_E_SIP_TLS_FAIL                          0x80EE0069L
#define RTC_E_SIP_TRANSPORT_NOT_SUPPORTED           0x80EE0017L
#define RTC_E_SIP_UDP_SIZE_EXCEEDED                 0x80EE001BL
#define RTC_E_SIP_UNHOLD_OPERATION_PENDING          0x80EE0074L
#define RTC_E_TOO_MANY_GROUPS                       0x80EE0053L
#define RTC_E_TOO_MANY_RETRIES                      0x80EE005BL
#define RTC_E_TOO_SMALL_EXPIRES_VALUE               0x80EE0068L
#define RTC_E_STATUS_CLIENT_ADDRESS_INCOMPLETE      0x80EF01E4L
#define RTC_E_STATUS_CLIENT_AMBIGUOUS               0x80EF01E5L
#define RTC_E_STATUS_CLIENT_BAD_EXTENSION           0x80EF01A4L
#define RTC_E_STATUS_CLIENT_BAD_REQUEST             0x80EF0190L
#define RTC_E_STATUS_CLIENT_BUSY_HERE               0x80EF01E6L
#define RTC_E_STATUS_CLIENT_CONFLICT                0x80EF0199L
#define RTC_E_STATUS_CLIENT_FORBIDDEN               0x80EF0193L
#define RTC_E_STATUS_CLIENT_GONE                    0x80EF019AL
#define RTC_E_STATUS_CLIENT_LENGTH_REQUIRED         0x80EF019BL
#define RTC_E_STATUS_CLIENT_LOOP_DETECTED           0x80EF01E2L
#define RTC_E_STATUS_CLIENT_METHOD_NOT_ALLOWED      0x80EF0195L
#define RTC_E_STATUS_CLIENT_NOT_ACCEPTABLE          0x80EF0196L
#define RTC_E_STATUS_CLIENT_NOT_FOUND               0x80EF0194L
#define RTC_E_STATUS_CLIENT_PROXY_AUTHENTICATION_REQUIRED0x80EF0197L
#define RTC_E_STATUS_CLIENT_REQUEST_ENTITY_TOO_LARGE0x80EF019DL
#define RTC_E_STATUS_CLIENT_REQUEST_TIMEOUT         0x80EF0198L
#define RTC_E_STATUS_CLIENT_REQUEST_URI_TOO_LARGE   0x80EF019EL
#define RTC_E_STATUS_CLIENT_TEMPORARILY_NOT_AVAILABLE0x80EF01E0L
#define RTC_E_STATUS_CLIENT_TOO_MANY_HOPS           0x80EF01E3L
#define RTC_E_STATUS_CLIENT_TRANSACTION_DOES_NOT_EXIST0x80EF01E1L
#define RTC_E_STATUS_CLIENT_UNAUTHORIZED            0x80EF0191L
#define RTC_E_STATUS_CLIENT_UNSUPPORTED_MEDIA_TYPE  0x80EF019FL
#define RTC_E_STATUS_GLOBAL_BUSY_EVERYWHERE         0x80EF0258L
#define RTC_E_STATUS_GLOBAL_DECLINE                 0x80EF025BL
#define RTC_E_STATUS_GLOBAL_DOES_NOT_EXIST_ANYWHERE 0x80EF025CL
#define RTC_E_STATUS_GLOBAL_NOT_ACCEPTABLE          0x80EF025EL
#define RTC_E_STATUS_INFO_CALL_FORWARDING           0x00EF00B5L
#define RTC_E_STATUS_INFO_QUEUED                    0x00EF00B6L
#define RTC_E_STATUS_INFO_RINGING                   0x00EF00B4L
#define RTC_E_STATUS_INFO_TRYING                    0x00EF0064L
#define RTC_E_STATUS_NOT_ACCEPTABLE_HERE            0x80EF01E8L
#define RTC_E_STATUS_REDIRECT_ALTERNATIVE_SERVICE   0x80EF017CL
#define RTC_E_STATUS_REDIRECT_MOVED_PERMANENTLY     0x80EF012DL
#define RTC_E_STATUS_REDIRECT_MOVED_TEMPORARILY     0x80EF012EL
#define RTC_E_STATUS_REDIRECT_MULTIPLE_CHOICES      0x80EF012CL
#define RTC_E_STATUS_REDIRECT_SEE_OTHER             0x80EF012FL
#define RTC_E_STATUS_REDIRECT_USE_PROXY             0x80EF0131L
#define RTC_E_STATUS_REQUEST_TERMINATED             0x80EF01E7L
#define RTC_E_STATUS_SERVER_BAD_GATEWAY             0x80EF01F6L
#define RTC_E_STATUS_SERVER_INTERNAL_ERROR          0x80EF01F4L
#define RTC_E_STATUS_SERVER_NOT_IMPLEMENTED         0x80EF01F5L
#define RTC_E_STATUS_SERVER_SERVER_TIMEOUT          0x80EF01F8L
#define RTC_E_STATUS_SERVER_SERVICE_UNAVAILABLE     0x80EF01F7L
#define RTC_E_STATUS_SERVER_VERSION_NOT_SUPPORTED   0x80EF01F9L
#define RTC_E_STATUS_SESSION_PROGRESS               0x00EF00B7L
#define RTC_E_STATUS_SUCCESS                        0x00EF00C8L
#define RTC_E_PINT_STATUS_REJECTED_ALL_BUSY         0x80F00007L
#define RTC_E_PINT_STATUS_REJECTED_BADNUMBER        0x80F0000BL
#define RTC_E_PINT_STATUS_REJECTED_BUSY             0x80F00005L
#define RTC_E_PINT_STATUS_REJECTED_CANCELLED        0x80F0000AL
#define RTC_E_PINT_STATUS_REJECTED_NO_ANSWER        0x80F00006L
#define RTC_E_PINT_STATUS_REJECTED_PL_FAILED        0x80F00008L
#define RTC_E_PINT_STATUS_REJECTED_SW_FAILED        0x80F00009L

/* RTC_S_ (ms912578; Rtccore.h / Rtcerr.h): values printed on the page. */
#define RTC_S_ROAMING_NOT_SUPPORTED                 0x80EE0041L

/* RTCAU_ (ms931697; Rtccore.h / Rtcerr.h): values printed on the page. */
#define RTCAU_BASIC                                 0x00000001
#define RTCAU_DIGEST                                0x00000002
#define RTCAU_KERBEROS                              0x00000008
#define RTCAU_NTLM                                  0x00000004
#define RTCAU_USE_LOGON_CRED                        0x00010000

/* RTCCS_ (ms931725; Rtccore.h / Rtcerr.h): values printed on the page. */
#define RTCCS_FAIL_ON_REDIRECT                      0x00000002
#define RTCCS_FORCE_PROFILE                         0x00000001

/* RTCEF_ (ms931840; Rtccore.h / Rtcerr.h): values printed on the page. */
#define RTCEF_ALL                                   0x01FFFFFF
#define RTCEF_BUDDY                                 0x00000100
#define RTCEF_BUDDY2                                0x00040000
#define RTCEF_CLIENT                                0x00000001
#define RTCEF_GROUP                                 0x00002000
#define RTCEF_INFO                                  0x00001000
#define RTCEF_INTENSITY                             0x00000040
#define RTCEF_MEDIA                                 0x00000020
#define RTCEF_MEDIA_REQUEST                         0x00004000
#define RTCEF_MESSAGING                             0x00000080
#define RTCEF_PARTICIPANT_STATE_CHANGE              0x00000010
#define RTCEF_PRESENCE_DATA                         0x00800000
#define RTCEF_PRESENCE_PROPERTY                     0x00020000
#define RTCEF_PRESENCE_STATUS                       0x01000000
#define RTCEF_PROFILE                               0x00000400
#define RTCEF_REGISTRATION_STATE_CHANGE             0x00000002
#define RTCEF_REINVITE                              0x00400000
#define RTCEF_ROAMING                               0x00010000
#define RTCEF_SESSION_OPERATION_COMPLETE            0x00000008
#define RTCEF_SESSION_REFER_STATUS                  0x00100000
#define RTCEF_SESSION_REFERRED                      0x00200000
#define RTCEF_SESSION_STATE_CHANGE                  0x00000004
#define RTCEF_USERSEARCH                            0x00000800
#define RTCEF_WATCHER                               0x00000200
#define RTCEF_WATCHER2                              0x00080000

/* RTCIF_ (ms912432; Rtccore.h / Rtcerr.h): values printed on the page. */
#define RTCIF_DISABLE_MEDIA                         0x00000001
#define RTCIF_DISABLE_STRICT_DNS                    0x00000008
#define RTCIF_DISABLE_UPNP                          0x00000002
#define RTCIF_ENABLE_SERVER_CLASS                   0x00000004

/* RTCMT_ (ms912554; Rtccore.h / Rtcerr.h): values printed on the page. */
#define RTCMT_ALL                                   0x0000001F
#define RTCMT_ALL_RTP                               0x0000000F
#define RTCMT_AUDIO_RECEIVE                         0x00000002
#define RTCMT_AUDIO_SEND                            0x00000001
#define RTCMT_T120_SENDRECV                         0x00000010
#define RTCMT_VIDEO_RECEIVE                         0x00000008
#define RTCMT_VIDEO_SEND                            0x00000004

/* RTCRF_ (ms912574; Rtccore.h / Rtcerr.h): values printed on the page. */
#define RTCRF_REGISTER_ALL                          0x0000000F
#define RTCRF_REGISTER_INVITE_SESSIONS              0x00000001
#define RTCRF_REGISTER_MESSAGE_SESSIONS             0x00000002
#define RTCRF_REGISTER_NOTIFY                       0x00000008
#define RTCRF_REGISTER_PRESENCE                     0x00000004

/* RTCRMF_ (ms912576; Rtccore.h / Rtcerr.h): values printed on the page. */
#define RTCRMF_ALL_ROAMING                          0x0000000F
#define RTCRMF_BUDDY_ROAMING                        0x00000001
#define RTCRMF_PRESENCE_ROAMING                     0x00000004
#define RTCRMF_PROFILE_ROAMING                      0x00000008
#define RTCRMF_WATCHER_ROAMING                      0x00000002

/* RTCSI_ (ms912584; Rtccore.h / Rtcerr.h): values printed on the page. */
#define RTCSI_APPLICATION                           0x00000020
#define RTCSI_IM                                    0x00000008
#define RTCSI_MULTIPARTY                            0x00000010
#define RTCSI_PC_TO_PC                              0x00000001
#define RTCSI_PC_TO_PHONE                           0x00000002
#define RTCSI_PHONE_TO_PHONE                        0x00000004

/* RTCTR_ (ms912587; Rtccore.h / Rtcerr.h): values printed on the page. */
#define RTCTR_TCP                                   0x00000002
#define RTCTR_TLS                                   0x00000004
#define RTCTR_UDP                                   0x00000001

/* ------------------------------------------------------------------ */
/* Enumerations (RTC Client API Enumerations book, 39 pages):         */
/* verbatim prints, values printed where shown (sequential bodies     */
/* recorded where bare).                                              */
/* ------------------------------------------------------------------ */

typedef enum RTC_ACE_SCOPE {
    RTCAS_SCOPE_USER,
    RTCAS_SCOPE_DOMAIN,
    RTCAS_SCOPE_ALL,
} RTC_ACE_SCOPE;

typedef enum RTC_ANSWER_MODE {
    RTCAM_OFFER_SESSION_EVENT,
    RTCAM_AUTOMATICALLY_ACCEPT,
    RTCAM_AUTOMATICALLY_REJECT,
    RTCAM_NOT_SUPPORTED,
} RTC_ANSWER_MODE;

typedef enum RTC_AUDIO_DEVICE {
    RTCAD_SPEAKER,
    RTCAD_MICROPHONE,
} RTC_AUDIO_DEVICE;

typedef enum RTC_BUDDY_EVENT_TYPE {
    RTCBET_BUDDY_ADD,
    RTCBET_BUDDY_REMOVE,
    RTCBET_BUDDY_UPDATE,
    RTCBET_BUDDY_STATE_CHANGE,
    RTCBET_BUDDY_ROAMED,
    RTCBET_BUDDY_SUBSCRIBED,
} RTC_BUDDY_EVENT_TYPE;

typedef enum RTC_BUDDY_SUBSCRIPTION_TYPE {
    RTCBT_SUBSCRIBED,
    RTCBT_ALWAYS_OFFLINE,
    RTCBT_ALWAYS_ONLINE,
    RTCBT_POLL,
} RTC_BUDDY_SUBSCRIPTION_TYPE;

typedef enum RTC_CLIENT_EVENT_TYPE {
    RTCCET_VOLUME_CHANGE,
    RTCCET_DEVICE_CHANGE,
    RTCCET_NETWORK_QUALITY_CHANGE,
    RTCCET_ASYNC_CLEANUP_DONE,
} RTC_CLIENT_EVENT_TYPE;

typedef enum RTC_DTMF {
    RTC_DTMF_0,
    RTC_DTMF_1,
    RTC_DTMF_2,
    RTC_DTMF_3,
    RTC_DTMF_4,
    RTC_DTMF_5,
    RTC_DTMF_6,
    RTC_DTMF_7,
    RTC_DTMF_8,
    RTC_DTMF_9,
    RTC_DTMF_STAR,
    RTC_DTMF_POUND,
    RTC_DTMF_A,
    RTC_DTMF_B,
    RTC_DTMF_C,
    RTC_DTMF_D,
    RTC_DTMF_FLASH,
} RTC_DTMF;

typedef enum RTC_EVENT {
    RTCE_CLIENT,
    RTCE_REGISTRATION_STATE_CHANGE,
    RTCE_SESSION_STATE_CHANGE,
    RTCE_SESSION_OPERATION_COMPLETE,
    RTCE_PARTICIPANT_STATE_CHANGE,
    RTCE_MEDIA,
    RTCE_INTENSITY,
    RTCE_MESSAGING,
    RTCE_BUDDY,
    RTCE_WATCHER,
    RTCE_PROFILE, RTCE_USERSEARCH,
    RTCE_INFO,
    RTCE_GROUP,
    RTCE_MEDIA_REQUEST,
    RTCE_ROAMING,
    RTCE_PRESENCE_PROPERTY,
    RTCE_PRESENCE_DATA,
    RTCE_PRESENCE_STATUS,
    RTCE_SESSION_REFER_STATUS,
    RTCE_SESSION_REFERRED,
    RTCE_REINVITE,
} RTC_EVENT;

typedef enum RTC_GROUP_EVENT_TYPE {
    RTCGET_GROUP_ADD,
    RTCGET_GROUP_REMOVE,
    RTCGET_GROUP_UPDATE,
    RTCGET_GROUP_BUDDY_ADD,
    RTCGET_GROUP_BUDDY_REMOVE,
    RTCGET_GROUP_ROAMED,
} RTC_GROUP_EVENT_TYPE;

typedef enum RTC_LISTEN_MODE {
    RTCLM_NONE,
    RTCLM_DYNAMIC,
    RTCLM_BOTH,
} RTC_LISTEN_MODE;

typedef enum RTC_MEDIA_EVENT_REASON {
    RTCMER_NORMAL,
    RTCMER_HOLD,
    RTCMER_TIMEOUT,
    RTCMER_BAD_DEVICE,
    RTCMER_NO_PORT,
    RTCMER_PORT_MAPPING_FAILED,
    RTCMER_REMOTE_REQUEST,
} RTC_MEDIA_EVENT_REASON;

typedef enum RTC_MEDIA_EVENT_TYPE {
    RTCMET_STOPPED,
    RTCMET_STARTED,
    RTCMET_FAILED,
} RTC_MEDIA_EVENT_TYPE;

typedef enum RTC_MESSAGING_EVENT_TYPE {
    RTCMSET_MESSAGE,
    RTCMSET_STATUS,
} RTC_MESSAGING_EVENT_TYPE;

typedef enum RTC_MESSAGING_USER_STATUS {
    RTCMUS_IDLE,
    RTCMUS_TYPING,
} RTC_MESSAGING_USER_STATUS;

typedef enum RTC_OFFER_WATCHER_MODE {
    RTCOWM_OFFER_WATCHER_EVENT,
    RTCOWM_AUTOMATICALLY_ADD_WATCHER,
} RTC_OFFER_WATCHER_MODE;

typedef enum RTC_PARTICIPANT_STATE {
    RTCPS_IDLE,
    RTCPS_PENDING,
    RTCPS_INCOMING,
    RTCPS_ANSWERING,
    RTCPS_INPROGRESS,
    RTCPS_ALERTING,
    RTCPS_CONNECTED,
    RTCPS_DISCONNECTING,
    RTCPS_DISCONNECTED,
} RTC_PARTICIPANT_STATE;

typedef enum RTC_PORT_TYPE {
    RTCPT_AUDIO_RTP,
    RTCPT_AUDIO_RTCP,
    RTCPT_VIDEO_RTP,
    RTCPT_VIDEO_RTCP,
    RTCPT_SIP,
} RTC_PORT_TYPE;

typedef enum RTC_PRESENCE_PROPERTY {
    RTCPP_PHONENUMBER,
    RTCPP_DISPLAYNAME,
    RTCPP_EMAIL,
    RTCPP_DEVICE_NAME,
    RTCPP_MULTIPLE,
} RTC_PRESENCE_PROPERTY;

typedef enum RTC_PRESENCE_STATUS {
    RTCXS_PRESENCE_OFFLINE,
    RTCXS_PRESENCE_ONLINE,
    RTCXS_PRESENCE_AWAY,
    RTCXS_PRESENCE_IDLE,
    RTCXS_PRESENCE_BUSY,
    RTCXS_PRESENCE_BE_RIGHT_BACK,
    RTCXS_PRESENCE_ON_THE_PHONE,
    RTCXS_PRESENCE_OUT_TO_LUNCH,
} RTC_PRESENCE_STATUS;

typedef enum RTC_PRIVACY_MODE {
    RTCPM_BLOCK_LIST_EXCLUDED,
    RTCPM_ALLOW_LIST_ONLY,
} RTC_PRIVACY_MODE;

typedef enum RTC_PROFILE_EVENT_TYPE {
    RTCPFET_PROFILE_GET,
    RTCPFET_PROFILE_UPDATE,
} RTC_PROFILE_EVENT_TYPE;

typedef enum RTC_PROVIDER_URI {
    RTCPU_URIHOMEPAGE,
    RTCPU_URIHELPDESK,
    RTCPU_URIPERSONALACCOUNT,
    RTCPU_URIDISPLAYDURINGCALL,
    RTCPU_URIDISPLAYDURINGIDLE,
} RTC_PROVIDER_URI;

typedef enum RTC_REGISTRATION_STATE {
    RTCRS_NOT_REGISTERED,
    RTCRS_REGISTERING,
    RTCRS_REGISTERED,
    RTCRS_REJECTED,
    RTCRS_UNREGISTERING,
    RTCRS_ERROR,
    RTCRS_LOGGED_OFF,
    RTCRS_LOCAL_PA_LOGGED_OFF,
    RTCRS_REMOTE_PA_LOGGED_OFF,
} RTC_REGISTRATION_STATE;

typedef enum RTC_REINVITE_STATE {
    RTCRIN_INCOMING,
    RTCRIN_SUCCEEDED,
    RTCRIN_FAIL,
} RTC_REINVITE_STATE;

typedef enum RTC_RING_TYPE {
    RTCRT_PHONE,
    RTCRT_MESSAGE,
    RTCRT_RINGBACK,
} RTC_RING_TYPE;

typedef enum RTC_ROAMING_EVENT_TYPE {
    RTCRET_BUDDY_ROAMING,
    RTCRET_WATCHER_ROAMING,
    RTCRET_PRESENCE_ROAMING,
    RTCRET_PROFILE_ROAMING,
    RTCRET_WPENDING_ROAMING,
} RTC_ROAMING_EVENT_TYPE;

typedef enum RTC_SECURITY_LEVEL {
    RTCSECL_UNSUPPORTED = 1,
    RTCSECL_SUPPORTED,
    RTCSECL_REQUIRED,
} RTC_SECURITY_LEVEL;

typedef enum RTC_SECURITY_TYPE {
    RTCSECT_AUDIO_VIDEO_MEDIA_ENCRYPTION,
    RTCSECT_T120_MEDIA_ENCRYPTION,
} RTC_SECURITY_TYPE;

typedef enum RTC_SESSION_REFER_STATUS {
    RTCSRS_REFERRING,
    RTCSRS_ACCEPTED,
    RTCSRS_ERROR,
    RTCSRS_REJECTED,
    RTCSRS_DROPPED,
    RTCSRS_DONE,
} RTC_SESSION_REFER_STATUS;

typedef enum RTC_SESSION_STATE {
    RTCSS_IDLE,
    RTCSS_INCOMING,
    RTCSS_ANSWERING,
    RTCSS_INPROGRESS,
    RTCSS_CONNECTED,
    RTCSS_DISCONNECTED,
    RTCSS_HOLD,
    RTCSS_REFER,
} RTC_SESSION_STATE;

typedef enum RTC_SESSION_TYPE {
    RTCST_PC_TO_PC,
    RTCST_PC_TO_PHONE,
    RTCST_PHONE_TO_PHONE,
    RTCST_IM,
    RTCST_MULTIPARTY_IM,
    RTCST_APPLICATION,
} RTC_SESSION_TYPE;

typedef enum RTC_T120_APPLET {
    RTCTA_WHITEBOARD,
    RTCTA_APPSHARING,
} RTC_T120_APPLET;

typedef enum RTC_TERMINATE_REASON {
    RTCTR_NORMAL,
    RTCTR_DND,
    RTCTR_BUSY,
    RTCTR_REJECT,
    RTCTR_TIMEOUT,
    RTCTR_SHUTDOWN,
    RTCTR_INSUFFICIENT_SECURITY_LEVEL,
    RTCTR_NOT_SUPPORTED,
} RTC_TERMINATE_REASON;

typedef enum RTC_USER_SEARCH_COLUMN {
    RTCUSC_URI,
    RTCUSC_DISPLAYNAME,
    RTCUSC_TITLE,
    RTCUSC_OFFICE,
    RTCUSC_PHONE,
    RTCUSC_COMPANY,
    RTCUSC_CITY,
    RTCUSC_STATE,
    RTCUSC_COUNTRY,
    RTCUSC_EMAIL,
} RTC_USER_SEARCH_COLUMN;

typedef enum RTC_USER_SEARCH_PREFERENCE {
    RTCUSP_MAX_MATCHES,
    RTCUSP_TIME_LIMIT,
} RTC_USER_SEARCH_PREFERENCE;

typedef enum RTC_VIDEO_DEVICE {
    RTCVD_RECEIVE,
    RTCVD_PREVIEW,
} RTC_VIDEO_DEVICE;

typedef enum RTC_WATCHER_EVENT_TYPE {
    RTCWET_WATCHER_ADD,
    RTCWET_WATCHER_REMOVE,
    RTCWET_WATCHER_UPDATE,
    RTCWET_WATCHER_OFFERING,
    RTCWET_WATCHER_ROAMED,
} RTC_WATCHER_EVENT_TYPE;

typedef enum RTC_WATCHER_MATCH_MODE {
    RTCWMM_EXACT_MATCH,
    RTCWMM_BEST_ACE_MATCH,
} RTC_WATCHER_MATCH_MODE;

typedef enum RTC_WATCHER_STATE {
    RTCWS_UNKNOWN,
    RTCWS_OFFERING,
    RTCWS_ALLOWED,
    RTCWS_BLOCKED,
    RTCWS_DENIED,
    RTCWS_PROMPT,
} RTC_WATCHER_STATE;


/* ------------------------------------------------------------------ */
/* Interfaces (RTC Client API Interfaces book, 60 overview pages; the
 * 62nd/63rd records below -- IRTCClientEvent2, IRTCBuddyEvent2-class
 * spellings -- come from the method pages' title qualifiers).  Opaque
 * forward declarations (M44 policy).  Dangling names recorded inside
 * the records: IRTCProfile2/IRTCClient2/IRTCSession2 method pages
 * reference IRTCClientPresence2/IRTCSessionDescriptionManager
 * spellings carried by their own overview pages.
 * ------------------------------------------------------------------ */
typedef struct IRTCBuddy IRTCBuddy;
typedef struct IRTCBuddy2 IRTCBuddy2;
typedef struct IRTCBuddyEvent IRTCBuddyEvent;
typedef struct IRTCBuddyEvent2 IRTCBuddyEvent2;
typedef struct IRTCBuddyGroup IRTCBuddyGroup;
typedef struct IRTCBuddyGroupEvent IRTCBuddyGroupEvent;
typedef struct IRTCClient IRTCClient;
typedef struct IRTCClient2 IRTCClient2;
typedef struct IRTCClientEvent IRTCClientEvent;
typedef struct IRTCClientPortManagement IRTCClientPortManagement;
typedef struct IRTCClientPresence IRTCClientPresence;
typedef struct IRTCClientPresence2 IRTCClientPresence2;
typedef struct IRTCClientProvisioning IRTCClientProvisioning;
typedef struct IRTCClientProvisioning2 IRTCClientProvisioning2;
typedef struct IRTCCollection IRTCCollection;
typedef struct IRTCEnumBuddies IRTCEnumBuddies;
typedef struct IRTCEnumGroups IRTCEnumGroups;
typedef struct IRTCEnumParticipants IRTCEnumParticipants;
typedef struct IRTCEnumPresenceDevices IRTCEnumPresenceDevices;
typedef struct IRTCEnumProfiles IRTCEnumProfiles;
typedef struct IRTCEnumUserSearchResults IRTCEnumUserSearchResults;
typedef struct IRTCEnumWatchers IRTCEnumWatchers;
typedef struct IRTCEventNotification IRTCEventNotification;
typedef struct IRTCInfoEvent IRTCInfoEvent;
typedef struct IRTCIntensityEvent IRTCIntensityEvent;
typedef struct IRTCMediaEvent IRTCMediaEvent;
typedef struct IRTCMediaRequestEvent IRTCMediaRequestEvent;
typedef struct IRTCMessagingEvent IRTCMessagingEvent;
typedef struct IRTCParticipant IRTCParticipant;
typedef struct IRTCParticipantStateChangeEvent IRTCParticipantStateChangeEvent;
typedef struct IRTCPortManager IRTCPortManager;
typedef struct IRTCPresenceContact IRTCPresenceContact;
typedef struct IRTCPresenceDataEvent IRTCPresenceDataEvent;
typedef struct IRTCPresenceDevice IRTCPresenceDevice;
typedef struct IRTCPresencePropertyEvent IRTCPresencePropertyEvent;
typedef struct IRTCPresenceStatusEvent IRTCPresenceStatusEvent;
typedef struct IRTCProfile IRTCProfile;
typedef struct IRTCProfile2 IRTCProfile2;
typedef struct IRTCProfileEvent IRTCProfileEvent;
typedef struct IRTCProfileEvent2 IRTCProfileEvent2;
typedef struct IRTCReInviteEvent IRTCReInviteEvent;
typedef struct IRTCRegistrationStateChangeEvent IRTCRegistrationStateChangeEvent;
typedef struct IRTCRoamingEvent IRTCRoamingEvent;
typedef struct IRTCSession IRTCSession;
typedef struct IRTCSession2 IRTCSession2;
typedef struct IRTCSessionCallControl IRTCSessionCallControl;
typedef struct IRTCSessionDescriptionManager IRTCSessionDescriptionManager;
typedef struct IRTCSessionOperationCompleteEvent IRTCSessionOperationCompleteEvent;
typedef struct IRTCSessionOperationCompleteEvent2 IRTCSessionOperationCompleteEvent2;
typedef struct IRTCSessionPortManagement IRTCSessionPortManagement;
typedef struct IRTCSessionReferStatusEvent IRTCSessionReferStatusEvent;
typedef struct IRTCSessionReferredEvent IRTCSessionReferredEvent;
typedef struct IRTCSessionStateChangeEvent IRTCSessionStateChangeEvent;
typedef struct IRTCSessionStateChangeEvent2 IRTCSessionStateChangeEvent2;
typedef struct IRTCUserSearch IRTCUserSearch;
typedef struct IRTCUserSearchQuery IRTCUserSearchQuery;
typedef struct IRTCUserSearchResult IRTCUserSearchResult;
typedef struct IRTCUserSearchResultsEvent IRTCUserSearchResultsEvent;
typedef struct IRTCWatcher IRTCWatcher;
typedef struct IRTCWatcher2 IRTCWatcher2;
typedef struct IRTCWatcherEvent IRTCWatcherEvent;
typedef struct IRTCWatcherEvent2 IRTCWatcherEvent2;

/* IRTCBuddy: documented methods (2 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms930128 Notes: HRESULT get_Notes(BSTR* pbstrNotes);
 *   ms930134 Status: HRESULT get_Status(RTC_PRESENCE_STATUS* penStatus);
 */

/* IRTCBuddy2: documented methods (8 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms909308 EnumerateGroups: HRESULT EnumerateGroups(
 *      IRTCEnumGroups**ppEnum);
 *   ms909309 EnumeratePresenceDevices: HRESULT EnumeratePresenceDevices(
 *      IRTCEnumPresenceDevices**ppEnumDevices);
 *   ms909310 Groups: HRESULT get_Groups( IRTCCollection**ppCollection );
 *   ms909312 PresenceDevices: HRESULT get_PresenceDevices(
 *      IRTCCollection**ppDevicesCollection);
 *   ms909313 PresenceProperty: HRESULT get_PresenceProperty(
 *      RTC_PRESENCE_PROPERTYenProperty,BSTR*pbstrProperty);
 *   ms909314 Profile: HRESULT get_Profile( IRTCProfile2**ppProfile);
 *   ms909315 Refresh: HRESULT Refresh();
 *   ms909316 SubscriptionType: HRESULT
 *      get_SubscriptionType(RTC_BUDDY_SUBSCRIPTION_TYPE*penSubscriptionType);
 */

/* IRTCBuddyEvent: documented methods (1 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms909321 Buddy: HRESULT get_Buddy(IRTCBuddy** ppBuddy);
 */

/* IRTCBuddyEvent2: documented methods (3 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms909317 EventType: HRESULT get_EventType(
 *      RTC_BUDDY_EVENT_TYPE*pEventType );
 *   ms909319 StatusCode: HRESULT get_StatusCode( long*plStatusCode);
 *   ms909320 StatusText: HRESULT get_StatusText BSTR*pbstrStatusText );
 */

/* IRTCBuddyGroup: documented methods (7 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms909323 AddBuddy: HRESULT AddBuddy( IRTCBuddy*pBuddy );
 *   ms909324 Buddies: HRESULT get_Buddies( IRTCCollection**ppCollection );
 *   ms909325 Data: HRESULT put_Data( BSTRbstrData );HRESULT get_Data(
 *      BSTR*pbstrData );
 *   ms909326 EnumerateBuddies: HRESULT EnumerateBuddies(
 *      IRTCEnumBuddies**ppEnum );
 *   ms929968 Name: HRESULT put_Name( BSTRbstrGroupName );HRESULT get_Name(
 *      BSTR*pbstrGroupName);
 *   ms930098 Profile: HRESULT get_Profile( IRTCProfile2**ppProfile );
 *   ms930105 RemoveBuddy: HRESULT RemoveBuddy( IRTCBuddy*pBuddy);
 */

/* IRTCBuddyGroupEvent: documented methods (4 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms909327 Buddy: HRESULT get_Buddy( IRTCBuddy2**ppBuddy );
 *   ms909328 EventType: HRESULT get_EventType(
 *      RTC_GROUP_EVENT_TYPE*pEventType );
 *   ms909329 Group: HRESULT get_Group( IRTCBuddyGroup**ppGroup );
 *   ms909548 StatusCode: HRESULT get_StatusCode( long*plStatusCode );
 */

/* IRTCClient: documented methods (30 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910041 ActiveMedia: HRESULT get_ActiveMedia(long* plMediaType);
 *   ms910051 AudioMuted: HRESULT
 *      put_AudioMuted(RTC_AUDIO_DEVICEenDevice,VARIANT_BOOLfMuted);HRESULT
 *      get_AudioMuted(RTC_AUDIO_DEVICEenDevice,VARIANT_BOOL* pfMuted);
 *   ms910054 CreateSession: HRESULT
 *      CreateSession(RTC_SESSION_TYPEenType,BSTRbstrLocalPhoneURI,IRTCProfil
 *      e* pProfile,longlFlags,IRTCSession** ppSession);
 *   ms910058 EventFilter: HRESULT put_EventFilter(longlFilter);HRESULT
 *      get_EventFilter(long* plFilter);
 *   ms910066 IVideoWindow: HRESULT get_IVideoWindow(RTC_VIDEO_DEVICE
 *      enDevice,IVideoWindow** ppIVideoWindow);
 *   ms910061 Initialize: HRESULT Initialize();
 *   ms910062 InvokeTuningWizard: HRESULT
 *      InvokeTuningWizard(OAHWNDhwndParent);
 *   ms910063 IsT120AppletRunning: HRESULT
 *      get_IsT120AppletRunning(RTC_T120_APPLET enApplet, VARIANT_BOOL*
 *      pfRunning);
 *   ms910064 IsTuned: HRESULT get_IsTuned(VARIANT_BOOL* pfTuned);
 *   ms910067 ListenForIncomingSessions: HRESULT
 *      put_ListenForIncomingSessions(RTC_LISTEN_MODEenListen);HRESULT
 *      get_ListenForIncomingSessions(RTC_LISTEN_MODE* penListen);
 *   ms910068 LocalUserName: HRESULT
 *      put_LocalUserName(BSTRbstrUserName);HRESULT get_LocalUserName(BSTR*
 *      pbstrUserName);
 *   ms910069 LocalUserURI: HRESULT put_LocalUserURI(BSTRbstrUserURI);HRESULT
 *      get_LocalUserURI(BSTR* pbstrUserURI);
 *   ms910071 MaxBitrate: HRESULT set_MaxBitrate(long lMaxBitrate);HRESULT
 *      get_MaxBitrate(long* plMaxBitrate);
 *   ms910072 MediaCapabilities: HRESULT get_MediaCapabilities(long*
 *      plMediaTypes);
 *   ms910073 NetworkAddresses: HRESULT
 *      get_NetworkAddresses(VARIANT_BOOLfTCP,VARIANT_BOOL fExternal,VARIANT*
 *      pvAddresses);
 *   ms910074 NetworkQuality: HRESULT get_NetworkQuality(long*
 *      plNetworkQuality);
 *   ms910075 PlayRing: HRESULT
 *      PlayRing(RTC_RING_TYPEenType,VARIANT_BOOLbPlay);
 *   ms910080 PreferredAEC: HRESULT
 *      put_PreferredAEC(VARIANT_BOOLbEnable);HRESULT
 *      get_PreferredAEC(VARIANT_BOOL* pbEnabled);
 *   ms910081 PreferredAudioDevice: HRESULT
 *      put_PreferredAudioDevice(RTC_AUDIO_DEVICE
 *      enDevice,BSTRbstrDeviceName);HRESULT
 *      get_PreferredAudioDevice(RTC_AUDIO_DEVICE enDevice,BSTR*
 *      pbstrDeviceName);
 *   ms910082 PreferredMediaTypes: HRESULT get_PreferredMediaTypes(long*
 *      plMediaTypes);
 *   ms910083 PreferredVideoDevice: HRESULT set_PreferredVideoDevice(BSTR
 *      bstrDeviceName);HRESULT get_PreferredVideoDevice(BSTR*
 *      pbstrDeviceName);
 *   ms910084 PreferredVolume: HRESULT
 *      put_PreferredVolume(RTC_AUDIO_DEVICEenDevice,longlVolume);HRESULT
 *      get_PreferredVolume(RTC_AUDIO_DEVICEenDevice,long* plVolume);
 *   ms910085 PrepareForShutdown: HRESULT PrepareForShutdown();
 *   ms910129 SendDTMF: HRESULT SendDTMF(RTC_DTMFenDTMF);
 *   ms910130 SetPreferredMediaTypes: HRESULT
 *      SetPreferredMediaTypes(longlMediaTypes,VARIANT_BOOLfPersistent);
 *   ms910131 Shutdown: HRESULT Shutdown();
 *   ms910132 StartT120Applet: HRESULT StartT120Applet(RTC_T120_APPLET
 *      enApplet);
 *   ms910133 StopT120Applets: HRESULT StopT120Applets();
 *   ms910134 TemporalSpatialTradeOff: HRESULT
 *      set_TemporalSpatialTradeOff(long lValue);HRESULT
 *      get_TemporalSpatialTradeOff(long* plValue);
 *   ms910135 Volume: HRESULT put_Volume(RTC_AUDIO_DEVICEenDevice,longlVolume
 *      );HRESULT get_Volume(RTC_AUDIO_DEVICEenDevice,long* plVolume);
 */

/* IRTCClient2: documented methods (10 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms909665 AllowedPorts: HRESULT put_AllowedPorts( long lTransport,
 *      RTC_LISTEN_MODE penMode);HRESULT get_AllowedPorts( long lTransport,
 *      RTC_LISTEN_MODE* penMode);
 *   ms909769 AnswerMode: HRESULT put_AnswerMode(
 *      RTC_SESSION_TYPEenType,RTC_ANSWER_MODEenMode );HRESULT
 *      get_AnswerMode( RTC_SESSION_TYPEenType,RTC_ANSWER_MODE*penMode );
 *   ms909780 ClientCurVer: HRESULT put_ClientCurVer(BSTRbstrClientCurVer);
 *   ms909789 ClientName: HRESULT put_ClientName(BSTRbstrClientName);
 *   ms909800 CreateSessionWithDescription: HRESULT
 *      CreateSessionWithDescription(BSTRbstrContentType,
 *      BSTRbstrSessionDescription, IRTCProfile*pProfile, longlFlags,
 *      IRTCSession2**ppSession2);
 *   ms909809 InitializeEx: HRESULT InitializeEx(longlFlags);
 *   ms909899 InvokeTuningWizardEx: HRESULT InvokeTuningWizardEx(
 *      OAHWNDhwndParent,VARIANT_BOOLfAllowAudio,VARIANT_BOOLfAllowVideo );
 *   ms930346 PreferredSecurityLevel: HRESULT
 *      put_PreferredSecurityLevel(RTC_SECURITY_TYPEenSecurityType,RTC_SECURI
 *      TY_LEVELenSecurityLevel);HRESULT
 *      get_PreferredSecurityLevel(RTC_SECURITY_TYPEenSecurityType,RTC_SECURI
 *      TY_LEVEL*penSecurityLevel);
 *   ms930435 SetSessionDescriptionManager: HRESULT
 *      SetSessionDescriptionManager(IRTCSessionDescriptionManager*pSessionDe
 *      scriptionManager);
 *   ms930643 Version: HRESULT get_Version( long*plVersion );
 */

/* IRTCClientEvent: documented methods (2 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910055 Client: HRESULT get_Client(IRTCClient** ppClient);
 *   ms910056 EventType: HRESULT get_EventType(RTC_CLIENT_EVENT_TYPE*
 *      penEventType);
 */

/* IRTCClientPortManagement: documented methods (3 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910076 GetPortRange: HRESULT
 *      GetPortRange(RTC_PORT_TYPEenPortType,long*plMinValue,long*plMaxValue);
 *   ms910078 StartListenAddressAndPort: HRESULT
 *      StartListenAddressAndPort(BSTRbstrInternalLocalAddress,longlInternalL
 *      ocalPort);
 *   ms910079 StopListenAddressAndPort: HRESULT
 *      StopListenAddressAndPort(BSTRbstrInternalLocalAddress,longlInternalLo
 *      calPort);
 */

/* IRTCClientPresence: documented methods (16 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910101 AddBuddy: HRESULT AddBuddy(BSTR
 *      bstrPresentityURI,BSTRbstrUserName,BSTRbstrData,VARIANT_BOOLfPersiste
 *      nt,IRTCProfile* pProfile,longlFlags,IRTCBuddy** ppBuddy);
 *   ms910102 AddWatcher: HRESULT
 *      AddWatcher(BSTRbstrPresentityURI,BSTRbstrUserName,BSTRbstrData,VARIAN
 *      T_BOOLfBlocked,VARIANT_BOOLfPersistent,IRTCWatcher** ppWatcher);
 *   ms910103 Buddies: HRESULT get_Buddies(IRTCCollection** ppCollection);
 *   ms910104 Buddy: HRESULT get_Buddy(BSTRbstrPresentityURI,IRTCBuddy**
 *      ppBuddy);
 *   ms910105 EnablePresence: HRESULT
 *      EnablePresence(VARIANT_BOOLfUseStorage,VARIANTvarStorage);
 *   ms910106 EnumerateBuddies: HRESULT EnumerateBuddies(IRTCEnumBuddies**
 *      ppEnum);
 *   ms910107 EnumerateWatchers: HRESULT EnumerateWatchers(IRTCEnumWatchers**
 *      ppEnum);
 *   ms910108 Export: HRESULT Export(VARIANTvarStorage);
 *   ms910109 Import: HRESULT Import(VARIANTvarStorage,VARIANT_BOOLfReplaceAl
 *      l);
 *   ms910112 OfferWatcherMode: HRESULT
 *      put_OfferWatcherMode(RTC_OFFER_WATCHER_MODEenMode);HRESULT
 *      get_OfferWatcherMode(RTC_OFFER_WATCHER_MODE* penMode);
 *   ms910113 PrivacyMode: HRESULT put_PrivacyMode(RTC_PRIVACY_MODE
 *      enMode);HRESULT get_PrivacyMode(RTC_PRIVACY_MODE* penMode);
 *   ms910114 RemoveBuddy: HRESULT RemoveBuddy(IRTCBuddy* pBuddy);
 *   ms910115 RemoveWatcher: HRESULT RemoveWatcher(IRTCWatcher* pWatcher);
 *   ms910116 SetLocalPresenceInfo: HRESULT
 *      SetLocalPresenceInfo(RTC_PRESENCE_STATUS enStatus,BSTR bstrNotes);
 *   ms910117 Watcher: HRESULT
 *      get_Watcher(BSTRbstrPresentityURI,IRTCWatcher** ppWatcher);
 *   ms910118 Watchers: HRESULT get_Watchers(IRTCCollection** ppCollection);
 */

/* IRTCClientPresence2: documented methods (14 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910086 AddBuddyEx: HRESULT
 *      AddBuddyEx(BSTRbstrPresentityURI,BSTRbstrUserName,BSTRbstrData,VARIAN
 *      T_BOOLfPersistent,RTC_BUDDY_SUBSCRIPTION_TYPEenSubscriptionType,IRTCP
 *      rofile*pProfile,longlFlags,IRTCBuddy2**ppBuddy2);
 *   ms910087 AddGroup: HRESULT AddGroup(
 *      BSTRbstrGroupName,BSTRbstrData,IRTCProfile*pProfile,longlFlags,IRTCBu
 *      ddyGroup**ppGroup );
 *   ms910088 AddWatcherEx: HRESULT AddWatcherEx( BSTRbstrPresentityURI,
 *      BSTRbstrUserName, BSTRbstrData, RTC_WATCHER_STATEenState,
 *      VARIANT_BOOLfPersistent, RTC_ACE_SCOPEenScope, IRTCProfile*pProfile,
 *      longlFlags, IRTCWatcher2**ppWatcher);
 *   ms910089 DisablePresence: HRESULT DisablePresence();
 *   ms910090 EnablePresenceEx: HRESULT EnablePresenceEx(
 *      IRTCProfile*pProfile,VARIANTvarStorage,longlFlags );
 *   ms910091 EnumerateGroups: HRESULT EnumerateGroups(
 *      IRTCEnumGroups**ppEnum );
 *   ms910092 GetLocalPresenceInfo: HRESULT
 *      GetLocalPresenceInfo(RTC_PRESENCE_STATUS*penStatus,BSTR*pbstrNotes);
 *   ms910093 GetPresenceData: HRESULT
 *      GetPresenceData(BSTR*pbstrNamespace,BSTR*pbstrData);
 *   ms910094 Group: HRESULT get_Group(
 *      BSTRbstrGroupName,IRTCBuddyGroup**ppGroup );
 *   ms910095 Groups: HRESULT get_Groups( IRTCCollection**ppCollection );
 *   ms910097 PresenceProperty: HRESULT
 *      put_PresenceProperty(RTC_PRESENCE_PROPERTYenProperty,BSTRbstrProperty
 *      );HRESULT get_PresenceProperty(RTC_PRESENCE_PROPERTYenProperty,BSTR*p
 *      bstrProperty);
 *   ms910098 RemoveGroup: HRESULT RemoveGroup( IRTCBuddyGroup*pGroup );
 *   ms910099 SetPresenceData: HRESULT
 *      SetPresenceData(BSTRbstrNamespace,BSTRbstrData);
 *   ms910100 WatcherEx: HRESULT get_WatcherEx(
 *      RTC_WATCHER_MATCH_MODEenMode,BSTRbstrPresentityURI,IRTCWatcher2**ppWa
 *      tcher );
 */

/* IRTCClientProvisioning: documented methods (7 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910121 CreateProfile: HRESULT CreateProfile(BSTR
 *      bstrProfileXML,IRTCProfile** ppProfile);
 *   ms910122 DisableProfile: HRESULT DisableProfile(IRTCProfile* pProfile);
 *   ms910123 EnableProfile: HRESULT EnableProfile(IRTCProfile* pProfile,long
 *      lRegisterFlags);
 *   ms910124 EnumerateProfiles: HRESULT EnumerateProfiles(IRTCEnumProfiles**
 *      ppEnum);
 *   ms910125 GetProfile: HRESULT
 *      GetProfile(BSTRbstrUserAccount,BSTRbstrUserPassword,BSTRbstrUserURI,B
 *      STRbstrServer,longlTransport,LONG_PTRlCookie);
 *   ms910127 Profiles: HRESULT get_Profiles(IRTCCollection** ppCollection);
 *   ms910128 SessionCapabilities: HRESULT get_SessionCapabilities(long*
 *      plSupportedSessions);
 */

/* IRTCClientProvisioning2: documented methods (1 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910119 EnableProfileEx: HRESULT EnableProfileEx(
 *      IRTCProfile*pProfile,longlRegisterFlags,longlRoamingFlags );
 */

/* IRTCCollection: documented methods (3 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms930755 Count: HRESULT get_Count(long* lCount);
 *   ms930835 Item: HRESULT get_Item(long Index,VARIANT* pVariant);
 *   ms930842 _NewEnum: HRESULT get__NewEnum(IUnknown** ppNewEnum);
 */

/* IRTCEnumBuddies: documented methods (4 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms930851 Clone: HRESULT Clone(IRTCEnumBuddies** ppEnum);
 *   ms930867 Next: HRESULT Next( ULONG celt, IRTCBuddy** ppElements,ULONG*
 *      pceltFetched);
 *   ms930877 Reset: HRESULT Reset();
 *   ms930885 Skip: HRESULT Skip(ULONG celt);
 */

/* IRTCEnumGroups: documented methods (4 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms930893 Clone: HRESULT Clone( IRTCEnumGroups** ppEnum);
 *   ms910271 Next: HRESULT Next( ULONG celt, IRTCBuddyGroup** ppElements,
 *      ULONG* pceltFetched);
 *   ms910302 Reset: HRESULT Reset();
 *   ms910310 Skip: HRESULT Skip( ULONG celt);
 */

/* IRTCEnumParticipants: documented methods (4 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910323 Clone: HRESULT Clone(IRTCEnumParticipants** ppEnum);
 *   ms910340 Next: HRESULT Next( ULONG celt, IRTCParticipant**
 *      ppElements,ULONG* pceltFetched);
 *   ms910350 Reset: HRESULT Reset();
 *   ms910356 Skip: HRESULT Skip(ULONG celt);
 */

/* IRTCEnumPresenceDevices: documented methods (4 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910365 Clone: HRESULT Clone(IRTCEnumPresenceDevices**ppEnum);
 *   ms910377 Next: HRESULT Next(ULONGcelt,IRTCPresenceDevice**ppElements,ULO
 *      NG*pceltFetched);
 *   ms910387 Reset: HRESULT Reset();
 *   ms910391 Skip: HRESULT Skip(ULONGcelt);
 */

/* IRTCEnumProfiles: documented methods (4 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910397 Clone: HRESULT Clone(IRTCEnumProfiles** ppEnum);
 *   ms910408 Next: HRESULT Next( ULONG celt, IRTCProfile** ppElements,ULONG*
 *      pceltFetched);
 *   ms910413 Reset: HRESULT Reset();
 *   ms910417 Skip: HRESULT Skip(ULONG celt);
 */

/* IRTCEnumUserSearchResults: documented methods (4 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910426 Clone: HRESULT Clone( IRTCEnumUserSearchResults** ppEnum);
 *   ms910437 Next: HRESULT Next( ULONG celt, IRTCUserSearchResult**
 *      ppElements, ULONG* pceltFetched);
 *   ms910443 Reset: HRESULT Reset();
 *   ms910452 Skip: HRESULT Skip( ULONG celt);
 */

/* IRTCEnumWatchers: documented methods (4 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910453 Clone: HRESULT Clone(IRTCEnumWatchers** ppEnum);
 *   ms910455 Next: HRESULT Next( ULONG celt, IRTCWatcher** ppElements,ULONG*
 *      pceltFetched);
 *   ms910456 Reset: HRESULT Reset();
 *   ms910457 Skip: HRESULT Skip(ULONG celt);
 */

/* IRTCEventNotification: documented methods (1 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910458 Event: HRESULT Event(RTC_EVENT RTCEvent,IDispatch* pEvent);
 */

/* IRTCInfoEvent: documented methods (4 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910461 Info: HRESULT get_Info( BSTR* pbstrInfo);
 *   ms910462 InfoHeader: HRESULT get_InfoHeader( BSTR* pbstrInfoHeader);
 *   ms910463 Participant: HRESULT get_Participant( IRTCParticipant**
 *      ppParticipant);
 *   ms910464 Session: HRESULT get_Session( IRTCSession2** ppSession);
 */

/* IRTCIntensityEvent: documented methods (4 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910465 Direction: HRESULT get_Direction(RTC_AUDIO_DEVICE*
 *      penDirection);
 *   ms910467 Level: HRESULT get_Level(long* plLevel);
 *   ms910468 Max: HRESULT get_Max(long* plMax);
 *   ms910469 Min: HRESULT get_Min(long* plMin);
 */

/* IRTCMediaEvent: documented methods (3 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910470 EventReason: HRESULT get_EventReason(
 *      RTC_MEDIA_EVENT_REASON*penEventReason);
 *   ms910471 EventType: HRESULT get_EventType(
 *      RTC_MEDIA_EVENT_TYPE*penEventType );
 *   ms910473 MediaType: HRESULT get_MediaType( long*pMediaType );
 */

/* IRTCMediaRequestEvent: documented methods (7 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910474 Accept: HRESULT Accept( long lMediaTypes);
 *   ms910475 CurrentMedia: HRESULT get_CurrentMedia( long* plMediaTypes);
 *   ms910477 ProposedMedia: HRESULT get_ProposedMedia( long* plMediaTypes);
 *   ms910478 Reject: HRESULT Reject();
 *   ms910479 RemotePreferredSecurityLevel: HRESULT
 *      get_RemotePreferredSecurityLevel(RTC_SECURITY_TYPEenSecurityType,RTC_
 *      SECURITY_LEVEL*penSecurityLevel);
 *   ms910480 Session: HRESULT get_Session( IRTCSession2** ppSession);
 *   ms910481 State: HRESULT get_State( RTC_REINVITE_STATE* pState);
 */

/* IRTCMessagingEvent: documented methods (6 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910482 EventType: HRESULT get_EventType(RTC_MESSAGING_EVENT_TYPE*
 *      penEventType);
 *   ms910484 Message: HRESULT get_Message(BSTR* pbstrMessage);
 *   ms910485 MessageHeader: HRESULT get_MessageHeader(BSTR*
 *      pbstrMessageHeader);
 *   ms910486 Participant: HRESULT get_Participant(IRTCParticipant**
 *      ppParticipant);
 *   ms910487 Session: HRESULT get_Session(IRTCSession** ppSession);
 *   ms910488 UserStatus: HRESULT get_UserStatus(RTC_MESSAGING_USER_STATUS*
 *      penUserStatus);
 */

/* IRTCParticipant: documented methods (5 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910490 Name: HRESULT get_Name(BSTR* pbstrName);
 *   ms910491 Removable: HRESULT get_Removable(VARIANT_BOOL* pfRemovable);
 *   ms910492 Session: HRESULT get_Session(IRTCSession** ppSession);
 *   ms910493 State: HRESULT get_State(RTC_PARTICIPANT_STATE* penState);
 *   ms910498 UserURI: HRESULT get_UserURI(BSTR* pbstrUserURI);
 */

/* IRTCParticipantStateChangeEvent: documented methods (3 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910495 Participant: HRESULT get_Participant(IRTCParticipant**
 *      ppParticipant);
 *   ms910496 State: HRESULT get_State(RTC_PARTICIPANT_STATE* penState);
 *   ms910497 StatusCode: HRESULT get_StatusCode(long* plStatusCode);
 */

/* IRTCPortManager: documented methods (3 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910499 GetMapping: HRESULT GetMapping( BSTR bstrRemoteAddress,
 *      RTC_PORT_TYPE enPortType, BSTR* pbstrInternalLocalAddress, long*
 *      plInternalLocalPort, BSTR* pbstrExternalLocalAddress, long*
 *      plExternalLocalPort);
 *   ms910501 ReleaseMapping: HRESULT ReleaseMapping( BSTR
 *      bstrInternalLocalAddress, long lInternalLocalPort, BSTR
 *      bstrExternalLocalAddress, long lExternalLocalPort);
 *   ms910502 UpdateRemoteAddress: HRESULT UpdateRemoteAddress( BSTR
 *      bstrRemoteAddress, BSTR bstrInternalLocalAddress, long
 *      lInternalLocalPort, BSTR bstrExternalLocalAddress, long
 *      lExternalLocalPort);
 */

/* IRTCPresenceContact: documented methods (4 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910503 Data: HRESULT put_Data( BSTRbstrData );HRESULT get_Data(
 *      BSTR*pbstrData );
 *   ms910505 Name: HRESULT put_Name( BSTRbstrName );HRESULT get_Name(
 *      BSTR*pbstrName );
 *   ms910506 Persistent: HRESULT put_Persistent( VARIANT_BOOLfPersistent
 *      );HRESULT get_Persistent(VARIANT_BOOL*pfPersistent);
 *   ms910507 PresentityURI: HRESULT put_PresentityURI( BSTRbstrPresentityURI
 *      );HRESULT get_PresentityURI( BSTR*pbstrPresentityURI );
 */

/* IRTCPresenceDataEvent: documented methods (3 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910508 GetPresenceData: HRESULT
 *      GetPresenceData(BSTR*pbstrNamespace,BSTR* pbstrData);
 *   ms910510 StatusCode: HRESULT get_StatusCode( long*plStatusCode );
 *   ms910511 StatusText: HRESULT get_StatusText( BSTR*pbstrStatusText );
 */

/* IRTCPresenceDevice: documented methods (4 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910512 GetPresenceData: HRESULT GetPresenceData(BSTR*
 *      pbstrNamespace,BSTR* pbstrData);
 *   ms910514 Notes: HRESULT get_Notes(BSTR* pbstrNotes);
 *   ms910515 PresenceProperty: HRESULT
 *      get_PresenceProperty(RTC_PRESENCE_PROPERTY enProperty,BSTR*
 *      pbstrProperty);
 *   ms910516 Status: HRESULT get_Status(RTC_PRESENCE_STATUS* penStatus);
 */

/* IRTCPresencePropertyEvent: documented methods (4 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910518 PresenceProperty: HRESULT
 *      get_PresenceProperty(RTC_PRESENCE_PROPERTY*penPresProp);
 *   ms910647 StatusCode: HRESULT get_StatusCode( long*plStatusCode );
 *   ms910714 StatusText: HRESULT get_StatusText(BSTR*pbstrStatusText);
 *   ms910716 Value: HRESULT get_Value(BSTR*pbstrValue);
 */

/* IRTCPresenceStatusEvent: documented methods (3 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910723 GetLocalPresenceInfo: HRESULT
 *      GetLocalPresenceInfo(RTC_PRESENCE_STATUS*penStatus,BSTR* pbstrNotes);
 *   ms910732 StatusCode: HRESULT get_StatusCode( long*plStatusCode );
 *   ms910739 StatusText: HRESULT get_StatusText( BSTR*pbstrStatusText );
 */

/* IRTCProfile: documented methods (18 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910755 ClientBanner: HRESULT get_ClientBanner(VARIANT_BOOL* pfBanner);
 *   ms910763 ClientCurVer: HRESULT get_ClientCurVer(BSTR* pbstrCurVer);
 *   ms910765 ClientData: HRESULT get_ClientData(BSTR* pbstrData);
 *   ms910773 ClientMinVer: HRESULT get_ClientMinVer(BSTR* pbstrMinVer);
 *   ms910779 ClientName: HRESULT get_ClientName(BSTR* pbstrName);
 *   ms910783 ClientUpdateURI: HRESULT get_ClientUpdateURI(BSTR*
 *      pbstrUpdateURI);
 *   ms910822 Key: HRESULT get_Key(BSTR* pbstrKey);
 *   ms910829 Name: HRESULT get_Name(BSTR* pbstrName);
 *   ms910834 ProviderData: HRESULT get_ProviderData(BSTR* pbstrData);
 *   ms910840 ProviderName: HRESULT get_ProviderName(BSTR* pbstrName);
 *   ms910842 ProviderURI: HRESULT get_ProviderURI(RTC_PROVIDER_URI
 *      enURI,BSTR* pbstrURI);
 *   ms910847 SessionCapabilities: HRESULT get_SessionCapabilities(long*
 *      plSupportedSessions);
 *   ms910854 SetCredentials: HRESULT SetCredentials(BSTR bstrUserURI,BSTR
 *      bstrUserAccount,BSTR bstrPassword);
 *   ms910856 State: HRESULT get_State(RTC_REGISTRATION_STATE* penState);
 *   ms910861 UserAccount: HRESULT get_UserAccount(BSTR* pbstrUserAccount);
 *   ms910869 UserName: HRESULT get_UserName(BSTR* pbstrUserName);
 *   ms910874 UserURI: HRESULT get_UserURI(BSTR* pbstrUserURI);
 *   ms910875 XML: HRESULT get_XML(BSTR* pbstrXML);
 */

/* IRTCProfile2: documented methods (2 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910743 AllowedAuth: HRESULT put_AllowedAuth( long
 *      lAllowedAuth);HRESULT get_AllowedAuth( long* plAllowedAuth);
 *   ms910751 Realm: HRESULT put_Realm( BSTR bstrRealm);HRESULT get_Realm(
 *      BSTR* pbstrRealm);
 */

/* IRTCProfileEvent: documented methods (3 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910798 Cookie: HRESULT get_Cookie( LONG_PTR* plCookie);
 *   ms910808 Profile: HRESULT get_Profile( IRTCProfile** ppProfile);
 *   ms910813 StatusCode: HRESULT get_StatusCode( long* plStatusCode);
 */

/* IRTCProfileEvent2: documented methods (1 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910785 EventType: HRESULT get_EventType( RTC_PROFILE_EVENT_TYPE*
 *      pEventType);
 */

/* IRTCReInviteEvent: documented methods (5 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910881 Accept: HRESULT Accept(BSTRbstrContentType,BSTRbstrSessionDescr
 *      iption);
 *   ms910882 GetRemoteSessionDescription: HRESULT
 *      GetRemoteSessionDescription(BSTR*pbstrContentType,BSTR*pbstrSessionDe
 *      scription);
 *   ms910884 Reject: HRESULT Reject();
 *   ms910885 Session: HRESULT get_Session(IRTCSession2**ppSession2);
 *   ms910886 State: HRESULT get_State( RTC_REINVITE_STATE* pState);
 */

/* IRTCRegistrationStateChangeEvent: documented methods (4 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910877 Profile: HRESULT get_Profile(IRTCProfile** ppProfile);
 *   ms910878 State: HRESULT get_State(RTC_REGISTRATION_STATE* penState);
 *   ms910879 StatusCode: HRESULT get_StatusCode(long* plStatusCode);
 *   ms910880 StatusText: HRESULT get_StatusText(BSTR* pbstrStatusText);
 */

/* IRTCRoamingEvent: documented methods (4 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910887 EventType: HRESULT get_EventType( RTC_ROAMING_EVENT_TYPE*
 *      pEventType);
 *   ms910890 Profile: HRESULT get_Profile( IRTCProfile2** ppProfile);
 *   ms910891 StatusCode: HRESULT get_StatusCode( long* plStatusCode);
 *   ms910892 StatusText: HRESULT get_StatusText( BSTR* pbstrStatusText);
 */

/* IRTCSession: documented methods (20 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910899 AddParticipant: HRESULT AddParticipant(BSTR bstrAddress,BSTR
 *      bstrName,IRTCParticipant** ppParticipant);
 *   ms910900 AddStream: HRESULT AddStream(long lMediaType,LONG_PTR lCookie);
 *   ms910901 Answer: HRESULT Answer( );
 *   ms910910 CanAddParticipants: HRESULT
 *      get_CanAddParticipants(VARIANT_BOOL* pfCanAdd);
 *   ms910911 Client: HRESULT get_Client(IRTCClient** ppClient);
 *   ms910914 EncryptionKey: HRESULT put_EncryptionKey(long lMediaType,BSTR
 *      EncryptionKey);
 *   ms910915 EnumerateParticipants: HRESULT
 *      EnumerateParticipants(IRTCEnumParticipants** ppEnum);
 *   ms910917 NextRedirectedUser: HRESULT NextRedirectedUser();
 *   ms910926 Participants: HRESULT get_Participants(IRTCCollection**
 *      ppCollection);
 *   ms910929 Profile: HRESULT get_Profile(IRTCProfile** ppProfile);
 *   ms910930 Redirect: HRESULT Redirect(RTC_SESSION_TYPE enType,BSTR
 *      bstrLocalPhoneURI,IRTCProfile* pProfile,long lFlags);
 *   ms910931 RedirectedUserName: HRESULT get_RedirectedUserName(BSTR*
 *      pbstrUserName);
 *   ms910932 RedirectedUserURI: HRESULT get_RedirectedUserURI(BSTR*
 *      pbstrUserURI);
 *   ms930927 RemoveParticipant: HRESULT RemoveParticipant(IRTCParticipant*
 *      pParticipant);
 *   ms930933 RemoveStream: HRESULT RemoveStream(long lMediaType,LONG_PTR
 *      lCookie);
 *   ms930939 SendMessage: HRESULT SendMessage(BSTR bstrMessageHeader,BSTR
 *      bstrMessage,LONG_PTR lCookie);
 *   ms930943 SendMessageStatus: HRESULT
 *      SendMessageStatus(RTC_MESSAGING_USER_STATUS enUserStatus,LONG_PTR
 *      lCookie);
 *   ms930950 State: HRESULT get_State(RTC_SESSION_STATE* penState);
 *   ms931149 Terminate: HRESULT Terminate(RTC_TERMINATE_REASON enReason);
 *   ms931166 Type: HRESULT get_Type(RTC_SESSION_TYPE* penType);
 */

/* IRTCSession2: documented methods (5 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910893 AnswerWithSessionDescription: HRESULT
 *      AnswerWithSessionDescription(BSTRbstrContentType,BSTRbstrSessionDescr
 *      iption);
 *   ms910895 IsSecurityEnabled: HRESULT
 *      IsSecurityEnabled(RTC_SECURITY_TYPEenSecurityType,VARIANT_BOOL*pfSecu
 *      rityEnabled);
 *   ms910896 PreferredSecurityLevel: HRESULT
 *      put_PreferredSecurityLevel(RTC_SECURITY_TYPEenSecurityType,RTC_SECURI
 *      TY_LEVEL enSecurityLevel);HRESULT
 *      get_PreferredSecurityLevel(RTC_SECURITY_TYPEenSecurityType,RTC_SECURI
 *      TY_LEVEL*penSecurityLevel);
 *   ms910897 ReInviteWithSessionDescription: HRESULT
 *      ReInviteWithSessionDescription(BSTRbstrContentType,BSTRbstrSessionDes
 *      cription,LONG_PTR lCookie);
 *   ms910898 SendInfo: HRESULT SendInfo( BSTR bstrInfoHeader, BSTR bstrInfo,
 *      LONG_PTR lCookie);
 */

/* IRTCSessionCallControl: documented methods (7 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910902 Forward: HRESULT Forward(BSTRbstrForwardToURI);
 *   ms910903 Hold: HRESULT Hold(LONG_PTRlCookie);
 *   ms910904 IsReferred: HRESULT get_IsReferred(VARIANT_BOOL* pfIsReferred);
 *   ms910906 Refer: HRESULT Refer(BSTRbstrReferToURI,BSTRbstrReferCookie);
 *   ms910907 ReferCookie: HRESULT
 *      put_ReferCookie(BSTRbstrReferCookie);HRESULT
 *      get_ReferCookie(BSTR*pbstrReferCookie);
 *   ms910908 ReferredByURI: HRESULT
 *      put_ReferredByURI(BSTRbstrReferredByURI);HRESULT
 *      get_ReferredByURI(BSTR*pbstrReferredByURI);
 *   ms910909 UnHold: HRESULT UnHold(LONG_PTRlCookie);
 */

/* IRTCSessionDescriptionManager: documented methods (1 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910912 EvaluateSessionDescription: HRESULT
 *      EvaluateSessionDescription(BSTRbstrContentType,BSTRbstrSessionDescrip
 *      tion,VARIANT_BOOL*pfApplicationSession);
 */

/* IRTCSessionOperationCompleteEvent: documented methods (4 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910921 Cookie: HRESULT get_Cookie(LONG_PTR* plCookie);
 *   ms910923 Session: HRESULT get_Session(IRTCSession** ppSession);
 *   ms910924 StatusCode: HRESULT get_StatusCode(long* plStatusCode);
 *   ms910925 StatusText: HRESULT get_StatusText(BSTR* pbstrStatusText);
 */

/* IRTCSessionOperationCompleteEvent2: documented methods (2 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910918 GetRemoteSessionDescription: HRESULT
 *      GetRemoteSessionDescription(BSTR*pbstrContentType,BSTR*pbstrSessionDe
 *      scription);
 *   ms910920 Participant: HRESULT get_Participant( IRTCParticipant**
 *      ppParticipant);
 */

/* IRTCSessionPortManagement: documented methods (1 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910928 SetPortManager: HRESULT SetPortManager( IRTCPortManager*
 *      pPortManager);
 */

/* IRTCSessionReferStatusEvent: documented methods (4 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms911220 ReferStatus: HRESULT
 *      get_ReferStatus(RTC_SESSION_REFER_STATUS*penReferStatus);
 *   ms911312 Session: HRESULT get_Session(IRTCSession2**ppSession);
 *   ms930910 StatusCode: HRESULT get_StatusCode(long*plStatusCode);
 *   ms930918 StatusText: HRESULT get_StatusText(BSTR*pbstrStatusText);
 */

/* IRTCSessionReferredEvent: documented methods (7 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms910933 Accept: HRESULT Accept();
 *   ms910935 ReferCookie: HRESULT get_ReferCookie(BSTR*pbstrReferCookie);
 *   ms910937 ReferToURI: HRESULT get_ReferToURI(BSTR*pbstrReferToURI);
 *   ms910936 ReferredByURI: HRESULT
 *      get_ReferredByURI(BSTR*pbstrReferredByURI);
 *   ms910938 Reject: HRESULT Reject();
 *   ms910939 Session: HRESULT get_Session(IRTCSession2**ppSession);
 *   ms910940 SetReferredSessionState: HRESULT
 *      SetReferredSessionState(RTC_SESSION_STATEenState);
 */

/* IRTCSessionStateChangeEvent: documented methods (4 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms931011 Session: HRESULT get_Session(IRTCSession** ppSession);
 *   ms931017 State: HRESULT get_State(RTC_SESSION_STATE* penState);
 *   ms931031 StatusCode: HRESULT get_StatusCode(long* plStatusCode);
 *   ms931043 StatusText: HRESULT get_StatusText(BSTR* pbstrStatusText);
 */

/* IRTCSessionStateChangeEvent2: documented methods (4 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms930958 GetRemoteSessionDescription: HRESULT
 *      GetRemoteSessionDescription(BSTR*pbstrContentType,BSTR*pbstrSessionDe
 *      scription);
 *   ms930976 IsForked: HRESULT get_IsForked(VARIANT_BOOL*pfIsForked);
 *   ms930984 MediaTypes: HRESULT get_MediaTypes( long* pMediaTypes);
 *   ms930993 RemotePreferredSecurityLevel: HRESULT
 *      get_RemotePreferredSecurityLevel(RTC_SECURITY_TYPEenSecurityType,RTC_
 *      SECURITY_LEVEL*penSecurityLevel);
 */

/* IRTCUserSearch: documented methods (2 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms911320 CreateQuery: HRESULT CreateQuery( IRTCUserSearchQuery**
 *      ppQuery);
 *   ms911326 ExecuteSearch: HRESULT ExecuteSearch( IRTCUserSearchQuery*
 *      pQuery, IRTCProfile* pProfile, LONG_PTR lCookie);
 */

/* IRTCUserSearchQuery: documented methods (4 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms911348 SearchDomain: HRESULT put_SearchDomain( BSTR
 *      bstrDomain);HRESULT get_SearchDomain( BSTR* pbstrDomain);
 *   ms911359 SearchPreference: HRESULT put_SearchPreference(
 *      RTC_USER_SEARCH_PREFERENCE enPreference, long lValue);HRESULT
 *      get_SearchPreference( RTC_USER_SEARCH_PREFERENCE enPreference, long*
 *      plValue);
 *   ms911365 SearchTerm: HRESULT put_SearchTerm( BSTR bstrName, BSTR
 *      bstrValue);HRESULT get_SearchTerm( BSTR bstrName, BSTR* pbstrValue);
 *   ms911377 SearchTerms: HRESULT get_SearchTerms( BSTR* pbstrNames);
 */

/* IRTCUserSearchResult: documented methods (1 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms911458 Value: HRESULT get_Value( RTC_USER_SEARCH_COLUMN enColumn,
 *      BSTR* pbstrValue);
 */

/* IRTCUserSearchResultsEvent: documented methods (7 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms911392 Cookie: HRESULT get_Cookie( LONG_PTR* plCookie);
 *   ms911400 EnumerateResults: HRESULT EnumerateResults(
 *      IRTCEnumUserSearchResults** ppEnum);
 *   ms911421 MoreAvailable: HRESULT get_MoreAvailable( VARIANT_BOOL*
 *      pfMoreAvailable);
 *   ms911430 Profile: HRESULT get_Profile( IRTCProfile2** ppProfile);
 *   ms911437 Query: HRESULT get_Query( IRTCUserSearchQuery** ppQuery);
 *   ms911445 Results: HRESULT get_Results( IRTCCollection** ppCollection);
 *   ms911449 StatusCode: HRESULT get_StatusCode( long* plStatusCode);
 */

/* IRTCWatcher: documented methods (1 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms911524 State: HRESULT put_State(RTC_WATCHER_STATE enState);HRESULT
 *      get_State(RTC_WATCHER_STATE* penState);
 */

/* IRTCWatcher2: documented methods (2 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms911477 Profile: HRESULT get_Profile( IRTCProfile2** ppProfile);
 *   ms911481 Scope: HRESULT get_Scope( RTC_ACE_SCOPE* penScope);
 */

/* IRTCWatcherEvent: documented methods (1 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms911509 Watcher: HRESULT get_Watcher(IRTCWatcher** ppWatcher);
 */

/* IRTCWatcherEvent2: documented methods (2 pages; Windows CE
 * .NET 4.0/4.2 and later; Rtccore.h, Rtccore.idl; Link Library:
 * Uuid.lib).  Vtable layouts are not published; signatures recorded
 * verbatim (archive type-space traps preserved: e.g.
 * RTC_SESSION_TYPEenType, BSTRbstrLocalPhoneURI, longlFlags).
 *   ms911489 EventType: HRESULT get_EventType( RTC_WATCHER_EVENT_TYPE*
 *      pEventType);
 *   ms911496 StatusCode: HRESULT get_StatusCode( long* plStatusCode);
 */

#ifdef __cplusplus
}
#endif

#endif /* AKARI_RTCCORE_H */
