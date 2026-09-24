long long maxSubarraySum(int* nums, int numsSize, int k) {
    long long prefix[200005];
    prefix[0] = 0;

    for (int i = 1; i <= numsSize; i++) {
        prefix[i] = prefix[i - 1] + nums[i - 1];
    }

    long long best[200005];
    for (int i = 0; i < k; i++) best[i] = prefix[i];

    long long ans = -1000000000000000LL;

    for (int i = k; i <= numsSize; i++) {
        long long remainder = i % k;

        long long curr = prefix[i] - best[remainder];
        if (curr > ans) ans = curr;

        if (prefix[i] < best[remainder]) {
            best[remainder] = prefix[i];
        }
    }

    return ans;
}
