# What is this?

I have been writing a bunch of small `ez` wrappers for my C projects, so I thought I might as well share them all in one place for others to use.

`ezautomate.c` searches the current directory and all its subdirectories for files starting with `ez` and copies them into `ezlibs`, so you don't have to hunt them down yourself.

# Why use these?

They are just simple wrappers that save you from writing the same boilerplate over and over. Especially when those boilerplate code could have been way more simpler so you don't have to remember the syntax and all that :)

For example, with `ezthreads`, creating a thread is as simple as:

```c
#include "ezthreads.h"
#include <Windows.h>
#include <stdio.h>

void worker(void *arg) {
    Sleep(2000);
    printf("worker: done\n");
}

int main(void) {
    thread_t thread = thread_start(worker, NULL);

    printf("main: waiting...\n");
    thread_join(thread);
    printf("main: resumed\n");

    return 0;
}
```

Compare that to doing the same thing with the Windows API directly, where you need to deal with `CreateThread`, `WaitForSingleObject`, `CloseHandle`, and a bunch of extra boilerplate.

I have made similar wrappers for SQLite (`ezsqlite`), sockets (`ezsocks`), and a few other things.

I will keep adding more as I work on projects and find more stuff that could use a simpler interface. More verbose examples for all these `ez` wrappers are coming soon! Have fun :)
