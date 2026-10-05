#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HEAD 0
#define TAIL 1

int output[3];

int coin_engine(int player) {
    int result = rand() % 2;

    if (player == result) {
        return 1;
    }

    return 0;
}

int *martingale(int bal, int games, int initial_bet, int max) {
    int streak_l = 0;
    int longest_l = 0;
    int i;

    for (i = 0; i < games && bal > 0 && bal < max; i++) {

        int bet = initial_bet * (int)pow(2, streak_l + 1);

        while (bet > bal) {
            bet /= 2;
        }

        int choice = rand() % 2;
        int result = coin_engine(choice);

        if (result == 1) {
            bal += bet;
            streak_l = 0;
        }
        else {
            bal -= bet;
            streak_l++;

            if (streak_l > longest_l) {
                longest_l = streak_l;
            }
        }
    }

    output[0] = i;
    output[1] = bal;
    output[2] = longest_l;

    return output;
}

int main(void) {
    srand(time(NULL));

    int bal = 100000;
    int og_bal = bal;
    int max_profit = 100000;
    int max = bal + max_profit;

    int *result = martingale(bal, 1000000, 10, max);

    int profit = result[1] - og_bal;

    printf("Games successfully played: %d\n", result[0]);
    printf("Initial balance: %d\n", og_bal);
    printf("Final balance: %d\n", result[1]);
    printf("Profit: %d\n", profit);
    printf("Longest L streak: %d\n", result[2]);

    return 0;
}
