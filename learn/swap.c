#include <stdio.h>
#define swap(t, a, b){t temp = a; a = b; b = temp;}

int main(void){
    int a = 20;
    int b = 10;
    swap(int, a, b)
    printf("a: %d b: %d\n", a, b);
}
