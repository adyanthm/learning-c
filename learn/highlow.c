#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int gen_rand(int lower, int upper){
    srand(time(NULL));
    int rand_num = rand() % upper + lower;
    return rand_num;
}

int highlow(int target){
    int num;
    scanf("%d", &num);
    if (num > target){
        printf("Too high! Try again: ");
        return highlow(target);
    } else if (num < target) {
        printf("Too low! Try again: ");
        return highlow(target);
    } else {
        printf("You got it! Good game!");
        return 0;
    }
}

int main(void){
    int x, status, num;
    printf("Enter a number: ");
    num = gen_rand(0, 100);
    status = highlow(num);
    if (status == 0){
        return 0;
    }
}
