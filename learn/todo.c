#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    char todo[100][100];
    char input[100];

    int count = 0;

    while (1) {
        printf("> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strncmp(input, "Add ", 4) == 0){
            strcpy(todo[count], input + 4);
            count++;
        }
        else if (strcmp(input, "List") == 0) {
            for (int i = 0; i < count; i++){
                printf("%d. %s\n", i+1, todo[i]);
            }
        }
        else if (strncmp(input, "Delete ", 7) == 0) {
            int index = atoi(input + 7);
            index--;
            for (int i = index; i < count - 1; i++){
                strcpy(todo[i], todo[i + 1]);
            }
            count--;
        }
        else if (strcmp(input, "Quit") == 0){
            return 0;
        }
    }
}
