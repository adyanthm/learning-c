#include <stdio.h>

int main(void){
    int c;
    while ((c = getchar()) != EOF){
        switch (c) {
            case '"': {
                putchar(c);
                while ((c = getchar()) != EOF){
                    putchar(c);
                    if (c == '\\') {
                        putchar(getchar());
                    }
                    else if (c == '"'){
                        break;
                    }
                }
                break;
            }
            case '/': {
                int next = getchar();
                if (next == '/'){
                    while ((c = getchar()) != '\n' && c != EOF);
                    if (c == '\n'){
                        putchar(c);
                    }
                } else if (next == '*') {
                    while ((c = getchar()) != EOF) {
                        if (c == '*'){
                            next = getchar();
                            if (next == '/'){
                                break;
                            }
                        }
                    }
                }
                else {
                    putchar(c);
                    putchar(next);
                }
                break;
            }
            default:
                putchar(c);
                break;
        }
    }
}
