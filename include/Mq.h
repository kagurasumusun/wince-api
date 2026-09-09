/* Mq.h -- Message Queuing (MSMQ) for Windows CE.
 *
 * Pages: manifest tools/manifests/servers.manifest (Servers book,
 * Message Queuing node); Link Library rows print Msmqrt.lib
 * (C runtime functions, def/msmqrt-doc.def).  OS rows: Windows
 * CE 2.0 and later; versions prior to 2.12 require the MSMQ
 * add-on pack.  See docs/inventory.md M75a.
 */

#ifndef AKARI_MQ_H
#define AKARI_MQ_H

#include "Windef.h"    /* HANDLE, DWORD, VOID, PVOID, APIENTRY,
                        * LPHANDLE */
#include "Winbase.h"   /* LPDWORD, LPWSTR, LPCWSTR, LPOVERLAPPED */
#include "Objbase.h"   /* HRESULT, PSECURITY_DESCRIPTOR, PROPVARIANT */

/* --- Print-grounded closures. ------------------------------------
 * PHANDLE: printed by MQCreateCursor, unpublished as a typedef --
 * mechanical HANDLE pointer (LPHANDLE sibling).
 * QUEUEHANDLE: no CE page prints the typedef; used by the MQ*
 * signatures and paired with PHANDLE out-params in MQCreateCursor --
 * closed as HANDLE.  ITransaction: no interface page; the name is
 * printed by the MQSendMessage signature -- opaque forward.
 * Replace each on an official print. */
typedef HANDLE *PHANDLE;
typedef HANDLE QUEUEHANDLE;
typedef QUEUEHANDLE *LPQUEUEHANDLE;
typedef struct ITransaction ITransaction;

/* --- Property structures: pointer-only (members depend on
 *     unpublished types); verbatim prints recorded. --------------- */

/* ms895125 "MQMSGPROPS": print
 * `typedef struct tagMQMSGPROPS {DWORD cProp;MSGPROPID aPropID[];
 * PROPVARIANT aPropVar[];HRESULT aStatus[];} MQMSGPROPS;` */
typedef struct MQMSGPROPS MQMSGPROPS;

/* ms895140 "MQQUEUEPROPS": print
 * `typedef struct tagMQQUEUEPROPS {DWORD cProp;QUEUEPROPID
 * aPropID[];PROPVARIANT aPropVar[];HRESULT aStatus[];}
 * MQQUEUEPROPS;` */
typedef struct MQQUEUEPROPS MQQUEUEPROPS;

/* ms895138 "MQQMPROPS": print
 * `typedef struct tagMQQMPROPS {DWORD cProp;QMPROPID aPropID[];
 * PROPVARIANT aPropVar[];HRESULT aStatus[];} MQQMPROPS;` */
typedef struct MQQMPROPS MQQMPROPS;

/* ms895134 "MQPROPVARIANT": print
 * `struct tagMQPROPVARIANT {VARTYPE vt;WORD wReserved1;
 * WORD wReserved2;WORD wReserved3;union{UCHAR bVal;short iVal;
 * USHORT uiVal;VARIANT_BOOL bool;long lVal;ULONG ulVal;
 * SCODE scode;DATE date;CLSID _RPC_FAR* puuid;BLOB blob;
 * LPOLESTR bstrVal;LPSTR pszVal;LPWSTR pwszVal;CAUI1 caub;
 * CAI2 cai;CAUI2 caus;CABOOL cabool;CAI4 cal;CAUI4 caul;
 * CACLSID cauuid;CABSTR cabstr;CALPWSTR calpwstr;
 * CAPROPVARIANT capropvar;};};typedef struct MQPROPVARIANT
 * MQPROPVARIANT;` -- the CA-family and BLOB union members are the
 * same unpublished types that hold PROPVARIANT (Objbase.h, M73a);
 * pointer-only here. */
typedef struct MQPROPVARIANT MQPROPVARIANT;

/* MQMGMTPROPS (used by MQMgmtGetInfo, Mqmgmt.h rows): no CE page
 * prints the structure -- pointer-only, recorded by use. */
typedef struct MQMGMTPROPS MQMGMTPROPS;

