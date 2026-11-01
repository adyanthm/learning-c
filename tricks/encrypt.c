#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *encrypt(char *string, int key){
    size_t len = strlen(string);
    char *result = malloc(len + 1);
    if (result == NULL)
        return NULL;
    for (size_t i = 0; i < len; i++) {
        result[i] = string[i] ^ key;
    }
    result[len] = '\0';
    return result;
}

int main(void){
    while (1){
        char msg[1024];
        int key;
        printf("Enter Data: ");
        scanf("%s", msg);
        printf("Enter key: ");
        scanf("%d", &key);
        printf("=> %s\n", encrypt(msg, key));
    }
}
