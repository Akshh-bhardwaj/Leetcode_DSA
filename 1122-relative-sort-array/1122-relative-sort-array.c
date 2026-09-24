#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort (not needed in this solution, but left for flexibility)
int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int* relativeSortArray(int* arr1, int arr1Size, int* arr2, int arr2Size, int* returnSize) {
    int count[1001] = {0};  // arr[i] <= 1000
    *returnSize = arr1Size;

    // Count frequency of arr1 elements
    for (int i = 0; i < arr1Size; i++) {
        count[arr1[i]]++;
    }

    int* result = (int*)malloc(sizeof(int) * arr1Size);
    int k = 0;

    // Place elements according to arr2 order
    for (int i = 0; i < arr2Size; i++) {
        while (count[arr2[i]] > 0) {
            result[k++] = arr2[i];
            count[arr2[i]]--;
        }
    }

    // Place remaining elements (not in arr2) in ascending order
    for (int i = 0; i <= 1000; i++) {
        while (count[i] > 0) {
            result[k++] = i;
            count[i]--;
        }
    }

    return result;
}
