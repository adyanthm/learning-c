#include <stdio.h>
#define MAX_SIZE 1000

int len_line(char line[]){
    int len = 0;
    while(line[len] != '\0')
        len++;
    return len;
}

char *line_copy(char *dest, const char *source){
    char *og = dest;
    int i = 0;
    while (source[i] != '\0'){
        dest[i] = source[i];
        i++;
    }
    dest[i] = '\0';
    return og;
}

int main(void){
    int largest = 0;
    char line[MAX_SIZE], max_line[MAX_SIZE];

    while (fgets(line, MAX_SIZE, stdin) != NULL) {
        if (len_line(line) > largest){
            line_copy(max_line, line);
            largest = len_line(line);
        }
        printf("Largest Length: %d\n", largest);
    }
}
