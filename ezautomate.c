#include <Windows.h>
#include <stdio.h>
#include <string.h>


void search(const char *dir, const char *out){
    char pattern[MAX_PATH];
    snprintf(pattern, sizeof pattern, "%s\\*", dir);

    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA(pattern, &fd);

    if (h == INVALID_HANDLE_VALUE)
        return;

    do {
        if (strcmp(fd.cFileName, ".") == 0 ||
            strcmp(fd.cFileName, "..") == 0)
            continue;

        char src[MAX_PATH], dest[MAX_PATH];
        snprintf(src, sizeof src, "%s\\%s", dir, fd.cFileName);
        snprintf(dest, sizeof dest, "%s\\%s", out, fd.cFileName);

        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (_stricmp(src, out) == 0)
                continue;
            search(src, out);
        } else if (strncmp(fd.cFileName, "ez", 2) == 0) {
            printf("%s\n", src);
            if (!CopyFileA(src, dest, FALSE))
                fprintf(stderr, "Copy failed: %s (error %lu)\n",src, GetLastError());
        }
    } while (FindNextFileA(h, &fd));

    FindClose(h);
}

int main(void){
    search(".", "./ezlibs");
    return 0;
}
