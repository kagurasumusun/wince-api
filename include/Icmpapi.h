/* Icmpapi.h -- ICMP API (Windows CE .NET 4.1+; Icmplib.lib).
 * See docs/inventory.md M77b. */

#ifndef AKARI_ICMPAPI_H
#define AKARI_ICMPAPI_H

#include "Windef.h"    /* DWORD, WORD, HANDLE, VOID, LPVOID */

/* "IP_OPTION_INFORMATION": print `typedef struct
 * IP_OPTION_INFORMATION {unsigned char Ttl;unsigned char Tos;
 * unsigned char Flags;unsigned char OptionsSize;
 * unsigned char FAR* OptionsData;} IP_OPTION_INFORMATION;`
 * (FAR is empty on CE). */
typedef struct IP_OPTION_INFORMATION {
    unsigned char  Ttl;
    unsigned char  Tos;
    unsigned char  Flags;
    unsigned char  OptionsSize;
    unsigned char *OptionsData;
} IP_OPTION_INFORMATION, *PIP_OPTION_INFORMATION;

/* IcmpCreateFile: print `HANDLEWINAPI IcmpCreateFile(VOID);` */
AKARI_CE_IMPORT HANDLE WINAPI IcmpCreateFile(VOID)
                    AKARI_CE_NAME(IcmpCreateFile);

/* IcmpCloseHandle: print `BOOLWINAPI IcmpCloseHandle(HANDLEIcmpHandle);` */
AKARI_CE_IMPORT BOOL WINAPI IcmpCloseHandle(HANDLE IcmpHandle)
                    AKARI_CE_NAME(IcmpCloseHandle);

/* IcmpParseReplies: print
 * `DWORD IcmpParseReplies(LPVOIDReplyBuffer,DWORDReplySize);` */
AKARI_CE_IMPORT DWORD IcmpParseReplies(LPVOID ReplyBuffer,
                    DWORD ReplySize) AKARI_CE_NAME(IcmpParseReplies);

/* Icmp6CreateFile: print `HANDLE WINAPI Icmp6CreateFile(VOID);` */
AKARI_CE_IMPORT HANDLE WINAPI Icmp6CreateFile(VOID)
                    AKARI_CE_NAME(Icmp6CreateFile);

/* Icmp6ParseReplies: print
 * `DWORD Icmp6ParseReplies(LPVOID ReplyBuffer,DWORD ReplySize);` */
AKARI_CE_IMPORT DWORD Icmp6ParseReplies(LPVOID ReplyBuffer,
                    DWORD ReplySize) AKARI_CE_NAME(Icmp6ParseReplies);

/* --- Record-only. ------------------------------------------------
 * IcmpSendEcho: `DWORDWINAPI IcmpSendEcho(HANDLE IcmpHandle,
 * IPAddr DestinationAddress,LPVOID RequestData,WORD RequestSize,
 * PIP_OPTION_INFORMATION RequestOptions,LPVOID ReplyBuffer,
 * DWORD ReplySize,DWORD Timeout);` -- IPAddr unpublished (Iphlpapi.h
 * M77a hold list).
 * Icmp6SendEcho2: print embeds #ifdef PIO_APC_ROUTINE_DEFINED
 * blocks -- verbatim on the page (ms890357).
 * ICMP_ECHO_REPLY (ms890360): the page prints no structure --
 * members are described in prose only (Address is IPAddr). */

#endif /* AKARI_ICMPAPI_H */
