#include <stdio.h>
#include <string.h>

int main() {
    char password[20];
    printf("Enter password: ");
    scanf("%19s", password);

    if (strcmp(password, "secret123") == 0) {
        printf("Access Granted!\n");
    } else {
        printf("Access Denied!\n");
    }
    return 0;
}
