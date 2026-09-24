#define MOD 1000000007

int numRollsToTarget(int n, int k, int target) {
    // dp[i][j] = number of ways to roll i dice to get sum j
    int dp[n+1][target+1];
    memset(dp, 0, sizeof(dp));
    
    dp[0][0] = 1; // base case: 0 dice -> sum 0 has 1 way
    
    for (int dice = 1; dice <= n; dice++) {
        for (int sum = 1; sum <= target; sum++) {
            long long ways = 0;
            for (int face = 1; face <= k; face++) {
                if (sum - face >= 0) {
                    ways += dp[dice-1][sum-face];
                }
            }
            dp[dice][sum] = ways % MOD;
        }
    }
    
    return dp[n][target];
}
