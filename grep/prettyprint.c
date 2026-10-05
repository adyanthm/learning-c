#include <stdio.h>
#include "prettyprint.h"
#define RESET "\033[0m"

int len(char s[]){
    int i;
    for (i = 0; s[i] != '\0'; i++);
    return i;
}

int strindex(char s[], char t[]){
    int i, j, k;
    for (i = 0; s[i] != '\0'; i++){
        for (j = i, k = 0; s[j] == t[k] && t[k] != '\0'; k++, j++);
        if (t[k] == '\0'){
            return i;
        }
    }
    return -1;
}

void prettyprint(char line[], char s[], char colour[]){
    int length = len(s);
    int index = strindex(line, s);
    printf("%.*s", index , line);
    printf("%s%.*s%s", colour, length, line + index, RESET);
    printf("%s\n", line + index + length);
}
