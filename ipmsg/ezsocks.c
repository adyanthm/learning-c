#include "ezsocks.h"
#include <winsock2.h>

int sock_init(void){
    WSADATA wsa;
    return WSAStartup(MAKEWORD(2, 2), &wsa);
}

SOCKET start_server_adv(const char *ip, unsigned short port, int family, int type, int protocol, int backlog){
    SOCKET server = socket(family, type, protocol);
    if (server == INVALID_SOCKET){
        return INVALID_SOCKET;
    }
    if (family == AF_INET){
        struct sockaddr_in addr = {0};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);

        if (ip == NULL)
            addr.sin_addr.s_addr = htonl(INADDR_ANY);
        else if (InetPtonA(AF_INET, ip, &addr.sin_addr) != 1)
            goto fail;

        if (bind(server, (struct sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR)
            goto fail;
    }
    else if (family == AF_INET6) {
        struct sockaddr_in6 addr = {0};
        addr.sin6_family = AF_INET6;
        addr.sin6_port = htons(port);

        if (ip == NULL)
            addr.sin6_addr = in6addr_any;
        else if (InetPtonA(AF_INET6, ip, &addr.sin6_addr) != 1)
            goto fail;

        if (bind(server, (struct sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR)
            goto fail;
    }
    else {
        goto fail;
    }

    if (type == SOCK_STREAM && listen(server, backlog) == SOCKET_ERROR)
        goto fail;

    return server;

fail:
    closesocket(server);
    return INVALID_SOCKET;
}

SOCKET start_server(const char *ip, int port){
    if (port < 0 || port > 65535)
        return INVALID_SOCKET;
    return start_server_adv(ip, port, AF_INET, SOCK_STREAM, IPPROTO_TCP, SOMAXCONN);
}

int sendall(SOCKET sock, const char *buf, int len){
    int total = 0;
    while (total < len){
        int n = send(sock, buf + total, len - total, 0); // send() returns number of successfuly sent bytes.
        if (n == SOCKET_ERROR || n == 0) return SOCKET_ERROR;
        total += n;
    }
    return total;
}
