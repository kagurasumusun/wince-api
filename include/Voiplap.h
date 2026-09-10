/* Voiplap.h -- PC Authentication LAP (Local Authentication Provider).
 *
 * Source pages: PC Authentication book rows printing "Header:
 * Voiplap.h" (5 pages): AttemptConnection (ms909303),
 * GetPCSyncName (ms909307), SetPCSyncName (ms912594), and the
 * VOIPLAP_E_ / VOIPLAP_S_ constant tables (ms912601 / ms912602,
 * values as printed).  The pages print no Link Library row.
 * See docs/inventory.md M80.
 */

#ifndef AKARI_VOIPLAP_H
#define AKARI_VOIPLAP_H

#include "Windef.h"    /* DWORD, WCHAR, INT */
#include "Objbase.h"   /* HRESULT (Objbase.h ms-closure, M44) */

/* --- Constants (tables print the values). ----------------------- */
/* ms912601 "VOIPLAP_E_": failure codes (decimal values as printed). */
#define VOIPLAP_E_NOSERVER                   6001
#define VOIPLAP_E_NOCREDENTIALS              6002
#define VOIPLAP_E_CANTCONNECT                6003
#define VOIPLAP_E_CANTAUTHENTICATESERVER     6004
#define VOIPLAP_E_TRANSMISSIONFAILED         6005
#define VOIPLAP_E_TIMEOUT                    6006
#define VOIPLAP_E_INVALIDDATA                6007
#define VOIPLAP_E_BUSY                       6008

/* ms912602 "VOIPLAP_S_": success codes. */
#define VOIPLAP_S_PCUNLOCKED               0
#define VOIPLAP_S_PCLOCKED                 1

/* --- Functions (no Link Library row). --------------------------- */
/* ms909303 "AttemptConnection": print `DWORD AttemptConnection();`
 * (empty parens -> void). */
AKARI_CE_IMPORT DWORD AttemptConnection(void)
                    AKARI_CE_NAME(AttemptConnection);

/* ms909307 "GetPCSyncName": print
 * `HRESULT GetPCSyncName(WCHAR* wszNameBuffer,INT cchNameBuffer);`. */
AKARI_CE_IMPORT HRESULT GetPCSyncName(WCHAR *wszNameBuffer,
                    INT cchNameBuffer) AKARI_CE_NAME(GetPCSyncName);

/* ms912594 "SetPCSyncName": print
 * `HRESULT SetPCSyncName(const WCHAR* c_wszPCName);`. */
AKARI_CE_IMPORT HRESULT SetPCSyncName(const WCHAR *c_wszPCName)
                    AKARI_CE_NAME(SetPCSyncName);

#endif /* AKARI_VOIPLAP_H */
