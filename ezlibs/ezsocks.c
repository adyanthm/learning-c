#include "ezsocks.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <winsock2.h>

int sock_init(void){
    WSADATA wsa;
    return WSAStartup(MAKEWORD(2, 2), &wsa);
}

void sock_cleanup(void){
    WSACleanup();
}

void sock_close(SOCKET sock){
    if (sock != INVALID_SOCKET)
        closesocket(sock);
}

SOCKET start_server_adv(const char *ip, unsigned short port, int family, int type, int protocol, int backlog){
    SOCKET server = socket(family, type, protocol);
    if (server == INVALID_SOCKET)
        return INVALID_SOCKET;

    /*
     * We do not want to do SO_REUSEADDR on windows like in linux because it can allow other processes
     * to steal our ports. This can lead to SEVERE Man-In-The-Middle attack vulnerabilities.
     * Hence we use `SO_EXCLUSIVEADDRUSE` instead.
     */
    BOOL yes = TRUE;
    setsockopt(server, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (const char *)&yes, sizeof(yes));

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
    else if (family == AF_INET6){
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
    return start_server_adv(ip, (unsigned short)port, AF_INET, SOCK_STREAM, IPPROTO_TCP, SOMAXCONN);
}

SOCKET sock_accept(SOCKET server){
    return accept(server, NULL, NULL);
}

SOCKET sock_connect(const char *host, unsigned short port){
    char portstr[8];
    snprintf(portstr, sizeof(portstr), "%u", port);

    struct addrinfo hints = {0}, *res = NULL, *p;
    hints.ai_family   = AF_UNSPEC;      /* IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if (getaddrinfo(host, portstr, &hints, &res) != 0)
        return INVALID_SOCKET;

    SOCKET s = INVALID_SOCKET;
    for (p = res; p != NULL; p = p->ai_next){   /* try each address until one works */
        s = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (s == INVALID_SOCKET)
            continue;
        if (connect(s, p->ai_addr, (int)p->ai_addrlen) == 0)
            break;
        closesocket(s);
        s = INVALID_SOCKET;
    }

    freeaddrinfo(res);
    return s;
}

int sendall(SOCKET sock, const char *buf, int len){
    int total = 0;
    while (total < len){
        int n = send(sock, buf + total, len - total, 0);
        if (n <= 0) return n; // n = 0 means connection closed. n = -1 means socketerror.
        total += n;
    }
    return total;
}

int recvall(SOCKET sock, char *buf, int len){
    int total = 0;
    while (total < len){
        int n = recv(sock, buf + total, len - total, 0);
        if (n <= 0) return n; // n = 0 means connection closed. n = -1 means socketerror.
        total += n;
    }
    return total;
}

int send_str(SOCKET sock, const char *str){
    return sendall(sock, str, (int)strlen(str));
}

int recv_str(SOCKET sock, char *buf, int size){
    if (size <= 0) return SOCKET_ERROR;
    int n = recv(sock, buf, size - 1, 0);
    if (n >= 0) buf[n] = '\0';
    return n;
}

int send_msg(SOCKET s, const char *msg){
    size_t n = strlen(msg);
    if (n == 0 || n > MAX_MSG) return SOCKET_ERROR;

    uint32_t len = htonl((uint32_t)n);
    if (sendall(s, (const char *)&len, 4) != 4)
        return SOCKET_ERROR;

    return sendall(s, msg, (int)n);
}

int recv_msg(SOCKET s, char *buf, int size){
    uint32_t len;
    int r = recvall(s, (char *)&len, 4);
    if (r < 4) return r;

    len = ntohl(len);
    if (size <= 0 || len == 0 || len > MAX_MSG || len >= (uint32_t)size)
        return SOCKET_ERROR;

    if (recvall(s, buf, (int)len) != (int)len)
        return SOCKET_ERROR; // failed

    buf[len] = '\0';
    return (int)len;
}
