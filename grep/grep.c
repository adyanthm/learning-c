#include <stdio.h>
#include "prettyprint.h"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

int main(int argc, char *argv[]){
    int c;
    char line[1024];
    int i = 0;
    int ln = 0;

    if (argc != 3){
        printf("Use: %s <filename> <phrase>\n", argv[0]);
        printf("Example: %s logs.txt 404\n", argv[0]);
        return 1;
    }

    char *pattern = argv[2];

    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Error opening file!");
        return 1;
    }

    while ((c = fgetc(file)) != EOF){
        while (c != '\n' && c != EOF){
            line[i] = c;
            i++;
            c = fgetc(file);
        }
        ln++;
        line[i] = '\0';
        i = 0;
        if (strindex(line, pattern) != -1){
            printf(GREEN"%d: "RESET, ln);
            prettyprint(line, pattern, YELLOW);
        }
    }
}
