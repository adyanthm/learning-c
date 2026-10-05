#include <stdio.h>

int isdigit(int n){
    return (n >= '0' && n <= '9')? 1: 0;
}

int isspace(int n){
    return (n == ' ') ? 1: 0;
}

int atoi(char s[]){
    int i, n, sign;
    for (i = 0; isspace(s[i]); i++);
    sign = (s[i] == '-') ? -1: 1;
    if(s[i] == '-' || s[i] == '+')
        i++;
    for (n = 0; isdigit(s[i]); i++)
        n = 10 * n + (s[i] - '0');
    return sign * n;
}

int main(void){
    printf("%d\n", atoi("  -1273"));
    printf("%d\n", atoi("1273"));
}
