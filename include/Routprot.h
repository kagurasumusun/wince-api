/* Routprot.h -- routing protocol interface (Windows CE, Networking -
 * General harvest).  MIB_BEST_IF print carries the typedef-name
 * placement `} MIB_BEST_IF*, PMIB_BEST_IF;` (doc typo for
 * `MIB_BEST_IF, *PMIB_BEST_IF`).  See docs/inventory.md M77c. */

#ifndef AKARI_ROUTPROT_H
#define AKARI_ROUTPROT_H

#include "Windef.h"    /* DWORD */

/* "MIB_BEST_IF": print `typedef struct _MIB_BEST_IF {DWORDdwDestAddr;
 * DWORDdwIfIndex;} MIB_BEST_IF*, PMIB_BEST_IF;` */
typedef struct _MIB_BEST_IF {
    DWORD dwDestAddr;
    DWORD dwIfIndex;
} MIB_BEST_IF, *PMIB_BEST_IF;

#endif /* AKARI_ROUTPROT_H */