/* --- Property identifiers: HELD. ---------------------------------
 * aa450286 "aPropID" prints
 *   typedef PROPID MSGPROPID
 *   typedef PROPID QUEUEPROPID
 *   typedef PROPID QMPROPID
 * but no CE page publishes the PROPID typedef or the numeric value
 * of any property identifier -- all PROPID names are recorded only:
 * PROPID_M_ACKNOWLEDGE (ms896290)   PROPID_M_ADMIN_QUEUE (ms896291)
 * PROPID_M_ADMIN_QUEUE_LEN (ms896292)   PROPID_M_APPSPECIFIC (ms896293)
 * PROPID_M_ARRIVEDTIME (ms896294)   PROPID_M_AUTH_LEVEL (ms896295)
 * PROPID_M_BODY (ms896296)   PROPID_M_BODY_SIZE (ms896297)
 * PROPID_M_BODY_TYPE (ms896298)   PROPID_M_CLASS (ms896299)
 * PROPID_M_COMPOUND_MESSAGE (ms896300)   PROPID_M_COMPOUND_MESSAGE_SIZE (ms896301)
 * PROPID_M_CORRELATIONID (ms896302)   PROPID_M_DELIVERY (ms896303)
 * PROPID_M_DEST_QUEUE (ms896304)   PROPID_M_DEST_QUEUE_LEN (ms896305)
 * PROPID_M_EXTENSION (ms896306)   PROPID_M_EXTENSION_LEN (ms896307)
 * PROPID_M_FIRST_IN_XACT (ms896308)   PROPID_M_JOURNAL (ms896309)
 * PROPID_M_LABEL (ms896310)   PROPID_M_LABEL_LEN (ms896311)
 * PROPID_M_LAST_IN_XACT (ms896312)   PROPID_M_MSGID (ms896313)
 * PROPID_M_PRIORITY (ms896314)   PROPID_M_RESP_QUEUE (ms896315)
 * PROPID_M_RESP_QUEUE_LEN (ms896316)   PROPID_M_SENTTIME (ms896317)
 * PROPID_M_SOAP_BODY (ms896318)   PROPID_M_SOAP_ENVELOPE (ms896319)
 * PROPID_M_SOAP_ENVELOPE_LEN (ms896320)   PROPID_M_SOAP_HEADER (ms896321)
 * PROPID_M_SRC_MACHINE_ID (ms896322)   PROPID_M_TIME_TO_BE_RECEIVED (ms896323)
 * PROPID_M_TIME_TO_REACH_QUEUE (ms896324)   PROPID_M_TRACE (ms896325)
 * PROPID_M_VERSION (ms896326)   PROPID_M_XACTID (ms896327)
 * PROPID_QM_MACHINE_ID (ms896334)   PROPID_Q_AUTHENTICATE (ms896328)
 * PROPID_Q_CREATE_TIME (ms896329)   PROPID_Q_JOURNAL (ms896330)
 * PROPID_Q_JOURNAL_QUOTA (ms896331)   PROPID_Q_LABEL (ms896332)
 * PROPID_Q_MODIFY_TIME (ms896335)   PROPID_Q_PATHNAME (ms896336)
 * PROPID_Q_PRIV_LEVEL (ms896337)   PROPID_Q_QUOTA (ms896338)
 * PROPID_Q_TRANSACTION (ms896339)
 */

/* --- Functions (Msmqrt.lib -> def/msmqrt-doc.def). --------------- */

/* ms895103 "MQCloseCursor" */
AKARI_CE_IMPORT HRESULT APIENTRY MQCloseCursor(HANDLE hCursor)
                    AKARI_CE_NAME(MQCloseCursor);

/* ms895104 "MQCloseQueue" */
AKARI_CE_IMPORT HRESULT APIENTRY MQCloseQueue(QUEUEHANDLE hQueue)
                    AKARI_CE_NAME(MQCloseQueue);

/* ms895106 "MQCreateCursor" */
AKARI_CE_IMPORT HRESULT APIENTRY MQCreateCursor(QUEUEHANDLE hQueue, PHANDLE phCursor)
                    AKARI_CE_NAME(MQCreateCursor);

/* ms895108 "MQCreateQueue" */
AKARI_CE_IMPORT HRESULT APIENTRY MQCreateQueue(PSECURITY_DESCRIPTOR pSecurityDescriptor,
                    MQQUEUEPROPS *pQueueProps, LPWSTR lpwcsFormatName,
                    LPDWORD lpdwFormatNameLength)
                    AKARI_CE_NAME(MQCreateQueue);

