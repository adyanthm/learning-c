#ifndef EZSOCKS_H
#define EZSOCKS_H

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
int send_str(SOCKET sock, const char *str);
int recv_str(SOCKET sock, char *buf, int size);  /* NUL-terminates; returns bytes, 0 = closed, SOCKET_ERROR = error */
void sock_close(SOCKET sock);

#endif
