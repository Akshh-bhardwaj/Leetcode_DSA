int countPartitions(int* nums, int numsSize) {
    long long sum = 0;
    for (int i = 0; i < numsSize; ++i) {
        sum += nums[i];
    }

    // If total sum is even → every split (0..n-2) gives even difference
    // If total sum is odd  → no split gives even difference
    if ((sum & 1LL) == 0)
        return numsSize - 1;
    else
        return 0;
}