#include <stdio.h>
#include <stdlib.h>

int main(void){
    int size;

    printf("How many numbers: ");
    scanf("%d", &size);

    int *nums = malloc(size * sizeof(int));

    if (nums == NULL){
        return 1;
    }

    for (int i = 0; i < size; i++){
        printf("nums[%d]: ", i);
        scanf("%d", &nums[i]);
    }

    printf("Numbers: \n");

    for (int i = 0; i < size; i++){
        printf("%d ", nums[i]);
    }

    printf("\n");
    free(nums);

    return 0;
}
