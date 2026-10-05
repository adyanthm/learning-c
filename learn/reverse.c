#include <stdio.h>
#include <string.h>

// Reverse in place.
void reverse(char s[]){
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--){
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int main(void){
    char msg[50] = "Hello world!";
    reverse(msg);
    printf("%s", msg);
}
