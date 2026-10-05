#include <stdio.h>

int main(void){

    while (1) {
        int a, b;
        char op;
        printf(">>> ");
        scanf("%d %c %d", &a, &op, &b);

        switch (op) {
            case '+':
                printf("%d\n", a + b);
                break;
            case '-':
                printf("%d\n", a-b);
                break;
            case '*':
                printf("%d\n", a*b);
                break;
            case '/':
                printf("%f\n", (float)a/b);
                break;
            default:
                printf("Invalid command.");
                break;
        }
    }
}
