/*
 * wince-api: Clean-room Windows CE API implementation for LLVM/Clang
 * File: ws2def.h
 *
 * Winsock 2 basic data definitions.
 */

#ifndef _WS2DEF_H_
#define _WS2DEF_H_

#include <sdkddkver.h>
#include <windef.h>
#include <winnt.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned short u_short;
typedef unsigned long  u_long;
typedef unsigned char  u_char;
typedef unsigned int   u_int;

typedef UINT_PTR SOCKET;

#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR    (-1)

#define AF_UNSPEC       0
#define AF_INET         2
#define AF_INET6        23

#define SOCK_STREAM     1
#define SOCK_DGRAM      2
#define SOCK_RAW        3

#define IPPROTO_TCP     6
#define IPPROTO_UDP     17

typedef struct in_addr {
    union {
        struct { UCHAR s_b1, s_b2, s_b3, s_b4; } S_un_b;
        struct { USHORT s_w1, s_w2; } S_un_w;
        ULONG S_addr;
    } S_un;
#define s_addr S_un.S_addr
} IN_ADDR, *PIN_ADDR, *LPIN_ADDR;

typedef struct sockaddr_in {
    short          sin_family;
    USHORT         sin_port;
    IN_ADDR        sin_addr;
    char           sin_zero[8];
} SOCKADDR_IN, *PSOCKADDR_IN, *LPSOCKADDR_IN;

typedef struct sockaddr {
    USHORT         sa_family;
    char           sa_data[14];
} SOCKADDR, *PSOCKADDR, *LPSOCKADDR;

#ifdef __cplusplus
}
#endif

#endif /* _WS2DEF_H_ */
