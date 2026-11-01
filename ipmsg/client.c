#define MAX_MSG (100 * 1024)
#include "ezsocks.h"
#include "ezthreads.h"
#include <stdio.h>
#include <string.h>

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
    if (sock_init()) return 1;

    SOCKET s = sock_connect("127.0.0.1", 8080);
    if (s == INVALID_SOCKET){
        fprintf(stderr, "Connection failed: %d\n", WSAGetLastError());
        sock_cleanup();
        return 1;
    }

    thread_t recv_worker = thread_start(receiver, (void *)(UINT_PTR)s);
    if (recv_worker == NULL){
        fprintf(stderr, "Failed to start receiver thread\n");
        sock_close(s);
        sock_cleanup();
        return 1;
    }

    static char msg[MAX_MSG];
    while (1){
        printf(">>> ");
        fflush(stdout);
        if (!fgets(msg, sizeof(msg), stdin)) break;
        msg[strcspn(msg, "\r\n")] = '\0';
        if (msg[0] == '\0') continue;
        if (strcmp(msg, "quit") == 0)
            break;
        if (send_msg(s, msg) < 0){
            fprintf(stderr, "Send Failed\n");
            break;
        }
        printf("\x1b[1A\r\x1b[KYou: %s\n", msg);   // up one line, clear it, rewrite
        fflush(stdout);
    }

    sock_close(s);
    thread_join(recv_worker);
    sock_cleanup();
    return 0;
}
