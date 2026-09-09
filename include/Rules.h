/* Rules.h -- firewall rule masks (Windows CE; companion of Fwapi.h).
 * FW_RULE_MASKS page print carries one missing comma (after
 * FWM_PROTOCOL = 0x20) -- repaired, noted.  See docs/inventory.md M77c. */

#ifndef AKARI_RULES_H
#define AKARI_RULES_H

/* "FW_RULE_MASKS": print (explicit values; repaired comma). */
typedef enum _FW_RULE_MASKS {
    FWM_PRIVATE_HOST = 0x01,
    FWM_PUBLIC_HOST = 0x02,
    FWM_PORT = 0x04,
    FWM_TYPE = 0x08,
    FWM_CODE = 0x10,
    FWM_PROTOCOL = 0x20,
    FWM_ACTION = 0x40,
    FWM_TIME_OF_DAY = 0x80,
    FWM_DAY_OF_WEEK = 0x100,
    FWM_DAY = 0x200,
    FWM_MONTH = 0x400,
    FWM_PUBLIC_HOST_MASK = 0x800,
    FWM_PUBLIC_HOST_PREFIX = 0x1000
} FW_RULE_MASKS;

#endif /* AKARI_RULES_H */
