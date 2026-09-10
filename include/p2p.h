/* p2p.h -- Peer-to-Peer Networking identity/enum API (Windows CE 5.0+).
 *
 * Pages: tools/manifests/servers.manifest (Servers book,
 * Peer-to-Peer Networking node); Link Library rows print p2p.lib
 * (def/p2p-doc.def).  The only documented spelling is lowercase
 * p2p.h.  See docs/inventory.md M75d.
 */

#ifndef AKARI_P2P_H
#define AKARI_P2P_H

#include "Windef.h"    /* DWORD, ULONG, PVOID, PBYTE, PWSTR */
#include "Winsock2.h"  /* SOCKADDR_IN6 */
#include "Wincrypt.h"  /* HCRYPTPROV */

/* HPEERENUM: no CE page prints the typedef; used by the Peer*
 * signatures -- closed as HANDLE (QUEUEHANDLE policy).
 * SOCKADDR_IN6: the PEER_ADDRESS print spells the tag typedef that
 * Winsock2.h declares as struct sockaddr_in6 (aa450948) -- mechanical
 * tag closure. */
typedef HANDLE HPEERENUM;
typedef struct sockaddr_in6 SOCKADDR_IN6;

/* ms895901 "PEER_ADDRESS": print
 * `typedef struct peer_address_tag { DWORD dwSize; SOCKADDR_IN6
 * sin6;} PEER_ADDRESS, *PPEER_ADDRESS;` */
typedef struct peer_address_tag {
    DWORD       dwSize;
    SOCKADDR_IN6 sin6;
} PEER_ADDRESS, *PPEER_ADDRESS;

/* ms895902 "PEER_DATA": print
 * `typedef struct peer_data_tag { ULONG cbData; PBYTE pbData;}
 * PEER_DATA,*PPEER_DATA;` */
typedef struct peer_data_tag {
    ULONG cbData;
    PBYTE pbData;
} PEER_DATA, *PPEER_DATA;

/* ms895903 "PEER_NAME_PAIR" (title "PEER_NAME_PAIR_TAG"): print
 * `typedef struct peer_name_pair_tag { DWORD dwSize;
 * PWSTR pwzPeerName; PWSTR pwzFriendlyName;} PEER_NAME_PAIR,
 * *PPEER_NAME_PAIR;` */
typedef struct peer_name_pair_tag {
    DWORD dwSize;
    PWSTR pwzPeerName;
    PWSTR pwzFriendlyName;
} PEER_NAME_PAIR, *PPEER_NAME_PAIR;

/* ms895904 "PEER_RECORD_CHANGE_TYPE" (title
 * "PEER_RECORD_CHANGE_TYPE_TAG"): print
 * `typedef enum peer_record_change_type_tag{ PEER_RECORD_ADDED,
 * PEER_RECORD_UPDATED, PEER_RECORD_DELETED, PEER_RECORD_EXPIRED}
 * PEER_RECORD_CHANGE_TYPE;` -- sequential from 0 (C semantics). */
typedef enum peer_record_change_type_tag {
    PEER_RECORD_ADDED,
    PEER_RECORD_UPDATED,
    PEER_RECORD_DELETED,
    PEER_RECORD_EXPIRED
} PEER_RECORD_CHANGE_TYPE;

/* ms886712 "PEER_CONNECTION_FLAGS" (title
 * "PEER_CONNECTION_FLAGS_TAG"): print
 * `typedef enum peer_connection_flags_tag{ PEER_CONNECTION_NEIGHBOR,
 * PEER_CONNECTION_DIRECT} PEER_CONNECTION_FLAGS;` */
typedef enum peer_connection_flags_tag {
    PEER_CONNECTION_NEIGHBOR,
    PEER_CONNECTION_DIRECT
} PEER_CONNECTION_FLAGS;

/* --- Functions (p2p.lib -> def/p2p-doc.def). --------------------- */

/* ms895846 "PeerCreatePeerName" */
AKARI_CE_IMPORT HRESULT WINAPI PeerCreatePeerName(PCWSTR pwzIdentity, PCWSTR pwzClassifier,
                    PWSTR *ppwzPeerName)
                    AKARI_CE_NAME(PeerCreatePeerName);

