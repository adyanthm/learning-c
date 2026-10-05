#define ALLOCSIZE 10000
static char buffer[ALLOCSIZE];
static char *p = buffer; // next free block

// n means number of bytes to allocate.
char *alloc(int n){
    if (buffer + ALLOCSIZE - p >= n){
        p += n;
        return p - n; // return old pointer location.
    } else{
        return 0; // no memory available
    }
}

void afree(char *pointer){
    if (pointer >= buffer && p < buffer + ALLOCSIZE)
        p = pointer;
}
