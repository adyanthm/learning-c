
#include <stdio.h>

// Demo : int nums[] = {5, 3, 2, 9, 4, 8};
// Outer 1
// 1) a) 3 5 2 9 4 8 [i = 0]
// 1) b) 3 2 5 9 4 8 [i = 1]
// 1) c) 3 2 5 9 4 8 [i = 2]
// 1) d) 3 2 5 4 9 8 [i = 3]
// Outer 2.
// 1) e) 3 2 5 4 8 9 [i = 0]
// 2) a) 2 3 5 4 8 9 [i = 1]
// 2) b) 2 3 5 4 8 9 [i = 2]
// 2) c) 2 3 4 5 8 9 {END}

void sort(int nums[], int size){
    for (int j = 0; j < (size- 1); j ++){
        for (int i = 0; i < size - 1; i ++){
            if (nums[i] > nums[i + 1]){
                int temp = nums[i];
                nums[i] = nums[i + 1];
                nums[i + 1] = temp;
            }
        }
    }
}

int main(void){
    int nums[] = {5, 3, 2, 9, 4, 8};
    int size = sizeof(nums) / sizeof(nums[1]);

    sort(nums, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", nums[i]);
    }
}
