int findMaxConsecutiveOnes(int* nums, int numsSize) {
    int maxCount = 0;
    int currCount = 0;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 1) {
            currCount++;
            if (currCount > maxCount)
                maxCount = currCount;
        } else {
            currCount = 0;
        }
    }

    return maxCount;
}
