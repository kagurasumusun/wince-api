/* Windns.h -- DNS types (Windows CE).
 * Pages: tools/manifests/netgen.manifest.  IP4_ADDRESS,
 * DNS_IP6_ADDRESS, DNS_ATMA_MAX_ADDR_LENGTH, DNS_STATUS and
 * DNS_FREE_TYPE are not published on any CE page: the structs that
 * embed the first three and all four Dnsapi.lib functions are
 * recorded verbatim.  See docs/inventory.md M77b.
 */

#ifndef AKARI_WINDNS_H
#define AKARI_WINDNS_H

#include "Windef.h"    /* WORD, DWORD, BYTE, UCHAR, BOOL, LPTSTR,
                        * PBYTE */
#include "Winnt.h"     /* LONGLONG */

typedef struct _DNS_HEADER {
    WORD Xid;
    BYTE RecursionDesired;
    BYTE Truncation;
    BYTE Authoritative;
    BYTE Opcode;
    BYTE IsResponse;
    BYTE ResponseCode;
    BYTE Reserved;
    BYTE RecursionAvailable;
    WORD QuestionCount;
    WORD AnswerCount;
    WORD NameServerCount;
    WORD AdditionalCount;
} DNS_HEADER, *PDNS_HEADER;

typedef struct _DNS_MESSAGE_BUFFER {
    DNS_HEADER MessageHead;
    CHAR       MessageBody[1];
} DNS_MESSAGE_BUFFER, *PDNS_MESSAGE_BUFFER;

typedef struct _DNS_WIRE_QUESTION {
    WORD QuestionType;
    WORD QuestionClass;
} DNS_WIRE_QUESTION, *PDNS_WIRE_QUESTION;

typedef struct _DNS_WIRE_RECORD {
    WORD  RecordType;
    WORD  RecordClass;
    DWORD TimeToLive;
    WORD  DataLength;
} DNS_WIRE_RECORD, *PDNS_WIRE_RECORD;

/* "DNS_RECORD_FLAGS": print `typedef struct _DnsRecordFlags
 * {DWORD Section :2;DWORD Delete :1;DWORD CharSet :2;
 * DWORD Unused :3;DWORD Reserved :24;} DNS_RECORD_FLAGS;` */
typedef struct _DnsRecordFlags {
    DWORD Section : 2;
    DWORD Delete : 1;
    DWORD CharSet : 2;
    DWORD Unused : 3;
    DWORD Reserved : 24;
} DNS_RECORD_FLAGS;

typedef struct { LPTSTR pNameMailbox; LPTSTR pNameErrorsMailbox; }
    DNS_MINFO_DATA, *PDNS_MINFO_DATA;
typedef struct { LPTSTR pNameExchange; WORD wPreference; WORD Pad; }
    DNS_MX_DATA, *PDNS_MX_DATA;
typedef struct { LPTSTR pNameHost; } DNS_PTR_DATA, *PDNS_PTR_DATA;
typedef struct { LPTSTR pNamePrimaryServer; LPTSTR pNameAdministrator;
    DWORD dwSerialNo; DWORD dwRefresh; DWORD dwRetry; DWORD dwExpire;
    DWORD dwDefaultTtl; } DNS_SOA_DATA, *PDNS_SOA_DATA;
typedef struct { LPTSTR pNameTarget; WORD wPriority; WORD wWeight;
    WORD wPort; WORD Pad; } DNS_SRV_DATA, *PDNS_SRV_DATA;
typedef struct { DWORD dwStringCount; LPTSTR pStringArray[1]; }
    DNS_TXT_DATA, *PDNS_TXT_DATA;
typedef struct { DWORD dwByteCount; BYTE Data[1]; }
    DNS_NULL_DATA, *PDNS_NULL_DATA;
typedef struct { WORD wFlags; BYTE chProtocol; BYTE chAlgorithm;
    BYTE Key[1]; } DNS_KEY_DATA, *PDNS_KEY_DATA;
typedef struct { WORD wVersion; WORD wSize; WORD wHorPrec;
    WORD wVerPrec; DWORD dwLatitude; DWORD dwLongitude;
    DWORD dwAltitude; } DNS_LOC_DATA, *PDNS_LOC_DATA;
typedef struct { LPTSTR pNameSigner; WORD wTypeCovered;
    BYTE chAlgorithm; BYTE chLabelCount; DWORD dwOriginalTtl;
    DWORD dwExpiration; DWORD dwTimeSigned; WORD wKeyTag; WORD Pad;
    BYTE Signature[1]; } DNS_SIG_DATA, *PDNS_SIG_DATA;
typedef struct { LPTSTR pNameNext; WORD wNumTypes; WORD wTypes[1]; }
    DNS_NXT_DATA, *PDNS_NXT_DATA;
typedef struct { LPTSTR pNameAlgorithm; PBYTE pAlgorithmPacket;
    PBYTE pKey; PBYTE pOtherData; DWORD dwCreateTime;
    DWORD dwExpireTime; WORD wMode; WORD wError; WORD wKeyLength;
    WORD wOtherLength; UCHAR cAlgNameLength; BOOL bPacketPointers; }
    DNS_TKEY_DATA, *PDNS_TKEY_DATA;
