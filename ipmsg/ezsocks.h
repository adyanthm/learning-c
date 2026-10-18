#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <winsock2.h>
#include <ws2tcpip.h>

int sock_init(void);
SOCKET start_server_adv(const char *ip, unsigned short port, int family, int type, int protocol, int backlog);
SOCKET start_server(const char *ip, int port);
int sendall(SOCKET sock, const char *buf, int len);
