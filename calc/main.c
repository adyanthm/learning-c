#include <string.h>
#include <stdio.h>
#include "calc.h"

int main(void){
    char expr[1000];
    while (1){
        printf(">>> ");
        fgets(expr, sizeof(expr), stdin);
        if (strcmp(expr, "quit\n") == 0) return 0;
        printf("Evaluated: %f\n", calc(expr));
    }
}
