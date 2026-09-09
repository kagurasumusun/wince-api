/* Fwapi.h -- IPv4/IPv6 firewall API (Windows CE .NET 4.1+).
 * Pages: tools/manifests/netgen.manifest; Fwapi.lib rows on 5
 * functions (def/fwapi-doc.def); the log/refresh helpers print no
 * Link Library row.  HRULE is not published on any CE page --
 * FW_RULE and the HRULE-taking functions are recorded verbatim.
 * See docs/inventory.md M77c.
 */

#ifndef AKARI_FWAPI_H
#define AKARI_FWAPI_H

#include "Windef.h"    /* DWORD, BOOL, UINT, INT, WORD, UCHAR,
                        * USHORT, ULONG, LPCWSTR */
#include "Winsock2.h"  /* IN_ADDR, struct in6_addr */

/* IN6_ADDR closure: FW_IP_ADDRESS print (Winsock2.h declares the
 * struct in6_addr and the IN_ADDR tag typedef; IN6_ADDR is the
 * same mechanical tag closure). */
typedef struct in6_addr IN6_ADDR;

/* "FW_IP_ADDRESS": print `typedef struct _FW_IP_ADDRESS {
 * USHORT Family; union { IN6_ADDR AddressIPv6; IN_ADDR AddressIPv4;
 * }; ...` */
typedef struct _FW_IP_ADDRESS {
    USHORT Family;
    union {
        IN6_ADDR AddressIPv6;
        IN_ADDR  AddressIPv4;
    };
} FW_IP_ADDRESS;

/* "FW_ACTIONS": print (explicit values). */
typedef enum _FW_ACTIONS {
    FWA_BLOCK = 0x01,
    FWA_ALLOW = 0x02,
    FWA_ALLOW_RESPONSE = 0x03,
} FW_ACTIONS;

/* "FW_DAYS": print (explicit values). */
typedef enum _FW_DAYS {
    FWD_SUNDAY = 0x01,
    FWD_MONDAY = 0x02,
    FWD_TUESDAY = 0x04,
    FWD_WEDNESDAY = 0x08,
    FWD_THURSDAY = 0x10,
    FWD_FRIDAY = 0x20,
    FWD_SATURDAY = 0x40,
    FWD_WEEKDAY = 0x3E,
    FWD_WEEKEND = 0x41,
} FW_DAYS;

/* "FW_DIRECTIONS": print (explicit values). */
typedef enum _FW_DIRECTIONS {
    FWD_INBOUND = 0x08,
    FWD_OUTBOUND = 0x10,
} FW_DIRECTIONS;

/* "FW_RULE_FLAGS": print (value aliases of FW_ACTIONS/FW_DIRECTIONS). */
typedef enum _FW_RULE_FLAGS {
    FWF_BLOCK = FWA_BLOCK,
    FWF_ALLOW = FWA_ALLOW,
    FWF_LOG = 0x04,
    FWF_INBOUND = FWD_INBOUND,
    FWF_OUTBOUND = FWD_OUTBOUND,
    FWF_DISABLED = 0x20
} FW_RULE_FLAGS;

/* "FW_LOG_ENTRY": print; the lowercase member tokens ushort/uchar/
 * ulong are the page rendering of USHORT/UCHAR/ULONG (Natedit.h
 * ms885685 precedent, noted per member). */
typedef struct _FIREWALL_LOG_ENTRY {
    FW_IP_ADDRESS PrivateHost;
    FW_IP_ADDRESS PublicHost;
    INT           Protocol;
    FW_ACTIONS    Action;
    FW_DIRECTIONS Direction;
    union {
        struct {
            USHORT tcp_src;
            USHORT tcp_dest;
            INT    tcp_seq;
            INT    tcp_ack;
            USHORT tcp_flags;
            USHORT tcp_window;
            USHORT tcp_xsum;
            USHORT tcp_urgent;
        } TCPHeader;
        struct {
            USHORT Source;
            USHORT Dest;
            USHORT Length;
            USHORT Checksum;
        } UDPHeader;
        struct {
            UCHAR  ich_type;
            UCHAR  ich_code;
            USHORT ich_xsum;
            ULONG  ich_param;
        } ICMPHeader;
        struct {
            UCHAR  Type;
            UCHAR  Code;
            USHORT Checksum;
        } ICMPv6Header;
    };
} FW_LOG_ENTRY, *PFW_LOG_ENTRY;

