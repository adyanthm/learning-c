#include <stdio.h>
void strcopy(char *t, char *s){
    while ((*t++ = *s++) != '\0');
}

char *arrstrcopy(char t[], char s[]){
    int i;
    for (i = 0; s[i] != '\0'; i++) t[i] = s[i];
    t[i] = '\0';
    return t;
}

int strcomp(char *s, char *t){
    int i;
    for (i = 0; t[i] != s[i]; i++){
        if (t[i] == '\0'){
            return 0;
        }
    }
    return s[i] - t[i];
}

int pstrcomp(char *s, char *t){
    while (*s++ == *t++)
        if (*s == '\0') return 0;
    return *s - *t;
}

void strcat_custom(char *s, char *t){
    while (*s) s++;
    while ((*s++ = *t++));
}

int strend(char *s, char *t){
    char *os = s;
    char *ot = t;
    while (*s++);
    while (*t++);
    while (s > os && t > ot)
        if (*--s != *--t)
            return 0;
    return t == ot;
}

int strncomp(char *s, char *t, int n){
    while (n-- != 0 && *s == *t){
        if (*s == '\0') return 0;
        s++; t++;
    }
    return (n < 0) ? 0: *s - *t;
}

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

int patoi(char *s){
    int n = 0, sign = 1;
    while(isspace(*s)) s++;
    sign = (*s == '-') ? -1:1;
    if(*s == '-' || *s == '+') s++;
    while (isdigit(*s))
        n = 10 * n + (*s++ - '0');
    return sign * n;
}

int main(void){
    char *inp = " -123";
    char *inp2 = "  123";
    char *inp3 = "  +123";
    printf("%d\n", patoi(inp));
    printf("%d\n", patoi(inp2));
    printf("%d\n", patoi(inp3));
}
