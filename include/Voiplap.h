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

/* ------------------------------------------------------------------
 * Book surface: pcauth (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa525624 Determining PC Lock Status by Calling the LAP Directly */
/* aa525625 Determining PC Lock Status Using LASS */
/* aa525645 Learning More About PC Authentication */
/* aa525657 PC Authentication and IPsec */
/* ms912608 PC Authentication Application Development */
/* aa525655 PC Authentication Architecture */
/* ms931941 PC Authentication Constants */
/* ms931942 PC Authentication Functions */
/* aa525656 PC Authentication LAP Implementation */
/* aa525658 PC Authentication Migration */
/* aa525659 PC Authentication OS Design Development */
/* ms931943 PC Authentication Reference */
/* aa525660 PC Authentication Registry Settings */
/* aa525661 PC Authentication Samples */
/* aa525662 PC Authentication Security */
/* ms909235 Setting Up PC Authentication */
/* ms909236 Setting up the PC Authentication LAP on a Windows CE Device */
/* ms909237 Setting up the PC Authentication PC Application */
/* ------------------------------------------------------------------
 * Book surface: pcauth (tools/gen-book.py; page ids per record)
 * ------------------------------------------------------------------ */
/* aa525624 Determining PC Lock Status by Calling the LAP Directly */
/* aa525625 Determining PC Lock Status Using LASS */
/* aa525645 Learning More About PC Authentication */
/* aa525657 PC Authentication and IPsec */
/* ms912608 PC Authentication Application Development */
/* aa525655 PC Authentication Architecture */
/* ms931941 PC Authentication Constants */
/* ms931942 PC Authentication Functions */
/* aa525656 PC Authentication LAP Implementation */
/* aa525658 PC Authentication Migration */
/* aa525659 PC Authentication OS Design Development */
/* ms931943 PC Authentication Reference */
/* aa525660 PC Authentication Registry Settings */
/* aa525661 PC Authentication Samples */
/* aa525662 PC Authentication Security */
/* ms909235 Setting Up PC Authentication */
/* ms909236 Setting up the PC Authentication LAP on a Windows CE Device */
/* ms909237 Setting up the PC Authentication PC Application */
#endif /* AKARI_VOIPLAP_H */
