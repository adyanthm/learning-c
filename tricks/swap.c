#include <stdio.h>
int main(void){
    int a = 67;
    int b = 42;
    printf("%d %d\n", a, b);
    a ^= b; // a = 67 ^ 42
    b ^= a; // b = 42 ^ 67 ^ 42 => 67
    a ^= b; // a = 67 ^ 42 ^ 67 => 42
    // Successfuly swapped :D
    printf("%d %d", a, b);
    return 0;
}
