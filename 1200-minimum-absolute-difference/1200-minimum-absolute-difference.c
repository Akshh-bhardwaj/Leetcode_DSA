#include <stdlib.h>

// Compare function for qsort
int cmp(const void *a, const void *b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

int** minimumAbsDifference(int* arr, int arrSize, int* returnSize, int** returnColumnSizes){
    // Step 1: Sort the array
    qsort(arr, arrSize, sizeof(int), cmp);

    // Step 2: Find the minimum difference
    int minDiff = INT_MAX;
    for (int i = 1; i < arrSize; i++) {
        int diff = arr[i] - arr[i - 1];
        if (diff < minDiff) {
            minDiff = diff;
        }
    }

    // We can have at most arrSize - 1 pairs
    int maxPairs = arrSize - 1;
    int **result = (int **)malloc(maxPairs * sizeof(int *));
    *returnColumnSizes = (int *)malloc(maxPairs * sizeof(int));
    *returnSize = 0;

    // Step 3: Collect all pairs with that minimum difference
    for (int i = 1; i < arrSize; i++) {
        int diff = arr[i] - arr[i - 1];
        if (diff == minDiff) {
            int *pair = (int *)malloc(2 * sizeof(int));
            pair[0] = arr[i - 1];
            pair[1] = arr[i];
            result[*returnSize] = pair;
            (*returnColumnSizes)[*returnSize] = 2;
            (*returnSize)++;
        }
    }

    return result;
}
