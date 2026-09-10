/* Voiperrorcodes.h -- VoIP Manager API result codes.
 *
 * Source pages: VOIP_E_ (ms912600, 13 constants) and VOIP_S_
 * (ms912605, 1 constant), both printing "Header: Voiperrorcodes.h"
 * with the values.  See docs/inventory.md M80.
 */

#ifndef AKARI_VOIPERRORCODES_H
#define AKARI_VOIPERRORCODES_H

/* ms912600 "VOIP_E_": error codes (values as printed). */
#define VOIP_E_ENUMOUTOFDATE                     0x80cc0000
#define VOIP_E_NOTINITIALIZED                    0x80cc0001
#define VOIP_E_RECORDNOTINDB                     0x80cc0002
#define VOIP_E_ALREADYINITIALIZED                0x80cc0003
#define VOIP_E_NODB                              0x80cc0004
#define VOIP_E_NOTCURRENTCALL                    0x80cc0005
#define VOIP_E_BUSY                              0x80cc0006
#define VOIP_E_NOACTIVECALL                      0x80cc0007
#define VOIP_E_TIMENOTSET                        0x80cc0008
#define VOIP_E_INVALIDCALLSTATUS                 0x80cc0009
#define VOIP_E_PROVISIONING_FAILED               0x80cc000b
#define VOIP_E_NOMEDIAMGR                        0x80cc000c
#define VOIP_E_TOOMANYCONFERENCEPARTICIPANTS     0x80cc000d

/* ms912605 "VOIP_S_": success codes. */
#define VOIP_S_DONT_TERMINATE              0x00040000

#endif /* AKARI_VOIPERRORCODES_H */
