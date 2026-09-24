#include <limits.h>

/*
state 0: flat
state 1: holding long
state 2: holding short
*/

long long maximumProfit(int* prices, int pricesSize, int k) {
    if (pricesSize == 0 || k == 0) return 0;

    long long dp[k + 1][3];
    long long prev[k + 1][3];

    // Initialization
    for (int t = 0; t <= k; t++) {
        dp[t][0] = 0;
        dp[t][1] = LLONG_MIN;
        dp[t][2] = LLONG_MIN;
    }

    for (int i = 0; i < pricesSize; i++) {

        // copy previous day
        for (int t = 0; t <= k; t++) {
            prev[t][0] = dp[t][0];
            prev[t][1] = dp[t][1];
            prev[t][2] = dp[t][2];
        }

        for (int t = 0; t <= k; t++) {
            // stay flat
            dp[t][0] = prev[t][0];

            // open long
            dp[t][1] = prev[t][1];
            if (prev[t][0] != LLONG_MIN)
                dp[t][1] = dp[t][1] > prev[t][0] - prices[i]
                           ? dp[t][1]
                           : prev[t][0] - prices[i];

            // open short
            dp[t][2] = prev[t][2];
            if (prev[t][0] != LLONG_MIN)
                dp[t][2] = dp[t][2] > prev[t][0] + prices[i]
                           ? dp[t][2]
                           : prev[t][0] + prices[i];

            // close positions (consume transaction)
            if (t > 0) {
                if (prev[t - 1][1] != LLONG_MIN)
                    dp[t][0] = dp[t][0] > prev[t - 1][1] + prices[i]
                               ? dp[t][0]
                               : prev[t - 1][1] + prices[i];

                if (prev[t - 1][2] != LLONG_MIN)
                    dp[t][0] = dp[t][0] > prev[t - 1][2] - prices[i]
                               ? dp[t][0]
                               : prev[t - 1][2] - prices[i];
            }
        }
    }

    long long ans = 0;
    for (int t = 0; t <= k; t++)
        if (dp[t][0] > ans) ans = dp[t][0];

    return ans;
}
