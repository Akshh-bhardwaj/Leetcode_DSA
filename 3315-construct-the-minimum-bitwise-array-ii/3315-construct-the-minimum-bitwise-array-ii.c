#include <stdlib.h>

int* minBitwiseArray(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* ans = (int*)malloc(numsSize * sizeof(int));
    if (!ans) return NULL;

    for (int i = 0; i < numsSize; i++) {
        long long p = nums[i];
        long long S = p + 1LL;

        // find largest power of 2 dividing S
        long long d = 1LL;
        while ((S % (d * 2LL)) == 0LL) {
            d *= 2LL;
        }

        if (d < 2LL) {
            ans[i] = -1;
        } else {
            long long A = (S / d) - 1LL;
            long long x = A * d + (d / 2LL - 1LL);
            ans[i] = (int)x;
        }
    }

    return ans;
}
