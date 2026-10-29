#include "ezsocks.h"
#include <stdio.h>

int main(void){
    if (sock_init()) return 1;

    SOCKET s = sock_connect("127.0.0.1", 8080);
    if (s == INVALID_SOCKET){
        fprintf(stderr, "Connection failed: %d\n", WSAGetLastError());
        sock_cleanup();
        return 1;
    }

    send_str(s, "Hello from client");

    char buf[4096];
    if (recv_str(s, buf, sizeof(buf)) > 0)
        printf("Server replied: %s\n", buf);

    sock_close(s);
    sock_cleanup();
    return 0;
}
