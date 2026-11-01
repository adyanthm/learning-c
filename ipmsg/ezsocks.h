#ifndef EZSOCKS_H
#define EZSOCKS_H

#ifndef MAX_MSG
#define MAX_MSG (4 * 1024 * 1024) /* Default 4 MB limit */
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <winsock2.h>
#include <ws2tcpip.h>

int sock_init(void);                 /* 0 on success */
void sock_cleanup(void);

SOCKET start_server_adv(const char *ip, unsigned short port, int family, int type, int protocol, int backlog);
SOCKET start_server(const char *ip, int port);

SOCKET sock_accept(SOCKET server);
SOCKET sock_connect(const char *host, unsigned short port);

int sendall(SOCKET sock, const char *buf, int len);
int recvall(SOCKET sock, char *buf, int len);

int send_str(SOCKET sock, const char *str);
int recv_str(SOCKET sock, char *buf, int size);  /* NUL-terminates; returns bytes, 0 = closed, SOCKET_ERROR = error */

int send_msg(SOCKET s, const char *msg); /* Sends a message beginning with 4 byte header having its length. Format: [4 Byte Len][msg] and returns length received or error (-1 / 0) */
int recv_msg(SOCKET s, char *buf, int size); /* Receives a message beginning with 4 byte header having its length. Format: [4 Byte Len][msg] and returns length received or error (-1 / 0) */

void sock_close(SOCKET sock);

#endif
