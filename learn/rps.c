#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int gen_choice(){
    int num = rand() % 3;
    return num;
}

int engine(int player, int bot){
    // return 1 for player win, 0 for bot win, 2 for tie.
    // r = 0
    // p = 1
    // s = 2
    if ((player - bot + 3) % 3 == 1){
        return 1;
    } else if (player == bot) {
        return 2;
    }
    else {
        return 0;
    }
}

int benchmark(){
    int p1_wins = 0;
    int p2_wins = 0;
    int ties = 0;
    const int LIMIT = 100000000;

    for (int i = 0; i < LIMIT; i++) {

        int bot = gen_choice();
        // int bot = 1;
        int bot_2 = gen_choice();

        int status = engine(bot, bot_2);

        switch (status){
            case 1:
                p1_wins += 1;
                break;
            case 0:
                p2_wins += 1;
                break;
            case 2:
                ties += 1;
                break;
        }
    }

    printf("Player 1 wins: %d\n", p1_wins);
    printf("Player 2 wins: %d\n", p2_wins);
    printf("Draws: %d\n", ties);

    printf("Probability of Player 1 wins : %.4f%%\n", (double) p1_wins / LIMIT * 100);
    printf("Probability of Player 2 wins : %.4f%%\n", (double) p2_wins / LIMIT * 100);
    printf("Probability of Draws : %.4f%%\n", (double) ties / LIMIT * 100);

    return 1;
}

int main(void){
    srand(time(NULL));


}
