#include <stdio.h>

void printarr(int arr[], int size){
    for (int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void){
    int arr[] = {1,2,3,4,5,6};
    printarr(arr, 6);
}
