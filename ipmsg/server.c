#include "ezsocks.h"
#include <stdio.h>
#include <winsock2.h>
#define PORT 8080

int main(void){
    char buffer[4096];

    if(sock_init()){
        fprintf(stderr, "WSAStartup failed\n");
        return 1;
    };

    SOCKET server = start_server("127.0.0.1", PORT);
    if (server == INVALID_SOCKET) {
        fprintf(stderr, "Server creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    SOCKET client = accept(server, NULL, NULL);
    if (client == INVALID_SOCKET) {
        fprintf(stderr, "accept client failed: %d\n", WSAGetLastError());
        closesocket(server);
        WSACleanup();
        return 1;
    }

    printf("Client connected!\n");

    int n;
    while ((n = recv(client, buffer, sizeof(buffer), 0)) > 0){
        if(sendall(client, buffer, n) == SOCKET_ERROR)
            break;
    }

    printf("Received: %s", buffer);

    closesocket(server);
    closesocket(client);
    WSACleanup();

    return 0;
}
