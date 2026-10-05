
#include <stdio.h>
void sort(int nums[], int size){
    for (int j = 0; j < size - 1; j++){
        int smallest = j;
        for (int i = j + 1; i < size; i++){
            if (nums[i] < nums[smallest]){
                smallest = i;
            }
        }
        int temp = nums[j];
        nums[j] = nums[smallest];
        nums[smallest] = temp;
    }
}

int main(void){
    int nums[] = {6,5,4,3,2,1};
    sort(nums, 6);
    for (int i = 0; i < 6; i++) {
        printf("%d ", nums[i]);
    }
}
