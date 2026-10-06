#include <ctype.h>
#include "calc.h"

void clear_space(char s[], int *i){
    // basically, skips forward all the whitespaces and moves to next non space char.
    while (s[*i] == ' ') (*i)++;
}

double next_digit(char s[], int *i){
    // this is just my own implementation of atol lol.
    double val;
    int power;

    for (val = 0.0; isdigit(s[*i]); (*i)++)
        val = val * 10 + (s[*i] - '0');

    // handle the digits after decimal point.
    if (s[*i] == '.') (*i)++;
    for (power = 1; isdigit(s[*i]); (*i)++){
        val = val * 10 + (s[*i] - '0');
        power *= 10;
    }

    return val / power;
}

double factor(char s[], int *i){
    // returns a "number" either directly or by recursively parsing a paranthesis.

    clear_space(s, i);

    if (isdigit(s[*i])) return next_digit(s, i);

    /********************************************************************
     * NOTE: I recommend you to skip this "else if" block until you     *
     * have finished reading until expression() after which you         *
     * should come back and then take a look at this for                *
     * a better understanding of how it works.                          *
     *******************************************************************/

    else if (s[*i] == '('){
        (*i)++;
        double a = expression(s, i);
        (*i)++;
        return a;
    } // recursively parses paranthesis and returns a single float.

    else return 0; // fallback.
}

double term(char s[], int *i){

    /********************************************************
     * Maths doesnt care if we do                           *
     * 10 * 2 / 5 or                                        *
     * 10 / 5 * 2                                           *
     * Both of them yield the same result.                  *
     * Hence, we are parsing together / and * symbols       *
     * and returning a single float.                        *
     * TLDR: Parses the "factors" (numbers) with '/'        *
     * or '*' operators till we find a different operator   *
     * and then it returns the result parsed.               *
     *******************************************************/

    double a = factor(s, i);
    char op;

    clear_space(s, i);

    while (s[*i] == '/' || s[*i] == '*'){
        op = s[*i];
        (*i)++;
        double b = factor(s, i);
        if (op == '*') a *= b;
        else a /= b;
        clear_space(s, i);
    }

    return a;
}

double expression(char s[], int *i){

    /********************************************************
     * So, we simplify "terms" into a single float          *
     * using the term() function and then parsing           *
     * them for '+' and '-' operators. Both '+' and         *
     * '-' have the same precedence and are left            *
     * associative, so they are parsed from left to         *
     * right. Example:                                      *
     *  2 + 5 - 3 = (2 + 5) - 3 = 4                         *
     *  2 - 3 + 5 = (2 - 3) + 5 = 4                         *
     * So we just parse them together :)                    *
     *******************************************************/

    double a = term(s, i);
    char op;

    clear_space(s, i);

    while (s[*i] == '+' ||s[*i] == '-'){
        op = s[*i];
        (*i)++;
        double b = term(s, i);
        if (op == '+') a += b;
        else a -= b;
        clear_space(s, i);
    }

    return a;
}

double calc(char s[]){

    /****************************************************************
      * QN) Why do you need a calc() function when you              *
      * can call expression() directly?                             *
      *                                                             *
      * ANS) expression() needs an integer index to keep track      *
      * of its position in the string, so you'd have to create      *
      * one and pass its address every time.                        *
      *                                                             *
      * calc() hides that implementation detail and lets the        *
      * user simply pass an expression string.                      *
      *                                                             *
      * TLDR: Simple interface for the user.                        *
      **************************************************************/

    int i = 0;
    return expression(s, &i);
}
