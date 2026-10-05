#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void){
    int not_done = 1; // not done giving inputs
    int size = 0;
    int capacity = 4;
    int sum = 0;

    int *nums = malloc(capacity * sizeof(int));

    if (nums == NULL){
        return 1;
    }

    while (not_done){ // till "done" is given.
        char input[100];
        printf("> ");
        scanf("%99s", input);
        if (strcmp(input, "done") == 0){
            not_done = 0;
            break;
        }
        if (size == capacity){
            capacity += size;
            int *temp = realloc(nums, capacity * sizeof(int));
            if (temp == NULL){
                free(nums);
                return 0;
            }
            nums = temp;
        }
        nums[size] = atoi(input);
        size ++;
    }
    for (int i = 0; i < size; i++){
        sum += nums[i];
    }

    free(nums);

    printf("Total sum = %d\n", sum);
    printf("Mean = %f", (double)sum / size);
}
