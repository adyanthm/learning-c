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

typedef struct {
    volatile LONG state;   /* 0 = unlocked, 1 = locked, 2 = locked + someone is sleeping */
} mutex_t;

#endif

#ifdef EZTHREADS_IMPLEMENTATION

#include <stdlib.h>
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0602   /* needed for WaitOnAddress (Windows 8+) */
#endif
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

/************************************************************************************
 * Mutexes: only one thread at a time may be between lock and unlock.               *
 * Used to protect shared data (e.g. the list of connected clients).                *
 *                                                                                  *
 * states: 0 = unlocked, 1 = locked, 2 = locked + someone is sleeping on it.        *
 * Link with -lsynchronization.                                                     *
 ***********************************************************************************/

void mutex_init(mutex_t *m){
    m->state = 0;
}

void mutex_lock(mutex_t *m){
    if (InterlockedCompareExchange(&m->state, 1, 0) == 0)
        return; // 0 -> 1 (unlocked -> locked)

    // If the code reaches here, means its locked.
    while (InterlockedExchange(&m->state, 2) != 0){
        // Always set state to 2 and look at the OLD value:
        //   old 0 -> lock was free, we own it now (state is 2, which is fine)
        //   old 1 or 2 -> still held by someone, go to sleep and retry
        LONG expected = 2;
        WaitOnAddress(&m->state, &expected, sizeof(LONG), INFINITE);
    }
}

int mutex_trylock(mutex_t *m){
    return InterlockedCompareExchange(&m->state, 1, 0) == 0;
}

void mutex_unlock(mutex_t *m){
    /* Releases and if someone was sleeping (old state 2), wake exactly one of them. */
    if (InterlockedExchange(&m->state, 0) == 2)
        WakeByAddressSingle((PVOID)&m->state);
}

void mutex_destroy(mutex_t *m){
    (void)m;
}

#endif
