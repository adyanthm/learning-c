#include <stdio.h>
int lower(int c){
    if (c > 'A' && c < 'a')
        return c + ('a' - 'A');
    else
        return c;
}

int to_lower(int c){
    return (c >= 'A' && c <= 'Z')? c + ('a' - 'A'): c;
}

int main(void){
    printf("%c\n", lower('H'));
    printf("%c", to_lower('H'));
}