/* ms895110 "MQDeleteQueue" */
AKARI_CE_IMPORT HRESULT APIENTRY MQDeleteQueue(LPCWSTR lpwcsFormatName)
                    AKARI_CE_NAME(MQDeleteQueue);

/* ms895113 "MQFreeMemory" */
AKARI_CE_IMPORT HRESULT APIENTRY MQFreeMemory(PVOID pvMemory)
                    AKARI_CE_NAME(MQFreeMemory);

/* ms895115 "MQGetMachineProperties" */
AKARI_CE_IMPORT HRESULT APIENTRY MQGetMachineProperties(LPCWSTR lpwcsMachineName,
                    const GUID *pguidMachineID,
                    MQQMPROPS *pQMProps)
                    AKARI_CE_NAME(MQGetMachineProperties);

/* ms895117 "MQGetQueueProperties" */
AKARI_CE_IMPORT HRESULT APIENTRY MQGetQueueProperties(LPCWSTR lpwcsFormatName,
                    MQQUEUEPROPS *pQueueProps)
                    AKARI_CE_NAME(MQGetQueueProperties);

/* ms895119 "MQHandleToFormatName" */
AKARI_CE_IMPORT HRESULT APIENTRY MQHandleToFormatName(QUEUEHANDLE hQueue, LPWSTR lpwcsFormatName,
                    LPDWORD lpdwCount)
                    AKARI_CE_NAME(MQHandleToFormatName);

/* ms895121 "MQMgmtAction" */
AKARI_CE_IMPORT HRESULT MQMgmtAction(LPCWSTR pMachineName, LPCWSTR pObjectName,
                    LPCWSTR pAction) AKARI_CE_NAME(MQMgmtAction);

/* ms895123 "MQMgmtGetInfo" */
AKARI_CE_IMPORT HRESULT MQMgmtGetInfo(LPCWSTR pMachineName, LPCWSTR pObjectName,
                    MQMGMTPROPS *pMgmtProps) AKARI_CE_NAME(MQMgmtGetInfo);

/* ms895127 "MQOpenQueue" */
AKARI_CE_IMPORT HRESULT APIENTRY MQOpenQueue(LPCWSTR lpwcsFormatName, DWORD dwAccess,
                    DWORD dwShareMode, LPQUEUEHANDLE phQueue)
                    AKARI_CE_NAME(MQOpenQueue);

/* ms895130 "MQPathNameToFormatName" */
AKARI_CE_IMPORT HRESULT APIENTRY MQPathNameToFormatName(LPCWSTR lpwcsPathName,
                    LPWSTR lpwcsFormatName, LPDWORD lpdwCount)
                    AKARI_CE_NAME(MQPathNameToFormatName);

/* ms895144 "MQSendMessage" */
AKARI_CE_IMPORT HRESULT APIENTRY MQSendMessage(QUEUEHANDLE hDestinationQueue,
                    MQMSGPROPS *pMessageProps,
                    ITransaction *pTransaction)
                    AKARI_CE_NAME(MQSendMessage);

/* ms895147 "MQSetQueueProperties" */
AKARI_CE_IMPORT HRESULT APIENTRY MQSetQueueProperties(LPCWSTR lpwcsFormatName,
                    MQQUEUEPROPS *pQueueProps)
                    AKARI_CE_NAME(MQSetQueueProperties);

/* MQReceiveMessage (ms895126): HELD as a declaration -- the print
 *   HRESULT APIENTRY MQReceiveMessage(QUEUEHANDLE hSource,
 *     DWORD dwTimeout,DWORD dwAction,MQMSGPROPS pMessageProps,
 *     LPOVERLAPPED lpOverlapped,PMQRECEIVECALLBACK fnReceiveCallback,
 *     HANDLE hCursor,Transaction* pTransaction);
 * passes MQMSGPROPS by value (pointer-only here, like its
 * siblings) and names PMQRECEIVECALLBACK and Transaction, whose
 * typedefs no CE page publishes.  Recorded verbatim. */

/* --- MSMQ COM object model (Mqoai.h rows, Mqoa.lib): recorded,
 *     not compiled; alias Mqoai.h -> this header.  Book overview
 *     pages with Mqoai.h/Mq.h rows: MSMQ Application Development (ms898983), MSMQ COM Objects (ms886696), MSMQ COM Support (ms882757), MSMQ Functions (ms886697), MSMQ Migration (ms898984), MSMQ Modules and Descriptions (ms882831), MSMQ OS Design Development (ms882768), MSMQ Programming Model (ms882835). */
