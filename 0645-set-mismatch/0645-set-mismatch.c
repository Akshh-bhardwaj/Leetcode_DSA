/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findErrorNums(int* nums, int numsSize, int* returnSize) {
    int* ans = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;

    int* freq = (int*)calloc(numsSize + 1, sizeof(int));

    for (int i = 0; i < numsSize; i++) {
        freq[nums[i]]++;
    }

    for (int i = 1; i <= numsSize; i++) {
        if (freq[i] == 2)
            ans[0] = i;   // duplicate
        else if (freq[i] == 0)
            ans[1] = i;   // missing
    }

    free(freq);
    return ans;
}
