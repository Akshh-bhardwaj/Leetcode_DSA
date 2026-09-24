#include <stdlib.h>

// Compare function for qsort (descending order)
int cmp(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

// Function to find the largest perimeter triangle
int largestPerimeter(int* nums, int numsSize) {
    // Sort the sides in descending order
    qsort(nums, numsSize, sizeof(int), cmp);

    // Check consecutive triplets for triangle property
    for (int i = 0; i < numsSize - 2; i++) {
        if (nums[i] < nums[i+1] + nums[i+2]) {
            return nums[i] + nums[i+1] + nums[i+2];
        }
    }

    // No valid triangle found
    return 0;
}
