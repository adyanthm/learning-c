#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void split(char *array, int *numbers, int size){
    char *token = strtok(array, " \t\n");

    for (int i = 0; token != NULL && i < size; i++){
        numbers[i] = atoi(token);
        token = strtok(NULL, " \t\n");
    }
}

double mean(int *nums, int size){
    int sum = 0;
    for(int i = 0; i < size; i++){
        sum += nums[i];
    }
    double result = (double) sum / sizeof(nums);
    return result;
}

int main(void){
    char input[100];
    int nums[100];
    printf("> ");
    fgets(input, sizeof(input), stdin);
    split(input, nums, 100);
    printf("The mean is : %lf", mean(nums, 100));
}