/* MSMQApplication object (ms895149):
 */
/* MSMQEvent object (ms895150):
 *   MSMQEvent.Arrived (ms895153)
 *   MSMQEvent.ArrivedError (ms895154)
 */
/* MSMQMessage object (ms895156):
 *   MSMQMessage.Ack (ms895158)
 *   MSMQMessage.AdminQueueInfo (ms895160)
 *   MSMQMessage.AppSpecific (ms895163)
 *   MSMQMessage.ArrivedTime (ms895164)
 *   MSMQMessage.AuthLevel (ms895166)
 *   MSMQMessage.Body (ms895169)
 *   MSMQMessage.BodyLength (ms895170)
 *   MSMQMessage.Class (ms895173)
 *   MSMQMessage.CorrelationId (ms895174)
 *   MSMQMessage.Delivery (ms895176)
 *   MSMQMessage.DestinationQueueInfo (ms895178)
 *   MSMQMessage.EncryptAlgorithm (ms895181)
 *   MSMQMessage.Extension (ms895182)
 *   MSMQMessage.HashAlgorithm (ms895185)
 *   MSMQMessage.Id (ms895186)
 *   MSMQMessage.IsAuthenticated (ms895189)
 *   MSMQMessage.Journal (ms895190)
 *   MSMQMessage.Label (ms895193)
 *   MSMQMessage.MaxTimeToReachQueue (ms895194)
 *   MSMQMessage.MaxTimeToReceive (ms895196)
 *   MSMQMessage.Priority (ms895199)
 *   MSMQMessage.PrivLevel (ms895200)
 *   MSMQMessage.ResponseQueueInfo (ms895203)
 *   MSMQMessage.Send (ms895204)
 *   MSMQMessage.SenderCertificate (ms895207)
 *   MSMQMessage.SenderId (ms895208)
 *   MSMQMessage.SenderIdType (ms895211)
 *   MSMQMessage.SentTime (ms895212)
 *   MSMQMessage.SourceMachineGuid (ms895215)
 *   MSMQMessage.Trace (ms895217)
 */
/* MSMQQuery object (ms895219):
 */
/* MSMQQueue object (ms895221):
 *   MSMQQueue.Access (ms895224)
 *   MSMQQueue.Close (ms895225)
 *   MSMQQueue.EnableNotification (ms895228)
 *   MSMQQueue.Handle (ms895231)
 *   MSMQQueue.IsOpen (ms895276)
 *   MSMQQueue.Peek (ms895279)
 *   MSMQQueue.PeekCurrent (ms895281)
 *   MSMQQueue.PeekNext (ms895284)
 *   MSMQQueue.QueueInfo (ms895286)
 *   MSMQQueue.Receive (ms895287)
 *   MSMQQueue.ReceiveCurrent (ms895289)
 *   MSMQQueue.Reset (ms895614)
 *   MSMQQueue.ShareMode (ms895653)
 */
/* MSMQQueueInfo object (ms895232):
 *   MSMQQueueInfo.Authenticate (ms895234)
 *   MSMQQueueInfo.BasePriority (ms895236)
 *   MSMQQueueInfo.Create (ms895238)
 *   MSMQQueueInfo.CreateTime (ms895240)
 *   MSMQQueueInfo.Delete (ms895241)
 *   MSMQQueueInfo.FormatName (ms895244)
 *   MSMQQueueInfo.IsTransactional (ms895245)
 *   MSMQQueueInfo.IsWorldReadable (ms895248)
 *   MSMQQueueInfo.Journal (ms895249)
 *   MSMQQueueInfo.JournalQuota (ms895252)
 *   MSMQQueueInfo.Label (ms895253)
 *   MSMQQueueInfo.ModifyTime (ms895256)
 *   MSMQQueueInfo.Open (ms895257)
 *   MSMQQueueInfo.PathName (ms895260)
 *   MSMQQueueInfo.PrivLevel (ms895261)
 *   MSMQQueueInfo.QueueGuid (ms895264)
 *   MSMQQueueInfo.Quota (ms895266)
 *   MSMQQueueInfo.Refresh (ms895268)
 *   MSMQQueueInfo.ServiceTypeGuid (ms895272)
 *   MSMQQueueInfo.Update (ms895275)
 */
/* MSMQQueueInfos object (ms895270):
 */

#endif /* AKARI_MQ_H */
