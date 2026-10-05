#include <stdio.h>

unsigned int state = 127;

unsigned int rand_custom(void) {
    state = state * 1103515245 + 12345;
    return state;
}

int main(void) {
    int heads = 0;
    int tails = 0;

    for (int i = 0; i < 100; i++) {
        int roll = rand_custom() % 2;

        printf("%d ", roll);

        if (roll == 0)
            heads++;
        else
            tails++;
    }

    printf("\nHeads: %d", heads);
    printf("\nTails: %d", tails);
}
