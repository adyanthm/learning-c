#include "ezthreads.h"
#include <Windows.h>
#include <stdio.h>

void worker(void *arg){
    Sleep(2000);
    printf("worker: done\n");
}

int main(void){
    thread_t thread = thread_start(worker, NULL);
    printf("main: waiting...\n");
    thread_join(thread);
    printf("main: resumed\n");
    return 0;
}
