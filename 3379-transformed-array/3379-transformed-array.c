#include <stdlib.h>

int* constructTransformedArray(int* nums, int numsSize, int* returnSize) {
    int *result = (int *)malloc(numsSize * sizeof(int));
    *returnSize = numsSize;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 0) {
            result[i] = 0;
        } else {
            int newIndex = (i + nums[i]) % numsSize;

            // handle negative index
            if (newIndex < 0)
                newIndex += numsSize;

            result[i] = nums[newIndex];
        }
    }

    return result;
}