typedef struct { LPTSTR pNameAlgorithm; PBYTE pAlgorithmPacket;
    PBYTE pSignature; PBYTE pOtherData; LONGLONG i64CreateTime;
    WORD wFudgeTime; WORD wOriginalXid; WORD wError; WORD wSigLength;
    WORD wOtherLength; UCHAR cAlgNameLength; BOOL bPacketPointers; }
    DNS_TSIG_DATA, *PDNS_TSIG_DATA;
typedef struct { DWORD dwMappingFlag; DWORD dwLookupTimeout;
    DWORD dwCacheTimeout; LPTSTR pNameResultDomain; }
    DNS_WINSR_DATA, *PDNS_WINSR_DATA;
typedef struct { DWORD IP6Dword[4]; } IP6_ADDRESS, *PIP6_ADDRESS;

/* DNS_RECORD: verbatim print (the Data union embeds the
 * record-only members below) -- pointer-only. */
typedef struct _DnsRecord DNS_RECORD, *PDNS_RECORD;

/* DNS_RRSET: print `typedef struct _DnsRRSet { PDNS_RECORD pFirstRR;
 * PDNS_RECORD pLastRR;} DNS_RRSET, *PDNS_RRSET;` */
typedef struct _DnsRRSet {
    PDNS_RECORD pFirstRR;
    PDNS_RECORD pLastRR;
} DNS_RRSET, *PDNS_RRSET;

/* --- Record-only (unpublished scalar/size types). ----------------
 * IP4_ADDRESS and DNS_IP6_ADDRESS (scalar typedefs),
 * DNS_ATMA_MAX_ADDR_LENGTH (value):
 *   DNS_A_DATA {IP4_ADDRESS IpAddress;} / DNS_WKS_DATA
 *     {IP4_ADDRESS IpAddress; UCHAR chProtocol; BYTE BitMask[1];} /
 *   DNS_WINS_DATA {DWORD dwMappingFlag; DWORD dwLookupTimeout;
 *     DWORD dwCacheTimeout; DWORD cWinsServerCount;
 *     IP4_ADDRESS WinsServers[1];} / IP4_ARRAY {DWORD AddrCount;
 *     IP4_ADDRESS AddrArray[1];} /
 *   DNS_AAAA_DATA {DNS_IP6_ADDRESS Ip6Address;} /
 *   DNS_ATMA_DATA {BYTE AddressType;BYTE Address[DNS_ATMA_MAX_ADDR_LENGTH];}
 * DNS_RECORD (aa450351) full print: `typedef struct _DnsRecord
 * {struct _DnsRecord* pNext;LPTSTR pName;WORD wType;WORD wDataLength;
 * union {DWORD DW;DNS_RECORD_FLAGS S;} Flags;DWORD dwTtl;
 * DWORD dwReserved;union {DNS_A_DATA A;DNS_SOA_DATA SOA, Soa;
 * DNS_PTR_DATA PTR, Ptr, NS, Ns, CNAME, Cname, MB, Mb, MD, Md, MF, Mf,
 * MG, Mg, MR, Mr;DNS_MINFO_DATA MINFO, Minfo, RP, Rp;DNS_MX_DATA MX,
 * Mx, AFSDB, Afsdb, RT, Rt;DNS_TXT_DATA HINFO, Hinfo, ISDN, Isdn,
 * TXT, Txt, X25;DNS_NULL_DATA Null;DNS_WKS_DATA WKS, Wks;
 * DNS_AAAA_DATA AAAA;DNS_KEY_DATA KEY, Key;DNS_SIG_DATA SIG, Sig;
 * DNS_ATMA_DATA ATMA, Atma;DNS_NXT_DATA NXT, Nxt;DNS_SRV_DATA SRV,
 * Srv;DNS_TKEY_DATA TKEY, Tkey;DNS_TSIG_DATA TSIG, Tsig;
 * DNS_WINS_DATA WINS, Wins;DNS_WINSR_DATA WINSR, WinsR, NBSTAT,
 * Nbstat;} Data;} DNS_RECORD, *PDNS_RECORD;`
 * Dnsapi.lib functions (DNS_STATUS / DNS_FREE_TYPE unpublished):
 *   aa450336 DnsQuery_W: `DNS_STATUS WINAPI DnsQuery_W( PCWSTR pszName,
 *     WORD wType, DWORD fOptions, PIP4_ARRAY aipServers,
 *     PDNS_RECORD* ppQueryResultsSet, PVOID* pReserved);`
 *   aa450335 DnsModifyRecordsInSet_W: `DNS_STATUS WINAPI
 *     DnsModifyRecordsInSet_W( PDNS_RECORD pAddRecords,
 *     PDNS_RECORD pDeleteRecords, DWORD Options, HANDLE hContext,
 *     PIP4_ARRAY pServerList, PVOID pReserved);`
 *   aa450338 DnsReplaceRecordSetW: `DNS_STATUS WINAPI
 *     DnsReplaceRecordSetW( PDNS_RECORD pNewSet, DWORD Options,
 *     HANDLE hContext, PIP_ARRAY pServerList, PVOID pReserved);`
 *   aa450337 DnsRecordListFree: `void WINAPI DnsRecordListFree(
 *     PDNS_RECORD pRecordList, DNS_FREE_TYPE FreeType);` */

#endif /* AKARI_WINDNS_H */
