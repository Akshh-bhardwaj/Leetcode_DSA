#include <stdbool.h>
#include <stdlib.h>

bool* prefixesDivBy5(int* nums, int numsSize, int* returnSize) {
    bool* result = (bool*)malloc(numsSize * sizeof(bool));
    *returnSize = numsSize;

    int num = 0;
    for (int i = 0; i < numsSize; i++) {
        num = (num * 2 + nums[i]) % 5;   // keep only remainder to avoid overflow
        result[i] = (num == 0);
    }

    return result;
}
