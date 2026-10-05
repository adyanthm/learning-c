
#include <ctype.h>
#include <stdio.h>
#include "calc.h"

double calc(char input[]){
    int i = 0;
    double a, b;
    a = next_digit(input, &i);
    while (input[i] != '\n' && input[i] != '\0'){
        while (isspace(input[i])) i++;
        switch (input[i]){
            case '/':
                i++;
                b = next_digit(input, &i);
                a /= b;
                break;
            case '*':
                i++;
                b = next_digit(input, &i);
                a *= b;
                break;
            case '+':
                i++;
                b = next_digit(input, &i);
                a += b;
                break;
            case '-':
                i++;
                b = next_digit(input, &i);
                a -= b;
                break;
        }
    }
    return a;
}

int main(void){
    char input[200];
    fgets(input, 199, stdin);
    printf("%f\n", calc(input));
}
