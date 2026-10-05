
#include <ctype.h>
#include <stdio.h>

double next_digit(char s[], int *i){
    double val, power;
    int sign = 1;

    while (isspace((unsigned char)s[*i]))
        (*i)++;

    if (s[*i] == '-') {
        sign = -1;
        (*i)++;
    } else if (s[*i] == '+') {
        (*i)++;
    }
    for (val = 0.0; isdigit(s[*i]); (*i)++)
        val = 10.0 * val + (s[*i] - '0');

    if (s[*i] == '.') (*i)++;
    for (power = 1.0; isdigit(s[*i]); (*i)++){
        val = 10.0 * val + (s[*i] - '0');
        power *= 10;
    }

    return sign * val / power;
}

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
