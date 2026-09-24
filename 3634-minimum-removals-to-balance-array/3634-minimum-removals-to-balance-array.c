#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int minRemoval(int* nums, int numsSize, int k) {
    if (numsSize <= 1) return 0;

    qsort(nums, numsSize, sizeof(int), cmp);

    int maxKeep = 1;
    int j = 0;

    for (int i = 0; i < numsSize; i++) {
        while (j < numsSize && (long long)nums[j] <= (long long)nums[i] * k) {
            j++;
        }
        int keep = j - i;
        if (keep > maxKeep)
            maxKeep = keep;
    }

    return numsSize - maxKeep;
}
