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
