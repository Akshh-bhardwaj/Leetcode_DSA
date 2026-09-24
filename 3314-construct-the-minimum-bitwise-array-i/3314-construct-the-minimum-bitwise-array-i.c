#include <stdlib.h>

int* minBitwiseArray(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* ans = (int*)malloc(numsSize * sizeof(int));

    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];

        // No solution for even num (especially 2), because x | (x + 1) is odd
        if (num % 2 == 0) {
            ans[i] = -1;
            continue;
        }

        int x = -1;

        // Brute force up to num - 1 is safe since nums[i] <= 1000
        for (int a = 0; a < num; a++) {
            if ((a | (a + 1)) == num) {
                x = a;
                break;
            }
        }

        ans[i] = x;
    }

    return ans;
}
