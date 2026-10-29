#include <stdlib.h>
#include "ezthreads.h"

typedef struct {
    void (*fn) (void *);
    void *arg;
} thread_ctx;

static DWORD WINAPI redirector(LPVOID p){
    thread_ctx ctx = *(thread_ctx *)p;
    free(p);
    ctx.fn(ctx.arg);
    return 0;
}

// Start the worker.
thread_t thread_start(void (*fn)(void *), void *arg) {
    thread_ctx *ctx = malloc(sizeof(thread_ctx));
    if (ctx == NULL){
        return NULL;
    }
    ctx->fn = fn;
    ctx->arg = arg;

    /********************************************************************************
     * Syntax for CreateThread() used below.                                        *
     *                                                                              *
     * HANDLE CreateThread(                                                         *
     *    LPSECURITY_ATTRIBUTES   lpThreadAttributes,  // security options          *
     *    SIZE_T                  dwStackSize,         // stack size in bytes       *
     *    LPTHREAD_START_ROUTINE  lpStartAddress,      // the function to run       *
     *    LPVOID                  lpParameter,         // argument passed to it     *
     *    DWORD                   dwCreationFlags,     // when to start             *
     *    LPDWORD                 lpThreadId           // receives the thread's ID  *
     * );                                                                           *
     *                                                                              *
     *******************************************************************************/

    thread_t thread = CreateThread(NULL, 0, redirector, ctx, 0, NULL);
    if (thread == NULL){
        free(ctx);
        return NULL;
    }
    return thread;
}

/********************************************************************************************
 * Freeze mains thread until the worker is done after which the main thread resumes again.  *
 * Used in stuff where we want to proceed AFTER the helper is finished.                     *
 * Example: Finish all jobs before returning.                                               *
 *******************************************************************************************/
void thread_join(thread_t thread){
    if (thread == NULL) return;
    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
}

/************************************************************************************
 * the thread keeps running and terminates on its own but we "detach" its handle.   *
 * (i.e) We do not care about what happens to it.                                   *
 * Example: Fire and forget jobs like receive data from network or stuff.           *
 ***********************************************************************************/

void thread_detach(thread_t thread){
    if (thread != NULL)
        CloseHandle(thread);
}
