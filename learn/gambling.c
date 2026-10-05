#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int toss_coin(void) {
    return rand() % 2;
}

int gamble(int bal) {
    int bet;
    int result;
    char choice[10];
    char again[10];

    while (1) {
        printf("\nBalance: %d\n", bal);

        printf("Enter head or tail (or exit): ");
        scanf("%9s", choice);

        if (strcmp(choice, "exit") == 0 ){
            printf("GGs, You exited with a balance of %d\n", bal);
            return 0;
        }

        printf("Enter bet amount: ");
        scanf("%d", &bet);

        if (bet > bal || bet <= 0) {
            printf("Invalid Bet Amount\n");
            continue;
        }

        result = toss_coin();

        if (strcmp(choice, "head") == 0 && result == 0) {
            bal += bet;
            printf("You won!\n");
        }
        else if (strcmp(choice, "tail") == 0 && result == 1) {
            bal += bet;
            printf("You won!\n");
        }

        else {
            bal -= bet;
            printf("You lost!\n");
        }

        printf("Your current balance is : %d\n", bal);
    }
}

int main(void) {
    srand(time(NULL));

    int bal = 10000;
    gamble(bal);

    return 0;
}
