/*
 * Define EZTHREADS_IMPLEMENTATION in ONE source file before including
 * this header to compile the implementation directly into that file.
 *
 * This allows ezsocks to be used as a single-header library,
 * without separately compiling ezsocks.c.
 *
 * I tried to make something like an STB lib :)
 */

#ifndef EZTHREADS_H
#define EZTHREADS_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

typedef HANDLE thread_t;

/* Runs fn(arg) in a new thread. Returns NULL on failure. */
thread_t thread_start(void (*fn)(void *), void *arg);

/* Wait until the thread finishes, then release its handle. */
void thread_join(thread_t t);

/* Let the thread run on its own; you will never join it. */
void thread_detach(thread_t t);

#endif

#ifdef EZTHREADS_IMPLEMENTATION

#include <stdlib.h>

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

#endif
