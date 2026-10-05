
#include <stdio.h>
int bin_search(int x, int v[], int n){
    int low, high, mid;
    low = 0;
    high = n-1;

    while (low < high){
        mid = (high + low) / 2;
        if (x > v[mid])
            low = mid + 1;
        else
            high = mid;
    }

    if (x == v[low])
        return low;

    return -1;
}

int main(void){
    int list[] = {1,2,3,4,5,6,7,8,9,10};
    printf("%d ", bin_search(3, list, 10));
}
