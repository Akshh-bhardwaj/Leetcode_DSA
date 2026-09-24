/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDisappearedNumbers(int* nums, int numsSize, int* returnSize) {
    // Mark visited indices
    for (int i = 0; i < numsSize; i++) {
        int idx = abs(nums[i]) - 1;
        if (nums[idx] > 0)
            nums[idx] = -nums[idx];
    }

    // Count missing numbers
    int count = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > 0)
            count++;
    }

    int* ans = (int*)malloc(count * sizeof(int));
    *returnSize = count;

    int k = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > 0)
            ans[k++] = i + 1;
    }

    return ans;
}
