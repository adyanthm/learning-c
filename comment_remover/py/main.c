#include <stdio.h>

int main(int argc, char *argv[]){
    if (argc != 3){
        printf("Usage: %s <input> <output>\n", argv[0]);
        return 1;
    }
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    if (in == NULL || out == NULL){
        printf("Could not open file.\n");
        return 1;
    }

    int c;
    while ((c = fgetc(in)) != EOF){
        switch (c) {
            case '"': {
                int c2 = fgetc(in);
                int c3 = fgetc(in);
                if (c2 == '"' && c3 == '"'){
                    while ((c = fgetc(in)) != EOF){
                        if (c == '"'){
                            c2 = fgetc(in);
                            c3 = fgetc(in);
                            if (c2 == '"' && c3 == '"'){
                                break;
                            }
                        }
                    }
                    break;
                } else {
                    fputc(c, out);
                    if (c2 != EOF)
                        fputc(c2, out);
                    if (c3 != EOF)
                        fputc(c3, out);
                    while ((c = fgetc(in)) != EOF){
                        fputc(c, out);
                        if (c == '\\') {
                            fputc(fgetc(in), out);
                        }
                        else if (c == '"'){
                            break;
                        }
                    }
                    break;
                }
            }
            case '\'': {
                int c2 = fgetc(in);
                int c3 = fgetc(in);
                if (c2 == '\'' && c3 == '\''){
                    while ((c = fgetc(in)) != EOF){
                        if (c == '\''){
                            c2 = fgetc(in);
                            c3 = fgetc(in);
                            if (c2 == '\'' && c3 == '\''){
                                break;
                            }
                        }
                    }
                    break;
                } else {
                    fputc(c, out);
                    if (c2 != EOF)
                        fputc(c2, out);
                    if (c3 != EOF)
                        fputc(c3, out);
                    while ((c = fgetc(in)) != EOF){
                        fputc(c, out);
                        if (c == '\\') {
                            fputc(fgetc(in), out);
                        }
                        else if (c == '\''){
                            break;
                        }
                    }
                    break;
                }
            }
            case '#':
                while ((c = fgetc(in)) != EOF && c != '\n');
                if (c == '\n')
                    fputc('\n', out);
                break;
            default:
                fputc(c, out);
                break;
        }
    }
    fclose(in);
        fclose(out);

    return 0;
}
