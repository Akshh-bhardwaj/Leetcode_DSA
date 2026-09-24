#include <stdlib.h>

// Compare function for qsort
int cmp(const void *a, const void *b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int minimumDifference(int* nums, int numsSize, int k) {
    if (k <= 1) return 0;  // selecting only one element => difference 0

    // Sort the scores
    qsort(nums, numsSize, sizeof(int), cmp);

    int minDiff = INT_MAX;

    // Slide window through sorted array
    for (int i = 0; i <= numsSize - k; i++) {
        int diff = nums[i + k - 1] - nums[i];
        if (diff < minDiff) {
            minDiff = diff;
        }
    }

    return minDiff;
}
