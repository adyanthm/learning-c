int strlen(char *c){
    int n;
    for (n = 0; c[n] != '\0'; c++) n++;
    return n;
}
