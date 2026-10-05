#include <ctype.h>
#include "calc.h"

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