/* ms895847 "PeerEndEnumeration" */
AKARI_CE_IMPORT HRESULT WINAPI PeerEndEnumeration(HPEERENUM hPeerEnum)
                    AKARI_CE_NAME(PeerEndEnumeration);

/* ms895849 "PeerEnumGroups" */
AKARI_CE_IMPORT HRESULT WINAPI PeerEnumGroups(PCWSTR pwzIdentity, HPEERENUM *phPeerEnum)
                    AKARI_CE_NAME(PeerEnumGroups);

/* ms895853 "PeerEnumIdentities" */
AKARI_CE_IMPORT HRESULT WINAPI PeerEnumIdentities(HPEERENUM *phPeerEnum)
                    AKARI_CE_NAME(PeerEnumIdentities);

/* ms895857 "PeerFreeData" */
AKARI_CE_IMPORT VOID WINAPI PeerFreeData(PVOID pvData) AKARI_CE_NAME(PeerFreeData);

/* ms895860 "PeerGetItemCount" */
AKARI_CE_IMPORT HRESULT WINAPI PeerGetItemCount(HPEERENUM hPeerEnum, PULONG pCount)
                    AKARI_CE_NAME(PeerGetItemCount);

/* ms895866 "PeerGetNextItem" */
AKARI_CE_IMPORT HRESULT WINAPI PeerGetNextItem(HPEERENUM hPeerEnum, PULONG pCount,
                    PVOID *ppvItems)
                    AKARI_CE_NAME(PeerGetNextItem);

/* ms895870 "PeerIdentityCreate" */
AKARI_CE_IMPORT HRESULT WINAPI PeerIdentityCreate(PCWSTR pwzClassifier, PCWSTR pwzFriendlyName,
                    HCRYPTPROV hCryptProv, PWSTR *ppwzIdentity)
                    AKARI_CE_NAME(PeerIdentityCreate);

/* ms895871 "PeerIdentityDelete" */
AKARI_CE_IMPORT HRESULT WINAPI PeerIdentityDelete(PCWSTR pwzIdentity)
                    AKARI_CE_NAME(PeerIdentityDelete);

/* ms895877 "PeerIdentityExport" */
AKARI_CE_IMPORT HRESULT WINAPI PeerIdentityExport(PCWSTR pwzIdentity, PCWSTR pwzPassword,
                    PCWSTR *ppwzExportXML)
                    AKARI_CE_NAME(PeerIdentityExport);

/* ms895881 "PeerIdentityGetCryptKey" */
AKARI_CE_IMPORT HRESULT WINAPI PeerIdentityGetCryptKey(PCWSTR pwzIdentity,
                    HCRYPTPROV *phCryptProv)
                    AKARI_CE_NAME(PeerIdentityGetCryptKey);

/* ms895884 "PeerIdentityGetFriendlyName" */
AKARI_CE_IMPORT HRESULT WINAPI PeerIdentityGetFriendlyName(PCWSTR pwzIdentity,
                    PWSTR *ppwzFriendlyName)
                    AKARI_CE_NAME(PeerIdentityGetFriendlyName);

/* ms895889 "PeerIdentityGetXML" */
AKARI_CE_IMPORT HRESULT WINAPI PeerIdentityGetXML(PCWSTR pwzIdentity,
                    PWSTR *ppwzIdentityXML)
                    AKARI_CE_NAME(PeerIdentityGetXML);

/* ms895893 "PeerIdentityImport" */
AKARI_CE_IMPORT HRESULT WINAPI PeerIdentityImport(PWSTR *ppwzImportXML,
                    PCWSTR pwzPassword, PCWSTR *ppwzIdentity)
                    AKARI_CE_NAME(PeerIdentityImport);

/* ms895895 "PeerIdentitySetFriendlyName" */
AKARI_CE_IMPORT HRESULT WINAPI PeerIdentitySetFriendlyName(PCWSTR pwzIdentity,
                    PCWSTR pwzFriendlyName)
                    AKARI_CE_NAME(PeerIdentitySetFriendlyName);

#endif /* AKARI_P2P_H */
