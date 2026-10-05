#include <stdio.h>
#define max(a,b) (a > b) ? a : b

int main(void){
    int a = 3;
    int b = 5;
    printf("%d\n", max(a++, b));
    printf("%d %d\n", a, b);
}
