#include <stdlib.h>

int numberOfStableArrays(int zero, int one, int limit) {
    int MOD = 1000000007;
    
    int (*dp)[zero + 1][2] = calloc(one + 1, sizeof(*dp));
    
    dp[0][0][0] = 1;
    dp[0][0][1] = 1;

    for (int i = 0; i <= one; i++) {
        for (int j = 0; j <= zero; j++) {
            for (int k = 1; k <= limit; k++) {
                if (i - k >= 0) {
                    dp[i][j][1] = (dp[i][j][1] + dp[i - k][j][0]) % MOD;
                }
                if (j - k >= 0) {
                    dp[i][j][0] = (dp[i][j][0] + dp[i][j - k][1]) % MOD;
                }
            }
        }
    }

    int result = (dp[one][zero][0] + dp[one][zero][1]) % MOD;
    
    free(dp);
    
    return result;
}