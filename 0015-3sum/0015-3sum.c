#include <stdlib.h>

// Comparator for qsort
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// 3Sum function
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    qsort(nums, numsSize, sizeof(int), compare);

    int capacity = 1000;  // Initial capacity
    int** result = (int**)malloc(capacity * sizeof(int*));
    *returnColumnSizes = (int*)malloc(capacity * sizeof(int));
    *returnSize = 0;

    for (int i = 0; i < numsSize - 2; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;  // Skip duplicates

        int left = i + 1;
        int right = numsSize - 1;

        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];

            if (sum == 0) {
                // Store triplet
                int* triplet = (int*)malloc(3 * sizeof(int));
                triplet[0] = nums[i];
                triplet[1] = nums[left];
                triplet[2] = nums[right];

                result[*returnSize] = triplet;
                (*returnColumnSizes)[*returnSize] = 3;
                (*returnSize)++;

                // Reallocate memory if needed
                if (*returnSize >= capacity) {
                    capacity *= 2;
                    result = (int**)realloc(result, capacity * sizeof(int*));
                    *returnColumnSizes = (int*)realloc(*returnColumnSizes, capacity * sizeof(int));
                }

                // Move pointers & skip duplicates
                while (left < right && nums[left] == triplet[1]) left++;
                while (left < right && nums[right] == triplet[2]) right--;
            }
            else if (sum < 0)
                left++;
            else
                right--;
        }
    }

    return result;
}

