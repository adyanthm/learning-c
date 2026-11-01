#define MAX_MSG (100 * 1024)
#include "ezsocks.h"
#include "ezthreads.h"
#include <stdio.h>
#include <winsock2.h>
#define PORT 8080

static void receiver(void *arg){
    SOCKET s = (SOCKET)(UINT_PTR)arg;
    static char msg[MAX_MSG];

    while (recv_msg(s, msg, sizeof(msg)) > 0){
        printf("\rServer: %s\n>>> ", msg);   // \r returns to line start, overwriting ">>> "
        fflush(stdout);
    }

    printf("\nDisconnected.\n");
}

int main(void){
    if(sock_init()){
        fprintf(stderr, "WSAStartup failed\n");
        return 1;
    }

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

    thread_t recv_worker = thread_start(receiver, (void *)(UINT_PTR)client);
    if (recv_worker == NULL){
        fprintf(stderr, "Failed to start receiver thread\n");
        sock_close(client);
        sock_cleanup();
        return 1;
    }

    static char msg[MAX_MSG];
    while (1){
        printf(">>> ");
        fflush(stdout);
        if (!fgets(msg, sizeof(msg), stdin)) break;
        msg[strcspn(msg, "\r\n")] = '\0';
        if (msg[0] == '\0') continue;      ;
        if (strcmp(msg, "quit") == 0)
            break;
        if (send_msg(client, msg) < 0){
            fprintf(stderr, "Send Failed\n");
            break;
        }
        printf("\x1b[1A\r\x1b[KYou: %s\n", msg);   // up one line, clear it, rewrite
        fflush(stdout);
    }

    sock_close(client);
    sock_close(server);
    thread_join(recv_worker);
    sock_cleanup();
    return 0;
}
