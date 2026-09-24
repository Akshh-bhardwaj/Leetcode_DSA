long long getDescentPeriods(int* prices, int pricesSize) {
    long long ans = 1;   // first day always counts
    long long dp = 1;    // length of current smooth descent

    for (int i = 1; i < pricesSize; i++) {
        if (prices[i] == prices[i - 1] - 1) {
            dp++;
        } else {
            dp = 1;
        }
        ans += dp;
    }

    return ans;
}
