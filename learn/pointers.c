#include <stdio.h>

void print_array(int *nums, int size){
    for (int i = 0; i < size; i++){
        printf("%d ", nums[i]);
    }
}

void sq_array(int *nums, int size){
    for (int i = 0; i < size; i++){
        nums[i] *= nums[i];
    }
}

void rev_array(int *nums, int size){
    for (int i = 0; i < (size / 2); i++){
        int temp = nums[i];
        nums[i] = nums[size-i-1];
        nums[size-i-1] = temp;
    }
}

void swap(int *a, int *b){
    int temp = *b;
    *b = *a;
    *a = temp;
}

int sum_arr(int *nums, int size){
    int sum = 0;
    for (int i = 0; i < size; i++){
        sum += *(nums + i); // OR sum += nums[i]
    }
    return sum;
}

void cp_array(int *source, int *dest, int size){
    for (int i = 0; i < size; i++){
        *(dest + i) = *(source + i); // OR dest[i] = source[i]
    }
}

void min_max(int *nums, int size, int *min, int *max){
    *min = *max = nums[0];
    for (int i = 1; i < size; i++){
        if (nums[i] > *max)
            *max = nums[i];
        else if (nums[i] < *min)
            *min = nums[i];
    }
}

int main(void){
    int nums[] = {1,2,3,4,5,6,7,8,9,10};
    sq_array(nums, 10);
    rev_array(nums, 10);
    print_array(nums, 10);
    int min, max;
    min_max(nums, 10, &min, &max);
    printf("\nmin: %d\nmax: %d", min, max);
}