/* --- Record-only. -----------------------------------------------
 * FW_RULE: `typedef struct _FIREWALL_RULE{ DWORD dwSize; HRULE hRule; DWORD dwFlags; DWORD dwMask; LPCWSTR wszDescription; FW_IP_ADDRESS PrivateHost; FW_IP_ADDRESS PublicHost; union { UINT PublicHostPrefixLength; IN_ADDR PublicHostMask; }; INT Protocol; FW_ACTIONS Action; WORD wHourStart, wHourEnd; WORD wDayOfWeek; WORD wDay; WORD wMonth; union { { USHORT PortMin; USHORT PortMax; }; struct { UCHAR Type; UCHAR Code; }; };}FW_RULE, *PFW__RULE;`
 * -- embeds the unpublished HRULE; pointer typedef below (the
 * print spells the pointer name *PFW__RULE -- doc typo, closed as
 * PFW_RULE). */
typedef struct _FIREWALL_RULE FW_RULE, *PFW_RULE;

/* --- Functions. ------------------------------------------------- */

/* "FirewallCreateRule" (Fwapi.lib): print `DWORD FirewallCreateRule(
 * FW_RULE* pRule, BOOL bPersist);` */
AKARI_CE_IMPORT DWORD FirewallCreateRule(FW_RULE *pRule, BOOL bPersist)
                    AKARI_CE_NAME(FirewallCreateRule);

/* "FirewallEnable" (Fwapi.lib): print `DWORD FirewallEnable(
 * USHORT Family, BOOL bEnable, BOOL bPersist);` */
AKARI_CE_IMPORT DWORD FirewallEnable(USHORT Family, BOOL bEnable,
                    BOOL bPersist) AKARI_CE_NAME(FirewallEnable);

/* FirewallLogInit / FirewallLogUninit / FirewallRefresh (no Link
 * Library row): prints `void FirewallLogInit();`,
 * `void FirewallLogUninit();`, `VOID FirewallRefresh();` */
AKARI_CE_IMPORT void FirewallLogInit(void) AKARI_CE_NAME(FirewallLogInit);
AKARI_CE_IMPORT void FirewallLogUninit(void)
                    AKARI_CE_NAME(FirewallLogUninit);
AKARI_CE_IMPORT VOID FirewallRefresh(void) AKARI_CE_NAME(FirewallRefresh);

/* FirewallLogPacket (no Link Library row): print
 * `void FirewallLogPacket ( const FW_LOG_ENTRY* pLogEntry);` */
AKARI_CE_IMPORT void FirewallLogPacket(const FW_LOG_ENTRY *pLogEntry)
                    AKARI_CE_NAME(FirewallLogPacket);

/* FirewallSetInterface (no Link Library row): print
 * `DWORD FirewallSetInterface( LPCWSTR pszInterfaceName,
 * BOOL bFirewalled, BOOL bPersist);` */
AKARI_CE_IMPORT DWORD FirewallSetInterface(
                    LPCWSTR pszInterfaceName, BOOL bFirewalled,
                    BOOL bPersist) AKARI_CE_NAME(FirewallSetInterface);

/* IsFirewallEnabled / IsInterfaceFirewalled (no Link Library rows):
 * prints `BOOL IsFirewallEnabled( USHORT Family);`,
 * `BOOL IsInterfaceFirewalled( LPCWSTR pszInterfaceName);` */
AKARI_CE_IMPORT BOOL IsFirewallEnabled(USHORT Family)
                    AKARI_CE_NAME(IsFirewallEnabled);
AKARI_CE_IMPORT BOOL IsInterfaceFirewalled(LPCWSTR pszInterfaceName)
                    AKARI_CE_NAME(IsInterfaceFirewalled);

/* --- Recorded only (HRULE unpublished / broken print). ----------
 * FirewallDeleteRule: `DWORD FirewallDeleteRule( HRULE hRule,
 * BOOL bPersist);`
 * FirewallEnableRule: `DWORD FirewallEnableRule( HRULE hRule,
 * BOOL bEnabled, BOOL bPersist);`
 * FirewallGetRules: `DWORD FirewallGetRules( PFW RULE pRules,
 * DWORD* pdwSize, DWORD* pdwCount);` (print breaks PFW_RULE into
 * two tokens). */

#endif /* AKARI_FWAPI_H */
