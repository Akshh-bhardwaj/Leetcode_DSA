#include <stdlib.h>

/*
 LeetCode C function signature:
 int* getSneakyNumbers(int* nums, int numsSize, int* returnSize)
*/
int* getSneakyNumbers(int* nums, int numsSize, int* returnSize) {
    if (!nums || numsSize < 2) {
        *returnSize = 0;
        return NULL;
    }

    int n = numsSize - 2;              // original distinct count should be n
    if (n <= 0) {
        *returnSize = 0;
        return NULL;
    }

    // counts for values in range [0, n-1]
    int *count = (int*)calloc(n, sizeof(int));
    int *res = (int*)malloc(2 * sizeof(int));
    int found = 0;

    for (int i = 0; i < numsSize && found < 2; ++i) {
        int v = nums[i];
        if (v >= 0 && v < n) {
            count[v]++;
            if (count[v] == 2) {
                res[found++] = v;
            }
        }
        // If input violates constraints (unexpected value), we just ignore it.
    }

    free(count);
    *returnSize = found;
    return res;
}
