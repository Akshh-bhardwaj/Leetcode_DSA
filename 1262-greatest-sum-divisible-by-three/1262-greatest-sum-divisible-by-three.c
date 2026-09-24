int maxSumDivThree(int* nums, int numsSize) {
    int dp[3] = {0, -1000000000, -1000000000};

    for (int i = 0; i < numsSize; i++) {
        int temp[3];
        temp[0] = dp[0];
        temp[1] = dp[1];
        temp[2] = dp[2];

        for (int r = 0; r < 3; r++) {
            int newR = (r + nums[i]) % 3;
            int val = dp[r] + nums[i];
            if (val > temp[newR]) {
                temp[newR] = val;
            }
        }

        dp[0] = temp[0];
        dp[1] = temp[1];
        dp[2] = temp[2];
    }

    return dp[0];
}
