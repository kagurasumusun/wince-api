/*
 * wince-api: Clean-room Windows CE API implementation for LLVM/Clang
 * File: winsock2.h
 *
 * Windows CE Winsock 2 Networking API definitions.
 */

#ifndef _WINSOCK2_H_
#define _WINSOCK2_H_

#include <windows.h>
#include <ws2def.h>

#ifdef __cplusplus
extern "C" {
#endif

#define WSADESCRIPTION_LEN      256
#define WSASYS_STATUS_LEN       128

typedef struct WSAData {
    WORD                    wVersion;
    WORD                    wHighVersion;
    char                    szDescription[WSADESCRIPTION_LEN+1];
    char                    szSystemStatus[WSASYS_STATUS_LEN+1];
    unsigned short          iMaxSockets;
    unsigned short          iMaxUdpDg;
    char                    *lpVendorInfo;
} WSADATA, *LPWSADATA;

int WINAPI WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData);
int WINAPI WSACleanup(void);
int WINAPI WSAGetLastError(void);

SOCKET WINAPI socket(int af, int type, int protocol);
int WINAPI closesocket(SOCKET s);
int WINAPI bind(SOCKET s, const struct sockaddr *name, int namelen);
int WINAPI listen(SOCKET s, int backlog);
SOCKET WINAPI accept(SOCKET s, struct sockaddr *addr, int *addrlen);
int WINAPI connect(SOCKET s, const struct sockaddr *name, int namelen);
int WINAPI send(SOCKET s, const char *buf, int len, int flags);
int WINAPI recv(SOCKET s, char *buf, int len, int flags);

u_short WINAPI htons(u_short hostshort);
u_long  WINAPI htonl(u_long hostlong);
u_short WINAPI ntohs(u_short netshort);
u_long  WINAPI ntohl(u_long netlong);

#ifdef __cplusplus
}
#endif

#endif /* _WINSOCK2_H_ */
