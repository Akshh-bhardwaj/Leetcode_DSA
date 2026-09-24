int minimumPairRemoval(int* nums, int numsSize) {
    int operations = 0;

    while (1) {
        // Step 1: Check if array is non-decreasing
        int sorted = 1;
        for (int i = 0; i < numsSize - 1; i++) {
            if (nums[i] > nums[i + 1]) {
                sorted = 0;
                break;
            }
        }
        if (sorted) {
            break;
        }

        // Step 2: Find adjacent pair with minimum sum
        int minSum = nums[0] + nums[1];
        int minIndex = 0;

        for (int i = 1; i < numsSize - 1; i++) {
            int sum = nums[i] + nums[i + 1];
            if (sum < minSum) {
                minSum = sum;
                minIndex = i;
            }
        }

        // Step 3: Replace pair with their sum
        nums[minIndex] = minSum;

        // Shift elements left
        for (int i = minIndex + 1; i < numsSize - 1; i++) {
            nums[i] = nums[i + 1];
        }

        numsSize--;
        operations++;
    }

    return operations;
}
