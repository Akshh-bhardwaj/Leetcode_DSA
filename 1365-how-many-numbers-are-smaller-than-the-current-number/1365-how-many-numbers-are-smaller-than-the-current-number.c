/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* smallerNumbersThanCurrent(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;

    int* ans = (int*)malloc(numsSize * sizeof(int));
    int freq[101] = {0};   // nums[i] range is 0 to 100

    // Count frequency of each number
    for (int i = 0; i < numsSize; i++) {
        freq[nums[i]]++;
    }

    // Prefix sum: count of numbers smaller than i
    for (int i = 1; i <= 100; i++) {
        freq[i] += freq[i - 1];
    }

    // Build answer
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 0)
            ans[i] = 0;
        else
            ans[i] = freq[nums[i] - 1];
    }

    return ans;
}
