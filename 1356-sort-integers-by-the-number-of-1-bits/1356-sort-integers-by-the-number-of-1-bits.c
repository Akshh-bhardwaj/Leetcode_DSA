#include <stdlib.h>

// function to count set bits
int countBits(int x) {
    int count = 0;
    while (x) {
        count += x & 1;
        x >>= 1;
    }
    return count;
}

// comparator for qsort
int cmp(const void *a, const void *b) {
    int x = *(int *)a;
    int y = *(int *)b;

    int cx = countBits(x);
    int cy = countBits(y);

    if (cx == cy)
        return x - y;   // if same bit count → sort by value
    return cx - cy;     // sort by bit count
}

int* sortByBits(int* arr, int arrSize, int* returnSize) {
    qsort(arr, arrSize, sizeof(int), cmp);
    *returnSize = arrSize;
    return arr;
}