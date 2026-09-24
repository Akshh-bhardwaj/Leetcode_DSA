#include <stdlib.h>

// Compare function for qsort
int cmp(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

int minPairSum(int* nums, int numsSize) {
    // Sort the array
    qsort(nums, numsSize, sizeof(int), cmp);

    int maxSum = 0;
    int left = 0, right = numsSize - 1;

    // Pair smallest with largest
    while (left < right) {
        int sum = nums[left] + nums[right];
        if (sum > maxSum) {
            maxSum = sum;
        }
        left++;
        right--;
    }
    return maxSum;
}
